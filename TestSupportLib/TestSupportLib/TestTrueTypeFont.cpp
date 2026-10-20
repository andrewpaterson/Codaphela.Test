#include "BaseLib/FastFunctions.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/Logger.h"
#include "StandardLib/Objects.h"
#include "SupportLib/ImageWriter.h"
#include "SupportLib/TrueTypeFont.h"
#include "SupportLib/TrueTypeRasteriser.h"
#include "TestLib/Assert.h"
#include "TestLib/AssertFile.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
bool LoadTrueTypeFont(CTrueTypeFont* pcFont, char* szFontName)
{
	CChars	szFilename;
	bool	bResult;

	szFilename.Init("Input" _FS_ "Fonts" _FS_);
	szFilename.Append(szFontName);
	pcFont->Init();
	bResult = pcFont->Load(szFilename.Text());
	szFilename.Kill();
	return bResult;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertTrueTypeMetrics(int iAdvance, int iLeftSideBearing, int iXMin, int iYMin, int iXMax, int iYMax, CTrueTypeFont* pcFont, int iGlyph)
{
	STrueTypeGlyphMetrics	sMetrics;

	AssertTrue(pcFont->GetGlyphMetrics(iGlyph, &sMetrics));
	AssertInt(iAdvance, sMetrics.iAdvanceWidth);
	AssertInt(iLeftSideBearing, sMetrics.iLeftSideBearing);
	AssertInt(iXMin, sMetrics.iXMin);
	AssertInt(iYMin, sMetrics.iYMin);
	AssertInt(iXMax, sMetrics.iXMax);
	AssertInt(iYMax, sMetrics.iYMax);
}


//////////////////////////////////////////////////////////////////////////
//
// Returns false if the outline's points aren't exactly the glyph's
// bounding box.
//
//////////////////////////////////////////////////////////////////////////
bool TrueTypeOutlineMatchesBounds(CTrueTypeOutline* pcOutline, STrueTypeGlyphMetrics* psMetrics)
{
	size			i;
	STrueTypePoint*	psPoint;
	int32			iXMin;
	int32			iYMin;
	int32			iXMax;
	int32			iYMax;

	if (pcOutline->NumPoints() == 0)
	{
		return (psMetrics->iXMin == 0) && (psMetrics->iYMin == 0) && (psMetrics->iXMax == 0) && (psMetrics->iYMax == 0);
	}

	psPoint = pcOutline->GetPoint(0);
	iXMin = psPoint->x;
	iYMin = psPoint->y;
	iXMax = psPoint->x;
	iYMax = psPoint->y;
	for (i = 1; i < pcOutline->NumPoints(); i++)
	{
		psPoint = pcOutline->GetPoint(i);
		iXMin = (psPoint->x < iXMin) ? psPoint->x : iXMin;
		iYMin = (psPoint->y < iYMin) ? psPoint->y : iYMin;
		iXMax = (psPoint->x > iXMax) ? psPoint->x : iXMax;
		iYMax = (psPoint->y > iYMax) ? psPoint->y : iYMax;
	}
	return (iXMin == psMetrics->iXMin) && (iYMin == psMetrics->iYMin) && (iXMax == psMetrics->iXMax) && (iYMax == psMetrics->iYMax);
}


//////////////////////////////////////////////////////////////////////////
//
// Draws an opacity image as text, darker characters for more coverage.
//
//////////////////////////////////////////////////////////////////////////
void TrueTypeImageToString(Ptr<CImage> pcImage, CChars* psz)
{
	char	aszShades[] = " .:+*#";
	uint8*	puiData;
	int		x;
	int		y;
	uint8	uiValue;

	puiData = (uint8*)pcImage->GetData();
	for (y = 0; y < pcImage->GetHeight(); y++)
	{
		for (x = 0; x < pcImage->GetWidth(); x++)
		{
			uiValue = puiData[y * pcImage->GetWidth() + x];
			if (uiValue == 0)
			{
				psz->Append(aszShades[0]);
			}
			else if (uiValue == 255)
			{
				psz->Append(aszShades[5]);
			}
			else
			{
				psz->Append(aszShades[1 + uiValue / 64]);
			}
		}
		psz->Append('\n');
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTrueTypeFontLoad(void)
{
	CTrueTypeFont	cFont;
	CChars			sz;
	int				iXMin;
	int				iYMin;
	int				iXMax;
	int				iYMax;
	SLogConfig		sLogConfig;

	AssertTrue(LoadTrueTypeFont(&cFont, "LiberationSans-Regular.ttf"));
	AssertInt(675, cFont.NumGlyphs());
	AssertInt(2048, cFont.GetUnitsPerEm());
	AssertInt(1854, cFont.GetAscender());
	AssertInt(-434, cFont.GetDescender());
	AssertInt(67, cFont.GetLineGap());
	cFont.GetBounds(&iXMin, &iYMin, &iXMax, &iYMax);
	AssertInt(-416, iXMin);
	AssertInt(-621, iYMin);
	AssertInt(2151, iXMax);
	AssertInt(1864, iYMax);
	sz.Init();
	AssertTrue(cFont.GetName(TRUE_TYPE_NAME_FAMILY, &sz));
	AssertString("Liberation Sans", sz.Text());
	sz.Kill();
	cFont.Kill();

	AssertTrue(LoadTrueTypeFont(&cFont, "JetBrainsMonoNL-Regular.ttf"));
	AssertInt(1590, cFont.NumGlyphs());
	AssertInt(1000, cFont.GetUnitsPerEm());
	AssertInt(1020, cFont.GetAscender());
	AssertInt(-300, cFont.GetDescender());
	AssertInt(0, cFont.GetLineGap());
	sz.Init();
	AssertTrue(cFont.GetName(TRUE_TYPE_NAME_FAMILY, &sz));
	AssertString("JetBrains Mono NL", sz.Text());
	sz.Kill();
	cFont.Kill();

	AssertTrue(LoadTrueTypeFont(&cFont, "InterVariable.ttf"));
	AssertInt(2937, cFont.NumGlyphs());
	AssertInt(2048, cFont.GetUnitsPerEm());
	AssertInt(1984, cFont.GetAscender());
	AssertInt(-494, cFont.GetDescender());
	AssertInt(0, cFont.GetLineGap());
	sz.Init();
	AssertTrue(cFont.GetName(TRUE_TYPE_NAME_FAMILY, &sz));
	AssertString("Inter Variable", sz.Text());
	sz.Kill();
	cFont.Kill();

	sLogConfig = gcLogger.SetSilent();
	cFont.Init();
	AssertFalse(cFont.Load("Input" _FS_ "Fonts" _FS_ "Missing.ttf"));
	AssertFalse(cFont.Load("Input" _FS_ "Adelle.png"));
	cFont.Kill();
	gcLogger.SetConfig(&sLogConfig);
}


//////////////////////////////////////////////////////////////////////////
//
// Liberation Sans only has a format 4 character map; JetBrains Mono and
// Inter have format 12 maps too.
//
//////////////////////////////////////////////////////////////////////////
void TestTrueTypeFontGlyphIndex(void)
{
	CTrueTypeFont	cFont;

	AssertTrue(LoadTrueTypeFont(&cFont, "LiberationSans-Regular.ttf"));
	AssertInt(36, cFont.GetGlyphIndex('A'));
	AssertInt(3, cFont.GetGlyphIndex(' '));
	AssertInt(74, cFont.GetGlyphIndex('g'));
	AssertInt(8, cFont.GetGlyphIndex('%'));
	AssertInt(129, cFont.GetGlyphIndex(0xC1));
	AssertInt(169, cFont.GetGlyphIndex(0xE9));
	AssertInt(0, cFont.GetGlyphIndex(0x10FFFF));
	AssertInt(0, cFont.GetGlyphIndex(0x1F600));
	cFont.Kill();

	AssertTrue(LoadTrueTypeFont(&cFont, "JetBrainsMonoNL-Regular.ttf"));
	AssertInt(1, cFont.GetGlyphIndex('A'));
	AssertInt(888, cFont.GetGlyphIndex(' '));
	AssertInt(245, cFont.GetGlyphIndex('g'));
	AssertInt(1010, cFont.GetGlyphIndex('%'));
	AssertInt(2, cFont.GetGlyphIndex(0xC1));
	AssertInt(226, cFont.GetGlyphIndex(0xE9));
	AssertInt(0, cFont.GetGlyphIndex(0x10FFFF));
	cFont.Kill();

	AssertTrue(LoadTrueTypeFont(&cFont, "InterVariable.ttf"));
	AssertInt(2, cFont.GetGlyphIndex('A'));
	AssertInt(1777, cFont.GetGlyphIndex(' '));
	AssertInt(658, cFont.GetGlyphIndex('g'));
	AssertInt(1744, cFont.GetGlyphIndex('%'));
	AssertInt(6, cFont.GetGlyphIndex(0xC1));
	AssertInt(618, cFont.GetGlyphIndex(0xE9));
	AssertInt(0, cFont.GetGlyphIndex(0x10FFFF));
	cFont.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTrueTypeFontMetrics(void)
{
	CTrueTypeFont			cFont;
	STrueTypeGlyphMetrics	sMetrics;

	AssertTrue(LoadTrueTypeFont(&cFont, "LiberationSans-Regular.ttf"));
	AssertTrueTypeMetrics(1366, 4, 4, 0, 1362, 1409, &cFont, 36);
	AssertTrueTypeMetrics(569, 0, 0, 0, 0, 0, &cFont, 3);
	AssertTrueTypeMetrics(1139, 86, 86, -425, 1007, 1099, &cFont, 74);
	AssertTrueTypeMetrics(1366, 4, 4, 0, 1362, 1776, &cFont, 129);
	AssertTrueTypeMetrics(1139, 87, 87, -20, 1048, 1508, &cFont, 169);
	AssertFalse(cFont.GetGlyphMetrics(675, &sMetrics));
	AssertFalse(cFont.GetGlyphMetrics(-1, &sMetrics));
	cFont.Kill();

	AssertTrue(LoadTrueTypeFont(&cFont, "JetBrainsMonoNL-Regular.ttf"));
	AssertTrueTypeMetrics(600, 50, 50, 0, 550, 730, &cFont, 1);
	AssertTrueTypeMetrics(600, 0, 0, 0, 0, 0, &cFont, 888);
	AssertTrueTypeMetrics(600, 88, 88, -180, 507, 560, &cFont, 245);
	AssertTrueTypeMetrics(600, 50, 50, 0, 550, 950, &cFont, 2);
	cFont.Kill();

	AssertTrue(LoadTrueTypeFont(&cFont, "InterVariable.ttf"));
	AssertTrueTypeMetrics(1413, 52, 52, 0, 1361, 1490, &cFont, 2);
	AssertTrueTypeMetrics(576, 0, 0, 0, 0, 0, &cFont, 1777);
	AssertTrueTypeMetrics(1256, 104, 104, -442, 1098, 1132, &cFont, 658);
	AssertTrueTypeMetrics(2011, 230, 230, -29, 1781, 1514, &cFont, 1744);
	AssertTrueTypeMetrics(1194, 104, 104, -24, 1094, 1558, &cFont, 618);
	cFont.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTrueTypeFontOutline(void)
{
	CTrueTypeFont			cFont;
	CTrueTypeOutline		cOutline;
	STrueTypeGlyphMetrics	sMetrics;

	AssertTrue(LoadTrueTypeFont(&cFont, "LiberationSans-Regular.ttf"));
	cOutline.Init();

	AssertTrue(cFont.GetGlyphOutline(36, &cOutline));
	AssertSize(2, cOutline.NumContours());
	AssertSize(21, cOutline.NumPoints());
	AssertSize(0, cOutline.GetContourStart(0));
	AssertSize(cOutline.GetContourEnd(0) + 1, cOutline.GetContourStart(1));
	AssertSize(20, cOutline.GetContourEnd(1));
	cFont.GetGlyphMetrics(36, &sMetrics);
	AssertTrue(TrueTypeOutlineMatchesBounds(&cOutline, &sMetrics));

	//Space has no outline.
	cOutline.Clear();
	AssertTrue(cFont.GetGlyphOutline(3, &cOutline));
	AssertSize(0, cOutline.NumContours());
	AssertSize(0, cOutline.NumPoints());

	//A composite of A and an acute accent.
	cOutline.Clear();
	AssertTrue(cFont.GetGlyphOutline(129, &cOutline));
	AssertTrue(cOutline.NumContours() > 2);
	cFont.GetGlyphMetrics(129, &sMetrics);
	AssertTrue(TrueTypeOutlineMatchesBounds(&cOutline, &sMetrics));

	AssertFalse(cFont.GetGlyphOutline(675, &cOutline));
	AssertSize(0, cOutline.NumPoints());

	cOutline.Kill();
	cFont.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// Every glyph of every font reads, and its points match its bounding box.
//
//////////////////////////////////////////////////////////////////////////
void TestTrueTypeFontAllGlyphs(void)
{
	char*					aszFonts[] = {	"InterVariable.ttf", "InterVariable-Italic.ttf",
											"JetBrainsMonoNL-Bold.ttf", "JetBrainsMonoNL-BoldItalic.ttf", "JetBrainsMonoNL-Italic.ttf",
											"JetBrainsMonoNL-Light.ttf", "JetBrainsMonoNL-LightItalic.ttf", "JetBrainsMonoNL-Regular.ttf",
											"LiberationSans-Bold.ttf", "LiberationSans-BoldItalic.ttf", "LiberationSans-Italic.ttf", "LiberationSans-Regular.ttf" };
	int						iFont;
	CTrueTypeFont			cFont;
	CTrueTypeOutline		cOutline;
	STrueTypeGlyphMetrics	sMetrics;
	int						iGlyph;
	int						iFailedOutlines;
	int						iMismatchedBounds;

	cOutline.Init();
	for (iFont = 0; iFont < 12; iFont++)
	{
		AssertTrue(LoadTrueTypeFont(&cFont, aszFonts[iFont]));

		iFailedOutlines = 0;
		iMismatchedBounds = 0;
		for (iGlyph = 0; iGlyph < cFont.NumGlyphs(); iGlyph++)
		{
			cOutline.Clear();
			if (!cFont.GetGlyphOutline(iGlyph, &cOutline) || !cFont.GetGlyphMetrics(iGlyph, &sMetrics))
			{
				iFailedOutlines++;
			}
			else if (!TrueTypeOutlineMatchesBounds(&cOutline, &sMetrics))
			{
				iMismatchedBounds++;
			}
		}
		AssertInt(0, iFailedOutlines);
		AssertInt(0, iMismatchedBounds);

		cFont.Kill();
	}
	cOutline.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTrueTypeRasteriseGlyph(void)
{
	ObjectsInit();
	{
		CTrueTypeFont			cFont;
		CTrueTypeRasteriser		cRasteriser;
		Ptr<CImage>				pcImage;
		int						iLeft;
		int						iTop;
		CChars					sz;

		AssertTrue(LoadTrueTypeFont(&cFont, "LiberationSans-Regular.ttf"));
		cRasteriser.Init(&cFont, 16.0f);
		AssertFloat(16.0f / 2048.0f, cRasteriser.GetScale(), 6);

		pcImage = cRasteriser.RasteriseGlyph(cFont.GetGlyphIndex('A'), &iLeft, &iTop);
		AssertTrue(pcImage.IsNotNull());
		AssertInt(0, iLeft);
		AssertInt(-12, iTop);
		AssertInt(11, pcImage->GetWidth());
		AssertInt(12, pcImage->GetHeight());
		AssertSize(1, pcImage->NumChannels());
		AssertTrue(pcImage->HasChannel(IMAGE_OPACITY));
		sz.Init();
		TrueTypeImageToString(pcImage, &sz);
		AssertString(
			"    ..     \n"
			"    +#:    \n"
			"   .*+*    \n"
			"   +*.#.   \n"
			"  .*+ *+   \n"
			"  :*. :*.  \n"
			"  ++  .*:  \n"
			" .*+:::**  \n"
			" +******#. \n"
			".*+    .*+ \n"
			":#.     :*.\n"
			"**      .*:\n", sz.Text());
		sz.Kill();

		pcImage = cRasteriser.RasteriseGlyph(cFont.GetGlyphIndex('g'), &iLeft, &iTop);
		AssertTrue(pcImage.IsNotNull());
		AssertInt(0, iLeft);
		AssertInt(-9, iTop);
		sz.Init();
		TrueTypeImageToString(pcImage, &sz);
		AssertString(
			"  :+:..:\n"
			" :*++*+*\n"
			".*+  .**\n"
			".#.   **\n"
			":#.   +*\n"
			":#.   +*\n"
			".#:  .**\n"
			" **..+**\n"
			" .***:+*\n"
			"   .  ++\n"
			" ++. .*:\n"
			" .****+.\n"
			"  ..:.  \n", sz.Text());
		sz.Kill();

		pcImage = cRasteriser.RasteriseGlyph(cFont.GetGlyphIndex(' '), &iLeft, &iTop);
		AssertTrue(pcImage.IsNull());

		pcImage = NULL;
		cRasteriser.Kill();
		cFont.Kill();
	}
	ObjectsKill(false);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTrueTypeRasteriseText(void)
{
	ObjectsInit();
	{
		CTrueTypeFont			cFont;
		CTrueTypeRasteriser		cRasteriser;
		Ptr<CImage>				pcImage;
		int						iOriginX;
		int						iOriginY;
		CChars					sz;

		AssertTrue(LoadTrueTypeFont(&cFont, "JetBrainsMonoNL-Regular.ttf"));
		cRasteriser.Init(&cFont, 10.0f);
		AssertFloat(30.0f, cRasteriser.GetTextWidth("Hello"), 3);

		pcImage = cRasteriser.RasteriseText("Hi", &iOriginX, &iOriginY);
		AssertTrue(pcImage.IsNotNull());
		AssertInt(0, iOriginX);
		AssertInt(8, iOriginY);
		sz.Init();
		TrueTypeImageToString(pcImage, &sz);
		AssertString(
			".:  :.  :+  \n"
			".*  *.  .:  \n"
			".*  *. :+:  \n"
			".*..*. ::+  \n"
			".*++*.  .+  \n"
			".*  *.  .+  \n"
			".*  *.  .+  \n"
			".*  *..****:\n", sz.Text());
		sz.Kill();

		pcImage = cRasteriser.RasteriseText("   ", &iOriginX, &iOriginY);
		AssertTrue(pcImage.IsNull());

		pcImage = NULL;
		cRasteriser.Kill();
		cFont.Kill();
	}
	ObjectsKill(false);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTrueTypeDrawText(void)
{
	char		szDirectory[] = "Output" _FS_ "TrueType";
	CFileUtil	cFileUtil;

	AssertTrue(cFileUtil.RemoveDir(szDirectory));
	AssertTrue(cFileUtil.TouchDir(szDirectory));

	ObjectsInit();
	{
		char*					aszFonts[] = { "LiberationSans-Regular.ttf", "LiberationSans-Bold.ttf", "LiberationSans-Italic.ttf", "LiberationSans-BoldItalic.ttf",
												"JetBrainsMonoNL-Light.ttf", "JetBrainsMonoNL-Regular.ttf", "JetBrainsMonoNL-Bold.ttf", "JetBrainsMonoNL-LightItalic.ttf",
												"InterVariable.ttf", "InterVariable-Italic.ttf" };
		float32					afSizes[] = { 11.0f, 16.0f, 24.0f, 40.0f };
		//Colour channels as bytes; fractions like 9 / 10.0f land on half a byte and round either way under /fp:fast.
		int						aiReds[] = { 0, 26, 51, 77, 102, 128, 153, 178, 204, 229 };
		int						aiBlues[] = { 0, 43, 85, 128 };
		CTrueTypeFont			cFont;
		CTrueTypeRasteriser		cRasteriser;
		Ptr<CImage>				pcImage;
		CImageColourRGB			cColour;
		int						iFont;
		int						iSize;
		float32					fY;
		CChars					szOutputFilename;
		CChars					szInputFilename;

		pcImage = OMalloc<CImage>(640, 1280, PT_uint8, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, CHANNEL_STOP);
		pcImage->White();

		fY = 40.0f;
		for (iFont = 0; iFont < 10; iFont++)
		{
			AssertTrue(LoadTrueTypeFont(&cFont, aszFonts[iFont]));
			for (iSize = 0; iSize < 4; iSize++)
			{
				cRasteriser.Init(&cFont, afSizes[iSize]);
				fY += cRasteriser.GetAscent();
				cColour.Init(aiReds[iFont] / 255.0f, 0.0f, aiBlues[iSize] / 255.0f);
				AssertTrue(cRasteriser.DrawText(pcImage, 4.25f, fY, "Sphinx of black quartz, judge my vow! \xC3\x81\xC3\xA9 0123 %&@", &cColour));
				fY += cRasteriser.GetDescent();
				cRasteriser.Kill();
			}
			cFont.Kill();
		}

		//Clipped at every edge.
		AssertTrue(LoadTrueTypeFont(&cFont, "LiberationSans-Bold.ttf"));
		cRasteriser.Init(&cFont, 64.0f);
		cColour.Init(0.0f, 0.6f, 0.0f);
		AssertTrue(cRasteriser.DrawText(pcImage, 300.0f, 20.0f, "Clipped", &cColour));
		AssertTrue(cRasteriser.DrawText(pcImage, -20.5f, 1200.0f, "Clipped", &cColour));
		AssertTrue(cRasteriser.DrawText(pcImage, 500.0f, 1290.0f, "Clipped", &cColour));
		AssertTrue(cRasteriser.DrawText(pcImage, 5000.0f, 100.0f, "Outside", &cColour));
		cRasteriser.Kill();
		cFont.Kill();

		szOutputFilename.Init(szDirectory);
		cFileUtil.AppendToPath(&szOutputFilename, "DrawText.png");
		AssertTrue(WriteImage(pcImage, szOutputFilename.Text()));
		pcImage = NULL;


		szInputFilename.Init(szOutputFilename);
		szInputFilename.Replace("Output", "Input");
		AssertFile(szInputFilename, szOutputFilename);

		szOutputFilename.Kill();
		szInputFilename.Kill();
	}
	ObjectsFlush();
	ObjectsKill(false);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTrueTypeFont(void)
{
	BeginTests();

	DataIOInit();

	TestTrueTypeFontLoad();
	TestTrueTypeFontGlyphIndex();
	TestTrueTypeFontMetrics();
	TestTrueTypeFontOutline();
	TestTrueTypeFontAllGlyphs();
	TestTrueTypeRasteriseGlyph();
	TestTrueTypeRasteriseText();
	TestTrueTypeDrawText();

	DataIOKill();

	TestStatistics();
}
