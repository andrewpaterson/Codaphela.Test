#include "StandardLib/StackPointers.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestStackPointers(void)
{
	CStackPointers	cStackPointes;
	CPointer		cPointer1;
	CPointer		cPointer2;
	CStackPointer*	pcStackPointer11;
	CStackPointer*	pcStackPointer12;
	CStackPointer*	pcStackPointer21;
	CStackPointer*	pcStackPointer22;

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
	cStackPointes.Kill();
}

