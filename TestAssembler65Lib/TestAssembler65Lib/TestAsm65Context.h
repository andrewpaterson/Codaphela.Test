#ifndef __TEST_ASM65_CONTEXT_H__
#define __TEST_ASM65_CONTEXT_H__
#include "BaseLib/PrimitiveTypes.h"
#include "BaseLib/Chars.h"
#include "MicroprocessorLib/65C64Meta.h"
#include "Assembler65Lib/Asm65Assembler.h"
#include "Assembler65Lib/Asm65Linker.h"


#define TEST_ASM65_LOW_SIZE		0x200000
#define TEST_ASM65_HIGH_BASE	0xFFFFF000
#define TEST_ASM65_HIGH_SIZE	0x1000


//Memory for a 65C64 running assembled code: 2MB at 0000:0000 (enough for a 400 x 400
//32 bit image at 0010:0000) and the 4KB vector page at FFFF:F000.
class CTestAsm65Context
{
public:
	uint8	mauiLow[TEST_ASM65_LOW_SIZE];
	uint8	mauiHigh[TEST_ASM65_HIGH_SIZE];
	size	muiBadAccesses;
	size	muiCycles;

	void	Init(void);
	uint8*	Byte(uint32 uiAddress);
	uint8	GetByte(uint32 uiAddress);
	void	SetByte(uint32 uiAddress, uint8 uiValue);
	uint16	GetWord(uint32 uiAddress);
	uint32	GetLong(uint32 uiAddress);
	uint64	GetQuad(uint32 uiAddress);
	void	SetLong(uint32 uiAddress, uint32 uiValue);
	void	Load(CAsm65Output* pcOutput);
};


//An assembled program running from reset.
struct STestAsm65Run
{
	CTestAsm65Context*	pcContext;
	C65C64Meta			cMeta;
	size				uiInstructions;
};


bool		TestAsm65Assemble(CAsm65Assembler* pcAssembler, const char* szSource);
uint16		TestAsm65Word(CAsm65Assembler* pcAssembler, uint32 uiAddress);
bool		TestAsm65ReadSource(CChars* pszSource, const char* szFilename);
bool		TestAsm65Begin(STestAsm65Run* psRun, const char* szSource, uint32 uiResetAddress);
bool		TestAsm65BeginFile(STestAsm65Run* psRun, const char* szFilename, uint32 uiResetAddress);
void		TestAsm65BeginOutput(STestAsm65Run* psRun, CAsm65Output* pcOutput, uint32 uiResetAddress);
bool		TestAsm65BeginLinked(STestAsm65Run* psRun, const char* szSource, uint32 uiTextAddress);
size		TestAsm65Run(STestAsm65Run* psRun, size uiMaxInstructions);
C65C64*		TestAsm65MPU(STestAsm65Run* psRun);
void		TestAsm65End(STestAsm65Run* psRun);


#endif // __TEST_ASM65_CONTEXT_H__
