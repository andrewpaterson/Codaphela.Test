#include "BaseLib/FileUtil.h"
#include "StandardLib/Objects.h"
#include "StandardLib/ObjectGraphDeserialiser.h"
#include "StandardLib/ObjectGraphSerialiser.h"
#include "StandardLib/ObjectWriterSimple.h"
#include "StandardLib/ObjectReaderSimple.h"
#include "StandardLib/ObjectWriterChunked.h"
#include "StandardLib/ObjectReaderChunked.h"
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
	gcObjects.AddConstructor<CString>();
	gcObjects.AddConstructor<CArray>();
	gcObjects.AddConstructor<CSet>();
	gcObjects.AddConstructor<CTestSaveableObject1>();
	gcObjects.AddConstructor<CTestSaveableObject2>();
	gcObjects.AddConstructor<CRoot>();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectGraphDeserialiserBuildGraph1(void)
{
	CPointer<CTestSaveableObject2>	cStart1;
	CPointer<CTestSaveableObject2>	cStart2;
	CPointer<CRoot>					cRoot;
	CPointer<CTestSaveableObject1>	cShared;
	CPointer<CString>				cString1;
	CPointer<CString>				cString2;
	CPointer<CTestInteger>			cIgnored;

	cRoot = ORoot();
	cStart1 = ONMalloc(CTestSaveableObject2, "Ow/Start 1");
	cStart2 = ONMalloc(CTestSaveableObject2, "Ow/Start 2");
	cShared = ONMalloc(CTestSaveableObject1, "Ow/Shared");
	cString1 = OMalloc(CString);
	cString2 = OMalloc(CString);
	cIgnored = OMalloc(CTestInteger);
	
	cStart1->Init("Battery");
	cStart2->Init("Charger");

	cStart1->mp1 = cShared;
	cStart2->mp1 = cShared;

	cShared->Init();
	cShared->miInt = 89;
	cShared->mpObject = cShared;

	cString1->Init("Black");
	cString2->Init("Jack");

	cStart1->mp2 = cString1;
	cStart2->mp2 = cString2;

	cIgnored->Init(0, 1, 0);

	cRoot->Add(cStart1);
	cRoot->Add(cStart2);
	cRoot->Add(cIgnored);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestRemappingOfOIs(CObjectWriter* pcWriter, CObjectReader* pcReader)
{
	CFileUtil							cFileUtil;
	CPointer<CTestSaveableObject2>		cBase;
	CPointer<CTestSaveableObject2>		cStart1;
	CPointer<CRoot>						cRoot;
	CPointer<CString>					szOne;
	CPointer<CString>					cString1;
	CPointer<CString>					cString2;
	CObjectGraphSerialiser				cGraphSerialiser;
	CObjectGraphDeserialiser			cGraphDeserialiser;
	CPointer<CTestSaveableObject1>		cShared;
	int									i;

	cFileUtil.MakeDir("Output/GraphDeserialiser/Simple/Remapping");

	ObjectsInit("Output/GraphDeserialiser/Simple/Remapping");
	TestObjectGraphDeserialiserAddConstructors();
	TestObjectGraphDeserialiserBuildGraph1();

	cBase = gcObjects.Get("Ow/Start 1");
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

	ObjectsKill();

	ObjectsInit("Output/GraphDeserialiser/Simple/Remapping");
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

	cGraphDeserialiser.Init(pcReader, gcObjects.GetIndexGenerator());
	cStart1 = cGraphDeserialiser.Read("Ow/Start 1");
	AssertTrue(cStart1.IsNotNull());
	AssertLongLongInt(23, cStart1->GetOI());

	AssertTrue(cStart1->mp1.IsNotNull());
	AssertString("CTestSaveableObject1", cStart1->mp1->ClassName());
	cShared = cStart1->mp1;
	AssertLongLongInt(24, cShared->GetOI());

	AssertTrue(cStart1->mp2.IsNotNull());
	AssertString("CString", cStart1->mp2->ClassName());
	cString1 = cStart1->mp2;
	AssertLongLongInt(25, cString1->GetOI());
	cGraphDeserialiser.Kill();

	for (i = 0; i < 20; i++)
	{
		szOne = OMalloc(CString);
		szOne->Init("Hello World ");
		szOne->Append(i + 20);
		cRoot->Add(szOne);
		AssertLongLongInt(26+i, szOne->GetOI());
	}

	cGraphDeserialiser.Init(pcReader, gcObjects.GetIndexGenerator());
	cStart1 = cGraphDeserialiser.Read("Ow/Start 1");
	AssertTrue(cStart1.IsNotNull());
	AssertLongLongInt(46, cStart1->GetOI());

	AssertTrue(cStart1->mp1.IsNotNull());
	AssertString("CTestSaveableObject1", cStart1->mp1->ClassName());
	cShared = cStart1->mp1;
	AssertLongLongInt(47, cShared->GetOI());

	AssertTrue(cStart1->mp2.IsNotNull());
	AssertString("CString", cStart1->mp2->ClassName());
	cString1 = cStart1->mp2;
	AssertLongLongInt(48, cString1->GetOI());
	cGraphDeserialiser.Kill();

	pcReader->Kill();

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestRemappingOfSimpleFilesOIs(void)
{
	CObjectWriterSimple		cWriter;
	CObjectReaderSimple		cReader;

	cWriter.Init("Output/GraphDeserialiser/Simple/Remapping", "");
	cReader.Init("Output/GraphDeserialiser/Simple/Remapping");

	TestRemappingOfOIs(&cWriter, &cReader);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestRemappingOfChunkedFilesOIs(void)
{
	CObjectWriterChunked	cWriter;
	CObjectReaderChunked	cReader;

	cWriter.Init("Output/GraphDeserialiser/Simple/Remapping", "", "GraphFile");
	cReader.Init("Output/GraphDeserialiser/Simple/Remapping", "GraphFile");

	TestRemappingOfOIs(&cWriter, &cReader);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestOverwritingOfExistingNamesFromChunkedFiles(void)
{
	CObjectWriterChunked				cWriterStart1;
	CObjectWriterChunked				cWriterStart2;
	CObjectReaderChunked				cReader;
	CFileUtil							cFileUtil;
	CPointer<CTestSaveableObject2>		cOwStart1;
	CPointer<CTestSaveableObject2>		cOwStart2;
	CPointer<CTestSaveableObject2>		cStart1;
	CObjectGraphSerialiser				cGraphSerialiser;

	cWriterStart1.Init("Output/GraphDeserialiser/Simple/Remapping", "", "Start1");
	cWriterStart2.Init("Output/GraphDeserialiser/Simple/Remapping", "", "Start2");
	cReader.Init("Output/GraphDeserialiser/Simple/Remapping", "GraphFile");


	cFileUtil.MakeDir("Output/GraphDeserialiser/Simple/Remapping");

	ObjectsInit("Output/GraphDeserialiser/Simple/Remapping");
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

	ObjectsKill();

	ObjectsInit("Output/GraphDeserialiser/Simple/Remapping");
	TestObjectGraphDeserialiserAddConstructors();

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

