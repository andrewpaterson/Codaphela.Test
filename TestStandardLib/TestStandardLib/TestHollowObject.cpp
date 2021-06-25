#include "BaseLib/GlobalMemory.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/TypeNames.h"
#include "CoreLib/SequenceFactory.h"
#include "CoreLib/CodabaseFactory.h"
#include "StandardLib/Objects.h"
#include "StandardLib/String.h"
#include "StandardLib/Root.h"
#include "StandardLib/PointerContainer.h"
#include "TestLib/Assert.h"
#include "ObjectTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestHollowObjectAddConstructors(void)
{
	gcObjects.AddConstructor<CTestObject>();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestHollowObject1(void)
{
	CFileUtil					cFileUtil;
	Ptr<CTestObject>			pObject1;
	Ptr<CTestObject>			pObject2;
	Ptr<CTestObject>			pObject3;
	Ptr<CRoot>					pRoot;
	CCodabase*					pcDatabase;
	CSequence*					pcSequence;
	STestObjectFreedNotifier	sFreeNotifider1;
	STestObjectFreedNotifier	sFreeNotifider2;
	STestObjectFreedNotifier	sFreeNotifider3;
	char						szDirectory[] = "Output" _FS_ "HollowObject";

	cFileUtil.RemoveDir(szDirectory);
	cFileUtil.TouchDir(szDirectory);


	pcSequence = CSequenceFactory::Create(szDirectory);
	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase, pcSequence);
	TestHollowObjectAddConstructors();

	pRoot = ORoot();
	pObject1 = ONMalloc<CTestObject>("Paval", &sFreeNotifider1);
	pObject2 = ONMalloc<CTestObject>("Meninski", &sFreeNotifider2);
	pObject3 = ONMalloc<CTestObject>("Ned", &sFreeNotifider3);
	pRoot->Add(pObject1);
	pObject1->mpTest = pObject2;
	pObject2->mpTest = pObject3;
	
	AssertTrue(pObject1->IsDirty());
	AssertTrue(pObject2->IsDirty());
	AssertTrue(pObject3->IsDirty());
	ObjectsFlush();

	AssertFalse(pObject1->IsDirty());
	AssertFalse(pObject2->IsDirty());
	AssertFalse(pObject3->IsDirty());
	pcDatabase->Close();
	SafeKill(pcSequence);
	SafeKill(pcDatabase);
	ObjectsKill();

	pcSequence = CSequenceFactory::Create(szDirectory);
	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase, pcSequence);

	AssertFalse(pObject1->IsDirty());
	AssertFalse(pObject2->IsDirty());
	AssertFalse(pObject3->IsDirty());
	ObjectsFlush();
	pcDatabase->Close();
	SafeKill(pcSequence);
	SafeKill(pcDatabase);
	ObjectsKill();

	cFileUtil.RemoveDir(szDirectory);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestHollowObject(void)
{
	BeginTests();
	MemoryInit();
	TypesInit();
	DataIOInit();

	TestHollowObject1();

	DataIOKill();
	TypesKill();
	MemoryKill();
	TestStatistics();
}

