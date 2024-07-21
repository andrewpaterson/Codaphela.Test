#include "SupportLib/Image.h"
#include "BaseLib/FastFunctions.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "StandardLib/Objects.h"
#include "SupportLib/ImageReader.h"
#include "SupportLib/ImageWriter.h"
#include "TestLib/Assert.h"

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageSFTWriter1(void)
{
	bool bResult;

	Ptr<CImage> pcImage = ReadImage("Input\\MakiStand.png", IT_Unknown, true);
	AssertTrue(pcImage.IsNotNull());

	bResult = WriteImage(pcImage, "Output\\MakiStand.sft");
	AssertTrue(bResult);

	pcImage->Kill();

}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageSFTWriter(void)
{
	BeginTests();

	DataIOInit();
	ObjectsInit();
	ImageChannelDescriptorInit();

	TestImageSFTWriter1();

	ImageChannelDescriptorKill();
	ObjectsKill();
	DataIOKill();

	TestStatistics();
}

