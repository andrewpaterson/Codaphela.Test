#include "BaseLib/GlobalMemory.h"
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
	STestObjectKilledNotifier	sKillNotifier;

	AssertFalse(cObject.IsAllocatedInObjects());
	AssertTrue(cObject.GetFlags() & OBJECT_FLAGS_CALLED_CONSTRUCTOR);
	AssertFalse(cObject.GetFlags() & OBJECT_FLAGS_CALLED_ALLOCATE);
	AssertFalse(cObject.GetFlags() & OBJECT_FLAGS_CALLED_INIT);
	AssertInt(0, cObject.GetDistToStack());
	AssertInt(UNATTACHED_DIST_TO_ROOT, cObject.GetDistToRoot());

	cObject.Init(&sKillNotifier);

	AssertTrue(cObject.GetFlags() & OBJECT_FLAGS_CALLED_INIT);

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

	TestObjectStackInit();

	MemoryKill();
	TestStatistics();
}

