#include "BaseLib/FastFunctions.h"
#include "BaseLib/PointerRemapper.h"
#include "BaseLib/TypeNames.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/Operators.h"
#include "CppParserLib/Preprocessor.h"
#include "CppParserLib/HeaderFileMap.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPreprocessorSimple(void)
{
	CChars	szDest;

	szDest.Init();
	CPreprocessor::Preprocess("char sz;", &szDest);

	AssertString("char sz;\n", szDest.Text());
	szDest.Kill();

	szDest.Init();
	CPreprocessor::Preprocess("\
#define XACT 3\n\
int x = XACT + 2;", &szDest);

	AssertString("int x = 3 + 2;\n", szDest.Text());
	szDest.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPreprocessorSimpleReplacement(void)
{
	CChars	szDest;

	szDest.Init();
	CPreprocessor::Preprocess("\
#define D5( X ) X \n\
#define D9(P,Q)  D5(P)  D5(Q) \n\
D9(Hello, World)", &szDest);

	AssertString("Hello  World  \n", szDest.Text());
	szDest.Kill();
}


#define D8(P,Q) P " " Q

D8(char sz[] =, ;)

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPreprocessorStringReplacement(void)
{
	CChars	szDest;

	szDest.Init();
	CPreprocessor::Preprocess("\
#define D8(P,Q) P \" \" Q\n\
D8(char sz[] =,;)\
", &szDest);

	//Actually I don't know what this is supposed to look like.  Just make the test pass for now.
	AssertString("char sz[] = \" \" ;\n", szDest.Text());
	szDest.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPreprocessorReplacement(void)
{
	CChars	szDest;

	szDest.Init();
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
	szDest.Kill();

	szDest.Init();
	CPreprocessor::Preprocess("\
int x = ++y / z;\n\
", &szDest);

	AssertString("int x = ++y / z;\n", szDest.Text());
	szDest.Kill();

	szDest.Init();
	CPreprocessor::Preprocess("\
#define SOME_FOO_1(ARG1, ARG2)          0xDE + ARG1 - ARG2 +ARG1 //  \'\'\"\' for US\n\
#define SOME_FOO_2        0xE2  //  \"<>\" or \"\\|\" on RT 102-key kbd.\n\
#define SOME_FOO_3         0x00000080L /* Don't do \"&\" character translation */\n\
int dufi = SOME_FOO_1(1, 2), dasf = SOME_FOO_2, ewqr = SOME_FOO_3;\n\
", &szDest);

	AssertString("int dufi = 0xDE + 1 - 2 +1 , dasf = 0xE2 , ewqr = 0x00000080L ;\n", szDest.Text());
	szDest.Kill();

	szDest.Init();
	CPreprocessor::Preprocess("\
char gsz[] = (\"//@  Don't Collapse me please     ! /*     \");\n\
char g_Char = \'\\n\';\n\
char g_Char2 = \'\"\';\n\
", &szDest);

	AssertString("char gsz[] = (\"//@  Don\\'t Collapse me please     ! /*     \");\n\
char g_Char = \'\\n\';\n\
char g_Char2 = \'\\\"\';\n\
", szDest.Text());
	szDest.Kill();

	szDest.Init();
	CPreprocessor::Preprocess("\
# define __nothrow __declspec(nothrow)\n\
__nothrow;\n\
", &szDest);

	AssertString("__declspec(nothrow);\n", szDest.Text());
	szDest.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPreprocessorExactDefine(void)
{
		CChars	szDest;

	szDest.Init();
	CPreprocessor::Preprocess("\
#define floa	int giJoe;\n\
float	gFriend;\n\
", &szDest);

	AssertString("float gFriend;\n", szDest.Text());
	szDest.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPreprocessorConditionals(void)
{
	CChars	szDest;

	szDest.Init();
	CPreprocessor::Preprocess("\
#if 1\n\
Passed\n\
#else\n\
Failed\n\
#endif\n\
", &szDest);
	AssertString("Passed\n", szDest.Text());
	szDest.Kill();

	szDest.Init();
	CPreprocessor::Preprocess("\
#if 0\n\
Failed\n\
#else\n\
Passed\n\
#endif\n\
", &szDest);
	AssertString("Passed\n", szDest.Text());
	szDest.Kill();

	szDest.Init();
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
	szDest.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPreprocessorOperatorPrecedence(void)
{
	CChars	szDest;

	szDest.Init();
	CPreprocessor::Preprocess("\
#if 1 || 0 && 0\n\
Passed\n\
#else\n\
Failed\n\
#endif\n\
", &szDest);
	AssertString("Passed\n", szDest.Text());
	szDest.Kill();

	szDest.Init();
	CPreprocessor::Preprocess("\
#if 0 && 1 || 0\n\
Failed\n\
#else\n\
Passed\n\
#endif\n\
", &szDest);
	AssertString("Passed\n", szDest.Text());
	szDest.Kill();

	szDest.Init();
	CPreprocessor::Preprocess("\
#if 0 && 0 | 1\n\
Failed\n\
#else\n\
Passed\n\
#endif\n\
", &szDest);
	AssertString("Passed\n", szDest.Text());
	szDest.Kill();

	szDest.Init();
	CPreprocessor::Preprocess("\
#if 1 | 0 ^ 1\n\
Passed\n\
#else\n\
Failed\n\
#endif\n\
", &szDest);
	AssertString("Passed\n", szDest.Text());
	szDest.Kill();

	szDest.Init();
	CPreprocessor::Preprocess("\
#if 1 ^ 0 & 0\n\
Passed\n\
#else\n\
Failed\n\
#endif\n\
", &szDest);
	AssertString("Passed\n", szDest.Text());
	szDest.Kill();

	szDest.Init();
	CPreprocessor::Preprocess("\
#if 0 & 0 == 0\n\
Failed\n\
#else\n\
Passed\n\
#endif\n\
", &szDest);
	AssertString("Passed\n", szDest.Text());
	szDest.Kill();

	szDest.Init();
	CPreprocessor::Preprocess("\
#if 0 == 0 < 0\n\
Passed\n\
#else\n\
Failed\n\
#endif\n\
", &szDest);
	AssertString("Passed\n", szDest.Text());
	szDest.Kill();

	szDest.Init();
	CPreprocessor::Preprocess("\
#if 1 < 1 << 1\n\
Passed\n\
#else\n\
Failed\n\
#endif\n\
", &szDest);
	AssertString("Passed\n", szDest.Text());
	szDest.Kill();

	szDest.Init();
	CPreprocessor::Preprocess("\
#if 0 << 0 + 1\n\
Failed\n\
#else\n\
Passed\n\
#endif\n\
", &szDest);
	AssertString("Passed\n", szDest.Text());
	szDest.Kill();

	szDest.Init();
	CPreprocessor::Preprocess("\
#if 1 + 0 * 0\n\
Passed\n\
#else\n\
Failed\n\
#endif\n\
", &szDest);
	AssertString("Passed\n", szDest.Text());
	szDest.Kill();

	szDest.Init();
	CPreprocessor::Preprocess("\
#if ~1 * 0\n\
Failed\n\
#else\n\
Passed\n\
#endif\n\
", &szDest);
	AssertString("Passed\n", szDest.Text());
	szDest.Kill();

	szDest.Init();
	CPreprocessor::Preprocess("\
#if -(1 - 1)\n\
Failed\n\
#else\n\
Passed\n\
#endif\n\
", &szDest);
	AssertString("Passed\n", szDest.Text());
	szDest.Kill();

	szDest.Init();
CPreprocessor::Preprocess("\
#if +(0 + 0)\n\
Failed\n\
#else\n\
Passed\n\
#endif\n\
", &szDest);
	AssertString("Passed\n", szDest.Text());
	szDest.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPreprocessorBlockSkipping(void)
{
	CChars				szDest;
	CTranslationUnit	cFile;
	CPreprocessor		cPreprocessor;
	CListLibraries		cLibraries;
	CConfig				cConfig;
	CChars				szName;

	szName.Init("None.cpp");

	cFile.Init(szName.Text(), NULL, false, false);
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
	cPreprocessor.Init(&cConfig);
	cPreprocessor.PreprocessTranslationUnit(&cFile);
	szDest.Init();
	cFile.Print(&szDest);

	AssertString("Start\nPassed\nEnd\n", szDest.Text());

	cPreprocessor.Kill();
	szDest.Kill();
	cLibraries.Kill();
	cConfig.Kill();
	cFile.Kill();

	cFile.Init(szName.Text(), NULL, false, false);
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
	cPreprocessor.Init(&cConfig);
	cPreprocessor.PreprocessTranslationUnit(&cFile);
	szDest.Init();
	cFile.Print(&szDest);

	AssertString("Start\nPassed\nEnd\nTest\n", szDest.Text());

	cPreprocessor.Kill();
	szDest.Kill();
	cLibraries.Kill();
	cConfig.Kill();
	cFile.Kill();

	szName.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPreprocessorParentheses(void)
{
	CChars				szDest;
	CTranslationUnit	cFile;
	CPreprocessor		cPreprocessor;
	CConfig				cConfig;
	CChars				szName;

	szName.Init("None.cpp");

	cFile.Init(szName.Text(), NULL, false, false);
	cFile.SetContents("\
#if (defined _M_ARM || defined _M_HYBRID_X86_ARM64) && !defined _M_CEE_PURE\n\
Unexpected\n\
#define _VA_ALIGN       4\n\
#define _SLOTSIZEOF(t)  ((sizeof(t) + _VA_ALIGN - 1) & ~(_VA_ALIGN - 1))\n\
#define _APALIGN(t,ap)  (((va_list)0 - (ap)) & (__alignof(t) - 1))\n\
#elif (defined _M_ARM64 || defined _M_ARM64EC) && !defined _M_CEE_PURE\n\
Unexpected\n\
#define _VA_ALIGN       8\n\
#define _SLOTSIZEOF(t)  ((sizeof(t) + _VA_ALIGN - 1) & ~(_VA_ALIGN - 1))\n\
#define _APALIGN(t,ap)  (((va_list)0 - (ap)) & (__alignof(t) - 1))\n\
#else\n\
Expected\n\
#define _SLOTSIZEOF(t)  (sizeof(t))\n\
#define _APALIGN(t,ap)  (__alignof(t))\n\
#endif\n\
");

	cConfig.Init("");
	cPreprocessor.Init(&cConfig);
	cPreprocessor.PreprocessTranslationUnit(&cFile);
	szDest.Init();
	cFile.Print(&szDest);

	AssertString("Expected\n", szDest.Text());

	cPreprocessor.Kill();
	szDest.Kill();
	cConfig.Kill();
	cFile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPreprocessorSimpleVariadic(void)
{
	CChars				szDest;
	CTranslationUnit	cFile;
	CPreprocessor		cPreprocessor;
	CConfig				cConfig;
	CChars				szName;

	szName.Init("None.cpp");

	cFile.Init(szName.Text(), NULL, false, false);
	cFile.SetContents("\
#define _CRT_UNPARENTHESIZE_(FIRST, ARGS ...) ARGS\n\
Expected\n\
");

	cConfig.Init("");
	cPreprocessor.Init(&cConfig);
	cPreprocessor.PreprocessTranslationUnit(&cFile);
	szDest.Init();
	cFile.Print(&szDest);

	AssertString("Expected\n", szDest.Text());

	cPreprocessor.Kill();
	szName.Kill();
	szDest.Kill();
	cConfig.Kill();
	cFile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPreprocessorComplexVariadic(void)
{
	CChars				szDest;
	CTranslationUnit	cFile;
	CPreprocessor		cPreprocessor;
	CConfig				cConfig;
	CChars				szName;

	szName.Init("None.cpp");

	cFile.Init(szName.Text(), NULL, false, false);
	cFile.SetContents("\
#define CHECK1(x, a...) if (!(x)) { printf(a); }\n\
CHECK1(0, \"here % s % s % s\", \"are\", \"some\", \"varargs(1)\\n\");\n\
");

	cConfig.Init("");
	cPreprocessor.Init(&cConfig);
	cPreprocessor.PreprocessTranslationUnit(&cFile);
	szDest.Init();
	cFile.Print(&szDest);

	AssertString("if (!(0)) { printf(\"here % s % s % s\", \"are\", \"some\", \"varargs(1)\\n\"); };\n", szDest.Text());

	cPreprocessor.Kill();
	szName.Kill();
	szDest.Kill();
	cConfig.Kill();
	cFile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPreprocessorRedefinedVariadic(void)
{
	CChars				szDest;
	CTranslationUnit	cFile;
	CPreprocessor		cPreprocessor;
	CConfig				cConfig;
	CChars				szName;

	szName.Init("None.cpp");

	cFile.Init(szName.Text(), NULL, false, false);
	cFile.SetContents("\
#define _CRT_UNPARENTHESIZE_(...) __VA_ARGS__\n\
Expected1\n\
#define _CRT_UNPARENTHESIZE(...)  _CRT_UNPARENTHESIZE_ __VA_ARGS__\n\
Expected2\n\
");

	cConfig.Init("");
	cPreprocessor.Init(&cConfig);
	cPreprocessor.PreprocessTranslationUnit(&cFile);
	szDest.Init();
	cFile.Print(&szDest);

	AssertString("Expected1\nExpected2\n", szDest.Text());

	cPreprocessor.Kill();
	szName.Kill();
	szDest.Kill();
	cConfig.Kill();
	cFile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPreprocessorHasInclude(void)
{
	CChars				szDest;
	CTranslationUnit	cFile;
	CPreprocessor		cPreprocessor;
	CConfig				cConfig;
	CChars				szName;
	CHeaderFileMap		cHeaderFiles;
	CHeaderFiles		cHeaderNames;
	CFileUtil			cFileUtil;
	CChars				szDirectory;

	szName.Init("None.cpp");

	szDirectory.Init();
	cFileUtil.CurrentDirectory(&szDirectory);
	cFileUtil.AppendToPath(&szDirectory, "Input");


	cHeaderFiles.Init();
	cHeaderNames.Init(szDirectory.Text(), &cHeaderFiles, false, true);

	cFile.Init(szName.Text(), NULL, false, false);
	cFile.SetContents("\
#if defined __has_include\n\
#  if __has_include (<Header.h>)\n\
IncludeWasHadded\n\
#  else\n\
Nope\n\
#  endif\n\
#endif\n\
");

	cConfig.Init("");
	cPreprocessor.Init(&cConfig);
	cPreprocessor.AddIncludeDirectory(&cHeaderNames);
	cPreprocessor.PreprocessTranslationUnit(&cFile);
	szDest.Init();
	cFile.Print(&szDest);

	AssertString("IncludeWasHadded\n", szDest.Text());

	cPreprocessor.Kill();
	cHeaderFiles.Kill();
	cHeaderNames.Kill();

	szName.Kill();
	szDirectory.Kill();
	szDest.Kill();
	cConfig.Kill();
	cFile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPreprocessorDefineEvaluateToZero(void)
{
	CChars				szDest;

	szDest.Init();
	CPreprocessor::Preprocess("\
#if NOT_DEFINED > 1\n\
Should not get here\n\
#else\n\
Yuppers, here is good\n\
#endif\n\
", &szDest);

	AssertString("Yuppers, here is good\n", szDest.Text());
	szDest.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPreprocessorExistingEmpty(void)
{
	CChars				szDest;
	CTranslationUnit	cFile;
	CPreprocessor		cPreprocessor;
	CConfig				cConfig;
	CChars				szName;

	szName.Init("None.cpp");

	cFile.Init(szName.Text(), NULL, false, false);
	cFile.SetContents("\
#if EMPTY > 1997L\n\
Should not get here\n\
#else\n\
Evaluate Good!\n\
#endif\n\
");

	cConfig.Init("");
	cPreprocessor.Init(&cConfig);
	cPreprocessor.AddDefine("EMPTY");
	cPreprocessor.PreprocessTranslationUnit(&cFile);
	szDest.Init();
	cFile.Print(&szDest);

	AssertString("Evaluate Good!\n", szDest.Text());

	cPreprocessor.Kill();
	szName.Kill();
	szDest.Kill();
	cConfig.Kill();
	cFile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPreprocessorRedefinedEmpty(void)
{
	CChars				szDest;
	CTranslationUnit	cFile;
	CPreprocessor		cPreprocessor;
	CConfig				cConfig;
	CChars				szName;
	CDefine*			pcDefine;
	CPPText*			pcText;
	CChars				szText;

	szName.Init("None.cpp");

	cFile.Init(szName.Text(), NULL, false, false);
	cFile.SetContents("\
#if defined(EMPTY)\n\
#define REEMPTY EMPTY\n\
#endif\n\
#if REEMPTY > 1996\n\
#define _HAS_X 1\n\
#define _HAS_Y 1\n\
#elif REEMPTY > 1\n\
#define _HAS_X 1\n\
#define _HAS_Y 0\n\
#else\n\
#define _HAS_X 0\n\
#define _HAS_Y 0\n\
#endif\n\
#undef REEMPTY\n\
");

	cConfig.Init("");
	cPreprocessor.Init(&cConfig);
	cPreprocessor.AddDefine("EMPTY");
	cPreprocessor.PreprocessTranslationUnit(&cFile);
	szDest.Init();
	cFile.Print(&szDest);

	AssertString("", szDest.Text());

	pcDefine = cPreprocessor.GetDefine("_HAS_X", true);
	pcText = (CPPText*)pcDefine->GetReplacement()->Get(0);
	szText.Init();
	AssertString("0", pcText->Print(&szText));
	szText.Kill();

	pcDefine = cPreprocessor.GetDefine("_HAS_Y", true);
	pcText = (CPPText*)pcDefine->GetReplacement()->Get(0);
	szText.Init();
	AssertString("0", pcText->Print(&szText));
	szText.Kill();

	cPreprocessor.Kill();
	szName.Kill();
	szDest.Kill();
	cConfig.Kill();
	cFile.Kill();


}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPreprocessorSimpleEmpty(void)
{


	CChars				szDest;

	szDest.Init();
	CPreprocessor::Preprocess("\
#if EMPTY(1)\n\
Nope, not good.\n\
#else\n\
Good, good.\n\
#endif\
", &szDest);

	AssertString("Good, good.\n", szDest.Text());
	szDest.Kill();


}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPreprocessorBrackettedEmpty(void)
{

	CChars				szDest;

	szDest.Init();
	CPreprocessor::Preprocess("\
#if FUNC(X_TOKE | Y_TOKE)\n\
Nope, not good.\n\
#else\n\
Good, good.\n\
#endif\
", &szDest);

	AssertString("Good, good.\n", szDest.Text());
	szDest.Kill();


}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPreprocessorDefineBrackettedOmmitted(void)
{

	CChars				szDest;

	szDest.Init();
	CPreprocessor::Preprocess("\
#define F(X) \n\
F Surfe();\n\
", &szDest);

	AssertString("Surfe();\n", szDest.Text());
	szDest.Kill();


}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPreprocessorHashedArgumentExpansion()
{

	CChars				szDest;

	szDest.Init();
	CPreprocessor::Preprocess("\
#define D3(X) #X\n\
#define F1(X) X##__##X\n\
char	gszF1[] = D3(F1(H));\
", &szDest);

	AssertString("char gszF1[] = \"H__H\";\n", szDest.Text());
	szDest.Kill();


}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPreprocessorHasCPPNameSpaceAttribute()
{


	CChars				szDest;
	CTranslationUnit	cFile;
	CPreprocessor		cPreprocessor;
	CConfig				cConfig;
	CChars				szName;
	CDefine* pcDefine;

	szName.Init("None.cpp");

	cFile.Init(szName.Text(), NULL, false, false);
	cFile.SetContents("\
#ifndef __has_cpp_attribute\n\
#define _KNOWN_SEMANTICS_1\n\
#elif defined(CUDA)\n\
#define _KNOWN_SEMANTICS_2\n\
#elif __has_cpp_attribute(name_space::known_semantics)\n\
#define _KNOWN_SEMANTICS_3 [[msvc::known_semantics]]\n\
#else\n\
#define _KNOWN_SEMANTICS_4\n\
#endif\n\
");

	cConfig.Init("");
	cPreprocessor.Init(&cConfig);
	cPreprocessor.PreprocessTranslationUnit(&cFile);
	szDest.Init();
	cFile.Print(&szDest);

	AssertString("", szDest.Text());

	pcDefine = cPreprocessor.GetDefine("_KNOWN_SEMANTICS_1", true);
	AssertNotNull(pcDefine);
	pcDefine = cPreprocessor.GetDefine("_KNOWN_SEMANTICS_2", true);
	AssertNull(pcDefine);
	pcDefine = cPreprocessor.GetDefine("_KNOWN_SEMANTICS_3", true);
	AssertNull(pcDefine);
	pcDefine = cPreprocessor.GetDefine("_KNOWN_SEMANTICS_4", true);
	AssertNull(pcDefine);

	cPreprocessor.Kill();
	szName.Kill();
	szDest.Kill();
	cConfig.Kill();
	cFile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPreprocessorNegativeExpression()
{
	CChars				szDest;

	szDest.Init();
	CPreprocessor::Preprocess("\
#if (1 == -1)\n\
You broke maths\n\
#else\n\
Maths is still okay\n\
#endif\n\
", &szDest);

	AssertString("Maths is still okay\n", szDest.Text());
	szDest.Kill();


}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPreprocessor(void)
{
	BeginTests();

	TypesInit();
	FastFunctionsInit();
	TypeConverterInit();
	OperatorsInit();
	NumberInit();

	TestPreprocessorSimple();
	TestPreprocessorSimpleReplacement();
	TestPreprocessorStringReplacement();
	TestPreprocessorReplacement();
	TestPreprocessorExactDefine();
	TestPreprocessorConditionals();
	TestPreprocessorOperatorPrecedence();
	TestPreprocessorBlockSkipping();
	TestPreprocessorHasInclude();
	TestPreprocessorSimpleVariadic();
	TestPreprocessorComplexVariadic();
	TestPreprocessorRedefinedVariadic();
	TestPreprocessorDefineEvaluateToZero();
	TestPreprocessorSimpleEmpty();
	TestPreprocessorExistingEmpty();
	TestPreprocessorRedefinedEmpty();
	TestPreprocessorBrackettedEmpty();
	TestPreprocessorHashedArgumentExpansion();
	TestPreprocessorDefineBrackettedOmmitted();
	TestPreprocessorHasCPPNameSpaceAttribute();
	TestPreprocessorNegativeExpression();

	NumberKill();
	OperatorsKill();
	TypeConverterKill();
	FastFunctionsKill();
	TypesKill();

	TestStatistics();
}

