#include "BaseLib/GlobalMemory.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/TypeNames.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/MemoryFile.h"
#include "CoreLib/Codabase.h"
#include "CoreLib/CodabaseFactory.h"
#include "CoreLib/SequenceFactory.h"
#include "StandardLib/Objects.h"
#include "StandardLib/ObjectConverterText.h"
#include "StandardLib/ObjectConverterNative.h"
#include "StandardLib/String.h"
#include "StandardLib/ChunkFileObjectWriter.h"
#include "StandardLib/ObjectGraphSerialiser.h"
#include "TestLib/Assert.h"
#include "ChunkFileObjectWriterTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void SetupDehollowficationConstructors(void)
{
	gcObjects.AddConstructor<CTestWithArray>();
	gcObjects.AddConstructor<CTestInteger>();
	gcObjects.AddConstructor<CTestNamedString>();
	gcObjects.AddConstructor<CTestDoubleNamedString>();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
Ptr<CTestDoubleNamedString> SetupDehollowficationScene(void)
{
	Ptr<CTestNamedString>			cNS1;
	Ptr<CTestNamedString>			cNS2;
	Ptr<CTestNamedString>			cDiamond;
	Ptr<CTestDoubleNamedString>	cDouble;
	Ptr<CString>					sz1;
	Ptr<CString>					sz3;
	Ptr<CString>					sz2;
	Ptr<CString>					sz4;
	Ptr<CRoot>						cRoot;
	Ptr<CTestNamedString>			cNS3;

	cRoot = ORoot();

	sz3 = OMalloc<CString>("End");

	cDiamond = ONMalloc<CTestNamedString>("Diamond End", sz3, Null(), "Before Swine");
	sz1 = OMalloc<CString>("World");

	cNS1 = ONMalloc<CTestNamedString>("NamedString 1", sz1, cDiamond, "Hello");

	sz2 = OMalloc<CString>("6789");
	cNS2 = ONMalloc<CTestNamedString>("NamedString 2", sz2, cDiamond, "12345");

	sz4 = OMalloc<CString>("Start");
	cDouble = ONMalloc<CTestDoubleNamedString>("Double Start", sz4, cNS1, Null());

	cRoot->Add(cDouble);

	cDouble->mpSplit1 = cNS2;

	cNS3 = ONMalloc<CTestNamedString>("NamedString 3", sz1, Null(), "Random");

	cRoot->Add(cNS3);

//
//      sz3
//       |
//    cDiamond
//      / \
// sz2 /   \  sz1
//  | /     \  |
//  cNS2    cNS1
//    \     /
//     \   / sz4
//      \ /  /
//    cDouble   sz1 
//       \       |
//        \    cNS3
//         \   /
//          \ /
//          Set
//           |
//         cRoot
//       

	return cDouble;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void WriteDehollowficationChunkedFile(void)
{
	Ptr<CTestDoubleNamedString>	cDouble;
	CChunkFileObjectWriter		cWriter;
	CObjectGraphSerialiser		cGraphSerialiser;

	cDouble = SetupDehollowficationScene();

	cWriter.Init("Output" _FS_ "Dehollowfication" _FS_ "ChunkFile", "", "Double");
	cGraphSerialiser.Init(&cWriter);
	AssertTrue(cGraphSerialiser.Write(&cDouble));
	cGraphSerialiser.Kill();
	cWriter.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDehollowficationFromDatabase(void)
{
	CFileUtil							cFileUtil;
	CCodabase*							pcDatabase;
	CSequence*							pcSequence;
	char								szDirectory[] = "Output" _FS_ "Dehollowfication" _FS_ "Database1";

	cFileUtil.RemoveDir(szDirectory);

	pcSequence = CSequenceFactory::Create(szDirectory);
	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase, pcSequence);
	
	SetupDehollowficationScene();
	
	ObjectsFlush();
	pcDatabase->Close();
	SafeKill(pcDatabase);
	SafeKill(pcSequence);
	ObjectsKill();

	pcSequence = CSequenceFactory::Create(szDirectory);
	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase, pcSequence);
	SetupDehollowficationConstructors();
	AssertLongLongInt(0, gcUnknowns.NumElements());
	AssertInt(0, gcObjects.GetStackPointers()->UsedPointers());

	AssertLongLongInt(0, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(0, gcObjects.NumMemoryNames());
	AssertLongLongInt(0, pcDatabase->NumIndicesCached());
	AssertLongLongInt(11, pcDatabase->NumIndices());
	AssertLongLongInt(6, pcDatabase->NumNames());
	Pass();

	ObjectsFlush();
	pcDatabase->Close();
	SafeKill(pcDatabase);
	SafeKill(pcSequence);
	ObjectsKill();

	pcSequence = CSequenceFactory::Create(szDirectory);
	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase, pcSequence);

	Ptr<CRoot> pRoot = ORoot();

	AssertTrue(pRoot->IsSetHollow());
	Pass();

	AssertLongLongInt(2, gcUnknowns.NumElements());
	AssertLongLongInt(2, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(1, gcObjects.NumMemoryNames());
	AssertLongLongInt(1, pcDatabase->NumIndicesCached());
	AssertLongLongInt(6, pcDatabase->NumNames());
	AssertInt(1, gcObjects.GetStackPointers()->UsedPointers());
	Pass();

	Ptr<CTestDoubleNamedString> pTest = pRoot->Get<CTestDoubleNamedString>("Double Start");  //This will cause pRoot.Set to be dehollowed.
	AssertInt(2, gcObjects.GetStackPointers()->UsedPointers());
	AssertFalse(pRoot->IsSetHollow());
	AssertTrue(pTest.IsNotNull());
	AssertTrue(pTest.IsHollow());
	AssertLongLongInt(10, pTest.GetIndex());
	AssertLongLongInt(4, gcUnknowns.NumElements());
	AssertLongLongInt(4, gcObjects.NumMemoryIndexes());
	Pass();

	AssertString("12345", pTest->mpSplit1->mszEmbedded.Text()); //This will cause pTest and pTest.Split1 to be dehollowed.
	AssertLongLongInt(9, gcUnknowns.NumElements());
	AssertLongLongInt(9, gcObjects.NumMemoryIndexes());
	AssertFalse(pTest.IsHollow());
	AssertLongLongInt(10, pTest.GetIndex());
	AssertInt(2, gcObjects.GetStackPointers()->UsedPointers());
	AssertTrue(pTest->mpSplit1->mpAnother.IsHollow());
	AssertTrue(pTest->mpSplit2.IsHollow());
	AssertTrue(pTest->mpSplit1->mszString.IsHollow());
	AssertString("Diamond End", pTest->mpSplit1->mpAnother.GetName());
	AssertString("6789", pTest->mpSplit1->mszString->Text());
	AssertFalse(pTest->mpSplit1->mszString.IsHollow());
	Pass();

	AssertInt(2, gcObjects.GetStackPointers()->UsedPointers());
	Pass();

	Ptr<CTestNamedString> pDiamond = pTest->mpSplit1->mpAnother;
	AssertLongLongInt(9, gcUnknowns.NumElements());
	AssertLongLongInt(9, gcObjects.NumMemoryIndexes());
	AssertInt(3, gcObjects.GetStackPointers()->UsedPointers());
	AssertTrue(pTest->mpSplit1->mpAnother.IsHollow());
	AssertTrue(pDiamond.IsHollow());
	Pass();

	pDiamond->ClassName(); //This will cause pDiamond to be de-hollowed

	AssertFalse(pDiamond.IsHollow());
	AssertFalse(pTest->mpSplit1->mpAnother.IsHollow());
	Pass();

	AssertLongLongInt(10, gcUnknowns.NumElements());
	AssertLongLongInt(10, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(6, gcObjects.NumMemoryNames());
	AssertLongLongInt(6, pcDatabase->NumNames());
	Pass();

	AssertTrue(pTest->mpSplit2.IsHollow());
	pTest->mpSplit2->ClassSize();
	AssertFalse(pTest->mpSplit2.IsHollow());
	AssertFalse(pTest->mpSplit2->mpAnother.IsHollow());
	AssertPointer(pDiamond.Object(), pTest->mpSplit2->mpAnother.Object());
	Pass();

	AssertLongLongInt(11, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(6, gcObjects.NumMemoryNames());
	AssertLongLongInt(6, pcDatabase->NumNames());
	Pass();

	Ptr<CTestNamedString> pRandom = pRoot->Get<CTestNamedString>("NamedString 3");
	AssertTrue(pRandom.IsNotNull());
	AssertTrue(pRandom.IsHollow());
	Pass();

	AssertTrue(pRandom->mszString.IsHollow());
	AssertFalse(pRandom.IsHollow());
	AssertTrue(pTest->mpSplit2->mszString.IsHollow());
	Pass();

	AssertString("World", pRandom->mszString->Text());
	AssertFalse(pRandom->mszString.IsHollow());
	AssertFalse(pTest->mpSplit2->mszString.IsHollow());
	AssertPointer(pRandom->mszString.Object(), pTest->mpSplit2->mszString.Object());
	Pass();

	AssertLongLongInt(11, pcDatabase->NumIndices());
	Pass();

	ObjectsFlush();
	pcDatabase->Close();
	SafeKill(pcDatabase);
	SafeKill(pcSequence);
	ObjectsKill();

	AssertTrue(pRoot.IsNull());
	AssertTrue(pTest.IsNull());
	AssertTrue(pDiamond.IsNull());
	AssertTrue(pRandom.IsNull());
	Pass();

	pDiamond.UnsafeClearObject();
	
	cFileUtil.RemoveDir(szDirectory);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDehollowficationFromDatabaseOfTwoPointers(void)
{
	CFileUtil							cFileUtil;
	CCodabase*							pcDatabase;
	CSequence*							pcSequence;
	CIndexTreeEvictionStrategyRandom	cEvictionStrategy;
	char								szDirectory[] = "Output" _FS_ "Dehollowfication" _FS_ "Database2";

	cFileUtil.RemoveDir(szDirectory);

	pcSequence = CSequenceFactory::Create(szDirectory);
	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase, pcSequence);

	SetupDehollowficationScene();

	ObjectsFlush();
	pcDatabase->Close();
	SafeKill(pcDatabase);
	SafeKill(pcSequence);
	ObjectsKill();

	pcSequence = CSequenceFactory::Create(szDirectory);
	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase, pcSequence);
	SetupDehollowficationConstructors();

	Ptr<CRoot> pRoot = ORoot();
	Ptr<CTestDoubleNamedString> pDouble = pRoot->Get<CTestDoubleNamedString>("Double Start");

	Ptr<CTestNamedString> pString1 = pDouble->mpSplit1;
	Ptr<CTestNamedString> pString2 = pDouble->mpSplit2;
	pString1->ClassName();
	pString2->ClassName();

	Ptr<CTestNamedString> pDiamond1 = pString1->mpAnother;
	Ptr<CTestNamedString> pDiamond2 = pString2->mpAnother;

	AssertTrue(pDiamond1.IsHollow());
	AssertTrue(pDiamond2.IsHollow());
	AssertPointer(pDiamond1.Object(), pDiamond2.Object());
	AssertPointer(pString1->mpAnother.Object(), pString2->mpAnother.Object());
	AssertLongLongInt(3LL, pDiamond1.GetIndex());
	AssertLongLongInt(3LL, pDiamond2.GetIndex());

	//Dehollofication of pDiamond1 happens here. pString1->mpAnother and pString2->mpAnother are remapped to the dehollowed diamond object.
	pDiamond1->ClassName();

	AssertFalse(pDiamond1.IsHollow());
	AssertFalse(pDiamond2.IsHollow());  //This should be false but it's not until I remap local pointers.
	AssertPointer(pDiamond1.Object(), pDiamond2.Object());  //These should be the same but they're not until I remap local pointers.
	AssertLongLongInt(3LL, pDiamond1.GetIndex());

	AssertFalse(pString1->mpAnother.IsHollow());
	AssertFalse(pString2->mpAnother.IsHollow());
	AssertPointer(pString1->mpAnother.Object(), pString2->mpAnother.Object());

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
void TestDehollowficationFromChunkFileSource(void)
{
	CFileUtil		cFileUtil;
	CCodabase*		pcDatabase;
	CSequence*		pcSequence;
	char			szDirectory[] = "Output" _FS_ "Dehollowfication" _FS_ "Temp";

	cFileUtil.RemoveDir(szDirectory);

	pcSequence = CSequenceFactory::Create(szDirectory);
	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase, pcSequence);

	WriteDehollowficationChunkedFile();

	ObjectsFlush();
	pcDatabase->Close();
	SafeKill(pcDatabase);
	SafeKill(pcSequence);
	ObjectsKill();
	cFileUtil.RemoveDir(szDirectory);

	CObjectSourceChunked* pcObjectSourceChunked;


	CDiskFile*	pcDiskFile = DiskFile("Output" _FS_ "Dehollowfication" _FS_ "ChunkFile" _FS_ "Double.DRG");

	pcSequence = CSequenceFactory::Create(szDirectory);
	pcDatabase = CCodabaseFactory::Create("Output" _FS_ "Dehollowfication" _FS_ "Temp", IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase, pcSequence);
	SetupDehollowficationConstructors();

	pcObjectSourceChunked = (CObjectSourceChunked*)gcObjects.AddSource<CObjectConverterNative>(pcDiskFile, "Double");  //Note the .DRG is intentionally dropped.
	AssertNotNull(pcObjectSourceChunked);

	AssertInt(4, pcObjectSourceChunked->NumNames());
	AssertString("Diamond End", pcObjectSourceChunked->GetName(0));
	AssertString("Double Start", pcObjectSourceChunked->GetName(1));
	AssertString("NamedString 1", pcObjectSourceChunked->GetName(2));
	AssertString("NamedString 2", pcObjectSourceChunked->GetName(3));

	Ptr<CTestDoubleNamedString> pStart;

	pStart = gcObjects.Get("Double Start");
	AssertTrue(pStart.IsNotNull());
	AssertString("CTestDoubleNamedString", pStart.ClassName());

	AssertTrue(pStart->mpSplit1.IsHollow());
	AssertTrue(pStart->mpSplit2.IsHollow());
	AssertFalse(pStart->mszString.IsHollow());

	pStart->mpSplit1->ClassName();
	AssertFalse(pStart->mpSplit1.IsHollow());
	AssertString("CTestNamedString", pStart->mpSplit1.ClassName());

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
void TestDehollowfication(void)
{
	BeginTests();
	MemoryInit();
	FastFunctionsInit();
	TypesInit();
	DataIOInit();

	TestDehollowficationFromDatabase();
	TestDehollowficationFromDatabaseOfTwoPointers();
	TestDehollowficationFromChunkFileSource();

	DataIOKill();
	TypesKill();
	FastFunctionsKill();
	MemoryKill();
	TestStatistics();
}

