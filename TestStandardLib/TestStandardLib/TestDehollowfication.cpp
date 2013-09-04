#include "BaseLib/FileUtil.h"
#include "BaseLib/MemoryFile.h"
#include "StandardLib/Objects.h"
#include "StandardLib/ObjectConverterText.h"
#include "StandardLib/ObjectConverterNative.h"
#include "StandardLib/String.h"
#include "StandardLib/ObjectWriterChunked.h"
#include "StandardLib/ObjectGraphSerialiser.h"
#include "TestLib/Assert.h"
#include "ObjectWriterChunkedTestClasses.h"


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
	gcObjects.AddConstructor<CString>();
	gcObjects.AddConstructor<CArrayObject>();
	gcObjects.AddConstructor<CSetObject>();
	gcObjects.AddConstructor<CRoot>();
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

	cDiamond = ONMalloc(CTestNamedString, "Diamond End");
	sz1 = OMalloc(CString);

	cNS1 = ONMalloc(CTestNamedString, "NamedString 1");
	cNS1->Init(sz1, cDiamond, "Hello");
	sz1->Init("World");

	cNS2 = ONMalloc(CTestNamedString, "NamedString 2");
	sz2 = OMalloc(CString);

	cNS2->Init(sz2, cDiamond, "12345");
	sz2->Init("6789");

	sz3 = OMalloc(CString);
	sz3->Init("End");
	cDiamond->Init(sz3, ONull, "Before Swine");

	sz4 = OMalloc(CString);
	sz4->Init("Start");
	cDouble = ONMalloc(CTestDoubleNamedString, "Double Start");
	cDouble->Init(sz4, cNS1, ONull);

	cRoot->Add(cDouble);

	cDouble->mpSplit1 = cNS2;

	cNS3 = ONMalloc(CTestNamedString, "NamedString 3");
	cNS3->Init(sz1, ONull, "Random");

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
//     \   /sz4
//      \ / /
//    cDouble  sz1 
//       \      |
//        \   cNS3
//         \  /
//        cRoot
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
	CObjectWriterChunked				cWriter;
	CObjectGraphSerialiser				cGraphSerialiser;

	cDouble = SetupDehollowficationScene();

	cWriter.Init("Output\\Dehollowfication\\ChunkFile", "", "Double");
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
	CIndexedConfig	cConfig;
	CFileUtil		cFileUtil;

	cConfig.Manual("Output\\Dehollowfication\\Database",
					FALSE,
					TRUE,
					FALSE,
					4,
					2,
					4,
					2,
					4 * sizeof(CIndexedDataDescriptor),
					1 MB,
					FALSE);

	cFileUtil.RemoveDir("Output\\Dehollowfication\\Database");
	ObjectsInit(&cConfig);
	SetupDehollowficationScene();
	gcObjects.Flush(FALSE, FALSE);
	ObjectsKill();

	ObjectsInit(&cConfig);
	SetupDehollowficationConstructors();

	AssertLongLongInt(0, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(0, gcObjects.NumMemoryNames());
	AssertLongLongInt(11, gcObjects.NumDatabaseObjects());
	AssertLongLongInt(0, gcObjects.NumDatabaseObjectsCached());
	AssertLongLongInt(6, gcObjects.NumDatabaseNames());

	Ptr<CRoot> pRoot = ORoot();

	AssertTrue(pRoot->IsSetHollow());

	AssertLongLongInt(2, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(1, gcObjects.NumMemoryNames());
	AssertLongLongInt(1, gcObjects.NumDatabaseObjectsCached());
	AssertLongLongInt(6, gcObjects.NumDatabaseNames());

	Ptr<CTestDoubleNamedString> pTest = pRoot->Get<CTestDoubleNamedString>("Double Start");
	AssertFalse(pRoot->IsSetHollow());
	AssertTrue(pTest.IsNotNull());
	AssertTrue(pTest.IsHollow());
	
	AssertString("12345", pTest->mpSplit1->mszEmbedded.Text());
	AssertTrue(pTest->mpSplit1->mpAnother.IsHollow());
	AssertTrue(pTest->mpSplit2.IsHollow());
	AssertTrue(pTest->mpSplit1->mszString.IsHollow());
	AssertString("Diamond End", pTest->mpSplit1->mpAnother.GetName());
	AssertString("6789", pTest->mpSplit1->mszString->Text());
	AssertFalse(pTest->mpSplit1->mszString.IsHollow());

	AssertInt(2, gcObjects.GetStackPointers()->UsedPointers());

	Ptr<CTestNamedString> pDiamond = pTest->mpSplit1->mpAnother;
	AssertInt(3, gcObjects.GetStackPointers()->UsedPointers());
	AssertTrue(pTest->mpSplit1->mpAnother.IsHollow());
	AssertTrue(pDiamond.IsHollow());

	pDiamond->ClassName();
	AssertFalse(pDiamond.IsHollow());
	AssertFalse(pTest->mpSplit1->mpAnother.IsHollow());

	AssertLongLongInt(10, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(6, gcObjects.NumMemoryNames());
	AssertLongLongInt(3, gcObjects.NumDatabaseObjectsCached());
	AssertLongLongInt(6, gcObjects.NumDatabaseNames());

	AssertTrue(pTest->mpSplit2.IsHollow());
	pTest->mpSplit2->ClassSize();
	AssertFalse(pTest->mpSplit2.IsHollow());
	AssertFalse(pTest->mpSplit2->mpAnother.IsHollow());
	AssertPointer(pDiamond.Object(), pTest->mpSplit2->mpAnother.Object());

	AssertLongLongInt(11, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(6, gcObjects.NumMemoryNames());
	AssertLongLongInt(2, gcObjects.NumDatabaseObjectsCached());
	AssertLongLongInt(6, gcObjects.NumDatabaseNames());

	Ptr<CTestNamedString> pRandom = pRoot->Get<CTestNamedString>("NamedString 3");
	AssertTrue(pRandom.IsNotNull());
	AssertTrue(pRandom.IsHollow());

	AssertTrue(pRandom->mszString.IsHollow());
	AssertFalse(pRandom.IsHollow());
	AssertTrue(pTest->mpSplit2->mszString.IsHollow());

	AssertString("World", pRandom->mszString->Text());
	AssertFalse(pRandom->mszString.IsHollow());
	AssertFalse(pTest->mpSplit2->mszString.IsHollow());
	AssertPointer(pRandom->mszString.Object(), pTest->mpSplit2->mszString.Object());

	AssertLongLongInt(11, gcObjects.NumDatabaseObjects());

	ObjectsKill();

	AssertTrue(pRoot.IsNull());
	AssertTrue(pTest.IsNull());
	AssertTrue(pDiamond.IsNull());
	AssertTrue(pRandom.IsNull());

	pDiamond.UnsafeClearObject();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDehollowficationFromDatabaseOfTwoPointers(void)
{
	CIndexedConfig	cConfig;
	CFileUtil		cFileUtil;

	cConfig.Manual("Output\\Dehollowfication\\Database",
		FALSE,
		TRUE,
		FALSE,
		4,
		2,
		4,
		2,
		4 * sizeof(CIndexedDataDescriptor),
		1 MB,
		FALSE);

	cFileUtil.RemoveDir("Output\\Dehollowfication\\Database");
	ObjectsInit(&cConfig);
	SetupDehollowficationScene();
	gcObjects.Flush(FALSE, FALSE);
	ObjectsKill();

	ObjectsInit(&cConfig);
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
	//AssertFalse(pDiamond2.IsHollow());  //This should be false but it's not until I remap local pointers.
	//AssertPointer(pDiamond1.Object(), pDiamond2.Object());  //These should be the same but they're not until I remap local pointers.
	AssertLongLongInt(3LL, pDiamond1.GetIndex());
	//AssertLongLongInt(-1LL, pDiamond2.GetIndex());

	AssertFalse(pString1->mpAnother.IsHollow());
	AssertFalse(pString2->mpAnother.IsHollow());
	AssertPointer(pString1->mpAnother.Object(), pString2->mpAnother.Object());

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDehollowficationFromChunkFileSource(void)
{
	CFileUtil		cFileUtil;

	cFileUtil.RemoveDir("Output\\Dehollowfication\\ChunkFile");
	ObjectsInit("Output\\Dehollowfication\\Temp");
	WriteDehollowficationChunkedFile();
	ObjectsKill();
	cFileUtil.RemoveDir("Output\\Dehollowfication\\Temp");

	CObjectSourceChunked* pcObjectSourceChunked;


	CDiskFile*	pcDiskFile = DiskFile("Output\\Dehollowfication\\ChunkFile\\Double.DRG");

	ObjectsInit("Output\\Dehollowfication\\Temp");
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

	ObjectsKill();
}



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDehollowfication(void)
{
	BeginTests();

	TestDehollowficationFromDatabase();
	TestDehollowficationFromDatabaseOfTwoPointers();
	TestDehollowficationFromChunkFileSource();

	TestStatistics();
}

