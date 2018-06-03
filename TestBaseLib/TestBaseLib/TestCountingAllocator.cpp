#include "BaseLib/MemoryAllocator.h"
#include "BaseLib/CountingAllocator.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCountingAllocatorSize(void)
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
void TestCountingAllocator(void)
{
	BeginTests();
	FastFunctionsInit();

	TestCountingAllocatorSize();

	FastFunctionsKill();
	TestStatistics();
}

