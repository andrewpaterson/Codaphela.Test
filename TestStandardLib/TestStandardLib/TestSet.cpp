#include "StandardLib/Set.h"
#include "StandardLib/Objects.h"
#include "TestLib/Assert.h"
#include "ObjectTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSetAdd(void)
{
	ObjectsInit();

	Ptr<CSet<CTestSaveableObject1>> pacStuff = OMalloc(CSet<CTestSaveableObject1>)->Init();
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
void TestSetGet(void)
{
	ObjectsInit();

	Ptr<CSet<CTestSaveableObject1>> pacStuff = OMalloc(CSet<CTestSaveableObject1>)->Init();
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
void TestSetAddAll(void)
{
	ObjectsInit();

	Ptr<CSet<CTestSaveableObject1>> pacStuff = OMalloc(CSet<CTestSaveableObject1>)->Init();
	pacStuff->Add(OMalloc(CTestSaveableObject1)->Init());
	Ptr<CTestSaveableObject1> pSaveable = OMalloc(CTestSaveableObject1)->Init();
	pSaveable->miInt = 3;
	pacStuff->Add(pSaveable);

	Ptr<CSet<CTestSaveableObject1>> pacMore = OMalloc(CSet<CTestSaveableObject1>)->Init();
	pSaveable = OMalloc(CTestSaveableObject1)->Init();
	pSaveable->miInt = 5;
	pacStuff->Add(pSaveable);

	pacMore->AddAll(pacStuff);

	AssertInt(3, pacMore->NumElements());
	AssertInt(7, pacMore->Get(0)->miInt);
	AssertInt(3, pacMore->Get(1)->miInt);
	AssertInt(5, pacMore->Get(2)->miInt);

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSetRemove(void)
{
	ObjectsInit();

	Ptr<CRoot> pRoot = ORoot();

	Ptr<CSet<CTestSaveableObject1>> pacStuff = OMalloc(CSet<CTestSaveableObject1>)->Init();
	pRoot->Add(pacStuff);

	pacStuff->Add(OMalloc(CTestSaveableObject1)->Init());
	Ptr<CTestSaveableObject1> pSaveable = OMalloc(CTestSaveableObject1)->Init();
	pSaveable->miInt = 3;
	pacStuff->Add(pSaveable);
	pSaveable = OMalloc(CTestSaveableObject1)->Init();
	pSaveable->miInt = 5;
	pacStuff->Add(pSaveable);

	pacStuff->Remove(pSaveable);

	AssertInt(2, pacStuff->NumElements());
	AssertInt(7, pacStuff->Get(0)->miInt);
	AssertInt(3, pacStuff->Get(1)->miInt);

	pacStuff->KillAll();

	AssertInt(0, pacStuff->NumElements());

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSet(void)
{
	BeginTests();

	TestSetAdd();
	TestSetGet();
	TestSetAddAll();
	TestSetRemove();

	TestStatistics();
}

