#include "BaseLib/FastFunctions.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/RedirectPrintf.h"
#include "BaseLib/DiskFile.h"
#include "BaseLib/IntegerHelper.h"
#include "BaseLib/StringHelper.h"
#include "BaseLib/ArrayChars.h"
#include "CoreLib/MemoryDrive.h"
#include "CoreLib/Fat32.h"
#include "TestLib/Assert.h"


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
	uint16					uiResult;
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

	uiResult = cVolume.Mount(&cMemoryDrive);
	AssertInt(STORAGE_SUCCESS, uiResult);

	memset(&sQuery, 0, sizeof(SFatFileSystemQuery));
	uiResult = cVolume.FatFindFirstEntry(NULL, 0, &psFatDirectoryEntry, &sQuery);
	AssertInt(FAT_SUCCESS, uiResult);
	AssertString("Document.txt", (char*)psFatDirectoryEntry->name);
	AssertInt(FAT_ATTR_ARCHIVE, psFatDirectoryEntry->attributes);

	cFatFile.Init(&cVolume);
	uiResult = cFatFile.FatFileOpen(&cVolume, (char*)psFatDirectoryEntry->name, 0);
	AssertInt(FAT_SUCCESS, uiResult);

	uiResult = cFatFile.FatFileRead((uint8*)auiFileData, cFatFile.GetCurrentSize(), &uiBytesRead);
	AssertInt(FAT_SUCCESS, uiResult);
	AssertInt(12, uiBytesRead);
	auiFileData[12] = '\0';
	AssertString("Mostly Empty", auiFileData);

	uiResult = cFatFile.FatFileClose();
	AssertInt(FAT_SUCCESS, uiResult);

	uiResult = cVolume.FatFindNextEntry(&psFatDirectoryEntry, &sQuery);
	AssertInt(FAT_SUCCESS, uiResult);
	AssertString("Pico", (char*)psFatDirectoryEntry->name);
	AssertInt(FAT_ATTR_DIRECTORY, psFatDirectoryEntry->attributes);

	uiResult = cVolume.FatFindNextEntry(&psFatDirectoryEntry, &sQuery);
	AssertTrue((StrEmpty((char*)psFatDirectoryEntry->name)));


	memset(&sQuery, 0, sizeof(SFatFileSystemQuery));
	uiResult = cVolume.FatFindFirstEntry("\\Pico", 0, &psFatDirectoryEntry, &sQuery);
	AssertInt(FAT_SUCCESS, uiResult);
	AssertString(".", (char*)psFatDirectoryEntry->name);
	AssertInt(FAT_ATTR_DIRECTORY, psFatDirectoryEntry->attributes);

	uiResult = cVolume.FatFindNextEntry(&psFatDirectoryEntry, &sQuery);
	AssertInt(FAT_SUCCESS, uiResult);
	AssertString("..", (char*)psFatDirectoryEntry->name);
	AssertInt(FAT_ATTR_DIRECTORY, psFatDirectoryEntry->attributes);

	uiResult = cVolume.FatFindNextEntry(&psFatDirectoryEntry, &sQuery);
	AssertInt(FAT_SUCCESS, uiResult);
	AssertString(".gitignore", (char*)psFatDirectoryEntry->name);
	AssertInt(FAT_ATTR_ARCHIVE, psFatDirectoryEntry->attributes);

	uiResult = cVolume.FatFindNextEntry(&psFatDirectoryEntry, &sQuery);
	AssertInt(FAT_SUCCESS, uiResult);
	AssertString("HowDoesItWork", (char*)psFatDirectoryEntry->name);
	AssertInt(FAT_ATTR_DIRECTORY, psFatDirectoryEntry->attributes);

	uiResult = cVolume.FatFindNextEntry(&psFatDirectoryEntry, &sQuery);
	AssertInt(FAT_SUCCESS, uiResult);
	AssertString("LCDBusReader", (char*)psFatDirectoryEntry->name);
	AssertInt(FAT_ATTR_DIRECTORY, psFatDirectoryEntry->attributes);

	uiResult = cVolume.FatFindNextEntry(&psFatDirectoryEntry, &sQuery);
	AssertTrue((StrEmpty((char*)psFatDirectoryEntry->name)));


	uiResult = cVolume.FatGetFileEntry("\\Pico\\LCDBusReader\\src\\SDCard.cpp", &sFatFileEntry);
	AssertInt(FAT_SUCCESS, uiResult);
	AssertString("SDCARD.CPP", (char*)sFatFileEntry.name);
	AssertInt(FAT_ATTR_ARCHIVE, sFatFileEntry.attributes);

	cFatFile.Init(&cVolume);
	uiResult = cFatFile.FatOpenFileByEntry(&cVolume, &sFatFileEntry, FAT_FILE_ACCESS_READ);
	AssertInt(FAT_SUCCESS, uiResult);

	uiResult = cFatFile.FatFileRead((uint8*)auiFileData, cFatFile.GetCurrentSize(), &uiBytesRead);
	AssertInt(FAT_SUCCESS, uiResult);
	AssertInt(44000, uiBytesRead);
	auiFileData[44000] = '\0';

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
void RecurseFindFatFilenames(CFatVolume* pcVolume, char* szPath, CArrayChars* paszFiles)
{
	SFatFileSystemQuery		sQuery;
	SFatDirectoryEntry*		psFatDirectoryEntry;
	uint16					uiResult;
	char					szNewPath[FAT_MAX_PATH];

	memset(&sQuery, 0, sizeof(SFatFileSystemQuery));
	uiResult = pcVolume->FatFindFirstEntry(szPath, 0, &psFatDirectoryEntry, &sQuery);
	for (;;)
	{
		if ((uiResult != FAT_SUCCESS) || (StrEmpty((char*)psFatDirectoryEntry->name)))
		{
			break;
		}

		memset(szNewPath, 0, FAT_MAX_PATH);
		strcpy(szNewPath, szPath);
		strcat(szNewPath, "\\");
		strcat(szNewPath, (char*)psFatDirectoryEntry->name);

		if (FixBool(psFatDirectoryEntry->attributes & FAT_ATTR_DIRECTORY))
		{
			if (!((strcmp((char*)psFatDirectoryEntry->name, ".") == 0) || (strcmp((char*)psFatDirectoryEntry->name, "..") == 0)))
			{
				RecurseFindFatFilenames(pcVolume, szNewPath, paszFiles);
			}
		}

		if (FixBool(psFatDirectoryEntry->attributes & FAT_ATTR_ARCHIVE))
		{
			paszFiles->Add(szNewPath);
		}

		uiResult = pcVolume->FatFindNextEntry(&psFatDirectoryEntry, &sQuery);
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void RecurseFindFatDirectories(CFatVolume* pcVolume, char* szPath, CArrayChars* paszDirectories)
{
	SFatFileSystemQuery		sQuery;
	SFatDirectoryEntry*		psFatDirectoryEntry;
	uint16					uiResult;
	char					szNewPath[FAT_MAX_PATH];

	memset(&sQuery, 0, sizeof(SFatFileSystemQuery));
	uiResult = pcVolume->FatFindFirstEntry(szPath, 0, &psFatDirectoryEntry, &sQuery);
	for (;;)
	{
		if ((uiResult != FAT_SUCCESS) || (StrEmpty((char*)psFatDirectoryEntry->name)))
		{
			break;
		}

		memset(szNewPath, 0, FAT_MAX_PATH);
		strcpy(szNewPath, szPath);
		strcat(szNewPath, "\\");
		strcat(szNewPath, (char*)psFatDirectoryEntry->name);

		if (FixBool(psFatDirectoryEntry->attributes & FAT_ATTR_DIRECTORY))
		{
			if (!((strcmp((char*)psFatDirectoryEntry->name, ".") == 0) || (strcmp((char*)psFatDirectoryEntry->name, "..") == 0)))
			{
				RecurseFindFatDirectories(pcVolume, szNewPath, paszDirectories);
				paszDirectories->Add(szNewPath);
			}
		}

		uiResult = pcVolume->FatFindNextEntry(&psFatDirectoryEntry, &sQuery);
	}
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
	uint16					uiResult;
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

	uiResult = cVolume.Mount(&cMemoryDrive);
	AssertInt(STORAGE_SUCCESS, uiResult);

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
		uiResult = cVolume.FatGetFileEntry(szFileName, &sFatFileEntry);
		AssertInt(FAT_SUCCESS, uiResult);

		cFatFile.Init(&cVolume);
		uiResult = cFatFile.FatFileOpen(&cVolume, szFileName, 0);
		AssertInt(FAT_SUCCESS, uiResult);

		uiResult = cFatFile.FatFileRead((uint8*)auiFileData, cFatFile.GetCurrentSize(), &uiBytesRead);
		AssertInt(FAT_SUCCESS, uiResult);
		AssertInt(cFatFile.GetCurrentSize(), uiBytesRead);
		AssertInt(sFatFileEntry.size, uiBytesRead);

		uiResult = cFatFile.FatFileClose();
		AssertInt(FAT_SUCCESS, uiResult);
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
	uint16					uiResult;
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

	uiResult = FatFormat(FAT_FS_TYPE_FAT32, "Fat32", 1, &cMemoryDrive);
	AssertInt(STORAGE_SUCCESS, uiResult);

	uiResult = cVolume.Mount(&cMemoryDrive);
	AssertInt(STORAGE_SUCCESS, uiResult);

	memset(&sQuery, 0, sizeof(SFatFileSystemQuery));
	uiResult = cVolume.FatFindFirstEntry(NULL, 0, &psFatDirectoryEntry, &sQuery);
	AssertInt(FAT_SUCCESS, uiResult);
	AssertString("", (char*)psFatDirectoryEntry->name);
	AssertInt(0, psFatDirectoryEntry->attributes);

	uiResult = cVolume.Unmount();
	AssertInt(STORAGE_SUCCESS, uiResult);

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
	uint16					uiResult;
	bool					bResult;
	SFatDirectoryEntry*		psFatDirectoryEntry;
	SFatFileSystemQuery		sQuery;
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

	uiResult = cVolume.Mount(&cMemoryDrive);
	AssertInt(STORAGE_SUCCESS, uiResult);

	cFatFile.Init(&cVolume);
	uiResult = cFatFile.FatFileOpen(&cVolume, "\\New File.txt", FAT_FILE_ACCESS_CREATE | FAT_FILE_ACCESS_WRITE);
	AssertInt(FAT_SUCCESS, uiResult);
	AssertInt(0, cFatFile.GetCurrentSize());

	memset(&sQuery, 0, sizeof(SFatFileSystemQuery));
	uiResult = cVolume.FatFindFirstEntry(NULL, 0, &psFatDirectoryEntry, &sQuery);
	AssertInt(FAT_SUCCESS, uiResult);
	AssertString("New File.txt", (char*)psFatDirectoryEntry->name);
	AssertInt(0, psFatDirectoryEntry->attributes);

	for (i = 0; i < 4 KB; i++)
	{
		auiFileData[i] = (char)i;
	}

	uiResult = cFatFile.FatFileWrite((uint8*)auiFileData, 4 KB);
	AssertInt(FAT_SUCCESS, uiResult);
	AssertInt(4096, cFatFile.GetCurrentSize());

	uiResult = cFatFile.FatFileClose();
	AssertInt(FAT_SUCCESS, uiResult);

	uiResult = cVolume.Unmount();
	AssertInt(STORAGE_SUCCESS, uiResult);

	uiResult = cVolume.Mount(&cMemoryDrive);
	AssertInt(STORAGE_SUCCESS, uiResult);

	cFatFile.Init(&cVolume);
	uiResult = cFatFile.FatFileOpen(&cVolume, "\\New File.txt", FAT_FILE_ACCESS_READ);
	AssertInt(FAT_SUCCESS, uiResult);
	AssertInt(4096, cFatFile.GetCurrentSize());

	uiResult = cFatFile.FatFileRead((uint8*)auiFileData2, 4 KB, &uiBytesRead);
	AssertInt(FAT_SUCCESS, uiResult);
	AssertInt(0, memcmp(auiFileData, auiFileData2, 4 KB));

	uiResult = cFatFile.FatFileClose();
	AssertInt(FAT_SUCCESS, uiResult);

	uiResult = cVolume.Unmount();
	AssertInt(STORAGE_SUCCESS, uiResult);

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
	uint16			uiResult;
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

	uiResult = cVolume.Mount(&cMemoryDrive);
	AssertInt(STORAGE_SUCCESS, uiResult);

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
	
	uiResult = cVolume.Unmount();
	AssertInt(STORAGE_SUCCESS, uiResult);

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
	uint16			uiResult;
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

	uiResult = FatFormat(FAT_FS_TYPE_FAT32, "Fat32", 1, &cMemoryDrive);
	AssertInt(STORAGE_SUCCESS, uiResult);

	uiResult = cVolume.Mount(&cMemoryDrive);
	AssertInt(STORAGE_SUCCESS, uiResult);

	uiResult = cVolume.FatCreateDirectory("\\A Directory");
	AssertInt(FAT_SUCCESS, uiResult);
	uiResult = cVolume.FatCreateDirectory("\\A Directory\\Another");
	AssertInt(FAT_SUCCESS, uiResult);

	aszDirectories.Init();
	RecurseFindFatDirectories(&cVolume, "", &aszDirectories);

	sz.Init();
	aszDirectories.Print(&sz);
	aszDirectories.Kill();
	AssertString("\
\\A Directory\\Another\n\
\\A Directory\n", sz.Text());
	sz.Kill();

	uiResult = cVolume.Unmount();
	AssertInt(STORAGE_SUCCESS, uiResult);

	cMemoryDrive.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFat32(void)
{
	TypeConverterInit();
	BeginTests();

	TestFat32ReadSpecific();
	TestFat32ReadDirectoryTree();
	TestFat32Format();
	TestFat32Write();
	TestFat32CreateDirectory();
	TestFat32FormatAndCreateDirectory();

	TestStatistics();
	TypeConverterKill();
}

