#include "StandardLib/Objects.h"
#include "TestLib/Assert.h"
#include "ObjectTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestPointerNegation(void)
{
	CPointer<CTestObject>	pcObject;
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
	ObjectsInit(NULL);

	TestPointerNegation();

	ObjectsKill();
	TestStatistics();
}

