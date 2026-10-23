#include "BaseLib/LeakDetector.h"
#include "TestLib/Assert.h"


void TestCppErrors(void);
void TestPreprocessor(void);
void TestProject(void);
void TestCppTokeniser(void);
void TestCppParser(void);
void TestCppHighlighter(void);
void TestCPP65Generator(void);


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int __cdecl main(void)
{
	int	iTotalTestsFailed;

	BreakOnAllocation(0);
	InitTotalStatistics();

	TestCppErrors();
	TestPreprocessor();
	TestProject();
	TestCppTokeniser();
	TestCppParser();
	TestCppHighlighter();
	TestCPP65Generator();

	iTotalTestsFailed = TestTotalStatistics();

	LeakDetection();
	return iTotalTestsFailed;
}

