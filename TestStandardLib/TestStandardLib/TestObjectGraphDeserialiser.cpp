#include "BaseLib/FileUtil.h"
#include "StandardLib/Objects.h"
#include "StandardLib/ObjectGraphDeserialiser.h"
#include "StandardLib/ObjectGraphSerialiser.h"
#include "StandardLib/ObjectWriterSimple.h"
#include "StandardLib/ObjectReaderSimple.h"
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
	gcObjects.AddConstructor<CTestObject>();
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
void TestRemappingOfSimpleFilesOIs(void)
{
	CFileUtil							cFileUtil;
	CPointer<CTestSaveableObject2>		cBase;
	CPointer<CTestSaveableObject2>		cRead;
	CPointer<CRoot>						cRoot;
	CPointer<CString>					szOne;

	cFileUtil.MakeDir("Output/GraphDeserialiser/Simple/Remapping");

	ObjectsInit("Output/GraphDeserialiser/Simple/Remapping");
	TestObjectGraphDeserialiserAddConstructors();
	TestObjectGraphDeserialiserBuildGraph1();

	CObjectGraphSerialiser		cGraphSerialiser;
	CObjectWriterSimple			cWriter;

	cWriter.Init("Output/GraphDeserialiser/Simple/Remapping", "");
	cGraphSerialiser.Init(&cWriter);
	cBase = gcObjects.Get("Ow/Start 1");
	AssertLongLongInt(1, cBase->GetOI());
	AssertTrue(cGraphSerialiser.Write(&cBase));
	cGraphSerialiser.Kill();
	cWriter.Kill();

	ObjectsKill();

	ObjectsInit("Output/GraphDeserialiser/Simple/Remapping");
	TestObjectGraphDeserialiserAddConstructors();

	cRoot = ORoot();
	szOne = OMalloc(CString);
	szOne->Init("Hello World");
	cRoot->Add(szOne);
	AssertLongLongInt(1, szOne->GetOI());

	CObjectGraphDeserialiser	cGraphDeserialiser;
	CObjectReaderSimple			cReader;

	cReader.Init("Output/GraphDeserialiser/Simple/Remapping");
	cGraphDeserialiser.Init(&cReader);
	cRead = cGraphDeserialiser.Read("Ow/Start 1");
	AssertTrue(cRead.IsNotNull());
	AssertLongLongInt(1, cRead->GetOI());
	cGraphDeserialiser.Kill();
	cReader.Kill();

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestRemappingOfChunkedFilesOIs(void)
{

}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestOverwritingOfExistingNamesFromSimpleFiles(void)
{
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestOverwritingOfExistingNamesFromChunkedFiles(void)
{

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

	TestOverwritingOfExistingNamesFromSimpleFiles();
	TestOverwritingOfExistingNamesFromChunkedFiles();

	TestStatistics();

	cFileUtil.RemoveDir("Output");
}

