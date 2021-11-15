#include "TestLib/Assert.h"


void TestPreprocessor(void);
void TestASCIITree(void);
void TestProject(void);


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int __cdecl main(void)
{
	InitTotalStatistics();

	TestASCIITree();
	TestPreprocessor();
	TestProject();

	return TestTotalStatistics();
}

