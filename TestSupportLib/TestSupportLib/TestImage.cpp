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
#include "SupportLib/ImageDrawBox.h"
#include "SupportLib/ImageCopier.h"
#include "TestLib/Assert.h"
#include "TestImageWriter.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDrawImage(void)
{
	CImage				cImageDest;
	CImageDrawBox		cBox;
	CImage				cImageSource;
	char				szSourceRGB[18] = "ABCDEFGHIJKLMNOPQ";
	char				szSourceRB[12] = "ACDFGIJLMOP";
	char				szSourceR2G2B2[36] = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqR";
	char*				pcData;
	bool				bResult;
	char				szDestSameType[18] = "BACEDFHGIKJLNMOQP";
	char				szDestRGBMissingType[18] = "A\0CD\0FG\0IJ\0LM\0OP\0";
	char				szDestRGMissingType[13] = "ABDEGHJKMNPQ";
	char				szDestRGBDifferentType[36] = "AABBCCDDEEFFGGHHIIJJKKLLMMNNOOPPQQ";
	char				szDestRGBDifferentType2[18] = "abcdefghijklmnopq";
	CImageColourRGB		cRGB;

	//Same format, Same types ------------------------------------------
	cImageDest.Init(3, 2, PT_uint8, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, CHANNEL_ZERO);
	cImageDest.Clear();

	cImageSource.Init(3, 2, szSourceRGB, PT_uint8, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, CHANNEL_ZERO);
	
	bResult = cImageSource.IsSameFormat(&cImageDest);
	AssertTrue(bResult);


	CImageCopier::Copy(&cImageSource, &cImageDest, 0, 0, NULL);
	
	pcData = (char*)cImageDest.GetData();
	AssertString(szSourceRGB, pcData);

	cImageSource.Kill();
	cImageDest.Kill();

	//Different format, Same types ------------------------------------------
	cImageDest.Init(3, 2, PT_uint8, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_BLUE, CHANNEL_ZERO);
	cImageDest.Clear();

	cImageSource.Init(3, 2, szSourceRGB, PT_uint8, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, CHANNEL_ZERO);

	bResult = cImageSource.IsSameFormat(&cImageDest);
	AssertBool(false, bResult);

	CImageCopier::Copy(&cImageSource, &cImageDest, 0, 0, NULL);
	pcData = (char*)cImageDest.GetData();
	AssertString(szDestSameType, pcData);

	cImageSource.Kill();
	cImageDest.Kill();

	//Different format, Missing source types ------------------------------------------
	cImageDest.Init(3, 2, PT_uint8, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, CHANNEL_ZERO);

	cRGB.Init(0, 0, 0);
	cBox.Init(NULL, &cRGB);
	cBox.Modify(&cImageDest);
	cBox.Kill();

	cImageSource.Init(3, 2, szSourceRB, PT_uint8, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_BLUE, CHANNEL_ZERO);

	bResult = cImageSource.IsSameFormat(&cImageDest);
	AssertBool(false, bResult);

	CImageCopier::Copy(&cImageSource, &cImageDest, 0, 0, NULL);
	pcData = (char*)cImageDest.GetData();
	AssertMemory(szDestRGBMissingType, pcData, 18);

	cImageSource.Kill();
	cImageDest.Kill();

	//Different format, Missing dest types ------------------------------------------
	cImageDest.Init(3, 2, PT_uint8, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, CHANNEL_ZERO);
	cImageDest.Clear();

	cImageSource.Init(3, 2, szSourceRGB, PT_uint8, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, CHANNEL_ZERO);

	bResult = cImageSource.IsSameFormat(&cImageDest);
	AssertBool(false, bResult);

	CImageCopier::Copy(&cImageSource, &cImageDest, 0, 0 , NULL);
	pcData = (char*)cImageDest.GetData();
	AssertMemory(szDestRGMissingType, pcData, 12);

	cImageSource.Kill();
	cImageDest.Kill();

	//Different types ------------------------------------------
	cImageDest.Init(3, 2, PT_uint16, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, CHANNEL_ZERO);
	cImageDest.Clear();
	AssertInt(3*2 * 3*2, cImageDest.GetByteSize());

	cImageSource.Init(3, 2, szSourceRGB, PT_uint8, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, CHANNEL_ZERO);

	bResult = cImageSource.IsSameFormat(&cImageDest);
	AssertBool(false, bResult);

	CImageCopier::Copy(&cImageSource, &cImageDest, 0, 0, NULL);
	pcData = (char*)cImageDest.GetData();
	AssertString(szDestRGBDifferentType, pcData);

	cImageSource.Kill();
	cImageDest.Kill();

	//Different types ------------------------------------------
	cImageDest.Init(3, 2, PT_uint8, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, CHANNEL_ZERO);
	cImageDest.Clear();
	AssertInt(3*2 * 3, cImageDest.GetByteSize());

	cImageSource.Init(3, 2, szSourceR2G2B2, PT_uint16, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, CHANNEL_ZERO);

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

	TestDrawImage();

	ObjectsKill();
	DataIOKill();

	TestStatistics();
}


