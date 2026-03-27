#include "BaseLib/GlobalMemory.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/TypeNames.h"
#include "StandardLib/IndexObject.h"
#include "StandardLib/Objects.h"
#include "TestLib/Assert.h"
#include "ObjectTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexObjectPut(void)
{
	ObjectsInit();

	{
		Ptr<CRoot>					pRoot;
		Ptr<CIndexObject>			pIndex;
		Ptr<CTestObject>			pTest1;
		Ptr<CTestObject>			pTest2;
		Ptr<CTestObject>			pTest3;
		STestObjectFreedNotifier	sNotifier1;
		STestObjectFreedNotifier	sNotifier2;
		STestObjectFreedNotifier	sNotifier3;

		pRoot = ORoot();
		pIndex = OMalloc<CIndexObject>();
		pRoot->Add(pIndex);

		pIndex->Put("shnork", OMalloc<CTestObject>(&sNotifier1));
		pIndex->Put("shnerp", OMalloc<CTestObject>(&sNotifier2));
		pIndex->Put("booger", OMalloc<CTestObject>(&sNotifier3));

		AssertSize(3, pIndex->NumElements());
		AssertSize(6, gcObjects.NumMemoryIndexes());

		pIndex = NULL;
		AssertSize(6, gcObjects.NumMemoryIndexes());

		pIndex = pRoot->GetFirst<CIndexObject>();
		pTest1 = pIndex->Get("booger");
		AssertPointer(&sNotifier3, pTest1->mpsFreedNotifier);
		pTest2 = pIndex->Get("shnerp");
		AssertPointer(&sNotifier2, pTest2->mpsFreedNotifier);
		pTest3 = pIndex->Get("shnork");
		AssertPointer(&sNotifier1, pTest3->mpsFreedNotifier);
	}

	ObjectsFlush();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexObjectDetach(void)
{
	ObjectsInit();

	{
		Ptr<CRoot>					pRoot;
		Ptr<CIndexObject>			pIndex;
		Ptr<CTestObject>			pTest1;
		Ptr<CTestObject>			pTest2;
		Ptr<CTestObject>			pTest3;
		STestObjectFreedNotifier	sNotifier1;
		STestObjectFreedNotifier	sNotifier2;
		STestObjectFreedNotifier	sNotifier3;

		pRoot = ORoot();
		pIndex = OMalloc<CIndexObject>();
		pRoot->Add(pIndex);

		pIndex->Put("shnork", OMalloc<CTestObject>(&sNotifier1));
		pIndex->Put("shnerp", OMalloc<CTestObject>(&sNotifier2));
		pIndex->Put("booger", OMalloc<CTestObject>(&sNotifier3));
		AssertFalse(sNotifier1.bFreed);
		AssertFalse(sNotifier2.bFreed);
		AssertFalse(sNotifier3.bFreed);

		AssertSize(3, pIndex->NumElements());
		AssertSize(6, gcObjects.NumMemoryIndexes());


		pRoot->RemoveAll();
		pIndex = NULL;
		AssertSize(2, gcObjects.NumMemoryIndexes());
		AssertTrue(sNotifier1.bFreed);
		AssertTrue(sNotifier2.bFreed);
		AssertTrue(sNotifier3.bFreed);
	}

	ObjectsFlush();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexObjectIterateNull(void)
{
	ObjectsInit();

	{
		Ptr<CRoot>					pRoot;
		Ptr<CIndexObject>			pIndex;
		Ptr<CTestObject>			pTest1;
		Ptr<CTestObject>			pTest2;
		Ptr<CTestObject>			pTest3;
		STestObjectFreedNotifier	sNotifier1;
		STestObjectFreedNotifier	sNotifier2;
		STestObjectFreedNotifier	sNotifier3;
		SIndexTreeMemoryIterator	sIter;
		uint8						auiKey[8];
		size						uiKeySize;
		bool						bExists;
		CPointer					pPtr;

		pRoot = ORoot();
		pIndex = OMalloc<CIndexObject>();
		pRoot->Add(pIndex);

		pTest3 = OMalloc<CTestObject>(&sNotifier1);
		pTest2 = OMalloc<CTestObject>(&sNotifier2);
		pTest1 = OMalloc<CTestObject>(&sNotifier3);
		pIndex->Put("shnork", pTest3);
		pIndex->Put("shniqu", Null<CObject>());
		pIndex->Put("shnerp", pTest2);
		pIndex->Put("booger", pTest1);
		pIndex->Put("bozzul", Null<CObject>());

		AssertSize(5, pIndex->NumElements());
		AssertSize(6, gcObjects.NumMemoryIndexes());

		memset(auiKey, 0, 8);
		pPtr = pIndex->StartIteration(&sIter, auiKey, &uiKeySize, 8, &bExists);
		AssertTrue(bExists);
		AssertString("booger", auiKey);
		AssertPointer(&pTest1, &pPtr);

		memset(auiKey, 0, 8);
		pPtr = pIndex->Iterate(&sIter, auiKey, &uiKeySize, 8, &bExists);
		AssertTrue(bExists);
		AssertString("bozzul", auiKey);
		AssertNull(&pPtr);

		memset(auiKey, 0, 8);
		pPtr = pIndex->Iterate(&sIter, auiKey, &uiKeySize, 8, &bExists);
		AssertTrue(bExists);
		AssertString("shnerp", auiKey);
		AssertPointer(&pTest2, &pPtr);

		memset(auiKey, 0, 8);
		pPtr = pIndex->Iterate(&sIter, auiKey, &uiKeySize, 8, &bExists);
		AssertTrue(bExists);
		AssertString("shniqu", auiKey);
		AssertNull(&pPtr);

		memset(auiKey, 0, 8);
		pPtr = pIndex->Iterate(&sIter, auiKey, &uiKeySize, 8, &bExists);
		AssertTrue(bExists);
		AssertString("shnork", auiKey);
		AssertPointer(&pTest3, &pPtr);

		memset(auiKey, 0, 8);
		pPtr = pIndex->Iterate(&sIter, auiKey, &uiKeySize, 8, &bExists);
		AssertFalse(bExists);
		AssertNull(&pPtr);
	}

	ObjectsFlush();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexObject(void)
{
	BeginTests();
	MemoryInit();
	TypesInit();
	DataIOInit();

	//TestIndexObjectPut();
	//TestIndexObjectDetach();
	TestIndexObjectIterateNull();

	DataIOKill();
	TypesKill();
	MemoryKill();
	TestStatistics();
}

