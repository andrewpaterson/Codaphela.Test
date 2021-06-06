#include "BaseLib/GlobalMemory.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/TypeNames.h"
#include "StandardLib/Objects.h"
#include "TestLib/Assert.h"
#include "ObjectTestClasses.h"


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
void TestObjectStack(void)
{
	BeginTests();
	MemoryInit();
	TypesInit();
	DataIOInit();

	TestObjectStackInit();
	TestObjectStackDestructor();

	DataIOKill();
	TypesKill();
	MemoryKill();
	TestStatistics();
}

