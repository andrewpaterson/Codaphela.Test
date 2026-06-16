#include "BaseLib/GlobalMemory.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/TypeNames.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/MemoryFile.h"
#include "BaseLib/Codabase.h"
#include "BaseLib/CodabaseFactory.h"
#include "BaseLib/SequenceFactory.h"
#include "StandardLib/Objects.h"
#include "StandardLib/String.h"
#include "TestLib/Assert.h"
#include "CollectionObjectTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectFreeSelfCyclicPointer(void)
{
	ObjectsInit();
	{
		Ptr<CTestObject>						pObject;
		CArrayTemplateEmbeddedBaseObjectPtr		apcHeapFroms;
		CArrayStackPointer						apcStackFroms;
		CBaseObject*							pcObject1;
		CBaseObject*							pcObject2;
		CPointer*								pcPointer;

		AssertSize(0, gcObjects.NumMemoryIndexes());

		pObject = OMalloc<CTestObject>();
		pObject->mpTest = pObject;
		AssertSize(1, pObject.NumHeapFroms());

		pObject->mpObject = pObject;

		AssertSize(2, pObject.NumHeapFroms());
		apcHeapFroms.Init();
		pObject->GetHeapFroms(&apcHeapFroms);
		pcObject1 = *apcHeapFroms.Get(0);
		pcObject2 = *apcHeapFroms.Get(1);
		apcHeapFroms.Kill();

		AssertPointer(&pObject, pcObject1);
		AssertPointer(&pObject, pcObject2);

		AssertSize(1, pObject.NumStackFroms());
		apcStackFroms.Init();
		pObject->GetStackFroms(&apcStackFroms);
		pcPointer = apcStackFroms.Get(0)->u.pcPointer;
		apcStackFroms.Kill();
		AssertPointer(pObject.This(), pcPointer);

		AssertSize(1, gcObjects.NumMemoryIndexes());

		pObject = NULL;

		AssertSize(0, gcObjects.NumMemoryIndexes());
	}
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectFreeLoopCyclicPointer(void)
{
	ObjectsInit();
	{
		Ptr<CTestObject>						pObject;
		CArrayTemplateEmbeddedBaseObjectPtr		apcHeapFroms;
		CArrayStackPointer						apcStackFroms;
		CBaseObject*							pcObject1;
		CBaseObject*							pcObject2;
		CPointer*								pcPointer;

		AssertSize(0, gcObjects.NumMemoryIndexes());

		pObject = OMalloc<CTestObject>();
		pObject->AllocateTest();
		AssertSize(0, pObject.NumHeapFroms());
		AssertSize(2, gcObjects.NumMemoryIndexes());
		pObject->mpTest->mpTest = pObject;
		pcObject1 = &pObject->mpTest;

		AssertSize(1, pObject.NumHeapFroms());
		apcHeapFroms.Init();
		pObject->GetHeapFroms(&apcHeapFroms);
		pcObject2 = *apcHeapFroms.Get(0);
		apcHeapFroms.Kill();

		AssertPointer(pcObject1, pcObject2);

		AssertSize(1, pObject.NumStackFroms());
		apcStackFroms.Init();
		pObject->GetStackFroms(&apcStackFroms);
		pcPointer = apcStackFroms.Get(0)->u.pcPointer;
		apcStackFroms.Kill();
		AssertPointer(pObject.This(), pcPointer);

		pObject = NULL;

		AssertSize(0, gcObjects.NumMemoryIndexes());
	}
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectFreeLoopCollectionCyclicPointer(void)
{
	ObjectsInit();
	{
		Ptr<CTestArrayObject>					pObject;
		CArrayTemplateEmbeddedBaseObjectPtr		apcHeapFroms;
		CArrayStackPointer						apcStackFroms;
		CBaseObject*							pcObject2;
		CPointer*								pcPointer;

		AssertSize(0, gcObjects.NumMemoryIndexes());

		pObject = OMalloc<CTestArrayObject>(3);
		pObject->AllocateTest();
		AssertSize(0, pObject.NumHeapFroms());
		AssertSize(2, gcObjects.NumMemoryIndexes());
		pObject->Get(0)->mpTest = pObject;

		AssertSize(1, pObject.NumHeapFroms());
		apcHeapFroms.Init();
		pObject->GetHeapFroms(&apcHeapFroms);
		pcObject2 = *apcHeapFroms.Get(0);
		apcHeapFroms.Kill();

		AssertSize(1, pObject.NumStackFroms());
		apcStackFroms.Init();
		pObject->GetStackFroms(&apcStackFroms);
		pcPointer = apcStackFroms.Get(0)->u.pcPointer;
		apcStackFroms.Kill();
		AssertPointer(pObject.This(), pcPointer);

		pObject = NULL;

		AssertSize(0, gcObjects.NumMemoryIndexes());
	}
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectFreeStackWithCyclicHeapPointer(void)
{
	ObjectsInit();
	{
		STestObjectFreedNotifier	sFreed1;
		STestObjectFreedNotifier	sFreed2;
		Ptr<CTestObject>			pObject1;
		Ptr<CTestObject>			pObject2;
		CArrayStackPointer			apcStackFroms;
		CChars						sz;

		AssertSize(0, gcObjects.NumMemoryIndexes());

		pObject1 = OMalloc<CTestObject>(&sFreed1);
		pObject2 = OMalloc<CTestObject>(&sFreed2);

		pObject1->mpTest = pObject2;
		pObject2->mpTest = pObject1;
		
		AssertFalse(sFreed1.bFreed);
		AssertFalse(sFreed2.bFreed);
		AssertSize(1, pObject1.NumStackFroms());
		AssertSize(1, pObject2.NumStackFroms());
		AssertSize(2, gcObjects.NumMemoryIndexes());

		sz.Init();
		gcObjects.PrintStackPointers(&sz);
		AssertString("\
0: Pointer [CTestObject:1 Rx (CC, D, CA, CI, CC)]\n\
1: Pointer [CTestObject:2 Rx (CC, D, CA, CI, CC)]\n", sz.Text());
		sz.Kill();

		pObject1 = NULL;

		AssertFalse(sFreed1.bFreed);
		AssertFalse(sFreed2.bFreed);
		AssertSize(0, pObject1.NumStackFroms());
		AssertSize(1, pObject2.NumStackFroms());
		AssertSize(2, gcObjects.NumMemoryIndexes());

		sz.Init();
		gcObjects.PrintStackPointers(&sz);
		AssertString("\
0: Pointer [CTestObject:2 Rx (CC, D, CA, CI, CC)]\n", sz.Text());
		sz.Kill();

		pObject2 = NULL;

		AssertTrue(sFreed1.bFreed);
		AssertTrue(sFreed2.bFreed);
		AssertSize(0, pObject1.NumStackFroms());
		AssertSize(0, pObject2.NumStackFroms());
		AssertSize(0, gcObjects.NumMemoryIndexes());

		sz.Init();
		gcObjects.PrintStackPointers(&sz);
		AssertString("", sz.Text());
		sz.Kill();
	}
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectFreeStackWithCyclicHeapPointerHeapFrom(void)
{
	ObjectsInit();
	{
		STestObjectFreedNotifier	sFreed1;
		STestObjectFreedNotifier	sFreed2;
		STestObjectFreedNotifier	sFreedBase;
		Ptr<CTestObject>			pObject1;
		Ptr<CTestObject>			pObject2;
		Ptr<CTestObject>			pObjectBase;
		CArrayStackPointer			apcStackFroms;
		CChars						sz;

		AssertSize(0, gcObjects.NumMemoryIndexes());

		pObject1 = OMalloc<CTestObject>(&sFreed1);
		pObject2 = OMalloc<CTestObject>(&sFreed2);
		pObjectBase = OMalloc<CTestObject>(&sFreedBase);

		pObject1->mpTest = pObject2;
		pObject2->mpTest = pObject1;
		pObjectBase->mpTest = pObject1;

		sz.Init();
		gcObjects.PrintStackPointers(&sz);
		AssertString("\
0: Pointer [CTestObject:1 Rx (CC, D, CA, CI, CC)]\n\
1: Pointer [CTestObject:2 Rx (CC, D, CA, CI, CC)]\n\
2: Pointer [CTestObject:3 Rx (CC, D, CA, CI, CC)]\n", sz.Text());
		sz.Kill();

		pObject1 = NULL;
		pObject2 = NULL;

		AssertFalse(sFreed1.bFreed);
		AssertFalse(sFreed2.bFreed);
		AssertFalse(sFreedBase.bFreed);
		AssertSize(0, pObject1.NumStackFroms());
		AssertSize(0, pObject2.NumStackFroms());
		AssertSize(1, pObjectBase.NumStackFroms());
		AssertSize(3, gcObjects.NumMemoryIndexes());

		sz.Init();
		gcObjects.PrintStackPointers(&sz);
		AssertString("\
0: Pointer [CTestObject:3 Rx (CC, D, CA, CI, CC)]\n", sz.Text());
		sz.Kill();

	}
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectFreeStackWithCyclicHeapPointerRootFrom(void)
{
	ObjectsInit();
	{
		STestObjectFreedNotifier	sFreed1;
		STestObjectFreedNotifier	sFreed2;
		Ptr<CTestObject>			pObject1;
		Ptr<CTestObject>			pObject2;
		Ptr<CRoot>					pRoot;
		CArrayStackPointer			apcStackFroms;
		CChars						sz;

		AssertSize(0, gcObjects.NumMemoryIndexes());

		pObject1 = OMalloc<CTestObject>(&sFreed1);
		pObject2 = OMalloc<CTestObject>(&sFreed2);
		
		pRoot = ORoot();

		pObject1->mpTest = pObject2;
		pObject2->mpTest = pObject1;
		pRoot->Add(pObject1);

		sz.Init();
		gcObjects.PrintStackPointers(&sz);
		AssertString("\
0: Pointer [CTestObject:1 R2 (CC, D, CA, CI, CC)]\n\
1: Pointer [CTestObject:2 R3 (CC, D, CA, CI, CC)]\n\
2: Pointer [CRoot:3:\"GraphRoot\" R0 (CC, D, CA, CI, CC)]\n", sz.Text());
		sz.Kill();

		pObject1 = NULL;
		pObject2 = NULL;

		AssertFalse(sFreed1.bFreed);
		AssertFalse(sFreed2.bFreed);
		AssertSize(0, pObject1.NumStackFroms());
		AssertSize(0, pObject2.NumStackFroms());
		AssertSize(4, gcObjects.NumMemoryIndexes());

		sz.Init();
		gcObjects.PrintStackPointers(&sz);
		AssertString("\
0: Pointer [CRoot:3:\"GraphRoot\" R0 (CC, D, CA, CI, CC)]\n", sz.Text());
		sz.Kill();

		pRoot = NULL;

		AssertFalse(sFreed1.bFreed);
		AssertFalse(sFreed2.bFreed);
		AssertSize(4, gcObjects.NumMemoryIndexes());

		sz.Init();
		gcObjects.PrintStackPointers(&sz);
		AssertString("", sz.Text());
		sz.Kill();
	}
	ObjectsFlush();
	ObjectsKill();
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectFree(void)
{
	BeginTests();
	MemoryInit();
	FastFunctionsInit();
	TypesInit();
	DataIOInit();

	TestObjectFreeSelfCyclicPointer();
	TestObjectFreeLoopCyclicPointer();
	TestObjectFreeLoopCollectionCyclicPointer();
	TestObjectFreeStackWithCyclicHeapPointer();
	TestObjectFreeStackWithCyclicHeapPointerHeapFrom();
	TestObjectFreeStackWithCyclicHeapPointerRootFrom();

	DataIOKill();
	TypesKill();
	FastFunctionsKill();
	MemoryKill();
	TestStatistics();
}

