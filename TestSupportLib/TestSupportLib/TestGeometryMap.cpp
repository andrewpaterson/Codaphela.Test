#include "BaseLib/GlobalDataTypesIO.h"
#include "StandardLib/Objects.h"
#include "SupportLib/ImageAccessorCreator.h"
#include "SupportLib/ColourARGB32.h"
#include "SupportLib/GeometryMap.h"
#include "SupportLib/Maps.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
// Red, green, blue and opacity (255 if the image has none).
//
//////////////////////////////////////////////////////////////////////////
void GetGeometryPixel(Ptr<CImage> pImage, int32 x, int32 y, uint8* puiRGBA)
{
	CImageAccessorCreator	cCreator;
	CImageAccessor*			pcAccessor;

	cCreator.Init(&pImage);
	if (pImage->HasChannel(IMAGE_OPACITY))
	{
		cCreator.AddAccess(IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, IMAGE_OPACITY, PT_uint8);
		pcAccessor = cCreator.CreateAndKill();
		pcAccessor->Get(x, y, puiRGBA);
	}
	else
	{
		cCreator.AddAccess(IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, PT_uint8);
		pcAccessor = cCreator.CreateAndKill();
		pcAccessor->Get(x, y, puiRGBA);
		puiRGBA[3] = 255;
	}
	pcAccessor->Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertGeometryPixel(int iRed, int iGreen, int iBlue, int iOpacity, Ptr<CImage> pImage, int32 x, int32 y)
{
	uint8	auiRGBA[4];

	GetGeometryPixel(pImage, x, y, auiRGBA);
	AssertInt(iRed, auiRGBA[0]);
	AssertInt(iGreen, auiRGBA[1]);
	AssertInt(iBlue, auiRGBA[2]);
	AssertInt(iOpacity, auiRGBA[3]);
}


//////////////////////////////////////////////////////////////////////////
//
// Rectangles are filled with their right and bottom edges excluded.  A
// translucent colour is blended with what is there.
//
//////////////////////////////////////////////////////////////////////////
void TestGeometryMapRectangles(void)
{
	ObjectsInit();
	{
		Ptr<CImage>			pImage;
		Ptr<CGeometryMap>	pMap;
		CInt32Rect			cViewport;

		pImage = OMalloc<CImage>(8, 6, PT_uint8, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, CHANNEL_STOP);
		pImage->Black();
		pMap = OMalloc<CGeometryMap>();
		pMap->SetViewport(pImage);
		AssertTrue(pMap->GetViewport() == pImage);

		pMap->AddRectangle(1, 1, 3, 2, Set32BitColour((uint8)255, (uint8)0, (uint8)0));
		pMap->AddRectangle(0, 0, 0, 5, Set32BitColour((uint8)255, (uint8)0, (uint8)0));
		pMap->AddRectangle(0, 0, 5, -1, Set32BitColour((uint8)255, (uint8)0, (uint8)0));
		AssertSize(1, pMap->NumCommands());
		AssertInt(4, pMap->GetCommand(0)->cBounds.msBottomRight.x);
		AssertInt(3, pMap->GetCommand(0)->cBounds.msBottomRight.y);

		//Half covered green, partly off the image.
		pMap->AddRectangle(5, 3, 10, 10, Set32BitColour((uint8)0, (uint8)255, (uint8)0, (uint8)128));
		AssertSize(2, pMap->NumCommands());

		cViewport.Init(0, 0, 8, 6);
		AssertTrue(pMap->Blit(&cViewport, false));
		AssertGeometryPixel(255, 0, 0, 255, pImage, 1, 1);
		AssertGeometryPixel(255, 0, 0, 255, pImage, 3, 2);
		AssertGeometryPixel(0, 0, 0, 255, pImage, 4, 1);
		AssertGeometryPixel(0, 0, 0, 255, pImage, 1, 3);
		AssertGeometryPixel(0, 0, 0, 255, pImage, 0, 0);
		AssertGeometryPixel(0, 128, 0, 255, pImage, 5, 3);
		AssertGeometryPixel(0, 128, 0, 255, pImage, 7, 5);
		AssertGeometryPixel(0, 0, 0, 255, pImage, 4, 3);

		pMap->Clear();
		AssertSize(0, pMap->NumCommands());

		pMap = NULL;
		pImage = NULL;
	}
	ObjectsKill(false);
}


//////////////////////////////////////////////////////////////////////////
//
// On an image with opacity cleared to nothing a translucent colour leaves
// premultiplied pixels, as a translucent cel does.
//
//////////////////////////////////////////////////////////////////////////
void TestGeometryMapOpacity(void)
{
	ObjectsInit();
	{
		Ptr<CImage>			pImage;
		Ptr<CGeometryMap>	pMap;
		CInt32Rect			cViewport;

		pImage = OMalloc<CImage>(4, 4, PT_uint8, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, IMAGE_OPACITY, CHANNEL_STOP);
		pImage->Black();
		AssertGeometryPixel(0, 0, 0, 0, pImage, 0, 0);

		pMap = OMalloc<CGeometryMap>();
		pMap->SetViewport(pImage);
		pMap->AddRectangle(0, 0, 2, 1, Set32BitColour((uint8)255, (uint8)0, (uint8)0));
		pMap->AddRectangle(0, 1, 2, 1, Set32BitColour((uint8)255, (uint8)0, (uint8)0, (uint8)128));
		pMap->AddRectangle(0, 1, 1, 1, Set32BitColour((uint8)0, (uint8)0, (uint8)255, (uint8)128));
		cViewport.Init(0, 0, 4, 4);
		AssertTrue(pMap->Blit(&cViewport, false));

		AssertGeometryPixel(255, 0, 0, 255, pImage, 0, 0);
		AssertGeometryPixel(128, 0, 0, 128, pImage, 1, 1);

		//Half blue over half red: the red is halved, the opacity is 128 + 128 * 127 / 255.
		AssertGeometryPixel(64, 0, 128, 192, pImage, 0, 1);
		AssertGeometryPixel(0, 0, 0, 0, pImage, 2, 0);

		pMap = NULL;
		pImage = NULL;
	}
	ObjectsKill(false);
}


//////////////////////////////////////////////////////////////////////////
//
// The viewport rectangle's top left is drawn at the image's top left.
// Shapes outside it aren't drawn.
//
//////////////////////////////////////////////////////////////////////////
void TestGeometryMapViewport(void)
{
	ObjectsInit();
	{
		Ptr<CImage>			pImage;
		Ptr<CGeometryMap>	pMap;
		CInt32Rect			cViewport;

		pImage = OMalloc<CImage>(8, 6, PT_uint8, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, CHANNEL_STOP);
		pImage->Black();
		pMap = OMalloc<CGeometryMap>();
		pMap->SetViewport(pImage);
		pMap->AddRectangle(3, 2, 1, 1, Set32BitColour((uint8)255, (uint8)255, (uint8)255));
		pMap->AddRectangle(-20, -20, 5, 5, Set32BitColour((uint8)255, (uint8)255, (uint8)255));
		pMap->AddRectangle(0, 0, 3, 1, Set32BitColour((uint8)255, (uint8)255, (uint8)255));
		pMap->AddRectangle(8, 5, 4, 4, Set32BitColour((uint8)255, (uint8)255, (uint8)255));

		cViewport.Init(2, 1, 10, 7);
		AssertTrue(pMap->Blit(&cViewport, false));
		AssertGeometryPixel(255, 255, 255, 255, pImage, 1, 1);
		AssertGeometryPixel(0, 0, 0, 255, pImage, 0, 0);
		AssertGeometryPixel(0, 0, 0, 255, pImage, 2, 1);
		AssertGeometryPixel(255, 255, 255, 255, pImage, 6, 4);
		AssertGeometryPixel(255, 255, 255, 255, pImage, 7, 5);
		AssertGeometryPixel(0, 0, 0, 255, pImage, 5, 4);

		pMap = NULL;
		pImage = NULL;
	}
	ObjectsKill(false);
}


//////////////////////////////////////////////////////////////////////////
//
// Colours go to the image's own channels whatever their order.
//
//////////////////////////////////////////////////////////////////////////
void TestGeometryMapColourOrder(void)
{
	ObjectsInit();
	{
		Ptr<CImage>			pImage;
		Ptr<CGeometryMap>	pMap;
		CInt32Rect			cViewport;
		uint8*				puiData;

		pImage = OMalloc<CImage>(2, 1, PT_uint8, IMAGE_DIFFUSE_BLUE, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_RED, CHANNEL_STOP);
		pImage->Black();
		AssertInt(CCO_BGR, pImage->GetColourOrder());
		pMap = OMalloc<CGeometryMap>();
		pMap->SetViewport(pImage);
		pMap->AddRectangle(0, 0, 1, 1, Set32BitColour((uint8)255, (uint8)16, (uint8)0));
		cViewport.Init(0, 0, 2, 1);
		AssertTrue(pMap->Blit(&cViewport, false));
		AssertGeometryPixel(255, 16, 0, 255, pImage, 0, 0);

		puiData = (uint8*)pImage->GetData();
		AssertInt(0, puiData[0]);
		AssertInt(16, puiData[1]);
		AssertInt(255, puiData[2]);

		pMap = NULL;
		pImage = NULL;
	}
	ObjectsKill(false);
}


//////////////////////////////////////////////////////////////////////////
//
// A geometry map is drawn by CMaps with the other maps, at the maps'
// viewport position.
//
//////////////////////////////////////////////////////////////////////////
void TestGeometryMapInMaps(void)
{
	ObjectsInit();
	{
		Ptr<CImage>			pImage;
		Ptr<CGeometryMap>	pMap;
		Ptr<CMaps>			pMaps;

		pImage = OMalloc<CImage>(8, 6, PT_uint8, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, CHANNEL_STOP);
		pImage->Black();
		pMap = OMalloc<CGeometryMap>();
		AssertTrue(pMap->GetBlockMap() == NULL);
		pMap->AddRectangle(4, 3, 2, 1, Set32BitColour((uint8)0, (uint8)0, (uint8)255));

		pMaps = OMalloc<CMaps>();
		pMaps->AddMap(pMap);
		pMaps->SetCacheAndViewport(pImage->GetBlitterCache(), pImage);
		AssertTrue(pMap->GetViewport() == pImage);
		AssertTrue(pMaps->HasCelBlitters());
		pMaps->SetViewportPosition(1, 1);
		AssertTrue(pMaps->Blit(false));
		AssertGeometryPixel(0, 0, 255, 255, pImage, 3, 2);
		AssertGeometryPixel(0, 0, 255, 255, pImage, 4, 2);
		AssertGeometryPixel(0, 0, 0, 255, pImage, 5, 2);

		pMaps = NULL;
		pMap = NULL;
		pImage = NULL;
	}
	ObjectsKill(false);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestGeometryMap(void)
{
	BeginTests();

	DataIOInit();

	TestGeometryMapRectangles();
	TestGeometryMapOpacity();
	TestGeometryMapViewport();
	TestGeometryMapColourOrder();
	TestGeometryMapInMaps();

	DataIOKill();

	TestStatistics();
}

