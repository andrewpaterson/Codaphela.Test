#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Assembler65Lib/Asm816Profile.h"
#include "BaseLib/TypeNames.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/NumberControl.h"
#include "BaseLib/ArrayInt.h"
#include "BaseLib/ArrayChars.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/FileBasic.h"
#include "BaseLib/DiskFile.h"
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
#define TEST_CPP816_BASELIB_MEMORY	0x1000000
#define TEST_CPP816_BASELIB_LIMIT	0x1C0000


//Libc65's units for the W65C816 (no 65C64 assembly).
static const char* gaszTestCPP816Libc65[] = { "string.cpp", "string816.asm", "string816_16.asm", "stdlib.cpp", "ctype.cpp", "time.cpp", "math.cpp", "softfloat.cpp", "softfloat816.asm", "new.cpp", "signal.cpp", "stdio.cpp", "host.cpp", NULL };


//////////////////////////////////////////////////////////////////////////
//
// Runs the program a few instructions at a time and counts where it is after each run by the function (the symbol
// in the linker's map at or before the address), then prints the functions it was most often in (W65C816.txt step
// 7).  Returns how many instructions ran.
//
//////////////////////////////////////////////////////////////////////////
size TestCPP816Profile(CCPP65Builder* pcBuilder, CFast65C816* pcFast, size uiMaxSteps)
{
	CArrayTemplate<uint32>	auiAddresses;
	CArrayTemplate<int32>	aiCounts;
	CArrayChars				aszNames;
	const char*				szLine;
	const char*				szName;
	uint32					uiAddress;
	size					uiSteps;
	size					uiRun;
	size					ui;
	size					uiBest;
	int32					iZero;
	int32					iTotal;
	int						iShown;

	//The map's functions in address order: "  $00012345 G Name (object)".
	auiAddresses.Init();
	aszNames.Init();
	aiCounts.Init();
	iZero = 0;
	for (szLine = strstr(pcBuilder->GetMap(), "Symbols\n"); szLine; szLine = strchr(szLine + 1, '\n'))
	{
		if ((szLine[1] == ' ') && (szLine[3] == '$') && ((szLine[13] == 'G') || ((szLine[13] == 'L') && !((szLine[15] == 'L') && (szLine[16] >= '0') && (szLine[16] <= '9')))))
		{
			uiAddress = (uint32)strtoul(&szLine[4], NULL, 16);
			szName = &szLine[15];
			auiAddresses.Add(&uiAddress);
			aszNames.Add(szName, 0, (size)(strchr(szName, ' ') - szName));
			aiCounts.Add(&iZero);
		}
	}

	uiSteps = 0;
	iTotal = 0;
	while ((uiSteps < uiMaxSteps) && !pcFast->IsStopped())
	{
		uiRun = pcFast->Run(97);
		uiSteps += uiRun;
		if (uiRun == 0)
		{
			break;
		}
		uiAddress = pcFast->GetProgramAddress();
		uiBest = (size)-1;
		for (ui = 0; ui < auiAddresses.NumElements(); ui++)
		{
			if ((*auiAddresses.Get(ui) <= uiAddress) && ((uiBest == (size)-1) || (*auiAddresses.Get(ui) >= *auiAddresses.Get(uiBest))))
			{
				uiBest = ui;
			}
		}
		if (uiBest != (size)-1)
		{
			(*aiCounts.Get(uiBest))++;
			iTotal++;
		}
	}

	for (iShown = 0; iShown < 12; iShown++)
	{
		uiBest = 0;
		for (ui = 1; ui < aiCounts.NumElements(); ui++)
		{
			if (*aiCounts.Get(ui) > *aiCounts.Get(uiBest))
			{
				uiBest = ui;
			}
		}
		if ((aiCounts.NumElements() == 0) || (*aiCounts.Get(uiBest) == 0))
		{
			break;
		}
		fprintf(stderr, "CPP816_PROFILE %5.1f%% %s\n", 100.0 * *aiCounts.Get(uiBest) / (iTotal ? iTotal : 1), aszNames.GetText(uiBest));
		*aiCounts.Get(uiBest) = 0;
	}
	aiCounts.Kill();
	aszNames.Kill();
	auiAddresses.Kill();
	return uiSteps;
}


//Memory a test program reads and writes: puiLoad's uiLoadBytes are put at uiLoadAddress before it runs, and the
//uiSaveBytes at uiSaveAddress copied to puiSave after.
struct STestCPP816Memory
{
	const uint8*	puiLoad;
	size			uiLoadBytes;
	uint32			uiLoadAddress;
	uint8*			puiSave;
	size			uiSaveBytes;
	uint32			uiSaveAddress;
};


//////////////////////////////////////////////////////////////////////////
//
// Compiles and links szSource (if given) and the units (TestCPP65AddUnits, without the 65C64 assembly ones) for
// the W65C816 and runs it in CAsm65Memory's 2MB (with psMemory's bytes put in and taken out, if given).  The labels
// in szStubs must be exactly the ones used but defined by no unit.  The first uiResults longs at 0010:0000 are copied
// to puiResults.  It may run uiMaxSteps instructions.  Returns main's int (16 bits, sign extended), or -1000000 if it
// didn't build or stop.
//
//////////////////////////////////////////////////////////////////////////
int32 TestCPP816RunProject(const char** aszUnits, const char* szStubs, const char* szSource, bool bLockstep = false, uint32* puiResults = NULL, size uiResults = 0, size uiMaxSteps = TEST_CPP816_STEPS, bool bBaseLib = false, STestCPP816Memory* psMemory = NULL)
{
	CCPP65Builder	cBuilder;
	CAsm65Memory	cMemory;
	CFast65C816		cFast;
	CAsm816Lockstep	cLockstep;
	CChars			szMissing;
	CChars			szProject;
	CFileUtil		cFileUtil;
	size			uiSteps;
	size			i;
	int32			iResult;
	bool			bResult;

	iResult = -1000000;
	cBuilder.Init();
	cBuilder.SetTarget(CPPT_W65C816);
	TestCPP65AddIncludeDirectories(&cBuilder);
	bResult = cBuilder.AddStartUp();
	szProject.Init(".." _FS_ ".." _FS_ ".." _FS_ "commonlibraries" _FS_ "Libc65");
	cFileUtil.FullPath(&szProject);
	cBuilder.AddMathTables(szProject.Text());
	szProject.Kill();
	if (szSource)
	{
		bResult &= cBuilder.AddSource("Test.cpp", szSource);
	}
	if (aszUnits)
	{
		TestCPP65AddUnits(&cBuilder, aszUnits, false);
	}
	if (bBaseLib)
	{
		//All of BaseLib and Libc65, each unit linked only when it is used.
		szProject.Init(".." _FS_ ".." _FS_ ".." _FS_ "commonlibraries" _FS_ "BaseLib" _FS_ "BaseLib.vcxproj");
		cFileUtil.FullPath(&szProject);
		bResult &= cBuilder.AddVisualStudioProject("BaseLib", szProject.Text(), true);
		szProject.Kill();
		szProject.Init(".." _FS_ ".." _FS_ ".." _FS_ "commonlibraries" _FS_ "Libc65");
		cFileUtil.FullPath(&szProject);
		for (i = 0; gaszTestCPP816Libc65[i]; i++)
		{
			cBuilder.AddUnit("Libc65", szProject.Text(), gaszTestCPP816Libc65[i], true);
		}
		szProject.Kill();

		//A program with BaseLib in it is bigger: it ends below the stack, with the heap above 2MB in 16MB.
		cBuilder.SetLimit(TEST_CPP816_BASELIB_LIMIT);
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
		cMemory.Init(bBaseLib ? TEST_CPP816_BASELIB_MEMORY : ASM65_MEMORY_LOW_SIZE);
		cMemory.Load(cBuilder.GetOutput());
		for (i = 0; psMemory && (i < psMemory->uiLoadBytes); i++)
		{
			cMemory.SetByte(psMemory->uiLoadAddress + (uint32)i, psMemory->puiLoad[i]);
		}
		cMemory.InitFast816(&cFast);
		cFast.Reset();
		if (bLockstep)
		{
			cLockstep.Init(&cMemory, &cFast);
			uiSteps = cLockstep.Run(uiMaxSteps, 64);
			AssertString("", cLockstep.GetDifferences());
			cLockstep.Kill();
		}
		else if (getenv("CPP816_PROFILE"))
		{
			uiSteps = TestCPP816Profile(&cBuilder, &cFast, uiMaxSteps);
		}
		else
		{
			uiSteps = cFast.Run(uiMaxSteps);
		}
		AssertTrue(uiSteps < uiMaxSteps);
		if (getenv("CPP816_STEPS"))
		{
			//How fast the code is (W65C816.txt step 7).
			fprintf(stderr, "CPP816_STEPS %s: %d instructions %d cycles\n", (aszUnits && aszUnits[0]) ? aszUnits[0] : "source", (int)uiSteps, (int)cFast.NumCycles());
		}
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
		for (i = 0; psMemory && (i < psMemory->uiSaveBytes); i++)
		{
			psMemory->puiSave[i] = cMemory.GetByte(psMemory->uiSaveAddress + (uint32)i);
		}
		cFast.Kill();
		cMemory.Kill();
	}
	cBuilder.Kill();
	return iResult;
}


