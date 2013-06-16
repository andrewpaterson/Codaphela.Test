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
	gcObjects.AddConstructor<CArray>();
	gcObjects.AddConstructor<CSet>();
	gcObjects.AddConstructor<CRoot>();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CPointer<CTestDoubleNamedString> SetupDehollowficationScene(void)
{
	CPointer<CTestNamedString>			cNS1;
	CPointer<CTestNamedString>			cNS2;
	CPointer<CTestNamedString>			cDiamond;
	CPointer<CTestDoubleNamedString>	cDouble;
	CPointer<CString>					sz1;
	CPointer<CString>					sz3;
	CPointer<CString>					sz2;
	CPointer<CString>					sz4;
	CPointer<CRoot>						cRoot;
	CPointer<CTestNamedString>			cNS3;

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
	cDiamond->Init(sz3, ONNull(CTestNamedString), "Before Swine");

	sz4 = OMalloc(CString);
	sz4->Init("Start");
	cDouble = ONMalloc(CTestDoubleNamedString, "Double Start");
	cDouble->Init(sz4, cNS1, ONNull(CTestNamedString));

	cRoot->Add(cDouble);

	cDouble->mpSplit1 = cNS2;

	cNS3 = ONMalloc(CTestNamedString, "NamedString 3");
	cNS3->Init(sz1, ONNull(CTestNamedString), "Random");

	cRoot->Add(cNS3);

	return cDouble;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void WriteDehollowficationChunkedFile(void)
{
	CPointer<CTestDoubleNamedString>	cDouble;
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
					4,  //4
					12, //2 break with 12 objects.  
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

	CPointer<CRoot> pRoot = ORoot();

	AssertTrue(pRoot->IsSetHollow());

	AssertLongLongInt(2, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(1, gcObjects.NumMemoryNames());
	AssertLongLongInt(11, gcObjects.NumDatabaseObjects());
	AssertLongLongInt(1, gcObjects.NumDatabaseObjectsCached());
	AssertLongLongInt(6, gcObjects.NumDatabaseNames());

	CPointer<CTestDoubleNamedString> pTest = pRoot->Get<CTestDoubleNamedString>("Double Start");
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

	CPointer<CTestNamedString> pDiamond = pTest->mpSplit1->mpAnother;
	AssertTrue(pTest->mpSplit1->mpAnother.IsHollow());
	AssertTrue(pDiamond.IsHollow());

	pDiamond->ClassName();
	AssertFalse(pDiamond.IsHollow());
	AssertFalse(pTest->mpSplit1->mpAnother.IsHollow());

	AssertLongLongInt(10, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(6, gcObjects.NumMemoryNames());
	AssertLongLongInt(11, gcObjects.NumDatabaseObjects());
	AssertLongLongInt(6, gcObjects.NumDatabaseObjectsCached());
	AssertLongLongInt(6, gcObjects.NumDatabaseNames());

	AssertTrue(pTest->mpSplit2.IsHollow());
	pTest->mpSplit2->ClassSize();
	AssertFalse(pTest->mpSplit2.IsHollow());
	AssertFalse(pTest->mpSplit2->mpAnother.IsHollow());
	AssertPointer(pDiamond.Object(), pTest->mpSplit2->mpAnother.Object());

	AssertLongLongInt(11, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(6, gcObjects.NumMemoryNames());
	AssertLongLongInt(11, gcObjects.NumDatabaseObjects());
	AssertLongLongInt(7, gcObjects.NumDatabaseObjectsCached());
	AssertLongLongInt(6, gcObjects.NumDatabaseNames());

	CPointer<CTestNamedString> pRandom = pRoot->Get<CTestNamedString>("NamedString 3");
	AssertTrue(pRandom.IsNotNull());
	AssertTrue(pRandom.IsHollow());

	AssertTrue(pRandom->mszString.IsHollow());
	AssertFalse(pRandom.IsHollow());
	AssertTrue(pTest->mpSplit2->mszString.IsHollow());

	AssertString("World", pRandom->mszString->Text());
	AssertFalse(pRandom->mszString.IsHollow());
	AssertFalse(pTest->mpSplit2->mszString.IsHollow());
	AssertPointer(pRandom->mszString.Object(), pTest->mpSplit2->mszString.Object());

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

	
	ObjectsInit("Output\\Dehollowfication\\Temp");

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
	TestDehollowficationFromChunkFileSource();

	TestStatistics();
}

