#include "BaseLib/SystemAllocator.h"
#include "BaseLib/FreeListAllocator.h"
#include "BaseLib/MemoryBlock.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMemoryBlockAllocate(void)
{
	CMemoryBlock	cBlock;
	void*			pvMem;

	cBlock.Init(&gcSystemAllocator);
	pvMem = cBlock.Allocate(10);
	AssertNotNull(pvMem);
	AssertPointer(pvMem, cBlock.GetMemory());
	AssertInt(10, (int)cBlock.GetSize());
	pvMem = cBlock.Allocate(20);
	AssertNotNull(pvMem);
	AssertPointer(pvMem, cBlock.GetMemory());
	AssertInt(20, (int)cBlock.GetSize());
	cBlock.Kill();
	AssertNull(cBlock.GetMemory());
	AssertInt(0, (int)cBlock.GetSize());
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMemoryBlock(void)
{
	BeginTests();
	FastFunctionsInit();

	TestMemoryBlockAllocate();

	FastFunctionsKill();
	TestStatistics();
}

