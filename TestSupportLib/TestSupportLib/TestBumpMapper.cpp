#include "BaseLib/NaiveFile.h"
#include "BaseLib/FastFunctions.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "StandardLib/Objects.h"
#include "SupportLib/Image.h"
#include "SupportLib/ImageReader.h"
#include "SupportLib/ImageWriter.h"
#include "SupportLib/BumpMapper.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestBumpMapper1(void)
{
	Ptr<CImage> pcSource = ReadImage("Input\\HeightMap.png");
	Ptr<CImage>	pcDest = OMalloc<CImage>();

	pcDest = ConvertHeightMapTo(true, true, pcSource, IMAGE_DIFFUSE_RED);

	pcDest->BeginChange();
	pcDest->RenameChannel(IMAGE_NORMAL_X, IMAGE_DIFFUSE_RED);
	pcDest->RenameChannel(IMAGE_NORMAL_Y, IMAGE_DIFFUSE_GREEN);
	pcDest->RenameChannel(IMAGE_NORMAL_Z, IMAGE_DIFFUSE_BLUE);
	pcDest->EndChange();

	WriteImage(pcDest, "Output\\NormalMap.png", IT_PNG);

	pcDest->BeginChange();
	pcDest->RenameChannel(IMAGE_DIFFUSE_RED, IMAGE_NORMAL_X);
	pcDest->RenameChannel(IMAGE_DIFFUSE_GREEN, IMAGE_NORMAL_Y);

	pcDest->RenameChannel(IMAGE_BUMP_U, IMAGE_DIFFUSE_RED);
	pcDest->RenameChannel(IMAGE_BUMP_V, IMAGE_DIFFUSE_GREEN);
	pcDest->EndChange();

	WriteImage(pcDest, "Output\\BumpMap.png", IT_PNG);

	AssertFile("Input\\NormalMap.png", "Output\\NormalMap.png");
	AssertFile("Input\\BumpMap.png", "Output\\BumpMap.png");

	//These are probably unnecessay.
	pcDest->Kill();
	pcSource->Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestBumpMapper(void)
{
	BeginTests();

	DataIOInit();
	ObjectsInit();

	TestBumpMapper1();

	ObjectsKill();
	DataIOKill();

	TestStatistics();
}
