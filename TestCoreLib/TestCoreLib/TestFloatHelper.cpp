#include "BaseLib/FloatHelper.h"
#include "TestLib/Assert.h"
#include "TestLib/IntelTimer.h"
#include "TestFloatHelper.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTruncateFloat(void)
{
	AssertFloat(1.0f, TruncateFloat(1.25f, 0), 7);
	AssertFloat(13.0f, TruncateFloat(13.5493f, 0), 7);
	AssertFloat(8.0f, TruncateFloat(13.5493f, 3), 7);  //mask 2^3 = 8 = %1000  value 13 = %1011
	AssertFloat(13.53125f, TruncateFloat(13.5493f, -5), 7);
	AssertFloat(0.0f, TruncateFloat(1.0f, 1), 7);
	AssertFloat(-1.0f, TruncateFloat(-1.25f, 0), 7);
	AssertFloat(-13.0f, TruncateFloat(-13.5493f, 0), 7);
	AssertFloat(-8.0f, TruncateFloat(-13.5493f, 3), 7);
	AssertFloat(-13.53125f, TruncateFloat(-13.5493f, -5), 7);
	AssertFloat(0.8125f, TruncateFloat(0.824f, -5), 7);
	AssertFloat(0.8125f, TruncateFloat(0.817f, -5), 7);
	AssertFloat(280.39874f, TruncateFloat(280.39874f, -16), 7);
	AssertFloat(80.39874f, TruncateFloat(80.39874f, -16), 7);
	AssertFloat(1000000.0f, TruncateFloat(1000000.0, -16), 7);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestRoundFloat(void)
{
	AssertFloat(1.0f, RoundFloat(0.75f, 0), 7);
	AssertFloat(1.0f, RoundFloat(1.0f, 0), 7);
	AssertFloat(1.0f, RoundFloat(0.5f, 0), 7);
	AssertFloat(1.0f, RoundFloat(1.49f, 0), 7);
	AssertFloat(0.0f, RoundFloat(0.25f, 0), 7);
	AssertFloat(-1.0f, RoundFloat(-0.75f, 0), 7);
	AssertFloat(-1.0f, RoundFloat(-1.0f, 0), 7);
	AssertFloat(-1.0f, RoundFloat(-0.5f, 0), 7);
	AssertFloat(0.0f, RoundFloat(-0.25f, 0), 7);
	AssertFloat(2.0f, RoundFloat(2.9f, 1), 7);
	AssertFloat(2.0f, RoundFloat(1.0f, 1), 7);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFloatHelper(void)
{
	BeginTests();

	TestTruncateFloat();
	TestRoundFloat();

	TestStatistics();
}

