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
void TestReplaceAndRemapAddConstructors(void)
{
	gcObjects.AddConstructor<CTestObject>();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectReplaceNoPointers(void)
{
	Ptr<CTestObject>						pObject1;
	Ptr<CTestObject>						pObject2;
	Ptr<CTestObject>						pObject3;
	Ptr<CTestObject>						pObject4;
	STestObjectFreedNotifier				sFreeNotifider1;
	STestObjectFreedNotifier				sFreeNotifider2;
	STestObjectFreedNotifier				sFreeNotifider3;
	Ptr<CRoot>								pRoot;
	OIndex									oi1;
	OIndex									oi3;

	ObjectsInit();
	TestReplaceAndRemapAddConstructors();
	AssertInt(0, gcUnknowns.NumElements());

	pRoot = ORoot();
	pObject1 = ONMalloc<CTestObject>("Pavel", &sFreeNotifider1);
	pObject2 = ONMalloc<CTestObject>("Meninski", &sFreeNotifider2);
	pObject3 = ONMalloc<CTestObject>("Ned", &sFreeNotifider3);
	pRoot->Add(pObject1);
	pRoot->Add(pObject2);
	oi1 = pObject1->GetIndex();
	oi3 = pObject3->GetIndex();
	AssertLongLongInt(5, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(4, gcObjects.NumMemoryNames());
	AssertFalse(oi1 == oi3);
	AssertString("GraphRoot", pRoot->GetName());
	AssertInt(5, gcUnknowns.NumElements());

	gcObjects.ReplaceBaseObject(&pObject1, &pObject3);
	AssertLongLongInt(4, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(3, gcObjects.NumMemoryNames());
	AssertTrue(sFreeNotifider1.bFreed);
	AssertPointer(&pObject3, &pObject1);
	AssertFalse(sFreeNotifider2.bFreed);
	AssertFalse(sFreeNotifider3.bFreed);
	pObject4 = pRoot->Get(0);
	AssertPointer(&pObject3, &pObject4);
	AssertInt(4, gcUnknowns.NumElements());

	ObjectsFlush();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestReplaceAndRemap(void)
{
	BeginTests();
	MemoryInit();
	TypesInit();
	DataIOInit();

	TestObjectReplaceNoPointers();
	//TestObjectRemap();
	//TestObjectRename();

	DataIOKill();
	TypesKill();
	MemoryKill();
	TestStatistics();
}

