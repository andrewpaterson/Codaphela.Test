#include "BaseLib/MapStringString.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapStringTemplate(void)
{
	CMapStringTemplate<double>	cMap;

	cMap.Init(1, FALSE);
	cMap.Kill();

	cMap.Init(2, TRUE);
	cMap.Kill();
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

	cMap.Init(16);

	cMap.Put("EZ", 15);
	cMap.Put("Dock", 17);

	iResult = *cMap.GetWithKey("EZ");
	AssertInt(15, iResult);

	cMap.Put("KingWin", 13);
	AssertInt(3, cMap.NumElements());

	iResult = *cMap.GetWithKey("EZ");
	AssertInt(15, iResult);
	iResult = *cMap.GetWithKey("KingWin");
	AssertInt(13, iResult);
	iResult = *cMap.GetWithKey("Dock");
	AssertInt(17, iResult);
	AssertNull(cMap.GetWithKey("KWM"));

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

