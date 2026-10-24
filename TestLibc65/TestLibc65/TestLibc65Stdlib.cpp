#include "BaseLib/Chars.h"
#include "TestLib/Assert.h"
#include "TestLibc65Context.h"


//A string to convert, as it is written in the test program, and what the C standard says the conversion gives
//with 32 bit longs: the value and how many characters are used (0 when there are no digits).
struct STestLibc65Conversion
{
	const char*	szText;
	int			iBase;
	int32		iValue;
	int32		iEnd;
};


//////////////////////////////////////////////////////////////////////////
//
// Runs strtol or strtoul on each conversion and checks the value and end pointer.
//
//////////////////////////////////////////////////////////////////////////
static void TestLibc65StdlibConversions(const char* szFunction, STestLibc65Conversion* asConversions, size uiConversions)
{
	static const char*	aszUnits[] = { "stdlib.cpp", "string.cpp", "string.asm", "ctype.cpp", NULL };
	STestLibc65Run		sRun;
	CChars				szSource;
	size				i;

	szSource.Init("#include <stdlib.h>\nconst char* gaszText[] = {");
	for (i = 0; i < uiConversions; i++)
	{
		szSource.Append(" \"")->Append(asConversions[i].szText)->Append("\",");
	}
	szSource.Append(" };\nint gaiBase[] = {");
	for (i = 0; i < uiConversions; i++)
	{
		szSource.Append(' ')->Append(asConversions[i].iBase)->Append(',');
	}
	szSource.Append(" };\n");
	szSource.Append("int main()\n{\n\tint* p = (int*)0x100000;\n\tchar* pszEnd;\n");
	szSource.Append("\tfor (int i = 0; i < ")->Append((int)uiConversions)->Append("; i++)\n\t{\n");
	szSource.Append("\t\t*p++ = (int)")->Append(szFunction)->Append("(gaszText[i], &pszEnd, gaiBase[i]);\n");
	szSource.Append("\t\t*p++ = (int)(pszEnd - gaszText[i]);\n");
	szSource.Append("\t}\n\treturn 0;\n}\n");

	AssertTrue(TestLibc65Begin(&sRun, aszUnits, "", szSource.Text()));
	AssertTrue(TestLibc65Run(&sRun, 2000000));

	for (i = 0; i < uiConversions; i++)
	{
		AssertInt(asConversions[i].iValue, TestLibc65Result(&sRun, 2 * i));
		AssertInt(asConversions[i].iEnd, TestLibc65Result(&sRun, 2 * i + 1));
	}

	TestLibc65End(&sRun);
	szSource.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestLibc65StdlibStrtol(void)
{
	static STestLibc65Conversion	asConversions[] =
	{
		{ "0",				10,	0,				1 },
		{ "123",			10,	123,			3 },
		{ "  -42xyz",		10,	-42,			5 },
		{ "+7",				10,	7,				2 },
		{ "\\t\\n 12",		10,	12,				5 },
		{ "\\v\\f12",		10,	12,				4 },
		{ "0x1F",			16,	31,				4 },
		{ "0x1F",			0,	31,				4 },
		{ "0X1f",			0,	31,				4 },
		{ "017",			0,	15,				3 },
		{ "019",			0,	1,				2 },
		{ "z",				36,	35,				1 },
		{ "101",			2,	5,				3 },
		{ "0x",				16,	0,				1 },
		{ "0xg",			0,	0,				1 },
		{ "abc",			10,	0,				0 },
		{ "-",				10,	0,				0 },
		{ "  +",			10,	0,				0 },
		{ "2147483647",		10,	2147483647,		10 },
		{ "2147483648",		10,	2147483647,		10 },
		{ "-2147483648",	10,	INT32_MIN,		11 },
		{ "-2147483649",	10,	INT32_MIN,		11 },
		{ "99999999999",	10,	2147483647,		11 },
		{ "7fffffff",		16,	2147483647,		8 },
	};

	TestLibc65StdlibConversions("strtol", asConversions, sizeof(asConversions) / sizeof(STestLibc65Conversion));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestLibc65StdlibStrtoul(void)
{
	static STestLibc65Conversion	asConversions[] =
	{
		{ "4294967295",		10,	(int32)0xFFFFFFFF,	10 },
		{ "4294967296",		10,	(int32)0xFFFFFFFF,	10 },
		{ "-1",				10,	(int32)0xFFFFFFFF,	2 },
		{ "0xFFFFFFFF",		0,	(int32)0xFFFFFFFF,	10 },
		{ "123abc",			10,	123,				3 },
		{ "  -0",			10,	0,					4 },
		{ "",				10,	0,					0 },
	};

	TestLibc65StdlibConversions("strtoul", asConversions, sizeof(asConversions) / sizeof(STestLibc65Conversion));
}


//////////////////////////////////////////////////////////////////////////
//
// The C standard's example generator, which Libc65's rand follows.
//
//////////////////////////////////////////////////////////////////////////
static uint32	guiTestLibc65Next;


static int32 TestLibc65Rand(void)
{
	guiTestLibc65Next = guiTestLibc65Next * 1103515245 + 12345;
	return (int32)((guiTestLibc65Next / 65536) % 32768);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestLibc65StdlibRand(void)
{
	static const char*	aszUnits[] = { "stdlib.cpp", "string.cpp", "string.asm", "ctype.cpp", NULL };
	STestLibc65Run		sRun;
	size				i;
	size				j;

	AssertTrue(TestLibc65Begin(&sRun, aszUnits, "",
		"#include <stdlib.h>\n"
		"int main()\n"
		"{\n"
		"	int* p = (int*)0x100000;\n"
		"	for (int i = 0; i < 5; i++)\n"
		"	{\n"
		"		*p++ = rand();\n"
		"	}\n"
		"	srand(1);\n"
		"	for (int i = 0; i < 5; i++)\n"
		"	{\n"
		"		*p++ = rand();\n"
		"	}\n"
		"	srand(42);\n"
		"	for (int i = 0; i < 5; i++)\n"
		"	{\n"
		"		*p++ = rand();\n"
		"	}\n"
		"	*p++ = RAND_MAX;\n"
		"	return 0;\n"
		"}\n"));
	AssertTrue(TestLibc65Run(&sRun, 2000000));

	//Without srand the seed is 1.
	for (j = 0; j < 3; j++)
	{
		guiTestLibc65Next = (j == 2) ? 42 : 1;
		for (i = 0; i < 5; i++)
		{
			AssertInt(TestLibc65Rand(), TestLibc65Result(&sRun, 5 * j + i));
		}
	}
	AssertInt(32767, TestLibc65Result(&sRun, 15));

	TestLibc65End(&sRun);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestLibc65StdlibQsort(void)
{
	static const char*	aszUnits[] = { "stdlib.cpp", "string.cpp", "string.asm", "ctype.cpp", NULL };
	static const int32	aiAscending[] = { -2, 0, 1, 3, 3, 5, 5, 7, 8, 9 };
	static const int32	aiDescending[] = { 9, 8, 7, 5, 5, 3, 3, 1, 0, -2 };
	static const int32	aiPairs[] = { 1, 30, 2, 20, 3, 10 };
	STestLibc65Run		sRun;
	size				i;

	AssertTrue(TestLibc65Begin(&sRun, aszUnits, "",
		"#include <stdlib.h>\n"
		"struct SPair\n"
		"{\n"
		"	int	iKey;\n"
		"	int	iValue;\n"
		"};\n"
		"int Ascending(const void* pv1, const void* pv2)\n"
		"{\n"
		"	return *(const int*)pv1 - *(const int*)pv2;\n"
		"}\n"
		"int Descending(const void* pv1, const void* pv2)\n"
		"{\n"
		"	return *(const int*)pv2 - *(const int*)pv1;\n"
		"}\n"
		"int ByKey(const void* pv1, const void* pv2)\n"
		"{\n"
		"	return ((const SPair*)pv1)->iKey - ((const SPair*)pv2)->iKey;\n"
		"}\n"
		"int gaiA[10] = { 5, 3, 9, 1, 5, 0, -2, 7, 3, 8 };\n"
		"int gaiB[10] = { 5, 3, 9, 1, 5, 0, -2, 7, 3, 8 };\n"
		"SPair gasPairs[3] = { { 3, 10 }, { 1, 30 }, { 2, 20 } };\n"
		"int giOne = 4;\n"
		"int main()\n"
		"{\n"
		"	int* p = (int*)0x100000;\n"
		"	qsort(gaiA, 10, sizeof(int), Ascending);\n"
		"	qsort(gaiB, 10, sizeof(int), Descending);\n"
		"	qsort(gasPairs, 3, sizeof(SPair), ByKey);\n"
		"	qsort(&giOne, 1, sizeof(int), Ascending);\n"
		"	qsort(&giOne, 0, sizeof(int), Ascending);\n"
		"	for (int i = 0; i < 10; i++)\n"
		"	{\n"
		"		*p++ = gaiA[i];\n"
		"	}\n"
		"	for (int i = 0; i < 10; i++)\n"
		"	{\n"
		"		*p++ = gaiB[i];\n"
		"	}\n"
		"	for (int i = 0; i < 3; i++)\n"
		"	{\n"
		"		*p++ = gasPairs[i].iKey;\n"
		"		*p++ = gasPairs[i].iValue;\n"
		"	}\n"
		"	*p++ = giOne;\n"
		"	return 0;\n"
		"}\n"));
	AssertTrue(TestLibc65Run(&sRun, 2000000));

	for (i = 0; i < 10; i++)
	{
		AssertInt(aiAscending[i], TestLibc65Result(&sRun, i));
		AssertInt(aiDescending[i], TestLibc65Result(&sRun, 10 + i));
	}
	for (i = 0; i < 6; i++)
	{
		AssertInt(aiPairs[i], TestLibc65Result(&sRun, 20 + i));
	}
	AssertInt(4, TestLibc65Result(&sRun, 26));

	TestLibc65End(&sRun);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestLibc65StdlibAllocation(void)
{
	static const char*	aszUnits[] = { "stdlib.cpp", "string.cpp", "string.asm", "ctype.cpp", NULL };
	STestLibc65Run		sRun;
	size				i;

	AssertTrue(TestLibc65Begin(&sRun, aszUnits, "",
		"#include <stdlib.h>\n"
		"#include <string.h>\n"
		"int main()\n"
		"{\n"
		"	int*	p;\n"
		"	char*	a;\n"
		"	char*	b;\n"
		"	char*	c;\n"
		"	char*	d;\n"
		"	char*	e;\n"
		"	char*	f;\n"
		"	int		iZero;\n"
		"	p = (int*)0x100000;\n"
		"	a = (char*)malloc(10);\n"
		"	*p++ = a != NULL;\n"
		"	*p++ = ((unsigned int)a & 3) == 0;\n"
		"	b = (char*)malloc(20);\n"
		"	*p++ = (b != NULL) && ((b >= a + 10) || (b + 20 <= a));\n"
		"	memset(a, 0xAA, 10);\n"
		"	memset(b, 0xBB, 20);\n"
		"	*p++ = (a[9] == (char)0xAA) && (b[0] == (char)0xBB);\n"
		"	free(a);\n"
		"	c = (char*)calloc(5, 2);\n"
		"	*p++ = c != NULL;\n"
		"	iZero = 1;\n"
		"	for (int i = 0; i < 10; i++)\n"
		"	{\n"
		"		if (c[i] != 0)\n"
		"		{\n"
		"			iZero = 0;\n"
		"		}\n"
		"	}\n"
		"	*p++ = iZero;\n"
		"	memcpy(c, \"123456789\", 10);\n"
		"	d = (char*)realloc(c, 100);\n"
		"	*p++ = (d != NULL) && (memcmp(d, \"123456789\", 10) == 0);\n"
		"	e = (char*)realloc(d, 4);\n"
		"	*p++ = (e != NULL) && (memcmp(e, \"1234\", 4) == 0);\n"
		"	f = (char*)realloc(NULL, 16);\n"
		"	*p++ = f != NULL;\n"
		"	*p++ = malloc(0x100000) == NULL;\n"
		"	free(NULL);\n"
		"	*p++ = abs(-5);\n"
		"	*p++ = abs(5);\n"
		"	*p++ = abs(0);\n"
		"	*p++ = (int)labs(-2147483647L);\n"
		"	*p++ = atoi(\"  -12abc\");\n"
		"	*p++ = (int)atol(\"2147483647\");\n"
		"	*p++ = atoi(\"\");\n"
		"	return 0;\n"
		"}\n"));
	AssertTrue(TestLibc65Run(&sRun, 2000000));

	for (i = 0; i < 10; i++)
	{
		AssertInt(1, TestLibc65Result(&sRun, i));
	}
	AssertInt(5, TestLibc65Result(&sRun, 10));
	AssertInt(5, TestLibc65Result(&sRun, 11));
	AssertInt(0, TestLibc65Result(&sRun, 12));
	AssertInt(2147483647, TestLibc65Result(&sRun, 13));
	AssertInt(-12, TestLibc65Result(&sRun, 14));
	AssertInt(2147483647, TestLibc65Result(&sRun, 15));
	AssertInt(0, TestLibc65Result(&sRun, 16));

	TestLibc65End(&sRun);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestLibc65StdlibAllocationOverflow(void)
{
	static const char*	aszUnits[] = { "stdlib.cpp", "string.cpp", "string.asm", "ctype.cpp", NULL };
	STestLibc65Run		sRun;
	size				i;

	//Sizes whose rounding or header, or count times size, don't fit in a size_t must fail, not wrap to a small
	//block.
	AssertTrue(TestLibc65Begin(&sRun, aszUnits, "",
		"#include <stdlib.h>\n"
		"int main()\n"
		"{\n"
		"	int*	p;\n"
		"	char*	pc;\n"
		"	p = (int*)0x100000;\n"
		"	*p++ = malloc(0xFFFFFFFD) == NULL;\n"
		"	*p++ = malloc(0xFFFFFFF8) == NULL;\n"
		"	*p++ = malloc(0x7FFFFFFF) == NULL;\n"
		"	*p++ = calloc(0x10000, 0x10001) == NULL;\n"
		"	*p++ = calloc(0x40000001, 4) == NULL;\n"
		"	*p++ = realloc(NULL, 0xFFFFFFFD) == NULL;\n"
		"	pc = (char*)malloc(16);\n"
		"	*p++ = pc != NULL;\n"
		"	*p++ = realloc(pc, 0xFFFFFFFD) == NULL;\n"
		"	return 0;\n"
		"}\n"));
	AssertTrue(TestLibc65Run(&sRun, 2000000));

	for (i = 0; i < 8; i++)
	{
		AssertInt(1, TestLibc65Result(&sRun, i));
	}

	TestLibc65End(&sRun);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestLibc65StdlibFragmentation(void)
{
	static const char*	aszUnits[] = { "stdlib.cpp", "string.cpp", "string.asm", "ctype.cpp", NULL };
	STestLibc65Run		sRun;

	//Only one block is ever allocated, each a little bigger than the last, so the 512KB heap must not run out.
	//Freed neighbours have to be joined (or the top of the heap given back) for that.
	AssertTrue(TestLibc65Begin(&sRun, aszUnits, "",
		"#include <stdlib.h>\n"
		"int main()\n"
		"{\n"
		"	int*	p;\n"
		"	char*	pc;\n"
		"	int		iFailed;\n"
		"	p = (int*)0x100000;\n"
		"	iFailed = 0;\n"
		"	for (int i = 0; i < 400; i++)\n"
		"	{\n"
		"		pc = (char*)malloc(64 + 8 * i);\n"
		"		if (pc == NULL)\n"
		"		{\n"
		"			iFailed++;\n"
		"		}\n"
		"		free(pc);\n"
		"	}\n"
		"	*p++ = iFailed;\n"
		"	iFailed = 0;\n"
		"	for (int i = 0; i < 2000; i++)\n"
		"	{\n"
		"		pc = (char*)malloc(1000);\n"
		"		if (pc == NULL)\n"
		"		{\n"
		"			iFailed++;\n"
		"		}\n"
		"		free(pc);\n"
		"	}\n"
		"	*p++ = iFailed;\n"
		"	return 0;\n"
		"}\n"));
	AssertTrue(TestLibc65Run(&sRun, 20000000));

	AssertInt(0, TestLibc65Result(&sRun, 0));
	AssertInt(0, TestLibc65Result(&sRun, 1));

	TestLibc65End(&sRun);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestLibc65StdlibExit(void)
{
	static const char*	aszUnits[] = { "stdlib.cpp", "string.cpp", "string.asm", "ctype.cpp", NULL };
	STestLibc65Run		sRun;

	//exit stops the program as returning from main would: the destructors of globals run and the status is
	//what main would have returned.  Nothing after the call to exit runs.  gsFinal is only there for its
	//destructor, so it is marked used (the linker leaves out globals nothing uses).
	AssertTrue(TestLibc65Begin(&sRun, aszUnits, "",
		"#include <stdlib.h>\n"
		"struct SFinal\n"
		"{\n"
		"	~SFinal()\n"
		"	{\n"
		"		*(int*)0x100004 = 99;\n"
		"	}\n"
		"};\n"
		"SFinal gsFinal __attribute__((used));\n"
		"void Deep(int i)\n"
		"{\n"
		"	if (i == 0)\n"
		"	{\n"
		"		exit(3);\n"
		"	}\n"
		"	Deep(i - 1);\n"
		"	*(int*)0x100008 = 1;\n"
		"}\n"
		"int main()\n"
		"{\n"
		"	*(int*)0x100000 = 1;\n"
		"	Deep(5);\n"
		"	*(int*)0x100000 = 2;\n"
		"	return 7;\n"
		"}\n"));
	AssertTrue(TestLibc65RunToStop(&sRun, 2000000));

	AssertInt(3, TestLibc65Return(&sRun));
	AssertInt(1, TestLibc65Result(&sRun, 0));
	AssertInt(99, TestLibc65Result(&sRun, 1));
	AssertInt(0, TestLibc65Result(&sRun, 2));

	TestLibc65End(&sRun);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestLibc65StdlibUnderscoreExit(void)
{
	static const char*	aszUnits[] = { "stdlib.cpp", "string.cpp", "string.asm", "ctype.cpp", NULL };
	STestLibc65Run		sRun;

	//_Exit stops at once with the status: the destructors of globals don't run.  gsFinal is marked used so
	//it is linked.
	AssertTrue(TestLibc65Begin(&sRun, aszUnits, "",
		"#include <stdlib.h>\n"
		"struct SFinal\n"
		"{\n"
		"	~SFinal()\n"
		"	{\n"
		"		*(int*)0x100004 = 99;\n"
		"	}\n"
		"};\n"
		"SFinal gsFinal __attribute__((used));\n"
		"int main()\n"
		"{\n"
		"	*(int*)0x100000 = 1;\n"
		"	_Exit(4);\n"
		"	*(int*)0x100000 = 2;\n"
		"	return 7;\n"
		"}\n"));
	AssertTrue(TestLibc65RunToStop(&sRun, 2000000));

	AssertInt(4, TestLibc65Return(&sRun));
	AssertInt(1, TestLibc65Result(&sRun, 0));
	AssertInt(0, TestLibc65Result(&sRun, 1));

	TestLibc65End(&sRun);
}



//////////////////////////////////////////////////////////////////////////
//
// A program that logs at 0010:0000 onwards: main logs 0, the atexit functions 1 and 2, gsFinal's destructor 9.
// main ends with szEnd.
//
//////////////////////////////////////////////////////////////////////////
static void TestLibc65StdlibAtExitProgram(STestLibc65Run* psRun, const char* szEnd)
{
	static const char*	aszUnits[] = { "stdlib.cpp", "string.cpp", "string.asm", "ctype.cpp", NULL };
	CChars				szSource;

	szSource.Init(
		"#include <stdlib.h>\n"
		"int giNext;\n"
		"void Log(int i)\n"
		"{\n"
		"	((int*)0x100000)[giNext] = i;\n"
		"	giNext++;\n"
		"}\n"
		"struct SFinal\n"
		"{\n"
		"	~SFinal()\n"
		"	{\n"
		"		Log(9);\n"
		"	}\n"
		"};\n"
		"SFinal gsFinal __attribute__((used));\n"
		"void First() { Log(1); }\n"
		"void Second() { Log(2); }\n"
		"int main()\n"
		"{\n"
		"	if (atexit(First) != 0) return 10;\n"
		"	if (atexit(Second) != 0) return 11;\n"
		"	Log(0);\n");
	szSource.Append(szEnd);
	szSource.Append("}\n");
	AssertTrue(TestLibc65Begin(psRun, aszUnits, "", szSource.Text()));
	szSource.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// main logged 0, then the atexit functions ran last first (2 and 1), then gsFinal's destructor (9).
//
//////////////////////////////////////////////////////////////////////////
static void TestLibc65StdlibAssertExitLog(STestLibc65Run* psRun)
{
	AssertInt(0, TestLibc65Result(psRun, 0));
	AssertInt(2, TestLibc65Result(psRun, 1));
	AssertInt(1, TestLibc65Result(psRun, 2));
	AssertInt(9, TestLibc65Result(psRun, 3));
}


//////////////////////////////////////////////////////////////////////////
//
// The atexit functions run last first, before the destructors of globals, when main returns and when exit is
// called; _Exit runs neither.  At most 32 functions can be registered.
//
//////////////////////////////////////////////////////////////////////////
void TestLibc65StdlibAtExit(void)
{
	static const char*	aszUnits[] = { "stdlib.cpp", "string.cpp", "string.asm", "ctype.cpp", NULL };
	STestLibc65Run		sRun;

	TestLibc65StdlibAtExitProgram(&sRun, "	return 5;\n");
	AssertTrue(TestLibc65Run(&sRun, 2000000));
	AssertInt(5, TestLibc65Return(&sRun));
	TestLibc65StdlibAssertExitLog(&sRun);
	TestLibc65End(&sRun);

	TestLibc65StdlibAtExitProgram(&sRun, "	exit(6);\n	return 5;\n");
	AssertTrue(TestLibc65RunToStop(&sRun, 2000000));
	AssertInt(6, TestLibc65Return(&sRun));
	TestLibc65StdlibAssertExitLog(&sRun);
	TestLibc65End(&sRun);

	TestLibc65StdlibAtExitProgram(&sRun, "	_Exit(4);\n	return 5;\n");
	AssertTrue(TestLibc65RunToStop(&sRun, 2000000));
	AssertInt(4, TestLibc65Return(&sRun));
	AssertInt(0, TestLibc65Result(&sRun, 0));
	AssertInt(0, TestLibc65Result(&sRun, 1));
	TestLibc65End(&sRun);

	AssertTrue(TestLibc65Begin(&sRun, aszUnits, "",
		"#include <stdlib.h>\n"
		"int giCount;\n"
		"void Count() { giCount++; *(int*)0x100000 = giCount; }\n"
		"int main()\n"
		"{\n"
		"	for (int i = 0; i < 32; i++)\n"
		"	{\n"
		"		if (atexit(Count) != 0) return 1;\n"
		"	}\n"
		"	if (atexit(Count) != -1) return 2;\n"
		"	return 0;\n"
		"}\n"));
	AssertTrue(TestLibc65Run(&sRun, 2000000));
	AssertInt(0, TestLibc65Return(&sRun));
	AssertInt(32, TestLibc65Result(&sRun, 0));
	TestLibc65End(&sRun);
}


//////////////////////////////////////////////////////////////////////////
//
// abort stops at once with EXIT_FAILURE: neither the atexit functions nor the destructors of globals run.
//
//////////////////////////////////////////////////////////////////////////
void TestLibc65StdlibAbort(void)
{
	STestLibc65Run	sRun;

	TestLibc65StdlibAtExitProgram(&sRun, "	abort();\n	return 5;\n");
	AssertTrue(TestLibc65RunToStop(&sRun, 2000000));
	AssertInt(1, TestLibc65Return(&sRun));
	AssertInt(0, TestLibc65Result(&sRun, 0));
	AssertInt(0, TestLibc65Result(&sRun, 1));
	TestLibc65End(&sRun);
}


//////////////////////////////////////////////////////////////////////////
//
// signal and raise (signal.cpp): a handler is called once (it is reset to SIG_DFL),
// an ignored signal does nothing, a signal without a handler stops the program like
// abort, and bad signal numbers fail.  errno is a global starting at 0.
//
//////////////////////////////////////////////////////////////////////////
void TestLibc65StdlibSignal(void)
{
	static const char*	aszUnits[] = { "stdlib.cpp", "string.cpp", "string.asm", "ctype.cpp", "signal.cpp", NULL };
	STestLibc65Run		sRun;

	AssertTrue(TestLibc65Begin(&sRun, aszUnits, "",
		"#include <signal.h>\n"
		"#include <errno.h>\n"
		"int giSeen;\n"
		"void Handle(int iSignal) { giSeen = giSeen * 100 + iSignal; }\n"
		"int main()\n"
		"{\n"
		"	if (errno != 0) return 1;\n"
		"	errno = ERANGE;\n"
		"	if (signal(SIGINT, Handle) != SIG_DFL) return 2;\n"
		"	if (raise(SIGINT) != 0) return 3;\n"
		"	if (signal(SIGINT, SIG_IGN) != SIG_DFL) return 4;\n"
		"	if (raise(SIGINT) != 0) return 5;\n"
		"	if ((signal(0, Handle) != SIG_ERR) || (raise(99) != -1)) return 6;\n"
		"	signal(SIGTERM, Handle);\n"
		"	raise(SIGTERM);\n"
		"	if ((giSeen != 215) || (errno != ERANGE)) return 7;\n"
		"	raise(SIGABRT);\n"
		"	return 8;\n"
		"}\n"));
	AssertTrue(TestLibc65RunToStop(&sRun, 2000000));
	AssertInt(1, TestLibc65Return(&sRun));
	TestLibc65End(&sRun);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestLibc65Stdlib(void)
{
	BeginTests();

	TestLibc65StdlibAllocation();
	TestLibc65StdlibAllocationOverflow();
	TestLibc65StdlibFragmentation();
	TestLibc65StdlibExit();
	TestLibc65StdlibUnderscoreExit();
	TestLibc65StdlibAtExit();
	TestLibc65StdlibAbort();
	TestLibc65StdlibSignal();
	TestLibc65StdlibQsort();
	TestLibc65StdlibRand();
	TestLibc65StdlibStrtol();
	TestLibc65StdlibStrtoul();

	TestStatistics();
}

