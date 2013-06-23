#include "StandardLib/Objects.h"
#include "TestLib/Assert.h"
#include "ObjectTestSetup.h"


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
void TestEmbedded(void)
{
	BeginTests();

	TestEmbeddedObjectAddDistToRoot();
	TestEmbeddedObjectRemoveDistToRoot();

	TestStatistics();
}

