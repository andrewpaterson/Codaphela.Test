#include "BaseLib/GlobalDataTypesIO.h"
#include "SupportLib/ImageReader.h"
#include "SupportLib/ImageWriter.h"
#include "SupportLib/ImageDivider.h"
#include "SupportLib/Maps.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapsRender(void)
{
	DataIOInit();
	ObjectsInit();
	{
		CMaps					cMaps;
		CMapsContext			cContext;
		CImageDivider			cImageDivider;
		CImageDividerNumbers	cNumbers;
		Ptr<CArrayImageCel>		pacBackgroundCels;
		CFileUtil				cFileUtil;
		CChars					szFilename;

		ImageChannelDescriptorInit();

		szFilename.Init();
		cFileUtil.CurrentDirectory(&szFilename);
		cFileUtil.AppendToPath(&szFilename, "Input");
		cFileUtil.AppendToPath(&szFilename, "SpaceCrusade");
		cFileUtil.AppendToPath(&szFilename, "Tiles.png");
		AssertTrue(cFileUtil.Exists(szFilename.Text()));
		szFilename.Kill();

		Ptr<CImage> pBackground = ReadImage("Input" _FS_ "SpaceCrusade" _FS_ "Tiles.png", IT_Unknown, true);
		AssertTrue(pBackground.IsNotNull());

		cNumbers.InitGeneral(-1, -1, 10, 3, 0, 0, 0, 0);
		cImageDivider.Init(&pBackground, NULL);
		cImageDivider.GenerateFromNumbers(&cNumbers);
		pacBackgroundCels = cImageDivider.GetDestImageCels();
		AssertSize(30, pacBackgroundCels->NumElements());

		cContext.Init();
		cMaps.Init(&cContext);

		cMaps.Kill();
		cContext.Kill();

		ImageChannelDescriptorKill();
	}
	ObjectsKill();
	DataIOKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapsInit(void)
{
	DataIOInit();
	ObjectsInit();
	ImageChannelDescriptorInit();

	CMaps						cMaps;
	CMapsContext				cContext;
	CArrayMovableBlockType*		pacBlockTypes;
	CMovableBlockType*			pcType0;
	CMovableBlockType*			pcType1;
	CMovableBlock*				pcBlock0;
	CMovableBlock*				pcBlock1;
	CMovableBlock*				pcNullBlock0;
	CMovableBlock*				pcNullBlock1;

	cContext.Init();
	cMaps.Init(&cContext);

	pacBlockTypes = cContext.GetBlockTypes();
	AssertSize(2, pacBlockTypes->NumElements());
	pcType0 = pacBlockTypes->Get(0);
	pcType1 = pacBlockTypes->Get(1);

	AssertString("Image", pcType0->GetName());
	AssertSize(1, pcType0->NumBlocks());
	pcBlock0 = pcType0->GetBlock(0);
	AssertString("CMovableBlockImageCel", pcBlock0->ClassName());
	pcNullBlock0 = pcType0->GetNullBlock();
	AssertPointer(pcBlock0, pcNullBlock0);

	AssertString("Boolean", pcType1->GetName());
	AssertSize(1, pcType1->NumBlocks());
	pcBlock1 = pcType1->GetBlock(0);
	AssertString("CMovableBlockBoolean", pcBlock1->ClassName());
	pcNullBlock1 = pcType1->GetNullBlock();
	AssertPointer(pcBlock1, pcNullBlock1);

	cMaps.Kill();
	cContext.Kill();

	ImageChannelDescriptorKill();
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

	TestMapsInit();
	TestMapsRender();

	TestStatistics();
}

