#include "BaseLib/GlobalMemory.h"
#include "BaseLib/ScratchPadAllocator.h"
#include "TestLib/Assert.h"
#include "ConstructorTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestScratchPadAllocatorPop(void)
{
	MemoryInit();

	CScratchPadAllocator		cAlloc;
	CConstructorTestClass*		pcTest1;
	CConstructorTestClass*		pcTest2;

	gcConstructors.Add<CConstructorTestClass>("CConstructorTestClass");

	cAlloc.Init();
	AssertInt(0, cAlloc.GetScratchPad()->GetUsedSize());

	pcTest1 = (CConstructorTestClass*)gcConstructors.Construct("CConstructorTestClass", &cAlloc);
	AssertInt(28, cAlloc.GetScratchPad()->GetUsedSize());

	pcTest1->k = 7;
	AssertInt(3, pcTest1->Method1());
	AssertInt(7, pcTest1->k);

	pcTest2 = (CConstructorTestClass*)gcConstructors.Construct("CConstructorTestClass", &cAlloc);
	AssertInt(56, cAlloc.GetScratchPad()->GetUsedSize());

	cAlloc.Free(pcTest1);
	AssertInt(56, cAlloc.GetScratchPad()->GetUsedSize());
	cAlloc.Free(pcTest2);
	AssertInt(56, cAlloc.GetScratchPad()->GetUsedSize());

	cAlloc.GetScratchPad()->Pop();
	AssertInt(56, cAlloc.GetScratchPad()->GetUsedSize());
	AssertInt(6 MB, cAlloc.GetScratchPad()->GetMemorySize());

	cAlloc.GetScratchPad()->Pop();
	AssertInt(0, cAlloc.GetScratchPad()->GetUsedSize());
	AssertInt(6 MB, cAlloc.GetScratchPad()->GetMemorySize());

	cAlloc.Kill();

	MemoryKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestScratchPadAllocator(void)
{
	BeginTests();

	TestScratchPadAllocatorPop();

	TestStatistics();
}

