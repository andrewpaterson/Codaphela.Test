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
#include "SupportLib/ImageSourceDiskFile.h"
#include "SupportLib/ImageCombiner.h"
#include "TestLib/Assert.h"


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
	cCombiner.AddCels(cSource.GetCels());
	pcImage = cCombiner.Combine();

	if (pcImage.IsNotNull())
	{
		pcImage->BeginChange();
		pcImage->RemoveChannel(IMAGE_OPACITY);
		pcImage->EndChange();
		WriteImage(&pcImage, "C:" _FS_ "Work" _FS_ "Star Control" _FS_ "Frames" _FS_ "StarControl All.rad");
	}

	pcImage->Kill();
	cCombiner.Kill();
	cSource.Kill();

	ObjectsKill();
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

	cSource.Load();

	cCombiner.Init(ICL_Best, ICS_Arbitrary, ICC_FromCels);
	cCombiner.AddCels(cSource.GetCels());
	pcImage = cCombiner.Combine();

	if (pcImage.IsNotNull())
	{
		AssertInt(630, pcImage->GetWidth());
		AssertInt(109, pcImage->GetHeight());
		WriteImage(&pcImage, "Output" _FS_ "StarControl.raw");
		AssertFileMemory("input" _FS_ "StarControl.raw", pcImage->mcChannels.GetData(), pcImage->GetByteSize());
	}
	else
	{
		AssertTrue(false);
	}

	pcImage->Kill();
	cCombiner.Kill();
	cSource.Kill();

	ObjectsKill();
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
	//TestImageCelGroupSourceStarControl();

	TestStatistics();
}

