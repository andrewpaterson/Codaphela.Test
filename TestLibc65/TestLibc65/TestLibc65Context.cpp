#include <string.h>
#include <stdlib.h>
#include "BaseLib/FileUtil.h"
#include "BaseLib/ArrayChars.h"
#include "Assembler65Lib/Asm65Assembler.h"
#include "CppParserLib/Preprocessor.h"
#include "CppParserLib/HeaderFileMap.h"
#include "CppParserLib/HeaderFiles.h"
#include "CppParserLib/CppTokeniser.h"
#include "CppParserLib/CppParser.h"
#include "CppParserLib/CPP65Generator.h"
#include "CppParserLib/Project.h"
#include "TestLib/Assert.h"
#include "TestLibc65Context.h"


#define TEST_LIBC65_DIRECTORY		".." _FS_ ".." _FS_ ".." _FS_ "commonlibraries" _FS_ "Libc65"
#define TEST_LIBC65_LIBRARIES		".." _FS_ ".." _FS_ ".." _FS_ "commonlibraries"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CTestLibc65Memory::Init(void)
{
	memset(mauiLow, 0, sizeof(mauiLow));
	memset(mauiHigh, 0, sizeof(mauiHigh));
	muiBadAccesses = 0;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
uint8* CTestLibc65Memory::Byte(uint32 uiAddress)
{
	if (uiAddress < TEST_LIBC65_LOW_SIZE)
	{
		return &mauiLow[uiAddress];
	}
	if (uiAddress >= TEST_LIBC65_HIGH_BASE)
	{
		return &mauiHigh[uiAddress - TEST_LIBC65_HIGH_BASE];
	}
	return NULL;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
uint8 CTestLibc65Memory::GetByte(uint32 uiAddress)
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
void CTestLibc65Memory::SetByte(uint32 uiAddress, uint8 uiValue)
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
uint16 CTestLibc65Memory::GetWord(uint32 uiAddress)
{
	return (uint16)(GetByte(uiAddress) | (GetByte(uiAddress + 1) << 8));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
uint32 CTestLibc65Memory::GetLong(uint32 uiAddress)
{
	return (uint32)GetWord(uiAddress) | ((uint32)GetWord(uiAddress + 2) << 16);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CTestLibc65Memory::SetLong(uint32 uiAddress, uint32 uiValue)
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
void CTestLibc65Memory::Load(CAsm65Output* pcOutput)
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
static void TestLibc65TickHigh(C65C64Meta* pcMPU, void* pvContext)
{
	CTestLibc65Memory*	pcMemory;
	uint32				uiAddress;
	uint16				uiData;

	pcMemory = (CTestLibc65Memory*)pvContext;
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
		pcMPU->GetData()->Set(pcMemory->GetWord(uiAddress));
	}
	else
	{
		uiData = pcMPU->GetData()->Get();
		if (pcMPU->GetLowerByte()->IsHigh())
		{
			pcMemory->SetByte(uiAddress, (uint8)uiData);
		}
		if (pcMPU->GetUpperByte()->IsHigh())
		{
			pcMemory->SetByte(uiAddress + 1, (uint8)(uiData >> 8));
		}
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
static void TestLibc65TickLow(C65C64Meta* pcMPU, void* pvContext)
{
}


//////////////////////////////////////////////////////////////////////////
//
// Preprocesses, parses and generates szSource as the unit prefixed szUnit.  Libc65 is the system include
// directory.
//
//////////////////////////////////////////////////////////////////////////
static void TestLibc65Generate(CChars* pszAssembly, CChars* pszErrors, const char* szSource, const char* szUnit, CArrayChars* paszExternals, CArrayChars* paszEmitted, CArrayChars* paszInitialise, CArrayChars* paszFinalise)
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
	CFileUtil			cFileUtil;
	CChars				szDirectory;
	CConfig				cConfig;

	cHeaderFileMap.Init();
	szDirectory.Init(TEST_LIBC65_DIRECTORY);
	cFileUtil.FullPath(&szDirectory);
	cStandard.Init(szDirectory.Text(), &cHeaderFileMap, false, true);
	szDirectory.Kill();
	szDirectory.Init(TEST_LIBC65_LIBRARIES);
	cFileUtil.FullPath(&szDirectory);
	cLibraries.Init(szDirectory.Text(), &cHeaderFileMap, true, false);
	szDirectory.Kill();

	cConfig.Init("65C64");
	CCPP65Generator::AddDefines(&cConfig);

	cFile.Init("Test.cpp", NULL, false);
	cFile.SetContents((char*)szSource);
	cPreprocessor.Init(&cConfig);
	cPreprocessor.AddIncludeDirectory(&cStandard);
	cPreprocessor.AddIncludeDirectory(&cLibraries);
	cPreprocessor.PreprocessTranslationUnit(&cFile);
	pszErrors->Append(cPreprocessor.GetErrors()->Text());
	cPreprocessor.Kill();

	cTokeniser.Init();
	cTokeniser.Tokenise(cFile.GetTokens());
	pszErrors->Append(cTokeniser.GetErrors()->Text());

	cTree.Init(&cTokeniser);
	cParser.Init(&cTokeniser, &cTree);
	cParser.Parse();
	pszErrors->Append(cTree.GetErrors()->Text());
	cParser.Kill();

	cGenerator.Init(&cTree);
	cGenerator.SetUnit(szUnit, paszEmitted);
	cGenerator.Generate(pszAssembly);
	cGenerator.GetExternals(paszExternals);
	cGenerator.GetStartUp(paszInitialise, paszFinalise);
	pszErrors->Append(cGenerator.GetErrors()->Text());
	cGenerator.Kill();

	cTree.Kill();
	cTokeniser.Kill();
	cFile.Kill();
	cConfig.Kill();
	cLibraries.Kill();
	cStandard.Kill();
	cHeaderFileMap.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// Adds the labels defined in szAssembly (a name at the start of a line, followed by a colon) to paszLabels.
//
//////////////////////////////////////////////////////////////////////////
static void TestLibc65DefinedLabels(CArrayChars* paszLabels, const char* szAssembly)
{
	const char*	szLine;
	const char*	szEnd;
	CChars		szLabel;

	szLine = szAssembly;
	while (*szLine)
	{
		szEnd = szLine;
		while ((*szEnd != '\0') && (*szEnd != '\n'))
		{
			szEnd++;
		}
		if ((szEnd > szLine + 1) && (szLine[0] != '\t') && (szLine[0] != ' ') && (szLine[0] != ';') && (szEnd[-1] == ':'))
		{
			szLabel.Init();
			szLabel.Append(szLine, (int)(szEnd - szLine - 1));
			paszLabels->AddIfUnique(szLabel);
			szLabel.Kill();
		}
		szLine = (*szEnd == '\n') ? szEnd + 1 : szEnd;
	}
}


//////////////////////////////////////////////////////////////////////////
//
// Compiles szSource and the Libc65 units (file names in commonlibraries/Libc65, NULL terminated), links them
// and loads the program at reset.  The labels in szStubs (space separated, sorted) must be exactly the ones
// used but defined by no unit; each is a stp so a call to one stops the program.
//
//////////////////////////////////////////////////////////////////////////
bool TestLibc65Begin(STestLibc65Run* psRun, const char** aszUnits, const char* szStubs, const char* szSource)
{
	CProject			cProject;
	CLibrary*			pcLibrary;
	CTranslationUnit*	pcFile;
	SProcessIter		sIter;
	CCPPTokeniser		cTokeniser;
	CCPPSyntaxTree		cTree;
	CCPPParser			cParser;
	CCPP65Generator		cGenerator;
	CAsm65Assembler		cAssembler;
	CFileUtil			cFileUtil;
	CChars				szDirectory;
	CChars				szUnits;
	CChars				szProgram;
	CChars				szUnit;
	CChars				szErrors;
	CChars				szMissing;
	CArrayChars			aszEmitted;
	CArrayChars			aszInitialise;
	CArrayChars			aszFinalise;
	CArrayChars			aszExternals;
	CArrayChars			aszDefined;
	int					iUnit;
	size				i;
	bool				bResult;

	cProject.Init(false);
	szDirectory.Init(TEST_LIBC65_DIRECTORY);
	cFileUtil.FullPath(&szDirectory);
	cProject.AddIncludeDirectory(szDirectory.Text(), false, true);
	pcLibrary = cProject.AddLibrary("Libc65", szDirectory.Text(), false);
	CCPP65Generator::AddDefines(pcLibrary->AddConfiguration("65C64"));
	szDirectory.Kill();
	szDirectory.Init(TEST_LIBC65_LIBRARIES);
	cFileUtil.FullPath(&szDirectory);
	cProject.AddIncludeDirectory(szDirectory.Text(), true, false);
	szDirectory.Kill();

	for (i = 0; aszUnits[i]; i++)
	{
		pcLibrary->AddTranslationUnit((char*)aszUnits[i]);
	}
	AssertTrue(cProject.Process("65C64"));

	szUnits.Init();
	szErrors.Init();
	aszEmitted.Init();
	aszInitialise.Init();
	aszFinalise.Init();
	aszExternals.Init();

	TestLibc65Generate(&szUnits, &szErrors, szSource, "U0_", &aszExternals, &aszEmitted, &aszInitialise, &aszFinalise);

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

		szUnit.Init("U");
		szUnit.Append(iUnit);
		szUnit.Append('_');
		cGenerator.Init(&cTree);
		cGenerator.SetUnit(szUnit.Text(), &aszEmitted);
		cGenerator.Generate(&szUnits);
		szErrors.Append(cGenerator.GetErrors()->Text());
		cGenerator.GetStartUp(&aszInitialise, &aszFinalise);
		cGenerator.GetExternals(&aszExternals);
		cGenerator.Kill();
		szUnit.Kill();
		cTree.Kill();
		cTokeniser.Kill();
	}
	AssertInt((int)i, iUnit);
	AssertString("", szErrors.Text());

	szProgram.Init();
	CCPP65Generator::AppendStartUp(&szProgram, &aszInitialise, &aszFinalise);
	szProgram.Append(szUnits);

	//What is used but not written by any unit.
	aszDefined.Init();
	TestLibc65DefinedLabels(&aszDefined, szProgram.Text());
	szMissing.Init();
	aszExternals.QuickSort(true);
	for (i = 0; i < aszExternals.NumElements(); i++)
	{
		if (aszDefined.GetIndex(aszExternals.GetText(i)) == ARRAY_ELEMENT_NOT_FOUND)
		{
			if (!szMissing.Empty())
			{
				szMissing.Append(' ');
			}
			szMissing.Append(aszExternals.GetText(i));
			szProgram.Append(aszExternals.GetText(i));
			szProgram.Append(":\n\t\tstp\n");
		}
	}
	AssertString(szStubs, szMissing.Text());

	bResult = szErrors.Empty();
	psRun->pcMemory = NULL;
	if (bResult)
	{
		psRun->pcMemory = (CTestLibc65Memory*)malloc(sizeof(CTestLibc65Memory));
		psRun->pcMemory->Init();
		psRun->pcMemory->SetLong(VECTOR_65C64_BASE + 4 * VECTOR_65C64_RESET, CPP65_PROGRAM_ADDRESS);

		cAssembler.Init();
		bResult = cAssembler.Assemble(szProgram.Text());
		AssertString("", cAssembler.GetErrors());
		psRun->pcMemory->Load(cAssembler.GetOutput());
		cAssembler.Kill();

		psRun->cMeta.Init(TestLibc65TickHigh, TestLibc65TickLow, psRun->pcMemory);
		psRun->cMeta.TickInstruction();
	}

	szMissing.Kill();
	aszDefined.Kill();
	szProgram.Kill();
	aszExternals.Kill();
	aszFinalise.Kill();
	aszInitialise.Kill();
	aszEmitted.Kill();
	szErrors.Kill();
	szUnits.Kill();
	cProject.Kill();
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
	size	i;

	for (i = 0; i < uiMaxInstructions; i++)
	{
		if (!psRun->cMeta.TickInstruction())
		{
			return psRun->cMeta.GetMPU()->GetS() == CPP65_STACK_TOP;
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
		AssertSize(0, psRun->pcMemory->muiBadAccesses);
		psRun->cMeta.Kill();
		free(psRun->pcMemory);
		psRun->pcMemory = NULL;
	}
}

