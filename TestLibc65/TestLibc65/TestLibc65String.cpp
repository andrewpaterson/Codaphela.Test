#include "BaseLib/TextFile.h"
#include "TestLib/Assert.h"
#include "TestLibc65Context.h"
#include "TestLibc65StringCases.h"


//////////////////////////////////////////////////////////////////////////
//
// string.h against the C standard.  Comparisons are checked by sign and found pointers as offsets (-1 for
// NULL).
//
//////////////////////////////////////////////////////////////////////////
void TestLibc65StringFunctions(void)
{
	static const char*	aszUnits[] = { "string.cpp", "string.asm", NULL };
	static const int32	aiExpected[] =
	{
		0, 1, 11,								//strlen
		0, -1, 1, -1, 1, 0, 1,					//strcmp, the last as unsigned char
		0, -1, 0, -1, 0,						//strncmp
		4, -1, 11, 7, -1, 11,					//strchr, strrchr
		6, 4, 0, -1, 1,							//strstr
		-1, 0, 1, 5, -1, 1,						//memcmp, memchr
		1, 1, 1, 1, 1, 1, 1,					//the functions return their destination
	};
	STestLibc65Run		sRun;
	size				i;

	AssertTrue(TestLibc65Begin(&sRun, aszUnits, "",
		"#include <string.h>\n"
		"int Sign(int i)\n"
		"{\n"
		"	return (i > 0) - (i < 0);\n"
		"}\n"
		"int Offset(const void* pv, const char* szBase)\n"
		"{\n"
		"	return pv ? (int)((const char*)pv - szBase) : -1;\n"
		"}\n"
		"int main()\n"
		"{\n"
		"	long*		p;\n"
		"	char*		pc;\n"
		"	const char*	sz;\n"
		"	char		ac[16];\n"
		"	p = (long*)0x100000;\n"
		"	pc = (char*)0x108000;\n"
		"	*p++ = strlen(\"\");\n"
		"	*p++ = strlen(\"a\");\n"
		"	*p++ = strlen(\"hello world\");\n"
		"	*p++ = Sign(strcmp(\"abc\", \"abc\"));\n"
		"	*p++ = Sign(strcmp(\"abc\", \"abd\"));\n"
		"	*p++ = Sign(strcmp(\"abd\", \"abc\"));\n"
		"	*p++ = Sign(strcmp(\"ab\", \"abc\"));\n"
		"	*p++ = Sign(strcmp(\"abc\", \"ab\"));\n"
		"	*p++ = Sign(strcmp(\"\", \"\"));\n"
		"	*p++ = Sign(strcmp(\"\\x80\", \"a\"));\n"
		"	*p++ = Sign(strncmp(\"abcdef\", \"abcxyz\", 3));\n"
		"	*p++ = Sign(strncmp(\"abcdef\", \"abcxyz\", 4));\n"
		"	*p++ = Sign(strncmp(\"abc\", \"abd\", 0));\n"
		"	*p++ = Sign(strncmp(\"ab\", \"abc\", 5));\n"
		"	*p++ = Sign(strncmp(\"abc\", \"abc\", 10));\n"
		"	sz = \"hello world\";\n"
		"	*p++ = Offset(strchr(sz, 'o'), sz);\n"
		"	*p++ = Offset(strchr(sz, 'z'), sz);\n"
		"	*p++ = Offset(strchr(sz, '\\0'), sz);\n"
		"	*p++ = Offset(strrchr(sz, 'o'), sz);\n"
		"	*p++ = Offset(strrchr(sz, 'z'), sz);\n"
		"	*p++ = Offset(strrchr(sz, '\\0'), sz);\n"
		"	*p++ = Offset(strstr(sz, \"world\"), sz);\n"
		"	*p++ = Offset(strstr(sz, \"o w\"), sz);\n"
		"	*p++ = Offset(strstr(sz, \"\"), sz);\n"
		"	*p++ = Offset(strstr(sz, \"worlds\"), sz);\n"
		"	sz = \"aab\";\n"
		"	*p++ = Offset(strstr(sz, \"ab\"), sz);\n"
		"	*p++ = Sign(memcmp(\"abc\", \"abd\", 3));\n"
		"	*p++ = Sign(memcmp(\"abc\", \"abd\", 2));\n"
		"	*p++ = Sign(memcmp(\"\\x80\", \"\\x01\", 1));\n"
		"	sz = \"0123456789\";\n"
		"	*p++ = Offset(memchr(sz, '5', 10), sz);\n"
		"	*p++ = Offset(memchr(sz, '5', 5), sz);\n"
		"	sz = \"a\\200b\";\n"
		"	*p++ = Offset(memchr(sz, 0x180, 3), sz);\n"
		"	*p++ = strcpy(ac, \"x\") == ac;\n"
		"	*p++ = strcat(ac, \"y\") == ac;\n"
		"	*p++ = memset(ac, 0, 1) == ac;\n"
		"	*p++ = memcpy(ac, \"a\", 1) == ac;\n"
		"	*p++ = memmove(ac, \"a\", 1) == ac;\n"
		"	*p++ = strncpy(ac, \"a\", 2) == ac;\n"
		"	*p++ = strncat(ac, \"a\", 1) == ac;\n"
		"	strcpy(pc, \"abc\");\n"
		"	strcat(pc, \"def\");\n"
		"	memset(pc + 16, 'Z', 8);\n"
		"	strncpy(pc + 16, \"xy\", 5);\n"
		"	memset(pc + 32, 'Z', 8);\n"
		"	strncpy(pc + 32, \"abcdef\", 3);\n"
		"	memset(pc + 48, 'Z', 8);\n"
		"	strcpy(pc + 48, \"ab\");\n"
		"	strncat(pc + 48, \"cdef\", 2);\n"
		"	memcpy(pc + 64, \"0123456789\", 10);\n"
		"	memmove(pc + 66, pc + 64, 6);\n"
		"	memcpy(pc + 80, \"0123456789\", 10);\n"
		"	memmove(pc + 80, pc + 82, 6);\n"
		"	memset(pc + 96, 0x141, 4);\n"
		"	memcpy(pc + 112, \"0123456789ABCDEF\", 16);\n"
		"	memmove(pc + 116, pc + 112, 10);\n"
		"	return 0;\n"
		"}\n"));
	AssertTrue(TestLibc65Run(&sRun, 2000000));
	AssertInt(0, TestLibc65Return(&sRun));

	for (i = 0; i < sizeof(aiExpected) / sizeof(int32); i++)
	{
		AssertInt(aiExpected[i], TestLibc65Result(&sRun, i));
	}

	AssertMemory("abcdef\0", TestLibc65Bytes(&sRun, 0), 7);
	AssertMemory("xy\0\0\0ZZZ", TestLibc65Bytes(&sRun, 16), 8);
	AssertMemory("abcZZZZZ", TestLibc65Bytes(&sRun, 32), 8);
	AssertMemory("abcd\0ZZZ", TestLibc65Bytes(&sRun, 48), 8);
	AssertMemory("0101234589", TestLibc65Bytes(&sRun, 64), 10);
	AssertMemory("2345676789", TestLibc65Bytes(&sRun, 80), 10);
	AssertMemory("AAAA\0", TestLibc65Bytes(&sRun, 96), 5);
	AssertMemory("01230123456789EF", TestLibc65Bytes(&sRun, 112), 16);

	TestLibc65End(&sRun);
}


