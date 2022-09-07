#include "BaseLib/FastFunctions.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/RedirectPrintf.h"
#include "BaseLib/DiskFile.h"
#include "BaseLib/IntegerHelper.h"
#include "BaseLib/StringHelper.h"
#include "BaseLib/ArrayChars.h"
#include "CoreLib/MemoryDrive.h"
#include "CoreLib/Fat.h"
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
	SFatVolume				sFatVolume;
	SFatFileSystemQuery		sQuery;
	uint16					uiResult;
	SFatFile				sFatFile;
	BOOL					bResult;
	uint32					uiBytesRead;
	char					auiFileData[44 KB];
	char					auiExpectedData[44 KB];

	cFile.Init("Input\\Fat32\\ComplexDisk.img");
	bResult = cFile.Open(EFM_Read);
	AssertTrue(bResult);
	uiLength = cFile.Size();
	cMemoryDrive.Init((size_t)uiLength, 512);
	pvMemory = cMemoryDrive.GetMemory();
	cFile.Read(pvMemory, uiLength, 1);
	cFile.Close();
	cFile.Kill();

	fat_init();

	uiResult = fat_mount_volume(&sFatVolume, &cMemoryDrive);
	AssertInt(STORAGE_SUCCESS, uiResult);

	memset(&sQuery, 0, sizeof(SFatFileSystemQuery));
	uiResult = fat_find_first_entry(&sFatVolume, NULL, 0, &psFatDirectoryEntry, &sQuery);
	AssertInt(FAT_SUCCESS, uiResult);
	AssertString("Document.txt", (char*)psFatDirectoryEntry->name);
	AssertInt(FAT_ATTR_ARCHIVE, psFatDirectoryEntry->attributes);

	memset(&sFatFile, 0, sizeof(SFatFile));
	uiResult = fat_file_open(&sFatVolume, (char*)psFatDirectoryEntry->name, 0, &sFatFile);
	AssertInt(FAT_SUCCESS, uiResult);

	uiResult = fat_file_read(&sFatFile, (uint8*)auiFileData, sFatFile.current_size, &uiBytesRead);
	AssertInt(FAT_SUCCESS, uiResult);
	AssertInt(12, uiBytesRead);
	auiFileData[12] = '\0';
	AssertString("Mostly Empty", auiFileData);

	uiResult = fat_file_close(&sFatFile);
	AssertInt(FAT_SUCCESS, uiResult);

	uiResult = fat_find_next_entry(&sFatVolume, &psFatDirectoryEntry, &sQuery);
	AssertInt(FAT_SUCCESS, uiResult);
	AssertString("Pico", (char*)psFatDirectoryEntry->name);
	AssertInt(FAT_ATTR_DIRECTORY, psFatDirectoryEntry->attributes);

	uiResult = fat_find_next_entry(&sFatVolume, &psFatDirectoryEntry, &sQuery);
	AssertTrue((StrEmpty((char*)psFatDirectoryEntry->name)));


	memset(&sQuery, 0, sizeof(SFatFileSystemQuery));
	uiResult = fat_find_first_entry(&sFatVolume, "\\Pico", 0, &psFatDirectoryEntry, &sQuery);
	AssertInt(FAT_SUCCESS, uiResult);
	AssertString(".", (char*)psFatDirectoryEntry->name);
	AssertInt(FAT_ATTR_DIRECTORY, psFatDirectoryEntry->attributes);

	uiResult = fat_find_next_entry(&sFatVolume, &psFatDirectoryEntry, &sQuery);
	AssertInt(FAT_SUCCESS, uiResult);
	AssertString("..", (char*)psFatDirectoryEntry->name);
	AssertInt(FAT_ATTR_DIRECTORY, psFatDirectoryEntry->attributes);

	uiResult = fat_find_next_entry(&sFatVolume, &psFatDirectoryEntry, &sQuery);
	AssertInt(FAT_SUCCESS, uiResult);
	AssertString(".gitignore", (char*)psFatDirectoryEntry->name);
	AssertInt(FAT_ATTR_ARCHIVE, psFatDirectoryEntry->attributes);

	uiResult = fat_find_next_entry(&sFatVolume, &psFatDirectoryEntry, &sQuery);
	AssertInt(FAT_SUCCESS, uiResult);
	AssertString("HowDoesItWork", (char*)psFatDirectoryEntry->name);
	AssertInt(FAT_ATTR_DIRECTORY, psFatDirectoryEntry->attributes);

	uiResult = fat_find_next_entry(&sFatVolume, &psFatDirectoryEntry, &sQuery);
	AssertInt(FAT_SUCCESS, uiResult);
	AssertString("LCDBusReader", (char*)psFatDirectoryEntry->name);
	AssertInt(FAT_ATTR_DIRECTORY, psFatDirectoryEntry->attributes);

	uiResult = fat_find_next_entry(&sFatVolume, &psFatDirectoryEntry, &sQuery);
	AssertTrue((StrEmpty((char*)psFatDirectoryEntry->name)));


	uiResult = fat_get_file_entry(&sFatVolume, "\\Pico\\LCDBusReader\\src\\SDCard.cpp", &sFatFileEntry);
	AssertInt(FAT_SUCCESS, uiResult);
	AssertString("SDCARD.CPP", (char*)sFatFileEntry.name);
	AssertInt(FAT_ATTR_ARCHIVE, sFatFileEntry.attributes);

	memset(&sFatFile, 0, sizeof(SFatFile));
	sFatFile.buffer = sFatFile.buffer_internal;
	uiResult = fat_open_file_by_entry(&sFatVolume, &sFatFileEntry, &sFatFile, FAT_FILE_ACCESS_READ);
	AssertInt(FAT_SUCCESS, uiResult);

	uiResult = fat_file_read(&sFatFile, (uint8*)auiFileData, sFatFile.current_size, &uiBytesRead);
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

	fat_unmount_volume(&sFatVolume);

	cMemoryDrive.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void RecurseFindFatFilenames(SFatVolume* psFatVolume, char* szPath, CArrayChars* paszFiles)
{
	SFatFileSystemQuery		sQuery;
	SFatDirectoryEntry*		psFatDirectoryEntry;
	uint16					uiResult;
	char					szNewPath[FAT_MAX_PATH];

	memset(&sQuery, 0, sizeof(SFatFileSystemQuery));
	uiResult = fat_find_first_entry(psFatVolume, szPath, 0, &psFatDirectoryEntry, &sQuery);
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
				RecurseFindFatFilenames(psFatVolume, szNewPath, paszFiles);
			}
		}

		if (FixBool(psFatDirectoryEntry->attributes & FAT_ATTR_ARCHIVE))
		{
			paszFiles->Add(szNewPath);
		}

		uiResult = fat_find_next_entry(psFatVolume, &psFatDirectoryEntry, &sQuery);
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
	SFatVolume				sFatVolume;
	uint16					uiResult;
	BOOL					bResult;
	CArrayChars				aszFileNames;
	CChars					sz;
	int						i;
	char*					szFileName;
	SFatDirectoryEntry		sFatFileEntry;
	char					auiFileData[44 KB];
	SFatFile				sFatFile;
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

	fat_init();

	uiResult = fat_mount_volume(&sFatVolume, &cMemoryDrive);
	AssertInt(STORAGE_SUCCESS, uiResult);

	aszFileNames.Init();
	RecurseFindFatFilenames(&sFatVolume, "", &aszFileNames);

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
		uiResult = fat_get_file_entry(&sFatVolume, szFileName, &sFatFileEntry);
		AssertInt(FAT_SUCCESS, uiResult);

		memset(&sFatFile, 0, sizeof(SFatFile));
		uiResult = fat_file_open(&sFatVolume, szFileName, 0, &sFatFile);
		AssertInt(FAT_SUCCESS, uiResult);

		uiResult = fat_file_read(&sFatFile, (uint8*)auiFileData, sFatFile.current_size, &uiBytesRead);
		AssertInt(FAT_SUCCESS, uiResult);
		AssertInt(sFatFile.current_size, uiBytesRead);
		AssertInt(sFatFileEntry.size, uiBytesRead);

		uiResult = fat_file_close(&sFatFile);
		AssertInt(FAT_SUCCESS, uiResult);
	}

	aszFileNames.Kill();

	fat_unmount_volume(&sFatVolume);

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

	TestStatistics();
	TypeConverterKill();
}

