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

	DataIOKill();
	TypesKill();
	FastFunctionsKill();
	MemoryKill();
	TestStatistics();
}

