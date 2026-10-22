#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/Logger.h"
#include "StandardLib/Objects.h"
#include "SupportLib/FontFamily.h"
#include "TestLib/Assert.h"


#define FAMILY_FONTS	"Input" _FS_ "Fonts" _FS_


//////////////////////////////////////////////////////////////////////////
//
// Liberation Sans in its four faces.
//
//////////////////////////////////////////////////////////////////////////
Ptr<CFontFamily> CreateLiberationFamily(float32 fDefaultPixelSize, EColourOrder eColourOrder)
{
	Ptr<CFontFamily>	pFamily;

	pFamily = OMalloc<CFontFamily>("Liberation Sans", "AB ab", fDefaultPixelSize, eColourOrder);
	AssertTrue(pFamily->SetFace(FS_Regular, FAMILY_FONTS "LiberationSans-Regular.ttf"));
	AssertTrue(pFamily->SetFace(FS_Bold, FAMILY_FONTS "LiberationSans-Bold.ttf"));
	AssertTrue(pFamily->SetFace(FS_Italic, FAMILY_FONTS "LiberationSans-Italic.ttf"));
	AssertTrue(pFamily->SetFace(FS_BoldItalic, FAMILY_FONTS "LiberationSans-BoldItalic.ttf"));
	return pFamily;
}


//////////////////////////////////////////////////////////////////////////
//
// Each face and size is made once, the first time it is asked for.
//
//////////////////////////////////////////////////////////////////////////
void TestFontFamilyFacesAndSizes(void)
{
	ObjectsInit();
	{
		Ptr<CFontFamily>	pFamily;
		Ptr<CFontColours>	pRegular;
		Ptr<CFontColours>	pBold;
		Ptr<CFontColours>	pItalic;
		Ptr<CFontColours>	pBoldItalic;
		Ptr<CFontColours>	pBig;
		STextStyle			sStyle;
		ARGB32				sRed;

		pFamily = CreateLiberationFamily(16.0f, CCO_Unknown);
		AssertString("Liberation Sans", pFamily->GetFamilyName());
		AssertTrue(pFamily->GetDefaultPixelSize() == 16.0f);
		AssertSize(0, pFamily->NumSizes());

		//A size of 0 is the default size.  Sizes are told apart to 1/64 of a pixel.
		pRegular = pFamily->GetColours(FS_Regular, 0.0f);
		AssertTrue(pRegular.IsNotNull());
		AssertString("Liberation Sans Regular 16px", pRegular->GetWhite()->GetFontName());
		AssertTrue(pFamily->GetColours(FS_Regular, 16.0f) == pRegular);
		AssertTrue(pFamily->GetColours(FS_Regular, 16.004f) == pRegular);
		AssertSize(1, pFamily->NumSizes());

		pBold = pFamily->GetColours(FS_Bold, 16.0f);
		pItalic = pFamily->GetColours(FS_Italic, 16.0f);
		pBoldItalic = pFamily->GetColours(FS_BoldItalic, 16.0f);
		AssertString("Liberation Sans Bold 16px", pBold->GetWhite()->GetFontName());
		AssertString("Liberation Sans Italic 16px", pItalic->GetWhite()->GetFontName());
		AssertString("Liberation Sans Bold Italic 16px", pBoldItalic->GetWhite()->GetFontName());
		AssertSize(4, pFamily->NumSizes());

		//Bold A is wider than regular A.
		AssertInt(11, pRegular->GetWhite()->GetGlyph((uint32)'A', 1)->GetStep());
		AssertInt(12, pBold->GetWhite()->GetGlyph((uint32)'A', 1)->GetStep());

		pBig = pFamily->GetColours(FS_Regular, 32.0f);
		AssertString("Liberation Sans Regular 32px", pBig->GetWhite()->GetFontName());
		AssertTrue(pBig->GetWhite()->GetLineHeight() > pRegular->GetWhite()->GetLineHeight());
		AssertSize(5, pFamily->NumSizes());

		//A style's font is its face and size in its colour.
		sRed = Set32BitColour((uint8)0xFF, (uint8)0x00, (uint8)0x00);
		sStyle.Init(true, false, 16.0f, sRed);
		AssertTrue(pFamily->GetFont(&sStyle) == pBold->GetFont(sRed));
		sStyle.Init(false, false, 0.0f, FONT_COLOURS_WHITE);
		AssertTrue(pFamily->GetFont(&sStyle) == pRegular->GetWhite());
		AssertSize(5, pFamily->NumSizes());

		pBig = NULL;
		pBoldItalic = NULL;
		pItalic = NULL;
		pBold = NULL;
		pRegular = NULL;
		pFamily = NULL;
	}
	ObjectsKill(false);
}


