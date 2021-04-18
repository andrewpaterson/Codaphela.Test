#include "BaseLib/GlobalMemory.h"
#include "BaseLib/MemoryFile.h"
#include "BaseLib/LogToMemory.h"
#include "CoreLib/CodabaseFactory.h"
#include "CoreLib/SequenceFactory.h"
#include "StandardLib/Objects.h"
#include "StandardLib/String.h"
#include "TestLib/Assert.h"
#include "NamedObjectTestClasses.h"
#include "ObjectTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectDirtyAddConstructors(void)
{
	gcObjects.AddConstructor<CRoot>();
	gcObjects.AddConstructor<CTestObject>();
	gcObjects.AddConstructor<CTestTriPointerObject>();
	gcObjects.AddConstructor<CTestSaveableObject1>();
	gcObjects.AddConstructor<CTestSaveableObject2>();
	gcObjects.AddConstructor<CSetObject>();
	gcObjects.AddConstructor<CTestNamedObject>();
	gcObjects.AddConstructor<CTestNamedObjectSmall>();
	gcObjects.AddConstructor<CTestNamedObjectWithEmbedded>();
	gcObjects.AddConstructor<CTestObjectWithFields>();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectDirtySimplePrimitiveAssignment(void)
{
	Ptr<CTestObjectWithFields>	pObject;
	CCodabase*					pcDatabase;
	CSequence*					pcSequence;
	CFileUtil					cFileUtil;
	char						szDirectory[] = "Output" _FS_ "ObjectDirty" _FS_ "Database1";

	cFileUtil.RemoveDir(szDirectory);
	MemoryInit();


	pcSequence = CSequenceFactory::Create(szDirectory);
	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase, pcSequence);

	TestObjectDirtyAddConstructors();

	pObject = OMalloc<CTestObjectWithFields>();
	
	pObject->mi32 = 7;
	pObject->mui32 = (unsigned int)99;
	pObject->mi32 = (unsigned char)8;
	pObject->mf32 = 1.0f;
	pObject->mf64 = 1.0;
	pObject->mf64 = 2.0f;
	pObject->mf32 = 1;

	pObject->mi8 = 100;
	pObject->mui8 = 100;
	pObject->mi32 = 100;
	pObject->mui32 = 100;
	pObject->mi16 = 100;
	pObject->mui16 = 100;
	pObject->mc8 = 100;
	pObject->mc16 = 100;
	pObject->mf32 = 100;
	pObject->mf64 = 100;
	pObject->mi64 = 100;
	pObject->mui64 = 100;

	pObject->mb = TRUE;
	pObject->mb = FALSE;
	pObject->mb = true;
	pObject->mb = false;

	ObjectsFlush();
	pcDatabase->Close();
	SafeKill(pcDatabase);
	SafeKill(pcSequence);
	ObjectsKill();


	MemoryKill();
	cFileUtil.RemoveDir(szDirectory);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectDirtyOnPrimitiveAssignment(void)
{
	Ptr<CTestObjectWithFields>	pObject;
	OIndex						oi;
	CCodabase*					pcDatabase;
	CSequence*					pcSequence;
	CFileUtil					cFileUtil;
	char						szDirectory[] = "Output" _FS_ "ObjectDirty" _FS_ "Database2";

	cFileUtil.RemoveDir(szDirectory);
	MemoryInit();


	pcSequence = CSequenceFactory::Create(szDirectory);
	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase, pcSequence);
	TestObjectDirtyAddConstructors();


	pObject = OMalloc<CTestObjectWithFields>();
	oi = pObject->GetIndex();
	AssertTrue(pObject.IsDirty());

	pObject->Flush();
	AssertFalse(pObject.IsDirty());

	pObject->mi32 = 7;
	AssertTrue(pObject.IsDirty());

	ObjectsFlush();
	AssertFalse(pObject.IsDirty());

	pcDatabase->Close();
	SafeKill(pcDatabase);
	SafeKill(pcSequence);
	ObjectsKill();
	AssertNull(&pObject);


	pcSequence = CSequenceFactory::Create(szDirectory);
	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase, pcSequence);
	TestObjectDirtyAddConstructors();

	pObject = gcObjects.Get(oi);
	AssertInt(7, pObject->mi32);
	AssertFalse(pObject.IsDirty());

	pcDatabase->Close();
	SafeKill(pcDatabase);
	SafeKill(pcSequence);
	ObjectsKill();


	MemoryKill();
	cFileUtil.RemoveDir(szDirectory);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectDirtyOnPointerAssignment(void)
{
	Ptr<CTestNamedObject>		pObject1;
	Ptr<CTestNamedObject>		pObject2;
	Ptr<CTestNamedObject>		pObject3;
	CCodabase*					pcDatabase;
	CSequence*					pcSequence;
	CFileUtil					cFileUtil;
	char						szDirectory[] = "Output" _FS_ "ObjectDirty" _FS_ "Database3";

	cFileUtil.RemoveDir(szDirectory);
	MemoryInit();


	pcSequence = CSequenceFactory::Create(szDirectory);
	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase, pcSequence);
	TestObjectDirtyAddConstructors();


	pObject1 = ONMalloc<CTestNamedObject>("OBJ1", 1);
	pObject2 = ONMalloc<CTestNamedObject>("OBJ2", 2);
	pObject3 = ONMalloc<CTestNamedObject>("OBJ3", 3);
	ObjectsFlush(); 

	AssertFalse(pObject1.IsDirty());
	AssertFalse(pObject2.IsDirty());
	AssertFalse(pObject3.IsDirty());

	pObject1->mpNamedTest1 = pObject2;
	AssertTrue(pObject1.IsDirty());
	AssertTrue(pObject2.IsDirty());  //Because it's Froms changed.
	AssertFalse(pObject3.IsDirty());

	ObjectsFlush();
	pcDatabase->Close();
	SafeKill(pcDatabase);
	SafeKill(pcSequence);
	ObjectsKill();

	AssertNull(&pObject1);
	AssertNull(&pObject2);
	AssertNull(&pObject3);


	pcSequence = CSequenceFactory::Create(szDirectory);
	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase, pcSequence);
	TestObjectDirtyAddConstructors();

	pObject1 = gcObjects.Get("OBJ1");
	pObject2 = pObject1->mpNamedTest1;
	pObject3 = pObject1->mpNamedTest2;
	
	AssertFalse(pObject1.IsDirty());
	AssertString("OBJ2", pObject2.GetName());
	AssertFalse(pObject2.IsDirty());
	AssertNull(&pObject3);

	pcDatabase->Close();
	SafeKill(pcDatabase);
	SafeKill(pcSequence);
	ObjectsKill();


	MemoryKill();
	cFileUtil.RemoveDir(szDirectory);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectDirtyOnPrimitiveAssignmentWithEmbedded(void)
{
	Ptr<CTestEmbeddedObjectWithFields>	pObject;
	OIndex								oi;
	CCodabase*							pcDatabase;
	CSequence*							pcSequence;
	CFileUtil							cFileUtil;
	Ptr<CString>						pStringA;
	Ptr<CString>						pStringB;
	Ptr<CString>						pStringC;

	char								szDirectory[] = "Output" _FS_ "ObjectDirty" _FS_ "Database4";

	cFileUtil.RemoveDir(szDirectory);
	MemoryInit();


	pcSequence = CSequenceFactory::Create(szDirectory);
	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase, pcSequence);
	TestObjectDirtyAddConstructors();


	pObject = OMalloc<CTestEmbeddedObjectWithFields>();
	AssertTrue(pObject.IsDirty());
	AssertTrue(pObject->mcEmbedded1.IsDirty());
	AssertTrue(pObject->mcEmbedded2.IsDirty());

	pObject->Flush();
	AssertFalse(pObject.IsDirty());
	AssertFalse(pObject->mcEmbedded1.IsDirty());
	AssertFalse(pObject->mcEmbedded2.IsDirty());

	pObject->mcEmbedded1.mi32 = 7;
	AssertTrue(pObject.IsDirty());
	AssertTrue(pObject->mcEmbedded1.IsDirty());
	AssertTrue(pObject->mcEmbedded2.IsDirty());

	ObjectsFlush();
	AssertFalse(pObject.IsDirty());
	AssertFalse(pObject->mcEmbedded1.IsDirty());
	AssertFalse(pObject->mcEmbedded2.IsDirty());

	pObject->mbY = TRUE;
	AssertTrue(pObject.IsDirty());
	AssertTrue(pObject->mcEmbedded1.IsDirty());
	AssertTrue(pObject->mcEmbedded2.IsDirty());

	ObjectsFlush();
	AssertFalse(pObject.IsDirty());
	AssertFalse(pObject->mcEmbedded1.IsDirty());
	AssertFalse(pObject->mcEmbedded2.IsDirty());

	pStringA = (CPointer)OMalloc<CString>();
	pStringA->Set("Commander X16");
	pStringB = (CPointer)OMalloc<CString>();
	pStringB->Set("Fleetwood");
	pStringC = (CPointer)OMalloc<CString>();
	pStringC->Set("Master Git");

	pObject->mbX = TRUE;
	pObject->mbY = FALSE;
	pObject->mpObjectA = pStringA;
	pObject->mpObjectB = pStringB;
	pObject->mpObjectC = pStringC;
	pObject->mcEmbedded1.mi8 = -8;
	pObject->mcEmbedded1.mi16 = -16;
	pObject->mcEmbedded1.mi32 = -32;
	pObject->mcEmbedded1.mi64 = -64;
	pObject->mcEmbedded1.mf32 = 32.5f;
	pObject->mcEmbedded1.mf64 = 64.5;
	pObject->mcEmbedded1.mb = TRUE;
	pObject->mcEmbedded1.mui8 = 8;
	pObject->mcEmbedded1.mui16 = 16;
	pObject->mcEmbedded1.mui32 = 32;
	pObject->mcEmbedded1.mui64 = 64;
	pObject->mcEmbedded1.mc8= 'A';
	pObject->mcEmbedded1.mc16 = 'B';
	AssertTrue(pObject.IsDirty());
	AssertTrue(pObject->mcEmbedded1.IsDirty());
	AssertTrue(pObject->mcEmbedded2.IsDirty());

	oi = pObject.GetIndex();

	ObjectsFlush();
	AssertFalse(pObject.IsDirty());
	AssertFalse(pObject->mcEmbedded1.IsDirty());
	AssertFalse(pObject->mcEmbedded2.IsDirty());

	pcDatabase->Close();
	SafeKill(pcDatabase);
	SafeKill(pcSequence);
	ObjectsKill();
	AssertNull(&pObject);


	pcSequence = CSequenceFactory::Create(szDirectory);
	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase, pcSequence);
	TestObjectDirtyAddConstructors();

	pObject = gcObjects.Get(oi);

	pcDatabase->Close();
	SafeKill(pcDatabase);
	SafeKill(pcSequence);
	ObjectsKill();
	AssertNull(&pObject);

	MemoryKill();
	cFileUtil.RemoveDir(szDirectory);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectDirty(void)
{
	BeginTests();

	TestObjectDirtySimplePrimitiveAssignment();
	TestObjectDirtyOnPrimitiveAssignment();
	TestObjectDirtyOnPointerAssignment();
	TestObjectDirtyOnPrimitiveAssignmentWithEmbedded();

	//String
	//Hollow pointers
	//Hollow pointers in embedded 

	TestStatistics();
}

