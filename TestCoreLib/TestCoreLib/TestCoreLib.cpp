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
void TestIndexes(void);
void TestIndexedData(void);
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
void TestIndexTreeEvictingDiagnosticCallback(void);


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int main(void)
{
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
	TestIndexes();
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
	TestNamedIndexes();
	TestNamedIndexedData();
	TestIndexTreeEvictingDiagnosticCallback();
	TestIndexTreeAccess();

	return TestTotalStatistics();
}

