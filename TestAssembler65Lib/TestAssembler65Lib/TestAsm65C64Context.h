#ifndef __TEST_ASM65C64_CONTEXT_H__
#define __TEST_ASM65C64_CONTEXT_H__
#include "BaseLib/PrimitiveTypes.h"
#include "BaseLib/Chars.h"
#include "MicroprocessorLib/Fast65C64.h"
#include "Assembler65Lib/Asm65C64Assembler.h"
#include "Assembler65Lib/Asm65Linker.h"
#include "Assembler65Lib/Asm65Memory.h"


//An assembled program running from reset.
struct STestAsm65Run
{
	CAsm65Memory*	pcContext;
	CFast65C64		cMPU;
	size			uiInstructions;
};


bool		TestAsm65Assemble(CAsm65C64Assembler* pcAssembler, const char* szSource);
bool		TestAsm65AssembleObject(CAsm65Object* pcObject, const char* szSource);
uint16		TestAsm65Word(CAsm65C64Assembler* pcAssembler, uint32 uiAddress);
bool		TestAsm65ReadSource(CChars* pszSource, const char* szFilename);
bool		TestAsm65Begin(STestAsm65Run* psRun, const char* szSource, uint32 uiResetAddress);
bool		TestAsm65BeginFile(STestAsm65Run* psRun, const char* szFilename, uint32 uiResetAddress);
void		TestAsm65BeginOutput(STestAsm65Run* psRun, CAsm65Output* pcOutput, uint32 uiResetAddress);
bool		TestAsm65BeginLinked(STestAsm65Run* psRun, const char* szSource, uint32 uiTextAddress);
size		TestAsm65Run(STestAsm65Run* psRun, size uiMaxInstructions);
CFast65C64*	TestAsm65MPU(STestAsm65Run* psRun);
void		TestAsm65End(STestAsm65Run* psRun);


#endif // __TEST_ASM65C64_CONTEXT_H__
