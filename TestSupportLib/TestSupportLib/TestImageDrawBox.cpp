#include "stdafx.h"
#include "BaseLib/FastFunctions.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/NaiveFile.h"
#include "BaseLib/TypeConverter.h"
#include "StandardLib/Unknowns.h"
#include "SupportLib/ImageReader.h"
#include "SupportLib/ImageWriter.h"
#include "SupportLib/ImageDrawBox.h"
#include "TestLib/Assert.h"
#include "TestImageDrawBox.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageDrawBox(void)
{
	BeginTests();

	CImage				cImage;
	CImageDrawBox		cBox;
	CRectangle			cRect;
	CImageColourRGB		cRGB;

	cImage.Init();
	cImage.BeginChange();
	cImage.AddChannel(IMAGE_NORMAL_X, PT_uint16);
	cImage.AddChannel(IMAGE_NORMAL_Y, PT_uint16);
	cImage.AddChannel(IMAGE_NORMAL_Z, PT_uint16);
	cImage.AddChannel(IMAGE_DIFFUSE_BLUE, PT_uint8);
	cImage.AddChannel(IMAGE_DIFFUSE_GREEN, PT_uint8);
	cImage.AddChannel(IMAGE_DIFFUSE_RED, PT_uint8);
	cImage.SetSize(4, 4);
	cImage.EndChange();
	cImage.Clear();

	cRect.Init(1, 1, 3, 3);  //End not inclusive.
	cRGB.Init(0.9f, 0.2f, 0.25f);
	cBox.Init(&cRect, &cRGB);
	cBox.Modify(&cImage);

	WriteImage(&cImage, "Output\\Box.png");
	AssertFileMemory("input\\Box.raw", cImage.GetData(), cImage.GetByteSize());

	cImage.BeginChange();
	cImage.SetSize(8, 8);  //Oops, Set size does not preserve the image.  Also Write Image cannot write out non *4 sized pngs.
	cImage.EndChange();
	cImage.Clear();
	cBox.Modify(&cImage);
	cBox.Kill();

	cRect.Init(1, 1, 4, 4);  //End not inclusive.
	cRGB.Init(0.5f, 0.6f, 0.7f);
	cBox.Init(&cRect, &cRGB, false);
	cBox.Modify(&cImage);
	cBox.Kill();

	WriteImage(&cImage, "Output\\BoxBorder.png");
	AssertFileMemory("input\\BoxBorder.raw", cImage.GetData(), cImage.GetByteSize());

	cImage.Kill();

	TestStatistics();
}

