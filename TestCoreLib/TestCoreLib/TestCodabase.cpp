#include "BaseLib/TypeConverter.h"
#include "BaseLib/DebugOutput.h"
#include "BaseLib/GlobalMemory.h"
#include "BaseLib/CharsHelper.h"
#include "CoreLib/LogFile.h"
#include "CoreLib/CodabaseFactory.h"
#include "CoreLib/Codabase.h"
#include "TestLib/Words.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCodabaseFactoryCreate(void)
{
	CCodabase*	pcDatabase;
	CFileUtil	cFileUtil;

	cFileUtil.RemoveDir("Output" _FS_ "CodabaseFactory1");

	pcDatabase = CCodabaseFactory::Create("Output" _FS_ "CodabaseFactory1", IWT_No);

	AssertTrue(cFileUtil.Exists("Output" _FS_ "CodabaseFactory1" _FS_ "Primary" _FS_ "Index"));
	AssertTrue(cFileUtil.Exists("Output" _FS_ "CodabaseFactory1" _FS_ "Primary" _FS_ "Names"));
	AssertTrue(pcDatabase->ValidateConfigInitialised());
	Pass();

	pcDatabase->Kill();
	AssertTrue(pcDatabase->ValidateConfigKilled()); 
	Pass();
	
	SafeFree(pcDatabase);
	Pass();

	AssertTrue(cFileUtil.RemoveDir("Output" _FS_ "CodabaseFactory1"));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCodabase(void)
{
	FastFunctionsInit();
	TypeConverterInit();
	MemoryInit();
	DataMemoryInit();
	WordsInit();
	BeginTests();

	TestCodabaseFactoryCreate();

	TestStatistics();
	WordsKill();
	DataMemoryKill();
	MemoryKill();
	FastFunctionsKill();
	TypeConverterKill();
}

