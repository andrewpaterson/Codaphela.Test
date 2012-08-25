#include "BaseLib/FileUtil.h"
#include "StandardLib/Objects.h"
#include "StandardLib/ObjectReaderChunked.h"
#include "StandardLib/ObjectGraphDeserialiser.h"
#include "StandardLib/ObjectWriterChunked.h"
#include "StandardLib/ObjectGraphSerialiser.h"
#include "TestLib/Assert.h"
#include "ObjectWriterChunkedTestClasses.h"



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CPointerObject SetupObjectReaderChunkedChunkFile(void)
{
	CPointer<CTestNamedString>	cNS1;
	CPointer<CTestNamedString>	cNS2;
	CPointer<CTestNamedString>	cNS3;
	CPointer<CTestInteger>		cI1;
	CPointer<CTestInteger>		cI2;
	CPointer<CTestInteger>		cI3;
	CPointer<CTestWithArray>	cA1;
	CPointer<CTestWithArray>	cA2;
	CPointer<CString>			sz1;
	CPointer<CString>			sz2;
	CPointer<CString>			sz3;

	cNS1 = ONMalloc(CTestNamedString, "NamedString 1");
	cNS2 = ONMalloc(CTestNamedString, "NamedString 2");
	cNS3 = ONMalloc(CTestNamedString, "NamedString 3");

	cI1 = OMalloc(CTestInteger);
	cI2 = OMalloc(CTestInteger);
	cI3 = OMalloc(CTestInteger);

	cA1 = ONMalloc(CTestWithArray, "Array 1");
	cA2 = ONMalloc(CTestWithArray, "Array X");

	sz1 = OMalloc(CString);
	sz2 = OMalloc(CString);
	sz3 = OMalloc(CString);

	sz1->Init("String 1");
	cNS1->Init(sz1, cNS2, "In Named 1");

	cNS2->Init(sz1, cNS3, "Another in 2");

	sz3->Init("3");
	cNS3->Init(sz3, cNS1, "Three");

	cI1->Init(3, 2, 1);
	cI2->Init(543, 3, 4);
	cI3->Init(10, 8192, 7);

	sz2->Init("Ye!");
	cA1->Init("Something with One", 1);
	cA1->Add(sz2);
	cA1->Add(cNS1);
	cA1->Add(cI1);
	cA1->Add(cNS3);
	cA1->Add(cI2);
	cA1->Add(cA2);

	cA2->Init("An with 2", 2);
	cA2->Add(cI3);
	cA2->Add(cNS2);
	cA2->Add(cI1);

	return cA1;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void WriteObjectReaderChunkedFile(void)
{
	CPointerObject			cBase;
	CObjectWriterChunked	cWriter;
	CObjectGraphSerialiser	cGraphSerialiser;

	cBase = SetupObjectReaderChunkedChunkFile();

	cWriter.Init("Output\\ObjectReaderChunked\\Test\\", "", "Reader");
	cGraphSerialiser.Init(&cWriter);
	AssertTrue(cGraphSerialiser.Write(&cBase));
	cGraphSerialiser.Kill();
	cWriter.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectReaderChunkedDeserialised(void)
{
	CObjectReaderChunked		cReader;
	CObjectGraphDeserialiser	cGraphDeserialiser;
	CPointerObject				cBase;
	CPointer<CTestWithArray>	cA1;
	CPointer<CTestWithArray>	cA2;
	CPointer<CTestNamedString>	cNS1;
	CPointer<CTestNamedString>	cNS2;
	CPointer<CTestNamedString>	cNS3;

	gcObjects.AddConstructor<CTestWithArray>();
	gcObjects.AddConstructor<CTestInteger>();
	gcObjects.AddConstructor<CTestNamedString>();
	gcObjects.AddConstructor<CString>();
	gcObjects.AddConstructor<CArray>();

	WriteObjectReaderChunkedFile();

	AssertLongLongInt(0, gcObjects.NumDatabaseObjects());
	AssertLongLongInt(13, gcObjects.NumMemoryObjects());

	ObjectsKill();
	ObjectsInit(NULL);

	AssertLongLongInt(0, gcObjects.NumDatabaseObjects());
	AssertLongLongInt(0, gcObjects.NumMemoryObjects());

	cReader.Init("Output\\ObjectReaderChunked\\Test\\", "Reader");
	cGraphDeserialiser.Init(&cReader);
	cBase = cGraphDeserialiser.Read("Array 1");

	AssertLongLongInt(0, gcObjects.NumDatabaseObjects());
	AssertLongLongInt(13, gcObjects.NumMemoryObjects());

	cA1 = gcObjects.Get("Array 1");
	AssertTrue(cA1.IsNotNull());
	AssertString("CTestWithArray", cA1->ClassName());
	AssertString("Something with One", cA1->mszString.Text());
	AssertInt(1, cA1->mx);

	cA2 = gcObjects.Get("Array X");
	AssertTrue(cA2.IsNotNull());
	AssertString("CTestWithArray", cA2->ClassName());
	AssertString("An with 2", cA2->mszString.Text());
	AssertInt(2, cA2->mx);

	cNS1 = gcObjects.Get("NamedString 1");
	AssertTrue(cNS1.IsNotNull());
	AssertString("CTestNamedString", cNS1->ClassName());
	AssertString("In Named 1", cNS1->mszEmbedded.Text());

	cNS2 = gcObjects.Get("NamedString 2");
	AssertTrue(cNS2.IsNotNull());
	AssertString("CTestNamedString", cNS2->ClassName());
	AssertString("Another in 2", cNS2->mszEmbedded.Text());

	cNS3 = gcObjects.Get("NamedString 3");
	AssertTrue(cNS3.IsNotNull());
	AssertString("CTestNamedString", cNS3->ClassName());
	AssertString("Three", cNS3->mszEmbedded.Text());

	AssertTrue(cBase.IsNotNull());
	AssertString("CTestWithArray", cBase->ClassName());
	AssertPointer(&cA1, &cBase);
	
	AssertNotNull(&cA1->mcArray);


	cGraphDeserialiser.Kill();
	cReader.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectReaderChunked(void)
{
	CFileUtil	cFileUtil;

	cFileUtil.RemoveDir("Output");
	cFileUtil.MakeDir("Output\\ObjectReaderChunked");
	ObjectsInit(NULL);
	BeginTests();

	TestObjectReaderChunkedDeserialised();

	TestStatistics();
	ObjectsKill();

	cFileUtil.RemoveDir("Output");
}

