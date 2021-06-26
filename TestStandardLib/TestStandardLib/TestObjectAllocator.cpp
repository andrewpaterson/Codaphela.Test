#include "BaseLib/GlobalMemory.h"
#include "BaseLib/MemoryFile.h"
#include "BaseLib/LogToMemory.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/TypeNames.h"
#include "CoreLib/CodabaseFactory.h"
#include "CoreLib/SequenceFactory.h"
#include "StandardLib/Objects.h"
#include "TestLib/Assert.h"
#include "NamedObjectTestClasses.h"
#include "ObjectTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectAllocatorAddConstructors(void)
{
	gcObjects.AddConstructor<CTestNamedObject>();
	gcObjects.AddConstructor<CTestNamedObjectSmall>();
	gcObjects.AddConstructor<CTestNamedObjectWithEmbedded>();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectAllocatorSimpleAdd(void)
{
	Ptr<CTestNamedObject>	pNamed;
	Ptr<CTestNamedObject>	pTemp;

	MemoryInit();
	FastFunctionsInit();
	TypesInit();
	DataIOInit();
	ObjectsInit();

	TestObjectAllocatorAddConstructors();

	pNamed = gcObjects.AllocateUninitialisedByClassNameAndAddIntoMemory("CTestNamedObject");
	AssertNotNull(pNamed.Object());

	AssertLongLongInt(1LL, pNamed.GetIndex());
	AssertString("", pNamed.GetName());

	pTemp = gcObjects.Get("");
	AssertNull(pTemp.Object());
	pTemp = gcObjects.Get(1LL);
	AssertPointer(pNamed.Object(), pTemp.Object());

	ObjectsFlush();
	ObjectsKill();
	DataIOKill();
	TypesKill();
	FastFunctionsKill();
	MemoryKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectAllocatorNamedAdd(void)
{
	Ptr<CTestNamedObject>	pNamed1;
	Ptr<CTestNamedObject>	pNamed2;
	Ptr<CTestNamedObject>	pTemp;
	SLogConfig				sLogConfig;

	MemoryInit();
	FastFunctionsInit();
	TypesInit();
	DataIOInit();
	ObjectsInit();

	TestObjectAllocatorAddConstructors();
	AssertLongLongInt(0, gcObjects.NumMemoryIndexes());

	pNamed1 = gcObjects.AllocateNamedUninitialisedByClassNameAndAddIntoMemory("CTestNamedObject", "My Object Name");
	AssertNotNull(pNamed1.Object());
	AssertLongLongInt(1, gcObjects.NumMemoryIndexes());
	AssertFalse(pNamed1->IsInitialised());
	pNamed1->Init(98);
	AssertTrue(pNamed1->IsInitialised());

	AssertLongLongInt(1LL, pNamed1.GetIndex());
	AssertString("My Object Name", pNamed1.GetName());
	AssertInt(98, pNamed1->miNum);

	pTemp = gcObjects.Get("My Object Name");
	AssertPointer(pNamed1.Object(), pTemp.Object());

	sLogConfig = gcLogger.SetSilent();
	pNamed2 = gcObjects.AllocateNamedUninitialisedByClassNameAndAddIntoMemory("CTestNamedObject", "My Object Name");
	gcLogger.SetConfig(&sLogConfig);

	AssertNull(pNamed2.Object());
	AssertLongLongInt(1, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(NULL_O_INDEX, pNamed2.GetIndex());

	AssertLongLongInt(1LL, pNamed1.GetIndex());
	AssertString("My Object Name", pNamed1.GetName());

	ObjectsFlush();
	ObjectsKill();
	DataIOKill();
	TypesKill();
	FastFunctionsKill();
	MemoryKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectAllocatorNamedOverwrite(void)
{
	Ptr<CTestNamedObject>	pNamed1;
	Ptr<CTestNamedObject>	pNamed2;
	Ptr<CTestNamedObject>	pTemp;

	MemoryInit();
	FastFunctionsInit();
	TypesInit();
	DataIOInit();
	ObjectsInit();

	TestObjectAllocatorAddConstructors();

	AssertLongLongInt(0, gcObjects.NumMemoryIndexes());

	pNamed1 = gcObjects.AllocateNamedUninitialisedByClassNameAndAddIntoMemory("CTestNamedObject", "My Object Name");
	pNamed1->Init(1);
	AssertLongLongInt(1LL, pNamed1.GetIndex());
	AssertString("My Object Name", pNamed1.GetName());

	AssertLongLongInt(1, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(1, gcObjects.NumMemoryNames());

	pNamed2 = gcObjects.GetNamedObjectInMemoryAndReplaceOrAllocateUnitialised("CTestNamedObject", "My Object Name");
	pNamed2->Init(2);
	AssertNotNull(pNamed2.Object());
	AssertLongLongInt(1LL, pNamed2.GetIndex());
	AssertString("My Object Name", pNamed2.GetName());
	AssertLongLongInt(1, gcObjects.NumMemoryIndexes());

	pNamed1 = gcObjects.Get(1LL);
	AssertNotNull(pNamed1.Object());
	AssertInt(2, pNamed1->miNum);
	AssertInt(2, pNamed2->miNum);
	AssertPointer(pNamed2.Object(), pNamed1.Object());

	AssertLongLongInt(1, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(1, gcObjects.NumMemoryNames());

	pTemp = gcObjects.Get("My Object Name");
	AssertPointer(pNamed2.Object(), pTemp.Object());

	ObjectsFlush();
	ObjectsKill();
	DataIOKill();
	TypesKill();
	FastFunctionsKill();
	MemoryKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectAllocatorOverwriteFromRootCausesChildrenToBeDestroyed(void)
{
	Ptr<CRoot>					pRoot;
	Ptr<CTestNamedObject>		pNamed1;
	Ptr<CTestNamedObject>		pNamed2;
	Ptr<CTestNamedObject>		pNamed3;
	Ptr<CTestNamedObject>		pNamed4;
	Ptr<CTestNamedObject>		pNamed5;
	CPointer					pObject1;
	CPointer					pObject2;
	Ptr<CTestNamedObjectSmall>	pNamedSmall;

	MemoryInit();
	FastFunctionsInit();
	TypesInit();
	DataIOInit();
	ObjectsInit();

	TestObjectAllocatorAddConstructors();

	pRoot = ORoot();
	AssertLongLongInt(2, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(1, gcObjects.NumMemoryNames());

	pNamed1 = ONMalloc<CTestNamedObject>("1", 1);
	pRoot->Add(pNamed1);

	pNamed2 = ONMalloc<CTestNamedObject>("2", 2);
	pRoot->Add(pNamed2);

	pNamed3 = ONMalloc<CTestNamedObject>("3", 3);
	pNamed1->mpNamedTest1 = pNamed3;
	pNamed2->mpNamedTest1 = pNamed3;

	Pass();
	pNamed4 = ONMalloc<CTestNamedObject>("4", 4);
	pNamed1->mpNamedTest2 = pNamed4;

	pNamed5 = ONMalloc<CTestNamedObject>("5", 5);
	pNamed2->mpNamedTest2 = pNamed5;

	pNamed3 = NULL;
	pNamed4 = NULL;
	pNamed5 = NULL;

	AssertLongLongInt(7, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(6, gcObjects.NumMemoryNames());
	
	AssertString("CTestNamedObject", pNamed1.ClassName());
	AssertString("CTestNamedObject", pNamed2.ClassName());
	AssertLongLongInt(3, pNamed1.GetIndex());
	AssertLongLongInt(4, pNamed2.GetIndex());

	pNamedSmall = gcObjects.GetNamedObjectInMemoryAndReplaceOrAllocateUnitialised("CTestNamedObjectSmall", "2");
	pNamedSmall->Init("ABC");

	AssertString("CTestNamedObject", pNamed1.ClassName());
	AssertString("CTestNamedObjectSmall", pNamed2.ClassName());
	AssertLongLongInt(3, pNamed1.GetIndex());
	AssertLongLongInt(4, pNamed2.GetIndex());
	AssertString("CTestNamedObjectSmall", pNamedSmall.ClassName());
	AssertLongLongInt(4, pNamedSmall.GetIndex());

	pObject1 = pRoot->Get("1");
	pObject2 = pRoot->Get("2");

	AssertPointer(pObject1.Dereference(), pNamed1.Dereference());
	AssertPointer(pObject2.Dereference(), pNamedSmall.Dereference());

	AssertLongLongInt(6, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(5, gcObjects.NumMemoryNames());

	pNamed3 = gcObjects.Get("3");
	pNamed4 = gcObjects.Get("4");
	pNamed5 = gcObjects.Get("5");

	AssertNotNull(&pNamed3);
	AssertNotNull(&pNamed4);
	AssertNull(&pNamed5);

	ObjectsFlush();
	ObjectsKill();
	DataIOKill();
	TypesKill();
	FastFunctionsKill();
	MemoryKill();
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectAllocatorAssignmentToNullObject(void)
{
	Ptr<CRoot>				pRoot;
	Ptr<CTestNamedObject>	pNamed1;
	Ptr<CTestNamedObject>	pNamed2;
	CMemoryFile				cMemoryFile;
	CFileBasic				cFileBasic;
	char					szLog[4096];
	char*					szError;
	CLogToMemory			cLogToMemory;
	char*					sz;

	sz = (char*)4096;

	MemoryInit();
	FastFunctionsInit();
	TypesInit();
	DataIOInit();
	ObjectsInit();

	TestObjectAllocatorAddConstructors();

	pRoot = ORoot();

	pNamed1 = ONMalloc<CTestNamedObject>("1", 1);
	pRoot->Add(pNamed1);

	
	cLogToMemory.Start(TRUE);

	//gcLogger.SetBreakOnError(FALSE);
	pNamed2->mpNamedTest1 = pNamed1;
	
	cLogToMemory.Stop(szLog, 4096);

	szError = strstr(szLog, "CPointer::DereferenceArrow(void) Attempted to dereference NULL Pointer.");
	AssertNotNull(szError);


	AssertLongLongInt(3, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(2, gcObjects.NumMemoryNames());

	ObjectsFlush();
	ObjectsKill();
	DataIOKill();
	TypesKill();
	FastFunctionsKill();
	MemoryKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectAllocatorOverwrittensParentMaintainsPointerToOverwritten(void)
{
	Ptr<CRoot>					pRoot;
	Ptr<CTestNamedObject>		pNamed1;
	Ptr<CTestNamedObject>		pNamed2;
	Ptr<CTestNamedObject>		pNamed3;
	Ptr<CTestNamedObject>		pNamed4;
	Ptr<CTestNamedObject>		pNamed5;
	Ptr<CTestNamedObject>		pNamed6;
	CPointer					pObject1;
	CPointer					pObject2;
	Ptr<CTestNamedObject>		pNamed3New;
	Ptr<CTestNamedObject>		pNamed4New;
	void*						pv3;
	void*						pv4;

	MemoryInit();
	FastFunctionsInit();
	TypesInit();
	DataIOInit();
	ObjectsInit();

	TestObjectAllocatorAddConstructors();

	pRoot = ORoot();
	AssertLongLongInt(2, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(1, gcObjects.NumMemoryNames());

	pNamed1 = ONMalloc<CTestNamedObject>("1", 1);
	pRoot->Add(pNamed1);

	pNamed2 = ONMalloc<CTestNamedObject>("2", 2);
	pRoot->Add(pNamed2);

	pNamed3 = ONMalloc<CTestNamedObject>("3", 3);
	pNamed4 = ONMalloc<CTestNamedObject>("4", 4);
	pNamed5 = ONMalloc<CTestNamedObject>("5", 5);
	pNamed6 = ONMalloc<CTestNamedObject>("6", 6);

	pNamed1->mpNamedTest1 = pNamed3;
	pNamed3->mpNamedTest1 = pNamed5;
	pNamed3->mpNamedTest2 = pNamed6;

	pNamed2->mpNamedTest1 = pNamed4;
	pNamed4->mpNamedTest1 = pNamed6;
	pNamed4->mpNamedTest2 = pNamed5;

	AssertInt(3, pNamed1->mpNamedTest1->miNum);
	AssertInt(4, pNamed2->mpNamedTest1->miNum);

	AssertLongLongInt(8, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(7, gcObjects.NumMemoryNames());

	AssertInt(3, pNamed3->GetDistToRoot());
	AssertInt(3, pNamed4->GetDistToRoot());
	AssertLongLongInt(5LL, pNamed3->GetIndex());
	AssertLongLongInt(6LL, pNamed4->GetIndex());

	pv3 = &pNamed3;
	pv4 = &pNamed4;

	pNamed3New = gcObjects.GetNamedObjectInMemoryAndReplaceOrAllocateUnitialised("CTestNamedObject", "3");
	pNamed3New->Init(33);
	pNamed4New = gcObjects.GetNamedObjectInMemoryAndReplaceOrAllocateUnitialised("CTestNamedObject", "4");
	pNamed4New->Init(44);

	AssertLongLongInt(8, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(7, gcObjects.NumMemoryNames());

	AssertLongLongInt(5LL, pNamed3New->GetIndex());
	AssertLongLongInt(6ll, pNamed4New->GetIndex());

	AssertInt(33, pNamed1->mpNamedTest1->miNum);
	AssertInt(44, pNamed2->mpNamedTest1->miNum);

	AssertTrue(&pNamed3 == &pNamed3New);
	AssertTrue(&pNamed4 == &pNamed4New);
	AssertFalse(pv3 == &pNamed3New);
	AssertFalse(pv4 == &pNamed4New);

	AssertInt(3, pNamed3New->GetDistToRoot());
	AssertInt(3, pNamed4New->GetDistToRoot());

	ObjectsFlush();
	ObjectsKill();
	DataIOKill();
	TypesKill();
	FastFunctionsKill();
	MemoryKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectAllocatorOverwrittensParentMaintainsPointerToOverwrittenWithEmbedded(void)
{
	Ptr<CRoot>							pRoot;
	Ptr<CTestNamedObjectWithEmbedded>	pNamed1;
	Ptr<CTestNamedObjectWithEmbedded>	pNamed2;
	Ptr<CTestNamedObjectSmall>			pNamed1a;
	Ptr<CTestNamedObject>				pNamed1b;
	Ptr<CTestNamedObjectSmall>			pNamed2a;
	Ptr<CTestNamedObject>				pNamed2b;
	
	MemoryInit();
	FastFunctionsInit();
	TypesInit();
	DataIOInit();
	ObjectsInit();

	TestObjectAllocatorAddConstructors();

	pRoot = ORoot();
	AssertLongLongInt(2, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(1, gcObjects.NumMemoryNames());

	pNamed1a = ONMalloc<CTestNamedObjectSmall>("TestNamedObjectSmall 1A", (char*)"ABC");
	pNamed1b = ONMalloc<CTestNamedObject>("TestNamedObject 1B", 4);
	pNamed2a = ONMalloc<CTestNamedObjectSmall>("TestNamedObjectSmall 2A", (char*)"XYZ");
	pNamed2b = ONMalloc<CTestNamedObject>("TestNamedObject 2B", 4);

	pNamed1 = ONMalloc<CTestNamedObjectWithEmbedded>("Agrarian", 12, 13, 14, 15, pNamed1b, pNamed1a);
	pRoot->Add(pNamed1);

	pNamed2 = ONMalloc<CTestNamedObjectWithEmbedded>("Hydroponics", 2012, 2013, 2014, 2015, pNamed2b, pNamed2a);
	pRoot->Add(pNamed2);

	pNamed2a = NULL;
	pNamed2b = NULL;
	
	AssertLongLongInt(8, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(7, gcObjects.NumMemoryNames());

	AssertInt(2, pNamed1->GetDistToRoot());
	AssertInt(3, pNamed1->mpObject->GetDistToRoot());
	AssertInt(3, pNamed1->mpSmall->GetDistToRoot());
	AssertInt(3, pNamed2->mpObject->GetDistToRoot());
	AssertInt(3, pNamed2->mpSmall->GetDistToRoot());
	AssertInt(2, pNamed1->mNamedTest1.GetDistToRoot());
	AssertInt(2, pNamed1->mNamedTest2.GetDistToRoot());
	AssertInt(2, pNamed2->mNamedTest1.GetDistToRoot());
	AssertInt(2, pNamed2->mNamedTest2.GetDistToRoot());


	pNamed1 = gcObjects.GetNamedObjectInMemoryAndReplaceOrAllocateUnitialised("CTestNamedObjectWithEmbedded", "Agrarian");
	pNamed1->Init(1012, 1013, 1014, 1015, Null(), Null());
	pNamed2 = gcObjects.GetNamedObjectInMemoryAndReplaceOrAllocateUnitialised("CTestNamedObjectWithEmbedded", "Hydroponics");
	pNamed2->Init(2012, 2013, 2014, 2015, Null(), Null());

	AssertLongLongInt(6, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(5, gcObjects.NumMemoryNames());

	AssertInt(2, pNamed1->GetDistToRoot());
	AssertNull(&pNamed1->mpObject);
	AssertNull(&pNamed1->mpSmall);
	AssertNull(&pNamed2->mpObject);
	AssertNull(&pNamed2->mpSmall);
	AssertInt(2, pNamed1->mNamedTest1.GetDistToRoot());
	AssertInt(2, pNamed1->mNamedTest2.GetDistToRoot());
	AssertInt(2, pNamed2->mNamedTest1.GetDistToRoot());
	AssertInt(2, pNamed2->mNamedTest2.GetDistToRoot());

	AssertInt(-1, pNamed1a->GetDistToRoot());
	AssertInt(-1, pNamed1b->GetDistToRoot());

	pNamed1 = NULL;
	pNamed2 = NULL;
	pNamed1a = NULL;
	pNamed2a = NULL;
	pNamed1b = NULL;
	pNamed2b = NULL;

	AssertLongLongInt(4, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(3, gcObjects.NumMemoryNames());

	pNamed1 = gcObjects.Get("Agrarian");
	pNamed2 = gcObjects.Get("Hydroponics");
	AssertNotNull(&pNamed1);
	AssertNotNull(&pNamed2);

	ObjectsFlush();
	ObjectsKill();
	DataIOKill();
	TypesKill();
	FastFunctionsKill();
	MemoryKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectAllocatorOverwrittensFlushedObjects(void)
{
	Ptr<CRoot>							pRoot;
	Ptr<CTestTriPointerObject>			pObjet1;
	Ptr<CTestNamedObject>				pNamed2;
	Ptr<CTestObject>					pObjet3;
	Ptr<CTestNamedObjectSmall>			pNamed4;
	Ptr<CTestNamedObjectWithEmbedded>	pNamed5;
	Ptr<CTestObject>					pObjet6;
	Ptr<CTestNamedObject>				pNamed7;
	Ptr<CTestNamedObject>				pNamed8;
	CCodabase*							pcDatabase;
	CSequence*							pcSequence;
	CFileUtil							cFileUtil;
	char								szDirectory[] = "Output" _FS_ "ObjectAllocator" _FS_ "Database1";

	cFileUtil.RemoveDir(szDirectory);
	MemoryInit();
	FastFunctionsInit();
	TypesInit();
	DataIOInit();


	pcSequence = CSequenceFactory::Create(szDirectory);
	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase, pcSequence);

	TestObjectAllocatorAddConstructors();

	pRoot = ORoot();
	AssertLongLongInt(2, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(1, gcObjects.NumMemoryNames());

	pObjet1 = OMalloc<CTestTriPointerObject>();
	pNamed2 = ONMalloc<CTestNamedObject>("Virgil Mallin", 12);
	pObjet3 = OMalloc<CTestObject>();	pObjet3->mi = 34;
	pNamed4 = ONMalloc<CTestNamedObjectSmall>("Henry Lindsey", "Sol");
	pNamed5 = ONMalloc<CTestNamedObjectWithEmbedded>("Wilfrid Stanley", 44, 55, 1, 2, Null(), Null());
	pObjet6 = OMalloc<CTestObject>();	pObjet3->mi = 56;
	pNamed7 = ONMalloc<CTestNamedObject>("Matt Hudson", 78);
	pNamed8 = ONMalloc<CTestNamedObject>("Kiva Charity", 90);
	
	AssertInt(-1, pObjet1.GetDistToRoot());
	AssertInt(-1, pNamed2.GetDistToRoot());
	AssertInt(-1, pObjet3.GetDistToRoot());
	AssertInt(-1, pNamed4.GetDistToRoot());
	AssertInt(-1, pNamed5.GetDistToRoot());
	AssertInt(-1, pObjet6.GetDistToRoot());
	AssertInt(-1, pNamed7.GetDistToRoot());

	pRoot->Add(pObjet1);
	pObjet1->mpObject1 = pNamed5;
	pObjet1->mpObject2 = pObjet3;
	pObjet1->mpObject3 = pNamed4;

	pNamed5->mNamedTest1.mpNamedTest1 = pNamed2;
	pNamed5->mNamedTest1.mpNamedTest2 = pNamed7;
	pNamed5->mpObject = pObjet6;
	
	pObjet6->mpObject = pNamed4;

//	                                      
//	                                      pNamed4(3)
//	                                      /   |     
//          pNamed2(4)   pNamed7(4)      /    |
//	           |            |           /     |   
//	           |            |     pObjet6(4)  |
//             |            |     /           |
//	           |            |    /            |       
//             |            |   /             |        
//	           |            |  /              |      
//          mNamedTest1  mNamedTest2          |
//                    .  .   /               /
//                   pNamed5(3)  pObjet3(3) /
// 	                       \       |       /  
// 	                        \      |      /  
//                           \     |     /  
// 	                          \    |    /  
//                             \   |   /   
// 	                            \  |  /    
//                             pObjet1(2)
//                                 |
//                                 |
//                                ...
//                              Root(0)                   pNamed8(-1)  


	AssertInt(0, pRoot.GetDistToRoot());
	AssertInt(2, pObjet1.GetDistToRoot());
	AssertInt(4, pNamed2.GetDistToRoot());
	AssertInt(3, pObjet3.GetDistToRoot());
	AssertInt(3, pNamed4.GetDistToRoot());
	AssertInt(3, pNamed5.GetDistToRoot());
	AssertInt(4, pObjet6.GetDistToRoot());
	AssertInt(4, pNamed7.GetDistToRoot());
	AssertInt(-1, pNamed8.GetDistToRoot());

	AssertLongLongInt(10, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(6, gcObjects.NumMemoryNames());

	ObjectsFlush();
	pcDatabase->Close();
	SafeKill(pcDatabase);
	SafeKill(pcSequence);
	ObjectsKill();

	AssertNull(&pRoot);
	AssertNull(&pObjet1);
	AssertNull(&pNamed2);
	AssertNull(&pObjet3);
	AssertNull(&pNamed4);
	AssertNull(&pNamed5);
	AssertNull(&pObjet6);
	AssertNull(&pNamed7);
	AssertNull(&pNamed8);

	pcSequence = CSequenceFactory::Create(szDirectory);
	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase, pcSequence);

	pRoot = ORoot();
	AssertLongLongInt(2, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(1, gcObjects.NumMemoryNames());
	AssertLongLongInt(9, gcObjects.NumDatabaseIndexes());
	AssertLongLongInt(5, gcObjects.NumDatabaseNames());
	AssertLongLongInt(2, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(1, gcObjects.NumMemoryNames());

	pNamed2 = gcObjects.Get("Virgil Mallin");
	AssertInt(4, pNamed2.GetDistToRoot());
	pNamed4 = gcObjects.Get("Henry Lindsey");
	AssertInt(3, pNamed4.GetDistToRoot());
	pNamed5 = gcObjects.Get("Wilfrid Stanley");
	AssertInt(3, pNamed5.GetDistToRoot());
	pNamed7 = gcObjects.Get("Matt Hudson");
	AssertInt(4, pNamed7.GetDistToRoot());
	pNamed8 = gcObjects.Get("Matt Hudson");
	AssertInt(-1, pNamed8.GetDistToRoot());

	ObjectsFlush();
	pcDatabase->Close();
	SafeKill(pcDatabase);
	SafeKill(pcSequence);
	ObjectsKill();


	pcSequence = CSequenceFactory::Create(szDirectory);
	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase, pcSequence);

	pRoot = ORoot();
	AssertLongLongInt(2, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(1, gcObjects.NumMemoryNames());
	AssertLongLongInt(2, gcObjects.NumDatabaseIndexes());
	AssertLongLongInt(1, gcObjects.NumDatabaseNames());

	ObjectsFlush();
	pcDatabase->Close();
	SafeKill(pcDatabase);
	SafeKill(pcSequence);
	ObjectsKill();


	DataIOKill();
	TypesKill();
	FastFunctionsKill();
	MemoryKill();
	cFileUtil.RemoveDir(szDirectory);
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectAllocator(void)
{
	BeginTests();

	TestObjectAllocatorSimpleAdd();
	TestObjectAllocatorNamedAdd();
	TestObjectAllocatorNamedOverwrite();
	TestObjectAllocatorOverwriteFromRootCausesChildrenToBeDestroyed();
	TestObjectAllocatorAssignmentToNullObject();
	TestObjectAllocatorOverwrittensParentMaintainsPointerToOverwritten();
	TestObjectAllocatorOverwrittensParentMaintainsPointerToOverwrittenWithEmbedded();
	TestObjectAllocatorOverwrittensFlushedObjects();

	//Test dependent named objects overwrite existing named objects.  i.e:  Load "Name 1" -> x -> "Name 2" overwrites "Name 2" that exists in the database.

	TestStatistics();
}

