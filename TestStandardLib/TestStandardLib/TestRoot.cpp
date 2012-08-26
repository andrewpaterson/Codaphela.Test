#include "StandardLib/Objects.h"
#include "StandardLib/Root.h"
#include "TestLib/Assert.h"
#include "ObjectTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestRootDistance(void)
{
	STestObjectKilledNotifier	sKilled1;
	CPointer<CRoot>				pcRoot;
	CPointer<CTestObject>		pcTest1;
	int							iDist;
	CBaseObject*				pcFrom;

	ObjectsInit(NULL);
	pcRoot = ORoot();
	
	pcTest1 = OMalloc(CTestObject);
	pcTest1->Init(&sKilled1);

	pcRoot->Add(pcTest1);
	AssertInt(1, pcTest1->NumFroms());
	pcFrom = pcTest1->GetFrom(0);  //RootSet.
	pcFrom = pcFrom->GetFrom(0);  //Root

	AssertTrue(pcFrom->IsRoot());
	iDist = pcTest1->DistToRoot();
	AssertInt(2, iDist);
	pcFrom = pcTest1->GetFrom(0);  //RootSet.
	AssertInt(1, pcFrom->DistToRoot());
	pcFrom = pcFrom->GetFrom(0);  //Root
	AssertInt(0, pcFrom->DistToRoot());

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestStackPointers(void)
{
	STestObjectKilledNotifier	sKilled1;
	STestObjectKilledNotifier	sKilled2;
	STestObjectKilledNotifier	sKilled3;

	CPointer<CRoot>				pcRoot;
	CPointer<CTestObject>		pTest1;
	CPointer<CTestObject>		pTest2;
	CPointer<CTestObject>		pTest3;
	int							iFroms;

	CObject*					pcTest1;
	CObject*					pcTest2;
	CObject*					pcTest3;

	ObjectsInit(NULL);

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
	pTest3->mpTest = pTest2;

	AssertInt(0, pcRoot->NumFroms());
	AssertInt(1, pcRoot->NumTos());

	iFroms = pTest2->NumFroms();
	AssertInt(2, iFroms);
	pcTest1 = (CObject*)pTest2->GetFrom(0);
	AssertPointer(&pTest1, pcTest1);
	pcTest3 = (CObject*)pTest2->GetFrom(1);
	AssertPointer(&pTest3, pcTest3);
	AssertInt(0, pTest2->NumTos());
	AssertInt(3, pTest2->DistToRoot());

	iFroms = pTest1->NumFroms();
	AssertInt(1, iFroms);

	iFroms = pTest3->NumFroms();
	AssertInt(1, iFroms);

	pcTest3 = &pTest3;  //Cheating to hang onto the object.
	iFroms = pcTest3->NumFroms();
	AssertInt(1, iFroms);

	AssertFalse(sKilled1.bKilled);
	AssertFalse(sKilled3.bKilled);
	AssertFalse(sKilled2.bKilled);

	pcTest2 = &pTest2;
	pcRoot->Remove(pTest3);

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
	CPointer<CRoot>				pRoot;
	STestObjectKilledNotifier	sKilled2;
	STestObjectKilledNotifier	sKilled3;
	STestObjectKilledNotifier	sKilled4;
	STestObjectKilledNotifier	sKilled5;
	STestObjectKilledNotifier	sKilledTop1;
	STestObjectKilledNotifier	sKilledTop2;
	CPointer<CTestObject>		pTest2;
	CPointer<CTestObject>		pTest3;
	CPointer<CTestObject>		pTest4;
	CPointer<CTestObject>		pTest5;
	CPointer<CSet>				pSet;
	CPointer<CTestObject>		pTop1;
	CPointer<CTestObject>		pTop2;

	ObjectsInit(NULL);
	pRoot = ORoot();
	
	pTest2 = OMalloc(CTestObject);
	pTest3 = OMalloc(CTestObject);
	pTest4 = OMalloc(CTestObject);
	pTest5 = OMalloc(CTestObject);
	pSet = OMalloc(CSet);
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
	AssertInt(-1, pSet->DistToRoot());  //Not yet root aware.
	AssertInt(-1, pTop1->DistToRoot());
	AssertInt(1, pSet->NumTos());
	AssertInt(0, pTop1->NumTos());
	AssertInt(0, pSet->NumFroms());
	AssertInt(1, pTop1->NumFroms());

	// Top1
	//  |
	// Set


	pTest2->mpTest = pTest3;
	pTest4->mpTest = pTest5;
	AssertInt(-1, pTest2->DistToRoot());  //Not yet root aware.
	AssertInt(-1, pTest3->DistToRoot());
	AssertInt(1, pTest2->NumTos());
	AssertInt(0, pTest3->NumTos());
	AssertInt(0, pTest2->NumFroms());
	AssertInt(1, pTest3->NumFroms());

	// Top1    Test3    Test5
	//  |        |	      |
	// Set     Test2    Test4


	pRoot->Add(pTest2);
	AssertInt(2, pTest2->DistToRoot());
	AssertInt(3, pTest3->DistToRoot());
	AssertInt(1, pTest2->NumTos());
	AssertInt(0, pTest3->NumTos());
	AssertInt(1, pTest2->NumFroms());
	AssertInt(1, pTest3->NumFroms());

	//  Top1    Test3    Test5
	//   |        |	      |
	//  Set     Test2    Test4
	//            |
	//          Root


	pTest3->mpTest = pTest4;
	AssertInt(4, pTest4->DistToRoot());
	AssertInt(5, pTest5->DistToRoot());

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
	AssertInt(6, pSet->DistToRoot());
	AssertInt(7, pTop1->DistToRoot());
	pSet->Add(pTop2);
	AssertInt(7, pTop2->DistToRoot());
	AssertInt(1, pSet->NumFroms());
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
	AssertInt(2, pTest2->DistToRoot());
	AssertInt(3, pTest3->DistToRoot());
	AssertInt(3, pTest4->DistToRoot());
	AssertInt(4, pTest5->DistToRoot());
	AssertInt(5, pSet->DistToRoot());
	AssertInt(6, pTop1->DistToRoot());
	AssertInt(6, pTop2->DistToRoot());

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
	AssertInt(2, pTest2->DistToRoot());
	AssertInt(3, pTest3->DistToRoot());
	AssertInt(3, pTest4->DistToRoot());
	AssertInt(4, pTest5->DistToRoot());
	AssertInt(5, pSet->DistToRoot());
	AssertInt(6, pTop1->DistToRoot());
	AssertInt(4, pTop2->DistToRoot());

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

	pTest2->mpTest = NULL;
	AssertFalse(sKilled2.bKilled);
	AssertTrue( sKilled3.bKilled);
	AssertFalse(sKilled4.bKilled);
	AssertFalse(sKilled5.bKilled);
	AssertFalse(sKilledTop1.bKilled);
	AssertFalse(sKilledTop2.bKilled);
	AssertInt(2, pTest2->DistToRoot());
	AssertInt(3, pTest4->DistToRoot());
	AssertInt(4, pTest5->DistToRoot());
	AssertInt(5, pSet->DistToRoot());
	AssertInt(6, pTop1->DistToRoot());
	AssertInt(6, pTop2->DistToRoot());

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
	AssertInt(2, pTest2->DistToRoot());
	AssertInt(3, pTest4->DistToRoot());
	AssertInt(4, pTest5->DistToRoot());
	AssertInt(3, pSet->DistToRoot());
	AssertInt(4, pTop1->DistToRoot());
	AssertInt(4, pTop2->DistToRoot());

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


	pTest2->mpTest = NULL;
	AssertFalse(sKilled2.bKilled);
	AssertTrue( sKilled4.bKilled);
	AssertTrue( sKilled5.bKilled);
	AssertFalse(sKilledTop1.bKilled);
	AssertFalse(sKilledTop2.bKilled);
	AssertInt(2, pTest2->DistToRoot());
	AssertInt(3, pSet->DistToRoot());
	AssertInt(4, pTop1->DistToRoot());
	AssertInt(4, pTop2->DistToRoot());

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
	AssertInt(4, pTop1->DistToRoot());
	AssertInt(4, pTop2->DistToRoot());
	pTest2->mpObject = NULL;
	AssertFalse(sKilled2.bKilled);
	AssertTrue( sKilledTop1.bKilled);
	AssertTrue( sKilledTop2.bKilled);
	AssertInt(2, pTest2->DistToRoot());

	//   Test2(2)
	//      |
	//     ...
	//    Root(0)


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
	CPointer<CRoot>				pRoot;
	STestObjectKilledNotifier	sKilled2;
	STestObjectKilledNotifier	sKilled3;
	STestObjectKilledNotifier	sKilled4;
	STestObjectKilledNotifier	sKilled5;
	STestObjectKilledNotifier	sKilledTop1;
	STestObjectKilledNotifier	sKilledTop2;
	CPointer<CTestObject>		pTest2;
	CPointer<CTestObject>		pTest3;
	CPointer<CTestObject>		pTest4;
	CPointer<CTestObject>		pTest5;
	CPointer<CSet>				pSet;
	CPointer<CTestObject>		pTop1;
	CPointer<CTestObject>		pTop2;

	ObjectsInit(NULL);
	pRoot = ORoot();
	
	pTest2 = OMalloc(CTestObject);
	pTest3 = OMalloc(CTestObject);
	pTest4 = OMalloc(CTestObject);
	pTest5 = OMalloc(CTestObject);
	pSet = OMalloc(CSet);
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

	AssertInt(2, pTop1->NumFroms());
	AssertPointer(&pTop2, pTop1->GetFrom(0));
	AssertPointer(&pTest5, pTop1->GetFrom(1));
	AssertInt(2, pTop2->NumFroms());
	AssertPointer(&pTop1, pTop2->GetFrom(0));
	AssertPointer(&pTest3, pTop2->GetFrom(1));
	AssertInt(2, pSet->NumTos());
	AssertPointer(&pTest4, pSet->TestGetTo(0));
	AssertPointer(&pTest2, pSet->TestGetTo(1));
	AssertInt(1, pTest4->NumTos());
	AssertPointer(&pTest5, pTest4->TestGetTo(0));
	AssertInt(1, pTest4->NumFroms());
	AssertPointer(&pSet, pTest4->GetFrom(0));
	AssertInt(5, pTop1->DistToRoot());
	AssertInt(5, pTop2->DistToRoot());
	AssertInt(4, pTest5->DistToRoot());
	AssertInt(4, pTest3->DistToRoot());
	AssertInt(3, pTest4->DistToRoot());
	AssertInt(3, pTest2->DistToRoot());
	AssertInt(2, pSet->DistToRoot());

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


	pTest4->mpTest = NULL;
	AssertFalse(sKilled2.bKilled);
	AssertFalse(sKilled3.bKilled);
	AssertFalse(sKilled4.bKilled);
	AssertTrue( sKilled5.bKilled);
	AssertFalse(sKilledTop1.bKilled);
	AssertFalse(sKilledTop2.bKilled);
	AssertInt(1, pTop1->NumFroms());
	AssertPointer(&pTop2, pTop1->GetFrom(0));
	AssertInt(2, pTop2->NumFroms());
	AssertPointer(&pTop1, pTop2->GetFrom(0));
	AssertPointer(&pTest3, pTop2->GetFrom(1));
	AssertInt(2, pSet->NumTos());
	AssertPointer(&pTest4, pSet->TestGetTo(0));
	AssertPointer(&pTest2, pSet->TestGetTo(1));
	AssertInt(0, pTest4->NumTos());
	AssertPointer(NULL, pTest4->TestGetTo(0));
	AssertInt(1, pTest4->NumFroms());
	AssertPointer(&pSet, pTest4->GetFrom(0));

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
	AssertInt(2, pTop1->NumFroms());
	AssertPointer(&pTop2, pTop1->GetFrom(0));
	AssertPointer(&pTest5, pTop1->GetFrom(1));
	AssertInt(2, pTop2->NumFroms());
	AssertPointer(&pTop1, pTop2->GetFrom(0));
	AssertPointer(&pTest3, pTop2->GetFrom(1));
	AssertInt(2, pSet->NumTos());
	AssertPointer(&pTest4, pSet->TestGetTo(0));
	AssertPointer(&pTest2, pSet->TestGetTo(1));
	AssertInt(1, pTest4->NumTos());
	AssertPointer(&pTest5, pTest4->TestGetTo(0));
	AssertInt(1, pTest4->NumFroms());
	AssertPointer(&pSet, pTest4->GetFrom(0));
	AssertInt(5, pTop1->DistToRoot());
	AssertInt(5, pTop2->DistToRoot());
	AssertInt(4, pTest5->DistToRoot());
	AssertInt(4, pTest3->DistToRoot());
	AssertInt(3, pTest4->DistToRoot());
	AssertInt(3, pTest2->DistToRoot());
	AssertInt(2, pSet->DistToRoot());
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


	pRoot->Remove(pSet);
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
	CPointer<CRoot>				pRoot;
	STestObjectKilledNotifier	sKilled1;
	STestObjectKilledNotifier	sKilled2;
	STestObjectKilledNotifier	sKilled3;
	STestObjectKilledNotifier	sKilled4;
	STestObjectKilledNotifier	sKilled5;
	STestObjectKilledNotifier	sKilledTop1;
	STestObjectKilledNotifier	sKilledTop2;
	CPointer<CTestObject>		pTest1;
	CPointer<CTestObject>		pTest2;
	CPointer<CTestObject>		pTest3;
	CPointer<CTestObject>		pTest4;
	CPointer<CTestObject>		pTest5;
	CPointer<CSet>				pSet;
	CPointer<CTestObject>		pTop1;
	CPointer<CTestObject>		pTop2;

	ObjectsInit(NULL);
	pRoot = ORoot();
	
	pTest1 = OMalloc(CTestObject);
	pTest2 = OMalloc(CTestObject);
	pTest3 = OMalloc(CTestObject);
	pTest4 = OMalloc(CTestObject);
	pTest5 = OMalloc(CTestObject);
	pSet = OMalloc(CSet);
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

	AssertInt(2, pSet->DistToRoot());
	AssertInt(3, pTest2->DistToRoot());
	AssertInt(4, pTest3->DistToRoot());
	AssertInt(5, pTest4->DistToRoot());
	AssertInt(6, pTest5->DistToRoot());
	AssertInt(4, pTest1->DistToRoot());
	AssertInt(5, pTop1->DistToRoot());
	AssertInt(3, pTop2->DistToRoot());

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

	pSet->Remove(pTest2);
	AssertInt(2, pSet->DistToRoot());
	AssertInt(3, pTop2->DistToRoot());
	AssertInt(4, pTest1->DistToRoot());
	AssertInt(5, pTop1->DistToRoot());
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
	CPointer<CRoot>				pRoot;
	STestObjectKilledNotifier	sKilled1;
	STestObjectKilledNotifier	sKilled2;
	STestObjectKilledNotifier	sKilled3;
	STestObjectKilledNotifier	sKilled4;
	STestObjectKilledNotifier	sKilled5;
	STestObjectKilledNotifier	sKilledTop1;
	STestObjectKilledNotifier	sKilledTop2;
	CPointer<CTestObject>		pTest1;
	CPointer<CTestObject>		pTest2;
	CPointer<CTestObject>		pTest3;
	CPointer<CTestObject>		pTest4;
	CPointer<CTestObject>		pTest5;
	CPointer<CSet>				pSet;
	CPointer<CTestObject>		pTop1;
	CPointer<CTestObject>		pTop2;

	ObjectsInit(NULL);
	pRoot = ORoot();
	
	pTest1 = OMalloc(CTestObject);
	pTest2 = OMalloc(CTestObject);
	pTest3 = OMalloc(CTestObject);
	pTest4 = OMalloc(CTestObject);
	pTest5 = OMalloc(CTestObject);
	pSet = OMalloc(CSet);
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

	AssertInt(2, pSet->DistToRoot());
	AssertInt(3, pTest2->DistToRoot());
	AssertInt(4, pTest3->DistToRoot());
	AssertInt(5, pTest4->DistToRoot());
	AssertInt(6, pTest5->DistToRoot());
	AssertInt(4, pTest1->DistToRoot());
	AssertInt(5, pTop1->DistToRoot());
	AssertInt(3, pTop2->DistToRoot());

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
	AssertInt(2, pSet->DistToRoot());
	AssertInt(3, pTest2->DistToRoot());
	AssertInt(4, pTest3->DistToRoot());
	AssertInt(5, pTest4->DistToRoot());
	AssertInt(6, pTest5->DistToRoot());
	AssertInt(7, pTop1->DistToRoot());
	AssertInt(8, pTest1->DistToRoot());
	AssertInt(9, pTop2->DistToRoot());
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
	CPointer<CRoot>				pRoot;
	STestObjectKilledNotifier	sKilled1;
	STestObjectKilledNotifier	sKilled2;
	STestObjectKilledNotifier	sKilled3;
	STestObjectKilledNotifier	sKilled4;
	STestObjectKilledNotifier	sKilled5;
	STestObjectKilledNotifier	sKilled6;
	STestObjectKilledNotifier	sKilledTop1;
	STestObjectKilledNotifier	sKilledTop2;
	CPointer<CTestObject>		pTest1;
	CPointer<CTestObject>		pTest2;
	CPointer<CTestObject>		pTest3;
	CPointer<CTestObject>		pTest4;
	CPointer<CTestObject>		pTest5;
	CPointer<CTestObject>		pTest6;
	CPointer<CSet>				pSet;
	CPointer<CTestObject>		pTop1;
	CPointer<CTestObject>		pTop2;

	ObjectsInit(NULL);
	pRoot = ORoot();
	
	pTest1 = OMalloc(CTestObject);
	pTest2 = OMalloc(CTestObject);
	pTest3 = OMalloc(CTestObject);
	pTest4 = OMalloc(CTestObject);
	pTest5 = OMalloc(CTestObject);
	pTest6 = OMalloc(CTestObject);
	pSet = OMalloc(CSet);
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

	AssertInt(2, pSet->DistToRoot());
	AssertInt(3, pTest2->DistToRoot());
	AssertInt(3, pTest3->DistToRoot());
	AssertInt(4, pTest4->DistToRoot());
	AssertInt(5, pTest5->DistToRoot());
	AssertInt(6, pTop1->DistToRoot());
	AssertInt(5, pTest1->DistToRoot());
	AssertInt(4, pTop2->DistToRoot());
	AssertInt(2, pSet->NumElements());
	AssertInt(3, pTop2->NumFroms());

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
	AssertInt(2, pSet->DistToRoot());
	AssertInt(3, pTest3->DistToRoot());
	AssertInt(4, pTest4->DistToRoot());
	AssertInt(5, pTest5->DistToRoot());
	AssertInt(6, pTop1->DistToRoot());
	AssertInt(7, pTest1->DistToRoot());
	AssertInt(8, pTop2->DistToRoot());
	AssertInt(9, pTest6->DistToRoot());
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
void TestRoot(void)
{
	BeginTests();

	TestRootDistance();
	TestStackPointers();
	TestRootGraphRemoveSimple();
	TestRootGraphRemoveComplex();
	TestRootGraphRemoveUnbalancedLarge();
	TestRootGraphRemoveUnbalancedSmall();
	TestRootGraphRemoveMostlyBalanced();

	TestStatistics();
}

