#include "TestLib/Assert.h"
#include "TestAsm65C64Context.h"


//////////////////////////////////////////////////////////////////////////
//
// One error per line, reported by the final pass with the line, column and token.
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65ErrorsStatements(void)
{
	CAsm65C64Assembler	cAssembler;

	cAssembler.Init();
	AssertFalse(cAssembler.Assemble(
		"	cpy A, B\n"
		"	foo A, B\n"
		"	cpy A, Missing\n"
		"	add A, [W]\n"
		"Dup:	nop\n"
		"Dup:	nop\n"
		"	brk 2000\n"
		"A:	nop\n"
		"	cpy [$10], 100\n"
		"	wth V, 16\n"
		"	cpy A, B C\n"
		"	add A, [V + W]\n"));
	AssertString(
		"2:2: Unknown instruction 'foo'\n"
		"3:9: Undefined symbol 'Missing'\n"
		"4:10: Register W cannot address memory here 'W'\n"
		"6:1: Symbol is already defined 'Dup'\n"
		"7:6: A break vector is 0 to 1023 '2000'\n"
		"8:1: Reserved name cannot be a label 'A'\n"
		"9:13: A value used with memory must be -8 to 8; use a register '100'\n"
		"10:6: Only A, B, X and Y have a width 'V'\n"
		"11:11: Expected the end of the line 'C'\n"
		"12:10: Those two registers cannot address memory here 'V'\n", cAssembler.GetErrors());
	AssertSize(10, cAssembler.NumErrors());
	cAssembler.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65ErrorsRanges(void)
{
	CAsm65C64Assembler	cAssembler;

	cAssembler.Init();
	AssertFalse(cAssembler.Assemble(
		".org $1000\n"
		"	brac z, $100001000\n"
		"	cpy A, 300:8\n"
		"	shl A, -1\n"
		"	bcpy B, V, +1, A, z\n"
		"	vcpy W, V, +1, A, 12\n"
		"	scp (A, 8), (B, 0), 1\n"
		"	hws 3, A\n"
		"	.byte 256\n"
		"	bra *\n"
		"	psh C + 4\n"
		"	psh 4 + C\n"
		"	psh [C]\n"
		"	cpy A, C\n"
		"	jmp C\n"
		"Count = C\n"
		"	.word C\n"
		"	bra C * 2\n"
		"Lab:	bra C + Lab\n"
		"	bra 2 - C\n"
		"	bra [C]\n"
		"	bras c, ~C\n"
		"	cpy A, 4:s:16\n"
		"	cpy A, 4:16:s\n"
		"	cpy A, 4:s12\n"
		"	cpy A, [4:s16]\n"
		"	sep c, n\n"
		"	stp l, e0\n"
		"	sep (c)\n"
		"	psh (A)\n"
		"	vsub W, V, (-1, +1), A, 16\n"
		"	bcpy B, V, (+1, -1), A\n"
		"	gwth Y, (A, -2)\n"
		"	gwth Y, (A, +1)\n"));
	AssertString(
		"2:10: Target is out of range '$100001000'\n"
		"3:9: Value does not fit '300'\n"
		"4:9: A shift amount cannot be negative '-'\n"
		"5:20: bcpy cannot stop early 'z'\n"
		"6:20: A vector element is 8, 16, 32 or 64 bits '12'\n"
		"7:10: A byte index is 0 to 7 '8'\n"
		"8:2: Hardware register instructions are not supported 'hws'\n"
		"9:8: Value does not fit '256'\n"
		"10:6: Expected a value '*'\n"
		"11:8: C cannot be part of a pushed value; push C then add to it '+'\n"
		"12:10: C is only allowed in branch, bra and brsr targets 'C'\n"
		"13:7: C is only allowed in branch, bra and brsr targets 'C'\n"
		"14:9: C is only allowed in branch, bra and brsr targets 'C'\n"
		"15:6: C is only allowed in branch, bra and brsr targets 'C'\n"
		"16:9: C is only allowed in branch, bra and brsr targets 'C'\n"
		"17:8: C is only allowed in branch, bra and brsr targets 'C'\n"
		"18:8: C can only have an offset added or subtracted '*'\n"
		"19:10: A target using C must be C + offset or C - offset 'C'\n"
		"20:6: A target using C must be C + offset or C - offset '2'\n"
		"21:7: C is only allowed in a target, not an address 'C'\n"
		"22:10: C can only have an offset added or subtracted '~'\n"
		"23:12: Only one suffix is allowed; a signed width is written :s16 ':'\n"
		"24:13: Only one suffix is allowed; a signed width is written :s16 ':'\n"
		"25:11: A width is :8, :16, :24, :32, :40, :48 or :64 's12'\n"
		"26:12: Expected a width or s 's16'\n"
		"27:6: More than one operand must be grouped in brackets 'c'\n"
		"28:6: More than one operand must be grouped in brackets 'l'\n"
		"29:6: Brackets only group more than one operand '('\n"
		"30:6: Brackets only group more than one operand '('\n"
		"31:13: Directions cannot be grouped in brackets '('\n"
		"32:13: Directions cannot be grouped in brackets '('\n"
		"33:14: gwth can only subtract 1 (-1) '-'\n"
		"34:14: gwth can only subtract 1 (-1) '+'\n", cAssembler.GetErrors());
	cAssembler.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65ErrorsCopyExtendBranchEqual(void)
{
	CAsm65C64Assembler	cAssembler;

	cAssembler.Init();
	AssertFalse(cAssembler.Assemble(
		".org $1000\n"
		"	cpyx A, [V + X]:8\n"
		"	cpyx A, [[$10] + Y]:8\n"
		"	cpyx S, [$10]:8\n"
		"	cpyx A, [$10]:24\n"
		"	cpyx A, B\n"
		"	cpyx A, [$10 + W]:8\n"
		"	add A, [$10 + W]\n"
		"	cpyx A, [$10]\n"
		"	cpy A, [$10]:8\n"
		"	cpyx [$10]:s8, A\n"
		"	cpyx A, [$10]:s64\n"
		"	cpyx A:s, [$10]:8\n"
		"	brae (0, z), 4\n"
		"	brane (z, 1), 4\n"));
	AssertString(
		"2:11: cpyx cannot use that addressing mode 'V'\n"
		"3:12: cpyx cannot use that addressing mode '$10'\n"
		"4:7: The register must be A, B, X or Y 'S'\n"
		"5:11: cpyx memory needs a width of :8, :16, :32 or :64 '$10'\n"
		"6:10: cpyx needs a memory operand 'B'\n"
		"7:11: Register W cannot address memory here '$10'\n"
		"8:10: Register W cannot address memory here '$10'\n"
		"9:11: cpyx memory needs a width of :8, :16, :32 or :64 '$10'\n"
		"10:15: A width is not allowed here '8'\n"
		"11:8: A copy into memory cannot sign extend '$10'\n"
		"12:11: 64 bits has nothing to sign extend; use :64 '$10'\n"
		"13:7: cpyx sign extends memory: [address]:s8, :s16 or :s32 'A'\n"
		"14:8: Expected a status flag '0'\n"
		"15:12: Expected a status flag '1'\n", cAssembler.GetErrors());
	AssertSize(14, cAssembler.NumErrors());
	cAssembler.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// Tokeniser errors stop assembly before the first pass.
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65ErrorsTokens(void)
{
	CAsm65C64Assembler	cAssembler;

	cAssembler.Init();
	AssertFalse(cAssembler.Assemble("	cpy A, 0x\n	cpy A, @\n	cpy A, 4:16s\n"));
	AssertString(
		"1:9: Malformed number\n"
		"2:9: Unknown character\n"
		"3:11: Malformed number\n", cAssembler.GetErrors());
	cAssembler.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// Addresses that are too wide lose their high bits with a warning.
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65ErrorsWarnings(void)
{
	CAsm65C64Assembler	cAssembler;

	cAssembler.Init();
	AssertTrue(cAssembler.Assemble(
		".org $1000\n"
		"	cpy [$5e6f7081:16], A\n"
		"	cpy A, [[$1a2b3c4d5e6f7081] + X]\n"
		"	cpy A, [[$1a2b3c4d5e6f7081:16] + X]\n"
		"	cpy A, [$123456789:32]\n"));
	AssertString("", cAssembler.GetErrors());
	AssertString(
		"2:7: Offset address is wider than 16 bits; the high bits are discarded '$5e6f7081'\n"
		"3:11: Address is wider than 32 bits; the high bits are discarded '$1a2b3c4d5e6f7081'\n"
		"4:11: Offset address is wider than 16 bits; the high bits are discarded '$1a2b3c4d5e6f7081'\n"
		"5:10: Address is wider than 32 bits; the high bits are discarded '$123456789'\n", cAssembler.GetWarnings());
	AssertSize(4, cAssembler.NumWarnings());

	AssertShortHex((uint16)0x8860, TestAsm65Word(&cAssembler, 0x1000));
	AssertShortHex((uint16)0x7081, TestAsm65Word(&cAssembler, 0x1002));
	AssertShortHex((uint16)0x0E50, TestAsm65Word(&cAssembler, 0x1004));
	AssertShortHex((uint16)0x7081, TestAsm65Word(&cAssembler, 0x1006));
	AssertShortHex((uint16)0x5E6F, TestAsm65Word(&cAssembler, 0x1008));
	AssertShortHex((uint16)0x0E90, TestAsm65Word(&cAssembler, 0x100A));
	AssertShortHex((uint16)0x7081, TestAsm65Word(&cAssembler, 0x100C));
	AssertShortHex((uint16)0x0820, TestAsm65Word(&cAssembler, 0x100E));
	AssertShortHex((uint16)0x6789, TestAsm65Word(&cAssembler, 0x1010));
	AssertShortHex((uint16)0x2345, TestAsm65Word(&cAssembler, 0x1012));
	cAssembler.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65C64Errors(void)
{
	BeginTests();

	TestAsm65ErrorsStatements();
	TestAsm65ErrorsRanges();
	TestAsm65ErrorsCopyExtendBranchEqual();
	TestAsm65ErrorsTokens();
	TestAsm65ErrorsWarnings();

	TestStatistics();
}
