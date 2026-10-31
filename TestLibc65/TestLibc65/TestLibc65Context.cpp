#include <stdlib.h>
#include <string.h>
#include "BaseLib/PointerFunctions.h"
#include "BaseLib/ConstructorCall.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/ArrayChars.h"
#include "CppParserLib/CPP65Generator.h"
#include "CppParserLib/CPP65Builder.h"
#include "TestLib/Assert.h"
#include "TestLibc65Context.h"


#define TEST_LIBC65_DIRECTORY		".." _FS_ ".." _FS_ ".." _FS_ "commonlibraries" _FS_ "Libc65"
#define TEST_LIBC65_LIBRARIES		".." _FS_ ".." _FS_ ".." _FS_ "commonlibraries"


//The W65C816 runs more instructions for the same C++ (a 16 bit int, soft float in C++ rather than softfloat.asm):
//its runs may take this many times the 65C64's instructions.
#define TEST_LIBC65_816_INSTRUCTIONS	400


ECPPTarget	geTestLibc65Target = CPPT_65C64;


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
// Whether szUnit is 65C64 assembly (.asm).
//
//////////////////////////////////////////////////////////////////////////
static bool TestLibc65IsAssembly(const char* szUnit)
{
	const char*	szDot;

	szDot = strrchr(szUnit, '.');
	return szDot && (strcmp(szDot, ".asm") == 0);
}


//////////////////////////////////////////////////////////////////////////
//
// The W65C816's unit for a 65C64 assembly unit: X<szSuffix> (X816.asm or X816_16.asm) for X.asm when there is
// one (in szDirectory), else empty.
//
//////////////////////////////////////////////////////////////////////////
static void TestLibc65Unit816(const char* szDirectory, const char* szUnit, const char* szSuffix, CChars* pszUnit)
{
	CChars		szPath;
	CFileUtil	cFileUtil;

	pszUnit->Init();
	pszUnit->Append(szUnit, (size)(strrchr(szUnit, '.') - szUnit));
	pszUnit->Append(szSuffix);
	szPath.Init(szDirectory);
	szPath.Append(_FS_);
	szPath.Append(*pszUnit);
	if (!cFileUtil.Exists(szPath.Text()))
	{
		pszUnit->Kill();
		pszUnit->Init();
	}
	szPath.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// Compiles szSource and the Libc65 units (file names in commonlibraries/Libc65, NULL terminated) and links
// the start up and szSource with the Libc65 units as a library (a unit is linked when something needs it).
// BaseLib's TrueMallocator.cpp, which malloc uses, is in the library too.
// Loads the program at reset.  On the W65C816 a unit in 65C64 assembly (X.asm) is its W65C816 assembly (X816.asm,
// and X816_16.asm) when there is some, else left out: their .cpp units have the other functions for it.  The labels in szStubs (space separated, sorted) must be exactly the ones
// used but defined by no linked unit; the linker makes each a stp so a call to one stops the program.
//
//////////////////////////////////////////////////////////////////////////
bool TestLibc65Begin(STestLibc65Run* psRun, const char** aszUnits, const char* szStubs, const char* szSource)
{
	CCPP65Builder	cBuilder;
	CChars			szLibc65;
	CChars			szLibraries;
	CChars			szBaseLib;
	CChars			szMissing;
	CChars			szUnit;
	size			i;
	size			j;
	bool			bResult;
	const char*		aszSuffixes[] = { "816.asm", "816_16.asm", NULL };

	TestLibc65FullPath(&szLibc65, TEST_LIBC65_DIRECTORY);
	TestLibc65FullPath(&szLibraries, TEST_LIBC65_LIBRARIES);
	cBuilder.Init();
	cBuilder.SetTarget(geTestLibc65Target);
	cBuilder.AddIncludeDirectory(szLibc65.Text(), false, true);
	cBuilder.AddIncludeDirectory(szLibraries.Text(), true, false);

	bResult = cBuilder.AddStartUp();
	bResult &= cBuilder.AddSource("Test.cpp", szSource);
	for (i = 0; aszUnits[i]; i++)
	{
		if ((geTestLibc65Target == CPPT_65C64) || !TestLibc65IsAssembly(aszUnits[i]))
		{
			cBuilder.AddUnit("Libc65", szLibc65.Text(), aszUnits[i], true);
		}
		else
		{
			//The W65C816's own assembly for the unit, and with 16 bit counts, if it has some.
			for (j = 0; aszSuffixes[j]; j++)
			{
				TestLibc65Unit816(szLibc65.Text(), aszUnits[i], aszSuffixes[j], &szUnit);
				if (!szUnit.Empty())
				{
					cBuilder.AddUnit("Libc65", szLibc65.Text(), szUnit.Text(), true);
				}
				szUnit.Kill();
			}
		}
	}
	cBuilder.AddMathTables(szLibc65.Text());
	TestLibc65FullPath(&szBaseLib, TEST_LIBC65_LIBRARIES _FS_ "BaseLib");
	cBuilder.AddUnit("BaseLib", szBaseLib.Text(), "TrueMallocator.cpp", true);
	szBaseLib.Kill();
	bResult &= cBuilder.Link();
	AssertString("", cBuilder.GetErrors());

	//What is used but written by no linked unit.
	szMissing.Init();
	cBuilder.GetMissingNames(&szMissing);
	AssertString(szStubs, szMissing.Text());

	psRun->pcMemory = NULL;
	if (bResult)
	{
		psRun->pcMemory = NewMalloc<CAsm65Memory>();
		psRun->pcMemory->Init();
		if (geTestLibc65Target == CPPT_W65C816)
		{
			psRun->pcMemory->Load(cBuilder.GetOutput());
			psRun->pcMemory->InitFast65816(&psRun->cMPU816);
			psRun->cMPU816.Reset();
		}
		else
		{
			psRun->pcMemory->LoadProgram(cBuilder.GetOutput(), CPP65_PROGRAM_ADDRESS);
			psRun->pcMemory->InitFast65C64(&psRun->cMPU);
			psRun->cMPU.Reset();
		}
	}

	szMissing.Kill();
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
		if (geTestLibc65Target == CPPT_W65C816)
		{
			return psRun->cMPU816.GetS() == GetCPPTarget(CPPT_W65C816)->uiStackTop;
		}
		return psRun->cMPU.GetS() == CPP65_STACK_TOP;
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
	if (geTestLibc65Target == CPPT_W65C816)
	{
		uiMaxInstructions = (uiMaxInstructions > SIZE_MAX / TEST_LIBC65_816_INSTRUCTIONS) ? SIZE_MAX : uiMaxInstructions * TEST_LIBC65_816_INSTRUCTIONS;
		psRun->cMPU816.Run(uiMaxInstructions);
		return psRun->cMPU816.IsStopped();
	}
	psRun->cMPU.Run(uiMaxInstructions);
	return psRun->cMPU.IsStopped();
}


//////////////////////////////////////////////////////////////////////////
//
// What main returned.
//
//////////////////////////////////////////////////////////////////////////
int32 TestLibc65Return(STestLibc65Run* psRun)
{
	if (geTestLibc65Target == CPPT_W65C816)
	{
		return (int16)psRun->cMPU816.GetC();
	}
	return (int32)psRun->cMPU.GetA();
}


//////////////////////////////////////////////////////////////////////////
//
// The long at index uiIndex of the test's results (from TEST_LIBC65_RESULTS).
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
		if (geTestLibc65Target == CPPT_W65C816)
		{
			psRun->cMPU816.Kill();
		}
		else
		{
			psRun->cMPU.Kill();
		}
		SafeKill(psRun->pcMemory);
	}
}

