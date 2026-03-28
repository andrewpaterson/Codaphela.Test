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
void TestIndexObjectDetachInHeap(void)
{
	ObjectsInit();

	{
		Ptr<CRoot>					pRoot;
		Ptr<CIndexObject>			pIndex;
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
void TestIndexObjectIterateSafeNull(void)
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
void TestIndexObjectIterateUnsafeNull(void)
{
	ObjectsInit();

	{
		Ptr<CRoot>						pRoot;
		Ptr<CIndexObject>				pIndex;
		Ptr<CTestObject>				pTest1;
		Ptr<CTestObject>				pTest2;
		Ptr<CTestObject>				pTest3;
		STestObjectFreedNotifier		sNotifier1;
		STestObjectFreedNotifier		sNotifier2;
		STestObjectFreedNotifier		sNotifier3;
		SIndexTreeMemoryUnsafeIterator	sIter;
		bool							bExists;
		CObject*						pcObject;

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

		bExists = pIndex->GetIndexForTesting()->StartIteration(&sIter, (CUnknown**)&pcObject);
		AssertTrue(bExists);
		AssertPointer(&pTest1, pcObject);

		bExists = pIndex->GetIndexForTesting()->Iterate(&sIter, (CUnknown**)&pcObject);
		AssertTrue(bExists);
		AssertNull(pcObject);

		bExists = pIndex->GetIndexForTesting()->Iterate(&sIter, (CUnknown**)&pcObject);
		AssertTrue(bExists);
		AssertPointer(&pTest2, pcObject);

		bExists = pIndex->GetIndexForTesting()->Iterate(&sIter, (CUnknown**)&pcObject);
		AssertTrue(bExists);
		AssertNull(pcObject);

		bExists = pIndex->GetIndexForTesting()->Iterate(&sIter, (CUnknown**)&pcObject);
		AssertTrue(bExists);
		AssertPointer(&pTest3, pcObject);

		bExists = pIndex->GetIndexForTesting()->Iterate(&sIter, (CUnknown**)&pcObject);
		AssertFalse(bExists);
		AssertNull(pcObject);
	}

	ObjectsFlush();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexObjectRemove(void)
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

		pIndex->Put("shnork", OMalloc<CTestObject>(&sNotifier3));
		pIndex->Put("shnerp", OMalloc<CTestObject>(&sNotifier2));
		pIndex->Put("booger", OMalloc<CTestObject>(&sNotifier1));
		AssertSize(3, pIndex->NumElements());
		AssertSize(6, gcObjects.NumMemoryIndexes());

		pIndex->Remove("shnerp");
		AssertSize(2, pIndex->NumElements());
		AssertSize(5, gcObjects.NumMemoryIndexes());
		AssertFalse(sNotifier1.bFreed);
		AssertTrue(sNotifier2.bFreed);
		AssertFalse(sNotifier3.bFreed);

		pTest1 = pIndex->Get("booger");
		pIndex->Remove("booger");
		AssertSize(1, pIndex->NumElements());
		AssertSize(5, gcObjects.NumMemoryIndexes());
		AssertFalse(sNotifier1.bFreed);
		AssertTrue(sNotifier2.bFreed);
		AssertFalse(sNotifier3.bFreed);
	}

	ObjectsFlush();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexObjectDetachOnStack(void)
{
	ObjectsInit();

	{
		STestObjectFreedNotifier		sNotifier1;
		STestObjectFreedNotifier		sNotifier2;
		STestObjectFreedNotifier		sNotifier3;
		bool							bExists;
		SIndexTreeMemoryUnsafeIterator	sIter;
		CTestObject*					pcObject;

		{
			CIndexObject			cIndex;

			cIndex.Init();
			cIndex.Put("shnork", OMalloc<CTestObject>(&sNotifier1));
			cIndex.Put("shnerp", OMalloc<CTestObject>(&sNotifier2));
			cIndex.Put("booger", OMalloc<CTestObject>(&sNotifier3));
			AssertFalse(sNotifier1.bFreed);
			AssertFalse(sNotifier2.bFreed);
			AssertFalse(sNotifier3.bFreed);
			AssertSize(3, cIndex.NumElements());
			AssertSize(3, gcObjects.NumMemoryIndexes());

			bExists = cIndex.GetIndexForTesting()->StartIteration(&sIter, (CUnknown**)&pcObject);
			while (bExists)
			{
				AssertIntHex(0x7070707, pcObject->mi);
				bExists = cIndex.GetIndexForTesting()->Iterate(&sIter, (CUnknown**)&pcObject);
			}
		}

		AssertSize(0, gcObjects.NumMemoryIndexes());
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
void TestIndexObjectGetPointerTos(void)
{
	ObjectsInit();

	{
		Ptr<CRoot>							pRoot;
		Ptr<CIndexObject>					pIndex;
		Ptr<CTestObject>					pTest1;
		Ptr<CTestObject>					pTest2;
		Ptr<CTestObject>					pTest3;
		STestObjectFreedNotifier			sNotifier1;
		STestObjectFreedNotifier			sNotifier2;
		STestObjectFreedNotifier			sNotifier3;
		CArrayTemplateEmbeddedObjectPtr		apcTos;

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

		apcTos.Init();
		pIndex->GetPointerTos(&apcTos);
		AssertSize(3, apcTos.NumElements());
		AssertTrue(apcTos.ContainsVoidPtr(&pTest1));
		AssertTrue(apcTos.ContainsVoidPtr(&pTest2));
		AssertTrue(apcTos.ContainsVoidPtr(&pTest3));
		apcTos.Kill();
	}

	ObjectsFlush();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexObjectPointerFromsHeap(void)
{
	ObjectsInit();

	{
		Ptr<CRoot>							pRoot;
		Ptr<CIndexObject>					pIndex;
		Ptr<CTestObject>					pTest1;
		Ptr<CTestObject>					pTest2;
		Ptr<CTestObject>					pTest3;
		STestObjectFreedNotifier			sNotifier1;
		STestObjectFreedNotifier			sNotifier2;
		STestObjectFreedNotifier			sNotifier3;

		pRoot = ORoot();
		pIndex = OMalloc<CIndexObject>();
		pRoot->Add(pIndex);

		pTest3 = OMalloc<CTestObject>(&sNotifier1);
		pTest2 = OMalloc<CTestObject>(&sNotifier2);
		pTest1 = OMalloc<CTestObject>(&sNotifier3);
		pIndex->Put("booger", pTest1);
		pIndex->Put("shnerp", pTest2);
		pIndex->Put("shnork", pTest3);
		AssertSize(1, pTest1->NumHeapFroms());
		AssertSize(1, pTest2->NumHeapFroms());
		AssertSize(1, pTest3->NumHeapFroms());
		AssertSize(3, pIndex->NumElements());

		pIndex->Remove("booger");
		AssertSize(0, pTest1->NumHeapFroms());
		AssertSize(1, pTest2->NumHeapFroms());
		AssertSize(1, pTest3->NumHeapFroms());
		AssertSize(2, pIndex->NumElements());

		pIndex->RemoveAll();
		AssertSize(0, pTest1->NumHeapFroms());
		AssertSize(0, pTest2->NumHeapFroms());
		AssertSize(0, pTest3->NumHeapFroms());
		AssertSize(0, pIndex->NumElements());

		pIndex->Put("abcde", pTest1);
		AssertSize(1, pTest1->NumHeapFroms());
		AssertSize(0, pTest2->NumHeapFroms());
		AssertSize(0, pTest3->NumHeapFroms());
		AssertSize(1, pIndex->NumElements());

		pIndex->Put("abcdf", pTest1);
		AssertSize(2, pTest1->NumHeapFroms());
		AssertSize(0, pTest2->NumHeapFroms());
		AssertSize(0, pTest3->NumHeapFroms());
		AssertSize(2, pIndex->NumElements());

		pIndex->Remove("abcde");
		AssertSize(1, pTest1->NumHeapFroms());
		AssertSize(0, pTest2->NumHeapFroms());
		AssertSize(0, pTest3->NumHeapFroms());
		AssertSize(1, pIndex->NumElements());

		pIndex->Remove("abcdf");
		AssertSize(0, pTest1->NumHeapFroms());
		AssertSize(0, pTest2->NumHeapFroms());
		AssertSize(0, pTest3->NumHeapFroms());
		AssertSize(0, pIndex->NumElements());
	}

	ObjectsFlush();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexObjectPointerFromsStack(void)
{
	ObjectsInit();

	{
		CIndexObject						cIndex;
		Ptr<CTestObject>					pTest1;
		Ptr<CTestObject>					pTest2;
		Ptr<CTestObject>					pTest3;
		STestObjectFreedNotifier			sNotifier1;
		STestObjectFreedNotifier			sNotifier2;
		STestObjectFreedNotifier			sNotifier3;

		gcObjects.ValidateObjectsConsistency();

		cIndex.Init();
		pTest3 = OMalloc<CTestObject>(&sNotifier1);
		pTest2 = OMalloc<CTestObject>(&sNotifier2);
		pTest1 = OMalloc<CTestObject>(&sNotifier3);
		cIndex.Put("booger", pTest1);
		cIndex.Put("shnerp", pTest2);
		cIndex.Put("shnork", pTest3);
		AssertSize(2, pTest1->NumStackFroms());
		AssertSize(2, pTest2->NumStackFroms());
		AssertSize(2, pTest3->NumStackFroms());
		AssertSize(3, cIndex.NumElements());

		cIndex.Remove("booger");
		AssertSize(1, pTest1->NumStackFroms());
		AssertSize(2, pTest2->NumStackFroms());
		AssertSize(2, pTest3->NumStackFroms());
		AssertSize(2, cIndex.NumElements());

		cIndex.RemoveAll();
		AssertSize(1, pTest1->NumStackFroms());
		AssertSize(1, pTest2->NumStackFroms());
		AssertSize(1, pTest3->NumStackFroms());
		AssertSize(0, cIndex.NumElements());

		cIndex.Put("abcde", pTest1);
		AssertSize(2, pTest1->NumStackFroms());
		AssertSize(1, pTest2->NumStackFroms());
		AssertSize(1, pTest3->NumStackFroms());
		AssertSize(1, cIndex.NumElements());

		cIndex.Put("abcdf", pTest1);
		AssertSize(3, pTest1->NumStackFroms());
		AssertSize(1, pTest2->NumStackFroms());
		AssertSize(1, pTest3->NumStackFroms());
		AssertSize(2, cIndex.NumElements());

		cIndex.Remove("abcde");
		AssertSize(2, pTest1->NumStackFroms());
		AssertSize(1, pTest2->NumStackFroms());
		AssertSize(1, pTest3->NumStackFroms());
		AssertSize(1, cIndex.NumElements());

		cIndex.Remove("abcdf");
		AssertSize(1, pTest1->NumStackFroms());
		AssertSize(1, pTest2->NumStackFroms());
		AssertSize(1, pTest3->NumStackFroms());
		AssertSize(0, cIndex.NumElements());

		pTest1 = NULL;
		pTest2 = NULL;
		pTest3 = NULL;
	}

	ObjectsFlush();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexObjectPutOverwrite(void)
{
	ObjectsInit();

	{
		Ptr<CRoot>							pRoot;
		Ptr<CIndexObject>					pIndex;
		Ptr<CTestObject>					pTest1;
		Ptr<CTestObject>					pTest2;
		STestObjectFreedNotifier			sNotifier1;
		STestObjectFreedNotifier			sNotifier2;
		bool								bResult;

		pRoot = ORoot();
		pIndex = OMalloc<CIndexObject>();
		pRoot->Add(pIndex);

		pTest2 = OMalloc<CTestObject>(&sNotifier2);
		pTest1 = OMalloc<CTestObject>(&sNotifier1);
		bResult = pIndex->Put("1", pTest2);
		gcObjects.ValidateObjectsConsistency();
		AssertTrue(bResult);
		AssertSize(1, pIndex->NumElements());
		AssertSize(5, gcObjects.NumMemoryIndexes());

		bResult = pIndex->Put("1", pTest1);
		gcObjects.ValidateObjectsConsistency();
		AssertTrue(bResult);
		AssertSize(1, pIndex->NumElements());
		AssertSize(5, gcObjects.NumMemoryIndexes());
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

	TestIndexObjectPut();
	TestIndexObjectDetachInHeap();
	TestIndexObjectIterateSafeNull();
	TestIndexObjectIterateUnsafeNull();
	TestIndexObjectRemove();
	TestIndexObjectDetachOnStack();
	TestIndexObjectGetPointerTos();
	TestIndexObjectPointerFromsHeap();
	TestIndexObjectPointerFromsStack();
	TestIndexObjectPutOverwrite();

	DataIOKill();
	TypesKill();
	MemoryKill();
	TestStatistics();
}

