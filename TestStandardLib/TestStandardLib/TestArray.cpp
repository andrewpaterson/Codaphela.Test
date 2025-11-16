#include "BaseLib/GlobalMemory.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/TypeNames.h"
#include "StandardLib/Array.h"
#include "StandardLib/Objects.h"
#include "TestLib/Assert.h"
#include "ObjectTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayAdd(void)
{
	ObjectsInit();

	Ptr<CArray<CTestSaveableObject1>> pacStuff = OMalloc<CArray<CTestSaveableObject1>>();
	pacStuff->Add(OMalloc<CTestSaveableObject1>());

	Ptr<CTestSaveableObject1> pSaveable = pacStuff->Get(0);
	AssertTrue(pSaveable.IsNotNull());
	AssertInt(7, pSaveable->miInt);

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayGet(void)
{
	ObjectsInit();

	Ptr<CArray<CTestSaveableObject1>> pacStuff = OMalloc<CArray<CTestSaveableObject1>>();
	pacStuff->Add(OMalloc<CTestSaveableObject1>());
	Ptr<CTestSaveableObject1> pSaveable = OMalloc<CTestSaveableObject1>();
	pSaveable->miInt = 3;
	pacStuff->Add(pSaveable);

	AssertInt(2, pacStuff->NumElements());
	AssertInt(7, pacStuff->Get(0)->miInt);
	AssertInt(3, pacStuff->Get(1)->miInt);

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayInsert(void)
{
	ObjectsInit();

	Ptr<CArray<CTestSaveableObject1>> pacStuff = OMalloc<CArray<CTestSaveableObject1>>();
	pacStuff->Add(OMalloc<CTestSaveableObject1>());
	Ptr<CTestSaveableObject1> pSaveable = OMalloc<CTestSaveableObject1>();
	pSaveable->miInt = 3;
	pacStuff->Insert(0, pSaveable);

	AssertInt(2, pacStuff->NumElements());
	AssertInt(3, pacStuff->Get(0)->miInt);
	AssertInt(7, pacStuff->Get(1)->miInt);

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayAddAll(void)
{
	ObjectsInit();

	Ptr<CArray<CTestSaveableObject1>> pacStuff = OMalloc<CArray<CTestSaveableObject1>>();
	pacStuff->Add(OMalloc<CTestSaveableObject1>());
	Ptr<CTestSaveableObject1> pSaveable = OMalloc<CTestSaveableObject1>();
	pSaveable->miInt = 3;
	pacStuff->Insert(0, pSaveable);

	Ptr<CArray<CTestSaveableObject1>> pacMore = OMalloc<CArray<CTestSaveableObject1>>();
	pSaveable = OMalloc<CTestSaveableObject1>();
	pSaveable->miInt = 5;

	AssertInt(0, pSaveable->NumHeapFroms());
	pacStuff->Insert(0, pSaveable);
	AssertInt(1, pSaveable->NumHeapFroms());
	gcObjects.ValidateObjectsConsistency();

	pacMore->AddAll(pacStuff);

	AssertInt(3, pacMore->NumElements());
	AssertInt(5, pacMore->Get(0)->miInt);
	AssertInt(3, pacMore->Get(1)->miInt);
	AssertInt(7, pacMore->Get(2)->miInt);

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayRemove(void)
{
	ObjectsInit();

	Ptr<CRoot> pRoot = ORoot();

	Ptr<CArray<CTestSaveableObject1>> pacStuff = OMalloc<CArray<CTestSaveableObject1>>();
	pRoot->Add(pacStuff);

	pacStuff->Add(OMalloc<CTestSaveableObject1>());
	Ptr<CTestSaveableObject1> pSaveable = OMalloc<CTestSaveableObject1>();
	pSaveable->miInt = 3;
	pacStuff->Insert(0, pSaveable);
	pSaveable = OMalloc<CTestSaveableObject1>();
	pSaveable->miInt = 5;
	pacStuff->Insert(0, pSaveable);

	pacStuff->RemoveAt(1);

	AssertInt(2, pacStuff->NumElements());
	AssertInt(5, pacStuff->Get(0)->miInt);
	AssertInt(7, pacStuff->Get(1)->miInt);

	ObjectsFlush();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArraySneakyOnStack(void)
{
	ObjectsInit();

	CTestObject					aArray;
	STestObjectFreedNotifier	sFreed;
	SStackPointer*				psPointer;
	CBaseObject*				pcObject;

	AssertSize(0, gcStackPointers.NumElements());

	Ptr<CTestSimpleObject> pTestObject = OMalloc<CTestSimpleObject>(&sFreed, 23);
	AssertSize(1, gcStackPointers.NumElements());
	psPointer = gcStackPointers.Get(0);
	AssertTrue(psPointer->meType == SPT_Pointer);
	pcObject = psPointer->u.pcPointer->BaseObject();
	//The pointer 'pTestObject' is on the stack and pointes to a CTestSimpleObject.
	AssertPointer(pTestObject.BaseObject(), pcObject);

	AssertSize(1, gcStackPointers.NumElements());
	aArray.Init(pTestObject, NULL);
	AssertSize(2, gcStackPointers.NumElements());

	AssertFalse(sFreed.bFreed);
	pTestObject = NULL;
	AssertFalse(sFreed.bFreed);
	AssertSize(1, gcStackPointers.NumElements());

	aArray.Kill();
	AssertSize(0, gcStackPointers.NumElements());
	AssertTrue(sFreed.bFreed);

	ObjectsFlush();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayOnStackKill(void)
{
	ObjectsInit();

	CArray<CTestSimpleObject>	aArray;
	STestObjectFreedNotifier	sFreed;
	SStackPointer*				psPointer;
	CBaseObject*				pcObject;

	AssertSize(0, gcStackPointers.NumElements());

	Ptr<CTestSimpleObject> pTestObject = OMalloc<CTestSimpleObject>(&sFreed, 23);
	AssertSize(1, gcStackPointers.NumElements());
	psPointer = gcStackPointers.Get(0);
	AssertTrue(psPointer->meType == SPT_Pointer);
	pcObject = psPointer->u.pcPointer->BaseObject();
	//The pointer 'pTestObject' is on the stack and pointes to a CTestSimpleObject.
	AssertPointer(pTestObject.BaseObject(), pcObject);

	AssertSize(1, gcStackPointers.NumElements());
	aArray.Init();
	aArray.Add(pTestObject);
	AssertSize(2, gcStackPointers.NumElements());

	AssertFalse(sFreed.bFreed);
	pTestObject = NULL;
	AssertFalse(sFreed.bFreed);
	AssertSize(1, gcStackPointers.NumElements());

	aArray.Kill();
	AssertSize(0, gcStackPointers.NumElements());
	AssertTrue(sFreed.bFreed);

	ObjectsFlush();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayOnStackRemoveObject(void)
{
	ObjectsInit();

	CArray<CTestSimpleObject>	aArray;
	STestObjectFreedNotifier	sFreed;
	SStackPointer*				psPointer;
	CBaseObject*				pcObject;

	AssertSize(0, gcStackPointers.NumElements());
	AssertSize(0, gcObjects.NumMemoryIndexes());

	Ptr<CTestSimpleObject> pTestObject = OMalloc<CTestSimpleObject>(&sFreed, 23);
	AssertSize(1, gcStackPointers.NumElements());
	AssertSize(1, gcObjects.NumMemoryIndexes());
	psPointer = gcStackPointers.Get(0);
	AssertTrue(psPointer->meType == SPT_Pointer);
	pcObject = psPointer->u.pcPointer->BaseObject();
	//The pointer 'pTestObject' is on the stack and pointes to a CTestSimpleObject.
	AssertPointer(pTestObject.BaseObject(), pcObject);

	AssertSize(1, gcStackPointers.NumElements());
	aArray.Init();
	AssertSize(1, gcStackPointers.NumElements());
	aArray.Add(pTestObject);
	AssertSize(2, gcStackPointers.NumElements());
	AssertSize(1, aArray.NumElements());
	AssertSize(1, gcObjects.NumMemoryIndexes());

	aArray.Remove(pTestObject);
	AssertSize(1, gcStackPointers.NumElements());
	AssertSize(0, aArray.NumElements());
	AssertSize(1, gcObjects.NumMemoryIndexes());
	AssertFalse(sFreed.bFreed);

	pTestObject = NULL;
	AssertTrue(sFreed.bFreed);
	AssertSize(0, gcStackPointers.NumElements());
	AssertSize(0, gcObjects.NumMemoryIndexes());

	aArray.Kill();
	AssertSize(0, gcStackPointers.NumElements());

	ObjectsFlush();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArray(void)
{
	BeginTests();
	MemoryInit();
	FastFunctionsInit();
	TypesInit();
	DataIOInit();

	TestArrayAdd();
	TestArrayGet();
	TestArrayInsert();
	TestArrayAddAll();
	TestArrayRemove();
	TestArraySneakyOnStack();
	TestArrayOnStackKill();
	TestArrayOnStackRemoveObject();

	DataIOKill();
	TypesKill();
	FastFunctionsKill();
	MemoryKill();
	TestStatistics();
}

