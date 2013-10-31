#include "StandardLib/Objects.h"
#include "StandardLib/Root.h"
#include "StandardLib/PointerContainer.h"
#include "StandardLib/Set.h"
#include "TestLib/Assert.h"
#include "ObjectTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDistToStackSimpleOneStep(void)
{
	ObjectsInit();

	Ptr<CNamedPointerContainer>	p1 = ONMalloc(CNamedPointerContainer, "Pointer A")->Init();
	Ptr<CNamedPointerContainer>	p2 = ONMalloc(CNamedPointerContainer, "Pointer B")->Init();
	Ptr<CNamedPointerContainer> p3 = ONMalloc(CNamedPointerContainer, "Pointer C")->Init();
	AssertInt(0, p2->NumHeapFroms());

	//  
	//  x   x   x
	//  |   |   |
	//  |   |   |
	//  p1  p2  p3
	//  .   .   .
	//  .   .   .
	//

	p3->mp = p2;
	AssertInt(1, p2->NumHeapFroms());

	//  
	//      x
	//      |
	//      |
	//  x   p2
	//  |   . \
	//  |   .  \
	//  p1  .   p3
	//  .   .   .
	//  .   .   .
	//

	p3 = NULL;
	AssertInt(0, p2->NumHeapFroms());

	//  
	//  x   x 
	//  |   | 
	//  |   | 
	//  p1  p2
	//  .   . 
	//  .   . 
	//

	gcObjects.ValidateConsistency();

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDistToStackSimpleTwoStep(void)
{
	ObjectsInit();

	Ptr<CNamedPointerContainer>	p1 = ONMalloc(CNamedPointerContainer, "Pointer A")->Init();
	Ptr<CNamedPointerContainer>	p2 = ONMalloc(CNamedPointerContainer, "Pointer B")->Init();
	Ptr<CNamedPointerContainer> p3 = ONMalloc(CNamedPointerContainer, "Pointer C")->Init();
	AssertInt(0, p2->NumHeapFroms());

	p3->mp = p2;
	AssertInt(1, p2->NumHeapFroms());

	p3->mp = NULL;
	AssertInt(0, p2->NumHeapFroms());
	AssertInt(3, (int)gcObjects.NumMemoryIndexes());
	p3 = NULL;

	AssertInt(2, (int)gcObjects.NumMemoryIndexes());
	AssertTrue(gcObjects.Contains("Pointer A"));
	AssertTrue(gcObjects.Contains("Pointer B"));

	gcObjects.ValidateConsistency();

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDistToStackCyclicWithStackPointerA(void)
{
	ObjectsInit();

	CDistToRootCalculator		cDistToRootCalculator;
	CDistToStackCalculator		cDistToStackCalculator;
	CDistCalculatorParameters	cDistParameters;
	CNamedPointerContainer*		pc1;
	CNamedPointerContainer*		pc2;
	CNamedPointerContainer*		pc3;

	Ptr<CNamedPointerContainer>	p1 = ONMalloc(CNamedPointerContainer, "Pointer A")->Init();
	Ptr<CNamedPointerContainer>	p2 = ONMalloc(CNamedPointerContainer, "Pointer B")->Init();
	Ptr<CNamedPointerContainer>	p3 = ONMalloc(CNamedPointerContainer, "Pointer C")->Init();
	p1->mp = p2;
	p2->mp = p3;
	p3->mp = p1;

	Ptr<CRoot> pRoot = ORoot();
	Ptr<CNamedPointerContainer>	p0 = ONMalloc(CNamedPointerContainer, "Test Helper")->Init(p1);
	pRoot->Add(p0);

	Ptr<CPointerContainer> pStack = OMalloc(CPointerContainer)->Init(p2);

	AssertInt(2, p0->GetDistToRoot());
	AssertInt(3, p1->GetDistToRoot());
	AssertInt(4, p2->GetDistToRoot());
	AssertInt(5, p3->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pStack->GetDistToRoot());

	pStack = p1;
	pc1 = &p1;
	pc2 = &p2;
	pc3 = &p3;
	p1 = NULL;
	p2 = NULL;
	p3 = NULL;

	gcObjects.ValidateConsistency();

	p0->mp.UnsafeClearObject();
	pc1->TestRemoveHeapFrom(p0.BaseObject());

	cDistParameters.Init();
	cDistToRootCalculator.Init();
	cDistToRootCalculator.AddFromChanged(pc1);
	cDistToRootCalculator.Calculate(&cDistParameters);
	cDistToRootCalculator.Kill();

	AssertInt(UNATTACHED_DIST_TO_ROOT, pc1->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pc2->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pc3->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pStack->GetDistToRoot());

	gcObjects.ValidateConsistency();

	cDistToStackCalculator.Init();
	cDistToStackCalculator.Calculate(&cDistParameters);

	AssertInt(3, cDistParameters.NumDetachedFromRoot());
	AssertInt(0, cDistParameters.NumCompletelyDetached());

	cDistToStackCalculator.Kill();
	cDistParameters.Kill();

	gcObjects.ValidateConsistency();

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDistToStackCyclicWithStackPointerB(void)
{
	ObjectsInit();

	CDistToRootCalculator		cDistToRootCalculator;
	CDistToStackCalculator		cDistToStackCalculator;
	CDistCalculatorParameters	cDistParameters;
	CNamedPointerContainer*		pc1;
	CNamedPointerContainer*		pc2;
	CNamedPointerContainer*		pc3;

	Ptr<CNamedPointerContainer>	p1 = ONMalloc(CNamedPointerContainer, "Pointer A")->Init();
	Ptr<CNamedPointerContainer>	p2 = ONMalloc(CNamedPointerContainer, "Pointer B")->Init();
	Ptr<CNamedPointerContainer>	p3 = ONMalloc(CNamedPointerContainer, "Pointer C")->Init();
	p1->mp = p2;
	p2->mp = p3;
	p3->mp = p1;

	Ptr<CRoot> pRoot = ORoot();
	Ptr<CNamedPointerContainer>	p0 = ONMalloc(CNamedPointerContainer, "Test Helper")->Init(p1);
	pRoot->Add(p0);

	Ptr<CPointerContainer> pStack = OMalloc(CPointerContainer)->Init(p1);

	AssertInt(2, p0->GetDistToRoot());
	AssertInt(3, p1->GetDistToRoot());
	AssertInt(4, p2->GetDistToRoot());
	AssertInt(5, p3->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pStack->GetDistToRoot());

	pStack = p1;
	pc1 = &p1;
	pc2 = &p2;
	pc3 = &p3;
	p1 = NULL;
	p2 = NULL;
	p3 = NULL;

	p0->mp.UnsafeClearObject();
	pc1->TestRemoveHeapFrom(p0.BaseObject());

	cDistParameters.Init();
	cDistToRootCalculator.Init();
	cDistToRootCalculator.AddFromChanged(pc1);
	cDistToRootCalculator.Calculate(&cDistParameters);
	cDistToRootCalculator.Kill();

	AssertInt(UNATTACHED_DIST_TO_ROOT, pc1->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pc2->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pc3->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pStack->GetDistToRoot());

	cDistToStackCalculator.Init();
	cDistToStackCalculator.Calculate(&cDistParameters);

	AssertInt(3, cDistParameters.NumDetachedFromRoot());
	AssertInt(0, cDistParameters.NumCompletelyDetached());

	cDistToStackCalculator.Kill();
	cDistParameters.Kill();

	gcObjects.ValidateConsistency();

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDistToStackCyclicWithStackPointerC(void)
{
	ObjectsInit();

	CDistToRootCalculator		cDistToRootCalculator;
	CDistToStackCalculator		cDistToStackCalculator;
	CDistCalculatorParameters	cDistParameters;
	CNamedPointerContainer*		pc1;
	CNamedPointerContainer*		pc2;
	CNamedPointerContainer*		pc3;

	Ptr<CNamedPointerContainer>	p1 = ONMalloc(CNamedPointerContainer, "Pointer A")->Init();
	Ptr<CNamedPointerContainer>	p2 = ONMalloc(CNamedPointerContainer, "Pointer B")->Init();
	Ptr<CNamedPointerContainer>	p3 = ONMalloc(CNamedPointerContainer, "Pointer C")->Init();
	p1->mp = p2;
	p2->mp = p3;
	p3->mp = p1;

	Ptr<CRoot> pRoot = ORoot();
	Ptr<CNamedPointerContainer>	p0 = ONMalloc(CNamedPointerContainer, "Test Helper")->Init(p1);
	pRoot->Add(p0);

	Ptr<CPointerContainer> pStack = OMalloc(CPointerContainer)->Init(p3);

	AssertInt(2, p0->GetDistToRoot());
	AssertInt(3, p1->GetDistToRoot());
	AssertInt(4, p2->GetDistToRoot());
	AssertInt(5, p3->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pStack->GetDistToRoot());

	pStack = p1;
	pc1 = &p1;
	pc2 = &p2;
	pc3 = &p3;
	p1 = NULL;
	p2 = NULL;
	p3 = NULL;

	p0->mp.UnsafeClearObject();
	pc1->TestRemoveHeapFrom(p0.BaseObject());

	cDistParameters.Init();
	cDistToRootCalculator.Init();
	cDistToRootCalculator.AddFromChanged(pc1);
	cDistToRootCalculator.Calculate(&cDistParameters);
	cDistToRootCalculator.Kill();

	AssertInt(UNATTACHED_DIST_TO_ROOT, pc1->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pc2->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pc3->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pStack->GetDistToRoot());

	cDistToStackCalculator.Init();
	cDistToStackCalculator.Calculate(&cDistParameters);

	AssertInt(3, cDistParameters.NumDetachedFromRoot());
	AssertInt(0, cDistParameters.NumCompletelyDetached());

	cDistToStackCalculator.Kill();
	cDistParameters.Kill();

	gcObjects.ValidateConsistency();

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDistToStackCyclicWithoutStackPointer(void)
{
	ObjectsInit();

	CDistToRootCalculator		cDistToRootCalculator;
	CDistToStackCalculator		cDistToStackCalculator;
	CDistCalculatorParameters	cDistParameters;
	CNamedPointerContainer*		pc1;
	CNamedPointerContainer*		pc2;
	CNamedPointerContainer*		pc3;

	Ptr<CNamedPointerContainer>	p1 = ONMalloc(CNamedPointerContainer, "Pointer A")->Init();
	Ptr<CNamedPointerContainer>	p2 = ONMalloc(CNamedPointerContainer, "Pointer B")->Init();
	Ptr<CNamedPointerContainer>	p3 = ONMalloc(CNamedPointerContainer, "Pointer C")->Init();
	p1->mp = p2;
	p2->mp = p3;
	p3->mp = p1;

	Ptr<CRoot> pRoot = ORoot();
	Ptr<CNamedPointerContainer>	p0 = ONMalloc(CNamedPointerContainer, "Test Helper")->Init(p1);
	pRoot->Add(p0);

	//
	// p2 --> p3
	//  ^     /
	//   \   /
	//    \ v
	//    p1
	//     ^
	//     |
	//     |
	//    p0
	//     ^
	//     |
	//     |
	//    ...
	//   pRoot
	//

	AssertInt(2, p0->GetDistToRoot());
	AssertInt(3, p1->GetDistToRoot());
	AssertInt(4, p2->GetDistToRoot());
	AssertInt(5, p3->GetDistToRoot());

	pc1 = &p1;
	pc2 = &p2;
	pc3 = &p3;
	p1 = NULL;
	p2 = NULL;
	p3 = NULL;

	AssertInt(2, pc1->NumHeapFroms());
	AssertInt(0, pc1->NumStackFroms());

	p0->mp.UnsafeClearObject();
	pc1->TestRemoveHeapFrom(p0.BaseObject());

	cDistParameters.Init();
	cDistToRootCalculator.Init();
	cDistToRootCalculator.AddFromChanged(pc1);
	cDistToRootCalculator.Calculate(&cDistParameters);
	cDistToRootCalculator.Kill();

	AssertInt(UNATTACHED_DIST_TO_ROOT, pc1->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pc2->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pc3->GetDistToRoot());

	cDistToStackCalculator.Init();
	cDistToStackCalculator.Calculate(&cDistParameters);

	AssertInt(3, cDistParameters.NumDetachedFromRoot());
	AssertInt(3, cDistParameters.NumCompletelyDetached());
	AssertPointer(pc1, cDistParameters.GetCompletelyDetached(0));
	AssertPointer(pc3, cDistParameters.GetCompletelyDetached(1));
	AssertPointer(pc2, cDistParameters.GetCompletelyDetached(2));

	cDistToStackCalculator.Kill();
	cDistParameters.Kill();
	cDistParameters.Kill();

	gcObjects.ValidateConsistency();

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDistToStackSplitRootAndStack(void)
{
	ObjectsInit();

	CDistToRootCalculator		cDistToRootCalculator;
	CDistToStackCalculator		cDistToStackCalculator;
	CDistCalculatorParameters	cDistParameters;
	CTestObject*				pcTestC;
	CTestObject*				pcTestL1;
	CTestObject*				pcTestL2;
	CTestObject*				pcTestR1;
	CTestObject*				pcTestR2;
	CNamedPointerContainer*		pcC;
	CNamedPointerContainer*		pcL1;

	Ptr<CTestObject>	pTestC = OMalloc(CTestObject)->Init();
	Ptr<CTestObject>	pTestL1 = OMalloc(CTestObject)->Init();
	Ptr<CTestObject>	pTestL2 = OMalloc(CTestObject)->Init();
	Ptr<CTestObject>	pTestR1 = OMalloc(CTestObject)->Init();
	Ptr<CTestObject>	pTestR2 = OMalloc(CTestObject)->Init();

	pTestL1->mpTest = pTestL2;
	pTestR1->mpTest = pTestR2;
	pTestC->mpTest = pTestL1;
	pTestC->mpObject = pTestR1;

	Ptr<CRoot> pRoot = ORoot();
	Ptr<CNamedPointerContainer>	pC = ONMalloc(CNamedPointerContainer, "Test Helper Center")->Init(pTestC);
	Ptr<CNamedPointerContainer>	pL1 = ONMalloc(CNamedPointerContainer, "Test Helper Left")->Init(pTestL1);
	pRoot->Add(pC);
	pRoot->Add(pL1);

	Ptr<CPointerContainer> pStack = OMalloc(CPointerContainer)->Init();
	pStack = pTestR1;

	AssertInt(3, pTestC->GetDistToRoot());
	AssertInt(3, pTestL1->GetDistToRoot());
	AssertInt(4, pTestR1->GetDistToRoot());
	AssertInt(4, pTestL2->GetDistToRoot());
	AssertInt(5, pTestR2->GetDistToRoot());

	pcTestC = &pTestC;
	pcTestL1 = &pTestL1;
	pcTestL2 = &pTestL2;
	pcTestR1 = &pTestR1;
	pcTestR2 = &pTestR2;
	pcC = &pC;
	pcL1 = &pL1;

	pTestC = NULL;
	pTestL1 = NULL;
	pTestL2 = NULL;
	pTestR1 = NULL;
	pTestR2 = NULL;
	pC = NULL;
	pL1 = NULL;

	pcC->mp.UnsafeClearObject();
	pcTestC->TestRemoveHeapFrom(pcC);

	cDistParameters.Init();
	cDistToRootCalculator.Init();
	cDistToRootCalculator.AddFromChanged(pcTestC);
	cDistToRootCalculator.Calculate(&cDistParameters);
	cDistToRootCalculator.Kill();

	AssertInt(UNATTACHED_DIST_TO_ROOT, pcTestC->GetDistToRoot());
	AssertInt(3, pcTestL1->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pcTestR1->GetDistToRoot());
	AssertInt(4, pcTestL2->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pcTestR2->GetDistToRoot());

	AssertInt(3, cDistParameters.NumTouched());

	cDistToStackCalculator.Init();
	cDistToStackCalculator.Calculate(&cDistParameters);

	AssertInt(3, cDistParameters.NumDetachedFromRoot());
	AssertInt(1, cDistParameters.NumCompletelyDetached());
	AssertPointer(pcTestC, cDistParameters.GetCompletelyDetached(0));

	cDistToStackCalculator.Kill();
	cDistParameters.Kill();

	gcObjects.ValidateConsistency();

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDistToStackSetWithoutStackPointers(void)
{
	ObjectsInit();

	CDistToRootCalculator		cDistToRootCalculator;
	CDistToStackCalculator		cDistToStackCalculator;
	CDistCalculatorParameters	cDistParameters;
	STestObjectKilledNotifier	sKillNotifier;
	Ptr<CSet<CTestObject>>		pSet;
	Ptr<CRoot>					pRoot;
	Ptr<CPointerContainer>		pContainer;
	Ptr<CTestObject>			pTest;
	CSet<CTestObject>*			pcSet;
	CPointerContainer*			pcContainer;
	CTestObject*				pcTest;

	pTest = OMalloc(CTestObject)->Init(&sKillNotifier);
	pSet = OMalloc(CSet<CTestObject>)->Init();
	pSet->Add(pTest);

	pContainer = OMalloc(CPointerContainer)->Init();
	pContainer->mp = pSet;
	pRoot = ORoot();
	pRoot->Add(pContainer);

	pcSet = &pSet;
	pcContainer = &pContainer;
	pcTest = &pTest;
	pSet = NULL;
	pContainer = NULL;
	pTest = NULL;

	pcContainer->mp.UnsafeClearObject();
	pcSet->TestRemoveHeapFrom(pcContainer);

	cDistParameters.Init();
	cDistToRootCalculator.Init();
	cDistToRootCalculator.AddFromChanged(pcSet);
	cDistToRootCalculator.Calculate(&cDistParameters);
	cDistToRootCalculator.Kill();
	cDistToStackCalculator.Init();
	cDistToStackCalculator.Calculate(&cDistParameters);

	AssertInt(2, cDistParameters.NumDetachedFromRoot());
	AssertInt(2, cDistParameters.NumCompletelyDetached());
	AssertPointer(pcSet, cDistParameters.GetCompletelyDetached(0));
	AssertPointer(pcTest, cDistParameters.GetCompletelyDetached(1));

	cDistToStackCalculator.Kill();

	AssertLongLongInt(5, gcObjects.NumMemoryIndexes());
	gcObjects.Remove(cDistParameters.GetCompletelyDetachedArray());
	AssertLongLongInt(3, gcObjects.NumMemoryIndexes());

	cDistParameters.Kill();

	gcObjects.ValidateConsistency();

	ObjectsKill();
}




//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDistToStackSetWithStackPointers(void)
{
	ObjectsInit();

	CDistToRootCalculator		cDistToRootCalculator;
	CDistToStackCalculator		cDistToStackCalculator;
	CDistCalculatorParameters	cDistParameters;
	STestObjectKilledNotifier	sKillNotifier;
	Ptr<CSet<CTestObject>>		pSet;
	Ptr<CRoot>					pRoot;
	Ptr<CPointerContainer>		pContainer;
	Ptr<CTestObject>			pTest;
	CSet<CTestObject>*			pcSet;
	CPointerContainer*			pcContainer;
	CTestObject*				pcTest;

	pTest = OMalloc(CTestObject)->Init(&sKillNotifier);
	pSet = OMalloc(CSet<CTestObject>)->Init();
	pSet->Add(pTest);

	pContainer = OMalloc(CPointerContainer)->Init();
	pContainer->mp = pSet;
	pRoot = ORoot();
	pRoot->Add(pContainer);

	pcSet = &pSet;
	pcContainer = &pContainer;
	pcTest = &pTest;
	pSet = NULL;
	pContainer = NULL;

	pcContainer->mp.UnsafeClearObject();
	pcSet->TestRemoveHeapFrom(pcContainer);

	cDistParameters.Init();
	cDistToRootCalculator.Init();
	cDistToRootCalculator.AddFromChanged(pcSet);
	cDistToRootCalculator.Calculate(&cDistParameters);
	cDistToRootCalculator.Kill();
	cDistToStackCalculator.Init();
	cDistToStackCalculator.Calculate(&cDistParameters);

	AssertInt(2, cDistParameters.NumDetachedFromRoot());
	AssertInt(1, cDistParameters.NumCompletelyDetached());
	AssertPointer(pcSet, cDistParameters.GetCompletelyDetached(0));

	cDistToStackCalculator.Kill();

	AssertLongLongInt(5, gcObjects.NumMemoryIndexes());
	gcObjects.Remove(cDistParameters.GetCompletelyDetachedArray());
	AssertLongLongInt(4, gcObjects.NumMemoryIndexes());

	cDistParameters.Kill();

	gcObjects.ValidateConsistency();

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDistToStackSetBroken(void)
{
	CDistToRootCalculator		cDistToRootCalculator;
	CDistToStackCalculator		cDistToStackCalculator;
	CDistCalculatorParameters	cDistParameters;

	STestObjectKilledNotifier	sKilled1;
	STestObjectKilledNotifier	sKilled2;
	STestObjectKilledNotifier	sKilled3;

	Ptr<CRoot>					pRoot;
	Ptr<CTestObject>			pTest1;
	Ptr<CTestObject>			pTest2;
	Ptr<CTestObject>			pTest3;

	CObject*					pcTest1;
	CObject*					pcTest2;
	CObject*					pcTest3;
	CSetObject*					pcSet;

	ObjectsInit();

	pTest1 = OMalloc(CTestObject);
	pTest1->Init(&sKilled1);

	pTest3 = OMalloc(CTestObject);
	pTest3->Init(&sKilled3);

	pRoot = ORoot();

	pRoot->Add(pTest1);
	pRoot->Add(pTest3);

	pTest2 = OMalloc(CTestObject);
	pTest2->Init(&sKilled2);

	pTest1->mpTest = pTest2;
	AssertInt(3, pTest2->GetDistToRoot());

	pTest3->mpTest = pTest2;
	AssertInt(3, pTest2->GetDistToRoot());

	//           
	//           pTest2[5](4)
	//            ^ ^
	//           /   \
	//          /     \
	//         /       \
	//   pTest1[1](3)  pTest3[2](3)
	//         ^       ^
	//          \     /
	//           \   /
	//            \ /
	//            ...
	//           pRoot[3](0) 
	//    

	pcTest1 = &pTest1;
	pcTest3 = &pTest3;
	pcTest2 = &pTest2;
	pTest1 = NULL;
	pTest2 = NULL;
	pTest3 = NULL;

	AssertLongLongInt(5, gcObjects.NumMemoryIndexes());
	AssertInt(3, pcTest2->GetDistToRoot());
	AssertInt(2, pcTest2->NumHeapFroms());
	
	pcSet = pRoot->TestGetSet();
	pcSet->UnsafeRemove(pcTest3);
	pcTest3->TestRemoveHeapFrom(pcSet);

	AssertInt(2, pcTest2->NumHeapFroms());

	cDistParameters.Init();

	cDistToRootCalculator.Init();
	cDistToRootCalculator.AddFromChanged(pcTest3);
	cDistToRootCalculator.Calculate(&cDistParameters);
	AssertInt(3, pcTest2->GetDistToRoot());
	cDistToRootCalculator.Kill();

	cDistToStackCalculator.Init();
	cDistToStackCalculator.Calculate(&cDistParameters);

	AssertInt(1, cDistParameters.NumDetachedFromRoot());
	AssertInt(1, cDistParameters.NumCompletelyDetached());
	AssertPointer(pcTest3, cDistParameters.GetCompletelyDetached(0));

	cDistToStackCalculator.Kill();

	AssertLongLongInt(5, gcObjects.NumMemoryIndexes());
	gcObjects.Remove(cDistParameters.GetCompletelyDetachedArray());
	AssertLongLongInt(4, gcObjects.NumMemoryIndexes());

	cDistParameters.Kill();

	AssertFalse(sKilled1.bKilled);
	AssertTrue( sKilled3.bKilled);
	AssertFalse(sKilled2.bKilled);

	gcObjects.ValidateConsistency();

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDistToStack(void)
{
	BeginTests();

	TestDistToStackSimpleTwoStep();
	TestDistToStackSimpleOneStep();
	TestDistToStackCyclicWithStackPointerA();
	TestDistToStackCyclicWithStackPointerB();
	TestDistToStackCyclicWithStackPointerC();
	TestDistToStackCyclicWithoutStackPointer();
	TestDistToStackSplitRootAndStack();
	TestDistToStackSetWithoutStackPointers();
	TestDistToStackSetWithStackPointers();
	TestDistToStackSetBroken();

	TestStatistics();
}

