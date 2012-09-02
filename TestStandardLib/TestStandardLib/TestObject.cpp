#include "CoreLib/FunctionCaller.h"
#include "StandardLib/Parameters.h"
#include "StandardLib/Object.h"
#include "StandardLib/Objects.h"
#include "StandardLib/Pointer.h"
#include "StandardLib/Root.h"
#include "TestLib/Assert.h"
#include "ObjectTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectSize(void)
{
	ObjectsInit(NULL);

	AssertInt(12, sizeof(CUnknown));
	AssertInt(96, sizeof(CObject));
	AssertInt(136, sizeof(CRoot));
	AssertInt(112, sizeof(CSet));
	AssertInt(8, sizeof(CPointerObject));

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectPointerRemapping(void)
{
	CPointer<CRoot>					pRoot;
	CPointer<CTestObject>			pObject1;
	CPointer<CTestObject>			pObject2;
	CPointer<CTestObject>			pObject3;
	STestObjectKilledNotifier		sKillNotifier1;
	STestObjectKilledNotifier		sKillNotifier2;
	STestObjectKilledNotifier		sKillNotifier3;
	int								iNumRemapped;

	ObjectsInit(NULL);

	pRoot = ORoot();

	pObject1 = OMalloc(CTestObject);
	pObject2 = OMalloc(CTestObject);
	pObject3 = OMalloc(CTestObject);

	sKillNotifier1.bKilled = FALSE;
	sKillNotifier2.bKilled = FALSE;
	sKillNotifier3.bKilled = FALSE;

	pObject1->Init(&sKillNotifier1);
	pObject2->Init(&sKillNotifier2);
	pObject3->Init(&sKillNotifier3);

	pRoot->Add(pObject1);
	pObject1->mpObject = pObject2;

	AssertInt(1, pObject1->NumTos());
	AssertInt(1, pObject1->NumFroms());
	AssertInt(0, pObject2->NumTos());
	AssertInt(1, pObject2->NumFroms());
	AssertInt(0, pObject3->NumTos());
	AssertInt(0, pObject3->NumFroms());
	
	iNumRemapped = pObject3.RemapFrom(&pObject2);
	AssertInt(1, iNumRemapped);

	AssertPointer(&pObject3, &pObject1->mpObject);

	AssertInt(1, pObject1->NumTos());
	AssertInt(1, pObject1->NumFroms());
	AssertInt(0, pObject3->NumTos());
	AssertInt(1, pObject3->NumFroms());
	AssertInt(0, pObject2->NumTos());
	AssertInt(0, pObject2->NumFroms());

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectPointerRemappingKilling(void)
{
	CPointer<CRoot>					pRoot;
	CPointer<CTestObject>			pObject1;
	CPointer<CTestObject>			pObject2;
	CPointer<CTestObject>			pObject3;
	CPointer<CTestObject>			pObject4;
	CPointer<CTestObject>			pObject5;
	STestObjectKilledNotifier		sKillNotifier1;
	STestObjectKilledNotifier		sKillNotifier2;
	STestObjectKilledNotifier		sKillNotifier3;
	STestObjectKilledNotifier		sKillNotifier4;
	STestObjectKilledNotifier		sKillNotifier5;
	int								iNumRemapped;

	ObjectsInit(NULL);

	pRoot = ORoot();

	pObject1 = OMalloc(CTestObject);
	pObject2 = OMalloc(CTestObject);
	pObject3 = OMalloc(CTestObject);
	pObject4 = OMalloc(CTestObject);
	pObject5 = OMalloc(CTestObject);

	sKillNotifier1.bKilled = FALSE;
	sKillNotifier2.bKilled = FALSE;
	sKillNotifier3.bKilled = FALSE;
	sKillNotifier4.bKilled = FALSE;
	sKillNotifier5.bKilled = FALSE;

	pObject1->Init(&sKillNotifier1);
	pObject2->Init(&sKillNotifier2);
	pObject3->Init(&sKillNotifier3);
	pObject4->Init(&sKillNotifier4);
	pObject5->Init(&sKillNotifier5);

	pRoot->Add(pObject1);
	pObject1->mpObject = pObject2;
	pObject2->mpObject = pObject3;

	pObject4->mpObject = pObject5;

	iNumRemapped = pObject4.RemapFrom(&pObject2);
	AssertInt(1, iNumRemapped);

	AssertPointer(&pObject4, &pObject1->mpObject);
	AssertPointer(&pObject5, &pObject4->mpObject);

	AssertTrue(sKillNotifier2.bKilled);
	AssertTrue(sKillNotifier3.bKilled);

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObject(void)
{
	BeginTests();

	TestObjectSize();
	TestObjectPointerRemapping();
	TestObjectPointerRemappingKilling();

	TestStatistics();
}

