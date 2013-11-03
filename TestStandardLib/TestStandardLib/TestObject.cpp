#include "CoreLib/FunctionCaller.h"
#include "StandardLib/Parameters.h"
#include "StandardLib/Object.h"
#include "StandardLib/Objects.h"
#include "StandardLib/Pointer.h"
#include "StandardLib/Root.h"
#include "StandardLib/PointerContainer.h"
#include "TestLib/Assert.h"
#include "ObjectTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectSize(void)
{
	ObjectsInit();

	AssertInt(12, sizeof(CUnknown));
	AssertInt(56, sizeof(CEmbeddedObject));
	AssertInt(80, sizeof(CBaseObject));
	AssertInt(144, sizeof(CObject));
	AssertInt(184, sizeof(CRoot));
	AssertInt(128, sizeof(CSetObject));
	AssertInt(8, sizeof(CPointer));

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectPointerRemapping(void)
{
	Ptr<CRoot>					pRoot;
	Ptr<CTestObject>			pObject1;
	Ptr<CTestObject>			pObject2;
	Ptr<CTestObject>			pObject3;
	STestObjectKilledNotifier	sKillNotifier1;
	STestObjectKilledNotifier	sKillNotifier2;
	STestObjectKilledNotifier	sKillNotifier3;
	int							iNumRemapped;
	CTestObject*				pcObject2;
	CPointer					p4;
	CPointer					p5;

	ObjectsInit();

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
	AssertInt(1, pObject1->NumHeapFroms());
	AssertInt(0, pObject2->NumTos());
	AssertInt(1, pObject2->NumHeapFroms());
	AssertInt(0, pObject3->NumTos());
	AssertInt(0, pObject3->NumHeapFroms());
	AssertLongLongInt(5, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(5, gcUnknowns.NumElements());
	AssertLongLongInt(4LL, pObject2.GetIndex());
	AssertLongLongInt(5LL, pObject3.GetIndex());

	pcObject2 = (CTestObject*)pObject2.Object();
	iNumRemapped = pObject2.MorphInto(&pObject3);
	AssertInt(1, iNumRemapped);
	AssertTrue(sKillNotifier2.bKilled);
	AssertFalse(sKillNotifier3.bKilled);

	AssertPointer(&pObject3, &pObject1->mpObject);
	AssertPointer(&pObject3, &pObject2);
	AssertTrue(&pObject2 != pcObject2);
	AssertLongLongInt(4, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(4, gcUnknowns.NumElements());
	AssertLongLongInt(5LL, pObject3.GetIndex());  //Index of 5 because Pointer.MorphInto does not swap indicies.  ObjectAllocator.ReplaceExisting does and we're not testing it.

	AssertInt(1, pObject1->NumTos());
	AssertPointer(&pObject3, pObject1->TestGetTo(0));
	AssertInt(1, pObject1->NumHeapFroms());
	AssertPointer(pRoot->TestGetSet(), pObject1->GetHeapFrom(0));

	p4 = gcObjects.Get(4LL);
	p5 = gcObjects.Get(5LL);

	AssertNull(&p4);
	AssertPointer(&pObject3, &p5);

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectPointerRemappingKilling(void)
{
	Ptr<CRoot>					pRoot;
	Ptr<CTestObject>			pObject1;
	Ptr<CTestObject>			pObject2;
	Ptr<CTestObject>			pObject3;
	Ptr<CTestObject>			pObject4;
	Ptr<CTestObject>			pObject5;
	STestObjectKilledNotifier	sKillNotifier1;
	STestObjectKilledNotifier	sKillNotifier2;
	STestObjectKilledNotifier	sKillNotifier3;
	STestObjectKilledNotifier	sKillNotifier4;
	STestObjectKilledNotifier	sKillNotifier5;
	int							iNumRemapped;
	CTestObject*				pcObject1;
	CTestObject*				pcObject2;
	CTestObject*				pcObject3;
	CTestObject*				pcObject4;
	CTestObject*				pcObject5;

	ObjectsInit();

	pRoot = ORoot();

	pObject1 = OMalloc(CTestObject);
	pObject2 = OMalloc(CTestObject);
	pObject3 = OMalloc(CTestObject);
	pObject4 = OMalloc(CTestObject);
	pObject5 = OMalloc(CTestObject);

	pObject1->Init(&sKillNotifier1);
	pObject2->Init(&sKillNotifier2);
	pObject3->Init(&sKillNotifier3);
	pObject4->Init(&sKillNotifier4);
	pObject5->Init(&sKillNotifier5);

	pcObject1 = (CTestObject*)pObject1.Object();
	pcObject2 = (CTestObject*)pObject2.Object();
	pcObject3 = (CTestObject*)pObject3.Object();
	pcObject4 = (CTestObject*)pObject4.Object();
	pcObject5 = (CTestObject*)pObject5.Object();

	pRoot->Add(pObject1);
	pObject1->mpObject = pObject2;
	pObject2->mpObject = pObject3;
	
	pObject3 = NULL;
	AssertFalse(pcObject3->HasStackPointers());
	AssertTrue(pcObject3->HasHeapFroms());

	AssertInt(0, pObject4->NumTos());
	pObject4->mpObject = pObject5;
	AssertInt(1, pObject4->NumTos());

	iNumRemapped = pObject2.MorphInto(&pObject4);
	AssertInt(1, iNumRemapped);

	AssertPointer(pcObject4, &pObject4);
	AssertPointer(&pObject4, &pObject2);
	AssertPointer(&pObject4, &pObject1->mpObject);

	AssertInt(1, pObject4->NumTos());
	AssertPointer(&pObject5, &pObject4->mpObject);

	AssertFalse(sKillNotifier4.bKilled);
	AssertTrue(sKillNotifier2.bKilled);
	AssertTrue(sKillNotifier3.bKilled);

	gcObjects.ValidateConsistency();

	ObjectsKill();
}



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectPointerRemappingSimplerComplex(void)
{
	Ptr<CRoot>					pRoot;
	Ptr<CTestObject>			pTest10;
	Ptr<CTestObject>			pTest11;
	Ptr<CTestObject>			pTest12;
	Ptr<CTestObject>			pTest13;
	Ptr<CTestObject>			pTest14;
	STestObjectKilledNotifier	sKillNotifier10;
	STestObjectKilledNotifier	sKillNotifier11;
	STestObjectKilledNotifier	sKillNotifier12;
	STestObjectKilledNotifier	sKillNotifier13;
	STestObjectKilledNotifier	sKillNotifier14;
	CTestObject*				pcTest10;

	ObjectsInit();

	pRoot = ORoot();

	pTest10 = OMalloc(CTestObject);
	pTest11 = OMalloc(CTestObject);
	pTest12 = OMalloc(CTestObject);
	pTest13 = OMalloc(CTestObject);
	pTest14 = OMalloc(CTestObject);

	pTest10->Init(&sKillNotifier10);
	pTest11->Init(&sKillNotifier11);
	pTest12->Init(&sKillNotifier12);
	pTest13->Init(&sKillNotifier13);
	pTest14->Init(&sKillNotifier14);

	pRoot->Add(pTest10);
	pTest10->mpObject = pTest11;
	pTest10->mpTest = pTest12;
	pTest11->mpObject = pTest13;
	pTest11->mpTest = pTest14;
	pTest12->mpObject = pTest13;
	pTest12->mpTest = pTest14;

	AssertInt(4, pTest13->GetDistToRoot());
	AssertInt(4, pTest14->GetDistToRoot());
	AssertInt(3, pTest11->GetDistToRoot());
	AssertInt(3, pTest12->GetDistToRoot());
	AssertInt(2, pTest10->GetDistToRoot());

	AssertLongLongInt(7, gcObjects.NumMemoryIndexes());


	//   Test13  Test14
	//	   |  \  /  |	
	//	   |   \/   |	
	//	   |   /\   |	
	//	   |  /  \  |	
	//   Test11  Test12
	//       \   /
	//      Test10
	//        |
	//        |
	//       ...
	//     Root(0)

	pcTest10 = &pTest10;
	pTest10 = NULL;
	pTest11 = NULL;
	pTest12 = NULL;
	pTest13 = NULL;
	pTest14 = NULL;

	AssertFalse(sKillNotifier10.bKilled);
	AssertFalse(sKillNotifier11.bKilled);
	AssertFalse(sKillNotifier12.bKilled);
	AssertFalse(sKillNotifier13.bKilled);
	AssertFalse(sKillNotifier14.bKilled);

	pRoot->Remove(pcTest10);

	AssertTrue(sKillNotifier10.bKilled);
	AssertTrue(sKillNotifier11.bKilled);
	AssertTrue(sKillNotifier12.bKilled);
	AssertTrue(sKillNotifier13.bKilled);
	AssertTrue(sKillNotifier14.bKilled);

	AssertLongLongInt(2, gcObjects.NumMemoryIndexes());

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
void TestObjectPointerRemappingComplex(void)
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
	Ptr<CTestObject>			pTest10;
	Ptr<CTestObject>			pTest11;
	Ptr<CTestObject>			pTest12;
	Ptr<CTestObject>			pTest13;
	Ptr<CTestObject>			pTest14;
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
	STestObjectKilledNotifier	sKillNotifier10;
	STestObjectKilledNotifier	sKillNotifier11;
	STestObjectKilledNotifier	sKillNotifier12;
	STestObjectKilledNotifier	sKillNotifier13;
	STestObjectKilledNotifier	sKillNotifier14;
	STestObjectKilledNotifier	sKillNotifier15;
	int							iNumRemapped;
	CTestObject*				pcTest1;
	CTestObject*				pcTest3;

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

	AssertInt(5, pTest6->GetDistToRoot());
	AssertInt(6, pTest8->GetDistToRoot());
	AssertInt(6, pTest9->GetDistToRoot());

	AssertLongLongInt(17, gcObjects.NumMemoryIndexes());

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
	
	pTest5 = NULL;
	pTest7 = NULL;

	AssertLongLongInt(17, gcObjects.NumMemoryIndexes());

	pcTest3 = (CTestObject*)pTest3.Object();
	iNumRemapped = pTest3.MorphInto(&pTest10);
	AssertInt(1, iNumRemapped);

	AssertPointer(&pTest2, &pTest1->mpObject);
	AssertPointer(&pTest10, &pTest1->mpTest);

	AssertInt(1, pTest10->NumHeapFroms());
	AssertPointer(&pTest1, pTest10->GetHeapFrom(0));
	AssertInt(2, pTest10->NumTos());
	AssertPointer(&pTest11, pTest10->TestGetTo(0));
	AssertPointer(&pTest12, pTest10->TestGetTo(1));
	AssertPointer(&pTest11, &pTest10->mpObject);
	AssertPointer(&pTest12, &pTest10->mpTest);

	AssertInt(1, pTest2->NumHeapFroms());
	AssertPointer(&pTest1, pTest2->GetHeapFrom(0));
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

	AssertInt(1, pTest6->NumHeapFroms());
	AssertPointer(&pTest4, pTest6->GetHeapFrom(0));
	AssertInt(2, pTest6->NumTos());

	AssertInt(6, pTest6->GetDistToRoot());
	AssertInt(7, pTest8->GetDistToRoot());
	AssertInt(7, pTest9->GetDistToRoot());

	AssertInt(3, pTest10->GetDistToRoot());
	AssertInt(4, pTest11->GetDistToRoot());
	AssertInt(4, pTest12->GetDistToRoot());
	AssertInt(5, pTest13->GetDistToRoot());
	AssertInt(5, pTest14->GetDistToRoot());

	AssertLongLongInt(14, gcObjects.NumMemoryIndexes());

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

	pcTest1 = &pTest1;
	pTest1 = NULL;
	pTest2 = NULL;
	pTest3 = NULL;
	pTest4 = NULL;
	pTest5 = NULL;
	pTest6 = NULL;
	pTest7 = NULL;
	pTest8 = NULL;
	pTest9 = NULL;
	pTest10 = NULL;
	pTest11 = NULL;
	pTest12 = NULL;
	pTest13 = NULL;
	pTest14 = NULL;
	pTest15 = NULL;

	pRoot->Remove(pcTest1);

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

	AssertLongLongInt(2, gcObjects.NumMemoryIndexes());

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
void TestObjectGetObjects(void)
{
	ObjectsInit();

	CTestObject					cObject;
	CObjects*					pcObjects;
	Ptr<CTestObject>			pObject1;
	STestObjectKilledNotifier	sKillNotifier1;

	pcObjects = cObject.GetObjects();
	AssertNull(pcObjects);

	pObject1 = OMalloc(CTestObject);
	pObject1->Init(&sKillNotifier1);

	pcObjects = pObject1->GetObjects();
	AssertPointer(&gcObjects, pcObjects);

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectStackKill(void)
{
	ObjectsInit();

	CTestObject					cObject;
	Ptr<CTestObject>			pObject1;
	Ptr<CTestObject>			pObject2;
	STestObjectKilledNotifier	sKillNotifier1;

	pObject1 = OMalloc(CTestObject);
	pObject1->Init(&sKillNotifier1);

	pObject2 = pObject1;

	pObject1->Kill();

	AssertNull(&pObject1);
	AssertNull(&pObject2);

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectRootUnattachment(void)
{
	ObjectsInit();

	Ptr<CPointerContainer>		pContainer1;
	Ptr<CPointerContainer>		pContainer2;
	Ptr<CTestObject>			pObject;
	Ptr<CRoot>					pRoot;
	STestObjectKilledNotifier	sKillNotifier1;
	CTestObject*				pcObject;
	CPointerContainer*			pcContainer1;
	CPointerContainer*			pcContainer2;

	pObject = OMalloc(CTestObject)->Init(&sKillNotifier1);
	pContainer2 = OMalloc(CPointerContainer)->Init(pObject);
	pContainer1 = OMalloc(CPointerContainer)->Init(pContainer2);
	pRoot = ORoot();
	pRoot->Add(pContainer1);

	pcObject = &pObject;
	pcContainer1 = &pContainer1;
	pcContainer2 = &pContainer2;

	pContainer2 = NULL;
	pObject = NULL;
	AssertLongLongInt(5, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(5, gcUnknowns.NumElements());

	pRoot->Remove(pContainer1);
	AssertLongLongInt(5, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(5, gcUnknowns.NumElements());

	AssertInt(UNATTACHED_DIST_TO_ROOT, pcContainer1->GetDistToRoot());
	AssertFalse(pcContainer1->CanFindRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pcContainer2->GetDistToRoot());
	AssertFalse(pcContainer2->CanFindRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pcObject->GetDistToRoot());
	AssertFalse(pcObject->CanFindRoot());

	pContainer1 = NULL;
	AssertLongLongInt(2, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(2, gcUnknowns.NumElements());

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectKill(void)
{
	ObjectsInit();

	Ptr<CPointerContainer>		pContainer1;
	Ptr<CPointerContainer>		pContainer2;
	Ptr<CTestObject>			pObject;
	Ptr<CRoot>					pRoot;
	STestObjectKilledNotifier	sKillNotifier1;
	CTestObject*				pcObject;
	CPointerContainer*			pcContainer1;
	CPointerContainer*			pcContainer2;

	pObject = OMalloc(CTestObject)->Init(&sKillNotifier1);
	pContainer2 = OMalloc(CPointerContainer)->Init(pObject);
	pContainer1 = OMalloc(CPointerContainer)->Init(pContainer2);
	pRoot = ORoot();
	pRoot->Add(pContainer1);

	pcObject = &pObject;
	pcContainer1 = &pContainer1;
	pcContainer2 = &pContainer2;

	pContainer2 = NULL;
	pObject = NULL;
	AssertLongLongInt(5, gcObjects.NumMemoryIndexes());

	pRoot->TestGetSet()->Kill();
	AssertInt(UNATTACHED_DIST_TO_ROOT, pcContainer1->GetDistToRoot());
	AssertFalse(pcContainer1->CanFindRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pcContainer2->GetDistToRoot());
	AssertFalse(pcContainer2->CanFindRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pcObject->GetDistToRoot());
	AssertFalse(pcObject->CanFindRoot());

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectSetUnattachment(void)
{
	ObjectsInit();

	Ptr<CPointerContainer>		pContainer1;
	Ptr<CPointerContainer>		pContainer2;
	Ptr<CTestObject>			pObject;
	Ptr<CRoot>					pRoot;
	STestObjectKilledNotifier	sKillNotifier1;
	CTestObject*				pcObject;
	CPointerContainer*			pcContainer1;
	CPointerContainer*			pcContainer2;

	pObject = OMalloc(CTestObject)->Init(&sKillNotifier1);
	pContainer2 = OMalloc(CPointerContainer)->Init(pObject);
	pContainer1 = OMalloc(CPointerContainer)->Init(pContainer2);
	pRoot = ORoot();
	pRoot->Add(pContainer1);

	pcObject = &pObject;
	pcContainer1 = &pContainer1;
	pcContainer2 = &pContainer2;

	pContainer2 = NULL;
	pObject = NULL;
	AssertLongLongInt(5, gcObjects.NumMemoryIndexes());

	pRoot->NullifySet();
	AssertLongLongInt(4, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(4, gcUnknowns.NumElements());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pcContainer1->GetDistToRoot());
	AssertFalse(pcContainer1->CanFindRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pcContainer2->GetDistToRoot());
	AssertFalse(pcContainer2->CanFindRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pcObject->GetDistToRoot());
	AssertFalse(pcObject->CanFindRoot());

	pContainer1 = NULL;
	AssertLongLongInt(1, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(1, gcUnknowns.NumElements());

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectKillCyclic(void)
{
	ObjectsInit();

	Ptr<CTestObject>			pTest1;
	Ptr<CTestObject>			pTest2;
	Ptr<CTestObject>			pTest3;
	Ptr<CTestObject>			pTest4;
	Ptr<CRoot>					pRoot;

	pTest1 = OMalloc(CTestObject)->Init(NULL);
	pTest2 = OMalloc(CTestObject)->Init(NULL);
	pTest1->mpTest = pTest2;
	pTest2->mpTest = pTest1;
	pTest3 = OMalloc(CTestObject)->Init(NULL);
	pTest3->mpTest = pTest2;
	pTest4 = OMalloc(CTestObject)->Init(NULL);
	pTest4->mpTest = pTest3;
	pRoot = ORoot();
	pRoot->Add(pTest4);

	AssertLongLongInt(6, gcObjects.NumMemoryIndexes());
	AssertInt(5, pTest1->GetDistToRoot());
	AssertInt(4, pTest2->GetDistToRoot());
	AssertInt(3, pTest3->GetDistToRoot());
	AssertInt(2, pTest4->GetDistToRoot());

	pTest4->Kill();
	AssertLongLongInt(5, gcObjects.NumMemoryIndexes());
	AssertNull(&pTest4);
	AssertInt(UNATTACHED_DIST_TO_ROOT, pTest1->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pTest2->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pTest3->GetDistToRoot());

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
	TestObjectGetObjects();
	TestObjectStackKill();
	TestObjectPointerRemapping();
	TestObjectPointerRemappingKilling();
	TestObjectPointerRemappingSimplerComplex();
	TestObjectPointerRemappingComplex();
	TestObjectKill();
	TestObjectKillCyclic();
	TestObjectRootUnattachment();
	TestObjectSetUnattachment();

	TestStatistics();
}

