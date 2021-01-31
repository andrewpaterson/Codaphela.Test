#include "BaseLib/GlobalMemory.h"
#include "CoreLib/Codabase.h"
#include "CoreLib/CodabaseFactory.h"
#include "StandardLib/Objects.h"
#include "TestLib/Assert.h"
#include "ObjectTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectsCompilation(void)
{
	if (FALSE)  //This is intentional.  This code must only be compiled (testing template compilation) not run.
	{
		CObjects				cObjects;
		Ptr<CTestObject>	cTestPtr;

		cTestPtr = cObjects.Add<CTestObject>();
		cTestPtr = cObjects.Get<CTestObject>("Invalid Name");
		cTestPtr = cObjects.Get<CTestObject>(INVALID_O_INDEX);
	}
	AssertTrue(TRUE);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectFreeing(void)
{
	Ptr<CTestObject>			pTest1;
	Ptr<CTestObject>			pTest2;
	STestObjectFreedNotifier	sFreedNotifier1;
	STestObjectFreedNotifier	sFreedNotifier2;
	CCodabase*					pcDatabase;
	char						szDirectory[] = "Output" _FS_ "TestObjectFreeing";
	CFileUtil					cFileUtil;
			
	cFileUtil.RemoveDir(szDirectory);

	pcDatabase = CCodabaseFactory::Create(szDirectory, IWT_No);
	pcDatabase->Open();
	ObjectsInit(pcDatabase);

	pTest1 = OMalloc(CTestObject);
	pTest2 = OMalloc(CTestObject);

	AssertNotNull(&pTest1);
	AssertNotNull(&pTest2);

	pTest1->Init(&sFreedNotifier1);
	pTest2->Init(&sFreedNotifier2);
	AssertLongLongInt(2, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(0, pcDatabase->NumIndicesCached());

	pTest1->Kill();
	AssertLongLongInt(1, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(0, pcDatabase->NumIndicesCached());
	AssertTrue(sFreedNotifier1.bFreed);

	pTest2->Kill();
	AssertLongLongInt(0, gcObjects.NumMemoryIndexes());
	AssertLongLongInt(0, pcDatabase->NumIndicesCached());
	AssertTrue(sFreedNotifier2.bFreed);

	pcDatabase->Close();
	SafeKill(pcDatabase);
	ObjectsKill();

	cFileUtil.RemoveDir(szDirectory);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectsSimple(void)
{
	BeginTests();
	MemoryInit();

	TestObjectsCompilation();
	TestObjectFreeing();

	MemoryKill();
	TestStatistics();
}

