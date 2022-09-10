#include "BaseLib/GlobalMemory.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/TypeNames.h"
#include "StandardLib/Set.h"
#include "StandardLib/Objects.h"
#include "StandardLib/PointerContainer.h"
#include "StandardLib/ExternalObjectDeserialiser.h"
#include "StandardLib/ExternalObjectSerialiser.h"
#include "StandardLib/ChunkFileObjectWriter.h"
#include "StandardLib/ChunkFileSystemObjectReader.h"
#include "TestLib/Assert.h"
#include "ObjectTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSetAddConstructors(void)
{
	gcObjects.AddConstructor<CTestSaveableObject1>();
	gcObjects.AddConstructor<CTestObject>();
	gcObjects.AddConstructor<CPointerContainer>();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSetAdd(void)
{
	ObjectsInit();

	Ptr<CSet<CTestSaveableObject1>> pacStuff = OMalloc<CSet<CTestSaveableObject1>>();
	pacStuff->Add(OMalloc<CTestSaveableObject1>());

	Ptr<CTestSaveableObject1> pSaveable = pacStuff->Get(0);
	AssertTrue(pSaveable.IsNotNull());
	AssertInt(7, pSaveable->miInt);

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSetGet(void)
{
	ObjectsInit();

	Ptr<CSet<CTestSaveableObject1>> pacStuff = OMalloc<CSet<CTestSaveableObject1>>();
	pacStuff->Add(OMalloc<CTestSaveableObject1>());
	Ptr<CTestSaveableObject1> pSaveable = OMalloc<CTestSaveableObject1>();
	pSaveable->miInt = 3;
	pacStuff->Add(pSaveable);

	AssertInt(2, pacStuff->NumElements());
	AssertInt(7, pacStuff->Get(0)->miInt);
	AssertInt(3, pacStuff->Get(1)->miInt);

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSetAddAll(void)
{
	ObjectsInit();

	Ptr<CSet<CTestSaveableObject1>> pacStuff = OMalloc<CSet<CTestSaveableObject1>>();
	pacStuff->Add(OMalloc<CTestSaveableObject1>());
	Ptr<CTestSaveableObject1> pSaveable = OMalloc<CTestSaveableObject1>();
	pSaveable->miInt = 3;
	pacStuff->Add(pSaveable);

	Ptr<CSet<CTestSaveableObject1>> pacMore = OMalloc<CSet<CTestSaveableObject1>>();
	pSaveable = OMalloc<CTestSaveableObject1>();
	pSaveable->miInt = 5;
	pacStuff->Add(pSaveable);

	pacMore->AddAll(pacStuff);

	AssertInt(3, pacMore->NumElements());
	AssertInt(7, pacMore->Get(0)->miInt);
	AssertInt(3, pacMore->Get(1)->miInt);
	AssertInt(5, pacMore->Get(2)->miInt);

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSetRemove(void)
{
	ObjectsInit();

	Ptr<CRoot> pRoot = ORoot();

	Ptr<CSet<CTestSaveableObject1>> pacStuff = OMalloc<CSet<CTestSaveableObject1>>();
	pRoot->Add(pacStuff);

	pacStuff->Add(OMalloc<CTestSaveableObject1>());
	Ptr<CTestSaveableObject1> pSaveable = OMalloc<CTestSaveableObject1>();
	pSaveable->miInt = 3;
	pacStuff->Add(pSaveable);
	pSaveable = OMalloc<CTestSaveableObject1>();
	pSaveable->miInt = 5;
	pacStuff->Add(pSaveable);

	pacStuff->Remove(pSaveable);

	AssertInt(2, pacStuff->NumElements());
	AssertInt(7, pacStuff->Get(0)->miInt);
	AssertInt(3, pacStuff->Get(1)->miInt);

	ObjectsFlush();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSetKillCyclic(void)
{
	ObjectsInit();

	Ptr<CTestObject>			pTest1;
	Ptr<CTestObject>			pTest2;
	Ptr<CTestObject>			pTest3;
	Ptr<CRoot>					pRoot;
	Ptr<CSetObject>				pSet;

	pTest1 = OMalloc<CTestObject>();
	pTest2 = OMalloc<CTestObject>();
	pTest1->mpTest = pTest2;
	pTest2->mpTest = pTest1;
	pTest3 = OMalloc<CTestObject>();
	pTest3->mpTest = pTest2;
	pSet = OMalloc<CSetObject>();
	pRoot = ORoot();
	pRoot->Add(pSet);
	pSet->Add(pTest3);

	AssertLongLongInt(6, gcObjects.NumMemoryIndexes());
	AssertInt(5, pTest1->GetDistToRoot());
	AssertInt(4, pTest2->GetDistToRoot());
	AssertInt(3, pTest3->GetDistToRoot());

	pSet->Kill();
	AssertLongLongInt(5, gcObjects.NumMemoryIndexes());
	AssertNull(&pSet);
	AssertInt(UNATTACHED_DIST_TO_ROOT, pTest1->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pTest2->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pTest3->GetDistToRoot());

	ObjectsFlush();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSetKillAll(void)
{
	ObjectsInit();

	Ptr<CPointerContainer>		pContainer1;
	Ptr<CPointerContainer>		pContainer2;
	Ptr<CTestObject>			pObject;
	Ptr<CRoot>					pRoot;
	Ptr<CSetObject>				pSet;

	pObject = OMalloc<CTestObject>();
	pContainer2 = OMalloc<CPointerContainer>(pObject);
	pContainer1 = OMalloc<CPointerContainer>(pContainer2);
	pSet = OMalloc<CSetObject>();
	pRoot = ORoot();
	pRoot->Add(pSet);
	pSet->Add(pContainer1);

	AssertLongLongInt(6, gcObjects.NumMemoryIndexes());
	AssertInt(1, pSet->NumElements());

	pSet->KillAll();
	AssertInt(0, pSet->NumElements());
	AssertLongLongInt(5, gcObjects.NumMemoryIndexes());
	AssertNotNull(&pSet);
	AssertNull(&pContainer1);
	AssertInt(UNATTACHED_DIST_TO_ROOT, pContainer2->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pObject->GetDistToRoot());

	pSet->Kill();

	ObjectsFlush();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSetRemoveAll(void)
{
	ObjectsInit();

	Ptr<CPointerContainer>		pContainer1;
	Ptr<CPointerContainer>		pContainer2;
	Ptr<CTestObject>			pObject;
	Ptr<CRoot>					pRoot;
	Ptr<CSetObject>				pSet;

	pObject = OMalloc<CTestObject>();
	pContainer2 = OMalloc<CPointerContainer>(pObject);
	pContainer1 = OMalloc<CPointerContainer>(pContainer2);
	pSet = OMalloc<CSetObject>();
	pRoot = ORoot();
	pRoot->Add(pSet);
	pSet->Add(pContainer1);

	AssertLongLongInt(6, gcObjects.NumMemoryIndexes());
	AssertInt(1, pSet->NumElements());

	pSet->RemoveAll();
	AssertInt(0, pSet->NumElements());
	AssertLongLongInt(6, gcObjects.NumMemoryIndexes());
	AssertNotNull(&pSet);
	AssertInt(UNATTACHED_DIST_TO_ROOT, pContainer1->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pContainer2->GetDistToRoot());
	AssertInt(UNATTACHED_DIST_TO_ROOT, pObject->GetDistToRoot());

	pSet->Kill();

	ObjectsFlush();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSetSerialisation()
{
	ObjectsInit();
	TestSetAddConstructors();

	Ptr<CPointerContainer>			pContainer1;
	Ptr<CPointerContainer>			pContainer2;
	Ptr<CTestObject>				pObject;
	Ptr<CSetObject>					pSet;
	CExternalObjectSerialiser		cSerialiser;
	CChunkFileObjectWriter			cWriter;
	CFileUtil						cFileUtil;
	bool							bResult;
	char							szDirectory[] = "Output" _FS_ "TestSet";
	CExternalObjectDeserialiser		cGraphDeserialiser;
	CChunkFileSystemObjectReader 	cReader;

	AssertTrue(cFileUtil.RemoveDir(szDirectory));
	AssertTrue(cFileUtil.TouchDir(szDirectory));

	pObject = OMalloc<CTestObject>();
	pContainer2 = OMalloc<CPointerContainer>(pObject);
	pContainer1 = OMalloc<CPointerContainer>(pContainer2);
	pSet = ONMalloc<CSetObject>("Burke");
	pSet->Add(pContainer1);
	pSet->Add(pContainer2);

	AssertLongLongInt(4, gcObjects.NumMemoryIndexes());
	AssertInt(2, pSet->NumElements());

	cWriter.Init(szDirectory, "", "File");
	cSerialiser.Init(&cWriter);
	bResult = cSerialiser.Write(&pSet);
	cSerialiser.Kill();
	cWriter.Kill();

	ObjectsKill();
	AssertNull(&pSet);
	ObjectsInit();

	cReader.Init(szDirectory, "File");
	cGraphDeserialiser.Init(&cReader, false, &gcObjects, gcObjects.GetMemory());
	pSet = cGraphDeserialiser.Read("Burke");
	AssertNotNull(&pSet);

	pSet = NULL;

	ObjectsKill();

	AssertTrue(cFileUtil.RemoveDir(szDirectory));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSet(void)
{
	BeginTests();
	MemoryInit();
	FastFunctionsInit();
	TypesInit();
	DataIOInit();

	TestSetAdd();
	TestSetGet();
	TestSetAddAll();
	TestSetSerialisation();
	TestSetRemove();
	TestSetKillCyclic();
	TestSetKillAll();
	TestSetRemoveAll();

	DataIOKill();
	TypesKill();
	FastFunctionsKill();
	MemoryKill();
	TestStatistics();
}

