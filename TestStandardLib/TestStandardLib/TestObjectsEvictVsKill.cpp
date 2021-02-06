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
void TestObjectsEvictVsKillUserFree(EIndexWriteThrough eWriteThrough)
{
	CFileUtil								cFileUtil;
	char									szDirectory[] = "Output" _FS_ "ObjectsUserFree";
	CCodabase*								pcDatabase;

	cFileUtil.RemoveDir(szDirectory);
	AssertTrue(cFileUtil.TouchDir(szDirectory));

	pcDatabase = CCodabaseFactory::Create(szDirectory, eWriteThrough);
	pcDatabase->Open();
	ObjectsInit(pcDatabase);

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

	TestObjectsEvictVsKillUserFree(IWT_No);
	TestObjectsEvictVsKillUserFree(IWT_Yes);

	MemoryKill();
	TestStatistics();
}

