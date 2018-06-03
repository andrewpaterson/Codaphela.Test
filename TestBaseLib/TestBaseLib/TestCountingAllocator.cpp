#include "BaseLib/MemoryAllocator.h"
#include "BaseLib/CountingAllocator.h"
#include "BaseLib/ScratchPadAllocator.h"
#include "BaseLib/GlobalMemory.h"
#include "BaseLib/TrackingAllocator.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCountingAllocatorSizeSystemAllocator(void)
{
	CCountingAllocator	cCounting;
	void*				pv1;
	void*				pv2;
	void*				pv3;
	void*				pv4;

	cCounting.Init(&gcSystemAllocator);
	AssertInt(sizeof(SCountingMemoryAllocation), cCounting.SizeOffset());

	AssertInt(0, cCounting.AllocatedSize());

	pv1 = cCounting.Malloc(100);
	AssertInt(100, cCounting.AllocatedSize());

	pv2 = cCounting.Malloc(200);
	AssertInt(300, cCounting.AllocatedSize());

	pv3 = cCounting.Malloc(50);
	AssertInt(350, cCounting.AllocatedSize());

	pv4 = cCounting.Realloc(pv3, 1000);
	AssertInt(1300, cCounting.AllocatedSize());

	cCounting.Free(pv1);
	AssertInt(1200, cCounting.AllocatedSize());

	cCounting.Free(pv2);
	AssertInt(1000, cCounting.AllocatedSize());

	cCounting.Free(pv4);
	AssertInt(0, cCounting.AllocatedSize());

	cCounting.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCountingAllocatorSizeMemoryAllocator(void)
{
	CCountingAllocator	cCounting;
	CMemoryAllocator	cMemory;
	void*				pv1;
	void*				pv2;
	void*				pv3;
	void*				pv4;

	cMemory.Init();
	cCounting.Init(&cMemory);
	AssertInt(0, cCounting.AllocatedSize());

	pv1 = cCounting.Malloc(100);
	AssertInt(100, cCounting.AllocatedSize());

	pv2 = cCounting.Malloc(200);
	AssertInt(300, cCounting.AllocatedSize());

	pv3 = cCounting.Malloc(50);
	AssertInt(350, cCounting.AllocatedSize());

	pv4 = cCounting.Realloc(pv3, 1000);
	AssertInt(1300, cCounting.AllocatedSize());

	cCounting.Free(pv1);
	AssertInt(1200, cCounting.AllocatedSize());

	cCounting.Free(pv2);
	AssertInt(1000, cCounting.AllocatedSize());

	cCounting.Free(pv4);
	AssertInt(0, cCounting.AllocatedSize());

	cCounting.Kill();
	cMemory.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCountingAllocatorSizeScratchPadAllocator(void)
{
	CCountingAllocator		cCounting;
	CScratchPadAllocator	cScratchPad;
	void*					pv1;
	void*					pv2;
	void*					pv3;
	void*					pv4;

	cScratchPad.Init();
	cCounting.Init(&cScratchPad);
	AssertInt(0, cCounting.AllocatedSize());

	pv1 = cCounting.Malloc(100);
	AssertInt(100, cCounting.AllocatedSize());

	pv2 = cCounting.Malloc(200);
	AssertInt(300, cCounting.AllocatedSize());

	pv3 = cCounting.Malloc(50);
	AssertInt(350, cCounting.AllocatedSize());

	pv4 = cCounting.Realloc(pv3, 1000);
	AssertInt(1300, cCounting.AllocatedSize());

	cCounting.Free(pv1);
	AssertInt(1200, cCounting.AllocatedSize());

	cCounting.Free(pv2);
	AssertInt(1000, cCounting.AllocatedSize());

	cCounting.Free(pv4);
	AssertInt(0, cCounting.AllocatedSize());

	cCounting.Kill();
	cScratchPad.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCountingAllocatorSizeGlobalMemoryAllocator(void)
{
	CCountingAllocator		cCounting;
	void*					pv1;
	void*					pv2;
	void*					pv3;
	void*					pv4;

	MemoryInit();

	cCounting.Init(&gcMemoryAllocator);
	AssertInt(0, cCounting.AllocatedSize());

	pv1 = cCounting.Malloc(100);
	AssertInt(100, cCounting.AllocatedSize());

	pv2 = cCounting.Malloc(200);
	AssertInt(300, cCounting.AllocatedSize());

	pv3 = cCounting.Malloc(50);
	AssertInt(350, cCounting.AllocatedSize());

	pv4 = cCounting.Realloc(pv3, 1000);
	AssertInt(1300, cCounting.AllocatedSize());

	cCounting.Free(pv1);
	AssertInt(1200, cCounting.AllocatedSize());

	cCounting.Free(pv2);
	AssertInt(1000, cCounting.AllocatedSize());

	cCounting.Free(pv4);
	AssertInt(0, cCounting.AllocatedSize());

	cCounting.Kill();
	MemoryKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCountingAllocatorSizeTrackingSystemAllocator(void)
{
	CCountingAllocator	cCounting;
	CTrackingAllocator	cTracking;
	void*				pv1;
	void*				pv2;
	void*				pv3;
	void*				pv4;

	cTracking.Init(&gcSystemAllocator);
	cCounting.Init(&cTracking);
	AssertInt(sizeof(SCountingMemoryAllocation), cCounting.SizeOffset());
	AssertInt(0, cCounting.AllocatedSize());
	AssertInt(0, cTracking.AllocatedCount());

	pv1 = cCounting.Malloc(100);
	AssertInt(100, cCounting.AllocatedSize());
	AssertInt(1, cTracking.AllocatedCount());

	pv2 = cCounting.Malloc(200);
	AssertInt(300, cCounting.AllocatedSize());
	AssertInt(2, cTracking.AllocatedCount());

	pv3 = cCounting.Malloc(50);
	AssertInt(350, cCounting.AllocatedSize());
	AssertInt(3, cTracking.AllocatedCount());

	pv4 = cCounting.Realloc(pv3, 1000);
	AssertInt(1300, cCounting.AllocatedSize());
	AssertInt(3, cTracking.AllocatedCount());

	cCounting.Free(pv1);
	AssertInt(1200, cCounting.AllocatedSize());
	AssertInt(2, cTracking.AllocatedCount());

	cCounting.Free(pv2);
	AssertInt(1000, cCounting.AllocatedSize());
	AssertInt(1, cTracking.AllocatedCount());

	cCounting.Free(pv4);
	AssertInt(0, cCounting.AllocatedSize());
	AssertInt(0, cTracking.AllocatedCount());

	cCounting.Kill();
	cTracking.Kill();

	cCounting.Init(&gcSystemAllocator);
	cTracking.Init(&cCounting);
	AssertInt(sizeof(SCountingMemoryAllocation), cTracking.SizeOffset());
	AssertInt(0, cCounting.AllocatedSize());
	AssertInt(0, cTracking.AllocatedCount());

	pv1 = cTracking.Malloc(100);
	AssertInt(100, cCounting.AllocatedSize());
	AssertInt(1, cTracking.AllocatedCount());

	pv2 = cTracking.Malloc(200);
	AssertInt(300, cCounting.AllocatedSize());
	AssertInt(2, cTracking.AllocatedCount());

	pv3 = cTracking.Malloc(50);
	AssertInt(350, cCounting.AllocatedSize());
	AssertInt(3, cTracking.AllocatedCount());

	pv4 = cTracking.Realloc(pv3, 1000);
	AssertInt(1300, cCounting.AllocatedSize());
	AssertInt(3, cTracking.AllocatedCount());

	cTracking.Free(pv1);
	AssertInt(1200, cCounting.AllocatedSize());
	AssertInt(2, cTracking.AllocatedCount());

	cTracking.Free(pv2);
	AssertInt(1000, cCounting.AllocatedSize());
	AssertInt(1, cTracking.AllocatedCount());

	cTracking.Free(pv4);
	AssertInt(0, cCounting.AllocatedSize());
	AssertInt(0, cTracking.AllocatedCount());

	cCounting.Kill();
	cTracking.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCountingAllocatorSizeTrackingGlobalMemoryAllocator(void)
{
	CCountingAllocator		cCounting;
	CTrackingAllocator		cTracking;
	void*					pv1;
	void*					pv2;
	void*					pv3;
	void*					pv4;

	MemoryInit();
	cTracking.Init(&gcMemoryAllocator);
	cCounting.Init(&cTracking);
	AssertInt(sizeof(SGeneralMemoryAllocation), cCounting.SizeOffset());
	AssertInt(0, cCounting.AllocatedSize());
	AssertInt(0, cTracking.AllocatedCount());

	pv1 = cCounting.Malloc(100);
	AssertInt(100, cCounting.AllocatedSize());
	AssertInt(1, cTracking.AllocatedCount());

	pv2 = cCounting.Malloc(200);
	AssertInt(300, cCounting.AllocatedSize());
	AssertInt(2, cTracking.AllocatedCount());

	pv3 = cCounting.Malloc(50);
	AssertInt(350, cCounting.AllocatedSize());
	AssertInt(3, cTracking.AllocatedCount());

	pv4 = cCounting.Realloc(pv3, 1000);
	AssertInt(1300, cCounting.AllocatedSize());
	AssertInt(3, cTracking.AllocatedCount());

	cCounting.Free(pv1);
	AssertInt(1200, cCounting.AllocatedSize());
	AssertInt(2, cTracking.AllocatedCount());

	cCounting.Free(pv2);
	AssertInt(1000, cCounting.AllocatedSize());
	AssertInt(1, cTracking.AllocatedCount());

	cCounting.Free(pv4);
	AssertInt(0, cCounting.AllocatedSize());
	AssertInt(0, cTracking.AllocatedCount());

	cCounting.Kill();
	cTracking.Kill();
	MemoryKill();

	MemoryInit();
	cCounting.Init(&gcMemoryAllocator);
	cTracking.Init(&cCounting);
	AssertInt(sizeof(SGeneralMemoryAllocation), cCounting.SizeOffset());
	AssertInt(0, cCounting.AllocatedSize());
	AssertInt(0, cTracking.AllocatedCount());

	pv1 = cTracking.Malloc(100);
	AssertInt(100, cCounting.AllocatedSize());
	AssertInt(1, cTracking.AllocatedCount());

	pv2 = cTracking.Malloc(200);
	AssertInt(300, cCounting.AllocatedSize());
	AssertInt(2, cTracking.AllocatedCount());

	pv3 = cTracking.Malloc(50);
	AssertInt(350, cCounting.AllocatedSize());
	AssertInt(3, cTracking.AllocatedCount());

	pv4 = cTracking.Realloc(pv3, 1000);
	AssertInt(1300, cCounting.AllocatedSize());
	AssertInt(3, cTracking.AllocatedCount());

	cTracking.Free(pv1);
	AssertInt(1200, cCounting.AllocatedSize());
	AssertInt(2, cTracking.AllocatedCount());

	cTracking.Free(pv2);
	AssertInt(1000, cCounting.AllocatedSize());
	AssertInt(1, cTracking.AllocatedCount());

	cTracking.Free(pv4);
	AssertInt(0, cCounting.AllocatedSize());
	AssertInt(0, cTracking.AllocatedCount());

	cCounting.Kill();
	cTracking.Kill();
	MemoryKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCountingAllocator(void)
{
	BeginTests();
	FastFunctionsInit();

	TestCountingAllocatorSizeSystemAllocator();
	TestCountingAllocatorSizeMemoryAllocator();
	TestCountingAllocatorSizeScratchPadAllocator();
	TestCountingAllocatorSizeGlobalMemoryAllocator();
	TestCountingAllocatorSizeTrackingSystemAllocator();
	TestCountingAllocatorSizeTrackingGlobalMemoryAllocator();

	FastFunctionsKill();
	TestStatistics();
}

