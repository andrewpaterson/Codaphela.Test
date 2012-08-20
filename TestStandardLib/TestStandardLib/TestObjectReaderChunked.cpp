#include "BaseLib/FileUtil.h"
#include "StandardLib/Objects.h"
#include "StandardLib/ObjectReaderChunked.h"
#include "StandardLib/ObjectGraphDeserialiser.h"
#include "TestLib/Assert.h"
#include "ObjectWriterChunkedTestClasses.h"



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void SetupObjectReaderChunkedChunkFile(void)
{
	CPointer<CTestNamedString>	cNS1;
	CPointer<CTestNamedString>	cNS2;
	CPointer<CTestNamedString>	cNS3;
	CPointer<CTestInteger>		cI1;
	CPointer<CTestInteger>		cI2;
	CPointer<CTestInteger>		cI3;
	CPointer<CTestWithArray>	cA1;
	CPointer<CTestWithArray>	cA2;

	cNS1 = ONMalloc(CTestNamedString, "NamedString 1");
	cNS2 = ONMalloc(CTestNamedString, "NamedString 2");
	cNS3 = ONMalloc(CTestNamedString, "NamedString 3");

	cI1 = OMalloc(CTestInteger);
	cI2 = OMalloc(CTestInteger);
	cI3 = OMalloc(CTestInteger);

	cA1 = ONMalloc(CTestWithArray, "Array 1");
	cA2 = ONMalloc(CTestWithArray, "Array X");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectReaderChunkedDeserialised(void)
{
	SetupObjectReaderChunkedChunkFile();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectReaderChunked(void)
{
	CFileUtil	cFileUtil;

	cFileUtil.RemoveDir("Output");
	cFileUtil.MakeDir("Output\\ObjectWriterChunked");
	ObjectsInit(NULL);
	BeginTests();

	TestObjectReaderChunkedDeserialised();

	TestStatistics();
	ObjectsKill();

	cFileUtil.RemoveDir("Output");
}

