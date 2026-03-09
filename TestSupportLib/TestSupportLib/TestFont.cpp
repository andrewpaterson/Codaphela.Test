#include "BaseLib/FastFunctions.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "StandardLib/Objects.h"
#include "SupportLib/Font.h"
#include "SupportLib/FontFactory.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFontCreateFont(void)
{
	CFontFactory		cFactory;
	CFontImportParams	cParams;

	cParams.Init("Input" _FS_ "Font Pack", , 8, 8);
	cFactory.Init();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFont(void)
{
	BeginTests();

	DataIOInit();
	ObjectsInit();

	TestFontCreateFont();

	ObjectsKill();
	DataIOKill();

	TestStatistics();
}


