#include "BaseLib/FastFunctions.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/Calculator.h"
#include "BaseLib/CalculatorParser.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCalculatorBinaryOperator(void)
{
	CCalculator			cCalculator;
	CCalculatorParser	cParser;
	CNumber				cResult;
	CCalcExpression*	pcExpression;
	CChars				sz;

	cCalculator.Init();
	cParser.Init(&cCalculator, "7.5 / 2.3");
	pcExpression = cParser.Parse();
	cParser.Kill();

	sz.Init();
	pcExpression->Print(&sz);
	AssertString("(7.5 / 2.3)", sz.Text());
	sz.Kill();

	AssertFalse(cCalculator.HasError());
	cResult = cCalculator.Eval(pcExpression);
	AssertNumber("3.2608695652173913", &cResult);
	SafeKill(pcExpression);
	cCalculator.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCalculatorAddition(void)
{	
	CCalculator			cCalculator;
	CCalculatorParser	cParser;
	CNumber				cResult;
	CCalcExpression*	pcExpression;

	cCalculator.Init();
	cParser.Init(&cCalculator, "-1 - 44 + 45");
	pcExpression = cParser.Parse();
	cParser.Kill();

	AssertFalse(cCalculator.HasError());
	cResult = cCalculator.Eval(pcExpression);
	AssertNumber("0", &cResult);
	SafeKill(pcExpression);
	cCalculator.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCalculatorSingleNegative(void)
{
	CCalculator			cCalculator;
	CCalculatorParser	cParser;
	CNumber				cResult;
	CCalcExpression*	pcExpression;

	cCalculator.Init();
	cParser.Init(&cCalculator, "-1");
	pcExpression = cParser.Parse();
	cParser.Kill();

	AssertFalse(cCalculator.HasError());
	cResult = cCalculator.Eval(pcExpression);
	AssertNumber("-1", &cResult);
	cCalculator.Kill();
	SafeKill(pcExpression);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCalculatorPositiveEquality(void)
{
	CCalculator			cCalculator;
	CCalculatorParser	cParser;
	CNumber				cResult;
	CCalcExpression*	pcExpression;

	cCalculator.Init();
	cParser.Init(&cCalculator, "(3 == 3)");
	pcExpression = cParser.Parse();
	cParser.Kill();

	AssertFalse(cCalculator.HasError());
	cResult = cCalculator.Eval(pcExpression);
	AssertNumber("1", &cResult);
	cCalculator.Kill();
	SafeKill(pcExpression);

	cCalculator.Init();
	cParser.Init(&cCalculator, "(2 == 3)");
	pcExpression = cParser.Parse();
	cParser.Kill();

	AssertFalse(cCalculator.HasError());
	cResult = cCalculator.Eval(pcExpression);
	AssertNumber("0", &cResult);
	cCalculator.Kill();
	SafeKill(pcExpression);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCalculatorNegativeEquality(void)
{
	CCalculator			cCalculator;
	CCalculatorParser	cParser;
	CNumber				cResult;
	CCalcExpression*	pcExpression;

	cCalculator.Init();
	cParser.Init(&cCalculator, "1 == -1");
	pcExpression = cParser.Parse();
	cParser.Kill();

	AssertFalse(cCalculator.HasError());
	cResult = cCalculator.Eval(pcExpression);
	AssertNumber("0", &cResult);
	cCalculator.Kill();
	SafeKill(pcExpression);

	cCalculator.Init();
	cParser.Init(&cCalculator, "(1 == -1)");
	pcExpression = cParser.Parse();
	cParser.Kill();

	AssertFalse(cCalculator.HasError());
	cResult = cCalculator.Eval(pcExpression);
	AssertNumber("0", &cResult);
	cCalculator.Kill();
	SafeKill(pcExpression);


	cCalculator.Init();
	cParser.Init(&cCalculator, "43 == -1 - 44 + 45 + 43");
	pcExpression = cParser.Parse();
	cParser.Kill();

	AssertFalse(cCalculator.HasError());
	cResult = cCalculator.Eval(pcExpression);
	AssertNumber("1", &cResult);
	cCalculator.Kill();
	SafeKill(pcExpression);
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

	TestCalculatorBinaryOperator();
	TestCalculatorAddition();
	TestCalculatorSingleNegative();
	TestCalculatorPositiveEquality();
	TestCalculatorNegativeEquality();

	TestStatistics();
	NumberKill();
	TypeConverterKill();
}

