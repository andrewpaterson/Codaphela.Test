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
	CJavaTokenMemory		cTokenMemory;
	CJavaSyntaxMemory		cSyntaxMemory;
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
	cTokenMemory.Init();
	cTokenParser.Init(&cTokenDefinitions, &cTokenMemory, szFileName, szFileContents);

	bResult = cTokenParser.Parse();
	AssertTrue(bResult);

	cSyntaxMemory.Init();
	cSyntaxParser.Init(&cLogger, &cSyntaxMemory, &cTokenDefinitions, &cTokenMemory, szFileName, cTokenParser.GetFirstToken());

	cSyntaxParser.Parse();

	cSyntaxParser.Kill();
	cTokenParser.Kill();
	cSyntaxMemory.Kill();
	cTokenMemory.Kill();
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

