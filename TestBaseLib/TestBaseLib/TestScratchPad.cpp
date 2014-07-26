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

	cPad.Init(10 + sizeof(SSPNode));

	pvData = cPad.Add(10);
	AssertNotNull(pvData);
	AssertInt(18, cPad.GetMemorySize());
	AssertInt(18, cPad.GetUsedSize());

	pvData = cPad.Add(9);
	AssertNotNull(pvData);
	AssertInt(36, cPad.GetMemorySize());
	AssertInt(35, cPad.GetUsedSize());

	pvData = cPad.Add(5);
	AssertNotNull(pvData);
	AssertInt(54, cPad.GetMemorySize());
	AssertInt(48, cPad.GetUsedSize());

	pvData = cPad.Add(5);
	AssertNotNull(pvData);
	AssertInt(72, cPad.GetMemorySize());
	AssertInt(61, cPad.GetUsedSize());

	pvData = cPad.Add(11);
	AssertNotNull(pvData);
	AssertInt(91, cPad.GetMemorySize());
	AssertInt(80, cPad.GetUsedSize());
	
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


