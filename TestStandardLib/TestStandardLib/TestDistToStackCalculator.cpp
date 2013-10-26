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

	p0->mp.UnsafeClearObject();
	p1->TestRemoveHeapFrom(p0.BaseObject());

	cDetached.Init();
	cDistToRootCalculator.Init();
	cDistToRootCalculator.AddFromChanged(p1.BaseObject());
	cDistToRootCalculator.Calculate(&cDetached);
	cDistToRootCalculator.Kill();

	AssertInt(UNATTACHED_DIST_TO_ROOT, p1->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, p2->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, p3->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pStack->GetDistToRoot());

	cDistToStackCalculator.Init();
	cDistToStackCalculator.Calculate(&cDetached);
	cDistToStackCalculator.Kill();
	cDetached.Kill();

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

