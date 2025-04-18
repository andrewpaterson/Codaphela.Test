#include "BaseLib/GlobalMemory.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/TypeNames.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/Codabase.h"
#include "BaseLib/CodabaseFactory.h"
#include "BaseLib/SequenceFactory.h"
#include "StandardLib/Objects.h"
#include "StandardLib/ObjectReaderSimpleDisk.h"
#include "StandardLib/ExternalObjectDeserialiser.h"
#include "StandardLib/MultiFileObjectWriter.h"
#include "StandardLib/ExternalObjectSerialiser.h"
#include "TestLib/Assert.h"
#include "ChunkFileObjectWriterTestClasses.h"



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CPointer SetupObjectReaderSimpleFile(void)
{
	Ptr<CTestNamedString>	cNS1;
	Ptr<CTestNamedString>	cNS2;

	cNS2 = ONMalloc<CTestNamedString>("Dog", Null(), Null(), "NS2");
	cNS1 = ONMalloc<CTestNamedString>("Waggy", Null(), cNS2, "NS1");


	return cNS1;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void WriteObjectReaderSimpleFile(void)
{
	ObjectsInit();
	gcObjects.AddConstructor<CTestNamedString>();

	CPointer				cBase;
	CMultiFileObjectWriter		cWriter;
	CExternalObjectSerialiser	cGraphSerialiser;

	cBase = SetupObjectReaderSimpleFile();

	cWriter.Init("Output" _FS_ "ObjectReaderSimple" _FS_ "Test" _FS_, "");
	cGraphSerialiser.Init(&cWriter);
	AssertTrue(cGraphSerialiser.Write(cBase.BaseObject()));
	cGraphSerialiser.Kill();
	cWriter.Kill();

	ObjectsFlush();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectReaderSimpleDeserialised(void)
{
	CFileUtil					cFileUtil;
	char						szDirectory[] = "Output" _FS_ "ObjectReaderSimple";

	cFileUtil.RemoveDir(szDirectory);
	AssertTrue(cFileUtil.TouchDir(szDirectory));

	WriteObjectReaderSimpleFile();

	CObjectReaderSimpleDisk		cReader;
	CExternalObjectDeserialiser	cGraphDeserialiser;
	CPointer					cBase;

	Ptr<CTestNamedString>		cNS1;
	Ptr<CTestNamedString>		cNS2;
	CPointer					cTemp;

	CCodabase*					pcDatabase;
	CSequence*					pcSequence;

	pcSequence = CSequenceFactory::Create(szDirectory);
	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_Yes);
	pcDatabase->Open();
	ObjectsInit(pcDatabase, pcSequence);

	gcObjects.AddConstructor<CTestNamedString>();

	AssertLong(0, pcDatabase->NumIndices());
	AssertLong(0, gcObjects.NumMemoryIndexes());

	cReader.Init("Output" _FS_ "ObjectReaderSimple" _FS_ "Test" _FS_);
	cGraphDeserialiser.Init(&cReader, false, &gcObjects, gcObjects.GetMemory());
	cBase = cGraphDeserialiser.Read("Waggy");
	AssertTrue(cBase.IsNotNull());
	AssertString("CTestNamedString", cBase->ClassName());
	AssertString("Waggy", cBase.GetName());
	AssertString("NS1",  ((CTestNamedString*)&cBase)->mszEmbedded.Text());

	AssertLong(0, pcDatabase->NumIndices());
	AssertLong(2, gcObjects.NumMemoryIndexes());

	cNS1 = gcObjects.Get("Waggy");
	AssertTrue(cNS1.IsNotNull());
	AssertString("NS1", cNS1->mszEmbedded.Text());

	cNS2 = gcObjects.Get("Dog");
	AssertTrue(cNS2.IsNotNull());
	AssertString("NS2", cNS2->mszEmbedded.Text());

	AssertPointer(&cNS1, &cBase);

	AssertPointer(&cNS2, &cNS1->mpAnother);
	AssertPointer(NULL, &cNS2->mpAnother);

	cGraphDeserialiser.Kill();
	cReader.Kill();

	ObjectsFlush();
	pcDatabase->Close();
	SafeKill(pcDatabase);
	SafeKill(pcSequence);
	ObjectsKill();

	cFileUtil.RemoveDir(szDirectory);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectReaderSimple(void)
{
	BeginTests();
	MemoryInit();
	FastFunctionsInit();
	TypesInit();
	DataIOInit();

	TestObjectReaderSimpleDeserialised();

	DataIOKill();
	TypesKill();
	FastFunctionsKill();
	MemoryKill();
	TestStatistics();
}

