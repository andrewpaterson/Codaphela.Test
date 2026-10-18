#include "BaseLib/FastFunctions.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "StandardLib/Objects.h"
#include "StandardLib/ArrayObject.h"
#include "SupportLib/ImageReader.h"
#include "SupportLib/ImageWriter.h"
#include "SupportLib/ImageDraw.h"
#include "SupportLib/ImageCel.h"
#include "SupportLib/ImageCelBlitterCache.h"
#include "SupportLib/ImageBlitterContext.h"
#include "BaseLib/Logger.h"
#include "TestLib/Assert.h"
#include "TestLib/AssertFile.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageDrawBox1(void)
{
	CImageDraw			cDraw;
	Ptr<CImage>			pImage = OMalloc<CImage>(32, 32);
	CImageColourRGB		cColour;

	pImage->Black();

	cDraw.Init(&pImage);

	cColour.Init(0, 0, 0);
	cDraw.SetColour(&cColour);
	cColour.Kill();
	cDraw.DrawBox(0, 0, 31, 31, true);

	cColour.Init(1, 1, 1);
	cDraw.SetColour(&cColour);
	cColour.Kill();
	cDraw.DrawBox(0, 0, 31, 31, false);

	cDraw.Kill();
	WriteImage(pImage, "Output" _FS_ "DrawBox1.raw");
	WriteImage(pImage, "Output" _FS_ "DrawBox1.png");
	AssertFileMemory("Input" _FS_ "DrawBox1.raw", pImage->GetData(), pImage->GetByteSize());

	pImage = NULL;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageDrawBox2(void)
{
	CImageDraw			cDraw;
	Ptr<CImage>			pImage = OMalloc<CImage>(32, 32);
	CImageColourRGB		cColour;
	size				i;

	pImage->Black();

	cDraw.Init(&pImage);

	for (i = 0; i < 6; i++)
	{
		cColour.Init(1.0f, 0.7f + (i / 20.0f) * 1.05263162f, 0.4f + (i / 10.0f) * 1.11111116f);
		cDraw.SetColour(&cColour);
		cDraw.DrawBox(8 + i, 10 + i, 23 - i, 21 - i, false);
		cColour.Kill();
	}

	cDraw.Kill();
	WriteImage(pImage, "Output" _FS_ "DrawBox2.raw");
	WriteImage(pImage, "Output" _FS_ "DrawBox2.png");
	AssertFileMemory("Input" _FS_ "DrawBox2.raw", pImage->GetData(), pImage->GetByteSize());

	pImage = NULL;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageDrawLine(void)
{
	CImageDraw			cDraw;
	Ptr<CImage>			pImage = OMalloc<CImage>(64, 32);
	CImageColourRGB		cColour;

	pImage->Black();

	cDraw.Init(&pImage);
	cColour.Init(1.0f, 1, 1);
	cDraw.SetColour(&cColour);

	cDraw.DrawLine(0, 0, 63, 31);
	cDraw.DrawLine(0, 0, 63, 16);
	cDraw.DrawLine(0, 0, 31, 31);
	cDraw.DrawLine(0, 0, 63, 0);
	cDraw.DrawLine(0, 0, 0, 31);

	WriteImage(pImage, "Output" _FS_ "DrawLine1.raw");
	WriteImage(pImage, "Output" _FS_ "DrawLine1.png");
	AssertFileMemory("Input" _FS_ "DrawLine1.raw", pImage->GetData(), pImage->GetByteSize());

	pImage->Black();

	cColour.Init(0.4f, 0.9f, 0.4f);
	cDraw.SetColour(&cColour);

	cDraw.DrawLine(63, 31, 0, 0);
	cDraw.DrawLine(63, 16, 0, 0);
	cDraw.DrawLine(31, 31, 0, 0);
	cDraw.DrawLine(63, 0 , 0, 0);
	cDraw.DrawLine(0, 31 , 0, 0);

	WriteImage(pImage, "Output" _FS_ "DrawLine2.raw");
	WriteImage(pImage, "Output" _FS_ "DrawLine2.png");
	AssertFileMemory("Input" _FS_ "DrawLine2.raw", pImage->GetData(), pImage->GetByteSize());

	pImage->Black();

	cColour.Init(0.4f, 0.4f, 0.99f);
	cDraw.SetColour(&cColour);

	cDraw.DrawLine(63, 0, 0, 31);
	cDraw.DrawLine(63, 0, 0, 16);
	cDraw.DrawLine(31, 0, 0, 31);
	cDraw.DrawLine(63, 0, 0, 0);
	cDraw.DrawLine(0, 0, 0, 31);

	WriteImage(pImage, "Output" _FS_ "DrawLine3.raw");
	WriteImage(pImage, "Output" _FS_ "DrawLine3.png");
	AssertFileMemory("Input" _FS_ "DrawLine3.raw", pImage->GetData(), pImage->GetByteSize());

	cDraw.Kill();
	cColour.Kill();
	pImage = NULL;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageDrawLineExtents(void)
{
	CImageDraw			cDraw;
	Ptr<CImage>			pImage = OMalloc<CImage>(16, 16);
	CImageColourRGB		cColour1;
	CImageColourRGB		cColour2;
	int32				x;
	int32				y;

	pImage->Black();

	cDraw.Init(&pImage);
	cColour1.Init(1.0f, 0.1f, 0.1f);
	cColour2.Init(0.1f, 0.1f, 1.0f);

	for (x = 0; x < 16; x += 2)
	{
		cDraw.SetColour(&cColour1);
		cDraw.DrawLine(x, 0, x, 1);
		cDraw.SetColour(&cColour2);
		cDraw.DrawVerticalLine(x+1, 0, 1);
	}

	WriteImage(pImage, "Output" _FS_ "DrawLine4.raw");
	WriteImage(pImage, "Output" _FS_ "DrawLine4.png");
	AssertFileMemory("Input" _FS_ "DrawLine4.raw", pImage->GetData(), pImage->GetByteSize());

	pImage->Black();

	for (y = 0; y < 16; y += 2)
	{
		cDraw.SetColour(&cColour1);
		cDraw.DrawLine(15, y, 16, y);
		cDraw.SetColour(&cColour2);
		cDraw.DrawHorizontalLine(15, 16, y + 1);
	}

	WriteImage(pImage, "Output" _FS_ "DrawLine5.raw");
	WriteImage(pImage, "Output" _FS_ "DrawLine5.png");
	AssertFileMemory("Input" _FS_ "DrawLine5.raw", pImage->GetData(), pImage->GetByteSize());

	cDraw.Kill();
	cColour1.Kill();
	cColour2.Kill();
	pImage = NULL;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
Ptr<CImage> CreateDrawCelImage(int32 iWidth, int32 iHeight, EColourFormat eFormat, ERGBAlphaBits eAlphaBits, size uiStride, bool bGaps)
{
	Ptr<CImage>		pImage;
	uint8*			puiData;
	int32			x;
	int32			y;
	size			uiPixel;

	//Every pixel is different so a pixel drawn in the wrong place is always noticed.
	//With gaps the fourth byte is opacity in runs of two opaque and two transparent pixels that shift on each row.
	pImage = OMalloc<CImage>(iWidth, iHeight, eFormat, CCO_RGB, CRGB_24bit, eAlphaBits);
	puiData = (uint8*)pImage->GetData();
	for (y = 0; y < iHeight; y++)
	{
		for (x = 0; x < iWidth; x++)
		{
			uiPixel = (x + y * iWidth) * uiStride;
			puiData[uiPixel + 0] = (uint8)(10 + x * 30);
			puiData[uiPixel + 1] = (uint8)(20 + y * 40);
			puiData[uiPixel + 2] = 200;
			if (uiStride == 4)
			{
				puiData[uiPixel + 3] = bGaps ? ((((x + y) / 2) % 2 == 0) ? 255 : 0) : 77;
			}
		}
	}
	return pImage;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
Ptr<CImage> CreateDrawCelSourceImage(int32 iWidth, int32 iHeight)
{
	return CreateDrawCelImage(iWidth, iHeight, CFT_RGB, ARGB_None, 3, false);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertDrawCelPixels(Ptr<CImage> pDest, size uiDestStride, Ptr<CImage> pSource, size uiSourceStride, bool bSourceGaps, int32 iDestX, int32 iDestY, CRectangle* pcClip)
{
	uint8*	puiDest;
	uint8*	puiSource;
	int32	x;
	int32	y;
	int32	xs;
	int32	ys;
	bool	bDrawn;
	size	uiDest;
	size	uiSource;
	size	uiWrong;

	//A destination pixel must hold the source pixel over it if it is inside the clip and opaque, otherwise it must still be black.
	//Only the colour bytes are compared.
	puiDest = (uint8*)pDest->GetData();
	puiSource = (uint8*)pSource->GetData();
	uiWrong = 0;
	for (y = 0; y < pDest->GetHeight(); y++)
	{
		for (x = 0; x < pDest->GetWidth(); x++)
		{
			xs = x - iDestX;
			ys = y - iDestY;
			uiSource = 0;
			bDrawn = (xs >= 0) && (xs < pSource->GetWidth()) && (ys >= 0) && (ys < pSource->GetHeight());
			bDrawn &= (pcClip == NULL) || ((x >= pcClip->msTopLeft.x) && (x < pcClip->msBottomRight.x) && (y >= pcClip->msTopLeft.y) && (y < pcClip->msBottomRight.y));
			if (bDrawn)
			{
				uiSource = (xs + ys * pSource->GetWidth()) * uiSourceStride;
				if (bSourceGaps)
				{
					bDrawn = puiSource[uiSource + 3] == 255;
				}
			}

			uiDest = (x + y * pDest->GetWidth()) * uiDestStride;
			if (bDrawn)
			{
				if ((puiDest[uiDest] != puiSource[uiSource]) || (puiDest[uiDest + 1] != puiSource[uiSource + 1]) || (puiDest[uiDest + 2] != puiSource[uiSource + 2]))
				{
					uiWrong++;
				}
			}
			else
			{
				if ((puiDest[uiDest] != 0) || (puiDest[uiDest + 1] != 0) || (puiDest[uiDest + 2] != 0))
				{
					uiWrong++;
				}
			}
		}
	}
	AssertSize(0, uiWrong);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertDrawCel(Ptr<CImage> pDest, Ptr<CImage> pSource, int32 iDestX, int32 iDestY, CRectangle* pcClip)
{
	AssertDrawCelPixels(pDest, 3, pSource, 3, false, iDestX, iDestY, pcClip);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageDrawCelClipping(void)
{
	CImageDraw		cDraw;
	Ptr<CImage>		pSource;
	Ptr<CImage>		pDest;
	Ptr<CImageCel>	pCel;
	CRectangle		cClip;
	int32			aiPositions[10][2] = { { 2, 2 }, { -2, -1 }, { 7, 5 }, { -3, 5 }, { 7, -2 }, { -6, 0 }, { 10, 3 }, { 0, -4 }, { 4, 8 }, { -20, -20 } };
	size			i;

	//The source is 6x4 and the destination 10x8 so the cel can hang off every edge and corner and fall right outside.
	pSource = CreateDrawCelSourceImage(6, 4);
	pCel = OMalloc<CImageCel>(pSource);
	pDest = OMalloc<CImage>(10, 8, CFT_RGB, CCO_RGB, CRGB_24bit, ARGB_None);

	cDraw.Init(&pDest);
	for (i = 0; i < 10; i++)
	{
		pDest->Black();
		AssertTrue(cDraw.DrawCel(aiPositions[i][0], aiPositions[i][1], pCel));
		AssertDrawCel(pDest, pSource, aiPositions[i][0], aiPositions[i][1], NULL);
	}

	//A clip rectangle limits drawing further still.  Its right and bottom are exclusive.
	cClip.Init(3, 2, 7, 5);
	for (i = 0; i < 10; i++)
	{
		pDest->Black();
		AssertTrue(cDraw.DrawCel(aiPositions[i][0], aiPositions[i][1], pCel, &cClip));
		AssertDrawCel(pDest, pSource, aiPositions[i][0], aiPositions[i][1], &cClip);
	}

	//A clip rectangle partly outside the destination is limited to the destination.
	cClip.Init(-5, 6, 4, 20);
	pDest->Black();
	AssertTrue(cDraw.DrawCel(-1, 5, pCel, &cClip));
	AssertDrawCel(pDest, pSource, -1, 5, &cClip);

	//An empty clip rectangle draws nothing.
	cClip.Init(4, 4, 4, 6);
	pDest->Black();
	AssertTrue(cDraw.DrawCel(2, 2, pCel, &cClip));
	AssertDrawCel(pDest, pSource, 2, 2, &cClip);

	cDraw.Kill();
	pCel = NULL;
	pSource = NULL;
	pDest = NULL;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageDrawCelMismatchedFormat(void)
{
	CImageDraw		cDraw;
	Ptr<CImage>		pSource;
	Ptr<CImage>		pDest;
	Ptr<CImageCel>	pCel;
	SLogConfig		sLogConfig;
	bool			bResult;

	//A cel can only be drawn onto an image with the same colour order and colour bits.
	pSource = CreateDrawCelSourceImage(6, 4);
	pCel = OMalloc<CImageCel>(pSource);
	pDest = OMalloc<CImage>(10, 8, CFT_RGB, CCO_BGR, CRGB_24bit, ARGB_None);
	pDest->Black();

	cDraw.Init(&pDest);
	sLogConfig = gcLogger.SetSilent();
	bResult = cDraw.DrawCel(2, 2, pCel);
	gcLogger.SetConfig(&sLogConfig);
	AssertFalse(bResult);
	AssertDrawCel(pDest, pSource, 100, 100, NULL);

	cDraw.Kill();
	pCel = NULL;
	pSource = NULL;
	pDest = NULL;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageDrawCelClippingTransparentGaps(void)
{
	CImageDraw		cDraw;
	Ptr<CImage>		pSource;
	Ptr<CImage>		pDest;
	Ptr<CImageCel>	pCel;
	CRectangle		acClips[4];
	int32			aiPositions[6][2] = { { 0, 0 }, { 2, 3 }, { -3, 1 }, { 4, -1 }, { 6, 6 }, { -1, -1 } };
	size			i;
	size			j;

	//A cel with transparent gaps is blitted as several segments per row.  The narrow clips leave
	//some segments of a row wholly outside the clip while others in the same row are drawn.
	pSource = CreateDrawCelImage(9, 3, CFT_RGBA, ARGB_8bit, 4, true);
	pCel = OMalloc<CImageCel>(pSource);
	pDest = OMalloc<CImage>(10, 8, CFT_RGB, CCO_RGB, CRGB_24bit, ARGB_None);

	acClips[0].Init(3, 0, 6, 8);
	acClips[1].Init(5, 0, 6, 8);
	acClips[2].Init(0, 1, 10, 2);
	acClips[3].Init(2, 2, 9, 7);

	cDraw.Init(&pDest);
	for (i = 0; i < 6; i++)
	{
		pDest->Black();
		AssertTrue(cDraw.DrawCel(aiPositions[i][0], aiPositions[i][1], pCel));
		AssertDrawCelPixels(pDest, 3, pSource, 4, true, aiPositions[i][0], aiPositions[i][1], NULL);

		for (j = 0; j < 4; j++)
		{
			pDest->Black();
			AssertTrue(cDraw.DrawCel(aiPositions[i][0], aiPositions[i][1], pCel, &acClips[j]));
			AssertDrawCelPixels(pDest, 3, pSource, 4, true, aiPositions[i][0], aiPositions[i][1], &acClips[j]);
		}
	}

	cDraw.Kill();
	pCel = NULL;
	pSource = NULL;
	pDest = NULL;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageDrawCelRGBX(void)
{
	CImageDraw		cDraw;
	Ptr<CImage>		pSource;
	Ptr<CImage>		pDest;
	Ptr<CImageCel>	pCel;
	CRectangle		cClip;

	//RGBX has alpha bits for its ignored channel but no opacity channel and must still be drawable.
	pSource = CreateDrawCelImage(6, 4, CFT_RGBX, ARGB_8bit, 4, false);
	pCel = OMalloc<CImageCel>(pSource);
	pDest = OMalloc<CImage>(10, 8, CFT_RGBX, CCO_RGB, CRGB_24bit, ARGB_8bit);

	cDraw.Init(&pDest);

	pDest->Black();
	AssertTrue(cDraw.DrawCel(2, 1, pCel));
	AssertDrawCelPixels(pDest, 4, pSource, 4, false, 2, 1, NULL);

	pDest->Black();
	AssertTrue(cDraw.DrawCel(-2, 5, pCel));
	AssertDrawCelPixels(pDest, 4, pSource, 4, false, -2, 5, NULL);

	cClip.Init(3, 2, 7, 4);
	pDest->Black();
	AssertTrue(cDraw.DrawCel(2, 1, pCel, &cClip));
	AssertDrawCelPixels(pDest, 4, pSource, 4, false, 2, 1, &cClip);

	cDraw.Kill();
	pCel = NULL;
	pSource = NULL;
	pDest = NULL;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageDrawCelDestAlphaRowEnds(void)
{
	CImageDraw		cDraw;
	Ptr<CImage>		pSource;
	Ptr<CImage>		pDest;
	Ptr<CImageCel>	pCel;
	uint8			auiOpaque[4] = { 200, 100, 50, 255 };
	uint8			auiTranslucent[4] = { 60, 120, 180, 128 };
	uint8			auiClear[4] = { 0, 0, 0, 0 };
	uint8			auiBackground[4] = { 10, 20, 30, 100 };
	uint8*			apuiRows[2][8] = { { auiOpaque, auiOpaque, auiClear, auiClear, auiTranslucent, auiTranslucent, auiOpaque, auiOpaque },
									   { auiTranslucent, auiTranslucent, auiOpaque, auiOpaque, auiClear, auiClear, auiTranslucent, auiTranslucent } };
	uint8*			puiSource;
	uint8*			puiDest;
	int32			x;
	int32			y;

	//A cel with opacity is split into opaque and translucent segments.  Drawn onto an image with its own opacity each
	//segment must also write that opacity.  Row 0 ends with an opaque segment and row 1 with a translucent one, and
	//both kinds also appear in the middle of a row.  The same source pixel drawn over the same background must give
	//the same result wherever its segment is in the row.
	pSource = OMalloc<CImage>(8, 2, CFT_RGBA, CCO_RGB, CRGB_24bit, ARGB_8bit);
	pDest = OMalloc<CImage>(8, 2, CFT_RGBA, CCO_RGB, CRGB_24bit, ARGB_8bit);
	puiSource = (uint8*)pSource->GetData();
	puiDest = (uint8*)pDest->GetData();
	for (y = 0; y < 2; y++)
	{
		for (x = 0; x < 8; x++)
		{
			memcpy(&puiSource[(x + y * 8) * 4], apuiRows[y][x], 4);
			memcpy(&puiDest[(x + y * 8) * 4], auiBackground, 4);
		}
	}
	pCel = OMalloc<CImageCel>(pSource);

	cDraw.Init(&pDest);
	AssertTrue(cDraw.DrawCel(0, 0, pCel));
	cDraw.Kill();

	//Transparent pixels leave the background alone.
	AssertMemory(auiBackground, &puiDest[(2 + 0 * 8) * 4], 4);
	AssertMemory(auiBackground, &puiDest[(4 + 1 * 8) * 4], 4);

	//Opaque pixels replace the background, opacity included.
	AssertMemory(auiOpaque, &puiDest[(0 + 0 * 8) * 4], 4);
	AssertMemory(auiOpaque, &puiDest[(2 + 1 * 8) * 4], 4);
	AssertMemory(auiOpaque, &puiDest[(6 + 0 * 8) * 4], 4);  //Ends row 0.
	AssertMemory(auiOpaque, &puiDest[(7 + 0 * 8) * 4], 4);

	//Translucent pixels must blend the same way in the middle of row 0, at the start of row 1 and at the end of row 1.
	AssertMemory(&puiDest[(4 + 0 * 8) * 4], &puiDest[(0 + 1 * 8) * 4], 4);
	AssertMemory(&puiDest[(4 + 0 * 8) * 4], &puiDest[(6 + 1 * 8) * 4], 4);  //Ends row 1.
	AssertMemory(&puiDest[(4 + 0 * 8) * 4], &puiDest[(7 + 1 * 8) * 4], 4);

	//Translucent pixels combine their opacity with the background's: 128 + 100 * (255 - 128) / 255.
	AssertInt(178, puiDest[(4 + 0 * 8) * 4 + 3]);
	AssertInt(178, puiDest[(0 + 1 * 8) * 4 + 3]);
	AssertInt(178, puiDest[(7 + 1 * 8) * 4 + 3]);

	pCel = NULL;
	pSource = NULL;
	pDest = NULL;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertDrawCelOpacity(Ptr<CImage> pDest, int32 iLeft, int32 iTop, int32 iRight, int32 iBottom, CRectangle* pcClip)
{
	uint8*	puiDest;
	int32	x;
	int32	y;
	bool	bDrawn;
	uint8	uiExpected;
	size	uiWrong;

	//The fourth byte of an RGBA destination must be opaque where the cel was drawn and still zero everywhere else.
	puiDest = (uint8*)pDest->GetData();
	uiWrong = 0;
	for (y = 0; y < pDest->GetHeight(); y++)
	{
		for (x = 0; x < pDest->GetWidth(); x++)
		{
			bDrawn = (x >= iLeft) && (x < iRight) && (y >= iTop) && (y < iBottom);
			bDrawn &= (pcClip == NULL) || ((x >= pcClip->msTopLeft.x) && (x < pcClip->msBottomRight.x) && (y >= pcClip->msTopLeft.y) && (y < pcClip->msBottomRight.y));
			uiExpected = bDrawn ? 255 : 0;
			if (puiDest[(x + y * pDest->GetWidth()) * 4 + 3] != uiExpected)
			{
				uiWrong++;
			}
		}
	}
	AssertSize(0, uiWrong);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageDrawCelOpaqueOntoDestOpacity(void)
{
	CImageDraw		cDraw;
	Ptr<CImage>		pSource;
	Ptr<CImage>		pDest;
	Ptr<CImageCel>	pCel;
	CRectangle		cClip;

	//An RGB cel has no opacity of its own.  Drawn onto an RGBA image the colour must be copied unchanged and the
	//destination opacity set to opaque, not written over one of the colours.
	pSource = CreateDrawCelSourceImage(6, 4);
	pCel = OMalloc<CImageCel>(pSource);
	pDest = OMalloc<CImage>(10, 8, CFT_RGBA, CCO_RGB, CRGB_24bit, ARGB_8bit);

	cDraw.Init(&pDest);

	memset(pDest->GetData(), 0, pDest->GetByteSize());
	AssertTrue(cDraw.DrawCel(2, 1, pCel));
	AssertDrawCelPixels(pDest, 4, pSource, 3, false, 2, 1, NULL);
	AssertDrawCelOpacity(pDest, 2, 1, 8, 5, NULL);

	memset(pDest->GetData(), 0, pDest->GetByteSize());
	AssertTrue(cDraw.DrawCel(-3, 6, pCel));
	AssertDrawCelPixels(pDest, 4, pSource, 3, false, -3, 6, NULL);
	AssertDrawCelOpacity(pDest, -3, 6, 3, 10, NULL);

	cClip.Init(3, 2, 7, 4);
	memset(pDest->GetData(), 0, pDest->GetByteSize());
	AssertTrue(cDraw.DrawCel(2, 1, pCel, &cClip));
	AssertDrawCelPixels(pDest, 4, pSource, 3, false, 2, 1, &cClip);
	AssertDrawCelOpacity(pDest, 2, 1, 8, 5, &cClip);

	cDraw.Kill();
	pCel = NULL;
	pSource = NULL;
	pDest = NULL;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageDrawCelAlignment(void)
{
	CImageDraw		cDraw;
	Ptr<CImage>		pSource;
	Ptr<CImage>		pDest;
	Ptr<CImageCel>	pCel;
	CRectangle		cClip;
	int32			aiPositions[6][2] = { { 8, 6 }, { 6, 4 }, { 3, 2 }, { 12, 9 }, { 15, 3 }, { 7, 13 } };
	size			i;

	//A cel aligned to its bottom right is drawn with its bottom right corner at the position given.  The cel must be
	//both clipped and drawn where its alignment puts it, else it can be drawn outside the destination image.
	pSource = CreateDrawCelSourceImage(6, 4);
	pCel = OMalloc<CImageCel>(pSource, 0, 0, 6, 4, 0, 0, 0, 0, SUB_IMAGE_ALIGNMENT_RIGHT | SUB_IMAGE_ALIGNMENT_BOTTOM);
	pDest = OMalloc<CImage>(10, 8, CFT_RGB, CCO_RGB, CRGB_24bit, ARGB_None);

	cDraw.Init(&pDest);
	for (i = 0; i < 6; i++)
	{
		pDest->Black();
		AssertTrue(cDraw.DrawCel(aiPositions[i][0], aiPositions[i][1], pCel));
		AssertDrawCel(pDest, pSource, aiPositions[i][0] - 6, aiPositions[i][1] - 4, NULL);
	}

	cClip.Init(3, 2, 7, 5);
	for (i = 0; i < 6; i++)
	{
		pDest->Black();
		AssertTrue(cDraw.DrawCel(aiPositions[i][0], aiPositions[i][1], pCel, &cClip));
		AssertDrawCel(pDest, pSource, aiPositions[i][0] - 6, aiPositions[i][1] - 4, &cClip);
	}

	//Centred, the middle of the cel is at the position given.
	pCel = OMalloc<CImageCel>(pSource, 0, 0, 6, 4, 0, 0, 0, 0, SUB_IMAGE_ALIGNMENT_CENTER_HORIZONTAL | SUB_IMAGE_ALIGNMENT_CENTER_VERTICAL);
	pDest->Black();
	AssertTrue(cDraw.DrawCel(5, 4, pCel));
	AssertDrawCel(pDest, pSource, 2, 2, NULL);

	pDest->Black();
	AssertTrue(cDraw.DrawCel(9, 1, pCel));
	AssertDrawCel(pDest, pSource, 6, -1, NULL);

	cDraw.Kill();
	pCel = NULL;
	pSource = NULL;
	pDest = NULL;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageDrawBlitterContextInit(void)
{
	CImageBlitterContext	cContext;

	//Init with no images must clear every field, not just the first few bytes.
	memset(&cContext, 0xAB, sizeof(CImageBlitterContext));
	cContext.Init();

	AssertSize(0, cContext.miSourcePixelStride);
	AssertSize(0, cContext.miDestPixelStride);
	AssertSize(0, cContext.miSourceWidth);
	AssertSize(0, cContext.miDestWidth);
	AssertSize(0, cContext.miSourceRowStride);
	AssertSize(0, cContext.miDestRowStride);
	AssertSize(0, cContext.muiSourceColourOffset);
	AssertSize(0, cContext.muiDestColourOffset);
	AssertSize(0, cContext.muiDestAlphaOffset);
	AssertSize(0, cContext.muiSourceAlphaOffset);
	AssertSize(0, cContext.muiColourWidth);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
Ptr<CImage> CreateDrawCelTranslucentImage(int32 iWidth, int32 iHeight)
{
	Ptr<CImage>		pImage;
	uint8*			puiData;
	int32			x;
	int32			y;
	uint8			auiAlpha[8] = { 255, 255, 0, 128, 40, 255, 0, 200 };

	//Opaque, transparent and translucent runs of different lengths in every row.
	pImage = CreateDrawCelImage(iWidth, iHeight, CFT_RGBA, ARGB_8bit, 4, false);
	puiData = (uint8*)pImage->GetData();
	for (y = 0; y < iHeight; y++)
	{
		for (x = 0; x < iWidth; x++)
		{
			puiData[(x + y * iWidth) * 4 + 3] = auiAlpha[(x + 3 * y) % 8];
		}
	}
	return pImage;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void FillDrawCelBackground(Ptr<CImage> pDest, size uiDestStride, uint8* puiBackground)
{
	uint8*	puiDest;
	size	ui;
	size	uiNumPixels;

	puiDest = (uint8*)pDest->GetData();
	uiNumPixels = pDest->GetWidth() * pDest->GetHeight();
	for (ui = 0; ui < uiNumPixels; ui++)
	{
		memcpy(&puiDest[ui * uiDestStride], puiBackground, uiDestStride);
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertDrawCelSized(Ptr<CImage> pDest, size uiDestStride, uint8* puiBackground, Ptr<CImageCel> pCel, size uiSourceStride, int32 iLeft, int32 iTop, int32 iWidth, int32 iHeight, CRectangle* pcClip)
{
	CSubImage*		pcSubImage;
	Ptr<CImage>		pSource;
	uint8*			puiDest;
	uint8*			puiSource;
	uint8*			puiSourcePixel;
	uint8			auiExpected[4];
	int32			x;
	int32			y;
	int32			xCel;
	int32			yCel;
	bool			bInside;
	uint16			uiAlpha;
	uint16			uiBlend;
	size			i;
	size			uiWrong;

	//Every destination pixel is worked out on its own: the cel pixel under its centre, (2x + 1) * full / (2 * sized),
	//drawn over the background.  Pixels outside the sized cel, the clip, or the cel's image keep the background.
	pcSubImage = pCel->GetSubImage();
	pSource = pCel->GetSourceImage();
	puiDest = (uint8*)pDest->GetData();
	puiSource = (uint8*)pSource->GetData();
	uiWrong = 0;
	for (y = 0; y < pDest->GetHeight(); y++)
	{
		for (x = 0; x < pDest->GetWidth(); x++)
		{
			memcpy(auiExpected, puiBackground, uiDestStride);

			bInside = (x >= iLeft) && (x < iLeft + iWidth) && (y >= iTop) && (y < iTop + iHeight);
			bInside &= (pcClip == NULL) || ((x >= pcClip->msTopLeft.x) && (x < pcClip->msBottomRight.x) && (y >= pcClip->msTopLeft.y) && (y < pcClip->msBottomRight.y));
			if (bInside)
			{
				xCel = ((2 * (x - iLeft) + 1) * pcSubImage->GetFullWidth()) / (2 * iWidth) - pcSubImage->msOffsetTopLeft.x;
				yCel = ((2 * (y - iTop) + 1) * pcSubImage->GetFullHeight()) / (2 * iHeight) - pcSubImage->msOffsetTopLeft.y;
				if ((xCel >= 0) && (xCel < pcSubImage->GetImageWidth()) && (yCel >= 0) && (yCel < pcSubImage->GetImageHeight()))
				{
					puiSourcePixel = &puiSource[((pcSubImage->mcImageRect.msTopLeft.x + xCel) + (pcSubImage->mcImageRect.msTopLeft.y + yCel) * pSource->GetWidth()) * uiSourceStride];
					uiAlpha = (uiSourceStride == 4) ? puiSourcePixel[3] : 255;
					if (uiAlpha == 255)
					{
						memcpy(auiExpected, puiSourcePixel, 3);
						if (uiDestStride == 4)
						{
							auiExpected[3] = 255;
						}
					}
					else if (uiAlpha != 0)
					{
						uiBlend = (uiAlpha > 128) ? uiAlpha + 1 : uiAlpha;
						for (i = 0; i < 3; i++)
						{
							auiExpected[i] = (uint8)((puiSourcePixel[i] * uiBlend + auiExpected[i] * (256 - uiBlend)) >> 8);
						}
						if (uiDestStride == 4)
						{
							auiExpected[3] = (uint8)(uiAlpha + (auiExpected[3] * (255 - uiAlpha) + 127) / 255);
						}
					}
				}
			}

			if (memcmp(&puiDest[(x + y * pDest->GetWidth()) * uiDestStride], auiExpected, uiDestStride) != 0)
			{
				uiWrong++;
			}
		}
	}
	AssertSize(0, uiWrong);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertDrawCelSizes(Ptr<CImageCel> pCel, size uiSourceStride, Ptr<CImage> pDest, size uiDestStride)
{
	CImageDraw		cDraw;
	CRectangle		acClips[3];
	CRectangle*		pcClip;
	uint8			auiBackground[4] = { 5, 6, 7, 9 };
	int32			aiSizes[13][2] = { { 12, 8 }, { 3, 2 }, { 7, 5 }, { 6, 9 }, { 13, 4 }, { 6, 2 }, { 1, 1 }, { 25, 3 }, { 2, 11 }, { 6, 4 }, { 19, 14 }, { 0, 5 }, { 4, -1 } };
	int32			aiPositions[6][2] = { { 2, 2 }, { -3, -2 }, { 15, 11 }, { -30, -30 }, { 0, 0 }, { 9, -4 } };
	size			uiSize;
	size			uiPosition;
	size			uiClip;
	int32			x;
	int32			y;
	int32			iWidth;
	int32			iHeight;
	bool			bResult;

	//Every size is drawn through the same blitter so its sized tables must be rebuilt whenever the size changes.
	//A size of 6x4 is the cel's own and the zero and negative sizes draw nothing.
	acClips[1].Init(3, 2, 9, 7);
	acClips[2].Init(5, 0, 6, 16);

	cDraw.Init(&pDest);
	for (uiSize = 0; uiSize < 13; uiSize++)
	{
		iWidth = aiSizes[uiSize][0];
		iHeight = aiSizes[uiSize][1];
		for (uiPosition = 0; uiPosition < 6; uiPosition++)
		{
			x = aiPositions[uiPosition][0];
			y = aiPositions[uiPosition][1];
			for (uiClip = 0; uiClip < 3; uiClip++)
			{
				pcClip = (uiClip == 0) ? NULL : &acClips[uiClip];
				FillDrawCelBackground(pDest, uiDestStride, auiBackground);
				bResult = cDraw.DrawCel(x, y, iWidth, iHeight, pCel, pcClip);
				AssertTrue(bResult);
				AssertDrawCelSized(pDest, uiDestStride, auiBackground, pCel, uiSourceStride, x, y, iWidth, iHeight, pcClip);
			}
		}
	}
	cDraw.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageDrawCelSizedOpaque(void)
{
	Ptr<CImage>		pSource;
	Ptr<CImage>		pDest;
	Ptr<CImageCel>	pCel;

	//The same layout with no destination opacity uses the contiguous blitter, which can only be used one for one.
	pSource = CreateDrawCelSourceImage(6, 4);
	pCel = OMalloc<CImageCel>(pSource);
	pDest = OMalloc<CImage>(20, 16, CFT_RGB, CCO_RGB, CRGB_24bit, ARGB_None);
	AssertDrawCelSizes(pCel, 3, pDest, 3);

	//Opaque onto a destination with opacity.
	pDest = OMalloc<CImage>(20, 16, CFT_RGBA, CCO_RGB, CRGB_24bit, ARGB_8bit);
	AssertDrawCelSizes(pCel, 3, pDest, 4);

	//Opaque segments between transparent gaps.  Shrinking can drop a segment entirely.
	pSource = CreateDrawCelImage(6, 4, CFT_RGBA, ARGB_8bit, 4, true);
	pCel = OMalloc<CImageCel>(pSource);
	pDest = OMalloc<CImage>(20, 16, CFT_RGB, CCO_RGB, CRGB_24bit, ARGB_None);
	AssertDrawCelSizes(pCel, 4, pDest, 3);

	pCel = NULL;
	pSource = NULL;
	pDest = NULL;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageDrawCelSizedTranslucent(void)
{
	Ptr<CImage>		pSource;
	Ptr<CImage>		pDest;
	Ptr<CImageCel>	pCel;

	//Translucent and opaque segments, without and with destination opacity.
	pSource = CreateDrawCelTranslucentImage(6, 4);
	pCel = OMalloc<CImageCel>(pSource);

	pDest = OMalloc<CImage>(20, 16, CFT_RGB, CCO_RGB, CRGB_24bit, ARGB_None);
	AssertDrawCelSizes(pCel, 4, pDest, 3);

	pDest = OMalloc<CImage>(20, 16, CFT_RGBA, CCO_RGB, CRGB_24bit, ARGB_8bit);
	AssertDrawCelSizes(pCel, 4, pDest, 4);

	pCel = NULL;
	pSource = NULL;
	pDest = NULL;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageDrawCelSizedBorders(void)
{
	Ptr<CImage>		pSource;
	Ptr<CImage>		pDest;
	Ptr<CImageCel>	pCel;

	//The cel is the 4x3 part of the source at 1,1 with transparent borders of 1 left, 0 top, 1 right and 1 bottom,
	//so the full cel is 6x4.  The borders are sized with the rest of the cel.
	pSource = CreateDrawCelTranslucentImage(7, 5);
	pCel = OMalloc<CImageCel>(pSource, 1, 1, 5, 4, 1, 0, 1, 1, SUB_IMAGE_ALIGNMENT_LEFT | SUB_IMAGE_ALIGNMENT_TOP);
	AssertInt(6, pCel->GetSubImage()->GetFullWidth());
	AssertInt(4, pCel->GetSubImage()->GetFullHeight());

	pDest = OMalloc<CImage>(20, 16, CFT_RGB, CCO_RGB, CRGB_24bit, ARGB_None);
	AssertDrawCelSizes(pCel, 4, pDest, 3);

	pCel = NULL;
	pSource = NULL;
	pDest = NULL;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageDrawCelSizedAlignment(void)
{
	CImageDraw		cDraw;
	Ptr<CImage>		pSource;
	Ptr<CImage>		pDest;
	Ptr<CImageCel>	pCel;
	CRectangle		cClip;
	uint8			auiBackground[3] = { 5, 6, 7 };

	//A centred 6x4 cel drawn 12x8 is centred on its position.
	pSource = CreateDrawCelSourceImage(6, 4);
	pCel = OMalloc<CImageCel>(pSource, 0, 0, 6, 4, 0, 0, 0, 0, SUB_IMAGE_ALIGNMENT_CENTER_HORIZONTAL | SUB_IMAGE_ALIGNMENT_CENTER_VERTICAL);
	pDest = OMalloc<CImage>(20, 16, CFT_RGB, CCO_RGB, CRGB_24bit, ARGB_None);

	cDraw.Init(&pDest);

	FillDrawCelBackground(pDest, 3, auiBackground);
	AssertTrue(cDraw.DrawCel(10, 8, 12, 8, pCel));
	AssertDrawCelSized(pDest, 3, auiBackground, pCel, 3, 4, 4, 12, 8, NULL);

	FillDrawCelBackground(pDest, 3, auiBackground);
	AssertTrue(cDraw.DrawCel(1, 15, 12, 8, pCel));
	AssertDrawCelSized(pDest, 3, auiBackground, pCel, 3, -5, 11, 12, 8, NULL);

	//Aligned to its bottom right and shrunk to 3x2.
	pCel = OMalloc<CImageCel>(pSource, 0, 0, 6, 4, 0, 0, 0, 0, SUB_IMAGE_ALIGNMENT_RIGHT | SUB_IMAGE_ALIGNMENT_BOTTOM);
	cClip.Init(0, 0, 9, 7);
	FillDrawCelBackground(pDest, 3, auiBackground);
	AssertTrue(cDraw.DrawCel(10, 8, 3, 2, pCel, &cClip));
	AssertDrawCelSized(pDest, 3, auiBackground, pCel, 3, 7, 6, 3, 2, &cClip);

	cDraw.Kill();
	pCel = NULL;
	pSource = NULL;
	pDest = NULL;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageDrawBlitterCacheOnImage(void)
{
	Ptr<CImage>					pImage;
	Ptr<CImage>					pSource;
	Ptr<CImageCelBlitterCache>	pCache;
	Ptr<CImageCelBlitterCache>	pNextCache;
	Ptr<CImageCel>				pCel;
	size						uiObjects;

	//An image keeps the cache of blitters that draw onto it.  The same cache is returned until the image's size or
	//format changes, then a new one is made because blitters only work for the image they were made for.
	uiObjects = gcObjects.NumMemoryIndexes();
	pImage = OMalloc<CImage>(10, 8, CFT_RGB, CCO_RGB, CRGB_24bit, ARGB_None);
	pSource = CreateDrawCelSourceImage(6, 4);
	pCel = OMalloc<CImageCel>(pSource);

	pCache = pImage->GetBlitterCache();
	AssertTrue(pCache.IsNotNull());
	AssertTrue(pCache->Matches(pImage));
	AssertTrue(pCache->CreateImageBlitter(pCel).IsNotNull());
	AssertTrue(pImage->GetBlitterCache().Object() == pCache.Object());

	pImage->BeginChange();
	pImage->SetSize(12, 8);
	pImage->EndChange();
	pNextCache = pImage->GetBlitterCache();
	AssertTrue(pNextCache.Object() != pCache.Object());
	pCache = pNextCache;

	pImage->ReInit();
	pNextCache = pImage->GetBlitterCache();
	AssertTrue(pNextCache.Object() != pCache.Object());

	//The image, its cache and a blitter in it point at each other, but once nothing else does they are all freed.
	pImage->ReInit(4, 4, PT_uint8, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, CHANNEL_STOP);
	AssertTrue(pImage->GetBlitterCache()->CreateImageBlitter(pCel).IsNotNull());
	pCache = NULL;
	pNextCache = NULL;
	pImage = NULL;
	pCel = NULL;
	pSource = NULL;
	AssertSize(uiObjects, gcObjects.NumMemoryIndexes());
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
Ptr<CImageCel> CreateDrawCel(void)
{
	//A cel and its source image are two objects.
	return OMalloc<CImageCel>(CreateDrawCelSourceImage(6, 4));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
Ptr<CImage> CreateDrawDest(void)
{
	return OMalloc<CImage>(10, 8, CFT_RGB, CCO_RGB, CRGB_24bit, ARGB_None);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageDrawBlitterCacheCelFreedFirst(void)
{
	Ptr<CImage>					pDest;
	Ptr<CImageCel>				pCel;
	Ptr<CImageCelBlitterCache>	pCache;
	size						uiStart;

	//A blitter does not keep its cel alive, so a cel can be freed while the image it was drawn onto lives on.
	//The cache forgets the cel's blitter and only removes it the next time the cache is used.
	uiStart = gcObjects.NumMemoryIndexes();
	pDest = CreateDrawDest();
	pCel = CreateDrawCel();
	pCache = pDest->GetBlitterCache();
	AssertTrue(pCache->CreateImageBlitter(pCel).IsNotNull());
	AssertSize(1, pCel->NumBlitterCaches());
	AssertSize(uiStart + 5, gcObjects.NumMemoryIndexes());  //Destination, cache, blitter, cel and its image.

	pCel = NULL;
	AssertSize(uiStart + 3, gcObjects.NumMemoryIndexes());  //The cel and its image are gone, the forgotten blitter is not yet.
	AssertSize(0, pCache->NumImageBlitters());
	AssertSize(uiStart + 2, gcObjects.NumMemoryIndexes());

	//The cache carries on working.
	pCel = CreateDrawCel();
	AssertTrue(pCache->CreateImageBlitter(pCel).IsNotNull());
	AssertSize(1, pCache->NumImageBlitters());

	pCel = NULL;
	pCache = NULL;
	pDest = NULL;
	AssertSize(uiStart, gcObjects.NumMemoryIndexes());
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageDrawBlitterCacheDestinationFreedFirst(void)
{
	Ptr<CImage>		pDest;
	Ptr<CImageCel>	pCel;
	size			uiStart;

	//When the destination is freed its cache and blitters go with it, and the cel forgets the cache.  The cel can then
	//be drawn onto another image and freed without touching the freed cache.
	uiStart = gcObjects.NumMemoryIndexes();
	pDest = CreateDrawDest();
	pCel = CreateDrawCel();
	AssertTrue(pDest->GetBlitterCache()->CreateImageBlitter(pCel).IsNotNull());
	AssertSize(1, pCel->NumBlitterCaches());

	pDest = NULL;
	AssertSize(0, pCel->NumBlitterCaches());
	AssertSize(uiStart + 2, gcObjects.NumMemoryIndexes());  //Just the cel and its image.

	pDest = CreateDrawDest();
	AssertTrue(pDest->GetBlitterCache()->CreateImageBlitter(pCel).IsNotNull());
	AssertSize(1, pCel->NumBlitterCaches());
	pCel = NULL;
	AssertSize(0, pDest->GetBlitterCache()->NumImageBlitters());

	pDest = NULL;
	AssertSize(uiStart, gcObjects.NumMemoryIndexes());
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageDrawBlitterCacheSharedCel(void)
{
	Ptr<CImage>		pDest1;
	Ptr<CImage>		pDest2;
	Ptr<CImageCel>	pCel;
	size			uiStart;

	//One cel drawn onto two images is in both images' caches.
	uiStart = gcObjects.NumMemoryIndexes();
	pDest1 = CreateDrawDest();
	pDest2 = CreateDrawDest();
	pCel = CreateDrawCel();
	AssertTrue(pDest1->GetBlitterCache()->CreateImageBlitter(pCel).IsNotNull());
	AssertTrue(pDest2->GetBlitterCache()->CreateImageBlitter(pCel).IsNotNull());
	AssertTrue(pDest2->GetBlitterCache()->CreateImageBlitter(pCel).IsNotNull());  //The same blitter again.
	AssertSize(2, pCel->NumBlitterCaches());
	AssertSize(1, pDest2->GetBlitterCache()->NumImageBlitters());

	pDest1 = NULL;
	AssertSize(1, pCel->NumBlitterCaches());

	pCel = NULL;
	AssertSize(0, pDest2->GetBlitterCache()->NumImageBlitters());

	pDest2 = NULL;
	AssertSize(uiStart, gcObjects.NumMemoryIndexes());
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageDrawBlitterCacheCelKilled(void)
{
	Ptr<CImage>		pDest;
	Ptr<CImageCel>	pCel;
	Ptr<CImageCel>	pOtherPointer;
	size			uiStart;

	//Killing a cel outright, while other pointers still point at it, also makes the caches forget it.
	uiStart = gcObjects.NumMemoryIndexes();
	pDest = CreateDrawDest();
	pCel = CreateDrawCel();
	pOtherPointer = pCel;
	AssertTrue(pDest->GetBlitterCache()->CreateImageBlitter(pCel).IsNotNull());

	pCel->Kill();
	AssertSize(0, pDest->GetBlitterCache()->NumImageBlitters());

	pCel = NULL;
	pOtherPointer = NULL;
	pDest = NULL;
	AssertSize(uiStart, gcObjects.NumMemoryIndexes());
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageDrawBlitterCacheFreedTogether(void)
{
	Ptr<CArrayObject>	pHolder;
	Ptr<CImage>			pDest;
	Ptr<CImageCel>		pCel;
	size				i;
	size				uiStart;

	//When the only thing holding a destination and a cel is freed, the destination, its cache, the blitter, the cel and
	//its image are all freed in the same kill in whatever order the objects system chooses.  Each must let go of the
	//others without touching one that has already been freed.  A few cels make some be freed before the cache and some after.
	uiStart = gcObjects.NumMemoryIndexes();
	pHolder = OMalloc<CArrayObject>();
	pDest = CreateDrawDest();
	pHolder->Add(pDest);
	for (i = 0; i < 4; i++)
	{
		pCel = CreateDrawCel();
		pHolder->Add(pCel);
		AssertTrue(pDest->GetBlitterCache()->CreateImageBlitter(pCel).IsNotNull());
	}
	pCel = NULL;
	AssertSize(4, pDest->GetBlitterCache()->NumImageBlitters());
	pDest = NULL;
	AssertSize(uiStart + 1 + 2 + 4 + 4 * 2, gcObjects.NumMemoryIndexes());  //Holder, destination and cache, four blitters, four cels and their images.

	pHolder = NULL;
	AssertSize(uiStart, gcObjects.NumMemoryIndexes());
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageDraw(void)
{
	BeginTests();

	DataIOInit();
	ObjectsInit();

	TestImageDrawBox1();
	TestImageDrawBox2();
	TestImageDrawLine();
	TestImageDrawLineExtents();
	TestImageDrawCelClipping();
	TestImageDrawCelMismatchedFormat();
	TestImageDrawCelClippingTransparentGaps();
	TestImageDrawCelRGBX();
	TestImageDrawCelDestAlphaRowEnds();
	TestImageDrawCelOpaqueOntoDestOpacity();
	TestImageDrawCelAlignment();
	TestImageDrawBlitterContextInit();
	TestImageDrawCelSizedOpaque();
	TestImageDrawCelSizedTranslucent();
	TestImageDrawCelSizedBorders();
	TestImageDrawCelSizedAlignment();
	TestImageDrawBlitterCacheOnImage();
	TestImageDrawBlitterCacheCelFreedFirst();
	TestImageDrawBlitterCacheDestinationFreedFirst();
	TestImageDrawBlitterCacheSharedCel();
	TestImageDrawBlitterCacheCelKilled();
	TestImageDrawBlitterCacheFreedTogether();

	ObjectsKill(false);
	DataIOKill();

	TestStatistics();
}

