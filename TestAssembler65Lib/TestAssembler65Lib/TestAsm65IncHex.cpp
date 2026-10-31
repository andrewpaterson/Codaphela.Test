#include <string.h>
#include "BaseLib/TextFile.h"
#include "Assembler65Lib/Asm65816Assembler.h"
#include "Assembler65Lib/Asm65Linker.h"
#include "TestLib/Assert.h"
#include "TestAsm65C64Context.h"


#define TEST_ASM65_MATH_TABLES	".." _FS_ ".." _FS_ ".." _FS_ "commonlibraries" _FS_ "Libc65" _FS_ "MathTbls"


//////////////////////////////////////////////////////////////////////////
//
// .inchex in absolute mode: Input/IncHex.hex has DE AD BE EF at $10 and
// CA FE at $16, so $14 and $15 are filled with $FF; whole and sliced.
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65IncHexAbsolute(void)
{
	CAsm65C64Assembler	cAssembler;
	CAsm65Output*	pcOutput;
	int64			iEnd;
	uint8			uiByte;

	cAssembler.Init();
	cAssembler.SetDirectory("Input");
	AssertTrue(cAssembler.Assemble(".org $1000\n.inchex \"IncHex.hex\"\nEnd:\n.byte 1\n"));
	AssertString("", cAssembler.GetErrors());
	AssertTrue(cAssembler.GetSymbol("End", &iEnd));
	AssertLongLongIntHex(0x1008LL, iEnd);
	pcOutput = cAssembler.GetOutput();
	AssertIntHex(0xADDE, pcOutput->GetWord(0x1000));
	AssertIntHex(0xEFBE, pcOutput->GetWord(0x1002));
	AssertIntHex(0xFFFF, pcOutput->GetWord(0x1004));
	AssertIntHex(0xFECA, pcOutput->GetWord(0x1006));
	AssertTrue(pcOutput->Get(0x1008, &uiByte));
	AssertInt(1, uiByte);
	cAssembler.Kill();

	cAssembler.Init();
	cAssembler.SetDirectory("Input");
	AssertTrue(cAssembler.Assemble(".org $1000\n.inchex \"IncHex.hex\", $E\nEnd:\n"));
	AssertString("", cAssembler.GetErrors());
	AssertTrue(cAssembler.GetSymbol("End", &iEnd));
	AssertLongLongIntHex(0x100ALL, iEnd);
	AssertIntHex(0xFFFF, cAssembler.GetOutput()->GetWord(0x1000));
	AssertIntHex(0xADDE, cAssembler.GetOutput()->GetWord(0x1002));
	cAssembler.Kill();

	//Slices: from $12 to the end, and 4 bytes from $13.
	cAssembler.Init();
	cAssembler.SetDirectory("Input");
	AssertTrue(cAssembler.Assemble(".org $1000\n.inchex \"IncHex.hex\", $12\nMiddle:\n.inchex \"IncHex.hex\", $13, 4\nEnd:\n"));
	AssertString("", cAssembler.GetErrors());
	AssertTrue(cAssembler.GetSymbol("Middle", &iEnd));
	AssertLongLongIntHex(0x1006LL, iEnd);
	AssertTrue(cAssembler.GetSymbol("End", &iEnd));
	AssertLongLongIntHex(0x100ALL, iEnd);
	AssertIntHex(0xEFBE, cAssembler.GetOutput()->GetWord(0x1000));
	AssertIntHex(0xFECA, cAssembler.GetOutput()->GetWord(0x1004));
	AssertIntHex(0xFFEF, cAssembler.GetOutput()->GetWord(0x1006));
	AssertIntHex(0xCAFF, cAssembler.GetOutput()->GetWord(0x1008));
	cAssembler.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
static void AssertIncHexError(const char* szExpected, const char* szSource, bool bObject)
{
	CAsm65C64Assembler	cAssembler;
	CAsm65Object	cObject;

	cAssembler.Init();
	cAssembler.SetDirectory("Input");
	if (bObject)
	{
		cObject.Init("test");
		AssertFalse(cAssembler.AssembleObject(szSource, &cObject));
		cObject.Kill();
	}
	else
	{
		AssertFalse(cAssembler.Assemble(szSource));
	}
	AssertString(szExpected, cAssembler.GetErrors());
	cAssembler.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65IncHexErrors(void)
{
	AssertIncHexError("2:9: Included bytes must be 0 to 16MB '\"IncHex.hex\"'\n", ".org $1000\n.inchex \"IncHex.hex\", $10, -1\n", false);
	AssertIncHexError("2:9: Could not read Input" _FS_ "Missing.hex '\"Missing.hex\"'\n", ".org $1000\n.inchex \"Missing.hex\"\n", false);
	AssertIncHexError("2:9: Expected a file name '5'\n", ".org $1000\n.inchex 5\n", false);
	AssertIncHexError("2:9: A bss section only has labels, .space and .align '\"IncHex.hex\"'\n", ".section bss.Table\n.inchex \"IncHex.hex\"\n", true);
}


//////////////////////////////////////////////////////////////////////////
//
// Libc65's MathMult.asm (Garth Wilson's MULT.HEX) as a W65C816 object: a
// 128KB section aligned to a bank, which the linker puts at the start of one,
// with a * b for every pair of bytes.
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65IncHexMathTable(void)
{
	CTextFile			cFile;
	CAsm65816Assembler	cAssembler;
	CAsm65Object		acObjects[2];
	CAsm65Linker		cLinker;
	SAsm65Section*		psSection;
	int64				iMathMult;
	CAsm65Output*		pcOutput;
	uint32				a;
	uint32				b;
	size				uiWrong;

	cFile.Init();
	AssertTrue(cFile.Read(TEST_ASM65_MATH_TABLES _FS_ "MathMult.asm"));
	cFile.PassifyNewlines();
	acObjects[0].Init("MathMult");
	cAssembler.Init();
	cAssembler.SetDirectory(TEST_ASM65_MATH_TABLES);
	AssertTrue(cAssembler.AssembleObject(cFile.Text(), &acObjects[0]));
	AssertString("", cAssembler.GetErrors());
	cAssembler.Kill();
	cFile.Kill();
	psSection = acObjects[0].GetSection(acObjects[0].NumSections() - 1);
	AssertString("rodata.MathMult", psSection->szName.Text());
	AssertIntHex(0x20000, psSection->uiSize);
	AssertIntHex(0x10000, psSection->uiAlignment);

	acObjects[1].Init("Code");
	cAssembler.Init();
	AssertTrue(cAssembler.AssembleObject("\t\t.section text.Start\nStart:\n\t\t.width (A, X), 16\n\t\tlda [MathMult + $1FFFE]:24\n\t\tstp\n", &acObjects[1]));
	AssertString("", cAssembler.GetErrors());
	cAssembler.Kill();

	cLinker.Init();
	cLinker.SetBankSize(0x10000);
	cLinker.SetAddress(ASK65_Text, 0x10000);
	cLinker.AddObject(&acObjects[1]);
	cLinker.AddObject(&acObjects[0]);
	AssertTrue(cLinker.Link());
	AssertString("", cLinker.GetErrors());
	AssertTrue(cLinker.GetSymbol("MathMult", &iMathMult));
	AssertLongLongIntHex(0x20000LL, iMathMult);
	pcOutput = cLinker.GetOutput();
	AssertIntHex(0x0000, pcOutput->GetWord(0x20000));
	AssertIntHex(6, pcOutput->GetWord(0x20000 + ((2 << 8) | 3) * 2));
	AssertIntHex(255 * 255, pcOutput->GetWord(0x20000 + 0xFFFF * 2));
	uiWrong = 0;
	for (a = 0; a < 256; a++)
	{
		for (b = 0; b < 256; b++)
		{
			if (pcOutput->GetWord(0x20000 + ((a << 8) | b) * 2) != a * b)
			{
				uiWrong++;
			}
		}
	}
	AssertSize(0, uiWrong);
	AssertIntHex(0x3FFFE, pcOutput->GetWord(0x10001) | (pcOutput->GetWord(0x10003) & 0xFF) << 16);
	cLinker.Kill();
	acObjects[1].Kill();
	acObjects[0].Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// .include: Input/Include.inc defines Answer and includes
// IncludeNested.inc, which defines Nested from it; every pass reads them.
// A file that isn't there is an error.
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65Include(void)
{
	CAsm65C64Assembler	cAssembler;
	int64				iEnd;
	int64				iNested;

	cAssembler.Init();
	cAssembler.SetDirectory("Input");
	AssertTrue(cAssembler.Assemble(".org $1000\n\t\t.include \"Include.inc\"\n.word Answer, Nested, Later\nEnd:\nLater = End + 1\n"));
	AssertString("", cAssembler.GetErrors());
	AssertTrue(cAssembler.GetSymbol("End", &iEnd));
	AssertLongLongIntHex(0x1006LL, iEnd);
	AssertTrue(cAssembler.GetSymbol("Nested", &iNested));
	AssertLong(43LL, iNested);
	AssertIntHex(42, cAssembler.GetOutput()->GetWord(0x1000));
	AssertIntHex(43, cAssembler.GetOutput()->GetWord(0x1002));
	AssertIntHex(0x1007, cAssembler.GetOutput()->GetWord(0x1004));
	cAssembler.Kill();

	cAssembler.Init();
	cAssembler.SetDirectory("Input");
	AssertFalse(cAssembler.Assemble(".org $1000\n.include \"Missing.inc\"\n"));
	AssertTrue(strstr(cAssembler.GetErrors(), "Could not read the included file") != NULL);
	cAssembler.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65IncHex(void)
{
	BeginTests();

	TestAsm65IncHexAbsolute();
	TestAsm65IncHexErrors();
	TestAsm65IncHexMathTable();
	TestAsm65Include();

	TestStatistics();
}
