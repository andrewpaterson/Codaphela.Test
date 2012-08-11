#include "StandardLib/Objects.h"
#include "TestLib/Assert.h"
#include "ObjectTestClasses.h"
#include "TestObjects.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCompilation(void)
{
	if (FALSE)  //This is intentional.  This code must only be compiled (testing template compilation) not run.
	{
		CObjects				cObjects;
		CPointer<CTestObject>	cTestPtr;

		cTestPtr = cObjects.Add<CTestObject>();
		cTestPtr = cObjects.Get<CTestObject>("Invalid Name");
		cTestPtr = cObjects.Get<CTestObject>(INVALID_O_INDEX);
	}
	AssertTrue(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjects(void)
{
	BeginTests();
	ObjectsInit(NULL);

	TestCompilation();

	ObjectsKill();
	TestStatistics();
}

