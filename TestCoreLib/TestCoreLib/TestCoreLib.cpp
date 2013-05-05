#include "TestLib/Assert.h"


void TestFloatHelper(void);
void TestIntegerHelper(void);
void TestFastFunctions(void);
void TestArraySimple(void);
void TestChars(void);
void TestMap(void);
void TestTextParser(void);
void TestXMLParser(void);
void TestXMLFile(void);
void TestLogFile(void);
void TestDurableFile(void);
void TestIndexedFile(void);
void TestIndexes(void);
void TestIndexedHuge(void);
void TestIndexedData(void);
void TestIndexedDataSmart(void);
void TestTransientIndexedFile(void);
void TestTransactionData(void);
void TestTransactionController(void);
void TestDurableSet(void);
void TestOperators(void);
void TestFunctionCaller(void);
void TestNumber(void);
void TestFiles(void);


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
	InitTotalStatistics();

	TestFloatHelper();
	TestIntegerHelper();
	TestFastFunctions();
	TestArraySimple();
	TestChars();
	TestMap();
	TestTextParser();
	TestXMLParser();
	TestXMLFile();
	TestLogFile();
	TestDurableFile();
	TestIndexedFile();
	TestIndexes();
	TestIndexedHuge();
	TestIndexedData();
	TestIndexedDataSmart();
	TestTransientIndexedFile();
	TestTransactionData();
	TestTransactionController();
	TestDurableSet();
	TestOperators();
	TestFunctionCaller();
	TestNumber();
	TestFiles();

	return TestTotalStatistics();
}

