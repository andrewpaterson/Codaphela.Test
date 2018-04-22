#include "BaseLib/Memory.h"
#include "TestLib/Assert.h"


#define MEM_TEST_INT_1 0x3f47a921
#define MEM_TEST_INT_2 0x64d80c23


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMemoryAdd(void)
{
	CMemory						cMemory;
	void*						pv1;
	void*						pv2;
	void*						pv4;
	void*						pv5;
	void*						pv8;
	void*						pv9;
	void*						pv;
	SGeneralMemoryAllocation*	psAlloc;
	CFreeList*					pcList;
	CFreeList*					pcListSame;
	SFreeListIterator			sIter;

	cMemory.Init();

	pv1 = cMemory.Add(1);
	psAlloc = MEMORY_GET_ALLOCATION(pv1);
	AssertInt(1, psAlloc->uiSize);
	AssertInt(1, cMemory.GetSize(pv1));
	pcList = cMemory.GetFreeList(1, 4, 0);
	AssertPointer(pcList, psAlloc->psFreeListNode->pcList);
	pcListSame = cMemory.GetFreeList(8, 4, 0);
	AssertPointer(pcList, pcListSame);
	AssertInt(24803, cMemory.ByteSize());

	pv2 = cMemory.Grow(pv1, 2);
	psAlloc = MEMORY_GET_ALLOCATION(pv2);
	AssertInt(2, psAlloc->uiSize);
	AssertInt(2, cMemory.GetSize(pv2));
	AssertPointer(pcList, psAlloc->psFreeListNode->pcList);
	AssertPointer(pv1, pv2);
	AssertInt(24803, cMemory.ByteSize());

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
	AssertInt(28931, cMemory.ByteSize());

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
	CMemory		cMemory;
	void*		pv;
	CFreeList*	pcList;

	cMemory.Init();
	pcList = cMemory.TestGetFreeListsHead();
	AssertNull(pcList);

	pv = cMemory.Add(2032);
	pcList = cMemory.TestGetFreeListsHead();
	AssertNotNull(pcList);
	AssertInt(34891, cMemory.ByteSize());
	cMemory.Kill();

	cMemory.Init();

	pv = cMemory.Add(2033);
	pcList = cMemory.TestGetFreeListsHead();
	AssertNull(pcList);
	AssertInt(2092, cMemory.ByteSize());

	cMemory.TestGetLargeListsHead();

	cMemory.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void SetupTestMemoryRemove(CMemory* pcMemory)
{
	void*	pv;

	pcMemory->Init(4, FALSE);
	pcMemory->GetFreeListParams()->AddParamBlock(8, 0, 4);
	pcMemory->GetFreeListParams()->AddParamBlock(16, 8, 4);
	pcMemory->GetFreeListParams()->AddParamBlock(24, 16, 4);

	pv = pcMemory->Add(10);
	AssertInt(1, pcMemory->NumElements());
	pcMemory->Remove(pv);
	AssertInt(0, pcMemory->NumElements());

	pcMemory->Add(10);
	pcMemory->Add(11);
	pv = pcMemory->Add(12);
	pcMemory->Add(13);

	pcMemory->Add(9);
	pcMemory->Add(14);
	pcMemory->Add(10);
	pcMemory->Add(9);

	pcMemory->Add(9);
	pcMemory->Add(14);

	pcMemory->Remove(pv);
	AssertInt(9, pcMemory->NumElements());
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMemoryRemoveAllByArray(void)
{
	CMemory				cMemory;
	CArrayVoidPtr		apv;
	SMemoryIterator		sIter;
	SMemory				sMem;

	SetupTestMemoryRemove(&cMemory);

	apv.Init();
	sMem = cMemory.StartIteration(&sIter);
	while (sMem.bValid)
	{
		apv.Add(sMem.pvMem);
		sMem = cMemory.Iterate(&sIter);
	}

	AssertInt(9, apv.NumElements());

	cMemory.Remove(&apv);
	AssertInt(0, cMemory.NumElements());

	apv.Kill();
	cMemory.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMemoryRemoveHalfByArray(void)
{
	CMemory				cMemory;
	CArrayVoidPtr		apv;
	SMemoryIterator		sIter;
	BOOL				bAdd;
	SMemory				sMem;

	SetupTestMemoryRemove(&cMemory);

	apv.Init();
	sMem = cMemory.StartIteration(&sIter);
	bAdd = TRUE;
	while (sMem.bValid)
	{
		if (bAdd)
		{
			apv.Add(sMem.pvMem);
		}
		bAdd = !bAdd;
		sMem = cMemory.Iterate(&sIter);
	}

	AssertInt(5, apv.NumElements());

	cMemory.Remove(&apv);
	AssertInt(4, cMemory.NumElements());

	apv.Kill();
	cMemory.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMemoryRemoveNoneByArray(void)
{
	CMemory			cMemory;
	CArrayVoidPtr	apv;

	SetupTestMemoryRemove(&cMemory);

	apv.Init();
	
	cMemory.Remove(&apv);
	AssertInt(9, cMemory.NumElements());

	apv.Kill();
	cMemory.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMemoryGrow(void)
{
	CMemory			cMemory;
	char			sz[27] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
	char*			sz1;
	char*			sz2;

	cMemory.Init();

	sz1 = (char*)cMemory.Add(16);
	memcpy(sz1, sz, 15);
	sz1[15] = 0;
	AssertString("ABCDEFGHIJKLMNO", sz1);

	sz2 = (char*)cMemory.Grow(sz1, 20);
	AssertFalse(sz1 == sz2);
	AssertString("ABCDEFGHIJKLMNO", sz2);

	cMemory.Kill();
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
	TestMemoryGrow();
	TestMemoryRemoveAllByArray();
	TestMemoryRemoveHalfByArray();
	TestMemoryRemoveNoneByArray();

	TestStatistics();
}

