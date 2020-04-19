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
void TestNamedIndexedDataAdd(void)
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
	cDatabase.Add(0x0102, "Ernest", &cObject1, cObject1.Size());
	cController.End();

	cController.Begin();
	cObject2.Init("Bohr", 1885, 1962);
	cDatabase.Add(0x0203, "Niels", &cObject2, cObject2.Size());
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
	bResult = cDatabase.Get(0x0203, &cResult);
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


	cDatabase.Kill();
	cController.Kill();


	cFileUtil.RemoveDir("Output" _FS_ "Database2");
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
	TestNamedIndexedDataAdd();

	TestStatistics();
	DataMemoryKill();
	MemoryKill();
	FastFunctionsKill();
	TypeConverterKill();
}

