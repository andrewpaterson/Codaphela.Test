#include <string.h>
#include "BaseLib/Chars.h"
#include "MicroprocessorLib/W65C816InstructionFactory.h"
#include "MicroprocessorLib/W65Instruction.h"
#include "MicroprocessorLib/W65InstructionCycles.h"
#include "MicroprocessorLib/Fast65C816.h"
#include "Assembler65Lib/Asm816Assembler.h"
#include "Assembler65Lib/Asm65Linker.h"
#include "Assembler65Lib/Asm816Lockstep.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
// The W65C816 assembler (Assembler816Syntax.txt).
//
//////////////////////////////////////////////////////////////////////////


#define TEST_ASM816_RUN_MEMORY	0x30000


//////////////////////////////////////////////////////////////////////////
//
// Whether the simulator's addressing mode is the assembler's.
//
//////////////////////////////////////////////////////////////////////////
static bool TestAsm816SameMode(uint8 uiMode, EAddressingMode eMode)
{
	switch (uiMode)
	{
	case A816M_Implied:				return (eMode == AM_Implied) || (eMode == AM_StackImplied) || (eMode == AM_WaitForInterrupt) || (eMode == AM_StopTheClock);
	case A816M_Accumulator:			return eMode == AM_Accumulator;
	case A816M_ImmediateM:
	case A816M_ImmediateX:			return eMode == AM_Immediate;
	case A816M_Immediate8:			return (eMode == AM_Immediate) || (eMode == AM_StackInterruptSoftware) || (eMode == AM_Implied);
	case A816M_Immediate16:			return eMode == AM_StackImmediate;
	case A816M_Absolute:
	case A816M_JumpAbsolute:		return eMode == AM_Absolute;
	case A816M_AbsoluteX:			return eMode == AM_AbsoluteIndexedWithX;
	case A816M_AbsoluteY:			return eMode == AM_AbsoluteIndexedWithY;
	case A816M_Long:
	case A816M_JumpLong:			return eMode == AM_AbsoluteLong;
	case A816M_LongX:				return eMode == AM_AbsoluteLongIndexedWithX;
	case A816M_Direct:				return (eMode == AM_Direct) || (eMode == AM_StackDirectIndirect);
	case A816M_DirectX:				return eMode == AM_DirectIndexedWithX;
	case A816M_DirectY:				return eMode == AM_DirectIndexedWithY;
	case A816M_DirectIndirect:		return eMode == AM_DirectIndirect;
	case A816M_DirectIndirectX:		return eMode == AM_DirectIndexedIndirectWithX;
	case A816M_DirectIndirectY:		return eMode == AM_DirectIndirectIndexedWithY;
	case A816M_DirectIndirectLong:	return eMode == AM_DirectIndirectLong;
	case A816M_DirectIndirectLongY:	return eMode == AM_DirectIndirectLongIndexedWithY;
	case A816M_Stack:				return eMode == AM_StackRelative;
	case A816M_StackIndirectY:		return eMode == AM_StackRelativeIndirectIndexedWithY;
	case A816M_Relative:			return eMode == AM_Relative;
	case A816M_RelativeLong:		return eMode == AM_RelativeLong;
	case A816M_JumpIndirect:		return eMode == AM_AbsoluteIndirect;
	case A816M_JumpIndirectX:		return eMode == AM_AbsoluteIndexedIndirectWithX;
	case A816M_JumpIndirectLong:	return eMode == AM_AbsoluteIndirectLong;
	case A816M_BlockMove:			return eMode == AM_BlockMove;
	default:						return false;
	}
}


