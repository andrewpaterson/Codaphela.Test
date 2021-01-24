#include "BaseLib/FileUtil.h"
#include "CoreLib/Codabase.h"
#include "CoreLib/CodabaseFactory.h"
#include "StandardLib/Objects.h"
#include "StandardLib/ObjectGraphDeserialiser.h"
#include "StandardLib/ObjectGraphSerialiser.h"
#include "StandardLib/ObjectWriterSimple.h"
#include "StandardLib/ObjectReaderSimpleDisk.h"
#include "StandardLib/ObjectWriterChunked.h"
#include "StandardLib/ObjectReaderChunkFileDisk.h"
#include "StandardLib/ObjectAllocator.h"
#include "StandardLib/Root.h"
#include "TestLib/Assert.h"
#include "ObjectWriterChunkedTestClasses.h"
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
	gcObjects.AddConstructor<CString>();
	gcObjects.AddConstructor<CArrayObject>();
	gcObjects.AddConstructor<CSetObject>();
	gcObjects.AddConstructor<CRoot>();
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
	cStart1 = ONMalloc(CTestSaveableObject2, "Ow/Start 1")->Init("Battery");
	cStart2 = ONMalloc(CTestSaveableObject2, "Ow/Start 2")->Init("Charger");
	cShared = ONMalloc(CTestSaveableObject1, "Ow/Shared")->Init();
	cString1 = OMalloc(CString)->Init("Black");
	cString2 = OMalloc(CString)->Init("Jack");
	cIgnored = OMalloc(CTestInteger)->Init(0, 1, 0);
	
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
void TestRemappingOfOIs(CObjectWriter* pcWriter, CObjectReader* pcReader)
{
	CFileUtil					cFileUtil;
	Ptr<CTestSaveableObject2>	cBase;
	Ptr<CTestSaveableObject2>	cStart1;
	Ptr<CRoot>					cRoot;
	Ptr<CString>				szOne;
	Ptr<CString>				cString1;
	Ptr<CString>				cString2;
	CObjectGraphSerialiser		cGraphSerialiser;
	CObjectGraphDeserialiser	cGraphDeserialiser;
	Ptr<CTestSaveableObject1>	cShared;
	int							i;
	CObjectAllocator			cAllocator;
	CDependentReadObjects		cDependentReadObjects;
	CCodabase*					pcDatabase;
	char						szDirectory[] = "Output" _FS_ "GraphDeserialiser" _FS_ "Simple" _FS_ "Remapping";

	cFileUtil.MakeDir(szDirectory);

	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase);

	TestObjectGraphDeserialiserAddConstructors();
	TestObjectGraphDeserialiserBuildGraph1();

	cBase = gcObjects.Get("Ow/Start 1");
	AssertTrue(cBase.IsNotNull());
	AssertLongLongInt(3, cBase->GetOI());
	cString1 = gcObjects.Get(6LL);
	AssertString("Black", cString1->Text());
	AssertLongLongInt(6LL, cString1->GetOI());
	cString2 = gcObjects.Get(7LL);
	AssertString("Jack", cString2->Text());
	AssertLongLongInt(7LL, cString2->GetOI());

	cGraphSerialiser.Init(pcWriter);
	AssertTrue(cGraphSerialiser.Write(&cBase));
	cGraphSerialiser.Kill();
	pcWriter->Kill();

	pcDatabase->Close();
	SafeKill(pcDatabase);
	ObjectsKill();


	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase);
	TestObjectGraphDeserialiserAddConstructors();

	cRoot = ORoot();

	for (i = 0; i < 20; i++)
	{
		szOne = OMalloc(CString);
		szOne->Init("Hello World ");
		szOne->Append(i);
		cRoot->Add(szOne);
		AssertLongLongInt(3+i, szOne->GetOI());
	}

	cAllocator.Init(&gcObjects);
	cDependentReadObjects.Init();
	cGraphDeserialiser.Init(pcReader, FALSE, &cAllocator, &cDependentReadObjects, gcObjects.GetMemory());
	cStart1 = cGraphDeserialiser.Read("Ow/Start 1");
	AssertTrue(cStart1.IsNotNull());
	AssertLongLongInt(23, cStart1->GetOI());

	AssertTrue(cStart1->mp1.IsNotNull());
	AssertString("CTestSaveableObject1", cStart1->mp1->ClassName());
	cShared = cStart1->mp1;
	AssertLongLongInt(25, cShared->GetOI());

	AssertTrue(cStart1->mp2.IsNotNull());
	AssertString("CString", cStart1->mp2->ClassName());
	cString1 = cStart1->mp2;
	AssertLongLongInt(24, cString1->GetOI());
	cGraphDeserialiser.Kill();
	cDependentReadObjects.Kill();
	cAllocator.Kill();

	for (i = 0; i < 20; i++)
	{
		szOne = OMalloc(CString);
		szOne->Init("Hello World ");
		szOne->Append(i + 20);
		cRoot->Add(szOne);
		AssertLongLongInt(26+i, szOne->GetOI());
	}

	pcReader->Kill();

	pcDatabase->Close();
	SafeKill(pcDatabase);
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestRemappingOfSimpleFilesOIs(void)
{
	CObjectWriterSimple			cWriter;
	CObjectReaderSimpleDisk		cReader;

	cWriter.Init("Output" _FS_ "GraphDeserialiser" _FS_ "Simple" _FS_ "Remapping", "");
	cReader.Init("Output" _FS_ "GraphDeserialiser" _FS_ "Simple" _FS_ "Remapping");

	TestRemappingOfOIs(&cWriter, &cReader);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestRemappingOfChunkedFilesOIs(void)
{
	CObjectWriterChunked		cWriter;
	CObjectReaderChunkFileDisk	cReader;

	cWriter.Init("Output" _FS_ "GraphDeserialiser" _FS_ "Simple" _FS_ "Remapping", "", "GraphFile");
	cReader.Init("Output" _FS_ "GraphDeserialiser" _FS_ "Simple" _FS_ "Remapping", "GraphFile");

	TestRemappingOfOIs(&cWriter, &cReader);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestOverwritingOfExistingNamesFromChunkedFiles(void)
{
	CObjectWriterChunked			cWriterStart1;
	CObjectWriterChunked			cWriterStart2;
	CFileUtil						cFileUtil;
	Ptr<CTestSaveableObject2>		cOwStart1;
	Ptr<CTestSaveableObject2>		cOwStart2;
	CObjectGraphSerialiser			cGraphSerialiser;
	CObjectGraphDeserialiser		cGraphDeserialiser;
	CObjectReaderChunkFileDisk		cReaderStart1;
	CObjectReaderChunkFileDisk		cReaderStart2;
	Ptr<CTestSaveableObject1>		cShared;
	Ptr<CRoot>						cRoot;
	CPointer						cObject;
	int								iNumUnknowns;
	int								iNumIndexes;
	int								iNumNames;
	CObjectAllocator				cAllocator;
	CDependentReadObjects			cDependentReadObjects;
	CCodabase*						pcDatabase;
	char							szDirectory[] = "Output" _FS_ "GraphDeserialiser" _FS_ "Simple" _FS_ "Remapping";

	cWriterStart1.Init(szDirectory, "", "Start1");
	cWriterStart2.Init(szDirectory, "", "Start2");

	cFileUtil.MakeDir(szDirectory);

	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase);

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

	pcDatabase->Close();
	SafeKill(pcDatabase);
	ObjectsKill();


	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase);

	TestObjectGraphDeserialiserAddConstructors();
	cRoot = ORoot();

	cAllocator.Init(&gcObjects);
	cDependentReadObjects.Init();
	cReaderStart1.Init("Output" _FS_ "GraphDeserialiser" _FS_ "Simple" _FS_ "Remapping", "Start1");
	cGraphDeserialiser.Init(&cReaderStart1, FALSE, &cAllocator, &cDependentReadObjects, gcObjects.GetMemory());
	cOwStart1 = cGraphDeserialiser.Read("Ow/Start 1");
	cGraphDeserialiser.Kill();
	cDependentReadObjects.Kill();
	cAllocator.Kill();
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

	cAllocator.Init(&gcObjects);
	cDependentReadObjects.Init();
	cReaderStart2.Init("Output" _FS_ "GraphDeserialiser" _FS_ "Simple" _FS_ "Remapping", "Start2");
	cGraphDeserialiser.Init(&cReaderStart2, FALSE, &cAllocator, &cDependentReadObjects, gcObjects.GetMemory());
	cOwStart2 = cGraphDeserialiser.Read("Ow/Start 2");
	cGraphDeserialiser.Kill();
	cDependentReadObjects.Kill();
	cAllocator.Kill();
	cReaderStart2.Kill();

	AssertInt(iNumUnknowns+2, gcUnknowns.NumElements());
	AssertInt(iNumIndexes+2, (int)gcObjects.NumMemoryIndexes());
	AssertInt(iNumNames+1, (int)gcObjects.NumMemoryNames());

	AssertNotNull(cOwStart2.Object());
	cRoot->Add(cOwStart2);

	AssertNotNull(&cOwStart2);
	AssertInt(89, cOwStart2->mp1->miInt);
	AssertLongLongInt(cOwStart1->mp1->GetOI(), cOwStart2->mp1->GetOI());
	AssertInt(89, cOwStart1->mp1->miInt);
	AssertPointer(&cOwStart1->mp1, &cOwStart2->mp1);

	cObject = gcObjects.Get("Ow/Start 2");
	AssertPointer(&cOwStart2, &cObject);

	cObject = gcObjects.Get(cOwStart2->GetOI());
	AssertPointer(&cOwStart2, &cObject);

	pcDatabase->Close();
	SafeKill(pcDatabase);
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectGraphDeserialiser(void)
{
	CFileUtil	cFileUtil;

	cFileUtil.RemoveDir("Output");

	BeginTests();

	TestRemappingOfSimpleFilesOIs();
	TestRemappingOfChunkedFilesOIs();
	TestOverwritingOfExistingNamesFromChunkedFiles();

	TestStatistics();

	cFileUtil.RemoveDir("Output");
}

