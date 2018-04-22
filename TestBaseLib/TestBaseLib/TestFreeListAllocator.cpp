#include "BaseLib/GlobalMemory.h"
#include "BaseLib/MemoryFile.h"
#include "BaseLib/FreeListAllocator.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFreeListAllocatorReadWrite(void)
{
	MemoryInit();

	CFreeListAllocator		cAlloc;
	CFileBasic				cFile;
	CFreeListAllocator		cAllocIn;
	int						i;
	SFreeListParams		sParams;

	cFile.Init(MemoryFile());
	cFile.Open(EFM_ReadWrite_Create);

	cFile.WriteInt(789);

	cAlloc.Init(48, 16, 4);
	AssertTrue(cAlloc.Write(&cFile));

	cFile.WriteInt(124);

	cFile.Close();
	cAlloc.Kill();

	cFile.Open(EFM_Read);

	cFile.ReadInt(&i);
	AssertInt(789, i);

	AssertTrue(cAllocIn.Read(&cFile));

	cFile.ReadInt(&i);
	AssertInt(124, i);

	AssertInt(16, cAllocIn.GetFreeList()->GetAlignment());
	AssertInt(4, cAllocIn.GetFreeList()->GetOffset());
	AssertInt(48, cAllocIn.GetFreeList()->GetElementSize());
	AssertInt(0, cAllocIn.GetFreeList()->ByteSize());
	cAllocIn.GetFreeList()->GetParams(&sParams);
	AssertInt(4, sParams.iOffset);

	MemoryKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFreeListAllocator(void)
{
	BeginTests();

	TestFreeListAllocatorReadWrite();

	TestStatistics();
}

