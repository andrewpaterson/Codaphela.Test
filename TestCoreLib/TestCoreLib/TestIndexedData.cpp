#include "BaseLib/FastFunctions.h"
#include "BaseLib/FileUtil.h"
#include "CoreLib/IndexedData.h"
#include "CoreLib/TypeConverter.h"
#include "TestLib/Assert.h"
#include "TestIndexedData.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCacheEviction(void)
{
	CIndexedData	cIndexedData;
	OIndex			OI;
	char			szHello[] = "Hello";
	char			szWorld[] = "World";
	char			szSteam[] = "Stream";
	char			szIn[7];
	unsigned int	uiSize;
	int				iFileSize;
	CFileUtil		cFileUtil;

	cFileUtil.RemoveDir("Database1");

	AssertInt(40, sizeof(CIndexedDataDescriptor));

	OI = 0LL;
	cIndexedData.Init("Database1", 71, FALSE);  //A little more than two items in the cache...
	cIndexedData.Add(OI, szHello, 6, 0);
	AssertInt(1, cIndexedData.NumCached());
	AssertInt(30, cIndexedData.TestGetCachedObjectSize(OI));
	OI = 1LL;
	cIndexedData.Add(OI, szWorld, 6, 0);
	AssertInt(2, cIndexedData.NumCached());
	AssertInt(30, cIndexedData.TestGetCachedObjectSize(OI));
	OI = 2LL;
	cIndexedData.Add(OI, szSteam, 7, 0);
	AssertInt(1, cIndexedData.NumCached());
	AssertInt(1, (int)cIndexedData.TestNumCachedIndexes());
	AssertInt(31, cIndexedData.TestGetCachedObjectSize(OI));

	cIndexedData.Kill();

	iFileSize = cFileUtil.Size("Database1/6_0.DAT");
	AssertInt(12, iFileSize);
	iFileSize = cFileUtil.Size("Database1/7_0.DAT");
	AssertInt(7, iFileSize);

	cIndexedData.Init("Database1", 1024, FALSE);
	AssertInt(2, cIndexedData.NumFiles());

	OI = 0LL;
	uiSize = cIndexedData.Size(OI);
	AssertInt(6, uiSize);
	memset(szIn, 0, 7);
	cIndexedData.Get(OI, szIn);
	AssertString("Hello", szIn);
	AssertInt(1, cIndexedData.NumCached());

	OI = 1LL;
	uiSize = cIndexedData.Size(OI);
	AssertInt(6, uiSize);
	memset(szIn, 0, 7);
	cIndexedData.Get(OI, szIn);
	AssertString("World", szIn);
	AssertInt(2, cIndexedData.NumCached());

	OI = 2LL;
	uiSize = cIndexedData.Size(OI);
	AssertInt(7, uiSize);
	memset(szIn, 0, 7);
	cIndexedData.Get(OI, szIn);
	AssertString("Stream", szIn);
	AssertInt(3, cIndexedData.NumCached());

	OI = 0LL;
	uiSize = cIndexedData.Size(OI);
	AssertInt(6, uiSize);
	memset(szIn, 0, 7);
	cIndexedData.Get(OI, szIn);
	AssertString("Hello", szIn);
	AssertInt(3, cIndexedData.NumCached());
	AssertInt(3, (int)cIndexedData.TestNumCachedIndexes());

	cIndexedData.Kill();

	cIndexedData.Init("Database1", 1024, FALSE);
	AssertInt(0, (int)cIndexedData.TestNumCachedIndexes());
	cIndexedData.Kill();

	cFileUtil.RemoveDir("Database1");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestLargeData(void)
{
	CIndexedData	cIndexedData;
	OIndex			OI;
	char			szBig[] = "A Long String";
	char			szSmall[] = "Cat";
	char			szIn[14];
	CFileUtil		cFileUtil;

	cFileUtil.RemoveDir("Database2");

	cIndexedData.Init("Database2", 34, FALSE);
	OI = 0LL;
	AssertInt(0, cIndexedData.NumCached());
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

	cIndexedData.Kill();

	cFileUtil.RemoveDir("Database2");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedAdd(void)
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

	cIndexedData.Init("Database3", 98+12, FALSE);

	OI = 0LL;
	bResult = cIndexedData.Add(OI, szBat, 4, 0);
	AssertBool(TRUE, bResult);
	AssertInt(1, (int)cIndexedData.NumCached());
	AssertInt(0, (int)cIndexedData.NumInFile(4));
	cIndexedData.Flush();
	AssertInt(1, (int)cIndexedData.NumInFile(4));
	AssertInt(0, (int)cIndexedData.NumCached());

	bResult = cIndexedData.Add(OI, szCat, 4, 0);
	AssertBool(FALSE, bResult);
	bResult = cIndexedData.Set(OI, szDog, 0);
	AssertBool(TRUE, bResult);
	AssertInt(1, (int)cIndexedData.NumCached());
	AssertInt(1, (int)cIndexedData.NumInFile(4));
	AssertInt(0, (int)cIndexedData.TestNumIgnoredCacheElements());
	cIndexedData.Get(OI, szIn);
	AssertString(szDog, szIn);

	bResult = cIndexedData.Set(OI, szFish, 5, 0);
	AssertBool(TRUE, bResult);
	AssertInt(1, (int)cIndexedData.NumCached());
	AssertInt(1, (int)cIndexedData.TestNumIgnoredCacheElements());
	cIndexedData.Get(OI, szIn);
	AssertString(szFish, szIn);

	cIndexedData.Flush();
	AssertInt(1, (int)cIndexedData.NumInFile(4));
	AssertInt(1, (int)cIndexedData.NumInFile(5));
	cIndexedData.Get(OI, szIn);
	AssertString(szFish, szIn);

	bResult = cIndexedData.Set(OI, szCat, 4, 0);
	AssertBool(TRUE, bResult);
	cIndexedData.Flush();
	AssertInt(2, (int)cIndexedData.NumInFile(4));  //One is ignored but they are both still in the file.
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
	cIndexedData.Flush();
	AssertInt(3, (int)cIndexedData.NumInFile(4));
	AssertInt(1, (int)cIndexedData.NumInFile(5));
	AssertInt(2, (int)cIndexedData.NumElements());
	AssertInt(4, (int)cIndexedData.TestIndexedDescriptorsLength());

	cIndexedData.Kill();

	cFileUtil.RemoveDir("Database3");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestDescriptorCaching(void)
{
	CIndexedData	cIndexedData;
	OIndex			OI;
	CFileUtil		cFileUtil;
	int				iData;
	OIndex			iNumCached;

	cFileUtil.RemoveDir("Database4");

	cIndexedData.Init("Database4", 96, FALSE);  //Used to be huge

	OI = 0LL;
	iData = 77;
	cIndexedData.Add(OI, &iData, 4, 0); OI++; 
	cIndexedData.Add(OI, &iData, 4, 0); OI++;
	iData = 0; OI = 0LL; cIndexedData.Get(OI, &iData);
	AssertInt(77, iData);

	OI = 2LL;
	cIndexedData.Add(OI, &iData, 4, 0); OI++;
	iData = 0; OI = 0LL; cIndexedData.Get(OI, &iData);
	AssertInt(77, iData);

	OI = 2LL;
	cIndexedData.Add(OI, &iData, 4, 0); OI++;
	cIndexedData.Add(OI, &iData, 4, 0); OI++;
	cIndexedData.Add(OI, &iData, 4, 0); OI++;
	cIndexedData.Add(OI, &iData, 4, 0); OI++;
	cIndexedData.Add(OI, &iData, 4, 0); OI++;
	cIndexedData.Add(OI, &iData, 4, 0); OI++;
	iData = 0; OI--; cIndexedData.Get(OI, &iData);;
	AssertInt(77, iData);

	iData = 0; OI = 0LL; cIndexedData.Get(OI, &iData);
	AssertInt(77, iData);

	iNumCached = cIndexedData.TestNumCachedIndexes();
	AssertInt(3, (int)iNumCached);

	cIndexedData.Kill();

	cIndexedData.Init("Database4", 96, FALSE);  //Used to be huge

	iNumCached = cIndexedData.TestNumCachedIndexes();
	AssertInt(0, (int)iNumCached);

	cIndexedData.Kill();

	cFileUtil.RemoveDir("Database4");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestNoCaching(BOOL bDurable)
{
	CIndexedData	cIndexedData;
	OIndex			OI;
	CFileUtil		cFileUtil;
	int				iData;
	OIndex			iNumCached;

	cFileUtil.RemoveDir("Database5");

	cIndexedData.Init("Database5", 0, bDurable);  //Used to be huge

	cIndexedData.DurableBegin();

	OI = 0LL;
	iData = 77;
	cIndexedData.Add(OI, &iData, 4, 0); OI++; 
	cIndexedData.Add(OI, &iData, 4, 0); OI++;
	iData = 0; OI = 0LL; cIndexedData.Get(OI, &iData);
	AssertInt(77, iData);

	iNumCached = cIndexedData.TestNumCachedIndexes();
	AssertInt(0, (int)iNumCached);

	OI = 2LL;
	cIndexedData.Add(OI, &iData, 4, 0); OI++;
	iData = 0; OI = 0LL; cIndexedData.Get(OI, &iData);
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
	iData = 0; OI--; cIndexedData.Get(OI, &iData);;

	AssertInt(77, iData);
	iData = 0; OI = 0LL; cIndexedData.Get(OI, &iData);
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
void TestIndexedData(void)
{
	FastFunctionsInit();
	TypeConverterInit();
	BeginTests();

	TestCacheEviction();
	TestLargeData();
	TestIndexedAdd();
	TestDescriptorCaching();
	TestNoCaching(FALSE);
	TestNoCaching(TRUE);

	TestStatistics();
	FastFunctionsKill();
	TypeConverterKill();
}

