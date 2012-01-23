#include "stdafx.h"
#include "TestHalfSpace.h"
#include "TestLib/Assert.h"
#include "BaseLib/FastFunctions.h"
#include "SupportLib/HalfSpace.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestHalfSpace(void)
{
	BeginTests();
	FastFunctionsInit();

	SFloat3		sPos1;
	SFloat3		sPos2;
	SFloat3		sPos3;
	CHalfSpace	cHalfSpace;
	SFloat3		sTest;
	SFloat3		sNormal;
	BOOL		bResult;

	sPos1.Init(25.00, -12.50, 50.00);
	sPos2.Init(25.00, -12.50, -50.00);
	sPos3.Init(-25.00, -12.50, 50.00);
	cHalfSpace.Init(&sNormal);
	cHalfSpace.Set(&sPos1, &sPos2, &sPos3);

	AssertFloat(1.0f, sNormal.y, 3);

	sTest.Init(0.00, -12.50, 0.00);
	bResult = cHalfSpace.On(&sTest);
	AssertBool(TRUE, bResult);

	sTest.Init(0.00, -14.00, 0.00);
	bResult = cHalfSpace.Contains(&sTest);
	AssertBool(TRUE, bResult);

	sTest.Init(0.00, 12.50, 0.00);
	bResult = cHalfSpace.NotContains(&sTest);
	AssertBool(TRUE, bResult);


	sPos1.Init(25.00, -12.50, 50.00);
	sPos2.Init(-25.00, -12.50, 50.00);
	sPos3.Init(25.00, -12.50, -50.00);
	cHalfSpace.Init(&sNormal);
	cHalfSpace.Set(&sPos1, &sPos2, &sPos3);

	AssertFloat(-1.0f, sNormal.y, 3);

	sTest.Init(0.00, -12.50, 0.00);
	bResult = cHalfSpace.On(&sTest);
	AssertBool(TRUE, bResult);

	sTest.Init(0.00, -14.00, 0.00);
	bResult = cHalfSpace.Contains(&sTest);
	AssertBool(FALSE, bResult);

	sTest.Init(0.00, 12.50, 0.00);
	bResult = cHalfSpace.NotContains(&sTest);
	AssertBool(FALSE, bResult);

	FastFunctionsKill();
	TestStatistics();
}

