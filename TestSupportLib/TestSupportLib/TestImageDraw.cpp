#include "BaseLib/FastFunctions.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "StandardLib/Objects.h"
#include "SupportLib/ImageReader.h"
#include "SupportLib/ImageWriter.h"
#include "SupportLib/ImageDraw.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageDrawBox(void)
{
	CImageDraw			cDraw;
	Ptr<CImage>			pImage = OMalloc<CImage>(32, 32);
	CImageColourRGB		cColour;
	size				i;

	pImage->Clear();

	cDraw.Init(pImage);

	for (i = 0; i < 6; i++)
	{
		cColour.Init(1.0f, 0.7f + (i/20.0f)* 1.05263162f, 0.4f + (i/10.0f)* 1.11111116f);
		cDraw.SetColour(&cColour);
		cDraw.DrawBox(8+i, 10+i, 24-i, 22-i, false);
		cColour.Kill();
	}
	
	WriteImage(pImage, "Output\\DrawBox1.raw");
	WriteImage(pImage, "Output\\DrawBox1.png");
	AssertFileMemory("input\\DrawBox1.raw", pImage->GetData(), pImage->GetByteSize());

	pImage = NULL;
}



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageDrawLine(void)
{
	CImageDraw			cDraw;
	Ptr<CImage>			pImage = OMalloc<CImage>(64, 32);
	CImageColourRGB		cColour;

	pImage->Clear();

	cDraw.Init(pImage);
	cColour.Init(1.0f, 1, 1);
	cDraw.SetColour(&cColour);

	cDraw.DrawLine(0, 0, 64, 32);
	cDraw.DrawLine(0, 0, 64, 16);
	cDraw.DrawLine(0, 0, 32, 32);
	cDraw.DrawLine(0, 0, 64, 0);
	cDraw.DrawLine(0, 0, 0, 32);

	WriteImage(pImage, "Output\\DrawLine1.raw");
	WriteImage(pImage, "Output\\DrawLine1.png");
	AssertFileMemory("input\\DrawLine1.raw", pImage->GetData(), pImage->GetByteSize());

	pImage->Clear();

	cColour.Init(0.4f, 0.9f, 0.4f);
	cDraw.SetColour(&cColour);

	cDraw.DrawLine(64, 32, 0, 0);
	cDraw.DrawLine(64, 16, 0, 0);
	cDraw.DrawLine(32, 32, 0, 0);
	cDraw.DrawLine(64, 0 , 0, 0);
	cDraw.DrawLine(0, 32 , 0, 0);

	WriteImage(pImage, "Output\\DrawLine2.raw");
	WriteImage(pImage, "Output\\DrawLine2.png");
	AssertFileMemory("input\\DrawLine2.raw", pImage->GetData(), pImage->GetByteSize());

	pImage->Clear();

	cColour.Init(0.4f, 0.4f, 0.99f);
	cDraw.SetColour(&cColour);

	cDraw.DrawLine(64, 0, 0, 32);
	cDraw.DrawLine(64, 0, 0, 16);
	cDraw.DrawLine(32, 0, 0, 32);
	cDraw.DrawLine(64, 0, 0, 0);
	cDraw.DrawLine(0, 0, 0, 32);

	WriteImage(pImage, "Output\\DrawLine3.raw");
	WriteImage(pImage, "Output\\DrawLine3.png");
	AssertFileMemory("input\\DrawLine3.raw", pImage->GetData(), pImage->GetByteSize());

	pImage = NULL;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageDraw(void)
{
	BeginTests();

	DataIOInit();
	ObjectsInit();

	TestImageDrawBox();
	TestImageDrawLine();

	ObjectsKill();
	DataIOKill();

	TestStatistics();
}

