#include "BaseLib/FileUtil.h"
#include "BaseLib/GlobalMemory.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/TypeNames.h"
#include "BaseLib/Codabase.h"
#include "BaseLib/CodabaseFactory.h"
#include "BaseLib/SequenceFactory.h"
#include "StandardLib/Objects.h"
#include "StandardLib/ExternalObjectDeserialiser.h"
#include "StandardLib/ExternalObjectSerialiser.h"
#include "StandardLib/MultiFileObjectWriter.h"
#include "StandardLib/ObjectReaderSimpleDisk.h"
#include "StandardLib/ChunkFileObjectWriter.h"
#include "StandardLib/ChunkFileSystemObjectReader.h"
#include "StandardLib/Root.h"
#include "TestLib/Assert.h"
#include "ChunkFileObjectWriterTestClasses.h"
#include "ObjectTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectGraphDeserialiserAddConstructors(void)
{
	gcObjects.AddConstructor<CTestWithArray>();
	gcObjects.AddConstructor<CTestInteger>();
	gcObjects.AddConstructor<CTestNamedString>();
	gcObjects.AddConstructor<CTestDoubleNamedString>();
	gcObjects.AddConstructor<CTestSaveableObject1>();
	gcObjects.AddConstructor<CTestSaveableObject2>();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectGraphDeserialiserBuildGraph1(void)
{
	Ptr<CTestSaveableObject2>	cStart1;
	Ptr<CTestSaveableObject2>	cStart2;
	Ptr<CRoot>					cRoot;
	Ptr<CTestSaveableObject1>	cShared;
	Ptr<CString>				cString1;
	Ptr<CString>				cString2;
	Ptr<CTestInteger>			cIgnored;

	cRoot = ORoot();
	cStart1 = ONMalloc<CTestSaveableObject2>("Ow/Start 1", "Battery");
	cStart2 = ONMalloc<CTestSaveableObject2>("Ow/Start 2", "Charger");
	cShared = ONMalloc<CTestSaveableObject1>("Ow/Shared");
	cString1 = OMalloc<CString>("Black");
	cString2 = OMalloc<CString>("Jack");
	cIgnored = OMalloc<CTestInteger>(0, 1, 0);
	
	cRoot->Add(cStart1);
	cRoot->Add(cStart2);

	cStart1->mp1 = cShared;
	cStart2->mp1 = cShared;

	cShared->miInt = 89;
	cShared->mpObject = cShared;

	cStart1->mp2 = cString1;
	cStart2->mp2 = cString2;

	cRoot->Add(cIgnored);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestRemappingOfOIs(CExternalObjectWriter* pcWriter, CExternalObjectReader* pcReader)
{
	Ptr<CTestSaveableObject2>		cBase;
	Ptr<CTestSaveableObject2>		cStart1;
	Ptr<CRoot>						cRoot;
	Ptr<CString>					szOne;
	Ptr<CString>					cString1;
	Ptr<CString>					cString2;
	CExternalObjectSerialiser		cGraphSerialiser;
	Ptr<CTestSaveableObject1>		cShared;
	int								i;
	CExternalObjectDeserialiser		cGraphDeserialiser;
	CCodabase*						pcDatabase;
	CSequence*						pcSequence;
	char							szDirectory[] = "Output" _FS_ "GraphDeserialiser" _FS_ "Simple" _FS_ "Remapping";

	pcSequence = CSequenceFactory::Create(szDirectory);
	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase, pcSequence);

	TestObjectGraphDeserialiserAddConstructors();
	TestObjectGraphDeserialiserBuildGraph1();

	cBase = gcObjects.Get("Ow/Start 1");
	AssertTrue(cBase.IsNotNull());
	AssertLongLongInt(3, cBase->GetIndex());
	AssertString("Ow/Start 1", cBase.GetName());
	cString1 = gcObjects.Get(6LL);
	AssertString("Black", cString1->Text());
	AssertLongLongInt(6LL, cString1->GetIndex());
	cString2 = gcObjects.Get(7LL);
	AssertString("Jack", cString2->Text());
	AssertLongLongInt(7LL, cString2->GetIndex());

	cGraphSerialiser.Init(pcWriter);
	AssertTrue(cGraphSerialiser.Write(&cBase));
	cGraphSerialiser.Kill();
	pcWriter->Kill();

	AssertLongLongInt(9LL, pcSequence->PeekNext());

	gcObjects.Flush();

	pcDatabase->Close();
	SafeKill(pcDatabase);
	SafeKill(pcSequence);
	ObjectsKill();


	pcSequence = CSequenceFactory::Create(szDirectory);
	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase, pcSequence);
	TestObjectGraphDeserialiserAddConstructors();

	cRoot = ORoot();

	for (i = 0; i < 20; i++)
	{
		szOne = OMalloc<CString>("Hello World ");
		szOne->Append(i);
		cRoot->Add(szOne);
		AssertLongLongInt(9LL + i, szOne->GetIndex());
	}
	
	cGraphDeserialiser.Init(pcReader, false, &gcObjects, gcObjects.GetMemory());
	cStart1 = cGraphDeserialiser.Read("Ow/Start 1");
	AssertTrue(cStart1.IsNotNull());
	AssertLongLongInt(29, cStart1->GetIndex());


	AssertTrue(cStart1->mp1.IsNotNull());
	AssertString("CTestSaveableObject1", cStart1->mp1->ClassName());
	cShared = cStart1->mp1;
	AssertLongLongInt(31, cShared->GetIndex());

	AssertTrue(cStart1->mp2.IsNotNull());
	AssertString("CString", cStart1->mp2->ClassName());
	cString1 = cStart1->mp2;
	AssertLongLongInt(30, cString1->GetIndex());

	cGraphDeserialiser.Kill();

	for (i = 0; i < 20; i++)
	{
		szOne = OMalloc<CString>();
		szOne->Init("Hello World ");
		szOne->Append(i + 20);
		cRoot->Add(szOne);
		AssertLongLongInt(32LL + i, szOne->GetIndex());
	}

	pcDatabase->ValidateIdentifiers();

	pcReader->Kill();

	ObjectsFlush();
	pcDatabase->Close();
	SafeKill(pcDatabase);
	SafeKill(pcSequence);
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectGraphDeserialiserReuseName(void)
{
	CMultiFileObjectWriter			cWriter;
	CObjectReaderSimpleDisk			cReader;
	CFileUtil						cFileUtil;
	Ptr<CTestSaveableObject2>		cBase;
	Ptr<CTestSaveableObject2>		cStart1;
	Ptr<CRoot>						cRoot;
	CExternalObjectSerialiser		cGraphSerialiser;
	CExternalObjectDeserialiser		cGraphDeserialiser;
	Ptr<CTestSaveableObject1>		cShared;
	CCodabase*						pcDatabase;
	CSequence*						pcSequence;
	char							szDirectory[] = "Output" _FS_ "GraphDeserialiser" _FS_ "Reuse";

	AssertTrue(cFileUtil.RemoveDir("Output" _FS_ "GraphDeserialiser"));
	AssertTrue(cFileUtil.TouchDir("Output" _FS_ "GraphDeserialiser" _FS_ "Reuse"));

	cWriter.Init("Output" _FS_ "GraphDeserialiser" _FS_ "Reuse", "");
	cReader.Init("Output" _FS_ "GraphDeserialiser" _FS_ "Reuse");


	pcSequence = CSequenceFactory::Create(szDirectory);
	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase, pcSequence);

	TestObjectGraphDeserialiserAddConstructors();
	

	cRoot = ORoot();
	cStart1 = ONMalloc<CTestSaveableObject2>("Ow/Start 1", "Battery");
	AssertLongLongInt(3, cStart1->GetIndex());

	cRoot->Add(cStart1);

	cBase = gcObjects.Get("Ow/Start 1");
	AssertTrue(cBase.IsNotNull());
	AssertLongLongInt(3, cBase->GetIndex());
	AssertString("Ow/Start 1", cBase.GetName());

	cGraphSerialiser.Init(&cWriter);
	AssertTrue(cGraphSerialiser.Write(&cBase));
	cGraphSerialiser.Kill();
	cWriter.Kill();


	ObjectsFlush();
	pcDatabase->Close();
	SafeKill(pcDatabase);
	SafeKill(pcSequence);
	ObjectsKill();


	pcSequence = CSequenceFactory::Create(szDirectory);
	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase, pcSequence);
	TestObjectGraphDeserialiserAddConstructors();

	cBase = gcObjects.Get("Ow/Start 1");

	
	cGraphDeserialiser.Init(&cReader, false, &gcObjects, gcObjects.GetMemory());
	cStart1 = cGraphDeserialiser.Read("Ow/Start 1");
	AssertTrue(cStart1.IsNotNull());
	AssertLongLongInt(3, cStart1->GetIndex());  //Should this be 4?  I don't know.

	cGraphDeserialiser.Kill();

	pcDatabase->ValidateIdentifiers();

	ObjectsFlush();

	pcDatabase->ValidateIdentifiers();

	cReader.Kill();

	pcDatabase->Close();
	SafeKill(pcDatabase);
	SafeKill(pcSequence);
	ObjectsKill();

	cFileUtil.RemoveDir("Output" _FS_ "GraphDeserialiser");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectGraphDeserialiserRemappingOfSimpleFilesOIs(void)
{
	CMultiFileObjectWriter		cWriter;
	CObjectReaderSimpleDisk		cReader;
	CFileUtil					cFileUtil;

	AssertTrue(cFileUtil.RemoveDir("Output" _FS_ "GraphDeserialiser"));
	AssertTrue(cFileUtil.TouchDir("Output" _FS_ "GraphDeserialiser" _FS_ "Simple" _FS_ "Remapping"));

	cWriter.Init("Output" _FS_ "GraphDeserialiser" _FS_ "Simple" _FS_ "Remapping", "");
	cReader.Init("Output" _FS_ "GraphDeserialiser" _FS_ "Simple" _FS_ "Remapping");

	TestRemappingOfOIs(&cWriter, &cReader);

	cFileUtil.RemoveDir("Output" _FS_ "GraphDeserialiser");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectGraphDeserialiserRemappingOfChunkedFilesOIs(void)
{
	CChunkFileObjectWriter		cWriter;
	CChunkFileSystemObjectReader	cReader;
	CFileUtil					cFileUtil;

	AssertTrue(cFileUtil.RemoveDir("Output" _FS_ "GraphDeserialiser"));
	AssertTrue(cFileUtil.TouchDir("Output" _FS_ "GraphDeserialiser" _FS_ "Simple" _FS_ "Remapping"));

	cWriter.Init("Output" _FS_ "GraphDeserialiser" _FS_ "Simple" _FS_ "Remapping", "", "GraphFile");
	cReader.Init("Output" _FS_ "GraphDeserialiser" _FS_ "Simple" _FS_ "Remapping", "GraphFile");

	TestRemappingOfOIs(&cWriter, &cReader);

	cFileUtil.RemoveDir("Output" _FS_ "GraphDeserialiser");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectGraphDeserialiserOverwritingOfExistingNamesFromChunkedFiles(void)
{
	CChunkFileObjectWriter			cWriterStart1;
	CChunkFileObjectWriter			cWriterStart2;
	CFileUtil						cFileUtil;
	Ptr<CTestSaveableObject2>		cOwStart1;
	Ptr<CTestSaveableObject2>		cOwStart2;
	CExternalObjectSerialiser		cGraphSerialiser;
	CExternalObjectDeserialiser		cGraphDeserialiser;
	CChunkFileSystemObjectReader		cReaderStart1;
	CChunkFileSystemObjectReader		cReaderStart2;
	Ptr<CTestSaveableObject1>		cShared;
	Ptr<CRoot>						cRoot;
	CPointer						cObject;
	int								iNumUnknowns;
	int								iNumIndexes;
	int								iNumNames;
	CCodabase*						pcDatabase;
	CSequence*						pcSequence;
	char							szDirectory[] = "Output" _FS_ "GraphDeserialiser" _FS_ "Simple" _FS_ "Remapping";

	AssertTrue(cFileUtil.RemoveDir("Output" _FS_ "GraphDeserialiser"));
	AssertTrue(cFileUtil.TouchDir(szDirectory));


	cWriterStart1.Init(szDirectory, "", "Start1");
	cWriterStart2.Init(szDirectory, "", "Start2");

	pcSequence = CSequenceFactory::Create(szDirectory);
	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase, pcSequence);

	TestObjectGraphDeserialiserAddConstructors();
	TestObjectGraphDeserialiserBuildGraph1();

	cOwStart1 = gcObjects.Get("Ow/Start 1");
	cGraphSerialiser.Init(&cWriterStart1);
	AssertTrue(cGraphSerialiser.Write(&cOwStart1));
	cGraphSerialiser.Kill();
	cWriterStart1.Kill();

	cOwStart2 = gcObjects.Get("Ow/Start 2");
	cGraphSerialiser.Init(&cWriterStart2);
	AssertTrue(cGraphSerialiser.Write(&cOwStart2));
	cGraphSerialiser.Kill();
	cWriterStart2.Kill();

	cShared = gcObjects.Get("Ow/Shared");
	
	AssertInt(3, cShared->NumHeapFroms());
	AssertPointer(&cOwStart1, cShared->GetHeapFrom(0));
	AssertPointer(&cOwStart2, cShared->GetHeapFrom(1));
	AssertPointer(&cShared, cShared->GetHeapFrom(2));  //Remember: cShared->mpObject = cShared;
	AssertInt(2, cOwStart1->NumPointerTos());
	AssertPointer(&cShared, cOwStart1->TestGetPointerTo(0));
	AssertPointer(&cOwStart1->mp1, cOwStart1->TestGetPointerTo(0));
	AssertPointer(&cOwStart1->mp2, cOwStart1->TestGetPointerTo(1));
	AssertInt(2, cOwStart1->GetDistToRoot());
	AssertInt(3, cShared->GetDistToRoot());

	ObjectsFlush();
	pcDatabase->Close();
	SafeKill(pcDatabase);
	SafeKill(pcSequence);
	ObjectsKill();


	pcSequence = CSequenceFactory::Create(szDirectory);
	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase, pcSequence);

	TestObjectGraphDeserialiserAddConstructors();
	cRoot = ORoot();

	
	cReaderStart1.Init("Output" _FS_ "GraphDeserialiser" _FS_ "Simple" _FS_ "Remapping", "Start1");
	cGraphDeserialiser.Init(&cReaderStart1, false, &gcObjects, gcObjects.GetMemory());
	cOwStart1 = cGraphDeserialiser.Read("Ow/Start 1");
	cGraphDeserialiser.Kill();
	cReaderStart1.Kill();

	AssertInt(-1, cOwStart1->GetDistToRoot());
	
	cRoot->Add(cOwStart1);

	cShared = gcObjects.Get("Ow/Shared");

	//Make sure the pointed 'froms' are correctly setup after loading.
	AssertInt(2, cShared->NumHeapFroms());
	AssertPointer(&cOwStart1, cShared->GetHeapFrom(0));
	AssertPointer(&cShared, cShared->GetHeapFrom(1));
	AssertInt(2, cOwStart1->NumPointerTos());
	AssertPointer(&cShared, cOwStart1->TestGetPointerTo(0));
	AssertPointer(&cOwStart1->mp1, cOwStart1->TestGetPointerTo(0));
	AssertPointer(&cOwStart1->mp2, cOwStart1->TestGetPointerTo(1));
	AssertInt(2, cOwStart1->GetDistToRoot());
	AssertInt(3, cShared->GetDistToRoot());

	AssertInt(89, cOwStart1->mp1->miInt);
	cOwStart1->mp1->miInt = 66;

	iNumUnknowns = gcUnknowns.NumElements();
	iNumIndexes = (int)gcObjects.NumMemoryIndexes();
	iNumNames = gcObjects.NumMemoryNames();

	
	cReaderStart2.Init("Output" _FS_ "GraphDeserialiser" _FS_ "Simple" _FS_ "Remapping", "Start2");
	cGraphDeserialiser.Init(&cReaderStart2, false, &gcObjects, gcObjects.GetMemory());
	cOwStart2 = cGraphDeserialiser.Read("Ow/Start 2");
	cGraphDeserialiser.Kill();
	cReaderStart2.Kill();

	AssertInt(iNumUnknowns+1, gcUnknowns.NumElements());
	AssertInt(iNumIndexes+1, (int)gcObjects.NumMemoryIndexes());
	AssertInt(iNumNames, (int)gcObjects.NumMemoryNames());

	AssertNotNull(cOwStart2.Object());
	cRoot->Add(cOwStart2);

	AssertNotNull(&cOwStart2);
	AssertInt(89, cOwStart2->mp1->miInt);
	AssertLongLongInt(cOwStart1->mp1->GetIndex(), cOwStart2->mp1->GetIndex());
	AssertInt(89, cOwStart1->mp1->miInt);
	AssertPointer(&cOwStart1->mp1, &cOwStart2->mp1);

	cObject = gcObjects.Get("Ow/Start 2");
	AssertPointer(&cOwStart2, &cObject);

	cObject = gcObjects.Get(cOwStart2->GetIndex());
	AssertPointer(&cOwStart2, &cObject);

	ObjectsFlush();
	pcDatabase->Close();
	SafeKill(pcDatabase);
	SafeKill(pcSequence);
	ObjectsKill();

	AssertTrue(cFileUtil.RemoveDir("Output" _FS_ "GraphDeserialiser"));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectGraphDeserialiser(void)
{
	BeginTests();
	MemoryInit();
	FastFunctionsInit();
	TypesInit();
	DataIOInit();

	TestObjectGraphDeserialiserReuseName();
	TestObjectGraphDeserialiserRemappingOfSimpleFilesOIs();
	TestObjectGraphDeserialiserRemappingOfChunkedFilesOIs();
	TestObjectGraphDeserialiserOverwritingOfExistingNamesFromChunkedFiles();

	DataIOKill();
	TypesKill();
	FastFunctionsKill();
	MemoryKill();
	TestStatistics();
}

