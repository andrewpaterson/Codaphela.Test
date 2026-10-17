#include "BaseLib/FastFunctions.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "StandardLib/Objects.h"
#include "StandardLib/ArrayObject.h"
#include "SupportLib/ImageReader.h"
#include "SupportLib/ImageWriter.h"
#include "SupportLib/ImageDraw.h"
#include "SupportLib/ImageCel.h"
#include "SupportLib/ImageCelBlitterCache.h"
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

