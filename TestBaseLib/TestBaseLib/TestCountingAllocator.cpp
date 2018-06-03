#include "BaseLib/MemoryAllocator.h"
#include "BaseLib/CountingAllocator.h"
#include "BaseLib/ScratchPadAllocator.h"
#include "BaseLib/GlobalMemory.h"
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
void TestCountingAllocator(void)
{
	BeginTests();
	FastFunctionsInit();

	TestCountingAllocatorSizeSystemAllocator();
	TestCountingAllocatorSizeMemoryAllocator();
	TestCountingAllocatorSizeScratchPadAllocator();
	TestCountingAllocatorSizeGlobalMemoryAllocator();

	FastFunctionsKill();
	TestStatistics();
}

