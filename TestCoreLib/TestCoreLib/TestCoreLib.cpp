#include "TestLib/Assert.h"


void TestFloatHelper(void);
void TestIntegerHelper(void);
void TestFastFunctions(void);
void TestArrayMinimalTemplate(void);
void TestPropertiesFile(void);
void TestChars(void);
void TestMap(void);
void TestTextParser(void);
void TestXMLParser(void);
void TestXMLFile(void);
void TestLogFile(void);
void TestDurableFile(void);
void TestDurableSet(void);
void TestDurableFileController(void);
void TestIndexTreeBlockFile(void);
void TestIndexTreeNodeFile(void);
void TestIndexTreeWriter(void);
void TestIndexedFile(void);
void TestIndexedFiles(void);
void TestIndexes(void);
void TestIndexedHuge(void);
void TestIndexedData(void);
void TestIndexedDataSmart(void);
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
	TestArrayMinimalTemplate();
	TestPropertiesFile();
	TestChars();
	TestMap();
	TestTextParser();
	TestXMLParser();
	TestXMLFile();
	TestLogFile();
	TestDurableSet();
	TestDurableFile();
	TestDurableFileController();
	TestIndexTreeNodeFile();
	TestIndexTreeBlockFile();
	TestIndexTreeWriter();
	TestIndexedFile();
	TestIndexedFiles();
	TestIndexes();
	TestIndexedHuge();
	TestOperators();
	TestFunctionCaller();
	TestFiles();
	TestPackFilesPacker();
	TestIndexedData();
	TestIndexedDataSmart();
	TestNumber();

	return TestTotalStatistics();
}

