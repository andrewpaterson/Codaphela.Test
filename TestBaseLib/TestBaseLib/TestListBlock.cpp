#include "BaseLib/ListBlock.h"
#include "BaseLib/SystemAllocator.h"
#include "BaseLib/IntegerHelper.h"
#include "BaseLib/MapStringString.h"
#include "BaseLib/MemoryFile.h"
#include "BaseLib/GlobalMemory.h"
#include "TestLib/Assert.h"


struct STestListBlockItem
{
	int	mi1;
	int	mi2;

	void Init(int i1, int i2)
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

	cList.Init(3, sizeof(STestListBlockItem));
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
	AssertInt(2, cList.NumBlocks());
	AssertPointer(psItem1, cList.Get(0));
	AssertPointer(psItem2, cList.Get(1));
	AssertPointer(psItem3, cList.Get(2));
	AssertPointer(psItem4, cList.Get(3));

	psItem5 = (STestListBlockItem *)cList.Add(); psItem5->Init(5, 505);
	psItem6 = (STestListBlockItem *)cList.Add(); psItem6->Init(6, 606);
	AssertInt(6, cList.NumElements());
	AssertInt(6, cList.NumElementsFromFreeList());
	AssertInt(2, cList.NumBlocks());
	AssertPointer(psItem1, cList.Get(0));
	AssertPointer(psItem2, cList.Get(1));
	AssertPointer(psItem3, cList.Get(2));
	AssertPointer(psItem4, cList.Get(3));
	AssertPointer(psItem5, cList.Get(4));
	AssertPointer(psItem6, cList.Get(5));

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

	cList.Init(3, sizeof(STestListBlockItem));
	AssertInt(0, cList.NumElements());
	AssertInt(0, cList.NumElementsFromFreeList());
	AssertInt(0, cList.NumBlocks());

	psItem1 = (STestListBlockItem *)cList.Add(); psItem1->Init(1, 101);
	psItem2 = (STestListBlockItem *)cList.Add(); psItem2->Init(2, 202);
	psItem3 = (STestListBlockItem *)cList.Add(); psItem3->Init(3, 303);
	psItem4 = (STestListBlockItem *)cList.Add(); psItem4->Init(4, 404);
	psItem5 = (STestListBlockItem *)cList.Add(); psItem5->Init(5, 505);
	psItem6 = (STestListBlockItem *)cList.Add(); psItem6->Init(6, 606);
	AssertInt(6, cList.NumElements());
	AssertInt(6, cList.NumElementsFromFreeList());
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
	AssertInt(5, cList.NumElements());
	AssertInt(5, cList.NumElementsFromFreeList());
	AssertInt(2, cList.NumBlocks());

	cList.RemoveAt(0);
	AssertPointer(psItem2, cList.Get(0));
	AssertPointer(psItem4, cList.Get(1));
	AssertPointer(psItem5, cList.Get(2));
	AssertPointer(psItem6, cList.Get(3));
	AssertInt(4, cList.NumElements());
	AssertInt(4, cList.NumElementsFromFreeList());
	AssertInt(2, cList.NumBlocks());

	cList.RemoveAt(2);
	AssertPointer(psItem2, cList.Get(0));
	AssertPointer(psItem4, cList.Get(1));
	AssertPointer(psItem6, cList.Get(2));
	AssertInt(3, cList.NumElements());
	AssertInt(3, cList.NumElementsFromFreeList());
	AssertInt(2, cList.NumBlocks());

	cList.RemoveAt(0);
	AssertPointer(psItem4, cList.Get(0));
	AssertPointer(psItem6, cList.Get(1));
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

	cList.Init(3, sizeof(STestListBlockItem));
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
	AssertInt(2, cList.NumBlocks());
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
void TestListBlock(void)
{
	BeginTests();
	MemoryInit();
	FastFunctionsInit();

	TestListBlockAdd();
	TestListBlockRemove();
	TestListBlockRemoveRange();

	FastFunctionsKill();
	MemoryKill();
	TestStatistics();
}

