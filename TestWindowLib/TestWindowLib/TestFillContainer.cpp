#include "BaseLib/GlobalMemory.h"
#include "BaseLib/FileUtil.h"
#include "StandardLib/Objects.h"
#include "WindowLib/Window.h"
#include "WindowLib/FillContainer.h"
#include "WindowLib/ImageCanvasDraw.h"
#include "WinRefLib/WinRefWindowFactory.h"
#include "TestLib/AssertGeometric.h"
#include "TestLib/AssertFile.h"
#include "BorderCanvasDraw.h"
#include "TickTestRefWindow.h"
#include "DataTestRefWindow.h"
#include "DarkForest.h"


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
void TestFillContainerImageCanvasDesiredSize(void)
{
	CWinRefWindowFactory	cNativeFactory;
	CFileUtil				cFileUtil;
	char					szDirectory[] = "Output" _FS_ "FillContainerImageCanvasDesiredSize";

	cFileUtil.RemoveDir(szDirectory);
	cFileUtil.MakeDir(szDirectory);

	{
		Ptr<CWindow>			pTestWindow;
		Ptr<CCanvas>			pCanvas;
		Ptr<CImageCanvasDraw>	pDraw;
		Ptr<CImage>				pImage;
		Ptr<CImageCel>			pCel;
		CTickTestRefWindow		cTick;
		SDataTestRefWindow		cData;
		Ptr<CFillContainer>		pFill;
		SInt32Vec2				sVec;
		CPointer				pNull;

		cNativeFactory.Init(&gcMemoryAllocator, 96, 30, szDirectory);

		cTick.Init(&cData, 1);
		pTestWindow = OMalloc<CWindow>("Reference Test Window", &cNativeFactory, &cTick, pNull, CFT_RGB, CCO_RGB, CRGB_24bit, ARGB_None);

		pFill = OMalloc<CFillContainer>(pTestWindow);
		pFill->SetFillStyle(CSH_Left, CSV_Top);
		pTestWindow->SetContainer(pFill);

		pImage = OMalloc<CImage>(12, 7, CFT_RGB, CCO_RGB, CRGB_24bit, ARGB_None);
		pCel = OMalloc<CImageCel>(pImage);
		pDraw = OMalloc<CImageCanvasDraw>(pCel);
		pCanvas = OMalloc<CCanvas>(pTestWindow, pDraw);
		pFill->AddComponent(pCanvas);

		sVec = pDraw->GetDesiredSize();
		AssertInt32Vec2(12, 7, &sVec);
		sVec = pCanvas->GetDesiredSize();
		AssertInt32Vec2(12, 7, &sVec);

		pTestWindow->Show();
		sVec = pCanvas->GetActualSize();
		AssertInt32Vec2(12, 7, &sVec);

		pCanvas->SetDesiredSize(20, 10);
		sVec = pCanvas->GetDesiredSize();
		AssertInt32Vec2(20, 10, &sVec);

		pTestWindow->Layout();
		sVec = pCanvas->GetActualSize();
		AssertInt32Vec2(20, 10, &sVec);

		pCanvas->SetDesiredSize(-1, -1);
		sVec = pCanvas->GetDesiredSize();
		AssertInt32Vec2(12, 7, &sVec);

		pTestWindow = NULL;
		pFill = NULL;
		pCanvas = NULL;
		pDraw = NULL;
		pCel = NULL;
		pImage = NULL;
	}

	AssertFillContainerObjectsRemoved();

	cNativeFactory.Kill();
	cFileUtil.RemoveDir(szDirectory);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFillContainerDarkForest(char* szDirectory, int32 iWidth, int32 iHeight, EFillContainerSplit eSplit, int32 iSpacing, EContainerStyleHorizontal eH, EContainerStyleVertical eV, int* paiInsets, size uiNumComponents, SDarkForestComponent* asComponents, SInt32Vec2* asExpectedPositions)
{
	CWinRefWindowFactory	cNativeFactory;
	CFileUtil				cFileUtil;

	cFileUtil.RemoveDir(szDirectory);
	cFileUtil.MakeDir(szDirectory);

	{
		Ptr<CWindow>			pTestWindow;
		size					i;
		CChars					szExpectedDirectory;
		Ptr<CCanvas>			apCanvas[16];
		Ptr<CCanvasDraw>		pDraw;
		CTickTestRefWindow		cTick;
		SDataTestRefWindow		cData;
		Ptr<CFillContainer>		pFill;
		SInsets					sInsets;
		CColourFormatHelper		cHelper;
		SDarkForestComponent*	psComponent;
		SInt32Vec2				sDesired;
		SInt32Vec2				sVec;
		CPointer				pNull;

		AssertTrue(uiNumComponents <= 16);

		cNativeFactory.Init(&gcMemoryAllocator, iWidth, iHeight, szDirectory);

		cTick.Init(&cData, 1);
		pTestWindow = OMalloc<CWindow>("Reference Test Window", &cNativeFactory, &cTick, pNull, CFT_RGB, CCO_RGB, CRGB_24bit, ARGB_None);
		pTestWindow->GetColourFormat(&cHelper);

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
			psComponent = &asComponents[i];
			pDraw = CreateDarkForestDraw(psComponent, &cHelper);
			apCanvas[i] = OMalloc<CCanvas>(pTestWindow, pDraw);
			apCanvas[i]->SetDesiredSize(psComponent->sDesiredSize.x, psComponent->sDesiredSize.y);
			pFill->AddComponent(apCanvas[i]);
			pDraw = NULL;
		}

		pTestWindow->Show();

		//Where an axis has a desired size and isn't stretched the canvas must have been laid out at exactly that size.
		for (i = 0; i < uiNumComponents; i++)
		{
			sDesired = apCanvas[i]->GetDesiredSize();
			sVec = apCanvas[i]->GetActualSize();
			if ((sDesired.x > 0) && (eH != CSH_Stretch))
			{
				AssertInt(sDesired.x, sVec.x);
			}
			if ((sDesired.y > 0) && (eV != CSV_Stretch))
			{
				AssertInt(sDesired.y, sVec.y);
			}
			if (asExpectedPositions)
			{
				sVec = apCanvas[i]->GetPosition();
				AssertInt32Vec2(asExpectedPositions[i].x, asExpectedPositions[i].y, &sVec);
			}
			apCanvas[i] = NULL;
		}

		pTestWindow = NULL;
		pFill = NULL;

		szExpectedDirectory.Init(szDirectory);
		szExpectedDirectory.Replace("Output", "Input");

		AssertDirectory(szExpectedDirectory.Text(), szDirectory);
		szExpectedDirectory.Kill();
	}

	AssertFillContainerObjectsRemoved();

	cNativeFactory.Kill();
	cFileUtil.RemoveDir(szDirectory);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFillContainerDarkForestImagesHorizontalCenter(void)
{
	SDarkForestComponent	asComponents[5] = {
		{ "Pine.png",		SInt32Vec2(-1, -1), 0 },
		{ "Owl.png",		SInt32Vec2(-1, -1), 0 },
		{ "Moon.png",		SInt32Vec2(-1, -1), 0 },
		{ "Mushroom.png",	SInt32Vec2(-1, -1), 0 },
		{ "Wolf.png",		SInt32Vec2(-1, -1), 0 } };

	TestFillContainerDarkForest("Output" _FS_ "FillContainerDarkForestImagesHorizontalCenter", 72, 18, FCS_Horizontal, 1, CSH_Center, CSV_Center, NULL, 5, asComponents, NULL);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFillContainerDarkForestImagesVerticalRightBottomInsets(void)
{
	int						aiInsets[4] = { 1, 2, 3, 4 };  //Top, Right, Bottom, Left.
	SDarkForestComponent	asComponents[4] = {
		{ "Bat.png",		SInt32Vec2(-1, -1), 0 },
		{ "Stump.png",		SInt32Vec2(-1, -1), 0 },
		{ "Fireflies.png",	SInt32Vec2(-1, -1), 0 },
		{ "Fern.png",		SInt32Vec2(-1, -1), 0 } };

	TestFillContainerDarkForest("Output" _FS_ "FillContainerDarkForestImagesVerticalRightBottomInsets", 20, 64, FCS_Vertical, 2, CSH_Right, CSV_Bottom, aiInsets, 4, asComponents, NULL);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFillContainerDarkForestImagesVerticalStretch(void)
{
	//Stretched image canvases are larger than their cels so each cel sits in the top left of its slot.
	SDarkForestComponent	asComponents[3] = {
		{ "Mushroom.png",	SInt32Vec2(-1, -1), 0 },
		{ "Owl.png",		SInt32Vec2(-1, -1), 0 },
		{ "Stump.png",		SInt32Vec2(-1, -1), 0 } };

	TestFillContainerDarkForest("Output" _FS_ "FillContainerDarkForestImagesVerticalStretch", 16, 40, FCS_Vertical, 1, CSH_Stretch, CSV_Stretch, NULL, 3, asComponents, NULL);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFillContainerDarkForestMixedHorizontalTop(void)
{
	//Border canvases without a desired size fill their slots and so show where each slot is.
	SDarkForestComponent	asComponents[6] = {
		{ "Owl.png",		SInt32Vec2(-1, -1), 0 },
		{ NULL,				SInt32Vec2(-1, -1), Set32BitColour((uint8)60, 110, 60) },
		{ "Wolf.png",		SInt32Vec2(-1, -1), 0 },
		{ NULL,				SInt32Vec2(-1, -1), Set32BitColour((uint8)150, 30, 30) },
		{ "Pine.png",		SInt32Vec2(-1, -1), 0 },
		{ NULL,				SInt32Vec2(-1, 8),	Set32BitColour((uint8)236, 200, 70) } };

	TestFillContainerDarkForest("Output" _FS_ "FillContainerDarkForestMixedHorizontalTop", 84, 18, FCS_Horizontal, 2, CSH_Center, CSV_Top, NULL, 6, asComponents, NULL);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFillContainerDarkForestMixedOverlayCenter(void)
{
	//The border fills the inset area and the moon is drawn centred on top of it.
	int						aiInsets[4] = { 1, 1, 1, 1 };  //Top, Right, Bottom, Left.
	SDarkForestComponent	asComponents[2] = {
		{ NULL,				SInt32Vec2(-1, -1), Set32BitColour((uint8)78, 60, 96) },
		{ "Moon.png",		SInt32Vec2(-1, -1), 0 } };

	TestFillContainerDarkForest("Output" _FS_ "FillContainerDarkForestMixedOverlayCenter", 18, 16, FCS_Overlay, 0, CSH_Center, CSV_Center, aiInsets, 2, asComponents, NULL);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFillContainerDarkForestCenterTooSmall(void)
{
	//Each 20x24 slot is larger than its cel so the cel is centred with space all around.
	SDarkForestComponent	asComponents[3] = {
		{ "Mushroom.png",	SInt32Vec2(-1, -1), 0 },
		{ "Fireflies.png",	SInt32Vec2(-1, -1), 0 },
		{ "Stump.png",		SInt32Vec2(-1, -1), 0 } };
	SInt32Vec2				asPosition[3] = { SInt32Vec2(6, 8), SInt32Vec2(27, 7), SInt32Vec2(45, 9) };

	TestFillContainerDarkForest("Output" _FS_ "FillContainerDarkForestCenterTooSmall", 60, 24, FCS_Horizontal, 0, CSH_Center, CSV_Center, NULL, 3, asComponents, asPosition);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestFillContainerDarkForestCenterTooLarge(void)
{
	//The 4 pixel insets leave a 32x8 area split into slots 10, 9 and 9 wide.  Every cel is at least as large as its slot
	//so it is centred over the slot and spills into the insets and spacing.  An odd overflow puts the extra pixel on the right or bottom.
	int						aiInsets[4] = { 4, 4, 4, 4 };  //Top, Right, Bottom, Left.
	SDarkForestComponent	asComponents[3] = {
		{ "Wolf.png",		SInt32Vec2(-1, -1), 0 },
		{ "Pine.png",		SInt32Vec2(-1, -1), 0 },
		{ "Moon.png",		SInt32Vec2(-1, -1), 0 } };
	SInt32Vec2				asPosition[3] = { SInt32Vec2(3, 3), SInt32Vec2(16, 1), SInt32Vec2(27, 3) };

	TestFillContainerDarkForest("Output" _FS_ "FillContainerDarkForestCenterTooLarge", 40, 16, FCS_Horizontal, 2, CSH_Center, CSV_Center, aiInsets, 3, asComponents, asPosition);
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
	TestFillContainerImageCanvasDesiredSize();
	TestFillContainerDarkForestImagesHorizontalCenter();
	TestFillContainerDarkForestImagesVerticalRightBottomInsets();
	TestFillContainerDarkForestImagesVerticalStretch();
	TestFillContainerDarkForestMixedHorizontalTop();
	TestFillContainerDarkForestMixedOverlayCenter();
	TestFillContainerDarkForestCenterTooSmall();
	TestFillContainerDarkForestCenterTooLarge();

	ObjectsFlush();
	ObjectsKill();
	TestStatistics();
}

