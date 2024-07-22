#include "SupportLib/Image.h"
#include "BaseLib/FastFunctions.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/NaiveFile.h"
#include "StandardLib/Objects.h"
#include "SupportLib/ImageReader.h"
#include "SupportLib/ImageWriter.h"
#include "SupportLib/SFTReader.h"
#include "SupportLib/SFTWriter.h"
#include "SupportLib/ImageDivider.h"
#include "SupportLib/ImageCel.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageSFTWriter1(void)
{
	bool		bResult;
	CNaiveFile	cNaiveFile;

	Ptr<CImage> pcImage = ReadImage("Input\\Tiny.png", IT_Unknown, true);
	AssertTrue(pcImage.IsNotNull());

	bResult = SaveSFTTransparent(pcImage, "Output\\Tiny.sft");
	AssertTrue(bResult);

	pcImage = NULL;

	AssertFile("Input\\Tiny-expected.sft", "Output\\Tiny.sft")

	pcImage = LoadSFT("Output\\Tiny.sft");

	cNaiveFile.Init(pcImage->GetData(), pcImage->GetByteSize());
	cNaiveFile.Write("Output\\Tiny.raw");
	cNaiveFile.KillExceptBuffer();

	pcImage = NULL;

	AssertFile("Input\\Tiny-expected.raw", "Output\\Tiny.raw")
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageSFTWriter2(void)
{
	bool		bResult;

	Ptr<CImage> pcImage = ReadImage("Input\\MakiStand.png", IT_Unknown, true);
	AssertTrue(pcImage.IsNotNull());

	bResult = SaveSFT(pcImage, "Output\\MakiStand.sft");
	AssertTrue(bResult);

	AssertFile("Input\\MakiStand-expected.sft", "Output\\MakiStand.sft")

	pcImage = NULL;

	pcImage = LoadSFT("Output\\MakiStand.sft");
	WriteImage(pcImage, "Output\\MakiStand.png", IT_PNG);

	pcImage = NULL;

	AssertFile("Input\\MakiStand-expected.png", "Output\\MakiStand.png")
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageSFTWriter3(void)
{
	bool		bResult;

	Ptr<CImage> pcImage = ReadImage("Input\\Fighting320.png", IT_Unknown, true);
	AssertTrue(pcImage.IsNotNull());

	bResult = SaveSFT(pcImage, "Output\\Fighting320.sft");
	AssertTrue(bResult);

	AssertFile("Input\\Fighting320-expected.sft", "Output\\Fighting320.sft")

		pcImage = NULL;

	pcImage = LoadSFT("Output\\Fighting320.sft");
	WriteImage(pcImage, "Output\\Fighting320.png", IT_PNG);

	pcImage = NULL;

	AssertFile("Input\\Fighting320-expected.png", "Output\\Fighting320.png")
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageSFTWriter4(void)
{
	bool					bResult;
	CImageDivider			cImageDivider;
	CImageDividerNumbers	cNumbers;
	CArrayUnknown*			pacImageCels;
	CImageCel*				pcImageCel;

	Ptr<CImage> pcImage = ReadImage("Input\\MakiWalk.png", IT_Unknown, true);
	AssertTrue(pcImage.IsNotNull());

	cNumbers.InitGeneral(-1, -1, 6, 1, 0, 0, 0, 0);
	cImageDivider.Init(&pcImage, NULL);
	cImageDivider.GenerateFromNumbers(&cNumbers);
	pacImageCels = cImageDivider.GetDestImageCels();

	AssertSize(6, pacImageCels->NumElements());
	pcImageCel = (CImageCel*)pacImageCels->Get(0);

	AssertSize(42, pcImageCel->GetSubImage()->GetFullWidth());
	AssertSize(32, pcImageCel->GetSubImage()->GetImageWidth());
	AssertSize(91, pcImageCel->GetSubImage()->GetFullHeight());
	AssertSize(90, pcImageCel->GetSubImage()->GetImageHeight());

	bResult = SaveSFT(pacImageCels, "Output\\MakiStand.sft");
	AssertTrue(bResult);

	AssertFile("Input\\MakiStand-expected.sft", "Output\\MakiStand.sft")

	pcImage = NULL;

	pcImage = LoadSFT("Output\\MakiStand.sft");
	WriteImage(pcImage, "Output\\MakiStand.png", IT_PNG);

	pcImage = NULL;

	AssertFile("Input\\MakiStand-expected.png", "Output\\MakiStand.png")
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageSFTWriter(void)
{
	BeginTests();

	DataIOInit();
	ObjectsInit();
	ImageChannelDescriptorInit();

	TestImageSFTWriter1();
	TestImageSFTWriter2();
	TestImageSFTWriter3();
	TestImageSFTWriter4();

	ImageChannelDescriptorKill();
	ObjectsKill();
	DataIOKill();

	TestStatistics();
}

