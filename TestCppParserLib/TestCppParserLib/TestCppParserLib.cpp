#include "TestLib/Assert.h"


void TestPreprocessor(void);
void TestASCIITree(void);
void TestProject(void);


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int main(void)
{
	InitTotalStatistics();

	TestASCIITree();
	TestPreprocessor();
	TestProject();

	return TestTotalStatistics();
}

