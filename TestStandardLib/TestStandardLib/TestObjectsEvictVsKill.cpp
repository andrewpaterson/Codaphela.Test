#include "BaseLib/GlobalMemory.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/TypeNames.h"
#include "BaseLib/Codabase.h"
#include "BaseLib/CodabaseFactory.h"
#include "BaseLib/SequenceFactory.h"
#include "BaseLib/ValueIndexedDataConfig.h"
#include "BaseLib/ValueNamedIndexesConfig.h"
#include "BaseLib/NamedIndexedHeader.h"
#include "StandardLib/Objects.h"
#include "TestLib/Assert.h"
#include "ObjectTestClasses.h"
#include "ChunkFileObjectWriterTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectsEvictVsKillUserEvictAfterSave(EIndexWriteThrough eWriteThrough)
{
	CFileUtil					cFileUtil;
	char						szDirectory[] = "Output" _FS_ "ObjectsUserFree";
	CCodabase*					pcDatabase;
	CSequence*					pcSequence;
	Ptr<CTestObject>			pTest1a;
	Ptr<CTestObject>			pTest1b;
	STestObjectFreedNotifier	sFreeNotifier1a;
	STestObjectFreedNotifier	sFreeNotifier1b;
	Ptr<CRoot>					pRoot;

	cFileUtil.RemoveDir(szDirectory);
	AssertTrue(cFileUtil.TouchDir(szDirectory));

	pcSequence = CSequenceFactory::Create(szDirectory);
	pcDatabase = CCodabaseFactory::Create(szDirectory, eWriteThrough);
	pcDatabase->Open();
	ObjectsInit(pcDatabase, pcSequence);

	pTest1a = OMalloc<CTestObject>(&sFreeNotifier1a);
	pRoot = ORoot();
	pRoot->Add(pTest1a);
	pTest1b = OMalloc<CTestObject>(&sFreeNotifier1b);
	pTest1a->mpTest = pTest1b;
	AssertLong(0, pcDatabase->NumIndices());
	AssertLong(4, gcObjects.NumMemoryIndexes());

	AssertInt(0x07070707, pTest1a->mi);

	pTest1a->Flush();

	AssertLong(1, pcDatabase->NumIndices());
	AssertLong(4, gcObjects.NumMemoryIndexes());

	ObjectsFlush();
	pcDatabase->Close();
	SafeKill(pcDatabase);
	SafeKill(pcSequence);
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
	FastFunctionsInit();
	TypesInit();
	DataIOInit();

	TestObjectsEvictVsKillUserEvictAfterSave(IWT_No);
	TestObjectsEvictVsKillUserEvictAfterSave(IWT_Yes);

	DataIOKill();
	TypesKill();
	FastFunctionsKill();
	MemoryKill();
	TestStatistics();
}

