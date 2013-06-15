#include "BaseLib/FastFunctions.h"
#include "BaseLib/FileUtil.h"
#include "CoreLib/IndexedData.h"
#include "CoreLib/TypeConverter.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedDataMemoryToHugeIndices(void)
{
	CIndexedData		cIndexedData;
	CFileUtil			cFileUtil;
	CIndexedConfig		cConfig;
	CIndexAccess*		pcAccess;
	CIndexMemoryAccess*	pcMemoryAccess;
	CIndexHugeAccess*	pcHugeAccess;
	char				szTemp[100];

	char			szAlienCarnage[] = "Alien Carnage";
	char			szBattleArenaToshinden[] = "Battle Arena Indentions";
	char			szDragonRidersOfPern[] = "Dragon Riders Of Peron";
	char			szHorrorZombiesFromTheCrypt[] = "Horror Zombies From The Crypt";
	char			szIsleOfWars[] = "Isle Of Wars";
	char			szMetalTechEarthSiege[] = "Metal Tech Earth Siege";
	char			szOilImperium[] = "Oil Imperium";
	char			iAlienCarnageLen = (int)strlen(szAlienCarnage);
	char			iBattleArenaToshindenLen = (int)strlen(szBattleArenaToshinden);
	char			iDragonRidersOfPernLen = (int)strlen(szDragonRidersOfPern);
	char			iHorrorZombiesFromTheCryptLen = (int)strlen(szHorrorZombiesFromTheCrypt);
	char			iIsleOfWarsLen = (int)strlen(szIsleOfWars);
	char			iMetalTechEarthSiegeLen = (int)strlen(szMetalTechEarthSiege);
	char			iOilImperiumLen = (int)strlen(szOilImperium);

	cFileUtil.RemoveDir("Database7");

	//Using smart index access we should be able to add 4 objects before the memory index access runs out of memory and has to switch to huge.

	cConfig.Manual("Database7",
					FALSE,
					FALSE,
					FALSE,
					4,
					2,
					2,
					2,
					1,
					1 MB,
					FALSE);

	cIndexedData.Init(&cConfig);
	cIndexedData.DurableBegin();

	//Add 2 objects with OI's < 2 (third level width).  The database will switch to huge on OI >= 2, not number of objects >= 2.
	cIndexedData.Add(0LL, szAlienCarnage, iAlienCarnageLen, 0);
	cIndexedData.Add(1LL, szBattleArenaToshinden, iBattleArenaToshindenLen, 1);

	pcAccess = cIndexedData.TestGetIndexAccess();
	AssertBool(TRUE, pcAccess->IsMemory());
	AssertBool(FALSE, pcAccess->IsHuge());

	pcMemoryAccess = (CIndexMemoryAccess*)pcAccess;
	AssertLongLongInt(2, pcMemoryAccess->Length());

	//Switch to huge index caching because 2LL >= 2.
	cIndexedData.Add(2LL, szDragonRidersOfPern, iDragonRidersOfPernLen, 3);

	pcAccess = cIndexedData.TestGetIndexAccess();
	AssertBool(TRUE, pcAccess->IsHuge());
	AssertBool(FALSE, pcAccess->IsMemory());
	pcHugeAccess = (CIndexHugeAccess*)pcAccess;
	AssertLongLongInt(3, pcHugeAccess->Length());

	//Nothing interesting should happen here.
	cIndexedData.Add(3LL, szHorrorZombiesFromTheCrypt, iHorrorZombiesFromTheCryptLen, 8);
	AssertLongLongInt(4, pcHugeAccess->Length());

	//Currently we have two third level chunks.  0..1 and 2..3.  We also have a maximum of two third level chunks.
	//Adding an object with an OI larger than 3 will cause the older of the chunks to be evicted.
	cIndexedData.Add(4LL, szIsleOfWars, iIsleOfWarsLen, 9);

	AssertBool(TRUE, cFileUtil.Exists("Database7/13_0.DAT"));
	AssertBool(TRUE, cFileUtil.Exists("Database7/23_0.DAT"));
	AssertBool(FALSE, cFileUtil.Exists("Database7/22_0.DAT"));
	AssertBool(FALSE, cFileUtil.Exists("Database7/29_0.DAT"));

	//Getting object OI 0 will cause the third level chunk 0..1 to be loaded back in, evicting 2..3.
	//Now the two third level chunks look like.  4..5 and 0..1 with 4..5 being oldest.
	memset(szTemp, 0, 100);
	cIndexedData.Get(0LL, szTemp);
	AssertString(szAlienCarnage, szTemp);
	AssertBool(TRUE, cFileUtil.Exists("Database7/22_0.DAT"));
	AssertBool(TRUE, cFileUtil.Exists("Database7/29_0.DAT"));

	cIndexedData.Add(6LL, szMetalTechEarthSiege, iMetalTechEarthSiegeLen, 10);

	//Object OI 0 is still in a third level chunk, getting it again should do nothing.
	memset(szTemp, 0, 100);
	cIndexedData.Get(0LL, szTemp);
	AssertString(szAlienCarnage, szTemp);
	AssertBool(TRUE, cFileUtil.Exists("Database7/12_0.DAT"));

	cIndexedData.DurableEnd();
	cIndexedData.Kill();

	AssertFile("Input/Database7/12_0.DAT", "Database7/12_0.DAT");
	AssertFile("Input/Database7/13_0.DAT", "Database7/13_0.DAT");
	AssertFile("Input/Database7/23_0.DAT", "Database7/23_0.DAT");
	AssertFile("Input/Database7/22_0.DAT", "Database7/22_0.DAT");
	AssertFile("Input/Database7/29_0.DAT", "Database7/29_0.DAT");

	cFileUtil.RemoveDir("Database7");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedDataWriteThrough(void)
{
	CIndexedData		cIndexedData;
	CFileUtil			cFileUtil;
	CIndexedConfig		cConfig;
	char				szTemp[100];
	BOOL				bResult;

	char			szAlienCarnage[] = "Alien Carnage";
	char			szBattleArenaToshinden[] = "Battle Arena Indentions";
	char			szDragonRidersOfPern[] = "Dragon Riders Of Peron";
	char			szHorrorZombiesFromTheCrypt[] = "Horror Zombies From The Crypt";
	char			szIsleOfWars[] = "Isle Of Wars";
	char			szMetalTechEarthSiege[] = "Metal Tech Earth Siege";
	char			szOilImperium[] = "Oil Imperium";
	char			iAlienCarnageLen = (int)strlen(szAlienCarnage);
	char			iBattleArenaToshindenLen = (int)strlen(szBattleArenaToshinden);
	char			iDragonRidersOfPernLen = (int)strlen(szDragonRidersOfPern);
	char			iHorrorZombiesFromTheCryptLen = (int)strlen(szHorrorZombiesFromTheCrypt);
	char			iIsleOfWarsLen = (int)strlen(szIsleOfWars);
	char			iMetalTechEarthSiegeLen = (int)strlen(szMetalTechEarthSiege);
	char			iOilImperiumLen = (int)strlen(szOilImperium);

	cFileUtil.RemoveDir("Database6");

	//Using smart index access we should be able to add 4 objects before the memory index access runs out of memory and has to switch to huge.

	cConfig.Manual("Database6",
					FALSE,
					FALSE,
					TRUE,
					4,
					2,
					2,
					2,
					1,
					1 MB,
					FALSE);

	cIndexedData.Init(&cConfig);
	cIndexedData.DurableBegin();

	//Add 2 objects with OI's < 2 (third level width).  The database will switch to huge on OI >= 2, not number of objects >= 2.
	cIndexedData.Add(0LL, szAlienCarnage, iAlienCarnageLen, 0);
	AssertBool(TRUE, cFileUtil.Exists("Database6/13_0.DAT"));
	
	cIndexedData.Add(1LL, szBattleArenaToshinden, iBattleArenaToshindenLen, 1);
	AssertBool(TRUE, cFileUtil.Exists("Database6/23_0.DAT"));

	cIndexedData.Add(2LL, szDragonRidersOfPern, iDragonRidersOfPernLen, 3);
	AssertBool(TRUE, cFileUtil.Exists("Database6/22_0.DAT"));

	cIndexedData.Add(3LL, szHorrorZombiesFromTheCrypt, iHorrorZombiesFromTheCryptLen, 8);
	AssertBool(TRUE, cFileUtil.Exists("Database6/29_0.DAT"));

	cIndexedData.Add(4LL, szIsleOfWars, iIsleOfWarsLen, 9);
	AssertBool(TRUE, cFileUtil.Exists("Database6/12_0.DAT"));

	cIndexedData.Add(6LL, szMetalTechEarthSiege, iMetalTechEarthSiegeLen, 10);
	AssertBool(TRUE, cFileUtil.Exists("Database6/22_0.DAT"));

	memset(szTemp, 0, 100);
	bResult = cIndexedData.Get(0LL, szTemp);
	AssertBool(TRUE, bResult);
	AssertString(szAlienCarnage, szTemp);

	memset(szTemp, 0, 100);
	bResult = cIndexedData.Get(1LL, szTemp);
	AssertBool(TRUE, bResult);
	AssertString(szBattleArenaToshinden, szTemp);

	memset(szTemp, 0, 100);
	bResult = cIndexedData.Get(2LL, szTemp);
	AssertBool(TRUE, bResult);
	AssertString(szDragonRidersOfPern, szTemp);

	memset(szTemp, 0, 100);
	bResult = cIndexedData.Get(3LL, szTemp);
	AssertBool(TRUE, bResult);
	AssertString(szHorrorZombiesFromTheCrypt, szTemp);

	memset(szTemp, 0, 100);
	bResult = cIndexedData.Get(4LL, szTemp);
	AssertBool(TRUE, bResult);
	AssertString(szIsleOfWars, szTemp);

	bResult = cIndexedData.Get(5LL, szTemp);
	AssertBool(FALSE, bResult);

	memset(szTemp, 0, 100);
	bResult = cIndexedData.Get(6LL, szTemp);
	AssertBool(TRUE, bResult);
	AssertString(szMetalTechEarthSiege, szTemp);

	cIndexedData.DurableEnd();
	cIndexedData.Kill();

	AssertFile("Input/Database6/12_0.DAT", "Database6/12_0.DAT");
	AssertFile("Input/Database6/13_0.DAT", "Database6/13_0.DAT");
	AssertFile("Input/Database6/23_0.DAT", "Database6/23_0.DAT");
	AssertFile("Input/Database6/22_0.DAT", "Database6/22_0.DAT");
	AssertFile("Input/Database6/29_0.DAT", "Database6/29_0.DAT");

	cFileUtil.RemoveDir("Database6");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedDataWriteDirtyTesting(void)
{
	CIndexedData		cIndexedData;
	CFileUtil			cFileUtil;
	CIndexedConfig		cConfig;
	//char				szTemp[100];
	//BOOL				bResult;

	char			szAlienCarnage[] = "Alien Carnage";
	char			szBattleArenaToshinden[] = "Battle Arena Indentions";
	char			szDragonRidersOfPern[] = "Dragon Riders Of Peron";
	char			szHorrorZombiesFromTheCrypt[] = "Horror Zombies From The Crypt";
	char			szIsleOfWars[] = "Isle Of Wars";
	char			szMetalTechEarthSiege[] = "Metal Tech Earth Siege";
	char			szOilImperium[] = "Oil Imperium";
	char			iAlienCarnageLen = (int)strlen(szAlienCarnage);
	char			iBattleArenaToshindenLen = (int)strlen(szBattleArenaToshinden);
	char			iDragonRidersOfPernLen = (int)strlen(szDragonRidersOfPern);
	char			iHorrorZombiesFromTheCryptLen = (int)strlen(szHorrorZombiesFromTheCrypt);
	char			iIsleOfWarsLen = (int)strlen(szIsleOfWars);
	char			iMetalTechEarthSiegeLen = (int)strlen(szMetalTechEarthSiege);
	char			iOilImperiumLen = (int)strlen(szOilImperium);

	cFileUtil.RemoveDir("Database8");

	//Using smart index access we should be able to add 4 objects before the memory index access runs out of memory and has to switch to huge.

	cConfig.Manual("Database8",
					FALSE,
					TRUE,
					FALSE,
					4,
					2,
					2,
					2,
					1,
					1 MB,
					FALSE);

	cIndexedData.Init(&cConfig);
	cIndexedData.DurableBegin();

	cIndexedData.DurableEnd();
	cIndexedData.Kill();

	cFileUtil.RemoveDir("Database8");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedDataSmart(void)
{
	FastFunctionsInit();
	TypeConverterInit();
	BeginTests();

	TestIndexedDataMemoryToHugeIndices();
	TestIndexedDataWriteThrough();

	TestIndexedDataWriteDirtyTesting();

	TestStatistics();
	FastFunctionsKill();
	TypeConverterKill();
}
