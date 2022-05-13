#include "BaseLib/FastFunctions.h"
#include "BaseLib/PointerRemapper.h"
#include "BaseLib/TypeNames.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/TextFile.h"
#include "CoreLib/Operators.h"
#include "TestLib/Assert.h"
#include "JavaParserLib/JavaTokenParser.h"
#include "JavaParserLib/JavaSyntaxParser.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestJavaSyntaxParserStuff(void)
{
	CJavaTokenParser		cTokenParser;
	CJavaSyntaxParser		cSyntaxParser;
	CJavaTokenDefinitions	cTokenDefinitions;
	BOOL					bResult;
	CLogger					cLogger;
	char					szFileName[] = "Test1.Java";
	char					szFileContents[] = "\
package net.assembler;\n\
\n\
import static net.simulation.common.TraceValue.*;\n\
import java.util.List;\n\
\n\
public class W65C816Assembler\n\
{\n\
  private int y;\n\
\n\
  public W65C816Assembler()\n\
  {\n\
    int x = 5;\n\
  }\n\
}\n\
";

	cLogger.Init();
	cTokenDefinitions.Init();
	cTokenParser.Init(&cTokenDefinitions, szFileName, szFileContents);

	bResult = cTokenParser.Parse();
	AssertTrue(bResult);

	cSyntaxParser.Init(&cLogger, &cTokenDefinitions, szFileName, cTokenParser.GetFirstToken());

	cSyntaxParser.Parse();

	cSyntaxParser.Kill();
	cTokenParser.Kill();

	cTokenParser.Kill();
	cTokenDefinitions.Kill();
	cLogger.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestJavaSyntaxParser(void)
{
	BeginTests();

	TestJavaSyntaxParserStuff();

	TestStatistics();
}

