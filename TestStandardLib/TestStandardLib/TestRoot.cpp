#include "StandardLib/Objects.h"
#include "StandardLib/String.h"
#include "StandardLib/Root.h"
#include "TestLib/Assert.h"
#include "ObjectTestClasses.h"
#include "ObjectWriterChunkedTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestRootDistance(void)
{
	STestObjectKilledNotifier	sKilled1;
	Ptr<CRoot>					pRoot;
	Ptr<CTestObject>			pTest1;
	int							iDist;
	CBaseObject*				pcFrom;

	ObjectsInit();
	pRoot = ORoot();
	AssertInt(ROOT_DIST_TO_ROOT, pRoot->GetDistToRoot());
	AssertInt(ROOT_DIST_TO_ROOT+1, pRoot->TestGetSet()->GetDistToRoot());
	
	pTest1 = OMalloc(CTestObject);
	pTest1->Init(&sKilled1);
	AssertInt(UNATTACHED_DIST_TO_ROOT, pTest1->GetDistToRoot());

	pRoot->Add(pTest1);
	AssertInt(1, pTest1->NumHeapFroms());
	pcFrom = pTest1->GetHeapFrom(0);  //RootSet.
	pcFrom = pcFrom->GetHeapFrom(0);  //Root

	AssertTrue(pcFrom->IsRoot());
	iDist = pTest1->GetDistToRoot();
	AssertInt(2, iDist);
	pcFrom = pTest1->GetHeapFrom(0);  //RootSet.
	AssertInt(1, pcFrom->GetDistToRoot());
	pcFrom = pcFrom->GetHeapFrom(0);  //Root
	AssertInt(0, pcFrom->GetDistToRoot());

	pRoot->Kill();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestRootStackPointers(void)
{
	STestObjectKilledNotifier	sKilled1;
	STestObjectKilledNotifier	sKilled2;
	STestObjectKilledNotifier	sKilled3;

	Ptr<CRoot>					pcRoot;
	Ptr<CTestObject>			pTest1;
	Ptr<CTestObject>			pTest2;
	Ptr<CTestObject>			pTest3;
	int							iFroms;

	CObject*					pcTest1;
	CObject*					pcTest2;
	CObject*					pcTest3;

	ObjectsInit();

	pTest1 = OMalloc(CTestObject);
	pTest1->Init(&sKilled1);

	pTest3 = OMalloc(CTestObject);
	pTest3->Init(&sKilled3);

	pcRoot = ORoot();
	
	pcRoot->Add(pTest1);
	pcRoot->Add(pTest3);

	pTest2 = OMalloc(CTestObject);
	pTest2->Init(&sKilled2);
	
	pTest1->mpTest = pTest2;
	AssertInt(3, pTest2->GetDistToRoot());

	pTest3->mpTest = pTest2;
	AssertInt(3, pTest2->GetDistToRoot());

	AssertInt(0, pcRoot->NumHeapFroms());
	AssertInt(1, pcRoot->NumTos());

	iFroms = pTest2->NumHeapFroms();
	AssertInt(2, iFroms);
	pcTest1 = (CObject*)pTest2->GetHeapFrom(0);
	AssertPointer(&pTest1, pcTest1);
	pcTest3 = (CObject*)pTest2->GetHeapFrom(1);
	AssertPointer(&pTest3, pcTest3);
	AssertInt(0, pTest2->NumTos());
	AssertInt(3, pTest2->GetDistToRoot());

	iFroms = pTest1->NumHeapFroms();
	AssertInt(1, iFroms);

	iFroms = pTest3->NumHeapFroms();
	AssertInt(1, iFroms);

	pcTest3 = &pTest3;  //Cheating to hang onto the object.
	iFroms = pcTest3->NumHeapFroms();
	AssertInt(1, iFroms);

	//Stop the stack from pointing.
	pTest1 = NULL;
	pTest2 = NULL;
	pTest3 = NULL;

	AssertFalse(sKilled1.bKilled);
	AssertFalse(sKilled3.bKilled);
	AssertFalse(sKilled2.bKilled);

	pcTest2 = &pTest2;
	pcRoot->Remove(pcTest3);

	AssertFalse(sKilled1.bKilled);
	AssertTrue( sKilled3.bKilled);
	AssertFalse(sKilled2.bKilled);

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestRootGraphRemoveSimple(void)
{
	Ptr<CRoot>					pRoot;
	STestObjectKilledNotifier	sKilled2;
	STestObjectKilledNotifier	sKilled3;
	STestObjectKilledNotifier	sKilled4;
	STestObjectKilledNotifier	sKilled5;
	STestObjectKilledNotifier	sKilledTop1;
	STestObjectKilledNotifier	sKilledTop2;
	Ptr<CTestObject>			pTest2;
	Ptr<CTestObject>			pTest3;
	Ptr<CTestObject>			pTest4;
	Ptr<CTestObject>			pTest5;
	Ptr<CSetObject>				pSet;
	Ptr<CTestObject>			pTop1;
	Ptr<CTestObject>			pTop2;

	ObjectsInit();
	pRoot = ORoot();
	
	pTest2 = OMalloc(CTestObject);
	pTest3 = OMalloc(CTestObject);
	pTest4 = OMalloc(CTestObject);
	pTest5 = OMalloc(CTestObject);
	pSet = OMalloc(CSetObject);
	pTop1 = OMalloc(CTestObject);
	pTop2 = OMalloc(CTestObject);

	pTest2->Init(&sKilled2);
	pTest3->Init(&sKilled3);
	pTest4->Init(&sKilled4);
	pTest5->Init(&sKilled5);
	pSet->Init();
	pTop1->Init(&sKilledTop1);
	pTop2->Init(&sKilledTop2);


	pSet->Add(pTop1);
	AssertInt(-1, pSet->GetDistToRoot());  //Not yet root aware.
	AssertInt(-1, pTop1->GetDistToRoot());
	AssertInt(1, pSet->NumTos());
	AssertInt(0, pTop1->NumTos());
	AssertInt(0, pSet->NumHeapFroms());
	AssertInt(1, pTop1->NumHeapFroms());

	// Top1
	//  |
	// Set


	pTest2->mpTest = pTest3;
	pTest4->mpTest = pTest5;
	AssertInt(-1, pTest2->GetDistToRoot());  //Not yet root aware.
	AssertInt(-1, pTest3->GetDistToRoot());
	AssertInt(1, pTest2->NumTos());
	AssertInt(0, pTest3->NumTos());
	AssertInt(0, pTest2->NumHeapFroms());
	AssertInt(1, pTest3->NumHeapFroms());

	// Top1    Test3    Test5
	//  |        |	      |
	// Set     Test2    Test4


	pRoot->Add(pTest2);
	AssertInt(2, pTest2->GetDistToRoot());
	AssertInt(3, pTest3->GetDistToRoot());
	AssertInt(1, pTest2->NumTos());
	AssertInt(0, pTest3->NumTos());
	AssertInt(1, pTest2->NumHeapFroms());
	AssertInt(1, pTest3->NumHeapFroms());

	//  Top1    Test3    Test5
	//   |        |	      |
	//  Set     Test2    Test4
	//            |
	//          Root


	pTest3->mpTest = pTest4;
	AssertInt(4, pTest4->GetDistToRoot());
	AssertInt(5, pTest5->GetDistToRoot());

	//          Test5   
	//            |   
	//          Test4   
	//            |   
	//  Top1    Test3
	//   |        |	
	//  Set     Test2
	//            |
	//          Root


	pTest5->mpObject = pSet;
	AssertInt(6, pSet->GetDistToRoot());
	AssertInt(7, pTop1->GetDistToRoot());
	pSet->Add(pTop2);
	AssertInt(7, pTop2->GetDistToRoot());
	AssertInt(1, pSet->NumHeapFroms());
	AssertInt(2, pSet->NumTos());

	//   Top1  Top2
	//     \   /
	//      Set 
	//       |
	//     Test5
	//       |  
	//     Test4
	//       |  
	//     Test3
	//       |	
	//     Test2
	//       |
	//     Root


	pTest2->mpObject = pTest4;
	AssertInt(2, pTest2->GetDistToRoot());
	AssertInt(3, pTest3->GetDistToRoot());
	AssertInt(3, pTest4->GetDistToRoot());
	AssertInt(4, pTest5->GetDistToRoot());
	AssertInt(5, pSet->GetDistToRoot());
	AssertInt(6, pTop1->GetDistToRoot());
	AssertInt(6, pTop2->GetDistToRoot());

	//   Top1  Top2
	//     \   /
	//      Set 
	//       |
	//     Test5
	//       |  
	//     Test4
	//     |   \  
	//     |  Test3
	//      \  /	
	//     Test2
	//       |
	//     Root


	pTest3->mpObject = pTop2;
	AssertInt(2, pTest2->GetDistToRoot());
	AssertInt(3, pTest3->GetDistToRoot());
	AssertInt(3, pTest4->GetDistToRoot());
	AssertInt(4, pTest5->GetDistToRoot());
	AssertInt(5, pSet->GetDistToRoot());
	AssertInt(6, pTop1->GetDistToRoot());
	AssertInt(4, pTop2->GetDistToRoot());

	//   Top1(6)  Top2(4)
	//     \     / \
	//      \   /   \
	//      Set(5)   |
	//       |       |
	//     Test5(4)  |
	//       |       |
	//     Test4(3)  |
	//     |    \    |
	//     |   Test3(3)
	//      \   /	
	//     Test2(2)
	//        |
	//       ...
	//      Root(0)


	AssertFalse(sKilled2.bKilled);
	AssertFalse(sKilled3.bKilled);
	AssertFalse(sKilled4.bKilled);
	AssertFalse(sKilled5.bKilled);
	AssertFalse(sKilledTop1.bKilled);
	AssertFalse(sKilledTop2.bKilled);

	AssertInt(2, pTest2->NumTos());
	AssertPointer(&pTest4, pTest2->TestGetTo(0));
	AssertPointer(&pTest3, pTest2->TestGetTo(1));
	AssertPointer(&pTest4, &pTest2->mpObject);
	AssertPointer(&pTest3, &pTest2->mpTest);
	AssertInt(1, pTest2->NumHeapFroms());
	AssertPointer(pRoot->TestGetSet(), pTest2->GetHeapFrom(0));

	pTest3 = NULL;
	pTest2->mpTest = NULL;
	AssertFalse(sKilled2.bKilled);
	AssertTrue( sKilled3.bKilled);
	AssertFalse(sKilled4.bKilled);
	AssertFalse(sKilled5.bKilled);
	AssertFalse(sKilledTop1.bKilled);
	AssertFalse(sKilledTop2.bKilled);
	AssertInt(2, pTest2->GetDistToRoot());
	AssertInt(3, pTest4->GetDistToRoot());
	AssertInt(4, pTest5->GetDistToRoot());
	AssertInt(5, pSet->GetDistToRoot());
	AssertInt(6, pTop1->GetDistToRoot());
	AssertInt(6, pTop2->GetDistToRoot());

	AssertInt(1, pTest2->NumTos());
	AssertPointer(&pTest4, pTest2->TestGetTo(0));
	AssertPointer(&pTest4, &pTest2->mpObject);
	AssertInt(1, pTest2->NumHeapFroms());
	AssertPointer(pRoot->TestGetSet(), pTest2->GetHeapFrom(0));

	//   Top1(6)  Top2(6)
	//     \     / 
	//      \   /  
	//      Set(5) 
	//       |     
	//     Test5(4)
	//       |     
	//     Test4(3)
	//       |
	//     Test2(2)
	//       |
	//      ...
	//     Root(0)


	pTest2->mpTest = pTest4;
	pTest2->mpObject = pSet;
	AssertInt(2, pTest2->GetDistToRoot());
	AssertInt(3, pTest4->GetDistToRoot());
	AssertInt(4, pTest5->GetDistToRoot());
	AssertInt(3, pSet->GetDistToRoot());
	AssertInt(4, pTop1->GetDistToRoot());
	AssertInt(4, pTop2->GetDistToRoot());

	//      Top1(4)  Top2(4)
	//        \     / 
	//         \   /  
	//         Set(3) 
	//        /    \
	//     Test5(4) |
	//       |      |
	//     Test4(3) |
	//       |      |
	//       |     /
	//        \   /
	//       Test2(2)
	//          |
	//         ...
	//        Root(0)

	pTest5 = NULL;
	pTest4 = NULL;
	pTest2->mpTest = NULL;
	AssertFalse(sKilled2.bKilled);
	AssertTrue( sKilled4.bKilled);
	AssertTrue( sKilled5.bKilled);
	AssertFalse(sKilledTop1.bKilled);
	AssertFalse(sKilledTop2.bKilled);
	AssertInt(2, pTest2->GetDistToRoot());
	AssertInt(3, pSet->GetDistToRoot());
	AssertInt(4, pTop1->GetDistToRoot());
	AssertInt(4, pTop2->GetDistToRoot());

	//  Top1(4)  Top2(4)
	//      \     / 
	//       \   /  
	//       Set(3) 
	//        |
	//     Test2(2)
	//        |
	//       ...
	//      Root(0)


	pTop1->mpTest = pTop2;
	pTop2->mpTest = pTop1;
	AssertInt(4, pTop1->GetDistToRoot());
	AssertInt(4, pTop2->GetDistToRoot());

	pTop1 = NULL;
	pTop2 = NULL;
	pSet = NULL;

	pTest2->mpObject = NULL;

	AssertFalse(sKilled2.bKilled);
	AssertTrue(sKilledTop1.bKilled);
	AssertTrue(sKilledTop2.bKilled);
	AssertInt(2, pTest2->GetDistToRoot());

	//   Test2(2)
	//      |
	//     ...
	//    Root(0)

	pTest2 = NULL;

	pRoot->RemoveAll();
	AssertTrue(sKilled2.bKilled);

	pRoot->Kill();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestRootGraphRemoveComplex(void)
{
	Ptr<CRoot>					pRoot;
	STestObjectKilledNotifier	sKilled2;
	STestObjectKilledNotifier	sKilled3;
	STestObjectKilledNotifier	sKilled4;
	STestObjectKilledNotifier	sKilled5;
	STestObjectKilledNotifier	sKilledTop1;
	STestObjectKilledNotifier	sKilledTop2;
	Ptr<CTestObject>			pTest2;
	Ptr<CTestObject>			pTest3;
	Ptr<CTestObject>			pTest4;
	Ptr<CTestObject>			pTest5;
	Ptr<CSetObject>				pSet;
	CSetObject*					pcSet;
	Ptr<CTestObject>			pTop1;
	Ptr<CTestObject>			pTop2;

	ObjectsInit();
	pRoot = ORoot();
	
	pTest2 = OMalloc(CTestObject);
	pTest3 = OMalloc(CTestObject);
	pTest4 = OMalloc(CTestObject);
	pTest5 = OMalloc(CTestObject);
	pSet = OMalloc(CSetObject);
	pTop1 = OMalloc(CTestObject);
	pTop2 = OMalloc(CTestObject);

	pTest2->Init(&sKilled2);
	pTest3->Init(&sKilled3);
	pTest4->Init(&sKilled4);
	pTest5->Init(&sKilled5);
	pSet->Init();
	pTop1->Init(&sKilledTop1);
	pTop2->Init(&sKilledTop2);

	pRoot->Add(pSet);
	pSet->Add(pTest4);
	pSet->Add(pTest2);
	pTest4->mpTest = pTest5;
	pTest2->mpTest = pTest3;
	pTop1->mpTest = pTop2;
	pTop2->mpTest = pTop1;
	pTest5->mpTest = pTop1;
	pTest3->mpTest = pTop2;

	AssertInt(2, pTop1->NumHeapFroms());
	AssertPointer(&pTop2, pTop1->GetHeapFrom(0));
	AssertPointer(&pTest5, pTop1->GetHeapFrom(1));
	AssertInt(2, pTop2->NumHeapFroms());
	AssertPointer(&pTop1, pTop2->GetHeapFrom(0));
	AssertPointer(&pTest3, pTop2->GetHeapFrom(1));
	AssertInt(2, pSet->NumTos());
	AssertPointer(&pTest4, pSet->TestGetTo(0));
	AssertPointer(&pTest2, pSet->TestGetTo(1));
	AssertInt(1, pTest4->NumTos());
	AssertPointer(&pTest5, pTest4->TestGetTo(0));
	AssertInt(1, pTest4->NumHeapFroms());
	AssertPointer(&pSet, pTest4->GetHeapFrom(0));
	AssertInt(5, pTop1->GetDistToRoot());
	AssertInt(5, pTop2->GetDistToRoot());
	AssertInt(4, pTest5->GetDistToRoot());
	AssertInt(4, pTest3->GetDistToRoot());
	AssertInt(3, pTest4->GetDistToRoot());
	AssertInt(3, pTest2->GetDistToRoot());
	AssertInt(2, pSet->GetDistToRoot());

	//   Top1(5)====Top2(5)
	//     |         |
	//   Test5(4)  Test3(4)
	//	   |         |	
	//	 Test4(3)  Test2(3)
	//      \       /
	//       \     /
	//        \   /
	//        Set(2)
	//          |
	//         ...
	//        Root(0)

	pTest5 = NULL;

	pTest4->mpTest = NULL;
	AssertFalse(sKilled2.bKilled);
	AssertFalse(sKilled3.bKilled);
	AssertFalse(sKilled4.bKilled);
	AssertTrue( sKilled5.bKilled);
	AssertFalse(sKilledTop1.bKilled);
	AssertFalse(sKilledTop2.bKilled);
	AssertInt(1, pTop1->NumHeapFroms());
	AssertPointer(&pTop2, pTop1->GetHeapFrom(0));
	AssertInt(2, pTop2->NumHeapFroms());
	AssertPointer(&pTop1, pTop2->GetHeapFrom(0));
	AssertPointer(&pTest3, pTop2->GetHeapFrom(1));
	AssertInt(2, pSet->NumTos());
	AssertPointer(&pTest4, pSet->TestGetTo(0));
	AssertPointer(&pTest2, pSet->TestGetTo(1));
	AssertInt(0, pTest4->NumTos());
	AssertPointer(NULL, pTest4->TestGetTo(0));
	AssertInt(1, pTest4->NumHeapFroms());
	AssertPointer(&pSet, pTest4->GetHeapFrom(0));

	//Tested for root should never be true (outside of the CanFindRoot method).
	AssertFalse(pSet->TestedForRoot());
	AssertFalse(pTest2->TestedForRoot());
	AssertFalse(pTest3->TestedForRoot());
	AssertFalse(pTest4->TestedForRoot());
	AssertFalse(pTop1->TestedForRoot());
	AssertFalse(pTop2->TestedForRoot());

	//   Top1====Top2
	//            |
	//          Test3
	//	          |	
	//	 Test4  Test2
	//      \    /
	//       \  /
	//       Set
	//        |
	//       ...
	//      Root(0)


	pTest5 = OMalloc(CTestObject);
	pTest5->Init(&sKilled5);
	pTest4->mpTest = pTest5;
	pTest5->mpTest = pTop1;
	AssertInt(2, pTop1->NumHeapFroms());
	AssertPointer(&pTop2, pTop1->GetHeapFrom(0));
	AssertPointer(&pTest5, pTop1->GetHeapFrom(1));
	AssertInt(2, pTop2->NumHeapFroms());
	AssertPointer(&pTop1, pTop2->GetHeapFrom(0));
	AssertPointer(&pTest3, pTop2->GetHeapFrom(1));
	AssertInt(2, pSet->NumTos());
	AssertPointer(&pTest4, pSet->TestGetTo(0));
	AssertPointer(&pTest2, pSet->TestGetTo(1));
	AssertInt(1, pTest4->NumTos());
	AssertPointer(&pTest5, pTest4->TestGetTo(0));
	AssertInt(1, pTest4->NumHeapFroms());
	AssertPointer(&pSet, pTest4->GetHeapFrom(0));
	AssertInt(5, pTop1->GetDistToRoot());
	AssertInt(5, pTop2->GetDistToRoot());
	AssertInt(4, pTest5->GetDistToRoot());
	AssertInt(4, pTest3->GetDistToRoot());
	AssertInt(3, pTest4->GetDistToRoot());
	AssertInt(3, pTest2->GetDistToRoot());
	AssertInt(2, pSet->GetDistToRoot());
	AssertFalse(pSet->TestedForRoot());
	AssertFalse(pTest2->TestedForRoot());
	AssertFalse(pTest3->TestedForRoot());
	AssertFalse(pTest4->TestedForRoot());
	AssertFalse(pTest5->TestedForRoot());
	AssertFalse(pTop1->TestedForRoot());
	AssertFalse(pTop2->TestedForRoot());

	//   Top1====Top2
	//     |      |
	//   Test5  Test3
	//	   |      |	
	//	 Test4  Test2
	//      \    /
	//       \  /
	//       Set
	//        |
	//       ...
	//      Root(0)

	pTest2 = NULL;
	pTest3 = NULL;
	pTest5 = NULL;
	pTest4 = NULL;
	pTop1 = NULL;
	pTop2 = NULL;
	pcSet = &pSet;
	pSet = NULL;

	pRoot->Remove(pcSet);
	AssertTrue(sKilled2.bKilled);
	AssertTrue(sKilled3.bKilled);
	AssertTrue(sKilled4.bKilled);
	AssertTrue(sKilled5.bKilled);
	AssertTrue(sKilledTop1.bKilled);
	AssertTrue(sKilledTop2.bKilled);

	pRoot->Kill();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestRootGraphRemoveUnbalancedLarge(void)
{
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

	//       Test1(4)  
	//       //\\      
	//      //  \\       
	//   Top1(5) Top2(3)
	//     |      |
	//   Test5(6) |
	//     |      |
	//   Test4(5) |
	//     |      |
	//   Test3(4) |
	//     |	  |
	//   Test2(3) |
	//      \    /
	//       \  /
	//       Set(2)
	//        |
	//       ...
	//      Root(0)

	pTest3 = NULL;
	pTest4 = NULL;
	pTest5 = NULL;

	pSet->Remove(pTest2);
	pTest2 = NULL;

	AssertInt(2, pSet->GetDistToRoot());
	AssertInt(3, pTop2->GetDistToRoot());
	AssertInt(4, pTest1->GetDistToRoot());
	AssertInt(5, pTop1->GetDistToRoot());
	AssertTrue(sKilled2.bKilled);
	AssertTrue(sKilled3.bKilled);
	AssertTrue(sKilled4.bKilled);
	AssertTrue(sKilled5.bKilled);
	AssertFalse(sKilledTop1.bKilled);
	AssertFalse(sKilledTop2.bKilled);
	AssertFalse(sKilled1.bKilled);
	AssertInt(1, pSet->NumElements());

	//   Top1(5)
	//     |
	//   Test1(4)  
	//     |
	//    Top2(3)
	//     |
	//    Set(2)
	//     |
	//    ...
	//   Root(0)

	pRoot->Kill();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestRootGraphRemoveUnbalancedSmall(void)
{
	Ptr<CRoot>				pRoot;
	STestObjectKilledNotifier	sKilled1;
	STestObjectKilledNotifier	sKilled2;
	STestObjectKilledNotifier	sKilled3;
	STestObjectKilledNotifier	sKilled4;
	STestObjectKilledNotifier	sKilled5;
	STestObjectKilledNotifier	sKilledTop1;
	STestObjectKilledNotifier	sKilledTop2;
	Ptr<CTestObject>		pTest1;
	Ptr<CTestObject>		pTest2;
	Ptr<CTestObject>		pTest3;
	Ptr<CTestObject>		pTest4;
	Ptr<CTestObject>		pTest5;
	Ptr<CSetObject>				pSet;
	Ptr<CTestObject>		pTop1;
	Ptr<CTestObject>		pTop2;

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

	//       Test1(4)  
	//       //\\      
	//      //  \\       
	//   Top1(5) Top2(3)
	//     |      |
	//   Test5(6) |
	//     |      |
	//   Test4(5) |
	//     |      |
	//   Test3(4) |
	//     |	  |
	//   Test2(3) |
	//      \    /
	//       \  /
	//       Set(2)
	//        |
	//       ...
	//      Root(0)


	pSet->Remove(pTop2);
	AssertInt(1, pSet->NumElements());
	AssertInt(2, pSet->GetDistToRoot());
	AssertInt(3, pTest2->GetDistToRoot());
	AssertInt(4, pTest3->GetDistToRoot());
	AssertInt(5, pTest4->GetDistToRoot());
	AssertInt(6, pTest5->GetDistToRoot());
	AssertInt(7, pTop1->GetDistToRoot());
	AssertInt(8, pTest1->GetDistToRoot());
	AssertInt(9, pTop2->GetDistToRoot());
	AssertFalse(sKilled2.bKilled);
	AssertFalse(sKilled3.bKilled);
	AssertFalse(sKilled4.bKilled);
	AssertFalse(sKilled5.bKilled);
	AssertFalse(sKilledTop1.bKilled);
	AssertFalse(sKilledTop2.bKilled);
	AssertFalse(sKilled1.bKilled);

	//   Top2(9)
	//     |
	//   Test1(8)  
	//     |  
	//   Top1(7)
	//     |    
	//   Test5(6)
	//     |    
	//   Test4(5)
	//     |    
	//   Test3(4)
	//     |	
	//   Test2(3)
	//     |
	//    Set(2)
	//     |
	//    ...
	//   Root(0)


	pRoot->Kill();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestRootGraphRemoveMostlyBalanced(void)
{
	Ptr<CRoot>					pRoot;
	STestObjectKilledNotifier	sKilled1;
	STestObjectKilledNotifier	sKilled2;
	STestObjectKilledNotifier	sKilled3;
	STestObjectKilledNotifier	sKilled4;
	STestObjectKilledNotifier	sKilled5;
	STestObjectKilledNotifier	sKilled6;
	STestObjectKilledNotifier	sKilledTop1;
	STestObjectKilledNotifier	sKilledTop2;
	Ptr<CTestObject>			pTest1;
	Ptr<CTestObject>			pTest2;
	Ptr<CTestObject>			pTest3;
	Ptr<CTestObject>			pTest4;
	Ptr<CTestObject>			pTest5;
	Ptr<CTestObject>			pTest6;
	Ptr<CSetObject>				pSet;
	Ptr<CTestObject>			pTop1;
	Ptr<CTestObject>			pTop2;

	ObjectsInit();
	pRoot = ORoot();
	
	pTest1 = OMalloc(CTestObject);
	pTest2 = OMalloc(CTestObject);
	pTest3 = OMalloc(CTestObject);
	pTest4 = OMalloc(CTestObject);
	pTest5 = OMalloc(CTestObject);
	pTest6 = OMalloc(CTestObject);
	pSet = OMalloc(CSetObject);
	pTop1 = OMalloc(CTestObject);
	pTop2 = OMalloc(CTestObject);

	pTest1->Init(&sKilled1);
	pTest2->Init(&sKilled2);
	pTest3->Init(&sKilled3);
	pTest4->Init(&sKilled4);
	pTest5->Init(&sKilled5);
	pTest6->Init(&sKilled6);
	pSet->Init();
	pTop1->Init(&sKilledTop1);
	pTop2->Init(&sKilledTop2);

	pRoot->Add(pSet);
	pSet->Add(pTest3);
	pSet->Add(pTest2);

	pTest2->mpTest = pTop2;
	pTest5->mpTest = pTop1;
	pTest4->mpTest = pTest5;
	pTest3->mpTest = pTest4;
	pTop1->mpTest = pTest1;
	pTop2->mpTest = pTest1;
	pTop2->mpObject = pTest6;
	pTest1->mpTest = pTop1;
	pTest1->mpObject = pTop2;
	pTest6->mpTest = pTop2;

	AssertInt(2, pSet->GetDistToRoot());
	AssertInt(3, pTest2->GetDistToRoot());
	AssertInt(3, pTest3->GetDistToRoot());
	AssertInt(4, pTest4->GetDistToRoot());
	AssertInt(5, pTest5->GetDistToRoot());
	AssertInt(6, pTop1->GetDistToRoot());
	AssertInt(5, pTest1->GetDistToRoot());
	AssertInt(4, pTop2->GetDistToRoot());
	AssertInt(2, pSet->NumElements());
	AssertInt(3, pTop2->NumHeapFroms());

	//      Test1(5)  Test6(5)
	//       //  \\    //  
	//      //    \\  //     
	//  Top1(6)   Top2(4)
	//     |        |
	//  Test5(5)    |
	//     |        |
	//  Test4(4)    |
	//     |        |
	//  Test3(3)  Test2(3)
	//      \      /
	//       \    /
	//       Set(2)
	//        |
	//       ...
	//      Root(0)


	pSet->Remove(pTest2);
	pTest2 = NULL;

	AssertInt(2, pSet->GetDistToRoot());
	AssertInt(3, pTest3->GetDistToRoot());
	AssertInt(4, pTest4->GetDistToRoot());
	AssertInt(5, pTest5->GetDistToRoot());
	AssertInt(6, pTop1->GetDistToRoot());
	AssertInt(7, pTest1->GetDistToRoot());
	AssertInt(8, pTop2->GetDistToRoot());
	AssertInt(9, pTest6->GetDistToRoot());
	AssertTrue( sKilled2.bKilled);
	AssertFalse(sKilled3.bKilled);
	AssertFalse(sKilled4.bKilled);
	AssertFalse(sKilled5.bKilled);
	AssertFalse(sKilled6.bKilled);
	AssertFalse(sKilledTop1.bKilled);
	AssertFalse(sKilledTop2.bKilled);
	AssertFalse(sKilled1.bKilled);
	AssertInt(1, pSet->NumElements());

	//   Test6(9)       
	//     ||     
	//   Top2(8)
	//     ||
	//   Test1(7)  
	//     || 
	//   Top1(6)
	//     |    
	//   Test5(5)
	//     |    
	//   Test4(4)
	//     |    
	//   Test3(3)
	//     |	
	//    Set(2)
	//     |
	//    ...
	//   Root(0)


	pRoot->Kill();
	ObjectsKill();
}



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestRootGraphRemoveErrorFromPointerRemapping(void)
{
	Ptr<CRoot>					pRoot;
	Ptr<CTestObject>			pTest1;
	Ptr<CTestObject>			pTest2;
	Ptr<CTestObject>			pTest3;
	Ptr<CTestObject>			pTest4;
	Ptr<CTestObject>			pTest5;
	Ptr<CTestObject>			pTest6;
	Ptr<CTestObject>			pTest7;
	Ptr<CTestObject>			pTest8;
	Ptr<CTestObject>			pTest9;
	Ptr<CTestObject>			pTest15;
	STestObjectKilledNotifier	sKillNotifier1;
	STestObjectKilledNotifier	sKillNotifier2;
	STestObjectKilledNotifier	sKillNotifier3;
	STestObjectKilledNotifier	sKillNotifier4;
	STestObjectKilledNotifier	sKillNotifier5;
	STestObjectKilledNotifier	sKillNotifier6;
	STestObjectKilledNotifier	sKillNotifier7;
	STestObjectKilledNotifier	sKillNotifier8;
	STestObjectKilledNotifier	sKillNotifier9;
	STestObjectKilledNotifier	sKillNotifier15;

	ObjectsInit();

	pRoot = ORoot();

	pTest1 = OMalloc(CTestObject);
	pTest2 = OMalloc(CTestObject);
	pTest3 = OMalloc(CTestObject);
	pTest4 = OMalloc(CTestObject);
	pTest5 = OMalloc(CTestObject);
	pTest6 = OMalloc(CTestObject);
	pTest7 = OMalloc(CTestObject);
	pTest8 = OMalloc(CTestObject);
	pTest9 = OMalloc(CTestObject);
	pTest15 = OMalloc(CTestObject);

	pTest1->Init(&sKillNotifier1);
	pTest2->Init(&sKillNotifier2);
	pTest3->Init(&sKillNotifier3);
	pTest4->Init(&sKillNotifier4);
	pTest5->Init(&sKillNotifier5);
	pTest6->Init(&sKillNotifier6);
	pTest7->Init(&sKillNotifier7);
	pTest8->Init(&sKillNotifier8);
	pTest9->Init(&sKillNotifier9);
	pTest15->Init(&sKillNotifier15);

	pRoot->Add(pTest1);
	pTest1->mpObject = pTest2;
	pTest1->mpTest = pTest3;
	pTest2->mpObject = pTest15;
	pTest15->mpTest = pTest4;
	pTest3->mpObject = pTest5;
	pTest4->mpTest = pTest6;
	pTest5->mpObject = pTest6;
	pTest5->mpTest = pTest7;
	pTest6->mpObject = pTest8;
	pTest6->mpTest = pTest9;
	pTest7->mpTest = pTest9;

	AssertInt(2, pTest1->GetDistToRoot());
	AssertInt(3, pTest2->GetDistToRoot());
	AssertInt(3, pTest3->GetDistToRoot());
	AssertInt(4, pTest15->GetDistToRoot());
	AssertInt(4, pTest5->GetDistToRoot());
	AssertInt(5, pTest4->GetDistToRoot());
	AssertInt(5, pTest6->GetDistToRoot());
	AssertInt(5, pTest7->GetDistToRoot());
	AssertInt(6, pTest8->GetDistToRoot());
	AssertInt(6, pTest9->GetDistToRoot());

	AssertLongLongInt(12, gcObjects.NumMemoryIndexes());

	//   Test8(6)  Test9(6)
	//	   |      /  |
	//	   |     /   |
	//	   |    /    |
	//	   |   /     |
	//   Test6(5)  Test7(5)
	//	   |   \     |	
	//	   |    \    |	
	//	   |     \   |	
	//	   |      \  |	
	//   Test4(5)  Test5(4)
	//	   |         |	
	//	   |         |	
	//	 Test15(4)   |	
	//	   |         |	
	//	   |         |	
	//   Test2(3)  Test3(3)
	//      \      /
	//       \    /
	//        \  /
	//       Test1(2)
	//         |
	//         |
	//        ...
	//      Root(0)

	pTest5 = NULL;
	pTest7 = NULL;
	pTest3 = NULL;
	pTest1->mpTest = NULL;

	AssertTrue(sKillNotifier3.bKilled);
	AssertTrue(sKillNotifier5.bKilled);
	AssertTrue(sKillNotifier7.bKilled);
	AssertFalse(sKillNotifier9.bKilled);

	AssertFalse(sKillNotifier1.bKilled);
	AssertFalse(sKillNotifier2.bKilled);
	AssertFalse(sKillNotifier4.bKilled);
	AssertFalse(sKillNotifier6.bKilled);
	AssertFalse(sKillNotifier8.bKilled);
	AssertFalse(sKillNotifier15.bKilled);

	AssertInt(1, pTest6->NumHeapFroms());
	AssertPointer(&pTest4, pTest6->GetHeapFrom(0));
	AssertInt(2, pTest6->NumTos());

	AssertInt(2, pTest1->GetDistToRoot());
	AssertInt(3, pTest2->GetDistToRoot());
	AssertInt(4, pTest15->GetDistToRoot());
	AssertInt(5, pTest4->GetDistToRoot());
	AssertInt(6, pTest6->GetDistToRoot());
	AssertInt(7, pTest8->GetDistToRoot());
	AssertInt(7, pTest9->GetDistToRoot());
	       
	//  Test8(7)  Test9(7)
	//	   \       /  
	//      \     /   
	//	     \   /    
	//      Test6(6)  
	//	       |  
	//	       |  
	//      Test4(5)  
	//	       |       
	//	       |       	
	//	    Test15(4)
	//	       |      
	//	       |      
	//      Test2(3) 
	//         |     
	//         |    
	//         |  
	//      Test1(2)
	//         |
	//         |
	//        ...
	//      Root(0)

	AssertLongLongInt(9, gcObjects.NumMemoryIndexes());

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestRootGraphRemoveErrorFromObjectConverter(void)
{
	Ptr<CTestNamedString>			cNS1;
	Ptr<CTestNamedString>			cNS2;
	Ptr<CTestNamedString>			cDiamond;
	Ptr<CTestDoubleNamedString>	cDouble;
	Ptr<CString>					sz1;
	Ptr<CString>					sz3;
	Ptr<CString>					sz2;
	Ptr<CString>					sz4;
	Ptr<CRoot>						cRoot;

	ObjectsInit();

	cRoot = ORoot();

	cDiamond = ONMalloc(CTestNamedString, "Diamond End");

	cNS1 = ONMalloc(CTestNamedString, "NamedString 1");
	sz1 = OMalloc(CString);

	cNS1->Init(sz1, cDiamond, "Hello");
	sz1->Init("World");

	cNS2 = ONMalloc(CTestNamedString, "NamedString 2");
	sz2 = OMalloc(CString);

	cNS2->Init(sz2, cDiamond, "Hello");
	sz2->Init("World");

	sz3 = OMalloc(CString);
	sz3->Init("End");
	cDiamond->Init(sz3, ONull, "1234");

	sz4 = OMalloc(CString);
	sz4->Init("Start");
	cDouble = ONMalloc(CTestDoubleNamedString, "Double Start");
	cDouble->Init(sz4, cNS1, ONull);

	cRoot->Add(cDouble);

	AssertInt(2, cDouble->GetDistToRoot());
	AssertInt(3, cNS1->GetDistToRoot());
	AssertInt(4, cDiamond->GetDistToRoot());
	AssertInt(-1, cNS2->GetDistToRoot());

	cDouble->mpSplit2 = cNS2;

	AssertInt(3, cNS2->GetDistToRoot());
	AssertInt(4, cDiamond->GetDistToRoot());

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestRoot(void)
{
	BeginTests();

	TestRootDistance();
	TestRootStackPointers();
	TestRootGraphRemoveSimple();
	TestRootGraphRemoveComplex();
	TestRootGraphRemoveUnbalancedLarge();
	TestRootGraphRemoveUnbalancedSmall();
	TestRootGraphRemoveMostlyBalanced();
	TestRootGraphRemoveErrorFromPointerRemapping();
	TestRootGraphRemoveErrorFromObjectConverter();

	TestStatistics();
}

