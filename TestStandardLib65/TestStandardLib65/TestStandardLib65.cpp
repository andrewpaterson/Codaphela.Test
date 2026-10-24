#include "BaseLib/LeakDetector.h"
#include "BaseLib/FastFunctions.h"
#include "BaseLib/TypeNames.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/NumberControl.h"
#include "TestLib/Assert.h"


void TestStandardLib65Tests(void);


//////////////////////////////////////////////////////////////////////////
//
// StandardLib's own tests (TestStandardLib), compiled from their real source with CppParserLib's 65C64 generator
// and run on MicroprocessorLib's 65C64.
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
	NumberInit();

	TestStandardLib65Tests();

	NumberKill();
	TypeConverterKill();
	FastFunctionsKill();
	TypesKill();

	iTotalTestsFailed = TestTotalStatistics();

	LeakDetection();
	return iTotalTestsFailed;
}

