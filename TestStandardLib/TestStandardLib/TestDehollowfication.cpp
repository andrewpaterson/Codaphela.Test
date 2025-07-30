#include "BaseLib/GlobalMemory.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/TypeNames.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/MemoryFile.h"
#include "BaseLib/Codabase.h"
#include "BaseLib/CodabaseFactory.h"
#include "BaseLib/SequenceFactory.h"
#include "StandardLib/Objects.h"
#include "StandardLib/ObjectConverterText.h"
#include "StandardLib/ObjectConverterNative.h"
#include "StandardLib/String.h"
#include "StandardLib/ChunkFileObjectWriter.h"
#include "StandardLib/ExternalObjectSerialiser.h"
#include "TestLib/Assert.h"
#include "ObjectTestClasses.h"
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
	Ptr<CTestDoubleNamedString>		cDouble;
	Ptr<CString>					sz1;
	Ptr<CString>					sz3;
	Ptr<CString>					sz2;
	Ptr<CString>					sz4;
	Ptr<CRoot>						cRoot;
	Ptr<CTestNamedString>			cNS3;

	cRoot = ORoot();

	sz3 = OMalloc<CString>("End");

	cDiamond = ONMalloc<CTestNamedString>("Diamond End", sz3, Null(), "Before Swine");  //cDiamond->mpAnother = sz3
	sz1 = OMalloc<CString>("World");

	cNS1 = ONMalloc<CTestNamedString>("NamedString 1", sz1, cDiamond, "Hello");		//cNS1->mpAnother = cDiamond

	sz2 = OMalloc<CString>("6789");
	cNS2 = ONMalloc<CTestNamedString>("NamedString 2", sz2, cDiamond, "12345");		//cNS2->mpAnother = cDiamond

	sz4 = OMalloc<CString>("Start");
	cDouble = ONMalloc<CTestDoubleNamedString>("Double Start", sz4, cNS1, Null());  //cDouble->szString = sz4
																					//cDouble->mpSplit2 = cNS1
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
	Ptr<CTestDoubleNamedString>		cDouble;
	CChunkFileObjectWriter			cWriter;
	CExternalObjectSerialiser		cGraphSerialiser;

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
void TestDehollowficationFromDatabaseSimple(void)
{
	Ptr<CString>				pString1;
	Ptr<CString>				pString2;
	Ptr<CString>				pString3;
	Ptr<CTestEmbeddedStrings>	pContainer;
	OIndex						oiContainer;
	CCodabase*					pcDatabase;
	CSequence*					pcSequence;
	CFileUtil					cFileUtil;
	Ptr<CRoot>					pRoot;
	char						szDirectory[] = "Output" _FS_ "Dehollowfication" _FS_ "Database3";

	cFileUtil.RemoveDir(szDirectory);


	pcSequence = CSequenceFactory::Create(szDirectory);
	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase, pcSequence);
	gcObjects.AddConstructor<CTestEmbeddedStrings>();

	pRoot = ORoot();
	pContainer = OMalloc<CTestEmbeddedStrings>();
	pRoot->Add(pContainer);

	oiContainer = pContainer->GetIndex();

	pContainer->mString1.Set("Goldberry is first");
	pContainer->mString2.Set("Jane is great");
	pContainer->mString3.Set("Baby Wooglers");

	ObjectsFlush();
	pcDatabase->Close();
	SafeKill(pcDatabase);
	SafeKill(pcSequence);
	ObjectsKill();

	pcSequence = CSequenceFactory::Create(szDirectory);
	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase, pcSequence);

	pContainer = gcObjects.Get(oiContainer);
	AssertTrue(pContainer.IsNotNull());

	pString1 = &pContainer->mString1;
	pString2 = &pContainer->mString2;
	pString3 = &pContainer->mString3;

	AssertString("Goldberry is first", pString1->Text());
	AssertString("Jane is great", pString2->Text());
	AssertString("Baby Wooglers", pString3->Text());

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
void TestDehollowficationFromDatabaseComplex(void)
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
	AssertLong(0, gcUnknowns.NumElements());
	AssertInt(0, gcObjects.GetStackPointers()->UsedPointers());

	AssertLong(0, gcObjects.NumMemoryIndexes());
	AssertLong(0, gcObjects.NumMemoryNames());
	AssertLong(0, pcDatabase->NumIndicesCached());
	AssertLong(11, pcDatabase->NumIndices());
	AssertLong(6, pcDatabase->NumNames());
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

	AssertLong(2, gcUnknowns.NumElements());
	AssertLong(2, gcObjects.NumMemoryIndexes());
	AssertLong(1, gcObjects.NumMemoryNames());
	AssertLong(1, pcDatabase->NumIndicesCached());
	AssertLong(6, pcDatabase->NumNames());
	AssertInt(1, gcObjects.GetStackPointers()->UsedPointers());
	Pass();

	Ptr<CTestDoubleNamedString> pDouble = pRoot->Get<CTestDoubleNamedString>("Double Start");  //This will cause pRoot.Set to be dehollowed.
	AssertInt(2, gcObjects.GetStackPointers()->UsedPointers());
	AssertFalse(pRoot->IsSetHollow());
	AssertTrue(pDouble.IsNotNull());
	AssertTrue(pDouble.IsHollow());
	AssertLong(10, pDouble.GetIndex());
	AssertLong(4, gcUnknowns.NumElements());
	AssertLong(3, gcObjects.NumMemoryIndexes());
	Pass();

	AssertString("12345", pDouble->mpSplit1->mszEmbedded.Text()); //This will cause pDouble and pDouble.Split1 to be dehollowed.
	AssertLong(9, gcUnknowns.NumElements());
	AssertLong(6, gcObjects.NumMemoryIndexes());
	AssertFalse(pDouble.IsHollow());
	AssertLong(10, pDouble.GetIndex());
	AssertInt(2, gcObjects.GetStackPointers()->UsedPointers());
	AssertTrue(pDouble->mpSplit1->mpAnother.IsHollow());
	AssertTrue(pDouble->mpSplit2.IsHollow());
	AssertTrue(pDouble->mpSplit1->mszString.IsHollow());
	AssertString("Diamond End", pDouble->mpSplit1->mpAnother.GetName());
	AssertString("6789", pDouble->mpSplit1->mszString->Text());
	AssertFalse(pDouble->mpSplit1->mszString.IsHollow());
	Pass();

	AssertInt(2, gcObjects.GetStackPointers()->UsedPointers());
	Pass();

	Ptr<CTestNamedString> pDiamond = pDouble->mpSplit1->mpAnother;
	AssertLong(9, gcUnknowns.NumElements());
	AssertLong(5, gcObjects.NumMemoryIndexes());
	AssertInt(3, gcObjects.GetStackPointers()->UsedPointers());
	AssertTrue(pDouble->mpSplit1->mpAnother.IsHollow());
	AssertTrue(pDiamond.IsHollow());
	Pass();

	pDiamond->ClassName(); //This will cause pDiamond to be de-hollowed

	AssertFalse(pDiamond.IsHollow());
	AssertFalse(pDouble->mpSplit1->mpAnother.IsHollow());
	Pass();

	AssertLong(10, gcUnknowns.NumElements());
	AssertLong(5, gcObjects.NumMemoryIndexes());
	AssertLong(3, gcObjects.NumMemoryNames());
	AssertLong(6, pcDatabase->NumNames());
	Pass();

	AssertTrue(pDouble->mpSplit2.IsHollow());
	pDouble->mpSplit2->ClassSize(); //This will cause mpSplit2 to be de-hollowed
	AssertFalse(pDouble->mpSplit2.IsHollow());
	AssertFalse(pDouble->mpSplit2->mpAnother.IsHollow());
	AssertPointer(pDiamond.Object(), pDouble->mpSplit2->mpAnother.Object());
	Pass();

	AssertLong(11, gcObjects.NumMemoryIndexes());
	AssertLong(6, gcObjects.NumMemoryNames());
	AssertLong(6, pcDatabase->NumNames());
	Pass();

	Ptr<CTestNamedString> pRandom = pRoot->Get<CTestNamedString>("NamedString 3");
	AssertTrue(pRandom.IsNotNull());
	AssertTrue(pRandom.IsHollow());
	Pass();

	AssertTrue(pRandom->mszString.IsHollow());
	AssertFalse(pRandom.IsHollow());
	AssertTrue(pDouble->mpSplit2->mszString.IsHollow());
	Pass();

	AssertString("World", pRandom->mszString->Text());
	AssertFalse(pRandom->mszString.IsHollow());
	AssertFalse(pDouble->mpSplit2->mszString.IsHollow());
	AssertPointer(pRandom->mszString.Object(), pDouble->mpSplit2->mszString.Object());
	Pass();

	AssertLong(11, pcDatabase->NumIndices());
	Pass();

	ObjectsFlush();
	pcDatabase->Close();
	SafeKill(pcDatabase);
	SafeKill(pcSequence);
	ObjectsKill();

	AssertTrue(pRoot.IsNull());
	AssertTrue(pDouble.IsNull());
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
	AssertLong(3LL, pDiamond1.GetIndex());
	AssertLong(3LL, pDiamond2.GetIndex());

	//Dehollofication of pDiamond1 happens here. pString1->mpAnother and pString2->mpAnother are remapped to the dehollowed diamond object.
	pDiamond1->ClassName();

	AssertFalse(pDiamond1.IsHollow());
	AssertFalse(pDiamond2.IsHollow());  //This should be false but it's not until I remap local pointers.
	AssertPointer(pDiamond1.Object(), pDiamond2.Object());  //These should be the same but they're not until I remap local pointers.
	AssertLong(3LL, pDiamond1.GetIndex());

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

	Ptr<CTestDoubleNamedString> pDouble;

	pDouble = gcObjects.Get("Double Start");
	AssertTrue(pDouble.IsNotNull());
	AssertString("CTestDoubleNamedString", pDouble.ClassName());

	AssertTrue(pDouble->mpSplit1.IsHollow());
	AssertTrue(pDouble->mpSplit2.IsHollow());
	AssertFalse(pDouble->mszString.IsHollow());

	pDouble->mpSplit1->ClassName();
	AssertFalse(pDouble->mpSplit1.IsHollow());
	AssertString("CTestNamedString", pDouble->mpSplit1.ClassName());

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

	TestDehollowficationFromDatabaseSimple();
	TestDehollowficationFromDatabaseComplex();
	TestDehollowficationFromDatabaseOfTwoPointers();
	TestDehollowficationFromChunkFileSource();

	DataIOKill();
	TypesKill();
	FastFunctionsKill();
	MemoryKill();
	TestStatistics();
}

