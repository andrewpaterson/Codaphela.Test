#include "BaseLib/FastFunctions.h"
#include "BaseLib/PointerRemapper.h"
#include "BaseLib/TypeNames.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/TextFile.h"
#include "CoreLib/Operators.h"
#include "TestLib/Assert.h"
#include "JavaParserLib/JavaTokenParserEnvironment.h"
#include "JavaParserLib/JavaSyntaxParser.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestJavaSyntaxParserGenericGeneric(void)
{
	BOOL						bResult;
	CTokenParserEnvironment		cTokenParser;
	CJavaSyntaxParser			cSyntaxParser;
	CJavaSyntaxMemory			cSyntaxMemory;
	char						szFilename[] = "Test2.Java";
	char						szFileContents[] = "\
public final class W65C816Assembler<List<List>>\n\
{\n\
}\n\
";

	cTokenParser.Init(szFilename, szFileContents, TRUE);
	AssertTrue(cTokenParser.Parse());

	cSyntaxMemory.Init();
	cSyntaxParser.Init(&cSyntaxMemory, cTokenParser.GetParser());

	bResult = cSyntaxParser.Parse();
	AssertTrue(bResult);
	cSyntaxParser.Dump(TRUE);

	cSyntaxParser.Kill();
	cSyntaxMemory.Kill();
	cTokenParser.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestJavaSyntaxParserGenericExtends(void)
{
	BOOL						bResult;
	CTokenParserEnvironment		cTokenParser;
	CJavaSyntaxParser			cSyntaxParser;
	CJavaSyntaxMemory			cSyntaxMemory;
	char						szFilename[] = "Test3.Java";
	char						szFileContents[] = "\
public final class W65C816Assembler<X extends Integer>\n\
{\n\
}\n\
";

	cTokenParser.Init(szFilename, szFileContents, TRUE);
	AssertTrue(cTokenParser.Parse());

	cSyntaxMemory.Init();
	cSyntaxParser.Init(&cSyntaxMemory, cTokenParser.GetParser());

	bResult = cSyntaxParser.Parse();
	AssertTrue(bResult);
	cSyntaxParser.Dump(TRUE);

	cSyntaxParser.Kill();
	cSyntaxMemory.Kill();
	cTokenParser.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestJavaSyntaxParserGenericWildcard(void)
{
	BOOL						bResult;
	CTokenParserEnvironment		cTokenParser;
	CJavaSyntaxParser			cSyntaxParser;
	CJavaSyntaxMemory			cSyntaxMemory;
	char						szFilename[] = "Test4.Java";
	char						szFileContents[] = "\
public final class W65C816Assembler<? extends Map<?, ?>>\n\
{\n\
}\n\
";

	cTokenParser.Init(szFilename, szFileContents, TRUE);
	AssertTrue(cTokenParser.Parse());

	cSyntaxMemory.Init();
	cSyntaxParser.Init(&cSyntaxMemory, cTokenParser.GetParser());

	bResult = cSyntaxParser.Parse();
	AssertTrue(bResult);
	cSyntaxParser.Dump(TRUE);

	cSyntaxParser.Kill();
	cSyntaxMemory.Kill();
	cTokenParser.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestJavaSyntaxParserGenericComplex(void)
{
	BOOL						bResult;
	CTokenParserEnvironment		cTokenParser;
	CJavaSyntaxParser			cSyntaxParser;
	CJavaSyntaxMemory			cSyntaxMemory;
	char						szFilename[] = "Test5.Java";
	char						szFileContents[] = "\
public class W65C816Assembler<X, Y extends List<Map<X, ? extends Integer>>, ? extends Map<?, ?>>\n\
{\n\
}\n\
";

	cTokenParser.Init(szFilename, szFileContents, TRUE);
	AssertTrue(cTokenParser.Parse());

	cSyntaxMemory.Init();
	cSyntaxParser.Init(&cSyntaxMemory, cTokenParser.GetParser());

	bResult = cSyntaxParser.Parse();
	AssertTrue(bResult);
	cSyntaxParser.Dump(TRUE);

	cSyntaxParser.Kill();
	cSyntaxMemory.Kill();
	cTokenParser.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestJavaSyntaxParserGenericError(void)
{
	BOOL						bResult;
	CTokenParserEnvironment		cTokenParser;
	CJavaSyntaxParser			cSyntaxParser;
	CJavaSyntaxMemory			cSyntaxMemory;
	CChars						szOutput;
	char* szBuffer;
	int							iLength;
	char						szFilename[] = "Test2.Java";
	char						szFileContents[] = "\
public final class W65C816Assembler<List \n\
{\n\
}\n\
";

	cTokenParser.Init(szFilename, szFileContents, FALSE);
	AssertTrue(cTokenParser.Parse());

	cSyntaxMemory.Init();
	cSyntaxParser.Init(&cSyntaxMemory, cTokenParser.GetParser());

	bResult = cSyntaxParser.Parse();
	AssertFalse(bResult);

	iLength = 0;
	szBuffer = cTokenParser.GetOutput(&iLength);
	szOutput.Init(szBuffer, 0, iLength);
	AssertString("ERROR: '>' or Type expected.\n\
[Test2.Java:2]:  { \n\
                 ^\n\
\n", szOutput.Text());
	szOutput.Kill();

	cSyntaxParser.Kill();
	cSyntaxMemory.Kill();
	cTokenParser.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestJavaSyntaxParserGenerics(void)
{
	BeginTests();

	TestJavaSyntaxParserGenericGeneric();
	TestJavaSyntaxParserGenericExtends();
	TestJavaSyntaxParserGenericWildcard();
	TestJavaSyntaxParserGenericComplex();
	TestJavaSyntaxParserGenericError();

	TestStatistics();
}

