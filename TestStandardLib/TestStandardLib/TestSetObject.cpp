#include "BaseLib/GlobalMemory.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/TypeNames.h"
#include "BaseLib/Codabase.h"
#include "BaseLib/CodabaseFactory.h"
#include "BaseLib/SequenceFactory.h"
#include "BaseLib/DebugOutput.h"
#include "StandardLib/HollowObject.h"
#include "StandardLib/Set.h"
#include "TestLib/Assert.h"
#include "TestSetObject.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSetObjectAddConstructors(void)
{
	gcObjects.AddConstructor<CTestSaveableObject1>();
	gcObjects.AddConstructor<CTestObject>();
	gcObjects.AddConstructor<CPointerContainer>();
	gcObjects.AddConstructor<CTestTriPointerObject>();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSetObjectAdd(void)
{
	ObjectsInit();

	Ptr<CSet<CTestSaveableObject1>> pacStuff = OMalloc<CSet<CTestSaveableObject1>>(false);
	pacStuff->Add(OMalloc<CTestSaveableObject1>());

	Ptr<CTestSaveableObject1> pSaveable = pacStuff->UnsafeGet(0);
	AssertTrue(pSaveable.IsNotNull());
	AssertInt(7, pSaveable->miInt);

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSetObjectGet(void)
{
	ObjectsInit();

	Ptr<CSet<CTestSaveableObject1>> pacStuff = OMalloc<CSet<CTestSaveableObject1>>(false);
	pacStuff->Add(OMalloc<CTestSaveableObject1>());
	Ptr<CTestSaveableObject1> pSaveable = OMalloc<CTestSaveableObject1>();
	pSaveable->miInt = 3;
	pacStuff->Add(pSaveable);

	AssertInt(2, pacStuff->NumElements());
	AssertInt(7, pacStuff->UnsafeGet(0)->miInt);
	AssertInt(3, pacStuff->UnsafeGet(1)->miInt);

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSetObjectAddAll(void)
{
	ObjectsInit();

	Ptr<CSet<CTestSaveableObject1>> pacStuff = OMalloc<CSet<CTestSaveableObject1>>(false);
	pacStuff->Add(OMalloc<CTestSaveableObject1>());
	Ptr<CTestSaveableObject1> pSaveable = OMalloc<CTestSaveableObject1>();
	pSaveable->miInt = 3;
	pacStuff->Add(pSaveable);

	Ptr<CSet<CTestSaveableObject1>> pacMore = OMalloc<CSet<CTestSaveableObject1>>(false);
	pSaveable = OMalloc<CTestSaveableObject1>();
	pSaveable->miInt = 5;
	pacStuff->Add(pSaveable);

	pacMore->AddAll(pacStuff);

	AssertInt(3, pacMore->NumElements());
	AssertInt(7, pacMore->UnsafeGet(0)->miInt);
	AssertInt(3, pacMore->UnsafeGet(1)->miInt);
	AssertInt(5, pacMore->UnsafeGet(2)->miInt);

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSetObjectRemove(void)
{
	ObjectsInit();

	Ptr<CRoot> pRoot = ORoot();

	Ptr<CSet<CTestSaveableObject1>> pacStuff = OMalloc<CSet<CTestSaveableObject1>>(false);
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
	AssertInt(7, pacStuff->UnsafeGet(0)->miInt);
	AssertInt(3, pacStuff->UnsafeGet(1)->miInt);

	ObjectsFlush();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSetObjectKillCyclic(void)
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
	pSet = OMalloc<CSetObject>(false);
	pRoot = ORoot();
	pRoot->Add(pSet);
	pSet->Add(pTest3);

	AssertLong(6, gcObjects.NumMemoryIndexes());
	AssertInt(5, pTest1->GetDistToRoot());
	AssertInt(4, pTest2->GetDistToRoot());
	AssertInt(3, pTest3->GetDistToRoot());

	pSet->Kill();
	AssertLong(5, gcObjects.NumMemoryIndexes());
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
void TestSetObjectKillAll(void)
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
	pSet = OMalloc<CSetObject>(false);
	pRoot = ORoot();
	pRoot->Add(pSet);
	pSet->Add(pContainer1);

	AssertLong(6, gcObjects.NumMemoryIndexes());
	AssertInt(1, pSet->NumElements());

	pSet->KillAll();
	AssertInt(0, pSet->NumElements());
	AssertLong(5, gcObjects.NumMemoryIndexes());
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
void TestSetObjectRemoveAll(void)
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
	pSet = OMalloc<CSetObject>(false);
	pRoot = ORoot();
	pRoot->Add(pSet);
	pSet->Add(pContainer1);

	AssertLong(6, gcObjects.NumMemoryIndexes());
	AssertInt(1, pSet->NumElements());

	pSet->RemoveAll();
	AssertInt(0, pSet->NumElements());
	AssertLong(6, gcObjects.NumMemoryIndexes());
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
void TestSetObjectSerialisation(void)
{
	ObjectsInit();
	TestSetObjectAddConstructors();

	Ptr<CPointerContainer>			pContainer1;
	Ptr<CPointerContainer>			pContainer2;
	Ptr<CTestObject>				pObject;
	Ptr<CSetObject>					pSet;
	CExternalObjectSerialiser		cSerialiser;
	CChunkFileObjectWriter			cWriter;
	CFileUtil						cFileUtil;
	bool							bResult;
	char							szDirectory[] = "Output" _FS_ "TestSetObject";
	CExternalObjectDeserialiser		cDeserialiser;
	CChunkFileSystemObjectReader 	cReader;

	AssertTrue(cFileUtil.RemoveDir(szDirectory));
	AssertTrue(cFileUtil.TouchDir(szDirectory));

	pObject = OMalloc<CTestObject>();
	pContainer2 = OMalloc<CPointerContainer>(pObject);
	pContainer1 = OMalloc<CPointerContainer>(pContainer2);
	pSet = ONMalloc<CSetObject>("Burke", false);
	pSet->Add(pContainer1);
	pSet->Add(pContainer2);

	AssertLong(4, gcObjects.NumMemoryIndexes());
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
	cDeserialiser.Init(&cReader, false, &gcObjects);
	pSet = cDeserialiser.Read("Burke");
	AssertNotNull(&pSet);
	cDeserialiser.Kill();
	cReader.Kill();

	pSet = NULL;

	ObjectsKill();

	AssertTrue(cFileUtil.RemoveDir(szDirectory));
}


struct STriOi
{
	OIndex	oi1;
	OIndex	oi2;
	OIndex	oi3;
};


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSetObjectObjectInternalSerialisation(size uiNumSetItems)
{
	CFileUtil			cFileUtil;
	CCodabase*			pcDatabase;
	CSequence*			pcSequence;
	char				szDirectory[] = "Output" _FS_ "SetObjectInternalSerialisation";
	bool				bResult;
	CIndexTreeMemory	cIndexTriIndices;

	AssertTrue(cFileUtil.RemoveDir(szDirectory));
	AssertTrue(cFileUtil.TouchDir(szDirectory));

	CArrayInt	aiKeyNames;
	CRandom		cRandom;
	uint		uiCount;

	cIndexTriIndices.Init(IKR_Yes);

	cRandom.Init(32280975);
	aiKeyNames.Init();
	for (uiCount = 0; uiCount < uiNumSetItems; uiCount++)
	{
		aiKeyNames.Add(uiCount);
	}
	aiKeyNames.Shuffle(&cRandom);
	cRandom.Kill();
	AssertSize(uiNumSetItems, aiKeyNames.NumElements());

	pcSequence = CSequenceFactory::Create(szDirectory);
	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase, pcSequence);
	{
		Ptr<CRoot>					pRoot;
		Ptr<CSetObject>				pSet;
		Ptr<CTestObject>			pKey;
		Ptr<CTestObject>			pValue1;
		Ptr<CTestObject>			pValue2;
		Ptr<CTestObject>			pValue3;
		Ptr<CTestTriPointerObject>	pValue5;
		CPointer					pObject;
		bool						bResult;
		size						ui;
		OIndex						oi;
		STriOi*						psTriOi;
		STriOi						sTriOi;
		SSetIterator				sIter;
		bool						bExists;

		pRoot = ORoot();
		pSet = ONMalloc<CSetObject>("Set");
		pRoot->Add(pSet);

		gcObjects.DisableValidation();

		pValue1 = NULL;
		pValue2 = NULL;
		pValue3 = NULL;

		AssertTrue(pSet->IsMustSort());

		bResult = true;
		for (ui = 0; ui < uiNumSetItems; ui++)
		{
			if (ui % 2 == 0)
			{
				pValue3 = pValue2;
				pValue2 = pValue1;
				pValue1 = ONMalloc<CTestObject>(SizeToString(ui));
				bResult = pSet->Add(pValue1);
			}
			else
			{
				pValue5 = ONMalloc<CTestTriPointerObject>(SizeToString(ui));
				pValue5->mpObject1 = pValue1;
				pValue5->mpObject2 = pValue2;
				pValue5->mpObject3 = pValue3;
				bResult = pSet->Add(pValue5);

				oi = pValue5->GetIndex();
				psTriOi = (STriOi*)cIndexTriIndices.Put((uint8*)&oi, sizeof(OIndex), NULL, sizeof(STriOi));
				psTriOi->oi1 = pValue1.GetIndex();
				psTriOi->oi2 = pValue2.GetIndex();
				psTriOi->oi3 = pValue3.GetIndex();
			}
			if (!bResult)
			{
				AssertTrue(bResult);
				break;
			}
		}
		AssertTrue(bResult);

		pValue1 = NULL;
		pValue2 = NULL;
		pValue3 = NULL;

		bResult = true;
		pObject = pSet->StartIteration(&sIter);
		while (pObject.IsNotNull())
		{
			oi = pObject->GetIndex();
			bExists = cIndexTriIndices.Get((uint8*)&oi, sizeof(OIndex), &sTriOi, NULL, sizeof(STriOi));
			if (!bExists)
			{
				bResult = StringCompare("CTestObject", pObject->ClassName()) == 0;
				if (!bResult)
				{
					AssertTrue(bResult);
					break;
				}
			}
			else
			{
				bResult = StringCompare("CTestTriPointerObject", pObject->ClassName()) == 0;
				if (!bResult)
				{
					AssertTrue(bResult);
					break;
				}

				pValue1 = gcObjects.Get(sTriOi.oi1);
				pValue2 = gcObjects.Get(sTriOi.oi2);
				pValue3 = gcObjects.Get(sTriOi.oi3);

				pValue5 = pObject;
				bResult  = &pValue5->mpObject1 == &pValue1;
				bResult &= &pValue5->mpObject2 == &pValue2;
				bResult &= &pValue5->mpObject3 == &pValue3;
				if (!bResult)
				{
					AssertTrue(bResult);
					break;
				}
			}
			pObject = pSet->Iterate(&sIter);
		}
		AssertTrue(bResult);
	}

	gcObjects.EnableValidation();
	gcObjects.ValidateObjectsConsistency();

	bResult = ObjectsFlush();
	AssertTrue(bResult);
	bResult = gcObjects.EvictInMemory();
	AssertTrue(bResult);

	AssertLong(uiNumSetItems + 3LL, pcDatabase->NumIndices());
	pcDatabase->Close();
	SafeKill(pcDatabase);
	SafeKill(pcSequence);
	ObjectsKill();

	pcSequence = CSequenceFactory::Create(szDirectory);
	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase, pcSequence);
	{
		TestSetObjectAddConstructors();
		AssertLong(uiNumSetItems + 3LL, pcDatabase->NumIndices());

		AssertTrue(gcObjects.Contains("Set"));

		Ptr<CSetObject>				pSet;
		Ptr<CHollowObject>			pHollow;
		bool						bResult;
		OIndex						oi;
		STriOi						sTriOi;
		SSetIterator				sIter;
		CPointer					pObject;
		bool						bExists;
		CIndexTreeMemory			cIndexObjectPointers;
		char*						szName;
		size						uiLength;
		CHollowObject*				pcHollow;
		CObject*					pcObject;

		pSet = gcObjects.Get("Set");
		AssertTrue(pSet.IsNotNull());
		AssertSize(uiNumSetItems, pSet->NumElements());

		cIndexObjectPointers.Init();

		AssertTrue(pSet->IsMustSort());
		AssertFalse(pSet->IsSorted());

		bResult = true;
		pObject = pSet->StartIteration(&sIter);
		AssertTrue(pSet->IsSorted());
		AssertTrue(pSet->CalculateIsSorted());
		while (pObject.IsNotNull())
		{
			bResult = pObject.IsHollow();
			if (!bResult)
			{
				AssertTrue(bResult);
				break;
			}
			pHollow = pObject;
			pcHollow = ((CHollowObject*)pHollow.Object());
			bResult = pcHollow->IsFatHollow();
			if (!bResult)
			{
				AssertTrue(bResult);
				break;
			}
			szName = pHollow.GetName();
			uiLength = StrLen(szName);
			
			cIndexObjectPointers.Put((uint8*)szName, uiLength, &pcHollow, sizeof(CHollowObject*));

			oi = pObject->GetIndex();
			bResult = pObject.IsHollow();
			if (bResult)
			{
				AssertFalse(bResult);
				break;
			}

			bExists = cIndexTriIndices.Get((uint8*)&oi, sizeof(OIndex), &sTriOi, NULL, sizeof(STriOi));
			if (!bExists)
			{
				bResult = StringCompare("CTestObject", pObject->ClassName()) == 0;
				if (!bResult)
				{
					AssertTrue(bResult);
					break;
				}
			}
			else
			{
				bResult = StringCompare("CTestTriPointerObject", pObject->ClassName()) == 0;
				if (!bResult)
				{
					AssertTrue(bResult);
					break;
				}
			}
			pObject = pSet->Iterate(&sIter);
		}
		AssertTrue(bResult);
		AssertTrue(pSet->IsSorted());
		AssertTrue(pSet->CalculateIsSorted());

		bResult = true;
		pObject = pSet->StartIteration(&sIter);
		while (pObject.IsNotNull())
		{
			bResult = pObject.IsHollow();
			if (bResult)
			{
				AssertFalse(bResult);
				break;
			}
			szName = pObject.GetName();
			uiLength = StrLen(szName);

			bExists = cIndexObjectPointers.Get((uint8*)szName, uiLength, &pcObject, NULL, sizeof(CObject*));
			bResult = pObject.Object() == pcObject;
			if (bResult)
			{
				AssertPointer(pObject.Object(), pcObject);
				break;
			}
			pObject = pSet->Iterate(&sIter);
		}
		AssertTrue(bResult);

		cIndexObjectPointers.Kill();
		aiKeyNames.Kill();
	}
	pcDatabase->Close();
	SafeKill(pcDatabase);
	SafeKill(pcSequence);
	ObjectsKill();

	cIndexTriIndices.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSetObjectObjectMorphSetEntry(size uiNumElements)
{
	ObjectsInit();
	{
		size										ui;
		Ptr<CSetObject>								pSet;
		Ptr<CTestSaveableObject1>					pSaveable;
		CArrayTemplate<STestObjectFreedNotifier>	asFreedNotifiers;
		STestObjectFreedNotifier*					psFreedNotifier;
		Ptr<>										pMiddle;
		size										uiHalfWay;
		Ptr<CTestEmbeddedObjectWithFields>			pComplex;
		size										uiNumRemapped;
		Ptr<CRoot>									pRoot;
		size										uiNumSaveableObject;
		size										uiNumEmbeddedObject;
		SSetIterator								sIter;
		Ptr<>										pObject;
		bool										bResult;
		int											iCompare;
		Ptr<CTestObject>							pTestObject;

		uiHalfWay = uiNumElements / 2;
		asFreedNotifiers.Init();
		for (ui = 0; ui < uiNumElements; ui++)
		{
			asFreedNotifiers.Add();
		}

		gcObjects.DisableValidation();

		pRoot = ORoot();
		pSet = OMalloc<CSetObject>();
		pRoot->Add(pSaveable);
		for (ui = 0; ui < uiNumElements; ui++)
		{
			pSaveable = OMalloc<CTestSaveableObject1>();
			pSaveable->miInt = uiNumElements - ui;
			pSaveable->mszString.Init(SizeToString(ui));
			psFreedNotifier = asFreedNotifiers.Get(ui);
			pSaveable->mpObject = OMalloc<CTestObject>(psFreedNotifier);
			pSet->Add(pSaveable);

			if (ui == uiHalfWay)
			{
				pMiddle = pSaveable;
			}
		}
		pSaveable = NULL;

		AssertTrue(pSet->IsSorted());
		AssertTrue(pSet->CalculateIsSorted());

		AssertSize(1, pMiddle.NumHeapFroms());
		AssertSize(1, pMiddle.NumStackFroms());

		pComplex = ONMalloc<CTestEmbeddedObjectWithFields>("Complex");
		AssertSize(2 * uiNumElements + 1 + 3, gcObjects.NumMemoryIndexes());

		gcObjects.EnableValidation();

		uiNumRemapped = pMiddle.MorphInto(&pComplex);
		AssertSize(2, uiNumRemapped);
		AssertSize(2 * (uiNumElements - 1) + 1 + 3, gcObjects.NumMemoryIndexes());

		bResult = true;
		for (ui = 0; ui < uiNumElements; ui++)
		{
			psFreedNotifier = asFreedNotifiers.Get(ui);
			if (ui != uiHalfWay)
			{
				if (psFreedNotifier->bFreed)
				{
					AssertFalse(psFreedNotifier->bFreed);
					break;
				}
			}
			else
			{
				if (!psFreedNotifier->bFreed)
				{
					AssertTrue(psFreedNotifier->bFreed);
					break;
				}
			}
		}
		AssertTrue(bResult);

		AssertFalse(pSet->IsSorted());
		AssertFalse(pSet->CalculateIsSorted());

		pSet->Contains(pComplex);

		AssertTrue(pSet->IsSorted());
		AssertTrue(pSet->CalculateIsSorted());

		AssertPointer(&pComplex, &pMiddle);

		uiNumSaveableObject = 0;
		uiNumEmbeddedObject = 0;

		pObject = pSet->StartIteration(&sIter);
		while (pObject.IsNotNull())
		{
			iCompare = StrCmp("CTestSaveableObject1", pObject.ClassName());
			if (iCompare == 0)
			{
				uiNumSaveableObject++;
			}

			iCompare = StrCmp("CTestEmbeddedObjectWithFields", pObject.ClassName());
			if (iCompare == 0)
			{
				uiNumEmbeddedObject++;
			}

			pObject = pSet->Iterate(&sIter);
		}

		AssertInt(uiNumElements - 1, uiNumSaveableObject);
		AssertInt(1, uiNumEmbeddedObject);

		AssertSize(2 * (uiNumElements - 1) + 1 + 3, gcObjects.NumMemoryIndexes());

		pTestObject = OMalloc<CTestObject>();

		uiNumRemapped = pSet.MorphInto(&pTestObject);
		AssertSize(1, uiNumRemapped);
		AssertSize(1 + 3, gcObjects.NumMemoryIndexes());

		bResult = true;
		for (ui = 0; ui < uiNumElements; ui++)
		{
			psFreedNotifier = asFreedNotifiers.Get(ui);
			if (!psFreedNotifier->bFreed)
			{
				AssertTrue(psFreedNotifier->bFreed);
				break;
			}
		}
		AssertTrue(bResult);

		asFreedNotifiers.Kill();
	}
	ObjectsFlush();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSetObjectEmbeddedOnHeapKill(void)
{
	ObjectsInit();
	{
		STestObjectFreedNotifier	sFreedNotifier1;
		STestObjectFreedNotifier	sFreedNotifier2;
		Ptr<CTestEmbeddedSet>		pEmbedded;
		Ptr<CTestObject>			pTest;
		CTestObject*				pcTest;

		pEmbedded = OMalloc<CTestEmbeddedSet>(&sFreedNotifier1);
		pTest = OMalloc<CTestObject>(&sFreedNotifier2);
		pEmbedded->mcSet.Add(pTest);
		pEmbedded->mcSet.Add(pTest);

		AssertSize(2, pTest.NumHeapFroms());
		AssertSize(1, pTest.NumStackFroms());

		pcTest = &pTest;
		pTest = NULL;
		AssertFalse(sFreedNotifier1.bFreed);
		AssertFalse(sFreedNotifier2.bFreed);
		AssertSize(2, pcTest->NumHeapFroms());
		AssertSize(0, pcTest->NumStackFroms());

		pEmbedded = NULL;

		AssertTrue(sFreedNotifier1.bFreed);
		AssertTrue(sFreedNotifier2.bFreed);
	}
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSetObjectEmbeddedOnStackKill(void)
{
	STestObjectFreedNotifier	sFreedNotifier1;
	STestObjectFreedNotifier	sFreedNotifier2;

	ObjectsInit();
	{
		CTestEmbeddedSet		cEmbedded;
		Ptr<CTestObject>		pTest;
		CTestObject*			pcTest;

		cEmbedded.Init(&sFreedNotifier1);
		pTest = OMalloc<CTestObject>(&sFreedNotifier2);
		cEmbedded.mcSet.Add(pTest);
		cEmbedded.mcSet.Add(pTest);

		AssertSize(3, pTest.NumStackFroms());
		AssertSize(0, pTest.NumHeapFroms());
		pcTest = &pTest;

		pTest = NULL;
		AssertSize(0, pTest.NumStackFroms());
		AssertSize(0, pcTest->NumHeapFroms());
		AssertSize(2, pcTest->NumStackFroms());

		AssertFalse(sFreedNotifier1.bFreed);
		AssertFalse(sFreedNotifier2.bFreed);
	}
	AssertTrue(sFreedNotifier1.bFreed);
	AssertTrue(sFreedNotifier2.bFreed);

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSetObjectEmbeddedInObjectsKill(void)
{
	STestObjectFreedNotifier	sFreedNotifier1;
	STestObjectFreedNotifier	sFreedNotifier2;

	ObjectsInit();

	Ptr<CTestEmbeddedSet>		pEmbedded;
	Ptr<CTestObject>			pTest;
	CTestObject*				pcTest;
	Ptr<CRoot>					pRoot;

	pRoot = ORoot();
	pEmbedded = OMalloc<CTestEmbeddedSet>(&sFreedNotifier1);
	pRoot->Add(pEmbedded);
	pTest = OMalloc<CTestObject>(&sFreedNotifier2);
	pEmbedded->mcSet.Add(pTest);
	pEmbedded->mcSet.Add(pTest);

	AssertSize(2, pTest.NumHeapFroms());
	AssertSize(1, pTest.NumStackFroms());
	pcTest = &pTest;

	pTest = NULL;
	pEmbedded = NULL;
	AssertSize(2, pcTest->NumHeapFroms());
	AssertSize(0, pcTest->NumStackFroms());

	AssertFalse(sFreedNotifier1.bFreed);
	AssertFalse(sFreedNotifier2.bFreed);

	ObjectsFlush();
	ObjectsKill();

	AssertTrue(sFreedNotifier1.bFreed);
	AssertTrue(sFreedNotifier2.bFreed);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSetObject(void)
{
	BeginTests();
	MemoryInit();
	FastFunctionsInit();
	TypesInit();
	DataIOInit();

	TestSetObjectAdd();
	TestSetObjectGet();
	TestSetObjectAddAll();
	TestSetObjectRemove();
	TestSetObjectKillCyclic();
	TestSetObjectKillAll();
	TestSetObjectRemoveAll();
	TestSetObjectSerialisation();
	TestSetObjectObjectInternalSerialisation(4);
	TestSetObjectObjectInternalSerialisation(10000);
	TestSetObjectObjectMorphSetEntry(10);
	TestSetObjectObjectMorphSetEntry(2000);
	TestSetObjectEmbeddedOnHeapKill();
	TestSetObjectEmbeddedOnStackKill();
	TestSetObjectEmbeddedInObjectsKill();

	DataIOKill();
	TypesKill();
	FastFunctionsKill();
	MemoryKill();
	TestStatistics();
}

