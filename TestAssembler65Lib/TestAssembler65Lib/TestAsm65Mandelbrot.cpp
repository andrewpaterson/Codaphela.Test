#include "TestAsm65Context.h"
#include "BaseLib/FileUtil.h"
#include "StandardLib/Objects.h"
#include "SupportLib/Image.h"
#include "SupportLib/PNGWriter.h"
#include "TestLib/Assert.h"


#define MANDELBROT_WIDTH	100
#define MANDELBROT_HEIGHT	100
#define MANDELBROT_MAXITER	64
#define MANDELBROT_IMAGE	0x100000


//////////////////////////////////////////////////////////////////////////
//
// (a * b) >> 24 for signed Q24 values, as the Multiply subroutine does it.
//
//////////////////////////////////////////////////////////////////////////
static int64 MandelbrotMultiply(int64 a, int64 b)
{
	bool	bNegative;
	uint64	uiProduct;

	bNegative = (a < 0) != (b < 0);
	uiProduct = ((uint64)(a < 0 ? -a : a) * (uint64)(b < 0 ? -b : b)) >> 24;
	return bNegative ? -(int64)uiProduct : (int64)uiProduct;
}


//////////////////////////////////////////////////////////////////////////
//
// The colour the program should store for a pixel.
//
//////////////////////////////////////////////////////////////////////////
static uint32 MandelbrotColour(int64 iCx, int64 iCy)
{
	int64	iZx;
	int64	iZy;
	int64	iZx2;
	int64	iZy2;
	int		i;
	uint32	uiGrey;

	iZx = 0;
	iZy = 0;
	for (i = 0; i < MANDELBROT_MAXITER; i++)
	{
		iZx2 = MandelbrotMultiply(iZx, iZx);
		iZy2 = MandelbrotMultiply(iZy, iZy);
		if ((uint64)(iZx2 + iZy2) >= ((uint64)4 << 24))
		{
			uiGrey = (uint32)((i * 4) & 0xFF);
			return 0xFF000000 | (uiGrey * 0x010101);
		}
		iZy = (MandelbrotMultiply(iZx, iZy) << 1) + iCy;
		iZx = iZx2 - iZy2 + iCx;
	}
	return 0xFF000000;
}


//////////////////////////////////////////////////////////////////////////
//
// Writes the image in the processor's memory (32 bit ARGB, blue in the low byte) to a
// PNG.
//
//////////////////////////////////////////////////////////////////////////
static void WriteMandelbrotPNG(CAsm65Memory* pcContext, char* szFilename)
{
	Ptr<CImage>	pcImage;
	uint8*		puiPixel;
	uint32		uiARGB;
	int			i;

	pcImage = OMalloc<CImage>(MANDELBROT_WIDTH, MANDELBROT_HEIGHT, PT_uint8, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, IMAGE_OPACITY, CHANNEL_STOP);
	puiPixel = (uint8*)pcImage->GetData();
	for (i = 0; i < MANDELBROT_WIDTH * MANDELBROT_HEIGHT; i++)
	{
		uiARGB = pcContext->GetLong(MANDELBROT_IMAGE + 4 * i);
		puiPixel[0] = (uint8)(uiARGB >> 16);
		puiPixel[1] = (uint8)(uiARGB >> 8);
		puiPixel[2] = (uint8)uiARGB;
		puiPixel[3] = (uint8)(uiARGB >> 24);
		puiPixel += 4;
	}
	AssertTrue(SavePNG(pcImage, szFilename));
	pcImage->Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// Every pixel matches the same fixed point calculation done in C++.  The image is
// written to Output/Mandelbrot.png.
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65MandelbrotImage(void)
{
	STestAsm65Run	sRun;
	CFileUtil		cFileUtil;
	int64			iCx;
	int64			iCy;
	int64			iXStep;
	int64			iYStep;
	int				x;
	int				y;
	int				iMismatches;
	int				iInside;
	uint32			uiExpected;
	uint32			uiActual;

	AssertTrue(TestAsm65BeginFile(&sRun, "Mandelbrot.asm", 0x1000));
	AssertTrue(TestAsm65Run(&sRun, 50000000) < 50000000);

	iXStep = ((int64)5 << 24) / (2 * MANDELBROT_WIDTH);
	iYStep = ((int64)5 << 24) / (2 * MANDELBROT_HEIGHT);
	iMismatches = 0;
	iInside = 0;
	iCy = -((int64)5 << 24) / 4;
	for (y = 0; y < MANDELBROT_HEIGHT; y++)
	{
		iCx = -((int64)2 << 24);
		for (x = 0; x < MANDELBROT_WIDTH; x++)
		{
			uiExpected = MandelbrotColour(iCx, iCy);
			uiActual = sRun.pcContext->GetLong(MANDELBROT_IMAGE + 4 * (y * MANDELBROT_WIDTH + x));
			if (uiActual != uiExpected)
			{
				iMismatches++;
			}
			if (uiExpected == 0xFF000000)
			{
				iInside++;
			}
			iCx += iXStep;
		}
		iCy += iYStep;
	}
	AssertInt(0, iMismatches);
	AssertTrue(iInside > 0);
	AssertTrue(iInside < MANDELBROT_WIDTH * MANDELBROT_HEIGHT);

	//c = 0 (the middle of the main body) is inside; c = -2 - 1.25i (the first pixel) escapes
	//after one iteration (grey 4).
	AssertIntHex(0xFF000000, sRun.pcContext->GetLong(MANDELBROT_IMAGE + 4 * (50 * MANDELBROT_WIDTH + 80)));
	AssertIntHex(0xFF040404, sRun.pcContext->GetLong(MANDELBROT_IMAGE));

	cFileUtil.MakeDir("Output");
	WriteMandelbrotPNG(sRun.pcContext, "Output" _FS_ "Mandelbrot.png");
	TestAsm65End(&sRun);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65Mandelbrot(void)
{
	BeginTests();

	TestAsm65MandelbrotImage();

	TestStatistics();
}
