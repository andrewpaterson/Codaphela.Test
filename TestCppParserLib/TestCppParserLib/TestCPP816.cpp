#include <string.h>
#include "BaseLib/FastFunctions.h"
#include "BaseLib/TypeNames.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/NumberControl.h"
#include "BaseLib/ArrayInt.h"
#include "MicroprocessorLib/W65C816InstructionFactory.h"
#include "Assembler65Lib/Asm816Lockstep.h"
#include "Assembler65Lib/Asm65Memory.h"
#include "CppParserLib/CPP65Builder.h"
#include "TestLib/Assert.h"
#include "TestCPP65Context.h"


//////////////////////////////////////////////////////////////////////////
//
// C++ compiled for the W65C816 (CCPP65Builder with CPPT_W65C816): the generator's C++, the IR front end and
// CIR816Backend, linked with the W65C816's start up and runtime routines and run on CFast65C816.
//
//////////////////////////////////////////////////////////////////////////


//The native results TestCPP65Generator.cpp's FloatHelper and Quaternion tests check against.
extern CArrayInt	gaiFloatHelperResults;
extern CArrayInt	gaiQuaternionResults;
extern CArrayInt	gaiQuaternionIsFloat;
void	FloatHelperExpected(void);
void	QuaternionExpected(void);
uint64	TestCPP65FloatUlps(uint32 uiActual, uint32 uiExpected);


#define TEST_CPP816_STEPS		50000000
#define TEST_CPP816_SLOW_STEPS	500000000
#define TEST_CPP816_RESULTS		0x100000


//////////////////////////////////////////////////////////////////////////
//
// Compiles and links szSource (if given) and the units (TestCPP65AddUnits, without the 65C64 assembly ones) for
// the W65C816 and runs it in CAsm65Memory's 2MB.  The labels in szStubs must be exactly the ones used but defined
// by no unit.  The first uiResults longs at 0010:0000 are copied to puiResults.  It may run uiMaxSteps
// instructions.  Returns main's int (16 bits, sign extended), or -1000000 if it didn't build or stop.
//
//////////////////////////////////////////////////////////////////////////
int32 TestCPP816RunProject(const char** aszUnits, const char* szStubs, const char* szSource, bool bLockstep = false, uint32* puiResults = NULL, size uiResults = 0, size uiMaxSteps = TEST_CPP816_STEPS)
{
	CCPP65Builder	cBuilder;
	CAsm65Memory	cMemory;
	CFast65C816		cFast;
	CAsm816Lockstep	cLockstep;
	CChars			szMissing;
	size			uiSteps;
	size			i;
	int32			iResult;
	bool			bResult;

	iResult = -1000000;
	cBuilder.Init();
	cBuilder.SetTarget(CPPT_W65C816);
	TestCPP65AddIncludeDirectories(&cBuilder);
	bResult = cBuilder.AddStartUp();
	if (szSource)
	{
		bResult &= cBuilder.AddSource("Test.cpp", szSource);
	}
	if (aszUnits)
	{
		TestCPP65AddUnits(&cBuilder, aszUnits, false);
	}
	bResult &= cBuilder.Link();
	AssertString("", cBuilder.GetErrors());
	AssertTrue(bResult);
	szMissing.Init();
	cBuilder.GetMissingNames(&szMissing);
	AssertString(szStubs, szMissing.Text());
	szMissing.Kill();
	if (bResult)
	{
		cMemory.Init();
		cMemory.Load(cBuilder.GetOutput());
		cMemory.InitFast816(&cFast);
		cFast.Reset();
		if (bLockstep)
		{
			cLockstep.Init(&cMemory, &cFast);
			uiSteps = cLockstep.Run(uiMaxSteps, 64);
			AssertString("", cLockstep.GetDifferences());
			cLockstep.Kill();
		}
		else
		{
			uiSteps = cFast.Run(uiMaxSteps);
		}
		AssertTrue(uiSteps < uiMaxSteps);
		AssertTrue(cFast.IsStopped());
		AssertInt(0, (int)cMemory.NumBadAccesses());
		if (cFast.IsStopped())
		{
			iResult = (int16)cFast.GetC();
			AssertIntHex(GetCPPTarget(CPPT_W65C816)->uiStackTop, (uint32)cFast.GetS());
		}
		for (i = 0; i < uiResults; i++)
		{
			puiResults[i] = cMemory.GetLong(TEST_CPP816_RESULTS + 4 * (uint32)i);
		}
		cFast.Kill();
		cMemory.Kill();
	}
	cBuilder.Kill();
	return iResult;
}


