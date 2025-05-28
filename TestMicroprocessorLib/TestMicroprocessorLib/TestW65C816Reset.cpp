#include "BaseLib/FastFunctions.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/NaiveFile.h"
#include "BaseLib/LogToMemory.h"
#include "MicroprocessorLib/W65C816.h"
#include "MicroprocessorLib/InstructionFactory.h"
#include "TestLib/Assert.h"


void TestW65C816Reset(CW65C816* pcW65C816);


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertOpcodeName(CW65C816* pcW65C816, char* szExpected)
{
	CChars	sz;

	sz.Init();
	pcW65C816->GetOpcodeMnemonicString(&sz);
	AssertString(szExpected, sz.Text());
	sz.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertCycleName(CW65C816* pcW65C816, char* szExpected)
{
	CChars	sz;

	sz.Init();
	pcW65C816->GetCycleOperationString(&sz);
	AssertString(szExpected, sz.Text());
	sz.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertCycle(CW65C816* pcW65C816, int16 iExpected)
{
	AssertShort(iExpected, pcW65C816->GetCycle());
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertAddress(CW65C816Pins* pcW65C816, uint16 uiAddress)
{
	uint16	uiPinsAddress;

	uiPinsAddress = pcW65C816->GetAddress();
	AssertShortHex(uiAddress, uiPinsAddress);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertData(CW65C816Pins* pcW65C816, uint8 uiData)
{
	uint8	uiPinsData;

	uiPinsData = pcW65C816->GetData();
	AssertByteHex(uiData, uiPinsData);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertSignals(CW65C816Pins* pcW65C816, bool bVPA, bool bVDA, bool bVPB, bool bRWB)
{
	bool bPinsVPA;
	bool bPinsVDA;
	bool bPinsVPB;
	bool bPinsRWB;

	bPinsVPA = pcW65C816->GetVPA();
	bPinsVDA = pcW65C816->GetVDA();
	bPinsVPB = pcW65C816->GetVPB();
	bPinsRWB = pcW65C816->GetRWB();

	AssertBool(bVPA, bPinsVPA);
	AssertBool(bVDA, bPinsVDA);
	AssertBool(bVPB, bPinsVPB);
	AssertBool(bRWB, bPinsRWB);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertPhi2Low(CW65C816Pins* pcW65C816)
{
	AssertFalse(pcW65C816->GetPHI2());
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertPhi2High(CW65C816Pins* pcW65C816)
{
	AssertTrue(pcW65C816->GetPHI2());
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestW65C816OnlyInitAndKill(void)
{
	CW65C816		cW65C816;
	CW65C816Pins	cPins;

	CInstructionFactory::GetInstance()->Init();
	cPins.Init();
	cW65C816.Init(&cPins);
	cW65C816.Kill();
	CInstructionFactory::GetInstance()->Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestW65C816ResetReleaseBeforePhi2Falling(void)
{
	CW65C816		cW65C816;
	CW65C816Pins	cPins;

	CInstructionFactory::GetInstance()->Init();

	cPins.Init();
	cW65C816.Init(&cPins);
	cPins.Reset();
	AssertOpcodeName(&cW65C816, "---");
	AssertCycleName(&cW65C816, "---");

	cW65C816.InputTransition(NULL);
	AssertOpcodeName(&cW65C816, "RES");
	AssertCycle(&cW65C816, 1);
	AssertCycleName(&cW65C816, "IO");
	cPins.HalfCycle();
	cW65C816.InputTransition(NULL);

	cPins.HalfCycle();
	cW65C816.InputTransition(NULL);
	cPins.HalfCycle();
	cW65C816.InputTransition(NULL);
	AssertCycle(&cW65C816, 1);

	//Disable reset interrupt.
	//Falling edge, start of new cycle.
	cPins.SetRESB(true);
	cPins.HalfCycle();
	cW65C816.InputTransition(NULL);  // <---------  ¯¯\__
	AssertOpcodeName(&cW65C816, "RES");
	AssertSignals(&cPins, true, true, true, true);
	AssertPhi2Low(&cPins);
	AssertCycle(&cW65C816, 1);
	AssertCycleName(&cW65C816, "IO");
	cPins.HalfCycle();
	cW65C816.InputTransition(NULL);  // <---------  __/¯¯
	AssertSignals(&cPins, true, true, true, true);
	AssertOpcodeName(&cW65C816, "RES");
	AssertCycle(&cW65C816, 1);
	AssertCycleName(&cW65C816, "IO");
	AssertPhi2High(&cPins);

	TestW65C816Reset(&cW65C816);

	cW65C816.Kill();
	CInstructionFactory::GetInstance()->Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestW65C816ResetReleaseBeforePhi2Rising(void)
{
	CW65C816		cW65C816;
	CW65C816Pins	cPins;

	CInstructionFactory::GetInstance()->Init();

	cPins.Init();
	cW65C816.Init(&cPins);
	cPins.Reset();
	AssertOpcodeName(&cW65C816, "---");
	AssertCycleName(&cW65C816, "---");

	cW65C816.InputTransition(NULL);
	AssertOpcodeName(&cW65C816, "RES");
	AssertCycle(&cW65C816, 1);
	AssertCycleName(&cW65C816, "IO");
	cPins.HalfCycle();
	cW65C816.InputTransition(NULL);

	cPins.HalfCycle();
	cW65C816.InputTransition(NULL);
	cPins.HalfCycle();
	cW65C816.InputTransition(NULL);
	cPins.HalfCycle();
	cW65C816.InputTransition(NULL);
	AssertCycle(&cW65C816, 1);

	//Disable reset interrupt.
	//Rising edge
	cPins.SetRESB(true);
	cPins.HalfCycle();
	cW65C816.InputTransition(NULL);  // <---------  __/¯¯
	AssertOpcodeName(&cW65C816, "RES");
	AssertPhi2High(&cPins);
	AssertCycle(&cW65C816, 1);
	AssertCycleName(&cW65C816, "IO");

	//Start of new cycle.
	cPins.HalfCycle();
	cW65C816.InputTransition(NULL);  // <---------  ¯¯\__
	AssertSignals(&cPins, true, true, true, true);
	AssertOpcodeName(&cW65C816, "RES");
	AssertCycle(&cW65C816, 1);
	AssertCycleName(&cW65C816, "IO");
	AssertPhi2Low(&cPins);
	cPins.HalfCycle();
	cW65C816.InputTransition(NULL);  // <---------  __/¯¯
	AssertSignals(&cPins, true, true, true, true);
	AssertOpcodeName(&cW65C816, "RES");
	AssertCycle(&cW65C816, 1);
	AssertCycleName(&cW65C816, "IO");
	AssertPhi2High(&cPins);
	TestW65C816Reset(&cW65C816);

	cW65C816.Kill();
	CInstructionFactory::GetInstance()->Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestW65C816Reset(CW65C816* pcW65C816)
{
	CW65C816Pins*	pcPins;
	
	pcPins = pcW65C816->GetPins();

	pcPins->HalfCycle();
	AssertPhi2Low(pcPins);
	pcW65C816->InputTransition(NULL);  // <---------  ¯¯\__
	AssertOpcodeName(pcW65C816, "RES");
	AssertCycle(pcW65C816, 2);
	AssertCycleName(pcW65C816, "IO");
	pcPins->HalfCycle();
	AssertPhi2High(pcPins);
	pcW65C816->InputTransition(NULL);  // <---------  __/¯¯
	AssertCycle(pcW65C816, 2);
	AssertOpcodeName(pcW65C816, "RES");
	AssertCycleName(pcW65C816, "IO");

	pcPins->HalfCycle();
	pcW65C816->InputTransition(NULL);  // <---------  ¯¯\__
	AssertOpcodeName(pcW65C816, "RES");
	AssertCycle(pcW65C816, 3);
	AssertCycleName(pcW65C816, "IO");
	AssertAddress(pcPins, 0x1ff);
	pcPins->HalfCycle();
	pcW65C816->InputTransition(NULL);  // <---------  __/¯¯
	AssertCycle(pcW65C816, 3);
	AssertAddress(pcPins, 0x1ff);

	pcPins->HalfCycle();
	pcW65C816->InputTransition(NULL);  // <---------  ¯¯\__
	AssertCycle(pcW65C816, 4);
	AssertAddress(pcPins, 0x1fe);
	pcPins->HalfCycle();
	pcW65C816->InputTransition(NULL);  // <---------  __/¯¯
	AssertCycle(pcW65C816, 4);
	AssertAddress(pcPins, 0x1fe);

	pcPins->HalfCycle();
	pcW65C816->InputTransition(NULL);  // <---------  ¯¯\__
	AssertCycle(pcW65C816, 5);
	AssertAddress(pcPins, 0x1fd);
	pcPins->HalfCycle();
	pcW65C816->InputTransition(NULL);  // <---------  __/¯¯
	AssertCycle(pcW65C816, 5);
	AssertAddress(pcPins, 0x1fd);

	pcPins->HalfCycle();
	pcW65C816->InputTransition(NULL);  // <---------  ¯¯\__
	AssertCycle(pcW65C816, 6);
	AssertAddress(pcPins, 0xfffc);
	pcPins->HalfCycle();
	pcW65C816->InputTransition(NULL);  // <---------  __/¯¯
	AssertCycle(pcW65C816, 6);
	AssertAddress(pcPins, 0xfffc);

	pcPins->SetData(0x34);

	pcPins->HalfCycle();
	pcW65C816->InputTransition(NULL);  // <---------  ¯¯\__
	AssertCycle(pcW65C816, 7);
	AssertAddress(pcPins, 0xfffd);
	pcPins->HalfCycle();
	pcW65C816->InputTransition(NULL);  // <---------  __/¯¯
	AssertCycle(pcW65C816, 7);
	AssertAddress(pcPins, 0xfffd);

	pcPins->SetData(0x12);

	pcPins->HalfCycle();
	pcW65C816->InputTransition(NULL);  // <---------  ¯¯\__
	AssertCycle(pcW65C816, 1);
	AssertAddress(pcPins, 0x1234);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestW65C816ResetVector(void)
{

}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestW65C816Reset(void)
{
	TypeConverterInit();
	NumberInit();
	BeginTests();

	DataIOInit();

	TestW65C816OnlyInitAndKill();
	TestW65C816ResetReleaseBeforePhi2Falling();
	TestW65C816ResetReleaseBeforePhi2Rising();
	TestW65C816ResetVector();

	DataIOKill();

	TestStatistics();
	NumberKill();
	TypeConverterKill();
}

