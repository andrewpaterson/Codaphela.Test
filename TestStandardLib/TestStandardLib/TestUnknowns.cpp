#include "StandardLib/Unknowns.h"
#include "TestLib/Assert.h"
#include "UnknownTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestUnknownListAddKill(void)
{
	CUnknowns			cList;
	CTestUnknown*		pcTest;
	CFreeList*		pcFreeList;

	cList.Init("Test1");

	pcTest = cList.Add<CTestUnknown>();
	AssertPointer(&cList, pcTest->GetUnknownsThisIn());
	pcFreeList = cList.GetFreeList(sizeof(CTestUnknown));
	AssertInt(1, pcFreeList->NumElements());
	pcTest->Init();
	pcTest->Kill();
	AssertInt(0, pcFreeList->NumElements());

	cList.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestUnknownListIterables(void)
{
	CUnknowns									cList;
	CTestIterableUnknown*						pcTest7;
	CTestIterableUnknown*						pcTest5;
	CTestIterableUnknown*						pcTest3;
	CTestIterableUnknown*						pcTest4;
	CTestIterableUnknown*						pcTest1;
	CTestIterableUnknown*						pcTest;
	SIteratorTemplate<CTestIterableUnknown>		sIter; 

	cList.Init("Test2");

	pcTest7 = cList.Add<CTestIterableUnknown>();
	pcTest7->Init(7);
	pcTest5 = cList.Add<CTestIterableUnknown>();
	pcTest5->Init(5);
	pcTest3 = cList.Add<CTestIterableUnknown>();
	pcTest3->Init(3);
	pcTest4 = cList.Add<CTestIterableUnknown>();
	pcTest4->Init(4);
	pcTest1 = cList.Add<CTestIterableUnknown>();
	pcTest1->Init(1);

	pcTest = cList.StartIteration(&sIter);
	AssertInt(7, pcTest->miID);
	pcTest = cList.Iterate(&sIter);
	AssertInt(5, pcTest->miID);
	pcTest = cList.Iterate(&sIter);
	AssertInt(3, pcTest->miID);
	pcTest = cList.Iterate(&sIter);
	AssertInt(4, pcTest->miID);
	pcTest = cList.Iterate(&sIter);
	AssertInt(1, pcTest->miID);
	pcTest = cList.Iterate(&sIter);
	AssertNull(pcTest);

	pcTest7->Kill();
	pcTest1->Kill();

	pcTest = cList.StartIteration(&sIter);
	AssertInt(5, pcTest->miID);
	pcTest = cList.Iterate(&sIter);
	AssertInt(3, pcTest->miID);
	pcTest = cList.Iterate(&sIter);
	AssertInt(4, pcTest->miID);
	pcTest = cList.Iterate(&sIter);
	AssertNull(pcTest);

	pcTest3->Kill();

	pcTest = cList.StartIteration(&sIter);
	AssertInt(5, pcTest->miID);
	pcTest = cList.Iterate(&sIter);
	AssertInt(4, pcTest->miID);
	pcTest = cList.Iterate(&sIter);
	AssertNull(pcTest);

	pcTest5->Kill();
	pcTest4->Kill();

	pcTest = cList.StartIteration(&sIter);
	AssertNull(pcTest);

	cList.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestUnknownListRemoveDuringIteration(void)
{
	CUnknowns									cList;
	CTestIterableUnknown*						pcTest7;
	CTestIterableUnknown*						pcTest5;
	CTestIterableUnknown*						pcTest3;
	CTestIterableUnknown*						pcTest4;
	CTestIterableUnknown*						pcTest1;
	CTestIterableUnknown*						pcTest;
	SIteratorTemplate<CTestIterableUnknown>		sIter; 

	cList.Init("Test3");

	pcTest7 = cList.Add<CTestIterableUnknown>();
	pcTest7->Init(7);
	pcTest5 = cList.Add<CTestIterableUnknown>();
	pcTest5->Init(5);
	pcTest3 = cList.Add<CTestIterableUnknown>();
	pcTest3->Init(3);
	pcTest4 = cList.Add<CTestIterableUnknown>();
	pcTest4->Init(4);
	pcTest1 = cList.Add<CTestIterableUnknown>();
	pcTest1->Init(1);

	pcTest = cList.StartIteration(&sIter);
	AssertInt(7, pcTest->miID);
	cList.RemoveDuringIteration(&sIter);

	pcTest = cList.Iterate(&sIter);
	AssertInt(5, pcTest->miID);
	cList.RemoveDuringIteration(&sIter);
	cList.RemoveDuringIteration(&sIter);

	pcTest = cList.Iterate(&sIter);
	AssertInt(4, pcTest->miID);
	cList.RemoveDuringIteration(&sIter);
	cList.RemoveDuringIteration(&sIter);
	AssertInt(0, cList.GetIterableListsHeadNumElements());
	cList.RemoveDuringIteration(&sIter);
	AssertInt(0, cList.GetIterableListsHeadNumElements());

	cList.Kill();
}


//
//
//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestUnknowns(void)
{
	BeginTests();

	TestUnknownListAddKill();
	TestUnknownListIterables();
	TestUnknownListRemoveDuringIteration();

	TestStatistics();
}

