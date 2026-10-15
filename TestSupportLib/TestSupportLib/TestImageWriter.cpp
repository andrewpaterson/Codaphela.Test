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
// Reads Input/szName, writes it to Output/szName and reads it back.  The
// image read back must have the same size, channels and data.
//
//////////////////////////////////////////////////////////////////////////
void AssertPNGRoundTrip(const char* szName)
{
	CChars			szInput;
	CChars			szOutput;
	CArraySize		aiExpectedChannels;
	CArraySize		aiActualChannels;
	size			i;
	bool			bResult;

	szInput.Init("Input" _FS_);
	szInput.Append(szName);
	szOutput.Init("Output" _FS_);
	szOutput.Append(szName);

	Ptr<CImage> pcImage = ReadImage(szInput.Text());
	AssertTrue(pcImage.IsNotNull());
	bResult = WriteImage(pcImage, szOutput.Text());
	AssertTrue(bResult);
	Ptr<CImage> pcComp = ReadImage(szOutput.Text());
	AssertTrue(pcComp.IsNotNull());

	AssertInt(pcImage->GetWidth(), pcComp->GetWidth());
	AssertInt(pcImage->GetHeight(), pcComp->GetHeight());

	aiExpectedChannels.Init();
	aiActualChannels.Init();
	pcImage->GetAllChannels(&aiExpectedChannels);
	pcComp->GetAllChannels(&aiActualChannels);
	AssertSize(aiExpectedChannels.NumElements(), aiActualChannels.NumElements());
	if (aiExpectedChannels.NumElements() == aiActualChannels.NumElements())
	{
		for (i = 0; i < aiExpectedChannels.NumElements(); i++)
		{
			AssertSize(aiExpectedChannels.GetValue(i), aiActualChannels.GetValue(i));
		}
	}
	aiExpectedChannels.Kill();
	aiActualChannels.Kill();

	AssertSize(pcImage->GetByteSize(), pcComp->GetByteSize());
	if (pcImage->GetByteSize() == pcComp->GetByteSize())
	{
		AssertMemory(pcImage->mcChannels.GetData(), pcComp->mcChannels.GetData(), pcImage->GetByteSize());
	}

	pcImage->Kill();
	pcComp->Kill();
	szOutput.Kill();
	szInput.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestImagePNGWriter(void)
{
	CArraySize	aiChannels;

	//The GDI+ seems to be unable to write most of the types it claims, only 32 bit ARGB seems to work.
	Ptr<CImage> pcImage = ReadImage("Input" _FS_ "basn2c08.png");
	WriteImage(pcImage, "Output" _FS_ "basn2c08.png");
	Ptr<CImage> pcComp = ReadImage("Output" _FS_ "basn2c08.png");
	AssertInt(32, pcComp->GetWidth());
	AssertInt(32, pcComp->GetHeight());
	aiChannels.Init();
	pcComp->GetAllChannels(&aiChannels);
	AssertSize(3, aiChannels.NumElements());
	AssertSize(IMAGE_DIFFUSE_RED, aiChannels.GetValue(0));
	AssertSize(IMAGE_DIFFUSE_GREEN, aiChannels.GetValue(1));
	AssertSize(IMAGE_DIFFUSE_BLUE, aiChannels.GetValue(2));
	AssertMemory(pcImage->mcChannels.GetData(), pcComp->mcChannels.GetData(), pcImage->GetByteSize());
	aiChannels.Kill();
	pcImage->Kill();
	pcComp->Kill();

	AssertPNGRoundTrip("basn0g01.png");
	AssertPNGRoundTrip("basn0g02.png");
	AssertPNGRoundTrip("basn0g04.png");
	AssertPNGRoundTrip("basn0g08.png");
	AssertPNGRoundTrip("basn0g16.png");
	AssertPNGRoundTrip("basn2c16.png");

	//Palettes are not read yet.
	//AssertPNGRoundTrip("basn3p01.png");
	//AssertPNGRoundTrip("basn3p02.png");
	//AssertPNGRoundTrip("basn3p04.png");
	//AssertPNGRoundTrip("basn3p08.png");

	AssertPNGRoundTrip("basn4a08.png");
	AssertPNGRoundTrip("basn4a16.png");
	AssertPNGRoundTrip("basn6a08.png");
	AssertPNGRoundTrip("basn6a16.png");
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
	CArraySize		aiChannels;
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
	AssertSize(3, aiChannels.NumElements());
	AssertSize(IMAGE_DIFFUSE_RED, aiChannels.GetValue(0));
	AssertSize(IMAGE_DIFFUSE_GREEN, aiChannels.GetValue(1));
	AssertSize(IMAGE_DIFFUSE_BLUE, aiChannels.GetValue(2));
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

	ObjectsKill(false);
	DataIOKill();

	TestStatistics();
}

