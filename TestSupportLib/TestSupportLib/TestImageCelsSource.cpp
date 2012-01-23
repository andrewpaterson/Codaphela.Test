#include "stdafx.h"
#include "BaseLib/FastFunctions.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/NaiveFile.h"
#include "CoreLib/TypeConverter.h"
#include "StandardLib/Unknowns.h"
#include "SupportLib/ImageReader.h"
#include "SupportLib/ImageWriter.h"
#include "SupportLib/ImageCelsSource.h"
#include "SupportLib/ImageRGBToGrey.h"
#include "SupportLib/ImageCelSourceSingle.h"
#include "SupportLib/ImageCelSourceGrid.h"
#include "SupportLib/ImageSourceDiskFile.h"
#include "SupportLib/ImageCombiner.h"
#include "TestLib/Assert.h"
#include "TestImageCelsSource.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageCelsSourceStarControl(void)
{
	CImageCelSourceSingle	cSingle;
	CImageCombiner			cCombiner;
	CImage					cImage;
	CImageCelsSource	cSource;
	CImageSourceDiskFile	cDiskFile;
	BOOL					bResult;

	cSingle.Init();

	cSource.Init(TRUE);
	cSource.AddDiskFileSources("C:\\Work\\Star Control\\Frames\\Androsynth Blazer", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:\\Work\\Star Control\\Frames\\Androsynth Guardian", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:\\Work\\Star Control\\Frames\\Arilou Skiff", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:\\Work\\Star Control\\Frames\\Chenjesu Broodhome", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:\\Work\\Star Control\\Frames\\Chenjesu Doggi", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:\\Work\\Star Control\\Frames\\Chenjesu Photon Shard", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:\\Work\\Star Control\\Frames\\Chmmr Avatar", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:\\Work\\Star Control\\Frames\\Chmmr Zapsat", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:\\Work\\Star Control\\Frames\\Druuge", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:\\Work\\Star Control\\Frames\\Earthling Cruiser", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:\\Work\\Star Control\\Frames\\Earthling Nuclear Missile", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:\\Work\\Star Control\\Frames\\Ilwrath Avenger", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:\\Work\\Star Control\\Frames\\Kohr-Ah", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:\\Work\\Star Control\\Frames\\Mmrnmhrm Transformer XForm", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:\\Work\\Star Control\\Frames\\Mmrnmhrm Transformer YForm", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:\\Work\\Star Control\\Frames\\Mycon Podship", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:\\Work\\Star Control\\Frames\\Mycon Spore", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:\\Work\\Star Control\\Frames\\Orz Nemesis", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:\\Work\\Star Control\\Frames\\Orz Nemesis Turret", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:\\Work\\Star Control\\Frames\\Pkunk Fury", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:\\Work\\Star Control\\Frames\\Shofixti Scout", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:\\Work\\Star Control\\Frames\\Spathi Discriminator", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:\\Work\\Star Control\\Frames\\Suppox Blade", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:\\Work\\Star Control\\Frames\\Syreen Penetrator", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:\\Work\\Star Control\\Frames\\Umgah Drone", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:\\Work\\Star Control\\Frames\\Ur-Quan  Autonomous Fighter", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:\\Work\\Star Control\\Frames\\Ur-Quan Dreadnought", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:\\Work\\Star Control\\Frames\\Utwig Jugger", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:\\Work\\Star Control\\Frames\\Vux Intruder", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:\\Work\\Star Control\\Frames\\Yehat Terminator", "frame", NULL, &cSingle);
	cSource.AddDiskFileSources("C:\\Work\\Star Control\\Frames\\Yehat Terminator Shield", "frame", NULL, &cSingle);

	cSource.Load();

	cCombiner.Init(&cImage, ICL_Best, ICS_Arbitrary, ICC_FromCels);
	cCombiner.AddCels(cSource.GetCels());
	bResult = cCombiner.Combine();

	if (bResult)
	{
		cImage.BeginChange();
		cImage.RemoveChannel(IMAGE_OPACITY);
		cImage.EndChange();
		WriteImage(&cImage, "C:\\Work\\Star Control\\Frames\\StarControl All.rad");
	}

	cImage.Kill();
	cCombiner.Kill();
	cSource.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageCelGroupSourceCombine(void)
{
	CImageCelSourceSingle	cSingle;
	CImageDividerNumbers	cGridNumbers;
	CImageCelSourceGrid		cGrid;
	CImageCombiner			cCombiner;
	CImage					cImage;
	CImageCelsSource	cSource;
	CImageSourceDiskFile	cDiskFile;
	BOOL					bResult;

	cSingle.Init();
	cGridNumbers.InitFromRowsColumns(72, 1);
	cGrid.Init(&cGridNumbers);

	cSource.Init();
	cSource.AddDiskFileSources("Input\\Source\\Mauler", "frame", "Druuge Mauler", &cSingle);
	cDiskFile.Init("Input\\Source\\Broodhome.png", "Chenjesu Broodhome");
	cSource.AddSource(&cDiskFile, &cGrid);

	cSource.Load();

	cCombiner.Init(&cImage, ICL_Best, ICS_Arbitrary, ICC_FromCels);
	cCombiner.AddCels(cSource.GetCels());
	bResult = cCombiner.Combine();

	if (bResult)
	{
		WriteImage(&cImage, "Output\\StarControl.raw");
		AssertFileMemory("input\\StarControl.raw", cImage.mcChannels.GetData(), cImage.GetByteSize());
	}

	cImage.Kill();
	cCombiner.Kill();
	cSource.Kill();
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

