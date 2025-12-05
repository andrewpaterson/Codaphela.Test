#include "BaseLib/GlobalMemory.h"
#include "BaseLib/FileUtil.h"
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
		CChars* pszFilename;
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
void TestRefWindowFlowContainer(void)
{
	CWinRefWindowFactory	cNativeFactory;
	CFileUtil				cFileUtil;
	char					szDirectory[] = "Output" _FS_ "FlowContainer";

	cFileUtil.RemoveDir(szDirectory);
	cFileUtil.MakeDir(szDirectory);

	{
		CWindow					cTestWindow;
		CArrayChars				aszFiles;
		size					i;
		CChars*					pszFilename;
		CChars					szExpectedFilename;
		CCanvas					cCanvas1;
		CCanvas					cCanvas2;
		CCanvas					cCanvas3;
		CDrawCanvasBorder		cDraw1;
		CDrawCanvasBorder		cDraw2;
		CDrawCanvasBorder		cDraw3;
		CTickTestRefWindow		cTick;
		SDataTestRefWindow		cData;
		CFlowContainer			cFlow;
		SContainerBounds		sBounds;

		cNativeFactory.Init(&gcMemoryAllocator, 96, 64, szDirectory);

		cTick.Init(&cData, 1);
		cTestWindow.Init("Reference Test Window", &cNativeFactory, &cTick, NULL);

		cDraw1.Init(Set32BitColour(1.0f, 0, 0));
		cCanvas1.Init(&cTestWindow, CF_R8G8B8, &cDraw1);
		cDraw2.Init(Set32BitColour(0, 1.0f, 0));
		cCanvas2.Init(&cTestWindow, CF_R8G8B8, &cDraw2);
		cDraw3.Init(Set32BitColour(0, 0, 1.0f));
		cCanvas3.Init(&cTestWindow, CF_R8G8B8, &cDraw3);

		cFlow.Init(&cTestWindow);
		cTestWindow.SetContainer(&cFlow);

		cFlow.AddComponent(&cCanvas1);
		cFlow.AddComponent(&cCanvas2);
		cFlow.AddComponent(&cCanvas3);
		cCanvas1.SetDesiredSize(10, 10);
		cCanvas2.SetDesiredSize(20, 20);
		cCanvas3.SetDesiredSize(5, 16);

		AssertSize(3, cFlow.NumComponents());
		AssertInt2(0, 0, &cCanvas1.GetActualSize());

		cTestWindow.Show();

		AssertInt2(10, 10, &cCanvas1.GetActualSize());
		AssertInt2(20, 20, &cCanvas2.GetActualSize());
		AssertInt2(5, 16, &cCanvas3.GetActualSize());
		AssertInt2(0, 0, &cCanvas1.GetPosition());
		AssertInt2(10, 0, &cCanvas2.GetPosition());
		AssertInt2(30, 0, &cCanvas3.GetPosition());

		cCanvas1.GetContainerBounds(&sBounds);

		cTestWindow.Kill();

		aszFiles.Init();
		cFileUtil.FindAllFiles(szDirectory, &aszFiles, false, false);
		AssertSize(1, aszFiles.NumElements());

		for (i = 1; i < aszFiles.NumElements(); i++)
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
	TestRefWindowFlowContainer();

	TestStatistics();
}

