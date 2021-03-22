#include "BaseLib/GlobalMemory.h"
#include "StandardLib/Objects.h"
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
	Ptr<CTestNamedObject>	pNamed;
	Ptr<CTestNamedObject>	pTemp;

	MemoryInit();
	ObjectsInit();

	TestObjectAllocatorAddConstructors();

	pNamed = gcObjects.AllocateNew("CTestNamedObject");
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
	Ptr<CTestNamedObject>	pNamed1;
	Ptr<CTestNamedObject>	pNamed2;
	Ptr<CTestNamedObject>	pTemp;
	SLogConfig				sLogConfig;

	MemoryInit();
	ObjectsInit();

	TestObjectAllocatorAddConstructors();
	AssertLongLongInt(0, gcObjects.NumMemoryIndexes());

	pNamed1 = gcObjects.AllocateNewNamed("CTestNamedObject", "My Object Name");
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

	gcLogger.GetConfig(&sLogConfig);
	gcLogger.SetBreakOnError(FALSE);
	pNamed2 = gcObjects.AllocateNewNamed("CTestNamedObject", "My Object Name");
	gcLogger.SetConfig(&sLogConfig);

	AssertNull(pNamed2.Object());
	AssertLongLongInt(1, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(NULL_O_INDEX, pNamed2.GetIndex());

	AssertLongLongInt(1LL, pNamed1.GetIndex());
	AssertString("My Object Name", pNamed1.GetName());

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
	Ptr<CTestNamedObject>	pNamed1;
	Ptr<CTestNamedObject>	pNamed2;
	Ptr<CTestNamedObject>	pTemp;

	MemoryInit();
	ObjectsInit();

	TestObjectAllocatorAddConstructors();

	AssertLongLongInt(0, gcObjects.NumMemoryIndexes());

	pNamed1 = gcObjects.AllocateNewNamed("CTestNamedObject", "My Object Name");
	pNamed1->Init(1);
	AssertLongLongInt(1LL, pNamed1.GetIndex());
	AssertString("My Object Name", pNamed1.GetName());

	AssertLongLongInt(1, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(1, gcObjects.NumMemoryNames());

	pNamed2 = gcObjects.AllocateExistingNamed("CTestNamedObject", "My Object Name");
	pNamed2->Init(2);
	AssertNotNull(pNamed2.Object());
	AssertLongLongInt(1LL, pNamed2.GetIndex());
	AssertString("My Object Name", pNamed2.GetName());
	AssertLongLongInt(1, gcObjects.NumMemoryIndexes());

	pNamed1 = gcObjects.Get(1LL);
	AssertNotNull(pNamed1.Object());
	AssertInt(2, pNamed1->miNum);
	AssertInt(2, pNamed2->miNum);
	AssertPointer(pNamed2.Object(), pNamed1.Object());

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

	xxx;  //Write more tests for Overwrite cases

	TestStatistics();
}


