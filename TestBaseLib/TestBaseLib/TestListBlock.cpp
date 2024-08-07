#include "BaseLib/ListBlock.h"
#include "BaseLib/SystemAllocator.h"
#include "BaseLib/IntegerHelper.h"
#include "BaseLib/MapStringString.h"
#include "BaseLib/MemoryFile.h"
#include "BaseLib/GlobalMemory.h"
#include "TestLib/Assert.h"


struct STestListBlockItem
{
	int32	mi1;
	int32	mi2;

	void Init(int32 i1, int32 i2)
	{
		this->mi1 = i1;
		this->mi2 = i2;
	}
};


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestListBlockAdd(void)
{
	CListBlock				cList;
	STestListBlockItem*		psItem1;
	STestListBlockItem*		psItem2;
	STestListBlockItem*		psItem3;
	STestListBlockItem*		psItem4;
	STestListBlockItem*		psItem5;
	STestListBlockItem*		psItem6;
	STestListBlockItem*		psItem7;
	STestListBlockItem*		psItem8;
	STestListBlockItem*		psItem9;
	STestListBlockItem*		psItem10;

	cList.Init(sizeof(STestListBlockItem));
	AssertInt(0, cList.NumElements());
	AssertInt(0, cList.NumElementsFromFreeList());
	AssertInt(0, cList.NumBlocks());

	psItem1 = (STestListBlockItem *)cList.Add(); psItem1->Init(1, 101);
	psItem2 = (STestListBlockItem *)cList.Add(); psItem2->Init(2, 202);
	psItem3 = (STestListBlockItem *)cList.Add(); psItem3->Init(3, 303);
	AssertInt(3, cList.NumElements());
	AssertInt(3, cList.NumElementsFromFreeList());
	AssertInt(1, cList.NumBlocks());
	AssertPointer(psItem1, cList.Get(0));
	AssertPointer(psItem2, cList.Get(1));
	AssertPointer(psItem3, cList.Get(2));

	psItem4 = (STestListBlockItem *)cList.Add(); psItem4->Init(4, 404);
	AssertInt(4, cList.NumElements());
	AssertInt(4, cList.NumElementsFromFreeList());
	AssertInt(1, cList.NumBlocks());
	AssertPointer(psItem1, cList.Get(0));
	AssertPointer(psItem2, cList.Get(1));
	AssertPointer(psItem3, cList.Get(2));
	AssertPointer(psItem4, cList.Get(3));

	psItem5 = (STestListBlockItem *)cList.Add(); psItem5->Init(5, 505);
	psItem6 = (STestListBlockItem *)cList.Add(); psItem6->Init(6, 606);
	AssertInt(6, cList.NumElements());
	AssertInt(6, cList.NumElementsFromFreeList());
	AssertInt(1, cList.NumBlocks());
	AssertPointer(psItem1, cList.Get(0));
	AssertPointer(psItem2, cList.Get(1));
	AssertPointer(psItem3, cList.Get(2));
	AssertPointer(psItem4, cList.Get(3));
	AssertPointer(psItem5, cList.Get(4));
	AssertPointer(psItem6, cList.Get(5));
	
	psItem7 = (STestListBlockItem *)cList.Add(); psItem7->Init(7, 707);
	psItem8 = (STestListBlockItem *)cList.Add(); psItem8->Init(8, 808);
	psItem9 = (STestListBlockItem *)cList.Add(); psItem9->Init(9, 909);
	psItem10 = (STestListBlockItem *)cList.Add(); psItem10->Init(10, 111);
	AssertInt(10, cList.NumElements());
	AssertInt(10, cList.NumElementsFromFreeList());
	AssertInt(2, cList.NumBlocks());
	AssertPointer(psItem1, cList.Get(0));
	AssertPointer(psItem2, cList.Get(1));
	AssertPointer(psItem3, cList.Get(2));
	AssertPointer(psItem4, cList.Get(3));
	AssertPointer(psItem5, cList.Get(4));
	AssertPointer(psItem6, cList.Get(5));
	AssertPointer(psItem7, cList.Get(6));
	AssertPointer(psItem8, cList.Get(7));
	AssertPointer(psItem9, cList.Get(8));
	AssertPointer(psItem10, cList.Get(9));

	cList.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestListBlockRemove(void)
{
	CListBlock				cList;
	STestListBlockItem*		psItem1;
	STestListBlockItem*		psItem2;
	STestListBlockItem*		psItem3;
	STestListBlockItem*		psItem4;
	STestListBlockItem*		psItem5;
	STestListBlockItem*		psItem6;
	STestListBlockItem*		psItem7;
	STestListBlockItem*		psItem8;
	STestListBlockItem*		psItem9;
	STestListBlockItem*		psItem10;

	cList.Init(sizeof(STestListBlockItem));
	AssertInt(0, cList.NumElements());
	AssertInt(0, cList.NumElementsFromFreeList());
	AssertInt(0, cList.NumBlocks());

	psItem1 = (STestListBlockItem *)cList.Add(); psItem1->Init(1, 101);
	psItem2 = (STestListBlockItem *)cList.Add(); psItem2->Init(2, 202);
	psItem3 = (STestListBlockItem *)cList.Add(); psItem3->Init(3, 303);
	psItem4 = (STestListBlockItem *)cList.Add(); psItem4->Init(4, 404);
	psItem5 = (STestListBlockItem *)cList.Add(); psItem5->Init(5, 505);
	psItem6 = (STestListBlockItem *)cList.Add(); psItem6->Init(6, 606);
	psItem7 = (STestListBlockItem *)cList.Add(); psItem7->Init(7, 707);
	psItem8 = (STestListBlockItem *)cList.Add(); psItem8->Init(8, 808);
	psItem9 = (STestListBlockItem *)cList.Add(); psItem9->Init(9, 909);
	psItem10 = (STestListBlockItem *)cList.Add(); psItem10->Init(10, 111);
	AssertInt(10, cList.NumElements());
	AssertInt(10, cList.NumElementsFromFreeList());
	AssertInt(2, cList.NumBlocks());
	AssertPointer(psItem1, cList.Get(0));
	AssertPointer(psItem2, cList.Get(1));
	AssertPointer(psItem3, cList.Get(2));
	AssertPointer(psItem4, cList.Get(3));

	cList.RemoveAt(2);
	AssertPointer(psItem1, cList.Get(0));
	AssertPointer(psItem2, cList.Get(1));
	AssertPointer(psItem4, cList.Get(2));
	AssertPointer(psItem5, cList.Get(3));
	AssertPointer(psItem6, cList.Get(4));
	AssertInt(9, cList.NumElements());
	AssertInt(9, cList.NumElementsFromFreeList());
	AssertInt(2, cList.NumBlocks());

	cList.RemoveAt(0);
	AssertPointer(psItem2, cList.Get(0));
	AssertPointer(psItem4, cList.Get(1));
	AssertPointer(psItem5, cList.Get(2));
	AssertPointer(psItem6, cList.Get(3));
	AssertInt(8, cList.NumElements());
	AssertInt(8, cList.NumElementsFromFreeList());
	AssertInt(2, cList.NumBlocks());

	cList.RemoveAt(2);
	AssertPointer(psItem2, cList.Get(0));
	AssertPointer(psItem4, cList.Get(1));
	AssertPointer(psItem6, cList.Get(2));
	AssertInt(7, cList.NumElements());
	AssertInt(7, cList.NumElementsFromFreeList());
	AssertInt(2, cList.NumBlocks());

	cList.RemoveAt(0);
	AssertPointer(psItem4, cList.Get(0));
	AssertPointer(psItem6, cList.Get(1));
	AssertInt(6, cList.NumElements());
	AssertInt(6, cList.NumElementsFromFreeList());
	AssertInt(2, cList.NumBlocks());

	cList.RemoveAt(1);
	cList.RemoveAt(0);
	AssertInt(4, cList.NumElements());
	AssertInt(4, cList.NumElementsFromFreeList());
	AssertInt(2, cList.NumBlocks());

	cList.RemoveAt(1);
	cList.RemoveAt(0);
	AssertInt(2, cList.NumElements());
	AssertInt(2, cList.NumElementsFromFreeList());
	AssertInt(1, cList.NumBlocks());

	cList.RemoveAt(1);
	cList.RemoveAt(0);
	AssertInt(0, cList.NumElements());
	AssertInt(0, cList.NumElementsFromFreeList());
	AssertInt(0, cList.NumBlocks());

	cList.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestListBlockRemoveRange(void)
{
	CListBlock				cList;
	STestListBlockItem*		psItem1;
	STestListBlockItem*		psItem2;
	STestListBlockItem*		psItem3;
	STestListBlockItem*		psItem4;
	STestListBlockItem*		psItem5;
	STestListBlockItem*		psItem6;

	cList.Init(sizeof(STestListBlockItem));
	AssertInt(0, cList.NumElements());
	AssertInt(0, cList.NumElementsFromFreeList());
	AssertInt(0, cList.NumBlocks());

	psItem1 = (STestListBlockItem *)cList.Add(); psItem1->Init(1, 101);
	psItem2 = (STestListBlockItem *)cList.Add(); psItem2->Init(2, 202);
	psItem3 = (STestListBlockItem *)cList.Add(); psItem3->Init(3, 303);
	psItem4 = (STestListBlockItem *)cList.Add(); psItem4->Init(4, 404);
	psItem5 = (STestListBlockItem *)cList.Add(); psItem5->Init(5, 505);
	psItem6 = (STestListBlockItem *)cList.Add(); psItem6->Init(6, 606);

	cList.RemoveRange(3, 6);
	AssertInt(3, cList.NumElements());
	AssertInt(3, cList.NumElementsFromFreeList());
	AssertInt(1, cList.NumBlocks());
	AssertPointer(psItem1, cList.Get(0));
	AssertPointer(psItem2, cList.Get(1));
	AssertPointer(psItem3, cList.Get(2));

	cList.RemoveRange(0, 3);
	AssertInt(0, cList.NumElements());
	AssertInt(0, cList.NumElementsFromFreeList());
	AssertInt(0, cList.NumBlocks());

	psItem1 = (STestListBlockItem *)cList.Add(); psItem1->Init(1, 101);
	psItem2 = (STestListBlockItem *)cList.Add(); psItem2->Init(2, 202);
	psItem3 = (STestListBlockItem *)cList.Add(); psItem3->Init(3, 303);
	psItem4 = (STestListBlockItem *)cList.Add(); psItem4->Init(4, 404);
	psItem5 = (STestListBlockItem *)cList.Add(); psItem5->Init(5, 505);
	psItem6 = (STestListBlockItem *)cList.Add(); psItem6->Init(6, 606);

	cList.RemoveRange(0, 6);
	AssertInt(0, cList.NumElements());
	AssertInt(0, cList.NumElementsFromFreeList());
	AssertInt(0, cList.NumBlocks());

	psItem1 = (STestListBlockItem *)cList.Add(); psItem1->Init(1, 101);
	psItem2 = (STestListBlockItem *)cList.Add(); psItem2->Init(2, 202);
	psItem3 = (STestListBlockItem *)cList.Add(); psItem3->Init(3, 303);
	psItem4 = (STestListBlockItem *)cList.Add(); psItem4->Init(4, 404);
	psItem5 = (STestListBlockItem *)cList.Add(); psItem5->Init(5, 505);
	psItem6 = (STestListBlockItem *)cList.Add(); psItem6->Init(6, 606);
	cList.RemoveRange(2, 4);
	AssertInt(4, cList.NumElements());
	AssertInt(4, cList.NumElementsFromFreeList());
	AssertInt(1, cList.NumBlocks());
	AssertPointer(psItem1, cList.Get(0));
	AssertPointer(psItem2, cList.Get(1));
	AssertPointer(psItem5, cList.Get(2));
	AssertPointer(psItem6, cList.Get(3));

	cList.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestListBlockPushPop(void)
{
	CListBlock				cList;
	STestListBlockItem*		psItem1;
	STestListBlockItem*		psItem2;
	STestListBlockItem*		psItem3;
	STestListBlockItem*		psItem4;
	STestListBlockItem*		psItem5;
	STestListBlockItem*		psItem6;

	STestListBlockItem		sItem;

	cList.Init(sizeof(STestListBlockItem));
	AssertInt(0, cList.NumElements());
	AssertInt(0, cList.NumElementsFromFreeList());
	AssertInt(0, cList.NumBlocks());

	psItem1 = (STestListBlockItem*)cList.Add(); psItem1->Init(1, 101);
	psItem2 = (STestListBlockItem*)cList.Add(); psItem2->Init(2, 202);
	psItem3 = (STestListBlockItem*)cList.Add(); psItem3->Init(3, 303);
	psItem4 = (STestListBlockItem*)cList.Add(); psItem4->Init(4, 404);
	psItem5 = (STestListBlockItem*)cList.Add(); psItem5->Init(5, 505);
	psItem6 = (STestListBlockItem*)cList.Add(); psItem6->Init(6, 606);
	AssertInt(6, cList.NumElements());
	AssertInt(6, cList.NumElementsFromFreeList());
	AssertPointer(psItem1, cList.Get(0));
	AssertPointer(psItem2, cList.Get(1));
	AssertPointer(psItem3, cList.Get(2));
	AssertPointer(psItem4, cList.Get(3));
	AssertPointer(psItem5, cList.Get(4));
	AssertPointer(psItem6, cList.Get(5));

	cList.Pop(&sItem);
	AssertInt(5, cList.NumElements());
	AssertInt(5, cList.NumElementsFromFreeList());
	AssertInt(6, sItem.mi1);
	AssertInt(606, sItem.mi2);

	cList.Pop();
	cList.Pop(&sItem);
	AssertInt(3, cList.NumElements());
	AssertInt(3, cList.NumElementsFromFreeList());
	AssertInt(4, sItem.mi1);
	AssertInt(404, sItem.mi2);

	psItem4 = (STestListBlockItem*)cList.InsertAt(0); psItem4->Init(4, 404);
	AssertInt(4, cList.NumElements());
	AssertInt(4, cList.NumElementsFromFreeList());
	AssertPointer(psItem4, cList.Get(0));
	AssertPointer(psItem1, cList.Get(1));
	AssertPointer(psItem2, cList.Get(2));
	AssertPointer(psItem3, cList.Get(3));

	psItem5 = (STestListBlockItem*)cList.Push(); psItem5->Init(5, 505);
	psItem6 = (STestListBlockItem*)cList.Push(); psItem6->Init(6, 606);
	AssertInt(6, cList.NumElements());
	AssertInt(6, cList.NumElementsFromFreeList());
	AssertPointer(psItem4, cList.Get(0));
	AssertPointer(psItem1, cList.Get(1));
	AssertPointer(psItem2, cList.Get(2));
	AssertPointer(psItem3, cList.Get(3));
	AssertPointer(psItem5, cList.Get(4));
	AssertPointer(psItem6, cList.Get(5));

	cList.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestListBlock(void)
{
	BeginTests();
	MemoryInit();
	FastFunctionsInit();

	TestListBlockAdd();
	TestListBlockRemove();
	TestListBlockRemoveRange();
	TestListBlockPushPop();

	FastFunctionsKill();
	MemoryKill();
	TestStatistics();
}

