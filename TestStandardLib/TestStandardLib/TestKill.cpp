#include "StandardLib/Objects.h"
#include "TestLib/Assert.h"
#include "NamedObjectTestClasses.h"
#include "ObjectTestSetup.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestKillSelfPointer1(void)
{
	ObjectsInit();

	Ptr<CRoot>				pRoot;
	Ptr<CTestNamedObject>	pObject;
	BOOL					bResult;
	CBaseObject*			pvObject;

	pRoot = ORoot();

	pObject = OMalloc(CTestNamedObject);
	pObject->Init(1);
	pObject->mpNamedTest1 = pObject;

	pRoot->Add(pObject);
	AssertInt(1, pRoot->NumObjects());

	AssertLongLongInt(3, gcObjects.NumMemoryIndexes());

	pvObject = pObject.BaseObject();
	pObject = NULL;

	//pObject should be destroyed here and not cause a stack overflow.
	bResult = pRoot->Remove(pvObject);
	AssertTrue(bResult);
	AssertInt(0, pRoot->NumObjects());

	AssertLongLongInt(2, gcObjects.NumMemoryIndexes());

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestKillSelfPointer2(void)
{
	ObjectsInit();

	Ptr<CRoot>				pRoot;
	Ptr<CTestNamedObject>	pObject;
	BOOL					bResult;

	pRoot = ORoot();

	pObject = OMalloc(CTestNamedObject);
	pObject->Init(1);
	pObject->mpNamedTest1 = pObject;

	pRoot->Add(pObject);
	AssertInt(1, pRoot->NumObjects());

	AssertLongLongInt(3, gcObjects.NumMemoryIndexes());

	//pObject should not be destroyed here and not cause a stack overflow.
	bResult = pRoot->Remove(pObject);
	AssertTrue(bResult);
	AssertInt(0, pRoot->NumObjects());

	//If there were cyclic pointers then the object cannot tell it should be freed when a stack pointer is removed.
	pObject = NULL;
	AssertLongLongInt(2, gcObjects.NumMemoryIndexes());

	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestKillLongCyclicSelfPointer(void)
{
	ObjectsInit();

	Ptr<CRoot>				pRoot;
	Ptr<CTestNamedObject>	pObject1;
	Ptr<CTestNamedObject>	pObject2;
	Ptr<CTestNamedObject>	pObjectBase;
	BOOL					bResult;

	pRoot = ORoot();

	pObjectBase = OMalloc(CTestNamedObject);
	pObject1 = OMalloc(CTestNamedObject);
	pObjectBase->Init(0);
	pObject1->Init(1);
	pObjectBase->mpNamedTest1 = pObject1;
	pObject1->mpNamedTest1 = pObjectBase;

	pRoot->Add(pObjectBase);

	//pObject should be destroyed here and not cause a stack overflow.
	bResult = pRoot->Remove(pObjectBase);
	AssertTrue(bResult);

	ObjectsKill();
}


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
	//regardless of whether anything else points to them.
	//Those objects that did point to them will be updated to point to NULL.

	Ptr<CRoot>			pRoot;
	Ptr<CGameWorld>		pWorld;

	pRoot = ORoot();

	AssertLongLongInt(0, gcObjects.NumDatabaseNames());
	pWorld = OMalloc(CGameWorld);
	pWorld->Init();

	pRoot->Add(pWorld);

	Ptr<CHarrier> pHarrier = ONMalloc(CHarrier, "Harrier");
	pHarrier->Init(pWorld);

	Ptr<CJeep> pJeep = ONMalloc(CJeep, "Jeep");
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

	Ptr<CRedJet>	pRedJetGoose = ONMalloc(CRedJet, "Goose");
	Ptr<CRedJet>	pRedJetMaverick = ONMalloc(CRedJet, "Maverick");

	pRedJetGoose->Init(pWorld);
	pRedJetMaverick->Init(pWorld);

	pRedJetGoose->SetKillHook(&sGooseBefore, &sGooseAfter);
	pRedJetMaverick->SetKillHook(&sMaverickBefore, &sMaverickAfter);

	Ptr<CMissile> pMissile1 = pHarrier->FireMissile(pRedJetGoose);
	Ptr<CMissile> pMissile2 = pHarrier->FireMissile(pRedJetGoose);
	Ptr<CMissile> pMissile3 = pHarrier->FireMissile(pRedJetMaverick);

	AssertString("Kill not called", sMaverickBefore.cPicture.mszPretenedImAPicture);
	AssertString("Kill not called", sMaverickAfter.cPicture.mszPretenedImAPicture);
	AssertLongLongInt(12, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(5, gcObjects.NumMemoryNames());
	AssertLongLongInt(0, gcObjects.NumDatabaseObjects());
	AssertLongLongInt(0, gcObjects.NumDatabaseNames());
	AssertInt(2, pWorld.GetDistToRoot());
	AssertInt(3, pHarrier.GetDistToRoot());
	AssertInt(3, pJeep.GetDistToRoot());
	AssertInt(4, pRedJetGoose.GetDistToRoot());
	AssertInt(4, pRedJetMaverick.GetDistToRoot());
	AssertInt(4, pMissile1.GetDistToRoot());
	AssertInt(4, pMissile2.GetDistToRoot());
	AssertInt(4, pMissile3.GetDistToRoot());
	AssertInt(2, pRedJetMaverick->NumHeapFroms());
	AssertInt(3, pHarrier->GetMissiles()->NumElements());

	OIndex oiMissile3 = pMissile3->GetOI();
	AssertLongLongInt(12LL, oiMissile3);

	pMissile3->Kill();  //<-- This is what is being tested.
	pMissile3 = gcObjects.TestGetFromMemory(oiMissile3);
	AssertTrue(pMissile3.IsNull());

	AssertString("Kill not called", sMaverickBefore.cPicture.mszPretenedImAPicture);
	AssertString("Kill not called", sMaverickAfter.cPicture.mszPretenedImAPicture);
	AssertLongLongInt(11, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(5, gcObjects.NumMemoryNames());
	AssertLongLongInt(0, gcObjects.NumDatabaseObjects());
	AssertLongLongInt(0, gcObjects.NumDatabaseNames());
	AssertInt(2, pWorld.GetDistToRoot());
	AssertInt(3, pHarrier.GetDistToRoot());
	AssertInt(3, pJeep.GetDistToRoot());
	AssertInt(4, pRedJetGoose.GetDistToRoot());
	AssertInt(4, pRedJetMaverick.GetDistToRoot());
	AssertInt(4, pMissile1.GetDistToRoot());
	AssertInt(4, pMissile2.GetDistToRoot());
	AssertInt(1, pRedJetMaverick->NumHeapFroms());
	AssertInt(2, pHarrier->GetMissiles()->NumElements());

	AssertString("Kill not called", sGooseBefore.cPicture.mszPretenedImAPicture);
	AssertString("Kill not called", sGooseAfter.cPicture.mszPretenedImAPicture);

	pRedJetGoose->Kill();
	AssertString("012345678901234", sGooseBefore.cPicture.mszPretenedImAPicture);
	AssertString("Alas I am Dead!", sGooseAfter.cPicture.mszPretenedImAPicture);
	AssertInt(1, pMissile1->NumTos());
	CPointer pTarget1(pMissile1->GetTarget());
	AssertTrue(pTarget1.IsNull());
	AssertInt(1, pMissile2->NumTos());
	CPointer pTarget2 = pMissile2->GetTarget();
	AssertTrue(pTarget2.IsNull());
	AssertLongLongInt(10, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(4, gcObjects.NumMemoryNames());
	AssertLongLongInt(0, gcObjects.NumDatabaseObjects());
	AssertLongLongInt(0, gcObjects.NumDatabaseNames());
	AssertInt(2, pWorld.GetDistToRoot());
	AssertInt(3, pHarrier.GetDistToRoot());
	AssertInt(3, pJeep.GetDistToRoot());
	AssertInt(4, pRedJetMaverick.GetDistToRoot());
	AssertInt(4, pMissile1.GetDistToRoot());
	AssertInt(4, pMissile2.GetDistToRoot());

	pMissile1->Kill();
	pMissile2->Kill();
	AssertInt(0, pHarrier->GetMissiles()->NumElements());
	AssertTrue(pMissile1.IsNull());
	AssertTrue(pMissile2.IsNull());

	pJeep = NULL;
	pRedJetMaverick = NULL;
	pHarrier = NULL;

	//pHarrier.maMissiles.moi == 6
	//pWorld.maTickables.moi == 4
	//pWorld is pointed to from:
	//  pRoot.mpObjects
	//  pHarrier
	//  pJeep
	//  pRedJetMaverick

	pRoot->Remove(pWorld);
	//ERROR: (baseobject.cpp:1159) void __thiscall CBaseObject::ValidateCanFindRoot(void) Object {02596128 [ 4]:CArrayObject(128) 6} has a positive dist to root and should be able to find the Root object.

	AssertLongLongInt(8, gcObjects.NumMemoryIndexes());
	pWorld = NULL;

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
void TestKillCanFindRoot(void)
{
	ObjectsInit();

	Ptr<CRoot>			pRoot;
	Ptr<CGameWorld>		pWorld;
	CGameWorld*			pcWorld;

	pRoot = ORoot();

	pWorld = OMalloc(CGameWorld);
	pWorld->Init();

	pRoot->Add(pWorld);

	Ptr<CHarrier> pHarrier = ONMalloc(CHarrier, "Harrier");
	pHarrier->Init(pWorld);

	Ptr<CJeep> pJeep = ONMalloc(CJeep, "Jeep");
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

	Ptr<CRedJet>	pRedJetGoose = ONMalloc(CRedJet, "Goose");
	Ptr<CRedJet>	pRedJetMaverick = ONMalloc(CRedJet, "Maverick");

	pRedJetGoose->Init(pWorld);
	pRedJetMaverick->Init(pWorld);

	pRedJetGoose->SetKillHook(&sGooseBefore, &sGooseAfter);
	pRedJetMaverick->SetKillHook(&sMaverickBefore, &sMaverickAfter);

	AssertTrue(pJeep->CanFindRoot());
	AssertTrue(pRedJetMaverick->CanFindRoot());
	AssertTrue(pHarrier->CanFindRoot());
	AssertTrue(pHarrier->GetMissiles()->CanFindRoot());
	AssertTrue(pRedJetGoose->CanFindRoot());
	AssertTrue(pWorld->CanFindRoot());
	AssertTrue(pWorld->GetTickables()->CanFindRoot());
	AssertTrue(pRoot->CanFindRoot());
	AssertTrue(pRoot->TestGetSet()->CanFindRoot());
	AssertLongLongInt(9, gcObjects.NumMemoryIndexes());

	//     
	// 4        ArrayObject[6](4)
	// 4                 ^
	// 4                 |                     pRedJetGoose[8,Goose](4)
	// 4                 |                            ^/
	//                   |                           //  pRedJetMaverick[9,Maverick](4)
	// 3  pHarrier[5,Harrier](3)   pJeep[7,Jeep](3) //   ^/  
	// 3                |^     ^   /^     ^        //   //
	// 3                ||      \ //      |       //   //
	// 3                ||       //       |      //   //
	// 3                ||      //\       |     //   //
	// 3                ||     //  \      |    /.   //
	// 3                ||    //   ArrayObject[4](3)/
	//                  ||   //    ^          .    /
	// 2                ||  //    /          /    /
	// 2                v| v/    /          v    v 
	// 2               pWorld[3](2)---------------
	//                   ^
	// 1                 |
	// 1             SetObject[2](1)
	//                   ^
	// 0                 |
	// 0              pRoot[1,GraphRoot](0)
	//  

	pRoot->Remove(pWorld);
	AssertFalse(pJeep->CanFindRoot());
	AssertFalse(pRedJetMaverick->CanFindRoot());
	AssertFalse(pHarrier->CanFindRoot());
	AssertFalse(pHarrier->GetMissiles()->CanFindRoot());  //The destruction of the pointer created by pHarrier->GetMissiles() set a lot of the root distances to -2.
	AssertFalse(pRedJetGoose->CanFindRoot());
	AssertFalse(pWorld->CanFindRoot());
	AssertFalse(pWorld->GetTickables()->CanFindRoot());
	AssertTrue(pRoot->CanFindRoot());
	AssertTrue(pRoot->TestGetSet()->CanFindRoot());
	AssertInt(-1, pJeep->GetDistToRoot());
	AssertInt(-1, pRedJetMaverick->GetDistToRoot());
	AssertInt(-1, pHarrier->GetDistToRoot());
	AssertInt(-1, pHarrier->GetMissiles()->GetDistToRoot());
	AssertInt(-1, pRedJetGoose->GetDistToRoot());
	AssertInt(-1, pWorld->GetDistToRoot());
	AssertInt(-1, pWorld->GetTickables()->GetDistToRoot());
	AssertLongLongInt(9, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(5, gcObjects.NumMemoryNames());
	AssertLongLongInt(0, gcObjects.NumDatabaseObjects());
	AssertLongLongInt(0, gcObjects.NumDatabaseNames());

	pJeep = NULL;
	pRedJetMaverick = NULL;
	pHarrier = NULL;
	pRedJetGoose = NULL;
	pcWorld = &pWorld;
	pWorld = NULL;

	AssertLongLongInt(2, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(1, gcObjects.NumMemoryNames());

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

	TestKillSelfPointer1();
	TestKillSelfPointer2();
	TestKillLongCyclicSelfPointer();
	TestKillBestPractice();
	TestKillCanFindRoot();

	TestStatistics();
}


