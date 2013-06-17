#include "StandardLib/Objects.h"
#include "TestLib/Assert.h"
#include "ObjectTestSetup.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestKillBestPractice(void)
{
	ObjectsInit();

	//Generally an object will be killed if all pointers to it a removed.
	//Sometimes we'd rather not try and remove all the pointers we just want the object to die.
	//In the example below if a missile hits a jet then both objects should be removed;
	//regardless of wether anything else points to them.
	//Those objects that did point to them will be updated to point to NULL.

	CPointer<CRoot>			pRoot;
	CPointer<CGameWorld>	pWorld;

	pRoot = ORoot();
	pWorld = OMalloc(CGameWorld);
	pWorld->Init();

	pRoot->Add(pWorld);

	CPointer<CHarrier> pHarrier = ONMalloc(CHarrier, "Harrier");
	pHarrier->Init(pWorld);

	CPointer<CJeep> pJeep = ONMalloc(CJeep, "Jeep");
	pJeep->Init(pWorld);

	pWorld->AddPlayer(pHarrier);
	pWorld->AddPlayer(pJeep);

	SStateOnKill	sHarrierBefore;
	SStateOnKill	sHarrierAfter;
	SStateOnKill	sJeepBefore;
	SStateOnKill	sJeepAfter;

	pHarrier->SetKillHook(&sHarrierBefore, &sHarrierAfter);
	pJeep->SetKillHook(&sJeepBefore, &sJeepAfter);

	SStateOnKill	sGooseBefore;
	SStateOnKill	sGooseAfter;
	SStateOnKill	sMaverickBefore;
	SStateOnKill	sMaverickAfter;

	CPointer<CRedJet>	pRedJetGoose = ONMalloc(CRedJet, "Goose");
	CPointer<CRedJet>	pRedJetMaverick = ONMalloc(CRedJet, "Maverick");

	pRedJetGoose->Init(pWorld);
	pRedJetMaverick->Init(pWorld);

	pRedJetGoose->SetKillHook(&sGooseBefore, &sGooseAfter);
	pRedJetMaverick->SetKillHook(&sMaverickBefore, &sMaverickAfter);

	CPointer<CMissile> pMissile1 = pHarrier->FireMissile(pRedJetGoose);
	CPointer<CMissile> pMissile2 = pHarrier->FireMissile(pRedJetGoose);
	CPointer<CMissile> pMissile3 = pHarrier->FireMissile(pRedJetMaverick);

	AssertString("Kill not called", sMaverickBefore.cPicture.mszPretenedImAPicture);
	AssertString("Kill not called", sMaverickAfter.cPicture.mszPretenedImAPicture);
	AssertLongLongInt(12, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(5, gcObjects.NumMemoryNames());
	AssertLongLongInt(0, gcObjects.NumDatabaseObjects());
	AssertLongLongInt(0, gcObjects.NumDatabaseNames());
	AssertInt(2, pWorld.DistToRoot());
	AssertInt(3, pHarrier.DistToRoot());
	AssertInt(3, pJeep.DistToRoot());
	AssertInt(4, pRedJetGoose.DistToRoot());
	AssertInt(4, pRedJetMaverick.DistToRoot());
	AssertInt(4, pMissile1.DistToRoot());
	AssertInt(4, pMissile2.DistToRoot());
	AssertInt(4, pMissile3.DistToRoot());
	AssertInt(2, pRedJetMaverick->NumFroms());
	AssertInt(3, pHarrier->GetMissiles()->NumElements());

	OIndex oiMissile3 = pMissile3->GetOI();

	pMissile3->Kill();  //<-- This is what is being tested.
	pMissile3 = gcObjects.TestGetFromMemory(oiMissile3);
	AssertTrue(pMissile3.IsNull());

	AssertString("Kill not called", sMaverickBefore.cPicture.mszPretenedImAPicture);
	AssertString("Kill not called", sMaverickAfter.cPicture.mszPretenedImAPicture);
	AssertLongLongInt(11, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(5, gcObjects.NumMemoryNames());
	AssertLongLongInt(0, gcObjects.NumDatabaseObjects());
	AssertLongLongInt(0, gcObjects.NumDatabaseNames());
	AssertInt(2, pWorld.DistToRoot());
	AssertInt(3, pHarrier.DistToRoot());
	AssertInt(3, pJeep.DistToRoot());
	AssertInt(4, pRedJetGoose.DistToRoot());
	AssertInt(4, pRedJetMaverick.DistToRoot());
	AssertInt(4, pMissile1.DistToRoot());
	AssertInt(4, pMissile2.DistToRoot());
	AssertInt(1, pRedJetMaverick->NumFroms());
	AssertInt(2, pHarrier->GetMissiles()->NumElements());

	AssertString("Kill not called", sGooseBefore.cPicture.mszPretenedImAPicture);
	AssertString("Kill not called", sGooseAfter.cPicture.mszPretenedImAPicture);

	pRedJetGoose->Kill();
	AssertString("012345678901234", sGooseBefore.cPicture.mszPretenedImAPicture);
	AssertString("Alas I am Dead!", sGooseAfter.cPicture.mszPretenedImAPicture);
	AssertInt(1, pMissile1->NumTos());
	CPointerObject pTarget1 = pMissile1->GetTarget();
	AssertTrue(pTarget1.IsNull());
	AssertInt(1, pMissile2->NumTos());
	CPointerObject pTarget2 = pMissile2->GetTarget();
	AssertTrue(pTarget2.IsNull());
	AssertLongLongInt(10, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(4, gcObjects.NumMemoryNames());
	AssertLongLongInt(0, gcObjects.NumDatabaseObjects());
	AssertLongLongInt(0, gcObjects.NumDatabaseNames());
	AssertInt(2, pWorld.DistToRoot());
	AssertInt(3, pHarrier.DistToRoot());
	AssertInt(3, pJeep.DistToRoot());
	AssertInt(4, pRedJetMaverick.DistToRoot());
	AssertInt(4, pMissile1.DistToRoot());
	AssertInt(4, pMissile2.DistToRoot());

	pMissile1->Kill();
	pMissile2->Kill();
	AssertInt(0, pHarrier->GetMissiles()->NumElements());


	pRoot->Remove(pWorld);

	AssertLongLongInt(2, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(1, gcObjects.NumMemoryNames());
	AssertLongLongInt(0, gcObjects.NumDatabaseObjects());
	AssertLongLongInt(0, gcObjects.NumDatabaseNames());

	AssertInt('X', sHarrierBefore.sPoint.x);
	AssertInt('Y', sHarrierBefore.sPoint.y);
	AssertInt('Z', sHarrierBefore.sPoint.z);
	AssertString("012345678901234", sHarrierBefore.cPicture.mszPretenedImAPicture);
	AssertString("Alas I am Dead!", sHarrierAfter.cPicture.mszPretenedImAPicture);
	AssertString("012345678901234", sJeepBefore.cPicture.mszPretenedImAPicture);
	AssertString("Alas I am Dead!", sJeepAfter.cPicture.mszPretenedImAPicture);

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestKill(void)
{
	BeginTests();

	TestKillBestPractice();

	TestStatistics();
}


