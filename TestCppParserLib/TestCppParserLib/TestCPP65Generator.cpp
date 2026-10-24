#include <string.h>
#include <math.h>
#include "MicroprocessorLib/65C64InstructionFactory.h"
#include "TestCPP65Context.h"
#include "BaseLib/FileUtil.h"
#include "CppParserLib/Project.h"
#include "CppParserLib/CppTokeniser.h"
#include "CppParserLib/CppParser.h"
#include "CppParserLib/CPP65Generator.h"
#include "BaseLib/FastFunctions.h"
#include "BaseLib/TypeNames.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/NumberControl.h"
#include "BaseLib/FloatHelper.h"
#include "BaseLib/Quaternion.h"
#include "BaseLib/ArrayInt.h"
#include "TestLib/Assert.h"


//Short names for GCC's builtins in the test programs.
#define CPP65_BUILTINS \
	"#define Ctz(x) __builtin_ctz(x)\n" \
	"#define Clz(x) __builtin_clz(x)\n" \
	"#define Ctz64(x) __builtin_ctzll(x)\n" \
	"#define Clz64(x) __builtin_clzll(x)\n" \
	"#define PopCount(x) __builtin_popcount(x)\n" \
	"#define PopCount64(x) __builtin_popcountll(x)\n" \
	"#define Expect(x, e) __builtin_expect(x, e)\n" \
	"#define Unreachable() __builtin_unreachable()\n"


static const int32	gaiValues[] = { 0, 1, -1, 2, -2, 7, -7, 31, 100, -100, 12345, -98765, 65536, 2147483647, (int32)0x80000000 };
static const int32	gaiShifts[] = { 0, 1, 4, 15, 16, 31 };
static const int64	gaiValues64[] = { 0, 1, -1, 2, -7, 100, -98765, 2147483647, (int64)0x80000000LL, (int64)0xFFFFFFFFLL, (int64)0x100000000LL, 0x123456789ABCDEFLL, -0x123456789ABCDEFLL, 0x7FFFFFFFFFFFFFFFLL, (int64)0x8000000000000000LL };
static const int64	gaiShifts64[] = { 0, 1, 4, 31, 32, 33, 63 };


//////////////////////////////////////////////////////////////////////////
//
// The 32 bit result of a op b in C++, signed or unsigned.  Returns false if it is
// undefined (dividing by zero or INT_MIN / -1).
//
//////////////////////////////////////////////////////////////////////////
static bool TestCPP65Expected(const char* szOperator, int32 iA, int32 iB, bool bSigned, int32* piResult)
{
	uint32	uiA;
	uint32	uiB;

	uiA = (uint32)iA;
	uiB = (uint32)iB;
	if ((strcmp(szOperator, "/") == 0) || (strcmp(szOperator, "%") == 0))
	{
		if ((iB == 0) || (bSigned && (iA == (int32)0x80000000) && (iB == -1)))
		{
			return false;
		}
	}

	if (strcmp(szOperator, "+") == 0)				*piResult = (int32)(uiA + uiB);
	else if (strcmp(szOperator, "-") == 0)			*piResult = (int32)(uiA - uiB);
	else if (strcmp(szOperator, "*") == 0)			*piResult = (int32)(uiA * uiB);
	else if (strcmp(szOperator, "&") == 0)			*piResult = (int32)(uiA & uiB);
	else if (strcmp(szOperator, "|") == 0)			*piResult = (int32)(uiA | uiB);
	else if (strcmp(szOperator, "^") == 0)			*piResult = (int32)(uiA ^ uiB);
	else if (strcmp(szOperator, "<<") == 0)			*piResult = (int32)(uiA << uiB);
	else if (strcmp(szOperator, ">>") == 0)			*piResult = bSigned ? (iA >> iB) : (int32)(uiA >> uiB);
	else if (strcmp(szOperator, "/") == 0)			*piResult = bSigned ? (iA / iB) : (int32)(uiA / uiB);
	else if (strcmp(szOperator, "%") == 0)			*piResult = bSigned ? (iA % iB) : (int32)(uiA % uiB);
	else if (strcmp(szOperator, "<") == 0)			*piResult = bSigned ? (iA < iB) : (uiA < uiB);
	else if (strcmp(szOperator, "<=") == 0)			*piResult = bSigned ? (iA <= iB) : (uiA <= uiB);
	else if (strcmp(szOperator, ">") == 0)			*piResult = bSigned ? (iA > iB) : (uiA > uiB);
	else if (strcmp(szOperator, ">=") == 0)			*piResult = bSigned ? (iA >= iB) : (uiA >= uiB);
	else if (strcmp(szOperator, "==") == 0)			*piResult = iA == iB;
	else if (strcmp(szOperator, "!=") == 0)			*piResult = iA != iB;
	else if (strcmp(szOperator, "&&") == 0)			*piResult = iA && iB;
	else if (strcmp(szOperator, "||") == 0)			*piResult = iA || iB;
	else											return false;
	return true;
}


