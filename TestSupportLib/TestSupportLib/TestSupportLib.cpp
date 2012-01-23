// TestSupportLib.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "BaseLib/FastFunctions.h"
#include "BaseLib/FileUtil.h"
#include "CoreLib/TypeConverter.h"
#include "StandardLib/ClassStorage.h"
#include "StandardLib/Unknowns.h"
#include "TestLib/Assert.h"
#include "TestImage.h"
#include "TestImageImport.h"
#include "TestImageWriter.h"
#include "TestImageReader.h"
#include "TestImageDivider.h"
#include "TestBumpMapper.h"
#include "TestPlainTextEditor.h"
#include "TestImageColour.h"
#include "TestImageCel.h"
#include "TestRectangleBestPacker.h"
#include "TestRectanglePow2Packer.h"
#include "TestImageGreyToRGB.h"
#include "TestImageRGBToGrey.h"
#include "TestImageModifierStack.h"
#include "TestImageDrawBox.h"
#include "TestImageRecolour.h"
#include "TestImageSwizzle.h"
#include "TestImageCombiner.h"
#include "TestImageCelsSource.h"
#include "TestWinText.h"
#include "TestHalfSpace.h"
#include "TestPolygon.h"
#include "TestSphereShape.h"
#include "TestTriangleShape.h"
#include "TestMeshFaceReturn.h"
#include "TestMeshPolygons.h"
#include "TestMeshShapes.h"
#include "TestMeshConnectivity.h"
#include "TestNormalGeneration.h"
#include "TestMeshOBJReader.h"

int main(int argc, _TCHAR* argv[])
{
	CFileUtil		cFileUtil;

	InitTotalStatistics();

	FastFunctionsInit();
	ClassStorageInit();
	TypeConverterInit();
	UnknownsInit();

	cFileUtil.MakeDir("Output");

	TestImage();
	TestImageColour();
	TestImageImport();
	TestImageReader();
	TestImageWriter();
	TestImageGreyToRGB();
	TestImageRGBToGrey();
	TestImageDivider();
	TestBumpMapper();
	TestPlainTextEditor();
	TestImageCel();
	TestRectangleBestPacker();
	TestRectanglePow2Packer();
	TestImageModifierStack();
	TestImageDrawBox();
	TestImageRecolour();
	TestImageSwizzle();
	TestImageCombiner();
	TestWinText();
	TestImageCelsSource();
	TestHalfSpace();
	TestPolygon();
	TestSphereShape();
	TestTriangleShape();
	TestMeshFaceReturn();
	TestMeshPolygons();
	TestMeshShapes();
	TestMeshConnectivity();
	TestNormalGeneration();
	TestMeshOBJReader();

	cFileUtil.RemoveDir("Output");

	UnknownsKill();
	TypeConverterKill();
	ClassStorageKill();
	FastFunctionsKill();
	return TestTotalStatistics();
}

