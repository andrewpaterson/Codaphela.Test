#include <stdio.h>
#include "BaseLib/Chars.h"
#include "TestLib/Assert.h"
#include "TestAsm65Context.h"


#define SHA256_HASH		0x0200


//////////////////////////////////////////////////////////////////////////
//
// szMessage is the assembler data for the message; szDigest the expected hex digest.
//
//////////////////////////////////////////////////////////////////////////
static void AssertSha256(const char* szMessage, const char* szDigest)
{
	STestAsm65Run	sRun;
	CChars			szSource;
	CChars			szActual;
	char			szWord[16];
	int				i;

	szSource.Init();
	TestAsm65ReadSource(&szSource, "Sha256.asm");
	szSource.Append(szMessage);
	szSource.Append("MessageEnd:\n");
	AssertTrue(TestAsm65Begin(&sRun, szSource.Text(), 0x1000));
	AssertTrue(TestAsm65Run(&sRun, 1000000) < 1000000);

	szActual.Init();
	for (i = 0; i < 8; i++)
	{
		snprintf(szWord, sizeof(szWord), "%08x", sRun.pcContext->GetLong(SHA256_HASH + 4 * i));
		szActual.Append(szWord);
	}
	AssertString(szDigest, szActual.Text());

	szActual.Kill();
	TestAsm65End(&sRun);
	szSource.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// The FIPS 180 examples: one block, an empty message and two blocks.
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65Sha256Digests(void)
{
	AssertSha256("\t\t.byte \"abc\"\n", "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad");
	AssertSha256("", "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855");
	AssertSha256("\t\t.byte \"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq\"\n", "248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65Sha256(void)
{
	BeginTests();

	TestAsm65Sha256Digests();

	TestStatistics();
}
