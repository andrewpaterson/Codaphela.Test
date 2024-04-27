#include "stdafx.h"
#include "TestImageImport.h"
#include "SupportLib/Image.h"
#include "BaseLib/FastFunctions.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageImport(void)
{
//	CImage					cImage;
//	CImageImport			cImport;
//	SFastChannelAccessor*	psRedAccessor;
//	SFastChannelAccessor*	psGreenAccessor;
//	SFastChannelAccessor*	psBlueAccessor;
//	CChannels*				pcChannels;
//	int						i;
//	char					c;
//	uint8			acInput[] = {0xFF,0x00,0x00, 0x00,0xFF,0x00, 0x00,0x00,0xFF, 
//										 0xFF,0xFF,0xFF, 0x81,0x81,0x81, 0x00,0x00,0x00};
//
//	cImport.Init(&cImage);
//	cImport.SetFromText("\
//{\
//	iWidth 3;\
//	iHeight 2;\
//	sChannels\
//	{\
//		UChar Red;\
//		UChar Green;\
//		UChar Blue;\
//	}\
//}", NULL);
//	cImport.EndChange();
//	cImport.Import(acInput);
//	cImport.Kill();
//
//	pcChannels = cImage.macChannelDatas.Get(0);
//	AssertInt(pcChannels->mabData.miUsedElements, 3*3*2);  //Stride * width * Height.
//	for (i = 0; i < 3*3*2; i++)
//	{
//		c = pcChannels->mabData.GetValue(i);
//		AssertChar((char)acInput[i], c);
//	}
//
//	cImage.macChannelDatas.Get(0);
//
//	psRedAccessor   = cImage.CreateAccessor(IMAGE_DIFFUSE_RED);
//	psGreenAccessor = cImage.CreateAccessor(IMAGE_DIFFUSE_GREEN);
//	psBlueAccessor  = cImage.CreateAccessor(IMAGE_DIFFUSE_BLUE);
//
//	cImage.Kill();
//
}


