#include "BaseLib/GlobalMemory.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/DiskFile.h"
#include "TestLib/Assert.h"
#include "StandardLib/Unknowns.h"
#include "StandardLib/ArrayUnknown.h"
#include "UnknownTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayAllocation(void)
{
	MemoryInit();
	UnknownsInit();

	CArrayUnknown							cArray;
	CTestNamedUnknown*						pcTest1;
	CTestNamedUnknown*						pcTest2;
	CTestNamedUnknown*						pcTest3;
	int										iNum;
	CTestNamedUnknown*						pcTest;
	SIteratorTemplate<CTestNamedUnknown>	sIter;

	cArray.Init();

	pcTest1 = cArray.Add<CTestNamedUnknown>();
	pcTest1->Init("The One");

	pcTest2 = cArray.Add<CTestNamedUnknown>();
	pcTest2->Init("Two");

	pcTest3 = UMalloc(CTestNamedUnknown);
	pcTest3->Init("There can be only three");
	cArray.Add(pcTest3);
	
	iNum = cArray.NumElements();
	AssertInt(3, iNum);
	pcTest = (CTestNamedUnknown*)cArray.Get(0);
	AssertString("The One", pcTest->GetName());
	pcTest = (CTestNamedUnknown*)cArray.Get(1);
	AssertString("Two", pcTest->GetName());
	pcTest = (CTestNamedUnknown*)cArray.Get(2);
	AssertString("There can be only three", pcTest->GetName());

	cArray.Remove(1);

	iNum = cArray.NumElements();
	AssertInt(2, iNum);
	pcTest = (CTestNamedUnknown*)cArray.Get(0);
	AssertString("The One", pcTest->GetName());
	pcTest = (CTestNamedUnknown*)cArray.Get(1);
	AssertString("There can be only three", pcTest->GetName());

	pcTest = gcUnknowns.StartIteration(&sIter);
	AssertString("The One", pcTest->GetName());
	pcTest = gcUnknowns.Iterate(&sIter);
	AssertString("There can be only three", pcTest->GetName());
	
	cArray.Kill();

	pcTest = gcUnknowns.StartIteration(&sIter);
	AssertNull(pcTest);

	UnknownsKill();
	MemoryKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestRemoval(void)
{
	MemoryInit();
	UnknownsInit();

	CArrayUnknown							cArray;
	CTestNamedUnknown*						pcTest1;
	CTestNamedUnknown*						pcTest2;
	CTestNamedUnknown*						pcTest3;
	int										iNum;
	CTestNamedUnknown*						pcTest;
	SIteratorTemplate<CTestNamedUnknown>	sIter;
	SSetIterator							sSetIter;

	cArray.Init();

	pcTest1 = cArray.Add<CTestNamedUnknown>();
	pcTest1->Init("The One");

	pcTest2 = cArray.Add<CTestNamedUnknown>();
	pcTest2->Init("Two");

	pcTest3 = UMalloc(CTestNamedUnknown);
	pcTest3->Init("There can be only three");
	cArray.Add(pcTest3);

	iNum = cArray.NumElements();
	AssertInt(3, iNum);

	cArray.StartIteration(&sSetIter);
	cArray.RemoveDuringIteration(&sSetIter);
	cArray.RemoveDuringIteration(&sSetIter);
	cArray.RemoveDuringIteration(&sSetIter);

	iNum = cArray.NumElements();
	AssertInt(0, iNum);

	cArray.RemoveDuringIteration(&sSetIter);

	pcTest = gcUnknowns.StartIteration(&sIter);
	AssertNull(pcTest);

	cArray.Kill();

	cArray.Init();

	pcTest1 = cArray.Add<CTestNamedUnknown>();
	pcTest1->Init("The One");

	pcTest2 = cArray.Add<CTestNamedUnknown>();
	pcTest2->Init("Two");

	pcTest3 = UMalloc(CTestNamedUnknown);
	pcTest3->Init("There can be only three");
	cArray.Add(pcTest3);

	iNum = cArray.NumElements();
	AssertInt(3, iNum);

	pcTest = (CTestNamedUnknown*)cArray.StartIteration(&sSetIter);
	AssertString("The One", pcTest->GetName());

	cArray.RemoveDuringIteration(&sSetIter);
	pcTest = (CTestNamedUnknown*)cArray.Iterate(&sSetIter);
	AssertString("Two", pcTest->GetName());

	cArray.RemoveDuringIteration(&sSetIter);
	iNum = cArray.NumElements();
	AssertInt(1, iNum);
	pcTest = (CTestNamedUnknown*)cArray.Iterate(&sSetIter);
	AssertString("There can be only three", pcTest->GetName());

	cArray.RemoveDuringIteration(&sSetIter);
	iNum = cArray.NumElements();
	AssertInt(0, iNum);

	cArray.RemoveDuringIteration(&sSetIter);
	cArray.Kill();

	UnknownsKill();
	MemoryKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIteration(void)
{
	MemoryInit();
	UnknownsInit();

	CArrayUnknown			cArray;
	CTestNamedUnknown*		pcTest;
	SSetIterator			sSetIter;

	cArray.Init();

	pcTest = cArray.Add<CTestNamedUnknown>();
	pcTest->Init("A");
	pcTest = cArray.Add<CTestNamedUnknown>();
	pcTest->Init("B");
	pcTest = cArray.Add<CTestNamedUnknown>();
	pcTest->Init("C");
	pcTest = cArray.Add<CTestNamedUnknown>();
	pcTest->Init("D");

	pcTest = (CTestNamedUnknown*)cArray.StartIteration(&sSetIter);
	AssertString("A", pcTest->GetName());
	AssertInt(0, sSetIter.iIndex);
	pcTest = (CTestNamedUnknown*)cArray.Iterate(&sSetIter);
	AssertString("B", pcTest->GetName());
	AssertInt(1, sSetIter.iIndex);
	pcTest = (CTestNamedUnknown*)cArray.Iterate(&sSetIter);
	AssertString("C", pcTest->GetName());
	AssertInt(2, sSetIter.iIndex);
	pcTest = (CTestNamedUnknown*)cArray.Iterate(&sSetIter);
	AssertString("D", pcTest->GetName());
	AssertInt(3, sSetIter.iIndex);
	pcTest = (CTestNamedUnknown*)cArray.Iterate(&sSetIter);
	AssertNull(pcTest);
	AssertInt(4, sSetIter.iIndex);
	pcTest = (CTestNamedUnknown*)cArray.Iterate(&sSetIter);
	AssertNull(pcTest);
	AssertInt(4, sSetIter.iIndex);

	
	cArray.Kill();

	UnknownsKill();
	MemoryKill();
}



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayUnknownLoad(void)
{
	MemoryInit();
	UnknownsInit();

	CArrayUnknown		cArray;
	CChunkFile			cFile;
	CFileUtil			cFileUtil;
	CTestUnknown*		pcTest;
	CTestUnknownJobbie*	pcTestJobbie;
	BOOL				bResult;
	CUnknown*			pcUnknown;

	AssertInt(0, gcConstructors.NumConstructors());
	AssertInt(0, gcUnknowns.NumElements());
	gcUnknowns.AddConstructor<CTestUnknownJobbie>();
	gcUnknowns.AddConstructor<CTestUnknown>();
	AssertInt(0, gcUnknowns.NumElements());
	AssertInt(2, gcConstructors.NumConstructors());

	cFileUtil.RemoveDir("Output" _FS_ "ArrayUnknown");
	cFileUtil.TouchDir("Output" _FS_ "ArrayUnknown");

	cArray.Init();
	pcTest = cArray.Add<CTestUnknown>();
	pcTest->Init(3);
	pcTestJobbie = cArray.Add<CTestUnknownJobbie>();
	pcTestJobbie->Init(2, "Two");
	pcTestJobbie = cArray.Add<CTestUnknownJobbie>();
	pcTestJobbie->Init(1, "Onety");
	pcTest = cArray.Add<CTestUnknown>();
	pcTest->Init(0);

	cFile.Init(DiskFile("Output" _FS_ "ArrayUnknown" _FS_ "Array.dat"));
	bResult = cFile.WriteOpen();
	AssertTrue(bResult);

	bResult = cArray.Save(&cFile);
	AssertTrue(bResult);

	bResult = cFile.WriteClose();
	AssertTrue(bResult);

	cFile.Kill();
	cArray.Kill();

	AssertInt(0, gcUnknowns.NumElements());

	cFile.Init(DiskFile("Output" _FS_ "ArrayUnknown" _FS_ "Array.dat"));
	bResult = cFile.ReadOpen();
	AssertTrue(bResult);

	bResult = cArray.Load(&cFile);
	AssertTrue(bResult);

	bResult = cFile.ReadClose();
	AssertTrue(bResult);

	cFile.Kill();

	AssertInt(4, cArray.NumElements());
	AssertInt(4, gcUnknowns.NumElements());

	pcUnknown = cArray.Get(0);
	AssertString("CTestUnknown", pcUnknown->ClassName());
	AssertInt(3, ((CTestUnknown*)pcUnknown)->miCount);

	pcUnknown = cArray.Get(1);
	AssertString("CTestUnknownJobbie", pcUnknown->ClassName());
	AssertInt(2, ((CTestUnknownJobbie*)pcUnknown)->miANumber);
	AssertString("Two", ((CTestUnknownJobbie*)pcUnknown)->mszText.Text());

	pcUnknown = cArray.Get(2);
	AssertString("CTestUnknownJobbie", pcUnknown->ClassName());
	AssertInt(1, ((CTestUnknownJobbie*)pcUnknown)->miANumber);
	AssertString("Onety", ((CTestUnknownJobbie*)pcUnknown)->mszText.Text());

	pcUnknown = cArray.Get(3);
	AssertString("CTestUnknown", pcUnknown->ClassName());
	AssertInt(0, ((CTestUnknown*)pcUnknown)->miCount);

	cArray.Kill();

	AssertInt(0, gcUnknowns.NumElements());

	cFileUtil.RemoveDir("Output" _FS_ "ArrayUnknown");

	UnknownsKill();
	MemoryKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayUnknown(void)
{
	BeginTests();

	TestArrayAllocation();
	TestIteration();
	TestRemoval();
	TestArrayUnknownLoad();

	TestStatistics();
}

