#include "BaseLib/FreeList.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertIteration(CFreeList* pcFreeList, void* pvFirst, ...)
{
	va_list				vaMarker;
	void*				pv;
	int					iCount;
	SFreeListIterator	sIter;
	void*				pvTest;

	iCount = 0;
	pv = pvFirst;

	pvTest = pcFreeList->StartIteration(&sIter);

	va_start(vaMarker, pvFirst);
	while ((pv != NULL) || (pvTest != NULL))
	{
		if (pv != pvTest)
		{
			AssertPointer(pv, pvTest);
			return;
		}

		pvTest = pcFreeList->Iterate(&sIter);
		iCount++;
		pv = va_arg(vaMarker, void*);
	}
	va_end(vaMarker);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFreeListAllocation(void)
{
	CFreeList	cFreeList;
	void*				pv1;
	void*				pv2;
	void*				pv3;
	void*				pv4;
	void*				pv5;
	void*				pv6;
	void*				pv7;
	SFNode*				psNode0;
	SFNode*				psNode1;
	SFNode*				psNode2;

	cFreeList.Init(2, 7, 1);
	AssertInt(0, cFreeList.GetNumAllocatedChunks());
	AssertInt(0, cFreeList.NumElements());

	pv1 = cFreeList.Add();
	AssertInt(1, cFreeList.GetNumAllocatedChunks());
	AssertInt(1, cFreeList.NumElements());

	pv2 = cFreeList.Add();
	AssertInt(1, cFreeList.GetNumAllocatedChunks());
	AssertInt(2, cFreeList.NumElements());

	pv3 = cFreeList.Add();
	AssertInt(2, cFreeList.GetNumAllocatedChunks());
	AssertInt(3, cFreeList.NumElements());

	pv4 = cFreeList.Add();
	AssertInt(2, cFreeList.GetNumAllocatedChunks());
	AssertInt(4, cFreeList.NumElements());

	pv5 = cFreeList.Add();
	AssertInt(3, cFreeList.GetNumAllocatedChunks());
	AssertInt(5, cFreeList.NumElements());
	AssertIteration(&cFreeList, pv1, pv2, pv3, pv4, pv5, NULL);

	cFreeList.Remove(pv2);
	AssertInt(3, cFreeList.GetNumAllocatedChunks());
	AssertInt(4, cFreeList.NumElements());
	psNode0 = cFreeList.GetNode(0);
	pv2 = cFreeList.GetElement(psNode0, 1);
	AssertNull(pv2);
	AssertIteration(&cFreeList, pv1, pv3, pv4, pv5, NULL);

	cFreeList.Remove(pv1);
	AssertInt(2, cFreeList.GetNumAllocatedChunks());
	AssertInt(3, cFreeList.NumElements());
	psNode1 = cFreeList.GetNode(0);
	AssertFalse(psNode1 == psNode0);
	AssertIteration(&cFreeList, pv3, pv4, pv5, NULL);

	pv6 = cFreeList.Add();
	AssertInt(2, cFreeList.GetNumAllocatedChunks());
	AssertInt(4, cFreeList.NumElements());
	AssertIteration(&cFreeList, pv3, pv4, pv5, pv6, NULL);

	pv7 = cFreeList.Add();
	AssertInt(3, cFreeList.GetNumAllocatedChunks());
	AssertInt(5, cFreeList.NumElements());
	AssertIteration(&cFreeList, pv3, pv4, pv5, pv6, pv7, NULL);
	psNode2 = cFreeList.GetNode(2);
	AssertPointer(psNode0, psNode2);  //Make sure the "freed" node is reused.

	cFreeList.Kill();
}


typedef CArrayTemplate<CFreeList>	CArrayFreeList;


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFreeListAlignment(void)
{
	CArrayFreeList		cArray;
	int					i;
	int					j;
	CFreeList*	pcFreeList;
	void*				pv;
	int					k;
	CFreeList	cFreeList;
	SFNode*				psNode;

	cArray.Init();

	for (i = 2; i <= 48; i++)
	{
		for (j = 1; j <= 4; j++)
		{
			pcFreeList = cArray.Add();
			pcFreeList->Init(j, i, i);
			AssertInt(i, pcFreeList->GetElementStride());
			AssertInt(i, pcFreeList->GetElementSize());

			for (k = 0; k < 5; k++)
			{
				pv = pcFreeList->Add();
				AssertInt(0, ((int)(ENGINE_SIZE_T) pv) % i);
				psNode = pcFreeList->FindNode(pv, FALSE);
				AssertTrue(psNode->iOffset < i);
			}
		}
	}

	for (i = 0; i < cArray.NumElements(); i++)
	{
		pcFreeList = cArray.Get(i);
		pcFreeList->Kill();
	}

	cArray.Kill();

	cFreeList.Init(1, 10, 16);
	AssertInt(16, cFreeList.GetElementStride());
	AssertInt(10, cFreeList.GetElementSize());
	cFreeList.Kill();

	cFreeList.Init(1, 20, 16);
	AssertInt(32, cFreeList.GetElementStride());
	AssertInt(20, cFreeList.GetElementSize());
	cFreeList.Kill();

	cFreeList.Init(1, 1, 4);
	AssertInt(4, cFreeList.GetElementStride());
	cFreeList.Kill();

	cFreeList.Init(1, 2, 4);
	AssertInt(4, cFreeList.GetElementStride());
	cFreeList.Kill();

	cFreeList.Init(1, 3, 4);
	AssertInt(4, cFreeList.GetElementStride());
	cFreeList.Kill();

	cFreeList.Init(1, 4, 4);
	AssertInt(4, cFreeList.GetElementStride());
	cFreeList.Kill();

	cFreeList.Init(1, 5, 4);
	AssertInt(8, cFreeList.GetElementStride());
	cFreeList.Kill();

	cFreeList.Init(1, 6, 4);
	AssertInt(8, cFreeList.GetElementStride());
	cFreeList.Kill();

	cFreeList.Init(1, 7, 4);
	AssertInt(8, cFreeList.GetElementStride());
	cFreeList.Kill();

	cFreeList.Init(1, 8, 4);
	AssertInt(8, cFreeList.GetElementStride());
	cFreeList.Kill();
}



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFreeListOffsetAlignment(void)
{
	CArrayFreeList		cArray;
	int					iElementSize;
	int					iOffset;
	CFreeList*	pcFreeList;
	void*				pv;
	int					i;
	int					iAlignment;

	cArray.Init();

	for (iAlignment = 2; iAlignment <= 6; iAlignment++)
	{
		for (iElementSize = 2; iElementSize <= 8; iElementSize++)
		{
			for (iOffset = -1; iOffset <= 7; iOffset++)
			{
				pcFreeList = cArray.Add();
				pcFreeList->Init(1, iElementSize, iAlignment, iOffset);

				for (i = 0; i < 5; i++)
				{
					pv = pcFreeList->Add();
					if (iOffset >= 0)
					{
						AssertInt(iOffset % iAlignment, ((int)(ENGINE_SIZE_T) pv) % iAlignment);
					}
					else
					{
						AssertInt(iAlignment - (-iOffset % iAlignment), ((int)(ENGINE_SIZE_T) pv) % iAlignment);
					}
				}
			}
		}
	}

	for (i = 0; i < cArray.NumElements(); i++)
	{
		pcFreeList = cArray.Get(i);
		pcFreeList->Kill();
	}

	cArray.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFreeList(void)
{
	BeginTests();

	TestFreeListAllocation();
	TestFreeListAlignment();
	TestFreeListOffsetAlignment();

	TestStatistics();
}

