#include "BaseLib/NaiveFile.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "StandardLib/Objects.h"
#include "SupportLib/Image.h"
#include "SupportLib/ImageReader.h"
#include "SupportLib/ImageWriter.h"
#include "SupportLib/ImageRGBToGrey.h"
#include "TestLib/Assert.h"
#include "AssertImage.h"
#include "TestImageRGBToGrey.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageRGBToGrey1(void)
{
	CImage				cImage;
	CImageRGBToGrey		cRGBToGrey;
	CArrayChannel		pcChannels;
	bool				bResult;

	ReadImage(&cImage, "Input\\RGBToGrey.png");
	
	cImage.GetAllChannels(&pcChannels);
	AssertInt(3, pcChannels.NumElements());
	AssertChannel(IP_Diffuse, CT_Red, PT_uint8, pcChannels.Get(0));
	AssertChannel(IP_Diffuse, CT_Green, PT_uint8, pcChannels.Get(1));
	AssertChannel(IP_Diffuse, CT_Blue, PT_uint8, pcChannels.Get(2));
	AssertInt(32, cImage.GetWidth());
	AssertInt(32, cImage.GetHeight());
	AssertInt(3072, cImage.GetByteSize());

	cRGBToGrey.Init(RGBTGS_OnlyIfChannelsSame);
	bResult = cRGBToGrey.Modify(&cImage);
	cRGBToGrey.Kill();
	AssertTrue(bResult);

	cImage.GetAllChannels(&pcChannels);
	AssertInt(1, pcChannels.NumElements());
	AssertChannel(IP_Diffuse, CT_Intensity, PT_uint8, pcChannels.Get(0));
	AssertInt(32, cImage.GetWidth());
	AssertInt(32, cImage.GetHeight());
	AssertInt(1024, cImage.GetChannels()->GetSize());
	AssertInt(1024, cImage.GetByteSize());

	WriteImage(&cImage, "Output\\RGBToGrey.raw");
	AssertFileMemory("input\\RGBToGrey.raw", cImage.GetData(), cImage.GetByteSize());

	cImage.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageRGBToGrey(void)
{
	BeginTests();

	DataIOInit();
	ObjectsInit();

	TestImageRGBToGrey1();

	ObjectsKill();
	DataIOKill();

	TestStatistics();
}

