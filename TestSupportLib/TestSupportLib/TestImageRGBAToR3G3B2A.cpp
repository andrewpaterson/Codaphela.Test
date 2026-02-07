#include "BaseLib/NaiveFile.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "StandardLib/Objects.h"
#include "SupportLib/Image.h"
#include "SupportLib/ImageReader.h"
#include "SupportLib/ImageWriter.h"
#include "SupportLib/ImageToR3G3B2A.h"
#include "TestLib/Assert.h"
#include "AssertImage.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageToR3G3B2AConvert(void)
{
	CImageR3G3B2A	cRGBTo8bit;
	CArrayChannel	acChannels;
	bool			bResult;

	Ptr<CImage> pcImage = ReadImage("Input" _FS_ "cel1.png");

	cRGBTo8bit.Init();
	pcImage = cRGBTo8bit.Modify(pcImage);
	cRGBTo8bit.Kill();
	AssertTrue(pcImage.IsNotNull());

	acChannels.Init();
	pcImage->GetAllChannels(&acChannels);
	AssertInt(3, acChannels.NumElements());
	AssertChannel(IP_Diffuse, CT_Blue, PT_crumb, acChannels.Get(2));
	AssertChannel(IP_Diffuse, CT_Green, PT_tribble, acChannels.Get(1));
	AssertChannel(IP_Diffuse, CT_Red, PT_tribble, acChannels.Get(0));
	acChannels.Kill();
	AssertInt(24, pcImage->GetWidth());
	AssertInt(24, pcImage->GetHeight());
	AssertInt(576, pcImage->GetChannels()->GetSize());
	AssertInt(576, pcImage->GetByteSize());

	bResult =  WriteImage(pcImage, "Output" _FS_ "RGBTo8bit.raw");
	AssertTrue(bResult);
	AssertFileMemory("input" _FS_ "RGBTo8bit.raw", pcImage->GetData(), pcImage->GetByteSize());

	//This is probably unnecessay.
	pcImage->Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageToR3G3B2A(void)
{
	BeginTests();

	DataIOInit();
	ObjectsInit();

	TestImageToR3G3B2AConvert();

	ObjectsKill();
	DataIOKill();

	TestStatistics();
}

