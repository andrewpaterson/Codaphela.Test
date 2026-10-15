#include "BaseLib/GlobalMemory.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/TypeNames.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/MemoryFile.h"
#include "StandardLib/Objects.h"
#include "StandardLib/String.h"
#include "TestLib/Assert.h"
#include "ObjectTestClasses.h"


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
void TestObjectFreeOrdering(void)
{
	BeginTests();
	MemoryInit();
	FastFunctionsInit();
	TypesInit();
	DataIOInit();

	TestObjectFreeOrderingOutOfOrderOnStack();

	DataIOKill();
	TypesKill();
	FastFunctionsKill();
	MemoryKill();
	TestStatistics();
}

