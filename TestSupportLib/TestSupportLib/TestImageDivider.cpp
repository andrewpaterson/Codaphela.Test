#include "stdafx.h"
#include "BaseLib/FastFunctions.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/NaiveFile.h"
#include "SupportLib/ImageDivider.h"
#include "SupportLib/ImageReader.h"
#include "SupportLib/ImageWriter.h"
#include "SupportLib/ImageCelMask.h"
#include "SupportLib/ImageCelTransparent.h"
#include "SupportLib/ImageCelMaskTransparent.h"
#include "TestLib/Assert.h"
#include "TestImageDivider.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageDividerGenerateFromBorder(void)
{

	CImageDivider	cImageDivider;
	CImage			cImage;
	CImage			cMask;
	CImageCelMask*	pcRectangle;

	ReadImage(&cImage, "Input\\splitter.png");

	cImageDivider.Init(&cImage);
	cImageDivider.GenerateFromBorder(&cMask);
	AssertInt(20, cImageDivider.GetDestImageCels()->NumElements());
	pcRectangle = (CImageCelMask*)cImageDivider.GetDestImageCels()->Get(0);
	AssertInt(1, pcRectangle->GetSubImage()->mcImageRect.miLeft);
	AssertInt(1, pcRectangle->GetSubImage()->mcImageRect.miTop);
	AssertInt(13, pcRectangle->GetSubImage()->mcImageRect.GetWidth());
	AssertInt(13, pcRectangle->GetSubImage()->mcImageRect.GetHeight());

	pcRectangle = (CImageCelMask*)cImageDivider.GetDestImageCels()->Get(1);
	AssertInt(15, pcRectangle->GetSubImage()->mcImageRect.miLeft);
	AssertInt(1, pcRectangle->GetSubImage()->mcImageRect.miTop);
	AssertInt(13, pcRectangle->GetSubImage()->mcImageRect.GetWidth());
	AssertInt(13, pcRectangle->GetSubImage()->mcImageRect.GetHeight());

	pcRectangle = (CImageCelMask*)cImageDivider.GetDestImageCels()->Get(17);
	AssertInt(21, pcRectangle->GetSubImage()->mcImageRect.miLeft);
	AssertInt(39, pcRectangle->GetSubImage()->mcImageRect.miTop);
	AssertInt(3, pcRectangle->GetSubImage()->mcImageRect.GetWidth());
	AssertInt(3, pcRectangle->GetSubImage()->mcImageRect.GetHeight());

	WriteImage(&cMask, "Output\\splitter.raw");
	AssertFileMemory("input\\splitter.raw", cMask.mcChannels.GetData(), cMask.GetByteSize());

	cImageDivider.Kill();
	cMask.Kill();
	cImage.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageDividerGenerateFromNumbers(void)
{
	CImageDivider			cImageDivider;
	CImage					cImage;
	CImageCel*				pcImageCel;
	CImageDividerNumbers	cNumbers;

	ReadImage(&cImage, "Input\\grid.png");


	//int iCelWidth, int iCelHeight, int iColumnCount, int iRowCount, int iLeftOffset, int iTopOffset, int iWidthSpacing, int iHeightSpacing

	cNumbers.InitGeneral(-1, -1, 4, 3, 0, 0, 0, 0);
	cImageDivider.Init(&cImage, NULL);
	cImageDivider.GenerateFromNumbers(&cNumbers);
	AssertInt(12, cImageDivider.GetDestImageCels()->NumElements());
	pcImageCel = (CImageCel*)cImageDivider.GetDestImageCels()->Get(0);
	AssertInt(0, pcImageCel->GetSubImage()->mcImageRect.miLeft);
	AssertInt(0, pcImageCel->GetSubImage()->mcImageRect.miTop);
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetWidth());
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetHeight());

	pcImageCel = (CImageCel*)cImageDivider.GetDestImageCels()->Get(11);
	AssertInt(48, pcImageCel->GetSubImage()->mcImageRect.miLeft);
	AssertInt(32, pcImageCel->GetSubImage()->mcImageRect.miTop);
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetWidth());
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetHeight());
	cImageDivider.Kill();

	cNumbers.InitGeneral(16, 16, -1, -1, 0, 0, 0, 0);
	cImageDivider.Init(&cImage, NULL);
	cImageDivider.GenerateFromNumbers(&cNumbers);
	AssertInt(12, cImageDivider.GetDestImageCels()->NumElements());
	pcImageCel = (CImageCel*)cImageDivider.GetDestImageCels()->Get(0);
	AssertInt(0, pcImageCel->GetSubImage()->mcImageRect.miLeft);
	AssertInt(0, pcImageCel->GetSubImage()->mcImageRect.miTop);
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetWidth());
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetHeight());

	pcImageCel = (CImageCel*)cImageDivider.GetDestImageCels()->Get(11);
	AssertInt(48, pcImageCel->GetSubImage()->mcImageRect.miLeft);
	AssertInt(32, pcImageCel->GetSubImage()->mcImageRect.miTop);
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetWidth());
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetHeight());
	cImageDivider.Kill();

	cNumbers.InitGeneral(16, 16, -1, -1, 0, 0, 16, 0);
	cImageDivider.Init(&cImage, NULL);
	cImageDivider.GenerateFromNumbers(&cNumbers);
	AssertInt(6, cImageDivider.GetDestImageCels()->NumElements());
	pcImageCel = (CImageCel*)cImageDivider.GetDestImageCels()->Get(0);
	AssertInt(0, pcImageCel->GetSubImage()->mcImageRect.miLeft);
	AssertInt(0, pcImageCel->GetSubImage()->mcImageRect.miTop);
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetWidth());
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetHeight());

	pcImageCel = (CImageCel*)cImageDivider.GetDestImageCels()->Get(5);
	AssertInt(32, pcImageCel->GetSubImage()->mcImageRect.miLeft);
	AssertInt(32, pcImageCel->GetSubImage()->mcImageRect.miTop);
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetWidth());
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetHeight());
	cImageDivider.Kill();

	cNumbers.InitGeneral(16, 16, -1, -1, 0, 0, 0, 16);
	cImageDivider.Init(&cImage, NULL);
	cImageDivider.GenerateFromNumbers(&cNumbers);
	AssertInt(8, cImageDivider.GetDestImageCels()->NumElements());
	pcImageCel = (CImageCel*)cImageDivider.GetDestImageCels()->Get(0);
	AssertInt(0, pcImageCel->GetSubImage()->mcImageRect.miLeft);
	AssertInt(0, pcImageCel->GetSubImage()->mcImageRect.miTop);
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetWidth());
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetHeight());

	pcImageCel = (CImageCel*)cImageDivider.GetDestImageCels()->Get(7);
	AssertInt(48, pcImageCel->GetSubImage()->mcImageRect.miLeft);
	AssertInt(32, pcImageCel->GetSubImage()->mcImageRect.miTop);
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetWidth());
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetHeight());
	cImageDivider.Kill();

	cNumbers.InitGeneral(16, 16, -1, -1, 16, 0, 0, 0);
	cImageDivider.Init(&cImage, NULL);
	cImageDivider.GenerateFromNumbers(&cNumbers);
	AssertInt(9, cImageDivider.GetDestImageCels()->NumElements());
	pcImageCel = (CImageCel*)cImageDivider.GetDestImageCels()->Get(0);
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.miLeft);
	AssertInt(0, pcImageCel->GetSubImage()->mcImageRect.miTop);
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetWidth());
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetHeight());

	pcImageCel = (CImageCel*)cImageDivider.GetDestImageCels()->Get(8);
	AssertInt(48, pcImageCel->GetSubImage()->mcImageRect.miLeft);
	AssertInt(32, pcImageCel->GetSubImage()->mcImageRect.miTop);
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetWidth());
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetHeight());
	cImageDivider.Kill();

	cNumbers.InitGeneral(16, 16, -1, -1, 16, 0, 16, 0);
	cImageDivider.Init(&cImage, NULL);
	cImageDivider.GenerateFromNumbers(&cNumbers);
	AssertInt(6, cImageDivider.GetDestImageCels()->NumElements());
	pcImageCel = (CImageCel*)cImageDivider.GetDestImageCels()->Get(0);
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.miLeft);
	AssertInt(0, pcImageCel->GetSubImage()->mcImageRect.miTop);
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetWidth());
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetHeight());

	pcImageCel = (CImageCel*)cImageDivider.GetDestImageCels()->Get(5);
	AssertInt(48, pcImageCel->GetSubImage()->mcImageRect.miLeft);
	AssertInt(32, pcImageCel->GetSubImage()->mcImageRect.miTop);
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetWidth());
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetHeight());
	cImageDivider.Kill();

	cNumbers.InitGeneral(-1, -1, 3, 3, 16, 0, 0, 0);
	cImageDivider.Init(&cImage, NULL);
	cImageDivider.GenerateFromNumbers(&cNumbers);
	AssertInt(9, cImageDivider.GetDestImageCels()->NumElements());
	pcImageCel = (CImageCel*)cImageDivider.GetDestImageCels()->Get(0);
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.miLeft);
	AssertInt(0, pcImageCel->GetSubImage()->mcImageRect.miTop);
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetWidth());
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetHeight());

	pcImageCel = (CImageCel*)cImageDivider.GetDestImageCels()->Get(8);
	AssertInt(48, pcImageCel->GetSubImage()->mcImageRect.miLeft);
	AssertInt(32, pcImageCel->GetSubImage()->mcImageRect.miTop);
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetWidth());
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetHeight());
	cImageDivider.Kill();

	cNumbers.InitGeneral(-1, -1, 2, 3, 16, 0, 16, 0);
	cImageDivider.Init(&cImage, NULL);
	cImageDivider.GenerateFromNumbers(&cNumbers);
	AssertInt(6, cImageDivider.GetDestImageCels()->NumElements());
	pcImageCel = (CImageCel*)cImageDivider.GetDestImageCels()->Get(0);
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.miLeft);
	AssertInt(0, pcImageCel->GetSubImage()->mcImageRect.miTop);
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetWidth());
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetHeight());

	pcImageCel = (CImageCel*)cImageDivider.GetDestImageCels()->Get(5);
	AssertInt(48, pcImageCel->GetSubImage()->mcImageRect.miLeft);
	AssertInt(32, pcImageCel->GetSubImage()->mcImageRect.miTop);
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetWidth());
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetHeight());
	cImageDivider.Kill();

	cImage.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageDividerGenerateFromNumbersWithTransparent(void)
{
	CImageDivider			cImageDivider;
	CImage					cImage;
	CImageCel*				pcImageCel;
	uint32			uiTransparent;
	CImageDividerNumbers	cNumbers;

	ReadImage(&cImage, "Input\\grid.png");

	uiTransparent = 0x212121ff;
	cImageDivider.Init(&cImage, (SImageColour*)&uiTransparent);

	cNumbers.InitGeneral(-1, -1, 4, 3, 0, 0, 0, 0);
	cImageDivider.GenerateFromNumbers(&cNumbers);
	AssertInt(12, cImageDivider.GetDestImageCels()->NumElements());
	pcImageCel = (CImageCel*)cImageDivider.GetDestImageCels()->Get(0);
	AssertInt(1, pcImageCel->GetSubImage()->mcImageRect.miLeft);
	AssertInt(1, pcImageCel->GetSubImage()->mcImageRect.miTop);
	AssertInt(14, pcImageCel->GetSubImage()->mcImageRect.GetWidth());
	AssertInt(14, pcImageCel->GetSubImage()->mcImageRect.GetHeight());

	pcImageCel = (CImageCel*)cImageDivider.GetDestImageCels()->Get(11);
	AssertInt(49, pcImageCel->GetSubImage()->mcImageRect.miLeft);
	AssertInt(32, pcImageCel->GetSubImage()->mcImageRect.miTop);
	AssertInt(14, pcImageCel->GetSubImage()->mcImageRect.GetWidth());
	AssertInt(15, pcImageCel->GetSubImage()->mcImageRect.GetHeight());
	cImageDivider.Kill();

	cImage.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageDividerGenerateFromBorderWithTransparent(void)
{

	CImageDivider	cImageDivider;
	CImage			cImage;
	CImageCelMask*	pcRectangle;
	uint32	uiTransparent;
	CImage			cMask;

	ReadImage(&cImage, "Input\\cel6.png");

	uiTransparent = 0x000000;
	cImageDivider.Init(&cImage, (SImageColour*)&uiTransparent);
	cImageDivider.GenerateFromBorder(&cMask);
	AssertInt(2, cImageDivider.GetDestImageCels()->NumElements());
	pcRectangle = (CImageCelMask*)cImageDivider.GetDestImageCels()->Get(0);
	AssertInt(4, pcRectangle->GetSubImage()->mcImageRect.miLeft);
	AssertInt(4, pcRectangle->GetSubImage()->mcImageRect.miTop);
	AssertInt(18, pcRectangle->GetSubImage()->mcImageRect.GetWidth());
	AssertInt(28, pcRectangle->GetSubImage()->mcImageRect.GetHeight());

	pcRectangle = (CImageCelMask*)cImageDivider.GetDestImageCels()->Get(1);
	AssertInt(9, pcRectangle->GetSubImage()->mcImageRect.miLeft);
	AssertInt(18, pcRectangle->GetSubImage()->mcImageRect.miTop);
	AssertInt(11, pcRectangle->GetSubImage()->mcImageRect.GetWidth());
	AssertInt(25, pcRectangle->GetSubImage()->mcImageRect.GetHeight());

	WriteImage(&cMask, "Output\\cel6.raw");
	AssertFileMemory("input\\cel6.raw", cMask.mcChannels.GetData(), cMask.GetByteSize());

	cImageDivider.Kill();
	cMask.Kill();
	cImage.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageDivider(void)
{
	BeginTests();

	TestImageDividerGenerateFromBorder();
	TestImageDividerGenerateFromNumbers();
	TestImageDividerGenerateFromNumbersWithTransparent();
	TestImageDividerGenerateFromBorderWithTransparent();

	TestStatistics();
}

