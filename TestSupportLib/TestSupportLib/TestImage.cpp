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
void TestImageKillChannels(void)
{
	ObjectsInit();
	{
		CChannels* pcChannelsSource;
		CChannels* pcChannelsDest;

		AssertSize(0, gcObjects.NumMemoryIndexes());

		Ptr<CImage> pImageSource = OMalloc<CImage>(3, 2, PT_uint8, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, CHANNEL_STOP);
		pImageSource->Clear();
		Ptr<CImage> pImageDest = OMalloc<CImage>(3, 2, PT_uint8, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, CHANNEL_STOP);
		pImageDest->Clear();

		AssertSize(2, gcObjects.NumMemoryIndexes());

		pcChannelsSource = &pImageSource->mcChannels;
		pcChannelsDest = &pImageDest->mcChannels;

		AssertSize(6, pcChannelsSource->GetSize());
		AssertSize(2, pImageSource.NumEmbedded());  //Two because the Image is considered to be embedded in itself along with the Channels.
		pImageSource = NULL;
		AssertSize(0, pImageSource.NumEmbedded());

		AssertSize(6, pcChannelsDest->GetSize());
		AssertSize(2, pImageDest.NumEmbedded());
		pImageDest = NULL;
		AssertSize(0, pImageDest.NumEmbedded());

		AssertSize(0, gcObjects.NumMemoryIndexes());
	}
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageCopier(void)
{
	ObjectsInit();
	{
		CImage						cImageDest;
		CImageModifierDrawBox		cBox;
		CImage						cImageSource;
		char						szSourceRGB[18] = "ABCDEFGHIJKLMNOPQ";
		char						szSourceRB[12] = "ACDFGIJLMOP";
		char						szSourceR2G2B2[36] = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqR";
		char*						pcData;
		bool						bResult;
		char						szDestSameType[18] = "BACEDFHGIKJLNMOQP";
		char						szDestRGBMissingType[18] = "A\0CD\0FG\0IJ\0LM\0OP\0";
		char						szDestRGMissingType[13] = "ABDEGHJKMNPQ";
		char						szDestRGBDifferentType[36] = "AABBCCDDEEFFGGHHIIJJKKLLMMNNOOPPQQ";
		char						szDestRGBDifferentType2[18] = "abcdefghijklmnopq";
		CImageColourRGB				cRGB;
		CChannels*					pcChannelsSource;
		CChannels*					pcChannelsDest;

		//Same format, Same types ------------------------------------------
		cImageDest.Init(3, 2, PT_uint8, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, CHANNEL_STOP);
		pcChannelsDest = &cImageDest.mcChannels;
		cImageDest.Clear();

		cImageSource.Init(3, 2, szSourceRGB, PT_uint8, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, CHANNEL_STOP);
		pcChannelsSource = &cImageSource.mcChannels;

		bResult = cImageSource.IsSameFormat(&cImageDest);
		AssertTrue(bResult);

		CImageCopier::Copy(&cImageSource, &cImageDest, 0, 0, NULL);
		pcData = (char*)cImageDest.GetData();
		AssertString(szSourceRGB, pcData);

		AssertSize(0, gcObjects.NumMemoryIndexes());

		AssertSize(6, pcChannelsSource->GetSize());
		AssertSize(2, cImageSource.NumEmbedded());
		cImageSource.Kill();
		AssertSize(0, pcChannelsSource->GetSize());
		AssertSize(6, pcChannelsDest->GetSize());
		AssertSize(2, cImageDest.NumEmbedded());
		cImageDest.Kill();
		AssertSize(0, pcChannelsDest->GetSize());
		AssertSize(0, gcObjects.NumMemoryIndexes());

		//Different format, Same types ------------------------------------------
		cImageDest.Init(3, 2, PT_uint8, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_BLUE, CHANNEL_STOP);
		pcChannelsDest = &cImageDest.mcChannels;
		cImageDest.Clear();

		cImageSource.Init(3, 2, szSourceRGB, PT_uint8, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, CHANNEL_STOP);
		pcChannelsSource = &cImageSource.mcChannels;

		bResult = cImageSource.IsSameFormat(&cImageDest);
		AssertBool(false, bResult);

		CImageCopier::Copy(&cImageSource, &cImageDest, 0, 0, NULL);
		pcData = (char*)cImageDest.GetData();
		AssertString(szDestSameType, pcData);

		AssertSize(6, pcChannelsSource->GetSize());
		AssertSize(2, cImageSource.NumEmbedded());
		cImageSource.Kill();
		AssertSize(0, pcChannelsSource->GetSize());
		AssertSize(6, pcChannelsDest->GetSize());
		AssertSize(2, cImageDest.NumEmbedded());
		cImageDest.Kill();
		AssertSize(0, pcChannelsDest->GetSize());

		//Different format, Missing source types ------------------------------------------
		cImageDest.Init(3, 2, PT_uint8, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, CHANNEL_STOP);
		pcChannelsDest = &cImageDest.mcChannels;

		cRGB.Init(0, 0, 0);
		cBox.Init(NULL, &cRGB);
		cBox.Modify(&cImageDest);
		cBox.Kill();

		cImageSource.Init(3, 2, szSourceRB, PT_uint8, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_BLUE, CHANNEL_STOP);
		pcChannelsSource = &cImageSource.mcChannels;

		bResult = cImageSource.IsSameFormat(&cImageDest);
		AssertBool(false, bResult);

		CImageCopier::Copy(&cImageSource, &cImageDest, 0, 0, NULL);
		pcData = (char*)cImageDest.GetData();
		AssertMemory(szDestRGBMissingType, pcData, 18);

		cImageSource.Kill();
		cImageDest.Kill();

		//Different format, Missing dest types ------------------------------------------
		cImageDest.Init(3, 2, PT_uint8, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, CHANNEL_STOP);
		pcChannelsDest = &cImageDest.mcChannels;
		cImageDest.Clear();

		cImageSource.Init(3, 2, szSourceRGB, PT_uint8, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, CHANNEL_STOP);
		pcChannelsSource = &cImageSource.mcChannels;

		bResult = cImageSource.IsSameFormat(&cImageDest);
		AssertBool(false, bResult);

		CImageCopier::Copy(&cImageSource, &cImageDest, 0, 0 , NULL);
		pcData = (char*)cImageDest.GetData();
		AssertMemory(szDestRGMissingType, pcData, 12);

		cImageSource.Kill();
		cImageDest.Kill();

		//Different types ------------------------------------------
		cImageDest.Init(3, 2, PT_uint16, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, CHANNEL_STOP);
		pcChannelsDest = &cImageDest.mcChannels;
		cImageDest.Clear();
		AssertInt(3*2 * 3*2, cImageDest.GetByteSize());

		cImageSource.Init(3, 2, szSourceRGB, PT_uint8, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, CHANNEL_STOP);
		pcChannelsSource = &cImageSource.mcChannels;

		bResult = cImageSource.IsSameFormat(&cImageDest);
		AssertBool(false, bResult);

		CImageCopier::Copy(&cImageSource, &cImageDest, 0, 0, NULL);
		pcData = (char*)cImageDest.GetData();
		AssertString(szDestRGBDifferentType, pcData);

		cImageSource.Kill();
		cImageDest.Kill();

		//Different types ------------------------------------------
		cImageDest.Init(3, 2, PT_uint8, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, CHANNEL_STOP);
		pcChannelsDest = &cImageDest.mcChannels;
		cImageDest.Clear();
		AssertInt(3*2 * 3, cImageDest.GetByteSize());

		cImageSource.Init(3, 2, szSourceR2G2B2, PT_uint16, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, CHANNEL_STOP);
		pcChannelsSource = &cImageSource.mcChannels;

		bResult = cImageSource.IsSameFormat(&cImageDest);
		AssertBool(false, bResult);

		CImageCopier::Copy(&cImageSource, &cImageDest, 0, 0, NULL);
		pcData = (char*)cImageDest.GetData();

		AssertString(szDestRGBDifferentType2, pcData);

		cImageSource.Kill();
		cImageDest.Kill();
	}
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
Ptr<CImage> TestImageReadSpaceCrusadeImage(char* szFilename)
{
	CFileUtil			cFileUtil;
	CChars				szInputFilename;
	Ptr<CImage>			pImage;

	szInputFilename.Init();
	cFileUtil.CurrentDirectory(&szInputFilename);
	cFileUtil.AppendToPath(&szInputFilename, "Input");
	cFileUtil.AppendToPath(&szInputFilename, "SpaceCrusade");
	cFileUtil.AppendToPath(&szInputFilename, szFilename);
	AssertTrue(cFileUtil.Exists(szInputFilename.Text()));

	pImage = ReadImage(szInputFilename.Text(), IT_Unknown, true);
	AssertTrue(pImage.IsNotNull());
	szInputFilename.Kill();

	return pImage;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageCopierRealPNG(void)
{
	char				szDirectory[] = "Output" _FS_ "CopierRealPNG";
	CIndexTreeMemory	cMemory;
	CFileUtil			cFileUtil;

	AssertTrue(cFileUtil.RemoveDir(szDirectory));
	AssertTrue(cFileUtil.TouchDir(szDirectory));

	ObjectsInit();
	{
		Ptr<CImage>		pImage;
		CArrayChannel	asChannels;
		SChannel*		psChannel;
		Ptr<CImage>		pDestImage;
		size			uiWidth;
		size			uiHeight;
		CImageCopier	cCopier;
		CChars			szOutputFilename;
		CChars			szInputFilename;
		bool			bWritten;

		pImage = TestImageReadSpaceCrusadeImage("SoulSucker.png");

		asChannels.Init();
		pImage->GetAllChannels(&asChannels);

		AssertSize(4, asChannels.NumElements());
		psChannel = asChannels.Get(0);
		AssertSize(IMAGE_OPACITY, psChannel->iChannel);
		AssertInt(PT_uint8, psChannel->eType);
		AssertFalse(psChannel->bReverse);

		psChannel = asChannels.Get(1);
		AssertSize(IMAGE_DIFFUSE_RED, psChannel->iChannel);
		AssertInt(PT_uint8, psChannel->eType);

		psChannel = asChannels.Get(2);
		AssertSize(IMAGE_DIFFUSE_GREEN, psChannel->iChannel);
		AssertInt(PT_uint8, psChannel->eType);

		psChannel = asChannels.Get(3);
		AssertSize(IMAGE_DIFFUSE_BLUE, psChannel->iChannel);
		AssertInt(PT_uint8, psChannel->eType);

		asChannels.Kill();

		uiWidth = pImage->GetWidth() / 2;
		uiHeight = pImage->GetHeight();
		pDestImage = OMalloc<CImage>(uiWidth, uiHeight, PT_uint8, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, CHANNEL_STOP);
		AssertFalse(pDestImage.IsNull());

		pDestImage->Clear();
		cCopier.Init(pImage, pDestImage);
		cCopier.Copy(0, 0);
		cCopier.Kill();

		szOutputFilename.Init(szDirectory);
		cFileUtil.AppendToPath(&szOutputFilename, "SoulSucker.png");

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
void TestImage(void)
{
	BeginTests();

	DataIOInit();

	TestImageKillChannels();
	TestImageCopier();
	TestImageCopierRealPNG();

	DataIOKill();

	TestStatistics();
}


