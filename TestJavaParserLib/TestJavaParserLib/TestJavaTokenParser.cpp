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
	CJavaTokenParser	cTokenParser;

	cTokenParser.Init("Test1.Java", "{\n}");
	cTokenParser.Parse();
	cTokenParser.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTokenParserStartAndEndWithComment(void)
{
	CJavaTokenParser	cTokenParser;
	
	cTokenParser.Init("Test2.Java", "\
  // Tickable Pins Start\n\
package net.simulation.common;\n\
\n\
{\n\
  protected int x;\n\
} // Tickable Pins End\
");

	cTokenParser.Parse();
	cTokenParser.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTokenParserComplexGeneric(void)
{
	CJavaTokenParser	cTokenParser;

	cTokenParser.Init("Test3.Java", "\
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
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTokenParserLiterals(void)
{
	CJavaTokenParser	cTokenParser;
	CJavaToken*			pcToken;
	//CChars				szPretty;

	cTokenParser.Init("Test4.Java", "\
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
	cTokenParser.Dump(TRUE);

	pcToken = cTokenParser.GetFirstToken();
	
	pcToken = AssertKeyword(pcToken, JK_public);
	pcToken = AssertIdentifier(pcToken, "String");
	pcToken = AssertIdentifier(pcToken, "getType");
	pcToken = AssertSeparator(pcToken, JS_RoundBracketLeft);
	pcToken = AssertSeparator(pcToken, JS_RoundBracketRight);
	pcToken = AssertSeparator(pcToken, JS_CurlyBracketLeft);
	pcToken = AssertKeyword(pcToken, JK_long);
	pcToken = AssertIdentifier(pcToken, "xl");
	pcToken = AssertOperator(pcToken, JO_Assign);
	pcToken = AssertLiteral(pcToken, 1LL);
	pcToken = AssertSeparator(pcToken, JS_Semicolon);
	pcToken = AssertKeyword(pcToken, JK_int);
	pcToken = AssertIdentifier(pcToken, "x");
	pcToken = AssertOperator(pcToken, JO_Assign);
	pcToken = AssertLiteral(pcToken, 10000);
	pcToken = AssertSeparator(pcToken, JS_Semicolon);
	pcToken = AssertKeyword(pcToken, JK_float);
	pcToken = AssertIdentifier(pcToken, "f");
	pcToken = AssertOperator(pcToken, JO_Assign);
	pcToken = AssertLiteral(pcToken, 1000.f);
	pcToken = AssertSeparator(pcToken, JS_Semicolon);
	pcToken = AssertKeyword(pcToken, JK_double);
	pcToken = AssertIdentifier(pcToken, "fl");
	pcToken = AssertOperator(pcToken, JO_Assign);
	pcToken = AssertLiteral(pcToken, 1.33e+10);
	pcToken = AssertSeparator(pcToken, JS_Semicolon);
	pcToken = AssertKeyword(pcToken, JK_char);
	pcToken = AssertIdentifier(pcToken, "c");
	pcToken = AssertOperator(pcToken, JO_Assign);
	pcToken = AssertLiteral(pcToken, '!');
	pcToken = AssertSeparator(pcToken, JS_Semicolon);
	pcToken = AssertKeyword(pcToken, JK_char);
	pcToken = AssertIdentifier(pcToken, "c2");
	pcToken = AssertOperator(pcToken, JO_Assign);
	pcToken = AssertLiteral(pcToken, 'A');
	pcToken = AssertSeparator(pcToken, JS_Semicolon);
	pcToken = AssertKeyword(pcToken, JK_boolean);
	pcToken = AssertIdentifier(pcToken, "truey");
	pcToken = AssertOperator(pcToken, JO_Assign);
	pcToken = AssertLiteral(pcToken, true);
	pcToken = AssertSeparator(pcToken, JS_Semicolon);
	pcToken = AssertKeyword(pcToken, JK_boolean);
	pcToken = AssertIdentifier(pcToken, "notTrue");
	pcToken = AssertOperator(pcToken, JO_Assign);
	pcToken = AssertOperator(pcToken, JO_LogicalNegate);
	pcToken = AssertIdentifier(pcToken, "truey");
	pcToken = AssertSeparator(pcToken, JS_Semicolon);
	pcToken = AssertIdentifier(pcToken, "notTrue");
	pcToken = AssertOperator(pcToken, JO_Assign);
	pcToken = AssertLiteral(pcToken, (char16)4129);
	pcToken = AssertOperator(pcToken, JO_Equal);
	pcToken = AssertLiteral(pcToken, (char16)4130);
	pcToken = AssertSeparator(pcToken, JS_Semicolon);
	pcToken = AssertKeyword(pcToken, JK_return);
	pcToken = AssertLiteral(pcToken, "AND Gate");
	pcToken = AssertSeparator(pcToken, JS_Semicolon);
	pcToken = AssertSeparator(pcToken, JS_CurlyBracketRight);

	cTokenParser.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTokenParserStringEscapeChars(void)
{
	CJavaTokenParser	cTokenParser;
	CJavaToken*			pcToken;
	CChars				szPretty;

	cTokenParser.Init("Test5.Java", "return getType() + \" \\\"\" + name + \"\\\"\";");

	cTokenParser.Parse(TRUE);

	pcToken = cTokenParser.GetFirstToken();
	pcToken = AssertKeyword(pcToken, JK_return);
	pcToken = AssertIdentifier(pcToken, "getType");
	pcToken = AssertSeparator(pcToken, JS_RoundBracketLeft);
	pcToken = AssertSeparator(pcToken, JS_RoundBracketRight);
	pcToken = AssertOperator(pcToken, JO_Plus);
	pcToken = AssertLiteral(pcToken, " \"");
	pcToken = AssertOperator(pcToken, JO_Plus);
	pcToken = AssertIdentifier(pcToken, "name");
	pcToken = AssertOperator(pcToken, JO_Plus);
	pcToken = AssertLiteral(pcToken, "\"");
	pcToken = AssertSeparator(pcToken, JS_Semicolon);
	AssertNull(pcToken);

	szPretty.Init();
	cTokenParser.PrettyPrint(&szPretty);
	AssertString("return getType() + \" \\\"\" + name + \"\\\"\";\n", szPretty.Text());
	szPretty.Kill();

	cTokenParser.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTokenParserFiles(void)
{
	CJavaTokenParser	cTokenParser;
	CFileUtil			cFileUtil;
	CChars				sz;
	CTextFile			cFile;
	BOOL				bResult;

	sz.Init();
	cFileUtil.CurrentDirectory(&sz);
	cFileUtil.AppendToPath(&sz, "Input");
	cFileUtil.AppendToPath(&sz, "TickablePins.java");
	cFile.Init();
	bResult = cFile.Read(sz.Text());
	AssertTrue(bResult);
	cFile.PassifyNewlines();

	cTokenParser.Init(sz.Text(), cFile.Text());

	cTokenParser.Parse(TRUE);
	cFile.Kill();
	sz.Kill();

	cTokenParser.Dump();

	cTokenParser.Kill();
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

