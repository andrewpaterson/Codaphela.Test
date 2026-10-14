#include "BaseLib/LeakDetector.h"
#include "TestLib/Assert.h"


void TestPreprocessor(void);
void TestProject(void);


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int __cdecl main(void)
{
	int	iTotalTestsFailed;

	BreakOnAllocation(0);
	InitTotalStatistics();

	TestPreprocessor();
	TestProject();

	iTotalTestsFailed = TestTotalStatistics();

	LeakDetection();
	return iTotalTestsFailed;
}

