#include "BaseLib/FastFunctions.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/NaiveFile.h"
#include "BaseLib/LogToMemory.h"
#include "MicroprocessorLib/W65C816.h"
#include "MicroprocessorLib/InstructionFactory.h"
#include "TestLib/Assert.h"


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
void TestW65C816Reset(void)
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
	AssertCycle(&cW65C816, 0);
	AssertCycleName(&cW65C816, "IO");
	cPins.HalfCycle();
	cW65C816.InputTransition(NULL);

	cPins.HalfCycle();
	cW65C816.InputTransition(NULL);
	cPins.HalfCycle();
	cW65C816.InputTransition(NULL);
	cPins.HalfCycle();
	cW65C816.InputTransition(NULL);
	AssertCycle(&cW65C816, 0);

	//Disable reset interrupt.
	cPins.SetRESB(true);
	cPins.HalfCycle();
	cW65C816.InputTransition(NULL);  // <---------  __/¯¯
	AssertOpcodeName(&cW65C816, "RES");
	AssertSignals(&cPins, true, true, true, true);
	AssertPhi2High(&cPins);
	AssertCycle(&cW65C816, 1);
	AssertCycleName(&cW65C816, "IO");

	//Falling edge, start of new cycle.
	cPins.HalfCycle();
	cW65C816.InputTransition(NULL);  // <---------  ¯¯\__
	AssertSignals(&cPins, false, false, true, true);
	AssertOpcodeName(&cW65C816, "RES");
	AssertCycle(&cW65C816, 1);
	AssertCycleName(&cW65C816, "IO");

	AssertPhi2Low(&cPins);
	cPins.HalfCycle();
	AssertPhi2High(&cPins);
	cW65C816.InputTransition(NULL);  // <---------  __/¯¯
	AssertOpcodeName(&cW65C816, "RES");
	AssertCycle(&cW65C816, 2);
	AssertCycleName(&cW65C816, "IO");

	cPins.HalfCycle();
	AssertPhi2Low(&cPins);
	cW65C816.InputTransition(NULL);  // <---------  ¯¯\__
	AssertCycle(&cW65C816, 2);
	AssertOpcodeName(&cW65C816, "RES");
	AssertCycleName(&cW65C816, "IO");
	AssertAddress(&cPins, 0x1ff);

	cPins.HalfCycle();
	cW65C816.InputTransition(NULL);  // <---------  __/¯¯
	AssertOpcodeName(&cW65C816, "RES");
	AssertCycle(&cW65C816, 3);
	AssertCycleName(&cW65C816, "IO");
	AssertAddress(&cPins, 0x1ff);
	cPins.HalfCycle();
	cW65C816.InputTransition(NULL);  // <---------  ¯¯\__
	AssertCycle(&cW65C816, 3);
	AssertAddress(&cPins, 0x1ff);

	cPins.HalfCycle();
	cW65C816.InputTransition(NULL);  // <---------  __/¯¯
	cPins.HalfCycle();
	cW65C816.InputTransition(NULL);  // <---------  ¯¯\__

	cW65C816.Kill();
	CInstructionFactory::GetInstance()->Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestW65C816(void)
{
	TypeConverterInit();
	NumberInit();
	BeginTests();

	DataIOInit();

	TestW65C816OnlyInitAndKill();
	TestW65C816Reset();

	DataIOKill();

	TestStatistics();
	NumberKill();
	TypeConverterKill();
}

