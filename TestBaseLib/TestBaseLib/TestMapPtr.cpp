#include "BaseLib/GlobalMemory.h"
#include "BaseLib/MapIntInt.h"
#include "BaseLib/MapPtrPtr.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapPtrPtr(void)
{
	CMapPtrPtr		cMap;
	void*			pvValue;
	void**			ppvKey;
	void**			ppvValue;
	void*			pvk1;
	void*			pvv1;
	void*			pvk2;
	void*			pvv2;
	void*			pvk3;
	void*			pvv3;
	SMapIterator	sIter;
	BOOL			bResult;

	pvk1 = (void*)0x00324789;
	pvv1 = (void*)0x00723764;
	pvk2 = (void*)0x008a4562;
	pvv2 = (void*)0x002ff462;
	pvk3 = (void*)0x008a627d;
	pvv3 = (void*)0x00198201;


	cMap.Init(&gcSystemAllocator);

	cMap.Put(pvk1, pvv1);
	cMap.Put(pvk2, pvv2);

	pvValue = cMap.Get(pvk1);
	AssertPointer(pvv1, pvValue);

	cMap.Put(pvk3, pvv3);
	AssertInt(3, cMap.NumElements());

	pvValue = cMap.Get(pvk1);
	AssertPointer(pvv1, pvValue);
	pvValue = cMap.Get(pvk3);
	AssertPointer(pvv3, pvValue);
	pvValue = cMap.Get(pvk2);
	AssertPointer(pvv2, pvValue);

	bResult = cMap.StartIteration(&sIter, (void**)&ppvKey, (void**)&ppvValue);
	AssertTrue(bResult);
	AssertPointer(pvk1, *ppvKey);
	AssertPointer(pvv1, *ppvValue);

	bResult = cMap.Iterate(&sIter, (void**)&ppvKey, (void**)&ppvValue);
	AssertTrue(bResult);
	AssertPointer(pvk2, *ppvKey);
	AssertPointer(pvv2, *ppvValue);

	bResult = cMap.Iterate(&sIter, (void**)&ppvKey, (void**)&ppvValue);
	AssertTrue(bResult);
	AssertPointer(pvk3, *ppvKey);
	AssertPointer(pvv3, *ppvValue);

	bResult = cMap.Iterate(&sIter, (void**)&ppvKey, (void**)&ppvValue);
	AssertFalse(bResult);

	cMap.Kill();
}




//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapPtr(void)
{
	BeginTests();
	MemoryInit();
	FastFunctionsInit();

	TestMapPtrPtr();

	FastFunctionsKill();
	MemoryKill();
	TestStatistics();
}

