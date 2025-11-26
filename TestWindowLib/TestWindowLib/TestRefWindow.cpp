#include "BaseLib/GlobalMemory.h"
#include "BaseLib/FileUtil.h"
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
	CFileUtil				cFileUtil;
	char					szDirectory[] = "Output" _FS_ "Creation";

	cFileUtil.RemoveDir(szDirectory);
	cFileUtil.MakeDir(szDirectory);

	cNativeFactory.Init(&gcMemoryAllocator, 96, 64, szDirectory);
	cTestWindow.Init("Reference Test Window", &cNativeFactory);

	cTestWindow.Show();

	cTestWindow.Kill();

	cFileUtil.RemoveDir(szDirectory);
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

