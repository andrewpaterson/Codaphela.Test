#include "BaseLib/FileUtil.h"
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
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectWriterChunkedSerialised(void)
{
	CObjectWriterChunked		cWriter;
	CObjectGraphSerialiser		cGraphSerialiser;

	CPointer<CTestWithArray>	pcObject1;
	CPointer<CTestInteger>		pcObject2;
	CPointer<CTestInteger>		pcObject3;
	CPointer<CTestInteger>		pcObject4;
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
	pcObject4->Init(4, 5, 6);
	pcObject1->Add(pcObject4);

	cWriter.Init("Output\\ObjectWriterChunked\\Test\\", "Base/Level 1", "ChunkFile");

	cGraphSerialiser.Init(&cWriter);
	AssertTrue(cGraphSerialiser.Write(&pcObject1));
	cGraphSerialiser.Kill();

	cWriter.Kill();

	AssertFile("Input/ChunkFile.DRG", "Output/ObjectWriterChunked/Test/Base/Level 1/ChunkFile.DRG");

	cChunkFile.Init(DiskFile("Output/ObjectWriterChunked/Test/Base/Level 1/ChunkFile.DRG"));
	AssertTrue(cChunkFile.ReadOpen());

	//CTestWithArray pcObject1
	AssertTrue(cChunkFile.ReadChunkBegin("Warning"));
	AssertTrue(cChunkFile.ReadInt(&iLength));
	AssertInt(106, iLength);
	AssertTrue(cChunkFile.ReadData(szTest, 4));
	AssertString("NAM", szTest);
	AssertTrue(cChunkFile.ReadChunkEnd());

	//CArray
	AssertTrue(cChunkFile.ReadChunkBegin("Unnamed/0000000000000002"));
	AssertTrue(cChunkFile.ReadInt(&iLength));
	AssertInt(87, iLength);
	AssertTrue(cChunkFile.ReadData(szTest, 4));
	AssertString("IDX", szTest);
	AssertTrue(cChunkFile.ReadChunkEnd());

	//CTestInteger pcObject2
	AssertTrue(cChunkFile.ReadChunkBegin("Unnamed/0000000000000003"));
	AssertTrue(cChunkFile.ReadInt(&iLength));
	AssertInt(49, iLength);
	AssertTrue(cChunkFile.ReadData(szTest, 4));
	AssertString("IDX", szTest);
	AssertTrue(cChunkFile.ReadChunkEnd());

	//CTestInteger pcObject3
	AssertTrue(cChunkFile.ReadChunkBegin("Unnamed/0000000000000004"));
	AssertTrue(cChunkFile.ReadInt(&iLength));
	AssertInt(49, iLength);
	AssertTrue(cChunkFile.ReadData(szTest, 4));
	AssertString("IDX", szTest);
	AssertTrue(cChunkFile.ReadChunkEnd());

	//CTestInteger pcObject4
	AssertTrue(cChunkFile.ReadChunkBegin("Unnamed/0000000000000005"));
	AssertTrue(cChunkFile.ReadInt(&iLength));
	AssertInt(49, iLength);
	AssertTrue(cChunkFile.ReadData(szTest, 4));
	AssertString("IDX", szTest);
	AssertTrue(cChunkFile.ReadChunkEnd());

	AssertTrue(cChunkFile.ReadClose());
	cChunkFile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectWriterChunked(void)
{
	CFileUtil	cFileUtil;

	cFileUtil.RemoveDir("Output");
	cFileUtil.MakeDir("Output/ObjectWriterChunked");
	ObjectsInit();
	BeginTests();

	TestObjectWriterChunkedWrite();
	TestObjectWriterChunkedSerialised();

	TestStatistics();
	ObjectsKill();

	cFileUtil.RemoveDir("Output");
}

