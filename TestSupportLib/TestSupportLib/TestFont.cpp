#include "BaseLib/FastFunctions.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/UTF-8.h"
#include "BaseLib/TextFile.h"
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
	CChars				szCharacterFile;
	CChars				szImageFile;
	Ptr<CFont>			pFont;
	char				szDirectory[] = { "Input" _FS_ "Font Pack" _FS_ };
	bool				bExists;

	szCharacterFile.Init(szDirectory);
	szCharacterFile.Append("anuvverbubbla_8x8.txt");
	szImageFile.Init(szDirectory);
	szImageFile.Append("anuvverbubbla_8x8.png");

	bExists = cParams.Init(szImageFile.Text(), szCharacterFile.Text(), 8, 8);
	AssertTrue(bExists);
	cFactory.Init();
	pFont = cFactory.Generate(&cParams);
	AssertTrue(pFont.IsNotNull());
	cFactory.Kill();

	szCharacterFile.Kill();
	szImageFile.Kill();
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


