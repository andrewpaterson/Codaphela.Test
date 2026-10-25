#include "BaseLib/FileUtil.h"
#include "BaseLib/FastFunctions.h"
#include "BaseLib/TypeNames.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/NumberControl.h"
#include "MicroprocessorLib/65C64InstructionFactory.h"
#include "CppParserLib/IRParser.h"
#include "CppParserLib/IRVerifier.h"
#include "CppParserLib/IR65Backend.h"
#include "TestLib/Assert.h"
#include "TestCPP65Context.h"


//The generator's R_DivideSigned and R_DivideSigned64 (CCPP65Generator::AppendDivideSigned), for programs that
//are only IR.
const char*	gszTestIR65DivideSigned =
	"\t\t.section text.R_DivideSigned\n"
	"R_DivideSigned:\n"
	"\t\tcpy X, A\n"
	"\t\txor X, B\n"
	"\t\tpsh X\n"
	"\t\tpsh A\n"
	"\t\tabs Y, A\n"
	"\t\tabs A, B\n"
	"\t\tcpy B, 0\n"
	"\t\tpsh W\n"
	"\t\tcpy W, 0\n"
	"\t\tdiv\n"
	"\t\tpul W\n"
	"\t\tpul X\n"
	"\t\tcmp X, 0\n"
	"\t\tbrac n, R_DivideSigned1\n"
	"\t\tneg B, B\n"
	"R_DivideSigned1:\n"
	"\t\tpul X\n"
	"\t\tcmp X, 0\n"
	"\t\tbrac n, R_DivideSigned2\n"
	"\t\tneg Y, Y\n"
	"R_DivideSigned2:\n"
	"\t\tcpy A, Y\n"
	"\t\tret\n"
	"\n";

const char*	gszTestIR65DivideSigned64 =
	"\t\t.section text.R_DivideSigned64\n"
	"R_DivideSigned64:\n"
	"\t\twtth (X, Y), 64\n"
	"\t\tcpy X, A\n"
	"\t\txor X, B\n"
	"\t\tpsh X\n"
	"\t\tpsh A\n"
	"\t\tabs Y, A\n"
	"\t\tabs A, B\n"
	"\t\tcpy B, 0\n"
	"\t\tpsh W\n"
	"\t\tcpy W, 0\n"
	"\t\tdiv\n"
	"\t\tpul W\n"
	"\t\tpul X\n"
	"\t\tcmp X, 0\n"
	"\t\tbrac n, R_DivideSigned641\n"
	"\t\tneg B, B\n"
	"R_DivideSigned641:\n"
	"\t\tpul X\n"
	"\t\tcmp X, 0\n"
	"\t\tbrac n, R_DivideSigned642\n"
	"\t\tneg Y, Y\n"
	"R_DivideSigned642:\n"
	"\t\tcpy A, Y\n"
	"\t\twtth (X, Y), 32\n"
	"\t\tret\n"
	"\n";


