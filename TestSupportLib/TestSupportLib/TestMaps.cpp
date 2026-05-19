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
Ptr<CImage> ReadSpaceCrusadeImage(char* szFilename)
{
	CFileUtil			cFileUtil;
	CChars				szInputFilename;
	Ptr<CImage>			pImage;

	szInputFilename.Init();
	cFileUtil.CurrentDirectory(&szInputFilename);
	cFileUtil.AppendToPath(&szInputFilename, "Input");
	cFileUtil.AppendToPath(&szInputFilename, "SpaceCrusade");
	cFileUtil.AppendToPath(&szInputFilename, szFilename);
	AssertTrue(cFileUtil.Exists(szInputFilename.Text()));

	pImage = ReadImage(szInputFilename.Text(), IT_Unknown, true);
	AssertTrue(pImage.IsNotNull());
	szInputFilename.Kill();

	return pImage;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
Ptr<CArrayImageCel> ReadSpaceCrusadeCels(char* szFilename, int iColumnCount, int iRowCount)
{
	Ptr<CImage>				pImage;
	CImageDivider			cImageDivider;
	CImageDividerNumbers	cNumbers;
	Ptr<CArrayImageCel>		pCels;

	pImage = ReadSpaceCrusadeImage(szFilename);

	cNumbers.InitGeneral(-1, -1, iColumnCount, iRowCount, 0, 0, 0, 0);
	cImageDivider.Init(pImage, NULL);
	cImageDivider.GenerateFromNumbers(&cNumbers);
	pCels = cImageDivider.GetDestImageCels();

	AssertTrue(pCels.IsNotNull());
	AssertInt(iColumnCount * iRowCount, pCels->NumElements());

	AssertSize(2, pCels.NumStackFroms());
	AssertSize(0, pCels.NumHeapFroms());

	cImageDivider.Kill();

	AssertSize(1, pCels.NumStackFroms());
	AssertSize(0, pCels.NumHeapFroms());

	return pCels;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapsSpriteMap(void)
{
	char				szDirectory[] = "Output" _FS_ "MapsSpriteMap";
	CIndexTreeMemory	cMemory;
	CFileUtil			cFileUtil;

	AssertTrue(cFileUtil.RemoveDir(szDirectory));
	AssertTrue(cFileUtil.TouchDir(szDirectory));

	DataIOInit();
	ObjectsInit();
	{
		CMaps					cMaps;
		CImageDivider			cImageDivider;
		CChars					szInputFilename;
		CChars					szOutputFilename;
		Ptr<CArrayImageCel>		pSoulSuckerCels;
		Ptr<CArrayImageCel>		pBloodAngelsCels;
		Ptr<CArrayImageCel>		pGretchinCels;
		Ptr<CSpriteMap>			pSpriteMap;
		Ptr<CImageCel>			pCel1;
		Ptr<CImageCel>			pCel2;
		Ptr<CImageCel>			pCel3;
		Ptr<CImageCel>			pCel4;
		Ptr<CImageCel>			pCel5;
		Ptr<CImageCel>			pCel6 ;
		CSubImage*				pcSubImage;
		Ptr<CImage>				pWholeMap;
		bool					bWritten;
		size					uiSprite;

		ImageChannelDescriptorInit();

		pSoulSuckerCels = ReadSpaceCrusadeCels("SoulSucker.png", 8, 1);
		pBloodAngelsCels = ReadSpaceCrusadeCels("BloodAngels.png", 8, 1);
		pGretchinCels = ReadSpaceCrusadeCels("Gretchin.png", 8, 1);

		for (uiSprite = 0; uiSprite < 8; uiSprite++)
		{
			pCel1 = pSoulSuckerCels->Get(uiSprite);
			AssertTrue(pCel1.IsNotNull());
		}
		for (uiSprite = 0; uiSprite < 8; uiSprite++)
		{
			pCel1 = pBloodAngelsCels->Get(uiSprite);
			AssertTrue(pCel1.IsNotNull());
		}
		for (uiSprite = 0; uiSprite < 8; uiSprite++)
		{
			pCel1 = pGretchinCels->Get(uiSprite);
			AssertTrue(pCel1.IsNotNull());
		}

		pCel1 = pSoulSuckerCels->Get(7);
		pcSubImage = pCel1->GetSubImage();
		AssertSize(16, pcSubImage->GetFullWidth());
		AssertSize(16, pcSubImage->GetFullHeight());
		AssertSize(15, pcSubImage->GetImageWidth());
		AssertSize(14, pcSubImage->GetImageHeight());

		pCel2 = pSoulSuckerCels->Get(2);
		pcSubImage = pCel2->GetSubImage();
		AssertSize(16, pcSubImage->GetFullWidth());
		AssertSize(16, pcSubImage->GetFullHeight());
		AssertSize(16, pcSubImage->GetImageWidth());
		AssertSize(13, pcSubImage->GetImageHeight());

		pCel3 = pBloodAngelsCels->Get(3);
		pcSubImage = pCel3->GetSubImage();
		AssertSize(16, pcSubImage->GetFullWidth());
		AssertSize(16, pcSubImage->GetFullHeight());
		AssertSize(16, pcSubImage->GetImageWidth());
		AssertSize(16, pcSubImage->GetImageHeight());

		pCel4 = pBloodAngelsCels->Get(0);
		pcSubImage = pCel4->GetSubImage();
		AssertSize(16, pcSubImage->GetFullWidth());
		AssertSize(16, pcSubImage->GetFullHeight());
		AssertSize(16, pcSubImage->GetImageWidth());
		AssertSize(13, pcSubImage->GetImageHeight());

		pCel5 = pGretchinCels->Get(6);
		pcSubImage = pCel5->GetSubImage();
		AssertSize(16, pcSubImage->GetFullWidth());
		AssertSize(16, pcSubImage->GetFullHeight());
		AssertSize(13, pcSubImage->GetImageWidth());
		AssertSize(16, pcSubImage->GetImageHeight());

		pCel6 = pGretchinCels->Get(4);
		pcSubImage = pCel6->GetSubImage();
		AssertSize(16, pcSubImage->GetFullWidth());
		AssertSize(16, pcSubImage->GetFullHeight());
		AssertSize(15, pcSubImage->GetImageWidth());
		AssertSize(13, pcSubImage->GetImageHeight());

		AssertPointer(&pCel1->GetSourceImage(), &pCel2->GetSourceImage());
		AssertPointer(&pCel3->GetSourceImage(), &pCel4->GetSourceImage());
		AssertPointer(&pCel5->GetSourceImage(), &pCel6->GetSourceImage());

		AssertNotPointer(&pCel1->GetSourceImage(), &pCel3->GetSourceImage());
		AssertNotPointer(&pCel3->GetSourceImage(), &pCel5->GetSourceImage());
		AssertNotPointer(&pCel5->GetSourceImage(), &pCel1->GetSourceImage());

		cMaps.Init();
		
		pSpriteMap = OMalloc<CSpriteMap>();
		cMaps.AddMap(pSpriteMap);

		pSpriteMap->AddSprite(OMalloc<CSprite>(pCel1, 18, 29)); 
		pSpriteMap->AddSprite(OMalloc<CSprite>(pCel2,  2, 36));
		pSpriteMap->AddSprite(OMalloc<CSprite>(pCel3, 31,  9));
		pSpriteMap->AddSprite(OMalloc<CSprite>(pCel4, 39, 27));
		pSpriteMap->AddSprite(OMalloc<CSprite>(pCel5, 11,  3));
		pSpriteMap->AddSprite(OMalloc<CSprite>(pCel6, 25, 19));

		AssertSize(6, pSpriteMap->NumSprites());

		szOutputFilename.Init(szDirectory);
		cFileUtil.AppendToPath(&szOutputFilename, "TestSpriteMap.png");

		pWholeMap = pSpriteMap->WriteToImage();
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
void TestMapsTileMap(void)
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

	TestMapsTileMap();
	TestMapsSpriteMap();

	TestStatistics();
}

