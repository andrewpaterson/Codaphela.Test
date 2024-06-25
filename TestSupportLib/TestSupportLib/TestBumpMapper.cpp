#include "BaseLib/NaiveFile.h"
#include "BaseLib/FastFunctions.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "StandardLib/Objects.h"
#include "SupportLib/Image.h"
#include "SupportLib/ImageReader.h"
#include "SupportLib/ImageWriter.h"
#include "SupportLib/BumpMapper.h"
#include "TestLib/Assert.h"
#include "TestBumpMapper.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestBumpMapper1(void)
{
	CImage	cSource;
	CImage	cDest;

	ReadImage(&cSource, "Input\\HeightMap.png");

	cDest.Init();

	ConvertHeightMapTo(true, true, &cDest, &cSource, IMAGE_DIFFUSE_RED);

	cDest.BeginChange();
	cDest.RenameChannel(IMAGE_NORMAL_X, IMAGE_DIFFUSE_RED);
	cDest.RenameChannel(IMAGE_NORMAL_Y, IMAGE_DIFFUSE_GREEN);
	cDest.RenameChannel(IMAGE_NORMAL_Z, IMAGE_DIFFUSE_BLUE);
	cDest.EndChange();

	WriteImage(&cDest, "Output\\NormalMap.png", IT_PNG);

	cDest.BeginChange();
	cDest.RenameChannel(IMAGE_DIFFUSE_RED, IMAGE_NORMAL_X);
	cDest.RenameChannel(IMAGE_DIFFUSE_GREEN, IMAGE_NORMAL_Y);

	cDest.RenameChannel(IMAGE_BUMP_U, IMAGE_DIFFUSE_RED);
	cDest.RenameChannel(IMAGE_BUMP_V, IMAGE_DIFFUSE_GREEN);
	cDest.EndChange();

	WriteImage(&cDest, "Output\\BumpMap.png", IT_PNG);

	AssertFile("Input\\NormalMap.png", "Output\\NormalMap.png");
	AssertFile("Input\\BumpMap.png", "Output\\BumpMap.png");

	cDest.Kill();
	cSource.Kill();
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
