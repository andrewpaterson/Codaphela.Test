#include "BaseLib/GlobalMemory.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/StdRandom.h"
#include "StandardLib/Objects.h"
#include "WindowLib/Window.h"
#include "WindowLib/FillContainer.h"
#include "WinRefLib/WinRefWindowFactory.h"
#include "TestLib/AssertGeometric.h"
#include "DrawTestRefWindow.h"
#include "DrawCanvasBorder.h"
#include "TickTestRefWindow.h"
#include "DataTestRefWindow.h"


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
void TestCanvasWriteImage(void)
{
	CWinRefWindowFactory	cNativeFactory;
	CFileUtil				cFileUtil;
	char					szDirectory[] = "Output" _FS_ "FlowContainerRightCenteredContinue";

	cFileUtil.RemoveDir(szDirectory);
	cFileUtil.MakeDir(szDirectory);

	{
		Ptr<CWindow>							pTestWindow;
		Ptr<CCanvas>							pCanvas;
		Ptr<CDrawCanvasBorder>					pDraw;
		CTickTestRefWindow						cTick;
		SDataTestRefWindow						cData;
		Ptr<CFillContainer>						pFill;
		SContainerBounds						sBounds;
		CRandom									cRandom;
		CPointer								pNull;

		cNativeFactory.Init(&gcMemoryAllocator, 96, 24, szDirectory);

		cTick.Init(&cData, 1);
		pTestWindow = OMalloc<CWindow>("Reference Test Window", &cNativeFactory, &cTick, pNull);

		pFill = OMalloc<CFillContainer>(pTestWindow);
		pTestWindow->SetContainer(pFill);
	}
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
void TestCanvas(void)
{
	BeginTests();

	TestCanvasWriteImage();

	TestStatistics();
}

