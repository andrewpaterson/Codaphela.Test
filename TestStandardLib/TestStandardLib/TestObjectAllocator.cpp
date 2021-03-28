#include "BaseLib/GlobalMemory.h"
#include "BaseLib/MemoryFile.h"
#include "BaseLib/LogToMemory.h"
#include "StandardLib/Objects.h"
#include "TestLib/Assert.h"
#include "NamedObjectTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectAllocatorAddConstructors(void)
{
	gcObjects.AddConstructor<CRoot>();
	gcObjects.AddConstructor<CTestNamedObject>();
	gcObjects.AddConstructor<CTestNamedObjectSmall>();
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
	ObjectsInit();

	TestObjectAllocatorAddConstructors();

	pNamed = gcObjects.AllocateNew("CTestNamedObject");
	AssertNotNull(pNamed.Object());

	AssertLongLongInt(1LL, pNamed.GetIndex());
	AssertString("", pNamed.GetName());

	pTemp = gcObjects.Get("");
	AssertNull(pTemp.Object());
	pTemp = gcObjects.Get(1LL);
	AssertPointer(pNamed.Object(), pTemp.Object());

	ObjectsFlush();
	ObjectsKill();
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
	ObjectsInit();

	TestObjectAllocatorAddConstructors();
	AssertLongLongInt(0, gcObjects.NumMemoryIndexes());

	pNamed1 = gcObjects.AllocateNewNamed("CTestNamedObject", "My Object Name");
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
	pNamed2 = gcObjects.AllocateNewNamed("CTestNamedObject", "My Object Name");
	gcLogger.SetConfig(&sLogConfig);

	AssertNull(pNamed2.Object());
	AssertLongLongInt(1, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(NULL_O_INDEX, pNamed2.GetIndex());

	AssertLongLongInt(1LL, pNamed1.GetIndex());
	AssertString("My Object Name", pNamed1.GetName());

	ObjectsFlush();
	ObjectsKill();
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
	ObjectsInit();

	TestObjectAllocatorAddConstructors();

	AssertLongLongInt(0, gcObjects.NumMemoryIndexes());

	pNamed1 = gcObjects.AllocateNewNamed("CTestNamedObject", "My Object Name");
	pNamed1->Init(1);
	AssertLongLongInt(1LL, pNamed1.GetIndex());
	AssertString("My Object Name", pNamed1.GetName());

	AssertLongLongInt(1, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(1, gcObjects.NumMemoryNames());

	pNamed2 = gcObjects.AllocateExistingNamed("CTestNamedObject", "My Object Name");
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

	pNamedSmall = gcObjects.AllocateExistingNamed("CTestNamedObjectSmall", "2");
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
	MemoryKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectAllocatorOverwritensParentMaintainsPointerToOverwritten(void)
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

	pv3 = &pNamed3;
	pv4 = &pNamed4;

	pNamed3New = gcObjects.AllocateExistingNamed("CTestNamedObject", "3");
	pNamed3New->Init(33);
	pNamed4New = gcObjects.AllocateExistingNamed("CTestNamedObject", "4");
	pNamed4New->Init(44);

	AssertLongLongInt(8, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(7, gcObjects.NumMemoryNames());

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
	MemoryKill();
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
	TestObjectAllocatorOverwritensParentMaintainsPointerToOverwritten();
	//Test on disk; pointers to overwritten are preserved when read

	TestStatistics();
}

