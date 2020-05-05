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
#include "NamedIndexedDataObject.h"
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
	CValueIndexedDataConfig		cIndexConfig;
	CDurableFileController		cController;

	cFileUtil.RemoveDir(szDirectory);

	oiInsipidity = 789983209433243094LL;
	iLenInsipidity = strlen(szInsipidity) + 1;
	oiViolation = 3908343914887489103LL;
	iLenViolation = strlen(szViolation) + 1;

	cController.Init(szDirectory, NULL);
	cIndexConfig.Init(szSubDirectory, 8 KB, 8 KB, eWriteThrough);
	cController.Begin();
	cIndexedData.Init(&cController, &cIndexConfig);
	cController.End();
	
	AssertTrue(cController.Begin());
	AssertTrue(cIndexedData.Add(oiInsipidity, szInsipidity, iLenInsipidity));
	AssertTrue(cIndexedData.Add(oiViolation, szViolation, iLenViolation));

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
	cIndexConfig.Kill();


	cController.Init(szDirectory, NULL);
	cIndexConfig.Init(szSubDirectory, 8 KB, 8 KB, eWriteThrough);
	cController.Begin();
	cIndexedData.Init(&cController, &cIndexConfig);
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
	cIndexConfig.Kill();

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
	CValueIndexedDataConfig		cIndexConfig;
	SLogConfig					sLogConfig;
	CDurableFileController		cController;

	cFileUtil.RemoveDir(szDirectory);

	cController.Init(szDirectory, NULL);
	cIndexConfig.Init(NULL, 8 KB, 8 KB, IWT_No);
	cController.Begin();
	cIndexedData.Init(&cController, &cIndexConfig);
	cController.End();

	cController.Begin();
	AssertLongLongInt(0, cIndexedData.NumIndicesCached());
	AssertInt(0, cIndexedData.NumDataCached());
	AssertInt(3100, cIndexedData.GetIndiciesSystemMemorySize());

	AssertTrue(cIndexedData.Add(1LL, szHello, 6));
	AssertTrue(cIndexedData.Add(2LL, szStream, 7));
	AssertTrue(cIndexedData.Add(4LL, szWorld, 6));
	AssertLongLongInt(3, cIndexedData.NumIndicesCached());
	AssertInt(3, cIndexedData.NumDataCached());
	AssertInt(3596, cIndexedData.GetIndiciesSystemMemorySize());
	AssertInt(55, cIndexedData.GetDataSystemMemorySize());

	cIndexedData.Flush(FALSE);
	AssertLongLongInt(3, cIndexedData.NumIndicesCached());
	AssertInt(3, cIndexedData.NumDataCached());
	AssertInt(3596, cIndexedData.GetIndiciesSystemMemorySize());
	AssertInt(55, cIndexedData.GetDataSystemMemorySize());
	AssertTrue(cIndexedData.IsFlushed());
	
	cIndexedData.Flush();
	cController.End();
	cIndexedData.Kill();
	cIndexConfig.Kill();


	cController.Init(szDirectory, NULL);
	cIndexConfig.Init(NULL, 8 KB, 8 KB, IWT_No);
	cController.Begin();
	cIndexedData.Init(&cController, &cIndexConfig);
	cController.End();

	cController.Begin();
	AssertLongLongInt(0, cIndexedData.NumIndicesCached());
	AssertInt(0, cIndexedData.NumDataCached());
	AssertInt(3100 + 24, cIndexedData.GetIndiciesSystemMemorySize());

	AssertTrue(cIndexedData.Get(1LL, &uiDataSize, szData, 7));
	AssertTrue(cIndexedData.Get(2LL, &uiDataSize, szData, 7));
	AssertTrue(cIndexedData.Get(4LL, &uiDataSize, szData, 7));
	AssertLongLongInt(3, cIndexedData.NumIndicesCached());
	AssertInt(3, cIndexedData.NumDataCached());
	AssertInt(3656, cIndexedData.GetIndiciesSystemMemorySize());
	AssertInt(55, cIndexedData.GetDataSystemMemorySize());

	AssertTrue(cIndexedData.Flush(TRUE));
	AssertLongLongInt(3, cIndexedData.NumIndicesCached());
	AssertInt(0, cIndexedData.NumDataCached());
	AssertInt(3656, cIndexedData.GetIndiciesSystemMemorySize());
	AssertInt(00, cIndexedData.GetDataSystemMemorySize());

	cIndexedData.Flush();
	cController.End();
	cIndexedData.Kill();
	cIndexConfig.Kill();


	cController.Init(szDirectory, NULL);
	cIndexConfig.Init(NULL, 1 MB, 1 MB, IWT_No);
	cController.Begin();
	cIndexedData.Init(&cController, &cIndexConfig);
	cController.End();

	cController.Begin();
	AssertLongLongInt(0, cIndexedData.NumIndicesCached());
	AssertInt(0, cIndexedData.NumDataCached());
	AssertInt(3100 + 24, cIndexedData.GetIndiciesSystemMemorySize());

	sLogConfig = gcLogger.SetSilent();
	AssertFalse(cIndexedData.Add(1LL, szWorld, 6));
	AssertFalse(cIndexedData.Add(2LL, szStream, 7));
	AssertFalse(cIndexedData.Add(4LL, szHello, 6));
	gcLogger.SetConfig(&sLogConfig);
	AssertLongLongInt(3, cIndexedData.NumIndicesCached());
	AssertInt(0, cIndexedData.NumDataCached());
	AssertInt(3656, cIndexedData.GetIndiciesSystemMemorySize());
	AssertInt(0, cIndexedData.GetDataSystemMemorySize());

	AssertTrue(cIndexedData.Get(1LL, &uiDataSize, szData, 7));
	AssertString(szHello, szData);
	AssertTrue(cIndexedData.Get(2LL, &uiDataSize, szData, 7));
	AssertString(szStream, szData);
	AssertTrue(cIndexedData.Get(4LL, &uiDataSize, szData, 7));
	AssertString(szWorld, szData);
	AssertLongLongInt(3, cIndexedData.NumIndicesCached());
	AssertInt(3, cIndexedData.NumDataCached());
	AssertInt(3656, cIndexedData.GetIndiciesSystemMemorySize());
	AssertInt(55, cIndexedData.GetDataSystemMemorySize());

	cIndexedData.Flush();
	cController.End();
	cIndexedData.Kill();
	cIndexConfig.Kill();

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
	CValueIndexedDataConfig		cIndexConfig;
	CDurableFileController		cController;

	cFileUtil.RemoveDir(szDirectory);

	AssertInt(32, sizeof(CIndexedDataDescriptor));

	cController.Init(szDirectory, NULL);
	cIndexConfig.Init(NULL, 8 KB, 8 KB, IWT_No);
	cController.Begin();
	cIndexedData.Init(&cController, &cIndexConfig);
	cController.End();

	cController.Begin();
	AssertLongLongInt(0, cIndexedData.NumIndicesCached());
	AssertInt(0, cIndexedData.NumDataCached());
	AssertInt(3100, cIndexedData.GetIndiciesSystemMemorySize());

	AssertTrue(cIndexedData.Add(1LL, szHello, 6));
	AssertTrue(cIndexedData.Add(2LL, szStream, 7));
	AssertTrue(cIndexedData.Add(4LL, szWorld, 6));
	cIndexedData.Flush(FALSE);
	AssertLongLongInt(3, cIndexedData.NumIndicesCached());
	AssertInt(3, cIndexedData.NumDataCached());
	AssertInt(3596, cIndexedData.GetIndiciesSystemMemorySize());
	AssertInt(55, cIndexedData.GetDataSystemMemorySize());

	AssertTrue(cIndexedData.EvictKey(1LL));
	AssertLongLongInt(2, cIndexedData.NumIndicesCached());
	AssertInt(2, cIndexedData.NumDataCached());
	AssertInt(3536, cIndexedData.GetIndiciesSystemMemorySize());
	AssertInt(37, cIndexedData.GetDataSystemMemorySize());

	AssertTrue(cIndexedData.EvictKey(2LL));
	AssertLongLongInt(1, cIndexedData.NumIndicesCached());
	AssertInt(1, cIndexedData.NumDataCached());
	AssertInt(3476, cIndexedData.GetIndiciesSystemMemorySize());
	AssertInt(18, cIndexedData.GetDataSystemMemorySize());

	AssertTrue(cIndexedData.EvictKey(4LL));
	AssertLongLongInt(0, cIndexedData.NumIndicesCached());
	AssertInt(0, cIndexedData.NumDataCached());
	AssertInt(3100, cIndexedData.GetIndiciesSystemMemorySize());
	AssertInt(0, cIndexedData.GetDataSystemMemorySize());

	AssertTrue(cIndexedData.Get(1LL, &uiDataSize, szData, 7));
	AssertString(szHello, szData);
	AssertTrue(cIndexedData.Get(2LL, &uiDataSize, szData, 7));
	AssertString(szStream, szData);
	AssertTrue(cIndexedData.Get(4LL, &uiDataSize, szData, 7));
	AssertString(szWorld, szData);
	AssertLongLongInt(3, cIndexedData.NumIndicesCached());
	AssertInt(3, cIndexedData.NumDataCached());
	AssertInt(55, cIndexedData.GetDataSystemMemorySize());

	cIndexedData.Flush();
	cController.End();
	cIndexedData.Kill();
	cIndexConfig.Kill();

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
	CValueIndexedDataConfig		cIndexConfig;
	CDurableFileController		cController;

	AssertInt(20, strlen(szShortText1) + 1);
	AssertInt(20, strlen(szShortText2) + 1);
	AssertInt(176, strlen(szLongText) + 1);

	cFileUtil.RemoveDir(szDirectory);
	cAccess.Init(&cIndexedData);
	oi = 0x7752890759012357LL;

	//New Data
	cController.Init(szDirectory, NULL);
	cIndexConfig.Init(NULL, 8 KB, 8 KB, IWT_No);
	cController.Begin();
	cIndexedData.Init(&cController, &cIndexConfig);
	cController.End();

	cController.Begin();

	AssertTrue(cAccess.PutLongString(oi, szShortText1));
	AssertTrue(cIndexedData.EvictKey(oi));
	AssertLongLongInt(0, cIndexedData.NumIndicesCached());
	AssertInt(0, cIndexedData.NumDataCached());

	AssertNotNull(cAccess.GetLongString(oi, szData));
	AssertString(szShortText1, szData);

	cIndexedData.Flush();
	cController.End();
	cIndexedData.Kill();
	cIndexConfig.Kill();


	cController.Init(szDirectory, NULL);
	cIndexConfig.Init(NULL, 8 KB, 8 KB, IWT_No);
	cController.Begin();
	cIndexedData.Init(&cController, &cIndexConfig);
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

	cIndexedData.Flush();
	cController.End();
	cIndexedData.Kill();
	cIndexConfig.Kill();


	cController.Init(szDirectory, NULL);
	cIndexConfig.Init(NULL, 8 KB, 8 KB, IWT_No);
	cController.Begin();
	cIndexedData.Init(&cController, &cIndexConfig);
	cController.End();

	cController.Begin();
	//Data not cached.  File exists.
	//Descriptor size different to Set size.
	AssertTrue(cAccess.PutLongString(oi, szLongText));
	AssertTrue(cIndexedData.EvictKey(oi));
	AssertNotNull(cAccess.GetLongString(oi, szData));
	AssertString(szLongText, szData);

	cIndexedData.Flush();
	cController.End();
	cIndexedData.Kill();
	cIndexConfig.Kill();


	cFileUtil.RemoveDir(szDirectory);
	cController.Init(szDirectory, NULL);
	cIndexConfig.Init(NULL, 8 KB, 8 KB, IWT_No);
	cController.Begin();
	cIndexedData.Init(&cController, &cIndexConfig);
	cController.End();

	cController.Begin();
	//Cached data.  File not written.
	//Descriptor size same as Set size.
	AssertTrue(cAccess.PutLongString(oi, szShortText1));
	AssertTrue(cAccess.PutLongString(oi, szShortText2));
	AssertTrue(cIndexedData.EvictKey(oi));
	AssertNotNull(cAccess.GetLongString(oi, szData));
	AssertString(szShortText2, szData);

	cIndexedData.Flush();
	cController.End();
	cIndexedData.Kill();
	cIndexConfig.Kill();


	cFileUtil.RemoveDir(szDirectory);
	cController.Init(szDirectory, NULL);
	cIndexConfig.Init(NULL, 8 KB, 8 KB, IWT_No);
	cController.Begin();
	cIndexedData.Init(&cController, &cIndexConfig);
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
	cIndexConfig.Kill();


	cController.Init(szDirectory, NULL);
	cIndexConfig.Init(NULL, 8 KB, 8 KB, IWT_No);
	cController.Begin();
	cIndexedData.Init(&cController, &cIndexConfig);
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

	cIndexedData.Flush();
	cController.End();
	cIndexedData.Kill();
	cIndexConfig.Kill();


	cController.Init(szDirectory, NULL);
	cIndexConfig.Init(NULL, 8 KB, 8 KB, IWT_No);
	cController.Begin();
	cIndexedData.Init(&cController, &cIndexConfig);
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

	cIndexedData.Flush();
	cController.End();
	cIndexedData.Kill();
	cIndexConfig.Kill();

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
	CValueIndexedDataConfig		cIndexConfig;
	CDurableFileController		cController;

	cFileUtil.RemoveDir(szDirectory);

	cController.Init(szDirectory, NULL);
	cIndexConfig.Init(NULL, 8 KB, 8 KB, IWT_No);
	cController.Begin();
	cIndexedData.Init(&cController, &cIndexConfig);
	cController.End();

	cController.Begin();
	AssertLongLongInt(0, cIndexedData.NumIndicesCached());
	AssertInt(0, cIndexedData.NumDataCached());
	AssertInt(3100, cIndexedData.GetIndiciesSystemMemorySize());
	AssertInt(0, cIndexedData.GetDataSystemMemorySize());

	AssertTrue(cIndexedData.Add(1LL, szHello, 6));
	AssertTrue(cIndexedData.Add(2LL, szStream, 7));
	AssertTrue(cIndexedData.Add(4LL, szWorld, 6));
	AssertLongLongInt(3, cIndexedData.NumIndicesCached());
	AssertInt(3, cIndexedData.NumDataCached());
	AssertInt(3596, cIndexedData.GetIndiciesSystemMemorySize());
	AssertInt(55, cIndexedData.GetDataSystemMemorySize());

	cIndexedData.EvictKey(1LL);
	AssertLongLongInt(2, cIndexedData.NumIndicesCached());
	AssertInt(2, cIndexedData.NumDataCached());
	AssertInt(3536, cIndexedData.GetIndiciesSystemMemorySize());
	AssertInt(37, cIndexedData.GetDataSystemMemorySize());

	cIndexedData.EvictKey(4LL);
	AssertLongLongInt(1, cIndexedData.NumIndicesCached());
	AssertInt(1, cIndexedData.NumDataCached());
	AssertInt(3476, cIndexedData.GetIndiciesSystemMemorySize());
	AssertInt(19, cIndexedData.GetDataSystemMemorySize());
	
	cIndexedData.EvictKey(2LL);
	AssertLongLongInt(0, cIndexedData.NumIndicesCached());
	AssertInt(0, cIndexedData.NumDataCached());
	AssertInt(3100, cIndexedData.GetIndiciesSystemMemorySize());
	AssertInt(0, cIndexedData.GetDataSystemMemorySize());

	AssertTrue(cIndexedData.Get(1LL, &uiDataSize, szData, 1024));
	AssertInt(6, uiDataSize);
	AssertString(szHello, szData);
	AssertLongLongInt(1, cIndexedData.NumIndicesCached());
	AssertInt(1, cIndexedData.NumDataCached());
	AssertInt(3488, cIndexedData.GetIndiciesSystemMemorySize());
	AssertInt(18, cIndexedData.GetDataSystemMemorySize());

	AssertTrue(cIndexedData.Get(2LL, &uiDataSize, szData, 1024));
	AssertInt(7, uiDataSize);
	AssertString(szStream, szData);
	AssertLongLongInt(2, cIndexedData.NumIndicesCached());
	AssertInt(2, cIndexedData.NumDataCached());
	AssertInt(3560, cIndexedData.GetIndiciesSystemMemorySize());
	AssertInt(37, cIndexedData.GetDataSystemMemorySize());

	AssertTrue(cIndexedData.Get(4LL, &uiDataSize, szData, 1024));
	AssertInt(6, uiDataSize);
	AssertString(szWorld, szData);
	AssertLongLongInt(3, cIndexedData.NumIndicesCached());
	AssertInt(3, cIndexedData.NumDataCached());
	AssertInt(3632, cIndexedData.GetIndiciesSystemMemorySize());
	AssertInt(55, cIndexedData.GetDataSystemMemorySize());

	uiSize = cIndexedData.Size(1LL);
	AssertInt(6, uiSize);
	uiSize = cIndexedData.Size(2LL);
	AssertInt(7, uiSize);
	uiSize = cIndexedData.Size(4LL);
	AssertInt(6, uiSize);

	cIndexedData.Flush();
	cController.End();
	cIndexedData.Kill();
	cIndexConfig.Kill();


	cController.Init(szDirectory, NULL);
	cIndexConfig.Init(NULL, 8 KB, 8 KB, IWT_No);
	cController.Begin();
	cIndexedData.Init(&cController, &cIndexConfig);
	cController.End();

	AssertInt(2, cIndexedData.NumFiles());

	cController.Begin();
	AssertLongLongInt(0, cIndexedData.NumIndicesCached());
	AssertInt(0, cIndexedData.NumDataCached());

	uiSize = cIndexedData.Size(1LL);
	AssertInt(6, uiSize);
	uiSize = cIndexedData.Size(2LL);
	AssertInt(7, uiSize);
	uiSize = cIndexedData.Size(4LL);
	AssertInt(6, uiSize);

	cController.End();
	cIndexedData.Kill();
	cIndexConfig.Kill();

	cFileUtil.RemoveDir(szDirectory);
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
	CValueIndexedDataConfig		cIndexConfig;
	CDurableFileController		cController;

	cFileUtil.RemoveDir(szDirectory);

	AssertInt(32, sizeof(CIndexedDataDescriptor));

	cIndexEvictedList.Init();
	cKeyDataEvictedList.Init();
	cController.Init(szDirectory, NULL);
	cIndexConfig.Init(NULL, 1024, 3570, IWT_No, &cIndexEvictedList, &cKeyDataEvictedList);  //A little more than two items in the cache...
	cController.Begin();
	cIndexedData.Init(&cController, &cIndexConfig);
	cController.End();


	cController.Begin();
	AssertTrue(cIndexedData.Add(4LL, szHello, 6));
	AssertInt(1, cIndexedData.NumDataCached());
	AssertInt(sizeof(SIndexedCacheDescriptor) + 6, cIndexedData.TestGetCachedObjectSize(4LL));
	AssertInt(3440, cIndexedData.GetIndiciesSystemMemorySize());

	AssertTrue(cIndexedData.Add(1LL, szWorld, 6));
	AssertInt(2, cIndexedData.NumDataCached());
	AssertLongLongInt(2, cIndexedData.NumIndicesCached());
	AssertInt(sizeof(SIndexedCacheDescriptor) + 6, cIndexedData.TestGetCachedObjectSize(1LL));
	AssertInt(3536, cIndexedData.GetIndiciesSystemMemorySize());

	AssertInt(0, cIndexEvictedList.NumElements());
	AssertTrue(cIndexedData.Add(2LL, szStream, 7));  //Node 4LL evicted here.
	AssertInt(3536, cIndexedData.GetIndiciesSystemMemorySize());
	AssertInt(1, cIndexEvictedList.NumElements());

	AssertInt(2, cIndexedData.NumDataCached());
	AssertInt(2, (int)cIndexedData.NumIndicesCached());
	AssertInt(sizeof(SIndexedCacheDescriptor) + 7, cIndexedData.TestGetCachedObjectSize(2LL));
	AssertInt(0, cIndexedData.TestGetCachedObjectSize(4LL));
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

	AssertTrue(cIndexedData.Flush());
	AssertTrue(cController.End());
	cIndexedData.Kill();
	cIndexConfig.Kill();
	cIndexEvictedList.Kill();
	cKeyDataEvictedList.Kill();

	iFileSize = cFileUtil.Size("Output" _FS_ "Database1e" _FS_ "6_0.DAT");
	AssertLongLongInt(12, iFileSize);
	iFileSize = cFileUtil.Size("Output" _FS_ "Database1e" _FS_ "7_0.DAT");
	AssertLongLongInt(7, iFileSize);

	cKeyDataEvictedList.Init();
	cIndexEvictedList.Init();
	cController.Init(szDirectory, NULL);
	cIndexConfig.Init(NULL, 8 KB, 8 KB, IWT_No, &cIndexEvictedList, &cKeyDataEvictedList);
	cController.Begin();
	cIndexedData.Init(&cController, &cIndexConfig);
	cController.End();
	AssertInt(2, cIndexedData.NumFiles());

	cController.Begin();
	AssertLongLongInt(0, cIndexedData.NumIndicesCached());
	AssertInt(0, cIndexedData.NumDataCached());

	uiSize = cIndexedData.Size(4LL);
	AssertInt(6, uiSize);
	memset(szIn, 0, 7);
	AssertTrue(cIndexedData.Get(4LL, szIn));
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

	uiSize = cIndexedData.Size(4LL);
	AssertInt(6, uiSize);
	memset(szIn, 0, 7);
	AssertTrue(cIndexedData.Get(4LL, szIn));
	AssertString("Hello", szIn);
	AssertInt(3, cIndexedData.NumDataCached());
	AssertLongLongInt(3, cIndexedData.NumIndicesCached());
	AssertTrue(cIndexedData.Flush());
	AssertTrue(cController.End());

	cIndexedData.Kill();
	cIndexConfig.Kill();
	cIndexEvictedList.Kill();
	cKeyDataEvictedList.Kill();

	cController.Init(szDirectory, NULL);
	cIndexConfig.Init(NULL, 8 KB, 8 KB, IWT_No);
	cController.Begin();
	cIndexedData.Init(&cController, &cIndexConfig);
	cController.End();

	AssertInt(0, (int)cIndexedData.NumIndicesCached());
	cIndexedData.Kill();
	cIndexConfig.Kill();

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
	CValueIndexedDataConfig		cIndexConfig;
	CDurableFileController		cController;

	cFileUtil.RemoveDir(szDirectory);

	cController.Init(szDirectory, NULL);
	cIndexConfig.Init(NULL, 8 KB, 8 KB, IWT_No);
	cController.Begin();
	cIndexedData.Init(&cController, &cIndexConfig);
	cController.End();

	cController.Begin();
	AssertTrue(cIndexedData.Add(198732178239018792LL, szStream, 7));
	AssertTrue(cIndexedData.Add(573107892314634784LL, szWorld, 6));

	cIndexedData.EvictKey(198732178239018792LL);
	ucFlags = cIndexedData.GetRootFlags();
	AssertChar(INDEX_TREE_NODE_FLAG_DIRTY_PATH, ucFlags);

	AssertTrue(cIndexedData.Flush(TRUE));

	AssertTrue(cController.End());
	cIndexedData.Kill();
	cIndexConfig.Kill();


	cController.Init(szDirectory, NULL);
	cIndexConfig.Init(NULL, 8 KB, 8 KB, IWT_No);
	cController.Begin();
	cIndexedData.Init(&cController, &cIndexConfig);
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
	cIndexConfig.Kill();
	
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
	CValueIndexedDataConfig		cIndexConfig;
	CDurableFileController		cController;

	cFileUtil.RemoveDir(szDirectory);

	cController.Init(szDirectory, NULL);
	cIndexConfig.Init(NULL, 8 KB, 8 KB, IWT_No);
	cController.Begin();
	cIndexedData.Init(&cController, &cIndexConfig);
	cController.End();

	cController.Begin();
	AssertTrue(cIndexedData.Add(198732178239018792LL, szStream, 7));
	AssertTrue(cIndexedData.Flush(TRUE));

	AssertTrue(cController.End());
	cIndexedData.Kill();
	cIndexConfig.Kill();

	
	cController.Init(szDirectory, NULL);
	cIndexConfig.Init(NULL, 8 KB, 8 KB, IWT_No);
	cController.Begin();
	cIndexedData.Init(&cController, &cIndexConfig);
	cController.End();

	cController.Begin();
	AssertTrue(cIndexedData.Add(573107892314634784LL, szWorld, 6));
	AssertTrue(cIndexedData.Flush(TRUE));

	cController.End();
	cIndexedData.Kill();
	cIndexConfig.Kill();

	cController.Init(szDirectory, NULL);
	cIndexConfig.Init(NULL, 8 KB, 8 KB, IWT_No);
	cController.Begin();
	cIndexedData.Init(&cController, &cIndexConfig);
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
	cIndexConfig.Kill();

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
	CValueIndexedDataConfig		cIndexConfig;
	CDurableFileController		cController;

	cFileUtil.RemoveDir(szDirectory);

	cController.Init(szDirectory, NULL);
	cIndexConfig.Init(NULL, 34, 8 KB, IWT_No);
	cController.Begin();
	cIndexedData.Init(&cController, &cIndexConfig);
	cController.End();
	OI = 4LL;
	AssertInt(0, cIndexedData.NumDataCached());

	cController.Begin();
	AssertTrue(cIndexedData.Add(OI, szBig, 14));
	AssertInt(0, cIndexedData.NumDataCached());
	AssertInt(1, (int)cIndexedData.NumIndicesCached());
	
	AssertTrue(cIndexedData.Get(OI, szIn));
	AssertInt(0, cIndexedData.NumDataCached());
	AssertInt(1, (int)cIndexedData.NumIndicesCached());
	AssertString(szBig, szIn);

	OI = 1LL;
	cIndexedData.Add(OI, szSmall, 4);
	AssertInt(1, cIndexedData.NumDataCached());
	AssertInt(2, (int)cIndexedData.NumIndicesCached());

	OI = 4LL;
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
	cIndexConfig.Kill();

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
	CValueIndexedDataConfig		cIndexConfig;
	CDurableFileController		cController;
	SLogConfig					sLogConfig;

	cFileUtil.RemoveDir(szDirectory);

	cController.Init(szDirectory, NULL);
	cIndexConfig.Init(NULL, 98 + 12, 8 KB, IWT_No);
	cController.Begin();
	cIndexedData.Init(&cController, &cIndexConfig);
	cController.End();

	cController.Begin();
	oIndex1 = 4LL;
	bResult = cIndexedData.Add(oIndex1, szBat, 4);
	AssertTrue(bResult);
	AssertInt(1, (int)cIndexedData.NumDataCached());
	AssertInt(0, (int)cIndexedData.NumDatas(4));
	AssertTrue(cIndexedData.Flush(TRUE));
	AssertInt(1, (int)cIndexedData.NumDatas(4));
	AssertInt(0, (int)cIndexedData.NumDataCached());

	sLogConfig = gcLogger.SetSilent();
	bResult = cIndexedData.Add(oIndex1, szCat, 4);
	AssertFalse(bResult);
	gcLogger.SetConfig(&sLogConfig);
	bResult = cIndexedData.Set(oIndex1, szDog);
	AssertTrue(bResult);
	AssertInt(1, (int)cIndexedData.NumDataCached());
	AssertInt(1, (int)cIndexedData.NumDatas(4));
	cIndexedData.Get(oIndex1, szIn);
	AssertString(szDog, szIn);

	bResult = cIndexedData.Set(oIndex1, szFish, 5);
	AssertTrue(bResult);
	AssertInt(1, (int)cIndexedData.NumDataCached());
	cIndexedData.Get(oIndex1, szIn);
	AssertString(szFish, szIn);

	AssertTrue(cIndexedData.Flush(TRUE));
	AssertInt(1, (int)cIndexedData.NumDatas(4));
	AssertInt(1, (int)cIndexedData.NumDatas(5));
	cIndexedData.Get(oIndex1, szIn);
	AssertString(szFish, szIn);

	bResult = cIndexedData.Set(oIndex1, szCat, 4);
	AssertInt(1, (int)cIndexedData.NumElements());
	AssertLongLongInt(1, cIndexedData.NumIndicesCached());
	AssertTrue(bResult);
	AssertTrue(cIndexedData.Flush(TRUE));
	AssertInt(2, (int)cIndexedData.NumDatas(4));  //One is ignored but they are both still in the file.
	AssertInt(1, (int)cIndexedData.NumElements());
	AssertInt(1, (int)cIndexedData.NumIndicesCached());

	oIndex2 = 3LL;
	bResult = cIndexedData.Add(oIndex2, szHell, 5);
	AssertTrue(bResult);
	AssertInt(1, (int)cIndexedData.NumDataCached());
	AssertInt(2, (int)cIndexedData.NumIndicesCached());
	sLogConfig = gcLogger.SetSilent();
	bResult = cIndexedData.Add(oIndex2, szMutt, 5);
	AssertFalse(bResult);
	gcLogger.SetConfig(&sLogConfig);
	bResult = cIndexedData.Set(oIndex2, szEve, 4);
	AssertTrue(bResult);
	AssertInt(1, (int)cIndexedData.NumDataCached());
	AssertInt(2, (int)cIndexedData.NumIndicesCached());
	AssertTrue(cIndexedData.Flush(TRUE));
	AssertInt(3, (int)cIndexedData.NumDatas(4));
	AssertInt(1, (int)cIndexedData.NumDatas(5));
	AssertInt(2, (int)cIndexedData.NumElements());
	cController.End();

	cIndexedData.Kill();
	cIndexConfig.Kill();

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
	CValueIndexedDataConfig		cIndexConfig;
	CDurableFileController		cController;
	SLogConfig					sLogConfig;

	cFileUtil.RemoveDir(szDirectory);

	cKeyDataEvictedList.Init();
	cController.Init(szDirectory, NULL);
	cIndexConfig.Init(NULL, 96, 3650, IWT_No, NULL, &cKeyDataEvictedList);
	cController.Begin();
	cIndexedData.Init(&cController, &cIndexConfig);
	cController.End();

	cController.Begin();
	OI = 1LL;
	iData = 77;
	cIndexedData.Add(OI, &iData, 4); OI++;  iData++; 
	cIndexedData.Add(OI, &iData, 4); OI++;  iData++;
	iData = 0; OI = 1LL; cIndexedData.Get(OI, (void*)&iData);
	AssertInt(77, iData);
	AssertInt(0, cKeyDataEvictedList.NumElements());

	OI = 3LL;
	iData = 79;
	cIndexedData.Add(OI, &iData, 4); OI++;  iData++;
	iData = 0; OI = 1LL; cIndexedData.Get(OI, (void*)&iData);
	AssertInt(77, iData);
	AssertInt(0, cKeyDataEvictedList.NumElements());

	sLogConfig = gcLogger.SetSilent();
	OI = 3LL;
	iData = 80;
	cIndexedData.Add(OI, &iData, 4); OI++;  iData++;
	cIndexedData.Add(OI, &iData, 4); OI++;  iData++;
	gcLogger.SetConfig(&sLogConfig);
	AssertInt(1, cKeyDataEvictedList.NumElements());
	AssertLongLongInt(1LL, cKeyDataEvictedList.GetKey(0));
	AssertInt(77, *(int*)cKeyDataEvictedList.GetData(0));
	cKeyDataEvictedList.Clear();

	cIndexedData.Add(OI, &iData, 4); OI++;  iData++;
	AssertInt(1, cKeyDataEvictedList.NumElements());
	AssertLongLongInt(2LL, cKeyDataEvictedList.GetKey(0));
	AssertInt(78, *(int*)cKeyDataEvictedList.GetData(0));
	cKeyDataEvictedList.Clear();

	cIndexedData.Add(OI, &iData, 4); OI++;  iData++;
	AssertInt(1, cKeyDataEvictedList.NumElements());
	AssertLongLongInt(3LL, cKeyDataEvictedList.GetKey(0));
	AssertInt(79, *(int*)cKeyDataEvictedList.GetData(0));
	cKeyDataEvictedList.Clear();

	cIndexedData.Add(OI, &iData, 4); OI++;  iData++;
	AssertInt(0, cKeyDataEvictedList.NumElements());
	cIndexedData.Add(OI, &iData, 4); OI++;  iData++;
	AssertInt(0, cKeyDataEvictedList.NumElements());
	iData = 0; OI--; cIndexedData.Get(OI, (void*)&iData);
	AssertInt(85, iData);
	AssertInt(0, cKeyDataEvictedList.NumElements());

	iData = 0; OI = 1LL; cIndexedData.Get(OI, (void*)&iData);
	AssertInt(77, iData);
	AssertInt(0, cKeyDataEvictedList.NumElements());

	iNumCached = cIndexedData.NumIndicesCached();
	AssertInt(2, (int)iNumCached);

	AssertTrue(cIndexedData.Flush(TRUE));
	cController.End();
	cIndexedData.Kill();
	cIndexConfig.Kill();

	
	cController.Init(szDirectory, NULL);
	cIndexConfig.Init(NULL, 96, 8 KB, IWT_No);
	cController.Begin();
	cIndexedData.Init(&cController, &cIndexConfig);
	cController.End();

	cController.Begin();
	iNumCached = cIndexedData.NumIndicesCached();
	AssertInt(0, (int)iNumCached);

	cController.End();
	cIndexedData.Kill();
	cIndexConfig.Kill();
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
	CValueIndexedDataConfig		cIndexConfig;
	CDurableFileController		cController;
	SLogConfig					sLogConfig;
	char						szDirectory[] = "Output" _FS_ "Database5";

	cFileUtil.RemoveDir(szDirectory);

	cController.Init(szDirectory, NULL);
	cIndexConfig.Init(NULL, 0, 3670, IWT_No);
	cController.Begin();
	cIndexedData.Init(&cController, &cIndexConfig);
	cController.End();

	cController.Begin();
	OI = 1LL;
	iData = 77;
	cIndexedData.Add(OI, &iData, 4); OI++; 
	cIndexedData.Add(OI, &iData, 4); OI++;
	iData = 0; OI = 1LL; cIndexedData.Get(OI, (void*)&iData);
	AssertInt(77, iData);

	iNumIndicesCached = cIndexedData.NumIndicesCached();
	AssertInt(2, (int)iNumIndicesCached);
	iNumDataCached = cIndexedData.NumDataCached();
	AssertLongLongInt(0, iNumDataCached);

	OI = 3LL;
	cIndexedData.Add(OI, &iData, 4); OI++;
	iData = 0; OI = 1LL; cIndexedData.Get(OI, (void*)&iData);
	AssertInt(77, iData);

	iNumIndicesCached = cIndexedData.NumIndicesCached();
	AssertInt(3, (int)iNumIndicesCached);
	iNumDataCached = cIndexedData.NumDataCached();
	AssertLongLongInt(0, iNumDataCached);

	sLogConfig = gcLogger.SetSilent();
	OI = 3LL;
	cIndexedData.Add(OI, &iData, 4); OI++;
	cIndexedData.Add(OI, &iData, 4); OI++;
	cIndexedData.Add(OI, &iData, 4); OI++;
	cIndexedData.Add(OI, &iData, 4); OI++;
	cIndexedData.Add(OI, &iData, 4); OI++;
	cIndexedData.Add(OI, &iData, 4); OI++;
	gcLogger.SetConfig(&sLogConfig);
	iData = 0; OI--; cIndexedData.Get(OI, (void*)&iData);;

	AssertInt(77, iData);
	iData = 0; OI = 1LL; cIndexedData.Get(OI, (void*)&iData);
	AssertInt(77, iData);

	iNumIndicesCached = cIndexedData.NumIndicesCached();
	AssertInt(3, (int)iNumIndicesCached);
	iNumDataCached = cIndexedData.NumDataCached();
	AssertLongLongInt(0, iNumDataCached);

	AssertTrue(cIndexedData.Flush());
	AssertTrue(cController.End());

	cIndexedData.Kill();
	cIndexConfig.Kill();

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
	CValueIndexedDataConfig		cIndexConfig;
	CDurableFileController		cController;

	cFileUtil.RemoveDir(szDirectory);

	cController.Init(szDirectory, NULL);
	cIndexConfig.Init(NULL, 8 KB, 8 KB, IWT_No);
	cController.Begin();
	cIndexedData.Init(&cController, &cIndexConfig);
	cController.End();

	cController.Begin();
	cIndexedData.Add(0x7634, szSmellsLikeTeenSpirit, (int)strlen(szSmellsLikeTeenSpirit)+1);
	cIndexedData.Add(0x3589, szSeizedPotPlants, (int)strlen(szSeizedPotPlants)+1);
	cIndexedData.Add(0x8743, szCallingFromWindows, (int)strlen(szCallingFromWindows)+1);
	
	AssertLongLongInt(3, cIndexedData.NumElements());

	AssertTrue(cIndexedData.Flush(TRUE));
	cController.End();
	cIndexedData.Kill();
	cIndexConfig.Kill();


	cController.Init(szDirectory, NULL);
	cIndexConfig.Init(NULL, 8 KB, 8 KB, IWT_No);
	cController.Begin();
	cIndexedData.Init(&cController, &cIndexConfig);
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
	cIndexConfig.Kill();

	cFileUtil.RemoveDir(szDirectory);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedDataSubDirectories(void)
{
	CIndexedData				cIndexedData;
	CFileUtil					cFileUtil;
	char						szGroot[] = { "I am Groot" };
	char						szDirectory[] = "Output" _FS_ "Database7" _FS_ "Write";
	char						szRewriteDirectory[] = "Output" _FS_ "Database7" _FS_ "Rewrite";
	CValueIndexedDataConfig		cIndexConfig;
	CDurableFileController		cController;
	CIndexedDataAccess			cAccess;

	cFileUtil.RemoveDir("Output" _FS_ "Database7");

	cController.Init(szDirectory, szRewriteDirectory);
	cIndexConfig.Init("Forest of Solitude", 8 KB, 8 KB, IWT_No);
	cController.Begin();
	cIndexedData.Init(&cController, &cIndexConfig);
	cController.End();

	cAccess.Init(&cIndexedData);
	cController.Begin();
	cAccess.PutLongString(0x7fffffffffffffffLL, szGroot);

	AssertLongLongInt(1, cIndexedData.NumElements());

	cIndexedData.Flush();
	cAccess.Kill();
	cController.End();
	cIndexedData.Kill();
	cIndexConfig.Kill();

	cFileUtil.RemoveDir("Output" _FS_ "Database7");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedDataRemove(EIndexWriteThrough eWriteThrough)
{
	CIndexedData				cIndexedData;
	CFileUtil					cFileUtil;
	char						szData[256];
	unsigned int				uiSize;
	char						szSmellsLikeTeenSpirit[] = { "Smells Like Teen Spirit" };
	char						szSeizedPotPlants[] = { "Seized pot plants turn out to be daisies" };
	char						szCallingFromWindows[] = { "I am calling you from Windows" };
	char						szDirectory[] = "Output" _FS_ "Database8";
	CValueIndexedDataConfig		cIndexConfig;
	CDurableFileController		cController;

	cFileUtil.RemoveDir(szDirectory);


	cController.Init(szDirectory, NULL);
	cIndexConfig.Init(NULL, 8 KB, 8 KB, eWriteThrough);
	cController.Begin();
	cIndexedData.Init(&cController, &cIndexConfig);
	cController.End();

	cController.Begin();
	cIndexedData.Add(0x7634, szSmellsLikeTeenSpirit, (int)strlen(szSmellsLikeTeenSpirit) + 1);
	cIndexedData.Add(0x3589, szSeizedPotPlants, (int)strlen(szSeizedPotPlants) + 1);
	cIndexedData.Add(0x8743, szCallingFromWindows, (int)strlen(szCallingFromWindows) + 1);
	AssertLongLongInt(3, cIndexedData.NumElements());
	AssertTrue(cIndexedData.Contains(0x7634));
	AssertTrue(cIndexedData.Contains(0x3589));
	AssertTrue(cIndexedData.Contains(0x8743));

	AssertTrue(cIndexedData.Flush(TRUE));
	cController.End();
	cIndexedData.Kill();
	cIndexConfig.Kill();


	cController.Init(szDirectory, NULL);
	cIndexConfig.Init(NULL, 8 KB, 8 KB, eWriteThrough);
	cController.Begin();
	cIndexedData.Init(&cController, &cIndexConfig);
	cController.End();

	cController.Begin();
	AssertTrue(cIndexedData.Contains(0x7634));
	AssertTrue(cIndexedData.Contains(0x3589));
	AssertTrue(cIndexedData.Contains(0x8743));

	cController.End();
	cIndexedData.Kill();
	cIndexConfig.Kill();


	cController.Init(szDirectory, NULL);
	cIndexConfig.Init(NULL, 8 KB, 8 KB, eWriteThrough);
	cController.Begin();
	cIndexedData.Init(&cController, &cIndexConfig);
	cController.End();

	cController.Begin();
	AssertTrue(cIndexedData.Remove(0x7634));
	AssertLongLongInt(2, cIndexedData.NumElements());
	AssertFalse(cIndexedData.Contains(0x7634));
	AssertTrue(cIndexedData.Contains(0x3589));
	AssertTrue(cIndexedData.Contains(0x8743));
	AssertFalse(cIndexedData.Get(0x7634, &uiSize, szData, 256));

	AssertTrue(cIndexedData.Flush(TRUE));
	cController.End();
	cIndexedData.Kill();
	cIndexConfig.Kill();


	cController.Init(szDirectory, NULL);
	cIndexConfig.Init(NULL, 8 KB, 8 KB, eWriteThrough);
	cController.Begin();
	cIndexedData.Init(&cController, &cIndexConfig);
	cController.End();

	cController.Begin();
	AssertTrue(cIndexedData.Remove(0x3589));
	AssertTrue(cIndexedData.Remove(0x8743));
	AssertFalse(cIndexedData.Contains(0x7634));
	AssertFalse(cIndexedData.Contains(0x3589));
	AssertFalse(cIndexedData.Contains(0x8743));
	AssertLongLongInt(0, cIndexedData.NumElements());
	AssertFalse(cIndexedData.Remove(0x7634));
	AssertFalse(cIndexedData.Remove(0x3589));
	AssertFalse(cIndexedData.Remove(0x8743));

	AssertTrue(cIndexedData.Flush(TRUE));
	AssertFalse(cIndexedData.Remove(0x7634));
	AssertFalse(cIndexedData.Remove(0x3589));
	AssertFalse(cIndexedData.Remove(0x8743));

	cController.End();
	cIndexedData.Kill();
	cIndexConfig.Kill();


	cFileUtil.RemoveDir(szDirectory);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexedDataRemove2(EIndexWriteThrough eWriteThrough)
{
	CIndexedData					cIndexedData;
	CFileUtil						cFileUtil;
	CTestNamedIndexedDataObject		cObject1;
	CTestNamedIndexedDataObject		cObject2;
	CTestNamedIndexedDataObject		cObject3;
	CTestNamedIndexedDataObject		cResult;
	char							szDirectory[] = "Output" _FS_ "Database8a";
	CValueIndexedDataConfig			cIndexConfig;
	CDurableFileController			cController;
	BOOL							bResult;

	cFileUtil.RemoveDir(szDirectory);


	cController.Init(szDirectory, NULL);
	cIndexConfig.Init(NULL, 8 KB, 8 KB, eWriteThrough);
	cController.Begin();
	cIndexedData.Init(&cController, &cIndexConfig);
	cController.End();

	cController.Begin();
	cObject1.Init("Rutherford", 1871, 1937);
	cIndexedData.Add(0x0102LL, &cObject1, cObject1.Size());
	cObject2.Init("Bohr", 1885, 1962);
	cIndexedData.Add(0x0203LL, &cObject2, cObject2.Size());
	cObject2.Init("Planck", 1858, 1947);
	cIndexedData.Add(0x0304LL, &cObject3, cObject3.Size());
	AssertLongLongInt(3, cIndexedData.NumIndices());
	AssertTrue(cIndexedData.Contains(0x0102LL));
	AssertTrue(cIndexedData.Contains(0x0203LL));
	AssertTrue(cIndexedData.Contains(0x0304LL));

	cResult.Init();
	bResult = cIndexedData.Get(0x0102LL, &cResult);
	bResult = cIndexedData.Remove(0x0102LL);
	AssertTrue(bResult);
	AssertFalse(cIndexedData.Contains(0x0102LL));
	AssertTrue(cIndexedData.Contains(0x0203LL));
	AssertTrue(cIndexedData.Contains(0x0304LL));
	if (eWriteThrough == IWT_No) cIndexedData.Flush();
	cController.End();

	cIndexedData.Kill();
	cController.Kill();
	cIndexConfig.Kill();


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
	TestIndexedDataSubDirectories();
	TestIndexedDataRemove(IWT_Yes);
	TestIndexedDataRemove(IWT_No);
	TestIndexedDataRemove2(IWT_Yes);
	TestIndexedDataRemove2(IWT_No);

	TestStatistics();
	DataMemoryKill();
	MemoryKill();
	FastFunctionsKill();
	TypeConverterKill();
}

