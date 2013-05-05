#include "stdafx.h"
#include "BaseLib/NaiveFile.h"
#include "CoreLib/TypeConverter.h"
#include "SupportLib/ImageModifierStack.h"
#include "SupportLib/ImageReader.h"
#include "SupportLib/ImageWriter.h"
#include "SupportLib/ImageRGBToGrey.h"
#include "SupportLib/BumpMapper.h"
#include "SupportLib/ImageResampler.h"
#include "TestLib/Assert.h"
#include "TestImageModifierStack.h"



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageModifierStack(void)
{
	BeginTests();

	CImage					cImage;
	CImageModifierStack		cStack;
	BOOL					bResult;
	CImageRGBToGrey*		pcGrey;
	CImageHeightToNormals*	pcNormals;
	CImageResampler*		pcSmall;
	CImage					cBak;

	bResult = ReadImage(&cBak, "Input/Adelle.png");
	AssertBool(TRUE, bResult);

	cImage.Copy(&cBak);
	cStack.Init(&cImage);

	pcGrey = cStack.AddModifier<CImageRGBToGrey>();
	pcGrey->Init(RGBTGS_UseRed);
	cStack.ApplyAll();

	WriteImage(&cImage, "Output/AdelleGrey.raw");
	AssertFileMemory("Input/AdelleGrey.raw", cImage.GetData(), cImage.GetByteSize());
	cImage.Kill();

	pcNormals = cStack.AddModifier<CImageHeightToNormals>();
	pcNormals->Init(IMAGE_DIFFUSE_GREY);
	cImage.Copy(&cBak);
	cStack.ApplyAll();

	WriteImage(&cImage, "Output/AdelleNormal.raw");
	AssertFileMemory("Input/AdelleNormal.raw", cImage.GetData(), cImage.GetByteSize());
	cImage.Kill();

	pcSmall = cStack.AddModifier<CImageResampler>();
	pcSmall->Init(IR_NearestNeighbour, 21, 16);
	cImage.Copy(&cBak);
	cStack.ApplyAll();

	WriteImage(&cImage, "Output/AdelleSmall.raw");
	AssertFileMemory("Input/AdelleSmall.raw", cImage.GetData(), cImage.GetByteSize());
	AssertInt(3, cStack.NumModifiers());

	cStack.Kill();
	cImage.Kill();

	cBak.Kill();

	TestStatistics();
}

