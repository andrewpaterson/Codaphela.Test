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
void TestNamedIndexedDataInit(void)
{
	CNamedIndexedData					cDatabase;
	CValueIndexedDataConfig				cIndexConfig;
	CValueNamedIndexesConfig			cNamedConfig;
	CNamedIndexedDataConfig				cConfig;
	CDurableFileController				cController;
	CIndexTreeEvictionStrategyRandom	cEvictionStrategy;
	CFileUtil							cFileUtil;

	cFileUtil.RemoveDir("Output" _FS_ "Database1");

	cController.Init("Output" _FS_ "Database1" _FS_ "R", "Output" _FS_ "Database1" _FS_ "W");

	cIndexConfig.Init(&cController, "IndexData", 8 KB, 8 KB, IWT_Yes);
	cNamedConfig.Init(&cController, "Names", 16 KB, &cEvictionStrategy, IWT_Yes);
	cConfig.Init(&cIndexConfig, &cNamedConfig);
	
	cController.Begin();
	cDatabase.Init(&cConfig);
	cController.End();
	cConfig.Kill();

	cDatabase.Kill();
	cFileUtil.RemoveDir("Output" _FS_ "Database1");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestNamedIndexedDataAddString(void)
{
	CNamedIndexedData					cDatabase;
	CValueIndexedDataConfig				cIndexConfig;
	CValueNamedIndexesConfig			cNamedConfig;
	CNamedIndexedDataConfig				cConfig;
	CDurableFileController				cController;
	CIndexTreeEvictionStrategyRandom	cEvictionStrategy;
	CFileUtil							cFileUtil;
	CTestNamedIndexedDataObject			cObject1;
	CTestNamedIndexedDataObject			cObject2;
	CTestNamedIndexedDataObject			cResult;
	BOOL								bResult;

	cFileUtil.RemoveDir("Output" _FS_ "Database2");

	/// Add Name and Index
	cController.Init("Output" _FS_ "Database2" _FS_ "R", "Output" _FS_ "Database2" _FS_ "W");

	cIndexConfig.Init(&cController, "IndexData", 8 KB, 8 KB, IWT_Yes);
	cNamedConfig.Init(&cController, "Names", 16 KB, &cEvictionStrategy, IWT_Yes);
	cConfig.Init(&cIndexConfig, &cNamedConfig);

	cController.Begin();
	cDatabase.Init(&cConfig);
	cController.End();
	cConfig.Kill();

	cController.Begin();
	cObject1.Init("Rutherford", 1871, 1937);
	cDatabase.Add(0x0102LL, "Ernest", &cObject1, cObject1.Size());
	cController.End();

	cController.Begin();
	cObject2.Init("Bohr", 1885, 1962);
	cDatabase.Add(0x0203LL, "Niels", &cObject2, cObject2.Size());
	cController.End();

	cDatabase.Kill();
	cController.Kill();


	//Get by Name
	cController.Init("Output" _FS_ "Database2" _FS_ "R", "Output" _FS_ "Database2" _FS_ "W");

	cIndexConfig.Init(&cController, "IndexData", 8 KB, 8 KB, IWT_Yes);
	cNamedConfig.Init(&cController, "Names", 16 KB, &cEvictionStrategy, IWT_Yes);
	cConfig.Init(&cIndexConfig, &cNamedConfig);

	cController.Begin();
	cDatabase.Init(&cConfig);
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


	//Get by Index
	cController.Init("Output" _FS_ "Database2" _FS_ "R", "Output" _FS_ "Database2" _FS_ "W");

	cIndexConfig.Init(&cController, "IndexData", 8 KB, 8 KB, IWT_Yes);
	cNamedConfig.Init(&cController, "Names", 16 KB, &cEvictionStrategy, IWT_Yes);
	cConfig.Init(&cIndexConfig, &cNamedConfig);

	cController.Begin();
	cDatabase.Init(&cConfig);
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


	//Size by Index
	cController.Init("Output" _FS_ "Database2" _FS_ "R", "Output" _FS_ "Database2" _FS_ "W");

	cIndexConfig.Init(&cController, "IndexData", 8 KB, 8 KB, IWT_Yes);
	cNamedConfig.Init(&cController, "Names", 16 KB, &cEvictionStrategy, IWT_Yes);
	cConfig.Init(&cIndexConfig, &cNamedConfig);

	cController.Begin();
	cDatabase.Init(&cConfig);
	cController.End();
	cConfig.Kill();

	cController.Begin();
	AssertInt(sizeof(CTestNamedIndexedDataObject), cDatabase.Size(0x0203));
	AssertInt(sizeof(CTestNamedIndexedDataObject), cDatabase.Size(0x0102));
	AssertLongLongInt(2, cDatabase.NumIndices());
	AssertLongLongInt(2, cDatabase.NumNames());
	cController.End();


	cDatabase.Kill();
	cController.Kill();


	cFileUtil.RemoveDir("Output" _FS_ "Database2");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestNamedIndexedDataAddChars(void)
{
	CNamedIndexedData					cDatabase;
	CValueIndexedDataConfig				cIndexConfig;
	CValueNamedIndexesConfig			cNamedConfig;
	CNamedIndexedDataConfig				cConfig;
	CDurableFileController				cController;
	CIndexTreeEvictionStrategyRandom	cEvictionStrategy;
	CFileUtil							cFileUtil;
	CTestNamedIndexedDataObject			cObject1;
	CTestNamedIndexedDataObject			cResult;
	BOOL								bResult;
	CChars								szName;

	cFileUtil.RemoveDir("Output" _FS_ "Database2a");

	/// Add Name and Index
	cController.Init("Output" _FS_ "Database2a" _FS_ "R", "Output" _FS_ "Database2a" _FS_ "W");

	cIndexConfig.Init(&cController, "IndexData", 8 KB, 8 KB, IWT_Yes);
	cNamedConfig.Init(&cController, "Names", 16 KB, &cEvictionStrategy, IWT_Yes);
	cConfig.Init(&cIndexConfig, &cNamedConfig);

	cController.Begin();
	cDatabase.Init(&cConfig);
	cController.End();
	cConfig.Kill();

	cController.Begin();
	szName.Init("Ernest");
	cObject1.Init("Rutherford", 1871, 1937);
	cDatabase.Add(1LL, &szName, &cObject1, cObject1.Size());
	szName.Kill();
	cController.End();


	//Get by Name
	cController.Init("Output" _FS_ "Database2a" _FS_ "R", "Output" _FS_ "Database2a" _FS_ "W");

	cIndexConfig.Init(&cController, "IndexData", 8 KB, 8 KB, IWT_Yes);
	cNamedConfig.Init(&cController, "Names", 16 KB, &cEvictionStrategy, IWT_Yes);
	cConfig.Init(&cIndexConfig, &cNamedConfig);

	cController.Begin();
	cDatabase.Init(&cConfig);
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

	cFileUtil.RemoveDir("Output" _FS_ "Database2a");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestNamedIndexedDataAddBad(void)
{
	CNamedIndexedData					cDatabase;
	CValueIndexedDataConfig				cIndexConfig;
	CValueNamedIndexesConfig			cNamedConfig;
	CNamedIndexedDataConfig				cConfig;
	CDurableFileController				cController;
	CIndexTreeEvictionStrategyRandom	cEvictionStrategy;
	CFileUtil							cFileUtil;
	CTestNamedIndexedDataObject			cObject1;
	SLogConfig							sLogConfig;
	CChars								szName;

	cFileUtil.RemoveDir("Output" _FS_ "Database2b");

	cController.Init("Output" _FS_ "Database2b" _FS_ "R", "Output" _FS_ "Database2b" _FS_ "W");

	cIndexConfig.Init(&cController, "IndexData", 8 KB, 8 KB, IWT_Yes);
	cNamedConfig.Init(&cController, "Names", 16 KB, &cEvictionStrategy, IWT_Yes);
	cConfig.Init(&cIndexConfig, &cNamedConfig);

	cController.Begin();
	cDatabase.Init(&cConfig);
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

	cFileUtil.RemoveDir("Output" _FS_ "Database2b");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestNamedIndexedDataAddIndex(void)
{
	CNamedIndexedData					cDatabase;
	CValueIndexedDataConfig				cIndexConfig;
	CValueNamedIndexesConfig			cNamedConfig;
	CNamedIndexedDataConfig				cConfig;
	CDurableFileController				cController;
	CIndexTreeEvictionStrategyRandom	cEvictionStrategy;
	CFileUtil							cFileUtil;
	CTestNamedIndexedDataObject			cObject1;
	CTestNamedIndexedDataObject			cResult;

	cFileUtil.RemoveDir("Output" _FS_ "Database2c");

	/// Add Index
	cController.Init("Output" _FS_ "Database2c" _FS_ "R", "Output" _FS_ "Database2c" _FS_ "W");

	cIndexConfig.Init(&cController, "IndexData", 8 KB, 8 KB, IWT_Yes);
	cNamedConfig.Init(&cController, "Names", 16 KB, &cEvictionStrategy, IWT_Yes);
	cConfig.Init(&cIndexConfig, &cNamedConfig);

	cController.Begin();
	cDatabase.Init(&cConfig);
	cController.End();
	cConfig.Kill();

	cController.Begin();
	cObject1.Init("Rutherford", 1871, 1937);
	cDatabase.Add(0x56788435450563LL, &cObject1, cObject1.Size());
	cController.End();


	//Get by Index
	cController.Init("Output" _FS_ "Database2c" _FS_ "R", "Output" _FS_ "Database2c" _FS_ "W");

	cIndexConfig.Init(&cController, "IndexData", 8 KB, 8 KB, IWT_Yes);
	cNamedConfig.Init(&cController, "Names", 16 KB, &cEvictionStrategy, IWT_Yes);
	cConfig.Init(&cIndexConfig, &cNamedConfig);

	cController.Begin();
	cDatabase.Init(&cConfig);
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


	cDatabase.Kill();
	cController.Kill();

	cFileUtil.RemoveDir("Output" _FS_ "Database2c");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestNamedIndexedDataGetName(void)
{
	CNamedIndexedData					cDatabase;
	CValueIndexedDataConfig				cIndexConfig;
	CValueNamedIndexesConfig			cNamedConfig;
	CNamedIndexedDataConfig				cConfig;
	CDurableFileController				cController;
	CIndexTreeEvictionStrategyRandom	cEvictionStrategy;
	CFileUtil							cFileUtil;
	int									pai[512];
	CChars								szName;

	cFileUtil.RemoveDir("Output" _FS_ "Database3");

	cController.Init("Output" _FS_ "Database3" _FS_ "R", "Output" _FS_ "Database3" _FS_ "W");

	cIndexConfig.Init(&cController, "IndexData", 8 KB, 8 KB, IWT_Yes);
	cNamedConfig.Init(&cController, "Names", 16 KB, &cEvictionStrategy, IWT_Yes);
	cConfig.Init(&cIndexConfig, &cNamedConfig);

	cController.Begin();
	cDatabase.Init(&cConfig);
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

	cController.End();

	cDatabase.Kill();
	cController.Kill();

	cFileUtil.RemoveDir("Output" _FS_ "Database3");
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

	TestNamedIndexedDataInit();
	TestNamedIndexedDataAddString();
	TestNamedIndexedDataAddChars();
	TestNamedIndexedDataAddIndex();
	TestNamedIndexedDataAddBad();
	TestNamedIndexedDataGetName();

	TestStatistics();
	DataMemoryKill();
	MemoryKill();
	FastFunctionsKill();
	TypeConverterKill();
}

