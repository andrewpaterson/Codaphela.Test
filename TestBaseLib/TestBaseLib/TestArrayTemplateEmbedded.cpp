#include "BaseLib/ArrayTemplateEmbedded.h"
#include "TestLib/Assert.h"
#include "ArrayTemplateTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayTemplateEmbeddedAdd(void)
{
	CArrayTemplateEmbedded<int, 5>	cArray;
	int*					pi;
	int*					piEmbeddedData;

	cArray.Init();
	AssertInt(0, cArray.NumElements());
	piEmbeddedData = cArray.GetData();

	pi = cArray.Add();
	*pi = 7;
	AssertInt(1, cArray.NumElements());
	AssertPointer(piEmbeddedData, cArray.GetData());

	pi = cArray.Get(0);
	AssertInt(7,* pi);

	cArray.AddNum(3);
	AssertInt(4, cArray.NumElements());
	AssertPointer(piEmbeddedData, cArray.GetData());
	*cArray.Get(1) = 6;
	*cArray.Get(2) = 5;
	*cArray.Get(3) = 4;

	pi = cArray.Add();
	*pi = 22;
	AssertInt(5, cArray.NumElements());
	AssertPointer(piEmbeddedData, cArray.GetData());
	AssertInt(7, *cArray.Get(0));
	AssertInt(22, *cArray.Get(4));

	pi = cArray.Add();
	*pi = 20;
	AssertInt(6, cArray.NumElements());
	AssertFalse(piEmbeddedData == cArray.GetData());

	AssertInt(7, *cArray.Get(0));
	AssertInt(6, *cArray.Get(1));
	AssertInt(5, *cArray.Get(2));
	AssertInt(4, *cArray.Get(3));
	AssertInt(22, *cArray.Get(4));
	AssertInt(20, *cArray.Get(5));

	AssertTrue(cArray.TestInternalConsistency());
	cArray.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayTemplateEmbeddedRemoveAt(void)
{
	CArrayTemplateEmbedded<int, 5>	cArray;
	int*					piEmbeddedData;
	int*					pi;
	int						i;

	cArray.Init();
	piEmbeddedData = cArray.GetData();
	cArray.AddNum(6);
	AssertFalse(piEmbeddedData == cArray.GetData());
	AssertInt(6, cArray.NumElements());

	*cArray.Get(0) = 7;
	*cArray.Get(1) = 6;
	*cArray.Get(2) = 5;
	*cArray.Get(3) = 4;
	*cArray.Get(4) = 22;
	*cArray.Get(5) = 20;

	AssertInt(7, *cArray.Get(0));
	AssertInt(6, *cArray.Get(1));
	AssertInt(5, *cArray.Get(2));
	AssertInt(4, *cArray.Get(3));
	AssertInt(22, *cArray.Get(4));
	AssertInt(20, *cArray.Get(5));
	
	cArray.Resize(5);
	AssertPointer(piEmbeddedData, cArray.GetData());
	AssertInt(5, cArray.NumElements());

	AssertInt(7, *cArray.Get(0));
	AssertInt(6, *cArray.Get(1));
	AssertInt(5, *cArray.Get(2));
	AssertInt(4, *cArray.Get(3));
	AssertInt(22, *cArray.Get(4));

	pi = cArray.Add();
	*pi = 20;
	AssertInt(6, cArray.NumElements());
	AssertFalse(piEmbeddedData == cArray.GetData());

	cArray.RemoveAt(2);
	AssertPointer(piEmbeddedData, cArray.GetData());
	AssertInt(5, cArray.NumElements());

	AssertInt(7, *cArray.Get(0));
	AssertInt(6, *cArray.Get(1));
	AssertInt(4, *cArray.Get(2));
	AssertInt(22, *cArray.Get(3));
	AssertInt(20, *cArray.Get(4));

	cArray.RemoveAt(3);
	AssertPointer(piEmbeddedData, cArray.GetData());
	AssertInt(4, cArray.NumElements());

	AssertInt(7, *cArray.Get(0));
	AssertInt(6, *cArray.Get(1));
	AssertInt(4, *cArray.Get(2));
	AssertInt(20, *cArray.Get(3));

	i = 8;
	cArray.InsertAt(&i, 4);
	AssertInt(5, cArray.NumElements());
	AssertInt(8, *cArray.Get(4));

	i = 9;
	cArray.InsertAt(&i, 5);
	AssertFalse(piEmbeddedData == cArray.GetData());
	AssertInt(6, cArray.NumElements());
	AssertInt(8, *cArray.Get(4));
	AssertInt(9, *cArray.Get(5));

	cArray.RemoveAt(5);
	AssertPointer(piEmbeddedData, cArray.GetData());
	AssertInt(5, cArray.NumElements());

	AssertInt(7, *cArray.Get(0));
	AssertInt(6, *cArray.Get(1));
	AssertInt(4, *cArray.Get(2));
	AssertInt(20, *cArray.Get(3));
	AssertInt(8, *cArray.Get(4));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayTemplateEmbeddedRemove(void)
{
	CArrayTemplateEmbedded<int*, 2>	cArray;

	int						i1;
	int						i2;
	int						i3;

	int*					pi1;
	int*					pi2;
	int*					pi3;

	int**					ppi1;
	int**					ppi2;

	int						iIndex;

	i1 = 1;
	i2 = 2;
	i3 = 3;

	pi1 = &i1;
	pi2 = &i2;
	pi3 = &i3;

	cArray.Init();
	ppi1 = cArray.Add(&pi1);
	ppi2 = cArray.Add(&pi2);

	iIndex = cArray.GetIndex(&pi1);
	AssertInt(-1, iIndex);
	iIndex = cArray.GetIndex(ppi1);
	AssertInt(0, iIndex);
	iIndex = cArray.GetIndex(&pi2);
	AssertInt(-1, iIndex);
	iIndex = cArray.GetIndex(ppi2);
	AssertInt(1, iIndex);

	iIndex = cArray.Find(&pi1);
	AssertInt(0, iIndex);
	iIndex = cArray.Find(ppi1);
	AssertInt(0, iIndex);
	iIndex = cArray.Find(&pi2);
	AssertInt(1, iIndex);
	iIndex = cArray.Find(ppi2);
	AssertInt(1, iIndex);

	cArray.Remove(&pi1);
	iIndex = cArray.Find(&pi1);
	AssertInt(-1, iIndex);
	AssertPointer(pi2, *cArray.Get(0));
}


typedef CArrayTemplateEmbedded<CTestOverridenArrayTemplateItem, 3> CTestArrayTemplateEmbedded;


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayTemplateEmbeddedSizeof(void)
{
	AssertInt(36, 3 * sizeof(CTestOverridenArrayTemplateItem));
	AssertInt(24, sizeof(CArrayTemplate<CTestOverridenArrayTemplateItem>));

	AssertInt(sizeof(SArrayTemplateHeader) + 3 * sizeof(CTestOverridenArrayTemplateItem), sizeof(CTestArrayTemplateEmbedded));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayTemplateEmbeddedAllocationWithVirtualClass(void)
{
	CTestArrayTemplateEmbedded			ac;
	CTestOverridenArrayTemplateItem*	pc;

	ac.Init();

	pc = ac.Add();
	pc->Init(5);
	AssertInt(5, pc->i1);
	AssertInt(33, pc->i2);

	pc = ac.InsertAt(0);
	pc->Init(6);
	AssertInt(6, pc->i1);
	AssertInt(33, pc->i2);

	pc = ac.Add();
	pc->Init(7);
	AssertInt(7, pc->i1);
	AssertInt(33, pc->i2);
	AssertPointer(ac.Get(2), pc);

	pc = ac.Add();
	pc->Init(8);
	AssertInt(8, pc->i1);
	AssertInt(33, pc->i2);
	AssertPointer(ac.Get(3), pc);

	AssertInt(4, ac.NumElements());

	pc = ac.InsertAt(3);
	pc->Init(9);
	AssertInt(9, pc->i1);
	AssertInt(33, pc->i2);
	AssertPointer(ac.Get(3), pc);
	pc = ac.Get(4);
	AssertInt(8, pc->i1);
	AssertInt(33, pc->i2);

	ac.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayTemplateEmbedded(void)
{
	BeginTests();
	FastFunctionsInit();

	TestArrayTemplateEmbeddedAdd();
	TestArrayTemplateEmbeddedRemoveAt();
	TestArrayTemplateEmbeddedRemove();
	TestArrayTemplateEmbeddedSizeof();
	TestArrayTemplateEmbeddedAllocationWithVirtualClass();

	FastFunctionsKill();
	TestStatistics();
}

