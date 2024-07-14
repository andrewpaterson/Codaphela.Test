#include "SupportLib/RectangleBestPacker.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestRectanglePackerHorizontalAllSameSize(void)
{
	CRectangleBestPacker	cPacker;
	CPackAttempt*			pcBestAttempt;
	CPackedLine*			pcLine;
	CPackRectangleAttempt*	pcRect;
	CRectangle				cRect1;
	CRectangle				cRect2;
	CRectangle				cRect3;
	CRectangle				cRect4;
	CRectangle				cRect5;
	CRectangle				cRect6;
	char					sz1[] = "1";
	char					sz2[] = "2";
	char					sz3[] = "3";
	char					sz4[] = "4";
	char					sz5[] = "5";
	char					sz6[] = "6";

	cRect1.Init(0, 0, 10, 10);
	cRect2.Init(0, 0, 10, 10);
	cRect3.Init(0, 0, 10, 10);
	cRect4.Init(0, 0, 10, 10);
	cRect5.Init(0, 0, 10, 10);
	cRect6.Init(0, 0, 10, 10);

	cPacker.Init(0, 0);

	cPacker.AddRectangle(&cRect1, sz1);
	cPacker.AddRectangle(&cRect2, sz2);
	cPacker.AddRectangle(&cRect3, sz3);
	cPacker.AddRectangle(&cRect4, sz4);
	cPacker.AddRectangle(&cRect5, sz5);
	cPacker.AddRectangle(&cRect6, sz6);

	cPacker.AddHorizontalAttempt();
	cPacker.Pack();

	pcBestAttempt = cPacker.GetBestAttempt();
	AssertInt(1, pcBestAttempt->macLines.NumElements());
	pcLine = pcBestAttempt->macLines.Get(0);
	AssertInt(6, pcLine->macRectangles.NumElements());

	AssertInt(0, pcLine->miy);
	AssertInt(60, pcLine->miWidth);
	AssertInt(10, pcLine->miHeight);

	pcRect = pcLine->Get(sz1);
	AssertNotNull(pcRect);
	AssertInt(50, pcRect->mix);
	AssertInt(0, pcRect->miy);

	pcRect = pcLine->Get(sz2);
	AssertNotNull(pcRect);
	AssertInt(10, pcRect->mix);
	AssertInt(0, pcRect->miy);

	pcRect = pcLine->Get(sz3);
	AssertNotNull(pcRect);
	AssertInt(20, pcRect->mix);
	AssertInt(0, pcRect->miy);

	pcRect = pcLine->Get(sz4);
	AssertNotNull(pcRect);
	AssertInt(30, pcRect->mix);
	AssertInt(0, pcRect->miy);

	pcRect = pcLine->Get(sz5);
	AssertNotNull(pcRect);
	AssertInt(40, pcRect->mix);
	AssertInt(0, pcRect->miy);

	pcRect = pcLine->Get(sz6);
	AssertNotNull(pcRect);
	AssertInt(0, pcRect->mix);
	AssertInt(0, pcRect->miy);

	cPacker.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestRectanglePackerSquareAllSameSize(void)
{
	CRectangleBestPacker		cPacker;
	CPackAttempt*			pcBestAttempt;
	CPackedLine*			pcLine;
	CRectangle				cRect1;
	CRectangle				cRect2;
	CRectangle				cRect3;
	CRectangle				cRect4;
	CRectangle				cRect5;
	CRectangle				cRect6;
	CRectangle				cRect7;
	CRectangle				cRect8;
	char					sz1[] = "1";
	char					sz2[] = "2";
	char					sz3[] = "3";
	char					sz4[] = "4";
	char					sz5[] = "5";
	char					sz6[] = "6";
	char					sz7[] = "7";
	char					sz8[] = "8";

	cRect1.Init(0, 0, 1, 1);
	cRect2.Init(0, 0, 1, 1);
	cRect3.Init(0, 0, 1, 1);
	cRect4.Init(0, 0, 1, 1);
	cRect5.Init(0, 0, 1, 1);
	cRect6.Init(0, 0, 1, 1);
	cRect7.Init(0, 0, 1, 1);
	cRect8.Init(0, 0, 1, 1);

	cPacker.Init(0, 0);

	cPacker.AddRectangle(&cRect1, sz1);
	cPacker.AddRectangle(&cRect2, sz2);
	cPacker.AddRectangle(&cRect3, sz3);
	cPacker.AddRectangle(&cRect4, sz4);
	cPacker.AddRectangle(&cRect5, sz5);
	cPacker.AddRectangle(&cRect6, sz6);
	cPacker.AddRectangle(&cRect7, sz7);
	cPacker.AddRectangle(&cRect8, sz8);

	cPacker.AddSquareAttempt();
	cPacker.Pack();

	pcBestAttempt = cPacker.GetBestAttempt();
	AssertInt(3, pcBestAttempt->macLines.NumElements());
	AssertInt(3, pcBestAttempt->miHeight);
	AssertInt(3, pcBestAttempt->miWidth);

	pcLine = pcBestAttempt->macLines.Get(0);
	AssertInt(3, pcLine->macRectangles.NumElements());
	AssertInt(0, pcLine->miy);
	AssertInt(3, pcLine->miWidth);
	AssertInt(1, pcLine->miHeight);

	pcLine = pcBestAttempt->macLines.Get(1);
	AssertInt(3, pcLine->macRectangles.NumElements());
	AssertInt(1, pcLine->miy);
	AssertInt(3, pcLine->miWidth);
	AssertInt(1, pcLine->miHeight);

	pcLine = pcBestAttempt->macLines.Get(2);
	AssertInt(2, pcLine->macRectangles.NumElements());
	AssertInt(2, pcLine->miy);
	AssertInt(2, pcLine->miWidth);
	AssertInt(1, pcLine->miHeight);

	cPacker.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AddPowerOf2Sizes(CRectangleBestPacker* pcPacker)
{
	CRectangle				cRect1;
	CRectangle				cRect2;
	CRectangle				cRect3;
	CRectangle				cRect4;
	CRectangle				cRect5;
	CRectangle				cRect6;
	CRectangle				cRect7;
	CRectangle				cRect8;

	cRect1.Init(0, 0, 8, 8);
	cRect2.Init(0, 0, 8, 8);
	cRect3.Init(0, 0, 4, 4);
	cRect4.Init(0, 0, 4, 4);
	cRect5.Init(0, 0, 4, 4);
	cRect6.Init(0, 0, 2, 2);
	cRect7.Init(0, 0, 2, 2);
	cRect8.Init(0, 0, 1, 1);

	pcPacker->AddRectangle(&cRect1, NULL);
	pcPacker->AddRectangle(&cRect2, NULL);
	pcPacker->AddRectangle(&cRect3, NULL);
	pcPacker->AddRectangle(&cRect4, NULL);
	pcPacker->AddRectangle(&cRect5, NULL);
	pcPacker->AddRectangle(&cRect6, NULL);
	pcPacker->AddRectangle(&cRect7, NULL);
	pcPacker->AddRectangle(&cRect8, NULL);

}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestRectanglePackerHorizontalPowerOf2Sizes(void)
{
	CRectangleBestPacker		cPacker;
	CPackAttempt*			pcBestAttempt;
	CChars					szRep;

	cPacker.Init(0, 0);
	AddPowerOf2Sizes(&cPacker);
	cPacker.AddHorizontalAttempt();
	cPacker.Pack();

	pcBestAttempt = cPacker.GetBestAttempt();
	AssertInt(1, pcBestAttempt->macLines.NumElements());
	AssertInt(24, pcBestAttempt->miWidth);
	AssertInt(8, pcBestAttempt->miHeight);

	szRep.Init();
	pcBestAttempt->Print(&szRep);
	AssertString("Lines[1] Size[24, 8]\n[(0, 0) 8:8], [(8, 0) 8:8], [(16, 0) 4:4], [(16, 4) 4:4], [(20, 0) 4:4], [(20, 4) 2:2], [(20, 6) 2:2], [(22, 4) 1:1]\n", szRep.Text());
	szRep.Kill();

	cPacker.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestRectanglePackerSquarePowerOf2Sizes(void)
{
	CRectangleBestPacker		cPacker;
	CPackAttempt*			pcBestAttempt;
	CChars					szRep;

	cPacker.Init(0, 0);

	AddPowerOf2Sizes(&cPacker);

	cPacker.AddSquareAttempt();
	cPacker.Pack();

	pcBestAttempt = cPacker.GetBestAttempt();
	AssertInt(2, pcBestAttempt->macLines.NumElements());
	AssertInt(16, pcBestAttempt->miWidth);
	AssertInt(12, pcBestAttempt->miHeight);

	szRep.Init();
	pcBestAttempt->Print(&szRep);
	AssertString("Lines[2] Size[16, 12]\n[(0, 0) 8:8], [(8, 0) 8:8]\n[(0, 0) 4:4], [(4, 0) 4:4], [(8, 0) 4:4], [(12, 0) 2:2], [(12, 2) 2:2], [(14, 0) 1:1]\n", szRep.Text());
	szRep.Kill();

	cPacker.Kill();
}



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestRectanglePackerVerticalPowerOf2Sizes(void)
{
	CRectangleBestPacker		cPacker;
	CPackAttempt*			pcBestAttempt;
	CChars					szRep;

	cPacker.Init(0, 0);
	AddPowerOf2Sizes(&cPacker);
	cPacker.AddVerticalAttempt();
	cPacker.Pack();

	pcBestAttempt = cPacker.GetBestAttempt();
	AssertInt(4, pcBestAttempt->macLines.NumElements());
	AssertInt(8, pcBestAttempt->miWidth);
	AssertInt(24, pcBestAttempt->miHeight);

	szRep.Init();
	pcBestAttempt->Print(&szRep);
	AssertString("Lines[4] Size[8, 24]\n[(0, 0) 8:8]\n[(0, 0) 8:8]\n[(0, 0) 4:4], [(4, 0) 4:4]\n[(0, 0) 4:4], [(4, 0) 2:2], [(4, 2) 2:2], [(6, 0) 1:1]\n", szRep.Text());
	szRep.Kill();

	cPacker.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestRectanglePackerDefault(void)
{
	CRectangleBestPacker		cPacker;
	CPackAttempt*			pcBestAttempt;
	CPackAttempt*			pcWorstAttempt;
	CChars					szRep;

	cPacker.Init(0, 0);
	AddPowerOf2Sizes(&cPacker);
	cPacker.AddDefaultAttempts();
	cPacker.Pack();

	pcBestAttempt = cPacker.GetBestAttempt();
	AssertInt(1, pcBestAttempt->macLines.NumElements());
	AssertInt(24, pcBestAttempt->miWidth);
	AssertInt(8, pcBestAttempt->miHeight);
	AssertInt(7, pcBestAttempt->GetWastedArea());

	szRep.Init();
	pcBestAttempt->Print(&szRep);
	AssertString("Lines[1] Size[24, 8]\n[(0, 0) 8:8], [(8, 0) 8:8], [(16, 0) 4:4], [(16, 4) 4:4], [(20, 0) 4:4], [(20, 4) 2:2], [(20, 6) 2:2], [(22, 4) 1:1]\n", szRep.Text());
	szRep.Kill();

	pcWorstAttempt = cPacker.GetWorstAttempt();
	AssertInt(2, pcWorstAttempt->macLines.NumElements());
	AssertInt(22, pcWorstAttempt->miWidth);
	AssertInt(12, pcWorstAttempt->miHeight);
	AssertInt(79, pcWorstAttempt->GetWastedArea());

	szRep.Init();
	pcWorstAttempt->Print(&szRep);
	AssertString("Lines[2] Size[22, 12]\n[(0, 0) 8:8], [(8, 0) 8:8], [(16, 0) 4:4], [(16, 4) 4:4], [(20, 0) 2:2], [(20, 2) 2:2], [(20, 4) 1:1]\n[(0, 0) 4:4]\n", szRep.Text());
	szRep.Kill();

	cPacker.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestRectanglePackerGetPackedRectangles(void)
{
	CRectangleBestPacker	cPacker;
	CPackAttempt*			pcBestAttempt;
	CRectangle				cRect1;
	CRectangle				cRect2;
	CRectangle				cRect3;
	char					sz1[] = "1";
	char					sz2[] = "2";
	char					sz3[] = "3";
	CArrayPackedRectangle	macRects;
	CPackedRectangle*		pcPackedRect;

	cRect1.Init(0, 0, 7, 5);
	cRect2.Init(0, 0, 3, 5);
	cRect3.Init(0, 0, 4, 5);

	cPacker.Init(0, 0);

	cPacker.AddRectangle(&cRect1, sz1);
	cPacker.AddRectangle(&cRect2, sz2);
	cPacker.AddRectangle(&cRect3, sz3);

	cPacker.AddVerticalAttempt();
	cPacker.Pack();

	pcBestAttempt = cPacker.GetBestAttempt();
	macRects.Init();
	pcBestAttempt->GetPackedRectangles(&macRects);

	AssertInt(3, macRects.NumElements());

	pcPackedRect = macRects.Get(0);
	AssertString(sz1, (char*)pcPackedRect->GetUserData());
	AssertInt(0, pcPackedRect->miLeft);
	AssertInt(0, pcPackedRect->miTop);
	AssertInt(7, pcPackedRect->miRight);
	AssertInt(5, pcPackedRect->miBottom);

	pcPackedRect = macRects.Get(1);
	AssertString(sz3, (char*)pcPackedRect->GetUserData());
	AssertInt(0, pcPackedRect->miLeft);
	AssertInt(5, pcPackedRect->miTop);
	AssertInt(4, pcPackedRect->miRight);
	AssertInt(10, pcPackedRect->miBottom);

	pcPackedRect = macRects.Get(2);
	AssertString(sz2, (char*)pcPackedRect->GetUserData());
	AssertInt(4, pcPackedRect->miLeft);
	AssertInt(5, pcPackedRect->miTop);
	AssertInt(7, pcPackedRect->miRight);
	AssertInt(10, pcPackedRect->miBottom);

	macRects.Kill();
	cPacker.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestRectanglePackerGetPackedRectanglesWithEdges(void)
{
	CRectangleBestPacker		cPacker;
	CPackAttempt*			pcBestAttempt;
	CRectangle				cRect1;
	CRectangle				cRect2;
	CRectangle				cRect3;
	char					sz1[] = "1";
	char					sz2[] = "2";
	char					sz3[] = "3";
	CArrayPackedRectangle	macRects;
	CPackedRectangle*		pcPackedRect;
	SInt2					sImageSize;

	cRect1.Init(0, 0, 7, 5);
	cRect2.Init(0, 0, 3, 5);
	cRect3.Init(0, 0, 4, 5);

	cPacker.Init(2, 1);

	cPacker.AddRectangle(&cRect1, sz1);
	cPacker.AddRectangle(&cRect2, sz2);
	cPacker.AddRectangle(&cRect3, sz3);

	cPacker.AddVerticalAttempt();
	cPacker.Pack();

	pcBestAttempt = cPacker.GetBestAttempt();
	macRects.Init();
	pcBestAttempt->GetPackedRectangles(&macRects);

	AssertInt(3, macRects.NumElements());

	pcPackedRect = macRects.Get(0);
	AssertInt(2, pcPackedRect->miLeft);
	AssertInt(2, pcPackedRect->miTop);
	AssertInt(9, pcPackedRect->miRight);
	AssertInt(7, pcPackedRect->miBottom);

	pcPackedRect = macRects.Get(1);
	AssertInt(2, pcPackedRect->miLeft);
	AssertInt(8, pcPackedRect->miTop);
	AssertInt(6, pcPackedRect->miRight);
	AssertInt(13, pcPackedRect->miBottom);

	pcPackedRect = macRects.Get(2);
	AssertInt(2, pcPackedRect->miLeft);
	AssertInt(14, pcPackedRect->miTop);
	AssertInt(5, pcPackedRect->miRight);
	AssertInt(19, pcPackedRect->miBottom);

	sImageSize = pcBestAttempt->GetPackedImageSize();
	AssertInt(11, sImageSize.x);
	AssertInt(21, sImageSize.y);

	macRects.Kill();
	cPacker.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestRectangleBestPacker(void)
{
	BeginTests();

	TestRectanglePackerHorizontalAllSameSize();
	TestRectanglePackerSquareAllSameSize();
	TestRectanglePackerHorizontalPowerOf2Sizes();
	TestRectanglePackerSquarePowerOf2Sizes();
	TestRectanglePackerVerticalPowerOf2Sizes();
	TestRectanglePackerDefault();
	TestRectanglePackerGetPackedRectangles();
	TestRectanglePackerGetPackedRectanglesWithEdges();

	TestStatistics();
}
