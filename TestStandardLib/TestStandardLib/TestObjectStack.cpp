#include "BaseLib/GlobalMemory.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/TypeNames.h"
#include "StandardLib/Objects.h"
#include "TestLib/Assert.h"
#include "ObjectTestClasses.h"
#include "TestClass.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectStackInit(void)
{
	ObjectsInit();

	CTestObject					cObject;
	STestObjectFreedNotifier	sFreedNotifier;
	CClass*						pcClass;

	AssertFalse(cObject.IsAllocatedInObjects());
	AssertTrue(cObject.GetFlags() & OBJECT_FLAGS_CALLED_CONSTRUCTOR);
	AssertFalse(cObject.GetFlags() & OBJECT_FLAGS_CALLED_ALLOCATE);
	AssertFalse(cObject.GetFlags() & OBJECT_FLAGS_CALLED_INIT);
	AssertFalse(cObject.GetFlags() & OBJECT_FLAGS_CALLED_CLASS);
	AssertInt(0, cObject.GetDistToStack());
	AssertInt(UNATTACHED_DIST_TO_ROOT, cObject.GetDistToRoot());

	pcClass = cObject.GetClass();
	AssertNull(pcClass);

	cObject.Init(&sFreedNotifier);

	pcClass = cObject.GetClass();
	AssertNotNull(pcClass);


	AssertTrue(cObject.GetFlags() & OBJECT_FLAGS_CALLED_INIT);

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectStackDestructorOutOfFrame(STestObjectFreedNotifier* psFreeNotifier)
{
	CTestObject					cObject;

	cObject.Init(psFreeNotifier);
	AssertTrue(cObject.GetFlags() & OBJECT_FLAGS_CALLED_INIT);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectStackDestructor(void)
{
	STestObjectFreedNotifier	sFreedNotifier;

	ObjectsInit();

	TestObjectStackDestructorOutOfFrame(&sFreedNotifier);
	AssertTrue(sFreedNotifier.bFreed);

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectStackPointedToOutOfFrame(void)
{
	Ptr<CTestClass>		pHeapTestClass;
	CTestClass			cStackTestClass;

	cStackTestClass.Init();
	pHeapTestClass = OMalloc<CTestClass>();
	pHeapTestClass->mpObject = &cStackTestClass;
	pHeapTestClass->mDouble = 98457.0;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectStackPointedTo(void)
{
	ObjectsInit();

	TestObjectStackPointedToOutOfFrame();

	ObjectsKill();
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectStackObjectReuseOutOfFrame(CTestClass** pcTestClass)
{
	CTestClass		cStackTestClass;
	CChars			sz;

	(*pcTestClass) = &cStackTestClass;

	sz.Init(); 
	cStackTestClass.PrintFlags(&sz);
	AssertString("CALLED_CONSTRUCTOR", sz.Text());
	sz.Kill();

	cStackTestClass.Init();
	sz.Init();
	cStackTestClass.PrintFlags(&sz);
	AssertString("CALLED_CONSTRUCTOR, DIRTY, CALLED_INIT, CALLED_CLASS", sz.Text());
	sz.Kill();

	cStackTestClass.Kill();
	sz.Init();
	cStackTestClass.PrintFlags(&sz);
	AssertString("CALLED_CONSTRUCTOR, DIRTY, CALLED_KILL, CALLED_CLASS", sz.Text());
	sz.Kill();


	cStackTestClass.Init();
	sz.Init();
	cStackTestClass.PrintFlags(&sz);
	AssertString("CALLED_CONSTRUCTOR, DIRTY, CALLED_INIT, CALLED_CLASS", sz.Text());
	sz.Kill();

	cStackTestClass.Kill();
	sz.Init();
	cStackTestClass.PrintFlags(&sz);
	AssertString("CALLED_CONSTRUCTOR, DIRTY, CALLED_KILL, CALLED_CLASS", sz.Text());
	sz.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectStackObjectReuse(void)
{
	CTestClass*		pcTestClass;
	CChars			sz;

	ObjectsInit();

	TestObjectStackObjectReuseOutOfFrame(&pcTestClass);
	sz.Init();
	pcTestClass->PrintFlags(&sz);
	AssertString("", sz.Text());
	sz.Kill();

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectStack(void)
{
	BeginTests();
	MemoryInit();
	TypesInit();
	DataIOInit();

	TestObjectStackInit();
	TestObjectStackDestructor();
	TestObjectStackPointedTo();
	TestObjectStackObjectReuse();

	DataIOKill();
	TypesKill();
	MemoryKill();
	TestStatistics();
}

