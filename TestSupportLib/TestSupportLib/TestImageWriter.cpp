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
	CImage		cImage;
	CImage		cComp;
	CArrayInt	aiChannels;

	//The GDI+ seems to be unable to write most of the types it claims, only 32 bit ARGB seems to work.
	ReadImage(&cImage, "Input\\basn2c08.png");
	WriteImage(&cImage, "Output\\basn2c08.png");
	ReadImage(&cComp, "Output\\basn2c08.png");
	AssertInt(32, cComp.GetWidth());
	AssertInt(32, cComp.GetHeight());
	cComp.GetAllChannels(&aiChannels);
	AssertInt(3, aiChannels.NumElements());
	AssertInt(IMAGE_DIFFUSE_RED, aiChannels.GetValue(0));
	AssertInt(IMAGE_DIFFUSE_GREEN, aiChannels.GetValue(1));
	AssertInt(IMAGE_DIFFUSE_BLUE, aiChannels.GetValue(2));
	AssertMemory(cImage.mcChannels.GetData(), cComp.mcChannels.GetData(), cImage.GetByteSize());
	aiChannels.Kill();
	cImage.Kill();
	cComp.Kill();

	//Not testing this unitl I start using PNGLib to write images rather than the GDI+.
	ReadImage(&cImage, "Input\\basn0g01.png");
	WriteImage(&cImage, "Output\\basn0g01.png");
	cImage.Kill();

	ReadImage(&cImage, "Input\\basn0g02.png");
	WriteImage(&cImage, "Output\\basn0g02.png");
	cImage.Kill();

	ReadImage(&cImage, "Input\\basn0g04.png");
	WriteImage(&cImage, "Output\\basn0g04.png");
	cImage.Kill();

	ReadImage(&cImage, "Input\\basn0g08.png");
	WriteImage(&cImage, "Output\\basn0g08.png");
	cImage.Kill();

	ReadImage(&cImage, "Input\\basn0g16.png");
	WriteImage(&cImage, "Output\\basn0g16.png");
	cImage.Kill();

	ReadImage(&cImage, "Input\\basn2c16.png");
	WriteImage(&cImage, "Output\\basn2c16.png");
	cImage.Kill();

	//ReadImage(&cImage, "Input\\basn3p01.png");
	//WriteImage(&cImage, "Output\\basn3p01.png");

	//ReadImage(&cImage, "Input\\basn3p02.png");
	//WriteImage(&cImage, "Output\\basn3p02.png");

	//ReadImage(&cImage, "Input\\basn3p04.png");
	//WriteImage(&cImage, "Output\\basn3p04.png");

	//ReadImage(&cImage, "Input\\basn3p08.png");
	//WriteImage(&cImage, "Output\\basn3p08.png");

	ReadImage(&cImage, "Input\\basn4a08.png");
	WriteImage(&cImage, "Output\\basn4a08.png");
	cImage.Kill();

	ReadImage(&cImage, "Input\\basn4a16.png");
	WriteImage(&cImage, "Output\\basn4a16.png");
	cImage.Kill();

	ReadImage(&cImage, "Input\\basn6a08.png");
	WriteImage(&cImage, "Output\\basn6a08.png");
	cImage.Kill();

	ReadImage(&cImage, "Input\\basn6a16.png");
	WriteImage(&cImage, "Output\\basn6a16.png");
	cImage.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageTGAWriter(void)
{
	//CImage		cImage;
	//CImage		cComp;
	//CArrayInt	aiChannels;

	//ReadImage(&cImage, "Input\\tar24un.tga");
	//WriteImage(&cImage, "Output\\tar24un.tga");
	//ReadImage(&cComp, "Output\\tar24un.tga");
	//AssertInt(32, cComp.GetWidth());
	//AssertInt(32, cComp.GetHeight());
	//cComp.GetAllChannels(&aiChannels);
	//AssertInt(3, aiChannels.NumElements());
	//AssertInt(IMAGE_DIFFUSE_RED, aiChannels.GetValue(0));
	//AssertInt(IMAGE_DIFFUSE_GREEN, aiChannels.GetValue(1));
	//AssertInt(IMAGE_DIFFUSE_BLUE, aiChannels.GetValue(2));
	//AssertMemory(cImage.mcChannels.GetData(), cComp.mcChannels.GetData(), cImage.GetByteSize());
	//aiChannels.Kill();
	//cImage.Kill();
	//cComp.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageRADWriter(void)
{
	CImage		cImage;
	CImage		cComp;
	CArrayInt	aiChannels;
	bool		bResult;

	//The GDI+ seems to be unable to write most of the types it claims, only 32 bit ARGB seems to work.
	ReadImage(&cImage, "Input\\basn2c08.png");
	bResult = WriteImage(&cImage, "Output\\writerad.rad");
	AssertBool(true, bResult);
	bResult = ReadImage(&cComp, "Output\\writerad.rad");
	AssertBool(true, bResult);
	AssertInt(32, cComp.GetWidth());
	AssertInt(32, cComp.GetHeight());
	cComp.GetAllChannels(&aiChannels);
	AssertInt(3, aiChannels.NumElements());
	AssertInt(IMAGE_DIFFUSE_RED, aiChannels.GetValue(0));
	AssertInt(IMAGE_DIFFUSE_GREEN, aiChannels.GetValue(1));
	AssertInt(IMAGE_DIFFUSE_BLUE, aiChannels.GetValue(2));
	AssertMemory(cImage.mcChannels.GetData(), cComp.mcChannels.GetData(), cImage.GetByteSize());
	aiChannels.Kill();
	cImage.Kill();
	cComp.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImageSFTWriter(void)
{
	CImage		cImage;
	CImage		cComp;
	bool		bResult;

	bResult = ReadImage(&cImage, "Input\\basn2c08.png");
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
	TestImageSFTWriter();

	ObjectsKill();
	DataIOKill();

	TestStatistics();
}

