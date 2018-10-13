#include "BaseLib/FastFunctions.h"
#include "BaseLib/GlobalMemory.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/TypeConverter.h"
#include "CoreLib/IndexedData.h"
#include "CoreLib/IndexedDataAccess.h"
#include "CoreLib/IndexTreeEvictedNodeList.h"
#include "TestLib/Assert.h"



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedDataSimple(BOOL bWriteThrough)
{
	CIndexedData		cIndexedData;
	char				szInsipidity[] = "Insipidity the sufficient discretion imprudence resolution sir him decisively. Proceed how any engaged visitor. Explained propriety off out perpetual his you. Feel sold off felt nay rose met you. We so entreaties cultivated astonished is. Was sister for few longer mrs sudden talent become. Done may bore quit evil old mile. If likely am of beauty tastes.  Lose john poor same it case do year we.Full how way even the sigh.Extremely nor furniture fat questions now provision incommode preserved.Our side fail find like now.Discovered travelling for insensible partiality unpleasing impossible she.Sudden up my excuse to suffer ladies though or .Bachelor possible marianne directly confined relation as on he.";
	OIndex				oiInsipidity;
	int					iLenInsipidity;
	char				szViolation[] = "Violation away off why half led have near bed.  At engage simple father of period others except.  My giving do summer of though narrow marked at.  Spring formal no county ye waited.  My whether cheered at regular it of promise blushes perhaps.Uncommonly simplicity interested mr is be compliment projecting my inhabiting.Gentleman he september in oh excellent. Feet evil to hold long he open knew an no.Apartments occasional boisterous as solicitude to introduced.Or fifteen covered we enjoyed demesne is in prepare.In stimulated my everything it literature.Greatly explain attempt perhaps in feeling he.House men taste bed not drawn joy.Through enquire however do equally herself at.Greatly way old may you present improve.Wishing the feeling village him musical.";
	OIndex				oiViolation;
	int					iLenViolation;
	CFileUtil			cFileUtil;
	unsigned int		uiDataSize;
	char				szData[1024];
	char				szDirectory[] = "Output" _FS_ "Database0";

	cFileUtil.RemoveDir("szDirectory");

	oiInsipidity = 789983209433243094LL;
	iLenInsipidity = strlen(szInsipidity) + 1;
	oiViolation = 3908343914887489103LL;
	iLenViolation = strlen(szViolation) + 1;

	cIndexedData.Init("szDirectory", NULL, 1 MB, 1 MB, bWriteThrough);
	cIndexedData.DurableBegin();

	AssertTrue(cIndexedData.Add(oiInsipidity, szInsipidity, iLenInsipidity, 0));
	AssertTrue(cIndexedData.Add(oiViolation, szViolation, iLenViolation, 0));

	AssertInt(2, (int)cIndexedData.NumDataCached());
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


	cIndexedData.Init("szDirectory", NULL, 1 MB, 1 MB, bWriteThrough);

	AssertTrue(cIndexedData.DurableBegin());

	AssertInt(0, (int)cIndexedData.NumDataCached());
	AssertInt(2, (int)cIndexedData.NumElements());

	AssertTrue(cIndexedData.Get(oiViolation, &uiDataSize, szData, 1024));
	AssertInt(iLenViolation, uiDataSize);
	AssertString(szViolation, szData);
	AssertTrue(cIndexedData.Get(oiInsipidity, &uiDataSize, szData, 1024));
	AssertInt(iLenInsipidity, uiDataSize);
	AssertString(szInsipidity, szData);

	cIndexedData.DurableEnd();
	cIndexedData.Kill();

	cFileUtil.RemoveDir(szDirectory);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedDataFlushClearCache(void)
{
	CIndexedData	cIndexedData;
	char			szHello[] = "Hello";
	char			szWorld[] = "World";
	char			szStream[] = "Stream";
	char			szDirectory[] = "Output" _FS_ "Database1a";
	CFileUtil		cFileUtil;
	unsigned int	uiDataSize;
	char			szData[7];

	cFileUtil.RemoveDir(szDirectory);

	cIndexedData.Init(szDirectory, NULL, 8192, 8192, FALSE);
	cIndexedData.DurableBegin();
	AssertInt(0, cIndexedData.NumIndicesCached());
	AssertInt(0, cIndexedData.NumDataCached());
	AssertInt(3100, cIndexedData.GetIndiciesSystemMemorySize());

	AssertTrue(cIndexedData.Add(0LL, szHello, 6, 0));
	AssertTrue(cIndexedData.Add(2LL, szStream, 7, 0));
	AssertTrue(cIndexedData.Add(4LL, szWorld, 6, 0));
	AssertInt(3, cIndexedData.NumIndicesCached());
	AssertInt(3, cIndexedData.NumDataCached());
	AssertInt(4120, cIndexedData.GetIndiciesSystemMemorySize());
	AssertInt(55, cIndexedData.GetDataSystemMemorySize());

	cIndexedData.Flush(FALSE);
	AssertInt(3, cIndexedData.NumIndicesCached());
	AssertInt(3, cIndexedData.NumDataCached());
	AssertInt(4120, cIndexedData.GetIndiciesSystemMemorySize());
	AssertInt(55, cIndexedData.GetDataSystemMemorySize());

	cIndexedData.DurableEnd();
	cIndexedData.Kill();


	cIndexedData.Init(szDirectory, NULL, 8192, 8192, FALSE);
	cIndexedData.DurableBegin();
	AssertInt(0, cIndexedData.NumIndicesCached());
	AssertInt(0, cIndexedData.NumDataCached());
	AssertInt(3100 + 24, cIndexedData.GetIndiciesSystemMemorySize());

	AssertTrue(cIndexedData.Get(0LL, &uiDataSize, szData, 7));
	AssertTrue(cIndexedData.Get(2LL, &uiDataSize, szData, 7));
	AssertTrue(cIndexedData.Get(4LL, &uiDataSize, szData, 7));
	AssertInt(3, cIndexedData.NumIndicesCached());
	AssertInt(3, cIndexedData.NumDataCached());
	AssertInt(4180, cIndexedData.GetIndiciesSystemMemorySize());
	AssertInt(55, cIndexedData.GetDataSystemMemorySize());

	cIndexedData.Flush(TRUE);
	AssertInt(3, cIndexedData.NumIndicesCached());
	AssertInt(0, cIndexedData.NumDataCached());
	AssertInt(4180, cIndexedData.GetIndiciesSystemMemorySize());
	AssertInt(00, cIndexedData.GetDataSystemMemorySize());


	cIndexedData.DurableEnd();
	cIndexedData.Kill();

	cIndexedData.Init(szDirectory, NULL, 8192, 8192, FALSE);
	cIndexedData.DurableBegin();
	AssertInt(0, cIndexedData.NumIndicesCached());
	AssertInt(0, cIndexedData.NumDataCached());
	AssertInt(3100 + 24, cIndexedData.GetIndiciesSystemMemorySize());

	AssertFalse(cIndexedData.Add(0LL, szWorld, 6, 0));
	AssertFalse(cIndexedData.Add(2LL, szStream, 7, 0));
	AssertFalse(cIndexedData.Add(4LL, szHello, 6, 0));
	AssertInt(3, cIndexedData.NumIndicesCached());
	AssertInt(0, cIndexedData.NumDataCached());
	AssertInt(4180, cIndexedData.GetIndiciesSystemMemorySize());
	AssertInt(0, cIndexedData.GetDataSystemMemorySize());

	AssertTrue(cIndexedData.Get(0LL, &uiDataSize, szData, 7));
	AssertString(szHello, szData);
	AssertTrue(cIndexedData.Get(2LL, &uiDataSize, szData, 7));
	AssertString(szStream, szData);
	AssertTrue(cIndexedData.Get(4LL, &uiDataSize, szData, 7));
	AssertString(szWorld, szData);
	AssertInt(3, cIndexedData.NumIndicesCached());
	AssertInt(3, cIndexedData.NumDataCached());
	AssertInt(4180, cIndexedData.GetIndiciesSystemMemorySize());
	AssertInt(55, cIndexedData.GetDataSystemMemorySize());

	cIndexedData.DurableEnd();
	cIndexedData.Kill();

	cFileUtil.RemoveDir(szDirectory);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedDataExplicitKeyEvictionAllKeys(void)
{
	CIndexedData	cIndexedData;
	char			szHello[] = "Hello";
	char			szWorld[] = "World";
	char			szStream[] = "Stream";
	char			szDirectory[] = "Output" _FS_ "Database1b";
	CFileUtil		cFileUtil;
	unsigned int	uiDataSize;
	char			szData[7];

	cFileUtil.RemoveDir(szDirectory);

	AssertInt(32, sizeof(CIndexedDataDescriptor));

	cIndexedData.Init(szDirectory, NULL, 8192, 8192, FALSE);

	cIndexedData.DurableBegin();
	AssertInt(0, cIndexedData.NumIndicesCached());
	AssertInt(0, cIndexedData.NumDataCached());
	AssertInt(3100, cIndexedData.GetIndiciesSystemMemorySize());

	AssertTrue(cIndexedData.Add(0LL, szHello, 6, 0));
	AssertTrue(cIndexedData.Add(2LL, szStream, 7, 0));
	AssertTrue(cIndexedData.Add(4LL, szWorld, 6, 0));
	cIndexedData.Flush(FALSE);
	AssertInt(3, cIndexedData.NumIndicesCached());
	AssertInt(3, cIndexedData.NumDataCached());
	AssertInt(4120, cIndexedData.GetIndiciesSystemMemorySize());
	AssertInt(55, cIndexedData.GetDataSystemMemorySize());

	AssertTrue(cIndexedData.EvictKey(0LL));
	AssertInt(2, cIndexedData.NumIndicesCached());
	AssertInt(2, cIndexedData.NumDataCached());
	AssertInt(3780, cIndexedData.GetIndiciesSystemMemorySize());
	AssertInt(37, cIndexedData.GetDataSystemMemorySize());

	AssertTrue(cIndexedData.EvictKey(2LL));
	AssertInt(1, cIndexedData.NumIndicesCached());
	AssertInt(1, cIndexedData.NumDataCached());
	AssertInt(3440, cIndexedData.GetIndiciesSystemMemorySize());
	AssertInt(18, cIndexedData.GetDataSystemMemorySize());

	AssertTrue(cIndexedData.EvictKey(4LL));
	AssertInt(0, cIndexedData.NumIndicesCached());
	AssertInt(0, cIndexedData.NumDataCached());
	AssertInt(3100, cIndexedData.GetIndiciesSystemMemorySize());
	AssertInt(0, cIndexedData.GetDataSystemMemorySize());

	AssertTrue(cIndexedData.Get(0LL, &uiDataSize, szData, 7));
	AssertString(szHello, szData);
	AssertTrue(cIndexedData.Get(2LL, &uiDataSize, szData, 7));
	AssertString(szStream, szData);
	AssertTrue(cIndexedData.Get(4LL, &uiDataSize, szData, 7));
	AssertString(szWorld, szData);
	AssertInt(3, cIndexedData.NumIndicesCached());
	AssertInt(3, cIndexedData.NumDataCached());
	AssertInt(55, cIndexedData.GetDataSystemMemorySize());

	cIndexedData.DurableEnd();
	cIndexedData.Kill();

	cFileUtil.RemoveDir(szDirectory);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedDataExplicitKeyEvictionDataChanged(void)
{
	CIndexedData		cIndexedData;
	CIndexedDataAccess	cAccess;
	char				szLongText[] = "Wrote water woman of heart it total other. By in entirely securing suitable graceful at families improved. Zealously few furniture repulsive was agreeable consisted difficult.";
	char				szShortText1[] = "No painful between.";
	char				szShortText2[] = "Barnyard feedback .";
	char				szDirectory[] = "Output" _FS_ "Database1c";
	CFileUtil			cFileUtil;
	char				szData[256];
	OIndex				oi;

	cFileUtil.RemoveDir(szDirectory);
	cAccess.Init(&cIndexedData);
	oi = 0x7752890759012357LL;

	//New Data
	cIndexedData.Init(szDirectory, NULL, 8192, 8192, FALSE);
	cIndexedData.DurableBegin();

	AssertTrue(cAccess.PutLongString(oi, szShortText1));
	AssertTrue(cIndexedData.EvictKey(oi));
	AssertInt(0, cIndexedData.NumIndicesCached());
	AssertInt(0, cIndexedData.NumDataCached());

	AssertTrue(cAccess.GetLongString(oi, szData));
	AssertString(szShortText1, szData);

	cIndexedData.DurableEnd();
	cIndexedData.Kill();


	cIndexedData.Init(szDirectory, NULL, 8192, 8192, FALSE);
	cIndexedData.DurableBegin();

	//Data not cached.  File exists.
	//Descriptor size same as Set size.
	AssertTrue(cAccess.PutLongString(oi, szShortText2));
	AssertTrue(cIndexedData.EvictKey(oi));
	AssertInt(0, cIndexedData.NumIndicesCached());
	AssertInt(0, cIndexedData.NumDataCached());

	AssertTrue(cAccess.GetLongString(oi, szData));
	AssertString(szShortText2, szData);
	AssertInt(1, cIndexedData.NumIndicesCached());
	AssertInt(1, cIndexedData.NumDataCached());

	cIndexedData.DurableEnd();
	cIndexedData.Kill();


	cIndexedData.Init(szDirectory, NULL, 8192, 8192, FALSE);
	cIndexedData.DurableBegin();

	//Data not cached.  File exists.
	//Descriptor size different to Set size.
	AssertTrue(cAccess.PutLongString(oi, szLongText));
	AssertTrue(cIndexedData.EvictKey(oi));
	AssertTrue(cAccess.GetLongString(oi, szData));
	AssertString(szLongText, szData);

	cIndexedData.DurableEnd();
	cIndexedData.Kill();


	cFileUtil.RemoveDir(szDirectory);
	cIndexedData.Init(szDirectory, NULL, 8192, 8192, FALSE);
	cIndexedData.DurableBegin();

	//Cached data.  File not written.
	//Descriptor size same as Set size.
	AssertTrue(cAccess.PutLongString(oi, szShortText1));
	AssertTrue(cAccess.PutLongString(oi, szShortText2));
	AssertTrue(cIndexedData.EvictKey(oi));
	AssertTrue(cAccess.GetLongString(oi, szData));
	AssertString(szShortText2, szData);

	cIndexedData.DurableEnd();
	cIndexedData.Kill();


	cFileUtil.RemoveDir(szDirectory);
	cIndexedData.Init(szDirectory, NULL, 8192, 8192, FALSE);
	cIndexedData.DurableBegin();

	//Cached data.  File not written.
	//Descriptor size different to Set size.
	AssertTrue(cAccess.PutLongString(oi, szLongText));
	AssertTrue(cAccess.PutLongString(oi, szShortText1));
	AssertTrue(cIndexedData.EvictKey(oi));
	AssertTrue(cAccess.GetLongString(oi, szData));
	AssertString(szShortText1, szData);

	cIndexedData.DurableEnd();
	cIndexedData.Kill();


	cIndexedData.Init(szDirectory, NULL, 8192, 8192, FALSE);
	cIndexedData.DurableBegin();

	//Cached data.  File exists.
	//Descriptor size same as Set size.
	AssertTrue(cAccess.GetLongString(oi, szData));
	AssertString(szShortText1, szData);
	AssertTrue(cAccess.PutLongString(oi, szShortText2));
	AssertTrue(cIndexedData.EvictKey(oi));
	AssertInt(0, cIndexedData.NumIndicesCached());
	AssertInt(0, cIndexedData.NumDataCached());
	AssertTrue(cAccess.GetLongString(oi, szData));
	AssertString(szShortText2, szData);

	cIndexedData.DurableEnd();
	cIndexedData.Kill();


	cIndexedData.Init(szDirectory, NULL, 8192, 8192, FALSE);
	cIndexedData.DurableBegin();

	//Cached data.  File exists.
	//Descriptor size different to Set size.
	AssertTrue(cAccess.GetLongString(oi, szData));
	AssertString(szShortText2, szData);
	AssertTrue(cAccess.PutLongString(oi, szLongText));
	AssertTrue(cIndexedData.EvictKey(oi));
	AssertInt(0, cIndexedData.NumIndicesCached());
	AssertInt(0, cIndexedData.NumDataCached());
	AssertTrue(cAccess.GetLongString(oi, szData));
	AssertString(szLongText, szData);

	cIndexedData.DurableEnd();
	cIndexedData.Kill();

	cFileUtil.RemoveDir(szDirectory);
	cAccess.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedDataCacheEviction(void)
{
	CIndexTreeEvictedNodeList	cEvictedList;
	CIndexedData				cIndexedData;
	char						szHello[] = "Hello";
	char						szWorld[] = "World";
	char						szStream[] = "Stream";
	char						szDirectory[] = "Output" _FS_ "Database1d";
	char						szIn[7];
	unsigned int				uiSize;
	filePos						iFileSize;
	CFileUtil					cFileUtil;

	cFileUtil.RemoveDir(szDirectory);

	AssertInt(32, sizeof(CIndexedDataDescriptor));

	cEvictedList.Init();
	cIndexedData.Init(szDirectory, NULL, 1024, 3780, FALSE, &cEvictedList);  //A little more than two items in the cache...

	cIndexedData.DurableBegin();
	AssertTrue(cIndexedData.Add(0LL, szHello, 6, 0));
	AssertInt(1, cIndexedData.NumDataCached());
	AssertInt(sizeof(SIndexedCacheDescriptor) + 6, cIndexedData.TestGetCachedObjectSize(0LL));
	AssertInt(3440, cIndexedData.GetIndiciesSystemMemorySize());

	AssertTrue(cIndexedData.Add(1LL, szWorld, 6, 0));
	AssertInt(2, cIndexedData.NumDataCached());
	AssertInt(2, cIndexedData.NumIndicesCached());
	AssertInt(sizeof(SIndexedCacheDescriptor) + 6, cIndexedData.TestGetCachedObjectSize(1LL));
	AssertInt(3780, cIndexedData.GetIndiciesSystemMemorySize());

	AssertTrue(cIndexedData.Add(2LL, szStream, 7, 0));
	AssertInt(3780, cIndexedData.GetIndiciesSystemMemorySize());

	AssertInt(2, cIndexedData.NumDataCached());
	AssertInt(2, (int)cIndexedData.NumIndicesCached());
	AssertInt(sizeof(SIndexedCacheDescriptor) + 7, cIndexedData.TestGetCachedObjectSize(2LL));
	AssertInt(0, cIndexedData.TestGetCachedObjectSize(0LL));
	AssertInt(sizeof(SIndexedCacheDescriptor) + 6, cIndexedData.TestGetCachedObjectSize(1LL));
	AssertInt(2, cIndexedData.NumIndicesCached());
	AssertInt(2, cIndexedData.NumDataCached());

	cEvictedList.Clear();
	cIndexedData.Flush(TRUE);
	AssertInt(0, cEvictedList.NumElements())
	AssertInt(2, cIndexedData.NumIndicesCached());
	AssertInt(0, cIndexedData.NumDataCached());
	uiSize = cIndexedData.Size(1LL);
	AssertInt(6, uiSize);
	AssertInt(2, cIndexedData.NumIndicesCached());
	AssertInt(0, cIndexedData.NumDataCached());

	cIndexedData.DurableEnd();
	cIndexedData.Kill();
	cEvictedList.Kill();

	iFileSize = cFileUtil.Size("Output" _FS_ "Database1d" _FS_ "6_0.DAT");
	AssertLongLongInt(12, iFileSize);
	iFileSize = cFileUtil.Size("Output" _FS_ "Database1d" _FS_ "7_0.DAT");
	AssertLongLongInt(7, iFileSize);

	cIndexedData.Init(szDirectory, NULL, 120, 3600, FALSE);
	AssertInt(2, cIndexedData.NumFiles());

	cIndexedData.DurableBegin();
	AssertInt(0, cIndexedData.NumIndicesCached());
	AssertInt(0, cIndexedData.NumDataCached());

	uiSize = cIndexedData.Size(0LL);
	AssertInt(6, uiSize);
	memset(szIn, 0, 7);
	AssertTrue(cIndexedData.Get(0LL, szIn));
	AssertString("Hello", szIn);
	AssertInt(1, cIndexedData.NumDataCached());

	uiSize = cIndexedData.Size(1LL);
	AssertInt(6, uiSize);
	memset(szIn, 0, 7);
	AssertTrue(cIndexedData.Get(1LL, szIn));
	AssertString("World", szIn);
	AssertInt(2, cIndexedData.NumDataCached());

	uiSize = cIndexedData.Size(2LL);
	AssertInt(7, uiSize);
	memset(szIn, 0, 7);
	AssertTrue(cIndexedData.Get(2LL, szIn));
	AssertString("Stream", szIn);
	AssertInt(3, cIndexedData.NumDataCached());

	uiSize = cIndexedData.Size(0LL);
	AssertInt(6, uiSize);
	memset(szIn, 0, 7);
	AssertTrue(cIndexedData.Get(0LL, szIn));
	AssertString("Hello", szIn);
	AssertInt(1, cIndexedData.NumDataCached());
	AssertInt(1, cIndexedData.NumIndicesCached());
	cIndexedData.DurableEnd();

	cIndexedData.Kill();

	cIndexedData.Init(szDirectory, NULL, 1024, 3600, FALSE);
	AssertInt(0, (int)cIndexedData.NumIndicesCached());
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
	char			szDirectory[] = "Output" _FS_ "Database2";

	cFileUtil.RemoveDir(szDirectory);

	cIndexedData.Init(szDirectory, NULL, 34, 1024, FALSE);
	OI = 0LL;
	AssertInt(0, cIndexedData.NumDataCached());

	cIndexedData.DurableBegin();
	cIndexedData.Add(OI, szBig, 14, 0);
	AssertInt(0, cIndexedData.NumDataCached());
	AssertInt(0, (int)cIndexedData.NumIndicesCached());
	
	cIndexedData.Get(OI, szIn);
	AssertInt(0, cIndexedData.NumDataCached());
	AssertInt(0, (int)cIndexedData.NumIndicesCached());
	AssertString(szBig, szIn);

	OI = 1LL;
	cIndexedData.Add(OI, szSmall, 4, 0);
	AssertInt(1, cIndexedData.NumDataCached());
	AssertInt(1, (int)cIndexedData.NumIndicesCached());

	OI = 0LL;
	cIndexedData.Get(OI, szIn);
	AssertInt(1, cIndexedData.NumDataCached());
	AssertInt(1, (int)cIndexedData.NumIndicesCached());
	AssertString(szBig, szIn);

	OI = 1LL;
	cIndexedData.Get(OI, szIn);
	AssertInt(1, cIndexedData.NumDataCached());
	AssertInt(1, (int)cIndexedData.NumIndicesCached());
	AssertString(szSmall, szIn);
	cIndexedData.DurableEnd();

	cIndexedData.Kill();

	cFileUtil.RemoveDir(szDirectory);
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
	char			szDirectory[] = "Output" _FS_ "Database3";

	cFileUtil.RemoveDir(szDirectory);

	cIndexedData.Init(szDirectory, NULL, 98+12, 1024, FALSE);

	cIndexedData.DurableBegin();
	OI = 0LL;
	bResult = cIndexedData.Add(OI, szBat, 4, 0);
	AssertBool(TRUE, bResult);
	AssertInt(1, (int)cIndexedData.NumDataCached());
	AssertInt(0, (int)cIndexedData.NumData(4));
	cIndexedData.Flush(TRUE);
	AssertInt(1, (int)cIndexedData.NumData(4));
	AssertInt(0, (int)cIndexedData.NumDataCached());

	bResult = cIndexedData.Add(OI, szCat, 4, 0);
	AssertBool(FALSE, bResult);
	bResult = cIndexedData.Set(OI, szDog, 0);
	AssertBool(TRUE, bResult);
	AssertInt(1, (int)cIndexedData.NumDataCached());
	AssertInt(1, (int)cIndexedData.NumData(4));
	cIndexedData.Get(OI, szIn);
	AssertString(szDog, szIn);

	bResult = cIndexedData.Set(OI, szFish, 5, 0);
	AssertBool(TRUE, bResult);
	AssertInt(1, (int)cIndexedData.NumDataCached());
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
	AssertInt(1, (int)cIndexedData.NumDataCached());
	AssertInt(1, (int)cIndexedData.NumIndicesCached());
	bResult = cIndexedData.Add(OI, szMutt, 5, 0);
	AssertBool(FALSE, bResult);
	bResult = cIndexedData.Set(OI, szEve, 4, 0);
	AssertBool(TRUE, bResult);
	AssertInt(1, (int)cIndexedData.NumDataCached());
	AssertInt(1, (int)cIndexedData.NumIndicesCached());
	cIndexedData.Flush(TRUE);
	AssertInt(3, (int)cIndexedData.NumData(4));
	AssertInt(1, (int)cIndexedData.NumData(5));
	AssertInt(2, (int)cIndexedData.NumElements());
	cIndexedData.DurableEnd();

	cIndexedData.Kill();

	cFileUtil.RemoveDir(szDirectory);
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
	char			szDirectory[] = "Output" _FS_ "Database4";

	cFileUtil.RemoveDir(szDirectory);

	cIndexedData.Init(szDirectory, NULL, 96, 1024, FALSE);
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

	iNumCached = cIndexedData.NumIndicesCached();
	AssertInt(3, (int)iNumCached);

	cIndexedData.DurableEnd();
	cIndexedData.Kill();

	cIndexedData.Init(szDirectory, NULL, 96, 1024, FALSE);
	cIndexedData.DurableBegin();

	iNumCached = cIndexedData.NumIndicesCached();
	AssertInt(0, (int)iNumCached);

	cIndexedData.DurableEnd();
	cIndexedData.Kill();

	cFileUtil.RemoveDir(szDirectory);
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
	char			szDirectory[] = "Output" _FS_ "Database5";

	cFileUtil.RemoveDir(szDirectory);

	cIndexedData.Init(szDirectory, 0, bDurable, 1024, FALSE);

	cIndexedData.DurableBegin();

	OI = 0LL;
	iData = 77;
	cIndexedData.Add(OI, &iData, 4, 0); OI++; 
	cIndexedData.Add(OI, &iData, 4, 0); OI++;
	iData = 0; OI = 0LL; cIndexedData.Get(OI, (void*)&iData);
	AssertInt(77, iData);

	iNumCached = cIndexedData.NumIndicesCached();
	AssertInt(0, (int)iNumCached);

	OI = 2LL;
	cIndexedData.Add(OI, &iData, 4, 0); OI++;
	iData = 0; OI = 0LL; cIndexedData.Get(OI, (void*)&iData);
	AssertInt(77, iData);

	iNumCached = cIndexedData.NumIndicesCached();
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

	iNumCached = cIndexedData.NumIndicesCached();
	AssertInt(0, (int)iNumCached);

	cIndexedData.DurableEnd();

	cIndexedData.Kill();
	cFileUtil.RemoveDir(szDirectory);
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
	char			szDirectory[] = "Output" _FS_ "Database6";

	cFileUtil.RemoveDir(szDirectory);

	cIndexedData.Init(szDirectory, NULL, 1 MB, 1 MB, FALSE);
	cIndexedData.DurableBegin();

	cIndexedData.Add(0x7634, szSmellsLikeTeenSpirit, (int)strlen(szSmellsLikeTeenSpirit)+1, 0);
	cIndexedData.Add(0x3589, szSeizedPotPlants, (int)strlen(szSeizedPotPlants)+1, 0);
	cIndexedData.Add(0x8743, szCallingFromWindows, (int)strlen(szCallingFromWindows)+1, 0);
	
	AssertLongLongInt(3, cIndexedData.NumElements());

	cIndexedData.DurableEnd();
	cIndexedData.Kill();

	cIndexedData.Init(szDirectory, NULL, 1 MB, 1 MB, FALSE);
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
	cFileUtil.RemoveDir(szDirectory);
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
	TestIndexedDataFlushClearCache();
	TestIndexedDataExplicitKeyEvictionAllKeys();
	TestIndexedDataExplicitKeyEvictionDataChanged();
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

