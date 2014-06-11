#include "StandardLib/Objects.h"
#include "StandardLib/PointerContainer.h"
#include "TestLib/Assert.h"
#include "ObjectTestSetup.h"
#include "EmbeddedObjectTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestEmbeddedStackPointersEmbeddedDist(void)
{
	ObjectsInit();

	CEmbeddedComplex	cComplex;

	cComplex.Class();
	cComplex.Init();

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

	TestEmbeddedStackPointersEmbeddedDist();

	TestStatistics();
}

