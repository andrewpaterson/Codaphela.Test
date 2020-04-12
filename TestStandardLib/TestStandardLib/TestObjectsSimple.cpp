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
		Ptr<CTestObject>	cTestPtr;

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
	Ptr<CTestObject>			pTest1;
	Ptr<CTestObject>			pTest2;
	STestObjectKilledNotifier	sKillNotifier1;
	STestObjectKilledNotifier	sKillNotifier2;

	ObjectsInit();

	pTest1 = OMalloc(CTestObject);
	pTest2 = OMalloc(CTestObject);

	AssertNotNull(&pTest1);
	AssertNotNull(&pTest2);

	pTest1->Init(&sKillNotifier1);
	pTest2->Init(&sKillNotifier2);
	AssertLongLongInt(2, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(0, gcObjects.NumIndiciesCached());

	pTest1->Kill();
	AssertLongLongInt(1, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(0, gcObjects.NumIndiciesCached());
	AssertTrue(sKillNotifier1.bKilled);

	pTest2->Kill();
	AssertLongLongInt(0, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(0, gcObjects.NumIndiciesCached());
	AssertTrue(sKillNotifier2.bKilled);

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectsSimple(void)
{
	BeginTests();

	TestObjectsCompilation();
	TestObjectFreeing();

	TestStatistics();
}

