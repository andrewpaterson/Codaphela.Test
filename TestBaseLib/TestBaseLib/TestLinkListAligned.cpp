#include "BaseLib/LinkListAligned.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestLinkListAlignedAdd(void)
{
	CLinkListAligned	cLinkListAligned;
	void*				pv;
	int					k;
	int					iAlignment;
	SDANode*			psNode;
	void*				pvAllocatedEnd;
	void*				pvObjectEnd;
	int					iPrevTotalSize;

	cLinkListAligned.Init();

	iPrevTotalSize = 0;
	for (iAlignment = 2; iAlignment <= 48; iAlignment++)
	{
		for (k = 0; k < 5; k++)
		{
			pv = cLinkListAligned.InsertAfterTail(65, iAlignment, 0);
			AssertInt(0, ((int)(ENGINE_SIZE_T) pv) % iAlignment);

			psNode = cLinkListAligned.GetNode(pv);
			pvAllocatedEnd = (void*)(ENGINE_SIZE_T) ((int)(ENGINE_SIZE_T) psNode->sAligned.pvAlloc + sizeof(SDANode) + 65 + iAlignment -1);
			pvObjectEnd = (void*)(ENGINE_SIZE_T) ((int)(ENGINE_SIZE_T) pv + 65);
			AssertTrue(pvAllocatedEnd >= pvObjectEnd);
			AssertInt(iPrevTotalSize + ((sizeof(SDANode) + 65 + iAlignment-1) * (k + 1)), cLinkListAligned.ByteSize());
		}
		iPrevTotalSize += ((sizeof(SDANode) + 65 + iAlignment-1) * k);
	}
	AssertInt(27495, iPrevTotalSize);

	cLinkListAligned.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestLinkListAlignedRemove(void)
{
	CLinkListAligned	cLinkListAligned;
	void*				pv1;
	void*				pv2;
	void*				pv3;
	void*				pv;

	cLinkListAligned.Init();
	pv1 = cLinkListAligned.InsertAfterTail(1, 4, 0);
	pv2 = cLinkListAligned.InsertAfterTail(2, 4, 0);
	pv3 = cLinkListAligned.InsertAfterTail(3, 4, 0);
	cLinkListAligned.Remove(pv2);

	pv = cLinkListAligned.GetHead();
	AssertPointer(pv1, pv);
	pv = cLinkListAligned.GetNext(pv);
	AssertPointer(pv3, pv);
	pv = cLinkListAligned.GetNext(pv);
	AssertNull(pv);

	cLinkListAligned.Remove(pv1);
	cLinkListAligned.Remove(pv3);

	pv = cLinkListAligned.GetHead();
	AssertNull(pv);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestLinkListAlignedGrow(void)
{
	CLinkListAligned	cLinkListAligned;
	int*				pi;
	void*				pvOld;
	void*				pvNew;

	cLinkListAligned.Init();
	pi = (int*)cLinkListAligned.InsertAfterTail(20, 4, 0);
	pi[0] = 0;
	pi[1] = 1;
	pi[2] = 2;
	pi[3] = 3;
	pi[4] = 4;
	
	pi = (int*)cLinkListAligned.Grow(pi, 24);
	AssertInt(0, pi[0]);
	AssertInt(1, pi[1]);
	AssertInt(2, pi[2]);
	AssertInt(3, pi[3]);
	AssertInt(4, pi[4]);

	pi[5] = 5;

	pi = (int*)cLinkListAligned.Grow(pi, 8);
	AssertInt(0, pi[0]);
	AssertInt(1, pi[1]);

	pi = (int*)cLinkListAligned.Grow(pi, 0);
	AssertNull(pi);
	cLinkListAligned.Kill();

	cLinkListAligned.Init();
	pvOld = cLinkListAligned.InsertAfterTail(1, 4, 0);
	pvNew = cLinkListAligned.Grow(pvOld, 2);
	AssertPointer(pvOld, pvNew);
	pvNew = cLinkListAligned.Grow(pvOld, 3);
	AssertPointer(pvOld, pvNew);
	pvNew = cLinkListAligned.Grow(pvOld, 3);
	AssertPointer(pvOld, pvNew);
	pvNew = cLinkListAligned.Grow(pvOld, 4);
	AssertPointer(pvOld, pvNew);
	pvNew = cLinkListAligned.Grow(pvOld, 8);
	AssertFalse(pvOld == pvNew);
	cLinkListAligned.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestLinkListAligned(void)
{
	BeginTests();

	TestLinkListAlignedAdd();
	TestLinkListAlignedRemove();
	TestLinkListAlignedGrow();

	TestStatistics();
}

