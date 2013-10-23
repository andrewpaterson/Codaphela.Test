#include "StandardLib/Objects.h"
#include "StandardLib/Root.h"
#include "StandardLib/PointerContainer.h"
#include "TestLib/Assert.h"
#include "ObjectTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestClearDistToRootToValidDistComplex(void)
{
	ObjectsInit();

	Ptr<CRoot>					pRoot;
	Ptr<CNamedPointerContainer>	p1;
	Ptr<CTestTriPointerObject>	pTri;
	Ptr<CPointerContainer>		p2a;
	Ptr<CPointerContainer>		p2b;
	Ptr<CPointerContainer>		p2c;
	Ptr<CTestObject>			pTest1a;
	Ptr<CTestObject>			pTest1b;
	Ptr<CTestObject>			pTest1c;
	Ptr<CTestObject>			pTest2d;
	Ptr<CTestObject>			pTest2e;
	Ptr<CPointerContainer>		p3a;
	Ptr<CPointerContainer>		p3b;
	Ptr<CPointerContainer>		p3c;

	Ptr<CPointerContainer>		p4a;
	Ptr<CPointerContainer>		p4c;
	Ptr<CPointerContainer>		p5a;
	Ptr<CPointerContainer>		p5c;
	Ptr<CPointerContainer>		p6a;
	Ptr<CPointerContainer>		p6c;
	Ptr<CPointerContainer>		p7c;
	Ptr<CPointerContainer>		p8c;
	Ptr<CPointerContainer>		p9c;

	CDistToRootEffectedFroms	cEffectedFroms;


	pRoot = ORoot();
	p1 = ONMalloc(CNamedPointerContainer, "Fred's")->Init();
	pRoot->Add(p1);
	pTri = OMalloc(CTestTriPointerObject)->Init();
	p1->mp = pTri;
	p2a = OMalloc(CPointerContainer)->Init();
	p2b = OMalloc(CPointerContainer)->Init();
	p2c = OMalloc(CPointerContainer)->Init();
	pTri->mpObject1 = p2a;
	pTri->mpObject2 = p2b;
	pTri->mpObject3 = p2c;
	p3a = OMalloc(CPointerContainer)->Init();
	p3b = OMalloc(CPointerContainer)->Init();
	p3c = OMalloc(CPointerContainer)->Init();
	p2a->mp = p3a;
	p2b->mp = p3b;
	p2c->mp = p3c;

	pTest1b = OMalloc(CTestObject)->Init();
	p4a = OMalloc(CPointerContainer)->Init();
	p4c = OMalloc(CPointerContainer)->Init();
	p3a->mp = p4a;
	p3b->mp = pTest1b;
	p3c->mp = p4c;
	pTest2d = OMalloc(CTestObject)->Init();
	pTest2e = OMalloc(CTestObject)->Init();
	p5a = OMalloc(CPointerContainer)->Init();
	p5c = OMalloc(CPointerContainer)->Init();
	p4a->mp = p5a;
	pTest1b->mpObject = pTest2d;
	pTest1b->mpTest = pTest2e;
	p4c->mp = p5c;
	pTest2d->mpTest = pTest1b;
	pTest2e->mpTest = pTest1b;
	pTest1a = OMalloc(CTestObject)->Init();
	pTest1c = OMalloc(CTestObject)->Init();
	p6a = OMalloc(CPointerContainer)->Init();
	p6c = OMalloc(CPointerContainer)->Init();
	p5a->mp = p6a;
	pTest1a->mpTest = pTest2d;
	pTest1c->mpTest = pTest2e;
	pTest2d->mpObject = pTest1a;
	pTest2e->mpObject = pTest1c;
	p5c->mp = p6c;
	p6a->mp = pTest1a;
	p7c = OMalloc(CPointerContainer)->Init();
	p8c = OMalloc(CPointerContainer)->Init();
	p9c = OMalloc(CPointerContainer)->Init();
	p6c->mp = p7c;
	p7c->mp = p8c;
	p8c->mp = p9c;
	p9c->mp = pTest1c;

	//       pTest2d(7)  pTest2e(7)
	//       //   \\     //   \\
	//      //     \\   //     \\
	//     //       \\ //       \\
	// pTest1a(8)  pTest1b(6) pTest1c(8)
	//    |           |          |
	//    |           |         p9c(11)
	//    |           |          |
	//    |           |         p8c(10)
	//    |           |          |
	//    |           |         p7c(9)
	//    |           |          |
	//   p6a(8)       |         p6c(8)
	//    |           |          |
	//   p5a(7)       |         p5c(7)
	//    |           |          |
	//   p4a(6)       |         p4c(6)
	//     \          |          /
	//      \         |         /
	//      p3a(5)   p3b(5)   p3c(5)
	//        \       |       /
	//         \      |      /
	//         p2a   p2b   p2c
	//           \    |    /
	//            \   |   /
	//             \  |  /
	//              pTri(3)
	//               |
	//               p1(2)
	//               |
	//              ...
	//             Root(0)

	AssertInt(2, p1->GetDistToRoot());
	AssertInt(3, pTri->GetDistToRoot());
	AssertInt(4, p2a->GetDistToRoot());
	AssertInt(4, p2b->GetDistToRoot());
	AssertInt(4, p2c->GetDistToRoot());
	AssertInt(5, p3a->GetDistToRoot());
	AssertInt(5, p3b->GetDistToRoot());
	AssertInt(5, p3c->GetDistToRoot());
	AssertInt(6, p4a->GetDistToRoot());
	AssertInt(6, p4c->GetDistToRoot());
	AssertInt(6, pTest1b->GetDistToRoot());
	AssertInt(7, p5a->GetDistToRoot());
	AssertInt(7, p5c->GetDistToRoot());
	AssertInt(7, pTest2d->GetDistToRoot());
	AssertInt(7, pTest2e->GetDistToRoot());
	AssertInt(8, p6a->GetDistToRoot());
	AssertInt(8, p6c->GetDistToRoot());
	AssertInt(8, pTest1a->GetDistToRoot());
	AssertInt(8, pTest1c->GetDistToRoot());
	AssertInt(9, p7c->GetDistToRoot());
	AssertInt(10,p8c->GetDistToRoot());
	AssertInt(11,p9c->GetDistToRoot());

	AssertInt(3, pTest1b->NumHeapFroms());
	AssertInt(24, (int)gcObjects.NumMemoryIndexes());
	p3b->mp.UnsafeClearObject();
	pTest1b->TestRemoveHeapFrom(p3b.BaseObject());
	AssertInt(24, (int)gcObjects.NumMemoryIndexes());
	AssertInt(2, pTest1b->NumHeapFroms());

	cEffectedFroms.Init();

	pTest1b->ClearDistToRootToValidDist(NULL, &cEffectedFroms);

	AssertInt(CLEARED_DIST_TO_ROOT, pTest1a->GetDistToRoot());
	AssertInt(CLEARED_DIST_TO_ROOT, pTest1b->GetDistToRoot());
	AssertInt(CLEARED_DIST_TO_ROOT, pTest1c->GetDistToRoot());
	AssertInt(CLEARED_DIST_TO_ROOT, pTest2d->GetDistToRoot());
	AssertInt(CLEARED_DIST_TO_ROOT, pTest2e->GetDistToRoot());

	AssertInt(2, cEffectedFroms.NumElements());
	AssertPointer(pTest1a.BaseObject(), cEffectedFroms.Get(0)->pcObject);
	AssertPointer(pTest1c.BaseObject(), cEffectedFroms.Get(1)->pcObject);
	AssertInt(9, cEffectedFroms.Get(0)->iExpectedDist);
	AssertInt(12, cEffectedFroms.Get(1)->iExpectedDist);

	cEffectedFroms.Kill();

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestClearDistToRootToValidDistSimpleLeft(void)
{
	ObjectsInit();

	Ptr<CRoot>					pRoot;
	Ptr<CNamedPointerContainer>	p1;
	Ptr<CTestObject>			pTest1;
	Ptr<CTestObject>			pTest2;
	Ptr<CTestObject>			pTest3;

	CDistToRootEffectedFroms		cEffectedFroms;

	pRoot = ORoot();
	p1 = ONMalloc(CNamedPointerContainer, "Back")->Init();
	pRoot->Add(p1);
	pTest1 = OMalloc(CTestObject)->Init();
	p1->mp = pTest1;
	pTest2 = OMalloc(CTestObject)->Init();
	pTest3 = OMalloc(CTestObject)->Init();
	pTest1->mpTest = pTest2;
	pTest1->mpObject = pTest3;
	pTest2->mpTest = pTest3;

	//     pTest3(4)
	//       | \
	//       |  \
	//       |   \
	//       |  pTest2(4)
	//       |   /
	//       |  /
	//       | /
	//     pTest1(3)
	//        |
	//        |
	//       p1(2)
	//        |
	//       ...
	//      Root(0)

	AssertInt(2, p1->GetDistToRoot());
	AssertInt(3, pTest1->GetDistToRoot());
	AssertInt(4, pTest2->GetDistToRoot());
	AssertInt(4, pTest3->GetDistToRoot());

	AssertInt(1, pTest2->NumHeapFroms());
	pTest1->mpTest.UnsafeClearObject();
	pTest2->TestRemoveHeapFrom(pTest1.BaseObject());
	AssertInt(0, pTest2->NumHeapFroms());

	cEffectedFroms.Init();

	pTest2->ClearDistToRootToValidDist(NULL, &cEffectedFroms);

	AssertInt(CLEARED_DIST_TO_ROOT, pTest2->GetDistToRoot());
	AssertInt(4, pTest3->GetDistToRoot());

	AssertInt(0, cEffectedFroms.NumElements());

	cEffectedFroms.Kill();

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestClearDistToRootToValidDistSimpleRight(void)
{
	ObjectsInit();

	Ptr<CRoot>					pRoot;
	Ptr<CNamedPointerContainer>	p1;
	Ptr<CTestObject>			pTest1;
	Ptr<CTestObject>			pTest2;
	Ptr<CTestObject>			pTest3;

	CDistToRootEffectedFroms		cEffectedFroms;

	pRoot = ORoot();
	p1 = ONMalloc(CNamedPointerContainer, "III")->Init();
	pRoot->Add(p1);
	pTest1 = OMalloc(CTestObject)->Init();
	p1->mp = pTest1;
	pTest2 = OMalloc(CTestObject)->Init();
	pTest3 = OMalloc(CTestObject)->Init();
	pTest1->mpTest = pTest2;
	pTest1->mpObject = pTest3;
	pTest2->mpTest = pTest3;

	//     pTest3(4)
	//       | \
	//       |  \
	//       |   \
	//       |  pTest2(4)
	//       |   /
	//       |  /
	//       | /
	//     pTest1(3)
	//        |
	//        |
	//       p1(2)
	//        |
	//       ...
	//      Root(0)

	AssertInt(2, p1->GetDistToRoot());
	AssertInt(3, pTest1->GetDistToRoot());
	AssertInt(4, pTest2->GetDistToRoot());
	AssertInt(4, pTest3->GetDistToRoot());

	AssertInt(2, pTest3->NumHeapFroms());
	pTest1->mpObject.UnsafeClearObject();
	pTest3->TestRemoveHeapFrom(pTest1.BaseObject());
	AssertInt(1, pTest3->NumHeapFroms());

	cEffectedFroms.Init();

	pTest3->ClearDistToRootToValidDist(NULL, &cEffectedFroms);

	AssertInt(CLEARED_DIST_TO_ROOT, pTest3->GetDistToRoot());

	AssertInt(1, cEffectedFroms.NumElements());
	AssertPointer(pTest3.BaseObject(), cEffectedFroms.Get(0)->pcObject);
	AssertInt(5, cEffectedFroms.Get(0)->iExpectedDist);

	cEffectedFroms.Kill();

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestUpdateTosDistToRootComplex(void)
{
	ObjectsInit();

	Ptr<CRoot>					pRoot;
	Ptr<CNamedPointerContainer>	p1;
	Ptr<CTestTriPointerObject>	pTri;
	Ptr<CPointerContainer>		p2a;
	Ptr<CPointerContainer>		p2b;
	Ptr<CPointerContainer>		p2c;
	Ptr<CTestObject>			pTest1a;
	Ptr<CTestObject>			pTest1b;
	Ptr<CTestObject>			pTest1c;
	Ptr<CTestObject>			pTest2d;
	Ptr<CTestObject>			pTest2e;
	Ptr<CPointerContainer>		p3a;
	Ptr<CPointerContainer>		p3b;
	Ptr<CPointerContainer>		p3c;

	Ptr<CPointerContainer>		p4a;
	Ptr<CPointerContainer>		p4c;
	Ptr<CPointerContainer>		p5a;
	Ptr<CPointerContainer>		p5c;
	Ptr<CPointerContainer>		p6a;
	Ptr<CPointerContainer>		p6c;
	Ptr<CPointerContainer>		p7c;
	Ptr<CPointerContainer>		p8c;
	Ptr<CPointerContainer>		p9c;

	CDistToRootCalculator		cDistToRootCalculator;
	CDistToRootEffectedFroms	cEffectedFroms;

	pRoot = ORoot();
	p1 = ONMalloc(CNamedPointerContainer, "Fred's")->Init();
	pRoot->Add(p1);
	pTri = OMalloc(CTestTriPointerObject)->Init();
	p1->mp = pTri;
	p2a = OMalloc(CPointerContainer)->Init();
	p2b = OMalloc(CPointerContainer)->Init();
	p2c = OMalloc(CPointerContainer)->Init();
	pTri->mpObject1 = p2a;
	pTri->mpObject2 = p2b;
	pTri->mpObject3 = p2c;
	p3a = OMalloc(CPointerContainer)->Init();
	p3b = OMalloc(CPointerContainer)->Init();
	p3c = OMalloc(CPointerContainer)->Init();
	p2a->mp = p3a;
	p2b->mp = p3b;
	p2c->mp = p3c;

	pTest1b = OMalloc(CTestObject)->Init();
	p4a = OMalloc(CPointerContainer)->Init();
	p4c = OMalloc(CPointerContainer)->Init();
	p3a->mp = p4a;
	p3b->mp = pTest1b;
	p3c->mp = p4c;
	pTest2d = OMalloc(CTestObject)->Init();
	pTest2e = OMalloc(CTestObject)->Init();
	p5a = OMalloc(CPointerContainer)->Init();
	p5c = OMalloc(CPointerContainer)->Init();
	p4a->mp = p5a;
	pTest1b->mpObject = pTest2d;
	pTest1b->mpTest = pTest2e;
	p4c->mp = p5c;
	pTest2d->mpTest = pTest1b;
	pTest2e->mpTest = pTest1b;
	pTest1a = OMalloc(CTestObject)->Init();
	pTest1c = OMalloc(CTestObject)->Init();
	p6a = OMalloc(CPointerContainer)->Init();
	p6c = OMalloc(CPointerContainer)->Init();
	p5a->mp = p6a;
	pTest1a->mpTest = pTest2d;
	pTest1c->mpTest = pTest2e;
	pTest2d->mpObject = pTest1a;
	pTest2e->mpObject = pTest1c;
	p5c->mp = p6c;
	p6a->mp = pTest1a;
	p7c = OMalloc(CPointerContainer)->Init();
	p8c = OMalloc(CPointerContainer)->Init();
	p9c = OMalloc(CPointerContainer)->Init();
	p6c->mp = p7c;
	p7c->mp = p8c;
	p8c->mp = p9c;
	p9c->mp = pTest1c;

	p3b->mp.UnsafeClearObject();
	pTest1b->TestRemoveHeapFrom(p3b.BaseObject());

	cDistToRootCalculator.Init();
	cEffectedFroms.Init();

	cDistToRootCalculator.AddFromChanged(pTest1b.BaseObject());
	cDistToRootCalculator.Calculate(&cEffectedFroms);

	cEffectedFroms.Kill();
	cDistToRootCalculator.Kill();

	//       pTest2d(10)  pTest2e(12)
	//       //   \\     //   \\
	//      //     \\   //     \\
	//     //       \\ //       \\
	// pTest1a(9)  pTest1b(11) pTest1c(12)
	//     |                      |
	//     |                      |
	//   p6a(8)                  p9c(11)

	AssertInt(8, p6a->GetDistToRoot());
	AssertInt(11, p9c->GetDistToRoot());
	AssertInt(9, pTest1a->GetDistToRoot());
	AssertInt(11, pTest1b->GetDistToRoot());
	AssertInt(12, pTest1c->GetDistToRoot());
	AssertInt(10, pTest2d->GetDistToRoot());
	AssertInt(12, pTest2e->GetDistToRoot());

	gcObjects.ValidateConsistency();

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestUpdateTosDistToRootSimpleLeft(void)
{
	ObjectsInit();

	Ptr<CRoot>					pRoot;
	Ptr<CNamedPointerContainer>	p1;
	Ptr<CTestObject>			pTest1;
	Ptr<CTestObject>			pTest2;
	Ptr<CTestObject>			pTest3;

	CDistToRootEffectedFroms	cEffectedFroms;
	CDistToRootCalculator		cDistToRootCalculator;

	pRoot = ORoot();
	p1 = ONMalloc(CNamedPointerContainer, "Back")->Init();
	pRoot->Add(p1);
	pTest1 = OMalloc(CTestObject)->Init();
	p1->mp = pTest1;
	pTest2 = OMalloc(CTestObject)->Init();
	pTest3 = OMalloc(CTestObject)->Init();
	pTest1->mpTest = pTest2;
	pTest1->mpObject = pTest3;
	pTest2->mpTest = pTest3;

	pTest1->mpTest.UnsafeClearObject();
	pTest2->TestRemoveHeapFrom(pTest1.BaseObject());

	//   pTest3(4)
	//      | 
	//      |
	//      |
	//   pTest1(3)
	//      |
	//      |
	//     p1(2)
	//      |
	//     ...
	//    Root(0)

	cDistToRootCalculator.Init();
	cEffectedFroms.Init();

	cDistToRootCalculator.AddFromChanged(pTest2.BaseObject());
	cDistToRootCalculator.Calculate(&cEffectedFroms);

	cEffectedFroms.Kill();
	cDistToRootCalculator.Kill();

	AssertInt(3, pTest1->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pTest2->GetDistToRoot());
	AssertInt(4, pTest3->GetDistToRoot());

	gcObjects.ValidateConsistency();

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestUpdateTosDistToRootSimpleRight(void)
{
	ObjectsInit();

	Ptr<CRoot>					pRoot;
	Ptr<CNamedPointerContainer>	p1;
	Ptr<CTestObject>			pTest1;
	Ptr<CTestObject>			pTest2;
	Ptr<CTestObject>			pTest3;

	CDistToRootEffectedFroms	cEffectedFroms;
	CDistToRootCalculator		cDistToRootCalculator;

	pRoot = ORoot();
	p1 = ONMalloc(CNamedPointerContainer, "III")->Init();
	pRoot->Add(p1);
	pTest1 = OMalloc(CTestObject)->Init();
	p1->mp = pTest1;
	pTest2 = OMalloc(CTestObject)->Init();
	pTest3 = OMalloc(CTestObject)->Init();
	pTest1->mpTest = pTest2;
	pTest1->mpObject = pTest3;
	pTest2->mpTest = pTest3;

	pTest1->mpObject.UnsafeClearObject();
	pTest3->TestRemoveHeapFrom(pTest1.BaseObject());

	// pTest3(4)    pTest2(4)
	//      \       /
	//       \     /
	//        \   /
	//         \ /
	//       pTest1(3)
	//          |
	//          |
	//         p1(2)
	//          |
	//         ...
	//        Root(0)

	cDistToRootCalculator.Init();
	cEffectedFroms.Init();

	cDistToRootCalculator.AddFromChanged(pTest2.BaseObject());
	cDistToRootCalculator.Calculate(&cEffectedFroms);

	cEffectedFroms.Kill();
	cDistToRootCalculator.Kill();

	AssertInt(3, pTest1->GetDistToRoot());
	AssertInt(4, pTest2->GetDistToRoot());
	AssertInt(4, pTest3->GetDistToRoot());

	gcObjects.ValidateConsistency();

	ObjectsKill();
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDistToRoot(void)
{
	BeginTests();

	TestClearDistToRootToValidDistComplex();
	TestClearDistToRootToValidDistSimpleLeft();
	TestClearDistToRootToValidDistSimpleRight();
	TestUpdateTosDistToRootComplex();
	TestUpdateTosDistToRootSimpleRight();
	TestUpdateTosDistToRootSimpleLeft();

	TestStatistics();
}

