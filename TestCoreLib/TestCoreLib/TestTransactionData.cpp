#include "TestTransactionData.h"
#include "CoreLib/IndexedMemory.h"
#include "BaseLib/FastFunctions.h"
#include "TestLib/Assert.h"
#include "CoreLib/TypeConverter.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTransactionIndexedMemory(void)
{
	FastFunctionsInit();
	TypeConverterInit();

	CIndexedMemory	cData;
	char			sz1[16] = "Samurai Warrior";
	char			sz2[11] = "Project 11";
	char			sz3[11] = "Last Ninja";
	char			sz4[14] = "Noisy Pillars";
	char			sz5[13] = "Comic Bakery";
	char			sz[16];
	BOOL			bResult;

	cData.Init();

	cData.Add(0LL, sz1, 16);
	cData.Add(8LL, sz2, 11);

	memset(sz, 0, 16);
	bResult = cData.Get(0LL, sz);
	AssertBool(TRUE, bResult);
	AssertString(sz1, sz);
	memset(sz, 0, 16);
	bResult = cData.Get(8LL, sz);
	AssertBool(TRUE, bResult);
	AssertString(sz2, sz);
	memset(sz, 0, 16);
	bResult = cData.Get(2LL, sz);
	AssertBool(FALSE, bResult);

	cData.Set(8LL, sz3, 11);
	memset(sz, 0, 16);
	bResult = cData.Get(8LL, sz);
	AssertBool(TRUE, bResult);
	AssertString(sz3, sz);

	bResult = cData.Add(2LL, sz4, 14);
	AssertBool(TRUE, bResult);
	memset(sz, 0, 16);
	bResult = cData.Get(8LL, sz);
	AssertBool(TRUE, bResult);
	memset(sz, 0, 16);
	bResult = cData.Get(2LL, sz);
	AssertBool(TRUE, bResult);
	AssertString(sz4, sz);
	bResult = cData.Add(2LL, sz5, 13);
	AssertBool(FALSE, bResult);
	memset(sz, 0, 16);
	bResult = cData.Get(2LL, sz);
	AssertBool(TRUE, bResult);
	memset(sz, 0, 16);
	bResult = cData.Get(8LL, sz);
	AssertBool(TRUE, bResult);
	AssertString(sz3, sz);

	AssertBool(TRUE, cData.TestOrder());

	cData.Kill();

	FastFunctionsKill();
	TypeConverterKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTransactionData(void)
{
	BeginTests();

	TestTransactionIndexedMemory();

	TestStatistics();
}


