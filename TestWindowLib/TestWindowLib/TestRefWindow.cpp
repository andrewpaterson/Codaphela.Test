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
	CReferenceTestWindow	cTestWindow;

	cNativeFactory.Init(&gcMemoryAllocator, 96, 64);
	cTestWindow.Init("Reference Test Window", &cNativeFactory);

	cTestWindow.Show();

	cTestWindow.Kill();
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

