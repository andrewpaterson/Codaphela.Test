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
void TestTileMapGeneratorGenerate(void)
{
	char				szDirectory[] = "Output" _FS_ "TileMapGeneratorGenerate";
	CIndexTreeMemory	cMemory;
	CFileUtil			cFileUtil;

	AssertTrue(cFileUtil.RemoveDir(szDirectory));
	AssertTrue(cFileUtil.TouchDir(szDirectory));

	ObjectsInit();
	{
		CMaps					cMaps;
		CImageDivider			cImageDivider;
		//CChars				szInputFilename;
		//CChars				szOutputFilename;
		CTileMapGenerator		cTileMapGenerator;
		Ptr<CArrayImageCel>		pacBackgroundCels;
		CTileColourSource*		pcWallColour;
		CTileColourSource*		pcFloorColour;
		CTileColourSource*		pcSpaceColour;
		CTileColourSource*		pcDoorColour;
		Ptr<CImage>				pFloorPlan;

		pFloorPlan = TestReadImage("SpaceCrusade", "FloorPlan.png");

		cTileMapGenerator.Init();

		cTileMapGenerator.AddTileGridSource("FloorPlan", pFloorPlan);

		pcWallColour = cTileMapGenerator.AddColourSource(138, 138, 138);
		pcFloorColour = cTileMapGenerator.AddColourSource(107, 73, 14);
		pcSpaceColour = cTileMapGenerator.AddColourSource(0, 0, 0);
		pcDoorColour = cTileMapGenerator.AddColourSource(71, 71, 71);

		//Blocks must be rectangular with each row ending with a newline.  Spaces are removed before processing.

		// B: the block being placed.
		// P: required from the same CelType
		// .: any block 
		// !: any block other than the same CelType
		// any other letter or number: defined as another cell type.
		//  e.g. W ->  SCCT_Wall
		//  e.g. w -> !SCCT_Wall

		cTileMapGenerator.AddCelType(		 'W', SCCT_Wall);
		cTileMapGenerator.AddNegativeCelType('w', SCCT_Wall);

		cTileMapGenerator.AddPattern("FloorPlan", SCCT_Floor, "Single",		" . . . \n"
																			" . B . \n"
																			" . . . \n");

		cTileMapGenerator.AddPattern("FloorPlan", SCCT_Wall, "Single",		" . ! . \n"
																			" ! B ! \n"
																			" . ! . \n");

		cTileMapGenerator.AddPattern("FloorPlan", SCCT_Wall, "UpDown",		" . P . \n"
																			" ! B ! \n"
																			" . P . \n");

		cTileMapGenerator.AddPattern("FloorPlan", SCCT_Wall, "LeftRight",	" . ! . \n"
																			" P B P \n"
																			" . ! . \n");

		cTileMapGenerator.AddPattern("FloorPlan", SCCT_Wall, "UpRight",		" . P . \n"
																			" ! B P \n"
																			" . ! . \n");

		cTileMapGenerator.AddPattern("FloorPlan", SCCT_Wall, "DownRight",	" . ! . \n"
																			" ! B P \n"
																			" . P . \n");

		cTileMapGenerator.AddPattern("FloorPlan", SCCT_Wall, "DownLeft",	" . ! . \n"
																			" P B ! \n"
																			" . P . \n");

		cTileMapGenerator.AddPattern("FloorPlan", SCCT_Wall, "UpLeft",		" . P . \n"
																			" P B ! \n"
																			" . ! . \n");

		cTileMapGenerator.AddPattern("FloorPlan", SCCT_Wall, "LeftRightDown"," . ! . \n"
																			" P B P \n"
																			" . P . \n");

		cTileMapGenerator.AddPattern("FloorPlan", SCCT_Wall, "UpDownLeft",	" . P . \n"
																			" P B ! \n"
																			" . P . \n");

		cTileMapGenerator.AddPattern("FloorPlan", SCCT_Wall, "UpDownRight",	" . P . \n"
																			" ! B P \n"
																			" . P . \n");

		cTileMapGenerator.AddPattern("FloorPlan", SCCT_Wall, "LeftRightUp",	" . P . \n"
																			" P B P \n"
																			" . ! . \n");

		cTileMapGenerator.AddPattern("FloorPlan", SCCT_Door, "DoorDown",	" . W . \n"
																			" . B . \n"
																			" . P . \n");

		cTileMapGenerator.AddPattern("FloorPlan", SCCT_Door, "DoorUp",		" . P . \n"
																			" . B . \n"
																			" . W . \n");

		cTileMapGenerator.AddPattern("FloorPlan", SCCT_Door, "DoorLeft",	" . . . \n"
																			" W B P \n"
																			" . . . \n");

		cTileMapGenerator.AddPattern("FloorPlan", SCCT_Door, "DoorRight",	" . . . \n"
																			" P B W \n"
																			" . . . \n");

		cTileMapGenerator.AddPattern("FloorPlan", SCCT_Shadow, "ShadowLeft"," W w . \n"
																			" W B . \n"
																			" . . . \n");

		cTileMapGenerator.AddPattern("FloorPlan", SCCT_Shadow,"ShadowSingle"," W w . \n"
																			" w B . \n"
																			" . . . \n");

		cTileMapGenerator.AddPattern("FloorPlan", SCCT_Shadow,"ShadowUpLeft"," W W . \n"
																			" W B . \n"
																			" . . . \n");

		cTileMapGenerator.AddPattern("FloorPlan", SCCT_Shadow,"ShadowUp",	" W W . \n"
																			" w B . \n"
																			" . . . \n");

		cTileMapGenerator.AddPattern("FloorPlan", SCCT_Shadow,"ShadowDown",	" w w . \n"
																			" W B . \n"
																			" . . . \n");

		pacBackgroundCels = TestReadCels("SpaceCrusade", "Tiles.png", 10, 3);

		cTileMapGenerator.AddTileBrush(pacBackgroundCels, 26, SCCT_Space,  "Single");
		cTileMapGenerator.AddTileBrush(pacBackgroundCels,  0, SCCT_Wall,   "Single");
		cTileMapGenerator.AddTileBrush(pacBackgroundCels,  4, SCCT_Wall,   "UpDown");
		cTileMapGenerator.AddTileBrush(pacBackgroundCels,  5, SCCT_Wall,   "LeftRight");
		cTileMapGenerator.AddTileBrush(pacBackgroundCels,  6, SCCT_Wall,   "DownLeft");
		cTileMapGenerator.AddTileBrush(pacBackgroundCels,  7, SCCT_Wall,   "DownRight");
		cTileMapGenerator.AddTileBrush(pacBackgroundCels,  8, SCCT_Wall,   "UpLeft");
		cTileMapGenerator.AddTileBrush(pacBackgroundCels,  9, SCCT_Wall,   "UpRight");
		cTileMapGenerator.AddTileBrush(pacBackgroundCels, 10, SCCT_Wall,   "LeftRightDown");
		cTileMapGenerator.AddTileBrush(pacBackgroundCels, 11, SCCT_Wall,   "UpDownLeft");
		cTileMapGenerator.AddTileBrush(pacBackgroundCels, 12, SCCT_Wall,   "UpDownRight");
		cTileMapGenerator.AddTileBrush(pacBackgroundCels, 13, SCCT_Wall,   "LeftRightUp");
		cTileMapGenerator.AddTileBrush(pacBackgroundCels,  1, SCCT_Floor,  "Single");
		cTileMapGenerator.AddTileBrush(pacBackgroundCels,  2, SCCT_Floor,  "Single");
		cTileMapGenerator.AddTileBrush(pacBackgroundCels,  3, SCCT_Floor,  "Single");
		cTileMapGenerator.AddTileBrush(pacBackgroundCels, 14, SCCT_Door,   "DoorUp");
		cTileMapGenerator.AddTileBrush(pacBackgroundCels, 15, SCCT_Door,   "DoorDown");
		cTileMapGenerator.AddTileBrush(pacBackgroundCels, 16, SCCT_Door,   "DoorLeft");
		cTileMapGenerator.AddTileBrush(pacBackgroundCels, 17, SCCT_Door,   "DoorRight");
		cTileMapGenerator.AddTileBrush(pacBackgroundCels, 18, SCCT_Door,   "DoorUp");
		cTileMapGenerator.AddTileBrush(pacBackgroundCels, 19, SCCT_Door,   "DoorDown");
		cTileMapGenerator.AddTileBrush(pacBackgroundCels, 20, SCCT_Door,   "DoorLeft");
		cTileMapGenerator.AddTileBrush(pacBackgroundCels, 21, SCCT_Door,   "DoorRight");
		cTileMapGenerator.AddTileBrush(pacBackgroundCels, 22, SCCT_Shadow, "ShadowLeft");
		cTileMapGenerator.AddTileBrush(pacBackgroundCels, 23, SCCT_Shadow, "ShadowSingle");
		cTileMapGenerator.AddTileBrush(pacBackgroundCels, 24, SCCT_Shadow, "ShadowUpLeft");
		cTileMapGenerator.AddTileBrush(pacBackgroundCels, 25, SCCT_Shadow, "ShadowUp");
		cTileMapGenerator.AddTileBrush(pacBackgroundCels, 27, SCCT_Shadow, "ShadowDown");

		cTileMapGenerator.AddTileGenerator("FloorPlan", SCML_Floor,	 SCCT_Space,  pcSpaceColour);
		cTileMapGenerator.AddTileGenerator("FloorPlan", SCML_Floor,	 SCCT_Wall,	 pcWallColour);
		cTileMapGenerator.AddTileGenerator("FloorPlan", SCML_Floor,	 SCCT_Door,	 pcDoorColour);
		cTileMapGenerator.AddTileGenerator("FloorPlan", SCML_Floor,	 SCCT_Floor,  pcFloorColour);
		cTileMapGenerator.AddTileGenerator("FloorPlan", SCML_Shadow, SCCT_Shadow, pcFloorColour);

		cTileMapGenerator.Generate();

		CTileMap
		//szOutputFilename.Kill();
		//szInputFilename.Kill();
	}
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

	TestTileMapGeneratorGenerate();

	DataIOKill();

	TestStatistics();
}

