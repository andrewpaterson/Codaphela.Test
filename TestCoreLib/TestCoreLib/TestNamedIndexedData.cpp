#include "BaseLib/TypeConverter.h"
#include "BaseLib/Define.h"
#include "BaseLib/StdRandom.h"
#include "BaseLib/Logger.h"
#include "BaseLib/LifeCycle.h"
#include "BaseLib/GlobalMemory.h"
#include "CoreLib/DurableFileController.h"
#include "CoreLib/NamedIndexedData.h"
#include "CoreLib/ValueIndexedDataConfig.h"
#include "CoreLib/ValueNamedIndexesConfig.h"
#include "CoreLib/IndexTreeEvictionCounter.h"
#include "CoreLib/IndexedDataEvictionCounter.h"
#include "StandardLib/BaseObject.h"
#include "TestLib/Assert.h"
#include "TestLib/Words.h"
#include "NamedIndexedDataObject.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestNamedIndexedDataInit(EIndexWriteThrough eWriteThrough)
{
	CNamedIndexedData					cDatabase;
	CLifeInit<CIndexedDataConfig>		cIndexConfig;
	CLifeInit<CNamedIndexesConfig>		cNamedConfig;
	CDurableFileController				cController;
	CIndexTreeEvictionStrategyRandom	cIndexEvictionStrategy;
	CIndexTreeEvictionStrategyRandom	cNamedEvictionStrategy;
	CFileUtil							cFileUtil;
	
	cFileUtil.RemoveDir("Output" _FS_ "Database1");

	cController.Init("Output" _FS_ "Database1" _FS_ "R", "Output" _FS_ "Database1" _FS_ "W");

	cNamedEvictionStrategy.Init();
	cIndexEvictionStrategy.Init();

	cIndexConfig = CValueIndexedDataConfig::Create("IndexData", 8 KB, 8 KB, eWriteThrough, LifeLocal<CIndexTreeEvictionStrategy>(&cIndexEvictionStrategy));
	cNamedConfig = CValueNamedIndexesConfig::Create("Names", 16 KB, LifeLocal<CIndexTreeEvictionStrategy>(&cNamedEvictionStrategy), eWriteThrough);
	
	cController.Begin();
	cDatabase.Init(&cController, cIndexConfig, cNamedConfig);
	cController.End();
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
	CLifeInit<CIndexedDataConfig>		cIndexConfig;
	CLifeInit<CNamedIndexesConfig>		cNamedConfig;
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
	cIndexConfig = CValueIndexedDataConfig::Create("IndexData", 8 KB, 8 KB, eWriteThrough, LifeLocal<CIndexTreeEvictionStrategy>(&cIndexEvictionStrategy));
	cNamedConfig = CValueNamedIndexesConfig::Create("Names", 16 KB, LifeLocal<CIndexTreeEvictionStrategy>(&cNamedEvictionStrategy), eWriteThrough);

	cController.Begin();
	cDatabase.Init(&cController, cIndexConfig, cNamedConfig);
	cController.End();

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
	cIndexConfig = CValueIndexedDataConfig::Create("IndexData", 8 KB, 8 KB, eWriteThrough, LifeLocal<CIndexTreeEvictionStrategy>(&cIndexEvictionStrategy));
	cNamedConfig = CValueNamedIndexesConfig::Create("Names", 16 KB, LifeLocal<CIndexTreeEvictionStrategy>(&cNamedEvictionStrategy), eWriteThrough);

	cController.Begin();
	cDatabase.Init(&cController, cIndexConfig, cNamedConfig);
	cController.End();

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
	cIndexConfig = CValueIndexedDataConfig::Create("IndexData", 8 KB, 8 KB, eWriteThrough, LifeLocal<CIndexTreeEvictionStrategy>(&cIndexEvictionStrategy));
	cNamedConfig = CValueNamedIndexesConfig::Create("Names", 16 KB, LifeLocal<CIndexTreeEvictionStrategy>(&cNamedEvictionStrategy), eWriteThrough);

	cController.Begin();
	cDatabase.Init(&cController, cIndexConfig, cNamedConfig);
	cController.End();

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
	cIndexConfig = CValueIndexedDataConfig::Create("IndexData", 8 KB, 8 KB, eWriteThrough, LifeLocal<CIndexTreeEvictionStrategy>(&cIndexEvictionStrategy));
	cNamedConfig = CValueNamedIndexesConfig::Create("Names", 16 KB, LifeLocal<CIndexTreeEvictionStrategy>(&cNamedEvictionStrategy), eWriteThrough);

	cController.Begin();
	cDatabase.Init(&cController, cIndexConfig, cNamedConfig);
	cController.End();

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
	CLifeInit<CIndexedDataConfig>		cIndexConfig;
	CLifeInit<CNamedIndexesConfig>		cNamedConfig;
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
	cIndexConfig = CValueIndexedDataConfig::Create("IndexData", 8 KB, 8 KB, eWriteThrough, LifeLocal<CIndexTreeEvictionStrategy>(&cIndexEvictionStrategy));
	cNamedConfig = CValueNamedIndexesConfig::Create("Names", 16 KB, LifeLocal<CIndexTreeEvictionStrategy>(&cNamedEvictionStrategy), eWriteThrough);

	cController.Begin();
	cDatabase.Init(&cController, cIndexConfig, cNamedConfig);
	cController.End();

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
	cIndexConfig = CValueIndexedDataConfig::Create("IndexData", 8 KB, 8 KB, eWriteThrough, LifeLocal<CIndexTreeEvictionStrategy>(&cIndexEvictionStrategy));
	cNamedConfig = CValueNamedIndexesConfig::Create("Names", 16 KB, LifeLocal<CIndexTreeEvictionStrategy>(&cNamedEvictionStrategy), eWriteThrough);

	cController.Begin();
	cDatabase.Init(&cController, cIndexConfig, cNamedConfig);
	cController.End();

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
	CLifeInit<CIndexedDataConfig>		cIndexConfig;
	CLifeInit<CNamedIndexesConfig>		cNamedConfig;
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
	cIndexConfig = CValueIndexedDataConfig::Create("IndexData", 8 KB, 8 KB, eWriteThrough, LifeLocal<CIndexTreeEvictionStrategy>(&cIndexEvictionStrategy));
	cNamedConfig = CValueNamedIndexesConfig::Create("Names", 16 KB, LifeLocal<CIndexTreeEvictionStrategy>(&cNamedEvictionStrategy), eWriteThrough);

	cController.Begin();
	cDatabase.Init(&cController, cIndexConfig, cNamedConfig);
	cController.End();

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
	CLifeInit<CIndexedDataConfig>		cIndexConfig;
	CLifeInit<CNamedIndexesConfig>		cNamedConfig;
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
	cIndexConfig = CValueIndexedDataConfig::Create("IndexData", 8 KB, 8 KB, eWriteThrough, LifeLocal<CIndexTreeEvictionStrategy>(&cIndexEvictionStrategy));
	cNamedConfig = CValueNamedIndexesConfig::Create("Names", 16 KB, LifeLocal<CIndexTreeEvictionStrategy>(&cNamedEvictionStrategy), eWriteThrough);

	cController.Begin();
	cDatabase.Init(&cController, cIndexConfig, cNamedConfig);
	cController.End();

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
	cIndexConfig = CValueIndexedDataConfig::Create("IndexData", 8 KB, 8 KB, eWriteThrough, LifeLocal<CIndexTreeEvictionStrategy>(&cIndexEvictionStrategy));
	cNamedConfig = CValueNamedIndexesConfig::Create("Names", 16 KB, LifeLocal<CIndexTreeEvictionStrategy>(&cNamedEvictionStrategy), eWriteThrough);

	cController.Begin();
	cDatabase.Init(&cController, cIndexConfig, cNamedConfig);
	cController.End();

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
	CLifeInit<CIndexedDataConfig>		cIndexConfig;
	CLifeInit<CNamedIndexesConfig>		cNamedConfig;
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
	cIndexConfig = CValueIndexedDataConfig::Create("IndexData", 8 KB, 8 KB, eWriteThrough, LifeLocal<CIndexTreeEvictionStrategy>(&cIndexEvictionStrategy));
	cNamedConfig = CValueNamedIndexesConfig::Create("Names", 16 KB, LifeLocal<CIndexTreeEvictionStrategy>(&cNamedEvictionStrategy), eWriteThrough);

	cController.Begin();
	cDatabase.Init(&cController, cIndexConfig, cNamedConfig);
	cController.End();

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
	CLifeInit<CIndexedDataConfig>		cIndexConfig;
	CLifeInit<CNamedIndexesConfig>		cNamedConfig;
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
	cIndexConfig = CValueIndexedDataConfig::Create("IndexData", 8 KB, 8 KB, eWriteThrough, LifeLocal<CIndexTreeEvictionStrategy>(&cIndexEvictionStrategy));
	cNamedConfig = CValueNamedIndexesConfig::Create("Names", 16 KB, LifeLocal<CIndexTreeEvictionStrategy>(&cNamedEvictionStrategy), eWriteThrough);

	cController.Begin();
	cDatabase.Init(&cController, cIndexConfig, cNamedConfig);
	cController.End();

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
	CLifeInit<CIndexedDataConfig>		cIndexConfig;
	CLifeInit<CNamedIndexesConfig>		cNamedConfig;
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
	cIndexConfig = CValueIndexedDataConfig::Create("IndexData", 8 KB, 8 KB, eWriteThrough, LifeLocal<CIndexTreeEvictionStrategy>(&cIndexEvictionStrategy));
	cNamedConfig = CValueNamedIndexesConfig::Create("Names", 16 KB, LifeLocal<CIndexTreeEvictionStrategy>(&cNamedEvictionStrategy), eWriteThrough);

	cController.Begin();
	cDatabase.Init(&cController, cIndexConfig, cNamedConfig);
	cController.End();

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
	CLifeInit<CIndexedDataConfig>		cIndexConfig;
	CLifeInit<CNamedIndexesConfig>		cNamedConfig;
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
	cIndexConfig = CValueIndexedDataConfig::Create("IndexData", 8 KB, 8 KB, eWriteThrough, LifeLocal<CIndexTreeEvictionStrategy>(&cIndexEvictionStrategy));
	cNamedConfig = CValueNamedIndexesConfig::Create("Names", 16 KB, LifeLocal<CIndexTreeEvictionStrategy>(&cNamedEvictionStrategy), eWriteThrough);

	cController.Begin();
	cDatabase.Init(&cController, cIndexConfig, cNamedConfig);
	cObject1.Init("Rutherford", 1871, 1937);
	cDatabase.Add(0x0102LL, "Ernest", &cObject1, cObject1.Size());
	cObject2.Init("Bohr", 1885, 1962);
	cDatabase.Add(0x0203LL, "Niels", &cObject2, cObject2.Size());
	cObject3.Init("Planck", 1858, 1947);
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
	cIndexConfig = CValueIndexedDataConfig::Create("IndexData", 8 KB, 8 KB, eWriteThrough, LifeLocal<CIndexTreeEvictionStrategy>(&cIndexEvictionStrategy));
	cNamedConfig = CValueNamedIndexesConfig::Create("Names", 16 KB, LifeLocal<CIndexTreeEvictionStrategy>(&cNamedEvictionStrategy), eWriteThrough);

	cController.Begin();
	cDatabase.Init(&cController, cIndexConfig, cNamedConfig);
	cController.End();

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
	cIndexConfig = CValueIndexedDataConfig::Create("IndexData", 8 KB, 8 KB, eWriteThrough, LifeLocal<CIndexTreeEvictionStrategy>(&cIndexEvictionStrategy));
	cNamedConfig = CValueNamedIndexesConfig::Create("Names", 16 KB, LifeLocal<CIndexTreeEvictionStrategy>(&cNamedEvictionStrategy), eWriteThrough);

	cController.Begin();
	cDatabase.Init(&cController, cIndexConfig, cNamedConfig);
	cController.End();

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
	cIndexConfig = CValueIndexedDataConfig::Create("IndexData", 8 KB, 8 KB, eWriteThrough, LifeLocal<CIndexTreeEvictionStrategy>(&cIndexEvictionStrategy));
	cNamedConfig = CValueNamedIndexesConfig::Create("Names", 16 KB, LifeLocal<CIndexTreeEvictionStrategy>(&cNamedEvictionStrategy), eWriteThrough);

	cController.Begin();
	cDatabase.Init(&cController, cIndexConfig, cNamedConfig);
	cController.End();

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
void TestNamedIndexedDataIterate(EIndexWriteThrough eWriteThrough)
{
	CNamedIndexedData					cDatabase;
	CLifeInit<CIndexedDataConfig>		cIndexConfig;
	CLifeInit<CNamedIndexesConfig>		cNamedConfig;
	CDurableFileController				cController;
	CIndexTreeEvictionStrategyRandom	cIndexEvictionStrategy;
	CIndexTreeEvictionStrategyRandom	cNamedEvictionStrategy;
	CFileUtil							cFileUtil;
	CTestNamedIndexedDataObject			cObject1;
	CTestNamedIndexedDataObject			cObject2;
	CTestNamedIndexedDataObject			cObject3;
	CTestNamedIndexedDataObject			cObject4;
	CTestNamedIndexedDataObject			cObject5;
	SIndexTreeFileIterator		sIter;
	CTestNamedIndexedDataObject			cResult;
	size_t								iDataSize;
	OIndex								oi;
	char								szKey[MAX_KEY_SIZE];
	BOOL								bResult;

	cFileUtil.RemoveDir("Output" _FS_ "Database8");

	cIndexEvictionStrategy.Init();
	cNamedEvictionStrategy.Init();
	cController.Init("Output" _FS_ "Database8" _FS_ "R", "Output" _FS_ "Database8" _FS_ "W");
	cIndexConfig = CValueIndexedDataConfig::Create("IndexData", 8 KB, 8 KB, eWriteThrough, LifeLocal<CIndexTreeEvictionStrategy>(&cIndexEvictionStrategy));
	cNamedConfig = CValueNamedIndexesConfig::Create("Names", 16 KB, LifeLocal<CIndexTreeEvictionStrategy>(&cNamedEvictionStrategy), eWriteThrough);

	cController.Begin();
	cDatabase.Init(&cController, cIndexConfig, cNamedConfig);
	cObject1.Init("Rutherford", 1871, 1937);
	cDatabase.Add(0x0102LL, "Ernest", &cObject1, cObject1.Size());
	cObject2.Init("Bohr", 1885, 1962);
	cDatabase.Add(0x0203LL, "Niels", &cObject2, cObject2.Size());
	cObject3.Init("Planck", 1858, 1947);
	cDatabase.Add(0x0304LL, &cObject3, cObject3.Size());
	cObject4.Init("Einstein", 1879, 1955);
	cDatabase.Add(0x405LL, "Albert", &cObject4, cObject4.Size());
	cObject5.Init("Newton", 1643, 1727);
	cDatabase.Add(0x506LL, "Isaac", &cObject5, cObject5.Size());
	AssertLongLongInt(5, cDatabase.NumIndices());
	AssertLongLongInt(4, cDatabase.NumNames());

	oi = cDatabase.StartIndexIteration(&sIter, &cResult, &iDataSize, sizeof(CTestNamedIndexedDataObject));
	AssertLongLongInt(0x0102LL, oi);
	AssertInt(sizeof(CTestNamedIndexedDataObject), iDataSize);
	AssertMemory(&cObject1, &cResult, iDataSize);

	oi = cDatabase.IndexIterate(&sIter, &cResult, &iDataSize, sizeof(CTestNamedIndexedDataObject));
	AssertLongLongInt(0x0203LL, oi);
	AssertInt(sizeof(CTestNamedIndexedDataObject), iDataSize);
	AssertMemory(&cObject2, &cResult, iDataSize);

	oi = cDatabase.IndexIterate(&sIter, &cResult, &iDataSize, sizeof(CTestNamedIndexedDataObject));
	AssertLongLongInt(0x0304LL, oi);
	AssertInt(sizeof(CTestNamedIndexedDataObject), iDataSize);
	AssertMemory(&cObject3, &cResult, iDataSize);

	oi = cDatabase.IndexIterate(&sIter, &cResult, &iDataSize, sizeof(CTestNamedIndexedDataObject));
	AssertLongLongInt(0x0405LL, oi);
	AssertInt(sizeof(CTestNamedIndexedDataObject), iDataSize);
	AssertMemory(&cObject4, &cResult, iDataSize);

	oi = cDatabase.IndexIterate(&sIter, &cResult, &iDataSize, sizeof(CTestNamedIndexedDataObject));
	AssertLongLongInt(0x0506LL, oi);
	AssertInt(sizeof(CTestNamedIndexedDataObject), iDataSize);
	AssertMemory(&cObject5, &cResult, iDataSize);

	oi = cDatabase.IndexIterate(&sIter, &cResult, &iDataSize, sizeof(CTestNamedIndexedDataObject));
	AssertLongLongInt(INVALID_O_INDEX, oi);


	bResult = cDatabase.StartNameIteration(&sIter, szKey, &oi);
	AssertTrue(bResult);
	AssertLongLongInt(0x0405LL, oi);
	AssertString("Albert", szKey);

	bResult = cDatabase.NameIterate(&sIter, szKey, &oi);
	AssertTrue(bResult);
	AssertLongLongInt(0x0102LL, oi);
	AssertString("Ernest", szKey);

	bResult = cDatabase.NameIterate(&sIter, szKey, &oi);
	AssertTrue(bResult);
	AssertLongLongInt(0x0506LL, oi);
	AssertString("Isaac", szKey);

	bResult = cDatabase.NameIterate(&sIter, szKey, &oi);
	AssertTrue(bResult);
	AssertLongLongInt(0x0203LL, oi);
	AssertString("Niels", szKey);

	bResult = cDatabase.NameIterate(&sIter, szKey, &oi);
	AssertFalse(bResult);


	oi = cDatabase.StartIndexIteration(&sIter, &cResult, &iDataSize, 0);
	AssertLongLongInt(0x0102LL, oi);

	oi = cDatabase.IndexIterate(&sIter, &cResult, &iDataSize, 0);
	AssertLongLongInt(0x0203LL, oi);

	oi = cDatabase.IndexIterate(&sIter, &cResult, &iDataSize, 0);
	AssertLongLongInt(0x0304LL, oi);

	oi = cDatabase.IndexIterate(&sIter, &cResult, &iDataSize, 0);
	AssertLongLongInt(0x0405LL, oi);

	oi = cDatabase.IndexIterate(&sIter, &cResult, &iDataSize, 0);
	AssertLongLongInt(0x0506LL, oi);

	oi = cDatabase.IndexIterate(&sIter, &cResult, &iDataSize, 0);
	AssertLongLongInt(INVALID_O_INDEX, oi);


	if (eWriteThrough == IWT_No) cDatabase.Flush();
	cController.End();
	cDatabase.Kill();
	cController.Kill();
	cNamedEvictionStrategy.Kill();
	cIndexEvictionStrategy.Kill();

	cFileUtil.RemoveDir("Output" _FS_ "Database8");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestNamedIndexedDataIterateDuringTreeChange(EIndexWriteThrough eWriteThrough)
{
	CNamedIndexedData					cDatabase;
	CLifeInit<CIndexedDataConfig>		cIndexConfig;
	CLifeInit<CNamedIndexesConfig>		cNamedConfig;
	CDurableFileController				cController;
	CIndexTreeEvictionStrategyRandom	cIndexEvictionStrategy;
	CIndexTreeEvictionStrategyRandom	cNamedEvictionStrategy;
	CFileUtil							cFileUtil;
	CTestNamedIndexedDataObject			cObject;
	SIndexTreeFileIterator				sIter;
	CTestNamedIndexedDataObject			cResult;
	size_t								iDataSize;
	OIndex								oi;
	char								szKey[MAX_KEY_SIZE];
	BOOL								bResult;
	CArrayChars							aszWords;
	CRandom								cRandom;
	CChars								sz;
	int									iNumWords;
	int									iIndex;
	int									iWord;
	CArrayChars							aszNames;
	int									iIter;
	int									iExpectedOi;
	CIndexTreeEvictionCounter			cIndexEvictionCounter;
	CIndexedDataEvictionCounter			cDataEvictionCounter;
	CIndexTreeEvictionCounter			cNameEvictionCounter;
	BOOL								bFailed;

	aszWords.Init();
	GetCommonWords(&aszWords);
	iNumWords = aszWords.NumElements();
	cRandom.Init(8976);

	cFileUtil.RemoveDir("Output" _FS_ "Database9");

	aszNames.Init();
	cIndexEvictionCounter.Init();
	cDataEvictionCounter.Init();
	cNameEvictionCounter.Init();

	cIndexEvictionStrategy.Init();
	cNamedEvictionStrategy.Init();
	cController.Init("Output" _FS_ "Database9" _FS_ "R", "Output" _FS_ "Database9" _FS_ "W");
	cIndexConfig = CValueIndexedDataConfig::Create("IndexData", 8 KB, 8 KB, eWriteThrough, LifeLocal<CIndexTreeEvictionStrategy>(&cIndexEvictionStrategy), &cIndexEvictionCounter, &cDataEvictionCounter);
	cNamedConfig = CValueNamedIndexesConfig::Create("Names", 16 KB, LifeLocal<CIndexTreeEvictionStrategy>(&cNamedEvictionStrategy), eWriteThrough, &cNameEvictionCounter);
	
	cController.Begin();
	cDatabase.Init(&cController, cIndexConfig, cNamedConfig);

	AssertLongLongInt(3100, cDatabase.GetIndiciesSystemMemorySize());
	AssertLongLongInt(0, cDatabase.GetDataSystemMemorySize());
	AssertLongLongInt(3100, cDatabase.GetNamesSystemMemorySize());

	for (oi = 1; oi < 1024; oi++)
	{
		sz.Init();
		for (iWord = 0; iWord < 3; iWord++)
		{
			if (iWord != 0)
			{
				sz.Append(" ");
			}
			iIndex = cRandom.Next(0, iNumWords - 1);
			sz.Append(aszWords.Get(iIndex));
		}
		cObject.Init(sz.Text(), oi-1, oi * 7);
		cDatabase.Add(oi * 7, sz.Text(), &cObject, cObject.Size());
		aszNames.Add(sz.Text());
		sz.Kill();
	}

	AssertLongLongInt(8156, cDatabase.GetIndiciesSystemMemorySize());
	AssertLongLongInt(5756, cDatabase.GetDataSystemMemorySize());
	AssertLongLongInt(16308, cDatabase.GetNamesSystemMemorySize());
	AssertLongLongInt(21, cDatabase.NumIndicesCached());
	AssertLongLongInt(18, cDatabase.NumDataCached());
	AssertLongLongInt(10, cDatabase.NumNamesCached());
	AssertLongLongInt(1002, cIndexEvictionCounter.EvictionCount());
	AssertLongLongInt(1005, cDataEvictionCounter.EvictionCount());
	AssertLongLongInt(1013, cNameEvictionCounter.EvictionCount());
	AssertLongLongInt(1023, cDatabase.NumIndices());
	AssertLongLongInt(1023, cDatabase.NumNames());
	cIndexEvictionCounter.Reset();
	cDataEvictionCounter.Reset();
	cNameEvictionCounter.Reset();

	bFailed = FALSE;
	iIter = 0;
	oi = cDatabase.StartIndexIteration(&sIter, &cResult, &iDataSize, sizeof(CTestNamedIndexedDataObject));
	while (oi != INVALID_O_INDEX)
	{
		iExpectedOi = (iIter + 1) * 7;
		if (iExpectedOi != oi) bFailed = TRUE;
		if (sizeof(CTestNamedIndexedDataObject) != iDataSize) bFailed = TRUE;
		if (iIter != cResult.miNumberX) bFailed = TRUE;
		if (iExpectedOi != cResult.miNumberY)  bFailed = TRUE;
		if (!aszNames.Get(iIter)->Equals(cResult.mszString)) bFailed = TRUE;
		AssertFalse(bFailed);

		iIter++;
		oi = cDatabase.IndexIterate(&sIter, &cResult, &iDataSize, sizeof(CTestNamedIndexedDataObject));
	}

	AssertLongLongInt(8156, cDatabase.GetIndiciesSystemMemorySize());
	AssertLongLongInt(5115, cDatabase.GetDataSystemMemorySize());
	AssertLongLongInt(0, cDatabase.GetNamesSystemMemorySize());
	AssertLongLongInt(18, cDatabase.NumIndicesCached());
	AssertLongLongInt(16, cDatabase.NumDataCached());
	AssertLongLongInt(1023, cDatabase.NumNamesCached());
	AssertLongLongInt(2027, cIndexEvictionCounter.EvictionCount());
	AssertLongLongInt(1025, cDataEvictionCounter.EvictionCount());
	AssertLongLongInt(0, cNameEvictionCounter.EvictionCount());
	AssertLongLongInt(1023, cDatabase.NumIndices());
	AssertLongLongInt(1023, cDatabase.NumNames());
	cIndexEvictionCounter.Reset();
	cDataEvictionCounter.Reset();
	cNameEvictionCounter.Reset();
	
	aszNames.QuickSort();

	iIter = 0;
	bResult = cDatabase.StartNameIteration(&sIter, szKey, &oi);
	while (bResult)
	{
		AssertString(aszNames.Get(iIter)->Text(), szKey);

		iIter++;
		bResult = cDatabase.NameIterate(&sIter, szKey, &oi);
	}

	AssertLongLongInt(1023, cDatabase.NumIndicesCached());
	AssertLongLongInt(16, cDatabase.NumDataCached());
	AssertLongLongInt(15, cDatabase.NumNamesCached());
	AssertLongLongInt(0, cIndexEvictionCounter.EvictionCount());
	AssertLongLongInt(0, cDataEvictionCounter.EvictionCount());
	AssertLongLongInt(2030, cNameEvictionCounter.EvictionCount());
	AssertLongLongInt(1023, cDatabase.NumIndices());
	AssertLongLongInt(1023, cDatabase.NumNames());


	if (eWriteThrough == IWT_No) cDatabase.Flush();
	cController.End();
	cDatabase.Kill();
	cController.Kill();
	cNamedEvictionStrategy.Kill();
	cIndexEvictionStrategy.Kill();

	cFileUtil.RemoveDir("Output" _FS_ "Database8");

	aszWords.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestNamedIndexedDataGetDoesNotExceedCache(EIndexWriteThrough eWriteThrough)
{
	CNamedIndexedData					cDatabase;
	CLifeInit<CIndexedDataConfig>		cIndexConfig;
	CLifeInit<CNamedIndexesConfig>		cNamedConfig;
	CDurableFileController				cController;
	CIndexTreeEvictionStrategyRandom	cIndexEvictionStrategy;
	CIndexTreeEvictionStrategyRandom	cNamedEvictionStrategy;
	CFileUtil							cFileUtil;
	CTestNamedIndexedDataObject			cObject;
	CTestNamedIndexedDataObject			cResult;
	OIndex								oi;
	BOOL								bResult;
	CArrayChars							aszWords;
	CRandom								cRandom;
	CChars								sz;
	int									iNumWords;
	int									iIndex;
	int									iWord;
	CArrayChars							aszNames;
	CIndexTreeEvictionCounter			cIndexEvictionCounter;
	CIndexedDataEvictionCounter			cDataEvictionCounter;
	CIndexTreeEvictionCounter			cNameEvictionCounter;
	//BOOL								bFailed;
	int									i;
	unsigned int						uiDataSize;

	aszWords.Init();
	GetCommonWords(&aszWords);
	iNumWords = aszWords.NumElements();
	cRandom.Init(8976);

	cFileUtil.RemoveDir("Output" _FS_ "Database9");

	aszNames.Init();
	cIndexEvictionCounter.Init();
	cDataEvictionCounter.Init();
	cNameEvictionCounter.Init();

	cIndexEvictionStrategy.Init();
	cNamedEvictionStrategy.Init();
	cController.Init("Output" _FS_ "Database9" _FS_ "R", "Output" _FS_ "Database9" _FS_ "W");
	cIndexConfig = CValueIndexedDataConfig::Create("IndexData", 8 KB, 8 KB, eWriteThrough, LifeLocal<CIndexTreeEvictionStrategy>(&cIndexEvictionStrategy), &cIndexEvictionCounter, &cDataEvictionCounter);
	cNamedConfig = CValueNamedIndexesConfig::Create("Names", 16 KB, LifeLocal<CIndexTreeEvictionStrategy>(&cNamedEvictionStrategy), eWriteThrough, &cNameEvictionCounter);

	cController.Begin();
	cDatabase.Init(&cController, cIndexConfig, cNamedConfig);

	AssertLongLongInt(3100, cDatabase.GetIndiciesSystemMemorySize());
	AssertLongLongInt(0, cDatabase.GetDataSystemMemorySize());
	AssertLongLongInt(3100, cDatabase.GetNamesSystemMemorySize());

	for (oi = 1; oi < 1024; oi++)
	{
		sz.Init();
		for (iWord = 0; iWord < 3; iWord++)
		{
			if (iWord != 0)
			{
				sz.Append(" ");
			}
			iIndex = cRandom.Next(0, iNumWords - 1);
			sz.Append(aszWords.Get(iIndex));
		}
		cObject.Init(sz.Text(), oi - 1, oi * 7);
		cDatabase.Add(oi * 7, sz.Text(), &cObject, cObject.Size());
		aszNames.Add(sz.Text());
		sz.Kill();
	}

	AssertLongLongInt(8156, cDatabase.GetIndiciesSystemMemorySize());
	AssertLongLongInt(5756, cDatabase.GetDataSystemMemorySize());
	AssertLongLongInt(16308, cDatabase.GetNamesSystemMemorySize());
	AssertLongLongInt(21, cDatabase.NumIndicesCached());
	AssertLongLongInt(18, cDatabase.NumDataCached());
	AssertLongLongInt(10, cDatabase.NumNamesCached());
	AssertLongLongInt(1002, cIndexEvictionCounter.EvictionCount());
	AssertLongLongInt(1005, cDataEvictionCounter.EvictionCount());
	AssertLongLongInt(1013, cNameEvictionCounter.EvictionCount());
	AssertLongLongInt(1023, cDatabase.NumIndices());
	AssertLongLongInt(1023, cDatabase.NumNames());
	
	cIndexEvictionCounter.Reset();
	cDataEvictionCounter.Reset();
	cNameEvictionCounter.Reset();
	aszNames.Shuffle(&cRandom);
	for (i = 0; i < aszNames.NumElements(); i++)
	{
		bResult = cDatabase.Get(aszNames.Get(i), &uiDataSize, &cResult, sizeof(CTestNamedIndexedDataObject));
	}

	AssertLongLongInt(6812, cDatabase.GetIndiciesSystemMemorySize());
	AssertLongLongInt(317, cDatabase.GetDataSystemMemorySize());
	AssertLongLongInt(15832, cDatabase.GetNamesSystemMemorySize());
	AssertLongLongInt(1, cDatabase.NumIndicesCached());
	AssertLongLongInt(1, cDatabase.NumDataCached());
	AssertLongLongInt(10, cDatabase.NumNamesCached());
	AssertLongLongInt(2044, cIndexEvictionCounter.EvictionCount());
	AssertLongLongInt(1040, cDataEvictionCounter.EvictionCount());
	AssertLongLongInt(2034, cNameEvictionCounter.EvictionCount());
	AssertLongLongInt(1023, cDatabase.NumIndices());
	AssertLongLongInt(1023, cDatabase.NumNames());

	cIndexEvictionCounter.Reset();
	cDataEvictionCounter.Reset();
	cNameEvictionCounter.Reset();
	aszNames.Shuffle(&cRandom);
	for (i = 0; i < aszNames.NumElements(); i++)
	{
		bResult = cDatabase.Get(aszNames.Get(i), &uiDataSize, &cResult, sizeof(CTestNamedIndexedDataObject));
	}

	AssertLongLongInt(6812, cDatabase.GetIndiciesSystemMemorySize());
	AssertLongLongInt(322, cDatabase.GetDataSystemMemorySize());
	AssertLongLongInt(14868, cDatabase.GetNamesSystemMemorySize());
	AssertLongLongInt(1, cDatabase.NumIndicesCached());
	AssertLongLongInt(1, cDatabase.NumDataCached());
	AssertLongLongInt(10, cDatabase.NumNamesCached());
	AssertLongLongInt(2044, cIndexEvictionCounter.EvictionCount());
	AssertLongLongInt(1023, cDataEvictionCounter.EvictionCount());
	AssertLongLongInt(2034, cNameEvictionCounter.EvictionCount());
	AssertLongLongInt(1023, cDatabase.NumIndices());
	AssertLongLongInt(1023, cDatabase.NumNames());

	if (eWriteThrough == IWT_No) cDatabase.Flush();
	cController.End();
	cDatabase.Kill();
	cController.Kill();
	cNamedEvictionStrategy.Kill();
	cIndexEvictionStrategy.Kill();

	cFileUtil.RemoveDir("Output" _FS_ "Database8");

	aszWords.Kill();
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
	TestNamedIndexedDataIterate(IWT_Yes);
	TestNamedIndexedDataIterate(IWT_No);
	TestNamedIndexedDataGetDoesNotExceedCache(IWT_Yes);
	TestNamedIndexedDataGetDoesNotExceedCache(IWT_No);
	TestNamedIndexedDataIterateDuringTreeChange(IWT_Yes);
	TestNamedIndexedDataIterateDuringTreeChange(IWT_No);

	TestStatistics();
	DataMemoryKill();
	MemoryKill();
	FastFunctionsKill();
	TypeConverterKill();
}

