#include "BaseLib/GlobalMemory.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/TypeNames.h"
#include "BaseLib/DataOrderers.h"
#include "StandardLib/MapObject.h"
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
void TestMapObjectAddConstructors(void)
{
	gcObjects.AddConstructor<CTestSaveableObject1>();
	gcObjects.AddConstructor<CTestObject>();
	gcObjects.AddConstructor<CPointerContainer>();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapObjectPut(void)
{
	ObjectsInit();
	{
		Ptr<CRoot>					pRoot;
		Ptr<CMapObject>				pMap;
		Ptr<CTestObject>			pKey1;
		Ptr<CTestObject>			pKey2;
		Ptr<CTestObject>			pKey3;
		Ptr<CTestObject>			pValue1;
		Ptr<CTestObject>			pValue2;
		Ptr<CTestObject>			pValue3;
		STestObjectFreedNotifier	sNotifier1;
		STestObjectFreedNotifier	sNotifier2;
		STestObjectFreedNotifier	sNotifier3;
		STestObjectFreedNotifier	sNotifier4;
		STestObjectFreedNotifier	sNotifier5;
		STestObjectFreedNotifier	sNotifier6;

		pRoot = ORoot();
		pMap = OMalloc<CMapObject>();
		pRoot->Add(pMap);

		pKey1 = ONMalloc<CTestObject>("shnork", &sNotifier4);
		pKey2 = ONMalloc<CTestObject>("shnerp", &sNotifier5);
		pKey3 = ONMalloc<CTestObject>("booger", &sNotifier6);
		pMap->Put(pKey1, OMalloc<CTestObject>(&sNotifier1));
		pMap->Put(pKey2, OMalloc<CTestObject>(&sNotifier2));
		pMap->Put(pKey3, OMalloc<CTestObject>(&sNotifier3));

		AssertSize(3, pMap->NumElements());
		AssertSize(9, gcObjects.NumMemoryIndexes());

		pMap = NULL;
		AssertSize(9, gcObjects.NumMemoryIndexes());

		pMap = pRoot->GetFirst<CMapObject>();
		pValue1 = pMap->Get(pKey3);
		AssertPointer(&sNotifier3, pValue1->mpsFreedNotifier);
		pValue2 = pMap->Get(pKey2);
		AssertPointer(&sNotifier2, pValue2->mpsFreedNotifier);
		pValue3 = pMap->Get(pKey1);
		AssertPointer(&sNotifier1, pValue3->mpsFreedNotifier);
	}
	ObjectsFlush();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapObjectDetachInHeap(void)
{
	ObjectsInit();
	{
		Ptr<CRoot>					pRoot;
		Ptr<CMapObject>				pMap;
		STestObjectFreedNotifier	sNotifier1;
		STestObjectFreedNotifier	sNotifier2;
		STestObjectFreedNotifier	sNotifier3;
		STestObjectFreedNotifier	sNotifier4;
		STestObjectFreedNotifier	sNotifier5;
		STestObjectFreedNotifier	sNotifier6;

		pRoot = ORoot();
		pMap = OMalloc<CMapObject>();
		pRoot->Add(pMap);

		pMap->Put(ONMalloc<CTestObject>("shnork", &sNotifier4), OMalloc<CTestObject>(&sNotifier1));
		pMap->Put(ONMalloc<CTestObject>("shnerp", &sNotifier5), OMalloc<CTestObject>(&sNotifier2));
		pMap->Put(ONMalloc<CTestObject>("booger", &sNotifier6), OMalloc<CTestObject>(&sNotifier3));
		AssertFalse(sNotifier1.bFreed);
		AssertFalse(sNotifier2.bFreed);
		AssertFalse(sNotifier3.bFreed);
		AssertFalse(sNotifier4.bFreed);
		AssertFalse(sNotifier5.bFreed);
		AssertFalse(sNotifier6.bFreed);

		AssertSize(3, pMap->NumElements());
		AssertSize(9, gcObjects.NumMemoryIndexes());

		pRoot->RemoveAll();
		pMap = NULL;
		AssertSize(2, gcObjects.NumMemoryIndexes());
		AssertTrue(sNotifier1.bFreed);
		AssertTrue(sNotifier2.bFreed);
		AssertTrue(sNotifier3.bFreed);
		AssertTrue(sNotifier4.bFreed);
		AssertTrue(sNotifier5.bFreed);
		AssertTrue(sNotifier6.bFreed);
	}
	ObjectsFlush();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapObjectIterate(void)
{
	ObjectsInit();
	{
		Ptr<CRoot>					pRoot;
		Ptr<CMapObject>				pMap;
		Ptr<CTestObject>			pValue1;
		Ptr<CTestObject>			pValue2;
		Ptr<CTestObject>			pValue3;
		Ptr<CTestObject>			pKey1;
		Ptr<CTestObject>			pKey2;
		Ptr<CTestObject>			pKey3;
		Ptr<CTestObject>			pKey4;
		Ptr<CTestObject>			pKey5;
		STestObjectFreedNotifier	sNotifier1;
		STestObjectFreedNotifier	sNotifier2;
		STestObjectFreedNotifier	sNotifier3;
		STestObjectFreedNotifier	sNotifier4;
		STestObjectFreedNotifier	sNotifier5;
		STestObjectFreedNotifier	sNotifier6;
		STestObjectFreedNotifier	sNotifier7;
		STestObjectFreedNotifier	sNotifier8;
		SMapIterator				sIter;
		CMapEntry					cEntry;

		pRoot = ORoot();
		pMap = OMalloc<CMapObject>();
		pRoot->Add(pMap);

		pValue3 = OMalloc<CTestObject>(&sNotifier1);
		pValue2 = OMalloc<CTestObject>(&sNotifier2);
		pValue1 = OMalloc<CTestObject>(&sNotifier3);
		pKey1 = ONMalloc<CTestObject>("shnork", &sNotifier4);
		pKey2 = ONMalloc<CTestObject>("shniqu", &sNotifier5);
		pKey3 = ONMalloc<CTestObject>("shnerp", &sNotifier6);
		pKey4 = ONMalloc<CTestObject>("booger", &sNotifier7);
		pKey5 = ONMalloc<CTestObject>("bozzul", &sNotifier8);
		pMap->Put(pKey1, pValue3);
		pMap->Put(pKey2, Null<CObject>());
		pMap->Put(pKey3, pValue2);
		pMap->Put(pKey4, pValue1);
		pMap->Put(pKey5, Null<CObject>());

		AssertSize(5, pMap->NumElements());
		AssertSize(6, gcObjects.NumMemoryIndexes());

		cEntry = pMap->StartIteration(&sIter);
		AssertTrue(cEntry.Exists());
		AssertString("booger", cEntry.mpKey.GetName());
		AssertPointer(&pValue1, &cEntry.Value());

		cEntry = pMap->StartIteration(&sIter);		
		AssertTrue(cEntry.Exists());
		AssertString("bozzul", cEntry.mpKey.GetName());
		AssertNull(&cEntry.Value());

		cEntry = pMap->StartIteration(&sIter);
		AssertTrue(cEntry.Exists());
		AssertString("shnerp", cEntry.mpKey.GetName());
		AssertPointer(&pValue2, &cEntry.Value());

		cEntry = pMap->StartIteration(&sIter);
		AssertTrue(cEntry.Exists());
		AssertString("shniqu", cEntry.mpKey.GetName());
		AssertNull(&cEntry.Value());

		cEntry = pMap->StartIteration(&sIter);
		AssertTrue(cEntry.Exists());
		AssertString("shnork", cEntry.mpKey.GetName());
		AssertPointer(&pValue3, &cEntry.Value());

		cEntry = pMap->StartIteration(&sIter);
		AssertFalse(cEntry.Exists());
	}
	ObjectsFlush();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapObjectRemove(void)
{
	ObjectsInit();
	{
		Ptr<CRoot>					pRoot;
		Ptr<CMapObject>				pMap;
		Ptr<CTestObject>			pKey1;
		Ptr<CTestObject>			pKey2;
		Ptr<CTestObject>			pKey3;
		Ptr<CTestObject>			pValue1;
		Ptr<CTestObject>			pValue2;
		Ptr<CTestObject>			pValue3;
		STestObjectFreedNotifier	sNotifier1;
		STestObjectFreedNotifier	sNotifier2;
		STestObjectFreedNotifier	sNotifier3;
		STestObjectFreedNotifier	sNotifier4;
		STestObjectFreedNotifier	sNotifier5;
		STestObjectFreedNotifier	sNotifier6;

		pRoot = ORoot();
		pMap = OMalloc<CMapObject>();
		pRoot->Add(pMap);

		pKey1 = ONMalloc<CTestObject>("shnork", &sNotifier4);
		pKey2 = ONMalloc<CTestObject>("shnerp", &sNotifier5);
		pKey3 = ONMalloc<CTestObject>("booger", &sNotifier6);
		pMap->Put(pKey1, OMalloc<CTestObject>(&sNotifier3));
		pMap->Put(pKey2, OMalloc<CTestObject>(&sNotifier2));
		pMap->Put(pKey3, OMalloc<CTestObject>(&sNotifier1));

		AssertSize(3, pMap->NumElements());
		AssertSize(6, gcObjects.NumMemoryIndexes());

		pMap->Remove(pKey2);
		AssertSize(2, pMap->NumElements());
		AssertSize(5, gcObjects.NumMemoryIndexes());
		AssertFalse(sNotifier1.bFreed);
		AssertTrue(sNotifier2.bFreed);
		AssertFalse(sNotifier3.bFreed);
		AssertFalse(sNotifier4.bFreed);
		AssertTrue(sNotifier5.bFreed);
		AssertFalse(sNotifier6.bFreed);

		pValue1 = pMap->Get(pKey3);
		pMap->Remove(pKey3);
		AssertSize(1, pMap->NumElements());
		AssertSize(5, gcObjects.NumMemoryIndexes());
		AssertFalse(sNotifier1.bFreed);
		AssertTrue(sNotifier2.bFreed);
		AssertFalse(sNotifier3.bFreed);
		AssertFalse(sNotifier4.bFreed);
		AssertTrue(sNotifier5.bFreed);
		AssertFalse(sNotifier6.bFreed);
	}
	ObjectsFlush();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapObjectDetachOnStack(void)
{
	ObjectsInit();
	{
		STestObjectFreedNotifier	sNotifier1;
		STestObjectFreedNotifier	sNotifier2;
		STestObjectFreedNotifier	sNotifier3;
		STestObjectFreedNotifier	sNotifier4;
		STestObjectFreedNotifier	sNotifier5;
		STestObjectFreedNotifier	sNotifier6;
		bool						bExists;
		SMapIterator				sIter;
		CTestObject*				pcKey;
		CTestObject*				pcValue;

		{
			CMapObject			cMap;

			cMap.Init();
			cMap.Put(ONMalloc<CTestObject>("shnork", &sNotifier4), OMalloc<CTestObject>(&sNotifier1));
			cMap.Put(ONMalloc<CTestObject>("shnerp", &sNotifier5), OMalloc<CTestObject>(&sNotifier2));
			cMap.Put(ONMalloc<CTestObject>("booger", &sNotifier6), OMalloc<CTestObject>(&sNotifier3));
			AssertFalse(sNotifier1.bFreed);
			AssertFalse(sNotifier2.bFreed);
			AssertFalse(sNotifier3.bFreed);
			AssertFalse(sNotifier4.bFreed);
			AssertFalse(sNotifier5.bFreed);
			AssertFalse(sNotifier6.bFreed);
			AssertSize(3, cMap.NumElements());
			AssertSize(3, gcObjects.NumMemoryIndexes());

			bExists = cMap.GetMapForTesting()->StartIteration(&sIter, (CUnknown**)&pcKey, (CUnknown**)&pcValue);
			while (bExists)
			{
				AssertIntHex(0x7070707, pcKey->mi);
				AssertIntHex(0x7070707, pcValue->mi);
				bExists = cMap.GetMapForTesting()->Iterate(&sIter, (CUnknown**)&pcKey, (CUnknown**)&pcValue);
			}
		}

		AssertSize(0, gcObjects.NumMemoryIndexes());
		AssertTrue(sNotifier1.bFreed);
		AssertTrue(sNotifier2.bFreed);
		AssertTrue(sNotifier3.bFreed);
		AssertTrue(sNotifier4.bFreed);
		AssertTrue(sNotifier5.bFreed);
		AssertTrue(sNotifier6.bFreed);
	}
	ObjectsFlush();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapObjectGetPointerTos(void)
{
	ObjectsInit();
	{
		Ptr<CRoot>							pRoot;
		Ptr<CMapObject>						pMap;
		Ptr<CTestObject>					pValue1;
		Ptr<CTestObject>					pValue2;
		Ptr<CTestObject>					pValue3;
		Ptr<CTestObject>					pKey1;
		Ptr<CTestObject>					pKey2;
		Ptr<CTestObject>					pKey3;
		Ptr<CTestObject>					pKey4;
		Ptr<CTestObject>					pKey5;
		STestObjectFreedNotifier			sNotifier1;
		STestObjectFreedNotifier			sNotifier2;
		STestObjectFreedNotifier			sNotifier3;
		STestObjectFreedNotifier			sNotifier4;
		STestObjectFreedNotifier			sNotifier5;
		STestObjectFreedNotifier			sNotifier6;
		STestObjectFreedNotifier			sNotifier7;
		STestObjectFreedNotifier			sNotifier8;
		CArrayTemplateEmbeddedObjectPtr		apcTos;

		pRoot = ORoot();
		pMap = OMalloc<CMapObject>();
		pRoot->Add(pMap);

		pValue3 = OMalloc<CTestObject>(&sNotifier1);
		pValue2 = OMalloc<CTestObject>(&sNotifier2);
		pValue1 = OMalloc<CTestObject>(&sNotifier3);
		pKey1 = ONMalloc<CTestObject>("shnork", &sNotifier4);
		pKey2 = ONMalloc<CTestObject>("shniqu", &sNotifier5);
		pKey3 = ONMalloc<CTestObject>("shnerp", &sNotifier6);
		pKey4 = ONMalloc<CTestObject>("booger", &sNotifier7);
		pKey5 = ONMalloc<CTestObject>("bozzul", &sNotifier8);

		pMap->Put(pKey1, pValue3);
		pMap->Put(pKey2, Null<CObject>());
		pMap->Put(pKey3, pValue2);
		pMap->Put(pKey4, pValue1);
		pMap->Put(pKey5, Null<CObject>());

		AssertSize(5, pMap->NumElements());
		AssertSize(6, gcObjects.NumMemoryIndexes());

		apcTos.Init();
		pMap->GetPointerTos(&apcTos);
		AssertSize(3, apcTos.NumElements());
		AssertTrue(apcTos.ContainsVoidPtr(&pValue1));
		AssertTrue(apcTos.ContainsVoidPtr(&pValue2));
		AssertTrue(apcTos.ContainsVoidPtr(&pValue3));
		AssertTrue(apcTos.ContainsVoidPtr(&pKey1));
		AssertTrue(apcTos.ContainsVoidPtr(&pKey2));
		AssertTrue(apcTos.ContainsVoidPtr(&pKey3));
		AssertTrue(apcTos.ContainsVoidPtr(&pKey4));
		AssertTrue(apcTos.ContainsVoidPtr(&pKey5));
		apcTos.Kill();
	}
	ObjectsFlush();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapObjectPointerFromsHeap(void)
{
	ObjectsInit();
	{
		Ptr<CRoot>					pRoot;
		Ptr<CMapObject>				pMap;
		Ptr<CTestObject>			pKey1;
		Ptr<CTestObject>			pKey2;
		Ptr<CTestObject>			pKey3;
		Ptr<CTestObject>			pKey4;
		Ptr<CTestObject>			pKey5;
		Ptr<CTestObject>			pValue1;
		Ptr<CTestObject>			pValue2;
		Ptr<CTestObject>			pValue3;
		STestObjectFreedNotifier	sNotifier1;
		STestObjectFreedNotifier	sNotifier2;
		STestObjectFreedNotifier	sNotifier3;
		STestObjectFreedNotifier	sNotifier4;
		STestObjectFreedNotifier	sNotifier5;
		STestObjectFreedNotifier	sNotifier6;
		STestObjectFreedNotifier	sNotifier7;
		STestObjectFreedNotifier	sNotifier8;

		pRoot = ORoot();
		pMap = OMalloc<CMapObject>();
		pRoot->Add(pMap);

		pValue3 = OMalloc<CTestObject>(&sNotifier1);
		pValue2 = OMalloc<CTestObject>(&sNotifier2);
		pValue1 = OMalloc<CTestObject>(&sNotifier3);
		pKey1 = ONMalloc<CTestObject>("shnork", &sNotifier4);
		pKey2 = ONMalloc<CTestObject>("shnerp", &sNotifier5);
		pKey3 = ONMalloc<CTestObject>("booger", &sNotifier6);
		pMap->Put(pKey1, pValue1);
		pMap->Put(pKey2, pValue2);
		pMap->Put(pKey3, pValue3);
		AssertSize(1, pValue1->NumHeapFroms());
		AssertSize(1, pValue2->NumHeapFroms());
		AssertSize(1, pValue3->NumHeapFroms());
		AssertSize(1, pKey1->NumHeapFroms());
		AssertSize(1, pKey2->NumHeapFroms());
		AssertSize(1, pKey3->NumHeapFroms());
		AssertSize(3, pMap->NumElements());

		pMap->Remove(pKey3);
		AssertSize(0, pValue1->NumHeapFroms());
		AssertSize(1, pValue2->NumHeapFroms());
		AssertSize(1, pValue3->NumHeapFroms());
		AssertSize(0, pKey1->NumHeapFroms());
		AssertSize(1, pKey2->NumHeapFroms());
		AssertSize(1, pKey3->NumHeapFroms());
		AssertSize(2, pMap->NumElements());

		pMap->RemoveAll();
		AssertSize(0, pValue1->NumHeapFroms());
		AssertSize(0, pValue2->NumHeapFroms());
		AssertSize(0, pValue3->NumHeapFroms());
		AssertSize(0, pKey1->NumHeapFroms());
		AssertSize(0, pKey2->NumHeapFroms());
		AssertSize(0, pKey3->NumHeapFroms());
		AssertSize(0, pMap->NumElements());

		pKey4 = ONMalloc<CTestObject>("abcde", &sNotifier7);
		pMap->Put(pKey4, pValue1);
		AssertSize(1, pValue1->NumHeapFroms());
		AssertSize(0, pValue2->NumHeapFroms());
		AssertSize(0, pValue3->NumHeapFroms());
		AssertSize(1, pKey4->NumHeapFroms());
		AssertSize(1, pMap->NumElements());

		pKey5 = ONMalloc<CTestObject>("abcdf", &sNotifier8);
		pMap->Put(pKey5, pValue1);
		AssertSize(2, pValue1->NumHeapFroms());
		AssertSize(0, pValue2->NumHeapFroms());
		AssertSize(0, pValue3->NumHeapFroms());
		AssertSize(1, pKey4->NumHeapFroms());
		AssertSize(1, pKey5->NumHeapFroms());
		AssertSize(2, pMap->NumElements());

		pMap->Remove(pKey4);
		AssertSize(1, pValue1->NumHeapFroms());
		AssertSize(0, pValue2->NumHeapFroms());
		AssertSize(0, pValue3->NumHeapFroms());
		AssertSize(0, pKey4->NumHeapFroms());
		AssertSize(1, pKey5->NumHeapFroms());
		AssertSize(1, pMap->NumElements());

		pMap->Remove(pKey5);
		AssertSize(0, pValue1->NumHeapFroms());
		AssertSize(0, pValue2->NumHeapFroms());
		AssertSize(0, pValue3->NumHeapFroms());
		AssertSize(0, pKey4->NumHeapFroms());
		AssertSize(0, pKey5->NumHeapFroms());
		AssertSize(0, pMap->NumElements());
	}
	ObjectsFlush();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapObjectPointerFromsStack(void)
{
	ObjectsInit();
	{
		CMapObject					cMap;
		Ptr<CTestObject>			pKey1;
		Ptr<CTestObject>			pKey2;
		Ptr<CTestObject>			pKey3;
		Ptr<CTestObject>			pKey4;
		Ptr<CTestObject>			pKey5;
		Ptr<CTestObject>			pValue1;
		Ptr<CTestObject>			pValue2;
		Ptr<CTestObject>			pValue3;
		STestObjectFreedNotifier	sNotifier1;
		STestObjectFreedNotifier	sNotifier2;
		STestObjectFreedNotifier	sNotifier3;
		STestObjectFreedNotifier	sNotifier4;
		STestObjectFreedNotifier	sNotifier5;
		STestObjectFreedNotifier	sNotifier6;
		STestObjectFreedNotifier	sNotifier7;
		STestObjectFreedNotifier	sNotifier8;

		cMap.Init();
		pValue3 = OMalloc<CTestObject>(&sNotifier1);
		pValue2 = OMalloc<CTestObject>(&sNotifier2);
		pValue1 = OMalloc<CTestObject>(&sNotifier3);
		pKey1 = ONMalloc<CTestObject>("shnork", &sNotifier4);
		pKey2 = ONMalloc<CTestObject>("shnerp", &sNotifier5);
		pKey3 = ONMalloc<CTestObject>("booger", &sNotifier6);
		cMap.Put(pKey1, pValue1);
		cMap.Put(pKey2, pValue2);
		cMap.Put(pKey3, pValue3);
		AssertSize(1, pValue1->NumStackFroms());
		AssertSize(1, pValue2->NumStackFroms());
		AssertSize(1, pValue3->NumStackFroms());
		AssertSize(1, pKey1->NumStackFroms());
		AssertSize(1, pKey2->NumStackFroms());
		AssertSize(1, pKey3->NumStackFroms());
		AssertSize(3, cMap.NumElements());

		cMap.Remove(pKey3);
		AssertSize(0, pValue1->NumStackFroms());
		AssertSize(1, pValue2->NumStackFroms());
		AssertSize(1, pValue3->NumStackFroms());
		AssertSize(0, pKey1->NumStackFroms());
		AssertSize(1, pKey2->NumStackFroms());
		AssertSize(1, pKey3->NumStackFroms());
		AssertSize(2, cMap.NumElements());

		cMap.RemoveAll();
		AssertSize(0, pValue1->NumStackFroms());
		AssertSize(0, pValue2->NumStackFroms());
		AssertSize(0, pValue3->NumStackFroms());
		AssertSize(0, pKey1->NumStackFroms());
		AssertSize(0, pKey2->NumStackFroms());
		AssertSize(0, pKey3->NumStackFroms());
		AssertSize(0, cMap.NumElements());

		pKey4 = ONMalloc<CTestObject>("abcde", &sNotifier7);
		cMap.Put(pKey4, pValue1);
		AssertSize(1, pValue1->NumStackFroms());
		AssertSize(0, pValue2->NumStackFroms());
		AssertSize(0, pValue3->NumStackFroms());
		AssertSize(1, pKey4->NumStackFroms());
		AssertSize(1, cMap.NumElements());

		pKey5 = ONMalloc<CTestObject>("abcdf", &sNotifier8);
		cMap.Put(pKey5, pValue1);
		AssertSize(2, pValue1->NumStackFroms());
		AssertSize(0, pValue2->NumStackFroms());
		AssertSize(0, pValue3->NumStackFroms());
		AssertSize(1, pKey4->NumStackFroms());
		AssertSize(1, pKey5->NumStackFroms());
		AssertSize(2, cMap.NumElements());

		cMap.Remove(pKey4);
		AssertSize(1, pValue1->NumStackFroms());
		AssertSize(0, pValue2->NumStackFroms());
		AssertSize(0, pValue3->NumStackFroms());
		AssertSize(0, pKey4->NumStackFroms());
		AssertSize(1, pKey5->NumStackFroms());
		AssertSize(1, cMap.NumElements());

		cMap.Remove(pKey5);
		AssertSize(0, pValue1->NumStackFroms());
		AssertSize(0, pValue2->NumStackFroms());
		AssertSize(0, pValue3->NumStackFroms());
		AssertSize(0, pKey4->NumStackFroms());
		AssertSize(0, pKey5->NumStackFroms());
		AssertSize(0, cMap.NumElements());
	}
	ObjectsFlush();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapObjectPutOverwrite(void)
{
	ObjectsInit();
	{
		Ptr<CRoot>					pRoot;
		Ptr<CMapObject>				pMap;
		Ptr<CTestObject>			pKey1;
		Ptr<CTestObject>			pValue1;
		Ptr<CTestObject>			pValue2;
		STestObjectFreedNotifier	sNotifier1;
		STestObjectFreedNotifier	sNotifier2;
		STestObjectFreedNotifier	sNotifier3;
		bool						bResult;

		pRoot = ORoot();
		pMap = OMalloc<CMapObject>();
		pRoot->Add(pMap);

		pKey1 = ONMalloc<CTestObject>("1", &sNotifier3);
		pValue2 = OMalloc<CTestObject>(&sNotifier2);
		pValue1 = OMalloc<CTestObject>(&sNotifier1);
		bResult = pMap->Put(pKey1, pValue2);
		gcObjects.ValidateObjectsConsistency();
		AssertTrue(bResult);
		AssertSize(1, pMap->NumElements());
		AssertSize(5, gcObjects.NumMemoryIndexes());
		pValue2 = NULL;
		AssertFalse(sNotifier2.bFreed);

		bResult = pMap->Put(pKey1, pValue1);
		gcObjects.ValidateObjectsConsistency();
		AssertTrue(bResult);
		AssertSize(1, pMap->NumElements());
		AssertSize(5, gcObjects.NumMemoryIndexes());
		AssertTrue(sNotifier2.bFreed);
	}
	ObjectsFlush();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapObjectSerialisation()
{
	CFileUtil	cFileUtil;
//	bool		bResult;
	char		szDirectory[] = "Output" _FS_ "TestMapObject";

	AssertTrue(cFileUtil.RemoveDir(szDirectory));
	AssertTrue(cFileUtil.TouchDir(szDirectory));

	DataOrderersInit();
	ObjectsInit();
	//TestMapObjectAddConstructors();
	//{
	//	Ptr<CPointerContainer>			pContainer1;
	//	Ptr<CPointerContainer>			pContainer2;
	//	Ptr<CPointerContainer>			pContainer3;
	//	Ptr<CTestObject>				pObject;
	//	Ptr<CMapObject>					pMapObject;
	//	CExternalObjectSerialiser		cSerialiser;
	//	CChunkFileObjectWriter			cWriter;
	//	CExternalObjectDeserialiser		cDeserialiser;
	//	CChunkFileSystemObjectReader 	cReader;

	//	pObject = OMalloc<CTestObject>();
	//	pContainer2 = OMalloc<CPointerContainer>(pObject);
	//	pContainer1 = OMalloc<CPointerContainer>(pContainer2);
	//	pContainer3 = OMalloc<CPointerContainer>(Null());
	//	pMapObject = ONMalloc<CMapObject>("Orbis");
	//	pMapObject->Put("Hun", pContainer1);
	//	pMapObject->Put("Koya", pContainer2);
	//	pMapObject->Put("Tokka", pContainer3);

	//	AssertLong(5, gcObjects.NumMemoryIndexes());
	//	AssertInt(3, pMapObject->NumElements());

	//	cWriter.Init(szDirectory, "", "File");
	//	cSerialiser.Init(&cWriter);
	//	bResult = cSerialiser.Write(&pMapObject);
	//	cSerialiser.Kill();
	//	cWriter.Kill();
	//}
	//ObjectsKill();
	//ObjectsInit();
	//{
	//	CPointer						pPointer1;
	//	CPointer						pPointer2;
	//	CPointer						pPointer3;
	//	CPointer						pPointer4;
	//	Ptr<CMapObject>					pMapObject;
	//	CChunkFileObjectWriter			cWriter;
	//	CExternalObjectDeserialiser		cDeserialiser;
	//	CChunkFileSystemObjectReader 	cReader;

	//	cReader.Init(szDirectory, "File");
	//	cDeserialiser.Init(&cReader, false, &gcObjects);
	//	pMapObject = cDeserialiser.Read("Orbis");
	//	AssertNotNull(&pMapObject);
	//	pPointer1 = pMapObject->Get("Hun");
	//	pPointer2 = pMapObject->Get("Koya");
	//	pPointer3 = pMapObject->Get("Tokka");
	//	AssertTrue(pPointer1.IsNotNull());
	//	AssertTrue(pPointer2.IsNotNull());
	//	AssertTrue(pPointer3.IsNotNull());
	//	AssertString("CPointerContainer", pPointer1->ClassName());
	//	AssertString("CPointerContainer", pPointer2->ClassName());
	//	AssertString("CPointerContainer", pPointer3->ClassName());

	//	Ptr<CPointerContainer>	pContainer1;
	//	Ptr<CPointerContainer>	pContainer2;
	//	Ptr<CPointerContainer>	pContainer3;
	//	Ptr<CTestObject>		pObject;

	//	pContainer1 = pPointer1;
	//	pContainer2 = pPointer2;
	//	pContainer3 = pPointer3;
	//	AssertTrue(pContainer1->mp.IsNotNull());
	//	AssertTrue(pContainer2->mp.IsNotNull());
	//	AssertTrue(pContainer3->mp.IsNull());
	//	AssertString("CPointerContainer", pContainer1->mp->ClassName());
	//	AssertString("CTestObject", pContainer2->mp->ClassName());
	//	AssertPointer(&pContainer1->mp, &pContainer2);

	//	cDeserialiser.Kill();
	//	cReader.Kill();

	//	pMapObject = NULL;
	//}
	ObjectsFlush();
	ObjectsKill();
	DataOrderersKill();

	AssertTrue(cFileUtil.RemoveDir(szDirectory));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapObjectConstructorExists(void)
{
	CConstructors*	pcConstructors;
	CMapObject*		pcMapObject;

	ObjectsInit();

	pcConstructors = gcObjects.GetConstructors();
	pcMapObject = pcConstructors->Get<CMapObject>();
	AssertNotNull(pcMapObject);
	AssertString("CMapObject", pcMapObject->ClassName());

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapObjectClassExists(void)
{
	CClasses*	pcClasses;
	CClass*		pcClass;

	ObjectsInit();

	CMapObject	cMapObject;

	pcClasses = gcObjects.GetClasses();
	pcClass = pcClasses->Get(cMapObject.ClassName());
	AssertNotNull(pcClass);
	AssertString("CMapObject", pcClass->GetName());

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapObjectMorphInto(void)
{
	ObjectsInit();
	{
		Ptr<CRoot>					pRoot;
		Ptr<CMapObject>				pMap1;
		Ptr<CTestObject>			pKey1;
		Ptr<CTestObject>			pKey2;
		Ptr<CTestObject>			pKey3;
		Ptr<CTestObject>			pKey4;
		Ptr<CTestObject>			pKey5;
		Ptr<CTestObject>			pValue1;
		Ptr<CTestTriPointerObject>	pValue2;
		Ptr<CTestObject>			pValue3;
		Ptr<CTestTriPointerObject>	pValue4;
		STestObjectFreedNotifier	sNotifier1;
		STestObjectFreedNotifier	sNotifier2;
		STestObjectFreedNotifier	sNotifier3;
		STestObjectFreedNotifier	sNotifier4;
		STestObjectFreedNotifier	sNotifier5;
		STestObjectFreedNotifier	sNotifier6;
		STestObjectFreedNotifier	sNotifier7;
		STestObjectFreedNotifier	sNotifier8;
		STestObjectFreedNotifier	sNotifier9;
		bool						bResult;
		size						uiRemapped;

		pRoot = ORoot();
		pMap1 = OMalloc<CMapObject>();
		pRoot->Add(pMap1);

		pValue1 = OMalloc<CTestObject>(&sNotifier1);
		pValue2 = OMalloc<CTestTriPointerObject>(&sNotifier2);
		pValue3 = OMalloc<CTestObject>(&sNotifier3);
		pValue4 = OMalloc<CTestTriPointerObject>(&sNotifier4);
		pKey1 = ONMalloc<CTestObject>("1", &sNotifier5);
		pKey2 = ONMalloc<CTestObject>("2", &sNotifier6);
		bResult = pMap1->Put(pKey1, pValue1);
		AssertTrue(bResult);
		bResult = pMap1->Put(pKey2, pValue2);
		
		CMapObject		cMap2;

		pKey3 = ONMalloc<CTestObject>("3", &sNotifier7);
		pKey4 = ONMalloc<CTestObject>("4", &sNotifier8);
		pKey5 = ONMalloc<CTestObject>("5", &sNotifier9);

		cMap2.Init();
		cMap2.Put(pKey3, pValue2);
		cMap2.Put(pKey4, pValue3);
		cMap2.Put(pKey5, pValue2);

		pValue4->mpObject1 = pValue2;
		pValue4->mpObject2 = pValue2;

		pValue2->mpObject1 = pValue1;

		Ptr<CTestObjectWithFields>	pValue5;
		CPointer					pPtr;

		pValue5 = OMalloc<CTestObjectWithFields>();

		AssertFalse(sNotifier2.bFreed);
		uiRemapped = pValue2.MorphInto(&pValue5);
		//2 (cMap2) +
		//1 (pMap1) +
		//1 (pValue2)  +
		//2 (pValue4->mpObject1, pValue4->mpObject2) =
		//6
		AssertSize(6, uiRemapped);
		AssertPointer(&pValue5, &pValue2);
		AssertString("CTestObjectWithFields", pValue5->ClassName());
		AssertTrue(sNotifier2.bFreed);
		AssertPointer(&pValue5, &pValue4->mpObject1);
		AssertPointer(&pValue5, &pValue4->mpObject2);
		pPtr = pMap1->Get(pKey2);
		AssertPointer(&pValue5, &pPtr);
		pPtr = cMap2.Get(pKey3);
		AssertPointer(&pValue5, &pPtr);
		pPtr = cMap2.Get(pKey4);
		AssertPointer(&pValue3, &pPtr);
		pPtr = cMap2.Get(pKey5);
		AssertPointer(&pValue5, &pPtr);
	}
	ObjectsFlush();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapObject(void)
{
	BeginTests();
	MemoryInit();
	TypesInit();
	DataIOInit();

	TestMapObjectConstructorExists();
	TestMapObjectClassExists();
	TestMapObjectPut();
	TestMapObjectDetachInHeap();
	TestMapObjectIterate();
	TestMapObjectRemove();
	TestMapObjectDetachOnStack();
	TestMapObjectGetPointerTos();
	TestMapObjectPointerFromsHeap();
	TestMapObjectPointerFromsStack();
	TestMapObjectPutOverwrite();
	TestMapObjectSerialisation();
	TestMapObjectMorphInto();

	DataIOKill();
	TypesKill();
	MemoryKill();
	TestStatistics();
}

