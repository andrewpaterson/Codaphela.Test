#include "BaseLib/MapStringString.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapStringTemplate(void)
{
	CMapStringTemplate<double>	cMap;
	double						d;
	double*						pd;
	char*						szKey;

	cMap.Init(1, FALSE);
	cMap.Kill();

	cMap.Init(2, TRUE);
	cMap.Kill();

	cMap.Init(8, TRUE, TRUE);
	d = 1.0; cMap.Put("A", &d);
	d = 2.0; cMap.Put("B", &d);
	d = 3.0; cMap.Put("C", &d);

	pd = cMap.Get("B");
	AssertDouble(2.0, *pd, 2);
	szKey = cMap.GetKeyForData(pd);
	AssertString("B", szKey);

	pd = cMap.Get("C");
	AssertDouble(3.0, *pd, 2);
	szKey = cMap.GetKeyForData(pd);
	AssertString("C", szKey);

	pd = cMap.Get("A");
	AssertDouble(1.0, *pd, 2);
	szKey = cMap.GetKeyForData(pd);
	AssertString("A", szKey);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapStringString(void)
{
	CMapStringString	cMap;

	cMap.Init(10, TRUE);
	cMap.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapStringInt(void)
{
	CMapStringInt	cMap;
	int				iResult;
	int*			piResult;
	SMapIterator	sIter;
	char*			szKey;

	cMap.Init(16);

	AssertTrue(cMap.Put("EZ", 15));
	AssertInt(1, cMap.NumElements());
	AssertTrue(cMap.Put("Dock", 17));
	AssertInt(2, cMap.NumElements());

	AssertTrue(cMap.StartIteration(&sIter, (void**)&szKey, (void**)&piResult));
	AssertNotNull(szKey);
	AssertNotNull(piResult);
	AssertString("Dock", szKey);
	AssertInt(17, *piResult);

	piResult = cMap.Get("EZ");
	AssertNotNull(piResult);
	iResult = *piResult;
	AssertInt(15, iResult);

	cMap.Put("KingWin", 13);
	AssertInt(3, cMap.NumElements());

	iResult = *cMap.Get("EZ");
	AssertInt(15, iResult);
	iResult = *cMap.Get("KingWin");
	AssertInt(13, iResult);
	iResult = *cMap.Get("Dock");
	AssertInt(17, iResult);
	AssertNull(cMap.Get("KWM"));

	cMap.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapString(void)
{
	BeginTests();

	TestMapStringTemplate();
	TestMapStringInt();
	TestMapStringString();

	TestStatistics();
}

