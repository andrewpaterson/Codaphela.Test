#include "Assembler65Lib/Asm65Tokeniser.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65TokeniserTokens(void)
{
	CAsm65Errors	cErrors;
	CAsm65Tokeniser	cTokeniser;
	CChars			sz;

	cErrors.Init();
	cTokeniser.Init(&cErrors);
	AssertTrue(cTokeniser.Tokenise("Loop: cpy A, [$12_34:16 + X] ; comment\n  .byte \"hi\\n\", 'x', 0b101, 0x1F << 2\n"));
	AssertSize(0, cErrors.NumErrors());

	sz.Init();
	cTokeniser.Print(&sz);
	AssertString(
		"Identifier Loop\n"
		"Punctuator :\n"
		"Identifier cpy\n"
		"Identifier A\n"
		"Punctuator ,\n"
		"Punctuator [\n"
		"Number 4660\n"
		"Punctuator :\n"
		"Number 16\n"
		"Punctuator +\n"
		"Identifier X\n"
		"Punctuator ]\n"
		"NewLine\n"
		"Identifier .byte\n"
		"String \"hi\n\"\n"
		"Punctuator ,\n"
		"Number 120\n"
		"Punctuator ,\n"
		"Number 5\n"
		"Punctuator ,\n"
		"Number 31\n"
		"Punctuator <<\n"
		"Number 2\n"
		"NewLine\n"
		"End\n", sz.Text());
	sz.Kill();

	AssertInt(2, cTokeniser.Get(13)->uiLine);
	AssertInt(3, cTokeniser.Get(13)->uiColumn);
	AssertInt(3, cTokeniser.Get(14)->uiStringLength);

	cTokeniser.Kill();
	cErrors.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65TokeniserErrors(void)
{
	CAsm65Errors	cErrors;
	CAsm65Tokeniser	cTokeniser;

	cErrors.Init();
	cTokeniser.Init(&cErrors);
	AssertFalse(cTokeniser.Tokenise("cpy A, 12x\n  \"open\nab # c\n"));
	AssertSize(3, cErrors.NumErrors());
	AssertString(
		"1:8: Malformed number\n"
		"2:3: Unterminated string\n"
		"3:4: Unknown character\n", cErrors.Text());
	cTokeniser.Kill();
	cErrors.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65Tokeniser(void)
{
	BeginTests();

	TestAsm65TokeniserTokens();
	TestAsm65TokeniserErrors();

	TestStatistics();
}
