#include "BaseLib/GlobalMemory.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/TypeNames.h"
#include "StandardLib/Objects.h"
#include "StandardLib/PointerContainer.h"
#include "TestLib/Assert.h"
#include "ObjectTestClasses.h"
#include "ChunkFileObjectWriterTestClasses.h"
#include "EmbeddedObjectTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPointerNegation(void)
{
	ObjectsInit();

	Ptr<CTestObject>	pcObject;
	CPointer			pcBase;

	pcObject = OMalloc<CTestObject>();
	AssertFalse(!pcObject);

	pcObject = NULL;
	AssertTrue(!pcObject);

	pcBase = OMalloc<CTestObject>();
	AssertFalse(!pcBase);

	pcBase = NULL;
	AssertTrue(!pcBase);

	ObjectsFlush();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPointerConstructor(void)
{
	ObjectsInit();

	CEmbeddedContainer	cCluster;

	cCluster.Init();
	AssertNull(cCluster.mpTest.Object());
	AssertPointer(&cCluster, cCluster.mpTest.Embedding());
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPointerDestructorDestruct(STestObjectFreedNotifier* psFreedNotifier)
{
	CTestObject					cTestObject;

	AssertLongLongInt(0, gcObjects.NumMemoryIndexes());

	cTestObject.Init(NULL);
	cTestObject.mpTest = OMalloc<CTestObject>(psFreedNotifier);

	AssertLongLongInt(1, gcObjects.NumMemoryIndexes());
	//cTestObject Destructor called here.  It should cause the allocated object it points to to be destroyed too.
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPointerDestructor(void)
{
	ObjectsInit();

	STestObjectFreedNotifier	sFreedNotifier;

	TestPointerDestructorDestruct(&sFreedNotifier);
	
	AssertTrue(sFreedNotifier.bFreed);
	AssertLongLongInt(0, gcObjects.NumMemoryIndexes());

	ObjectsFlush();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPointerStackToEmbeddedDestruct(void)
{
	AssertLongLongInt(0, gcObjects.NumMemoryIndexes());
	Ptr<CEmbeddedContainer> pMissile = OMalloc<CEmbeddedContainer>();

	AssertLongLongInt(1, gcObjects.NumMemoryIndexes());
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPointerStackToEmbedded(void)
{
	ObjectsInit();

	TestPointerStackToEmbeddedDestruct();
	AssertLongLongInt(0, gcObjects.NumMemoryIndexes());

	ObjectsFlush();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPointerAssignmentSimple()
{
	ObjectsInit();

	Ptr<CTestWithArray>	pcObject1 = ONMalloc<CTestWithArray>("Urgle-burgle", "Warning", 17);

	AssertNotNull(&pcObject1);
	AssertLongLongInt(2, gcObjects.NumMemoryIndexes());

	ObjectsFlush();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPointerAssignmentStackToObjectPointer()
{
	ObjectsInit();

	Ptr<CTestInteger>		pInteger = OMalloc<CTestInteger>(6, 7, 6);
	Ptr<CTestNamedString>	pObject = ONMalloc<CTestNamedString>("Urgle-burgle", Null(), pInteger, "Embedded");

	AssertLongLongInt(2, gcObjects.GetStackPointers()->UsedPointers());

	Ptr<CTestInteger> ptr = pObject->mpAnother;

	AssertLongLongInt(3, gcObjects.GetStackPointers()->UsedPointers());

	ObjectsFlush();
	ObjectsKill();

	AssertTrue(pObject.IsNull());
	AssertTrue(pInteger.IsNull());
	AssertTrue(ptr.IsNull());
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPointerAssignmentObjectToObjectPointer()
{
	ObjectsInit();

	Ptr<CTestInteger>		pInteger = OMalloc<CTestInteger>(6, 7, 6);
	Ptr<CTestNamedString>	pObject = ONMalloc<CTestNamedString>("Urgle-burgle", Null(), pInteger, "Embedded");

	AssertLongLongInt(2, gcObjects.GetStackPointers()->UsedPointers());

	Ptr<CTestInteger> ptr = pObject->mpAnother;

	AssertLongLongInt(3, gcObjects.GetStackPointers()->UsedPointers());

	ObjectsFlush();
	ObjectsKill();

	AssertTrue(pObject.IsNull());
	AssertTrue(pInteger.IsNull());
	AssertTrue(ptr.IsNull());
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPointerHeapNotInGraphFreeStack(void)
{
	ObjectsInit();

	STestObjectFreedNotifier	sNotifier1;
	STestObjectFreedNotifier	sNotifier2;
	CTestObject*				pcTest1;
	CTestObject*				pcTest2;

	Ptr<CTestObject> pTest1 = OMalloc<CTestObject>(&sNotifier1);
	Ptr<CTestObject> pTest2 = OMalloc<CTestObject>(&sNotifier2);

	AssertInt(0, pTest1->NumHeapFroms());
	AssertInt(1, pTest1->NumStackFroms());
	AssertInt(0, pTest1->NumPointerTos());
	AssertInt(0, pTest2->NumHeapFroms());
	AssertInt(1, pTest2->NumStackFroms());
	AssertInt(0, pTest2->NumPointerTos());
	AssertFalse(sNotifier1.bFreed);
	AssertFalse(sNotifier2.bFreed);

	pTest2->mpObject = pTest1;

	AssertInt(1, pTest1->NumHeapFroms());
	AssertInt(1, pTest1->NumStackFroms());
	AssertInt(0, pTest1->NumPointerTos());
	AssertInt(0, pTest2->NumHeapFroms());
	AssertInt(1, pTest2->NumStackFroms());
	AssertInt(1, pTest2->NumPointerTos());

	pcTest2 = (CTestObject*)pTest2.Object();
	pcTest1 = (CTestObject*)pTest1.Object();
	pTest1 = NULL;  //pTest1 should not be killed here, even though it has no stack froms.  It still has a heap from.

	AssertFalse(sNotifier1.bFreed);
	AssertFalse(sNotifier2.bFreed);
	AssertInt(1, pcTest1->NumHeapFroms());
	AssertInt(0, pcTest1->NumStackFroms());
	AssertInt(0, pcTest1->NumPointerTos());
	AssertInt(0, pcTest2->NumHeapFroms());
	AssertInt(1, pcTest2->NumStackFroms());
	AssertInt(1, pcTest2->NumPointerTos());

	ObjectsFlush();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPointer(void)
{
	BeginTests();
	MemoryInit();
	TypesInit();
	DataIOInit();

	TestPointerConstructor();
	TestPointerDestructor();
	TestPointerStackToEmbedded();
	TestPointerAssignmentSimple();
	TestPointerAssignmentStackToObjectPointer();
	TestPointerAssignmentObjectToObjectPointer();
	TestPointerNegation();
	TestPointerHeapNotInGraphFreeStack();

	DataIOKill();
	TypesKill();
	MemoryKill();
	TestStatistics();
}

