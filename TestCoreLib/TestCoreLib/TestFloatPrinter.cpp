#include "BaseLib/FloatPrinter.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFloatPrinterFullRangeNineDigits(void)
{
	char	sz[1024];

	FloatToString(sz, 1024, 734.645348e10f, -1, TRUE);
	AssertString("7.34645348e+12f", sz);

	FloatToString(sz, 1024, 1e12f, -1, TRUE);
	AssertString("9.99999996e+11f", sz);

	FloatToString(sz, 1024, 1.01e12f, -1, TRUE);
	AssertString("1.01e+12f", sz);

	FloatToString(sz, 1024, 1.25e+12f, -1, TRUE);
	AssertString("1.24999998e+12f", sz);

	FloatToString(sz, 1024, 5873464534810.f, -1, TRUE);
	AssertString("5.87346477e+12f", sz);

	FloatToString(sz, 1024, 587346453481.f, -1, TRUE);
	AssertString("5.87346477e+11f", sz);

	FloatToString(sz, 1024, 58734645348.f, -1, TRUE);
	AssertString("5.87346452e+10f", sz);

	FloatToString(sz, 1024, 5873464534.f, -1, TRUE);
	AssertString("5.87346432e+9f", sz);

	FloatToString(sz, 1024, 587346453.f, -1, TRUE);
	AssertString("587346432.f", sz);

	FloatToString(sz, 1024, 8346453.7f, -1, TRUE);
	AssertString("8346453.5f", sz);

	FloatToString(sz, 1024, 2346453.7f, -1, TRUE);
	AssertString("2346453.75f", sz);

	FloatToString(sz, 1024, 234645.37f, -1, TRUE);
	AssertString("234645.375f", sz);

	FloatToString(sz, 1024, 234645.37f, -1, TRUE);
	AssertString("234645.375f", sz);

	FloatToString(sz, 1024, 23464.536f, -1, TRUE);
	AssertString("23464.5352f", sz);

	FloatToString(sz, 1024, 2346.45361f, -1, TRUE);
	AssertString("2346.45361f", sz);

	FloatToString(sz, 1024, 234.645361f, -1, TRUE);
	AssertString("234.645355f", sz);

	FloatToString(sz, 1024, 23.464536f, -1, TRUE);
	AssertString("23.4645367f", sz);

	FloatToString(sz, 1024, 2.34645343f, -1, TRUE);
	AssertString("2.34645343f", sz);

	FloatToString(sz, 1024, 0.234645343f, -1, TRUE);
	AssertString("0.234645337f", sz);

	FloatToString(sz, 1024, 0.023464534f, -1, TRUE);
	AssertString("0.0234645344f", sz);

	FloatToString(sz, 1024, 0.0023464534f, -1, TRUE);
	AssertString("0.00234645349f", sz);

	FloatToString(sz, 1024, 0.00023464534f, -1, TRUE);
	AssertString("2.3464534e-4f", sz);

	FloatToString(sz, 1024, 0.000023464534f, -1, TRUE);
	AssertString("2.3464534e-5f", sz);

	FloatToString(sz, 1024, 7.11645356e37f, -1, TRUE);
	AssertString("7.11645356e+37f", sz);

	FloatToString(sz, 1024, 1.70141183e+38f, -1, TRUE);
	AssertString("1.70141183e+38f", sz);

	FloatToString(sz, 1024, 1.17549435e-38f, -1, TRUE);
	AssertString("1.17549435e-38f", sz);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFloatPrinterRounding(void)
{
	char	sz[1024];

	FloatToString(sz, 1024, 734.645348f, 2, FALSE);
	AssertString("734.65", sz);

	FloatToString(sz, 1024, 734645376, 2, FALSE);
	AssertString("734645376.00", sz);

	FloatToString(sz, 1024, 734645376, 0, FALSE);
	AssertString("734645376", sz);

	FloatToString(sz, 1024, 734645376, 1, FALSE);
	AssertString("734645376.0", sz);

	FloatToString(sz, 1024, 73464534.8f, 2, FALSE);
	AssertString("73464536.00", sz);

	FloatToString(sz, 1024, 734.645325f, -1, FALSE);
	AssertString("734.645325", sz);

	FloatToString(sz, 1024, 3734645376, 0, FALSE);
	AssertString("3.73464525e+9", sz);

	FloatToString(sz, 1024, 3734645376, -1, FALSE);
	AssertString("3.73464525e+9", sz);

	FloatToString(sz, 1024, 3734645376, 1, FALSE);
	AssertString("3.73464525e+9", sz);

	FloatToString(sz, 1024, 0.373464537, 3, FALSE);
	AssertString("0.373", sz);

	FloatToString(sz, 1024, 0.373464537, 1, FALSE);
	AssertString("0.4", sz);

	FloatToString(sz, 1024, 0.373464537, 8, FALSE);
	AssertString("0.37346452", sz);

	FloatToString(sz, 1024, 0.373464537, 9, FALSE);
	AssertString("0.373464525", sz);

	FloatToString(sz, 1024, 0.373464537, 10, FALSE);
	AssertString("0.373464525", sz);

	FloatToString(sz, 1024, 0.373464537, 0, FALSE);
	AssertString("0", sz);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFloatPrinter(void)
{
	BeginTests();
	NumberInit();

	TestFloatPrinterFullRangeNineDigits();
	TestFloatPrinterRounding();

	NumberKill();
	TestStatistics();
}

