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
	CImage				cImage;
	CImageR3G3B2A		cRGBTo8bit;
	CArrayChannel		pcChannels;
	bool				bResult;

	ReadImage(&cImage, "Input\\cel1.png");

	cRGBTo8bit.Init();
	bResult = cRGBTo8bit.Modify(&cImage);
	cRGBTo8bit.Kill();
	AssertTrue(bResult);

	cImage.GetAllChannels(&pcChannels);
	AssertInt(3, pcChannels.NumElements());
	AssertChannel(IP_Diffuse, CT_Blue, PT_crumb, pcChannels.Get(0));
	AssertChannel(IP_Diffuse, CT_Green, PT_tribble, pcChannels.Get(1));
	AssertChannel(IP_Diffuse, CT_Red, PT_tribble, pcChannels.Get(2));
	AssertInt(24, cImage.GetWidth());
	AssertInt(24, cImage.GetHeight());
	AssertInt(576, cImage.GetChannels()->GetSize());
	AssertInt(576, cImage.GetByteSize());

	bResult =  WriteImage(&cImage, "Output\\RGBTo8bit.raw");
	AssertTrue(bResult);
	AssertFileMemory("input\\RGBTo8bit.raw", cImage.GetData(), cImage.GetByteSize());

	cImage.Kill();
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

