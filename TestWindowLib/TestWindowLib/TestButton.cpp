#include "BaseLib/GlobalMemory.h"
#include "BaseLib/FileUtil.h"
#include "StandardLib/ClassDefines.h"
#include "StandardLib/Objects.h"
#include "SupportLib/ImageColourConverter.h"
#include "WindowLib/Window.h"
#include "WindowLib/GridContainer.h"
#include "WindowLib/FillContainer.h"
#include "WindowLib/ClearCanvasDraw.h"
#include "WindowLib/Button.h"
#include "WinRefLib/WinRefWindowFactory.h"
#include "TestLib/AssertGeometric.h"
#include "TestLib/AssertFile.h"
#include "TickTestRefWindow.h"
#include "DataTestRefWindow.h"
#include "SpaceCrusade.h"


Ptr<CFont> ReadLabelFont(void);
void ValidateLabelObjects(void);


#define AssertLog(e)	AssertString(e, szLog.Text()); szLog.Clear()


//////////////////////////////////////////////////////////////////////////
//
// Logs each click as "Caption:Clicked;".
//
//////////////////////////////////////////////////////////////////////////
class CTestButtonListener : public CButtonListener
{
CONSTRUCTABLE(CTestButtonListener);
public:
	CChars*		mpszLog;

	void Init(CChars* pszLog)
	{
		mpszLog = pszLog;
	}

	void ButtonClicked(CUnknown* pcSource, void* pvContext) override
	{
		CButton*	pcButton;

		pcButton = (CButton*)pcSource;
		mpszLog->Append(pcButton->GetCaption());
		mpszLog->Append(":Clicked;");
	}
};


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
Ptr<CButtonImages> ReadBlueButtonImages(CColourFormatHelper* pcFormat)
{
	Ptr<CImage>		apStrips[NUM_BUTTON_STATES];
	char*			aszStates[NUM_BUTTON_STATES] = { (char*)"BlueBorderNormal.png", (char*)"BlueBorderMouseOver.png", (char*)"BlueBorderSelected.png", (char*)"BlueBorderPushed.png" };
	size			i;

	for (i = 0; i < NUM_BUTTON_STATES; i++)
	{
		apStrips[i] = ReadSpaceImage("BlueButton", aszStates[i]);
		apStrips[i] = CImageColourConverter::ConvertColour(apStrips[i], pcFormat->meOrder);
	}
	return OMalloc<CButtonImages>(apStrips[BS_Normal], apStrips[BS_MouseOver], apStrips[BS_Selected], apStrips[BS_Pushed], Set32BitColour((uint8)115, 151, 255));
}


