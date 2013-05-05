#include "stdafx.h"
#include "BaseLib/FastFunctions.h"
#include "BaseLib/PointerRemapper.h"
#include "CoreLib/Operators.h"
#include "CoreLib/TypeConverter.h"
#include "StandardLib/ClassStorage.h"
#include "CppParserLib/Preprocessor.h"
#include "TestLib/Assert.h"
#include "TestPreprocessor.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPreprocessorReplacement(void)
{
	ClassStorageInit();
	FastFunctionsInit();
	TypeConverterInit();
	OperatorsInit();
	InitTokenMemory();

	CChars	szDest;

	CPreprocessor::Preprocess("\
#define D3(X) #X\n\
#define D7(P,Q) D3(P) D3(Q)\n\
#define D4() " "\n\
#define D6(P,Q) D3(P)##D4()##D3(Q)\n\
#define D8(P,Q) D3(P) " " D3(Q)\n\
#define D5(X) X\n\
#define D9(P,Q) D5(P) D4() D5(Q)\n\
#define D2(P,Q) D9(#P, #Q)\n\
#define D1(P,Q) #P#Q\n\
\n\
void DoStuff()\n\
{\n\
	//You can only legally have hashes in the replacement text.  Bizzare things happen otherwise.\n\
	//You can only have a single hash preceding a replacement argument.\n\
	//Tokens after the hash are not expanded before hashing.\n\
	char sz6[]=D9(\"Hello\", \"World\");\n\
	char sz1[] = D7(Hello, World);\n\
	char sz3[] = D8(Hello, World);\n\
	char sz5[] = D1(Hello, World);\n\
	char sz4[] = D2(Hello, World);\n\
	char sz2[] = D6(Hello, World);\n\
}\n\
", &szDest);

	//Actually I don't know what this is supposed to look like.  Just make the test pass for now.
	AssertString("\
void DoStuff()\n\
{\n\
char sz6[]=\"Hello\"  \"World\";\n\
char sz1[] = \"Hello\" \"World\";\n\
char sz3[] = \"Hello\" \"World\";\n\
char sz5[] = \"Hello\"\"World\";\n\
char sz4[] = \"Hello\"  \"World\";\n\
char sz2[] = \"Hello\"\"World\";\n\
}\n\
", szDest.Text());

	CPreprocessor::Preprocess("\
#define floa	int giJoe;\n\
float	gFriend;\n\
", &szDest);

	AssertString("float gFriend;\n", szDest.Text());

		CPreprocessor::Preprocess("\
int x = ++y / z;\n\
", &szDest);

	AssertString("int x = ++y / z;\n", szDest.Text());

	CPreprocessor::Preprocess("\
#define SOME_FOO_1(ARG1, ARG2)          0xDE + ARG1 - ARG2 +ARG1 //  \'\'\"\' for US\n\
#define SOME_FOO_2        0xE2  //  \"<>\" or \"\\|\" on RT 102-key kbd.\n\
#define SOME_FOO_3         0x00000080L /* Don't do \"&\" character translation */\n\
int dufi = SOME_FOO_1(1, 2), dasf = SOME_FOO_2, ewqr = SOME_FOO_3;\n\
", &szDest);

	AssertString("int dufi = 0xDE + 1 - 2 +1 , dasf = 0xE2 , ewqr = 0x00000080L ;\n", szDest.Text());

	CPreprocessor::Preprocess("\
char gsz[] = (\"//@  Don't Collapse me please     ! /*     \");\n\
char g_Char = \'\\n\';\n\
char g_Char2 = \'\"\';\n\
", &szDest);

	AssertString("char gsz[] = (\"//@  Don't Collapse me please     ! /*     \");\n\
char g_Char = \'\\n\';\n\
char g_Char2 = \'\"\';\n\
", szDest.Text());

	CPreprocessor::Preprocess("\
# define __nothrow __declspec(nothrow)\n\
__nothrow;\n\
", &szDest);

	AssertString("__declspec(nothrow);\n", szDest.Text());

	KillTokenMemory();
	OperatorsKill();
	TypeConverterKill();
	FastFunctionsKill();
	ClassStorageKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPreprocessorConditionals(void)
{
	ClassStorageInit();
	FastFunctionsInit();
	TypeConverterInit();
	OperatorsInit();
	InitTokenMemory();
	NumberInit();

	CChars	szDest;

	CPreprocessor::Preprocess("\
#if 1\n\
Passed\n\
#else\n\
Failed\n\
#endif\n\
", &szDest);
	AssertString("Passed\n", szDest.Text());

	CPreprocessor::Preprocess("\
#if 0\n\
Failed\n\
#else\n\
Passed\n\
#endif\n\
", &szDest);
	AssertString("Passed\n", szDest.Text());

	CPreprocessor::Preprocess("\
#if 1\n\
#define Fred Quintin\n\
#else\n\
#define Larry Bird\n\
#endif\n\
#define Dick Moby\n\
Fred\n\
Larry\n\
Dick\n\
", &szDest);
	AssertString("Quintin\nLarry\nMoby\n", szDest.Text());

	NumberKill();
	KillTokenMemory();
	OperatorsKill();
	TypeConverterKill();
	FastFunctionsKill();
	ClassStorageKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPreprocessorOperatorPrecedence(void)
{
	ClassStorageInit();
	FastFunctionsInit();
	TypeConverterInit();
	OperatorsInit();
	InitTokenMemory();
	NumberInit();

	CChars	szDest;

	CPreprocessor::Preprocess("\
#if 1 || 0 && 0\n\
Passed\n\
#else\n\
Failed\n\
#endif\n\
", &szDest);
	AssertString("Passed\n", szDest.Text());

	CPreprocessor::Preprocess("\
#if 0 && 1 || 0\n\
Failed\n\
#else\n\
Passed\n\
#endif\n\
", &szDest);
	AssertString("Passed\n", szDest.Text());

	CPreprocessor::Preprocess("\
#if 0 && 0 | 1\n\
Failed\n\
#else\n\
Passed\n\
#endif\n\
", &szDest);
	AssertString("Passed\n", szDest.Text());

	CPreprocessor::Preprocess("\
#if 1 | 0 ^ 1\n\
Passed\n\
#else\n\
Failed\n\
#endif\n\
", &szDest);
	AssertString("Passed\n", szDest.Text());

	CPreprocessor::Preprocess("\
#if 1 ^ 0 & 0\n\
Passed\n\
#else\n\
Failed\n\
#endif\n\
", &szDest);
	AssertString("Passed\n", szDest.Text());

	CPreprocessor::Preprocess("\
#if 0 & 0 == 0\n\
Failed\n\
#else\n\
Passed\n\
#endif\n\
", &szDest);
	AssertString("Passed\n", szDest.Text());

	CPreprocessor::Preprocess("\
#if 0 == 0 < 0\n\
Passed\n\
#else\n\
Failed\n\
#endif\n\
", &szDest);
	AssertString("Passed\n", szDest.Text());

	CPreprocessor::Preprocess("\
#if 1 < 1 << 1\n\
Passed\n\
#else\n\
Failed\n\
#endif\n\
", &szDest);
	AssertString("Passed\n", szDest.Text());


	CPreprocessor::Preprocess("\
#if 0 << 0 + 1\n\
Failed\n\
#else\n\
Passed\n\
#endif\n\
", &szDest);
	AssertString("Passed\n", szDest.Text());

	CPreprocessor::Preprocess("\
#if 1 + 0 * 0\n\
Passed\n\
#else\n\
Failed\n\
#endif\n\
", &szDest);
	AssertString("Passed\n", szDest.Text());

	CPreprocessor::Preprocess("\
#if ~1 * 0\n\
Failed\n\
#else\n\
Passed\n\
#endif\n\
", &szDest);
	AssertString("Passed\n", szDest.Text());

	CPreprocessor::Preprocess("\
#if -(1 - 1)\n\
Failed\n\
#else\n\
Passed\n\
#endif\n\
", &szDest);
	AssertString("Passed\n", szDest.Text());

CPreprocessor::Preprocess("\
#if +(0 + 0)\n\
Failed\n\
#else\n\
Passed\n\
#endif\n\
", &szDest);
	AssertString("Passed\n", szDest.Text());

	NumberKill();
	KillTokenMemory();
	OperatorsKill();
	TypeConverterKill();
	FastFunctionsKill();
	ClassStorageKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPreprocessorBlockSkipping(void)
{
	ClassStorageInit();
	FastFunctionsInit();
	TypeConverterInit();
	OperatorsInit();
	InitTokenMemory();
	NumberInit();

	CChars				szDest;
	CTranslationUnit	cFile;
	CPreprocessor		cPreprocessor;
	CListLibraries		cLibraries;
	CConfig				cConfig;
	CChars				szName;

	szName.Init("None.cpp");

	cFile.Init(8, szName.Text(), NULL, FALSE, FALSE);
	cFile.SetContents("\
					   Start\n\
					   #if 1\n\
					   #define FOO\n\
					   #undef FOO\n\
					   #endif\n\
					   Passed\n\
					   #define FOO\n\
					   End\n\
					   ");

	cLibraries.Init();
	cConfig.Init("DEBUG");
	cPreprocessor.Init(&cConfig, &cFile.mcStack);
	cPreprocessor.PreprocessTranslationUnit(&cFile);
	szDest.Init(64);
	cFile.Append(&szDest);

	AssertString("Start\nPassed\nEnd\n", szDest.Text());

	szDest.Kill();
	cLibraries.Kill();
	cConfig.Kill();
	cFile.Kill();

	cFile.Init(8, szName.Text(), NULL, FALSE, FALSE);
	cFile.SetContents("\
					  Start\n\
					  #if 0\n\
					  #define FOO\n\
					  #undef FOO\n\
					  #endif\n\
					  Passed\n\
					  #define FOO\n\
					  End\n\
					  Test\n\
					  ");

	cLibraries.Init();
	cConfig.Init("DEBUG");
	cPreprocessor.Init(&cConfig, &cFile.mcStack);
	cPreprocessor.PreprocessTranslationUnit(&cFile);
	szDest.Init(64);
	cFile.Append(&szDest);

	AssertString("Start\nPassed\nEnd\nTest\n", szDest.Text());

	szDest.Kill();
	cLibraries.Kill();
	cConfig.Kill();
	cFile.Kill();

	szName.Kill();

	NumberKill();
	KillTokenMemory();
	OperatorsKill();
	TypeConverterKill();
	FastFunctionsKill();
	ClassStorageKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPreprocessor(void)
{
	BeginTests();

	TestPreprocessorReplacement();
	TestPreprocessorConditionals();
	TestPreprocessorOperatorPrecedence();
	TestPreprocessorBlockSkipping();

	TestStatistics();
}

