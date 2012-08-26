#include "BaseLib/FileUtil.h"
#include "StandardLib/Objects.h"
#include "StandardLib/ObjectGraphDeSerialiser.h"
#include "StandardLib/ObjectWriterSimple.h"
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

	cRoot = ORoot();
	cStart1 = ONMalloc(CTestSaveableObject2, "NamedString 1");
	cStart2 = ONMalloc(CTestSaveableObject2, "NamedString 2");

	
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestRemappingOfSimpleFilesOIs(void)
{

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
	//Must also test discarding of pointed to s.
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
	cFileUtil.MakeDir("Output/GraphWriter");

	ObjectsInit(NULL);
	BeginTests();



	TestStatistics();
	ObjectsKill();

	cFileUtil.RemoveDir("Output");
}

