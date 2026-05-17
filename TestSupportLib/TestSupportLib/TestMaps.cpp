#include "BaseLib/GlobalDataTypesIO.h"
#include "StandardLib/Pointer.h"
#include "SupportLib/ImageReader.h"
#include "SupportLib/ImageWriter.h"
#include "SupportLib/ImageDivider.h"
#include "SupportLib/Maps.h"
#include "TestLib/Assert.h"
#include "SupportAssert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapsGenerate(void)
{
	DataIOInit();
	ObjectsInit();
	{
		CMaps					cMaps;
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

		cMaps.Init();
		//Do something here.
		cMaps.Kill();

		ImageChannelDescriptorKill();
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

