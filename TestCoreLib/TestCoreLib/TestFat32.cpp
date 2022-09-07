#include "BaseLib/FastFunctions.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/RedirectPrintf.h"
#include "BaseLib/DiskFile.h"
#include "BaseLib/StringHelper.h"
#include "CoreLib/MemoryDrive.h"
#include "CoreLib/Fat.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFat32(void)
{
	TypeConverterInit();
	BeginTests();

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

	TestStatistics();
	TypeConverterKill();
}

