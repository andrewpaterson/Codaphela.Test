#include "BaseLib/GlobalMemory.h"
#include "StandardLib/Objects.h"
#include "StandardLib/ObjectAllocator.h"
#include "TestLib/Assert.h"
#include "NamedObjectTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectAllocatorAddConstructors(void)
{
	gcObjects.AddConstructor<CRoot>();
	gcObjects.AddConstructor<CTestNamedObject>();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectAllocatorSimpleAdd(void)
{
	CObjectAllocator			cAllocator;
	Ptr<CTestNamedObject>	pNamed;
	Ptr<CTestNamedObject>	pTemp;

	MemoryInit();
	ObjectsInit();

	TestObjectAllocatorAddConstructors();
	cAllocator.Init(&gcObjects);

	pNamed = cAllocator.AllocateNew("CTestNamedObject");
	AssertNotNull(pNamed.Object());

	AssertLongLongInt(1LL, pNamed.GetIndex());
	AssertString("", pNamed.GetName());

	pTemp = gcObjects.Get("");
	AssertNull(pTemp.Object());
	pTemp = gcObjects.Get(1LL);
	AssertPointer(pNamed.Object(), pTemp.Object());

	ObjectsFlush();
	ObjectsKill();
	MemoryKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectAllocatorNamedAdd(void)
{
	CObjectAllocator		cAllocator;
	Ptr<CTestNamedObject>	pNamed1;
	Ptr<CTestNamedObject>	pNamed2;
	Ptr<CTestNamedObject>	pTemp;

	MemoryInit();
	ObjectsInit();

	TestObjectAllocatorAddConstructors();
	cAllocator.Init(&gcObjects);

	pNamed1 = cAllocator.AllocateNewMaybeReplaceExisting("CTestNamedObject", "My Object Name");
	AssertNotNull(pNamed1.Object());
	AssertLongLongInt(1, gcObjects.NumMemoryIndexes());
	AssertFalse(pNamed1->IsInitialised());
	pNamed1->Init(98);
	AssertTrue(pNamed1->IsInitialised());

	AssertLongLongInt(1LL, pNamed1.GetIndex());
	AssertString("My Object Name", pNamed1.GetName());
	AssertInt(98, pNamed1->miNum);

	pTemp = gcObjects.Get("My Object Name");
	AssertPointer(pNamed1.Object(), pTemp.Object());

	//This should fail or AllocateExisting should be called.
	pNamed2 = cAllocator.AllocateNewMaybeReplaceExisting("CTestNamedObject", "My Object Name");
	AssertNotNull(pNamed2.Object());
	AssertLongLongInt(1, gcObjects.NumMemoryIndexes());
	pNamed1->Init(66);

	AssertLongLongInt(1LL, pNamed2.GetIndex());
	AssertString("My Object Name", pNamed2.GetName());
	AssertInt(66, pNamed2->miNum);

	AssertLongLongInt(1LL, pNamed1.GetIndex());
	AssertString("My Object Name", pNamed1.GetName());
	AssertInt(66, pNamed2->miNum);

	ObjectsFlush();
	ObjectsKill();
	MemoryKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectAllocatorNamedOverwrite(void)
{
	CObjectAllocator		cAllocator;
	Ptr<CTestNamedObject>	pNamed1;
	Ptr<CTestNamedObject>	pNamed2;
	Ptr<CTestNamedObject>	pTemp;

	MemoryInit();
	ObjectsInit();

	TestObjectAllocatorAddConstructors();
	cAllocator.Init(&gcObjects);

	AssertLongLongInt(0, gcObjects.NumMemoryIndexes());

	pNamed1 = cAllocator.AllocateNewMaybeReplaceExisting("CTestNamedObject", "My Object Name");
	AssertLongLongInt(1LL, pNamed1.GetIndex());

	AssertLongLongInt(1, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(1, gcObjects.NumMemoryNames());

	//This should fail or AllocateExisting should be called.
	pNamed2 = cAllocator.AllocateNewMaybeReplaceExisting("CTestNamedObject", "My Object Name");
	AssertNotNull(pNamed2.Object());
	AssertLongLongInt(2LL, pNamed2.GetIndex());
	AssertString("My Object Name", pNamed2.GetName());
	AssertLongLongInt(1, gcObjects.NumMemoryIndexes());

	pNamed1 = gcObjects.Get(1LL);
	AssertNull(pNamed1.Object());

	AssertLongLongInt(1, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(1, gcObjects.NumMemoryNames());

	pTemp = gcObjects.Get("My Object Name");
	AssertPointer(pNamed2.Object(), pTemp.Object());

	ObjectsFlush();
	ObjectsKill();
	MemoryKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectAllocator(void)
{
	BeginTests();

	TestObjectAllocatorSimpleAdd();
	TestObjectAllocatorNamedAdd();
	TestObjectAllocatorNamedOverwrite();

	TestStatistics();
}


