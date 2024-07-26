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
void TestImageSFTWriterTinyTransparent(void)
{
	bool		bResult;
	CNaiveFile	cNaiveFile;

	Ptr<CImage> pcImage = ReadImage("Input\\Tiny.png", IT_Unknown, true);
	AssertTrue(pcImage.IsNotNull());

	bResult = SaveSFT(pcImage, "Output\\Tiny.sft", true);
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
void TestImageSFTWriterTransparent(void)
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
void TestImageSFTWriterOpaque(void)
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
void TestImageSFTWriterTransparentCelContainer(void)
{
	bool					bResult;
	CImageDivider			cImageDivider;
	CImageDividerNumbers	cNumbers;
	CArrayUnknown*			pacImageCels;
	CImageCel*				pcImageCel;
	CFileUtil				cFileUtil;

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

	cFileUtil.Delete("Output\\MakiWalk.sft");
	cFileUtil.Delete("Output\\MakiWalk.png");

	bResult = SaveSFT(pacImageCels, "Output\\MakiWalk.sft");
	AssertTrue(bResult);

	AssertFile("Input\\MakiWalk-expected.sft", "Output\\MakiWalk.sft")

	pcImage = NULL;

	pcImage = LoadSFT("Output\\MakiWalk.sft");
	WriteImage(pcImage, "Output\\MakiWalk.png", IT_PNG);

	pcImage = NULL;

	AssertFile("Input\\MakiWalk-expected.png", "Output\\MakiWalk.png")
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageSFTWriterMultiSourceCelContainer(void)
{
	bool					bResult;
	CImageDivider			cImageDivider;
	CImageDividerNumbers	cNumbers;
	CArrayUnknown*			pacMakiWalkCels;
	CImageCel*				pcImageCel;
	CFileUtil				cFileUtil;
	CArrayUnknown			acImageCels;

	Ptr<CImage> pcBackground = ReadImage("Input\\Fighting320.png", IT_Unknown, true);
	AssertTrue(pcBackground.IsNotNull());

	Ptr<CImage> pcMakiStand = ReadImage("Input\\MakiStand.png", IT_Unknown, true);
	AssertTrue(pcMakiStand.IsNotNull());

	Ptr<CImage> pcMakiWalk = ReadImage("Input\\MakiWalk.png", IT_Unknown, true);
	AssertTrue(pcMakiWalk.IsNotNull());

	cNumbers.InitGeneral(-1, -1, 6, 1, 0, 0, 0, 0);
	cImageDivider.Init(&pcMakiWalk, NULL);
	cImageDivider.GenerateFromNumbers(&cNumbers);
	pacMakiWalkCels = cImageDivider.GetDestImageCels();

	acImageCels.Init();
	pcImageCel = acImageCels.Add<CImageCel>();
	pcImageCel->Init(pcBackground);

	pcImageCel = acImageCels.Add<CImageCel>();
	pcImageCel->Init(pcMakiStand);

	acImageCels.AddAll(pacMakiWalkCels);

	cFileUtil.Delete("Output\\Combined.sft");
	cFileUtil.Delete("Output\\Combined.png");

	bResult = SaveSFT(&acImageCels, "Output\\Combined.sft");
	AssertTrue(bResult);

	AssertFile("Input\\Combined-expected.sft", "Output\\Combined.sft")


	Ptr<CImage> pcImage = LoadSFT("Output\\Combined.sft");
	WriteImage(pcImage, "Output\\Combined.png", IT_PNG);

	pcImage = NULL;

	AssertFile("Input\\Combined-expected.png", "Output\\Combined.png")
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

	TestImageSFTWriterTinyTransparent();
	TestImageSFTWriterTransparent();
	TestImageSFTWriterOpaque();
	TestImageSFTWriterTransparentCelContainer();
	TestImageSFTWriterMultiSourceCelContainer();

	ImageChannelDescriptorKill();
	ObjectsKill();
	DataIOKill();

	TestStatistics();
}

