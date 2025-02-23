// TestSupportLib.cpp : Defines the entry point for the console application.
//

#include "BaseLib/FastFunctions.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/TypeNames.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/GlobalMemory.h"
#include "StandardLib/Unknowns.h"
#include "TestLib/Assert.h"


void TestGerberParser(void);


int __cdecl main(void)
{
	InitTotalStatistics();

	FastFunctionsInit();
	TypesInit();
	TypeConverterInit();
	MemoryInit();
	UnknownsInit();

	TestGerberParser();

	UnknownsKill();
	MemoryKill();
	TypeConverterKill();
	TypesKill();
	FastFunctionsKill();
	return TestTotalStatistics();
}

