#include "BaseLib/GlobalMemory.h"
#include "BaseLib/MemoryAllocator.h"
#include "TestLib/Assert.h"
#include "ConstructorTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMemoryAllocatorFree(void)
{
	MemoryInit();

	CMemoryAllocator		cAlloc;
	CConstructorTestClass*	pcTest;

	gcConstructors.Add<CConstructorTestClass>("CConstructorTestClass");

	cAlloc.Init();
	AssertInt(0, cAlloc.GetMemory()->NumElements());

	pcTest = (CConstructorTestClass*)gcConstructors.Construct("CConstructorTestClass", &cAlloc);
	AssertInt(1, cAlloc.GetMemory()->NumElements());

	pcTest->k = 7;
	AssertInt(3, pcTest->Method1());
	AssertInt(7, pcTest->k);
	
	cAlloc.Free(pcTest);
	AssertInt(0, cAlloc.GetMemory()->NumElements());

	cAlloc.Kill();

	MemoryKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMemoryAllocator(void)
{
	BeginTests();

	TestMemoryAllocatorFree();

	TestStatistics();
}

