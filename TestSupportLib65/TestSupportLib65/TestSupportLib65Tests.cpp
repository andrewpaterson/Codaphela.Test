#include "TestLib/Assert.h"
#include "../../TestBaseLib65/TestBaseLib65/TestProject65.h"


//////////////////////////////////////////////////////////////////////////
//
// TestSupportLib's tests, with SupportLib, StandardLib, BaseLib and TestLib, each run on the 65C64 (see
// TestProject65.cpp).
//
//////////////////////////////////////////////////////////////////////////


static const char* gaszTestSupportLib65Libraries[] = { "TestLib", "SupportLib", "StandardLib", "BaseLib", NULL };


//The tests that are not run.
static const char* gaszTestSupportLib65Excluded[] =
{
	//More than the 4G instructions each program gets here.  They pass when given longer: TestTrueTypeFont in 5.1G
	//65C64 instructions, TestModPlayer in 9.8G, TestFont in 16.6G, TestSoundResampler in 16.8G, TestImageResampler
	//in 24.0G, TestImageOpacity in 24.6G and TestNormalGeneration in 35.2G.
	"TestTrueTypeFont",
	"TestModPlayer",
	"TestFont",
	"TestSoundResampler",
	"TestImageResampler",
	"TestImageOpacity",
	"TestNormalGeneration",

	//Its 18MB combined image (it raises the debug allocation limit to 32MB) does not fit in the 48MB heap: SavePNG
	//cannot allocate memory to write it, after 51.6G instructions.
	"TestImageCombiner",

	NULL
};


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSupportLib65Tests(void)
{
	STestProject65	sProject;

	BeginTests();

	sProject.szTestProject = "TestSupportLib";
	sProject.aszLibraries = gaszTestSupportLib65Libraries;
	sProject.aszExcluded = gaszTestSupportLib65Excluded;
	sProject.uiMinPrograms = 46;
	sProject.iMinTestsRun = 20649;
	TestProject65RunTests(&sProject);

	TestStatistics();
}
