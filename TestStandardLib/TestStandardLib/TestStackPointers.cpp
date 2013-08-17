#include "StandardLib/StackPointers.h"
#include "StandardLib/Pointer.h"
#include "TestLib/Assert.h"


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
void TestStackPointers(void)
{
	BeginTests();

	TestStackPointersFindUnused();
	TestStackPointersAdd();

	TestStatistics();
}

