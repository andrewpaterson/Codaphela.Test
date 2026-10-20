#include "BaseLib/FastFunctions.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/Mallocator.h"
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
#include "SupportLib/ImageCelSourceSingle.h"
#include "SupportLib/ImageCelsWriter.h"
#include "SupportLib/ImageCelsReader.h"
#include "TestLib/Assert.h"
#include "TestLib/AssertFile.h"


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
	cSource.AddDiskFileSource("Input" _FS_ "cel4.png", "Cel 4", &cBorder);
	cSource.AddDiskFileSource("Input" _FS_ "cel6.png", "Cel 6", &cBorder);

	cSource.Load();

	cCombiner.Init(ICL_Best, ICS_Arbitrary, ICC_FromCels);
	cCombiner.AddCels(cSource.GetImageCels());
	pcImage = cCombiner.Combine();

	WriteImage(&pcImage, "Output" _FS_ "CombineMask.png");
	WriteImage(&pcImage, "Output" _FS_ "CombineMask.raw");
	AssertFileMemory("Input" _FS_ "CombineMask.raw", pcImage->GetChannels()->GetData(), pcImage->GetByteSize());

	pcImage = NULL;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageCombinerStarControl(void)
{
	CImageCelSourceSingle	cSingle;
	CImageCombiner			cCombiner;
	Ptr<CImage>				pcImage;
	CImageCelsSource		cSource;
	CFileUtil				cFileUtil;
	CArrayChars				aszDirectories;
	size					i;
	bool					bResult;
	Ptr<CArrayImageCel>		pacCels;
	Ptr<CArrayImageCel>		pacLoadedCels;
	size					uiMaxDebugAllocatorSize;

	//The combined image is about 18MB, larger than the debug allocation limit set in main.
	uiMaxDebugAllocatorSize = guiMaxDebugAllocatorSize;
	InitAllocatorDebug(32 MB);

	cSingle.Init();
	cSource.Init(true);

	aszDirectories.Init();
	cFileUtil.FindAllDirectories("Input" _FS_ "StarControl", &aszDirectories);
	aszDirectories.QuickSort();
	AssertSize(5, aszDirectories.NumElements());
	for (i = 0; i < aszDirectories.NumElements(); i++)
	{
		cSource.AddDiskFileSources(aszDirectories.Get(i)->Text(), "frame", NULL, &cSingle);
	}
	aszDirectories.Kill();

	gcObjects.DisableValidation();
	cSource.Load();
	AssertSize(360, cSource.GetImageCels()->NumElements());

	cCombiner.Init(ICL_Best, ICS_Arbitrary, ICC_FromCels);
	cCombiner.AddCels(cSource.GetImageCels());
	pcImage = cCombiner.Combine();
	gcObjects.EnableValidation();
	AssertTrue(pcImage.IsNotNull());

	pacCels = cCombiner.GetCels();
	AssertSize(360, pacCels->NumElements());
	AssertTrue(pacCels->Get(0)->GetSourceImage() == pcImage);

	bResult = WriteImage(pcImage, "Output" _FS_ "StarControl.png", IT_PNG);
	AssertTrue(bResult);
	bResult = SaveImageCels(pacCels, "Output" _FS_ "StarControl.png", "Output" _FS_ "StarControl.cels");
	AssertTrue(bResult);

	pacLoadedCels = LoadImageCels("Output" _FS_ "StarControl.cels");
	AssertTrue(pacLoadedCels.IsNotNull());
	AssertSize(360, pacLoadedCels->NumElements());
	AssertInt(pcImage->GetWidth(), pacLoadedCels->Get(0)->GetSourceImage()->GetWidth());
	AssertInt(pcImage->GetHeight(), pacLoadedCels->Get(0)->GetSourceImage()->GetHeight());
	pacLoadedCels = NULL;

	pacCels = NULL;
	pcImage = NULL;
	cCombiner.Kill();
	cSource.Kill();

	InitAllocatorDebug(uiMaxDebugAllocatorSize);
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
	TestImageCombinerStarControl();

	ObjectsKill(false);
	DataIOKill();
	
	TestStatistics();
}

