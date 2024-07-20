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
	bool		bResult;

	sPos1.Init(25.00, -12.50, 50.00);
	sPos2.Init(25.00, -12.50, -50.00);
	sPos3.Init(-25.00, -12.50, 50.00);
	cHalfSpace.Init(&sNormal);
	cHalfSpace.Set(&sPos1, &sPos2, &sPos3);

	AssertFloat(1.0f, sNormal.y, 3);

	sTest.Init(0.00, -12.50, 0.00);
	bResult = cHalfSpace.On(&sTest);
	AssertTrue(bResult);

	sTest.Init(0.00, -14.00, 0.00);
	bResult = cHalfSpace.Contains(&sTest);
	AssertTrue(bResult);

	sTest.Init(0.00, 12.50, 0.00);
	bResult = cHalfSpace.NotContains(&sTest);
	AssertTrue(bResult);


	sPos1.Init(25.00, -12.50, 50.00);
	sPos2.Init(-25.00, -12.50, 50.00);
	sPos3.Init(25.00, -12.50, -50.00);
	cHalfSpace.Init(&sNormal);
	cHalfSpace.Set(&sPos1, &sPos2, &sPos3);

	AssertFloat(-1.0f, sNormal.y, 3);

	sTest.Init(0.00, -12.50, 0.00);
	bResult = cHalfSpace.On(&sTest);
	AssertTrue(bResult);

	sTest.Init(0.00, -14.00, 0.00);
	bResult = cHalfSpace.Contains(&sTest);
	AssertBool(false, bResult);

	sTest.Init(0.00, 12.50, 0.00);
	bResult = cHalfSpace.NotContains(&sTest);
	AssertBool(false, bResult);

	FastFunctionsKill();
	TestStatistics();
}

