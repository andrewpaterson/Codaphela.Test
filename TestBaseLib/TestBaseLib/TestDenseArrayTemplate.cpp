#include "TestDenseArrayTemplate.h"
#include "TestLib/Assert.h"
#include "BaseLib/ArrayDenseTemplate.h"


struct STestArrayDenseTemplateItem
{
	int	i1;
};


typedef CArrayDenseTemplate<STestArrayDenseTemplateItem> CTestDenseArray;


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayDenseTemplateInsertion(void)
{
	CTestDenseArray					cArray;
	STestArrayDenseTemplateItem*	psItem0;
	STestArrayDenseTemplateItem*	psItem1;
	STestArrayDenseTemplateItem*	psItem2;
	STestArrayDenseTemplateItem*	psItem3;
	STestArrayDenseTemplateItem*	psItem;
	int								i;
	int								iEnd;

	cArray.Init(1, 1);

	psItem0 = cArray.Add();
	psItem0->i1 = 0;
	AssertPointer(psItem0, cArray.mpsRoot->GetLeft());

	psItem1 = cArray.Add();
	psItem1->i1 = 1;
	AssertPointer(psItem1, cArray.mpsRoot->GetRight());
	AssertInt(2, cArray.miUsedElements);

	psItem2 = cArray.Add();
	psItem2->i1 = 2;

	psItem3 = cArray.Add();
	psItem3->i1 = 3;
	AssertInt(4, cArray.miUsedElements);
	AssertInt(3, cArray.miUsedNodes);

	for (i = 0; i < cArray.miUsedElements; i++)
	{
		psItem = cArray.Get(i);
		AssertInt(i, psItem->i1);
	}

	iEnd = cArray.miUsedElements+100;
	for (i = cArray.miUsedElements; i < iEnd; i++)
	{
		psItem = cArray.Add();
		psItem->i1 = i;
	}
	for (i = 0; i < cArray.miUsedElements; i++)
	{
		psItem = cArray.Get(i);
		AssertInt(i, psItem->i1);
	}
	cArray.Kill();

	cArray.Init(100, 100);
	psItem = cArray.Add();
	psItem->i1 = 0;

	psItem = cArray.InsertAt(0);
	psItem->i1 = -1;

	psItem = cArray.Get(0);
	AssertInt(-1, psItem->i1);
	psItem = cArray.Get(1);
	AssertInt(0, psItem->i1);

	iEnd = cArray.miUsedElements+100;
	for (i = cArray.miUsedElements; i < iEnd; i++)
	{
		psItem = cArray.InsertAt(0);
		psItem->i1 = -i;
	}
	for (i = 0; i < cArray.miUsedElements; i++)
	{
		psItem = cArray.Get(i);
		AssertInt(i-(cArray.miUsedElements-1), psItem->i1);
	}

	cArray.Kill();

	cArray.Init(1, 1);
	psItem = cArray.Add();
	psItem->i1 = 0;

	psItem = cArray.InsertAt(1);
	psItem->i1 = 2;
	psItem = cArray.InsertAt(1);
	psItem->i1 = 1;
	psItem = cArray.InsertAt(3);
	psItem->i1 = 3;
	psItem = cArray.InsertAt(1);
	psItem->i1 = 100;
	psItem = cArray.InsertAt(0);
	psItem->i1 = 101;
	psItem = cArray.InsertAt(3);
	psItem->i1 = 102;
	psItem = cArray.InsertAt(6);
	psItem->i1 = 103;
	psItem = cArray.InsertAt(5);
	psItem->i1 = 104;

	AssertInt(9, cArray.miUsedElements);

	psItem = cArray.Get(0);
	AssertInt(101, psItem->i1);
	psItem = cArray.Get(1);
	AssertInt(0, psItem->i1);
	psItem = cArray.Get(2);
	AssertInt(100, psItem->i1);
	psItem = cArray.Get(3);
	AssertInt(102, psItem->i1);
	psItem = cArray.Get(4);
	AssertInt(1, psItem->i1);
	psItem = cArray.Get(5);
	AssertInt(104, psItem->i1);
	psItem = cArray.Get(6);
	AssertInt(2, psItem->i1);
	psItem = cArray.Get(7);
	AssertInt(103, psItem->i1);
	psItem = cArray.Get(8);
	AssertInt(3, psItem->i1);

	cArray.Kill();
}



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayDenseTemplateRemoval(void)
{
	CTestDenseArray					cArray;
	STestArrayDenseTemplateItem*	psItem;
	int								i;
	BOOL							bResult;

	cArray.Init(1, 1);

	for (i = 0; i < 10; i++)
	{
		psItem = cArray.Add();
		psItem->i1 = i;

		bResult = cArray.TestStructure();
		AssertTrue(bResult);
		if (!bResult)
		{
			cArray.Kill();
			return;
		}
	}

	cArray.RemoveAt(5);
	psItem = cArray.Get(5);
	AssertInt(6, psItem->i1);

	cArray.RemoveAt(2);
	psItem = cArray.Get(2);
	AssertInt(3, psItem->i1);

	cArray.RemoveAt(6);
	psItem = cArray.Get(6);
	AssertInt(9, psItem->i1);

	cArray.RemoveAt(0);
	psItem = cArray.Get(0);
	AssertInt(1, psItem->i1);

	cArray.RemoveAt(1);
	psItem = cArray.Get(1);
	AssertInt(4, psItem->i1);

	cArray.RemoveAt(2);
	psItem = cArray.Get(2);
	AssertInt(7, psItem->i1);

	cArray.RemoveAt(2);
	psItem = cArray.Get(2);
	AssertInt(9, psItem->i1);

	cArray.RemoveAt(0);
	psItem = cArray.Get(0);
	AssertInt(4, psItem->i1);

	cArray.RemoveAt(1);
	psItem = cArray.Get(0);
	AssertInt(4, psItem->i1);

	cArray.RemoveAt(0);
	AssertInt(0, cArray.miUsedElements);

	cArray.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayDenseTemplate(void)
{
	BeginTests();

	TestArrayDenseTemplateInsertion();
	TestArrayDenseTemplateRemoval();

	TestStatistics();
}

