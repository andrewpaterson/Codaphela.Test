#include "StandardLib/Objects.h"
#include "StandardLib/ObjectAllocator.h"
#include "TestLib/Assert.h"


void TestObjectAllocatorOverwrite(void)
{
	CObjectAllocator	cAllocator;

	ObjectsInit();

	cAllocator.Init(&gcObjects, TRUE);

	cAllocator.Add()
}


void TestObjectAllocator(void)
{
	BeginTests();

	TestObjectAllocatorOverwrite();

	TestStatistics();
}

