#include "BaseLib/FastFunctions.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/NaiveFile.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "StandardLib/Unknowns.h"
#include "StandardLib/Objects.h"
#include "SupportLib/ImageReader.h"
#include "SupportLib/ImageWriter.h"
#include "SupportLib/ImageCelsSource.h"
#include "SupportLib/ImageRGBToGrey.h"
#include "SupportLib/ImageCelSourceSingle.h"
#include "SupportLib/ImageCelSourceGrid.h"
#include "SupportLib/ImageCelSourceBorders.h"
#include "SupportLib/ImageCelMask.h"
#include "SupportLib/ImageSourceDiskFile.h"
#include "SupportLib/ImageCombiner.h"
#include "TestLib/Assert.h"
#include "TestLib/AssertFile.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageCelsSourceStarControl(void)
{
	DataIOInit();
	ObjectsInit();

	CImageCelSourceSingle	cSingle;
	CImageCombiner			cCombiner;
	Ptr<CImage>				pcImage;
	CImageCelsSource		cSource;
	CImageSourceDiskFile	cDiskFile;

	gcObjects.DisableValidation();

	cSingle.Init();

	cSource.Init(true);
	cSource.AddDiskFileSources("C:" _FS_ "Work" _FS_ "Star Control" _FS_ "Frames" _FS_ "Androsynth Blazer", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:" _FS_ "Work" _FS_ "Star Control" _FS_ "Frames" _FS_ "Androsynth Guardian", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:" _FS_ "Work" _FS_ "Star Control" _FS_ "Frames" _FS_ "Arilou Skiff", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:" _FS_ "Work" _FS_ "Star Control" _FS_ "Frames" _FS_ "Chenjesu Broodhome", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:" _FS_ "Work" _FS_ "Star Control" _FS_ "Frames" _FS_ "Chenjesu Doggi", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:" _FS_ "Work" _FS_ "Star Control" _FS_ "Frames" _FS_ "Chenjesu Photon Shard", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:" _FS_ "Work" _FS_ "Star Control" _FS_ "Frames" _FS_ "Chmmr Avatar", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:" _FS_ "Work" _FS_ "Star Control" _FS_ "Frames" _FS_ "Chmmr Zapsat", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:" _FS_ "Work" _FS_ "Star Control" _FS_ "Frames" _FS_ "Druuge", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:" _FS_ "Work" _FS_ "Star Control" _FS_ "Frames" _FS_ "Earthling Cruiser", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:" _FS_ "Work" _FS_ "Star Control" _FS_ "Frames" _FS_ "Earthling Nuclear Missile", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:" _FS_ "Work" _FS_ "Star Control" _FS_ "Frames" _FS_ "Ilwrath Avenger", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:" _FS_ "Work" _FS_ "Star Control" _FS_ "Frames" _FS_ "Kohr-Ah", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:" _FS_ "Work" _FS_ "Star Control" _FS_ "Frames" _FS_ "Mmrnmhrm Transformer XForm", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:" _FS_ "Work" _FS_ "Star Control" _FS_ "Frames" _FS_ "Mmrnmhrm Transformer YForm", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:" _FS_ "Work" _FS_ "Star Control" _FS_ "Frames" _FS_ "Mycon Podship", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:" _FS_ "Work" _FS_ "Star Control" _FS_ "Frames" _FS_ "Mycon Spore", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:" _FS_ "Work" _FS_ "Star Control" _FS_ "Frames" _FS_ "Orz Nemesis", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:" _FS_ "Work" _FS_ "Star Control" _FS_ "Frames" _FS_ "Orz Nemesis Turret", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:" _FS_ "Work" _FS_ "Star Control" _FS_ "Frames" _FS_ "Pkunk Fury", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:" _FS_ "Work" _FS_ "Star Control" _FS_ "Frames" _FS_ "Shofixti Scout", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:" _FS_ "Work" _FS_ "Star Control" _FS_ "Frames" _FS_ "Spathi Discriminator", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:" _FS_ "Work" _FS_ "Star Control" _FS_ "Frames" _FS_ "Suppox Blade", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:" _FS_ "Work" _FS_ "Star Control" _FS_ "Frames" _FS_ "Syreen Penetrator", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:" _FS_ "Work" _FS_ "Star Control" _FS_ "Frames" _FS_ "Umgah Drone", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:" _FS_ "Work" _FS_ "Star Control" _FS_ "Frames" _FS_ "Ur-Quan  Autonomous Fighter", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:" _FS_ "Work" _FS_ "Star Control" _FS_ "Frames" _FS_ "Ur-Quan Dreadnought", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:" _FS_ "Work" _FS_ "Star Control" _FS_ "Frames" _FS_ "Utwig Jugger", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:" _FS_ "Work" _FS_ "Star Control" _FS_ "Frames" _FS_ "Vux Intruder", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:" _FS_ "Work" _FS_ "Star Control" _FS_ "Frames" _FS_ "Yehat Terminator", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:" _FS_ "Work" _FS_ "Star Control" _FS_ "Frames" _FS_ "Yehat Terminator Shield", "frame", NULL, &cSingle);

	cSource.Load();

	cCombiner.Init(ICL_Best, ICS_Arbitrary, ICC_FromCels);
	cCombiner.AddCels(cSource.GetImageCels());
	pcImage = cCombiner.Combine();

	gcObjects.EnableValidation();

	if (pcImage.IsNotNull())
	{
		pcImage->BeginChange();
		pcImage->RemoveChannel(IMAGE_OPACITY);
		pcImage->EndChange();
		WriteImage(&pcImage, "C:" _FS_ "Work" _FS_ "Star Control" _FS_ "Frames" _FS_ "StarControl All.rad");
		pcImage->Kill();
	}

	cCombiner.Kill();
	cSource.Kill();

	ObjectsKill(false);
	DataIOKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageCelGroupSourceCombine(void)
{
	DataIOInit();
	ObjectsInit();

	CImageCelSourceSingle	cSingle;
	CImageDividerNumbers	cGridNumbers;
	CImageCelSourceGrid		cGrid;
	CImageCombiner			cCombiner;
	Ptr<CImage>				pcImage;
	CImageCelsSource		cSource;
	CImageSourceDiskFile	cDiskFile;

	cSingle.Init();
	cGridNumbers.InitFromRowsColumns(72, 1);
	cGrid.Init(&cGridNumbers);

	cSource.Init();
	cSource.AddDiskFileSources("Input" _FS_ "Source" _FS_ "Mauler", "frame", "Druuge Mauler", &cSingle);
	cDiskFile.Init("Input" _FS_ "Source" _FS_ "Broodhome.png", "Chenjesu Broodhome");
	cSource.AddSource(&cDiskFile, &cGrid);

	gcObjects.DisableValidation();

	cSource.Load();

	cCombiner.Init(ICL_Best, ICS_Arbitrary, ICC_FromCels);
	cCombiner.AddCels(cSource.GetImageCels());
	pcImage = cCombiner.Combine();

	gcObjects.EnableValidation();

	if (pcImage.IsNotNull())
	{
		AssertInt(630, pcImage->GetWidth());
		AssertInt(109, pcImage->GetHeight());
		WriteImage(&pcImage, "Output" _FS_ "StarControl.raw");
		AssertFileMemory("Input" _FS_ "StarControl.raw", pcImage->mcChannels.GetData(), pcImage->GetByteSize());
	}
	else
	{
		AssertTrue(false);
	}

	pcImage->Kill();
	cCombiner.Kill();
	cSource.Kill();
	cDiskFile.Kill();  //The cels source only releases its pointer to a source it did not create.

	ObjectsKill(false);
	DataIOKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageCelsSourceBorderMasks(void)
{
	DataIOInit();
	ObjectsInit();

	CImageCelSourceBorders	cBorder;
	CImageCelsSource		cSource;
	Ptr<CArrayImageCel>		pCels;
	CImageCelMask*			pcCel1;
	CImageCelMask*			pcCel2;

	//A border cel source needs a fill mask so the cels source creates one for each image it divides.
	cBorder.Init();
	AssertTrue(cBorder.NeedsMask());

	cSource.Init(false);
	cSource.AddDiskFileSource("Input" _FS_ "cel4.png", "Cel 4", &cBorder);
	AssertTrue(cSource.Load());

	AssertSize(1, cSource.GetImages()->NumElements());
	pCels = cSource.GetImageCels();
	AssertSize(2, pCels->NumElements());
	AssertString("CImageCelMask", pCels->UnsafeGetObject(0)->ClassName());
	AssertString("CImageCelMask", pCels->UnsafeGetObject(1)->ClassName());

	//Each cel is the region its mask value was filled with.
	pcCel1 = (CImageCelMask*)pCels->UnsafeGetObject(0);
	pcCel2 = (CImageCelMask*)pCels->UnsafeGetObject(1);
	AssertInt(1, pcCel1->GetMask());
	AssertInt(2, pcCel2->GetMask());

	AssertInt(36, pcCel1->GetSubImage()->GetFullWidth());
	AssertInt(28, pcCel1->GetSubImage()->GetImageWidth());
	AssertInt(22, pcCel1->GetSubImage()->GetFullHeight());
	AssertInt(18, pcCel1->GetSubImage()->GetImageHeight());

	AssertInt(31, pcCel2->GetSubImage()->GetFullWidth());
	AssertInt(25, pcCel2->GetSubImage()->GetImageWidth());
	AssertInt(22, pcCel2->GetSubImage()->GetFullHeight());
	AssertInt(11, pcCel2->GetSubImage()->GetImageHeight());

	pCels = NULL;
	cSource.Kill();
	cBorder.Kill();

	ObjectsKill(false);
	DataIOKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageCelsSourceBorderMasksPackOnLoad(void)
{
	DataIOInit();
	ObjectsInit();

	CImageCelSourceBorders	cBorder;
	CImageCelsSource		cSource;
	Ptr<CArrayImageCel>		pCels;
	Ptr<CImageCel>			pCel1;
	Ptr<CImageCel>			pCel2;

	//Packing combines the cels into a new image so the fill mask is no longer needed by them.
	cBorder.Init();

	cSource.Init(true);
	cSource.AddDiskFileSource("Input" _FS_ "cel4.png", "Cel 4", &cBorder);
	AssertTrue(cSource.Load());

	AssertSize(1, cSource.GetImages()->NumElements());
	pCels = cSource.GetImageCels();
	AssertSize(2, pCels->NumElements());

	//The packed cels keep the cropped sizes of the masked regions.
	pCel1 = pCels->Get(0);
	pCel2 = pCels->Get(1);
	AssertInt(28, pCel1->GetSubImage()->GetImageWidth());
	AssertInt(18, pCel1->GetSubImage()->GetImageHeight());
	AssertInt(25, pCel2->GetSubImage()->GetImageWidth());
	AssertInt(11, pCel2->GetSubImage()->GetImageHeight());

	pCel1 = NULL;
	pCel2 = NULL;
	pCels = NULL;
	cSource.Kill();
	cBorder.Kill();

	ObjectsKill(false);
	DataIOKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageCelsSource(void)
{
	BeginTests();

	TestImageCelGroupSourceCombine();
	TestImageCelsSourceStarControl();
	TestImageCelsSourceBorderMasks();
	TestImageCelsSourceBorderMasksPackOnLoad();

	TestStatistics();
}

