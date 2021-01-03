#include "stdio.h"
#include "BaseLib/FastFunctions.h"
#include "BaseLib/Define.h"
#include "BaseLib/TypeConverter.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void SetupTestMemory(char* pc1, char* pc2)
{
	int		i;

	for (i = 0; i < 1024; i++)
	{
		pc1[i] = (char)i;
		pc2[i] = 0;
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMemcpyFast(void)
{
	char	pc1[1024];
	char	pc2[1024];
	int		i;

	SetupTestMemory(pc1, pc2);
	memcpy_fast_1byte(pc2, pc1);
	AssertMemory(pc1, pc2, 1);

	ga_memcpy_fast[0](pc1, pc2);

	for (i = 0; i <= 64; i++)
	{
		SetupTestMemory(pc1, pc2);
		ga_memcpy_fast[i](pc2, pc1);
		AssertMemory(pc1, pc2, i);
		AssertZero(&((char*)pc2)[i], 64-i);
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMemcmpFast(void)
{
	char	pc1[1024];
	char	pc2[1024];
	int		i;
	int		iResult;
	char	sz1[] = "16";
	char	sz2[] = "84";

	memset(pc1, 0, 1024);
	memset(pc2, 1, 1024);

	iResult = memcmp_fast_2bytes(sz1, sz2);
	AssertNegative(iResult);
	iResult = memcmp(sz1, sz2, 2);
	AssertNegative(iResult);

	for (i = 1; i < 16; i++)
	{
		iResult = ga_memcmp_fast[i](pc2, pc1);
		AssertPositive(iResult);
	}
	for (i = 1; i < 16; i++)
	{
		iResult = ga_memcmp_fast[i](pc1, pc2);
		AssertNegative(iResult);
	}
	for (i = 1; i < 16; i++)
	{
		iResult = ga_memcmp_fast[i](pc2, pc2);
		AssertZero(&iResult, 4);
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFastFunctions(void)
{
	BeginTests();

	FastFunctionsInit();
	TypeConverterInit();

	TestMemcpyFast();
	TestMemcmpFast();

	FastFunctionsKill();
	TypeConverterKill();

	TestStatistics();
}


