#include "BaseLib/FastFunctions.h"
#include "BaseLib/TypeConverter.h"
#include "CoreLib/Calculator.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCalculatorAddition(void)
{	
	CCalculator		cCalc;
	CNumber			cResult;

	cCalc.Init();

	cResult = cCalc.Eval("-1 - 44 + 45");
	AssertNumber("0", &cResult);

	cCalc.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCalculatorSingleNegative(void)
{
	CCalculator		cCalc;
	CNumber			cResult;
	cCalc.Init();

	cResult = cCalc.Eval("-1");
	AssertNumber("-1", &cResult);

	cCalc.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCalculatorPositiveEquality(void)
{
	CCalculator		cCalc;
	CNumber			cResult;
	cCalc.Init();

	cResult = cCalc.Eval("(3 == 3)");
	AssertNumber("1", &cResult);

	cResult = cCalc.Eval("(2 == 3)");
	AssertNumber("0", &cResult);

	cCalc.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCalculatorNegativeEquality(void)
{
	CCalculator		cCalc;
	CNumber			cResult;
	cCalc.Init();

	cResult = cCalc.Eval("1 == -1");
	AssertNumber("0", &cResult);

	cResult = cCalc.Eval("(1 == -1)");
	AssertNumber("0", &cResult);

	cResult = cCalc.Eval("43 == -1 - 44 + 45 + 43");
	AssertNumber("1", &cResult);

	cCalc.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCalculator(void)
{
	TypeConverterInit();
	NumberInit();
	BeginTests();

	TestCalculatorAddition();
	TestCalculatorSingleNegative();
	TestCalculatorPositiveEquality();
	TestCalculatorNegativeEquality();

	TestStatistics();
	NumberKill();
	TypeConverterKill();
}

