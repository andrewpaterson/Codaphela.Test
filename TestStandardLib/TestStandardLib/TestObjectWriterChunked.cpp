#include "BaseLib/FileUtil.h"
#include "BaseLib/GlobalMemory.h"
#include "StandardLib/Objects.h"
#include "StandardLib/ObjectWriterChunked.h"
#include "StandardLib/ObjectGraphSerialiser.h"
#include "TestLib/Assert.h"
#include "ObjectWriterChunkedTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectWriterChunkedWrite(void)
{
	MemoryInit();
	ObjectsInit();

	ObjectsKill();
	MemoryKill();
}


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

	pcObject1 = ONMalloc(CTestWithArray, "Base/Level 1/Warning");
	pcObject1->Init("Talking Clock", 17);

	pcObject2 = OMalloc(CTestInteger);
	pcObject2->Init(2, 9, 937);
	pcObject1->Add(pcObject2);

	pcObject3 = OMalloc(CTestInteger);
	pcObject3->Init(3, 7321, 7);
	pcObject1->Add(pcObject3);

	pcObject4 = OMalloc(CTestInteger);
	pcObject4->Init(0xab, 0xbc, 0xcd);
	pcObject1->Add(pcObject4);

	cWriter.Init("Output" _FS_ "ObjectWriterChunked" _FS_ "Test" _FS_, "Base/Level 1", "ChunkFile");

	cGraphSerialiser.Init(&cWriter);
	AssertTrue(cGraphSerialiser.Write(&pcObject1));
	cGraphSerialiser.Kill();

	cWriter.Kill();

	AssertFile("Input" _FS_ "ChunkFile.DRG", "Output" _FS_ "ObjectWriterChunked" _FS_ "Test" _FS_ "Base" _FS_ "Level 1" _FS_ "ChunkFile.DRG");

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

	ObjectsKill();
	MemoryKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectWriterChunked(void)
{
	CFileUtil	cFileUtil;

	cFileUtil.RemoveDir("Output");
	cFileUtil.MakeDir("Output" _FS_ "ObjectWriterChunked");
	BeginTests();

	TestObjectWriterChunkedWrite();
	TestObjectWriterChunkedSerialised();

	TestStatistics();

	cFileUtil.RemoveDir("Output");
}

