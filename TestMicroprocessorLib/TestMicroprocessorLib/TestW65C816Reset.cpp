#include "BaseLib/FastFunctions.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/NaiveFile.h"
#include "BaseLib/LogToMemory.h"
#include "MicroprocessorLib/W65C816.h"
#include "MicroprocessorLib/InstructionFactory.h"
#include "TestLib/Assert.h"


void TestW65C816Reset(CW65C816* pcW65C816, CMetaTrace* pcPhi2, CMetaTrace* pcVPA, CMetaTrace* pcVDA, CMetaTrace* pcVPB, CMetaTrace* pcRWB);


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
void AssertAddress(CW65C816Pins* pcW65C816, CTimeline* pcTimeline, uint16 uiAddress)
{
	uint16	uiPinsAddress;

	uiPinsAddress = pcW65C816->ReadAddress(pcTimeline);
	AssertShortHex(uiAddress, uiPinsAddress);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertData(CW65C816Pins* pcW65C816, CTimeline* pcTimeline, uint8 uiData)
{
	uint8	uiPinsData;

	uiPinsData = pcW65C816->ReadData(pcTimeline);
	AssertByteHex(uiData, uiPinsData);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertSignals(bool bVPA, bool bVDA, bool bVPB, bool bRWB, CMetaTrace* pcVPA, CMetaTrace* pcVDA, CMetaTrace* pcVPB ,CMetaTrace* pcRWB)
{
	bool bPinsVPA;
	bool bPinsVDA;
	bool bPinsVPB;
	bool bPinsRWB;

	bPinsVPA = pcVPA->Get().IsHigh();
	bPinsVDA = pcVDA->Get().IsHigh();
	bPinsVPB = pcVPB->Get().IsHigh();
	bPinsRWB = pcRWB->Get().IsHigh();

	AssertBool(bVPA, bPinsVPA);
	AssertBool(bVDA, bPinsVDA);
	AssertBool(bVPB, bPinsVPB);
	AssertBool(bRWB, bPinsRWB);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertPhi2Low(CMetaTrace* pcPhi2)
{
	AssertTrue(pcPhi2->Get().IsLow());
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertPhi2High(CMetaTrace* pcPhi2)
{
	AssertTrue(pcPhi2->Get().IsHigh());
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestW65C816OnlyInitAndKill(void)
{
	CW65C816		cW65C816;
	CW65C816Pins	cPins;
	CMetaBus8		cData;
	CMetaBus16		cAddress;
	CMetaTrace		cPhi2;
	CMetaTrace		cResB;
	CMetaTrace		cRWB;

	CInstructionFactory::GetInstance()->Init();

	cData.Init();
	cAddress.Init();
	cPhi2.Init(false);
	cResB.Init(false);
	cRWB.Init();

	cPins.Init(&cAddress, &cData, &cPhi2, &cResB, &cRWB);
	cW65C816.Init(&cPins);
	cW65C816.Kill();

	cPhi2.Kill();
	cResB.Kill();
	cRWB.Kill();
	cAddress.Kill();
	cData.Kill();
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
	CMetaBus8		cData;
	CMetaBus16		cAddress;
	CMetaTrace		cPhi2;
	CMetaTrace		cResB;
	CMetaTrace		cRWB;
	CMetaTrace		cVPA;
	CMetaTrace		cVDA;
	CMetaTrace		cVPB;

	CInstructionFactory::GetInstance()->Init();

	cData.Init();
	cAddress.Init();
	cPhi2.Init(false);
	cResB.Init(false);
	cRWB.Init();
	cVPA.Init();
	cVDA.Init();
	cVPB.Init();

	cPins.Init(&cAddress, &cData, &cPhi2, &cResB, &cRWB);
	cPins.SetImportantTraces(&cVPA, &cVDA, &cVPB);
	cW65C816.Init(&cPins);
	AssertOpcodeName(&cW65C816, "---");
	AssertCycleName(&cW65C816, "---");

	cW65C816.InputTransition(NULL);
	AssertOpcodeName(&cW65C816, "RES");
	AssertCycle(&cW65C816, 1);
	AssertCycleName(&cW65C816, "IO");
	cPhi2.Invert();
	cW65C816.InputTransition(NULL);

	cPhi2.Invert();
	cW65C816.InputTransition(NULL);
	cPhi2.Invert();
	cW65C816.InputTransition(NULL);
	AssertCycle(&cW65C816, 1);

	//Disable reset interrupt.
	//Falling edge, start of new cycle.
	cResB.Set(true);
	cPhi2.Invert();
	cW65C816.InputTransition(NULL);  // <---------  ¯¯\__
	AssertOpcodeName(&cW65C816, "RES");
	AssertSignals(true, true, true, true, &cVPA, &cVDA, &cVPB, &cRWB);
	AssertPhi2Low(&cPhi2);
	AssertCycle(&cW65C816, 1);
	AssertCycleName(&cW65C816, "IO");
	cPhi2.Invert();
	cW65C816.InputTransition(NULL);  // <---------  __/¯¯
	AssertSignals(true, true, true, true, &cVPA, &cVDA, &cVPB, &cRWB);
	AssertOpcodeName(&cW65C816, "RES");
	AssertCycle(&cW65C816, 1);
	AssertCycleName(&cW65C816, "IO");
	AssertPhi2High(&cPhi2);

	TestW65C816Reset(&cW65C816, &cPhi2, &cVPA, &cVDA, &cVPB, &cRWB);

	cW65C816.Kill();
	cPins.Kill();

	cVPA.Kill();
	cVDA.Kill();
	cVPB.Kill();
	cPhi2.Kill();
	cResB.Kill();
	cRWB.Kill();
	cAddress.Kill();
	cData.Kill();
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
	CMetaBus8		cData;
	CMetaBus16		cAddress;
	CMetaTrace		cPhi2;
	CMetaTrace		cResB;
	CMetaTrace		cRWB;
	CMetaTrace		cVPA;
	CMetaTrace		cVDA;
	CMetaTrace		cVPB;

	CInstructionFactory::GetInstance()->Init();

	cData.Init();
	cAddress.Init();
	cPhi2.Init(false);
	cResB.Init(false);
	cRWB.Init();
	cVPA.Init();
	cVDA.Init();
	cVPB.Init();

	cPins.Init(&cAddress, &cData, &cPhi2, &cResB, &cRWB);
	cPins.SetImportantTraces(&cVPA, &cVDA, &cVPB);
	cW65C816.Init(&cPins);
	AssertOpcodeName(&cW65C816, "---");
	AssertCycleName(&cW65C816, "---");

	cW65C816.InputTransition(NULL);
	AssertOpcodeName(&cW65C816, "RES");
	AssertCycle(&cW65C816, 1);
	AssertCycleName(&cW65C816, "IO");
	cPhi2.Invert();
	cW65C816.InputTransition(NULL);

	cPhi2.Invert();
	cW65C816.InputTransition(NULL);
	cPhi2.Invert();
	cW65C816.InputTransition(NULL);
	cPhi2.Invert();
	cW65C816.InputTransition(NULL);
	AssertCycle(&cW65C816, 1);

	//Disable reset interrupt.
	//Rising edge
	cResB.Set(true);
	cPhi2.Invert();
	cW65C816.InputTransition(NULL);  // <---------  __/¯¯
	AssertOpcodeName(&cW65C816, "RES");
	AssertPhi2High(&cPhi2);
	AssertCycle(&cW65C816, 1);
	AssertCycleName(&cW65C816, "IO");

	//Start of new cycle.
	cPhi2.Invert();
	cW65C816.InputTransition(NULL);  // <---------  ¯¯\__
	AssertSignals(true, true, true, true, &cVPA, &cVDA, &cVPB, &cRWB);
	AssertOpcodeName(&cW65C816, "RES");
	AssertCycle(&cW65C816, 1);
	AssertCycleName(&cW65C816, "IO");
	AssertPhi2Low(&cPhi2);
	cPhi2.Invert();
	cW65C816.InputTransition(NULL);  // <---------  __/¯¯
	AssertSignals(true, true, true, true, &cVPA, &cVDA, &cVPB, &cRWB);
	AssertOpcodeName(&cW65C816, "RES");
	AssertCycle(&cW65C816, 1);
	AssertCycleName(&cW65C816, "IO");
	AssertPhi2High(&cPhi2);

	TestW65C816Reset(&cW65C816, &cPhi2, &cVPA, &cVDA, &cVPB, &cRWB);

	cW65C816.Kill();
	cPins.Kill();

	cVPA.Kill();
	cVDA.Kill();
	cVPB.Kill();
	cPhi2.Kill();
	cResB.Kill();
	cRWB.Kill();
	cAddress.Kill();
	cData.Kill();
	CInstructionFactory::GetInstance()->Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestW65C816Reset(CW65C816* pcW65C816, CMetaTrace* pcPhi2, CMetaTrace* pcVPA, CMetaTrace* pcVDA, CMetaTrace* pcVPB, CMetaTrace* pcRWB)
{
	CW65C816Pins*	pcPins;
	
	pcPins = pcW65C816->GetPins();

	pcPhi2->Invert();
	AssertPhi2Low(pcPhi2);
	pcW65C816->InputTransition(NULL);  // <---------  ¯¯\__
	AssertOpcodeName(pcW65C816, "RES");
	AssertCycle(pcW65C816, 2);
	AssertCycleName(pcW65C816, "IO");
	AssertSignals(false, false, true, true, pcVPA, pcVDA, pcVPB, pcRWB);
	pcPhi2->Invert();
	AssertPhi2High(pcPhi2);
	pcW65C816->InputTransition(NULL);  // <---------  __/¯¯
	AssertCycle(pcW65C816, 2);
	AssertOpcodeName(pcW65C816, "RES");
	AssertCycleName(pcW65C816, "IO");

	pcPhi2->Invert();
	pcW65C816->InputTransition(NULL);  // <---------  ¯¯\__
	AssertOpcodeName(pcW65C816, "RES");
	AssertCycle(pcW65C816, 3);
	AssertCycleName(pcW65C816, "IO");
	AssertAddress(pcPins, NULL, 0x1ff);
	AssertSignals(false, false, true, true, pcVPA, pcVDA, pcVPB, pcRWB);
	pcPhi2->Invert();
	pcW65C816->InputTransition(NULL);  // <---------  __/¯¯
	AssertCycle(pcW65C816, 3);
	AssertAddress(pcPins, NULL, 0x1ff);

	pcPhi2->Invert();
	pcW65C816->InputTransition(NULL);  // <---------  ¯¯\__
	AssertCycle(pcW65C816, 4);
	AssertAddress(pcPins, NULL, 0x1fe);
	AssertSignals(false, false, true, true, pcVPA, pcVDA, pcVPB, pcRWB);
	pcPhi2->Invert();
	pcW65C816->InputTransition(NULL);  // <---------  __/¯¯
	AssertCycle(pcW65C816, 4);
	AssertAddress(pcPins, NULL, 0x1fe);

	pcPhi2->Invert();
	pcW65C816->InputTransition(NULL);  // <---------  ¯¯\__
	AssertCycle(pcW65C816, 5);
	AssertAddress(pcPins, NULL, 0x1fd);
	AssertSignals(false, false, true, true, pcVPA, pcVDA, pcVPB, pcRWB);
	pcPhi2->Invert();
	pcW65C816->InputTransition(NULL);  // <---------  __/¯¯
	AssertCycle(pcW65C816, 5);
	AssertAddress(pcPins, NULL, 0x1fd);

	pcPhi2->Invert();
	pcW65C816->InputTransition(NULL);  // <---------  ¯¯\__
	AssertCycle(pcW65C816, 6);
	AssertAddress(pcPins, NULL, 0xfffc);
	AssertSignals(false, true, false, true, pcVPA, pcVDA, pcVPB, pcRWB);
	pcPhi2->Invert();
	pcW65C816->InputTransition(NULL);  // <---------  __/¯¯
	AssertCycle(pcW65C816, 6);
	AssertAddress(pcPins, NULL, 0xfffc);

	pcPins->WriteData(NULL, 0x34);

	pcPhi2->Invert();
	pcW65C816->InputTransition(NULL);  // <---------  ¯¯\__
	AssertCycle(pcW65C816, 7);
	AssertAddress(pcPins, NULL, 0xfffd);
	AssertSignals(false, true, false, true, pcVPA, pcVDA, pcVPB, pcRWB);
	pcPhi2->Invert();
	pcW65C816->InputTransition(NULL);  // <---------  __/¯¯
	AssertCycle(pcW65C816, 7);
	AssertAddress(pcPins, NULL, 0xfffd);

	pcPins->WriteData(NULL, 0x12);

	pcPhi2->Invert();
	pcW65C816->InputTransition(NULL);  // <---------  ¯¯\__
	AssertCycle(pcW65C816, 1);
	AssertAddress(pcPins, NULL, 0x1234);
	AssertSignals(true, true, true, true, pcVPA, pcVDA, pcVPB, pcRWB);
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

