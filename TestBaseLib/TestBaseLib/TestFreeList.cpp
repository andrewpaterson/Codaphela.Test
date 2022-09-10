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
void TestFreeListSizeof(void)
{
	AssertInt(32, sizeof(CFreeList));
	AssertInt(8, sizeof(SFNode));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFreeListAllocation(void)
{
	CFreeList	cFreeList;
	void*		pv1;
	void*		pv2;
	void*		pv3;
	void*		pv4;
	void*		pv5;
	void*		pv6;
	void*		pv7;
	void*		pv8;
	void*		pv9;
	SFNode*		psNode0;
	SFNode*		psNode1;
	SFNode*		psNode2;

	cFreeList.Init(7, 1);
	AssertInt(0, cFreeList.GetNumAllocatedChunks());
	AssertInt(0, cFreeList.NumElements());

	pv1 = cFreeList.Add();
	AssertInt(1, cFreeList.GetNumAllocatedChunks());
	AssertInt(1, cFreeList.NumElements());

	pv2 = cFreeList.Add();
	pv3 = cFreeList.Add();
	pv4 = cFreeList.Add();
	pv5 = cFreeList.Add();
	AssertInt(1, cFreeList.GetNumAllocatedChunks());
	AssertInt(5, cFreeList.NumElements());
	AssertIteration(&cFreeList, pv1, pv2, pv3, pv4, pv5, NULL);

	cFreeList.Remove(pv2);
	AssertInt(1, cFreeList.GetNumAllocatedChunks());
	AssertInt(4, cFreeList.NumElements());
	psNode0 = cFreeList.GetNode(0);
	pv2 = cFreeList.GetElement(psNode0, 1);
	AssertNull(pv2);
	AssertIteration(&cFreeList, pv1, pv3, pv4, pv5, NULL);

	cFreeList.Remove(pv1);
	AssertInt(1, cFreeList.GetNumAllocatedChunks());
	AssertInt(3, cFreeList.NumElements());
	psNode1 = cFreeList.GetNode(0);
	AssertPointer(psNode1, psNode0);
	AssertIteration(&cFreeList, pv3, pv4, pv5, NULL);

	pv6 = cFreeList.Add();
	AssertInt(1, cFreeList.GetNumAllocatedChunks());
	AssertInt(4, cFreeList.NumElements());
	AssertIteration(&cFreeList, pv6, pv3, pv4, pv5, NULL);

	pv7 = cFreeList.Add();
	pv8 = cFreeList.Add();
	pv9 = cFreeList.Add();
	pv1 = cFreeList.Add();
	AssertInt(1, cFreeList.GetNumAllocatedChunks());
	AssertInt(8, cFreeList.NumElements());
	AssertIteration(&cFreeList, pv6, pv7, pv3, pv4, pv5, pv8, pv9, pv1, NULL);

	pv2 = cFreeList.Add();
	AssertInt(2, cFreeList.GetNumAllocatedChunks());
	AssertInt(9, cFreeList.NumElements());
	psNode1 = cFreeList.GetNode(1);
	AssertFalse(psNode0 == psNode1);  //Make sure the "freed" node is reused.
	AssertIteration(&cFreeList, pv6, pv7, pv3, pv4, pv5, pv8, pv9, pv1, pv2, NULL);

	cFreeList.Remove(pv2);
	AssertInt(1, cFreeList.GetNumAllocatedChunks());
	AssertInt(8, cFreeList.NumElements());
	AssertIteration(&cFreeList, pv6, pv7, pv3, pv4, pv5, pv8, pv9, pv1, NULL);

	pv2 = cFreeList.Add();
	AssertInt(2, cFreeList.GetNumAllocatedChunks());
	AssertInt(9, cFreeList.NumElements());
	psNode2 = cFreeList.GetNode(1);
	AssertPointer(psNode1, psNode2);  //Make sure the "freed" node is reused.
	AssertIteration(&cFreeList, pv6, pv7, pv3, pv4, pv5, pv8, pv9, pv1, pv2, NULL);

	cFreeList.Kill();
}


typedef CArrayTemplate<CFreeList>	CArrayFreeList;


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFreeListAlignment(void)
{
	CArrayFreeList	cArray;
	char			iAlignment;
	CFreeList*		pcFreeList;
	void*			pv;
	int				k;
	CFreeList		cFreeList;
	SFNode*			psNode;
	int				i;

	cArray.Init();

	for (iAlignment = 2; iAlignment <= 48; iAlignment++)
	{
		pcFreeList = cArray.Add();
		pcFreeList->Init(iAlignment, iAlignment);
		AssertInt((int)iAlignment, pcFreeList->GetElementStride());
		AssertInt((int)iAlignment, pcFreeList->GetElementSize());

		for (k = 0; k < 9; k++)
		{
			pv = pcFreeList->Add();
			AssertInt(0, ((int)(size_t) pv) % iAlignment);
			psNode = pcFreeList->FindNode(pv, false);
			AssertTrue(psNode->iOffset < iAlignment);
		}
	}

	for (i = 0; i < cArray.NumElements(); i++)
	{
		pcFreeList = cArray.Get(i);
		pcFreeList->Kill();
	}

	cArray.Kill();

	cFreeList.Init(10, 16);
	AssertInt(16, cFreeList.GetElementStride());
	AssertInt(10, cFreeList.GetElementSize());
	cFreeList.Kill();

	cFreeList.Init(20, 16);
	AssertInt(32, cFreeList.GetElementStride());
	AssertInt(20, cFreeList.GetElementSize());
	cFreeList.Kill();

	cFreeList.Init(1, 4);
	AssertInt(4, cFreeList.GetElementStride());
	cFreeList.Kill();

	cFreeList.Init(2, 4);
	AssertInt(4, cFreeList.GetElementStride());
	cFreeList.Kill();

	cFreeList.Init(3, 4);
	AssertInt(4, cFreeList.GetElementStride());
	cFreeList.Kill();

	cFreeList.Init(4, 4);
	AssertInt(4, cFreeList.GetElementStride());
	cFreeList.Kill();

	cFreeList.Init(5, 4);
	AssertInt(8, cFreeList.GetElementStride());
	cFreeList.Kill();

	cFreeList.Init(6, 4);
	AssertInt(8, cFreeList.GetElementStride());
	cFreeList.Kill();

	cFreeList.Init(7, 4);
	AssertInt(8, cFreeList.GetElementStride());
	cFreeList.Kill();

	cFreeList.Init(8, 4);
	AssertInt(8, cFreeList.GetElementStride());
	cFreeList.Kill();
}



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFreeListOffsetAlignment(void)
{
	CArrayFreeList	cArray;
	uint16	iElementSize;
	char			iOffset;
	CFreeList*		pcFreeList;
	void*			pv;
	int				i;
	char			iAlignment;

	cArray.Init();

	for (iAlignment = 2; iAlignment <= 6; iAlignment++)
	{
		for (iElementSize = 2; iElementSize <= 8; iElementSize++)
		{
			for (iOffset = -1; iOffset <= 7; iOffset++)
			{
				pcFreeList = cArray.Add();
				pcFreeList->Init(iElementSize, iAlignment, iOffset);

				for (i = 0; i < 5; i++)
				{
					pv = pcFreeList->Add();
					if (iOffset >= 0)
					{
						AssertInt(iOffset % iAlignment, ((int)(size_t) pv) % iAlignment);
					}
					else
					{
						AssertInt(iAlignment - (-iOffset % iAlignment), ((int)(size_t) pv) % iAlignment);
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

	TestFreeListSizeof();
	TestFreeListAllocation();
	TestFreeListAlignment();
	TestFreeListOffsetAlignment();

	TestStatistics();
}

