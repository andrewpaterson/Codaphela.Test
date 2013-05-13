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
	pNamed2 = cAllocator.Add("CTestNamedObject", "My Object Name", 1LL, &oiExisting);
	

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


