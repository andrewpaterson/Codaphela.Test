#include "BaseLib/LeakDetector.h"
#include "TestLib/Assert.h"


void TestCppErrors(void);
void TestPreprocessor(void);
void TestProject(void);
void TestCppTokeniser(void);
void TestCppParser(void);
void TestCppHighlighter(void);
void TestIR(void);
void TestIR65Backend(void);
void TestCPP65IR(void);
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
	TestIR();
	TestIR65Backend();
	TestCPP65Generator();
	TestCPP65IR();

	iTotalTestsFailed = TestTotalStatistics();

	LeakDetection();
	return iTotalTestsFailed;
}

