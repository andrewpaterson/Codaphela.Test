#include "CoreLib/FunctionCaller.h"
#include "StandardLib/Parameters.h"
#include "StandardLib/Object.h"
#include "StandardLib/Objects.h"
#include "StandardLib/Pointer.h"
#include "StandardLib/Root.h"
#include "TestLib/Assert.h"
#include "ObjectTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectSize(void)
{
	ObjectsInit(NULL);

	AssertInt(12, sizeof(CUnknown));
	AssertInt(96, sizeof(CObject));
	AssertInt(136, sizeof(CRoot));
	AssertInt(112, sizeof(CSet));
	AssertInt(8, sizeof(CPointerObject));

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectPointerRemapping(void)
{
	CPointer<CRoot>					pRoot;
	CPointer<CTestObject>			pObject1;
	CPointer<CTestObject>			pObject2;
	CPointer<CTestObject>			pObject3;
	STestObjectKilledNotifier		sKillNotifier1;
	STestObjectKilledNotifier		sKillNotifier2;
	STestObjectKilledNotifier		sKillNotifier3;
	int								iNumRemapped;

	ObjectsInit(NULL);

	pRoot = ORoot();

	pObject1 = OMalloc(CTestObject);
	pObject2 = OMalloc(CTestObject);
	pObject3 = OMalloc(CTestObject);

	sKillNotifier1.bKilled = FALSE;
	sKillNotifier2.bKilled = FALSE;
	sKillNotifier3.bKilled = FALSE;

	pObject1->Init(&sKillNotifier1);
	pObject2->Init(&sKillNotifier2);
	pObject3->Init(&sKillNotifier3);

	pRoot->Add(pObject1);
	pObject1->mpObject = pObject2;

	AssertInt(1, pObject1->NumTos());
	AssertInt(1, pObject1->NumFroms());
	AssertInt(0, pObject2->NumTos());
	AssertInt(1, pObject2->NumFroms());
	AssertInt(0, pObject3->NumTos());
	AssertInt(0, pObject3->NumFroms());
	
	iNumRemapped = pObject3.RemapFrom(&pObject2);
	AssertInt(1, iNumRemapped);

	AssertPointer(&pObject3, &pObject1->mpObject);

	AssertInt(1, pObject1->NumTos());
	AssertInt(1, pObject1->NumFroms());
	AssertInt(0, pObject3->NumTos());
	AssertInt(1, pObject3->NumFroms());
	AssertTrue(sKillNotifier2.bKilled);

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectPointerRemappingKilling(void)
{
	CPointer<CRoot>					pRoot;
	CPointer<CTestObject>			pObject1;
	CPointer<CTestObject>			pObject2;
	CPointer<CTestObject>			pObject3;
	CPointer<CTestObject>			pObject4;
	CPointer<CTestObject>			pObject5;
	STestObjectKilledNotifier		sKillNotifier1;
	STestObjectKilledNotifier		sKillNotifier2;
	STestObjectKilledNotifier		sKillNotifier3;
	STestObjectKilledNotifier		sKillNotifier4;
	STestObjectKilledNotifier		sKillNotifier5;
	int								iNumRemapped;

	ObjectsInit(NULL);

	pRoot = ORoot();

	pObject1 = OMalloc(CTestObject);
	pObject2 = OMalloc(CTestObject);
	pObject3 = OMalloc(CTestObject);
	pObject4 = OMalloc(CTestObject);
	pObject5 = OMalloc(CTestObject);

	sKillNotifier1.bKilled = FALSE;
	sKillNotifier2.bKilled = FALSE;
	sKillNotifier3.bKilled = FALSE;
	sKillNotifier4.bKilled = FALSE;
	sKillNotifier5.bKilled = FALSE;

	pObject1->Init(&sKillNotifier1);
	pObject2->Init(&sKillNotifier2);
	pObject3->Init(&sKillNotifier3);
	pObject4->Init(&sKillNotifier4);
	pObject5->Init(&sKillNotifier5);

	pRoot->Add(pObject1);
	pObject1->mpObject = pObject2;
	pObject2->mpObject = pObject3;

	pObject4->mpObject = pObject5;

	iNumRemapped = pObject4.RemapFrom(&pObject2);
	AssertInt(1, iNumRemapped);

	AssertPointer(&pObject4, &pObject1->mpObject);
	AssertPointer(&pObject5, &pObject4->mpObject);

	AssertTrue(sKillNotifier2.bKilled);
	AssertTrue(sKillNotifier3.bKilled);

	ObjectsKill();
}



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectPointerRemappingComplex(void)
{
	CPointer<CRoot>					pRoot;
	CPointer<CTestObject>			pTest1;
	CPointer<CTestObject>			pTest2;
	CPointer<CTestObject>			pTest3;
	CPointer<CTestObject>			pTest4;
	CPointer<CTestObject>			pTest5;
	CPointer<CTestObject>			pTest6;
	CPointer<CTestObject>			pTest7;
	CPointer<CTestObject>			pTest8;
	CPointer<CTestObject>			pTest9;
	CPointer<CTestObject>			pTest10;
	CPointer<CTestObject>			pTest11;
	CPointer<CTestObject>			pTest12;
	CPointer<CTestObject>			pTest13;
	CPointer<CTestObject>			pTest14;
	CPointer<CTestObject>			pTest15;
	STestObjectKilledNotifier		sKillNotifier1;
	STestObjectKilledNotifier		sKillNotifier2;
	STestObjectKilledNotifier		sKillNotifier3;
	STestObjectKilledNotifier		sKillNotifier4;
	STestObjectKilledNotifier		sKillNotifier5;
	STestObjectKilledNotifier		sKillNotifier6;
	STestObjectKilledNotifier		sKillNotifier7;
	STestObjectKilledNotifier		sKillNotifier8;
	STestObjectKilledNotifier		sKillNotifier9;
	STestObjectKilledNotifier		sKillNotifier10;
	STestObjectKilledNotifier		sKillNotifier11;
	STestObjectKilledNotifier		sKillNotifier12;
	STestObjectKilledNotifier		sKillNotifier13;
	STestObjectKilledNotifier		sKillNotifier14;
	STestObjectKilledNotifier		sKillNotifier15;
	int								iNumRemapped;

	ObjectsInit(NULL);

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
	pTest10 = OMalloc(CTestObject);
	pTest11 = OMalloc(CTestObject);
	pTest12 = OMalloc(CTestObject);
	pTest13 = OMalloc(CTestObject);
	pTest14 = OMalloc(CTestObject);
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
	pTest10->Init(&sKillNotifier10);
	pTest11->Init(&sKillNotifier11);
	pTest12->Init(&sKillNotifier12);
	pTest13->Init(&sKillNotifier13);
	pTest14->Init(&sKillNotifier14);
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

	pTest10->mpObject = pTest11;
	pTest10->mpTest = pTest12;
	pTest11->mpObject = pTest13;
	pTest11->mpTest = pTest14;
	pTest12->mpObject = pTest13;
	pTest12->mpTest = pTest14;

	AssertInt(5, pTest6->DistToRoot());
	AssertInt(6, pTest8->DistToRoot());
	AssertInt(6, pTest9->DistToRoot());

	AssertLongLongInt(17, gcObjects.NumMemoryObjects());

	//   Test8  Test9
	//	   |    / |
	//	   |   /  |
	//	   |  /   |
	//   Test6  Test7
	//	   |  \   |	
	//	   |   \  |	
	//	   |    \ |	
	//   Test4  Test5
	//	   |      |	
	//	   |      |	
	//	 Test15   |	
	//	   |      |	
	//	   |      |	
	//   Test2  Test3
	//      \   /
	//      Test1(2)
	//        |
	//        |
	//       ...
	//     Root(0)
	//
	//
	//   Test13  Test14
	//	   |  \  /  |	
	//	   |   \/   |	
	//	   |   /\   |	
	//	   |  /  \  |	
	//   Test11  Test12
	//       \   /
	//      Test10
	//        |
	//       ---
	//        -
	
	iNumRemapped = pTest10.RemapFrom(&pTest3);
	AssertInt(1, iNumRemapped);

	AssertPointer(&pTest2, &pTest1->mpObject);
	AssertPointer(&pTest10, &pTest1->mpTest);

	AssertInt(1, pTest10->NumFroms());
	AssertPointer(&pTest1, pTest10->TestGetFrom(0));
	AssertInt(2, pTest10->NumTos());
	AssertPointer(&pTest11, pTest10->TestGetTo(0));
	AssertPointer(&pTest12, pTest10->TestGetTo(1));
	AssertPointer(&pTest11, &pTest10->mpObject);
	AssertPointer(&pTest12, &pTest10->mpTest);

	AssertInt(1, pTest2->NumFroms());
	AssertPointer(&pTest1, pTest2->TestGetFrom(0));
	AssertInt(1, pTest2->NumTos());
	AssertPointer(&pTest15, pTest2->TestGetTo(0));
	AssertPointer(&pTest15, &pTest2->mpObject);

	AssertTrue(sKillNotifier3.bKilled);
	AssertTrue(sKillNotifier5.bKilled);
	AssertTrue(sKillNotifier7.bKilled);
	AssertFalse(sKillNotifier9.bKilled);

	AssertFalse(sKillNotifier1.bKilled);
	AssertFalse(sKillNotifier2.bKilled);
	AssertFalse(sKillNotifier4.bKilled);
	AssertFalse(sKillNotifier6.bKilled);
	AssertFalse(sKillNotifier8.bKilled);
	AssertFalse(sKillNotifier10.bKilled);
	AssertFalse(sKillNotifier11.bKilled);
	AssertFalse(sKillNotifier12.bKilled);
	AssertFalse(sKillNotifier13.bKilled);
	AssertFalse(sKillNotifier14.bKilled);
	AssertFalse(sKillNotifier15.bKilled);

	AssertInt(1, pTest6->NumFroms());
	AssertPointer(&pTest4, pTest6->TestGetFrom(0));
	AssertInt(2, pTest6->NumTos());

	AssertInt(6, pTest6->DistToRoot());
	AssertInt(7, pTest8->DistToRoot());
	AssertInt(7, pTest9->DistToRoot());

	AssertInt(3, pTest10->DistToRoot());
	AssertInt(4, pTest11->DistToRoot());
	AssertInt(4, pTest12->DistToRoot());
	AssertInt(5, pTest13->DistToRoot());
	AssertInt(5, pTest14->DistToRoot());

	AssertLongLongInt(15, gcObjects.NumMemoryObjects());

	//   Test8   Test9
	//     |    /
	//     |   /       
	//	   |  /        
	//	 Test6           
	//	   |  	         
	//     |   Test13  Test14
	//	   |     |  \  /  |	
	//	   |     |   \/   |	
	//	 Test4   |   /\   |	
	//     |     |  /  \  |	
	//     |   Test11  Test12
	//  Test15    \      /
	//	   |  	   \    /
	//	   |  	    \  /
	//   Test2    Test10
	//      \     /
	//       \   /
	//       Test1(2) 
	//        |
	//        |
	//       ...
	//     Root(0)

	pRoot->Remove(pTest1);

	AssertTrue(sKillNotifier1.bKilled);
	AssertTrue(sKillNotifier2.bKilled);
	AssertTrue(sKillNotifier3.bKilled);
	AssertTrue(sKillNotifier4.bKilled);
	AssertTrue(sKillNotifier6.bKilled);
	AssertTrue(sKillNotifier8.bKilled);
	AssertTrue(sKillNotifier10.bKilled);
	AssertTrue(sKillNotifier11.bKilled);
	AssertTrue(sKillNotifier12.bKilled);
	AssertTrue(sKillNotifier13.bKilled);
	AssertTrue(sKillNotifier14.bKilled);
	AssertTrue(sKillNotifier15.bKilled);

	AssertLongLongInt(2, gcObjects.NumMemoryObjects());

	//       ---
	//        -
	//        |
	//       ...
	//     Root(0)


	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObject(void)
{
	BeginTests();

	TestObjectSize();
	TestObjectPointerRemapping();
	TestObjectPointerRemappingKilling();
	TestObjectPointerRemappingComplex();

	TestStatistics();
}

