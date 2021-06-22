#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  

#include "TestLib/Assert.h"


void TestFloatHelper(void);
void TestIntegerHelper(void);
void TestFastFunctions(void);
void TestPropertiesFile(void);
void TestXMLParser(void);
void TestXMLFile(void);
void TestLogFile(void);
void TestDurableFile(void);
void TestDurableSet(void);
void TestDurableFileController(void);
void TestIndexTreeMemory(void);
void TestIndexTreeFile(void);
void TestIndexTreeDataOrderer(void);
void TestIndexTreeFileCallback(void);
void TestIndexTreeTemplateFile(void);
void TestIndexTreeWriter(void);
void TestIndexedFile(void);
void TestIndexTreeFileIterator(void);
void TestIndexedFiles(void);
void TestIndexTreeNodeFile(void);
void TestIndexedData(void);
void TestSequence(void);
void TestOperators(void);
void TestFunctionCaller(void);
void TestNumber(void);
void TestFiles(void);
void TestPackFilesPacker(void);
void TestIndexedFilesEvicting(void);
void TestIndexTreeEvicting(void);
void TestIndexTreeAccess(void);
void TestNamedIndexes(void);
void TestNamedIndexedData(void);
void TestIndexTreeFileKeyDiagnosticCallback(void);
void TestCodabase(void);


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int __cdecl main(void)
{
	int iResult;

	_CrtSetBreakAlloc(0);
	InitTotalStatistics();

	TestFloatHelper();
	TestIntegerHelper();
	TestFastFunctions();
	TestPropertiesFile();
	TestXMLParser();
	TestXMLFile();
	TestNumber();
	TestOperators();
	TestFunctionCaller();
	TestLogFile();  
	TestDurableSet();
	TestDurableFile();  
	TestDurableFileController();
	TestFiles();
	TestPackFilesPacker();
	TestIndexedFile();
	TestIndexedFiles();
	TestIndexTreeMemory();
	TestIndexTreeNodeFile();
	TestIndexTreeFile();
	TestIndexTreeDataOrderer();
	TestIndexTreeFileCallback();
	TestIndexTreeFileIterator();
	TestIndexTreeTemplateFile();
	TestIndexTreeWriter();
	TestIndexTreeEvicting();
	TestIndexedFilesEvicting();
	TestIndexedData();
	TestSequence();
	TestNamedIndexes();
	TestNamedIndexedData();
	TestIndexTreeFileKeyDiagnosticCallback();
	TestIndexTreeAccess();
	TestCodabase();

	iResult = TestTotalStatistics();
	_CrtDumpMemoryLeaks();
	return iResult;
}

