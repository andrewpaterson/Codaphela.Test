#include "BaseLib/FloatHelper.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFloatHelperTruncateFloat(void)
{
	AssertFloat(0.1234130859375, TruncateFloat(0.12345f, -13), 13);
	AssertFloat(0.1232910156250, TruncateFloat(0.12345f, -12), 13);
	AssertFloat(0.1230468750000, TruncateFloat(0.12345f, -11), 13);
	AssertFloat(0.1230468750000, TruncateFloat(0.12345f, -10), 13);
	AssertFloat(0.1230468750000, TruncateFloat(0.12345f, -9), 13);
	AssertFloat(0.1210937500000, TruncateFloat(0.12345f, -8), 13);
	AssertFloat(0.1171875000000, TruncateFloat(0.12345f, -7), 13);
	AssertFloat(0.1093750000000, TruncateFloat(0.12345f, -6), 13);
	AssertFloat(0.0937500000000, TruncateFloat(0.12345f, -5), 13);
	AssertFloat(0.0625000000000, TruncateFloat(0.12345f, -4), 13);
	AssertFloat(0.0000000000000, TruncateFloat(0.12345f, -3), 13);
	AssertFloat(0.0000000000000, TruncateFloat(0.12345f, -2), 13);
	AssertFloat(0.0000000000000, TruncateFloat(0.12345f, -1), 13);

	AssertFloat(3274.4062500000, TruncateFloat(3274.437f, -5), 13);
	AssertFloat(3274.3750000000, TruncateFloat(3274.437f, -4), 13);
	AssertFloat(3274.3750000000, TruncateFloat(3274.437f, -3), 13);
	AssertFloat(3274.2500000000, TruncateFloat(3274.437f, -2), 13);
	AssertFloat(3274.0000000000, TruncateFloat(3274.437f, -1), 13);
	AssertFloat(3274.0000000000, TruncateFloat(3274.437f, 0), 13);
	AssertFloat(3274.0000000000, TruncateFloat(3274.437f, 1), 13);
	AssertFloat(3272.0000000000, TruncateFloat(3274.437f, 2), 13);
	AssertFloat(3272.0000000000, TruncateFloat(3274.437f, 3), 13);
	AssertFloat(3264.0000000000, TruncateFloat(3274.437f, 4), 13);
	AssertFloat(3264.0000000000, TruncateFloat(3274.437f, 5), 13);
	AssertFloat(3264.0000000000, TruncateFloat(3274.437f, 6), 13);
	AssertFloat(3200.0000000000, TruncateFloat(3274.437f, 7), 13);
	AssertFloat(3072.0000000000, TruncateFloat(3274.437f, 8), 13);
	AssertFloat(3072.0000000000, TruncateFloat(3274.437f, 9), 13);
	AssertFloat(3072.0000000000, TruncateFloat(3274.437f, 10), 13);
	AssertFloat(2048.0000000000, TruncateFloat(3274.437f, 11), 13);
	AssertFloat(0000.0000000000, TruncateFloat(3274.437f, 12), 13);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFloatHelperRoundFloat(void)
{
	AssertFloat(0.1234130859375, RoundFloat(0.12345f, -13), 13);
	AssertFloat(0.1235351562500, RoundFloat(0.12345f, -12), 13);
	AssertFloat(0.1235351562500, RoundFloat(0.12345f, -11), 13);
	AssertFloat(0.1230468750000, RoundFloat(0.12345f, -10), 13);
	AssertFloat(0.1230468750000, RoundFloat(0.12345f, -9), 13);
	AssertFloat(0.1250000000000, RoundFloat(0.12345f, -8), 13);
	AssertFloat(0.1250000000000, RoundFloat(0.12345f, -7), 13);
	AssertFloat(0.1250000000000, RoundFloat(0.12345f, -6), 13);
	AssertFloat(0.1250000000000, RoundFloat(0.12345f, -5), 13);
	AssertFloat(0.1250000000000, RoundFloat(0.12345f, -4), 13);
	AssertFloat(0.1250000000000, RoundFloat(0.12345f, -3), 13);
	AssertFloat(0.0000000000000, RoundFloat(0.12345f, -2), 13);
	AssertFloat(0.0000000000000, RoundFloat(0.12345f, -1), 13);

	AssertFloat(3274.4375000000, RoundFloat(3274.437f, -5), 13);
	AssertFloat(3274.4375000000, RoundFloat(3274.437f, -4), 13);
	AssertFloat(3274.3750000000, RoundFloat(3274.437f, -3), 13);
	AssertFloat(3274.5000000000, RoundFloat(3274.437f, -2), 13);
	AssertFloat(3274.5000000000, RoundFloat(3274.437f, -1), 13);
	AssertFloat(3274.0000000000, RoundFloat(3274.437f, 0), 13);
	AssertFloat(3274.0000000000, RoundFloat(3274.437f, 1), 13);
	AssertFloat(3276.0000000000, RoundFloat(3274.437f, 2), 13);
	AssertFloat(3272.0000000000, RoundFloat(3274.437f, 3), 13);
	AssertFloat(3280.0000000000, RoundFloat(3274.437f, 4), 13);
	AssertFloat(3264.0000000000, RoundFloat(3274.437f, 5), 13);
	AssertFloat(3264.0000000000, RoundFloat(3274.437f, 6), 13);
	AssertFloat(3328.0000000000, RoundFloat(3274.437f, 7), 13);
	AssertFloat(3328.0000000000, RoundFloat(3274.437f, 8), 13);
	AssertFloat(3072.0000000000, RoundFloat(3274.437f, 9), 13);
	AssertFloat(3072.0000000000, RoundFloat(3274.437f, 10), 13);
	AssertFloat(4096.0000000000, RoundFloat(3274.437f, 11), 13);
	AssertFloat(4096.0000000000, RoundFloat(3274.437f, 12), 13);
	AssertFloat(0000.0000000000, RoundFloat(3274.437f, 13), 13);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFloatHelperTruncateDouble(void)
{
	AssertDouble(0.1234130859375, TruncateDouble(0.12345, -13), 13);
	AssertDouble(0.1232910156250, TruncateDouble(0.12345, -12), 13);
	AssertDouble(0.1230468750000, TruncateDouble(0.12345, -11), 13);
	AssertDouble(0.1230468750000, TruncateDouble(0.12345, -10), 13);
	AssertDouble(0.1230468750000, TruncateDouble(0.12345, -9), 13);
	AssertDouble(0.1210937500000, TruncateDouble(0.12345, -8), 13);
	AssertDouble(0.1171875000000, TruncateDouble(0.12345, -7), 13);
	AssertDouble(0.1093750000000, TruncateDouble(0.12345, -6), 13);
	AssertDouble(0.0937500000000, TruncateDouble(0.12345, -5), 13);
	AssertDouble(0.0625000000000, TruncateDouble(0.12345, -4), 13);
	AssertDouble(0.0000000000000, TruncateDouble(0.12345, -3), 13);
	AssertDouble(0.0000000000000, TruncateDouble(0.12345, -2), 13);
	AssertDouble(0.0000000000000, TruncateDouble(0.12345, -1), 13);

	AssertDouble(3274.4062500000, TruncateDouble(3274.437, -5), 13);
	AssertDouble(3274.3750000000, TruncateDouble(3274.437, -4), 13);
	AssertDouble(3274.3750000000, TruncateDouble(3274.437, -3), 13);
	AssertDouble(3274.2500000000, TruncateDouble(3274.437, -2), 13);
	AssertDouble(3274.0000000000, TruncateDouble(3274.437, -1), 13);
	AssertDouble(3274.0000000000, TruncateDouble(3274.437, 0), 13);
	AssertDouble(3274.0000000000, TruncateDouble(3274.437, 1), 13);
	AssertDouble(3272.0000000000, TruncateDouble(3274.437, 2), 13);
	AssertDouble(3272.0000000000, TruncateDouble(3274.437, 3), 13);
	AssertDouble(3264.0000000000, TruncateDouble(3274.437, 4), 13);
	AssertDouble(3264.0000000000, TruncateDouble(3274.437, 5), 13);
	AssertDouble(3264.0000000000, TruncateDouble(3274.437, 6), 13);
	AssertDouble(3200.0000000000, TruncateDouble(3274.437, 7), 13);
	AssertDouble(3072.0000000000, TruncateDouble(3274.437, 8), 13);
	AssertDouble(3072.0000000000, TruncateDouble(3274.437, 9), 13);
	AssertDouble(3072.0000000000, TruncateDouble(3274.437, 10), 13);
	AssertDouble(2048.0000000000, TruncateDouble(3274.437, 11), 13);
	AssertDouble(0000.0000000000, TruncateDouble(3274.437, 12), 13);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFloatHelperRoundDouble(void)
{
	AssertDouble(0.1234130859375, RoundDouble(0.12345, -13), 13);
	AssertDouble(0.1235351562500, RoundDouble(0.12345, -12), 13);
	AssertDouble(0.1235351562500, RoundDouble(0.12345, -11), 13);
	AssertDouble(0.1230468750000, RoundDouble(0.12345, -10), 13);
	AssertDouble(0.1230468750000, RoundDouble(0.12345, -9), 13);
	AssertDouble(0.1250000000000, RoundDouble(0.12345, -8), 13);
	AssertDouble(0.1250000000000, RoundDouble(0.12345, -7), 13);
	AssertDouble(0.1250000000000, RoundDouble(0.12345, -6), 13);
	AssertDouble(0.1250000000000, RoundDouble(0.12345, -5), 13);
	AssertDouble(0.1250000000000, RoundDouble(0.12345, -4), 13);
	AssertDouble(0.1250000000000, RoundDouble(0.12345, -3), 13);
	AssertDouble(0.0000000000000, RoundDouble(0.12345, -2), 13);
	AssertDouble(0.0000000000000, RoundDouble(0.12345, -1), 13);

	AssertDouble(3274.4375000000, RoundDouble(3274.437, -5), 13);
	AssertDouble(3274.4375000000, RoundDouble(3274.437, -4), 13);
	AssertDouble(3274.3750000000, RoundDouble(3274.437, -3), 13);
	AssertDouble(3274.5000000000, RoundDouble(3274.437, -2), 13);
	AssertDouble(3274.5000000000, RoundDouble(3274.437, -1), 13);
	AssertDouble(3274.0000000000, RoundDouble(3274.437, 0), 13);
	AssertDouble(3274.0000000000, RoundDouble(3274.437, 1), 13);
	AssertDouble(3276.0000000000, RoundDouble(3274.437, 2), 13);
	AssertDouble(3272.0000000000, RoundDouble(3274.437, 3), 13);
	AssertDouble(3280.0000000000, RoundDouble(3274.437, 4), 13);
	AssertDouble(3264.0000000000, RoundDouble(3274.437, 5), 13);
	AssertDouble(3264.0000000000, RoundDouble(3274.437, 6), 13);
	AssertDouble(3328.0000000000, RoundDouble(3274.437, 7), 13);
	AssertDouble(3328.0000000000, RoundDouble(3274.437, 8), 13);
	AssertDouble(3072.0000000000, RoundDouble(3274.437, 9), 13);
	AssertDouble(3072.0000000000, RoundDouble(3274.437, 10), 13);
	AssertDouble(4096.0000000000, RoundDouble(3274.437, 11), 13);
	AssertDouble(4096.0000000000, RoundDouble(3274.437, 12), 13);
	AssertDouble(0000.0000000000, RoundDouble(3274.437, 13), 13);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFloatHelper(void)
{
	TestFloatHelperTruncateFloat();
	TestFloatHelperRoundFloat();
	TestFloatHelperTruncateDouble();
	TestFloatHelperRoundDouble();
}

