#include "BaseLib/ArrayChars.h"
#include "BaseLib/DataMemory.h"
#include "TestLib/Words.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDataMemorySizeof(void)
{
	AssertInt(52, sizeof(CDataMemory));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDataMemoryAdd(void)
{
	CDataMemory		cMemory;
	int				i;
	CChars*			psz;
	void*			pv;
	int				iAllocated;
	CArrayVoidPtr	apv;

	cMemory.Init(&gcDataMemoryFreeListParams);
	AssertInt(0, cMemory.NumElements());
	AssertInt(16, cMemory.ByteSize());
	AssertInt(0, cMemory.NumFreeLists());


	apv.Init();
	iAllocated = 0;
	for (i = 0; i < gacArchaicWords.NumElements(); i++)
	{
		psz = gacArchaicWords.Get(i);
		pv = cMemory.Add(psz->Length());
		strcpy((char*)pv, psz->Text());
		apv.Add(pv);

		iAllocated += psz->Length() + 1;
	}

	AssertInt(433, gacArchaicWords.NumElements());
	AssertInt(gacArchaicWords.NumElements(), cMemory.NumElements());
	AssertInt(29813, cMemory.ByteSize());
	AssertInt(8, cMemory.NumFreeLists());
	AssertInt(13665, iAllocated);

	for (i = 0; i < apv.NumElements(); i += 2)
	{
		pv = apv.GetPtr(i);
		cMemory.Remove(pv);
	}

	AssertInt(216, cMemory.NumElements());
	AssertInt(29813, cMemory.ByteSize());
	AssertInt(8, cMemory.NumFreeLists());

	for (i = 1; i < apv.NumElements(); i += 2)
	{
		pv = apv.GetPtr(i);
		cMemory.Remove(pv);
	}

	AssertInt(0, cMemory.NumElements());
	AssertInt(16, cMemory.ByteSize());
	AssertInt(0, cMemory.NumFreeLists());

	apv.Kill();

	cMemory.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDataMemoryIteration(void)
{
	CDataMemory			cMemory;
	void*				pv8192;
	void*				pv48;
	void*				pv64;
	void*				pv9036;
	SMemoryIterator		sIterator;
	SMemory				sResult;

	cMemory.Init(&gcDataMemoryFreeListParams);

	sResult = cMemory.StartIteration(&sIterator);
	AssertFalse(sResult.bValid);


	pv8192 = cMemory.Add(8192);
	sResult = cMemory.StartIteration(&sIterator);
	AssertTrue(sResult.bValid);
	AssertInt(8192, sResult.uiSize);
	AssertPointer(pv8192, sResult.pvMem);

	sResult = cMemory.Iterate(&sIterator);
	AssertFalse(sResult.bValid);


	pv48 = cMemory.Add(48);
	sResult = cMemory.StartIteration(&sIterator);
	AssertTrue(sResult.bValid);
	AssertInt(48, sResult.uiSize);
	AssertPointer(pv48, sResult.pvMem);

	sResult = cMemory.Iterate(&sIterator);
	AssertTrue(sResult.bValid);
	AssertInt(8192, sResult.uiSize);
	AssertPointer(pv8192, sResult.pvMem);

	sResult = cMemory.Iterate(&sIterator);
	AssertFalse(sResult.bValid);


	pv64 = cMemory.Add(64);
	sResult = cMemory.StartIteration(&sIterator);
	AssertTrue(sResult.bValid);
	AssertInt(48, sResult.uiSize);
	AssertPointer(pv48, sResult.pvMem);

	sResult = cMemory.Iterate(&sIterator);
	AssertTrue(sResult.bValid);
	AssertInt(64, sResult.uiSize);
	AssertPointer(pv64, sResult.pvMem);

	sResult = cMemory.Iterate(&sIterator);
	AssertTrue(sResult.bValid);
	AssertInt(8192, sResult.uiSize);
	AssertPointer(pv8192, sResult.pvMem);

	sResult = cMemory.Iterate(&sIterator);
	AssertFalse(sResult.bValid);


	cMemory.Remove(pv8192);
	sResult = cMemory.StartIteration(&sIterator);
	AssertTrue(sResult.bValid);
	AssertInt(48, sResult.uiSize);
	AssertPointer(pv48, sResult.pvMem);

	sResult = cMemory.Iterate(&sIterator);
	AssertTrue(sResult.bValid);
	AssertInt(64, sResult.uiSize);
	AssertPointer(pv64, sResult.pvMem);

	sResult = cMemory.Iterate(&sIterator);
	AssertFalse(sResult.bValid);


	pv8192 = cMemory.Add(8192);
	pv9036 = cMemory.Add(9036);
	sResult = cMemory.StartIteration(&sIterator);
	AssertTrue(sResult.bValid);
	AssertInt(48, sResult.uiSize);
	AssertPointer(pv48, sResult.pvMem);

	sResult = cMemory.Iterate(&sIterator);
	AssertTrue(sResult.bValid);
	AssertInt(64, sResult.uiSize);
	AssertPointer(pv64, sResult.pvMem);

	sResult = cMemory.Iterate(&sIterator);
	AssertTrue(sResult.bValid);
	AssertInt(8192, sResult.uiSize);
	AssertPointer(pv8192, sResult.pvMem);

	sResult = cMemory.Iterate(&sIterator);
	AssertTrue(sResult.bValid);
	AssertInt(9036, sResult.uiSize);
	AssertPointer(pv9036, sResult.pvMem);

	sResult = cMemory.Iterate(&sIterator);
	AssertFalse(sResult.bValid);

	cMemory.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDataMemory(void)
{
	BeginTests();
	WordsInit();
	DataMemoryInit();

	TestDataMemorySizeof();
	TestDataMemoryAdd();
	TestDataMemoryIteration();

	DataMemoryKill();
	WordsKill();
	TestStatistics();
}

