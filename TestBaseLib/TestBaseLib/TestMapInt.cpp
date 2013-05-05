#include "BaseLib/MapIntInt.h"
#include "TestLib/Assert.h"
#include "TestMapInt.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapIntInt(void)
{
	CMapIntInt	cMap;
	int			iResult;
	int*		piKey;
	int*		piValue;

	cMap.Init(16);

	cMap.Put(5, 15);
	cMap.Put(7, 17);

	iResult = cMap.GetWithKey(5);
	AssertInt(15, iResult);

	cMap.Put(3, 13);
	AssertInt(3, cMap.NumElements());

	iResult = cMap.GetWithKey(5);
	AssertInt(15, iResult);
	iResult = cMap.GetWithKey(3);
	AssertInt(13, iResult);
	iResult = cMap.GetWithKey(7);
	AssertInt(17, iResult);

	cMap.GetAtIndex(0, &piKey, &piValue);
	AssertInt(3, *piKey);
	AssertInt(13, *piValue);

	cMap.GetAtIndex(1, &piKey, &piValue);
	AssertInt(5, *piKey);
	AssertInt(15, *piValue);

	cMap.GetAtIndex(2, &piKey, &piValue);
	AssertInt(7, *piKey);
	AssertInt(17, *piValue);

	cMap.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapInt(void)
{
	BeginTests();

	TestMapIntInt();

	TestStatistics();
}

