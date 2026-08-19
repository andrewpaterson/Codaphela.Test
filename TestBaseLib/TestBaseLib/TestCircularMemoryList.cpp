#include "BaseLib/CircularMemoryList.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCircularMemoryList(void)
{
	BeginTests();
	FastFunctionsInit();

	//TestCircularMemoryListPush();

	FastFunctionsKill();
	TestStatistics();
}

