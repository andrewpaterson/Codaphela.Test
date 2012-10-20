#include "BaseLib/FastFunctions.h"
#include "BaseLib/FileUtil.h"
#include "CoreLib/TypeConverter.h"
#include "CoreLib/LogFile.h"
#include "TestLib/Assert.h"




void TestLogFile(void)
{
	BeginTests();

	FastFunctionsInit();
	TypeConverterInit();

	FastFunctionsKill();
	TypeConverterKill();

	TestStatistics();

}