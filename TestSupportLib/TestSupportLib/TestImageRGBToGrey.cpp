#include "stdafx.h"
#include "BaseLib/NaiveFile.h"
#include "StandardLib/Unknowns.h"
#include "SupportLib/Image.h"
#include "SupportLib/ImageReader.h"
#include "SupportLib/ImageWriter.h"
#include "SupportLib/ImageRGBToGrey.h"
#include "TestLib/Assert.h"
#include "TestImageRGBToGrey.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageRGBToGrey(void)
{
	BeginTests();

	CImage				cImage;
	CImageRGBToGrey		cRGBToGrey;

	cImage.Init(32, 32, PT_uchar, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, IMAGE_DIFFUSE_RED, CHANNEL_ZERO);
	ReadImage(&cImage, "Input\\RGBToGrey.png");

	cRGBToGrey.Init(RGBTGS_OnlyIfChannelsSame);
	cRGBToGrey.Modify(&cImage);
	cRGBToGrey.Kill();

	WriteImage(&cImage, "Output\\RGBToGrey.raw");
	AssertFileMemory("input\\RGBToGrey.raw", cImage.GetData(), cImage.GetByteSize());

	cImage.Kill();

	TestStatistics();
}

