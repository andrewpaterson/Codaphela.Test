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
// The outlined button from JetBrains' Jewel dark theme.  The outside two
// pixels of every tile are its focus ring, empty except when selected.
//
//////////////////////////////////////////////////////////////////////////
Ptr<CButtonImages> ReadJewelButtonImages(CColourFormatHelper* pcFormat)
{
	Ptr<CImage>		apStrips[NUM_BUTTON_STATES];
	char*			aszStates[NUM_BUTTON_STATES] = { (char*)"JewelBorderNormal.png", (char*)"JewelBorderMouseOver.png", (char*)"JewelBorderSelected.png", (char*)"JewelBorderPushed.png" };
	size			i;

	for (i = 0; i < NUM_BUTTON_STATES; i++)
	{
		apStrips[i] = ReadSpaceImage("JewelButton", aszStates[i]);
		apStrips[i] = CImageColourConverter::ConvertColour(apStrips[i], pcFormat->meOrder);
	}
	return OMalloc<CButtonImages>(apStrips[BS_Normal], apStrips[BS_MouseOver], apStrips[BS_Selected], apStrips[BS_Pushed], Set32BitColour((uint8)0x2B, 0x2D, 0x30));
}


//////////////////////////////////////////////////////////////////////////
//
// The default button from JetBrains' Jewel dark theme.  It is filled blue,
// lighter with the pointer over it and darker when pushed.  Selected it has
// a dark line between its face and its focus ring.
//
//////////////////////////////////////////////////////////////////////////
Ptr<CButtonImages> ReadJewelDefaultButtonImages(CColourFormatHelper* pcFormat)
{
	Ptr<CImage>		apStrips[NUM_BUTTON_STATES];
	char*			aszStates[NUM_BUTTON_STATES] = { (char*)"JewelDefaultBorderNormal.png", (char*)"JewelDefaultBorderMouseOver.png", (char*)"JewelDefaultBorderSelected.png", (char*)"JewelDefaultBorderPushed.png" };
	size			i;

	for (i = 0; i < NUM_BUTTON_STATES; i++)
	{
		apStrips[i] = ReadSpaceImage("JewelButton", aszStates[i]);
		apStrips[i] = CImageColourConverter::ConvertColour(apStrips[i], pcFormat->meOrder);
	}
	return OMalloc<CButtonImages>(apStrips[BS_Normal], apStrips[BS_MouseOver], apStrips[BS_Selected], apStrips[BS_Pushed],
									Set32BitColour((uint8)0x35, 0x74, 0xF0), Set32BitColour((uint8)0x46, 0x82, 0xFA), Set32BitColour((uint8)0x35, 0x74, 0xF0), Set32BitColour((uint8)0x36, 0x6A, 0xCE));
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
// The window is 300x60 with OK, Cancel and a focusable Name label in three
// columns.  OK is the default button.
//
//////////////////////////////////////////////////////////////////////////
void TestButtonDefault(void)
{
	CWinRefWindowFactory	cNativeFactory;

	{
		Ptr<CWindow>			pTestWindow;
		Ptr<CGridContainer>		pGrid;
		Ptr<CButtonImages>		pImages;
		Ptr<CButtonImages>		pDefaultImages;
		Ptr<CFont>				pFont;
		Ptr<CButton>			pOK;
		Ptr<CButton>			pCancel;
		Ptr<CLabel>				pName;
		Ptr<CFocus>				pFocus;
		CTickTestRefWindow		cTick;
		SDataTestRefWindow		cData;
		CColourFormatHelper		cHelper;
		CTestButtonListener		cListener;
		CPointer				pNull;
		CChars					szLog;
		SInt32Vec2				sSize;
		SInt32Vec2				sDefaultSize;
		int						y;

		szLog.Init();
		cListener.Init(&szLog);
		cNativeFactory.Init(&gcMemoryAllocator, 300, 60, NULL);
		cTick.Init(&cData, 1);
		pTestWindow = OMalloc<CWindow>("Default Button Window", &cNativeFactory, &cTick, pNull, CFT_RGB, CCO_RGB, CRGB_24bit, ARGB_None);
		pTestWindow->GetColourFormat(&cHelper);
		pFocus = pTestWindow->GetFocus();

		pFont = ReadLabelFont();
		pImages = ReadJewelButtonImages(&cHelper);
		pDefaultImages = ReadJewelDefaultButtonImages(&cHelper);
		AssertInt(Set32BitColour((uint8)0x2B, 0x2D, 0x30), pImages->GetFaceColour(BS_Pushed));
		AssertInt(Set32BitColour((uint8)0x36, 0x6A, 0xCE), pDefaultImages->GetFaceColour(BS_Pushed));

		pOK = OMalloc<CButton>(pTestWindow, pImages, pDefaultImages, pFont, "OK");
		pCancel = OMalloc<CButton>(pTestWindow, pImages, pFont, "Cancel");
		pName = OMalloc<CLabel>(pTestWindow, pFont, "Name");
		pName->SetCanGetFocus(true);
		AssertTrue(pOK->AddListener(&cListener));
		AssertTrue(pCancel->AddListener(&cListener));
		pGrid = OMalloc<CGridContainer>(pTestWindow);
		pTestWindow->SetContainer(pGrid);
		AssertTrue(pGrid->AddComponent(pOK, 0, 0, 1, 1, 1, 1));
		AssertTrue(pGrid->AddComponent(pCancel, 1, 0, 1, 1, 1, 1));
		AssertTrue(pGrid->AddComponent(pName, 2, 0, 1, 1, 1, 1));
		pTestWindow->Layout();

		//Without a default button enter goes nowhere when nothing has focus.
		AssertTrue(pTestWindow->GetDefaultButton().IsNull());
		AssertFalse(pOK->IsDefault());
		AssertTrue(pOK->GetImages() == pImages);
		pTestWindow->InputCommand(CIC_Enter, true);
		AssertLog("");

		//The default button takes on its default images.  Default images don't change its size.
		sSize = pOK->GetDesiredSize();
		pTestWindow->SetDefaultButton(pOK);
		AssertTrue(pTestWindow->GetDefaultButton() == pOK);
		AssertTrue(pOK->IsDefault());
		AssertTrue(pOK->GetImages() == pDefaultImages);
		sDefaultSize = pOK->GetDesiredSize();
		AssertInt32Vec2(sSize.x, sSize.y, &sDefaultSize);

		//With nothing focussed enter clicks the default button.
		pTestWindow->InputCommand(CIC_Enter, true);
		AssertLog("OK:Clicked;");

		//A focussed button wants enter for itself.
		y = pCancel->GetPosition().y + pCancel->GetActualSize().y / 2;
		pTestWindow->PointerMoved(pCancel->GetPosition().x + pCancel->GetActualSize().x / 2, y);
		pTestWindow->InputCommand(CIC_ActivateComponent, true);
		pTestWindow->InputCommand(CIC_ExecuteComponent, true);
		AssertLog("Cancel:Clicked;");
		AssertTrue(pCancel->IsFocussed());
		pTestWindow->InputCommand(CIC_Enter, true);
		AssertLog("Cancel:Clicked;");

		//A focussed component that doesn't want enter leaves it to the default button.
		pTestWindow->PointerMoved(pName->GetPosition().x + 1, pName->GetPosition().y + 1);
		pTestWindow->InputCommand(CIC_ActivateComponent, true);
		pTestWindow->InputCommand(CIC_ExecuteComponent, true);
		AssertTrue(pName->IsFocussed());
		pTestWindow->InputCommand(CIC_Enter, true);
		AssertLog("OK:Clicked;");

		//The default button clicks itself when focussed, once and not twice.
		pTestWindow->PointerMoved(pOK->GetPosition().x + pOK->GetActualSize().x / 2, y);
		pTestWindow->InputCommand(CIC_ActivateComponent, true);
		pTestWindow->InputCommand(CIC_ExecuteComponent, true);
		AssertLog("OK:Clicked;");
		pTestWindow->InputCommand(CIC_Enter, true);
		AssertLog("OK:Clicked;");

		//Making another button the default takes it from the first.  Cancel has no default images so looks the same.
		pTestWindow->SetDefaultButton(pCancel);
		AssertFalse(pOK->IsDefault());
		AssertTrue(pOK->GetImages() == pImages);
		AssertTrue(pCancel->IsDefault());
		AssertTrue(pCancel->GetImages() == pImages);

		pTestWindow->SetDefaultButton(pNull);
		AssertFalse(pCancel->IsDefault());
		AssertTrue(pTestWindow->GetDefaultButton().IsNull());

		ValidateLabelObjects();

		pOK = NULL;
		pCancel = NULL;
		pName = NULL;
		pGrid = NULL;
		pImages = NULL;
		pDefaultImages = NULL;
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
// over, pushed and then selected once the pointer moves away.  If asked it
// moves back over the button, which pushes it again as the press is still
// held.
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
	bool		mbReturnOver;

public:
	void Init(SInt32Vec2 sOver, SInt32Vec2 sAway, bool bReturnOver)
	{
		PreInit();
		CWindowTick::Init();
		miFrame = 0;
		msOver = sOver;
		msAway = sAway;
		mbReturnOver = bReturnOver;
		PostInit();
	}

	void Class(void) override
	{
		CWindowTick::Class();
		U_Int32(miFrame);
		U_2Int32(msOver);
		U_2Int32(msAway);
		U_Bool(mbReturnOver);
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
		else if ((miFrame == 4) && mbReturnOver)
		{
			pWindow->PointerMoved(msOver.x, msOver.y);
		}
		else
		{
			pWindow->Stop();
		}
	}
};


//////////////////////////////////////////////////////////////////////////
//
// The Jewel button's last frame is pushed after selected, so the focus
// ring drawn in the frame before must be gone from its empty band.  With
// default images the button is made the window's default button.
//
//////////////////////////////////////////////////////////////////////////
void TestButtonStates(char* szName, Ptr<CButtonImages>(*ReadImages)(CColourFormatHelper*), Ptr<CButtonImages>(*ReadDefaultImages)(CColourFormatHelper*), ARGB32 sBackground, bool bReturnOver)
{
	CWinRefWindowFactory	cNativeFactory;
	CFileUtil				cFileUtil;
	CChars					szDirectory;

	szDirectory.Init("Output" _FS_);
	szDirectory.Append(szName);
	cFileUtil.RemoveDir(szDirectory.Text());
	cFileUtil.MakeDir(szDirectory.Text());

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

		cNativeFactory.Init(&gcMemoryAllocator, 120, 60, szDirectory.Text());
		pTestWindow = OMalloc<CWindow>("Button States", &cNativeFactory, &cTick, OMalloc<CClearCanvasDraw>(sBackground), CFT_RGB, CCO_RGB, CRGB_24bit, ARGB_None);
		pTestWindow->GetColourFormat(&cHelper);

		pFont = ReadLabelFont();
		pImages = ReadImages(&cHelper);
		if (ReadDefaultImages)
		{
			pButton = OMalloc<CButton>(pTestWindow, pImages, ReadDefaultImages(&cHelper), pFont, "Press Me");
			pTestWindow->SetDefaultButton(pButton);
		}
		else
		{
			pButton = OMalloc<CButton>(pTestWindow, pImages, pFont, "Press Me");
		}
		pFill = OMalloc<CFillContainer>(pTestWindow);
		pTestWindow->SetContainer(pFill);
		pFill->AddComponent(pButton);

		pTestWindow->Layout();
		sPosition = pButton->GetPosition();
		sSize = pButton->GetActualSize();
		cTick.Init(SInt32Vec2(sPosition.x + sSize.x / 2, sPosition.y + sSize.y / 2), SInt32Vec2(1, 1), bReturnOver);

		pTestWindow->Show();
		AssertInt(bReturnOver ? BS_Pushed : BS_Selected, pButton->GetState());

		ValidateLabelObjects();

		pButton = NULL;
		pFill = NULL;
		pImages = NULL;
		pFont = NULL;
		pTestWindow = NULL;

		szExpectedDirectory.Init(szDirectory);
		szExpectedDirectory.Replace("Output", "Input");
		AssertDirectory(szExpectedDirectory.Text(), szDirectory.Text());
		szExpectedDirectory.Kill();
	}

	AssertSize(0, gcObjects.NumFreeObjects());
	AssertTrue(ORoot()->RemoveAll());
	AssertSize(2, gcObjects.NumMemoryIndexes());
	cNativeFactory.Kill();
	cFileUtil.RemoveDir(szDirectory.Text());
	szDirectory.Kill();
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
	TestButtonDefault();
	TestButtonStates((char*)"ButtonStates", ReadBlueButtonImages, NULL, Set32BitColour((uint8)40, 40, 48), false);
	TestButtonStates((char*)"JewelButtonStates", ReadJewelButtonImages, NULL, Set32BitColour((uint8)0x1E, 0x1F, 0x22), true);
	TestButtonStates((char*)"JewelDefaultButtonStates", ReadJewelButtonImages, ReadJewelDefaultButtonImages, Set32BitColour((uint8)0x1E, 0x1F, 0x22), true);

	ObjectsFlush();
	ObjectsKill();
	TestStatistics();
}

