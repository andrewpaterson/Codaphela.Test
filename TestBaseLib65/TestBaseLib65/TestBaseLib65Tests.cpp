#include <stdlib.h>
#include <string.h>
#include "BaseLib/TextFile.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/ArrayChars.h"
#include "Assembler65Lib/Asm65Memory.h"
#include "Assembler65Lib/Asm65HostFiles.h"
#include "MicroprocessorLib/Fast65C64.h"
#include "CppParserLib/CPP65Builder.h"
#include "CppParserLib/CPP65Generator.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
// The BaseLib, TestLib and TestBaseLib Visual Studio projects are each added to a CCPP65Builder's CProject (as a
// library whose units are only linked when used) with Libc65, and compiled once with the real source.  Each test
// that TestBaseLib.cpp's main calls is then linked as its own program, TestBaseLib.cpp with only that test's call
// left in its main (the whole of TestBaseLib does not fit below the 65C64's stack), and run on a CFast65C64.  The
// programs read and write a copy of TestBaseLib's directory through the host file device.
//
//////////////////////////////////////////////////////////////////////////


#define TEST_BASELIB65_COMMON			".." _FS_ ".." _FS_ ".." _FS_ "commonlibraries"
#define TEST_BASELIB65_PROJECTS			TEST_BASELIB65_COMMON _FS_
#define TEST_BASELIB65_TESTBASELIB		".." _FS_ ".." _FS_ "TestBaseLib" _FS_ "TestBaseLib"
#define TEST_BASELIB65_DIRECTORY		"Output" _FS_ "TestBaseLib"

//64MB, so the heap is from 0100:0000 (past the devices) to 0400:0000.
#define TEST_BASELIB65_MEMORY_SIZE		0x4000000

//The program ends below the stack (001F:FFFF down): its heap is above 2MB.
#define TEST_BASELIB65_PROGRAM_LIMIT	0x1C0000

#define TEST_BASELIB65_MAX_STEPS		4000000000ULL


//The tests that are not run.
static const char* gaszTestBaseLib65Excluded[] =
{
	//CNativeThread and CConditionVariable have no 65C64 versions (it runs one thread).
	"TestCodabase",
	"TestWriteTransaction",
	"TestReadTransaction",
	"TestTransactionConcurrency",

	//Hundreds of millions to billions of instructions natively, far too many to simulate here.
	"TestNumber",
	"TestFloatPrinter",
	"TestNamedIndexedData",
	"TestIndexTreeAccess",
	"TestFat32",

	//Expects a bigger block, malloc'ed after free, at another address (as MSVC and glibc give it).  Libc65's malloc
	//gives back the block just freed at the top of the heap.
	"TestTemporaryMemory",

	NULL
};


static const char* gaszTestBaseLib65Libc65[] = { "string.cpp", "stdlib.cpp", "ctype.cpp", "time.cpp", "math.cpp", "softfloat.cpp", "softfloat.asm", "new.cpp", "signal.cpp", "stdio.cpp", "host.cpp", NULL };


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
static bool TestBaseLib65IsExcluded(const char* szTest)
{
	size	i;

	for (i = 0; gaszTestBaseLib65Excluded[i]; i++)
	{
		if (strcmp(gaszTestBaseLib65Excluded[i], szTest) == 0)
		{
			return true;
		}
	}
	return false;
}


//////////////////////////////////////////////////////////////////////////
//
// Each test TestBaseLib.cpp's main calls, in order (once each).
//
//////////////////////////////////////////////////////////////////////////
static void TestBaseLib65ListTests(CArrayChars* paszLines, CArrayChars* paszTests)
{
	CChars	szLine;
	size	i;
	bool	bMain;

	bMain = false;
	for (i = 0; i < paszLines->NumElements(); i++)
	{
		szLine.Init(paszLines->GetText(i));
		szLine.StripWhitespace();
		if (szLine.StartsWith("int __cdecl main"))
		{
			bMain = true;
		}
		if (bMain && szLine.StartsWith("Test") && szLine.EndsWith("();"))
		{
			szLine.RemoveFromEnd(3);
			if (!paszTests->Contains(szLine.Text()))
			{
				paszTests->Add(szLine.Text());
			}
		}
		szLine.Kill();
	}
}


//////////////////////////////////////////////////////////////////////////
//
// TestBaseLib.cpp with only szTest's (first) call left in main.  Natively the tests before main calls
// FastFunctionsInit run after earlier tests have initialised the fast functions, so the program does that first.
//
//////////////////////////////////////////////////////////////////////////
static void TestBaseLib65SingleTestMain(CArrayChars* paszLines, const char* szTest, CChars* pszDest)
{
	CChars	szLine;
	CChars	szName;
	size	i;
	bool	bMain;
	bool	bDone;
	bool	bFastFunctions;

	bMain = false;
	bDone = false;
	bFastFunctions = false;
	for (i = 0; i < paszLines->NumElements(); i++)
	{
		szLine.Init(paszLines->GetText(i));
		szLine.StripWhitespace();
		if (szLine.StartsWith("int __cdecl main"))
		{
			bMain = true;
		}
		if (bMain && szLine.Equals("FastFunctionsInit();"))
		{
			bFastFunctions = true;
		}

		if (bMain && szLine.StartsWith("Test") && szLine.EndsWith("();"))
		{
			szName.Init(szLine.Text());
			szName.RemoveFromEnd(3);
			if (!bDone && szName.Equals(szTest))
			{
				if (!bFastFunctions)
				{
					pszDest->Append("\tFastFunctionsInit();\n");
				}
				pszDest->Append(paszLines->GetText(i))->AppendNewLine();
				bDone = true;
			}
			szName.Kill();
		}
		else
		{
			pszDest->Append(paszLines->GetText(i))->AppendNewLine();
		}
		szLine.Kill();
	}
}


