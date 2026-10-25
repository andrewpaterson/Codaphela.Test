#include <string.h>
#include "BaseLib/LeakDetector.h"
#include "BaseLib/FastFunctions.h"
#include "BaseLib/TypeNames.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/NumberControl.h"
#include "MicroprocessorLib/65C64InstructionFactory.h"
#include "TestLib/Assert.h"
#include "TestLibc65Context.h"


void TestLibc65String(void);
void TestLibc65Ctype(void);
void TestLibc65Stdlib(void);
void TestLibc65Time(void);
void TestLibc65Stdarg(void);
void TestLibc65Limits(void);
void TestLibc65SoftFloat(void);


//////////////////////////////////////////////////////////////////////////
//
// Libc65 is compiled with CppParserLib's 65C64 generator and run on MicroprocessorLib's 65C64, or with "816" for
// the W65C816 compiler and run on its fast core.
//
//////////////////////////////////////////////////////////////////////////
int __cdecl main(int argc, char** argv)
{
	int	iTotalTestsFailed;

	if ((argc > 1) && (strcmp(argv[1], "816") == 0))
	{
		geTestLibc65Target = CPPT_W65C816;
	}
	BreakOnAllocation(0);
	InitTotalStatistics();

	TypesInit();
	FastFunctionsInit();
	TypeConverterInit();
	NumberInit();
	C65C64InstructionFactory::GetInstance()->Init();

	TestLibc65String();
	TestLibc65Ctype();
	TestLibc65Stdlib();
	TestLibc65Time();
	TestLibc65Stdarg();
	TestLibc65Limits();
	TestLibc65SoftFloat();

	C65C64InstructionFactory::GetInstance()->Kill();
	NumberKill();
	TypeConverterKill();
	FastFunctionsKill();
	TypesKill();

	iTotalTestsFailed = TestTotalStatistics();

	LeakDetection();
	return iTotalTestsFailed;
}

