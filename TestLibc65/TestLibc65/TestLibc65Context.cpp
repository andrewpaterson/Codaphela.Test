#include <stdlib.h>
#include "BaseLib/FileUtil.h"
#include "BaseLib/ArrayChars.h"
#include "CppParserLib/CPP65Generator.h"
#include "CppParserLib/CPP65Builder.h"
#include "TestLib/Assert.h"
#include "TestLibc65Context.h"


#define TEST_LIBC65_DIRECTORY		".." _FS_ ".." _FS_ ".." _FS_ "commonlibraries" _FS_ "Libc65"
#define TEST_LIBC65_LIBRARIES		".." _FS_ ".." _FS_ ".." _FS_ "commonlibraries"


//////////////////////////////////////////////////////////////////////////
//
// The full path of szRelative (to this test's directory).
//
//////////////////////////////////////////////////////////////////////////
static void TestLibc65FullPath(CChars* pszDirectory, const char* szRelative)
{
	CFileUtil	cFileUtil;

	pszDirectory->Init(szRelative);
	cFileUtil.FullPath(pszDirectory);
}


//////////////////////////////////////////////////////////////////////////
//
// Compiles szSource and the Libc65 units (file names in commonlibraries/Libc65, NULL terminated) and links
// the start up and szSource with the Libc65 units as a library (a unit is linked when something needs it).
// Loads the program at reset.  The labels in szStubs (space separated, sorted) must be exactly the ones
// used but defined by no linked unit; the linker makes each a stp so a call to one stops the program.
//
//////////////////////////////////////////////////////////////////////////
bool TestLibc65Begin(STestLibc65Run* psRun, const char** aszUnits, const char* szStubs, const char* szSource)
{
	CCPP65Builder	cBuilder;
	CChars			szLibc65;
	CChars			szLibraries;
	CChars			szMissing;
	CArrayChars		aszMissing;
	size			i;
	bool			bResult;

	TestLibc65FullPath(&szLibc65, TEST_LIBC65_DIRECTORY);
	TestLibc65FullPath(&szLibraries, TEST_LIBC65_LIBRARIES);
	cBuilder.Init();
	cBuilder.AddIncludeDirectory(szLibc65.Text(), false, true);
	cBuilder.AddIncludeDirectory(szLibraries.Text(), true, false);

	bResult = cBuilder.AddStartUp();
	bResult &= cBuilder.AddSource("Test.cpp", szSource);
	for (i = 0; aszUnits[i]; i++)
	{
		cBuilder.AddUnit("Libc65", szLibc65.Text(), aszUnits[i], true);
	}
	bResult &= cBuilder.Link();
	AssertString("", cBuilder.GetErrors());

	//What is used but written by no linked unit.
	aszMissing.Init();
	for (i = 0; i < cBuilder.NumMissing(); i++)
	{
		aszMissing.Add(cBuilder.GetMissing(i));
	}
	aszMissing.QuickSort(true);
	szMissing.Init();
	for (i = 0; i < aszMissing.NumElements(); i++)
	{
		if (!szMissing.Empty())
		{
			szMissing.Append(' ');
		}
		szMissing.Append(aszMissing.GetText(i));
	}
	AssertString(szStubs, szMissing.Text());

	psRun->pcMemory = NULL;
	if (bResult)
	{
		psRun->pcMemory = (CAsm65Memory*)malloc(sizeof(CAsm65Memory));
		psRun->pcMemory->Init();
		psRun->pcMemory->SetLong(VECTOR_65C64_BASE + 4 * VECTOR_65C64_RESET, CPP65_PROGRAM_ADDRESS);
		psRun->pcMemory->Load(cBuilder.GetOutput());
		psRun->cMeta.Init(CAsm65Memory::TickHigh, CAsm65Memory::TickLow, psRun->pcMemory);
		psRun->cMeta.TickInstruction();
	}

	szMissing.Kill();
	aszMissing.Kill();
	cBuilder.Kill();
	szLibraries.Kill();
	szLibc65.Kill();
	return bResult;
}


//////////////////////////////////////////////////////////////////////////
//
// Runs until the processor stops.  Returns false if it did not stop within uiMaxInstructions or main did
// not return with the stack where it started.
//
//////////////////////////////////////////////////////////////////////////
bool TestLibc65Run(STestLibc65Run* psRun, size uiMaxInstructions)
{
	if (TestLibc65RunToStop(psRun, uiMaxInstructions))
	{
		return psRun->cMeta.GetMPU()->GetS() == CPP65_STACK_TOP;
	}
	return false;
}


//////////////////////////////////////////////////////////////////////////
//
// Runs until the processor stops, wherever the stack is (exit stops the program from inside a call).
// Returns false if it did not stop within uiMaxInstructions.
//
//////////////////////////////////////////////////////////////////////////
bool TestLibc65RunToStop(STestLibc65Run* psRun, size uiMaxInstructions)
{
	size	i;

	for (i = 0; i < uiMaxInstructions; i++)
	{
		if (!psRun->cMeta.TickInstruction())
		{
			return true;
		}
	}
	return false;
}


//////////////////////////////////////////////////////////////////////////
//
// What main returned.
//
//////////////////////////////////////////////////////////////////////////
int32 TestLibc65Return(STestLibc65Run* psRun)
{
	return (int32)psRun->cMeta.GetMPU()->GetA();
}


//////////////////////////////////////////////////////////////////////////
//
// The int at index uiIndex of the test's results (from TEST_LIBC65_RESULTS).
//
//////////////////////////////////////////////////////////////////////////
int32 TestLibc65Result(STestLibc65Run* psRun, size uiIndex)
{
	return (int32)psRun->pcMemory->GetLong(TEST_LIBC65_RESULTS + 4 * (uint32)uiIndex);
}


//////////////////////////////////////////////////////////////////////////
//
// The test's byte results, uiOffset bytes from TEST_LIBC65_BYTES.
//
//////////////////////////////////////////////////////////////////////////
char* TestLibc65Bytes(STestLibc65Run* psRun, uint32 uiOffset)
{
	return (char*)psRun->pcMemory->Byte(TEST_LIBC65_BYTES + uiOffset);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestLibc65End(STestLibc65Run* psRun)
{
	if (psRun->pcMemory)
	{
		AssertSize(0, psRun->pcMemory->NumBadAccesses());
		psRun->cMeta.Kill();
		free(psRun->pcMemory);
		psRun->pcMemory = NULL;
	}
}

