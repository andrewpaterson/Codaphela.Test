#include "StandardLib/Objects.h"
#include "StandardLib/Root.h"
#include "StandardLib/PointerContainer.h"
#include "TestLib/Assert.h"
#include "ObjectTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDistToStack1(void)
{
	ObjectsInit();

	CDistToRootCalculator	cDistToRootCalculator;
	CDistToStackCalculator	cDistToStackCalculator;
	CDistDetachedFroms		cDetached;
	CNamedPointerContainer*	pc1;
	CNamedPointerContainer*	pc2;
	CNamedPointerContainer*	pc3;

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

	p0->mp.UnsafeClearObject();
	pc1->TestRemoveHeapFrom(p0.BaseObject());

	cDetached.Init();
	cDistToRootCalculator.Init();
	cDistToRootCalculator.AddFromChanged(pc1);
	cDistToRootCalculator.Calculate(&cDetached);
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
	cDetached.Kill();

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

	TestDistToStack1();

	TestStatistics();
}

