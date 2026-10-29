#include <string.h>
#include "BaseLib/TypeNames.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/NumberControl.h"
#include "MicroprocessorLib/W65C816InstructionFactory.h"
#include "MicroprocessorLib/65C64InstructionFactory.h"
#include "Assembler65Lib/Asm816Assembler.h"
#include "Assembler65Lib/Asm816Lockstep.h"
#include "Assembler65Lib/Asm65Linker.h"
#include "Assembler65Lib/Asm65Memory.h"
#include "CppParserLib/IRParser.h"
#include "CppParserLib/IRVerifier.h"
#include "CppParserLib/IR816Backend.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
// The W65C816 back end (CIR816Backend), on IR programs: each runs on CFast65C816 (some in lockstep with the
// CW65C816 simulator too) and must give the result expected and the 65C64 back end's.
//
//////////////////////////////////////////////////////////////////////////


#define TEST_IR816_STEPS		50000000		//The most steps a test program may take.
#define TEST_IR816_MEMORY		0x100000
#define TEST_IR816_STACK_TOP	0xEFFF


int64 TestIR65Run(const char* szIR, bool bFloat, CChars* pszAssembly);


//The start up: the reset vector and its jml stub in bank 0, then main's result (A and X, or 8 bytes through the
//hidden pointer) is stored at Result and the processor stops.
static const char* gszTestIR816StartUp =
	"\t\t.section rodata.Vectors, at $FFFC\n"
	"\t\t.word ResetStub\n"
	"\t\t.section text.ResetStub, at $FF00\n"
	"ResetStub:\n"
	"\t\tjml Start\n"
	"\t\t.section text.Start\n"
	"Start:\n"
	"\t\tclc\n"
	"\t\txce\n"
	"\t\trep (m, x)\n"
	"\t\tlda $EFFF\n"
	"\t\ttcs\n"
	"\t\tlda 0\n"
	"\t\ttcd\n"
	"\t\tjsl _main\n"
	"RESULT"
	"\t\tstp\n"
	"\t\t.section bss.Result\n"
	".global Result\n"
	"Result:\n"
	"\t\t.space 8\n";


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
static bool TestIR816Assemble(CAsm65Object* pcObject, const char* szName, const char* szSource)
{
	CAsm816Assembler	cAssembler;
	bool				bResult;

	pcObject->Init(szName);
	cAssembler.Init();
	bResult = cAssembler.AssembleObject(szSource, pcObject);
	AssertString("", cAssembler.GetErrors());
	cAssembler.Kill();
	return bResult;
}


//////////////////////////////////////////////////////////////////////////
//
// Parses and verifies szIR, generates it (and the runtime routines it uses) with the W65C816 back end, links it
// with the start up and runs it.  Returns main's result, sign extended from its type.
//
//////////////////////////////////////////////////////////////////////////
int64 TestIR816Run(const char* szIR, bool bLockstep, CChars* pszAssembly = NULL)
{
	CIRModule		cModule;
	CCPPErrors		cErrors;
	CIRParser		cParser;
	CIRVerifier		cVerifier;
	CIR816Backend	cBackend;
	CChars			szCode;
	CChars			szRuntime;
	CChars			szStartUp;
	int				iLabels;
	CAsm65Object	acObjects[3];
	CAsm65Linker	cLinker;
	CAsm65Memory	cMemory;
	CFast65C816		cFast;
	CAsm816Lockstep	cLockstep;
	CIRFunction*	pcMain;
	SIRType			sReturn;
	int64			iResult;
	int64			lliResult;
	size			uiSteps;
	bool			bWide;
	int				i;

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

	pcMain = cModule.FindFunction((uint32)cModule.FindSymbol("_main"));
	sReturn = pcMain ? pcMain->msReturnType : IRType(IRTK_I32);
	bWide = sReturn.Is(IRTK_I64);

	szCode.Init();
	szRuntime.Init();
	iLabels = 0;
	cBackend.Init(&cModule, &iLabels);
	AssertTrue(cBackend.GenerateModule(&szCode, &cErrors));
	AssertTrue(CIR816Backend::GenerateRuntime(cBackend.GetRuntime(), &iLabels, &szRuntime, &cErrors));
	AssertString("", cErrors.Text());
	cBackend.Kill();
	if (pszAssembly)
	{
		pszAssembly->Append(szCode);
	}

	szStartUp.Init(gszTestIR816StartUp);
	szStartUp.Replace("\t\tjsl", bWide ? "\t\tpea Result >> 16\n\t\tpea Result & $FFFF\n\t\tjsl" : "\t\tjsl");
	szStartUp.Replace("RESULT", bWide ? "" : "\t\tsta [Result]:24\n\t\ttxa\n\t\tsta [Result + 2]:24\n");
	lliResult = -1;
	if (TestIR816Assemble(&acObjects[0], "startup", szStartUp.Text()) &&
		TestIR816Assemble(&acObjects[1], "ir", szCode.Text()) &&
		TestIR816Assemble(&acObjects[2], "runtime", szRuntime.Text()))
	{
		cLinker.Init();
		cLinker.SetBankSize(0x10000);
		cLinker.SetAddress(ASK65_Text, 0x010000);
		for (i = 0; i < 3; i++)
		{
			cLinker.AddObject(&acObjects[i]);
		}
		AssertTrue(cLinker.Link());
		AssertString("", cLinker.GetErrors());
		AssertTrue(cLinker.GetSymbol("Result", &iResult));

		cMemory.Init(TEST_IR816_MEMORY);
		cMemory.Load(cLinker.GetOutput());
		cMemory.InitFast816(&cFast);
		cFast.Reset();
		if (bLockstep)
		{
			cLockstep.Init(&cMemory, &cFast);
			uiSteps = cLockstep.Run(TEST_IR816_STEPS, 64);
			AssertString("", cLockstep.GetDifferences());
			cLockstep.Kill();
		}
		else
		{
			uiSteps = cFast.Run(TEST_IR816_STEPS);
		}
		AssertTrue(uiSteps < TEST_IR816_STEPS);
		AssertTrue(cFast.IsStopped());
		AssertIntHex(bWide ? TEST_IR816_STACK_TOP - 4 : TEST_IR816_STACK_TOP, cFast.GetS());
		AssertInt(0, (int)cMemory.NumBadAccesses());
		lliResult = (int64)cMemory.GetQuad((uint32)iResult);
		if (!bWide)
		{
			lliResult = IRSignExtend(sReturn, (uint64)lliResult);
		}
		cFast.Kill();
		cMemory.Kill();
		cLinker.Kill();
	}
	for (i = 0; i < 3; i++)
	{
		acObjects[i].Kill();
	}
	szStartUp.Kill();
	szRuntime.Kill();
	szCode.Kill();
	cErrors.Kill();
	cModule.Kill();
	return lliResult;
}


