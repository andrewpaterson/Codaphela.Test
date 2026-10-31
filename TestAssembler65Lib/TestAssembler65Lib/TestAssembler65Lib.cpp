#include "BaseLib/LeakDetector.h"
#include "BaseLib/TypeNames.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/GlobalMemory.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/NumberControl.h"
#include "MicroprocessorLib/65C64InstructionFactory.h"
#include "StandardLib/Objects.h"
#include "TestLib/Assert.h"


void TestAsm65Tokeniser(void);
void TestAsm65C64Encoding(void);
void TestAsm65C64Labels(void);
void TestAsm65C64Errors(void);
void TestAsm65C64Programs(void);
void TestAsm65C64Mandelbrot(void);
void TestAsm65C64Sieve(void);
void TestAsm65Relocate(void);
void TestAsm65C64Brainfuck(void);
void TestAsm65C64Queens(void);
void TestAsm65C64Base64(void);
void TestAsm65C64Bignum(void);
void TestAsm65C64Strings(void);
void TestAsm65C64Sha256(void);
void TestAsm65C64Life(void);
void TestAsm65C64Quicksort(void);
void TestAsm65Object(void);
void TestAsm65Linker(void);
void TestAsm65C64Drive(void);
void TestAsm65Lazy(void);
void TestAsm65C64Fast(void);
void TestAsm65816(void);
void TestAsm65IncHex(void);


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int __cdecl main(void)
{
	int	iResult;

	BreakOnAllocation(0);
	InitTotalStatistics();

	TypesInit();
	TypeConverterInit();
	NumberInit();
	MemoryInit();
	DataIOInit();
	ObjectsInit();
	C65C64InstructionFactory::GetInstance()->Init();

	TestAsm65Tokeniser();
	TestAsm65C64Encoding();
	TestAsm65C64Labels();
	TestAsm65C64Errors();
	TestAsm65C64Programs();
	TestAsm65C64Mandelbrot();
	TestAsm65C64Sieve();
	TestAsm65Relocate();
	TestAsm65C64Brainfuck();
	TestAsm65C64Queens();
	TestAsm65C64Base64();
	TestAsm65C64Bignum();
	TestAsm65C64Strings();
	TestAsm65C64Sha256();
	TestAsm65C64Life();
	TestAsm65C64Quicksort();
	TestAsm65Object();
	TestAsm65Linker();
	TestAsm65C64Drive();
	TestAsm65Lazy();
	TestAsm65C64Fast();
	TestAsm65816();
	TestAsm65IncHex();

	C65C64InstructionFactory::GetInstance()->Kill();
	ObjectsKill(false);
	DataIOKill();
	MemoryKill();
	NumberKill();
	TypeConverterKill();
	TypesKill();

	iResult = TestTotalStatistics();
	LeakDetection();
	return iResult;
}
