#include "TestLib/Assert.h"
#include "BaseLib/IntegerHelper.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestBitFunctions(void)
{
	char	c[8];

	memset(c, 0, 8);

	SetBit(1, c, 1);
	AssertChar(c[0], 2);
	SetBit(7, c, 1);
	AssertChar(c[0], -126);
	SetBit(8, c, 1);
	AssertChar(c[1], 1);

	c[0] = 5;
	AssertBool(TRUE, GetBit(0, &c));
	AssertBool(FALSE, GetBit(1, &c));
	AssertBool(TRUE, GetBit(2, &c));

	AssertInt(1, FindFirstClearBit(c, 8*8));
	AssertInt(0, FindFirstSetBit(c, 8*8));
	c[0] = 4;
	AssertInt(0, FindFirstClearBit(c, 8*8));
	AssertInt(2, FindFirstSetBit(c, 8*8));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMisc(void)
{
	AssertInt(4, GetLogBase2(16));
	AssertInt(4, GetLogBase2(31));
	AssertInt(5, GetLogBase2(32));
	AssertInt(5, GetLogBase2(63));

	AssertInt(1024, TruncateLowBits(1024));
	AssertInt(1024, TruncateLowBits(1025));
	AssertInt(1024, TruncateLowBits(2047));
	AssertInt(1, TruncateLowBits(1));
	AssertInt(0, TruncateLowBits(0));

	AssertInt(1024, GetBestHighBit(1023));
	AssertInt(1024, GetBestHighBit(1024));
	AssertInt(2048, GetBestHighBit(1025));
	AssertInt(2048, GetBestHighBit(2047));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIntegerHelper(void)
{
	BeginTests();

	TestBitFunctions();
	TestMisc();

	TestStatistics();
}

