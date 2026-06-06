#include "BaseLib/FastFunctions.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/UTF8.h"
#include "BaseLib/TextFile.h"
#include "StandardLib/Objects.h"
#include "SupportLib/ImageWriter.h"
#include "SupportLib/Font.h"
#include "SupportLib/FontFactory.h"
#include "SupportLib/Text.h"
#include "SupportLib/SimpleTextReader.h"
#include "SupportLib/TextUTF16Short.h"
#include "SupportLib/TextUTF16Long.h"
#include "SupportLib/TextLayout.h"
#include "SupportLib/GlyphListFontDraw.h"
#include "SupportLib/MapFontDraw.h"
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
	ObjectsInit();
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

		AssertSize(73, pFont->NumGlyphs());

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
	ObjectsKill();
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
	ObjectsInit();
	{
		Ptr<CFont>			pFont;
		Ptr<CText>			pText;
		CSimpleTextReader	cTextReader;
		size				uiNumRuns;
		size				uiNumElements;
		CTextRun* pcRun;
		CTextElement* pcElement;
		CTextUTF16Short* pcUTF16Short;
		CChars				sz;

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
		AssertString("CTextUTF16Short", pcElement->ClassName());
		pcUTF16Short = (CTextUTF16Short*)pcElement;
		sz.Init();
		pcUTF16Short->PrintAsASCII(&sz);
		AssertString("¿BACK IN THE DÄY?  ! ", sz.Text());
		sz.Kill();
		pcElement = pcRun->GetElement(1);
		AssertString("CTextNewLine", pcElement->ClassName());

		pcRun = pText->GetRun(1);
		uiNumElements = pcRun->NumElements();
		AssertSize(2, uiNumElements);
		pcElement = pcRun->GetElement(0);
		AssertString("CTextUTF16Short", pcElement->ClassName());
		pcUTF16Short = (CTextUTF16Short*)pcElement;
		sz.Init();
		pcUTF16Short->PrintAsASCII(&sz);
		AssertString(" Ñ = (5   3 + 7 / 2)", sz.Text());
		sz.Kill();
		pcElement = pcRun->GetElement(1);
		AssertString("CTextNewLine", pcElement->ClassName());

		pcRun = pText->GetRun(2);
		uiNumElements = pcRun->NumElements();
		AssertSize(2, uiNumElements);
		pcElement = pcRun->GetElement(0);
		AssertString("CTextUTF16Short", pcElement->ClassName());
		pcUTF16Short = (CTextUTF16Short*)pcElement;
		sz.Init();
		pcUTF16Short->PrintAsASCII(&sz);
		AssertString("  ©< >© UNICORNS  ", sz.Text());
		sz.Kill();
		pcElement = pcRun->GetElement(1);
		AssertString("CTextNewLine", pcElement->ClassName());

		pText->Kill();
		pFont = NULL;
	}
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertGlyph(int iXExpected, int iYExpected, char* szExpected, SGlyphPosition* psGlyph)
{
	CChars						sz;

	AssertInt(iXExpected, psGlyph->sPosition.x);
	AssertInt(iYExpected, psGlyph->sPosition.y);
	sz.Init();
	psGlyph->pcGlyph->Print(&sz);
	AssertString(szExpected, sz.Text());
	sz.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFontGetGlyphsFromText(void)
{
	ObjectsInit();
	{
		Ptr<CFont>					pFont;
		Ptr<CText>					pText;
		CSimpleTextReader			cTextReader;
		CTextLayout					cLayout;
		Ptr<CGlyphListFontDraw>		pFontDraw;
		CArrayGlyphPosition* pacGlyphs;

		pFont = CreateFont("anuvverbubbla_8x8", 8, 8);
		cTextReader.Init(&pFont);
		pText = cTextReader.Read("Input" _FS_ "Text" _FS_ "Test1 anuvverbubbla.txt");
		cTextReader.Kill();

		pFontDraw = OMalloc<CGlyphListFontDraw>();

		cLayout.Init();
		cLayout.Layout(pFontDraw, pText);
		cLayout.Kill();

		pacGlyphs = pFontDraw->GetGlyphs();
		AssertSize(59, pacGlyphs->NumElements());
		AssertGlyph(0, 0,
			"    ··  \n"
			"   ·••· \n"
			"   ···  \n"
			" ···OO· \n"
			"·•@@@•· \n"
			"·OO·····\n"
			"··ooooo·\n"
			" ·······\n", pacGlyphs->Get(0));
		AssertGlyph(8, 0,
			"······· \n"
			"·•••••··\n"
			"·oo··o•·\n"
			"·OOOOo· \n"
			"·@@··@o·\n"
			"·OOOOOO·\n"
			"·ooooo··\n"
			"······· \n", pacGlyphs->Get(1));
		AssertGlyph(16, 0,
			" ······ \n"
			"··••••··\n"
			"·oo···o·\n"
			"·OOOOOO·\n"
			"·@@···@·\n"
			"·OO· ·O·\n"
			"·oo· ·o·\n"
			"···· ···\n", pacGlyphs->Get(2));
		AssertGlyph(24, 0,
			" ·······\n"
			"··•••••·\n"
			"·oo·····\n"
			"·OO·    \n"
			"·@@·····\n"
			"·OOOOOO·\n"
			"··ooooo·\n"
			" ·······\n", pacGlyphs->Get(3));

		AssertGlyph(144, 0,
			"", pacGlyphs->Get(18));
		AssertGlyph(152, 0,
			" ··· \n"
			"·•••·\n"
			"·oo··\n"
			"·O·· \n"
			" ··  \n"
			"·OO· \n"
			"·oo· \n"
			" ··  \n", pacGlyphs->Get(19));
		AssertGlyph(160, 0,
			" ·· ·· \n"
			"··•·•··\n"
			"·OO•OO·\n"
			" ·@@@· \n"
			"  ·O·  \n"
			"   ·   \n", pacGlyphs->Get(20));

		AssertGlyph(24, 8,
			"······\n"
			"·oooo·\n"
			"······\n"
			"·@@@@·\n"
			"······\n", pacGlyphs->Get(24));
		AssertGlyph(64, 8,
			"   ··   \n"
			"  ····  \n"
			" ··oo·· \n"
			"··OOOO··\n"
			" ·•@@•· \n"
			"··OOOO··\n"
			"·o····o·\n"
			"···  ···\n", pacGlyphs->Get(29));

		pFontDraw->Kill();
		pText->Kill();
		pFont = NULL;
	}
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFontMapFontDraw(void)
{
	char		szDirectory[] = "Output" _FS_ "MapFontDraw";
	CFileUtil	cFileUtil;

	AssertTrue(cFileUtil.RemoveDir(szDirectory));
	AssertTrue(cFileUtil.TouchDir(szDirectory));

	ObjectsInit();
	{
		Ptr<CFont>			pFont;
		Ptr<CText>			pText;
		CSimpleTextReader	cTextReader;
		CTextLayout			cLayout;
		Ptr<CMapFontDraw>	pFontDraw;
		Ptr<CSpriteMap>		pSpriteMap;
		Ptr<CImage>			pImage;
		CChars				szOutputFilename;
		CChars				szInputFilename;
		bool				bWritten;

		pFont = CreateFont("anuvverbubbla_8x8", 8, 8);
		cTextReader.Init(&pFont);
		pText = cTextReader.Read("Input" _FS_ "Text" _FS_ "Test1 anuvverbubbla.txt");
		cTextReader.Kill();

		pSpriteMap = OMalloc<CSpriteMap>();
		pFontDraw = OMalloc<CMapFontDraw>(pSpriteMap);

		pSpriteMap->BeginChange();
		cLayout.Init();
		cLayout.Layout(pFontDraw, pText);
		cLayout.Kill();
		pSpriteMap->EndChange();

		pImage = pSpriteMap->WriteToImage();

		szOutputFilename.Init(szDirectory);
		cFileUtil.AppendToPath(&szOutputFilename, "anuvverbubbla.txt.png");
		bWritten = WriteImage(pImage, szOutputFilename.Text());
		AssertTrue(bWritten);

		pFontDraw->Kill();
		pText->Kill();
		pFont = NULL;

		szInputFilename.Init(szOutputFilename);
		szInputFilename.Replace("Output", "Input");

		AssertFile(szInputFilename, szOutputFilename);

		szOutputFilename.Kill();
		szInputFilename.Kill();
	}
	ObjectsKill();

}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFont(void)
{
	BeginTests();

	DataIOInit();

	TestFontCreateFont();
	TestFontLookupText();
	TestFontGetGlyphsFromText();
	TestFontMapFontDraw();

	DataIOKill();

	TestStatistics();
}

