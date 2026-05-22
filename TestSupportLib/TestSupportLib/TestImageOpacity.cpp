#include "BaseLib/NaiveFile.h"
#include "BaseLib/PointerRemapper.h"
#include "BaseLib/FastFunctions.h"
#include "BaseLib/Operators.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "StandardLib/Unknowns.h"
#include "StandardLib/Objects.h"
#include "SupportLib/Image.h"
#include "SupportLib/ImageReader.h"
#include "SupportLib/ImageAccessorCreator.h"
#include "SupportLib/ImageModifierDrawBox.h"
#include "SupportLib/ImageCopier.h"
#include "SupportLib/ImageWriter.h"
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
		Ptr<CImage>		pBackground;
		Ptr<CImage>		pMaki;
		CArrayChannel	asChannels;
		SChannel*		psChannel;
		Ptr<CImage>		pDestImage;
		size			uiWidth;
		size			uiHeight;
		CImageCopier	cCopier;
		CChars			szOutputFilename;
		CChars			szInputFilename;
		bool			bWritten;

		pBackground = TestImageOpacityReadImage("Fighting320.png");
		pMaki = TestImageOpacityReadImage("MakiStand.png");

		asChannels.Init();
		pBackground->GetAllChannels(&asChannels);
		AssertSize(3, asChannels.NumElements());
		psChannel = asChannels.Get(0);
		AssertSize(IMAGE_DIFFUSE_RED, psChannel->iChannel);
		AssertInt(PT_uint8, psChannel->eType);
		AssertFalse(psChannel->bReverse);
		asChannels.Kill();

		asChannels.Init();
		pMaki->GetAllChannels(&asChannels);
		AssertSize(4, asChannels.NumElements());
		psChannel = asChannels.Get(0);
		AssertSize(IMAGE_OPACITY, psChannel->iChannel);
		AssertInt(PT_uint8, psChannel->eType);
		AssertFalse(psChannel->bReverse);
		asChannels.Kill();

		uiWidth = pBackground->GetWidth();
		uiHeight = pBackground->GetHeight();
		pDestImage = OMalloc<CImage>(uiWidth, uiHeight, PT_uint8, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, CHANNEL_ZERO);
		pDestImage->Clear();

		cCopier.Init(pBackground, pDestImage);
		cCopier.Copy(0, 0);
		cCopier.Kill();

		// Add a transforming destination CChannelsAccessor that understand the channel types and can multiply them by the channel opacity.  See CChannelsAccessorTypeConverter.

		cCopier.Init(pMaki, pDestImage);
		cCopier.Copy(100, 87);
		cCopier.Kill();

		szOutputFilename.Init(szDirectory);
		cFileUtil.AppendToPath(&szOutputFilename, "Fighting.png");

		bWritten = WriteImage(pDestImage, szOutputFilename.Text(), IT_PNG);
		AssertTrue(bWritten);


		szInputFilename.Init(szOutputFilename);
		szInputFilename.Replace("Output", "Input");

		AssertFile(szInputFilename, szOutputFilename);

		szOutputFilename.Kill();
		szInputFilename.Kill();
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


