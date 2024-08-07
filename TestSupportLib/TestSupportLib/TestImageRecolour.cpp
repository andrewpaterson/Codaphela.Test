#include "BaseLib/FastFunctions.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/NaiveFile.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "StandardLib/Objects.h"
#include "SupportLib/ImageReader.h"
#include "SupportLib/ImageWriter.h"
#include "SupportLib/ImageRecolour.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageRecolour1(void)
{
	CImageRecolour		cRecolour;
	CRectangle			cRect;
	CImageColourRGB		o1, o2, o3, n1, n2, n3;

	Ptr<CImage> pcImage = ReadImage("Input\\recolour.png");
	cRect.Init(0, 4, 8, 8);
	o1.Init(1.0f, 0.0f, 0.0f); n1.Init(0.2f, 1.0f, 0.3f);
	o2.Init(0.0f, 0.0f, 0.0f); n2.Init(0.9f, 0.0f, 0.8f);
	o3.Init(1.0f, 1.0f, 1.0f); n3.Init(0.0f, 0.0f, 0.0f);

	cRecolour.Init(&o1, &n1, &cRect);
	cRecolour.AddRecolour(&o2, &n2);
	cRecolour.AddRecolour(&o3, &n3);
	cRecolour.Modify(pcImage);
	cRecolour.Kill();

	WriteImage(pcImage, "Output\\recolour.raw");
	AssertFileMemory("input\\recolour.raw", pcImage->GetData(), pcImage->GetByteSize());

	pcImage = NULL;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageRecolour(void)
{
	BeginTests();

	DataIOInit();
	ObjectsInit();

	TestImageRecolour1();

	ObjectsKill();
	DataIOKill();

	TestStatistics();
}


