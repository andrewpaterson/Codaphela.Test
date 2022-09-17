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
void TestFatCacheWrite(void)
{
	CMemoryDrive			cMemoryDrive;
	CDiskFile				cFile;
	CFatCache				cCache;
	char*					pvData;
	int						iDataLength;
	uint32					uiLength;

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
	AssertString("!!!###$$$%%%&&&'''((()))***+++,,,---...///000111222333444555666777888999:::;;;<<<===>>>???@@@AAABBBCCCDDDEEEFFFGGGHHHIIIJJJKKKLLLMMMNNNOOOPPPQQQRRRSSSTTTUUUVVVWWWXXXYYYZZZ[[[]]]^^^___```aaabbbcccdddeeefffggghhhiiijjjkkklllmmmnnnooopppqqqrrrssstttuuuvvvwwwxxxyyyzzz{{{|||}}}~~~€€€‚‚‚ƒƒƒ„„„………†††‡‡‡ˆˆˆ‰‰‰ŠŠŠ‹‹‹ŒŒŒ‘‘‘’’’“““”””•••–––———˜˜˜™™™ššš›››œœœŸŸŸ   ¡¡¡¢¢¢£££¤¤¤¥¥¥¦¦¦§§§¨¨¨©©©ªªª«««¬¬¬­­­®®®¯¯¯°°°±±±²²²³³³´´´µµµ¶¶¶···¸¸¸¹¹¹ººº»»»¼¼¼½½½¾¾¾¿¿¿ÀÀÀÁÁÁÂÂÂÃÃÃÄÄÄÅÅÅÆÆÆÇÇÇÈÈÈÉÉÉÊÊÊËËËÌÌÌÍ", 
		(char*)cCache.GetCache());
	AssertTrue(cCache.IsSectorDirty(0));
	AssertTrue(cCache.IsSectorCached(0));
	AssertFalse(cCache.IsSectorDirty(1));
	AssertFalse(cCache.IsSectorCached(1));

	uiLength = 1;
	cCache.Write((uint8*)pvData, 0, 0, 511, &uiLength, 511);
	AssertInt(512, strlen((char*)cCache.GetCache()));
	AssertString("!!!###$$$%%%&&&'''((()))***+++,,,---...///000111222333444555666777888999:::;;;<<<===>>>???@@@AAABBBCCCDDDEEEFFFGGGHHHIIIJJJKKKLLLMMMNNNOOOPPPQQQRRRSSSTTTUUUVVVWWWXXXYYYZZZ[[[]]]^^^___```aaabbbcccdddeeefffggghhhiiijjjkkklllmmmnnnooopppqqqrrrssstttuuuvvvwwwxxxyyyzzz{{{|||}}}~~~€€€‚‚‚ƒƒƒ„„„………†††‡‡‡ˆˆˆ‰‰‰ŠŠŠ‹‹‹ŒŒŒ‘‘‘’’’“““”””•••–––———˜˜˜™™™ššš›››œœœŸŸŸ   ¡¡¡¢¢¢£££¤¤¤¥¥¥¦¦¦§§§¨¨¨©©©ªªª«««¬¬¬­­­®®®¯¯¯°°°±±±²²²³³³´´´µµµ¶¶¶···¸¸¸¹¹¹ººº»»»¼¼¼½½½¾¾¾¿¿¿ÀÀÀÁÁÁÂÂÂÃÃÃÄÄÄÅÅÅÆÆÆÇÇÇÈÈÈÉÉÉÊÊÊËËËÌÌÌÍ!",
		(char*)cCache.GetCache());
	AssertTrue(cCache.IsSectorDirty(0));
	AssertTrue(cCache.IsSectorCached(0));
	AssertFalse(cCache.IsSectorDirty(1));
	AssertFalse(cCache.IsSectorCached(1));

	uiLength = 512 + 256;
	cCache.Write((uint8*)pvData, 0, 0, 1, &uiLength, 512);
	AssertInt(512 + 256 + 1, strlen((char*)cCache.GetCache()));
	AssertString("!!!!###$$$%%%&&&'''((()))***+++,,,---...///000111222333444555666777888999:::;;;<<<===>>>???@@@AAABBBCCCDDDEEEFFFGGGHHHIIIJJJKKKLLLMMMNNNOOOPPPQQQRRRSSSTTTUUUVVVWWWXXXYYYZZZ[[[]]]^^^___```aaabbbcccdddeeefffggghhhiiijjjkkklllmmmnnnooopppqqqrrrssstttuuuvvvwwwxxxyyyzzz{{{|||}}}~~~€€€‚‚‚ƒƒƒ„„„………†††‡‡‡ˆˆˆ‰‰‰ŠŠŠ‹‹‹ŒŒŒ‘‘‘’’’“““”””•••–––———˜˜˜™™™ššš›››œœœŸŸŸ   ¡¡¡¢¢¢£££¤¤¤¥¥¥¦¦¦§§§¨¨¨©©©ªªª«««¬¬¬­­­®®®¯¯¯°°°±±±²²²³³³´´´µµµ¶¶¶···¸¸¸¹¹¹ººº»»»¼¼¼½½½¾¾¾¿¿¿ÀÀÀÁÁÁÂÂÂÃÃÃÄÄÄÅÅÅÆÆÆÇÇÇÈÈÈÉÉÉÊÊÊËËËÌÌÌÍÍÍÎÎÎÏÏÏĞĞĞÑÑÑÒÒÒÓÓÓÔÔÔÕÕÕÖÖÖ×××ØØØÙÙÙÚÚÚÛÛÛÜÜÜİİİŞŞŞßßßàààáááâââãããäääåååæææçççèèèéééêêêëëëìììíííîîîïïïğğğñññòòòóóóôôôõõõööö÷÷÷øøøùùùúúúûûûüüüııışşşÿÿÿ!!!###$$$%%%&&&'''((()))***+++,,,---...///000111222333444555666777888999:::;;;<<<===>>>???@@@AAABBBCCCDDD",
		(char*)cCache.GetCache());

	uiLength = 512 + 512 + 1;
	cCache.Write((uint8*)pvData, 0, 0, 16, &uiLength, 512 + 256 + 1);
	AssertInt(16 + 512 + 512 + 1, strlen((char*)cCache.GetCache()));
	AssertString("!!!!###$$$%%%&&&!!!###$$$%%%&&&'''((()))***+++,,,---...///000111222333444555666777888999:::;;;<<<===>>>???@@@AAABBBCCCDDDEEEFFFGGGHHHIIIJJJKKKLLLMMMNNNOOOPPPQQQRRRSSSTTTUUUVVVWWWXXXYYYZZZ[[[]]]^^^___```aaabbbcccdddeeefffggghhhiiijjjkkklllmmmnnnooopppqqqrrrssstttuuuvvvwwwxxxyyyzzz{{{|||}}}~~~€€€‚‚‚ƒƒƒ„„„………†††‡‡‡ˆˆˆ‰‰‰ŠŠŠ‹‹‹ŒŒŒ‘‘‘’’’“““”””•••–––———˜˜˜™™™ššš›››œœœŸŸŸ   ¡¡¡¢¢¢£££¤¤¤¥¥¥¦¦¦§§§¨¨¨©©©ªªª«««¬¬¬­­­®®®¯¯¯°°°±±±²²²³³³´´´µµµ¶¶¶···¸¸¸¹¹¹ººº»»»¼¼¼½½½¾¾¾¿¿¿ÀÀÀÁÁÁÂÂÂÃÃÃÄÄÄÅÅÅÆÆÆÇÇÇÈÈÈÉÉÉÊÊÊËËËÌÌÌÍÍÍÎÎÎÏÏÏĞĞĞÑÑÑÒÒÒÓÓÓÔÔÔÕÕÕÖÖÖ×××ØØØÙÙÙÚÚÚÛÛÛÜÜÜİİİŞŞŞßßßàààáááâââãããäääåååæææçççèèèéééêêêëëëìììíííîîîïïïğğğñññòòòóóóôôôõõõööö÷÷÷øøøùùùúúúûûûüüüııışşşÿÿÿ!!!###$$$%%%&&&'''((()))***+++,,,---...///000111222333444555666777888999:::;;;<<<===>>>???@@@AAABBBCCCDDDEEEFFFGGGHHHIIIJJJKKKLLLMMMNNNOOOPPPQQQRRRSSSTTTUUUVVVWWWXXXYYYZZZ[[[]]]^^^___```aaabbbcccdddeeefffggghhhiiijjjkkklllmmmnnnooopppqqqrrrssstttuuuvvvwwwxxxyyyzzz{{{|||}}}~~~€€€‚‚‚ƒƒƒ„„„………†††‡‡‡ˆˆˆ‰‰‰ŠŠŠ‹‹‹ŒŒŒ‘‘‘’’’“““”””•••–––———˜˜˜™™™ššš››",
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
	CMemoryDrive			cMemoryDrive;
	CDiskFile				cFile;
	CFatCache				cCache;
	char*					pvData;
	int						iDataLength;
	uint32					uiLength;

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
	CMemoryDrive			cMemoryDrive;
	CDiskFile				cFile;
	CFatCache				cCache;
	char*					pvData;
	int						iDataLength;
	uint32					uiLength;
	char*					pcMemory;
	int						iStart;
	int						i;
	int						iZeroIndex;
	int						iNonZeroIndex;
	int						aiZeroIndices[16];
	int						aiNonZeroIndices[16];
	bool					bIsZero = false;

	iDataLength = 65 KB;
	pvData = FatCacheAllocateTestData(iDataLength);

	cMemoryDrive.Init(1 MB, 512);
	cCache.Init(&cMemoryDrive, 32 KB, 512);
	cMemoryDrive.Erase(0, cCache.GetSectorsPerCluster() - 1);

	uiLength = 512 * 2;
	cCache.Write((uint8*)pvData, 0, 0, 512, &uiLength, 512);

	uiLength = 512 * 3;
	cCache.Write((uint8*)pvData, 0, 0, 512 * 5, &uiLength, 512 * 4);

	uiLength = 512;
	cCache.Write((uint8*)pvData, 0, 0, 512 * 11, &uiLength, 512 * 10);

	uiLength = 512;
	cCache.Write((uint8*)pvData, 0, 0, 512 * 13, &uiLength, 512 * 12);

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
void TestFatCache(void)
{
	TypeConverterInit();
	BeginTests();

	TestFatCacheWrite();
	TestFatCacheDirty();
	TestFatCacheDiscontiguousWrites();

	TestStatistics();
	TypeConverterKill();
}

