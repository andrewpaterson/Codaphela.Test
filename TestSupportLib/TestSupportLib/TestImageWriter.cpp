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
	Ptr<CImage> pcImage = ReadImage("Input\\basn2c08.png");
	WriteImage(pcImage, "Output\\basn2c08.png");
	Ptr<CImage> pcComp = ReadImage("Output\\basn2c08.png");
	AssertInt(32, pcComp->GetWidth());
	AssertInt(32, pcComp->GetHeight());
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
	pcImage = ReadImage("Input\\basn0g01.png");
	WriteImage(pcImage, "Output\\basn0g01.png");
	pcImage->Kill();

	pcImage = ReadImage("Input\\basn0g02.png");
	WriteImage(pcImage, "Output\\basn0g02.png");
	pcImage->Kill();

	pcImage = ReadImage("Input\\basn0g04.png");
	WriteImage(pcImage, "Output\\basn0g04.png");
	pcImage->Kill();

	pcImage = ReadImage("Input\\basn0g08.png");
	WriteImage(pcImage, "Output\\basn0g08.png");
	pcImage->Kill();

	pcImage = ReadImage("Input\\basn0g16.png");
	WriteImage(pcImage, "Output\\basn0g16.png");
	pcImage->Kill();

	pcImage = ReadImage("Input\\basn2c16.png");
	WriteImage(pcImage, "Output\\basn2c16.png");
	pcImage->Kill();

	//pcImage = ReadImage("Input\\basn3p01.png");
	//WriteImage(pcImage, "Output\\basn3p01.png");

	//pcImage = ReadImage("Input\\basn3p02.png");
	//WriteImage(pcImage, "Output\\basn3p02.png");

	//pcImage = ReadImage("Input\\basn3p04.png");
	//WriteImage(pcImage, "Output\\basn3p04.png");

	//pcImage = ReadImage("Input\\basn3p08.png");
	//WriteImage(pcImage, "Output\\basn3p08.png");

	pcImage = ReadImage("Input\\basn4a08.png");
	WriteImage(pcImage, "Output\\basn4a08.png");
	pcImage->Kill();

	pcImage = ReadImage("Input\\basn4a16.png");
	WriteImage(pcImage, "Output\\basn4a16.png");
	pcImage->Kill();

	pcImage = ReadImage("Input\\basn6a08.png");
	WriteImage(pcImage, "Output\\basn6a08.png");
	pcImage->Kill();

	pcImage = ReadImage("Input\\basn6a16.png");
	WriteImage(pcImage, "Output\\basn6a16.png");
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

	//Ptr<CImage> pcImage = ReadImage("Input\\tar24un.tga");
	//WriteImage(pcImage, "Output\\tar24un.tga");
	//Ptr<CImage> pcComp = ReadImage("Output\\tar24un.tga");
	//AssertInt(32, pcComp->GetWidth());
	//AssertInt(32, pcComp->GetHeight());
	//pcComp->GetAllChannels(&aiChannels);
	//AssertInt(3, aiChannels.NumElements());
	//AssertInt(IMAGE_DIFFUSE_RED, aiChannels.GetValue(0));
	//AssertInt(IMAGE_DIFFUSE_GREEN, aiChannels.GetValue(1));
	//AssertInt(IMAGE_DIFFUSE_BLUE, aiChannels.GetValue(2));
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
	Ptr<CImage> pcImage = ReadImage("Input\\basn2c08.png");
	bResult = WriteImage(pcImage, "Output\\writerad.rad");
	AssertTrue(bResult);
	Ptr<CImage> pcComp = ReadImage("Output\\writerad.rad");
	AssertTrue(bResult);
	AssertInt(32, pcComp->GetWidth());
	AssertInt(32, pcComp->GetHeight());
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

