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
	CConstructorTestClass*		pcTest;

	gcConstructors.Add<CConstructorTestClass>("CConstructorTestClass");

	cAlloc.Init();
	AssertInt(0, cAlloc.GetScratchPad()->GetUsedSize());

	pcTest = (CConstructorTestClass*)gcConstructors.Construct("CConstructorTestClass", &cAlloc);
	AssertInt(28, cAlloc.GetScratchPad()->GetUsedSize());

	pcTest->k = 7;
	AssertInt(3, pcTest->Method1());
	AssertInt(7, pcTest->k);

	cAlloc.Free(pcTest);
	AssertInt(28, cAlloc.GetScratchPad()->GetUsedSize());

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

