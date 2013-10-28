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
	CDistDetachedFroms			cDetached;
	CDistToRootEffectedFroms	cEffectedFroms;
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

	cDetached.Init();
	cEffectedFroms.Init();
	cDistToRootCalculator.Init();
	cDistToRootCalculator.AddFromChanged(pc1);
	cDistToRootCalculator.Calculate(&cEffectedFroms, &cDetached);
	cDistToRootCalculator.Kill();

	AssertInt(UNATTACHED_DIST_TO_ROOT, pc1->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pc2->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pc3->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pStack->GetDistToRoot());

	gcObjects.ValidateConsistency();

	cDistToStackCalculator.Init();
	cDistToStackCalculator.Calculate(&cDetached);

	AssertInt(3, cDetached.NumDetachedFromRoot());
	AssertInt(0, cDetached.NumCompletelyDetached());

	cDistToStackCalculator.Kill();
	cEffectedFroms.Kill();
	cDetached.Kill();

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
	CDistDetachedFroms			cDetached;
	CDistToRootEffectedFroms	cEffectedFroms;
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

	cDetached.Init();
	cEffectedFroms.Init();
	cDistToRootCalculator.Init();
	cDistToRootCalculator.AddFromChanged(pc1);
	cDistToRootCalculator.Calculate(&cEffectedFroms, &cDetached);
	cDistToRootCalculator.Kill();

	AssertInt(UNATTACHED_DIST_TO_ROOT, pc1->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pc2->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pc3->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pStack->GetDistToRoot());

	cDistToStackCalculator.Init();
	cDistToStackCalculator.Calculate(&cDetached);

	AssertInt(3, cDetached.NumDetachedFromRoot());
	AssertInt(0, cDetached.NumCompletelyDetached());

	cDistToStackCalculator.Kill();
	cEffectedFroms.Kill();
	cDetached.Kill();

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
	CDistDetachedFroms			cDetached;
	CDistToRootEffectedFroms	cEffectedFroms;
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

	cDetached.Init();
	cEffectedFroms.Init();
	cDistToRootCalculator.Init();
	cDistToRootCalculator.AddFromChanged(pc1);
	cDistToRootCalculator.Calculate(&cEffectedFroms, &cDetached);
	cDistToRootCalculator.Kill();

	AssertInt(UNATTACHED_DIST_TO_ROOT, pc1->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pc2->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pc3->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pStack->GetDistToRoot());

	cDistToStackCalculator.Init();
	cDistToStackCalculator.Calculate(&cDetached);

	AssertInt(3, cDetached.NumDetachedFromRoot());
	AssertInt(0, cDetached.NumCompletelyDetached());

	cDistToStackCalculator.Kill();
	cEffectedFroms.Kill();
	cDetached.Kill();

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
	CDistDetachedFroms			cDetached;
	CDistToRootEffectedFroms	cEffectedFroms;
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

	p0->mp.UnsafeClearObject();
	pc1->TestRemoveHeapFrom(p0.BaseObject());

	cDetached.Init();
	cEffectedFroms.Init();
	cDistToRootCalculator.Init();
	cDistToRootCalculator.AddFromChanged(pc1);
	cDistToRootCalculator.Calculate(&cEffectedFroms, &cDetached);
	cDistToRootCalculator.Kill();

	AssertInt(UNATTACHED_DIST_TO_ROOT, pc1->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pc2->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pc3->GetDistToRoot());

	cDistToStackCalculator.Init();
	cDistToStackCalculator.Calculate(&cDetached);

	AssertInt(3, cDetached.NumDetachedFromRoot());
	AssertInt(3, cDetached.NumCompletelyDetached());
	AssertPointer(pc1, cDetached.GetCompletelyDetached(0));
	AssertPointer(pc2, cDetached.GetCompletelyDetached(1));
	AssertPointer(pc3, cDetached.GetCompletelyDetached(2));

	cDistToStackCalculator.Kill();
	cEffectedFroms.Kill();
	cDetached.Kill();

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
	CDistDetachedFroms			cDetached;
	CDistToRootEffectedFroms	cEffectedFroms;
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

	cDetached.Init();
	cEffectedFroms.Init();
	cDistToRootCalculator.Init();
	cDistToRootCalculator.AddFromChanged(pcTestC);
	cDistToRootCalculator.Calculate(&cEffectedFroms, &cDetached);
	cDistToRootCalculator.Kill();

	AssertInt(UNATTACHED_DIST_TO_ROOT, pcTestC->GetDistToRoot());
	AssertInt(3, pcTestL1->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pcTestR1->GetDistToRoot());
	AssertInt(4, pcTestL2->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pcTestR2->GetDistToRoot());

	AssertInt(3, cDetached.NumDetachedFromRoot());
	AssertPointer(pcTestC, cDetached.GetDetachedFromRoot(0));
	AssertPointer(pcTestR1, cDetached.GetDetachedFromRoot(1));
	AssertPointer(pcTestR2, cDetached.GetDetachedFromRoot(2));

	cDistToStackCalculator.Init();
	cDistToStackCalculator.Calculate(&cDetached);

	AssertInt(3, cDetached.NumDetachedFromRoot());
	AssertInt(1, cDetached.NumCompletelyDetached());
	AssertPointer(pcTestC, cDetached.GetCompletelyDetached(0));

	cDistToStackCalculator.Kill();
	cEffectedFroms.Kill();
	cDetached.Kill();

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
	CDistDetachedFroms			cDetached;
	CDistToRootEffectedFroms	cEffectedFroms;
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

	cDetached.Init();
	cEffectedFroms.Init();
	cDistToRootCalculator.Init();
	cDistToRootCalculator.AddFromChanged(pcSet);
	cDistToRootCalculator.Calculate(&cEffectedFroms, &cDetached);
	cDistToRootCalculator.Kill();
	cDistToStackCalculator.Init();
	cDistToStackCalculator.Calculate(&cDetached);

	AssertInt(2, cDetached.NumDetachedFromRoot());
	AssertInt(2, cDetached.NumCompletelyDetached());
	AssertPointer(pcSet, cDetached.GetCompletelyDetached(0));
	AssertPointer(pcTest, cDetached.GetCompletelyDetached(1));

	cDistToStackCalculator.Kill();
	cEffectedFroms.Kill();

	AssertLongLongInt(5, gcObjects.NumMemoryIndexes());
	gcObjects.Remove(cDetached.GetCompletelyDetachedArray());
	cDetached.Kill();
	AssertLongLongInt(3, gcObjects.NumMemoryIndexes());

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
	CDistDetachedFroms			cDetached;
	CDistToRootEffectedFroms	cEffectedFroms;
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

	cDetached.Init();
	cEffectedFroms.Init();
	cDistToRootCalculator.Init();
	cDistToRootCalculator.AddFromChanged(pcSet);
	cDistToRootCalculator.Calculate(&cEffectedFroms, &cDetached);
	cDistToRootCalculator.Kill();
	cDistToStackCalculator.Init();
	cDistToStackCalculator.Calculate(&cDetached);

	AssertInt(2, cDetached.NumDetachedFromRoot());
	AssertInt(1, cDetached.NumCompletelyDetached());
	AssertPointer(pcSet, cDetached.GetCompletelyDetached(0));

	cDistToStackCalculator.Kill();
	cEffectedFroms.Kill();

	AssertLongLongInt(5, gcObjects.NumMemoryIndexes());
	gcObjects.Remove(cDetached.GetCompletelyDetachedArray());
	cDetached.Kill();
	AssertLongLongInt(4, gcObjects.NumMemoryIndexes());

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

	TestStatistics();
}

