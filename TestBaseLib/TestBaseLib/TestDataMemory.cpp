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
	AssertInt(36, sizeof(CDataMemory));
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
	AssertInt(12, cMemory.ByteSize());
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
	AssertInt(29777, cMemory.ByteSize());
	AssertInt(8, cMemory.NumFreeLists());
	AssertInt(13665, iAllocated);

	for (i = 0; i < apv.NumElements(); i += 2)
	{
		pv = apv.GetPtr(i);
		cMemory.Remove(pv);
	}

	AssertInt(216, cMemory.NumElements());
	AssertInt(29777, cMemory.ByteSize());
	AssertInt(8, cMemory.NumFreeLists());

	for (i = 1; i < apv.NumElements(); i += 2)
	{
		pv = apv.GetPtr(i);
		cMemory.Remove(pv);
	}

	AssertInt(0, cMemory.NumElements());
	AssertInt(12, cMemory.ByteSize());
	AssertInt(0, cMemory.NumFreeLists());

	apv.Kill();

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

	DataMemoryKill();
	WordsKill();
	TestStatistics();
}

