#include "BaseLib/FastFunctions.h"
#include "BaseLib/PointerRemapper.h"
#include "BaseLib/TypeNames.h"
#include "BaseLib/TypeConverter.h"
#include "CoreLib/Operators.h"
#include "CppParserLib/Project.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestReinclude(void)
{
	TypesInit();
	FastFunctionsInit();
	TypeConverterInit();
	OperatorsInit();
	InitTokenMemory();
	NumberInit();

	CProject			cProject;
	CLibrary*			pcLibrary;
	CConfig*			pcConfig;
	CTranslationUnit*	pcTU1;
	CTranslationUnit*	pcTU2;
	CHeaderFile*		pcHF1;
	CHeaderFile*		pcHF2;

	cProject.Init(TRUE, TRUE);

	pcLibrary = cProject.AddLibrary("Test", ".", FALSE);
	pcHF1 = pcLibrary->AddHeaderFile("TestHeader.h");
	pcTU1 = pcLibrary->AddTranslationUnit("TestUnit1.cpp", TRUE, TRUE);
	pcTU2 = pcLibrary->AddTranslationUnit("TestUnit2.cpp", TRUE, TRUE);
	pcHF2 = pcLibrary->AddHeaderFile("TestHeader2.h");
	pcConfig = pcLibrary->AddConfiguration("Debug");
	pcConfig->AddDefines("_WIN32;_DEBUG;_LIB;_CRT_SECURE_NO_DEPRECATE");

	cProject.Process("Debug");

	AssertString("\
     TestUnit1.cpp (Parsing): 0, 0 (1)\n\
         TestHeader.h (Parsing): 0, 0 (1)\n\
             TestHeader2.h (Parsing): 0, 0 (1)\n\
             TestHeader2.h (Parsing): 1, 0 (5)\n\
             TestHeader2.h (Parsing): 2, 0 (8)\n\
         TestHeader.h (Parsing): 1, 0 (6)\n\
         TestHeader.h (Parsing): 2, 0 (15)\n\
         TestHeader.h (Parsing): 0, 0 (1)\n\
         TestHeader.h          : 2, 0 (15)\n\
         TestHeader.h (Parsing): 0, 0 (1)\n\
         TestHeader.h          : 2, 0 (15)\n\
     TestUnit1.cpp (Parsing): 1, 0 (6)\n", pcTU1->GetLogs()->szBlocksLog.Text());

	AssertString("\
     TestUnit1.cpp (Included)\n\
         TestHeader.h (Included)\n\
             TestHeader2.h (Included)\n\
         TestHeader.h (Included)\n\
         TestHeader.h (Included)\n", pcTU1->GetLogs()->szIncludesLog.Text());

		AssertString("\
     TestUnit2.cpp (Parsing): 0, 0 (1)\n\
         TestHeader.h (Parsing): 0, 0 (1)\n\
             TestHeader2.h (Parsing): 0, 0 (1)\n\
             TestHeader2.h (Parsing): 1, 0 (5)\n\
             TestHeader2.h (Parsing): 2, 0 (8)\n\
         TestHeader.h (Parsing): 1, 0 (6)\n\
         TestHeader.h (Parsing): 2, 0 (15)\n\
         TestHeader.h (Parsing): 0, 0 (1)\n\
         TestHeader.h          : 2, 0 (15)\n\
         TestHeader.h (Parsing): 0, 0 (1)\n\
         TestHeader.h          : 2, 0 (15)\n\
     TestUnit2.cpp (Parsing): 1, 0 (6)\n", pcTU2->GetLogs()->szBlocksLog.Text());

	AssertString("\
     TestUnit2.cpp (Included)\n\
         TestHeader.h (Included)\n\
             TestHeader2.h (Included)\n\
         TestHeader.h (Included)\n\
         TestHeader.h (Included)\n\
", pcTU2->GetLogs()->szIncludesLog.Text());

	AssertInt(2, cProject.GetBlockReuse());

	cProject.Kill();

	NumberKill();
	KillTokenMemory();
	OperatorsKill();
	TypeConverterKill();
	FastFunctionsKill();
	TypesKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestProject(void)
{
	BeginTests();

	TestReinclude();

	TestStatistics();
}

