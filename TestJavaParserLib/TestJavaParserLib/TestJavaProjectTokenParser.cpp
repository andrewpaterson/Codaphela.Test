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
void PrettyPrintFile(char* szFileName)
{
	BeginTests();

	CJavaTokenDefinitions	cTokenDefinitions;
	CJavaTokenParser		cTokenParser;
	CTextFile				cFile;
	BOOL					bResult;
	CChars					szPretty;


	cFile.Init();
	bResult = cFile.Read(szFileName);
	AssertTrue(bResult);
	cFile.PassifyNewlines();

	cTokenDefinitions.Init();
	cTokenParser.Init(&cTokenDefinitions, szFileName, cFile.Text());

	bResult = cTokenParser.Parse(TRUE);
	AssertTrue(bResult);

	cFile.Kill();

	szPretty.Init(" /////////////// ");
	szPretty.Append(szFileName);
	szPretty.Append(" /////////////// ");
	
	szPretty.AppendNewLine();
	cTokenParser.PrettyPrint(&szPretty);

	szPretty.Dump();
	szPretty.Kill();

	cTokenParser.Kill();
	cTokenDefinitions.Kill();

	TestStatistics();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestJavaProjectTokenParser(void)
{
	BeginTests();

	CFileUtil				cFileUtil;
	CChars					sz;
	CArrayChars				aszJavaFileNames;
	int						i;
	CChars*					szFileName;

	sz.Init("D:" _FS_ "Work" _FS_ "658-Computer" _FS_ "logi65816" _FS_ "src");

	aszJavaFileNames.Init();
	cFileUtil.FindFilesWithExtension(sz.Text(), "java", &aszJavaFileNames, TRUE);
	sz.Kill();

	for (i = 0; i < aszJavaFileNames.NumElements(); i++)
	{
		szFileName = aszJavaFileNames.Get(i);
		PrettyPrintFile(szFileName->Text());
	}
	aszJavaFileNames.Kill();

	TestStatistics();
}

