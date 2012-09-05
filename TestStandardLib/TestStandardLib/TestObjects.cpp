#include "StandardLib/Objects.h"
#include "TestLib/Assert.h"
#include "ObjectTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectsCompilation(void)
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
void TestObjectFreeing(void)
{
	CPointer<CTestObject>			pTest1;
	CPointer<CTestObject>			pTest2;
	STestObjectKilledNotifier		sKillNotifier1;
	STestObjectKilledNotifier		sKillNotifier2;

	ObjectsInit(NULL);


	pTest1 = OMalloc(CTestObject);
	pTest2 = OMalloc(CTestObject);

	pTest1->Init(&sKillNotifier1);
	pTest2->Init(&sKillNotifier2);
	AssertLongLongInt(2, gcObjects.NumMemoryIndexes());

	pTest1->Kill();
	AssertLongLongInt(1, gcObjects.NumMemoryIndexes());

	pTest2->Kill();
	AssertLongLongInt(0, gcObjects.NumMemoryIndexes());
	
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjects(void)
{
	BeginTests();

	TestObjectsCompilation();
	TestObjectFreeing();

	TestStatistics();
}