//////////////////////////////////////////////////////////////////////////
//
// A style with no face is an error, as is a face that can't be loaded.
//
//////////////////////////////////////////////////////////////////////////
void TestFontFamilyMissingFace(void)
{
	ObjectsInit();
	{
		Ptr<CFontFamily>	pFamily;
		Ptr<CFontColours>	pColours;
		SLogConfig			sLogConfig;
		STextStyle			sStyle;

		pFamily = OMalloc<CFontFamily>("Liberation Sans", "AB", 16.0f, CCO_Unknown);
		AssertTrue(pFamily->SetFace(FS_Regular, FAMILY_FONTS "LiberationSans-Regular.ttf"));
		AssertTrue(pFamily->HasFace(FS_Regular));
		AssertFalse(pFamily->HasFace(FS_Bold));

		sLogConfig = gcLogger.SetSilent();
		pColours = pFamily->GetColours(FS_Bold, 16.0f);
		AssertTrue(pColours.IsNull());
		sStyle.Init(false, true, 16.0f, FONT_COLOURS_WHITE);
		AssertTrue(pFamily->GetFont(&sStyle).IsNull());
		AssertFalse(pFamily->SetFace(FS_Bold, FAMILY_FONTS "Missing.ttf"));
		gcLogger.SetConfig(&sLogConfig);
		AssertFalse(pFamily->HasFace(FS_Bold));
		AssertSize(0, pFamily->NumSizes());

		pColours = NULL;
		pFamily = NULL;
	}
	ObjectsKill(false);
}


//////////////////////////////////////////////////////////////////////////
//
// A family of one font already made has only that style and size.
//
//////////////////////////////////////////////////////////////////////////
void TestFontFamilyOneFont(void)
{
	ObjectsInit();
	{
		Ptr<CFontFamily>	pLiberation;
		Ptr<CFontColours>	pColours;
		Ptr<CFontFamily>	pFamily;
		SLogConfig			sLogConfig;

		pLiberation = CreateLiberationFamily(16.0f, CCO_Unknown);
		pColours = pLiberation->GetColours(FS_Regular, 0.0f);

		pFamily = OMalloc<CFontFamily>(pColours);
		AssertString("Liberation Sans Regular 16px", pFamily->GetFamilyName());
		AssertTrue(pFamily->GetColours(FS_Regular, 0.0f) == pColours);
		AssertSize(1, pFamily->NumSizes());

		sLogConfig = gcLogger.SetSilent();
		AssertTrue(pFamily->GetColours(FS_Bold, 0.0f).IsNull());
		AssertTrue(pFamily->GetColours(FS_Regular, 16.0f).IsNull());
		gcLogger.SetConfig(&sLogConfig);
		AssertSize(1, pFamily->NumSizes());

		pFamily = NULL;
		pColours = NULL;
		pLiberation = NULL;
	}
	ObjectsKill(false);
}


