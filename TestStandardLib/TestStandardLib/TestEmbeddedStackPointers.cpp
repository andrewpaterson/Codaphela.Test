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


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestEmbeddedStackPointers(void)
{
	BeginTests();

	TestEmbeddedStackPointersKill();
	TestEmbeddedStackPointersEmbeddedDistPassThruPointer();
	TestEmbeddedStackPointersEmbeddedDistDirect();

	TestStatistics();
}

