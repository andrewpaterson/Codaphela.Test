#include "BaseLib/Chars.h"
#include "TestLib/Assert.h"
#include "TestAsm65C64Context.h"


#define BIGNUM_FACTORIAL_TEXT	0x0120
#define BIGNUM_FIBONACCI_TEXT	0x0128


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
static void AppendText(CChars* psz, CAsm65Memory* pcContext, uint32 uiAddress)
{
	uint8	uiByte;

	for (; (uiByte = pcContext->GetByte(uiAddress)) != 0; uiAddress++)
	{
		psz->Append((char)uiByte);
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65BignumFactorialFibonacci(void)
{
	STestAsm65Run	sRun;
	CChars			szText;

	AssertTrue(TestAsm65BeginFile(&sRun, "Bignum.asm", 0x1000));
	AssertTrue(TestAsm65Run(&sRun, 10000000) < 10000000);

	szText.Init();
	AppendText(&szText, sRun.pcContext, sRun.pcContext->GetLong(BIGNUM_FACTORIAL_TEXT));
	AssertString("93326215443944152681699238856266700490715968264381621468592963895217599993229915608941463976156518286253697920827223758251185210916864000000000000000000000000", szText.Text());
	szText.Kill();

	szText.Init();
	AppendText(&szText, sRun.pcContext, sRun.pcContext->GetLong(BIGNUM_FIBONACCI_TEXT));
	AssertString("222232244629420445529739893461909967206666939096499764990979600", szText.Text());
	szText.Kill();

	TestAsm65End(&sRun);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65C64Bignum(void)
{
	BeginTests();

	TestAsm65BignumFactorialFibonacci();

	TestStatistics();
}
