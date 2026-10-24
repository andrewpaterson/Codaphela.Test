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
	//More than the 4G instructions each program gets here.  They pass when given longer: TestCompressionZLib in 5.1G
	//65C64 instructions, TestMapObject in 9.7G, TestSetObject in 12.7G and TestArrayObject in 20.0G.
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
	sProject.uiMinPrograms = 57;
	sProject.iMinTestsRun = 4877;
	TestProject65RunTests(&sProject);

	TestStatistics();
}
