#include "TestLib/Assert.h"
#include "BaseLib/Memory.h"
#include "TestMemory.h"


#define MEM_TEST_INT_1 0x3f47a921
#define MEM_TEST_INT_2 0x64d80c23


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMemoryAdd(void)
{
	CMemory				cMemory;
	void*				pv1;
	void*				pv2;
	void*				pv4;
	void*				pv5;
	void*				pv8;
	void*				pv9;
	void*				pv;
	SMemoryAllocation*	psAlloc;
	CFreeListBlock*	pcList;
	CFreeListBlock*	pcListSame;
	SFreeListIterator	sIter;
	int*				piBits;

	cMemory.Init();

	pv1 = cMemory.Add(1);
	psAlloc = MEMORY_GET_ALLOCATION(pv1);
	piBits = psAlloc->psFreeListNode->GetBitArray();
	AssertInt(1, psAlloc->uiSize);
	pcList = cMemory.GetFreeList(1, 4, 0);
	AssertPointer(pcList, psAlloc->psFreeListNode->pcList);
	pcListSame = cMemory.GetFreeList(8, 4, 0);
	AssertPointer(pcList, pcListSame);
	AssertInt(24811, cMemory.ByteSize());

	pv2 = cMemory.Grow(pv1, 2);
	psAlloc = MEMORY_GET_ALLOCATION(pv2);
	AssertInt(2, psAlloc->uiSize);
	AssertPointer(pcList, psAlloc->psFreeListNode->pcList);
	AssertPointer(pv1, pv2);
	AssertInt(24811, cMemory.ByteSize());

	pv4 = cMemory.Grow(pv2, 4);
	psAlloc = MEMORY_GET_ALLOCATION(pv4);
	AssertInt(4, psAlloc->uiSize);
	AssertPointer(pcList, psAlloc->psFreeListNode->pcList);
	AssertPointer(pv1, pv4);
	*((int*)pv4) = MEM_TEST_INT_1;

	pv5 = cMemory.Grow(pv4, 5);
	psAlloc = MEMORY_GET_ALLOCATION(pv4);
	AssertInt(5, psAlloc->uiSize);
	AssertPointer(pcList, psAlloc->psFreeListNode->pcList);
	AssertPointer(pv1, pv5);
	AssertInt(MEM_TEST_INT_1, *((int*)pv5));

	pv8 = cMemory.Grow(pv5, 8);
	psAlloc = MEMORY_GET_ALLOCATION(pv8);
	AssertInt(8, psAlloc->uiSize);
	AssertPointer(pcList, psAlloc->psFreeListNode->pcList);
	AssertPointer(pv1, pv8);
	AssertInt(MEM_TEST_INT_1, *((int*)pv8));
	((int*)pv8)[1] = MEM_TEST_INT_2;

	pv9 = cMemory.Grow(pv8, 9);
	psAlloc = MEMORY_GET_ALLOCATION(pv9);
	AssertInt(9, psAlloc->uiSize);
	pcList = cMemory.GetFreeList(9, 4, 0);	AssertNotNull(pcList);
	AssertPointer(pcList, psAlloc->psFreeListNode->pcList);
	AssertFalse(pv1 == pv9);
	AssertInt(MEM_TEST_INT_1, *((int*)pv9));
	AssertInt(MEM_TEST_INT_2, ((int*)pv9)[1]);
	pcList = cMemory.GetFreeList(8, 4, 0);
	pv = pcList->StartIteration(&sIter);
	AssertNull(pv);
	AssertInt(28939, cMemory.ByteSize());

	cMemory.Kill();

	cMemory.Init();

	pv4 = cMemory.Add(4);
	*((int*)pv4) = MEM_TEST_INT_1;
	pv8 = cMemory.Grow(pv4, 8);
	((int*)pv8)[1] = MEM_TEST_INT_2;

	pv = cMemory.Add(4);
	*((int*)pv) = MEM_TEST_INT_1;
	AssertInt(MEM_TEST_INT_2, ((int*)pv8)[1]);

	cMemory.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMemoryLargeAdd(void)
{
	CMemory				cMemory;
	void*				pv;
	CFreeListBlock*	pcList;

	cMemory.Init();
	pcList = cMemory.mcFreeLists.GetHead();
	AssertNull(pcList);

	pv = cMemory.Add(2032);
	pcList = cMemory.mcFreeLists.GetHead();
	AssertNotNull(pcList);
	AssertInt(34899, cMemory.ByteSize());
	cMemory.Kill();

	cMemory.Init();

	pv = cMemory.Add(2033);
	pcList = cMemory.mcFreeLists.GetHead();
	AssertNull(pcList);
	AssertInt(2088, cMemory.ByteSize());

	cMemory.mcLargeList.GetHead();

	cMemory.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMemoryFree(void)
{

}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMemory(void)
{
	BeginTests();

	TestMemoryLargeAdd();
	TestMemoryAdd();
	TestMemoryFree();

	TestStatistics();
}

