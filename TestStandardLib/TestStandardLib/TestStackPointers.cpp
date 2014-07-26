#include "BaseLib/GlobalMemory.h"
#include "StandardLib/StackPointers.h"
#include "StandardLib/Pointer.h"
#include "StandardLib/Objects.h"
#include "TestLib/Assert.h"
#include "ObjectTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestStackPointersAdd(void)
{
	CStackPointers	cStackPointes;
	CPointer		cPointer1;
	CPointer		cPointer2;
	CStackPointer*	pcStackPointer11;
	CStackPointer*	pcStackPointer12;
	CStackPointer*	pcStackPointer13;
	CStackPointer*	pcStackPointer21;
	CStackPointer*	pcStackPointer22;
	CStackPointer*	pcStackPointer23;
	CStackPointer*	pcStackPointerNull;

	cStackPointes.Init(6);

	pcStackPointer11 = cStackPointes.Add(cPointer1.This());
	AssertNotNull(pcStackPointer11);

	pcStackPointer12 = cStackPointes.Add(cPointer1.This(), pcStackPointer11);
	AssertNotNull(pcStackPointer12);
	AssertPointer(pcStackPointer11->GetNext(), pcStackPointer12);

	AssertInt(2, pcStackPointer11->NumPointers());

	pcStackPointer21 = cStackPointes.Add(cPointer2.This());
	AssertNotNull(pcStackPointer21);

	pcStackPointer22 = cStackPointes.Add(cPointer2.This(), pcStackPointer21);
	AssertNotNull(pcStackPointer22);
	AssertPointer(pcStackPointer21->GetNext(), pcStackPointer22);

	AssertInt(2, pcStackPointer21->NumPointers());

	AssertInt(4, cStackPointes.UsedPointers());

	pcStackPointer13 = cStackPointes.Add(cPointer1.This(), pcStackPointer11);
	AssertNotNull(pcStackPointer13);
	AssertPointer(pcStackPointer11->GetNext(), pcStackPointer12);
	AssertPointer(pcStackPointer12->GetNext(), pcStackPointer13);
	AssertNull(pcStackPointer13->GetNext());

	AssertInt(3, pcStackPointer11->NumPointers());

	pcStackPointer23 = cStackPointes.Add(cPointer1.This(), pcStackPointer21);
	AssertNotNull(pcStackPointer23);
	AssertPointer(pcStackPointer21->GetNext(), pcStackPointer22);
	AssertPointer(pcStackPointer22->GetNext(), pcStackPointer23);
	AssertNull(pcStackPointer23->GetNext());

	AssertInt(3, pcStackPointer21->NumPointers());

	AssertInt(6, cStackPointes.UsedPointers());

	pcStackPointerNull = cStackPointes.Add(cPointer1.This(), pcStackPointer11);
	AssertNull(pcStackPointerNull);
	AssertInt(3, pcStackPointer11->NumPointers());

	AssertInt(6, cStackPointes.UsedPointers());

	cStackPointes.RemoveAll(pcStackPointer21);

	AssertInt(3, cStackPointes.UsedPointers());

	AssertFalse(pcStackPointer21->mbUsed);

	pcStackPointer21 = cStackPointes.Add(cPointer1.This());
	AssertNotNull(pcStackPointer21);

	pcStackPointer22 = cStackPointes.Add(cPointer2.This(), pcStackPointer21);
	AssertNotNull(pcStackPointer22);
	AssertPointer(pcStackPointer21->GetNext(), pcStackPointer22);

	AssertInt(2, pcStackPointer21->NumPointers());

	pcStackPointer23 = cStackPointes.Add(cPointer1.This(), pcStackPointer21);
	AssertNotNull(pcStackPointer23);
	AssertPointer(pcStackPointer21->GetNext(), pcStackPointer22);
	AssertPointer(pcStackPointer22->GetNext(), pcStackPointer23);
	AssertNull(pcStackPointer23->GetNext());

	AssertInt(3, pcStackPointer21->NumPointers());

	AssertInt(6, cStackPointes.UsedPointers());

	pcStackPointerNull = cStackPointes.Add(cPointer1.This(), pcStackPointer21);
	AssertNull(pcStackPointerNull);
	AssertInt(3, pcStackPointer11->NumPointers());

	AssertInt(6, cStackPointes.UsedPointers());

	cStackPointes.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestStackPointersFindUnused(void)
{
	CStackPointers	cStackPointes;
	
	cStackPointes.Init(3);

	AssertInt(2, cStackPointes.TestFindUnusedIndex(2));
	AssertInt(0, cStackPointes.TestFindUnusedIndex(0));
	AssertInt(1, cStackPointes.TestFindUnusedIndex(1));

	cStackPointes.TestAdd(2);
	AssertInt(0, cStackPointes.TestFindUnusedIndex(2));
	cStackPointes.TestKill(2);

	cStackPointes.TestAdd(0);
	AssertInt(1, cStackPointes.TestFindUnusedIndex(0));
	cStackPointes.TestKill(0);

	cStackPointes.TestAdd(1);
	AssertInt(2, cStackPointes.TestFindUnusedIndex(1));
	cStackPointes.TestKill(1);

	cStackPointes.TestAdd(2);
	cStackPointes.TestAdd(0);
	AssertInt(1, cStackPointes.TestFindUnusedIndex(2));
	AssertInt(1, cStackPointes.TestFindUnusedIndex(0));
	AssertInt(1, cStackPointes.TestFindUnusedIndex(1));
	cStackPointes.TestKill(2);
	cStackPointes.TestKill(0);

	cStackPointes.TestAdd(0);
	cStackPointes.TestAdd(1);
	AssertInt(2, cStackPointes.TestFindUnusedIndex(0));
	AssertInt(2, cStackPointes.TestFindUnusedIndex(1));
	AssertInt(2, cStackPointes.TestFindUnusedIndex(2));
	cStackPointes.TestKill(0);
	cStackPointes.TestKill(1);

	cStackPointes.TestAdd(1);
	cStackPointes.TestAdd(2);
	AssertInt(0, cStackPointes.TestFindUnusedIndex(1));
	AssertInt(0, cStackPointes.TestFindUnusedIndex(2));
	AssertInt(0, cStackPointes.TestFindUnusedIndex(0));
	cStackPointes.TestKill(1);
	cStackPointes.TestKill(2);

	cStackPointes.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestStackPointersHeapKill(void)
{
	ObjectsInit();

	Ptr<CTestObject>			pTest1;
	Ptr<CTestObject>			pTest2;
	Ptr<CTestObject>			pTest3;
	STestObjectKilledNotifier	sKillNotifier1;
	STestObjectKilledNotifier	sKillNotifier2;

	pTest1 = OMalloc(CTestObject)->Init(&sKillNotifier1);
	pTest2 = OMalloc(CTestObject)->Init(&sKillNotifier2);
	AssertLongLongInt(1LL, pTest1.GetIndex());
	AssertLongLongInt(2LL, pTest2.GetIndex());
	pTest3 = pTest2;

	pTest1->mpTest = pTest2;

	//
	//        O[2]
	//        / ^ ^
	//       /  .  .
	//      /   .   .
	//     /    .    .
	//  O[1]  pTest2 pTest3
	//    ^     ^     ^  
	//    |     .     .  
	//  pTest1  .     .  
	//    ^     .     .  
	//    .     .     . 
	//

	AssertInt(UNKNOWN_DIST_TO_STACK, pTest1->GetDistToStack());
	AssertInt(UNKNOWN_DIST_TO_STACK, pTest2->GetDistToStack());
	AssertInt(2, pTest2->NumStackFroms());
	AssertInt(1, pTest2->NumHeapFroms());
	AssertInt(1, pTest1->NumStackFroms());
	AssertInt(0, pTest1->NumHeapFroms());
	AssertLongLongInt(2, gcObjects.NumMemoryIndexes());

	pTest3 = NULL;

	//
	//       O[2]
	//       / ^ 
	//      /   . 
	//     /     . 
	//  O[1]   pTest2
	//    ^       ^      -
	//    .       .      .
	//  pTest1    .    pTest3
	//    ^       .      ^  
	//    .       .      .    
	//

	AssertFalse(sKillNotifier1.bKilled);
	AssertFalse(sKillNotifier2.bKilled);
	AssertInt(UNKNOWN_DIST_TO_STACK, pTest1->GetDistToStack());
	AssertInt(UNKNOWN_DIST_TO_STACK, pTest2->GetDistToStack());
	AssertInt(1, pTest2->NumStackFroms());
	AssertInt(1, pTest2->NumHeapFroms());
	AssertInt(1, pTest1->NumStackFroms());
	AssertInt(0, pTest1->NumHeapFroms());
	AssertLongLongInt(2, gcObjects.NumMemoryIndexes());

	pTest1 = NULL;

	//      O[2]
	//        ^      -      -
	//        .      .	    .
	//     pTest2  pTest2  pTest3
	//        ^      ^      ^  
	//        .      .      .  

	AssertTrue(sKillNotifier1.bKilled);
	AssertFalse(sKillNotifier2.bKilled);
	AssertInt(UNKNOWN_DIST_TO_STACK, pTest2->GetDistToStack());
	AssertInt(1, pTest2->NumStackFroms());
	AssertInt(0, pTest2->NumHeapFroms());
	AssertLongLongInt(1, gcObjects.NumMemoryIndexes());

	pTest1 = OMalloc(CTestObject)->Init(&sKillNotifier1);
	AssertLongLongInt(3LL, pTest1.GetIndex());
	AssertLongLongInt(2LL, pTest2.GetIndex());
	pTest1->mpTest = pTest2;

	//
	//      O[2]
	//       / ^ 
	//      /   . 
	//     /     . 
	//  O[3]   pTest2
	//    ^       ^      -
	//    .       .      .
	//  pTest1    .    pTest3
	//    ^       .      ^  
	//    .       .      .  
	//

	AssertFalse(sKillNotifier1.bKilled);
	AssertFalse(sKillNotifier2.bKilled);
	AssertInt(UNKNOWN_DIST_TO_STACK, pTest1->GetDistToStack());
	AssertInt(UNKNOWN_DIST_TO_STACK, pTest2->GetDistToStack());
	AssertInt(1, pTest2->NumStackFroms());
	AssertInt(1, pTest2->NumHeapFroms());
	AssertInt(1, pTest1->NumStackFroms());
	AssertInt(0, pTest1->NumHeapFroms());
	AssertLongLongInt(2, gcObjects.NumMemoryIndexes());

	pTest2 = NULL;

	//
	//   O[2]
	//    ^
	//    |  
	//   O[3]  
	//    ^        -      -
	//    |   	   .      .
	//  pTest1	 pTest2  pTest3
	//    ^   	   ^       ^  
	//    .   	   .       .  
	//

	AssertFalse(sKillNotifier1.bKilled);
	AssertFalse(sKillNotifier2.bKilled);
	AssertInt(UNKNOWN_DIST_TO_STACK, pTest1->GetDistToStack());
	AssertInt(UNKNOWN_DIST_TO_STACK, pTest1->mpTest->GetDistToStack());
	AssertInt(0, pTest1->mpTest->NumStackFroms());
	AssertInt(1, pTest1->mpTest->NumHeapFroms());
	AssertInt(1, pTest1->NumStackFroms());
	AssertInt(0, pTest1->NumHeapFroms());
	AssertLongLongInt(2, gcObjects.NumMemoryIndexes());

	pTest1 = NULL;

	//
	//    -       -       -
	//    .       .       .
	//  pTest1  pTest2  pTest3
	//    ^       ^       ^  
	//    .       .       .  
	//

	AssertTrue(sKillNotifier1.bKilled);
	AssertTrue(sKillNotifier2.bKilled);
	AssertLongLongInt(0, gcObjects.NumMemoryIndexes());

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestStackPointersHeapKillSingle(void)
{
	MemoryInit();
	ObjectsInit();

	Ptr<CTestObject>			pTest1;
	STestObjectKilledNotifier	sKillNotifier1;

	pTest1 = OMalloc(CTestObject)->Init(&sKillNotifier1);

	AssertInt(UNKNOWN_DIST_TO_STACK, pTest1->GetDistToStack());
	AssertInt(1, pTest1->NumStackFroms());
	AssertInt(0, pTest1->NumHeapFroms());
	AssertLongLongInt(1, gcObjects.NumMemoryIndexes());

	pTest1 = NULL;

	AssertLongLongInt(0, gcObjects.NumMemoryIndexes());

	ObjectsKill();
	MemoryKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestStackPointersKillSingle(void)
{
	MemoryInit();
	ObjectsInit();

	Ptr<CTestObject>			pTest1;
	STestObjectKilledNotifier	sKillNotifier1;

	pTest1 = OMalloc(CTestObject)->Init(&sKillNotifier1);

	AssertInt(UNKNOWN_DIST_TO_STACK, pTest1->GetDistToStack());
	AssertInt(1, pTest1->NumStackFroms());
	AssertInt(0, pTest1->NumHeapFroms());
	AssertLongLongInt(1, gcObjects.NumMemoryIndexes());

	pTest1->Kill();
	AssertTrue(pTest1.IsNull());
	AssertLongLongInt(0, gcObjects.NumMemoryIndexes());

	ObjectsKill();
	MemoryKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestStackPointers(void)
{
	BeginTests();

	TestStackPointersFindUnused();
	TestStackPointersAdd();
	TestStackPointersKillSingle();
	TestStackPointersHeapKillSingle();
	TestStackPointersHeapKill();

	TestStatistics();
}

