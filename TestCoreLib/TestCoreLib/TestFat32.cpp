#include "BaseLib/FastFunctions.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/RedirectPrintf.h"
#include "BaseLib/DiskFile.h"
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

	CMemoryDrive	cMemoryDrive;
	uint16			c;
	CDiskFile		cFile;
	filePos			uiLength;
	void*			pvMemory;

	FAT_DIRECTORY_ENTRY*	psFatDirectory;
	FAT_VOLUME				sFatVolume;
	FAT_FILESYSTEM_QUERY	sQuery;
	uint16					uiResult;

	cFile.Init("D:\\Work\\658-Computer\\SD Card Image\\SDCardFat32.img");
	cFile.Open(EFM_Read);
	uiLength = cFile.Size();
	cMemoryDrive.Init((size_t)uiLength, 512);
	pvMemory = cMemoryDrive.GetMemory();
	cFile.Read(pvMemory, uiLength, 1);
	cFile.Close();
	cFile.Kill();

	fat_init();

	if ((c = fat_mount_volume(&sFatVolume, &cMemoryDrive)) == STORAGE_SUCCESS)
	{
		eprintf("Volume '%s' mounted.\n\n", sFatVolume.label);
	}
	else
	{
		eprintf("Could not mount volume. Error: %x\n\n", c);
	}

	memset(&sQuery, 0, sizeof(FAT_FILESYSTEM_QUERY));
	uiResult = fat_find_first_entry(&sFatVolume, NULL, 0, &psFatDirectory, &sQuery);

	uiResult = fat_find_next_entry(&sFatVolume, &psFatDirectory, &sQuery);
	uiResult = fat_find_next_entry(&sFatVolume, &psFatDirectory, &sQuery);
	uiResult = fat_find_next_entry(&sFatVolume, &psFatDirectory, &sQuery);

	fat_dismount_volume(&sFatVolume);

	cMemoryDrive.Kill();
//	TestMain("D:\\Temp\\SDCardFat32.img", "-d");

	TestStatistics();
	TypeConverterKill();
}

