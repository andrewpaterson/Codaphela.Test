#include "StandardLib/ArrayCommonObject.h"
#include "StandardLib/Objects.h"
#include "TestLib/Assert.h"
#include "ObjectTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayCommonPointerRemapping(void)
{
	Ptr<CArrayCommonObject>		pArray;
	Ptr<CRoot>					pRoot;
	Ptr<CTestObject>			pObject1;
	Ptr<CTestSaveableObject1>	pObject2;
	Ptr<CTestSaveableObject1>	pObject3;
	STestObjectKilledNotifier	sKillNotifier;
	CPointer					pNull;
	int							iNumRemapped;
	CTestObject*				pcObject1;
	
	ObjectsInit();

	pRoot = ORoot();
	pArray = OMalloc(CArrayCommonObject);
	pArray->Init(FALSE, FALSE, TRUE, 1);
	pRoot->Add(pArray);

	pObject1 = OMalloc(CTestObject);
	pObject2 = ONMalloc(CTestSaveableObject1, "Fred");
	pObject3 = ONMalloc(CTestSaveableObject1, "Barney");
	pNull = NULL;

	pArray->Add(pNull);
	pArray->Add(pObject2);
	pArray->Add(pObject1);
	pArray->Add(pObject2);
	pArray->Add(pObject1);
	pArray->Add(pObject2);
	AssertInt(6, pArray->NumElements());
	AssertInt(5, pArray->NonNullElements());

	sKillNotifier.bKilled = FALSE;
	pObject1->Init(&sKillNotifier);
	pObject2->Init();
	pObject3->Init();

	AssertInt(5, pArray->NumTos());
	AssertInt(1, pArray->NumHeapFroms());
	AssertInt(2, pObject1->NumHeapFroms());
	AssertInt(0, pObject1->NumTos());
	AssertInt(3, pObject2->NumHeapFroms());
	AssertInt(0, pObject2->NumTos());
	AssertInt(0, pObject3->NumHeapFroms());
	AssertInt(0, pObject3->NumTos());

	pcObject1 = (CTestObject*)pObject1.Object();
	iNumRemapped = pObject1.MorphInto(&pObject3);
	AssertInt(2, iNumRemapped);

	AssertInt(6, pArray->NumElements());
	AssertInt(5, pArray->NonNullElements());
	AssertNull(pArray->UnsafeGet(0));
	AssertPointer(&pObject2, pArray->UnsafeGet(1));
	AssertPointer(&pObject3, pArray->UnsafeGet(2));
	AssertPointer(&pObject2, pArray->UnsafeGet(3));
	AssertPointer(&pObject3, pArray->UnsafeGet(4));
	AssertPointer(&pObject2, pArray->UnsafeGet(5));

	AssertInt(5, pArray->NumTos());
	AssertInt(1, pArray->NumHeapFroms());
	AssertTrue(sKillNotifier.bKilled);
	AssertInt(3, pObject2->NumHeapFroms());
	AssertInt(0, pObject2->NumTos());
	AssertInt(2, pObject3->NumHeapFroms());
	AssertInt(0, pObject3->NumTos());

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayCommonObject(void)
{
	BeginTests();

	TestArrayCommonPointerRemapping();

	TestStatistics();
}

