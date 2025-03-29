#include "BaseLib/FastFunctions.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/Calculator.h"
#include "BaseLib/CalculatorParser.h"
#include "TestLib/Assert.h"
#include "ParserCustomIdentifier.h"


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
	cParser.Init(&cCalculator);
	pcExpression = (CCalcExpression*)cParser.Parse("7.5 / 2.3");
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
	cParser.Init(&cCalculator);
	pcExpression = (CCalcExpression*)cParser.Parse("-1 - 44 + 45");
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
	cParser.Init(&cCalculator);
	pcExpression = (CCalcExpression*)cParser.Parse("-1");
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
	cParser.Init(&cCalculator);
	pcExpression = (CCalcExpression*)cParser.Parse("(3 == 3)");
	cParser.Kill();

	AssertFalse(cCalculator.HasError());
	cResult = cCalculator.Eval(pcExpression);
	AssertNumber("1", &cResult);
	cCalculator.Kill();
	SafeKill(pcExpression);

	cCalculator.Init();
	cParser.Init(&cCalculator);
	pcExpression = (CCalcExpression*)cParser.Parse("(2 == 3)");
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
	cParser.Init(&cCalculator);
	pcExpression = (CCalcExpression*)cParser.Parse("1 == -1");
	cParser.Kill();

	AssertFalse(cCalculator.HasError());
	cResult = cCalculator.Eval(pcExpression);
	AssertNumber("0", &cResult);
	cCalculator.Kill();
	SafeKill(pcExpression);

	cCalculator.Init();
	cParser.Init(&cCalculator);
	pcExpression = (CCalcExpression*)cParser.Parse("(1 == -1)");
	cParser.Kill();

	AssertFalse(cCalculator.HasError());
	cResult = cCalculator.Eval(pcExpression);
	AssertNumber("0", &cResult);
	cCalculator.Kill();
	SafeKill(pcExpression);


	cCalculator.Init();
	cParser.Init(&cCalculator);
	pcExpression = (CCalcExpression*)cParser.Parse("43 == -1 - 44 + 45 + 43");
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
void TestCalculatorIdentifiers(void)
{
	CCalculator			cCalculator;
	CCalculatorParser	cParser;
	CNumber				cResult;
	CCalcExpression*	pcExpression;
	CChars				sz;

	cCalculator.Init(false);
	cParser.Init(&cCalculator);
	pcExpression = (CCalcExpression*)cParser.Parse("2.57 * x");
	cParser.Kill();

	sz.Init();
	pcExpression->Print(&sz);
	AssertString("(2.57 * x)", sz.Text());
	sz.Kill();

	AssertFalse(cCalculator.HasError());
	cResult = cCalculator.Eval(pcExpression);
	AssertTrue(cCalculator.HasError());
	AssertString("Variable [x] is not assigned.", cCalculator.GetError());
	SafeKill(pcExpression);
	cCalculator.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCalculatorAssignment(void)
{
	CCalculator					cCalculator;
	CCalculatorParser			cParser;
	CNumber						cResult;
	CCalcVariableDefinition*	pcVariableDefinition;
	CChars						sz;

	cCalculator.Init();
	cParser.Init(&cCalculator);
	pcVariableDefinition = (CCalcVariableDefinition*)cParser.Parse("x = 3 * 2");
	cCalculator.Add(pcVariableDefinition);
	cParser.Kill();

	sz.Init();
	pcVariableDefinition->Print(&sz);
	AssertString("x = (3 * 2)", sz.Text());
	sz.Kill();

	AssertFalse(cCalculator.HasError());
	cResult = cCalculator.Eval(pcVariableDefinition->GetExpression());
	AssertFalse(cCalculator.HasError());
	AssertNumber("6", &cResult);
	cCalculator.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCalculatorVariableEvaluation(void)
{
	CCalculator					cCalculator;
	CCalculatorParser			cParser;
	CNumber						cResult;
	CCalcVariableDefinition*	pcVariableDefinition;
	CCalcExpression*			pcExpression;

	cCalculator.Init();
	cParser.Init(&cCalculator);
	pcVariableDefinition = (CCalcVariableDefinition*)cParser.Parse("x = 3 * 2");
	cCalculator.Add(pcVariableDefinition);
	pcExpression = (CCalcExpression*)cParser.Parse("4 + x");
	cCalculator.Add(pcExpression);
	cParser.Kill();

	AssertFalse(cCalculator.HasError());
	cResult = cCalculator.Eval(pcExpression);
	AssertFalse(cCalculator.HasError());
	AssertNumber("10", &cResult);
	cCalculator.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCalculatorUnaryOperator1(void)
{
	CCalculator			cCalculator;
	CCalculatorParser	cParser;
	CNumber				cResult;
	CCalcExpression*	pcExpression;
	CChars				sz;

	cCalculator.Init();
	cParser.Init(&cCalculator);
	pcExpression = (CCalcExpression*)cParser.Parse("-7.5 * 2.3");
	cParser.Kill();

	sz.Init();
	pcExpression->Print(&sz);
	AssertString("((-7.5) * 2.3)", sz.Text());
	sz.Kill();

	AssertFalse(cCalculator.HasError());
	cResult = cCalculator.Eval(pcExpression);
	AssertNumber("-17.25", &cResult);
	SafeKill(pcExpression);
	cCalculator.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCalculatorUnaryOperator2(void)
{
	CCalculator			cCalculator;
	CCalculatorParser	cParser;
	CNumber				cResult;
	CCalcExpression*	pcExpression;
	CChars				sz;

	cCalculator.Init();
	cParser.Init(&cCalculator);
	pcExpression = (CCalcExpression*)cParser.Parse("2 * -3");
	cParser.Kill();

	sz.Init();
	pcExpression->Print(&sz);
	AssertString("(2 * (-3))", sz.Text());
	sz.Kill();

	AssertFalse(cCalculator.HasError());
	cResult = cCalculator.Eval(pcExpression);
	AssertNumber("-6", &cResult);
	SafeKill(pcExpression);
	cCalculator.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCalculatorExternalParser(void)
{
	CCalculator			cCalculator;
	CCalculatorParser	cParser;
	CNumber				cResult;
	CCalcObject*		pcObject;
	CChars				sz;
	CTextParser			cTextParser;
	TRISTATE			tResult;

	cCalculator.Init(false);

	cTextParser.Init("x = y + 4;\ny = 6 / 5;\n x * y;");
	cParser.Init(&cCalculator);
	for (;;)
	{
		cCalculator.ClearError();

		pcObject = cParser.Parse(&cTextParser, false);
		if (pcObject != NULL)
		{
			cCalculator.Add(pcObject);
		}
		else
		{
			if (cCalculator.HasError())
			{
				Fail();
			}
			else
			{
				break;
			}
		}

		tResult = cTextParser.GetExactCharacter(';');
		if (tResult != TRITRUE)
		{
			Fail();
		}
	}
	cParser.Kill();
	cTextParser.Kill();

	sz.Init();
	cCalculator.Print(&sz);
	AssertString("\
x = (y + 4)\n\
y = (6 / 5)\n\
(x * y)\n", sz.Text());
	sz.Kill();

	AssertFalse(cCalculator.HasError());
	cResult = cCalculator.Eval();
	AssertNumber("6.24", &cResult);

	cCalculator.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCalculatorMinimalParser()
{
	CCalculator			cCalculator;
	CCalculatorParser	cParser;
	CNumber				cResult;
	CCalcObject*		pcObject;
	CChars				sz;
	CTextParser			cTextParser;
	TRISTATE			tResult;
	CCalculatorSymbols* pcSymbols;

	cCalculator.Init(true, false, false);
	pcSymbols = cCalculator.GetSymbols();
	pcSymbols->SetOperator("+", CO_Add, 3);
	pcSymbols->SetOperator("-", CO_Subtract, 3);
	pcSymbols->SetOperator("x", CO_Multiply, 2);
	pcSymbols->SetOperator("/", CO_Divide, 2);
	pcSymbols->SetAssignment("=", 12);

	cTextParser.Init("$1=$2+4*$2=6/5*$1x$2*");
	cTextParser.SetIdentifierParser(ParseCustomIdentifier);
	cParser.Init(&cCalculator);
	for (;;)
	{
		cCalculator.ClearError();

		pcObject = cParser.Parse(&cTextParser, false);
		if (pcObject != NULL)
		{
			cCalculator.Add(pcObject);
		}
		else
		{
			if (cCalculator.HasError())
			{
				Fail();
			}
			else
			{
				break;
			}
		}

		tResult = cTextParser.GetExactCharacter('*');
		if (tResult != TRITRUE)
		{
			Fail();
		}
	}
	cParser.Kill();
	cTextParser.Kill();

	sz.Init();
	cCalculator.Print(&sz);
	AssertString("\
$1=($2+4)\n\
$2=(6/5)\n\
($1x$2)\n", sz.Text());
	sz.Kill();

	AssertFalse(cCalculator.HasError());
	cResult = cCalculator.Eval();
	AssertNumber("6.24", &cResult);

	cCalculator.Kill();
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
	TestCalculatorIdentifiers();
	TestCalculatorAssignment();
	TestCalculatorVariableEvaluation();
	TestCalculatorExternalParser();
	TestCalculatorMinimalParser();
	TestCalculatorUnaryOperator1();
	TestCalculatorUnaryOperator2();
	//You should test things like ++ and <=

	TestStatistics();
	NumberKill();
	TypeConverterKill();
}