//////////////////////////////////////////////////////////////////////////
//
// Compiles, links and runs szSource, with Libc65's string routines (the optimiser makes loops calls of them).
// Returns main's int (16 bits, sign extended), or -1000000 if it didn't build or stop.
//
//////////////////////////////////////////////////////////////////////////
int32 TestCPP816Run(const char* szSource, bool bLockstep = false)
{
	static const char*	aszUnits[] = { "Libc65/string816.asm", NULL };

	return TestCPP816RunProject(aszUnits, "", szSource, bLockstep);
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

	//Signed / and % by powers of 2 are shifts and adds (negative values round towards 0); the sum was worked out natively.
	AssertInt(7, TestCPP816Run(
		"long Mix(long s, int x) { return s * 3 + x / 2 + x % 2 + x / 4 * 5 + x % 4 * 7 + x / 8 + x % 16 * 11; }\n"
		"long MixLong(long s, long l) { return s * 5 + l / 16 + l % 16 + l / 1024 + l % 2; }\n"
		"int main()\n"
		"{\n"
		"	long s = 0;\n"
		"	for (int i = -1000; i <= 1000; i++) { s = Mix(s, i) & 0xFFFFFFF; }\n"
		"	for (int i = -1000; i <= 1000; i += 7) { s = MixLong(s, (long)i * 99991) & 0xFFFFFFF; }\n"
		"	int x = -32767 - 1; s += x / 2 + x % 4 + x / 16384; x = 32767; s += x / 2 + x % 4 + x / 16384;\n"
		"	long l = -2147483647L - 1; s += l / 2 + l % 8;\n"
		"	return ((s & 0xFFFFFFF) == 259971084L) ? 7 : 1;\n"
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
// Loops that fill, copy, measure or compare memory, which the optimiser
// makes memset, memmove, strlen, memcmp, memchr and strchr calls
// (ReplaceLoopIdioms), give
// what the loops would: a fill of bytes and of 16 bit zeros, a copy of 16 bit
// elements, copies that overlap both ways (a copy up into itself repeats the
// first bytes, as the loop does, so it stays a loop), lengths counted by an
// index and by a pointer, and compares that differ first, in the middle,
// last or not at all, and searches by pointer, by index and to a terminator
// that find the first, middle, last, a zero or nothing.  Returns the answers
// wrong.
//
//////////////////////////////////////////////////////////////////////////
void TestCPP816LoopIdioms(void)
{
	static const char*	aszUnits[] = { "Libc65/string816.asm", NULL };

	AssertInt(0, TestCPP816RunProject(aszUnits, "",
		"unsigned char	gauc[300];\n"
		"short			gas[100];\n"
		"short			gas2[100];\n"
		"void Fill(unsigned char* puc, unsigned char uc, long iCount)\n"
		"{\n"
		"	long	i;\n"
		"	for (i = 0; i < iCount; i++)\n"
		"	{\n"
		"		puc[i] = uc;\n"
		"	}\n"
		"}\n"
		"void Zero(short* ps, unsigned long uiCount)\n"
		"{\n"
		"	unsigned long	i;\n"
		"	for (i = 0; i < uiCount; i++)\n"
		"	{\n"
		"		ps[i] = 0;\n"
		"	}\n"
		"}\n"
		"void Copy(short* psTo, short* psFrom, unsigned long uiCount)\n"
		"{\n"
		"	unsigned long	i;\n"
		"	for (i = 0; i < uiCount; i++)\n"
		"	{\n"
		"		psTo[i] = psFrom[i];\n"
		"	}\n"
		"}\n"
		"int Length(const char* sz)\n"
		"{\n"
		"	int	i;\n"
		"	i = 0;\n"
		"	while (sz[i] != 0)\n"
		"	{\n"
		"		i++;\n"
		"	}\n"
		"	return i;\n"
		"}\n"
		"unsigned long PointerLength(const char* sz)\n"
		"{\n"
		"	const char*	pc;\n"
		"	pc = sz;\n"
		"	while (*pc)\n"
		"	{\n"
		"		pc++;\n"
		"	}\n"
		"	return (unsigned long)(pc - sz);\n"
		"}\n"
		"int Same(unsigned char* puc1, unsigned char* puc2, unsigned long uiCount)\n"
		"{\n"
		"	unsigned long	i;\n"
		"	for (i = 0; i < uiCount; i++)\n"
		"	{\n"
		"		if (puc1[i] != puc2[i])\n"
		"		{\n"
		"			return 0;\n"
		"		}\n"
		"	}\n"
		"	return 1;\n"
		"}\n"
		"const unsigned char* Find(const unsigned char* puc, unsigned char uc, unsigned long uiCount)\n"
		"{\n"
		"	unsigned long	i;\n"
		"	for (i = 0; i < uiCount; i++)\n"
		"	{\n"
		"		if (puc[i] == uc)\n"
		"		{\n"
		"			return &puc[i];\n"
		"		}\n"
		"	}\n"
		"	return 0;\n"
		"}\n"
		"long FindIndex(const unsigned char* puc, unsigned char uc, long iCount)\n"
		"{\n"
		"	long	i;\n"
		"	for (i = 0; i < iCount; i++)\n"
		"	{\n"
		"		if (puc[i] == uc)\n"
		"		{\n"
		"			return i;\n"
		"		}\n"
		"	}\n"
		"	return -1;\n"
		"}\n"
		"const char* Chr(const char* sz, char c)\n"
		"{\n"
		"	while (*sz != c)\n"
		"	{\n"
		"		if (*sz == 0)\n"
		"		{\n"
		"			return 0;\n"
		"		}\n"
		"		sz++;\n"
		"	}\n"
		"	return sz;\n"
		"}\n"
		"void CopyBytes(unsigned char* pucTo, unsigned char* pucFrom, long iCount)\n"
		"{\n"
		"	long	i;\n"
		"	for (i = 0; i < iCount; i++)\n"
		"	{\n"
		"		pucTo[i] = pucFrom[i];\n"
		"	}\n"
		"}\n"
		"int main(void)\n"
		"{\n"
		"	long	i;\n"
		"	int		iWrong;\n"
		"	iWrong = 0;\n"
		"	for (i = 0; i < 300; i++)\n"
		"	{\n"
		"		gauc[i] = 1;\n"
		"	}\n"
		"	Fill(gauc + 3, 9, 200);\n"
		"	for (i = 0; i < 300; i++)\n"
		"	{\n"
		"		iWrong += gauc[i] != (((i >= 3) && (i < 203)) ? 9 : 1);\n"
		"	}\n"
		"	for (i = 0; i < 100; i++)\n"
		"	{\n"
		"		gas[i] = (short)(i * 3 - 50);\n"
		"		gas2[i] = 5;\n"
		"	}\n"
		"	Zero(gas2 + 10, 50);\n"
		"	Copy(gas2 + 70, gas + 20, 25);\n"
		"	for (i = 0; i < 100; i++)\n"
		"	{\n"
		"		iWrong += gas2[i] != (((i >= 10) && (i < 60)) ? 0 : (((i >= 70) && (i < 95)) ? (short)((i - 50) * 3 - 50) : 5));\n"
		"	}\n"
		"	for (i = 0; i < 300; i++)\n"
		"	{\n"
		"		gauc[i] = (unsigned char)i;\n"
		"	}\n"
		"	CopyBytes(gauc + 1, gauc, 100);\n"
		"	CopyBytes(gauc + 150, gauc + 160, 100);\n"
		"	for (i = 0; i < 300; i++)\n"
		"	{\n"
		"		iWrong += gauc[i] != ((i <= 100) ? 0 : (((i >= 150) && (i < 250)) ? (unsigned char)(i + 10) : (unsigned char)i));\n"
		"	}\n"
		"	iWrong += (Length(\"\") != 0) + (Length(\"Hello world\") != 11) + (PointerLength(\"\") != 0) + (PointerLength(\"Hello\") != 5);\n"
		"	for (i = 0; i < 300; i++)\n"
		"	{\n"
		"		gauc[i] = (i == 250) ? 0 : 'a';\n"
		"	}\n"
		"	iWrong += (Length((char*)gauc) != 250) + (PointerLength((char*)gauc + 10) != 240);\n"
		"	iWrong += (Same(gauc, gauc + 1, 200) != 1) + (Same(gauc, gauc + 1, 0) != 1);\n"
		"	gauc[0] = 'b';\n"
		"	iWrong += (Same(gauc, gauc + 1, 200) != 0);\n"
		"	gauc[0] = 'a';\n"
		"	gauc[100] = 'c';\n"
		"	iWrong += (Same(gauc, gauc + 1, 200) != 0) + (Same(gauc + 1, gauc + 2, 98) != 1);\n"
		"	gauc[100] = 'a';\n"
		"	gauc[200] = 'c';\n"
		"	iWrong += (Same(gauc, gauc + 1, 200) != 0) + (Same(gauc, gauc + 1, 199) != 1);\n"
		"	gauc[0] = 'x';\n"
		"	gauc[120] = 'y';\n"
		"	gauc[249] = 'z';\n"
		"	iWrong += (Find(gauc, 'x', 250) != gauc) + (Find(gauc, 'y', 250) != gauc + 120) + (Find(gauc, 'z', 250) != gauc + 249);\n"
		"	iWrong += (Find(gauc, 'z', 249) != 0) + (Find(gauc, 'q', 300) != 0) + (Find(gauc, 'x', 0) != 0) + (Find(gauc + 1, 0, 299) != gauc + 250);\n"
		"	iWrong += (FindIndex(gauc, 'x', 250) != 0) + (FindIndex(gauc, 'y', 250) != 120) + (FindIndex(gauc, 'z', 250) != 249);\n"
		"	iWrong += (FindIndex(gauc, 'z', 249) != -1) + (FindIndex(gauc, 'q', 300) != -1) + (FindIndex(gauc, 'x', 0) != -1);\n"
		"	iWrong += (Chr((char*)gauc, 'x') != (char*)gauc) + (Chr((char*)gauc, 'y') != (char*)gauc + 120) + (Chr((char*)gauc, 'z') != (char*)gauc + 249);\n"
		"	iWrong += (Chr((char*)gauc, 'q') != 0) + (Chr((char*)gauc, 0) != (char*)gauc + 250) + (Chr(\"\", 'a') != 0) + (Chr(\"\", 0) == 0);\n"
		"	return iWrong;\n"
		"}\n"));
}


//////////////////////////////////////////////////////////////////////////
//
// MemSwp in string816.asm (BaseLib's is left out for the W65C816): every
// length from 0 to 40 and 255 to 257, both buffers swapped and the bytes
// after them unchanged.  Returns the bytes wrong.
//
//////////////////////////////////////////////////////////////////////////
void TestCPP816MemSwp(void)
{
	static const char*	aszUnits[] = { "Libc65/string816.asm", NULL };

	AssertInt(0, TestCPP816RunProject(aszUnits, "",
		"void MemSwp(const void* pv1, const void* pv2, unsigned long uiLength);\n"
		"unsigned char gauc1[300];\n"
		"unsigned char gauc2[300];\n"
		"int Check(unsigned long uiLength)\n"
		"{\n"
		"	unsigned long	i;\n"
		"	int				iWrong;\n"
		"	for (i = 0; i < 300; i++)\n"
		"	{\n"
		"		gauc1[i] = (unsigned char)(i + 1);\n"
		"		gauc2[i] = (unsigned char)(i * 3 + 7);\n"
		"	}\n"
		"	MemSwp(gauc1, gauc2, uiLength);\n"
		"	iWrong = 0;\n"
		"	for (i = 0; i < 300; i++)\n"
		"	{\n"
		"		if (gauc1[i] != ((i < uiLength) ? (unsigned char)(i * 3 + 7) : (unsigned char)(i + 1)))\n"
		"		{\n"
		"			iWrong++;\n"
		"		}\n"
		"		if (gauc2[i] != ((i < uiLength) ? (unsigned char)(i + 1) : (unsigned char)(i * 3 + 7)))\n"
		"		{\n"
		"			iWrong++;\n"
		"		}\n"
		"	}\n"
		"	return iWrong;\n"
		"}\n"
		"int main(void)\n"
		"{\n"
		"	unsigned long	ul;\n"
		"	int				iWrong;\n"
		"	iWrong = 0;\n"
		"	for (ul = 0; ul <= 40; ul++)\n"
		"	{\n"
		"		iWrong += Check(ul);\n"
		"	}\n"
		"	iWrong += Check(255) + Check(256) + Check(257);\n"
		"	return iWrong;\n"
		"}\n"));
}


//////////////////////////////////////////////////////////////////////////
//
// BaseLib code with the Libc65 code it needs, as TestCPP65GeneratorBaseLib runs it on the 65C64.
//
//////////////////////////////////////////////////////////////////////////
void TestCPP816BaseLib(void)
{
	static const char*	aszMD5[] = { "BaseLib/MD5.cpp", "Libc65/string.cpp", "Libc65/string816.asm", "Input/CPP65/MD5Project/Main.cpp", NULL };
	static const char*	aszMersenneTwister[] = { "BaseLib/MersenneTwister.cpp", "Libc65/time.cpp", "Input/CPP65/MersenneTwisterProject/Main.cpp", NULL };
	static const char*	aszSort[] = { "BaseLib/QuickSort.cpp", "BaseLib/BubbleSort.cpp", "BaseLib/BinarySearch.cpp", "Input/CPP65/SortProject/MemSwpStub.cpp", "Input/CPP65/SortProject/Main.cpp", NULL };
	static const char*	aszRedBlackTree[] = { "BaseLib/RedBlackTree.cpp", "Libc65/string.cpp", "Libc65/string816.asm", "Libc65/stdlib.cpp", "BaseLib/TrueMallocator.cpp", "Libc65/ctype.cpp", "Input/CPP65/RedBlackTreeProject/FreeListStub.cpp", "Input/CPP65/RedBlackTreeProject/Main.cpp", NULL };
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
// Sprite drawing in C style (Input/CPP65/SpriteProject: Sprite.h and Sprite.cpp as given, Image.cpp's DrawPixel on a
// 320 x 200 byte screen at 0011:0000): a container of an opaque and a transparent sprite, iterated and drawn.  The
// expected values are from the same sources built natively (with DrawPixel on an array): 20 pixels set, 2 images and
// the screen's hash.  DrawPixel is inlined across the units.
//
//////////////////////////////////////////////////////////////////////////
void TestCPP816Sprites(void)
{
	static const char*	aszSprites[] = { "Input/CPP65/SpriteProject/Sprite.cpp", "Input/CPP65/SpriteProject/Image.cpp", "Libc65/string816.asm", "Input/CPP65/SpriteProject/Main.cpp", NULL };
	uint32				auiResults[2];

	CCPP65Builder		cBuilder;
	CChars				szProject;
	CFileUtil			cFileUtil;
	int64				iAddress;

	AssertInt(20, TestCPP816RunProject(aszSprites, "", NULL, true, auiResults, 2));
	AssertIntHex(974038828, auiResults[0]);
	AssertInt(2, auiResults[1]);

	//DrawPixel (Image.cpp) is inlined into DrawSprite (Sprite.cpp, compiled before it, so again at the end) and into
	//nothing else: it is left out of the program.
	cBuilder.Init();
	cBuilder.SetTarget(CPPT_W65C816);
	TestCPP65AddIncludeDirectories(&cBuilder);
	AssertTrue(cBuilder.AddStartUp());
	szProject.Init(".." _FS_ ".." _FS_ ".." _FS_ "commonlibraries" _FS_ "Libc65");
	cFileUtil.FullPath(&szProject);
	cBuilder.AddMathTables(szProject.Text());
	szProject.Kill();
	TestCPP65AddUnits(&cBuilder, aszSprites, false);
	AssertTrue(cBuilder.Link());
	AssertString("", cBuilder.GetErrors());
	AssertTrue(cBuilder.GetSymbol("_DrawSprite__FssPC13SSpriteHeader", &iAddress));
	AssertFalse(cBuilder.GetSymbol("_DrawPixel__Fssh", &iAddress));
	cBuilder.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// Functions inlined across units that name their unit's own symbols (a
// string, a static global, a static local) aren't exported: the names mean
// other things in the unit calling them.
//
//////////////////////////////////////////////////////////////////////////
void TestCPP816LocalSymbols(void)
{
	static const char*	aszUnits[] = { "Input/CPP65/LocalSymbolsProject/Name.cpp", "Libc65/string816.asm", "Input/CPP65/LocalSymbolsProject/Main.cpp", NULL };

	AssertInt(7, TestCPP816RunProject(aszUnits, "", NULL));
}


//////////////////////////////////////////////////////////////////////////
//
// A loop that only steps q and x until x is x0 + d (when d isn't 0) goes:
// q is p + d after it.  x wraps past 65535 in the second call.  And a loop
// counter times a value the loop doesn't change, wrapping.
//
//////////////////////////////////////////////////////////////////////////
void TestCPP816ExitValues(void)
{
	//y * w (16 bit, wrapping past 65535) as a phi stepped by w (ReduceMultiplies).
	AssertInt(-19760,
		TestCPP816Run(
			"unsigned int F(unsigned int y0, unsigned int w, unsigned int n)\n"
			"{\n\tunsigned int s = 0;\n\tfor (unsigned int y = y0; y < n; y++)\n\t{\n\t\ts ^= y * w;\n\t}\n\treturn s;\n}\n"
			"int main(void) { return (int)F(3, 1000, 90); }\n", true));
	AssertInt(-23988,
		TestCPP816Run(
			"unsigned int G(unsigned int y, unsigned int w)\n"
			"{\n\tunsigned int s = 0;\n\tfor (unsigned int i = 0; i < 200; i++)\n\t{\n\t\tif ((i % 3) == 0)\n\t\t{\n\t\t\ty++;\n\t\t}\n\t\ts ^= y * w;\n\t}\n\treturn s;\n}\n"
			"int main(void) { return (int)G(5, 700); }\n", true));
	AssertInt(300 + 2 + 0,
		TestCPP816Run(
			"int Skip(const char* p, unsigned int x0, unsigned int d)\n"
			"{\n\tconst char* q = p;\n\tunsigned int x = x0;\n"
			"\tif (d > 0)\n\t{\n\t\tdo\n\t\t{\n\t\t\tq++;\n\t\t\tx++;\n\t\t} while (x != x0 + d);\n\t}\n"
			"\treturn (int)(q - p);\n}\n"
			"int main(void) { char a[1]; return Skip(a, 65531, 300) + Skip(a, 65535, 2) + Skip(a, 7, 0); }\n", true));
}


//////////////////////////////////////////////////////////////////////////
//
// Optimisations whose IR tests are in TestIR, run: a load isn't moved past
// a store that may write it (SinkLoads), an instruction both ways of an if
// work out is worked out once (HoistCommon), and a loop's counter is
// replaced by the other value it steps (ReplaceLoopCounters), n = 0 too.
//
//////////////////////////////////////////////////////////////////////////
void TestCPP816MovedCode(void)
{
	AssertInt(10,
		TestCPP816Run(
			"int H(int* p, int* q, int f) { int v = *p; if (f) { *q = 5; return v; } return 0; }\n"
			"int main(void) { int a = 1; int r = H(&a, &a, 1) * 10; return r + H(&a, &a, 0); }\n", true));
	AssertInt((3 * 4 + 1 + 100) + (5 * 2 - 1),
		TestCPP816Run(
			"int K(int a, int b, int f) { int c = a < b; int r; if (f) r = a * b + 1; else r = a * b - 1; if (c) r += 100; return r; }\n"
			"int main(void) { return K(3, 4, 1) + K(5, 2, 0); }\n", true));
	AssertInt(3 + 4 + 5 + 6 + 7,
		TestCPP816Run(
			"int L(const char* p, int x0, int n) { int s = 0; int x = x0; for (int i = 0; i < n; i++) { s += p[x]; x++; } return s; }\n"
			"int main(void) { char a[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }; return L(a, 2, 5) + L(a, 0, 0) * 100; }\n", true));
}


//////////////////////////////////////////////////////////////////////////
//
// BaseLib units compiled for the W65C816 without errors: the IR of each
// function verifies after the optimiser (Float32Vec2TransformCoords's two
// muls of its counter once read a moved instruction's result, and the
// first parameter was replaced).
//
//////////////////////////////////////////////////////////////////////////
void TestCPP816CompileBaseLibUnits(void)
{
	static const char*	aszUnits[] = { "BaseLib/Float32Vec2.cpp", "BaseLib/Float32Vec3.cpp", "BaseLib/Float32Vec4.cpp", NULL };
	CCPP65Builder		cBuilder;

	cBuilder.Init();
	cBuilder.SetTarget(CPPT_W65C816);
	TestCPP65AddIncludeDirectories(&cBuilder);
	TestCPP65AddUnits(&cBuilder, aszUnits, false);
	cBuilder.Link();
	AssertString("", cBuilder.GetErrors());
	cBuilder.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// A restrict global pointer promises that what it reaches isn't reached
// another way.  Here it breaks the promise, pointing at the int the loop
// reads: with __restrict the read leaves the loop and sees the int before
// the stores (0x101 three times); without it each read sees them (0x100,
// then 0, then 0).
//
//////////////////////////////////////////////////////////////////////////
void TestCPP816Restrict(void)
{
	static const char*	szSource =
		"int giWidth;\n"
		"unsigned char* RESTRICT gpuMemory;\n"
		"int Sum(int n) { int s = 0; for (int i = 0; i < n; i++) { gpuMemory[i] = 0; s += giWidth; } return s; }\n"
		"int main(void) { gpuMemory = (unsigned char*)&giWidth; giWidth = 0x101; return Sum(3); }\n";
	CChars	szRestrict;
	CChars	szPlain;

	szRestrict.Init("#define RESTRICT __restrict\n");
	szRestrict.Append(szSource);
	szPlain.Init("#define RESTRICT\n");
	szPlain.Append(szSource);
	AssertInt(0x303, TestCPP816Run(szRestrict.Text()));
	AssertInt(0x100, TestCPP816Run(szPlain.Text()));
	szPlain.Kill();
	szRestrict.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// A restrict parameter breaking its promise in the same way: p is giWidth.
// Sum is called through a volatile pointer so it isn't inlined (restrict is
// dropped then).
//
//////////////////////////////////////////////////////////////////////////
void TestCPP816RestrictParameter(void)
{
	static const char*	szSource =
		"int giWidth;\n"
		"int Sum(unsigned char* RESTRICT p, int n) { int s = 0; for (int i = 0; i < n; i++) { p[i] = 0; s += giWidth; } return s; }\n"
		"int (* volatile gpfSum)(unsigned char*, int) = Sum;\n"
		"int main(void) { giWidth = 0x101; return gpfSum((unsigned char*)&giWidth, 3); }\n";
	CChars	szRestrict;
	CChars	szPlain;

	szRestrict.Init("#define RESTRICT __restrict\n");
	szRestrict.Append(szSource);
	szPlain.Init("#define RESTRICT\n");
	szPlain.Append(szSource);
	AssertInt(0x303, TestCPP816Run(szRestrict.Text()));
	AssertInt(0x100, TestCPP816Run(szPlain.Text()));
	szPlain.Kill();
	szRestrict.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// Tide/Video's sprites (Input/CPP65/TideVideoProject: Image.c, Image.h, Sprite.c and Sprite.h as they are but for
// guiImageMemory declared __restrict, Main.c as MainSprites.c without its font and heap) drawn from Input/SFT/Graphics.sft (put at 0008:0000) into an 8 bit
// 320 x 200 screen at 0011:0000: the background, Maki standing and walking (clipped at both sides).  The expected
// hash is the same sources built natively; the screen is saved to Output/Graphics.raw.  DrawPixel, which reads
// globals, is inlined across the units.
//
//////////////////////////////////////////////////////////////////////////
void TestCPP816TideVideo(void)
{
	static const char*	aszUnits[] = { "Input/CPP65/TideVideoProject/Image.c", "Input/CPP65/TideVideoProject/Sprite.c", "Libc65/string816.asm", "Input/CPP65/TideVideoProject/Main.c", NULL };
	STestCPP816Memory	sMemory;
	CFileBasic			cFile;
	CFileUtil			cFileUtil;
	CCPP65Builder		cBuilder;
	CChars				szProject;
	int64				iAddress;
	uint8*				puiSft;
	uint8*				puiScreen;
	size				uiSftBytes;
	uint32				auiResults[2];

	cFile.Init(DiskFile("Input" _FS_ "SFT" _FS_ "Graphics.sft"));
	AssertTrue(cFile.Open(EFM_Read));
	uiSftBytes = (size)cFile.Size();
	AssertInt(77719, (int)uiSftBytes);
	puiSft = (uint8*)malloc(uiSftBytes);
	AssertInt(1, (int)cFile.Read(puiSft, uiSftBytes, 1));
	cFile.Close();
	cFile.Kill();

	puiScreen = (uint8*)malloc(320 * 200);
	sMemory.puiLoad = puiSft;
	sMemory.uiLoadBytes = uiSftBytes;
	sMemory.uiLoadAddress = 0x080000;
	sMemory.puiSave = puiScreen;
	sMemory.uiSaveBytes = 320 * 200;
	sMemory.uiSaveAddress = 0x110000;
	AssertInt(8, TestCPP816RunProject(aszUnits, "", NULL, false, auiResults, 2, TEST_CPP816_STEPS, false, &sMemory));
	AssertIntHex(0xD06A69C6, auiResults[0]);
	AssertInt(8, auiResults[1]);

	cFileUtil.MakeDir("Output");
	cFile.Init(DiskFile("Output" _FS_ "Graphics.raw"));
	AssertTrue(cFile.Open(EFM_Write_Create));
	cFile.Write(puiScreen, 320 * 200, 1);
	cFile.Close();
	cFile.Kill();
	free(puiScreen);
	free(puiSft);

	//DrawPixel (Image.c, which reads Image.c's globals) is inlined into DrawSprite (Sprite.c) across the units, the
	//globals named the same: it is left out of the program.
	cBuilder.Init();
	cBuilder.SetTarget(CPPT_W65C816);
	TestCPP65AddIncludeDirectories(&cBuilder);
	AssertTrue(cBuilder.AddStartUp());
	szProject.Init(".." _FS_ ".." _FS_ ".." _FS_ "commonlibraries" _FS_ "Libc65");
	cFileUtil.FullPath(&szProject);
	cBuilder.AddMathTables(szProject.Text());
	szProject.Kill();
	TestCPP65AddUnits(&cBuilder, aszUnits, false);
	AssertTrue(cBuilder.Link());
	AssertString("", cBuilder.GetErrors());
	AssertTrue(cBuilder.GetSymbol("_DrawSprite__FssPC13SSpriteHeader", &iAddress));
	AssertTrue(cBuilder.GetSymbol("_guiImageWidth", &iAddress));
	AssertFalse(cBuilder.GetSymbol("_DrawPixel__Fssh", &iAddress));
	cBuilder.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// BaseLib's FloatHelper and SQuaternion with softfloat.cpp (and math.cpp) compiled for the W65C816, against the
// same calls natively, as on the 65C64.
//
//////////////////////////////////////////////////////////////////////////
void TestCPP816Floats(void)
{
	static const char*	aszFloatHelper[] = { "BaseLib/FloatHelper.cpp", "Libc65/softfloat.cpp", "Libc65/softfloat816.asm", "Libc65/math.cpp", "Libc65/string816.asm", "Input/CPP65/FloatHelperProject/Main.cpp", NULL };
	static const char*	aszQuaternion[] = { "BaseLib/Quaternion.cpp", "Libc65/softfloat.cpp", "Libc65/softfloat816.asm", "Libc65/string816.asm", "Input/CPP65/QuaternionProject/Main.cpp", NULL };
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
	static const char*	aszUnits[] = { "Libc65/new.cpp", "Libc65/stdlib.cpp", "BaseLib/TrueMallocator.cpp", "Libc65/string.cpp", "Libc65/string816.asm", "Libc65/ctype.cpp", NULL };

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

	//new T() and new T{} value initialise: a class without constructors of its own is zeroed (arrays in it too), in
	//place or (big ones) with memset, before a member's constructor runs.  The heap block is dirtied first.
	AssertInt(7, TestCPP816RunProject(aszUnits, "",
		"#include <stdlib.h>\n"
		"#include <string.h>\n"
		"struct SPlain { int a; long b[4]; };\n"
		"struct SBig { long c[40]; };\n"
		"class CMember { public: int m; CMember() { m = 7; } };\n"
		"struct SMixed { CMember cm; long d[3]; };\n"
		"void Dirty(int n) { void* p = malloc(n); memset(p, 0x55, n); free(p); }\n"
		"int main()\n"
		"{\n"
		"	int r = 0;\n"
		"	Dirty(sizeof(SPlain));\n"
		"	SPlain* a = new SPlain();\n"
		"	if ((a->a != 0) || (a->b[0] != 0) || (a->b[3] != 0)) r |= 1;\n"
		"	Dirty(sizeof(SBig));\n"
		"	SBig* b = new SBig{};\n"
		"	if ((b->c[0] != 0) || (b->c[39] != 0)) r |= 2;\n"
		"	Dirty(sizeof(SMixed));\n"
		"	SMixed* c = new SMixed();\n"
		"	if ((c->d[0] != 0) || (c->d[2] != 0)) r |= 4;\n"
		"	if (c->cm.m != 7) r |= 8;\n"
		"	delete a;\n"
		"	delete b;\n"
		"	delete c;\n"
		"	return r + 7;\n"
		"}\n"));
}


//////////////////////////////////////////////////////////////////////////
//
// Bugs found running TestBaseLib on the W65C816.
//
//////////////////////////////////////////////////////////////////////////
void TestCPP816TestBaseLibBugs(void)
{
	//Pointers compare as 24 bit addresses (across banks).
	AssertInt(1 + 2 + 4 + 8 + 16, TestCPP816Run(
		"int Compare(char* pa, char* pb, char* pc)\n"
		"{\n"
		"\treturn (pa < pb) + (pb > pa) * 2 + (pc >= pa) * 4 + (pa <= pb) * 8 + ((pc >= pa) && (pc < pb)) * 16;\n"
		"}\n"
		"int main(void) { return Compare((char*)0x1FFF0, (char*)0x30010, (char*)0x20005); }\n"));

	static const char*	aszMersenneTwister[] = { "BaseLib/MersenneTwister.cpp", "Libc65/time.cpp", NULL };

	//CMersenneTwister::Next(int, int) gives the same numbers as natively (18248 is the native checksum).
	AssertInt(18248, TestCPP816RunProject(aszMersenneTwister, "",
		"#include \"BaseLib/MersenneTwister.h\"\n"
		"int main()\n"
		"{\n"
		"\tCMersenneTwister c;\n"
		"\tint s = 0;\n"
		"\tc.Init(3456897);\n"
		"\tfor (int i = 0; i < 100; i++) { int a = c.Next(0, 580 - i); int b = c.Next(0, 2); s = (s * 31 + a * 3 + b) & 0x7FFF; }\n"
		"\treturn s;\n"
		"}\n", false, NULL, 0, TEST_CPP816_SLOW_STEPS));

	//An object whose copy isn't its bytes is passed by the address of a copy the caller makes and destroys.
	AssertInt(7 + 2 * 10 + 2 * 100 + 9 * 1000, TestCPP816Run(
		"int giCopies;\n"
		"int giGone;\n"
		"class CHeld\n"
		"{\n"
		"public:\n"
		"\tint\tmi;\n"
		"\tCHeld(int i) { mi = i; }\n"
		"\tCHeld(const CHeld& c) { mi = c.mi; giCopies++; }\n"
		"\t~CHeld() { giGone++; }\n"
		"};\n"
		"int Value(CHeld c, int iAdd) { int i = c.mi + iAdd; c.mi = 1000; return i; }\n"
		"int main(void)\n"
		"{\n"
		"\tint r;\n"
		"\tint s;\n"
		"\t{\n"
		"\t\tCHeld h(5);\n"
		"\t\tr = Value(h, 2);\n"
		"\t\ts = Value(h, 4) + h.mi - 5;\n"
		"\t}\n"
		"\treturn r + giCopies * 10 + (giGone - 1) * 100 + s * 1000;\n"
		"}\n"));

	AssertInt(1 + 20, TestCPP816RunProject(NULL, "",
		"#include <string.h>\n"
		"#include \"BaseLib/TypeConverter.h\"\n"
		"#include \"BaseLib/NumberControl.h\"\n"
		"#include \"BaseLib/Calculator.h\"\n"
		"#include \"BaseLib/CalculatorParser.h\"\n"
		"int Eval(const char* sz, const char* szExpected)\n"
		"{\n"
		"\tCCalculator\t\t\tcCalculator;\n"
		"\tCCalculatorParser\tcParser;\n"
		"\tCNumber\t\t\t\tcResult;\n"
		"\tCCalcExpression*\tpcExpression;\n"
		"\tCCalculatorSymbols\tcSymbols;\n"
		"\tCChars\t\t\t\tszResult;\n"
		"\tint\t\t\t\t\tiSame;\n"
		"\tcSymbols.Init(false);\n"
		"\tcCalculator.Init(&cSymbols);\n"
		"\tcParser.Init(&cCalculator);\n"
		"\tpcExpression = (CCalcExpression*)cParser.Parse(sz);\n"
		"\tcParser.Kill();\n"
		"\tcResult = cCalculator.Eval(pcExpression);\n"
		"\tszResult.Init();\n"
		"\tcResult.Print(&szResult);\n"
		"\tiSame = strcmp(szResult.Text(), szExpected) == 0;\n"
		"\tszResult.Kill();\n"
		"\tcCalculator.Kill();\n"
		"\tdelete pcExpression;\n"
		"\tcSymbols.Kill();\n"
		"\treturn iSame;\n"
		"}\n"
		"int main(void)\n"
		"{\n"
		"\tTypeConverterInit();\n"
		"\tNumberInit();\n"
		"\treturn Eval(\"-1\", \"-1\") + Eval(\"1 == -1\", \"0\") * 20;\n"
		"}\n", false, NULL, 0, TEST_CPP816_SLOW_STEPS, true));

	AssertInt(3 + 40 + 500, TestCPP816RunProject(NULL, "",
		"long double Half(long double ld) { return ld / 2.0L; }\n"
		"int main(void)\n"
		"{\n"
		"\tlong double ld = 1.5;\n"
		"\tdouble d = (double)(ld * 2);\n"
		"\tlong double l2 = 0.0L;\n"
		"\tl2 = l2 * 10 + 4;\n"
		"\treturn (int)d + (int)(l2 * 10) + (int)(Half(1000.0L));\n"
		"}\n", false, NULL, 0, TEST_CPP816_STEPS, true));

	AssertInt(14, TestCPP816RunProject(NULL, "",
		"#include \"BaseLib/Number.h\"\n"
		"#include \"BaseLib/NumberControl.h\"\n"
		"int main(void)\n"
		"{\n"
		"\tCNumber\ta;\n"
		"\tCNumber\tb;\n"
		"\tNumberInit();\n"
		"\ta.Init(100);\n"
		"\tb.Init(7);\n"
		"\ta.Divide(&b);\n"
		"\treturn a.IntValue();\n"
		"}\n", false, NULL, 0, TEST_CPP816_SLOW_STEPS, true));
	AssertInt(1, TestCPP816RunProject(NULL, "",
		"#include <string.h>\n"
		"#include \"BaseLib/FloatPrinter.h\"\n"
		"#include \"BaseLib/NumberControl.h\"\n"
		"int main(void)\n"
		"{\n"
		"\tchar\tsz[64];\n"
		"\tNumberInit();\n"
		"\tDoubleToString(sz, 64, 345.34, 2);\n"
		"\treturn strcmp(sz, \"345.34\") == 0;\n"
		"}\n", false, NULL, 0, TEST_CPP816_SLOW_STEPS, true));
	AssertInt(1 + 20 + 300, TestCPP816RunProject(NULL, "",
		"#include \"BaseLib/Number.h\"\n"
		"#include \"BaseLib/NumberControl.h\"\n"
		"int main(void)\n"
		"{\n"
		"\tCNumber\ta;\n"
		"\tCNumber\tb;\n"
		"\tNumberInit();\n"
		"\ta.Init(1);\n"
		"\tb.Init(-1);\n"
		"\treturn (a.Equals(&b) ? 0 : 1) + (b.IsNegative() ? 20 : 0) + ((b.IntValue() == -1) ? 300 : 0);\n"
		"}\n", false, NULL, 0, TEST_CPP816_SLOW_STEPS, true));

	static const char*	aszFloat[] = { "Libc65/softfloat.cpp", "Libc65/softfloat816.asm", NULL };

	AssertInt(0x407, TestCPP816RunProject(aszFloat, "",
		"int Exponent(double f, int iShift)\n"
		"{\n"
		"\tunsigned char* pui = (unsigned char*)&f;\n"
		"\treturn (int)((*((long long*)pui) & 0x7ff0000000000000) >> iShift);\n"
		"}\n"
		"int main(void) { return Exponent(345.34, 52); }\n"));
	AssertInt(0x407, TestCPP816RunProject(aszFloat, "",
		"template<class FLOAT, class INTEGER>\n"
		"int Exponent(FLOAT f, INTEGER iMask, int iShift)\n"
		"{\n"
		"\tunsigned char* pui = (unsigned char*)&f;\n"
		"\treturn (int)((*((INTEGER*)pui) & iMask) >> iShift);\n"
		"}\n"
		"int main(void) { return Exponent<double, long long>(345.34, 0x7ff0000000000000, 52); }\n"));

	AssertInt(8 + 7 * 10, TestCPP816Run(
		"int main(void)\n"
		"{\n"
		"\tunion { long long i64; signed char ia8[8]; };\n"
		"\ti64 = 0x0102030405060708LL;\n"
		"\treturn ia8[0] + ia8[1] * 10;\n"
		"}\n"));
	AssertInt(8 + 7 * 10, TestCPP816Run(
		"int main(void)\n"
		"{\n"
		"\tlong long i64;\n"
		"\ti64 = 0x0102030405060708LL;\n"
		"\tsigned char* p = (signed char*)&i64;\n"
		"\treturn p[0] + p[1] * 10;\n"
		"}\n"));
}


//////////////////////////////////////////////////////////////////////////
//
// Shifts by constants (whole words moved, then a byte, then the bits) of
// 16, 32 and 64 bit values, signed and unsigned, positive and negative (and
// the edges), by every amount, against the same shifts natively.
//
//////////////////////////////////////////////////////////////////////////
void TestCPP816ConstantShifts(void)
{
	static const uint16	aui16[] = { 0x9AB1, 0x5A3C, 0x8000, 0x7FFF, 0xFFFF };
	static const uint32	aui32[] = { 0x9ABCDEF1, 0x5ABCDEF1, 0x80000000, 0xFFFFFFFF };
	static const uint64	aui64[] = { 0x9ABCDEF123456789ULL, 0x1ABCDEF123456789ULL };
	CChars				szSource;
	int					i;
	size				uiValue;
	uint16				ui16;
	int16				i16;
	uint32				ui32;
	int32				i32;
	uint64				ui64;
	int64				i64;
	uint32				uiSum;

	uiSum = 0;
	szSource.Init("volatile unsigned short gui16;\nvolatile short gi16;\nvolatile unsigned long gui32;\nvolatile long gi32;\nvolatile unsigned long long gui64;\nvolatile long long gi64;\n");
	szSource.Append("unsigned long s = 0;\n");
	for (uiValue = 0; uiValue < sizeof(aui16) / sizeof(uint16); uiValue++)
	{
		ui16 = aui16[uiValue];
		i16 = (int16)aui16[uiValue];
		szSource.Append("void Shift16_")->Append((int)uiValue)->Append("(void)\n{\n\tgui16 = ")->Append((int)ui16)->Append("U;\n\tgi16 = (short)")->Append((int)ui16)->Append("U;\n");
		for (i = 1; i < 16; i++)
		{
			uiSum = uiSum * 3 + (uint16)(ui16 << i) + (uint16)(ui16 >> i) + (uint16)(i16 >> i);
			szSource.Append("\ts = s * 3 + (unsigned short)(gui16 << ")->Append(i)->Append(") + (unsigned short)(gui16 >> ")->Append(i)->Append(") + (unsigned short)(gi16 >> ")->Append(i)->Append(");\n");
		}
		szSource.Append("}\n");
	}
	for (uiValue = 0; uiValue < sizeof(aui32) / sizeof(uint32); uiValue++)
	{
		ui32 = aui32[uiValue];
		i32 = (int32)aui32[uiValue];
		szSource.Append("void Shift32_")->Append((int)uiValue)->Append("(void)\n{\n\tgui32 = ")->Append((int64)ui32)->Append("UL;\n\tgi32 = (long)")->Append((int64)ui32)->Append("UL;\n");
		for (i = 1; i < 32; i++)
		{
			uiSum = uiSum * 3 + (ui32 << i) + (ui32 >> i) + (uint32)(i32 >> i);
			szSource.Append("\ts = s * 3 + (gui32 << ")->Append(i)->Append(") + (gui32 >> ")->Append(i)->Append(") + (unsigned long)(gi32 >> ")->Append(i)->Append(");\n");
		}
		szSource.Append("}\n");
	}
	for (uiValue = 0; uiValue < sizeof(aui64) / sizeof(uint64); uiValue++)
	{
		ui64 = aui64[uiValue];
		i64 = (int64)aui64[uiValue];
		szSource.Append("void Shift64_")->Append((int)uiValue)->Append("(void)\n{\n\tgui64 = ")->Append((int64)(ui64 >> 32))->Append("ULL << 32 | ")->Append((int64)(ui64 & 0xFFFFFFFF))->Append("ULL;\n\tgi64 = (long long)gui64;\n");
		for (i = 1; i < 64; i++)
		{
			uiSum = uiSum * 5 + (uint32)(ui64 << i) + (uint32)((ui64 << i) >> 32) + (uint32)(ui64 >> i) + (uint32)((ui64 >> i) >> 32) + (uint32)(i64 >> i) + (uint32)((i64 >> i) >> 32);
			szSource.Append("\ts = s * 5 + (unsigned long)(gui64 << ")->Append(i)->Append(") + (unsigned long)((gui64 << ")->Append(i)->Append(") >> 32) + (unsigned long)(gui64 >> ")->Append(i)->Append(") + (unsigned long)((gui64 >> ")->Append(i)->Append(") >> 32) + (unsigned long)(gi64 >> ")->Append(i)->Append(") + (unsigned long)((gi64 >> ")->Append(i)->Append(") >> 32);\n");
		}
		szSource.Append("}\n");
	}
	szSource.Append("int main(void)\n{\n");
	for (uiValue = 0; uiValue < sizeof(aui16) / sizeof(uint16); uiValue++)
	{
		szSource.Append("\tShift16_")->Append((int)uiValue)->Append("();\n");
	}
	for (uiValue = 0; uiValue < sizeof(aui32) / sizeof(uint32); uiValue++)
	{
		szSource.Append("\tShift32_")->Append((int)uiValue)->Append("();\n");
	}
	for (uiValue = 0; uiValue < sizeof(aui64) / sizeof(uint64); uiValue++)
	{
		szSource.Append("\tShift64_")->Append((int)uiValue)->Append("();\n");
	}
	szSource.Append("\treturn (int)(s ^ (s >> 16)) & 0x7FFF;\n}\n");
	AssertInt((int)((uiSum ^ (uiSum >> 16)) & 0x7FFF), TestCPP816Run(szSource.Text()));
	szSource.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// Shifts by counts known only when they run (word, byte and the jump into
// the unrolled bit steps, or the loop in memory for 64 bits) of 8, 16, 32
// and 64 bit values, signed and unsigned, by every count from 0 to the
// width less one, against the same shifts natively.
//
//////////////////////////////////////////////////////////////////////////
void TestCPP816VariableShifts(void)
{
	static const uint16	aui16[] = { 0x9AB1, 0x5A3C, 0x8000, 0x7FFF, 0xFFFF };
	static const uint32	aui32[] = { 0x9ABCDEF1, 0x5ABCDEF1, 0x80000000, 0xFFFFFFFF };
	static const uint64	aui64[] = { 0x9ABCDEF123456789ULL, 0x1ABCDEF123456789ULL };
	static const uint8	aui8[] = { 0x9A, 0x5C, 0x80, 0xFF };
	CChars				szSource;
	int					i;
	size				uiValue;
	uint32				uiSum;

	uiSum = 0;
	szSource.Init("unsigned short aui16[] = { 0x9AB1, 0x5A3C, 0x8000, 0x7FFF, 0xFFFF };\n");
	szSource.Append("unsigned long aui32[] = { 0x9ABCDEF1, 0x5ABCDEF1, 0x80000000, 0xFFFFFFFF };\n");
	szSource.Append("unsigned long long aui64[] = { 0x9ABCDEF123456789ULL, 0x1ABCDEF123456789ULL };\n");
	szSource.Append("unsigned char aui8[] = { 0x9A, 0x5C, 0x80, 0xFF };\n");
	szSource.Append("volatile int giCount;\n");
	szSource.Append("int main(void)\n{\n\tunsigned long s;\n\tint v;\n\tint i;\n\ts = 0;\n");
	szSource.Append("\tfor (v = 0; v < 5; v++) { for (i = 0; i < 16; i++) { giCount = i; s = s * 3 + (unsigned short)(aui16[v] << giCount) + (unsigned short)(aui16[v] >> giCount) + (unsigned short)((short)aui16[v] >> giCount); } }\n");
	szSource.Append("\tfor (v = 0; v < 4; v++) { for (i = 0; i < 32; i++) { giCount = i; s = s * 3 + (aui32[v] << giCount) + (aui32[v] >> giCount) + (unsigned long)((long)aui32[v] >> giCount); } }\n");
	szSource.Append("\tfor (v = 0; v < 2; v++) { for (i = 0; i < 64; i++) { giCount = i; s = s * 5 + (unsigned long)(aui64[v] << giCount) + (unsigned long)((aui64[v] << giCount) >> 32) + (unsigned long)(aui64[v] >> giCount) + (unsigned long)((long long)aui64[v] >> giCount); } }\n");
	szSource.Append("\tfor (v = 0; v < 4; v++) { for (i = 0; i < 8; i++) { giCount = i; s = s * 3 + (unsigned char)(aui8[v] << giCount) + (unsigned char)(aui8[v] >> giCount) + (unsigned char)((signed char)aui8[v] >> giCount); } }\n");
	szSource.Append("\treturn (int)(s ^ (s >> 16)) & 0x7FFF;\n}\n");

	for (uiValue = 0; uiValue < sizeof(aui16) / sizeof(uint16); uiValue++)
	{
		for (i = 0; i < 16; i++)
		{
			uiSum = uiSum * 3 + (uint16)(aui16[uiValue] << i) + (uint16)(aui16[uiValue] >> i) + (uint16)((int16)aui16[uiValue] >> i);
		}
	}
	for (uiValue = 0; uiValue < sizeof(aui32) / sizeof(uint32); uiValue++)
	{
		for (i = 0; i < 32; i++)
		{
			uiSum = uiSum * 3 + (aui32[uiValue] << i) + (aui32[uiValue] >> i) + (uint32)((int32)aui32[uiValue] >> i);
		}
	}
	for (uiValue = 0; uiValue < sizeof(aui64) / sizeof(uint64); uiValue++)
	{
		for (i = 0; i < 64; i++)
		{
			uiSum = uiSum * 5 + (uint32)(aui64[uiValue] << i) + (uint32)((aui64[uiValue] << i) >> 32) + (uint32)(aui64[uiValue] >> i) + (uint32)((int64)aui64[uiValue] >> i);
		}
	}
	for (uiValue = 0; uiValue < sizeof(aui8) / sizeof(uint8); uiValue++)
	{
		for (i = 0; i < 8; i++)
		{
			uiSum = uiSum * 3 + (uint8)(aui8[uiValue] << i) + (uint8)(aui8[uiValue] >> i) + (uint8)((int8)aui8[uiValue] >> i);
		}
	}
	AssertInt((int)((uiSum ^ (uiSum >> 16)) & 0x7FFF), TestCPP816Run(szSource.Text(), true));
	szSource.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// Explicit destructor calls (with placement new, as an object is made and
// destroyed in memory the caller owns): through a pointer, through a base
// pointer to a virtual destructor, on a named object, and of a class without
// a destructor (nothing happens).
//
//////////////////////////////////////////////////////////////////////////
void TestCPP816DestructorCalls(void)
{
	AssertInt(1 + 20 + 300 + 4000, TestCPP816RunProject(NULL, "",
		"#include <new>\n"
		"int giDestroyed = 0;\n"
		"class CPlain { public: int mi; ~CPlain() { giDestroyed += mi; } };\n"
		"class CBase { public: virtual ~CBase() { giDestroyed += 1000; } };\n"
		"class CDerived : public CBase { public: ~CDerived() { giDestroyed += 3000; } };\n"
		"class CTrivial { public: int mi; };\n"
		"int main(void)\n"
		"{\n"
		"\tlong\t\talBuffer[8];\n"
		"\tCPlain*\t\tpcPlain;\n"
		"\tCBase*\t\tpcBase;\n"
		"\tCTrivial*\tpcTrivial;\n"
		"\tpcPlain = new(alBuffer) CPlain;\n"
		"\tpcPlain->mi = 1;\n"
		"\tpcPlain->~CPlain();\n"
		"\tpcPlain = new(alBuffer) CPlain;\n"
		"\tpcPlain->mi = 20;\n"
		"\t(*pcPlain).~CPlain();\n"
		"\tpcPlain = new(alBuffer) CPlain;\n"
		"\tpcPlain->mi = 300;\n"
		"\tpcPlain->CPlain::~CPlain();\n"
		"\tpcBase = new(alBuffer) CDerived;\n"
		"\tpcBase->~CBase();\n"
		"\tpcTrivial = new(alBuffer) CTrivial;\n"
		"\tpcTrivial->~CTrivial();\n"
		"\treturn giDestroyed;\n"
		"}\n"));
}


//////////////////////////////////////////////////////////////////////////
//
// Builds and runs szSource on the W65C816 with pcProfile guiding it (NULL
// for none), profiling the run into pcMeasure (NULL to not) with the
// program's line table.  Returns main's result and its cycles, and the
// program's map in pszMap (when not NULL).
//
//////////////////////////////////////////////////////////////////////////
int32 TestCPP816RunProfiled(const char* szSource, CAsm816Profile* pcProfile, CAsm816Profile* pcMeasure, uint64* puiCycles, CChars* pszMap = NULL)
{
	static const char*	aszUnits[] = { "Libc65/string816.asm", NULL };
	CCPP65Builder		cBuilder;
	CAsm65Memory		cMemory;
	CFast65C816			cFast;
	CChars				szProject;
	CFileUtil			cFileUtil;
	int32				iResult;

	iResult = -1000000;
	cBuilder.Init();
	cBuilder.SetTarget(CPPT_W65C816);
	cBuilder.SetFrameProfile(pcProfile);
	cBuilder.SetLineTable(pcMeasure != NULL);
	TestCPP65AddIncludeDirectories(&cBuilder);
	AssertTrue(cBuilder.AddStartUp());
	szProject.Init(".." _FS_ ".." _FS_ ".." _FS_ "commonlibraries" _FS_ "Libc65");
	cFileUtil.FullPath(&szProject);
	cBuilder.AddMathTables(szProject.Text());
	szProject.Kill();
	AssertTrue(cBuilder.AddSource("Test.cpp", szSource));
	TestCPP65AddUnits(&cBuilder, aszUnits, false);
	AssertTrue(cBuilder.Link());
	AssertString("", cBuilder.GetErrors());
	if (pszMap)
	{
		pszMap->Append(cBuilder.GetMap());
	}

	cMemory.Init(ASM65_MEMORY_LOW_SIZE);
	cMemory.Load(cBuilder.GetOutput());
	cMemory.InitFast816(&cFast);
	cFast.Reset();
	if (pcMeasure)
	{
		pcMeasure->Run(&cMemory, &cFast, cBuilder.GetMap(), TEST_CPP816_STEPS, cBuilder.GetLineTable());
	}
	else
	{
		cFast.Run(TEST_CPP816_STEPS);
	}
	AssertTrue(cFast.IsStopped());
	if (cFast.IsStopped())
	{
		iResult = (int16)cFast.GetC();
	}
	*puiCycles = cFast.NumCycles();
	cFast.Kill();
	cMemory.Kill();
	cBuilder.Kill();
	return iResult;
}


//////////////////////////////////////////////////////////////////////////
//
// A profile by line: a call's line counts how often it ran, in the
// function it is in.  With the profile the hot call (in the loop) of a
// function too big to inline without one is inlined; the cold one isn't.
// A function compiled from other code since (another fingerprint) starts
// its profile again.
//
//////////////////////////////////////////////////////////////////////////
void TestCPP816ProfileGuidedInlining(void)
{
	static const char*	szSource =
		"int Mix(int a, int b)\n"
		"{\n"
		"\tint x = a * 3 + b;\n"
		"\tx ^= (x >> 2); x += a & 7; x -= b | 5; x ^= x << 1;\n"
		"\tx += a * b; x ^= (b >> 3); x += 11; x -= a; x ^= 0x55;\n"
		"\tx += b * 5; x ^= (a >> 1); x += (b & 3) * 9; x ^= (x >> 4);\n"
		"\tx += a ^ b; x -= (a | b) >> 2; x ^= (b << 2); x += (a & b) * 7;\n"
		"\treturn x;\n"
		"}\n"
		"int main()\n"
		"{\n"
		"\tint r = 0;\n"
		"\tfor (int i = 0; i < 2000; i++)\n"
		"\t{\n"
		"\t\tr += Mix(i, r & 255);\n"
		"\t}\n"
		"\tr += Mix(r, 3);\n"
		"\treturn r;\n"
		"}\n";
	CAsm816Profile			cProfile;
	CAsm816Profile			cGuided;
	SAsm816FunctionProfile*	psMix;
	SAsm816FunctionProfile*	psMain;
	int32					iResult;
	uint64					uiPlain;
	uint64					uiGuided;

	cProfile.Init();
	iResult = TestCPP816RunProfiled(szSource, NULL, &cProfile, &uiPlain);
	psMix = cProfile.Get("_Mix__Fss");
	AssertNotNull((void*)psMix);
	AssertLong(2001, psMix ? (int64)psMix->ulliCalls : 0);
	AssertTrue(cProfile.GetLine("_main", "Test.cpp", 15) != NULL);
	AssertLong(2000, cProfile.GetLine("_main", "Test.cpp", 15) ? (int64)cProfile.GetLine("_main", "Test.cpp", 15)->ulliEntries : 0);
	AssertLong(2000, (int64)cProfile.LineEntries("Test.cpp", 15));
	psMain = cProfile.Get("_main");
	AssertTrue(psMain && (psMain->uiHash != 0) && (psMain->iTime != 0));

	//Guided: only the call in main's loop is inlined.
	cGuided.Init();
	AssertInt(iResult, TestCPP816RunProfiled(szSource, &cProfile, &cGuided, &uiGuided));
	psMix = cGuided.Get("_Mix__Fss");
	AssertLong(1, psMix ? (int64)psMix->ulliCalls : 0);
	AssertTrue(uiGuided < uiPlain);
	cGuided.Kill();
	cProfile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// Hot divides and remainders of a byte's values by constants (char / 10,
// unsigned char % 7) are looked up in tables (R816_STable10, R816_UTable7)
// when a profile says they are hot, and give what the reciprocals give for
// every byte; char multiplies look the product up in MathMult.
//
//////////////////////////////////////////////////////////////////////////
void TestCPP816ProfileGuidedDivisionTables(void)
{
	static const char*	szSource =
		"int main()\n"
		"{\n"
		"\tunsigned short h = 0;\n"
		"\tfor (int k = 0; k < 3; k++)\n"
		"\t{\n"
		"\t\tfor (int i = 0; i < 256; i++)\n"
		"\t\t{\n"
		"\t\t\tsigned char c = (signed char)i;\n"
		"\t\t\tunsigned char u = (unsigned char)(i + k);\n"
		"\t\t\tsigned char q = c / 10;\n"
		"\t\t\tsigned char r = c % 10;\n"
		"\t\t\tunsigned char uq = u / 7;\n"
		"\t\t\tunsigned char ur = u % 7;\n"
		"\t\t\tsigned char m = (signed char)(c * (signed char)(i >> 3));\n"
		"\t\t\th = h * 31 + (unsigned char)q;\n"
		"\t\t\th = h * 31 + (unsigned char)r;\n"
		"\t\t\th = h * 31 + uq;\n"
		"\t\t\th = h * 31 + ur;\n"
		"\t\t\th = h * 31 + (unsigned char)m;\n"
		"\t\t}\n"
		"\t}\n"
		"\treturn (int)(short)h;\n"
		"}\n";
	CAsm816Profile	cProfile;
	CChars			szPlainMap;
	CChars			szGuidedMap;
	uint64			uiPlain;
	uint64			uiGuided;
	uint16			uiHash;
	int				k;
	int				i;
	signed char		c;
	unsigned char	u;

	uiHash = 0;
	for (k = 0; k < 3; k++)
	{
		for (i = 0; i < 256; i++)
		{
			c = (signed char)i;
			u = (unsigned char)(i + k);
			uiHash = (uint16)(uiHash * 31 + (unsigned char)(signed char)(c / 10));
			uiHash = (uint16)(uiHash * 31 + (unsigned char)(signed char)(c % 10));
			uiHash = (uint16)(uiHash * 31 + (unsigned char)(u / 7));
			uiHash = (uint16)(uiHash * 31 + (unsigned char)(u % 7));
			uiHash = (uint16)(uiHash * 31 + (unsigned char)(signed char)(c * (signed char)(i >> 3)));
		}
	}

	cProfile.Init();
	szPlainMap.Init();
	AssertInt((int16)uiHash, TestCPP816RunProfiled(szSource, NULL, &cProfile, &uiPlain, &szPlainMap));
	AssertFalse(szPlainMap.Contains("R816_STable10"));
	AssertFalse(szPlainMap.Contains("R816_UTable7"));
	AssertFalse(szPlainMap.Contains("R816_Mul16"));

	szGuidedMap.Init();
	AssertInt((int16)uiHash, TestCPP816RunProfiled(szSource, &cProfile, NULL, &uiGuided, &szGuidedMap));
	AssertTrue(szGuidedMap.Contains("R816_STable10"));
	AssertTrue(szGuidedMap.Contains("R816_UTable7"));
	AssertTrue(uiGuided < uiPlain);
	szGuidedMap.Kill();
	szPlainMap.Kill();
	cProfile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// Loads and stores through a pointer plus a signed 16 bit index (biased:
// (p - 32768) + zext(i ^ 32768) with the index in Y), negative and
// positive, bytes and words, in a loop and not.
//
//////////////////////////////////////////////////////////////////////////
void TestCPP816BiasedIndices(void)
{
	static const char*	szSource =
		"char gac[600];\n"
		"short gas[600];\n"
		"char Get(char* p, short i) { return p[i]; }\n"
		"char (*volatile gpGet)(char*, short) = Get;\n"
		"int main()\n"
		"{\n"
		"\tchar* pc = &gac[300];\n"
		"\tshort* ps = &gas[300];\n"
		"\tunsigned short h = 0;\n"
		"\tfor (short i = -300; i < 300; i++) { pc[i] = (char)(i * 7); ps[i] = (short)(i * 1001); }\n"
		"\tfor (short i = 299; i >= -300; i--) { h = h * 31 + (unsigned char)pc[i]; h = h * 31 + (unsigned short)ps[i]; }\n"
		"\th = h * 31 + (unsigned char)gpGet(pc, -300);\n"
		"\th = h * 31 + (unsigned char)gpGet(pc, 299);\n"
		"\th = h * 31 + (unsigned char)gpGet(pc, 0);\n"
		"\treturn (int)(short)h;\n"
		"}\n";
	signed char	ac[600];
	short		as[600];
	uint16		uiHash;
	int			i;
	uint64		uiCycles;

	for (i = -300; i < 300; i++)
	{
		ac[i + 300] = (signed char)(i * 7);
		as[i + 300] = (short)(i * 1001);
	}
	uiHash = 0;
	for (i = 299; i >= -300; i--)
	{
		uiHash = (uint16)(uiHash * 31 + (unsigned char)ac[i + 300]);
		uiHash = (uint16)(uiHash * 31 + (unsigned short)as[i + 300]);
	}
	uiHash = (uint16)(uiHash * 31 + (unsigned char)ac[0]);
	uiHash = (uint16)(uiHash * 31 + (unsigned char)ac[599]);
	uiHash = (uint16)(uiHash * 31 + (unsigned char)ac[300]);
	AssertInt((int16)uiHash, TestCPP816RunProfiled(szSource, NULL, NULL, &uiCycles));
}


//////////////////////////////////////////////////////////////////////////
//
// A pointer chosen between one base plus different i16 indices (and null)
// and only loaded and stored through is the base plus the chosen index
// (MergeAddressPhis); a choice between two bases is left as it is.
//
//////////////////////////////////////////////////////////////////////////
void TestCPP816MergedAddressPhis(void)
{
	static const char*	szSource =
		"char gac[400];\n"
		"char gbc[400];\n"
		"struct SDigits { short iWhole; char ac[400]; };\n"
		"SDigits gs;\n"
		"char* At(SDigits* p, short i) { if (i > 0) { return &p->ac[p->iWhole - i]; } else if (i < 0) { return &p->ac[p->iWhole - i - 1]; } return 0; }\n"
		"void Set(SDigits* p, short i, char c) { *At(p, i) = c; }\n"
		"char Get(SDigits* p, short i) { return *At(p, i); }\n"
		"char* Pick(short b, short i) { return b ? &gac[i + 100] : &gbc[i + 200]; }\n"
		"int main()\n"
		"{\n"
		"\tunsigned short h = 0;\n"
		"\tgs.iWhole = 200;\n"
		"\tfor (short i = -199; i <= 199; i++) { if (i != 0) { Set(&gs, i, (char)(i * 3)); } }\n"
		"\tfor (short i = 199; i >= -199; i--) { if (i != 0) { h = h * 31 + (unsigned char)Get(&gs, i); } }\n"
		"\tfor (short i = -100; i < 100; i++) { *Pick(i & 1, i) = (char)(i + 5); }\n"
		"\tfor (short i = 0; i < 400; i++) { h = h * 31 + (unsigned char)gac[i]; h = h * 31 + (unsigned char)gbc[i]; }\n"
		"\treturn (int)(short)h;\n"
		"}\n";
	signed char	ac[400];
	signed char	abc[400];
	signed char	ad[400];
	uint16		uiHash;
	int			i;
	uint64		uiCycles;

	memset(ac, 0, sizeof(ac));
	memset(abc, 0, sizeof(abc));
	memset(ad, 0, sizeof(ad));
	for (i = -199; i <= 199; i++)
	{
		if (i != 0)
		{
			ad[(i > 0) ? (200 - i) : (200 - i - 1)] = (signed char)(i * 3);
		}
	}
	uiHash = 0;
	for (i = 199; i >= -199; i--)
	{
		if (i != 0)
		{
			uiHash = (uint16)(uiHash * 31 + (unsigned char)ad[(i > 0) ? (200 - i) : (200 - i - 1)]);
		}
	}
	for (i = -100; i < 100; i++)
	{
		if (i & 1)
		{
			ac[i + 100] = (signed char)(i + 5);
		}
		else
		{
			abc[i + 200] = (signed char)(i + 5);
		}
	}
	for (i = 0; i < 400; i++)
	{
		uiHash = (uint16)(uiHash * 31 + (unsigned char)ac[i]);
		uiHash = (uint16)(uiHash * 31 + (unsigned char)abc[i]);
	}
	AssertInt((int16)uiHash, TestCPP816RunProfiled(szSource, NULL, NULL, &uiCycles));
}


//////////////////////////////////////////////////////////////////////////
//
// 32 bit loop counters whose start and bound fit 16 bits count in 16 bits:
// up and down, < <= > >=, starting past the bound, near the ends of 16
// bits, with the counter's value used in the loop and after it.
//
//////////////////////////////////////////////////////////////////////////
void TestCPP816NarrowCounters(void)
{
	static const char*	szSource =
		"short gas[7] = { -32767, -5, 0, 7, 32766, 100, -1 };\n"
		"long Sum(short a, short b) { long t = 0; for (long i = a; i <= b; i++) { t += i; } return t; }\n"
		"long Down(short a, short b) { long t = 0; long i; for (i = a; i >= b; i--) { t += i * 3; } return t + i; }\n"
		"long Lt(short a, short b) { long i; long n = 0; for (i = a; i < b; i++) { n++; } return n * 7 + i; }\n"
		"long Gt(short a, short b) { long i; long n = 0; for (i = a; i > b; i--) { n++; } return n * 5 - i; }\n"
		"long (*volatile gpSum)(short, short) = Sum;\n"
		"long (*volatile gpDown)(short, short) = Down;\n"
		"long (*volatile gpLt)(short, short) = Lt;\n"
		"long (*volatile gpGt)(short, short) = Gt;\n"
		"int main()\n"
		"{\n"
		"\tunsigned long r = 0;\n"
		"\tfor (int a = 0; a < 7; a++)\n"
		"\t{\n"
		"\t\tfor (int b = 0; b < 7; b++)\n"
		"\t\t{\n"
		"\t\t\tr = r * 31 + (unsigned long)gpSum(gas[a], gas[b]);\n"
		"\t\t\tr = r * 31 + (unsigned long)gpDown(gas[a], gas[b]);\n"
		"\t\t\tr = r * 31 + (unsigned long)gpLt(gas[a], gas[b]);\n"
		"\t\t\tr = r * 31 + (unsigned long)gpGt(gas[a], gas[b]);\n"
		"\t\t}\n"
		"\t}\n"
		"\treturn (int)r;\n"
		"}\n";
	uint64	uiCycles;

	AssertInt(-24560, TestCPP816RunProfiled(szSource, NULL, NULL, &uiCycles));
}


//////////////////////////////////////////////////////////////////////////
//
// TestCPP816IntIndexPointers' functions natively, with 16 bit ints.
//
//////////////////////////////////////////////////////////////////////////
uint16 TestCPP816IntIndexSubtract(char* pc, const char* pd, int16 iThis, int16 iOther, int16 iFirst)
{
	char	cCarry;
	char	cResult;

	cCarry = 0;
	for (; iOther >= iFirst; iOther--, iThis--)
	{
		cResult = (char)(pc[iThis] + 10 - (pd[iOther] + cCarry));
		if (cResult >= 10)
		{
			cCarry = 0;
			cResult -= 10;
		}
		else
		{
			cCarry = 1;
		}
		pc[iThis] = cResult;
	}
	return (uint16)cCarry;
}


uint16 TestCPP816IntIndexSum(int16* as, int16 iStart, int16 iEnd)
{
	uint16	t;
	int16	i;

	t = 0;
	for (i = iStart; i < iEnd; i++)
	{
		t = (uint16)(t + (uint16)(as[i] * 3));
	}
	return t;
}


//////////////////////////////////////////////////////////////////////////
//
// int (16 bit) indices stepped through arrays (two going down together, as
// CNumber's PrivateSubtract does, and one going up through shorts) become
// pointers stepped round the loop, not the index sign extended and added
// each time: the same results, in under 66000 cycles (72255 without).
//
//////////////////////////////////////////////////////////////////////////
void TestCPP816IntIndexPointers(void)
{
	static const char*	szSource =
		"char gac[40];\n"
		"char gad[40];\n"
		"short gas[40];\n"
		"int Subtract(char* pc, const char* pd, int iThis, int iOther, int iFirst)\n"
		"{\n"
		"\tchar cCarry = 0;\n"
		"\tfor (; iOther >= iFirst; iOther--, iThis--)\n"
		"\t{\n"
		"\t\tchar cResult = pc[iThis] + 10 - (pd[iOther] + cCarry);\n"
		"\t\tif (cResult >= 10) { cCarry = 0; cResult -= 10; } else { cCarry = 1; }\n"
		"\t\tpc[iThis] = cResult;\n"
		"\t}\n"
		"\treturn cCarry;\n"
		"}\n"
		"unsigned int Sum(int iStart, int iEnd) { unsigned int t = 0; for (int i = iStart; i < iEnd; i++) { t += (unsigned int)(gas[i] * 3); } return t; }\n"
		"int (*volatile gpSubtract)(char*, const char*, int, int, int) = Subtract;\n"
		"unsigned int (*volatile gpSum)(int, int) = Sum;\n"
		"int main()\n"
		"{\n"
		"\tunsigned int r = 0;\n"
		"\tfor (int i = 0; i < 40; i++) { gac[i] = (char)((i * 7) % 10); gad[i] = (char)((i * 3 + 1) % 10); gas[i] = (short)(i * 101 - 2000); }\n"
		"\tr = r * 31 + (unsigned int)gpSubtract(gac, gad, 39, 30, 0);\n"
		"\tr = r * 31 + (unsigned int)gpSubtract(gac + 20, gad + 10, 19, 29, 12);\n"
		"\tfor (int i = 0; i < 40; i++) { r = r * 31 + (unsigned int)gac[i]; }\n"
		"\tr = r * 31 + (unsigned int)gpSum(0, 40) + (unsigned int)gpSum(5, 6) + (unsigned int)gpSum(7, 7);\n"
		"\treturn (int)r;\n"
		"}\n";
	uint64			uiCycles;
	char			ac[40];
	char			ad[40];
	int16			as[40];
	uint16			uiResult;
	int				i;

	//The same natively, with 16 bit ints.
	for (i = 0; i < 40; i++)
	{
		ac[i] = (char)((i * 7) % 10);
		ad[i] = (char)((i * 3 + 1) % 10);
		as[i] = (int16)(i * 101 - 2000);
	}
	uiResult = 0;
	uiResult = (uint16)(uiResult * 31 + TestCPP816IntIndexSubtract(ac, ad, 39, 30, 0));
	uiResult = (uint16)(uiResult * 31 + TestCPP816IntIndexSubtract(ac + 20, ad + 10, 19, 29, 12));
	for (i = 0; i < 40; i++)
	{
		uiResult = (uint16)(uiResult * 31 + (uint16)ac[i]);
	}
	uiResult = (uint16)(uiResult * 31 + TestCPP816IntIndexSum(as, 0, 40) + TestCPP816IntIndexSum(as, 5, 6) + TestCPP816IntIndexSum(as, 7, 7));

	AssertInt((int16)uiResult, TestCPP816RunProfiled(szSource, NULL, NULL, &uiCycles));
	AssertTrue(uiCycles < 66000);
}


//////////////////////////////////////////////////////////////////////////
//
// Divides and remainders by constants of values in a known range (a char,
// an unsigned char, an and) are a multiply and shifts, not the runtime's
// divide: every value gives the same quotients and remainders.
//
//////////////////////////////////////////////////////////////////////////
void TestCPP816ConstantDivisions(void)
{
	static const char*	szSource =
		"int main()\n"
		"{\n"
		"\tunsigned int r = 0;\n"
		"\tfor (int i = -128; i < 128; i++) { char c = (char)i; r = r * 31 + (unsigned int)(c / 10) * 7 + (unsigned int)(c % 10); }\n"
		"\tfor (int i = 0; i < 256; i++) { unsigned char u = (unsigned char)i; r = r * 31 + u / 10 + (u % 7) * 3 + u / 3; }\n"
		"\tfor (int i = 0; i < 1000; i++) { int x = i & 511; r = r * 31 + x / 9 + x % 9; }\n"
		"\treturn (int)r;\n"
		"}\n";
	CCPP65Builder	cBuilder;
	CChars			szAssembly;
	CChars			szErrors;
	uint64			uiCycles;

	AssertInt(26921, TestCPP816RunProfiled(szSource, NULL, NULL, &uiCycles));

	cBuilder.Init();
	TestCPP65AddIncludeDirectories(&cBuilder);
	szAssembly.Init();
	szErrors.Init();
	AssertTrue(CCPP65Builder::Generate(&szAssembly, &szErrors, cBuilder.GetIncludeDirectories(), "Test.cpp", szSource, false, NULL, CPPT_W65C816));
	AssertString("", szErrors.Text());
	AssertFalse(szAssembly.Contains("R816_SDiv") || szAssembly.Contains("R816_SRem") || szAssembly.Contains("R816_UDiv") || szAssembly.Contains("R816_URem"));
	szErrors.Kill();
	szAssembly.Kill();
	cBuilder.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// A small function that takes an object by value (passed as its bytes: the
// callee takes the parameter's address) is inlined, with the object in a
// slot in the caller; the callee changing its copy changes the caller's
// object neither.
//
//////////////////////////////////////////////////////////////////////////
void TestCPP816InlineObjectParameters(void)
{
	static const char*	szSource =
		"struct SPair { int a; int b; char c; };\n"
		"int Weigh(SPair s, int k) { s.a += k; return s.a * 2 + s.b - s.c; }\n"
		"int main()\n"
		"{\n"
		"\tSPair\tp;\n"
		"\tint\t\tr = 0;\n"
		"\tp.a = 1; p.b = 10; p.c = 3;\n"
		"\tfor (int i = 0; i < 20; i++)\n"
		"\t{\n"
		"\t\tp.b = i;\n"
		"\t\tr += Weigh(p, i);\n"
		"\t}\n"
		"\treturn (p.a == 1) ? r : -1;\n"
		"}\n";
	CAsm816Profile			cProfile;
	SAsm816FunctionProfile*	psWeigh;
	uint64					uiCycles;

	cProfile.Init();
	AssertInt(20 * 2 + 2 * 190 + 190 - 60, TestCPP816RunProfiled(szSource, NULL, &cProfile, &uiCycles));
	psWeigh = cProfile.Get("_Weigh__FC5SPairs");
	AssertTrue((psWeigh == NULL) || (psWeigh->ulliCalls == 0));
	cProfile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// A variadic function's named parameter of a class that isn't trivially
// copyable (SupportLib's CTileLayerCel::SetTiles takes a Ptr) is passed by
// the address of a copy the caller makes and destroys, as any call's; the
// last named parameter stays on the stack for va_start.
//
//////////////////////////////////////////////////////////////////////////
void TestCPP816VariadicObjectParameters(void)
{
	AssertInt(1 + 100 + 60 + 1000 + 10000, TestCPP816RunProject(NULL, "",
		"#include <stdarg.h>\n"
		"int giCopies = 0;\n"
		"int giDestroyed = 0;\n"
		"class CPtr { public: int* mp; CPtr(int* p) { mp = p; } CPtr(const CPtr& c) { mp = c.mp; giCopies++; } ~CPtr() { giDestroyed++; } };\n"
		"int Sum(int x, CPtr p, int n, ...)\n"
		"{\n"
		"\tva_list\tap;\n"
		"\tint\t\tt;\n"
		"\tint\t\ti;\n"
		"\tva_start(ap, n);\n"
		"\tt = x + *p.mp;\n"
		"\tfor (i = 0; i < n; i++) t += va_arg(ap, int);\n"
		"\tva_end(ap);\n"
		"\treturn t;\n"
		"}\n"
		"int main(void)\n"
		"{\n"
		"\tint\t\tv = 100;\n"
		"\tCPtr\tc(&v);\n"
		"\tint\t\tr = Sum(1, c, 3, 10, 20, 30);\n"
		"\treturn r + giCopies * 1000 + giDestroyed * 10000;\n"
		"}\n"));
}


//////////////////////////////////////////////////////////////////////////
//
// Compiles szSource for eTarget (it must compile) and returns how many
// warnings mention szWarning.
//
//////////////////////////////////////////////////////////////////////////
int TestCPP816CountWarnings(const char* szSource, const char* szWarning, ECPPTarget eTarget = CPPT_W65C816)
{
	CCPP65Builder	cBuilder;
	CChars			szAssembly;
	CChars			szErrors;
	CChars			szWarnings;
	int				iCount;
	const char*		sz;

	cBuilder.Init();
	szAssembly.Init();
	szErrors.Init();
	szWarnings.Init();
	AssertTrue(CCPP65Builder::Generate(&szAssembly, &szErrors, cBuilder.GetIncludeDirectories(), "Test.cpp", szSource, false, NULL, eTarget, &szWarnings));
	AssertString("", szErrors.Text());

	iCount = 0;
	for (sz = strstr(szWarnings.Text(), szWarning); sz; sz = strstr(sz + 1, szWarning))
	{
		iCount++;
	}
	szWarnings.Kill();
	szErrors.Kill();
	szAssembly.Kill();
	cBuilder.Kill();
	return iCount;
}


//////////////////////////////////////////////////////////////////////////
//
// Whether the function whose label starts with szPrefix (in the linked
// program's map) starts with an aligned frame's prologue: phd, tsc, tax (a
// frame that isn't aligned is phd, tsc, sec).
//
//////////////////////////////////////////////////////////////////////////
bool TestCPP816IsAligned(CCPP65Builder* pcBuilder, CAsm65Memory* pcMemory, const char* szPrefix)
{
	const char*	szLine;
	uint32		uiAddress;

	for (szLine = strstr(pcBuilder->GetMap(), "Symbols\n"); szLine; szLine = strchr(szLine + 1, '\n'))
	{
		if ((szLine[1] == ' ') && (szLine[3] == '$') && (strncmp(&szLine[15], szPrefix, strlen(szPrefix)) == 0))
		{
			uiAddress = (uint32)strtoul(&szLine[4], NULL, 16);
			return (pcMemory->GetByte(uiAddress) == 0x0B) && (pcMemory->GetByte(uiAddress + 1) == 0x3B) && (pcMemory->GetByte(uiAddress + 2) == 0xAA);
		}
	}
	AssertString("A function", szPrefix);
	return false;
}


//////////////////////////////////////////////////////////////////////////
//
// Builds szSource for the W65C816 (aligned frames estimated, or measured by
// pcProfile if given) and runs it, measuring its functions into pcMeasure (if given).
// Returns main's int; *puiCycles gets the cycles, and *pbAligned (for each
// of the aszPrefixes' functions) whether it has an aligned frame.
//
//////////////////////////////////////////////////////////////////////////
int32 TestCPP816RunFrames(const char* szSource, CAsm816Profile* pcProfile, CAsm816Profile* pcMeasure, uint64* puiCycles, const char** aszPrefixes, bool* abAligned)
{
	static const char*	aszUnits[] = { "Libc65/string816.asm", NULL };
	CCPP65Builder		cBuilder;
	CAsm65Memory		cMemory;
	CFast65C816			cFast;
	CChars				szProject;
	CFileUtil			cFileUtil;
	size				i;
	int32				iResult;

	iResult = -1000000;
	cBuilder.Init();
	cBuilder.SetTarget(CPPT_W65C816);
	cBuilder.SetFrameProfile(pcProfile);
	TestCPP65AddIncludeDirectories(&cBuilder);
	AssertTrue(cBuilder.AddStartUp());
	szProject.Init(".." _FS_ ".." _FS_ ".." _FS_ "commonlibraries" _FS_ "Libc65");
	cFileUtil.FullPath(&szProject);
	cBuilder.AddMathTables(szProject.Text());
	szProject.Kill();
	AssertTrue(cBuilder.AddSource("Test.cpp", szSource));
	TestCPP65AddUnits(&cBuilder, aszUnits, false);
	AssertTrue(cBuilder.Link());
	AssertString("", cBuilder.GetErrors());

	cMemory.Init(ASM65_MEMORY_LOW_SIZE);
	cMemory.Load(cBuilder.GetOutput());
	for (i = 0; aszPrefixes[i]; i++)
	{
		abAligned[i] = TestCPP816IsAligned(&cBuilder, &cMemory, aszPrefixes[i]);
	}
	cMemory.InitFast816(&cFast);
	cFast.Reset();
	if (pcMeasure)
	{
		pcMeasure->Run(&cMemory, &cFast, cBuilder.GetMap(), TEST_CPP816_STEPS);
	}
	else
	{
		cFast.Run(TEST_CPP816_STEPS);
	}
	AssertTrue(cFast.IsStopped());
	if (cFast.IsStopped())
	{
		iResult = (int16)cFast.GetC();
		AssertIntHex(GetCPPTarget(CPPT_W65C816)->uiStackTop, (uint32)cFast.GetS());
	}
	*puiCycles = cFast.NumCycles();
	cFast.Kill();
	cMemory.Kill();
	cBuilder.Kill();
	return iResult;
}


//////////////////////////////////////////////////////////////////////////
//
// A function gets D on a page (a cycle less each direct page access) when
// it's worth it and it can't recurse: by default when its loops' accesses
// are estimated to be well past the cost; with a profile (CAsm816Profile,
// CCPP65Builder::SetFrameProfile) when they were measured to be.  Its
// arguments are copied up to the aligned frame (stored, or pushed when the
// frame passes the page) and S as it was is kept for the epilogue.  (The
// functions are called through pointers, so they aren't inlined.)
//
//////////////////////////////////////////////////////////////////////////
void TestCPP816AlignedFrames(void)
{
	static const char*	szSource =
		"int Sum(int* p, int n, int k) { int s = 0; for (int i = 0; i < n; i++) { s += p[i] * k; } return s; }\n"
		"long Wide(int n, long add) { int a[200]; for (int i = 0; i < 200; i++) { a[i] = i + n; } long s = add; for (int i = 0; i < 200; i++) { s += a[i]; } return s; }\n"
		"int Cold(int* p, int n) { int s = 0; for (int i = 0; i < n; i++) { s += p[i] * p[i] - i; } return s; }\n"
		"int (*volatile gpSum)(int*, int, int) = Sum;\n"
		"long (*volatile gpWide)(int, long) = Wide;\n"
		"int (*volatile gpCold)(int*, int) = Cold;\n"
		"long Big(int n, long add) { int a[200]; for (int i = 0; i < 200; i++) { a[i] = i + n; } long s = add; for (int i = 0; i < 200; i++) { s += a[i]; } if (n > 0) { s += Big(n - 1, 1); } return s; }\n"
		"int main()\n"
		"{\n"
		"	int v[100];\n"
		"	long w = 0;\n"
		"	int r = 0;\n"
		"	for (int i = 0; i < 100; i++) { v[i] = i; }\n"
		"	for (int i = 0; i < 5; i++) { r += gpSum(v, 100, 1); }\n"
		"	for (int i = 0; i < 20; i++) { w += gpWide(i, 1); }\n"
		"	int c = gpCold(v, 3);\n"
		"	long b = Big(5, 7);\n"
		"	return ((r == 24750) && (w == 436020L) && (c == 2) && (b == 122412L)) ? 7 : 1;\n"
		"}\n";
	static const char*	aszPrefixes[] = { "_Sum", "_Wide", "_Cold", "_Big", NULL };
	CAsm816Profile		cProfile;
	uint64				uiEstimated;
	uint64				uiMeasured;
	bool				abAligned[4];

	//Estimated: Sum, Wide (its frame past the page) and Cold have loops; Big calls itself.
	cProfile.Init();
	AssertInt(7, TestCPP816RunFrames(szSource, NULL, &cProfile, &uiEstimated, aszPrefixes, abAligned));
	AssertTrue(abAligned[0]);
	AssertTrue(abAligned[1]);
	AssertTrue(abAligned[2]);
	AssertFalse(abAligned[3]);
	AssertTrue((cProfile.Get("_Big__Fsi") != NULL) && cProfile.Get("_Big__Fsi")->bRecursive);
	AssertTrue((cProfile.Get("_Sum__FPsss") != NULL) && !cProfile.Get("_Sum__FPsss")->bRecursive);
	AssertTrue((cProfile.Get("_Wide__Fsi") != NULL) && !cProfile.Get("_Wide__Fsi")->bRecursive);

	//Measured: Cold's loop ran 3 times once, not worth a page of stack.
	AssertInt(7, TestCPP816RunFrames(szSource, &cProfile, NULL, &uiMeasured, aszPrefixes, abAligned));
	AssertTrue(abAligned[0]);
	AssertTrue(abAligned[1]);
	AssertFalse(abAligned[2]);
	AssertFalse(abAligned[3]);
	cProfile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// Integer constant expressions that overflow their type, and constants that
// an implicit conversion truncates, are warned about: the W65C816's 16 bit int
// turns code written for a 32 bit int quietly wrong ("12000 * 6").
//
//////////////////////////////////////////////////////////////////////////
void TestCPP816Warnings(void)
{
	//An int expression that doesn't fit 16 bits: not on the 65C64, where int is 32 bits.
	AssertInt(1, TestCPP816CountWarnings("int F(void) { return 12000 * 6; }\n", "Integer overflow"));
	AssertInt(0, TestCPP816CountWarnings("int F(void) { return 12000 * 6; }\n", "Integer overflow", CPPT_65C64));
	AssertInt(1, TestCPP816CountWarnings("int F(void) { return 30000 + 30000; }\n", "Integer overflow"));
	AssertInt(1, TestCPP816CountWarnings("int F(void) { return 1 << 15; }\n", "Integer overflow"));
	AssertInt(1, TestCPP816CountWarnings("unsigned F(void) { return 40000u * 2; }\n", "Integer overflow"));

	//What the code means is fine: a long expression, unsigned wrap by subtraction, a cast.
	AssertInt(0, TestCPP816CountWarnings("long F(void) { return (long)12000 * 6; }\n", "overflow"));
	AssertInt(0, TestCPP816CountWarnings("long F(void) { return 12000L * 6; }\n", "overflow"));
	AssertInt(0, TestCPP816CountWarnings("unsigned F(void) { return 0u - 1; }\n", "overflow"));
	AssertInt(0, TestCPP816CountWarnings("int F(void) { return (int)70000L; }\n", "overflow"));
	AssertInt(0, TestCPP816CountWarnings("int F(void) { return 32767; }\n", "overflow"));

	//A constant an implicit conversion truncates: parameters, initialisers, assignments, returns and globals.
	AssertInt(1, TestCPP816CountWarnings("void G(int i);\nvoid F(void) { G(89037124); }\n", "Integer conversion overflow"));
	AssertInt(0, TestCPP816CountWarnings("void G(int i);\nvoid F(void) { G(89037124); }\n", "Integer conversion overflow", CPPT_65C64));
	AssertInt(1, TestCPP816CountWarnings("int F(void) { int i = 70000; return i; }\n", "Integer conversion overflow"));
	AssertInt(1, TestCPP816CountWarnings("int F(void) { int i; i = 70000; return i; }\n", "Integer conversion overflow"));
	AssertInt(1, TestCPP816CountWarnings("int F(void) { return 70000; }\n", "Integer conversion overflow"));
	AssertInt(1, TestCPP816CountWarnings("int giX = 70000;\n", "Integer conversion overflow"));
	AssertInt(1, TestCPP816CountWarnings("char F(void) { return 300; }\n", "Integer conversion overflow"));

	//Bit patterns are fine: -1 to unsigned, 0xFFFF to a 16 bit int, 255 or -128 to a char.
	AssertInt(0, TestCPP816CountWarnings("unsigned F(void) { unsigned u = -1; return u; }\n", "overflow"));
	AssertInt(0, TestCPP816CountWarnings("int F(void) { int i = 0xFFFF; return i; }\n", "overflow"));
	AssertInt(0, TestCPP816CountWarnings("char F(void) { char c = 255; c = -128; return c; }\n", "overflow"));
	AssertInt(0, TestCPP816CountWarnings("unsigned long F(void) { unsigned long ul = 0xFFFFFFFF; return ul; }\n", "overflow"));

	//An expression looked at more than once is warned about once.
	AssertInt(1, TestCPP816CountWarnings("void G(int i);\nvoid F(void) { G(12000 * 6); }\n", "Integer overflow"));

	//An enum is as big as its enumerators need ([dcl.enum]), not always an int: TRISTATE's TRIERROR = 0xffffffff.
	AssertInt(0, TestCPP816CountWarnings("enum ETri { TRI_FALSE = 0, TRI_ERROR = 0xffffffff };\nETri F(void) { ETri e = TRI_ERROR; return e; }\n", "overflow"));
	AssertInt(2 + 4 * 8 + 1 * 64 + 2 * 512 + 4 * 4096, TestCPP816RunProject(NULL, "",
		"enum E1 { A1 = 1 };\n"
		"enum E2 { A2 = 0, B2 = 0xffffffff };\n"
		"enum E3 : unsigned char { A3 };\n"
		"enum class E4 { A4 };\n"
		"enum E5 { A5 = -1, B5 = 40000 };\n"
		"int main(void)\n"
		"{\n"
		"\treturn (int)(sizeof(E1) + sizeof(E2) * 8 + sizeof(E3) * 64 + sizeof(E4) * 512 + sizeof(E5) * 4096);\n"
		"}\n"));
	AssertInt(3, TestCPP816RunProject(NULL, "",
		"enum ETri { TRI_FALSE = 0, TRI_TRUE = 1, TRI_ERROR = 0xffffffff };\n"
		"ETri Get(int i) { return (i == 0) ? TRI_ERROR : TRI_TRUE; }\n"
		"int main(void)\n"
		"{\n"
		"\tETri e = Get(0);\n"
		"\treturn ((e == TRI_ERROR) ? 1 : 0) + ((unsigned long)e == 0xffffffffUL ? 2 : 0) + ((Get(1) == TRI_ERROR) ? 4 : 0);\n"
		"}\n"));
}


//////////////////////////////////////////////////////////////////////////
//
// A for loop's counter compared with a wider value that isn't a constant
// wraps before it can pass one that doesn't fit: a 16 bit i against a 32 bit
// count goes round forever once the count passes 65535.
//
//////////////////////////////////////////////////////////////////////////
void TestCPP816LoopCounterWarnings(void)
{
	const char*	szWarning = "Loop counter narrower than its bound";

	//i++, ++i, i += 2 and i-- against a 32 bit bound, on either side, in && and with a comma.
	AssertInt(1, TestCPP816CountWarnings("unsigned long N(void);\nint F(void) { unsigned i; int t = 0; for (i = 0; i < N(); i++) t++; return t; }\n", szWarning));
	AssertInt(1, TestCPP816CountWarnings("int F(unsigned long n) { int t = 0; for (unsigned i = 0; n > i; ++i) t++; return t; }\n", szWarning));
	AssertInt(1, TestCPP816CountWarnings("int F(unsigned long n) { int t = 0; for (unsigned i = 0; i <= n; i += 2) t++; return t; }\n", szWarning));
	AssertInt(1, TestCPP816CountWarnings("int F(unsigned long n) { int t = 0; for (unsigned i = 10; i != n; i--) t++; return t; }\n", szWarning));
	AssertInt(1, TestCPP816CountWarnings("int F(unsigned long n, int b) { int t = 0; for (unsigned i = 0; b && (i < n); i++) t++; return t; }\n", szWarning));
	AssertInt(1, TestCPP816CountWarnings("int F(unsigned long n) { int t = 0; unsigned j = 0; for (unsigned i = 0; i < n; i++, j++) t++; return t; }\n", szWarning));
	AssertInt(1, TestCPP816CountWarnings("struct S { unsigned m; int F(unsigned long n) { int t = 0; for (m = 0; m < n; m++) t++; return t; } };\nint G(void) { S s; return s.F(5); }\n", szWarning));

	//The same width, a wider counter, a constant bound, a converted bound, a variable that isn't stepped, and the 65C64 (32 bit ints).
	AssertInt(0, TestCPP816CountWarnings("int F(unsigned n) { int t = 0; for (unsigned i = 0; i < n; i++) t++; return t; }\n", szWarning));
	AssertInt(0, TestCPP816CountWarnings("int F(unsigned n) { int t = 0; for (unsigned long i = 0; i < n; i++) t++; return t; }\n", szWarning));
	AssertInt(0, TestCPP816CountWarnings("int F(void) { int t = 0; for (unsigned i = 0; i < 100L; i++) t++; return t; }\n", szWarning));
	AssertInt(0, TestCPP816CountWarnings("int F(char b) { int t = 0; for (unsigned char i = 0; i < (b ? 7 : 3); i++) t++; return t; }\n", szWarning));
	AssertInt(1, TestCPP816CountWarnings("int F(char b, int n) { int t = 0; for (unsigned char i = 0; i < (b ? n : 3); i++) t++; return t; }\n", szWarning));
	AssertInt(0, TestCPP816CountWarnings("int F(unsigned long n) { int t = 0; for (unsigned i = 0; i < (unsigned)n; i++) t++; return t; }\n", szWarning));
	AssertInt(0, TestCPP816CountWarnings("int F(unsigned long n) { int t = 0; unsigned j = 0; for (unsigned i = 0; j < n; i++) t++; return t; }\n", szWarning));
	AssertInt(0, TestCPP816CountWarnings("int F(unsigned long n) { int t = 0; for (unsigned i = 0; i < n; i++) t++; return t; }\n", szWarning, CPPT_65C64));
	AssertInt(1, TestCPP816CountWarnings("int F(unsigned long long n) { int t = 0; for (unsigned i = 0; i < n; i++) t++; return t; }\n", szWarning, CPPT_65C64));
}


//////////////////////////////////////////////////////////////////////////
//
// A comparison with a constant outside the other side's range is always true
// or always false (a 16 bit size compared with a 32 bit "not found").  With
// SetWarnNarrowing a non constant integer implicitly converted to a narrower
// type is warned about (a 32 bit index stored in a 16 bit one).
//
//////////////////////////////////////////////////////////////////////////
void TestCPP816RangeWarnings(void)
{
	//A 16 bit unsigned can't be 0xFFFFFFFF; in conditions and in values.
	AssertInt(1, TestCPP816CountWarnings("int F(unsigned u) { return u == 0xFFFFFFFFUL; }\n", "Comparison is always false"));
	AssertInt(1, TestCPP816CountWarnings("int F(unsigned u) { return u != 0xFFFFFFFFUL; }\n", "Comparison is always true"));
	AssertInt(1, TestCPP816CountWarnings("int F(unsigned u) { if (u == 0xFFFFFFFFUL) return 1; return 0; }\n", "Comparison is always false"));
	AssertInt(0, TestCPP816CountWarnings("int F(unsigned u) { return u == 0xFFFFFFFFUL; }\n", "Comparison", CPPT_65C64));

	//Relational comparisons, the constant on either side.
	AssertInt(1, TestCPP816CountWarnings("int F(int i) { return i < 40000L; }\n", "Comparison is always true"));
	AssertInt(1, TestCPP816CountWarnings("int F(int i) { return 40000L < i; }\n", "Comparison is always false"));
	AssertInt(1, TestCPP816CountWarnings("int F(int i) { return i >= -40000L; }\n", "Comparison is always true"));
	AssertInt(1, TestCPP816CountWarnings("int F(unsigned char c) { return c >= 256; }\n", "Comparison is always false"));
	AssertInt(1, TestCPP816CountWarnings("int F(unsigned char c) { return 256 > c; }\n", "Comparison is always true"));

	//The constant is converted first: -1 is 0xFFFF as a 16 bit unsigned, but an int on the 65C64.
	AssertInt(0, TestCPP816CountWarnings("int F(unsigned u) { return u == -1; }\n", "Comparison"));
	AssertInt(1, TestCPP816CountWarnings("int F(unsigned short u) { return u == -1; }\n", "Comparison is always false", CPPT_65C64));

	//In range, both sides variable or constant, and a signed side compared as unsigned.
	AssertInt(0, TestCPP816CountWarnings("int F(int i) { return i == 32767; }\n", "Comparison"));
	AssertInt(0, TestCPP816CountWarnings("int F(int i) { return i < 0; }\n", "Comparison"));
	AssertInt(0, TestCPP816CountWarnings("int F(unsigned long ul) { return ul == 0xFFFFFFFFUL; }\n", "Comparison"));
	AssertInt(0, TestCPP816CountWarnings("int F(unsigned u, long l) { return u == l; }\n", "Comparison"));
	AssertInt(0, TestCPP816CountWarnings("int F(void) { return 70000L == 0xFFFFFFFFUL; }\n", "Comparison"));
	AssertInt(0, TestCPP816CountWarnings("int F(int i) { return i == 0xFFFFFFFFUL; }\n", "Comparison"));
	AssertInt(0, TestCPP816CountWarnings("enum ETri { TRI_FALSE = 0, TRI_ERROR = 0xffffffff };\nint F(ETri e) { return e == TRI_ERROR; }\n", "Comparison"));

	//Narrowing is off by default.
	AssertInt(0, TestCPP816CountWarnings("int F(long l) { int i = l; return i; }\n", "narrows"));

	CCPP65Generator::SetDefaultWarnNarrowing(true);
	AssertInt(1, TestCPP816CountWarnings("int F(long l) { int i = l; return i; }\n", "Integer conversion narrows"));
	AssertInt(1, TestCPP816CountWarnings("int F(long l) { int i; i = l; return i; }\n", "Integer conversion narrows"));
	AssertInt(1, TestCPP816CountWarnings("int F(long l) { return l; }\n", "Integer conversion narrows"));
	AssertInt(1, TestCPP816CountWarnings("void G(int i);\nvoid F(long l) { G(l); }\n", "Integer conversion narrows"));
	AssertInt(1, TestCPP816CountWarnings("char F(int i) { return i; }\n", "Integer conversion narrows"));

	//Widening, explicit casts, same width and constants (which have their own warning) aren't.
	AssertInt(0, TestCPP816CountWarnings("long F(int i) { long l = i; return l; }\n", "narrows"));
	AssertInt(0, TestCPP816CountWarnings("int F(long l) { return (int)l; }\n", "narrows"));
	AssertInt(0, TestCPP816CountWarnings("unsigned F(int i) { return i; }\n", "narrows"));
	AssertInt(0, TestCPP816CountWarnings("int F(void) { int i = 7L; return i; }\n", "narrows"));
	AssertInt(0, TestCPP816CountWarnings("int F(long l) { return l; }\n", "narrows", CPPT_65C64));
	CCPP65Generator::SetDefaultWarnNarrowing(false);
}


//////////////////////////////////////////////////////////////////////////
//
// What making BaseLib's size 16 bits on the W65C816 (with a 32 bit lsize)
// turned up.  Libc65's printf read %ld as a 16 bit int.  MemSwp is string816.asm's (lsize length): when BaseLib
// declared it with a size length the call named a label nothing defined, and
// its stub was the 65C64's stp, which the W65C816 ran as something else: the
// sorts called address 0.  A missing name's stub now stops the W65C816.  A
// pointer to a 16 bit value passed for a pointer to a 32 bit one, and a call
// that matches two overloads (size and lsize), are errors that say so, not
// "doesn't support yet".  A 16 bit multiply widened to 64 bits (a key made
// from a 16 bit index) is warned about, and so is a comparison that can't
// change once the values are followed (a 16 bit "not found" widened and
// compared with the 32 bit one).
//
//////////////////////////////////////////////////////////////////////////
void TestCPP816SizeLsizeBugs(void)
{
	CCPP65Builder	cBuilder;
	CChars			szAssembly;
	CChars			szErrors;
	CAsm65Memory	cMemory;
	int64			lliAddress;

	//BaseLib's sorts swap with MemSwp.
	AssertInt(1 + 3 * 10, TestCPP816RunProject(NULL, "",
		"#include \"BaseLib/ArrayUint.h\"\n"
		"int main(void)\n"
		"{\n"
		"\tCArrayUint\tc;\n"
		"\tint\t\t\tr;\n"
		"\tc.Init();\n"
		"\tc.Add(3);\n"
		"\tc.Add(1);\n"
		"\tc.Add(2);\n"
		"\tc.BubbleSort();\n"
		"\tr = c[0] + c[2] * 10;\n"
		"\tc.QuickSort();\n"
		"\tc.Kill();\n"
		"\treturn r;\n"
		"}\n", false, NULL, 0, TEST_CPP816_SLOW_STEPS, true));

	//printf's l is a long, not an int: an int is 16 bits on the W65C816.
	AssertInt(1, TestCPP816RunProject(NULL, "",
		"#include <stdio.h>\n"
		"#include <string.h>\n"
		"int main(void)\n"
		"{\n"
		"\tchar\tsz[64];\n"
		"\tsprintf(sz, \"%ld %lu %d %lx %u\", -65588L, 65588UL, 7, 0x12345678UL, 9u);\n"
		"\treturn strcmp(sz, \"-65588 65588 7 12345678 9\") == 0;\n"
		"}\n", false, NULL, 0, TEST_CPP816_SLOW_STEPS, true));

	//TestMemoryQueue's FillQueueElement: uiSize - 1 is both widened for memset and a store's folded index (Y).  Its
	//store to the frame was dropped (the zext's lda right after took it from A), so Y was read from a slot never
	//written and the '\0' went somewhere else.
	AssertInt(1, TestCPP816RunProject(NULL, "",
		"#include <string.h>\n"
		"void Fill(void* pvData, unsigned short uiSize, char c)\n"
		"{\n"
		"\tif (pvData && uiSize > 1)\n"
		"\t{\n"
		"\t\tmemset(pvData, c, uiSize - 1);\n"
		"\t\t((char*)pvData)[uiSize - 1] = '\\0';\n"
		"\t}\n"
		"}\n"
		"int main(void)\n"
		"{\n"
		"\tchar\tac[40];\n"
		"\tmemset(ac, 'x', 40);\n"
		"\tFill(ac, 28, 'D');\n"
		"\treturn (ac[26] == 'D') && (ac[27] == '\\0') && (ac[28] == 'x');\n"
		"}\n", false, NULL, 0, TEST_CPP816_SLOW_STEPS, true));

	//No conversion from unsigned short* to unsigned long*.
	cBuilder.Init();
	szAssembly.Init();
	szErrors.Init();
	AssertFalse(CCPP65Builder::Generate(&szAssembly, &szErrors, cBuilder.GetIncludeDirectories(), "Test.cpp",
		"void F(unsigned long* pul) { *pul = 7; }\n"
		"int main(void) { unsigned short u; F(&u); return u; }\n", false, NULL, CPPT_W65C816));
	AssertNull(strstr(szErrors.Text(), "doesn't support"));
	AssertNull(strstr(szErrors.Text(), "Unknown instruction"));
	AssertNotNull(strstr(szErrors.Text(), "No function matches the arguments (unsigned short*): it takes (unsigned long*)"));
	szErrors.Kill();
	szAssembly.Kill();
	cBuilder.Kill();

	//An int matches a size and an lsize parameter as well.
	cBuilder.Init();
	szAssembly.Init();
	szErrors.Init();
	AssertFalse(CCPP65Builder::Generate(&szAssembly, &szErrors, cBuilder.GetIncludeDirectories(), "Test.cpp",
		"void M(void* p, unsigned short u);\n"
		"void M(void* p, unsigned long u);\n"
		"int main(void) { char a[4]; M(a, 6); return 0; }\n", false, NULL, CPPT_W65C816));
	AssertNull(strstr(szErrors.Text(), "doesn't support"));
	AssertNotNull(strstr(szErrors.Text(), "The call is ambiguous"));
	szErrors.Kill();
	szAssembly.Kill();
	cBuilder.Kill();

	//The stub a name nothing defines is linked to is the W65C816's stp ($DB), not the 65C64's.
	cBuilder.Init();
	cBuilder.SetTarget(CPPT_W65C816);
	TestCPP65AddIncludeDirectories(&cBuilder);
	AssertTrue(cBuilder.AddStartUp());
	AssertTrue(cBuilder.AddSource("Test.cpp", "void Missing(void);\nint main(void) { Missing(); return 5; }\n"));
	AssertTrue(cBuilder.Link());
	AssertSize(1, cBuilder.NumMissing());
	AssertTrue(cBuilder.GetSymbol("_Missing", &lliAddress));
	cMemory.Init(ASM65_MEMORY_LOW_SIZE);
	cMemory.Load(cBuilder.GetOutput());
	AssertInt(0xDB, cMemory.GetByte((uint32)lliAddress));
	cMemory.Kill();
	cBuilder.Kill();

	//TestIndexPtr's keys: ui * 0x39e7 multiplied in 16 bits, then widened.
	AssertInt(1, TestCPP816CountWarnings("long long gl;\nvoid F(unsigned short ui) { gl = ui * 0x39e7; }\n", "widened after it may have wrapped"));
	AssertInt(1, TestCPP816CountWarnings("void* Remap(void* pv, long l);\nvoid* F(void* pv, unsigned short ui) { return Remap(pv, ui << 3); }\n", "widened after it may have wrapped"));
	AssertInt(0, TestCPP816CountWarnings("long long gl;\nvoid F(unsigned short ui) { gl = (long long)ui * 0x39e7; }\n", "widened after it may have wrapped"));
	AssertInt(1, TestCPP816CountWarnings("long long gl;\nvoid F(unsigned short ui) { gl = (long long)(ui * 0x39e7); }\n", "widened after it may have wrapped"));
	//SupportLib's row blitters: y * uiRowStride + x * uiPixelStride made a 16 bit offset, then widened to a ptrdiff.
	AssertInt(1, TestCPP816CountWarnings("void* Remap(void* pv, long l);\nvoid* F(void* pv, unsigned short y, unsigned short s, unsigned short x) { return Remap(pv, y * s + x * 3); }\n", "widened after it may have wrapped"));
	AssertInt(1, TestCPP816CountWarnings("long gl;\nvoid F(unsigned short a, unsigned short b) { gl = (a << 4) | b; }\n", "widened after it may have wrapped"));
	AssertInt(0, TestCPP816CountWarnings("void* Remap(void* pv, long l);\nvoid* F(void* pv, unsigned short y, unsigned long s, unsigned short x) { return Remap(pv, y * s + x); }\n", "widened after it may have wrapped"));
	AssertInt(0, TestCPP816CountWarnings("long gl;\nvoid F(unsigned short a, unsigned short b) { gl = a + b; }\n", "widened after it may have wrapped"));

	//TestIndexUnknown: the cast doesn't make the multiply wider.
	AssertInt(1, TestCPP816CountWarnings("void Init(long l);\nvoid F(unsigned short ui) { Init((long)((ui + 1) * 7)); }\n", "widened after it may have wrapped"));
	AssertInt(0, TestCPP816CountWarnings("void Init(long l);\nvoid F(unsigned short ui) { Init(((long)ui + 1) * 7); }\n", "widened after it may have wrapped"));
	AssertInt(0, TestCPP816CountWarnings("long F(void) { return (long)(4 * 7); }\n", "widened after it may have wrapped"));
	AssertInt(0, TestCPP816CountWarnings("unsigned short F(unsigned short a, unsigned short b) { return (unsigned short)(a * b); }\n", "widened after it may have wrapped"));
	AssertInt(0, TestCPP816CountWarnings("long gl;\nvoid F(unsigned short ui) { gl = ui + 1; }\n", "widened after it may have wrapped"));

	//CChars::PassifyNewlines: ::PassifyNewlines' 16 bit MAX_SIZE in a 32 bit lsize, compared with MAX_LSIZE.
	AssertInt(1, TestCPP816CountWarnings("unsigned short Find(void);\nint F(void) { unsigned long ul; ul = Find(); if (ul != 0xFFFFFFFFUL) { return 1; } return 0; }\n", "Comparison is always true: a 16 bit value, zero extended, is compared with 4294967295"));
	AssertInt(0, TestCPP816CountWarnings("unsigned long Find(void);\nint F(void) { unsigned long ul; ul = Find(); if (ul != 0xFFFFFFFFUL) { return 1; } return 0; }\n", "Comparison is always"));
	AssertInt(0, TestCPP816CountWarnings("unsigned short Find(void);\nint F(void) { unsigned long ul; ul = Find(); if (ul != 0xFFFFUL) { return 1; } return 0; }\n", "Comparison is always"));

	//TestSound's every 16 bit value loop: i <= 32767 with a 16 bit int never ends.
	AssertInt(1, TestCPP816CountWarnings("int F(void) { int i; int n; n = 0; for (i = -32768; i <= 32767; i++) { n++; } return n; }\n", "Comparison is always true: the constant 32767 is the largest value of the 16 bit signed"));
	AssertInt(0, TestCPP816CountWarnings("int F(unsigned short u) { return 65535 < u; }\n", "Comparison is always"));
	AssertInt(1, TestCPP816CountWarnings("int F(short s) { return s >= -32768; }\n", "Comparison is always true"));
	AssertInt(0, TestCPP816CountWarnings("int F(unsigned short u) { return u >= 0; }\n", "Comparison is always"));
	AssertInt(0, TestCPP816CountWarnings("int F(int i) { return i < 32767; }\n", "Comparison is always"));
	AssertInt(0, TestCPP816CountWarnings("int F(long l) { return l <= 32767; }\n", "Comparison is always"));

	//SupportLib's Convert8BitColourTo32BitColour: uint8s promoted to a 16 bit int and shifted by 16 and 24 are zero.
	AssertInt(2, TestCPP816CountWarnings("unsigned long F(unsigned char r, unsigned char b, unsigned char a) { return r | (b << 16) | (a << 24); }\n", "Shift count"));
	AssertInt(1, TestCPP816CountWarnings("int F(int i) { return i >> 16; }\n", "Shift count 16 is not less than the 16 bit width"));
	//SupportLib's Set32BitColour(r, g, b): a constant 255 << 24 is shifted as a 16 bit int too.
	AssertInt(1, TestCPP816CountWarnings("unsigned long F(unsigned long ul) { ul |= 255 << 24; return ul; }\n", "Shift count 24"));
	AssertInt(0, TestCPP816CountWarnings("unsigned long F(unsigned char b) { return ((unsigned long)b << 16) | (b << 15); }\n", "Shift count"));
	AssertInt(0, TestCPP816CountWarnings("unsigned long F(unsigned char b, int i) { return (unsigned long)b << i; }\n", "Shift count"));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCPP816(void)
{
	BeginTests();

	TypesInit();
	TypeConverterInit();
	NumberInit();
	CW65C816InstructionFactory::GetInstance()->Init();

	TestCPP816Basics();
	TestCPP816Functions();
	TestCPP816Classes();
	TestCPP816Statements();
	TestCPP816Globals();
	TestCPP816Builtins();
	TestCPP816MemSwp();
	TestCPP816LoopIdioms();
	TestCPP816BaseLib();
	TestCPP816Sprites();
	TestCPP816TideVideo();
	TestCPP816Restrict();
	TestCPP816RestrictParameter();
	TestCPP816LocalSymbols();
	TestCPP816ExitValues();
	TestCPP816MovedCode();
	TestCPP816CompileBaseLibUnits();
	TestCPP816NewDelete();
	TestCPP816Floats();
	TestCPP816TestBaseLibBugs();
	TestCPP816ConstantShifts();
	TestCPP816VariableShifts();
	TestCPP816Warnings();
	TestCPP816RangeWarnings();
	TestCPP816LoopCounterWarnings();
	TestCPP816SizeLsizeBugs();
	TestCPP816DestructorCalls();
	TestCPP816VariadicObjectParameters();
	TestCPP816ProfileGuidedInlining();
	TestCPP816ProfileGuidedDivisionTables();
	TestCPP816BiasedIndices();
	TestCPP816MergedAddressPhis();
	TestCPP816InlineObjectParameters();
	TestCPP816ConstantDivisions();
	TestCPP816IntIndexPointers();
	TestCPP816NarrowCounters();
	TestCPP816AlignedFrames();

	CW65C816InstructionFactory::GetInstance()->Kill();
	NumberKill();
	TypeConverterKill();
	TypesKill();

	TestStatistics();
}

