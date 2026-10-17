#include "BaseLib/GlobalMemory.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/Logger.h"
#include "StandardLib/Objects.h"
#include "WindowLib/Window.h"
#include "WindowLib/GridContainer.h"
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
struct SGridTestComponent
{
	const char*	szImage;		//NULL for a red border canvas.
	int			iColumn;
	int			iRow;
	int			iColumnSpan;
	int			iRowSpan;
	int			iWidthWeight;
	int			iHeightWeight;
	SInt32Vec2	sDesiredSize;	//-1 on an axis fills the cell on that axis.  -1, -1 on an image canvas takes the cel's size.
	SInt32Vec2	sExpectedPosition;
	SInt32Vec2	sExpectedSize;
};


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestGridContainerLayout(char* szDirectory, int32 iWidth, int32 iHeight, size uiNumComponents, SGridTestComponent* asComponents, int32 iRequiredWidth, int32 iRequiredHeight, bool bCompareFrame)
{
	CWinRefWindowFactory	cNativeFactory;
	CFileUtil				cFileUtil;

	cFileUtil.RemoveDir(szDirectory);
	cFileUtil.MakeDir(szDirectory);

	ObjectsInit();
	{
		Ptr<CWindow>			pTestWindow;
		Ptr<CGridContainer>		pGrid;
		Ptr<CCanvas>			apCanvas[8];
		Ptr<CCanvasDraw>		pDraw;
		CTickTestRefWindow		cTick;
		SDataTestRefWindow		cData;
		CColourFormatHelper		cHelper;
		SGridTestComponent*		psComponent;
		CChars					szExpectedDirectory;
		SInt32Vec2				sVec;
		CPointer				pNull;
		size					i;

		AssertTrue(uiNumComponents <= 8);

		cNativeFactory.Init(&gcMemoryAllocator, iWidth, iHeight, szDirectory);
		cTick.Init(&cData, 1);
		pTestWindow = OMalloc<CWindow>("Grid Container", &cNativeFactory, &cTick, pNull, CFT_RGB, CCO_RGB, CRGB_24bit, ARGB_None);
		pTestWindow->GetColourFormat(&cHelper);

		pGrid = OMalloc<CGridContainer>(pTestWindow);
		pTestWindow->SetContainer(pGrid);

		for (i = 0; i < uiNumComponents; i++)
		{
			psComponent = &asComponents[i];
			if (psComponent->szImage)
			{
				pDraw = OMalloc<CImageCanvasDraw>(ReadDarkForestCel(psComponent->szImage, &cHelper));
			}
			else
			{
				pDraw = OMalloc<CBorderCanvasDraw>(Set32BitColour(1.0f, 0, 0));
			}
			apCanvas[i] = OMalloc<CCanvas>(pTestWindow, pDraw);
			apCanvas[i]->SetDesiredSize(psComponent->sDesiredSize.x, psComponent->sDesiredSize.y);
			pGrid->AddComponent(apCanvas[i], psComponent->iColumn, psComponent->iRow, psComponent->iColumnSpan, psComponent->iRowSpan, psComponent->iWidthWeight, psComponent->iHeightWeight);
			pDraw = NULL;
		}

		pGrid->SetRequiredSize();
		sVec = pGrid->GetRequiredSize();
		AssertInt32Vec2(iRequiredWidth, iRequiredHeight, &sVec);

		pTestWindow->Show();

		for (i = 0; i < uiNumComponents; i++)
		{
			sVec = apCanvas[i]->GetPosition();
			AssertInt32Vec2(asComponents[i].sExpectedPosition.x, asComponents[i].sExpectedPosition.y, &sVec);
			sVec = apCanvas[i]->GetActualSize();
			AssertInt32Vec2(asComponents[i].sExpectedSize.x, asComponents[i].sExpectedSize.y, &sVec);
			apCanvas[i] = NULL;
		}

		pGrid = NULL;
		pTestWindow = NULL;

		if (bCompareFrame)
		{
			szExpectedDirectory.Init(szDirectory);
			szExpectedDirectory.Replace("Output", "Input");
			AssertDirectory(szExpectedDirectory.Text(), szDirectory);
			szExpectedDirectory.Kill();
		}
	}
	AssertTrue(ORoot()->RemoveAll());
	cNativeFactory.Kill();
	ObjectsFlush();
	ObjectsKill();

	cFileUtil.RemoveDir(szDirectory);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestGridContainerNoWeights(void)
{
	//Column 0 is 14 wide and column 1 is 6 wide, row 0 is 12 tall and row 1 is 5 tall.  With no weights nothing takes the
	//spare space so the 20 x 17 grid is centred in the 40 x 30 window, and each component is centred in its cell.
	SGridTestComponent	asComponents[4] = {
		{ NULL, 0, 0, 1, 1, 0, 0, SInt32Vec2(10, 8),  SInt32Vec2(12, 8),  SInt32Vec2(10, 8) },
		{ NULL, 1, 0, 1, 1, 0, 0, SInt32Vec2(6, 12),  SInt32Vec2(24, 6),  SInt32Vec2(6, 12) },
		{ NULL, 0, 1, 1, 1, 0, 0, SInt32Vec2(14, 5),  SInt32Vec2(10, 18), SInt32Vec2(14, 5) },
		{ NULL, 1, 1, 1, 1, 0, 0, SInt32Vec2(4, 4),   SInt32Vec2(25, 18), SInt32Vec2(4, 4) } };

	TestGridContainerLayout("Output" _FS_ "GridContainerNoWeights", 40, 30, 4, asComponents, 20, 17, false);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestGridContainerColumnWeights(void)
{
	//The 60 spare pixels are shared 1 : 2 so column 0 grows from 10 to 30 and column 1 from 0 to 40.  The fixed canvas is
	//centred in its cell and the canvas without a desired size fills its cell.
	SGridTestComponent	asComponents[2] = {
		{ NULL, 0, 0, 1, 1, 1, 0, SInt32Vec2(10, 10), SInt32Vec2(10, 0),  SInt32Vec2(10, 10) },
		{ NULL, 1, 0, 1, 1, 2, 0, SInt32Vec2(-1, -1), SInt32Vec2(30, 0),  SInt32Vec2(40, 10) } };

	TestGridContainerLayout("Output" _FS_ "GridContainerColumnWeights", 70, 10, 2, asComponents, 10, 10, false);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestGridContainerRowWeights(void)
{
	//The 22 spare pixels are shared evenly between the two rows, 8 + 11 and 0 + 11.
	SGridTestComponent	asComponents[2] = {
		{ NULL, 0, 0, 1, 1, 0, 1, SInt32Vec2(8, 8),   SInt32Vec2(0, 5),   SInt32Vec2(8, 8) },
		{ NULL, 0, 1, 1, 1, 0, 1, SInt32Vec2(8, -1),  SInt32Vec2(0, 19),  SInt32Vec2(8, 11) } };

	TestGridContainerLayout("Output" _FS_ "GridContainerRowWeights", 8, 30, 2, asComponents, 8, 8, false);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestGridContainerSpanWithoutWeights(void)
{
	//The 20 wide component spans the two 6 wide columns.  With no weights the missing 8 pixels go to the last column.
	SGridTestComponent	asComponents[3] = {
		{ NULL, 0, 0, 1, 1, 0, 0, SInt32Vec2(6, 4),   SInt32Vec2(0, 0),   SInt32Vec2(6, 4) },
		{ NULL, 1, 0, 1, 1, 0, 0, SInt32Vec2(6, 4),   SInt32Vec2(10, 0),  SInt32Vec2(6, 4) },
		{ NULL, 0, 1, 2, 1, 0, 0, SInt32Vec2(20, 4),  SInt32Vec2(0, 4),   SInt32Vec2(20, 4) } };

	TestGridContainerLayout("Output" _FS_ "GridContainerSpanWithoutWeights", 20, 8, 3, asComponents, 20, 8, false);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestGridContainerSpanWithWeights(void)
{
	//With column weights of 1 and 3 the missing 8 pixels are shared 2 and 6, making the columns 8 and 12 wide.
	SGridTestComponent	asComponents[3] = {
		{ NULL, 0, 0, 1, 1, 1, 0, SInt32Vec2(6, 4),   SInt32Vec2(1, 0),   SInt32Vec2(6, 4) },
		{ NULL, 1, 0, 1, 1, 3, 0, SInt32Vec2(6, 4),   SInt32Vec2(11, 0),  SInt32Vec2(6, 4) },
		{ NULL, 0, 1, 2, 1, 0, 0, SInt32Vec2(20, 4),  SInt32Vec2(0, 4),   SInt32Vec2(20, 4) } };

	TestGridContainerLayout("Output" _FS_ "GridContainerSpanWithWeights", 20, 8, 3, asComponents, 20, 8, false);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestGridContainerShrink(void)
{
	//The two 20 wide columns need 40 pixels.  In 30 pixels the weighted column gives up the missing 10, leaving its fixed
	//component centred over a 10 wide cell.
	SGridTestComponent	asWeightedFirst[2] = {
		{ NULL, 0, 0, 1, 1, 0, 0, SInt32Vec2(20, 4),  SInt32Vec2(0, 0),   SInt32Vec2(20, 4) },
		{ NULL, 1, 0, 1, 1, 1, 0, SInt32Vec2(20, 4),  SInt32Vec2(15, 0),  SInt32Vec2(20, 4) } };

	//In 10 pixels the weighted column gives up all 20 of its pixels and the other column then shrinks to 10.
	SGridTestComponent	asThenEverything[2] = {
		{ NULL, 0, 0, 1, 1, 0, 0, SInt32Vec2(20, 4),  SInt32Vec2(-5, 0),  SInt32Vec2(20, 4) },
		{ NULL, 1, 0, 1, 1, 1, 0, SInt32Vec2(20, 4),  SInt32Vec2(0, 0),   SInt32Vec2(20, 4) } };

	TestGridContainerLayout("Output" _FS_ "GridContainerShrinkWeightedFirst", 30, 4, 2, asWeightedFirst, 40, 4, false);
	TestGridContainerLayout("Output" _FS_ "GridContainerShrinkThenEverything", 10, 4, 2, asThenEverything, 40, 4, false);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestGridContainerOverlap(void)
{
	//Two components in the same cell are both laid out in it.
	SGridTestComponent	asComponents[2] = {
		{ NULL, 0, 0, 1, 1, 0, 0, SInt32Vec2(10, 10), SInt32Vec2(0, 0),   SInt32Vec2(10, 10) },
		{ NULL, 0, 0, 1, 1, 0, 0, SInt32Vec2(4, 4),   SInt32Vec2(3, 3),   SInt32Vec2(4, 4) } };

	TestGridContainerLayout("Output" _FS_ "GridContainerOverlap", 10, 10, 2, asComponents, 10, 10, false);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestGridContainerDarkForestImages(void)
{
	//Three images on the top row and the wolf spanning the first two columns of the bottom row.  The columns are 9, 9 and
	//10 wide and the rows 14 and 10 tall, so the 28 x 24 grid is centred at 6, 3 in the 40 x 30 window.
	SGridTestComponent	asComponents[5] = {
		{ "Pine.png",		0, 0, 1, 1, 0, 0, SInt32Vec2(-1, -1), SInt32Vec2(6, 3),   SInt32Vec2(9, 14) },
		{ "Owl.png",		1, 0, 1, 1, 0, 0, SInt32Vec2(-1, -1), SInt32Vec2(15, 5),  SInt32Vec2(9, 10) },
		{ "Moon.png",		2, 0, 1, 1, 0, 0, SInt32Vec2(-1, -1), SInt32Vec2(24, 5),  SInt32Vec2(10, 10) },
		{ "Wolf.png",		0, 1, 2, 1, 0, 0, SInt32Vec2(-1, -1), SInt32Vec2(9, 17),  SInt32Vec2(12, 10) },
		{ "Mushroom.png",	2, 1, 1, 1, 0, 0, SInt32Vec2(-1, -1), SInt32Vec2(25, 18), SInt32Vec2(8, 8) } };

	TestGridContainerLayout("Output" _FS_ "GridContainerDarkForestImages", 40, 30, 5, asComponents, 28, 24, true);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
Ptr<CCanvas> CreateGridTestCanvas(Ptr<CWindow> pWindow, int32 iWidth, int32 iHeight)
{
	Ptr<CCanvas>	pCanvas;

	pCanvas = OMalloc<CCanvas>(pWindow, OMalloc<CBorderCanvasDraw>(Set32BitColour(1.0f, 0, 0)));
	pCanvas->SetDesiredSize(iWidth, iHeight);
	return pCanvas;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestGridContainerAddAndRemove(void)
{
	CWinRefWindowFactory	cNativeFactory;
	CFileUtil				cFileUtil;
	char					szDirectory[] = "Output" _FS_ "GridContainerAddAndRemove";

	cFileUtil.RemoveDir(szDirectory);
	cFileUtil.MakeDir(szDirectory);

	ObjectsInit();
	{
		Ptr<CWindow>			pTestWindow;
		Ptr<CGridContainer>		pGrid;
		Ptr<CComponent>			pGridAsComponent;
		Ptr<CCanvas>			pCanvas0;
		Ptr<CCanvas>			pCanvas1;
		Ptr<CCanvas>			pCanvas2;
		CTickTestRefWindow		cTick;
		SDataTestRefWindow		cData;
		SLogConfig				sLogConfig;
		SInt32Vec2				sVec;
		CPointer				pNull;

		cNativeFactory.Init(&gcMemoryAllocator, 20, 10, szDirectory);
		cTick.Init(&cData, 1);
		pTestWindow = OMalloc<CWindow>("Grid Container", &cNativeFactory, &cTick, pNull, CFT_RGB, CCO_RGB, CRGB_24bit, ARGB_None);
		pGrid = OMalloc<CGridContainer>(pTestWindow);
		pTestWindow->SetContainer(pGrid);

		//A component can only be added to a grid with a cell, even through a pointer to it as a plain component.
		pCanvas0 = CreateGridTestCanvas(pTestWindow, 10, 10);
		pGridAsComponent = pGrid;
		sLogConfig = gcLogger.SetSilent();
		AssertFalse(pGrid->AddComponent(pCanvas0));
		AssertFalse(pGridAsComponent->AddComponent(pCanvas0));
		gcLogger.SetConfig(&sLogConfig);
		AssertSize(0, pGrid->NumComponents());

		//Three 10 wide components in columns 0, 1 and 2.  Removing the middle one takes its cell with it, so the others stay
		//in their own cells: column 1 is then empty and the 20 wide grid exactly fills the window.
		pCanvas1 = CreateGridTestCanvas(pTestWindow, 10, 10);
		pCanvas2 = CreateGridTestCanvas(pTestWindow, 10, 10);
		AssertTrue(pGrid->AddComponent(pCanvas0, 0, 0));
		AssertTrue(pGrid->AddComponent(pCanvas1, 1, 0));
		AssertTrue(pGrid->AddComponent(pCanvas2, 2, 0));
		AssertSize(3, pGrid->NumComponents());

		AssertTrue(pGridAsComponent->RemoveComponent(pCanvas1));
		AssertSize(2, pGrid->NumComponents());
		AssertFalse(pGrid->RemoveComponent(pCanvas1));

		pTestWindow->Show();
		sVec = pCanvas0->GetPosition();
		AssertInt32Vec2(0, 0, &sVec);
		sVec = pCanvas2->GetPosition();
		AssertInt32Vec2(10, 0, &sVec);

		//Removing everything removes every cell, so a component added afterwards is laid out on its own.  In column 1 with
		//an empty column 0 the 10 wide grid is centred in the window.
		AssertTrue(pGrid->RemoveAllComponents());
		AssertSize(0, pGrid->NumComponents());
		AssertTrue(pGrid->AddComponent(pCanvas1, 1, 0));
		pTestWindow->Layout();
		sVec = pCanvas1->GetPosition();
		AssertInt32Vec2(5, 0, &sVec);

		pCanvas0 = NULL;
		pCanvas1 = NULL;
		pCanvas2 = NULL;
		pGridAsComponent = NULL;
		pGrid = NULL;
		pTestWindow = NULL;
	}
	AssertTrue(ORoot()->RemoveAll());
	cNativeFactory.Kill();
	ObjectsFlush();
	ObjectsKill();

	cFileUtil.RemoveDir(szDirectory);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestGridContainer(void)
{
	BeginTests();

	TestGridContainerNoWeights();
	TestGridContainerColumnWeights();
	TestGridContainerRowWeights();
	TestGridContainerSpanWithoutWeights();
	TestGridContainerSpanWithWeights();
	TestGridContainerShrink();
	TestGridContainerOverlap();
	TestGridContainerDarkForestImages();
	TestGridContainerAddAndRemove();

	TestStatistics();
}

