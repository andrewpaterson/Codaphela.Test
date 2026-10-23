#include "BaseLib/Chars.h"
#include "MicroprocessorLib/65C64Decoded.h"
#include "TestLib/Assert.h"
#include "TestAsm65Context.h"


//////////////////////////////////////////////////////////////////////////
//
// Four lower case hex digits.
//
//////////////////////////////////////////////////////////////////////////
static void AppendWord(CChars* psz, uint16 uiWord)
{
	static const char	acDigits[17] = "0123456789abcdef";
	int					i;

	for (i = 12; i >= 0; i -= 4)
	{
		psz->Append(acDigits[(uiWord >> i) & 0xF]);
	}
}


//////////////////////////////////////////////////////////////////////////
//
// "line => words" for the line assembled at 1000, with ILLEGAL appended when
// Decode65C64 does not recognise the opcode and ERRORS when assembling failed.
//
//////////////////////////////////////////////////////////////////////////
static void Asm65Words(CChars* psz, const char* szLine)
{
	CAsm65Assembler	cAssembler;
	CChars			szSource;
	S65C64Decoded	sDecoded;
	size			uiBytes;
	size			i;
	uint16			uiWord;

	szSource.Init(".org $1000\n");
	szSource.Append(szLine);
	szSource.AppendNewLine();

	cAssembler.Init();
	psz->Append(szLine);
	psz->Append(" =>");
	if (!cAssembler.Assemble(szSource.Text()))
	{
		psz->Append(" ERRORS ");
		psz->Append(cAssembler.GetErrors());
	}
	else
	{
		uiBytes = cAssembler.GetOutput()->NumBytes();
		for (i = 0; i < uiBytes; i += 2)
		{
			uiWord = cAssembler.GetOutput()->GetWord((uint32)(0x1000 + i));
			psz->Append(" 0x");
			AppendWord(psz, uiWord);
		}
		Decode65C64(cAssembler.GetOutput()->GetWord(0x1000), &sDecoded);
		if (sDecoded.eInstruction == I65_Illegal)
		{
			psz->Append(" ILLEGAL");
		}
	}
	cAssembler.Kill();
	szSource.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
static void AssertAsm65(const char* szLine, const char* szWords, int iLine)
{
	CChars	szExpected;
	CChars	szActual;

	szExpected.Init(szLine);
	szExpected.Append(" => ");
	szExpected.Append(szWords);
	szActual.Init();
	Asm65Words(&szActual, szLine);
	PrivateAssertString(szExpected.Text(), szActual.Text(), true, NULL, iLine, __FILE__);
	szActual.Kill();
	szExpected.Kill();
}


#define AssertAsm(szLine, szWords) AssertAsm65(szLine, szWords, __LINE__)


//////////////////////////////////////////////////////////////////////////
//
// The expected words were worked out by hand from the opcode encoding sheet.
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65EncodingArithmeticLogic(void)
{
	AssertAsm("cpy A, B", "0x2200");
	AssertAsm("cpy A, B:s", "0x2a00");
	AssertAsm("add X, Y", "0xce05");
	AssertAsm("add A, B:s", "0x2415");
	AssertAsm("cpy A, 0", "0x2000");
	AssertAsm("cpy A, 5", "0x24f0");
	AssertAsm("cpy A, -1", "0x3ff0");
	AssertAsm("cpy A, 16", "0x2ff0");
	AssertAsm("cpy A, 17", "0x2110 0x0011");
	AssertAsm("cpy A, $1234", "0x2210 0x1234");
	AssertAsm("cpy A, -200", "0x2a10 0xff38");
	AssertAsm("cpy A, 17:16", "0x2210 0x0011");
	AssertAsm("cpy A, $4:s8", "0x2910 0x0004");
	AssertAsm("cpy A, -1:s16", "0x2a10 0xffff");
	AssertAsm("cpy A, -32768:16", "0x2a10 0x8000");
	AssertAsm("cpy A, $123456789A", "0x2510 0x789a 0x3456 0x0012");
	AssertAsm("cpy A, $123456789ABCDEF0", "0x2710 0xdef0 0x9abc 0x5678 0x1234");
	AssertAsm("add A, 9", "0x2225 0x0009");
	AssertAsm("add A, 8", "0x2fe5");
	AssertAsm("sub W, 8", "0xafe6");
	AssertAsm("xor A, -1", "0x3ff3");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65EncodingMemory(void)
{
	AssertAsm("cpy A, [$1234]", "0x0860 0x1234");
	AssertAsm("cpy A, [$12345678]", "0x0820 0x5678 0x1234");
	AssertAsm("cpy A, [$1234:32]", "0x0820 0x1234 0x0000");
	AssertAsm("cpy [$1234], A", "0x8860 0x1234");
	AssertAsm("cpy A, [$1234 + X]", "0x0e60 0x1234");
	AssertAsm("cpy A, [[$1234]]", "0x0870 0x1234");
	AssertAsm("cpy A, [[$1234 + Y]]", "0x0f80 0x1234");
	AssertAsm("cpy A, [[$1234] + Y]", "0x0f90 0x1234");
	AssertAsm("cpy A, [X]", "0x0ea0");
	AssertAsm("cpy B, [V + W]", "0x27b0");
	AssertAsm("cpy B, [W + V]", "0x27b0");
	AssertAsm("cpy [A + W], B", "0xa4b0");
	AssertAsm("cpy A, [[V]]", "0x0cc0");
	AssertAsm("cpy A, [[S + X]]", "0x1ad0");
	AssertAsm("cpy A, [[B] + Y]", "0x1de0");
	AssertAsm("add [$10:16], 1", "0x40c5 0x0010");
	AssertAsm("cpy A, [$10:16]", "0x0860 0x0010");
	AssertAsm("and [$40], A", "0x8861 0x0040");
	AssertAsm("add A, [$1234 + X]", "0x0cc5 0x1234");
	AssertAsm("add A, [V + X]", "0x1765");
	AssertAsm("cpy [$20], 0", "0x8060 0x0020");
	AssertAsm("cpy [$20], -8", "0xc060 0x0020");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65EncodingFlow(void)
{
	AssertAsm("shl A, 1", "0x23ec");
	AssertAsm("shr A, X", "0x383c");
	AssertAsm("shl A, 20", "0x206c 0x0014");
	AssertAsm("jmp A", "0x080a");
	AssertAsm("jmp $1100", "0x108a 0x1100");
	AssertAsm("jsr $1100", "0x10aa 0x1100");
	AssertAsm("jsr $1100, P", "0x10ea 0x1100");
	AssertAsm("jsr $12345678", "0x20aa 0x5678 0x1234");
	AssertAsm("jmp [$1234]", "0x038a 0x1234");
	AssertAsm("bra C - 2", "0xfd1c");
	AssertAsm("bra C + 200", "0x109a 0x00c8");
	AssertAsm("brsr C + 200", "0x10ba 0x00c8");
	AssertAsm("psh P", "0x00ca");
	AssertAsm("psh C", "0x00aa");
	AssertAsm("psh (C, P), V", "0x40ea");
	AssertAsm("ret", "0x010b");
	AssertAsm("ret P", "0x030b");
	AssertAsm("ret P, W", "0x830b");
	AssertAsm("rti", "0x038b");
	AssertAsm("pul P", "0x020b");
	AssertAsm("brac z, C - 8", "0x660c");
	AssertAsm("brac z, -8", "0x660c");
	AssertAsm("bras c, 8", "0x434c");
	AssertAsm("bras c, 100", "0x405c 0x0064");
	AssertAsm("bra -2", "0xfd1c");
	AssertAsm("bra 200", "0x109a 0x00c8");
	AssertAsm("brsr -100", "0x08ba 0x009c");
	AssertAsm("brsr -100 + C", "0x08ba 0x009c");
	AssertAsm("bras c, C + 8", "0x434c");
	AssertAsm("brasa (z, c), C + 2", "0x608c");
	AssertAsm("braso (n, v), C + 1000", "0x9adc 0x03e8");
	AssertAsm("psh C, V", "0x40aa");
	AssertAsm("nop", "0x015c");
	AssertAsm("nop 3", "0x055c");
	AssertAsm("brk 5", "0x016b");
	AssertAsm("stp", "0x003b");
	AssertAsm("stp (l, e0)", "0x033b");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65EncodingState(void)
{
	AssertAsm("sep (c, n)", "0x091b");
	AssertAsm("cep l", "0x405b");
	AssertAsm("wth A, 4", "0x0b9b");
	AssertAsm("wth B, X", "0x469b");
	AssertAsm("wtth (X, Y), 4", "0xbbdb");
	AssertAsm("gwth Y, (A, -1)", "0x3cbb");
	AssertAsm("gwth Y, A", "0x1cbb");
	AssertAsm("wthx A, 4:s", "0x0bfb");
	AssertAsm("mul", "0x000e");
	AssertAsm("div", "0x004e");
	AssertAsm("neg A, B", "0x228e");
	AssertAsm("abs X", "0xc6ce");
	AssertAsm("fsbi A, X", "0x391e");
	AssertAsm("fcby B, Y, -1", "0x5ede");
	AssertAsm("psh (A, B), S", "0x60cd");
	AssertAsm("psh A", "0x604d");
	AssertAsm("pul (A, V, W), S", "0x666d");
	AssertAsm("psh $1234", "0x685d 0x1234");
	AssertAsm("psh [$40 + X], V", "0x999d 0x0040");
	AssertAsm("pul [$40], W", "0xa1bd 0x0040");
	AssertAsm("scp (A, 2), (B, X), 4", "0x2ac9 0xa060");
	AssertAsm("scb (A, 40), (B, 3), 33", "0x2a19 0xd087");
	AssertAsm("bist f, (A, 3)", "0xc5cf");
	AssertAsm("bist c, (A, 40)", "0x474f 0xa000");
	AssertAsm("bist c, (A, X)", "0x47cf 0xc000");
	AssertAsm("stab (A, Y, X, -1), n", "0x87df 0xe2c0");
	AssertAsm("stab (A, 0), f", "0xc45f");
	AssertAsm("stab (A, 2, 10), 1", "0x275f 0x0928");
	AssertAsm("stat f, c", "0xc87f");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65EncodingBlockVector(void)
{
	AssertAsm("bcpy B, V, +1, A", "0x0408");
	AssertAsm("bpand B, V, +1, A, !n", "0x75a8");
	AssertAsm("band X, V, -1, A, z", "0xcc48");
	AssertAsm("vcpy W, V, +1, A, 64", "0x0618");
	AssertAsm("vcpy W, V, -1, A, 8", "0x8818");
	AssertAsm("vsub W, V, -1, +1, A, 16, n", "0x6b18");
	AssertAsm("vsub W, V, -1, A, 16, n", "0xeb18");
}


//////////////////////////////////////////////////////////////////////////
//
// Every opcode the assembler writes decodes to the instruction it was written as.
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65EncodingDecode(void)
{
	static const char*	aszLines[] = { "cpy A, [[$1234] + Y]", "add A, [V + X]", "shl [$10 + X], 3", "shr [V + Y], B", "jsr [V + X]", "brsr X", "vpxor W, V, +1, A, 32", "bpcpy Y, V, -1, A, !z", "fccr A, X", "scb (X, Y), (A, 63), B" };
	static const E65Instruction	aeInstructions[] = { I65_Cpy, I65_Add, I65_Shl, I65_Shr, I65_Jsr, I65_Brsr, I65_Vpxor, I65_Bpcpy, I65_Fccr, I65_Scb };
	size				i;
	CAsm65Assembler		cAssembler;
	CChars				szSource;
	S65C64Decoded		sDecoded;

	for (i = 0; i < sizeof(aszLines) / sizeof(char*); i++)
	{
		szSource.Init(".org $1000\n");
		szSource.Append(aszLines[i]);
		TestAsm65Assemble(&cAssembler, szSource.Text());
		Decode65C64(cAssembler.GetOutput()->GetWord(0x1000), &sDecoded);
		AssertInt(aeInstructions[i], sDecoded.eInstruction);
		cAssembler.Kill();
		szSource.Kill();
	}

	TestAsm65Assemble(&cAssembler, ".org $1000\nshl [$10 + X], 7");
	Decode65C64(cAssembler.GetOutput()->GetWord(0x1000), &sDecoded);
	AssertInt(OK65_Memory, sDecoded.sFirst.eKind);
	AssertInt(R65_X, sDecoded.ePre1);
	AssertInt(OPERAND_MODE_OFFSET, sDecoded.uiMode);
	AssertLong(7, sDecoded.sSecond.iEmbedded);
	cAssembler.Kill();

	TestAsm65Assemble(&cAssembler, ".org $1000\nadd [[S] + Y], X:s");
	Decode65C64(cAssembler.GetOutput()->GetWord(0x1000), &sDecoded);
	AssertInt(I65_Add, sDecoded.eInstruction);
	AssertTrue(sDecoded.bSigned);
	AssertInt(OK65_Memory, sDecoded.sFirst.eKind);
	AssertInt(R65_X, sDecoded.sSecond.eRegister);
	AssertInt(R65_S, sDecoded.ePre1);
	AssertInt(R65_Y, sDecoded.ePost);
	AssertInt(OPERAND_MODE_REGISTER_INDIRECT_REGISTER, sDecoded.uiMode);
	cAssembler.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65Encoding(void)
{
	BeginTests();

	TestAsm65EncodingArithmeticLogic();
	TestAsm65EncodingMemory();
	TestAsm65EncodingFlow();
	TestAsm65EncodingState();
	TestAsm65EncodingBlockVector();
	TestAsm65EncodingDecode();

	TestStatistics();
}
