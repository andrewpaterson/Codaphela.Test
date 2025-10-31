#include <Windows.h>
#include "TestLib/Assert.h"


void TestStackPointers(void);
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
void TestObjectGraphSerialiser(void);
void TestPointer(void);
void TestObjectConverter(void);
void TestObject(void);
void TestObjectStack(void);
void TestObjectStackPointers(void);
void TestReplaceAndRemap(void);
void TestHollowObject(void);
void TestNamedObject(void);
void TestObjectsSimple(void);
void TestRoot(void);
void TestDistToRoot(void);
void TestDistToStack(void);
void TestObjectGraphWriting(void);
void TestArrayCommonObject(void);
void TestParameters(void);
void TestObjectDirty(void);
void TestObjectAllocator(void);
void TestString(void);
void TestStringOverride(void);
void TestClass(void);
void TestChunkFileObjectWriter(void);
void TestObjectReaderChunked(void);
void TestObjectGraphDeserialiser(void);
void TestObjectReaderSimple(void);
void TestObjects(void);
void TestObjectsEvictVsKill(void);
void TestDehollowfication(void);
void TestKill(void);
void TestUsage(void);
void TestArray(void);
void TestSet(void);
void TestEmbedded(void);
void TestEmbeddedObjectRemapTos(void);
void TestEmbeddedStackPointers(void);
void TestFreeEmbedded(void);
void TestIndexTreeMemory(void);


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int __cdecl main(void)
{
	int iResult;

	_CrtSetBreakAlloc(0);
	InitTotalStatistics();
	FastFunctionsInit();

	TestIndexTreeMemory();
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
	TestParameters();
	TestClass();
	TestDistToRoot();
	TestDistToStack();
	TestObjectsSimple();
	TestRoot();
	TestSet();
	TestObjectGraphWriting();
	TestObject();
	TestObjectStack();
	TestPointer();
	TestArrayCommonObject();
	TestFreeEmbedded();
	TestStringOverride();
	TestReplaceAndRemap();
	TestHollowObject();
	TestNamedObject();
	TestObjectDirty();
	TestObjectAllocator();
	TestChunkFileObjectWriter();
	TestObjectGraphSerialiser();
	TestObjectReaderSimple();
	TestObjectReaderChunked();
	TestObjectStackPointers();
	//TestObjectGraphDeserialiser();
	TestObjectConverter();
	TestObjects();
	TestStackPointers();
	//TestDehollowfication();
	TestString();
	TestObjectsEvictVsKill();
	TestUsage();
	TestArray();
	TestKill();
	TestEmbedded();
	TestEmbeddedObjectRemapTos();
	TestEmbeddedStackPointers();

	FastFunctionsKill();

	iResult = TestTotalStatistics();
	_CrtDumpMemoryLeaks();
	return iResult;
}

