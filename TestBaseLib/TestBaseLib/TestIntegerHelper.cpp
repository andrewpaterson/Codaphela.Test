#include "BaseLib/IntegerHelper.h"
#include "TestLib/Assert.h"
#include "TestIntegerHelper.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFindFirstClearBit(void)
{
	unsigned char	ab[9];
	int				iIndex;
	int				iBit;

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
		SetBit(iBit, ab, FALSE);
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
void TestFindFirstSetBit(void)
{
	unsigned char	ab[9];
	int				iIndex;
	int				iBit;

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
		SetBit(iBit, ab, TRUE);
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
void TestFindLastClearBit(void)
{
	unsigned char	ab[9];
	int				iIndex;
	int				iBit;

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
		SetBit(iBit, ab, FALSE);
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
void TestFindLastSetBit(void)
{
	unsigned char	ab[9];
	int				iIndex;
	int				iBit;

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
		SetBit(iBit, ab, TRUE);
		iIndex = FindLastSetBit(ab, 72);
		AssertInt(iBit, iIndex);
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIntegerHelper(void)
{
	TestFindFirstClearBit();
	TestFindFirstSetBit();
	TestFindLastClearBit();
	TestFindLastSetBit();
}

