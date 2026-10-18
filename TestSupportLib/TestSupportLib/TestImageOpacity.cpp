#include "BaseLib/NaiveFile.h"
#include "BaseLib/PointerRemapper.h"
#include "BaseLib/FastFunctions.h"
#include "BaseLib/Operators.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "StandardLib/Unknowns.h"
#include "StandardLib/Objects.h"
#include "StandardLib/ChannelsAccessorContiguous.h"
#include "StandardLib/ChannelsAccessorCreatorParams.h"
#include "SupportLib/Image.h"
#include "SupportLib/ImageReader.h"
#include "SupportLib/ImageAccessorCreator.h"
#include "SupportLib/ImageModifierDrawBox.h"
#include "SupportLib/ImageCopier.h"
#include "SupportLib/ImageBlitter.h"
#include "SupportLib/ImageWriter.h"
#include "SupportLib/ImageRowBlitterFactory.h"
#include "TestLib/Assert.h"
#include "TestLib/AssertFile.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
Ptr<CImage> TestImageOpacityReadImage(char* szFilename)
{
	CFileUtil			cFileUtil;
	CChars				szInputFilename;
	Ptr<CImage>			pBackground;

	szInputFilename.Init();
	cFileUtil.CurrentDirectory(&szInputFilename);
	cFileUtil.AppendToPath(&szInputFilename, "Input");
	cFileUtil.AppendToPath(&szInputFilename, szFilename);
	AssertTrue(cFileUtil.Exists(szInputFilename.Text()));

	pBackground = ReadImage(szInputFilename.Text(), IT_Unknown, true);
	AssertTrue(pBackground.IsNotNull());
	szInputFilename.Kill();

	return pBackground;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageOpacityBlitter(char* szDirectory, char* szInputPathName, char* szTestFilename, int32 x, int32 y)
{
	CFileUtil			cFileUtil;

	AssertTrue(cFileUtil.RemoveDir(szDirectory));
	AssertTrue(cFileUtil.TouchDir(szDirectory));

	ObjectsInit();
	{
		Ptr<CImage>		pBackgroundImage;
		Ptr<CImage>		pMakiImage;
		Ptr<CImageCel>	pBackgroundCel;
		Ptr<CImageCel>	pMakiCel;
		CArrayChannel	asChannels;
		SChannel*		psChannel;
		Ptr<CImage>		pDestImage;
		size			uiWidth;
		size			uiHeight;
		CImageBlitter	cBlitter;
		CChars			szOutputFilename;
		CChars			szInputFilename;
		bool			bWritten;
		bool			bResult;

		pBackgroundImage = TestImageOpacityReadImage("Fighting320.png");
		pMakiImage = TestImageOpacityReadImage(szInputPathName);

		asChannels.Init();
		pBackgroundImage->GetAllChannels(&asChannels);
		AssertSize(3, asChannels.NumElements());
		psChannel = asChannels.Get(0);
		AssertSize(IMAGE_DIFFUSE_RED, psChannel->iChannel);
		AssertInt(PT_uint8, psChannel->eType);
		AssertFalse(psChannel->bReverse);
		asChannels.Kill();

		asChannels.Init();
		pMakiImage->GetAllChannels(&asChannels);
		AssertSize(4, asChannels.NumElements());
		psChannel = asChannels.Get(0);
		AssertSize(IMAGE_OPACITY, psChannel->iChannel);
		AssertInt(PT_uint8, psChannel->eType);
		AssertFalse(psChannel->bReverse);
		asChannels.Kill();


		uiWidth = pBackgroundImage->GetWidth();
		uiHeight = pBackgroundImage->GetHeight();
		pDestImage = OMalloc<CImage>(uiWidth, uiHeight, PT_uint8, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, CHANNEL_STOP);
		pDestImage->Black();

		pBackgroundCel = OMalloc<CImageCel>(pBackgroundImage);
		pMakiCel = OMalloc<CImageCel>(pMakiImage, true);

		cBlitter.Init(pBackgroundCel, pDestImage);
		bResult = cBlitter.Configure(&gcImageRowBlitterFactory, false);
		AssertTrue(bResult);
		cBlitter.Blit(0, 0);
		cBlitter.Kill();

		cBlitter.Init(pMakiCel, pDestImage);
		bResult = cBlitter.Configure(&gcImageRowBlitterFactory, false);
		AssertTrue(bResult);
		cBlitter.Blit(x, y);
		cBlitter.Kill();

		szOutputFilename.Init(szDirectory);
		cFileUtil.AppendToPath(&szOutputFilename, szTestFilename);

		bWritten = WriteImage(pDestImage, szOutputFilename.Text(), IT_PNG);
		AssertTrue(bWritten);


		szInputFilename.Init(szOutputFilename);
		szInputFilename.Replace("Output", "Input");

		AssertFile(szInputFilename, szOutputFilename);

		szOutputFilename.Kill();
		szInputFilename.Kill();

	}
	ObjectsKill(false);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageOpacitySizingBlitter(char* szDirectory, char* szInputPathName, char* szTestFilename, int32 x, int32 y, int32 iWidth, int32 iHeight)
{
	CFileUtil			cFileUtil;

	AssertTrue(cFileUtil.RemoveDir(szDirectory));
	AssertTrue(cFileUtil.TouchDir(szDirectory));

	ObjectsInit();
	{
		Ptr<CImage>		pBackgroundImage;
		Ptr<CImage>		pMakiImage;
		Ptr<CImageCel>	pBackgroundCel;
		Ptr<CImageCel>	pMakiCel;
		CArrayChannel	asChannels;
		SChannel*		psChannel;
		Ptr<CImage>		pDestImage;
		size			uiWidth;
		size			uiHeight;
		CImageBlitter	cBlitter;
		CChars			szOutputFilename;
		CChars			szInputFilename;
		bool			bWritten;
		bool			bResult;

		pBackgroundImage = TestImageOpacityReadImage("Fighting320.png");
		pMakiImage = TestImageOpacityReadImage(szInputPathName);

		asChannels.Init();
		pBackgroundImage->GetAllChannels(&asChannels);
		AssertSize(3, asChannels.NumElements());
		psChannel = asChannels.Get(0);
		AssertSize(IMAGE_DIFFUSE_RED, psChannel->iChannel);
		AssertInt(PT_uint8, psChannel->eType);
		AssertFalse(psChannel->bReverse);
		asChannels.Kill();

		asChannels.Init();
		pMakiImage->GetAllChannels(&asChannels);
		AssertSize(4, asChannels.NumElements());
		psChannel = asChannels.Get(0);
		AssertSize(IMAGE_OPACITY, psChannel->iChannel);
		AssertInt(PT_uint8, psChannel->eType);
		AssertFalse(psChannel->bReverse);
		asChannels.Kill();


		uiWidth = pBackgroundImage->GetWidth();
		uiHeight = pBackgroundImage->GetHeight();
		pDestImage = OMalloc<CImage>(uiWidth, uiHeight, PT_uint8, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, CHANNEL_STOP);
		pDestImage->Black();

		pBackgroundCel = OMalloc<CImageCel>(pBackgroundImage);
		pMakiCel = OMalloc<CImageCel>(pMakiImage, true);

		cBlitter.Init(pBackgroundCel, pDestImage);
		bResult = cBlitter.Configure(&gcImageRowBlitterFactory, false);
		AssertTrue(bResult);
		cBlitter.Blit(0, 0);
		cBlitter.Kill();

		cBlitter.Init(pMakiCel, pDestImage);
		bResult = cBlitter.Configure(&gcImageRowBlitterFactory, true);
		AssertTrue(bResult);
		cBlitter.Blit(x, y, iWidth, iHeight);
		cBlitter.Kill();

		szOutputFilename.Init(szDirectory);
		cFileUtil.AppendToPath(&szOutputFilename, szTestFilename);

		bWritten = WriteImage(pDestImage, szOutputFilename.Text(), IT_PNG);
		AssertTrue(bWritten);


		szInputFilename.Init(szOutputFilename);
		szInputFilename.Replace("Output", "Input");

		AssertFile(szInputFilename, szOutputFilename);

		szOutputFilename.Kill();
		szInputFilename.Kill();

	}
	ObjectsKill(false);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageOpacityOpaqueBlitter(void)
{
	TestImageOpacityBlitter("Output" _FS_ "ImageOpacityCopier", "MakiStand.png", "Fighting.png", 100, 87);
	TestImageOpacityBlitter("Output" _FS_ "ImageOpacityCopier", "MakiStand.png", "FightingZero.png", 0, 0);
	TestImageOpacityBlitter("Output" _FS_ "ImageOpacityCopier", "MakiStand.png", "FightingMinus10Y.png", 120, -10);
	TestImageOpacityBlitter("Output" _FS_ "ImageOpacityCopier", "MakiStand.png", "FightingPlus210Y.png", 77, 120);
	TestImageOpacityBlitter("Output" _FS_ "ImageOpacityCopier", "MakiStand.png", "FightingMinus18X.png", -18, 60);
	TestImageOpacityBlitter("Output" _FS_ "ImageOpacityCopier", "MakiStand.png", "FightingPlus295X.png", 295, 68);
	TestImageOpacityBlitter("Output" _FS_ "ImageOpacityCopier", "ImageOpacityCopier" _FS_ "MakiWalkWide.png", "FightingPlusWide.png", -170, -3);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageOpacityTranslucentBlitter(void)
{
	TestImageOpacityBlitter("Output" _FS_ "ImageOpacityCopier", "ImageOpacityCopier" _FS_ "MakiStandFeathered.png", "FightingFeathered.png", 100, 87);
	TestImageOpacityBlitter("Output" _FS_ "ImageOpacityCopier", "ImageOpacityCopier" _FS_ "MakiStandFeathered.png", "FightingFeathered.png", 100, 87);
	TestImageOpacityBlitter("Output" _FS_ "ImageOpacityCopier", "ImageOpacityCopier" _FS_ "MakiStandFeathered.png", "FightingZeroFeathered.png", 0, 0);
	TestImageOpacityBlitter("Output" _FS_ "ImageOpacityCopier", "ImageOpacityCopier" _FS_ "MakiStandFeathered.png", "FightingMinus10YFeathered.png", 120, -10);
	TestImageOpacityBlitter("Output" _FS_ "ImageOpacityCopier", "ImageOpacityCopier" _FS_ "MakiStandFeathered.png", "FightingPlus210YFeathered.png", 77, 120);
	TestImageOpacityBlitter("Output" _FS_ "ImageOpacityCopier", "ImageOpacityCopier" _FS_ "MakiStandFeathered.png", "FightingMinus18XFeathered.png", -18, 60);
	TestImageOpacityBlitter("Output" _FS_ "ImageOpacityCopier", "ImageOpacityCopier" _FS_ "MakiStandFeathered.png", "FightingPlus295XFeathered.png", 295, 68);
	TestImageOpacityBlitter("Output" _FS_ "ImageOpacityCopier", "ImageOpacityCopier" _FS_ "MakiWalkWideTranslucent.png", "FightingPlusWideTranslucent.png", -170, -3);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageOpacityOpaqueSizingBlitter(void)
{
	TestImageOpacitySizingBlitter("Output" _FS_ "ImageOpacityCopier", "MakiStand.png", "SizingNoScale.png", 100, 87, 42, 91);
	TestImageOpacitySizingBlitter("Output" _FS_ "ImageOpacityCopier", "MakiStand.png", "SizingPlusOneX.png", 100, 87, 43, 91);
	TestImageOpacitySizingBlitter("Output" _FS_ "ImageOpacityCopier", "MakiStand.png", "SizingPlusTwoX.png", 100, 87, 44, 91);
	TestImageOpacitySizingBlitter("Output" _FS_ "ImageOpacityCopier", "MakiStand.png", "SizingPlusThreeX.png", 100, 87, 45, 91);
	TestImageOpacitySizingBlitter("Output" _FS_ "ImageOpacityCopier", "MakiStand.png", "SizingPlusFourX.png", 100, 87, 46, 91);
	TestImageOpacitySizingBlitter("Output" _FS_ "ImageOpacityCopier", "MakiStand.png", "SizingPlusFiveX.png", 100, 87, 47, 91);
	TestImageOpacitySizingBlitter("Output" _FS_ "ImageOpacityCopier", "MakiStand.png", "SizingDoubleX.png", 100, 87, 82, 91);
	TestImageOpacitySizingBlitter("Output" _FS_ "ImageOpacityCopier", "MakiStand.png", "SizingDoublePlusOneX.png", 100, 87, 83, 91);
	TestImageOpacitySizingBlitter("Output" _FS_ "ImageOpacityCopier", "MakiStand.png", "SizingOneX.png", 100, 87, 1, 91);
	TestImageOpacitySizingBlitter("Output" _FS_ "ImageOpacityCopier", "MakiStand.png", "SizingZeroX.png", 100, 87, 0, 91);
	TestImageOpacitySizingBlitter("Output" _FS_ "ImageOpacityCopier", "MakiStand.png", "SizingTwoX.png", 100, 87, 2, 91);
	TestImageOpacitySizingBlitter("Output" _FS_ "ImageOpacityCopier", "MakiStand.png", "SizingFourX.png", 100, 87, 4, 91);
	TestImageOpacitySizingBlitter("Output" _FS_ "ImageOpacityCopier", "MakiStand.png", "SizingEightX.png", 100, 87, 8, 91);
	TestImageOpacitySizingBlitter("Output" _FS_ "ImageOpacityCopier", "MakiStand.png", "SizingFifteenX.png", 100, 87, 15, 91);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageOpacityTranslucentSizingBlitter(void)
{
	TestImageOpacitySizingBlitter("Output" _FS_ "ImageOpacityCopier", "ImageOpacityCopier" _FS_ "MakiStandFeathered.png", "SizingNoScaleFeathered.png", 100, 87, 42, 91);
	TestImageOpacitySizingBlitter("Output" _FS_ "ImageOpacityCopier", "ImageOpacityCopier" _FS_ "MakiStandFeathered.png", "SizingPlusOneXFeathered.png", 100, 87, 43, 91);
	TestImageOpacitySizingBlitter("Output" _FS_ "ImageOpacityCopier", "ImageOpacityCopier" _FS_ "MakiStandFeathered.png", "SizingPlusTwoXFeathered.png", 100, 87, 44, 91);
	TestImageOpacitySizingBlitter("Output" _FS_ "ImageOpacityCopier", "ImageOpacityCopier" _FS_ "MakiStandFeathered.png", "SizingPlusThreeXFeathered.png", 100, 87, 45, 91);
	TestImageOpacitySizingBlitter("Output" _FS_ "ImageOpacityCopier", "ImageOpacityCopier" _FS_ "MakiStandFeathered.png", "SizingPlusFourXFeathered.png", 100, 87, 46, 91);
	TestImageOpacitySizingBlitter("Output" _FS_ "ImageOpacityCopier", "ImageOpacityCopier" _FS_ "MakiStandFeathered.png", "SizingPlusFiveXFeathered.png", 100, 87, 47, 91);
	TestImageOpacitySizingBlitter("Output" _FS_ "ImageOpacityCopier", "ImageOpacityCopier" _FS_ "MakiStandFeathered.png", "SizingDoubleXFeathered.png", 100, 87, 82, 91);
	TestImageOpacitySizingBlitter("Output" _FS_ "ImageOpacityCopier", "ImageOpacityCopier" _FS_ "MakiStandFeathered.png", "SizingDoublePlusOneXFeathered.png", 100, 87, 83, 91);
	TestImageOpacitySizingBlitter("Output" _FS_ "ImageOpacityCopier", "ImageOpacityCopier" _FS_ "MakiStandFeathered.png", "SizingOneXFeathered.png", 100, 87, 1, 91);
	TestImageOpacitySizingBlitter("Output" _FS_ "ImageOpacityCopier", "ImageOpacityCopier" _FS_ "MakiStandFeathered.png", "SizingZeroXFeathered.png", 100, 87, 0, 91);
	TestImageOpacitySizingBlitter("Output" _FS_ "ImageOpacityCopier", "ImageOpacityCopier" _FS_ "MakiStandFeathered.png", "SizingTwoXFeathered.png", 100, 87, 2, 91);
	TestImageOpacitySizingBlitter("Output" _FS_ "ImageOpacityCopier", "ImageOpacityCopier" _FS_ "MakiStandFeathered.png", "SizingFourXFeathered.png", 100, 87, 4, 91);
	TestImageOpacitySizingBlitter("Output" _FS_ "ImageOpacityCopier", "ImageOpacityCopier" _FS_ "MakiStandFeathered.png", "SizingEightXFeathered.png", 100, 87, 8, 91);
	TestImageOpacitySizingBlitter("Output" _FS_ "ImageOpacityCopier", "ImageOpacityCopier" _FS_ "MakiStandFeathered.png", "SizingFifteenXFeathered.png", 100, 87, 15, 91);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageOpacity(void)
{
	BeginTests();

	DataIOInit();
	
	TestImageOpacityOpaqueBlitter();
	TestImageOpacityTranslucentBlitter();
	TestImageOpacityOpaqueSizingBlitter();
	TestImageOpacityTranslucentSizingBlitter();

	DataIOKill();

	TestStatistics();
}

