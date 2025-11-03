#include "BaseLib/FastFunctions.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/NaiveFile.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "StandardLib/Objects.h"
#include "SupportLib/ImageReader.h"
#include "SupportLib/ImageWriter.h"
#include "SupportLib/ImageModifierStack.h"
#include "SupportLib/ImageModifierDrawBox.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageModifierDrawBox1(void)
{

	CImage					cImage;
	CImageModifierDrawBox	cBox;
	CRectangle				cRect;
	CImageColourRGB			cRGB;

	cImage.Init();
	cImage.BeginChange();
	cImage.AddChannel(IMAGE_NORMAL_X, PT_uint16);
	cImage.AddChannel(IMAGE_NORMAL_Y, PT_uint16);
	cImage.AddChannel(IMAGE_NORMAL_Z, PT_uint16);
	cImage.AddChannel(IMAGE_DIFFUSE_BLUE, PT_uint8);
	cImage.AddChannel(IMAGE_DIFFUSE_GREEN, PT_uint8);
	cImage.AddChannel(IMAGE_DIFFUSE_RED, PT_uint8);
	cImage.SetSize(4, 4);
	cImage.EndChange();
	cImage.Clear();

	cRect.Init(1, 1, 3, 3);  //End not inclusive.
	cRGB.Init(0.9f, 0.2f, 0.25f);
	cBox.Init(&cRect, &cRGB);
	cBox.Modify(&cImage);

	WriteImage(&cImage, "Output\\Box1.png");
	WriteImage(&cImage, "Output\\Box1.raw");
	AssertFileMemory("input\\Box1.raw", cImage.GetData(), cImage.GetByteSize());

	cImage.BeginChange();
	cImage.SetSize(8, 8);  //Oops, Set size does not preserve the image.  Also Write Image cannot write out non *4 sized pngs.
	cImage.EndChange();
	cImage.Clear();
	cBox.Modify(&cImage);
	cBox.Kill();

	cRect.Init(1, 1, 4, 4);  //End not inclusive.
	cRGB.Init(0.5f, 0.6f, 0.7f);
	cBox.Init(&cRect, &cRGB, false);
	cBox.Modify(&cImage);
	cBox.Kill();

	WriteImage(&cImage, "Output\\BoxBorder.png");
	WriteImage(&cImage, "Output\\BoxBorder.raw");
	AssertFileMemory("input\\BoxBorder.raw", cImage.GetData(), cImage.GetByteSize());

	cImage.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageModifierDrawBox2(void)
{
	CImageModifierDrawBox*	pcBackground;
	CImageModifierDrawBox*	pcBox1;
	CImageModifierDrawBox*	pcBox2;
	CImageModifierDrawBox*	pcBox3;
	CRectangle				cRect;
	CImageColourRGB			cRed;
	CImageColourRGB			cGreen;
	CImageColourRGB			cBlue;
	CImageColourRGB			cGrey;
	CImageModifierStack		cStack;
	Ptr<CImage>				pImage;

	pImage = ONMalloc<CImage>("Picture", 32, 32);
	pImage->Clear();

	cStack.Init(pImage);

	pcBackground = cStack.AddModifier<CImageModifierDrawBox>();
	cGrey.Init(0.3f, 0.3f, 0.3f);
	pcBackground->Init(NULL, &cGrey);

	pcBox1 = cStack.AddModifier<CImageModifierDrawBox>();
	cRect.Init(12, 0, 31, 22);
	cRed.Init(1.0f, 0.2f, 0.2f);
	pcBox1->Init(&cRect, &cRed);

	pcBox2 = cStack.AddModifier<CImageModifierDrawBox>();
	cRect.Init(3, 15, 19, 28);
	cGreen.Init(0.2f, 1.0f, 0.2f);
	pcBox2->Init(&cRect, &cGreen);

	pcBox3 = cStack.AddModifier<CImageModifierDrawBox>();
	cRect.Init(6, 6, 25, 12);
	cBlue.Init(0.2f, 0.2f, 1.0f);
	pcBox3->Init(&cRect, &cBlue);

	cStack.ApplyAll();
	cStack.Kill();

	WriteImage(pImage, "Output\\Box2.png");
	WriteImage(pImage, "Output\\Box2.raw");
	AssertFileMemory("input\\Box2.raw", pImage->GetData(), pImage->GetByteSize());

	pImage->Kill();

	cRect.Kill();
	cRed.Kill();
	cGreen.Kill();
	cBlue.Kill();
	cGrey.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageModifierDrawBox(void)
{
	BeginTests();

	DataIOInit();
	ObjectsInit();

	TestImageModifierDrawBox1();
	TestImageModifierDrawBox2();

	ObjectsKill();
	DataIOKill();

	TestStatistics();
}

