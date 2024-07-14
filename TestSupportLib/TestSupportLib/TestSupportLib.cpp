// TestSupportLib.cpp : Defines the entry point for the console application.
//

#include "BaseLib/FastFunctions.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/TypeNames.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/GlobalMemory.h"
#include "StandardLib/Unknowns.h"
#include "TestLib/Assert.h"
#include "TestImageWriter.h"
#include "TestPlainTextEditor.h"
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


void TestBumpMapper(void);
void TestImage(void);
void TestImageCel(void);
void TestImageCelsSource(void);
void TestImageColour(void);
void TestImageCombiner(void);
void TestImageDivider(void);
void TestImageDrawBox(void);
void TestImageGreyToRGB(void);
void TestImageImport(void);
void TestImageModifierStack(void);
void TestImageMultiAccessor(void);
void TestImageReader(void);
void TestImageRecolour(void);
void TestImageRGBToGrey(void);
void TestImageSwizzle(void);
void TestRectangleBestPacker(void);
void TestRectanglePow2Packer(void);
void TestImageToR3G3B2A1(void);


int __cdecl main(void)
{
	CFileUtil		cFileUtil;

	InitTotalStatistics();

	FastFunctionsInit();
	TypesInit();
	TypeConverterInit();
	MemoryInit();
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
	TestImageToR3G3B2A1();
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
	MemoryKill();
	TypeConverterKill();
	TypesKill();
	FastFunctionsKill();
	return TestTotalStatistics();
}

