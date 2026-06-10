#include "BaseLib/GlobalDataTypesIO.h"
#include "StandardLib/Pointer.h"
#include "SupportLib/ImageReader.h"
#include "SupportLib/ImageWriter.h"
#include "SupportLib/ImageDivider.h"
#include "SupportLib/Maps.h"
#include "SupportLib/MapViewport.h"
#include "SupportLib/TileLayerCel.h"
#include "TestLib/Assert.h"
#include "SupportAssert.h"



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
Ptr<CImage> TestMapViewportReadImage(char* szDirectory, char* szFilename)
{
	CFileUtil	cFileUtil;
	CChars		szInputFilename;
	Ptr<CImage>	pImage;

	szInputFilename.Init();
	cFileUtil.CurrentDirectory(&szInputFilename);
	cFileUtil.AppendToPath(&szInputFilename, "Input");
	cFileUtil.AppendToPath(&szInputFilename, szDirectory);
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
Ptr<CArrayImageCel> TestMapViewportReadCels(char* szDirectory, char* szFilename, int iColumnCount, int iRowCount)
{
	Ptr<CImage>				pImage;
	CImageDivider			cImageDivider;
	CImageDividerNumbers	cNumbers;
	Ptr<CArrayImageCel>		pCels;

	pImage = TestMapViewportReadImage(szDirectory, szFilename);

	cNumbers.InitGeneral(-1, -1, iColumnCount, iRowCount, 0, 0, 0, 0);
	cImageDivider.Init(pImage, NULL);
	cImageDivider.GenerateFromNumbers(&cNumbers);
	pCels = cImageDivider.GetDestImageCels();

	cImageDivider.Kill();

	return pCels;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
Ptr<CArrayImageCel> TestMapViewportReadCels(char* szFilename, int iColumnCount, int iRowCount)
{
	return TestMapViewportReadCels("SpaceCrusade", szFilename, iColumnCount, iRowCount);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapViewportBlit(void)
{
	char				szDirectory[] = "Output" _FS_ "MapsViewport";
	CIndexTreeMemory	cMemory;
	CFileUtil			cFileUtil;

	AssertTrue(cFileUtil.RemoveDir(szDirectory));
	AssertTrue(cFileUtil.TouchDir(szDirectory));

	ObjectsInit();
	{
		CMaps						cMaps;
		CImageDivider				cImageDivider;
		CImageDividerNumbers		cNumbers;
		Ptr<CArrayImageCel>			pacBackgroundCels;
		CChars						szInputFilename;
		CChars						szOutputFilename;
		Ptr<CImage>					pBackground;
		Ptr<CTileMap>				pTileMap;
		Ptr<CTileLayerCel>			pCelLayer;
		Ptr<CImageCel>				pCel;
		bool						bWritten;
		Ptr<CImage>					pDestImage;
		Ptr<CImageCelBlitterCache>	pBlitterCache;
		Ptr<CArrayImageCel>			pSoulSuckerCels;
		Ptr<CArrayImageCel>			pBloodAngelsCels;
		Ptr<CArrayImageCel>			pGretchinCels;
		bool						bResult;
		Ptr<CSpriteMap>				pSpriteMap;
		Ptr<CImageCel>				pCel1;
		Ptr<CImageCel>				pCel2;
		Ptr<CImageCel>				pCel3;
		Ptr<CImageCel>				pCel4;
		Ptr<CImageCel>				pCel5;
		Ptr<CImageCel>				pCel6;
		int32						x, y;

		ImageChannelDescriptorInit();

		pBackground = TestMapViewportReadImage("SpaceCrusade", "Tiles.png");
		pSoulSuckerCels = TestMapViewportReadCels("SoulSucker.png", 8, 1);
		pBloodAngelsCels = TestMapViewportReadCels("BloodAngels.png", 8, 1);
		pGretchinCels = TestMapViewportReadCels("Gretchin.png", 8, 1);
		pCel1 = pSoulSuckerCels->Get(7);
		pCel2 = pSoulSuckerCels->Get(2);
		pCel3 = pBloodAngelsCels->Get(3);
		pCel4 = pBloodAngelsCels->Get(0);
		pCel5 = pGretchinCels->Get(6);
		pCel6 = pGretchinCels->Get(4);

		cNumbers.InitGeneral(-1, -1, 10, 3, 0, 0, 0, 0);
		cImageDivider.Init(&pBackground, NULL);
		cImageDivider.GenerateFromNumbers(&cNumbers);
		pacBackgroundCels = cImageDivider.GetDestImageCels();
		AssertSize(30, pacBackgroundCels->NumElements());

		pDestImage = OMalloc<CImage>(32, 32, PT_uint8, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, CHANNEL_STOP);
		pBlitterCache = OMalloc<CImageCelBlitterCache>(pDestImage);
		cMaps.Init(pBlitterCache, pDestImage);

		pTileMap = OMalloc<CTileMap>();
		pCelLayer = OMalloc<CTileLayerCel>(pTileMap, "Cel", SInt32Vec2(4, 4), SInt32Vec2(16, 16), SInt32Vec2(0, 0));
		pCelLayer->SetTiles(0, 0, pacBackgroundCels, 7, 5, 5, 6);
		pCelLayer->SetTiles(0, 1, pacBackgroundCels, 19, 2, 2, 4);
		pCelLayer->SetTiles(0, 2, pacBackgroundCels, 18, 2, 3, 4);
		pCelLayer->SetTiles(0, 3, pacBackgroundCels, 9, 5, 5, 8);
		pTileMap->AddLayer(pCelLayer);

		cMaps.AddMap(pTileMap);

		pSpriteMap = OMalloc<CSpriteMap>();
		cMaps.AddMap(pSpriteMap);

		pSpriteMap->AddSprite(OMalloc<CSprite>(pCel1, 0, 0));
		pSpriteMap->AddSprite(OMalloc<CSprite>(pCel2, 16, 16));
		pSpriteMap->AddSprite(OMalloc<CSprite>(pCel3, 0, 32));
		pSpriteMap->AddSprite(OMalloc<CSprite>(pCel4, 32, 0));
		pSpriteMap->AddSprite(OMalloc<CSprite>(pCel5, 32, 32));
		pSpriteMap->AddSprite(OMalloc<CSprite>(pCel6, 48, 16));

		bResult = cMaps.CreateCelBlitters();
		AssertTrue(bResult);

		for (x = 8; x < 24; x++)
		{
			y = x;
			cMaps.SetViewportPosition(x, y);
			bResult = cMaps.Blit();
			AssertTrue(bResult);

			szOutputFilename.Init(szDirectory);
			cFileUtil.AppendToPath(&szOutputFilename, "TestViewportBlit");
			szOutputFilename.Append(x - 8);
			szOutputFilename.Append(".png");
			bWritten = WriteImage(pDestImage, szOutputFilename.Text(), IT_PNG);
			AssertTrue(bWritten);

			szInputFilename.Init(szOutputFilename);
			szInputFilename.Replace("Output", "Input");

			AssertFile(szInputFilename, szOutputFilename);

			szOutputFilename.Kill();
			szInputFilename.Kill();
		}

		cMaps.Kill();

		ImageChannelDescriptorKill();


	}
	ObjectsKill();
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapViewport(void)
{
	BeginTests();

	DataIOInit();

	TestMapViewportBlit();

	DataIOKill();

	TestStatistics();
}

