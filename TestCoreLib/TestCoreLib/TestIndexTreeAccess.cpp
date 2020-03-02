#include "BaseLib/TypeConverter.h"
#include "BaseLib/GlobalMemory.h"
#include "CoreLib/LogFile.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeAccess(void)
{
	FastFunctionsInit();
	TypeConverterInit();
	MemoryInit();
	DataMemoryInit();
	BeginTests();

	TestStatistics();
	DataMemoryKill();
	MemoryKill();
	FastFunctionsKill();
	TypeConverterKill();
}

