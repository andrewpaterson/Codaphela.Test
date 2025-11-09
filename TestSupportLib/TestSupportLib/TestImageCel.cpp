#include "BaseLib/FastFunctions.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "StandardLib/Objects.h"
#include "SupportLib/ImageCel.h"
#include "SupportLib/ImageCelMask.h"
#include "SupportLib/ImageCelTransparent.h"
#include "SupportLib/ImageReader.h"
#include "SupportLib/ImageDivider.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageCelCropBorders(void)
{
	CImageCel	cCel;

	Ptr<CImage> pcImage = ReadImage("Input" _FS_ "cel1.png");
	cCel.Init(&pcImage);
	cCel.CropTransparentBorders();

	AssertInt(24, cCel.GetSubImage()->GetFullWidth());
	AssertInt(24, cCel.GetSubImage()->GetImageWidth());
	AssertInt(24, cCel.GetSubImage()->GetFullHeight());
	AssertInt(24, cCel.GetSubImage()->GetImageHeight());

	cCel.Kill();
	pcImage->Kill();

	pcImage = ReadImage("Input" _FS_ "cel2.png");
	cCel.Init(&pcImage);
	cCel.CropTransparentBorders();

	AssertInt(24, cCel.GetSubImage()->GetFullWidth());
	AssertInt(21, cCel.GetSubImage()->GetImageWidth());
	AssertInt(24, cCel.GetSubImage()->GetFullHeight());
	AssertInt(18, cCel.GetSubImage()->GetImageHeight());
	AssertInt(1, cCel.GetSubImage()->mcImageRect.miLeft);
	AssertInt(3, cCel.GetSubImage()->mcImageRect.miTop);

	cCel.Kill();
	pcImage->Kill();

	pcImage = ReadImage("Input" _FS_ "cel3.png");
	cCel.Init(&pcImage);
	cCel.CropTransparentBorders();

	AssertInt(24, cCel.GetSubImage()->GetFullWidth());
	AssertInt(0, cCel.GetSubImage()->GetImageWidth());
	AssertInt(24, cCel.GetSubImage()->GetFullHeight());
	AssertInt(0, cCel.GetSubImage()->GetImageHeight());
	AssertBool(true, cCel.GetSubImage()->IsImageEmpty());

	cCel.Kill();
	pcImage->Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageCelMaskCropBorders(void)
{
	CImageDivider	cDivider;
	CImageCelMask*	pcRect1;
	CImageCelMask*	pcRect2;

	Ptr<CImage> pcImage = ReadImage("Input" _FS_ "cel4.png");
	Ptr<CImage> pcMask = OMalloc<CImage>();

	cDivider.Init(&pcImage);
	cDivider.GenerateFromBorder(pcMask);
	
	AssertInt(2, cDivider.GetDestImageCels()->NumElements());
	pcRect1 = (CImageCelMask*)cDivider.GetDestImageCels()->UnsafeGet(0);
	pcRect2 = (CImageCelMask*)cDivider.GetDestImageCels()->UnsafeGet(1);
	AssertInt(1, pcRect1->GetMask());
	AssertInt(2, pcRect2->GetMask());

	AssertInt(36, pcRect1->GetSubImage()->GetFullWidth());
	AssertInt(28, pcRect1->GetSubImage()->GetImageWidth());
	AssertInt(22, pcRect1->GetSubImage()->GetFullHeight());
	AssertInt(18, pcRect1->GetSubImage()->GetImageHeight());

	AssertInt(31, pcRect2->GetSubImage()->GetFullWidth());
	AssertInt(25, pcRect2->GetSubImage()->GetImageWidth());
	AssertInt(22, pcRect2->GetSubImage()->GetFullHeight());
	AssertInt(11, pcRect2->GetSubImage()->GetImageHeight());

	cDivider.Kill();
	pcImage = NULL;
	pcMask = NULL;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageCelTransparentColourCropBorders(void)
{
	CImageCelTransparent	cCel;
	uint32					cBlack;

	cBlack = 0x5a000000;  //the 5a represents garbage.  Only the first three bytes are used.
	Ptr<CImage> pcImage = ReadImage("Input" _FS_ "cel5.png");
	cCel.Init(&pcImage, (SImageColour*)&cBlack);
	cCel.CropTransparentBorders();

	AssertInt(24, cCel.GetSubImage()->GetFullWidth());
	AssertInt(18, cCel.GetSubImage()->GetImageWidth());
	AssertInt(24, cCel.GetSubImage()->GetFullHeight());
	AssertInt(19, cCel.GetSubImage()->GetImageHeight());
	AssertInt(4, cCel.GetSubImage()->mcImageRect.miLeft);
	AssertInt(2, cCel.GetSubImage()->mcImageRect.miTop);

	cCel.Kill();
	pcImage->Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageCel(void)
{
	BeginTests();

	DataIOInit();
	ObjectsInit();

	TestImageCelCropBorders();
	TestImageCelMaskCropBorders();
	TestImageCelTransparentColourCropBorders();

	ObjectsKill();
	DataIOKill();

	TestStatistics();
}

