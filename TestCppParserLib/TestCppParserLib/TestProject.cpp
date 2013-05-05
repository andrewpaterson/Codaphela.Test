#include "BaseLib/FastFunctions.h"
#include "BaseLib/PointerRemapper.h"
#include "CoreLib/Operators.h"
#include "CoreLib/TypeConverter.h"
#include "StandardLib/ClassStorage.h"
#include "CppParserLib/Project.h"
#include "TestLib/Assert.h"
#include "TestPreprocessor.h"
#include "TestProject.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestReinclude(void)
{
	ClassStorageInit();
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

	cProject.Init();

	pcLibrary = cProject.AddLibrary("Test", ".");
	pcLibrary->AddFile("TestHeader.h");
	pcTU1 = (CTranslationUnit*)pcLibrary->AddFile("TestUnit1.cpp", TRUE, TRUE);
	pcTU2 = (CTranslationUnit*)pcLibrary->AddFile("TestUnit2.cpp", TRUE, TRUE);
	pcLibrary->AddFile("TestHeader2.h");
	pcConfig = pcLibrary->AddConfiguration("Debug");
	pcConfig->AddDefines("WIN32;_DEBUG;_LIB;_CRT_SECURE_NO_DEPRECATE");

	cProject.Process("Debug");

	AssertString("\
TestUnit1.cpp (Parsing): 0, 0 (0)\n\
TestHeader.h (Parsing): 0, 0 (0)\n\
TestHeader2.h (Parsing): 0, 0 (0)\n\
TestHeader2.h (Parsing): 1, 0 (4)\n\
TestHeader2.h (Parsing): 2, 0 (7)\n\
TestHeader2.h (Parsing): 3, 0\n\
TestHeader.h (Parsing): 1, 0 (5)\n\
TestHeader.h (Parsing): 2, 0 (14)\n\
TestHeader.h (Parsing): 3, 0\n\
TestHeader.h (Parsing): 0, 0 (0)\n\
TestHeader.h          : 2, 0 (14)\n\
TestHeader.h (Parsing): 3, 0\n\
TestHeader.h (Parsing): 0, 0 (0)\n\
TestHeader.h          : 2, 0 (14)\n\
TestHeader.h (Parsing): 3, 0\n\
TestUnit1.cpp (Parsing): 1, 0 (5)\n\
TestUnit1.cpp (Parsing): 2, 0\n\
", pcTU1->mpcLogs->szBlocksLog.Text());

	AssertString("\
     TestUnit1.cpp\n\
         TestHeader.h\n\
             TestHeader2.h\n\
         TestHeader.h\n\
         TestHeader.h\n\
", pcTU1->mpcLogs->szIncludesLog.Text());

		AssertString("\
TestUnit2.cpp (Parsing): 0, 0 (0)\n\
TestHeader.h (Parsing): 0, 0 (0)\n\
TestHeader2.h (Parsing): 0, 0 (0)\n\
TestHeader2.h (Parsing): 1, 0 (4)\n\
TestHeader2.h (Parsing): 2, 0 (7)\n\
TestHeader2.h (Parsing): 3, 0\n\
TestHeader.h (Parsing): 1, 0 (5)\n\
TestHeader.h (Parsing): 2, 0 (14)\n\
TestHeader.h (Parsing): 3, 0\n\
TestHeader.h (Parsing): 0, 0 (0)\n\
TestHeader.h          : 2, 0 (14)\n\
TestHeader.h (Parsing): 3, 0\n\
TestHeader.h (Parsing): 0, 0 (0)\n\
TestHeader.h          : 2, 0 (14)\n\
TestHeader.h (Parsing): 3, 0\n\
TestUnit2.cpp (Parsing): 1, 0 (5)\n\
TestUnit2.cpp (Parsing): 2, 0\n\
", pcTU2->mpcLogs->szBlocksLog.Text());

	AssertString("\
     TestUnit2.cpp\n\
         TestHeader.h\n\
             TestHeader2.h\n\
         TestHeader.h\n\
         TestHeader.h\n\
", pcTU2->mpcLogs->szIncludesLog.Text());

	AssertInt(3, cProject.miBlockReuse);

	cProject.Kill();

	NumberKill();
	KillTokenMemory();
	OperatorsKill();
	TypeConverterKill();
	FastFunctionsKill();
	ClassStorageKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestXXX(void)
{
	ClassStorageInit();
	FastFunctionsInit();
	TypeConverterInit();
	OperatorsInit();
	InitTokenMemory();
	NumberInit();

	
	NumberKill();
	KillTokenMemory();
	OperatorsKill();
	TypeConverterKill();
	FastFunctionsKill();
	ClassStorageKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestProject(void)
{
	BeginTests();

	TestReinclude();
	TestXXX();

	TestStatistics();
}

