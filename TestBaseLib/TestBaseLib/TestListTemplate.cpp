#include "BaseLib/ListTemplate.h"
#include "BaseLib/SystemAllocator.h"
#include "BaseLib/IntegerHelper.h"
#include "BaseLib/MapStringString.h"
#include "BaseLib/MemoryFile.h"
#include "BaseLib/GlobalMemory.h"
#include "TestLib/Assert.h"


struct STestListTemplateItem
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
void TestListTemplateMethods(void)
{
	CListTemplate<STestListTemplateItem>	cList;
	STestListTemplateItem*					psItem1;
	STestListTemplateItem					sItem2;
	STestListTemplateItem*					psItem2;
	STestListTemplateItem*					psItem3;
	STestListTemplateItem*					psItem4;
	STestListTemplateItem*					psItem5;
	STestListTemplateItem					sItem6;
	int										iIndex;
	STestListTemplateItem					sItem;

	cList.Init(16);
	cList.Kill();

	cList.Init(16, 7);
	cList.Kill();

	cList.Init();
	psItem1 = cList.Add();
	psItem1->Init(111, 8);

	sItem2.Init(222, 16);
	cList.Add(&sItem2);
	AssertInt(2, cList.NumElements());

	psItem3 = cList.AddGetIndex(&iIndex);
	psItem3->Init(333, 32);
	AssertInt(2, iIndex);
	AssertInt(3, cList.NumElements());
	AssertInt(3, cList.NumElementsFromFreeList());
	AssertInt(1, cList.NumBlocks());

	psItem2 = cList.Get(1);
	AssertInt(sItem2.mi1, psItem2->mi1);
	AssertInt(sItem2.mi2, psItem2->mi2);
	AssertPointer(psItem1, cList.Get(0));

	AssertNull(cList.SafeGet(-1));
	AssertNull(cList.SafeGet(3));

	AssertInt(0, cList.GetIndex(psItem1));
	AssertInt(1, cList.GetIndex(psItem2));
	AssertInt(2, cList.GetIndex(psItem3));

	AssertPointer(psItem3, cList.Tail());

	psItem4 = cList.InsertAt(1);
	psItem4->Init(444, 64);
	AssertInt(4, cList.NumElements());
	AssertInt(4, cList.NumElementsFromFreeList());
	AssertInt(0, cList.GetIndex(psItem1));
	AssertInt(1, cList.GetIndex(psItem4));
	AssertInt(2, cList.GetIndex(psItem2));
	AssertInt(3, cList.GetIndex(psItem3));

	cList.Pop(&sItem);
	AssertInt(333, sItem.mi1);
	AssertInt(32, sItem.mi2);
	AssertInt(3, cList.NumElements());
	AssertInt(3, cList.NumElementsFromFreeList());

	psItem5 = cList.Push();
	psItem5->Init(1, 5);

	sItem6.Init(1, 6);
	cList.Push(&sItem6);
	AssertInt(5, cList.NumElements());
	AssertInt(5, cList.NumElementsFromFreeList());

	AssertTrue(cList.Contains(psItem1));
	AssertFalse(cList.Contains(NULL));

	sItem.Init(12, 17);
	AssertTrue(cList.Set(0, &sItem));
	AssertInt(5, cList.NumElements());
	AssertInt(5, cList.NumElementsFromFreeList());
	AssertInt(12, cList.Get(0)->mi1);
	AssertInt(17, cList.Get(0)->mi2);
	AssertPointer(psItem1, cList.Get(0));

	AssertFalse(cList.Set(-1, &sItem));
	AssertFalse(cList.Set(5, &sItem));

	cList.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestListTemplate(void)
{
	BeginTests();
	MemoryInit();
	FastFunctionsInit();

	TestListTemplateMethods();

	FastFunctionsKill();
	MemoryKill();
	TestStatistics();
}

