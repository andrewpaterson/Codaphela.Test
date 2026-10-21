#include "BaseLib/GlobalMemory.h"
#include "BaseLib/MemoryFile.h"
#include "BaseLib/ScratchPadAllocator.h"
#include "TestLib/Assert.h"
#include "ConstructorsTestClasses.h"


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
	AssertSize(0, cAlloc.GetScratchPad()->GetUsedSize());

	pcTest1 = (CConstructorTestClass*)gcConstructors.Construct("CConstructorTestClass", &cAlloc);
#ifdef BUILD_64
	AssertSize(48, cAlloc.GetScratchPad()->GetUsedSize());
#else
	AssertSize(28, cAlloc.GetScratchPad()->GetUsedSize());
#endif // BUILD_64

	pcTest1->k = 7;
	AssertInt(3, pcTest1->Method1());
	AssertInt(7, pcTest1->k);

	pcTest2 = (CConstructorTestClass*)gcConstructors.Construct("CConstructorTestClass", &cAlloc);
#ifdef BUILD_64
	AssertSize(96, cAlloc.GetScratchPad()->GetUsedSize());
#else
	AssertSize(56, cAlloc.GetScratchPad()->GetUsedSize());
#endif // BUILD_64

	cAlloc.Free(pcTest1);
#ifdef BUILD_64
	AssertSize(96, cAlloc.GetScratchPad()->GetUsedSize());
#else
	AssertSize(56, cAlloc.GetScratchPad()->GetUsedSize());
#endif // BUILD_64
	cAlloc.Free(pcTest2);
#ifdef BUILD_64
	AssertSize(96, cAlloc.GetScratchPad()->GetUsedSize());
#else
	AssertSize(56, cAlloc.GetScratchPad()->GetUsedSize());
#endif // BUILD_64

	cAlloc.Kill();

	MemoryKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestScratchPadAllocatorReadWrite(void)
{
	MemoryInit();

	CScratchPadAllocator	cAlloc;
	CFileBasic				cFile;
	CScratchPadAllocator	cAllocIn;
	int32						i;
	SScratchPadParams		sParams;

	cFile.Init(MemoryFile());
	cFile.Open(EFM_ReadWrite_Create);

	cFile.WriteInt32(789);

	cAlloc.Init(32 KB);
	AssertTrue(cAlloc.Write(&cFile));

	cFile.WriteInt32(124);

	cFile.Close();
	cAlloc.Kill();

	cFile.Open(EFM_Read);

	cFile.ReadInt32(&i);
	AssertInt(789, i);

	AssertTrue(cAllocIn.Read(&cFile));

	cFile.ReadInt32(&i);
	AssertInt(124, i);

	AssertSize(0, cAllocIn.GetScratchPad()->GetMemorySize());
	AssertSize(0, cAllocIn.GetScratchPad()->GetUsedSize());
	cAllocIn.GetScratchPad()->GetParams(&sParams);
	AssertInt(32 KB, sParams.iChunkSize);
	cFile.Close();
	cFile.Kill();
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
	TestScratchPadAllocatorReadWrite();

	TestStatistics();
}

