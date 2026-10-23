#include <string.h>
#include <stdlib.h>
#include "TestCPP65Context.h"
#include "Assembler65Lib/Asm65Assembler.h"
#include "BaseLib/TextFile.h"
#include "BaseLib/FileUtil.h"
#include "CppParserLib/Preprocessor.h"
#include "CppParserLib/HeaderFileMap.h"
#include "CppParserLib/HeaderFiles.h"
#include "CppParserLib/CppTokeniser.h"
#include "CppParserLib/CppParser.h"
#include "CppParserLib/CPP65Generator.h"
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
// Preprocesses, parses and generates szSource, as a whole program with its start up
// if bProgram.  The assembly is appended to pszAssembly and every stage's errors to
// pszErrors.  The labels it uses but does not define are added to paszExternals.
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

	cFile.Init("Generated.cpp", NULL, false);
	cFile.SetContents((char*)szSource);
	cPreprocessor.Init(NULL);
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
// Assembles a program, loads it and runs reset.
//
//////////////////////////////////////////////////////////////////////////
bool TestCPP65BeginAssembly(STestCPP65Run* psRun, const char* szAssembly)
{
	CAsm65Assembler		cAssembler;
	bool				bResult;

	psRun->pcContext = (CTestCPP65Context*)malloc(sizeof(CTestCPP65Context));
	psRun->pcContext->Init();
	psRun->pcContext->SetLong(VECTOR_65C64_BASE + 4 * VECTOR_65C64_RESET, CPP65_PROGRAM_ADDRESS);
	psRun->uiInstructions = 0;

	cAssembler.Init();
	bResult = cAssembler.Assemble(szAssembly);
	AssertString("", cAssembler.GetErrors());
	psRun->pcContext->Load(cAssembler.GetOutput());
	cAssembler.Kill();

	psRun->cMeta.Init(TestCPP65TickHigh, TestCPP65TickLow, psRun->pcContext);
	psRun->cMeta.TickInstruction();
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
// Compiles szSource (as a program with its start up if bProgram) and assembles it,
// with a stub for each label it uses but does not define.  Returns the number of
// externals.
//
//////////////////////////////////////////////////////////////////////////
int TestCPP65Assemble(const char* szSource, bool bProgram)
{
	CChars				szAssembly;
	CChars				szErrors;
	CArrayChars			aszExternals;
	CAsm65Assembler		cAssembler;
	size				i;
	int					iExternals;

	szAssembly.Init();
	szErrors.Init();
	aszExternals.Init();
	AssertTrue(TestCPP65Generate(&szAssembly, &szErrors, szSource, bProgram, &aszExternals));
	AssertString("", szErrors.Text());
	for (i = 0; i < aszExternals.NumElements(); i++)
	{
		szAssembly.Append(aszExternals.GetText(i));
		szAssembly.Append(":\n\t\tstp\n");
	}

	cAssembler.Init();
	AssertTrue(cAssembler.Assemble(szAssembly.Text()));
	AssertString("", cAssembler.GetErrors());
	cAssembler.Kill();

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
