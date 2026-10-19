#include "BaseLib/GlobalMemory.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/StdRandom.h"
#include "StandardLib/Objects.h"
#include "WindowLib/Window.h"
#include "WindowLib/BorderLayoutHelper.h"
#include "SupportLib/ImageAccessorCreator.h"
#include "SupportLib/ImageColourConverter.h"
#include "WindowLib/ImageCanvasDraw.h"
#include "WindowLib/ClearCanvasDraw.h"
#include "WinRefLib/WinRefWindowFactory.h"
#include "TestLib/AssertGeometric.h"
#include "TestLib/AssertFile.h"
#include "BorderCanvasDraw.h"
#include "TickTestRefWindow.h"
#include "DataTestRefWindow.h"
#include "DarkForest.h"
#include "SpaceCrusade.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
struct SBorderTestComponent
{
	const char*			szImage;			//NULL for a border canvas.
	EBorderLayoutCell	eCell;
	SInt32Vec2			sDesiredSize;		//-1 on an axis fills the cell on that axis.  -1, -1 on an image canvas takes the cel's size.
	SInt32Vec2			sExpectedPosition;
	SInt32Vec2			sExpectedSize;
};


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestBorderLayoutHelperLayout(char* szDirectory, int32 iWidth, int32 iHeight, size uiNumComponents, SBorderTestComponent* asComponents, uint32 iRandomSeed, int32 iExpectedRequiredWidth, int32 iExpectedRequiredHeight)
{
	CWinRefWindowFactory	cNativeFactory;
	CFileUtil				cFileUtil;
	CRandom					cRandom;

	cFileUtil.RemoveDir(szDirectory);
	cFileUtil.MakeDir(szDirectory);

	cRandom.Init(iRandomSeed);

	ObjectsInit();
	{
		Ptr<CWindow>			pTestWindow;
		CBorderLayoutHelper		cBorder;
		Ptr<CGridContainer>		pGrid;
		Ptr<CCanvas>			apCanvas[9];
		Ptr<CCanvasDraw>		pDraw;
		CTickTestRefWindow		cTick;
		SDataTestRefWindow		cData;
		CColourFormatHelper		cHelper;
		SBorderTestComponent*	psComponent;
		CChars					szExpectedDirectory;
		SInt32Vec2				sVec;
		CPointer				pNull;
		size					i;
		ARGB32					sColour;

		AssertTrue(uiNumComponents <= 9);

		cNativeFactory.Init(&gcMemoryAllocator, iWidth, iHeight, szDirectory);
		cTick.Init(&cData, 1);
		pTestWindow = OMalloc<CWindow>("Border Layout", &cNativeFactory, &cTick, pNull, CFT_RGB, CCO_RGB, CRGB_24bit, ARGB_None);
		pTestWindow->GetColourFormat(&cHelper);

		cBorder.Init(pTestWindow);
		pGrid = cBorder.GetContainer();
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
				sColour = Set32BitColour(cRandom.Next(0, 255) / 255.0f, cRandom.Next(0, 255) / 255.0f, cRandom.Next(0, 255) / 255.0f);
				pDraw = OMalloc<CBorderCanvasDraw>(sColour);
			}
			apCanvas[i] = OMalloc<CCanvas>(pTestWindow, pDraw);
			apCanvas[i]->SetDesiredSize(psComponent->sDesiredSize.x, psComponent->sDesiredSize.y);
			AssertTrue(cBorder.AddComponent(apCanvas[i], psComponent->eCell));
			pDraw = NULL;
		}
		if (uiNumComponents > 0)
		{
			AssertFalse(cBorder.AddComponent(apCanvas[0], (EBorderLayoutCell)9));
		}

		pGrid->SetRequiredSize();
		sVec = pGrid->GetRequiredSize();
		AssertInt32Vec2(iExpectedRequiredWidth, iExpectedRequiredHeight, &sVec);

		pTestWindow->Show();

		for (i = 0; i < uiNumComponents; i++)
		{
			sVec = apCanvas[i]->GetPosition();
			AssertInt32Vec2(asComponents[i].sExpectedPosition.x, asComponents[i].sExpectedPosition.y, &sVec);
			sVec = apCanvas[i]->GetActualSize();
			AssertInt32Vec2(asComponents[i].sExpectedSize.x, asComponents[i].sExpectedSize.y, &sVec);
			apCanvas[i] = NULL;
		}

		cBorder.Kill();
		pGrid = NULL;
		pTestWindow = NULL;

		szExpectedDirectory.Init(szDirectory);
		szExpectedDirectory.Replace("Output", "Input");
		AssertDirectory(szExpectedDirectory.Text(), szDirectory);
		szExpectedDirectory.Kill();
	}
	AssertTrue(ORoot()->RemoveAll());
	cNativeFactory.Kill();
	ObjectsFlush();
	ObjectsKill();

	cRandom.Kill();

	cFileUtil.RemoveDir(szDirectory);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestBorderLayoutHelperAllCells(void)
{
	//The left column is 12 wide and the right 8, the top row is 10 tall and the bottom 6.  The weighted centre column and
	//row take the rest of the 100 x 80 window.  The edges and the centre have no desired size on the axis they run along
	//so they fill their cells.
	SBorderTestComponent	asComponents[9] = {
		{ NULL, BLC_TopLeft,		SInt32Vec2(12, 10), SInt32Vec2(0, 0),   SInt32Vec2(12, 10) },
		{ NULL, BLC_Top,			SInt32Vec2(-1, 10), SInt32Vec2(12, 0),  SInt32Vec2(80, 10) },
		{ NULL, BLC_TopRight,		SInt32Vec2(8, 10),  SInt32Vec2(92, 0),  SInt32Vec2(8, 10) },
		{ NULL, BLC_Left,			SInt32Vec2(12, -1), SInt32Vec2(0, 10),  SInt32Vec2(12, 64) },
		{ NULL, BLC_Center,			SInt32Vec2(-1, -1), SInt32Vec2(12, 10), SInt32Vec2(80, 64) },
		{ NULL, BLC_Right,			SInt32Vec2(8, -1),  SInt32Vec2(92, 10), SInt32Vec2(8, 64) },
		{ NULL, BLC_BottomLeft,		SInt32Vec2(12, 6),  SInt32Vec2(0, 74),  SInt32Vec2(12, 6) },
		{ NULL, BLC_Bottom,			SInt32Vec2(-1, 6),  SInt32Vec2(12, 74), SInt32Vec2(80, 6) },
		{ NULL, BLC_BottomRight,	SInt32Vec2(8, 6),   SInt32Vec2(92, 74), SInt32Vec2(8, 6) } };

	TestBorderLayoutHelperLayout("Output" _FS_ "BorderLayoutHelperAllCells", 100, 80, 9, asComponents, 5167, 20, 16);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestBorderLayoutHelperMissingCells(void)
{
	//Nothing is in the right column or the corners so the right column takes no space and the weighted centre column gets
	//the 51 pixels the 9 wide pine leaves.  The rows are 8, 36 and 6.  The pine and the moon keep their cel sizes.  The
	//pine is aligned right, towards the centre, and centred vertically.  The moon is centred in its cell.
	SBorderTestComponent	asComponents[4] = {
		{ NULL,			BLC_Top,		SInt32Vec2(-1, 8),  SInt32Vec2(9, 0),   SInt32Vec2(51, 8) },
		{ "Pine.png",	BLC_Left,		SInt32Vec2(-1, -1), SInt32Vec2(0, 19),  SInt32Vec2(9, 14) },
		{ "Moon.png",	BLC_Center,		SInt32Vec2(-1, -1), SInt32Vec2(29, 21), SInt32Vec2(10, 10) },
		{ NULL,			BLC_Bottom,		SInt32Vec2(-1, 6),  SInt32Vec2(9, 44),  SInt32Vec2(51, 6) } };

	TestBorderLayoutHelperLayout("Output" _FS_ "BorderLayoutHelperMissingCells", 60, 50, 4, asComponents, 8270, 19, 28);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestBorderLayoutHelperAlignment(void)
{
	//The top right corner sets the right column to 8 and the top row to 10, the bottom left corner sets the left column to
	//12 and the bottom row to 6.  Everything else around the edge is smaller than its cell and is aligned towards the
	//centre: the top left corner sits at the bottom right of its cell, the top edge at the bottom of its row, the left edge
	//at the right of its column, the right edge at the left and the bottom edge and bottom right corner at the top.
	SBorderTestComponent	asComponents[9] = {
		{ NULL, BLC_TopLeft,		SInt32Vec2(6, 4),   SInt32Vec2(6, 6),   SInt32Vec2(6, 4) },
		{ NULL, BLC_Top,			SInt32Vec2(-1, 6),  SInt32Vec2(12, 4),  SInt32Vec2(80, 6) },
		{ NULL, BLC_TopRight,		SInt32Vec2(8, 10),  SInt32Vec2(92, 0),  SInt32Vec2(8, 10) },
		{ NULL, BLC_Left,			SInt32Vec2(8, -1),  SInt32Vec2(4, 10),  SInt32Vec2(8, 64) },
		{ NULL, BLC_Center,			SInt32Vec2(-1, -1), SInt32Vec2(12, 10), SInt32Vec2(80, 64) },
		{ NULL, BLC_Right,			SInt32Vec2(6, -1),  SInt32Vec2(92, 10), SInt32Vec2(6, 64) },
		{ NULL, BLC_BottomLeft,		SInt32Vec2(12, 6),  SInt32Vec2(0, 74),  SInt32Vec2(12, 6) },
		{ NULL, BLC_Bottom,			SInt32Vec2(-1, 4),  SInt32Vec2(12, 74), SInt32Vec2(80, 4) },
		{ NULL, BLC_BottomRight,	SInt32Vec2(4, 3),   SInt32Vec2(92, 74), SInt32Vec2(4, 3) } };

	TestBorderLayoutHelperLayout("Output" _FS_ "BorderLayoutHelperAlignment", 100, 80, 9, asComponents, 2318, 20, 16);
}


Ptr<CImageCel> CreateBlueButtonCel(Ptr<CImage> pStrip, int iTile, int iQuarterTurns)
{
	Ptr<CImage>		pTile;
	CImageAccessor*	pcSource;
	CImageAccessor*	pcDest;
	int				x;
	int				y;
	int				iTop;

	//The strip is eight 8 x 8 tiles from the top down: the top, right, bottom and left edges then the top left, top right,
	//bottom right and bottom left corners.  Every edge is drawn with its outside along its top so the right, bottom and
	//left edges are turned clockwise by one, two and three quarters to put their outsides on the outside of the button.
	iTop = iTile * 8;
	if (iQuarterTurns == 0)
	{
		return OMalloc<CImageCel>(pStrip, 0, iTop, 8, iTop + 8);
	}

	pTile = OMalloc<CImage>(8, 8, pStrip);
	pcSource = CImageAccessorCreator::Create(&pStrip);
	pcDest = CImageAccessorCreator::Create(&pTile);
	for (y = 0; y < 8; y++)
	{
		for (x = 0; x < 8; x++)
		{
			if (iQuarterTurns == 1)
			{
				pcDest->Set(x, y, pcSource->Get(y, iTop + 7 - x));
			}
			else if (iQuarterTurns == 2)
			{
				pcDest->Set(x, y, pcSource->Get(7 - x, iTop + 7 - y));
			}
			else
			{
				pcDest->Set(x, y, pcSource->Get(7 - y, iTop + x));
			}
		}
	}
	pcSource->Kill();
	pcDest->Kill();
	return OMalloc<CImageCel>(pTile);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AddBlueButtonPiece(CBorderLayoutHelper* pcBorder, Ptr<CWindow> pWindow, Ptr<CCanvasDraw> pDraw, EBorderLayoutCell eCell, int32 iWidth, int32 iHeight)
{
	Ptr<CCanvas>	pCanvas;

	pCanvas = OMalloc<CCanvas>(pWindow, pDraw);
	pCanvas->SetDesiredSize(iWidth, iHeight);
	AssertTrue(pcBorder->AddComponent(pCanvas, eCell));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
Ptr<CCanvas> CreateBlueButton(CBorderLayoutHelper* pcBorder, Ptr<CWindow> pWindow, char* szFilename, CColourFormatHelper* pcFormat)
{
	Ptr<CImage>			pStrip;
	Ptr<CGridContainer>	pGrid;
	Ptr<CCanvas>		pFace;

	//Like the old WindowLib's label: 8 x 8 corners, 8 pixel edges stretched along the sides and a 100 x 24 face filled
	//with the colour the tiles fade into.  Returns the face.
	pStrip = ReadSpaceImage("BlueButton", szFilename);
	pStrip = CImageColourConverter::ConvertColour(pStrip, pcFormat->meOrder);

	pcBorder->Init(pWindow);
	pGrid = pcBorder->GetContainer();
	pGrid->SetDesiredSize(116, 40);

	AddBlueButtonPiece(pcBorder, pWindow, OMalloc<CImageCanvasDraw>(CreateBlueButtonCel(pStrip, 4, 0)), BLC_TopLeft, -1, -1);
	AddBlueButtonPiece(pcBorder, pWindow, OMalloc<CImageCanvasDraw>(CreateBlueButtonCel(pStrip, 0, 0), true), BLC_Top, -1, 8);
	AddBlueButtonPiece(pcBorder, pWindow, OMalloc<CImageCanvasDraw>(CreateBlueButtonCel(pStrip, 5, 0)), BLC_TopRight, -1, -1);
	AddBlueButtonPiece(pcBorder, pWindow, OMalloc<CImageCanvasDraw>(CreateBlueButtonCel(pStrip, 3, 3), true), BLC_Left, 8, -1);
	pFace = OMalloc<CCanvas>(pWindow, OMalloc<CClearCanvasDraw>(Set32BitColour((uint8)115, 151, 255)));
	AssertTrue(pcBorder->AddComponent(pFace, BLC_Center));
	AddBlueButtonPiece(pcBorder, pWindow, OMalloc<CImageCanvasDraw>(CreateBlueButtonCel(pStrip, 1, 1), true), BLC_Right, 8, -1);
	AddBlueButtonPiece(pcBorder, pWindow, OMalloc<CImageCanvasDraw>(CreateBlueButtonCel(pStrip, 7, 0)), BLC_BottomLeft, -1, -1);
	AddBlueButtonPiece(pcBorder, pWindow, OMalloc<CImageCanvasDraw>(CreateBlueButtonCel(pStrip, 2, 2), true), BLC_Bottom, -1, 8);
	AddBlueButtonPiece(pcBorder, pWindow, OMalloc<CImageCanvasDraw>(CreateBlueButtonCel(pStrip, 6, 0)), BLC_BottomRight, -1, -1);
	return pFace;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestBorderLayoutHelperBlueButtons(void)
{
	CWinRefWindowFactory	cNativeFactory;
	CFileUtil				cFileUtil;
	char					szDirectory[] = "Output" _FS_ "BorderLayoutHelperBlueButtons";

	cFileUtil.RemoveDir(szDirectory);
	cFileUtil.MakeDir(szDirectory);

	ObjectsInit();
	{
		Ptr<CWindow>			pTestWindow;
		Ptr<CGridContainer>		pColumn;
		Ptr<CGridContainer>		pButton;
		Ptr<CCanvas>			apFaces[4];
		CBorderLayoutHelper		acBorders[4];
		CTickTestRefWindow		cTick;
		SDataTestRefWindow		cData;
		CColourFormatHelper		cHelper;
		CChars					szExpectedDirectory;
		SInt32Vec2				sVec;
		CPointer				pNull;
		size					i;
		char*					aszStates[4] = { (char*)"BlueBorderNormal.png", (char*)"BlueBorderMouseOver.png", (char*)"BlueBorderSelected.png", (char*)"BlueBorderPushed.png" };

		cNativeFactory.Init(&gcMemoryAllocator, 132, 184, szDirectory);
		cTick.Init(&cData, 1);
		pTestWindow = OMalloc<CWindow>("Blue Buttons", &cNativeFactory, &cTick, pNull, CFT_RGB, CCO_RGB, CRGB_24bit, ARGB_None);
		pTestWindow->GetColourFormat(&cHelper);

		//One button for each state, each centred in a 132 x 46 row.
		pColumn = OMalloc<CGridContainer>(pTestWindow);
		pTestWindow->SetContainer(pColumn);
		for (i = 0; i < 4; i++)
		{
			apFaces[i] = CreateBlueButton(&acBorders[i], pTestWindow, aszStates[i], &cHelper);
			pColumn->AddComponent(acBorders[i].GetContainer(), 0, (int)i, 1, 1, 1, 1);
		}

		pTestWindow->Show();

		for (i = 0; i < 4; i++)
		{
			pButton = acBorders[i].GetContainer();
			sVec = pButton->GetPosition();
			AssertInt32Vec2(8, 3 + 46 * (int32)i, &sVec);
			sVec = pButton->GetActualSize();
			AssertInt32Vec2(116, 40, &sVec);
			sVec = apFaces[i]->GetPosition();
			AssertInt32Vec2(16, 11 + 46 * (int32)i, &sVec);
			sVec = apFaces[i]->GetActualSize();
			AssertInt32Vec2(100, 24, &sVec);
			apFaces[i] = NULL;
			acBorders[i].Kill();
		}

		pButton = NULL;
		pColumn = NULL;
		pTestWindow = NULL;

		szExpectedDirectory.Init(szDirectory);
		szExpectedDirectory.Replace("Output", "Input");
		AssertDirectory(szExpectedDirectory.Text(), szDirectory);
		szExpectedDirectory.Kill();
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
void TestBorderLayoutHelper(void)
{
	BeginTests();

	TestBorderLayoutHelperAllCells();
	TestBorderLayoutHelperMissingCells();
	TestBorderLayoutHelperAlignment();
	TestBorderLayoutHelperBlueButtons();

	TestStatistics();
}

