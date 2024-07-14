#include "BaseLib/FastFunctions.h"
#include "BaseLib/NaiveFile.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/TypeNames.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "StandardLib/Objects.h"
#include "SupportLib/Image.h"
#include "SupportLib/ImageReader.h"
#include "SupportLib/ImageWriter.h"
#include "TestLib/Assert.h"
#include "AssertImage.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageReaderRAD(void)
{
	CImage			cImage;
	bool			bResult;
	CArrayChannel	pcChannels;

	bResult = ReadImage(&cImage, "Input\\readrad.rad");
	AssertBool(true, bResult);
	cImage.GetAllChannels(&pcChannels);
	AssertInt(3, pcChannels.NumElements());
	AssertChannel(IP_Diffuse, CT_Red, PT_uint8, pcChannels.Get(0));
	AssertChannel(IP_Diffuse, CT_Green, PT_uint8, pcChannels.Get(1));
	AssertChannel(IP_Diffuse, CT_Blue, PT_uint8, pcChannels.Get(2));

	WriteImage(&cImage, "Output\\readrad.raw");
	AssertFileMemory("input\\readrad.raw", cImage.GetData(), cImage.GetByteSize());
	cImage.Kill();


	//Read raw is a special case.  Because the size and the channels aren't known the image must be initialised before hand.
	cImage.Init(32, 48, PT_uint8, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, CHANNEL_ZERO);
	bResult = ReadImage(&cImage, "Input\\readrad.raw");
	AssertBool(true, bResult);
	cImage.GetAllChannels(&pcChannels);
	AssertInt(3, pcChannels.NumElements());
	AssertChannel(IP_Diffuse, CT_Red, PT_uint8, pcChannels.Get(0));
	AssertChannel(IP_Diffuse, CT_Green, PT_uint8, pcChannels.Get(1));
	AssertChannel(IP_Diffuse, CT_Blue, PT_uint8, pcChannels.Get(2));

	WriteImage(&cImage, "Output\\readraw.raw");
	AssertFileMemory("input\\readraw.raw", cImage.GetData(), cImage.GetByteSize());
	cImage.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageReaderPNG(void)
{
	CImage			cImage;
	CArrayChannel	pcChannels;	

	ReadImage(&cImage, "Input\\basn0g01.png");
	cImage.GetAllChannels(&pcChannels);
	AssertInt(1, pcChannels.NumElements());
	AssertChannel(IP_Diffuse, CT_Intensity, PT_uint8, pcChannels.Get(0));

	WriteImage(&cImage, "Output\\basn0g01.raw");
	AssertFileMemory("input\\basn0g01.raw", cImage.GetData(), cImage.GetByteSize());
	cImage.Kill();


	ReadImage(&cImage, "Input\\basn0g02.png");
	cImage.GetAllChannels(&pcChannels);
	AssertInt(1, pcChannels.NumElements());
	AssertChannel(IP_Diffuse, CT_Intensity, PT_uint8, pcChannels.Get(0));

	WriteImage(&cImage, "Output\\basn0g02.raw");
	AssertFileMemory("input\\basn0g02.raw", cImage.GetData(), cImage.GetByteSize());
	cImage.Kill();


	ReadImage(&cImage, "Input\\basn0g04.png");
	cImage.GetAllChannels(&pcChannels);
	AssertInt(1, pcChannels.NumElements());
	AssertChannel(IP_Diffuse, CT_Intensity, PT_uint8, pcChannels.Get(0));

	WriteImage(&cImage, "Output\\basn0g04.raw");
	AssertFileMemory("input\\basn0g04.raw", cImage.GetData(), cImage.GetByteSize());
	cImage.Kill();


	ReadImage(&cImage, "Input\\basn0g08.png");
	cImage.GetAllChannels(&pcChannels);
	AssertInt(1, pcChannels.NumElements());
	AssertChannel(IP_Diffuse, CT_Intensity, PT_uint8, pcChannels.Get(0));

	WriteImage(&cImage, "Output\\basn0g08.raw");
	AssertFileMemory("input\\basn0g08.raw", cImage.GetData(), cImage.GetByteSize());
	cImage.Kill();


	ReadImage(&cImage, "Input\\basn0g16.png");
	cImage.GetAllChannels(&pcChannels);
	AssertInt(1, pcChannels.NumElements());
	AssertChannel(IP_Diffuse, CT_Intensity, PT_uint16, pcChannels.Get(0));

	WriteImage(&cImage, "Output\\basn0g16.raw");
	AssertFileMemory("input\\basn0g16.raw", cImage.GetData(), cImage.GetByteSize());
	cImage.Kill();


	ReadImage(&cImage, "Input\\basn2c08.png");
	cImage.GetAllChannels(&pcChannels);
	AssertInt(3, pcChannels.NumElements());
	AssertChannel(IP_Diffuse, CT_Red, PT_uint8, pcChannels.Get(0));
	AssertChannel(IP_Diffuse, CT_Green, PT_uint8, pcChannels.Get(1));
	AssertChannel(IP_Diffuse, CT_Blue, PT_uint8, pcChannels.Get(2));

	WriteImage(&cImage, "Output\\basn2c08.raw");
	AssertFileMemory("input\\basn2c08.raw", cImage.GetData(), cImage.GetByteSize());
	cImage.Kill();


	ReadImage(&cImage, "Input\\basn2c16.png");
	cImage.GetAllChannels(&pcChannels);
	AssertInt(3, pcChannels.NumElements());
	AssertChannel(IP_Diffuse, CT_Red, PT_uint16, pcChannels.Get(0));
	AssertChannel(IP_Diffuse, CT_Green, PT_uint16, pcChannels.Get(1));
	AssertChannel(IP_Diffuse, CT_Blue, PT_uint16, pcChannels.Get(2));

	WriteImage(&cImage, "Output\\basn2c16.raw");
	AssertFileMemory("input\\basn2c16.raw", cImage.GetData(), cImage.GetByteSize());
	cImage.Kill();


	ReadImage(&cImage, "Input\\basn4a08.png");
	AssertInt(32, cImage.GetWidth());
	AssertInt(32, cImage.GetHeight());
	AssertInt(2048, cImage.GetByteSize());
	cImage.GetAllChannels(&pcChannels);
	AssertInt(2, pcChannels.NumElements());
	AssertChannel(IP_Opacity, CT_Intensity, PT_uint8, pcChannels.Get(0));
	AssertChannel(IP_Diffuse, CT_Intensity, PT_uint8, pcChannels.Get(1));

	WriteImage(&cImage, "Output\\basn4a08.raw");
	AssertFileMemory("input\\basn4a08.raw", cImage.GetData(), cImage.GetByteSize());
	cImage.Kill();


	ReadImage(&cImage, "Input\\basn4a16.png");
	cImage.GetAllChannels(&pcChannels);
	AssertInt(2, pcChannels.NumElements());
	AssertChannel(IP_Opacity, CT_Intensity, PT_uint16, pcChannels.Get(0));
	AssertChannel(IP_Diffuse, CT_Intensity, PT_uint16, pcChannels.Get(1));

	WriteImage(&cImage, "Output\\basn4a16.raw");
	AssertFileMemory("input\\basn4a16.raw", cImage.GetData(), cImage.GetByteSize());
	cImage.Kill();


	ReadImage(&cImage, "Input\\basn6a08.png");
	cImage.GetAllChannels(&pcChannels);
	AssertInt(4, pcChannels.NumElements());
	AssertChannel(IP_Opacity, CT_Intensity, PT_uint8, pcChannels.Get(0));
	AssertChannel(IP_Diffuse, CT_Red, PT_uint8, pcChannels.Get(1));
	AssertChannel(IP_Diffuse, CT_Green, PT_uint8, pcChannels.Get(2));
	AssertChannel(IP_Diffuse, CT_Blue, PT_uint8, pcChannels.Get(3));

	WriteImage(&cImage, "Output\\basn6a08.raw");
	AssertFileMemory("input\\basn6a08.raw", cImage.GetData(), cImage.GetByteSize());
	cImage.Kill();


	ReadImage(&cImage, "Input\\basn6a16.png");
	cImage.GetAllChannels(&pcChannels);
	AssertInt(4, pcChannels.NumElements());
	AssertChannel(IP_Opacity, CT_Intensity, PT_uint16, pcChannels.Get(0));
	AssertChannel(IP_Diffuse, CT_Red, PT_uint16, pcChannels.Get(1));
	AssertChannel(IP_Diffuse, CT_Green, PT_uint16, pcChannels.Get(2));
	AssertChannel(IP_Diffuse, CT_Blue, PT_uint16, pcChannels.Get(3));

	WriteImage(&cImage, "Output\\basn6a16.raw");
	AssertFileMemory("input\\basn6a16.raw", cImage.GetData(), cImage.GetByteSize());
	cImage.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageReaderTGA(void)
{
	CImage			cImage;
	CArrayChannel	pcChannels;	

	ReadImage(&cImage, "Input\\tar32un.tga");
	cImage.GetAllChannels(&pcChannels);
	AssertInt(4, pcChannels.NumElements());
	AssertChannel(IP_Opacity, CT_Intensity, PT_uint8, pcChannels.Get(0));
	AssertChannel(IP_Diffuse, CT_Red, PT_uint8, pcChannels.Get(1));
	AssertChannel(IP_Diffuse, CT_Green, PT_uint8, pcChannels.Get(2));
	AssertChannel(IP_Diffuse, CT_Blue, PT_uint8, pcChannels.Get(3));

	WriteImage(&cImage, "Output\\tar32un.raw");
	AssertFileMemory("input\\tar32un.raw", cImage.GetData(), cImage.GetByteSize());
	cImage.Kill();


	ReadImage(&cImage, "Input\\tar24un.tga");
	cImage.GetAllChannels(&pcChannels);
	AssertInt(3, pcChannels.NumElements());
	AssertChannel(IP_Diffuse, CT_Red, PT_uint8, pcChannels.Get(0));
	AssertChannel(IP_Diffuse, CT_Green, PT_uint8, pcChannels.Get(1));
	AssertChannel(IP_Diffuse, CT_Blue, PT_uint8, pcChannels.Get(2));


	WriteImage(&cImage, "Output\\tar24un.raw");
	AssertFileMemory("input\\tar24un.raw", cImage.GetData(), cImage.GetByteSize());
	cImage.Kill();


	ReadImage(&cImage, "Input\\tar16un.tga");
	cImage.GetAllChannels(&pcChannels);
	AssertInt(3, pcChannels.NumElements());
	AssertChannel(IP_Diffuse, CT_Red, PT_uint8, pcChannels.Get(0));
	AssertChannel(IP_Diffuse, CT_Green, PT_uint8, pcChannels.Get(1));
	AssertChannel(IP_Diffuse, CT_Blue, PT_uint8, pcChannels.Get(2));

	WriteImage(&cImage, "Output\\tar16un.raw");
	AssertFileMemory("input\\tar16un.raw", cImage.GetData(), cImage.GetByteSize());
	cImage.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageReader(void)
{
	BeginTests();

	DataIOInit();
	ObjectsInit();

	TestImageReaderRAD();
	TestImageReaderPNG();
	TestImageReaderTGA();

	ObjectsKill();
	DataIOKill();

	TestStatistics();
}


