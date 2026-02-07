#include "SupportLib/Image.h"
#include "BaseLib/FastFunctions.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "StandardLib/Objects.h"
#include "SupportLib/ImageReader.h"
#include "SupportLib/ImageWriter.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImagePNGWriter(void)
{
	CArrayInt	aiChannels;

	//The GDI+ seems to be unable to write most of the types it claims, only 32 bit ARGB seems to work.
	Ptr<CImage> pcImage = ReadImage("Input" _FS_ "basn2c08.png");
	WriteImage(pcImage, "Output" _FS_ "basn2c08.png");
	Ptr<CImage> pcComp = ReadImage("Output" _FS_ "basn2c08.png");
	AssertInt(32, pcComp->GetWidth());
	AssertInt(32, pcComp->GetHeight());
	aiChannels.Init();
	pcComp->GetAllChannels(&aiChannels);
	AssertInt(3, aiChannels.NumElements());
	AssertInt(IMAGE_DIFFUSE_RED, aiChannels.GetValue(0));
	AssertInt(IMAGE_DIFFUSE_GREEN, aiChannels.GetValue(1));
	AssertInt(IMAGE_DIFFUSE_BLUE, aiChannels.GetValue(2));
	AssertMemory(pcImage->mcChannels.GetData(), pcComp->mcChannels.GetData(), pcImage->GetByteSize());
	aiChannels.Kill();
	pcImage->Kill();
	pcComp->Kill();

	//Not testing this unitl I start using PNGLib to write images rather than the GDI+.
	pcImage = ReadImage("Input" _FS_ "basn0g01.png");
	WriteImage(pcImage, "Output" _FS_ "basn0g01.png");
	pcImage->Kill();

	pcImage = ReadImage("Input" _FS_ "basn0g02.png");
	WriteImage(pcImage, "Output" _FS_ "basn0g02.png");
	pcImage->Kill();

	pcImage = ReadImage("Input" _FS_ "basn0g04.png");
	WriteImage(pcImage, "Output" _FS_ "basn0g04.png");
	pcImage->Kill();

	pcImage = ReadImage("Input" _FS_ "basn0g08.png");
	WriteImage(pcImage, "Output" _FS_ "basn0g08.png");
	pcImage->Kill();

	pcImage = ReadImage("Input" _FS_ "basn0g16.png");
	WriteImage(pcImage, "Output" _FS_ "basn0g16.png");
	pcImage->Kill();

	pcImage = ReadImage("Input" _FS_ "basn2c16.png");
	WriteImage(pcImage, "Output" _FS_ "basn2c16.png");
	pcImage->Kill();

	//pcImage = ReadImage("Input" _FS_ "basn3p01.png");
	//WriteImage(pcImage, "Output" _FS_ "basn3p01.png");

	//pcImage = ReadImage("Input" _FS_ "basn3p02.png");
	//WriteImage(pcImage, "Output" _FS_ "basn3p02.png");

	//pcImage = ReadImage("Input" _FS_ "basn3p04.png");
	//WriteImage(pcImage, "Output" _FS_ "basn3p04.png");

	//pcImage = ReadImage("Input" _FS_ "basn3p08.png");
	//WriteImage(pcImage, "Output" _FS_ "basn3p08.png");

	pcImage = ReadImage("Input" _FS_ "basn4a08.png");
	WriteImage(pcImage, "Output" _FS_ "basn4a08.png");
	pcImage->Kill();

	pcImage = ReadImage("Input" _FS_ "basn4a16.png");
	WriteImage(pcImage, "Output" _FS_ "basn4a16.png");
	pcImage->Kill();

	pcImage = ReadImage("Input" _FS_ "basn6a08.png");
	WriteImage(pcImage, "Output" _FS_ "basn6a08.png");
	pcImage->Kill();

	pcImage = ReadImage("Input" _FS_ "basn6a16.png");
	WriteImage(pcImage, "Output" _FS_ "basn6a16.png");
	pcImage->Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageTGAWriter(void)
{
	//CImage		pcImage;
	//CImage		pcComp;
	//CArrayInt	aiChannels;

	//Ptr<CImage> pcImage = ReadImage("Input" _FS_ "tar24un.tga");
	//WriteImage(pcImage, "Output" _FS_ "tar24un.tga");
	//Ptr<CImage> pcComp = ReadImage("Output" _FS_ "tar24un.tga");
	//AssertInt(32, pcComp->GetWidth());
	//AssertInt(32, pcComp->GetHeight());
	//acChannels.Init();
	//pcComp->GetAllChannels(&aiChannels);
	//AssertInt(3, aiChannels.NumElements());
	//AssertInt(IMAGE_DIFFUSE_RED, aiChannels.GetValue(0));
	//AssertInt(IMAGE_DIFFUSE_GREEN, aiChannels.GetValue(1));
	//AssertInt(IMAGE_DIFFUSE_BLUE, aiChannels.GetValue(2));
	//acChannels.Kill();
	//AssertMemory(pcImage->mcChannels.GetData(), pcComp->mcChannels.GetData(), pcImage->GetByteSize());
	//aiChannels.Kill();
	//pcImage->Kill();
	//pcComp->Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageRADWriter(void)
{
	CArrayInt		aiChannels;
	bool			bResult;

	//The GDI+ seems to be unable to write most of the types it claims, only 32 bit ARGB seems to work.
	Ptr<CImage> pcImage = ReadImage("Input" _FS_ "basn2c08.png");
	bResult = WriteImage(pcImage, "Output" _FS_ "writerad.rad");
	AssertTrue(bResult);
	Ptr<CImage> pcComp = ReadImage("Output" _FS_ "writerad.rad");
	AssertTrue(bResult);
	AssertInt(32, pcComp->GetWidth());
	AssertInt(32, pcComp->GetHeight());
	aiChannels.Init();
	pcComp->GetAllChannels(&aiChannels);
	AssertInt(3, aiChannels.NumElements());
	AssertInt(IMAGE_DIFFUSE_RED, aiChannels.GetValue(0));
	AssertInt(IMAGE_DIFFUSE_GREEN, aiChannels.GetValue(1));
	AssertInt(IMAGE_DIFFUSE_BLUE, aiChannels.GetValue(2));
	AssertMemory(pcImage->mcChannels.GetData(), pcComp->mcChannels.GetData(), pcImage->GetByteSize());
	aiChannels.Kill();
	pcImage->Kill();
	pcComp->Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageWriter(void)
{
	BeginTests();

	DataIOInit();
	ObjectsInit();

	TestImagePNGWriter();
	TestImageTGAWriter();
	TestImageRADWriter();

	ObjectsKill();
	DataIOKill();

	TestStatistics();
}

