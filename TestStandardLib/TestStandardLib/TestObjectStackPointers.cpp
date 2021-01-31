#include "BaseLib/GlobalMemory.h"
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

	STestObjectFreedNotifier	sNotifier;

	Ptr<CTestObject> ptr = OMalloc(CTestObject);
	ptr->Init(&sNotifier);

	AssertInt(1, ptr->NumStackFroms());
	AssertFalse(sNotifier.bFreed);

	ptr = NULL;

	AssertTrue(sNotifier.bFreed);

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectStackPointersSingleWithRoot(void)
{
	ObjectsInit();

	STestObjectFreedNotifier	sNotifier;

	Ptr<CTestObject> ptr = OMalloc(CTestObject);
	ptr->Init(&sNotifier);

	AssertInt(1, ptr->NumStackFroms());
	AssertFalse(sNotifier.bFreed);
	
	Ptr<CRoot>	pRoot = ORoot();
	pRoot->Add(ptr);

	CTestObject*	pcTest;
	pcTest = &ptr;
	ptr = NULL;

	AssertFalse(sNotifier.bFreed);

	pRoot->Remove(pcTest);

	AssertTrue(sNotifier.bFreed);

	pRoot = NULL;

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectStackPointers(void)
{
	BeginTests();
	MemoryInit();

	TestObjectStackPointersSingle();
	TestObjectStackPointersSingleWithRoot();

	MemoryKill();
	TestStatistics();
}

