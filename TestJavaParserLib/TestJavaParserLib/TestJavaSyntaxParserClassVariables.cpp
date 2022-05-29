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
	CStatementArray*			papcStatements;
	CJavaSyntaxStatement*		pcStatement;
	char						szFilename[] = __ENGINE_PRETTY_FUNCTION__".Java";
	char						szFileContents[] = "\
class Clazz\n\
{\n\
	private int y[];\n\
	public static final X x;\n\
}\n\
";

	cTokenParser.Init(szFilename, szFileContents, FALSE);
	AssertTrue(cTokenParser.Parse());
	cSyntaxMemory.Init();
	cSyntaxParser.Init(&cSyntaxMemory, cTokenParser.GetParser());
	AssertTrue(cSyntaxParser.Parse());

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
	pcType->PrettyPrint(&sz);
	AssertString("Clazz", sz.Text());
	sz.Kill();
	pcBlock = pcClass->GetBlock();
	AssertNotNull(pcBlock);
	papcStatements = pcBlock->GetStatements();
	AssertNotNull(papcStatements);
	AssertInt(2, papcStatements->NumElements());
	pcStatement = papcStatements->GetPtr(0);
	AssertTrue(pcStatement->IsStatement());
	AssertTrue(pcStatement->IsVariableDeclaration());
	sz.Init();
	pcStatement->PrettyPrint(&sz, 0);
	AssertString("private int y[]", sz.Text());
	sz.Kill();

	pcStatement = papcStatements->GetPtr(1);
	AssertTrue(pcStatement->IsStatement());
	AssertTrue(pcStatement->IsVariableDeclaration());
	sz.Init();
	pcStatement->PrettyPrint(&sz, 0);
	AssertString("public static final X x", sz.Text());
	sz.Kill();

	sz.Init();
	pcFile->PrettyPrint(&sz, 0);
	AssertString("\
Class Clazz\n\
{\n\
	private int y[];\n\
	public static final X x;\n\
}\n\
", sz.Text());
	sz.Kill();

	cSyntaxParser.Kill();
	cSyntaxMemory.Kill();
	cTokenParser.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestJavaSyntaxParserClassVariablesGenericDeclaration(void)
{
	CTokenParserEnvironment		cTokenParser;
	CJavaSyntaxParser			cSyntaxParser;
	CJavaSyntaxMemory			cSyntaxMemory;
	CJavaSyntaxFile* pcFile;
	CJavaSyntaxPackage* pcPackage;
	CImportArray* papcImports;
	CClassCommonArray* papcClasses;
	CJavaSyntaxClass* pcClass;
	CJavaSyntaxType* pcType;
	CJavaSyntaxClassBlock* pcBlock;
	CChars						sz;
	CStatementArray* papcStatements;
	CJavaSyntaxStatement* pcStatement;
	char						szFilename[] = __ENGINE_PRETTY_FUNCTION__".Java";
	char						szFileContents[] = "\
class Clazz\n\
{\n\
	public final List<Map<? extends X, ? extends Integer>> map;\n\
}\n\
";

	cTokenParser.Init(szFilename, szFileContents, FALSE);
	AssertTrue(cTokenParser.Parse());
	cSyntaxMemory.Init();
	cSyntaxParser.Init(&cSyntaxMemory, cTokenParser.GetParser());
	AssertTrue(cSyntaxParser.Parse());

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
	pcType->PrettyPrint(&sz, 0);
	AssertString("Clazz", sz.Text());
	sz.Kill();
	pcBlock = pcClass->GetBlock();
	AssertNotNull(pcBlock);
	papcStatements = pcBlock->GetStatements();
	AssertNotNull(papcStatements);
	AssertInt(2, papcStatements->NumElements());
	pcStatement = papcStatements->GetPtr(0);
	AssertTrue(pcStatement->IsStatement());
	AssertTrue(pcStatement->IsVariableDeclaration());
	sz.Init();
	pcStatement->PrettyPrint(&sz, 0);
	AssertString("private int y[];", sz.Text());
	sz.Kill();

	pcStatement = papcStatements->GetPtr(1);
	AssertTrue(pcStatement->IsStatement());
	AssertTrue(pcStatement->IsVariableDeclaration());
	sz.Init();
	pcStatement->PrettyPrint(&sz, 0);
	AssertString("public static final X x;", sz.Text());
	sz.Kill();

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
	char						szFilename[] = __ENGINE_PRETTY_FUNCTION__".Java";
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

