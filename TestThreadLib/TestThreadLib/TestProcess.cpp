#include "BaseLib/GlobalMemory.h"
#include "ThreadLib/ProcessFork.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestProcess(void)
{
	BeginTests();
	MemoryInit();
	FastFunctionsInit();

	ForkProcess("--client", FALSE);

	FastFunctionsKill();
	MemoryKill();
	TestStatistics();
}

