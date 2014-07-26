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

	cAlloc.Init();

	gcConstructors.Add<CConstructorTestClass>("CConstructorTestClass");
	pcTest = (CConstructorTestClass*)gcConstructors.Construct("CConstructorTestClass", &cAlloc);
	pcTest->k = 7;

	AssertInt(3, pcTest->Method1());
	AssertInt(7, pcTest->k);
	
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

