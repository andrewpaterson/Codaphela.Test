#include "BaseLib/MemoryManager.h"
#include "BaseLib/IntegerHelper.h"
#include "BaseLib/ArrayVoidPtr.h"
#include "BaseLib/StdRandom.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMemoryManagerContiguousAllocations(void)
{
	CMemoryManager	cMemory;
	void*			pvStartMemory;
	void*			pvEndMemory;
	void*			pvMem1;
	void*			pvMem2;
	void*			pvMem3;
	void*			pvMem4;
	uint32			uiMemorySize;

	uiMemorySize = 96;
	pvStartMemory = malloc(uiMemorySize);
	pvEndMemory = RemapSinglePointer(pvStartMemory, (uiMemorySize - 1));
	cMemory.Init(pvStartMemory, pvEndMemory);
	cMemory.DisableEmptyCache();

	pvMem1 = cMemory.Allocate(10);
	pvMem2 = cMemory.Allocate(20);
	pvMem3 = cMemory.Allocate(30);
	pvMem4 = cMemory.Allocate(1);
	AssertNotNull(pvMem1);
	AssertNotNull(pvMem2);
	AssertNotNull(pvMem3);
	AssertNull(pvMem4);
	AssertInt(10 + MM_NODE_HEADER_SIZE, (size)pvMem2 - (size)pvMem1);
	AssertInt(20 + MM_NODE_HEADER_SIZE, (size)pvMem3 - (size)pvMem2);

	cMemory.Kill();

	free(pvStartMemory);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
SMMNode* AssertNode(SMMNode* psNode, uint32 uiExpectedSize, bool bUsed)
{
	uint32 uiActualSize;

	uiActualSize = GetMMNodeDataSize(psNode) - MM_NODE_HEADER_SIZE;
	AssertInt(uiExpectedSize, uiActualSize);
	AssertBool(bUsed, FixBool(psNode->uiFlags & MM_NODE_USED));
	return (SMMNode*)psNode->psNext;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
SMMNode* AssertNode(SMMNode* psNode, uint32 uiExpectedUserSize, uint32 uiExpectedNodeSize, bool bUsed)
{
	uint32 uiActualUserSize;
	uint32 uiActualNodeSize;

	uiActualUserSize = GetMMNodeDataSize(psNode) - MM_NODE_HEADER_SIZE;
	uiActualNodeSize = ((size)(psNode->psNext) - (size)psNode) - MM_NODE_HEADER_SIZE;
	AssertInt(uiExpectedUserSize, uiActualUserSize);
	AssertInt(uiExpectedNodeSize, uiActualNodeSize);
	AssertBool(bUsed, FixBool(psNode->uiFlags & MM_NODE_USED));
	return (SMMNode*)psNode->psNext;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMemoryManagerDeallocate1(void)
{
	CMemoryManager	cMemory;
	void*			pvStartMemory;
	void*			pvEndMemory;
	void*			pvMem1;
	void*			pvMem2;
	void*			pvMem3;
	void*			pvMem4;
	uint32			uiMemorySize;
	SMMNode*		psNode;

	uiMemorySize = 88;
	pvStartMemory = malloc(uiMemorySize);
	pvEndMemory = RemapSinglePointer(pvStartMemory, (uiMemorySize - 1));
	cMemory.Init(pvStartMemory, pvEndMemory);
	cMemory.DisableEmptyCache();

	pvMem1 = cMemory.Allocate(10);
	pvMem2 = cMemory.Allocate(10);
	pvMem3 = cMemory.Allocate(10);
	pvMem4 = cMemory.Allocate(10);

	AssertNotNull(pvMem1);
	AssertNotNull(pvMem2);
	AssertNotNull(pvMem3);
	AssertNotNull(pvMem4);

	cMemory.Deallocate(pvMem2);
	psNode = cMemory.StartIteration();
	psNode = AssertNode(psNode, 10, true);
	psNode = AssertNode(psNode, 10, false);
	psNode = AssertNode(psNode, 10, true);
	psNode = AssertNode(psNode, 10, true);
	AssertNull(psNode);
	
	cMemory.Deallocate(pvMem1);
	psNode = cMemory.StartIteration();
	psNode = AssertNode(psNode, 32, false);
	psNode = AssertNode(psNode, 10, true);
	psNode = AssertNode(psNode, 10, true);
	AssertNull(psNode);

	cMemory.Deallocate(pvMem3);
	psNode = cMemory.StartIteration();
	psNode = AssertNode(psNode, 54, false);
	psNode = AssertNode(psNode, 10, true);
	AssertNull(psNode);

	cMemory.Deallocate(pvMem4);
	psNode = cMemory.StartIteration();
	AssertNull(psNode);

	cMemory.Kill();

	free(pvStartMemory);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMemoryManagerDeallocate2(void)
{
	CMemoryManager	cMemory;
	void*			pvStartMemory;
	void*			pvEndMemory;
	void*			pvMem1;
	void*			pvMem2;
	void*			pvMem3;
	void*			pvMem4;
	void*			pvMem5;
	uint32			uiMemorySize;
	SMMNode*		psNode;

	uiMemorySize = 100;
	pvStartMemory = malloc(uiMemorySize);
	pvEndMemory = RemapSinglePointer(pvStartMemory, (uiMemorySize - 1));
	cMemory.Init(pvStartMemory, pvEndMemory);
	cMemory.DisableEmptyCache();

	pvMem1 = cMemory.Allocate(8);
	pvMem2 = cMemory.Allocate(8);
	pvMem3 = cMemory.Allocate(8);
	pvMem4 = cMemory.Allocate(8);
	pvMem5 = cMemory.Allocate(8);

	AssertNotNull(pvMem1);
	AssertNotNull(pvMem2);
	AssertNotNull(pvMem3);
	AssertNotNull(pvMem4);
	AssertNotNull(pvMem5);

	cMemory.Deallocate(pvMem2);
	psNode = cMemory.StartIteration();
	psNode = AssertNode(psNode, 8, true);
	psNode = AssertNode(psNode, 8, false);
	psNode = AssertNode(psNode, 8, true);
	psNode = AssertNode(psNode, 8, true);
	psNode = AssertNode(psNode, 8, true);
	AssertNull(psNode);
	
	cMemory.Deallocate(pvMem4);
	psNode = cMemory.StartIteration();
	psNode = AssertNode(psNode, 8, true);
	psNode = AssertNode(psNode, 8, false);
	psNode = AssertNode(psNode, 8, true);
	psNode = AssertNode(psNode, 8, false);
	psNode = AssertNode(psNode, 8, true);
	AssertNull(psNode);

	cMemory.Deallocate(pvMem3);
	psNode = cMemory.StartIteration();
	psNode = AssertNode(psNode, 8, true);
	psNode = AssertNode(psNode, 48, false);
	psNode = AssertNode(psNode, 8, true);
	AssertNull(psNode);

	cMemory.Deallocate(pvMem1);
	psNode = cMemory.StartIteration();
	psNode = AssertNode(psNode, 68, false);
	psNode = AssertNode(psNode, 8, true);
	AssertNull(psNode);

	cMemory.Deallocate(pvMem5);
	psNode = cMemory.StartIteration();
	AssertNull(psNode);

	cMemory.Kill();

	free(pvStartMemory);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMemoryManagerDeallocateAllocate1(void)
{
	CMemoryManager	cMemory;
	void*			pvStartMemory;
	void*			pvEndMemory;
	void*			pvMem1;
	void*			pvMem2;
	void*			pvMem3;
	void*			pvMem4;
	uint32			uiMemorySize;
	SMMNode*		psNode;

	uiMemorySize = 100;
	pvStartMemory = malloc(uiMemorySize);
	pvEndMemory = RemapSinglePointer(pvStartMemory, (uiMemorySize - 1));
	cMemory.Init(pvStartMemory, pvEndMemory);
	cMemory.DisableEmptyCache();

	pvMem1 = cMemory.Allocate(8);
	pvMem2 = cMemory.Allocate(8);
	pvMem3 = cMemory.Allocate(8);
	pvMem4 = cMemory.Allocate(8);

	AssertNotNull(pvMem1);
	AssertNotNull(pvMem2);
	AssertNotNull(pvMem3);
	AssertNotNull(pvMem4);

	cMemory.Deallocate(pvMem2);
	psNode = cMemory.StartIteration();
	psNode = AssertNode(psNode, 8, true);
	psNode = AssertNode(psNode, 8, false);
	psNode = AssertNode(psNode, 8, true);
	psNode = AssertNode(psNode, 8, true);
	AssertNull(psNode);

	pvMem2 = cMemory.Allocate(8);
	psNode = cMemory.StartIteration();
	psNode = AssertNode(psNode, 8, true);
	psNode = AssertNode(psNode, 8, true);
	psNode = AssertNode(psNode, 8, true);
	psNode = AssertNode(psNode, 8, true);
	AssertNull(psNode);

	cMemory.Deallocate(pvMem2);
	psNode = cMemory.StartIteration();
	psNode = AssertNode(psNode, 8, true);
	psNode = AssertNode(psNode, 8, false);
	psNode = AssertNode(psNode, 8, true);
	psNode = AssertNode(psNode, 8, true);
	AssertNull(psNode);

	cMemory.Deallocate(pvMem3);
	psNode = cMemory.StartIteration();
	psNode = AssertNode(psNode, 8, true);
	psNode = AssertNode(psNode, 28, false);
	psNode = AssertNode(psNode, 8, true);
	AssertNull(psNode);

	pvMem2 = cMemory.Allocate(16);
	psNode = cMemory.StartIteration();
	psNode = AssertNode(psNode, 8, true);
	psNode = AssertNode(psNode, 16, 28, true);
	psNode = AssertNode(psNode, 8, true);
	AssertNull(psNode);

	cMemory.Deallocate(pvMem2);
	psNode = cMemory.StartIteration();
	psNode = AssertNode(psNode, 8, true);
	psNode = AssertNode(psNode, 28, false);
	psNode = AssertNode(psNode, 8, true);
	AssertNull(psNode);

	pvMem2 = cMemory.Allocate(6);
	psNode = cMemory.StartIteration();
	psNode = AssertNode(psNode, 8, true);
	psNode = AssertNode(psNode, 6, 6, true);
	psNode = AssertNode(psNode, 10, false);
	psNode = AssertNode(psNode, 8, true);
	AssertNull(psNode);

	cMemory.Kill();

	free(pvStartMemory);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMemoryManagerDeallocateAllocate2(void)
{
	CMemoryManager	cMemory;
	void*			pvStartMemory;
	void*			pvEndMemory;
	void*			pvMem1;
	void*			pvMem2;
	void*			pvMem3;
	void*			pvMem4;
	uint32			uiMemorySize;
	SMMNode*		psNode;

	uiMemorySize = 100;
	pvStartMemory = malloc(uiMemorySize);
	pvEndMemory = RemapSinglePointer(pvStartMemory, (uiMemorySize - 1));
	cMemory.Init(pvStartMemory, pvEndMemory);
	cMemory.DisableEmptyCache();

	pvMem1 = cMemory.Allocate(8);
	pvMem2 = cMemory.Allocate(8);
	pvMem3 = cMemory.Allocate(8);
	pvMem4 = cMemory.Allocate(8);

	AssertNotNull(pvMem1);
	AssertNotNull(pvMem2);
	AssertNotNull(pvMem3);
	AssertNotNull(pvMem4);

	cMemory.Deallocate(pvMem2);
	psNode = cMemory.StartIteration();
	psNode = AssertNode(psNode, 8, true);
	psNode = AssertNode(psNode, 8, false);
	psNode = AssertNode(psNode, 8, true);
	psNode = AssertNode(psNode, 8, true);
	AssertNull(psNode);

	cMemory.Deallocate(pvMem3);
	psNode = cMemory.StartIteration();
	psNode = AssertNode(psNode, 8, true);
	psNode = AssertNode(psNode, 28, false);
	psNode = AssertNode(psNode, 8, true);
	AssertNull(psNode);

	pvMem2 = cMemory.Allocate(16);
	psNode = cMemory.StartIteration();
	psNode = AssertNode(psNode, 8, true);
	psNode = AssertNode(psNode, 16, 28, true);
	psNode = AssertNode(psNode, 8, true);
	AssertNull(psNode);

	cMemory.Deallocate(pvMem4);
	psNode = cMemory.StartIteration();
	psNode = AssertNode(psNode, 8, true);
	psNode = AssertNode(psNode, 16, true);
	AssertNull(psNode);

	pvMem2 = cMemory.Allocate(6);
	psNode = cMemory.StartIteration();
	psNode = AssertNode(psNode, 8, true);
	psNode = AssertNode(psNode, 16, 16, true);
	psNode = AssertNode(psNode, 6, true);
	AssertNull(psNode);

	cMemory.Kill();

	free(pvStartMemory);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMemoryManagerDeallocateAllocate3(void)
{
	CMemoryManager	cMemory;
	void*			pvStartMemory;
	void*			pvEndMemory;
	void*			pvMem1;
	void*			pvMem2;
	void*			pvMem3;
	void*			pvMem4;
	uint32			uiMemorySize;
	SMMNode*		psNode;

	uiMemorySize = 88;
	pvStartMemory = malloc(uiMemorySize);
	pvEndMemory = RemapSinglePointer(pvStartMemory, (uiMemorySize - 1));
	cMemory.Init(pvStartMemory, pvEndMemory);
	cMemory.DisableEmptyCache();

	pvMem1 = cMemory.Allocate(12);
	pvMem2 = cMemory.Allocate(8);
	pvMem3 = cMemory.Allocate(12);
	pvMem4 = cMemory.Allocate(8);

	AssertNotNull(pvMem1);
	AssertNotNull(pvMem2);
	AssertNotNull(pvMem3);
	AssertNotNull(pvMem4);

	cMemory.Deallocate(pvMem1);
	psNode = cMemory.StartIteration();
	psNode = AssertNode(psNode, 12, false);
	psNode = AssertNode(psNode, 8, true);
	psNode = AssertNode(psNode, 12, true);
	psNode = AssertNode(psNode, 8, true);
	AssertNull(psNode);

	cMemory.Deallocate(pvMem2);
	psNode = cMemory.StartIteration();
	psNode = AssertNode(psNode, 32, false);
	psNode = AssertNode(psNode, 12, 12, true);
	psNode = AssertNode(psNode, 8, true);
	AssertNull(psNode);

	pvMem1 = cMemory.Allocate(16);
	psNode = cMemory.StartIteration();
	psNode = AssertNode(psNode, 16, 32, true);
	psNode = AssertNode(psNode, 12, 12, true);
	psNode = AssertNode(psNode, 8, true);
	AssertNull(psNode);

	cMemory.Deallocate(pvMem1);
	psNode = cMemory.StartIteration();
	psNode = AssertNode(psNode, 32, false);
	psNode = AssertNode(psNode, 12, 12, true);
	psNode = AssertNode(psNode, 8, true);
	AssertNull(psNode);

	pvMem1 = cMemory.Allocate(15);
	psNode = cMemory.StartIteration();
	psNode = AssertNode(psNode, 15, 15, true);
	psNode = AssertNode(psNode, 5, false);
	psNode = AssertNode(psNode, 12, 12, true);
	psNode = AssertNode(psNode, 8, true);
	AssertNull(psNode);

	cMemory.Deallocate(pvMem3);
	psNode = cMemory.StartIteration();
	psNode = AssertNode(psNode, 15, 15, true);
	psNode = AssertNode(psNode, 29, false);
	psNode = AssertNode(psNode, 8, true);
	AssertNull(psNode);

	cMemory.Deallocate(pvMem1);
	psNode = cMemory.StartIteration();
	psNode = AssertNode(psNode, 56, false);
	psNode = AssertNode(psNode, 8, true);
	AssertNull(psNode);

	cMemory.Deallocate(pvMem4);
	psNode = cMemory.StartIteration();
	AssertNull(psNode);

	cMemory.Kill();

	free(pvStartMemory);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMemoryManagerEmptyCache(void)
{
	CMemoryManager	cMemory;
	void*			pvStartMemory;
	void*			pvEndMemory;
	void*			pv;
	uint32			uiMemorySize;
	uint32			uiCount;
	uint8			uiValue;
	uint32			uiAllocations;
	uint32			uiRemainingSize;
	uint32			uiUsedSize;
	uint32			uiUnusedSize;
	uint32			uiTotalSize;
	int32			i;
	int32			iIndex;
	int32			iToRemove;
	int32			j;
	CArrayVoidPtr	apvAllocations;
	CRandom			cRandom;
	void**			ppv;
	uint32			uiRemovals;

	uiMemorySize = 64 KB;
	pvStartMemory = malloc(uiMemorySize);
	pvEndMemory = RemapSinglePointer(pvStartMemory, (uiMemorySize - 1));
	cMemory.Init(pvStartMemory, pvEndMemory);

	apvAllocations.Init();

	uiCount = 100;
	uiValue = 0;
	for (;;)
	{
		pv = cMemory.Allocate(uiCount);
		if (pv == NULL)
		{
			break;
		}

		apvAllocations.Add(pv);

		memset(pv, uiValue, uiCount);
		uiValue++;
		uiCount++;
		if (uiCount > 150)
		{
			uiCount = 50;
		}
	}

	uiTotalSize = cMemory.GetTotalSize();
	AssertInt((uint32)(64 KB), uiTotalSize);
	uiAllocations = cMemory.GetNumAllocations(false);
	AssertInt(582, uiAllocations);
	AssertInt(582, apvAllocations.NumElements());
	uiRemainingSize = cMemory.GetRemaingTailSize();
	AssertInt(52, uiRemainingSize);
	uiUsedSize = cMemory.GetUsedAllocationSize();
	AssertInt(65484, uiUsedSize);
	uiUnusedSize = cMemory.GetUnusedAllocationSize();
	AssertInt(0, uiUnusedSize);
	AssertInt((uint32)(64 KB), uiRemainingSize + uiUsedSize + uiUnusedSize);

	uiRemovals = 0;
	cRandom.Init(3456897);
	for (i = 0; i < 100; i++)
	{
		iIndex = cRandom.Next(0, apvAllocations.NumElements() - 1);
		iToRemove = cRandom.Next(0, 2);
		for (j = iToRemove; j >= 0; j--)
		{
			ppv = apvAllocations.Get(iIndex + j);
			pv = *ppv;
			cMemory.Deallocate(pv);
			apvAllocations.RemoveAt(iIndex + j, true);
			uiRemovals++;
		}
		uiAllocations = cMemory.GetNumAllocations(false);
		AssertInt(582, uiAllocations + uiRemovals);
	}
	
	uiTotalSize = cMemory.GetTotalSize();
	AssertInt((uint32)(64 KB), uiTotalSize);
	uiAllocations = cMemory.GetNumAllocations(false);
	AssertInt(382, uiAllocations);
	uiRemainingSize = cMemory.GetRemaingTailSize();
	AssertInt(52, uiRemainingSize);
	uiUsedSize = cMemory.GetUsedAllocationSize();
	AssertInt(42753, uiUsedSize);
	uiUnusedSize = cMemory.GetUnusedAllocationSize();
	AssertInt(22731, uiUnusedSize);
	AssertInt((uint32)(64 KB), uiRemainingSize + uiUsedSize + uiUnusedSize);

	apvAllocations.Kill();

	cRandom.Kill();
	cMemory.Kill();
	free(pvStartMemory);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMemoryManager(void)
{
	BeginTests();
	FastFunctionsInit();

	TestMemoryManagerContiguousAllocations();
	TestMemoryManagerDeallocate1();
	TestMemoryManagerDeallocate2();
	TestMemoryManagerDeallocateAllocate1();
	TestMemoryManagerDeallocateAllocate2();
	TestMemoryManagerDeallocateAllocate3();
	TestMemoryManagerEmptyCache();

	FastFunctionsKill();
	TestStatistics();
}

