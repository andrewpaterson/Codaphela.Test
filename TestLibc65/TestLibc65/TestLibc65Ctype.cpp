#include <ctype.h>
#include "TestLib/Assert.h"
#include "TestLibc65Context.h"


//////////////////////////////////////////////////////////////////////////
//
// Each classification of c as a bit, in the order the test program packs them.
//
//////////////////////////////////////////////////////////////////////////
static int32 TestLibc65CtypeBits(int c)
{
	return	((isalnum(c) != 0) << 0) |
			((isalpha(c) != 0) << 1) |
			((isblank(c) != 0) << 2) |
			((iscntrl(c) != 0) << 3) |
			((isdigit(c) != 0) << 4) |
			((isgraph(c) != 0) << 5) |
			((islower(c) != 0) << 6) |
			((isprint(c) != 0) << 7) |
			((ispunct(c) != 0) << 8) |
			((isspace(c) != 0) << 9) |
			((isupper(c) != 0) << 10) |
			((isxdigit(c) != 0) << 11);
}


//////////////////////////////////////////////////////////////////////////
//
// ctype.h for EOF and every unsigned char against the host's "C" locale.
//
//////////////////////////////////////////////////////////////////////////
void TestLibc65CtypeAll(void)
{
	static const char*	aszUnits[] = { "ctype.cpp", NULL };
	STestLibc65Run		sRun;
	int					c;
	size				i;

	AssertTrue(TestLibc65Begin(&sRun, aszUnits, "",
		"#include <ctype.h>\n"
		"int main()\n"
		"{\n"
		"	int*	p;\n"
		"	p = (int*)0x100000;\n"
		"	for (int c = -1; c < 256; c++)\n"
		"	{\n"
		"		*p++ =	((isalnum(c) != 0) << 0) |\n"
		"				((isalpha(c) != 0) << 1) |\n"
		"				((isblank(c) != 0) << 2) |\n"
		"				((iscntrl(c) != 0) << 3) |\n"
		"				((isdigit(c) != 0) << 4) |\n"
		"				((isgraph(c) != 0) << 5) |\n"
		"				((islower(c) != 0) << 6) |\n"
		"				((isprint(c) != 0) << 7) |\n"
		"				((ispunct(c) != 0) << 8) |\n"
		"				((isspace(c) != 0) << 9) |\n"
		"				((isupper(c) != 0) << 10) |\n"
		"				((isxdigit(c) != 0) << 11);\n"
		"		*p++ = tolower(c);\n"
		"		*p++ = toupper(c);\n"
		"	}\n"
		"	return 0;\n"
		"}\n"));
	AssertTrue(TestLibc65Run(&sRun, 2000000));
	AssertInt(0, TestLibc65Return(&sRun));

	i = 0;
	for (c = -1; c < 256; c++)
	{
		AssertInt(TestLibc65CtypeBits(c), TestLibc65Result(&sRun, i));
		AssertInt(tolower(c), TestLibc65Result(&sRun, i + 1));
		AssertInt(toupper(c), TestLibc65Result(&sRun, i + 2));
		i += 3;
	}

	TestLibc65End(&sRun);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestLibc65Ctype(void)
{
	BeginTests();

	TestLibc65CtypeAll();

	TestStatistics();
}