//////////////////////////////////////////////////////////////////////////
//
// The number after szKey on the console, or -1.
//
//////////////////////////////////////////////////////////////////////////
static int TestBaseLib65ConsoleNumber(CChars* pszConsole, const char* szKey)
{
	const char*	sz;

	sz = strstr(pszConsole->Text(), szKey);
	return sz ? atoi(sz + strlen(szKey)) : -1;
}


//////////////////////////////////////////////////////////////////////////
//
// A copy of TestBaseLib's directory (without its Output) for the programs to read and write.
//
//////////////////////////////////////////////////////////////////////////
static void TestBaseLib65CopyDirectory(void)
{
	CFileUtil	cFileUtil;
	CArrayChars	aszEntries;
	CChars		szName;
	CChars		szDest;
	size		i;

	cFileUtil.RemoveDir(TEST_BASELIB65_DIRECTORY);
	cFileUtil.MakeDir("Output");
	AssertTrue(cFileUtil.MakeDir(TEST_BASELIB65_DIRECTORY));

	aszEntries.Init();
	cFileUtil.FindAllDirectories(TEST_BASELIB65_TESTBASELIB, &aszEntries, true);
	for (i = 0; i < aszEntries.NumElements(); i++)
	{
		szName.Init(aszEntries.GetText(i));
		cFileUtil.RemovePath(&szName);
		if (!szName.Equals("Output"))
		{
			szDest.Init(TEST_BASELIB65_DIRECTORY);
			cFileUtil.AppendToPath(&szDest, szName.Text());
			AssertTrue(cFileUtil.CopyDir(aszEntries.GetText(i), szDest.Text()));
			szDest.Kill();
		}
		szName.Kill();
	}
	aszEntries.Kill();

	aszEntries.Init();
	cFileUtil.FindAllFiles(TEST_BASELIB65_TESTBASELIB, &aszEntries, false, true);
	for (i = 0; i < aszEntries.NumElements(); i++)
	{
		szName.Init(aszEntries.GetText(i));
		cFileUtil.RemovePath(&szName);
		szDest.Init(TEST_BASELIB65_DIRECTORY);
		cFileUtil.AppendToPath(&szDest, szName.Text());
		AssertTrue(cFileUtil.Copy(aszEntries.GetText(i), szDest.Text()));
		szDest.Kill();
		szName.Kill();
	}
	aszEntries.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// The projects as libraries of the builder's CProject, and Libc65.
//
//////////////////////////////////////////////////////////////////////////
static void TestBaseLib65AddProjects(CCPP65Builder* pcBuilder)
{
	CFileUtil	cFileUtil;
	CChars		szPath;
	size		i;

	szPath.Init(TEST_BASELIB65_PROJECTS "Libc65");
	cFileUtil.FullPath(&szPath);
	pcBuilder->AddIncludeDirectory(szPath.Text(), false, true);
	szPath.Kill();
	szPath.Init(TEST_BASELIB65_COMMON);
	cFileUtil.FullPath(&szPath);
	pcBuilder->AddIncludeDirectory(szPath.Text(), true, false);
	szPath.Kill();
	szPath.Init(TEST_BASELIB65_PROJECTS "BaseLib");
	cFileUtil.FullPath(&szPath);
	pcBuilder->AddIncludeDirectory(szPath.Text(), false, false);
	szPath.Kill();
	szPath.Init(TEST_BASELIB65_TESTBASELIB);
	cFileUtil.FullPath(&szPath);
	pcBuilder->AddIncludeDirectory(szPath.Text(), false, false);
	szPath.Kill();

	AssertTrue(pcBuilder->AddStartUp());

	//TestBaseLib.cpp's main is replaced for each test.
	AssertTrue(pcBuilder->AddVisualStudioProject("TestBaseLib", TEST_BASELIB65_TESTBASELIB _FS_ "TestBaseLib.vcxproj", true, "TestBaseLib.cpp"));
	AssertTrue(pcBuilder->AddVisualStudioProject("TestLib", TEST_BASELIB65_PROJECTS "TestLib" _FS_ "TestLib.vcxproj", true));
	AssertTrue(pcBuilder->AddVisualStudioProject("BaseLib", TEST_BASELIB65_PROJECTS "BaseLib" _FS_ "BaseLib.vcxproj", true));

	szPath.Init(TEST_BASELIB65_PROJECTS "Libc65");
	cFileUtil.FullPath(&szPath);
	for (i = 0; gaszTestBaseLib65Libc65[i]; i++)
	{
		pcBuilder->AddUnit("Libc65", szPath.Text(), gaszTestBaseLib65Libc65[i], true);
	}
	szPath.Kill();
	pcBuilder->SetLimit(TEST_BASELIB65_PROGRAM_LIMIT);
}


//////////////////////////////////////////////////////////////////////////
//
// Runs the linked program.  pszConsole gets what it printed.  Returns true if main returned.
//
//////////////////////////////////////////////////////////////////////////
static bool TestBaseLib65Run(CCPP65Builder* pcBuilder, CChars* pszConsole)
{
	CAsm65Memory*		pcMemory;
	CAsm65HostFiles		cHostFiles;
	CFast65C64			cMPU;
	uint64				uiSteps;
	bool				bReturned;

	pcMemory = (CAsm65Memory*)malloc(sizeof(CAsm65Memory));
	pcMemory->Init(TEST_BASELIB65_MEMORY_SIZE);
	pcMemory->LoadProgram(pcBuilder->GetOutput(), CPP65_PROGRAM_ADDRESS);
	pcMemory->SetConsole(pszConsole);
	cHostFiles.Init();
	cHostFiles.SetDirectory(TEST_BASELIB65_DIRECTORY);
	pcMemory->SetHostFiles(&cHostFiles);
	pcMemory->InitFast(&cMPU);
	cMPU.Reset();

	//Run takes a size, which is 32 bits in a 32 bit build.
	for (uiSteps = 0; (uiSteps < TEST_BASELIB65_MAX_STEPS) && !cMPU.IsStopped(); uiSteps += 1000000)
	{
		cMPU.Run(1000000);
	}
	bReturned = cMPU.IsStopped() && (cMPU.GetS() == CPP65_STACK_TOP);

	cMPU.Kill();
	cHostFiles.Kill();
	pcMemory->Kill();
	free(pcMemory);
	return bReturned;
}


//////////////////////////////////////////////////////////////////////////
//
// Every test TestBaseLib.cpp's main calls (but the excluded ones) runs to the end without a failure.
//
//////////////////////////////////////////////////////////////////////////
void TestBaseLib65RunTests(void)
{
	CCPP65Builder	cBuilder;
	CTextFile		cFile;
	CArrayChars		aszLines;
	CArrayChars		aszTests;
	CChars			szText;
	CChars			szMain;
	CChars			szConsole;
	CChars			szExpected;
	CChars			szActual;
	size			i;
	int				iRun;
	int				iFailed;
	int				iTotalRun;
	size			uiPrograms;
	bool			bReturned;
	bool			bLinked;

	TestBaseLib65CopyDirectory();

	cBuilder.Init();
	TestBaseLib65AddProjects(&cBuilder);
	AssertTrue(cBuilder.Compile());
	AssertString("", cBuilder.GetErrors());

	cFile.Init();
	AssertTrue(cFile.Read(TEST_BASELIB65_TESTBASELIB _FS_ "TestBaseLib.cpp"));
	cFile.PassifyNewlines();
	aszLines.Init();
	szText.Init(cFile.Text());
	szText.SplitLines(&aszLines);
	szText.Kill();
	cFile.Kill();
	aszTests.Init();
	TestBaseLib65ListTests(&aszLines, &aszTests);
	AssertTrue(aszTests.NumElements() > 100);

	iTotalRun = 0;
	uiPrograms = 0;
	for (i = 0; i < aszTests.NumElements(); i++)
	{
		if (TestBaseLib65IsExcluded(aszTests.GetText(i)))
		{
			continue;
		}

		szMain.Init();
		TestBaseLib65SingleTestMain(&aszLines, aszTests.GetText(i), &szMain);
		bLinked = cBuilder.LinkWith("TestBaseLib.cpp", szMain.Text());
		szMain.Kill();

		//The test's name, and how it went if it did not pass.
		szExpected.Init(aszTests.GetText(i));
		szActual.Init(aszTests.GetText(i));
		szConsole.Init();
		if (!bLinked)
		{
			szActual.Append(" did not link: ");
			szActual.Append(cBuilder.GetErrors());
		}
		else
		{
			uiPrograms++;
			bReturned = TestBaseLib65Run(&cBuilder, &szConsole);
			iRun = TestBaseLib65ConsoleNumber(&szConsole, "Total Tests Run: ");
			iFailed = TestBaseLib65ConsoleNumber(&szConsole, "Total Failed: ");
			if (!bReturned || (iFailed > 0))
			{
				szActual.Append(bReturned ? " failed:\n" : " did not finish:\n");
				szActual.Append(szConsole);
			}
			iTotalRun += (iRun > 0) ? iRun : 0;
		}
		AssertString(szExpected.Text(), szActual.Text());
		szConsole.Kill();
		szActual.Kill();
		szExpected.Kill();
	}
	AssertTrue(uiPrograms > 100);
	AssertTrue(iTotalRun > 30000);

	aszTests.Kill();
	aszLines.Kill();
	cBuilder.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestBaseLib65Tests(void)
{
	BeginTests();

	TestBaseLib65RunTests();

	TestStatistics();
}

