#include "BaseLib/GlobalDataTypesIO.h"
#include "StandardLib/Pointer.h"
#include "SupportLib/ImageReader.h"
#include "SupportLib/ImageWriter.h"
#include "SupportLib/ImageDivider.h"
#include "SupportLib/Maps.h"
#include "SupportLib/TileLayerCel.h"
#include "SupportLib/ImageWriter.h"
#include "TestLib/Assert.h"
#include "SupportAssert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapsGenerate(void)
{
	char				szDirectory[] = "Output" _FS_ "MapsGenerate";
	CIndexTreeMemory	cMemory;
	CFileUtil			cFileUtil;

	AssertTrue(cFileUtil.RemoveDir(szDirectory));
	AssertTrue(cFileUtil.TouchDir(szDirectory));

	DataIOInit();
	ObjectsInit();
	{
		CMaps					cMaps;
		CImageDivider			cImageDivider;
		CImageDividerNumbers	cNumbers;
		Ptr<CArrayImageCel>		pacBackgroundCels;
		CChars					szInputFilename;
		CChars					szOutputFilename;
		Ptr<CImage>				pBackground;
		Ptr<CTileMap>			pTileMap;
		Ptr<CTileLayerCel>		pCelLayer;
		Ptr<CImageCel>			pCel;
		CSubImage*				pcSubImage;
		bool					b1, b2, b3, b4;
		Ptr<CImage>				pWholeMap;
		bool					bWritten;
		size					uiTile;

		ImageChannelDescriptorInit();

		szInputFilename.Init();
		cFileUtil.CurrentDirectory(&szInputFilename);
		cFileUtil.AppendToPath(&szInputFilename, "Input");
		cFileUtil.AppendToPath(&szInputFilename, "SpaceCrusade");
		cFileUtil.AppendToPath(&szInputFilename, "Tiles.png");
		AssertTrue(cFileUtil.Exists(szInputFilename.Text()));

		pBackground = ReadImage(szInputFilename.Text(), IT_Unknown, true);
		AssertTrue(pBackground.IsNotNull());
		szInputFilename.Kill();

		cNumbers.InitGeneral(-1, -1, 10, 3, 0, 0, 0, 0);
		cImageDivider.Init(&pBackground, NULL);
		cImageDivider.GenerateFromNumbers(&cNumbers);
		pacBackgroundCels = cImageDivider.GetDestImageCels();
		AssertSize(30, pacBackgroundCels->NumElements());

		pCel = pacBackgroundCels->Get(0);
		pcSubImage = pCel->GetSubImage();
		AssertSize(16, pcSubImage->GetFullWidth());
		AssertSize(16, pcSubImage->GetFullHeight());

		for (uiTile = 0; uiTile < 30; uiTile++)
		{
			pCel = pacBackgroundCels->Get(uiTile);
			AssertTrue(pCel.IsNotNull());
		}

		cMaps.Init();
		
		pTileMap = OMalloc<CTileMap>();
		cMaps.AddMap(pTileMap);
		pCelLayer = OMalloc<CTileLayerCel>(pTileMap, "Cel", SInt32Vec2(4, 4), SInt32Vec2(16, 16), SInt32Vec2(0, 0));
		b1 = pCelLayer->SetTiles(0, 0, pacBackgroundCels,  7, 5, 5, 6);
		b2 = pCelLayer->SetTiles(0, 1, pacBackgroundCels, 19, 2, 2, 4);
		b3 = pCelLayer->SetTiles(0, 2, pacBackgroundCels, 18, 2, 3, 4);
		b4 = pCelLayer->SetTiles(0, 3, pacBackgroundCels,  9, 5, 5, 8);
		AssertTrue(b1);
		AssertTrue(b2);
		AssertTrue(b3);
		AssertTrue(b4);

		szOutputFilename.Init(szDirectory);
		cFileUtil.AppendToPath(&szOutputFilename, "TestTileLayer.png");

		pWholeMap = pCelLayer->WriteToImage();
		AssertTrue(pWholeMap.IsNotNull());

		bWritten = WriteImage(pWholeMap, szOutputFilename.Text(), IT_PNG);
		AssertTrue(bWritten);

		cMaps.Kill();

		ImageChannelDescriptorKill();

		szInputFilename.Init(szOutputFilename);
		szInputFilename.Replace("Output", "Input");

		AssertFile(szInputFilename, szOutputFilename);

		szOutputFilename.Kill();
		szInputFilename.Kill();
	}
	ObjectsKill();
	DataIOKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMaps(void)
{
	BeginTests();

	TestMapsGenerate();

	TestStatistics();
}

