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
void TestFatCacheStuff(void)
{
	CMemoryDrive			cMemoryDrive;
	CDiskFile				cFile;
	int						i;
	CFatCache				cCache;
	char*					pvData;
	int						iDataLength;
	uint32					uiLength;

	iDataLength = 65 KB;
	pvData = (char*)malloc(iDataLength);

	char c = 33;
	for (i = 0; i < iDataLength; i++)
	{
		pvData[i] = c;
		if (i % 3 == 2)
		{
			c++;
			if (c == 0)
			{
				c = 33;
			}
		}
	}
	cMemoryDrive.Init(1 MB, 512);
	cCache.Init(&cMemoryDrive, 32 KB, 512);
	cCache.Clear();

	uiLength = 3;
	cCache.Write((uint8*)pvData, 0, 0, 0, &uiLength, 0);
	uiLength = 3;
	cCache.Write((uint8*)&pvData[3], 0, 0, 2, &uiLength, 3);
	AssertString("!!\"\"\"", (char*)cCache.GetCache());

	uiLength = 511;
	cCache.Write((uint8*)pvData, 0, 0, 0, &uiLength, 3);
	AssertInt(511, strlen((char*)cCache.GetCache()));
	AssertString("!!!\"\"\"###$$$%%%&&&'''((()))***+++,,,---...///000111222333444555666777888999:::;;;<<<===>>>???@@@AAABBBCCCDDDEEEFFFGGGHHHIIIJJJKKKLLLMMMNNNOOOPPPQQQRRRSSSTTTUUUVVVWWWXXXYYYZZZ[[[\\\\\\]]]^^^___```aaabbbcccdddeeefffggghhhiiijjjkkklllmmmnnnooopppqqqrrrssstttuuuvvvwwwxxxyyyzzz{{{|||}}}~~~€€€‚‚‚ƒƒƒ„„„………†††‡‡‡ˆˆˆ‰‰‰ŠŠŠ‹‹‹ŒŒŒ‘‘‘’’’“““”””•••–––———˜˜˜™™™ššš›››œœœŸŸŸ   ¡¡¡¢¢¢£££¤¤¤¥¥¥¦¦¦§§§¨¨¨©©©ªªª«««¬¬¬­­­®®®¯¯¯°°°±±±²²²³³³´´´µµµ¶¶¶···¸¸¸¹¹¹ººº»»»¼¼¼½½½¾¾¾¿¿¿ÀÀÀÁÁÁÂÂÂÃÃÃÄÄÄÅÅÅÆÆÆÇÇÇÈÈÈÉÉÉÊÊÊË", 
		(char*)cCache.GetCache());

	uiLength = 1;
	cCache.Write((uint8*)pvData, 0, 0, 511, &uiLength, 511);
	AssertInt(512, strlen((char*)cCache.GetCache()));
	AssertString("!!!\"\"\"###$$$%%%&&&'''((()))***+++,,,---...///000111222333444555666777888999:::;;;<<<===>>>???@@@AAABBBCCCDDDEEEFFFGGGHHHIIIJJJKKKLLLMMMNNNOOOPPPQQQRRRSSSTTTUUUVVVWWWXXXYYYZZZ[[[\\\\\\]]]^^^___```aaabbbcccdddeeefffggghhhiiijjjkkklllmmmnnnooopppqqqrrrssstttuuuvvvwwwxxxyyyzzz{{{|||}}}~~~€€€‚‚‚ƒƒƒ„„„………†††‡‡‡ˆˆˆ‰‰‰ŠŠŠ‹‹‹ŒŒŒ‘‘‘’’’“““”””•••–––———˜˜˜™™™ššš›››œœœŸŸŸ   ¡¡¡¢¢¢£££¤¤¤¥¥¥¦¦¦§§§¨¨¨©©©ªªª«««¬¬¬­­­®®®¯¯¯°°°±±±²²²³³³´´´µµµ¶¶¶···¸¸¸¹¹¹ººº»»»¼¼¼½½½¾¾¾¿¿¿ÀÀÀÁÁÁÂÂÂÃÃÃÄÄÄÅÅÅÆÆÆÇÇÇÈÈÈÉÉÉÊÊÊË!",
		(char*)cCache.GetCache());

	uiLength = 512 + 256;
	cCache.Write((uint8*)pvData, 0, 0, 1, &uiLength, 512);
	AssertInt(512 + 256 + 1, strlen((char*)cCache.GetCache()));
	AssertString("!!!!\"\"\"###$$$%%%&&&'''((()))***+++,,,---...///000111222333444555666777888999:::;;;<<<===>>>???@@@AAABBBCCCDDDEEEFFFGGGHHHIIIJJJKKKLLLMMMNNNOOOPPPQQQRRRSSSTTTUUUVVVWWWXXXYYYZZZ[[[\\\\\\]]]^^^___```aaabbbcccdddeeefffggghhhiiijjjkkklllmmmnnnooopppqqqrrrssstttuuuvvvwwwxxxyyyzzz{{{|||}}}~~~€€€‚‚‚ƒƒƒ„„„………†††‡‡‡ˆˆˆ‰‰‰ŠŠŠ‹‹‹ŒŒŒ‘‘‘’’’“““”””•••–––———˜˜˜™™™ššš›››œœœŸŸŸ   ¡¡¡¢¢¢£££¤¤¤¥¥¥¦¦¦§§§¨¨¨©©©ªªª«««¬¬¬­­­®®®¯¯¯°°°±±±²²²³³³´´´µµµ¶¶¶···¸¸¸¹¹¹ººº»»»¼¼¼½½½¾¾¾¿¿¿ÀÀÀÁÁÁÂÂÂÃÃÃÄÄÄÅÅÅÆÆÆÇÇÇÈÈÈÉÉÉÊÊÊËËËÌÌÌÍÍÍÎÎÎÏÏÏĞĞĞÑÑÑÒÒÒÓÓÓÔÔÔÕÕÕÖÖÖ×××ØØØÙÙÙÚÚÚÛÛÛÜÜÜİİİŞŞŞßßßàààáááâââãããäääåååæææçççèèèéééêêêëëëìììíííîîîïïïğğğñññòòòóóóôôôõõõööö÷÷÷øøøùùùúúúûûûüüüııışşşÿÿÿ!!!\"\"\"###$$$%%%&&&'''((()))***+++,,,---...///000111222333444555666777888999:::;;;<<<===>>>???@@@AAA",
		(char*)cCache.GetCache());

	uiLength = 512 + 512 + 1;
	cCache.Write((uint8*)pvData, 0, 0, 16, &uiLength, 512 + 256 + 1);
	AssertInt(16 + 512 + 512 + 1, strlen((char*)cCache.GetCache()));
	AssertString("!!!!\"\"\"###$$$%%%!!!\"\"\"###$$$%%%&&&'''((()))***+++,,,---...///000111222333444555666777888999:::;;;<<<===>>>???@@@AAABBBCCCDDDEEEFFFGGGHHHIIIJJJKKKLLLMMMNNNOOOPPPQQQRRRSSSTTTUUUVVVWWWXXXYYYZZZ[[[\\\\\\]]]^^^___```aaabbbcccdddeeefffggghhhiiijjjkkklllmmmnnnooopppqqqrrrssstttuuuvvvwwwxxxyyyzzz{{{|||}}}~~~€€€‚‚‚ƒƒƒ„„„………†††‡‡‡ˆˆˆ‰‰‰ŠŠŠ‹‹‹ŒŒŒ‘‘‘’’’“““”””•••–––———˜˜˜™™™ššš›››œœœŸŸŸ   ¡¡¡¢¢¢£££¤¤¤¥¥¥¦¦¦§§§¨¨¨©©©ªªª«««¬¬¬­­­®®®¯¯¯°°°±±±²²²³³³´´´µµµ¶¶¶···¸¸¸¹¹¹ººº»»»¼¼¼½½½¾¾¾¿¿¿ÀÀÀÁÁÁÂÂÂÃÃÃÄÄÄÅÅÅÆÆÆÇÇÇÈÈÈÉÉÉÊÊÊËËËÌÌÌÍÍÍÎÎÎÏÏÏĞĞĞÑÑÑÒÒÒÓÓÓÔÔÔÕÕÕÖÖÖ×××ØØØÙÙÙÚÚÚÛÛÛÜÜÜİİİŞŞŞßßßàààáááâââãããäääåååæææçççèèèéééêêêëëëìììíííîîîïïïğğğñññòòòóóóôôôõõõööö÷÷÷øøøùùùúúúûûûüüüııışşşÿÿÿ!!!\"\"\"###$$$%%%&&&'''((()))***+++,,,---...///000111222333444555666777888999:::;;;<<<===>>>???@@@AAABBBCCCDDDEEEFFFGGGHHHIIIJJJKKKLLLMMMNNNOOOPPPQQQRRRSSSTTTUUUVVVWWWXXXYYYZZZ[[[\\\\\\]]]^^^___```aaabbbcccdddeeefffggghhhiiijjjkkklllmmmnnnooopppqqqrrrssstttuuuvvvwwwxxxyyyzzz{{{|||}}}~~~€€€‚‚‚ƒƒƒ„„„………†††‡‡‡ˆˆˆ‰‰‰ŠŠŠ‹‹‹ŒŒŒ‘‘‘’’’“““”””•••–––——",
		(char*)cCache.GetCache());

	uiLength = iDataLength;
	cCache.Write((uint8*)pvData, 0, 0, 0, &uiLength, 16 + 512 + 512 + 1);
	AssertMemory(pvData, cCache.GetCache(), 32768);
	cCache.Write((uint8*)&pvData[32768], 0, 0, 0, &uiLength, 0);
	AssertMemory((uint8*)&pvData[32768], cCache.GetCache(), 32768);
	cCache.Write((uint8*)&pvData[65536], 0, 0, 0, &uiLength, 0);
	AssertMemory((uint8*)&pvData[65536], cCache.GetCache(), 1024);

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

	TestFatCacheStuff();

	TestStatistics();
	TypeConverterKill();
}

