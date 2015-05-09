#include "BaseLib/TemporaryMemory.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTemporaryMemorySize(void)
{
	CTemporaryMemory	cTemp;
	void*				pv;
	void*				pvOld;

	cTemp.Init();
	AssertNull(cTemp.Get());
	pv = cTemp.Size(10);
	AssertNotNull(cTemp.Get());
	pvOld = pv;
	pv = cTemp.Size(9);
	AssertPointer(pvOld, pv);
	pvOld = pv;
	pv = cTemp.Size(1024*1024);
	AssertFalse(pvOld == pv);

	cTemp.Kill();
	AssertNull(cTemp.Get());
	pv = cTemp.Size(10);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTemporaryMemory(void)
{
	BeginTests();
	FastFunctionsInit();

	TestTemporaryMemorySize();

	FastFunctionsKill();
	TestStatistics();
}

