#include "BaseLib/GlobalMemory.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/TypeNames.h"
#include "BaseLib/Codabase.h"
#include "BaseLib/CodabaseFactory.h"
#include "BaseLib/SequenceFactory.h"
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
	gcObjects.AddConstructor<CEmbeddedTest>();
	gcObjects.AddConstructor<CEmbeddedContainer>();
	gcObjects.AddConstructor<CEmbeddedComplex>();
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
	Ptr<CGameWorld>			pWorld = OMalloc<CGameWorld>();

	pRoot->Add(pWorld);

	Ptr<CClusterMissile>	pMissile = ONMalloc<CClusterMissile>("Frank", pWorld);
	Ptr<CHarrier>			pHarrier = OMalloc<CHarrier>(pWorld);
	
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
	Ptr<CGameWorld>			pWorld = OMalloc<CGameWorld>();

	pRoot->Add(pWorld);

	Ptr<CClusterMissile>	pMissile = ONMalloc<CClusterMissile>("Frank", pWorld);
	Ptr<CHarrier>			pHarrier = OMalloc<CHarrier>(pWorld);
	Ptr<CMissile>			pHolder = OMalloc<CMissile>(pWorld);
	
	pWorld->AddTickable(pHolder);
	AssertInt(4, pHolder->GetDistToRoot());

	pHolder->SetTarget(pHarrier);
	AssertInt(5, pHarrier->GetDistToRoot());

	Ptr<CClusterLauncher>	pLauncher = OMalloc<CClusterLauncher>();

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
	Ptr<CGameWorld> pWorld = OMalloc<CGameWorld>();

	pRoot->Add(pWorld);

	Ptr<CClusterMissile> pClusterMissile = ONMalloc<CClusterMissile>("Anna", pWorld);
	pWorld = NULL;

	Ptr<CPointerContainer> pPointerPointer = OMalloc<CPointerContainer>();
	pRoot->Add(pPointerPointer);
	pPointerPointer->Init(&pClusterMissile->mcMissile1);

	Ptr<CPointerContainer> pPointerPointer2 = OMalloc<CPointerContainer>();
	pRoot->Add(pPointerPointer2);
	pPointerPointer2->Init(&pClusterMissile);

	//The number of allocated object shouldn't change until all the froms are removed
	//both from the embedded object and the 'normal' object.
	AssertLong(7, gcObjects.GetMemory()->NumIndexed());
	AssertLong(7, gcUnknowns.NumElements());

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
	AssertLong(7, gcObjects.GetMemory()->NumIndexed());
	AssertLong(7, gcUnknowns.NumElements());

	pPointerPointer->Clear();

	AssertString("Killed", szClusterMissileState);
	AssertString("Killed", szMissile1State);

	AssertLong(6, gcObjects.GetMemory()->NumIndexed());
	AssertLong(6, gcUnknowns.NumElements());

	ObjectsFlush();
	gcObjects.EvictInMemory();

	AssertLong(0, gcObjects.GetMemory()->NumIndexed());
	AssertLong(0, gcUnknowns.NumElements());

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestEmbeddedObjectContainerDehollowfication(void)
{
	bool			bResult;
	CFileUtil		cFileUtil;
	const char*		szClassName;
	OIndex			oiComplex;
	CCodabase*		pcDatabase;
	CSequence*		pcSequence;
	char			szDirectory[] = "Output" _FS_ "EmbeddedObject";

	cFileUtil.RemoveDir(szDirectory);

	pcSequence = CSequenceFactory::Create(szDirectory);
	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase, pcSequence);
	SetupEmbeddedObjectConstructors();

	Ptr<CRoot> pRoot = ORoot();
	Ptr<CEmbeddedComplex> pComplex = OMalloc<CEmbeddedComplex>();
	oiComplex = pComplex->GetIndex();

	pRoot->Add(pComplex);

	bResult = ObjectsFlush();
	AssertTrue(bResult);
	bResult = gcObjects.EvictInMemory();
	AssertTrue(bResult);

	ObjectsFlush();
	pcDatabase->Close();
	SafeKill(pcDatabase);
	SafeKill(pcSequence);
	ObjectsKill();

	AssertInt(184, sizeof(CEmbeddedTest));
	AssertInt(568, sizeof(CEmbeddedContainer));
	AssertInt(1088, sizeof(CEmbeddedComplex));

	pcSequence = CSequenceFactory::Create(szDirectory);
	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase, pcSequence);
	SetupEmbeddedObjectConstructors();

	pRoot = gcObjects.Root();
	AssertTrue(pRoot.IsNotNull());
	pComplex = pRoot->Get(0);
	AssertTrue(pComplex.IsHollow());
	
	szClassName = pComplex->ClassName();
	AssertString("CEmbeddedComplex", szClassName);
	AssertLong(oiComplex, pComplex.GetIndex());

	AssertInt(1, pComplex->mai[0]);
	AssertInt(2, pComplex->mai[1]);
	
	AssertLong(INVALID_O_INDEX, pComplex->mcSimple.GetIndex());
	AssertInt(85, pComplex->mcSimple.miAmANumber);
	AssertFloat(58.0f, pComplex->mcSimple.mfSoAmI, 0);

	AssertLong(INVALID_O_INDEX, pComplex->mcContainer.GetIndex());
	AssertInt(73, pComplex->mcContainer.mi);
	AssertFloat(666.0f, pComplex->mcContainer.mf, 0);
	AssertString("And", pComplex->mcContainer.msz);

	AssertLong(INVALID_O_INDEX, pComplex->mcContainer.mcOne.GetIndex());
	AssertInt(85, pComplex->mcContainer.mcOne.miAmANumber);
	AssertFloat(58.0f, pComplex->mcContainer.mcOne.mfSoAmI, 0);

	AssertLong(INVALID_O_INDEX, pComplex->mcContainer.mcTwo.GetIndex());
	AssertInt(85, pComplex->mcContainer.mcTwo.miAmANumber);
	AssertFloat(58.0f, pComplex->mcContainer.mcTwo.mfSoAmI, 0);

	AssertLong(3, gcObjects.NumMemoryIndexes());

	ObjectsFlush();
	pcDatabase->Close();
	SafeKill(pcSequence);
	SafeKill(pcDatabase);
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestEmbeddedObjectPointTo(void)
{
	bool		bResult;
	CFileUtil	cFileUtil;
	OIndex		oiComplex;
	const char*	szClassName;
	CCodabase*	pcDatabase;
	CSequence*	pcSequence;
	char		szDirectory[] = "Output" _FS_ "EmbeddedObject";

	cFileUtil.RemoveDir(szDirectory);

	pcSequence = CSequenceFactory::Create(szDirectory);
	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase, pcSequence);
	SetupEmbeddedObjectConstructors();

	Ptr<CRoot> pRoot = ORoot();
	Ptr<CEmbeddedComplex> pComplex = OMalloc<CEmbeddedComplex>();
	oiComplex = pComplex->GetIndex();

	Ptr<CEmbeddedContainer> pContainer = &pComplex->mcContainer;
	pRoot->Add(pContainer);

	bResult = ObjectsFlush();
	AssertTrue(bResult);
	bResult = gcObjects.EvictInMemory();
	AssertTrue(bResult);

	ObjectsFlush();
	SafeKill(pcSequence);
	SafeKill(pcDatabase);
	ObjectsKill();

	AssertNull(&pContainer);


	pcSequence = CSequenceFactory::Create(szDirectory);
	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase, pcSequence);
	SetupEmbeddedObjectConstructors();

	pRoot = gcObjects.Root();
	AssertTrue(pRoot.IsNotNull());
	pContainer = pRoot->Get(0);
	AssertTrue(pContainer.IsHollow());
	AssertSize(0, pContainer.Object()->GetNumEmbedded());
	AssertLong(-1, pContainer.GetIndex());

	szClassName = pContainer->ClassName();
	AssertString("CEmbeddedContainer", szClassName);

	pComplex = pContainer->GetEmbeddingContainer();
	//Kinda feels like this test just stopped...

	ObjectsFlush();
	pcDatabase->Close();
	SafeKill(pcDatabase);
	SafeKill(pcSequence);
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestEmbeddedGetEmbeddedIndex(void)
{
	ObjectsInit();

	CEmbeddedComplex	cComplex;

	cComplex.Init();

	AssertInt(0, cComplex.TestGetNumEmbeddedFromFlags());
	AssertSize(6, cComplex.GetNumEmbedded());
	AssertInt(6, cComplex.TestGetNumEmbeddedFromFlags());

	AssertSize(1, cComplex.mcSimple.GetNumEmbedded());
	AssertSize(1, cComplex.ma.GetNumEmbedded());
	AssertSize(3, cComplex.mcContainer.GetNumEmbedded());
	AssertSize(1, cComplex.mcContainer.mcOne.GetNumEmbedded());
	AssertSize(1, cComplex.mcContainer.mcOne.GetNumEmbedded());

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
	AssertInt(0, cComplex.GetNumFieldPointerTos());
	AssertSize(1, cComplex.GetNumEmbedded());

	cComplex.ClearFlagNumEmbedded();
	cComplex.Init();
	AssertInt(5, cComplex.GetNumFieldPointerTos());
	AssertSize(6, cComplex.GetNumEmbedded());

	pcPtr0 = cComplex.GetFieldPointerTo(0);
	pcPtr1 = cComplex.GetFieldPointerTo(1);
	pcPtr2 = cComplex.GetFieldPointerTo(2);
	pcPtr3 = cComplex.GetFieldPointerTo(3);
	pcPtr4 = cComplex.GetFieldPointerTo(4);
	pcPtr5 = cComplex.GetFieldPointerTo(5);

	AssertPointer(cComplex.mpTest.This(), pcPtr0);
	AssertPointer(cComplex.mcSimple.mpTest.This(), pcPtr1);
	AssertPointer(cComplex.mcContainer.mpTest.This(), pcPtr2);
	AssertPointer(cComplex.mcContainer.mcOne.mpTest.This(), pcPtr3);
	AssertPointer(cComplex.mcContainer.mcTwo.mpTest.This(), pcPtr4);
	AssertNull(pcPtr5);

	AssertInt(0, cComplex.GetFieldPointerToIndex(pcPtr0));
	AssertInt(1, cComplex.GetFieldPointerToIndex(pcPtr1));
	AssertInt(2, cComplex.GetFieldPointerToIndex(pcPtr2));
	AssertInt(3, cComplex.GetFieldPointerToIndex(pcPtr3));
	AssertInt(4, cComplex.GetFieldPointerToIndex(pcPtr4));
	AssertInt(-1, cComplex.GetFieldPointerToIndex(NULL));

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestEmbeddedOjectIsAllocatedInObjects()
{
	ObjectsInit();

	Ptr<CClusterMissile> pClusterMissile = ONMalloc<CClusterMissile>("Gerbil", Null());
	AssertTrue(pClusterMissile->IsAllocatedInObjects());
	AssertTrue(pClusterMissile->mcMissile1.IsAllocatedInObjects());
	AssertTrue(pClusterMissile->mcMissile2.IsAllocatedInObjects());
	pClusterMissile = NULL;

	CClusterMissile cClusterMissile;
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
	MemoryInit();
	FastFunctionsInit();
	TypesInit();
	DataIOInit();

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

	DataIOKill();
	TypesKill();
	FastFunctionsKill();
	MemoryKill();
	TestStatistics();
}

