#include "BaseLib/ArrayTemplateEmbeddedPtr.h"
#include "TestLib/Assert.h"
#include "ArrayTemplateTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayTemplateEmbeddedPtrAdd(void)
{
	CArrayTemplateEmbeddedPtr<int, 5>	cArray;
	int		ia, ib, ic;
	int		iSize;
	int*	pi;

	ia = 1;
	ib = 2;
	ic = 3;

	iSize = sizeof(CArrayTemplateEmbeddedPtr<int, 6>);

	cArray.Init();
	cArray.Add(&ia);
	cArray.Add(&ib);
	cArray.Add(&ic);

	pi = cArray.GetPtr(0);
	AssertInt(1, *pi);
	pi = cArray.GetPtr(1);
	AssertInt(2, *pi);
	pi = cArray.GetPtr(2);
	AssertInt(3, *pi);

	cArray.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayTemplateEmbeddedPtr(void)
{
	BeginTests();
	FastFunctionsInit();

	TestArrayTemplateEmbeddedPtrAdd();

	FastFunctionsKill();
	TestStatistics();
}

