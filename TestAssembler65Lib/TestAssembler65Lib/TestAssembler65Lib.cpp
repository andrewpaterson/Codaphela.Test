#include "BaseLib/LeakDetector.h"
#include "BaseLib/FastFunctions.h"
#include "BaseLib/TypeNames.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/GlobalMemory.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/NumberControl.h"
#include "MicroprocessorLib/65C64InstructionFactory.h"
#include "StandardLib/Objects.h"
#include "TestLib/Assert.h"


void TestAsm65Tokeniser(void);
void TestAsm65Encoding(void);
void TestAsm65Labels(void);
void TestAsm65Errors(void);
void TestAsm65Programs(void);
void TestAsm65Mandelbrot(void);
void TestAsm65Sieve(void);
void TestAsm65Relocate(void);
void TestAsm65Brainfuck(void);
void TestAsm65Queens(void);
void TestAsm65Base64(void);
void TestAsm65Bignum(void);
void TestAsm65Strings(void);
void TestAsm65Sha256(void);
void TestAsm65Life(void);
void TestAsm65Quicksort(void);
void TestAsm65Object(void);
void TestAsm65Linker(void);


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int __cdecl main(void)
{
	int	iResult;

	BreakOnAllocation(0);
	InitTotalStatistics();

	FastFunctionsInit();
	TypesInit();
	TypeConverterInit();
	NumberInit();
	MemoryInit();
	DataIOInit();
	ObjectsInit();
	C65C64InstructionFactory::GetInstance()->Init();

	TestAsm65Tokeniser();
	TestAsm65Encoding();
	TestAsm65Labels();
	TestAsm65Errors();
	TestAsm65Programs();
	TestAsm65Mandelbrot();
	TestAsm65Sieve();
	TestAsm65Relocate();
	TestAsm65Brainfuck();
	TestAsm65Queens();
	TestAsm65Base64();
	TestAsm65Bignum();
	TestAsm65Strings();
	TestAsm65Sha256();
	TestAsm65Life();
	TestAsm65Quicksort();
	TestAsm65Object();
	TestAsm65Linker();

	C65C64InstructionFactory::GetInstance()->Kill();
	ObjectsKill(false);
	DataIOKill();
	MemoryKill();
	NumberKill();
	TypeConverterKill();
	TypesKill();
	FastFunctionsKill();

	iResult = TestTotalStatistics();
	LeakDetection();
	return iResult;
}
