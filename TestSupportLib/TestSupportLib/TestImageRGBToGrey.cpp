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
void TestImageRGBToGrey1(void)
{
	CImageRGBToGrey		cRGBToGrey;
	CArrayChannel		pcChannels;

	Ptr<CImage> pcImage = ReadImage("Input" _FS_ "RGBToGrey.png");
	
	pcImage->GetAllChannels(&pcChannels);
	AssertInt(3, pcChannels.NumElements());
	AssertChannel(IP_Diffuse, CT_Red, PT_uint8, pcChannels.Get(0));
	AssertChannel(IP_Diffuse, CT_Green, PT_uint8, pcChannels.Get(1));
	AssertChannel(IP_Diffuse, CT_Blue, PT_uint8, pcChannels.Get(2));
	AssertInt(32, pcImage->GetWidth());
	AssertInt(32, pcImage->GetHeight());
	AssertInt(3072, pcImage->GetByteSize());

	cRGBToGrey.Init(RGBTGS_OnlyIfChannelsSame);
	pcImage = cRGBToGrey.Modify(pcImage);
	cRGBToGrey.Kill();
	AssertTrue(pcImage.IsNotNull());

	pcImage->GetAllChannels(&pcChannels);
	AssertInt(1, pcChannels.NumElements());
	AssertChannel(IP_Diffuse, CT_Intensity, PT_uint8, pcChannels.Get(0));
	AssertInt(32, pcImage->GetWidth());
	AssertInt(32, pcImage->GetHeight());
	AssertInt(1024, pcImage->GetChannels()->GetSize());
	AssertInt(1024, pcImage->GetByteSize());

	WriteImage(pcImage, "Output" _FS_ "RGBToGrey.raw");
	AssertFileMemory("input" _FS_ "RGBToGrey.raw", pcImage->GetData(), pcImage->GetByteSize());

	//This is probably unnecessay.
	pcImage->Kill();
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

