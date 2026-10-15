#include "BaseLib/GlobalDataTypesIO.h"
#include "StandardLib/Objects.h"
#include "SupportLib/Image.h"
#include "SupportLib/ImageReader.h"
#include "SupportLib/ImageWriter.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
// Compares channel by channel so images with the same channels in a
// different order (LoadPNG puts opacity first) are the same.
//
//////////////////////////////////////////////////////////////////////////
void AssertSameImage(Ptr<CImage> pcExpected, Ptr<CImage> pcActual)
{
	CArraySize		aiExpectedChannels;
	CArraySize		aiActualChannels;
	size			i;
	size			uiChannel;
	CChannel*		pcExpectedChannel;
	CChannel*		pcActualChannel;
	int				iNumPixels;
	size			uiExpectedStride;
	size			uiActualStride;
	uint8*			puiExpected;
	uint8*			puiActual;
	int				iPixel;
	int				iMismatches;

	AssertTrue(pcExpected.IsNotNull());
	AssertTrue(pcActual.IsNotNull());
	if (pcExpected.IsNull() || pcActual.IsNull())
	{
		return;
	}

	AssertInt(pcExpected->GetWidth(), pcActual->GetWidth());
	AssertInt(pcExpected->GetHeight(), pcActual->GetHeight());
	if ((pcExpected->GetWidth() != pcActual->GetWidth()) || (pcExpected->GetHeight() != pcActual->GetHeight()))
	{
		return;
	}

	aiExpectedChannels.Init();
	aiActualChannels.Init();
	pcExpected->GetAllChannels(&aiExpectedChannels);
	pcActual->GetAllChannels(&aiActualChannels);
	AssertSize(aiExpectedChannels.NumElements(), aiActualChannels.NumElements());

	iNumPixels = pcExpected->GetWidth() * pcExpected->GetHeight();
	uiExpectedStride = pcExpected->GetByteSize() / iNumPixels;
	uiActualStride = pcActual->GetByteSize() / iNumPixels;
	puiExpected = (uint8*)pcExpected->GetData();
	puiActual = (uint8*)pcActual->GetData();
	iMismatches = 0;
	for (i = 0; i < aiExpectedChannels.NumElements(); i++)
	{
		uiChannel = aiExpectedChannels.GetValue(i);
		pcExpectedChannel = pcExpected->GetChannel(uiChannel);
		pcActualChannel = pcActual->GetChannel(uiChannel);
		AssertNotNull(pcActualChannel);
		if (pcActualChannel == NULL)
		{
			continue;
		}
		AssertInt((int)pcExpectedChannel->eType, (int)pcActualChannel->eType);
		if (pcExpectedChannel->eType != pcActualChannel->eType)
		{
			continue;
		}
		for (iPixel = 0; iPixel < iNumPixels; iPixel++)
		{
			if (memcmp(&puiExpected[iPixel * uiExpectedStride + pcExpectedChannel->miByteOffset], &puiActual[iPixel * uiActualStride + pcActualChannel->miByteOffset], pcExpectedChannel->miByteSize) != 0)
			{
				iMismatches++;
			}
		}
	}
	AssertInt(0, iMismatches);

	aiExpectedChannels.Kill();
	aiActualChannels.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// Input/BMP/szName.png was decoded from Input/BMP/szName.bmp by another
// library (PIL).
//
//////////////////////////////////////////////////////////////////////////
void AssertBMPMatchesPNG(const char* szName)
{
	CChars	szBMP;
	CChars	szPNG;

	szBMP.Init("Input" _FS_ "BMP" _FS_);
	szBMP.Append(szName);
	szBMP.Append(".bmp");
	szPNG.Init("Input" _FS_ "BMP" _FS_);
	szPNG.Append(szName);
	szPNG.Append(".png");

	Ptr<CImage> pcBMP = ReadImage(szBMP.Text());
	Ptr<CImage> pcPNG = ReadImage(szPNG.Text());
	AssertSameImage(pcPNG, pcBMP);

	pcBMP = NULL;
	pcPNG = NULL;
	szPNG.Kill();
	szBMP.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageBMPReader(void)
{
	AssertBMPMatchesPNG("pal1");
	AssertBMPMatchesPNG("grey1");
	AssertBMPMatchesPNG("pal4");
	AssertBMPMatchesPNG("pal8");
	AssertBMPMatchesPNG("grey8");
	AssertBMPMatchesPNG("rle4");
	AssertBMPMatchesPNG("rle8");
	AssertBMPMatchesPNG("os2pal8");
	AssertBMPMatchesPNG("os2rgb24");
	AssertBMPMatchesPNG("rgb555");
	AssertBMPMatchesPNG("rgb565");
	AssertBMPMatchesPNG("rgb24");
	AssertBMPMatchesPNG("rgb24topdown");
	AssertBMPMatchesPNG("rgb32");
	AssertBMPMatchesPNG("rgba32v4");
	AssertBMPMatchesPNG("rgba32v5");
}


//////////////////////////////////////////////////////////////////////////
//
// Reads the PNG szSource, writes it to Output/szDest and reads that back.
//
//////////////////////////////////////////////////////////////////////////
void AssertBMPRoundTrip(const char* szSource, const char* szDest)
{
	CChars	szOutput;
	bool	bResult;

	szOutput.Init("Output" _FS_);
	szOutput.Append(szDest);

	Ptr<CImage> pcImage = ReadImage((char*)szSource);
	AssertTrue(pcImage.IsNotNull());
	bResult = WriteImage(pcImage, szOutput.Text());
	AssertTrue(bResult);
	Ptr<CImage> pcComp = ReadImage(szOutput.Text());
	AssertSameImage(pcImage, pcComp);

	pcImage = NULL;
	pcComp = NULL;
	szOutput.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// Bitmaps have no grey with alpha format so grey with alpha is written as
// RGBA with the grey copied into red, green and blue.
//
//////////////////////////////////////////////////////////////////////////
void TestImageBMPWriterGreyAlpha(void)
{
	bool		bResult;
	uint8*		puiSource;
	uint8*		puiDest;
	size		uiSourceStride;
	size		uiDestStride;
	size		uiGrey;
	size		uiOpacity;
	size		uiRed;
	size		uiGreen;
	size		uiBlue;
	size		uiAlpha;
	int			iNumPixels;
	int			i;
	int			iMismatches;

	Ptr<CImage> pcImage = ReadImage("Input" _FS_ "basn4a08.png");
	AssertTrue(pcImage->HasChannels(IMAGE_DIFFUSE_GREY, IMAGE_OPACITY, CHANNEL_STOP));
	bResult = WriteImage(pcImage, "Output" _FS_ "basn4a08.bmp");
	AssertTrue(bResult);
	Ptr<CImage> pcComp = ReadImage("Output" _FS_ "basn4a08.bmp");
	AssertTrue(pcComp->HasChannels(IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, IMAGE_OPACITY, CHANNEL_STOP));
	AssertInt(pcImage->GetWidth(), pcComp->GetWidth());
	AssertInt(pcImage->GetHeight(), pcComp->GetHeight());

	iNumPixels = pcImage->GetWidth() * pcImage->GetHeight();
	uiSourceStride = pcImage->GetByteSize() / iNumPixels;
	uiDestStride = pcComp->GetByteSize() / iNumPixels;
	uiGrey = pcImage->GetChannel(IMAGE_DIFFUSE_GREY)->miByteOffset;
	uiOpacity = pcImage->GetChannel(IMAGE_OPACITY)->miByteOffset;
	uiRed = pcComp->GetChannel(IMAGE_DIFFUSE_RED)->miByteOffset;
	uiGreen = pcComp->GetChannel(IMAGE_DIFFUSE_GREEN)->miByteOffset;
	uiBlue = pcComp->GetChannel(IMAGE_DIFFUSE_BLUE)->miByteOffset;
	uiAlpha = pcComp->GetChannel(IMAGE_OPACITY)->miByteOffset;

	puiSource = (uint8*)pcImage->GetData();
	puiDest = (uint8*)pcComp->GetData();
	iMismatches = 0;
	for (i = 0; i < iNumPixels; i++)
	{
		if ((puiDest[i * uiDestStride + uiRed] != puiSource[i * uiSourceStride + uiGrey]) ||
			(puiDest[i * uiDestStride + uiGreen] != puiSource[i * uiSourceStride + uiGrey]) ||
			(puiDest[i * uiDestStride + uiBlue] != puiSource[i * uiSourceStride + uiGrey]) ||
			(puiDest[i * uiDestStride + uiAlpha] != puiSource[i * uiSourceStride + uiOpacity]))
		{
			iMismatches++;
		}
	}
	AssertInt(0, iMismatches);

	pcImage = NULL;
	pcComp = NULL;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageBMPWriter(void)
{
	AssertBMPRoundTrip("Input" _FS_ "BMP" _FS_ "rgb24.png", "rgb24.bmp");
	AssertBMPRoundTrip("Input" _FS_ "BMP" _FS_ "rgba32v4.png", "rgba32.bmp");
	AssertBMPRoundTrip("Input" _FS_ "BMP" _FS_ "grey8.png", "grey8.bmp");
	AssertBMPRoundTrip("Input" _FS_ "basn2c08.png", "basn2c08.bmp");
	AssertBMPRoundTrip("Input" _FS_ "basn6a08.png", "basn6a08.bmp");
	AssertBMPRoundTrip("Input" _FS_ "basn0g08.png", "basn0g08.bmp");
	TestImageBMPWriterGreyAlpha();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageBMP(void)
{
	BeginTests();

	DataIOInit();
	ObjectsInit();

	TestImageBMPReader();
	TestImageBMPWriter();

	ObjectsKill(false);
	DataIOKill();

	TestStatistics();
}
