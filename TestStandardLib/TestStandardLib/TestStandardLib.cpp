#include <Windows.h>
#include "TestLib/Assert.h"


void TestClass(void);
void TestClassStorage(void);
void TestArrayType(void);
void TestArrayUnknown(void);
void TestUnknowns(void);
void TestMapStringUnknown(void);
void TestSetType(void);
void TestSetUnknown(void);
void TestChannelsAccessor(void);
void TestExternalChannelPadder(void);
void TestChannels(void);
void TestExternalChannels(void);
void TestSingleChannelAccessor(void);
void TestActionEvent(void);
void TestEvent(void);
void TestChunkFileNames(void);
void TestNamedIndexes(void);
void TestObjectGraphSerialiser(void);
void TestPointer(void);
void TestObjectConverter(void);
void TestObject(void);
void TestObjects(void);
void TestRoot(void);
void TestParameters(void);
void TestObjectWriterChunked(void);
void TestObjectReaderChunked(void);
void TestObjectGraphDeserialiser(void);
void TestObjectReaderSimple(void);


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int FAR PASCAL WinMain(HINSTANCE hInstance,	HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	InitTotalStatistics();
	InitEmptyString();
	FastFunctionsInit();

	TestClass();
	TestClassStorage();
	TestUnknowns();
	TestArrayUnknown();
	TestSetUnknown();
	TestArrayType();
	TestSetType();
	TestMapStringUnknown();
	TestEvent();
	TestActionEvent();
	TestExternalChannels();
	TestExternalChannelPadder();
	TestChannels();
	TestChannelsAccessor();
	TestSingleChannelAccessor();
	TestChunkFileNames();
	TestParameters();
	TestObject();
	TestRoot();
	TestPointer();
	TestObjectWriterChunked();
	TestObjectGraphSerialiser();
	TestObjectReaderSimple();
	TestObjectReaderChunked();
	TestNamedIndexes();
	TestObjects();
	TestObjectGraphDeserialiser();
	//TestObjectConverter();

	FastFunctionsKill();
	KillEmptyString();
	return TestTotalStatistics();
}

