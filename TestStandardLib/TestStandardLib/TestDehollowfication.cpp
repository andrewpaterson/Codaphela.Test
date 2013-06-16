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
	cNS3->Init(sz1, cDiamond, "Random");

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

	CPointer<CRoot> pRoot = ORoot();

	AssertTrue(pRoot->IsSetHollow());

	CPointer<CTestDoubleNamedString> pTest = pRoot->Get<CTestDoubleNamedString>("Double Start");
	AssertFalse(pRoot->IsSetHollow());
	AssertTrue(pTest.IsNotNull());
	AssertTrue(pTest.IsHollow());
	
	AssertTrue(gcObjects.GetMemory()->GetNames()->TestConsistency()); //Bug in CASCIITree.
	AssertString("12345", pTest->mpSplit1->mszEmbedded.Text());
	AssertTrue(gcObjects.GetMemory()->GetNames()->TestConsistency()); //Bug in CASCIITree.
	AssertTrue(pTest->mpSplit1->mpAnother.IsHollow());
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

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDehollowficationFromChunkFileSource(void)
{
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

