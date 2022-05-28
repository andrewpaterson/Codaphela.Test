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
void TestJavaSyntaxParserClassVariablesSimpleDeclaration(void)
{
	CTokenParserEnvironment		cTokenParser;
	CJavaSyntaxParser			cSyntaxParser;
	CJavaSyntaxMemory			cSyntaxMemory;
	CJavaSyntaxFile*			pcFile;
	CJavaSyntaxPackage*			pcPackage;
	CImportArray*				papcImports;
	CClassCommonArray*			papcClasses;
	CJavaSyntaxClass*			pcClass;
	CJavaSyntaxType*			pcType;
	CJavaSyntaxClassBlock*		pcBlock;
	CChars						sz;
	char						szFilename[] = "TestClassVariablesSimpleDeclaration.Java";
	char						szFileContents[] = "\
class Clazz\n\
{\n\
	private int y;\n\
	private X x;\n\
}\n\
";

	cTokenParser.Init(szFilename, szFileContents, FALSE);
	AssertTrue(cTokenParser.Parse());

	cSyntaxMemory.Init();
	cSyntaxParser.Init(&cSyntaxMemory, cTokenParser.GetParser());

	cSyntaxParser.Parse();

	cSyntaxParser.Dump(TRUE);
	cTokenParser.DumpLog();

	pcFile = cSyntaxParser.GetSyntaxFile();
	pcPackage = pcFile->GetPackage();
	AssertNull(pcPackage);

	papcImports = pcFile->GetImports();
	AssertNotNull(papcImports);
	AssertInt(0, papcImports->NumElements());

	papcClasses = pcFile->GetClasses();
	AssertNotNull(papcClasses);
	AssertInt(1, papcClasses->NumElements());

	pcClass = (CJavaSyntaxClass*)papcClasses->GetPtr(0);
	AssertTrue(pcClass->IsClassCommon());
	AssertTrue(pcClass->IsClass());

	pcType = pcClass->GetSyntaxType();
	sz.Init();
	AssertString("", pcType->PrettyPrint(&sz));
	sz.Kill();
	pcBlock = pcClass->GetBlock();

	cSyntaxParser.Kill();
	cSyntaxMemory.Kill();
	cTokenParser.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestJavaSyntaxParserClassVariablesSimpleInitialisation(void)
{
	CTokenParserEnvironment		cTokenParser;
	CJavaSyntaxParser			cSyntaxParser;
	CJavaSyntaxMemory			cSyntaxMemory;
	char						szFilename[] = "TestClassVariables.Java";
	char						szFileContents[] = "\
class Clazz\n\
{\n\
  public static final String s = \"\";\n\
  java.util.Date date = new Date();\n\
}\n\
";

	cTokenParser.Init(szFilename, szFileContents, FALSE);
	AssertTrue(cTokenParser.Parse());

	cSyntaxMemory.Init();
	cSyntaxParser.Init(&cSyntaxMemory, cTokenParser.GetParser());

	cSyntaxParser.Parse();
	cTokenParser.DumpLog();

	cSyntaxParser.Kill();
	cSyntaxMemory.Kill();
	cTokenParser.Kill();
}



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestJavaSyntaxParserClassVariables(void)
{
	BeginTests();

	TestJavaSyntaxParserClassVariablesSimpleDeclaration();
	TestJavaSyntaxParserClassVariablesSimpleInitialisation();

	TestStatistics();
}

