#include "stdafx.h"
#include "BaseLib/FastFunctions.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/NaiveFile.h"
#include "CoreLib/TypeConverter.h"
#include "StandardLib/Unknowns.h"
#include "SupportLib/ImageReader.h"
#include "SupportLib/ImageWriter.h"
#include "SupportLib/ImageRGBToGrey.h"
#include "SupportLib/ImageDrawBox.h"
#include "SupportLib/ImageModifierStack.h"
#include "SupportLib/ImageChannelRename.h"
#include "SupportLib/ImageChannelAdd.h"
#include "TestLib/Assert.h"
#include "TestImageSwizzle.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageSwizzle(void)
{
	BeginTests();

	CImage					cImage;
	CImageModifierStack		cStack;
	CImageRGBToGrey*		pcRGBToGrey;
	CImageChannelRename*	pcChannelRename;
	CImageChannelAdd*		pcChannelAdd;
	CImageDrawBox*			pcDrawBox;
	CImageColourRGB			cRGB;

	ReadImage(&cImage, "Input\\swizzel.png");

	cStack.Init(&cImage);
	
	pcRGBToGrey = cStack.AddModifier<CImageRGBToGrey>();
	pcRGBToGrey->Init(RGBTGS_OnlyIfChannelsSame);

	pcChannelRename = cStack.AddModifier<CImageChannelRename>();
	pcChannelRename->Init(IMAGE_DIFFUSE_GREY, IMAGE_OPACITY);

	pcChannelAdd = cStack.AddModifier<CImageChannelAdd>();
	pcChannelAdd->Init(IMAGE_DIFFUSE_RED, PT_uchar);
	pcChannelAdd->AddChannel(IMAGE_DIFFUSE_GREEN);
	pcChannelAdd->AddChannel(IMAGE_DIFFUSE_BLUE);

	pcDrawBox = cStack.AddModifier<CImageDrawBox>();
	
	cRGB.Init(1.0f, 1.0f, 1.0f);
	pcDrawBox->Init(NULL, &cRGB);

	cStack.ApplyAll();
	cStack.Kill();

	WriteImage(&cImage, "Output\\swizzle.raw");
	AssertFileMemory("input\\swizzle.raw", cImage.GetData(), cImage.GetByteSize());

	cImage.Kill();

	TestStatistics();
}



