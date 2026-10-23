#include "BaseLib/Chars.h"
#include "TestLib/Assert.h"
#include "TestAsm65Context.h"


#define BRAINFUCK_OUTPUT	0x40000


//////////////////////////////////////////////////////////////////////////
//
// Runs the Brainfuck program (assembler .byte lines) and checks what it printed.
//
//////////////////////////////////////////////////////////////////////////
static void AssertBrainfuck(const char* szProgram, const char* szExpected)
{
	STestAsm65Run	sRun;
	CChars			szSource;
	CChars			szOutput;
	uint32			uiAddress;
	uint8			uiByte;

	szSource.Init();
	TestAsm65ReadSource(&szSource, "Brainfuck.asm");
	szSource.Append(szProgram);
	szSource.Append("\t\t.byte 0\n");
	AssertTrue(TestAsm65Begin(&sRun, szSource.Text(), 0x1000));
	AssertTrue(TestAsm65Run(&sRun, 1000000) < 1000000);

	szOutput.Init();
	for (uiAddress = BRAINFUCK_OUTPUT; uiAddress < BRAINFUCK_OUTPUT + 1000; uiAddress++)
	{
		uiByte = sRun.pcContext->GetByte(uiAddress);
		if (uiByte == 0)
		{
			break;
		}
		szOutput.Append((char)uiByte);
	}
	AssertString(szExpected, szOutput.Text());

	szOutput.Kill();
	TestAsm65End(&sRun);
	szSource.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65BrainfuckPrograms(void)
{
	AssertBrainfuck(
		"\t\t.byte \"Hello World program by Urban Mueller\", 10\n"
		"\t\t.byte \"++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.\"\n",
		"Hello World!\n");

	//Cell 1 = 8 x 6 = '0', then print and increment it 10 times.
	AssertBrainfuck(
		"\t\t.byte \"++++++++ [ >++++++ <- ]   set cell 1 to 48\", 10\n"
		"\t\t.byte \"++++++++++ [ >.+ <- ]     print 10 digits\", 10\n",
		"0123456789");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65Brainfuck(void)
{
	BeginTests();

	TestAsm65BrainfuckPrograms();

	TestStatistics();
}
