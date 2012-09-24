#include "BaseLib/FastFunctions.h"
#include "CoreLib/Indexes.h"
#include "TestLib/Assert.h"
#include "TestIndexes.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexes(void)
{
	FastFunctionsInit();
	BeginTests();

	CIndexes		cIndexes;
	char			szOne[] = "One";
	char			szTwo[] = "Two";
	char			szThree[] = "Three";
	char			szFour[] = "Four";
	char*			szTemp;
	BOOL			bResult;

	cIndexes.Init(512);

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

	bResult = cIndexes.Add(17LL, szFour);
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

	TestStatistics();
	FastFunctionsKill();
}
