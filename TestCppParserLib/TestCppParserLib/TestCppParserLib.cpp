#include "BaseLib/LeakDetector.h"
#include "TestLib/Assert.h"


void TestPreprocessor(void);
void TestProject(void);
void TestCppTokeniser(void);
void TestCppParser(void);
void TestCppHighlighter(void);


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
	TestCppTokeniser();
	TestCppParser();
	TestCppHighlighter();

	iTotalTestsFailed = TestTotalStatistics();

	LeakDetection();
	return iTotalTestsFailed;
}

