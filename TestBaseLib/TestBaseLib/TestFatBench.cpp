#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BaseLib/TypeConverter.h"
#include "TestFat32Common.h"
#include "BaseLib/Fat32.h"
#include "TestLib/Assert.h"


//A FAT32 work load to time the 65C64 and W65C816 code generators with: format, directories, files written in
//chunks, read back, seeks, overwrites, renames, deletes (leaving holes that later files fill) and directory listings.
//Each file's expected contents are kept in memory and everything read is compared with them.

#define FAT_BENCH_FILES			24


struct SFatBenchFile
{
	char	szName[96];
	uint8*	puiData;
	uint32	uiSize;
	bool	bExists;
};


static uint32	guiFatBenchSeed;


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
static uint32 FatBenchRandom(void)
{
	guiFatBenchSeed = guiFatBenchSeed * 1103515245 + 12345;
	return guiFatBenchSeed >> 8;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
static void FatBenchFill(uint8* puiData, uint32 uiSize)
{
	uint32	i;

	for (i = 0; i < uiSize; i++)
	{
		puiData[i] = (uint8)FatBenchRandom();
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
static void FatBenchName(SFatBenchFile* psFile, uint32 uiIndex, const char* szSuffix)
{
	static const char*	aszDirectories[] = { "\\Projects\\Source", "\\Projects", "\\Music\\Albums With Long Names", "" };

	sprintf(psFile->szName, "%s\\File Number %u%s", aszDirectories[uiIndex % 4], (unsigned int)uiIndex, szSuffix);
}


//////////////////////////////////////////////////////////////////////////
//
// Writes the whole file in uiChunk sized writes.
//
//////////////////////////////////////////////////////////////////////////
static void FatBenchWrite(CFatVolume* pcVolume, SFatBenchFile* psFile, uint32 uiChunk)
{
	CFatFile	cFatFile;
	EFatCode	eResult;
	uint32		uiDone;
	uint32		uiLength;

	cFatFile.Init(pcVolume);
	eResult = cFatFile.Open(psFile->szName, FAT_FILE_ACCESS_CREATE | FAT_FILE_ACCESS_OVERWRITE | FAT_FILE_ACCESS_WRITE);
	AssertInt(FAT_SUCCESS, eResult);
	for (uiDone = 0; uiDone < psFile->uiSize; uiDone += uiLength)
	{
		uiLength = psFile->uiSize - uiDone;
		if (uiLength > uiChunk)
		{
			uiLength = uiChunk;
		}
		eResult = cFatFile.Write(&psFile->puiData[uiDone], uiLength);
		AssertInt(FAT_SUCCESS, eResult);
	}
	AssertInt(psFile->uiSize, cFatFile.Size());
	eResult = cFatFile.Close();
	AssertInt(FAT_SUCCESS, eResult);
	psFile->bExists = true;
}


//////////////////////////////////////////////////////////////////////////
//
// Reads the whole file in uiChunk sized reads and compares it.
//
//////////////////////////////////////////////////////////////////////////
static void FatBenchRead(CFatVolume* pcVolume, SFatBenchFile* psFile, uint32 uiChunk, uint8* puiBuffer)
{
	CFatFile	cFatFile;
	EFatCode	eResult;
	uint32		uiDone;
	uint32		uiLength;
	lsize		uiBytesRead;

	cFatFile.Init(pcVolume);
	eResult = cFatFile.Open(psFile->szName, FAT_FILE_ACCESS_READ);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt(psFile->uiSize, cFatFile.Size());
	for (uiDone = 0; uiDone < psFile->uiSize; uiDone += uiLength)
	{
		uiLength = psFile->uiSize - uiDone;
		if (uiLength > uiChunk)
		{
			uiLength = uiChunk;
		}
		eResult = cFatFile.Read(puiBuffer, uiLength, &uiBytesRead);
		AssertInt(FAT_SUCCESS, eResult);
		AssertLSize(uiLength, uiBytesRead);
		AssertMemory(&psFile->puiData[uiDone], puiBuffer, uiLength);
	}
	eResult = cFatFile.Close();
	AssertInt(FAT_SUCCESS, eResult);
}


//////////////////////////////////////////////////////////////////////////
//
// Small reads at random places.
//
//////////////////////////////////////////////////////////////////////////
static void FatBenchSeekAndRead(CFatVolume* pcVolume, SFatBenchFile* psFile, uint32 uiSeeks, uint8* puiBuffer)
{
	CFatFile	cFatFile;
	EFatCode	eResult;
	uint32		i;
	uint32		uiPosition;
	uint32		uiLength;
	lsize		uiBytesRead;

	cFatFile.Init(pcVolume);
	eResult = cFatFile.Open(psFile->szName, FAT_FILE_ACCESS_READ);
	AssertInt(FAT_SUCCESS, eResult);
	for (i = 0; i < uiSeeks; i++)
	{
		uiPosition = FatBenchRandom() % psFile->uiSize;
		uiLength = 1 + FatBenchRandom() % 200;
		if (uiPosition + uiLength > psFile->uiSize)
		{
			uiLength = psFile->uiSize - uiPosition;
		}
		eResult = cFatFile.Seek(uiPosition, FAT_SEEK_START);
		AssertInt(FAT_SUCCESS, eResult);
		eResult = cFatFile.Read(puiBuffer, uiLength, &uiBytesRead);
		AssertInt(FAT_SUCCESS, eResult);
		AssertLSize(uiLength, uiBytesRead);
		AssertMemory(&psFile->puiData[uiPosition], puiBuffer, uiLength);
	}
	eResult = cFatFile.Close();
	AssertInt(FAT_SUCCESS, eResult);
}


//////////////////////////////////////////////////////////////////////////
//
// Overwrites a few ranges inside the file (the expected data too).
//
//////////////////////////////////////////////////////////////////////////
static void FatBenchOverwrite(CFatVolume* pcVolume, SFatBenchFile* psFile, uint32 uiWrites)
{
	CFatFile	cFatFile;
	EFatCode	eResult;
	uint32		i;
	uint32		uiPosition;
	uint32		uiLength;

	cFatFile.Init(pcVolume);
	eResult = cFatFile.Open(psFile->szName, FAT_FILE_ACCESS_READ | FAT_FILE_ACCESS_WRITE);
	AssertInt(FAT_SUCCESS, eResult);
	for (i = 0; i < uiWrites; i++)
	{
		uiPosition = FatBenchRandom() % psFile->uiSize;
		uiLength = 1 + FatBenchRandom() % 900;
		if (uiPosition + uiLength > psFile->uiSize)
		{
			uiLength = psFile->uiSize - uiPosition;
		}
		FatBenchFill(&psFile->puiData[uiPosition], uiLength);
		eResult = cFatFile.Seek(uiPosition, FAT_SEEK_START);
		AssertInt(FAT_SUCCESS, eResult);
		eResult = cFatFile.Write(&psFile->puiData[uiPosition], uiLength);
		AssertInt(FAT_SUCCESS, eResult);
	}
	AssertInt(psFile->uiSize, cFatFile.Size());
	eResult = cFatFile.Close();
	AssertInt(FAT_SUCCESS, eResult);
}


//////////////////////////////////////////////////////////////////////////
//
// The number of entries (and their total size) in szDirectory, but . and ..
//
//////////////////////////////////////////////////////////////////////////
static uint32 FatBenchList(CFatVolume* pcVolume, const char* szDirectory, uint32* puiTotalSize)
{
	SFatDirectoryEntry*		psEntry;
	SFatFileSystemQuery		sQuery;
	EFatCode				eResult;
	uint32					uiCount;

	uiCount = 0;
	*puiTotalSize = 0;
	sQuery.Init();
	eResult = pcVolume->FindFirstFATEntry(szDirectory, 0, &psEntry, &sQuery);
	AssertInt(FAT_SUCCESS, eResult);
	while ((eResult == FAT_SUCCESS) && (psEntry->szName[0] != '\0'))
	{
		if (psEntry->szName[0] != '.')
		{
			uiCount++;
			*puiTotalSize += psEntry->uiSize;
		}
		eResult = pcVolume->FindNextFATEntry(&psEntry, &sQuery);
	}
	sQuery.Kill(pcVolume->GetSectorCache());
	return uiCount;
}


//////////////////////////////////////////////////////////////////////////
//
// The files' expected count and total size in the listings of all four directories.
//
//////////////////////////////////////////////////////////////////////////
static void FatBenchCheckListings(CFatVolume* pcVolume, SFatBenchFile* asFiles)
{
	static const char*	aszDirectories[] = { "\\Projects\\Source", "\\Projects", "\\Music\\Albums With Long Names", "\\" };
	static const uint32	auiSubdirectories[] = { 0, 1, 0, 2 };
	uint32				uiDirectory;
	uint32				uiCount;
	uint32				uiSize;
	uint32				uiExpectedCount;
	uint32				uiExpectedSize;
	uint32				i;

	for (uiDirectory = 0; uiDirectory < 4; uiDirectory++)
	{
		uiExpectedCount = auiSubdirectories[uiDirectory];
		uiExpectedSize = 0;
		for (i = uiDirectory; i < FAT_BENCH_FILES; i += 4)
		{
			if (asFiles[i].bExists)
			{
				uiExpectedCount++;
				uiExpectedSize += asFiles[i].uiSize;
			}
		}
		uiCount = FatBenchList(pcVolume, aszDirectories[uiDirectory], &uiSize);
		AssertInt(uiExpectedCount, uiCount);
		AssertInt(uiExpectedSize, uiSize);
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
static void FatBenchRun(uint8 uiSectorsPerCluster, uint64 uiSectors)
{
	CFatTestDrive	cMemoryDrive;
	CFatVolume		cVolume;
	EFatCode		eResult;
	SFatBenchFile	asFiles[FAT_BENCH_FILES];
	char			szNewName[96];
	uint8*			puiBuffer;
	uint32			i;

	guiFatBenchSeed = 0x5EED + uiSectorsPerCluster;

	cMemoryDrive.Init(uiSectors);
	eResult = FatFormat(FAT_FS_TYPE_FAT32, "Bench", uiSectorsPerCluster, &cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);

	eResult = cVolume.Mount(&cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);
	AssertInt((int)FAT_FS_TYPE_FAT32, (int)cVolume.GetFileSystemType());

	AssertInt(FAT_SUCCESS, cVolume.CreateDirectory("\\Projects"));
	AssertInt(FAT_SUCCESS, cVolume.CreateDirectory("\\Projects\\Source"));
	AssertInt(FAT_SUCCESS, cVolume.CreateDirectory("\\Music"));
	AssertInt(FAT_SUCCESS, cVolume.CreateDirectory("\\Music\\Albums With Long Names"));

	puiBuffer = (uint8*)malloc(4096);

	for (i = 0; i < FAT_BENCH_FILES; i++)
	{
		FatBenchName(&asFiles[i], i, ".txt");
		asFiles[i].uiSize = 100 + (i * 7919) % 30000;
		asFiles[i].puiData = (uint8*)malloc(asFiles[i].uiSize);
		asFiles[i].bExists = false;
		FatBenchFill(asFiles[i].puiData, asFiles[i].uiSize);
		FatBenchWrite(&cVolume, &asFiles[i], 300 + (i % 5) * 700);
	}
	FatBenchCheckListings(&cVolume, asFiles);

	eResult = cVolume.Unmount();
	AssertInt(FAT_SUCCESS, eResult);
	eResult = cVolume.Mount(&cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);

	for (i = 0; i < FAT_BENCH_FILES; i++)
	{
		FatBenchRead(&cVolume, &asFiles[i], (i & 1) ? 512 : 333, puiBuffer);
	}
	for (i = 0; i < FAT_BENCH_FILES; i += 3)
	{
		FatBenchSeekAndRead(&cVolume, &asFiles[i], 40, puiBuffer);
	}
	for (i = 1; i < FAT_BENCH_FILES; i += 4)
	{
		FatBenchOverwrite(&cVolume, &asFiles[i], 12);
	}

	//Renames, short and long.
	for (i = 0; i < FAT_BENCH_FILES; i += 2)
	{
		strcpy(szNewName, asFiles[i].szName);
		FatBenchName(&asFiles[i], i, (i & 2) ? ".c" : " renamed to something a good deal longer.txt");
		eResult = cVolume.Rename(szNewName, asFiles[i].szName);
		AssertInt(FAT_SUCCESS, eResult);
	}

	//Deletes leave holes in the FAT and the directories that the next files fill.
	for (i = 0; i < FAT_BENCH_FILES; i += 3)
	{
		eResult = cVolume.Delete(asFiles[i].szName);
		AssertInt(FAT_SUCCESS, eResult);
		asFiles[i].bExists = false;
	}
	FatBenchCheckListings(&cVolume, asFiles);
	for (i = 0; i < FAT_BENCH_FILES; i += 3)
	{
		FatBenchName(&asFiles[i], i, ".new");
		free(asFiles[i].puiData);
		asFiles[i].uiSize = 2000 + (i * 4513) % 20000;
		asFiles[i].puiData = (uint8*)malloc(asFiles[i].uiSize);
		FatBenchFill(asFiles[i].puiData, asFiles[i].uiSize);
		FatBenchWrite(&cVolume, &asFiles[i], 1024);
	}
	FatBenchCheckListings(&cVolume, asFiles);

	eResult = cVolume.Unmount();
	AssertInt(FAT_SUCCESS, eResult);
	eResult = cVolume.Mount(&cMemoryDrive);
	AssertInt(FAT_SUCCESS, eResult);

	for (i = 0; i < FAT_BENCH_FILES; i++)
	{
		FatBenchRead(&cVolume, &asFiles[i], 4096, puiBuffer);
	}
	FatBenchCheckListings(&cVolume, asFiles);

	eResult = cVolume.Unmount();
	AssertInt(FAT_SUCCESS, eResult);

	for (i = 0; i < FAT_BENCH_FILES; i++)
	{
		free(asFiles[i].puiData);
	}
	free(puiBuffer);
	cMemoryDrive.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFatBench(void)
{
	TypeConverterInit();
	BeginTests();

	//FAT32 needs at least 65525 clusters: 512 byte clusters (33MB) and 4KB clusters (260MB).
	FatBenchRun(1, 65600 + 4096);
	FatBenchRun(8, 65600 * 8 + 4096);

	TestStatistics();
	TypeConverterKill();
}

