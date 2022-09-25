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
#include "TestFat32Common.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFat32WriteLargerThanOneCluster(void)
{
	TypeConverterInit();
	BeginTests();

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

	eResult = cVolume.Mount(&cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);

	cFatFile.Init(&cVolume);
	eResult = cFatFile.Open("\\File1.txt", FAT_FILE_ACCESS_CREATE | FAT_FILE_ACCESS_OVERWRITE | FAT_FILE_ACCESS_WRITE | FAT_FILE_ACCESS_READ);
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cFatFile.Write((uint8*)szSource, 32769);
	AssertInt(FAT_SUCCESS, eResult);

	szRead = (char*)malloc(32769);
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

	eResult = cFatFile.Close();
	AssertInt(FAT_SUCCESS, eResult);

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

	TestStatistics();
	TypeConverterKill();
}

