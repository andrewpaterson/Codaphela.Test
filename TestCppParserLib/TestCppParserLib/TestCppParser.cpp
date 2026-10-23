#include "BaseLib/FastFunctions.h"
#include "BaseLib/TypeNames.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/Operators.h"
#include "CppParserLib/Preprocessor.h"
#include "CppParserLib/CppTokeniser.h"
#include "CppParserLib/CppParser.h"
#include "TestLib/Assert.h"


//A translation unit parsed from text.
struct SParsedText
{
	CTranslationUnit	cFile;
	CCPPTokeniser		cTokeniser;
	CCPPSyntaxTree		cTree;
	int					iErrors;

	bool	Init(char* szSource);
	void	Kill(void);
	char*	Print(CChars* psz);
	int		FindToken(char* szSpelling, int iOccurrence);
	CCPPSymbol*	GetSymbol(char* szSpelling, int iOccurrence);
	int		GetRole(char* szSpelling, int iOccurrence);
};


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
bool SParsedText::Init(char* szSource)
{
	CPreprocessor	cPreprocessor;
	CCPPParser		cParser;
	bool			bResult;

	cFile.Init("Parsed.cpp", NULL, false);
	cFile.SetContents(szSource);
	cPreprocessor.Init(NULL);
	bResult = cPreprocessor.PreprocessTranslationUnit(&cFile);
	cPreprocessor.Kill();

	cTokeniser.Init();
	bResult &= cTokeniser.Tokenise(cFile.GetTokens());

	cTree.Init(&cTokeniser);
	cParser.Init(&cTokeniser, &cTree);
	bResult &= cParser.Parse();
	iErrors = cParser.NumErrors();
	cParser.Kill();
	return bResult;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void SParsedText::Kill(void)
{
	cTree.Kill();
	cTokeniser.Kill();
	cFile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
char* SParsedText::Print(CChars* psz)
{
	cTree.PrettyPrint(psz);
	return psz->Text();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int SParsedText::FindToken(char* szSpelling, int iOccurrence)
{
	size					i;
	SPreprocessedToken*		psSource;

	for (i = 0; i < cTokeniser.NumTokens(); i++)
	{
		psSource = cTokeniser.GetSource(cTokeniser.Get(i));
		if (psSource->Is(szSpelling))
		{
			if (iOccurrence == 0)
			{
				return (int)i;
			}
			iOccurrence--;
		}
	}
	return -1;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CCPPSymbol* SParsedText::GetSymbol(char* szSpelling, int iOccurrence)
{
	int		iToken;

	iToken = FindToken(szSpelling, iOccurrence);
	if (iToken == -1)
	{
		return NULL;
	}
	return cTree.GetTokenSymbol(iToken)->pcSymbol;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int SParsedText::GetRole(char* szSpelling, int iOccurrence)
{
	int		iToken;

	iToken = FindToken(szSpelling, iOccurrence);
	if (iToken == -1)
	{
		return -1;
	}
	return cTree.GetTokenSymbol(iToken)->uiRole;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCppParserDeclarations(void)
{
	SParsedText		sParsed;
	CChars			sz;

	AssertTrue(sParsed.Init("\
typedef unsigned int uint;\n\
namespace N { extern \"C\" int f(int a, ...); }\n\
struct SPoint { int x, y : 3; static const int Z = 2; };\n\
enum EColour { RED = 1, GREEN = RED << 1, };\n\
void (*gpfCallback)(int);\n\
char gaszNames[2][8] = { \"A\", \"B\" };\n\
int (SPoint::*gpiMember);\n\
using namespace N;\n\
static_assert(sizeof(SPoint) > 4, \"Too small\");"));
	AssertInt(0, sParsed.iErrors);

	sz.Init();
	AssertString("\
typedef unsigned int uint;\n\
namespace N\n\
{\n\
	extern \"C\" int f(int a, ...);\n\
}\n\
struct SPoint\n\
{\n\
	int x, y : 3;\n\
	static const int Z = 2;\n\
};\n\
enum EColour\n\
{\n\
	RED = 1,\n\
	GREEN = RED << 1,\n\
};\n\
void (*gpfCallback)(int);\n\
char gaszNames[2][8] = { \"A\", \"B\" };\n\
int (SPoint::*gpiMember);\n\
using namespace N;\n\
static_assert(sizeof(SPoint) > 4, \"Too small\");\n", sParsed.Print(&sz));
	sz.Kill();

	AssertInt(CPPSK_Typedef, sParsed.GetSymbol("uint", 0)->meKind);
	AssertInt(CPPSK_Namespace, sParsed.GetSymbol("N", 0)->meKind);
	AssertInt(CPPSK_Function, sParsed.GetSymbol("f", 0)->meKind);
	AssertInt(CPPSK_Class, sParsed.GetSymbol("SPoint", 0)->meKind);
	AssertInt(CPPSK_Field, sParsed.GetSymbol("x", 0)->meKind);
	AssertInt(CPPSK_Enumerator, sParsed.GetSymbol("RED", 0)->meKind);
	AssertInt(CPPTR_Reference, sParsed.GetRole("RED", 1));
	AssertPointer(sParsed.GetSymbol("RED", 0), sParsed.GetSymbol("RED", 1));
	AssertInt(CPPSK_Variable, sParsed.GetSymbol("gpfCallback", 0)->meKind);
	AssertPointer(sParsed.GetSymbol("SPoint", 0), sParsed.GetSymbol("SPoint", 2));
	sParsed.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCppParserAmbiguities(void)
{
	SParsedText		sParsed;
	CChars			sz;

	//[stmt.ambig] and [dcl.ambig.res]: what could be a declaration is one.
	AssertTrue(sParsed.Init("\
struct T { T(int); T operator*(T); };\n\
int a, b;\n\
T f(int);\n\
void g(void)\n\
{\n\
	T(x);\n\
	a * b;\n\
	T * p;\n\
	T t(a);\n\
	T u(int);\n\
	(T)a;\n\
	(a)*b;\n\
	T(a) * T(b);\n\
}"));
	AssertInt(0, sParsed.iErrors);

	sz.Init();
	AssertString("\
struct T\n\
{\n\
	T(int);\n\
	T operator *(T);\n\
};\n\
int a, b;\n\
T f(int);\n\
void g(void)\n\
{\n\
	T (x);\n\
	a * b;\n\
	T *p;\n\
	T t(a);\n\
	T u(int);\n\
	(T)a;\n\
	(a) * b;\n\
	T(a) * T(b);\n\
}\n", sParsed.Print(&sz));
	sz.Kill();

	//T(x) declares x.  T u(int) declares a function.
	AssertInt(CPPTR_Declaration, sParsed.GetRole("x", 0));
	AssertInt(CPPSK_Variable, sParsed.GetSymbol("x", 0)->meKind);
	AssertInt(CPPSK_Variable, sParsed.GetSymbol("t", 0)->meKind);
	AssertInt(CPPSK_Function, sParsed.GetSymbol("u", 0)->meKind);
	AssertInt(CPPSK_Variable, sParsed.GetSymbol("p", 0)->meKind);
	AssertInt(CPPTR_Reference, sParsed.GetRole("a", 2));
	sParsed.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCppParserClasses(void)
{
	SParsedText		sParsed;
	CChars			sz;

	//Member function bodies see members declared after them.  [class.mem] 6
	AssertTrue(sParsed.Init("\
class CBase\n\
{\n\
public:\n\
	virtual ~CBase() {}\n\
	virtual int Get(void) = 0;\n\
protected:\n\
	int miBase;\n\
};\n\
class CDerived : public CBase\n\
{\n\
public:\n\
	CDerived() : miValue(0) {}\n\
	int Get(void) override { return miValue + miBase + Twice(); }\n\
	int Twice(void) const;\n\
private:\n\
	int miValue;\n\
};\n\
int CDerived::Twice(void) const\n\
{\n\
	return miValue * 2;\n\
}"));
	AssertInt(0, sParsed.iErrors);

	sz.Init();
	AssertString("\
class CBase\n\
{\n\
public:\n\
	virtual ~CBase()\n\
	{\n\
	}\n\
	virtual int Get(void) = 0;\n\
protected:\n\
	int miBase;\n\
};\n\
class CDerived : public CBase\n\
{\n\
public:\n\
	CDerived() : miValue(0)\n\
	{\n\
	}\n\
	int Get(void) override\n\
	{\n\
		return miValue + miBase + Twice();\n\
	}\n\
	int Twice(void) const;\n\
private:\n\
	int miValue;\n\
};\n\
int CDerived::Twice(void) const\n\
{\n\
	return miValue * 2;\n\
}\n", sParsed.Print(&sz));
	sz.Kill();

	//miValue in the constructor and Get are the member declared after them; miBase is in the base class.
	AssertNotNull(sParsed.GetSymbol("miValue", 2));
	AssertPointer(sParsed.GetSymbol("miValue", 2), sParsed.GetSymbol("miValue", 0));
	AssertPointer(sParsed.GetSymbol("miValue", 2), sParsed.GetSymbol("miValue", 1));
	AssertPointer(sParsed.GetSymbol("miValue", 2), sParsed.GetSymbol("miValue", 3));
	AssertNotNull(sParsed.GetSymbol("miBase", 0));
	AssertPointer(sParsed.GetSymbol("miBase", 0), sParsed.GetSymbol("miBase", 1));
	AssertPointer(sParsed.GetSymbol("Twice", 1), sParsed.GetSymbol("Twice", 0));
	AssertInt(CPPSK_Function, sParsed.GetSymbol("Twice", 2)->meKind);
	AssertInt(CPPSK_Class, sParsed.GetSymbol("CBase", 2)->meKind);
	sParsed.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCppParserTemplates(void)
{
	SParsedText		sParsed;
	CChars			sz;

	AssertTrue(sParsed.Init("\
template<class M> class CArray { public: M* Get(int i); M maData[4]; };\n\
template<class M> M* CArray<M>::Get(int i) { return &maData[i]; }\n\
template<> class CArray<bool> { };\n\
template class CArray<char>;\n\
template<class M, typename... Args> M* New(Args... args) { return new M(args...); }\n\
CArray<CArray<int>> gcArrays;\n\
int x = New<int>(3) != 0 && 1 > 0;\n\
bool b = sizeof(CArray<int>) >> 2 > 1;"));
	AssertInt(0, sParsed.iErrors);

	sz.Init();
	AssertString("\
template<class M>\n\
class CArray\n\
{\n\
public:\n\
	M *Get(int i);\n\
	M maData[4];\n\
};\n\
template<class M>\n\
M *CArray<M>::Get(int i)\n\
{\n\
	return &maData[i];\n\
}\n\
template<>\n\
class CArray<bool>\n\
{\n\
};\n\
template\n\
class CArray<char>;\n\
template<class M, typename... Args>\n\
M *New(Args ...args)\n\
{\n\
	return new M(args...);\n\
}\n\
CArray<CArray<int>> gcArrays;\n\
int x = New<int>(3) != 0 && 1 > 0;\n\
bool b = sizeof(CArray<int>) >> 2 > 1;\n", sParsed.Print(&sz));
	sz.Kill();

	AssertInt(CPPSK_ClassTemplate, sParsed.GetSymbol("CArray", 0)->meKind);
	AssertInt(CPPSK_TypeParameter, sParsed.GetSymbol("M", 0)->meKind);
	AssertInt(CPPSK_FunctionTemplate, sParsed.GetSymbol("New", 0)->meKind);
	AssertPointer(sParsed.GetSymbol("maData", 0), sParsed.GetSymbol("maData", 1));
	AssertPointer(sParsed.GetSymbol("Get", 0), sParsed.GetSymbol("Get", 1));
	sParsed.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCppParserStatements(void)
{
	SParsedText		sParsed;
	CChars			sz;

	AssertTrue(sParsed.Init("\
int f(int* pi, int n)\n\
{\n\
	int iTotal = 0;\n\
	for (int i = 0; i < n; i++)\n\
		iTotal += pi[i];\n\
	while (int j = n--) { if (j == 3) continue; else break; }\n\
	do { n++; } while (n < 10);\n\
	switch (n) { case 1: return 1; default: break; }\n\
	if (n > 0) goto done;\n\
done:\n\
	return iTotal ? iTotal : -1;\n\
}"));
	AssertInt(0, sParsed.iErrors);

	sz.Init();
	AssertString("\
int f(int *pi, int n)\n\
{\n\
	int iTotal = 0;\n\
	for (int i = 0; i < n; i++)\n\
		iTotal += pi[i];\n\
	while (int j = n--)\n\
	{\n\
		if (j == 3)\n\
			continue;\n\
		else\n\
			break;\n\
	}\n\
	do\n\
	{\n\
		n++;\n\
	}\n\
	while (n < 10);\n\
	switch (n)\n\
	{\n\
	case 1:\n\
		return 1;\n\
	default:\n\
		break;\n\
	}\n\
	if (n > 0)\n\
		goto done;\n\
done:\n\
	return iTotal ? iTotal : -1;\n\
}\n", sParsed.Print(&sz));
	sz.Kill();

	AssertInt(CPPSK_Parameter, sParsed.GetSymbol("pi", 1)->meKind);
	AssertInt(CPPSK_Variable, sParsed.GetSymbol("i", 2)->meKind);
	AssertInt(CPPSK_Variable, sParsed.GetSymbol("j", 1)->meKind);
	sParsed.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCppParserErrorRecovery(void)
{
	SParsedText		sParsed;
	CChars			sz;

	//A declaration that can't be parsed is kept as its tokens and parsing carries on.
	AssertFalse(sParsed.Init("\
int a = ;\n\
int b = 2;\n\
void f(void) { int c = 3 +; c++; }"));
	AssertInt(2, sParsed.iErrors);
	AssertInt(2, (int)sParsed.cTree.NumErrors());
	AssertString("Parsed.cpp (1, 9): Expected an expression. [;]", sParsed.cTree.GetError(0));
	AssertInt(sParsed.FindToken(";", 0), sParsed.cTree.GetErrorToken(0));
	AssertString("Parsed.cpp (3, 27): Expected an expression. [;]", sParsed.cTree.GetErrors()->Get(1));
	AssertInt(2, sParsed.cTree.GetErrors()->GetLine(1));

	sz.Init();
	AssertString("\
int a = ;\n\
int b = 2;\n\
void f(void)\n\
{\n\
	int c = 3 +;\n\
	c++;\n\
}\n", sParsed.Print(&sz));
	sz.Kill();
	AssertInt(CPPSK_Variable, sParsed.GetSymbol("b", 0)->meKind);
	sParsed.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCppParser(void)
{
	BeginTests();

	TypesInit();
	FastFunctionsInit();
	TypeConverterInit();
	OperatorsInit();
	NumberInit();

	TestCppParserDeclarations();
	TestCppParserAmbiguities();
	TestCppParserClasses();
	TestCppParserTemplates();
	TestCppParserStatements();
	TestCppParserErrorRecovery();

	NumberKill();
	OperatorsKill();
	TypeConverterKill();
	FastFunctionsKill();
	TypesKill();

	TestStatistics();
}

