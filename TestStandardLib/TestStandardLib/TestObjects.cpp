#include "StandardLib/Objects.h"
#include "TestLib/Assert.h"
#include "ObjectTestClasses.h"
#include "ObjectWriterChunkedTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
Ptr<CTestDoubleNamedString> SetupObjectsForDehollowfication(void)
{
	Ptr<CTestNamedString>			cNS1;
	Ptr<CTestNamedString>			cNS2;
	Ptr<CTestNamedString>			cNS3;
	Ptr<CTestNamedString>			cDiamond;
	Ptr<CTestDoubleNamedString>	cDouble;
	Ptr<CRoot>						cRoot;
	Ptr<CString>					cS1;
	Ptr<CString>					cS2;

	cRoot = ORoot();

	cDiamond = ONMalloc(CTestNamedString, "Diamond");

	cS1 = OMalloc(CString);
	cS1->Init("CS1");
	cNS1 = ONMalloc(CTestNamedString, "NS1");
	cNS1->Init(cS1, cDiamond, "NS1");

	cNS2 = ONMalloc(CTestNamedString, "NS2");
	cNS2->Init(ONull, cDiamond, "NS2");

	cNS3 = ONMalloc(CTestNamedString, "NS3");
	cNS3->Init(ONull, cNS1, "NS3");

	cS2 = OMalloc(CString);
	cS2->Init("CS2");
	cDiamond->Init(cS2, ONull, "Diamond");

	cDouble = ONMalloc(CTestDoubleNamedString, "Double");
	cDouble->Init(ONull, cNS2, cNS3);

	cRoot->Add(cDouble);
	return cDouble;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void SetupObjectsConstructors(void)
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
void TestObjectsInMemoryIteration()
{
	SIndexesIterator	sIter;
	OIndex				oi;

	ObjectsInit();
	SetupObjectsForDehollowfication();

	oi = gcObjects.StartMemoryIteration(&sIter);
	AssertLongLongInt(1LL, oi);
	oi = gcObjects.IterateMemory(&sIter);
	AssertLongLongInt(2LL, oi);
	oi = gcObjects.IterateMemory(&sIter);
	AssertLongLongInt(3LL, oi);
	oi = gcObjects.IterateMemory(&sIter);
	AssertLongLongInt(4LL, oi);
	oi = gcObjects.IterateMemory(&sIter);
	AssertLongLongInt(5LL, oi);
	oi = gcObjects.IterateMemory(&sIter);
	AssertLongLongInt(6LL, oi);
	oi = gcObjects.IterateMemory(&sIter);
	AssertLongLongInt(7LL, oi);
	oi = gcObjects.IterateMemory(&sIter);
	AssertLongLongInt(8LL, oi);
	oi = gcObjects.IterateMemory(&sIter);
	AssertLongLongInt(9LL, oi);
	oi = gcObjects.IterateMemory(&sIter);
	AssertLongLongInt(INVALID_O_INDEX, oi);

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectsObjectSave(void)
{
	CFileUtil							cFileUtil;
	Ptr<CTestDoubleNamedString>	cDouble;
	BOOL								bResult;
	CIndexedConfig						cConfig;

	cFileUtil.RemoveDir("Output");
	cFileUtil.MakeDir("Output/ObjectSave");
	cConfig.OptimiseForGameGraph("Output/ObjectSave");
	cConfig.SetTransient(TRUE);
	ObjectsInit(&cConfig);

	cDouble = SetupObjectsForDehollowfication();

	AssertLongLongInt(0, gcObjects.NumDatabaseObjects());
	AssertLongLongInt(9, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(6, gcObjects.NumMemoryNames());
	AssertTrue(cDouble.IsDirty());
	
	bResult = gcObjects.Save(cDouble.BaseObject());
	AssertTrue(bResult);
	AssertTrue(cDouble.IsDirty());  //This object is *still* dirty after save.  Almost no objects will answer true to IsDirty.

	AssertLongLongInt(1, gcObjects.NumDatabaseObjects());
	AssertLongLongInt(9, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(6, gcObjects.NumMemoryNames());
	AssertInt(106, cDouble->SerialisedSize());
	AssertLongLongInt(1, gcObjects.NumDatabaseObjectsCached(106));
	AssertLongLongInt(0, gcObjects.NumDatabaseObjectsCached(118));

	bResult = gcObjects.Save(cDouble.BaseObject());
	AssertTrue(bResult);
	AssertLongLongInt(1, gcObjects.NumDatabaseObjects());
	AssertInt(106, cDouble->SerialisedSize());
	AssertLongLongInt(1, gcObjects.NumDatabaseObjectsCached(106));
	AssertLongLongInt(0, gcObjects.NumDatabaseObjectsCached(118));
	
	cDouble->mszString = OMalloc(CString);
	cDouble->mszString->Init("A String");

	bResult = gcObjects.Save(cDouble.BaseObject());
	AssertTrue(bResult);
	AssertLongLongInt(1, gcObjects.NumDatabaseObjects());
	AssertInt(118, cDouble->SerialisedSize());
	AssertLongLongInt(0, gcObjects.NumDatabaseObjectsCached(106));
	AssertLongLongInt(1, gcObjects.NumDatabaseObjectsCached(118));

	cDouble->mszString = OMalloc(CString);
	cDouble->mszString->Init("Different Object");

	AssertInt(118, cDouble->SerialisedSize());
	bResult = gcObjects.Save(cDouble.BaseObject());
	AssertTrue(bResult);
	AssertLongLongInt(1, gcObjects.NumDatabaseObjects());
	AssertInt(118, cDouble->SerialisedSize());
	AssertLongLongInt(0, gcObjects.NumDatabaseObjectsCached(106));
	AssertLongLongInt(1, gcObjects.NumDatabaseObjectsCached(118));

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectsFlushNoClear(void)
{
	CFileUtil	cFileUtil;
	BOOL		bResult;

	cFileUtil.RemoveDir("Output");
	cFileUtil.MakeDir("Output/Flush1");
	ObjectsInit("Output/Flush1");
	SetupObjectsForDehollowfication();

	AssertLongLongInt(0, gcObjects.NumDatabaseObjects());
	AssertLongLongInt(0, gcObjects.NumDatabaseNames());
	AssertLongLongInt(9, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(6, gcObjects.NumMemoryNames());
	
	bResult = gcObjects.Flush(FALSE, FALSE);
	AssertTrue(bResult);

	AssertLongLongInt(9, gcObjects.NumDatabaseObjects());
	AssertLongLongInt(6, gcObjects.NumDatabaseNames());
	AssertLongLongInt(9, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(6, gcObjects.NumMemoryNames());

	ObjectsKill();

	AssertFile("Input/Dehollowfication/32_0.NAM",     "Output/Flush1/32_0.NAM");
	AssertFile("Input/Dehollowfication/44_0.DAT",     "Output/Flush1/44_0.DAT");
	AssertFile("Input/Dehollowfication/56_0.DAT",     "Output/Flush1/56_0.DAT");
	AssertFile("Input/Dehollowfication/78_0.DAT",     "Output/Flush1/78_0.DAT");
	AssertFile("Input/Dehollowfication/89_0.DAT",     "Output/Flush1/89_0.DAT");
	AssertFile("Input/Dehollowfication/93_0.DAT",     "Output/Flush1/93_0.DAT");
	AssertFile("Input/Dehollowfication/105_0.DAT",    "Output/Flush1/105_0.DAT");
	AssertFile("Input/Dehollowfication/106_0.DAT",    "Output/Flush1/106_0.DAT");
	AssertFile("Input/Dehollowfication/Files.DAT",    "Output/Flush1/Files.DAT");
	AssertFile("Input/Dehollowfication/Indicies.DAT", "Output/Flush1/Indicies.DAT");
	AssertFile("Input/Dehollowfication/Files.NAM",    "Output/Flush1/Files.NAM");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectsFlushDurable(void)
{
	CFileUtil		cFileUtil;
	BOOL			bResult;
	CIndexedConfig	cConfig;

	cFileUtil.RemoveDir("Output");
	cFileUtil.MakeDir("Output/Flush2");
	

	cConfig.OptimiseForTransactions("Output/Flush2");
	//cConfig.SetWriteThrough(FALSE);

	ObjectsInit(&cConfig);
	SetupObjectsForDehollowfication();

	AssertLongLongInt(0, gcObjects.NumDatabaseObjects());
	AssertLongLongInt(0, gcObjects.NumDatabaseNames());
	AssertLongLongInt(9, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(6, gcObjects.NumMemoryNames());

	bResult = gcObjects.Flush(FALSE, FALSE);
	AssertTrue(bResult);

	AssertLongLongInt(9, gcObjects.NumDatabaseObjects());
	AssertLongLongInt(6, gcObjects.NumDatabaseNames());
	AssertLongLongInt(9, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(6, gcObjects.NumMemoryNames());

	ObjectsKill();

	AssertFile("Input/Dehollowfication/48_0.DAT",     "Output/Flush2/48_0.DAT");
	AssertFile("Input/Dehollowfication/56_0.DAT",     "Output/Flush2/56_0.DAT");
	AssertFile("Input/Dehollowfication/68_0.DAT",     "Output/Flush2/68_0.DAT");
	AssertFile("Input/Dehollowfication/89_0.DAT",     "Output/Flush2/89_0.DAT");
	AssertFile("Input/Dehollowfication/93_0.DAT",     "Output/Flush2/93_0.DAT");
	AssertFile("Input/Dehollowfication/101_0.DAT",    "Output/Flush2/101_0.DAT");
	AssertFile("Input/Dehollowfication/102_0.DAT",    "Output/Flush2/102_0.DAT");
	AssertFile("Input/Dehollowfication/Files.DAT",    "Output/Flush2/Files.DAT");
	AssertFile("Input/Dehollowfication/Indicies.DAT", "Output/Flush2/Indicies.DAT");
	AssertFile("Input/Dehollowfication/32_0.NAM",     "Output/Flush2/32_0.NAM");
	AssertFile("Input/Dehollowfication/Files.NAM",    "Output/Flush2/Files.NAM");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectsEvict(void)
{
	CFileUtil	cFileUtil;
	BOOL		bResult;

	cFileUtil.RemoveDir("Output");
	cFileUtil.MakeDir("Output/Eviction");
	ObjectsInit("Output/Eviction");
	SetupObjectsForDehollowfication();

	AssertLongLongInt(0, gcObjects.NumDatabaseObjects());
	AssertLongLongInt(0, gcObjects.NumDatabaseObjectsCached());
	AssertLongLongInt(9, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(6, gcObjects.NumMemoryNames());

	bResult = gcObjects.Flush(FALSE, FALSE);
	AssertTrue(bResult);

	AssertLongLongInt(9, gcObjects.NumDatabaseObjects());
	AssertLongLongInt(9, gcObjects.NumDatabaseObjectsCached());
	AssertLongLongInt(9, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(6, gcObjects.NumMemoryNames());

	ObjectsKill();

	cFileUtil.RemoveDir("Output");
	cFileUtil.MakeDir("Output/Eviction");
	ObjectsInit("Output/Eviction");
	SetupObjectsForDehollowfication();

	bResult = gcObjects.Flush(FALSE, TRUE);
	AssertTrue(bResult);

	AssertLongLongInt(9, gcObjects.NumDatabaseObjects());
	AssertLongLongInt(0, gcObjects.NumDatabaseObjectsCached());
	AssertLongLongInt(9, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(6, gcObjects.NumMemoryNames());

	ObjectsKill();

	cFileUtil.RemoveDir("Output");
	cFileUtil.MakeDir("Output/Eviction");
	ObjectsInit("Output/Eviction");
	SetupObjectsForDehollowfication();

	bResult = gcObjects.Flush(TRUE, FALSE);
	AssertTrue(bResult);

	AssertLongLongInt(9, gcObjects.NumDatabaseObjects());
	AssertLongLongInt(9, gcObjects.NumDatabaseObjectsCached());
	AssertLongLongInt(0, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(0, gcObjects.NumMemoryNames());

	ObjectsKill();

	cFileUtil.RemoveDir("Output");
	cFileUtil.MakeDir("Output/Eviction");
	ObjectsInit("Output/Eviction");
	SetupObjectsForDehollowfication();

	bResult = gcObjects.Flush(TRUE, TRUE);
	AssertTrue(bResult);

	AssertLongLongInt(9, gcObjects.NumDatabaseObjects());
	AssertLongLongInt(0, gcObjects.NumDatabaseObjectsCached());
	AssertLongLongInt(0, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(0, gcObjects.NumMemoryNames());

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectsObjectKillInGraph(void)
{
	Ptr<CTestNamedString>	cNS1;
	Ptr<CTestNamedString>	cNS2;
	Ptr<CRoot>				cRoot;
	Ptr<CString>			cS1;
	Ptr<CString>			cS2;
	CTestNamedString*		pcNS2;
	CString*				pcS2;

	ObjectsInit();

	cRoot = ORoot();

	cS1 = OMalloc(CString);
	cS1->Init("CS1");
	cNS1 = ONMalloc(CTestNamedString, "NS1");
	cNS1->Init(cS1, ONull, "NS1");

	cS2 = OMalloc(CString);
	cS2->Init("CS2");
	cNS2 = ONMalloc(CTestNamedString, "NS2");
	cNS2->Init(cS2, cNS1, "NS2");

	cRoot->Add(cNS2);
	
	AssertPointer(cNS2->mpAnother.Object(), cNS1.Object());
	AssertLongLongInt(6, gcObjects.NumMemoryIndexes());
	pcNS2 = &cNS2;
	cNS2 = NULL;
	cRoot = NULL;
	cS1 = NULL;
	pcS2 = &cS2;
	cS2 = NULL;
	AssertLongLongInt(6, gcObjects.NumMemoryIndexes());

	cNS1->Kill();

	AssertNull(pcNS2->mpAnother.Object());
	AssertLongLongInt(4, gcObjects.NumMemoryIndexes());
	AssertPointer(pcNS2->mszString.Object(), pcS2);

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectsArrayKillInGraph(void)
{
	Ptr<CTestNamedString>	cNS1;
	Ptr<CArrayObject>		cA1;
	Ptr<CArrayObject>		cA2;
	Ptr<CRoot>				cRoot;
	Ptr<CString>			cS1;

	ObjectsInit();

	cRoot = ORoot();

	cS1 = OMalloc(CString);
	cS1->Init("CS1");
	cNS1 = ONMalloc(CTestNamedString, "NS1");
	cNS1->Init(cS1, ONull, "NS1");

	cA1 = OMalloc(CArrayObject);
	cA2 = OMalloc(CArrayObject);

	cA1->Init();
	cA1->Add(cNS1);

	cA2->Init();
	cA2->Add(cNS1);

	cRoot->Add(cA1);
	cRoot->Add(cA2);

	AssertLongLongInt(6, gcObjects.NumMemoryIndexes());

	cNS1 = NULL;
	cRoot = NULL;
	cS1 = NULL;

	cA1->Kill();
	AssertLongLongInt(5, gcObjects.NumMemoryIndexes());

	cA2->Kill();
	AssertLongLongInt(2, gcObjects.NumMemoryIndexes());

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectsObjectKillInArrayInGraph(void)
{
	Ptr<CTestNamedString>	cNS1;
	Ptr<CArrayObject>		cA1;
	Ptr<CArrayObject>		cA2;
	Ptr<CRoot>				cRoot;
	Ptr<CString>			cS1;

	ObjectsInit();

	cRoot = ORoot();

	cS1 = OMalloc(CString);
	cS1->Init("CS1");
	cNS1 = ONMalloc(CTestNamedString, "NS1");
	cNS1->Init(cS1, ONull, "NS1");

	cA1 = OMalloc(CArrayObject);
	cA2 = OMalloc(CArrayObject);

	cA1->Init();
	cA1->Add(cNS1);

	cA2->Init();
	cA2->Add(cNS1);

	cRoot->Add(cA1);
	cRoot->Add(cA2);

	AssertInt(1, cA1->NumTos());
	AssertInt(1, cA2->NumTos());
	AssertLongLongInt(6, gcObjects.NumMemoryIndexes());
	cRoot = NULL;
	cS1 = NULL;
	AssertLongLongInt(6, gcObjects.NumMemoryIndexes());

	cNS1->Kill();
	AssertLongLongInt(4, gcObjects.NumMemoryIndexes());

	AssertInt(0, cA1->NumTos());
	AssertInt(0, cA2->NumTos());


	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectDehollowfication(void)
{
	CFileUtil							cFileUtil;
	CPointer						pPointer;
	CTestDoubleNamedString*				pcInternal;
	Ptr<CTestDoubleNamedString>	pDouble;
	Ptr<CTestNamedString>			pSingle;
	int									iClassSize;
	OIndex								oiOld;
	OIndex								oiNew;

	cFileUtil.RemoveDir("Output");
	cFileUtil.MakeDir("Output/Dehollowfication");
	ObjectsInit("Output/Dehollowfication");
	SetupObjectsForDehollowfication();
	gcObjects.Flush(TRUE, TRUE);
	AssertLongLongInt(9, gcObjects.NumDatabaseObjects());
	ObjectsKill();

	ObjectsInit("Output/Dehollowfication");
	SetupObjectsConstructors();
	AssertLongLongInt(9, gcObjects.NumDatabaseObjects());

	AssertTrue(gcObjects.Contains("Double"));

	pPointer = gcObjects.Get("Double");
	AssertNotNull(pPointer.Object());
	AssertString("CTestDoubleNamedString", pPointer.ClassName());

	pcInternal = (CTestDoubleNamedString*)pPointer.Object();
	AssertTrue(pcInternal->mpSplit1.IsNotNull());
	AssertTrue(pcInternal->mpSplit1.IsHollow());
	AssertTrue(pcInternal->mpSplit2.IsNotNull());
	AssertTrue(pcInternal->mpSplit2.IsHollow());

	pDouble = pPointer;

	oiOld = pDouble->mpSplit1.GetIndex();
	AssertTrue(pcInternal->mpSplit1.IsHollow());  //Making sure we haven't de-hollowed the object by calling GetIndex.

	//Problem - An oi of 1 is briefly assigned to the de-hollowed object and then it is reassigned back to its original value.
	iClassSize = pDouble->mpSplit1->ClassSize();  //The method call - ClassSize() - is irrelevant as long as the -> operator on mpSplit1 is invoked.
	AssertTrue(pcInternal->mpSplit1.IsNotNull());
	AssertFalse(pcInternal->mpSplit1.IsHollow());
	AssertInt(sizeof(CTestNamedString), iClassSize);
	AssertString("CTestNamedString", pcInternal->mpSplit1.ClassName());
	oiNew = pDouble->mpSplit1.GetIndex();
	AssertLongLongInt(oiOld, oiNew);

	pSingle = pDouble->mpSplit2;
	AssertTrue(pcInternal->mpSplit2.IsNotNull());
	AssertTrue(pcInternal->mpSplit2.IsHollow());

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectsFlushClearGetByOid(void)
{
	CFileUtil							cFileUtil;
	CPointer						cPointer;
	Ptr<CTestDoubleNamedString>	cDouble;
	Ptr<CRoot>						cRoot;

	cFileUtil.RemoveDir("Output");
	cFileUtil.MakeDir("Output/Dehollowfication");

	ObjectsInit("Output/Dehollowfication");
	SetupObjectsConstructors();
	
	cRoot = ORoot();
	cDouble = ONMalloc(CTestDoubleNamedString, "Double");
	cDouble->Init();
	cRoot->Add(cDouble);
	AssertLongLongInt(0, gcObjects.NumDatabaseObjects());
	cPointer = gcObjects.Get(3);
	AssertNotNull(cPointer.Object());
	AssertString("CTestDoubleNamedString", cPointer.ClassName());

	gcObjects.Flush(TRUE, TRUE);
	AssertLongLongInt(3, gcObjects.NumDatabaseObjects());

	cPointer = gcObjects.Get(3);
	AssertNotNull(cPointer.Object());
	AssertString("CTestDoubleNamedString", cPointer.ClassName());

	cPointer = gcObjects.Get("Double");
	AssertNotNull(cPointer.Object());
	AssertString("CTestDoubleNamedString", cPointer.ClassName());

	ObjectsKill();
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectsFlushClearGetByName(void)
{
	CFileUtil							cFileUtil;
	CPointer						cPointer;
	Ptr<CTestDoubleNamedString>	cDouble;
	Ptr<CRoot>						cRoot;

	cFileUtil.RemoveDir("Output");
	cFileUtil.MakeDir("Output/Dehollowfication");

	ObjectsInit("Output/Dehollowfication");
	SetupObjectsConstructors();

	cRoot = ORoot();
	cDouble = ONMalloc(CTestDoubleNamedString, "Double");
	cDouble->Init();
	cRoot->Add(cDouble);
	AssertLongLongInt(0, gcObjects.NumDatabaseObjects());
	AssertLongLongInt(0, gcObjects.NumDatabaseNames());
	cPointer = gcObjects.Get(3);
	AssertNotNull(cPointer.Object());
	AssertString("CTestDoubleNamedString", cPointer.ClassName());

	gcObjects.Flush(TRUE, TRUE);
	AssertLongLongInt(3, gcObjects.NumDatabaseObjects());
	AssertLongLongInt(2, gcObjects.NumDatabaseNames());

	cPointer = gcObjects.Get("Double");
	AssertNotNull(cPointer.Object());
	AssertString("CTestDoubleNamedString", cPointer.ClassName());

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjects(void)
{
	BeginTests();

	TestObjectsObjectKillInGraph();
	TestObjectsArrayKillInGraph();
	TestObjectsObjectKillInArrayInGraph();
	TestObjectsInMemoryIteration();
	TestObjectsObjectSave();
	TestObjectsFlushNoClear();
	TestObjectsFlushClearGetByOid();
	TestObjectsFlushClearGetByName();
	//TestObjectsFlushDurable();
	TestObjectsEvict();
	TestObjectDehollowfication();

	TestStatistics();
}

