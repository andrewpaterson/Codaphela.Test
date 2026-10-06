#include "BaseLib/GlobalMemory.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/StdRandom.h"
#include "StandardLib/Objects.h"
#include "SupportLib/ImageCelBlitterCache.h"
#include "WindowLib/Window.h"
#include "WindowLib/FillContainer.h"
#include "WindowLib/MapsCanvasDraw.h"
#include "WinRefLib/WinRefWindowFactory.h"
#include "TestLib/AssertFile.h"
#include "TestRefWindowCanvasDraw.h"
#include "BorderCanvasDraw.h"
#include "TickTestRefWindow.h"
#include "DataTestRefWindow.h"
#include "SpaceCrusade.h"


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
void TestCanvasWriteImage(void)
{
	CWinRefWindowFactory	cNativeFactory;
	CFileUtil				cFileUtil;
	char					szDirectory[] = "Output" _FS_ "CanvasWriteImage";

	cFileUtil.RemoveDir(szDirectory);
	cFileUtil.MakeDir(szDirectory);

	ObjectsInit();
	{
		Ptr<CWindow>				pTestWindow;
		Ptr<CCanvas>				pCanvas;
		Ptr<CTickTestRefWindow>		pTick;
		SDataTestRefWindow			cData;
		CPointer					pNull;
		Ptr<CFillContainer>			pFill;
		Ptr<CMapsCanvasDraw>		pDraw;
		Ptr<CRoot>					pRoot;
		CRandom						cRandom;
		Ptr<CImage>					pFloorPlanImage;
		Ptr<CTileMap>				pTileMap;
		Ptr<CTileMapGenerator>		pTileMapGenerator;
		Ptr<CArrayImageCel>			paBackgroundCels;
		Ptr<CMaps>					pMaps;
		CChars						szExpectedDirectory;


		pFloorPlanImage = ReadSpaceImage("SpaceCrusade", "FloorPlan.png");

		cRandom.Init(2345);

		cNativeFactory.Init(&gcMemoryAllocator, 320, 200, szDirectory);

		pRoot = ORoot();

		pTick = OMalloc<CTickTestRefWindow>(&cData, 1);
		pTestWindow = OMalloc<CWindow>("Space Crusade", &cNativeFactory, pTick, pNull);
		gcObjects.ValidateObjectsConsistency();

		pRoot->Add(pTestWindow);

		pFill = OMalloc<CFillContainer>(pTestWindow);
		pTestWindow->SetContainer(pFill);

		pTileMapGenerator = OMalloc<CTileMapGenerator>(&cRandom);
		pRoot->Add(pTileMapGenerator);

		pTileMapGenerator->AddTileGridSource("FloorPlan", pFloorPlanImage);
		paBackgroundCels = ReadSpaceCels("SpaceCrusade", "Tiles.png", 10, 3);
		AddSpacePatterns(pTileMapGenerator, paBackgroundCels);
		AddSpaceSources(pTileMapGenerator);

		pTileMap = pTileMapGenerator->Generate();

		pMaps = OMalloc<CMaps>();
		pMaps->AddMap(pTileMap);
		pMaps->SetViewportPosition(0, 0);

		pDraw = OMalloc<CMapsCanvasDraw>(pMaps);
		pCanvas = OMalloc<CCanvas>(pTestWindow, CFT_RGB, pDraw);
		pFill->AddComponent(pCanvas);

		pTestWindow->Show();

		pTestWindow = NULL;
		pCanvas = NULL;
		pTick = NULL;
		pFill = NULL;
		pDraw = NULL;
		pRoot->RemoveAll();

		cNativeFactory.Kill();

		szExpectedDirectory.Init(szDirectory);
		szExpectedDirectory.Replace("Output", "Input");

		AssertDirectory(szExpectedDirectory.Text(), szDirectory);
		szExpectedDirectory.Kill();
	}
	AssertSize(2, gcObjects.NumMemoryIndexes());  //Root and root-set.
	ObjectsFlush();
	ObjectsKill();

	cFileUtil.RemoveDir(szDirectory);
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
void TestCanvas(void)
{
	BeginTests();

	TestCanvasWriteImage();

	TestStatistics();
}

