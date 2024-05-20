#include "BaseLib/MemoryCache.h"
#include "BaseLib/MemoryCacheEvictedData.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void FillCachedElement(void* pvData, int iSize, char c)
{
	memset_fast(pvData, c, iSize-1);
	((char*)pvData)[iSize-1] = '\0';
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertElement(void* pvData, size uiDataSize, char cExpected)
{
	char* szData;
	CChars	szExpected;

	szData = (char*)pvData;
	szExpected.Init();
	szExpected.Append(cExpected, uiDataSize - 1);
	AssertString(szExpected.Text(), szData);
	szExpected.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertCacheElement(CMemoryCache* pcCache, void* pvData, size uiDataSize, char cExpected)
{
	AssertInt(uiDataSize, pcCache->GetSize(pvData));

	AssertElement(pvData, uiDataSize, cExpected);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertLinkOrder(CMemoryCache* pcCache)
{
	void*					psCacheDesc;
	void*					psCacheDescReverse;
	CArrayVoidPtr			cPointers;
	int						i;

	AssertPointer(pcCache->GetPrev(pcCache->GetFirst()), pcCache->GetLast());
	AssertPointer(pcCache->GetNext(pcCache->GetLast()), pcCache->GetFirst());

	cPointers.Init();
	psCacheDesc = pcCache->GetFirst();

	for (;;)
	{
		cPointers.Add(psCacheDesc);
		psCacheDesc = pcCache->GetNext(psCacheDesc);
		if (psCacheDesc == pcCache->GetFirst())
		{
			break;
		}
	}

	psCacheDesc = pcCache->GetLast();
	i = cPointers.NumElements();
	do
	{
		i--;
		psCacheDescReverse = (SMemoryCacheDescriptor*)cPointers.GetPtr(i);
		
		AssertPointer(psCacheDesc, psCacheDescReverse);

		psCacheDesc = pcCache->GetPrev(psCacheDesc);
	}
	while (i != 0);

	cPointers.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertCache(CMemoryCache* pcCache, int iFirstLength, char cFirstChar)
{
	void*		psFirst;
	void*		psLast;

	AssertInt(1, pcCache->NumElements());
	
	psFirst = pcCache->GetFirst();
	AssertNotNull(psFirst);
	AssertPointer(psFirst, pcCache->GetNext(psFirst));

	psLast = pcCache->GetLast();
	AssertPointer(psFirst, psLast);

	AssertPointer(psLast, pcCache->GetNext(psLast));
	
	AssertCacheElement(pcCache, psFirst, iFirstLength, cFirstChar);

	AssertLinkOrder(pcCache);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertCache(CMemoryCache* pcCache, int iFirstLength, char cFirstChar, int iSecondLength, char cSecondChar)
{
	void*		psFirst;
	void*		psLast;

	AssertInt(2, pcCache->NumElements());

	psFirst = pcCache->GetFirst();
	psLast = pcCache->GetLast();
	AssertNotNull(psFirst);
	AssertFalse(psFirst == psLast);

	AssertPointer(psLast, pcCache->GetNext(psFirst));
	AssertPointer(psFirst, pcCache->GetNext(psLast));

	AssertCacheElement(pcCache, psFirst, iFirstLength, cFirstChar);
	AssertCacheElement(pcCache, psLast, iSecondLength, cSecondChar);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertCache(CMemoryCache* pcCache, int iLen1, char c1, int iLen2, char c2, int iLen3, char c3)
{
	void*		psFirst;
	void*		psLast;

	AssertInt(3, pcCache->NumElements());

	psFirst = pcCache->GetFirst();
	psLast = pcCache->GetLast();
	AssertNotNull(psFirst);
	AssertFalse(psFirst == psLast);
	AssertFalse(pcCache->GetNext(psFirst) == psLast);

	AssertPointer(pcCache->GetNext(pcCache->GetNext(psFirst)), psLast);
	AssertPointer(pcCache->GetNext(psLast), psFirst);

	AssertCacheElement(pcCache, psFirst, iLen1, c1);
	AssertCacheElement(pcCache, pcCache->GetNext(psFirst), iLen2, c2);
	AssertCacheElement(pcCache, pcCache->GetNext(pcCache->GetNext(psFirst)), iLen3, c3);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMemoryCacheSimple(void)
{
	CMemoryCache	cCache;
	void*			pvData;

	cCache.Init(64 + sizeof(SMemoryCacheDescriptor), NULL);

	pvData = cCache.Allocate(52);
	AssertNotNull(pvData);
	FillCachedElement(pvData, 52, 'A');
	AssertCache(&cCache, 52, 'A');

	pvData = cCache.Allocate(20);
	AssertNotNull(pvData);
	FillCachedElement(pvData, 20, 'B');
	AssertCache(&cCache, 20, 'B');

	pvData = cCache.Allocate(20);
	AssertNotNull(pvData);
	FillCachedElement(pvData, 20, 'C');
	AssertCache(&cCache, 20, 'B', 20, 'C');

	cCache.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMemoryCacheBrokenExample(void)
{
	CMemoryCache	cCache;
	void*			pvData;

	cCache.Init(64 + sizeof(SMemoryCacheDescriptor), NULL);

	pvData = cCache.Allocate(20);
	FillCachedElement(pvData, 20, 'A');
	AssertCache(&cCache, 20, 'A');

	pvData = cCache.Allocate(20);
	FillCachedElement(pvData, 20, 'B');
	AssertCache(&cCache, 20, 'A', 20, 'B');

	pvData = cCache.Allocate(20);
	FillCachedElement(pvData, 20, 'C');
	AssertCache(&cCache, 20, 'B', 20, 'C');

	pvData = cCache.Allocate(20);
	AssertNotNull(pvData);
	FillCachedElement(pvData, 20, 'D');
	AssertCache(&cCache, 20, 'C', 20, 'D');

	cCache.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMemoryCacheEvictAll(void)
{
	CMemoryCache	cCache;
	void*			pvData;

	cCache.Init(64 + sizeof(SMemoryCacheDescriptor), NULL);

	pvData = cCache.Allocate(17);
	AssertNotNull(pvData);
	FillCachedElement(pvData, 17, 'A');
	AssertCache(&cCache, 17, 'A');

	pvData = cCache.Allocate(6);
	AssertNotNull(pvData);
	FillCachedElement(pvData, 6, 'B');
	AssertCache(&cCache, 17, 'A', 6, 'B');

	pvData = cCache.Allocate(47);
	AssertNotNull(pvData);
	FillCachedElement(pvData, 47, 'C');
	AssertCache(&cCache, 47, 'C');

	cCache.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMemoryCacheEvictLeftmost(void)
{
	CMemoryCache	cCache;
	void*			pvData;

	cCache.Init(64 + sizeof(SMemoryCacheDescriptor), NULL);

	pvData = cCache.Allocate(8);
	FillCachedElement(pvData, 8, 'A');
	pvData = cCache.Allocate(9);
	FillCachedElement(pvData, 9, 'B');
	pvData = cCache.Allocate(8);
	FillCachedElement(pvData, 8, 'C');
	AssertCache(&cCache, 8, 'A', 9, 'B', 8, 'C');

	//Um, not sure why testing this here...
	pvData = cCache.Allocate(47);
	AssertNotNull(pvData);
	FillCachedElement(pvData, 47, 'C');
	AssertCache(&cCache, 47, 'C');

	cCache.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMemoryCacheEvictRightmost(void)
{
	CMemoryCache	cCache;
	void*			pvData;

	cCache.Init(64 + sizeof(SMemoryCacheDescriptor), NULL);
	AssertInt(0, cCache.GetAllocatedSize());

	pvData = cCache.Allocate(8);
	FillCachedElement(pvData, 8, 'A');
	AssertInt(8 + sizeof(SMemoryCacheDescriptor), cCache.GetAllocatedSize());

	pvData = cCache.Allocate(9);
	FillCachedElement(pvData, 9, 'B');
	AssertInt(8 + 9 + 2 * sizeof(SMemoryCacheDescriptor), cCache.GetAllocatedSize());

	pvData = cCache.Allocate(8);
	FillCachedElement(pvData, 8, 'C');
	AssertInt(8 + 9 + 8 + 3 * sizeof(SMemoryCacheDescriptor), cCache.GetAllocatedSize());
	AssertInt(61, cCache.GetAllocatedSize());
	AssertCache(&cCache, 8, 'A', 9, 'B', 8, 'C');

	pvData = cCache.Allocate(7);
	FillCachedElement(pvData, 7, 'D');
	AssertInt(7 + 9 + 8 + 3 * sizeof(SMemoryCacheDescriptor), cCache.GetAllocatedSize());
	AssertInt(60, cCache.GetAllocatedSize());
	AssertCache(&cCache, 9, 'B', 8, 'C', 7, 'D');

	pvData = cCache.Allocate(6);
	FillCachedElement(pvData, 6, 'E');
	AssertInt(8 + 7 + 6 + 3 * sizeof(SMemoryCacheDescriptor), cCache.GetAllocatedSize());
	AssertCache(&cCache, 8, 'C', 7, 'D', 6, 'E');

	pvData = cCache.Allocate(9);
	FillCachedElement(pvData, 9, 'F');
	AssertInt(7 + 6 + 9 + 3 * sizeof(SMemoryCacheDescriptor), cCache.GetAllocatedSize());
	AssertCache(&cCache, 7, 'D', 6, 'E', 9, 'F');

	pvData = cCache.Allocate(8);
	FillCachedElement(pvData, 8, 'A');
	AssertInt(9 + 8 + 2 * sizeof(SMemoryCacheDescriptor), cCache.GetAllocatedSize());
	AssertInt(41, cCache.GetAllocatedSize());  // out of 76 (35 remain)
	AssertCache(&cCache, 9, 'F', 8, 'A');

	pvData = cCache.Allocate(17);
	FillCachedElement(pvData, 17, 'B');
	AssertInt(17 + 8 + 2 * sizeof(SMemoryCacheDescriptor), cCache.GetAllocatedSize());
	AssertInt(49, cCache.GetAllocatedSize());  // out of 76 (27 remain)
	AssertCache(&cCache, 8, 'A', 17, 'B');

	pvData = cCache.Allocate(9);
	FillCachedElement(pvData, 9, 'Z');
	AssertInt(8 + 17 + 9 + 3 * sizeof(SMemoryCacheDescriptor), cCache.GetAllocatedSize());
	AssertCache(&cCache, 8, 'A', 17, 'B', 9, 'Z');

	pvData = cCache.Allocate(64);
	FillCachedElement(pvData, 64, 'Q');
	AssertInt(64 + sizeof(SMemoryCacheDescriptor), cCache.GetAllocatedSize());
	AssertCache(&cCache, 64, 'Q');

	pvData = cCache.Allocate(65);
	AssertNull(pvData);

	pvData = cCache.Allocate(32);
	FillCachedElement(pvData, 32, 'P');
	AssertInt(32 + sizeof(SMemoryCacheDescriptor), cCache.GetAllocatedSize());
	AssertCache(&cCache, 32, 'P');

	pvData = cCache.Allocate(16);
	FillCachedElement(pvData, 16, 'R');
	AssertInt(32 + 16 + 2 * sizeof(SMemoryCacheDescriptor), cCache.GetAllocatedSize());
	AssertCache(&cCache, 32, 'P', 16, 'R');

	cCache.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMemoryCacheDeallocate(void)
{
	CMemoryCache	cCache;
	void*			pvA;
	void*			pvB;
	void*			pvC;

	cCache.Init(128, NULL);

	pvA = cCache.Allocate(8);
	FillCachedElement(pvA, 8, 'A');
	pvB = cCache.Allocate(9);
	FillCachedElement(pvB, 9, 'B');
	pvC = cCache.Allocate(8);
	FillCachedElement(pvC, 8, 'C');

	AssertCache(&cCache, 8, 'A', 9, 'B', 8, 'C');
	AssertInt(61, cCache.GetAllocatedSize());

	cCache.Deallocate(pvA);
	AssertCache(&cCache, 9, 'B', 8, 'C');
	AssertInt(41, cCache.GetAllocatedSize());

	cCache.Deallocate(pvC);
	AssertCache(&cCache, 9, 'B');
	AssertInt(21, cCache.GetAllocatedSize());

	cCache.Deallocate(pvB);
	AssertInt(0, cCache.GetAllocatedSize());

	pvA = cCache.Allocate(8);
	FillCachedElement(pvA, 8, 'A');
	pvB = cCache.Allocate(9);
	FillCachedElement(pvB, 9, 'B');
	pvC = cCache.Allocate(8);
	FillCachedElement(pvC, 8, 'C');

	AssertCache(&cCache, 8, 'A', 9, 'B', 8, 'C');
	AssertInt(61, cCache.GetAllocatedSize());

	cCache.Deallocate(pvB);
	AssertCache(&cCache, 8, 'A', 8, 'C');
	AssertInt(40, cCache.GetAllocatedSize());

	cCache.Deallocate(pvA);
	AssertCache(&cCache, 8, 'C');
	AssertInt(20, cCache.GetAllocatedSize());

	cCache.Deallocate(pvC);
	AssertInt(0, cCache.GetAllocatedSize());

	pvA = cCache.Allocate(8);
	FillCachedElement(pvA, 8, 'A');
	pvB = cCache.Allocate(9);
	FillCachedElement(pvB, 9, 'B');
	pvC = cCache.Allocate(8);
	FillCachedElement(pvC, 8, 'C');

	AssertCache(&cCache, 8, 'A', 9, 'B', 8, 'C');
	AssertInt(61, cCache.GetAllocatedSize());

	cCache.Deallocate(pvB);
	AssertCache(&cCache, 8, 'A', 8, 'C');
	AssertInt(40, cCache.GetAllocatedSize());

	cCache.Deallocate(pvC);
	AssertCache(&cCache, 8, 'A');
	AssertInt(20, cCache.GetAllocatedSize());

	cCache.Deallocate(pvA);
	AssertInt(0, cCache.GetAllocatedSize());

	cCache.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMemoryCachePreallocate(void)
{
	CMemoryCache			cCache;
	void*					pvA;
	void*					pvB;
	void*					pvC;
	void*					pvD;
	void*					pv;
	CMemoryCacheEvictedData	cEvictedData;

	cCache.Init(128, &cEvictedData);

	cEvictedData.Init();
	pvA = cCache.Allocate(40);
	FillCachedElement(pvA, 40, 'A');
	AssertInt(0, cEvictedData.NumElements());
	cEvictedData.Kill();

	cEvictedData.Init();
	pvB = cCache.Allocate(40);
	FillCachedElement(pvB, 40, 'B');
	AssertInt(0, cEvictedData.NumElements());
	cEvictedData.Kill();

	cEvictedData.Init();
	pvC = cCache.Allocate(38);
	AssertInt(1, cEvictedData.NumElements());
	pv = cEvictedData.Get(0);
	AssertElement(pv, 40, 'A');
	FillCachedElement(pvC, 38, 'C');
	AssertCacheElement(&cCache, pvC, 38, 'C');
	cEvictedData.Kill();

	cEvictedData.Init();
	pvD = cCache.Allocate(38);
	AssertInt(1, cEvictedData.NumElements());
	pv = cEvictedData.Get(0);
	AssertElement(pv, 40, 'B');
	FillCachedElement(pvD, 38, 'D');
	AssertCacheElement(&cCache, pvD, 38, 'D');
	cEvictedData.Kill();

	cCache.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMemoryCacheReallocate(void)
{
	CMemoryCache	cCache;
	void*			pvA;
	void*			pvB;
	void*			pvC;
	void*			pvD;
	void*			pvE;
	void*			pvF;
	void*			pvG;
	void*			pvH;
	void*			pvI;
	void*			psIter;

	cCache.Init(128, NULL);

	pvA = cCache.Allocate(20);
	FillCachedElement(pvA, 20, 'A');
	AssertTrue(cCache.ValidateCache());

	pvB = cCache.Allocate(24);
	FillCachedElement(pvB, 24, 'B');
	AssertTrue(cCache.ValidateCache());

	pvC = cCache.Allocate(28);
	FillCachedElement(pvC, 28, 'C');
	AssertTrue(cCache.ValidateCache());

	pvD = cCache.Allocate(18);
	FillCachedElement(pvD, 18, 'D');
	AssertTrue(cCache.ValidateCache());

	AssertInt(3, cCache.NumElements());
	AssertInt(106, cCache.GetAllocatedSize());
	AssertCacheElement(&cCache, pvB, 24, 'B');
	AssertCacheElement(&cCache, pvC, 28, 'C');
	AssertCacheElement(&cCache, pvD, 18, 'D');

	cCache.Resize(256);
	Pass();

	AssertInt(3, cCache.NumElements());
	AssertInt(106, cCache.GetAllocatedSize());

	psIter = cCache.StartIteration();
	AssertTrue(pvB != psIter);
	AssertCacheElement(&cCache, psIter, 24, 'B');

	psIter = cCache.Iterate(psIter);
	AssertTrue(pvC != psIter);
	AssertCacheElement(&cCache, psIter, 28, 'C');

	psIter = cCache.Iterate(psIter);
	AssertTrue(pvD != psIter);
	AssertCacheElement(&cCache, psIter, 18, 'D');

	psIter = cCache.Iterate(psIter);
	AssertNull(psIter);
	Pass();

	pvE = cCache.Allocate(20);
	FillCachedElement(pvE, 20, 'E');

	AssertInt(4, cCache.NumElements());
	AssertInt(138, cCache.GetAllocatedSize());

	pvF = cCache.Allocate(24);
	FillCachedElement(pvF, 24, 'F');

	pvG = cCache.Allocate(28);
	FillCachedElement(pvG, 28, 'G');

	pvH = cCache.Allocate(18);
	FillCachedElement(pvH, 18, 'H');

	AssertInt(7, cCache.NumElements());
	AssertInt(244, cCache.GetAllocatedSize());

	psIter = cCache.StartIteration();
	AssertCacheElement(&cCache, psIter, 24, 'B');

	psIter = cCache.Iterate(psIter);
	AssertCacheElement(&cCache, psIter, 28, 'C');

	psIter = cCache.Iterate(psIter);
	AssertCacheElement(&cCache, psIter, 18, 'D');

	psIter = cCache.Iterate(psIter);
	AssertCacheElement(&cCache, psIter, 20, 'E');

	psIter = cCache.Iterate(psIter);
	AssertCacheElement(&cCache, psIter, 24, 'F');

	psIter = cCache.Iterate(psIter);
	AssertCacheElement(&cCache, psIter, 28, 'G');

	psIter = cCache.Iterate(psIter);
	AssertCacheElement(&cCache, psIter, 18, 'H');

	psIter = cCache.Iterate(psIter);
	AssertNull(psIter);
	Pass();

	pvI = cCache.Allocate(32);
	FillCachedElement(pvI, 32, 'I');

	AssertInt(6, cCache.NumElements());
	AssertInt(212, cCache.GetAllocatedSize());

	psIter = cCache.StartIteration();
	AssertCacheElement(&cCache, psIter, 18, 'D');

	psIter = cCache.Iterate(psIter);
	AssertCacheElement(&cCache, psIter, 20, 'E');

	psIter = cCache.Iterate(psIter);
	AssertCacheElement(&cCache, psIter, 24, 'F');

	psIter = cCache.Iterate(psIter);
	AssertCacheElement(&cCache, psIter, 28, 'G');

	psIter = cCache.Iterate(psIter);
	AssertCacheElement(&cCache, psIter, 18, 'H');

	psIter = cCache.Iterate(psIter);
	AssertCacheElement(&cCache, psIter, 32, 'I');

	psIter = cCache.Iterate(psIter);
	AssertNull(psIter);
	Pass();

	cCache.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMemoryCache(void)
{
	BeginTests();
	FastFunctionsInit();
	DataMemoryInit();

	TestMemoryCacheSimple();
	TestMemoryCacheBrokenExample();
	TestMemoryCacheEvictAll();
	TestMemoryCacheEvictLeftmost();
	TestMemoryCacheEvictRightmost();
	TestMemoryCacheDeallocate();
	TestMemoryCachePreallocate();
	TestMemoryCacheReallocate();

	DataMemoryKill();
	FastFunctionsKill();
	TestStatistics();
}

