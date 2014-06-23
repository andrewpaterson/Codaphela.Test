#include "BaseLib/ArrayBit.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayBitAdd(void)
{
	CArrayBit		cArrayBit;
	unsigned int	ui[3];

	cArrayBit.Init();

	cArrayBit.Add(TRUE);
	cArrayBit.Add(FALSE);

	AssertInt(2, cArrayBit.NumElements());

	AssertTrue(cArrayBit.Get(0));
	AssertFalse(cArrayBit.Get(1));

	cArrayBit.Add(TRUE);
	cArrayBit.Add(FALSE);
	cArrayBit.Add(TRUE);
	cArrayBit.Add(FALSE);
	cArrayBit.Add(TRUE);
	cArrayBit.Add(FALSE);

	AssertInt(8, cArrayBit.NumElements());

	AssertTrue(cArrayBit.Get(2));
	AssertFalse(cArrayBit.Get(3));
	AssertTrue(cArrayBit.Get(4));
	AssertFalse(cArrayBit.Get(5));
	AssertTrue(cArrayBit.Get(6));
	AssertFalse(cArrayBit.Get(7));

	ui[0] = 0xffcbb78e;
	ui[1] = 0x18011861;
	ui[2] = 0x0082d97e;

	cArrayBit.Add(ui, 0, 88);

	AssertInt(96, cArrayBit.NumElements());

	AssertFalse(cArrayBit.Get(8));
	AssertTrue(cArrayBit.Get(9));
	AssertTrue(cArrayBit.Get(10));
	AssertTrue(cArrayBit.Get(11));
	AssertFalse(cArrayBit.Get(12));
	AssertFalse(cArrayBit.Get(13));
	AssertFalse(cArrayBit.Get(14));
	AssertTrue(cArrayBit.Get(15));

	AssertIntHex(0xcbb78e55, ((int*)cArrayBit.GetData())[0]);
	AssertIntHex(0x011861ff, ((int*)cArrayBit.GetData())[1]);
	AssertIntHex(0x82d97e18, ((int*)cArrayBit.GetData())[2]);

	cArrayBit.Add(TRUE);

	AssertInt(97, cArrayBit.NumElements());
	AssertTrue(cArrayBit.Get(96));

	cArrayBit.Add(FALSE);
	cArrayBit.Add(TRUE);
	cArrayBit.Add(FALSE);
	cArrayBit.Add(TRUE);
	cArrayBit.Add(FALSE);
	cArrayBit.Add(TRUE);
	cArrayBit.Add(FALSE);

	AssertInt(104, cArrayBit.NumElements());

	cArrayBit.Add(TRUE);

	AssertInt(105, cArrayBit.NumElements());
	AssertTrue(cArrayBit.Get(104));

	cArrayBit.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayBitLoad(void)
{
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayBit(void)
{
	BeginTests();
	FastFunctionsInit();

	AssertInt(16, sizeof(CArrayBit));
	TestArrayBitAdd();
	TestArrayBitLoad();

	FastFunctionsKill();
	TestStatistics();
}

