#include "StandardLib/Objects.h"
#include "TestLib/Assert.h"
#include "ObjectTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectStackPointersSingle(void)
{
	ObjectsInit();

	STestObjectKilledNotifier	sNotifier;

	Ptr<CTestObject> ptr = OMalloc(CTestObject);
	ptr->Init(&sNotifier);

	AssertInt(1, ptr->NumStackFroms());
	AssertFalse(sNotifier.bKilled);

	ptr = NULL;

	AssertTrue(sNotifier.bKilled);

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectStackPointersSingleWithRoot(void)
{
	ObjectsInit();

	STestObjectKilledNotifier	sNotifier;

	Ptr<CTestObject> ptr = OMalloc(CTestObject);
	ptr->Init(&sNotifier);

	AssertInt(1, ptr->NumStackFroms());
	AssertFalse(sNotifier.bKilled);
	
	Ptr<CRoot>	pRoot = ORoot();
	pRoot->Add(ptr);

	ptr = NULL;

	AssertFalse(sNotifier.bKilled);

	pRoot->Remove(ptr);

	AssertTrue(sNotifier.bKilled);

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectStackPointers(void)
{
	TestObjectStackPointersSingle();
	TestObjectStackPointersSingleWithRoot();
}

