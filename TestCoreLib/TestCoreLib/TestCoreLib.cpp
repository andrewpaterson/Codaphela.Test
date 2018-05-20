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
void TestIndexTreeTemplateFile(void);
void TestIndexTreeWriter(void);
void TestIndexedFile(void);
void TestIndexedFiles(void);
void TestIndexTreeNodeFile(void);
void TestIndexes(void);
void TestIndexedData(void);
void TestIndexTreeAccess(void);
void TestOperators(void);
void TestFunctionCaller(void);
void TestNumber(void);
void TestFiles(void);
void TestPackFilesPacker(void);


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
	TestLogFile();
	TestDurableSet();
	TestDurableFile();
	TestDurableFileController();
	TestIndexes();
	TestOperators();
	TestFunctionCaller();
	TestFiles();
	TestPackFilesPacker();
	//TestNumber();
	TestIndexedFile();
	TestIndexedFiles();
	TestIndexTreeMemory();
	TestIndexTreeNodeFile();
	TestIndexTreeFile();
	TestIndexTreeTemplateFile();
	TestIndexTreeAccess();
	TestIndexTreeWriter();
	TestIndexedData();

	return TestTotalStatistics();
}

