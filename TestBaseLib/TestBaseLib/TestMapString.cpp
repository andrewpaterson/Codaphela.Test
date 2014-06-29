#include "BaseLib/MapIntInt.h"
#include "TestLib/Assert.h"


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

	TestMapStringInt();

	TestStatistics();
}

