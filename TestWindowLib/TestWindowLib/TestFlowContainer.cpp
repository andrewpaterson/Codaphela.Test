#include "BaseLib/GlobalMemory.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/StdRandom.h"
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
void TestFlowContainerBasic(void)
{
	CWinRefWindowFactory	cNativeFactory;
	CFileUtil				cFileUtil;
	char					szDirectory[] = "Output" _FS_ "FlowContainerBasic";

	cFileUtil.RemoveDir(szDirectory);
	cFileUtil.MakeDir(szDirectory);

	{
		CWindow					cTestWindow;
		CArrayChars				aszFiles;
		size					i;
		CChars* pszFilename;
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

		cNativeFactory.Init(&gcMemoryAllocator, 96, 30, szDirectory);

		cTick.Init(&cData, 1);
		cTestWindow.Init("Reference Test Window", &cNativeFactory, &cTick, NULL);

		cDraw1.Init(Set32BitColour(1.0f, 0, 0));
		cCanvas1.Init(&cTestWindow, CF_R8G8B8, &cDraw1);
		cDraw2.Init(Set32BitColour(0, 1.0f, 0));
		cCanvas2.Init(&cTestWindow, CF_R8G8B8, &cDraw2);
		cDraw3.Init(Set32BitColour(0, 0, 1.0f));
		cCanvas3.Init(&cTestWindow, CF_R8G8B8, &cDraw3);

		cFlow.Init(&cTestWindow);
		cFlow.SetFlowStyle(CSD_Right, CSW_Continue, CSV_Top);
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
void TestFlowContainerRightCenteredContinue(void)
{
	CWinRefWindowFactory	cNativeFactory;
	CFileUtil				cFileUtil;
	char					szDirectory[] = "Output" _FS_ "FlowContainerRightCenteredContinue";

	cFileUtil.RemoveDir(szDirectory);
	cFileUtil.MakeDir(szDirectory);

	{
		Ptr<CWindow>							pTestWindow;
		CArrayChars								aszFiles;
		size									i;
		CChars* pszFilename;
		CChars									szExpectedFilename;
		Ptr<CCanvas>							pCanvas;
		Ptr<CDrawCanvasBorder>					pDraw;
		CTickTestRefWindow						cTick;
		SDataTestRefWindow						cData;
		Ptr<CFlowContainer>						pFlow;
		SContainerBounds						sBounds;
		ARGB32									sColour;
		CRandom									cRandom;
		CPointer								pNull;
		CArrayTemplateEmbeddedBaseObjectPtr		apcHeapFroms;
		CArrayStackPointer						apcStackFroms;
		size									uiNumHeaps;
		CBaseObject* pcWindowObject;
		CBaseObject* pcCanvasObject1a;
		CBaseObject* pcCanvasObject1b;
		CBaseObject* pcFocusObject;
		CBaseObject* pcObject;
		CPointer* pcWindowPointer;
		CPointer* pcPointer1;

		cNativeFactory.Init(&gcMemoryAllocator, 96, 24, szDirectory);

		cTick.Init(&cData, 1);
		pTestWindow = OMalloc<CWindow>("Reference Test Window", &cNativeFactory, &cTick, pNull);
		AssertSize(4, pTestWindow.NumHeapFroms());
		apcHeapFroms.Init();
		pTestWindow->GetHeapFroms(&apcHeapFroms);
		pcWindowObject = *apcHeapFroms.Get(0);
		pcCanvasObject1a = *apcHeapFroms.Get(1);
		pcCanvasObject1b = *apcHeapFroms.Get(2);
		pcFocusObject = *apcHeapFroms.Get(3);
		apcHeapFroms.Kill();

		AssertPointer(&pTestWindow, pcWindowObject);
		AssertPointer(&pTestWindow->GetCanvas(), pcCanvasObject1a);
		AssertPointer(&pTestWindow->GetCanvas(), pcCanvasObject1b);
		AssertPointer(&pTestWindow->GetFocus(), pcFocusObject);

		AssertSize(1, pTestWindow.NumStackFroms());
		apcStackFroms.Init();
		pTestWindow->GetStackFroms(&apcStackFroms);
		pcWindowPointer = apcStackFroms.Get(0)->u.pcPointer;
		apcStackFroms.Kill();
		AssertPointer(pTestWindow.This(), pcWindowPointer);

		pFlow = OMalloc<CFlowContainer>(pTestWindow);

		pFlow->SetFlowStyle(CSD_Right, CSW_Continue, CSV_Center);
		pTestWindow->SetContainer(pFlow);
		AssertSize(3, gcObjects.NumMemoryIndexes());

		cRandom.Init(6785);
		for (i = 0; i < 10; i++)
		{
			sColour = Set32BitColour(cRandom.Next(0, 255) / 255.0f, cRandom.Next(0, 255) / 255.0f, cRandom.Next(0, 255) / 255.0f);
			pDraw = OMalloc<CDrawCanvasBorder>(sColour);

			pCanvas = OMalloc<CCanvas>(pTestWindow, CF_R8G8B8, pDraw);
			pFlow->AddComponent(pCanvas);

			if (i % 2 == 0)
			{
				pCanvas->SetDesiredSize(5 + i, 5 + i);
			}
			else
			{
				pCanvas->SetDesiredSize(5 + (10 - i), 5 + (10 - i));
			}
			pCanvas = NULL;
			pDraw = NULL;

			AssertSize(3 + (i + 1) * 2, gcObjects.NumMemoryIndexes());
			AssertSize(6 + i, pTestWindow.NumHeapFroms());
			AssertSize(1, pTestWindow.NumStackFroms());

			apcHeapFroms.Init();
			pTestWindow->GetHeapFroms(&apcHeapFroms);
			pcWindowObject = *apcHeapFroms.Get(0);
			pcCanvasObject1a = *apcHeapFroms.Get(1);
			pcCanvasObject1b = *apcHeapFroms.Get(2);
			pcFocusObject = *apcHeapFroms.Get(3);
			apcHeapFroms.Kill();

			AssertPointer(&pTestWindow, pcWindowObject);
			AssertPointer(&pTestWindow->GetCanvas(), pcCanvasObject1a);
			AssertPointer(&pTestWindow->GetCanvas(), pcCanvasObject1b);
			AssertPointer(&pTestWindow->GetFocus(), pcFocusObject);
		}

		AssertSize(10, pFlow->NumComponents());
		AssertSize(1, pFlow.NumStackFroms());
		apcStackFroms.Init();
		pFlow->GetStackFroms(&apcStackFroms);
		pcPointer1 = apcStackFroms.Get(0)->u.pcPointer;
		apcStackFroms.Kill();
		pFlow = NULL;

		pTestWindow->Show();
		AssertSize(34, gcObjects.NumMemoryIndexes());

		AssertSize(1, pTestWindow.NumStackFroms());
		apcStackFroms.Init();
		pTestWindow->GetStackFroms(&apcStackFroms);
		pcWindowPointer = apcStackFroms.Get(0)->u.pcPointer;
		apcStackFroms.Kill();
		AssertPointer(pTestWindow.This(), pcWindowPointer);

		AssertSize(15, pTestWindow.NumHeapFroms());
		apcHeapFroms.Init();
		pTestWindow->GetHeapFroms(&apcHeapFroms);
		uiNumHeaps = apcHeapFroms.NumElements();
		for (i = 0; i < uiNumHeaps; i++)
		{
			pcObject = *apcHeapFroms.Get(i);
		}
		apcHeapFroms.Kill();

		pTestWindow = NULL;
		AssertSize(0, gcObjects.NumMemoryIndexes());

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
void TestFlowContainerRightTopContinue(void)
{
	CWinRefWindowFactory	cNativeFactory;
	CFileUtil				cFileUtil;
	char					szDirectory[] = "Output" _FS_ "FlowContainerRightTopContinue";

	cFileUtil.RemoveDir(szDirectory);
	cFileUtil.MakeDir(szDirectory);

	{
		Ptr<CWindow>							pTestWindow;
		CArrayChars								aszFiles;
		size									i;
		CChars* pszFilename;
		CChars									szExpectedFilename;
		Ptr<CCanvas>							pCanvas;
		Ptr<CDrawCanvasBorder>					pDraw;
		CTickTestRefWindow						cTick;
		SDataTestRefWindow						cData;
		Ptr<CFlowContainer>						pFlow;
		SContainerBounds						sBounds;
		ARGB32									sColour;
		CRandom									cRandom;
		CPointer								pNull;

		cNativeFactory.Init(&gcMemoryAllocator, 96, 24, szDirectory);

		cTick.Init(&cData, 1);
		pTestWindow = OMalloc<CWindow>("Reference Test Window", &cNativeFactory, &cTick, pNull);
		AssertSize(4, pTestWindow.NumHeapFroms());


		pFlow = OMalloc<CFlowContainer>(pTestWindow);

		pFlow->SetFlowStyle(CSD_Right, CSW_Continue, CSV_Top);
		pTestWindow->SetContainer(pFlow);

		cRandom.Init(2945);
		for (i = 0; i < 10; i++)
		{
			sColour = Set32BitColour(cRandom.Next(0, 255) / 255.0f, cRandom.Next(0, 255) / 255.0f, cRandom.Next(0, 255) / 255.0f);
			pDraw = OMalloc<CDrawCanvasBorder>(sColour);

			pCanvas = OMalloc<CCanvas>(pTestWindow, CF_R8G8B8, pDraw);
			pFlow->AddComponent(pCanvas);

			if (i % 2 == 0)
			{
				pCanvas->SetDesiredSize(5 + i, 5 + i);
			}
			else
			{
				pCanvas->SetDesiredSize(5 + (10 - i), 5 + (10 - i));
			}
			pCanvas = NULL;
			pDraw = NULL;

			AssertSize(3 + (i + 1) * 2, gcObjects.NumMemoryIndexes());
			AssertSize(6 + i, pTestWindow.NumHeapFroms());
			AssertSize(1, pTestWindow.NumStackFroms());
		}

		pTestWindow->Show();


		AssertSize(34, gcObjects.NumMemoryIndexes());
		pTestWindow = NULL;
		AssertSize(34, gcObjects.NumMemoryIndexes());
		pFlow = NULL;
		AssertSize(0, gcObjects.NumMemoryIndexes());

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
void TestFlowContainerRightBottomContinue(void)
{
	CWinRefWindowFactory	cNativeFactory;
	CFileUtil				cFileUtil;
	char					szDirectory[] = "Output" _FS_ "FlowContainerRightBottomContinue";

	cFileUtil.RemoveDir(szDirectory);
	cFileUtil.MakeDir(szDirectory);

	{
		Ptr<CWindow>							pTestWindow;
		CArrayChars								aszFiles;
		size									i;
		CChars* pszFilename;
		CChars									szExpectedFilename;
		Ptr<CCanvas>							pCanvas;
		Ptr<CDrawCanvasBorder>					pDraw;
		CTickTestRefWindow						cTick;
		SDataTestRefWindow						cData;
		Ptr<CFlowContainer>						pFlow;
		SContainerBounds						sBounds;
		ARGB32									sColour;
		CRandom									cRandom;
		CPointer								pNull;

		cNativeFactory.Init(&gcMemoryAllocator, 96, 24, szDirectory);

		cTick.Init(&cData, 1);
		pTestWindow = OMalloc<CWindow>("Reference Test Window", &cNativeFactory, &cTick, pNull);
		AssertSize(4, pTestWindow.NumHeapFroms());


		pFlow = OMalloc<CFlowContainer>(pTestWindow);

		pFlow->SetFlowStyle(CSD_Right, CSW_Continue, CSV_Bottom);
		pTestWindow->SetContainer(pFlow);

		cRandom.Init(3563);
		for (i = 0; i < 10; i++)
		{
			sColour = Set32BitColour(cRandom.Next(0, 255) / 255.0f, cRandom.Next(0, 255) / 255.0f, cRandom.Next(0, 255) / 255.0f);
			pDraw = OMalloc<CDrawCanvasBorder>(sColour);

			pCanvas = OMalloc<CCanvas>(pTestWindow, CF_R8G8B8, pDraw);
			pFlow->AddComponent(pCanvas);

			if (i % 2 == 0)
			{
				pCanvas->SetDesiredSize(5 + i, 5 + i);
			}
			else
			{
				pCanvas->SetDesiredSize(5 + (10 - i), 5 + (10 - i));
			}
			pCanvas = NULL;
			pDraw = NULL;

			AssertSize(3 + (i + 1) * 2, gcObjects.NumMemoryIndexes());
			AssertSize(6 + i, pTestWindow.NumHeapFroms());
			AssertSize(1, pTestWindow.NumStackFroms());
		}

		pTestWindow->Show();


		AssertSize(34, gcObjects.NumMemoryIndexes());
		pTestWindow = NULL;
		AssertSize(34, gcObjects.NumMemoryIndexes());
		pFlow = NULL;
		AssertSize(0, gcObjects.NumMemoryIndexes());

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
void TestFlowContainer(void)
{
	BeginTests();

	TestFlowContainerBasic();
	TestFlowContainerRightCenteredContinue();
	TestFlowContainerRightTopContinue();
	TestFlowContainerRightBottomContinue();

	TestStatistics();
}

