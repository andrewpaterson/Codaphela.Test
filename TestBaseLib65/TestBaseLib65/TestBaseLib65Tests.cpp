#include "TestLib/Assert.h"
#include "TestProject65.h"


//////////////////////////////////////////////////////////////////////////
//
// TestBaseLib's tests, with BaseLib and TestLib, each run on the 65C64 (see TestProject65.cpp).
//
//////////////////////////////////////////////////////////////////////////


static const char* gaszTestBaseLib65Libraries[] = { "TestLib", "BaseLib", NULL };


//The tests that are not run.
static const char* gaszTestBaseLib65Excluded[] =
{
	//CNativeThread and CConditionVariable have no 65C64 versions (it runs one thread).
	"TestCodabase",
	"TestWriteTransaction",
	"TestReadTransaction",
	"TestTransactionConcurrency",

	//Hundreds of millions to billions of instructions natively, far too many to simulate here.
	"TestNumber",
	"TestFloatPrinter",
	"TestNamedIndexedData",
	"TestIndexTreeAccess",
	"TestFat32",

	//Expects a bigger block, malloc'ed after free, at another address (as MSVC and glibc give it).  Libc65's malloc
	//joins the block just freed to the free memory after it, so the bigger block starts in the same place.
	"TestTemporaryMemory",

	NULL
};


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestBaseLib65Tests(void)
{
	STestProject65	sProject;

	BeginTests();

	sProject.szTestProject = "TestBaseLib";
	sProject.aszLibraries = gaszTestBaseLib65Libraries;
	sProject.aszExcluded = gaszTestBaseLib65Excluded;
	sProject.uiMinPrograms = 101;
	sProject.iMinTestsRun = 30001;
	TestProject65RunTests(&sProject);

	TestStatistics();
}
