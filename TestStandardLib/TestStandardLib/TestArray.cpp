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

	Ptr<CArray<CTestSaveableObject1>> pacStuff = OMalloc(CArray<CTestSaveableObject1>)->Init();
	pacStuff->Add(OMalloc(CTestSaveableObject1)->Init());

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

	Ptr<CArray<CTestSaveableObject1>> pacStuff = OMalloc(CArray<CTestSaveableObject1>)->Init();
	pacStuff->Add(OMalloc(CTestSaveableObject1)->Init());
	Ptr<CTestSaveableObject1> pSaveable = OMalloc(CTestSaveableObject1)->Init();
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

	Ptr<CArray<CTestSaveableObject1>> pacStuff = OMalloc(CArray<CTestSaveableObject1>)->Init();
	pacStuff->Add(OMalloc(CTestSaveableObject1)->Init());
	Ptr<CTestSaveableObject1> pSaveable = OMalloc(CTestSaveableObject1)->Init();
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

	Ptr<CArray<CTestSaveableObject1>> pacStuff = OMalloc(CArray<CTestSaveableObject1>)->Init();
	pacStuff->Add(OMalloc(CTestSaveableObject1)->Init());
	Ptr<CTestSaveableObject1> pSaveable = OMalloc(CTestSaveableObject1)->Init();
	pSaveable->miInt = 3;
	pacStuff->Insert(0, pSaveable);

	Ptr<CArray<CTestSaveableObject1>> pacMore = OMalloc(CArray<CTestSaveableObject1>)->Init();
	pSaveable = OMalloc(CTestSaveableObject1)->Init();
	pSaveable->miInt = 5;
	pacStuff->Insert(0, pSaveable);

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

	Ptr<CArray<CTestSaveableObject1>> pacStuff = OMalloc(CArray<CTestSaveableObject1>)->Init();
	pRoot->Add(pacStuff);

	pacStuff->Add(OMalloc(CTestSaveableObject1)->Init());
	Ptr<CTestSaveableObject1> pSaveable = OMalloc(CTestSaveableObject1)->Init();
	pSaveable->miInt = 3;
	pacStuff->Insert(0, pSaveable);
	pSaveable = OMalloc(CTestSaveableObject1)->Init();
	pSaveable->miInt = 5;
	pacStuff->Insert(0, pSaveable);

	pacStuff->RemoveAt(1);

	AssertInt(2, pacStuff->NumElements());
	AssertInt(5, pacStuff->Get(0)->miInt);
	AssertInt(7, pacStuff->Get(1)->miInt);

	pacStuff->KillAll();

	AssertInt(0, pacStuff->NumElements());

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArray(void)
{
	BeginTests();

	TestArrayAdd();
	TestArrayGet();
	TestArrayInsert();
	TestArrayAddAll();
	TestArrayRemove();

	TestStatistics();
}

