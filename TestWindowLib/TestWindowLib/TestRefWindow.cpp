#include "BaseLib/GlobalMemory.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/StdRandom.h"
#include "WindowLib/Window.h"
#include "WindowLib/FlowContainer.h"
#include "SupportLib/ColourARGB32.h"
#include "WinRefLib/WinRefWindowFactory.h"
#include "TestLib/AssertGeometric.h"
#include "DrawTestRefWindow.h"
#include "DrawCanvasBorder.h"
#include "TickTestRefWindow.h"
#include "DataTestRefWindow.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestRefWindowCreation(void)
{
	CWinRefWindowFactory	cNativeFactory;
	CFileUtil				cFileUtil;
	char					szDirectory[] = "Output" _FS_ "Creation";

	cFileUtil.RemoveDir(szDirectory);
	cFileUtil.MakeDir(szDirectory);

	{
		CWindow					cTestWindow;
		CArrayChars				aszFiles;
		size					i;
		CChars*					pszFilename;
		CChars					szExpectedFilename;
		CDrawTestRefWindow		cDraw;
		CTickTestRefWindow		cTick;
		SDataTestRefWindow		cData;

		cNativeFactory.Init(&gcMemoryAllocator, 96, 64, szDirectory);

		cTick.Init(&cData, 10);
		cDraw.Init(&cData);
		cTestWindow.Init("Reference Test Window", &cNativeFactory, &cTick, &cDraw);

		cTestWindow.Show();

		cTestWindow.Kill();

		aszFiles.Init();
		cFileUtil.FindAllFiles(szDirectory, &aszFiles, false, false);
		AssertSize(10, aszFiles.NumElements());

		for (i = 0; i < aszFiles.NumElements(); i++)
		{
			pszFilename = aszFiles.Get(i);
			szExpectedFilename.Init(pszFilename);
			szExpectedFilename.Replace("Output", "Input");

			AssertFile(szExpectedFilename.Text(), pszFilename->Text());

			szExpectedFilename.Kill();
		}

		aszFiles.Kill();

	}

	cNativeFactory.Kill();
	cFileUtil.RemoveDir(szDirectory);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestRefWindowCanvasBorder(void)
{
	CWinRefWindowFactory	cNativeFactory;
	CFileUtil				cFileUtil;
	char					szDirectory[] = "Output" _FS_ "CanvasBorder";

	cFileUtil.RemoveDir(szDirectory);
	cFileUtil.MakeDir(szDirectory);

	{
		CWindow					cTestWindow;
		CArrayChars				aszFiles;
		size					i;
		CChars*					pszFilename;
		CChars					szExpectedFilename;
		CDrawCanvasBorder		cDraw;
		CTickTestRefWindow		cTick;
		SDataTestRefWindow		cData;

		cNativeFactory.Init(&gcMemoryAllocator, 96, 64, szDirectory);

		cTick.Init(&cData, 1);
		cDraw.Init(Set32BitColour(1.0f, 0, 0));
		cTestWindow.Init("Reference Test Window", &cNativeFactory, &cTick, &cDraw);

		cTestWindow.Show();

		cTestWindow.Kill();

		aszFiles.Init();
		cFileUtil.FindAllFiles(szDirectory, &aszFiles, false, false);
		AssertSize(1, aszFiles.NumElements());

		for (i = 0; i < aszFiles.NumElements(); i++)
		{
			pszFilename = aszFiles.Get(i);
			szExpectedFilename.Init(pszFilename);
			szExpectedFilename.Replace("Output", "Input");

			AssertFile(szExpectedFilename.Text(), pszFilename->Text());

			szExpectedFilename.Kill();
		}

		aszFiles.Kill();
	}

	cNativeFactory.Kill();
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
	TestRefWindowCanvasBorder();

	TestStatistics();
}

