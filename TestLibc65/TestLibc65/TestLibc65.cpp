#include "BaseLib/LeakDetector.h"
#include "BaseLib/FastFunctions.h"
#include "BaseLib/TypeNames.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/Operators.h"
#include "BaseLib/NumberControl.h"
#include "MicroprocessorLib/65C64InstructionFactory.h"
#include "TestLib/Assert.h"


void TestLibc65String(void);
void TestLibc65Ctype(void);
void TestLibc65Stdlib(void);
void TestLibc65Time(void);
void TestLibc65Stdarg(void);
void TestLibc65Limits(void);


//////////////////////////////////////////////////////////////////////////
//
// Libc65 is compiled with CppParserLib's 65C64 generator and run on MicroprocessorLib's 65C64.
//
//////////////////////////////////////////////////////////////////////////
int __cdecl main(void)
{
	int	iTotalTestsFailed;

	BreakOnAllocation(0);
	InitTotalStatistics();

	TypesInit();
	FastFunctionsInit();
	TypeConverterInit();
	OperatorsInit();
	NumberInit();
	C65C64InstructionFactory::GetInstance()->Init();

	TestLibc65String();
	TestLibc65Ctype();
	TestLibc65Stdlib();
	TestLibc65Time();
	TestLibc65Stdarg();
	TestLibc65Limits();

	C65C64InstructionFactory::GetInstance()->Kill();
	NumberKill();
	OperatorsKill();
	TypeConverterKill();
	FastFunctionsKill();
	TypesKill();

	iTotalTestsFailed = TestTotalStatistics();

	LeakDetection();
	return iTotalTestsFailed;
}

