#include "BaseLib/LinkedListBlockAligned.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestLinkedListBlockAlignedAdd(void)
{
	CLinkedListBlockAligned	cLinkedListBlockAligned;
	void*				pv;
	int					k;
	int					iAlignment;
	SLLANode*			psNode;
	void*				pvAllocatedEnd;
	void*				pvObjectEnd;
	int					iPrevTotalSize;

	cLinkedListBlockAligned.Init();

	iPrevTotalSize = 0;
	for (iAlignment = 2; iAlignment <= 48; iAlignment++)
	{
		for (k = 0; k < 5; k++)
		{
			pv = cLinkedListBlockAligned.InsertAfterTail(65, iAlignment, 0);
			AssertInt(0, ((int)(size_t) pv) % iAlignment);

			psNode = cLinkedListBlockAligned.GetNode(pv);
			pvAllocatedEnd = (void*)(size_t) ((int)(size_t) psNode->sAligned.pvAlloc + sizeof(SLLANode) + 65 + iAlignment -1);
			pvObjectEnd = (void*)(size_t) ((int)(size_t) pv + 65);
			AssertTrue(pvAllocatedEnd >= pvObjectEnd);
			AssertInt(iPrevTotalSize + ((sizeof(SLLANode) + 65 + iAlignment-1) * (k + 1)), cLinkedListBlockAligned.ByteSize());
		}
		iPrevTotalSize += ((sizeof(SLLANode) + 65 + iAlignment-1) * k);
	}
	AssertInt(27495, iPrevTotalSize);

	cLinkedListBlockAligned.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestLinkedListBlockAlignedRemove(void)
{
	CLinkedListBlockAligned	cLinkedListBlockAligned;
	void*				pv1;
	void*				pv2;
	void*				pv3;
	void*				pv;

	cLinkedListBlockAligned.Init();
	pv1 = cLinkedListBlockAligned.InsertAfterTail(1, 4, 0);
	pv2 = cLinkedListBlockAligned.InsertAfterTail(2, 4, 0);
	pv3 = cLinkedListBlockAligned.InsertAfterTail(3, 4, 0);
	cLinkedListBlockAligned.Remove(pv2);

	pv = cLinkedListBlockAligned.GetHead();
	AssertPointer(pv1, pv);
	pv = cLinkedListBlockAligned.GetNext(pv);
	AssertPointer(pv3, pv);
	pv = cLinkedListBlockAligned.GetNext(pv);
	AssertNull(pv);

	cLinkedListBlockAligned.Remove(pv1);
	cLinkedListBlockAligned.Remove(pv3);

	pv = cLinkedListBlockAligned.GetHead();
	AssertNull(pv);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestLinkedListBlockAlignedGrow(void)
{
	CLinkedListBlockAligned	cLinkedListBlockAligned;
	int*				pi;
	void*				pvOld;
	void*				pvNew;

	cLinkedListBlockAligned.Init();
	pi = (int*)cLinkedListBlockAligned.InsertAfterTail(20, 4, 0);
	pi[0] = 0;
	pi[1] = 1;
	pi[2] = 2;
	pi[3] = 3;
	pi[4] = 4;
	
	pi = (int*)cLinkedListBlockAligned.Grow(pi, 24);
	AssertInt(0, pi[0]);
	AssertInt(1, pi[1]);
	AssertInt(2, pi[2]);
	AssertInt(3, pi[3]);
	AssertInt(4, pi[4]);

	pi[5] = 5;

	pi = (int*)cLinkedListBlockAligned.Grow(pi, 8);
	AssertInt(0, pi[0]);
	AssertInt(1, pi[1]);

	pi = (int*)cLinkedListBlockAligned.Grow(pi, 0);
	AssertNull(pi);
	cLinkedListBlockAligned.Kill();

	cLinkedListBlockAligned.Init();
	pvOld = cLinkedListBlockAligned.InsertAfterTail(1, 4, 0);
	pvNew = cLinkedListBlockAligned.Grow(pvOld, 2);
	AssertPointer(pvOld, pvNew);
	pvNew = cLinkedListBlockAligned.Grow(pvOld, 3);
	AssertPointer(pvOld, pvNew);
	pvNew = cLinkedListBlockAligned.Grow(pvOld, 3);
	AssertPointer(pvOld, pvNew);
	pvNew = cLinkedListBlockAligned.Grow(pvOld, 4);
	AssertPointer(pvOld, pvNew);
	pvNew = cLinkedListBlockAligned.Grow(pvOld, 8);
	AssertFalse(pvOld == pvNew);
	cLinkedListBlockAligned.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestLinkedListBlockAligned(void)
{
	BeginTests();

	TestLinkedListBlockAlignedAdd();
	TestLinkedListBlockAlignedRemove();
	TestLinkedListBlockAlignedGrow();

	TestStatistics();
}

