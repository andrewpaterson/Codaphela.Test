// TestSupportLib.cpp : Defines the entry point for the console application.
//

#include "BaseLib/FastFunctions.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/TypeNames.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/GlobalMemory.h"
#include "StandardLib/Unknowns.h"
#include "MicroprocessorLib/MetaTrace.h"
#include "TestLib/Assert.h"


void TestW65C816Reset(void);
void TestW65C816Add(void);
void TestW65C816Subtract(void);
void TestW65C816Arithmetic(void);
void TestW65C816Load(void);


int __cdecl main(void)
{
	int iResult;

	_CrtSetBreakAlloc(0);
	InitTotalStatistics();

	FastFunctionsInit();
	TypesInit();
	TypeConverterInit();
	MemoryInit();
	UnknownsInit();
	gcMetaTraceUndriven.Init();

	TestW65C816Reset();
	TestW65C816Add();
	TestW65C816Subtract();
	TestW65C816Load();
	//TestW65C816Arithmetic();

	UnknownsKill();
	MemoryKill();
	TypeConverterKill();
	TypesKill();
	FastFunctionsKill();

	iResult = TestTotalStatistics();
	_CrtDumpMemoryLeaks();
	return iResult;
}

