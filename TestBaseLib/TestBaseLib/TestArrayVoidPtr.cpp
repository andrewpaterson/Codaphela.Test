#include "BaseLib/ArrayVoidPtr.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayVoidPtrGet(void)
{
	CArrayVoidPtr	cArray;
	int				iValue;
	int*			pi;

	iValue = 55;

	cArray.Init();
	cArray.Add(&iValue);

	cArray.Get(0, (void**)&pi);
	AssertInt(55, *pi);

	pi = (int*)cArray.GetPtr(0);
	AssertInt(55, *pi);

	cArray.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayVoidPtr(void)
{
	BeginTests();

	TestArrayVoidPtrGet();

	TestStatistics();
}

