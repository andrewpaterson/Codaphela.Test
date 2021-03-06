#include "BaseLib/SystemAllocator.h"
#include "BaseLib/NullAllocator.h"
#include "BaseLib/FreeListAllocator.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestAllocatorSystem(void)
{
	CSystemAllocator	cAlloc;
	void*				pv;
	void*				pv2;

	pv = cAlloc.Malloc(100);
	AssertNotNull(pv);

	pv2 = cAlloc.Realloc(pv, 10000);
	AssertNotNull(pv2);

	cAlloc.Free(pv2);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestAllocatorNull(void)
{
	CNullAllocator	cAlloc;
	void*			pv;

	pv = cAlloc.Malloc(100);
	AssertNull(pv);
	pv = cAlloc.Malloc(100);
	AssertNull(pv);
	pv = cAlloc.Malloc(100);
	AssertNull(pv);

	pv = cAlloc.Realloc((void*)0x73984, 10000);
	AssertNull(pv);
	pv = cAlloc.Realloc(NULL, 10000);
	AssertNull(pv);
	pv = cAlloc.Realloc((void*)0xffffffff, 10000);
	AssertNull(pv);

	cAlloc.Free(pv);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestAllocatorFreeList(void)
{
	CFreeList*			pcBlock;
	CFreeListAllocator	cAlloc;
	void*				pv1;
	void*				pv2;
	void*				pv3;
	void*				pv4;
	void*				pv;

	cAlloc.Init(256);
	pcBlock = cAlloc.GetFreeList();
	AssertInt(0, pcBlock->NumElements());

	pv1 = cAlloc.Malloc(256);
	AssertNotNull(pv1);
	AssertInt(1, pcBlock->NumElements());
	AssertPointer(pcBlock->Get(0), pv1);

	pv2 = cAlloc.Malloc(255);
	AssertNotNull(pv2);
	AssertInt(2, pcBlock->NumElements());
	AssertPointer(pcBlock->Get(1), pv2);

	pv3 = cAlloc.Malloc(1);
	AssertNotNull(pv3);
	AssertInt(3, pcBlock->NumElements());
	AssertPointer(pcBlock->Get(2), pv3);

	pv4 = cAlloc.Malloc(256);
	AssertNotNull(pv4);
	AssertInt(4, pcBlock->NumElements());
	AssertPointer(pcBlock->Get(3), pv4);

	pv = cAlloc.Realloc(pv1, 255);
	AssertPointer(pv1, pv);
	AssertInt(4, pcBlock->NumElements());

	pv = cAlloc.Malloc(257);
	AssertNull(pv);
	AssertInt(4, pcBlock->NumElements());

	cAlloc.Free(pv2);
	AssertInt(3, pcBlock->NumElements());
	cAlloc.Free(pv1);
	AssertInt(2, pcBlock->NumElements());
	cAlloc.Free(pv4);
	AssertInt(1, pcBlock->NumElements());
	cAlloc.Free(pv3);
	AssertInt(0, pcBlock->NumElements());

	cAlloc.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestAllocator(void)
{
	BeginTests();
	FastFunctionsInit();

	TestAllocatorSystem();
	TestAllocatorNull();
	TestAllocatorFreeList();

	FastFunctionsKill();
	TestStatistics();
}

