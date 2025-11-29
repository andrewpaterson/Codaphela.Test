#include "BaseLib/GlobalMemory.h"
#include "BaseLib/FileUtil.h"
#include "WinRefLib/WinRefWindowFactory.h"
#include "WindowLib/Window.h"
#include "TestLib/Assert.h"
#include "DrawTestRefWindow.h"
#include "TickTestRefWindow.h"
#include "DataTestRefWindow.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestRefWindowCreation(void)
{
	CWinRefWindowFactory	cNativeFactory;

	{
		CWindow					cTestWindow;
		CFileUtil				cFileUtil;
		char					szDirectory[] = "Output" _FS_ "Creation";
		CArrayChars				aszFiles;
		size					i;
		CChars* pszFilename;
		CChars					szExpectedFilename;
		CDrawTestRefWindow		cDraw;
		CTickTestRefWindow		cTick;
		SDataTestRefWindow		cData;

		cFileUtil.RemoveDir(szDirectory);
		cFileUtil.MakeDir(szDirectory);

		cNativeFactory.Init(&gcMemoryAllocator, 96, 64, szDirectory);

		cTick.Init(&cData);
		cDraw.Init(&cData);
		cTestWindow.Init("Reference Test Window", &cNativeFactory, &cTick, &cDraw);

		cTestWindow.Show();

		cTestWindow.Kill();

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

	cNativeFactory.Kill();
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

