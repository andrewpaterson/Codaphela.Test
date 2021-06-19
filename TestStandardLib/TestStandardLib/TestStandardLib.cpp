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


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int main(void)
{
	InitTotalStatistics();
	FastFunctionsInit();

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
	TestNamedObject();
	TestObjectDirty();
	TestString();
	TestObjectAllocator();
	TestChunkFileObjectWriter();
	TestObjectGraphSerialiser();
	TestObjectReaderSimple();
	TestObjectReaderChunked();
	TestObjectStackPointers();
	TestObjectGraphDeserialiser();
	TestObjectConverter();
	TestObjects();
	TestStackPointers();
	TestDehollowfication();
	TestObjectsEvictVsKill();
	TestUsage();
	TestArray();
	TestKill();
	TestEmbedded();
	TestEmbeddedObjectRemapTos();
	TestEmbeddedStackPointers();

	FastFunctionsKill();
	return TestTotalStatistics();
}