//////////////////////////////////////////////////////////////////////////
//
// Parses and verifies szIR, generates it with the 65C64 back end, links it
// with the start up (and the soft float runtime when bFloat) and runs it.
// Returns A when the program stops (main's result).
//
//////////////////////////////////////////////////////////////////////////
int64 TestIR65Run(const char* szIR, bool bFloat = false, CChars* pszAssembly = NULL)
{
	CIRModule		cModule;
	CCPPErrors		cErrors;
	CIRParser		cParser;
	CIRVerifier		cVerifier;
	CIR65Backend	cBackend;
	CChars			szCode;
	CArrayChars		aszRuntime;
	int				iLabels;
	CCPP65Builder	cBuilder;
	CFileUtil		cFileUtil;
	CChars			szDirectory;
	STestCPP65Run	sRun;
	int64			lliResult;
	bool			bResult;

	cModule.Init();
	cModule.AddSpace("default", 4);
	cErrors.Init();
	cParser.Init(&cModule, &cErrors);
	cParser.Parse(szIR);
	cParser.Kill();
	cVerifier.Init(&cModule, &cErrors);
	cVerifier.Verify();
	cVerifier.Kill();
	AssertString("", cErrors.Text());

	szCode.Init();
	aszRuntime.Init();
	iLabels = 0;
	cBackend.Init(&cModule, &iLabels, &aszRuntime);
	AssertTrue(cBackend.GenerateModule(&szCode, &cErrors));
	AssertString("", cErrors.Text());
	if (cBackend.UsesSignedDivide())
	{
		szCode.Append(gszTestIR65DivideSigned);
	}
	if (cBackend.UsesSignedDivide64())
	{
		szCode.Append(gszTestIR65DivideSigned64);
	}
	cBackend.Kill();
	if (pszAssembly)
	{
		pszAssembly->Append(szCode);
	}

	cBuilder.Init();
	TestCPP65AddIncludeDirectories(&cBuilder);
	bResult = cBuilder.AddStartUp();
	bResult &= cBuilder.AddAssembly("ir", szCode.Text());
	if (bFloat)
	{
		szDirectory.Init(".." _FS_ ".." _FS_ ".." _FS_ "commonlibraries" _FS_ "Libc65");
		cFileUtil.FullPath(&szDirectory);
		cBuilder.AddUnit("Libc65", szDirectory.Text(), "softfloat.cpp");
		cBuilder.AddUnit("Libc65", szDirectory.Text(), "softfloat.asm");
		szDirectory.Kill();
	}
	bResult &= cBuilder.Link();
	AssertString("", cBuilder.GetErrors());
	AssertTrue(bResult);

	lliResult = -1;
	if (bResult && TestCPP65BeginBuilt(&sRun, &cBuilder))
	{
		AssertTrue(TestCPP65Run(&sRun, 20000000) < 20000000);
		AssertIntHex(CPP65_STACK_TOP, TestCPP65MPU(&sRun)->GetS());
		lliResult = (int64)TestCPP65MPU(&sRun)->GetA();
		TestCPP65End(&sRun);
	}
	cBuilder.Kill();
	aszRuntime.Kill();
	szCode.Kill();
	cErrors.Kill();
	cModule.Kill();
	return lliResult;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int32 TestIR65Main(const char* szIR, bool bFloat = false)
{
	return (int32)TestIR65Run(szIR, bFloat);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIR65BackendReturn(void)
{
	CChars	szAssembly;

	szAssembly.Init();
	AssertLong(42, (int32)TestIR65Run("function i32 @_main()\n{\nb:\n\tret i32 42\n}\n", false, &szAssembly));
	AssertString(
		"\t\t.section text._main\n"
		"\t\t.global _main\n"
		"_main:\n"
		"L1:\n"
		"\t\tcpy A, 42\n"
		"L2:\n"
		"\t\tret\n"
		"\n", szAssembly.Text());
	szAssembly.Kill();

	AssertInt(-7, TestIR65Main("function i32 @_main()\n{\nb:\n\t%x = sub i32 3, 10\n\tret i32 %x\n}\n"));
}


//////////////////////////////////////////////////////////////////////////
//
// Sum of a table, with a loop's phis.
//
//////////////////////////////////////////////////////////////////////////
void TestIR65BackendLoop(void)
{
	AssertInt(150, TestIR65Main(
		"global @_gTable, align 4 { i32 10, i32 20, i32 30, i32 40, i32 50 }\n"
		"\n"
		"function i32 @_Sum__FPii(ptr %p, i32 %n)\n"
		"{\n"
		"entry:\n"
		"\tjmp loop\n"
		"loop:\n"
		"\t%s = phi i32 [entry, 0], [body, %s2]\n"
		"\t%i = phi i32 [entry, 0], [body, %i2]\n"
		"\t%c = slt i32 %i, %n\n"
		"\tbrif %c, body, exit\n"
		"body:\n"
		"\t%o = shl i32 %i, 2\n"
		"\t%a = ptradd ptr %p, %o\n"
		"\t%v = load i32 %a\n"
		"\t%s2 = add i32 %s, %v\n"
		"\t%i2 = add i32 %i, 1\n"
		"\tjmp loop\n"
		"exit:\n"
		"\tret i32 %s\n"
		"}\n"
		"\n"
		"function i32 @_main()\n"
		"{\n"
		"b:\n"
		"\t%r = call i32 @_Sum__FPii(ptr @_gTable, i32 5)\n"
		"\tret i32 %r\n"
		"}\n"));
}


//////////////////////////////////////////////////////////////////////////
//
// Phis that swap must all read before any is written.
//
//////////////////////////////////////////////////////////////////////////
void TestIR65BackendSwap(void)
{
	AssertInt(1 * 1000 + 2, TestIR65Main(
		"function i32 @_main()\n"
		"{\n"
		"entry:\n"
		"\tjmp loop\n"
		"loop:\n"
		"\t%a = phi i32 [entry, 1], [loop, %b]\n"
		"\t%b = phi i32 [entry, 2], [loop, %a]\n"
		"\t%i = phi i32 [entry, 0], [loop, %i2]\n"
		"\t%i2 = add i32 %i, 1\n"
		"\t%c = ult i32 %i2, 5\n"
		"\tbrif %c, loop, exit\n"
		"exit:\n"
		"\t%m = mul i32 %a, 1000\n"
		"\t%r = add i32 %m, %b\n"
		"\tret i32 %r\n"
		"}\n"));
}


//////////////////////////////////////////////////////////////////////////
//
// i8 and i16 wrap, extend and compare by their own widths.
//
//////////////////////////////////////////////////////////////////////////
void TestIR65BackendNarrow(void)
{
	AssertInt(-56, TestIR65Main(
		"function i32 @_main()\n{\nb:\n"
		"\t%t = trunc i32 200 to i8\n"
		"\t%s = sext i8 %t to i32\n"
		"\tret i32 %s\n}\n"));
	AssertInt(200, TestIR65Main(
		"function i32 @_main()\n{\nb:\n"
		"\t%t = trunc i32 200 to i8\n"
		"\t%s = zext i8 %t to i32\n"
		"\tret i32 %s\n}\n"));
	AssertInt(44, TestIR65Main(
		"function i32 @_main()\n{\nb:\n"
		"\t%a = add i8 100, 200\n"
		"\t%s = zext i8 %a to i32\n"
		"\tret i32 %s\n}\n"));
	//sext of an i1 is 0 or -1, and so compares below 0.
	AssertInt(-1 * 10 + 1, TestIR65Main(
		"function i32 @_Flag__Fi(i32 %x), local\n{\nb:\n\t%c = ne i32 %x, 0\n\t%s = sext i1 %c to i32\n\t%n = slt i1 %c, 0\n\t%z = zext i1 %n to i32\n\t%m = mul i32 %s, 10\n\t%r = add i32 %m, %z\n\tret i32 %r\n}\n\n"
		"function i32 @_main()\n{\nb:\n\t%r = call i32 @_Flag__Fi(i32 5)\n\tret i32 %r\n}\n"));
	AssertInt(1, TestIR65Main(
		"function i32 @_main()\n{\nb:\n"
		"\t%c = slt i8 -1, 1\n"
		"\t%s = zext i1 %c to i32\n"
		"\tret i32 %s\n}\n"));
	AssertInt(0, TestIR65Main(
		"function i32 @_main()\n{\nb:\n"
		"\t%c = ult i8 -1, 1\n"
		"\t%s = zext i1 %c to i32\n"
		"\tret i32 %s\n}\n"));
	AssertInt(-2, TestIR65Main(
		"function i32 @_main()\n{\nb:\n"
		"\t%a = ashr i16 -8, 2\n"
		"\t%s = sext i16 %a to i32\n"
		"\tret i32 %s\n}\n"));
	AssertInt(16382, TestIR65Main(
		"function i32 @_main()\n{\nb:\n"
		"\t%a = lshr i16 -8, 2\n"
		"\t%s = zext i16 %a to i32\n"
		"\tret i32 %s\n}\n"));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIR65BackendDivide(void)
{
	AssertInt(-3, TestIR65Main("function i32 @_main()\n{\nb:\n\t%a = sdiv i32 -7, 2\n\tret i32 %a\n}\n"));
	AssertInt(-1, TestIR65Main("function i32 @_main()\n{\nb:\n\t%a = srem i32 -7, 2\n\tret i32 %a\n}\n"));
	AssertInt(2147483644, TestIR65Main("function i32 @_main()\n{\nb:\n\t%a = udiv i32 -7, 2\n\tret i32 %a\n}\n"));
	AssertInt(1, TestIR65Main("function i32 @_main()\n{\nb:\n\t%a = urem i32 -7, 2\n\tret i32 %a\n}\n"));
	AssertInt(-14, TestIR65Main(
		"function i32 @_main()\n{\nb:\n"
		"\t%a = sdiv i8 -100, 7\n"
		"\t%s = sext i8 %a to i32\n"
		"\tret i32 %s\n}\n"));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIR65BackendWide(void)
{
	AssertLong(1000000000000LL * 3, TestIR65Run(
		"function i64 @_main()\n{\nb:\n"
		"\t%a = mul i64 1000000000000, 3\n"
		"\tret i64 %a\n}\n"));
	AssertLong(-4, TestIR65Run(
		"function i64 @_main()\n{\nb:\n"
		"\t%a = sdiv i64 -9000000000000, 2250000000000\n"
		"\tret i64 %a\n}\n"));
	AssertLong(1, TestIR65Run(
		"function i64 @_main()\n{\nb:\n"
		"\t%c = slt i64 -5000000000, 4000000000\n"
		"\t%r = zext i1 %c to i64\n"
		"\tret i64 %r\n}\n"));
	AssertLong(-1, TestIR65Run(
		"function i64 @_main()\n{\nb:\n"
		"\t%a = ashr i64 -9000000000000, 60\n"
		"\tret i64 %a\n}\n"));
	AssertLong(0xFFFFFFFFLL, TestIR65Run(
		"function i64 @_main()\n{\nb:\n"
		"\t%a = zext i32 -1 to i64\n"
		"\tret i64 %a\n}\n"));
	//A value squared: it is both operands, copied from A to B all 64 bits wide.
	AssertLong(20123405LL * 20123405LL, TestIR65Run(
		"function i64 @_main()\n{\nb:\n"
		"\t%a = add i32 20123404, 1\n"
		"\t%w = sext i32 %a to i64\n"
		"\t%s = mul i64 %w, %w\n"
		"\tret i64 %s\n}\n"));
	AssertLong(-1, TestIR65Run(
		"function i64 @_main()\n{\nb:\n"
		"\t%a = sext i32 -1 to i64\n"
		"\tret i64 %a\n}\n"));
}


//////////////////////////////////////////////////////////////////////////
//
// Narrow memory, slots, a narrow argument and recursion.
//
//////////////////////////////////////////////////////////////////////////
void TestIR65BackendMemory(void)
{
	AssertInt(-1 + 300 + 70000, TestIR65Main(
		"function i32 @_main()\n{\nb:\n"
		"\t%p = slot ptr 8, 4\n"
		"\tstore i32 -1, %p\n"
		"\t%q = ptradd ptr %p, 4\n"
		"\tstore i16 300, %q\n"
		"\t%c = load i8 %p\n"
		"\t%cs = sext i8 %c to i32\n"
		"\t%h = load volatile i16 %q\n"
		"\t%hs = zext i16 %h to i32\n"
		"\t%t = add i32 %cs, %hs\n"
		"\t%r = add i32 %t, 70000\n"
		"\tret i32 %r\n}\n"));

	AssertInt(55, TestIR65Main(
		"function i32 @_Fibonacci__Fc(i8 %n)\n{\n"
		"entry:\n"
		"\t%c = slt i8 %n, 2\n"
		"\tbrif %c, small, large\n"
		"small:\n"
		"\t%r = zext i8 %n to i32\n"
		"\tret i32 %r\n"
		"large:\n"
		"\t%a = sub i8 %n, 1\n"
		"\t%b = sub i8 %n, 2\n"
		"\t%x = call i32 @_Fibonacci__Fc(i8 %a)\n"
		"\t%y = call i32 @_Fibonacci__Fc(i8 %b)\n"
		"\t%s = add i32 %x, %y\n"
		"\tret i32 %s\n"
		"}\n\n"
		"function i32 @_main()\n{\nb:\n"
		"\t%r = call i32 @_Fibonacci__Fc(i8 10)\n"
		"\tret i32 %r\n}\n"));
}


//////////////////////////////////////////////////////////////////////////
//
// A variadic function walks its arguments from argaddr; a function pointer
// call; a thiscall.
//
//////////////////////////////////////////////////////////////////////////
void TestIR65BackendCalls(void)
{
	AssertInt(1 + 20 + 300, TestIR65Main(
		"function i32 @_SumAll(i32 %count, ...)\n{\n"
		"entry:\n"
		"\t%first = argaddr ptr 0\n"
		"\t%p0 = ptradd ptr %first, 4\n"
		"\tjmp loop\n"
		"loop:\n"
		"\t%s = phi i32 [entry, 0], [body, %s2]\n"
		"\t%i = phi i32 [entry, 0], [body, %i2]\n"
		"\t%p = phi ptr [entry, %p0], [body, %p2]\n"
		"\t%c = slt i32 %i, %count\n"
		"\tbrif %c, body, exit\n"
		"body:\n"
		"\t%v = load i32 %p\n"
		"\t%s2 = add i32 %s, %v\n"
		"\t%i2 = add i32 %i, 1\n"
		"\t%p2 = ptradd ptr %p, 4\n"
		"\tjmp loop\n"
		"exit:\n"
		"\tret i32 %s\n"
		"}\n\n"
		"function i32 @_main()\n{\nb:\n"
		"\t%r = call i32 @_SumAll(i32 3, ..., i32 1, i32 20, i32 300)\n"
		"\tret i32 %r\n}\n"));

	AssertInt(12, TestIR65Main(
		"function i32 @_Double__Fi(i32 %x)\n{\nb:\n\t%r = add i32 %x, %x\n\tret i32 %r\n}\n\n"
		"function i32 @_main()\n{\nb:\n"
		"\t%f = copy ptr @_Double__Fi\n"
		"\t%r = call i32 %f(i32 6)\n"
		"\tret i32 %r\n}\n"));

	AssertInt(7 + 5, TestIR65Main(
		"global @_gObject, align 4 { i32 7 }\n\n"
		"function i32 @_C__Get__Fi(ptr %this, i32 %x), thiscall\n{\nb:\n"
		"\t%v = load i32 %this\n"
		"\t%r = add i32 %v, %x\n"
		"\tret i32 %r\n}\n\n"
		"function i32 @_main()\n{\nb:\n"
		"\t%r = call thiscall i32 @_C__Get__Fi(ptr @_gObject, i32 5)\n"
		"\tret i32 %r\n}\n"));
}


//////////////////////////////////////////////////////////////////////////
//
// Floats through the soft float runtime.
//
//////////////////////////////////////////////////////////////////////////
void TestIR65BackendFloat(void)
{
	//(1.5 + 2.25) * 4 = 15.
	AssertInt(15, TestIR65Main(
		"function i32 @_main()\n{\nb:\n"
		"\t%a = fadd f32 1.5, 2.25\n"
		"\t%m = fmul f32 %a, 4\n"
		"\t%i = ftosi f32 %m to i32\n"
		"\tret i32 %i\n}\n", true));
	AssertInt(-3, TestIR65Main(
		"function i32 @_main()\n{\nb:\n"
		"\t%a = sitof i32 7 to f64\n"
		"\t%d = fdiv f64 %a, -2\n"
		"\t%n = fneg f64 %d\n"
		"\t%s = fsub f64 0.5, %n\n"
		"\t%i = ftosi f64 %s to i32\n"
		"\tret i32 %i\n}\n", true));
	AssertInt(1, TestIR65Main(
		"function i32 @_main()\n{\nb:\n"
		"\t%a = fext f32 0.25 to f64\n"
		"\t%c = flt f64 %a, 0.5\n"
		"\tbrif %c, yes, no\n"
		"yes:\n\tret i32 1\n"
		"no:\n\tret i32 0\n}\n", true));
}


//////////////////////////////////////////////////////////////////////////
//
// Register allocation: a loop's values in X, Y and pseudo registers; phis
// that rotate; values kept across calls (in the pseudo registers a function
// keeps, so recursion must keep them); more values than homes; mul and div
// around values kept in Y; narrow loads into a register through itself.
//
//////////////////////////////////////////////////////////////////////////
void TestIR65BackendAllocation(void)
{
	CChars	szAssembly;
	CChars	szSum;
	CChars	szIR;
	int		i;
	int32	iExpected;

	szAssembly.Init();
	AssertInt(10 + 20 + 30, (int32)TestIR65Run(
		"global @_gTable, align 4 { i32 10, i32 20, i32 30 }\n\n"
		"function i32 @_Sum__FPii(ptr %p, i32 %n), local\n"
		"{\n"
		"entry:\n"
		"\tjmp loop\n"
		"loop:\n"
		"\t%s = phi i32 [entry, 0], [body, %s2]\n"
		"\t%i = phi i32 [entry, 0], [body, %i2]\n"
		"\t%c = slt i32 %i, %n\n"
		"\tbrif %c, body, exit\n"
		"body:\n"
		"\t%o = shl i32 %i, 2\n"
		"\t%a = ptradd ptr %p, %o\n"
		"\t%v = load i32 %a\n"
		"\t%s2 = add i32 %s, %v\n"
		"\t%i2 = add i32 %i, 1\n"
		"\tjmp loop\n"
		"exit:\n"
		"\tret i32 %s\n"
		"}\n\n"
		"function i32 @_main()\n{\nb:\n"
		"\t%r = call i32 @_Sum__FPii(ptr @_gTable, i32 3)\n"
		"\tret i32 %r\n}\n", false, &szAssembly));
	szSum.Init();
	szSum.AppendSubString(szAssembly, 0, szAssembly.Find("\t\t.section text._main"));
	AssertString(
		"\t\t.section text._Sum__FPii\n"
		"_Sum__FPii:\n"
		"\t\tcpy A, [5 + S]\n"
		"\t\tcpy [0 + W], A\n"
		"\t\tcpy A, [9 + S]\n"
		"\t\tcpy [4 + W], A\n"
		"L1:\n"
		"\t\tcpy Y, 0\n"
		"\t\tcpy X, 0\n"
		"\t\tbra L3\n"
		"L2:\n"
		"\t\tcpy A, X\n"
		"\t\tshl A, 2\n"
		"\t\tadd A, [0 + W]\n"
		"\t\tcpy A, [A]\n"
		"\t\tadd Y, A\n"
		"\t\tadd X, 1\n"
		"L3:\n"
		"\t\tcmp X, [4 + W]\n"
		"\t\tbraso (n, v), L2\n"
		"L4:\n"
		"\t\tcpy A, Y\n"
		"L5:\n"
		"\t\tret\n"
		"\n", szSum.Text());
	szSum.Kill();
	szAssembly.Kill();

	//(a, b, c) = (b, c, a) three times leaves them as they started.
	AssertInt(1 * 100 + 2 * 10 + 3, TestIR65Main(
		"function i32 @_main()\n{\n"
		"entry:\n\tjmp loop\n"
		"loop:\n"
		"\t%a = phi i32 [entry, 1], [loop, %b]\n"
		"\t%b = phi i32 [entry, 2], [loop, %c]\n"
		"\t%c = phi i32 [entry, 3], [loop, %a]\n"
		"\t%i = phi i32 [entry, 0], [loop, %i2]\n"
		"\t%i2 = add i32 %i, 1\n"
		"\t%k = ult i32 %i2, 4\n"
		"\tbrif %k, loop, exit\n"
		"exit:\n"
		"\t%a1 = mul i32 %a, 100\n"
		"\t%b1 = mul i32 %b, 10\n"
		"\t%s = add i32 %a1, %b1\n"
		"\t%r = add i32 %s, %c\n"
		"\tret i32 %r\n}\n"));

	//Sum of Triangle(i) for i < 6: the loop's values are kept across the calls, in pseudo registers the callee keeps.
	AssertInt(0 + 1 + 3 + 6 + 10 + 15, TestIR65Main(
		"function i32 @_Triangle__Fi(i32 %n), local\n{\n"
		"entry:\n"
		"\t%z = eq i32 %n, 0\n"
		"\tbrif %z, zero, more\n"
		"zero:\n\tret i32 0\n"
		"more:\n"
		"\t%m = sub i32 %n, 1\n"
		"\t%t = call i32 @_Triangle__Fi(i32 %m)\n"
		"\t%r = add i32 %t, %n\n"
		"\tret i32 %r\n}\n\n"
		"function i32 @_main()\n{\n"
		"entry:\n\tjmp loop\n"
		"loop:\n"
		"\t%s = phi i32 [entry, 0], [body, %s2]\n"
		"\t%i = phi i32 [entry, 0], [body, %i2]\n"
		"\t%c = slt i32 %i, 6\n"
		"\tbrif %c, body, exit\n"
		"body:\n"
		"\t%t = call i32 @_Triangle__Fi(i32 %i)\n"
		"\t%s2 = add i32 %s, %t\n"
		"\t%i2 = add i32 %i, 1\n"
		"\tjmp loop\n"
		"exit:\n\tret i32 %s\n}\n"));

	//Count(n) = 1 + Count(0) + ... + Count(n - 1) = 2^n: its loop's values are in the pseudo registers it keeps, so
	//each call must give the caller's back.
	AssertInt(1 << 6, TestIR65Main(
		"function i32 @_Count__Fi(i32 %n), local\n{\n"
		"entry:\n\tjmp loop\n"
		"loop:\n"
		"\t%s = phi i32 [entry, 1], [body, %s2]\n"
		"\t%i = phi i32 [entry, 0], [body, %i2]\n"
		"\t%c = slt i32 %i, %n\n"
		"\tbrif %c, body, exit\n"
		"body:\n"
		"\t%t = call i32 @_Count__Fi(i32 %i)\n"
		"\t%s2 = add i32 %s, %t\n"
		"\t%i2 = add i32 %i, 1\n"
		"\tjmp loop\n"
		"exit:\n\tret i32 %s\n}\n\n"
		"function i32 @_main()\n{\nb:\n"
		"\t%r = call i32 @_Count__Fi(i32 6)\n"
		"\tret i32 %r\n}\n"));

	//A parameter used once, also written through its argaddr, is read as it was passed.
	AssertInt(5 * 100 + 9, TestIR65Main(
		"function i32 @_Keep__Fi(i32 %x), local\n{\nb:\n"
		"\t%a = argaddr ptr 0\n"
		"\tstore volatile i32 9, %a\n"
		"\t%v = load volatile i32 %a\n"
		"\t%m = mul i32 %x, 100\n"
		"\t%r = add i32 %m, %v\n"
		"\tret i32 %r\n}\n\n"
		"function i32 @_main()\n{\nb:\n\t%r = call i32 @_Keep__Fi(i32 5)\n\tret i32 %r\n}\n"));

	//40 values live at once: more than X, Y and the pseudo registers hold.
	szIR.Init("function i32 @_main()\n{\nb:\n");
	iExpected = 0;
	for (i = 0; i < 40; i++)
	{
		szIR.Append("\t%v")->Append(i)->Append(" = mul i32 ")->Append(i + 1)->Append(", 3\n");
	}
	szIR.Append("\t%s0 = copy i32 %v0\n");
	for (i = 1; i < 40; i++)
	{
		szIR.Append("\t%s")->Append(i)->Append(" = add i32 %s")->Append(i - 1)->Append(", %v")->Append(i)->Append('\n');
	}
	for (i = 0; i < 40; i++)
	{
		iExpected += 3 * (i + 1);
	}
	szIR.Append("\tret i32 %s39\n}\n");
	AssertInt(iExpected, TestIR65Main(szIR.Text()));
	szIR.Kill();

	//mul and div change Y: values live across them aren't kept there.
	AssertInt((7 * 6 + 5) * 1000 + 100 / 7 + 100 % 7 + 11, TestIR65Main(
		"function i32 @_Work__Fiii(i32 %a, i32 %b, i32 %c), local\n{\n"
		"entry:\n"
		"\t%m = mul i32 %a, %b\n"
		"\t%x = add i32 %m, %c\n"
		"\t%k = mul i32 %x, 1000\n"
		"\t%q = udiv i32 100, %a\n"
		"\t%r = urem i32 100, %a\n"
		"\t%t = add i32 %k, %q\n"
		"\t%u = add i32 %t, %r\n"
		"\t%w = add i32 %u, %b\n"
		"\t%y = add i32 %w, %c\n"
		"\tret i32 %y\n}\n\n"
		"function i32 @_main()\n{\nb:\n"
		"\t%r = call i32 @_Work__Fiii(i32 7, i32 6, i32 5)\n"
		"\tret i32 %r\n}\n"));

	//A narrow load whose result is kept in the register its address was in.
	AssertInt(5, TestIR65Main(
		"global @_gText, align 1 { i8 104, i8 101, i8 108, i8 108, i8 111, i8 0 }\n\n"
		"function i32 @_Length__FPc(ptr %s), local\n{\n"
		"entry:\n\tjmp loop\n"
		"loop:\n"
		"\t%p = phi ptr [entry, %s], [body, %p2]\n"
		"\t%c = load i8 %p\n"
		"\t%z = ne i8 %c, 0\n"
		"\tbrif %z, body, exit\n"
		"body:\n"
		"\t%p2 = ptradd ptr %p, 1\n"
		"\tjmp loop\n"
		"exit:\n"
		"\t%a = ptrtoi ptr %p to i32\n"
		"\t%b = ptrtoi ptr %s to i32\n"
		"\t%l = sub i32 %a, %b\n"
		"\tret i32 %l\n}\n\n"
		"function i32 @_main()\n{\nb:\n"
		"\t%r = call i32 @_Length__FPc(ptr @_gText)\n"
		"\tret i32 %r\n}\n"));

	//64 bit phis in pseudo register pairs, and kept across a call.
	AssertLong(3000000000LL * 4 + 7, TestIR65Run(
		"function i64 @_Seven__F(), local\n{\nb:\n\tret i64 7\n}\n\n"
		"function i64 @_main()\n{\n"
		"entry:\n\tjmp loop\n"
		"loop:\n"
		"\t%s = phi i64 [entry, 0], [loop, %s2]\n"
		"\t%i = phi i32 [entry, 0], [loop, %i2]\n"
		"\t%s2 = add i64 %s, 3000000000\n"
		"\t%i2 = add i32 %i, 1\n"
		"\t%c = ult i32 %i2, 4\n"
		"\tbrif %c, loop, exit\n"
		"exit:\n"
		"\t%v = call i64 @_Seven__F()\n"
		"\t%r = add i64 %s2, %v\n"
		"\tret i64 %r\n}\n"));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIR65Backend(void)
{
	BeginTests();

	TypesInit();
	FastFunctionsInit();
	TypeConverterInit();
	NumberInit();
	C65C64InstructionFactory::GetInstance()->Init();

	TestIR65BackendReturn();
	TestIR65BackendLoop();
	TestIR65BackendSwap();
	TestIR65BackendNarrow();
	TestIR65BackendDivide();
	TestIR65BackendWide();
	TestIR65BackendMemory();
	TestIR65BackendCalls();
	TestIR65BackendFloat();
	TestIR65BackendAllocation();

	C65C64InstructionFactory::GetInstance()->Kill();
	NumberKill();
	TypeConverterKill();
	FastFunctionsKill();
	TypesKill();

	TestStatistics();
}
