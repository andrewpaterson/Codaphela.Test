#include "BaseLib/FastFunctions.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/UTF8.h"
#include "BaseLib/TextFile.h"
#include "StandardLib/Objects.h"
#include "SupportLib/Font.h"
#include "SupportLib/FontFactory.h"
#include "SupportLib/Text.h"
#include "SupportLib/SimpleTextReader.h"
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
Ptr<CFont> CreateFont(char* szFontName, int iCharWidth, int iCharHeight)
{
	CFontFactory				cFactory;
	CFontImportParams			cParams;
	CChars						szCharacterFile;
	CChars						szImageFile;
	Ptr<CFont>					pFont;
	char						szDirectory[] = { "Input" _FS_ "Font Pack" _FS_ };
	bool						bExists;

	szCharacterFile.Init(szDirectory);
	szCharacterFile.Append(szFontName);
	szCharacterFile.Append(".txt");
	szImageFile.Init(szDirectory);
	szImageFile.Append(szFontName);
	szImageFile.Append(".png");

	bExists = cParams.Init(szImageFile.Text(), szCharacterFile.Text(), iCharWidth, iCharHeight);
	if (!bExists)
	{
		szCharacterFile.Kill();
		szImageFile.Kill();
		cParams.Kill();
		return NULL;
	}
	
	cFactory.Init();
	pFont = cFactory.Generate(&cParams);
	szCharacterFile.Kill();
	szImageFile.Kill();
	cFactory.Kill();
	cParams.Kill();

	return pFont;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFontLookupText(void)
{
	Ptr<CFont>			pFont;
	Ptr<CText>			pText;
	CSimpleTextReader	cTextReader;
	size				uiNumRuns;
	size				uiNumElements;
	CTextRun*			pcRun;
	CTextElement*		pcElement;

	pFont = CreateFont("anuvverbubbla_8x8", 8, 8);
	cTextReader.Init(&pFont);
	pText = cTextReader.Read("Input" _FS_ "Text" _FS_ "Test1 anuvverbubbla.txt");
	cTextReader.Kill();

	uiNumRuns = pText->NumRuns();
	AssertSize(3, uiNumRuns);

	pcRun = pText->GetRun(0);
	uiNumElements = pcRun->NumElements();
	AssertSize(2, uiNumElements);
	pcElement = pcRun->GetElement(0);
	AssertString("CTextUTF16Long", pcElement->ClassName());
	pcElement = pcRun->GetElement(1);
	AssertString("CTextNewLine", pcElement->ClassName());

	pcRun = pText->GetRun(1);
	uiNumElements = pcRun->NumElements();
	AssertSize(2, uiNumElements);
	pcElement = pcRun->GetElement(0);
	AssertString("CTextUTF16Long", pcElement->ClassName());
	pcElement = pcRun->GetElement(1);
	AssertString("CTextNewLine", pcElement->ClassName());

	pcRun = pText->GetRun(2);
	uiNumElements = pcRun->NumElements();
	AssertSize(2, uiNumElements);
	pcElement = pcRun->GetElement(0);
	AssertString("CTextUTF16Long", pcElement->ClassName());
	pcElement = pcRun->GetElement(1);
	AssertString("CTextNewLine", pcElement->ClassName());


	pText->Kill();
	pFont = NULL;

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
	TestFontLookupText();

	ObjectsKill();
	DataIOKill();

	TestStatistics();
}


