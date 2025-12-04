#include "BaseLib/FastFunctions.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "StandardLib/Objects.h"
#include "SupportLib/ImageReader.h"
#include "SupportLib/ImageWriter.h"
#include "SupportLib/ImageDraw.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageDrawBox1(void)
{
	CImageDraw			cDraw;
	Ptr<CImage>			pImage = OMalloc<CImage>(32, 32);
	CImageColourRGB		cColour;

	pImage->Clear();

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
	AssertFileMemory("input" _FS_ "DrawBox1.raw", pImage->GetData(), pImage->GetByteSize());

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

	pImage->Clear();

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
	AssertFileMemory("input" _FS_ "DrawBox2.raw", pImage->GetData(), pImage->GetByteSize());

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

	pImage->Clear();

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
	AssertFileMemory("input" _FS_ "DrawLine1.raw", pImage->GetData(), pImage->GetByteSize());

	pImage->Clear();

	cColour.Init(0.4f, 0.9f, 0.4f);
	cDraw.SetColour(&cColour);

	cDraw.DrawLine(63, 31, 0, 0);
	cDraw.DrawLine(63, 16, 0, 0);
	cDraw.DrawLine(31, 31, 0, 0);
	cDraw.DrawLine(63, 0 , 0, 0);
	cDraw.DrawLine(0, 31 , 0, 0);

	WriteImage(pImage, "Output" _FS_ "DrawLine2.raw");
	WriteImage(pImage, "Output" _FS_ "DrawLine2.png");
	AssertFileMemory("input" _FS_ "DrawLine2.raw", pImage->GetData(), pImage->GetByteSize());

	pImage->Clear();

	cColour.Init(0.4f, 0.4f, 0.99f);
	cDraw.SetColour(&cColour);

	cDraw.DrawLine(63, 0, 0, 31);
	cDraw.DrawLine(63, 0, 0, 16);
	cDraw.DrawLine(31, 0, 0, 31);
	cDraw.DrawLine(63, 0, 0, 0);
	cDraw.DrawLine(0, 0, 0, 31);

	WriteImage(pImage, "Output" _FS_ "DrawLine3.raw");
	WriteImage(pImage, "Output" _FS_ "DrawLine3.png");
	AssertFileMemory("input" _FS_ "DrawLine3.raw", pImage->GetData(), pImage->GetByteSize());

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

	pImage->Clear();

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
	AssertFileMemory("input" _FS_ "DrawLine4.raw", pImage->GetData(), pImage->GetByteSize());

	pImage->Clear();

	for (y = 0; y < 16; y += 2)
	{
		cDraw.SetColour(&cColour1);
		cDraw.DrawLine(15, y, 16, y);
		cDraw.SetColour(&cColour2);
		cDraw.DrawHorizontalLine(15, 16, y + 1);
	}

	WriteImage(pImage, "Output" _FS_ "DrawLine5.raw");
	WriteImage(pImage, "Output" _FS_ "DrawLine5.png");
	AssertFileMemory("input" _FS_ "DrawLine5.raw", pImage->GetData(), pImage->GetByteSize());

	cDraw.Kill();
	cColour1.Kill();
	cColour2.Kill();
	pImage = NULL;
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

	ObjectsKill();
	DataIOKill();

	TestStatistics();
}

