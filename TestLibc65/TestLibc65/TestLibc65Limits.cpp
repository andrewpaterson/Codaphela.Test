#include "TestLib/Assert.h"
#include "TestLibc65Context.h"


//////////////////////////////////////////////////////////////////////////
//
// The sizes the 65C64's headers promise: char 8 bits, short 16, int and long 32, long long 64, pointers 32.
//
//////////////////////////////////////////////////////////////////////////
void TestLibc65LimitsSizes(void)
{
	static const char*	aszUnits[] = { NULL };
	static const int32	aiExpected[] =
	{
		1, 2, 4, 4, 8, 4, 4, 4, 4, 1,			//char short int long, long long, void* size_t ptrdiff_t float bool
		1, 2, 4, 8, 1, 2, 4, 8,					//int8_t to int64_t, uint8_t to uint64_t
		4, 4, 8, 8,								//intptr_t uintptr_t intmax_t uintmax_t
		8, 8, 4,								//INT64_C, UINT64_C, UINT32_C
	};
	STestLibc65Run		sRun;
	size				i;

	AssertTrue(TestLibc65Begin(&sRun, aszUnits, "",
		"#include <stddef.h>\n"
		"#include <stdint.h>\n"
		"int main()\n"
		"{\n"
		"	int* p = (int*)0x100000;\n"
		"	*p++ = sizeof(char);\n"
		"	*p++ = sizeof(short);\n"
		"	*p++ = sizeof(int);\n"
		"	*p++ = sizeof(long);\n"
		"	*p++ = sizeof(long long);\n"
		"	*p++ = sizeof(void*);\n"
		"	*p++ = sizeof(size_t);\n"
		"	*p++ = sizeof(ptrdiff_t);\n"
		"	*p++ = sizeof(float);\n"
		"	*p++ = sizeof(bool);\n"
		"	*p++ = sizeof(int8_t);\n"
		"	*p++ = sizeof(int16_t);\n"
		"	*p++ = sizeof(int32_t);\n"
		"	*p++ = sizeof(int64_t);\n"
		"	*p++ = sizeof(uint8_t);\n"
		"	*p++ = sizeof(uint16_t);\n"
		"	*p++ = sizeof(uint32_t);\n"
		"	*p++ = sizeof(uint64_t);\n"
		"	*p++ = sizeof(intptr_t);\n"
		"	*p++ = sizeof(uintptr_t);\n"
		"	*p++ = sizeof(intmax_t);\n"
		"	*p++ = sizeof(uintmax_t);\n"
		"	*p++ = sizeof(INT64_C(5));\n"
		"	*p++ = sizeof(UINT64_C(5));\n"
		"	*p++ = sizeof(UINT32_C(5));\n"
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
// The limits' values, and that the types really wrap at them.
//
//////////////////////////////////////////////////////////////////////////
void TestLibc65LimitsValues(void)
{
	static const char*	aszUnits[] = { NULL };
	static const int32	aiExpected[] =
	{
		8, -128, 127, 255, -128, 127,							//CHAR_BIT SCHAR_MIN SCHAR_MAX UCHAR_MAX CHAR_MIN CHAR_MAX
		-32768, 32767, 65535,									//SHRT_MIN SHRT_MAX USHRT_MAX
		(int32)0x80000000, 0x7FFFFFFF, (int32)0xFFFFFFFF,		//INT_MIN INT_MAX UINT_MAX
		(int32)0x80000000, 0x7FFFFFFF, (int32)0xFFFFFFFF,		//LONG_MIN LONG_MAX ULONG_MAX
		0, (int32)0x80000000, -1, 0x7FFFFFFF, -1, -1,			//LLONG_MIN LLONG_MAX ULLONG_MAX, low then high
		-128, 127, 255, -32768, 32767, 65535,					//INT8_MIN INT8_MAX UINT8_MAX INT16_MIN INT16_MAX UINT16_MAX
		(int32)0x80000000, 0x7FFFFFFF, (int32)0xFFFFFFFF,		//INT32_MIN INT32_MAX UINT32_MAX
		0, (int32)0x80000000, -1, 0x7FFFFFFF, -1, -1,			//INT64_MIN INT64_MAX UINT64_MAX, low then high
		(int32)0xFFFFFFFF, 0x7FFFFFFF, (int32)0x80000000,		//SIZE_MAX PTRDIFF_MAX PTRDIFF_MIN
		1, 1, 1, 1, 1, 1, 1, 1,									//wrapping
	};
	STestLibc65Run		sRun;
	size				i;

	AssertTrue(TestLibc65Begin(&sRun, aszUnits, "",
		"#include <limits.h>\n"
		"#include <stdint.h>\n"
		"int* gp;\n"
		"void Long(long long ll)\n"
		"{\n"
		"	*gp++ = (int)ll;\n"
		"	*gp++ = (int)(ll >> 32);\n"
		"}\n"
		"int main()\n"
		"{\n"
		"	char			c;\n"
		"	unsigned char	uc;\n"
		"	short			s;\n"
		"	unsigned short	us;\n"
		"	int8_t			i8;\n"
		"	uint16_t		u16;\n"
		"	unsigned int	ui;\n"
		"	unsigned long long	ull;\n"
		"	gp = (int*)0x100000;\n"
		"	*gp++ = CHAR_BIT;\n"
		"	*gp++ = SCHAR_MIN;\n"
		"	*gp++ = SCHAR_MAX;\n"
		"	*gp++ = UCHAR_MAX;\n"
		"	*gp++ = CHAR_MIN;\n"
		"	*gp++ = CHAR_MAX;\n"
		"	*gp++ = SHRT_MIN;\n"
		"	*gp++ = SHRT_MAX;\n"
		"	*gp++ = USHRT_MAX;\n"
		"	*gp++ = INT_MIN;\n"
		"	*gp++ = INT_MAX;\n"
		"	*gp++ = (int)UINT_MAX;\n"
		"	*gp++ = (int)LONG_MIN;\n"
		"	*gp++ = (int)LONG_MAX;\n"
		"	*gp++ = (int)ULONG_MAX;\n"
		"	Long(LLONG_MIN);\n"
		"	Long(LLONG_MAX);\n"
		"	Long((long long)ULLONG_MAX);\n"
		"	*gp++ = INT8_MIN;\n"
		"	*gp++ = INT8_MAX;\n"
		"	*gp++ = UINT8_MAX;\n"
		"	*gp++ = INT16_MIN;\n"
		"	*gp++ = INT16_MAX;\n"
		"	*gp++ = UINT16_MAX;\n"
		"	*gp++ = INT32_MIN;\n"
		"	*gp++ = INT32_MAX;\n"
		"	*gp++ = (int)UINT32_MAX;\n"
		"	Long(INT64_MIN);\n"
		"	Long(INT64_MAX);\n"
		"	Long((long long)UINT64_MAX);\n"
		"	*gp++ = (int)SIZE_MAX;\n"
		"	*gp++ = PTRDIFF_MAX;\n"
		"	*gp++ = PTRDIFF_MIN;\n"
		"	c = (char)200;\n"
		"	*gp++ = (c < 0) == (CHAR_MIN < 0);\n"
		"	uc = UCHAR_MAX;\n"
		"	uc++;\n"
		"	*gp++ = uc == 0;\n"
		"	s = SHRT_MAX;\n"
		"	s = (short)(s + 1);\n"
		"	*gp++ = s == SHRT_MIN;\n"
		"	us = USHRT_MAX;\n"
		"	us++;\n"
		"	*gp++ = us == 0;\n"
		"	i8 = (int8_t)(INT8_MAX + 1);\n"
		"	*gp++ = i8 == INT8_MIN;\n"
		"	u16 = (uint16_t)(UINT16_MAX + 1);\n"
		"	*gp++ = u16 == 0;\n"
		"	ui = UINT_MAX;\n"
		"	*gp++ = ui + 1 == 0;\n"
		"	ull = ULLONG_MAX;\n"
		"	*gp++ = ull + 1 == 0;\n"
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
void TestLibc65Limits(void)
{
	BeginTests();

	TestLibc65LimitsSizes();
	TestLibc65LimitsValues();

	TestStatistics();
}

