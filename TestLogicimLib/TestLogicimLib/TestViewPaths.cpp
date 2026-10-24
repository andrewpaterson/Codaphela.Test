#include "BaseLib/ConstructorCall.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/Logger.h"
#include "StandardLib/Objects.h"
#include "MicroprocessorLib/CircuitSimulation.h"
#include "MicroprocessorLib/FamilyVoltageConfigurationStore.h"
#include "MicroprocessorLib/Trace.h"
#include "MicroprocessorLib/Event.h"
#include "MicroprocessorLib/Timeline.h"
#include "MicroprocessorLib/Voltage.h"
#include "LogicimLib/BufferView.h"
#include "LogicimLib/PowerSourceView.h"
#include "LogicimLib/CircuitView.h"
#include "LogicimLib/ViewPath.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
// A circuit is the only view on its top path.  The path has a subcircuit
// simulation for each circuit simulation it's simulated in.
//
//////////////////////////////////////////////////////////////////////////
void TestViewPathTop(void)
{
	CViewPaths				cPaths;
	CCircuitView			cCircuit;
	CCircuitView			cOther;
	CCircuitSimulation		cFirst;
	CCircuitSimulation		cSecond;
	CViewPath*				pcPath;
	CViewPath*				pcOtherPath;
	CChars					sz;
	SLogConfig				sLogConfig;

	ObjectsInit();
	CViewPath::ResetNextID();
	cCircuit.Init();
	cOther.Init();
	cPaths.Init();
	cFirst.Init("First");
	cSecond.Init("Second");

	pcPath = cPaths.AddTop(&cCircuit);
	AssertNotNull(pcPath);
	AssertTrue(pcPath->IsTop());
	AssertSize(1, pcPath->Length());
	AssertTrue(pcPath->GetFirst() == &cCircuit);
	AssertTrue(pcPath->GetLast() == &cCircuit);
	AssertTrue(pcPath->GetCircuitView() == &cCircuit);
	AssertNull(pcPath->GetPrevious());
	AssertLong(1, pcPath->GetID());
	sz.Init();
	pcPath->AppendDescription(&sz);
	AssertString("Circuit", sz.Text());
	sz.Kill();

	pcOtherPath = cPaths.AddTop(&cOther);
	AssertLong(2, pcOtherPath->GetID());
	AssertSize(2, cPaths.NumViewPaths());
	AssertTrue(cPaths.GetTop(&cCircuit) == pcPath);
	AssertTrue(cPaths.GetTop(&cOther) == pcOtherPath);

	gcLogger.GetConfig(&sLogConfig);
	gcLogger.SetSilent();
	AssertNull(cPaths.AddTop(&cCircuit));
	gcLogger.SetConfig(&sLogConfig);
	AssertSize(2, cPaths.NumViewPaths());

	AssertSize(0, pcPath->NumCircuitSimulations());
	AssertFalse(pcPath->ContainsCircuitSimulation(&cFirst));
	AssertNull(pcPath->GetSubcircuitSimulation(&cFirst));
	AssertTrue(pcPath->AddSubcircuitSimulation(cFirst.GetSubcircuitTopSimulation()));
	AssertTrue(pcPath->AddSubcircuitSimulation(cSecond.GetSubcircuitTopSimulation()));
	gcLogger.SetSilent();
	AssertFalse(pcPath->AddSubcircuitSimulation(cFirst.GetSubcircuitTopSimulation()));
	gcLogger.SetConfig(&sLogConfig);
	AssertSize(2, pcPath->NumCircuitSimulations());
	AssertTrue(pcPath->GetCircuitSimulation(0) == &cFirst);
	AssertTrue(pcPath->GetCircuitSimulation(1) == &cSecond);
	AssertTrue(pcPath->GetSubcircuitSimulation(&cSecond) == cSecond.GetSubcircuitTopSimulation());
	AssertFalse(pcOtherPath->ContainsCircuitSimulation(&cFirst));

	AssertTrue(pcPath->RemoveSubcircuitSimulation(&cFirst));
	AssertFalse(pcPath->RemoveSubcircuitSimulation(&cFirst));
	AssertFalse(pcPath->ContainsCircuitSimulation(&cFirst));
	AssertTrue(pcPath->ContainsCircuitSimulation(&cSecond));
	AssertTrue(pcPath->GetCircuitSimulation(0) == &cSecond);

	cSecond.Kill();
	cFirst.Kill();
	cPaths.Kill();
	cOther.Kill();
	cCircuit.Kill();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
// A ground on an inverter's input, as TestCircuitViewGroundDrivesInverters.
//
//////////////////////////////////////////////////////////////////////////
static void AddGroundedInverter(CCircuitView* pcCircuit, CInverterView** ppcInverter, CTraceView** ppcOut)
{
	CGroundView*	pcGround;

	pcGround = NewMalloc<CGroundView>();
	pcGround->Init(-4, 3, ROT_North, "");
	pcCircuit->Add(pcGround);
	*ppcInverter = NewMalloc<CInverterView>();
	(*ppcInverter)->Init(-3, 3, ROT_West, "", "LVC", false, 1, 1);
	pcCircuit->Add(*ppcInverter);
	*ppcOut = pcCircuit->AddTrace(-1, 3, 6, 3);
}


//////////////////////////////////////////////////////////////////////////
//
// One circuit's views simulated in two circuit simulations at once, as
// Logicim's editor can: each simulation has its own components and traces,
// and forgetting one leaves the other running.
//
//////////////////////////////////////////////////////////////////////////
void TestViewPathTwoSimulations(void)
{
	CFamilyVoltageConfigurationStore	cFamilies;
	CFamilyVoltageConfiguration*		pcFamily;
	CCircuitSimulation					cFirst;
	CCircuitSimulation					cSecond;
	CCircuitView						cCircuit;
	CViewPaths							cPaths;
	CViewPath*							pcPath;
	CInverterView*						pcInverter;
	CTraceView*							pcOut;
	float32								fVcc;

	ObjectsInit();
	CEvent::ResetNextID();
	CTrace::ResetNextID();
	cFamilies.Init();
	AssertTrue(cFamilies.Load("Input" _FS_ "PropagationTimes.csv"));
	pcFamily = cFamilies.Get("LVC");
	fVcc = pcFamily->GetDefaultVoltageConfiguration(DEFAULT_LOGIC_LEVEL)->GetVcc();
	cFirst.Init("First");
	cSecond.Init("Second");
	cCircuit.Init();
	cPaths.Init();
	pcPath = cPaths.AddTop(&cCircuit);
	AddGroundedInverter(&cCircuit, &pcInverter, &pcOut);

	AssertTrue(cCircuit.CreateSimulation(pcPath, &cFirst, &cFamilies));
	AssertTrue(cCircuit.CreateSimulation(pcPath, &cSecond, &cFamilies));
	AssertTrue(pcPath->GetSubcircuitSimulation(&cFirst) == cFirst.GetSubcircuitTopSimulation());
	AssertTrue(pcPath->GetSubcircuitSimulation(&cSecond) == cSecond.GetSubcircuitTopSimulation());
	AssertSize(2, pcInverter->NumComponents());
	AssertNotNull(pcInverter->GetComponent(pcPath, &cFirst));
	AssertNotNull(pcInverter->GetComponent(pcPath, &cSecond));
	AssertTrue(pcInverter->GetComponent(pcPath, &cFirst) != pcInverter->GetComponent(pcPath, &cSecond));
	AssertTrue(pcInverter->GetComponent(pcPath, &cFirst)->GetContainingSubcircuitSimulation() == cFirst.GetSubcircuitTopSimulation());
	AssertTrue(pcInverter->GetComponent(pcPath, &cSecond)->GetContainingSubcircuitSimulation() == cSecond.GetSubcircuitTopSimulation());
	AssertSize(1, pcOut->NumTraces(pcPath, &cFirst));
	AssertSize(1, pcOut->NumTraces(pcPath, &cSecond));
	AssertTrue(pcOut->GetTrace(pcPath, &cFirst, 0) != pcOut->GetTrace(pcPath, &cSecond, 0));
	AssertTrue(pcInverter->GetPortView("Output")->GetPort(pcPath, &cFirst, 0)->GetTrace() == pcOut->GetTrace(pcPath, &cFirst, 0));
	AssertTrue(pcInverter->GetPortView("Output")->GetPort(pcPath, &cSecond, 0)->GetTrace() == pcOut->GetTrace(pcPath, &cSecond, 0));

	//Only the first is run; the second's output hasn't been driven yet.
	cFirst.GetTimeline()->Run();
	AssertInt(TV_High, pcFamily->GetValue(pcOut->GetTrace(pcPath, &cFirst, 0)->GetVoltage(cFirst.GetTime()), fVcc));
	AssertFalse(IsVoltage(pcOut->GetTrace(pcPath, &cSecond, 0)->GetVoltage(cSecond.GetTime())));

	cCircuit.DisconnectSimulation(pcPath, &cFirst);
	AssertFalse(pcPath->ContainsCircuitSimulation(&cFirst));
	AssertNull(pcInverter->GetComponent(pcPath, &cFirst));
	AssertSize(0, pcOut->NumTraces(pcPath, &cFirst));
	AssertSize(1, pcInverter->NumComponents());
	AssertNotNull(pcInverter->GetComponent(pcPath, &cSecond));

	cSecond.GetTimeline()->Run();
	AssertInt(TV_High, pcFamily->GetValue(pcOut->GetTrace(pcPath, &cSecond, 0)->GetVoltage(cSecond.GetTime()), fVcc));

	cCircuit.Kill();
	cPaths.Kill();
	cSecond.Kill();
	cFirst.Kill();
	cFamilies.Kill();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
// A component is made once for each path and simulation, and only for a
// path that ends in the circuit and is simulated.
//
//////////////////////////////////////////////////////////////////////////
void TestViewPathCreateErrors(void)
{
	CFamilyVoltageConfigurationStore	cFamilies;
	CCircuitSimulation					cSimulation;
	CCircuitView						cCircuit;
	CCircuitView						cOther;
	CViewPaths							cPaths;
	CViewPath*							pcPath;
	CViewPath*							pcOtherPath;
	CInverterView*						pcInverter;
	CTraceView*							pcOut;
	SLogConfig							sLogConfig;

	ObjectsInit();
	cFamilies.Init();
	AssertTrue(cFamilies.Load("Input" _FS_ "PropagationTimes.csv"));
	cSimulation.Init("Errors");
	cCircuit.Init();
	cOther.Init();
	cPaths.Init();
	pcPath = cPaths.AddTop(&cCircuit);
	pcOtherPath = cPaths.AddTop(&cOther);
	AddGroundedInverter(&cCircuit, &pcInverter, &pcOut);

	gcLogger.GetConfig(&sLogConfig);
	gcLogger.SetSilent();
	AssertFalse(cCircuit.CreateSimulation(pcOtherPath, &cSimulation, &cFamilies));
	AssertSize(0, pcInverter->NumComponents());
	AssertNull(pcInverter->CreateComponent(pcPath, &cSimulation, &cFamilies));
	gcLogger.SetConfig(&sLogConfig);

	AssertTrue(cCircuit.CreateSimulation(pcPath, &cSimulation, &cFamilies));
	gcLogger.SetSilent();
	AssertNull(pcInverter->CreateComponent(pcPath, &cSimulation, &cFamilies));
	gcLogger.SetConfig(&sLogConfig);
	AssertSize(1, pcInverter->NumComponents());

	cCircuit.Kill();
	cOther.Kill();
	cPaths.Kill();
	cSimulation.Kill();
	cFamilies.Kill();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestViewPaths(void)
{
	BeginTests();
	DataIOInit();

	TestViewPathTop();
	TestViewPathTwoSimulations();
	TestViewPathCreateErrors();

	DataIOKill();
	TestStatistics();
}

