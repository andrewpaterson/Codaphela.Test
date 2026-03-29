#include "BaseLib/GlobalMemory.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/TypeNames.h"
#include "StandardLib/ArrayObject.h"
#include "StandardLib/Objects.h"
#include "StandardLib/ExternalObjectDeserialiser.h"
#include "StandardLib/ExternalObjectSerialiser.h"
#include "StandardLib/ChunkFileObjectWriter.h"
#include "StandardLib/ChunkFileSystemObjectReader.h"
#include "StandardLib/PointerContainer.h"
#include "TestLib/Assert.h"
#include "ObjectTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayAddConstructors(void)
{
	gcObjects.AddConstructor<CTestSaveableObject1>();
	gcObjects.AddConstructor<CTestObject>();
	gcObjects.AddConstructor<CPointerContainer>();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayAdd(void)
{
	ObjectsInit();

	Ptr<CArray<CTestSaveableObject1>> pacStuff = OMalloc<CArray<CTestSaveableObject1>>();
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
void TestArrayGet(void)
{
	ObjectsInit();

	Ptr<CArray<CTestSaveableObject1>> pacStuff = OMalloc<CArray<CTestSaveableObject1>>();
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
void TestArrayInsert(void)
{
	ObjectsInit();

	Ptr<CArray<CTestSaveableObject1>> pacStuff = OMalloc<CArray<CTestSaveableObject1>>();
	pacStuff->Add(OMalloc<CTestSaveableObject1>());
	Ptr<CTestSaveableObject1> pSaveable = OMalloc<CTestSaveableObject1>();
	pSaveable->miInt = 3;
	pacStuff->Insert(0, pSaveable);

	AssertInt(2, pacStuff->NumElements());
	AssertInt(3, pacStuff->Get(0)->miInt);
	AssertInt(7, pacStuff->Get(1)->miInt);

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayAddAll(void)
{
	ObjectsInit();

	Ptr<CArray<CTestSaveableObject1>> pacStuff = OMalloc<CArray<CTestSaveableObject1>>();
	pacStuff->Add(OMalloc<CTestSaveableObject1>());
	Ptr<CTestSaveableObject1> pSaveable = OMalloc<CTestSaveableObject1>();
	pSaveable->miInt = 3;
	pacStuff->Insert(0, pSaveable);

	Ptr<CArray<CTestSaveableObject1>> pacMore = OMalloc<CArray<CTestSaveableObject1>>();
	pSaveable = OMalloc<CTestSaveableObject1>();
	pSaveable->miInt = 5;

	AssertInt(0, pSaveable->NumHeapFroms());
	pacStuff->Insert(0, pSaveable);
	AssertInt(1, pSaveable->NumHeapFroms());
	gcObjects.ValidateObjectsConsistency();

	pacMore->AddAll(pacStuff);

	AssertInt(3, pacMore->NumElements());
	AssertInt(5, pacMore->Get(0)->miInt);
	AssertInt(3, pacMore->Get(1)->miInt);
	AssertInt(7, pacMore->Get(2)->miInt);

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayRemove(void)
{
	ObjectsInit();

	Ptr<CRoot> pRoot = ORoot();

	Ptr<CArray<CTestSaveableObject1>> pacStuff = OMalloc<CArray<CTestSaveableObject1>>();
	pRoot->Add(pacStuff);

	pacStuff->Add(OMalloc<CTestSaveableObject1>());
	Ptr<CTestSaveableObject1> pSaveable = OMalloc<CTestSaveableObject1>();
	pSaveable->miInt = 3;
	pacStuff->Insert(0, pSaveable);
	pSaveable = OMalloc<CTestSaveableObject1>();
	pSaveable->miInt = 5;
	pacStuff->Insert(0, pSaveable);

	pacStuff->RemoveAt(1);

	AssertInt(2, pacStuff->NumElements());
	AssertInt(5, pacStuff->Get(0)->miInt);
	AssertInt(7, pacStuff->Get(1)->miInt);

	ObjectsFlush();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArraySneakyOnStack(void)
{
	ObjectsInit();

	CTestObject					aArray;
	STestObjectFreedNotifier	sFreed;
	SStackPointer*				psPointer;
	CBaseObject*				pcObject;

	AssertSize(0, gcStackPointers.NumElements());

	Ptr<CTestSimpleObject> pTestObject = OMalloc<CTestSimpleObject>(&sFreed, 23);
	AssertSize(1, gcStackPointers.NumElements());
	psPointer = gcStackPointers.Get(0);
	AssertTrue(psPointer->meType == SPT_Pointer);
	pcObject = psPointer->u.pcPointer->BaseObject();
	//The pointer 'pTestObject' is on the stack and pointes to a CTestSimpleObject.
	AssertPointer(pTestObject.BaseObject(), pcObject);

	AssertSize(1, gcStackPointers.NumElements());
	aArray.Init(pTestObject, NULL);
	AssertSize(2, gcStackPointers.NumElements());

	AssertFalse(sFreed.bFreed);
	pTestObject = NULL;
	AssertFalse(sFreed.bFreed);
	AssertSize(1, gcStackPointers.NumElements());

	aArray.Kill();
	AssertSize(0, gcStackPointers.NumElements());
	AssertTrue(sFreed.bFreed);

	ObjectsFlush();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayOnStackKill(void)
{
	ObjectsInit();

	CArray<CTestSimpleObject>	aArray;
	STestObjectFreedNotifier	sFreed;
	SStackPointer*				psPointer;
	CBaseObject*				pcObject;

	AssertSize(0, gcStackPointers.NumElements());

	Ptr<CTestSimpleObject> pTestObject = OMalloc<CTestSimpleObject>(&sFreed, 23);
	AssertSize(1, gcStackPointers.NumElements());
	psPointer = gcStackPointers.Get(0);
	AssertTrue(psPointer->meType == SPT_Pointer);
	pcObject = psPointer->u.pcPointer->BaseObject();
	//The pointer 'pTestObject' is on the stack and pointes to a CTestSimpleObject.
	AssertPointer(pTestObject.BaseObject(), pcObject);

	AssertSize(1, gcStackPointers.NumElements());
	aArray.Init();
	aArray.Add(pTestObject);
	AssertSize(2, gcStackPointers.NumElements());

	AssertFalse(sFreed.bFreed);
	pTestObject = NULL;
	AssertFalse(sFreed.bFreed);
	AssertSize(1, gcStackPointers.NumElements());

	aArray.Kill();
	AssertSize(0, gcStackPointers.NumElements());
	AssertTrue(sFreed.bFreed);

	ObjectsFlush();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayOnStackRemoveObject(void)
{
	ObjectsInit();

	CArray<CTestSimpleObject>	aArray;
	STestObjectFreedNotifier	sFreed;
	SStackPointer*				psPointer;
	CBaseObject*				pcObject;

	AssertSize(0, gcStackPointers.NumElements());
	AssertSize(0, gcObjects.NumMemoryIndexes());

	Ptr<CTestSimpleObject> pTestObject = OMalloc<CTestSimpleObject>(&sFreed, 23);
	AssertSize(1, gcStackPointers.NumElements());
	AssertSize(1, gcObjects.NumMemoryIndexes());
	psPointer = gcStackPointers.Get(0);
	AssertTrue(psPointer->meType == SPT_Pointer);
	pcObject = psPointer->u.pcPointer->BaseObject();
	//The pointer 'pTestObject' is on the stack and pointes to a CTestSimpleObject.
	AssertPointer(pTestObject.BaseObject(), pcObject);

	AssertSize(1, gcStackPointers.NumElements());
	aArray.Init();
	AssertSize(1, gcStackPointers.NumElements());
	aArray.Add(pTestObject);
	AssertSize(2, gcStackPointers.NumElements());
	AssertSize(1, aArray.NumElements());
	AssertSize(1, gcObjects.NumMemoryIndexes());

	aArray.Remove(pTestObject);
	AssertSize(1, gcStackPointers.NumElements());
	AssertSize(0, aArray.NumElements());
	AssertSize(1, gcObjects.NumMemoryIndexes());
	AssertFalse(sFreed.bFreed);

	pTestObject = NULL;
	AssertTrue(sFreed.bFreed);
	AssertSize(0, gcStackPointers.NumElements());
	AssertSize(0, gcObjects.NumMemoryIndexes());

	aArray.Kill();
	AssertSize(0, gcStackPointers.NumElements());

	ObjectsFlush();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayConstructorExists(void)
{
	CConstructors*	pcConstructors;
	CArrayObject*	pcArray;

	ObjectsInit();

	pcConstructors = gcObjects.GetConstructors();
	pcArray = pcConstructors->Get<CArrayObject>();
	AssertNotNull(pcArray);
	AssertString("CArrayObject", pcArray->ClassName());

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayClassExists(void)
{
	CClasses*		pcClasses;
	CClass*			pcClass;

	ObjectsInit();

	CArrayObject	cArray;

	pcClasses = gcObjects.GetClasses();
	pcClass = pcClasses->Get(cArray.ClassName());
	AssertNotNull(pcClass);
	AssertString("CArrayObject", pcClass->GetName());

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArraySerialisation(void)
{
	CFileUtil	cFileUtil;
	bool		bResult;
	char		szDirectory[] = "Output" _FS_ "TestArray";

	AssertTrue(cFileUtil.RemoveDir(szDirectory));
	AssertTrue(cFileUtil.TouchDir(szDirectory));

	ObjectsInit();
	TestArrayAddConstructors();
	{
		Ptr<CPointerContainer>			pContainer1;
		Ptr<CPointerContainer>			pContainer2;
		Ptr<CPointerContainer>			pContainer3;
		Ptr<CTestObject>				pObject;
		Ptr<CArrayObject>				pArray;
		CExternalObjectSerialiser		cSerialiser;
		CChunkFileObjectWriter			cWriter;
		CExternalObjectDeserialiser		cDeserialiser;
		CChunkFileSystemObjectReader 	cReader;

		pObject = OMalloc<CTestObject>();
		pContainer2 = OMalloc<CPointerContainer>(pObject);
		pContainer1 = OMalloc<CPointerContainer>(pContainer2);
		pContainer3 = OMalloc<CPointerContainer>(Null());
		pArray = ONMalloc<CArrayObject>("Orbis");
		pArray->Add(pContainer1);
		pArray->Add(pContainer2);
		pArray->Add(pContainer3);

		AssertLong(5, gcObjects.NumMemoryIndexes());
		AssertInt(3, pArray->NumElements());

		cWriter.Init(szDirectory, "", "File");
		cSerialiser.Init(&cWriter);
		bResult = cSerialiser.Write(&pArray);
		cSerialiser.Kill();
		cWriter.Kill();
	}
	ObjectsKill();
	ObjectsInit();
	{
		CPointer						pPointer1;
		CPointer						pPointer2;
		CPointer						pPointer3;
		CPointer						pPointer4;
		Ptr<CArrayObject>				pArray;
		CChunkFileObjectWriter			cWriter;
		CExternalObjectDeserialiser		cDeserialiser;
		CChunkFileSystemObjectReader 	cReader;

		cReader.Init(szDirectory, "File");
		cDeserialiser.Init(&cReader, false, &gcObjects);
		pArray = cDeserialiser.Read("Orbis");
		AssertNotNull(&pArray);
		pPointer1 = pArray->Get(0);
		pPointer2 = pArray->Get(1);
		pPointer3 = pArray->Get(2);
		AssertTrue(pPointer1.IsNotNull());
		AssertTrue(pPointer2.IsNotNull());
		AssertTrue(pPointer3.IsNotNull());
		AssertString("CPointerContainer", pPointer1->ClassName());
		AssertString("CPointerContainer", pPointer2->ClassName());
		AssertString("CPointerContainer", pPointer3->ClassName());

		Ptr<CPointerContainer>			pContainer1;
		Ptr<CPointerContainer>			pContainer2;
		Ptr<CPointerContainer>			pContainer3;
		Ptr<CTestObject>				pObject;
		pContainer1 = pPointer1;
		pContainer2 = pPointer2;
		pContainer3 = pPointer3;
		AssertTrue(pContainer1->mp.IsNotNull());
		AssertTrue(pContainer2->mp.IsNotNull());
		AssertTrue(pContainer3->mp.IsNull());
		AssertString("CPointerContainer", pContainer1->mp->ClassName());
		AssertString("CTestObject", pContainer2->mp->ClassName());
		AssertPointer(&pContainer1->mp, &pContainer2);
		
		cDeserialiser.Kill();
		cReader.Kill();

		pArray = NULL;
	}
	ObjectsFlush();
	ObjectsKill();

	AssertTrue(cFileUtil.RemoveDir(szDirectory));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArray(void)
{
	BeginTests();
	MemoryInit();
	FastFunctionsInit();
	TypesInit();
	DataIOInit();

	TestArrayAdd();
	TestArrayGet();
	TestArrayInsert();
	TestArrayAddAll();
	TestArrayRemove();
	TestArraySneakyOnStack();
	TestArrayOnStackKill();
	TestArrayOnStackRemoveObject();
	TestArrayConstructorExists();
	TestArrayClassExists();
	TestArraySerialisation();

	DataIOKill();
	TypesKill();
	FastFunctionsKill();
	MemoryKill();
	TestStatistics();
}

