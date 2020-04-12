#include "BaseLib/FastFunctions.h"
#include "BaseLib/Logger.h"
#include "CoreLib/Indexes.h"
#include "TestLib/Assert.h"



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexesSomething(void)
{
	CIndexes		cIndexes;
	char			szOne[] = "One";
	char			szTwo[] = "Two";
	char			szThree[] = "Three";
	char			szFour[] = "Four";
	char*			szTemp;
	BOOL			bResult;
	SLogConfig		sLogConfig;

	cIndexes.Init();

	AssertInt(0, cIndexes.TestNumLevels());

	cIndexes.Add(17LL, szOne);
	szTemp = (char*)cIndexes.Get(17LL);
	AssertString(szOne, szTemp);
	AssertInt(7, cIndexes.TestNumLevels());

	szTemp = (char*)cIndexes.Get(268472648234LL);
	AssertNull(szTemp);

	cIndexes.Add(268472648234LL, szTwo);
	szTemp = (char*)cIndexes.Get(268472648234LL);
	AssertString(szTwo, szTemp);
	AssertInt(11, cIndexes.TestNumLevels());

	szTemp = (char*)cIndexes.Get(268472648233LL);
	AssertNull(szTemp);

	cIndexes.Add(268472648233LL, szThree);
	szTemp = (char*)cIndexes.Get(268472648233LL);
	AssertString(szThree, szTemp);
	AssertInt(11, cIndexes.TestNumLevels());
	szTemp = (char*)cIndexes.Get(268472648234LL);
	AssertString(szTwo, szTemp);

	sLogConfig = gcLogger.SetSilent();;
	bResult = cIndexes.Add(17LL, szFour);
	gcLogger.SetConfig(&sLogConfig);
	AssertFalse(bResult);
	szTemp = (char*)cIndexes.Get(17LL);
	AssertString(szOne, szTemp);
	AssertInt(11, cIndexes.TestNumLevels());

	bResult = cIndexes.Remove(17LL);
	AssertBool(TRUE, bResult)
	szTemp = (char*)cIndexes.Get(17LL);
	AssertNull(szTemp);
	AssertInt(7, cIndexes.TestNumLevels());

	bResult = cIndexes.Remove(268472648233LL);
	AssertBool(TRUE, bResult);
	AssertInt(7, cIndexes.TestNumLevels());
	bResult = cIndexes.Remove(268472648234LL);
	AssertBool(TRUE, bResult);
	AssertInt(0, cIndexes.TestNumLevels());
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexesIteration(void)
{
	CIndexes			cIndexes;
	void*				pvMem;
	void*				pvTest;
	int					i;
	SIndexesIterator	sIter;

	i = 15;
	pvMem = &i;

	cIndexes.Init();
	cIndexes.Add(2, pvMem);
	pvTest = cIndexes.Get(2);
	AssertPointer(pvMem, pvTest);

	cIndexes.Add(255, pvMem);
	cIndexes.Add(256, pvMem);
	cIndexes.Add(260, pvMem);
	cIndexes.Add(0x0000708a9bcd5500LL, pvMem);
	cIndexes.Add(0x0000708a9bcd5501LL, pvMem);
	cIndexes.Add(0x0000708a9bcd55FFLL, pvMem);
	cIndexes.Add(0x0000720000000101LL, pvMem);
	cIndexes.Add(0x0000720000000102LL, pvMem);

	AssertLongLongInt(2, cIndexes.StartIteration(&sIter));
	AssertLongLongInt(255, cIndexes.Iterate(&sIter));

	AssertLongLongInt(256, cIndexes.Iterate(&sIter));
	AssertLongLongInt(260, cIndexes.Iterate(&sIter));

	AssertLongLongInt(0x0000708a9bcd5500LL, cIndexes.Iterate(&sIter));
	AssertLongLongInt(0x0000708a9bcd5501LL, cIndexes.Iterate(&sIter));
	AssertLongLongInt(0x0000708a9bcd55FFLL, cIndexes.Iterate(&sIter));
	AssertLongLongInt(0x0000720000000101LL, cIndexes.Iterate(&sIter));
	AssertLongLongInt(0x0000720000000102LL, cIndexes.Iterate(&sIter));

	AssertLongLongInt(INVALID_O_INDEX, cIndexes.Iterate(&sIter));

	cIndexes.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexesAddAndRemove(void)
{
	CIndexes			cIndexes;
	void*				pvMem;
	int					i;

	i = 391287491;
	pvMem = &i;

	cIndexes.Init();
	AssertInt(0, (int)cIndexes.NumIndexed());
	
	cIndexes.Add(1, pvMem);
	AssertInt(1, (int)cIndexes.NumIndexed());

	cIndexes.Remove(1);
	AssertInt(0, (int)cIndexes.NumIndexed());
	AssertTrue(cIndexes.TestTopIsEmpty());

	cIndexes.Add(1, pvMem);
	AssertInt(1, (int)cIndexes.NumIndexed());

	cIndexes.Remove(1);
	AssertInt(0, (int)cIndexes.NumIndexed());
	AssertTrue(cIndexes.TestTopIsEmpty());

	cIndexes.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexes(void)
{
	FastFunctionsInit();
	BeginTests();

	TestIndexesSomething();
	TestIndexesIteration();
	TestIndexesAddAndRemove();
	
	TestStatistics();
	FastFunctionsKill();
}

