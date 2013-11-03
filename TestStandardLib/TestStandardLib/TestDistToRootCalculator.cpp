#include "StandardLib/Objects.h"
#include "StandardLib/Root.h"
#include "StandardLib/PointerContainer.h"
#include "StandardLib/String.h"
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

	CDistCalculatorParameters	cDistParameters;

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

	cDistParameters.Init();
	pTest1b->CollectValidDistStartingObjectsAndSetClearedToRoot(NULL, &cDistParameters);

	AssertInt(CLEARED_DIST_TO_ROOT, pTest1a->GetDistToRoot());
	AssertInt(CLEARED_DIST_TO_ROOT, pTest1b->GetDistToRoot());
	AssertInt(CLEARED_DIST_TO_ROOT, pTest1c->GetDistToRoot());
	AssertInt(CLEARED_DIST_TO_ROOT, pTest2d->GetDistToRoot());
	AssertInt(CLEARED_DIST_TO_ROOT, pTest2e->GetDistToRoot());

	AssertInt(2, cDistParameters.NumExpectedDists());
	AssertPointer(pTest1a.BaseObject(), cDistParameters.GetExpectedDist(0)->pcObject);
	AssertPointer(pTest1c.BaseObject(), cDistParameters.GetExpectedDist(1)->pcObject);
	AssertInt(9, cDistParameters.GetExpectedDist(0)->iExpectedDist);
	AssertInt(12, cDistParameters.GetExpectedDist(1)->iExpectedDist);

	cDistParameters.Kill();

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestClearDistToRootToValidDistSimpleLeft(void)
{
	ObjectsInit();

	Ptr<CRoot>						pRoot;
	Ptr<CNamedPointerContainer>		p1;
	Ptr<CTestObject>				pTest1;
	Ptr<CTestObject>				pTest2;
	Ptr<CTestObject>				pTest3;

	CDistCalculatorParameters		cDistParameters;
	CDistToRootCalculator			cDistCalculator;

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
	//       ^ ^
	//       |  \
	//       |   \
	//       |  pTest2(4)
	//       |   ^
	//       |  /
	//       | /
	//     pTest1(3)
	//        ^
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

	cDistParameters.Init();

	cDistCalculator.Calculate(&pTest2, &cDistParameters);

	AssertInt(UNATTACHED_DIST_TO_ROOT, pTest2->GetDistToRoot());
	AssertInt(4, pTest3->GetDistToRoot());

	AssertInt(0, cDistParameters.NumExpectedDists());

	
	cDistParameters.Kill();

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

	CDistCalculatorParameters		cDistParameters;

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

	cDistParameters.Init();

	pTest3->CollectValidDistStartingObjectsAndSetClearedToRoot(NULL, &cDistParameters);

	AssertInt(CLEARED_DIST_TO_ROOT, pTest3->GetDistToRoot());

	AssertInt(1, cDistParameters.NumExpectedDists());
	AssertPointer(pTest3.BaseObject(), cDistParameters.GetExpectedDist(0)->pcObject);
	AssertInt(5, cDistParameters.GetExpectedDist(0)->iExpectedDist);

	cDistParameters.Kill();

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestUpdateAttachedTosDistToRootComplex(void)
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

	CDistCalculatorParameters	cParameters;
	CDistToRootCalculator		cDistToRootCalculator;

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

	cParameters.Init();
	cDistToRootCalculator.Calculate(pTest1b.BaseObject(), &cParameters);
	cParameters.ClearTouchedFlags();
	cParameters.Kill();


	//
	//       pTest2d(10)  pTest2e(12)
	//       //   \\     //   \\
	//      //     \\   //     \\
	//     //       \\ //       \\
	// pTest1a(9)  pTest1b(11) pTest1c(12)
	//     |                      |
	//     |                      |
	//   p6a(8)                  p9c(11)
	//     |                      |
	//     .                      .
	//     .                      .
	//

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
void TestUpdateAttachedTosDistToRootSimpleLeft(void)
{
	ObjectsInit();

	Ptr<CRoot>					pRoot;
	Ptr<CNamedPointerContainer>	p1;
	Ptr<CTestObject>			pTest1;
	Ptr<CTestObject>			pTest2;
	Ptr<CTestObject>			pTest3;

	CDistCalculatorParameters	cParameters;
	CDistToRootCalculator		cDistToRootCalculator;
	int							iFlags;

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

	//
	// pTest3(4)<--pTest2(4)
	//      ^       ^
	//       \     /
	//        \   /
	//         \ /
	//       pTest1(3)
	//          ^
	//          |
	//         p1(2)
	//          ^
	//          |
	//         ...
	//        Root(0)
	//

	pTest1->mpTest.UnsafeClearObject();
	pTest2->TestRemoveHeapFrom(pTest1.BaseObject());

	//
	//   pTest3(4)
	//      | 
	//      |
	//      |
	//   pTest1(3)
	//      |
	//      |
	//     p1(2)
	//      |
	//      |
	//     ...
	//    Root(0)
	//

	cParameters.Init();
	cDistToRootCalculator.Calculate(pTest2.BaseObject(), &cParameters);
	cParameters.ClearTouchedFlags();
	cParameters.Kill();

	AssertInt(3, pTest1->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pTest2->GetDistToRoot());
	AssertInt(4, pTest3->GetDistToRoot());

	iFlags = pTest3->GetFlags();
	AssertFalse(iFlags & OBJECT_FLAGS_CLEARED_DIST_TO_ROOT);
	AssertFalse(iFlags & OBJECT_FLAGS_UPDATED_TOS_DIST_TO_ROOT);

	gcObjects.ValidateConsistency();

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestUpdateAttachedTosDistToRootSimpleRight(void)
{
	ObjectsInit();

	Ptr<CRoot>					pRoot;
	Ptr<CNamedPointerContainer>	p1;
	Ptr<CTestObject>			pTest1;
	Ptr<CTestObject>			pTest2;
	Ptr<CTestObject>			pTest3;

	CDistCalculatorParameters	cParameters;
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

	//
	// pTest3(4)<--pTest2(4)
	//      ^       ^
	//       \     /
	//        \   /
	//         \ /
	//       pTest1(3)
	//          ^
	//          |
	//         p1(2)
	//          ^
	//          |
	//          |
	//         ...
	//        Root(0)
	//

	AssertLongLongInt(4, pTest1->GetOI());
	AssertLongLongInt(5, pTest2->GetOI());
	AssertLongLongInt(6, pTest3->GetOI());

	pTest2->mpTest.UnsafeClearObject();
	pTest3->TestRemoveHeapFrom(pTest2.BaseObject());

	//
	// pTest3(4)    pTest2(4)
	//      ^       ^
	//       \     /
	//        \   /
	//         \ /
	//       pTest1(3)
	//          ^
	//          |
	//          |
	//         p1(2)
	//          ^
	//          |
	//          |
	//         ...
	//        Root(0)
	//

	cParameters.Init();
	cDistToRootCalculator.Calculate(pTest3.BaseObject(), &cParameters);
	cParameters.ClearTouchedFlags();
	cParameters.Kill();

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
void TestUpdateAttachedTosDistToRootSimpleRightBroken(void)
{
	ObjectsInit();

	Ptr<CRoot>					pRoot;
	Ptr<CNamedPointerContainer>	p1;
	Ptr<CTestObject>			pTest1;
	Ptr<CTestObject>			pTest2;
	Ptr<CTestObject>			pTest3;

	CDistToRootCalculator		cDistToRootCalculator;
	CDistCalculatorParameters	cDistParameters;

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

	//
	// pTest3(4)<--pTest2(4)
	//      ^       ^
	//       \     /
	//        \   /
	//         \ /
	//       pTest1(3)
	//          ^
	//          |
	//         p1(2)
	//          ^
	//          |
	//         ...
	//        Root(0)
	//

	AssertLongLongInt(4, pTest1->GetOI());
	AssertLongLongInt(5, pTest2->GetOI());
	AssertLongLongInt(6, pTest3->GetOI());

	pTest1->mpObject.UnsafeClearObject();
	pTest3->TestRemoveHeapFrom(pTest1.BaseObject());

	//
	// pTest3(5)<--pTest2(4)
	//              ^
	//             /
	//            /
	//           /
	//       pTest1(3)
	//          ^
	//          |
	//         p1(2)
	//          ^
	//          |
	//         ...
	//        Root(0)
	//


	cDistParameters.Init();
	cDistToRootCalculator.Calculate(pTest3.BaseObject(), &cDistParameters);
	cDistParameters.ClearTouchedFlags();

	AssertInt(3, pTest1->GetDistToRoot());
	AssertInt(4, pTest2->GetDistToRoot());
	AssertInt(5, pTest3->GetDistToRoot());

	cDistParameters.Kill();

	gcObjects.ValidateConsistency();

	ObjectsKill();
}



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestUpdateAttachedTosDistToRootChildTriangleKindaBalanced(void)
{
	ObjectsInit();

	Ptr<CNamedPointerContainer>	p1a;
	Ptr<CNamedPointerContainer>	p1b;
	Ptr<CPointerContainer>		p2a;
	Ptr<CPointerContainer>		p2b;
	Ptr<CPointerContainer>		p3a;
	Ptr<CPointerContainer>		p3b;
	Ptr<CPointerContainer>		p4a;
	Ptr<CPointerContainer>		p4b;
	Ptr<CPointerContainer>		p5a;
	Ptr<CPointerContainer>		p5b;
	Ptr<CPointerContainer>		p6b;
	Ptr<CNamedPointerContainer>	p1c;
	Ptr<CPointerContainer>		p6c;
	Ptr<CRoot>					pRoot;
	Ptr<CTestObject>			pTest1a;
	Ptr<CTestObject>			pTest1b;
	Ptr<CTestObject>			pTest1c;
	Ptr<CTestObject>			pTest2a;
	Ptr<CTestObject>			pTest2b;
	Ptr<CTestObject>			pTest3a;

	CDistCalculatorParameters	cParameters;
	CDistToRootCalculator		cDistToRootCalculator;

	pRoot = ORoot();

	p6b = OMalloc(CPointerContainer)->Init();
	p6c = OMalloc(CPointerContainer)->Init();
	p5a = OMalloc(CPointerContainer)->Init();
	p5b = OMalloc(CPointerContainer)->Init(p6b);
	p4a = OMalloc(CPointerContainer)->Init(p5a);
	p4b = OMalloc(CPointerContainer)->Init(p5b);
	p3a = OMalloc(CPointerContainer)->Init(p4a);
	p3b	= OMalloc(CPointerContainer)->Init(p4b);
	p2a = OMalloc(CPointerContainer)->Init(p3a);
	p2b = OMalloc(CPointerContainer)->Init(p3b);
	p1a = ONMalloc(CNamedPointerContainer, "R.")->Init(p2a);
	p1b = ONMalloc(CNamedPointerContainer, "E.")->Init(p2b);
	p1c = ONMalloc(CNamedPointerContainer, "B.")->Init(p6c);
	pRoot->Add(p1a);
	pRoot->Add(p1b);
	pRoot->Add(p1c);

	pTest1a = OMalloc(CTestObject)->Init();
	pTest1b = OMalloc(CTestObject)->Init();
	pTest1c = OMalloc(CTestObject)->Init();
	pTest2a = OMalloc(CTestObject)->Init();
	pTest2b = OMalloc(CTestObject)->Init();
	pTest3a = OMalloc(CTestObject)->Init();
	p5a->mp = pTest1a;
	p6b->mp = pTest1c;
	p6c->mp = pTest1b;
	pTest1a->mpTest = pTest1b;
	pTest1c->mpTest = pTest1b;
	pTest1a->mpObject = pTest2a;
	pTest1c->mpObject = pTest2b;
	pTest1b->mpObject = pTest2a;
	pTest1b->mpTest = pTest2b;
	pTest2a->mpTest = pTest3a;
	pTest2b->mpTest = pTest3a;
	pTest2a->mpObject = pTest2b;

	//                            
	//                 pTest3a(6)
	//                  /   \
	//                 /     \
	//                /       \
	//               /         \
	//              /           \
	//         pTest2a(5)-->pTest2b(5)
	//            |  \         /  |
	//            |   \       /   |
	//            |    \     /    |
	//            |     \   /     |
	//            |  pTest1b(4)   |
	//            |   /   |   \   |
	//            |  /    |    \  |
	//            | /     |     \ |
	//         pTest1a(7) |     pTest1c(8)
	//            |       |       |
	//            |       |       |
	//            |      p6c(3)  p6b(7)
	//            |       |       |
	//            |       |       |
	//           p5a(6)   |      p5b(6)
	//            |       |       |
	//            |       |       |
	//           p4a(5)   |      p4b(5)
	//            |       |       |
	//            |       |       |
	//           p3a(4)   |      p3b(4)
	//            |       |       |
	//            |       |       |
	//           p2a(3)   |      p2b(3)
	//            |       |       |
	//            |       |       |
	//           p1a(2)  p1c(2)  p1b(2)
	//             \      |      /           
	//              \     |     /           
	//               \    |    /           
	//                \   |   /             
	//                 \  |  /            
	//                  \ | /            
	//                   ...
	//                  Root(0)
	//                         

	AssertInt(2, p1a->GetDistToRoot());
	AssertInt(2, p1c->GetDistToRoot());
	AssertInt(2, p1b->GetDistToRoot());
	AssertInt(3, p2a->GetDistToRoot());
	AssertInt(3, p2b->GetDistToRoot());
	AssertInt(4, p3a->GetDistToRoot());
	AssertInt(4, p3b->GetDistToRoot());
	AssertInt(5, p4a->GetDistToRoot());
	AssertInt(5, p4b->GetDistToRoot());
	AssertInt(6, p5a->GetDistToRoot());
	AssertInt(6, p5b->GetDistToRoot());
	AssertInt(7, p6b->GetDistToRoot());
	AssertInt(3, p6c->GetDistToRoot());
	AssertInt(7, pTest1a->GetDistToRoot());
	AssertInt(4, pTest1b->GetDistToRoot());
	AssertInt(8, pTest1c->GetDistToRoot());
	AssertInt(5, pTest2a->GetDistToRoot());
	AssertInt(5, pTest2b->GetDistToRoot());
	AssertInt(6, pTest3a->GetDistToRoot());

	p6c->mp.UnsafeClearObject();
	pTest1b->TestRemoveHeapFrom(p6c.BaseObject());

	cParameters.Init();
	cDistToRootCalculator.Calculate(pTest1b.BaseObject(), &cParameters);
	cParameters.ClearTouchedFlags();
	cParameters.Kill();

	//                            
	//                 pTest3a(9)
	//                  /   \
	//                 /     \
	//                /       \
	//               /         \
	//              /           \
	//         pTest2a(8)-->pTest2b(9)
	//            |  \         /  |
	//            |   \       /   |
	//            |    \     /    |
	//            |     \   /     |
	//            |  pTest1b(8)   |
	//            |   /       \   |
	//            |  /         \  |
	//            | /           \ |
	//         pTest1a(7)       pTest1c(8)
	//            |               |
	//            .               .
	//            .               .

	AssertInt(7, pTest1a->GetDistToRoot());
	AssertInt(8, pTest1b->GetDistToRoot());
	AssertInt(8, pTest1c->GetDistToRoot());
	AssertInt(8, pTest2a->GetDistToRoot());
	AssertInt(9, pTest2b->GetDistToRoot());
	AssertInt(9, pTest3a->GetDistToRoot());

	gcObjects.ValidateConsistency();

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestUpdateAttachedTosDistToRootChildTriangleShortLeft(void)
{
	ObjectsInit();

	Ptr<CNamedPointerContainer>	p1a;
	Ptr<CNamedPointerContainer>	p1b;
	Ptr<CPointerContainer>		p2a;
	Ptr<CPointerContainer>		p2b;
	Ptr<CPointerContainer>		p3a;
	Ptr<CPointerContainer>		p3b;
	Ptr<CPointerContainer>		p4b;
	Ptr<CPointerContainer>		p5b;
	Ptr<CPointerContainer>		p6b;
	Ptr<CNamedPointerContainer>	p1c;
	Ptr<CPointerContainer>		p6c;
	Ptr<CRoot>					pRoot;
	Ptr<CTestObject>			pTest1a;
	Ptr<CTestObject>			pTest1b;
	Ptr<CTestObject>			pTest1c;
	Ptr<CTestObject>			pTest2a;
	Ptr<CTestObject>			pTest2b;
	Ptr<CTestObject>			pTest3a;

	CDistCalculatorParameters	cParameters;
	CDistToRootCalculator		cDistToRootCalculator;

	pRoot = ORoot();

	p6b = OMalloc(CPointerContainer)->Init();
	p6c = OMalloc(CPointerContainer)->Init();
	p5b = OMalloc(CPointerContainer)->Init(p6b);
	p4b = OMalloc(CPointerContainer)->Init(p5b);
	p3a = OMalloc(CPointerContainer)->Init();
	p3b	= OMalloc(CPointerContainer)->Init(p4b);
	p2a = OMalloc(CPointerContainer)->Init(p3a);
	p2b = OMalloc(CPointerContainer)->Init(p3b);
	p1a = ONMalloc(CNamedPointerContainer, "E.")->Init(p2a);
	p1b = ONMalloc(CNamedPointerContainer, "L.")->Init(p2b);
	p1c = ONMalloc(CNamedPointerContainer, "!!")->Init(p6c);
	pRoot->Add(p1a);
	pRoot->Add(p1b);
	pRoot->Add(p1c);

	pTest1a = OMalloc(CTestObject)->Init();
	pTest1b = OMalloc(CTestObject)->Init();
	pTest1c = OMalloc(CTestObject)->Init();
	pTest2a = OMalloc(CTestObject)->Init();
	pTest2b = OMalloc(CTestObject)->Init();
	pTest3a = OMalloc(CTestObject)->Init();
	p3a->mp = pTest1a;
	p6b->mp = pTest1c;
	p6c->mp = pTest1b;
	pTest1a->mpTest = pTest1b;
	pTest1c->mpTest = pTest1b;
	pTest1a->mpObject = pTest2a;
	pTest1c->mpObject = pTest2b;
	pTest1b->mpObject = pTest2a;
	pTest1b->mpTest = pTest2b;
	pTest2a->mpTest = pTest3a;
	pTest2b->mpTest = pTest3a;
	pTest2a->mpObject = pTest2b;

	AssertInt(2, p1a->GetDistToRoot());
	AssertInt(2, p1c->GetDistToRoot());
	AssertInt(2, p1b->GetDistToRoot());
	AssertInt(3, p2a->GetDistToRoot());
	AssertInt(3, p2b->GetDistToRoot());
	AssertInt(4, p3a->GetDistToRoot());
	AssertInt(4, p3b->GetDistToRoot());
	AssertInt(5, p4b->GetDistToRoot());
	AssertInt(6, p5b->GetDistToRoot());
	AssertInt(7, p6b->GetDistToRoot());
	AssertInt(3, p6c->GetDistToRoot());
	AssertInt(5, pTest1a->GetDistToRoot());
	AssertInt(4, pTest1b->GetDistToRoot());
	AssertInt(8, pTest1c->GetDistToRoot());
	AssertInt(5, pTest2a->GetDistToRoot());
	AssertInt(5, pTest2b->GetDistToRoot());
	AssertInt(6, pTest3a->GetDistToRoot());

	p6c->mp.UnsafeClearObject();
	pTest1b->TestRemoveHeapFrom(p6c.BaseObject());

	cParameters.Init();
	cDistToRootCalculator.Calculate(pTest1b.BaseObject(), &cParameters);
	cParameters.ClearTouchedFlags();
	cParameters.Kill();

	//                            
	//                 pTest3a(7)
	//                  /   \
	//                 /     \
	//                /       \
	//               /         \
	//              /           \
	//         pTest2a(6)-->pTest2b(7)
	//            |  \         /  |
	//            |   \       /   |
	//            |    \     /    |
	//            |     \   /     |
	//            |  pTest1b(6)   |
	//            |   /       \   |
	//            |  /         \  |
	//            | /           \ |
	//         pTest1a(5)       pTest1c(8)
	//            |               |
	//            .               .
	//            .               .

	AssertInt(5, pTest1a->GetDistToRoot());
	AssertInt(6, pTest1b->GetDistToRoot());
	AssertInt(8, pTest1c->GetDistToRoot());
	AssertInt(6, pTest2a->GetDistToRoot());
	AssertInt(7, pTest2b->GetDistToRoot());
	AssertInt(7, pTest3a->GetDistToRoot());

	gcObjects.ValidateConsistency();

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestUpdateEmbeddedObjectTosDetachedSetupDistance(void)
{
	ObjectsInit();

	Ptr<CTestObject>	pTest1;
	Ptr<CTestObject>	pLTest2;
	Ptr<CTestObject>	pRTest2;
	Ptr<CTestObject>	pLTest3;
	Ptr<CTestObject>	pRTest3l;
	Ptr<CTestObject>	pRTest3r;
	Ptr<CTestObject>	pRTest4l;
	Ptr<CTestObject>	pRTest4r;
	Ptr<CTestObject>	pRTest5l;
	Ptr<CTestObject>	pRTest5r;
	Ptr<CTestObject>	pRTest6l;
	Ptr<CTestObject>	pRTest6r;
	Ptr<CTestObject>	pRTest7l;
	Ptr<CTestObject>	pRTest8;
	Ptr<CRoot>			pRoot;

	pRoot = ORoot();
	pTest1 = OMalloc(CTestObject)->Init();
	pLTest2 = OMalloc(CTestObject)->Init();
	pRTest2 = OMalloc(CTestObject)->Init();
	pLTest3 = OMalloc(CTestObject)->Init();
	pRTest3l = OMalloc(CTestObject)->Init();
	pRTest3r = OMalloc(CTestObject)->Init();
	pRTest4l = OMalloc(CTestObject)->Init();
	pRTest4r = OMalloc(CTestObject)->Init();
	pRTest5l = OMalloc(CTestObject)->Init();
	pRTest5r = OMalloc(CTestObject)->Init();
	pRTest6l = OMalloc(CTestObject)->Init();
	pRTest6r = OMalloc(CTestObject)->Init();
	pRTest7l = OMalloc(CTestObject)->Init();
	pRTest8 = OMalloc(CTestObject)->Init();

	pRoot->Add(pTest1);

	pTest1->mpObject = pLTest2;
	pLTest2->mpObject = pLTest3;

	pTest1->mpTest = pRTest2;
	pRTest2->mpObject = pRTest3l;
	pRTest3l->mpObject = pRTest4l;
	pRTest4l->mpObject = pRTest5l;
	pRTest5l->mpObject = pRTest6l;
	pRTest6l->mpObject = pRTest7l;

	pLTest3->mpObject = pRTest6l;

	pRTest2->mpTest = pRTest3r;
	pRTest3r->mpTest = pRTest4r;
	pRTest4r->mpTest = pRTest5r;
	pRTest5r->mpTest = pRTest6r;

	pRTest7l->mpObject = pRTest8;
	pRTest6r->mpTest = pRTest8;

	//                             
	//                          pRTest8(7)
	//                           /   \
	//                          /     \
	//                         /       \
	//                        /         \
	//                       /           \
	//                 pRTest7l(6)     pRTest6r(7)
	//                      |             |
	//                      |             |
	//                 pRTest6l(5)        |
	//                   /   |            |
	//                  /    |            |
	//                 /  pRTest5l(6)  pRTest5r(6)
	//                /      |            |
	//               /       |            |
	//              /     pRTest4l(5)  pRTest4r(5)
	//             /         |            |
	//            /          |            |
	//        pLTest3(4)  pRTest3l(4)  pRTest3r(4)
	//           |            \          /
	//           |             \        /
	//           |              \      /
	//           |               \    /
	//           |                \  /
	//        pLTest2(3)       pRTest2(3)
	//             \             /
	//              \           /
	//               \         /
	//                \       /
	//                 \     /
	//                  \   /
	//                 pTest1(2)
	//                   |
	//                  ...
	//                 Root(0)
	//                       

	AssertInt(2, pTest1->GetDistToRoot());
	AssertInt(3, pLTest2->GetDistToRoot());
	AssertInt(3, pRTest2->GetDistToRoot());
	AssertInt(4, pLTest3->GetDistToRoot());
	AssertInt(4, pRTest3l->GetDistToRoot());
	AssertInt(4, pRTest3r->GetDistToRoot());
	AssertInt(5, pRTest4l->GetDistToRoot());
	AssertInt(5, pRTest4r->GetDistToRoot());
	AssertInt(6, pRTest5l->GetDistToRoot());
	AssertInt(6, pRTest5r->GetDistToRoot());
	AssertInt(5, pRTest6l->GetDistToRoot());
	AssertInt(7, pRTest6r->GetDistToRoot());
	AssertInt(6, pRTest7l->GetDistToRoot());
	AssertInt(7, pRTest8->GetDistToRoot());
	
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestUpdateEmbeddedObjectTosDetachedScenarioA(void)
{
	ObjectsInit();

	Ptr<CTestObject>			pTest1;
	Ptr<CTestObject>			pLTest2;
	Ptr<CTestObject>			pRTest2;
	Ptr<CTestObject>			pLTest3;
	Ptr<CTestObject>			pRTest3l;
	Ptr<CTestObject>			pRTest3r;
	Ptr<CTestObject>			pRTest4l;
	Ptr<CTestObject>			pRTest4r;
	Ptr<CTestObject>			pRTest5l;
	Ptr<CTestObject>			pRTest5r;
	Ptr<CTestObject>			pRTest6l;
	Ptr<CTestObject>			pRTest6r;
	Ptr<CTestObject>			pRTest7l;
	Ptr<CTestObject>			pRTest8;
	Ptr<CRoot>					pRoot;

	CDistToRootCalculator		cDistToRootCalculator;
	CDistCalculatorParameters	cDistParameters;

	pRoot = ORoot();
	pTest1 = OMalloc(CTestObject)->Init();
	pLTest2 = OMalloc(CTestObject)->Init();
	pRTest2 = OMalloc(CTestObject)->Init();
	pLTest3 = OMalloc(CTestObject)->Init();
	pRTest3l = OMalloc(CTestObject)->Init();
	pRTest3r = OMalloc(CTestObject)->Init();
	pRTest4l = OMalloc(CTestObject)->Init();
	pRTest4r = OMalloc(CTestObject)->Init();
	pRTest5l = OMalloc(CTestObject)->Init();
	pRTest5r = OMalloc(CTestObject)->Init();
	pRTest6l = OMalloc(CTestObject)->Init();
	pRTest6r = OMalloc(CTestObject)->Init();
	pRTest7l = OMalloc(CTestObject)->Init();
	pRTest8 = OMalloc(CTestObject)->Init();

	pRoot->Add(pTest1);

	pTest1->mpObject = pLTest2;
	pLTest2->mpObject = pLTest3;

	pTest1->mpTest = pRTest2;
	pRTest2->mpObject = pRTest3l;
	pRTest3l->mpObject = pRTest4l;
	pRTest4l->mpObject = pRTest5l;
	pRTest5l->mpObject = pRTest6l;
	pRTest6l->mpObject = pRTest7l;

	pLTest3->mpObject = pRTest6l;

	pRTest2->mpTest = pRTest3r;
	pRTest3r->mpTest = pRTest4r;
	pRTest4r->mpTest = pRTest5r;
	pRTest5r->mpTest = pRTest6r;

	pRTest7l->mpObject = pRTest8;
	pRTest6r->mpTest = pRTest8;

	pTest1->mpObject.UnsafeClearObject();
	pLTest2->TestRemoveHeapFrom(pTest1.BaseObject());


	cDistParameters.Init();
	cDistToRootCalculator.Calculate(pLTest2.BaseObject(), &cDistParameters);
	cDistParameters.ClearTouchedFlags();

	//                             
	//                          pRTest8(8)
	//                           /   \
	//                          /     \
	//                         /       \
	//                        /         \
	//                       /           \
	//                 pRTest7l(8)     pRTest6r(7)
	//                      |             |
	//                      |             |
	//                 pRTest6l(7)        |
	//                   .   |            |
	//                  .    |            |
	//                 .  pRTest5l(6)  pRTest5r(6)
	//                .      |            |
	//               .       |            |
	//              .     pRTest4l(5)  pRTest4r(5)
	//             .         |            |
	//            .          |            |
	//        pLTest3(X)  pRTest3l(4)  pRTest3r(4)
	//           .            \          /
	//           .             \        /
	//           .              \      /
	//           .               \    /
	//           .                \  /
	//        pLTest2(X)       pRTest2(3)
	//             .             /
	//              .           /
	//               .         /
	//                .       /
	//                 .     /
	//                  .   /
	//                 pTest1(2)
	//                    |
	//                   ...
	//                  Root(0)
	//                       

	AssertInt(UNATTACHED_DIST_TO_ROOT, pLTest2->GetDistToRoot());
	AssertFalse(pLTest2->CanFindRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pLTest3->GetDistToRoot());
	AssertFalse(pLTest3->CanFindRoot());
	AssertInt(7, pRTest6l->GetDistToRoot());
	AssertInt(8, pRTest7l->GetDistToRoot());
	AssertInt(8, pRTest8->GetDistToRoot());

	AssertInt(8, cDistParameters.NumTouched());

	cDistParameters.Kill();

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestUpdateEmbeddedObjectTosDetachedScenarioB(void)
{
	ObjectsInit();

	Ptr<CTestObject>			pTest1;
	Ptr<CTestObject>			pLTest2;
	Ptr<CTestObject>			pRTest2;
	Ptr<CTestObject>			pLTest3;
	Ptr<CTestObject>			pRTest3l;
	Ptr<CTestObject>			pRTest3r;
	Ptr<CTestObject>			pRTest4l;
	Ptr<CTestObject>			pRTest4r;
	Ptr<CTestObject>			pRTest5l;
	Ptr<CTestObject>			pRTest5r;
	Ptr<CTestObject>			pRTest6l;
	Ptr<CTestObject>			pRTest6r;
	Ptr<CTestObject>			pRTest7l;
	Ptr<CTestObject>			pRTest8;
	Ptr<CRoot>					pRoot;

	CDistToRootCalculator		cDistToRootCalculator;
	CDistCalculatorParameters	cDistParameters;

	pRoot = ORoot();
	pTest1 = OMalloc(CTestObject)->Init();
	pLTest2 = OMalloc(CTestObject)->Init();
	pRTest2 = OMalloc(CTestObject)->Init();
	pLTest3 = OMalloc(CTestObject)->Init();
	pRTest3l = OMalloc(CTestObject)->Init();
	pRTest3r = OMalloc(CTestObject)->Init();
	pRTest4l = OMalloc(CTestObject)->Init();
	pRTest4r = OMalloc(CTestObject)->Init();
	pRTest5l = OMalloc(CTestObject)->Init();
	pRTest5r = OMalloc(CTestObject)->Init();
	pRTest6l = OMalloc(CTestObject)->Init();
	pRTest6r = OMalloc(CTestObject)->Init();
	pRTest7l = OMalloc(CTestObject)->Init();
	pRTest8 = OMalloc(CTestObject)->Init();

	pRoot->Add(pTest1);

	pTest1->mpObject = pLTest2;
	pLTest2->mpObject = pLTest3;

	pTest1->mpTest = pRTest2;
	pRTest2->mpObject = pRTest3l;
	pRTest3l->mpObject = pRTest4l;
	pRTest4l->mpObject = pRTest5l;
	pRTest5l->mpObject = pRTest6l;
	pRTest6l->mpObject = pRTest7l;

	pLTest3->mpObject = pRTest6l;

	pRTest2->mpTest = pRTest3r;
	pRTest3r->mpTest = pRTest4r;
	pRTest4r->mpTest = pRTest5r;
	pRTest5r->mpTest = pRTest6r;

	pRTest7l->mpObject = pRTest8;
	pRTest6r->mpTest = pRTest8;

	pTest1->mpTest.UnsafeClearObject();
	pRTest2->TestRemoveHeapFrom(pTest1.BaseObject());


	cDistParameters.Init();
	cDistToRootCalculator.Calculate(pRTest2.BaseObject(), &cDistParameters);
	cDistParameters.ClearTouchedFlags();

	//                             
	//                          pRTest8(7)
	//                           /   .
	//                          /     .
	//                         /       .
	//                        /         .
	//                       /           .
	//                 pRTest7l(6)     pRTest6r(X)
	//                      |             .
	//                      |             .
	//                 pRTest6l(5)        .
	//                   /   .            .
	//                  /    .            .
	//                 /  pRTest5l(X)  pRTest5r(X)
	//                /      .            .
	//               /       .            .
	//              /     pRTest4l(X)  pRTest4r(X)
	//             /         .            .
	//            /          .            .
	//        pLTest3(4)  pRTest3l(X)  pRTest3r(x)
	//           |            .          .
	//           |             .        .
	//           |              .      .
	//           |               .    .
	//           |                .  .
	//        pLTest2(3)       pRTest2(X)
	//             \             .
	//              \           .
	//               \         .
	//                \       .
	//                 \     .
	//                  \   .
	//                 pTest1(2)
	//                    |
	//                   ...
	//                  Root(0)
	//                       

	AssertInt(UNATTACHED_DIST_TO_ROOT, pRTest2->GetDistToRoot());
	AssertFalse(pRTest2->CanFindRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pRTest3l->GetDistToRoot());
	AssertFalse(pRTest3l->CanFindRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pRTest3r->GetDistToRoot());
	AssertFalse(pRTest3r->CanFindRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pRTest4l->GetDistToRoot());
	AssertFalse(pRTest4l->CanFindRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pRTest4r->GetDistToRoot());
	AssertFalse(pRTest4r->CanFindRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pRTest5l->GetDistToRoot());
	AssertFalse(pRTest5l->CanFindRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pRTest5r->GetDistToRoot());
	AssertFalse(pRTest5r->CanFindRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pRTest6r->GetDistToRoot());
	AssertFalse(pRTest6r->CanFindRoot());

	AssertInt(6, pRTest7l->GetDistToRoot());
	AssertInt(7, pRTest8->GetDistToRoot());

	cDistParameters.Kill();

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestUpdateEmbeddedObjectTosDetachedScenarioC(void)
{
	ObjectsInit();

	Ptr<CTestObject>			pTest1;
	Ptr<CTestObject>			pLTest2;
	Ptr<CTestObject>			pRTest2;
	Ptr<CTestObject>			pLTest3;
	Ptr<CTestObject>			pRTest3l;
	Ptr<CTestObject>			pRTest3r;
	Ptr<CTestObject>			pRTest4l;
	Ptr<CTestObject>			pRTest4r;
	Ptr<CTestObject>			pRTest5l;
	Ptr<CTestObject>			pRTest5r;
	Ptr<CTestObject>			pRTest6l;
	Ptr<CTestObject>			pRTest6r;
	Ptr<CTestObject>			pRTest7l;
	Ptr<CTestObject>			pRTest8;
	Ptr<CRoot>					pRoot;

	CDistToRootCalculator		cDistToRootCalculator;
	CDistCalculatorParameters	cDistParameters;

	pRoot = ORoot();
	pTest1 = OMalloc(CTestObject)->Init();
	pLTest2 = OMalloc(CTestObject)->Init();
	pRTest2 = OMalloc(CTestObject)->Init();
	pLTest3 = OMalloc(CTestObject)->Init();
	pRTest3l = OMalloc(CTestObject)->Init();
	pRTest3r = OMalloc(CTestObject)->Init();
	pRTest4l = OMalloc(CTestObject)->Init();
	pRTest4r = OMalloc(CTestObject)->Init();
	pRTest5l = OMalloc(CTestObject)->Init();
	pRTest5r = OMalloc(CTestObject)->Init();
	pRTest6l = OMalloc(CTestObject)->Init();
	pRTest6r = OMalloc(CTestObject)->Init();
	pRTest7l = OMalloc(CTestObject)->Init();
	pRTest8 = OMalloc(CTestObject)->Init();

	pRoot->Add(pTest1);

	pTest1->mpObject = pLTest2;
	pLTest2->mpObject = pLTest3;

	pTest1->mpTest = pRTest2;
	pRTest2->mpObject = pRTest3l;
	pRTest3l->mpObject = pRTest4l;
	pRTest4l->mpObject = pRTest5l;
	pRTest5l->mpObject = pRTest6l;
	pRTest6l->mpObject = pRTest7l;

	pLTest3->mpObject = pRTest6l;

	pRTest2->mpTest = pRTest3r;
	pRTest3r->mpTest = pRTest4r;
	pRTest4r->mpTest = pRTest5r;
	pRTest5r->mpTest = pRTest6r;

	pRTest7l->mpObject = pRTest8;
	pRTest6r->mpTest = pRTest8;

	pRTest2->mpObject.UnsafeClearObject();
	pRTest3l->TestRemoveHeapFrom(pRTest2.BaseObject());


	cDistParameters.Init();
	cDistToRootCalculator.Calculate(pRTest3l.BaseObject(), &cDistParameters);
	cDistParameters.ClearTouchedFlags();

	//                             
	//                          pRTest8(7)
	//                           /   \
	//                          /     \
	//                         /       \
	//                        /         \
	//                       /           \
	//                 pRTest7l(6)     pRTest6r(7)
	//                      |             |
	//                      |             |
	//                 pRTest6l(5)        |
	//                   /   .            |
	//                  /    .            |
	//                 /  pRTest5l(X)  pRTest5r(6)
	//                /      .            |
	//               /       .            |
	//              /     pRTest4l(X)  pRTest4r(5)
	//             /         .            |
	//            /          .            |
	//        pLTest3(4)  pRTest3l(X)  pRTest3r(4)
	//           |            .          /
	//           |             .        /
	//           |              .      /
	//           |               .    /
	//           |                .  /
	//        pLTest2(3)       pRTest2(3)
	//             \             /
	//              \           /
	//               \         /
	//                \       /
	//                 \     /
	//                  \   /
	//                 pTest1(2)
	//                    |
	//                   ...
	//                  Root(0)
	//                       

	AssertInt(UNATTACHED_DIST_TO_ROOT, pRTest3l->GetDistToRoot());
	AssertFalse(pRTest3l->CanFindRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pRTest4l->GetDistToRoot());
	AssertFalse(pRTest4l->CanFindRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pRTest5l->GetDistToRoot());
	AssertFalse(pRTest5l->CanFindRoot());

	AssertInt(5, pRTest6l->GetDistToRoot());
	AssertInt(4, pRTest3r->GetDistToRoot());

	cDistParameters.Kill();

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestUpdateEmbeddedObjectTosDetachedScenarioD(void)
{
	ObjectsInit();

	Ptr<CTestObject>			pTest1;
	Ptr<CTestObject>			pLTest2;
	Ptr<CTestObject>			pRTest2;
	Ptr<CTestObject>			pLTest3;
	Ptr<CTestObject>			pRTest3l;
	Ptr<CTestObject>			pRTest3r;
	Ptr<CTestObject>			pRTest4l;
	Ptr<CTestObject>			pRTest4r;
	Ptr<CTestObject>			pRTest5l;
	Ptr<CTestObject>			pRTest5r;
	Ptr<CTestObject>			pRTest6l;
	Ptr<CTestObject>			pRTest6r;
	Ptr<CTestObject>			pRTest7l;
	Ptr<CTestObject>			pRTest8;
	Ptr<CRoot>					pRoot;

	CDistToRootCalculator		cDistToRootCalculator;
	CDistCalculatorParameters	cDistParameters;

	pRoot = ORoot();
	pTest1 = OMalloc(CTestObject)->Init();
	pLTest2 = OMalloc(CTestObject)->Init();
	pRTest2 = OMalloc(CTestObject)->Init();
	pLTest3 = OMalloc(CTestObject)->Init();
	pRTest3l = OMalloc(CTestObject)->Init();
	pRTest3r = OMalloc(CTestObject)->Init();
	pRTest4l = OMalloc(CTestObject)->Init();
	pRTest4r = OMalloc(CTestObject)->Init();
	pRTest5l = OMalloc(CTestObject)->Init();
	pRTest5r = OMalloc(CTestObject)->Init();
	pRTest6l = OMalloc(CTestObject)->Init();
	pRTest6r = OMalloc(CTestObject)->Init();
	pRTest7l = OMalloc(CTestObject)->Init();
	pRTest8 = OMalloc(CTestObject)->Init();

	pRoot->Add(pTest1);

	pTest1->mpObject = pLTest2;
	pLTest2->mpObject = pLTest3;

	pTest1->mpTest = pRTest2;
	pRTest2->mpObject = pRTest3l;
	pRTest3l->mpObject = pRTest4l;
	pRTest4l->mpObject = pRTest5l;
	pRTest5l->mpObject = pRTest6l;
	pRTest6l->mpObject = pRTest7l;

	pLTest3->mpObject = pRTest6l;

	pRTest2->mpTest = pRTest3r;
	pRTest3r->mpTest = pRTest4r;
	pRTest4r->mpTest = pRTest5r;
	pRTest5r->mpTest = pRTest6r;

	pRTest7l->mpObject = pRTest8;
	pRTest6r->mpTest = pRTest8;

	pRTest2->mpTest.UnsafeClearObject();
	pRTest3r->TestRemoveHeapFrom(pRTest2.BaseObject());


	cDistParameters.Init();
	cDistToRootCalculator.Calculate(pRTest3r.BaseObject(), &cDistParameters);
	cDistParameters.ClearTouchedFlags();

	//                             
	//                          pRTest8(7)
	//                           /   .
	//                          /     .
	//                         /       .
	//                        /         .
	//                       /           .
	//                 pRTest7l(6)     pRTest6r(X)
	//                      |             .
	//                      |             .
	//                 pRTest6l(5)        .
	//                   /   |            .
	//                  /    |            .
	//                 /  pRTest5l(6)  pRTest5r(X)
	//                /      |            .
	//               /       |            .
	//              /     pRTest4l(5)  pRTest4r(X)
	//             /         |            .
	//            /          |            .
	//        pLTest3(4)  pRTest3l(4)  pRTest3r(X)
	//           |            \          .
	//           |             \        .
	//           |              \      .
	//           |               \    .
	//           |                \  .
	//        pLTest2(3)       pRTest2(3)
	//             \             /
	//              \           /
	//               \         /
	//                \       /
	//                 \     /
	//                  \   /
	//                 pTest1(2)
	//                    |
	//                   ...
	//                  Root(0)
	//                       

	AssertInt(UNATTACHED_DIST_TO_ROOT, pRTest3r->GetDistToRoot());
	AssertFalse(pRTest3r->CanFindRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pRTest4r->GetDistToRoot());
	AssertFalse(pRTest4r->CanFindRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pRTest5r->GetDistToRoot());
	AssertFalse(pRTest5r->CanFindRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pRTest6r->GetDistToRoot());
	AssertFalse(pRTest6r->CanFindRoot());

	AssertInt(7, pRTest8->GetDistToRoot());
	AssertInt(4, pRTest3l->GetDistToRoot());

	cDistParameters.Kill();

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestUpdateAttachedTosDistToRootBroken(void)
{
	ObjectsInit();

	Ptr<CPointerContainer>		p6b;
	Ptr<CPointerContainer>		p6c;
	Ptr<CRoot>					pRoot;
	Ptr<CTestObject>			pTest1a;
	Ptr<CTestObject>			pTest1b;
	Ptr<CTestObject>			pTest2a;

	CDistCalculatorParameters	cParameters;
	CDistToRootCalculator		cDistToRootCalculator;

	pRoot = ORoot();
	p6b = OMalloc(CPointerContainer)->Init();
	p6c = OMalloc(CPointerContainer)->Init();
	pRoot->Add(p6b);
	pRoot->Add(p6c);

	pTest1a = OMalloc(CTestObject)->Init();
	pTest1b = OMalloc(CTestObject)->Init();
	pTest2a = OMalloc(CTestObject)->Init();
	p6b->mp = pTest1a;
	p6c->mp = pTest1b;
	pTest1a->mpTest = pTest1b;
	pTest1a->mpObject = pTest2a;
	pTest1b->mpObject = pTest2a;

	//
	//         pTest2a[7](4)
	//            |  \   
	//            |   \  
	//            |    \ 
	//            |     \
	//            |  pTest1b[6](3)  
	//            |   /     |
	//            |  /      |
	//            | /       |
	//        pTest1a[5](3) |
	//            |         |
	//            |         |
	//           p6b[3](2) p6c[4](2)
	//             \       /
	//              \     /
	//               \   /
	//               ...
	//              Root(0)
	//                         

	AssertInt(2, p6b->GetDistToRoot());
	AssertInt(2, p6c->GetDistToRoot());
	AssertInt(3, pTest1a->GetDistToRoot());
	AssertInt(3, pTest1b->GetDistToRoot());
	AssertInt(4, pTest2a->GetDistToRoot());

	p6c->mp.UnsafeClearObject();
	pTest1b->TestRemoveHeapFrom(p6c.BaseObject());

	cParameters.Init();
	cDistToRootCalculator.Calculate(pTest1b.BaseObject(), &cParameters);
	cParameters.ClearTouchedFlags();
	cParameters.Kill();

	//
	//         pTest2a(4)
	//            |  \   
	//            |   \  
	//            |    \ 
	//            |     \
	//            |  pTest1b(4)  
	//            |   /   
	//            |  /    
	//            | /     
	//         pTest1a(3) 
	//             |       
	//             |       
	//            p6b(2)  
	//             |  
	//             |
	//            ...
	//           Root(0)
	//                         

	AssertInt(3, pTest1a->GetDistToRoot());
	AssertInt(4, pTest1b->GetDistToRoot());
	AssertInt(4, pTest2a->GetDistToRoot());

	gcObjects.ValidateConsistency();

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestClearDistToRootToValidDistBroken(void)
{
	ObjectsInit();

	Ptr<CPointerContainer>		p6b;
	Ptr<CPointerContainer>		p6c;
	Ptr<CRoot>					pRoot;
	Ptr<CTestObject>			pTest1a;
	Ptr<CTestObject>			pTest1b;
	Ptr<CTestObject>			pTest2a;
	Ptr<CTestObject>			pTest2b;
	Ptr<CTestObject>			pTest3a;


	CDistCalculatorParameters	cDistParameters;
	SDistToRoot*				psDistToRoot;

	pRoot = ORoot();
	p6b = OMalloc(CPointerContainer)->Init();
	p6c = OMalloc(CPointerContainer)->Init();
	pRoot->Add(p6b);
	pRoot->Add(p6c);

	pTest1a = OMalloc(CTestObject)->Init();
	pTest1b = OMalloc(CTestObject)->Init();
	pTest2a = OMalloc(CTestObject)->Init();
	pTest2b = OMalloc(CTestObject)->Init();
	pTest3a = OMalloc(CTestObject)->Init();
	p6b->mp = pTest1a;
	p6c->mp = pTest1b;
	pTest1a->mpTest = pTest1b;
	pTest1a->mpObject = pTest2a;
	pTest1b->mpObject = pTest2a;
	pTest2a->mpObject = pTest3a;
	pTest1b->mpTest = pTest2b;

	//
	//         pTest3a[9](5)
	//            |
	//            |
	//         pTest2a[7](4)  pTest2b[8](4)
	//            | \          /
	//            |  \        /
	//            |   \      /
	//            |  pTest1b[6](3)  
	//            |   /     |
	//            |  /      |
	//            | /       |
	//        pTest1a[5](3) |
	//            |         |
	//            |         |
	//           p6b[3](2) p6c[4](2)
	//             \       /
	//              \     /
	//               \   /
	//               ...
	//              Root(0)
	//                         
	
	AssertLongLongInt(3LL, p6b->GetOI());
	AssertLongLongInt(4LL, p6c->GetOI());
	AssertLongLongInt(5LL, pTest1a->GetOI());
	AssertLongLongInt(6LL, pTest1b->GetOI());
	AssertLongLongInt(7LL, pTest2a->GetOI());
	AssertLongLongInt(8LL, pTest2b->GetOI());
	AssertLongLongInt(9LL, pTest3a->GetOI());

	AssertInt(2, p6b->GetDistToRoot());
	AssertInt(2, p6c->GetDistToRoot());
	AssertInt(3, pTest1a->GetDistToRoot());
	AssertInt(3, pTest1b->GetDistToRoot());
	AssertInt(4, pTest2a->GetDistToRoot());
	AssertInt(4, pTest2b->GetDistToRoot());
	AssertInt(5, pTest3a->GetDistToRoot());

	p6c->mp.UnsafeClearObject();
	pTest1b->TestRemoveHeapFrom(p6c.BaseObject());

	cDistParameters.Init();
	pTest1b->CollectValidDistStartingObjectsAndSetClearedToRoot(NULL, &cDistParameters);

	AssertInt(1, cDistParameters.NumExpectedDists());
	psDistToRoot = cDistParameters.GetLowestExpectedDist();
	AssertLongLongInt(6LL, psDistToRoot->pcObject->GetOI());
	AssertInt(4, psDistToRoot->iExpectedDist);

	AssertInt(2, p6b->GetDistToRoot());
	AssertInt(2, p6c->GetDistToRoot());
	AssertInt(3, pTest1a->GetDistToRoot());
	AssertInt(CLEARED_DIST_TO_ROOT, pTest1b->GetDistToRoot());
	AssertInt(4, pTest2a->GetDistToRoot());
	AssertInt(4, pTest2b->GetDistToRoot());
	AssertInt(5, pTest3a->GetDistToRoot());

	cDistParameters.Kill();

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDistToRootLinear(void)
{
	ObjectsInit();

	CDistToRootCalculator		cDistToRootCalculator;
	CDistCalculatorParameters	cDistParameters;

	Ptr<CNamedPointerContainer>	p1 = ONMalloc(CNamedPointerContainer, "Pointer A")->Init();
	Ptr<CNamedPointerContainer>	p2 = ONMalloc(CNamedPointerContainer, "Pointer B")->Init();
	p1->mp = p2;

	Ptr<CRoot> pRoot = ORoot();
	Ptr<CNamedPointerContainer>	p0 = ONMalloc(CNamedPointerContainer, "Test Helper")->Init(p1);
	pRoot->Add(p0);

	//
	//               p2(4)
	//                |
	//                |
	//               p1(3)
	//                |
	//                |
	//               p0(2)
	//                |
	//                |
	//               ...
	//              Root(0)
	//                         

	AssertInt(2, p0->GetDistToRoot());
	AssertInt(3, p1->GetDistToRoot());
	AssertInt(4, p2->GetDistToRoot());

	p0->mp.UnsafeClearObject();
	p1->TestRemoveHeapFrom(p0.BaseObject());

	cDistParameters.Init();
	cDistToRootCalculator.Calculate(p1.BaseObject(), &cDistParameters);
	cDistParameters.ClearTouchedFlags();

	AssertInt(2, p0->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, p1->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, p2->GetDistToRoot());

	AssertInt(2, cDistParameters.NumTouched());

	cDistParameters.Kill();

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDistToRootCyclic(void)
{
	ObjectsInit();

	CDistToRootCalculator		cDistToRootCalculator;
	CDistCalculatorParameters	cDistParameters;

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
	//           p3(5)<--p2(4)
	//             \     ^
	//              \   /
	//               v /
	//               p1(3)
	//                ^
	//                |
	//               p0(2)
	//                ^
	//                |
	//               ...
	//              Root(0)
	//                         

	AssertInt(2, p0->GetDistToRoot());
	AssertInt(3, p1->GetDistToRoot());
	AssertInt(4, p2->GetDistToRoot());
	AssertInt(5, p3->GetDistToRoot());

	p0->mp.UnsafeClearObject();
	p1->TestRemoveHeapFrom(p0.BaseObject());

	cDistParameters.Init();
	cDistToRootCalculator.Calculate(p1.BaseObject(), &cDistParameters);
	cDistParameters.ClearTouchedFlags();

	AssertInt(UNATTACHED_DIST_TO_ROOT, p1->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, p2->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, p3->GetDistToRoot());

	gcObjects.ValidateConsistency();

	cDistParameters.Kill();

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDistToRootWithStackPointers(void)
{
	Ptr<CTestObject>			cNS1;
	Ptr<CTestObject>			cNS2;
	Ptr<CTestObject>			cNS3;
	Ptr<CString>				sz1;
	Ptr<CString>				sz2;

	ObjectsInit();

	cNS3 = OMalloc(CTestObject);
	cNS1 = OMalloc(CTestObject);
	sz1 = OMalloc(CString);
	cNS2 = OMalloc(CTestObject);
	sz2 = OMalloc(CString);

	AssertLongLongInt(1, cNS3.GetIndex());
	AssertLongLongInt(2, cNS1.GetIndex());
	AssertLongLongInt(3, sz1.GetIndex());
	AssertLongLongInt(4, cNS2.GetIndex());
	AssertLongLongInt(5, sz2.GetIndex());

	sz1->Init("Back");
	cNS1->Init(sz1, cNS3);

	sz2->Init("Down");
	cNS2->Init(sz2, cNS3);

	gcObjects.ValidateConsistency();

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDistToRootLinearToStackScenarioA(void)
{
	ObjectsInit();

	CDistToRootCalculator		cDistToRootCalculator;
	CDistCalculatorParameters	cDistParameters;
	CNamedPointerContainer*		pc1;
	CNamedPointerContainer*		pc0;
	CNamedPointerContainer*		pc2;

	Ptr<CNamedPointerContainer>	p1 = ONMalloc(CNamedPointerContainer, "Pointer A")->Init();
	Ptr<CNamedPointerContainer>	p2 = ONMalloc(CNamedPointerContainer, "Pointer B")->Init();
	p1->mp = p2;

	Ptr<CRoot> pRoot = ORoot();
	Ptr<CNamedPointerContainer>	p0 = ONMalloc(CNamedPointerContainer, "Test Helper")->Init(p1);
	pRoot->Add(p0);

	pc1 = &p1;
	pc2 = &p2;
	pc0 = &p0;

	p0 = NULL;
	p1 = NULL;

	//
	//               p2(4)
	//                ^  ^
	//                |   .
	//                |    .
	//               p1(3)
	//                ^
	//                |
	//                |
	//               p0(2)
	//                ^
	//                |
	//                |
	//               ...
	//              Root(0)
	//                         

	AssertInt(2, pc0->GetDistToRoot());
	AssertInt(3, pc1->GetDistToRoot());
	AssertInt(4, pc2->GetDistToRoot());

	pc0->mp.UnsafeClearObject();
	pc1->TestRemoveHeapFrom(pc0);

	cDistParameters.Init();

	cDistToRootCalculator.Calculate(pc1, &cDistParameters);
	cDistParameters.ClearTouchedFlags();

	//
	//                    p2(-1)
	//                    ^  ^
	//                   /   .
	//              p1(-1)   .
	//                       .
	//                   
	//               p0(2)
	//                ^
	//                |
	//                |
	//               ...
	//              Root(0)
	//             
	// p1 is completely unattached but the DistCaclulator doesn't kill it.

	AssertInt(2, pc0->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pc1->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pc2->GetDistToRoot());
	AssertFalse(pc1->CanFindRoot());
	AssertFalse(pc1->CanFindRootThroughValidPath());
	AssertFalse(pc2->CanFindRoot());
	AssertFalse(pc2->CanFindRootThroughValidPath());

	cDistParameters.Kill();

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDistToRootLinearToStackScenarioB(void)
{
	ObjectsInit();

	CDistToRootCalculator		cDistToRootCalculator;
	CDistCalculatorParameters	cDistParameters;
	CNamedPointerContainer*		pc1;
	CNamedPointerContainer*		pc0;
	CNamedPointerContainer*		pc2;

	Ptr<CNamedPointerContainer>	p1 = ONMalloc(CNamedPointerContainer, "Pointer A")->Init();
	Ptr<CNamedPointerContainer>	p2 = ONMalloc(CNamedPointerContainer, "Pointer B")->Init();
	p1->mp = p2;

	Ptr<CRoot> pRoot = ORoot();
	Ptr<CNamedPointerContainer>	p0 = ONMalloc(CNamedPointerContainer, "Test Helper")->Init(p1);
	pRoot->Add(p0);

	pc1 = &p1;
	pc2 = &p2;
	pc0 = &p0;

	p0 = NULL;
	p2 = NULL;

	//
	//               p2(4)
	//                ^  
	//                |  
	//                |  
	//               p1(3)
	//                ^  ^
	//                |	  .
	//                |	   .
	//               p0(2)
	//                ^
	//                |
	//                |
	//               ...
	//              Root(0)
	//                         

	AssertInt(2, pc0->GetDistToRoot());
	AssertInt(3, pc1->GetDistToRoot());
	AssertInt(4, pc2->GetDistToRoot());

	pc0->mp.UnsafeClearObject();
	pc1->TestRemoveHeapFrom(pc0);

	cDistParameters.Init();
	cDistToRootCalculator.Calculate(pc1, &cDistParameters);
	cDistParameters.ClearTouchedFlags();

	//
	//                      p2(-2)
	//                       ^  
	//                       |  
	//                       |  
	//                      p1(-1)
	//                       ^
	//                       .
	//                       .
	//               p0(2)
	//                ^
	//                |
	//                |
	//               ...
	//              Root(0)
	//     

	AssertInt(2, pc0->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pc1->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pc2->GetDistToRoot());
	AssertFalse(pc1->CanFindRoot());
	AssertFalse(pc1->CanFindRootThroughValidPath());
	AssertFalse(pc2->CanFindRoot());
	AssertFalse(pc2->CanFindRootThroughValidPath());

	cDistParameters.Kill();

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDistToRootTosNotUpdated(void)
{
	ObjectsInit();

	CDistToRootCalculator		cDistToRootCalculator;
	CDistCalculatorParameters	cDistParameters;

	CTestObject*		pcTest1;
	CTestObject*		pcTest2;
	CTestObject*		pcTest3;
	CSetObject*			pcSet;

	Ptr<CTestObject>	pTest1;
	Ptr<CTestObject>	pTest2;
	Ptr<CTestObject>	pTest3;
	Ptr<CRoot>			pRoot;

	pRoot = ORoot();
	pTest1 = OMalloc(CTestObject);
	pTest2 = OMalloc(CTestObject);
	pTest3 = OMalloc(CTestObject);

	pTest1->mpTest = pTest2;
	pTest2->mpTest = pTest3;
	pTest2->mpObject = pTest1;

	pRoot->Add(pTest1);
	
	AssertInt(2, pTest1->GetDistToRoot());
	AssertInt(3, pTest2->GetDistToRoot());
	AssertInt(4, pTest3->GetDistToRoot());

	pcTest1 = &pTest1;
	pcTest2	= &pTest2;
	pcTest3	= &pTest3;

	AssertTrue(pTest3->CanFindRootThroughValidPath());

	pTest2 = NULL;
	pTest3 = NULL;

	//
	//   pTest3[4](4)
	//       ^
	//       |      
	//       |      
	//   pTest2[3](3)
	//      |^
	//      ||
	//      v|
	//   pTest1[2](2)
	//   ^   ^
	//  .    |
	// .     |
	//   SetObject[1](1)
	//       ^
	//       |
	//       |
	//    pRoot[1,GraphRoot](0)
	//  

	pcSet = pRoot->TestGetSet();
	pcSet->UnsafeRemove(pcTest1);
	pcTest1->TestRemoveHeapFrom(pcSet);

	AssertInt(0, pcSet->NumElements());
	AssertInt(1, pcTest1->NumHeapFroms()); //pointed to from pTest2
	AssertInt(1, pcTest1->NumStackFroms());

	cDistParameters.Init();


	cDistToRootCalculator.Calculate(pcTest1, &cDistParameters);
	cDistParameters.ClearTouchedFlags();
	
	AssertInt(UNATTACHED_DIST_TO_ROOT, pcTest1->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pcTest2->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pcTest3->GetDistToRoot());


	cDistParameters.Kill();

	gcObjects.ValidateConsistency();

	ObjectsKill();
};


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDistToRootComplex(void)
{
	ObjectsInit();

	CDistToRootCalculator		cDistToRootCalculator;
	CDistCalculatorParameters	cDistParameters;

	Ptr<CRoot> pRoot = ORoot();

	Ptr<CTestObject> pTest3  = OMalloc(CTestObject)->Init();
	Ptr<CTestObject> pTest4  = OMalloc(CTestObject)->Init();
	Ptr<CTestObject> pTest5  = OMalloc(CTestObject)->Init();
	Ptr<CTestObject> pTest6  = OMalloc(CTestObject)->Init();
	Ptr<CTestObject> pTest7  = OMalloc(CTestObject)->Init();
	Ptr<CTestObject> pTest8  = OMalloc(CTestObject)->Init();
	Ptr<CTestObject> pTest9  = OMalloc(CTestObject)->Init();
	Ptr<CTestObject> pTest10 = OMalloc(CTestObject)->Init();
	Ptr<CTestObject> pTest11 = OMalloc(CTestObject)->Init();
	Ptr<CTestObject> pTest12 = OMalloc(CTestObject)->Init();
	Ptr<CTestObject> pTest13 = OMalloc(CTestObject)->Init();
	Ptr<CTestObject> pTest14 = OMalloc(CTestObject)->Init();
	Ptr<CTestObject> pTest15 = OMalloc(CTestObject)->Init();
	Ptr<CTestObject> pTest16 = OMalloc(CTestObject)->Init();
	Ptr<CTestObject> pTest17 = OMalloc(CTestObject)->Init();
	Ptr<CTestObject> pTest18 = OMalloc(CTestObject)->Init();
	Ptr<CTestObject> pTest19 = OMalloc(CTestObject)->Init();
	Ptr<CTestObject> pTest20 = OMalloc(CTestObject)->Init();
	Ptr<CTestObject> pTest21 = OMalloc(CTestObject)->Init();
	Ptr<CTestObject> pTest22 = OMalloc(CTestObject)->Init();
	Ptr<CTestObject> pTest23 = OMalloc(CTestObject)->Init();
	Ptr<CTestObject> pTest24 = OMalloc(CTestObject)->Init();

	CTestObject* pcTest3  = &pTest3;
	CTestObject* pcTest4  = &pTest4;
	CTestObject* pcTest5  = &pTest5;
	CTestObject* pcTest6  = &pTest6;
	CTestObject* pcTest7  = &pTest7;
	CTestObject* pcTest8  = &pTest8;
	CTestObject* pcTest9  = &pTest9;
	CTestObject* pcTest10 = &pTest10;
	CTestObject* pcTest11 = &pTest11;
	CTestObject* pcTest12 = &pTest12;
	CTestObject* pcTest13 = &pTest13;
	CTestObject* pcTest14 = &pTest14;
	CTestObject* pcTest15 = &pTest15;
	CTestObject* pcTest16 = &pTest16;
	CTestObject* pcTest17 = &pTest17;
	CTestObject* pcTest18 = &pTest18;
	CTestObject* pcTest19 = &pTest19;
	CTestObject* pcTest20 = &pTest20;
	CTestObject* pcTest21 = &pTest21;
	CTestObject* pcTest22 = &pTest22;
	CTestObject* pcTest23 = &pTest23;
	CTestObject* pcTest24 = &pTest24;

	pRoot->Add(pTest3);
	pRoot->Add(pTest4);

	pTest4->mpTest = pTest5;
	pTest5->mpTest = pTest6;
	pTest6->mpTest = pTest7;
	pTest7->mpTest = pTest8;
	pTest8->mpTest = pTest9;
	pTest9->mpTest = pTest10;
	pTest10->mpTest = pTest11;
	pTest11->mpTest = pTest12;
	pTest12->mpTest = pTest14;
	
	pTest3->mpTest = pTest13;
	pTest3->mpObject = pTest14;

	pTest13->mpTest = pTest15;
	pTest14->mpTest = pTest15;
	pTest14->mpObject = pTest19;

	pTest15->mpTest = pTest16;
	pTest16->mpTest = pTest17;
	pTest17->mpTest = pTest18;

	pTest18->mpTest = pTest20;
	pTest18->mpObject = pTest21;

	pTest19->mpTest = pTest21;
	pTest19->mpObject = pTest22;

	pTest20->mpTest = pTest23;
	pTest20->mpObject = pTest18;
	pTest21->mpTest = pTest18;
	pTest21->mpObject = pTest19;
	pTest22->mpTest = pTest24;
	pTest22->mpObject = pTest19;

	AssertInt(3, pTest18->NumHeapFroms());
	AssertInt(3, pTest19->NumHeapFroms());

	pTest3 = NULL;
	pTest4  = NULL;
	pTest5  = NULL;
	pTest6  = NULL;
	pTest7  = NULL;
	pTest8  = NULL;
	pTest9  = NULL;
	pTest10 = NULL;
	pTest11 = NULL;
	pTest12 = NULL;
	pTest13 = NULL;
	pTest14 = NULL;
	pTest15 = NULL;
	pTest16 = NULL;
	pTest17 = NULL;
	pTest18 = NULL;
	pTest19 = NULL;
	pTest20 = NULL;
	pTest21 = NULL;
	pTest22 = NULL;
	pTest23 = NULL;
	pTest24 = NULL;

	AssertLongLongInt(24, gcObjects.NumMemoryIndexes());
	AssertInt( 2,  pcTest3->GetDistToRoot());
	AssertInt( 2,  pcTest4->GetDistToRoot());
	AssertInt( 3,  pcTest5->GetDistToRoot());
	AssertInt( 4,  pcTest6->GetDistToRoot());
	AssertInt( 5,  pcTest7->GetDistToRoot());
	AssertInt( 6,  pcTest8->GetDistToRoot());
	AssertInt( 7,  pcTest9->GetDistToRoot());
	AssertInt( 8, pcTest10->GetDistToRoot());
	AssertInt( 9, pcTest11->GetDistToRoot());
	AssertInt(10, pcTest12->GetDistToRoot());
	AssertInt( 3, pcTest13->GetDistToRoot());
	AssertInt( 3, pcTest14->GetDistToRoot());
	AssertInt( 4, pcTest15->GetDistToRoot());
	AssertInt( 5, pcTest16->GetDistToRoot());
	AssertInt( 6, pcTest17->GetDistToRoot());
	AssertInt( 6, pcTest18->GetDistToRoot());
	AssertInt( 4, pcTest19->GetDistToRoot());
	AssertInt( 7, pcTest20->GetDistToRoot());
	AssertInt( 5, pcTest21->GetDistToRoot());
	AssertInt( 5, pcTest22->GetDistToRoot());
	AssertInt( 8, pcTest23->GetDistToRoot());
	AssertInt( 6, pcTest24->GetDistToRoot());

	//                    
	//          pTest23(8)                 pTest24(6)
	//              ^                         ^
	//              |                         |
	//              |                         |
	//          pTest20(7)    pTest21(5)   pTest22(5)
	//               ^\       ^/   ^\       ^/
	//                \\     //     \\ 	  // 
	//                 \v   /v       \v   /v  
	//                pTest18(6)    pTest19(4)
	//                     ^             ^
	//                     |             |
	//                pTest17(6)         |
	//                     ^             |
	//                     |             |
	//                pTest16(5)         |
	//                     ^             |
	//                     |             |
	//                pTest15(4)         |
	//                   ^     ^         |
	//                   |      \       / 
	//                   |       \     /
	//                pTest13(3)  pTest14(3)
	//                   ^          ^   ^ 
	//                   |         /     \ 
	//                   |        /       \ 
	//                   |       /       pTest12(10)
	//                   |      |           ^
	//                   |      |           |
	//                   |      |        pTest11(9)
	// Break this one ---|----> X        pTest10(8) 
	//                    \     |        pTest9(7)
	//                     \    |        pTest8(6)
	//                      \   |        pTest7(5)
	//                       \  |        pTest6(4)
	//                        \ |        pTest5(3)
	//                      pTest3(2)    pTest4(2)
	//                           ^         ^
	//                            \       /  
	//                             \     /  
	//                              \   /  
	//                               ...
	//                              pRoot(0)
	//                    

	pcTest3->mpObject.UnsafeClearObject();
	pcTest14->TestRemoveHeapFrom(pcTest3);

	cDistParameters.Init();

	cDistToRootCalculator.Calculate(pcTest14, &cDistParameters);
	cDistParameters.ClearTouchedFlags();

	//                    
	//          pTest23(9)                 pTest24(11)
	//              ^                         ^
	//              |                         |
	//              |                         |
	//          pTest20(8)    pTest21(8)   pTest22(10)
	//               ^\       ^/   ^\       ^/
	//                \\     //     \\ 	  // 
	//                 \v   /v       \v   /v  
	//                pTest18(7)    pTest19(9) <-- pTest19 changing to (9) and 
	//                     ^             ^         not (12) is important.
	//                     |             |
	//                pTest17(6)         |
	//                     ^             |
	//                     |             |
	//                pTest16(5)         |
	//                     ^             |
	//                     |             |
	//                pTest15(4)         |
	//                   ^     ^         |
	//                   |      \       / 
	//                   |       \     /
	//                pTest13(3)  pTest14(11)
	//                   ^              ^ 
	//                   |               \ 
	//                   |                \ 
	//                   |               pTest12(10)
	//                   |                  ^
	//                   |                  |
	//                   |               pTest11(9)
	//                   |               pTest10(8) 
	//                    \              pTest9(7)
	//                     \             pTest8(6)
	//                      \            pTest7(5)
	//                       \           pTest6(4)
	//                        \          pTest5(3)
	//                      pTest3(2)    pTest4(2)
	//                           ^         ^
	//                            \       /  
	//                             \     /  
	//                              \   /  
	//                               ...
	//                              pRoot(0)
	//                    

	AssertLongLongInt(24, gcObjects.NumMemoryIndexes());
	AssertInt( 2,  pcTest3->GetDistToRoot());
	AssertInt( 2,  pcTest4->GetDistToRoot());
	AssertInt( 3,  pcTest5->GetDistToRoot());
	AssertInt( 4,  pcTest6->GetDistToRoot());
	AssertInt( 5,  pcTest7->GetDistToRoot());
	AssertInt( 6,  pcTest8->GetDistToRoot());
	AssertInt( 7,  pcTest9->GetDistToRoot());
	AssertInt( 8, pcTest10->GetDistToRoot());
	AssertInt( 9, pcTest11->GetDistToRoot());
	AssertInt(10, pcTest12->GetDistToRoot());
	AssertInt( 3, pcTest13->GetDistToRoot());
	AssertInt(11, pcTest14->GetDistToRoot());
	AssertInt( 4, pcTest15->GetDistToRoot());
	AssertInt( 5, pcTest16->GetDistToRoot());
	AssertInt( 6, pcTest17->GetDistToRoot());
	AssertInt( 7, pcTest18->GetDistToRoot());
	AssertInt( 9, pcTest19->GetDistToRoot());
	AssertInt( 8, pcTest20->GetDistToRoot());
	AssertInt( 8, pcTest21->GetDistToRoot());
	AssertInt(10, pcTest22->GetDistToRoot());
	AssertInt( 9, pcTest23->GetDistToRoot());
	AssertInt(11, pcTest24->GetDistToRoot());


	cDistParameters.Kill();

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

	TestDistToRootTosNotUpdated();
	TestClearDistToRootToValidDistBroken();
	TestClearDistToRootToValidDistComplex();
	TestClearDistToRootToValidDistSimpleLeft();
	TestClearDistToRootToValidDistSimpleRight();
	TestUpdateAttachedTosDistToRootBroken();
	TestUpdateAttachedTosDistToRootComplex();
	TestUpdateAttachedTosDistToRootSimpleRight();
	TestUpdateAttachedTosDistToRootSimpleRightBroken();
	TestUpdateAttachedTosDistToRootSimpleLeft();
	TestUpdateAttachedTosDistToRootChildTriangleKindaBalanced();
	TestUpdateAttachedTosDistToRootChildTriangleShortLeft();
	TestUpdateEmbeddedObjectTosDetachedSetupDistance();
	TestUpdateEmbeddedObjectTosDetachedScenarioA();
	TestUpdateEmbeddedObjectTosDetachedScenarioB();
	TestUpdateEmbeddedObjectTosDetachedScenarioC();
	TestUpdateEmbeddedObjectTosDetachedScenarioD();
	TestDistToRootLinear();
	TestDistToRootCyclic();
	TestDistToRootWithStackPointers();
	TestDistToRootLinearToStackScenarioA();
	TestDistToRootLinearToStackScenarioB();
	TestDistToRootComplex();

	TestStatistics();
}

