#include "BaseLib/Chars.h"
#include "BaseLib/ConstructorCall.h"
#include "BaseLib/PointerFunctions.h"
#include "Assembler65Lib/Asm65Lockstep.h"
#include "TestLib/Assert.h"
#include "TestAsm65Context.h"


//////////////////////////////////////////////////////////////////////////
//
// The programs run by C65C64 and CFast65C64 side by side, each with its own memory.  The registers must agree
// after every instruction, memory every TEST_ASM65_FAST_MEMORY_STEPS instructions and at the end.
//
//////////////////////////////////////////////////////////////////////////


#define TEST_ASM65_FAST_MEMORY_STEPS	0x4000


//////////////////////////////////////////////////////////////////////////
//
// Runs pcOutput on both until they stop or uiMaxSteps.  Returns the number of steps.
//
//////////////////////////////////////////////////////////////////////////
static size TestAsm65FastLockstep(CAsm65Output* pcOutput, uint32 uiResetAddress, size uiMaxSteps)
{
	CAsm65Memory*	pcMemory;
	CFast65C64		cFast;
	CAsm65Lockstep	cLockstep;
	size			uiSteps;

	pcMemory = NewMalloc<CAsm65Memory>();
	pcMemory->Init();
	pcMemory->LoadProgram(pcOutput, uiResetAddress);
	pcMemory->InitFast(&cFast);
	cFast.Reset();

	cLockstep.Init(pcMemory, &cFast);
	uiSteps = cLockstep.Run(uiMaxSteps, TEST_ASM65_FAST_MEMORY_STEPS);
	AssertString("", cLockstep.GetDifferences());
	cLockstep.Kill();

	cFast.Kill();
	SafeKill(pcMemory);
	return uiSteps;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
static size TestAsm65FastFile(const char* szFilename, uint32 uiResetAddress, size uiMaxSteps)
{
	CChars			szSource;
	CAsm65Assembler	cAssembler;
	size			uiSteps;

	szSource.Init();
	AssertTrue(TestAsm65ReadSource(&szSource, szFilename));
	AssertTrue(TestAsm65Assemble(&cAssembler, szSource.Text()));
	uiSteps = TestAsm65FastLockstep(cAssembler.GetOutput(), uiResetAddress, uiMaxSteps);
	cAssembler.Kill();
	szSource.Kill();
	return uiSteps;
}


//////////////////////////////////////////////////////////////////////////
//
// The programs run to their stp, Mandelbrot for its first 300000 instructions.
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65FastPrograms(void)
{
	AssertTrue(TestAsm65FastFile("Strings.asm", 0x1000, 100000) < 100000);
	AssertTrue(TestAsm65FastFile("Sieve.asm", 0x1000, 1000000) < 1000000);
	AssertTrue(TestAsm65FastFile("Relocate.asm", 0x1000, 10000) < 10000);
	AssertTrue(TestAsm65FastFile("Bignum.asm", 0x1000, 10000000) < 10000000);
	AssertSize(300000, TestAsm65FastFile("Mandelbrot.asm", 0x1000, 300000));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestAsm65Fast(void)
{
	BeginTests();

	TestAsm65FastPrograms();

	TestStatistics();
}

