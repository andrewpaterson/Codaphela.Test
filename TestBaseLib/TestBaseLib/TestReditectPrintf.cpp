#include "BaseLib/RedirectPrintf.h"
#include "TestLib/Assert.h"



CChars	gszTestPrintFunction;


void TestPrintFunction(const char* szString)
{
	gszTestPrintFunction.Append(szString);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestReditectPrintf(void)
{
	BeginTests();

	gszTestPrintFunction.Init();
	SetPrintFunction(TestPrintFunction);
	eprintf("%s %s\n", "Hello", "World");
	AssertString("Hello World\n", gszTestPrintFunction.Text());
	gszTestPrintFunction.Kill();

	TestStatistics();
}

