#include "BaseLib/GlobalMemory.h"
#include "BaseLib/FileUtil.h"
#include "StandardLib/Objects.h"
#include "WindowLib/Window.h"
#include "WindowLib/FillContainer.h"
#include "WinRefLib/WinRefWindowFactory.h"
#include "TestLib/AssertGeometric.h"
#include "BorderCanvasDraw.h"
#include "TickTestRefWindow.h"
#include "DataTestRefWindow.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertFillContainerObjectsRemoved(void)
{
	AssertSize(0, gcObjects.NumFreeObjects());
	AssertTrue(ORoot()->RemoveAll());
	AssertSize(2, gcObjects.NumMemoryIndexes());
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFillContainerPositions(char* szDirectory, int32 iWidth, int32 iHeight, EFillContainerSplit eSplit, int32 iSpacing, EContainerStyleHorizontal eH, EContainerStyleVertical eV, int* paiInsets, size uiNumComponents, SInt32Vec2* asDesiredSizes, SInt32Vec2* asExpectedPositions, SInt32Vec2* asExpectedSizes)
{
	CWinRefWindowFactory	cNativeFactory;
	CFileUtil				cFileUtil;

	cFileUtil.RemoveDir(szDirectory);
	cFileUtil.MakeDir(szDirectory);

	{
		Ptr<CWindow>			pTestWindow;
		size					i;
		Ptr<CCanvas>			apCanvas[3];
		Ptr<CBorderCanvasDraw>	pDraw;
		CTickTestRefWindow		cTick;
		SDataTestRefWindow		cData;
		Ptr<CFillContainer>		pFill;
		SInsets					sInsets;
		SInt32Vec2				sVec;
		CPointer				pNull;

		cNativeFactory.Init(&gcMemoryAllocator, iWidth, iHeight, szDirectory);

		cTick.Init(&cData, 1);
		pTestWindow = OMalloc<CWindow>("Reference Test Window", &cNativeFactory, &cTick, pNull, CFT_RGB, CCO_RGB, CRGB_24bit, ARGB_None);

		pFill = OMalloc<CFillContainer>(pTestWindow);
		pFill->SetFillStyle(eH, eV);
		pFill->SetSplit(eSplit, iSpacing);
		if (paiInsets)
		{
			sInsets.Init(paiInsets);
			pFill->SetInsets(&sInsets);
		}
		pTestWindow->SetContainer(pFill);

		for (i = 0; i < uiNumComponents; i++)
		{
			pDraw = OMalloc<CBorderCanvasDraw>(Set32BitColour(1.0f, 0, 0));
			apCanvas[i] = OMalloc<CCanvas>(pTestWindow, pDraw);
			pFill->AddComponent(apCanvas[i]);
			apCanvas[i]->SetDesiredSize(asDesiredSizes[i].x, asDesiredSizes[i].y);
		}
		pDraw = NULL;

		pTestWindow->Show();

		for (i = 0; i < uiNumComponents; i++)
		{
			sVec = apCanvas[i]->GetPosition();
			AssertInt32Vec2(asExpectedPositions[i].x, asExpectedPositions[i].y, &sVec);
			sVec = apCanvas[i]->GetActualSize();
			AssertInt32Vec2(asExpectedSizes[i].x, asExpectedSizes[i].y, &sVec);
			apCanvas[i] = NULL;
		}

		pTestWindow = NULL;
		pFill = NULL;
	}

	AssertFillContainerObjectsRemoved();

	cNativeFactory.Kill();
	cFileUtil.RemoveDir(szDirectory);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFillContainerOverlayStretchInsets(void)
{
	int			aiInsets[4] = { 2, 3, 4, 5 };  //Top, Right, Bottom, Left.
	SInt32Vec2	asDesired[1] = { SInt32Vec2(-1, -1) };
	SInt32Vec2	asPosition[1] = { SInt32Vec2(5, 2) };
	SInt32Vec2	asSize[1] = { SInt32Vec2(88, 24) };

	TestFillContainerPositions("Output" _FS_ "FillContainerOverlayStretchInsets", 96, 30, FCS_Overlay, 0, CSH_Stretch, CSV_Stretch, aiInsets, 1, asDesired, asPosition, asSize);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFillContainerOverlayCenterBottom(void)
{
	SInt32Vec2	asDesired[1] = { SInt32Vec2(10, 10) };
	SInt32Vec2	asPosition[1] = { SInt32Vec2(43, 20) };

	TestFillContainerPositions("Output" _FS_ "FillContainerOverlayCenterBottom", 96, 30, FCS_Overlay, 0, CSH_Center, CSV_Bottom, NULL, 1, asDesired, asPosition, asDesired);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFillContainerOverlayPartialDesiredSize(void)
{
	SInt32Vec2	asDesired[1] = { SInt32Vec2(10, -1) };
	SInt32Vec2	asPosition[1] = { SInt32Vec2(0, 0) };
	SInt32Vec2	asSize[1] = { SInt32Vec2(10, 30) };

	TestFillContainerPositions("Output" _FS_ "FillContainerOverlayPartialDesiredSize", 96, 30, FCS_Overlay, 0, CSH_Left, CSV_Top, NULL, 1, asDesired, asPosition, asSize);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFillContainerOverlayLargeInsets(void)
{
	int			aiInsets[4] = { 20, 0, 20, 0 };
	SInt32Vec2	asDesired[1] = { SInt32Vec2(-1, -1) };
	SInt32Vec2	asPosition[1] = { SInt32Vec2(0, 20) };
	SInt32Vec2	asSize[1] = { SInt32Vec2(96, 0) };

	TestFillContainerPositions("Output" _FS_ "FillContainerOverlayLargeInsets", 96, 30, FCS_Overlay, 0, CSH_Stretch, CSV_Stretch, aiInsets, 1, asDesired, asPosition, asSize);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFillContainerHorizontalSplit(void)
{
	SInt32Vec2	asDesired[3] = { SInt32Vec2(10, 10), SInt32Vec2(20, 20), SInt32Vec2(-1, -1) };
	SInt32Vec2	asPosition[3] = { SInt32Vec2(0, 0), SInt32Vec2(33, 0), SInt32Vec2(66, 0) };
	SInt32Vec2	asSize[3] = { SInt32Vec2(31, 30), SInt32Vec2(31, 30), SInt32Vec2(30, 30) };

	TestFillContainerPositions("Output" _FS_ "FillContainerHorizontalSplit", 96, 30, FCS_Horizontal, 2, CSH_Stretch, CSV_Stretch, NULL, 3, asDesired, asPosition, asSize);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFillContainerVerticalSplitCenter(void)
{
	SInt32Vec2	asDesired[2] = { SInt32Vec2(10, 10), SInt32Vec2(10, 10) };
	SInt32Vec2	asPosition[2] = { SInt32Vec2(43, 0), SInt32Vec2(43, 15) };
	SInt32Vec2	asSize[2] = { SInt32Vec2(10, 15), SInt32Vec2(10, 15) };

	TestFillContainerPositions("Output" _FS_ "FillContainerVerticalSplitCenter", 96, 30, FCS_Vertical, 0, CSH_Center, CSV_Stretch, NULL, 2, asDesired, asPosition, asSize);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFillContainerRequiredSize(void)
{
	CWinRefWindowFactory	cNativeFactory;
	CFileUtil				cFileUtil;
	char					szDirectory[] = "Output" _FS_ "FillContainerRequiredSize";

	cFileUtil.RemoveDir(szDirectory);
	cFileUtil.MakeDir(szDirectory);

	{
		Ptr<CWindow>			pTestWindow;
		Ptr<CCanvas>			pCanvas;
		Ptr<CBorderCanvasDraw>	pDraw;
		CTickTestRefWindow		cTick;
		SDataTestRefWindow		cData;
		Ptr<CFillContainer>		pFill;
		SInsets					sInsets;
		int						aiInsets[4] = { 1, 2, 3, 4 };
		SInt32Vec2				sVec;
		CPointer				pNull;

		cNativeFactory.Init(&gcMemoryAllocator, 96, 30, szDirectory);

		cTick.Init(&cData, 1);
		pTestWindow = OMalloc<CWindow>("Reference Test Window", &cNativeFactory, &cTick, pNull, CFT_RGB, CCO_RGB, CRGB_24bit, ARGB_None);

		pFill = OMalloc<CFillContainer>(pTestWindow);
		pTestWindow->SetContainer(pFill);

		pDraw = OMalloc<CBorderCanvasDraw>(Set32BitColour(1.0f, 0, 0));
		pCanvas = OMalloc<CCanvas>(pTestWindow, pDraw);
		pCanvas->SetDesiredSize(10, 5);
		pFill->AddComponent(pCanvas);
		pDraw = OMalloc<CBorderCanvasDraw>(Set32BitColour(0, 1.0f, 0));
		pCanvas = OMalloc<CCanvas>(pTestWindow, pDraw);
		pCanvas->SetDesiredSize(20, 8);
		pFill->AddComponent(pCanvas);
		pDraw = OMalloc<CBorderCanvasDraw>(Set32BitColour(0, 0, 1.0f));
		pCanvas = OMalloc<CCanvas>(pTestWindow, pDraw);
		pCanvas->SetDesiredSize(6, 12);
		pFill->AddComponent(pCanvas);
		pCanvas = NULL;
		pDraw = NULL;

		pFill->SetRequiredSize();
		sVec = pFill->GetRequiredSize();
		AssertInt32Vec2(20, 12, &sVec);

		pFill->SetSplit(FCS_Horizontal, 2);
		pFill->SetRequiredSize();
		sVec = pFill->GetRequiredSize();
		AssertInt32Vec2(64, 12, &sVec);

		pFill->SetSplit(FCS_Vertical, 2);
		sInsets.Init(aiInsets);
		pFill->SetInsets(&sInsets);
		pFill->SetRequiredSize();
		sVec = pFill->GetRequiredSize();
		AssertInt32Vec2(26, 44, &sVec);

		pTestWindow = NULL;
		pFill = NULL;
	}

	AssertFillContainerObjectsRemoved();

	cNativeFactory.Kill();
	cFileUtil.RemoveDir(szDirectory);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFillContainer(void)
{
	BeginTests();
	ObjectsInit();

	TestFillContainerOverlayStretchInsets();
	TestFillContainerOverlayCenterBottom();
	TestFillContainerOverlayPartialDesiredSize();
	TestFillContainerOverlayLargeInsets();
	TestFillContainerHorizontalSplit();
	TestFillContainerVerticalSplitCenter();
	TestFillContainerRequiredSize();

	ObjectsFlush();
	ObjectsKill();
	TestStatistics();
}

