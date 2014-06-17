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
	AssertInt(0, p1->NumHeapFroms());
	AssertInt(0, p3->NumHeapFroms());
	AssertInt(UNKNOWN_DIST_TO_STACK, p1.Object()->GetDistToStack());
	AssertInt(UNKNOWN_DIST_TO_STACK, p2.Object()->GetDistToStack());
	AssertInt(UNKNOWN_DIST_TO_STACK, p3.Object()->GetDistToStack());

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

	gcObjects.ValidateObjectsConsistency();

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
	AssertInt(3, (int)gcObjects.NumMemoryIndexes());
	AssertInt(0, p2->NumHeapFroms());

	//
	//     x
	//     |
	//     |
	//     p2      x 
	//    /  .     | 
	//   /    .    | 
	//  p3	  .    p1
	//  . 	  .    .  
	//  . 	  .    . 
	//

	p3->mp = p2;
	AssertInt(1, p2->NumHeapFroms());

	p3->mp = NULL;

	//  
	//  x   x   x
	//  |   |   |
	//  |   |   |
	//  p1  p2  p3
	//  .   .   .
	//  .   .   .
	//

	AssertInt(0, p2->NumHeapFroms());
	AssertInt(3, (int)gcObjects.NumMemoryIndexes());
	p3 = NULL;

	//  
	//  x   x 
	//  |   | 
	//  |   | 
	//  p1  p2
	//  .   . 
	//  .   . 
	//

	AssertInt(2, (int)gcObjects.NumMemoryIndexes());
	AssertTrue(gcObjects.Contains("Pointer A"));
	AssertTrue(gcObjects.Contains("Pointer B"));

	gcObjects.ValidateObjectsConsistency();

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDistToStackSimpleHeap(void)
{
	ObjectsInit();

	CNamedPointerContainer*		pc2;
	CNamedPointerContainer*		pc3;

	CDistCalculatorParameters	cParameters;
	CDistToStackCalculator		cDistToStackCalculator;

	Ptr<CNamedPointerContainer>	p1 = ONMalloc(CNamedPointerContainer, "Pointer A")->Init();

	Ptr<CNamedPointerContainer>	p2 = ONMalloc(CNamedPointerContainer, "Pointer B")->Init();
	Ptr<CNamedPointerContainer> p3 = ONMalloc(CNamedPointerContainer, "Pointer C")->Init();
	AssertInt(3, (int)gcObjects.NumMemoryIndexes());
	AssertInt(0, p2->NumHeapFroms());

	AssertInt(1, p2->NumStackFroms());
	AssertInt(1, p1->NumStackFroms());
	AssertInt(1, p3->NumStackFroms());

	//
	//     x
	//     |
	//     |
	//     p2      x 
	//    /  .     | 
	//   /    .    | 
	//  p3	  .    p1
	//  . 	  .    .  
	//  . 	  .    . 
	//

	p3->mp = p2;
	AssertInt(1, p2->NumHeapFroms());
	AssertInt(1, p2->NumStackFroms());

	pc3 = &p3;
	pc2 = &p2;

	AssertInt(UNKNOWN_DIST_TO_STACK, pc2->GetDistToStack());
	AssertInt(UNKNOWN_DIST_TO_STACK, pc3->GetDistToStack());

	p2.BaseObject()->TestRemoveStackFrom(p2.This());
	p2.UnsafeClearObject();

	AssertInt(1, pc2->NumHeapFroms());
	AssertInt(0, pc2->NumStackFroms());
	AssertInt(1, p1->NumStackFroms());
	AssertInt(1, p3->NumStackFroms());

	cParameters.Init();
	cDistToStackCalculator.Calculate(pc2, &cParameters);

	//
	//  x
	//  |
	//  |
	//  p2     x 
	//  |      | 
	//  |      | 
	//  p3	   p1
	//  . 	   . 
	//  . 	   . 
	//

	AssertInt(2, pc2->GetDistToStack());
	AssertInt(1, pc3->GetDistToStack());

	cParameters.Kill();

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDistToStackRootCyclicWithStackPointerA(void)
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

	gcObjects.ValidateObjectsConsistency();

	p0->mp.UnsafeClearObject();
	pc1->TestRemoveHeapFrom(p0.BaseObject());

	cDistParameters.Init();
	cDistToRootCalculator.Calculate(pc1, &cDistParameters);

	AssertInt(UNATTACHED_DIST_TO_ROOT, pc1->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pc2->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pc3->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pStack->GetDistToRoot());

	cDistToStackCalculator.CalculateFromTouched(&cDistParameters);

	AssertInt(3, cDistParameters.NumDetachedFromRoot());
	AssertInt(0, cDistParameters.NumCompletelyDetached());

	cDistParameters.ClearTouchedFlags();
	cDistParameters.Kill();

	gcObjects.ValidateObjectsConsistency();

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDistToStackRootCyclicWithStackPointerB(void)
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
	cDistToRootCalculator.Calculate(pc1, &cDistParameters);

	AssertInt(UNATTACHED_DIST_TO_ROOT, pc1->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pc2->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pc3->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pStack->GetDistToRoot());

	cDistToStackCalculator.CalculateFromTouched(&cDistParameters);
	cDistParameters.ClearTouchedFlags();

	AssertInt(3, cDistParameters.NumDetachedFromRoot());
	AssertInt(0, cDistParameters.NumCompletelyDetached());

	cDistParameters.Kill();

	gcObjects.ValidateObjectsConsistency();

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDistToStackRootCyclicWithStackPointerC(void)
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
	cDistToRootCalculator.Calculate(pc1, &cDistParameters);
	
	AssertInt(UNATTACHED_DIST_TO_ROOT, pc1->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pc2->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pc3->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pStack->GetDistToRoot());
	
	cDistToStackCalculator.CalculateFromTouched(&cDistParameters);
	cDistParameters.ClearTouchedFlags();

	AssertInt(3, cDistParameters.NumDetachedFromRoot());
	AssertInt(0, cDistParameters.NumCompletelyDetached());

	cDistParameters.Kill();

	gcObjects.ValidateObjectsConsistency();

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDistToStackRootCyclicWithoutStackPointer(void)
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
	cDistToRootCalculator.Calculate(pc1, &cDistParameters);

	AssertInt(UNATTACHED_DIST_TO_ROOT, pc1->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pc2->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pc3->GetDistToRoot());
	
	cDistToStackCalculator.CalculateFromTouched(&cDistParameters);
	cDistParameters.ClearTouchedFlags();

	AssertInt(3, cDistParameters.NumDetachedFromRoot());
	AssertInt(3, cDistParameters.NumCompletelyDetached());
	AssertPointer(pc1, cDistParameters.GetCompletelyDetached(0));
	AssertPointer(pc3, cDistParameters.GetCompletelyDetached(1));
	AssertPointer(pc2, cDistParameters.GetCompletelyDetached(2));

	cDistParameters.Kill();

	gcObjects.ValidateObjectsConsistency();

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
	cDistToRootCalculator.Calculate(pcTestC, &cDistParameters);

	AssertInt(UNATTACHED_DIST_TO_ROOT, pcTestC->GetDistToRoot());
	AssertInt(3, pcTestL1->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pcTestR1->GetDistToRoot());
	AssertInt(4, pcTestL2->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pcTestR2->GetDistToRoot());

	AssertInt(3, cDistParameters.NumTouched());

	cDistToStackCalculator.CalculateFromTouched(&cDistParameters);
	cDistParameters.ClearTouchedFlags();

	AssertInt(3, cDistParameters.NumDetachedFromRoot());
	AssertInt(1, cDistParameters.NumCompletelyDetached());
	AssertPointer(pcTestC, cDistParameters.GetCompletelyDetached(0));


	cDistParameters.Kill();

	gcObjects.ValidateObjectsConsistency();

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
	cDistToRootCalculator.Calculate(pcSet, &cDistParameters);
	cDistToStackCalculator.CalculateFromTouched(&cDistParameters);
	cDistParameters.ClearTouchedFlags();

	AssertInt(2, cDistParameters.NumDetachedFromRoot());
	AssertInt(2, cDistParameters.NumCompletelyDetached());
	AssertPointer(pcSet, cDistParameters.GetCompletelyDetached(0));
	AssertPointer(pcTest, cDistParameters.GetCompletelyDetached(1));

	AssertLongLongInt(5, gcObjects.NumMemoryIndexes());
	gcObjects.Remove(cDistParameters.GetCompletelyDetachedArray());
	AssertLongLongInt(3, gcObjects.NumMemoryIndexes());

	cDistParameters.Kill();

	gcObjects.ValidateObjectsConsistency();

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
	
	cDistToRootCalculator.Calculate(pcSet, &cDistParameters);
	cDistToStackCalculator.CalculateFromTouched(&cDistParameters);
	cDistParameters.ClearTouchedFlags();

	AssertInt(2, cDistParameters.NumDetachedFromRoot());
	AssertInt(1, cDistParameters.NumCompletelyDetached());
	AssertPointer(pcSet, cDistParameters.GetCompletelyDetached(0));



	AssertLongLongInt(5, gcObjects.NumMemoryIndexes());
	gcObjects.Remove(cDistParameters.GetCompletelyDetachedArray());
	AssertLongLongInt(4, gcObjects.NumMemoryIndexes());

	cDistParameters.Kill();

	gcObjects.ValidateObjectsConsistency();

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
	cDistToRootCalculator.Calculate(pcTest3, &cDistParameters);
	AssertInt(3, pcTest2->GetDistToRoot());

	cDistToStackCalculator.CalculateFromTouched(&cDistParameters);
	cDistParameters.ClearTouchedFlags();

	AssertInt(1, cDistParameters.NumDetachedFromRoot());
	AssertInt(1, cDistParameters.NumCompletelyDetached());
	AssertPointer(pcTest3, cDistParameters.GetCompletelyDetached(0));

	AssertLongLongInt(5, gcObjects.NumMemoryIndexes());
	gcObjects.Remove(cDistParameters.GetCompletelyDetachedArray());
	AssertLongLongInt(4, gcObjects.NumMemoryIndexes());

	cDistParameters.Kill();

	AssertFalse(sKilled1.bKilled);
	AssertTrue( sKilled3.bKilled);
	AssertFalse(sKilled2.bKilled);

	gcObjects.ValidateObjectsConsistency();

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDistToStackNoStackHeapFromBroken(void)
{
	ObjectsInit();

	STestObjectKilledNotifier	sNotifier1;
	STestObjectKilledNotifier	sNotifier2;
	CTestObject*				pcTest1;
	CTestObject*				pcTest2;

	Ptr<CTestObject> pTest1 = OMalloc(CTestObject)->Init(&sNotifier1);
	Ptr<CTestObject> pTest2 = OMalloc(CTestObject)->Init(&sNotifier2);

	pTest2->mpTest = pTest1;

	//
	//    pTest1
	//      ^ ^
	//      |  .
	//      |   .
	//      |
	//    pTest2
	//        ^
	//         .
	//          .
	//

	pcTest2 = (CTestObject*)pTest2.Object();
	pcTest1 = (CTestObject*)pTest1.Object();

	pTest1 = NULL;  //pTest1 should not be killed here, even though it has no stack froms.  
					//It still has a heap from that has a stack from.

	AssertFalse(sNotifier1.bKilled);
	AssertFalse(sNotifier2.bKilled);
	AssertInt(1, pcTest1->NumHeapFroms());
	AssertInt(0, pcTest1->NumStackFroms());
	AssertInt(0, pcTest1->NumPointerTos());
	AssertInt(0, pcTest2->NumHeapFroms());
	AssertInt(1, pcTest2->NumStackFroms());
	AssertInt(1, pcTest2->NumPointerTos());

	ObjectsKill();
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDistToStackCyclicWithScenarioA(void)
{
	ObjectsInit();

	CTestObject*				pcTest1;
	CTestTriPointerObject*		pcTest2;
	CTestTriPointerObject*		pcTest3;
	CTestObject*				pcTest4;
	CTestObject*				pcTest5;

	CDistCalculatorParameters	cParameters;
	CDistToStackCalculator		cDistToStackCalculator;

	Ptr<CTestObject> pTest1 = OMalloc(CTestObject)->Init();
	Ptr<CTestTriPointerObject> pTest2 = OMalloc(CTestTriPointerObject)->Init();
	Ptr<CTestTriPointerObject> pTest3 = OMalloc(CTestTriPointerObject)->Init();
	Ptr<CTestObject> pTest4 = OMalloc(CTestObject)->Init();
	Ptr<CTestObject> pTest5 = OMalloc(CTestObject)->Init();

	pcTest1 = &pTest1;
	pcTest2 = &pTest2;
	pcTest3 = &pTest3;
	pcTest4 = &pTest4;
	pcTest5 = &pTest5;

	pTest1->mpTest = pTest2;
	pTest1->mpObject = pTest3;
	pTest2->mpObject1 = pTest1;
	pTest2->mpObject2 = pTest3;
	pTest2->mpObject3 = pTest4;
	pTest3->mpObject1 = pTest1;
	pTest3->mpObject2 = pTest2;
	pTest3->mpObject3 = pTest5;

	pcTest2->TestRemoveStackFrom(pTest2.This());
	pcTest3->TestRemoveStackFrom(pTest3.This());
	pcTest4->TestRemoveStackFrom(pTest4.This());
	pcTest5->TestRemoveStackFrom(pTest5.This());
	pTest2.UnsafeClearObject();
	pTest3.UnsafeClearObject();
	pTest4.UnsafeClearObject();
	pTest5.UnsafeClearObject();

	//
	//  pTest4   pTest5
	//    |         |
	//    |         |
	//  pTest2===pTest3
	//     \\     //
	//      \\   //
	//       \\ //
	//       pTest1
	//         . 
	//         . 
	//

	//Test from pTest1
	AssertInt(UNKNOWN_DIST_TO_STACK, pcTest1->GetDistToStack());
	AssertInt(UNKNOWN_DIST_TO_STACK, pcTest2->GetDistToStack());
	AssertInt(UNKNOWN_DIST_TO_STACK, pcTest3->GetDistToStack());
	AssertInt(UNKNOWN_DIST_TO_STACK, pcTest4->GetDistToStack());
	AssertInt(UNKNOWN_DIST_TO_STACK, pcTest5->GetDistToStack());

	cParameters.Init();
	cDistToStackCalculator.Calculate(pcTest1, &cParameters);
	
	AssertInt(1, pcTest1->GetDistToStack());
	AssertInt(2, pcTest2->GetDistToStack());
	AssertInt(2, pcTest3->GetDistToStack());
	AssertInt(3, pcTest4->GetDistToStack());
	AssertInt(3, pcTest5->GetDistToStack());

	cDistToStackCalculator.ResetObjectsToUnknownDistToStack(&cParameters);
	cParameters.Kill();

	//Test from pTest2
	AssertInt(UNKNOWN_DIST_TO_STACK, pcTest1->GetDistToStack());
	AssertInt(UNKNOWN_DIST_TO_STACK, pcTest2->GetDistToStack());
	AssertInt(UNKNOWN_DIST_TO_STACK, pcTest3->GetDistToStack());
	AssertInt(UNKNOWN_DIST_TO_STACK, pcTest4->GetDistToStack());
	AssertInt(UNKNOWN_DIST_TO_STACK, pcTest5->GetDistToStack());

	cParameters.Init();
	cDistToStackCalculator.Calculate(pcTest2, &cParameters);

	AssertInt(1, pcTest1->GetDistToStack());
	AssertInt(2, pcTest2->GetDistToStack());
	AssertInt(2, pcTest3->GetDistToStack());
	AssertInt(3, pcTest4->GetDistToStack());
	AssertInt(3, pcTest5->GetDistToStack());

	cDistToStackCalculator.ResetObjectsToUnknownDistToStack(&cParameters);
	cParameters.Kill();

	//Test from pTest3
	AssertInt(UNKNOWN_DIST_TO_STACK, pcTest1->GetDistToStack());
	AssertInt(UNKNOWN_DIST_TO_STACK, pcTest2->GetDistToStack());
	AssertInt(UNKNOWN_DIST_TO_STACK, pcTest3->GetDistToStack());
	AssertInt(UNKNOWN_DIST_TO_STACK, pcTest4->GetDistToStack());
	AssertInt(UNKNOWN_DIST_TO_STACK, pcTest5->GetDistToStack());

	cParameters.Init();
	cDistToStackCalculator.Calculate(pcTest3, &cParameters);

	AssertInt(1, pcTest1->GetDistToStack());
	AssertInt(2, pcTest2->GetDistToStack());
	AssertInt(2, pcTest3->GetDistToStack());
	AssertInt(3, pcTest4->GetDistToStack());
	AssertInt(3, pcTest5->GetDistToStack());

	cDistToStackCalculator.ResetObjectsToUnknownDistToStack(&cParameters);
	cParameters.Kill();

	//Test from pTest4
	AssertInt(UNKNOWN_DIST_TO_STACK, pcTest1->GetDistToStack());
	AssertInt(UNKNOWN_DIST_TO_STACK, pcTest2->GetDistToStack());
	AssertInt(UNKNOWN_DIST_TO_STACK, pcTest3->GetDistToStack());
	AssertInt(UNKNOWN_DIST_TO_STACK, pcTest4->GetDistToStack());
	AssertInt(UNKNOWN_DIST_TO_STACK, pcTest5->GetDistToStack());

	cParameters.Init();
	cDistToStackCalculator.Calculate(pcTest4, &cParameters);

	AssertInt(1, pcTest1->GetDistToStack());
	AssertInt(2, pcTest2->GetDistToStack());
	AssertInt(2, pcTest3->GetDistToStack());
	AssertInt(3, pcTest4->GetDistToStack());
	AssertInt(UNKNOWN_DIST_TO_STACK, pcTest5->GetDistToStack());  //Removing a stack pointer to 4 should be unable to effect 5 in any way.

	cDistToStackCalculator.ResetObjectsToUnknownDistToStack(&cParameters);
	cParameters.Kill();

	//Test from pTest5
	AssertInt(UNKNOWN_DIST_TO_STACK, pcTest1->GetDistToStack());
	AssertInt(UNKNOWN_DIST_TO_STACK, pcTest2->GetDistToStack());
	AssertInt(UNKNOWN_DIST_TO_STACK, pcTest3->GetDistToStack());
	AssertInt(UNKNOWN_DIST_TO_STACK, pcTest4->GetDistToStack());
	AssertInt(UNKNOWN_DIST_TO_STACK, pcTest5->GetDistToStack());

	cParameters.Init();
	cDistToStackCalculator.Calculate(pcTest5, &cParameters);

	AssertInt(1, pcTest1->GetDistToStack());
	AssertInt(2, pcTest2->GetDistToStack());
	AssertInt(2, pcTest3->GetDistToStack());
	AssertInt(UNKNOWN_DIST_TO_STACK, pcTest4->GetDistToStack());  //Removing a stack pointer to 5 should be unable to effect 4 in any way.
	AssertInt(3, pcTest5->GetDistToStack());

	cDistToStackCalculator.ResetObjectsToUnknownDistToStack(&cParameters);
	cParameters.Kill();

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDistToStackRemoveUnbalancedLargeBroken(void)
{
	CDistCalculatorParameters	cParameters;
	CDistToStackCalculator		cDistToStackCalculator;

	Ptr<CRoot>					pRoot;
	STestObjectKilledNotifier	sKilled1;
	STestObjectKilledNotifier	sKilled2;
	STestObjectKilledNotifier	sKilled3;
	STestObjectKilledNotifier	sKilled4;
	STestObjectKilledNotifier	sKilled5;
	STestObjectKilledNotifier	sKilledTop1;
	STestObjectKilledNotifier	sKilledTop2;
	Ptr<CTestObject>			pTest1;
	Ptr<CTestObject>			pTest2;
	Ptr<CTestObject>			pTest3;
	Ptr<CTestObject>			pTest4;
	Ptr<CTestObject>			pTest5;
	Ptr<CSetObject>				pSet;
	Ptr<CTestObject>			pTop1;
	Ptr<CTestObject>			pTop2;
	CTestObject*				pcTest2;
	CTestObject*				pcTest3;
	CTestObject*				pcTest4;
	CTestObject*				pcTest5;
	CArrayBaseObjectPtr*		papcKilled;

	ObjectsInit();
	pRoot = ORoot();

	pTest1 = OMalloc(CTestObject);
	pTest2 = OMalloc(CTestObject);
	pTest3 = OMalloc(CTestObject);
	pTest4 = OMalloc(CTestObject);
	pTest5 = OMalloc(CTestObject);
	pSet = OMalloc(CSetObject);
	pTop1 = OMalloc(CTestObject);
	pTop2 = OMalloc(CTestObject);

	pTest1->Init(&sKilled1);
	pTest2->Init(&sKilled2);
	pTest3->Init(&sKilled3);
	pTest4->Init(&sKilled4);
	pTest5->Init(&sKilled5);
	pSet->Init();
	pTop1->Init(&sKilledTop1);
	pTop2->Init(&sKilledTop2);

	pRoot->Add(pSet);
	pSet->Add(pTest2);
	pSet->Add(pTop2);

	pTest2->mpTest = pTest3;
	pTest5->mpTest = pTop1;
	pTest4->mpTest = pTest5;
	pTest3->mpTest = pTest4;
	pTop1->mpTest = pTest1;
	pTop2->mpTest = pTest1;
	pTest1->mpTest = pTop1;
	pTest1->mpObject = pTop2;

	AssertInt(2, pSet->GetDistToRoot());
	AssertInt(3, pTest2->GetDistToRoot());
	AssertInt(4, pTest3->GetDistToRoot());
	AssertInt(5, pTest4->GetDistToRoot());
	AssertInt(6, pTest5->GetDistToRoot());
	AssertInt(4, pTest1->GetDistToRoot());
	AssertInt(5, pTop1->GetDistToRoot());
	AssertInt(3, pTop2->GetDistToRoot());
	AssertInt(2, pSet->NumElements());
	AssertInt(2, pSet->NumPointerTos());

	pcTest2 = &pTest2;
	pcTest3 = &pTest3;
	pcTest4 = &pTest4;
	pcTest5 = &pTest5;

	pTest3 = NULL;
	pTest4 = NULL;
	pTest5 = NULL;

	//
	//     Test1[3](4)  
	//       // \\      
	//      //   \\       
	//   Top1(5) Top2(3)
	//     |       |
	//   Test5(6)  |
	//     |       |
	//   Test4(5)  |
	//     |       |
	//   Test3(4)  |
	//     |	   |
	// Test2[4](3) |
	//      \     /
	//       \   /
	//       Set(2)
	//        |
	//       ...
	//      Root(0)
	//

	AssertInt(UNKNOWN_DIST_TO_STACK, pcTest2->GetDistToStack());
	AssertInt(UNKNOWN_DIST_TO_STACK, pcTest3->GetDistToStack());
	AssertInt(UNKNOWN_DIST_TO_STACK, pcTest4->GetDistToStack());
	AssertInt(UNKNOWN_DIST_TO_STACK, pcTest5->GetDistToStack());

	pSet->Remove(pcTest2);

	AssertInt(UNKNOWN_DIST_TO_STACK, pcTest2->GetDistToStack());
	AssertInt(UNKNOWN_DIST_TO_STACK, pcTest3->GetDistToStack());
	AssertInt(UNKNOWN_DIST_TO_STACK, pcTest4->GetDistToStack());
	AssertInt(UNKNOWN_DIST_TO_STACK, pcTest5->GetDistToStack());

	gcObjects.ValidateObjectsConsistency();

	pcTest2->TestRemoveStackFrom(pTest2.This());
	pTest2.UnsafeClearObject();

	cParameters.Init();
	cDistToStackCalculator.Calculate(pcTest2, &cParameters);

	papcKilled = cParameters.GetCompletelyDetachedArray();
	AssertInt(4, papcKilled->NumElements());

	cParameters.Kill();

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
	TestDistToStackSimpleHeap();
	TestDistToStackNoStackHeapFromBroken();
	TestDistToStackRootCyclicWithStackPointerA();
	TestDistToStackRootCyclicWithStackPointerB();
	TestDistToStackRootCyclicWithStackPointerC();
	TestDistToStackRootCyclicWithoutStackPointer();
	TestDistToStackSplitRootAndStack();
	TestDistToStackSetWithoutStackPointers();
	TestDistToStackSetWithStackPointers();
	TestDistToStackCyclicWithScenarioA();
	TestDistToStackSetBroken();
	TestDistToStackRemoveUnbalancedLargeBroken();

	TestStatistics();
}

