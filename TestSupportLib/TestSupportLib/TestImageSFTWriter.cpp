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

	bResult = SaveSFTTransparentCel(pcImage, "Output\\Tiny.sft", 0, 0, pcImage->GetWidth(), pcImage->GetHeight());
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
void TestImageSFTWriter(void)
{
	BeginTests();

	DataIOInit();
	ObjectsInit();
	ImageChannelDescriptorInit();

	TestImageSFTWriter1();
	TestImageSFTWriter2();
	TestImageSFTWriter3();

	ImageChannelDescriptorKill();
	ObjectsKill();
	DataIOKill();

	TestStatistics();
}

