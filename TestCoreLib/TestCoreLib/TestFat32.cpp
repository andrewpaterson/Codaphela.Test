#include "BaseLib/FastFunctions.h"
#include "BaseLib/TypeConverter.h"
#include "CoreLib/Fat32.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFat32(void)
{
	BeginTests();

	TypeConverterInit();

	tf_init();

	TypeConverterKill();

	TestStatistics();
}

