#include "BaseLib/FastFunctions.h"
#include "BaseLib/GlobalMemory.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/TypeConverter.h"
#include "CoreLib/IndexedData.h"
#include "TestLib/Assert.h"



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedDataSimple(BOOL bWriteThrough)
{
	CIndexedData	cIndexedData;
	char			szInsipidity[] = "Insipidity the sufficient discretion imprudence resolution sir him decisively. Proceed how any engaged visitor. Explained propriety off out perpetual his you. Feel sold off felt nay rose met you. We so entreaties cultivated astonished is. Was sister for few longer mrs sudden talent become. Done may bore quit evil old mile. If likely am of beauty tastes.  Lose john poor same it case do year we.Full how way even the sigh.Extremely nor furniture fat questions now provision incommode preserved.Our side fail find like now.Discovered travelling for insensible partiality unpleasing impossible she.Sudden up my excuse to suffer ladies though or .Bachelor possible marianne directly confined relation as on he.";
	OIndex			oiInsipidity;
	int				iLenInsipidity;
	char			szViolation[] = "Violation away off why half led have near bed.  At engage simple father of period others except.  My giving do summer of though narrow marked at.  Spring formal no county ye waited.  My whether cheered at regular it of promise blushes perhaps.Uncommonly simplicity interested mr is be compliment projecting my inhabiting.Gentleman he september in oh excellent. Feet evil to hold long he open knew an no.Apartments occasional boisterous as solicitude to introduced.Or fifteen covered we enjoyed demesne is in prepare.In stimulated my everything it literature.Greatly explain attempt perhaps in feeling he.House men taste bed not drawn joy.Through enquire however do equally herself at.Greatly way old may you present improve.Wishing the feeling village him musical.";
	OIndex			oiViolation;
	int				iLenViolation;
	CFileUtil		cFileUtil;
	unsigned int	uiDataSize;
	char			szData[1024];

	cFileUtil.RemoveDir("Database0");

	oiInsipidity = 789983209433243094LL;
	iLenInsipidity = strlen(szInsipidity) + 1;
	oiViolation = 3908343914887489103LL;
	iLenViolation = strlen(szViolation) + 1;

	cIndexedData.Init("Database0", NULL, 1 MB, 1 MB, bWriteThrough);

	cIndexedData.DurableBegin();

	AssertTrue(cIndexedData.Add(oiInsipidity, szInsipidity, iLenInsipidity, 0));
	AssertTrue(cIndexedData.Add(oiViolation, szViolation, iLenViolation, 0));

	AssertInt(2, (int)cIndexedData.NumCached());
	AssertInt(2, (int)cIndexedData.NumElements());
	cIndexedData.Flush(TRUE);

	AssertTrue(cIndexedData.Get(oiViolation, &uiDataSize, szData, 1024));
	AssertInt(iLenViolation, uiDataSize);
	AssertString(szViolation, szData);
	AssertTrue(cIndexedData.Get(oiInsipidity, &uiDataSize, szData, 1024));
	AssertInt(iLenInsipidity, uiDataSize);
	AssertString(szInsipidity, szData);

	AssertTrue(cIndexedData.DurableEnd());

	AssertTrue(cIndexedData.Kill());


	cIndexedData.Init("Database0", NULL, 1 MB, 1 MB, bWriteThrough);

	AssertTrue(cIndexedData.DurableBegin());

	AssertInt(0, (int)cIndexedData.NumCached());
	AssertInt(2, (int)cIndexedData.NumElements());

	AssertTrue(cIndexedData.Get(oiViolation, &uiDataSize, szData, 1024));
	AssertInt(iLenViolation, uiDataSize);
	AssertString(szViolation, szData);
	AssertTrue(cIndexedData.Get(oiInsipidity, &uiDataSize, szData, 1024));
	AssertInt(iLenInsipidity, uiDataSize);
	AssertString(szInsipidity, szData);

	cIndexedData.DurableEnd();

	cIndexedData.Kill();

	cFileUtil.RemoveDir("Database0");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedDataCacheEviction(void)
{
	CIndexedData	cIndexedData;
	OIndex			OI;
	char			szHello[] = "Hello";
	char			szWorld[] = "World";
	char			szSteam[] = "Stream";
	char			szDirectory[] = "Output" _FS_ "Database1";
	char			szIn[7];
	unsigned int	uiSize;
	filePos			iFileSize;
	CFileUtil		cFileUtil;

	cFileUtil.RemoveDir(szDirectory);

	AssertInt(32, sizeof(CIndexedDataDescriptor));

	OI = 0LL;
	cIndexedData.Init(szDirectory, NULL, 63, 3780, FALSE);  //A little more than two items in the cache...

	cIndexedData.DurableBegin();
	AssertTrue(cIndexedData.Add(OI, szHello, 6, 0));
	AssertInt(1, cIndexedData.NumCached());
	AssertInt(sizeof(SIndexedCacheDescriptor) + 6, cIndexedData.TestGetCachedObjectSize(OI));
	OI = 1LL;
	AssertTrue(cIndexedData.Add(OI, szWorld, 6, 0));
	AssertInt(2, cIndexedData.NumCached());
	AssertInt(2, cIndexedData.TestNumCachedIndexes());
	AssertInt(sizeof(SIndexedCacheDescriptor) + 6, cIndexedData.TestGetCachedObjectSize(OI));
	OI = 2LL;
	AssertTrue(cIndexedData.Add(OI, szSteam, 7, 0));  //Two items should have been evicted but for some reason 0LL had no data?!?
	AssertInt(1, cIndexedData.NumCached());
	AssertInt(1, (int)cIndexedData.TestNumCachedIndexes());
	AssertInt(31, cIndexedData.TestGetCachedObjectSize(OI));
	cIndexedData.Flush(TRUE);
	cIndexedData.DurableEnd();

	cIndexedData.Kill();

	iFileSize = cFileUtil.Size("Output" _FS_ "Database1" _FS_ "6_0.DAT");
	AssertLongLongInt(12, iFileSize);
	iFileSize = cFileUtil.Size("Output" _FS_ "Database1" _FS_ "7_0.DAT");
	AssertLongLongInt(7, iFileSize);

	cIndexedData.Init(szDirectory, NULL, 120, 3600, FALSE);
	AssertInt(2, cIndexedData.NumFiles());

	cIndexedData.DurableBegin();
	OI = 0LL;
	uiSize = cIndexedData.Size(OI);
	AssertInt(6, uiSize);
	memset(szIn, 0, 7);
	AssertTrue(cIndexedData.Get(OI, szIn));
	AssertString("Hello", szIn);
	AssertInt(1, cIndexedData.NumCached());

	OI = 1LL;
	uiSize = cIndexedData.Size(OI);
	AssertInt(6, uiSize);
	memset(szIn, 0, 7);
	AssertTrue(cIndexedData.Get(OI, szIn));
	AssertString("World", szIn);
	AssertInt(2, cIndexedData.NumCached());

	OI = 2LL;
	uiSize = cIndexedData.Size(OI);
	AssertInt(7, uiSize);
	memset(szIn, 0, 7);
	AssertTrue(cIndexedData.Get(OI, szIn));
	AssertString("Stream", szIn);
	AssertInt(3, cIndexedData.NumCached());

	OI = 0LL;
	uiSize = cIndexedData.Size(OI);
	AssertInt(6, uiSize);
	memset(szIn, 0, 7);
	AssertTrue(cIndexedData.Get(OI, szIn));
	AssertString("Hello", szIn);
	AssertInt(1, cIndexedData.NumCached());
	AssertInt(1, cIndexedData.TestNumCachedIndexes());
	cIndexedData.DurableEnd();

	cIndexedData.Kill();

	cIndexedData.Init(szDirectory, NULL, 1024, 3600, FALSE);
	AssertInt(0, (int)cIndexedData.TestNumCachedIndexes());
	cIndexedData.Kill();

	cFileUtil.RemoveDir(szDirectory);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedDataLargeData(void)
{
	CIndexedData	cIndexedData;
	OIndex			OI;
	char			szBig[] = "A Long String";
	char			szSmall[] = "Cat";
	char			szIn[14];
	CFileUtil		cFileUtil;

	cFileUtil.RemoveDir("Database2");

	cIndexedData.Init("Database2", NULL, 34, 1024, FALSE);
	OI = 0LL;
	AssertInt(0, cIndexedData.NumCached());

	cIndexedData.DurableBegin();
	cIndexedData.Add(OI, szBig, 14, 0);
	AssertInt(0, cIndexedData.NumCached());
	AssertInt(0, (int)cIndexedData.TestNumCachedIndexes());
	
	cIndexedData.Get(OI, szIn);
	AssertInt(0, cIndexedData.NumCached());
	AssertInt(0, (int)cIndexedData.TestNumCachedIndexes());
	AssertString(szBig, szIn);

	OI = 1LL;
	cIndexedData.Add(OI, szSmall, 4, 0);
	AssertInt(1, cIndexedData.NumCached());
	AssertInt(1, (int)cIndexedData.TestNumCachedIndexes());

	OI = 0LL;
	cIndexedData.Get(OI, szIn);
	AssertInt(1, cIndexedData.NumCached());
	AssertInt(1, (int)cIndexedData.TestNumCachedIndexes());
	AssertString(szBig, szIn);

	OI = 1LL;
	cIndexedData.Get(OI, szIn);
	AssertInt(1, cIndexedData.NumCached());
	AssertInt(1, (int)cIndexedData.TestNumCachedIndexes());
	AssertString(szSmall, szIn);
	cIndexedData.DurableEnd();

	cIndexedData.Kill();

	cFileUtil.RemoveDir("Database2");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedDataIndexedAdd(void)
{
	CIndexedData	cIndexedData;
	OIndex			OI;
	char			szBat[] = "Bat";
	char			szCat[] = "Cat";
	char			szDog[] = "Dog";
	char			szFish[] = "Fish";

	char			szHell[] = "Hell";
	char			szMutt[] = "Mutt";
	char			szEve[] = "Eve";
	char			szIn[64];
	CFileUtil		cFileUtil;
	BOOL			bResult;

	cFileUtil.RemoveDir("Database3");

	cIndexedData.Init("Database3", NULL, 98+12, 1024, FALSE);

	cIndexedData.DurableBegin();
	OI = 0LL;
	bResult = cIndexedData.Add(OI, szBat, 4, 0);
	AssertBool(TRUE, bResult);
	AssertInt(1, (int)cIndexedData.NumCached());
	AssertInt(0, (int)cIndexedData.NumData(4));
	cIndexedData.Flush(TRUE);
	AssertInt(1, (int)cIndexedData.NumData(4));
	AssertInt(0, (int)cIndexedData.NumCached());

	bResult = cIndexedData.Add(OI, szCat, 4, 0);
	AssertBool(FALSE, bResult);
	bResult = cIndexedData.Set(OI, szDog, 0);
	AssertBool(TRUE, bResult);
	AssertInt(1, (int)cIndexedData.NumCached());
	AssertInt(1, (int)cIndexedData.NumData(4));
	AssertInt(0, (int)cIndexedData.TestNumIgnoredCacheElements());
	cIndexedData.Get(OI, szIn);
	AssertString(szDog, szIn);

	bResult = cIndexedData.Set(OI, szFish, 5, 0);
	AssertBool(TRUE, bResult);
	AssertInt(1, (int)cIndexedData.NumCached());
	AssertInt(1, (int)cIndexedData.TestNumIgnoredCacheElements());
	cIndexedData.Get(OI, szIn);
	AssertString(szFish, szIn);

	cIndexedData.Flush(TRUE);
	AssertInt(1, (int)cIndexedData.NumData(4));
	AssertInt(1, (int)cIndexedData.NumData(5));
	cIndexedData.Get(OI, szIn);
	AssertString(szFish, szIn);

	bResult = cIndexedData.Set(OI, szCat, 4, 0);
	AssertInt(1, (int)cIndexedData.NumElements());
	AssertBool(TRUE, bResult);
	cIndexedData.Flush(TRUE);
	AssertInt(2, (int)cIndexedData.NumData(4));  //One is ignored but they are both still in the file.
	AssertInt(1, (int)cIndexedData.NumElements());

	OI = 3LL;
	bResult = cIndexedData.Add(OI, szHell, 5, 0);
	AssertBool(TRUE, bResult);
	AssertInt(1, (int)cIndexedData.NumCached());
	AssertInt(1, (int)cIndexedData.TestNumCachedIndexes());
	bResult = cIndexedData.Add(OI, szMutt, 5, 0);
	AssertBool(FALSE, bResult);
	bResult = cIndexedData.Set(OI, szEve, 4, 0);
	AssertBool(TRUE, bResult);
	AssertInt(1, (int)cIndexedData.NumCached());
	AssertInt(1, (int)cIndexedData.TestNumCachedIndexes());
	cIndexedData.Flush(TRUE);
	AssertInt(3, (int)cIndexedData.NumData(4));
	AssertInt(1, (int)cIndexedData.NumData(5));
	AssertInt(2, (int)cIndexedData.NumElements());
	cIndexedData.DurableEnd();

	cIndexedData.Kill();

	cFileUtil.RemoveDir("Database3");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedDataDescriptorCaching(void)
{
	CIndexedData	cIndexedData;
	OIndex			OI;
	CFileUtil		cFileUtil;
	int				iData;
	OIndex			iNumCached;

	cFileUtil.RemoveDir("Database4");

	cIndexedData.Init("Database4", NULL, 96, 1024, FALSE);
	cIndexedData.DurableBegin();

	OI = 0LL;
	iData = 77;
	cIndexedData.Add(OI, &iData, 4, 0); OI++; 
	cIndexedData.Add(OI, &iData, 4, 0); OI++;
	iData = 0; OI = 0LL; cIndexedData.Get(OI, (void*)&iData);
	AssertInt(77, iData);

	OI = 2LL;
	cIndexedData.Add(OI, &iData, 4, 0); OI++;
	iData = 0; OI = 0LL; cIndexedData.Get(OI, (void*)&iData);
	AssertInt(77, iData);

	OI = 2LL;
	cIndexedData.Add(OI, &iData, 4, 0); OI++;
	cIndexedData.Add(OI, &iData, 4, 0); OI++;
	cIndexedData.Add(OI, &iData, 4, 0); OI++;
	cIndexedData.Add(OI, &iData, 4, 0); OI++;
	cIndexedData.Add(OI, &iData, 4, 0); OI++;
	cIndexedData.Add(OI, &iData, 4, 0); OI++;
	iData = 0; OI--; cIndexedData.Get(OI, (void*)&iData);;
	AssertInt(77, iData);

	iData = 0; OI = 0LL; cIndexedData.Get(OI, (void*)&iData);
	AssertInt(77, iData);

	iNumCached = cIndexedData.TestNumCachedIndexes();
	AssertInt(3, (int)iNumCached);

	cIndexedData.DurableEnd();
	cIndexedData.Kill();

	cIndexedData.Init("Database4", NULL, 96, 1024, FALSE);
	cIndexedData.DurableBegin();

	iNumCached = cIndexedData.TestNumCachedIndexes();
	AssertInt(0, (int)iNumCached);

	cIndexedData.DurableEnd();
	cIndexedData.Kill();

	cFileUtil.RemoveDir("Database4");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedDataNoCaching(BOOL bDurable)
{
	CIndexedData	cIndexedData;
	OIndex			OI;
	CFileUtil		cFileUtil;
	int				iData;
	OIndex			iNumCached;

	cFileUtil.RemoveDir("Database5");

	cIndexedData.Init("Database5", 0, bDurable, 1024, FALSE);

	cIndexedData.DurableBegin();

	OI = 0LL;
	iData = 77;
	cIndexedData.Add(OI, &iData, 4, 0); OI++; 
	cIndexedData.Add(OI, &iData, 4, 0); OI++;
	iData = 0; OI = 0LL; cIndexedData.Get(OI, (void*)&iData);
	AssertInt(77, iData);

	iNumCached = cIndexedData.TestNumCachedIndexes();
	AssertInt(0, (int)iNumCached);

	OI = 2LL;
	cIndexedData.Add(OI, &iData, 4, 0); OI++;
	iData = 0; OI = 0LL; cIndexedData.Get(OI, (void*)&iData);
	AssertInt(77, iData);

	iNumCached = cIndexedData.TestNumCachedIndexes();
	AssertInt(0, (int)iNumCached);

	OI = 2LL;
	cIndexedData.Add(OI, &iData, 4, 0); OI++;
	cIndexedData.Add(OI, &iData, 4, 0); OI++;
	cIndexedData.Add(OI, &iData, 4, 0); OI++;
	cIndexedData.Add(OI, &iData, 4, 0); OI++;
	cIndexedData.Add(OI, &iData, 4, 0); OI++;
	cIndexedData.Add(OI, &iData, 4, 0); OI++;
	iData = 0; OI--; cIndexedData.Get(OI, (void*)&iData);;

	AssertInt(77, iData);
	iData = 0; OI = 0LL; cIndexedData.Get(OI, (void*)&iData);
	AssertInt(77, iData);

	iNumCached = cIndexedData.TestNumCachedIndexes();
	AssertInt(0, (int)iNumCached);

	cIndexedData.DurableEnd();

	cIndexedData.Kill();
	cFileUtil.RemoveDir("Database5");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedDataGet(void)
{
	CIndexedData	cIndexedData;
	CFileUtil		cFileUtil;
	char*			szData;
	int				iSize;
	char			szSmellsLikeTeenSpirit[] = {"Smells Like Teen Spirit"};
	char			szSeizedPotPlants[] = {"Seized pot plants turn out to be daisies"};
	char			szCallingFromWindows[] = {"I am calling you from Windows"};
	
	cFileUtil.RemoveDir("Database6");

	cIndexedData.Init("Database6", NULL, 1 MB, 1 MB, FALSE);
	cIndexedData.DurableBegin();

	cIndexedData.Add(0x7634, szSmellsLikeTeenSpirit, (int)strlen(szSmellsLikeTeenSpirit)+1, 0);
	cIndexedData.Add(0x3589, szSeizedPotPlants, (int)strlen(szSeizedPotPlants)+1, 0);
	cIndexedData.Add(0x8743, szCallingFromWindows, (int)strlen(szCallingFromWindows)+1, 0);
	
	AssertLongLongInt(3, cIndexedData.NumElements());

	cIndexedData.DurableEnd();
	cIndexedData.Kill();

	cIndexedData.Init("Database6", NULL, 1 MB, 1 MB, FALSE);
	cIndexedData.DurableBegin();

	AssertLongLongInt(3, cIndexedData.NumElements());

	szData = (char*)cIndexedData.Get(0x7634, &iSize);
	AssertInt((int)strlen(szSmellsLikeTeenSpirit)+1, iSize);
	AssertString(szSmellsLikeTeenSpirit, szData);
	free(szData);

	szData = (char*)cIndexedData.Get(0x3589, &iSize);
	AssertInt((int)strlen(szSeizedPotPlants)+1, iSize);
	AssertString(szSeizedPotPlants, szData);
	free(szData);
	
	szData = (char*)cIndexedData.Get(0x8743, &iSize);
	AssertInt((int)strlen(szCallingFromWindows)+1, iSize);
	AssertString(szCallingFromWindows, szData);
	free(szData);

	cIndexedData.DurableEnd();
	cIndexedData.Kill();
	cFileUtil.RemoveDir("Database6");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedData(void)
{
	FastFunctionsInit();
	TypeConverterInit();
	MemoryInit();
	DataMemoryInit();
	BeginTests();

	TestIndexedDataSimple(TRUE);
	TestIndexedDataSimple(FALSE);
	TestIndexedDataCacheEviction();
	TestIndexedDataLargeData();
	TestIndexedDataIndexedAdd();
	TestIndexedDataDescriptorCaching();
	TestIndexedDataNoCaching(FALSE);
	TestIndexedDataNoCaching(TRUE);
	TestIndexedDataGet();

	TestStatistics();
	DataMemoryKill();
	MemoryKill();
	FastFunctionsKill();
	TypeConverterKill();
}

