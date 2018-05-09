#include "BaseLib/ArrayIntMinimal.h"
#include "BaseLib/ArrayCharMinimal.h"
#include "TestLib/Assert.h"
#include "ArrayTemplateTestClasses.h"


typedef CArrayTemplateMinimal<STestArrayTemplateItem> CTestArray;
typedef CArrayTemplateMinimal<CTestOverridenArrayTemplateItem> CTestOverriddenArray;


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayMinimalTemplateChar(void)
{
	CArrayCharMinimal	cac;

	cac.Init("aabbc");
	AssertString("aabbc", cac.GetArray());

	cac.InsertBatch(0, 3, 2, 2);

	cac.GetArray()[0] = cac.GetArray()[1] = cac.GetArray()[2]='_';
	cac.GetArray()[5] = cac.GetArray()[6] = cac.GetArray()[7]='_';
	AssertString("___aa___bbc", cac.GetArray());

	cac.InsertNumAt(2, 1);

	cac.GetArray()[1]=cac.GetArray()[2]='X';
	AssertString("_XX__aa___bbc", cac.GetArray());

	cac.Kill();

	cac.Init("ABCDEFGHIJKLMNO");
	cac.RemoveBatch(2, 2, 3, 3);
	cac.Add(0);
	AssertString("ABEFGJKLO", cac.GetArray());

	cac.Kill();

	cac.Init("ABCDEFGHIJKLMNO");
	cac.RemoveBatch(0, 1, 4, 1);
	cac.Add(0);
	AssertString("BDFHIJKLMNO", cac.GetArray());

	cac.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayMinimalTemplateInt(void)
{
	CArrayIntMinimal	cai;

	cai.Init();
	cai.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayMinimalTemplateInsertBatch()
{
	CTestArray					as;
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
void TestArrayMinimalTemplateRemoveBatch()
{
	CTestArray					as;
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
	AssertInt(5, as.NumElements());
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
void TestArrayMinimalTemplateWithVirtualClass(void)
{
	CTestOverriddenArray				ac;
	CTestOverridenArrayTemplateItem*	pc;
	CTestOverridenArrayTemplateItem		c;
	int									iIndex;
	CTestOverridenArrayTemplateItem		av[5];
	int									i;

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

	pc = ac.InsertNumAt(3, 0);
	pc[0].Init(20);
	pc[1].Init(21);
	pc[2].Init(22);
	AssertPointer(pc, ac.Get(0));
	AssertInt(20, pc->i1);
	AssertInt(33, pc->i2);
	AssertInt(21, pc[1].i1);
	AssertInt(33, pc[1].i2);
	AssertInt(22, pc[2].i1);
	AssertInt(33, pc[2].i2);
	pc = ac.Get(3);
	AssertInt(4, pc->i1);
	AssertInt(33, pc->i2);

	AssertInt(8, ac.NumElements());

	pc = ac.Push();
	pc->Init(84);
	AssertInt(84, pc->i1);
	AssertInt(33, pc->i2);
	AssertPointer(pc, ac.Get(8));

	pc = ac.PushCopy();
	AssertInt(84, pc->i1);
	AssertInt(33, pc->i2);
	AssertPointer(pc, ac.Get(9));

	AssertInt(10, ac.NumElements());

	iIndex = ac.AddNum(3);
	AssertInt(10, iIndex);
	pc = ac.Get(iIndex);
	AssertString("CTestOverridenArrayTemplateItem", pc->GetName());
	AssertString("CTestOverridenArrayTemplateItem", pc[1].GetName());
	AssertString("CTestOverridenArrayTemplateItem", pc[2].GetName());

	AssertInt(13, ac.NumElements());

	ac.InsertBatch(1, 2, 3, 1);
	AssertInt(19, ac.NumElements());
	pc = ac.Get(0);
	AssertInt(20, pc->i1);
	AssertInt(33, pc->i2);
	pc = ac.Get(3);
	AssertInt(21, pc->i1);
	AssertInt(33, pc->i2);

	for (i = 0; i < 19; i++)
	{
		AssertString("CTestOverridenArrayTemplateItem", ac.Get(i)->GetName());
	}

	ac.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayMinimalTemplate(void)
{
	BeginTests();

	TestArrayMinimalTemplateChar();
	TestArrayMinimalTemplateInt();
	TestArrayMinimalTemplateInsertBatch();
	TestArrayMinimalTemplateRemoveBatch();
	TestArrayMinimalTemplateWithVirtualClass();

	TestStatistics();
}

