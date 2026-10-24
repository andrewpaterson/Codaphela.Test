#include <string.h>
#include <stdlib.h>
#include "BaseLib/TextFile.h"
#include "TestLib/Assert.h"
#include "TestAsm65Context.h"


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
// Assembles into an initialised object and asserts there are no errors.
//
//////////////////////////////////////////////////////////////////////////
bool TestAsm65AssembleObject(CAsm65Object* pcObject, const char* szSource)
{
	CAsm65Assembler	cAssembler;
	bool			bResult;

	cAssembler.Init();
	bResult = cAssembler.AssembleObject(szSource, pcObject);
	AssertString("", cAssembler.GetErrors());
	cAssembler.Kill();
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
	psRun->pcContext = (CAsm65Memory*)malloc(sizeof(CAsm65Memory));
	psRun->pcContext->Init();
	psRun->uiInstructions = 0;
	psRun->pcContext->LoadProgram(pcOutput, uiResetAddress);

	psRun->pcContext->InitFast(&psRun->cMPU);
	psRun->cMPU.Reset();
}


//////////////////////////////////////////////////////////////////////////
//
// Assembles an absolute program (one .org) as an object instead, links it with its
// text at uiTextAddress and runs reset at the start of the text.
//
//////////////////////////////////////////////////////////////////////////
bool TestAsm65BeginLinked(STestAsm65Run* psRun, const char* szSource, uint32 uiTextAddress)
{
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
	bResult = TestAsm65AssembleObject(&cObject, szObjectSource.Text());
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

	i = psRun->cMPU.Run(uiMaxInstructions);
	psRun->uiInstructions += i;
	return i;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CFast65C64* TestAsm65MPU(STestAsm65Run* psRun)
{
	return &psRun->cMPU;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65End(STestAsm65Run* psRun)
{
	AssertSize(0, psRun->pcContext->NumBadAccesses());
	psRun->cMPU.Kill();
	free(psRun->pcContext);
}
