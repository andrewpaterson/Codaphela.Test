#include "BaseLib/ScratchPad.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestScratchPadAdd(void)
{
	CScratchPad		cPad;
	void*			pvData;

	cPad.Init(10);

	pvData = cPad.Add(10);
	AssertNotNull(pvData);
	AssertInt(10, cPad.GetMemorySize());
	AssertInt(10, cPad.GetUsedSize());

	pvData = cPad.Add(9);
	AssertNotNull(pvData);
	AssertInt(20, cPad.GetMemorySize());
	AssertInt(19, cPad.GetUsedSize());

	pvData = cPad.Add(5);
	AssertNotNull(pvData);
	AssertInt(30, cPad.GetMemorySize());
	AssertInt(24, cPad.GetUsedSize());

	pvData = cPad.Add(5);
	AssertNotNull(pvData);
	AssertInt(30, cPad.GetMemorySize());
	AssertInt(29, cPad.GetUsedSize());

	pvData = cPad.Add(11);
	AssertNotNull(pvData);
	AssertInt(41, cPad.GetMemorySize());
	AssertInt(40, cPad.GetUsedSize());
	
	cPad.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestScratchPadRollback(void)
{
	CScratchPad		cPad;
	
	cPad.Init(100);

	cPad.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestScratchPad(void)
{
	BeginTests();

	TestScratchPadAdd();
	TestScratchPadRollback();

	TestStatistics();
}


