#include "BaseLib/GlobalMemory.h"
#include "CoreLib/Codabase.h"
#include "CoreLib/CodabaseFactory.h"
#include "CoreLib/ValueIndexedDataConfig.h"
#include "CoreLib/ValueNamedIndexesConfig.h"
#include "CoreLib/NamedIndexedHeader.h"
#include "StandardLib/Objects.h"
#include "TestLib/Assert.h"
#include "ObjectTestClasses.h"
#include "ObjectWriterChunkedTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectsEvictVsKillUserEvictAfterSave(EIndexWriteThrough eWriteThrough)
{
	CFileUtil					cFileUtil;
	char						szDirectory[] = "Output" _FS_ "ObjectsUserFree";
	CCodabase*					pcDatabase;
	Ptr<CTestObject>			pTest1a;
	Ptr<CTestObject>			pTest1b;
	STestObjectFreedNotifier	sFreeNotifier1a;
	STestObjectFreedNotifier	sFreeNotifier1b;
	Ptr<CRoot>					pRoot;

	cFileUtil.RemoveDir(szDirectory);
	AssertTrue(cFileUtil.TouchDir(szDirectory));

	pcDatabase = CCodabaseFactory::Create(szDirectory, eWriteThrough);
	pcDatabase->Open();
	ObjectsInit(pcDatabase);

	pTest1a = OMalloc<CTestObject>(&sFreeNotifier1a);
	pRoot = ORoot();
	pRoot->Add(pTest1a);
	pTest1b = OMalloc<CTestObject>(&sFreeNotifier1b);
	pTest1a->mpTest = pTest1b;
	AssertLongLongInt(0, pcDatabase->NumIndices());
	AssertLongLongInt(4, gcObjects.NumMemoryIndexes());

	AssertInt(0x07070707, pTest1a->mi);

	pTest1a->Flush();

	AssertLongLongInt(1, pcDatabase->NumIndices());
	AssertLongLongInt(4, gcObjects.NumMemoryIndexes());

	ObjectsFlush();

	pcDatabase->Close();
	SafeKill(pcDatabase);
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectsEvictVsKill(void)
{
	BeginTests();
	MemoryInit();

	TestObjectsEvictVsKillUserEvictAfterSave(IWT_No);
	TestObjectsEvictVsKillUserEvictAfterSave(IWT_Yes);

	MemoryKill();
	TestStatistics();
}
