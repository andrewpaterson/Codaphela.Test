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
	CArrayChannel	pcChannels;

	Ptr<CImage> pcImage = ReadImage("Input\\readrad.rad");
	AssertTrue(pcImage.IsNotNull());
	pcImage->GetAllChannels(&pcChannels);
	AssertInt(3, pcChannels.NumElements());
	AssertChannel(IP_Diffuse, CT_Red, PT_uint8, pcChannels.Get(0));
	AssertChannel(IP_Diffuse, CT_Green, PT_uint8, pcChannels.Get(1));
	AssertChannel(IP_Diffuse, CT_Blue, PT_uint8, pcChannels.Get(2));

	WriteImage(pcImage, "Output\\readrad.raw");
	AssertFileMemory("input\\readrad.raw", pcImage->GetData(), pcImage->GetByteSize());
	pcImage = NULL;


	//Read raw is a special case.  Because the size and the channels aren't known the image must be initialised before hand.
	pcImage = OMalloc<CImage>(32, 48, PT_uint8, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, CHANNEL_ZERO);
	ReadRawImage(pcImage, "Input\\readrad.raw");
	AssertTrue(pcImage.IsNotNull());
	pcImage->GetAllChannels(&pcChannels);
	AssertInt(3, pcChannels.NumElements());
	AssertChannel(IP_Diffuse, CT_Red, PT_uint8, pcChannels.Get(0));
	AssertChannel(IP_Diffuse, CT_Green, PT_uint8, pcChannels.Get(1));
	AssertChannel(IP_Diffuse, CT_Blue, PT_uint8, pcChannels.Get(2));

	WriteImage(pcImage, "Output\\readraw.raw");
	AssertFileMemory("input\\readraw.raw", pcImage->GetData(), pcImage->GetByteSize());
	pcImage = NULL;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageReaderPNG(void)
{
	CArrayChannel	pcChannels;	

	Ptr<CImage> pcImage = ReadImage("Input\\basn0g01.png");
	pcImage->GetAllChannels(&pcChannels);
	AssertInt(1, pcChannels.NumElements());
	AssertChannel(IP_Diffuse, CT_Intensity, PT_uint8, pcChannels.Get(0));

	WriteImage(pcImage, "Output\\basn0g01.raw");
	AssertFileMemory("input\\basn0g01.raw", pcImage->GetData(), pcImage->GetByteSize());
	pcImage = NULL;


	pcImage = ReadImage("Input\\basn0g02.png");
	pcImage->GetAllChannels(&pcChannels);
	AssertInt(1, pcChannels.NumElements());
	AssertChannel(IP_Diffuse, CT_Intensity, PT_uint8, pcChannels.Get(0));

	WriteImage(pcImage, "Output\\basn0g02.raw");
	AssertFileMemory("input\\basn0g02.raw", pcImage->GetData(), pcImage->GetByteSize());
	pcImage = NULL;


	pcImage = ReadImage("Input\\basn0g04.png");
	pcImage->GetAllChannels(&pcChannels);
	AssertInt(1, pcChannels.NumElements());
	AssertChannel(IP_Diffuse, CT_Intensity, PT_uint8, pcChannels.Get(0));

	WriteImage(pcImage, "Output\\basn0g04.raw");
	AssertFileMemory("input\\basn0g04.raw", pcImage->GetData(), pcImage->GetByteSize());
	pcImage = NULL;


	pcImage = ReadImage("Input\\basn0g08.png");
	pcImage->GetAllChannels(&pcChannels);
	AssertInt(1, pcChannels.NumElements());
	AssertChannel(IP_Diffuse, CT_Intensity, PT_uint8, pcChannels.Get(0));

	WriteImage(pcImage, "Output\\basn0g08.raw");
	AssertFileMemory("input\\basn0g08.raw", pcImage->GetData(), pcImage->GetByteSize());
	pcImage = NULL;


	pcImage = ReadImage("Input\\basn0g16.png");
	pcImage->GetAllChannels(&pcChannels);
	AssertInt(1, pcChannels.NumElements());
	AssertChannel(IP_Diffuse, CT_Intensity, PT_uint16, pcChannels.Get(0));

	WriteImage(pcImage, "Output\\basn0g16.raw");
	AssertFileMemory("input\\basn0g16.raw", pcImage->GetData(), pcImage->GetByteSize());
	pcImage = NULL;


	pcImage = ReadImage("Input\\basn2c08.png");
	pcImage->GetAllChannels(&pcChannels);
	AssertInt(3, pcChannels.NumElements());
	AssertChannel(IP_Diffuse, CT_Red, PT_uint8, pcChannels.Get(0));
	AssertChannel(IP_Diffuse, CT_Green, PT_uint8, pcChannels.Get(1));
	AssertChannel(IP_Diffuse, CT_Blue, PT_uint8, pcChannels.Get(2));

	WriteImage(pcImage, "Output\\basn2c08.raw");
	AssertFileMemory("input\\basn2c08.raw", pcImage->GetData(), pcImage->GetByteSize());
	pcImage = NULL;


	pcImage = ReadImage("Input\\basn2c16.png");
	pcImage->GetAllChannels(&pcChannels);
	AssertInt(3, pcChannels.NumElements());
	AssertChannel(IP_Diffuse, CT_Red, PT_uint16, pcChannels.Get(0));
	AssertChannel(IP_Diffuse, CT_Green, PT_uint16, pcChannels.Get(1));
	AssertChannel(IP_Diffuse, CT_Blue, PT_uint16, pcChannels.Get(2));

	WriteImage(pcImage, "Output\\basn2c16.raw");
	AssertFileMemory("input\\basn2c16.raw", pcImage->GetData(), pcImage->GetByteSize());
	pcImage = NULL;


	pcImage = ReadImage("Input\\basn4a08.png");
	AssertInt(32, pcImage->GetWidth());
	AssertInt(32, pcImage->GetHeight());
	AssertInt(2048, pcImage->GetByteSize());
	pcImage->GetAllChannels(&pcChannels);
	AssertInt(2, pcChannels.NumElements());
	AssertChannel(IP_Opacity, CT_Intensity, PT_uint8, pcChannels.Get(0));
	AssertChannel(IP_Diffuse, CT_Intensity, PT_uint8, pcChannels.Get(1));

	WriteImage(pcImage, "Output\\basn4a08.raw");
	AssertFileMemory("input\\basn4a08.raw", pcImage->GetData(), pcImage->GetByteSize());
	pcImage = NULL;


	pcImage = ReadImage("Input\\basn4a16.png");
	pcImage->GetAllChannels(&pcChannels);
	AssertInt(2, pcChannels.NumElements());
	AssertChannel(IP_Opacity, CT_Intensity, PT_uint16, pcChannels.Get(0));
	AssertChannel(IP_Diffuse, CT_Intensity, PT_uint16, pcChannels.Get(1));

	WriteImage(pcImage, "Output\\basn4a16.raw");
	AssertFileMemory("input\\basn4a16.raw", pcImage->GetData(), pcImage->GetByteSize());
	pcImage = NULL;


	pcImage = ReadImage("Input\\basn6a08.png");
	pcImage->GetAllChannels(&pcChannels);
	AssertInt(4, pcChannels.NumElements());
	AssertChannel(IP_Opacity, CT_Intensity, PT_uint8, pcChannels.Get(0));
	AssertChannel(IP_Diffuse, CT_Red, PT_uint8, pcChannels.Get(1));
	AssertChannel(IP_Diffuse, CT_Green, PT_uint8, pcChannels.Get(2));
	AssertChannel(IP_Diffuse, CT_Blue, PT_uint8, pcChannels.Get(3));

	WriteImage(pcImage, "Output\\basn6a08.raw");
	AssertFileMemory("input\\basn6a08.raw", pcImage->GetData(), pcImage->GetByteSize());
	pcImage = NULL;


	pcImage = ReadImage("Input\\basn6a16.png");
	pcImage->GetAllChannels(&pcChannels);
	AssertInt(4, pcChannels.NumElements());
	AssertChannel(IP_Opacity, CT_Intensity, PT_uint16, pcChannels.Get(0));
	AssertChannel(IP_Diffuse, CT_Red, PT_uint16, pcChannels.Get(1));
	AssertChannel(IP_Diffuse, CT_Green, PT_uint16, pcChannels.Get(2));
	AssertChannel(IP_Diffuse, CT_Blue, PT_uint16, pcChannels.Get(3));

	WriteImage(pcImage, "Output\\basn6a16.raw");
	AssertFileMemory("input\\basn6a16.raw", pcImage->GetData(), pcImage->GetByteSize());
	pcImage = NULL;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageReaderTGA(void)
{
	CArrayChannel	pcChannels;	

	Ptr<CImage> pcImage = ReadImage("Input\\tar32un.tga");
	pcImage->GetAllChannels(&pcChannels);
	AssertInt(4, pcChannels.NumElements());
	AssertChannel(IP_Opacity, CT_Intensity, PT_uint8, pcChannels.Get(0));
	AssertChannel(IP_Diffuse, CT_Red, PT_uint8, pcChannels.Get(1));
	AssertChannel(IP_Diffuse, CT_Green, PT_uint8, pcChannels.Get(2));
	AssertChannel(IP_Diffuse, CT_Blue, PT_uint8, pcChannels.Get(3));

	WriteImage(pcImage, "Output\\tar32un.raw");
	AssertFileMemory("input\\tar32un.raw", pcImage->GetData(), pcImage->GetByteSize());
	pcImage = NULL;


	pcImage = ReadImage("Input\\tar24un.tga");
	pcImage->GetAllChannels(&pcChannels);
	AssertInt(3, pcChannels.NumElements());
	AssertChannel(IP_Diffuse, CT_Red, PT_uint8, pcChannels.Get(0));
	AssertChannel(IP_Diffuse, CT_Green, PT_uint8, pcChannels.Get(1));
	AssertChannel(IP_Diffuse, CT_Blue, PT_uint8, pcChannels.Get(2));


	WriteImage(pcImage, "Output\\tar24un.raw");
	AssertFileMemory("input\\tar24un.raw", pcImage->GetData(), pcImage->GetByteSize());
	pcImage = NULL;


	pcImage = ReadImage("Input\\tar16un.tga");
	pcImage->GetAllChannels(&pcChannels);
	AssertInt(3, pcChannels.NumElements());
	AssertChannel(IP_Diffuse, CT_Red, PT_uint8, pcChannels.Get(0));
	AssertChannel(IP_Diffuse, CT_Green, PT_uint8, pcChannels.Get(1));
	AssertChannel(IP_Diffuse, CT_Blue, PT_uint8, pcChannels.Get(2));

	WriteImage(pcImage, "Output\\tar16un.raw");
	AssertFileMemory("input\\tar16un.raw", pcImage->GetData(), pcImage->GetByteSize());
	pcImage = NULL;
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

