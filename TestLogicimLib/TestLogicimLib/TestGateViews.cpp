#include "BaseLib/ConstructorCall.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "StandardLib/Objects.h"
#include "MicroprocessorLib/CircuitSimulation.h"
#include "MicroprocessorLib/FamilyVoltageConfigurationStore.h"
#include "MicroprocessorLib/IntegratedCircuit.h"
#include "MicroprocessorLib/PowerSource.h"
#include "MicroprocessorLib/PowerOutPort.h"
#include "MicroprocessorLib/Trace.h"
#include "MicroprocessorLib/Event.h"
#include "MicroprocessorLib/LongTime.h"
#include "MicroprocessorLib/Timeline.h"
#include "LogicimLib/AndGateView.h"
#include "LogicimLib/OrGateView.h"
#include "LogicimLib/BufferView.h"
#include "LogicimLib/PowerSourceView.h"
#include "LogicimLib/CircuitView.h"
#include "TestLib/Assert.h"
#include "TestLogicimRender.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertBounds(float64 fLeft, float64 fTop, float64 fRight, float64 fBottom, SFloat64Vec2* psMinimum, SFloat64Vec2* psMaximum)
{
	AssertDouble(fLeft, psMinimum->x, 3);
	AssertDouble(fTop, psMinimum->y, 3);
	AssertDouble(fRight, psMaximum->x, 3);
	AssertDouble(fBottom, psMaximum->y, 3);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertGridPosition(int32 x, int32 y, CPortView* pcPortView)
{
	SInt32Vec2	sPosition;

	AssertNotNull(pcPortView);
	sPosition = pcPortView->GetGridPosition();
	AssertInt(x, sPosition.x);
	AssertInt(y, sPosition.y);
}


//////////////////////////////////////////////////////////////////////////
//
// Rotating right (clockwise) goes North, East, South, West.  East leaves
// a point as it is: a component is drawn facing East.  North turns its
// front (+x) up (-y), South down and West to the left.
//
//////////////////////////////////////////////////////////////////////////
void TestRotation(void)
{
	SInt32Vec2		sPoint;
	SFloat64Vec2	sFloat;

	AssertInt(ROT_East, RotateRight(ROT_North));
	AssertInt(ROT_South, RotateRight(ROT_East));
	AssertInt(ROT_West, RotateRight(ROT_South));
	AssertInt(ROT_North, RotateRight(ROT_West));
	AssertInt(ROT_West, RotateLeft(ROT_North));
	AssertInt(ROT_South, OppositeRotation(ROT_North));
	AssertInt(ROT_West, RotateRight(ROT_North, -1));
	AssertInt(ROT_North, RotateRight(ROT_North, 8));
	AssertInt(ROT_Cannot, RotateRight(ROT_Cannot));
	AssertInt(0, RotationToDegrees(ROT_East));
	AssertInt(90, RotationToDegrees(ROT_North));
	AssertInt(270, RotationToDegrees(ROT_South));
	AssertTrue(IsRotationEastWest(ROT_East));
	AssertFalse(IsRotationEastWest(ROT_South));
	AssertString("West", RotationToString(ROT_West));

	sPoint.Init(2, 0);
	RotatePoint(ROT_East, &sPoint);
	AssertInt(2, sPoint.x);
	AssertInt(0, sPoint.y);
	sPoint.Init(2, 0);
	RotatePoint(ROT_North, &sPoint);
	AssertInt(0, sPoint.x);
	AssertInt(-2, sPoint.y);
	sPoint.Init(2, 0);
	RotatePoint(ROT_South, &sPoint);
	AssertInt(0, sPoint.x);
	AssertInt(2, sPoint.y);
	sPoint.Init(2, 1);
	RotatePoint(ROT_West, &sPoint);
	AssertInt(-2, sPoint.x);
	AssertInt(-1, sPoint.y);

	sFloat.Init(1.5, 0.5);
	RotatePoint(ROT_North, &sFloat);
	AssertDouble(0.5, sFloat.x, 3);
	AssertDouble(-1.5, sFloat.y, 3);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCircuitViewport(void)
{
	CCircuitViewport	cViewport;
	SFloat64Vec2		sGrid;
	SFloat64Vec2		sScreen;
	SFloat64Vec2		sBack;

	cViewport.Init(200, 100);
	AssertDouble(100, cViewport.GridToScreenX(0), 3);
	AssertDouble(50, cViewport.GridToScreenY(0), 3);
	AssertDouble(130, cViewport.GridToScreenX(3), 3);

	cViewport.SetZoom(2);
	cViewport.SetPosition(5, -5);
	sGrid.Init(-1, 2);
	cViewport.GridToScreen(&sScreen, &sGrid);
	AssertDouble(85, sScreen.x, 3);
	AssertDouble(85, sScreen.y, 3);
	cViewport.ScreenToGrid(&sBack, &sScreen);
	AssertDouble(-1, sBack.x, 3);
	AssertDouble(2, sBack.y, 3);

	AssertDouble(4, cViewport.GetDefaultLineWidth(), 3);
	AssertDouble(6, cViewport.GetConnectionRadius(), 3);
	cViewport.SetZoom(0.4);
	AssertDouble(1, cViewport.GetDefaultLineWidth(), 3);
	cViewport.SetZoom(0.1);
	AssertDouble(0.2, cViewport.GetZoom(), 3);
	AssertDouble(0.9, cViewport.GetConnectionRadius(), 3);
	cViewport.SetZoom(10);
	AssertDouble(6, cViewport.GetZoom(), 3);

	//The grid point under the pointer stays there.
	cViewport.SetZoom(1);
	sScreen.Init(150, 20);
	cViewport.ScreenToGrid(&sGrid, &sScreen);
	cViewport.ZoomAround(150, 20, 3);
	cViewport.GridToScreen(&sBack, &sGrid);
	AssertDouble(150, sBack.x, 3);
	AssertDouble(20, sBack.y, 3);

	cViewport.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestLogicGatePortOffsets(void)
{
	CArrayInt	aiOffsets;
	CArrayChars	aszNames;

	aiOffsets.Init();
	CLogicGateView::CalculatePortOffsets(&aiOffsets, 1);
	AssertSize(1, aiOffsets.NumElements());
	AssertInt(0, aiOffsets.GetValue(0));
	aiOffsets.ReInit();
	CLogicGateView::CalculatePortOffsets(&aiOffsets, 2);
	AssertSize(2, aiOffsets.NumElements());
	AssertInt(-1, aiOffsets.GetValue(0));
	AssertInt(1, aiOffsets.GetValue(1));
	aiOffsets.ReInit();
	CLogicGateView::CalculatePortOffsets(&aiOffsets, 5);
	AssertSize(5, aiOffsets.NumElements());
	AssertInt(-2, aiOffsets.GetValue(0));
	AssertInt(2, aiOffsets.GetValue(4));
	aiOffsets.Kill();

	AssertDouble(1.5, CLogicGateView::CalculateWidth(2), 3);
	AssertDouble(1.5, CLogicGateView::CalculateWidth(3), 3);
	AssertDouble(2.5, CLogicGateView::CalculateWidth(4), 3);
	AssertDouble(3.5, CLogicGateView::CalculateWidth(6), 3);

	aszNames.Init();
	CLogicGateView::GetPortNames(&aszNames, "Input", 1, 2, 3);
	AssertSize(2, aszNames.NumElements());
	AssertString("Input 2", aszNames.GetText(0));
	AssertString("Input 3", aszNames.GetText(1));
	aszNames.ReInit();
	CLogicGateView::GetPortNames(&aszNames, "Output", 0, 1, 1);
	AssertSize(1, aszNames.NumElements());
	AssertString("Output", aszNames.GetText(0));
	aszNames.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// Port positions turn with the gate; bounding boxes hold the shapes and
// the ports.
//
//////////////////////////////////////////////////////////////////////////
void TestLogicGateViewGeometry(void)
{
	CAndGateView*	pcAnd;
	CNandGateView*	pcNand;
	CXorGateView*	pcXor;
	CInverterView*	pcInverter;
	SFloat64Vec2	sMinimum;
	SFloat64Vec2	sMaximum;

	pcAnd = NewMalloc<CAndGateView>();
	pcAnd->Init(10, 20, ROT_North, "U1", "LVC", false, 2, 1);
	AssertString("AND Gate", pcAnd->GetType());
	AssertSize(3, pcAnd->NumPortViews());
	AssertGridPosition(9, 21, pcAnd->GetPortView("Input 0"));
	AssertGridPosition(11, 21, pcAnd->GetPortView("Input 1"));
	AssertGridPosition(10, 18, pcAnd->GetPortView("Output"));
	AssertTrue(pcAnd->GetLocalBounds(&sMinimum, &sMaximum));
	AssertBounds(-1, -1.5, 2, 1.5, &sMinimum, &sMaximum);

	pcAnd->SetRotation(ROT_East);
	AssertGridPosition(9, 19, pcAnd->GetPortView("Input 0"));
	AssertGridPosition(9, 21, pcAnd->GetPortView("Input 1"));
	AssertGridPosition(12, 20, pcAnd->GetPortView("Output"));
	AssertTrue(pcAnd->GetBoundingBox(&sMinimum, &sMaximum));
	AssertBounds(9, 18.5, 12, 21.5, &sMinimum, &sMaximum);
	SafeKill(pcAnd);

	//The bubble pushes the output out a grid unit.
	pcNand = NewMalloc<CNandGateView>();
	pcNand->Init(0, 0, ROT_North, "", "LVC", false, 3, 1);
	AssertString("NAND Gate", pcNand->GetType());
	AssertSize(4, pcNand->NumPortViews());
	AssertGridPosition(-1, 1, pcNand->GetPortView("Input 0"));
	AssertGridPosition(0, 1, pcNand->GetPortView("Input 1"));
	AssertGridPosition(1, 1, pcNand->GetPortView("Input 2"));
	AssertGridPosition(0, -3, pcNand->GetPortView("Output"));
	AssertTrue(pcNand->GetPortView("Output")->IsInverting());
	AssertTrue(pcNand->GetLocalBounds(&sMinimum, &sMaximum));
	AssertBounds(-1, -1.5, 3, 1.5, &sMinimum, &sMaximum);
	SafeKill(pcNand);

	//Exclusive OR inputs are a grid unit further back for the second curve; four inputs widen the gate.
	pcXor = NewMalloc<CXorGateView>();
	pcXor->Init(0, 0, ROT_South, "", "LVC", false, 4, 2);
	AssertString("XOR Gate", pcXor->GetType());
	AssertTrue(pcXor->IsExclusive());
	AssertSize(5, pcXor->NumPortViews());
	AssertSize(2, pcXor->GetPortView((size)0)->NumPortNames());
	AssertString("Input 0", pcXor->GetPortView((size)0)->GetPortName(0));
	AssertString("Input 1", pcXor->GetPortView((size)0)->GetPortName(1));
	AssertGridPosition(2, -2, pcXor->GetPortView((size)0));
	AssertGridPosition(0, 2, pcXor->GetPortView("Output"));
	AssertTrue(pcXor->GetLocalBounds(&sMinimum, &sMaximum));
	AssertDouble(-2.5, sMinimum.y, 1);
	AssertDouble(-2, sMinimum.x, 3);
	SafeKill(pcXor);

	pcInverter = NewMalloc<CInverterView>();
	pcInverter->Init(0, 0, ROT_West, "", "LVC", false, 2, 1);
	AssertString("Inverter", pcInverter->GetType());
	AssertSize(4, pcInverter->NumPortViews());
	AssertGridPosition(1, 1, pcInverter->GetPortView("Input 0"));
	AssertGridPosition(-2, 1, pcInverter->GetPortView("Output 0"));
	AssertGridPosition(-2, -1, pcInverter->GetPortView("Output 1"));
	SafeKill(pcInverter);
}


//////////////////////////////////////////////////////////////////////////
//
// Explicit power ports sit on the bounding box's sides with a stub each.
//
//////////////////////////////////////////////////////////////////////////
void TestLogicGateViewExplicitPower(void)
{
	COrGateView*	pcOr;
	size			uiShapes;

	pcOr = NewMalloc<COrGateView>();
	pcOr->Init(0, 0, ROT_North, "", "LVC", true, 2, 1);
	AssertTrue(pcOr->IsExplicitPowerPorts());
	AssertSize(5, pcOr->NumPortViews());
	AssertGridPosition(-2, 0, pcOr->GetPortView("VCC"));
	AssertGridPosition(2, 0, pcOr->GetPortView("GND"));
	uiShapes = pcOr->GetShapes()->NumShapes();
	AssertSize(9, uiShapes);
	AssertInt(CS_Line, pcOr->GetShapes()->GetShape(uiShapes - 1)->eType);
	SafeKill(pcOr);
}


//////////////////////////////////////////////////////////////////////////
//
// The standard gates in a row facing right as Logicim draws them (rendered
// in Logicim at the same places to compare), and below them some others.
//
//////////////////////////////////////////////////////////////////////////
void TestGateViewsRender(void)
{
	CFamilyVoltageConfigurationStore	cFamilies;
	CCircuitSimulation					cSimulation;
	CCircuitView						cCircuit;
	CViewPaths							cPaths;
	CViewPath*							pcPath;
	CCircuitColours						cColours;
	CAndGateView*						pcAnd;
	CNandGateView*						pcNand;
	COrGateView*						pcOr;
	CNorGateView*						pcNor;
	CXorGateView*						pcXor;
	CXnorGateView*						pcXnor;
	CBufferView*						pcBuffer;
	CInverterView*						pcInverter;

	ObjectsInit();
	cFamilies.Init();
	AssertTrue(cFamilies.Load("Input" _FS_ "PropagationTimes.csv"));
	cSimulation.Init("Gates");
	cCircuit.Init();
	cPaths.Init();
	pcPath = cPaths.AddTop(&cCircuit);
	cColours.InitLogicim();

	pcAnd = NewMalloc<CAndGateView>();
	pcAnd->Init(-30, -5, ROT_East, "", "LVC", false, 2, 1);
	cCircuit.Add(pcAnd);
	pcNand = NewMalloc<CNandGateView>();
	pcNand->Init(-20, -5, ROT_East, "", "LVC", false, 2, 1);
	cCircuit.Add(pcNand);
	pcOr = NewMalloc<COrGateView>();
	pcOr->Init(-10, -5, ROT_East, "", "LVC", false, 2, 1);
	cCircuit.Add(pcOr);
	pcNor = NewMalloc<CNorGateView>();
	pcNor->Init(0, -5, ROT_East, "", "LVC", false, 2, 1);
	cCircuit.Add(pcNor);
	pcXor = NewMalloc<CXorGateView>();
	pcXor->Init(10, -5, ROT_East, "", "LVC", false, 2, 1);
	cCircuit.Add(pcXor);
	pcXnor = NewMalloc<CXnorGateView>();
	pcXnor->Init(20, -5, ROT_East, "", "LVC", false, 2, 1);
	cCircuit.Add(pcXnor);
	pcBuffer = NewMalloc<CBufferView>();
	pcBuffer->Init(30, -5, ROT_East, "", "LVC", false, 1, 1);
	cCircuit.Add(pcBuffer);

	pcInverter = NewMalloc<CInverterView>();
	pcInverter->Init(-30, 6, ROT_East, "", "LVC", false, 1, 1);
	cCircuit.Add(pcInverter);
	pcAnd = NewMalloc<CAndGateView>();
	pcAnd->Init(-20, 6, ROT_North, "", "LVC", false, 4, 1);
	cCircuit.Add(pcAnd);
	pcOr = NewMalloc<COrGateView>();
	pcOr->Init(-8, 6, ROT_South, "", "LVC", false, 5, 1);
	cCircuit.Add(pcOr);
	pcXnor = NewMalloc<CXnorGateView>();
	pcXnor->Init(5, 6, ROT_West, "", "LVC", false, 3, 1);
	cCircuit.Add(pcXnor);
	pcNor = NewMalloc<CNorGateView>();
	pcNor->Init(17, 6, ROT_East, "", "LVC", true, 2, 1);
	cCircuit.Add(pcNor);
	pcBuffer = NewMalloc<CBufferView>();
	pcBuffer->Init(29, 6, ROT_North, "", "LVC", false, 3, 1);
	cCircuit.Add(pcBuffer);

	AssertTrue(cCircuit.CreateSimulation(pcPath, &cSimulation, &cFamilies));
	AssertNotNull(pcAnd->GetComponent(pcPath, &cSimulation));
	AssertString("AND Gate", ((CIntegratedCircuit*)pcAnd->GetComponent(pcPath, &cSimulation))->GetType());
	AssertSize(4, pcAnd->GetIntegratedCircuit(pcPath, &cSimulation)->GetPins()->NumPorts() - 3);

	AssertRenderedCircuit(&cCircuit, &cColours, 1400, 400, 2, pcPath, &cSimulation, true, "Gates");

	cColours.InitDark();
	AssertRenderedCircuit(&cCircuit, &cColours, 1400, 400, 2, pcPath, &cSimulation, true, "GatesDark");

	cCircuit.Kill();
	cPaths.Kill();
	cSimulation.Kill();
	cFamilies.Kill();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
// Wire ends at ports and where three or more wires meet are junctions.
//
//////////////////////////////////////////////////////////////////////////
void TestCircuitViewJunctions(void)
{
	CCircuitView	cCircuit;
	CInverterView*	pcInverter;
	CTraceView*		pcIn;
	CTraceView*		pcA;
	CTraceView*		pcB;
	CTraceView*		pcC;
	CTraceView*		pcCross;

	cCircuit.Init();
	pcInverter = NewMalloc<CInverterView>();
	pcInverter->Init(0, 0, ROT_East, "", "LVC", false, 1, 1);
	cCircuit.Add(pcInverter);

	pcIn = cCircuit.AddTrace(-6, 0, -1, 0);
	pcA = cCircuit.AddTrace(2, 0, 6, 0);
	pcB = cCircuit.AddTrace(6, 0, 6, -4);
	pcC = cCircuit.AddTrace(6, 0, 10, 0);
	pcCross = cCircuit.AddTrace(8, -2, 8, 2);
	cCircuit.CalculateJunctions();

	AssertFalse(pcIn->IsStartJunction());
	AssertTrue(pcIn->IsEndJunction());
	AssertTrue(pcA->IsStartJunction());
	AssertTrue(pcA->IsEndJunction());
	AssertTrue(pcB->IsStartJunction());
	AssertFalse(pcB->IsEndJunction());
	AssertTrue(pcC->IsStartJunction());
	AssertFalse(pcC->IsEndJunction());
	AssertFalse(pcCross->IsStartJunction());
	AssertFalse(pcCross->IsEndJunction());
	AssertFalse(pcCross->Touches(pcC));
	AssertTrue(pcA->Touches(pcB));

	cCircuit.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// An inverter feeding both inputs of an AND gate through a junction.  The
// input wire is driven by a supply wired on while the simulation runs; the
// wires are coloured by their voltages.
//
//////////////////////////////////////////////////////////////////////////
void TestCircuitViewSimulation(void)
{
	CFamilyVoltageConfigurationStore	cFamilies;
	CFamilyVoltageConfiguration*		pcFamily;
	CCircuitSimulation					cSimulation;
	CCircuitView						cCircuit;
	CViewPaths							cPaths;
	CViewPath*							pcPath;
	CCircuitColours						cColours;
	CInverterView*						pcInverter;
	CAndGateView*						pcAnd;
	CTraceView*							pcIn;
	CTraceView*							pcMiddle;
	CTraceView*							pcOut;
	CTraceView*							pcUpper;
	CPowerSource*						pcSupply;
	float32								fVcc;

	ObjectsInit();
	CEvent::ResetNextID();
	CTrace::ResetNextID();
	cFamilies.Init();
	AssertTrue(cFamilies.Load("Input" _FS_ "PropagationTimes.csv"));
	pcFamily = cFamilies.Get("LVC");
	fVcc = pcFamily->GetDefaultVoltageConfiguration(DEFAULT_LOGIC_LEVEL)->GetVcc();
	cSimulation.Init("Inverter");
	cCircuit.Init();
	cPaths.Init();
	pcPath = cPaths.AddTop(&cCircuit);
	cColours.InitLogicim();

	pcInverter = NewMalloc<CInverterView>();
	pcInverter->Init(-10, 0, ROT_East, "U1", "LVC", false, 1, 1);
	cCircuit.Add(pcInverter);
	pcAnd = NewMalloc<CAndGateView>();
	pcAnd->Init(2, 0, ROT_East, "U2", "LVC", false, 2, 1);
	cCircuit.Add(pcAnd);

	pcIn = cCircuit.AddTrace(-18, 0, -11, 0);
	pcMiddle = cCircuit.AddTrace(-8, 0, -4, 0);
	cCircuit.AddTraces(-4, 0, 1, -1);
	pcUpper = cCircuit.GetTrace(cCircuit.NumTraces() - 1);
	cCircuit.AddTrace(-4, 0, -4, 1);
	cCircuit.AddTrace(-4, 1, 1, 1);
	pcOut = cCircuit.AddTrace(4, 0, 10, 0);

	AssertTrue(cCircuit.CreateSimulation(pcPath, &cSimulation, &cFamilies));
	AssertSize(1, pcIn->NumTraces(pcPath, &cSimulation));
	AssertTrue(pcMiddle->GetTrace(pcPath, &cSimulation, 0) == pcUpper->GetTrace(pcPath, &cSimulation, 0));
	AssertTrue(pcMiddle->GetTrace(pcPath, &cSimulation, 0) != pcIn->GetTrace(pcPath, &cSimulation, 0));
	AssertTrue(pcMiddle->IsEndJunction());
	AssertTrue(pcAnd->GetPortView("Input 0")->GetPort(pcPath, &cSimulation, 0)->GetTrace() == pcMiddle->GetTrace(pcPath, &cSimulation, 0));
	AssertTrue(pcAnd->GetPortView("Output")->GetPort(pcPath, &cSimulation, 0)->GetTrace() == pcOut->GetTrace(pcPath, &cSimulation, 0));

	//Nothing drives the input yet.
	AssertRenderedCircuit(&cCircuit, &cColours, 600, 160, 2, NULL, NULL, false, "InverterAndDisconnected");

	//Wired on to the running simulation, as the editor would.
	pcSupply = NewMalloc<CPowerSource>();
	pcSupply->Init(cSimulation.GetSubcircuitTopSimulation(), "Supply", fVcc);
	AssertTrue(pcSupply->GetPowerOutPort()->ConnectLive(pcIn->GetTrace(pcPath, &cSimulation, 0), cSimulation.GetTimeline()));
	cSimulation.GetTimeline()->Run();
	AssertInt(TV_High, pcFamily->GetValue(pcIn->GetTrace(pcPath, &cSimulation, 0)->GetVoltage(cSimulation.GetTime()), fVcc));
	AssertInt(TV_Low, pcFamily->GetValue(pcMiddle->GetTrace(pcPath, &cSimulation, 0)->GetVoltage(cSimulation.GetTime()), fVcc));
	AssertInt(TV_Low, pcFamily->GetValue(pcOut->GetTrace(pcPath, &cSimulation, 0)->GetVoltage(cSimulation.GetTime()), fVcc));
	AssertRenderedCircuit(&cCircuit, &cColours, 600, 160, 2, pcPath, &cSimulation, true, "InverterAndHigh");

	//The views can make the circuit again in a new simulation.
	cCircuit.DisconnectSimulation(pcPath, &cSimulation);
	AssertNull(pcAnd->GetComponent(pcPath, &cSimulation));
	AssertSize(0, pcIn->NumTraces(pcPath, &cSimulation));
	AssertSize(0, pcAnd->GetPortView("Output")->NumPorts(pcPath, &cSimulation));
	cSimulation.Kill();
	cSimulation.Init("Again");
	AssertTrue(cCircuit.CreateSimulation(pcPath, &cSimulation, &cFamilies));
	AssertNotNull(pcAnd->GetComponent(pcPath, &cSimulation));
	AssertTrue(pcAnd->GetPortView("Output")->GetPort(pcPath, &cSimulation, 0)->GetTrace() == pcOut->GetTrace(pcPath, &cSimulation, 0));
	AssertTrue(pcMiddle->GetTrace(pcPath, &cSimulation, 0) == pcUpper->GetTrace(pcPath, &cSimulation, 0));

	cCircuit.Kill();
	cPaths.Kill();
	cSimulation.Kill();
	cFamilies.Kill();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
// A supply drawn in the circuit drives the gates on its net from the
// start, as in Logicim: a ground on an inverter's input through a wire,
// and another touching an inverter's input directly.
//
//////////////////////////////////////////////////////////////////////////
void TestCircuitViewGroundDrivesInverters(void)
{
	CFamilyVoltageConfigurationStore	cFamilies;
	CFamilyVoltageConfiguration*		pcFamily;
	CCircuitSimulation					cSimulation;
	CCircuitView						cCircuit;
	CViewPaths							cPaths;
	CViewPath*							pcPath;
	CCircuitColours						cColours;
	CGroundView*						pcGround;
	CInverterView*						pcInverter;
	CTraceView*							pcOut1;
	CTraceView*							pcOut2;
	float32								fVcc;
	SFloat64Vec2						sMinimum;
	SFloat64Vec2						sMaximum;

	ObjectsInit();
	CEvent::ResetNextID();
	CTrace::ResetNextID();
	cFamilies.Init();
	AssertTrue(cFamilies.Load("Input" _FS_ "PropagationTimes.csv"));
	pcFamily = cFamilies.Get("LVC");
	fVcc = pcFamily->GetDefaultVoltageConfiguration(DEFAULT_LOGIC_LEVEL)->GetVcc();
	cSimulation.Init("Ground");
	cCircuit.Init();
	cPaths.Init();
	pcPath = cPaths.AddTop(&cCircuit);
	cColours.InitLogicim();

	pcGround = NewMalloc<CGroundView>();
	pcGround->Init(-8, -3, ROT_North, "");
	cCircuit.Add(pcGround);
	AssertString("Ground", pcGround->GetType());
	AssertTrue(pcGround->GetLocalBounds(&sMinimum, &sMaximum));
	AssertBounds(-1.166, -0.9, 0, 0.9, &sMinimum, &sMaximum);
	cCircuit.AddTraces(-8, -3, -4, -2);
	pcInverter = NewMalloc<CInverterView>();
	pcInverter->Init(-3, -2, ROT_East, "", "LVC", false, 1, 1);
	cCircuit.Add(pcInverter);
	pcOut1 = cCircuit.AddTrace(-1, -2, 6, -2);

	pcGround = NewMalloc<CGroundView>();
	pcGround->Init(-4, 3, ROT_North, "");
	cCircuit.Add(pcGround);
	pcInverter = NewMalloc<CInverterView>();
	pcInverter->Init(-3, 3, ROT_East, "", "LVC", false, 1, 1);
	cCircuit.Add(pcInverter);
	pcOut2 = cCircuit.AddTrace(-1, 3, 6, 3);

	AssertTrue(cCircuit.CreateSimulation(pcPath, &cSimulation, &cFamilies));
	cSimulation.GetTimeline()->Run();
	AssertInt(TV_High, pcFamily->GetValue(pcOut1->GetTrace(pcPath, &cSimulation, 0)->GetVoltage(cSimulation.GetTime()), fVcc));
	AssertInt(TV_High, pcFamily->GetValue(pcOut2->GetTrace(pcPath, &cSimulation, 0)->GetVoltage(cSimulation.GetTime()), fVcc));
	AssertRenderedCircuit(&cCircuit, &cColours, 420, 160, 2, pcPath, &cSimulation, true, "GroundInverters");

	cCircuit.Kill();
	cPaths.Kill();
	cSimulation.Kill();
	cFamilies.Kill();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
// A NAND enabled by a supply and two inverters in a ring oscillates once
// the enable goes high.  The enable starts low so the ring starts at known
// levels.
//
//////////////////////////////////////////////////////////////////////////
void TestCircuitViewRingOscillator(void)
{
	CFamilyVoltageConfigurationStore	cFamilies;
	CFamilyVoltageConfiguration*		pcFamily;
	CCircuitSimulation					cSimulation;
	CCircuitView						cCircuit;
	CViewPaths							cPaths;
	CViewPath*							pcPath;
	CNandGateView*						pcNand;
	CInverterView*						pcInverter;
	CTraceView*							pcEnable;
	CTraceView*							pcRing;
	CPowerSource*						pcLow;
	CPowerSource*						pcHigh;
	float32								fVcc;
	int									i;
	int									iChanges;
	ETraceValue							eLast;
	ETraceValue							eValue;
	CTimeline*							pcTimeline;

	ObjectsInit();
	CEvent::ResetNextID();
	CTrace::ResetNextID();
	cFamilies.Init();
	AssertTrue(cFamilies.Load("Input" _FS_ "PropagationTimes.csv"));
	pcFamily = cFamilies.Get("LVC");
	fVcc = pcFamily->GetDefaultVoltageConfiguration(DEFAULT_LOGIC_LEVEL)->GetVcc();
	cSimulation.Init("Ring");
	cCircuit.Init();
	cPaths.Init();
	pcPath = cPaths.AddTop(&cCircuit);

	pcNand = NewMalloc<CNandGateView>();
	pcNand->Init(-17, 0, ROT_East, "U1", "LVC", false, 2, 1);
	cCircuit.Add(pcNand);
	pcInverter = NewMalloc<CInverterView>();
	pcInverter->Init(-11, 0, ROT_East, "U2", "LVC", false, 1, 1);
	cCircuit.Add(pcInverter);
	pcInverter = NewMalloc<CInverterView>();
	pcInverter->Init(-6, 0, ROT_East, "U3", "LVC", false, 1, 1);
	cCircuit.Add(pcInverter);
	pcEnable = cCircuit.AddTrace(-25, -1, -18, -1);
	pcRing = cCircuit.AddTrace(-14, 0, -12, 0);
	cCircuit.AddTrace(-9, 0, -7, 0);
	cCircuit.AddTrace(-4, 0, -1, 0);
	cCircuit.AddTrace(-1, 0, -1, 4);
	cCircuit.AddTrace(-1, 4, -20, 4);
	cCircuit.AddTrace(-20, 4, -20, 1);
	cCircuit.AddTrace(-20, 1, -18, 1);

	AssertTrue(cCircuit.CreateSimulation(pcPath, &cSimulation, &cFamilies));
	pcTimeline = cSimulation.GetTimeline();

	pcLow = NewMalloc<CPowerSource>();
	pcLow->Init(cSimulation.GetSubcircuitTopSimulation(), "Disable", 0.0f);
	AssertTrue(pcLow->GetPowerOutPort()->ConnectLive(pcEnable->GetTrace(pcPath, &cSimulation, 0), pcTimeline));
	pcTimeline->Run();
	AssertInt(TV_High, pcFamily->GetValue(pcRing->GetTrace(pcPath, &cSimulation, 0)->GetVoltage(cSimulation.GetTime()), fVcc));
	pcLow->GetPowerOutPort()->Disconnect(pcTimeline);

	pcHigh = NewMalloc<CPowerSource>();
	pcHigh->Init(cSimulation.GetSubcircuitTopSimulation(), "Enable", fVcc);
	AssertTrue(pcHigh->GetPowerOutPort()->ConnectLive(pcEnable->GetTrace(pcPath, &cSimulation, 0), pcTimeline));

	iChanges = 0;
	eLast = TV_High;
	for (i = 0; i < 200; i++)
	{
		cSimulation.RunToTime(NanosecondsToTime((int64)1));
		eValue = pcFamily->GetValue(pcRing->GetTrace(pcPath, &cSimulation, 0)->GetVoltage(cSimulation.GetTime()), fVcc);
		if (((eValue == TV_High) || (eValue == TV_Low)) && (eValue != eLast))
		{
			iChanges++;
			eLast = eValue;
		}
	}
	AssertTrue(iChanges >= 4);

	cCircuit.Kill();
	cPaths.Kill();
	cSimulation.Kill();
	cFamilies.Kill();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestGateViews(void)
{
	BeginTests();
	DataIOInit();

	TestRotation();
	TestCircuitViewport();
	TestLogicGatePortOffsets();
	TestLogicGateViewGeometry();
	TestLogicGateViewExplicitPower();
	TestCircuitViewJunctions();
	TestGateViewsRender();
	TestCircuitViewSimulation();
	TestCircuitViewGroundDrivesInverters();
	TestCircuitViewRingOscillator();

	DataIOKill();
	TestStatistics();
}

