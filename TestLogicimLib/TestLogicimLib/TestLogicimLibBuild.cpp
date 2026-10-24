#include "SupportLib/ColourARGB32.h"
#include "MicroprocessorLib/CircuitSimulation.h"
#include "LogicimLib/LogicimLib.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
// Uses SupportLib and MicroprocessorLib together so a missing library
// shows up as a link error.
//
//////////////////////////////////////////////////////////////////////////
void TestLogicimLibBuildLink(void)
{
	CCircuitSimulation	cSimulation;

	cSimulation.Init("Main");
	AssertString("Main", cSimulation.GetName());
	AssertLong(0, cSimulation.GetTime());
	cSimulation.Kill();

	AssertTrue(Set32BitColour((uint8)0, (uint8)255, (uint8)0, (uint8)255) == 0xFF00FF00);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestLogicimLibBuild(void)
{
	BeginTests();

	TestLogicimLibBuildLink();

	TestStatistics();
}

