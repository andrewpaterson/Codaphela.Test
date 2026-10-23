#include <string.h>
#include "BaseLib/MemoryDrive.h"
#include "TestLib/Assert.h"
#include "TestAsm65Context.h"


#define LAZY_SECTOR_SIZE	512
#define LAZY_FIRST_SECTOR	1
#define LAZY_CODE_END		0x18000


//A resident start (linked first) and other objects whose code is loaded when it is first called.
struct SLazyTest
{
	CAsm65Library	cObjects;
	CAsm65Linker	cLinker;
	CMemoryDrive	cDrive;
};


//////////////////////////////////////////////////////////////////////////
//
// Links szStart (resident) and the other sources lazily, puts the units on a drive of
// uiDriveSectors and loads the core.  Returns false if it does not link.
//
//////////////////////////////////////////////////////////////////////////
static bool LazyBegin(SLazyTest* psTest, STestAsm65Run* psRun, uint32 uiCodeEnd, uint32 uiDriveSectors, const char* szStart, const char* szOther, const char* szThird)
{
	CArrayUint8*	pcImage;
	bool			bResult;

	psTest->cObjects.Init("objects");
	psTest->cLinker.Init();
	psTest->cLinker.SetLazy(uiCodeEnd, LAZY_SECTOR_SIZE, LAZY_FIRST_SECTOR);
	TestAsm65AssembleObject(psTest->cObjects.AddObject("start"), szStart);
	psTest->cLinker.AddResidentObject(psTest->cObjects.GetObject(0));
	TestAsm65AssembleObject(psTest->cObjects.AddObject("b"), szOther);
	psTest->cLinker.AddObject(psTest->cObjects.GetObject(1));
	if (szThird)
	{
		TestAsm65AssembleObject(psTest->cObjects.AddObject("c"), szThird);
		psTest->cLinker.AddObject(psTest->cObjects.GetObject(2));
	}
	bResult = psTest->cLinker.Link();
	AssertString("", psTest->cLinker.GetErrors());

	psTest->cDrive.Init(uiDriveSectors * LAZY_SECTOR_SIZE, LAZY_SECTOR_SIZE);
	pcImage = psTest->cLinker.GetLazyImage();
	if (LAZY_FIRST_SECTOR * LAZY_SECTOR_SIZE + pcImage->NumElements() <= uiDriveSectors * LAZY_SECTOR_SIZE)
	{
		memcpy((uint8*)psTest->cDrive.GetMemory() + LAZY_FIRST_SECTOR * LAZY_SECTOR_SIZE, pcImage->GetData(), pcImage->NumElements());
	}
	TestAsm65BeginOutput(psRun, psTest->cLinker.GetOutput(), ASM65_DEFAULT_TEXT_ADDRESS);
	psRun->pcContext->SetDrive(&psTest->cDrive);
	return bResult;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
static void LazyEnd(SLazyTest* psTest, STestAsm65Run* psRun)
{
	TestAsm65End(psRun);
	psTest->cDrive.Kill();
	psTest->cLinker.Kill();
	psTest->cObjects.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
static int64 LazySymbol(SLazyTest* psTest, const char* szName)
{
	int64	iValue;

	iValue = -1;
	AssertTrue(psTest->cLinker.GetSymbol(szName, &iValue));
	return iValue;
}


//////////////////////////////////////////////////////////////////////////
//
// The resident start calls Twice twice and AddTen, which calls Twice: each unit is
// read from the drive once, when it is first called.
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65LazyCalls(void)
{
	SLazyTest		sTest;
	STestAsm65Run	sRun;

	AssertTrue(LazyBegin(&sTest, &sRun, LAZY_CODE_END, 16,
		"	.section text, keep\n"
		"	wtth (A, B), 4\n"
		"	wtth (X, Y), 4\n"
		"	cpy A, 1\n"
		"	jsr Twice\n"
		"	jsr Twice\n"
		"	jsr AddTen\n"
		"	stp\n",
		"	.global Twice\n"
		"Twice:\n"
		"	add A, A\n"
		"	ret\n"
		"	.section text.AddTen\n"
		"	.global AddTen\n"
		"AddTen:\n"
		"	jsr Twice\n"
		"	add A, 10\n"
		"	ret\n",
		NULL));
	AssertSize(2, sTest.cLinker.NumUnits());
	AssertTrue(LazySymbol(&sTest, "Twice") < LAZY_CODE_END);
	AssertTrue(strstr(sTest.cLinker.GetMap(), "Lazy units (sector, size)\n") != NULL);

	AssertTrue(TestAsm65Run(&sRun, 10000) < 10000);
	AssertLong(18, TestAsm65MPU(&sRun)->GetA());
	AssertSize(2, sRun.pcContext->NumDriveReads());
	AssertLongLongIntHex(0, sRun.pcContext->GetLong((uint32)LazySymbol(&sTest, "R_LazyError")));
	LazyEnd(&sTest, &sRun);
}


//////////////////////////////////////////////////////////////////////////
//
// A function's address in data is its trampoline, the same as everywhere else, and
// calling through it loads the unit.  An address inside a unit (Table) has the unit's
// address added when it is loaded; a relative call from a unit to the core (brsr
// Core) is worked out then too.
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65LazyAddresses(void)
{
	SLazyTest		sTest;
	STestAsm65Run	sRun;

	AssertTrue(LazyBegin(&sTest, &sRun, LAZY_CODE_END, 16,
		"	.section text, keep\n"
		"	wtth (A, B), 4\n"
		"	wtth (X, Y), 4\n"
		"	cpy A, 0\n"
		"	cpy X, [Pointer]\n"
		"	cmp X, Inner\n"
		"	brac z, Different\n"
		"	jsr X\n"
		"	stp\n"
		"Different:\n"
		"	cpy A, -2\n"
		"	stp\n"
		"	.global Core\n"
		"Core:\n"
		"	add A, 100\n"
		"	ret\n"
		"	.section data\n"
		"Pointer:\n"
		"	.long Inner\n",
		"	.global Inner\n"
		"Inner:\n"
		"	cpy Y, Table\n"
		"	add A, [Y]\n"
		"	add A, [4 + Y]\n"
		"	brsr Core\n"
		"	ret\n"
		"	.align 4\n"
		"Table:\n"
		"	.long 20, 3\n",
		NULL));
	AssertTrue(TestAsm65Run(&sRun, 10000) < 10000);
	AssertLong(123, TestAsm65MPU(&sRun)->GetA());
	AssertSize(1, sRun.pcContext->NumDriveReads());
	LazyEnd(&sTest, &sRun);
}


//////////////////////////////////////////////////////////////////////////
//
// A resident section stays in the core (it is called without the loader), so only
// Twice is a unit.
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65LazyResident(void)
{
	SLazyTest		sTest;
	STestAsm65Run	sRun;

	AssertTrue(LazyBegin(&sTest, &sRun, LAZY_CODE_END, 16,
		"	.section text, keep\n"
		"	wtth (A, B), 4\n"
		"	wtth (X, Y), 4\n"
		"	cpy A, 3\n"
		"	jsr Twice\n"
		"	jsr Fixed\n"
		"	stp\n",
		"	.global Twice\n"
		"Twice:\n"
		"	add A, A\n"
		"	ret\n"
		"	.section text.Fixed, resident\n"
		"	.global Fixed\n"
		"Fixed:\n"
		"	add A, 1\n"
		"	ret\n",
		NULL));
	AssertSize(1, sTest.cLinker.NumUnits());
	AssertTrue(TestAsm65Run(&sRun, 10000) < 10000);
	AssertLong(7, TestAsm65MPU(&sRun)->GetA());
	AssertSize(1, sRun.pcContext->NumDriveReads());
	LazyEnd(&sTest, &sRun);
}


//////////////////////////////////////////////////////////////////////////
//
// No room for a unit stops with A -1 and R_LazyError 1; a drive error with
// R_LazyError 2.
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65LazyFailures(void)
{
	SLazyTest		sTest;
	STestAsm65Run	sRun;
	const char*		szStart;
	const char*		szBig;

	szStart =
		"	.section text, keep\n"
		"	wtth (A, B), 4\n"
		"	wtth (X, Y), 4\n"
		"	jsr Big\n"
		"	stp\n";
	szBig =
		"	.global Big\n"
		"Big:\n"
		"	cpy A, 5\n"
		"	ret\n"
		"	.space 2000\n";

	AssertTrue(LazyBegin(&sTest, &sRun, 0x10400, 16, szStart, szBig, NULL));
	AssertTrue(TestAsm65Run(&sRun, 10000) < 10000);
	AssertLongLongIntHex(0xFFFFFFFF, TestAsm65MPU(&sRun)->GetA());
	AssertLong(1, sRun.pcContext->GetLong((uint32)LazySymbol(&sTest, "R_LazyError")));
	AssertSize(0, sRun.pcContext->NumDriveReads());
	LazyEnd(&sTest, &sRun);

	AssertTrue(LazyBegin(&sTest, &sRun, LAZY_CODE_END, 2, szStart, szBig, NULL));
	AssertTrue(TestAsm65Run(&sRun, 10000) < 10000);
	AssertLongLongIntHex(0xFFFFFFFF, TestAsm65MPU(&sRun)->GetA());
	AssertLong(2, sRun.pcContext->GetLong((uint32)LazySymbol(&sTest, "R_LazyError")));
	LazyEnd(&sTest, &sRun);

	AssertTrue(LazyBegin(&sTest, &sRun, LAZY_CODE_END, 16, szStart, szBig, NULL));
	AssertTrue(TestAsm65Run(&sRun, 10000) < 10000);
	AssertLong(5, TestAsm65MPU(&sRun)->GetA());
	LazyEnd(&sTest, &sRun);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65Lazy(void)
{
	BeginTests();

	TestAsm65LazyCalls();
	TestAsm65LazyAddresses();
	TestAsm65LazyResident();
	TestAsm65LazyFailures();

	TestStatistics();
}
