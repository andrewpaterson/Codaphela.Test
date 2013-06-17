#include "StandardLib/Objects.h"
#include "TestLib/Assert.h"
#include "ObjectTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPointerNegation(void)
{
	Ptr<CTestObject>	pcObject;
	CPointerObject			pcBase;

	pcObject = OMalloc(CTestObject);
	AssertFalse(!pcObject);

	pcObject = NULL;
	AssertTrue(!pcObject);

	pcBase = OMalloc(CTestObject);
	AssertFalse(!pcBase);

	pcBase = NULL;
	AssertTrue(!pcBase);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPointer(void)
{
	BeginTests();
	ObjectsInit();

	TestPointerNegation();

	ObjectsKill();
	TestStatistics();
}

