#include "BaseLib/FileUtil.h"
#include "BaseLib/GlobalMemory.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/TypeNames.h"
#include "BaseLib/NaiveFile.h"
#include "BaseLib/ScratchPadAllocator.h"
#include "CoreLib/TransientSequence.h"
#include "StandardLib/Objects.h"
#include "StandardLib/ChunkFileObjectWriter.h"
#include "StandardLib/ExternalObjectSerialiser.h"
#include "TestLib/Assert.h"
#include "ChunkFileObjectWriterTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestChunkFileObjectWriterSerialised(void)
{	
	MemoryInit();
	FastFunctionsInit();
	TypesInit();
	DataIOInit();

	CScratchPadAllocator	cScratchPad;
	CUnknowns				cUnknowns;
	CLifeInit<CMallocator>	cLifeAlloc;

	cScratchPad.Init();
	cLifeAlloc.Init(&cScratchPad, FALSE, FALSE);
	cUnknowns.Init(cLifeAlloc, "TestChunkFileObjectWriterSerialised", &gcConstructors);

	ObjectsInit(&cUnknowns, &gcStackPointers, NULL, &gcTransientSequence);

	CChunkFileObjectWriter		cWriter;
	CExternalObjectSerialiser	cGraphSerialiser;

	Ptr<CTestWithArray>			pcObject1;
	Ptr<CTestInteger>			pcObject2;
	Ptr<CTestInteger>			pcObject3;
	Ptr<CTestInteger>			pcObject4;
	CChunkFile					cChunkFile;
	CChunkFileFileSystem		cChunkFileFileSystem;
	int							iLength;
	char						szTest[4];
	int							iTest;
	CFileUtil					cFileUtil;
	Ptr<CTestInteger>			pcGet;

	AssertTrue(cFileUtil.RemoveDir("Output" _FS_ "ChunkFileObjectWriter"));
	AssertTrue(cFileUtil.TouchDir("Output" _FS_ "ChunkFileObjectWriter" _FS_ "Test"));

	pcObject1 = ONMalloc<CTestWithArray>("Base/Level 1/Warning", "Talking Clock", 17);

	pcObject2 = OMalloc<CTestInteger>(2, 9, 937);
	pcObject1->Add(pcObject2);

	pcObject3 = OMalloc<CTestInteger>(3, 7321, 7);
	pcObject1->Add(pcObject3);

	pcObject4 = OMalloc<CTestInteger>(0xab, 0xbc, 0xcd);
	pcObject1->Add(pcObject4);

	cWriter.Init("Output" _FS_ "ChunkFileObjectWriter" _FS_ "Test", "Base" _FS_ "Level 1", "ChunkFile");

	AssertInt(3, pcObject1->mcArray->NumElements());
	AssertLongLongInt(3, pcObject1->mcArray->Get(0).GetIndex());
	AssertLongLongInt(4, pcObject1->mcArray->Get(1).GetIndex());
	AssertLongLongInt(5, pcObject1->mcArray->Get(2).GetIndex());

	cGraphSerialiser.Init(&cWriter);
	AssertTrue(cGraphSerialiser.Write(&pcObject1));
	cGraphSerialiser.Kill();

	cWriter.Kill();

	CNaiveFile			cInputFile;
	CNaiveFile			cOutputFile;
	SChunkFileHeader*	psInputHeader;
	SChunkFileHeader*	psOutputHeader;

	AssertTrue(cInputFile.Init()->Read("Input" _FS_ "ChunkFile.DRG"));
	AssertTrue(cOutputFile.Init()->Read("Output" _FS_ "ChunkFileObjectWriter" _FS_ "Test" _FS_ "Base" _FS_ "Level 1" _FS_ "ChunkFile.DRG"));
	
	AssertLongLongInt(1202LL, cInputFile.Size());
	AssertLongLongInt(1202LL, cOutputFile.Size());
	psInputHeader = (SChunkFileHeader*)cInputFile.Get();
	psOutputHeader = (SChunkFileHeader*)cOutputFile.Get();
	AssertInt(CHUNK_HEADER_MAGIC, psInputHeader->miMagic);
	AssertInt(CHUNK_HEADER_MAGIC, psOutputHeader->miMagic);

	AssertFile("Input" _FS_ "ChunkFile.DRG", "Output" _FS_ "ChunkFileObjectWriter" _FS_ "Test" _FS_ "Base" _FS_ "Level 1" _FS_ "ChunkFile.DRG");
	Pass();

	cOutputFile.Kill();
	cInputFile.Kill();

	cChunkFile.Init(DiskFile("Output" _FS_ "ChunkFileObjectWriter" _FS_ "Test" _FS_ "Base" _FS_ "Level 1" _FS_ "ChunkFile.DRG"));
	cChunkFileFileSystem.Init(&cChunkFile);
	AssertTrue(cChunkFileFileSystem.ReadOpen());

	//CTestWithArray pcObject1
	AssertTrue(cChunkFileFileSystem.ReadChunkBegin("Warning"));
	AssertTrue(cChunkFileFileSystem.ReadInt(&iLength));
	AssertInt(130, iLength);
	AssertTrue(cChunkFileFileSystem.ReadData(szTest, 4));
	AssertString("DAT", szTest);
	AssertTrue(cChunkFileFileSystem.ReadData(szTest, 4));
	AssertString("NAM", szTest);
	AssertTrue(cChunkFileFileSystem.ReadData(&iTest, 4));
	AssertInt(-1, iTest);
	AssertTrue(cChunkFileFileSystem.ReadChunkEnd());

	//CArrayObject
	AssertTrue(cChunkFileFileSystem.ReadChunkBegin("Unnamed/0000000000000002"));
	AssertTrue(cChunkFileFileSystem.ReadInt(&iLength));
	AssertInt(121, iLength);
	AssertTrue(cChunkFileFileSystem.ReadData(szTest, 4));
	AssertString("DAT", szTest);
	AssertTrue(cChunkFileFileSystem.ReadData(szTest, 4));
	AssertString("IDX", szTest);
	AssertTrue(cChunkFileFileSystem.ReadData(&iTest, 4));
	AssertInt(-1, iTest);
	AssertTrue(cChunkFileFileSystem.ReadChunkEnd());

	//CTestInteger pcObject2
	AssertTrue(cChunkFileFileSystem.ReadChunkBegin("Unnamed/0000000000000003"));
	AssertTrue(cChunkFileFileSystem.ReadInt(&iLength));
	AssertInt(65, iLength);
	AssertTrue(cChunkFileFileSystem.ReadData(szTest, 4));
	AssertString("DAT", szTest);
	AssertTrue(cChunkFileFileSystem.ReadData(szTest, 4));
	AssertString("IDX", szTest);
	AssertTrue(cChunkFileFileSystem.ReadChunkEnd());

	//CTestInteger pcObject3
	AssertTrue(cChunkFileFileSystem.ReadChunkBegin("Unnamed/0000000000000004"));
	AssertTrue(cChunkFileFileSystem.ReadInt(&iLength));
	AssertInt(65, iLength);
	AssertTrue(cChunkFileFileSystem.ReadData(szTest, 4));
	AssertString("DAT", szTest);
	AssertTrue(cChunkFileFileSystem.ReadData(szTest, 4));
	AssertString("IDX", szTest);
	AssertTrue(cChunkFileFileSystem.ReadData(&iTest, 4));
	AssertInt(-1, iTest);
	AssertTrue(cChunkFileFileSystem.ReadChunkEnd());

	//CTestInteger pcObject4
	AssertTrue(cChunkFileFileSystem.ReadChunkBegin("Unnamed/0000000000000005"));
	AssertTrue(cChunkFileFileSystem.ReadInt(&iLength));
	AssertInt(65, iLength);
	AssertTrue(cChunkFileFileSystem.ReadData(szTest, 4));
	AssertString("DAT", szTest);
	AssertTrue(cChunkFileFileSystem.ReadData(szTest, 4));
	AssertString("IDX", szTest);
	AssertTrue(cChunkFileFileSystem.ReadData(&iTest, 4));
	AssertInt(-1, iTest);
	AssertTrue(cChunkFileFileSystem.ReadChunkEnd());

	AssertTrue(cChunkFileFileSystem.ReadClose());
	cChunkFileFileSystem.Kill();
	cChunkFile.Kill();

	ObjectsFlush();
	ObjectsKill();

	cScratchPad.Kill();

	DataIOKill();
	TypesKill();
	FastFunctionsKill();
	MemoryKill();

	cFileUtil.RemoveDir("Output" _FS_ "ChunkFileObjectWriter");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestChunkFileObjectWriter(void)
{
	BeginTests();

	TestChunkFileObjectWriterSerialised();

	TestStatistics();
}