//////////////////////////////////////////////////////////////////////////
//
// The expected result, the W65C816's and the 65C64's.
//
//////////////////////////////////////////////////////////////////////////
static void AssertIR816(int64 lliExpected, const char* szIR, bool bLockstep = false)
{
	int64	lliResult65;

	AssertLong(lliExpected, TestIR816Run(szIR, bLockstep));
	lliResult65 = TestIR65Run(szIR, false, NULL);
	if (strstr(szIR, "function i64 @_main") == NULL)
	{
		lliResult65 = (int32)lliResult65;
	}
	AssertLong(lliExpected, lliResult65);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIR816BackendBasics(void)
{
	CChars	szAssembly;

	szAssembly.Init();
	AssertLong(42, TestIR816Run("function i32 @_main()\n{\nb:\n\tret i32 42\n}\n", true, &szAssembly));
	AssertString(
		"\t\t.section text._main\n"
		"\t\t.global _main\n"
		"_main:\n"
		"\t\t.width (A, X), 16\n"
		"\t\t.relax\n"
		"\t\tphd\n"
		"\t\ttsc\n"
		"\t\tsec\n"
		"\t\tsbc 22\n"
		"\t\ttcs\n"
		"\t\ttcd\n"
		"L1:\n"
		"\t\tldx 0\n"
		"\t\tlda 42\n"
		"\t\ttay\n"
		"\t\ttdc\n"
		"\t\tclc\n"
		"\t\tadc 22\n"
		"\t\ttcs\n"
		"\t\ttya\n"
		"\t\tpld\n"
		"\t\trtl\n"
		"\n", szAssembly.Text());
	szAssembly.Kill();

	AssertIR816(-7, "function i32 @_main()\n{\nb:\n\t%x = sub i32 3, 10\n\tret i32 %x\n}\n", true);
	AssertIR816(0x12345678 ^ 0x0F0F0F0F, "function i32 @_main()\n{\nb:\n\t%x = xor i32 305419896, 252645135\n\tret i32 %x\n}\n");
	AssertIR816(-305419897, "function i32 @_main()\n{\nb:\n\t%x = not i32 305419896\n\tret i32 %x\n}\n");
	AssertIR816(-100000, "function i32 @_main()\n{\nb:\n\t%x = neg i32 100000\n\tret i32 %x\n}\n");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIR816BackendLoops(void)
{
	AssertIR816(150,
		"global @_gTable, align 4 { i32 10, i32 20, i32 30, i32 40, i32 50 }\n"
		"\n"
		"function i32 @_Sum__FPii(ptr %p, i32 %n)\n"
		"{\n"
		"entry:\n\tjmp loop\n"
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
		"exit:\n\tret i32 %s\n"
		"}\n\n"
		"function i32 @_main()\n{\nb:\n"
		"\t%r = call i32 @_Sum__FPii(ptr @_gTable, i32 5)\n"
		"\tret i32 %r\n}\n", true);

	//Phis that swap (and rotate) must all be read before any is written.
	AssertIR816(1 * 1000 + 2,
		"function i32 @_main()\n{\n"
		"entry:\n\tjmp loop\n"
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
		"\tret i32 %r\n}\n");
	AssertIR816(1 * 100 + 2 * 10 + 3,
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
		"\tret i32 %r\n}\n");
}


//////////////////////////////////////////////////////////////////////////
//
// i1, i8 and i16 wrap, extend and compare by their own widths.
//
//////////////////////////////////////////////////////////////////////////
void TestIR816BackendNarrow(void)
{
	AssertIR816(-56, "function i32 @_main()\n{\nb:\n\t%t = trunc i32 200 to i8\n\t%s = sext i8 %t to i32\n\tret i32 %s\n}\n");
	AssertIR816(200, "function i32 @_main()\n{\nb:\n\t%t = trunc i32 200 to i8\n\t%s = zext i8 %t to i32\n\tret i32 %s\n}\n");
	AssertIR816(44, "function i32 @_main()\n{\nb:\n\t%a = add i8 100, 200\n\t%s = zext i8 %a to i32\n\tret i32 %s\n}\n");
	AssertIR816(-2, "function i32 @_main()\n{\nb:\n\t%a = ashr i16 -8, 2\n\t%s = sext i16 %a to i32\n\tret i32 %s\n}\n");
	AssertIR816(16382, "function i32 @_main()\n{\nb:\n\t%a = lshr i16 -8, 2\n\t%s = zext i16 %a to i32\n\tret i32 %s\n}\n");
	AssertIR816(-4, "function i32 @_main()\n{\nb:\n\t%a = ashr i8 -16, 2\n\t%s = sext i8 %a to i32\n\tret i32 %s\n}\n");
	AssertIR816(1, "function i32 @_main()\n{\nb:\n\t%c = slt i8 -1, 1\n\t%s = zext i1 %c to i32\n\tret i32 %s\n}\n");
	AssertIR816(0, "function i32 @_main()\n{\nb:\n\t%c = ult i8 -1, 1\n\t%s = zext i1 %c to i32\n\tret i32 %s\n}\n");

	//Signed i8 and i16 comparisons of parameters: -1 < 1, 1 > -1, -2 <= -2, -32768 < 32767, 100 > -1, 127 >= -128.
	AssertIR816(111111,
		"function i32 @_C__Fcc(i8 %a, i8 %b, i16 %c, i16 %d), local\n{\nb:\n"
		"\t%1 = slt i8 %a, %b\n\t%2 = sgt i8 %b, %a\n\t%3 = sle i8 %a, %a\n\t%4 = slt i16 %c, %d\n"
		"\t%5 = sgt i8 %b, -1\n\t%6 = sge i8 %b, %a\n"
		"\t%z1 = zext i1 %1 to i32\n\t%z2 = zext i1 %2 to i32\n\t%z3 = zext i1 %3 to i32\n\t%z4 = zext i1 %4 to i32\n\t%z5 = zext i1 %5 to i32\n\t%z6 = zext i1 %6 to i32\n"
		"\t%m1 = mul i32 %z1, 100000\n\t%m2 = mul i32 %z2, 10000\n\t%m3 = mul i32 %z3, 1000\n\t%m4 = mul i32 %z4, 100\n\t%m5 = mul i32 %z5, 10\n"
		"\t%s1 = add i32 %m1, %m2\n\t%s2 = add i32 %s1, %m3\n\t%s3 = add i32 %s2, %m4\n\t%s4 = add i32 %s3, %m5\n\t%s5 = add i32 %s4, %z6\n"
		"\tret i32 %s5\n}\n\n"
		"function i32 @_main()\n{\nb:\n\t%r = call i32 @_C__Fcc(i8 -1, i8 1, i16 -32768, i16 32767)\n\tret i32 %r\n}\n", true);

	//sext of an i1 is 0 or -1, and so compares below 0.
	AssertIR816(-1 * 10 + 1,
		"function i32 @_Flag__Fi(i32 %x), local\n{\nb:\n\t%c = ne i32 %x, 0\n\t%s = sext i1 %c to i32\n\t%n = slt i1 %c, 0\n\t%z = zext i1 %n to i32\n\t%m = mul i32 %s, 10\n\t%r = add i32 %m, %z\n\tret i32 %r\n}\n\n"
		"function i32 @_main()\n{\nb:\n\t%r = call i32 @_Flag__Fi(i32 5)\n\tret i32 %r\n}\n");

	//32 bit compares: INT_MIN > 0 is false, INT_MIN <= 0 true, 5 > 0 true, -1 > -1 false; unsigned too.
	AssertIR816(1101,
		"function i32 @_P__Fiii(i32 %a, i32 %b, i32 %c), local\n{\nb:\n"
		"\t%1 = sgt i32 %a, 0\n\t%2 = sle i32 %a, 0\n\t%3 = sgt i32 %b, 0\n\t%4 = sgt i32 %c, -1\n\t%5 = ugt i32 %a, %b\n"
		"\t%z1 = zext i1 %1 to i32\n\t%z2 = zext i1 %2 to i32\n\t%z3 = zext i1 %3 to i32\n\t%z4 = zext i1 %4 to i32\n\t%z5 = zext i1 %5 to i32\n"
		"\t%m1 = mul i32 %z1, 10000\n\t%m2 = mul i32 %z2, 1000\n\t%m3 = mul i32 %z3, 100\n\t%m4 = mul i32 %z4, 10\n"
		"\t%s1 = add i32 %m1, %m2\n\t%s2 = add i32 %s1, %m3\n\t%s3 = add i32 %s2, %m4\n\t%s4 = add i32 %s3, %z5\n\tret i32 %s4\n}\n\n"
		"function i32 @_main()\n{\nb:\n\t%r = call i32 @_P__Fiii(i32 -2147483648, i32 5, i32 -1)\n\tret i32 %r\n}\n");

	//A three way compare, twice.
	AssertIR816(-99 * 2,
		"function i32 @_Cmp__Fcc(i8 %a, i8 %b), local\n{\nx:\n\t%l = slt i8 %a, %b\n\tbrif %l, y, z\ny:\n\tret i32 -1\n"
		"z:\n\t%g = ne i8 %a, %b\n\tbrif %g, w, v\nw:\n\tret i32 1\nv:\n\tret i32 0\n}\n\n"
		"function i32 @_Cmp__Fii(i32 %a, i32 %b), local\n{\nx:\n\t%l = slt i32 %a, %b\n\tbrif %l, y, z\ny:\n\tret i32 -1\n"
		"z:\n\t%g = ne i32 %b, %a\n\tbrif %g, w, v\nw:\n\tret i32 1\nv:\n\tret i32 0\n}\n\n"
		"function i32 @_main()\n{\nb:\n"
		"\t%1 = call i32 @_Cmp__Fcc(i8 -2, i8 2)\n\t%2 = call i32 @_Cmp__Fcc(i8 -2, i8 -2)\n\t%3 = call i32 @_Cmp__Fcc(i8 3, i8 -2)\n"
		"\t%4 = call i32 @_Cmp__Fii(i32 1, i32 2)\n\t%5 = call i32 @_Cmp__Fii(i32 2, i32 2)\n\t%6 = call i32 @_Cmp__Fii(i32 3, i32 2)\n"
		"\t%m1 = mul i32 %1, 100\n\t%m2 = mul i32 %2, 10\n\t%m4 = mul i32 %4, 100\n\t%m5 = mul i32 %5, 10\n"
		"\t%s1 = add i32 %m1, %m2\n\t%s2 = add i32 %s1, %3\n\t%s3 = add i32 %s2, %m4\n\t%s4 = add i32 %s3, %m5\n\t%s5 = add i32 %s4, %6\n"
		"\tret i32 %s5\n}\n");
}


//////////////////////////////////////////////////////////////////////////
//
// The runtime routines: multiply, divide and remainder at 8, 16, 32 and 64 bits.
//
//////////////////////////////////////////////////////////////////////////
void TestIR816BackendDivide(void)
{
	AssertIR816(-3, "function i32 @_main()\n{\nb:\n\t%a = sdiv i32 -7, 2\n\tret i32 %a\n}\n", true);
	AssertIR816(-1, "function i32 @_main()\n{\nb:\n\t%a = srem i32 -7, 2\n\tret i32 %a\n}\n");
	AssertIR816(2147483644, "function i32 @_main()\n{\nb:\n\t%a = udiv i32 -7, 2\n\tret i32 %a\n}\n");
	AssertIR816(1, "function i32 @_main()\n{\nb:\n\t%a = urem i32 -7, 2\n\tret i32 %a\n}\n");
	AssertIR816(-14, "function i32 @_main()\n{\nb:\n\t%a = sdiv i8 -100, 7\n\t%s = sext i8 %a to i32\n\tret i32 %s\n}\n");
	AssertIR816(-2, "function i32 @_main()\n{\nb:\n\t%a = srem i8 -100, 7\n\t%s = sext i8 %a to i32\n\tret i32 %s\n}\n");
	AssertIR816(-4681, "function i32 @_main()\n{\nb:\n\t%a = sdiv i16 -32768, 7\n\t%s = sext i16 %a to i32\n\tret i32 %s\n}\n");
	AssertIR816(65535 / 3, "function i32 @_main()\n{\nb:\n\t%a = udiv i16 -1, 3\n\t%s = zext i16 %a to i32\n\tret i32 %s\n}\n");
	AssertIR816(4000000000U % 3000000000U, "function i32 @_main()\n{\nb:\n\t%a = urem i32 4000000000, 3000000000\n\tret i32 %a\n}\n");
	AssertIR816(39, "function i32 @_main()\n{\nb:\n\t%a = mul i8 13, 3\n\t%s = zext i8 %a to i32\n\tret i32 %s\n}\n");
	AssertIR816(1234567 * 11 + 1234567 * 255 + 217,
		"function i32 @_B__Fic(i32 %a, i8 %c), local\n{\nb:\n"
		"\t%1 = mul i32 %a, 11\n\t%2 = mul i32 %a, 255\n\t%3 = mul i8 %c, -3\n\t%z = zext i8 %3 to i32\n"
		"\t%s1 = add i32 %1, %2\n\t%s2 = add i32 %s1, %z\n\tret i32 %s2\n}\n\n"
		"function i32 @_main()\n{\nb:\n\t%r = call i32 @_B__Fic(i32 1234567, i8 13)\n\tret i32 %r\n}\n");
	AssertIR816(123 * 1000 + 4 + 34 * 1000 + 12,
		"function i32 @_D__Fjj(i32 %a, i32 %b, i32 %c), local\n{\nb:\n"
		"\t%q = udiv i32 %a, %b\n\t%m = mul i32 %q, 1000\n\t%r = urem i32 %a, %b\n\t%s = add i32 %m, %r\n"
		"\t%r2 = urem i32 %a, %c\n\t%m2 = mul i32 %r2, 1000\n\t%q2 = udiv i32 %a, %c\n\t%s2 = add i32 %m2, %q2\n"
		"\t%t = add i32 %s, %s2\n\tret i32 %t\n}\n\n"
		"function i32 @_main()\n{\nb:\n\t%r = call i32 @_D__Fjj(i32 1234, i32 10, i32 100)\n\tret i32 %r\n}\n");
}


//////////////////////////////////////////////////////////////////////////
//
// The runtime divide's paths (R816_UDiv32 and R816_UDiv64 in IR816Backend.cpp), with values passed in so they aren't
// worked out when compiled: both under 65536, a divisor under 65536 with a dividend's high word below it and not
// (and a divisor of 65535, which carries out of A), a dividend below the divisor, a divisor of 1, a dividend under 256,
// a wide divisor with a narrow dividend and with a wide one; 64
// bits with zero words at the top of the dividend skipped and not.
//
//////////////////////////////////////////////////////////////////////////
void TestIR816BackendDividePaths(void)
{
	static const uint32	auiPairs32[][2] = { { 60000, 7 }, { 0x0003FFFF, 10 }, { 4000000000U, 7 }, { 0xFFFFFFFF, 0xFFFF }, { 0xFFFFFFFF, 0x8001 },
											{ 1234, 100000 }, { 4000000000U, 70000 }, { 0xFFFFFFFF, 0x10000 }, { 65535, 65535 }, { 0x0000FFFF, 0x0000FFFF },
											{ 5, 9 }, { 200, 7 }, { 255, 16 }, { 40000, 1 }, { 0x12345678, 1 }, { 0x12345678, 0x1234 } };
	static const uint64	auiPairs64[][2] = { { 0xFFFFFFFFULL, 7 }, { 0x8000000000000005ULL, 3 }, { 12345, 0x100000000ULL }, { 0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFULL },
											{ 0x123456789ABCDEFULL, 0x10001ULL }, { 5, 5 } };
	char				sz[1024];
	size				i;
	CChars				szAssembly;

	//The values reach the routines (they aren't worked out by inlining).
	szAssembly.Init();
	snprintf(sz, sizeof(sz), "function i32 @_D__Fjj(i32 %%a, i32 %%b), local\n{\nb:\n\t%%q = udiv i32 %%a, %%b\n\tret i32 %%q\n}\n\n"
		"function i32 @_main()\n{\nb:\n\t%%r = call i32 @_D__Fjj(i32 %u, i32 %u)\n\tret i32 %%r\n}\n", auiPairs32[0][0], auiPairs32[0][1]);
	AssertLong(auiPairs32[0][0] / auiPairs32[0][1], TestIR816Run(sz, false, &szAssembly));
	AssertTrue(szAssembly.Contains("jsl R816_UDiv32"));
	szAssembly.Kill();

	for (i = 0; i < sizeof(auiPairs32) / sizeof(auiPairs32[0]); i++)
	{
		snprintf(sz, sizeof(sz), "function i32 @_D__Fjj(i32 %%a, i32 %%b), local\n{\nb:\n\t%%q = udiv i32 %%a, %%b\n\tret i32 %%q\n}\n\n"
			"function i32 @_main()\n{\nb:\n\t%%r = call i32 @_D__Fjj(i32 %u, i32 %u)\n\tret i32 %%r\n}\n", auiPairs32[i][0], auiPairs32[i][1]);
		AssertIR816((int32)(auiPairs32[i][0] / auiPairs32[i][1]), sz);
		snprintf(sz, sizeof(sz), "function i32 @_D__Fjj(i32 %%a, i32 %%b), local\n{\nb:\n\t%%q = urem i32 %%a, %%b\n\tret i32 %%q\n}\n\n"
			"function i32 @_main()\n{\nb:\n\t%%r = call i32 @_D__Fjj(i32 %u, i32 %u)\n\tret i32 %%r\n}\n", auiPairs32[i][0], auiPairs32[i][1]);
		AssertIR816((int32)(auiPairs32[i][0] % auiPairs32[i][1]), sz);
	}
	for (i = 0; i < sizeof(auiPairs64) / sizeof(auiPairs64[0]); i++)
	{
		snprintf(sz, sizeof(sz), "function i64 @_D__Fyy(i64 %%a, i64 %%b), local\n{\nb:\n\t%%q = udiv i64 %%a, %%b\n\tret i64 %%q\n}\n\n"
			"function i64 @_main()\n{\nb:\n\t%%r = call i64 @_D__Fyy(i64 %llu, i64 %llu)\n\tret i64 %%r\n}\n", (unsigned long long)auiPairs64[i][0], (unsigned long long)auiPairs64[i][1]);
		AssertIR816((int64)(auiPairs64[i][0] / auiPairs64[i][1]), sz);
		snprintf(sz, sizeof(sz), "function i64 @_D__Fyy(i64 %%a, i64 %%b), local\n{\nb:\n\t%%q = urem i64 %%a, %%b\n\tret i64 %%q\n}\n\n"
			"function i64 @_main()\n{\nb:\n\t%%r = call i64 @_D__Fyy(i64 %llu, i64 %llu)\n\tret i64 %%r\n}\n", (unsigned long long)auiPairs64[i][0], (unsigned long long)auiPairs64[i][1]);
		AssertIR816((int64)(auiPairs64[i][0] % auiPairs64[i][1]), sz);
	}
}


//////////////////////////////////////////////////////////////////////////
//
// Unsigned 32 bit compares branch on the high words' Z, then on the low words' C: the peephole mustn't take the
// compare of a high word with 0 out (its carry is read after the branch, a label and a .width away).
//
//////////////////////////////////////////////////////////////////////////
void TestIR816BackendCompareCarry(void)
{
	static const uint32	auiPairs[][2] = { { 0x10000, 4 }, { 3, 4 }, { 4, 4 }, { 5, 4 }, { 0, 0x10000 }, { 0x20000, 0x10000 }, { 0x10003, 0x10004 } };
	char				sz[512];
	size				i;

	for (i = 0; i < sizeof(auiPairs) / sizeof(auiPairs[0]); i++)
	{
		snprintf(sz, sizeof(sz), "function i32 @_C__Fjj(i32 %%a, i32 %%b), local\n{\nb:\n\t%%c = ult i32 %%a, %%b\n\tbrif %%c, y, n\n"
			"y:\n\tret i32 1\nn:\n\t%%d = uge i32 %%a, 4\n\tbrif %%d, g, l\ng:\n\tret i32 2\nl:\n\tret i32 3\n}\n\n"
			"function i32 @_main()\n{\nb:\n\t%%r = call i32 @_C__Fjj(i32 %u, i32 %u)\n\tret i32 %%r\n}\n", auiPairs[i][0], auiPairs[i][1]);
		AssertIR816((auiPairs[i][0] < auiPairs[i][1]) ? 1 : ((auiPairs[i][0] >= 4) ? 2 : 3), sz);
	}
}


//////////////////////////////////////////////////////////////////////////
//
// A result shares the place of an argument that dies where it is defined (and a loop's next value its phi's place),
// but not of one still live after it: a call's result that is never used is only live where it is written, and a
// shift's count is read after its value is copied to the result.
//
//////////////////////////////////////////////////////////////////////////
void TestIR816BackendSharedPlaces(void)
{
	AssertIR816(42,
		"function i32 @_Seven__Fi(i32 %x), local\n{\nb:\n\tret i32 7\n}\n\n"
		"function i32 @_main()\n{\nb:\n\t%a = add i32 40, 2\n\t%r = call i32 @_Seven__Fi(i32 %a)\n\tret i32 %a\n}\n");

	AssertIR816(126,
		"function i32 @_Seven__Fi(i32 %x), local\n{\nb:\n\tret i32 7\n}\n\n"
		"function i32 @_main()\n{\n"
		"entry:\n\t%p = add i32 40, 2\n\tjmp loop\n"
		"loop:\n"
		"\t%i = phi i32 [entry, 0], [loop, %i2]\n"
		"\t%r = call i32 @_Seven__Fi(i32 %p)\n"
		"\t%i2 = add i32 %i, %p\n"
		"\t%c = ult i32 %i2, 100\n"
		"\tbrif %c, loop, exit\n"
		"exit:\n\tret i32 %i2\n}\n", true);

	AssertIR816((((1000 - 42) ^ 255) << 2 << 2) + (2 << 2),
		"function i32 @_main()\n{\nb:\n"
		"\t%a = add i32 40, 2\n"
		"\t%b = sub i32 1000, %a\n"
		"\t%c = xor i32 %b, 255\n"
		"\t%d = shl i32 %c, 2\n"
		"\t%k = add i32 1, 1\n"
		"\t%e = shl i32 %d, %k\n"
		"\t%j = add i32 1, 1\n"
		"\t%f = shl i32 %j, %j\n"
		"\t%g = add i32 %e, %f\n"
		"\tret i32 %g\n}\n", true);
}


//////////////////////////////////////////////////////////////////////////
//
// Shifts by a count only known at run time (in X, a word in A, a whole word
// moved first for 16 or more) and by constants, of 16 and 32 bit values.
//
//////////////////////////////////////////////////////////////////////////
void TestIR816BackendShifts(void)
{
	static const int	aiCounts[] = { 0, 1, 5, 15, 16, 17, 31 };
	static const char*	aszOpcodes[] = { "shl", "lshr", "ashr" };
	char				sz[512];
	size				i;
	size				j;
	int64				lliExpected;
	uint32				uiValue;
	uint16				uiShort;

	uiValue = 0x9234ABCD;
	uiShort = 0x9A5C;
	for (i = 0; i < sizeof(aiCounts) / sizeof(aiCounts[0]); i++)
	{
		for (j = 0; j < 3; j++)
		{
			lliExpected = (j == 0) ? (int32)(uiValue << aiCounts[i]) : ((j == 1) ? (int32)(uiValue >> aiCounts[i]) : ((int32)uiValue >> aiCounts[i]));
			snprintf(sz, sizeof(sz), "function i32 @_S__Fl(i32 %%n), local\n{\nb:\n\t%%r = %s i32 %u, %%n\n\tret i32 %%r\n}\n\n"
				"function i32 @_main()\n{\nb:\n\t%%r = call i32 @_S__Fl(i32 %d)\n\tret i32 %%r\n}\n", aszOpcodes[j], uiValue, aiCounts[i]);
			AssertIR816(lliExpected, sz);
			snprintf(sz, sizeof(sz), "function i32 @_main()\n{\nb:\n\t%%r = %s i32 %u, %d\n\tret i32 %%r\n}\n", aszOpcodes[j], uiValue, aiCounts[i]);
			AssertIR816(lliExpected, sz);

			if (aiCounts[i] < 16)
			{
				lliExpected = (j == 0) ? (int16)(uint16)(uiShort << aiCounts[i]) : ((j == 1) ? (int16)(uiShort >> aiCounts[i]) : ((int16)uiShort >> aiCounts[i]));
				snprintf(sz, sizeof(sz), "function i16 @_S__Fs(i16 %%n), local\n{\nb:\n\t%%r = %s i16 %u, %%n\n\tret i16 %%r\n}\n\n"
					"function i32 @_main()\n{\nb:\n\t%%r = call i16 @_S__Fs(i16 %d)\n\t%%w = sext i16 %%r to i32\n\tret i32 %%w\n}\n", aszOpcodes[j], uiShort, aiCounts[i]);
				AssertIR816(lliExpected, sz);
			}
		}
	}
}


//////////////////////////////////////////////////////////////////////////
//
// Values kept in X (AllocateX): a loop's counter and sum (phis, the counter
// stepped with inx), the counter as the second operand of a sub (through
// the scratch word), and signed compares of a 16 bit value with 0 that
// branch on N and Z.
//
//////////////////////////////////////////////////////////////////////////
void TestIR816BackendX(void)
{
	static const int16	aiValues[] = { -32768, -5, -1, 0, 1, 7, 32767 };
	static const char*	aszCompares[] = { "slt", "sle", "sgt", "sge" };
	char				sz[512];
	CChars				szAssembly;
	size				i;
	size				j;
	int64				lliExpected;

	szAssembly.Init();
	AssertLong(4950, TestIR816Run(
		"function i32 @_main()\n{\n"
		"e:\n\tjmp l\n"
		"l:\n"
		"\t%i = phi i16 [e, 0], [l, %i2]\n"
		"\t%s = phi i16 [e, 0], [l, %s2]\n"
		"\t%s2 = add i16 %s, %i\n"
		"\t%i2 = add i16 %i, 1\n"
		"\t%c = slt i16 %i2, 100\n"
		"\tbrif %c, l, x\n"
		"x:\n\t%r = sext i16 %s2 to i32\n\tret i32 %r\n}\n", false, &szAssembly));
	AssertTrue(szAssembly.Contains("inx"));
	szAssembly.Kill();

	AssertIR816(1000 * 100 - 4950,
		"function i32 @_main()\n{\n"
		"e:\n\tjmp l\n"
		"l:\n"
		"\t%i = phi i16 [e, 0], [l, %i2]\n"
		"\t%s = phi i32 [e, 0], [l, %s2]\n"
		"\t%d = sub i16 1000, %i\n"
		"\t%w = sext i16 %d to i32\n"
		"\t%s2 = add i32 %s, %w\n"
		"\t%i2 = add i16 %i, 1\n"
		"\t%c = ult i16 %i2, 100\n"
		"\tbrif %c, l, x\n"
		"x:\n\tret i32 %s2\n}\n");

	//trunc, zext, sext and a shift by a constant worked out in A and kept in X.
	AssertIR816(4 * 4950 + 1468,
		"function i32 @_main()\n{\n"
		"e:\n\tjmp l\n"
		"l:\n"
		"\t%i = phi i16 [e, 0], [l, %i2]\n"
		"\t%s = phi i16 [e, 0], [l, %s3]\n"
		"\t%b = trunc i16 %i to i8\n"
		"\t%w = zext i8 %b to i16\n"
		"\t%t = shl i16 %w, 2\n"
		"\t%m = ult i16 %i, 100\n"
		"\t%z = zext i1 %m to i16\n"
		"\t%n = sub i16 0, %z\n"
		"\t%u = and i16 %t, %n\n"
		"\t%e = sext i8 %b to i16\n"
		"\t%s2 = add i16 %s, %u\n"
		"\t%s3 = add i16 %s2, %e\n"
		"\t%i2 = add i16 %i, 1\n"
		"\t%c = slt i16 %i2, 200\n"
		"\tbrif %c, l, x\n"
		"x:\n\t%r = sext i16 %s3 to i32\n\tret i32 %r\n}\n");

	for (i = 0; i < sizeof(aiValues) / sizeof(aiValues[0]); i++)
	{
		for (j = 0; j < 4; j++)
		{
			lliExpected = (j == 0) ? (aiValues[i] < 0) : ((j == 1) ? (aiValues[i] <= 0) : ((j == 2) ? (aiValues[i] > 0) : (aiValues[i] >= 0)));
			snprintf(sz, sizeof(sz), "function i32 @_C__Fs(i16 %%x), local\n{\nb:\n\t%%c = %s i16 %%x, 0\n\tbrif %%c, y, n\ny:\n\tret i32 1\nn:\n\tret i32 0\n}\n\n"
				"function i32 @_main()\n{\nb:\n\t%%r = call i32 @_C__Fs(i16 %d)\n\tret i32 %%r\n}\n", aszCompares[j], aiValues[i]);
			AssertIR816(lliExpected, sz);
		}
	}
}


//////////////////////////////////////////////////////////////////////////
//
// 64 bit values: four words, returned through the hidden pointer.
//
//////////////////////////////////////////////////////////////////////////
void TestIR816BackendWide(void)
{
	AssertIR816(1000000000000LL * 3, "function i64 @_main()\n{\nb:\n\t%a = mul i64 1000000000000, 3\n\tret i64 %a\n}\n", true);
	AssertIR816(-4, "function i64 @_main()\n{\nb:\n\t%a = sdiv i64 -9000000000000, 2250000000000\n\tret i64 %a\n}\n");
	AssertIR816(1, "function i64 @_main()\n{\nb:\n\t%c = slt i64 -5000000000, 4000000000\n\t%r = zext i1 %c to i64\n\tret i64 %r\n}\n");
	AssertIR816(-1, "function i64 @_main()\n{\nb:\n\t%a = ashr i64 -9000000000000, 60\n\tret i64 %a\n}\n");
	AssertIR816(0xFFFFFFFFLL, "function i64 @_main()\n{\nb:\n\t%a = zext i32 -1 to i64\n\tret i64 %a\n}\n");
	AssertIR816(-1, "function i64 @_main()\n{\nb:\n\t%a = sext i32 -1 to i64\n\tret i64 %a\n}\n");
	AssertIR816(20123405LL * 20123405LL,
		"function i64 @_main()\n{\nb:\n\t%a = add i32 20123404, 1\n\t%w = sext i32 %a to i64\n\t%s = mul i64 %w, %w\n\tret i64 %s\n}\n");
	AssertIR816(0x123456789ABCDEFLL % 1000000007LL,
		"function i64 @_main()\n{\nb:\n\t%a = urem i64 81985529216486895, 1000000007\n\tret i64 %a\n}\n");

	//A function returning i64 called from one that returns i32.
	AssertIR816(7,
		"function i64 @_Big__Fi(i32 %x), local\n{\nb:\n\t%w = sext i32 %x to i64\n\t%s = shl i64 %w, 40\n\tret i64 %s\n}\n\n"
		"function i32 @_main()\n{\nb:\n\t%r = call i64 @_Big__Fi(i32 7)\n\t%t = lshr i64 %r, 40\n\t%n = trunc i64 %t to i32\n\tret i32 %n\n}\n");
}


//////////////////////////////////////////////////////////////////////////
//
// Narrow memory, slots, recursion, a variadic function, a function pointer and a thiscall.
//
//////////////////////////////////////////////////////////////////////////
void TestIR816BackendMemoryAndCalls(void)
{
	AssertIR816(-1 + 300 + 70000,
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
		"\tret i32 %r\n}\n", true);

	//A byte stored through a pointer leaves the bytes either side alone.
	AssertIR816(0x11AA3344,
		"global @_gWord, align 4 { i32 287454020 }\n\n"
		"function i32 @_main()\n{\nb:\n"
		"\t%p = ptradd ptr @_gWord, 2\n"
		"\tstore i8 -86, %p\n"
		"\t%v = load i32 @_gWord\n"
		"\tret i32 %v\n}\n");

	AssertIR816(55,
		"function i32 @_Fibonacci__Fc(i8 %n)\n{\n"
		"entry:\n\t%c = slt i8 %n, 2\n\tbrif %c, small, large\n"
		"small:\n\t%r = zext i8 %n to i32\n\tret i32 %r\n"
		"large:\n\t%a = sub i8 %n, 1\n\t%b = sub i8 %n, 2\n"
		"\t%x = call i32 @_Fibonacci__Fc(i8 %a)\n\t%y = call i32 @_Fibonacci__Fc(i8 %b)\n"
		"\t%s = add i32 %x, %y\n\tret i32 %s\n}\n\n"
		"function i32 @_main()\n{\nb:\n\t%r = call i32 @_Fibonacci__Fc(i8 10)\n\tret i32 %r\n}\n", true);

	AssertIR816(1 + 20 + 300,
		"function i32 @_SumAll(i32 %count, ...)\n{\n"
		"entry:\n\t%first = argaddr ptr 0\n\t%p0 = ptradd ptr %first, 4\n\tjmp loop\n"
		"loop:\n"
		"\t%s = phi i32 [entry, 0], [body, %s2]\n"
		"\t%i = phi i32 [entry, 0], [body, %i2]\n"
		"\t%p = phi ptr [entry, %p0], [body, %p2]\n"
		"\t%c = slt i32 %i, %count\n"
		"\tbrif %c, body, exit\n"
		"body:\n"
		"\t%v = load i32 %p\n\t%s2 = add i32 %s, %v\n\t%i2 = add i32 %i, 1\n\t%p2 = ptradd ptr %p, 4\n\tjmp loop\n"
		"exit:\n\tret i32 %s\n}\n\n"
		"function i32 @_main()\n{\nb:\n\t%r = call i32 @_SumAll(i32 3, ..., i32 1, i32 20, i32 300)\n\tret i32 %r\n}\n");

	AssertIR816(12,
		"function i32 @_Double__Fi(i32 %x)\n{\nb:\n\t%r = add i32 %x, %x\n\tret i32 %r\n}\n\n"
		"function i32 @_main()\n{\nb:\n\t%f = copy ptr @_Double__Fi\n\t%r = call i32 %f(i32 6)\n\tret i32 %r\n}\n", true);

	AssertIR816(7 + 5,
		"global @_gObject, align 4 { i32 7 }\n\n"
		"function i32 @_C__Get__Fi(ptr %this, i32 %x), thiscall\n{\nb:\n\t%v = load i32 %this\n\t%r = add i32 %v, %x\n\tret i32 %r\n}\n\n"
		"function i32 @_main()\n{\nb:\n\t%r = call thiscall i32 @_C__Get__Fi(ptr @_gObject, i32 5)\n\tret i32 %r\n}\n");

	//Sum of Triangle(i) for i < 6, and Count(n) = 1 + Count(0) + ... + Count(n - 1) = 2^n.
	AssertIR816(0 + 1 + 3 + 6 + 10 + 15,
		"function i32 @_Triangle__Fi(i32 %n), local\n{\n"
		"entry:\n\t%z = eq i32 %n, 0\n\tbrif %z, zero, more\n"
		"zero:\n\tret i32 0\n"
		"more:\n\t%m = sub i32 %n, 1\n\t%t = call i32 @_Triangle__Fi(i32 %m)\n\t%r = add i32 %t, %n\n\tret i32 %r\n}\n\n"
		"function i32 @_main()\n{\n"
		"entry:\n\tjmp loop\n"
		"loop:\n\t%s = phi i32 [entry, 0], [body, %s2]\n\t%i = phi i32 [entry, 0], [body, %i2]\n\t%c = slt i32 %i, 6\n\tbrif %c, body, exit\n"
		"body:\n\t%t = call i32 @_Triangle__Fi(i32 %i)\n\t%s2 = add i32 %s, %t\n\t%i2 = add i32 %i, 1\n\tjmp loop\n"
		"exit:\n\tret i32 %s\n}\n");
}


//////////////////////////////////////////////////////////////////////////
//
// A frame bigger than the direct page's 256 bytes: values past it are reached through X, and an argument past it is
// copied near before it is followed as a pointer.
//
//////////////////////////////////////////////////////////////////////////
void TestIR816BackendBigFrame(void)
{
	CChars	szIR;
	int		i;
	int64	lliExpected;

	szIR.Init("global @_gValue, align 4 { i32 3 }\n\n");
	szIR.Append("function i32 @_Many__FPi(ptr %p), local\n{\nb:\n\t%x = load i32 %p\n");
	lliExpected = 0;
	for (i = 1; i <= 80; i++)
	{
		szIR.Append("\t%v");
		szIR.Append(i);
		szIR.Append(" = mul i32 %x, ");
		szIR.Append(i);
		szIR.AppendNewLine();
		lliExpected += 3 * i;
	}
	szIR.Append("\t%s1 = copy i32 %v1\n");
	for (i = 2; i <= 80; i++)
	{
		szIR.Append("\t%s");
		szIR.Append(i);
		szIR.Append(" = add i32 %s");
		szIR.Append(i - 1);
		szIR.Append(", %v");
		szIR.Append(i);
		szIR.AppendNewLine();
	}
	szIR.Append("\t%y = load i32 %p\n\t%r = add i32 %s80, %y\n\tret i32 %r\n}\n\n");
	szIR.Append("function i32 @_main()\n{\nb:\n\t%r = call i32 @_Many__FPi(ptr @_gValue)\n\tret i32 %r\n}\n");
	AssertIR816(lliExpected + 3, szIR.Text(), true);
	szIR.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIR816Backend(void)
{
	BeginTests();

	TypesInit();
	TypeConverterInit();
	NumberInit();
	C65C64InstructionFactory::GetInstance()->Init();
	CW65C816InstructionFactory::GetInstance()->Init();

	TestIR816BackendBasics();
	TestIR816BackendLoops();
	TestIR816BackendNarrow();
	TestIR816BackendDivide();
	TestIR816BackendDividePaths();
	TestIR816BackendCompareCarry();
	TestIR816BackendSharedPlaces();
	TestIR816BackendShifts();
	TestIR816BackendX();
	TestIR816BackendWide();
	TestIR816BackendMemoryAndCalls();
	TestIR816BackendBigFrame();

	CW65C816InstructionFactory::GetInstance()->Kill();
	C65C64InstructionFactory::GetInstance()->Kill();
	NumberKill();
	TypeConverterKill();
	TypesKill();

	TestStatistics();
}

