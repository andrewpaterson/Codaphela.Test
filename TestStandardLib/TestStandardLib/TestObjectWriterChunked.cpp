#include "BaseLib/FileUtil.h"
#include "BaseLib/GlobalMemory.h"
#include "BaseLib/NaiveFile.h"
#include "StandardLib/Objects.h"
#include "StandardLib/ObjectWriterChunked.h"
#include "StandardLib/ObjectGraphSerialiser.h"
#include "TestLib/Assert.h"
#include "ObjectWriterChunkedTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectWriterChunkedSerialised(void)
{	
	MemoryInit();
	ObjectsInit();

	CObjectWriterChunked		cWriter;
	CObjectGraphSerialiser		cGraphSerialiser;

	Ptr<CTestWithArray>			pcObject1;
	Ptr<CTestInteger>			pcObject2;
	Ptr<CTestInteger>			pcObject3;
	Ptr<CTestInteger>			pcObject4;
	CChunkFileNames				cChunkFile;
	int							iLength;
	char						szTest[4];
	CFileUtil					cFileUtil;
	Ptr<CTestInteger>			pcGet;

	AssertTrue(cFileUtil.RemoveDir("Output" _FS_ "ObjectWriterChunked"));
	AssertTrue(cFileUtil.TouchDir("Output" _FS_ "ObjectWriterChunked" _FS_ "Test"));

	pcObject1 = ONMalloc<CTestWithArray>("Base/Level 1/Warning", "Talking Clock", 17);

	pcObject2 = OMalloc<CTestInteger>(2, 9, 937);
	pcObject1->Add(pcObject2);

	pcObject3 = OMalloc<CTestInteger>(3, 7321, 7);
	pcObject1->Add(pcObject3);

	pcObject4 = OMalloc<CTestInteger>(0xab, 0xbc, 0xcd);
	pcObject1->Add(pcObject4);

	cWriter.Init("Output" _FS_ "ObjectWriterChunked" _FS_ "Test", "Base" _FS_ "Level 1", "ChunkFile");

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
	CChunkFileHeader*	psInputHeader;
	CChunkFileHeader*	psOutputHeader;

	AssertTrue(cInputFile.Init()->Read("Input" _FS_ "ChunkFile.DRG"));
	AssertTrue(cOutputFile.Init()->Read("Output" _FS_ "ObjectWriterChunked" _FS_ "Test" _FS_ "Base" _FS_ "Level 1" _FS_ "ChunkFile.DRG"));
	
	AssertLongLongInt(1158LL, cInputFile.Size());
	AssertLongLongInt(1158LL, cOutputFile.Size());
	psInputHeader = (CChunkFileHeader*)cInputFile.Get();
	psOutputHeader = (CChunkFileHeader*)cOutputFile.Get();
	AssertInt(CHUNK_HEADER_MAGIC, psInputHeader->miMagic);
	AssertInt(CHUNK_HEADER_MAGIC, psOutputHeader->miMagic);
	//Why does the hash sometimes change?  Because the file is actually changing.
	// Failed
	//  INFO : CTestWithArray : 1 : "Base/Level 1/Warning"
	//  INFO : CArrayObject : 2
	//  INFO : CTestInteger : 4
	//  INFO : CTestInteger : 5
	//  INFO : CTestInteger : 3 <--
	//
	// Passed
	//  INFO : CTestWithArray : 1 : "Base/Level 1/Warning"
	//  INFO : CArrayObject : 2
	//  INFO : CTestInteger : 3 <--
	//  INFO : CTestInteger : 4
	//  INFO : CTestInteger : 5
	//CompareDependentWriteObject compares where the objects are allocated in memory.  This makes adding dependent write objects ordering depend on memory allocations.

	AssertFile("Input" _FS_ "ChunkFile.DRG", "Output" _FS_ "ObjectWriterChunked" _FS_ "Test" _FS_ "Base" _FS_ "Level 1" _FS_ "ChunkFile.DRG");
	Pass();

	cOutputFile.Kill();
	cInputFile.Kill();

	cChunkFile.Init(DiskFile("Output" _FS_ "ObjectWriterChunked" _FS_ "Test" _FS_ "Base" _FS_ "Level 1" _FS_ "ChunkFile.DRG"));
	AssertTrue(cChunkFile.ReadOpen());

	//CTestWithArray pcObject1
	AssertTrue(cChunkFile.ReadChunkBegin("Warning"));
	AssertTrue(cChunkFile.ReadInt(&iLength));
	AssertInt(127, iLength);
	AssertTrue(cChunkFile.ReadData(szTest, 4));
	AssertString("NAM", szTest);
	AssertTrue(cChunkFile.ReadChunkEnd());

	//CArrayObject
	AssertTrue(cChunkFile.ReadChunkBegin("Unnamed/0000000000000002"));
	AssertTrue(cChunkFile.ReadInt(&iLength));
	AssertInt(101, iLength);
	AssertTrue(cChunkFile.ReadData(szTest, 4));
	AssertString("IDX", szTest);
	AssertTrue(cChunkFile.ReadChunkEnd());

	//CTestInteger pcObject2
	AssertTrue(cChunkFile.ReadChunkBegin("Unnamed/0000000000000003"));
	AssertTrue(cChunkFile.ReadInt(&iLength));
	AssertInt(45, iLength);
	AssertTrue(cChunkFile.ReadData(szTest, 4));
	AssertString("IDX", szTest);
	AssertTrue(cChunkFile.ReadChunkEnd());

	//CTestInteger pcObject3
	AssertTrue(cChunkFile.ReadChunkBegin("Unnamed/0000000000000004"));
	AssertTrue(cChunkFile.ReadInt(&iLength));
	AssertInt(45, iLength);
	AssertTrue(cChunkFile.ReadData(szTest, 4));
	AssertString("IDX", szTest);
	AssertTrue(cChunkFile.ReadChunkEnd());

	//CTestInteger pcObject4
	AssertTrue(cChunkFile.ReadChunkBegin("Unnamed/0000000000000005"));
	AssertTrue(cChunkFile.ReadInt(&iLength));
	AssertInt(45, iLength);
	AssertTrue(cChunkFile.ReadData(szTest, 4));
	AssertString("IDX", szTest);
	AssertTrue(cChunkFile.ReadChunkEnd());

	AssertTrue(cChunkFile.ReadClose());
	cChunkFile.Kill();

	ObjectsFlush();
	ObjectsKill();
	MemoryKill();

	cFileUtil.RemoveDir("Output" _FS_ "ObjectWriterChunked");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectWriterChunked(void)
{
	BeginTests();

	TestObjectWriterChunkedSerialised();

	TestStatistics();
}