//////////////////////////////////////////////////////////////////////////
//
// The window is 200x60 with an OK button centred in its left half and a
// Cancel button centred in its right half.  The grid between them is the
// background.
//
//////////////////////////////////////////////////////////////////////////
void TestButtonInput(void)
{
	CWinRefWindowFactory	cNativeFactory;

	{
		Ptr<CWindow>			pTestWindow;
		Ptr<CGridContainer>		pGrid;
		Ptr<CButtonImages>		pImages;
		Ptr<CFont>				pFont;
		Ptr<CButton>			pOK;
		Ptr<CButton>			pCancel;
		Ptr<CFocus>				pFocus;
		CTickTestRefWindow		cTick;
		SDataTestRefWindow		cData;
		CColourFormatHelper		cHelper;
		CTestButtonListener		cListener;
		CPointer				pNull;
		CChars					szLog;
		SInt32Vec2				sSize;
		SInt32Vec2				sPosition;
		int32					iCaptionWidth;
		int32					iSpare;
		int						x;
		int						y;

		szLog.Init();
		cListener.Init(&szLog);
		cNativeFactory.Init(&gcMemoryAllocator, 200, 60, NULL);
		cTick.Init(&cData, 1);
		pTestWindow = OMalloc<CWindow>("Button Window", &cNativeFactory, &cTick, pNull, CFT_RGB, CCO_RGB, CRGB_24bit, ARGB_None);
		pTestWindow->GetColourFormat(&cHelper);
		pFocus = pTestWindow->GetFocus();

		pFont = ReadLabelFont();
		pImages = ReadBlueButtonImages(&cHelper);
		AssertInt(8, pImages->GetTileSize());

		pOK = OMalloc<CButton>(pTestWindow, pImages, pFont, "OK");
		pCancel = OMalloc<CButton>(pTestWindow, pImages, pFont, "Cancel");
		AssertTrue(pOK->AddListener(&cListener));
		AssertTrue(pCancel->AddListener(&cListener));
		pGrid = OMalloc<CGridContainer>(pTestWindow);
		pTestWindow->SetContainer(pGrid);
		AssertTrue(pGrid->AddComponent(pOK, 0, 0, 1, 1, 1, 1));
		AssertTrue(pGrid->AddComponent(pCancel, 1, 0, 1, 1, 1, 1));

		//A button is its caption, 8 pixels of padding each side and 2 above and below, inside an 8 pixel border.
		iCaptionWidth = (int32)pFont->CalculateWidth("OK");
		sSize = pOK->GetDesiredSize();
		AssertInt32Vec2(iCaptionWidth + 32, 44, &sSize);

		//Each column is its button's width plus half the spare width.  The button is centred in it.
		pTestWindow->Layout();
		sSize = pOK->GetActualSize();
		AssertInt32Vec2(iCaptionWidth + 32, 44, &sSize);
		iSpare = 200 - sSize.x - pCancel->GetActualSize().x;
		sPosition = pOK->GetPosition();
		AssertInt32Vec2((iSpare / 2) / 2, 8, &sPosition);
		AssertInt(BS_Normal, pOK->GetState());

		//The button is hit as a whole, its border and face included.
		x = sPosition.x + sSize.x / 2;
		y = sPosition.y + sSize.y / 2;
		AssertTrue(pTestWindow->FindComponentAt(x, y) == pOK);
		AssertTrue(pTestWindow->FindComponentAt(sPosition.x, sPosition.y) == pOK);
		AssertTrue(pTestWindow->FindComponentAt(sPosition.x - 1, y) == pGrid);

		pTestWindow->PointerMoved(x, y);
		AssertInt(BS_MouseOver, pOK->GetState());
		AssertTrue(pFocus->GetMouseOverComponent() == pOK);

		pTestWindow->InputCommand(CIC_ActivateComponent, true);
		AssertInt(BS_Pushed, pOK->GetState());
		AssertTrue(pOK->IsPressed());
		AssertTrue(pOK->IsFocussed());
		AssertLog("");
		pTestWindow->InputCommand(CIC_ExecuteComponent, true);
		AssertLog("OK:Clicked;");
		AssertInt(BS_MouseOver, pOK->GetState());
		AssertFalse(pOK->IsPressed());

		//Moving off a pressed button and letting go doesn't click it.
		pTestWindow->InputCommand(CIC_ActivateComponent, true);
		pTestWindow->PointerMoved(2, y);
		AssertInt(BS_Selected, pOK->GetState());
		pTestWindow->PointerMoved(x, y);
		AssertInt(BS_Pushed, pOK->GetState());
		pTestWindow->PointerMoved(2, y);
		pTestWindow->InputCommand(CIC_ExecuteComponent, true);
		AssertLog("");
		AssertInt(BS_Selected, pOK->GetState());

		//Space and enter click the button with focus.
		pTestWindow->InputCommand(CIC_Space, true);
		pTestWindow->InputCommand(CIC_Enter, true);
		AssertLog("OK:Clicked;OK:Clicked;");

		//Hovering over Cancel doesn't take focus from OK.
		x = pCancel->GetPosition().x + pCancel->GetActualSize().x / 2;
		pTestWindow->PointerMoved(x, y);
		AssertInt(BS_Selected, pOK->GetState());
		AssertInt(BS_MouseOver, pCancel->GetState());
		pTestWindow->InputCommand(CIC_ActivateComponent, true);
		AssertInt(BS_Normal, pOK->GetState());
		AssertInt(BS_Pushed, pCancel->GetState());
		pTestWindow->InputCommand(CIC_ExecuteComponent, true);
		AssertLog("Cancel:Clicked;");

		//Clicking the background clears focus.
		pTestWindow->PointerMoved(100, 2);
		AssertInt(BS_Selected, pCancel->GetState());
		pTestWindow->InputCommand(CIC_ActivateComponent, true);
		pTestWindow->InputCommand(CIC_ExecuteComponent, true);
		AssertInt(BS_Normal, pCancel->GetState());
		AssertTrue(pFocus->GetFocussedComponent().IsNull());
		AssertLog("");

		//Deactivating the window ends a press.
		pTestWindow->PointerMoved(x, y);
		pTestWindow->InputCommand(CIC_ActivateComponent, true);
		AssertInt(BS_Pushed, pCancel->GetState());
		pTestWindow->Deactivate();
		AssertInt(BS_Normal, pCancel->GetState());
		AssertFalse(pCancel->IsPressed());
		//Focus comes back but the pointer isn't known until it moves.
		pTestWindow->Activate();
		AssertInt(BS_Selected, pCancel->GetState());
		pTestWindow->InputCommand(CIC_ExecuteComponent, true);
		AssertLog("");
		pTestWindow->PointerMoved(x, y);
		AssertInt(BS_MouseOver, pCancel->GetState());

		AssertTrue(pCancel->RemoveListener(&cListener));
		pTestWindow->InputCommand(CIC_Enter, true);
		AssertLog("");

		//A longer caption makes the button wider.
		pOK->SetCaption("Okay");
		AssertString("Okay", pOK->GetCaption());
		sSize = pOK->GetDesiredSize();
		AssertInt32Vec2((int32)pFont->CalculateWidth("Okay") + 32, 44, &sSize);
		pOK->SetPadding(0, 0);
		sSize = pOK->GetDesiredSize();
		AssertInt32Vec2((int32)pFont->CalculateWidth("Okay") + 16, 40, &sSize);

		ValidateLabelObjects();

		pOK = NULL;
		pCancel = NULL;
		pGrid = NULL;
		pImages = NULL;
		pFont = NULL;
		pFocus = NULL;
		pTestWindow = NULL;
		szLog.Kill();
	}

	AssertSize(0, gcObjects.NumFreeObjects());
	AssertTrue(ORoot()->RemoveAll());
	AssertSize(2, gcObjects.NumMemoryIndexes());
	cNativeFactory.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// Draws a frame then moves the button on to its next state: normal, mouse
// over, pushed and then selected once the pointer moves away.
//
//////////////////////////////////////////////////////////////////////////
class CButtonStatesTick : public CWindowTick
{
CONSTRUCTABLE(CButtonStatesTick);
DESTRUCTABLE(CButtonStatesTick);
protected:
	int32		miFrame;
	SInt32Vec2	msOver;
	SInt32Vec2	msAway;

public:
	void Init(SInt32Vec2 sOver, SInt32Vec2 sAway)
	{
		PreInit();
		CWindowTick::Init();
		miFrame = 0;
		msOver = sOver;
		msAway = sAway;
		PostInit();
	}

	void Class(void) override
	{
		CWindowTick::Class();
		U_Int32(miFrame);
		U_2Int32(msOver);
		U_2Int32(msAway);
	}

	void Tick(Ptr<CWindow> pWindow, int64 iUpdateTimeInMillieconds, int64 iTotalTimeInMillieconds) override
	{
		pWindow->Paint();

		miFrame++;
		if (miFrame == 1)
		{
			pWindow->PointerMoved(msOver.x, msOver.y);
		}
		else if (miFrame == 2)
		{
			pWindow->InputCommand(CIC_ActivateComponent, true);
		}
		else if (miFrame == 3)
		{
			pWindow->PointerMoved(msAway.x, msAway.y);
		}
		else
		{
			pWindow->Stop();
		}
	}
};


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestButtonStates(void)
{
	CWinRefWindowFactory	cNativeFactory;
	CFileUtil				cFileUtil;
	char					szDirectory[] = "Output" _FS_ "ButtonStates";

	cFileUtil.RemoveDir(szDirectory);
	cFileUtil.MakeDir(szDirectory);

	{
		Ptr<CWindow>			pTestWindow;
		Ptr<CFillContainer>		pFill;
		Ptr<CButtonImages>		pImages;
		Ptr<CFont>				pFont;
		Ptr<CButton>			pButton;
		CButtonStatesTick		cTick;
		CColourFormatHelper		cHelper;
		CPointer				pNull;
		CChars					szExpectedDirectory;
		SInt32Vec2				sPosition;
		SInt32Vec2				sSize;

		cNativeFactory.Init(&gcMemoryAllocator, 120, 60, szDirectory);
		pTestWindow = OMalloc<CWindow>("Button States", &cNativeFactory, &cTick, OMalloc<CClearCanvasDraw>(Set32BitColour((uint8)40, 40, 48)), CFT_RGB, CCO_RGB, CRGB_24bit, ARGB_None);
		pTestWindow->GetColourFormat(&cHelper);

		pFont = ReadLabelFont();
		pImages = ReadBlueButtonImages(&cHelper);
		pButton = OMalloc<CButton>(pTestWindow, pImages, pFont, "Press Me");
		pFill = OMalloc<CFillContainer>(pTestWindow);
		pTestWindow->SetContainer(pFill);
		pFill->AddComponent(pButton);

		pTestWindow->Layout();
		sPosition = pButton->GetPosition();
		sSize = pButton->GetActualSize();
		cTick.Init(SInt32Vec2(sPosition.x + sSize.x / 2, sPosition.y + sSize.y / 2), SInt32Vec2(1, 1));

		pTestWindow->Show();
		AssertInt(BS_Selected, pButton->GetState());

		ValidateLabelObjects();

		pButton = NULL;
		pFill = NULL;
		pImages = NULL;
		pFont = NULL;
		pTestWindow = NULL;

		szExpectedDirectory.Init(szDirectory);
		szExpectedDirectory.Replace("Output", "Input");
		AssertDirectory(szExpectedDirectory.Text(), szDirectory);
		szExpectedDirectory.Kill();
	}

	AssertSize(0, gcObjects.NumFreeObjects());
	AssertTrue(ORoot()->RemoveAll());
	AssertSize(2, gcObjects.NumMemoryIndexes());
	cNativeFactory.Kill();
	cFileUtil.RemoveDir(szDirectory);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestButton(void)
{
	BeginTests();
	ObjectsInit();

	TestButtonInput();
	TestButtonStates();

	ObjectsFlush();
	ObjectsKill();
	TestStatistics();
}

