#include "BaseLib/FastFunctions.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "StandardLib/Objects.h"
#include "SupportLib/ImageReader.h"
#include "SupportLib/ImageWriter.h"
#include "SupportLib/ImageDraw.h"
#include "SupportLib/ImageCel.h"
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
Ptr<CImage> CreateDrawCelSourceImage(int32 iWidth, int32 iHeight)
{
	Ptr<CImage>		pImage;
	uint8*			puiData;
	int32			x;
	int32			y;

	//Every pixel is different so a pixel drawn in the wrong place is always noticed.
	pImage = OMalloc<CImage>(iWidth, iHeight, CFT_RGB, CCO_RGB, CRGB_24bit, ARGB_None);
	puiData = (uint8*)pImage->GetData();
	for (y = 0; y < iHeight; y++)
	{
		for (x = 0; x < iWidth; x++)
		{
			puiData[(x + y * iWidth) * 3 + 0] = (uint8)(10 + x * 30);
			puiData[(x + y * iWidth) * 3 + 1] = (uint8)(20 + y * 40);
			puiData[(x + y * iWidth) * 3 + 2] = 200;
		}
	}
	return pImage;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertDrawCel(Ptr<CImage> pDest, Ptr<CImage> pSource, int32 iDestX, int32 iDestY, CRectangle* pcClip)
{
	uint8*	puiDest;
	uint8*	puiSource;
	int32	x;
	int32	y;
	int32	xs;
	int32	ys;
	bool	bInSource;
	bool	bInClip;
	size	uiDest;
	size	uiSource;
	size	uiWrong;

	//A destination pixel must hold the source pixel over it if it is inside the clip, otherwise it must still be black.
	puiDest = (uint8*)pDest->GetData();
	puiSource = (uint8*)pSource->GetData();
	uiWrong = 0;
	for (y = 0; y < pDest->GetHeight(); y++)
	{
		for (x = 0; x < pDest->GetWidth(); x++)
		{
			xs = x - iDestX;
			ys = y - iDestY;
			bInSource = (xs >= 0) && (xs < pSource->GetWidth()) && (ys >= 0) && (ys < pSource->GetHeight());
			bInClip = (pcClip == NULL) || ((x >= pcClip->msTopLeft.x) && (x < pcClip->msBottomRight.x) && (y >= pcClip->msTopLeft.y) && (y < pcClip->msBottomRight.y));

			uiDest = (x + y * pDest->GetWidth()) * 3;
			if (bInSource && bInClip)
			{
				uiSource = (xs + ys * pSource->GetWidth()) * 3;
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

	ObjectsKill(false);
	DataIOKill();

	TestStatistics();
}

