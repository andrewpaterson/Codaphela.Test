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
void TestJavaSyntaxParserImport(void)
{
	CTokenParserEnvironment		cTokenParser;
	CJavaSyntaxParser			cSyntaxParser;
	CJavaSyntaxMemory			cSyntaxMemory;
	CChars						sz;
	char						szFilename[] = "Test3.Java";
	char						szFileContents[] = "\
package net.assembler;\n\
\n\
import static net.simulation.common.TraceValue.*; \n\
import net.simulation.common.TraceValue; \n\
\n\
import java.util.ArrayList; \n\
import java.util.List; \n\
import java.util.Map; \n\
";

	cTokenParser.Init(szFilename, szFileContents);
	AssertTrue(cTokenParser.Parse());

	cSyntaxMemory.Init();
	cSyntaxParser.Init(&cSyntaxMemory, cTokenParser.GetParser());

	cSyntaxParser.Parse();
	sz.Init();
	cSyntaxParser.TypePrint(&sz);
	AssertString("\
File: Test3.Java\n\
  Package: net.assembler\n\
  Import: net.simulation.common.TraceValue\n\
  Import: net.simulation.common.TraceValue\n\
  Import: java.util.ArrayList\n\
  Import: java.util.List\n\
  Import: java.util.Map\n", sz.Text());
	sz.Kill();

	cSyntaxParser.Kill();
	cSyntaxMemory.Kill();
	cTokenParser.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestJavaSyntaxParserGenericGeneric(void)
{
	CTokenParserEnvironment		cTokenParser;
	CJavaSyntaxParser			cSyntaxParser;
	CJavaSyntaxMemory			cSyntaxMemory;
	char						szFilename[] = "Test2.Java";
	char						szFileContents[] = "\
class W65C816Assembler<List<List>>\n\
{\n\
}\n\
";

	cTokenParser.Init(szFilename, szFileContents);
	AssertTrue(cTokenParser.Parse());

	cSyntaxMemory.Init();
	cSyntaxParser.Init(&cSyntaxMemory, cTokenParser.GetParser());

	cSyntaxParser.Parse();
	cSyntaxParser.Dump(TRUE);

	cSyntaxParser.Kill();
	cSyntaxMemory.Kill();
	cTokenParser.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestJavaSyntaxParserStuff(void)
{
	CTokenParserEnvironment		cTokenParser;
	CJavaSyntaxParser			cSyntaxParser;
	CJavaSyntaxMemory			cSyntaxMemory;
	char						szFilename[] = "Test3.Java";
	char						szFileContents[] = "\
package net.assembler;\n\
\n\
import static net.simulation.common.TraceValue.*; \n\
import net.simulation.common.TraceValue; \n\
\n\
import java.util.ArrayList; \n\
import java.util.List; \n\
import java.util.Map; \n\
\n\
public class W65C816Assembler<X, Y extends List<Map<X, ? extends Integer>>>\n\
{\n\
  private int y; \n\
  private X x; \n\
\n\
  public W65C816Assembler()\n\
  {\n\
    TraceValue value = NotConnected;\n\
    List<Map<X, Integer>> map = new ArrayList<>();\n\
    int x = 5;\n\
  }\n\
}\n\
";

//	It breaks on Map because list starts getting a generic but expects an extend not a Map

	cTokenParser.Init(szFilename, szFileContents);
	AssertTrue(cTokenParser.Parse());

	cSyntaxMemory.Init();
	cSyntaxParser.Init(&cSyntaxMemory, cTokenParser.GetParser());

	cSyntaxParser.Parse();

	cSyntaxParser.Kill();
	cSyntaxMemory.Kill();
	cTokenParser.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestJavaSyntaxParser(void)
{
	BeginTests();

	//TestJavaSyntaxParserImport();
	TestJavaSyntaxParserGenericGeneric();
	TestJavaSyntaxParserStuff();

	TestStatistics();
}

