#include "BaseLib/FileUtil.h"
#include "BaseLib/GlobalMemory.h"
#include "StandardLib/Objects.h"
#include "StandardLib/ObjectGraphSerialiser.h"
#include "StandardLib/ObjectWriterSimple.h"
#include "TestLib/Assert.h"
#include "ObjectTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectGraphSerialiserReachability(void)
{
	CFileUtil						cFileUtil;
	Ptr<CTestSaveableObject1>	pTest1a;
	Ptr<CTestSaveableObject1>	pTest1b;
	Ptr<CTestSaveableObject1>	pTest1c;
	Ptr<CTestSaveableObject2>	pTest2a;
	Ptr<CTestSaveableObject2>	pTest2b;
	CObjectGraphSerialiser			cGraphSerialiser;
	CObjectWriterSimple				cSimpleWriter;

	BOOL							bResult;

	cFileUtil.MakeDir("Output" _FS_ "GraphWriter" _FS_ "Data");

	pTest1a = ONMalloc(CTestSaveableObject1, "Test1/OneA");
	pTest1a->Init();
	pTest1a->mszString.Append("I'm a real string now.");
	pTest1a->miInt = 19;

	pTest1b = ONMalloc(CTestSaveableObject1, "Test1/OneB");
	pTest1b->Init();
	pTest1b->mszString.Append("More Testing!");
	pTest1b->miInt = 2;

	pTest1c = ONMalloc(CTestSaveableObject1, "Test1/Miscellaneous/OneC");
	pTest1c->Init();
	pTest1c->mszString.Append("Ur-Quan");
	pTest1c->miInt = -1;

	pTest2a = ONMalloc(CTestSaveableObject2, "Test2/TwoAye");
	pTest2a->Init("Hello");

	pTest2b = ONMalloc(CTestSaveableObject2, "Test2/TowBee");
	pTest2b->Init("World");

	pTest2a->mp1 = pTest1a;
	pTest2a->mp2 = pTest2b;
	pTest1a->mpObject = pTest1b;
	pTest2b->mp1 = pTest1c;
	pTest2b->mp2 = pTest1b;

	AssertInt(224, sizeof(CTestSaveableObject1));  //If these sizes change the input test files will be wrong.
	AssertInt(232, sizeof(CTestSaveableObject2));

	cSimpleWriter.Init("Output" _FS_ "GraphWriter" _FS_ "Data", "");
	cGraphSerialiser.Init(&cSimpleWriter);
	bResult = cGraphSerialiser.Write(&pTest2a);
	AssertTrue(bResult);
	cGraphSerialiser.Kill();

	AssertTrue(pTest1a->mbSaved);
	AssertTrue(pTest1b->mbSaved);
	AssertTrue(pTest1c->mbSaved);
	AssertTrue(pTest2a->mbSaved);
	AssertTrue(pTest2b->mbSaved);

	AssertFile("Input" _FS_ "OneA.DRG", "Output" _FS_ "GraphWriter" _FS_ "Data" _FS_ "Test1" _FS_ "OneA.DRG");
	AssertFile("Input" _FS_ "OneB.DRG", "Output" _FS_ "GraphWriter" _FS_ "Data" _FS_ "Test1" _FS_ "OneB.DRG");
	AssertFile("Input" _FS_ "OneC.DRG", "Output" _FS_ "GraphWriter" _FS_ "Data" _FS_ "Test1" _FS_ "Miscellaneous" _FS_ "OneC.DRG");
	AssertFile("Input" _FS_ "TwoAye.DRG", "Output" _FS_ "GraphWriter" _FS_ "Data" _FS_ "Test2" _FS_ "TwoAye.DRG");
	AssertFile("Input" _FS_ "TowBee.DRG", "Output" _FS_ "GraphWriter" _FS_ "Data" _FS_ "Test2" _FS_ "TowBee.DRG");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestObjectGraphSerialiser(void)
{
	CFileUtil	cFileUtil;

	cFileUtil.RemoveDir("Output");
	cFileUtil.MakeDir("Output" _FS_ "GraphWriter");

	MemoryInit();
	ObjectsInit();
	BeginTests();

	TestObjectGraphSerialiserReachability();

	TestStatistics();
	ObjectsKill();
	MemoryKill();

	cFileUtil.RemoveDir("Output");
}

