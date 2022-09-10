#include "BaseLib/GlobalMemory.h"
#include "BaseLib/MapLongLong.h"
#include "TestLib/Assert.h"


class CTestMapLongLong : public CMapLongLong
{
public:
	void InsertHoldingIntoSorted(void)
	{
		return CMapLongLong::InsertHoldingIntoSorted();
	}


	void GetInSorted(int iIndex, void** ppvKey, void** ppvData)
	{
		return CMapLongLong::GetInSorted(iIndex, ppvKey, ppvData);
	}
};


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapLongTemplate(void)
{
	CMapLongTemplate<double>	cMap;

	double	d;
	double	e;
	int64		i;

	cMap.Init(true);

	d = 1.0; cMap.Put((int64)d, &d);
	d = 2.0; cMap.Put((int64)d, &d);
	d = 3.0; cMap.Put((int64)d, &d);
	d = 4.0; cMap.Put((int64)d, &d);
	d = -1.0; cMap.Put((int64)d, &d);
	d = -2.0; cMap.Put((int64)d, &d);
	d = -3.0; cMap.Put((int64)d, &d);
	d = -4.0; cMap.Put((int64)d, &d);
	d = 0.0; cMap.Put((int64)d, &d);
	AssertLongLongInt(9, cMap.NumElements());

	AssertNull(cMap.Get(-5));
	e = -4.0; d = *cMap.Get((int64)e);
	AssertDouble(e, d, 2);
	e = -3.0; d = *cMap.Get((int64)e);
	AssertDouble(e, d, 2);
	e = -2.0; d = *cMap.Get((int64)e);
	AssertDouble(e, d, 2);
	e = -1.0; d = *cMap.Get((int64)e);
	AssertDouble(e, d, 2);
	e = 0.0; d = *cMap.Get((int64)e);
	AssertDouble(e, d, 2);
	e = 1.0; d = *cMap.Get((int64)e);
	AssertDouble(e, d, 2);
	e = 2.0; d = *cMap.Get((int64)e);
	AssertDouble(e, d, 2);
	e = 3.0; d = *cMap.Get((int64)e);
	AssertDouble(e, d, 2);
	e = 4.0; d = *cMap.Get((int64)e);
	AssertDouble(e, d, 2);
	e = 1.0; d = *cMap.Get((int64)e);
	AssertDouble(e, d, 2);
	e = 1.0; d = *cMap.Get((int64)e);
	AssertDouble(e, d, 2);
	AssertNull(cMap.Get(5));

	i = -4;
	AssertTrue(cMap.Remove(i));
	AssertLongLongInt(8, cMap.NumElements());
	AssertNull(cMap.Get(i));
	e = -3.0;
	d = *cMap.Get((int64)e);
	AssertDouble(e, d, 2);
	AssertFalse(cMap.Remove(i));

	i = -3;
	AssertTrue(cMap.Remove(i));
	AssertLongLongInt(7, cMap.NumElements());
	AssertNull(cMap.Get(i));
	e = -2.0;
	d = *cMap.Get((int64)e);
	AssertDouble(e, d, 2);
	AssertFalse(cMap.Remove(i));

	i = 3;
	AssertTrue(cMap.Remove(i));
	AssertLongLongInt(6, cMap.NumElements());
	AssertNull(cMap.Get(i));
	e = 4.0;
	d = *cMap.Get((int64)e);
	AssertDouble(e, d, 2);
	AssertFalse(cMap.Remove(i));

	i = 0;
	AssertTrue(cMap.Remove(i));
	AssertLongLongInt(5, cMap.NumElements());
	AssertNull(cMap.Get(i));
	e = 4.0;
	d = *cMap.Get((int64)e);
	AssertDouble(e, d, 2);
	i = 0;
	AssertFalse(cMap.Remove(i));

	i = 1;
	AssertTrue(cMap.Remove(i));
	AssertLongLongInt(4, cMap.NumElements());
	AssertNull(cMap.Get(i));
	e = -2.0;
	d = *cMap.Get((int64)e);
	AssertDouble(e, d, 2);
	AssertFalse(cMap.Remove(i));

	AssertTrue(cMap.Remove(-2));
	AssertTrue(cMap.Remove(-1));
	AssertTrue(cMap.Remove(4));
	AssertLongLongInt(1, cMap.NumElements());
	AssertTrue(cMap.Remove(2));
	AssertLongLongInt(0, cMap.NumElements());
	AssertFalse(cMap.Remove(2));

	cMap.Kill();
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapLongLong(void)
{
	CTestMapLongLong	cMap;
	int64				iResult;
	int64*				piKey;
	int64*				piValue;

	cMap.Init(true);

	cMap.Put(5, 15);
	cMap.Put(7, 17);

	iResult = *cMap.Get(5);
	AssertLongLongInt(15, iResult);

	cMap.Put(3, 13);
	AssertLongLongInt(3, cMap.NumElements());

	iResult = *cMap.Get(5);
	AssertLongLongInt(15, iResult);
	iResult = *cMap.Get(3);
	AssertLongLongInt(13, iResult);
	iResult = *cMap.Get(7);
	AssertLongLongInt(17, iResult);
	AssertNull(cMap.Get(1));

	AssertLongLongInt(0, cMap.GetArray()->GetSortedSize());
	AssertLongLongInt(3, cMap.GetArray()->GetHoldingSize());
	AssertLongLongInt(8, (*(SMNode**)cMap.GetArray()->GetInHolding(0, 0))->iKeySize);

	cMap.InsertHoldingIntoSorted();
	cMap.GetInSorted(0, (void**)&piKey, (void**)&piValue);
	AssertLongLongInt(3, *piKey);
	AssertLongLongInt(13, *piValue);

	cMap.GetInSorted(1, (void**)&piKey, (void**)&piValue);
	AssertLongLongInt(5, *piKey);
	AssertLongLongInt(15, *piValue);

	cMap.GetInSorted(2, (void**)&piKey, (void**)&piValue);
	AssertLongLongInt(7, *piKey);
	AssertLongLongInt(17, *piValue);

	cMap.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapLong(void)
{
	BeginTests();
	MemoryInit();
	FastFunctionsInit();

	TestMapLongTemplate();
	TestMapLongLong();

	FastFunctionsKill();
	MemoryKill();
	TestStatistics();
}

