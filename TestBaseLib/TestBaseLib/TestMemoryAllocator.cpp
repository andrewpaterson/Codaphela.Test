#include "BaseLib/GlobalMemory.h"
#include "BaseLib/MemoryFile.h"
#include "BaseLib/MemoryAllocator.h"
#include "TestLib/Assert.h"
#include "ConstructorsTestClasses.h"


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
void TestMemoryAllocatorReadWrite(void)
{
	MemoryInit();

	CMemoryAllocator		cAlloc;
	CFileBasic				cFile;
	CMemoryAllocator		cAllocIn;
	int						i;
	SMemoryFreeListParams*	psBlockParams;

	cFile.Init(MemoryFile());
	cFile.Open(EFM_ReadWrite_Create);

	cFile.WriteInt(789);

	cAlloc.Init(16, FALSE);
	cAlloc.GetMemory()->GetFreeListParams()->AddParamBlock(24  , 16  , 32*32);
	cAlloc.GetMemory()->GetFreeListParams()->AddParamBlock(32  , 24  , 28*32);
	cAlloc.GetMemory()->GetFreeListParams()->AddParamBlock(40  , 32  , 24*32);

	AssertTrue(cAlloc.Write(&cFile));

	cFile.WriteInt(124);

	cFile.Close();
	cAlloc.Kill();

	cFile.Open(EFM_Read);

	cFile.ReadInt(&i);
	AssertInt(789, i);

	AssertTrue(cAllocIn.Read(&cFile));

	cFile.ReadInt(&i);
	cFile.Kill();
	AssertInt(124, i);

	AssertInt(16, cAllocIn.GetMemory()->ByteSize());
	AssertInt(16, cAllocIn.GetMemory()->GetDefaultAlignment());
	AssertInt(56, cAllocIn.GetMemory()->GetFreeListParams()->GetFreeListSizeLimit());
	AssertInt(3, cAllocIn.GetMemory()->GetFreeListParams()->NumParams());

	psBlockParams = cAllocIn.GetMemory()->GetFreeListParams()->GetFreeListParams(0);
	AssertNotNull(psBlockParams);
	AssertInt(32*32, psBlockParams->iChunkSize);
	AssertInt(17, psBlockParams->iMinElementSize);
	AssertInt(24, psBlockParams->iMaxElementSize);

	psBlockParams = cAllocIn.GetMemory()->GetFreeListParams()->GetFreeListParams(1);
	AssertNotNull(psBlockParams);
	AssertInt(28*32, psBlockParams->iChunkSize);
	AssertInt(25, psBlockParams->iMinElementSize);
	AssertInt(32, psBlockParams->iMaxElementSize);

	psBlockParams = cAllocIn.GetMemory()->GetFreeListParams()->GetFreeListParams(2);
	AssertNotNull(psBlockParams);
	AssertInt(24*32, psBlockParams->iChunkSize);
	AssertInt(33, psBlockParams->iMinElementSize);
	AssertInt(40, psBlockParams->iMaxElementSize);

	psBlockParams = cAllocIn.GetMemory()->GetFreeListParams()->GetFreeListParams(3);
	AssertNull(psBlockParams);

	cAllocIn.Kill();
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
	TestMemoryAllocatorReadWrite();

	TestStatistics();
}

