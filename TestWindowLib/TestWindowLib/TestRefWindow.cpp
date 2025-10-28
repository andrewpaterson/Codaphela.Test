#include "BaseLib/GlobalMemory.h"
#include "WinRefLib/WinRefWindowFactory.h"
#include "TestLib/Assert.h"
#include "ReferenceTestWindow.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestRefWindowCreation(void)
{
	CWinRefWindowFactory	cNativeFactory;
	CReferenceTestWindow	cTesterWindow;

	cNativeFactory.Init(&gcMemoryAllocator);
	cTesterWindow.Init("HCP65 Board Tester", &cNativeFactory);

	cTesterWindow.Show();

	cTesterWindow.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestRefWindow(void)
{
	BeginTests();

	TestRefWindowCreation();

	TestStatistics();
}

