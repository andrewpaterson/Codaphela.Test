#include "BaseLib/Chars.h"
#include "TestLib/Assert.h"
#include "TestAsm65Context.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
static void AssertText(const char* szExpected, CAsm65Memory* pcContext, uint32 uiAddress, int iLength)
{
	CChars	sz;
	int		i;

	sz.Init();
	for (i = 0; i < iLength; i++)
	{
		sz.Append((char)pcContext->GetByte(uiAddress + i));
	}
	AssertString(szExpected, sz.Text());
	sz.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65StringsRoutines(void)
{
	STestAsm65Run	sRun;

	AssertTrue(TestAsm65BeginFile(&sRun, "Strings.asm", 0x1000));
	AssertTrue(TestAsm65Run(&sRun, 100000) < 100000);

	AssertInt(43, sRun.pcContext->GetLong(0x0100));				//strlen
	AssertText("The quick brown fox jumps over the lazy dog", sRun.pcContext, 0x3000, 43);	//strcpy
	AssertInt(0, sRun.pcContext->GetByte(0x3000 + 43));
	AssertInt(0, sRun.pcContext->GetByte(0x3000 + 44));
	AssertIntHex(0x2004, sRun.pcContext->GetLong(0x0108));			//strchr finds the q
	AssertText("HELLO", sRun.pcContext, 0x2060, 5);					//upper case
	AssertInt(0, sRun.pcContext->GetByte(0x2065));
	AssertText("HELLO!", sRun.pcContext, 0x2070, 6);				//end marker stripped
	AssertInt(5, sRun.pcContext->GetLong(0x0110));
	AssertText("ABABCDEFGH", sRun.pcContext, 0x2080, 10);			//memmove up
	AssertText("CDEFGHIJIJ", sRun.pcContext, 0x2090, 10);			//memmove down
	AssertIntHex(0xFFFFFFFF, sRun.pcContext->GetLong(0x0118));		//"...brown..." < "...red..."
	AssertInt(1, sRun.pcContext->GetLong(0x0120));					//equal strings

	TestAsm65End(&sRun);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65Strings(void)
{
	BeginTests();

	TestAsm65StringsRoutines();

	TestStatistics();
}
