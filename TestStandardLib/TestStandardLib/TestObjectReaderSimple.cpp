#include "BaseLib/GlobalMemory.h"
#include "BaseLib/FileUtil.h"
#include "CoreLib/Codabase.h"
#include "CoreLib/CodabaseFactory.h"
#include "CoreLib/SequenceFactory.h"
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

	cNS2 = ONMalloc<CTestNamedString>("Dog", ONull, ONull, "NS2");
	cNS1 = ONMalloc<CTestNamedString>("Waggy", ONull, cNS2, "NS1");


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
	CObjectWriterSimple		cWriter;
	CObjectGraphSerialiser	cGraphSerialiser;

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
	CObjectGraphDeserialiser	cGraphDeserialiser;
	CPointer					cBase;

	Ptr<CTestNamedString>		cNS1;
	Ptr<CTestNamedString>		cNS2;
	CPointer					cTemp;

	CObjectAllocator			cAllocator;
	CDependentReadObjects		cDependentReadObjects;
	CCodabase*					pcDatabase;
	CSequence*					pcSequence;

	pcSequence = CSequenceFactory::Create(szDirectory);
	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_Yes);
	pcDatabase->Open();
	ObjectsInit(pcDatabase, pcSequence);

	gcObjects.AddConstructor<CTestNamedString>();

	AssertLongLongInt(0, pcDatabase->NumIndices());
	AssertLongLongInt(0, gcObjects.NumMemoryIndexes());

	cAllocator.Init(&gcObjects);
	cDependentReadObjects.Init();
	cReader.Init("Output" _FS_ "ObjectReaderSimple" _FS_ "Test" _FS_);
	cGraphDeserialiser.Init(&cReader, FALSE, &cAllocator, &cDependentReadObjects, gcObjects.GetMemory());
	cBase = cGraphDeserialiser.Read("Waggy");

	AssertLongLongInt(0, pcDatabase->NumIndices());
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

	TestObjectReaderSimpleDeserialised();

	MemoryKill();
	TestStatistics();
}

