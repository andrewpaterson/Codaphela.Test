#include "BaseLib/MemoryCache.h"
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
void AssertCacheElement(CMemoryCache* pcCache, SMemoryCacheDescriptor* psCacheDesc, int iDataSize, char cExpected)
{
	char*						szData;
	CChars						szExpected;

	AssertInt(iDataSize, psCacheDesc->uiSize);

	szData = (char*)pcCache->GetData(psCacheDesc);
	szExpected.Init();
	szExpected.Append(cExpected, iDataSize-1);
	AssertString(szExpected.Text(), szData);
	szExpected.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertLinkOrder(CMemoryCache* pcCache)
{
	SMemoryCacheDescriptor*	psCacheDesc;
	SMemoryCacheDescriptor*	psCacheDescReverse;
	CArrayVoidPtr			cPointers;
	int						i;

	AssertPointer(pcCache->TestGetFirst()->psPrev, pcCache->TestGetLast());
	AssertPointer(pcCache->TestGetLast()->psNext, pcCache->TestGetFirst());

	cPointers.Init();
	psCacheDesc = pcCache->TestGetFirst();

	for (;;)
	{
		cPointers.Add(psCacheDesc);
		psCacheDesc = psCacheDesc->psNext;
		if (psCacheDesc == pcCache->TestGetFirst())
		{
			break;
		}
	}

	psCacheDesc = pcCache->TestGetLast();
	for (i = cPointers.NumElements() - 1; i >= 0; i--)
	{
		psCacheDescReverse = (SMemoryCacheDescriptor*)cPointers.GetPtr(i);
		
		AssertPointer(psCacheDesc, psCacheDescReverse);

		psCacheDesc = psCacheDesc->psPrev;
	}

	cPointers.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertCache(CMemoryCache* pcCache, int iFirstLength, char cFirstChar)
{
	SMemoryCacheDescriptor*		psFirst;
	SMemoryCacheDescriptor*		psLast;

	AssertInt(1, pcCache->NumCached());
	
	psFirst = pcCache->GetFirst();
	AssertNotNull(psFirst);
	AssertPointer(psFirst, psFirst->psNext);

	psLast = pcCache->GetLast();
	AssertPointer(psFirst, psLast);

	AssertPointer(psLast, psLast->psNext);
	
	AssertCacheElement(pcCache, psFirst, iFirstLength, cFirstChar);

	AssertLinkOrder(pcCache);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertCache(CMemoryCache* pcCache, int iFirstLength, char cFirstChar, int iSecondLength, char cSecondChar)
{
	SMemoryCacheDescriptor*		psFirst;
	SMemoryCacheDescriptor*		psLast;

	AssertInt(2, pcCache->NumCached());

	psFirst = pcCache->GetFirst();
	psLast = pcCache->GetLast();
	AssertNotNull(psFirst);
	AssertFalse(psFirst == psLast);

	AssertPointer(psLast, psFirst->psNext);
	AssertPointer(psFirst, psLast->psNext);

	AssertCacheElement(pcCache, psFirst, iFirstLength, cFirstChar);
	AssertCacheElement(pcCache, psLast, iSecondLength, cSecondChar);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertCache(CMemoryCache* pcCache, int iLen1, char c1, int iLen2, char c2, int iLen3, char c3)
{
	SMemoryCacheDescriptor*		psFirst;
	SMemoryCacheDescriptor*		psLast;

	AssertInt(3, pcCache->NumCached());

	psFirst = pcCache->GetFirst();
	psLast = pcCache->GetLast();
	AssertNotNull(psFirst);
	AssertFalse(psFirst == psLast);
	AssertFalse(psFirst->psNext == psLast);

	AssertPointer(psFirst->psNext->psNext, psLast);
	AssertPointer(psLast->psNext, psFirst);

	AssertCacheElement(pcCache, psFirst, iLen1, c1);
	AssertCacheElement(pcCache, psFirst->psNext, iLen2, c2);
	AssertCacheElement(pcCache, psFirst->psNext->psNext, iLen3, c3);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMemoryCacheSimple(void)
{
	CMemoryCache	cCache;
	void*			pvData;

	cCache.Init(64+12);

	pvData = cCache.QuickAllocate(52);
	AssertNotNull(pvData);
	FillCachedElement(pvData, 52, 'A');
	AssertCache(&cCache, 52, 'A');

	pvData = cCache.QuickAllocate(20);
	AssertNotNull(pvData);
	FillCachedElement(pvData, 20, 'B');
	AssertCache(&cCache, 20, 'B');

	pvData = cCache.QuickAllocate(20);
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

	cCache.Init(64+12);

	pvData = cCache.QuickAllocate(20);
	FillCachedElement(pvData, 20, 'A');
	AssertCache(&cCache, 20, 'A');

	pvData = cCache.QuickAllocate(20);
	FillCachedElement(pvData, 20, 'B');
	AssertCache(&cCache, 20, 'A', 20, 'B');

	pvData = cCache.QuickAllocate(20);
	FillCachedElement(pvData, 20, 'C');
	AssertCache(&cCache, 20, 'B', 20, 'C');

	pvData = cCache.QuickAllocate(20);
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

	cCache.Init(64+12);

	pvData = cCache.QuickAllocate(17);
	AssertNotNull(pvData);
	FillCachedElement(pvData, 17, 'A');
	AssertCache(&cCache, 17, 'A');

	pvData = cCache.QuickAllocate(6);
	AssertNotNull(pvData);
	FillCachedElement(pvData, 6, 'B');
	AssertCache(&cCache, 17, 'A', 6, 'B');

	pvData = cCache.QuickAllocate(47);
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

	cCache.Init(64+12);

	pvData = cCache.QuickAllocate(8);
	FillCachedElement(pvData, 8, 'A');
	pvData = cCache.QuickAllocate(9);
	FillCachedElement(pvData, 9, 'B');
	pvData = cCache.QuickAllocate(8);
	FillCachedElement(pvData, 8, 'C');
	AssertCache(&cCache, 8, 'A', 9, 'B', 8, 'C');

	//Um, not sure why testing this here...
	pvData = cCache.QuickAllocate(47);
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

	cCache.Init(64+12);

	pvData = cCache.QuickAllocate(8);
	FillCachedElement(pvData, 8, 'A');
	pvData = cCache.QuickAllocate(9);
	FillCachedElement(pvData, 9, 'B');
	pvData = cCache.QuickAllocate(8);
	FillCachedElement(pvData, 8, 'C');
	AssertCache(&cCache, 8, 'A', 9, 'B', 8, 'C');

	pvData = cCache.QuickAllocate(7);
	FillCachedElement(pvData, 7, 'D');
	AssertCache(&cCache, 9, 'B', 8, 'C', 7, 'D');

	pvData = cCache.QuickAllocate(6);
	FillCachedElement(pvData, 6, 'E');
	AssertCache(&cCache, 8, 'C', 7, 'D', 6, 'E');

	pvData = cCache.QuickAllocate(9);
	FillCachedElement(pvData, 9, 'F');

	pvData = cCache.QuickAllocate(8);
	FillCachedElement(pvData, 8, 'A');
	AssertCache(&cCache, 9, 'F', 8, 'A');

	pvData = cCache.QuickAllocate(17);
	FillCachedElement(pvData, 17, 'B');
	AssertCache(&cCache, 8, 'A', 17, 'B');

	pvData = cCache.QuickAllocate(9);
	FillCachedElement(pvData, 9, 'Z');
	AssertCache(&cCache, 9, 'Z');

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

	cCache.Init(128);

	pvA = cCache.QuickAllocate(8);
	FillCachedElement(pvA, 8, 'A');
	pvB = cCache.QuickAllocate(9);
	FillCachedElement(pvB, 9, 'B');
	pvC = cCache.QuickAllocate(8);
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

	pvA = cCache.QuickAllocate(8);
	FillCachedElement(pvA, 8, 'A');
	pvB = cCache.QuickAllocate(9);
	FillCachedElement(pvB, 9, 'B');
	pvC = cCache.QuickAllocate(8);
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

	pvA = cCache.QuickAllocate(8);
	FillCachedElement(pvA, 8, 'A');
	pvB = cCache.QuickAllocate(9);
	FillCachedElement(pvB, 9, 'B');
	pvC = cCache.QuickAllocate(8);
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
void TestMemoryCache(void)
{
	BeginTests();
	FastFunctionsInit();

	//TestMemoryCacheSimple();
	//TestMemoryCacheBrokenExample();
	//TestMemoryCacheEvictAll();
	//TestMemoryCacheEvictLeftmost();
	//TestMemoryCacheEvictRightmost();
	TestMemoryCacheDeallocate();

	FastFunctionsKill();
	TestStatistics();
}


