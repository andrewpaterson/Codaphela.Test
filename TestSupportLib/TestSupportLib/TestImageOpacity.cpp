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
void TestImageOpacityCopier(void)
{
	char				szDirectory[] = "Output" _FS_ "ImageOpacityCopier";
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
		Ptr<CImageRowBlitterCache>	pCache;
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
		pMakiImage = TestImageOpacityReadImage("MakiStand.png");

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

		pCache = OMalloc<CImageRowBlitterCache>();

		uiWidth = pBackgroundImage->GetWidth();
		uiHeight = pBackgroundImage->GetHeight();
		pDestImage = OMalloc<CImage>(uiWidth, uiHeight, PT_uint8, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, CHANNEL_STOP);
		pDestImage->Clear();

		pBackgroundCel = OMalloc<CImageCel>(pBackgroundImage);
		pMakiCel = OMalloc<CImageCel>(pMakiImage);

		cBlitter.Init(pBackgroundCel, pDestImage, pCache);
		cBlitter.Copy(0, 0);
		cBlitter.Kill();

		// Aaaagh

		cBlitter.Init(pMakiCel, pDestImage, pCache);
		cBlitter.Copy(100, 87);
		cBlitter.Kill();

		szOutputFilename.Init(szDirectory);
		cFileUtil.AppendToPath(&szOutputFilename, "Fighting.png");

		bWritten = WriteImage(pDestImage, szOutputFilename.Text(), IT_PNG);
		AssertTrue(bWritten);


		szInputFilename.Init(szOutputFilename);
		szInputFilename.Replace("Output", "Input");

		AssertFile(szInputFilename, szOutputFilename);

		szOutputFilename.Kill();
		szInputFilename.Kill();

		pCache = NULL;
	}
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageOpacity(void)
{
	BeginTests();

	DataIOInit();

	TestImageOpacityCopier();

	DataIOKill();

	TestStatistics();
}

