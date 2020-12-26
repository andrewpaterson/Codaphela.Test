#include "BaseLib/GlobalMemory.h"
#include "BaseLib/ArrayTemplate.h"
#include "TestLib/Assert.h"
#include "ArrayTemplateTestClasses.h"


typedef CArrayTemplate<STestArrayTemplateItem> CTestArrayTemplate;
typedef CArrayTemplate<CTestOverridenArrayTemplateItem> CTestOverriddenArray;


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayTemplateAllocation(void)
{
	CTestArrayTemplate			asTestArrayTemplate;
	STestArrayTemplateItem*		psItem;
	int				i;

	asTestArrayTemplate.Init();
	AssertInt(sizeof(STestArrayTemplateItem), asTestArrayTemplate.ElementSize());
	AssertInt(0, asTestArrayTemplate.NumElements());
	AssertInt(0, asTestArrayTemplate.AllocatedElements());
	AssertInt(1, asTestArrayTemplate.ChunkSize());
	AssertPointer(NULL, asTestArrayTemplate.GetData());

	psItem = asTestArrayTemplate.Add();
	AssertInt(1, asTestArrayTemplate.NumElements());
	AssertInt(1, asTestArrayTemplate.AllocatedElements());
	AssertInt(1, asTestArrayTemplate.ChunkSize());
	AssertFalse(asTestArrayTemplate.GetData() == NULL);

	psItem->i1 = 1;
	psItem->i2 = 2;

	//Add upto and including the eleventh element.  This will cause the array to be reallocated.
	for (i = 0; i < 10; i++)
	{
		asTestArrayTemplate.Add();
	}

	//Make sure the elements haven't been corrupted on reallocation.
	psItem = asTestArrayTemplate.Get(0);
	AssertInt(1, psItem->i1);
	AssertInt(2, psItem->i2);

	asTestArrayTemplate.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayTemplateAllocationWithVirtualClass(void)
{
	CTestOverriddenArray				ac;
	CTestOverridenArrayTemplateItem*	pc;
	CTestOverridenArrayTemplateItem		c;
	int									iIndex;
	CTestOverridenArrayTemplateItem		av[5];

	ac.Init();

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

	pc = ac.InsertNumAt(3, 0);
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
int SortTestArrayTemplateItemFunc(const void* pvItemLeft, const void* pvItemRight)
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
void TestArrayTemplateSorting(void)
{
	CTestArrayTemplate					asTestArrayTemplate;
	STestArrayTemplateItem*		psItem;

	asTestArrayTemplate.Init();
	psItem = asTestArrayTemplate.Add();
	psItem->i1 = psItem->i2 = 8;
	psItem = asTestArrayTemplate.Add();
	psItem->i1 = psItem->i2 = 5;
	psItem = asTestArrayTemplate.Add();
	psItem->i1 = psItem->i2 = 7;
	psItem = asTestArrayTemplate.Add();
	psItem->i1 = psItem->i2 = 2;

	asTestArrayTemplate.QuickSort(&SortTestArrayTemplateItemFunc);

	AssertInt(2, asTestArrayTemplate[0].i1);
	AssertInt(5, asTestArrayTemplate[1].i1);
	AssertInt(7, asTestArrayTemplate[2].i1);
    AssertInt(8, asTestArrayTemplate[3].i1);

	asTestArrayTemplate.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayTemplateCopy(void)
{
	CTestArrayTemplate			asTestArrayTemplate;
	CTestArrayTemplate			asDestArray;
	STestArrayTemplateItem*		psItem;
	void*						pvDest1;
	void*						pvDest2;

	asTestArrayTemplate.Init();
	psItem = asTestArrayTemplate.Add();
	psItem->i1 = psItem->i2 = 8;
	psItem = asTestArrayTemplate.Add();
	psItem->i1 = psItem->i2 = 5;
	psItem = asTestArrayTemplate.Add();
	psItem->i1 = psItem->i2 = 7;
	psItem = asTestArrayTemplate.Add();
	psItem->i1 = psItem->i2 = 2;
	psItem = asTestArrayTemplate.Add();
	psItem->i1 = psItem->i2 = 1;

	asDestArray.Init();
	asDestArray.Copy(&asTestArrayTemplate);
	pvDest1 = asDestArray.GetData();

	asDestArray.Copy(&asTestArrayTemplate);
	pvDest2 = asDestArray.GetData();
	AssertTrue(pvDest1 == pvDest2);

	psItem = asTestArrayTemplate.Add();
	psItem->i1 = psItem->i2 = 3;
	psItem = asTestArrayTemplate.Add();
	psItem->i1 = psItem->i2 = 4;
	psItem = asTestArrayTemplate.Add();
	psItem->i1 = psItem->i2 = 6;
	psItem = asTestArrayTemplate.Add();
	psItem->i1 = psItem->i2 = 9;

	asDestArray.Copy(&asTestArrayTemplate);

	AssertInt(16, asDestArray.AllocatedElements());
	AssertInt(9, asDestArray.NumElements());

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

	asTestArrayTemplate.Kill();
	asDestArray.Kill();
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayTemplateMisc(void)
{
	CTestArrayTemplate				cArray;
	STestArrayTemplateItem	sStack;
	int						iIndex;
	STestArrayTemplateItem*	psHeap;
	STestArrayTemplateItem*	psReturn;

	cArray.Init();
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
	cArray.Init();
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

	cArray.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayTemplateRemove(void)
{
	CTestArrayTemplate					cArray;
	STestArrayTemplateItem*		psTest1;
	STestArrayTemplateItem*		psTest2;

	cArray.Init();
	psTest1 = cArray.Add();
	psTest1->i1 = 0; psTest1->i2 = 0;
	cArray.RemoveAt(0, TRUE);
	AssertInt(0, cArray.NumElements());
	cArray.Kill();

	cArray.Init();
	psTest1 = cArray.Add();
	psTest2 = cArray.Add();
	psTest1->i1 = 0; psTest1->i2 = 0;
	psTest2->i1 = 1; psTest2->i2 = 1;
	cArray.RemoveAt(0, TRUE);
	psTest1 = cArray.Get(0);
	AssertInt(1, psTest1->i1);
	AssertInt(1, cArray.NumElements());
	cArray.Kill();

	cArray.Init();
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

	cArray.Init();
	psTest1 = cArray.Add();
	psTest1->i1 = 0; psTest1->i2 = 0;
	psTest2 = cArray.Add();
	psTest2->i1 = 1; psTest2->i2 = 1;
	cArray.RemoveAt(0, FALSE);
	psTest1 = cArray.Get(0);
	AssertInt(1, psTest1->i1);
	AssertInt(1, cArray.NumElements());
	cArray.Kill();

	cArray.Init();
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
void TestArrayTemplateFake(void)
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
void TestArrayTemplateInsertBatch()
{
	CTestArrayTemplate			as;
	int							i;
	STestArrayTemplateItem*		ps;


	as.Init();

	for (i = 0; i < 10; i++)
	{
		ps = as.Add();
		ps->i1 = i;
		ps->i2 = 255;
	}
	AssertInt(10, as.NumElements());

	as.InsertBatch(1, 2, 3, 1);
	AssertInt(16, as.NumElements());
	AssertInt(0, as.Get(0)->i1);
	AssertInt(1, as.Get(3)->i1);
	AssertInt(2, as.Get(6)->i1);
	AssertInt(3, as.Get(9)->i1);
	AssertInt(4, as.Get(10)->i1);
	AssertInt(5, as.Get(11)->i1);
	AssertInt(6, as.Get(12)->i1);
	AssertInt(7, as.Get(13)->i1);
	AssertInt(8, as.Get(14)->i1);
	AssertInt(9, as.Get(15)->i1);

	as.ReInit();

	for (i = 0; i < 3; i++)
	{
		ps = as.Add();
		ps->i1 = i;
		ps->i2 = 255;
	}
	AssertInt(3, as.NumElements());

	as.InsertBatch(0, 1, 3, 1);
	AssertInt(6, as.NumElements());
	AssertInt(0, as.Get(1)->i1);
	AssertInt(1, as.Get(3)->i1);
	AssertInt(2, as.Get(5)->i1);

	as.ReInit();

	for (i = 0; i < 3; i++)
	{
		ps = as.Add();
		ps->i1 = i;
		ps->i2 = 255;
	}
	AssertInt(3, as.NumElements());

	as.InsertBatch(0, 1, 3, 2);
	AssertInt(6, as.NumElements());
	AssertInt(0, as.Get(1)->i1);
	AssertInt(1, as.Get(2)->i1);
	AssertInt(2, as.Get(4)->i1);

	as.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayTemplateRemoveBatch(void)
{
	CTestArrayTemplate			as;
	int							i;
	STestArrayTemplateItem*		ps;


	as.Init();
	for (i = 0; i < 10; i++)
	{
		ps = as.Add();
		ps->i1 = i;
		ps->i2 = 255;
	}
	AssertInt(10, as.NumElements());

	as.RemoveBatch(1, 1, 5, 1);
	AssertInt(5, as.NumElements()));
	AssertInt(0, as.Get(0)->i1);
	AssertInt(2, as.Get(1)->i1);
	AssertInt(4, as.Get(2)->i1);
	AssertInt(6, as.Get(3)->i1);
	AssertInt(8, as.Get(4)->i1);

	as.Kill();

	as.Init();
	for (i = 0; i < 10; i++)
	{
		ps = as.Add();
		ps->i1 = i;
		ps->i2 = 255;
	}

	as.RemoveBatch(0, 3, 2, 2);
	AssertInt(4, as.NumElements());
	AssertInt(3, as.Get(0)->i1);
	AssertInt(4, as.Get(1)->i1);
	AssertInt(8, as.Get(2)->i1);
	AssertInt(9, as.Get(3)->i1);

	as.Kill();

	as.Init();
	for (i = 0; i < 10; i++)
	{
		ps = as.Add();
		ps->i1 = i;
		ps->i2 = 255;
	}

	as.RemoveBatch(0, 4, 2, 6);
	AssertInt(6, as.NumElements());
	AssertInt(4, as.Get(0)->i1);
	AssertInt(5, as.Get(1)->i1);
	AssertInt(6, as.Get(2)->i1);
	AssertInt(7, as.Get(3)->i1);
	AssertInt(8, as.Get(4)->i1);
	AssertInt(9, as.Get(5)->i1);

	as.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayTemplateSetChunkSize(void)
{
	CTestArrayTemplate			as;
	int							i;
	STestArrayTemplateItem*		ps;
	SArrayTemplateHeader		sHeader;


	as.Init(&gcSystemAllocator, 4);
	for (i = 0; i < 32; i++)
	{
		ps = as.Add();
		ps->i1 = i;
		ps->i2 = 255;
	}
	AssertInt(32, as.NumElements());

	as.GetHeader(&sHeader);
	AssertInt(16, sHeader.miChunkSize);

	AssertTrue(as.SetChunkSize(4));

	as.GetHeader(&sHeader);
	AssertInt(4, sHeader.miChunkSize);

	ps = as.Add();
	ps->i1 = 32;
	ps->i2 = 255;

	//Chunk size is calculated on the number of elements not the chunksize so it will just be reset to 16 after the array is grown again.
	as.GetHeader(&sHeader);
	AssertInt(16, sHeader.miChunkSize);

	for (i = 0; i < 64; i++)
	{
		ps = as.Add();
		ps->i1 = 32 + i;
		ps->i2 = 255;
	}

	as.GetHeader(&sHeader);
	AssertInt(32, sHeader.miChunkSize);
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

	TestArrayTemplateMisc();
	TestArrayTemplateAllocation();
	TestArrayTemplateAllocationWithVirtualClass();
	TestArrayTemplateCopy();
	TestArrayTemplateSorting();
	TestArrayTemplateRemove();
	TestArrayTemplateFake();
	TestArrayTemplateInsertBatch();
	TestArrayTemplateRemoveBatch();
	TestArrayTemplateSetChunkSize();

	FastFunctionsKill();
	MemoryKill();
	TestStatistics();
}

