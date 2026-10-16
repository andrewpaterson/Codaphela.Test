#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/Logger.h"
#include "StandardLib/Objects.h"
#include "SupportLib/Image.h"
#include "SupportLib/ImageReader.h"
#include "SupportLib/ImageWriter.h"
#include "TestLib/Assert.h"
#include "AssertImage.h"


//////////////////////////////////////////////////////////////////////////
//
// Input/PNG/szName-expected.png has the same pixels as Input/PNG/szName.png
// but is not interlaced, uses no filters and has palettes expanded.
//
//////////////////////////////////////////////////////////////////////////
void AssertPNGMatchesExpected(const char* szName)
{
	CChars	szPNG;
	CChars	szExpected;

	szPNG.Init("Input" _FS_ "PNG" _FS_);
	szPNG.Append(szName);
	szPNG.Append(".png");
	szExpected.Init("Input" _FS_ "PNG" _FS_);
	szExpected.Append(szName);
	szExpected.Append("-expected.png");

	Ptr<CImage> pcPNG = ReadImage(szPNG.Text());
	Ptr<CImage> pcExpected = ReadImage(szExpected.Text());
	AssertTrue(pcPNG.IsNotNull());
	AssertSameImage(pcExpected, pcPNG);

	pcPNG = NULL;
	pcExpected = NULL;
	szExpected.Kill();
	szPNG.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImagePNGInterlaced(void)
{
	AssertPNGMatchesExpected("interlacedgrey1");
	AssertPNGMatchesExpected("interlacedgrey2");
	AssertPNGMatchesExpected("interlacedgrey4");
	AssertPNGMatchesExpected("interlacedgrey8");
	AssertPNGMatchesExpected("interlacedgrey16");
	AssertPNGMatchesExpected("interlacedrgb8");
	AssertPNGMatchesExpected("interlacedrgb16");
	AssertPNGMatchesExpected("interlacedgreyalpha8");
	AssertPNGMatchesExpected("interlacedrgba8");
	AssertPNGMatchesExpected("interlacedrgba16");
	AssertPNGMatchesExpected("interlaced1x1");
	AssertPNGMatchesExpected("interlaced3x2");
	AssertPNGMatchesExpected("paletteinterlaced");
}


//////////////////////////////////////////////////////////////////////////
//
// The rows cycle through all five filter types.
//
//////////////////////////////////////////////////////////////////////////
void TestImagePNGFilters(void)
{
	AssertPNGMatchesExpected("filtersgrey2");
	AssertPNGMatchesExpected("filtersgrey8");
	AssertPNGMatchesExpected("filtersgrey16");
	AssertPNGMatchesExpected("filtersrgb8");
	AssertPNGMatchesExpected("filtersrgba16");
	AssertPNGMatchesExpected("filtersgreyalpha16");
}


//////////////////////////////////////////////////////////////////////////
//
// Palettes that are all grey are read as grey, tRNS alpha as opacity.
//
//////////////////////////////////////////////////////////////////////////
void TestImagePNGPalettes(void)
{
	CArrayChannel	acChannels;

	AssertPNGMatchesExpected("palette1");
	AssertPNGMatchesExpected("palette2");
	AssertPNGMatchesExpected("palette4");
	AssertPNGMatchesExpected("palette8");
	AssertPNGMatchesExpected("palettetrns");
	AssertPNGMatchesExpected("paletteshorttrns");
	AssertPNGMatchesExpected("paletteopaquetrns");
	AssertPNGMatchesExpected("palettegrey");
	AssertPNGMatchesExpected("palettegreytrns");
	AssertPNGMatchesExpected("paletteindexpastend");

	Ptr<CImage> pcImage = ReadImage("Input" _FS_ "PNG" _FS_ "palettetrns.png");
	acChannels.Init();
	pcImage->GetAllChannels(&acChannels);
	AssertInt(4, acChannels.NumElements());
	AssertChannel(IP_Opacity, CT_Intensity, PT_uint8, acChannels.Get(0));
	AssertChannel(IP_Diffuse, CT_Red, PT_uint8, acChannels.Get(1));
	AssertChannel(IP_Diffuse, CT_Green, PT_uint8, acChannels.Get(2));
	AssertChannel(IP_Diffuse, CT_Blue, PT_uint8, acChannels.Get(3));
	acChannels.Kill();

	pcImage = ReadImage("Input" _FS_ "PNG" _FS_ "palettegrey.png");
	acChannels.Init();
	pcImage->GetAllChannels(&acChannels);
	AssertInt(1, acChannels.NumElements());
	AssertChannel(IP_Diffuse, CT_Intensity, PT_uint8, acChannels.Get(0));
	acChannels.Kill();
	pcImage = NULL;
}


//////////////////////////////////////////////////////////////////////////
//
// Image data split over many (some empty) IDAT chunks, ancillary chunks
// that are skipped, and tRNS on an RGB image, which isn't used.
//
//////////////////////////////////////////////////////////////////////////
void TestImagePNGChunks(void)
{
	AssertPNGMatchesExpected("splitidat");
	AssertPNGMatchesExpected("ancillary");
	AssertPNGMatchesExpected("rgbtrns");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertPNGRejected(const char* szName)
{
	CChars	szPNG;

	szPNG.Init("Input" _FS_ "PNG" _FS_ "Bad" _FS_);
	szPNG.Append(szName);

	Ptr<CImage> pcImage = ReadImage(szPNG.Text());
	AssertTrue(pcImage.IsNull());

	pcImage = NULL;
	szPNG.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// Malformed PNGs must be rejected without reading past the file.
//
//////////////////////////////////////////////////////////////////////////
void TestImagePNGBadFiles(void)
{
	SLogConfig	sLogConfig;

	sLogConfig = gcLogger.SetSilent();
	AssertPNGRejected("badsignature.png");
	AssertPNGRejected("badcrc.png");
	AssertPNGRejected("truncated.png");
	AssertPNGRejected("headeronly.png");
	AssertPNGRejected("noidat.png");
	AssertPNGRejected("noiend.png");
	AssertPNGRejected("ihdrnotfirst.png");
	AssertPNGRejected("unknowncritical.png");
	AssertPNGRejected("badrgbdepth.png");
	AssertPNGRejected("badcolourtype.png");
	AssertPNGRejected("badcompression.png");
	AssertPNGRejected("badinterlace.png");
	AssertPNGRejected("zerowidth.png");
	AssertPNGRejected("hugeimage.png");
	AssertPNGRejected("nopalette.png");
	AssertPNGRejected("trnsbeforeplte.png");
	AssertPNGRejected("badfilter.png");
	AssertPNGRejected("toolittledata.png");
	AssertPNGRejected("toomuchdata.png");
	AssertPNGRejected("badzlib.png");
	gcLogger.SetConfig(&sLogConfig);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImagePNG(void)
{
	BeginTests();

	DataIOInit();
	ObjectsInit();

	TestImagePNGInterlaced();
	TestImagePNGFilters();
	TestImagePNGPalettes();
	TestImagePNGChunks();
	TestImagePNGBadFiles();

	ObjectsKill(false);
	DataIOKill();

	TestStatistics();
}