//////////////////////////////////////////////////////////////////////////
//
// Generates a program that works out a op b for every pair of values, as a value
// (Value) and as a branch (Branch), and checks each result against C++.
//
//////////////////////////////////////////////////////////////////////////
static void AssertCPP65Operator(const char* szOperator, const char* szType, bool bSigned)
{
	STestCPP65Run	sRun;
	CChars			szSource;
	const int32*	aiRight;
	size			uiValues;
	size			uiRight;
	size			uiPairs;
	size			i;
	size			j;
	size			k;
	int32			iExpected;
	bool			bShift;

	bShift = (strcmp(szOperator, "<<") == 0) || (strcmp(szOperator, ">>") == 0);
	uiValues = sizeof(gaiValues) / sizeof(int32);
	aiRight = bShift ? gaiShifts : gaiValues;
	uiRight = bShift ? sizeof(gaiShifts) / sizeof(int32) : uiValues;

	szSource.Init();
	szSource.Append("int Value(")->Append(szType)->Append(" a, ")->Append(szType)->Append(" b) { return a ")->Append(szOperator)->Append(" b; }\n");
	szSource.Append("int Branch(")->Append(szType)->Append(" a, ")->Append(szType)->Append(" b) { if (a ")->Append(szOperator)->Append(" b) return 1; return 0; }\n");

	uiPairs = 0;
	szSource.Append(szType)->Append(" gA[] = {");
	for (i = 0; i < uiValues; i++)
	{
		for (j = 0; j < uiRight; j++)
		{
			if (TestCPP65Expected(szOperator, gaiValues[i], aiRight[j], bSigned, &iExpected))
			{
				szSource.Append((int64)gaiValues[i])->Append(", ");
				uiPairs++;
			}
		}
	}
	szSource.Append("};\n")->Append(szType)->Append(" gB[] = {");
	for (i = 0; i < uiValues; i++)
	{
		for (j = 0; j < uiRight; j++)
		{
			if (TestCPP65Expected(szOperator, gaiValues[i], aiRight[j], bSigned, &iExpected))
			{
				szSource.Append((int64)aiRight[j])->Append(", ");
			}
		}
	}
	szSource.Append("};\n");
	szSource.Append("int main()\n{\n\tint* p = (int*)0x100000;\n\tfor (int i = 0; i < ")->Append((int)uiPairs)->Append("; i++)\n\t{\n");
	szSource.Append("\t\t*p++ = Value(gA[i], gB[i]);\n");
	szSource.Append("\t\t*p++ = Branch(gA[i], gB[i]);\n");
	szSource.Append("\t}\n\treturn 0;\n}\n");

	AssertTrue(TestCPP65Begin(&sRun, szSource.Text()));
	AssertTrue(TestCPP65Run(&sRun, 2000000) < 2000000);
	AssertIntHex(CPP65_STACK_TOP, TestCPP65MPU(&sRun)->GetS());

	k = 0;
	for (i = 0; i < uiValues; i++)
	{
		for (j = 0; j < uiRight; j++)
		{
			if (TestCPP65Expected(szOperator, gaiValues[i], aiRight[j], bSigned, &iExpected))
			{
				AssertInt(iExpected, (int32)sRun.pcContext->GetLong(TEST_CPP65_RESULTS + 8 * (uint32)k));
				AssertInt(iExpected != 0, (int32)sRun.pcContext->GetLong(TEST_CPP65_RESULTS + 8 * (uint32)k + 4));
				k++;
			}
		}
	}
	TestCPP65End(&sRun);
	szSource.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// The 64 bit result of a op b in C++, signed or unsigned.  Returns false if it is
// undefined (dividing by zero or INT64_MIN / -1).
//
//////////////////////////////////////////////////////////////////////////
static bool TestCPP65Expected64(const char* szOperator, int64 iA, int64 iB, bool bSigned, int64* piResult)
{
	uint64	uiA;
	uint64	uiB;

	uiA = (uint64)iA;
	uiB = (uint64)iB;
	if ((strcmp(szOperator, "/") == 0) || (strcmp(szOperator, "%") == 0))
	{
		if ((iB == 0) || (bSigned && (iA == (int64)0x8000000000000000LL) && (iB == -1)))
		{
			return false;
		}
	}

	if (strcmp(szOperator, "+") == 0)				*piResult = (int64)(uiA + uiB);
	else if (strcmp(szOperator, "-") == 0)			*piResult = (int64)(uiA - uiB);
	else if (strcmp(szOperator, "*") == 0)			*piResult = (int64)(uiA * uiB);
	else if (strcmp(szOperator, "&") == 0)			*piResult = (int64)(uiA & uiB);
	else if (strcmp(szOperator, "|") == 0)			*piResult = (int64)(uiA | uiB);
	else if (strcmp(szOperator, "^") == 0)			*piResult = (int64)(uiA ^ uiB);
	else if (strcmp(szOperator, "<<") == 0)			*piResult = (int64)(uiA << uiB);
	else if (strcmp(szOperator, ">>") == 0)			*piResult = bSigned ? (iA >> iB) : (int64)(uiA >> uiB);
	else if (strcmp(szOperator, "/") == 0)			*piResult = bSigned ? (iA / iB) : (int64)(uiA / uiB);
	else if (strcmp(szOperator, "%") == 0)			*piResult = bSigned ? (iA % iB) : (int64)(uiA % uiB);
	else if (strcmp(szOperator, "<") == 0)			*piResult = bSigned ? (iA < iB) : (uiA < uiB);
	else if (strcmp(szOperator, "<=") == 0)			*piResult = bSigned ? (iA <= iB) : (uiA <= uiB);
	else if (strcmp(szOperator, ">") == 0)			*piResult = bSigned ? (iA > iB) : (uiA > uiB);
	else if (strcmp(szOperator, ">=") == 0)			*piResult = bSigned ? (iA >= iB) : (uiA >= uiB);
	else if (strcmp(szOperator, "==") == 0)			*piResult = iA == iB;
	else if (strcmp(szOperator, "!=") == 0)			*piResult = iA != iB;
	else if (strcmp(szOperator, "&&") == 0)			*piResult = iA && iB;
	else if (strcmp(szOperator, "||") == 0)			*piResult = iA || iB;
	else											return false;
	return true;
}


//////////////////////////////////////////////////////////////////////////
//
// Appends a 64 bit value as a C++ literal.  The most negative value has no literal.
//
//////////////////////////////////////////////////////////////////////////
static void TestCPP65AppendLiteral64(CChars* psz, int64 iValue, bool bSigned)
{
	if (iValue == (int64)0x8000000000000000LL)
	{
		psz->Append("(-9223372036854775807LL - 1)");
	}
	else
	{
		psz->Append(iValue)->Append(bSigned ? "LL" : "ULL");
	}
}


//////////////////////////////////////////////////////////////////////////
//
// Generates a program that works out a op b for every pair of 64 bit values, as a
// value (Value) and as a branch (Branch), and checks each result against C++.
//
//////////////////////////////////////////////////////////////////////////
static void AssertCPP65Operator64(const char* szOperator, const char* szType, bool bSigned)
{
	STestCPP65Run	sRun;
	CChars			szSource;
	const int64*	aiRight;
	size			uiValues;
	size			uiRight;
	size			uiPairs;
	size			i;
	size			j;
	size			k;
	int64			iExpected;
	bool			bShift;
	uint64			ulliActual;

	bShift = (strcmp(szOperator, "<<") == 0) || (strcmp(szOperator, ">>") == 0);
	uiValues = sizeof(gaiValues64) / sizeof(int64);
	aiRight = bShift ? gaiShifts64 : gaiValues64;
	uiRight = bShift ? sizeof(gaiShifts64) / sizeof(int64) : uiValues;

	szSource.Init();
	szSource.Append(szType)->Append(" Value(")->Append(szType)->Append(" a, ")->Append(szType)->Append(" b) { return a ")->Append(szOperator)->Append(" b; }\n");
	szSource.Append("int Branch(")->Append(szType)->Append(" a, ")->Append(szType)->Append(" b) { if (a ")->Append(szOperator)->Append(" b) return 1; return 0; }\n");

	uiPairs = 0;
	szSource.Append(szType)->Append(" gA[] = {");
	for (i = 0; i < uiValues; i++)
	{
		for (j = 0; j < uiRight; j++)
		{
			if (TestCPP65Expected64(szOperator, gaiValues64[i], aiRight[j], bSigned, &iExpected))
			{
				TestCPP65AppendLiteral64(&szSource, gaiValues64[i], true);
				szSource.Append(", ");
				uiPairs++;
			}
		}
	}
	szSource.Append("};\n")->Append(szType)->Append(" gB[] = {");
	for (i = 0; i < uiValues; i++)
	{
		for (j = 0; j < uiRight; j++)
		{
			if (TestCPP65Expected64(szOperator, gaiValues64[i], aiRight[j], bSigned, &iExpected))
			{
				TestCPP65AppendLiteral64(&szSource, aiRight[j], true);
				szSource.Append(", ");
			}
		}
	}
	szSource.Append("};\n");
	szSource.Append("int main()\n{\n\t")->Append(szType)->Append("* p = (")->Append(szType)->Append("*)0x100000;\n\tfor (int i = 0; i < ")->Append((int)uiPairs)->Append("; i++)\n\t{\n");
	szSource.Append("\t\t*p++ = Value(gA[i], gB[i]);\n");
	szSource.Append("\t\t*p++ = Branch(gA[i], gB[i]);\n");
	szSource.Append("\t}\n\treturn 0;\n}\n");

	AssertTrue(TestCPP65Begin(&sRun, szSource.Text()));
	AssertTrue(TestCPP65Run(&sRun, 4000000) < 4000000);
	AssertIntHex(CPP65_STACK_TOP, TestCPP65MPU(&sRun)->GetS());

	k = 0;
	for (i = 0; i < uiValues; i++)
	{
		for (j = 0; j < uiRight; j++)
		{
			if (TestCPP65Expected64(szOperator, gaiValues64[i], aiRight[j], bSigned, &iExpected))
			{
				ulliActual = sRun.pcContext->GetLong(TEST_CPP65_RESULTS + 16 * (uint32)k) | ((uint64)sRun.pcContext->GetLong(TEST_CPP65_RESULTS + 16 * (uint32)k + 4) << 32);
				AssertLong(iExpected, (int64)ulliActual);
				AssertInt(iExpected != 0, (int32)sRun.pcContext->GetLong(TEST_CPP65_RESULTS + 16 * (uint32)k + 8));
				k++;
			}
		}
	}
	TestCPP65End(&sRun);
	szSource.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCPP65GeneratorAssembly(void)
{
	CChars	szAssembly;
	CChars	szErrors;

	szAssembly.Init();
	szErrors.Init();
	AssertTrue(TestCPP65Generate(&szAssembly, &szErrors, "int Add(int a, int b) { return a + b; }"));
	AssertString("", szErrors.Text());
	AssertString(
		"\t\t.section text._Add\n"
		"\t\t.global _Add\n"
		"_Add:\n"
		"\t\tpsh V\n"
		"\t\tcpy V, S\n"
		"\t\tcpy A, [9 + V]\n"
		"\t\tcpy B, [13 + V]\n"
		"\t\tadd A, B\n"
		"L1:\n"
		"\t\tpul V\n"
		"\t\tret\n"
		"\n", szAssembly.Text());
	szErrors.Kill();
	szAssembly.Kill();

	szAssembly.Init();
	szErrors.Init();
	AssertTrue(TestCPP65Generate(&szAssembly, &szErrors, "int gTotal = 5;\nvoid Count(char c) { int x = c; if (x > 3) gTotal += x; }"));
	AssertString("", szErrors.Text());
	AssertString(
		"\t\t.section text._Count\n"
		"\t\t.global _Count\n"
		"_Count:\n"
		"\t\tpsh V\n"
		"\t\tsub S, 4\n"
		"\t\tcpy V, S\n"
		"\t\twth Y, 1\n"
		"\t\tcpy Y, [13 + V]\n"
		"\t\tcpy A, Y:s\n"
		"\t\twth Y, 4\n"
		"\t\tcpy [1 + V], A\n"
		"\t\tcpy A, [1 + V]\n"
		"\t\tcpy B, 3\n"
		"\t\tcmp B, A\n"
		"\t\tbraso (n, v), L3\n"
		"\t\tbra L2\n"
		"L3:\n"
		"\t\tcpy A, [1 + V]\n"
		"\t\tcpy B, A\n"
		"\t\tcpy A, [_gTotal]\n"
		"\t\tadd A, B\n"
		"\t\tcpy [_gTotal], A\n"
		"L2:\n"
		"L1:\n"
		"\t\tadd S, 4\n"
		"\t\tpul V\n"
		"\t\tret\n"
		"\n"
		"\t\t.section data._gTotal\n"
		"\t\t.align 4\n"
		"\t\t.global _gTotal\n"
		"_gTotal:\n"
		"\t\t.long 5\n", szAssembly.Text());
	szErrors.Kill();
	szAssembly.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// The start up, the stack, arguments at their own size and pseudo registers.
//
//////////////////////////////////////////////////////////////////////////
void TestCPP65GeneratorConvention(void)
{
	CChars	szAssembly;
	CChars	szErrors;

	szAssembly.Init();
	szErrors.Init();
	AssertTrue(TestCPP65Generate(&szAssembly, &szErrors, "int main() { return 0; }", true));
	AssertString("", szErrors.Text());
	AssertTrue(szAssembly.StartsWith(
		"\t\t.section text, keep, resident\n"
		"Start:\n"
		"\t\tcpy S, $1fffff\n"
		"\t\tcpy W, 0\n"
		"\t\twtth (A, B), 4\n"
		"\t\twtth (X, Y), 4\n"
		"\t\tcpy Y, __init_start\n"
		"StartInitialise:\n"
		"\t\tcmp Y, __init_end\n"
		"\t\tbras c, StartMain\n"
		"\t\tpsh Y\n"
		"\t\tjsr [Y]\n"
		"\t\tpul Y\n"
		"\t\tadd Y, 4\n"
		"\t\tbra StartInitialise\n"
		"StartMain:\n"
		"\t\tjsr _main\n"));
	szErrors.Kill();
	szAssembly.Kill();

	//main's return address is at 001F:FFFC, the caller's V below it, then x.
	AssertIntHex(0x1FFFF4, TestCPP65Main("int main() { int x = 5; return (int)&x; }"));
	//It is in the start up, at the start of the text.
	AssertInt(1, TestCPP65Main("int main() { unsigned r = *(unsigned*)0x1FFFFC; return r > 0x10000 && r < 0x10060; }"));

	//Arguments take their own size: 1 + 2 + 4 + 1 bytes.
	AssertInt(-1 - 300 + 100000 + 200, TestCPP65Main(
		"int Sum(char a, short b, int c, unsigned char d) { return a + b + c + d; }\n"
		"int main() { return Sum(-1, -300, 100000, 200); }\n"));
	AssertInt(1, TestCPP65Main(
		"bool Odd(bool a, int b) { return a && (b & 1); }\n"
		"int main() { return Odd(5, 3) + Odd(0, 3) + Odd(true, 2); }\n"));
	AssertInt(-1000, TestCPP65Main(
		"short Twice(short s) { return s + s; }\n"
		"int main() { return Twice(Twice(-250)); }\n"));

	//Right operands are kept in pseudo registers while the left is worked out.
	szAssembly.Init();
	szErrors.Init();
	AssertTrue(TestCPP65Generate(&szAssembly, &szErrors, "int f(int a, int b) { return (a + b) * (a - b); }"));
	AssertString(
		"\t\t.section text._f\n"
		"\t\t.global _f\n"
		"_f:\n"
		"\t\tpsh V\n"
		"\t\tcpy V, S\n"
		"\t\tcpy A, [9 + V]\n"
		"\t\tcpy B, [13 + V]\n"
		"\t\tsub A, B\n"
		"\t\tcpy [0 + W], A\n"
		"\t\tcpy A, [9 + V]\n"
		"\t\tcpy B, [13 + V]\n"
		"\t\tadd A, B\n"
		"\t\tcpy B, [0 + W]\n"
		"\t\tpsh W\n"
		"\t\tcpy W, 0\n"
		"\t\tmul\n"
		"\t\tpul W\n"
		"\t\tcpy A, Y\n"
		"L1:\n"
		"\t\tpul V\n"
		"\t\tret\n"
		"\n", szAssembly.Text());
	szErrors.Kill();
	szAssembly.Kill();

	AssertInt((7 + 3) * (2 - 9) - (7 ^ 2) / (3 | 1) + ((7 << 2) - (3 >> 1)) % ((9 & 6) + 1), TestCPP65Main(
		"int f(int a, int b, int c, int d) { return (a + b) * (c - d) - (a ^ c) / (b | 1) + ((a << c) - (b >> 1)) % ((d & 6) + 1); }\n"
		"int main() { return f(7, 3, 2, 9); }\n"));
	AssertInt(3, TestCPP65Main(
		"int g(int x) { return x + 1; }\n"
		"int main() { int a = 4; int b = 5; int r = 0; if ((a + b) < (a * b)) r++; if ((a - b) > (b - a)) r += 10; if (g(a) * 2 == (a + b) + 1) r += 2; return r; }\n"));

	szAssembly.Init();
	szErrors.Init();
	AssertTrue(TestCPP65Generate(&szAssembly, &szErrors, "int g(int x);\nint f(int a) { return g(a) - (a + 1); }"));
	AssertTrue(szAssembly.Contains("psh A") && !szAssembly.Contains("+ W]"));
	szErrors.Kill();
	szAssembly.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCPP65GeneratorOperators(void)
{
	static const char*	aszOperators[] = { "+", "-", "*", "/", "%", "&", "|", "^", "<<", ">>", "<", "<=", ">", ">=", "==", "!=", "&&", "||" };
	size				i;

	for (i = 0; i < sizeof(aszOperators) / sizeof(char*); i++)
	{
		AssertCPP65Operator(aszOperators[i], "int", true);
		AssertCPP65Operator(aszOperators[i], "unsigned", false);
		AssertCPP65Operator64(aszOperators[i], "long long", true);
		AssertCPP65Operator64(aszOperators[i], "unsigned long long", false);
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCPP65GeneratorConversions(void)
{
	AssertInt(44, TestCPP65Main("int main() { return (char)300; }"));
	AssertInt(-56, TestCPP65Main("int main() { int i = 200; char c = i; return c; }"));
	AssertInt(200, TestCPP65Main("int main() { int i = 200; unsigned char c = i; return c; }"));
	AssertInt(-1, TestCPP65Main("int main() { short s = 65535; return s; }"));
	AssertInt(65535, TestCPP65Main("int main() { unsigned short s = -1; return s; }"));
	AssertInt(1, TestCPP65Main("int main() { bool b = 256; return b; }"));
	AssertInt(0, TestCPP65Main("int main() { bool b = 0; return b; }"));
	AssertInt(4, TestCPP65Main("int main() { unsigned char u = 250; u += 10; return u; }"));
	AssertInt(-128, TestCPP65Main("int main() { char c = 127; ++c; return c; }"));
	AssertInt(127, TestCPP65Main("int main() { char c = 127; return c++; }"));
	AssertInt(-3000, TestCPP65Main("int main() { short h = -1000; h *= 3; return h; }"));
	AssertInt(1, TestCPP65Main("int main() { char c = -1; unsigned u = 0xFFFFFFFF; return c == u; }"));
	AssertInt(1, TestCPP65Main("int main() { unsigned char a = 200; char b = -56; return a > b; }"));
	AssertInt(0, TestCPP65Main("int main() { unsigned a = 200; int b = -56; return a > b; }"));
	AssertInt(-16, TestCPP65Main("int main() { int r = -64; r >>= 2; return r; }"));
	AssertInt(4, TestCPP65Main("int main() { return sizeof(long); }"));
	AssertInt(20, TestCPP65Main("int main() { int a[5]; return sizeof(a); }"));
	AssertInt(6, TestCPP65Main("char gName[] = \"Hello\";\nint main() { return sizeof(gName); }"));
	AssertInt(8, TestCPP65Main("int main() { return sizeof(long long); }"));
	AssertInt(3 + 10 * 2 + 100 * 31, TestCPP65Main(
		"int Count() { static int siCalls = 0; siCalls++; return siCalls; }\n"
		"int Other() { static int siCalls = 1; return ++siCalls; }\n"
		"int Days(int i) { static const int aiDays[3] = { 31, 28, 31 }; return aiDays[i]; }\n"
		"int main() { Count(); Count(); Other(); return Count() + 10 * Other() - 10 + 100 * Days(2); }"));
	AssertInt(1 + 2 + 3 + 1 + 1000, TestCPP65Main(
		"#include <stdarg.h>\n"
		"int Sum(char n, ...) { va_list ap; va_start(ap, n); int t = 0; for (int i = 0; i < n; i++) { t += va_arg(ap, int); } va_end(ap); return t; }\n"
		"int main() { char c = 3; bool b = true; short s = 1000; return Sum(5, 1, 2, c, b, s); }"));
	AssertInt(1, TestCPP65Main(
		"#include <stdarg.h>\n"
		"long long Mix(const char* f, ...)\n"
		"{\n"
		"\tva_list ap; long long t = 0; const char* p;\n"
		"\tva_start(ap, f);\n"
		"\tfor (; *f; f++) { if (*f == 'i') t += va_arg(ap, int); else if (*f == 'l') t += va_arg(ap, long long); else { p = va_arg(ap, const char*); while (*p++) t++; } }\n"
		"\tva_end(ap);\n"
		"\treturn t;\n"
		"}\n"
		"char gText[] = \"abcd\";\n"
		"int main() { return Mix(\"ilsi\", -5, 0x100000000LL, gText, (unsigned char)200) == 0x100000000LL + 199; }"));
	AssertInt(1, TestCPP65Main(
		"int Same(const char* a, const char* b) { while (*a && (*a == *b)) { a++; b++; } return *a == *b; }\n"
		"struct CName { int Get() { return Same(__PRETTY_FUNCTION__, \"CName::Get\") && Same(__func__, \"Get\") && Same(__FUNCTION__ \".x\", \"Get.x\") && Same(__FUNCSIG__, \"CName::Get\") && Same(__FUNCDNAME__ \".x\", \"_CName__Get.x\"); } };\n"
		"int main() { CName c; return c.Get() && Same(__FUNCTION__, \"main\") && Same(\"a\" \"bc\", \"abc\") && __65C64__; }"));
	AssertInt(0 + 4 * 32 + 16 * 31, TestCPP65Main(CPP65_BUILTINS
		"int main() { return Ctz(1) + 4 * Ctz(0) + 16 * Ctz(0x80000000); }"));
	AssertInt(31 + 4 * 32 + 16 * 0 + 64 * 20, TestCPP65Main(CPP65_BUILTINS
		"int main() { return Clz(1) + 4 * Clz(0) + 16 * Clz(0x80000000) + 64 * Clz(0xFFF); }"));
	AssertInt(40 + 4 * 64 + 16 * 63, TestCPP65Main(CPP65_BUILTINS
		"int main() { return Ctz64(0x10000000000LL) + 4 * Ctz64(0) + 16 * Clz64(1); }"));
	AssertInt(0 + 4 * 1 + 16 * 32 + 64 * 12, TestCPP65Main(CPP65_BUILTINS
		"int main() { return PopCount(0) + 4 * PopCount(0x80000000) + 16 * PopCount(-1) + 64 * PopCount(0x1234567); }"));
	AssertInt(64 + 4 * 2, TestCPP65Main(CPP65_BUILTINS
		"int main() { return PopCount64(-1LL) + 4 * PopCount64(0x8000000000000001LL); }"));
	AssertInt(5, TestCPP65Main(CPP65_BUILTINS
		"int main() { int x = 5; if (Expect(x == 5, 1)) return x; Unreachable(); }"));
	AssertInt(-1, TestCPP65Main("int main() { int i = -1; long long l = i; return (int)(l >> 32); }"));
	AssertInt(0, TestCPP65Main("int main() { unsigned u = 0xFFFFFFFF; long long l = u; return (int)(l >> 32); }"));
	AssertInt(0xFFFFFF, TestCPP65Main("int main() { char c = -1; unsigned long long l = c; return (int)(l >> 40); }"));
	AssertInt(0x12345678, TestCPP65Main("int main() { long long l = 0x7654321012345678LL; return (int)l; }"));
	AssertInt(0x76543210, TestCPP65Main("int main() { long long l = 0x7654321012345678LL; return (int)(l >> 32); }"));
	AssertInt(1, TestCPP65Main("int main() { long long l = 0x100000000LL; int i = 1; return l > i && i < l && l != 0; }"));
	AssertInt(1, TestCPP65Main("int main() { long long l = 0x100000000LL; if (l) return 1; return 0; }"));
	AssertInt(1, TestCPP65Main("int main() { long long l = 0x100000000LL; bool b = l; return b; }"));
	AssertInt(2, TestCPP65Main("int main() { long long l = 0x100000000LL; l += 0xFFFFFFFF; l++; ++l; return (int)(l >> 32) + (int)l - 1; }"));
	AssertInt(1, TestCPP65Main("int main() { long long l = 0x100000000LL; long long m = l--; return (m == 0x100000000LL) && (l == 0xFFFFFFFFLL); }"));
	AssertInt(-3, TestCPP65Main("int main() { long long l = 0x300000000LL; l = -l; return (int)(l >> 32); }"));
	AssertInt(-4, TestCPP65Main("int main() { long long l = 0x300000000LL; l = ~l; return (int)(l >> 32); }"));
	AssertInt(6, TestCPP65Main("int main() { long long l = 0x300000000LL; l *= 2; l /= 0x100000000LL; return (int)l; }"));
	AssertInt(3, TestCPP65Main("long long f(long long a) { return a * 3; }\nint main() { return (int)(f(0x100000000LL) >> 32); }"));
	AssertInt(20, TestCPP65Main("int main() { long long l = 0x200000000LL; switch (l) { case 1: return 10; case 0x200000000LL: return 20; default: return 30; } }"));
	AssertInt(7, TestCPP65Main("struct D { int* p; ~D() { *p = 7; } };\nint g;\nlong long f() { D d; d.p = &g; return 0x500000000LL; }\nint main() { long long l = f(); return (l == 0x500000000LL) ? g : 0; }"));
	AssertInt(1, TestCPP65Main("int main() { long long a[3]; a[0] = 1; a[1] = 0x100000000LL; a[2] = a[0] + a[1]; long long* p = &a[2]; return *p == 0x100000001LL && sizeof(a) == 24; }"));
	AssertInt(1, TestCPP65Main("struct S { char c; long long l; int i; };\nint main() { S s; s.l = -2; s.i = 5; return s.l + s.i == 3 && sizeof(S) == 16; }"));
}


//////////////////////////////////////////////////////////////////////////
//
// A program that returns the number of the first check that fails, or 0.
//
//////////////////////////////////////////////////////////////////////////
void TestCPP65GeneratorStatements(void)
{
	AssertInt(0, TestCPP65Main(
		"enum Colour { Red, Green = 5, Blue };\n"
		"const int N = 10;\n"
		"int gTable[N];\n"
		"char gName[] = \"Hello\";\n"
		"unsigned gCount = 3;\n"
		"\n"
		"int Sum(int* p, int n)\n"
		"{\n"
		"	int s = 0;\n"
		"	for (int i = 0; i < n; i++)\n"
		"		s += p[i];\n"
		"	return s;\n"
		"}\n"
		"\n"
		"int Length(const char* s)\n"
		"{\n"
		"	int n = 0;\n"
		"	while (*s++)\n"
		"		n++;\n"
		"	return n;\n"
		"}\n"
		"\n"
		"int Classify(int x)\n"
		"{\n"
		"	switch (x)\n"
		"	{\n"
		"	case Red: return 100;\n"
		"	case Green: return 200;\n"
		"	case Blue:\n"
		"	case 7: return 300;\n"
		"	default: break;\n"
		"	}\n"
		"	return -1;\n"
		"}\n"
		"\n"
		"int main()\n"
		"{\n"
		"	int a[5] = {1, 2, 3, 4, 5};\n"
		"	int r = 0;\n"
		"	for (int i = 0; i < N; i++)\n"
		"		gTable[i] = i * i;\n"
		"	if (Sum(gTable, N) != 285) return 1;\n"
		"	if (Sum(a, 5) != 15) return 2;\n"
		"	if (Length(gName) != 5) return 3;\n"
		"	if (Length(\"abc\\n\") != 4) return 4;\n"
		"	if (Classify(5) != 200 || Classify(6) != 300 || Classify(7) != 300 || Classify(0) != 100 || Classify(9) != -1) return 5;\n"
		"	if (!(gCount > 2u)) return 6;\n"
		"	int* p = &a[1];\n"
		"	*p = 20;\n"
		"	p[1] += 10;\n"
		"	if (a[1] != 20 || a[2] != 13) return 7;\n"
		"	p++;\n"
		"	if (*p != 13 || p - a != 2) return 8;\n"
		"	r = a[0] ? 7 : 8;\n"
		"	if (r != 7) return 9;\n"
		"	r = (a[0] > 1 && Length(\"x\")) || (a[0] == 1 && !a[4]);\n"
		"	if (r != 0) return 10;\n"
		"	int k = 0;\n"
		"	do { k += 3; } while (k < 10);\n"
		"	if (k != 12) return 11;\n"
		"	for (k = 0; ; k++) { if (k == 5) break; if (k & 1) continue; r++; }\n"
		"	if (r != 3) return 12;\n"
		"	char buf[4] = \"ab\";\n"
		"	if (buf[1] != 'b' || buf[3] != 0) return 13;\n"
		"	if (gName[0] != 'H') return 14;\n"
		"	if (int z = Sum(a, 2)) { if (z != 21) return 15; } else return 16;\n"
		"	int m[3];\n"
		"	int* q = m + 3;\n"
		"	while (q != m) *--q = 9;\n"
		"	if (m[0] + m[2] != 18 || *(m + 1) != 9 || 2[m] != 9) return 17;\n"
		"	return 0;\n"
		"}\n"));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCPP65GeneratorPrograms(void)
{
	AssertInt(6765, TestCPP65Main(
		"int Fibonacci(int n)\n"
		"{\n"
		"	if (n < 2)\n"
		"		return n;\n"
		"	return Fibonacci(n - 1) + Fibonacci(n - 2);\n"
		"}\n"
		"int main() { return Fibonacci(20); }\n"));

	AssertInt(168, TestCPP65Main(
		"bool gComposite[1000];\n"
		"int main()\n"
		"{\n"
		"	int iCount = 0;\n"
		"	for (int i = 2; i < 1000; i++)\n"
		"	{\n"
		"		if (gComposite[i])\n"
		"			continue;\n"
		"		iCount++;\n"
		"		for (int j = i * i; j < 1000; j += i)\n"
		"			gComposite[j] = true;\n"
		"	}\n"
		"	return iCount;\n"
		"}\n"));

	AssertInt(4, TestCPP65Main(
		"const int N = 6;\n"
		"int gColumns[N];\n"
		"bool Safe(int iRow, int iColumn)\n"
		"{\n"
		"	for (int i = 0; i < iRow; i++)\n"
		"	{\n"
		"		int d = gColumns[i] - iColumn;\n"
		"		if (d == 0 || d == iRow - i || d == i - iRow)\n"
		"			return false;\n"
		"	}\n"
		"	return true;\n"
		"}\n"
		"int Solve(int iRow)\n"
		"{\n"
		"	if (iRow == N)\n"
		"		return 1;\n"
		"	int iSolutions = 0;\n"
		"	for (int c = 0; c < N; c++)\n"
		"	{\n"
		"		if (Safe(iRow, c))\n"
		"		{\n"
		"			gColumns[iRow] = c;\n"
		"			iSolutions += Solve(iRow + 1);\n"
		"		}\n"
		"	}\n"
		"	return iSolutions;\n"
		"}\n"
		"int main() { return Solve(0); }\n"));

	AssertInt(0, TestCPP65Main(
		"int gData[] = { 9, -3, 7, 0, 22, -15, 4, 4, 1000, -1 };\n"
		"void Sort(int* p, int n)\n"
		"{\n"
		"	for (int i = 0; i < n - 1; i++)\n"
		"		for (int j = 0; j < n - 1 - i; j++)\n"
		"			if (p[j] > p[j + 1])\n"
		"			{\n"
		"				int t = p[j];\n"
		"				p[j] = p[j + 1];\n"
		"				p[j + 1] = t;\n"
		"			}\n"
		"}\n"
		"int main()\n"
		"{\n"
		"	Sort(gData, sizeof(gData) / sizeof(int));\n"
		"	for (int i = 1; i < 10; i++)\n"
		"		if (gData[i - 1] > gData[i])\n"
		"			return i;\n"
		"	return gData[0] == -15 && gData[9] == 1000 ? 0 : 99;\n"
		"}\n"));

	AssertInt(0, TestCPP65Main(
		"void Copy(char* d, const char* s) { while ((*d++ = *s++)) {} }\n"
		"int Compare(const char* a, const char* b)\n"
		"{\n"
		"	while (*a && *a == *b) { a++; b++; }\n"
		"	return (unsigned char)*a - (unsigned char)*b;\n"
		"}\n"
		"void Reverse(char* s)\n"
		"{\n"
		"	char* e = s;\n"
		"	while (*e) e++;\n"
		"	while (s < --e) { char c = *s; *s++ = *e; *e = c; }\n"
		"}\n"
		"int main()\n"
		"{\n"
		"	char sz[16];\n"
		"	Copy(sz, \"65C64\");\n"
		"	if (Compare(sz, \"65C64\") != 0) return 1;\n"
		"	Reverse(sz);\n"
		"	if (Compare(sz, \"46C56\") != 0) return 2;\n"
		"	if (Compare(\"abc\", \"abd\") >= 0) return 3;\n"
		"	if (Compare(\"\\xFF\", \"a\") <= 0) return 4;\n"
		"	return 0;\n"
		"}\n"));

	AssertInt(111, TestCPP65Main(
		"unsigned Gcd(unsigned a, unsigned b) { while (b) { unsigned t = a % b; a = b; b = t; } return a; }\n"
		"int Collatz(int n) { int s = 0; while (n != 1) { n = (n & 1) ? 3 * n + 1 : n / 2; s++; } return s; }\n"
		"int main() { return Gcd(1071, 462) == 21 && Gcd(17, 5) == 1 ? Collatz(27) : -1; }\n"));
}


//////////////////////////////////////////////////////////////////////////
//
// Classes: fields, member functions (this in X), constructors, destructors,
// single inheritance, virtual functions, static members and overloads.
//
//////////////////////////////////////////////////////////////////////////
void TestCPP65GeneratorClasses(void)
{
	//Objects by value: arguments are copies, results are made in the caller's temporaries.
	AssertInt(1, TestCPP65Main(
		"struct SPoint { int x; int y; char c; };\n"
		"SPoint Make(int x, int y) { SPoint p; p.x = x; p.y = y; p.c = 'c'; return p; }\n"
		"int Sum(SPoint p) { int s = p.x + p.y; p.x = 1000; return s; }\n"
		"SPoint Swap(SPoint p) { int t = p.x; p.x = p.y; p.y = t; return p; }\n"
		"SPoint Twice(SPoint p) { return Swap(Swap(p)); }\n"
		"SPoint Aggregate(int i) { return { i, i * 2, 'a' }; }\n"
		"int Depth(int n) { SPoint p = Make(n, n); if (n == 0) return 0; return Make(n, 0).x + Depth(n - 1); }\n"
		"int main()\n"
		"{\n"
		"\tSPoint a = Make(3, 4); SPoint b; b = Swap(a); SPoint c(Twice(a));\n"
		"\tint i = Sum(a); int j = Make(7, 8).y; int k = Sum(Swap(Make(1, 2)));\n"
		"\treturn a.x == 3 && b.x == 4 && b.y == 3 && c.x == 3 && c.y == 4 && c.c == 'c' && i == 7 && j == 8 && k == 3 && Aggregate(5).y == 10 && Depth(10) == 55 && sizeof(SPoint) == 12;\n"
		"}\n"));

	//A class without a copy constructor whose fields have them: its bytes, then the fields' copy constructors.
	AssertInt(1, TestCPP65Main(
		"int giCopies = 0;\n"
		"struct CInner { int i; CInner() { i = 0; } CInner(const CInner& c) { i = c.i + 100; giCopies++; } };\n"
		"struct CBase { int b; CBase() { b = 0; } CBase(const CBase& c) { b = c.b + 1; giCopies++; } };\n"
		"struct CMiddle { CInner aInner[2]; char c; };\n"
		"struct COuter : CBase { int x; CMiddle sMiddle; CInner sInner; };\n"
		"COuter Copy(COuter o) { return o; }\n"
		"int main()\n"
		"{\n"
		"\tCOuter a; a.b = 5; a.x = 7; a.sMiddle.aInner[1].i = 3; a.sMiddle.c = 'q'; a.sInner.i = 9;\n"
		"\tCOuter b = Copy(a);\n"
		"\treturn b.b == 7 && b.x == 7 && b.sMiddle.aInner[1].i == 203 && b.sMiddle.aInner[0].i == 200 && b.sMiddle.c == 'q' && b.sInner.i == 209 && giCopies == 8;\n"
		"}\n"));

	//Copy constructors, destructors of temporaries and arguments, operators and a template like BaseLib's SVec3.
	//Objects made by calls and operators are made where they go (as C++17 requires), so the only copy is Dot's
	//argument.
	AssertInt(1, TestCPP65Main(
		"int giCopies = 0; int giDestroyed = 0;\n"
		"template<class M>\n"
		"class SVec\n"
		"{\n"
		"public:\n"
		"\tM x; M y;\n"
		"\tSVec() {}\n"
		"\tSVec(M x, M y) { this->x = x; this->y = y; }\n"
		"\tSVec(const SVec& v) { x = v.x; y = v.y; giCopies++; }\n"
		"\tSVec& operator = (const SVec& v) { x = v.x; y = v.y; return *this; }\n"
		"\tSVec operator + (const SVec& v) const { return SVec(x + v.x, y + v.y); }\n"
		"\tSVec operator - () const { return SVec(-x, -y); }\n"
		"\tbool operator == (const SVec& v) const { return x == v.x && y == v.y; }\n"
		"\tbool operator != (const SVec& v) const { return !(*this == v); }\n"
		"\tM Dot(SVec v) const { return x * v.x + y * v.y; }\n"
		"};\n"
		"template<class M>\n"
		"SVec<M> operator * (M f, const SVec<M>& v) { return SVec<M>(f * v.x, f * v.y); }\n"
		"struct CCounted { int i; CCounted(int i) { this->i = i; } ~CCounted() { giDestroyed += i; } int Get() { return i; } };\n"
		"CCounted MakeCounted(int i) { return CCounted(i); }\n"
		"int Take(CCounted c) { return c.i; }\n"
		"struct CShape { virtual SVec<int> Centre() { return SVec<int>(1, 1); } };\n"
		"struct CBox : CShape { int w; CBox() { w = 6; } SVec<int> Centre() { return SVec<int>(w / 2, w); } };\n"
		"SVec<int> Centre(CShape* p) { return p->Centre(); }\n"
		"int main()\n"
		"{\n"
		"\tSVec<int> a(1, 2); SVec<int> b(10, 20);\n"
		"\tSVec<int> c = a + b + a;\n"
		"\tSVec<int> d = -c;\n"
		"\tSVec<int> e = 3 * a;\n"
		"\tint iCopies = giCopies;\n"
		"\tint iDot = a.Dot(b);\n"
		"\tbool bEqual = (a + a == SVec<int>(2, 4)) && (a != b);\n"
		"\tint iGot = MakeCounted(5).Get() + Take(CCounted(7)) + Take(MakeCounted(11));\n"
		"\tCBox cBox; SVec<int> f = Centre(&cBox);\n"
		"\treturn c.x == 12 && c.y == 24 && d.x == -12 && e.y == 6 && iDot == 50 && bEqual && iGot == 23 && giDestroyed == 23 && f.x == 3 && f.y == 6 && iCopies == 0 && giCopies == 1;\n"
		"}\n"));

	//Multiple polymorphic bases: secondary vtables with thunks, overridden at two levels, and a secondary
	//base's own secondary vtable.
	AssertInt(42 + 1000 * 140 + 8 + 10 * 8 + 100000 * 3 + 7, TestCPP65Main(
		"struct CForce1 { virtual void Force1() {} };\n"
		"struct CForce2 { virtual void Force2() {} };\n"
		"struct CKill { int k; virtual int Kill() { return 1; } virtual ~CKill() {} };\n"
		"struct CName : CForce1, CForce2 { virtual int Size() { return 1; } virtual int Three() { return 3; } };\n"
		"struct CBoth : CName, CKill { int miValue; CBoth() { miValue = 40; } int Kill() override { return miValue + 2; } int Size() { return 8; } };\n"
		"struct CMore : CBoth { int Kill() { return 100 + miValue; } void Force2() {} };\n"
		"struct CLast : CForce1, CMore { int miSeven; CLast() { miSeven = 7; } int Three() { return miSeven; } };\n"
		"int Call(CKill* p) { return p->Kill(); }\n"
		"int Size(CName* p) { return p->Size(); }\n"
		"int Three(CName* p) { return p->Three(); }\n"
		"int main()\n"
		"{\n"
		"\tCBoth b; CMore m; CLast l;\n"
		"\tCBoth c = b;\n"
		"\tCForce2* pf = &m; pf->Force2();\n"
		"\treturn Call(&b) + 1000 * Call(&m) + Size(&c) + 10 * m.Size() + 100000 * Three(&b) + Three(&l) - 100000 * 0 + (Call(&l) - 140);\n"
		"}\n"));

	STestCPP65Run	sRun;
	CChars			szAssembly;
	CChars			szErrors;

	AssertInt(3914, TestCPP65Main(
		"struct Point\n"
		"{\n"
		"	int x;\n"
		"	int y;\n"
		"	int Sum() { return x + y; }\n"
		"	void Move(int dx, int dy) { x += dx; y += dy; }\n"
		"};\n"
		"\n"
		"int main()\n"
		"{\n"
		"	Point p;\n"
		"	p.x = 3;\n"
		"	p.y = 4;\n"
		"	p.Move(10, 20);\n"
		"	Point* q = &p;\n"
		"	q->Move(1, 1);\n"
		"	return q->Sum() * 100 + p.x;\n"
		"}\n"));

	//Describe is 254 for the square and 123 for the triangle.  The triangle is destroyed
	//first (~Shape logs 3), then the square (~Square logs 9, ~Shape 1).
	AssertInt(37725791, TestCPP65Main(
		"int gLog = 0;\n"
		"\n"
		"struct Shape\n"
		"{\n"
		"	int mid;\n"
		"	Shape(int id) : mid(id) {}\n"
		"	virtual int Area() { return 0; }\n"
		"	virtual int Sides() = 0;\n"
		"	virtual ~Shape() { gLog = gLog * 10 + mid; }\n"
		"	int Describe() { return Area() * 10 + Sides(); }\n"
		"};\n"
		"\n"
		"class Square : public Shape\n"
		"{\n"
		"public:\n"
		"	int mside = 2;\n"
		"	Square(int id, int side);\n"
		"	int Area() override { return mside * mside; }\n"
		"	int Sides() override { return 4; }\n"
		"	~Square() { gLog = gLog * 10 + 9; }\n"
		"};\n"
		"\n"
		"Square::Square(int id, int side) : Shape(id), mside(side) {}\n"
		"\n"
		"struct Triangle : Shape\n"
		"{\n"
		"	int mbase;\n"
		"	int mheight;\n"
		"	Triangle(int b, int h) : Shape(3) { mbase = b; mheight = h; }\n"
		"	int Area() { return mbase * mheight / 2; }\n"
		"	int Sides() { return 3; }\n"
		"};\n"
		"\n"
		"int Total(Shape* p, Shape* q) { return p->Describe() + q->Describe(); }\n"
		"\n"
		"int main()\n"
		"{\n"
		"	int r;\n"
		"	{\n"
		"		Square s(1, 5);\n"
		"		Triangle t(4, 6);\n"
		"		Shape* ps = &s;\n"
		"		r = Total(ps, &t) * 1000 + s.Describe();\n"
		"	}\n"
		"	return r * 100 + gLog;\n"
		"}\n"));

	AssertInt(0, TestCPP65Main(
		"int gOrder = 0;\n"
		"\n"
		"struct Counter\n"
		"{\n"
		"	static int sCount;\n"
		"	static int Count() { return sCount; }\n"
		"	int mvalue;\n"
		"	Counter() { mvalue = 7; sCount++; }\n"
		"	Counter(int v) { mvalue = v; sCount++; }\n"
		"	Counter(int a, int b) : mvalue(a * b) { sCount++; }\n"
		"	~Counter() { sCount--; gOrder = gOrder * 10 + mvalue % 10; }\n"
		"	Counter* Self() { return this; }\n"
		"};\n"
		"int Counter::sCount = 0;\n"
		"\n"
		"struct Node { int v; Node* next; };\n"
		"struct Pair { int a = 1; char b = 'x'; short c; };\n"
		"\n"
		"Counter gGlobal(5);\n"
		"\n"
		"int Overload(int a) { return 1; }\n"
		"int Overload(char* p) { return 2; }\n"
		"int Overload(int a, int b) { return 3; }\n"
		"\n"
		"int Find(int n)\n"
		"{\n"
		"	Counter c(n);\n"
		"	for (int i = 0; i < 10; i++)\n"
		"	{\n"
		"		Counter d(i);\n"
		"		if (i == n) return i * 100 + Counter::Count();\n"
		"		if (i > 5) break;\n"
		"	}\n"
		"	return -1;\n"
		"}\n"
		"\n"
		"int main()\n"
		"{\n"
		"	if (Counter::Count() != 1) return 1;\n"
		"	Counter a;\n"
		"	Counter b(3, 4);\n"
		"	Counter arr[3];\n"
		"	if (Counter::Count() != 6 || a.mvalue != 7 || b.mvalue != 12 || arr[2].mvalue != 7) return 2;\n"
		"	if (b.Self() != &b || b.Self()->mvalue != 12) return 3;\n"
		"	Node n3 = {3, 0};\n"
		"	Node n2 = {2, &n3};\n"
		"	Node n1 = {1, &n2};\n"
		"	if (n1.next->next->v != 3) return 4;\n"
		"	Pair p;\n"
		"	if (p.a != 1 || p.b != 'x') return 5;\n"
		"	Pair q = p;\n"
		"	q.a = 9;\n"
		"	if (q.b != 'x' || p.a != 1) return 6;\n"
		"	p = q;\n"
		"	if (p.a != 9) return 7;\n"
		"	if (Overload(1) != 1 || Overload(\"s\") != 2 || Overload(1, 2) != 3) return 8;\n"
		"	if (Find(2) != 208) return 9;\n"
		"	if (Counter::Count() != 6) return 10;\n"
		"	if (Find(8) != -1 || Counter::Count() != 6) return 11;\n"
		"	if (gGlobal.mvalue != 5) return 12;\n"
		"	return 0;\n"
		"}\n"));

	//Locals are destroyed last first at the end of their block, globals last first by
	//their R_Finalise after main.  Nothing uses gA and gB, so the linker leaves them (and
	//their constructors and destructors) out...
	AssertTrue(TestCPP65Begin(&sRun,
		"struct D\n"
		"{\n"
		"	int m;\n"
		"	D(int v) : m(v) {}\n"
		"	~D() { int* p = (int*)0x100000; *p = *p * 10 + m; }\n"
		"};\n"
		"D gA(1);\n"
		"D gB(2);\n"
		"int main() { { D x(3); D y(4); } return *(int*)0x100000; }\n"));
	AssertTrue(TestCPP65Run(&sRun, 100000) < 100000);
	AssertInt(43, (int32)TestCPP65MPU(&sRun)->GetA());
	AssertInt(43, (int32)sRun.pcContext->GetLong(TEST_CPP65_RESULTS));
	AssertIntHex(CPP65_STACK_TOP, TestCPP65MPU(&sRun)->GetS());
	TestCPP65End(&sRun);

	//...unless they are marked used.
	AssertTrue(TestCPP65Begin(&sRun,
		"struct D\n"
		"{\n"
		"	int m;\n"
		"	D(int v) : m(v) {}\n"
		"	~D() { int* p = (int*)0x100000; *p = *p * 10 + m; }\n"
		"};\n"
		"D gA __attribute__((used)) (1);\n"
		"D gB __attribute__((__used__)) (2);\n"
		"int main() { { D x(3); D y(4); } return *(int*)0x100000; }\n"));
	AssertTrue(TestCPP65Run(&sRun, 100000) < 100000);
	AssertInt(43, (int32)TestCPP65MPU(&sRun)->GetA());
	AssertInt(4321, (int32)sRun.pcContext->GetLong(TEST_CPP65_RESULTS));
	AssertIntHex(CPP65_STACK_TOP, TestCPP65MPU(&sRun)->GetS());
	TestCPP65End(&sRun);

	//A virtual call loads the vtable pointer through X and calls through the vtable.  The vtable is written
	//when an object of the class is made.
	szAssembly.Init();
	szErrors.Init();
	AssertTrue(TestCPP65Generate(&szAssembly, &szErrors, "struct A { int m; virtual int f() { return m; } };\nint Call(A* p) { return p->f(); }\nint Make() { A a; return Call(&a); }"));
	AssertString("", szErrors.Text());
	AssertTrue(szAssembly.Contains(
		"_Call:\n"
		"\t\tpsh V\n"
		"\t\tcpy V, S\n"
		"\t\tcpy A, [9 + V]\n"
		"\t\tcpy X, A\n"
		"\t\tcpy A, [0 + X]\n"
		"\t\tjsr [0 + A]\n"));
	AssertTrue(szAssembly.Contains(
		"_A__f:\n"
		"\t\tpsh V\n"
		"\t\tsub S, 4\n"
		"\t\tcpy V, S\n"
		"\t\tcpy [1 + V], X\n"
		"\t\tcpy A, [4 + X]\n"));
	AssertTrue(szAssembly.Contains(
		"_A__2:\n"
		"\t\t.long _A__f\n"));
	szErrors.Kill();
	szAssembly.Kill();

	//A field of an unnamed nested class.
	AssertInt(1, TestCPP65Main(
		"struct COuter { int a; struct { short x; int y; } sInner; char c; void Set() { a = 1; sInner.x = 2; sInner.y = 3; c = 4; } };\n"
		"int main() { COuter o; o.Set(); return o.a + o.sInner.x + o.sInner.y + o.c == 10 && sizeof(COuter) == 16; }\n"));

	//An unnamed union in a class template (like BaseLib's CStackMemory) is a different class in each instance.
	AssertInt(1, TestCPP65Main(
		"template<int I> struct CStack { union { char ac[I]; char* pc; } u; int Size() { return sizeof(u); } char* Init() { u.pc = 0; return u.ac; } int Fits(int i); };\n"
		"template<int I> int CStack<I>::Fits(int i) { short s = (short)I; return (i > I) ? -s : I * 2; }\n"
		"typedef struct { int a; } SPlain;\n"
		"template<class M> int Plain(M m) { SPlain s; s.a = (int)m; return s.a; }\n"
		"int main() { CStack<16> a; CStack<40> b; return a.Size() == 16 && b.Size() == 40 && a.Init() == (char*)&a && Plain(3) == 3 && a.Fits(17) == -16 && b.Fits(17) == 80; }\n"));
}


//////////////////////////////////////////////////////////////////////////
//
// extern declares a global without defining it, and so does extern "C" without
// braces (as if it were extern); with an initialiser, or in extern "C" { }, it is a
// definition.  A second definition would be an error.
//
//////////////////////////////////////////////////////////////////////////
void TestCPP65GeneratorExtern(void)
{
	CChars	szAssembly;
	CChars	szErrors;

	AssertInt(7 + 5 + 3 + 2, TestCPP65Main(
		"extern int gPlain;\n"
		"extern \"C\" int gCount;\n"
		"extern \"C\" int gInitialised = 5;\n"
		"extern int gExtern = 3;\n"
		"extern \"C\" { int gBraced = 2; }\n"
		"int gPlain = 0;\n"
		"int gCount = 7;\n"
		"int main() { return gCount + gInitialised + gExtern + gBraced + gPlain; }\n"));

	//Only declared: it is an external of the object, not data.
	szAssembly.Init();
	szErrors.Init();
	AssertTrue(TestCPP65Generate(&szAssembly, &szErrors, "extern \"C\" char gStart;\nint Get() { return (int)&gStart; }\n"));
	AssertString("", szErrors.Text());
	AssertFalse(szAssembly.Contains("_gStart:"));
	AssertTrue(szAssembly.Contains("cpy A, _gStart"));
	szErrors.Kill();
	szAssembly.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// BaseLib's CArrayTemplate, with the 65C64's standard headers.  The CArrayBlock
// functions it calls are in ArrayBlockStub.h.
//
//////////////////////////////////////////////////////////////////////////
void TestCPP65GeneratorArrayTemplate(void)
{
	AssertInt(268, TestCPP65MainFile("ArrayTemplateInt.cpp"));
	AssertInt(553, TestCPP65MainFile("ArrayTemplateStruct.cpp"));

	//Every member: the 40 CArrayBlock functions they call are in ArrayBlock.cpp.
	AssertInt(40, TestCPP65Assemble("#include \"BaseLib/ArrayTemplate.h\"\ntemplate class CArrayTemplate<int>;\nint main() { return 0; }\n"));
	//ArrayBlock.cpp itself compiles and assembles.  Its externals (about 30) are the functions and globals of
	//other BaseLib files and the C library; the count isn't pinned as BaseLib changes.
	AssertTrue(TestCPP65AssembleLibraryFile("BaseLib" _FS_ "ArrayBlock.cpp") > 0);
	AssertInt(40, TestCPP65Assemble("#include \"BaseLib/ArrayTemplate.h\"\nstruct SNode { SNode* psNext; char c; SNode() { psNext = 0; c = 'n'; } };\ntemplate class CArrayTemplate<SNode>;\nint main() { return 0; }\n"));
}


//////////////////////////////////////////////////////////////////////////
//
// CArrayTemplate<CTestClass> in a project of three translation units: Main.cpp,
// TestClass.cpp (CTestClass, and a function that also uses the array) and
// ArrayBlockStub.cpp (the CArrayBlock functions).  Each unit is an object; the
// inline and template functions both use are written by both, each in a COMDAT
// section, and the linker keeps the first.
//
//////////////////////////////////////////////////////////////////////////
void TestCPP65GeneratorProject(void)
{
	static const char*	aszUnits[] = { "Input/CPP65/ArrayTemplateProject/Main.cpp", "Input/CPP65/ArrayTemplateProject/TestClass.cpp", "Input/CPP65/ArrayTemplateProject/ArrayBlockStub.cpp", NULL };
	STestCPP65Run		sRun;
	CChars				szMap;

	szMap.Init();
	AssertTrue(TestCPP65BeginProject(&sRun, aszUnits, "", NULL, &szMap));
	AssertTrue(TestCPP65Run(&sRun, 1000000) < 1000000);
	AssertIntHex(CPP65_STACK_TOP, TestCPP65MPU(&sRun)->GetS());
	AssertInt(4031, (int32)TestCPP65MPU(&sRun)->GetA());
	TestCPP65End(&sRun);

	//Get is used by Main.cpp and TestClass.cpp: TestClass.cpp's copy is dropped.  No unit has global objects
	//(CTestClass::siMade is constant data), so there is no init table.
	AssertTrue(szMap.Contains("  text._CArrayTemplate__T_C10CTestClass__Get comdat text._CArrayTemplate__T_C10CTestClass__Get (TestClass.cpp)\n"));
	AssertFalse(szMap.Contains(" init "));
	szMap.Kill();
}


//The expected values below are worked out by C++ on the host and must follow IEEE 754.
//Under /fp:fast NaN comparisons (and x != x) are wrong, so the host maths is precise here.
#ifdef _MSC_VER
#pragma float_control(precise, on, push)
#endif // _MSC_VER


//////////////////////////////////////////////////////////////////////////
//
// The result of a op b in C++ for float (bDouble false) or double values given as
// bits: the result's bits for + - * and /, 0 or 1 for comparisons.
//
//////////////////////////////////////////////////////////////////////////
static uint64 TestCPP65ExpectedFloat(const char* szOperator, uint64 ulliA, uint64 ulliB, bool bDouble)
{
	volatile float	fA;
	volatile float	fB;
	volatile float	fResult;
	volatile double	dA;
	volatile double	dB;
	volatile double	dResult;
	uint32			uiA;
	uint32			uiB;
	uint32			uiResult;
	uint64			ulliResult;
	bool			bResult;

	uiA = (uint32)ulliA;
	uiB = (uint32)ulliB;
	memcpy((void*)&fA, &uiA, 4);
	memcpy((void*)&fB, &uiB, 4);
	memcpy((void*)&dA, &ulliA, 8);
	memcpy((void*)&dB, &ulliB, 8);
	fResult = 0;
	dResult = 0;
	if (strcmp(szOperator, "+") == 0)			{ fResult = fA + fB;	dResult = dA + dB; }
	else if (strcmp(szOperator, "-") == 0)		{ fResult = fA - fB;	dResult = dA - dB; }
	else if (strcmp(szOperator, "*") == 0)		{ fResult = fA * fB;	dResult = dA * dB; }
	else if (strcmp(szOperator, "/") == 0)		{ fResult = fA / fB;	dResult = dA / dB; }
	else
	{
		if (strcmp(szOperator, "<") == 0)			bResult = bDouble ? (dA < dB) : (fA < fB);
		else if (strcmp(szOperator, "<=") == 0)		bResult = bDouble ? (dA <= dB) : (fA <= fB);
		else if (strcmp(szOperator, ">") == 0)		bResult = bDouble ? (dA > dB) : (fA > fB);
		else if (strcmp(szOperator, ">=") == 0)		bResult = bDouble ? (dA >= dB) : (fA >= fB);
		else if (strcmp(szOperator, "==") == 0)		bResult = bDouble ? (dA == dB) : (fA == fB);
		else										bResult = bDouble ? (dA != dB) : (fA != fB);
		return bResult ? 1 : 0;
	}
	if (bDouble)
	{
		memcpy(&ulliResult, (void*)&dResult, 8);
		return ulliResult;
	}
	memcpy(&uiResult, (void*)&fResult, 4);
	return uiResult;
}


//////////////////////////////////////////////////////////////////////////
//
// Generates a program that works out a op b for every pair of values, as a value
// (Value) and as a branch (Branch), and checks each against C++, bit for bit.
//
//////////////////////////////////////////////////////////////////////////
static void AssertCPP65FloatOperator(const char* szOperator, bool bDouble)
{
	STestCPP65Run	sRun;
	CChars			szSource;
	const char*		szType;
	const char*		szBits;
	size			uiValues;
	size			i;
	size			j;
	uint32			uiAddress;
	uint64			ulliExpected;
	uint64			ulliActual;
	bool			bCompare;
	int				iBytes;

	static const uint64	aulliFloats[] = { 0, 0x80000000, 0x3F800000, 0xBF800000, 0x3F000000, 0x40400000, 0x3EAAAAAB, 0x000116C2, 0x00800000, 0x7F7FFFFF, 0x7F800000, 0xFF800000, 0x7FC00000, 0x7149F2CA, 0x42F6E979, 0xC0E80000, 0x00000001, 0x4B800001 };
	static const uint64	aulliDoubles[] = { 0, 0x8000000000000000ULL, 0x3FF0000000000000ULL, 0xBFF0000000000000ULL, 0x3FE0000000000000ULL, 0x4008000000000000ULL, 0x3FD5555555555555ULL, 0x0000B5E620F48000ULL, 0x0010000000000000ULL, 0x7FEFFFFFFFFFFFFFULL, 0x7FF0000000000000ULL, 0xFFF0000000000000ULL, 0x7FF8000000000000ULL, 0x46293E5939A08CEAULL, 0x405EDD2F1A9FBE77ULL, 0xC01D000000000000ULL, 0x0000000000000001ULL, 0x4340000000000001ULL };
	const uint64*		aulliValues;

	aulliValues = bDouble ? aulliDoubles : aulliFloats;
	uiValues = bDouble ? sizeof(aulliDoubles) / sizeof(uint64) : sizeof(aulliFloats) / sizeof(uint64);
	szType = bDouble ? "double" : "float";
	szBits = bDouble ? "unsigned long long" : "unsigned";
	iBytes = bDouble ? 8 : 4;
	bCompare = (strlen(szOperator) == 2) || (szOperator[0] == '<') || (szOperator[0] == '>');

	szSource.Init();
	szSource.Append(bCompare ? "int" : szType)->Append(" Value(")->Append(szType)->Append(" a, ")->Append(szType)->Append(" b) { return a ")->Append(szOperator)->Append(" b; }\n");
	szSource.Append("int Branch(")->Append(szType)->Append(" a, ")->Append(szType)->Append(" b) { if (a ")->Append(szOperator)->Append(" b) return 1; return 0; }\n");
	szSource.Append(szBits)->Append(" gauiValues[] = {");
	for (i = 0; i < uiValues; i++)
	{
		szSource.Append(aulliValues[i])->Append("ULL, ");
	}
	szSource.Append("};\n");
	szSource.Append("int main()\n{\n");
	szSource.Append("\t")->Append(szBits)->Append("* p = (")->Append(szBits)->Append("*)0x100000;\n");
	szSource.Append("\tfor (int i = 0; i < ")->Append((int)uiValues)->Append("; i++)\n\t{\n");
	szSource.Append("\t\tfor (int j = 0; j < ")->Append((int)uiValues)->Append("; j++)\n\t\t{\n");
	szSource.Append("\t\t\t")->Append(szType)->Append(" a = *(")->Append(szType)->Append("*)&gauiValues[i];\n");
	szSource.Append("\t\t\t")->Append(szType)->Append(" b = *(")->Append(szType)->Append("*)&gauiValues[j];\n");
	if (bCompare)
	{
		szSource.Append("\t\t\t*p++ = Value(a, b);\n");
	}
	else
	{
		szSource.Append("\t\t\t")->Append(szType)->Append(" r = Value(a, b);\n");
		szSource.Append("\t\t\t*p++ = *(")->Append(szBits)->Append("*)&r;\n");
	}
	szSource.Append("\t\t\t*p++ = Branch(a, b);\n");
	szSource.Append("\t\t}\n\t}\n\treturn 0;\n}\n");

	static const char*	aszUnits[] = { "Libc65/softfloat.cpp", "Libc65/softfloat.asm", NULL };
	AssertTrue(TestCPP65BeginProject(&sRun, aszUnits, "", szSource.Text()));
	AssertTrue(TestCPP65Run(&sRun, 60000000) < 60000000);
	AssertIntHex(CPP65_STACK_TOP, TestCPP65MPU(&sRun)->GetS());

	uiAddress = TEST_CPP65_RESULTS;
	for (i = 0; i < uiValues; i++)
	{
		for (j = 0; j < uiValues; j++)
		{
			ulliExpected = TestCPP65ExpectedFloat(szOperator, aulliValues[i], aulliValues[j], bDouble);
			ulliActual = sRun.pcContext->GetLong(uiAddress);
			if (bDouble)
			{
				ulliActual |= (uint64)sRun.pcContext->GetLong(uiAddress + 4) << 32;
			}
			AssertLongLongIntHex((int64)ulliExpected, ulliActual);
			uiAddress += iBytes;

			//A branch on a value is on it not being zero (a NaN is not).
			if (!bCompare)
			{
				ulliExpected = (((ulliExpected << 1) & (bDouble ? ~(uint64)0 : 0xFFFFFFFF)) != 0) ? 1 : 0;
			}
			AssertLongLongIntHex((int64)ulliExpected, (uint64)sRun.pcContext->GetLong(uiAddress) | (bDouble ? (uint64)sRun.pcContext->GetLong(uiAddress + 4) << 32 : 0));
			uiAddress += iBytes;
		}
	}
	TestCPP65End(&sRun);
	szSource.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// Converts each integer to float and double, and each double (in range) to every
// integer type and to float, on the 65C64 and in C++.
//
//////////////////////////////////////////////////////////////////////////
static void AssertCPP65FloatConversions(void)
{
	STestCPP65Run	sRun;
	CChars			szSource;
	size			i;
	uint32			uiAddress;
	volatile float	fValue;
	volatile double	dValue;
	uint32			uiBits;
	uint64			ulliBits;

	static const int64	alliIntegers[] = { 0, 1, -1, 7, -100, 16777217, -16777217, 2147483647, (int64)0x80000000LL, (int64)0xFFFFFFFFLL, 9007199254740993LL, -9007199254740993LL, 0x7FFFFFFFFFFFFFFFLL, (int64)0x8000000000000000ULL, 123456789123LL };
	static const double	adDoubles[] = { 0.0, -0.0, 0.5, -0.5, 1.9999, -1.9999, 100.75, -128.0, 127.5, 255.9, 32767.0, -32768.0, 65535.5, 2147483647.0, -2147483648.0, 4294967295.0, 1e18, -1e18, 3.4028234e38, 1e-45, 1e-300 };

	szSource.Init();
	szSource.Append("long long galliIntegers[] = {");
	for (i = 0; i < sizeof(alliIntegers) / sizeof(int64); i++)
	{
		szSource.Append((uint64)alliIntegers[i])->Append("ULL, ");
	}
	szSource.Append("};\nunsigned long long gaulliDoubles[] = {");
	for (i = 0; i < sizeof(adDoubles) / sizeof(double); i++)
	{
		memcpy(&ulliBits, &adDoubles[i], 8);
		szSource.Append(ulliBits)->Append("ULL, ");
	}
	szSource.Append("};\n");
	szSource.Append(
		"unsigned* gp = (unsigned*)0x100000;\n"
		"void Float(float f) { *gp++ = *(unsigned*)&f; }\n"
		"void Double(double d) { *gp++ = (unsigned)*(unsigned long long*)&d; *gp++ = (unsigned)(*(unsigned long long*)&d >> 32); }\n"
		"int main()\n"
		"{\n"
		"\tfor (int i = 0; i < ")->Append((int)(sizeof(alliIntegers) / sizeof(int64)))->Append("; i++)\n"
		"\t{\n"
		"\t\tlong long l = galliIntegers[i]; int n = (int)l; unsigned u = (unsigned)l; unsigned long long ul = (unsigned long long)l; short s = (short)l; unsigned char c = (unsigned char)l;\n"
		"\t\tFloat(l); Float(n); Float(u); Float(ul); Float(s); Float(c);\n"
		"\t\tDouble(l); Double(n); Double(u); Double(ul); Double(s); Double(c);\n"
		"\t}\n"
		"\tfor (int i = 0; i < ")->Append((int)(sizeof(adDoubles) / sizeof(double)))->Append("; i++)\n"
		"\t{\n"
		"\t\tdouble d = *(double*)&gaulliDoubles[i]; float f = (float)d;\n"
		"\t\tFloat(f); Double(f);\n"
		"\t\tif (d > -2147483649.0 && d < 2147483648.0) { *gp++ = (int)d; *gp++ = (int)f; } else { *gp++ = 0; *gp++ = 0; }\n"
		"\t\tif (d > -1.0 && d < 4294967296.0) { *gp++ = (unsigned)d; } else { *gp++ = 0; }\n"
		"\t\tif (d > -9.3e18 && d < 9.3e18) { long long l = (long long)d; *gp++ = (unsigned)l; *gp++ = (unsigned)(l >> 32); } else { *gp++ = 0; *gp++ = 0; }\n"
		"\t\tif (d > -129.0 && d < 128.0) { char c = (char)d; *gp++ = c; } else { *gp++ = 0; }\n"
		"\t\tif (d > -1.0 && d < 65536.0) { unsigned short s = (unsigned short)f; *gp++ = s; } else { *gp++ = 0; }\n"
		"\t}\n"
		"\treturn 0;\n"
		"}\n");

	static const char*	aszUnits[] = { "Libc65/softfloat.cpp", "Libc65/softfloat.asm", NULL };
	AssertTrue(TestCPP65BeginProject(&sRun, aszUnits, "", szSource.Text()));
	AssertTrue(TestCPP65Run(&sRun, 20000000) < 20000000);
	AssertIntHex(CPP65_STACK_TOP, TestCPP65MPU(&sRun)->GetS());

	uiAddress = TEST_CPP65_RESULTS;
	for (i = 0; i < sizeof(alliIntegers) / sizeof(int64); i++)
	{
		int64	l = alliIntegers[i];
		int32	n = (int32)l;
		uint32	u = (uint32)l;
		uint64	ul = (uint64)l;
		int16	sh = (int16)l;
		uint8	c = (uint8)l;

		fValue = (float)l;	memcpy(&uiBits, (void*)&fValue, 4);	AssertIntHex(uiBits, sRun.pcContext->GetLong(uiAddress));	uiAddress += 4;
		fValue = (float)n;	memcpy(&uiBits, (void*)&fValue, 4);	AssertIntHex(uiBits, sRun.pcContext->GetLong(uiAddress));	uiAddress += 4;
		fValue = (float)u;	memcpy(&uiBits, (void*)&fValue, 4);	AssertIntHex(uiBits, sRun.pcContext->GetLong(uiAddress));	uiAddress += 4;
		fValue = (float)ul;	memcpy(&uiBits, (void*)&fValue, 4);	AssertIntHex(uiBits, sRun.pcContext->GetLong(uiAddress));	uiAddress += 4;
		fValue = (float)sh;	memcpy(&uiBits, (void*)&fValue, 4);	AssertIntHex(uiBits, sRun.pcContext->GetLong(uiAddress));	uiAddress += 4;
		fValue = (float)c;	memcpy(&uiBits, (void*)&fValue, 4);	AssertIntHex(uiBits, sRun.pcContext->GetLong(uiAddress));	uiAddress += 4;
		dValue = (double)l;		memcpy(&ulliBits, (void*)&dValue, 8);	AssertLongLongIntHex((int64)ulliBits, (int64)(sRun.pcContext->GetLong(uiAddress) | ((uint64)sRun.pcContext->GetLong(uiAddress + 4) << 32)));	uiAddress += 8;
		dValue = (double)n;		memcpy(&ulliBits, (void*)&dValue, 8);	AssertLongLongIntHex((int64)ulliBits, (int64)(sRun.pcContext->GetLong(uiAddress) | ((uint64)sRun.pcContext->GetLong(uiAddress + 4) << 32)));	uiAddress += 8;
		dValue = (double)u;		memcpy(&ulliBits, (void*)&dValue, 8);	AssertLongLongIntHex((int64)ulliBits, (int64)(sRun.pcContext->GetLong(uiAddress) | ((uint64)sRun.pcContext->GetLong(uiAddress + 4) << 32)));	uiAddress += 8;
		dValue = (double)ul;	memcpy(&ulliBits, (void*)&dValue, 8);	AssertLongLongIntHex((int64)ulliBits, (int64)(sRun.pcContext->GetLong(uiAddress) | ((uint64)sRun.pcContext->GetLong(uiAddress + 4) << 32)));	uiAddress += 8;
		dValue = (double)sh;	memcpy(&ulliBits, (void*)&dValue, 8);	AssertLongLongIntHex((int64)ulliBits, (int64)(sRun.pcContext->GetLong(uiAddress) | ((uint64)sRun.pcContext->GetLong(uiAddress + 4) << 32)));	uiAddress += 8;
		dValue = (double)c;		memcpy(&ulliBits, (void*)&dValue, 8);	AssertLongLongIntHex((int64)ulliBits, (int64)(sRun.pcContext->GetLong(uiAddress) | ((uint64)sRun.pcContext->GetLong(uiAddress + 4) << 32)));	uiAddress += 8;
	}
	for (i = 0; i < sizeof(adDoubles) / sizeof(double); i++)
	{
		double	d = adDoubles[i];
		float	f = (float)d;
		int64	l;

		memcpy(&uiBits, &f, 4);
		AssertIntHex(uiBits, sRun.pcContext->GetLong(uiAddress));	uiAddress += 4;
		dValue = f;	memcpy(&ulliBits, (void*)&dValue, 8);	AssertLongLongIntHex((int64)ulliBits, (int64)(sRun.pcContext->GetLong(uiAddress) | ((uint64)sRun.pcContext->GetLong(uiAddress + 4) << 32)));	uiAddress += 8;
		if ((d > -2147483649.0) && (d < 2147483648.0))
		{
			AssertInt((int32)d, (int32)sRun.pcContext->GetLong(uiAddress));
			AssertInt((f >= -2147483648.0f) && (f < 2147483648.0f) ? (int32)f : (int32)0x80000000, (int32)sRun.pcContext->GetLong(uiAddress + 4));
		}
		uiAddress += 8;
		if ((d > -1.0) && (d < 4294967296.0))
		{
			AssertIntHex((uint32)d, sRun.pcContext->GetLong(uiAddress));
		}
		uiAddress += 4;
		if ((d > -9.3e18) && (d < 9.3e18))
		{
			l = (int64)d;
			AssertLongLongIntHex(l, (int64)(sRun.pcContext->GetLong(uiAddress) | ((uint64)sRun.pcContext->GetLong(uiAddress + 4) << 32)));
		}
		uiAddress += 8;
		if ((d > -129.0) && (d < 128.0))
		{
			AssertInt((int8)d, (int32)sRun.pcContext->GetLong(uiAddress));
		}
		uiAddress += 4;
		if ((d > -1.0) && (d < 65536.0))
		{
			AssertInt((uint16)f, (int32)sRun.pcContext->GetLong(uiAddress));
		}
		uiAddress += 4;
	}
	TestCPP65End(&sRun);
	szSource.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// Libc65's math.cpp on the 65C64 against the C library, bit for bit.
//
//////////////////////////////////////////////////////////////////////////
static void AssertCPP65Math(void)
{
	STestCPP65Run	sRun;
	CChars			szSource;
	size			i;
	size			j;
	uint32			uiAddress;
	uint64			ulliBits;
	uint64			aulliExpected[13];
	double			d;
	double			dInteger;
	float			f;
	int				iExponent;
	uint32			uiBits;

	static const double	adValues[] = { 0.0, -0.0, 0.25, -0.5, 0.5, 1.5, -1.5, 2.5, -2.5, 3.75, -3.75, 1e-310, -7e-320, 4503599627370495.5, -4503599627370497.0, 1e300, 123456.789, -0.7, 2.0, 1e22 };

	szSource.Init();
	szSource.Append("#include <math.h>\nunsigned long long gaulliValues[] = {");
	for (i = 0; i < sizeof(adValues) / sizeof(double); i++)
	{
		memcpy(&ulliBits, &adValues[i], 8);
		szSource.Append(ulliBits)->Append("ULL, ");
	}
	szSource.Append("};\n");
	szSource.Append(
		"unsigned long long* gp = (unsigned long long*)0x100000;\n"
		"void Put(double d) { *gp++ = *(unsigned long long*)&d; }\n"
		"int main()\n"
		"{\n"
		"\tint e; double ip;\n"
		"\tfor (int i = 0; i < ")->Append((int)(sizeof(adValues) / sizeof(double)))->Append("; i++)\n"
		"\t{\n"
		"\t\tdouble x = *(double*)&gaulliValues[i]; float f = (float)x;\n"
		"\t\tPut(fabs(x)); Put(sqrt(fabs(x))); Put(trunc(x)); Put(floor(x)); Put(ceil(x)); Put(round(x));\n"
		"\t\tPut(frexp(x, &e)); *gp++ = e; Put(ldexp(x, 10)); Put(modf(x, &ip)); Put(ip); Put(fmod(x, 0.7)); Put(fmod(x, -3.0));\n"
		"\t\t*gp++ = *(unsigned*)&f; float g = sqrtf(fabsf(f)); *gp++ = *(unsigned*)&g; g = floorf(f); *gp++ = *(unsigned*)&g;\n"
		"\t}\n"
		"\treturn 0;\n"
		"}\n");

	static const char*	aszUnits[] = { "Libc65/softfloat.cpp", "Libc65/softfloat.asm", "Libc65/math.cpp", NULL };
	AssertTrue(TestCPP65BeginProject(&sRun, aszUnits, "", szSource.Text()));
	AssertTrue(TestCPP65Run(&sRun, 60000000) < 60000000);
	AssertIntHex(CPP65_STACK_TOP, TestCPP65MPU(&sRun)->GetS());

	uiAddress = TEST_CPP65_RESULTS;
	for (i = 0; i < sizeof(adValues) / sizeof(double); i++)
	{
		d = adValues[i];
		f = (float)d;
		j = 0;
		aulliExpected[j++] = 0;
		#define CPP65_EXPECT(x)	{ volatile double dExpected = (x); memcpy(&aulliExpected[j], (void*)&dExpected, 8); j++; }
		j = 0;
		CPP65_EXPECT(fabs(d));
		CPP65_EXPECT(sqrt(fabs(d)));
		CPP65_EXPECT(trunc(d));
		CPP65_EXPECT(floor(d));
		CPP65_EXPECT(ceil(d));
		CPP65_EXPECT(round(d));
		CPP65_EXPECT(frexp(d, &iExponent));
		aulliExpected[j++] = (uint64)(int64)iExponent;
		CPP65_EXPECT(ldexp(d, 10));
		CPP65_EXPECT(modf(d, &dInteger));
		CPP65_EXPECT(dInteger);
		CPP65_EXPECT(fmod(d, 0.7));
		CPP65_EXPECT(fmod(d, -3.0));
		#undef CPP65_EXPECT
		for (j = 0; j < 13; j++)
		{
			ulliBits = sRun.pcContext->GetLong(uiAddress) | ((uint64)sRun.pcContext->GetLong(uiAddress + 4) << 32);
			if (j == 7)
			{
				//The exponent is an int.
				ulliBits = (uint64)(int64)(int32)ulliBits;
			}
			AssertLongLongIntHex((int64)aulliExpected[j], (int64)ulliBits);
			uiAddress += 8;
		}
		memcpy(&uiBits, &f, 4);
		AssertIntHex(uiBits, sRun.pcContext->GetLong(uiAddress));
		f = sqrtf(fabsf((float)d));
		memcpy(&uiBits, &f, 4);
		AssertIntHex(uiBits, sRun.pcContext->GetLong(uiAddress + 8));
		f = floorf((float)d);
		memcpy(&uiBits, &f, 4);
		AssertIntHex(uiBits, sRun.pcContext->GetLong(uiAddress + 16));
		uiAddress += 24;
	}
	TestCPP65End(&sRun);
	szSource.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// The distance in ulps between two doubles; 0 for two NaNs.
//
//////////////////////////////////////////////////////////////////////////
static uint64 TestCPP65Ulps(double dActual, double dExpected)
{
	int64	lliActual;
	int64	lliExpected;

	if ((dActual != dActual) || (dExpected != dExpected))
	{
		return ((dActual != dActual) && (dExpected != dExpected)) ? 0 : 0xFFFFFFFFFFFFFFFFULL;
	}
	memcpy(&lliActual, &dActual, 8);
	memcpy(&lliExpected, &dExpected, 8);
	lliActual = (lliActual < 0) ? (int64)0x8000000000000000ULL - lliActual : lliActual;
	lliExpected = (lliExpected < 0) ? (int64)0x8000000000000000ULL - lliExpected : lliExpected;
	return (lliActual > lliExpected) ? (uint64)(lliActual - lliExpected) : (uint64)(lliExpected - lliActual);
}


//////////////////////////////////////////////////////////////////////////
//
// math.cpp's transcendental functions on the 65C64 against the C library's long
// double ones, rounded: within an ulp.  The arguments are special values and ones
// that are hard for each function.
//
//////////////////////////////////////////////////////////////////////////
static void AssertCPP65Transcendentals(void)
{
	STestCPP65Run	sRun;
	CChars			szSource;
	size			i;
	size			j;
	uint32			uiAddress;
	uint64			ulliBits;
	double			adActual[10];
	double			adExpected[10];
	double			dX;
	double			dY;

	static const double	adValues[] =
	{
		0.0, -0.0, 1.0, -1.0, 0.5, -0.5, 2.0, 1e-310, -4e-320, 1e-8, 0.1, 0.7853981633974483, 1.5707963267948966, -3.141592653589793,
		2.356194490192345, 10.0, -100.25, 709.78, -745.0, 1e5, 524288.5, 1.2e15, -5.3193726483265414e255, 1.7976931348623157e308,
		0.999999999999, 1.0000000001, 0.1875, 0.30000000000000004, 1.0 / 0.0, -1.0 / 0.0, 0.0 / 0.0
	};
	static const double	adPowPairs[][2] =
	{
		{ 2.0, 10.0 }, { 2.0, -1074.0 }, { 2.0, 0.5 }, { 10.0, -3.0 }, { -2.0, 3.0 }, { -2.0, 4.0 }, { -2.0, 0.5 }, { 0.0, -1.0 },
		{ -0.0, -1.0 }, { -0.0, -2.0 }, { -0.0, 3.0 }, { 0.0, 0.0 }, { 0.0 / 0.0, 0.0 }, { 1.0, 0.0 / 0.0 }, { -1.0, 1.0 / 0.0 },
		{ 0.5, 1.0 / 0.0 }, { 0.5, -1.0 / 0.0 }, { 1.0 / 0.0, -2.0 }, { -1.0 / 0.0, 3.0 }, { -1.0 / 0.0, -3.0 }, { 1.6047705625191471, -32.0 },
		{ 10775875.572735816, 26.531882830247795 }, { 0.999999, 1e9 }, { 1.0000001, -1e10 }, { 123.456, 7.89 }, { 3.0, 646.0 },
		{ 2.5, -1000.0 }, { 1e-300, 0.5 }, { 7.0, 1.0 / 3.0 }
	};

	szSource.Init();
	szSource.Append("#include <math.h>\nunsigned long long gaulliValues[] = {");
	for (i = 0; i < sizeof(adValues) / sizeof(double); i++)
	{
		memcpy(&ulliBits, &adValues[i], 8);
		szSource.Append(ulliBits)->Append("ULL, ");
	}
	szSource.Append("};\nunsigned long long gaulliPairs[] = {");
	for (i = 0; i < sizeof(adPowPairs) / sizeof(adPowPairs[0]); i++)
	{
		for (j = 0; j < 2; j++)
		{
			memcpy(&ulliBits, &adPowPairs[i][j], 8);
			szSource.Append(ulliBits)->Append("ULL, ");
		}
	}
	szSource.Append("};\n");
	szSource.Append(
		"unsigned long long* gp = (unsigned long long*)0x100000;\n"
		"void Put(double d) { *gp++ = *(unsigned long long*)&d; }\n"
		"int main()\n"
		"{\n"
		"\tfor (int i = 0; i < ")->Append((int)(sizeof(adValues) / sizeof(double)))->Append("; i++)\n"
		"\t{\n"
		"\t\tdouble x = *(double*)&gaulliValues[i];\n"
		"\t\tPut(exp(x)); Put(log(x)); Put(log10(x)); Put(sin(x)); Put(cos(x)); Put(tan(x)); Put(atan(x)); Put(asin(x)); Put(acos(x)); Put(atan2(x, 0.75));\n"
		"\t}\n"
		"\tfor (int i = 0; i < ")->Append((int)(sizeof(adPowPairs) / sizeof(adPowPairs[0])))->Append("; i++)\n"
		"\t{\n"
		"\t\tdouble x = *(double*)&gaulliPairs[2 * i]; double y = *(double*)&gaulliPairs[2 * i + 1];\n"
		"\t\tPut(pow(x, y)); Put(atan2(x, y));\n"
		"\t}\n"
		"\treturn 0;\n"
		"}\n");

	static const char*	aszUnits[] = { "Libc65/softfloat.cpp", "Libc65/softfloat.asm", "Libc65/math.cpp", NULL };
	AssertTrue(TestCPP65BeginProject(&sRun, aszUnits, "", szSource.Text()));
	AssertTrue(TestCPP65Run(&sRun, 200000000) < 200000000);
	AssertIntHex(CPP65_STACK_TOP, TestCPP65MPU(&sRun)->GetS());

	uiAddress = TEST_CPP65_RESULTS;
	for (i = 0; i < sizeof(adValues) / sizeof(double); i++)
	{
		dX = adValues[i];
		adExpected[0] = (double)expl(dX);
		adExpected[1] = (double)logl(dX);
		adExpected[2] = (double)log10l(dX);
		adExpected[3] = (double)sinl(dX);
		adExpected[4] = (double)cosl(dX);
		adExpected[5] = (double)tanl(dX);
		adExpected[6] = (double)atanl(dX);
		adExpected[7] = (double)asinl(dX);
		adExpected[8] = (double)acosl(dX);
		adExpected[9] = (double)atan2l(dX, 0.75L);
		for (j = 0; j < 10; j++)
		{
			ulliBits = sRun.pcContext->GetLong(uiAddress) | ((uint64)sRun.pcContext->GetLong(uiAddress + 4) << 32);
			memcpy(&adActual[j], &ulliBits, 8);
			uiAddress += 8;
#ifndef BUILD_64
			//The 32 bit C library's sin, cos and tan lose accuracy for large arguments (by up to 20 ulps at 1e5 and
			//with no correct digits from 1e15) so they can't be the expected values there.  The 64 bit build checks them.
			if ((j >= 3) && (j <= 5) && (fabs(dX) > 1000.0))
			{
				continue;
			}
#endif // BUILD_64
			AssertTrue(TestCPP65Ulps(adActual[j], adExpected[j]) <= 1);
		}
	}
	for (i = 0; i < sizeof(adPowPairs) / sizeof(adPowPairs[0]); i++)
	{
		dX = adPowPairs[i][0];
		dY = adPowPairs[i][1];
		adExpected[0] = (double)powl(dX, dY);
		adExpected[1] = (double)atan2l(dX, dY);
		for (j = 0; j < 2; j++)
		{
			ulliBits = sRun.pcContext->GetLong(uiAddress) | ((uint64)sRun.pcContext->GetLong(uiAddress + 4) << 32);
			memcpy(&adActual[j], &ulliBits, 8);
			uiAddress += 8;
			AssertTrue(TestCPP65Ulps(adActual[j], adExpected[j]) <= 1);
		}
	}
	TestCPP65End(&sRun);
	szSource.Kill();
}


#ifdef _MSC_VER
#pragma float_control(pop)
#endif // _MSC_VER


//////////////////////////////////////////////////////////////////////////
//
// float and double, worked out by Libc65's soft float runtime.
//
//////////////////////////////////////////////////////////////////////////
void TestCPP65GeneratorFloat(void)
{
	AssertInt(7, TestCPP65MainFloat("int main() { float f = 3.5f; return (int)(f * 2.0f); }"));
	AssertInt(-3, TestCPP65MainFloat("int main() { double d = -7.0; return (int)(d / 2); }"));
	AssertInt(1, TestCPP65MainFloat("int main() { float f = 0.1f; double d = f; return d > 0.1 && f < 0.2f && f == 0.1f; }"));

	static const char*	aszOperators[] = { "+", "-", "*", "/", "<", "<=", ">", ">=", "==", "!=" };
	size				i;

	AssertCPP65FloatConversions();
	AssertCPP65Math();
	AssertCPP65Transcendentals();

	//Globals and constants: data, folded as the target would.
	AssertInt(1, TestCPP65MainFloat(
		"float gf = 1.5f; double gd = -2.25; double gs[3] = { 1, 2.5, 3.0f }; float gx = 0.1f * 3; double gy = (float)0.1 + 1e-30;\n"
		"int main() { float x = 0.1f; x = x * 3; double y = (float)0.1; y = y + 1e-30; return gf == 1.5f && gd == -2.25 && gs[0] + gs[1] + gs[2] == 6.5 && gx == x && gy == y && sizeof(long double) == 8; }"));

	//Compound assignment, increments, negation, ?:, ! and mixed integers.
	AssertInt(1, TestCPP65MainFloat(
		"int main()\n"
		"{\n"
		"\tfloat f = 1.0f; double d = 10.0; int i = 3; long long l = 5;\n"
		"\tf += 2; f *= i; f -= 0.5f; f /= 2;\n"
		"\td++; ++d; d--; d += l; d = -d;\n"
		"\tfloat g = f++; float h = --f;\n"
		"\tdouble z = 0.0; double nz = -z;\n"
		"\ti = (int)(i * 2.5);\n"
		"\treturn f == 4.25f && g == 4.25f && h == 4.25f && d == -16.0 && !z && !nz && i == 7 && (i > 0 ? 1.5 : 2) == 1.5 && (f ? 1 : 0) && (1.0f / 0.0f > 1e30);\n"
		"}\n"));

	//Through pointers, fields, arrays and parameters; varargs get doubles.
	AssertInt(1, TestCPP65MainFloat(
		"#include <stdarg.h>\n"
		"struct SPoint { char c; float x; double y; };\n"
		"double Sum(int n, ...) { va_list ap; va_start(ap, n); double t = 0; for (int i = 0; i < n; i++) { t += va_arg(ap, double); } va_end(ap); return t; }\n"
		"float Scale(float f, short s) { return f * s; }\n"
		"int main()\n"
		"{\n"
		"\tSPoint p; SPoint* pp = &p; double a[4]; float* pf = &p.x;\n"
		"\tp.x = 2.5f; pp->y = 0.25; *pf += 1; a[2] = pp->x; a[1] = p.y;\n"
		"\tfor (int i = 0; i < 4; i++) { a[i] = (i == 2) ? a[i] : i * 0.5; }\n"
		"\tpp->x++; a[3]--;\n"
		"\treturn p.x == 4.5f && a[2] == 3.5 && a[3] == 0.5 && Sum(3, 1.5f, 2.0, a[2]) == 7.0 && Scale(1.25f, -4) == -5.0f && sizeof(SPoint) == 16;\n"
		"}\n"));

	for (i = 0; i < sizeof(aszOperators) / sizeof(char*); i++)
	{
		AssertCPP65FloatOperator(aszOperators[i], false);
		AssertCPP65FloatOperator(aszOperators[i], true);
	}
}


//////////////////////////////////////////////////////////////////////////
//
// The FloatHelper results worked out natively, in the order the 65C64 stores them.
//
//////////////////////////////////////////////////////////////////////////
static CArrayInt	gaiFloatHelperResults;


static void FloatHelperFloat32(float32 f)
{
	uint32	ui;

	memcpy(&ui, &f, 4);
	gaiFloatHelperResults.Add((int)ui);
}


static void FloatHelperFloat64(float64 d)
{
	uint64	ulli;

	memcpy(&ulli, &d, 8);
	gaiFloatHelperResults.Add((int)(uint32)ulli);
	gaiFloatHelperResults.Add((int)(uint32)(ulli >> 32));
}


static void FloatHelperInteger(int i)
{
	gaiFloatHelperResults.Add(i);
}


static void FloatHelperExpected(void)
{
#define FLOAT32(x)	FloatHelperFloat32(x)
#define FLOAT64(x)	FloatHelperFloat64(x)
#define INTEGER(x)	FloatHelperInteger(x)
#include "Input/CPP65/FloatHelperProject/FloatHelperCalls.h"
#undef FLOAT32
#undef FLOAT64
#undef INTEGER
}


//////////////////////////////////////////////////////////////////////////
//
// The SQuaternion results worked out natively, in the order the 65C64 stores them.
//
//////////////////////////////////////////////////////////////////////////
static CArrayInt	gaiQuaternionResults;
static CArrayInt	gaiQuaternionIsFloat;


static void QuaternionFloat(float f)
{
	uint32	ui;

	memcpy(&ui, &f, 4);
	gaiQuaternionResults.Add((int)ui);
	gaiQuaternionIsFloat.Add(1);
}


static void QuaternionNative(SQuaternion q)
{
	QuaternionFloat(q.x);
	QuaternionFloat(q.y);
	QuaternionFloat(q.z);
	QuaternionFloat(q.w);
}


static void QuaternionInteger(int i)
{
	gaiQuaternionResults.Add(i);
	gaiQuaternionIsFloat.Add(0);
}


//////////////////////////////////////////////////////////////////////////
//
// The distance in ulps between two floats given as bits.
//
//////////////////////////////////////////////////////////////////////////
static uint64 TestCPP65FloatUlps(uint32 uiActual, uint32 uiExpected)
{
	int64	lliActual;
	int64	lliExpected;

	lliActual = (uiActual & 0x80000000) ? -(int64)(uiActual & 0x7FFFFFFF) : (int64)uiActual;
	lliExpected = (uiExpected & 0x80000000) ? -(int64)(uiExpected & 0x7FFFFFFF) : (int64)uiExpected;
	return (lliActual > lliExpected) ? (uint64)(lliActual - lliExpected) : (uint64)(lliExpected - lliActual);
}


static void QuaternionExpected(void)
{
#define QUATERNION(x)	QuaternionNative(x)
#define INTEGER(x)		QuaternionInteger((int)(x))
#include "Input/CPP65/QuaternionProject/QuaternionCalls.h"
#undef QUATERNION
#undef INTEGER
}


//////////////////////////////////////////////////////////////////////////
//
// BaseLib's SQuaternion, a value type (its objects passed and returned by value,
// with member, friend and assignment operators), on the 65C64 against natively.
//
//////////////////////////////////////////////////////////////////////////
static void AssertCPP65Quaternion(void)
{
	STestCPP65Run	sRun;
	size			i;
	uint32			uiExpected;
	uint32			uiActual;

	static const char*	aszUnits[] = { "BaseLib/Quaternion.cpp", "Libc65/softfloat.cpp", "Libc65/softfloat.asm", "Input/CPP65/QuaternionProject/Main.cpp", NULL };

	gaiQuaternionResults.Init();
	gaiQuaternionIsFloat.Init();
	QuaternionExpected();
	AssertTrue(TestCPP65BeginProject(&sRun, aszUnits, ""));
	AssertTrue(TestCPP65Run(&sRun, 20000000) < 20000000);
	AssertIntHex(CPP65_STACK_TOP, TestCPP65MPU(&sRun)->GetS());
	AssertInt((int)gaiQuaternionResults.NumElements(), (int32)TestCPP65MPU(&sRun)->GetA());
	for (i = 0; i < gaiQuaternionResults.NumElements(); i++)
	{
		uiExpected = (uint32)gaiQuaternionResults.GetValue(i);
		uiActual = sRun.pcContext->GetLong(TEST_CPP65_RESULTS + 4 * (uint32)i);
#ifndef _DEBUG
		//Release is /fp:fast, which can reorder or fuse the native float maths and move its result by an ulp.
		if (gaiQuaternionIsFloat.GetValue(i) && (TestCPP65FloatUlps(uiActual, uiExpected) <= 1))
		{
			uiExpected = uiActual;
		}
#endif // _DEBUG
		AssertIntHex(uiExpected, uiActual);
	}
	TestCPP65End(&sRun);
	gaiQuaternionIsFloat.Kill();
	gaiQuaternionResults.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// BaseLib's FloatHelper on the 65C64 against the same calls natively.  The calls
// avoid sin, cos and pow, whose last bit may differ from the C library's.
//
//////////////////////////////////////////////////////////////////////////
static void AssertCPP65FloatHelper(void)
{
	STestCPP65Run	sRun;
	size			i;

	static const char*	aszUnits[] = { "BaseLib/FloatHelper.cpp", "Libc65/softfloat.cpp", "Libc65/softfloat.asm", "Libc65/math.cpp", "Input/CPP65/FloatHelperProject/Main.cpp", NULL };

	gaiFloatHelperResults.Init();
	FloatHelperExpected();
	AssertTrue(TestCPP65BeginProject(&sRun, aszUnits, ""));
	AssertTrue(TestCPP65Run(&sRun, 20000000) < 20000000);
	AssertIntHex(CPP65_STACK_TOP, TestCPP65MPU(&sRun)->GetS());
	AssertInt((int)gaiFloatHelperResults.NumElements(), (int32)TestCPP65MPU(&sRun)->GetA());
	for (i = 0; i < gaiFloatHelperResults.NumElements(); i++)
	{
		AssertIntHex((uint32)gaiFloatHelperResults.GetValue(i), sRun.pcContext->GetLong(TEST_CPP65_RESULTS + 4 * (uint32)i));
	}
	TestCPP65End(&sRun);
	gaiFloatHelperResults.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// new and delete, of single objects and arrays, over Libc65's operator new and
// operator delete (new.cpp) and malloc.  An array of objects is constructed first to
// last and destroyed last first; deleting a null pointer does nothing; delete calls a
// virtual destructor.  Memory given back is used again.
//
//////////////////////////////////////////////////////////////////////////
void TestCPP65GeneratorNewDelete(void)
{
	static const char*	aszUnits[] = { "Libc65/new.cpp", "Libc65/stdlib.cpp", "Libc65/string.cpp", "Libc65/ctype.cpp", NULL };

	AssertInt(7, TestCPP65RunProject(aszUnits, "", 20000000, "int main() { int* p = new int(7); int r = *p; delete p; return r; }\n"));

	AssertInt(2600 + 50 + 5, TestCPP65RunProject(aszUnits, "", 20000000,
		"int giMade;\n"
		"int giGone;\n"
		"struct C { int m; C() : m(3) { giMade++; } C(int v) : m(v) { giMade++; } ~C() { giGone++; } };\n"
		"int main()\n"
		"{\n"
		"	C* p = new C(5);\n"
		"	int r = p->m;\n"
		"	delete p;\n"
		"	C* a = new C[4];\n"
		"	for (int i = 0; i < 4; i++) r += a[i].m;\n"
		"	delete[] a;\n"
		"	int* q = new int[10];\n"
		"	for (int i = 0; i < 10; i++) q[i] = i;\n"
		"	r += q[9];\n"
		"	delete[] q;\n"
		"	delete (C*)0;\n"
		"	return r * 100 + giMade * 10 + giGone;\n"
		"}\n"));

	AssertInt(321, TestCPP65RunProject(aszUnits, "", 20000000,
		"int giLog;\n"
		"struct B { virtual ~B() { giLog = giLog * 10 + 1; } };\n"
		"struct D : B { ~D() { giLog = giLog * 10 + 2; } };\n"
		"struct E { int m; E() : m(0) {} ~E() { giLog = giLog * 10 + 3; } };\n"
		"int main()\n"
		"{\n"
		"	E* e = new E[1];\n"
		"	delete[] e;\n"
		"	B* p = new D;\n"
		"	delete p;\n"
		"	return giLog;\n"
		"}\n"));

	AssertInt(1000, TestCPP65RunProject(aszUnits, "", 20000000,
		"int main()\n"
		"{\n"
		"	int n = 0;\n"
		"	for (int i = 0; i < 1000; i++) { int* p = new int[1000]; if (p) n++; delete[] p; }\n"
		"	return n;\n"
		"}\n"));
}


//////////////////////////////////////////////////////////////////////////
//
// Member templates: defined in a class and outside it, in a class and in a class
// template (using both the class's and its own parameters), deduced and explicit
// arguments, static, and called unqualified from another member.
//
//////////////////////////////////////////////////////////////////////////
void TestCPP65GeneratorMemberTemplates(void)
{
	AssertInt(1, TestCPP65Main(
		"struct CValue\n"
		"{\n"
		"\tint m;\n"
		"\tCValue() { m = 1; }\n"
		"\ttemplate<class T> T Twice(T t) { return t + t + (T)m; }\n"
		"\ttemplate<class T> T As(void) { return (T)(m + 1000); }\n"
		"\ttemplate<class T> int Size(T* p);\n"
		"\ttemplate<class T> static T Max(T a, T b) { return a > b ? a : b; }\n"
		"\tint Use(void) { return Twice(20) + Max(3, 4); }\n"
		"};\n"
		"template<class T> int CValue::Size(T* p) { return (int)sizeof(T) + m; }\n"
		"struct CDerived : CValue { int d; };\n"
		"int main()\n"
		"{\n"
		"\tCValue c;\n"
		"\tCDerived e;\n"
		"\tlong long ll = 0;\n"
		"\tchar ch = c.Twice((char)3);\n"
		"\treturn c.Twice(10) == 21 && ch == 7 && c.As<short>() == 1001 && c.Size(&ll) == 9 && c.Size(&ch) == 2 && CValue::Max(5, 2) == 5 && c.Use() == 45 && e.Twice(4) == 9;\n"
		"}\n"));

	AssertInt(1, TestCPP65Main(
		"template<class M>\n"
		"struct SBox\n"
		"{\n"
		"\tM m;\n"
		"\tSBox(M v) { m = v; }\n"
		"\ttemplate<class N> M Add(N n) { return m + (M)n; }\n"
		"\ttemplate<class N> N Mul(N n);\n"
		"\ttemplate<class N> SBox<N> Convert(void) { return SBox<N>((N)m); }\n"
		"};\n"
		"template<class M> template<class N> N SBox<M>::Mul(N n) { return (N)m * n; }\n"
		"int main()\n"
		"{\n"
		"\tSBox<int> a(5);\n"
		"\tSBox<char> b(2);\n"
		"\tSBox<short> c = a.Convert<short>();\n"
		"\treturn a.Add((char)3) == 8 && b.Add(300) == 46 && a.Mul(7) == 35 && b.Mul((short)1000) == 2000 && c.m == 5 && sizeof(c) == 2;\n"
		"}\n"));
}


//////////////////////////////////////////////////////////////////////////
//
// Explicit and partial specialisations of class templates (of pointers, const,
// instances of another template and constants, with a member defined outside a
// partial specialisation) and explicit specialisations of function templates
// (with explicit and deduced arguments).
//
//////////////////////////////////////////////////////////////////////////
void TestCPP65GeneratorSpecialisation(void)
{
	AssertInt(1, TestCPP65Main(
		"template<class T> struct SAlign { int Get() { return 10; } };\n"
		"template<class T> struct SAlign<T*> { int Get(); int Base() { SAlign<T> s; return s.Get(); } };\n"
		"template<class T> int SAlign<T*>::Get() { return 20; }\n"
		"template<class T> struct SAlign<const T> { int Get() { return 30; } };\n"
		"template<> struct SAlign<char> { int Get() { return 40; } };\n"
		"template<int N> struct SFactorial { int Get() { SFactorial<N - 1> s; return N * s.Get(); } };\n"
		"template<> struct SFactorial<0> { int Get() { return 1; } };\n"
		"template<class T> struct SBox { T t; };\n"
		"template<class T> struct SAlign<SBox<T> > { int Get() { SAlign<T> s; return 50 + s.Get(); } };\n"
		"template<class T> int Size(T t) { return 100; }\n"
		"template<> int Size<char>(char t) { return 200; }\n"
		"template<> int Size(short t) { return 300; }\n"
		"int main()\n"
		"{\n"
		"\tSAlign<int> a; SAlign<int*> b; SAlign<char> c; SAlign<const int> d; SAlign<char*> e; SAlign<SBox<char> > f; SFactorial<5> g;\n"
		"\treturn a.Get() == 10 && b.Get() == 20 && c.Get() == 40 && d.Get() == 30 && e.Base() == 40 && f.Get() == 90 && g.Get() == 120 && Size(1) == 100 && Size('c') == 200 && Size((short)1) == 300 && sizeof(SAlign<int*>) == 1;\n"
		"}\n"));
}


//////////////////////////////////////////////////////////////////////////
//
// Pointers to member functions and fields: &Class::member (also with the class a
// template parameter and a member of a base), casts between them, and calls and
// accesses with .* and ->*.
//
//////////////////////////////////////////////////////////////////////////
void TestCPP65GeneratorMemberPointers(void)
{
	AssertInt(1, TestCPP65Main(
		"struct SIO { int miBase; };\n"
		"class CFile;\n"
		"struct CNumber\n"
		"{\n"
		"\tint\t\tx;\n"
		"\tint\t\ty;\n"
		"\tbool\tSave(CFile* p) { return x == 7; }\n"
		"\tint\t\tAdd(int a, int b) { return x + y + a + b; }\n"
		"};\n"
		"typedef bool (SIO::*FWriter)(CFile*);\n"
		"template<class Class>\n"
		"FWriter GetWriter(void)\n"
		"{\n"
		"\tbool (Class::* f)(CFile*);\n"
		"\tf = &Class::Save;\n"
		"\treturn (FWriter)f;\n"
		"}\n"
		"int main()\n"
		"{\n"
		"\tCNumber n; n.x = 7; n.y = 3;\n"
		"\tint CNumber::* pm = &CNumber::y;\n"
		"\tint (CNumber::* pa)(int, int) = &CNumber::Add;\n"
		"\tCNumber* p = &n;\n"
		"\tFWriter fw = GetWriter<CNumber>();\n"
		"\tbool b = (((SIO*)p)->*fw)((CFile*)0);\n"
		"\tn.*pm = 5;\n"
		"\treturn b && (p->*pm) == 5 && (n.*pa)(1, 2) == 15 && (p->*pa)(10, 20) == 42 && sizeof(pm) == 4;\n"
		"}\n"));
}


//////////////////////////////////////////////////////////////////////////
//
// Function templates with a parameter pack, forwarded with args... to a call, with
// packs of zero, one and three types.
//
//////////////////////////////////////////////////////////////////////////
void TestCPP65GeneratorVariadicTemplates(void)
{
	AssertInt(1, TestCPP65Main(
		"struct CThing\n"
		"{\n"
		"\tint\tm;\n"
		"\tvoid Init(void) { m = 1; }\n"
		"\tvoid Init(int a) { m = a; }\n"
		"\tvoid Init(int a, char b, int* c) { m = a + b + *c; }\n"
		"};\n"
		"template <class SpecificClass, class SuperClass, typename ... Args>\n"
		"SuperClass* Make(SpecificClass* p, Args ... args)\n"
		"{\n"
		"\tp->Init(args...);\n"
		"\treturn p;\n"
		"}\n"
		"template <typename ... Args>\n"
		"int Count(Args ... args) { return 7; }\n"
		"int main()\n"
		"{\n"
		"\tCThing a, b, c; int i = 100;\n"
		"\tMake<CThing, CThing>(&a);\n"
		"\tMake<CThing, CThing>(&b, 5);\n"
		"\tMake<CThing, CThing>(&c, 10, (char)2, &i);\n"
		"\treturn a.m == 1 && b.m == 5 && c.m == 112 && Count() == 7 && Count(1, 2.0, \"x\") == 7;\n"
		"}\n"));
}


//////////////////////////////////////////////////////////////////////////
//
// Overloads are chosen by the best conversion of each argument: exact, then
// promotion (char and short to int, an enum to int), then conversion.  An enum is a
// type of its own.  A cast to a pointer to a function chooses an overloaded
// function.
//
//////////////////////////////////////////////////////////////////////////
void TestCPP65GeneratorOverloadRanking(void)
{
	AssertInt(1, TestCPP65Main(
		"int F(int i) { return 1; }\n"
		"int F(unsigned int u) { return 2; }\n"
		"int F(long long l) { return 3; }\n"
		"int F(char c) { return 4; }\n"
		"enum EColour { Red, Green };\n"
		"int G(int i) { return 10; }\n"
		"int G(EColour e) { return 20; }\n"
		"int H(int i, EColour e) { return 30; }\n"
		"int H(int i, int j) { return 40; }\n"
		"void Convert(void* pvDest, void* pvSource) { *(int*)pvDest = 1; }\n"
		"void Convert(int* piDest, char* pcSource) { *piDest = 2; }\n"
		"typedef void (*FConvert)(void*, void*);\n"
		"int main()\n"
		"{\n"
		"\tFConvert f = (FConvert)&Convert;\n"
		"\tint i = 0;\n"
		"\tf(&i, &i);\n"
		"\treturn F((short)1) == 1 && F((unsigned short)1) == 1 && F('c') == 4 && F(1u) == 2 && F(2LL) == 3 && G(1) == 10 && G(Green) == 20 && G((int)Red) == 10 && H(1, Green) == 30 && H(1, 2) == 40 && i == 1;\n"
		"}\n"));
}


//////////////////////////////////////////////////////////////////////////
//
// Constructs BaseLib uses: local classes (and a local unnamed union), a member
// defined with its class named twice, anonymous unions, calls through fields that
// point to functions, addresses of function template instances, non-type template
// arguments passed to a base class, and __builtin_alloca.
//
//////////////////////////////////////////////////////////////////////////
void TestCPP65GeneratorBaseLibConstructs(void)
{
	AssertInt(1, TestCPP65Main(
		"struct CNumber { int a; int b; };\n"
		"#define UNumber(p, q) union { CNumber c; char a[p + q + 8]; }\n"
		"int Local(int x)\n"
		"{\n"
		"\tstruct SPoint { int x; int y; int Sum() { return x + y; } };\n"
		"\tSPoint p; p.x = x; p.y = 2;\n"
		"\tUNumber(4, 4) u;\n"
		"\tu.c.a = 5; u.c.b = 6;\n"
		"\treturn p.Sum() + u.c.a + u.c.b + (int)sizeof(u);\n"
		"}\n"
		"struct CBlock { int m; void* Add(void); };\n"
		"void* CBlock::CBlock::Add(void) { m = 3; return this; }\n"
		"int main() { CBlock b; b.Add(); return Local(1) == 1 + 2 + 5 + 6 + 16 && b.m == 3; }\n"));

	AssertInt(1, TestCPP65Main(
		"template<class M> int ComparePrimitive(const void* a, const void* b) { return *(M*)a - *(M*)b; }\n"
		"typedef int (*FCompare)(const void*, const void*);\n"
		"int Call(FCompare f, int a, int b) { return f(&a, &b); }\n"
		"typedef void (*CCall)(void);\n"
		"struct SFunctionPointer { union { CCall cCall; int (*pfInt)(void); }; int x; };\n"
		"int Five(void) { return 5; }\n"
		"int main()\n"
		"{\n"
		"\tSFunctionPointer s; s.pfInt = &Five; s.x = 3;\n"
		"\tFCompare f = ComparePrimitive<short>;\n"
		"\treturn Call(&ComparePrimitive<int>, 7, 2) == 5 && f == &ComparePrimitive<short> && s.pfInt() == 5 && s.x == 3 && sizeof(s) == 8 && (void*)s.cCall == (void*)&Five;\n"
		"}\n"));

	AssertInt(1, TestCPP65Main(
		"typedef signed char int8;\n"
		"template<class M, int8 I> class CBase { public: M ma[I]; int Num() { return I; } };\n"
		"template<class M, int8 I> class CDerived : public CBase<M, I> { public: int Get() { return CBase<M, I>::Num(); } };\n"
		"class CInt : public CDerived<int, 4> { public: int All() { return Num() + Get(); } };\n"
		"int main() { CInt c; return c.All() == 8 && sizeof(c) == 16; }\n"));

	AssertInt(1, TestCPP65Main(
		"int Sum(int n)\n"
		"{\n"
		"\tint* p = (int*)__builtin_alloca(n * sizeof(int));\n"
		"\tchar* c = (char*)__builtin_alloca(3);\n"
		"\tint t = 0;\n"
		"\tfor (int i = 0; i < n; i++) p[i] = i;\n"
		"\tc[0] = 1; c[2] = 2;\n"
		"\tfor (int i = 0; i < n; i++) t += p[i];\n"
		"\treturn t + c[0] + c[2];\n"
		"}\n"
		"int main() { int a = 7; int r = Sum(10) + Sum(3); return r == 45 + 3 + 3 + 3 && a == 7; }\n"));
}


//////////////////////////////////////////////////////////////////////////
//
// Every BaseLib .cpp file compiles for the 65C64 and links (with a main that uses
// none of it).
//
//////////////////////////////////////////////////////////////////////////
void TestCPP65GeneratorAllBaseLib(void)
{
	CChars	szErrors;
	size	uiFiles;

	szErrors.Init();
	uiFiles = TestCPP65CompileLibrary("BaseLib", &szErrors);
	AssertTrue(uiFiles > 350);
	AssertString("", szErrors.Text());
	szErrors.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// Programs whose functions are loaded from a drive when they are first called give
// the same results.  Only some of the units are loaded: the ones a run calls.
//
//////////////////////////////////////////////////////////////////////////
void TestCPP65GeneratorLazy(void)
{
	static const char*	aszMD5[] = { "BaseLib/MD5.cpp", "Libc65/string.cpp", "Input/CPP65/MD5Project/Main.cpp", NULL };
	static const char*	aszRedBlackTree[] = { "BaseLib/RedBlackTree.cpp", "Libc65/string.cpp", "Libc65/stdlib.cpp", "Libc65/ctype.cpp", "Input/CPP65/RedBlackTreeProject/FreeListStub.cpp", "Input/CPP65/RedBlackTreeProject/Main.cpp", NULL };
	static const char*	aszSort[] = { "BaseLib/QuickSort.cpp", "BaseLib/BubbleSort.cpp", "BaseLib/BinarySearch.cpp", "Input/CPP65/SortProject/MemSwpStub.cpp", "Input/CPP65/SortProject/Main.cpp", NULL };
	static const char*	aszFloat[] = { "Libc65/softfloat.cpp", "Libc65/softfloat.asm", NULL };
	static const char*	aszNone[] = { NULL };
	size				uiUnits;
	size				uiLoads;

	AssertInt(0x3F, TestCPP65RunProjectLazy(aszMD5, "", &uiUnits, &uiLoads));
	AssertTrue((uiLoads > 0) && (uiLoads <= uiUnits));
	AssertInt(0xF, TestCPP65RunProjectLazy(aszRedBlackTree, "", &uiUnits, &uiLoads));
	AssertTrue((uiLoads > 0) && (uiLoads <= uiUnits));
	AssertInt(0x7, TestCPP65RunProjectLazy(aszSort, "", &uiUnits, &uiLoads));
	AssertTrue((uiLoads > 0) && (uiLoads <= uiUnits));
	AssertInt(6 + 9, TestCPP65RunProjectLazy(aszFloat, "", &uiUnits, &uiLoads, "int Never(float x) { return (int)(x * 100); }\nint main() { float f = 1.5f; double d = 2.25; if (f > 10.0f) return Never(f); return (int)(f * 4 + d * 4); }\n"));
	AssertTrue((uiLoads > 0) && (uiLoads < uiUnits));

	//A global object, a virtual call, a function pointer and recursion.  Unused is left out; Twice is loaded
	//when Apply calls it through the pointer.
	AssertInt(5 + 10 + 6 + 120, TestCPP65RunProjectLazy(aszNone, "", &uiUnits, &uiLoads,
		"struct S { int m; S(int v) : m(v) {} ~S() { *(int*)0x100000 = m; } };\n"
		"S gS(5);\n"
		"struct B { virtual int F() { return 1; } };\n"
		"struct D : B { int F() { return 10; } };\n"
		"int Twice(int x) { return x * 2; }\n"
		"int Apply(int (*f)(int), int x) { return f(x); }\n"
		"int Fact(int n) { return n <= 1 ? 1 : n * Fact(n - 1); }\n"
		"int Unused() { return 99; }\n"
		"int main() { D d; B* p = &d; return gS.m + p->F() + Apply(Twice, 3) + Fact(5); }\n"));
	AssertTrue((uiLoads > 0) && (uiLoads <= uiUnits));
}


//////////////////////////////////////////////////////////////////////////
//
// BaseLib code with the Libc65 code it needs, run on the 65C64.
//
//////////////////////////////////////////////////////////////////////////
void TestCPP65GeneratorBaseLib(void)
{
	static const char*	aszMD5[] = { "BaseLib/MD5.cpp", "Libc65/string.cpp", "Input/CPP65/MD5Project/Main.cpp", NULL };
	static const char*	aszMersenneTwister[] = { "BaseLib/MersenneTwister.cpp", "Libc65/time.cpp", "Input/CPP65/MersenneTwisterProject/Main.cpp", NULL };
	static const char*	aszSort[] = { "BaseLib/QuickSort.cpp", "BaseLib/BubbleSort.cpp", "BaseLib/BinarySearch.cpp", "Input/CPP65/SortProject/MemSwpStub.cpp", "Input/CPP65/SortProject/Main.cpp", NULL };
	static const char*	aszRedBlackTree[] = { "BaseLib/RedBlackTree.cpp", "Libc65/string.cpp", "Libc65/stdlib.cpp", "Libc65/ctype.cpp", "Input/CPP65/RedBlackTreeProject/FreeListStub.cpp", "Input/CPP65/RedBlackTreeProject/Main.cpp", NULL };

	//MD5Dump makes a CChars, which is not compiled here, but nothing calls MD5Dump so it is left out.
	AssertInt(0x3F, TestCPP65RunProject(aszMD5, ""));

	//CFreeList is a stub over malloc.
	AssertInt(0xF, TestCPP65RunProject(aszRedBlackTree, ""));

	//Static functions and globals are each unit's own.
	static const char*	aszStatic[] = { "Input/CPP65/StaticProject/Other.cpp", NULL };
	AssertInt(11 + 22 * 100, TestCPP65RunProject(aszStatic, "", 100000, "static int giValue = 10;\nstatic int Value(void) { return 1; }\nint Other(void);\nint main() { return Value() + giValue + Other() * 100; }\n"));

	//floats, against the same calls natively.
	AssertCPP65FloatHelper();
	AssertCPP65Quaternion();

	//MT19937 against its reference sequence, and Libc65's time.
	AssertInt(0xFF, TestCPP65RunProject(aszMersenneTwister, ""));

	//QuickSort has an unnamed struct and gotos.  MemSwp is a stub (StringHelper has floating point).
	AssertInt(0x7, TestCPP65RunProject(aszSort, ""));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
static void AssertCPP65Error(const char* szExpected, const char* szSource)
{
	CChars	szAssembly;
	CChars	szErrors;

	szAssembly.Init();
	szErrors.Init();
	AssertFalse(TestCPP65Generate(&szAssembly, &szErrors, szSource));
	AssertString(szExpected, szErrors.Text());
	szErrors.Kill();
	szAssembly.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCPP65GeneratorErrors(void)
{
	AssertCPP65Error("Generated.cpp (1, 27): The operands must be integers [f]\n", "float f; int g() { return f % 2; }");
	AssertCPP65Error("Generated.cpp (1, 1): This declaration is not supported by the 65C64 generator yet [namespace]\n", "namespace N { int x; }");
	AssertCPP65Error("Generated.cpp (1, 19): Only new Type[count] (one dimension, no initialiser list) is supported by the 65C64 generator yet [new]\n", "int* f() { return new int[2]{1, 2}; }");
	AssertCPP65Error("Generated.cpp (1, 44): Objects can only be copied or used through pointers by the 65C64 generator yet [p]\n", "struct P { int x; }; int f() { P p; return p; }");
	AssertCPP65Error("Generated.cpp (1, 32): No function matches the arguments [f]\n", "int f(int a); int g() { return f(); }");
	AssertCPP65Error("Generated.cpp (1, 16): break outside a loop or switch [break]\n", "void f(void) { break; }");
	AssertCPP65Error("Generated.cpp (1, 31): A static local variable needs a constant initialiser in the 65C64 generator yet [a]\n", "int f(int a) { static int s = a; return s; }");
	AssertCPP65Error("Generated.cpp (1, 149): More than one specialisation of the class template matches equally [s]\n", "template<class A, class B> struct S {}; template<class A, class B> struct S<A*, B> {}; template<class A, class B> struct S<A, B*> {}; S<int*, int*> s; int main() { return 0; }");
	AssertCPP65Error("Generated.cpp (1, 70): The member template has not been defined [c]\n", "struct C { template<class T> int F(T t); }; int main() { C c; return c.F(1); }");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCPP65Generator(void)
{
	BeginTests();

	TypesInit();
	FastFunctionsInit();
	TypeConverterInit();
	NumberInit();
	C65C64InstructionFactory::GetInstance()->Init();

	TestCPP65GeneratorAssembly();
	TestCPP65GeneratorConvention();
	TestCPP65GeneratorOperators();
	TestCPP65GeneratorConversions();
	TestCPP65GeneratorStatements();
	TestCPP65GeneratorPrograms();
	TestCPP65GeneratorClasses();
	TestCPP65GeneratorExtern();
	TestCPP65GeneratorNewDelete();
	TestCPP65GeneratorMemberTemplates();
	TestCPP65GeneratorSpecialisation();
	TestCPP65GeneratorMemberPointers();
	TestCPP65GeneratorVariadicTemplates();
	TestCPP65GeneratorOverloadRanking();
	TestCPP65GeneratorBaseLibConstructs();
	TestCPP65GeneratorArrayTemplate();
	TestCPP65GeneratorProject();
	TestCPP65GeneratorFloat();
	TestCPP65GeneratorBaseLib();
	TestCPP65GeneratorAllBaseLib();
	TestCPP65GeneratorLazy();
	TestCPP65GeneratorErrors();

	C65C64InstructionFactory::GetInstance()->Kill();
	NumberKill();
	TypeConverterKill();
	FastFunctionsKill();
	TypesKill();

	TestStatistics();
}
