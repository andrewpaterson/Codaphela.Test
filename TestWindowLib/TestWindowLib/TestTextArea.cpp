#include "BaseLib/GlobalMemory.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/UTF8.h"
#include "StandardLib/Objects.h"
#include "SupportLib/FontReader.h"
#include "SupportLib/SimpleTextReader.h"
#include "SupportLib/GlyphListFontDraw.h"
#include "WindowLib/Window.h"
#include "WindowLib/FillContainer.h"
#include "WindowLib/TextArea.h"
#include "WindowLib/ClearCanvasDraw.h"
#include "WinRefLib/WinRefWindowFactory.h"
#include "TestLib/AssertGeometric.h"
#include "TestLib/AssertFile.h"
#include "TickTestRefWindow.h"
#include "DataTestRefWindow.h"


Ptr<CFont> ReadLabelFont(void);
void ValidateLabelObjects(void);
void AssertLabelObjectsRemoved(void);


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
Ptr<CText> ReadTextAreaText(Ptr<CFont> pFont, const char* szText)
{
	CSimpleTextReader	cReader;
	CUTF8				cUTF8;
	Ptr<CText>			pText;

	cUTF8.Init(szText);
	cReader.Init(&pFont);
	pText = cReader.Read(&cUTF8, true);
	cReader.Kill();
	cUTF8.Kill();
	return pText;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void LayoutTextAreaText(Ptr<CTextLayout> pLayout, Ptr<CGlyphListFontDraw> pDraw, Ptr<CFont> pFont, const char* szText)
{
	Ptr<CText>	pText;

	pText = ReadTextAreaText(pFont, szText);
	pDraw->Begin();
	pLayout->Layout(pDraw, pText);
	pDraw->End();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int32 TextAreaWidth(Ptr<CFont> pFont, const char* szText)
{
	return (int32)pFont->CalculateWidth((char*)szText);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int32 TextAreaMax(int32 i1, int32 i2)
{
	return (i1 > i2) ? i1 : i2;
}


//////////////////////////////////////////////////////////////////////////
//
// Lines in a CTextLayout end at line feeds and, given a width, are wrapped
// at spaces.
//
//////////////////////////////////////////////////////////////////////////
void TestTextAreaLayout(void)
{
	{
		Ptr<CFont>					pFont;
		Ptr<CTextLayout>			pLayout;
		Ptr<CGlyphListFontDraw>		pDraw;
		CArrayGlyphPosition*		pasGlyphs;
		SInt32Vec2					sSize;
		int32						iWidth;

		pFont = ReadLabelFont();
		AssertTrue(pFont.IsNotNull());
		AssertInt(24, pFont->GetLineHeight());

		pLayout = OMalloc<CTextLayout>();
		pDraw = OMalloc<CGlyphListFontDraw>();
		AssertInt(-1, pLayout->GetWidth());

		//Without a width only line feeds end lines.  An empty line is as high as the font.
		LayoutTextAreaText(pLayout, pDraw, pFont, "ab\n\ncd");
		sSize = pLayout->GetSize();
		AssertInt32Vec2(TextAreaMax(TextAreaWidth(pFont, "ab"), TextAreaWidth(pFont, "cd")), 72, &sSize);
		pasGlyphs = pDraw->GetGlyphs();
		AssertSize(4, pasGlyphs->NumElements());
		AssertInt32Vec2(0, 0, &pasGlyphs->Get(0)->sPosition);
		AssertInt32Vec2(TextAreaWidth(pFont, "a"), 0, &pasGlyphs->Get(1)->sPosition);
		AssertInt32Vec2(0, 48, &pasGlyphs->Get(2)->sPosition);
		AssertInt32Vec2(TextAreaWidth(pFont, "c"), 48, &pasGlyphs->Get(3)->sPosition);

		//Without a width a line is never wrapped.
		LayoutTextAreaText(pLayout, pDraw, pFont, "aaa bbb ccc");
		sSize = pLayout->GetSize();
		AssertInt32Vec2(TextAreaWidth(pFont, "aaa bbb ccc"), 24, &sSize);

		//A word that doesn't fit goes on the next line.  The space before it stays at the end of the line above.
		iWidth = TextAreaWidth(pFont, "aaa bbb");
		pLayout->SetWidth(iWidth);
		AssertInt(iWidth, pLayout->GetWidth());
		LayoutTextAreaText(pLayout, pDraw, pFont, "aaa bbb ccc");
		sSize = pLayout->GetSize();
		AssertInt32Vec2(iWidth, 48, &sSize);
		pasGlyphs = pDraw->GetGlyphs();
		AssertSize(11, pasGlyphs->NumElements());
		AssertInt32Vec2(TextAreaWidth(pFont, "aaa "), 0, &pasGlyphs->Get(4)->sPosition);
		AssertInt32Vec2(iWidth, 0, &pasGlyphs->Get(7)->sPosition);
		AssertInt32Vec2(0, 24, &pasGlyphs->Get(8)->sPosition);
		AssertInt32Vec2(TextAreaWidth(pFont, "cc"), 24, &pasGlyphs->Get(10)->sPosition);

		//One pixel narrower and the second word wraps too.
		pLayout->SetWidth(iWidth - 1);
		LayoutTextAreaText(pLayout, pDraw, pFont, "aaa bbb ccc");
		sSize = pLayout->GetSize();
		AssertInt32Vec2(TextAreaMax(TextAreaWidth(pFont, "aaa"), TextAreaMax(TextAreaWidth(pFont, "bbb"), TextAreaWidth(pFont, "ccc"))), 72, &sSize);
		pasGlyphs = pDraw->GetGlyphs();
		AssertInt32Vec2(0, 24, &pasGlyphs->Get(4)->sPosition);
		AssertInt32Vec2(0, 48, &pasGlyphs->Get(8)->sPosition);

		//A word too wide for a line by itself is broken between glyphs.
		iWidth = TextAreaWidth(pFont, "abc");
		pLayout->SetWidth(iWidth);
		LayoutTextAreaText(pLayout, pDraw, pFont, "abcdef");
		sSize = pLayout->GetSize();
		AssertInt32Vec2(TextAreaMax(iWidth, TextAreaWidth(pFont, "def")), 48, &sSize);
		pasGlyphs = pDraw->GetGlyphs();
		AssertSize(6, pasGlyphs->NumElements());
		AssertInt32Vec2(TextAreaWidth(pFont, "ab"), 0, &pasGlyphs->Get(2)->sPosition);
		AssertInt32Vec2(0, 24, &pasGlyphs->Get(3)->sPosition);

		//Even a glyph wider than the line is placed, on a line of its own.
		pLayout->SetWidth(1);
		LayoutTextAreaText(pLayout, pDraw, pFont, "ab");
		sSize = pLayout->GetSize();
		AssertInt32Vec2(TextAreaMax(TextAreaWidth(pFont, "a"), TextAreaWidth(pFont, "b")), 48, &sSize);

		//Spaces at the end of a wrapped line don't make the text wider.
		pLayout->SetWidth(1000);
		LayoutTextAreaText(pLayout, pDraw, pFont, "ab   ");
		sSize = pLayout->GetSize();
		AssertInt32Vec2(TextAreaWidth(pFont, "ab"), 24, &sSize);

		//Line feeds still end lines when wrapping.
		LayoutTextAreaText(pLayout, pDraw, pFont, "aaa\nbbb\n");
		sSize = pLayout->GetSize();
		AssertInt32Vec2(TextAreaMax(TextAreaWidth(pFont, "aaa"), TextAreaWidth(pFont, "bbb")), 72, &sSize);
		pasGlyphs = pDraw->GetGlyphs();
		AssertInt32Vec2(0, 24, &pasGlyphs->Get(3)->sPosition);

		ValidateLabelObjects();

		pDraw = NULL;
		pLayout = NULL;
		pFont = NULL;
	}

	AssertLabelObjectsRemoved();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTextAreaWordWrap(void)
{
	CWinRefWindowFactory	cNativeFactory;

	{
		Ptr<CWindow>			pTestWindow;
		Ptr<CFont>				pFont;
		Ptr<CTextArea>			pTextArea;
		CTickTestRefWindow		cTick;
		SDataTestRefWindow		cData;
		SInt32Vec2				sSize;
		SInt32Vec2				sPosition;
		SInt32Vec2				sArea;
		CPointer				pNull;
		int32					iWidth;

		cNativeFactory.Init(&gcMemoryAllocator, 64, 32, NULL);
		cTick.Init(&cData, 1);
		pTestWindow = OMalloc<CWindow>("Text Area Window", &cNativeFactory, &cTick, pNull, CFT_RGB, CCO_RGB, CRGB_24bit, ARGB_None);

		pFont = ReadLabelFont();
		AssertTrue(pFont.IsNotNull());

		//Word wrap is off by default.  The required size is the size of the laid out text.
		pTextArea = OMalloc<CTextArea>(pTestWindow, pFont, "aaa bbb\nccc");
		AssertString("aaa bbb\nccc", pTextArea->GetText());
		AssertFalse(pTextArea->IsWordWrap());
		AssertTrue(pTextArea->IsTransparent());
		iWidth = TextAreaMax(TextAreaWidth(pFont, "aaa bbb"), TextAreaWidth(pFont, "ccc"));
		sSize = pTextArea->GetTextSize();
		AssertInt32Vec2(iWidth, 48, &sSize);
		sSize = pTextArea->GetRequiredSize();
		AssertInt32Vec2(iWidth, 48, &sSize);
		sSize = pTextArea->GetDesiredSize();
		AssertInt32Vec2(iWidth, 48, &sSize);

		//A desired size overrides the required size only on the axes it is set on.
		pTextArea->SetDesiredSize(50, -1);
		sSize = pTextArea->GetDesiredSize();
		AssertInt32Vec2(50, 48, &sSize);
		pTextArea->SetDesiredSize(-1, 30);
		sSize = pTextArea->GetDesiredSize();
		AssertInt32Vec2(iWidth, 30, &sSize);
		pTextArea->SetDesiredSize(-1, -1);

		//The required size follows the text.
		pTextArea->SetText("aaa bbb ccc\nddd\neee");
		sSize = pTextArea->GetRequiredSize();
		AssertInt32Vec2(TextAreaWidth(pFont, "aaa bbb ccc"), 72, &sSize);
		pTextArea->SetText("aaa bbb\nccc");

		//A word wrapped text area takes whatever width it is given.  Until it is laid out it has no width so its lines
		//aren't wrapped.
		pTextArea->SetWordWrap(true);
		AssertTrue(pTextArea->IsWordWrap());
		sSize = pTextArea->GetTextSize();
		AssertInt32Vec2(iWidth, 48, &sSize);
		sSize = pTextArea->GetRequiredSize();
		AssertInt32Vec2(-1, 48, &sSize);
		sSize = pTextArea->GetDesiredSize();
		AssertInt32Vec2(-1, 48, &sSize);

		//Laid out narrower than a line the text is wrapped to the width it is given and needs more height.
		iWidth = TextAreaWidth(pFont, "aaa bbb") - 1;
		sPosition.Init(0, 0);
		sArea.Init(iWidth, 100);
		pTextArea->Layout(sPosition, sArea);
		sSize = pTextArea->GetActualSize();
		AssertInt32Vec2(iWidth, 100, &sSize);
		sSize = pTextArea->GetTextSize();
		AssertInt32Vec2(TextAreaMax(TextAreaWidth(pFont, "aaa"), TextAreaMax(TextAreaWidth(pFont, "bbb"), TextAreaWidth(pFont, "ccc"))), 72, &sSize);
		sSize = pTextArea->GetRequiredSize();
		AssertInt32Vec2(-1, 72, &sSize);

		//New text is wrapped to the same width.
		pTextArea->SetText("aaa bbb");
		AssertString("aaa bbb", pTextArea->GetText());
		sSize = pTextArea->GetTextSize();
		AssertInt32Vec2(TextAreaMax(TextAreaWidth(pFont, "aaa"), TextAreaWidth(pFont, "bbb")), 48, &sSize);
		sSize = pTextArea->GetRequiredSize();
		AssertInt32Vec2(-1, 48, &sSize);

		//Without word wrap only line feeds end lines.
		pTextArea->SetWordWrap(false);
		sSize = pTextArea->GetRequiredSize();
		AssertInt32Vec2(TextAreaWidth(pFont, "aaa bbb"), 24, &sSize);
		pTextArea->SetWordWrap(true);
		sSize = pTextArea->GetRequiredSize();
		AssertInt32Vec2(-1, 48, &sSize);

		//Laid out wider the text is wrapped again.
		sArea.Init(200, 100);
		pTextArea->Layout(sPosition, sArea);
		sSize = pTextArea->GetTextSize();
		AssertInt32Vec2(TextAreaWidth(pFont, "aaa bbb"), 24, &sSize);
		sSize = pTextArea->GetRequiredSize();
		AssertInt32Vec2(-1, 24, &sSize);

		//Even with no text a text area is a line high.
		pTextArea->SetText("");
		sSize = pTextArea->GetRequiredSize();
		AssertInt32Vec2(-1, 24, &sSize);
		pTextArea->SetWordWrap(false);
		sSize = pTextArea->GetRequiredSize();
		AssertInt32Vec2(0, 24, &sSize);

		ValidateLabelObjects();

		pTextArea = NULL;
		pFont = NULL;
		pTestWindow = NULL;
	}

	AssertLabelObjectsRemoved();
	cNativeFactory.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// A word wrapped text area in a fill container with insets takes the
// width inside the insets and wraps its text to fit.  Its height is the
// height of the wrapped lines, which is only known once it has been given
// its width, so the window lays it out again.
//
//////////////////////////////////////////////////////////////////////////
void TestTextAreaFillContainer(void)
{
	CWinRefWindowFactory	cNativeFactory;
	CFileUtil				cFileUtil;
	char					szDirectory[] = "Output" _FS_ "TextAreaFillContainer";
	int32					iWidth;
	int32					iHeight;

	iWidth = 200;
	iHeight = 160;

	cFileUtil.RemoveDir(szDirectory);
	cFileUtil.MakeDir(szDirectory);

	{
		Ptr<CWindow>			pTestWindow;
		Ptr<CFont>				pFont;
		Ptr<CFillContainer>		pFill;
		Ptr<CClearCanvasDraw>	pBackground;
		Ptr<CTextArea>			pTextArea;
		CTickTestRefWindow		cTick;
		SDataTestRefWindow		cData;
		SInt32Vec2				sVec;
		SInsets					sInsets;
		int						aiInsets[4];
		CChars					szExpectedDirectory;
		CPointer				pNull;

		cNativeFactory.Init(&gcMemoryAllocator, iWidth, iHeight, szDirectory);
		cTick.Init(&cData, 1);
		//The text area is transparent, it is drawn over the window's background.
		pBackground = OMalloc<CClearCanvasDraw>(Set32BitColour((uint8)40, 60, 110));
		pTestWindow = OMalloc<CWindow>("Text Area Window", &cNativeFactory, &cTick, pBackground, CFT_RGB, CCO_RGB, CRGB_24bit, ARGB_None);

		pFill = OMalloc<CFillContainer>(pTestWindow);
		aiInsets[BEI_Top] = 5;
		aiInsets[BEI_Right] = 8;
		aiInsets[BEI_Bottom] = 5;
		aiInsets[BEI_Left] = 8;
		sInsets.Init(aiInsets);
		pFill->SetInsets(&sInsets);
		pTestWindow->SetContainer(pFill);

		pFont = ReadLabelFont();
		AssertTrue(pFont.IsNotNull());

		pTextArea = OMalloc<CTextArea>(pTestWindow, pFont, "The quick brown fox jumps over the lazy dog.\nPack my box with five dozen liquor jugs.");
		pTextArea->SetWordWrap(true);
		pTextArea->SetAlignment(CSH_Left, CSV_Top);
		pFill->AddComponent(pTextArea);

		pTestWindow->Show();

		sVec = pTextArea->GetPosition();
		AssertInt32Vec2(8, 5, &sVec);
		sVec = pTextArea->GetTextSize();
		AssertTrue(sVec.x <= iWidth - 16);
		AssertInt(144, sVec.y);
		sVec = pTextArea->GetActualSize();
		AssertInt32Vec2(iWidth - 16, 144, &sVec);

		ValidateLabelObjects();

		pTextArea = NULL;
		pFont = NULL;
		pFill = NULL;
		pTestWindow = NULL;
		pBackground = NULL;

		szExpectedDirectory.Init(szDirectory);
		szExpectedDirectory.Replace("Output", "Input");
		AssertDirectory(szExpectedDirectory.Text(), szDirectory);
		szExpectedDirectory.Kill();
	}

	AssertLabelObjectsRemoved();
	cNativeFactory.Kill();
	cFileUtil.RemoveDir(szDirectory);
}


//////////////////////////////////////////////////////////////////////////
//
// A text area that isn't word wrapped is the size of its text and placed
// by its alignment.  The shown frame is written to
// Output/TextAreaNoWordWrapFill.
//
//////////////////////////////////////////////////////////////////////////
void TestTextAreaNoWordWrapFillContainer(void)
{
	CWinRefWindowFactory	cNativeFactory;
	CFileUtil				cFileUtil;
	const char*				szDirectory;

	szDirectory = "Output" _FS_ "TextAreaNoWordWrapFill";
	cFileUtil.RemoveDir(szDirectory);
	cFileUtil.MakeDir(szDirectory);

	{
		Ptr<CWindow>			pTestWindow;
		Ptr<CFont>				pFont;
		Ptr<CFillContainer>		pFill;
		Ptr<CTextArea>			pTextArea;
		CTickTestRefWindow		cTick;
		SDataTestRefWindow		cData;
		SInt32Vec2				sVec;
		CPointer				pNull;
		int32					iTextWidth;

		cNativeFactory.Init(&gcMemoryAllocator, 200, 100, (char*)szDirectory);
		cTick.Init(&cData, 1);
		pTestWindow = OMalloc<CWindow>("Text Area Window", &cNativeFactory, &cTick, pNull, CFT_RGB, CCO_RGB, CRGB_24bit, ARGB_None);

		pFill = OMalloc<CFillContainer>(pTestWindow);
		pTestWindow->SetContainer(pFill);

		pFont = ReadLabelFont();
		AssertTrue(pFont.IsNotNull());

		pTextArea = OMalloc<CTextArea>(pTestWindow, pFont, "aaa bbb\nccc ddd eee");
		pTextArea->SetAlignment(CSH_Right, CSV_Bottom);
		pFill->AddComponent(pTextArea);

		pTestWindow->Show();

		iTextWidth = TextAreaWidth(pFont, "ccc ddd eee");
		sVec = pTextArea->GetActualSize();
		AssertInt32Vec2(iTextWidth, 48, &sVec);
		sVec = pTextArea->GetPosition();
		AssertInt32Vec2(200 - iTextWidth, 100 - 48, &sVec);
		sVec = pTextArea->GetTextSize();
		AssertInt32Vec2(iTextWidth, 48, &sVec);

		ValidateLabelObjects();

		pTextArea = NULL;
		pFont = NULL;
		pFill = NULL;
		pTestWindow = NULL;
	}

	AssertLabelObjectsRemoved();
	cNativeFactory.Kill();
	cFileUtil.RemoveDir(szDirectory);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTextArea(void)
{
	BeginTests();
	ObjectsInit();

	TestTextAreaLayout();
	TestTextAreaWordWrap();
	TestTextAreaFillContainer();
	TestTextAreaNoWordWrapFillContainer();

	ObjectsFlush();
	ObjectsKill();
	TestStatistics();
}

