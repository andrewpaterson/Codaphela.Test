#include "TestLib/Assert.h"


struct TestPrimitiveLongStruct
{
public:
	int64_t lli1;
	int64_t lli2;
};


struct TestPrimitivePointerArrayStruct
{
public:
	TestPrimitiveLongStruct*	aps[256];
};


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPrimitiveTypesPointerArray(void)
{
	AssertInt(16, sizeof(TestPrimitiveLongStruct));
	AssertInt(4, sizeof(TestPrimitiveLongStruct*));
	AssertInt(256 * sizeof(TestPrimitiveLongStruct*), sizeof(TestPrimitivePointerArrayStruct));

	TestPrimitiveLongStruct*			p1;
	TestPrimitiveLongStruct*			p2;
	TestPrimitivePointerArrayStruct		sPointers;
	TestPrimitiveLongStruct				sLongs1;
	TestPrimitiveLongStruct				sLongs2;

	memset(&sPointers, 0, sizeof(TestPrimitivePointerArrayStruct));
	p1 = sPointers.aps[0];
	p2 = sPointers.aps[1];

	AssertNull(p1);
	AssertNull(p2);

	sLongs1.lli1 = 1LL;
	sLongs1.lli2 = 3LL;
	sLongs2.lli1 = 2LL;
	sLongs2.lli2 = 4LL;

	sPointers.aps[0] = &sLongs1;
	sPointers.aps[1] = &sLongs2;
	p1 = sPointers.aps[0];
	p2 = sPointers.aps[1];

	AssertPointer(&sLongs1, p1);
	AssertPointer(&sLongs2, p2);
	AssertLongLongInt(1LL, p1->lli1);
	AssertLongLongInt(2LL, p2->lli1);
	AssertLongLongInt(3LL, sPointers.aps[0]->lli2);
	AssertLongLongInt(4LL, sPointers.aps[1]->lli2);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPrimitiveTypesSizes(void)
{
	AssertInt(1, sizeof(char));
	AssertInt(2, sizeof(wchar_t));
	AssertInt(4, sizeof(int));
	AssertInt(8, sizeof(int64_t));
	AssertInt(4, sizeof(void*));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPrimitiveTypes(void)
{
	BeginTests();

	TestPrimitiveTypesSizes();
	TestPrimitiveTypesPointerArray();

	TestStatistics();
}

