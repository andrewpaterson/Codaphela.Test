#include "TestLib/Assert.h"


void TestPreprocessor(void);
void TestProject(void);


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int __cdecl main(void)
{
	InitTotalStatistics();

	TestPreprocessor();
	TestProject();

	return TestTotalStatistics();
}

