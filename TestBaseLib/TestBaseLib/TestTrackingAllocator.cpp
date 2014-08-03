#include "BaseLib/MemoryAllocator.h"
#include "BaseLib/TrackingAllocator.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTrackingAllocatorSize(void)
{
	CTrackingAllocator	cTracking;
	CMemoryAllocator	cMemory;
	void*				pv1;
	void*				pv2;
	void*				pv3;
	void*				pv4;

	cMemory.Init();
	cTracking.Init(&cMemory);
	AssertInt(0, cTracking.AllocatedSize());

	pv1 = cTracking.Malloc(100);
	AssertInt(100, cTracking.AllocatedSize());

	pv2 = cTracking.Malloc(200);
	AssertInt(300, cTracking.AllocatedSize());

	pv3 = cTracking.Malloc(50);
	AssertInt(350, cTracking.AllocatedSize());

	pv4 = cTracking.Realloc(pv3, 1000);
	AssertInt(1300, cTracking.AllocatedSize());

	cTracking.Free(pv1);
	AssertInt(1200, cTracking.AllocatedSize());

	cTracking.Free(pv2);
	AssertInt(1000, cTracking.AllocatedSize());

	cTracking.Free(pv4);
	AssertInt(0, cTracking.AllocatedSize());

	cTracking.Kill();
	cMemory.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTrackingAllocator(void)
{
	BeginTests();
	FastFunctionsInit();

	TestTrackingAllocatorSize();

	FastFunctionsKill();
	TestStatistics();
}

