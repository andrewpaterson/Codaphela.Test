#include "BaseLib/FileUtil.h"
#include "StandardLib/Objects.h"
#include "StandardLib/ObjectReaderSimple.h"
#include "StandardLib/ObjectGraphDeserialiser.h"
#include "StandardLib/ObjectWriterSimple.h"
#include "StandardLib/ObjectGraphSerialiser.h"
#include "TestLib/Assert.h"
#include "ObjectWriterChunkedTestClasses.h"



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CPointerObject SetupObjectReaderSimpleFile(void)
{
	CPointer<CTestNamedString>	cNS1;
	CPointer<CTestNamedString>	cNS2;

	cNS1 = ONMalloc(CTestNamedString, "Waggy");
	cNS2 = ONMalloc(CTestNamedString, "Dog");

	cNS1->Init(ONNull(CString), cNS2, "NS1");
	cNS2->Init(ONNull(CString), ONNull(CTestNamedString), "NS2");

	return cNS1;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void WriteObjectReaderSimpleFile(void)
{
	CPointerObject			cBase;
	CObjectWriterSimple		cWriter;
	CObjectGraphSerialiser	cGraphSerialiser;

	cBase = SetupObjectReaderSimpleFile();

	cWriter.Init("Output\\ObjectReaderSimple\\Test\\", "");
	cGraphSerialiser.Init(&cWriter);
	AssertTrue(cGraphSerialiser.Write(&cBase));
	cGraphSerialiser.Kill();
	cWriter.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectReaderSimpleDeserialised(void)
{
	CObjectReaderSimple			cReader;
	CObjectGraphDeserialiser	cGraphDeserialiser;
	CPointerObject				cBase;

	CPointer<CTestNamedString>	cNS1;
	CPointer<CTestNamedString>	cNS2;
	CPointerObject				cTemp;

	gcObjects.AddConstructor<CTestNamedString>();

	WriteObjectReaderSimpleFile();

	AssertLongLongInt(0, gcObjects.NumDatabaseObjects());
	AssertLongLongInt(2, gcObjects.NumMemoryObjects());

	ObjectsKill();
	ObjectsInit(NULL);

	gcObjects.AddConstructor<CTestNamedString>();

	AssertLongLongInt(0, gcObjects.NumDatabaseObjects());
	AssertLongLongInt(0, gcObjects.NumMemoryObjects());

	cReader.Init("Output\\ObjectReaderSimple\\Test\\");
	cGraphDeserialiser.Init(&cReader, gcObjects.GetIndexGenerator());
	cBase = cGraphDeserialiser.Read("Waggy");

	AssertLongLongInt(0, gcObjects.NumDatabaseObjects());
	AssertLongLongInt(2, gcObjects.NumMemoryObjects());

	cNS1 = gcObjects.Get("Waggy");
	AssertTrue(cNS1.IsNotNull());
	AssertString("NS1", cNS1->mszEmbedded.Text());

	cNS2 = gcObjects.Get("Dog");
	AssertTrue(cNS2.IsNotNull());
	AssertString("NS2", cNS2->mszEmbedded.Text());


	AssertTrue(cBase.IsNotNull());
	AssertString("CTestNamedString", cBase->ClassName());
	AssertPointer(&cNS1, &cBase);

	AssertPointer(&cNS2, &cNS1->mpAnother);
	AssertPointer(NULL, &cNS2->mpAnother);

	cGraphDeserialiser.Kill();
	cReader.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectReaderSimple(void)
{
	CFileUtil	cFileUtil;

	cFileUtil.RemoveDir("Output");
	cFileUtil.MakeDir("Output\\ObjectReaderSimple");
	ObjectsInit(NULL);
	BeginTests();

	TestObjectReaderSimpleDeserialised();

	TestStatistics();
	ObjectsKill();

	cFileUtil.RemoveDir("Output");
}

