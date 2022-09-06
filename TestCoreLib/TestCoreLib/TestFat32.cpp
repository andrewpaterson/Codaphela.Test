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

	SFatDirectoryEntry*	psFatDirectory;
	SFatVolume				sFatVolume;
	SFatFileSystemQuery	sQuery;
	uint16					uiResult;
	SFatFile				sFatFile;
	BOOL					bResult;
	uint32					uiBytesRead;

	char					auiFileData[4 KB];

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
	uiResult = fat_find_first_entry(&sFatVolume, NULL, 0, &psFatDirectory, &sQuery);
	AssertInt(FAT_SUCCESS, uiResult);
	AssertString("Document.txt", (char*)psFatDirectory->name);
	AssertInt(FAT_ATTR_ARCHIVE, psFatDirectory->attributes);

	uiResult = fat_file_open(&sFatVolume, (char*)psFatDirectory->name, 0, &sFatFile);
	AssertInt(FAT_SUCCESS, uiResult);

	uiResult = fat_file_read(&sFatFile, (uint8*)auiFileData, sFatFile.current_size, &uiBytesRead);
	AssertInt(FAT_SUCCESS, uiResult);
	AssertInt(12, uiBytesRead);
	auiFileData[12] = '\0';
	AssertString("Mostly Empty", auiFileData);

	uiResult = fat_file_close(&sFatFile);
	AssertInt(FAT_SUCCESS, uiResult);

	uiResult = fat_find_next_entry(&sFatVolume, &psFatDirectory, &sQuery);
	AssertInt(FAT_SUCCESS, uiResult);
	AssertString("Pico", (char*)psFatDirectory->name);
	AssertInt(FAT_ATTR_DIRECTORY, psFatDirectory->attributes);

	uiResult = fat_find_next_entry(&sFatVolume, &psFatDirectory, &sQuery);
	AssertTrue((StrEmpty((char*)psFatDirectory->name)));

	memset(&sQuery, 0, sizeof(SFatFileSystemQuery));
	uiResult = fat_find_first_entry(&sFatVolume, "\\Pico", 0, &psFatDirectory, &sQuery);
	AssertInt(FAT_SUCCESS, uiResult);
	AssertString(".", (char*)psFatDirectory->name);
	AssertInt(FAT_ATTR_DIRECTORY, psFatDirectory->attributes);

	uiResult = fat_find_next_entry(&sFatVolume, &psFatDirectory, &sQuery);
	AssertInt(FAT_SUCCESS, uiResult);
	AssertString("..", (char*)psFatDirectory->name);
	AssertInt(FAT_ATTR_DIRECTORY, psFatDirectory->attributes);

	uiResult = fat_find_next_entry(&sFatVolume, &psFatDirectory, &sQuery);
	AssertInt(FAT_SUCCESS, uiResult);
	AssertString(".gitignore", (char*)psFatDirectory->name);
	AssertInt(FAT_ATTR_ARCHIVE, psFatDirectory->attributes);

	uiResult = fat_find_next_entry(&sFatVolume, &psFatDirectory, &sQuery);
	AssertInt(FAT_SUCCESS, uiResult);
	AssertString("HowDoesItWork", (char*)psFatDirectory->name);
	AssertInt(FAT_ATTR_DIRECTORY, psFatDirectory->attributes);

	uiResult = fat_find_next_entry(&sFatVolume, &psFatDirectory, &sQuery);
	AssertInt(FAT_SUCCESS, uiResult);
	AssertString("LCDBusReader", (char*)psFatDirectory->name);
	AssertInt(FAT_ATTR_DIRECTORY, psFatDirectory->attributes);

	uiResult = fat_find_next_entry(&sFatVolume, &psFatDirectory, &sQuery);
	AssertTrue((StrEmpty((char*)psFatDirectory->name)));

	fat_unmount_volume(&sFatVolume);

	cMemoryDrive.Kill();

	TestStatistics();
	TypeConverterKill();
}

