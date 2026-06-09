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

		ImageChannelDescriptorInit();

		pBackground = TestMapViewportReadImage("SpaceCrusade", "Tiles.png");
		pSoulSuckerCels = TestMapViewportReadCels("SoulSucker.png", 8, 1);
		pBloodAngelsCels = TestMapViewportReadCels("BloodAngels.png", 8, 1);
		pGretchinCels = TestMapViewportReadCels("Gretchin.png", 8, 1);

		cNumbers.InitGeneral(-1, -1, 10, 3, 0, 0, 0, 0);
		cImageDivider.Init(&pBackground, NULL);
		cImageDivider.GenerateFromNumbers(&cNumbers);
		pacBackgroundCels = cImageDivider.GetDestImageCels();
		AssertSize(30, pacBackgroundCels->NumElements());

		pDestImage = OMalloc<CImage>(32, 32, PT_uint8, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, CHANNEL_STOP);
		pBlitterCache = OMalloc<CImageCelBlitterCache>(pDestImage);
		cMaps.Init(pBlitterCache, pBlitterCache);

		pTileMap = OMalloc<CTileMap>();
		cMaps.AddMap(pTileMap);
		pCelLayer = OMalloc<CTileLayerCel>(pTileMap, "Cel", SInt32Vec2(4, 4), SInt32Vec2(16, 16), SInt32Vec2(0, 0));
		pCelLayer->SetTiles(0, 0, pacBackgroundCels, 7, 5, 5, 6);
		pCelLayer->SetTiles(0, 1, pacBackgroundCels, 19, 2, 2, 4);
		pCelLayer->SetTiles(0, 2, pacBackgroundCels, 18, 2, 3, 4);
		pCelLayer->SetTiles(0, 3, pacBackgroundCels, 9, 5, 5, 8);

		cMaps.Blit();

		bWritten = WriteImage(pDestImage, szOutputFilename.Text(), IT_PNG);
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

