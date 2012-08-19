#include "BaseLib/FileUtil.h"
#include "StandardLib/Objects.h"
#include "StandardLib/ObjectWriterChunked.h"
#include "StandardLib/ObjectGraphWriter.h"
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
	CObjectGraphWriter			cGraphWriter;

	CTestWithArray				cObject1;
	CPointer<CTestInteger>		pcObject2;
	CPointer<CTestInteger>		pcObject3;
	CPointer<CTestInteger>		pcObject4;

	cObject1.Init("Talking Clock", 17);

	pcObject2 = OMalloc(CTestInteger);
	pcObject2->Init(2, 9, 937);
	cObject1.Add(pcObject2);

	pcObject3 = OMalloc(CTestInteger);
	pcObject3->Init(3, 7321, 7);
	cObject1.Add(pcObject3);

	pcObject4 = OMalloc(CTestInteger);
	pcObject4->Init(4, 5, 6);
	cObject1.Add(pcObject4);

	cWriter.Init("Output\\ObjectWriterChunked\\Test\\", "Base/Level 1", "ChunkFile");
	AssertTrue(cWriter.Begin());

	cGraphWriter.Init(&cWriter);
	AssertTrue(cGraphWriter.Write(&cObject1));
	cGraphWriter.Kill();

	AssertTrue(cWriter.End());
	cWriter.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectWriterChunked(void)
{
	CFileUtil	cFileUtil;

	cFileUtil.RemoveDir("Output");
	cFileUtil.MakeDir("Output\\ObjectWriterChunked");
	ObjectsInit(NULL);
	BeginTests();

	TestObjectWriterChunkedWrite();
	TestObjectWriterChunkedSerialised();

	TestStatistics();
	ObjectsKill();

	cFileUtil.RemoveDir("Output");
}

