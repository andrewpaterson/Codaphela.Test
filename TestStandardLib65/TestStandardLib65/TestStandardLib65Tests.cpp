#include "TestLib/Assert.h"
#include "../../TestBaseLib65/TestBaseLib65/TestProject65.h"


//////////////////////////////////////////////////////////////////////////
//
// TestStandardLib's tests, with StandardLib, BaseLib and TestLib, each run on the 65C64 (see TestProject65.cpp).
//
//////////////////////////////////////////////////////////////////////////


static const char* gaszTestStandardLib65Libraries[] = { "TestLib", "StandardLib", "BaseLib", NULL };


//The tests that are not run.
static const char* gaszTestStandardLib65Excluded[] =
{
	//Billions of instructions natively, more than the 4G instructions each program gets here (they pass when given
	//longer: TestSetUnknown in 5.0G 65C64 instructions, TestCompressionZLib in 8.8G).
	"TestSetUnknown",
	"TestCompressionZLib",
	"TestArrayObject",
	"TestSetObject",
	"TestMapObject",

	NULL
};


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestStandardLib65Tests(void)
{
	STestProject65	sProject;

	BeginTests();

	sProject.szTestProject = "TestStandardLib";
	sProject.aszLibraries = gaszTestStandardLib65Libraries;
	sProject.aszExcluded = gaszTestStandardLib65Excluded;
	sProject.uiMinPrograms = 56;
	sProject.iMinTestsRun = 4758;
	TestProject65RunTests(&sProject);

	TestStatistics();
}
