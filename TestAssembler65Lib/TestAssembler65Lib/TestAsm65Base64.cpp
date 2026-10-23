#include <string.h>
#include "BaseLib/Chars.h"
#include "TestLib/Assert.h"
#include "TestAsm65Context.h"


#define BASE64_ENCODED	0x4000
#define BASE64_DECODED	0x5000


//////////////////////////////////////////////////////////////////////////
//
// szInput is the assembler data after Input; pvBytes and iLength are those bytes.
//
//////////////////////////////////////////////////////////////////////////
static void AssertBase64(const char* szInput, const void* pvBytes, int iLength, const char* szEncoded)
{
	STestAsm65Run	sRun;
	CChars			szSource;
	CChars			szActual;
	uint32			uiAddress;
	uint8			uiByte;
	int				i;
	int				iDifferent;

	szSource.Init();
	TestAsm65ReadSource(&szSource, "Base64.asm");
	szSource.Append(szInput);
	szSource.Append("InputEnd:\n");
	AssertTrue(TestAsm65Begin(&sRun, szSource.Text(), 0x1000));
	AssertTrue(TestAsm65Run(&sRun, 1000000) < 1000000);

	szActual.Init();
	for (uiAddress = BASE64_ENCODED; (uiByte = sRun.pcContext->GetByte(uiAddress)) != 0; uiAddress++)
	{
		szActual.Append((char)uiByte);
	}
	AssertString(szEncoded, szActual.Text());
	szActual.Kill();

	iDifferent = 0;
	for (i = 0; i < iLength; i++)
	{
		if (sRun.pcContext->GetByte(BASE64_DECODED + i) != ((uint8*)pvBytes)[i])
		{
			iDifferent++;
		}
	}
	AssertInt(0, iDifferent);
	AssertInt(0, sRun.pcContext->GetByte(BASE64_DECODED + iLength));

	TestAsm65End(&sRun);
	szSource.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// The RFC 4648 style examples: no padding, ==, = and an empty input.
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65Base64Text(void)
{
	AssertBase64("\t\t.byte \"Many hands make light work.\"\n", "Many hands make light work.", 27, "TWFueSBoYW5kcyBtYWtlIGxpZ2h0IHdvcmsu");
	AssertBase64("\t\t.byte \"light w\"\n", "light w", 7, "bGlnaHQgdw==");
	AssertBase64("\t\t.byte \"light wo\"\n", "light wo", 8, "bGlnaHQgd28=");
	AssertBase64("\t\t.byte \"M\"\n", "M", 1, "TQ==");
	AssertBase64("", "", 0, "");
}


//////////////////////////////////////////////////////////////////////////
//
// Bytes that use + and / and a zero byte.
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65Base64Binary(void)
{
	static const uint8	auiBytes[5] = { 0x00, 0x01, 0xFE, 0xFF, 0x80 };

	AssertBase64("\t\t.byte 0, 1, $FE, $FF, $80\n", auiBytes, 5, "AAH+/4A=");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65Base64(void)
{
	BeginTests();

	TestAsm65Base64Text();
	TestAsm65Base64Binary();

	TestStatistics();
}
