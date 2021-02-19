#include "BaseLib/ChunkFile.h"
#include "BaseLib/ChunkFileFile.h"
#include "BaseLib/MemoryFile.h"
#include "BaseLib/GlobalMemory.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestChunkFileFileRead(void)
{
	CChunkFile		cChunkFile;
	int				iChunkNum;
	char			szZ[] = {"Z"};
	CChunkFileFile	cChunkFileFile;
	char			cz;

	cChunkFile.Init(MemoryFile());
	AssertTrue(cChunkFile.WriteOpen());
	AssertTrue(cChunkFile.WriteChunkBegin());
	AssertLongLongInt(1, cChunkFile.Write(szZ, 1, 1));
	AssertTrue(cChunkFile.WriteChunkEnd("Zynaps"));
	AssertTrue(cChunkFile.WriteClose());

	AssertTrue(cChunkFile.ReadOpen());
	iChunkNum = cChunkFile.FindFirstChunkWithName("Zynaps");
	AssertInt(0, iChunkNum);
	AssertTrue(cChunkFile.ReadChunkBegin(iChunkNum));

	cChunkFileFile.Init(&cChunkFile);
	AssertTrue(cChunkFileFile.Open(EFM_Read));
	AssertLongLongInt(1, cChunkFileFile.Size());
	AssertLongLongInt(0, cChunkFileFile.Tell());
	AssertLongLongInt(1, cChunkFileFile.Read(&cz, 1, 1));
	AssertChar('Z', cz); cz = 'Q';

	AssertTrue(cChunkFileFile.Seek(0, EFSO_SET));
	AssertLongLongInt(0, cChunkFileFile.Tell());
	AssertLongLongInt(1, cChunkFileFile.Read(&cz, 1, 1));
	AssertChar('Z', cz); cz = 'Q';
	AssertLongLongInt(1, cChunkFileFile.Tell());
	AssertLongLongInt(0, cChunkFileFile.Read(&cz, 1, 1));
	AssertLongLongInt(1, cChunkFileFile.Tell());

	AssertTrue(cChunkFileFile.Seek(0, EFSO_SET));
	AssertLongLongInt(1, cChunkFileFile.Read(&cz, 1, 2));
	AssertChar('Z', cz); cz = 'Q';
	AssertLongLongInt(1, cChunkFileFile.Tell());

	AssertTrue(cChunkFileFile.Close());

	AssertTrue(cChunkFile.ReadChunkEnd());
	AssertTrue(cChunkFile.ReadClose());

	cChunkFile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestChunkFileFile(void)
{
	BeginTests();
	FastFunctionsInit();
	MemoryInit();

	TestChunkFileFileRead();

	MemoryKill();
	FastFunctionsKill();
	TestStatistics();
}

