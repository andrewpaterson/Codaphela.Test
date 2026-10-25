#include <stdlib.h>
#include <string.h>
#include "BaseLib/TextFile.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/ArrayChars.h"
#include "BaseLib/StringHelper.h"
#include "BaseLib/ConstructorCall.h"
#include "BaseLib/PointerFunctions.h"
#include "Assembler65Lib/Asm65Memory.h"
#include "Assembler65Lib/Asm65HostFiles.h"
#include "MicroprocessorLib/Fast65C64.h"
#include "MicroprocessorLib/Fast65C816.h"
#include "CppParserLib/CPP65Builder.h"
#include "CppParserLib/CPP65Generator.h"
#include "TestLib/Assert.h"
#include "TestProject65.h"


//////////////////////////////////////////////////////////////////////////
//
// A test project (TestBaseLib, TestStandardLib) and the commonlibraries projects it uses are each added to a
// CCPP65Builder's CProject (as a library whose units are only linked when used) with Libc65, and compiled once with
// the real source.  Each test that the test project's main calls is then linked as its own program, the main's
// file with only that test's call left in its main (a whole test project does not fit below the 65C64's stack), and
// run on a CFast65C64.  The programs read and write a copy of the test project's directory through the host file
// device.  For the W65C816 (geTestProject65Target) the units in 65C64 assembly are left out, the memory is 16MB (24
// bit addresses) and the programs run on a CFast65C816.
//
//////////////////////////////////////////////////////////////////////////


#define TEST_PROJECT65_COMMON			".." _FS_ ".." _FS_ ".." _FS_ "commonlibraries"
#define TEST_PROJECT65_PROJECTS			TEST_PROJECT65_COMMON _FS_
#define TEST_PROJECT65_TESTS			".." _FS_ ".." _FS_

//64MB, so the heap is from 0100:0000 (past the devices) to 0400:0000.  The W65C816's 16MB has it from 0020:0000 to
//the devices.
#define TEST_PROJECT65_MEMORY_SIZE		0x4000000
#define TEST_PROJECT816_MEMORY_SIZE		0x1000000

//The program ends below the stack (001F:FFFF down): its heap is above 2MB.
#define TEST_PROJECT65_PROGRAM_LIMIT	0x1C0000

#define TEST_PROJECT65_MAX_STEPS		4000000000ULL


ECPPTarget	geTestProject65Target = CPPT_65C64;


static const char* gaszTestProject65Libc65[] = { "string.cpp", "string.asm", "stdlib.cpp", "ctype.cpp", "time.cpp", "math.cpp", "softfloat.cpp", "softfloat.asm", "new.cpp", "signal.cpp", "stdio.cpp", "host.cpp", NULL };


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
static bool TestProject65IsExcluded(STestProject65* psProject, const char* szTest)
{
	size	i;

	for (i = 0; psProject->aszExcluded[i]; i++)
	{
		if (StringCompare(psProject->aszExcluded[i], szTest) == 0)
		{
			return true;
		}
	}
	return false;
}


//////////////////////////////////////////////////////////////////////////
//
// Whether szLine (in main) is a call to a test, Test...();.  pszName gets the test's name.
//
//////////////////////////////////////////////////////////////////////////
static bool TestProject65TestCall(const char* szLine, CChars* pszName)
{
	pszName->Init(szLine);
	pszName->StripWhitespace();
	if (pszName->StartsWith("Test") && pszName->EndsWith("();"))
	{
		pszName->RemoveFromEnd(3);
		return true;
	}
	pszName->Kill();
	return false;
}


//////////////////////////////////////////////////////////////////////////
//
// Whether szLine starts main.
//
//////////////////////////////////////////////////////////////////////////
static bool TestProject65MainStart(const char* szLine)
{
	CChars	szStripped;
	bool	bMain;

	szStripped.Init(szLine);
	szStripped.StripWhitespace();
	bMain = szStripped.StartsWith("int __cdecl main");
	szStripped.Kill();
	return bMain;
}


//////////////////////////////////////////////////////////////////////////
//
// Each test the main calls, in order (once each).
//
//////////////////////////////////////////////////////////////////////////
static void TestProject65ListTests(CArrayChars* paszLines, CArrayChars* paszTests)
{
	CChars	szName;
	size	i;
	bool	bMain;

	bMain = false;
	for (i = 0; i < paszLines->NumElements(); i++)
	{
		bMain |= TestProject65MainStart(paszLines->GetText(i));
		if (bMain && TestProject65TestCall(paszLines->GetText(i), &szName))
		{
			if (!paszTests->Contains(szName.Text()))
			{
				paszTests->Add(szName.Text());
			}
			szName.Kill();
		}
	}
}


