#include "StandardLib/Objects.h"
#include "StandardLib/ObjectWriter.h"
#include "StandardLib/ObjectReader.h"
#include "StandardLib/ClassDefines.h"
#include "ObjectTestSetup.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CGraphicPicture::Init(void)
{
	strcpy(mszPretenedImAPicture, "012345678901234");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CGraphicPicture::Kill(void)
{
	strcpy(mszPretenedImAPicture, "Alas I am Dead!");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
Ptr<CPlayerVehicle> CPlayerVehicle::Init(void)
{
	PreInit();
	mpsPoint = (SPhysicsPoint*)malloc(sizeof(SPhysicsPoint));
	mcPicture.Init();

	mpsPoint->x = 'X';
	mpsPoint->y = 'Y';
	mpsPoint->z = 'Z';

	mpsBeforeDeath = NULL;
	mpsAfterDeath = NULL;

	PostInit();
	return Ptr<CPlayerVehicle>(this);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CPlayerVehicle::Class(void)
{
	U_Data(CGraphicPicture, mcPicture);
	U_Data(SPhysicsPoint, mpsPoint);
	U_Pointer(mpsBeforeDeath);
	U_Pointer(mpsAfterDeath);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CPlayerVehicle::Free(void)
{
	if (mpsBeforeDeath)
	{
		memcpy(&mpsBeforeDeath->sPoint, mpsPoint, sizeof(SPhysicsPoint));
		memcpy(&mpsBeforeDeath->cPicture, &mcPicture, sizeof(CGraphicPicture));
	}

	mcPicture.Kill();
	free(mpsPoint);
	mpsPoint = NULL;

	if (mpsAfterDeath)
	{
		memset(&mpsAfterDeath->sPoint, 0, sizeof(SPhysicsPoint));
		memcpy(&mpsAfterDeath->cPicture, &mcPicture, sizeof(CGraphicPicture));
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CPlayerVehicle::SetKillHook(SStateOnKill* psBeforeDeath, SStateOnKill* psAfterDeath)
{
	mpsBeforeDeath = psBeforeDeath;
	mpsAfterDeath = psAfterDeath;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
Ptr<CHarrier> CHarrier::Init(Ptr<CGameWorld> pWorld)
{
	PreInit();

	CPlayerVehicle::Init();
	mpWorld = pWorld;
	miSpeed = 7;

	maMissiles = OMalloc<CArray<CMissile>>();

	PostInit();
	return Ptr<CHarrier>(this);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CHarrier::Class(void)
{
	CPlayerVehicle::Class();

	M_Pointer(mpWorld);
	M_Pointer(maMissiles);
	U_Int32(miSpeed);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CHarrier::Free(void)
{
	CPlayerVehicle::Free();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
Ptr<CMissile> CHarrier::FireMissile(CPointer& pTarget)
{
	Ptr<CMissile> pMissile = OMalloc<CMissile>(mpWorld);
	maMissiles->Add(pMissile);
	pMissile->SetTarget(pTarget);

	mpWorld->AddTickable(pMissile);

	return pMissile;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
Ptr<CArray<CMissile>> CHarrier::GetMissiles(void)
{
	return maMissiles;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
Ptr<CJeep> CJeep::Init(Ptr<CGameWorld> pWorld)
{
	PreInit();

	CPlayerVehicle::Init();
	mpWorld = pWorld;
	mfBackWheel = 2.3f;
	mfFrontWheel = 2.1f;

	PostInit();
	return Ptr<CJeep>(this);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CJeep::Class(void)
{
	CPlayerVehicle::Class();

	M_Pointer(mpWorld);
	U_Float32(mfFrontWheel);
	U_Float32(mfBackWheel);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CJeep::Free(void)
{
	CPlayerVehicle::Free();
	mfBackWheel = 0.0f;
	mfFrontWheel = 0.0f;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
Ptr<CMissile> CMissile::Init(Ptr<CGameWorld> pWorld)
{
	PreInit();
	mpWorld = pWorld;
	mpTarget = NULL;

	mszKillState = NULL;

	PostInit();
	return Ptr<CMissile>(this);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CMissile::Class(void)
{
	M_Pointer(mpWorld);
	M_Pointer(mpTarget);
	U_Pointer(mszKillState);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CMissile::Free(void)
{
	if (mszKillState)
	{
		strcpy(mszKillState, "Killed");
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CPointer CMissile::GetTarget(void)
{
	return mpTarget;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CMissile::SetTarget(CPointer& pTarget)
{
	mpTarget = pTarget;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CMissile::SetKillString(char* szKillString)
{
	mszKillState = szKillString;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
Ptr<CRedJet> CRedJet::Init(Ptr<CGameWorld> pWorld)
{
	PreInit();

	mpsPoint = (SPhysicsPoint*)malloc(sizeof(SPhysicsPoint));
	mcPicture.Init();

	mpWorld = pWorld;

	Ptr<CRedJet> pThis;
	pThis = this;
	mpWorld->AddTickable(pThis);

	PostInit();
	return Ptr<CRedJet>(this);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CRedJet::Class(void)
{
	U_Data(CGraphicPicture, mcPicture);
	M_Pointer(mpWorld);
	U_Data(SPhysicsPoint, mpsPoint);
	U_Pointer(mpsBeforeDeath);
	U_Pointer(mpsAfterDeath);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CRedJet::Free(void)
{
	memcpy(&mpsBeforeDeath->sPoint, mpsPoint, sizeof(SPhysicsPoint));
	memcpy(&mpsBeforeDeath->cPicture, &mcPicture, sizeof(CGraphicPicture));

	mcPicture.Kill();
	free(mpsPoint);
	mpsPoint = NULL;

	memset(&mpsAfterDeath->sPoint, 0, sizeof(SPhysicsPoint));
	memcpy(&mpsAfterDeath->cPicture, &mcPicture, sizeof(CGraphicPicture));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CRedJet::SetKillHook(SStateOnKill* psBeforeDeath, SStateOnKill* psAfterDeath)
{
	mpsBeforeDeath = psBeforeDeath;
	mpsAfterDeath = psAfterDeath;

	strcpy(mpsBeforeDeath->cPicture.mszPretenedImAPicture, "Kill not called");
	strcpy(mpsAfterDeath->cPicture.mszPretenedImAPicture, "Kill not called");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
Ptr<CClusterMissile> CClusterMissile::Init(Ptr<CGameWorld> pWorld)
{
	PreInit();

	mcMissile1.Init(pWorld);
	mcMissile2.Init(pWorld);

	mszKillState = NULL;

	PostInit();
	return Ptr<CClusterMissile>(this);
}



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CClusterMissile::Class(void)
{
	M_Pointer(mpWorld);
	M_Embedded(mcMissile1);
	M_Embedded(mcMissile2);
	U_Pointer(mszKillState);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CClusterMissile::Free(void)
{
	if (mszKillState)
	{
		strcpy(mszKillState, "Killed");
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CClusterMissile::SetKillString(char* szKillString)
{
	mszKillState = szKillString;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
Ptr<CClusterLauncher> CClusterLauncher::Init(void)
{
	PreInit();
	PostInit();
	return Ptr<CClusterLauncher>(this);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CClusterLauncher::Free(void)
{
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CClusterLauncher::Class(void)
{
	M_Pointer(mpMissile);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
Ptr<CGameWorld> CGameWorld::Init(void)
{
	PreInit();
	maTickables = OMalloc<CArray<>>();
	PostInit();
	return Ptr<CGameWorld>(this);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CGameWorld::Free(void)
{
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CGameWorld::Class(void)
{
	M_Pointer(maTickables);
	M_Pointer(mpPlayer1);
	M_Pointer(mpPlayer2);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CGameWorld::Tick(void)
{
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CGameWorld::AddPlayer(Ptr<CPlayerVehicle> pPlayer)
{
	if (pPlayer.IsNull())
	{
		return;
	}

	if (mpPlayer1.IsNull())
	{
		mpPlayer1 = pPlayer;
	}
	else if (mpPlayer2.IsNull())
	{
		mpPlayer2 = pPlayer;
	}
	else
	{
		return;
	}

	maTickables->Add(pPlayer);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CGameWorld::AddTickable(CPointer& pTickable)
{
	if (pTickable.IsNotNull())
	{
		maTickables->Add(pTickable);
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CGameWorld::RemoveTickable(CPointer& pTickable)
{
	if (pTickable.IsNotNull())
	{
		maTickables->Remove(pTickable);
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
Ptr<CArray<>> CGameWorld::GetTickables(void)
{
	return maTickables;
}

