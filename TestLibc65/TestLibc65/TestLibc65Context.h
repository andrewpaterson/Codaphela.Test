#ifndef __TEST_LIBC65_CONTEXT_H__
#define __TEST_LIBC65_CONTEXT_H__
#include "MicroprocessorLib/65C64Meta.h"
#include "BaseLib/PrimitiveTypes.h"
#include "Assembler65Lib/Asm65Output.h"


#define TEST_LIBC65_LOW_SIZE		0x200000
#define TEST_LIBC65_HIGH_BASE		0xFFFFF000
#define TEST_LIBC65_HIGH_SIZE		0x1000
#define TEST_LIBC65_RESULTS			0x100000
#define TEST_LIBC65_BYTES			0x108000


//Memory for a 65C64 running Libc65: 2MB at 0000:0000 and the vector page at FFFF:F000.  The program is at
//0001:0000, Libc65's heap from 0008:0000 to 000F:FFFF, a test's int results at 0010:0000 (TEST_LIBC65_RESULTS),
//its byte results at 0010:8000 (TEST_LIBC65_BYTES) and the stack from 001F:FFFC down.
class CTestLibc65Memory
{
public:
	uint8	mauiLow[TEST_LIBC65_LOW_SIZE];
	uint8	mauiHigh[TEST_LIBC65_HIGH_SIZE];
	size	muiBadAccesses;

	void	Init(void);
	uint8*	Byte(uint32 uiAddress);
	uint8	GetByte(uint32 uiAddress);
	void	SetByte(uint32 uiAddress, uint8 uiValue);
	uint16	GetWord(uint32 uiAddress);
	uint32	GetLong(uint32 uiAddress);
	void	SetLong(uint32 uiAddress, uint32 uiValue);
	void	Load(CAsm65Output* pcOutput);
};


//A test program and the Libc65 units it is linked with, running from reset.
struct STestLibc65Run
{
	CTestLibc65Memory*	pcMemory;
	C65C64Meta			cMeta;
};


bool	TestLibc65Begin(STestLibc65Run* psRun, const char** aszUnits, const char* szStubs, const char* szSource);
bool	TestLibc65Run(STestLibc65Run* psRun, size uiMaxInstructions);
int32	TestLibc65Return(STestLibc65Run* psRun);
int32	TestLibc65Result(STestLibc65Run* psRun, size uiIndex);
char*	TestLibc65Bytes(STestLibc65Run* psRun, uint32 uiOffset);
void	TestLibc65End(STestLibc65Run* psRun);


#endif // __TEST_LIBC65_CONTEXT_H__

