#include <string.h>
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
#include "BaseLib/Operators.h"
#include "BaseLib/NumberControl.h"
#include "TestLib/Assert.h"


static const int32	gaiValues[] = { 0, 1, -1, 2, -2, 7, -7, 31, 100, -100, 12345, -98765, 65536, 2147483647, (int32)0x80000000 };
static const int32	gaiShifts[] = { 0, 1, 4, 15, 16, 31 };


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
		"\t\t.align 4\n"
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
		"\t\t.org $10000\n"
		"Start:\n"
		"\t\tcpy S, $1fffff\n"
		"\t\tcpy W, 0\n"
		"\t\twtth (A, B), 4\n"
		"\t\twtth (X, Y), 4\n"
		"\t\tjsr _main\n"
		"\t\tstp\n"));
	szErrors.Kill();
	szAssembly.Kill();

	//main's return address is at 001F:FFFC, the caller's V below it, then x.
	AssertIntHex(0x1FFFF4, TestCPP65Main("int main() { int x = 5; return (int)&x; }"));
	AssertInt(1, TestCPP65Main("int main() { unsigned r = *(unsigned*)0x1FFFFC; return r > 0x10000 && r < 0x10020; }"));

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
	//R_Finalise after main.
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
// CArrayTemplate<CTestClass> in a project of three translation units, added by
// hand: Main.cpp, TestClass.cpp (CTestClass, and a function that also uses the
// array) and ArrayBlockStub.cpp (the CArrayBlock functions).  Each unit is compiled
// with its own label prefix; the inline and template functions they both use are
// written once.  The units are joined under one start up, assembled and run.
//
//////////////////////////////////////////////////////////////////////////
void TestCPP65GeneratorProject(void)
{
	CProject			cProject;
	CLibrary*			pcLibrary;
	CTranslationUnit*	pcFile;
	SProcessIter		sIter;
	CCPPTokeniser		cTokeniser;
	CCPPSyntaxTree		cTree;
	CCPPParser			cParser;
	CCPP65Generator		cGenerator;
	CFileUtil			cFileUtil;
	CChars				szDirectory;
	CChars				szUnits;
	CChars				szProgram;
	CChars				szUnit;
	CArrayChars			aszEmitted;
	CArrayChars			aszInitialise;
	CArrayChars			aszFinalise;
	STestCPP65Run		sRun;
	int					iUnit;

	cProject.Init(false);
	szDirectory.Init(".." _FS_ ".." _FS_ ".." _FS_ "commonlibraries" _FS_ "Libc65");
	cFileUtil.FullPath(&szDirectory);
	cProject.AddIncludeDirectory(szDirectory.Text(), false, true);
	szDirectory.Kill();
	szDirectory.Init(".." _FS_ ".." _FS_ ".." _FS_ "commonlibraries");
	cFileUtil.FullPath(&szDirectory);
	cProject.AddIncludeDirectory(szDirectory.Text(), true, false);
	szDirectory.Kill();

	pcLibrary = cProject.AddLibrary("ArrayTemplateProject", "Input" _FS_ "CPP65" _FS_ "ArrayTemplateProject", false);
	pcLibrary->AddHeaderFile("TestClass.h");
	pcLibrary->AddHeaderFile("ArrayBlockStub.h");
	pcLibrary->AddTranslationUnit("Main.cpp");
	pcLibrary->AddTranslationUnit("TestClass.cpp");
	pcLibrary->AddTranslationUnit("ArrayBlockStub.cpp");
	pcLibrary->AddConfiguration("65C64");
	AssertTrue(cProject.Process("65C64"));

	szUnits.Init();
	aszEmitted.Init();
	aszInitialise.Init();
	aszFinalise.Init();
	iUnit = 0;
	for (pcFile = cProject.Start(&sIter, "65C64"); pcFile; pcFile = cProject.Iterate(&sIter))
	{
		iUnit++;
		cTokeniser.Init();
		AssertTrue(cTokeniser.Tokenise(pcFile->GetTokens()));
		cTree.Init(&cTokeniser);
		cParser.Init(&cTokeniser, &cTree);
		AssertTrue(cParser.Parse());
		cParser.Kill();

		szUnit.Init("U");
		szUnit.Append(iUnit);
		szUnit.Append('_');
		cGenerator.Init(&cTree);
		cGenerator.SetUnit(szUnit.Text(), &aszEmitted);
		AssertTrue(cGenerator.Generate(&szUnits));
		AssertString("", cGenerator.GetErrors()->Text());
		cGenerator.GetStartUp(&aszInitialise, &aszFinalise);
		cGenerator.Kill();
		szUnit.Kill();

		cTree.Kill();
		cTokeniser.Kill();
	}
	AssertInt(3, iUnit);

	//No unit has global objects (CTestClass::siMade is constant data), so there is nothing to initialise.  Get is
	//used by Main.cpp and TestClass.cpp but written once (assembling would fail on a label written twice).
	AssertInt(0, (int)aszInitialise.NumElements());
	AssertTrue(aszEmitted.GetIndex("_CArrayTemplate__T_C10CTestClass__Get") != ARRAY_ELEMENT_NOT_FOUND);

	szProgram.Init();
	CCPP65Generator::AppendStartUp(&szProgram, &aszInitialise, &aszFinalise);
	szProgram.Append(szUnits);
	AssertTrue(TestCPP65BeginAssembly(&sRun, szProgram.Text()));
	AssertTrue(TestCPP65Run(&sRun, 1000000) < 1000000);
	AssertIntHex(CPP65_STACK_TOP, TestCPP65MPU(&sRun)->GetS());
	AssertInt(4031, (int32)TestCPP65MPU(&sRun)->GetA());
	TestCPP65End(&sRun);

	szProgram.Kill();
	aszFinalise.Kill();
	aszInitialise.Kill();
	aszEmitted.Kill();
	szUnits.Kill();
	cProject.Kill();
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
	AssertCPP65Error("Generated.cpp (1, 27): Floating point is not supported by the 65C64 generator yet [f]\n", "float f; int g() { return f; }");
	AssertCPP65Error("Generated.cpp (1, 31): 64 bit integers are not supported by the 65C64 generator yet [l]\n", "long long l; int g() { return l; }");
	AssertCPP65Error("Generated.cpp (1, 1): This declaration is not supported by the 65C64 generator yet [namespace]\n", "namespace N { int x; }");
	AssertCPP65Error("Generated.cpp (1, 63): Only the first base class can be polymorphic in the 65C64 generator yet [struct]\n", "struct A { virtual int f(); }; struct B { virtual int g(); }; struct C : A, B {}; C gC;");
	AssertCPP65Error("Generated.cpp (1, 58): Objects cannot be passed by value by the 65C64 generator yet; pass a pointer or a reference [q]\n", "struct P { int x; }; int f(P p); int g() { P q; return f(q); }");
	AssertCPP65Error("Generated.cpp (1, 19): Only placement new is supported by the 65C64 generator yet [new]\n", "int* f() { return new int; }");
	AssertCPP65Error("Generated.cpp (1, 44): Objects can only be copied or used through pointers by the 65C64 generator yet [p]\n", "struct P { int x; }; int f() { P p; return p; }");
	AssertCPP65Error("Generated.cpp (1, 32): No function matches the arguments [f]\n", "int f(int a); int g() { return f(); }");
	AssertCPP65Error("Generated.cpp (1, 16): break outside a loop or switch [break]\n", "void f(void) { break; }");
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
	OperatorsInit();
	NumberInit();
	C65C64InstructionFactory::GetInstance()->Init();

	TestCPP65GeneratorAssembly();
	TestCPP65GeneratorConvention();
	TestCPP65GeneratorOperators();
	TestCPP65GeneratorConversions();
	TestCPP65GeneratorStatements();
	TestCPP65GeneratorPrograms();
	TestCPP65GeneratorClasses();
	TestCPP65GeneratorArrayTemplate();
	TestCPP65GeneratorProject();
	TestCPP65GeneratorErrors();

	C65C64InstructionFactory::GetInstance()->Kill();
	NumberKill();
	OperatorsKill();
	TypeConverterKill();
	FastFunctionsKill();
	TypesKill();

	TestStatistics();
}