//////////////////////////////////////////////////////////////////////////
//
// Sizes are made in the family's colour order.
//
//////////////////////////////////////////////////////////////////////////
void TestFontFamilyColourOrder(void)
{
	ObjectsInit();
	{
		Ptr<CFontFamily>	pFamily;
		Ptr<CFontColours>	pColours;

		pFamily = CreateLiberationFamily(16.0f, CCO_BGR);
		pColours = pFamily->GetColours(FS_Italic, 0.0f);
		AssertInt(CCO_BGR, pColours->GetWhite()->GetImage()->GetColourOrder());
		AssertInt(CCO_BGR, pColours->GetFont(Set32BitColour((uint8)0x10, (uint8)0x20, (uint8)0x30))->GetImage()->GetColourOrder());

		pColours = NULL;
		pFamily = NULL;
	}
	ObjectsKill(false);
}


//////////////////////////////////////////////////////////////////////////
//
// Superscript and subscript are the face at the size times the font's
// scale, their baselines moved by the font's shift.
//
//////////////////////////////////////////////////////////////////////////
void TestFontFamilySuperscriptAndSubscript(void)
{
	ObjectsInit();
	{
		Ptr<CFontFamily>	pFamily;
		Ptr<CFontFamily>	pOneFont;
		Ptr<CFont>			pFont;
		STextStyle			sStyle;
		int16				iShift;
		ARGB32				sRed;
		SLogConfig			sLogConfig;

		pFamily = CreateLiberationFamily(16.0f, CCO_Unknown);
		sRed = Set32BitColour((uint8)0xFF, (uint8)0x00, (uint8)0x00);

		//Not moved.
		sStyle.Init(false, false, 0.0f, FONT_COLOURS_WHITE);
		pFont = pFamily->GetRunFont(&sStyle, &iShift);
		AssertString("Liberation Sans Regular 16px", pFont->GetFontName());
		AssertInt(0, iShift);

		//16 * 1331 / 2048 = 10.4 pixels, raised 977 units at 16 pixels.
		sStyle.ePosition = TP_Superscript;
		pFont = pFamily->GetRunFont(&sStyle, &iShift);
		AssertString("Liberation Sans Regular 10px", pFont->GetFontName());
		AssertInt(8, iShift);
		AssertTrue(pFont == pFamily->GetColours(FS_Regular, 16.0f * 1331.0f / 2048.0f)->GetWhite());

		//Lowered 283 units at 16 pixels.
		sStyle.ePosition = TP_Subscript;
		pFont = pFamily->GetRunFont(&sStyle, &iShift);
		AssertString("Liberation Sans Regular 10px", pFont->GetFontName());
		AssertInt(-2, iShift);

		//In the style's face, size and colour.
		sStyle.Init(true, false, 32.0f, sRed);
		sStyle.ePosition = TP_Superscript;
		pFont = pFamily->GetRunFont(&sStyle, &iShift);
		AssertString("Liberation Sans Bold 21px", pFont->GetFontName());
		AssertInt(15, iShift);
		AssertTrue(pFont == pFamily->GetColours(FS_Bold, 32.0f * 1331.0f / 2048.0f)->GetFont(sRed));
		AssertTrue(pFamily->GetFont(&sStyle) == pFont);

		//A family of a font already made can't make the smaller size.
		pOneFont = OMalloc<CFontFamily>(pFamily->GetColours(FS_Regular, 0.0f));
		sStyle.Init(false, false, 0.0f, FONT_COLOURS_WHITE);
		sStyle.ePosition = TP_Subscript;
		sLogConfig = gcLogger.SetSilent();
		AssertTrue(pOneFont->GetRunFont(&sStyle, &iShift).IsNull());
		gcLogger.SetConfig(&sLogConfig);
		AssertInt(0, iShift);

		pOneFont = NULL;
		pFont = NULL;
		pFamily = NULL;
	}
	ObjectsKill(false);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFontFamily(void)
{
	BeginTests();

	DataIOInit();

	TestFontFamilyFacesAndSizes();
	TestFontFamilyMissingFace();
	TestFontFamilyOneFont();
	TestFontFamilyColourOrder();
	TestFontFamilySuperscriptAndSubscript();

	DataIOKill();

	TestStatistics();
}

