#include "BaseLib/GlobalMemory.h"
#include "BaseLib/MapIntInt.h"
#include "BaseLib/MapPtrPtr.h"
#include "BaseLib/MapPtrPrimitiveTemplate.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapPtrPtr(void)
{
	CMapPtrPtr		cMap;
	void*			pvValue;
	void**			ppvKey;
	void**			ppvValue;
	void*			pvk1;
	void*			pvv1;
	void*			pvk2;
	void*			pvv2;
	void*			pvk3;
	void*			pvv3;
	SMapIterator	sIter;
	BOOL			bResult;

	pvk1 = (void*)0x00324789;
	pvv1 = (void*)0x00723764;
	pvk2 = (void*)0x008a4562;
	pvv2 = (void*)0x002ff462;
	pvk3 = (void*)0x008a627d;
	pvv3 = (void*)0x00198201;


	cMap.Init(&gcSystemAllocator, 16);

	cMap.Put(pvk1, pvv1);
	cMap.Put(pvk2, pvv2);

	pvValue = cMap.Get(pvk1);
	AssertPointer(pvv1, pvValue);

	cMap.Put(pvk3, pvv3);
	AssertInt(3, cMap.NumElements());

	pvValue = cMap.Get(pvk1);
	AssertPointer(pvv1, pvValue);
	pvValue = cMap.Get(pvk3);
	AssertPointer(pvv3, pvValue);
	pvValue = cMap.Get(pvk2);
	AssertPointer(pvv2, pvValue);

	bResult = cMap.StartIteration(&sIter, (void**)&ppvKey, (void**)&ppvValue);
	AssertTrue(bResult);
	AssertPointer(pvk1, *ppvKey);
	AssertPointer(pvv1, *ppvValue);

	bResult = cMap.Iterate(&sIter, (void**)&ppvKey, (void**)&ppvValue);
	AssertTrue(bResult);
	AssertPointer(pvk2, *ppvKey);
	AssertPointer(pvv2, *ppvValue);

	bResult = cMap.Iterate(&sIter, (void**)&ppvKey, (void**)&ppvValue);
	AssertTrue(bResult);
	AssertPointer(pvk3, *ppvKey);
	AssertPointer(pvv3, *ppvValue);

	bResult = cMap.Iterate(&sIter, (void**)&ppvKey, (void**)&ppvValue);
	AssertFalse(bResult);

	cMap.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapPtrPrimitiveTemplateLong(void)
{
	CMapPtrPrimitiveTemplate<long long>		cMapPtrLong;
	char									c1;
	char									c2;
	char									c3;
	char									c4;

	c1 = c2 = c3 = c4 = ' ';

	cMapPtrLong.Init();
	cMapPtrLong.Put(&c1, 1LL);
	cMapPtrLong.Put(&c2, 2LL);
	cMapPtrLong.Put(&c3, 3LL);
	cMapPtrLong.Put(&c4, 4LL);

	AssertLongLongInt(1LL, cMapPtrLong.Get(&c1));
	AssertLongLongInt(2LL, cMapPtrLong.Get(&c2));
	AssertLongLongInt(3LL, cMapPtrLong.Get(&c3));
	AssertLongLongInt(4LL, cMapPtrLong.Get(&c4));

	cMapPtrLong.Remove(&c2);
	AssertInt(3, cMapPtrLong.NumElements());

	*cMapPtrLong.Put(&c3) = 5LL;
	AssertLongLongInt(5LL, cMapPtrLong.Get(&c3));
	AssertInt(3, cMapPtrLong.NumElements());

	cMapPtrLong.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapPtrPrimitiveTemplateInt(void)
{
	CMapPtrPrimitiveTemplate<int>	cMapPtrInt;
	char							c1;
	char							c2;
	char							c3;
	char							c4;

	c1 = c2 = c3 = c4 = ' ';

	cMapPtrInt.Init();
	cMapPtrInt.Put(&c1, 1);
	cMapPtrInt.Put(&c2, 2);
	cMapPtrInt.Put(&c3, 3);
	cMapPtrInt.Put(&c4, 4);

	AssertInt(1, cMapPtrInt.Get(&c1));
	AssertInt(2, cMapPtrInt.Get(&c2));
	AssertInt(3, cMapPtrInt.Get(&c3));
	AssertInt(4, cMapPtrInt.Get(&c4));

	cMapPtrInt.Remove(&c2);
	AssertInt(3, cMapPtrInt.NumElements());

	*cMapPtrInt.Put(&c3) = 5;
	AssertInt(5, cMapPtrInt.Get(&c3));
	AssertInt(3, cMapPtrInt.NumElements());

	cMapPtrInt.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapPtrPrimitiveTemplateUnsignedChar(void)
{
	CMapPtrPrimitiveTemplate<unsigned char>	cMapPtrUnsignedChar;
	char									c1;
	char									c2;
	char									c3;
	char									c4;

	c1 = c2 = c3 = c4 = ' ';

	cMapPtrUnsignedChar.Init();
	cMapPtrUnsignedChar.Put(&c1, 1);
	cMapPtrUnsignedChar.Put(&c2, 2);
	cMapPtrUnsignedChar.Put(&c3, 3);
	cMapPtrUnsignedChar.Put(&c4, 4);

	AssertChar(1, cMapPtrUnsignedChar.Get(&c1));
	AssertChar(2, cMapPtrUnsignedChar.Get(&c2));
	AssertChar(3, cMapPtrUnsignedChar.Get(&c3));
	AssertChar(4, cMapPtrUnsignedChar.Get(&c4));

	cMapPtrUnsignedChar.Remove(&c2);
	AssertInt(3, cMapPtrUnsignedChar.NumElements());

	*cMapPtrUnsignedChar.Put(&c3) = 5;
	AssertChar(5, cMapPtrUnsignedChar.Get(&c3));
	AssertInt(3, cMapPtrUnsignedChar.NumElements());

	cMapPtrUnsignedChar.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapPtr(void)
{
	BeginTests();
	MemoryInit();
	FastFunctionsInit();

	TestMapPtrPtr();
	TestMapPtrPrimitiveTemplateLong();
	TestMapPtrPrimitiveTemplateInt();
	TestMapPtrPrimitiveTemplateUnsignedChar();

	FastFunctionsKill();
	MemoryKill();
	TestStatistics();
}

