#include "BaseLib/MemoryCache.h"
#include "TestLib/Assert.h"
#include "TestMemoryCache.h"

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
void AssertCache(CMemoryCache* pcCache, int iFirstLength, char cFirstChar)
{
	SMemoryCacheDescriptor*		psCacheDesc;
	SMemoryCacheDescriptor*		psFirst;
	SMemoryCacheDescriptor*		psLast;
	CChars						szExpected;
	char*						szData;

	AssertInt(1, pcCache->NumCached());
	
	psFirst = pcCache->GetFirst();
	AssertNotNull(psFirst);
	AssertPointer(psFirst, psFirst->psNext);

	psLast = pcCache->GetLast();
	AssertPointer(psFirst, psLast);

	AssertPointer(psLast, psLast->psNext);
	
	psCacheDesc = psFirst;
	AssertInt(iFirstLength, psCacheDesc->iDataSize);
	AssertInt(1, psCacheDesc->iFlags);

	szData = (char*)pcCache->GetData(psCacheDesc);
	szExpected.Init();
	szExpected.Append(cFirstChar, iFirstLength-1);
	AssertString(szExpected.Text(), szData);
	szExpected.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertCache(CMemoryCache* pcCache, int iFirstLength, char cFirstChar, int iSecondLength, char cSecondChar)
{
	SMemoryCacheDescriptor*		psCacheDesc;
	SMemoryCacheDescriptor*		psFirst;
	SMemoryCacheDescriptor*		psLast;
	CChars						szExpected;
	char*						szData;

	AssertInt(2, pcCache->NumCached());

	psFirst = pcCache->GetFirst();
	psLast = pcCache->GetLast();
	AssertNotNull(psFirst);
	AssertFalse(psFirst == psLast);

	AssertPointer(psLast, psFirst->psNext);
	AssertPointer(psFirst, psLast->psNext);

	psCacheDesc = psFirst;
	AssertInt(iFirstLength, psCacheDesc->iDataSize);
	AssertInt(1, psCacheDesc->iFlags);

	szData = (char*)pcCache->GetData(psCacheDesc);
	szExpected.Init();
	szExpected.Append(cFirstChar, iFirstLength-1);
	AssertString(szExpected.Text(), szData);
	szExpected.Kill();

	psCacheDesc = psLast;
	AssertInt(iSecondLength, psCacheDesc->iDataSize);
	AssertInt(1, psCacheDesc->iFlags);

	szData = (char*)pcCache->GetData(psCacheDesc);
	szExpected.Init();
	szExpected.Append(cSecondChar, iSecondLength-1);
	AssertString(szExpected.Text(), szData);
	szExpected.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMemoryCacheSimple(void)
{
	CMemoryCache	cCache;
	void*			pvData;

	cCache.Init(64);

	pvData = cCache.QuickAllocate(52); //64
	AssertNotNull(pvData);
	FillCachedElement(pvData, 52, 'A');
	AssertCache(&cCache, 52, 'A');
	cCache.Dump();

	pvData = cCache.QuickAllocate(20);  //32
	AssertNotNull(pvData);
	FillCachedElement(pvData, 20, 'B');
	AssertCache(&cCache, 20, 'B');
	cCache.Dump();

	pvData = cCache.QuickAllocate(20);  //32
	AssertNotNull(pvData);
	FillCachedElement(pvData, 20, 'C');
	AssertCache(&cCache, 20, 'B', 20, 'C');
	cCache.Dump();

	cCache.Kill();

	//cCache.Init(64);

	//pvData = cCache.QuickAllocate(20);
	//cCache.Dump();
	//pvData = cCache.QuickAllocate(20);
	//cCache.Dump();
	//pvData = cCache.QuickAllocate(20);
	//cCache.Dump();
	//pvData = cCache.QuickAllocate(20);
	//cCache.Dump();

	//cCache.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMemoryCache(void)
{
	BeginTests();
	FastFunctionsInit();

	TestMemoryCacheSimple();

	FastFunctionsKill();
	TestStatistics();
}


