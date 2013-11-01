#include "StandardLib/Objects.h"
#include "StandardLib/PointerContainer.h"
#include "TestLib/Assert.h"
#include "ObjectTestClasses.h"
#include "ObjectWriterChunkedTestClasses.h"
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

	pcObject = OMalloc(CTestObject);
	pcObject->Init(NULL);
	AssertFalse(!pcObject);

	pcObject = NULL;
	AssertTrue(!pcObject);

	pcBase = OMalloc(CTestObject);
	((CTestObject*)&pcBase)->Init(NULL);
	AssertFalse(!pcBase);

	pcBase = NULL;
	AssertTrue(!pcBase);

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

	cCluster.PreInit();
	cCluster.Init();
	AssertNull(cCluster.mpTest.Object());
	AssertPointer(&cCluster, cCluster.mpTest.Embedding());

	ObjectsKill();
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPointerDestructorDestruct(STestObjectKilledNotifier* psKillNotifier)
{
	CTestObject					cTestObject;

	AssertLongLongInt(0, gcObjects.NumMemoryIndexes());

	cTestObject.Init(NULL);
	cTestObject.mpTest = OMalloc(CTestObject)->Init(psKillNotifier);

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

	STestObjectKilledNotifier	sKillNotifier;

	TestPointerDestructorDestruct(&sKillNotifier);
	
	AssertTrue(sKillNotifier.bKilled);
	AssertLongLongInt(0, gcObjects.NumMemoryIndexes());

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPointerStackToEmbeddedDestruct(void)
{
	AssertLongLongInt(0, gcObjects.NumMemoryIndexes());
	Ptr<CEmbeddedContainer> pMissile = OMalloc(CEmbeddedContainer);

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

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPointerAssignmentSimple()
{
	ObjectsInit();

	Ptr<CTestWithArray>	pcObject1;
	pcObject1 = ONMalloc(CTestWithArray, "Urgle-burgle");
	pcObject1->Init("Warning", 17);

	AssertNotNull(&pcObject1);
	AssertLongLongInt(2, gcObjects.NumMemoryIndexes());

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPointerAssignmentStackToObjectPointer()
{
	ObjectsInit();

	Ptr<CTestNamedString>	pObject = ONMalloc(CTestNamedString, "Urgle-burgle");
	Ptr<CTestInteger>		pInteger = OMalloc(CTestInteger);

	pInteger->Init(6, 7, 6);
	pObject->Init(NULL, pInteger, "Embedded");

	AssertLongLongInt(2, gcObjects.GetStackPointers()->UsedPointers());

	Ptr<CTestInteger> ptr = pObject->mpAnother;

	AssertLongLongInt(3, gcObjects.GetStackPointers()->UsedPointers());

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

	Ptr<CTestNamedString>	pObject = ONMalloc(CTestNamedString, "Urgle-burgle");
	Ptr<CTestInteger>		pInteger = OMalloc(CTestInteger);

	pInteger->Init(6, 7, 6);
	pObject->Init(NULL, pInteger, "Embedded");

	AssertLongLongInt(2, gcObjects.GetStackPointers()->UsedPointers());

	Ptr<CTestInteger> ptr = pObject->mpAnother;

	AssertLongLongInt(3, gcObjects.GetStackPointers()->UsedPointers());

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

	STestObjectKilledNotifier	sNotifier1;
	STestObjectKilledNotifier	sNotifier2;
	CTestObject*				pcTest1;
	CTestObject*				pcTest2;

	Ptr<CTestObject> pTest1 = OMalloc(CTestObject)->Init(&sNotifier1);
	Ptr<CTestObject> pTest2 = OMalloc(CTestObject)->Init(&sNotifier2);

	AssertInt(0, pTest1->NumHeapFroms());
	AssertInt(1, pTest1->NumStackFroms());
	AssertInt(0, pTest1->NumTos());
	AssertInt(0, pTest2->NumHeapFroms());
	AssertInt(1, pTest2->NumStackFroms());
	AssertInt(0, pTest2->NumTos());
	AssertFalse(sNotifier1.bKilled);
	AssertFalse(sNotifier2.bKilled);

	pTest2->mpObject = pTest1;

	AssertInt(1, pTest1->NumHeapFroms());
	AssertInt(1, pTest1->NumStackFroms());
	AssertInt(0, pTest1->NumTos());
	AssertInt(0, pTest2->NumHeapFroms());
	AssertInt(1, pTest2->NumStackFroms());
	AssertInt(1, pTest2->NumTos());

	pcTest2 = (CTestObject*)pTest2.Object();
	pcTest1 = (CTestObject*)pTest1.Object();
	pTest1 = NULL;  //pTest1 should not be killed here, even though it has no stack froms.  It still has a heap from.

	AssertFalse(sNotifier1.bKilled);
	AssertFalse(sNotifier2.bKilled);
	AssertInt(1, pcTest1->NumHeapFroms());
	AssertInt(0, pcTest1->NumStackFroms());
	AssertInt(0, pcTest1->NumTos());
	AssertInt(0, pcTest2->NumHeapFroms());
	AssertInt(1, pcTest2->NumStackFroms());
	AssertInt(1, pcTest2->NumTos());

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPointer(void)
{
	BeginTests();

	TestPointerConstructor();
	TestPointerDestructor();
	TestPointerStackToEmbedded();
	TestPointerAssignmentSimple();
	TestPointerAssignmentStackToObjectPointer();
	TestPointerAssignmentObjectToObjectPointer();
	TestPointerNegation();
	TestPointerHeapNotInGraphFreeStack();

	TestStatistics();
}

