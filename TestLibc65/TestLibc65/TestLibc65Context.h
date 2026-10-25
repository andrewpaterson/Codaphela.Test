#ifndef __TEST_LIBC65_CONTEXT_H__
#define __TEST_LIBC65_CONTEXT_H__
#include "MicroprocessorLib/Fast65C64.h"
#include "MicroprocessorLib/Fast65C816.h"
#include "BaseLib/PrimitiveTypes.h"
#include "Assembler65Lib/Asm65Memory.h"
#include "CppParserLib/CPPTarget.h"


#define TEST_LIBC65_RESULTS			0x100000
#define TEST_LIBC65_BYTES			0x108000


//A test program and the Libc65 units it is linked with, running from reset in CAsm65Memory.  The program is at
//0001:0000, Libc65's heap from 0008:0000 to 000F:FFFF, a test's results (longs, 32 bits on every target) at
//0010:0000 (TEST_LIBC65_RESULTS),
//its byte results at 0010:8000 (TEST_LIBC65_BYTES) and the stack from 001F:FFFC down (on the W65C816 from the
//target's stack top in bank 0).  The target is geTestLibc65Target: the 65C64 (cMPU) or the W65C816 (cMPU816),
//whose int is 16 bits.
struct STestLibc65Run
{
	CAsm65Memory*	pcMemory;
	CFast65C64		cMPU;
	CFast65C816		cMPU816;
};


extern ECPPTarget	geTestLibc65Target;



bool	TestLibc65Begin(STestLibc65Run* psRun, const char** aszUnits, const char* szStubs, const char* szSource);
bool	TestLibc65Run(STestLibc65Run* psRun, size uiMaxInstructions);
bool	TestLibc65RunToStop(STestLibc65Run* psRun, size uiMaxInstructions);
int32	TestLibc65Return(STestLibc65Run* psRun);
int32	TestLibc65Result(STestLibc65Run* psRun, size uiIndex);
char*	TestLibc65Bytes(STestLibc65Run* psRun, uint32 uiOffset);
void	TestLibc65End(STestLibc65Run* psRun);


#endif // __TEST_LIBC65_CONTEXT_H__

