#include "BaseLib/TypeConverter.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeAccess(void)
{
	FastFunctionsInit();
	TypeConverterInit();
	BeginTests();

	TestStatistics();
	FastFunctionsKill();
	TypeConverterKill();
}

