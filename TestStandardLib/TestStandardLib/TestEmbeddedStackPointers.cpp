#include "BaseLib/GlobalMemory.h"
#include "StandardLib/Objects.h"
#include "StandardLib/PointerContainer.h"
#include "TestLib/Assert.h"
#include "ObjectTestSetup.h"
#include "ObjectTestClasses.h"
#include "EmbeddedObjectTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestEmbeddedStackPointersKill(void)
{
	ObjectsInit();

	CEmbeddedComplex			cComplex;
	STestObjectKilledNotifier	sKillNotifier;

	cComplex.Class();
	cComplex.Init();
	cComplex.mai[0] = 1234;
	cComplex.mai[1] = 7890;

	cComplex.mpTest = OMalloc(CTestObject)->Init(&sKillNotifier);
	AssertInt(0, cComplex.NumStackFroms());
	AssertInt(1, cComplex.mpTest->NumStackFroms());
	AssertLongLongInt(1, gcObjects.NumMemoryIndexes());

	cComplex.Kill();

	AssertTrue(sKillNotifier.bKilled);
	AssertLongLongInt(0, gcObjects.NumMemoryIndexes());
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestEmbeddedStackPointersDestructor(STestObjectKilledNotifier* psKillNotifier2, Ptr<CTestObject> pTest1)
{
	CTestObject					cTest2;

	cTest2.Class();
	cTest2.Init(psKillNotifier2);
	cTest2.mpTest = pTest1;
	cTest2.Kill();  //Kill has to be called manually - it's difficult to make the destructor call the right kill.
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestEmbeddedStackPointersDestructor(void)
{
	ObjectsInit();

	CTestObject					cTest1;
	STestObjectKilledNotifier	sKillNotifier1;
	STestObjectKilledNotifier	sKillNotifier2;

	cTest1.Class();
	cTest1.Init(&sKillNotifier1);
	sKillNotifier2.bKilled = FALSE;

	TestEmbeddedStackPointersDestructor(&sKillNotifier2, &cTest1);

	AssertTrue(sKillNotifier2.bKilled);
	AssertFalse(sKillNotifier1.bKilled);

	cTest1.Kill();

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestEmbeddedStackPointersEmbeddedDistPassThruPointer(void)
{
	ObjectsInit();

	CEmbeddedTest*		pcTest;
	CEmbeddedComplex	cComplex;
	Ptr<CEmbeddedTest>	pTest;
	
	cComplex.Class();
	cComplex.Init();
	cComplex.mai[0] = 1234;
	cComplex.mai[1] = 7890;

	AssertInt(0, cComplex.GetDistToStack());
	AssertInt(0, cComplex.NumStackFroms());

	Ptr<CEmbeddedComplex> pComplex;
	pComplex = &cComplex;

	AssertInt(1, cComplex.NumStackFroms());
	AssertInt(1234, pComplex->mai[0]);
	AssertInt(7890, pComplex->mai[1]);

	AssertInt(0, cComplex.GetDistToStack());

	pTest = OMalloc(CEmbeddedTest);
	pcTest = (CEmbeddedTest*)pTest.Object();

	pTest->Init();
	cComplex.mpTest = pTest;

	AssertInt(UNKNOWN_DIST_TO_STACK, pcTest->GetDistToStack());
	AssertInt(2, pComplex->mpTest->NumStackFroms());
	AssertInt(1, cComplex.NumStackFroms());

	pTest = NULL;
	AssertInt(UNKNOWN_DIST_TO_STACK, pcTest->GetDistToStack());
	AssertLongLongInt(1, gcObjects.NumMemoryIndexes());
	AssertInt(1, pComplex->mpTest->NumStackFroms());
	AssertInt(1, cComplex.NumStackFroms());

	cComplex.Kill();

	AssertLongLongInt(0, gcObjects.NumMemoryIndexes());

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestEmbeddedStackPointersEmbeddedDistDirect(void)
{
	ObjectsInit();

	CEmbeddedTest*		pcTest;
	CEmbeddedComplex	cComplex;

	cComplex.Class();
	cComplex.Init();
	cComplex.mai[0] = 1234;
	cComplex.mai[1] = 7890;

	AssertInt(0, cComplex.GetDistToStack());
	AssertInt(0, cComplex.NumStackFroms());

	Ptr<CEmbeddedComplex> pComplex;
	pComplex = &cComplex;

	AssertInt(1, cComplex.NumStackFroms());
	AssertInt(1234, pComplex->mai[0]);
	AssertInt(7890, pComplex->mai[1]);

	AssertInt(0, cComplex.GetDistToStack());

	cComplex.mpTest = OMalloc(CEmbeddedTest)->Init();
	AssertInt(1, pComplex->mpTest->NumStackFroms());
	AssertInt(1, cComplex.NumStackFroms());

	pcTest = (CEmbeddedTest*)cComplex.mpTest.Object();
	AssertInt(UNKNOWN_DIST_TO_STACK, pcTest->GetDistToStack());
	AssertLongLongInt(1, gcObjects.NumMemoryIndexes());

	cComplex.Kill();

	AssertLongLongInt(0, gcObjects.NumMemoryIndexes());

	ObjectsKill();
}


void TestEmbeddedStackPointersComplex(Ptr<CEmbeddedComplex> pComplexOnStack1, Ptr<CEmbeddedComplex> pComplexOnStack2)
{

}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestEmbeddedStackPointersComplex(void)
{
	ObjectsInit();

	CEmbeddedComplex			cComplexOnStack1;
	CEmbeddedComplex			cComplexOnStack2;
	Ptr<CTestObject>			pTestObject1;
	STestObjectKilledNotifier	sKillNotifier1;
	Ptr<CTestObject>			pTestObject2;
	STestObjectKilledNotifier	sKillNotifier2;

	cComplexOnStack1.Class();
	cComplexOnStack2.Class();
	cComplexOnStack1.Init();
	cComplexOnStack2.Init();

	pTestObject1 = OMalloc(CTestObject);
	pTestObject1->Init(&sKillNotifier1);
	pTestObject2 = OMalloc(CTestObject);
	pTestObject2->Init(&sKillNotifier2);

	AssertInt(0, cComplexOnStack1.GetDistToStack());
	AssertInt(0, cComplexOnStack1.NumStackFroms());
	AssertInt(0, cComplexOnStack2.GetDistToStack());
	AssertInt(0, cComplexOnStack2.NumStackFroms());

	cComplexOnStack1.mpTest = &cComplexOnStack2;
	cComplexOnStack1.mcSimple.mpTest = &cComplexOnStack2;
	cComplexOnStack1.mcContainer.mcOne.mpTest = pTestObject1;
	cComplexOnStack2.mcContainer.mcOne.mpTest = pTestObject1;

	AssertInt(0, cComplexOnStack1.GetDistToStack());
	AssertInt(0, cComplexOnStack1.NumStackFroms());
	AssertInt(3, cComplexOnStack1.NumPointerTos());
	AssertInt(0, cComplexOnStack2.GetDistToStack());
	AssertInt(2, cComplexOnStack2.NumStackFroms());
	AssertInt(1, cComplexOnStack2.NumPointerTos());

	AssertFalse(sKillNotifier1.bKilled);
	AssertFalse(sKillNotifier2.bKilled);
	TestEmbeddedStackPointersComplex(&cComplexOnStack1, &cComplexOnStack2);
	AssertFalse(sKillNotifier1.bKilled);
	AssertFalse(sKillNotifier2.bKilled);

	AssertInt(0, cComplexOnStack1.GetDistToStack());
	AssertInt(0, cComplexOnStack1.NumStackFroms());
	AssertInt(0, cComplexOnStack2.GetDistToStack());
	AssertInt(2, cComplexOnStack2.NumStackFroms());

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestEmbeddedStackPointers(void)
{
	BeginTests();
	MemoryInit();

	TestEmbeddedStackPointersKill();
	TestEmbeddedStackPointersDestructor();
	TestEmbeddedStackPointersEmbeddedDistPassThruPointer();
	TestEmbeddedStackPointersEmbeddedDistDirect();
	TestEmbeddedStackPointersComplex();

	MemoryKill();
	TestStatistics();
}

