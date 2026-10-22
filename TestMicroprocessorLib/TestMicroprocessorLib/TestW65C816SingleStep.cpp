#include <stdio.h>
#include "BaseLib/FastFunctions.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/DiskFile.h"
#include "BaseLib/ArraySparseTemplate.h"
#include "MicroprocessorLib/W65C816.h"
#include "MicroprocessorLib/InstructionFactory.h"
#include "MicroprocessorLib/MetaW65C816.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
// Runs the single instruction tests from https://github.com/SingleStepTests/65816
// (MIT licence).  Input/SingleStep holds the first tests of each opcode file, one
// file per opcode and mode (xx.n.bin native, xx.e.bin emulation), converted to
// binary by ConvertSingleStepTests.py.  Each test sets the registers and memory,
// runs one instruction and compares every bus cycle and the final state.
//
//////////////////////////////////////////////////////////////////////////


#define SINGLE_STEP_VDA			0x01
#define SINGLE_STEP_VPA			0x02
#define SINGLE_STEP_VPB			0x04
#define SINGLE_STEP_READ		0x08
#define SINGLE_STEP_E			0x10
#define SINGLE_STEP_M			0x20
#define SINGLE_STEP_X			0x40
#define SINGLE_STEP_MLB			0x80

#define SINGLE_STEP_VALUE_VALID		0x01
#define SINGLE_STEP_ADDRESS_VALID	0x02

#define SINGLE_STEP_MAX_CYCLES	1024


struct SSingleStepCycle
{
	uint32	uiAddress;
	uint8	uiValue;
	uint8	uiSignals;
	uint8	uiValid;
};


struct SSingleStepState
{
	uint16	uiPC;
	uint16	uiS;
	uint8	uiP;
	uint16	uiA;
	uint16	uiX;
	uint16	uiY;
	uint8	uiDBR;
	uint16	uiD;
	uint8	uiPBR;
	uint8	uiE;
	uint16	uiRamCount;
	uint8*	puiRam;  //uint24 address, uint8 value.
};


class CSingleStepReader
{
protected:
	uint8*	mpuiPos;

public:
	void	Init(uint8* puiData)	{ mpuiPos = puiData; }
	uint8	ReadByte(void)			{ return *mpuiPos++; }
	uint16	ReadShort(void)			{ uint16 ui = mpuiPos[0] | (mpuiPos[1] << 8); mpuiPos += 2; return ui; }
	uint32	ReadAddress(void)		{ uint32 ui = mpuiPos[0] | (mpuiPos[1] << 8) | (mpuiPos[2] << 16); mpuiPos += 3; return ui; }
	uint8*	GetPos(void)			{ return mpuiPos; }
	void	Skip(size uiBytes)		{ mpuiPos += uiBytes; }
};


class CTestW65C816SingleStepContext
{
public:
	CArraySparseTemplate<uint8>	mcMemory;
	SSingleStepCycle			masCycles[SINGLE_STEP_MAX_CYCLES];
	size						muiCycles;

	void Init(void)
	{
		mcMemory.Init();
		muiCycles = 0;
	}

	void Kill(void)
	{
		mcMemory.Kill();
	}

	void SetByte(uint32 uiAddress, uint8 uiValue)
	{
		*mcMemory.Set(uiAddress) = uiValue;
	}

