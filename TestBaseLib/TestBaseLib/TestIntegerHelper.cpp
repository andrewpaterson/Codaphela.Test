#include "BaseLib/IntegerHelper.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIntegerHelperFindFirstClearBit(void)
{
	uint8	ab[9];
	int		iIndex;
	int		iBit;

	ab[0] = ab[1] = ab[2] = ab[3] = ab[4] = ab[5] = ab[6] = ab[7] = ab[8] = 0xff;
	iIndex = FindFirstClearBit(ab, 64);
	AssertInt(-1, iIndex);
	
	ab[7] = 0xfe;
	iIndex = FindFirstClearBit(ab, 64);
	AssertInt(56, iIndex);
	ab[7] = 0x7f;
	iIndex = FindFirstClearBit(ab, 64);
	AssertInt(63, iIndex);

	ab[7] = 0xff;

	for (iBit = 71; iBit >= 0; iBit--)
	{
		SetBit(iBit, ab, false);
		iIndex = FindFirstClearBit(ab, 72);
		AssertInt(iBit, iIndex);
	}

	ab[0] = 0xff;
	iIndex = FindFirstClearBit(ab, 2);
	AssertInt(-1, iIndex);
	ab[0] = 0xfe;
	iIndex = FindFirstClearBit(ab, 2);
	AssertInt(0, iIndex);
	ab[0] = 0xfd;
	iIndex = FindFirstClearBit(ab, 2);
	AssertInt(1, iIndex);
	ab[0] = 0xfc;
	iIndex = FindFirstClearBit(ab, 2);
	AssertInt(0, iIndex);
	ab[0] = 0xfb;
	iIndex = FindFirstClearBit(ab, 2);
	AssertInt(-1, iIndex);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIntegerHelperFindFirstSetBit(void)
{
	uint8	ab[9];
	int		iIndex;
	int		iBit;

	ab[0] = ab[1] = ab[2] = ab[3] = ab[4] = ab[5] = ab[6] = ab[7] = ab[8] = 0;
	iIndex = FindFirstSetBit(ab, 64);
	AssertInt(-1, iIndex);

	ab[0] = 1;
	iIndex = FindFirstSetBit(ab, 64);
	AssertInt(0, iIndex);
	ab[0] = 2;
	iIndex = FindFirstSetBit(ab, 64);
	AssertInt(1, iIndex);
	ab[0] = 4;
	iIndex = FindFirstSetBit(ab, 64);
	AssertInt(2, iIndex);
	ab[0] = 8;
	iIndex = FindFirstSetBit(ab, 64);
	AssertInt(3, iIndex);
	ab[0] = 16;
	iIndex = FindFirstSetBit(ab, 64);
	AssertInt(4, iIndex);
	ab[0] = 32;
	iIndex = FindFirstSetBit(ab, 64);
	AssertInt(5, iIndex);
	ab[0] = 64;
	iIndex = FindFirstSetBit(ab, 64);
	AssertInt(6, iIndex);
	ab[0] = 128;
	iIndex = FindFirstSetBit(ab, 64);
	AssertInt(7, iIndex);
	ab[0] = 0;
	ab[1] = 1;
	iIndex = FindFirstSetBit(ab, 64);
	AssertInt(8, iIndex);
	ab[1] = 2;
	iIndex = FindFirstSetBit(ab, 64);
	AssertInt(9, iIndex);
	
	ab[1] = 0;
	ab[7] = 1;
	iIndex = FindFirstSetBit(ab, 64);
	AssertInt(56, iIndex);
	ab[7] = 0x80;
	iIndex = FindFirstSetBit(ab, 64);
	AssertInt(63, iIndex);

	ab[7] = 0;

	for (iBit = 71; iBit >= 0; iBit--)
	{
		SetBit(iBit, ab, true);
		iIndex = FindFirstSetBit(ab, 72);
		AssertInt(iBit, iIndex);
	}

	ab[0] = 0x00;
	iIndex = FindFirstSetBit(ab, 2);
	AssertInt(-1, iIndex);
	ab[0] = 0x01;
	iIndex = FindFirstSetBit(ab, 2);
	AssertInt(0, iIndex);
	ab[0] = 0x02;
	iIndex = FindFirstSetBit(ab, 2);
	AssertInt(1, iIndex);
	ab[0] = 0x03;
	iIndex = FindFirstSetBit(ab, 2);
	AssertInt(0, iIndex);
	ab[0] = 0x04;
	iIndex = FindFirstSetBit(ab, 2);
	AssertInt(-1, iIndex);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIntegerHelperFindLastClearBit(void)
{
	uint8	ab[9];
	int		iIndex;
	int		iBit;

	ab[0] = ab[1] = ab[2] = ab[3] = ab[4] = ab[5] = ab[6] = ab[7] = ab[8] = 0xff;
	iIndex = FindLastClearBit(ab, 64);
	AssertInt(-1, iIndex);

	ab[0] = 0x7f;
	iIndex = FindLastClearBit(ab, 64);
	AssertInt(7, iIndex);
	ab[0] = 0xfe;
	iIndex = FindLastClearBit(ab, 64);
	AssertInt(0, iIndex);

	ab[0] = 0xff;

	for (iBit = 0; iBit < 72; iBit++)
	{
		SetBit(iBit, ab, false);
		iIndex = FindLastClearBit(ab, 72);
		AssertInt(iBit, iIndex);
	}

	ab[0] = 0xff;
	iIndex = FindLastClearBit(ab, 2);
	AssertInt(-1, iIndex);
	ab[0] = 0xfd;
	iIndex = FindLastClearBit(ab, 2);
	AssertInt(1, iIndex);
	ab[0] = 0xfe;
	iIndex = FindLastClearBit(ab, 2);
	AssertInt(0, iIndex);
	ab[0] = 0xfc;
	iIndex = FindLastClearBit(ab, 2);
	AssertInt(1, iIndex);
	ab[0] = 0xfb;
	iIndex = FindLastClearBit(ab, 2);
	AssertInt(-1, iIndex);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIntegerHelperFindLastSetBit(void)
{
	uint8	ab[9];
	int		iIndex;
	int		iBit;

	ab[0] = ab[1] = ab[2] = ab[3] = ab[4] = ab[5] = ab[6] = ab[7] = ab[8] = 0;
	iIndex = FindLastSetBit(ab, 64);
	AssertInt(-1, iIndex);

	ab[7] = 128;
	iIndex = FindLastSetBit(ab, 64);
	AssertInt(63, iIndex);
	ab[7] = 64;
	iIndex = FindLastSetBit(ab, 64);
	AssertInt(62, iIndex);
	ab[7] = 32;
	iIndex = FindLastSetBit(ab, 64);
	AssertInt(61, iIndex);
	ab[7] = 16;
	iIndex = FindLastSetBit(ab, 64);
	AssertInt(60, iIndex);
	ab[7] = 8;
	iIndex = FindLastSetBit(ab, 64);
	AssertInt(59, iIndex);
	ab[7] = 4;
	iIndex = FindLastSetBit(ab, 64);
	AssertInt(58, iIndex);
	ab[7] = 2;
	iIndex = FindLastSetBit(ab, 64);
	AssertInt(57, iIndex);
	ab[7] = 1;
	iIndex = FindLastSetBit(ab, 64);
	AssertInt(56, iIndex);
	ab[7] = 0;
	ab[6] = 128;
	iIndex = FindLastSetBit(ab, 64);
	AssertInt(55, iIndex);
	ab[6] = 64;
	iIndex = FindLastSetBit(ab, 64);
	AssertInt(54, iIndex);

	ab[6] = 0;
	ab[0] = 128;
	iIndex = FindLastSetBit(ab, 64);
	AssertInt(7, iIndex);
	ab[0] = 2;
	iIndex = FindLastSetBit(ab, 64);
	AssertInt(1, iIndex);
	ab[0] = 1;
	iIndex = FindLastSetBit(ab, 64);
	AssertInt(0, iIndex);

	ab[0] = 0;

	for (iBit = 0; iBit < 72; iBit++)
	{
		SetBit(iBit, ab, true);
		iIndex = FindLastSetBit(ab, 72);
		AssertInt(iBit, iIndex);
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIntegerHelperReverseBytes(void)
{
	char szAuto[9] = "Autobody";
	char szAutoDash[10] = "Auto-Body";
	char szOne[2] = "1";

	ReverseBytes(szAuto, 8);
	AssertString("ydobotuA", szAuto);
	ReverseBytes(szAutoDash, 9);
	AssertString("ydoB-otuA", szAutoDash);
	ReverseBytes(szOne, 1);
	AssertString("1", szOne);
	ReverseBytes(szOne, 0);
	AssertString("1", szOne);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIntegerHelperCountBits(void)
{
	uint8 auc8a[] = { 0x6a, 0x83, 0x5d, 0x16, 0x42, 0x6e, 0x61, 0x80 };
	uint8 auc8b[] = { 0x54, 0xdc, 0x72, 0xf5, 0x78, 0xf9, 0x86, 0xa3 };
	uint8 auc80[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	uint8 auc81[] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };

	AssertInt(26, CountBits(auc8a, 64));
	AssertInt(26, CountBitsSingly(auc8a, 64));
	AssertInt(15, CountBits(auc8a, 32));
	AssertInt(15, CountBitsSingly(auc8a, 32));
	AssertInt(11, CountBits(&(auc8a[4]), 32));
	AssertInt(11, CountBitsSingly(&(auc8a[4]), 32));

	AssertInt(35, CountBits(auc8b, 64));
	AssertInt(35, CountBitsSingly(auc8b, 64));
	AssertInt(18, CountBits(auc8b, 32));
	AssertInt(18, CountBitsSingly(auc8b, 32));
	AssertInt(17, CountBits(&(auc8b[4]), 32));
	AssertInt(17, CountBitsSingly(&(auc8b[4]), 32));

	AssertInt(0, CountBits(auc80, 64));
	AssertInt(0, CountBitsSingly(auc80, 64));
	AssertInt(0, CountBits(auc80, 32));
	AssertInt(0, CountBitsSingly(auc80, 32));
	AssertInt(0, CountBits(&(auc80[4]), 32));
	AssertInt(0, CountBitsSingly(&(auc80[4]), 32));
	AssertInt(0, CountBits(auc80, 8));
	AssertInt(0, CountBits(auc80, 16));

	AssertInt(64, CountBits(auc81, 64));
	AssertInt(64, CountBitsSingly(auc81, 64));
	AssertInt(32, CountBits(auc81, 32));
	AssertInt(32, CountBitsSingly(auc81, 32));
	AssertInt(32, CountBits(&(auc81[4]), 32));
	AssertInt(32, CountBitsSingly(&(auc81[4]), 32));
	AssertInt(8, CountBits(auc81, 8));
	AssertInt(16, CountBits(auc81, 16));

	AssertInt(4, CountBits(auc8a, 8));
	AssertInt(4, CountBitsSingly(auc8a, 8));
	AssertInt(3, CountBits(auc8b, 8));
	AssertInt(3, CountBitsSingly(auc8b, 8));

	AssertInt(7, CountBits(auc8a, 16));
	AssertInt(7, CountBitsSingly(auc8a, 16));
	AssertInt(8, CountBits(&(auc8a[2]), 16));
	AssertInt(8, CountBitsSingly(&(auc8a[2]), 16));
	AssertInt(8, CountBits(auc8b, 16));
	AssertInt(8, CountBitsSingly(auc8b, 16));
	AssertInt(10, CountBits(&(auc8b[2]), 16));
	AssertInt(10, CountBitsSingly(&(auc8b[2]), 16));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIntegerHelperFindNextSetBit(void)
{
	uint8	ab[9];
	int		iBit;

	ab[0] = ab[1] = ab[2] = ab[3] = ab[4] = ab[5] = ab[6] = ab[7] = ab[8] = 0xff;
	ab[1] = 0b1110'1111;

	iBit = FindFirstClearBit(ab, 64);
	AssertInt(12, iBit);

	iBit = FindNextSetBit(ab, 64, iBit);
	AssertInt(13, iBit);

	iBit = FindFirstClearBit(&ab[1], 63);
	AssertInt(4, iBit);

	iBit = FindNextSetBit(&ab[1], 63, iBit);
	AssertInt(5, iBit);

	ab[0] = 0b1000'0000;
	iBit = FindFirstSetBit(ab, 7);
	AssertInt(-1, iBit);

	iBit = FindNextSetBit(ab, 7, 1);
	AssertInt(-1, iBit);

	ab[0] = ab[1] = ab[2] = ab[3] = ab[4] = ab[5] = ab[6] = ab[7] = ab[8] = 0;
	ab[7] = 0b0000'0010;
	ab[4] = 0b0010'0000;
	iBit = FindFirstSetBit(&ab[2], 44);
	AssertInt(21, iBit);

	iBit = FindNextSetBit(&ab[2], 44, 22);
	AssertInt(41, iBit);

	iBit = FindNextSetBit(&ab[2], 40, 22);
	AssertInt(-1, iBit);

	iBit = FindNextSetBit(&ab[2], 41, 22);
	AssertInt(-1, iBit);

	iBit = FindNextSetBit(&ab[2], 42, 22);
	AssertInt(41, iBit);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIntegerHelperFindNextClearBit(void)
{
	uint8	ab[9];
	int		iBit;

	ab[0] = ab[1] = ab[2] = ab[3] = ab[4] = ab[5] = ab[6] = ab[7] = ab[8] = 0;
	ab[1] = 0b0001'0000;

	iBit = FindFirstSetBit(ab, 64);
	AssertInt(12, iBit);

	iBit = FindNextClearBit(ab, 64, iBit);
	AssertInt(13, iBit);

	iBit = FindFirstSetBit(&ab[1], 63);
	AssertInt(4, iBit);

	iBit = FindNextClearBit(&ab[1], 63, iBit);
	AssertInt(5, iBit);

	ab[0] = 0b0111'1111;
	iBit = FindFirstClearBit(ab, 7);
	AssertInt(-1, iBit);

	iBit = FindNextClearBit(ab, 7, 1);
	AssertInt(-1, iBit);

	ab[0] = ab[1] = ab[2] = ab[3] = ab[4] = ab[5] = ab[6] = ab[7] = ab[8] = 0xff;
	ab[7] = 0b1111'1101;
	ab[4] = 0b1101'1111;
	iBit = FindFirstClearBit(&ab[2], 44);
	AssertInt(21, iBit);

	iBit = FindNextClearBit(&ab[2], 44, 22);
	AssertInt(41, iBit);

	iBit = FindNextClearBit(&ab[2], 40, 22);
	AssertInt(-1, iBit);

	iBit = FindNextClearBit(&ab[2], 41, 22);
	AssertInt(-1, iBit);

	iBit = FindNextClearBit(&ab[2], 42, 22);
	AssertInt(41, iBit);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIntegerHelperSetBits(void)
{
	uint8	ab[9];
	
	memset(ab, 0, 9);
	SetBits(9, ab, true, 3);

	AssertInt(0xe00, *((int*)ab));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIntegerHelperBitFunctions(void)
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
	AssertBool(true, GetBit(0, &c));
	AssertBool(false, GetBit(1, &c));
	AssertBool(true, GetBit(2, &c));

	AssertInt(1, FindFirstClearBit(c, 8 * 8));
	AssertInt(0, FindFirstSetBit(c, 8 * 8));
	c[0] = 4;
	AssertInt(0, FindFirstClearBit(c, 8 * 8));
	AssertInt(2, FindFirstSetBit(c, 8 * 8));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIntegerHelperMisc(void)
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
void TestIntegerHelperEndianness(void)
{
	union
	{
		int64	i64;
		int8	ia8[8];
	};

	i64 = 0x0102030405060708LL;

	AssertChar(0x08, ia8[0]);
#ifdef _DEBUG
	AssertChar(0x07, ia8[1]);
#endif // _DEBUG
	AssertChar(0x06, ia8[2]);
	AssertChar(0x05, ia8[3]);
	AssertChar(0x04, ia8[4]);
#ifdef _DEBUG
	AssertChar(0x03, ia8[5]);
#endif // _DEBUG
	AssertChar(0x02, ia8[6]);
	AssertChar(0x01, ia8[7]);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIntegerHelper(void)
{
	TestIntegerHelperFindFirstClearBit();
	TestIntegerHelperFindFirstSetBit();
	TestIntegerHelperFindLastClearBit();
	TestIntegerHelperFindLastSetBit();
	TestIntegerHelperReverseBytes();
	TestIntegerHelperCountBits();
	TestIntegerHelperFindNextSetBit();
	TestIntegerHelperFindNextClearBit();
	TestIntegerHelperSetBits();
	TestIntegerHelperBitFunctions();
	TestIntegerHelperMisc();
	TestIntegerHelperEndianness();
}

