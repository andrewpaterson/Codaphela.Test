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

	Ptr<CImage> pcImage = ReadImage("Input" _FS_ "Tiny.png", IT_Unknown, true);
	AssertTrue(pcImage.IsNotNull());

	bResult = SaveSFT(pcImage, "Output" _FS_ "Tiny.sft", true);
	AssertTrue(bResult);

	pcImage = NULL;

	AssertFile("Input" _FS_ "Tiny-expected.sft", "Output" _FS_ "Tiny.sft")

	pcImage = LoadSFT("Output" _FS_ "Tiny.sft");

	cNaiveFile.Init(pcImage->GetData(), pcImage->GetByteSize());
	cNaiveFile.Write("Output" _FS_ "Tiny.raw");
	cNaiveFile.KillExceptBuffer();

	pcImage = NULL;

	AssertFile("Input" _FS_ "Tiny-expected.raw", "Output" _FS_ "Tiny.raw")
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageSFTWriterTransparent(void)
{
	bool		bResult;

	Ptr<CImage> pcImage = ReadImage("Input" _FS_ "MakiStand.png", IT_Unknown, true);
	AssertTrue(pcImage.IsNotNull());

	bResult = SaveSFT(pcImage, "Output" _FS_ "MakiStand.sft");
	AssertTrue(bResult);

	AssertFile("Input" _FS_ "MakiStand-expected.sft", "Output" _FS_ "MakiStand.sft")

	pcImage = NULL;

	pcImage = LoadSFT("Output" _FS_ "MakiStand.sft");
	WriteImage(pcImage, "Output" _FS_ "MakiStand.png", IT_PNG);

	pcImage = NULL;

	AssertFile("Input" _FS_ "MakiStand-expected.png", "Output" _FS_ "MakiStand.png")
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageSFTWriterOpaque(void)
{
	bool		bResult;

	Ptr<CImage> pcImage = ReadImage("Input" _FS_ "Fighting320.png", IT_Unknown, true);
	AssertTrue(pcImage.IsNotNull());

	bResult = SaveSFT(pcImage, "Output" _FS_ "Fighting320.sft");
	AssertTrue(bResult);

	AssertFile("Input" _FS_ "Fighting320-expected.sft", "Output" _FS_ "Fighting320.sft")

	pcImage = NULL;

	pcImage = LoadSFT("Output" _FS_ "Fighting320.sft");
	WriteImage(pcImage, "Output" _FS_ "Fighting320.png", IT_PNG);

	pcImage = NULL;

	AssertFile("Input" _FS_ "Fighting320-expected.png", "Output" _FS_ "Fighting320.png")
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

	Ptr<CImage> pcImage = ReadImage("Input" _FS_ "MakiWalk.png", IT_Unknown, true);
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

	cFileUtil.Delete("Output" _FS_ "MakiWalk.sft");
	cFileUtil.Delete("Output" _FS_ "MakiWalk.png");

	bResult = SaveSFT(pacImageCels, "Output" _FS_ "MakiWalk.sft");
	AssertTrue(bResult);

	AssertFile("Input" _FS_ "MakiWalk-expected.sft", "Output" _FS_ "MakiWalk.sft")

	pcImage = NULL;

	pcImage = LoadSFT("Output" _FS_ "MakiWalk.sft");
	WriteImage(pcImage, "Output" _FS_ "MakiWalk.png", IT_PNG);

	pcImage = NULL;

	AssertFile("Input" _FS_ "MakiWalk-expected.png", "Output" _FS_ "MakiWalk.png")
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

	Ptr<CImage> pcBackground = ReadImage("Input" _FS_ "Fighting320.png", IT_Unknown, true);
	AssertTrue(pcBackground.IsNotNull());

	Ptr<CImage> pcMakiStand = ReadImage("Input" _FS_ "MakiStand.png", IT_Unknown, true);
	AssertTrue(pcMakiStand.IsNotNull());

	Ptr<CImage> pcMakiWalk = ReadImage("Input" _FS_ "MakiWalk.png", IT_Unknown, true);
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

	cFileUtil.Delete("Output" _FS_ "Combined.sft");
	cFileUtil.Delete("Output" _FS_ "Combined.png");

	bResult = SaveSFT(&acImageCels, "Output" _FS_ "Combined.sft");
	AssertTrue(bResult);

	AssertFile("Input" _FS_ "Combined-expected.sft", "Output" _FS_ "Combined.sft")


	Ptr<CImage> pcImage = LoadSFT("Output" _FS_ "Combined.sft");
	WriteImage(pcImage, "Output" _FS_ "Combined.png", IT_PNG);

	pcImage = NULL;

	AssertFile("Input" _FS_ "Combined-expected.png", "Output" _FS_ "Combined.png")
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

