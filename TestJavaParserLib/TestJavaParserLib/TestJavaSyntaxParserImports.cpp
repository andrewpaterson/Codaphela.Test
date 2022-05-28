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
	char						szFilename[] = __ENGINE_PRETTY_FUNCTION__".Java";
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
void TestJavaSyntaxParserPackageError(void)
{
	CTokenParserEnvironment		cTokenParser;
	CJavaSyntaxParser			cSyntaxParser;
	CJavaSyntaxMemory			cSyntaxMemory;
	CChars						szOutput;
	BOOL						bResult;

	cTokenParser.Init(NULL, "package;", FALSE);
	AssertTrue(cTokenParser.Parse());
	cSyntaxMemory.Init();
	cSyntaxParser.Init(&cSyntaxMemory, cTokenParser.GetParser());
	bResult = cSyntaxParser.Parse();
	AssertFalse(bResult);

	AssertString("ERROR: Identifier expected.\n\
package;\n\
       ^", cTokenParser.GetOutput(&szOutput));
	szOutput.Kill();
	cSyntaxParser.Kill();
	cSyntaxMemory.Kill();
	cTokenParser.Kill();


	cTokenParser.Init(NULL, "package net.;", FALSE);
	AssertTrue(cTokenParser.Parse());
	cSyntaxMemory.Init();
	cSyntaxParser.Init(&cSyntaxMemory, cTokenParser.GetParser());
	bResult = cSyntaxParser.Parse();
	AssertFalse(bResult);

	AssertString("ERROR: Identifier expected.\n\
package net.;\n\
            ^", cTokenParser.GetOutput(&szOutput));
	szOutput.Kill();
	cSyntaxParser.Kill();
	cSyntaxMemory.Kill();
	cTokenParser.Kill();


	cTokenParser.Init(NULL, "package net.;", FALSE);
	AssertTrue(cTokenParser.Parse());
	cSyntaxMemory.Init();
	cSyntaxParser.Init(&cSyntaxMemory, cTokenParser.GetParser());
	bResult = cSyntaxParser.Parse();
	AssertFalse(bResult);

	AssertString("ERROR: Identifier expected.\n\
package net.;\n\
            ^", cTokenParser.GetOutput(&szOutput));
	szOutput.Kill();
	cSyntaxParser.Kill();
	cSyntaxMemory.Kill();
	cTokenParser.Kill();


	cTokenParser.Init(NULL, "package net.3.parse;", FALSE);
	AssertTrue(cTokenParser.Parse());
	cSyntaxMemory.Init();
	cSyntaxParser.Init(&cSyntaxMemory, cTokenParser.GetParser());
	bResult = cSyntaxParser.Parse();
	AssertFalse(bResult);

	AssertString("ERROR: Identifier expected.\n\
package net.3.parse;\n\
            ^", cTokenParser.GetOutput(&szOutput));
	szOutput.Kill();
	cSyntaxParser.Kill();
	cSyntaxMemory.Kill();
	cTokenParser.Kill();


	cTokenParser.Init(NULL, "package net", FALSE);
	AssertTrue(cTokenParser.Parse());
	cSyntaxMemory.Init();
	cSyntaxParser.Init(&cSyntaxMemory, cTokenParser.GetParser());
	bResult = cSyntaxParser.Parse();
	AssertFalse(bResult);

	AssertString("ERROR: '.' or ';' expected.\n\
package net\n\
           ^", cTokenParser.GetOutput(&szOutput));
	szOutput.Kill();
	cSyntaxParser.Kill();
	cSyntaxMemory.Kill();
	cTokenParser.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestJavaSyntaxParserImportError(void)
{
	CTokenParserEnvironment		cTokenParser;
	CJavaSyntaxParser			cSyntaxParser;
	CJavaSyntaxMemory			cSyntaxMemory;
	CChars						szOutput;
	BOOL						bResult;

	cTokenParser.Init(NULL, "import static net.simulation.common.TraceValue.*", FALSE);
	AssertTrue(cTokenParser.Parse());
	cSyntaxMemory.Init();
	cSyntaxParser.Init(&cSyntaxMemory, cTokenParser.GetParser());
	bResult = cSyntaxParser.Parse();
	AssertFalse(bResult);

	AssertString("ERROR: ';' expected.\n\
import static net.simulation.common.TraceValue.*\n\
                                                ^", 
		cTokenParser.GetOutput(&szOutput));
	szOutput.Kill();
	cSyntaxParser.Kill();
	cSyntaxMemory.Kill();
	cTokenParser.Kill();


	cTokenParser.Init(NULL, "import static.simulation.common.TraceValue.*;", FALSE);
	AssertTrue(cTokenParser.Parse());
	cSyntaxMemory.Init();
	cSyntaxParser.Init(&cSyntaxMemory, cTokenParser.GetParser());
	bResult = cSyntaxParser.Parse();
	AssertFalse(bResult);

	AssertString("ERROR: Identifier expected.\n\
import static.simulation.common.TraceValue.*;\n\
             ^",
		cTokenParser.GetOutput(&szOutput));
	szOutput.Kill();
	cSyntaxParser.Kill();
	cSyntaxMemory.Kill();
	cTokenParser.Kill();


	cTokenParser.Init(NULL, "import static ;", FALSE);
	//cTokenParser.Init(NULL, "import static net.simulation.common.TraceValue.*", FALSE);
	AssertTrue(cTokenParser.Parse());
	cSyntaxMemory.Init();
	cSyntaxParser.Init(&cSyntaxMemory, cTokenParser.GetParser());
	bResult = cSyntaxParser.Parse();
	AssertFalse(bResult);

	AssertString("ERROR: Identifier expected.\n\
import static ;\n\
              ^",
		cTokenParser.GetOutput(&szOutput));
	szOutput.Kill();
	cSyntaxParser.Kill();
	cSyntaxMemory.Kill();
	cTokenParser.Kill();


	cTokenParser.Init(NULL, "import static *;", FALSE);
	//cTokenParser.Init(NULL, "import static net.simulation.common.TraceValue.*", FALSE);
	AssertTrue(cTokenParser.Parse());
	cSyntaxMemory.Init();
	cSyntaxParser.Init(&cSyntaxMemory, cTokenParser.GetParser());
	bResult = cSyntaxParser.Parse();
	AssertFalse(bResult);

	AssertString("ERROR: Identifier expected.\n\
import static *;\n\
              ^",
		cTokenParser.GetOutput(&szOutput));
	szOutput.Kill();
	cSyntaxParser.Kill();
	cSyntaxMemory.Kill();
	cTokenParser.Kill();


	cTokenParser.Init(NULL, "import net.simulation.;", FALSE);
	AssertTrue(cTokenParser.Parse());
	cSyntaxMemory.Init();
	cSyntaxParser.Init(&cSyntaxMemory, cTokenParser.GetParser());
	bResult = cSyntaxParser.Parse();
	AssertFalse(bResult);

	AssertString("ERROR: Identifier expected.\n\
import net.simulation.;\n\
                      ^",
		cTokenParser.GetOutput(&szOutput));
	szOutput.Kill();
	cSyntaxParser.Kill();
	cSyntaxMemory.Kill();
	cTokenParser.Kill();


	cTokenParser.Init(NULL, "import", FALSE);
	AssertTrue(cTokenParser.Parse());
	cSyntaxMemory.Init();
	cSyntaxParser.Init(&cSyntaxMemory, cTokenParser.GetParser());
	bResult = cSyntaxParser.Parse();
	AssertFalse(bResult);

	AssertString("ERROR: Identifier expected.\n\
import\n\
      ^",
		cTokenParser.GetOutput(&szOutput));
	szOutput.Kill();
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
	TestJavaSyntaxParserPackageError();
	TestJavaSyntaxParserImportError();

	TestStatistics();
}

