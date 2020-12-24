#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMainProcessDirector(int argc, char* argv[])
{
	BeginTests();

	AssertInt(2, argc);
	AssertString("param1", argv[0]);
	AssertString("--param:2", argv[1]);

	TestStatistics();
}

