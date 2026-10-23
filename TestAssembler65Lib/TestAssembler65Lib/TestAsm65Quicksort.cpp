#include <stdlib.h>
#include "BaseLib/Chars.h"
#include "TestLib/Assert.h"
#include "TestAsm65Context.h"


#define QUICKSORT_DATA	0x4000
#define QUICKSORT_COUNT	256
#define QUICKSORT_SEED	12345


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
static int CompareUint32(const void* pv1, const void* pv2)
{
	uint32	ui1;
	uint32	ui2;

	ui1 = *(const uint32*)pv1;
	ui2 = *(const uint32*)pv2;
	return (ui1 < ui2) ? -1 : ((ui1 > ui2) ? 1 : 0);
}


//////////////////////////////////////////////////////////////////////////
//
// The program's values sorted by qsort.
//
//////////////////////////////////////////////////////////////////////////
static void AssertQuicksort(uint32 uiMask)
{
	STestAsm65Run	sRun;
	CChars			szSource;
	uint32			auiExpected[QUICKSORT_COUNT];
	uint32			x;
	int				i;
	int				iDifferent;

	x = QUICKSORT_SEED;
	for (i = 0; i < QUICKSORT_COUNT; i++)
	{
		x = x * 1664525 + 1013904223;
		auiExpected[i] = x & uiMask;
	}
	qsort(auiExpected, QUICKSORT_COUNT, sizeof(uint32), CompareUint32);

	szSource.Init("COUNT = ");
	szSource.Append(QUICKSORT_COUNT);
	szSource.Append("\nSEED = ");
	szSource.Append(QUICKSORT_SEED);
	szSource.Append("\nMASK = ");
	szSource.Append(uiMask);
	szSource.AppendNewLine();
	TestAsm65ReadSource(&szSource, "Quicksort.asm");
	AssertTrue(TestAsm65Begin(&sRun, szSource.Text(), 0x1000));
	AssertTrue(TestAsm65Run(&sRun, 1000000) < 1000000);

	iDifferent = 0;
	for (i = 0; i < QUICKSORT_COUNT; i++)
	{
		if (sRun.pcContext->GetLong(QUICKSORT_DATA + 4 * i) != auiExpected[i])
		{
			iDifferent++;
		}
	}
	AssertInt(0, iDifferent);
	AssertIntHex(0x0001FFFF, TestAsm65MPU(&sRun)->GetS());

	TestAsm65End(&sRun);
	szSource.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// 32 bit values, then values from 0 to 15 (many the same).
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65QuicksortValues(void)
{
	AssertQuicksort(0xFFFFFFFF);
	AssertQuicksort(15);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65Quicksort(void)
{
	BeginTests();

	TestAsm65QuicksortValues();

	TestStatistics();
}
