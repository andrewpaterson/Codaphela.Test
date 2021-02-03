#include "BaseLib/GlobalMemory.h"
#include "StandardLib/Unknowns.h"
#include "TestLib/Assert.h"
#include "UnknownTestClasses.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestUnknownListAddKill(void)
{
	MemoryInit();

	CUnknowns		cUnknowns;
	CTestUnknown*	pcTest;
	CFreeList*		pcFreeList;
	CGeneralMemory*	pcMemory;

	cUnknowns.Init("Test1", &gcConstructors);
	pcMemory = cUnknowns.GetMemory();
	AssertNotNull(pcMemory);
	AssertInt(0, pcMemory->NumElements());
	AssertTrue(pcMemory->ByteSize() <= 64);

	pcTest = cUnknowns.Add<CTestUnknown>();
	AssertPointer(&cUnknowns, pcTest->GetUnknownsThisIn());
	pcFreeList = cUnknowns.GetFreeList(sizeof(CTestUnknown));
	AssertInt(1, pcFreeList->NumElements());
	AssertInt(1, pcMemory->NumElements());
	AssertInt(431, pcMemory->ByteSize());

	pcTest->Init();
	pcTest->Kill();
	pcFreeList = cUnknowns.GetFreeList(sizeof(CTestUnknown));
	AssertNull(pcFreeList);
	AssertInt(0, pcMemory->NumElements());
	AssertTrue(pcMemory->ByteSize() <= 64);

	cUnknowns.Kill();

	MemoryKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestUnknownListIterables(void)
{
	MemoryInit();

	CUnknowns									cUnknowns;
	CTestIterableUnknown*						pcTest7;
	CTestIterableUnknown*						pcTest5;
	CTestIterableUnknown*						pcTest3;
	CTestIterableUnknown*						pcTest4;
	CTestIterableUnknown*						pcTest1;
	CTestIterableUnknown*						pcTest;
	SIteratorTemplate<CTestIterableUnknown>		sIter; 

	cUnknowns.Init("Test2", &gcConstructors);

	pcTest7 = cUnknowns.Add<CTestIterableUnknown>();
	pcTest7->Init(7);
	pcTest5 = cUnknowns.Add<CTestIterableUnknown>();
	pcTest5->Init(5);
	pcTest3 = cUnknowns.Add<CTestIterableUnknown>();
	pcTest3->Init(3);
	pcTest4 = cUnknowns.Add<CTestIterableUnknown>();
	pcTest4->Init(4);
	pcTest1 = cUnknowns.Add<CTestIterableUnknown>();
	pcTest1->Init(1);

	pcTest = cUnknowns.StartIteration(&sIter);
	AssertInt(7, pcTest->miID);
	pcTest = cUnknowns.Iterate(&sIter);
	AssertInt(5, pcTest->miID);
	pcTest = cUnknowns.Iterate(&sIter);
	AssertInt(3, pcTest->miID);
	pcTest = cUnknowns.Iterate(&sIter);
	AssertInt(4, pcTest->miID);
	pcTest = cUnknowns.Iterate(&sIter);
	AssertInt(1, pcTest->miID);
	pcTest = cUnknowns.Iterate(&sIter);
	AssertNull(pcTest);

	pcTest7->Kill();
	pcTest1->Kill();

	pcTest = cUnknowns.StartIteration(&sIter);
	AssertInt(5, pcTest->miID);
	pcTest = cUnknowns.Iterate(&sIter);
	AssertInt(3, pcTest->miID);
	pcTest = cUnknowns.Iterate(&sIter);
	AssertInt(4, pcTest->miID);
	pcTest = cUnknowns.Iterate(&sIter);
	AssertNull(pcTest);

	pcTest3->Kill();

	pcTest = cUnknowns.StartIteration(&sIter);
	AssertInt(5, pcTest->miID);
	pcTest = cUnknowns.Iterate(&sIter);
	AssertInt(4, pcTest->miID);
	pcTest = cUnknowns.Iterate(&sIter);
	AssertNull(pcTest);

	pcTest5->Kill();
	pcTest4->Kill();

	pcTest = cUnknowns.StartIteration(&sIter);
	AssertNull(pcTest);

	cUnknowns.Kill();

	MemoryKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestUnknownListRemoveDuringIteration(void)
{
	MemoryInit();

	CUnknowns									cUnknowns;
	CTestIterableUnknown*						pcTest7;
	CTestIterableUnknown*						pcTest5;
	CTestIterableUnknown*						pcTest3;
	CTestIterableUnknown*						pcTest4;
	CTestIterableUnknown*						pcTest1;
	CTestIterableUnknown*						pcTest;
	SIteratorTemplate<CTestIterableUnknown>		sIter; 

	cUnknowns.Init("Test3", &gcConstructors);

	pcTest7 = cUnknowns.Add<CTestIterableUnknown>();
	pcTest7->Init(7);
	pcTest5 = cUnknowns.Add<CTestIterableUnknown>();
	pcTest5->Init(5);
	pcTest3 = cUnknowns.Add<CTestIterableUnknown>();
	pcTest3->Init(3);
	pcTest4 = cUnknowns.Add<CTestIterableUnknown>();
	pcTest4->Init(4);
	pcTest1 = cUnknowns.Add<CTestIterableUnknown>();
	pcTest1->Init(1);

	pcTest = cUnknowns.StartIteration(&sIter);
	AssertInt(7, pcTest->miID);
	cUnknowns.RemoveDuringIteration(&sIter);

	pcTest = cUnknowns.Iterate(&sIter);
	AssertInt(5, pcTest->miID);
	cUnknowns.RemoveDuringIteration(&sIter);
	cUnknowns.RemoveDuringIteration(&sIter);

	pcTest = cUnknowns.Iterate(&sIter);
	AssertInt(4, pcTest->miID);
	cUnknowns.RemoveDuringIteration(&sIter);
	cUnknowns.RemoveDuringIteration(&sIter);
	AssertInt(0, cUnknowns.GetIterableListsHeadNumElements());
	cUnknowns.RemoveDuringIteration(&sIter);
	AssertInt(0, cUnknowns.GetIterableListsHeadNumElements());

	cUnknowns.Kill();

	MemoryKill();
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

