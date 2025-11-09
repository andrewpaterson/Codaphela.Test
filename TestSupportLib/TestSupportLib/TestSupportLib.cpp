// TestSupportLib.cpp : Defines the entry point for the console application.
//

#include "BaseLib/FastFunctions.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/TypeNames.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/GlobalMemory.h"
#include "StandardLib/Unknowns.h"
#include "TestLib/Assert.h"


void TestPlainTextEditor(void);
void TestBumpMapper(void);
void TestImage(void);
void TestImageCel(void);
void TestImageCelsSource(void);
void TestImageWriter(void);
void TestImageColour(void);
void TestImageCombiner(void);
void TestImageDivider(void);
void TestImageDraw(void);
void TestImageModifierDrawBox(void);
void TestImageGreyToRGB(void);
void TestImageModifierStack(void);
void TestImageReader(void);
void TestImageRecolour(void);
void TestImageRGBToGrey(void);
void TestImageSwizzle(void);
void TestRectangleBestPacker(void);
void TestRectanglePow2Packer(void);
void TestImageToR3G3B2A(void);
void TestImageSFTWriter(void);
void TestMaps(void);
void TestWinText(void);
void TestHalfSpace(void);
void TestMeshColours(void);
void TestMeshUVCoords(void);
void TestMeshMaterials(void);
void TestPolygon(void);
void TestSphereShape(void);
void TestTriangleShape(void);
void TestMeshFaceReturn(void);
void TestMeshPolygons(void);
void TestMeshShapes(void);
void TestMeshConnectivity(void);
void TestNormalGeneration(void);
void TestMeshOBJReader(void);


int __cdecl main(void)
{
	CFileUtil	cFileUtil;
	int			iResult;

	_CrtSetBreakAlloc(426);

	InitTotalStatistics();

	FastFunctionsInit();
	TypesInit();
	TypeConverterInit();
	MemoryInit();

	cFileUtil.RemoveDir("Output");
	cFileUtil.MakeDir("Output");
	
	//TestImage();
	//TestImageColour();
	//TestImageReader();
	//TestImageWriter();
	//TestImageGreyToRGB();
	//TestImageRGBToGrey();
	//TestImageDivider();
	//TestBumpMapper();
	//TestPlainTextEditor();
	//TestImageCel();
	//TestRectangleBestPacker();
	//TestRectanglePow2Packer();
	//TestImageModifierStack();
	//TestImageModifierDrawBox();
	//TestImageDraw();
	//TestImageRecolour();
	//TestImageSwizzle();
	//TestImageCombiner();
	//TestImageToR3G3B2A();
	//TestImageSFTWriter();
	TestMaps();
	//TestWinText();
	//TestImageCelsSource();
	//TestHalfSpace();
	//TestPolygon();
	//TestMeshColours();
	//TestMeshUVCoords();
	//TestMeshMaterials();
	//TestSphereShape();
	//TestTriangleShape();
	//TestMeshFaceReturn();
	//TestMeshPolygons();
	//TestMeshShapes();
	//TestMeshConnectivity();
	//TestNormalGeneration();
	//TestMeshOBJReader();

	cFileUtil.RemoveDir("Output");

	MemoryKill();
	TypeConverterKill();
	TypesKill();
	FastFunctionsKill();

	iResult = TestTotalStatistics();
	_CrtDumpMemoryLeaks();
	return iResult;

}

