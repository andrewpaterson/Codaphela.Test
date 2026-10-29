#include "BaseLib/LeakDetector.h"
#include "BaseLib/TypeNames.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/NumberControl.h"
#include "TestLib/Assert.h"


void TestSupportLib65Tests(void);


//////////////////////////////////////////////////////////////////////////
//
// SupportLib's own tests (TestSupportLib), compiled from their real source with CppParserLib's 65C64 generator
// and run on MicroprocessorLib's 65C64.
//
//////////////////////////////////////////////////////////////////////////
int __cdecl main(void)
{
	int	iTotalTestsFailed;

	BreakOnAllocation(0);
	InitTotalStatistics();

	TypesInit();
	TypeConverterInit();
	NumberInit();

	TestSupportLib65Tests();

	NumberKill();
	TypeConverterKill();
	TypesKill();

	iTotalTestsFailed = TestTotalStatistics();

	LeakDetection();
	return iTotalTestsFailed;
}

