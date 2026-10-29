#include "BaseLib/LeakDetector.h"
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
void TestTraceAutoConnector(void);
void TestInverterPackageViews(void);
void TestViewPaths(void);
void TestSubcircuits(void);
void TestCircuitEditor(void);


int __cdecl main(void)
{
	int iResult;

	BreakOnAllocation(0);
	InitTotalStatistics();

	TypesInit();
	TypeConverterInit();
	MemoryInit();

	TestGateViews();
	TestCircuitFile();
	TestSimulationState();
	TestTextViews();
	TestWiring();
	TestTraceAutoConnector();
	TestInverterPackageViews();
	TestViewPaths();
	TestSubcircuits();
	TestCircuitEditor();

	MemoryKill();
	TypeConverterKill();
	TypesKill();

	iResult = TestTotalStatistics();
	LeakDetection();
	return iResult;
}