//////////////////////////////////////////////////////////////////////////
//
// The main's file with only szTest's (first) call left in main.  Natively the tests before main calls
// FastFunctionsInit run after earlier tests have initialised the fast functions, so the program does that first.
//
//////////////////////////////////////////////////////////////////////////
static void TestProject65SingleTestMain(CArrayChars* paszLines, const char* szTest, CChars* pszDest)
{
	CChars	szName;
	char*	szLine;
	size	i;
	bool	bMain;
	bool	bDone;
	bool	bFastFunctions;

	bMain = false;
	bDone = false;
	bFastFunctions = false;
	for (i = 0; i < paszLines->NumElements(); i++)
	{
		szLine = paszLines->GetText(i);
		bMain |= TestProject65MainStart(szLine);
		bFastFunctions |= bMain && (strstr(szLine, "FastFunctionsInit();") != NULL);

		if (bMain && TestProject65TestCall(szLine, &szName))
		{
			if (!bDone && szName.Equals(szTest))
			{
				if (!bFastFunctions)
				{
					pszDest->Append("\tFastFunctionsInit();\n");
				}
				pszDest->Append(szLine)->AppendNewLine();
				bDone = true;
			}
			szName.Kill();
		}
		else
		{
			pszDest->Append(szLine)->AppendNewLine();
		}
	}
}


//////////////////////////////////////////////////////////////////////////
//
// The number after szKey on the console, or -1.
//
//////////////////////////////////////////////////////////////////////////
static int TestProject65ConsoleNumber(CChars* pszConsole, const char* szKey)
{
	const char*	sz;

	sz = strstr(pszConsole->Text(), szKey);
	return sz ? atoi(sz + strlen(szKey)) : -1;
}


//////////////////////////////////////////////////////////////////////////
//
// The test project's directory, ../../<name>/<name>.
//
//////////////////////////////////////////////////////////////////////////
static void TestProject65TestDirectory(STestProject65* psProject, CChars* pszDest)
{
	pszDest->Init(TEST_PROJECT65_TESTS);
	pszDest->Append(psProject->szTestProject);
	pszDest->Append(_FS_);
	pszDest->Append(psProject->szTestProject);
}


//////////////////////////////////////////////////////////////////////////
//
// The directory the programs read and write, Output/<name>.
//
//////////////////////////////////////////////////////////////////////////
static void TestProject65OutputDirectory(STestProject65* psProject, CChars* pszDest)
{
	pszDest->Init("Output" _FS_);
	pszDest->Append(psProject->szTestProject);
}


