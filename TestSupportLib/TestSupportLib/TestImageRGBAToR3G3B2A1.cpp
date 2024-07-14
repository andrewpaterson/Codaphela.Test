#include "BaseLib/NaiveFile.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "StandardLib/Objects.h"
#include "SupportLib/Image.h"
#include "SupportLib/ImageReader.h"
#include "SupportLib/ImageWriter.h"
#include "SupportLib/ImageRGBToGrey.h"
#include "TestLib/Assert.h"
#include "AssertImage.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageToR3G3B2A1Convert(void)
{
	CImage				cImage;
	CImageRGBToGrey		cRGBToGrey;
	CArrayChannel		pcChannels;
	bool				bResult;

	ReadImage(&cImage, "Input\\cel1.png");

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
void TestImageToR3G3B2A1(void)
{
	BeginTests();

	DataIOInit();
	ObjectsInit();

	TestImageToR3G3B2A1Convert();

	ObjectsKill();
	DataIOKill();

	TestStatistics();
}

