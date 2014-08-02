#include "BaseLib/ArrayBit.h"
#include "BaseLib/MemoryFile.h"
#include "BaseLib/GlobalMemory.h"
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

	AssertIntHex(0xcbb78e55, ((int*)cArrayBit.GetData())[0]);
	AssertIntHex(0x011861ff, ((int*)cArrayBit.GetData())[1]);
	AssertIntHex(0x82d97e18, ((int*)cArrayBit.GetData())[2]);

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

	AssertFalse(cArrayBit.Get(97));
	AssertTrue(cArrayBit.Get(98));
	AssertFalse(cArrayBit.Get(99));
	AssertTrue(cArrayBit.Get(100));
	AssertFalse(cArrayBit.Get(101));
	AssertTrue(cArrayBit.Get(102));
	AssertFalse(cArrayBit.Get(103));
	AssertTrue(cArrayBit.Get(104));

	cArrayBit.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayBitReadWrite(void)
{
	CFileBasic		cFile;
	CArrayBit		cArrayBit;
	CArrayBit		cArrayBitIn;
	unsigned int	ui[3];
	cArrayBit.Init();

	cArrayBit.Add(TRUE);
	cArrayBit.Add(FALSE);

	cFile.Init(MemoryFile());
	cFile.Open(EFM_Write_Create);
	AssertTrue(cArrayBit.Write(&cFile));

	cFile.Close();
	cFile.Open(EFM_Read);
	
	cArrayBitIn.Read(&cFile);

	AssertInt(2, cArrayBitIn.NumElements());

	AssertTrue(cArrayBitIn.Get(0));
	AssertFalse(cArrayBitIn.Get(1));
	cArrayBitIn.Kill();

	cArrayBit.Add(TRUE);
	cArrayBit.Add(FALSE);
	cArrayBit.Add(TRUE);
	cArrayBit.Add(FALSE);
	cArrayBit.Add(TRUE);
	cArrayBit.Add(FALSE);
	ui[0] = 0xffcbb78e;
	ui[1] = 0x18011861;
	ui[2] = 0x0082d97e;
	cArrayBit.Add(ui, 0, 88);
	cArrayBit.Add(TRUE);
	cArrayBit.Add(FALSE);
	cArrayBit.Add(TRUE);
	cArrayBit.Add(FALSE);
	cArrayBit.Add(TRUE);
	cArrayBit.Add(FALSE);
	cArrayBit.Add(TRUE);
	cArrayBit.Add(FALSE);
	cArrayBit.Add(TRUE);
	AssertInt(105, cArrayBit.NumElements());

	cFile.Open(EFM_Write_Create);
	AssertTrue(cArrayBit.Write(&cFile));

	cFile.Close();
	cArrayBit.Kill();

	cFile.Open(EFM_Read);
	cArrayBitIn.Read(&cFile);

	AssertInt(105, cArrayBitIn.NumElements());
	AssertTrue(cArrayBitIn.Get(0));
	AssertFalse(cArrayBitIn.Get(1));
	AssertIntHex(0xcbb78e55, ((int*)cArrayBitIn.GetData())[0]);
	AssertIntHex(0x011861ff, ((int*)cArrayBitIn.GetData())[1]);
	AssertIntHex(0x82d97e18, ((int*)cArrayBitIn.GetData())[2]);
	AssertTrue(cArrayBitIn.Get(96));
	AssertFalse(cArrayBitIn.Get(97));
	AssertTrue(cArrayBitIn.Get(98));
	AssertFalse(cArrayBitIn.Get(99));
	AssertTrue(cArrayBitIn.Get(100));
	AssertFalse(cArrayBitIn.Get(101));
	AssertTrue(cArrayBitIn.Get(102));
	AssertFalse(cArrayBitIn.Get(103));
	AssertTrue(cArrayBitIn.Get(104));

	cArrayBitIn.Kill();
	cFile.Close();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayBit(void)
{
	BeginTests();
	FastFunctionsInit();
	MemoryInit();

	TestArrayBitAdd();
	TestArrayBitReadWrite();

	MemoryKill();
	FastFunctionsKill();
	TestStatistics();
}

