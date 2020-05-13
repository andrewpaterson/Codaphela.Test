#include "BaseLib/TypeConverter.h"
#include "BaseLib/Define.h"
#include "BaseLib/Logger.h"
#include "BaseLib/GlobalMemory.h"
#include "CoreLib/DurableFileController.h"
#include "CoreLib/NamedIndexedData.h"
#include "CoreLib/ValueIndexedDataConfig.h"
#include "CoreLib/ValueNamedIndexesConfig.h"
#include "StandardLib/BaseObject.h"
#include "TestLib/Assert.h"
#include "NamedIndexedDataObject.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestNamedIndexedDataInit(EIndexWriteThrough eWriteThrough)
{
	CNamedIndexedData					cDatabase;
	CValueIndexedDataConfig				cIndexConfig;
	CValueNamedIndexesConfig			cNamedConfig;
	CNamedIndexedDataConfig				cConfig;
	CDurableFileController				cController;
	CIndexTreeEvictionStrategyRandom	cIndexEvictionStrategy;
	CIndexTreeEvictionStrategyRandom	cNamedEvictionStrategy;
	CFileUtil							cFileUtil;
	
	cFileUtil.RemoveDir("Output" _FS_ "Database1");

	cController.Init("Output" _FS_ "Database1" _FS_ "R", "Output" _FS_ "Database1" _FS_ "W");

	cNamedEvictionStrategy.Init();
	cIndexEvictionStrategy.Init();
	cIndexConfig.Init("IndexData", 8 KB, 8 KB, eWriteThrough, &cIndexEvictionStrategy);
	cNamedConfig.Init("Names", 16 KB, &cNamedEvictionStrategy, eWriteThrough);
	cConfig.Init(&cIndexConfig, &cNamedConfig);
	
	cController.Begin();
	cDatabase.Init(&cController, &cConfig);
	cController.End();
	cConfig.Kill();
	cNamedEvictionStrategy.Kill();
	cIndexEvictionStrategy.Kill();

	cDatabase.Kill();
	cFileUtil.RemoveDir("Output" _FS_ "Database1");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestNamedIndexedDataAddString(EIndexWriteThrough eWriteThrough)
{
	CNamedIndexedData					cDatabase;
	CValueIndexedDataConfig				cIndexConfig;
	CValueNamedIndexesConfig			cNamedConfig;
	CNamedIndexedDataConfig				cConfig;
	CDurableFileController				cController;
	CIndexTreeEvictionStrategyRandom	cIndexEvictionStrategy;
	CIndexTreeEvictionStrategyRandom	cNamedEvictionStrategy;
	CFileUtil							cFileUtil;
	CTestNamedIndexedDataObject			cObject1;
	CTestNamedIndexedDataObject			cObject2;
	CTestNamedIndexedDataObject			cResult;
	BOOL								bResult;

	cFileUtil.RemoveDir("Output" _FS_ "Database2");

	/// Add Name and Index
	cController.Init("Output" _FS_ "Database2" _FS_ "R", "Output" _FS_ "Database2" _FS_ "W");
	cIndexEvictionStrategy.Init();
	cNamedEvictionStrategy.Init();
	cIndexConfig.Init("IndexData", 8 KB, 8 KB, eWriteThrough, &cIndexEvictionStrategy);
	cNamedConfig.Init("Names", 16 KB, &cNamedEvictionStrategy, eWriteThrough);
	cConfig.Init(&cIndexConfig, &cNamedConfig);

	cController.Begin();
	cDatabase.Init(&cController, &cConfig);
	cController.End();
	cConfig.Kill();

	cController.Begin();
	cObject1.Init("Rutherford", 1871, 1937);
	cDatabase.Add(0x0102LL, "Ernest", &cObject1, cObject1.Size());
	if (eWriteThrough == IWT_No) cDatabase.Flush();
	cController.End();

	cController.Begin();
	cObject2.Init("Bohr", 1885, 1962);
	cDatabase.Add(0x0203LL, "Niels", &cObject2, cObject2.Size());
	if (eWriteThrough == IWT_No) cDatabase.Flush();
	cController.End();

	cDatabase.Kill();
	cController.Kill();
	cNamedEvictionStrategy.Kill();
	cIndexEvictionStrategy.Kill();



	//Get by Name
	cController.Init("Output" _FS_ "Database2" _FS_ "R", "Output" _FS_ "Database2" _FS_ "W");
	cNamedEvictionStrategy.Init();
	cIndexEvictionStrategy.Init();
	cIndexConfig.Init("IndexData", 8 KB, 8 KB, eWriteThrough, &cIndexEvictionStrategy);
	cNamedConfig.Init("Names", 16 KB, &cNamedEvictionStrategy, eWriteThrough);
	cConfig.Init(&cIndexConfig, &cNamedConfig);

	cController.Begin();
	cDatabase.Init(&cController, &cConfig);
	cController.End();
	cConfig.Kill();

	cController.Begin();
	bResult = cDatabase.Get("Ernest", &cResult);
	AssertTrue(bResult);
	AssertString("Rutherford", cResult.mszString);
	AssertLongLongInt(1871, cResult.miNumberX);
	AssertLongLongInt(1937, cResult.miNumberY);

	bResult = cDatabase.Get("Niels", &cResult);
	AssertTrue(bResult);
	AssertString("Bohr", cResult.mszString);
	AssertLongLongInt(1885, cResult.miNumberX);
	AssertLongLongInt(1962, cResult.miNumberY);
	cController.End();
	cNamedEvictionStrategy.Kill();
	cIndexEvictionStrategy.Kill();



	//Get by Index
	cController.Init("Output" _FS_ "Database2" _FS_ "R", "Output" _FS_ "Database2" _FS_ "W");
	cNamedEvictionStrategy.Init();
	cIndexEvictionStrategy.Init();
	cIndexConfig.Init("IndexData", 8 KB, 8 KB, eWriteThrough, &cIndexEvictionStrategy);
	cNamedConfig.Init("Names", 16 KB, &cNamedEvictionStrategy, eWriteThrough);
	cConfig.Init(&cIndexConfig, &cNamedConfig);

	cController.Begin();
	cDatabase.Init(&cController, &cConfig);
	cController.End();
	cConfig.Kill();

	cController.Begin();
	bResult = cDatabase.Get(0x0203LL, &cResult);
	AssertTrue(bResult);
	AssertString("Bohr", cResult.mszString);
	AssertLongLongInt(1885, cResult.miNumberX);
	AssertLongLongInt(1962, cResult.miNumberY);

	bResult = cDatabase.Get(0x0102, &cResult);
	AssertTrue(bResult);
	AssertString("Rutherford", cResult.mszString);
	AssertLongLongInt(1871, cResult.miNumberX);
	AssertLongLongInt(1937, cResult.miNumberY);
	cController.End();
	cNamedEvictionStrategy.Kill();
	cIndexEvictionStrategy.Kill();


	//Size by Index
	cController.Init("Output" _FS_ "Database2" _FS_ "R", "Output" _FS_ "Database2" _FS_ "W");
	cNamedEvictionStrategy.Init();
	cIndexEvictionStrategy.Init();
	cIndexConfig.Init("IndexData", 8 KB, 8 KB, eWriteThrough, &cIndexEvictionStrategy);
	cNamedConfig.Init("Names", 16 KB, &cNamedEvictionStrategy, eWriteThrough);
	cConfig.Init(&cIndexConfig, &cNamedConfig);

	cController.Begin();
	cDatabase.Init(&cController, &cConfig);
	cController.End();
	cConfig.Kill();

	cController.Begin();
	AssertInt(sizeof(CTestNamedIndexedDataObject), cDatabase.Size(0x0203));
	AssertInt(sizeof(CTestNamedIndexedDataObject), cDatabase.Size(0x0102));
	AssertLongLongInt(2, cDatabase.NumIndices());
	AssertLongLongInt(2, cDatabase.NumNames());
	cController.End();


	cIndexEvictionStrategy.Kill();
	cNamedEvictionStrategy.Kill();
	cDatabase.Kill();
	cController.Kill();


	cFileUtil.RemoveDir("Output" _FS_ "Database2");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestNamedIndexedDataAddChars(EIndexWriteThrough eWriteThrough)
{
	CNamedIndexedData					cDatabase;
	CValueIndexedDataConfig				cIndexConfig;
	CValueNamedIndexesConfig			cNamedConfig;
	CNamedIndexedDataConfig				cConfig;
	CDurableFileController				cController;
	CIndexTreeEvictionStrategyRandom	cIndexEvictionStrategy;
	CIndexTreeEvictionStrategyRandom	cNamedEvictionStrategy;
	CFileUtil							cFileUtil;
	CTestNamedIndexedDataObject			cObject1;
	CTestNamedIndexedDataObject			cResult;
	BOOL								bResult;
	CChars								szName;

	cFileUtil.RemoveDir("Output" _FS_ "Database2a");

	/// Add Name and Index
	cController.Init("Output" _FS_ "Database2a" _FS_ "R", "Output" _FS_ "Database2a" _FS_ "W");
	cIndexEvictionStrategy.Init();
	cNamedEvictionStrategy.Init();
	cIndexConfig.Init("IndexData", 8 KB, 8 KB, eWriteThrough, &cIndexEvictionStrategy);
	cNamedConfig.Init("Names", 16 KB, &cNamedEvictionStrategy, eWriteThrough);
	cConfig.Init(&cIndexConfig, &cNamedConfig);

	cController.Begin();
	cDatabase.Init(&cController, &cConfig);
	cController.End();
	cConfig.Kill();

	cController.Begin();
	szName.Init("Ernest");
	cObject1.Init("Rutherford", 1871, 1937);
	cDatabase.Add(1LL, &szName, &cObject1, cObject1.Size());
	szName.Kill();
	if (eWriteThrough == IWT_No) cDatabase.Flush();
	cController.End();
	cIndexEvictionStrategy.Kill();
	cNamedEvictionStrategy.Kill();


	//Get by Name
	cController.Init("Output" _FS_ "Database2a" _FS_ "R", "Output" _FS_ "Database2a" _FS_ "W");
	cIndexEvictionStrategy.Init();
	cNamedEvictionStrategy.Init();
	cIndexConfig.Init("IndexData", 8 KB, 8 KB, eWriteThrough, &cIndexEvictionStrategy);
	cNamedConfig.Init("Names", 16 KB, &cNamedEvictionStrategy, eWriteThrough);
	cConfig.Init(&cIndexConfig, &cNamedConfig);

	cController.Begin();
	cDatabase.Init(&cController, &cConfig);
	cController.End();
	cConfig.Kill();

	cController.Begin();
	szName.Init("Ernest");
	bResult = cDatabase.Get(&szName, &cResult);
	szName.Kill();
	AssertTrue(bResult);
	AssertString("Rutherford", cResult.mszString);
	AssertLongLongInt(1871, cResult.miNumberX);
	AssertLongLongInt(1937, cResult.miNumberY);
	AssertLongLongInt(1, cDatabase.NumIndices());
	AssertLongLongInt(1, cDatabase.NumNames());
	cController.End();


	cDatabase.Kill();
	cController.Kill();
	cNamedEvictionStrategy.Kill();
	cIndexEvictionStrategy.Kill();

	cFileUtil.RemoveDir("Output" _FS_ "Database2a");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestNamedIndexedDataAddBad(EIndexWriteThrough eWriteThrough)
{
	CNamedIndexedData					cDatabase;
	CValueIndexedDataConfig				cIndexConfig;
	CValueNamedIndexesConfig			cNamedConfig;
	CNamedIndexedDataConfig				cConfig;
	CDurableFileController				cController;
	CIndexTreeEvictionStrategyRandom	cIndexEvictionStrategy;
	CIndexTreeEvictionStrategyRandom	cNamedEvictionStrategy;
	CFileUtil							cFileUtil;
	CTestNamedIndexedDataObject			cObject1;
	SLogConfig							sLogConfig;
	CChars								szName;

	cFileUtil.RemoveDir("Output" _FS_ "Database2b");

	cController.Init("Output" _FS_ "Database2b" _FS_ "R", "Output" _FS_ "Database2b" _FS_ "W");
	cNamedEvictionStrategy.Init();
	cIndexEvictionStrategy.Init();
	cIndexConfig.Init("IndexData", 8 KB, 8 KB, eWriteThrough, &cIndexEvictionStrategy);
	cNamedConfig.Init("Names", 16 KB, &cNamedEvictionStrategy, eWriteThrough);
	cConfig.Init(&cIndexConfig, &cNamedConfig);

	cController.Begin();
	cDatabase.Init(&cController, &cConfig);
	cController.End();
	cConfig.Kill();

	cController.Begin();
	cObject1.Init("Wild Butterfly", 1871, 1937);
	szName.Init("Hello");
	sLogConfig = gcLogger.SetSilent();
	AssertFalse(cDatabase.Add(1LL, (char*)NULL, &cObject1, cObject1.Size()));
	AssertFalse(cDatabase.Add(1LL, (CChars*)NULL, &cObject1, cObject1.Size()));
	AssertFalse(cDatabase.Add(INVALID_O_INDEX, "Hello", &cObject1, cObject1.Size()));
	AssertFalse(cDatabase.Add(INVALID_O_INDEX, &szName, &cObject1, cObject1.Size()));
	AssertFalse(cDatabase.Add(NULL_O_INDEX, &cObject1, cObject1.Size()));
	AssertFalse(cDatabase.Add(INVALID_O_INDEX, &cObject1, cObject1.Size()));
	AssertFalse(cDatabase.Add(1LL, "Hello", NULL, 0));
	AssertFalse(cDatabase.Add(1LL, &szName, NULL, 0));
	AssertFalse(cDatabase.Add(1LL, NULL, 0));
	gcLogger.SetConfig(&sLogConfig);
	szName.Kill();
	AssertLongLongInt(0, cDatabase.NumIndices());
	AssertLongLongInt(0, cDatabase.NumNames());
	cController.End();


	cDatabase.Kill();
	cController.Kill();
	cIndexEvictionStrategy.Kill();
	cNamedEvictionStrategy.Kill();

	cFileUtil.RemoveDir("Output" _FS_ "Database2b");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestNamedIndexedDataAddIndex(EIndexWriteThrough eWriteThrough)
{
	CNamedIndexedData					cDatabase;
	CValueIndexedDataConfig				cIndexConfig;
	CValueNamedIndexesConfig			cNamedConfig;
	CNamedIndexedDataConfig				cConfig;
	CDurableFileController				cController;
	CIndexTreeEvictionStrategyRandom	cIndexEvictionStrategy;
	CIndexTreeEvictionStrategyRandom	cNamedEvictionStrategy;
	CFileUtil							cFileUtil;
	CTestNamedIndexedDataObject			cObject1;
	CTestNamedIndexedDataObject			cResult;

	cFileUtil.RemoveDir("Output" _FS_ "Database2c");

	/// Add Index
	cController.Init("Output" _FS_ "Database2c" _FS_ "R", "Output" _FS_ "Database2c" _FS_ "W");
	cNamedEvictionStrategy.Init();
	cIndexEvictionStrategy.Init();
	cIndexConfig.Init("IndexData", 8 KB, 8 KB, eWriteThrough, &cIndexEvictionStrategy);
	cNamedConfig.Init("Names", 16 KB, &cNamedEvictionStrategy, eWriteThrough);
	cConfig.Init(&cIndexConfig, &cNamedConfig);

	cController.Begin();
	cDatabase.Init(&cController, &cConfig);
	cController.End();
	cConfig.Kill();

	cController.Begin();
	cObject1.Init("Rutherford", 1871, 1937);
	cDatabase.Add(0x56788435450563LL, &cObject1, cObject1.Size());
	if (eWriteThrough == IWT_No) cDatabase.Flush();
	cController.End();
	cNamedEvictionStrategy.Kill();
	cIndexEvictionStrategy.Kill();


	//Get by Index
	cController.Init("Output" _FS_ "Database2c" _FS_ "R", "Output" _FS_ "Database2c" _FS_ "W");
	cNamedEvictionStrategy.Init();
	cIndexEvictionStrategy.Init();
	cIndexConfig.Init("IndexData", 8 KB, 8 KB, eWriteThrough, &cIndexEvictionStrategy);
	cNamedConfig.Init("Names", 16 KB, &cNamedEvictionStrategy, eWriteThrough);
	cConfig.Init(&cIndexConfig, &cNamedConfig);

	cController.Begin();
	cDatabase.Init(&cController, &cConfig);
	cController.End();
	cConfig.Kill();

	cController.Begin();
	AssertFalse(cDatabase.Get("Ernest", &cResult));
	AssertTrue(cDatabase.Get(0x56788435450563LL, &cResult));
	AssertString("Rutherford", cResult.mszString);
	AssertLongLongInt(1871, cResult.miNumberX);
	AssertLongLongInt(1937, cResult.miNumberY);
	AssertLongLongInt(1, cDatabase.NumIndices());
	AssertLongLongInt(0, cDatabase.NumNames());
	cController.End();


	cIndexEvictionStrategy.Kill();
	cNamedEvictionStrategy.Kill();
	cDatabase.Kill();
	cController.Kill();

	cFileUtil.RemoveDir("Output" _FS_ "Database2c");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestNamedIndexedDataGetName(EIndexWriteThrough eWriteThrough)
{
	CNamedIndexedData					cDatabase;
	CValueIndexedDataConfig				cIndexConfig;
	CValueNamedIndexesConfig			cNamedConfig;
	CNamedIndexedDataConfig				cConfig;
	CDurableFileController				cController;
	CIndexTreeEvictionStrategyRandom	cIndexEvictionStrategy;
	CIndexTreeEvictionStrategyRandom	cNamedEvictionStrategy;
	CFileUtil							cFileUtil;
	int									pai[512];
	CChars								szName;

	cFileUtil.RemoveDir("Output" _FS_ "Database3");

	cController.Init("Output" _FS_ "Database3" _FS_ "R", "Output" _FS_ "Database3" _FS_ "W");
	cNamedEvictionStrategy.Init();
	cIndexEvictionStrategy.Init();
	cIndexConfig.Init("IndexData", 8 KB, 8 KB, eWriteThrough, &cIndexEvictionStrategy);
	cNamedConfig.Init("Names", 16 KB, &cNamedEvictionStrategy, eWriteThrough);
	cConfig.Init(&cIndexConfig, &cNamedConfig);

	cController.Begin();
	cDatabase.Init(&cController, &cConfig);
	cController.End();
	cConfig.Kill();

	cController.Begin();
	memset_fast(pai, 0x04, sizeof(pai));
	cDatabase.Add(0x89072fc3, "graphics/world/city1.3ds", pai, sizeof(pai));

	szName.Init();
	AssertTrue(cDatabase.GetName(0x89072fc3, &szName));
	AssertString("graphics/world/city1.3ds", szName.Text());
	szName.Kill();
	szName.Init();
	AssertFalse(cDatabase.GetName(0x89072fc4, &szName));
	szName.Kill();

	if (eWriteThrough == IWT_No) cDatabase.Flush();
	cController.End();

	cDatabase.Kill();
	cController.Kill();
	cNamedEvictionStrategy.Kill();
	cIndexEvictionStrategy.Kill();

	cFileUtil.RemoveDir("Output" _FS_ "Database3");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestNamedIndexedDataSetIndex(EIndexWriteThrough eWriteThrough)
{
	CNamedIndexedData					cDatabase;
	CValueIndexedDataConfig				cIndexConfig;
	CValueNamedIndexesConfig			cNamedConfig;
	CNamedIndexedDataConfig				cConfig;
	CDurableFileController				cController;
	CIndexTreeEvictionStrategyRandom	cIndexEvictionStrategy;
	CIndexTreeEvictionStrategyRandom	cNamedEvictionStrategy;
	CFileUtil							cFileUtil;
	CTestNamedIndexedDataObject			cObject1;
	CTestNamedIndexedDataObject			cResult;

	cFileUtil.RemoveDir("Output" _FS_ "Database4");

	cController.Init("Output" _FS_ "Database4" _FS_ "R", "Output" _FS_ "Database4" _FS_ "W");
	cIndexEvictionStrategy.Init();
	cNamedEvictionStrategy.Init();
	cIndexConfig.Init("IndexData", 8 KB, 8 KB, eWriteThrough, &cIndexEvictionStrategy);
	cNamedConfig.Init("Names", 16 KB, &cNamedEvictionStrategy, eWriteThrough);
	cConfig.Init(&cIndexConfig, &cNamedConfig);

	cController.Begin();
	cDatabase.Init(&cController, &cConfig);
	cController.End();
	cConfig.Kill();

	cController.Begin();
	cObject1.Init("Those an equal point no years do.", 456754674567, 192345324532);
	cDatabase.Add(0xf97f3227894f783eLL, "Depend warmth fat but her but played", &cObject1, cObject1.Size());
	if (eWriteThrough == IWT_No) cDatabase.Flush();
	cController.End();

	cController.Begin();
	AssertTrue(cDatabase.Set(0xf97f3227894f783eLL, &cObject1));
	if (eWriteThrough == IWT_No) cDatabase.Flush();
	cController.End();

	cController.Begin();
	AssertTrue(cDatabase.Get("Depend warmth fat but her but played", &cResult));
	AssertString("Those an equal point no years do.", cResult.mszString);
	AssertLongLongInt(456754674567, cResult.miNumberX);
	AssertLongLongInt(192345324532, cResult.miNumberY);
	AssertTrue(cDatabase.Get(0xf97f3227894f783eLL, &cResult));
	AssertString("Those an equal point no years do.", cResult.mszString);
	AssertLongLongInt(456754674567, cResult.miNumberX);
	AssertLongLongInt(192345324532, cResult.miNumberY);
	cController.End();

	cDatabase.Kill();
	cController.Kill();
	cNamedEvictionStrategy.Kill();
	cIndexEvictionStrategy.Kill();

	cFileUtil.RemoveDir("Output" _FS_ "Database4");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestNamedIndexedDataSet(EIndexWriteThrough eWriteThrough)
{
	CNamedIndexedData					cDatabase;
	CValueIndexedDataConfig				cIndexConfig;
	CValueNamedIndexesConfig			cNamedConfig;
	CNamedIndexedDataConfig				cConfig;
	CDurableFileController				cController;
	CIndexTreeEvictionStrategyRandom	cIndexEvictionStrategy;
	CIndexTreeEvictionStrategyRandom	cNamedEvictionStrategy;
	CFileUtil							cFileUtil;
	CTestNamedIndexedDataObject			cObject1;
	CTestNamedIndexedDataObject			cObject2;
	CTestNamedIndexedDataObject			cObject3;
	CTestNamedIndexedDataObject			cResult;
	CChars								sz;

	cFileUtil.RemoveDir("Output" _FS_ "Database4a");

	cController.Init("Output" _FS_ "Database4a" _FS_ "R", "Output" _FS_ "Database4a" _FS_ "W");
	cIndexEvictionStrategy.Init();
	cNamedEvictionStrategy.Init();
	cIndexConfig.Init("IndexData", 8 KB, 8 KB, eWriteThrough, &cIndexEvictionStrategy);
	cNamedConfig.Init("Names", 16 KB, &cNamedEvictionStrategy, eWriteThrough);
	cConfig.Init(&cIndexConfig, &cNamedConfig);

	cController.Begin();
	cDatabase.Init(&cController, &cConfig);
	cController.End();
	cConfig.Kill();

	cController.Begin();
	cObject1.Init("Those an equal point no years do.", 456754674567, 192345324532);
	cDatabase.Add(0xf97f3227894f783eLL, "Depend warmth fat but her but played", &cObject1, cObject1.Size());
	cObject2.Init("Shy and subjects wondered trifling.", 7682493597, 328476355);
	cDatabase.Add(0xd678f6989c68234aLL, "Prudent cordial comfort do no on colonel as assured chicken", &cObject2, cObject2.Size());
	cObject3.Init("Terminated uncommonly at at estimating.", 87632234423, 3948765293847);
	cDatabase.Add(0xf9786d986987bcd1LL, "Ten behaviour met moonlight extremity acuteness direction", &cObject3, cObject2.Size());
	if (eWriteThrough == IWT_No) cDatabase.Flush();
	cController.End();

	cController.Begin();
	AssertTrue(cDatabase.Get(0xf97f3227894f783eLL, &cResult));
	AssertTrue(cDatabase.Get(0xd678f6989c68234aLL, &cResult));
	AssertTrue(cDatabase.Get(0xf9786d986987bcd1LL, &cResult));
	AssertFalse(cDatabase.Get(0xf97f3227894f783fLL, &cResult));
	AssertFalse(cDatabase.Get(0xe678f6989c68234aLL, &cResult));
	AssertFalse(cDatabase.Get(0xf9786d996987bcd1LL, &cResult));
	AssertString("Terminated uncommonly at at estimating.", cResult.mszString);
	AssertLongLongInt(87632234423, cResult.miNumberX);
	AssertLongLongInt(3948765293847, cResult.miNumberY);

	cObject1.Init("Certainty listening no no behaviour.", 192345324532, 456754674567);
	AssertTrue(cDatabase.Set("Ten behaviour met moonlight extremity acuteness direction", &cObject1));
	cObject2.Init("Because add why not esteems amiable him.", 867575634, 75684567698873423);
	sz.Init("Prudent cordial comfort do no on colonel as assured chicken");
	AssertTrue(cDatabase.Set(&sz, &cObject2));
	cObject3.Init("Answer living law things either sir bed length.", 4657587587534, 327649823);
	AssertTrue(cDatabase.Set(0xf97f3227894f783eLL, &cObject3));
	if (eWriteThrough == IWT_No) cDatabase.Flush();
	cController.End();

	cController.Begin();
	AssertTrue(cDatabase.Get(0xf97f3227894f783eLL, &cResult));
	AssertString("Answer living law things either sir bed length.", cResult.mszString);
	AssertLongLongInt(4657587587534, cResult.miNumberX);
	AssertLongLongInt(327649823, cResult.miNumberY);
	AssertTrue(cDatabase.Get(&sz, &cResult));
	AssertString("Because add why not esteems amiable him.", cResult.mszString);
	AssertLongLongInt(867575634, cResult.miNumberX);
	AssertLongLongInt(75684567698873423, cResult.miNumberY);
	AssertTrue(cDatabase.Get("Prudent cordial comfort do no on colonel as assured chicken", &cResult));
	AssertString("Because add why not esteems amiable him.", cResult.mszString);
	AssertLongLongInt(867575634, cResult.miNumberX);
	AssertLongLongInt(75684567698873423, cResult.miNumberY);
	sz.Kill();
	cController.End();

	cDatabase.Kill();
	cController.Kill();
	cNamedEvictionStrategy.Kill();
	cIndexEvictionStrategy.Kill();

	cFileUtil.RemoveDir("Output" _FS_ "Database4a");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestNamedIndexedDataSetBad(EIndexWriteThrough eWriteThrough)
{
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestNamedIndexedDataPut(EIndexWriteThrough eWriteThrough)
{
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestNamedIndexedDataRemove(EIndexWriteThrough eWriteThrough)
{
	CNamedIndexedData					cDatabase;
	CValueIndexedDataConfig				cIndexConfig;
	CValueNamedIndexesConfig			cNamedConfig;
	CNamedIndexedDataConfig				cConfig;
	CDurableFileController				cController;
	CIndexTreeEvictionStrategyRandom	cIndexEvictionStrategy;
	CIndexTreeEvictionStrategyRandom	cNamedEvictionStrategy;
	CFileUtil							cFileUtil;
	CTestNamedIndexedDataObject			cObject1;
	CTestNamedIndexedDataObject			cObject2;
	CTestNamedIndexedDataObject			cObject3;
	BOOL								bResult;

	cFileUtil.RemoveDir("Output" _FS_ "Database7");

	cIndexEvictionStrategy.Init();
	cNamedEvictionStrategy.Init();
	cController.Init("Output" _FS_ "Database7" _FS_ "R", "Output" _FS_ "Database7" _FS_ "W");
	cIndexConfig.Init("IndexData", 8 KB, 8 KB, eWriteThrough, &cIndexEvictionStrategy);
	cNamedConfig.Init("Names", 16 KB, &cNamedEvictionStrategy, eWriteThrough);
	cConfig.Init(&cIndexConfig, &cNamedConfig);

	cController.Begin();
	cDatabase.Init(&cController, &cConfig);
	cConfig.Kill();
	cObject1.Init("Rutherford", 1871, 1937);
	cDatabase.Add(0x0102LL, "Ernest", &cObject1, cObject1.Size());
	cObject2.Init("Bohr", 1885, 1962);
	cDatabase.Add(0x0203LL, "Niels", &cObject2, cObject2.Size());
	cObject2.Init("Planck", 1858, 1947);
	cDatabase.Add(0x0304LL, &cObject3, cObject3.Size());
	AssertLongLongInt(3, cDatabase.NumIndices());
	AssertLongLongInt(2, cDatabase.NumNames());
	AssertTrue(cDatabase.Contains(0x0102LL));
	AssertTrue(cDatabase.Contains("Ernest"));
	AssertTrue(cDatabase.Contains(0x0203LL));
	AssertTrue(cDatabase.Contains("Niels"));
	AssertTrue(cDatabase.Contains(0x0304LL));
	if (eWriteThrough == IWT_No) cDatabase.Flush();
	cController.End();
	cDatabase.Kill();
	cController.Kill();
	cNamedEvictionStrategy.Kill();
	cIndexEvictionStrategy.Kill();


	cIndexEvictionStrategy.Init();
	cNamedEvictionStrategy.Init();
	cController.Init("Output" _FS_ "Database7" _FS_ "R", "Output" _FS_ "Database7" _FS_ "W");
	cIndexConfig.Init("IndexData", 8 KB, 8 KB, eWriteThrough, &cIndexEvictionStrategy);
	cNamedConfig.Init("Names", 16 KB, &cNamedEvictionStrategy, eWriteThrough);
	cConfig.Init(&cIndexConfig, &cNamedConfig);

	cController.Begin();
	cDatabase.Init(&cController, &cConfig);
	cController.End();
	cConfig.Kill();

	cController.Begin();
	AssertTrue(cDatabase.Contains(0x0102LL));
	AssertTrue(cDatabase.Contains("Ernest"));
	AssertTrue(cDatabase.Contains(0x0203LL));
	AssertTrue(cDatabase.Contains("Niels"));
	AssertTrue(cDatabase.Contains(0x0304LL));
	cController.End();
	cDatabase.Kill();
	cController.Kill();
	cNamedEvictionStrategy.Kill();
	cIndexEvictionStrategy.Kill();


	cIndexEvictionStrategy.Init();
	cNamedEvictionStrategy.Init();
	cController.Init("Output" _FS_ "Database7" _FS_ "R", "Output" _FS_ "Database7" _FS_ "W");
	cIndexConfig.Init("IndexData", 8 KB, 8 KB, eWriteThrough, &cIndexEvictionStrategy);
	cNamedConfig.Init("Names", 16 KB, &cNamedEvictionStrategy, eWriteThrough);
	cConfig.Init(&cIndexConfig, &cNamedConfig);

	cController.Begin();
	cDatabase.Init(&cController, &cConfig);
	cController.End();
	cConfig.Kill();

	cController.Begin();
	bResult = cDatabase.Remove(0x0102LL);
	AssertTrue(bResult);
	AssertFalse(cDatabase.Contains(0x0102LL));
	AssertFalse(cDatabase.Contains("Ernest"));
	if (eWriteThrough == IWT_No) cDatabase.Flush();
	cController.End();
	cDatabase.Kill();
	cController.Kill();
	cNamedEvictionStrategy.Kill();
	cIndexEvictionStrategy.Kill();


	cIndexEvictionStrategy.Init();
	cNamedEvictionStrategy.Init();
	cController.Init("Output" _FS_ "Database7" _FS_ "R", "Output" _FS_ "Database7" _FS_ "W");
	cIndexConfig.Init("IndexData", 8 KB, 8 KB, eWriteThrough, &cIndexEvictionStrategy);
	cNamedConfig.Init("Names", 16 KB, &cNamedEvictionStrategy, eWriteThrough);
	cConfig.Init(&cIndexConfig, &cNamedConfig);

	cController.Begin();
	cDatabase.Init(&cController, &cConfig);
	cController.End();
	cConfig.Kill();

	cController.Begin();
	AssertFalse(cDatabase.Contains(0x0102LL));
	AssertFalse(cDatabase.Contains("Ernest"));
	bResult = cDatabase.Remove("Niels");
	AssertTrue(bResult);
	AssertFalse(cDatabase.Contains(0x0203LL));
	AssertFalse(cDatabase.Contains("Niels"));
	bResult = cDatabase.Contains(0x0304LL);
	bResult = cDatabase.Remove(0x0304LL);
	AssertTrue(bResult);
	AssertFalse(cDatabase.Contains(0x0304LL));
	if (eWriteThrough == IWT_No) cDatabase.Flush();
	cController.End();

	cDatabase.Kill();
	cController.Kill();
	cNamedEvictionStrategy.Kill();
	cIndexEvictionStrategy.Kill();


	cFileUtil.RemoveDir("Output" _FS_ "Database7");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestNamedIndexedData(void)
{
	FastFunctionsInit();
	TypeConverterInit();
	MemoryInit();
	DataMemoryInit();
	BeginTests();

	TestNamedIndexedDataInit(IWT_Yes);
	TestNamedIndexedDataInit(IWT_No);
	TestNamedIndexedDataAddString(IWT_Yes);
	TestNamedIndexedDataAddString(IWT_No);
	TestNamedIndexedDataAddChars(IWT_Yes);
	TestNamedIndexedDataAddChars(IWT_No);
	TestNamedIndexedDataAddIndex(IWT_Yes);
	TestNamedIndexedDataAddIndex(IWT_No);
	TestNamedIndexedDataAddBad(IWT_Yes);
	TestNamedIndexedDataAddBad(IWT_No);
	TestNamedIndexedDataGetName(IWT_Yes);
	TestNamedIndexedDataGetName(IWT_No);
	TestNamedIndexedDataSetIndex(IWT_Yes);
	TestNamedIndexedDataSetIndex(IWT_No);
	TestNamedIndexedDataSet(IWT_Yes);
	TestNamedIndexedDataSet(IWT_No);
	TestNamedIndexedDataSetBad(IWT_Yes);
	TestNamedIndexedDataSetBad(IWT_No);
	TestNamedIndexedDataPut(IWT_Yes);
	TestNamedIndexedDataPut(IWT_No);
	TestNamedIndexedDataRemove(IWT_Yes);
	TestNamedIndexedDataRemove(IWT_No);

	TestStatistics();
	DataMemoryKill();
	MemoryKill();
	FastFunctionsKill();
	TypeConverterKill();
}

