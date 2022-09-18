#include "BaseLib/FastFunctions.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/RedirectPrintf.h"
#include "BaseLib/DiskFile.h"
#include "BaseLib/IntegerHelper.h"
#include "BaseLib/StringHelper.h"
#include "BaseLib/ArrayChars.h"
#include "CoreLib/MemoryDrive.h"
#include "CoreLib/FatCache.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
char* FatCacheAllocateTestData(int iDataLength)
{
	int		i;
	char*	pvData;

	iDataLength = 65 KB;
	pvData = (char*)malloc(iDataLength);

	char c = 33;
	for (i = 0; i < iDataLength; i++)
	{
		pvData[i] = c;
		if (i % 3 == 2)
		{
			c++;
			if (c == '"')
			{
				c++;
			}
			if (c == '\\')
			{
				c++;
			}
			if (c == 0)
			{
				c = 33;
			}
		}
	}
	return pvData;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void FatCacheFillTestDrive(char* pcMemory, int iDataLength)
{
	int		i;
	char	c;

	c = 'A';
	for (i = 0; i < iDataLength; i++)
	{
		pcMemory[i] = c;
		if (i % 512 == 511)
		{
			c++;
		}

		if (c == '"')
		{
			c++;
		}
		if (c == '\\')
		{
			c++;
		}
		if (c == 0)
		{
			c = 33;
		}
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFatCacheWrite(void)
{
	CMemoryDrive	cMemoryDrive;
	CDiskFile		cFile;
	CFatCache		cCache;
	char*			pvData;
	int				iDataLength;
	uint32			uiLength;

	iDataLength = 65 KB;
	pvData = FatCacheAllocateTestData(iDataLength);

	cMemoryDrive.Init(1 MB, 512);
	cCache.Init(&cMemoryDrive, 32 KB, 512);

	uiLength = 3;
	cCache.Write((uint8*)pvData, 0, 0, 0, &uiLength, 0);
	uiLength = 3;
	cCache.Write((uint8*)&pvData[3], 0, 0, 2, &uiLength, 3);
	AssertString("!!###", (char*)cCache.GetCache());
	AssertTrue(cCache.IsSectorDirty(0));
	AssertTrue(cCache.IsSectorCached(0));
	AssertFalse(cCache.IsSectorDirty(1));
	AssertFalse(cCache.IsSectorCached(1));

	uiLength = 511;
	cCache.Write((uint8*)pvData, 0, 0, 0, &uiLength, 3);
	AssertInt(511, strlen((char*)cCache.GetCache()));
	AssertString("!!!###$$$%%%&&&'''((()))***+++,,,---...///000111222333444555666777888999:::;;;<<<===>>>???@@@AAABBBCCCDDDEEEFFFGGGHHHIIIJJJKKKLLLMMMNNNOOOPPPQQQRRRSSSTTTUUUVVVWWWXXXYYYZZZ[[[]]]^^^___```aaabbbcccdddeeefffggghhhiiijjjkkklllmmmnnnooopppqqqrrrssstttuuuvvvwwwxxxyyyzzz{{{|||}}}~~~����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������", 
		(char*)cCache.GetCache());
	AssertTrue(cCache.IsSectorDirty(0));
	AssertTrue(cCache.IsSectorCached(0));
	AssertFalse(cCache.IsSectorDirty(1));
	AssertFalse(cCache.IsSectorCached(1));

	uiLength = 1;
	cCache.Write((uint8*)pvData, 0, 0, 511, &uiLength, 511);
	AssertInt(512, strlen((char*)cCache.GetCache()));
	AssertString("!!!###$$$%%%&&&'''((()))***+++,,,---...///000111222333444555666777888999:::;;;<<<===>>>???@@@AAABBBCCCDDDEEEFFFGGGHHHIIIJJJKKKLLLMMMNNNOOOPPPQQQRRRSSSTTTUUUVVVWWWXXXYYYZZZ[[[]]]^^^___```aaabbbcccdddeeefffggghhhiiijjjkkklllmmmnnnooopppqqqrrrssstttuuuvvvwwwxxxyyyzzz{{{|||}}}~~~����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������!",
		(char*)cCache.GetCache());
	AssertTrue(cCache.IsSectorDirty(0));
	AssertTrue(cCache.IsSectorCached(0));
	AssertFalse(cCache.IsSectorDirty(1));
	AssertFalse(cCache.IsSectorCached(1));

	uiLength = 512 + 256;
	cCache.Write((uint8*)pvData, 0, 0, 1, &uiLength, 512);
	AssertInt(512 + 256 + 1, strlen((char*)cCache.GetCache()));
	AssertString("!!!!###$$$%%%&&&'''((()))***+++,,,---...///000111222333444555666777888999:::;;;<<<===>>>???@@@AAABBBCCCDDDEEEFFFGGGHHHIIIJJJKKKLLLMMMNNNOOOPPPQQQRRRSSSTTTUUUVVVWWWXXXYYYZZZ[[[]]]^^^___```aaabbbcccdddeeefffggghhhiiijjjkkklllmmmnnnooopppqqqrrrssstttuuuvvvwwwxxxyyyzzz{{{|||}}}~~~������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������!!!###$$$%%%&&&'''((()))***+++,,,---...///000111222333444555666777888999:::;;;<<<===>>>???@@@AAABBBCCCDDD",
		(char*)cCache.GetCache());

	uiLength = 512 + 512 + 1;
	cCache.Write((uint8*)pvData, 0, 0, 16, &uiLength, 512 + 256 + 1);
	AssertInt(16 + 512 + 512 + 1, strlen((char*)cCache.GetCache()));
	AssertString("!!!!###$$$%%%&&&!!!###$$$%%%&&&'''((()))***+++,,,---...///000111222333444555666777888999:::;;;<<<===>>>???@@@AAABBBCCCDDDEEEFFFGGGHHHIIIJJJKKKLLLMMMNNNOOOPPPQQQRRRSSSTTTUUUVVVWWWXXXYYYZZZ[[[]]]^^^___```aaabbbcccdddeeefffggghhhiiijjjkkklllmmmnnnooopppqqqrrrssstttuuuvvvwwwxxxyyyzzz{{{|||}}}~~~������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������!!!###$$$%%%&&&'''((()))***+++,,,---...///000111222333444555666777888999:::;;;<<<===>>>???@@@AAABBBCCCDDDEEEFFFGGGHHHIIIJJJKKKLLLMMMNNNOOOPPPQQQRRRSSSTTTUUUVVVWWWXXXYYYZZZ[[[]]]^^^___```aaabbbcccdddeeefffggghhhiiijjjkkklllmmmnnnooopppqqqrrrssstttuuuvvvwwwxxxyyyzzz{{{|||}}}~~~�����������������������������������������������������������������������������������",
		(char*)cCache.GetCache());

	uiLength = iDataLength;
	cCache.Write((uint8*)pvData, 0, 0, 0, &uiLength, 16 + 512 + 512 + 1);
	AssertMemory(pvData, cCache.GetCache(), 32768);
	AssertTrue(cCache.IsSectorDirty(0));
	AssertTrue(cCache.IsSectorDirty(63));

	uiLength = iDataLength;
	cCache.Clear();
	cCache.Write((uint8*)pvData, 0, 0, 0, &uiLength, 0);
	AssertMemory(pvData, cCache.GetCache(), 32768);
	cCache.Write((uint8*)&pvData[32768], 1, 0, 0, &uiLength, 0);
	AssertMemory((uint8*)&pvData[32768], cCache.GetCache(), 32768);
	cCache.Write((uint8*)&pvData[65536], 2, 0, 0, &uiLength, 0);
	AssertMemory((uint8*)&pvData[65536], cCache.GetCache(), 1024);

	cCache.Kill();

	free(pvData);

	cMemoryDrive.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFatCacheDirty(void)
{
	CMemoryDrive	cMemoryDrive;
	CDiskFile		cFile;
	CFatCache		cCache;
	char*			pvData;
	int				iDataLength;
	uint32			uiLength;

	iDataLength = 65 KB;
	pvData = FatCacheAllocateTestData(iDataLength);

	cMemoryDrive.Init(1 MB, 512);
	cCache.Init(&cMemoryDrive, 32 KB, 512);

	uiLength = 512;
	cCache.Write((uint8*)pvData, 0, 0, 0, &uiLength, 0);
	AssertTrue(cCache.IsSectorDirty(0));
	AssertTrue(cCache.IsSectorCached(0));
	AssertFalse(cCache.IsSectorDirty(1));
	AssertFalse(cCache.IsSectorCached(1));

	cCache.Clear();
	uiLength = 513;
	cCache.Write((uint8*)pvData, 0, 0, 0, &uiLength, 0);
	AssertTrue(cCache.IsSectorDirty(0));
	AssertTrue(cCache.IsSectorCached(0));
	AssertTrue(cCache.IsSectorDirty(1));
	AssertTrue(cCache.IsSectorCached(1));
	AssertFalse(cCache.IsSectorDirty(2));
	AssertFalse(cCache.IsSectorCached(2));

	cCache.Clear();
	uiLength = 2;
	cCache.Write((uint8*)pvData, 0, 0, 511, &uiLength, 511);
	AssertTrue(cCache.IsSectorDirty(0));
	AssertTrue(cCache.IsSectorCached(0));
	AssertTrue(cCache.IsSectorDirty(1));
	AssertTrue(cCache.IsSectorCached(1));
	AssertFalse(cCache.IsSectorDirty(2));
	AssertFalse(cCache.IsSectorCached(2));

	cCache.Clear();
	uiLength = 1 + 512 + 512 + 1;
	cCache.Write((uint8*)pvData, 0, 0, 511 + 512, &uiLength, 511 + 512);
	AssertFalse(cCache.IsSectorDirty(0));
	AssertTrue(cCache.IsSectorDirty(1));
	AssertTrue(cCache.IsSectorDirty(2));
	AssertTrue(cCache.IsSectorDirty(3));
	AssertTrue(cCache.IsSectorDirty(4));
	AssertFalse(cCache.IsSectorDirty(5));

	cCache.Kill();

	free(pvData);

	cMemoryDrive.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFatCacheDiscontiguousWrites(void)
{
	CMemoryDrive	cMemoryDrive;
	CDiskFile		cFile;
	CFatCache		cCache;
	char*			pvData;
	int				iDataLength;
	uint32			uiLength;
	char*			pcMemory;
	int				iStart;
	int				i;
	int				iZeroIndex;
	int				iNonZeroIndex;
	int				aiZeroIndices[16];
	int				aiNonZeroIndices[16];
	bool			bIsZero = false;
	bool			bResult;

	iDataLength = 65 KB;
	pvData = FatCacheAllocateTestData(iDataLength);

	cMemoryDrive.Init(1 MB, 512);
	cCache.Init(&cMemoryDrive, 32 KB, 512);
	bResult = cMemoryDrive.Erase(0, cCache.GetSectorsPerCluster() - 1);
	AssertTrue(bResult);

	uiLength = 512 * 2;
	bResult = cCache.Write((uint8*)pvData, 0, 0, 512, &uiLength, 512);
	AssertTrue(bResult);

	uiLength = 512 * 3;
	bResult = cCache.Write((uint8*)pvData, 0, 0, 512 * 5, &uiLength, 512 * 5);
	AssertTrue(bResult);

	uiLength = 512;
	bResult = cCache.Write((uint8*)pvData, 0, 0, 512 * 11, &uiLength, 512 * 11);
	AssertTrue(bResult);

	uiLength = 512;
	bResult = cCache.Write((uint8*)pvData, 0, 0, 512 * 13, &uiLength, 512 * 13);
	AssertTrue(bResult);

	AssertFalse(cCache.IsSectorDirty(0));
	AssertTrue(cCache.IsSectorDirty(1));
	AssertTrue(cCache.IsSectorDirty(2));
	AssertFalse(cCache.IsSectorDirty(3));
	AssertFalse(cCache.IsSectorDirty(4));
	AssertTrue(cCache.IsSectorDirty(5));
	AssertTrue(cCache.IsSectorDirty(6));
	AssertTrue(cCache.IsSectorDirty(7));
	AssertFalse(cCache.IsSectorDirty(8));
	AssertFalse(cCache.IsSectorDirty(9));
	AssertFalse(cCache.IsSectorDirty(10));
	AssertTrue(cCache.IsSectorDirty(11));
	AssertFalse(cCache.IsSectorDirty(12));
	AssertTrue(cCache.IsSectorDirty(13));
	AssertFalse(cCache.IsSectorDirty(14));
	AssertFalse(cCache.IsSectorDirty(15));

	pcMemory = (char*)cMemoryDrive.GetMemory();

	iStart = FindFirstByte(pcMemory, 33, 32 KB);
	AssertInt(-1, iStart);

	cCache.Flush();

	iZeroIndex = 0;
	iNonZeroIndex = 0;
	memset(aiZeroIndices, -1, 16 * sizeof(int));
	memset(aiNonZeroIndices, -1, 16 * sizeof(int));
	bIsZero = false;
	for (i = 0; i < 32 KB; i++)
	{
		if (pcMemory[i])
		{
			if (bIsZero)
			{
				bIsZero = false;
				aiNonZeroIndices[iNonZeroIndex] = i;
				iNonZeroIndex++;
			}
		}
		else 
		{
			if (!bIsZero)
			{
				bIsZero = true;
				aiZeroIndices[iZeroIndex] = i;
				iZeroIndex++;
			}
		}
	}

	AssertInt(512 * 0, aiZeroIndices[0]);
	AssertInt(512 * 1, aiNonZeroIndices[0]);

	AssertInt(512 * 3, aiZeroIndices[1]);
	AssertInt(512 * 5, aiNonZeroIndices[1]);

	AssertInt(512 * 8, aiZeroIndices[2]);
	AssertInt(512 * 11, aiNonZeroIndices[2]);

	AssertInt(512 * 12, aiZeroIndices[3]);
	AssertInt(512 * 13, aiNonZeroIndices[3]);

	AssertInt(512 * 14, aiZeroIndices[4]);

	cCache.Kill();

	free(pvData);

	cMemoryDrive.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFatCacheRead(void)
{
	CMemoryDrive	cMemoryDrive;
	CDiskFile		cFile;
	CFatCache		cCache;
	char*			pvData;
	int				iDataLength;
	char*			pcMemory;
	uint32			uiLength;
	bool			bResult;

	iDataLength = 32 KB;
	pvData = FatCacheAllocateTestData(iDataLength);

	cMemoryDrive.Init(1 MB, 512);
	cCache.Init(&cMemoryDrive, 32 KB, 512);
	cMemoryDrive.Erase(0, cCache.GetSectorsPerCluster() - 1);

	pcMemory = (char*)cMemoryDrive.GetMemory();
	FatCacheFillTestDrive(pcMemory, 256 KB);

	uiLength = 32 KB;
	bResult = cCache.Read((uint8*)pvData, 0, 0, 0, &uiLength, 32 KB);
	AssertTrue(bResult);
	AssertInt(0, uiLength);
	AssertMemory(pcMemory, pvData, 32 KB);
	AssertTrue(cCache.IsSectorCached(0));
	AssertTrue(cCache.IsSectorCached(63));

	cCache.Clear();
	uiLength = 256;
	bResult = cCache.Read((uint8*)pvData, 0, 0, 128, &uiLength, 32 KB);
	AssertTrue(bResult);
	AssertInt(0, uiLength);
	AssertMemory(&pcMemory[128], pvData, 256);
	AssertTrue(cCache.IsSectorCached(0));
	AssertFalse(cCache.IsSectorCached(1));

	uiLength = 256;
	bResult = cCache.Read((uint8*)pvData, 0, 0, 384, &uiLength, 32 KB);
	AssertTrue(bResult);
	AssertInt(0, uiLength);
	AssertMemory(&pcMemory[384], pvData, 256);
	AssertTrue(cCache.IsSectorCached(0));
	AssertTrue(cCache.IsSectorCached(1));
	AssertFalse(cCache.IsSectorCached(2));

	uiLength = 256;
	bResult = cCache.Read((uint8*)pvData, 0, 0, 32384, &uiLength, 32 KB);
	AssertTrue(bResult);
	AssertInt(0, uiLength);
	AssertMemory(&pcMemory[32384], pvData, 256);
	AssertFalse(cCache.IsSectorCached(62));
	AssertTrue(cCache.IsSectorCached(63));

	uiLength = 256;
	bResult = cCache.Read((uint8*)pvData, 0, 0, 16256, &uiLength, 32 KB);
	AssertTrue(bResult);
	AssertInt(0, uiLength);
	AssertMemory(&pcMemory[16256], pvData, 256);
	AssertFalse(cCache.IsSectorCached(30));
	AssertTrue(cCache.IsSectorCached(31));
	AssertTrue(cCache.IsSectorCached(32));
	AssertFalse(cCache.IsSectorCached(33));

	uiLength = 32 KB;
	bResult = cCache.Read((uint8*)pvData, 0, 0, 0, &uiLength, 32 KB);
	AssertTrue(bResult);
	AssertInt(0, uiLength);
	AssertMemory(pcMemory, pvData, 32 KB);

	cCache.Clear();
	uiLength = 256;
	bResult = cCache.Read((uint8*)pvData, 0, 0, 16256, &uiLength, 32 KB);
	AssertTrue(bResult);
	AssertInt(0, uiLength);
	AssertMemory(&pcMemory[16256], pvData, 256);

	uiLength = 32 KB;
	bResult = cCache.Read((uint8*)pvData, 0, 0, 0, &uiLength, 32 KB);
	AssertTrue(bResult);
	AssertInt(0, uiLength);
	AssertMemory(pcMemory, pvData, 32 KB);

	cCache.Kill();

	free(pvData);

	cMemoryDrive.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFatCacheWriteLimits(void)
{
	CMemoryDrive	cMemoryDrive;
	CDiskFile		cFile;
	CFatCache		cCache;
	char*			pvData;
	int				iDataLength;
	uint32			uiLength;
	bool			bResult;
	char*			pcMemory;

	iDataLength = 65 KB;
	pvData = FatCacheAllocateTestData(iDataLength);

	cMemoryDrive.Init(1 MB, 512);
	cCache.Init(&cMemoryDrive, 32 KB, 512);
	bResult = cMemoryDrive.Erase(0, cCache.GetSectorsPerCluster() - 1);
	AssertTrue(bResult);

	uiLength = 1;
	bResult = cCache.Write((uint8*)pvData, 0, 0, 1, &uiLength, 0);
	AssertFalse(bResult);
	AssertInt(1, uiLength);

	uiLength = 1;
	bResult = cCache.Write((uint8*)pvData, 0, 0, 0, &uiLength, 0);
	AssertTrue(bResult);
	AssertInt(0, uiLength);
	AssertTrue(cCache.IsSectorCached(0));
	AssertTrue(cCache.IsSectorDirty(0));

	cCache.Clear();
	uiLength = 1;
	bResult = cCache.Write((uint8*)pvData, 0, 0, 511, &uiLength, 510);
	AssertFalse(bResult);
	AssertInt(1, uiLength);

	uiLength = 1;
	bResult = cCache.Write((uint8*)pvData, 0, 0, 511, &uiLength, 511);
	AssertTrue(bResult);
	AssertInt(0, uiLength);
	AssertTrue(cCache.IsSectorCached(0));
	AssertTrue(cCache.IsSectorDirty(0));

	cCache.Clear();
	uiLength = 1;
	bResult = cCache.Write((uint8*)pvData, 0, 0, 512, &uiLength, 511);
	AssertFalse(bResult);
	AssertInt(1, uiLength);

	uiLength = 1;
	bResult = cCache.Write((uint8*)pvData, 0, 0, 512, &uiLength, 512);
	AssertTrue(bResult);
	AssertInt(0, uiLength);
	AssertFalse(cCache.IsSectorCached(0));
	AssertFalse(cCache.IsSectorDirty(0));
	AssertTrue(cCache.IsSectorCached(1));
	AssertTrue(cCache.IsSectorDirty(1));

	pcMemory = (char*)cCache.GetCache();
	AssertChar('!', pcMemory[512]);
	AssertChar('\0', pcMemory[511]);
	AssertChar('\0', pcMemory[513]);
	cCache.Flush();

	pcMemory = (char*)cMemoryDrive.GetMemory();
	AssertChar('!', pcMemory[512]);
	AssertChar('\0', pcMemory[511]);
	AssertChar('\0', pcMemory[513]);

	cCache.Kill();

	free(pvData);

	cMemoryDrive.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFatCacheReadLimits(void)
{
	CMemoryDrive	cMemoryDrive;
	CDiskFile		cFile;
	CFatCache		cCache;
	int				iDataLength;
	uint32			uiLength;
	bool			bResult;
	char*			pcDriveMemory;
	char			acTestMemory[1 KB];

	iDataLength = 65 KB;

	cMemoryDrive.Init(1 MB, 512);
	cCache.Init(&cMemoryDrive, 32 KB, 512);
	bResult = cMemoryDrive.Erase(0, cCache.GetSectorsPerCluster() - 1);
	AssertTrue(bResult);

	pcDriveMemory = (char*)cMemoryDrive.GetMemory();
	FatCacheFillTestDrive(pcDriveMemory, 256 KB);

	uiLength = 1;
	bResult = cCache.Read((uint8*)acTestMemory, 0, 0, 1, &uiLength, 0);
	AssertFalse(bResult);
	AssertInt(1, uiLength);

	memset(acTestMemory, 0, 1 KB);
	uiLength = 2;
	bResult = cCache.Read((uint8*)acTestMemory, 0, 0, 0, &uiLength, 1);
	AssertTrue(bResult);
	AssertInt(1, uiLength);
	AssertString("A", acTestMemory);

	cCache.Clear();
	memset(acTestMemory, 0, 1 KB);
	uiLength = 513;
	bResult = cCache.Read((uint8*)acTestMemory, 0, 0, 0, &uiLength, 512);
	AssertTrue(bResult);
	AssertInt(1, uiLength);
	AssertString("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",
		acTestMemory);
	AssertTrue(cCache.IsSectorCached(0));
	AssertFalse(cCache.IsSectorCached(1));

	cCache.Clear();
	memset(acTestMemory, 0, 1 KB);
	uiLength = 2;
	bResult = cCache.Read((uint8*)acTestMemory, 0, 0, 32767, &uiLength, 32768);
	AssertTrue(bResult);
	AssertInt(1, uiLength);
	AssertString("\x81", acTestMemory);
	AssertFalse(cCache.IsSectorCached(62));
	AssertTrue(cCache.IsSectorCached(63));

	cCache.Clear();
	memset(acTestMemory, 0, 1 KB);
	uiLength = 3;
	bResult = cCache.Read((uint8*)acTestMemory, 0, 0, 32767, &uiLength, 32768);
	AssertTrue(bResult);
	AssertInt(2, uiLength);
	AssertString("\x81", acTestMemory);
	AssertFalse(cCache.IsSectorCached(62));
	AssertTrue(cCache.IsSectorCached(63));

	uiLength = 3;
	bResult = cCache.Read((uint8*)acTestMemory, 0, 0, 32767, &uiLength, 32769);
	AssertFalse(bResult);

	cCache.Kill();

	cMemoryDrive.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFatCacheComplex(void)
{
	CMemoryDrive	cMemoryDrive;
	CDiskFile		cFile;
	CFatCache		cCache;
	char*			acData;
	int				iDataLength;
	uint32			uiLength;
	bool			bIsZero = false;
	bool			bResult;
	char*			pcDriveMemory;
	char			acTestMemory[2 KB + 1];

	iDataLength = 65 KB;
	acData = FatCacheAllocateTestData(iDataLength);

	cMemoryDrive.Init(1 MB, 512);
	pcDriveMemory = (char*)cMemoryDrive.GetMemory();
	FatCacheFillTestDrive(pcDriveMemory, 256 KB);

	cCache.Init(&cMemoryDrive, 32 KB, 512);

	uiLength = 1 KB;
	bResult = cCache.Read((uint8*)acTestMemory, 1, 0, 677, &uiLength, 32 KB);
	AssertTrue(bResult);
	AssertInt(0, uiLength);

	uiLength = 333;
	bResult = cCache.Write((uint8*)acData, 1, 0, 439, &uiLength, 32 KB);
	AssertTrue(bResult);
	AssertInt(0, uiLength);
	AssertTrue(cCache.IsSectorCached(0));
	AssertTrue(cCache.IsSectorCached(1));
	AssertTrue(cCache.IsSectorCached(2));
	AssertTrue(cCache.IsSectorCached(3));
	AssertFalse(cCache.IsSectorCached(4));
	AssertTrue(cCache.IsSectorDirty(0));
	AssertTrue(cCache.IsSectorDirty(1));
	AssertFalse(cCache.IsSectorDirty(2));

	AssertString("\
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA!!!###$$$%%%&&&'''((()))***+++,,,---...///000111222333444555666777888999\
:::;;;<<<===>>>???@@@AAABBBCCCDDDEEEFFFGGGHHHIIIJJJKKKLLLMMMNNNOOOPPPQQQRRRSSSTTTUUUVVVWWWXXXYYYZZZ[[[]]]^^^___```aaabbbcccdddeeefffggghhhiiijjjkkklllmmmnnnooopppqqqrrrssstttuuuvvvwwwxxxyyyzzz{{{|||}}}~~~������������������������������������������������������BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBCCCCCCCCCCCCC\
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCDDDDDDDDDDDD\
DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD",
		(char*)cCache.GetCache());

	uiLength = 1 KB;
	bResult = cCache.Read((uint8*)acTestMemory, 1, 0, 0, &uiLength, 32 KB);
	AssertTrue(bResult);
	AssertInt(0, uiLength);

	acTestMemory[1 KB] = '\0';
	AssertString("\
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA!!!###$$$%%%&&&'''((()))***+++,,,---...///000111222333444555666777888999\
:::;;;<<<===>>>???@@@AAABBBCCCDDDEEEFFFGGGHHHIIIJJJKKKLLLMMMNNNOOOPPPQQQRRRSSSTTTUUUVVVWWWXXXYYYZZZ[[[]]]^^^___```aaabbbcccdddeeefffggghhhiiijjjkkklllmmmnnnooopppqqqrrrssstttuuuvvvwwwxxxyyyzzz{{{|||}}}~~~������������������������������������������������������BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
acTestMemory);

	uiLength = 2 KB;
	bResult = cCache.Read((uint8*)acTestMemory, 1, 0, 0, &uiLength, 32 KB);
	AssertTrue(bResult);
	AssertInt(0, uiLength);

	acTestMemory[2 KB] = '\0';
	AssertString("\
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA!!!###$$$%%%&&&'''((()))***+++,,,---...///000111222333444555666777888999\
:::;;;<<<===>>>???@@@AAABBBCCCDDDEEEFFFGGGHHHIIIJJJKKKLLLMMMNNNOOOPPPQQQRRRSSSTTTUUUVVVWWWXXXYYYZZZ[[[]]]^^^___```aaabbbcccdddeeefffggghhhiiijjjkkklllmmmnnnooopppqqqrrrssstttuuuvvvwwwxxxyyyzzz{{{|||}}}~~~������������������������������������������������������BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBCCCCCCCCCCCCC\
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCDDDDDDDDDDDD\
DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD",
acTestMemory);
	AssertTrue(cCache.IsSectorCached(0));
	AssertTrue(cCache.IsSectorCached(1));
	AssertTrue(cCache.IsSectorCached(2));
	AssertTrue(cCache.IsSectorCached(3));
	AssertFalse(cCache.IsSectorCached(4));
	AssertTrue(cCache.IsSectorDirty(0));
	AssertTrue(cCache.IsSectorDirty(1));
	AssertFalse(cCache.IsSectorDirty(2));

	uiLength = 1;
	bResult = cCache.Read((uint8*)acTestMemory, 0, 0, 477, &uiLength, 32 KB);
	AssertTrue(bResult);
	AssertInt(0, uiLength);
	AssertTrue(cCache.IsSectorCached(0));
	AssertFalse(cCache.IsSectorCached(1));
	AssertFalse(cCache.IsSectorCached(2));
	AssertFalse(cCache.IsSectorCached(3));
	AssertFalse(cCache.IsSectorCached(4));
	AssertFalse(cCache.IsSectorDirty(0));
	AssertFalse(cCache.IsSectorDirty(1));
	AssertFalse(cCache.IsSectorDirty(2));

	cCache.Kill();

	free(acData);

	cMemoryDrive.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFatCache(void)
{
	TypeConverterInit();
	BeginTests();

	TestFatCacheWrite();
	TestFatCacheDirty();
	TestFatCacheDiscontiguousWrites();
	TestFatCacheRead();
	TestFatCacheWriteLimits();
	TestFatCacheReadLimits();
	TestFatCacheComplex();

	TestStatistics();
	TypeConverterKill();
}

