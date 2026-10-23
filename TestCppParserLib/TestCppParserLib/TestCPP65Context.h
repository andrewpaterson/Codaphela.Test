#ifndef __TEST_CPP65_CONTEXT_H__
#define __TEST_CPP65_CONTEXT_H__
#include "MicroprocessorLib/65C64Meta.h"
#include "BaseLib/PrimitiveTypes.h"
#include "BaseLib/Chars.h"
#include "BaseLib/ArrayChars.h"
#include "Assembler65Lib/Asm65Output.h"
#include "CppParserLib/CPP65Generator.h"


#define TEST_CPP65_LOW_SIZE		0x200000
#define TEST_CPP65_HIGH_BASE	0xFFFFF000
#define TEST_CPP65_HIGH_SIZE	0x1000
#define TEST_CPP65_RESULTS		0x100000


//Memory for a 65C64 running compiled code: 2MB at 0000:0000 (pseudo registers below
//0001:0000, the program from 0001:0000, results at 0010:0000 and the stack from
//001F:FFFC down) and the vector page at FFFF:F000.
class CTestCPP65Context
{
public:
	uint8	mauiLow[TEST_CPP65_LOW_SIZE];
	uint8	mauiHigh[TEST_CPP65_HIGH_SIZE];
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


//A compiled program running from reset.
struct STestCPP65Run
{
	CTestCPP65Context*	pcContext;
	C65C64Meta			cMeta;
	size				uiInstructions;
};


bool		TestCPP65Generate(CChars* pszAssembly, CChars* pszErrors, const char* szSource, bool bProgram = false, CArrayChars* paszExternals = NULL);
int			TestCPP65Assemble(const char* szSource, bool bProgram = true);
int			TestCPP65AssembleLibraryFile(const char* szFilename);
bool		TestCPP65Begin(STestCPP65Run* psRun, const char* szSource);
bool		TestCPP65BeginAssembly(STestCPP65Run* psRun, const char* szAssembly);
size		TestCPP65Run(STestCPP65Run* psRun, size uiMaxInstructions);
C65C64*		TestCPP65MPU(STestCPP65Run* psRun);
void		TestCPP65End(STestCPP65Run* psRun);
int32		TestCPP65Main(const char* szSource);
int32		TestCPP65MainFile(const char* szFilename);


#endif // __TEST_CPP65_CONTEXT_H__
