#include "BaseLib/FileUtil.h"
#include "StandardLib/Objects.h"
#include "StandardLib/ObjectReaderSimpleDisk.h"
#include "StandardLib/ObjectGraphDeserialiser.h"
#include "StandardLib/ObjectWriterSimple.h"
#include "StandardLib/ObjectGraphSerialiser.h"
#include "StandardLib/ObjectAllocator.h"
#include "TestLib/Assert.h"
#include "ObjectWriterChunkedTestClasses.h"



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CPointer SetupObjectReaderSimpleFile(void)
{
	Ptr<CTestNamedString>	cNS1;
	Ptr<CTestNamedString>	cNS2;

	cNS1 = ONMalloc(CTestNamedString, "Waggy");
	cNS2 = ONMalloc(CTestNamedString, "Dog");

	cNS1->Init(ONull, cNS2, "NS1");
	cNS2->Init(ONull, ONull, "NS2");

	return cNS1;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void WriteObjectReaderSimpleFile(void)
{
	CPointer				cBase;
	CObjectWriterSimple		cWriter;
	CObjectGraphSerialiser	cGraphSerialiser;

	cBase = SetupObjectReaderSimpleFile();

	cWriter.Init("Output\\ObjectReaderSimple\\Test\\", "");
	cGraphSerialiser.Init(&cWriter);
	AssertTrue(cGraphSerialiser.Write(cBase.BaseObject()));
	cGraphSerialiser.Kill();
	cWriter.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectReaderSimpleDeserialised(void)
{
	CObjectReaderSimpleDisk		cReader;
	CObjectGraphDeserialiser	cGraphDeserialiser;
	CPointer				cBase;

	Ptr<CTestNamedString>	cNS1;
	Ptr<CTestNamedString>	cNS2;
	CPointer				cTemp;

	CObjectAllocator			cAllocator;
	CDependentReadObjects		cDependentReadObjects;

	gcObjects.AddConstructor<CTestNamedString>();

	WriteObjectReaderSimpleFile();

	AssertLongLongInt(0, gcObjects.NumDatabaseObjects());
	AssertLongLongInt(0, gcObjects.NumMemoryIndexes());

	ObjectsKill();
	ObjectsInit();

	gcObjects.AddConstructor<CTestNamedString>();

	AssertLongLongInt(0, gcObjects.NumDatabaseObjects());
	AssertLongLongInt(0, gcObjects.NumMemoryIndexes());

	cAllocator.Init(&gcObjects);
	cDependentReadObjects.Init();
	cReader.Init("Output\\ObjectReaderSimple\\Test\\");
	cGraphDeserialiser.Init(&cReader, FALSE, &cAllocator, &cDependentReadObjects, gcObjects.GetMemory());
	cBase = cGraphDeserialiser.Read("Waggy");

	AssertLongLongInt(0, gcObjects.NumDatabaseObjects());
	AssertLongLongInt(2, gcObjects.NumMemoryIndexes());

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
	cDependentReadObjects.Kill();
	cAllocator.Kill();
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
	cFileUtil.MakeDir("Output/ObjectReaderSimple");
	ObjectsInit();
	BeginTests();

	TestObjectReaderSimpleDeserialised();

	TestStatistics();
	ObjectsKill();

	cFileUtil.RemoveDir("Output");
}