//////////////////////////////////////////////////////////////////////////
//
// A copy of the test project's directory (without its Output) for the programs to read and write.
//
//////////////////////////////////////////////////////////////////////////
static void TestProject65CopyDirectory(STestProject65* psProject)
{
	CFileUtil	cFileUtil;
	CArrayChars	aszEntries;
	CChars		szName;
	CChars		szDest;
	CChars		szTestDirectory;
	CChars		szOutput;
	size		i;

	TestProject65TestDirectory(psProject, &szTestDirectory);
	TestProject65OutputDirectory(psProject, &szOutput);
	cFileUtil.RemoveDir(szOutput.Text());
	cFileUtil.MakeDir("Output");
	AssertTrue(cFileUtil.MakeDir(szOutput.Text()));

	aszEntries.Init();
	cFileUtil.FindAllDirectories(szTestDirectory.Text(), &aszEntries, true);
	for (i = 0; i < aszEntries.NumElements(); i++)
	{
		szName.Init(aszEntries.GetText(i));
		cFileUtil.RemovePath(&szName);
		if (!szName.Equals("Output"))
		{
			szDest.Init(szOutput);
			cFileUtil.AppendToPath(&szDest, szName.Text());
			AssertTrue(cFileUtil.CopyDir(aszEntries.GetText(i), szDest.Text()));
			szDest.Kill();
		}
		szName.Kill();
	}
	aszEntries.Kill();

	aszEntries.Init();
	cFileUtil.FindAllFiles(szTestDirectory.Text(), &aszEntries, false, true);
	for (i = 0; i < aszEntries.NumElements(); i++)
	{
		szName.Init(aszEntries.GetText(i));
		cFileUtil.RemovePath(&szName);
		szDest.Init(szOutput);
		cFileUtil.AppendToPath(&szDest, szName.Text());
		AssertTrue(cFileUtil.Copy(aszEntries.GetText(i), szDest.Text()));
		szDest.Kill();
		szName.Kill();
	}
	aszEntries.Kill();
	szOutput.Kill();
	szTestDirectory.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// The projects as libraries of the builder's CProject, and Libc65.
//
//////////////////////////////////////////////////////////////////////////
static void TestProject65AddProjects(STestProject65* psProject, CCPP65Builder* pcBuilder)
{
	CFileUtil	cFileUtil;
	CChars		szPath;
	CChars		szTestDirectory;
	CChars		szMain;
	size		i;

	TestProject65TestDirectory(psProject, &szTestDirectory);
	szPath.Init(TEST_PROJECT65_PROJECTS "Libc65");
	cFileUtil.FullPath(&szPath);
	pcBuilder->AddIncludeDirectory(szPath.Text(), false, true);
	szPath.Kill();
	szPath.Init(TEST_PROJECT65_COMMON);
	cFileUtil.FullPath(&szPath);
	pcBuilder->AddIncludeDirectory(szPath.Text(), true, false);
	szPath.Kill();
	for (i = 0; psProject->aszLibraries[i]; i++)
	{
		szPath.Init(TEST_PROJECT65_PROJECTS);
		szPath.Append(psProject->aszLibraries[i]);
		cFileUtil.FullPath(&szPath);
		pcBuilder->AddIncludeDirectory(szPath.Text(), false, false);
		szPath.Kill();
	}
	szPath.Init(szTestDirectory);
	cFileUtil.FullPath(&szPath);
	pcBuilder->AddIncludeDirectory(szPath.Text(), false, false);
	szPath.Kill();

	AssertTrue(pcBuilder->AddStartUp());

	//The main's file is replaced for each test.
	szPath.Init(szTestDirectory);
	szPath.Append(_FS_);
	szPath.Append(psProject->szTestProject);
	szPath.Append(".vcxproj");
	szMain.Init(psProject->szTestProject);
	szMain.Append(".cpp");
	AssertTrue(pcBuilder->AddVisualStudioProject(psProject->szTestProject, szPath.Text(), true, szMain.Text()));
	szMain.Kill();
	szPath.Kill();
	for (i = 0; psProject->aszLibraries[i]; i++)
	{
		szPath.Init(TEST_PROJECT65_PROJECTS);
		szPath.Append(psProject->aszLibraries[i]);
		szPath.Append(_FS_);
		szPath.Append(psProject->aszLibraries[i]);
		szPath.Append(".vcxproj");
		AssertTrue(pcBuilder->AddVisualStudioProject(psProject->aszLibraries[i], szPath.Text(), true));
		szPath.Kill();
	}

	szPath.Init(TEST_PROJECT65_PROJECTS "Libc65");
	cFileUtil.FullPath(&szPath);
	for (i = 0; gaszTestProject65Libc65[i]; i++)
	{
		if ((geTestProject65Target == CPPT_65C64) || (strcmp(strrchr(gaszTestProject65Libc65[i], '.'), ".asm") != 0))
		{
			pcBuilder->AddUnit("Libc65", szPath.Text(), gaszTestProject65Libc65[i], true);
		}
	}
	szPath.Kill();
	pcBuilder->SetLimit(TEST_PROJECT65_PROGRAM_LIMIT);
	szTestDirectory.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// Runs the linked program.  pszConsole gets what it printed.  Returns true if main returned.
//
//////////////////////////////////////////////////////////////////////////
static bool TestProject65Run(STestProject65* psProject, CCPP65Builder* pcBuilder, CChars* pszConsole)
{
	CAsm65Memory*		pcMemory;
	CAsm65HostFiles		cHostFiles;
	CFast65C64			cMPU;
	CFast65C816			cMPU816;
	CChars				szOutput;
	uint64				uiSteps;
	bool				bReturned;
	bool				bW65C816;

	bW65C816 = geTestProject65Target == CPPT_W65C816;
	pcMemory = NewMalloc<CAsm65Memory>();
	if (bW65C816)
	{
		pcMemory->Init(TEST_PROJECT816_MEMORY_SIZE);
		pcMemory->Load(pcBuilder->GetOutput());
	}
	else
	{
		pcMemory->Init(TEST_PROJECT65_MEMORY_SIZE);
		pcMemory->LoadProgram(pcBuilder->GetOutput(), CPP65_PROGRAM_ADDRESS);
	}
	pcMemory->SetConsole(pszConsole);
	cHostFiles.Init();
	TestProject65OutputDirectory(psProject, &szOutput);
	cHostFiles.SetDirectory(szOutput.Text());
	szOutput.Kill();
	pcMemory->SetHostFiles(&cHostFiles);

	//Run takes a size, which is 32 bits in a 32 bit build.
	if (bW65C816)
	{
		pcMemory->InitFast816(&cMPU816);
		cMPU816.Reset();
		for (uiSteps = 0; (uiSteps < TEST_PROJECT65_MAX_STEPS) && !cMPU816.IsStopped(); uiSteps += 1000000)
		{
			cMPU816.Run(1000000);
		}
		bReturned = cMPU816.IsStopped() && (cMPU816.GetS() == GetCPPTarget(CPPT_W65C816)->uiStackTop);
		cMPU816.Kill();
	}
	else
	{
		pcMemory->InitFast(&cMPU);
		cMPU.Reset();
		for (uiSteps = 0; (uiSteps < TEST_PROJECT65_MAX_STEPS) && !cMPU.IsStopped(); uiSteps += 1000000)
		{
			cMPU.Run(1000000);
		}
		bReturned = cMPU.IsStopped() && (cMPU.GetS() == CPP65_STACK_TOP);
		cMPU.Kill();
	}

	cHostFiles.Kill();
	SafeKill(pcMemory);
	return bReturned;
}


//////////////////////////////////////////////////////////////////////////
//
// Every test the test project's main calls (but the excluded ones) runs to the end without a failure.
//
//////////////////////////////////////////////////////////////////////////
void TestProject65RunTests(STestProject65* psProject)
{
	CCPP65Builder	cBuilder;
	CTextFile		cFile;
	CArrayChars		aszLines;
	CArrayChars		aszTests;
	CChars			szText;
	CChars			szMain;
	CChars			szMainFile;
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
	bool			bCompiled;

	TestProject65CopyDirectory(psProject);

	cBuilder.Init();
	cBuilder.SetTarget(geTestProject65Target);
	TestProject65AddProjects(psProject, &cBuilder);
	bCompiled = cBuilder.Compile();
	AssertString("", cBuilder.GetErrors());
	AssertTrue(bCompiled);

	TestProject65TestDirectory(psProject, &szMainFile);
	szMainFile.Append(_FS_);
	szMainFile.Append(psProject->szTestProject);
	szMainFile.Append(".cpp");
	cFile.Init();
	AssertTrue(cFile.Read(szMainFile.Text()));
	cFile.PassifyNewlines();
	aszLines.Init();
	szText.Init(cFile.Text());
	szText.SplitLines(&aszLines);
	szText.Kill();
	cFile.Kill();
	aszTests.Init();
	TestProject65ListTests(&aszLines, &aszTests);
	AssertTrue(aszTests.NumElements() >= psProject->uiMinPrograms);

	//LinkWith's name is the main's file's name.
	szMainFile.Init(psProject->szTestProject);
	szMainFile.Append(".cpp");

	iTotalRun = 0;
	uiPrograms = 0;
	for (i = 0; i < aszTests.NumElements(); i++)
	{
		if (TestProject65IsExcluded(psProject, aszTests.GetText(i)))
		{
			continue;
		}

		szMain.Init();
		TestProject65SingleTestMain(&aszLines, aszTests.GetText(i), &szMain);
		bLinked = cBuilder.LinkWith(szMainFile.Text(), szMain.Text());
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
			bReturned = TestProject65Run(psProject, &cBuilder, &szConsole);
			iRun = TestProject65ConsoleNumber(&szConsole, "Total Tests Run: ");
			iFailed = TestProject65ConsoleNumber(&szConsole, "Total Failed: ");
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
	AssertTrue(uiPrograms >= psProject->uiMinPrograms);
	AssertTrue(iTotalRun >= psProject->iMinTestsRun);

	szMainFile.Kill();
	aszTests.Kill();
	aszLines.Kill();
	cBuilder.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// The 65C64 unless the test's command line is "816".
//
//////////////////////////////////////////////////////////////////////////
void TestProject65ChooseTarget(int argc, char** argv)
{
	geTestProject65Target = ((argc > 1) && (strcmp(argv[1], "816") == 0)) ? CPPT_W65C816 : CPPT_65C64;
}

