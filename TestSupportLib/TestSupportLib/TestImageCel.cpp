#include "BaseLib/FastFunctions.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "StandardLib/Objects.h"
#include "SupportLib/ImageCel.h"
#include "SupportLib/ImageCelMask.h"
#include "SupportLib/ImageCelTransparent.h"
#include "SupportLib/ImageReader.h"
#include "SupportLib/ImageDivider.h"
#include "TestLib/Assert.h"
#include "TestImageCel.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageCelCropBorders(void)
{
	CImageCel	cCel;
	CImage		cImage;

	ReadImage(&cImage, "Input\\cel1.png");
	cCel.Init(&cImage);
	cCel.CropTransparentBorders();

	AssertInt(24, cCel.GetSubImage()->GetFullWidth());
	AssertInt(24, cCel.GetSubImage()->GetImageWidth());
	AssertInt(24, cCel.GetSubImage()->GetFullHeight());
	AssertInt(24, cCel.GetSubImage()->GetImageHeight());

	cCel.Kill();
	cImage.Kill();

	ReadImage(&cImage, "Input\\cel2.png");
	cCel.Init(&cImage);
	cCel.CropTransparentBorders();

	AssertInt(24, cCel.GetSubImage()->GetFullWidth());
	AssertInt(21, cCel.GetSubImage()->GetImageWidth());
	AssertInt(24, cCel.GetSubImage()->GetFullHeight());
	AssertInt(18, cCel.GetSubImage()->GetImageHeight());
	AssertInt(1, cCel.GetSubImage()->mcImageRect.miLeft);
	AssertInt(3, cCel.GetSubImage()->mcImageRect.miTop);

	cCel.Kill();
	cImage.Kill();

	ReadImage(&cImage, "Input\\cel3.png");
	cCel.Init(&cImage);
	cCel.CropTransparentBorders();

	AssertInt(24, cCel.GetSubImage()->GetFullWidth());
	AssertInt(0, cCel.GetSubImage()->GetImageWidth());
	AssertInt(24, cCel.GetSubImage()->GetFullHeight());
	AssertInt(0, cCel.GetSubImage()->GetImageHeight());
	AssertBool(true, cCel.GetSubImage()->IsImageEmpty());

	cCel.Kill();
	cImage.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageCelMaskCropBorders(void)
{
	CImage			cImage;
	CImageDivider	cDivider;
	CImageCelMask*	pcRect1;
	CImageCelMask*	pcRect2;
	CImage			cMask;

	ReadImage(&cImage, "Input\\cel4.png");

	cDivider.Init(&cImage);
	cDivider.GenerateFromBorder(&cMask);
	
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

	cMask.Kill();
	cImage.Kill();
	cDivider.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageCelTransparentColourCropBorders(void)
{
	CImageCelTransparent	cCel;
	CImage					cImage;
	uint32			cBlack;

	cBlack = 0x5a000000;  //the 5a represents garbage.  Only the first three bytes are used.
	ReadImage(&cImage, "Input\\cel5.png");
	cCel.Init(&cImage, (SImageColour*)&cBlack);
	cCel.CropTransparentBorders();

	AssertInt(24, cCel.GetSubImage()->GetFullWidth());
	AssertInt(18, cCel.GetSubImage()->GetImageWidth());
	AssertInt(24, cCel.GetSubImage()->GetFullHeight());
	AssertInt(19, cCel.GetSubImage()->GetImageHeight());
	AssertInt(4, cCel.GetSubImage()->mcImageRect.miLeft);
	AssertInt(2, cCel.GetSubImage()->mcImageRect.miTop);

	cCel.Kill();
	cImage.Kill();
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

