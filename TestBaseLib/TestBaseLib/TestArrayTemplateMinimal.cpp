#include "BaseLib/ArrayIntMinimal.h"
#include "BaseLib/ArrayCharMinimal.h"
#include "TestLib/Assert.h"
#include "ArrayTemplateTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayMinimalTemplateChar(void)
{
	CArrayCharMinimal	cac;

	cac.Init("aabbc");
	AssertString("aabbc", cac.GetArray());

	cac.BatchInsertElements(0, 3, 2, 2);

	cac.GetArray()[0] = cac.GetArray()[1] = cac.GetArray()[2]='_';
	cac.GetArray()[5] = cac.GetArray()[6] = cac.GetArray()[7]='_';
	AssertString("___aa___bbc", cac.GetArray());

	cac.InsertNumAt(2, 1);

	cac.GetArray()[1]=cac.GetArray()[2]='X';
	AssertString("_XX__aa___bbc", cac.GetArray());

	cac.Kill();

	cac.Init("ABCDEFGHIJK");
	cac.BatchRemoveElements(2, 2, 3, 3);
	AssertString("ABEHK", cac.GetArray());

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


typedef CArrayTemplateMinimal<STestArrayTemplateItem> CTestArray;
typedef CArrayTemplateMinimal<CTestOverridenArrayTemplateItem> CTestOverriddenArray;


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

	AssertInt(5, ac.NumElements());

	pc = ac.Push();
	pc->Init(84);
	AssertInt(84, pc->i1);
	AssertInt(33, pc->i2);
	AssertPointer(pc, ac.Get(5));

	pc = ac.PushCopy();
	AssertInt(84, pc->i1);
	AssertInt(33, pc->i2);
	AssertPointer(pc, ac.Get(6));

	AssertInt(7, ac.NumElements());

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
	TestArrayMinimalTemplateWithVirtualClass();

	TestStatistics();
}

