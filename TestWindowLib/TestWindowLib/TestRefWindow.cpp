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
	CArrayChars				aszFiles;
	size					i;
	CChars*					pszFilename;
	CChars					szExpectedFilename;

	cFileUtil.RemoveDir(szDirectory);
	cFileUtil.MakeDir(szDirectory);

	cNativeFactory.Init(&gcMemoryAllocator, 96, 64, szDirectory);
	cTestWindow.Init("Reference Test Window", &cNativeFactory);

	cTestWindow.Show();

	cTestWindow.Kill();
	cNativeFactory.Kill();

	aszFiles.Init();
	cFileUtil.FindAllFiles(szDirectory, &aszFiles, false, false);
	AssertSize(11, aszFiles.NumElements());

	for (i = 1; i < aszFiles.NumElements(); i++)
	{
		pszFilename = aszFiles.Get(i);
		szExpectedFilename.Init(pszFilename);
		szExpectedFilename.Replace("Output", "Input");

		AssertFile(szExpectedFilename.Text(), pszFilename->Text());

		szExpectedFilename.Kill();
	}

	aszFiles.Kill();

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

