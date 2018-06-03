#include "BaseLib/GlobalMemory.h"
#include "BaseLib/MapIntInt.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapIntTemplate(void)
{
	CMapIntTemplate<double>	cMap;

	double	d;
	double	e;
	int		i;

	cMap.Init(TRUE);

	d = 1.0; cMap.Put((int)d, &d);
	d = 2.0; cMap.Put((int)d, &d);
	d = 3.0; cMap.Put((int)d, &d);
	d = 4.0; cMap.Put((int)d, &d);
	d = -1.0; cMap.Put((int)d, &d);
	d = -2.0; cMap.Put((int)d, &d);
	d = -3.0; cMap.Put((int)d, &d);
	d = -4.0; cMap.Put((int)d, &d);
	d = 0.0; cMap.Put((int)d, &d);
	AssertInt(9, cMap.NumElements());

	AssertNull(cMap.Get(-5));
	e = -4.0; d = *cMap.Get((int)e);
	AssertDouble(e, d, 2);
	e = -3.0; d = *cMap.Get((int)e);
	AssertDouble(e, d, 2);
	e = -2.0; d = *cMap.Get((int)e);
	AssertDouble(e, d, 2);
	e = -1.0; d = *cMap.Get((int)e);
	AssertDouble(e, d, 2);
	e = 0.0; d = *cMap.Get((int)e);
	AssertDouble(e, d, 2);
	e = 1.0; d = *cMap.Get((int)e);
	AssertDouble(e, d, 2);
	e = 2.0; d = *cMap.Get((int)e);
	AssertDouble(e, d, 2);
	e = 3.0; d = *cMap.Get((int)e);
	AssertDouble(e, d, 2);
	e = 4.0; d = *cMap.Get((int)e);
	AssertDouble(e, d, 2);
	e = 1.0; d = *cMap.Get((int)e);
	AssertDouble(e, d, 2);
	e = 1.0; d = *cMap.Get((int)e);
	AssertDouble(e, d, 2);
	AssertNull(cMap.Get(5));

	i = -4;
	AssertTrue(cMap.Remove(i));
	AssertInt(8, cMap.NumElements());
	AssertNull(cMap.Get(i));
	e = -3.0; 
	d = *cMap.Get((int)e);
	AssertDouble(e, d, 2);
	AssertFalse(cMap.Remove(i));

	i = -3;
	AssertTrue(cMap.Remove(i));
	AssertInt(7, cMap.NumElements());
	AssertNull(cMap.Get(i));
	e = -2.0; 
	d = *cMap.Get((int)e);
	AssertDouble(e, d, 2);
	AssertFalse(cMap.Remove(i));

	i = 3;
	AssertTrue(cMap.Remove(i));
	AssertInt(6, cMap.NumElements());
	AssertNull(cMap.Get(i));
	e = 4.0; 
	d = *cMap.Get((int)e);
	AssertDouble(e, d, 2);
	AssertFalse(cMap.Remove(i));

	i = 0;
	AssertTrue(cMap.Remove(i));
	AssertInt(5, cMap.NumElements());
	AssertNull(cMap.Get(i));
	e = 4.0; 
	d = *cMap.Get((int)e);
	AssertDouble(e, d, 2);
	i = 0;
	AssertFalse(cMap.Remove(i));

	i = 1;
	AssertTrue(cMap.Remove(i));
	AssertInt(4, cMap.NumElements());
	AssertNull(cMap.Get(i));
	e = -2.0; 
	d = *cMap.Get((int)e);
	AssertDouble(e, d, 2);
	AssertFalse(cMap.Remove(i));

	AssertTrue(cMap.Remove(-2));
	AssertTrue(cMap.Remove(-1));
	AssertTrue(cMap.Remove(4));
	AssertInt(1, cMap.NumElements());
	AssertTrue(cMap.Remove(2));
	AssertInt(0, cMap.NumElements());
	AssertFalse(cMap.Remove(2));

	cMap.Kill();
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapIntInt(void)
{
	CMapIntInt	cMap;
	int			iResult;
	int*		piKey;
	int*		piValue;

	cMap.Init(TRUE);

	cMap.Put(5, 15);
	cMap.Put(7, 17);

	iResult = *cMap.Get(5);
	AssertInt(15, iResult);

	cMap.Put(3, 13);
	AssertInt(3, cMap.NumElements());

	iResult = *cMap.Get(5);
	AssertInt(15, iResult);
	iResult = *cMap.Get(3);
	AssertInt(13, iResult);
	iResult = *cMap.Get(7);
	AssertInt(17, iResult);
	AssertNull(cMap.Get(1));

	AssertInt(0, cMap.GetArray()->GetSortedSize());
	AssertInt(3, cMap.GetArray()->GetHoldingSize());
	AssertInt(4, (*(SMNode**)cMap.GetArray()->GetInHolding(0, 0))->iKeySize);

	cMap.InsertHoldingIntoSorted();
	cMap.GetInSorted(0, (void**)&piKey, (void**)&piValue);
	AssertInt(3, *piKey);
	AssertInt(13, *piValue);

	cMap.GetInSorted(1, (void**)&piKey, (void**)&piValue);
	AssertInt(5, *piKey);
	AssertInt(15, *piValue);

	cMap.GetInSorted(2, (void**)&piKey, (void**)&piValue);
	AssertInt(7, *piKey);
	AssertInt(17, *piValue);

	cMap.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapInt(void)
{
	BeginTests();
	MemoryInit();
	FastFunctionsInit();

	TestMapIntTemplate();
	TestMapIntInt();

	FastFunctionsKill();
	MemoryKill();
	TestStatistics();
}

