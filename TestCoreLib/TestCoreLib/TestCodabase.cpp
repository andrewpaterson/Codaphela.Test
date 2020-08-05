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
void TestCodabaseFactory(void)
{
	CCodabase*	pcDatabase;

	pcDatabase = CCodabaseFactory::Create("Output" _FS_ "CodabaseFactory", IWT_No);

	pcDatabase->Kill();
	Pass();
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

	TestCodabaseFactory();

	TestStatistics();
	WordsKill();
	DataMemoryKill();
	MemoryKill();
	FastFunctionsKill();
	TypeConverterKill();
}

