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
	CPointer<CTestNamedObject>	pNamed;
	CPointer<CTestNamedObject>	pTemp;

	ObjectsInit();

	TestObjectAllocatorAddConstructors();
	cAllocator.Init(&gcObjects, TRUE);

	pNamed = cAllocator.Add("CTestNamedObject");
	AssertNotNull(pNamed.Object());

	AssertLongLongInt(1LL, pNamed.GetIndex());
	AssertString("", pNamed.GetName());

	pTemp = gcObjects.Get("");
	AssertNull(pTemp.Object());
	pTemp = gcObjects.Get(1LL);
	AssertPointer(pNamed.Object(), pTemp.Object());

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectAllocatorNamedAdd(void)
{
	CObjectAllocator			cAllocator;
	CPointer<CTestNamedObject>	pNamed1;
	CPointer<CTestNamedObject>	pNamed2;
	CPointer<CTestNamedObject>	pTemp;

	ObjectsInit();

	TestObjectAllocatorAddConstructors();
	cAllocator.Init(&gcObjects, TRUE);

	pNamed1 = cAllocator.Add("CTestNamedObject", "My Object Name");
	AssertNotNull(pNamed1.Object());

	AssertLongLongInt(1LL, pNamed1.GetIndex());
	AssertString("My Object Name", pNamed1.GetName());

	pTemp = gcObjects.Get("My Object Name");
	AssertPointer(pNamed1.Object(), pTemp.Object());

	pNamed2 = cAllocator.Add("CTestNamedObject", "My Object Name");
	AssertNull(pNamed2.Object());

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectAllocatorNamedOverwrite(void)
{
	CObjectAllocator			cAllocator;
	CPointer<CTestNamedObject>	pNamed1;
	CPointer<CTestNamedObject>	pNamed2;
	CPointer<CTestNamedObject>	pTemp;
	long long int				oiExisting;

	ObjectsInit();

	TestObjectAllocatorAddConstructors();
	cAllocator.Init(&gcObjects, TRUE);

	pNamed1 = cAllocator.Add("CTestNamedObject", "My Object Name");
	AssertLongLongInt(1LL, pNamed1.GetIndex());

	AssertLongLongInt(1, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(1, gcObjects.NumMemoryNames());

	pNamed2 = cAllocator.Add("CTestNamedObject", "My Object Name", &oiExisting);
	AssertNotNull(pNamed2.Object());
	AssertLongLongInt(2LL, pNamed2.GetIndex());
	AssertString("My Object Name", pNamed2.GetName());

	pNamed1 = gcObjects.Get(1LL);
	AssertNull(pNamed1.Object());

	AssertLongLongInt(1, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(1, gcObjects.NumMemoryNames());

	pTemp = gcObjects.Get("My Object Name");
	AssertPointer(pNamed2.Object(), pTemp.Object());

	ObjectsKill();
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


