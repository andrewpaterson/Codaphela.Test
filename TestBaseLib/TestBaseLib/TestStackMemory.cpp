#include "BaseLib/StackMemory.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestStackMemoryCompilation(void)
{
	CStackMemory<>	cTemp;
	void*			pv;

	pv = cTemp.Init(5 KB);
	AssertPointer(&cTemp, pv);
	cTemp.Kill();

	pv = cTemp.Init(12 KB);
	AssertFalse(&cTemp == pv);
	cTemp.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestStackMemory(void)
{
	BeginTests();
	FastFunctionsInit();

	TestStackMemoryCompilation();

	FastFunctionsKill();
	TestStatistics();
}

