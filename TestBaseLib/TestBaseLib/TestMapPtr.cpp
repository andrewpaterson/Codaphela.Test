#include "BaseLib/MapIntInt.h"
#include "BaseLib/MapPtrPtr.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapPtrPtr(void)
{
	CMapPtrPtr	cMap;
	void*		pvValue;
	void**		ppvKey;
	void**		ppvValue;
	void*		pvk1;
	void*		pvv1;
	void*		pvk2;
	void*		pvv2;
	void*		pvk3;
	void*		pvv3;

	pvk1 = (void*)0x00324789;
	pvv1 = (void*)0x00723764;
	pvk2 = (void*)0x008a4562;
	pvv2 = (void*)0x002ff462;
	pvk3 = (void*)0x008a627d;
	pvv3 = (void*)0x00198201;


	cMap.Init(16);

	cMap.Put(pvk1, pvv1);
	cMap.Put(pvk2, pvv2);

	pvValue = cMap.GetWithKey(pvk1);
	AssertPointer(pvv1, pvValue);

	cMap.Put(pvk3, pvv3);
	AssertInt(3, cMap.NumElements());

	pvValue = cMap.GetWithKey(pvk1);
	AssertPointer(pvv1, pvValue);
	pvValue = cMap.GetWithKey(pvk3);
	AssertPointer(pvv3, pvValue);
	pvValue = cMap.GetWithKey(pvk2);
	AssertPointer(pvv2, pvValue);

	cMap.GetAtIndex(0, &ppvKey, &ppvValue);
	AssertPointer(pvk1, *ppvKey);
	AssertPointer(pvv1, *ppvValue);

	cMap.GetAtIndex(1, &ppvKey, &ppvValue);
	AssertPointer(pvk2, *ppvKey);
	AssertPointer(pvv2, *ppvValue);

	cMap.GetAtIndex(2, &ppvKey, &ppvValue);
	AssertPointer(pvk3, *ppvKey);
	AssertPointer(pvv3, *ppvValue);

	cMap.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapPtrTemplate(void)
{
	CMapPtrTemplate<int>	cMap;
	char					c1;
	char					c2;
	int						i1;
	int						i2;
	int*					piTest;
	
	c1 = 'A';
	c2 = 'A';
	i1 = 1;
	i2 = 2;

	cMap.Init(10);
	cMap.Put(&c1, &i1);
	cMap.Put(&c2, &i2);

	AssertInt(2, cMap.NumElements());
	piTest = cMap.GetWithKey(&c1);
	AssertInt(i1, *piTest);
	piTest = cMap.GetWithKey(&c2);
	AssertInt(i2, *piTest);

	cMap.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapPtr(void)
{
	BeginTests();

	TestMapPtrTemplate();
	TestMapPtrPtr();

	TestStatistics();
}

