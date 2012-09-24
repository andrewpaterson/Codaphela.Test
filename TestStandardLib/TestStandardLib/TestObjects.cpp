#include "StandardLib/Objects.h"
#include "TestLib/Assert.h"
#include "ObjectTestClasses.h"
#include "ObjectWriterChunkedTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CPointer<CTestDoubleNamedString> SetupObjectsForDehollowfication(void)
{
	CPointer<CTestNamedString>			cNS1;
	CPointer<CTestNamedString>			cNS2;
	CPointer<CTestNamedString>			cNS3;
	CPointer<CTestNamedString>			cDiamond;
	CPointer<CTestDoubleNamedString>	cDouble;
	CPointer<CRoot>						cRoot;
	CPointer<CString>					cS1;
	CPointer<CString>					cS2;

	cRoot = ORoot();

	cDiamond = ONMalloc(CTestNamedString, "Diamond");

	cS1 = OMalloc(CString);
	cS1->Init("CS1");
	cNS1 = ONMalloc(CTestNamedString, "NS1");
	cNS1->Init(cS1, cDiamond, "NS1");

	cNS2 = ONMalloc(CTestNamedString, "NS2");
	cNS2->Init(ONNull(CString), cDiamond, "NS2");

	cNS3 = ONMalloc(CTestNamedString, "NS3");
	cNS3->Init(ONNull(CString), cNS1, "NS3");

	cS2 = OMalloc(CString);
	cS2->Init("CS2");
	cDiamond->Init(cS2, ONNull(CTestNamedString), "Diamond");

	cDouble = ONMalloc(CTestDoubleNamedString, "Double");
	cDouble->Init(ONNull(CString), cNS2, cNS3);

	cRoot->Add(cDouble);
	return cDouble;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectsObjectSave(void)
{
	CFileUtil							cFileUtil;
	CPointer<CTestDoubleNamedString>	cDouble;
	BOOL								bResult;

	cFileUtil.RemoveDir("Output");
	cFileUtil.MakeDir("Output/ObjectSave");
	ObjectsInit("Output/ObjectSave");
	cDouble = SetupObjectsForDehollowfication();

	AssertLongLongInt(0, gcObjects.NumDatabaseObjects());
	AssertLongLongInt(9, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(6, gcObjects.NumMemoryNames());
	AssertTrue(cDouble.IsDirty());
	
	bResult = gcObjects.Save(cDouble.Object());
	AssertTrue(bResult);
	AssertTrue(cDouble.IsDirty());  //This object is *still* dirty after save.  Almost no objects will answer true to IsDirty.

	AssertLongLongInt(1, gcObjects.NumDatabaseObjects());
	AssertLongLongInt(9, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(6, gcObjects.NumMemoryNames());
	AssertInt(102, cDouble->SerialisedSize());
	AssertLongLongInt(1, gcObjects.NumDatabaseObjectsCached(102));
	AssertLongLongInt(0, gcObjects.NumDatabaseObjectsCached(110));

	bResult = gcObjects.Save(cDouble.Object());
	AssertTrue(bResult);
	AssertLongLongInt(1, gcObjects.NumDatabaseObjects());
	AssertInt(102, cDouble->SerialisedSize());
	AssertLongLongInt(1, gcObjects.NumDatabaseObjectsCached(102));
	AssertLongLongInt(0, gcObjects.NumDatabaseObjectsCached(110));
	
	cDouble->mszString = OMalloc(CString);
	cDouble->mszString->Init("A String");

	bResult = gcObjects.Save(cDouble.Object());
	AssertTrue(bResult);
	AssertLongLongInt(1, gcObjects.NumDatabaseObjects());
	AssertInt(110, cDouble->SerialisedSize());
	AssertLongLongInt(0, gcObjects.NumDatabaseObjectsCached(102));
	AssertLongLongInt(1, gcObjects.NumDatabaseObjectsCached(110));

	cDouble->mszString = OMalloc(CString);
	cDouble->mszString->Init("Different Object");

	AssertInt(110, cDouble->SerialisedSize());
	bResult = gcObjects.Save(cDouble.Object());
	AssertTrue(bResult);
	AssertLongLongInt(1, gcObjects.NumDatabaseObjects());
	AssertInt(110, cDouble->SerialisedSize());
	AssertLongLongInt(0, gcObjects.NumDatabaseObjectsCached(102));
	AssertLongLongInt(1, gcObjects.NumDatabaseObjectsCached(110));

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectDehollowfication(void)
{
	CFileUtil	cFileUtil;

	cFileUtil.RemoveDir("Output");
	cFileUtil.MakeDir("Output/Dehollowfication");
	ObjectsInit("Output/Dehollowfication");
	SetupObjectsForDehollowfication();
	gcObjects.Flush();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectsFlush(void)
{
	CFileUtil	cFileUtil;
	BOOL		bResult;

	cFileUtil.RemoveDir("Output");
	cFileUtil.MakeDir("Output/Dehollowfication");
	ObjectsInit("Output/Dehollowfication");
	SetupObjectsForDehollowfication();

	AssertLongLongInt(0, gcObjects.NumDatabaseObjects());
	AssertLongLongInt(9, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(6, gcObjects.NumMemoryNames());
	
	bResult = gcObjects.Flush();
	AssertTrue(bResult);

	AssertLongLongInt(9, gcObjects.NumDatabaseObjects());
	AssertLongLongInt(9, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(6, gcObjects.NumMemoryNames());

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjects(void)
{
	BeginTests();

	TestObjectsObjectSave();
	//TestObjectsFlush();
	//TestObjectDehollowfication();

	TestStatistics();
}

