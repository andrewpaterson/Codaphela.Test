#include "TestW65C816Context.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CTestW65C816Context::Init(uint32 uiMemorySize, uint8 uiFill)
{
	muiBank = 0;
	mauiMemory = (uint8*)malloc(uiMemorySize);
	mszSequence.Init();
	muiMemorySize = uiMemorySize;
	muiFill = uiFill;
	memset(mauiMemory, uiFill, uiMemorySize);

	mbPrintA = false;
	mbPrintX = false;
	mbPrintY = false;
	mbPrintPC = false;
	mbPrintS = false;
	mbPrintDP = false;
	mbPrintDB = false;
	mbPrintP = false;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CTestW65C816Context::Kill(void)
{
	mszSequence.Kill();
	free(mauiMemory);
	mauiMemory = NULL;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CTestW65C816Context::SetPrint(bool bA, bool bX, bool bY, bool bPC, bool bS, bool bDP, bool bDB, bool bP)
{
	mbPrintA = bA;
	mbPrintX = bX;
	mbPrintY = bY;
	mbPrintPC = bPC;
	mbPrintS = bS;
	mbPrintDP = bDP;
	mbPrintDB = bDB;
	mbPrintP = bP;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
uint8 CTestW65C816Context::GetBank(void)
{
	return muiBank;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CTestW65C816Context::SetBank(uint8 uiBank)
{
	muiBank = uiBank;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
uint8* CTestW65C816Context::GetMemory(void)
{
	return mauiMemory;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
uint8 CTestW65C816Context::GetMemory(uint32 uiAddress)
{
	if (uiAddress < muiMemorySize)
	{
		return mauiMemory[uiAddress];
	}
	else
	{
		return muiFill;
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CTestW65C816Context::SetMemory(uint32 uiAddress, uint8 uiValue)
{
	if (uiAddress < muiMemorySize)
	{
		mauiMemory[uiAddress] = uiValue;
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CChars* CTestW65C816Context::GetSequence(void)
{
	return &mszSequence;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
char* CTestW65C816Context::SequenceText(void)
{
	return mszSequence.Text();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestW65C81ContextTickLow(CMetaW65C816* pcMPU, void* pvContext)
{
	CTestW65C816Context* pcContext;

	pcContext = (CTestW65C816Context*)pvContext;
	pcContext->SetBank(pcMPU->GetData()->Get());
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestW65C81ContextTickHigh(CMetaW65C816* pcMPU, void* pvContext)
{
	uint32					uiAddress;
	bool					bRead;
	bool					bWrite;
	bool					bValidAddress;
	uint8					uiData;
	CTestW65C816Context*	pcContext;

	pcContext = (CTestW65C816Context*)pvContext;

	pcMPU->Print(pcContext->GetSequence(), pcContext->mbPrintA, pcContext->mbPrintX, pcContext->mbPrintY, pcContext->mbPrintPC, pcContext->mbPrintS, pcContext->mbPrintDP, pcContext->mbPrintDB, pcContext->mbPrintP);
	pcContext->GetSequence()->AppendNewLine();

	uiAddress = pcMPU->GetAddress()->Get();
	uiAddress |= pcContext->GetBank() << 16;

	bWrite = pcMPU->GetRWB()->IsLow();
	bRead = pcMPU->GetRWB()->IsHigh();

	bValidAddress = pcMPU->GetVDA()->IsHigh() || pcMPU->GetVPA()->IsHigh();

	if (bValidAddress)
	{
		if (bRead)
		{
			uiData = pcContext->GetMemory(uiAddress);
			pcMPU->GetData()->Set(uiData);
		}
		if (bWrite)
		{
			uiData = pcMPU->GetData()->Get();
			pcContext->SetMemory(uiAddress, uiData);
		}
	}
}

