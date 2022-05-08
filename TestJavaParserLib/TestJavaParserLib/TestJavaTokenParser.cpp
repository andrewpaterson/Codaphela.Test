#include "BaseLib/FastFunctions.h"
#include "BaseLib/PointerRemapper.h"
#include "BaseLib/TypeNames.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/TextFile.h"
#include "CoreLib/Operators.h"
#include "TestLib/Assert.h"
#include "JavaParserLib/JavaTokenParser.h"
#include "JavaTokenAssert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTokenParserEndOfFile(void)
{
	CJavaTokenParser		cTokenParser;
	CJavaTokenDefinitions	cTokenDefinitions;
	CJavaToken*				pcToken;

	cTokenDefinitions.Init();
	cTokenParser.Init(&cTokenDefinitions, "Test1.Java", "{\n}");
	cTokenParser.Parse();

	pcToken = cTokenParser.GetFirstToken();
	pcToken = AssertSeparator(&cTokenDefinitions, pcToken, JS_CurlyBracketLeft);
	pcToken = AssertSeparator(&cTokenDefinitions, pcToken, JS_CurlyBracketRight);
	AssertNull(pcToken);

	cTokenParser.Kill();
	cTokenDefinitions.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTokenParserStartAndEndWithComment(void)
{
	CJavaTokenParser		cTokenParser;
	CJavaTokenDefinitions	cTokenDefinitions;
	CJavaToken*				pcToken;

	cTokenDefinitions.Init();
	cTokenParser.Init(&cTokenDefinitions, "Test2.Java", "\
  // Tickable Pins Start\n\
package net.simulation.common;\n\
\n\
{\n\
  protected int x;\n\
} // Tickable Pins End\
");


	cTokenParser.Parse();

	pcToken = cTokenParser.GetFirstToken();

	pcToken = AssertComment(&cTokenDefinitions, pcToken, " Tickable Pins Start");
	pcToken = AssertKeyword(&cTokenDefinitions, pcToken, JK_package);
	pcToken = AssertIdentifier(&cTokenDefinitions, pcToken, "net");
	pcToken = AssertSeparator(&cTokenDefinitions, pcToken, JS_Dot);
	pcToken = AssertIdentifier(&cTokenDefinitions, pcToken, "simulation");
	pcToken = AssertSeparator(&cTokenDefinitions, pcToken, JS_Dot);
	pcToken = AssertIdentifier(&cTokenDefinitions, pcToken, "common");
	pcToken = AssertSeparator(&cTokenDefinitions, pcToken, JS_Semicolon);
	pcToken = AssertSeparator(&cTokenDefinitions, pcToken, JS_CurlyBracketLeft);
	pcToken = AssertKeyword(&cTokenDefinitions, pcToken, JK_protected);
	pcToken = AssertKeyword(&cTokenDefinitions, pcToken, JK_int);
	pcToken = AssertIdentifier(&cTokenDefinitions, pcToken, "x");
	pcToken = AssertSeparator(&cTokenDefinitions, pcToken, JS_Semicolon);
	pcToken = AssertSeparator(&cTokenDefinitions, pcToken, JS_CurlyBracketRight);
	pcToken = AssertComment(&cTokenDefinitions, pcToken, " Tickable Pins End");
	AssertNull(pcToken);
	
	cTokenParser.Kill();
	cTokenDefinitions.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTokenParserComplexGeneric(void)
{
	CJavaTokenDefinitions	cTokenDefinitions;
	CJavaTokenParser		cTokenParser;

	cTokenDefinitions.Init();
	cTokenParser.Init(&cTokenDefinitions, "Test3.Java", "\
  // Tickable Pins\n\
package net.simulation.common;\n\
\n\
import net.common.*;\n\
\n\
import java.util.Set; \n\
\n\
public abstract class TickablePins<\n\
	SNAPSHOT extends Snapshot,\n\
	PINS extends Pins<SNAPSHOT, PINS, ? extends IntegratedCircuit<SNAPSHOT, PINS>>,\n\
	INTEGRATED_CIRCUIT extends IntegratedCircuit<SNAPSHOT, PINS>>\n\
{\n\
  protected INTEGRATED_CIRCUIT integratedCircuit;\n\
  protected SNAPSHOT snapshot;\n\
}\
");

	cTokenParser.Parse();
	cTokenParser.Kill();
	cTokenDefinitions.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTokenParserLiterals(void)
{
	CJavaTokenDefinitions	cTokenDefinitions;
	CJavaTokenParser		cTokenParser;
	CJavaToken*				pcToken;

	cTokenDefinitions.Init();
	cTokenParser.Init(&cTokenDefinitions, "Test4.Java", "\
  public String getType()\n\
  {\n\
    long xl = 1L;\n\
    int x = 100_00;\n\
    float f = 1_000.000f;\n\
    double fl = 1.3_3e10;\n\
    char c =  '!'; \n\
	char c2 = 'A';\n\
	boolean truey = true;\n\
	boolean notTrue = !truey;\n\
	notTrue = '\\u1021' == '\\u1022';\n\
    return \"AND Gate\";\n\
  }\n");

	cTokenParser.Parse(TRUE);

	pcToken = cTokenParser.GetFirstToken();
	
	pcToken = AssertKeyword(&cTokenDefinitions, pcToken, JK_public);
	pcToken = AssertIdentifier(&cTokenDefinitions, pcToken, "String");
	pcToken = AssertIdentifier(&cTokenDefinitions, pcToken, "getType");
	pcToken = AssertSeparator(&cTokenDefinitions, pcToken, JS_RoundBracketLeft);
	pcToken = AssertSeparator(&cTokenDefinitions, pcToken, JS_RoundBracketRight);
	pcToken = AssertSeparator(&cTokenDefinitions, pcToken, JS_CurlyBracketLeft);
	pcToken = AssertKeyword(&cTokenDefinitions, pcToken, JK_long);
	pcToken = AssertIdentifier(&cTokenDefinitions, pcToken, "xl");
	pcToken = AssertOperator(&cTokenDefinitions, pcToken, JO_Assign);
	pcToken = AssertLiteral(&cTokenDefinitions, pcToken, 1LL);
	pcToken = AssertSeparator(&cTokenDefinitions, pcToken, JS_Semicolon);
	pcToken = AssertKeyword(&cTokenDefinitions, pcToken, JK_int);
	pcToken = AssertIdentifier(&cTokenDefinitions, pcToken, "x");
	pcToken = AssertOperator(&cTokenDefinitions, pcToken, JO_Assign);
	pcToken = AssertLiteral(&cTokenDefinitions, pcToken, 10000);
	pcToken = AssertSeparator(&cTokenDefinitions, pcToken, JS_Semicolon);
	pcToken = AssertKeyword(&cTokenDefinitions, pcToken, JK_float);
	pcToken = AssertIdentifier(&cTokenDefinitions, pcToken, "f");
	pcToken = AssertOperator(&cTokenDefinitions, pcToken, JO_Assign);
	pcToken = AssertLiteral(&cTokenDefinitions, pcToken, 1000.f);
	pcToken = AssertSeparator(&cTokenDefinitions, pcToken, JS_Semicolon);
	pcToken = AssertKeyword(&cTokenDefinitions, pcToken, JK_double);
	pcToken = AssertIdentifier(&cTokenDefinitions, pcToken, "fl");
	pcToken = AssertOperator(&cTokenDefinitions, pcToken, JO_Assign);
	pcToken = AssertLiteral(&cTokenDefinitions, pcToken, 1.33e+10);
	pcToken = AssertSeparator(&cTokenDefinitions, pcToken, JS_Semicolon);
	pcToken = AssertKeyword(&cTokenDefinitions, pcToken, JK_char);
	pcToken = AssertIdentifier(&cTokenDefinitions, pcToken, "c");
	pcToken = AssertOperator(&cTokenDefinitions, pcToken, JO_Assign);
	pcToken = AssertLiteral(&cTokenDefinitions, pcToken, '!');
	pcToken = AssertSeparator(&cTokenDefinitions, pcToken, JS_Semicolon);
	pcToken = AssertKeyword(&cTokenDefinitions, pcToken, JK_char);
	pcToken = AssertIdentifier(&cTokenDefinitions, pcToken, "c2");
	pcToken = AssertOperator(&cTokenDefinitions, pcToken, JO_Assign);
	pcToken = AssertLiteral(&cTokenDefinitions, pcToken, 'A');
	pcToken = AssertSeparator(&cTokenDefinitions, pcToken, JS_Semicolon);
	pcToken = AssertKeyword(&cTokenDefinitions, pcToken, JK_boolean);
	pcToken = AssertIdentifier(&cTokenDefinitions, pcToken, "truey");
	pcToken = AssertOperator(&cTokenDefinitions, pcToken, JO_Assign);
	pcToken = AssertLiteral(&cTokenDefinitions, pcToken, true);
	pcToken = AssertSeparator(&cTokenDefinitions, pcToken, JS_Semicolon);
	pcToken = AssertKeyword(&cTokenDefinitions, pcToken, JK_boolean);
	pcToken = AssertIdentifier(&cTokenDefinitions, pcToken, "notTrue");
	pcToken = AssertOperator(&cTokenDefinitions, pcToken, JO_Assign);
	pcToken = AssertOperator(&cTokenDefinitions, pcToken, JO_LogicalNegate);
	pcToken = AssertIdentifier(&cTokenDefinitions, pcToken, "truey");
	pcToken = AssertSeparator(&cTokenDefinitions, pcToken, JS_Semicolon);
	pcToken = AssertIdentifier(&cTokenDefinitions, pcToken, "notTrue");
	pcToken = AssertOperator(&cTokenDefinitions, pcToken, JO_Assign);
	pcToken = AssertLiteral(&cTokenDefinitions, pcToken, (char16)4129);
	pcToken = AssertOperator(&cTokenDefinitions, pcToken, JO_Equal);
	pcToken = AssertLiteral(&cTokenDefinitions, pcToken, (char16)4130);
	pcToken = AssertSeparator(&cTokenDefinitions, pcToken, JS_Semicolon);
	pcToken = AssertKeyword(&cTokenDefinitions, pcToken, JK_return);
	pcToken = AssertLiteral(&cTokenDefinitions, pcToken, "AND Gate");
	pcToken = AssertSeparator(&cTokenDefinitions, pcToken, JS_Semicolon);
	pcToken = AssertSeparator(&cTokenDefinitions, pcToken, JS_CurlyBracketRight);
	AssertNull(pcToken);

	cTokenParser.Kill();
	cTokenDefinitions.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTokenParserStringEscapeChars(void)
{
	CJavaTokenParser		cTokenParser;
	CJavaTokenDefinitions	cTokenDefinitions;
	CJavaToken*				pcToken;
	CChars					szPretty;

	cTokenDefinitions.Init();
	cTokenParser.Init(&cTokenDefinitions, "Test5.Java", "return getType() + \" \\\"\" + name + \"\\\"\";");

	cTokenParser.Parse(TRUE);

	pcToken = cTokenParser.GetFirstToken();
	pcToken = AssertKeyword(&cTokenDefinitions, pcToken, JK_return);
	pcToken = AssertIdentifier(&cTokenDefinitions, pcToken, "getType");
	pcToken = AssertSeparator(&cTokenDefinitions, pcToken, JS_RoundBracketLeft);
	pcToken = AssertSeparator(&cTokenDefinitions, pcToken, JS_RoundBracketRight);
	pcToken = AssertOperator(&cTokenDefinitions, pcToken, JO_Plus);
	pcToken = AssertLiteral(&cTokenDefinitions, pcToken, " \"");
	pcToken = AssertOperator(&cTokenDefinitions, pcToken, JO_Plus);
	pcToken = AssertIdentifier(&cTokenDefinitions, pcToken, "name");
	pcToken = AssertOperator(&cTokenDefinitions, pcToken, JO_Plus);
	pcToken = AssertLiteral(&cTokenDefinitions, pcToken, "\"");
	pcToken = AssertSeparator(&cTokenDefinitions, pcToken, JS_Semicolon);
	AssertNull(pcToken);

	szPretty.Init();
	cTokenParser.PrettyPrint(&szPretty);
	AssertString("return getType() + \" \\\"\" + name + \"\\\"\";\n", szPretty.Text());
	szPretty.Kill();

	cTokenParser.Kill();
	cTokenDefinitions.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTokenParserFiles(void)
{
	CJavaTokenDefinitions	cTokenDefinitions;
	CJavaTokenParser		cTokenParser;
	CFileUtil				cFileUtil;
	CChars					sz;
	CTextFile				cFile;
	BOOL					bResult;

	sz.Init();
	cFileUtil.CurrentDirectory(&sz);
	cFileUtil.AppendToPath(&sz, "Input");
	cFileUtil.AppendToPath(&sz, "TickablePins.java");
	cFile.Init();
	bResult = cFile.Read(sz.Text());
	AssertTrue(bResult);
	cFile.PassifyNewlines();

	cTokenDefinitions.Init();
	cTokenParser.Init(&cTokenDefinitions, sz.Text(), cFile.Text());

	cTokenParser.Parse(TRUE);
	cFile.Kill();
	sz.Kill();

	cTokenParser.Dump();

	cTokenParser.Kill();
	cTokenDefinitions.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTokenParser(void)
{
	BeginTests();

	TestTokenParserEndOfFile();
	TestTokenParserStartAndEndWithComment();
	TestTokenParserComplexGeneric();
	TestTokenParserLiterals();
	TestTokenParserStringEscapeChars();
	TestTokenParserFiles();

	TestStatistics();
}