//////////////////////////////////////////////////////////////////////////
//
// Every opcode's mnemonic and mode against MicroprocessorLib's W65C816S.
//
//////////////////////////////////////////////////////////////////////////
void TestAsm816Opcodes(void)
{
	CW65C816InstructionFactory*	pcFactory;
	CW65Instruction*			pcInstruction;
	const char*					szMnemonic;
	uint8						uiMode;
	int							i;
	CChars						szDifferences;
	bool						bSame;

	pcFactory = CW65C816InstructionFactory::GetInstance();
	szDifferences.Init();
	for (i = 0; i < 256; i++)
	{
		szMnemonic = Asm816Mnemonic((uint8)i, &uiMode);
		pcInstruction = pcFactory->GetInstruction((uint16)i);
		//The simulator calls jml JMP and puts per with the stack instructions.
		bSame = (MemICmp(szMnemonic, pcInstruction->GetName(), 4) == 0) || ((strcmp(szMnemonic, "jml") == 0) && (strcmp(pcInstruction->GetName(), "JMP") == 0));
		bSame &= TestAsm816SameMode(uiMode, pcInstruction->GetCycles()->GetAddressingMode()) ||
				 ((strcmp(szMnemonic, "per") == 0) && (pcInstruction->GetCycles()->GetAddressingMode() == AM_StackImplied));
		if (!bSame)
		{
			szDifferences.Append(i);
			szDifferences.Append(' ');
			szDifferences.Append(szMnemonic);
			szDifferences.Append(' ');
			szDifferences.Append(pcInstruction->GetName());
			szDifferences.Append(' ');
			szDifferences.Append((int)pcInstruction->GetCycles()->GetAddressingMode());
			szDifferences.AppendNewLine();
		}
	}
	AssertString("", szDifferences.Text());
	szDifferences.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// "bytes" assembled at $1000 from szSource, or the errors.
//
//////////////////////////////////////////////////////////////////////////
static void TestAsm816Bytes(CChars* psz, const char* szSource)
{
	CAsm816Assembler	cAssembler;
	CChars				szFull;
	size				uiBytes;
	size				i;
	uint8				uiByte;

	szFull.Init(".org $1000\n");
	szFull.Append(szSource);
	szFull.AppendNewLine();
	cAssembler.Init();
	if (!cAssembler.Assemble(szFull.Text()))
	{
		psz->Append("ERRORS ");
		psz->Append(cAssembler.GetErrors());
	}
	else
	{
		uiBytes = cAssembler.GetOutput()->NumBytes();
		for (i = 0; i < uiBytes; i++)
		{
			cAssembler.GetOutput()->Get((uint32)(0x1000 + i), &uiByte);
			if (i != 0)
			{
				psz->Append(' ');
			}
			psz->AppendHexHiLo(&uiByte, 1);
		}
	}
	cAssembler.Kill();
	szFull.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
static void AssertAsm816(const char* szExpected, const char* szSource)
{
	CChars	sz;

	sz.Init();
	TestAsm816Bytes(&sz, szSource);
	AssertString(szExpected, sz.Text());
	sz.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// One line with 16 bit widths.
//
//////////////////////////////////////////////////////////////////////////
static void AssertAsm816Line(const char* szExpected, const char* szLine)
{
	CChars	sz;

	sz.Init(".width (A, X), 16\n");
	sz.Append(szLine);
	AssertAsm816(szExpected, sz.Text());
	sz.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// Each addressing mode.
//
//////////////////////////////////////////////////////////////////////////
void TestAsm816Encoding(void)
{
	AssertAsm816Line("ea", "nop");
	AssertAsm816Line("0a", "asl A");
	AssertAsm816Line("1a", "inc A");
	AssertAsm816Line("a9 05 00", "lda 5");
	AssertAsm816Line("a9 34 12", "lda $1234");
	AssertAsm816Line("a9 05 00", "lda 5:16");
	AssertAsm816Line("a2 02 00", "ldx 2");
	AssertAsm816Line("89 05 00", "bit 5");
	AssertAsm816Line("ad 34 12", "lda [$1234]");
	AssertAsm816Line("bd 34 12", "lda [$1234 + X]");
	AssertAsm816Line("b9 34 12", "lda [$1234 + Y]");
	AssertAsm816Line("af 56 34 12", "lda [$123456]");
	AssertAsm816Line("af 34 12 00", "lda [$1234]:24");
	AssertAsm816Line("bf 56 34 12", "lda [$123456 + X]");
	AssertAsm816Line("a5 04", "lda [D + 4]");
	AssertAsm816Line("a5 00", "lda [D]");
	AssertAsm816Line("b5 04", "lda [D + 4 + X]");
	AssertAsm816Line("b6 04", "ldx [D + 4 + Y]");
	AssertAsm816Line("b2 04", "lda [[D + 4]]");
	AssertAsm816Line("a1 04", "lda [[D + 4 + X]]");
	AssertAsm816Line("b1 04", "lda [[D + 4] + Y]");
	AssertAsm816Line("a7 04", "lda [[D + 4]:24]");
	AssertAsm816Line("b7 04", "lda [[D + 4]:24 + Y]");
	AssertAsm816Line("a3 03", "lda [S + 3]");
	AssertAsm816Line("b3 03", "lda [[S + 3] + Y]");
	AssertAsm816Line("8d 34 12", "sta [$1234]");
	AssertAsm816Line("64 02", "stz [D + 2]");
	AssertAsm816Line("fe 34 12", "inc [$1234 + X]");
	AssertAsm816Line("1c 34 12", "trb [$1234]");
	AssertAsm816Line("e4 01", "cpx [D + 1]");
	AssertAsm816Line("bc 34 12", "ldy [$1234 + X]");
	AssertAsm816Line("96 01", "stx [D + 1 + Y]");
	AssertAsm816Line("c2 30", "rep (m, x)");
	AssertAsm816Line("c2 30", "rep $30");
	AssertAsm816Line("e2 20", "sep m");
	AssertAsm816Line("f4 34 12", "pea $1234");
	AssertAsm816Line("d4 06", "pei [D + 6]");
	AssertAsm816Line("4c 34 12", "jmp $1234");
	AssertAsm816Line("6c 34 12", "jmp [$1234]");
	AssertAsm816Line("7c 34 12", "jmp [$1234 + X]");
	AssertAsm816Line("5c 56 34 12", "jml $123456");
	AssertAsm816Line("dc 34 12", "jml [$1234]:24");
	AssertAsm816Line("20 34 12", "jsr $1234");
	AssertAsm816Line("fc 34 12", "jsr [$1234 + X]");
	AssertAsm816Line("22 56 34 12", "jsl $123456");
	AssertAsm816Line("80 fe", "bra C - 2");
	AssertAsm816Line("d0 04", "bne C + 4");
	AssertAsm816Line("80 05", "bra 5");
	AssertAsm816Line("82 00 01", "brl C + $100");
	AssertAsm816Line("62 02 00", "per C + 2");
	AssertAsm816Line("54 34 12", "mvn $12, $34");
	AssertAsm816Line("44 34 12", "mvp $12, $34");
	AssertAsm816Line("00 00", "brk 0");
	AssertAsm816Line("02 05", "cop 5");
	AssertAsm816Line("42 01", "wdm 1");
	AssertAsm816Line("eb", "xba");
	AssertAsm816Line("5b", "tcd");
	AssertAsm816Line("6b", "rtl");
	AssertAsm816Line("6b", "RTL");

	//8 bit widths.
	AssertAsm816("a9 05", ".width (A, X), 8\nlda 5");
	AssertAsm816("a0 ff", ".width X, 8\nldy 255");
	AssertAsm816("a9 ff", ".width A, 8\nlda -1");
	AssertAsm816("a9 01", "lda 1:8");

	//rep and sep change the widths.
	AssertAsm816("e2 20 a9 01 c2 20 a9 01 00", "sep m\nlda 1\nrep m\nlda 1");
	AssertAsm816("e2 30 a2 01 c2 10 a2 01 00 a9 01", "sep (m, x)\nldx 1\nrep x\nldx 1\nlda 1");

	//Labels, branches and an address that only turns out to be long in a later pass.
	AssertAsm816("ea d0 fd", "Loop:\nnop\nbne Loop");
	AssertAsm816("80 01 ea ea", "bra Forward\nnop\nForward:\nnop");
	AssertAsm816("af 56 34 12", "lda [Far]\nFar = $123456");
	AssertAsm816("82 fd ff", "Here:\nbrl Here");
	AssertAsm816("a9 00 10", ".width A, 16\nThere:\nlda There & $FFFF");
	AssertAsm816("a9 12", ".width A, 8\nlda Bank >> 16\nBank = $123456");

	//Data.
	AssertAsm816("56 34 12 78 56 34 12", ".word24 $123456\n.long $12345678");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
static void AssertAsm816Error(const char* szExpected, const char* szSource)
{
	CChars	sz;

	sz.Init();
	TestAsm816Bytes(&sz, szSource);
	if (strstr(sz.Text(), szExpected) == NULL)
	{
		AssertString(szExpected, sz.Text());
	}
	else
	{
		AssertTrue(true);
	}
	sz.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestAsm816Errors(void)
{
	CAsm816Assembler	cAssembler;
	CAsm65Object		cObject;

	AssertAsm816Error("The width of A is not known here", "lda 1");
	AssertAsm816Error("The width of X is not known here", "ldy 1");
	AssertAsm816Error("The width of A is not known here", "rep m\nxce\nlda 1");
	AssertAsm816Error("The width of A is not known here", "rep m\nplp\nlda 1");
	AssertAsm816Error("The suffix is not the width of A (16 bits)", "rep m\nlda 1:8");
	AssertAsm816Error("A direct page or stack offset is 0 to 255", "lda [D + 256]");
	AssertAsm816Error("the instruction has no long mode", "inc [$123456]");
	AssertAsm816Error("The instruction has no long mode", "ldx [$1234]:24");
	AssertAsm816Error("Target is out of range", "bra C + 200");
	AssertAsm816Error("Target is in another bank: use jml or jsl", "jmp $23456");
	AssertAsm816Error("A pointer is read from the direct page or the stack", "lda [[$1234]]");
	AssertAsm816Error("The instruction has no such addressing mode", "stx [$1234 + X]");
	AssertAsm816Error("Expected memory in square brackets", "sta 5");
	AssertAsm816Error("Unknown instruction", "lax 5");
	AssertAsm816Error("Reserved name cannot be a label", "D:\nnop");
	AssertAsm816Error("A width is 8 or 16 bits", ".width A, 32");

	cObject.Init("errors");
	cAssembler.Init();
	AssertFalse(cAssembler.AssembleObject(".section data.Values\nL:\n.byte (L >> 16) + 1\n", &cObject));
	AssertString("3:17: Nothing can be added to an address's bank or low 16 bits; add to the address first '+'\n", cAssembler.GetErrors());
	cAssembler.Kill();
	cObject.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// Relocations of each form, linked into the same bank and into another bank.
//
//////////////////////////////////////////////////////////////////////////
static const char* gszTestAsm816Code =
	".section text.Code\n"
	".global Start\n"
	"Start:\n"
	"\t.width (A, X), 16\n"
	"\tlda [Value]:24\n"
	"\tlda [Value]\n"
	"\tlda Value & $FFFF\n"
	"\tldx Value >> 16\n"
	"\tjsl Far\n"
	"\tjsr Near\n"
	"\tbra Near\n"
	"\tmvn Value >> 16, Value >> 16\n"
	"Near:\n"
	"\trtl\n"
	".section data.Values\n"
	"Value:\n"
	"\t.word 7\n"
	"\t.long Value\n"
	"\t.word24 Value\n"
	"\t.byte Value >> 16\n";

static const char* gszTestAsm816Far =
	".section text.Far\n"
	".global Far\n"
	"Far:\n"
	"\trtl\n";


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
static bool TestAsm816Link(CAsm65Linker* pcLinker, CAsm65Object* pcCode, CAsm65Object* pcFar, uint32 uiData)
{
	CAsm816Assembler	cAssembler;

	pcCode->Init("code");
	pcFar->Init("far");
	cAssembler.Init();
	AssertTrue(cAssembler.AssembleObject(gszTestAsm816Code, pcCode));
	AssertString("", cAssembler.GetErrors());
	cAssembler.Kill();
	cAssembler.Init();
	AssertTrue(cAssembler.AssembleObject(gszTestAsm816Far, pcFar));
	cAssembler.Kill();

	pcLinker->Init();
	pcLinker->AddObject(pcCode);
	pcLinker->AddObject(pcFar);
	pcLinker->SetAddress(ASK65_Text, 0x012000);
	pcLinker->SetAddress(ASK65_Data, uiData);
	return pcLinker->Link();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
static uint32 TestAsm816Get(CAsm65Output* pcOutput, uint32 uiAddress, int iBytes)
{
	uint32	uiValue;
	uint8	uiByte;
	int		i;

	uiValue = 0;
	for (i = 0; i < iBytes; i++)
	{
		uiByte = 0;
		pcOutput->Get(uiAddress + i, &uiByte);
		uiValue |= (uint32)uiByte << (8 * i);
	}
	return uiValue;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestAsm816Object(void)
{
	CAsm65Object	cCode;
	CAsm65Object	cFar;
	CAsm65Linker	cLinker;
	CAsm65Output*	pcOutput;
	CChars			szDump;
	int64			iStart;
	int64			iValue;
	int64			iFar;
	int64			iNear;
	uint32			v;

	AssertTrue(TestAsm816Link(&cLinker, &cCode, &cFar, 0x012800));
	AssertString("", cLinker.GetErrors());

	szDump.Init();
	cCode.Dump(&szDump);
	AssertTrue(strstr(szDump.Text(), "1 + 1 absolute 3 bytes = section 2 + 0\n") != NULL);
	AssertTrue(strstr(szDump.Text(), "1 + 5 absolute 2 bytes = section 2 + 0 in bank\n") != NULL);
	AssertTrue(strstr(szDump.Text(), "1 + 8 absolute 2 bytes = section 2 + 0 & $FFFF\n") != NULL);
	AssertTrue(strstr(szDump.Text(), "1 + 11 absolute 2 bytes = section 2 + 0 >> 16\n") != NULL);
	AssertTrue(strstr(szDump.Text(), "1 + 23 absolute 1 bytes = section 2 + 0 >> 16\n") != NULL);
	AssertTrue(strstr(szDump.Text(), "1 + 18 absolute 2 bytes = section 1 + 25 in bank\n") != NULL);
	AssertTrue(strstr(szDump.Text(), "2 + 9 absolute 1 bytes = section 2 + 0 >> 16\n") != NULL);
	szDump.Kill();

	AssertTrue(cLinker.GetSymbol("Start", &iStart));
	AssertTrue(cLinker.GetSymbol("Far", &iFar));
	iNear = iStart + 25;
	pcOutput = cLinker.GetOutput();
	iValue = 0x012800;
	v = (uint32)iValue;
	AssertInt(0x012000, (int)iStart);
	AssertInt(v, TestAsm816Get(pcOutput, (uint32)iStart + 1, 3));
	AssertInt(v & 0xFFFF, TestAsm816Get(pcOutput, (uint32)iStart + 5, 2));
	AssertInt(v & 0xFFFF, TestAsm816Get(pcOutput, (uint32)iStart + 8, 2));
	AssertInt(v >> 16, TestAsm816Get(pcOutput, (uint32)iStart + 11, 2));
	AssertInt((int)iFar, TestAsm816Get(pcOutput, (uint32)iStart + 14, 3));
	AssertInt((int)(iNear & 0xFFFF), TestAsm816Get(pcOutput, (uint32)iStart + 18, 2));
	AssertInt((int)(iNear - (iStart + 22)), TestAsm816Get(pcOutput, (uint32)iStart + 21, 1));
	AssertInt(0x0101, TestAsm816Get(pcOutput, (uint32)iStart + 23, 2));
	AssertInt(0x6B, TestAsm816Get(pcOutput, (uint32)iNear, 1));
	AssertInt(7, TestAsm816Get(pcOutput, v, 2));
	AssertInt(v, TestAsm816Get(pcOutput, v + 2, 4));
	AssertInt(v, TestAsm816Get(pcOutput, v + 6, 3));
	AssertInt(1, TestAsm816Get(pcOutput, v + 9, 1));
	cLinker.Kill();
	cFar.Kill();
	cCode.Kill();

	//lda [Value] is absolute: Value must be in the bank of the code.
	AssertFalse(TestAsm816Link(&cLinker, &cCode, &cFar, 0x030000));
	AssertTrue(strstr(cLinker.GetErrors(), "Address is not in the bank of the instruction using it") != NULL);
	cLinker.Kill();
	cFar.Kill();
	cCode.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
static uint8 TestAsm816Read(void* pvMemory, uint32 uiAddress)
{
	return 0xFF;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
static void TestAsm816Write(void* pvMemory, uint32 uiAddress, uint8 uiValue)
{
}


//////////////////////////////////////////////////////////////////////////
//
// A program in three banks run on CFast65C816: a 16 bit loop with the direct page,
// jsl to another bank, a 24 bit pointer and a block move.
//
//////////////////////////////////////////////////////////////////////////
void TestAsm816Run(void)
{
	CAsm816Assembler	cAssembler;
	CFast65C816			cFast;
	uint8*				puiMemory;
	SAsm65Segment*		psSegment;
	size				i;
	size				uiSteps;

	cAssembler.Init();
	AssertTrue(cAssembler.Assemble(
		".org $8000\n"
		"Start:\n"
		"\tclc\n"
		"\txce\n"
		"\trep (m, x)\n"
		"\tlda 0\n"
		"\tldx 100\n"
		"Sum:\n"
		"\tstx [D + $10]\n"
		"\tclc\n"
		"\tadc [D + $10]\n"
		"\tdex\n"
		"\tbne Sum\n"
		"\tsta [$2000]\n"
		"\tjsl Double\n"
		"\tsta [$2002]\n"
		"\tlda $1000\n"
		"\tsta [D + $20]\n"
		"\tlda $0002\n"
		"\tsta [D + $22]\n"
		"\tldy 2\n"
		"\tlda [[D + $20]:24 + Y]\n"
		"\tsta [$2004]\n"
		"\tlda 15\n"
		"\tldx $1000\n"
		"\tldy $2000\n"
		"\tmvn $02, $02\n"
		"\tstp\n"
		".org $018000\n"
		"Double:\n"
		"\tasl A\n"
		"\trtl\n"
		".org $021000\n"
		"\t.word $1111, $2222, $3333, $4444, $5555, $6666, $7777, $8888\n"
		".org $FFFC\n"
		"\t.word Start\n"));
	AssertString("", cAssembler.GetErrors());

	puiMemory = (uint8*)malloc(TEST_ASM816_RUN_MEMORY);
	memset(puiMemory, 0, TEST_ASM816_RUN_MEMORY);
	for (i = 0; i < cAssembler.GetOutput()->NumSegments(); i++)
	{
		psSegment = cAssembler.GetOutput()->GetSegment(i);
		memcpy(&puiMemory[psSegment->uiAddress], psSegment->cBytes.GetData(), psSegment->cBytes.NumElements());
	}
	cAssembler.Kill();

	cFast.Init(TestAsm816Read, TestAsm816Write, NULL, puiMemory, TEST_ASM816_RUN_MEMORY);
	cFast.Reset();
	uiSteps = cFast.Run(10000);
	AssertTrue(cFast.IsStopped());
	AssertTrue(uiSteps < 10000);
	AssertInt(5050, puiMemory[0x2000] | (puiMemory[0x2001] << 8));
	AssertInt(10100, puiMemory[0x2002] | (puiMemory[0x2003] << 8));
	AssertInt(0x2222, puiMemory[0x2004] | (puiMemory[0x2005] << 8));
	AssertInt(0, memcmp(&puiMemory[0x021000], &puiMemory[0x022000], 16));
	AssertInt(0x8888, puiMemory[0x02200E] | (puiMemory[0x02200F] << 8));
	cFast.Kill();
	free(puiMemory);
}


//The vectors and the reset stub in bank 0 (placed with at), the program in bank 1 and two
//big sections the linker keeps inside banks.
static const char* gszTestAsm816Banks =
	".section rodata.Vectors, at $FFFC\n"
	"\t.word ResetStub\n"
	".section text.ResetStub, at $FF00\n"
	"ResetStub:\n"
	"\tjml Start\n"
	".section text.Start\n"
	".global Start\n"
	"Start:\n"
	"\tclc\n"
	"\txce\n"
	"\trep (m, x)\n"
	"\tlda $1234\n"
	"\tsta [Result]:24\n"
	"\tjsl InBig\n"
	"\tsep m\n"
	"\tlda 'O'\n"
	"\tsta [$FF0100]:24\n"
	"\tlda 'K'\n"
	"\tsta [$FF0100]:24\n"
	"\tstp\n"
	".section text.Fixed, at $010100\n"
	"Fixed:\n"
	"\t.space 4\n"
	".section text.Big\n"
	"\t.space $8000\n"
	".section text.Bigger\n"
	".global InBig\n"
	"InBig:\n"
	"\t.width A, 16\n"
	"\tlda $5678\n"
	"\tsta [Result + 2]:24\n"
	"\trtl\n"
	"\t.space $8FF0\n"
	".section bss.Result\n"
	".global Result\n"
	"Result:\n"
	"\t.space 4\n";


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
static bool TestAsm816LinkBanks(CAsm65Linker* pcLinker, CAsm65Object* pcObject, const char* szSource, uint32 uiText)
{
	CAsm816Assembler	cAssembler;

	pcObject->Init("banks");
	cAssembler.Init();
	AssertTrue(cAssembler.AssembleObject(szSource, pcObject));
	AssertString("", cAssembler.GetErrors());
	cAssembler.Kill();

	pcLinker->Init();
	pcLinker->SetBankSize(0x10000);
	pcLinker->AddObject(pcObject);
	pcLinker->SetAddress(ASK65_Text, uiText);
	return pcLinker->Link();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestAsm816Banks(void)
{
	CAsm65Object		cObject;
	CAsm65Linker		cLinker;
	CFast65C816			cFast;
	uint8*				puiMemory;
	SAsm65Segment*		psSegment;
	int64				iStart;
	int64				iInBig;
	int64				iResult;
	size				i;
	CAsm65Memory		cMemory;
	CAsm816Lockstep		cLockstep;
	CChars				szConsole;

	AssertTrue(TestAsm816LinkBanks(&cLinker, &cObject, gszTestAsm816Banks, 0x010000));
	AssertString("", cLinker.GetErrors());
	AssertTrue(cLinker.GetSymbol("Start", &iStart));
	AssertTrue(cLinker.GetSymbol("InBig", &iInBig));
	AssertTrue(cLinker.GetSymbol("Result", &iResult));
	AssertInt(0x010000, (int)iStart);

	//text.Big ($8000 bytes) can't start before Fixed's end, text.Bigger ($9000) can't fit in bank 1.
	AssertTrue(strstr(cLinker.GetMap(), "text.Fixed") != NULL);
	AssertInt(0x020000, (int)iInBig);

	//On CFast65C816 and the CW65C816 simulator in lockstep, with CAsm65Memory's console.
	szConsole.Init();
	cMemory.Init(TEST_ASM816_RUN_MEMORY);
	cMemory.SetConsole(&szConsole);
	cMemory.Load(cLinker.GetOutput());
	cMemory.InitFast816(&cFast);
	cFast.Reset();
	cLockstep.Init(&cMemory, &cFast);
	cLockstep.Run(1000, 1);
	AssertString("", cLockstep.GetDifferences());
	AssertTrue(cLockstep.IsStopped());
	AssertString("OK", szConsole.Text());
	AssertInt(0x5678, cMemory.GetWord((uint32)iResult + 2));
	AssertInt(0, (int)cMemory.NumBadAccesses());
	cLockstep.Kill();
	cFast.Kill();
	cMemory.Kill();
	szConsole.Kill();

	puiMemory = (uint8*)malloc(TEST_ASM816_RUN_MEMORY);
	memset(puiMemory, 0, TEST_ASM816_RUN_MEMORY);
	for (i = 0; i < cLinker.GetOutput()->NumSegments(); i++)
	{
		psSegment = cLinker.GetOutput()->GetSegment(i);
		memcpy(&puiMemory[psSegment->uiAddress], psSegment->cBytes.GetData(), psSegment->cBytes.NumElements());
	}
	cLinker.Kill();
	cObject.Kill();

	cFast.Init(TestAsm816Read, TestAsm816Write, NULL, puiMemory, TEST_ASM816_RUN_MEMORY);
	cFast.Reset();
	cFast.Run(100);
	AssertTrue(cFast.IsStopped());
	AssertInt(0x1234, puiMemory[iResult] | (puiMemory[iResult + 1] << 8));
	AssertInt(0x5678, puiMemory[iResult + 2] | (puiMemory[iResult + 3] << 8));
	cFast.Kill();
	free(puiMemory);

	//Only sections with an address may be in bank 0.
	AssertFalse(TestAsm816LinkBanks(&cLinker, &cObject, gszTestAsm816Banks, 0x8000));
	AssertTrue(strstr(cLinker.GetErrors(), "Only a section with an address (at) can be in bank 0 'text.Start'") != NULL);
	cLinker.Kill();
	cObject.Kill();

	//A table of 4 byte init entries runs on into the next bank without a gap (each entry 4 byte aligned, so none crosses
	//the end of a bank and is moved on), and __init_start is its first entry (after the alignment).
	AssertTrue(TestAsm816LinkBanks(&cLinker, &cObject,
		".section text.Code\n.space $FFF5\nE1:\nE2:\nE3:\nE4:\n"
		".section init.E1\n.align 4\n.long E1\n.section init.E2\n.align 4\n.long E2\n"
		".section init.E3\n.align 4\n.long E3\n.section init.E4\n.align 4\n.long E4\n", 0x010000));
	AssertString("", cLinker.GetErrors());
	AssertTrue(cLinker.GetSymbol("__init_start", &iStart));
	AssertTrue(cLinker.GetSymbol("__init_end", &iResult));
	AssertInt(0, (int)(iStart & 3));
	AssertInt(16, (int)(iResult - iStart));
	AssertTrue((iStart < 0x20000) && (iResult > 0x20000));
	cLinker.Kill();
	cObject.Kill();

	//Sections with addresses can't overlap or cross the end of a bank.
	AssertFalse(TestAsm816LinkBanks(&cLinker, &cObject, ".section text.A, at $10000\n.space 8\n.section text.B, at $10004\n.space 8\n.section text.C, at $1FFFE\n.space 4\n", 0x010000));
	AssertTrue(strstr(cLinker.GetErrors(), "Section overlaps another section with an address 'text.B'") != NULL);
	AssertTrue(strstr(cLinker.GetErrors(), "Section crosses the end of a bank 'text.C'") != NULL);
	cLinker.Kill();
	cObject.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestAsm816(void)
{
	BeginTests();
	CW65C816InstructionFactory::GetInstance()->Init();

	TestAsm816Opcodes();
	TestAsm816Encoding();
	TestAsm816Errors();
	TestAsm816Object();
	TestAsm816Run();
	TestAsm816Banks();

	CW65C816InstructionFactory::GetInstance()->Kill();
	TestStatistics();
}

