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

	cTokenParser.Init(szFilename, szFileContents, TRUE);
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
void TestJavaSyntaxParserImports(void)
{
	BeginTests();

	TestJavaSyntaxParserImport();

	TestStatistics();
}

