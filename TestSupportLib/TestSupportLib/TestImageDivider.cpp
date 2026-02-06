#include "BaseLib/FastFunctions.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/NaiveFile.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "StandardLib/Objects.h"
#include "SupportLib/ImageDivider.h"
#include "SupportLib/ImageReader.h"
#include "SupportLib/ImageWriter.h"
#include "SupportLib/ImageCelMask.h"
#include "SupportLib/ImageCelTransparent.h"
#include "SupportLib/ImageCelMaskTransparent.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageDividerGenerateFromBorder(void)
{
	CImageDivider		cImageDivider;
	Ptr<CImageCelMask>	pcRectangle;

	Ptr<CImage> pcImage = ReadImage("Input" _FS_ "splitter.png");
	Ptr<CImage> pcMask = OMalloc<CImage>();

	cImageDivider.Init(&pcImage);
	cImageDivider.GenerateFromBorder(pcMask);
	AssertInt(20, cImageDivider.GetDestImageCels()->NumElements());
	pcRectangle = cImageDivider.GetDestImageCels()->Get(0);
	AssertInt(1, pcRectangle->GetSubImage()->mcImageRect.miLeft);
	AssertInt(1, pcRectangle->GetSubImage()->mcImageRect.miTop);
	AssertInt(13, pcRectangle->GetSubImage()->mcImageRect.GetWidth());
	AssertInt(13, pcRectangle->GetSubImage()->mcImageRect.GetHeight());

	pcRectangle = cImageDivider.GetDestImageCels()->Get(1);
	AssertInt(15, pcRectangle->GetSubImage()->mcImageRect.miLeft);
	AssertInt(1, pcRectangle->GetSubImage()->mcImageRect.miTop);
	AssertInt(13, pcRectangle->GetSubImage()->mcImageRect.GetWidth());
	AssertInt(13, pcRectangle->GetSubImage()->mcImageRect.GetHeight());

	pcRectangle = cImageDivider.GetDestImageCels()->Get(17);
	AssertInt(21, pcRectangle->GetSubImage()->mcImageRect.miLeft);
	AssertInt(39, pcRectangle->GetSubImage()->mcImageRect.miTop);
	AssertInt(3, pcRectangle->GetSubImage()->mcImageRect.GetWidth());
	AssertInt(3, pcRectangle->GetSubImage()->mcImageRect.GetHeight());

	WriteImage(pcMask, "Output" _FS_ "splitter.raw");
	AssertFileMemory("input" _FS_ "splitter.raw", pcMask->mcChannels.GetData(), pcMask->GetByteSize());

	cImageDivider.Kill();
	pcMask = NULL;
	pcImage = NULL;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageDividerGenerateFromNumbers(void)
{
	CImageDivider			cImageDivider;
	Ptr<CImageCel>			pcImageCel;
	CImageDividerNumbers	cNumbers;

	Ptr<CImage> pcImage = ReadImage("Input" _FS_ "grid.png");


	//int iCelWidth, int iCelHeight, int iColumnCount, int iRowCount, int iLeftOffset, int iTopOffset, int iWidthSpacing, int iHeightSpacing

	cNumbers.InitGeneral(-1, -1, 4, 3, 0, 0, 0, 0);
	cImageDivider.Init(&pcImage, NULL);
	cImageDivider.GenerateFromNumbers(&cNumbers);
	AssertInt(12, cImageDivider.GetDestImageCels()->NumElements());
	pcImageCel = cImageDivider.GetDestImageCels()->Get(0);
	AssertInt(0, pcImageCel->GetSubImage()->mcImageRect.miLeft);
	AssertInt(0, pcImageCel->GetSubImage()->mcImageRect.miTop);
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetWidth());
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetHeight());

	pcImageCel = cImageDivider.GetDestImageCels()->Get(11);
	AssertInt(48, pcImageCel->GetSubImage()->mcImageRect.miLeft);
	AssertInt(32, pcImageCel->GetSubImage()->mcImageRect.miTop);
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetWidth());
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetHeight());
	cImageDivider.Kill();

	cNumbers.InitGeneral(16, 16, -1, -1, 0, 0, 0, 0);
	cImageDivider.Init(&pcImage, NULL);
	cImageDivider.GenerateFromNumbers(&cNumbers);
	AssertInt(12, cImageDivider.GetDestImageCels()->NumElements());
	pcImageCel = cImageDivider.GetDestImageCels()->Get(0);
	AssertInt(0, pcImageCel->GetSubImage()->mcImageRect.miLeft);
	AssertInt(0, pcImageCel->GetSubImage()->mcImageRect.miTop);
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetWidth());
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetHeight());

	pcImageCel = cImageDivider.GetDestImageCels()->Get(11);
	AssertInt(48, pcImageCel->GetSubImage()->mcImageRect.miLeft);
	AssertInt(32, pcImageCel->GetSubImage()->mcImageRect.miTop);
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetWidth());
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetHeight());
	cImageDivider.Kill();

	cNumbers.InitGeneral(16, 16, -1, -1, 0, 0, 16, 0);
	cImageDivider.Init(&pcImage, NULL);
	cImageDivider.GenerateFromNumbers(&cNumbers);
	AssertInt(6, cImageDivider.GetDestImageCels()->NumElements());
	pcImageCel = cImageDivider.GetDestImageCels()->Get(0);
	AssertInt(0, pcImageCel->GetSubImage()->mcImageRect.miLeft);
	AssertInt(0, pcImageCel->GetSubImage()->mcImageRect.miTop);
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetWidth());
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetHeight());

	pcImageCel = cImageDivider.GetDestImageCels()->Get(5);
	AssertInt(32, pcImageCel->GetSubImage()->mcImageRect.miLeft);
	AssertInt(32, pcImageCel->GetSubImage()->mcImageRect.miTop);
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetWidth());
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetHeight());
	cImageDivider.Kill();

	cNumbers.InitGeneral(16, 16, -1, -1, 0, 0, 0, 16);
	cImageDivider.Init(&pcImage, NULL);
	cImageDivider.GenerateFromNumbers(&cNumbers);
	AssertInt(8, cImageDivider.GetDestImageCels()->NumElements());
	pcImageCel = cImageDivider.GetDestImageCels()->Get(0);
	AssertInt(0, pcImageCel->GetSubImage()->mcImageRect.miLeft);
	AssertInt(0, pcImageCel->GetSubImage()->mcImageRect.miTop);
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetWidth());
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetHeight());

	pcImageCel = cImageDivider.GetDestImageCels()->Get(7);
	AssertInt(48, pcImageCel->GetSubImage()->mcImageRect.miLeft);
	AssertInt(32, pcImageCel->GetSubImage()->mcImageRect.miTop);
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetWidth());
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetHeight());
	cImageDivider.Kill();

	cNumbers.InitGeneral(16, 16, -1, -1, 16, 0, 0, 0);
	cImageDivider.Init(&pcImage, NULL);
	cImageDivider.GenerateFromNumbers(&cNumbers);
	AssertInt(9, cImageDivider.GetDestImageCels()->NumElements());
	pcImageCel = cImageDivider.GetDestImageCels()->Get(0);
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.miLeft);
	AssertInt(0, pcImageCel->GetSubImage()->mcImageRect.miTop);
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetWidth());
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetHeight());

	pcImageCel = cImageDivider.GetDestImageCels()->Get(8);
	AssertInt(48, pcImageCel->GetSubImage()->mcImageRect.miLeft);
	AssertInt(32, pcImageCel->GetSubImage()->mcImageRect.miTop);
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetWidth());
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetHeight());
	cImageDivider.Kill();

	cNumbers.InitGeneral(16, 16, -1, -1, 16, 0, 16, 0);
	cImageDivider.Init(&pcImage, NULL);
	cImageDivider.GenerateFromNumbers(&cNumbers);
	AssertInt(6, cImageDivider.GetDestImageCels()->NumElements());
	pcImageCel = cImageDivider.GetDestImageCels()->Get(0);
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.miLeft);
	AssertInt(0, pcImageCel->GetSubImage()->mcImageRect.miTop);
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetWidth());
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetHeight());

	pcImageCel = cImageDivider.GetDestImageCels()->Get(5);
	AssertInt(48, pcImageCel->GetSubImage()->mcImageRect.miLeft);
	AssertInt(32, pcImageCel->GetSubImage()->mcImageRect.miTop);
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetWidth());
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetHeight());
	cImageDivider.Kill();

	cNumbers.InitGeneral(-1, -1, 3, 3, 16, 0, 0, 0);
	cImageDivider.Init(&pcImage, NULL);
	cImageDivider.GenerateFromNumbers(&cNumbers);
	AssertInt(9, cImageDivider.GetDestImageCels()->NumElements());
	pcImageCel = cImageDivider.GetDestImageCels()->Get(0);
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.miLeft);
	AssertInt(0, pcImageCel->GetSubImage()->mcImageRect.miTop);
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetWidth());
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetHeight());

	pcImageCel = cImageDivider.GetDestImageCels()->Get(8);
	AssertInt(48, pcImageCel->GetSubImage()->mcImageRect.miLeft);
	AssertInt(32, pcImageCel->GetSubImage()->mcImageRect.miTop);
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetWidth());
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetHeight());
	cImageDivider.Kill();

	cNumbers.InitGeneral(-1, -1, 2, 3, 16, 0, 16, 0);
	cImageDivider.Init(&pcImage, NULL);
	cImageDivider.GenerateFromNumbers(&cNumbers);
	AssertInt(6, cImageDivider.GetDestImageCels()->NumElements());
	pcImageCel = cImageDivider.GetDestImageCels()->Get(0);
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.miLeft);
	AssertInt(0, pcImageCel->GetSubImage()->mcImageRect.miTop);
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetWidth());
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetHeight());

	pcImageCel = cImageDivider.GetDestImageCels()->Get(5);
	AssertInt(48, pcImageCel->GetSubImage()->mcImageRect.miLeft);
	AssertInt(32, pcImageCel->GetSubImage()->mcImageRect.miTop);
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetWidth());
	AssertInt(16, pcImageCel->GetSubImage()->mcImageRect.GetHeight());
	cImageDivider.Kill();

	pcImage = NULL;;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageDividerGenerateFromNumbersWithTransparent(void)
{
	CImageDivider			cImageDivider;
	Ptr<CImageCel>			pcImageCel;
	uint32					uiTransparent;
	CImageDividerNumbers	cNumbers;

	Ptr<CImage> pcImage = ReadImage("Input" _FS_ "grid.png");

	uiTransparent = 0x212121ff;
	cImageDivider.Init(&pcImage, (SImageColour*)&uiTransparent);

	cNumbers.InitGeneral(-1, -1, 4, 3, 0, 0, 0, 0);
	cImageDivider.GenerateFromNumbers(&cNumbers);
	AssertInt(12, cImageDivider.GetDestImageCels()->NumElements());
	pcImageCel = cImageDivider.GetDestImageCels()->Get(0);
	AssertInt(1, pcImageCel->GetSubImage()->mcImageRect.miLeft);
	AssertInt(1, pcImageCel->GetSubImage()->mcImageRect.miTop);
	AssertInt(14, pcImageCel->GetSubImage()->mcImageRect.GetWidth());
	AssertInt(14, pcImageCel->GetSubImage()->mcImageRect.GetHeight());

	pcImageCel = cImageDivider.GetDestImageCels()->Get(11);
	AssertInt(49, pcImageCel->GetSubImage()->mcImageRect.miLeft);
	AssertInt(32, pcImageCel->GetSubImage()->mcImageRect.miTop);
	AssertInt(14, pcImageCel->GetSubImage()->mcImageRect.GetWidth());
	AssertInt(15, pcImageCel->GetSubImage()->mcImageRect.GetHeight());
	cImageDivider.Kill();

	pcImage = NULL;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageDividerGenerateFromBorderWithTransparent(void)
{

	CImageDivider		cImageDivider;
	Ptr<CImageCelMask>	pcRectangle;
	uint32				uiTransparent;

	Ptr<CImage> pcImage = ReadImage("Input" _FS_ "cel6.png");
	Ptr<CImage> pcMask = OMalloc<CImage>();

	uiTransparent = 0x000000;
	cImageDivider.Init(&pcImage, (SImageColour*)&uiTransparent);
	cImageDivider.GenerateFromBorder(&pcMask);
	AssertInt(2, cImageDivider.GetDestImageCels()->NumElements());
	pcRectangle = cImageDivider.GetDestImageCels()->Get(0);
	AssertInt(4, pcRectangle->GetSubImage()->mcImageRect.miLeft);
	AssertInt(4, pcRectangle->GetSubImage()->mcImageRect.miTop);
	AssertInt(18, pcRectangle->GetSubImage()->mcImageRect.GetWidth());
	AssertInt(28, pcRectangle->GetSubImage()->mcImageRect.GetHeight());

	pcRectangle = cImageDivider.GetDestImageCels()->Get(1);
	AssertInt(9, pcRectangle->GetSubImage()->mcImageRect.miLeft);
	AssertInt(18, pcRectangle->GetSubImage()->mcImageRect.miTop);
	AssertInt(11, pcRectangle->GetSubImage()->mcImageRect.GetWidth());
	AssertInt(25, pcRectangle->GetSubImage()->mcImageRect.GetHeight());

	WriteImage(&pcMask, "Output" _FS_ "cel6.raw");
	AssertFileMemory("input" _FS_ "cel6.raw", pcMask->mcChannels.GetData(), pcMask->GetByteSize());

	cImageDivider.Kill();
	pcMask = NULL;
	pcImage = NULL;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageDivider(void)
{
	BeginTests();

	DataIOInit();
	ObjectsInit();

	TestImageDividerGenerateFromBorder();
	TestImageDividerGenerateFromNumbers();
	TestImageDividerGenerateFromNumbersWithTransparent();
	TestImageDividerGenerateFromBorderWithTransparent();

	ObjectsKill();
	DataIOKill();

	TestStatistics();
}

