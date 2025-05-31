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

	mbPrintReset = false;
	mbPrintMnemonic = false;
	mbPrintCycle = false;
	mbPrintOperation = false;
	mbPrintA = false;
	mbPrintX = false;
	mbPrintY = false;
	mbPrintPC = false;
	mbPrintS = false;
	mbPrintDP = false;
	mbPrintDB = false;
	mbPrintP = false;
	muiStartOfPreviousLine = 0;
	muiStartOfPrevPrevLine = 0;
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
void CTestW65C816Context::SetPrint(bool bReset, bool bStop, bool bMnemonic, bool bCycle, bool bOperation, bool bA, bool bX, bool bY, bool bPC, bool bS, bool bDP, bool bDB, bool bP, bool mbMerged)
{
	mbPrintReset = bReset;
	mbPrintStop = bStop;
	mbPrintMnemonic = bMnemonic;
	mbPrintCycle = bCycle;
	mbPrintOperation = bOperation;
	mbPrintA = bA;
	mbPrintX = bX;
	mbPrintY = bY;
	mbPrintPC = bPC;
	mbPrintS = bS;
	mbPrintDP = bDP;
	mbPrintDB = bDB;
	mbPrintP = bP;
	mbPrintMergedCycles = mbMerged;
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
size CTestW65C816Context::GetStartOfPrevPrevLine(void)
{
	return muiStartOfPrevPrevLine;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CTestW65C816Context::SetStartOfPreviousLine(size uiStartOfPreviousLine)
{
	muiStartOfPrevPrevLine = muiStartOfPreviousLine;
	muiStartOfPreviousLine = uiStartOfPreviousLine;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void MergeEndCycleString(CTestW65C816Context* pcContext, bool bFetchOpcode, size uiPreviousStart, CChars* psz)
{
	size	uiPos1;
	size	uiPos2;

	if (pcContext->mbPrintMergedCycles && bFetchOpcode)
	{
		uiPos1 = psz->Find(pcContext->GetStartOfPrevPrevLine(), ':');
		uiPos2 = psz->Find(uiPreviousStart, ':');
		if (uiPos1 != uiPos2)
		{
			psz->Remove(uiPos1, uiPos2);
		}
		else
		{
			psz->Clear();
		}
		uiPreviousStart = psz->Length();
		pcContext->SetStartOfPreviousLine(uiPreviousStart);
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
size CTestW65C816Context::Run(CMetaW65C816* pcMPU)
{
	size		i;
	bool		bRunning;
	size		uiEnd;
	size		uiLength;

	for (i = 0;; i++)
	{
		bRunning = pcMPU->TickInstruction();
		if (!bRunning)
		{
			if (mbPrintMergedCycles && mbPrintStop)
			{
				uiLength = mszSequence.Length();
				uiEnd = mszSequence.FindFromEnd(uiLength-2, '\n');
				mszSequence.Remove(uiEnd, uiLength);
				mszSequence.AppendNewLine();
			}
			break;
		}
	}
	return i;
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
	bool					bReset;
	bool					bStop;
	bool					bFetchOpcode;
	CChars*					psz;
	size					uiPreviousStart;

	pcContext = (CTestW65C816Context*)pvContext;

	bFetchOpcode = pcMPU->IsFetchOpcodeCycle();
	bReset = pcMPU->IsResetInstruction();
	bStop = pcMPU->IsStopInstruction();

	if ((bReset && pcContext->mbPrintReset) ||
		(bStop && pcContext->mbPrintStop) || 
		!bReset && !bStop)
	{
		psz = pcContext->GetSequence();
		uiPreviousStart = psz->Length();
		if (pcContext->mbPrintMergedCycles && bFetchOpcode)
		{
			pcContext->SetStartOfPreviousLine(uiPreviousStart);
		}

		pcMPU->Print(pcContext->GetSequence(),
					 pcContext->mbPrintMnemonic,
					 pcContext->mbPrintCycle,
					 pcContext->mbPrintOperation,
					 pcContext->mbPrintA,
					 pcContext->mbPrintX,
					 pcContext->mbPrintY,
					 pcContext->mbPrintPC,
					 pcContext->mbPrintS,
					 pcContext->mbPrintDP,
					 pcContext->mbPrintDB,
					 pcContext->mbPrintP);
		psz->AppendNewLine();

		MergeEndCycleString(pcContext, bFetchOpcode, uiPreviousStart, psz);
	}

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

