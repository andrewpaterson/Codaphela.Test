#include "BaseLib/Logger.h"
#include "BaseLib/FastFunctions.h"
#include "BaseLib/GlobalMemory.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/Logger.h"
#include "CoreLib/IndexedData.h"
#include "CoreLib/ValueIndexedDataConfig.h"
#include "CoreLib/IndexedDataAccess.h"
#include "CoreLib/EvictedList.h"
#include "CoreLib/IndexedEvictedList.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedDataSimple(EIndexWriteThrough eWriteThrough)
{
	CIndexedData				cIndexedData;
	char						szInsipidity[] = "Insipidity the sufficient discretion imprudence resolution sir him decisively. Proceed how any engaged visitor. Explained propriety off out perpetual his you. Feel sold off felt nay rose met you. We so entreaties cultivated astonished is. Was sister for few longer mrs sudden talent become. Done may bore quit evil old mile. If likely am of beauty tastes.  Lose john poor same it case do year we.Full how way even the sigh.Extremely nor furniture fat questions now provision incommode preserved.Our side fail find like now.Discovered travelling for insensible partiality unpleasing impossible she.Sudden up my excuse to suffer ladies though or .Bachelor possible marianne directly confined relation as on he.";
	OIndex						oiInsipidity;
	int							iLenInsipidity;
	char						szViolation[] = "Violation away off why half led have near bed.  At engage simple father of period others except.  My giving do summer of though narrow marked at.  Spring formal no county ye waited.  My whether cheered at regular it of promise blushes perhaps.Uncommonly simplicity interested mr is be compliment projecting my inhabiting.Gentleman he september in oh excellent. Feet evil to hold long he open knew an no.Apartments occasional boisterous as solicitude to introduced.Or fifteen covered we enjoyed demesne is in prepare.In stimulated my everything it literature.Greatly explain attempt perhaps in feeling he.House men taste bed not drawn joy.Through enquire however do equally herself at.Greatly way old may you present improve.Wishing the feeling village him musical.";
	OIndex						oiViolation;
	int							iLenViolation;
	CFileUtil					cFileUtil;
	unsigned int				uiDataSize;
	char						szData[1024];
	char						szDirectory[] = "Output" _FS_ "Database0";
	char						szSubDirectory[] = "Data";
	CValueIndexedDataConfig		cDataConfig;
	CDurableFileController		cController;

	cFileUtil.RemoveDir(szDirectory);

	oiInsipidity = 789983209433243094LL;
	iLenInsipidity = strlen(szInsipidity) + 1;
	oiViolation = 3908343914887489103LL;
	iLenViolation = strlen(szViolation) + 1;

	cController.Init(szDirectory, NULL);
	cDataConfig.Init(&cController, szSubDirectory, 8192, 8192, eWriteThrough);
	cController.Begin();
	cIndexedData.Init(&cDataConfig);
	cController.End();
	
	AssertTrue(cController.Begin());
	AssertTrue(cIndexedData.Add(oiInsipidity, szInsipidity, iLenInsipidity, 0));
	AssertTrue(cIndexedData.Add(oiViolation, szViolation, iLenViolation, 0));

	AssertInt(2, (int)cIndexedData.NumDataCached());
	AssertInt(2, (int)cIndexedData.NumElements());
	AssertTrue(cIndexedData.Flush(TRUE));

	AssertTrue(cIndexedData.Get(oiViolation, &uiDataSize, szData, 1024));
	AssertInt(iLenViolation, uiDataSize);
	AssertString(szViolation, szData);
	AssertTrue(cIndexedData.Get(oiInsipidity, &uiDataSize, szData, 1024));
	AssertInt(iLenInsipidity, uiDataSize);
	AssertString(szInsipidity, szData);

	cIndexedData.Flush(TRUE);
	AssertTrue(cController.End());

	AssertTrue(cIndexedData.Kill());
	cDataConfig.Kill();


	cController.Init(szDirectory, NULL);
	cDataConfig.Init(&cController, szSubDirectory, 8192, 8192, eWriteThrough);
	cController.Begin();
	cIndexedData.Init(&cDataConfig);
	cController.End();

	AssertTrue(cController.Begin());
	AssertInt(0, (int)cIndexedData.NumDataCached());
	AssertInt(2, (int)cIndexedData.NumElements());

	AssertTrue(cIndexedData.Get(oiViolation, &uiDataSize, szData, 1024));
	AssertInt(iLenViolation, uiDataSize);
	AssertString(szViolation, szData);
	AssertTrue(cIndexedData.Get(oiInsipidity, &uiDataSize, szData, 1024));
	AssertInt(iLenInsipidity, uiDataSize);
	AssertString(szInsipidity, szData);

	AssertInt(2, (int)cIndexedData.NumDataCached());
	AssertInt(2, (int)cIndexedData.NumElements());

	cIndexedData.Flush(TRUE);
	AssertTrue(cController.End());
	AssertTrue(cIndexedData.Kill());
	cDataConfig.Kill();

	cFileUtil.RemoveDir(szDirectory);
}



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedDataFlushClearCache(void)
{
	CIndexedData				cIndexedData;
	char						szHello[] = "Hello";
	char						szWorld[] = "World";
	char						szStream[] = "Stream";
	char						szDirectory[] = "Output" _FS_ "Database1a";
	CFileUtil					cFileUtil;
	unsigned int				uiDataSize;
	char						szData[7];
	CValueIndexedDataConfig		cDataConfig;
	SLogConfig					sLogConfig;
	CDurableFileController		cController;

	cFileUtil.RemoveDir(szDirectory);

	cController.Init(szDirectory, NULL);
	cDataConfig.Init(&cController, NULL, 8192, 8192, IWT_No);
	cController.Begin();
	cIndexedData.Init(&cDataConfig);
	cController.End();

	cController.Begin();
	AssertLongLongInt(0, cIndexedData.NumIndicesCached());
	AssertInt(0, cIndexedData.NumDataCached());
	AssertInt(3100, cIndexedData.GetIndiciesSystemMemorySize());

	AssertTrue(cIndexedData.Add(0LL, szHello, 6, 0));
	AssertTrue(cIndexedData.Add(2LL, szStream, 7, 0));
	AssertTrue(cIndexedData.Add(4LL, szWorld, 6, 0));
	AssertLongLongInt(3, cIndexedData.NumIndicesCached());
	AssertInt(3, cIndexedData.NumDataCached());
	AssertInt(3608, cIndexedData.GetIndiciesSystemMemorySize());
	AssertInt(55, cIndexedData.GetDataSystemMemorySize());

	cIndexedData.Flush(FALSE);
	AssertLongLongInt(3, cIndexedData.NumIndicesCached());
	AssertInt(3, cIndexedData.NumDataCached());
	AssertInt(3608, cIndexedData.GetIndiciesSystemMemorySize());
	AssertInt(55, cIndexedData.GetDataSystemMemorySize());

	cController.End();
	cIndexedData.Kill();
	cDataConfig.Kill();


	cController.Init(szDirectory, NULL);
	cDataConfig.Init(&cController, NULL, 8192, 8192, IWT_No);
	cController.Begin();
	cIndexedData.Init(&cDataConfig);
	cController.End();

	cController.Begin();
	AssertLongLongInt(0, cIndexedData.NumIndicesCached());
	AssertInt(0, cIndexedData.NumDataCached());
	AssertInt(3100 + 24, cIndexedData.GetIndiciesSystemMemorySize());

	AssertTrue(cIndexedData.Get(0LL, &uiDataSize, szData, 7));
	AssertTrue(cIndexedData.Get(2LL, &uiDataSize, szData, 7));
	AssertTrue(cIndexedData.Get(4LL, &uiDataSize, szData, 7));
	AssertLongLongInt(3, cIndexedData.NumIndicesCached());
	AssertInt(3, cIndexedData.NumDataCached());
	AssertInt(3668, cIndexedData.GetIndiciesSystemMemorySize());
	AssertInt(55, cIndexedData.GetDataSystemMemorySize());

	AssertTrue(cIndexedData.Flush(TRUE));
	AssertLongLongInt(3, cIndexedData.NumIndicesCached());
	AssertInt(0, cIndexedData.NumDataCached());
	AssertInt(3668, cIndexedData.GetIndiciesSystemMemorySize());
	AssertInt(00, cIndexedData.GetDataSystemMemorySize());

	cController.End();
	cIndexedData.Kill();
	cDataConfig.Kill();


	cController.Init(szDirectory, NULL);
	cDataConfig.Init(&cController, NULL, 1 MB, 1 MB, IWT_No);
	cController.Begin();
	cIndexedData.Init(&cDataConfig);
	cController.End();

	cController.Begin();
	AssertLongLongInt(0, cIndexedData.NumIndicesCached());
	AssertInt(0, cIndexedData.NumDataCached());
	AssertInt(3100 + 24, cIndexedData.GetIndiciesSystemMemorySize());

	sLogConfig = gcLogger.SetSilent();
	AssertFalse(cIndexedData.Add(0LL, szWorld, 6, 0));
	AssertFalse(cIndexedData.Add(2LL, szStream, 7, 0));
	AssertFalse(cIndexedData.Add(4LL, szHello, 6, 0));
	gcLogger.SetConfig(&sLogConfig);
	AssertLongLongInt(3, cIndexedData.NumIndicesCached());
	AssertInt(0, cIndexedData.NumDataCached());
	AssertInt(3668, cIndexedData.GetIndiciesSystemMemorySize());
	AssertInt(0, cIndexedData.GetDataSystemMemorySize());

	AssertTrue(cIndexedData.Get(0LL, &uiDataSize, szData, 7));
	AssertString(szHello, szData);
	AssertTrue(cIndexedData.Get(2LL, &uiDataSize, szData, 7));
	AssertString(szStream, szData);
	AssertTrue(cIndexedData.Get(4LL, &uiDataSize, szData, 7));
	AssertString(szWorld, szData);
	AssertLongLongInt(3, cIndexedData.NumIndicesCached());
	AssertInt(3, cIndexedData.NumDataCached());
	AssertInt(3668, cIndexedData.GetIndiciesSystemMemorySize());
	AssertInt(55, cIndexedData.GetDataSystemMemorySize());

	cController.End();
	cIndexedData.Kill();
	cDataConfig.Kill();

	cFileUtil.RemoveDir(szDirectory);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedDataExplicitKeyEvictionAllKeys(void)
{
	CIndexedData				cIndexedData;
	char						szHello[] = "Hello";
	char						szWorld[] = "World";
	char						szStream[] = "Stream";
	char						szDirectory[] = "Output" _FS_ "Database1b";
	CFileUtil					cFileUtil;
	unsigned int				uiDataSize;
	char						szData[7];
	CValueIndexedDataConfig		cDataConfig;
	CDurableFileController		cController;

	cFileUtil.RemoveDir(szDirectory);

	AssertInt(32, sizeof(CIndexedDataDescriptor));

	cController.Init(szDirectory, NULL);
	cDataConfig.Init(&cController, NULL, 8192, 8192, IWT_No);
	cController.Begin();
	cIndexedData.Init(&cDataConfig);
	cController.End();

	cController.Begin();
	AssertLongLongInt(0, cIndexedData.NumIndicesCached());
	AssertInt(0, cIndexedData.NumDataCached());
	AssertInt(3100, cIndexedData.GetIndiciesSystemMemorySize());

	AssertTrue(cIndexedData.Add(0LL, szHello, 6, 0));
	AssertTrue(cIndexedData.Add(2LL, szStream, 7, 0));
	AssertTrue(cIndexedData.Add(4LL, szWorld, 6, 0));
	cIndexedData.Flush(FALSE);
	AssertLongLongInt(3, cIndexedData.NumIndicesCached());
	AssertInt(3, cIndexedData.NumDataCached());
	AssertInt(3608, cIndexedData.GetIndiciesSystemMemorySize());
	AssertInt(55, cIndexedData.GetDataSystemMemorySize());

	AssertTrue(cIndexedData.EvictKey(0LL));
	AssertLongLongInt(2, cIndexedData.NumIndicesCached());
	AssertInt(2, cIndexedData.NumDataCached());
	AssertInt(3548, cIndexedData.GetIndiciesSystemMemorySize());
	AssertInt(37, cIndexedData.GetDataSystemMemorySize());

	AssertTrue(cIndexedData.EvictKey(2LL));
	AssertLongLongInt(1, cIndexedData.NumIndicesCached());
	AssertInt(1, cIndexedData.NumDataCached());
	AssertInt(3488, cIndexedData.GetIndiciesSystemMemorySize());
	AssertInt(18, cIndexedData.GetDataSystemMemorySize());

	AssertTrue(cIndexedData.EvictKey(4LL));
	AssertLongLongInt(0, cIndexedData.NumIndicesCached());
	AssertInt(0, cIndexedData.NumDataCached());
	AssertInt(3100, cIndexedData.GetIndiciesSystemMemorySize());
	AssertInt(0, cIndexedData.GetDataSystemMemorySize());

	AssertTrue(cIndexedData.Get(0LL, &uiDataSize, szData, 7));
	AssertString(szHello, szData);
	AssertTrue(cIndexedData.Get(2LL, &uiDataSize, szData, 7));
	AssertString(szStream, szData);
	AssertTrue(cIndexedData.Get(4LL, &uiDataSize, szData, 7));
	AssertString(szWorld, szData);
	AssertLongLongInt(3, cIndexedData.NumIndicesCached());
	AssertInt(3, cIndexedData.NumDataCached());
	AssertInt(55, cIndexedData.GetDataSystemMemorySize());

	cController.End();
	cIndexedData.Kill();
	cDataConfig.Kill();

	cFileUtil.RemoveDir(szDirectory);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedDataExplicitKeyEvictionDataChanged(void)
{
	CIndexedData				cIndexedData;
	CIndexedDataAccess			cAccess;
	char						szLongText[] = "Wrote water woman of heart it total other. By in entirely securing suitable graceful at families improved. Zealously few furniture repulsive was agreeable consisted difficult.";
	char						szShortText1[] = "No painful between.";
	char						szShortText2[] = "Barnyard feedback .";
	char						szDirectory[] = "Output" _FS_ "Database1c";
	CFileUtil					cFileUtil;
	char						szData[256];
	OIndex						oi;
	CValueIndexedDataConfig		cDataConfig;
	CDurableFileController		cController;

	AssertInt(20, strlen(szShortText1) + 1);
	AssertInt(20, strlen(szShortText2) + 1);
	AssertInt(176, strlen(szLongText) + 1);

	cFileUtil.RemoveDir(szDirectory);
	cAccess.Init(&cIndexedData);
	oi = 0x7752890759012357LL;

	//New Data
	cController.Init(szDirectory, NULL);
	cDataConfig.Init(&cController, NULL, 8192, 8192, IWT_No);
	cController.Begin();
	cIndexedData.Init(&cDataConfig);
	cController.End();

	cController.Begin();

	AssertTrue(cAccess.PutLongString(oi, szShortText1));
	AssertTrue(cIndexedData.EvictKey(oi));
	AssertLongLongInt(0, cIndexedData.NumIndicesCached());
	AssertInt(0, cIndexedData.NumDataCached());

	AssertNotNull(cAccess.GetLongString(oi, szData));
	AssertString(szShortText1, szData);

	cController.End();
	cIndexedData.Kill();
	cDataConfig.Kill();


	cController.Init(szDirectory, NULL);
	cDataConfig.Init(&cController, NULL, 8192, 8192, IWT_No);
	cController.Begin();
	cIndexedData.Init(&cDataConfig);
	cController.End();

	cController.Begin();
	//Data not cached.  File exists.
	//Descriptor size same as Set size.
	AssertTrue(cAccess.PutLongString(oi, szShortText2));
	AssertTrue(cIndexedData.EvictKey(oi));
	AssertLongLongInt(0, cIndexedData.NumIndicesCached());
	AssertInt(0, cIndexedData.NumDataCached());

	memset(szData, 0, 256);
	AssertNotNull(cAccess.GetLongString(oi, szData));
	AssertString(szShortText2, szData);
	AssertLongLongInt(1, cIndexedData.NumIndicesCached());
	AssertInt(1, cIndexedData.NumDataCached());

	cController.End();
	cIndexedData.Kill();
	cDataConfig.Kill();


	cController.Init(szDirectory, NULL);
	cDataConfig.Init(&cController, NULL, 8192, 8192, IWT_No);
	cController.Begin();
	cIndexedData.Init(&cDataConfig);
	cController.End();

	cController.Begin();
	//Data not cached.  File exists.
	//Descriptor size different to Set size.
	AssertTrue(cAccess.PutLongString(oi, szLongText));
	AssertTrue(cIndexedData.EvictKey(oi));
	AssertNotNull(cAccess.GetLongString(oi, szData));
	AssertString(szLongText, szData);

	cController.End();
	cIndexedData.Kill();
	cDataConfig.Kill();


	cFileUtil.RemoveDir(szDirectory);
	cController.Init(szDirectory, NULL);
	cDataConfig.Init(&cController, NULL, 8192, 8192, IWT_No);
	cController.Begin();
	cIndexedData.Init(&cDataConfig);
	cController.End();

	cController.Begin();
	//Cached data.  File not written.
	//Descriptor size same as Set size.
	AssertTrue(cAccess.PutLongString(oi, szShortText1));
	AssertTrue(cAccess.PutLongString(oi, szShortText2));
	AssertTrue(cIndexedData.EvictKey(oi));
	AssertNotNull(cAccess.GetLongString(oi, szData));
	AssertString(szShortText2, szData);

	cController.End();
	cIndexedData.Kill();
	cDataConfig.Kill();


	cFileUtil.RemoveDir(szDirectory);
	cController.Init(szDirectory, NULL);
	cDataConfig.Init(&cController, NULL, 8192, 8192, IWT_No);
	cController.Begin();
	cIndexedData.Init(&cDataConfig);
	cController.End();

	cController.Begin();
	//Cached data.  File not written.
	//Descriptor size different to Set size.
	AssertTrue(cAccess.PutLongString(oi, szLongText));
	AssertTrue(cAccess.PutLongString(oi, szShortText1));
	AssertTrue(cIndexedData.EvictKey(oi));
	AssertNotNull(cAccess.GetLongString(oi, szData));
	AssertString(szShortText1, szData);

	AssertTrue(cIndexedData.Flush(TRUE));
	cController.End();
	cIndexedData.Kill();
	cDataConfig.Kill();


	cController.Init(szDirectory, NULL);
	cDataConfig.Init(&cController, NULL, 8192, 8192, IWT_No);
	cController.Begin();
	cIndexedData.Init(&cDataConfig);
	cController.End();

	cController.Begin();
	//Cached data.  File exists.
	//Descriptor size same as Set size.
	AssertNotNull(cAccess.GetLongString(oi, szData));
	AssertString(szShortText1, szData);
	AssertTrue(cAccess.PutLongString(oi, szShortText2));
	AssertTrue(cIndexedData.EvictKey(oi));
	AssertLongLongInt(0, cIndexedData.NumIndicesCached());
	AssertInt(0, cIndexedData.NumDataCached());
	AssertNotNull(cAccess.GetLongString(oi, szData));
	AssertString(szShortText2, szData);

	cController.End();
	cIndexedData.Kill();
	cDataConfig.Kill();


	cController.Init(szDirectory, NULL);
	cDataConfig.Init(&cController, NULL, 8192, 8192, IWT_No);
	cController.Begin();
	cIndexedData.Init(&cDataConfig);
	cController.End();

	cController.Begin();
	//Cached data.  File exists.
	//Descriptor size different to Set size.
	AssertNotNull(cAccess.GetLongString(oi, szData));
	AssertString(szShortText2, szData);
	AssertTrue(cAccess.PutLongString(oi, szLongText));
	AssertTrue(cIndexedData.EvictKey(oi));
	AssertLongLongInt(0, cIndexedData.NumIndicesCached());
	AssertInt(0, cIndexedData.NumDataCached());
	AssertNotNull(cAccess.GetLongString(oi, szData));
	AssertString(szLongText, szData);

	cController.End();
	cIndexedData.Kill();
	cDataConfig.Kill();

	cFileUtil.RemoveDir(szDirectory);
	cAccess.Kill();
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedDataEvictKey(void)
{
	CIndexedData				cIndexedData;
	char						szHello[] = "Hello";
	char						szWorld[] = "World";
	char						szStream[] = "Stream";
	char						szDirectory[] = "Output" _FS_ "Database1d";
	CFileUtil					cFileUtil;
	unsigned int				uiDataSize;
	char						szData[1024];
	unsigned int				uiSize;
	CValueIndexedDataConfig		cDataConfig;
	CDurableFileController		cController;

	cFileUtil.RemoveDir(szDirectory);

	cController.Init(szDirectory, NULL);
	cDataConfig.Init(&cController, NULL, 8192, 8192, IWT_No);
	cController.Begin();
	cIndexedData.Init(&cDataConfig);
	cController.End();

	cController.Begin();
	AssertLongLongInt(0, cIndexedData.NumIndicesCached());
	AssertInt(0, cIndexedData.NumDataCached());
	AssertInt(3100, cIndexedData.GetIndiciesSystemMemorySize());
	AssertInt(0, cIndexedData.GetDataSystemMemorySize());

	AssertTrue(cIndexedData.Add(0LL, szHello, 6, 0));
	AssertTrue(cIndexedData.Add(2LL, szStream, 7, 0));
	AssertTrue(cIndexedData.Add(4LL, szWorld, 6, 0));
	AssertLongLongInt(3, cIndexedData.NumIndicesCached());
	AssertInt(3, cIndexedData.NumDataCached());
	AssertInt(3608, cIndexedData.GetIndiciesSystemMemorySize());
	AssertInt(55, cIndexedData.GetDataSystemMemorySize());

	cIndexedData.EvictKey(0LL);
	AssertLongLongInt(2, cIndexedData.NumIndicesCached());
	AssertInt(2, cIndexedData.NumDataCached());
	AssertInt(3548, cIndexedData.GetIndiciesSystemMemorySize());
	AssertInt(37, cIndexedData.GetDataSystemMemorySize());

	cIndexedData.EvictKey(4LL);
	AssertLongLongInt(1, cIndexedData.NumIndicesCached());
	AssertInt(1, cIndexedData.NumDataCached());
	AssertInt(3488, cIndexedData.GetIndiciesSystemMemorySize());
	AssertInt(19, cIndexedData.GetDataSystemMemorySize());
	
	cIndexedData.EvictKey(2LL);
	AssertLongLongInt(0, cIndexedData.NumIndicesCached());
	AssertInt(0, cIndexedData.NumDataCached());
	AssertInt(3100, cIndexedData.GetIndiciesSystemMemorySize());
	AssertInt(0, cIndexedData.GetDataSystemMemorySize());

	AssertTrue(cIndexedData.Get(0LL, &uiDataSize, szData, 1024));
	AssertInt(6, uiDataSize);
	AssertString(szHello, szData);
	AssertLongLongInt(1, cIndexedData.NumIndicesCached());
	AssertInt(1, cIndexedData.NumDataCached());
	AssertInt(3500, cIndexedData.GetIndiciesSystemMemorySize());
	AssertInt(18, cIndexedData.GetDataSystemMemorySize());

	AssertTrue(cIndexedData.Get(2LL, &uiDataSize, szData, 1024));
	AssertInt(7, uiDataSize);
	AssertString(szStream, szData);
	AssertLongLongInt(2, cIndexedData.NumIndicesCached());
	AssertInt(2, cIndexedData.NumDataCached());
	AssertInt(3572, cIndexedData.GetIndiciesSystemMemorySize());
	AssertInt(37, cIndexedData.GetDataSystemMemorySize());

	AssertTrue(cIndexedData.Get(4LL, &uiDataSize, szData, 1024));
	AssertInt(6, uiDataSize);
	AssertString(szWorld, szData);
	AssertLongLongInt(3, cIndexedData.NumIndicesCached());
	AssertInt(3, cIndexedData.NumDataCached());
	AssertInt(3644, cIndexedData.GetIndiciesSystemMemorySize());
	AssertInt(55, cIndexedData.GetDataSystemMemorySize());

	uiSize = cIndexedData.Size(0LL);
	AssertInt(6, uiSize);
	uiSize = cIndexedData.Size(2LL);
	AssertInt(7, uiSize);
	uiSize = cIndexedData.Size(4LL);
	AssertInt(6, uiSize);

	cController.End();
	cIndexedData.Kill();
	cDataConfig.Kill();


	cController.Init(szDirectory, NULL);
	cDataConfig.Init(&cController, NULL, 8192, 8192, IWT_No);
	cController.Begin();
	cIndexedData.Init(&cDataConfig);
	cController.End();

	AssertInt(2, cIndexedData.NumFiles());

	cController.Begin();
	AssertLongLongInt(0, cIndexedData.NumIndicesCached());
	AssertInt(0, cIndexedData.NumDataCached());

	uiSize = cIndexedData.Size(0LL);
	AssertInt(6, uiSize);
	uiSize = cIndexedData.Size(2LL);
	AssertInt(7, uiSize);
	uiSize = cIndexedData.Size(4LL);
	AssertInt(6, uiSize);

	cController.End();
	cIndexedData.Kill();
	cDataConfig.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedDataIndexEviction(void)
{
	CEvictedList				cIndexEvictedList;
	CIndexedEvictedList			cKeyDataEvictedList;
	CIndexedData				cIndexedData;
	char						szHello[] = "Hello";
	char						szWorld[] = "World";
	char						szStream[] = "Stream";
	char						szDirectory[] = "Output" _FS_ "Database1e";
	char						szIn[7];
	unsigned int				uiSize;
	filePos						iFileSize;
	CFileUtil					cFileUtil;
	CValueIndexedDataConfig		cDataConfig;
	CDurableFileController		cController;

	cFileUtil.RemoveDir(szDirectory);

	AssertInt(32, sizeof(CIndexedDataDescriptor));

	cIndexEvictedList.Init();
	cKeyDataEvictedList.Init();
	cController.Init(szDirectory, NULL);
	cDataConfig.Init(&cController, NULL, 1024, 3570, IWT_No, &cIndexEvictedList, &cKeyDataEvictedList);  //A little more than two items in the cache...
	cController.Begin();
	cIndexedData.Init(&cDataConfig);
	cController.End();


	cController.Begin();
	AssertTrue(cIndexedData.Add(0LL, szHello, 6, 0));
	AssertInt(1, cIndexedData.NumDataCached());
	AssertInt(sizeof(SIndexedCacheDescriptor) + 6, cIndexedData.TestGetCachedObjectSize(0LL));
	AssertInt(3440, cIndexedData.GetIndiciesSystemMemorySize());

	AssertTrue(cIndexedData.Add(1LL, szWorld, 6, 0));
	AssertInt(2, cIndexedData.NumDataCached());
	AssertLongLongInt(2, cIndexedData.NumIndicesCached());
	AssertInt(sizeof(SIndexedCacheDescriptor) + 6, cIndexedData.TestGetCachedObjectSize(1LL));
	AssertInt(3512, cIndexedData.GetIndiciesSystemMemorySize());

	AssertInt(0, cIndexEvictedList.NumElements());
	AssertTrue(cIndexedData.Add(2LL, szStream, 7, 0));  //Node 0LL evicted here.
	AssertInt(3524, cIndexedData.GetIndiciesSystemMemorySize());
	AssertInt(1, cIndexEvictedList.NumElements());

	AssertInt(2, cIndexedData.NumDataCached());
	AssertInt(2, (int)cIndexedData.NumIndicesCached());
	AssertInt(sizeof(SIndexedCacheDescriptor) + 7, cIndexedData.TestGetCachedObjectSize(2LL));
	AssertInt(0, cIndexedData.TestGetCachedObjectSize(0LL));
	AssertInt(sizeof(SIndexedCacheDescriptor) + 6, cIndexedData.TestGetCachedObjectSize(1LL));
	AssertLongLongInt(2, cIndexedData.NumIndicesCached());
	AssertInt(2, cIndexedData.NumDataCached());

	cIndexEvictedList.Clear();
	cKeyDataEvictedList.Clear();
	AssertTrue(cIndexedData.Flush(TRUE));
	AssertInt(0, cIndexEvictedList.NumElements());
	AssertLongLongInt(3, cIndexedData.NumIndicesCached());
	AssertInt(0, cIndexedData.NumDataCached());
	uiSize = cIndexedData.Size(1LL);
	AssertInt(1, cIndexEvictedList.NumElements());
	AssertInt(6, uiSize);
	AssertLongLongInt(2, cIndexedData.NumIndicesCached());
	AssertInt(0, cIndexedData.NumDataCached());

	AssertTrue(cController.End());
	cIndexedData.Kill();
	cDataConfig.Kill();
	cIndexEvictedList.Kill();
	cKeyDataEvictedList.Kill();

	iFileSize = cFileUtil.Size("Output" _FS_ "Database1e" _FS_ "6_0.DAT");
	AssertLongLongInt(12, iFileSize);
	iFileSize = cFileUtil.Size("Output" _FS_ "Database1e" _FS_ "7_0.DAT");
	AssertLongLongInt(7, iFileSize);

	cKeyDataEvictedList.Init();
	cIndexEvictedList.Init();
	cController.Init(szDirectory, NULL);
	cDataConfig.Init(&cController, NULL, 8192, 8192, IWT_No, &cIndexEvictedList, &cKeyDataEvictedList);
	cController.Begin();
	cIndexedData.Init(&cDataConfig);
	cController.End();
	AssertInt(2, cIndexedData.NumFiles());

	cController.Begin();
	AssertLongLongInt(0, cIndexedData.NumIndicesCached());
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
	AssertInt(3, cIndexedData.NumDataCached());
	AssertLongLongInt(3, cIndexedData.NumIndicesCached());
	cController.End();

	cIndexedData.Kill();
	cDataConfig.Kill();
	cIndexEvictedList.Kill();
	cKeyDataEvictedList.Kill();

	cController.Init(szDirectory, NULL);
	cDataConfig.Init(&cController, NULL, 8192, 8192, IWT_No);
	cController.Begin();
	cIndexedData.Init(&cDataConfig);
	cController.End();

	AssertInt(0, (int)cIndexedData.NumIndicesCached());
	cIndexedData.Kill();
	cDataConfig.Kill();

	cFileUtil.RemoveDir(szDirectory);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedDataEvictAndFlush(void)
{
	CIndexedData				cIndexedData;
	char						szWorld[] = "World";
	char						szStream[] = "Stream";
	char						szDirectory[] = "Output" _FS_ "Database1f";
	char						szIn[8];
	unsigned int				uiSize;
	CFileUtil					cFileUtil;
	unsigned char				ucFlags;
	CValueIndexedDataConfig		cDataConfig;
	CDurableFileController		cController;

	cFileUtil.RemoveDir(szDirectory);

	cController.Init(szDirectory, NULL);
	cDataConfig.Init(&cController, NULL, 8192, 8192, IWT_No);
	cController.Begin();
	cIndexedData.Init(&cDataConfig);
	cController.End();

	cController.Begin();
	AssertTrue(cIndexedData.Add(198732178239018792LL, szStream, 7, 0));
	AssertTrue(cIndexedData.Add(573107892314634784LL, szWorld, 6, 0));

	cIndexedData.EvictKey(198732178239018792LL);
	ucFlags = cIndexedData.GetRootFlags();
	AssertChar(INDEX_TREE_NODE_FLAG_DIRTY_PATH, ucFlags);

	AssertTrue(cIndexedData.Flush(TRUE));

	AssertTrue(cController.End());
	cIndexedData.Kill();
	cDataConfig.Kill();


	cController.Init(szDirectory, NULL);
	cDataConfig.Init(&cController, NULL, 8192, 8192, IWT_No);
	cController.Begin();
	cIndexedData.Init(&cDataConfig);
	cController.End();

	cController.Begin();
	uiSize = cIndexedData.Size(573107892314634784LL);
	AssertInt(6, uiSize);
	memset(szIn, 0, 8);
	AssertTrue(cIndexedData.Get(573107892314634784LL, szIn));
	AssertString("World", szIn);

	uiSize = cIndexedData.Size(198732178239018792LL);
	AssertInt(7, uiSize);
	memset(szIn, 0, 8);
	AssertTrue(cIndexedData.Get(198732178239018792LL, szIn));
	AssertString("Stream", szIn);

	cController.End();
	cIndexedData.Kill();
	cDataConfig.Kill();
	
	cFileUtil.RemoveDir(szDirectory);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedDataFlushAndFlush(void)
{
	CIndexedData				cIndexedData;
	char						szWorld[] = "World";
	char						szStream[] = "Stream";
	char						szDirectory[] = "Output" _FS_ "Database1f";
	char						szIn[8];
	unsigned int				uiSize;
	CFileUtil					cFileUtil;
	CValueIndexedDataConfig		cDataConfig;
	CDurableFileController		cController;

	cFileUtil.RemoveDir(szDirectory);

	cController.Init(szDirectory, NULL);
	cDataConfig.Init(&cController, NULL, 8192, 8192, IWT_No);
	cController.Begin();
	cIndexedData.Init(&cDataConfig);
	cController.End();

	cController.Begin();
	AssertTrue(cIndexedData.Add(198732178239018792LL, szStream, 7, 0));
	AssertTrue(cIndexedData.Flush(TRUE));

	AssertTrue(cController.End());
	cIndexedData.Kill();
	cDataConfig.Kill();

	
	cController.Init(szDirectory, NULL);
	cDataConfig.Init(&cController, NULL, 8192, 8192, IWT_No);
	cController.Begin();
	cIndexedData.Init(&cDataConfig);
	cController.End();

	cController.Begin();
	AssertTrue(cIndexedData.Add(573107892314634784LL, szWorld, 6, 0));
	AssertTrue(cIndexedData.Flush(TRUE));

	cController.End();
	cIndexedData.Kill();
	cDataConfig.Kill();

	cController.Init(szDirectory, NULL);
	cDataConfig.Init(&cController, NULL, 8192, 8192, IWT_No);
	cController.Begin();
	cIndexedData.Init(&cDataConfig);
	cController.End();

	cController.Begin();
	uiSize = cIndexedData.Size(573107892314634784LL);
	AssertInt(6, uiSize);
	memset(szIn, 0, 8);
	AssertTrue(cIndexedData.Get(573107892314634784LL, szIn));
	AssertString("World", szIn);

	uiSize = cIndexedData.Size(198732178239018792LL);
	AssertInt(7, uiSize);
	memset(szIn, 0, 8);
	AssertTrue(cIndexedData.Get(198732178239018792LL, szIn));
	AssertString("Stream", szIn);

	cController.End();
	cIndexedData.Kill();
	cDataConfig.Kill();

	cFileUtil.RemoveDir(szDirectory);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedDataLargeData(void)
{
	CIndexedData				cIndexedData;
	OIndex						OI;
	char						szBig[] = "A Long String";
	char						szSmall[] = "Cat";
	char						szIn[14];
	CFileUtil					cFileUtil;
	char						szDirectory[] = "Output" _FS_ "Database2";
	CValueIndexedDataConfig		cDataConfig;
	CDurableFileController		cController;

	cFileUtil.RemoveDir(szDirectory);

	cController.Init(szDirectory, NULL);
	cDataConfig.Init(&cController, NULL, 34, 8192, IWT_No);
	cController.Begin();
	cIndexedData.Init(&cDataConfig);
	cController.End();
	OI = 0LL;
	AssertInt(0, cIndexedData.NumDataCached());

	cController.Begin();
	AssertTrue(cIndexedData.Add(OI, szBig, 14, 0));
	AssertInt(0, cIndexedData.NumDataCached());
	AssertInt(1, (int)cIndexedData.NumIndicesCached());
	
	AssertTrue(cIndexedData.Get(OI, szIn));
	AssertInt(0, cIndexedData.NumDataCached());
	AssertInt(1, (int)cIndexedData.NumIndicesCached());
	AssertString(szBig, szIn);

	OI = 1LL;
	cIndexedData.Add(OI, szSmall, 4, 0);
	AssertInt(1, cIndexedData.NumDataCached());
	AssertInt(2, (int)cIndexedData.NumIndicesCached());

	OI = 0LL;
	cIndexedData.Get(OI, szIn);
	AssertInt(1, cIndexedData.NumDataCached());
	AssertInt(2, (int)cIndexedData.NumIndicesCached());
	AssertString(szBig, szIn);

	OI = 1LL;
	cIndexedData.Get(OI, szIn);
	AssertInt(1, cIndexedData.NumDataCached());
	AssertInt(2, (int)cIndexedData.NumIndicesCached());
	AssertString(szSmall, szIn);

	AssertTrue(cIndexedData.Flush(TRUE));
	cController.End();
	cIndexedData.Kill();
	cDataConfig.Kill();

	cFileUtil.RemoveDir(szDirectory);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedDataIndexedAdd(void)
{
	CIndexedData				cIndexedData;
	OIndex						oIndex1;
	OIndex						oIndex2;
	char						szBat[] = "Bat";
	char						szCat[] = "Cat";
	char						szDog[] = "Dog";
	char						szFish[] = "Fish";

	char						szHell[] = "Hell";
	char						szMutt[] = "Mutt";
	char						szEve[] = "Eve";
	char						szIn[64];
	CFileUtil					cFileUtil;
	BOOL						bResult;
	char						szDirectory[] = "Output" _FS_ "Database3";
	CValueIndexedDataConfig		cDataConfig;
	CDurableFileController		cController;
	SLogConfig					sLogConfig;

	cFileUtil.RemoveDir(szDirectory);

	cController.Init(szDirectory, NULL);
	cDataConfig.Init(&cController, NULL, 98 + 12, 8192, IWT_No);
	cController.Begin();
	cIndexedData.Init(&cDataConfig);
	cController.End();

	cController.Begin();
	oIndex1 = 0LL;
	bResult = cIndexedData.Add(oIndex1, szBat, 4, 0);
	AssertTrue(bResult);
	AssertInt(1, (int)cIndexedData.NumDataCached());
	AssertInt(0, (int)cIndexedData.NumDatas(4));
	AssertTrue(cIndexedData.Flush(TRUE));
	AssertInt(1, (int)cIndexedData.NumDatas(4));
	AssertInt(0, (int)cIndexedData.NumDataCached());

	sLogConfig = gcLogger.SetSilent();
	bResult = cIndexedData.Add(oIndex1, szCat, 4, 0);
	AssertFalse(bResult);
	gcLogger.SetConfig(&sLogConfig);
	bResult = cIndexedData.Set(oIndex1, szDog, 0);
	AssertTrue(bResult);
	AssertInt(1, (int)cIndexedData.NumDataCached());
	AssertInt(1, (int)cIndexedData.NumDatas(4));
	cIndexedData.Get(oIndex1, szIn);
	AssertString(szDog, szIn);

	bResult = cIndexedData.Set(oIndex1, szFish, 5, 0);
	AssertTrue(bResult);
	AssertInt(1, (int)cIndexedData.NumDataCached());
	cIndexedData.Get(oIndex1, szIn);
	AssertString(szFish, szIn);

	AssertTrue(cIndexedData.Flush(TRUE));
	AssertInt(1, (int)cIndexedData.NumDatas(4));
	AssertInt(1, (int)cIndexedData.NumDatas(5));
	cIndexedData.Get(oIndex1, szIn);
	AssertString(szFish, szIn);

	bResult = cIndexedData.Set(oIndex1, szCat, 4, 0);
	AssertInt(1, (int)cIndexedData.NumElements());
	AssertLongLongInt(1, cIndexedData.NumIndicesCached());
	AssertTrue(bResult);
	AssertTrue(cIndexedData.Flush(TRUE));
	AssertInt(2, (int)cIndexedData.NumDatas(4));  //One is ignored but they are both still in the file.
	AssertInt(1, (int)cIndexedData.NumElements());
	AssertInt(1, (int)cIndexedData.NumIndicesCached());

	oIndex2 = 3LL;
	bResult = cIndexedData.Add(oIndex2, szHell, 5, 0);
	AssertTrue(bResult);
	AssertInt(1, (int)cIndexedData.NumDataCached());
	AssertInt(2, (int)cIndexedData.NumIndicesCached());
	sLogConfig = gcLogger.SetSilent();
	bResult = cIndexedData.Add(oIndex2, szMutt, 5, 0);
	AssertFalse(bResult);
	gcLogger.SetConfig(&sLogConfig);
	bResult = cIndexedData.Set(oIndex2, szEve, 4, 0);
	AssertTrue(bResult);
	AssertInt(1, (int)cIndexedData.NumDataCached());
	AssertInt(2, (int)cIndexedData.NumIndicesCached());
	AssertTrue(cIndexedData.Flush(TRUE));
	AssertInt(3, (int)cIndexedData.NumDatas(4));
	AssertInt(1, (int)cIndexedData.NumDatas(5));
	AssertInt(2, (int)cIndexedData.NumElements());
	cController.End();

	cIndexedData.Kill();
	cDataConfig.Kill();

	cFileUtil.RemoveDir(szDirectory);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedDataDescriptorCaching(void)
{
	CIndexedEvictedList			cKeyDataEvictedList;
	CIndexedData				cIndexedData;
	OIndex						OI;
	CFileUtil					cFileUtil;
	int							iData;
	OIndex						iNumCached;
	char						szDirectory[] = "Output" _FS_ "Database4";
	CValueIndexedDataConfig		cDataConfig;
	CDurableFileController		cController;
	SLogConfig					sLogConfig;

	cFileUtil.RemoveDir(szDirectory);

	cKeyDataEvictedList.Init();
	cController.Init(szDirectory, NULL);
	cDataConfig.Init(&cController, NULL, 96, 3650, IWT_No, NULL, &cKeyDataEvictedList);
	cController.Begin();
	cIndexedData.Init(&cDataConfig);
	cController.End();

	cController.Begin();
	OI = 0LL;
	iData = 77;
	cIndexedData.Add(OI, &iData, 4, 0); OI++;  iData++; 
	cIndexedData.Add(OI, &iData, 4, 0); OI++;  iData++;
	iData = 0; OI = 0LL; cIndexedData.Get(OI, (void*)&iData);
	AssertInt(77, iData);
	AssertInt(0, cKeyDataEvictedList.NumElements());

	OI = 2LL;
	iData = 79;
	cIndexedData.Add(OI, &iData, 4, 0); OI++;  iData++;
	iData = 0; OI = 0LL; cIndexedData.Get(OI, (void*)&iData);
	AssertInt(77, iData);
	AssertInt(0, cKeyDataEvictedList.NumElements());

	sLogConfig = gcLogger.SetSilent();
	OI = 2LL;
	iData = 80;
	cIndexedData.Add(OI, &iData, 4, 0); OI++;  iData++;
	cIndexedData.Add(OI, &iData, 4, 0); OI++;  iData++;
	gcLogger.SetConfig(&sLogConfig);
	AssertInt(1, cKeyDataEvictedList.NumElements());
	AssertLongLongInt(0, cKeyDataEvictedList.GetKey(0));
	AssertInt(77, *(int*)cKeyDataEvictedList.GetData(0));
	cKeyDataEvictedList.Clear();

	cIndexedData.Add(OI, &iData, 4, 0); OI++;  iData++;
	AssertInt(1, cKeyDataEvictedList.NumElements());
	AssertLongLongInt(1, cKeyDataEvictedList.GetKey(0));
	AssertInt(78, *(int*)cKeyDataEvictedList.GetData(0));
	cKeyDataEvictedList.Clear();

	cIndexedData.Add(OI, &iData, 4, 0); OI++;  iData++;
	AssertInt(1, cKeyDataEvictedList.NumElements());
	AssertLongLongInt(2, cKeyDataEvictedList.GetKey(0));
	AssertInt(79, *(int*)cKeyDataEvictedList.GetData(0));
	cKeyDataEvictedList.Clear();

	cIndexedData.Add(OI, &iData, 4, 0); OI++;  iData++;
	AssertInt(0, cKeyDataEvictedList.NumElements());
	cIndexedData.Add(OI, &iData, 4, 0); OI++;  iData++;
	AssertInt(0, cKeyDataEvictedList.NumElements());
	iData = 0; OI--; cIndexedData.Get(OI, (void*)&iData);
	AssertInt(85, iData);
	AssertInt(0, cKeyDataEvictedList.NumElements());

	iData = 0; OI = 0LL; cIndexedData.Get(OI, (void*)&iData);
	AssertInt(77, iData);
	AssertInt(0, cKeyDataEvictedList.NumElements());

	iNumCached = cIndexedData.NumIndicesCached();
	AssertInt(2, (int)iNumCached);

	AssertTrue(cIndexedData.Flush(TRUE));
	cController.End();
	cIndexedData.Kill();
	cDataConfig.Kill();

	
	cController.Init(szDirectory, NULL);
	cDataConfig.Init(&cController, NULL, 96, 8192, IWT_No);
	cController.Begin();
	cIndexedData.Init(&cDataConfig);
	cController.End();

	cController.Begin();
	iNumCached = cIndexedData.NumIndicesCached();
	AssertInt(0, (int)iNumCached);

	cController.End();
	cIndexedData.Kill();
	cDataConfig.Kill();
	cKeyDataEvictedList.Kill();

	cFileUtil.RemoveDir(szDirectory);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedDataNoCaching(void)
{
	CIndexedData				cIndexedData;
	OIndex						OI;
	CFileUtil					cFileUtil;
	int							iData;
	int64						iNumIndicesCached;
	int64						iNumDataCached;
	CValueIndexedDataConfig		cDataConfig;
	CDurableFileController		cController;
	SLogConfig					sLogConfig;
	char						szDirectory[] = "Output" _FS_ "Database5";

	cFileUtil.RemoveDir(szDirectory);

	cController.Init(szDirectory, NULL);
	cDataConfig.Init(&cController, NULL, 0, 3670, IWT_No);
	cController.Begin();
	cIndexedData.Init(&cDataConfig);
	cController.End();

	cController.Begin();
	OI = 0LL;
	iData = 77;
	cIndexedData.Add(OI, &iData, 4, 0); OI++; 
	cIndexedData.Add(OI, &iData, 4, 0); OI++;
	iData = 0; OI = 0LL; cIndexedData.Get(OI, (void*)&iData);
	AssertInt(77, iData);

	iNumIndicesCached = cIndexedData.NumIndicesCached();
	AssertInt(2, (int)iNumIndicesCached);
	iNumDataCached = cIndexedData.NumDataCached();
	AssertLongLongInt(0, iNumDataCached);

	OI = 2LL;
	cIndexedData.Add(OI, &iData, 4, 0); OI++;
	iData = 0; OI = 0LL; cIndexedData.Get(OI, (void*)&iData);
	AssertInt(77, iData);

	iNumIndicesCached = cIndexedData.NumIndicesCached();
	AssertInt(3, (int)iNumIndicesCached);
	iNumDataCached = cIndexedData.NumDataCached();
	AssertLongLongInt(0, iNumDataCached);

	sLogConfig = gcLogger.SetSilent();
	OI = 2LL;
	cIndexedData.Add(OI, &iData, 4, 0); OI++;
	cIndexedData.Add(OI, &iData, 4, 0); OI++;
	cIndexedData.Add(OI, &iData, 4, 0); OI++;
	cIndexedData.Add(OI, &iData, 4, 0); OI++;
	cIndexedData.Add(OI, &iData, 4, 0); OI++;
	cIndexedData.Add(OI, &iData, 4, 0); OI++;
	gcLogger.SetConfig(&sLogConfig);
	iData = 0; OI--; cIndexedData.Get(OI, (void*)&iData);;

	AssertInt(77, iData);
	iData = 0; OI = 0LL; cIndexedData.Get(OI, (void*)&iData);
	AssertInt(77, iData);

	iNumIndicesCached = cIndexedData.NumIndicesCached();
	AssertInt(3, (int)iNumIndicesCached);
	iNumDataCached = cIndexedData.NumDataCached();
	AssertLongLongInt(0, iNumDataCached);

	cController.End();

	cIndexedData.Kill();
	cDataConfig.Kill();

	cFileUtil.RemoveDir(szDirectory);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedDataGet(void)
{
	CIndexedData				cIndexedData;
	CFileUtil					cFileUtil;
	char						szData[256];
	unsigned int				uiSize;
	char						szSmellsLikeTeenSpirit[] = {"Smells Like Teen Spirit"};
	char						szSeizedPotPlants[] = {"Seized pot plants turn out to be daisies"};
	char						szCallingFromWindows[] = {"I am calling you from Windows"};
	char						szDirectory[] = "Output" _FS_ "Database6";
	CValueIndexedDataConfig		cDataConfig;
	CDurableFileController		cController;

	cFileUtil.RemoveDir(szDirectory);

	cController.Init(szDirectory, NULL);
	cDataConfig.Init(&cController, NULL, 8192, 8192, IWT_No);
	cController.Begin();
	cIndexedData.Init(&cDataConfig);
	cController.End();

	cController.Begin();
	cIndexedData.Add(0x7634, szSmellsLikeTeenSpirit, (int)strlen(szSmellsLikeTeenSpirit)+1, 0);
	cIndexedData.Add(0x3589, szSeizedPotPlants, (int)strlen(szSeizedPotPlants)+1, 0);
	cIndexedData.Add(0x8743, szCallingFromWindows, (int)strlen(szCallingFromWindows)+1, 0);
	
	AssertLongLongInt(3, cIndexedData.NumElements());

	AssertTrue(cIndexedData.Flush(TRUE));
	cController.End();
	cIndexedData.Kill();
	cDataConfig.Kill();


	cController.Init(szDirectory, NULL);
	cDataConfig.Init(&cController, NULL, 8192, 8192, IWT_No);
	cController.Begin();
	cIndexedData.Init(&cDataConfig);
	cController.End();

	cController.Begin();
	AssertLongLongInt(3, cIndexedData.NumElements());

	AssertTrue(cIndexedData.Get(0x7634, &uiSize, szData, 256));
	AssertInt((int)strlen(szSmellsLikeTeenSpirit)+1, uiSize);
	AssertString(szSmellsLikeTeenSpirit, szData);

	AssertTrue(cIndexedData.Get(0x3589, &uiSize, szData, 256));
	AssertInt((int)strlen(szSeizedPotPlants)+1, uiSize);
	AssertString(szSeizedPotPlants, szData);
	
	AssertTrue(cIndexedData.Get(0x8743, &uiSize, szData, 256));
	AssertInt((int)strlen(szCallingFromWindows)+1, uiSize);
	AssertString(szCallingFromWindows, szData);

	cController.End();
	cIndexedData.Kill();
	cDataConfig.Kill();

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

	TestIndexedDataSimple(IWT_Yes);
	TestIndexedDataSimple(IWT_No);
	TestIndexedDataFlushClearCache();
	TestIndexedDataEvictKey();
	TestIndexedDataExplicitKeyEvictionAllKeys();
	TestIndexedDataExplicitKeyEvictionDataChanged();
	TestIndexedDataEvictAndFlush();
	TestIndexedDataFlushAndFlush();
	TestIndexedDataIndexEviction();
	TestIndexedDataIndexedAdd();
	TestIndexedDataDescriptorCaching();
	TestIndexedDataNoCaching();
	TestIndexedDataGet();
	TestIndexedDataLargeData();

	TestStatistics();
	DataMemoryKill();
	MemoryKill();
	FastFunctionsKill();
	TypeConverterKill();
}

