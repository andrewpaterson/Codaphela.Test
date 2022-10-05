#include "BaseLib/FastFunctions.h"
#include "BaseLib/IntegerHelper.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/RedirectPrintf.h"
#include "BaseLib/StdRandom.h"
#include "BaseLib/DiskFile.h"
#include "BaseLib/StringHelper.h"
#include "BaseLib/ArrayChars.h"
#include "CoreLib/MemoryDrive.h"
#include "CoreLib/Fat32.h"
#include "CoreLib/FatDebug.h"
#include "TestLib/Assert.h"
#include "TestLib/Words.h"
#include "TestFat32Common.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFat32ReadSpecific(void)
{
	CMemoryDrive			cMemoryDrive;
	CDiskFile				cFile;
	filePos					uiLength;
	void*					pvMemory;
	SFatDirectoryEntry*		psFatDirectoryEntry;
	SFatDirectoryEntry		sFatFileEntry;
	SFatFileSystemQuery		sQuery;
	EFatCode				eResult;
	CFatFile				cFatFile;
	bool					bResult;
	uint32					uiBytesRead;
	char					auiFileData[44 KB];
	char					auiExpectedData[44 KB];
	CFatVolume				cVolume;

	cFile.Init("Input\\Fat32\\ComplexDisk.img");
	bResult = cFile.Open(EFM_Read);
	AssertTrue(bResult);
	uiLength = cFile.Size();
	cMemoryDrive.Init((size_t)uiLength, 512);
	pvMemory = cMemoryDrive.GetMemory();
	cFile.Read(pvMemory, uiLength, 1);
	cFile.Close();
	cFile.Kill();

	AssertInt(sizeof(uint8), sizeof(char));

	eResult = cVolume.Mount(&cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);


	memset(&sQuery, 0, sizeof(SFatFileSystemQuery));
	eResult = cVolume.FindFirstFATEntry(NULL, 0, &psFatDirectoryEntry, &sQuery);
	AssertInt(FAT_SUCCESS, eResult);
	AssertString("Document.txt", (char*)psFatDirectoryEntry->name);
	AssertInt(FAT_ATTR_ARCHIVE, psFatDirectoryEntry->attributes);

	cFatFile.Init(&cVolume);
	eResult = cFatFile.Open((char*)psFatDirectoryEntry->name, 0);
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cFatFile.Read((uint8*)auiFileData, cFatFile.GetCurrentSize(), &uiBytesRead);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(12, uiBytesRead);
	auiFileData[12] = '\0';
	AssertString("Mostly Empty", auiFileData);

	eResult = cFatFile.Close();
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cVolume.FindNextFATEntry(&psFatDirectoryEntry, &sQuery);
	AssertInt(FAT_SUCCESS, eResult);
	AssertString("Pico", (char*)psFatDirectoryEntry->name);
	AssertInt(FAT_ATTR_DIRECTORY, psFatDirectoryEntry->attributes);

	eResult = cVolume.FindNextFATEntry(&psFatDirectoryEntry, &sQuery);
	AssertTrue((StrEmpty((char*)psFatDirectoryEntry->name)));


	memset(&sQuery, 0, sizeof(SFatFileSystemQuery));
	eResult = cVolume.FindFirstFATEntry("\\Pico", 0, &psFatDirectoryEntry, &sQuery);
	AssertInt(FAT_SUCCESS, eResult);
	AssertString(".", (char*)psFatDirectoryEntry->name);
	AssertInt(FAT_ATTR_DIRECTORY, psFatDirectoryEntry->attributes);

	eResult = cVolume.FindNextFATEntry(&psFatDirectoryEntry, &sQuery);
	AssertInt(FAT_SUCCESS, eResult);
	AssertString("..", (char*)psFatDirectoryEntry->name);
	AssertInt(FAT_ATTR_DIRECTORY, psFatDirectoryEntry->attributes);

	eResult = cVolume.FindNextFATEntry(&psFatDirectoryEntry, &sQuery);
	AssertInt(FAT_SUCCESS, eResult);
	AssertString(".gitignore", (char*)psFatDirectoryEntry->name);
	AssertInt(FAT_ATTR_ARCHIVE, psFatDirectoryEntry->attributes);

	eResult = cVolume.FindNextFATEntry(&psFatDirectoryEntry, &sQuery);
	AssertInt(FAT_SUCCESS, eResult);
	AssertString("HowDoesItWork", (char*)psFatDirectoryEntry->name);
	AssertInt(FAT_ATTR_DIRECTORY, psFatDirectoryEntry->attributes);

	eResult = cVolume.FindNextFATEntry(&psFatDirectoryEntry, &sQuery);
	AssertInt(FAT_SUCCESS, eResult);
	AssertString("LCDBusReader", (char*)psFatDirectoryEntry->name);
	AssertInt(FAT_ATTR_DIRECTORY, psFatDirectoryEntry->attributes);

	eResult = cVolume.FindNextFATEntry(&psFatDirectoryEntry, &sQuery);
	AssertTrue((StrEmpty((char*)psFatDirectoryEntry->name)));

	eResult = cVolume.GetFileEntry("\\Pico\\LCDBusReader", &sFatFileEntry);
	AssertInt(FAT_SUCCESS, eResult);
	AssertString("LCDBUS~1", (char*)sFatFileEntry.name);
	AssertInt(FAT_ATTR_DIRECTORY, sFatFileEntry.attributes);

	eResult = cVolume.GetFileEntry("\\Pico\\LCDBusReader\\src", &sFatFileEntry);
	AssertInt(FAT_SUCCESS, eResult);
	AssertString("SRC", (char*)sFatFileEntry.name);
	AssertInt(FAT_ATTR_DIRECTORY, sFatFileEntry.attributes);

	eResult = cVolume.GetFileEntry("\\Pico\\HowDoesItWork\\build.sh", &sFatFileEntry);
	AssertInt(FAT_SUCCESS, eResult);
	AssertString("BUILD.SH", (char*)sFatFileEntry.name);
	AssertInt(FAT_ATTR_ARCHIVE, sFatFileEntry.attributes);

	eResult = cVolume.GetFileEntry("\\Pico\\LCDBusReader\\src\\SDCard.cpp", &sFatFileEntry);
	AssertInt(FAT_SUCCESS, eResult);
	AssertString("SDCARD.CPP", (char*)sFatFileEntry.name);
	AssertInt(FAT_ATTR_ARCHIVE, sFatFileEntry.attributes);

	cFatFile.Init(&cVolume);
	eResult = cFatFile.Open(&sFatFileEntry, FAT_FILE_ACCESS_READ);
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cFatFile.Read((uint8*)auiFileData, cFatFile.GetCurrentSize(), &uiBytesRead);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(44000, uiBytesRead);
	auiFileData[44000] = '\0';

	cFatFile.Close();


	cFile.Init("Input\\Fat32\\SDCard.cpp");
	bResult = cFile.Open(EFM_Read);
	AssertTrue(bResult);
	uiLength = cFile.Size();
	AssertInt(44000, (int)uiLength);
	cFile.Read(auiExpectedData, uiLength, 1);
	cFile.Close();
	cFile.Kill();
	AssertMemory(auiExpectedData, auiFileData, (int)uiLength);


	eResult = cVolume.GetFileEntry("\\Pico\\LCDBusReader\\src\\LCDBusReader.cpp", &sFatFileEntry);
	AssertInt(FAT_SUCCESS, eResult);
	AssertString("LCDBUS~1.CPP", (char*)sFatFileEntry.name);
	AssertInt(FAT_ATTR_ARCHIVE, sFatFileEntry.attributes);


	cVolume.Unmount();

	cMemoryDrive.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFat32ReadDirectoryTree(void)
{
	CMemoryDrive			cMemoryDrive;
	CDiskFile				cFile;
	filePos					uiLength;
	void*					pvMemory;
	EFatCode				eResult;
	bool					bResult;
	CArrayChars				aszFileNames;
	CChars					sz;
	int						i;
	char*					szFileName;
	SFatDirectoryEntry		sFatFileEntry;
	char					auiFileData[44 KB];
	CFatFile				cFatFile;
	uint32					uiBytesRead;
	CFatVolume				cVolume;

	cFile.Init("Input\\Fat32\\ComplexDisk.img");
	bResult = cFile.Open(EFM_Read);
	AssertTrue(bResult);
	uiLength = cFile.Size();
	cMemoryDrive.Init((size_t)uiLength, 512);
	pvMemory = cMemoryDrive.GetMemory();
	cFile.Read(pvMemory, uiLength, 1);
	cFile.Close();
	cFile.Kill();

	eResult = cVolume.Mount(&cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);

	aszFileNames.Init();
	RecurseFindFatFilenames(&cVolume, "", &aszFileNames);

	sz.Init();
	aszFileNames.Print(&sz);
	AssertString("\
\\Document.txt\n\
\\Pico\\.gitignore\n\
\\Pico\\HowDoesItWork\\build.sh\n\
\\Pico\\HowDoesItWork\\CMakeLists.txt\n\
\\Pico\\HowDoesItWork\\deploy.sh\n\
\\Pico\\HowDoesItWork\\HowDoesItWork.c\n\
\\Pico\\HowDoesItWork\\pico_sdk_import.cmake\n\
\\Pico\\HowDoesItWork\\.vscode\\.cortex-debug.peripherals.state.json\n\
\\Pico\\HowDoesItWork\\.vscode\\.cortex-debug.registers.state.json\n\
\\Pico\\HowDoesItWork\\.vscode\\c_cpp_properties.json\n\
\\Pico\\HowDoesItWork\\.vscode\\launch.json\n\
\\Pico\\HowDoesItWork\\.vscode\\settings.json\n\
\\Pico\\LCDBusReader\\build.sh\n\
\\Pico\\LCDBusReader\\CMakeLists.txt\n\
\\Pico\\LCDBusReader\\deploy.sh\n\
\\Pico\\LCDBusReader\\pico_sdk_import.cmake\n\
\\Pico\\LCDBusReader\\.vscode\\.cortex-debug.peripherals.state.json\n\
\\Pico\\LCDBusReader\\.vscode\\.cortex-debug.registers.state.json\n\
\\Pico\\LCDBusReader\\.vscode\\c_cpp_properties.json\n\
\\Pico\\LCDBusReader\\.vscode\\launch.json\n\
\\Pico\\LCDBusReader\\.vscode\\settings.json\n\
\\Pico\\LCDBusReader\\src\\GeneralPins.cpp\n\
\\Pico\\LCDBusReader\\src\\GeneralPins.h\n\
\\Pico\\LCDBusReader\\src\\HEXDisplay.cpp\n\
\\Pico\\LCDBusReader\\src\\HEXDisplay.h\n\
\\Pico\\LCDBusReader\\src\\HexToMem.cpp\n\
\\Pico\\LCDBusReader\\src\\HexToMem.h\n\
\\Pico\\LCDBusReader\\src\\LCDBusReader.cpp\n\
\\Pico\\LCDBusReader\\src\\LCDDisplay.cpp\n\
\\Pico\\LCDBusReader\\src\\LCDDisplay.h\n\
\\Pico\\LCDBusReader\\src\\LTC6903.cpp\n\
\\Pico\\LCDBusReader\\src\\LTC6903.h\n\
\\Pico\\LCDBusReader\\src\\SDCard.cpp\n\
\\Pico\\LCDBusReader\\src\\SDCard.h\n\
\\Pico\\LCDBusReader\\src\\SDCardTest.h\n\
\\Pico\\LCDBusReader\\src\\ShiftLCDDisplay.cpp\n\
\\Pico\\LCDBusReader\\src\\ShiftLCDDisplay.h\n\
\\Pico\\LCDBusReader\\src\\ShiftRegister.cpp\n\
\\Pico\\LCDBusReader\\src\\ShiftRegister.h\n\
\\Pico\\LCDBusReader\\src\\SPIComm.cpp\n\
\\Pico\\LCDBusReader\\src\\SPIComm.h\n\
\\Pico\\LCDBusReader\\src\\UARTComm.cpp\n\
\\Pico\\LCDBusReader\\src\\UARTComm.h\n", sz.Text());
	sz.Kill();

	for (i = 0; i < aszFileNames.NumElements(); i++)
	{
		szFileName = aszFileNames.GetText(i);
		eResult = cVolume.GetFileEntry(szFileName, &sFatFileEntry);
		AssertInt(FAT_SUCCESS, eResult);

		cFatFile.Init(&cVolume);
		eResult = cFatFile.Open(szFileName, 0);
		AssertInt(FAT_SUCCESS, eResult);

		eResult = cFatFile.Read((uint8*)auiFileData, cFatFile.GetCurrentSize(), &uiBytesRead);
		AssertInt(FAT_SUCCESS, eResult);
		AssertInt(cFatFile.GetCurrentSize(), uiBytesRead);
		AssertInt(sFatFileEntry.size, uiBytesRead);

		eResult = cFatFile.Close();
		AssertInt(FAT_SUCCESS, eResult);
	}

	aszFileNames.Kill();

	cVolume.Unmount();

	cMemoryDrive.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFat32Format(void)
{
	CMemoryDrive			cMemoryDrive;
	CDiskFile				cFile;
	filePos					uiLength;
	void*					pvMemory;
	EFatCode				eResult;
	bool					bResult;
	SFatDirectoryEntry*		psFatDirectoryEntry;
	SFatFileSystemQuery		sQuery;
	CFatVolume				cVolume;

	cFile.Init("Input\\Fat32\\ComplexDisk.img");
	bResult = cFile.Open(EFM_Read);
	AssertTrue(bResult);
	uiLength = cFile.Size();
	cMemoryDrive.Init((size_t)uiLength, 512);
	pvMemory = cMemoryDrive.GetMemory();
	cFile.Read(pvMemory, uiLength, 1);
	cFile.Close();
	cFile.Kill();

	eResult = FatFormat(FAT_FS_TYPE_FAT32, "FAT32", 1, &cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cVolume.Mount(&cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);

	memset(&sQuery, 0, sizeof(SFatFileSystemQuery));
	eResult = cVolume.FindFirstFATEntry(NULL, 0, &psFatDirectoryEntry, &sQuery);
	AssertInt(FAT_SUCCESS, eResult);
	AssertString("", (char*)psFatDirectoryEntry->name);
	AssertInt(0, psFatDirectoryEntry->attributes);

	eResult = cVolume.Unmount();
	AssertInt(FAT_SUCCESS, eResult);

	cMemoryDrive.Kill();
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFat32CreateFileEntries(void)
{
	CMemoryDrive			cMemoryDrive;
	CDiskFile				cFile;
	filePos					uiLength;
	void*					pvMemory;
	EFatCode				eResult;
	bool					bResult;
	CFatVolume				cVolume;
	SFatDirectoryEntry		sRootDirectoryEntry;
	SFatDirectoryEntry		sFileEntry;
	int						i;
	CChars					szFileName;
	CRandom					cRandom;
	CChars					sz;

	cFile.Init("Input\\Fat32\\ComplexDisk.img");
	bResult = cFile.Open(EFM_Read);
	AssertTrue(bResult);
	uiLength = cFile.Size();
	cMemoryDrive.Init((size_t)uiLength, 512);
	pvMemory = cMemoryDrive.GetMemory();
	cFile.Read(pvMemory, uiLength, 1);
	cFile.Close();
	cFile.Kill();

	eResult = cVolume.Mount(&cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cVolume.GetFileEntry("\\", &sRootDirectoryEntry);

	eResult = cVolume.CreateFATEntry(&sRootDirectoryEntry.raw, "Wort Wort Wort.cov", FAT_ATTR_ARCHIVE, 0, &sFileEntry);
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cVolume.Flush();
	AssertInt(FAT_SUCCESS, eResult);

	sz.Init();
	PrintRootFatFilenames(&sz, &cVolume);
	AssertString("\
\\Wort Wort Wort.cov\n\
\\Document.txt\n", sz.Text());
	sz.Kill();

	eResult = cVolume.Unmount();
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cVolume.Mount(&cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);

	cRandom.Init(4526);
	eResult = cVolume.GetFileEntry("\\", &sRootDirectoryEntry);
	for (i = 0; i < 10; i++)
	{
		szFileName.Init();
		PrintRandomWords(&szFileName, &cRandom, true, 30);
		szFileName.Append('.');
		PrintRandomWords(&szFileName, &cRandom, false, 1);

		if (szFileName.Length() > FAT_MAX_FILENAME - 1)
		{
			szFileName.SetLength(FAT_MAX_FILENAME - 1);
		}
		
		szFileName.Replace(",", " -");
		eResult = cVolume.CreateFATEntry(&sRootDirectoryEntry.raw, szFileName.Text(), FAT_ATTR_ARCHIVE, 0, &sFileEntry);
		AssertInt(FAT_SUCCESS, eResult);
		szFileName.Kill();
	}
	cRandom.Kill();

	eResult = cVolume.Flush();
	AssertInt(FAT_SUCCESS, eResult);

	DumpRootFatFilenames(&cVolume);

	eResult = cVolume.Unmount();
	AssertInt(FAT_SUCCESS, eResult);

	cMemoryDrive.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFat32OpenWriteMode(void)
{
	CMemoryDrive			cMemoryDrive;
	size_t					uiLength;
	void*					pvMemory;
	EFatCode				eResult;
	CFatFile				cFatFile;
	CFatVolume				cVolume;
	uint64					uiMaxSectorSize;
	SFatFileSystemQuery		sQuery;
	SFatDirectoryEntry*		psFatDirectoryEntry;

	uiLength = 4 MB;
	cMemoryDrive.Init(uiLength, 512);
	pvMemory = cMemoryDrive.GetMemory();
	
	cMemoryDrive.Erase();
	uiMaxSectorSize = cMemoryDrive.SetMaxSectorForTesting((uiLength / 512) * 1024);

	eResult = FatFormat(FAT_FS_TYPE_FAT32, "Fat32", 64, &cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);

	cMemoryDrive.SetMaxSectorForTesting(uiMaxSectorSize);

	eResult = cVolume.Mount(&cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);

	cFatFile.Init(&cVolume);
	eResult = cFatFile.Open("\\File.txt", FAT_FILE_ACCESS_CREATE | FAT_FILE_ACCESS_WRITE);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(0, cFatFile.GetCurrentSize());

	eResult = cFatFile.Close();
	AssertInt(FAT_SUCCESS, eResult);

	memset(&sQuery, 0, sizeof(SFatFileSystemQuery));
	eResult = cVolume.FindFirstFATEntry(NULL, 0, &psFatDirectoryEntry, &sQuery);
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cVolume.Unmount();
	AssertInt(FAT_SUCCESS, eResult);

	cMemoryDrive.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFat32Write(void)
{
	CMemoryDrive			cMemoryDrive;
	CDiskFile				cFile;
	filePos					uiLength;
	void*					pvMemory;
	EFatCode				eResult;
	bool					bResult;
	CFatVolume				cVolume;
	CFatFile				cFatFile;
	char					auiFileData[4 KB];
	char					auiFileData2[4 KB];
	int						i;
	uint32					uiBytesRead;

	cFile.Init("Input\\Fat32\\ComplexDisk.img");
	bResult = cFile.Open(EFM_Read);
	AssertTrue(bResult);
	uiLength = cFile.Size();
	cMemoryDrive.Init((size_t)uiLength, 512);
	pvMemory = cMemoryDrive.GetMemory();
	cFile.Read(pvMemory, uiLength, 1);
	cFile.Close();
	cFile.Kill();

	eResult = cVolume.Mount(&cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);

	cFatFile.Init(&cVolume);
	eResult = cFatFile.Open("\\New File.txt", FAT_FILE_ACCESS_CREATE | FAT_FILE_ACCESS_WRITE);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(0, cFatFile.GetCurrentSize());

	for (i = 0; i < 4 KB; i++)
	{
		auiFileData[i] = (char)i;
	}

	eResult = cFatFile.Write((uint8*)auiFileData, 4 KB);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(4096, cFatFile.GetCurrentSize());

	eResult = cFatFile.Close();
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cVolume.Unmount();
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cVolume.Mount(&cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);

	cFatFile.Init(&cVolume);
	eResult = cFatFile.Open("\\New File.txt", FAT_FILE_ACCESS_READ);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(4096, cFatFile.GetCurrentSize());

	eResult = cFatFile.Read((uint8*)auiFileData2, 4 KB, &uiBytesRead);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(0, memcmp(auiFileData, auiFileData2, 4 KB));

	eResult = cFatFile.Close();
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cVolume.Unmount();
	AssertInt(FAT_SUCCESS, eResult);

	cMemoryDrive.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFat32CreateDirectory(void)
{
	CMemoryDrive	cMemoryDrive;
	CDiskFile		cFile;
	filePos			uiLength;
	void*			pvMemory;
	EFatCode		eResult;
	bool			bResult;
	CFatVolume		cVolume;
	CArrayChars		aszDirectories;
	CChars			sz;

	cFile.Init("Input\\Fat32\\ComplexDisk.img");
	bResult = cFile.Open(EFM_Read);
	AssertTrue(bResult);
	uiLength = cFile.Size();
	cMemoryDrive.Init((size_t)uiLength, 512);
	pvMemory = cMemoryDrive.GetMemory();
	cFile.Read(pvMemory, uiLength, 1);
	cFile.Close();
	cFile.Kill();

	eResult = cVolume.Mount(&cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);

	cVolume.FatCreateDirectory("\\A Directory");

	aszDirectories.Init();
	RecurseFindFatDirectories(&cVolume, "", &aszDirectories);

	sz.Init();
	aszDirectories.Print(&sz);
	aszDirectories.Kill();
	AssertString("\
\\A Directory\n\
\\Pico\\HowDoesItWork\\.vscode\n\
\\Pico\\HowDoesItWork\n\
\\Pico\\LCDBusReader\\.vscode\n\
\\Pico\\LCDBusReader\\src\n\
\\Pico\\LCDBusReader\n\
\\Pico\n", sz.Text());
	sz.Kill();
	
	eResult = cVolume.Unmount();
	AssertInt(FAT_SUCCESS, eResult);

	cMemoryDrive.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFat32FormatAndCreateDirectory(void)
{
	CMemoryDrive	cMemoryDrive;
	CDiskFile		cFile;
	filePos			uiLength;
	void*			pvMemory;
	EFatCode		eResult;
	bool			bResult;
	CFatVolume		cVolume;
	CArrayChars		aszDirectories;
	CChars			sz;

	cFile.Init("Input\\Fat32\\ComplexDisk.img");
	bResult = cFile.Open(EFM_Read);
	AssertTrue(bResult);
	uiLength = cFile.Size();
	cMemoryDrive.Init((size_t)uiLength, 512);
	pvMemory = cMemoryDrive.GetMemory();
	cFile.Read(pvMemory, uiLength, 1);
	cFile.Close();
	cFile.Kill();

	eResult = FatFormat(FAT_FS_TYPE_FAT32, "Fat32", 1, &cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cVolume.Mount(&cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cVolume.FatCreateDirectory("\\A Directory");
	AssertInt(FAT_SUCCESS, eResult);
	eResult = cVolume.FatCreateDirectory("\\A Directory\\Another");
	AssertInt(FAT_SUCCESS, eResult);

	aszDirectories.Init();
	RecurseFindFatDirectories(&cVolume, "", &aszDirectories);

	sz.Init();
	aszDirectories.Print(&sz);
	aszDirectories.Kill();
	AssertString("\
\\A Directory\\Another\n\
\\A Directory\n", sz.Text());
	sz.Kill();

	eResult = cVolume.Unmount();
	AssertInt(FAT_SUCCESS, eResult);

	cMemoryDrive.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFat32GreatWrite(void)
{
	CMemoryDrive			cMemoryDrive;
	CDiskFile				cFile;
	filePos					uiLength;
	void*					pvMemory;
	EFatCode				eResult;
	bool					bResult;
	SFatDirectoryEntry*		psFatDirectoryEntry;
	SFatFileSystemQuery		sQuery;
	CFatVolume				cVolume;
	CFatFile				cFatFile;
	char*					puiFileData;
	char*					puiFileData2;
	int						i;
	uint32					uiBytesRead;
	int						iLength;

	cFile.Init("Input\\Fat32\\ComplexDisk.img");
	bResult = cFile.Open(EFM_Read);
	AssertTrue(bResult);
	uiLength = cFile.Size();
	cMemoryDrive.Init((size_t)uiLength, 512);
	pvMemory = cMemoryDrive.GetMemory();
	cFile.Read(pvMemory, uiLength, 1);
	cFile.Close();
	cFile.Kill();

	eResult = cVolume.Mount(&cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);

	cFatFile.Init(&cVolume);
	eResult = cFatFile.Open("\\New File.txt", FAT_FILE_ACCESS_CREATE | FAT_FILE_ACCESS_WRITE);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(0, cFatFile.GetCurrentSize());

	memset(&sQuery, 0, sizeof(SFatFileSystemQuery));
	eResult = cVolume.FindFirstFATEntry(NULL, 0, &psFatDirectoryEntry, &sQuery);
	AssertInt(FAT_SUCCESS, eResult);
	AssertString("New File.txt", (char*)psFatDirectoryEntry->name);
	AssertInt(0, psFatDirectoryEntry->attributes);

	iLength = 196 KB;
	puiFileData = (char*)malloc(iLength);
	puiFileData2 = (char*)malloc(iLength);

	char c = 33;
	for (i = 0; i < iLength; i++)
	{
		puiFileData[i] = c;
		if (i % 3 == 2)
		{
			c++;
		}
	}

	eResult = cFatFile.Write((uint8*)puiFileData, iLength);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(196 KB, cFatFile.GetCurrentSize());

	eResult = cFatFile.Close();
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cVolume.Unmount();
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cVolume.Mount(&cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);

	cFatFile.Init(&cVolume);
	eResult = cFatFile.Open("\\New File.txt", FAT_FILE_ACCESS_READ);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(196 KB , cFatFile.GetCurrentSize());

	memset(puiFileData2, 0, iLength);
	eResult = cFatFile.Read((uint8*)puiFileData2, iLength, &uiBytesRead);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(iLength, uiBytesRead);
	AssertInt(0, memcmp(puiFileData, puiFileData2, iLength));

	eResult = cFatFile.Close();
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cFatFile.Open("\\New File.txt", FAT_FILE_ACCESS_READ);
	AssertInt(FAT_SUCCESS, eResult);

	memset(puiFileData2, 0, iLength);
	iLength = 196 KB - 64 KB - 1024;
	cFatFile.Seek(64 KB + 1024, FAT_SEEK_START);
	eResult = cFatFile.Read((uint8*)puiFileData2, iLength, &uiBytesRead);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(iLength, uiBytesRead);
	AssertMemory(&(((uint8*)puiFileData)[64 KB + 1024]), puiFileData2, iLength);

	eResult = cFatFile.Close();
	AssertInt(FAT_SUCCESS, eResult);

	iLength = 196 KB;
	eResult = cVolume.FatCreateDirectory("\\A Directory");
	AssertInt(FAT_SUCCESS, eResult);
	eResult = cVolume.FatCreateDirectory("\\A Directory\\Another");
	AssertInt(FAT_SUCCESS, eResult);

	cFatFile.Init(&cVolume);
	eResult = cFatFile.Open("\\A Directory\\Another\\New File Number Two.txt", FAT_FILE_ACCESS_CREATE | FAT_FILE_ACCESS_WRITE);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(0, cFatFile.GetCurrentSize());

	eResult = cFatFile.Write((uint8*)puiFileData, iLength);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(196 KB, cFatFile.GetCurrentSize());

	eResult = cFatFile.Close();
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cVolume.Unmount();
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cVolume.Mount(&cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);

	cFatFile.Init(&cVolume);
	eResult = cFatFile.Open("\\New File.txt", FAT_FILE_ACCESS_READ);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(196 KB, cFatFile.GetCurrentSize());

	memset(puiFileData2, 0, iLength);
	eResult = cFatFile.Read((uint8*)puiFileData2, iLength, &uiBytesRead);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(iLength, uiBytesRead);
	AssertInt(0, memcmp(puiFileData, puiFileData2, iLength));

	eResult = cFatFile.Close();
	AssertInt(FAT_SUCCESS, eResult);


	cFatFile.Init(&cVolume);
	eResult = cFatFile.Open("\\A Directory\\Another\\New File Number Two.txt", FAT_FILE_ACCESS_READ);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(196 KB, cFatFile.GetCurrentSize());

	memset(puiFileData2, 0, iLength);
	eResult = cFatFile.Read((uint8*)puiFileData2, iLength, &uiBytesRead);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(iLength, uiBytesRead);
	AssertInt(0, memcmp(puiFileData, puiFileData2, iLength));

	eResult = cFatFile.Close();
	AssertInt(FAT_SUCCESS, eResult);

	free(puiFileData);
	free(puiFileData2);

	eResult = cVolume.Unmount();
	AssertInt(FAT_SUCCESS, eResult);

	cMemoryDrive.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFat32MultipleSmallReads(void)
{
	CMemoryDrive			cMemoryDrive;
	CDiskFile				cFile;
	filePos					uiLength;
	void*					pvMemory;
	SFatDirectoryEntry		sFatFileEntry;
	EFatCode				eResult;
	CFatFile				cFatFile;
	bool					bResult;
	uint32					uiBytesRead;
	char					auiFileData[44 KB];
	char					auiExpectedData[44 KB];
	CFatVolume				cVolume;
	uint32					uiFileSize;
	uint32					uiBytesToRead;
	uint8*					puiFileData;
	int						i;

	cFile.Init("Input\\Fat32\\ComplexDisk.img");
	bResult = cFile.Open(EFM_Read);
	AssertTrue(bResult);
	uiLength = cFile.Size();
	cMemoryDrive.Init((size_t)uiLength, 512);
	pvMemory = cMemoryDrive.GetMemory();
	cFile.Read(pvMemory, uiLength, 1);
	cFile.Close();
	cFile.Kill();

	eResult = cVolume.Mount(&cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cVolume.GetFileEntry("\\Pico\\LCDBusReader\\src\\SDCard.cpp", &sFatFileEntry);
	AssertInt(FAT_SUCCESS, eResult);

	cFatFile.Init(&cVolume);
	eResult = cFatFile.Open(&sFatFileEntry, FAT_FILE_ACCESS_READ);
	AssertInt(FAT_SUCCESS, eResult);

	uiBytesToRead = 1;
	puiFileData = (uint8*)auiFileData;
	uiFileSize = cFatFile.GetCurrentSize();
	for (i = 0;; i++)
	{
		eResult = cFatFile.Read(puiFileData, uiBytesToRead, &uiBytesRead);
		AssertInt(FAT_SUCCESS, eResult);
		AssertInt(uiBytesToRead, uiBytesRead);

		uiFileSize -= uiBytesToRead;
		if (uiFileSize == 0)
		{
			break;
		}
		puiFileData += uiBytesRead;

		uiBytesToRead++;
		if (uiBytesToRead > uiFileSize)
		{
			uiBytesToRead = uiFileSize;
		}
	}
	auiFileData[44000] = '\0';

	cFatFile.Close();

	cFile.Init("Input\\Fat32\\SDCard.cpp");
	bResult = cFile.Open(EFM_Read);
	AssertTrue(bResult);
	uiLength = cFile.Size();
	AssertInt(44000, (int)uiLength);
	cFile.Read(auiExpectedData, uiLength, 1);
	cFile.Close();
	cFile.Kill();

	AssertMemory(auiExpectedData, auiFileData, (int)uiLength);

	cVolume.Unmount();

	cMemoryDrive.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFat32Seek(void)
{
	CMemoryDrive	cMemoryDrive;
	CDiskFile		cFile;
	filePos			uiLength;
	void*			pvMemory;
	EFatCode		eResult;
	CFatFile		cFatFile;
	bool			bResult;
	CFatVolume		cVolume;
	int				i;

	cFile.Init("Input\\Fat32\\ComplexDisk.img");
	bResult = cFile.Open(EFM_Read);
	AssertTrue(bResult);
	uiLength = cFile.Size();
	cMemoryDrive.Init((size_t)uiLength, 512);
	pvMemory = cMemoryDrive.GetMemory();
	cFile.Read(pvMemory, uiLength, 1);
	cFile.Close();
	cFile.Kill();

	eResult = cVolume.Mount(&cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);

	cFatFile.Init(&cVolume);
	eResult = cFatFile.Open("\\Pico\\LCDBusReader\\src\\SDCard.cpp", FAT_FILE_ACCESS_READ);
	AssertInt(FAT_SUCCESS, eResult);

	bool bAllSuccess = true;
	for (i = 0; i < (int)cFatFile.GetCurrentSize(); i++)
	{
		eResult = cFatFile.Seek(i, FAT_SEEK_START);
		if (eResult != FAT_SUCCESS)
		{
			bAllSuccess = false;
			break;
		}
	}
	AssertTrue(bAllSuccess);

	cFatFile.Close();

	cVolume.Unmount();
	cMemoryDrive.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFat32WriteAndSeek(void)
{
	CMemoryDrive	cMemoryDrive;
	CDiskFile		cFile;
	filePos			uiLength;
	void*			pvMemory;
	EFatCode		eResult;
	CFatFile		cFatFile;
	bool			bResult;
	CFatVolume		cVolume;
	int				i;
	char*			szSource;
	char*			szRead;
	uint32			uiBytesRead;

	szSource = AllocateStringBuffer(196 KB);

	cFile.Init("Input\\Fat32\\ComplexDisk.img");
	bResult = cFile.Open(EFM_Read);
	AssertTrue(bResult);
	uiLength = cFile.Size();
	cMemoryDrive.Init((size_t)uiLength, 512);
	pvMemory = cMemoryDrive.GetMemory();
	cFile.Read(pvMemory, uiLength, 1);
	cFile.Close();
	cFile.Kill();

	eResult = cVolume.Mount(&cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);

	cFatFile.Init(&cVolume);
	eResult = cFatFile.Open("\\File.txt", FAT_FILE_ACCESS_CREATE | FAT_FILE_ACCESS_OVERWRITE | FAT_FILE_ACCESS_WRITE | FAT_FILE_ACCESS_READ);
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cFatFile.Write((uint8*)szSource, 196 KB);
	AssertInt(FAT_SUCCESS, eResult);

	bool bAllSuccess = true;
	for (i = 0; i < (int)cFatFile.GetCurrentSize(); i++)
	{
		eResult = cFatFile.Seek(i, FAT_SEEK_START);
		if (eResult != FAT_SUCCESS)
		{
			bAllSuccess = false;
			break;
		}
	}
	AssertTrue(bAllSuccess);

	szRead = (char*)malloc(196 KB);
	eResult = cFatFile.Seek(0, FAT_SEEK_START);
	AssertInt(FAT_SUCCESS, eResult);
	eResult = cFatFile.Read((uint8*)szRead, 196 KB, &uiBytesRead);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(196 KB, uiBytesRead);
	AssertString(szSource, szRead);

	for (i = 1; i < 32769 + 1024; i += 100)
	{
		eResult = cFatFile.Seek(i, FAT_SEEK_START);
		AssertInt(FAT_SUCCESS, eResult);
		eResult = cFatFile.Read((uint8*)szRead, 196 KB - i, &uiBytesRead);
		AssertInt(FAT_SUCCESS, eResult);
		AssertInt(196 KB - i, uiBytesRead);
		AssertString(&szSource[i], szRead);
	}

	cFatFile.Close();

	free(szRead);
	free(szSource);
	cVolume.Unmount();
	cMemoryDrive.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFat32SeekWriteAndRead1(void)
{
	CMemoryDrive	cMemoryDrive;
	CDiskFile		cFile;
	filePos			uiLength;
	void*			pvMemory;
	EFatCode		eResult;
	CFatFile		cFatFile;
	bool			bResult;
	CFatVolume		cVolume;
	char*			szSource;

	szSource = AllocateStringBuffer(64 KB);

	cFile.Init("Input\\Fat32\\ComplexDisk.img");
	bResult = cFile.Open(EFM_Read);
	AssertTrue(bResult);
	uiLength = cFile.Size();
	cMemoryDrive.Init((size_t)uiLength, 512);
	pvMemory = cMemoryDrive.GetMemory();
	cFile.Read(pvMemory, uiLength, 1);
	cFile.Close();
	cFile.Kill();

	eResult = cVolume.Mount(&cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);

	cFatFile.Init(&cVolume);
	eResult = cFatFile.Open("\\File.txt", FAT_FILE_ACCESS_CREATE | FAT_FILE_ACCESS_OVERWRITE | FAT_FILE_ACCESS_WRITE | FAT_FILE_ACCESS_READ);
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cFatFile.Write((uint8*)szSource, 65538);
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cFatFile.Seek(65535, FAT_SEEK_START);
	eResult = cFatFile.Write((uint8*)szSource, 3);
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cFatFile.Seek(65536, FAT_SEEK_START);
	eResult = cFatFile.Write((uint8*)szSource, 1);
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cFatFile.Close();
	AssertInt(FAT_SUCCESS, eResult);

	cVolume.Unmount();

	cMemoryDrive.Kill();

	free(szSource);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFat32SeekWriteAndRead2(void)
{
	CMemoryDrive	cMemoryDrive;
	CDiskFile		cFile;
	filePos			uiLength;
	void*			pvMemory;
	EFatCode		eResult;
	CFatFile		cFatFile;
	bool			bResult;
	CFatVolume		cVolume;
	int				i;
	char			szThree[4];
	char			c;
	char			szDest[8 KB];
	uint32			uiBytesRead;
	
	cFile.Init("Input\\Fat32\\ComplexDisk.img");
	bResult = cFile.Open(EFM_Read);
	AssertTrue(bResult);
	uiLength = cFile.Size();
	cMemoryDrive.Init((size_t)uiLength, 512);
	pvMemory = cMemoryDrive.GetMemory();
	cFile.Read(pvMemory, uiLength, 1);
	cFile.Close();
	cFile.Kill();

	eResult = cVolume.Mount(&cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);

	cFatFile.Init(&cVolume);
	eResult = cFatFile.Open("\\File.txt", FAT_FILE_ACCESS_CREATE | FAT_FILE_ACCESS_OVERWRITE | FAT_FILE_ACCESS_WRITE | FAT_FILE_ACCESS_READ);
	AssertInt(FAT_SUCCESS, eResult);

	c = 'A';
	for (i = 0; i < 196 KB; i++)
	{
		szThree[0] = szThree[1] = szThree[2] = c;
		c++;
		if (c == 127)
		{
			c = 'A';
		}
		if ((c == ' ') || (c == '\\') || (c == '"'))
		{
			c++;
		}

		eResult = cFatFile.Write((uint8*)szThree, 3);
		AssertInt(FAT_SUCCESS, eResult);

		eResult = cFatFile.Seek(i + 1, FAT_SEEK_START);
		AssertInt(FAT_SUCCESS, eResult);
	}

	memset(szDest, 0, 8 KB);
	eResult = cFatFile.Seek(0, FAT_SEEK_START);
	AssertInt(FAT_SUCCESS, eResult);
	eResult = cFatFile.Read((uint8*)szDest, 8 KB - 1, &uiBytesRead);
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cFatFile.Close();
	AssertInt(FAT_SUCCESS, eResult);

	cVolume.Unmount();

	cMemoryDrive.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFat32SeekWriteAndRead3(void)
{
	CMemoryDrive	cMemoryDrive;
	CDiskFile		cFile;
	filePos			uiLength;
	void*			pvMemory;
	EFatCode		eResult;
	CFatFile		cFatFile;
	bool			bResult;
	CFatVolume		cVolume;
	int				i;
	char			szThree[4];
	char			c;
	char			szDest[8 KB];
	uint32			uiBytesRead;

	cFile.Init("Input\\Fat32\\ComplexDisk.img");
	bResult = cFile.Open(EFM_Read);
	AssertTrue(bResult);
	uiLength = cFile.Size();
	cMemoryDrive.Init((size_t)uiLength, 512);
	pvMemory = cMemoryDrive.GetMemory();
	cFile.Read(pvMemory, uiLength, 1);
	cFile.Close();
	cFile.Kill();

	eResult = cVolume.Mount(&cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);

	cVolume.FatCreateDirectory("\\Directory");

	cFatFile.Init(&cVolume);
	eResult = cFatFile.Open("\\Directory\\File.txt", FAT_FILE_ACCESS_CREATE | FAT_FILE_ACCESS_OVERWRITE | FAT_FILE_ACCESS_WRITE | FAT_FILE_ACCESS_READ);
	AssertInt(FAT_SUCCESS, eResult);
	eResult = cFatFile.Close();
	AssertInt(FAT_SUCCESS, eResult);

	cFatFile.Init(&cVolume);
	eResult = cFatFile.Open("\\Directory\\File.txt", FAT_FILE_ACCESS_WRITE | FAT_FILE_ACCESS_READ);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(cFatFile.GetCurrentSize(), 0);

	c = 'A';
	for (i = 0; i < 196 KB; i++)
	{
		szThree[0] = szThree[1] = szThree[2] = c;
		c++;
		if (c == 127)
		{
			c = 'A';
		}
		if ((c == ' ') || (c == '\\') || (c == '"'))
		{
			c++;
		}

		eResult = cFatFile.Write((uint8*)szThree, 3);
		AssertInt(FAT_SUCCESS, eResult);
		if (i == 65536)
		{
			int xxx = 0;
		}
		eResult = cFatFile.Seek(i + 1, FAT_SEEK_START);
		AssertInt(FAT_SUCCESS, eResult);
	}

	memset(szDest, 0, 8 KB);
	eResult = cFatFile.Seek(0, FAT_SEEK_START);
	AssertInt(FAT_SUCCESS, eResult);
	eResult = cFatFile.Read((uint8*)szDest, 8 KB - 1, &uiBytesRead);
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cFatFile.Close();
	AssertInt(FAT_SUCCESS, eResult);

	cVolume.Unmount();

	cMemoryDrive.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFat32(void)
{
	TypeConverterInit();
	WordsInit();
	BeginTests();

	TestFat32ReadSpecific();
	TestFat32ReadDirectoryTree();
	TestFat32Format();
	TestFat32CreateFileEntries();
	TestFat32OpenWriteMode();
	TestFat32Write();
	TestFat32CreateDirectory();
	TestFat32FormatAndCreateDirectory();
	TestFat32GreatWrite();
	TestFat32MultipleSmallReads();
	TestFat32Seek();
	TestFat32WriteAndSeek();
	TestFat32SeekWriteAndRead1();
	TestFat32SeekWriteAndRead2();
	TestFat32SeekWriteAndRead3();

	TestStatistics();
	WordsKill();
	TypeConverterKill();
}

