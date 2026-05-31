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
#include "SupportLib/ImageRowBlitterCache.h"
#include "TestLib/Assert.h"


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
void TestImageOpacityCopier(char* szDirectory, char* szInputPathName, char* szTestFilename, int32 x, int32 y)
{
	CIndexTreeMemory	cMemory;
	CFileUtil			cFileUtil;

	AssertTrue(cFileUtil.RemoveDir(szDirectory));
	AssertTrue(cFileUtil.TouchDir(szDirectory));

	ObjectsInit();
	{
		Ptr<CImage>					pBackgroundImage;
		Ptr<CImage>					pMakiImage;
		Ptr<CImageCel>				pBackgroundCel;
		Ptr<CImageCel>				pMakiCel;
		CImageRowBlitterCache		cCache;
		CArrayChannel				asChannels;
		SChannel*					psChannel;
		Ptr<CImage>					pDestImage;
		size						uiWidth;
		size						uiHeight;
		CImageBlitter				cBlitter;
		CChars						szOutputFilename;
		CChars						szInputFilename;
		bool						bWritten;

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

		cCache.Init();

		uiWidth = pBackgroundImage->GetWidth();
		uiHeight = pBackgroundImage->GetHeight();
		pDestImage = OMalloc<CImage>(uiWidth, uiHeight, PT_uint8, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, CHANNEL_STOP);
		pDestImage->Clear();

		pBackgroundCel = OMalloc<CImageCel>(pBackgroundImage);
		pMakiCel = OMalloc<CImageCel>(pMakiImage, true);

		cBlitter.Init(pBackgroundCel, pDestImage, &cCache);
		cBlitter.Copy(0, 0);
		cBlitter.Kill();

		cBlitter.Init(pMakiCel, pDestImage, &cCache);
		cBlitter.Copy(x, y);
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

		cCache.Kill();
	}
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageOpacityOpaqueBlitter(void)
{
	TestImageOpacityCopier("Output" _FS_ "ImageOpacityCopier", "MakiStand.png", "Fighting.png", 100, 87);
	TestImageOpacityCopier("Output" _FS_ "ImageOpacityCopier", "MakiStand.png", "FightingZero.png", 0, 0);
	TestImageOpacityCopier("Output" _FS_ "ImageOpacityCopier", "MakiStand.png", "FightingMinus10Y.png", 120, -10);
	TestImageOpacityCopier("Output" _FS_ "ImageOpacityCopier", "MakiStand.png", "FightingPlus210Y.png", 77, 120);
	TestImageOpacityCopier("Output" _FS_ "ImageOpacityCopier", "MakiStand.png", "FightingMinus18X.png", -18, 60);
	TestImageOpacityCopier("Output" _FS_ "ImageOpacityCopier", "MakiStand.png", "FightingPlus295X.png", 295, 68);
	TestImageOpacityCopier("Output" _FS_ "ImageOpacityCopier", "ImageOpacityCopier" _FS_ "MakiWalkWide.png", "FightingPlusWide.png", -170, -3);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageOpacityTranslucentBlitter(void)
{
	TestImageOpacityCopier("Output" _FS_ "ImageOpacityCopier", "ImageOpacityCopier" _FS_ "MakiStandFeathered.png", "FightingFeathered.png", 100, 87);
	TestImageOpacityCopier("Output" _FS_ "ImageOpacityCopier", "ImageOpacityCopier" _FS_ "MakiStandFeathered.png", "FightingFeathered.png", 100, 87);
	TestImageOpacityCopier("Output" _FS_ "ImageOpacityCopier", "ImageOpacityCopier" _FS_ "MakiStandFeathered.png", "FightingZeroFeathered.png", 0, 0);
	TestImageOpacityCopier("Output" _FS_ "ImageOpacityCopier", "ImageOpacityCopier" _FS_ "MakiStandFeathered.png", "FightingMinus10YFeathered.png", 120, -10);
	TestImageOpacityCopier("Output" _FS_ "ImageOpacityCopier", "ImageOpacityCopier" _FS_ "MakiStandFeathered.png", "FightingPlus210YFeathered.png", 77, 120);
	TestImageOpacityCopier("Output" _FS_ "ImageOpacityCopier", "ImageOpacityCopier" _FS_ "MakiStandFeathered.png", "FightingMinus18XFeathered.png", -18, 60);
	TestImageOpacityCopier("Output" _FS_ "ImageOpacityCopier", "ImageOpacityCopier" _FS_ "MakiStandFeathered.png", "FightingPlus295XFeathered.png", 295, 68);
	TestImageOpacityCopier("Output" _FS_ "ImageOpacityCopier", "ImageOpacityCopier" _FS_ "MakiWalkWideTranslucent.png", "FightingPlusWideTranslucent.png", -170, -3);
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

	DataIOKill();

	TestStatistics();
}

