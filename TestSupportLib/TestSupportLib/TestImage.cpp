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
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageKillChannels(void)
{
	CChannels*	pcChannelsSource;
	CChannels*	pcChannelsDest;

	AssertSize(0, gcObjects.NumMemoryIndexes());

	Ptr<CImage> pImageSource = OMalloc<CImage>(3, 2, PT_uint8, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, CHANNEL_ZERO);
	pImageSource->Clear();
	Ptr<CImage> pImageDest = OMalloc<CImage>(3, 2, PT_uint8, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, CHANNEL_ZERO);
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


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageCopier(void)
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
	cImageDest.Init(3, 2, PT_uint8, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, CHANNEL_ZERO);
	pcChannelsDest = &cImageDest.mcChannels;
	cImageDest.Clear();

	cImageSource.Init(3, 2, szSourceRGB, PT_uint8, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, CHANNEL_ZERO);
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
	cImageDest.Init(3, 2, PT_uint8, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_BLUE, CHANNEL_ZERO);
	pcChannelsDest = &cImageDest.mcChannels;
	cImageDest.Clear();

	cImageSource.Init(3, 2, szSourceRGB, PT_uint8, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, CHANNEL_ZERO);
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
	cImageDest.Init(3, 2, PT_uint8, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, CHANNEL_ZERO);
	pcChannelsDest = &cImageDest.mcChannels;

	cRGB.Init(0, 0, 0);
	cBox.Init(NULL, &cRGB);
	cBox.Modify(&cImageDest);
	cBox.Kill();

	cImageSource.Init(3, 2, szSourceRB, PT_uint8, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_BLUE, CHANNEL_ZERO);
	pcChannelsSource = &cImageSource.mcChannels;

	bResult = cImageSource.IsSameFormat(&cImageDest);
	AssertBool(false, bResult);

	CImageCopier::Copy(&cImageSource, &cImageDest, 0, 0, NULL);
	pcData = (char*)cImageDest.GetData();
	AssertMemory(szDestRGBMissingType, pcData, 18);

	cImageSource.Kill();
	cImageDest.Kill();

	//Different format, Missing dest types ------------------------------------------
	cImageDest.Init(3, 2, PT_uint8, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, CHANNEL_ZERO);
	pcChannelsDest = &cImageDest.mcChannels;
	cImageDest.Clear();

	cImageSource.Init(3, 2, szSourceRGB, PT_uint8, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, CHANNEL_ZERO);
	pcChannelsSource = &cImageSource.mcChannels;

	bResult = cImageSource.IsSameFormat(&cImageDest);
	AssertBool(false, bResult);

	CImageCopier::Copy(&cImageSource, &cImageDest, 0, 0 , NULL);
	pcData = (char*)cImageDest.GetData();
	AssertMemory(szDestRGMissingType, pcData, 12);

	cImageSource.Kill();
	cImageDest.Kill();

	//Different types ------------------------------------------
	cImageDest.Init(3, 2, PT_uint16, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, CHANNEL_ZERO);
	pcChannelsDest = &cImageDest.mcChannels;
	cImageDest.Clear();
	AssertInt(3*2 * 3*2, cImageDest.GetByteSize());

	cImageSource.Init(3, 2, szSourceRGB, PT_uint8, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, CHANNEL_ZERO);
	pcChannelsSource = &cImageSource.mcChannels;

	bResult = cImageSource.IsSameFormat(&cImageDest);
	AssertBool(false, bResult);

	CImageCopier::Copy(&cImageSource, &cImageDest, 0, 0, NULL);
	pcData = (char*)cImageDest.GetData();
	AssertString(szDestRGBDifferentType, pcData);

	cImageSource.Kill();
	cImageDest.Kill();

	//Different types ------------------------------------------
	cImageDest.Init(3, 2, PT_uint8, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, CHANNEL_ZERO);
	pcChannelsDest = &cImageDest.mcChannels;
	cImageDest.Clear();
	AssertInt(3*2 * 3, cImageDest.GetByteSize());

	cImageSource.Init(3, 2, szSourceR2G2B2, PT_uint16, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, CHANNEL_ZERO);
	pcChannelsSource = &cImageSource.mcChannels;

	bResult = cImageSource.IsSameFormat(&cImageDest);
	AssertBool(false, bResult);

	CImageCopier::Copy(&cImageSource, &cImageDest, 0, 0, NULL);
	pcData = (char*)cImageDest.GetData();

	AssertString(szDestRGBDifferentType2, pcData);

	cImageSource.Kill();
	cImageDest.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImage(void)
{
	BeginTests();

	DataIOInit();
	ObjectsInit();

	TestImageKillChannels();
	TestImageCopier();

	ObjectsKill();
	DataIOKill();

	TestStatistics();
}


