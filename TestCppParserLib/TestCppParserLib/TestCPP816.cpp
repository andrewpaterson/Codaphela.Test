#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
static const char* gaszTestCPP816Libc65[] = { "string.cpp", "string816.asm", "stdlib.cpp", "ctype.cpp", "time.cpp", "math.cpp", "softfloat.cpp", "new.cpp", "signal.cpp", "stdio.cpp", "host.cpp", NULL };


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
// q is p + d after it.  x wraps past 65535 in the second call.
//
//////////////////////////////////////////////////////////////////////////
void TestCPP816ExitValues(void)
{
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
	static const char*	aszFloatHelper[] = { "BaseLib/FloatHelper.cpp", "Libc65/softfloat.cpp", "Libc65/math.cpp", "Libc65/string816.asm", "Input/CPP65/FloatHelperProject/Main.cpp", NULL };
	static const char*	aszQuaternion[] = { "BaseLib/Quaternion.cpp", "Libc65/softfloat.cpp", "Libc65/string816.asm", "Input/CPP65/QuaternionProject/Main.cpp", NULL };
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

	static const char*	aszFloat[] = { "Libc65/softfloat.cpp", NULL };

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
// Shifts by constants (whole words moved, then the bits) of 32 and 64 bit values, signed and unsigned, against the
// same shifts natively.
//
//////////////////////////////////////////////////////////////////////////
void TestCPP816ConstantShifts(void)
{
	CChars		szSource;
	int			i;
	uint32		ui32;
	uint64		ui64;
	int32		i32;
	int64		i64;
	uint32		uiSum;

	ui32 = 0x9ABCDEF1;
	i32 = (int32)0x9ABCDEF1;
	ui64 = 0x9ABCDEF123456789ULL;
	i64 = (int64)0x9ABCDEF123456789ULL;
	uiSum = 0;
	szSource.Init("unsigned long gui32 = 0x9ABCDEF1UL;\nlong gi32 = (long)0x9ABCDEF1UL;\nunsigned long long gui64 = 0x9ABCDEF123456789ULL;\nlong long gi64 = (long long)0x9ABCDEF123456789ULL;\n");
	szSource.Append("int main(void)\n{\n\tunsigned long s = 0;\n");
	for (i = 1; i < 32; i++)
	{
		uiSum = uiSum * 3 + (ui32 << i) + (ui32 >> i) + (uint32)(i32 >> i);
		szSource.Append("\ts = s * 3 + (gui32 << ")->Append(i)->Append(") + (gui32 >> ")->Append(i)->Append(") + (unsigned long)(gi32 >> ")->Append(i)->Append(");\n");
	}
	for (i = 1; i < 64; i++)
	{
		uiSum = uiSum * 5 + (uint32)(ui64 << i) + (uint32)((ui64 << i) >> 32) + (uint32)(ui64 >> i) + (uint32)((ui64 >> i) >> 32) + (uint32)(i64 >> i) + (uint32)((i64 >> i) >> 32);
		szSource.Append("\ts = s * 5 + (unsigned long)(gui64 << ")->Append(i)->Append(") + (unsigned long)((gui64 << ")->Append(i)->Append(") >> 32) + (unsigned long)(gui64 >> ")->Append(i)->Append(") + (unsigned long)((gui64 >> ")->Append(i)->Append(") >> 32) + (unsigned long)(gi64 >> ")->Append(i)->Append(") + (unsigned long)((gi64 >> ")->Append(i)->Append(") >> 32);\n");
	}
	szSource.Append("\treturn (int)(s ^ (s >> 16)) & 0x7FFF;\n}\n");
	AssertInt((int)((uiSum ^ (uiSum >> 16)) & 0x7FFF), TestCPP816Run(szSource.Text()));
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
	TestCPP816NewDelete();
	TestCPP816Floats();
	TestCPP816TestBaseLibBugs();
	TestCPP816ConstantShifts();
	TestCPP816Warnings();
	TestCPP816RangeWarnings();
	TestCPP816DestructorCalls();

	CW65C816InstructionFactory::GetInstance()->Kill();
	NumberKill();
	TypeConverterKill();
	TypesKill();

	TestStatistics();
}

