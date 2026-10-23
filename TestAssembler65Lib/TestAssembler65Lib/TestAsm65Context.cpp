#include <string.h>
#include <stdlib.h>
#include "BaseLib/TextFile.h"
#include "TestLib/Assert.h"
#include "TestAsm65Context.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CTestAsm65Context::Init(void)
{
	memset(mauiLow, 0, sizeof(mauiLow));
	memset(mauiHigh, 0, sizeof(mauiHigh));
	muiBadAccesses = 0;
	muiCycles = 0;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
uint8* CTestAsm65Context::Byte(uint32 uiAddress)
{
	if (uiAddress < TEST_ASM65_LOW_SIZE)
	{
		return &mauiLow[uiAddress];
	}
	if (uiAddress >= TEST_ASM65_HIGH_BASE)
	{
		return &mauiHigh[uiAddress - TEST_ASM65_HIGH_BASE];
	}
	return NULL;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
uint8 CTestAsm65Context::GetByte(uint32 uiAddress)
{
	uint8*	puiByte;

	puiByte = Byte(uiAddress);
	if (puiByte)
	{
		return *puiByte;
	}
	muiBadAccesses++;
	return 0;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CTestAsm65Context::SetByte(uint32 uiAddress, uint8 uiValue)
{
	uint8*	puiByte;

	puiByte = Byte(uiAddress);
	if (puiByte)
	{
		*puiByte = uiValue;
	}
	else
	{
		muiBadAccesses++;
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
uint16 CTestAsm65Context::GetWord(uint32 uiAddress)
{
	return (uint16)(GetByte(uiAddress) | (GetByte(uiAddress + 1) << 8));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
uint32 CTestAsm65Context::GetLong(uint32 uiAddress)
{
	return (uint32)GetWord(uiAddress) | ((uint32)GetWord(uiAddress + 2) << 16);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
uint64 CTestAsm65Context::GetQuad(uint32 uiAddress)
{
	return (uint64)GetLong(uiAddress) | ((uint64)GetLong(uiAddress + 4) << 32);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CTestAsm65Context::SetLong(uint32 uiAddress, uint32 uiValue)
{
	int	i;

	for (i = 0; i < 4; i++)
	{
		SetByte(uiAddress + i, (uint8)(uiValue >> (8 * i)));
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CTestAsm65Context::Load(CAsm65Output* pcOutput)
{
	size			i;
	size			j;
	SAsm65Segment*	psSegment;

	for (i = 0; i < pcOutput->NumSegments(); i++)
	{
		psSegment = pcOutput->GetSegment(i);
		for (j = 0; j < psSegment->cBytes.NumElements(); j++)
		{
			SetByte(psSegment->uiAddress + (uint32)j, psSegment->cBytes.GetValue(j));
		}
	}
}


//////////////////////////////////////////////////////////////////////////
//
// Memory responds while PHI2 is high.
//
//////////////////////////////////////////////////////////////////////////
static void TestAsm65TickHigh(C65C64Meta* pcMPU, void* pvContext)
{
	CTestAsm65Context*	pcContext;
	uint32				uiAddress;
	uint16				uiData;

	pcContext = (CTestAsm65Context*)pvContext;
	if (!pcMPU->GetRWB()->IsHigh() && !pcMPU->GetRWB()->IsLow())
	{
		return;
	}
	if (!pcMPU->GetVPA()->IsHigh() && !pcMPU->GetVDA()->IsHigh() && pcMPU->GetVPB()->IsHigh())
	{
		return;
	}

	uiAddress = pcMPU->GetAddress()->Get();
	if (pcMPU->GetRWB()->IsHigh())
	{
		pcMPU->GetData()->Set(pcContext->GetWord(uiAddress));
	}
	else
	{
		uiData = pcMPU->GetData()->Get();
		if (pcMPU->GetLowerByte()->IsHigh())
		{
			pcContext->SetByte(uiAddress, (uint8)uiData);
		}
		if (pcMPU->GetUpperByte()->IsHigh())
		{
			pcContext->SetByte(uiAddress + 1, (uint8)(uiData >> 8));
		}
	}
	pcContext->muiCycles++;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
static void TestAsm65TickLow(C65C64Meta* pcMPU, void* pvContext)
{
}


//////////////////////////////////////////////////////////////////////////
//
// Prints the errors when assembling fails.
//
//////////////////////////////////////////////////////////////////////////
bool TestAsm65Assemble(CAsm65Assembler* pcAssembler, const char* szSource)
{
	bool	bResult;

	pcAssembler->Init();
	bResult = pcAssembler->Assemble(szSource);
	AssertString("", pcAssembler->GetErrors());
	return bResult;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
uint16 TestAsm65Word(CAsm65Assembler* pcAssembler, uint32 uiAddress)
{
	return pcAssembler->GetOutput()->GetWord(uiAddress);
}


//////////////////////////////////////////////////////////////////////////
//
// Appends the assembly source in Input/szFilename to pszSource.
//
//////////////////////////////////////////////////////////////////////////
bool TestAsm65ReadSource(CChars* pszSource, const char* szFilename)
{
	CTextFile	cFile;
	CChars		szPath;
	bool		bResult;

	szPath.Init("Input" _FS_);
	szPath.Append(szFilename);
	cFile.Init();
	bResult = cFile.Read(szPath.Text());
	AssertTrue(bResult);
	if (bResult)
	{
		cFile.PassifyNewlines();
		pszSource->Append(cFile.Text());
	}
	cFile.Kill();
	szPath.Kill();
	return bResult;
}


//////////////////////////////////////////////////////////////////////////
//
// Assembles the source, loads it and runs reset.
//
//////////////////////////////////////////////////////////////////////////
bool TestAsm65Begin(STestAsm65Run* psRun, const char* szSource, uint32 uiResetAddress)
{
	CAsm65Assembler	cAssembler;
	bool			bResult;

	bResult = TestAsm65Assemble(&cAssembler, szSource);
	TestAsm65BeginOutput(psRun, cAssembler.GetOutput(), uiResetAddress);
	cAssembler.Kill();
	return bResult;
}


//////////////////////////////////////////////////////////////////////////
//
// Loads assembled or linked bytes and runs reset.
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65BeginOutput(STestAsm65Run* psRun, CAsm65Output* pcOutput, uint32 uiResetAddress)
{
	psRun->pcContext = (CTestAsm65Context*)malloc(sizeof(CTestAsm65Context));
	psRun->pcContext->Init();
	psRun->pcContext->SetLong(VECTOR_65C64_BASE + 4 * VECTOR_65C64_RESET, uiResetAddress);
	psRun->uiInstructions = 0;

	psRun->pcContext->Load(pcOutput);

	psRun->cMeta.Init(TestAsm65TickHigh, TestAsm65TickLow, psRun->pcContext);
	psRun->cMeta.TickInstruction();
	psRun->pcContext->muiCycles = 0;
}


//////////////////////////////////////////////////////////////////////////
//
// Assembles an absolute program (one .org) as an object instead, links it with its
// text at uiTextAddress and runs reset at the start of the text.
//
//////////////////////////////////////////////////////////////////////////
bool TestAsm65BeginLinked(STestAsm65Run* psRun, const char* szSource, uint32 uiTextAddress)
{
	CAsm65Assembler	cAssembler;
	CAsm65Object	cObject;
	CAsm65Linker	cLinker;
	CChars			szObjectSource;
	size			uiOrigin;
	size			uiEnd;
	bool			bResult;

	szObjectSource.Init(szSource);
	uiOrigin = szObjectSource.Find(0, ".org");
	AssertTrue(uiOrigin < szObjectSource.Length());
	uiEnd = szObjectSource.Find(uiOrigin, '\n');
	szObjectSource.Kill();

	szObjectSource.Init();
	szObjectSource.AppendSubString(szSource, 0, uiOrigin);
	szObjectSource.Append(".section text");
	szObjectSource.Append(&szSource[uiEnd]);

	cObject.Init("program");
	cAssembler.Init();
	bResult = cAssembler.AssembleObject(szObjectSource.Text(), &cObject);
	AssertString("", cAssembler.GetErrors());
	cAssembler.Kill();
	szObjectSource.Kill();

	cLinker.Init();
	cLinker.SetAddress(ASK65_Text, uiTextAddress);
	cLinker.AddObject(&cObject);
	bResult &= cLinker.Link();
	AssertString("", cLinker.GetErrors());
	TestAsm65BeginOutput(psRun, cLinker.GetOutput(), uiTextAddress);
	cLinker.Kill();
	cObject.Kill();
	return bResult;
}


//////////////////////////////////////////////////////////////////////////
//
// Assembles the source in Input/szFilename and resets the processor to run it.
//
//////////////////////////////////////////////////////////////////////////
bool TestAsm65BeginFile(STestAsm65Run* psRun, const char* szFilename, uint32 uiResetAddress)
{
	CChars	szSource;
	bool	bResult;

	szSource.Init();
	bResult = TestAsm65ReadSource(&szSource, szFilename);
	bResult &= TestAsm65Begin(psRun, szSource.Text(), uiResetAddress);
	szSource.Kill();
	return bResult;
}


//////////////////////////////////////////////////////////////////////////
//
// Runs until the processor stops.  Returns the number of instructions.
//
//////////////////////////////////////////////////////////////////////////
size TestAsm65Run(STestAsm65Run* psRun, size uiMaxInstructions)
{
	size	i;

	for (i = 0; i < uiMaxInstructions; i++)
	{
		if (!psRun->cMeta.TickInstruction())
		{
			psRun->uiInstructions += i + 1;
			return i + 1;
		}
	}
	psRun->uiInstructions += i;
	return i;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
C65C64* TestAsm65MPU(STestAsm65Run* psRun)
{
	return psRun->cMeta.GetMPU();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65End(STestAsm65Run* psRun)
{
	AssertSize(0, psRun->pcContext->muiBadAccesses);
	psRun->cMeta.Kill();
	free(psRun->pcContext);
}
