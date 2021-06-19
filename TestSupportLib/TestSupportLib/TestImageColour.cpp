#include "stdafx.h"
#include "BaseLib/FastFunctions.h"
#include "BaseLib/GeometricTypes.h"
#include "BaseLib/TypeConverter.h"
#include "SupportLib/ImageColour.h"
#include "SupportLib/ImageAccessor.h"
#include "SupportLib/ImageAccessorCreator.h"
#include "SupportLib/Image.h"
#include "TestLib/Assert.h"
#include "TestImageColour.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageColourAccessorBytes(void)
{
	CImageColourRGB		cRGB; 
	CImageColourOpacity	cAlpha;
	CImageColourCombo2	cColour;
	CChannels*			pcChannels;
	CImageAccessor*		pcAccessor;
	CImage				cImage;
	SImageColour		sDest;
	BOOL				bResult;
	char*				pvData;

	cRGB.Init(1.0f, 0.5f, 0.25f);
	cAlpha.Init(0.333f);
	cColour.Init(&cRGB, &cAlpha);

	cImage.Init(10, 10, PT_uint8,	IMAGE_DIFFUSE_GREEN,	//0x7f
									IMAGE_NORMAL_Y,		
									IMAGE_DIFFUSE_BLUE,	//0x3f
									IMAGE_OPACITY,		//0x54
									IMAGE_DIFFUSE_RED,	//0xff
									IMAGE_MASK, 
									CHANNEL_ZERO);
	cImage.Clear();

	pcAccessor = CImageAccessorCreator::Create(&cImage, PT_uint8, IMAGE_OPACITY, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, CHANNEL_ZERO);

	sDest.Full();
	bResult = pcAccessor->MakeColour(&sDest, &cColour);
	AssertBool(TRUE, bResult);

	//Remember ints have reverse endiannes which is why the test number below looks backwarsd.
	AssertIntHex(0x3f7fff54, *(int*)((void*)sDest.c));

	pcAccessor->Set(1, 0, &sDest);
	pcAccessor->Kill();

	pcChannels = &cImage.mcChannels;

	pvData = pcChannels->GetData();

	//First pixel.  Didn't touch it.
	AssertChar(0x00, pvData[0x0]);
	AssertChar(0x00, pvData[0x1]);
	AssertChar(0x00, pvData[0x2]);
	AssertChar(0x00, pvData[0x3]);
	AssertChar(0x00, pvData[0x4]);
	AssertChar(0x00, pvData[0x5]);

	//Second pixel.
	AssertChar(0x7f, pvData[0x6]);
	AssertChar(0x00, pvData[0x7]);
	AssertChar(0x3f, pvData[0x8]);
	AssertChar(0x54, pvData[0x9]);
	AssertChar((char)0xff, pvData[0xa]);
	AssertChar(0x00, pvData[0xb]);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageColourAccessorFloats(void)
{
	CImageColourNormal	cNormal;
	CChannels*			pcChannels;
	CImageAccessor*		pcAccessor;
	CImage				cImage;
	SImageColour		sDest;
	BOOL				bResult;

	cNormal.Init(0.7f, 0.6f, 0.5f);
	cImage.Init();
	cImage.BeginChange();
	cImage.AddChannel(IMAGE_DIFFUSE_GREEN, PT_uint8);
	cImage.AddChannel(IMAGE_NORMAL_Y, PT_float32);
	cImage.AddChannel(IMAGE_DIFFUSE_BLUE, PT_uint8);
	cImage.AddChannel(IMAGE_OPACITY, PT_int16);
	cImage.AddChannel(IMAGE_DIFFUSE_RED, PT_uint8);
	cImage.AddChannel(IMAGE_MASK, PT_int32);
	cImage.AddChannel(IMAGE_NORMAL_Z, PT_float32);
	cImage.AddChannel(IMAGE_NORMAL_X, PT_float32);
	cImage.SetSize(1, 2);
	cImage.EndChange();
	cImage.Clear();

	pcAccessor = CImageAccessorCreator::Create(&cImage, PT_float32, IMAGE_NORMAL_X, IMAGE_NORMAL_Y, IMAGE_NORMAL_Z, CHANNEL_ZERO);

	sDest.Full();
	bResult = pcAccessor->MakeColour(&sDest, &cNormal);
	AssertBool(TRUE, bResult);

	AssertFloat(0.7f, *((float*)&((sDest).c)[0x0]), 3);
	AssertFloat(0.6f, *((float*)&((sDest).c)[0x4]), 3);
	AssertFloat(0.5f, *((float*)&((sDest).c)[0x8]), 3);

	pcAccessor->Set(0, 1, &sDest);
	pcAccessor->Kill();

	pcChannels = &cImage.mcChannels;
	
	AssertFloat(0.6f, *(float*)&(pcChannels->GetData()[22]), 3);
	AssertFloat(0.7f, *(float*)&(pcChannels->GetData()[38]), 3);
	AssertFloat(0.5f, *(float*)&(pcChannels->GetData()[34]), 3);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageColourMultiAccessor(void)
{
	CImageColourNormal		cNormal;
	CImageColourOpacity		cAlpha;
	CImageColourCombo2		cColour;
	CChannels*				pcChannels;
	CImageAccessor*			pcAccessor;
	CImage					cImage;
	SImageColour			sDest;
	BOOL					bResult;

	cNormal.Init(0.7f, -0.6f, -0.5f);
	cAlpha.Init(0.333f);
	cColour.Init(&cNormal, &cAlpha);

	cImage.Init();
	cImage.BeginChange();
	cImage.AddChannel(IMAGE_DIFFUSE_GREEN, PT_uint8);
	cImage.AddChannel(IMAGE_NORMAL_Y, PT_float32);
	cImage.AddChannel(IMAGE_DIFFUSE_BLUE, PT_uint8);
	cImage.AddChannel(IMAGE_OPACITY, PT_uint16);
	cImage.AddChannel(IMAGE_DIFFUSE_RED, PT_uint8);
	cImage.AddChannel(IMAGE_MASK, PT_int32);
	cImage.AddChannel(IMAGE_NORMAL_Z, PT_float32);
	cImage.AddChannel(IMAGE_NORMAL_X, PT_float32);
	cImage.SetSize(1, 2);
	cImage.EndChange();
	cImage.Clear();

	pcAccessor = CImageAccessorCreator::Create(&cImage, IMAGE_NORMAL_X, IMAGE_NORMAL_Y, IMAGE_NORMAL_Z, IMAGE_OPACITY, CHANNEL_ZERO);

	sDest.Full();
	bResult = pcAccessor->MakeColour(&sDest, &cColour);
	AssertBool(TRUE, bResult);

	AssertFloat(0.7f, *((float*)&((sDest).c)[0x0]), 3);
	AssertFloat(-0.6f, *((float*)&((sDest).c)[0x4]), 3);
	AssertFloat(-0.5f, *((float*)&((sDest).c)[0x8]), 3);
	AssertShortHex(0x553f, *((unsigned short*)&((sDest).c)[0xc]));

	pcAccessor->Set(0, 1, &sDest);
	pcAccessor->Kill();

	pcChannels = &cImage.mcChannels;
	AssertFloat(-0.6f, *(float*)&(pcChannels->GetData()[22]), 3);
	AssertFloat( 0.7f, *(float*)&(pcChannels->GetData()[38]), 3);
	AssertFloat(-0.5f, *(float*)&(pcChannels->GetData()[34]), 3);
	AssertShortHex(0x553f, *(unsigned short*)&(pcChannels->GetData()[27]));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageColourStruct(void)
{
	SImageColour	sColour;
	int				i;

	sColour.Full();

	sColour.c[0] = 0;
	AssertBool(TRUE, sColour.IsZero(1));

	sColour.c[0] = 3;
	AssertBool(FALSE, sColour.IsZero(1));

	sColour.c[0] = 0xff;

	for (i = 0; i < MAX_IMAGE_COLOUR_BYTES; i++)
	{
		sColour.c[i] = 0;
		AssertBool(TRUE, sColour.IsZero(i+1));
	}

	for (i = MAX_IMAGE_COLOUR_BYTES-1; i >= 0; i--)
	{
		sColour.c[i] = 0xff;
		AssertBool(FALSE, sColour.IsZero(i+1));
	}

	sColour.Zero();
	AssertBool(TRUE, sColour.IsZero(8));

}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageColour(void)
{
	BeginTests();

	TestImageColourStruct();
	TestImageColourAccessorBytes();
	TestImageColourAccessorFloats();
	TestImageColourMultiAccessor();

	TestStatistics();
}

