#include "BaseLib/GlobalDataTypesIO.h"
#include "SupportLib/ImageWriter.h"
#include "SupportLib/Maps.h"
#include "SupportLib/TileLayerCel.h"
#include "SupportLib/TileMapGenerator.h"
#include "SupportLib/ImageWriter.h"
#include "TestLib/Assert.h"
#include "TestReadImage.h"
#include "SupportAssert.h"


enum ESpaceCrusadeCelType
{
	SCCT_Invalid,
	SCCT_Space,
	SCCT_Wall,
	SCCT_Floor,
	SCCT_Door,
	SCCT_Shadow,
};


enum ESpaceCrusadeMapLayer
{
	SCML_Invalid,
	SCML_Floor,
	SCML_Shadow,
};


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTileMapGenerator2x2Generate(void)
{
	char				szDirectory[] = "Output" _FS_ "TileMapGenerator2x2Generate";
	CIndexTreeMemory	cMemory;
	CFileUtil			cFileUtil;

	AssertTrue(cFileUtil.RemoveDir(szDirectory));
	AssertTrue(cFileUtil.TouchDir(szDirectory));

	ObjectsInit();
	{
		Ptr<CMaps>					pMaps;
		CImageDivider				cImageDivider;
		CChars						szInputFilename;
		CChars						szOutputFilename;
		Ptr<CRoot>					pRoot;
		Ptr<CTileMapGenerator>		pTileMapGenerator;
		Ptr<CArrayImageCel>			pacBackgroundCels;
		CTileColourSource*			pcWallColour;
		CTileColourSource*			pcFloorColour;
		CTileColourSource*			pcSpaceColour;
		CTileColourSource*			pcDoorColour;
		Ptr<CImage>					pFloorPlanImage;
		Ptr<CTileMap>				pTileMap;
		Ptr<CImage>					pDestImage;
		Ptr<CImageCelBlitterCache>	pBlitterCache;
		SSizeVec2					sMapSize;
		SSizeVec2					sCelSize;
		bool						bResult;
		bool						bWritten;

		pFloorPlanImage = TestReadImage("SpaceCrusade", "SmallPlan.png");

		pRoot = ORoot();
		pTileMapGenerator = OMalloc<CTileMapGenerator>();
		pRoot->Add(pTileMapGenerator);

		pTileMapGenerator->AddTileGridSource("FloorPlan", pFloorPlanImage);

		pcWallColour = pTileMapGenerator->AddColourSource(138, 138, 138);
		pcFloorColour = pTileMapGenerator->AddColourSource(107, 73, 14);
		pcSpaceColour = pTileMapGenerator->AddColourSource(0, 0, 0);
		pcDoorColour = pTileMapGenerator->AddColourSource(71, 71, 71);

		pTileMapGenerator->AddCelType(		 'W', SCCT_Wall);
		pTileMapGenerator->AddNegativeCelType('w', SCCT_Wall);
		pTileMapGenerator->AddCelType(		 'C', SCCT_Wall, SCCT_Door);
		pTileMapGenerator->AddNegativeCelType('c', SCCT_Wall, SCCT_Door);

		pTileMapGenerator->AddPattern("FloorPlan", SCCT_Space, "Single",		" . . . \n"
																			" . B . \n"
																			" . . . \n");

		pTileMapGenerator->AddPattern("FloorPlan", SCCT_Floor, "Single",		" . . . \n"
																			" . B . \n"
																			" . . . \n");

		pTileMapGenerator->AddPattern("FloorPlan", SCCT_Wall, "Single",		" . c . \n"
																			" c B c \n"
																			" . c . \n");

		pTileMapGenerator->AddPattern("FloorPlan", SCCT_Wall, "UpDown",		" . C . \n"
																			" c B c \n"
																			" . C . \n");

		pTileMapGenerator->AddPattern("FloorPlan", SCCT_Wall, "LeftRight",	" . c . \n"
																			" C B C \n"
																			" . c . \n");

		pTileMapGenerator->AddPattern("FloorPlan", SCCT_Wall, "UpRight",		" . C . \n"
																			" c B C \n"
																			" . c . \n");

		pTileMapGenerator->AddPattern("FloorPlan", SCCT_Wall, "DownRight",	" . c . \n"
																			" c B C \n"
																			" . C . \n");

		pTileMapGenerator->AddPattern("FloorPlan", SCCT_Wall, "DownLeft",	" . c . \n"
																			" C B c \n"
																			" . C . \n");

		pTileMapGenerator->AddPattern("FloorPlan", SCCT_Wall, "UpLeft",		" . C . \n"
																			" C B c \n"
																			" . c . \n");

		pTileMapGenerator->AddPattern("FloorPlan", SCCT_Wall, "LeftRightDown"," . c . \n"
																			" C B C \n"
																			" . C . \n");

		pTileMapGenerator->AddPattern("FloorPlan", SCCT_Wall, "UpDownLeft",	" . C . \n"
																			" C B c \n"
																			" . C . \n");

		pTileMapGenerator->AddPattern("FloorPlan", SCCT_Wall, "UpDownRight",	" . C . \n"
																			" c B C \n"
																			" . C . \n");

		pTileMapGenerator->AddPattern("FloorPlan", SCCT_Wall, "LeftRightUp",	" . C . \n"
																			" C B C \n"
																			" . c . \n");

		pTileMapGenerator->AddPattern("FloorPlan", SCCT_Door, "DoorDown",	" . W . \n"
																			" . B . \n"
																			" . P . \n");

		pTileMapGenerator->AddPattern("FloorPlan", SCCT_Door, "DoorUp",		" . P . \n"
																			" . B . \n"
																			" . W . \n");

		pTileMapGenerator->AddPattern("FloorPlan", SCCT_Door, "DoorLeft",	" . . . \n"
																			" W B P \n"
																			" . . . \n");

		pTileMapGenerator->AddPattern("FloorPlan", SCCT_Door, "DoorRight",	" . . . \n"
																			" P B W \n"
																			" . . . \n");

		pTileMapGenerator->AddPattern("FloorPlan", SCCT_Shadow, "ShadowLeft"," W w . \n"
																			" W B . \n"
																			" . . . \n");

		pTileMapGenerator->AddPattern("FloorPlan", SCCT_Shadow,"ShadowSingle"," W w . \n"
																			" w B . \n"
																			" . . . \n");

		pTileMapGenerator->AddPattern("FloorPlan", SCCT_Shadow,"ShadowUpLeft"," W W . \n"
																			" W B . \n"
																			" . . . \n");

		pTileMapGenerator->AddPattern("FloorPlan", SCCT_Shadow,"ShadowUp",	" W W . \n"
																			" w B . \n"
																			" . . . \n");

		pTileMapGenerator->AddPattern("FloorPlan", SCCT_Shadow,"ShadowDown",	" w w . \n"
																			" W B . \n"
																			" . . . \n");

		pacBackgroundCels = TestReadCels("SpaceCrusade", "Tiles.png", 10, 3);

		pTileMapGenerator->AddTileBrush(pacBackgroundCels, 26, SCCT_Space,  "Single");
		pTileMapGenerator->AddTileBrush(pacBackgroundCels,  0, SCCT_Wall,   "Single");
		pTileMapGenerator->AddTileBrush(pacBackgroundCels,  4, SCCT_Wall,   "UpDown");
		pTileMapGenerator->AddTileBrush(pacBackgroundCels,  5, SCCT_Wall,   "LeftRight");
		pTileMapGenerator->AddTileBrush(pacBackgroundCels,  6, SCCT_Wall,   "DownLeft");
		pTileMapGenerator->AddTileBrush(pacBackgroundCels,  7, SCCT_Wall,   "DownRight");
		pTileMapGenerator->AddTileBrush(pacBackgroundCels,  8, SCCT_Wall,   "UpLeft");
		pTileMapGenerator->AddTileBrush(pacBackgroundCels,  9, SCCT_Wall,   "UpRight");
		pTileMapGenerator->AddTileBrush(pacBackgroundCels, 10, SCCT_Wall,   "LeftRightDown");
		pTileMapGenerator->AddTileBrush(pacBackgroundCels, 11, SCCT_Wall,   "UpDownLeft");
		pTileMapGenerator->AddTileBrush(pacBackgroundCels, 12, SCCT_Wall,   "UpDownRight");
		pTileMapGenerator->AddTileBrush(pacBackgroundCels, 13, SCCT_Wall,   "LeftRightUp");
		pTileMapGenerator->AddTileBrush(pacBackgroundCels,  1, SCCT_Floor,  "Single");
		pTileMapGenerator->AddTileBrush(pacBackgroundCels, 14, SCCT_Door,   "DoorUp");
		pTileMapGenerator->AddTileBrush(pacBackgroundCels, 15, SCCT_Door,   "DoorDown");
		pTileMapGenerator->AddTileBrush(pacBackgroundCels, 16, SCCT_Door,   "DoorLeft");
		pTileMapGenerator->AddTileBrush(pacBackgroundCels, 17, SCCT_Door,   "DoorRight");
		pTileMapGenerator->AddTileBrush(pacBackgroundCels, 18, SCCT_Door,   "DoorUp");
		pTileMapGenerator->AddTileBrush(pacBackgroundCels, 19, SCCT_Door,   "DoorDown");
		pTileMapGenerator->AddTileBrush(pacBackgroundCels, 20, SCCT_Door,   "DoorLeft");
		pTileMapGenerator->AddTileBrush(pacBackgroundCels, 21, SCCT_Door,   "DoorRight");
		pTileMapGenerator->AddTileBrush(pacBackgroundCels, 22, SCCT_Shadow, "ShadowLeft");
		pTileMapGenerator->AddTileBrush(pacBackgroundCels, 23, SCCT_Shadow, "ShadowSingle");
		pTileMapGenerator->AddTileBrush(pacBackgroundCels, 24, SCCT_Shadow, "ShadowUpLeft");
		pTileMapGenerator->AddTileBrush(pacBackgroundCels, 25, SCCT_Shadow, "ShadowUp");
		pTileMapGenerator->AddTileBrush(pacBackgroundCels, 27, SCCT_Shadow, "ShadowDown");

		pTileMapGenerator->AddTileGenerator("FloorPlan", SCML_Floor,	 SCCT_Space,  pcSpaceColour);
		pTileMapGenerator->AddTileGenerator("FloorPlan", SCML_Floor,	 SCCT_Wall,	 pcWallColour);
		pTileMapGenerator->AddTileGenerator("FloorPlan", SCML_Floor,	 SCCT_Door,	 pcDoorColour);
		pTileMapGenerator->AddTileGenerator("FloorPlan", SCML_Floor,	 SCCT_Floor,  pcFloorColour);
		pTileMapGenerator->AddTileGenerator("FloorPlan", SCML_Shadow, SCCT_Shadow, pcFloorColour);

		sMapSize = pTileMapGenerator->GetMapSize();
		sCelSize = pTileMapGenerator->GetCelSize();

		pTileMap = pTileMapGenerator->Generate();

		pDestImage = OMalloc<CImage>(sMapSize.x * sCelSize.x, sMapSize.y * sCelSize.y, PT_uint8, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, CHANNEL_STOP);
		pBlitterCache = OMalloc<CImageCelBlitterCache>(pDestImage);

		pMaps = OMalloc<CMaps>(pBlitterCache, pDestImage);;
		pRoot->Add(pMaps);
		pMaps->AddMap(pTileMap);

		pMaps->SetViewportPosition(0, 0);

		bResult = pMaps->CreateCelBlitters();
		AssertTrue(bResult);

		bResult = pMaps->Blit(false);
		AssertTrue(bResult);

		pRoot->Remove(pMaps);
		pRoot->Remove(pTileMapGenerator);
		pMaps = NULL;
		pTileMapGenerator = NULL;

		szOutputFilename.Init(szDirectory);
		cFileUtil.AppendToPath(&szOutputFilename, "TileMapGenerator2x2Generate");
		szOutputFilename.Append(".png");
		bWritten = WriteImage(pDestImage, szOutputFilename.Text(), IT_PNG);
		AssertTrue(bWritten);

		szInputFilename.Init(szOutputFilename);
		szInputFilename.Replace("Output", "Input");

		AssertFile(szInputFilename, szOutputFilename);

		szOutputFilename.Kill();
		szInputFilename.Kill();
	}
	ObjectsFlush();
	ObjectsKill(false);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTileMapGenerator40x40Generate(void)
{
	char				szDirectory[] = "Output" _FS_ "TileMapGenerator40x40Generate";
	CIndexTreeMemory	cMemory;
	CFileUtil			cFileUtil;

	AssertTrue(cFileUtil.RemoveDir(szDirectory));
	AssertTrue(cFileUtil.TouchDir(szDirectory));

	ObjectsInit();
	{
		Ptr<CMaps>					pMaps;
		CImageDivider				cImageDivider;
		CChars						szInputFilename;
		CChars						szOutputFilename;
		Ptr<CRoot>					pRoot;
		Ptr<CTileMapGenerator>		pTileMapGenerator;
		Ptr<CArrayImageCel>			pacBackgroundCels;
		CTileColourSource*			pcWallColour;
		CTileColourSource*			pcFloorColour;
		CTileColourSource*			pcSpaceColour;
		CTileColourSource*			pcDoorColour;
		Ptr<CImage>					pFloorPlanImage;
		Ptr<CTileMap>				pTileMap;
		Ptr<CImage>					pDestImage;
		Ptr<CImageCelBlitterCache>	pBlitterCache;
		SSizeVec2					sMapSize;
		SSizeVec2					sCelSize;
		bool						bResult;
		bool						bWritten;
		CRandom						cRandom;

		pFloorPlanImage = TestReadImage("SpaceCrusade", "FloorPlan.png");

		cRandom.Init(2345);

		pRoot = ORoot();
		pTileMapGenerator = OMalloc<CTileMapGenerator>(&cRandom);
		pRoot->Add(pTileMapGenerator);

		pTileMapGenerator->AddTileGridSource("FloorPlan", pFloorPlanImage);

		pcWallColour = pTileMapGenerator->AddColourSource(138, 138, 138);
		pcFloorColour = pTileMapGenerator->AddColourSource(107, 73, 14);
		pcSpaceColour = pTileMapGenerator->AddColourSource(0, 0, 0);
		pcDoorColour = pTileMapGenerator->AddColourSource(71, 71, 71);

		//Blocks must be rectangular with each row ending with a newline.  Spaces are removed before processing.

		// B: the block being placed.
		// P: required from the same CelType
		// .: any block 
		// !: any block other than the same CelType
		// any other letter or number: defined as another cell type.
		//  e.g. W ->  SCCT_Wall
		//  e.g. w -> !SCCT_Wall

		pTileMapGenerator->AddCelType(		 'W', SCCT_Wall);
		pTileMapGenerator->AddNegativeCelType('w', SCCT_Wall);
		pTileMapGenerator->AddCelType(		 'C', SCCT_Wall, SCCT_Door);
		pTileMapGenerator->AddNegativeCelType('c', SCCT_Wall, SCCT_Door);

		pTileMapGenerator->AddPattern("FloorPlan", SCCT_Space, "Single",	" . . . \n"
																			" . B . \n"
																			" . . . \n");

		pTileMapGenerator->AddPattern("FloorPlan", SCCT_Floor, "Single",	" . . . \n"
																			" . B . \n"
																			" . . . \n");

		pTileMapGenerator->AddPattern("FloorPlan", SCCT_Wall, "Single",		" . c . \n"
																			" c B c \n"
																			" . c . \n");

		pTileMapGenerator->AddPattern("FloorPlan", SCCT_Wall, "UpDown",		" . C . \n"
																			" c B c \n"
																			" . C . \n");

		pTileMapGenerator->AddPattern("FloorPlan", SCCT_Wall, "LeftRight",	" . c . \n"
																			" C B C \n"
																			" . c . \n");

		pTileMapGenerator->AddPattern("FloorPlan", SCCT_Wall, "UpRight",	" . C . \n"
																			" c B C \n"
																			" . c . \n");

		pTileMapGenerator->AddPattern("FloorPlan", SCCT_Wall, "DownRight",	" . c . \n"
																			" c B C \n"
																			" . C . \n");

		pTileMapGenerator->AddPattern("FloorPlan", SCCT_Wall, "DownLeft",	" . c . \n"
																			" C B c \n"
																			" . C . \n");

		pTileMapGenerator->AddPattern("FloorPlan", SCCT_Wall, "UpLeft",		" . C . \n"
																			" C B c \n"
																			" . c . \n");

		pTileMapGenerator->AddPattern("FloorPlan", SCCT_Wall, "LeftRightDown"," . c . \n"
																			" C B C \n"
																			" . C . \n");

		pTileMapGenerator->AddPattern("FloorPlan", SCCT_Wall, "UpDownLeft",	" . C . \n"
																			" C B c \n"
																			" . C . \n");

		pTileMapGenerator->AddPattern("FloorPlan", SCCT_Wall, "UpDownRight"," . C . \n"
																			" c B C \n"
																			" . C . \n");

		pTileMapGenerator->AddPattern("FloorPlan", SCCT_Wall, "LeftRightUp"," . C . \n"
																			" C B C \n"
																			" . c . \n");

		pTileMapGenerator->AddPattern("FloorPlan", SCCT_Door, "DoorDown",	" . W . \n"
																			" . B . \n"
																			" . P . \n");

		pTileMapGenerator->AddPattern("FloorPlan", SCCT_Door, "DoorUp",		" . P . \n"
																			" . B . \n"
																			" . W . \n");

		pTileMapGenerator->AddPattern("FloorPlan", SCCT_Door, "DoorLeft",	" . . . \n"
																			" W B P \n"
																			" . . . \n");

		pTileMapGenerator->AddPattern("FloorPlan", SCCT_Door, "DoorRight",	" . . . \n"
																			" P B W \n"
																			" . . . \n");

		pTileMapGenerator->AddPattern("FloorPlan", SCCT_Shadow, "ShadowLeft"," W w . \n"
																			 " W B . \n"
																			 " . . . \n");

		pTileMapGenerator->AddPattern("FloorPlan", SCCT_Shadow,"ShadowSingle"," W w . \n"
																			  " w B . \n"
																			  " . . . \n");

		pTileMapGenerator->AddPattern("FloorPlan", SCCT_Shadow,"ShadowUpLeft"," W W . \n"
																			  " W B . \n"
																			  " . . . \n");

		pTileMapGenerator->AddPattern("FloorPlan", SCCT_Shadow,"ShadowUp",	 " W W . \n"
																			 " w B . \n"
																			 " . . . \n");

		pTileMapGenerator->AddPattern("FloorPlan", SCCT_Shadow,"ShadowDown", " w w . \n"
																			 " W B . \n"
																			 " . . . \n");

		pacBackgroundCels = TestReadCels("SpaceCrusade", "Tiles.png", 10, 3);

		pTileMapGenerator->AddTileBrush(pacBackgroundCels, 26, SCCT_Space,  "Single");
		pTileMapGenerator->AddTileBrush(pacBackgroundCels,  0, SCCT_Wall,   "Single");
		pTileMapGenerator->AddTileBrush(pacBackgroundCels,  4, SCCT_Wall,   "UpDown");
		pTileMapGenerator->AddTileBrush(pacBackgroundCels,  5, SCCT_Wall,   "LeftRight");
		pTileMapGenerator->AddTileBrush(pacBackgroundCels,  6, SCCT_Wall,   "DownLeft");
		pTileMapGenerator->AddTileBrush(pacBackgroundCels,  7, SCCT_Wall,   "DownRight");
		pTileMapGenerator->AddTileBrush(pacBackgroundCels,  8, SCCT_Wall,   "UpLeft");
		pTileMapGenerator->AddTileBrush(pacBackgroundCels,  9, SCCT_Wall,   "UpRight");
		pTileMapGenerator->AddTileBrush(pacBackgroundCels, 10, SCCT_Wall,   "LeftRightDown");
		pTileMapGenerator->AddTileBrush(pacBackgroundCels, 11, SCCT_Wall,   "UpDownLeft");
		pTileMapGenerator->AddTileBrush(pacBackgroundCels, 12, SCCT_Wall,   "UpDownRight");
		pTileMapGenerator->AddTileBrush(pacBackgroundCels, 13, SCCT_Wall,   "LeftRightUp");
		pTileMapGenerator->AddTileBrush(pacBackgroundCels,  1, SCCT_Floor,  "Single", 2);
		pTileMapGenerator->AddTileBrush(pacBackgroundCels,  2, SCCT_Floor,  "Single", 200);
		pTileMapGenerator->AddTileBrush(pacBackgroundCels,  3, SCCT_Floor,  "Single", 1);
		pTileMapGenerator->AddTileBrush(pacBackgroundCels, 14, SCCT_Door,   "DoorUp");
		pTileMapGenerator->AddTileBrush(pacBackgroundCels, 15, SCCT_Door,   "DoorDown");
		pTileMapGenerator->AddTileBrush(pacBackgroundCels, 16, SCCT_Door,   "DoorLeft");
		pTileMapGenerator->AddTileBrush(pacBackgroundCels, 17, SCCT_Door,   "DoorRight");
		pTileMapGenerator->AddTileBrush(pacBackgroundCels, 18, SCCT_Door,   "DoorUp");
		pTileMapGenerator->AddTileBrush(pacBackgroundCels, 19, SCCT_Door,   "DoorDown");
		pTileMapGenerator->AddTileBrush(pacBackgroundCels, 20, SCCT_Door,   "DoorLeft");
		pTileMapGenerator->AddTileBrush(pacBackgroundCels, 21, SCCT_Door,   "DoorRight");
		pTileMapGenerator->AddTileBrush(pacBackgroundCels, 22, SCCT_Shadow, "ShadowLeft");
		pTileMapGenerator->AddTileBrush(pacBackgroundCels, 23, SCCT_Shadow, "ShadowSingle");
		pTileMapGenerator->AddTileBrush(pacBackgroundCels, 24, SCCT_Shadow, "ShadowUpLeft");
		pTileMapGenerator->AddTileBrush(pacBackgroundCels, 25, SCCT_Shadow, "ShadowUp");
		pTileMapGenerator->AddTileBrush(pacBackgroundCels, 27, SCCT_Shadow, "ShadowDown");

		pTileMapGenerator->AddTileGenerator("FloorPlan", SCML_Floor,	 SCCT_Space,  pcSpaceColour);
		pTileMapGenerator->AddTileGenerator("FloorPlan", SCML_Floor,	 SCCT_Wall,	 pcWallColour);
		pTileMapGenerator->AddTileGenerator("FloorPlan", SCML_Floor,	 SCCT_Door,	 pcDoorColour);
		pTileMapGenerator->AddTileGenerator("FloorPlan", SCML_Floor,	 SCCT_Floor,  pcFloorColour);
		pTileMapGenerator->AddTileGenerator("FloorPlan", SCML_Shadow, SCCT_Shadow, pcFloorColour);

		sMapSize = pTileMapGenerator->GetMapSize();
		sCelSize = pTileMapGenerator->GetCelSize();

		pTileMap = pTileMapGenerator->Generate();

		pDestImage = OMalloc<CImage>(sMapSize.x * sCelSize.x, sMapSize.y * sCelSize.y, PT_uint8, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, CHANNEL_STOP);
		pBlitterCache = OMalloc<CImageCelBlitterCache>(pDestImage);
		
		pMaps = OMalloc<CMaps>(pBlitterCache, pDestImage);;
		pRoot->Add(pMaps);
		pMaps->AddMap(pTileMap);

		pMaps->SetViewportPosition(0, 0);

		bResult = pMaps->CreateCelBlitters();
		AssertTrue(bResult);

		bResult = pMaps->Blit(false);
		AssertTrue(bResult);

		pRoot->Remove(pMaps);
		pRoot->Remove(pTileMapGenerator);
		pMaps = NULL;
		pTileMapGenerator = NULL;

		szOutputFilename.Init(szDirectory);
		cFileUtil.AppendToPath(&szOutputFilename, "TileMapGenerator40x40Generate");
		szOutputFilename.Append(".png");
		bWritten = WriteImage(pDestImage, szOutputFilename.Text(), IT_PNG);
		AssertTrue(bWritten);

		szInputFilename.Init(szOutputFilename);
		szInputFilename.Replace("Output", "Input");

		AssertFile(szInputFilename, szOutputFilename);

		szOutputFilename.Kill();
		szInputFilename.Kill();
	}
	ObjectsFlush();
	ObjectsKill(false);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTileMapGenerator(void)
{
	BeginTests();

	DataIOInit();

	TestTileMapGenerator2x2Generate();
	TestTileMapGenerator40x40Generate();

	DataIOKill();

	TestStatistics();
}

