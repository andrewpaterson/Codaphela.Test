#include <string.h>
#include <stdlib.h>
#include "TestCPP65Context.h"
#include "Assembler65Lib/Asm65Assembler.h"
#include "Assembler65Lib/Asm65Linker.h"
#include "BaseLib/TextFile.h"
#include "BaseLib/FileUtil.h"
#include "CppParserLib/Preprocessor.h"
#include "CppParserLib/HeaderFileMap.h"
#include "CppParserLib/HeaderFiles.h"
#include "CppParserLib/CppTokeniser.h"
#include "CppParserLib/CppParser.h"
#include "CppParserLib/CPP65Generator.h"
#include "CppParserLib/Project.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CTestCPP65Context::Init(void)
{
	memset(mauiLow, 0, sizeof(mauiLow));
	memset(mauiHigh, 0, sizeof(mauiHigh));
	muiBadAccesses = 0;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
uint8* CTestCPP65Context::Byte(uint32 uiAddress)
{
	if (uiAddress < TEST_CPP65_LOW_SIZE)
	{
		return &mauiLow[uiAddress];
	}
	if (uiAddress >= TEST_CPP65_HIGH_BASE)
	{
		return &mauiHigh[uiAddress - TEST_CPP65_HIGH_BASE];
	}
	return NULL;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
uint8 CTestCPP65Context::GetByte(uint32 uiAddress)
{
	uint8*	puiByte;

	puiByte = Byte(uiAddress);
	if (puiByte)
	{
		return *puiByte;
	}
	muiBadAccesses++;
	return 0;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CTestCPP65Context::SetByte(uint32 uiAddress, uint8 uiValue)
{
	uint8*	puiByte;

	puiByte = Byte(uiAddress);
	if (puiByte)
	{
		*puiByte = uiValue;
	}
	else
	{
		muiBadAccesses++;
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
uint16 CTestCPP65Context::GetWord(uint32 uiAddress)
{
	return (uint16)(GetByte(uiAddress) | (GetByte(uiAddress + 1) << 8));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
uint32 CTestCPP65Context::GetLong(uint32 uiAddress)
{
	return (uint32)GetWord(uiAddress) | ((uint32)GetWord(uiAddress + 2) << 16);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CTestCPP65Context::SetLong(uint32 uiAddress, uint32 uiValue)
{
	int	i;

	for (i = 0; i < 4; i++)
	{
		SetByte(uiAddress + i, (uint8)(uiValue >> (8 * i)));
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CTestCPP65Context::Load(CAsm65Output* pcOutput)
{
	size			i;
	size			j;
	SAsm65Segment*	psSegment;

	for (i = 0; i < pcOutput->NumSegments(); i++)
	{
		psSegment = pcOutput->GetSegment(i);
		for (j = 0; j < psSegment->cBytes.NumElements(); j++)
		{
			SetByte(psSegment->uiAddress + (uint32)j, psSegment->cBytes.GetValue(j));
		}
	}
}


//////////////////////////////////////////////////////////////////////////
//
// Memory responds while PHI2 is high.
//
//////////////////////////////////////////////////////////////////////////
static void TestCPP65TickHigh(C65C64Meta* pcMPU, void* pvContext)
{
	CTestCPP65Context*	pcContext;
	uint32				uiAddress;
	uint16				uiData;

	pcContext = (CTestCPP65Context*)pvContext;
	if (!pcMPU->GetRWB()->IsHigh() && !pcMPU->GetRWB()->IsLow())
	{
		return;
	}
	if (!pcMPU->GetVPA()->IsHigh() && !pcMPU->GetVDA()->IsHigh() && pcMPU->GetVPB()->IsHigh())
	{
		return;
	}

	uiAddress = pcMPU->GetAddress()->Get();
	if (pcMPU->GetRWB()->IsHigh())
	{
		pcMPU->GetData()->Set(pcContext->GetWord(uiAddress));
	}
	else
	{
		uiData = pcMPU->GetData()->Get();
		if (pcMPU->GetLowerByte()->IsHigh())
		{
			pcContext->SetByte(uiAddress, (uint8)uiData);
		}
		if (pcMPU->GetUpperByte()->IsHigh())
		{
			pcContext->SetByte(uiAddress + 1, (uint8)(uiData >> 8));
		}
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
static void TestCPP65TickLow(C65C64Meta* pcMPU, void* pvContext)
{
}


//////////////////////////////////////////////////////////////////////////
//
// Compiles szSource (as a program with its start up if bProgram) into the assembly of
// an object, appended to pszAssembly, and the errors to pszErrors.  The labels it uses
// but does not define are added to paszExternals.
//
//////////////////////////////////////////////////////////////////////////
bool TestCPP65Generate(CChars* pszAssembly, CChars* pszErrors, const char* szSource, bool bProgram, CArrayChars* paszExternals)
{
	CTranslationUnit	cFile;
	CPreprocessor		cPreprocessor;
	CCPPTokeniser		cTokeniser;
	CCPPSyntaxTree		cTree;
	CCPPParser			cParser;
	CCPP65Generator		cGenerator;
	CHeaderFileMap		cHeaderFileMap;
	CHeaderFiles		cStandard;
	CHeaderFiles		cLibraries;
	CHeaderFiles		cInput;
	CHeaderFiles		cBaseLib;
	CFileUtil			cFileUtil;
	CChars				szDirectory;
	CConfig				cConfig;
	bool				bResult;

	//<stdint.h> and the rest are the 65C64's (Libc65), "BaseLib/..." are the libraries'.
	cHeaderFileMap.Init();
	szDirectory.Init(".." _FS_ ".." _FS_ ".." _FS_ "commonlibraries" _FS_ "Libc65");
	cFileUtil.FullPath(&szDirectory);
	cStandard.Init(szDirectory.Text(), &cHeaderFileMap, false, true);
	szDirectory.Kill();
	szDirectory.Init(".." _FS_ ".." _FS_ ".." _FS_ "commonlibraries");
	cFileUtil.FullPath(&szDirectory);
	cLibraries.Init(szDirectory.Text(), &cHeaderFileMap, true, false);
	szDirectory.Kill();
	szDirectory.Init("Input" _FS_ "CPP65");
	cFileUtil.FullPath(&szDirectory);
	cInput.Init(szDirectory.Text(), &cHeaderFileMap, true, false);
	szDirectory.Kill();
	szDirectory.Init(".." _FS_ ".." _FS_ ".." _FS_ "commonlibraries" _FS_ "BaseLib");
	cFileUtil.FullPath(&szDirectory);
	cBaseLib.Init(szDirectory.Text(), &cHeaderFileMap, false, false);
	szDirectory.Kill();

	cConfig.Init("65C64");
	CCPP65Generator::AddDefines(&cConfig);
	cFile.Init("Generated.cpp", NULL, false);
	cFile.SetContents((char*)szSource);
	cPreprocessor.Init(&cConfig);
	cPreprocessor.AddIncludeDirectory(&cStandard);
	cPreprocessor.AddIncludeDirectory(&cLibraries);
	cPreprocessor.AddIncludeDirectory(&cInput);
	cPreprocessor.AddIncludeDirectory(&cBaseLib);
	bResult = cPreprocessor.PreprocessTranslationUnit(&cFile);
	pszErrors->Append(cPreprocessor.GetErrors()->Text());
	cPreprocessor.Kill();

	cTokeniser.Init();
	bResult &= cTokeniser.Tokenise(cFile.GetTokens());
	pszErrors->Append(cTokeniser.GetErrors()->Text());

	cTree.Init(&cTokeniser);
	cParser.Init(&cTokeniser, &cTree);
	bResult &= cParser.Parse();
	pszErrors->Append(cTree.GetErrors()->Text());
	cParser.Kill();

	cGenerator.Init(&cTree);
	bResult &= bProgram ? cGenerator.GenerateProgram(pszAssembly) : cGenerator.Generate(pszAssembly);
	if (paszExternals)
	{
		cGenerator.GetExternals(paszExternals);
	}
	pszErrors->Append(cGenerator.GetErrors()->Text());
	cGenerator.Kill();

	cTree.Kill();
	cTokeniser.Kill();
	cFile.Kill();
	cConfig.Kill();
	cBaseLib.Kill();
	cInput.Kill();
	cLibraries.Kill();
	cStandard.Kill();
	cHeaderFileMap.Kill();
	return bResult;
}


//////////////////////////////////////////////////////////////////////////
//
// Compiles and assembles szSource as a program, loads it and runs reset.
//
//////////////////////////////////////////////////////////////////////////
bool TestCPP65Begin(STestCPP65Run* psRun, const char* szSource)
{
	CChars	szAssembly;
	CChars	szErrors;
	bool	bResult;

	szAssembly.Init();
	szErrors.Init();
	bResult = TestCPP65Generate(&szAssembly, &szErrors, szSource, true);
	AssertString("", szErrors.Text());
	bResult &= TestCPP65BeginAssembly(psRun, szAssembly.Text());
	szErrors.Kill();
	szAssembly.Kill();
	return bResult;
}


//////////////////////////////////////////////////////////////////////////
//
// Assembles one object (the start up must be its first code), adds it to the linker.
//
//////////////////////////////////////////////////////////////////////////
static bool TestCPP65AddObject(CAsm65Linker* pcLinker, CAsm65Library* pcObjects, const char* szName, const char* szAssembly)
{
	CAsm65Assembler	cAssembler;
	CAsm65Object*	pcObject;
	bool			bResult;

	pcObject = pcObjects->AddObject(szName);
	cAssembler.Init();
	bResult = cAssembler.AssembleObject(szAssembly, pcObject);
	AssertString("", cAssembler.GetErrors());
	cAssembler.Kill();
	pcLinker->AddObject(pcObject);
	return bResult;
}


//////////////////////////////////////////////////////////////////////////
//
// Links, loads the program and runs reset.  The text starts at CPP65_PROGRAM_ADDRESS
// and the program must end below the heap.
//
//////////////////////////////////////////////////////////////////////////
static bool TestCPP65BeginLinked(STestCPP65Run* psRun, CAsm65Linker* pcLinker)
{
	bool	bResult;

	pcLinker->SetAddress(ASK65_Text, CPP65_PROGRAM_ADDRESS);
	pcLinker->SetLimit(CPP65_HEAP_ADDRESS);
	bResult = pcLinker->Link();
	AssertString("", pcLinker->GetErrors());

	psRun->pcContext = (CTestCPP65Context*)malloc(sizeof(CTestCPP65Context));
	psRun->pcContext->Init();
	psRun->pcContext->SetLong(VECTOR_65C64_BASE + 4 * VECTOR_65C64_RESET, CPP65_PROGRAM_ADDRESS);
	psRun->uiInstructions = 0;
	psRun->pcContext->Load(pcLinker->GetOutput());

	psRun->cMeta.Init(TestCPP65TickHigh, TestCPP65TickLow, psRun->pcContext);
	psRun->cMeta.TickInstruction();
	return bResult;
}


//////////////////////////////////////////////////////////////////////////
//
// Assembles a program (one object with its start up), links it, loads it and runs
// reset.
//
//////////////////////////////////////////////////////////////////////////
bool TestCPP65BeginAssembly(STestCPP65Run* psRun, const char* szAssembly)
{
	CAsm65Library	cObjects;
	CAsm65Linker	cLinker;
	bool			bResult;

	cObjects.Init("objects");
	cLinker.Init();
	bResult = TestCPP65AddObject(&cLinker, &cObjects, "program", szAssembly);
	bResult &= TestCPP65BeginLinked(psRun, &cLinker);
	cLinker.Kill();
	cObjects.Kill();
	return bResult;
}


//////////////////////////////////////////////////////////////////////////
//
// Runs until the processor stops.  Returns the number of instructions.
//
//////////////////////////////////////////////////////////////////////////
size TestCPP65Run(STestCPP65Run* psRun, size uiMaxInstructions)
{
	size	i;

	for (i = 0; i < uiMaxInstructions; i++)
	{
		if (!psRun->cMeta.TickInstruction())
		{
			psRun->uiInstructions += i + 1;
			return i + 1;
		}
	}
	psRun->uiInstructions += i;
	return i;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
C65C64* TestCPP65MPU(STestCPP65Run* psRun)
{
	return psRun->cMeta.GetMPU();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCPP65End(STestCPP65Run* psRun)
{
	AssertSize(0, psRun->pcContext->muiBadAccesses);
	psRun->cMeta.Kill();
	free(psRun->pcContext);
}


//////////////////////////////////////////////////////////////////////////
//
// Compiles szSource (as a program with its start up if bProgram) and assembles it as
// an object.  Returns the number of labels it uses but does not define.
//
//////////////////////////////////////////////////////////////////////////
int TestCPP65Assemble(const char* szSource, bool bProgram)
{
	CChars				szAssembly;
	CChars				szErrors;
	CArrayChars			aszExternals;
	CAsm65Assembler		cAssembler;
	CAsm65Object		cObject;
	int					iExternals;

	szAssembly.Init();
	szErrors.Init();
	aszExternals.Init();
	AssertTrue(TestCPP65Generate(&szAssembly, &szErrors, szSource, bProgram, &aszExternals));
	AssertString("", szErrors.Text());

	cObject.Init("unit");
	cAssembler.Init();
	AssertTrue(cAssembler.AssembleObject(szAssembly.Text(), &cObject));
	AssertString("", cAssembler.GetErrors());
	cAssembler.Kill();
	cObject.Kill();

	iExternals = (int)aszExternals.NumElements();
	aszExternals.Kill();
	szErrors.Kill();
	szAssembly.Kill();
	return iExternals;
}


//////////////////////////////////////////////////////////////////////////
//
// TestCPP65Assemble on a file of the libraries, as a translation unit.
//
//////////////////////////////////////////////////////////////////////////
int TestCPP65AssembleLibraryFile(const char* szFilename)
{
	CTextFile	cFile;
	CChars		szPath;
	int			iExternals;

	szPath.Init(".." _FS_ ".." _FS_ ".." _FS_ "commonlibraries" _FS_);
	szPath.Append(szFilename);
	cFile.Init();
	AssertTrue(cFile.Read(szPath.Text()));
	cFile.PassifyNewlines();
	iExternals = TestCPP65Assemble(cFile.Text(), false);
	cFile.Kill();
	szPath.Kill();
	return iExternals;
}


//////////////////////////////////////////////////////////////////////////
//
// Compiles and runs Input/CPP65/szFilename.  Returns what main returned.
//
//////////////////////////////////////////////////////////////////////////
int32 TestCPP65MainFile(const char* szFilename)
{
	CTextFile	cFile;
	CChars		szPath;
	int32		iResult;

	szPath.Init("Input" _FS_ "CPP65" _FS_);
	szPath.Append(szFilename);
	cFile.Init();
	AssertTrue(cFile.Read(szPath.Text()));
	cFile.PassifyNewlines();
	iResult = TestCPP65Main(cFile.Text());
	cFile.Kill();
	szPath.Kill();
	return iResult;
}


//////////////////////////////////////////////////////////////////////////
//
// Compiles and runs szSource.  Returns what main returned.  The program must stop
// within a million instructions with the stack where it started.
//
//////////////////////////////////////////////////////////////////////////
int32 TestCPP65Main(const char* szSource)
{
	STestCPP65Run	sRun;
	int32			iResult;

	AssertTrue(TestCPP65Begin(&sRun, szSource));
	AssertTrue(TestCPP65Run(&sRun, 1000000) < 1000000);
	AssertIntHex(CPP65_STACK_TOP, TestCPP65MPU(&sRun)->GetS());
	iResult = (int32)TestCPP65MPU(&sRun)->GetA();
	TestCPP65End(&sRun);
	return iResult;
}


//////////////////////////////////////////////////////////////////////////
//
// Compiles the units (paths under commonlibraries, or under this test's directory
// when they start with "Input") and szSource if it is given, each into an object,
// links them after the start up and loads the program.  The units in a directory
// share a CLibrary (their include settings).  The labels in szStubs (space
// separated, sorted) must be exactly the ones used but defined by no unit; the
// linker makes each a stp so a call to one stops the program.  pszMap, if given,
// gets the linker's map.
//
//////////////////////////////////////////////////////////////////////////
bool TestCPP65BeginProject(STestCPP65Run* psRun, const char** aszUnits, const char* szStubs, const char* szSource, CChars* pszMap)
{
	CProject			cProject;
	CLibrary*			pcLibrary;
	CTranslationUnit*	pcFile;
	SProcessIter		sIter;
	CCPPTokeniser		cTokeniser;
	CCPPSyntaxTree		cTree;
	CCPPParser			cParser;
	CCPP65Generator		cGenerator;
	CFileUtil			cFileUtil;
	CChars				szDirectory;
	CChars				szLibrary;
	CChars				szFile;
	CChars				szAssembly;
	CChars				szErrors;
	CChars				szMissing;
	CArrayChars			aszMissing;
	CAsm65Library		cObjects;
	CAsm65Linker		cLinker;
	int					iUnit;
	int					iSlash;
	size				i;
	bool				bResult;

	cProject.Init(false);
	szDirectory.Init(".." _FS_ ".." _FS_ ".." _FS_ "commonlibraries" _FS_ "Libc65");
	cFileUtil.FullPath(&szDirectory);
	cProject.AddIncludeDirectory(szDirectory.Text(), false, true);
	szDirectory.Kill();
	szDirectory.Init(".." _FS_ ".." _FS_ ".." _FS_ "commonlibraries");
	cFileUtil.FullPath(&szDirectory);
	cProject.AddIncludeDirectory(szDirectory.Text(), true, false);
	szDirectory.Kill();
	szDirectory.Init("Input" _FS_ "CPP65");
	cFileUtil.FullPath(&szDirectory);
	cProject.AddIncludeDirectory(szDirectory.Text(), true, false);
	szDirectory.Kill();

	for (i = 0; aszUnits[i]; i++)
	{
		szLibrary.Init(aszUnits[i]);
		iSlash = szLibrary.FindFromEnd('/');
		szFile.Init(szLibrary.Text(iSlash + 1));
		szLibrary.SetLength(iSlash);
		pcLibrary = cProject.GetLibrary(szLibrary.Text());
		if (!pcLibrary)
		{
			if (szLibrary.StartsWith("Input"))
			{
				szDirectory.Init(szLibrary);
			}
			else
			{
				szDirectory.Init(".." _FS_ ".." _FS_ ".." _FS_ "commonlibraries" _FS_);
				szDirectory.Append(szLibrary);
			}
			szDirectory.Replace('/', FILE_SEPARATOR[0]);
			cFileUtil.FullPath(&szDirectory);
			pcLibrary = cProject.AddLibrary(szLibrary.Text(), szDirectory.Text(), false);
			CCPP65Generator::AddDefines(pcLibrary->AddConfiguration("65C64"));
			szDirectory.Kill();
		}
		pcLibrary->AddTranslationUnit(szFile.Text());
		szFile.Kill();
		szLibrary.Kill();
	}
	AssertTrue(cProject.Process("65C64"));

	szErrors.Init();
	cObjects.Init("objects");
	cLinker.Init();
	cLinker.SetStubMissing(true);
	bResult = true;

	szAssembly.Init();
	CCPP65Generator::AppendStartUp(&szAssembly);
	bResult &= TestCPP65AddObject(&cLinker, &cObjects, "start up", szAssembly.Text());
	szAssembly.Kill();
	if (szSource)
	{
		szAssembly.Init();
		TestCPP65Generate(&szAssembly, &szErrors, szSource, false);
		bResult &= TestCPP65AddObject(&cLinker, &cObjects, "source", szAssembly.Text());
		szAssembly.Kill();
	}
	iUnit = 0;
	for (pcFile = cProject.Start(&sIter, "65C64"); pcFile; pcFile = cProject.Iterate(&sIter))
	{
		iUnit++;
		cTokeniser.Init();
		cTokeniser.Tokenise(pcFile->GetTokens());
		szErrors.Append(cTokeniser.GetErrors()->Text());
		cTree.Init(&cTokeniser);
		cParser.Init(&cTokeniser, &cTree);
		cParser.Parse();
		szErrors.Append(cTree.GetErrors()->Text());
		cParser.Kill();

		szAssembly.Init();
		cGenerator.Init(&cTree);
		cGenerator.Generate(&szAssembly);
		szErrors.Append(cGenerator.GetErrors()->Text());
		cGenerator.Kill();
		bResult &= TestCPP65AddObject(&cLinker, &cObjects, pcFile->ShortName(), szAssembly.Text());
		szAssembly.Kill();

		cTree.Kill();
		cTokeniser.Kill();
	}
	AssertInt((int)i, iUnit);
	AssertString("", szErrors.Text());

	bResult &= szErrors.Empty() && TestCPP65BeginLinked(psRun, &cLinker);

	//What is used but written by no unit.
	aszMissing.Init();
	for (i = 0; i < cLinker.NumMissing(); i++)
	{
		aszMissing.Add(cLinker.GetMissing(i));
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
	if (pszMap)
	{
		pszMap->Append(cLinker.GetMap());
	}

	szMissing.Kill();
	aszMissing.Kill();
	cLinker.Kill();
	cObjects.Kill();
	szErrors.Kill();
	cProject.Kill();
	return bResult;
}


//////////////////////////////////////////////////////////////////////////
//
// Builds a project (see TestCPP65BeginProject) and runs it.  Returns A when main
// returns.
//
//////////////////////////////////////////////////////////////////////////
int32 TestCPP65RunProject(const char** aszUnits, const char* szStubs, size uiMaxInstructions, const char* szSource)
{
	STestCPP65Run	sRun;
	int32			iResult;

	iResult = 0;
	if (TestCPP65BeginProject(&sRun, aszUnits, szStubs, szSource))
	{
		AssertTrue(TestCPP65Run(&sRun, uiMaxInstructions) < uiMaxInstructions);
		AssertIntHex(CPP65_STACK_TOP, TestCPP65MPU(&sRun)->GetS());
		iResult = (int32)TestCPP65MPU(&sRun)->GetA();
		TestCPP65End(&sRun);
	}
	return iResult;
}


//////////////////////////////////////////////////////////////////////////
//
// Compiles and runs szSource with Libc65's soft float runtime.  Returns what main
// returned.
//
//////////////////////////////////////////////////////////////////////////
int32 TestCPP65MainFloat(const char* szSource)
{
	static const char*	aszUnits[] = { "Libc65/softfloat.cpp", NULL };

	return TestCPP65RunProject(aszUnits, "", 20000000, szSource);
}
