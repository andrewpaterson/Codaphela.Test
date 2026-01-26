#include "BaseLib/GlobalMemory.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/StdRandom.h"
#include "StandardLib/Objects.h"
#include "WindowLib/Window.h"
#include "WindowLib/FlowContainer.h"
#include "WindowLib/Text.h"
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
void TestText1(void)
{
	CWinRefWindowFactory	cNativeFactory;
	CFileUtil				cFileUtil;
	char					szDirectory[] = "Output" _FS_ "Text1";

	cFileUtil.RemoveDir(szDirectory);
	cFileUtil.MakeDir(szDirectory);

	{
		CWindow					cTestWindow;
		CArrayChars				aszFiles;
		size					i;
		CChars*					pszFilename;
		CChars					szExpectedFilename;
		CTickTestRefWindow		cTick;
		SDataTestRefWindow		cData;
		CFlowContainer			cFlow;
		SContainerBounds		sBounds;
		CText					cText;

		cNativeFactory.Init(&gcMemoryAllocator, 96, 30, szDirectory);

		cTick.Init(&cData, 1);
		cTestWindow.Init("Reference Test Window", &cNativeFactory, &cTick, NULL);

		cText.Init(&cTestWindow);

		cFlow.Init(&cTestWindow);
		cFlow.SetFlowStyle(CSD_Right, CSW_Continue, CSV_Top);
		cTestWindow.SetContainer(&cFlow);

		cFlow.AddComponent(&cText);

		AssertSize(3, cFlow.NumComponents());

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
void TestText(void)
{
	BeginTests();

	TestText1();

	TestStatistics();
}