//////////////////////////////////////////////////////////////////////////
//
// Compiles, links and runs szSource.  Returns main's int (16 bits, sign extended), or -1000000 if it didn't build
// or stop.
//
//////////////////////////////////////////////////////////////////////////
int32 TestCPP816Run(const char* szSource, bool bLockstep = false)
{
	return TestCPP816RunProject(NULL, "", szSource, bLockstep);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCPP816Basics(void)
{
	AssertInt(42, TestCPP816Run("int main(void) { return 42; }\n", true));
	AssertInt(-5, TestCPP816Run("int main(void) { int a = 7; int b = 12; return a - b; }\n"));

	//int is 16 bits: it wraps, and sizeof says so.
	AssertInt(2, TestCPP816Run("int main(void) { return sizeof(int); }\n"));
	AssertInt(4, TestCPP816Run("int main(void) { return sizeof(long) + sizeof(short) - 2; }\n"));
	AssertInt(-32768, TestCPP816Run("int main(void) { int a = 32767; a = a + 1; return a; }\n"));

	//long is 32 bits.
	AssertInt(1234, TestCPP816Run("int main(void) { long a = 100000; long b = a * 3 + 1234; return (int)(b - 300000); }\n", true));
	AssertInt(3, TestCPP816Run("int main(void) { long a = 1000000; long b = 300000; return (int)(a / b); }\n"));

	//Libc65's headers: the 32 bit types are long, size_t is 32 bits and INT_MAX is 16 bits'.
	AssertInt(4 * 1000 + 4 * 100 + 2 * 10 + 1, TestCPP816Run(
		"#include <stdint.h>\n"
		"#include <stddef.h>\n"
		"#include <limits.h>\n"
		"int main(void)\n"
		"{\n"
		"\tint32_t i = INT32_MAX;\n"
		"\treturn sizeof(i) * 1000 + sizeof(size_t) * 100 + sizeof(int16_t) * 10 + (INT_MAX == 32767);\n"
		"}\n"));
}


//////////////////////////////////////////////////////////////////////////
//
// Loops, arrays, pointers, functions and recursion.
//
//////////////////////////////////////////////////////////////////////////
void TestCPP816Functions(void)
{
	AssertInt(55, TestCPP816Run(
		"int Fibonacci(int n)\n"
		"{\n"
		"\tif (n < 2) { return n; }\n"
		"\treturn Fibonacci(n - 1) + Fibonacci(n - 2);\n"
		"}\n"
		"int main(void) { return Fibonacci(10); }\n", true));

	AssertInt(150, TestCPP816Run(
		"int gaiTable[5] = { 10, 20, 30, 40, 50 };\n"
		"int Sum(int* pi, int iCount)\n"
		"{\n"
		"\tint iSum = 0;\n"
		"\tfor (int i = 0; i < iCount; i++) { iSum += pi[i]; }\n"
		"\treturn iSum;\n"
		"}\n"
		"int main(void) { return Sum(gaiTable, 5); }\n"));

	AssertInt(11, TestCPP816Run(
		"int Length(const char* sz)\n"
		"{\n"
		"\tint i = 0;\n"
		"\twhile (sz[i] != 0) { i++; }\n"
		"\treturn i;\n"
		"}\n"
		"int main(void) { return Length(\"Hello world\"); }\n"));

	AssertInt(321, TestCPP816Run(
		"void Reverse(char* sz, int iLength)\n"
		"{\n"
		"\tfor (int i = 0; i < iLength / 2; i++)\n"
		"\t{\n"
		"\t\tchar c = sz[i];\n"
		"\t\tsz[i] = sz[iLength - 1 - i];\n"
		"\t\tsz[iLength - 1 - i] = c;\n"
		"\t}\n"
		"}\n"
		"int main(void)\n"
		"{\n"
		"\tchar sz[4] = { '1', '2', '3', 0 };\n"
		"\tReverse(sz, 3);\n"
		"\treturn (sz[0] - '0') * 100 + (sz[1] - '0') * 10 + (sz[2] - '0');\n"
		"}\n"));
}


//////////////////////////////////////////////////////////////////////////
//
// Classes: fields, member functions, constructors and a virtual call.
//
//////////////////////////////////////////////////////////////////////////
void TestCPP816Classes(void)
{
	AssertInt(7 * 3 + 2, TestCPP816Run(
		"class CPoint\n"
		"{\n"
		"public:\n"
		"\tint\tmiX;\n"
		"\tint\tmiY;\n"
		"\tCPoint(int iX, int iY) { miX = iX; miY = iY; }\n"
		"\tint Dot(CPoint* psOther) { return miX * psOther->miX + miY * psOther->miY; }\n"
		"};\n"
		"int main(void)\n"
		"{\n"
		"\tCPoint a(7, 1);\n"
		"\tCPoint b(3, 2);\n"
		"\treturn a.Dot(&b);\n"
		"}\n", true));

	AssertInt(10 + 200, TestCPP816Run(
		"class CShape\n"
		"{\n"
		"public:\n"
		"\tvirtual int Area(void) { return 0; }\n"
		"};\n"
		"class CSquare : public CShape\n"
		"{\n"
		"public:\n"
		"\tint\tmiSide;\n"
		"\tCSquare(int iSide) { miSide = iSide; }\n"
		"\tint Area(void) override { return miSide * miSide; }\n"
		"};\n"
		"class CBar : public CShape\n"
		"{\n"
		"public:\n"
		"\tint\tmiLength;\n"
		"\tCBar(int iLength) { miLength = iLength; }\n"
		"\tint Area(void) override { return miLength; }\n"
		"};\n"
		"int Total(CShape* pcA, CShape* pcB) { return pcA->Area() + pcB->Area(); }\n"
		"int main(void)\n"
		"{\n"
		"\tCBar cBar(10);\n"
		"\tCSquare cSquare(14);\n"
		"\treturn Total(&cBar, &cSquare) + 4;\n"
		"}\n"));
}


//////////////////////////////////////////////////////////////////////////
//
// Statements and operators: switch, do, 16 bit multiply, divide and shifts, unsigned long, function pointers,
// globals and a destructor.
//
//////////////////////////////////////////////////////////////////////////
void TestCPP816Statements(void)
{
	AssertInt(1 + 20 + 300 + 4000, TestCPP816Run(
		"int Pick(int i)\n"
		"{\n"
		"\tswitch (i)\n"
		"\t{\n"
		"\tcase 0: return 1;\n"
		"\tcase 1: return 20;\n"
		"\tcase 5: return 300;\n"
		"\tdefault: return 4000;\n"
		"\t}\n"
		"}\n"
		"int main(void) { return Pick(0) + Pick(1) + Pick(5) + Pick(9); }\n"));

	AssertInt(720 / 7 + 720 % 7 + (720 >> 3) + (-720 >> 2) + (3 << 4), TestCPP816Run(
		"int Factorial(int n) { int r = 1; do { r *= n; n--; } while (n > 1); return r; }\n"
		"int main(void) { int f = Factorial(6); int m = -f; return f / 7 + f % 7 + (f >> 3) + (m >> 2) + (3 << 4); }\n", true));

	AssertInt(10, TestCPP816Run(
		"unsigned long Hash(const char* sz)\n"
		"{\n"
		"\tunsigned long h = 5381;\n"
		"\twhile (*sz) { h = h * 33 + (unsigned char)*sz; sz++; }\n"
		"\treturn h;\n"
		"}\n"
		"int main(void) { return (int)(Hash(\"816\") % 11); }\n"));

	AssertInt(3 * 4 + 3 + 4, TestCPP816Run(
		"int Add(int a, int b) { return a + b; }\n"
		"int Multiply(int a, int b) { return a * b; }\n"
		"int Apply(int (*fOperation)(int, int), int a, int b) { return fOperation(a, b); }\n"
		"int main(void) { return Apply(Multiply, 3, 4) + Apply(Add, 3, 4); }\n"));

	AssertInt(6 + 100, TestCPP816Run(
		"int giCount = 0;\n"
		"class CCounter\n"
		"{\n"
		"public:\n"
		"\tint\tmiAdd;\n"
		"\tCCounter(int iAdd) { miAdd = iAdd; giCount += iAdd; }\n"
		"\t~CCounter() { giCount += 100; }\n"
		"};\n"
		"int Make(void) { CCounter a(1); CCounter b(5); return giCount; }\n"
		"int main(void) { int i = Make(); return i + giCount - 206 + 100; }\n"));
}


//////////////////////////////////////////////////////////////////////////
//
// Globals made at start up, in source order: constructed objects and a scalar with a non constant initialiser.
// Destructors run after main (and so can't change its result).  A global no one uses is dropped by the linker,
// with its start up routines, as on the 65C64.
//
//////////////////////////////////////////////////////////////////////////
void TestCPP816Globals(void)
{
	AssertInt(3 + 40 + 7, TestCPP816Run(
		"int Seven(void) { return 7; }\n"
		"class CValue\n"
		"{\n"
		"public:\n"
		"\tint\tmiValue;\n"
		"\tCValue(int iValue) { miValue = iValue; }\n"
		"};\n"
		"CValue gcA(3);\n"
		"CValue gcB(40);\n"
		"int giSeven = Seven();\n"
		"int main(void) { return gcA.miValue + gcB.miValue + giSeven; }\n", true));

	AssertInt(12, TestCPP816Run(
		"int giMade = 0;\n"
		"class CMade\n"
		"{\n"
		"public:\n"
		"\tCMade() { giMade = giMade * 10 + 1; }\n"
		"\t~CMade() { giMade = 0; }\n"
		"};\n"
		"class CSecond\n"
		"{\n"
		"public:\n"
		"\tCSecond() { giMade = giMade * 10 + 2; }\n"
		"};\n"
		"CMade gcMade;\n"
		"CSecond gcSecond;\n"
		"int main(void) { return (&gcMade != 0) && (&gcSecond != 0) ? giMade : -1; }\n"));
}


//////////////////////////////////////////////////////////////////////////
//
// The builtins softfloat.cpp and the libraries use: __builtin_clz, ctz and popcount at each width (and L literals
// are long).
//
//////////////////////////////////////////////////////////////////////////
void TestCPP816Builtins(void)
{
	AssertInt(-32768, TestCPP816Run("int main(void) { return (int)((1UL << 31) >> 16); }\n"));
	AssertInt(-32768, TestCPP816Run("int main(void) { unsigned long u = 1UL << 31; return (int)(u >> 16); }\n"));
	AssertInt(31, TestCPP816Run("int main(void) { unsigned long u = 1UL << 31; return __builtin_ctzl(u); }\n"));
	AssertInt(31, TestCPP816Run("int main(void) { return __builtin_ctzl(0x80000000UL); }\n"));
	AssertInt(4, TestCPP816Run("int main(void) { return sizeof(1UL); }\n"));
	AssertInt(1 + 14 * 10 + 3 * 100, TestCPP816Run(
		"int main(void) { unsigned int u = 0x4000; return __builtin_clz(u) + __builtin_ctz(u) * 10 + __builtin_popcount(0x7) * 100; }\n"));
	AssertInt(14 + 31 * 100, TestCPP816Run(
		"int main(void) { unsigned long u = 0x00024000; return __builtin_clzl(u) + __builtin_ctzl(1UL << 31) * 100; }\n"));
	AssertInt(10 + 63 * 100, TestCPP816Run(
		"int main(void) { unsigned long long u = 0x0020000000000000ULL; return __builtin_clzll(u) + __builtin_ctzll(1ULL << 63) * 100; }\n"));
	AssertInt(40, TestCPP816Run(
		"int main(void) { unsigned long long u = 0xFF00FF00FF00FF00ULL; return __builtin_popcountll(u) + __builtin_popcountll(0xFFULL); }\n"));
}


//////////////////////////////////////////////////////////////////////////
//
// BaseLib code with the Libc65 code it needs, as TestCPP65GeneratorBaseLib runs it on the 65C64.
//
//////////////////////////////////////////////////////////////////////////
void TestCPP816BaseLib(void)
{
	static const char*	aszMD5[] = { "BaseLib/MD5.cpp", "Libc65/string.cpp", "Input/CPP65/MD5Project/Main.cpp", NULL };
	static const char*	aszMersenneTwister[] = { "BaseLib/MersenneTwister.cpp", "Libc65/time.cpp", "Input/CPP65/MersenneTwisterProject/Main.cpp", NULL };
	static const char*	aszSort[] = { "BaseLib/QuickSort.cpp", "BaseLib/BubbleSort.cpp", "BaseLib/BinarySearch.cpp", "Input/CPP65/SortProject/MemSwpStub.cpp", "Input/CPP65/SortProject/Main.cpp", NULL };
	static const char*	aszRedBlackTree[] = { "BaseLib/RedBlackTree.cpp", "Libc65/string.cpp", "Libc65/stdlib.cpp", "BaseLib/TrueMallocator.cpp", "Libc65/ctype.cpp", "Input/CPP65/RedBlackTreeProject/FreeListStub.cpp", "Input/CPP65/RedBlackTreeProject/Main.cpp", NULL };
	static const char*	aszStatic[] = { "Input/CPP65/StaticProject/Other.cpp", NULL };

	AssertInt(0x3F, TestCPP816RunProject(aszMD5, "", NULL));
	AssertInt(0xF, TestCPP816RunProject(aszRedBlackTree, "", NULL));
	AssertInt(11 + 22 * 100, TestCPP816RunProject(aszStatic, "", "static int giValue = 10;\nstatic int Value(void) { return 1; }\nint Other(void);\nint main() { return Value() + giValue + Other() * 100; }\n"));
	//Every 32 bit multiply and remainder is a runtime call (Init and the twists' % 624): 57M instructions
	//(2026-10-25), before step 7's optimisation.
	AssertInt(0xFF, TestCPP816RunProject(aszMersenneTwister, "", NULL, false, NULL, 0, TEST_CPP816_SLOW_STEPS));
	AssertInt(0x7, TestCPP816RunProject(aszSort, "", NULL));
}


//////////////////////////////////////////////////////////////////////////
//
// BaseLib's FloatHelper and SQuaternion with softfloat.cpp (and math.cpp) compiled for the W65C816, against the
// same calls natively, as on the 65C64.
//
//////////////////////////////////////////////////////////////////////////
void TestCPP816Floats(void)
{
	static const char*	aszFloatHelper[] = { "BaseLib/FloatHelper.cpp", "Libc65/softfloat.cpp", "Libc65/math.cpp", "Input/CPP65/FloatHelperProject/Main.cpp", NULL };
	static const char*	aszQuaternion[] = { "BaseLib/Quaternion.cpp", "Libc65/softfloat.cpp", "Input/CPP65/QuaternionProject/Main.cpp", NULL };
	uint32				auiResults[256];
	size				i;
	uint32				uiExpected;

	gaiFloatHelperResults.Init();
	FloatHelperExpected();
	AssertTrue(gaiFloatHelperResults.NumElements() <= 256);
	AssertInt((int)gaiFloatHelperResults.NumElements(), TestCPP816RunProject(aszFloatHelper, "", NULL, false, auiResults, gaiFloatHelperResults.NumElements(), TEST_CPP816_SLOW_STEPS));
	for (i = 0; i < gaiFloatHelperResults.NumElements(); i++)
	{
		AssertIntHex((uint32)gaiFloatHelperResults.GetValue(i), auiResults[i]);
	}
	gaiFloatHelperResults.Kill();

	gaiQuaternionResults.Init();
	gaiQuaternionIsFloat.Init();
	QuaternionExpected();
	AssertTrue(gaiQuaternionResults.NumElements() <= 256);
	AssertInt((int)gaiQuaternionResults.NumElements(), TestCPP816RunProject(aszQuaternion, "", NULL, false, auiResults, gaiQuaternionResults.NumElements(), TEST_CPP816_SLOW_STEPS));
	for (i = 0; i < gaiQuaternionResults.NumElements(); i++)
	{
		uiExpected = (uint32)gaiQuaternionResults.GetValue(i);
#ifndef _DEBUG
		//Release is /fp:fast, which can reorder or fuse the native float maths and move its result by an ulp.
		if (gaiQuaternionIsFloat.GetValue(i) && (TestCPP65FloatUlps(auiResults[i], uiExpected) <= 1))
		{
			uiExpected = auiResults[i];
		}
#endif // _DEBUG
		AssertIntHex(uiExpected, auiResults[i]);
	}
	gaiQuaternionIsFloat.Kill();
	gaiQuaternionResults.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// new and delete over Libc65's operator new, operator delete and malloc, as TestCPP65GeneratorNewDelete.
//
//////////////////////////////////////////////////////////////////////////
void TestCPP816NewDelete(void)
{
	static const char*	aszUnits[] = { "Libc65/new.cpp", "Libc65/stdlib.cpp", "BaseLib/TrueMallocator.cpp", "Libc65/string.cpp", "Libc65/ctype.cpp", NULL };

	AssertInt(7, TestCPP816RunProject(aszUnits, "", "int main() { int* p = new int(7); int r = *p; delete p; return r; }\n"));

	AssertInt(2600 + 50 + 5, TestCPP816RunProject(aszUnits, "",
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

	AssertInt(321, TestCPP816RunProject(aszUnits, "",
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

	AssertInt(1000, TestCPP816RunProject(aszUnits, "",
		"int main()\n"
		"{\n"
		"	int n = 0;\n"
		"	for (int i = 0; i < 1000; i++) { int* p = new int[1000]; if (p) n++; delete[] p; }\n"
		"	return n;\n"
		"}\n"));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCPP816(void)
{
	BeginTests();

	TypesInit();
	FastFunctionsInit();
	TypeConverterInit();
	NumberInit();
	CW65C816InstructionFactory::GetInstance()->Init();

	TestCPP816Basics();
	TestCPP816Functions();
	TestCPP816Classes();
	TestCPP816Statements();
	TestCPP816Globals();
	TestCPP816Builtins();
	TestCPP816BaseLib();
	TestCPP816NewDelete();
	TestCPP816Floats();

	CW65C816InstructionFactory::GetInstance()->Kill();
	NumberKill();
	TypeConverterKill();
	FastFunctionsKill();
	TypesKill();

	TestStatistics();
}

