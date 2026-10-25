#include "TestLib/Assert.h"
#include "TestLibc65Context.h"


//////////////////////////////////////////////////////////////////////////
//
// va_start, va_arg, va_copy and va_end over ints, the arguments promoted to int, long longs and pointers.
//
//////////////////////////////////////////////////////////////////////////
void TestLibc65StdargArguments(void)
{
	static const char*	aszUnits[] = { NULL };
	static const int32	aiExpected[] =
	{
		0, 6, 1104,								//SumInts
		-5, -300, 1, 200,						//char, short, bool and unsigned char are promoted to int
		0x23456789, 0x1, 42, -2, -1,			//long long, int, long long
		'h', 7, 'w',							//pointers
		(int32)0xFFFFFFFF, 2000000000,			//unsigned int
		12, 12,									//va_copy reads the same arguments again
	};
	STestLibc65Run		sRun;
	size				i;

	AssertTrue(TestLibc65Begin(&sRun, aszUnits, "",
		"#include <stdarg.h>\n"
		"long* gp;\n"
		"int SumInts(int iCount, ...)\n"
		"{\n"
		"	va_list	ap;\n"
		"	int		iSum;\n"
		"	iSum = 0;\n"
		"	va_start(ap, iCount);\n"
		"	for (int i = 0; i < iCount; i++)\n"
		"	{\n"
		"		iSum += va_arg(ap, int);\n"
		"	}\n"
		"	va_end(ap);\n"
		"	return iSum;\n"
		"}\n"
		"void Record(const char* szTypes, ...)\n"
		"{\n"
		"	va_list		ap;\n"
		"	long long	ll;\n"
		"	const char*	sz;\n"
		"	va_start(ap, szTypes);\n"
		"	for (const char* pc = szTypes; *pc; pc++)\n"
		"	{\n"
		"		if (*pc == 'i')\n"
		"		{\n"
		"			*gp++ = va_arg(ap, int);\n"
		"		}\n"
		"		else if (*pc == 'u')\n"
		"		{\n"
		"			*gp++ = (long)va_arg(ap, unsigned long);\n"
		"		}\n"
		"		else if (*pc == 'l')\n"
		"		{\n"
		"			ll = va_arg(ap, long long);\n"
		"			*gp++ = (long)ll;\n"
		"			*gp++ = (long)(ll >> 32);\n"
		"		}\n"
		"		else if (*pc == 'p')\n"
		"		{\n"
		"			sz = va_arg(ap, const char*);\n"
		"			*gp++ = sz[0];\n"
		"		}\n"
		"	}\n"
		"	va_end(ap);\n"
		"}\n"
		"void Twice(int iCount, ...)\n"
		"{\n"
		"	va_list	ap;\n"
		"	va_list	apCopy;\n"
		"	int		iSum;\n"
		"	va_start(ap, iCount);\n"
		"	va_copy(apCopy, ap);\n"
		"	iSum = 0;\n"
		"	for (int i = 0; i < iCount; i++)\n"
		"	{\n"
		"		iSum += va_arg(ap, int);\n"
		"	}\n"
		"	*gp++ = iSum;\n"
		"	iSum = 0;\n"
		"	for (int i = 0; i < iCount; i++)\n"
		"	{\n"
		"		iSum += va_arg(apCopy, int);\n"
		"	}\n"
		"	*gp++ = iSum;\n"
		"	va_end(apCopy);\n"
		"	va_end(ap);\n"
		"}\n"
		"int main()\n"
		"{\n"
		"	char			c;\n"
		"	short			s;\n"
		"	bool			b;\n"
		"	unsigned char	uc;\n"
		"	gp = (long*)0x100000;\n"
		"	*gp++ = SumInts(0);\n"
		"	*gp++ = SumInts(3, 1, 2, 3);\n"
		"	*gp++ = SumInts(5, -1, -2, 100, 1000, 7);\n"
		"	c = -5;\n"
		"	s = -300;\n"
		"	b = true;\n"
		"	uc = 200;\n"
		"	Record(\"iiii\", c, s, b, uc);\n"
		"	Record(\"lil\", 0x123456789LL, 42, -2LL);\n"
		"	Record(\"pip\", \"hello\", 7, \"world\");\n"
		"	Record(\"uu\", 0xFFFFFFFFUL, 2000000000UL);\n"
		"	Twice(3, 3, 4, 5);\n"
		"	return 0;\n"
		"}\n"));
	AssertTrue(TestLibc65Run(&sRun, 2000000));

	for (i = 0; i < sizeof(aiExpected) / sizeof(int32); i++)
	{
		AssertInt(aiExpected[i], TestLibc65Result(&sRun, i));
	}

	TestLibc65End(&sRun);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestLibc65Stdarg(void)
{
	BeginTests();

	TestLibc65StdargArguments();

	TestStatistics();
}

