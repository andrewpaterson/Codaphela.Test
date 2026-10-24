#include "BaseLib/LeakDetector.h"
#include "BaseLib/FastFunctions.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/TypeNames.h"
#include "BaseLib/TypeConverter.h"
#include "BaseLib/GlobalMemory.h"
#include "StandardLib/Unknowns.h"
#include "TestLib/Assert.h"


void TestGateViews(void);
void TestCircuitFile(void);
void TestSimulationState(void);
void TestTextViews(void);
void TestWiring(void);
void TestViewPaths(void);
void TestSubcircuits(void);


int __cdecl main(void)
{
	int iResult;

	BreakOnAllocation(0);
	InitTotalStatistics();

	FastFunctionsInit();
	TypesInit();
	TypeConverterInit();
	MemoryInit();

	TestGateViews();
	TestCircuitFile();
	TestSimulationState();
	TestTextViews();
	TestWiring();
	TestViewPaths();
	TestSubcircuits();

	MemoryKill();
	TypeConverterKill();
	TypesKill();
	FastFunctionsKill();

	iResult = TestTotalStatistics();
	LeakDetection();
	return iResult;
}

