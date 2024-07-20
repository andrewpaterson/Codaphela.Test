#include "BaseLib/NaiveFile.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "StandardLib/Objects.h"
#include "SupportLib/ImageModifierStack.h"
#include "SupportLib/ImageReader.h"
#include "SupportLib/ImageWriter.h"
#include "SupportLib/ImageRGBToGrey.h"
#include "SupportLib/BumpMapper.h"
#include "SupportLib/ImageResampler.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageModifierStack1(void)
{
	CImageModifierStack		cStack;
	CImageRGBToGrey*		pcGrey;
	CImageHeightToNormals*	pcNormals;
	CImageResampler*		pcSmall;
	
	Ptr<CImage> pcBak = ReadImage("Input/Adelle.png", IT_Unknown, true);
	AssertTrue(pcBak.IsNotNull());

	Ptr<CImage> pcImage = OMallocNoI<CImage>();
	pcImage->Copy(pcBak);
	cStack.Init(pcImage);

	pcGrey = cStack.AddModifier<CImageRGBToGrey>();
	pcGrey->Init(RGBTGS_UseRed);
	cStack.ApplyAll();

	WriteImage(pcImage, "Output/AdelleGrey.raw");
	AssertFileMemory("Input/AdelleGrey.raw", pcImage->GetData(), pcImage->GetByteSize());
	pcImage = NULL;

	pcImage = OMallocNoI<CImage>();
	pcNormals = cStack.AddModifier<CImageHeightToNormals>();
	pcNormals->Init(IMAGE_DIFFUSE_GREY);
	pcImage->Copy(pcBak);
	cStack.SetImage(pcImage);
	cStack.ApplyAll();

	WriteImage(pcImage, "Output/AdelleNormal.raw");
	AssertFileMemory("Input/AdelleNormal.raw", pcImage->GetData(), pcImage->GetByteSize());
	pcImage = NULL;

	pcImage = OMallocNoI<CImage>();
	pcSmall = cStack.AddModifier<CImageResampler>();
	pcSmall->Init(IR_NearestNeighbour, 21, 16);
	pcImage->Copy(pcBak);
	cStack.SetImage(pcImage);
	cStack.ApplyAll();

	WriteImage(pcImage, "Output/AdelleSmall.raw");
	AssertFileMemory("Input/AdelleSmall.raw", pcImage->GetData(), pcImage->GetByteSize());
	AssertInt(3, cStack.NumModifiers());

	cStack.Kill();
	pcImage = NULL;

	pcBak = NULL;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageModifierStack(void)
{
	BeginTests();

	DataIOInit();
	ObjectsInit();
	ImageChannelDescriptorInit();

	TestImageModifierStack1();

	ImageChannelDescriptorKill();
	ObjectsKill();
	DataIOKill();

	TestStatistics();
}

