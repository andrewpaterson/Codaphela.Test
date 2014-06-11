#include "StandardLib/Objects.h"
#include "StandardLib/PointerContainer.h"
#include "TestLib/Assert.h"
#include "ObjectTestSetup.h"
#include "EmbeddedObjectTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void SetupEmbeddedObjectConstructors(void)
{
	gcObjects.AddConstructor<CArrayObject>();
	gcObjects.AddConstructor<CSetObject>();
	gcObjects.AddConstructor<CRoot>();
	gcObjects.AddConstructor<CEmbeddedTest>();
	gcObjects.AddConstructor<CEmbeddedContainer>();
	gcObjects.AddConstructor<CEmbeddedComplex>();
	gcObjects.AddConstructor<CPointerContainer>();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestEmbeddedFlags(void)
{
	ObjectsInit();

	CEmbeddedComplex	cComplex;

	AssertFalse(cComplex.HasClass());
	AssertFalse(cComplex.ma.HasClass());
	AssertFalse(cComplex.mcSimple.HasClass());
	AssertFalse(cComplex.mcContainer.HasClass());
	AssertFalse(cComplex.mcContainer.mcOne.HasClass());
	AssertFalse(cComplex.mcContainer.mcTwo.HasClass());
	AssertFalse(cComplex.IsInitialised());
	AssertFalse(cComplex.ma.IsInitialised());
	AssertFalse(cComplex.mcSimple.IsInitialised());
	AssertFalse(cComplex.mcContainer.IsInitialised());
	AssertFalse(cComplex.mcContainer.mcOne.IsInitialised());
	AssertFalse(cComplex.mcContainer.mcTwo.IsInitialised());

	cComplex.Class();

	AssertTrue(cComplex.HasClass());
	AssertTrue(cComplex.ma.HasClass());
	AssertTrue(cComplex.mcSimple.HasClass());
	AssertTrue(cComplex.mcContainer.HasClass());
	AssertTrue(cComplex.mcContainer.mcOne.HasClass());
	AssertTrue(cComplex.mcContainer.mcTwo.HasClass());
	AssertFalse(cComplex.IsInitialised());
	AssertFalse(cComplex.ma.IsInitialised());
	AssertFalse(cComplex.mcSimple.IsInitialised());
	AssertFalse(cComplex.mcContainer.IsInitialised());
	AssertFalse(cComplex.mcContainer.mcOne.IsInitialised());
	AssertFalse(cComplex.mcContainer.mcTwo.IsInitialised());

	cComplex.Init();

	AssertTrue(cComplex.HasClass());
	AssertTrue(cComplex.ma.HasClass());
	AssertTrue(cComplex.mcSimple.HasClass());
	AssertTrue(cComplex.mcContainer.HasClass());
	AssertTrue(cComplex.mcContainer.mcOne.HasClass());
	AssertTrue(cComplex.mcContainer.mcTwo.HasClass());
	AssertTrue(cComplex.IsInitialised());
	AssertTrue(cComplex.ma.IsInitialised());
	AssertTrue(cComplex.mcSimple.IsInitialised());
	AssertTrue(cComplex.mcContainer.IsInitialised());
	AssertTrue(cComplex.mcContainer.mcOne.IsInitialised());
	AssertTrue(cComplex.mcContainer.mcTwo.IsInitialised());

	cComplex.Kill();

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestEmbeddedObjectAddDistToRoot(void)
{
	ObjectsInit();

	Ptr<CRoot>				pRoot = ORoot();
	Ptr<CGameWorld>			pWorld = OMalloc(CGameWorld)->Init();

	pRoot->Add(pWorld);

	Ptr<CClusterMissile>	pMissile = ONMalloc(CClusterMissile, "Frank")->Init(pWorld);
	Ptr<CHarrier>			pHarrier = OMalloc(CHarrier)->Init(pWorld);
	
	pWorld->AddPlayer(pHarrier);
	AssertInt(3, pHarrier->GetDistToRoot());

	pRoot->Add(pMissile);

	AssertInt(2, pMissile->GetDistToRoot());
	AssertInt(2, pMissile->mcMissile1.GetDistToRoot());
	AssertInt(2, pMissile->mcMissile2.GetDistToRoot());

	pMissile->mcMissile1.SetTarget(pHarrier);

	AssertInt(3, pHarrier->GetDistToRoot());

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestEmbeddedObjectRemoveDistToRoot(void)
{
	ObjectsInit();

	Ptr<CRoot>				pRoot = ORoot();
	Ptr<CGameWorld>			pWorld = OMalloc(CGameWorld)->Init();

	pRoot->Add(pWorld);

	Ptr<CClusterMissile>	pMissile = ONMalloc(CClusterMissile, "Frank")->Init(pWorld);
	Ptr<CHarrier>			pHarrier = OMalloc(CHarrier)->Init(pWorld);
	Ptr<CMissile>			pHolder = OMalloc(CMissile)->Init(pWorld);
	
	pWorld->AddTickable(pHolder);
	AssertInt(4, pHolder->GetDistToRoot());

	pHolder->SetTarget(pHarrier);
	AssertInt(5, pHarrier->GetDistToRoot());

	Ptr<CClusterLauncher>	pLauncher = OMalloc(CClusterLauncher)->Init();

	pRoot->Add(pLauncher);
	AssertInt(2, pLauncher->GetDistToRoot());

	pLauncher->mpMissile = pMissile;

	AssertInt(3, pMissile->GetDistToRoot());
	AssertInt(3, pMissile->mcMissile1.GetDistToRoot());
	AssertInt(3, pMissile->mcMissile2.GetDistToRoot());
	AssertInt(5, pHarrier->GetDistToRoot());
	AssertInt(1, pHarrier->NumHeapFroms());

	pMissile->mcMissile1.SetTarget(pHarrier);
	AssertInt(4, pHarrier->GetDistToRoot());
	AssertInt(2, pHarrier->NumHeapFroms());

	pWorld->RemoveTickable(pHolder);
	pHolder = NULL;

	AssertInt(4, pHarrier->GetDistToRoot());
	AssertInt(1, pHarrier->NumHeapFroms());

	pRoot->Add(pHarrier);
	AssertInt(2, pHarrier->GetDistToRoot());

	pRoot->Remove(pHarrier);
	AssertInt(4, pHarrier->GetDistToRoot());

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestEmbeddedObjectKill(void)
{
	char	szClusterMissileState[64];
	char	szMissile1State[64];

	ObjectsInit();

	Ptr<CRoot> pRoot = ORoot();
	Ptr<CGameWorld> pWorld = OMalloc(CGameWorld)->Init();

	pRoot->Add(pWorld);

	Ptr<CClusterMissile> pClusterMissile = ONMalloc(CClusterMissile, "Anna")->Init(pWorld);
	pWorld = NULL;

	Ptr<CPointerContainer> pPointerPointer = OMalloc(CPointerContainer);
	pRoot->Add(pPointerPointer);
	pPointerPointer->Init(&pClusterMissile->mcMissile1);

	Ptr<CPointerContainer> pPointerPointer2 = OMalloc(CPointerContainer);
	pRoot->Add(pPointerPointer2);
	pPointerPointer2->Init(&pClusterMissile);

	//The number of allocated object shouldn't change until all the froms are removed
	//both from the embedded object and the 'normal' object.
	AssertLongLongInt(7, gcObjects.GetMemory()->NumIndexed());
	AssertLongLongInt(7, gcUnknowns.NumElements());

	pClusterMissile->SetKillString(szClusterMissileState);
	pClusterMissile->mcMissile1.SetKillString(szMissile1State);

	AssertInt(2, pClusterMissile->NumHeapFroms());
	AssertInt(1, pClusterMissile->CEmbeddedObject::NumHeapFroms());
	AssertInt(1, pClusterMissile->mcMissile1.NumHeapFroms());
	strcpy(szClusterMissileState, "Alive");
	strcpy(szMissile1State, "Alive");

	pPointerPointer->Clear();

	AssertInt(1, pClusterMissile->NumHeapFroms());
	AssertInt(1, pClusterMissile->CEmbeddedObject::NumHeapFroms());
	AssertInt(0, pClusterMissile->mcMissile1.NumHeapFroms());
	AssertString("Alive", szClusterMissileState);
	AssertString("Alive", szMissile1State);

	pPointerPointer->mp = &pClusterMissile->mcMissile1;

	AssertInt(2, pClusterMissile->NumHeapFroms());
	AssertInt(1, pClusterMissile->CEmbeddedObject::NumHeapFroms());
	AssertInt(1, pClusterMissile->mcMissile1.NumHeapFroms());

	pPointerPointer2->Clear();

	AssertInt(1, pClusterMissile->NumHeapFroms());
	AssertInt(0, pClusterMissile->CEmbeddedObject::NumHeapFroms());
	AssertInt(1, pClusterMissile->mcMissile1.NumHeapFroms());
	AssertString("Alive", szClusterMissileState);
	AssertString("Alive", szMissile1State);

	pClusterMissile = NULL;

	//Make sure nothing has been de-allocated.
	AssertLongLongInt(7, gcObjects.GetMemory()->NumIndexed());
	AssertLongLongInt(7, gcUnknowns.NumElements());

	pPointerPointer->Clear();

	AssertString("Killed", szClusterMissileState);
	AssertString("Killed", szMissile1State);

	AssertLongLongInt(6, gcObjects.GetMemory()->NumIndexed());
	AssertLongLongInt(6, gcUnknowns.NumElements());

	gcObjects.Flush(TRUE, FALSE);

	AssertLongLongInt(0, gcObjects.GetMemory()->NumIndexed());
	AssertLongLongInt(0, gcUnknowns.NumElements());

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestEmbeddedObjectContainerDehollowfication(void)
{
	BOOL		bResult;
	CFileUtil	cFileUtil;
	char*		szClassName;
	OIndex		oiComplex;

	cFileUtil.RemoveDir("Output/EmbeddedObject");

	ObjectsInit("Output/EmbeddedObject/");
	SetupEmbeddedObjectConstructors();

	Ptr<CRoot> pRoot = ORoot();
	Ptr<CEmbeddedComplex> pComplex = OMalloc(CEmbeddedComplex)->Init();
	oiComplex = pComplex->GetOI();

	pRoot->Add(pComplex);

	bResult = gcObjects.Flush(TRUE, TRUE);
	ObjectsKill();
	AssertTrue(bResult);

	AssertInt(160, sizeof(CEmbeddedTest));
	AssertInt(496, sizeof(CEmbeddedContainer));
	AssertInt(944, sizeof(CEmbeddedComplex));

	ObjectsInit("Output/EmbeddedObject/");
	SetupEmbeddedObjectConstructors();

	pRoot = gcObjects.GetRoot();
	AssertTrue(pRoot.IsNotNull());
	pComplex = pRoot->Get(0);
	AssertTrue(pComplex.IsHollow());
	
	szClassName = pComplex->ClassName();
	AssertString("CEmbeddedComplex", szClassName);
	AssertLongLongInt(oiComplex, pComplex.GetIndex());

	AssertInt(1, pComplex->mai[0]);
	AssertInt(2, pComplex->mai[1]);
	
	AssertLongLongInt(INVALID_O_INDEX, pComplex->mcSimple.GetOI());
	AssertInt(85, pComplex->mcSimple.miAmANumber);
	AssertFloat(58.0f, pComplex->mcSimple.mfSoAmI, 0);

	AssertLongLongInt(INVALID_O_INDEX, pComplex->mcContainer.GetOI());
	AssertInt(73, pComplex->mcContainer.mi);
	AssertFloat(666.0f, pComplex->mcContainer.mf, 0);
	AssertString("And", pComplex->mcContainer.msz);

	AssertLongLongInt(INVALID_O_INDEX, pComplex->mcContainer.mcOne.GetOI());
	AssertInt(85, pComplex->mcContainer.mcOne.miAmANumber);
	AssertFloat(58.0f, pComplex->mcContainer.mcOne.mfSoAmI, 0);

	AssertLongLongInt(INVALID_O_INDEX, pComplex->mcContainer.mcTwo.GetOI());
	AssertInt(85, pComplex->mcContainer.mcTwo.miAmANumber);
	AssertFloat(58.0f, pComplex->mcContainer.mcTwo.mfSoAmI, 0);

	AssertLongLongInt(3, gcObjects.NumMemoryIndexes());

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestEmbeddedObjectPointTo(void)
{
	BOOL		bResult;
	CFileUtil	cFileUtil;
	OIndex		oiComplex;
	char*		szClassName;
	
	cFileUtil.RemoveDir("Output/EmbeddedObject");

	ObjectsInit("Output/EmbeddedObject/");
	SetupEmbeddedObjectConstructors();

	Ptr<CRoot> pRoot = ORoot();
	Ptr<CEmbeddedComplex> pComplex = OMalloc(CEmbeddedComplex)->Init();
	oiComplex = pComplex->GetOI();

	Ptr<CEmbeddedContainer> pContainer = &pComplex->mcContainer;
	pRoot->Add(pContainer);

	bResult = gcObjects.Flush(TRUE, TRUE);
	ObjectsKill();
	AssertTrue(bResult);

	AssertNull(&pContainer);

	ObjectsInit("Output/EmbeddedObject/");
	SetupEmbeddedObjectConstructors();

	pRoot = gcObjects.GetRoot();
	AssertTrue(pRoot.IsNotNull());
	pContainer = pRoot->Get(0);
	AssertTrue(pContainer.IsHollow());
	AssertInt(0, pContainer.Object()->GetNumEmbedded());
	AssertLongLongInt(-1, pContainer.GetIndex());

	szClassName = pContainer->ClassName();
	AssertString("CEmbeddedContainer", szClassName);

	pComplex = pContainer->GetEmbeddingContainer();
	//Kinda feels like this test just stopped...
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestEmbeddedGetEmbeddedIndex(void)
{
	ObjectsInit();

	CEmbeddedComplex	cComplex;

	cComplex.Class();
	cComplex.Init();

	AssertInt(0, cComplex.TestGetNumEmbeddedFromFlags());
	AssertInt(6, cComplex.GetNumEmbedded());
	AssertInt(6, cComplex.TestGetNumEmbeddedFromFlags());

	AssertInt(1, cComplex.mcSimple.GetNumEmbedded());
	AssertInt(1, cComplex.ma.GetNumEmbedded());
	AssertInt(3, cComplex.mcContainer.GetNumEmbedded());
	AssertInt(1, cComplex.mcContainer.mcOne.GetNumEmbedded());
	AssertInt(1, cComplex.mcContainer.mcOne.GetNumEmbedded());

	AssertInt(0, cComplex.GetEmbeddedIndex(&cComplex));
	AssertInt(1, cComplex.GetEmbeddedIndex(&cComplex.mcSimple));
	AssertInt(2, cComplex.GetEmbeddedIndex(&cComplex.ma));
	AssertInt(3, cComplex.GetEmbeddedIndex(&cComplex.mcContainer));
	AssertInt(4, cComplex.GetEmbeddedIndex(&cComplex.mcContainer.mcOne));
	AssertInt(5, cComplex.GetEmbeddedIndex(&cComplex.mcContainer.mcTwo));
	AssertInt(-1, cComplex.GetEmbeddedIndex(NULL));

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestEmbeddedGetEmbeddedObject(void)
{
	ObjectsInit();

	CEmbeddedComplex	cComplex;
	CEmbeddedObject*	pcEmbedded;

	cComplex.Class();
	cComplex.Init();

	pcEmbedded = cComplex.GetEmbeddedObject(0);
	AssertPointer(&cComplex, pcEmbedded);
	pcEmbedded = cComplex.GetEmbeddedObject(1);
	AssertPointer(&cComplex.mcSimple, pcEmbedded);
	pcEmbedded = cComplex.GetEmbeddedObject(2);
	AssertPointer(&cComplex.ma, pcEmbedded);
	pcEmbedded = cComplex.GetEmbeddedObject(3);
	AssertPointer(&cComplex.mcContainer, pcEmbedded);
	pcEmbedded = cComplex.GetEmbeddedObject(4);
	AssertPointer(&cComplex.mcContainer.mcOne, pcEmbedded);
	pcEmbedded = cComplex.GetEmbeddedObject(5);
	AssertPointer(&cComplex.mcContainer.mcTwo, pcEmbedded);
	pcEmbedded = cComplex.GetEmbeddedObject(6);
	AssertNull(pcEmbedded);

	pcEmbedded = cComplex.mcSimple.GetEmbeddedObject(0);
	AssertPointer(&cComplex.mcSimple, pcEmbedded);
	pcEmbedded = cComplex.mcSimple.GetEmbeddedObject(1);
	AssertNull(pcEmbedded);

	pcEmbedded = cComplex.ma.GetEmbeddedObject(0);
	AssertPointer(&cComplex.ma, pcEmbedded);
	pcEmbedded = cComplex.ma.GetEmbeddedObject(1);
	AssertNull(pcEmbedded);

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestEmbeddedObjectClass(void)
{
	ObjectsInit();

	CEmbeddedComplex	cComplex;
	CPointer*			pcPtr0;
	CPointer*			pcPtr1;
	CPointer*			pcPtr2;
	CPointer*			pcPtr3;
	CPointer*			pcPtr4;
	CPointer*			pcPtr5;

	//Class not yet called.  Always call Class.
	AssertInt(0, cComplex.GetNumFieldPointers());
	AssertInt(1, cComplex.GetNumEmbedded());

	cComplex.ClearFlagNumEmbedded();
	cComplex.Class();
	AssertInt(5, cComplex.GetNumFieldPointers());
	AssertInt(6, cComplex.GetNumEmbedded());

	pcPtr0 = cComplex.GetFieldPointer(0);
	pcPtr1 = cComplex.GetFieldPointer(1);
	pcPtr2 = cComplex.GetFieldPointer(2);
	pcPtr3 = cComplex.GetFieldPointer(3);
	pcPtr4 = cComplex.GetFieldPointer(4);
	pcPtr5 = cComplex.GetFieldPointer(5);

	AssertPointer(cComplex.mpTest.This(), pcPtr0);
	AssertPointer(cComplex.mcSimple.mpTest.This(), pcPtr1);
	AssertPointer(cComplex.mcContainer.mpTest.This(), pcPtr2);
	AssertPointer(cComplex.mcContainer.mcOne.mpTest.This(), pcPtr3);
	AssertPointer(cComplex.mcContainer.mcTwo.mpTest.This(), pcPtr4);
	AssertNull(pcPtr5);

	AssertInt(0, cComplex.GetFieldPointerIndex(pcPtr0));
	AssertInt(1, cComplex.GetFieldPointerIndex(pcPtr1));
	AssertInt(2, cComplex.GetFieldPointerIndex(pcPtr2));
	AssertInt(3, cComplex.GetFieldPointerIndex(pcPtr3));
	AssertInt(4, cComplex.GetFieldPointerIndex(pcPtr4));
	AssertInt(-1, cComplex.GetFieldPointerIndex(NULL));

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestEmbeddedOjectIsAllocatedInObjects()
{

	ObjectsInit();

	Ptr<CClusterMissile> pClusterMissile = ONMalloc(CClusterMissile, "Gerbil")->Init(NULL);
	AssertTrue(pClusterMissile->IsAllocatedInObjects());
	AssertTrue(pClusterMissile->mcMissile1.IsAllocatedInObjects());
	AssertTrue(pClusterMissile->mcMissile2.IsAllocatedInObjects());
	pClusterMissile = NULL;

	CClusterMissile cClusterMissile;
	cClusterMissile.Class();
	cClusterMissile.Init(NULL);
	AssertFalse(cClusterMissile.IsAllocatedInObjects());
	AssertFalse(cClusterMissile.mcMissile1.IsAllocatedInObjects());
	AssertFalse(cClusterMissile.mcMissile2.IsAllocatedInObjects());

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestEmbedded(void)
{
	BeginTests();

	TestEmbeddedFlags();
	TestEmbeddedOjectIsAllocatedInObjects();
	TestEmbeddedObjectAddDistToRoot();
	TestEmbeddedObjectRemoveDistToRoot();
	TestEmbeddedObjectKill();
	TestEmbeddedObjectContainerDehollowfication();
	TestEmbeddedGetEmbeddedIndex();
	TestEmbeddedObjectClass();
	TestEmbeddedGetEmbeddedObject();
	TestEmbeddedObjectPointTo();

	TestStatistics();
}

