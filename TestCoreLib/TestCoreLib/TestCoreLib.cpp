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
void TestIndexedFile(void);
void TestIndexedFiles(void);
void TestIndexes(void);
void TestIndexedHuge(void);
void TestIndexedData(void);
void TestIndexedDataSmart(void);
void TestTransientIndexedFile(void);
void TestTransactionData(void);
void TestTransactionController(void);
void TestOperators(void);
void TestFunctionCaller(void);
void TestNumber(void);
void TestFiles(void);
void TestPackFilesPacker(void);


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
	InitTotalStatistics();

	//TestFloatHelper();
	//TestIntegerHelper();
	//TestFastFunctions();
	//TestArrayMinimalTemplate();
	//TestPropertiesFile();
	//TestChars();
	//TestMap();
	//TestTextParser();
	//TestXMLParser();
	//TestXMLFile();
	//TestLogFile();
	TestDurableSet();
	TestDurableFile();
	TestDurableFileController();
	//TestIndexTreeNodeFile();
	//TestIndexTreeBlockFile();
	//TestIndexedFile();
	//TestIndexedFiles();
	//TestIndexes();
	//TestIndexedHuge();
	//TestIndexedData();
	//TestIndexedDataSmart();
	//TestTransientIndexedFile();
	//TestTransactionData();
	//TestTransactionController();
	//TestOperators();
	//TestFunctionCaller();
	//TestFiles();
	//TestPackFilesPacker();
	//TestNumber();

	return TestTotalStatistics();
}

