#include "BaseLib/GlobalMemory.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/TypeNames.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/MemoryFile.h"
#include "StandardLib/Objects.h"
#include "StandardLib/String.h"
#include "TestLib/Assert.h"
#include "ObjectTestClasses.h"
#include "CollectionObjectTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectFreeOrderingOutOfOrderOnStack(void)
{
	ObjectsInit();
	{
		Ptr<CTestObject>			pObject1;
		Ptr<CTestNesHolderObject>	pNesHolder1;
		Ptr<CTestNesHolderObject>	pNesHolder2;
		Ptr<CTestObject>			pObject2;
		STestObjectFreedNotifier	sFreeNotifierO1;
		STestObjectFreedNotifier	sFreeNotifierN1;
		STestObjectFreedNotifier	sFreeNotifierN2;
		STestObjectFreedNotifier	sFreeNotifierO2;
		CArrayEmbeddedObjectPtrE8	apNesObjects;
		CEmbeddedObject*			pcExpectedNesPointerToObject;
		

		AssertSize(0, gcObjects.NumMemoryIndexes());

		pObject1 = OMalloc<CTestObject>(&sFreeNotifierO1);
		pNesHolder1 = OMalloc<CTestNesHolderObject>(&sFreeNotifierN1, pObject1);
		pNesHolder2 = OMalloc<CTestNesHolderObject>(&sFreeNotifierN2, (CPointer)NULL);
		pObject2 = OMalloc<CTestObject>(&sFreeNotifierO2);
		pNesHolder2->SetObject(pObject2);

		AssertSize(1, pObject1->NumHeapFroms());
		AssertSize(0, pNesHolder1->NumHeapFroms());
		AssertSize(0, pNesHolder2->NumHeapFroms());
		AssertSize(1, pObject2->NumHeapFroms());

		apNesObjects.Init();
		pObject1->GetNesPointerToThis(&apNesObjects);
		AssertSize(1, apNesObjects.NumElements());
		pcExpectedNesPointerToObject = apNesObjects.GetPtr(0);
		AssertPointer(pNesHolder1.Object(), pcExpectedNesPointerToObject);
		apNesObjects.Kill();

		apNesObjects.Init();
		pObject2->GetNesPointerToThis(&apNesObjects);
		AssertSize(1, apNesObjects.NumElements());
		pcExpectedNesPointerToObject = apNesObjects.GetPtr(0);
		AssertPointer(pNesHolder2.Object(), pcExpectedNesPointerToObject);
		apNesObjects.Kill();
	}
	AssertSize(0, gcObjects.NumMemoryIndexes());
	ObjectsKill();
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectFreeOrderingAllocate(bool bHolderFirst, Ptr<CTestObject>& pObject, STestObjectFreedNotifier* psFreeNotifierObject, STestObjectFreedNotifier* psFreeNotifierHolder)
{
	Ptr<CTestNesHolderObject>	pHolder;

	if (bHolderFirst)
	{
		pHolder = OMalloc<CTestNesHolderObject>(psFreeNotifierHolder, (CPointer)NULL);
		pObject = OMalloc<CTestObject>(psFreeNotifierObject);
		pHolder->SetObject(pObject);
	}
	else
	{
		pObject = OMalloc<CTestObject>(psFreeNotifierObject);
		pHolder = OMalloc<CTestNesHolderObject>(psFreeNotifierHolder, pObject);
	}

	//The holder is only reachable through the Object it depends on.
	pObject->mpObject = pHolder;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectFreeOrderingScopeExit(bool bHolderFirst)
{
	STestObjectFreedNotifier	sFreeNotifierObject;
	STestObjectFreedNotifier	sFreeNotifierHolder;

	ObjectsInit();
	{
		Ptr<CTestObject>	pObject;

		TestObjectFreeOrderingAllocate(bHolderFirst, pObject, &sFreeNotifierObject, &sFreeNotifierHolder);
		AssertSize(2, gcObjects.NumMemoryIndexes());
		AssertFalse(sFreeNotifierObject.bFreed);
		AssertFalse(sFreeNotifierHolder.bFreed);
	}
	AssertTrue(sFreeNotifierObject.bFreed);
	AssertTrue(sFreeNotifierHolder.bFreed);
	AssertFalse(sFreeNotifierHolder.bDependsOnFreedFirst);
	AssertSize(0, gcObjects.NumMemoryIndexes());
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectFreeOrderingExplicitKill(bool bHolderFirst)
{
	STestObjectFreedNotifier	sFreeNotifierObject;
	STestObjectFreedNotifier	sFreeNotifierHolder;

	ObjectsInit();
	{
		Ptr<CTestObject>	pObject;

		TestObjectFreeOrderingAllocate(bHolderFirst, pObject, &sFreeNotifierObject, &sFreeNotifierHolder);
		AssertSize(2, gcObjects.NumMemoryIndexes());

		pObject->Kill();
		AssertTrue(sFreeNotifierObject.bFreed);
		AssertTrue(sFreeNotifierHolder.bFreed);
		AssertFalse(sFreeNotifierHolder.bDependsOnFreedFirst);
		AssertSize(0, gcObjects.NumMemoryIndexes());
	}
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectFreeOrderingCollection(bool bExplicitKill)
{
	STestObjectFreedNotifier	sFreeNotifierObject;
	size						uiNumChildrenWhenFreed;

	uiNumChildrenWhenFreed = 99;
	ObjectsInit();
	{
		Ptr<CTestObject>		pObject;
		Ptr<CTestArrayObject>	pHolder;

		pObject = OMalloc<CTestObject>(&sFreeNotifierObject);
		pHolder = OMalloc<CTestArrayObject>(0);
		pHolder->mpuiNumChildrenWhenFreed = &uiNumChildrenWhenFreed;
		pHolder->maChildren.Add(pObject);

		//The holder is only reachable through the Object in its array.
		pObject->mpObject = pHolder;
		pHolder = NULL;
		AssertSize(2, gcObjects.NumMemoryIndexes());

		if (bExplicitKill)
		{
			pObject->Kill();
		}
		else
		{
			pObject = NULL;
		}
		AssertTrue(sFreeNotifierObject.bFreed);
		AssertSize(0, gcObjects.NumMemoryIndexes());
	}

	if (bExplicitKill)
	{
		//KillInternal only puts back pointer fields from Objects killed with the killed Object, not collection entries.
		//So the holder's array has already lost the killed Object when the holder is freed.
		AssertSize(0, uiNumChildrenWhenFreed);
	}
	else
	{
		AssertSize(1, uiNumChildrenWhenFreed);
	}
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectFreeOrdering(void)
{
	BeginTests();
	MemoryInit();
	FastFunctionsInit();
	TypesInit();
	DataIOInit();

	TestObjectFreeOrderingOutOfOrderOnStack();
	TestObjectFreeOrderingScopeExit(false);
	TestObjectFreeOrderingScopeExit(true);
	TestObjectFreeOrderingExplicitKill(false);
	TestObjectFreeOrderingExplicitKill(true);
	TestObjectFreeOrderingCollection(false);
	TestObjectFreeOrderingCollection(true);

	DataIOKill();
	TypesKill();
	FastFunctionsKill();
	MemoryKill();
	TestStatistics();
}

