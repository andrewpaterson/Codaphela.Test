#include "BaseLib/GlobalMemory.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/StdRandom.h"
#include "WindowLib/Window.h"
#include "WindowLib/FlowContainer.h"
#include "SupportLib/ColourARGB32.h"
#include "WinRefLib/WinRefWindowFactory.h"
#include "TestLib/AssertGeometric.h"
#include "TestRefWindowCanvasDraw.h"
#include "BorderCanvasDraw.h"
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

	ObjectsInit();
	{
		Ptr<CWindow>					pTestWindow;
		Ptr<CTestRefWindowCanvasDraw>	pDraw;
		Ptr<CTickTestRefWindow>			pTick;
		SDataTestRefWindow				cData;
		Ptr<CRoot>						pRoot;
		CArrayChars						aszFiles;
		size							i;
		CChars*							pszFilename;
		CChars							szExpectedFilename;

		cNativeFactory.Init(&gcMemoryAllocator, 96, 64, szDirectory);

		pRoot = ORoot();

		pTick = OMalloc<CTickTestRefWindow>(&cData, 10);
		pDraw = OMalloc<CTestRefWindowCanvasDraw>(&cData);
		pTestWindow = OMalloc<CWindow>("Reference Test Window", &cNativeFactory, pTick, pDraw);

		pRoot->Add(pTestWindow);

		pTestWindow->Show();

		pRoot->RemoveAll();
		pTestWindow = NULL;
		pDraw = NULL;
		pTick = NULL;

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

		cNativeFactory.Kill();
	}
	ObjectsFlush();
	ObjectsKill();

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

	ObjectsInit();
	{
		Ptr<CWindow>					pTestWindow;
		CArrayChars						aszFiles;
		size							i;
		CChars*							pszFilename;
		CChars							szExpectedFilename;
		Ptr<CBorderCanvasDraw>			pDraw;
		Ptr<CTickTestRefWindow>			pTick;
		SDataTestRefWindow				cData;
		Ptr<CRoot>						pRoot;

		cNativeFactory.Init(&gcMemoryAllocator, 96, 64, szDirectory);

		pRoot = ORoot();

		pTick = OMalloc<CTickTestRefWindow>(&cData, 1);
		pDraw = OMalloc<CBorderCanvasDraw>(Set32BitColour(1.0f, 0, 0));
		pTestWindow = OMalloc<CWindow>("Reference Test Window", &cNativeFactory, pTick, pDraw);

		pTestWindow->Show();

		pTestWindow->Kill();

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
		cNativeFactory.Kill();
	}
	ObjectsFlush();
	ObjectsKill();

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

