#include "BaseLib/FastFunctions.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/NaiveFile.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "StandardLib/Objects.h"
#include "SupportLib/ImageReader.h"
#include "SupportLib/ImageWriter.h"
#include "SupportLib/ImageCelsSource.h"
#include "SupportLib/ImageRGBToGrey.h"
#include "SupportLib/ImageCelSourceBorders.h"
#include "SupportLib/ImageSourceDiskFile.h"
#include "SupportLib/ImageCombiner.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageCombinerMask(void)
{
	CImageCelSourceBorders	cBorder;
	CImageCombiner			cCombiner;
	Ptr<CImage>				pcImage;
	CImageCelsSource		cSource;
	SImageColour			sColour;

	sColour.c[0] = 0;
	sColour.c[1] = 0;
	sColour.c[2] = 0;
	sColour.c[3] = 0;

	cBorder.Init(&sColour);

	cSource.Init();
	cSource.AddDiskFileSource("Input\\cel4.png", "Cel 4", &cBorder);
	cSource.AddDiskFileSource("Input\\cel6.png", "Cel 6", &cBorder);

	cSource.Load();

	cCombiner.Init(ICL_Best, ICS_Arbitrary, ICC_FromCels);
	cCombiner.AddCels(cSource.GetCels());
	pcImage = cCombiner.Combine();

	WriteImage(&pcImage, "Output\\CombineMask.png");
	WriteImage(&pcImage, "Output\\CombineMask.raw");
	AssertFileMemory("input\\CombineMask.raw", pcImage->mcChannels.GetData(), pcImage->GetByteSize());

	pcImage->Kill();
	cCombiner.Kill();
	cSource.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageCombiner(void)
{
	BeginTests();

	DataIOInit();
	ObjectsInit();

	TestImageCombinerMask();

	ObjectsKill();
	DataIOKill();
	
	TestStatistics();
}

