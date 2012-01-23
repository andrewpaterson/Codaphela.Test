#include "stdafx.h"
#include "BaseLib/NaiveFile.h"
#include "BaseLib/FastFunctions.h"
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
void TestBumpMapper(void)
{
	BeginTests();

	CImage			cSource;
	CImage			cDest;

	ReadImage(&cSource, "Input\\Heightmap.png");

	cDest.Init();

	ConvertHeightMapTo(TRUE, TRUE, &cDest, &cSource, IMAGE_DIFFUSE_RED);

	cDest.BeginChange();
	cDest.RenameChannel(IMAGE_NORMAL_X, IMAGE_DIFFUSE_RED);
	cDest.RenameChannel(IMAGE_NORMAL_Y, IMAGE_DIFFUSE_GREEN);
	cDest.RenameChannel(IMAGE_NORMAL_Z, IMAGE_DIFFUSE_BLUE);
	cDest.EndChange();

	WriteImage(&cDest, "Output\\Normals.png", IT_PNG);

	cDest.BeginChange();
	cDest.RenameChannel(IMAGE_DIFFUSE_RED, IMAGE_NORMAL_X);
	cDest.RenameChannel(IMAGE_DIFFUSE_GREEN, IMAGE_NORMAL_Y);

	cDest.RenameChannel(IMAGE_BUMP_U, IMAGE_DIFFUSE_RED);
	cDest.RenameChannel(IMAGE_BUMP_V, IMAGE_DIFFUSE_GREEN);
	cDest.EndChange();

	WriteImage(&cDest, "Output\\Bump.png", IT_PNG);

	AssertFile("Input\\NormalMap.png", "Output\\Normals.png");

	cSource.Kill();

	TestStatistics();
}
