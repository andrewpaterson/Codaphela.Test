#include "BaseLib/GlobalMemory.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/DiskFile.h"
#include "TestLib/Assert.h"
#include "StandardLib/Unknowns.h"
#include "StandardLib/ArrayType.h"
#include "UnknownTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayTypeInstantiation(void)
{
	MemoryInit();
	UnknownsInit();
	
	CArrayType<CTestUnknown>	cArray;
	CTestUnknown*				pcTest1;
	CTestUnknown*				pcTest2;
	CTestUnknown*				pcTest3;
	CTestUnknown*				pcTest4;
	CTestUnknown*				pcTest;
	int							iSize;
	const char*					szName;
	
	cArray.Init();

	pcTest1 = cArray.Add();
	pcTest1->Init();
	pcTest2 = UMalloc(CTestUnknown);
	pcTest2->Init();
	cArray.Add(pcTest2);

	pcTest3 = cArray.Insert(0);
	pcTest3->Init();
	pcTest4 = UMalloc(CTestUnknown);
	pcTest4->Init();
	cArray.Insert(0, pcTest4);

	pcTest = cArray.Get(0);
	AssertPointer(pcTest4, pcTest);
	pcTest = cArray.Get(1);
	AssertPointer(pcTest3, pcTest);
	pcTest = cArray.Get(2);
	AssertPointer(pcTest1, pcTest);
	pcTest = cArray.Get(3);
	AssertPointer(pcTest2, pcTest);

	cArray.Remove(0);
	cArray.Remove(pcTest2);

	pcTest = cArray.Get(0);
	AssertPointer(pcTest3, pcTest);

	pcTest = cArray.Get(1);
	AssertPointer(pcTest1, pcTest);

	iSize = cArray.ClassSize();
	AssertInt(48, iSize);

	szName = cArray.ClassName();
	AssertString("CArrayType", szName);

	cArray.Kill();

	UnknownsKill();
	MemoryKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayTypeLoad(void)
{
	MemoryInit();
	UnknownsInit();

	CArrayType<CTestUnknown>	cArray;
	CChunkFile					cFile;
	CFileUtil					cFileUtil;
	CTestUnknown*				pcTest;
	BOOL						bResult;

	AssertInt(0, gcUnknowns.NumElements());

	cArray.Init();
	pcTest = cArray.Add();
	pcTest->Init(3);
	pcTest = cArray.Add();
	pcTest->Init(2);
	pcTest = cArray.Add();
	pcTest->Init(1);
	pcTest = cArray.Add();
	pcTest->Init(0);

	cFileUtil.TouchDir("Output" _FS_ "ArrayType");
	cFile.Init(DiskFile("Output" _FS_ "ArrayType" _FS_ "Array.dat"));
	bResult = cFile.WriteOpen();
	AssertTrue(bResult);

	bResult = cArray.Save(&cFile);
	AssertTrue(bResult);

	bResult = cFile.WriteClose();
	AssertTrue(bResult);

	cFile.Kill();
	cArray.Kill();

	AssertInt(0, gcUnknowns.NumElements());

	cFile.Init(DiskFile("Output" _FS_ "ArrayType" _FS_ "Array.dat"));
	bResult = cFile.ReadOpen();
	AssertTrue(bResult);

	bResult = cArray.Load(&cFile);
	AssertTrue(bResult);

	bResult = cFile.ReadClose();
	AssertTrue(bResult);

	cFile.Kill();

	AssertInt(4, cArray.NumElements());
	AssertInt(4, gcUnknowns.NumElements());

	AssertInt(3, cArray.Get(0)->miCount);
	AssertInt(2, cArray.Get(1)->miCount);
	AssertInt(1, cArray.Get(2)->miCount);
	AssertInt(0, cArray.Get(3)->miCount);

	cArray.Kill();

	AssertInt(0, gcUnknowns.NumElements());

	cFileUtil.RemoveDir("Output" _FS_ "ArrayType");

	UnknownsKill();
	MemoryKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayType(void)
{
	BeginTests();

	TestArrayTypeInstantiation();
	TestArrayTypeLoad();

	TestStatistics();
}