	uint8 GetByte(uint32 uiAddress)
	{
		uint8*	puiValue;

		puiValue = mcMemory.Get(uiAddress);
		if (puiValue)
		{
			return *puiValue;
		}
		return 0;
	}
};


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestW65C816SingleStepTickHigh(CMetaW65C816* pcMPU, void* pvContext)
{
	CTestW65C816SingleStepContext*	pcContext;
	SSingleStepCycle*				psCycle;
	bool							bRead;
	bool							bEnabled;

	pcContext = (CTestW65C816SingleStepContext*)pvContext;
	if (pcContext->muiCycles >= SINGLE_STEP_MAX_CYCLES)
	{
		return;
	}

	psCycle = &pcContext->masCycles[pcContext->muiCycles];
	pcContext->muiCycles++;

	psCycle->uiAddress = pcMPU->GetAddress()->Get() | (pcMPU->GetBank() << 16);
	psCycle->uiSignals = 0;
	psCycle->uiSignals |= pcMPU->GetVDA()->IsHigh() ? SINGLE_STEP_VDA : 0;
	psCycle->uiSignals |= pcMPU->GetVPA()->IsHigh() ? SINGLE_STEP_VPA : 0;
	psCycle->uiSignals |= pcMPU->GetVPB()->IsLow() ? SINGLE_STEP_VPB : 0;
	psCycle->uiSignals |= pcMPU->GetRWB()->IsHigh() ? SINGLE_STEP_READ : 0;
	psCycle->uiSignals |= pcMPU->GetE()->IsHigh() ? SINGLE_STEP_E : 0;
	psCycle->uiSignals |= pcMPU->GetMX()->IsHigh() ? SINGLE_STEP_M : 0;
	psCycle->uiSignals |= pcMPU->GetX().IsHigh() ? SINGLE_STEP_X : 0;
	psCycle->uiSignals |= pcMPU->GetMLB()->IsLow() ? SINGLE_STEP_MLB : 0;
	psCycle->uiValid = SINGLE_STEP_ADDRESS_VALID;

	//As in the tests, memory only responds to VDA, VPA or VPB.
	bRead = pcMPU->GetRWB()->IsHigh();
	bEnabled = (psCycle->uiSignals & (SINGLE_STEP_VDA | SINGLE_STEP_VPA | SINGLE_STEP_VPB)) != 0;
	if (bRead)
	{
		if (bEnabled)
		{
			psCycle->uiValue = pcContext->GetByte(psCycle->uiAddress);
			psCycle->uiValid |= SINGLE_STEP_VALUE_VALID;
			pcMPU->GetData()->Set(psCycle->uiValue);
		}
		else
		{
			psCycle->uiValue = 0;
		}
	}
	else
	{
		psCycle->uiValue = pcMPU->GetData()->Get();
		psCycle->uiValid |= SINGLE_STEP_VALUE_VALID;
		if (bEnabled)
		{
			pcContext->SetByte(psCycle->uiAddress, psCycle->uiValue);
		}
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestW65C816SingleStepTickLow(CMetaW65C816* pcMPU, void* pvContext)
{
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestW65C816SingleStepReadState(CSingleStepReader* pcReader, SSingleStepState* psState)
{
	psState->uiPC = pcReader->ReadShort();
	psState->uiS = pcReader->ReadShort();
	psState->uiP = pcReader->ReadByte();
	psState->uiA = pcReader->ReadShort();
	psState->uiX = pcReader->ReadShort();
	psState->uiY = pcReader->ReadShort();
	psState->uiDBR = pcReader->ReadByte();
	psState->uiD = pcReader->ReadShort();
	psState->uiPBR = pcReader->ReadByte();
	psState->uiE = pcReader->ReadByte();
	psState->uiRamCount = pcReader->ReadShort();
	psState->puiRam = pcReader->GetPos();
	pcReader->Skip(psState->uiRamCount * 4);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestW65C816SingleStepAppendHex(CChars* psz, uint32 uiValue, int iDigits)
{
	char	sz[16];

	snprintf(sz, sizeof(sz), "%0*x", iDigits, uiValue);
	psz->Append(sz);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestW65C816SingleStepAppendCycle(CChars* psz, SSingleStepCycle* psCycle)
{
	char	szSignals[9];

	if (psCycle->uiValid & SINGLE_STEP_ADDRESS_VALID)
	{
		TestW65C816SingleStepAppendHex(psz, psCycle->uiAddress, 6);
	}
	else
	{
		psz->Append("------");
	}
	psz->Append(" ");
	if (psCycle->uiValid & SINGLE_STEP_VALUE_VALID)
	{
		TestW65C816SingleStepAppendHex(psz, psCycle->uiValue, 2);
	}
	else
	{
		psz->Append("--");
	}

	szSignals[0] = (psCycle->uiSignals & SINGLE_STEP_VDA) ? 'd' : '-';
	szSignals[1] = (psCycle->uiSignals & SINGLE_STEP_VPA) ? 'p' : '-';
	szSignals[2] = (psCycle->uiSignals & SINGLE_STEP_VPB) ? 'v' : '-';
	szSignals[3] = (psCycle->uiSignals & SINGLE_STEP_READ) ? 'r' : 'w';
	szSignals[4] = (psCycle->uiSignals & SINGLE_STEP_E) ? 'e' : '-';
	szSignals[5] = (psCycle->uiSignals & SINGLE_STEP_M) ? 'm' : '-';
	szSignals[6] = (psCycle->uiSignals & SINGLE_STEP_X) ? 'x' : '-';
	szSignals[7] = (psCycle->uiSignals & SINGLE_STEP_MLB) ? 'l' : '-';
	szSignals[8] = '\0';
	psz->Append(" ");
	psz->Append(szSignals);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
bool TestW65C816SingleStepCompareRegister(CChars* pszError, char* szName, uint32 uiExpected, uint32 uiActual, int iDigits)
{
	if (uiExpected == uiActual)
	{
		return true;
	}
	pszError->Append(szName);
	pszError->Append(" expected ");
	TestW65C816SingleStepAppendHex(pszError, uiExpected, iDigits);
	pszError->Append(" actual ");
	TestW65C816SingleStepAppendHex(pszError, uiActual, iDigits);
	return false;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
bool TestW65C816SingleStepCompareCycles(CChars* pszError, SSingleStepCycle* pasExpected, size uiExpected, CTestW65C816SingleStepContext* pcContext)
{
	size				i;
	SSingleStepCycle*	psExpected;
	SSingleStepCycle*	psActual;
	bool				bSame;

	for (i = 0; i < uiExpected; i++)
	{
		psExpected = &pasExpected[i];
		if (!(psExpected->uiValid & SINGLE_STEP_ADDRESS_VALID))
		{
			//The bus is floating (after WAI or STP).
			continue;
		}

		psActual = &pcContext->masCycles[i];
		bSame = (psExpected->uiAddress == psActual->uiAddress) && (psExpected->uiSignals == psActual->uiSignals);
		if (psExpected->uiValid & SINGLE_STEP_VALUE_VALID)
		{
			bSame = bSame && (psActual->uiValid & SINGLE_STEP_VALUE_VALID) && (psExpected->uiValue == psActual->uiValue);
		}

		if (!bSame)
		{
			pszError->Append("cycle ");
			pszError->Append((int)i + 1);
			pszError->Append(" expected [");
			TestW65C816SingleStepAppendCycle(pszError, psExpected);
			pszError->Append("] actual [");
			TestW65C816SingleStepAppendCycle(pszError, psActual);
			pszError->Append("]");
			return false;
		}
	}
	return true;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
bool TestW65C816SingleStepCompareState(CChars* pszError, SSingleStepState* psExpected, CW65C816* pcCPU, CTestW65C816SingleStepContext* pcContext)
{
	CSingleStepReader	cReader;
	uint16				i;
	uint32				uiAddress;
	uint8				uiValue;

	if (!TestW65C816SingleStepCompareRegister(pszError, "E", psExpected->uiE, pcCPU->IsEmulation() ? 1 : 0, 1)) return false;
	if (!TestW65C816SingleStepCompareRegister(pszError, "P", psExpected->uiP, pcCPU->GetProcessorRegisterValue(), 2)) return false;
	if (!TestW65C816SingleStepCompareRegister(pszError, "PBR", psExpected->uiPBR, pcCPU->GetProgramCounter()->GetBank(), 2)) return false;
	if (!TestW65C816SingleStepCompareRegister(pszError, "PC", psExpected->uiPC, pcCPU->GetProgramCounter()->GetOffset(), 4)) return false;
	if (!TestW65C816SingleStepCompareRegister(pszError, "A", psExpected->uiA, pcCPU->GetC(), 4)) return false;
	if (!TestW65C816SingleStepCompareRegister(pszError, "X", psExpected->uiX, pcCPU->GetX(), 4)) return false;
	if (!TestW65C816SingleStepCompareRegister(pszError, "Y", psExpected->uiY, pcCPU->GetY(), 4)) return false;
	if (!TestW65C816SingleStepCompareRegister(pszError, "S", psExpected->uiS, pcCPU->GetStackPointer16Bit(), 4)) return false;
	if (!TestW65C816SingleStepCompareRegister(pszError, "D", psExpected->uiD, pcCPU->GetDirectPage(), 4)) return false;
	if (!TestW65C816SingleStepCompareRegister(pszError, "DBR", psExpected->uiDBR, pcCPU->GetDataBank(), 2)) return false;

	cReader.Init(psExpected->puiRam);
	for (i = 0; i < psExpected->uiRamCount; i++)
	{
		uiAddress = cReader.ReadAddress();
		uiValue = cReader.ReadByte();
		if (pcContext->GetByte(uiAddress) != uiValue)
		{
			pszError->Append("ram ");
			TestW65C816SingleStepAppendHex(pszError, uiAddress, 6);
			pszError->Append(" expected ");
			TestW65C816SingleStepAppendHex(pszError, uiValue, 2);
			pszError->Append(" actual ");
			TestW65C816SingleStepAppendHex(pszError, pcContext->GetByte(uiAddress), 2);
			return false;
		}
	}
	return true;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestW65C816SingleStepAppendTest(CChars* psz, SSingleStepState* psInitial, SSingleStepCycle* pasExpected, size uiExpected, CTestW65C816SingleStepContext* pcContext)
{
	size	i;

	psz->Append("\n  initial E.");
	TestW65C816SingleStepAppendHex(psz, psInitial->uiE, 1);
	psz->Append(" P.");
	TestW65C816SingleStepAppendHex(psz, psInitial->uiP, 2);
	psz->Append(" PC.");
	TestW65C816SingleStepAppendHex(psz, psInitial->uiPBR, 2);
	psz->Append(":");
	TestW65C816SingleStepAppendHex(psz, psInitial->uiPC, 4);
	psz->Append(" A.");
	TestW65C816SingleStepAppendHex(psz, psInitial->uiA, 4);
	psz->Append(" X.");
	TestW65C816SingleStepAppendHex(psz, psInitial->uiX, 4);
	psz->Append(" Y.");
	TestW65C816SingleStepAppendHex(psz, psInitial->uiY, 4);
	psz->Append(" S.");
	TestW65C816SingleStepAppendHex(psz, psInitial->uiS, 4);
	psz->Append(" D.");
	TestW65C816SingleStepAppendHex(psz, psInitial->uiD, 4);
	psz->Append(" DBR.");
	TestW65C816SingleStepAppendHex(psz, psInitial->uiDBR, 2);

	for (i = 0; (i < uiExpected) || (i < pcContext->muiCycles); i++)
	{
		psz->Append("\n  ");
		if (i < uiExpected)
		{
			TestW65C816SingleStepAppendCycle(psz, &pasExpected[i]);
		}
		else
		{
			psz->Append("                ");
		}
		psz->Append("  |  ");
		if (i < pcContext->muiCycles)
		{
			TestW65C816SingleStepAppendCycle(psz, &pcContext->masCycles[i]);
		}
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
bool TestW65C816SingleStepRunTest(CSingleStepReader* pcReader, CChars* pszError, bool bWaitOrStop)
{
	SSingleStepState				sInitial;
	SSingleStepState				sFinal;
	SSingleStepCycle				asExpected[SINGLE_STEP_MAX_CYCLES];
	uint16							uiCycles;
	uint16							i;
	CTestW65C816SingleStepContext	cContext;
	CMetaW65C816					cMPU;
	CW65C816*						pcCPU;
	CSingleStepReader				cRam;
	uint32							uiAddress;
	bool							bOpcodeFetch;
	bool							bPassed;

	TestW65C816SingleStepReadState(pcReader, &sInitial);
	TestW65C816SingleStepReadState(pcReader, &sFinal);
	uiCycles = pcReader->ReadShort();
	for (i = 0; i < uiCycles; i++)
	{
		if (i < SINGLE_STEP_MAX_CYCLES)
		{
			asExpected[i].uiAddress = pcReader->ReadAddress();
			asExpected[i].uiValue = pcReader->ReadByte();
			asExpected[i].uiSignals = pcReader->ReadByte();
			asExpected[i].uiValid = pcReader->ReadByte();
		}
		else
		{
			pcReader->Skip(6);
		}
	}
	if (uiCycles > SINGLE_STEP_MAX_CYCLES)
	{
		pszError->Append("too many cycles");
		return false;
	}

	cContext.Init();
	cRam.Init(sInitial.puiRam);
	for (i = 0; i < sInitial.uiRamCount; i++)
	{
		uiAddress = cRam.ReadAddress();
		cContext.SetByte(uiAddress, cRam.ReadByte());
	}

	cMPU.Init(TestW65C816SingleStepTickHigh, TestW65C816SingleStepTickLow, &cContext);
	cMPU.GetRESB()->Set(true);

	pcCPU = cMPU.GetMPU();
	pcCPU->TestSetProcessorStatus(sInitial.uiP, sInitial.uiE != 0);
	pcCPU->TestSetC(sInitial.uiA);
	pcCPU->TestSetX(sInitial.uiX);
	pcCPU->TestSetY(sInitial.uiY);
	pcCPU->TestSetStackPointer(sInitial.uiS);
	pcCPU->TestSetDirectPage(sInitial.uiD);
	pcCPU->TestSetDataBank(sInitial.uiDBR);
	pcCPU->TestSetProgramCounter(sInitial.uiPBR, sInitial.uiPC);
	pcCPU->TestStartInstruction();

	//The first cycle only sets up the opcode fetch, the bus is not driven while it is high.
	cMPU.TestTickCycle();
	cContext.muiCycles = 0;

	bOpcodeFetch = false;
	for (i = 0; i < uiCycles; i++)
	{
		bOpcodeFetch = cMPU.TestTickCycle();
	}

	bPassed = TestW65C816SingleStepCompareCycles(pszError, asExpected, uiCycles, &cContext);
	if (bPassed && !bWaitOrStop && !bOpcodeFetch)
	{
		pszError->Append("instruction is longer than ");
		pszError->Append((int)uiCycles);
		pszError->Append(" cycles");
		bPassed = false;
	}
	if (bPassed)
	{
		bPassed = TestW65C816SingleStepCompareState(pszError, &sFinal, pcCPU, &cContext);
	}

	if (!bPassed)
	{
		TestW65C816SingleStepAppendTest(pszError, &sInitial, asExpected, uiCycles, &cContext);
	}

	cMPU.Kill();
	cContext.Kill();
	return bPassed;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestW65C816SingleStepFile(uint8 uiOpcode, char cMode)
{
	CChars				szFilename;
	CChars				szName;
	CChars				szExpected;
	CChars				szActual;
	CChars				szError;
	CChars				szTestError;
	CFileUtil			cFileUtil;
	CDiskFile			cDisk;
	CFileBasic			cFile;
	uint8*				puiData;
	size				uiSize;
	CSingleStepReader	cReader;
	uint16				uiTests;
	uint16				i;
	uint16				uiPassed;
	uint16				uiFirstFailure;
	bool				bWaitOrStop;

	szName.Init();
	TestW65C816SingleStepAppendHex(&szName, uiOpcode, 2);
	szName.Append('.');
	szName.Append(cMode);

	szFilename.Init();
	cFileUtil.CurrentDirectory(&szFilename);
	cFileUtil.AppendToPath(&szFilename, "Input");
	cFileUtil.AppendToPath(&szFilename, "SingleStep");
	cFileUtil.AppendToPath(&szFilename, szName.Text());
	szFilename.Append(".bin");

	szExpected.Init();
	szActual.Init();
	szError.Init();

	cDisk.Init(szFilename);
	cFile.Init(&cDisk);
	if (!cFile.Open(EFM_Read))
	{
		cFile.Kill();
		cDisk.Kill();
		szActual.Append(szName);
		szActual.Append(": missing ");
		szActual.Append(szFilename);
		AssertString(szName.Text(), szActual.Text());
		szActual.Kill();
		szExpected.Kill();
		szError.Kill();
		szFilename.Kill();
		szName.Kill();
		return;
	}

	uiSize = (size)cDisk.Size();
	puiData = (uint8*)malloc(uiSize);
	cFile.Read(puiData, uiSize, 1);
	cFile.Close();
	cFile.Kill();
	cDisk.Kill();

	cReader.Init(puiData);
	cReader.Skip(4);  //"S816"
	cReader.ReadShort();  //Version.
	uiTests = cReader.ReadShort();

	bWaitOrStop = (uiOpcode == WAI_Implied) || (uiOpcode == STP_Implied);
	uiPassed = 0;
	uiFirstFailure = 0;
	szTestError.Init();
	for (i = 0; i < uiTests; i++)
	{
		szTestError.Clear();
		if (TestW65C816SingleStepRunTest(&cReader, &szTestError, bWaitOrStop))
		{
			uiPassed++;
		}
		else if (uiFirstFailure == 0)
		{
			uiFirstFailure = i + 1;
			szError.Append(szTestError);
		}
	}
	szTestError.Kill();
	free(puiData);

	//One assert per file: "xx.n: 200/200" or the first failure.
	szExpected.Append(szName);
	szExpected.Append(": ");
	szExpected.Append((int)uiTests);
	szExpected.Append('/');
	szExpected.Append((int)uiTests);

	szActual.Append(szName);
	szActual.Append(": ");
	szActual.Append((int)uiPassed);
	szActual.Append('/');
	szActual.Append((int)uiTests);
	if (uiPassed != uiTests)
	{
		szActual.Append(" first failure test ");
		szActual.Append((int)uiFirstFailure);
		szActual.Append(": ");
		szActual.Append(szError);
	}
	AssertString(szExpected.Text(), szActual.Text());

	szError.Kill();
	szActual.Kill();
	szExpected.Kill();
	szFilename.Kill();
	szName.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestW65C816SingleStep(void)
{
	int		iOpcode;

	TypeConverterInit();
	NumberInit();
	BeginTests();

	DataIOInit();
	CInstructionFactory::GetInstance()->Init();

	for (iOpcode = 0; iOpcode < 256; iOpcode++)
	{
		TestW65C816SingleStepFile((uint8)iOpcode, 'n');
		TestW65C816SingleStepFile((uint8)iOpcode, 'e');
	}

	CInstructionFactory::GetInstance()->Kill();
	DataIOKill();

	TestStatistics();
	NumberKill();
	TypeConverterKill();
}

