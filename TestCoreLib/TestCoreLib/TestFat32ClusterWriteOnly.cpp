#include "BaseLib/FastFunctions.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/RedirectPrintf.h"
#include "BaseLib/DiskFile.h"
#include "BaseLib/IntegerHelper.h"
#include "BaseLib/StringHelper.h"
#include "BaseLib/ArrayChars.h"
#include "CoreLib/MemoryDrive.h"
#include "CoreLib/Fat32.h"
#include "CoreLib/FatDebug.h"
#include "TestLib/Assert.h"
#include "TestFat32Common.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFat32WriteLargerThanOneClusterAppend(void)
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
	char*			szRead;
	uint32			uiBytesRead;
	uint64			uiMaxSectorSize;
	CChars			sz;

	szSource = AllocateStringBuffer(33 KB);

	cFile.Init("Input\\Fat32\\ComplexDisk.img");
	bResult = cFile.Open(EFM_Read);
	AssertTrue(bResult);
	uiLength = cFile.Size();
	cMemoryDrive.Init((size_t)uiLength, 512);
	pvMemory = cMemoryDrive.GetMemory();
	cFile.Read(pvMemory, uiLength, 1);
	cFile.Close();
	cFile.Kill();

	cMemoryDrive.Erase();
	uiMaxSectorSize = cMemoryDrive.SetMaxSectorForTesting(((16 MB) / 512) * 1024);

	eResult = FatFormat(FAT_FS_TYPE_FAT32, "Fat32", 64, &cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);

	cMemoryDrive.SetMaxSectorForTesting(uiMaxSectorSize);

	szRead = (char*)malloc(32769);

	eResult = cVolume.Mount(&cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);

	cFatFile.Init(&cVolume);
	eResult = cFatFile.Open("\\File1.txt", FAT_FILE_ACCESS_CREATE | FAT_FILE_ACCESS_OVERWRITE | FAT_FILE_ACCESS_WRITE | FAT_FILE_ACCESS_READ);
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cFatFile.Write((uint8*)szSource, 32769);
	AssertInt(FAT_SUCCESS, eResult);

	cFatFile.Close();

	cFatFile.Init(&cVolume);
	eResult = cFatFile.Open("\\File1.txt", FAT_FILE_ACCESS_READ);
	AssertInt(FAT_SUCCESS, eResult);
	memset(szRead, 0xcc, 32769);
	eResult = cFatFile.Read((uint8*)szRead, 32769, &uiBytesRead);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(32769, uiBytesRead);
	AssertMemory(szSource, szRead, 32769);
	eResult = cFatFile.Close();
	AssertInt(FAT_SUCCESS, eResult);

	cFatFile.Init(&cVolume);
	eResult = cFatFile.Open("\\File2.txt", FAT_FILE_ACCESS_CREATE | FAT_FILE_ACCESS_OVERWRITE | FAT_FILE_ACCESS_WRITE | FAT_FILE_ACCESS_READ);
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cFatFile.Write((uint8*)szSource, 32768);
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cFatFile.Write((uint8*)(&szSource[32768]), 1);
	AssertInt(FAT_SUCCESS, eResult);
	
	sz.Init();
	PrintRootDirectoryEntries(&sz, &cVolume, false);
	AssertStringApproximate("\
---------------------------------------\n\
Short name: Fat32\n\
Cluster:    0\n\
Size:       0\n\
Attributes: VOLUME_ID\n\
---------------------------------------\n\
Sequence:     65\n\
Long name[1]: File1\n\
Long name[2]: .txt\n\
Long name[3]: ÿÿ\n\
Cluster:      0\n\
Attributes:   LONG_NAME\n\
Checksum:     225\n\
---------------------------------------\n\
Short name: FILE1~0.TXT\n\
Cluster:    4\n\
Size:       32769\n\
Attributes: ARCHIVE\n\
---------------------------------------\n\
Sequence:     65\n\
Long name[1]: File2\n\
Long name[2]: .txt\n\
Long name[3]: ÿÿ\n\
Cluster:      0\n\
Attributes:   LONG_NAME\n\
Checksum:     221\n\
---------------------------------------\n\
Short name: FILE2~0.TXT\n\
Cluster:    6\n\
Size:       0\n\
Attributes: ARCHIVE\n", sz.Text());
	sz.Kill();

	sz.Init();
	PrintFATClusters(&sz, &cVolume, 0, 0x10);
	AssertString("\
-------------------------------------------------------------------- Sector (32) --------------------------------------------------------------------\n\
    0 -> FFF8,     1 ->  EOC,     2 ->    0,     3 ->  EOC,     4 ->    5,     5 ->  EOC,     6 ->    7,     7 ->  EOC,     8 ->    0,     9 ->    0,     a ->    0,     b ->    0,     c ->    0,     d ->    0,     e ->    0,     f ->    0\n", sz.Text());
	sz.Kill();

	eResult = cFatFile.Close();
	AssertInt(FAT_SUCCESS, eResult);

	sz.Init();
	PrintRootDirectoryEntries(&sz, &cVolume, false);
	AssertStringApproximate("\
---------------------------------------\n\
Short name: Fat32\n\
Cluster:    0\n\
Size:       0\n\
Attributes: VOLUME_ID\n\
--------------------------------------- \n\
Sequence:     65\n\
Long name[1]: File1\n\
Long name[2]: .txt\n\
Long name[3]: ÿÿ\n\
Cluster:      0\n\
Attributes:   LONG_NAME\n\
Checksum:     225\n\
--------------------------------------- \n\
Short name: FILE1~0.TXT\n\
Cluster:    4\n\
Size:       32769\n\
Attributes: ARCHIVE\n\
--------------------------------------- \n\
Sequence:     65\n\
Long name[1]: File2\n\
Long name[2]: .txt\n\
Long name[3]: ÿÿ\n\
Cluster:      0\n\
Attributes:   LONG_NAME\n\
Checksum:     221\n\
---------------------------------------\n\
Short name: FILE2~0.TXT\n\
Cluster:    6\n\
Size:       32769\n\
Attributes: ARCHIVE\n", sz.Text());
	sz.Kill();

	sz.Init();
	PrintFATClusters(&sz, &cVolume, 0, 0x10);
	AssertString("\
-------------------------------------------------------------------- Sector (32) --------------------------------------------------------------------\n\
    0 -> FFF8,     1 ->  EOC,     2 ->    0,     3 ->  EOC,     4 ->    5,     5 ->  EOC,     6 ->    7,     7 ->  EOC,     8 ->    0,     9 ->    0,     a ->    0,     b ->    0,     c ->    0,     d ->    0,     e ->    0,     f ->    0\n", sz.Text());
	sz.Kill();

	cFatFile.Init(&cVolume);
	eResult = cFatFile.Open("\\File2.txt", FAT_FILE_ACCESS_READ);
	AssertInt(FAT_SUCCESS, eResult);
	memset(szRead, 0xcc, 32769);
	eResult = cFatFile.Read((uint8*)szRead, 32769, &uiBytesRead);
	AssertInt(FAT_SUCCESS, eResult);
	AssertMemory(szSource, szRead, 32769);
	eResult = cFatFile.Close();
	AssertInt(FAT_SUCCESS, eResult);

	cVolume.Unmount();

	cMemoryDrive.Kill();

	free(szRead);
	free(szSource);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFat32WriteLargerThanOneClusterOverwrite(void)
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
	char*			szRead;
	uint32			uiBytesRead;
	uint64			uiMaxSectorSize;
	int				i;
	bool			bAllSuccessful;

	szSource = AllocateStringBuffer(33 KB);

	cFile.Init("Input\\Fat32\\ComplexDisk.img");
	bResult = cFile.Open(EFM_Read);
	AssertTrue(bResult);
	uiLength = cFile.Size();
	cMemoryDrive.Init((size_t)uiLength, 512);
	pvMemory = cMemoryDrive.GetMemory();
	cFile.Read(pvMemory, uiLength, 1);
	cFile.Close();
	cFile.Kill();

	cMemoryDrive.Erase();
	uiMaxSectorSize = cMemoryDrive.SetMaxSectorForTesting(((16 MB) / 512) * 1024);

	eResult = FatFormat(FAT_FS_TYPE_FAT32, "Fat32", 64, &cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);

	cMemoryDrive.SetMaxSectorForTesting(uiMaxSectorSize);

	szRead = (char*)malloc(32769);

	eResult = cVolume.Mount(&cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);

	cFatFile.Init(&cVolume);
	eResult = cFatFile.Open("\\File1.txt", FAT_FILE_ACCESS_CREATE | FAT_FILE_ACCESS_OVERWRITE | FAT_FILE_ACCESS_WRITE | FAT_FILE_ACCESS_READ);
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cFatFile.Write((uint8*)szSource, 32768);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(32768, cFatFile.Size());

	eResult = cFatFile.Seek(32767, FAT_SEEK_START);
	AssertInt(FAT_SUCCESS, eResult);
	eResult = cFatFile.Write((uint8*)&szSource[32767], 2);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(32769, cFatFile.Size());

	cFatFile.Seek(0, FAT_SEEK_START);
	eResult = cFatFile.Read((uint8*)szRead, 32769, &uiBytesRead);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(32769, uiBytesRead);
	AssertMemory(szSource, szRead, uiBytesRead);

	eResult = cFatFile.Write((uint8*)szSource, 32768 + 64);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(65601, cFatFile.Size());

	bAllSuccessful = true;
	for (i = 32768; i >= 0; i--)
	{
		eResult = cFatFile.Seek(i, FAT_SEEK_START);
		if (eResult != FAT_SUCCESS)
		{
			AssertInt(FAT_SUCCESS, eResult);
			bAllSuccessful = false;
			break;
		}

		eResult = cFatFile.Read((uint8*)szRead, 1, &uiBytesRead);
		if (eResult != FAT_SUCCESS)
		{
			AssertInt(FAT_SUCCESS, eResult);
			bAllSuccessful = false;
			break;
		}

		if (uiBytesRead != 1)
		{
			AssertInt(1, uiBytesRead);
			bAllSuccessful = false;
			break;

		}

		if (szRead[0] != szSource[i])
		{
			AssertChar(szSource[i], szRead[i]);
			bAllSuccessful = false;
			break;
		}
	}

	AssertTrue(bAllSuccessful);

	bAllSuccessful = true;
	for (i = 65600; i > 32768; i--)
	{
		eResult = cFatFile.Seek(i, FAT_SEEK_START);
		if (eResult != FAT_SUCCESS)
		{
			AssertInt(FAT_SUCCESS, eResult);
			bAllSuccessful = false;
			break;
		}

		eResult = cFatFile.Read((uint8*)szRead, 1, &uiBytesRead);
		if (eResult != FAT_SUCCESS)
		{
			AssertInt(FAT_SUCCESS, eResult);
			bAllSuccessful = false;
			break;
		}

		if (uiBytesRead != 1)
		{
			AssertInt(1, uiBytesRead);
			bAllSuccessful = false;
			break;

		}

		if (szRead[0] != szSource[i - 32769])
		{
			AssertChar(szSource[i], szRead[i]);
			bAllSuccessful = false;
			break;
		}
	}

	AssertTrue(bAllSuccessful);

	eResult = cFatFile.Close();
	AssertInt(FAT_SUCCESS, eResult);

	cFatFile.Init(&cVolume);
	eResult = cFatFile.Open("\\File1.txt", FAT_FILE_ACCESS_READ);
	AssertInt(FAT_SUCCESS, eResult);
	memset(szRead, 0xcc, 32769);
	eResult = cFatFile.Read((uint8*)szRead, 32769, &uiBytesRead);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(32769, uiBytesRead);
	AssertMemory(szSource, szRead, 32768);
	eResult = cFatFile.Close();
	AssertInt(FAT_SUCCESS, eResult);

	cVolume.Unmount();

	cMemoryDrive.Kill();

	free(szRead);
	free(szSource);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFat32WriteLargerThanOneCluster(void)
{
	TypeConverterInit();
	BeginTests();

	TestFat32WriteLargerThanOneClusterAppend();
	TestFat32WriteLargerThanOneClusterOverwrite();

	TestStatistics();
	TypeConverterKill();
}

