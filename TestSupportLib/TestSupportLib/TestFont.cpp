#include "BaseLib/FastFunctions.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/UTF8.h"
#include "BaseLib/TextFile.h"
#include "StandardLib/Objects.h"
#include "SupportLib/Font.h"
#include "SupportLib/FontFactory.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertUTFChar(char* szExpected, char* szActual, size uiActualLength)
{
	size	uiExpectedLength;

	uiExpectedLength = strlen(szExpected);
	AssertSize(uiExpectedLength, uiActualLength);
	AssertMemory(szExpected, szActual, uiActualLength);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFontCreateFont(void)
{
	CFontFactory				cFactory;
	CFontImportParams			cParams;
	CChars						szCharacterFile;
	CChars						szImageFile;
	Ptr<CFont>					pFont;
	char						szDirectory[] = { "Input" _FS_ "Font Pack" _FS_ };
	bool						bExists;
	SIndexTreeMemoryIterator	sIter;
	char						szCharacter[5];
	size						uiLength;

	szCharacterFile.Init(szDirectory);
	szCharacterFile.Append("anuvverbubbla_8x8.txt");
	szImageFile.Init(szDirectory);
	szImageFile.Append("anuvverbubbla_8x8.png");

	bExists = cParams.Init(szImageFile.Text(), szCharacterFile.Text(), 8, 8);
	AssertTrue(bExists);
	cFactory.Init();
	pFont = cFactory.Generate(&cParams);
	AssertTrue(pFont.IsNotNull());

	AssertSize(69, pFont->NumGlyphs());

	memset(szCharacter, 0, 5);
	memset(szCharacter, 0x7F, 4);
	bExists = pFont->StartIteration(&sIter, (uint8*)szCharacter, &uiLength, 4);
	AssertUTFChar("\x5&", szCharacter, uiLength);
	bExists = pFont->Iterate(&sIter, (uint8*)szCharacter, &uiLength, 4);
	bExists = pFont->Iterate(&sIter, (uint8*)szCharacter, &uiLength, 4);
	bExists = pFont->Iterate(&sIter, (uint8*)szCharacter, &uiLength, 4);
	bExists = pFont->Iterate(&sIter, (uint8*)szCharacter, &uiLength, 4);
	bExists = pFont->Iterate(&sIter, (uint8*)szCharacter, &uiLength, 4);
	bExists = pFont->Iterate(&sIter, (uint8*)szCharacter, &uiLength, 4);
	bExists = pFont->Iterate(&sIter, (uint8*)szCharacter, &uiLength, 4);

	cFactory.Kill();
	cParams.Kill();

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