//////////////////////////////////////////////////////////////////////////
//
// TestLibc65StringCases.h's random cases (any length, alignment and overlap, empty strings, bytes above $7F,
// searches for the zero) give the same results with Libc65's string.asm on the 65C64 as with the host's C library.
//
//////////////////////////////////////////////////////////////////////////
void TestLibc65StringRandomCases(void)
{
	static const char*	aszUnits[] = { "string.cpp", "string.asm", NULL };
	STestLibc65Run		sRun;
	CTextFile			cFile;
	CChars				szSource;
	unsigned char		aucA[STRING_CASES_BUFFER];
	unsigned char		aucB[STRING_CASES_BUFFER];
	int32_t				aiResults[STRING_CASES_COUNT * 32];
	int					iCount;
	int					i;

	cFile.Init();
	AssertTrue(cFile.Read("TestLibc65StringCases.h"));
	cFile.PassifyNewlines();
	szSource.Init(cFile.Text());
	cFile.Kill();
	szSource.Append(
		"int main()\n"
		"{\n"
		"	int32_t*	p;\n"
		"	p = (int32_t*)0x100000;\n"
		"	p[0] = RunStringCases(p + 1, (unsigned char*)0x110000, (unsigned char*)0x111000);\n"
		"	return 0;\n"
		"}\n");
	AssertTrue(TestLibc65Begin(&sRun, aszUnits, "", szSource.Text()));
	szSource.Kill();
	AssertTrue(TestLibc65Run(&sRun, 100000000));

	iCount = RunStringCases(aiResults, aucA, aucB);
	AssertInt(iCount, TestLibc65Result(&sRun, 0));
	for (i = 0; i < iCount; i++)
	{
		AssertInt(aiResults[i], TestLibc65Result(&sRun, 1 + i));
	}

	TestLibc65End(&sRun);
}


