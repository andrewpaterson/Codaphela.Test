#include "BaseLib/GlobalMemory.h"
#include "BaseLib/ArrayTemplate.h"
#include "TestLib/Assert.h"
#include "ArrayTemplateTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayAllocation(void)
{
	CTestArray					asTestArray;
	STestArrayTemplateItem*		psItem;
	int				i;

	asTestArray.Init(10);
	AssertInt(sizeof(STestArrayTemplateItem), asTestArray.ElementSize());
	AssertInt(0, asTestArray.NumElements());
	AssertInt(0, asTestArray.AllocatedElements());
	AssertInt(10, asTestArray.ChunkSize());
	AssertPointer(NULL, asTestArray.GetData());

	psItem = asTestArray.Add();
	AssertInt(1, asTestArray.NumElements());
	AssertInt(10, asTestArray.AllocatedElements());
	AssertInt(10, asTestArray.ChunkSize());
	AssertFalse(asTestArray.GetData() == NULL);

	psItem->i1 = 1;
	psItem->i2 = 2;

	//Add upto and including the eleventh element.  This will cause the array to be reallocated.
	for (i = 0; i < 10; i++)
	{
		asTestArray.Add();
	}

	//Make sure the elements haven't been corrupted on reallocation.
	psItem = asTestArray.Get(0);
	AssertInt(1, psItem->i1);
	AssertInt(2, psItem->i2);

	asTestArray.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayAllocationWithVirtualClass(void)
{
	CTestOverriddenArray				ac;
	CTestOverridenArrayTemplateItem*	pc;
	CTestOverridenArrayTemplateItem		c;
	int									iIndex;
	CTestOverridenArrayTemplateItem		av[5];

	ac.Init(1);

	pc = ac.Add();
	pc->Init(1);
	AssertInt(1, pc->i1);
	AssertInt(33, pc->i2);

	c.Init(4);
	pc = ac.Add(&c);
	AssertInt(4, pc->i1);
	AssertInt(33, pc->i2);

	pc->Init(1);
	AssertInt(1, pc->i1);
	AssertInt(33, pc->i2);

	pc = ac.AddGetIndex(&iIndex);
	AssertInt(2, iIndex);
	pc->Init(47);
	AssertInt(47, pc->i1);
	AssertInt(33, pc->i2);
	
	pc = ac.InsertAt(1);
	pc->Init(5);
	AssertInt(5, pc->i1);
	AssertInt(33, pc->i2);
	AssertPointer(pc, ac.Get(1));
	pc = ac.Get(2);
	AssertInt(1, pc->i1);
	AssertInt(33, pc->i2);

	pc = ac.InsertAt(&c, 0);
	AssertInt(4, pc->i1);
	AssertInt(33, pc->i2);
	AssertPointer(pc, ac.Get(0));
	pc = ac.Get(1);
	AssertInt(1, pc->i1);
	AssertInt(33, pc->i2);

	AssertInt(5, ac.NumElements());

	av[0].Init(10);
	av[1].Init(11);
	av[2].Init(12);
	av[3].Init(13);
	av[4].Init(14);
	pc = ac.InsertBlockAfterEnd(av, 5);
	AssertInt(10, pc->i1);
	AssertInt(33, pc->i2);
	AssertInt(11, pc[1].i1);
	AssertInt(33, pc[1].i2);
	AssertInt(12, pc[2].i1);
	AssertInt(33, pc[2].i2);
	AssertInt(13, pc[3].i1);
	AssertInt(33, pc[3].i2);
	AssertInt(14, pc[4].i1);
	AssertInt(33, pc[4].i2);
	AssertPointer(pc, ac.Get(5));

	AssertInt(10, ac.NumElements());

	pc = ac.InsertBlockAt(av, 2, 8);
	AssertInt(10, pc->i1);
	AssertInt(33, pc->i2);
	AssertInt(11, pc[1].i1);
	AssertInt(33, pc[1].i2);
	AssertPointer(pc, ac.Get(8));
	pc = ac.Get(10);
	AssertInt(13, pc->i1);
	AssertInt(33, pc->i2);
	pc = ac.Get(9);
	AssertInt(11, pc->i1);
	AssertInt(33, pc->i2);

	AssertInt(12, ac.NumElements());

	pc = ac.InsertNumElementsAt(3, 0);
	pc[0].Init(20);
	pc[1].Init(21);
	pc[2].Init(22);
	AssertInt(20, pc->i1);
	AssertInt(33, pc->i2);
	AssertInt(21, pc[1].i1);
	AssertInt(33, pc[1].i2);
	AssertInt(22, pc[2].i1);
	AssertInt(33, pc[2].i2);

	AssertInt(15, ac.NumElements());

	pc = ac.Push();
	pc->Init(84);
	AssertInt(84, pc->i1);
	AssertInt(33, pc->i2);
	AssertPointer(pc, ac.Get(15));

	pc = ac.PushCopy();
	AssertInt(84, pc->i1);
	AssertInt(33, pc->i2);
	AssertPointer(pc, ac.Get(16));

	AssertInt(17, ac.NumElements());

	ac.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int SortTestArrayItemFunc(const void* pvItemLeft, const void* pvItemRight)
{
	if (((STestArrayTemplateItem*)pvItemLeft)->i1 < ((STestArrayTemplateItem*)pvItemRight)->i1)
	{
		return -1;
	}
	if (((STestArrayTemplateItem*)pvItemLeft)->i1 > ((STestArrayTemplateItem*)pvItemRight)->i1)
	{
		return 1;
	}
	return 0;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArraySorting(void)
{
	CTestArray					asTestArray;
	STestArrayTemplateItem*		psItem;

	asTestArray.Init(10);
	psItem = asTestArray.Add();
	psItem->i1 = psItem->i2 = 8;
	psItem = asTestArray.Add();
	psItem->i1 = psItem->i2 = 5;
	psItem = asTestArray.Add();
	psItem->i1 = psItem->i2 = 7;
	psItem = asTestArray.Add();
	psItem->i1 = psItem->i2 = 2;

	asTestArray.QuickSort(&SortTestArrayItemFunc);

	AssertInt(2, asTestArray[0].i1);
	AssertInt(5, asTestArray[1].i1);
	AssertInt(7, asTestArray[2].i1);
    AssertInt(8, asTestArray[3].i1);

	asTestArray.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayCopy(void)
{
	CTestArray					asTestArray;
	CTestArray					asDestArray;
	STestArrayTemplateItem*		psItem;
	void*						pvDest1;
	void*						pvDest2;
	BOOL						bResult;

	asTestArray.Init(5);
	psItem = asTestArray.Add();
	psItem->i1 = psItem->i2 = 8;
	psItem = asTestArray.Add();
	psItem->i1 = psItem->i2 = 5;
	psItem = asTestArray.Add();
	psItem->i1 = psItem->i2 = 7;
	psItem = asTestArray.Add();
	psItem->i1 = psItem->i2 = 2;
	psItem = asTestArray.Add();
	psItem->i1 = psItem->i2 = 1;

	asDestArray.Init(1);
	bResult = asDestArray.Copy(&asTestArray);
	AssertTrue(bResult);
	pvDest1 = asDestArray.GetData();

	bResult = asDestArray.Copy(&asTestArray);
	AssertFalse(bResult);
	pvDest2 = asDestArray.GetData();
	AssertTrue(pvDest1 == pvDest2);

	psItem = asTestArray.Add();
	psItem->i1 = psItem->i2 = 3;

	bResult = asDestArray.Copy(&asTestArray);
	AssertTrue(bResult);
	
	AssertInt(10, asDestArray.AllocatedElements());
	AssertInt(6, asDestArray.NumElements());

	psItem = asDestArray.Get(0);
	AssertInt(8, psItem->i1);
	psItem = asDestArray.Get(1);
	AssertInt(5, psItem->i1);
	psItem = asDestArray.Get(2);
	AssertInt(7, psItem->i1);
	psItem = asDestArray.Get(3);
	AssertInt(2, psItem->i1);
	psItem = asDestArray.Get(4);
	AssertInt(1, psItem->i1);
	psItem = asDestArray.Get(5);
	AssertInt(3, psItem->i1);

	asTestArray.Kill();
	asDestArray.Kill();
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMisc(void)
{
	CTestArray				cArray;
	STestArrayTemplateItem	sStack;
	int						iIndex;
	STestArrayTemplateItem*	psHeap;
	STestArrayTemplateItem*	psReturn;

	cArray.Init(5);
	iIndex = cArray.GetIndex(&sStack);
	AssertInt(-1, iIndex);

	psHeap = cArray.Add();
	psHeap->i1 = 0;
	psHeap->i2 = 1;

	sStack.i2 = 7;
	sStack.i1 = 8;

	cArray.InsertAt(&sStack, 0);
	AssertInt(2, cArray.NumElements());

	psReturn = cArray.Get(0);
	AssertInt(8, psReturn->i1);
	AssertInt(7, psReturn->i2);

	psReturn = cArray.Get(1);
	AssertInt(0, psReturn->i1);
	AssertInt(1, psReturn->i2);

	cArray.RemoveAt(0, TRUE);
	AssertInt(1, cArray.NumElements());

	psReturn = cArray.Get(0);
	AssertInt(0, psReturn->i1);
	AssertInt(1, psReturn->i2);

	cArray.PushCopy();
	AssertInt(2, cArray.NumElements());
	psReturn = cArray.Get(0);
	AssertInt(0, psReturn->i1);
	AssertInt(1, psReturn->i2);
	psReturn = cArray.Get(1);
	AssertInt(0, psReturn->i1);
	AssertInt(1, psReturn->i2);

	cArray.RemoveAt(1);
	cArray.Pop(&sStack);
	AssertInt(0, sStack.i1);
	AssertInt(1, sStack.i2);

	cArray.Kill();
	cArray.Init(1);
	psReturn = cArray.Add();  psReturn->i1 = 1; psReturn->i2 = 2;
	psReturn = cArray.Add();  psReturn->i1 = 3; psReturn->i2 = 4;
	psReturn = cArray.Add();  psReturn->i1 = 5; psReturn->i2 = 6;

	iIndex = cArray.FindWithIntKey(5);
	AssertInt(2, iIndex);

	iIndex = cArray.FindWithIntKey(6, sizeof(int));
	AssertInt(2, iIndex);

	iIndex = cArray.FindWithKey(psReturn, 0, sizeof(int));
	AssertInt(2, iIndex);

	iIndex = cArray.FindWithKey(psReturn, 4, sizeof(int));
	AssertInt(2, iIndex);

	cArray.Swap(1, 2);
	psReturn = cArray.Get(1);
	AssertInt(5, psReturn->i1);
	AssertInt(6, psReturn->i2);
	psReturn = cArray.Get(2);
	AssertInt(3, psReturn->i1);
	AssertInt(4, psReturn->i2);

}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayRemove(void)
{
	CTestArray					cArray;
	STestArrayTemplateItem*		psTest1;
	STestArrayTemplateItem*		psTest2;

	cArray.Init(1);
	psTest1 = cArray.Add();
	psTest1->i1 = 0; psTest1->i2 = 0;
	cArray.RemoveAt(0, TRUE);
	AssertInt(0, cArray.NumElements());
	cArray.Kill();

	cArray.Init(1);
	psTest1 = cArray.Add();
	psTest2 = cArray.Add();
	psTest1->i1 = 0; psTest1->i2 = 0;
	psTest2->i1 = 1; psTest2->i2 = 1;
	cArray.RemoveAt(0, TRUE);
	psTest1 = cArray.Get(0);
	AssertInt(1, psTest1->i1);
	AssertInt(1, cArray.NumElements());
	cArray.Kill();

	cArray.Init(1);
	psTest1 = cArray.Add();
	psTest1->i1 = 0; psTest1->i2 = 0;
	psTest2 = cArray.Add();
	psTest2->i1 = 1; psTest2->i2 = 1;
	psTest1 = cArray.Get(0);
	AssertInt(0, psTest1->i1);
	psTest2 = cArray.Get(1);
	AssertInt(1, psTest2->i1);
	cArray.RemoveAt(1, TRUE);
	psTest1 = cArray.Get(0);
	AssertInt(0, psTest1->i1);
	AssertInt(1, cArray.NumElements());
	cArray.Kill();

	cArray.Init(1);
	psTest1 = cArray.Add();
	psTest1->i1 = 0; psTest1->i2 = 0;
	psTest2 = cArray.Add();
	psTest2->i1 = 1; psTest2->i2 = 1;
	cArray.RemoveAt(0, FALSE);
	psTest1 = cArray.Get(0);
	AssertInt(1, psTest1->i1);
	AssertInt(1, cArray.NumElements());
	cArray.Kill();

	cArray.Init(1);
	psTest1 = cArray.Add();
	psTest1->i1 = 0; psTest1->i2 = 0;
	psTest2 = cArray.Add();
	psTest2->i1 = 1; psTest2->i2 = 1;
	cArray.RemoveAt(1, FALSE);
	psTest1 = cArray.Get(0);
	AssertInt(0, psTest1->i1);
	AssertInt(1, cArray.NumElements());
	cArray.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayFake(void)
{
	CArrayTemplate<char>	cac;
	char*					szTest;
	char*					pc;

	szTest = (char*)malloc(5);
	strcpy(szTest, "Test");

	cac.Fake(szTest, 2, 5);
	pc = cac.Add();
	*pc = 'x';

	AssertString("Text", cac.GetData());
	free(szTest);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayTemplate(void)
{
	BeginTests();
	MemoryInit();
	FastFunctionsInit();

	TestMisc();
	TestArrayAllocation();
	TestArrayAllocationWithVirtualClass();
	TestArrayCopy();
	TestArraySorting();
	TestArrayRemove();
	TestArrayFake();

	FastFunctionsKill();
	MemoryKill();
	TestStatistics();
}

