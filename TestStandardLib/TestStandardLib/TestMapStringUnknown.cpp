#include "BaseLib/GlobalMemory.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/DiskFile.h"
#include "StandardLib/Unknowns.h"
#include "StandardLib/MapStringUnknown.h"
#include "TestLib/Assert.h"
#include "UnknownTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapStringUnknownPut(void)
{
	MemoryInit();
	UnknownsInit();

	CMapStringUnknown	cMap;
	CTestUnknownJobbie*	pcTest;

	cMap.Init();

	AssertInt(0, cMap.NumElements());

	pcTest = cMap.Put<CTestUnknownJobbie>("Hello");
	pcTest->Init(7, "1st");
	AssertInt(1, cMap.NumElements());

	pcTest = cMap.Put<CTestUnknownJobbie>("World");
	pcTest->Init(19, "A pony");
	AssertInt(2, cMap.NumElements());

	pcTest = cMap.Put<CTestUnknownJobbie>("Aardvark");
	pcTest->Init(4, "Restore");
	AssertInt(3, cMap.NumElements());

	pcTest = cMap.Put<CTestUnknownJobbie>(NULL);
	AssertNull(pcTest);
	AssertInt(3, cMap.NumElements());

	cMap.Kill();

	UnknownsKill();
	MemoryKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapStringUnknownGet(void)
{
	MemoryInit();
	UnknownsInit();

	CMapStringUnknown	cMap;
	CTestUnknownJobbie*	pcTest;
	CTestUnknownJobbie*	pcA1;
	CTestUnknownJobbie*	pcA2;
	CTestUnknownJobbie*	pcA3;

	cMap.Init();

	pcTest = cMap.Put<CTestUnknownJobbie>("Hello");
	pcTest->Init(7, "1st");
	pcTest = cMap.Put<CTestUnknownJobbie>("World");
	pcTest->Init(19, "A pony");
	pcTest = cMap.Put<CTestUnknownJobbie>("Aardvark");
	pcTest->Init(4, "Restore");
	AssertInt(3, cMap.NumElements());
	AssertInt(3, gcUnknowns.NumElements());

	pcTest = (CTestUnknownJobbie*)cMap.Get("World");
	AssertInt(19, pcTest->miANumber);
	AssertString("A pony", pcTest->mszText.Text());

	pcA1 = UMalloc(CTestUnknownJobbie);
	pcA1->Init(999, "Grand");
	cMap.Put("Thesaurus", pcA1);
	AssertInt(4, cMap.NumElements());
	AssertInt(4, gcUnknowns.NumElements());
	pcA2 = UMalloc(CTestUnknownJobbie);
	pcA2->Init(17, "Replaced!");
	cMap.Put("World", pcA2);
	AssertInt(4, cMap.NumElements());
	AssertInt(4, gcUnknowns.NumElements());
	pcA3 = UMalloc(CTestUnknownJobbie);
	pcA3->Init(32, "Another");
	cMap.Put("Jump", pcA3);
	AssertInt(5, cMap.NumElements());
	AssertInt(5, gcUnknowns.NumElements());

	pcTest = (CTestUnknownJobbie*)cMap.Get("World");
	AssertPointer(pcA2, pcTest);
	AssertString("Replaced!", pcTest->mszText.Text());

	pcTest = (CTestUnknownJobbie*)cMap.Get("world");
	AssertPointer(NULL, pcTest);
	pcTest = (CTestUnknownJobbie*)cMap.Get(NULL);
	AssertPointer(NULL, pcTest);
	pcTest = (CTestUnknownJobbie*)cMap.Get("");
	AssertPointer(NULL, pcTest);

	pcTest = cMap.Put<CTestUnknownJobbie>("");
	pcTest->Init(0, "Empty");
	pcTest = (CTestUnknownJobbie*)cMap.Get("");
	AssertString("Empty", pcTest->mszText.Text());

	cMap.Kill();

	AssertInt(0, gcUnknowns.NumElements());

	UnknownsKill();
	MemoryKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapStringUnknownNoOverwrite(void)
{
	MemoryInit();
	UnknownsInit();

	CMapStringUnknown	cMap;
	CTestUnknownJobbie*	pcTest;

	cMap.Init(TRUE, FALSE);

	AssertInt(0, gcUnknowns.NumElements());

	pcTest = cMap.Put<CTestUnknownJobbie>("One");
	pcTest->Init(2, "");
	AssertNotNull(pcTest);
	AssertInt(1, gcUnknowns.NumElements());

	pcTest = cMap.Put<CTestUnknownJobbie>("One");
	AssertNull(pcTest);
	AssertInt(1, gcUnknowns.NumElements());

	cMap.Kill();

	AssertInt(0, gcUnknowns.NumElements());

	UnknownsKill();
	MemoryKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapStringUnknownLoad(void)
{
	MemoryInit();
	UnknownsInit();

	CMapStringUnknown	cMap;
	CTestUnknownJobbie*	pcTest;
	CChunkFile			cFile;
	CFileUtil			cFileUtil;
	BOOL				bResult;

	gcUnknowns.AddConstructor<CTestUnknownJobbie>();
	AssertInt(0, gcUnknowns.NumElements());

	cFileUtil.RemoveDir("Output" _FS_ "MapStringUnknown");
	cFileUtil.MakeDir("Output" _FS_ "MapStringUnknown");

	cMap.Init();

	pcTest = cMap.Put<CTestUnknownJobbie>("Hello");
	pcTest->Init(7, "1st");
	pcTest = cMap.Put<CTestUnknownJobbie>("World");
	pcTest->Init(19, "A pony");
	pcTest = cMap.Put<CTestUnknownJobbie>("Aardvark");
	pcTest->Init(4, "Restore");
	pcTest = cMap.Put<CTestUnknownJobbie>("Yurk");
	pcTest->Init(8, "Yurk");

	cFile.Init(DiskFile("Output" _FS_ "MapStringUnknown" _FS_ "Map.dat"));
	bResult = cFile.WriteOpen();
	AssertTrue(bResult);

	bResult = cMap.Save(&cFile);
	AssertTrue(bResult);

	bResult = cFile.WriteClose();
	AssertTrue(bResult);

	cFile.Kill();
	cMap.Kill();

	AssertInt(0, gcUnknowns.NumElements());

	cFile.Init(DiskFile("Output" _FS_ "MapStringUnknown" _FS_ "Map.dat"));
	bResult = cFile.ReadOpen();
	AssertTrue(bResult);

	bResult = cMap.Load(&cFile);
	AssertTrue(bResult);

	bResult = cFile.ReadClose();
	AssertTrue(bResult);

	cFile.Kill();

	AssertInt(4, cMap.NumElements());
	AssertInt(4, gcUnknowns.NumElements());

	pcTest = (CTestUnknownJobbie*)cMap.Get("Hello");
	AssertInt(7, pcTest->miANumber);
	AssertString("1st", pcTest->mszText.Text());

	pcTest = (CTestUnknownJobbie*)cMap.Get("World");
	AssertInt(19, pcTest->miANumber);
	AssertString("A pony", pcTest->mszText.Text());

	pcTest = (CTestUnknownJobbie*)cMap.Get("Aardvark");
	AssertInt(4, pcTest->miANumber);
	AssertString("Restore", pcTest->mszText.Text());

	pcTest = (CTestUnknownJobbie*)cMap.Get("Yurk");
	AssertInt(8, pcTest->miANumber);
	AssertString("Yurk", pcTest->mszText.Text());

	cMap.Kill();

	AssertInt(0, gcUnknowns.NumElements());

	cFileUtil.RemoveDir("Output" _FS_ "MapStringUnknown");

	UnknownsKill();
	MemoryKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMapStringUnknown(void)
{
	BeginTests();

	TestMapStringUnknownPut();
	TestMapStringUnknownGet();
	TestMapStringUnknownNoOverwrite();
	TestMapStringUnknownLoad();

	TestStatistics();
}

