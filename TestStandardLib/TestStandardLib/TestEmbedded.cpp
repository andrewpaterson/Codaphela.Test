#include "StandardLib/Objects.h"
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
	AssertInt(3, pHarrier->DistToRoot());

	pRoot->Add(pMissile);

	AssertInt(2, pMissile->DistToRoot());
	AssertInt(2, pMissile->mcMissile1.DistToRoot());
	AssertInt(2, pMissile->mcMissile2.DistToRoot());

	pMissile->mcMissile1.SetTarget(pHarrier);

	AssertInt(3, pHarrier->DistToRoot());

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
	pHolder->SetTarget(pHarrier);

	AssertInt(5, pHarrier->DistToRoot());

	Ptr<CClusterLauncher>	pLauncher = OMalloc(CClusterLauncher)->Init();

	pRoot->Add(pLauncher);
	pLauncher->mpMissile = pMissile;

	AssertInt(3, pMissile->DistToRoot());
	AssertInt(3, pMissile->mcMissile1.DistToRoot());
	AssertInt(3, pMissile->mcMissile2.DistToRoot());
	AssertInt(5, pHarrier->DistToRoot());
	AssertInt(1, pHarrier->NumFroms());

	pMissile->mcMissile1.SetTarget(pHarrier);
	AssertInt(4, pHarrier->DistToRoot());
	AssertInt(2, pHarrier->NumFroms());

	pWorld->RemoveTickable(pHolder);
	AssertInt(4, pHarrier->DistToRoot());
	AssertInt(1, pHarrier->NumFroms());

	pRoot->Add(pHarrier);
	AssertInt(2, pHarrier->DistToRoot());

	pRoot->Remove(pHarrier);
	AssertInt(4, pHarrier->DistToRoot());

	ObjectsKill();
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestEmbeddedObjectKill(void)
{
	ObjectsInit();

	Ptr<CRoot>				pRoot = ORoot();
	Ptr<CGameWorld>			pWorld = OMalloc(CGameWorld)->Init();

	pRoot->Add(pWorld);

	Ptr<CClusterMissile>	pMissile = ONMalloc(CClusterMissile, "Frank")->Init(pWorld);
	Ptr<CHarrier>			pHarrier = OMalloc(CHarrier)->Init(pWorld);
	Ptr<CMissile>			pHolder = OMalloc(CMissile)->Init(pWorld);

	pWorld->AddTickable(pHolder);
	pHolder->SetTarget(pHarrier);


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

	ObjectsInit("Output/EmbeddedObject/");
	SetupEmbeddedObjectConstructors();

	pRoot = gcObjects.GetRoot();
	AssertTrue(pRoot.IsNotNull());
	pContainer = pRoot->Get(0);
	AssertTrue(pContainer.IsHollow());
	AssertInt(6, pContainer.Object()->GetNumEmbedded());

	szClassName = pContainer->ClassName();
	AssertString("CEmbeddedContainer", szClassName);

	pComplex = pContainer->GetEmbeddingContainer();
	AssertLongLongInt(oiComplex, pContainer.GetIndex());
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestEmbeddedGetEmbeddedIndex(void)
{
	CEmbeddedComplex	cComplex;

	cComplex.PreInit(NULL);
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
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestEmbeddedGetEmbeddedObject(void)
{
	CEmbeddedComplex	cComplex;
	CEmbeddedObject*	pcEmbedded;

	cComplex.PreInit(NULL);
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
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestEmbedded(void)
{
	BeginTests();

	TestEmbeddedObjectAddDistToRoot();
	TestEmbeddedObjectRemoveDistToRoot();
	TestEmbeddedObjectKill();
	TestEmbeddedObjectContainerDehollowfication();
	TestEmbeddedGetEmbeddedIndex();
	TestEmbeddedGetEmbeddedObject();
	TestEmbeddedObjectPointTo();

	TestStatistics();
}
