#include "TestLib/Assert.h"
#include "TestAsm65Context.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
static int64 Symbol(CAsm65Assembler* pcAssembler, const char* szName)
{
	int64	iValue;

	iValue = -1;
	AssertTrue(pcAssembler->GetSymbol(szName, &iValue));
	return iValue;
}


//////////////////////////////////////////////////////////////////////////
//
// Forward references start small and grow: a branch to Far needs an immediate, Value
// needs 24 bits and Data is above 0000:FFFF so it is absolute.
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65LabelsForward(void)
{
	CAsm65Assembler	cAssembler;

	TestAsm65Assemble(&cAssembler,
		".org $1000\n"
		"Start:\n"
		"	brac z, Near\n"
		"	nop\n"
		"	nop\n"
		"Near:\n"
		"	brac z, Far\n"
		"	.quad 0, 0, 0, 0, 0, 0, 0, 0\n"
		"Far:\n"
		"	cpy A, Value\n"
		"	cpy B, [Data]\n"
		"	jmp Start\n"
		"Value = $12345\n"
		"Data = $20000 + 4\n");

	AssertLongLongIntHex(0x1006, Symbol(&cAssembler, "Near"));
	AssertLongLongIntHex(0x104A, Symbol(&cAssembler, "Far"));
	AssertLongLongIntHex(0x12345, Symbol(&cAssembler, "Value"));
	AssertShortHex((uint16)0x610C, TestAsm65Word(&cAssembler, 0x1000));
	AssertShortHex((uint16)0x601C, TestAsm65Word(&cAssembler, 0x1006));
	AssertShortHex((uint16)0x0040, TestAsm65Word(&cAssembler, 0x1008));
	AssertShortHex((uint16)0x2310, TestAsm65Word(&cAssembler, 0x104A));
	AssertShortHex((uint16)0x2345, TestAsm65Word(&cAssembler, 0x104C));
	AssertShortHex((uint16)0x0001, TestAsm65Word(&cAssembler, 0x104E));
	AssertShortHex((uint16)0x1020, TestAsm65Word(&cAssembler, 0x1050));
	AssertShortHex((uint16)0x0004, TestAsm65Word(&cAssembler, 0x1052));
	AssertShortHex((uint16)0x0002, TestAsm65Word(&cAssembler, 0x1054));
	AssertShortHex((uint16)0x108A, TestAsm65Word(&cAssembler, 0x1056));
	AssertShortHex((uint16)0x1000, TestAsm65Word(&cAssembler, 0x1058));
	AssertSize(0x5A, cAssembler.GetOutput()->NumBytes());
	AssertTrue(cAssembler.NumPasses() <= 5);
	cAssembler.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65LabelsData(void)
{
	CAsm65Assembler	cAssembler;
	CAsm65Output*	pcOutput;
	uint8			uiByte;

	TestAsm65Assemble(&cAssembler,
		".org $2001\n"
		"Bytes:\n"
		"	.byte \"AB\", 1, -1\n"
		"	.word $1234, Bytes\n"
		"Aligned:\n"
		"	nop\n"
		"	.align 8\n"
		"Eight:\n"
		"	.long 1 + 2 * 3, (1 + 2) * 3\n"
		"	.quad -2\n"
		"Shift = 1 << 4 | 3 & ~1\n"
		"Here:\n"
		"	cpy A, Here\n"
		"	.byte 7\n"
		"Lonely:\n"
		"\n"
		"	nop\n");

	pcOutput = cAssembler.GetOutput();
	AssertSize(1, pcOutput->NumSegments());
	AssertTrue(pcOutput->Get(0x2001, &uiByte));
	AssertInt('A', uiByte);
	AssertTrue(pcOutput->Get(0x2002, &uiByte));
	AssertInt('B', uiByte);
	AssertShortHex((uint16)0xFF01, pcOutput->GetWord(0x2003));
	AssertShortHex((uint16)0x1234, pcOutput->GetWord(0x2005));
	AssertShortHex((uint16)0x2001, pcOutput->GetWord(0x2007));
	AssertTrue(pcOutput->Get(0x2009, &uiByte));
	AssertInt(0, uiByte);
	AssertShortHex((uint16)0x015C, pcOutput->GetWord(0x200A));
	AssertIntHex(7, pcOutput->GetLong(0x2010));
	AssertIntHex(9, pcOutput->GetLong(0x2014));
	AssertIntHex(0xFFFFFFFE, pcOutput->GetLong(0x2018));
	AssertIntHex(0xFFFFFFFF, pcOutput->GetLong(0x201C));
	AssertShortHex((uint16)0x2210, pcOutput->GetWord(0x2020));
	AssertShortHex((uint16)0x2020, pcOutput->GetWord(0x2022));
	AssertShortHex((uint16)0x0007, pcOutput->GetWord(0x2024));
	AssertShortHex((uint16)0x015C, pcOutput->GetWord(0x2026));

	AssertLongLongIntHex(0x200A, Symbol(&cAssembler, "Aligned"));
	AssertLongLongIntHex(0x2010, Symbol(&cAssembler, "Eight"));
	AssertLong(18, Symbol(&cAssembler, "Shift"));
	AssertLongLongIntHex(0x2020, Symbol(&cAssembler, "Here"));
	AssertLongLongIntHex(0x2026, Symbol(&cAssembler, "Lonely"));
	cAssembler.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// Addresses below 0001:0000 use the one word offset modes.
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65LabelsOffset(void)
{
	CAsm65Assembler	cAssembler;

	TestAsm65Assemble(&cAssembler,
		".org $FFF0\n"
		"	cpy A, [Later]\n"
		"	cpy A, [Earlier]\n"
		"Earlier:\n"
		"	.byte 1\n"
		".org $10000\n"
		"Later:\n"
		"	.byte 2\n");

	AssertShortHex((uint16)0x0820, TestAsm65Word(&cAssembler, 0xFFF0));
	AssertShortHex((uint16)0x0000, TestAsm65Word(&cAssembler, 0xFFF2));
	AssertShortHex((uint16)0x0001, TestAsm65Word(&cAssembler, 0xFFF4));
	AssertShortHex((uint16)0x0860, TestAsm65Word(&cAssembler, 0xFFF6));
	AssertShortHex((uint16)0xFFFA, TestAsm65Word(&cAssembler, 0xFFF8));
	AssertSize(2, cAssembler.GetOutput()->NumSegments());
	cAssembler.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// Each branch growing pushes the next target further away.
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65LabelsCascade(void)
{
	CAsm65Assembler	cAssembler;

	TestAsm65Assemble(&cAssembler,
		".org $3000\n"
		"	brac z, End\n"
		"	brac z, End\n"
		"	brac z, End\n"
		"	brac z, End\n"
		"	brac z, End\n"
		"End:\n"
		"	stp\n");

	//The last branch (offset 0 is not embedded) grows, then the first (offset 10).
	AssertLongLongIntHex(0x300E, Symbol(&cAssembler, "End"));
	AssertShortHex((uint16)0x601C, TestAsm65Word(&cAssembler, 0x3000));
	AssertShortHex((uint16)0x000A, TestAsm65Word(&cAssembler, 0x3002));
	AssertShortHex((uint16)0x630C, TestAsm65Word(&cAssembler, 0x3004));
	AssertShortHex((uint16)0x620C, TestAsm65Word(&cAssembler, 0x3006));
	AssertShortHex((uint16)0x610C, TestAsm65Word(&cAssembler, 0x3008));
	AssertShortHex((uint16)0x601C, TestAsm65Word(&cAssembler, 0x300A));
	AssertShortHex((uint16)0x0000, TestAsm65Word(&cAssembler, 0x300C));
	cAssembler.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65Labels(void)
{
	BeginTests();

	TestAsm65LabelsForward();
	TestAsm65LabelsData();
	TestAsm65LabelsOffset();
	TestAsm65LabelsCascade();

	TestStatistics();
}
