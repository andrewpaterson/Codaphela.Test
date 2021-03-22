#include "BaseLib/GlobalMemory.h"
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

	AssertInt(16, sizeof(CUnknown));
	AssertInt(60, sizeof(CEmbeddedObject));
	AssertInt(96, sizeof(CBaseObject));
	AssertInt(168, sizeof(CObject));
	AssertInt(208, sizeof(CRoot));
	AssertInt(152, sizeof(CSetObject));
	AssertInt(8, sizeof(CPointer));

	ObjectsFlush();
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
	STestObjectFreedNotifier	sFreedNotifier1;
	STestObjectFreedNotifier	sFreedNotifier2;
	STestObjectFreedNotifier	sFreedNotifier3;
	int							iNumRemapped;
	CTestObject*				pcObject2;
	CPointer					p4;
	CPointer					p5;

	ObjectsInit();

	pRoot = ORoot();

	pObject1 = OMalloc<CTestObject>(&sFreedNotifier1);
	pObject2 = OMalloc<CTestObject>(&sFreedNotifier2);
	pObject3 = OMalloc<CTestObject>(&sFreedNotifier3);

	pRoot->Add(pObject1);
	pObject1->mpObject = pObject2;

	AssertInt(1, pObject1->NumPointerTos());
	AssertInt(1, pObject1->NumHeapFroms());
	AssertInt(0, pObject2->NumPointerTos());
	AssertInt(1, pObject2->NumHeapFroms());
	AssertInt(0, pObject3->NumPointerTos());
	AssertInt(0, pObject3->NumHeapFroms());
	AssertLongLongInt(5, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(5, gcUnknowns.NumElements());
	AssertLongLongInt(4LL, pObject2.GetIndex());
	AssertLongLongInt(5LL, pObject3.GetIndex());
	AssertInt(1, pObject2->GetNumEmbedded());
	AssertInt(1, pObject3->GetNumEmbedded());

	pcObject2 = (CTestObject*)pObject2.Object();
	iNumRemapped = pObject2.MorphInto(&pObject3);
	AssertInt(1, iNumRemapped);
	AssertTrue(sFreedNotifier2.bFreed);
	AssertFalse(sFreedNotifier3.bFreed);

	AssertPointer(&pObject3, &pObject1->mpObject);
	AssertPointer(&pObject3, &pObject2);
	AssertTrue(&pObject2 != pcObject2);
	AssertLongLongInt(4, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(4, gcUnknowns.NumElements());
	AssertLongLongInt(5LL, pObject3.GetIndex());  //Index of 5 because Pointer.MorphInto does not swap indices.  ObjectAllocator.ReplaceExisting does and we're not testing it.

	AssertInt(1, pObject1->NumPointerTos());
	AssertPointer(&pObject3, pObject1->TestGetPointerTo(0));
	AssertInt(1, pObject1->NumHeapFroms());
	AssertPointer(pRoot->TestGetSet(), pObject1->GetHeapFrom(0));

	p4 = gcObjects.Get(4LL);
	p5 = gcObjects.Get(5LL);

	AssertNull(&p4);
	AssertPointer(&pObject3, &p5);

	ObjectsFlush();
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
	STestObjectFreedNotifier	sFreedNotifier1;
	STestObjectFreedNotifier	sFreedNotifier2;
	STestObjectFreedNotifier	sFreedNotifier3;
	STestObjectFreedNotifier	sFreedNotifier4;
	STestObjectFreedNotifier	sFreedNotifier5;
	int							iNumRemapped;
	CTestObject*				pcObject1;
	CTestObject*				pcObject2;
	CTestObject*				pcObject3;
	CTestObject*				pcObject4;
	CTestObject*				pcObject5;

	ObjectsInit();

	pRoot = ORoot();

	pObject1 = OMalloc<CTestObject>(&sFreedNotifier1);
	pObject2 = OMalloc<CTestObject>(&sFreedNotifier2);
	pObject3 = OMalloc<CTestObject>(&sFreedNotifier3);
	pObject4 = OMalloc<CTestObject>(&sFreedNotifier4);
	pObject5 = OMalloc<CTestObject>(&sFreedNotifier5);

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

	AssertInt(0, pObject4->NumPointerTos());
	pObject4->mpObject = pObject5;
	AssertInt(1, pObject4->NumPointerTos());

	iNumRemapped = pObject2.MorphInto(&pObject4);
	AssertInt(1, iNumRemapped);

	AssertPointer(pcObject4, &pObject4);
	AssertPointer(&pObject4, &pObject2);
	AssertPointer(&pObject4, &pObject1->mpObject);

	AssertInt(1, pObject4->NumPointerTos());
	AssertPointer(&pObject5, &pObject4->mpObject);

	AssertFalse(sFreedNotifier4.bFreed);
	AssertTrue(sFreedNotifier2.bFreed);
	AssertTrue(sFreedNotifier3.bFreed);

	gcObjects.ValidateObjectsConsistency();

	ObjectsFlush();
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
	STestObjectFreedNotifier	sFreedNotifier10;
	STestObjectFreedNotifier	sFreedNotifier11;
	STestObjectFreedNotifier	sFreedNotifier12;
	STestObjectFreedNotifier	sFreedNotifier13;
	STestObjectFreedNotifier	sFreedNotifier14;
	CTestObject*				pcTest10;

	ObjectsInit();

	pRoot = ORoot();

	pTest10 = OMalloc<CTestObject>(&sFreedNotifier10);
	pTest11 = OMalloc<CTestObject>(&sFreedNotifier11);
	pTest12 = OMalloc<CTestObject>(&sFreedNotifier12);
	pTest13 = OMalloc<CTestObject>(&sFreedNotifier13);
	pTest14 = OMalloc<CTestObject>(&sFreedNotifier14);

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

	AssertFalse(sFreedNotifier10.bFreed);
	AssertFalse(sFreedNotifier11.bFreed);
	AssertFalse(sFreedNotifier12.bFreed);
	AssertFalse(sFreedNotifier13.bFreed);
	AssertFalse(sFreedNotifier14.bFreed);

	pRoot->Remove(pcTest10);

	AssertTrue(sFreedNotifier10.bFreed);
	AssertTrue(sFreedNotifier11.bFreed);
	AssertTrue(sFreedNotifier12.bFreed);
	AssertTrue(sFreedNotifier13.bFreed);
	AssertTrue(sFreedNotifier14.bFreed);

	AssertLongLongInt(2, gcObjects.NumMemoryIndexes());

	//       ---
	//        -
	//        |
	//       ...
	//     Root(0)


	ObjectsFlush();
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
	STestObjectFreedNotifier	sFreedNotifier1;
	STestObjectFreedNotifier	sFreedNotifier2;
	STestObjectFreedNotifier	sFreedNotifier3;
	STestObjectFreedNotifier	sFreedNotifier4;
	STestObjectFreedNotifier	sFreedNotifier5;
	STestObjectFreedNotifier	sFreedNotifier6;
	STestObjectFreedNotifier	sFreedNotifier7;
	STestObjectFreedNotifier	sFreedNotifier8;
	STestObjectFreedNotifier	sFreedNotifier9;
	STestObjectFreedNotifier	sFreedNotifier10;
	STestObjectFreedNotifier	sFreedNotifier11;
	STestObjectFreedNotifier	sFreedNotifier12;
	STestObjectFreedNotifier	sFreedNotifier13;
	STestObjectFreedNotifier	sFreedNotifier14;
	STestObjectFreedNotifier	sFreedNotifier15;
	int							iNumRemapped;
	CTestObject*				pcTest1;
	CTestObject*				pcTest3;

	ObjectsInit();

	pRoot = ORoot();

	pTest1 = OMalloc<CTestObject>(&sFreedNotifier1);
	pTest2 = OMalloc<CTestObject>(&sFreedNotifier2);
	pTest3 = OMalloc<CTestObject>(&sFreedNotifier3);
	pTest4 = OMalloc<CTestObject>(&sFreedNotifier4);
	pTest5 = OMalloc<CTestObject>(&sFreedNotifier5);
	pTest6 = OMalloc<CTestObject>(&sFreedNotifier6);
	pTest7 = OMalloc<CTestObject>(&sFreedNotifier7);
	pTest8 = OMalloc<CTestObject>(&sFreedNotifier8);
	pTest9 = OMalloc<CTestObject>(&sFreedNotifier9);
	pTest10 = OMalloc<CTestObject>(&sFreedNotifier10);
	pTest11 = OMalloc<CTestObject>(&sFreedNotifier11);
	pTest12 = OMalloc<CTestObject>(&sFreedNotifier12);
	pTest13 = OMalloc<CTestObject>(&sFreedNotifier13);
	pTest14 = OMalloc<CTestObject>(&sFreedNotifier14);
	pTest15 = OMalloc<CTestObject>(&sFreedNotifier15);

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
	AssertInt(2, pTest10->NumPointerTos());
	AssertPointer(&pTest11, pTest10->TestGetPointerTo(0));
	AssertPointer(&pTest12, pTest10->TestGetPointerTo(1));
	AssertPointer(&pTest11, &pTest10->mpObject);
	AssertPointer(&pTest12, &pTest10->mpTest);

	AssertInt(1, pTest2->NumHeapFroms());
	AssertPointer(&pTest1, pTest2->GetHeapFrom(0));
	AssertInt(1, pTest2->NumPointerTos());
	AssertPointer(&pTest15, pTest2->TestGetPointerTo(0));
	AssertPointer(&pTest15, &pTest2->mpObject);

	AssertTrue(sFreedNotifier3.bFreed);
	AssertTrue(sFreedNotifier5.bFreed);
	AssertTrue(sFreedNotifier7.bFreed);
	AssertFalse(sFreedNotifier9.bFreed);

	AssertFalse(sFreedNotifier1.bFreed);
	AssertFalse(sFreedNotifier2.bFreed);
	AssertFalse(sFreedNotifier4.bFreed);
	AssertFalse(sFreedNotifier6.bFreed);
	AssertFalse(sFreedNotifier8.bFreed);
	AssertFalse(sFreedNotifier10.bFreed);
	AssertFalse(sFreedNotifier11.bFreed);
	AssertFalse(sFreedNotifier12.bFreed);
	AssertFalse(sFreedNotifier13.bFreed);
	AssertFalse(sFreedNotifier14.bFreed);
	AssertFalse(sFreedNotifier15.bFreed);

	AssertInt(1, pTest6->NumHeapFroms());
	AssertPointer(&pTest4, pTest6->GetHeapFrom(0));
	AssertInt(2, pTest6->NumPointerTos());

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

	AssertTrue(sFreedNotifier1.bFreed);
	AssertTrue(sFreedNotifier2.bFreed);
	AssertTrue(sFreedNotifier3.bFreed);
	AssertTrue(sFreedNotifier4.bFreed);
	AssertTrue(sFreedNotifier6.bFreed);
	AssertTrue(sFreedNotifier8.bFreed);
	AssertTrue(sFreedNotifier10.bFreed);
	AssertTrue(sFreedNotifier11.bFreed);
	AssertTrue(sFreedNotifier12.bFreed);
	AssertTrue(sFreedNotifier13.bFreed);
	AssertTrue(sFreedNotifier14.bFreed);
	AssertTrue(sFreedNotifier15.bFreed);

	AssertLongLongInt(2, gcObjects.NumMemoryIndexes());

	//       ---
	//        -
	//        |
	//       ...
	//     Root(0)


	ObjectsFlush();
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
	STestObjectFreedNotifier	sFreedNotifier1;

	pcObjects = cObject.GetObjects();
	AssertNull(pcObjects);

	cObject.Init();

	pObject1 = OMalloc<CTestObject>(&sFreedNotifier1);

	pcObjects = pObject1->GetObjects();
	AssertPointer(&gcObjects, pcObjects);
	AssertFalse(sFreedNotifier1.bFreed);
	AssertFalse(gcObjects.HasRoot());

	ObjectsFlush();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectStackKill(void)
{
	ObjectsInit();

	Ptr<CTestObject>			pObject1;
	Ptr<CTestObject>			pObject2;
	STestObjectFreedNotifier	sFreedNotifier;

	pObject1 = OMalloc<CTestObject>(&sFreedNotifier);
	AssertFalse(sFreedNotifier.bFreed);

	pObject2 = pObject1;

	pObject1->Kill();

	AssertNull(&pObject1);
	AssertNull(&pObject2);
	AssertTrue(sFreedNotifier.bFreed);

	ObjectsFlush();
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
	STestObjectFreedNotifier	sFreedNotifier;
	CTestObject*				pcObject;
	CPointerContainer*			pcContainer1;
	CPointerContainer*			pcContainer2;

	pObject = OMalloc<CTestObject>(&sFreedNotifier);
	pContainer2 = OMalloc<CPointerContainer>(pObject);
	pContainer1 = OMalloc<CPointerContainer>(pContainer2);
	pRoot = ORoot();
	pRoot->Add(pContainer1);

	pcObject = &pObject;
	pcContainer1 = &pContainer1;
	pcContainer2 = &pContainer2;

	AssertFalse(sFreedNotifier.bFreed);

	pContainer2 = NULL;
	pObject = NULL;
	AssertLongLongInt(5, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(5, gcUnknowns.NumElements());
	AssertFalse(sFreedNotifier.bFreed);

	pRoot->Remove(pContainer1);
	AssertLongLongInt(5, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(5, gcUnknowns.NumElements());

	AssertInt(UNATTACHED_DIST_TO_ROOT, pcContainer1->GetDistToRoot());
	AssertFalse(pcContainer1->CanFindRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pcContainer2->GetDistToRoot());
	AssertFalse(pcContainer2->CanFindRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pcObject->GetDistToRoot());
	AssertFalse(pcObject->CanFindRoot());
	AssertFalse(sFreedNotifier.bFreed);

	pContainer1 = NULL;
	AssertLongLongInt(2, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(2, gcUnknowns.NumElements());
	AssertTrue(sFreedNotifier.bFreed);

	ObjectsFlush();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectKillOnHeap(void)
{
	ObjectsInit();

	Ptr<CPointerContainer>		pContainer1;
	Ptr<CPointerContainer>		pContainer2;
	Ptr<CTestObject>			pObject;
	Ptr<CRoot>					pRoot;
	STestObjectFreedNotifier	sFreedNotifier;
	CTestObject*				pcObject;
	CPointerContainer*			pcContainer1;
	CPointerContainer*			pcContainer2;

	pObject = OMalloc<CTestObject>(&sFreedNotifier);
	pContainer2 = OMalloc<CPointerContainer>(pObject);
	pContainer1 = OMalloc<CPointerContainer>(pContainer2);
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

	ObjectsFlush();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectKillPointerOnStack(void)
{
	ObjectsInit();

	Ptr<CTestObject>			pObject;
	STestObjectFreedNotifier	sFreedNotifier;

	pObject = OMalloc<CTestObject>(&sFreedNotifier);
	pObject.Kill();

	AssertTrue(sFreedNotifier.bFreed);

	ObjectsFlush();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectKillObjectOnStack(void)
{
	ObjectsInit();

	CTestObject					cObject;
	STestObjectFreedNotifier	sFreedNotifier;

	cObject.Init(&sFreedNotifier);
	cObject.Kill();

	AssertTrue(sFreedNotifier.bFreed);

	ObjectsFlush();
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
	STestObjectFreedNotifier	sFreedNotifier1;
	CTestObject*				pcObject;
	CPointerContainer*			pcContainer1;
	CPointerContainer*			pcContainer2;

	pObject = OMalloc<CTestObject>(&sFreedNotifier1);
	pContainer2 = OMalloc<CPointerContainer>(pObject);
	pContainer1 = OMalloc<CPointerContainer>(pContainer2);
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

	ObjectsFlush();
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

	pTest1 = OMalloc<CTestObject>();
	pTest2 = OMalloc<CTestObject>();
	pTest1->mpTest = pTest2;
	pTest2->mpTest = pTest1;
	pTest3 = OMalloc<CTestObject>();
	pTest3->mpTest = pTest2;
	pTest4 = OMalloc<CTestObject>();
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

	ObjectsFlush();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObject(void)
{
	BeginTests();
	MemoryInit();

	TestObjectSize();
	TestObjectGetObjects();
	TestObjectStackKill();
	TestObjectPointerRemapping();
	TestObjectPointerRemappingKilling();
	TestObjectPointerRemappingSimplerComplex();
	TestObjectPointerRemappingComplex();
	TestObjectKillOnHeap();
	TestObjectKillPointerOnStack();
	TestObjectKillObjectOnStack();
	TestObjectKillCyclic();
	TestObjectRootUnattachment();
	TestObjectSetUnattachment();

	MemoryKill();
	TestStatistics();
}

