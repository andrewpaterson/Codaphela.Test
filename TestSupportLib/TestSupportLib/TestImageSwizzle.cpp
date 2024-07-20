#include "BaseLib/FastFunctions.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/NaiveFile.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "StandardLib/Objects.h"
#include "SupportLib/ImageReader.h"
#include "SupportLib/ImageWriter.h"
#include "SupportLib/ImageRGBToGrey.h"
#include "SupportLib/ImageDrawBox.h"
#include "SupportLib/ImageModifierStack.h"
#include "SupportLib/ImageChannelRename.h"
#include "SupportLib/ImageChannelAdd.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageSwizzle1(void)
{
	CImageModifierStack		cStack;
	CImageRGBToGrey*		pcRGBToGrey;
	CImageChannelRename*	pcChannelRename;
	CImageChannelAdd*		pcChannelAdd;
	CImageDrawBox*			pcDrawBox;
	CImageColourRGB			cRGB;

	Ptr<CImage> pcImage = ReadImage("Input\\swizzel.png");

	cStack.Init(pcImage);
	
	pcRGBToGrey = cStack.AddModifier<CImageRGBToGrey>();
	pcRGBToGrey->Init(RGBTGS_OnlyIfChannelsSame);

	pcChannelRename = cStack.AddModifier<CImageChannelRename>();
	pcChannelRename->Init(IMAGE_DIFFUSE_GREY, IMAGE_OPACITY);

	pcChannelAdd = cStack.AddModifier<CImageChannelAdd>();
	pcChannelAdd->Init(IMAGE_DIFFUSE_RED, PT_uint8);
	pcChannelAdd->AddChannel(IMAGE_DIFFUSE_GREEN);
	pcChannelAdd->AddChannel(IMAGE_DIFFUSE_BLUE);

	pcDrawBox = cStack.AddModifier<CImageDrawBox>();
	
	cRGB.Init(1.0f, 1.0f, 1.0f);
	pcDrawBox->Init(NULL, &cRGB);

	cStack.ApplyAll();
	cStack.Kill();

	WriteImage(pcImage, "Output\\swizzle.raw");
	AssertFileMemory("input\\swizzle.raw", pcImage->GetData(), pcImage->GetByteSize());

	pcImage->Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageSwizzle(void)
{
	BeginTests();

	DataIOInit();
	ObjectsInit();

	TestImageSwizzle1();

	ObjectsKill();
	DataIOKill();

	TestStatistics();
}



