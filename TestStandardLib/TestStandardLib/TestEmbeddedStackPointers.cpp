#include "StandardLib/Objects.h"
#include "StandardLib/PointerContainer.h"
#include "TestLib/Assert.h"
#include "ObjectTestSetup.h"
#include "EmbeddedObjectTestClasses.h"


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

	Ptr<CEmbeddedComplex> pComplex;
	pComplex = &cComplex;

	AssertInt(1234, pComplex->mai[0]);
	AssertInt(7890, pComplex->mai[1]);

	AssertInt(0, cComplex.GetDistToStack());

	pTest = OMalloc(CEmbeddedTest);
	pcTest = (CEmbeddedTest*)pTest.Object();

	pTest->Init();
	cComplex.mpTest = pTest;

	AssertInt(1, pcTest->GetDistToStack());
	
	pTest = NULL;
	AssertInt(1, pcTest->GetDistToStack());

	cComplex.Kill();

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestEmbeddedStackPointersEmbeddedDistDirect(void)
{
	ObjectsInit();

	CEmbeddedTest*		pTest;
	CEmbeddedComplex	cComplex;

	cComplex.Class();
	cComplex.Init();
	cComplex.mai[0] = 1234;
	cComplex.mai[1] = 7890;

	AssertInt(0, cComplex.GetDistToStack());

	Ptr<CEmbeddedComplex> pComplex;
	pComplex = &cComplex;

	AssertInt(1234, pComplex->mai[0]);
	AssertInt(7890, pComplex->mai[1]);

	AssertInt(0, cComplex.GetDistToStack());

	cComplex.mpTest = OMalloc(CEmbeddedTest)->Init();

	pTest = (CEmbeddedTest*)cComplex.mpTest.Object();
	AssertInt(1, pTest->GetDistToStack());

	cComplex.Kill();

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestEmbeddedStackPointers(void)
{
	BeginTests();

	TestEmbeddedStackPointersEmbeddedDistPassThruPointer();
	TestEmbeddedStackPointersEmbeddedDistDirect();

	TestStatistics();
}

