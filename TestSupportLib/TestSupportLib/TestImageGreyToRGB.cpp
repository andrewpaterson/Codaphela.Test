#include "stdafx.h"
#include "BaseLib/NaiveFile.h"
#include "StandardLib/Unknowns.h"
#include "SupportLib/Image.h"
#include "SupportLib/ImageReader.h"
#include "SupportLib/ImageWriter.h"
#include "SupportLib/ImageGreyToRGB.h"
#include "TestLib/Assert.h"
#include "TestImageGreyToRGB.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageGreyToRGB(void)
{
	BeginTests();

	CImage				cImage;
	CImageGreyToRGB		cGreyToRGB;

	ReadImage(&cImage, "Input/basn0g08.png");

	cGreyToRGB.Init();
	cGreyToRGB.Modify(&cImage);
	cGreyToRGB.Kill();

	WriteImage(&cImage, "Output/GreyToRGB.raw");
	AssertFileMemory("input/GreyToRGB.raw", cImage.GetData(), cImage.GetByteSize());

	cGreyToRGB.Kill();
	cImage.Kill();

	TestStatistics();
}

