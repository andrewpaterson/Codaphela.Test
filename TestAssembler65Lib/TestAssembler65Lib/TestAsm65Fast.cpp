#include <string.h>
#include <stdlib.h>
#include "BaseLib/Chars.h"
#include "MicroprocessorLib/65C64Meta.h"
#include "TestLib/Assert.h"
#include "TestAsm65Context.h"


//////////////////////////////////////////////////////////////////////////
//
// The programs run by C65C64 and CFast65C64 side by side, each with its own memory.  The registers must agree
// after every instruction, memory every TEST_ASM65_FAST_MEMORY_STEPS instructions and at the end.
//
//////////////////////////////////////////////////////////////////////////


#define TEST_ASM65_FAST_MEMORY_STEPS	0x4000


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
static void TestAsm65FastCompare(CChars* psz, const char* szName, uint64 uiSim, uint64 uiFast)
{
	if (uiSim != uiFast)
	{
		psz->Append(" ");
		psz->Append(szName);
		psz->Append(" sim 0x");
		psz->AppendHexHiLo(&uiSim, 8);
		psz->Append(" fast 0x");
		psz->AppendHexHiLo(&uiFast, 8);
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
static void TestAsm65FastCompareMemory(CChars* psz, CAsm65Memory* pcSim, CAsm65Memory* pcFast)
{
	if ((memcmp(pcSim->Byte(0), pcFast->Byte(0), ASM65_MEMORY_LOW_SIZE) != 0) ||
		(memcmp(pcSim->Byte(ASM65_MEMORY_HIGH_BASE), pcFast->Byte(ASM65_MEMORY_HIGH_BASE), ASM65_MEMORY_HIGH_SIZE) != 0))
	{
		psz->Append(" Memory differs");
	}
	TestAsm65FastCompare(psz, "BadAccesses", pcSim->NumBadAccesses(), pcFast->NumBadAccesses());
}


//////////////////////////////////////////////////////////////////////////
//
// Runs pcOutput on both until they stop or uiMaxSteps.  Returns the number of steps.
//
//////////////////////////////////////////////////////////////////////////
static size TestAsm65FastLockstep(CAsm65Output* pcOutput, uint32 uiResetAddress, size uiMaxSteps)
{
	CAsm65Memory*	pcSimMemory;
	CAsm65Memory*	pcFastMemory;
	C65C64Meta		cMeta;
	C65C64*			pcSim;
	CFast65C64		cFast;
	size			uiStep;
	bool			bSim;
	bool			bFast;
	CChars			sz;
	CChars			szWhere;
	uint32			uiC;
	bool			bDone;

	pcSimMemory = (CAsm65Memory*)malloc(sizeof(CAsm65Memory));
	pcSimMemory->Init();
	pcSimMemory->LoadProgram(pcOutput, uiResetAddress);
	pcFastMemory = (CAsm65Memory*)malloc(sizeof(CAsm65Memory));
	pcFastMemory->Init();
	pcFastMemory->LoadProgram(pcOutput, uiResetAddress);

	cMeta.Init(CAsm65Memory::TickHigh, CAsm65Memory::TickLow, pcSimMemory);
	cMeta.TickInstruction();
	pcSim = cMeta.GetMPU();
	pcFastMemory->InitFast(&cFast);
	cFast.Reset();

	sz.Init();
	bDone = false;
	for (uiStep = 0; (uiStep < uiMaxSteps) && !bDone; uiStep++)
	{
		uiC = pcSim->GetProgramCounter();
		bSim = cMeta.TickInstruction();
		bFast = cFast.Step();

		TestAsm65FastCompare(&sz, "A", pcSim->GetA(), cFast.GetA());
		TestAsm65FastCompare(&sz, "B", pcSim->GetB(), cFast.GetB());
		TestAsm65FastCompare(&sz, "X", pcSim->GetX(), cFast.GetX());
		TestAsm65FastCompare(&sz, "Y", pcSim->GetY(), cFast.GetY());
		TestAsm65FastCompare(&sz, "S", pcSim->GetS(), cFast.GetS());
		TestAsm65FastCompare(&sz, "V", pcSim->GetV(), cFast.GetV());
		TestAsm65FastCompare(&sz, "W", pcSim->GetW(), cFast.GetW());
		TestAsm65FastCompare(&sz, "C", pcSim->GetProgramCounter(), cFast.GetProgramCounter());
		TestAsm65FastCompare(&sz, "P", pcSim->GetP(), cFast.GetP());
		TestAsm65FastCompare(&sz, "Running", bSim, bFast);

		bDone = !bSim || !bFast || (uiStep + 1 == uiMaxSteps);
		if (bDone || ((uiStep % TEST_ASM65_FAST_MEMORY_STEPS) == 0))
		{
			TestAsm65FastCompareMemory(&sz, pcSimMemory, pcFastMemory);
		}

		if (!sz.Empty())
		{
			szWhere.Init("Step ");
			szWhere.Append((int)uiStep);
			szWhere.Append(" at 0x");
			szWhere.AppendHexHiLo(&uiC, 4);
			szWhere.Append(":");
			sz.Insert(0, &szWhere);
			szWhere.Kill();
			AssertString("", sz.Text());
			break;
		}
	}
	sz.Kill();

	cFast.Kill();
	cMeta.Kill();
	pcFastMemory->Kill();
	free(pcFastMemory);
	pcSimMemory->Kill();
	free(pcSimMemory);
	return uiStep;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
static size TestAsm65FastFile(const char* szFilename, uint32 uiResetAddress, size uiMaxSteps)
{
	CChars			szSource;
	CAsm65Assembler	cAssembler;
	size			uiSteps;

	szSource.Init();
	AssertTrue(TestAsm65ReadSource(&szSource, szFilename));
	AssertTrue(TestAsm65Assemble(&cAssembler, szSource.Text()));
	uiSteps = TestAsm65FastLockstep(cAssembler.GetOutput(), uiResetAddress, uiMaxSteps);
	cAssembler.Kill();
	szSource.Kill();
	return uiSteps;
}


//////////////////////////////////////////////////////////////////////////
//
// The programs run to their stp, Mandelbrot for its first 300000 instructions.
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65FastPrograms(void)
{
	AssertTrue(TestAsm65FastFile("Strings.asm", 0x1000, 100000) < 100000);
	AssertTrue(TestAsm65FastFile("Sieve.asm", 0x1000, 1000000) < 1000000);
	AssertTrue(TestAsm65FastFile("Relocate.asm", 0x1000, 10000) < 10000);
	AssertTrue(TestAsm65FastFile("Bignum.asm", 0x1000, 10000000) < 10000000);
	AssertSize(300000, TestAsm65FastFile("Mandelbrot.asm", 0x1000, 300000));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65Fast(void)
{
	BeginTests();

	TestAsm65FastPrograms();

	TestStatistics();
}