//////////////////////////////////////////////////////////////////////////
//
// memcpy, memmove and memset across 64KB boundaries (the W65C816's banks: string816.asm's block moves stop at the
// end of a bank and go on in the next), the source and destination crossing at different places: a copy up, an
// overlapping copy down and a fill.
//
//////////////////////////////////////////////////////////////////////////
void TestLibc65StringBanks(void)
{
	static const char*	aszUnits[] = { "string.cpp", "string.asm", NULL };
	STestLibc65Run		sRun;
	unsigned char		aucSource[512];
	unsigned char		aucMoved[512];
	unsigned char		aucFill[100];
	int					i;

	//The program's pc is 0x108000 (TestLibc65Bytes' offset 0); the banks start at 0x110000, 0x120000 and 0x130000.  i
	//is a long: an int is 16 bits on the W65C816, and 0x7F00 + i would be negative past 255.
	AssertTrue(TestLibc65Begin(&sRun, aszUnits, "",
		"#include <string.h>\n"
		"int main()\n"
		"{\n"
		"	unsigned char*	pc;\n"
		"	long			i;\n"
		"	pc = (unsigned char*)0x108000;\n"
		"	for (i = 0; i < 512; i++)\n"
		"	{\n"
		"		pc[0x7F00 + i] = (unsigned char)(i * 7 + 1);\n"
		"		pc[0x8F00 + i] = (unsigned char)(i * 7 + 1);\n"
		"	}\n"
		"	memcpy(pc + 0x17F40, pc + 0x7F00, 512);\n"
		"	memmove(pc + 0x8F00 + 37, pc + 0x8F00, 400);\n"
		"	memset(pc + 0x27FF0, 0x5A, 100);\n"
		"	return 0;\n"
		"}\n"));
	AssertTrue(TestLibc65Run(&sRun, 2000000));
	AssertInt(0, TestLibc65Return(&sRun));

	for (i = 0; i < 512; i++)
	{
		aucSource[i] = (unsigned char)(i * 7 + 1);
		aucMoved[i] = (unsigned char)(i * 7 + 1);
	}
	memmove(aucMoved + 37, aucMoved, 400);
	memset(aucFill, 0x5A, 100);
	AssertMemory(aucSource, TestLibc65Bytes(&sRun, 0x17F40), 512);
	AssertMemory(aucMoved, TestLibc65Bytes(&sRun, 0x8F00), 512);
	AssertMemory(aucFill, TestLibc65Bytes(&sRun, 0x27FF0), 100);
	AssertTrue(TestLibc65Bytes(&sRun, 0x27FEF)[0] == 0);
	AssertTrue(TestLibc65Bytes(&sRun, 0x27FF0 + 100)[0] == 0);

	TestLibc65End(&sRun);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestLibc65String(void)
{
	BeginTests();

	TestLibc65StringFunctions();
	TestLibc65StringRandomCases();
	TestLibc65StringBanks();

	TestStatistics();
}

