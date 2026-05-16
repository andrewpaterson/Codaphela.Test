#include "BaseLib/GlobalDataTypesIO.h"
#include "StandardLib/Pointer.h"
#include "SupportLib/ImageReader.h"
#include "SupportLib/ImageWriter.h"
#include "SupportLib/ImageDivider.h"
#include "SupportLib/Maps.h"
#include "SupportLib/MapViewport.h"
#include "TestLib/Assert.h"
#include "SupportAssert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapViewportRender(void)
{
	DataIOInit();
	ObjectsInit();
	{
		Ptr<CMaps>				pMaps;
		Ptr<CMapsContext>		pContext;
		Ptr<CMapViewport>		pViewport;
		CImageDivider			cImageDivider;
		CImageDividerNumbers	cNumbers;
		Ptr<CArrayImageCel>		paSuckerCels;
		CFileUtil				cFileUtil;
		CChars					szFilename;
		Ptr<CImage>				pBloodSucker;
		Ptr<CImageCel>			pCel;
		Ptr<CSprite>			pSprite1;

		ImageChannelDescriptorInit();

		szFilename.Init();
		cFileUtil.CurrentDirectory(&szFilename);
		cFileUtil.AppendToPath(&szFilename, "Input");
		cFileUtil.AppendToPath(&szFilename, "SpaceCrusade");
		cFileUtil.AppendToPath(&szFilename, "SoulSucker.png");
		AssertTrue(cFileUtil.Exists(szFilename.Text()));

		pBloodSucker = ReadImage(szFilename.Text(), IT_Unknown, true);
		szFilename.Kill();
		AssertTrue(pBloodSucker.IsNotNull());

		cNumbers.InitGeneral(-1, -1, 8, 1, 0, 0, 0, 0);
		cImageDivider.Init(&pBloodSucker, NULL);
		cImageDivider.GenerateFromNumbers(&cNumbers);
		paSuckerCels = cImageDivider.GetDestImageCels();
		AssertSize(8, paSuckerCels->NumElements());
		
		pCel = paSuckerCels->Get(0);
		pSprite1 = OMalloc<CSprite>(pCel, 0, 0);

		pContext = OMalloc<CMapsContext>();
		pMaps = OMalloc<CMaps>(pContext);
		pViewport = OMalloc<CMapViewport>(pMaps);



		ImageChannelDescriptorKill();
	}
	ObjectsKill();
	DataIOKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapViewport(void)
{
	BeginTests();

	TestMapViewportRender();

	TestStatistics();
}

