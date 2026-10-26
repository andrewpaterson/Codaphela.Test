#include <math.h>
#include "BaseLib/ConstructorCall.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/DataMemory.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/XMLWriter.h"
#include "BaseLib/Logger.h"
#include "StandardLib/Objects.h"
#include "MicroprocessorLib/CircuitSimulation.h"
#include "MicroprocessorLib/FamilyVoltageConfigurationStore.h"
#include "MicroprocessorLib/Trace.h"
#include "MicroprocessorLib/Event.h"
#include "MicroprocessorLib/Timeline.h"
#include "MicroprocessorLib/LogicPort.h"
#include "LogicimLib/ClockView.h"
#include "LogicimLib/BufferView.h"
#include "LogicimLib/InverterPackageView.h"
#include "LogicimLib/PowerSourceView.h"
#include "LogicimLib/ValueView.h"
#include "LogicimLib/LabelView.h"
#include "TestLogicimRender.h"
#include "LogicimLib/SubcircuitInstanceView.h"
#include "LogicimLib/CircuitEditor.h"
#include "LogicimLib/ComponentLibraries.h"
#include "LogicimLib/ComponentProperties.h"
#include "LogicimLib/Radix.h"
#include "LogicimLib/ComponentPlacement.h"
#include "LogicimLib/ComponentViewFactory.h"
#include "BaseLib/PointerFunctions.h"
#include "SupportLib/Image.h"
#include "SupportLib/GeometryMap.h"
#include "SupportLib/SpriteMap.h"
#include "TestLib/Assert.h"


void LoadTestCircuitFonts(CCircuitFonts* pcFonts);
void KillTestCircuitFonts(CCircuitFonts* pcFonts);


//////////////////////////////////////////////////////////////////////////
//
// An editor and the families its components are made in.
//
//////////////////////////////////////////////////////////////////////////
struct SEditorTest
{
	CFamilyVoltageConfigurationStore	cFamilies;
	CCircuitEditor						cEditor;

	void Init(CCircuitFonts* pcFonts = NULL)
	{
		ObjectsInit();
		CEvent::ResetNextID();
		CTrace::ResetNextID();
		CViewPath::ResetNextID();
		cFamilies.Init();
		AssertTrue(cFamilies.Load("Input" _FS_ "PropagationTimes.csv"));
		cEditor.Init(&cFamilies, pcFonts);
	}

	//Rooted objects (fonts) leave the root changed; it isn't checked.
	void Kill(bool bRooted = false)
	{
		cEditor.Kill();
		cFamilies.Kill();
		if (bRooted)
		{
			ObjectsFlush();
		}
		ObjectsKill(!bRooted);
	}

	void PointAt(float64 x, float64 y)
	{
		SFloat64Vec2	sPosition;

		sPosition.Init(x, y);
		cEditor.PointerMoved(sPosition);
	}

	void Press(float64 x, float64 y)
	{
		SFloat64Vec2	sPosition;

		sPosition.Init(x, y);
		cEditor.PointerMoved(sPosition);
		cEditor.ButtonPressed(sPosition);
	}

	void Release(float64 x, float64 y)
	{
		SFloat64Vec2	sPosition;

		sPosition.Init(x, y);
		cEditor.PointerMoved(sPosition);
		cEditor.ButtonReleased(sPosition);
	}

	void Click(float64 x, float64 y)
	{
		Press(x, y);
		Release(x, y);
	}

	void Drag(float64 x0, float64 y0, float64 x1, float64 y1)
	{
		Press(x0, y0);
		Release(x1, y1);
	}

	void Run(void)
	{
		cEditor.GetSimulation()->GetTimeline()->Run();
	}

	int GetLevel(int32 x, int32 y)
	{
		return GetEditorLevel(&cEditor, &cFamilies, x, y);
	}

	//The level of the wire through the grid point in the editor's simulation, TV_Unsettled when nothing drives it.
	//Wires are looked up afresh as edits replace them.
	static int GetEditorLevel(CCircuitEditor* pcEditor, CFamilyVoltageConfigurationStore* pcFamilies, int32 x, int32 y)
	{
		CFamilyVoltageConfiguration*	pcFamily;
		CTraceView*						pcTrace;
		CTrace*							pcSimulated;
		float32							fVoltage;
		SInt32Vec2						sPoint;

		sPoint.Init(x, y);
		pcTrace = pcEditor->GetCircuit()->GetTraceAt(sPoint);
		if (pcTrace == NULL)
		{
			return -2;
		}
		pcSimulated = pcTrace->GetTrace(pcEditor->GetViewPath(), pcEditor->GetSimulation(), 0);
		if (pcSimulated == NULL)
		{
			return -1;
		}
		fVoltage = pcSimulated->GetVoltage(pcEditor->GetSimulation()->GetTime());
		if (isnan(fVoltage))
		{
			return TV_Unsettled;
		}
		pcFamily = pcFamilies->Get("LVC");
		return pcFamily->GetValue(fVoltage, pcFamily->GetDefaultVoltageConfiguration(DEFAULT_LOGIC_LEVEL)->GetVcc());
	}
};


//////////////////////////////////////////////////////////////////////////
//
// The middle of the component's box, where clicking picks it.
//
//////////////////////////////////////////////////////////////////////////
static SFloat64Vec2 GetCentre(CComponentView* pcComponent)
{
	SFloat64Vec2	sMinimum;
	SFloat64Vec2	sMaximum;
	SFloat64Vec2	sCentre;

	AssertTrue(pcComponent->GetBoundingBox(&sMinimum, &sMaximum));
	sCentre.Init((sMinimum.x + sMaximum.x) / 2, (sMinimum.y + sMaximum.y) / 2);
	return sCentre;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
static CInverterView* AddTestInverter(CCircuitView* pcCircuit, int32 x, int32 y)
{
	CInverterView*	pcInverter;

	pcInverter = NewMalloc<CInverterView>();
	pcInverter->Init(x, y, ROT_East, "", "LVC", false, 1, 1);
	pcCircuit->Add(pcInverter);
	return pcInverter;
}


//////////////////////////////////////////////////////////////////////////
//
// A ground wired to (-4, -2), where an inverter's input goes when it's at
// (-3, -2), and an output wire from (-1, -2), where its output goes.
//
//////////////////////////////////////////////////////////////////////////
static void AddGroundAndOutput(CCircuitView* pcCircuit)
{
	CGroundView*	pcGround;

	pcGround = NewMalloc<CGroundView>();
	pcGround->Init(-8, -3, ROT_North, "");
	pcCircuit->Add(pcGround);
	pcCircuit->AddTraces(-8, -3, -4, -2);
	pcCircuit->AddTrace(-1, -2, 6, -2);
}


//////////////////////////////////////////////////////////////////////////
//
// Clicks select, shift clicks add, control shift clicks take away and a
// click on nothing clears.  A rectangle dragged left to right takes what's
// wholly in it; dragged right to left, what it touches.  The component
// under the pointer is hovered only while nothing is selected.
//
//////////////////////////////////////////////////////////////////////////
void TestCircuitEditorSelection(void)
{
	SEditorTest			sTest;
	CCircuitView*		pcMain;
	CInverterView*		pcA;
	CInverterView*		pcB;
	CTraceView*			pcTrace;
	CCircuitSelection*	pcSelection;
	SFloat64Vec2		sA;
	SFloat64Vec2		sB;

	sTest.Init();
	pcMain = sTest.cEditor.AddCircuit("Main");
	pcA = AddTestInverter(pcMain, -3, -2);
	pcB = AddTestInverter(pcMain, -3, 3);
	pcTrace = pcMain->AddTrace(-1, -2, 6, -2);
	AssertTrue(sTest.cEditor.Simulate("Main"));
	pcSelection = sTest.cEditor.GetSelection();
	sA = GetCentre(pcA);
	sB = GetCentre(pcB);

	sTest.PointAt(sA.x, sA.y);
	AssertPointer(pcA, sTest.cEditor.GetHover());

	sTest.Click(sA.x, sA.y);
	AssertSize(1, pcSelection->NumComponents());
	AssertPointer(pcA, pcSelection->GetComponent(0));
	AssertSize(0, pcSelection->NumTraces());
	AssertNull(sTest.cEditor.GetHover());

	sTest.cEditor.SetModifiers(false, true);
	sTest.Click(sB.x, sB.y);
	AssertSize(2, pcSelection->NumComponents());
	AssertTrue(pcSelection->Contains(pcA));
	AssertTrue(pcSelection->Contains(pcB));

	sTest.cEditor.SetModifiers(true, true);
	sTest.Click(sA.x, sA.y);
	AssertSize(1, pcSelection->NumComponents());
	AssertPointer(pcB, pcSelection->GetComponent(0));

	sTest.cEditor.SetModifiers(false, false);
	sTest.Click(20.2, 20.2);
	AssertTrue(pcSelection->IsEmpty());

	sTest.Click(3, -2);
	AssertSize(0, pcSelection->NumComponents());
	AssertSize(1, pcSelection->NumTraces());
	AssertPointer(pcTrace, pcSelection->GetTrace(0));

	sTest.Drag(-10, -5, 0, 0);
	AssertSize(1, pcSelection->NumComponents());
	AssertPointer(pcA, pcSelection->GetComponent(0));
	AssertSize(0, pcSelection->NumTraces());

	sTest.Drag(-2, -3, 0, -1.5);
	AssertTrue(pcSelection->IsEmpty());

	sTest.Drag(0, -1.5, -2, -3);
	AssertSize(1, pcSelection->NumComponents());
	AssertPointer(pcA, pcSelection->GetComponent(0));
	AssertSize(1, pcSelection->NumTraces());
	AssertPointer(pcTrace, pcSelection->GetTrace(0));

	sTest.cEditor.StopEdit();
	AssertTrue(pcSelection->IsEmpty());

	sTest.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// A placed inverter follows the pointer until the button is pressed, then
// is made in the running simulation and wired: its input on the ground's
// wire, its output driving the output wire high.  The simulation can't run
// while it's being placed.  Escape takes out a component being placed.
//
//////////////////////////////////////////////////////////////////////////
void TestCircuitEditorPlace(void)
{
	SEditorTest			sTest;
	CCircuitView*		pcMain;
	CComponentView*		pcPlaced;

	sTest.Init();
	pcMain = sTest.cEditor.AddCircuit("Main");
	AddGroundAndOutput(pcMain);
	AssertTrue(sTest.cEditor.Simulate("Main"));
	sTest.Run();
	AssertInt(TV_Unsettled, sTest.GetLevel(3, -2));

	AssertFalse(sTest.cEditor.StartPlaceComponent("Inverter"));
	sTest.PointAt(10.3, 9.8);
	AssertTrue(sTest.cEditor.StartPlaceComponent("Inverter"));
	AssertTrue(sTest.cEditor.IsEditing());
	AssertFalse(sTest.cEditor.CanRun());
	AssertSize(2, pcMain->NumComponents());
	pcPlaced = pcMain->GetComponent(1);
	AssertString("Inverter", pcPlaced->GetType());
	AssertInt(10, pcPlaced->GetPosition().x);
	AssertInt(10, pcPlaced->GetPosition().y);
	AssertInt(ROT_East, pcPlaced->GetRotation());
	AssertNull(pcPlaced->GetComponent(sTest.cEditor.GetViewPath(), sTest.cEditor.GetSimulation()));

	sTest.PointAt(-2.9, -2.2);
	AssertInt(-3, pcPlaced->GetPosition().x);
	AssertInt(-2, pcPlaced->GetPosition().y);
	sTest.Press(-2.9, -2.2);
	AssertFalse(sTest.cEditor.IsEditing());
	AssertNotNull(pcPlaced->GetComponent(sTest.cEditor.GetViewPath(), sTest.cEditor.GetSimulation()));
	AssertTrue(sTest.cEditor.GetSelection()->IsEmpty());
	sTest.Run();
	AssertInt(TV_High, sTest.GetLevel(3, -2));

	sTest.Release(-2.9, -2.2);
	AssertSize(2, pcMain->NumComponents());

	sTest.PointAt(20, 20);
	AssertTrue(sTest.cEditor.StartPlaceComponent("Ground"));
	AssertSize(3, pcMain->NumComponents());
	sTest.cEditor.StopEdit();
	AssertSize(2, pcMain->NumComponents());
	AssertFalse(sTest.cEditor.IsEditing());

	sTest.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// Dragging a selected inverter away drags its wires with it: its input is
// routed back to the ground and its output wire, which ends on nothing,
// moves with it, so it stays wired up, and dragging it back too.
// It keeps the same component throughout (the simulation isn't remade)
// and the circuit's traces don't pile up.
//
//////////////////////////////////////////////////////////////////////////
void TestCircuitEditorMove(void)
{
	SEditorTest			sTest;
	CCircuitView*		pcMain;
	CInverterView*		pcInverter;
	CCircuitComponent*	pcComponent;
	SFloat64Vec2		sCentre;
	size				uiTraces;
	SInt32Vec2			sOldOut;

	sTest.Init();
	sOldOut.Init(3, -2);
	pcMain = sTest.cEditor.AddCircuit("Main");
	AddGroundAndOutput(pcMain);
	pcInverter = AddTestInverter(pcMain, -3, -2);
	AssertTrue(sTest.cEditor.Simulate("Main"));
	sTest.Run();
	AssertInt(TV_High, sTest.GetLevel(3, -2));
	pcComponent = pcInverter->GetComponent(sTest.cEditor.GetViewPath(), sTest.cEditor.GetSimulation());
	uiTraces = sTest.cEditor.GetSimulation()->GetCircuit()->NumTraces();

	sCentre = GetCentre(pcInverter);
	sTest.Click(sCentre.x, sCentre.y);
	AssertTrue(sTest.cEditor.GetSelection()->Contains(pcInverter));
	sTest.Drag(sCentre.x, sCentre.y, sCentre.x, sCentre.y + 10);
	AssertInt(-3, pcInverter->GetPosition().x);
	AssertInt(8, pcInverter->GetPosition().y);
	AssertTrue(sTest.cEditor.GetSelection()->Contains(pcInverter));
	sTest.Run();
	AssertInt(TV_High, sTest.GetLevel(6, 8));
	AssertNull(pcMain->GetTraceAt(sOldOut));
	AssertTrue(sTest.cEditor.GetSelection()->Contains(pcInverter));
	AssertSize(1, sTest.cEditor.GetSelection()->NumComponents());
	AssertSize(0, sTest.cEditor.GetSelection()->NumTraces());
	AssertPointer(pcComponent, pcInverter->GetComponent(sTest.cEditor.GetViewPath(), sTest.cEditor.GetSimulation()));

	sTest.Drag(sCentre.x, sCentre.y + 10, sCentre.x, sCentre.y);
	AssertInt(-2, pcInverter->GetPosition().y);
	sTest.Run();
	AssertInt(TV_High, sTest.GetLevel(6, -2));
	AssertPointer(pcComponent, pcInverter->GetComponent(sTest.cEditor.GetViewPath(), sTest.cEditor.GetSimulation()));
	AssertSize(uiTraces, sTest.cEditor.GetSimulation()->GetCircuit()->NumTraces());

	sTest.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// Two inverters fed from a ground's wire, one by a branch off the middle
// of it.  Moving that inverter routes its input back to the ground's net
// and takes its output wire with it; the other inverter is untouched.
//
//////////////////////////////////////////////////////////////////////////
void TestCircuitEditorMoveFromJunction(void)
{
	SEditorTest			sTest;
	CCircuitView*		pcMain;
	CGroundView*		pcGround;
	CInverterView*		pcInverter;
	SFloat64Vec2		sCentre;

	sTest.Init();
	pcMain = sTest.cEditor.AddCircuit("Main");
	pcGround = NewMalloc<CGroundView>();
	pcGround->Init(-8, -3, ROT_North, "");
	pcMain->Add(pcGround);
	pcMain->AddTrace(-8, -3, -8, 6);
	pcMain->AddTrace(-8, 0, -4, 0);
	pcMain->AddTrace(-8, 6, -4, 6);
	pcInverter = AddTestInverter(pcMain, -3, 0);
	AddTestInverter(pcMain, -3, 6);
	pcMain->AddTrace(-1, 0, 4, 0);
	pcMain->AddTrace(-1, 6, 4, 6);
	AssertTrue(sTest.cEditor.Simulate("Main"));
	sTest.Run();
	AssertInt(TV_High, sTest.GetLevel(4, 0));
	AssertInt(TV_High, sTest.GetLevel(4, 6));

	sCentre = GetCentre(pcInverter);
	sTest.Click(sCentre.x, sCentre.y);
	sTest.Drag(sCentre.x, sCentre.y, sCentre.x + 12, sCentre.y - 8);
	AssertInt(9, pcInverter->GetPosition().x);
	AssertInt(-8, pcInverter->GetPosition().y);
	sTest.Run();
	AssertInt(TV_High, sTest.GetLevel(16, -8));
	AssertInt(TV_High, sTest.GetLevel(4, 6));

	sTest.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// A ground wired down, across and down to an inverter's input.  Dragging
// the wire across down stretches it: while it's dragged the circuit isn't
// changed; when it's dropped new wire joins its ends back to the wires
// they were on, so the inverter is still driven.
//
//////////////////////////////////////////////////////////////////////////
void TestCircuitEditorMoveWire(void)
{
	SEditorTest			sTest;
	CCircuitView*		pcMain;
	CGroundView*		pcGround;
	size				uiTraces;
	SInt32Vec2			sPoint;

	sTest.Init();
	pcMain = sTest.cEditor.AddCircuit("Main");
	pcGround = NewMalloc<CGroundView>();
	pcGround->Init(0, -1, ROT_North, "");
	pcMain->Add(pcGround);
	pcMain->AddTrace(0, -1, 0, 5);
	pcMain->AddTrace(0, 5, 10, 5);
	pcMain->AddTrace(10, 5, 10, 10);
	AddTestInverter(pcMain, 11, 10);
	pcMain->AddTrace(13, 10, 18, 10);
	AssertTrue(sTest.cEditor.Simulate("Main"));
	sTest.Run();
	AssertInt(TV_High, sTest.GetLevel(15, 10));

	sTest.Click(5, 5);
	AssertSize(1, sTest.cEditor.GetSelection()->NumTraces());
	uiTraces = pcMain->NumTraces();
	sTest.Press(5, 5);
	sTest.PointAt(5, 8);
	AssertTrue(sTest.cEditor.IsEditing());
	AssertSize(uiTraces, pcMain->NumTraces());
	sPoint.Init(5, 8);
	AssertNotNull(pcMain->GetTraceAt(sPoint));

	sTest.Release(5, 8);
	AssertFalse(sTest.cEditor.IsEditing());
	sPoint.Init(5, 5);
	AssertNull(pcMain->GetTraceAt(sPoint));
	sPoint.Init(0, 7);
	AssertNotNull(pcMain->GetTraceAt(sPoint));
	sPoint.Init(10, 6);
	AssertNotNull(pcMain->GetTraceAt(sPoint));
	AssertSize(1, sTest.cEditor.GetSelection()->NumTraces());
	sPoint.Init(5, 8);
	AssertTrue(sTest.cEditor.GetSelection()->GetTrace(0)->Contains(sPoint));
	sTest.Run();
	AssertInt(TV_High, sTest.GetLevel(15, 10));

	sTest.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// Turning the inverter under the pointer turns it about the pointer, its
// wires following, and turns later placements too.  Deleting it takes its
// component out of the simulation and leaves the output undriven; deleting
// a selected wire takes it out of the circuit.
//
//////////////////////////////////////////////////////////////////////////
void TestCircuitEditorRotateAndDelete(void)
{
	SEditorTest			sTest;
	CCircuitView*		pcMain;
	CInverterView*		pcInverter;
	CCircuit*			pcCircuit;
	size				uiIntegratedCircuits;
	SInt32Vec2			sOutPoint;

	sTest.Init();
	pcMain = sTest.cEditor.AddCircuit("Main");
	AddGroundAndOutput(pcMain);
	pcInverter = AddTestInverter(pcMain, -3, -2);
	AssertTrue(sTest.cEditor.Simulate("Main"));
	sTest.Run();
	pcCircuit = sTest.cEditor.GetSimulation()->GetCircuit();
	uiIntegratedCircuits = pcCircuit->NumIntegratedCircuits();
	sOutPoint.Init(6, -2);

	sTest.PointAt(-1, -2);
	AssertPointer(pcInverter, sTest.cEditor.GetHover());
	sTest.cEditor.RotateRight();
	AssertInt(ROT_South, pcInverter->GetRotation());
	AssertInt(-1, pcInverter->GetPosition().x);
	AssertInt(-4, pcInverter->GetPosition().y);
	AssertInt(ROT_South, sTest.cEditor.GetCreationRotation());
	sTest.Run();
	AssertInt(TV_High, sTest.GetLevel(-1, 5));

	sTest.cEditor.RotateLeft();
	AssertInt(ROT_East, pcInverter->GetRotation());
	AssertInt(-3, pcInverter->GetPosition().x);
	AssertInt(-2, pcInverter->GetPosition().y);
	AssertInt(ROT_East, sTest.cEditor.GetCreationRotation());
	sTest.Run();
	AssertInt(TV_High, sTest.GetLevel(6, -2));

	sTest.PointAt(-2, -2);
	AssertPointer(pcInverter, sTest.cEditor.GetHover());
	AssertTrue(sTest.cEditor.Delete());
	AssertSize(1, pcMain->NumComponents());
	AssertSize(uiIntegratedCircuits - 1, pcCircuit->NumIntegratedCircuits());
	AssertNull(sTest.cEditor.GetHover());
	sTest.Run();
	AssertInt(TV_Unsettled, sTest.GetLevel(6, -2));

	sTest.Click(6, -2);
	AssertTrue(sTest.cEditor.GetSelection()->NumTraces() > 0);
	AssertTrue(sTest.cEditor.GetSelection()->GetTrace(0)->Contains(sOutPoint));
	AssertTrue(sTest.cEditor.Delete());
	AssertNull(pcMain->GetTraceAt(sOutPoint));
	AssertTrue(sTest.cEditor.GetSelection()->IsEmpty());
	AssertFalse(sTest.cEditor.Delete());

	sTest.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// A saved project loads with the same circuits, the same circuit being
// edited, the placement rotation and its simulation as it was.
//
//////////////////////////////////////////////////////////////////////////
void TestCircuitEditorSaveLoad(void)
{
	SEditorTest		sSaved;
	CCircuitEditor	cLoaded;
	CCircuitView*	pcMain;
	CFileUtil		cFileUtil;
	CXMLWriter		cSavedText;
	CXMLWriter		cLoadedText;
	SLogConfig		sLogConfig;

	sSaved.Init();
	pcMain = sSaved.cEditor.AddCircuit("Main");
	sSaved.cEditor.AddCircuit("Other");
	AddGroundAndOutput(pcMain);
	AssertTrue(sSaved.cEditor.Simulate("Main"));
	sSaved.PointAt(-3, -2);
	sSaved.cEditor.RotateRight();
	sSaved.cEditor.RotateLeft();
	sSaved.cEditor.RotateLeft();
	sSaved.cEditor.RotateRight();
	sSaved.cEditor.RotateRight();
	AssertTrue(sSaved.cEditor.StartPlaceComponent("Inverter"));
	sSaved.cEditor.RotateLeft();
	sSaved.Click(-3, -2);
	sSaved.Run();
	AssertInt(TV_High, sSaved.GetLevel(3, -2));
	AssertInt(ROT_East, sSaved.cEditor.GetCreationRotation());
	sSaved.PointAt(30, 30);
	sSaved.cEditor.RotateRight();

	cFileUtil.MakeDir("Output");
	AssertTrue(sSaved.cEditor.Save("Output" _FS_ "Editor.xml"));

	cLoaded.Init(&sSaved.cFamilies, NULL);
	AssertTrue(cLoaded.Load("Output" _FS_ "Editor.xml"));
	AssertString("Main", cLoaded.GetCircuit()->GetTypeName());
	AssertSize(2, cLoaded.GetCircuits()->NumCircuits());
	AssertInt(ROT_South, cLoaded.GetCreationRotation());
	AssertInt(TV_High, SEditorTest::GetEditorLevel(&cLoaded, &sSaved.cFamilies, 3, -2));
	AssertLong(sSaved.cEditor.GetSimulation()->GetTime(), cLoaded.GetSimulation()->GetTime());

	cSavedText.Init();
	sSaved.cEditor.GetCircuits()->SaveXML(&cSavedText);
	cLoadedText.Init();
	cLoaded.GetCircuits()->SaveXML(&cLoadedText);
	AssertString(cSavedText.GetText(), cLoadedText.GetText());
	cLoadedText.Kill();
	cSavedText.Kill();

	gcLogger.GetConfig(&sLogConfig);
	gcLogger.SetSilent();
	AssertFalse(cLoaded.Load("Output" _FS_ "Missing.xml"));
	gcLogger.SetConfig(&sLogConfig);
	AssertString("Main", cLoaded.GetCircuit()->GetTypeName());

	cLoaded.Kill();
	sSaved.Kill();
	cFileUtil.Delete("Output" _FS_ "Editor.xml");
	cFileUtil.RemoveDir("Output");
}


//////////////////////////////////////////////////////////////////////////
//
// An "Inverter" subcircuit: its In pin through an inverter to its Out
// pin.
//
//////////////////////////////////////////////////////////////////////////
static void AddEditorInverterSubcircuit(CCircuitEditor* pcEditor, CCircuitFonts* pcFonts)
{
	CCircuitView*	pcCircuit;
	CPinView*		pcPin;

	pcCircuit = pcEditor->AddCircuit("Inverter");
	pcPin = NewMalloc<CPinView>();
	pcPin->Init(-8, 3, ROT_East, "In", "LVC", false, 1, RADIX_Binary, pcFonts);
	pcPin->SetSubcircuitAppearance(PA_Left, PAN_Centre, 0, false, false);
	pcCircuit->Add(pcPin);
	pcCircuit->AddTrace(-8, 3, -4, 3);
	AddTestInverter(pcCircuit, -3, 3);
	pcCircuit->AddTrace(-1, 3, 3, 3);
	pcPin = NewMalloc<CPinView>();
	pcPin->Init(3, 3, ROT_West, "Out", "LVC", false, 1, RADIX_Binary, pcFonts);
	pcPin->SetSubcircuitAppearance(PA_Right, PAN_Centre, 0, false, false);
	pcCircuit->Add(pcPin);
}


//////////////////////////////////////////////////////////////////////////
//
// A placed instance of a subcircuit gets a path, an instance simulation
// and its subcircuit's components; deleting it takes them all away.  A
// circuit can't hold itself.
//
//////////////////////////////////////////////////////////////////////////
void TestCircuitEditorSubcircuit(void)
{
	SEditorTest					sTest;
	CCircuitFonts				cFonts;
	CCircuitView*				pcMain;
	CSubcircuitInstanceView*	pcInstance;
	CCircuitSimulation*			pcSimulation;
	size						uiPaths;
	size						uiIntegratedCircuits;
	SFloat64Vec2				sCentre;
	SLogConfig					sLogConfig;

	sTest.Init(&cFonts);
	LoadTestCircuitFonts(&cFonts);
	AddEditorInverterSubcircuit(&sTest.cEditor, &cFonts);
	pcMain = sTest.cEditor.AddCircuit("Main");
	AssertTrue(sTest.cEditor.Simulate("Main"));
	pcSimulation = sTest.cEditor.GetSimulation();
	uiPaths = sTest.cEditor.GetCircuits()->GetViewPaths()->NumViewPaths();
	uiIntegratedCircuits = pcSimulation->GetCircuit()->NumIntegratedCircuits();

	sTest.PointAt(0, 0);
	gcLogger.GetConfig(&sLogConfig);
	gcLogger.SetSilent();
	AssertFalse(sTest.cEditor.StartPlaceSubcircuit("Main"));
	AssertFalse(sTest.cEditor.StartPlaceSubcircuit("Missing"));
	gcLogger.SetConfig(&sLogConfig);
	AssertTrue(sTest.cEditor.StartPlaceSubcircuit("Inverter"));
	sTest.Click(5, 5);
	AssertSize(1, pcMain->NumComponents());
	pcInstance = (CSubcircuitInstanceView*)pcMain->GetComponent(0);
	AssertString("Inverter", pcInstance->GetTypeName());
	AssertSize(uiPaths + 1, sTest.cEditor.GetCircuits()->GetViewPaths()->NumViewPaths());
	AssertSize(1, pcSimulation->NumInstanceSimulations());
	AssertSize(uiIntegratedCircuits + 1, pcSimulation->GetCircuit()->NumIntegratedCircuits());
	AssertNotNull(pcInstance->GetComponent(sTest.cEditor.GetViewPath(), pcSimulation));

	sTest.cEditor.StopEdit();
	sCentre = GetCentre(pcInstance);
	sTest.PointAt(sCentre.x, sCentre.y);
	AssertPointer(pcInstance, sTest.cEditor.GetHover());
	AssertTrue(sTest.cEditor.Delete());
	AssertSize(0, pcMain->NumComponents());
	AssertSize(uiPaths, sTest.cEditor.GetCircuits()->GetViewPaths()->NumViewPaths());
	AssertSize(0, pcSimulation->NumInstanceSimulations());
	AssertSize(uiIntegratedCircuits, pcSimulation->GetCircuit()->NumIntegratedCircuits());
	AssertSize(0, pcSimulation->GetCircuit()->NumPassives());

	KillTestCircuitFonts(&cFonts);
	sTest.Kill(true);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
static void AssertTraceLine(int32 x0, int32 y0, int32 x1, int32 y1, CArrayTraceLine* pasLines, size uiIndex)
{
	STraceLine*	psLine;

	psLine = pasLines->Get(uiIndex);
	AssertInt(x0, psLine->sStart.x);
	AssertInt(y0, psLine->sStart.y);
	AssertInt(x1, psLine->sEnd.x);
	AssertInt(y1, psLine->sEnd.y);
}


//////////////////////////////////////////////////////////////////////////
//
// Lines along each other that overlap or meet end to end merge; a T is
// split where its stem ends; lines that cross aren't; a port splits the
// line it's on.
//
//////////////////////////////////////////////////////////////////////////
void TestCircuitEditorTraceLines(void)
{
	CArrayTraceLine		asLines;
	CArrayInt32Vec2		asEnds;
	CArrayInt32Vec2		asPorts;
	SInt32Vec2			sPoint;

	asLines.Init();
	asLines.Add()->Init(0, 0, 5, 0);
	asLines.Add()->Init(9, 0, 5, 0);
	asLines.Add()->Init(2, 3, 2, 7);
	asLines.Add()->Init(2, 5, 2, 9);
	asLines.Add()->Init(4, 4, 4, 4);
	MergeTraceLines(&asLines);
	AssertSize(2, asLines.NumElements());
	AssertTraceLine(0, 0, 9, 0, &asLines, 0);
	AssertTraceLine(2, 3, 2, 9, &asLines, 1);
	asLines.Kill();

	asLines.Init();
	asEnds.Init();
	asPorts.Init();
	asLines.Add()->Init(0, 0, 10, 0);
	asLines.Add()->Init(5, 0, 5, 5);
	asLines.Add()->Init(20, 0, 30, 0);
	asLines.Add()->Init(25, -5, 25, 5);
	sPoint.Init(5, 5);
	asEnds.Add(&sPoint);
	sPoint.Init(5, 0);
	asEnds.Add(&sPoint);
	sPoint.Init(25, -5);
	asEnds.Add(&sPoint);
	sPoint.Init(25, 5);
	asEnds.Add(&sPoint);
	sPoint.Init(28, 0);
	asPorts.Add(&sPoint);
	SplitTraceLines(&asLines, &asEnds, &asPorts);
	AssertSize(6, asLines.NumElements());
	AssertTraceLine(0, 0, 5, 0, &asLines, 0);
	AssertTraceLine(5, 0, 5, 5, &asLines, 1);
	AssertTraceLine(20, 0, 28, 0, &asLines, 2);
	AssertTraceLine(25, -5, 25, 5, &asLines, 3);
	AssertTraceLine(5, 0, 10, 0, &asLines, 4);
	AssertTraceLine(28, 0, 30, 0, &asLines, 5);
	asPorts.Kill();
	asEnds.Kill();
	asLines.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// A ground wired to an inverter.  A wire pulled out of the inverter's
// output is wired live.  A wire pulled on from a wire's end merges with
// it; one pulled
// from the middle of a wire makes a T on its net.  Deleting the hovered
// stem of the T leaves the wire it was on whole again.  A click on a wire
// selects it.
//
//////////////////////////////////////////////////////////////////////////
void TestCircuitEditorPullWire(void)
{
	SEditorTest			sTest;
	CCircuitView*		pcMain;
	CGroundView*		pcGround;
	SInt32Vec2			sConnection;
	SInt32Vec2			sPoint;
	CTraceView*			pcTrace;

	sTest.Init();
	pcMain = sTest.cEditor.AddCircuit("Main");
	pcGround = NewMalloc<CGroundView>();
	pcGround->Init(-8, -3, ROT_North, "");
	pcMain->Add(pcGround);
	pcMain->AddTraces(-8, -3, -4, -2);
	AddTestInverter(pcMain, -3, -2);
	AssertTrue(sTest.cEditor.Simulate("Main"));

	sTest.PointAt(-1, -2);
	AssertTrue(sTest.cEditor.GetHoverConnection(&sConnection));
	AssertInt(-1, sConnection.x);
	AssertInt(-2, sConnection.y);
	AssertNull(sTest.cEditor.GetHoverTrace());
	sTest.Press(-1, -2);
	sTest.PointAt(3, -2);
	AssertTrue(sTest.cEditor.IsEditing());
	sTest.PointAt(6, -2);
	sTest.Release(6, -2);
	AssertSize(3, pcMain->NumTraces());
	sTest.Run();
	AssertInt(TV_High, sTest.GetLevel(3, -2));
	AssertTrue(sTest.cEditor.GetSelection()->IsEmpty());

	sTest.PointAt(6, -2);
	AssertTrue(sTest.cEditor.GetHoverConnection(&sConnection));
	AssertNull(sTest.cEditor.GetHoverTrace());
	sTest.Drag(6, -2, 10, -2);
	AssertSize(3, pcMain->NumTraces());
	sPoint.Init(8, -2);
	pcTrace = pcMain->GetTraceAt(sPoint);
	AssertInt(-1, pcTrace->GetStart().x);
	AssertInt(10, pcTrace->GetEnd().x);

	sTest.PointAt(3, -2);
	AssertNotNull(sTest.cEditor.GetHoverTrace());
	sTest.Drag(3, -2, 3, 4);
	AssertSize(5, pcMain->NumTraces());
	sTest.Run();
	AssertInt(TV_High, sTest.GetLevel(3, 4));
	AssertInt(TV_High, sTest.GetLevel(8, -2));

	sTest.PointAt(3, 2);
	AssertNotNull(sTest.cEditor.GetHoverTrace());
	AssertTrue(sTest.cEditor.Delete());
	AssertSize(3, pcMain->NumTraces());
	pcTrace = pcMain->GetTraceAt(sPoint);
	AssertInt(-1, pcTrace->GetStart().x);
	AssertInt(10, pcTrace->GetEnd().x);
	sTest.Run();
	AssertInt(TV_High, sTest.GetLevel(8, -2));

	sTest.Click(8, -2);
	AssertSize(1, sTest.cEditor.GetSelection()->NumTraces());
	AssertPointer(pcTrace, sTest.cEditor.GetSelection()->GetTrace(0));

	sTest.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// A wire pulled from the ground's port and released on the inverter's
// input is routed around a box in the way, not drawn as pulled through it,
// and wires them up.
//
//////////////////////////////////////////////////////////////////////////
void TestCircuitEditorRouteWire(void)
{
	SEditorTest			sTest;
	CCircuitView*		pcMain;
	CGroundView*		pcGround;
	CLabelView*			pcLabel;
	SFloat64Vec2		sMinimum;
	SFloat64Vec2		sMaximum;
	SInt32Vec2			sPoint;
	size				i;
	int32				x;

	sTest.Init();
	pcMain = sTest.cEditor.AddCircuit("Main");
	pcGround = NewMalloc<CGroundView>();
	pcGround->Init(-8, -3, ROT_North, "");
	pcMain->Add(pcGround);
	AddTestInverter(pcMain, -3, -2);
	pcMain->AddTrace(-1, -2, 6, -2);
	sMinimum.Init(-1, -1);
	sMaximum.Init(1, 1);
	pcLabel = NewMalloc<CLabelView>();
	pcLabel->Init(-6, -3, ROT_East, "", TA_Left, false, true, true, sMinimum, sMaximum);
	pcMain->Add(pcLabel);
	AssertTrue(sTest.cEditor.Simulate("Main"));

	sTest.Press(-8, -3);
	sTest.PointAt(-4, -3);
	sTest.PointAt(-4, -2);
	sTest.Release(-4, -2);
	sTest.Run();
	AssertInt(TV_High, sTest.GetLevel(3, -2));

	for (x = -7; x <= -5; x++)
	{
		sPoint.Init(x, -3);
		for (i = 0; i < pcMain->NumTraces(); i++)
		{
			AssertFalse(pcMain->GetTrace(i)->Contains(sPoint));
		}
	}

	sTest.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// Every component in the libraries can be placed, every component that can
// be placed (but a subcircuit instance) is in exactly one library, and the
// filter finds components by every word, in any case, of their names,
// descriptions, keywords and libraries.
//
//////////////////////////////////////////////////////////////////////////
void TestCircuitEditorComponentLibraries(void)
{
	CCircuitFonts			cFonts;
	CCircuitView			cCircuit;
	SComponentLibrary*		psLibrary;
	SComponentLibrary*		psLogic;
	SComponentLibraryEntry*	psEntry;
	CComponentView*			pcView;
	size					i;
	size					j;
	size					k;
	int						iFound;
	const char*				szXMLName;

	ObjectsInit();
	LoadTestCircuitFonts(&cFonts);
	cCircuit.Init();

	for (i = 0; i < NumComponentLibraries(); i++)
	{
		psLibrary = GetComponentLibrary(i);
		AssertTrue(psLibrary->uiNumEntries > 0);
		for (j = 0; j < psLibrary->uiNumEntries; j++)
		{
			psEntry = &psLibrary->asEntries[j];
			pcView = NewPlacedComponentView(psEntry->szXMLName, 0, 0, ROT_East, &cCircuit, &cFonts);
			AssertNotNull(pcView);
			AssertString(psEntry->szXMLName, pcView->GetXMLName());
			SafeKill(pcView);
		}
	}
	AssertNull(GetComponentLibrary(NumComponentLibraries()));

	for (k = 0; k < NumComponentViewTypes(); k++)
	{
		szXMLName = GetComponentViewXMLName(k);
		if (StringCompare(szXMLName, "Subcircuit") == 0)
		{
			continue;
		}
		iFound = 0;
		for (i = 0; i < NumComponentLibraries(); i++)
		{
			psLibrary = GetComponentLibrary(i);
			for (j = 0; j < psLibrary->uiNumEntries; j++)
			{
				if (StringCompare(psLibrary->asEntries[j].szXMLName, szXMLName) == 0)
				{
					iFound++;
				}
			}
		}
		AssertInt(1, iFound);
	}

	psLogic = GetComponentLibrary(0);
	AssertString("Generic Logic", psLogic->szName);
	AssertString("74' Series", GetComponentLibrary(1)->szName);
	AssertString("InverterPackage", GetComponentLibrary(1)->asEntries[0].szXMLName);
	AssertString("AndGate", psLogic->asEntries[0].szXMLName);
	AssertTrue(ComponentMatchesFilter(psLogic, &psLogic->asEntries[0], ""));
	AssertTrue(ComponentMatchesFilter(psLogic, &psLogic->asEntries[0], "  "));
	AssertTrue(ComponentMatchesFilter(psLogic, &psLogic->asEntries[0], "and"));
	AssertTrue(ComponentMatchesFilter(psLogic, &psLogic->asEntries[0], "AND gate"));
	AssertTrue(ComponentMatchesFilter(psLogic, &psLogic->asEntries[0], "generic high"));
	AssertFalse(ComponentMatchesFilter(psLogic, &psLogic->asEntries[0], "and clock"));
	AssertFalse(ComponentMatchesFilter(psLogic, &psLogic->asEntries[0], "xor"));
	AssertTrue(TextMatchesFilter("Inverter", "VERT"));
	AssertFalse(TextMatchesFilter("Inverter", "Inverters"));
	AssertFalse(TextMatchesFilter(NULL, "a"));

	cCircuit.Kill();
	KillTestCircuitFonts(&cFonts);
	ObjectsFlush();
	ObjectsKill(false);
}


//////////////////////////////////////////////////////////////////////////
//
// Placing a unit of a part placed as its units goes straight on to placing
// its next unit, under the pointer, until the part's last is placed.
// Stopping the edit while placing a unit stops there.  Deleting a unit
// deletes all its part's units.
//
//////////////////////////////////////////////////////////////////////////
void TestCircuitEditorPlaceUnits(void)
{
	SEditorTest				sTest;
	CCircuitView*			pcMain;
	CInverterUnitView*		pcUnit;
	int						i;

	sTest.Init();
	pcMain = sTest.cEditor.AddCircuit("Main");
	AssertTrue(sTest.cEditor.Simulate("Main"));

	sTest.PointAt(0, 0);
	AssertTrue(sTest.cEditor.StartPlaceComponent("InverterUnit"));
	for (i = 0; i < 6; i++)
	{
		AssertTrue(sTest.cEditor.IsEditing());
		AssertSize(i + 1, pcMain->NumComponents());
		sTest.Click(6 * i, 0);
	}
	AssertFalse(sTest.cEditor.IsEditing());
	AssertSize(6, pcMain->NumComponents());
	for (i = 0; i < 6; i++)
	{
		pcUnit = (CInverterUnitView*)pcMain->GetComponent(i);
		AssertString("InverterUnit", pcUnit->GetXMLName());
		AssertChar((char)('A' + i), pcUnit->GetUnitLetter());
		AssertInt(6 * i, pcUnit->GetPosition().x);
		AssertNotNull(pcUnit->GetComponent(sTest.cEditor.GetViewPath(), sTest.cEditor.GetSimulation()));
	}

	//Stopped while placing the second unit: only the first is placed.
	sTest.PointAt(0, 10);
	AssertTrue(sTest.cEditor.StartPlaceComponent("InverterUnit"));
	sTest.Click(0, 10);
	AssertTrue(sTest.cEditor.IsEditing());
	AssertSize(8, pcMain->NumComponents());
	sTest.cEditor.StopEdit();
	AssertFalse(sTest.cEditor.IsEditing());
	AssertSize(7, pcMain->NumComponents());

	//A component of one isn't followed by anything.
	sTest.PointAt(0, 20);
	AssertTrue(sTest.cEditor.StartPlaceComponent("Inverter"));
	sTest.Click(0, 20);
	AssertFalse(sTest.cEditor.IsEditing());
	AssertSize(8, pcMain->NumComponents());

	//The units are named as one part, and the next part's as another.
	AssertString("U1", pcMain->GetComponent(0)->GetName());
	AssertString("U1", pcMain->GetComponent(5)->GetName());
	AssertString("U2", pcMain->GetComponent(6)->GetName());

	//Deleting one unit deletes only that unit.
	sTest.cEditor.StopEdit();
	sTest.PointAt(12, 0);
	AssertTrue(sTest.cEditor.GetHover() == pcMain->GetComponent(2));
	AssertTrue(sTest.cEditor.Delete());
	AssertSize(7, pcMain->NumComponents());
	AssertChar('B', ((CInverterUnitView*)pcMain->GetComponent(1))->GetUnitLetter());
	AssertChar('D', ((CInverterUnitView*)pcMain->GetComponent(2))->GetUnitLetter());
	AssertString("U1", pcMain->GetComponent(4)->GetName());
	AssertString("U2", pcMain->GetComponent(5)->GetName());
	AssertString("Inverter", pcMain->GetComponent(6)->GetXMLName());

	sTest.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// Every component in the libraries placed into a running simulation, as
// the tester places them from its component chooser, with nothing set up
// for them beforehand (a W65C816 once crashed as its instructions hadn't
// been made), starts, runs and is drawn.
//
//////////////////////////////////////////////////////////////////////////
void TestCircuitEditorPlaceEveryComponent(void)
{
	SEditorTest				sTest;
	CCircuitFonts			cFonts;
	CCircuitView*			pcMain;
	CComponentView*			pcView;
	CCircuitColours			cColours;
	CFileUtil				cFileUtil;
	SComponentLibrary*		psLibrary;
	size					i;
	size					j;
	size					k;
	int32					x;

	sTest.Init(&cFonts);
	LoadTestCircuitFonts(&cFonts);
	cColours.InitLogicim();
	pcMain = sTest.cEditor.AddCircuit("Main");
	AssertTrue(sTest.cEditor.Simulate("Main"));

	x = 0;
	for (i = 0; i < NumComponentLibraries(); i++)
	{
		psLibrary = GetComponentLibrary(i);
		for (j = 0; j < psLibrary->uiNumEntries; j++)
		{
			sTest.PointAt(x, 0);
			AssertTrue(sTest.cEditor.StartPlaceComponent(psLibrary->asEntries[j].szXMLName));
			sTest.Click(x, 0);
			for (k = 0; (k < 26) && sTest.cEditor.IsEditing(); k++)
			{
				//A part placed as its units goes on to its next unit.
				x += 6;
				sTest.Click(x, 0);
			}
			AssertFalse(sTest.cEditor.IsEditing());
			pcView = pcMain->GetComponent(pcMain->NumComponents() - 1);
			AssertString(psLibrary->asEntries[j].szXMLName, pcView->GetXMLName());
			if (pcView->MakesComponent())
			{
				AssertNotNull(pcView->GetComponent(sTest.cEditor.GetViewPath(), sTest.cEditor.GetSimulation()));
			}
			sTest.cEditor.GetSimulation()->RunToTime(100000);
			x += 60;
		}
	}
	sTest.cEditor.GetSimulation()->RunToTime(1000000);
	cFileUtil.MakeDir("Output");
	AssertTrue(RenderCircuitPNG(pcMain, &cColours, 400, 400, 0.2, sTest.cEditor.GetViewPath(), sTest.cEditor.GetSimulation(), false, "Output" _FS_ "PlacedComponents.png", &cFonts));

	cFileUtil.Delete("Output" _FS_ "PlacedComponents.png");
	cFileUtil.RemoveDir("Output");
	cColours.Kill();
	KillTestCircuitFonts(&cFonts);
	sTest.Kill(true);
}


//////////////////////////////////////////////////////////////////////////
//
// The pointer moved to a pixel on a canvas showing the circuit through the
// viewport, as CCircuitCanvas::MovedOver passes it to the editor.
//
//////////////////////////////////////////////////////////////////////////
static void PointAtPixel(SEditorTest* psTest, CCircuitViewport* pcViewport, int32 x, int32 y)
{
	SFloat64Vec2	sScreen;
	SFloat64Vec2	sGrid;

	sScreen.Init(x, y);
	pcViewport->ScreenToGrid(&sGrid, &sScreen);
	psTest->cEditor.PointerMoved(sGrid);
}


//////////////////////////////////////////////////////////////////////////
//
// The editor painted through the viewport into an image as the circuit
// canvas paints it (see CCircuitPainter::InitImage), and the box around
// the pixels of its hover colour that aren't blended with anything.  False
// if there are none.
//
//////////////////////////////////////////////////////////////////////////
static bool GetPaintedHoverBox(CCircuitEditor* pcEditor, CCircuitViewport* pcViewport, CCircuitColours* pcColours, SInt32Vec2* psMinimum, SInt32Vec2* psMaximum)
{
	Ptr<CImage>			pImage;
	Ptr<CGeometryMap>	pMap;
	Ptr<CSpriteMap>		pSprites;
	CCircuitPainter		cPainter;
	SInt32Vec2			sSize;
	uint8*				puiPixel;
	uint8				uiRed;
	uint8				uiGreen;
	uint8				uiBlue;
	int32				x;
	int32				y;
	bool				bFound;

	sSize = pcViewport->GetSize();
	pImage = OMalloc<CImage>(sSize.x, sSize.y, PT_uint8, IMAGE_DIFFUSE_RED, IMAGE_DIFFUSE_GREEN, IMAGE_DIFFUSE_BLUE, CHANNEL_STOP);
	pMap = OMalloc<CGeometryMap>();
	pSprites = OMalloc<CSpriteMap>();

	cPainter.InitImage(pImage, pcViewport, &pMap, &pSprites, pcColours, NULL, pcEditor->GetViewPath(), pcEditor->GetSimulation());
	pcEditor->Paint(&cPainter);
	AssertTrue(cPainter.BlitImage());
	cPainter.Kill();

	uiRed = (uint8)Get8BitRedColour(pcColours->msPortHover);
	uiGreen = (uint8)Get8BitGreenColour(pcColours->msPortHover);
	uiBlue = (uint8)Get8BitBlueColour(pcColours->msPortHover);
	bFound = false;
	for (y = 0; y < sSize.y; y++)
	{
		for (x = 0; x < sSize.x; x++)
		{
			puiPixel = &((uint8*)pImage->GetData())[(x + y * sSize.x) * 3];
			if ((puiPixel[0] == uiRed) && (puiPixel[1] == uiGreen) && (puiPixel[2] == uiBlue))
			{
				if (!bFound)
				{
					psMinimum->Init(x, y);
					psMaximum->Init(x, y);
					bFound = true;
				}
				else
				{
					if (x < psMinimum->x) psMinimum->x = x;
					if (y < psMinimum->y) psMinimum->y = y;
					if (x > psMaximum->x) psMaximum->x = x;
					if (y > psMaximum->y) psMaximum->y = y;
				}
			}
		}
	}
	return bFound;
}


//////////////////////////////////////////////////////////////////////////
//
// Zoomed in on a canvas whose middle isn't on a pixel, with the view
// scrolled, the pointer anywhere within a little under half a grid unit
// of a port, either side of it, hovers that port and the hover ring is
// painted centred on it.
//
//////////////////////////////////////////////////////////////////////////
void TestCircuitEditorPortHover(void)
{
	SEditorTest			sTest;
	CCircuitView*		pcMain;
	CInverterView*		pcInverter;
	CPortView*			pcPort;
	CCircuitViewport	cViewport;
	CCircuitColours		cColours;
	SInt32Vec2			sPort;
	SInt32Vec2			sHover;
	SFloat64Vec2		sGrid;
	SFloat64Vec2		sScreen;
	SInt32Vec2			sMinimum;
	SInt32Vec2			sMaximum;
	float64				fNear;
	size				i;
	int					iDX;
	int					iDY;

	sTest.Init();
	cColours.InitLogicim();
	pcMain = sTest.cEditor.AddCircuit("Main");
	pcInverter = AddTestInverter(pcMain, -3, -2);
	AssertTrue(sTest.cEditor.Simulate("Main"));

	cViewport.Init(401, 301);
	cViewport.SetZoom(4);
	cViewport.SetPosition(37, -23);
	fNear = 0.4 * cViewport.GetPixelsPerGrid();

	AssertSize(2, pcInverter->NumPortViews());
	for (i = 0; i < pcInverter->NumPortViews(); i++)
	{
		pcPort = pcInverter->GetPortView(i);
		sPort = pcPort->GetGridPosition();
		sGrid.Init(sPort.x, sPort.y);
		cViewport.GridToScreen(&sScreen, &sGrid);

		for (iDY = -1; iDY <= 1; iDY++)
		{
			for (iDX = -1; iDX <= 1; iDX++)
			{
				PointAtPixel(&sTest, &cViewport, (int32)floor(sScreen.x + iDX * fNear + 0.5), (int32)floor(sScreen.y + iDY * fNear + 0.5));
				AssertTrue(sTest.cEditor.GetHoverConnection(&sHover));
				AssertInt(sPort.x, sHover.x);
				AssertInt(sPort.y, sHover.y);
			}
		}

		PointAtPixel(&sTest, &cViewport, (int32)floor(sScreen.x + 0.5), (int32)floor(sScreen.y + 0.5));
		AssertTrue(GetPaintedHoverBox(&sTest.cEditor, &cViewport, &cColours, &sMinimum, &sMaximum));
		AssertDouble(sScreen.x, (sMinimum.x + sMaximum.x) / 2.0, 0);
		AssertDouble(sScreen.y, (sMinimum.y + sMaximum.y) / 2.0, 0);
	}

	cViewport.Kill();
	cColours.Kill();
	sTest.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// The pointer aimed at a point in grid space on a canvas showing the
// circuit through the viewport: the pixel nearest it, as the canvas passes
// it to the editor.
//
//////////////////////////////////////////////////////////////////////////
static SFloat64Vec2 AimAt(CCircuitViewport* pcViewport, float64 x, float64 y)
{
	SFloat64Vec2	sGrid;
	SFloat64Vec2	sScreen;

	sGrid.Init(x, y);
	pcViewport->GridToScreen(&sScreen, &sGrid);
	sScreen.Init(floor(sScreen.x + 0.5), floor(sScreen.y + 0.5));
	pcViewport->ScreenToGrid(&sGrid, &sScreen);
	return sGrid;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
static void MoveOnCanvas(CCircuitEditor* pcEditor, CCircuitViewport* pcViewport, float64 x, float64 y)
{
	pcEditor->PointerMoved(AimAt(pcViewport, x, y));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
static void PressOnCanvas(CCircuitEditor* pcEditor, CCircuitViewport* pcViewport, float64 x, float64 y)
{
	MoveOnCanvas(pcEditor, pcViewport, x, y);
	pcEditor->ButtonPressed(AimAt(pcViewport, x, y));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
static void ReleaseOnCanvas(CCircuitEditor* pcEditor, CCircuitViewport* pcViewport, float64 x, float64 y)
{
	MoveOnCanvas(pcEditor, pcViewport, x, y);
	pcEditor->ButtonReleased(AimAt(pcViewport, x, y));
}


//////////////////////////////////////////////////////////////////////////
//
// A drag through each of the points in turn, as a wire is drawn: pressed
// on the first, released on the last.
//
//////////////////////////////////////////////////////////////////////////
static void DragOnCanvas(CCircuitEditor* pcEditor, CCircuitViewport* pcViewport, SInt32Vec2* asPoints, size uiNumPoints)
{
	size	i;

	PressOnCanvas(pcEditor, pcViewport, asPoints[0].x, asPoints[0].y);
	for (i = 1; i < uiNumPoints; i++)
	{
		MoveOnCanvas(pcEditor, pcViewport, asPoints[i].x, asPoints[i].y);
	}
	ReleaseOnCanvas(pcEditor, pcViewport, asPoints[uiNumPoints - 1].x, asPoints[uiNumPoints - 1].y);
}


//////////////////////////////////////////////////////////////////////////
//
// Placed as from the component chooser: the pointer on the canvas at the
// grid point, the component picked, and a click to put it down.
//
//////////////////////////////////////////////////////////////////////////
static CComponentView* PlaceOnCanvas(CCircuitEditor* pcEditor, CCircuitViewport* pcViewport, const char* szXMLName, int32 x, int32 y)
{
	CCircuitView*	pcCircuit;

	pcCircuit = pcEditor->GetCircuit();
	MoveOnCanvas(pcEditor, pcViewport, x, y);
	AssertTrue(pcEditor->StartPlaceComponent(szXMLName));
	PressOnCanvas(pcEditor, pcViewport, x, y);
	ReleaseOnCanvas(pcEditor, pcViewport, x, y);
	AssertFalse(pcEditor->IsEditing());
	return pcCircuit->GetComponent(pcCircuit->NumComponents() - 1);
}


//////////////////////////////////////////////////////////////////////////
//
// The simulation running on, as the tester's tick runs it; it can't while
// an edit is in progress.
//
//////////////////////////////////////////////////////////////////////////
static void RunOnCanvas(CCircuitEditor* pcEditor, int64 iTimeForward)
{
	AssertTrue(pcEditor->CanRun());
	pcEditor->GetSimulation()->RunToTime(iTimeForward);
}


//////////////////////////////////////////////////////////////////////////
//
// The simulated port of a component's port view.
//
//////////////////////////////////////////////////////////////////////////
static CLogicPort* GetSimulatedPort(CCircuitEditor* pcEditor, CComponentView* pcComponent, const char* szPortName)
{
	CPortView*	pcPortView;
	CPort*		pcPort;

	pcPortView = pcComponent->GetPortView(szPortName);
	AssertNotNull(pcPortView);
	AssertSize(1, pcPortView->NumPorts(pcEditor->GetViewPath(), pcEditor->GetSimulation()));
	pcPort = pcPortView->GetPort(pcEditor->GetViewPath(), pcEditor->GetSimulation(), 0);
	AssertTrue(pcPort->IsLogicPort());
	return (CLogicPort*)pcPort;
}


//////////////////////////////////////////////////////////////////////////
//
// The rising edges of the voltage a port drives, sampled: their number and
// the average time between them.
//
//////////////////////////////////////////////////////////////////////////
struct SRisingEdges
{
	CLogicPort*	pcPort;
	bool		bHigh;
	size		uiRises;
	int64		iFirstRise;
	int64		iLastRise;

	void Init(CLogicPort* pcLogicPort, int64 iTime)
	{
		pcPort = pcLogicPort;
		bHigh = IsHigh(iTime);
		uiRises = 0;
		iFirstRise = 0;
		iLastRise = 0;
	}

	//NaN, when the port doesn't drive, isn't high.
	bool IsHigh(int64 iTime)
	{
		return pcPort->GetVoltageOut(iTime) > pcPort->GetVCC(iTime) / 2;
	}

	void Sample(int64 iTime)
	{
		bool	bNowHigh;

		bNowHigh = IsHigh(iTime);
		if (bNowHigh && !bHigh)
		{
			if (uiRises == 0)
			{
				iFirstRise = iTime;
			}
			iLastRise = iTime;
			uiRises++;
		}
		bHigh = bNowHigh;
	}

	int64 GetPeriod(void)
	{
		return (uiRises < 2) ? 0 : (iLastRise - iFirstRise) / (int64)(uiRises - 1);
	}
};


//////////////////////////////////////////////////////////////////////////
//
// Drawn on the canvas, zoomed in: a D flip flop is placed and a clock
// beside it, and a wire is dragged from the clock's output to the flip
// flop's clock input.  The simulation runs a while and is paused, and a
// wire drawn round it clear of its box, from the flip flop's inverted
// output out, down, under it, up its left side and into its D input (as
// three drags, each from the end of the last), feeds it back.  Both wires
// join their ports in the simulation, and once it runs again Q toggles on
// every rising clock, at half the clock's frequency.  It starts by
// itself, as the flip flop drives Q and QB from when it's made.
//
//////////////////////////////////////////////////////////////////////////
void TestCircuitEditorDrawClockDivider(void)
{
	SEditorTest			sTest;
	CCircuitEditor*		pcEditor;
	CCircuitViewport	cViewport;
	CComponentView*		pcFlipFlop;
	CComponentView*		pcClock;
	CLogicPort*			pcClockOut;
	CLogicPort*			pcClockIn;
	CLogicPort*			pcData;
	CLogicPort*			pcInverted;
	CLogicPort*			pcQ;
	SInt32Vec2			sClockOut;
	SInt32Vec2			sClockIn;
	SInt32Vec2			sData;
	SInt32Vec2			sInverted;
	SInt32Vec2			asClockWire[3];
	SInt32Vec2			asOutAndDown[3];
	SInt32Vec2			asUnderAndUp[3];
	SInt32Vec2			asIn[2];
	SFloat64Vec2		sMinimum;
	SFloat64Vec2		sMaximum;
	SRisingEdges		sClockEdges;
	SRisingEdges		sQEdges;
	int64				iClockPeriod;
	int64				iStep;
	int64				iTime;
	int32				iLeft;
	int32				iRight;
	int32				iBottom;

	sTest.Init();
	pcEditor = &sTest.cEditor;
	pcEditor->AddCircuit("Main");
	AssertTrue(pcEditor->Simulate("Main"));
	cViewport.Init(801, 601);
	cViewport.SetZoom(4);

	pcFlipFlop = PlaceOnCanvas(pcEditor, &cViewport, "DTypeFlipFlop", 0, 0);
	sClockIn = pcFlipFlop->GetPortView("CP")->GetGridPosition();
	sData = pcFlipFlop->GetPortView("D")->GetGridPosition();
	sInverted = pcFlipFlop->GetPortView("QB")->GetGridPosition();
	pcClock = PlaceOnCanvas(pcEditor, &cViewport, "Clock", sClockIn.x - 5, sClockIn.y);
	sClockOut = pcClock->GetPortView("Output")->GetGridPosition();
	AssertInt(sClockIn.y, sClockOut.y);
	iClockPeriod = (int64)(1024.0 * 1000000000.0 / ((CClockView*)pcClock)->GetFrequency());

	asClockWire[0] = sClockOut;
	asClockWire[1].Init((sClockOut.x + sClockIn.x) / 2, sClockOut.y);
	asClockWire[2] = sClockIn;
	DragOnCanvas(pcEditor, &cViewport, asClockWire, 3);

	RunOnCanvas(pcEditor, iClockPeriod * 5);

	//Paused: from the inverted output out, down, under the flip flop, up past its left side and into D, two grid
	//units clear of its box all the way round.
	AssertTrue(pcFlipFlop->GetBoundingBox(&sMinimum, &sMaximum));
	iLeft = (int32)floor(sMinimum.x) - 2;
	iRight = (int32)ceil(sMaximum.x) + 2;
	iBottom = (int32)ceil(sMaximum.y) + 2;
	asOutAndDown[0] = sInverted;
	asOutAndDown[1].Init(iRight, sInverted.y);
	asOutAndDown[2].Init(iRight, iBottom);
	DragOnCanvas(pcEditor, &cViewport, asOutAndDown, 3);
	asUnderAndUp[0] = asOutAndDown[2];
	asUnderAndUp[1].Init(iLeft, iBottom);
	asUnderAndUp[2].Init(iLeft, sData.y);
	DragOnCanvas(pcEditor, &cViewport, asUnderAndUp, 3);
	asIn[0] = asUnderAndUp[2];
	asIn[1] = sData;
	DragOnCanvas(pcEditor, &cViewport, asIn, 2);

	pcClockOut = GetSimulatedPort(pcEditor, pcClock, "Output");
	pcClockIn = GetSimulatedPort(pcEditor, pcFlipFlop, "CP");
	pcInverted = GetSimulatedPort(pcEditor, pcFlipFlop, "QB");
	pcData = GetSimulatedPort(pcEditor, pcFlipFlop, "D");
	pcQ = GetSimulatedPort(pcEditor, pcFlipFlop, "Q");
	AssertNotNull(pcClockIn->GetTrace());
	AssertPointer(pcClockOut->GetTrace(), pcClockIn->GetTrace());
	AssertNotNull(pcData->GetTrace());
	AssertPointer(pcInverted->GetTrace(), pcData->GetTrace());
	AssertFalse(pcClockIn->GetTrace() == pcData->GetTrace());

	//Running again, sampled at a hundredth of the clock's period.
	iStep = iClockPeriod / 100;
	iTime = pcEditor->GetSimulation()->GetTime();
	sClockEdges.Init(pcClockOut, iTime);
	sQEdges.Init(pcQ, iTime);
	for (iTime = 0; iTime < iClockPeriod * 20; iTime += iStep)
	{
		RunOnCanvas(pcEditor, iStep);
		sClockEdges.Sample(pcEditor->GetSimulation()->GetTime());
		sQEdges.Sample(pcEditor->GetSimulation()->GetTime());
	}
	AssertTrue(sClockEdges.uiRises >= 19);
	AssertTrue(sQEdges.uiRises >= 9);
	AssertTrue(llabs(sClockEdges.GetPeriod() - iClockPeriod) <= iStep);
	AssertTrue(llabs(sQEdges.GetPeriod() - 2 * iClockPeriod) <= iStep);

	cViewport.Kill();
	sTest.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// The view saved as XML, for comparing.
//
//////////////////////////////////////////////////////////////////////////
static void SaveViewText(CComponentView* pcView, CChars* pszText)
{
	CXMLWriter	cWriter;

	cWriter.Init();
	pcView->SaveXML(&cWriter);
	pszText->Init(cWriter.GetText());
	cWriter.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// Every component in the libraries, and a subcircuit instance, made again
// from its own properties is the same component: it saves the same.
//
//////////////////////////////////////////////////////////////////////////
void TestCircuitEditorPropertiesRoundTrip(void)
{
	SEditorTest				sTest;
	CCircuitFonts			cFonts;
	CCircuitView*			pcMain;
	CComponentView*			pcView;
	CComponentView*			pcNew;
	CComponentProperties	cProperties;
	SComponentLibrary*		psLibrary;
	CChars					szBefore;
	CChars					szAfter;
	size					i;
	size					j;
	size					k;
	int32					x;

	sTest.Init(&cFonts);
	LoadTestCircuitFonts(&cFonts);
	AddEditorInverterSubcircuit(&sTest.cEditor, &cFonts);
	pcMain = sTest.cEditor.AddCircuit("Main");
	AssertTrue(sTest.cEditor.Simulate("Main"));

	x = 0;
	for (i = 0; i < NumComponentLibraries(); i++)
	{
		psLibrary = GetComponentLibrary(i);
		for (j = 0; j < psLibrary->uiNumEntries; j++)
		{
			sTest.PointAt(x, 0);
			AssertTrue(sTest.cEditor.StartPlaceComponent(psLibrary->asEntries[j].szXMLName));
			sTest.Click(x, 0);
			x += 60;
		}
	}
	sTest.PointAt(x, 0);
	AssertTrue(sTest.cEditor.StartPlaceSubcircuit("Inverter"));
	sTest.Click(x, 0);

	for (k = 0; k < pcMain->NumComponents(); k++)
	{
		pcView = pcMain->GetComponent(k);
		SaveViewText(pcView, &szBefore);
		cProperties.Init();
		sTest.cEditor.GetProperties(pcView, &cProperties);
		AssertTrue(cProperties.NumProperties() > 0);
		AssertString("name", cProperties.Get(StringCompare(pcView->GetXMLName(), "Subcircuit") == 0 ? 1 : 0)->szName.Text());
		pcNew = sTest.cEditor.SetProperties(pcView, &cProperties, pcView->GetRotation());
		AssertNotNull(pcNew);
		AssertPointer(pcNew, pcMain->GetComponent(k));
		if (pcNew->MakesComponent())
		{
			AssertNotNull(pcNew->GetComponent(sTest.cEditor.GetViewPath(), sTest.cEditor.GetSimulation()));
		}
		SaveViewText(pcNew, &szAfter);
		AssertString(szBefore.Text(), szAfter.Text());
		szAfter.Kill();
		szBefore.Kill();
		cProperties.Kill();
	}
	sTest.cEditor.GetSimulation()->RunToTime(1000000);

	KillTestCircuitFonts(&cFonts);
	sTest.Kill(true);
}


//////////////////////////////////////////////////////////////////////////
//
// A gate's properties are its name, then its family (a choice of the
// families) and power, then its own, labelled as Logicim labels its
// fields.  A pin's are split by dividers.
//
//////////////////////////////////////////////////////////////////////////
void TestCircuitEditorPropertiesListed(void)
{
	SEditorTest				sTest;
	CCircuitView*			pcMain;
	CComponentProperties	cProperties;
	SComponentProperty*		psProperty;
	CPinView*				pcPin;
	SInt32Vec2				sMinimum;
	SInt32Vec2				sMaximum;

	sTest.Init();
	pcMain = sTest.cEditor.AddCircuit("Main");
	AddTestInverter(pcMain, 0, 0);
	sMinimum.Init(-2, -1);
	sMaximum.Init(0, 1);
	pcPin = NewMalloc<CPinView>();
	pcPin->Init(10, 0, ROT_East, "In", "LVC", false, 1, RADIX_Binary, sMinimum, sMaximum);
	pcMain->Add(pcPin);
	AssertTrue(sTest.cEditor.Simulate("Main"));

	cProperties.Init();
	sTest.cEditor.GetProperties(pcMain->GetComponent(0), &cProperties);
	AssertSize(5, cProperties.NumProperties());
	psProperty = cProperties.Get((size)0);
	AssertString("name", psProperty->szName.Text());
	AssertString("Name", psProperty->szLabel.Text());
	AssertInt(CPT_Text, psProperty->eType);
	psProperty = cProperties.Get(1);
	AssertString("Family", psProperty->szLabel.Text());
	AssertInt(CPT_Choice, psProperty->eType);
	AssertString("LVC", psProperty->szValue.Text());
	AssertTrue(psProperty->aszChoices.NumElements() > 1);
	AssertTrue(psProperty->aszChoices.Contains("LVC"));
	psProperty = cProperties.Get(2);
	AssertString("Explicit power ports", psProperty->szLabel.Text());
	AssertInt(CPT_Boolean, psProperty->eType);
	AssertString("false", psProperty->szValue.Text());
	psProperty = cProperties.Get(3);
	AssertString("Input count", psProperty->szLabel.Text());
	AssertInt(CPT_Integer, psProperty->eType);
	AssertString("1", psProperty->szValue.Text());
	AssertString("Input width", cProperties.Get(4)->szLabel.Text());
	cProperties.Kill();

	cProperties.Init();
	sTest.cEditor.GetProperties(pcPin, &cProperties);
	AssertString("bitWidth", cProperties.Get(1)->szName.Text());
	AssertInt(CPT_Divider, cProperties.Get("instanceLocation")->eType);
	AssertString("Instance location", cProperties.Get("instanceLocation")->szLabel.Text());
	AssertString("Left", cProperties.Get("alignment")->szValue.Text());
	AssertString("Centre", cProperties.Get("anchour")->szValue.Text());
	AssertInt(CPT_Divider, cProperties.Get("instanceDisplay")->eType);
	AssertString("Binary", cProperties.Get("radix")->szValue.Text());
	cProperties.Kill();

	sTest.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// Editing a wired inverter's properties keeps it wired and selected: given
// a new name and a width out of range, which is clamped (and can't be
// wired), then its width back, it still drives its output, and the
// circuit's components and traces don't pile up; turned, it stays where
// it is.
//
//////////////////////////////////////////////////////////////////////////
void TestCircuitEditorPropertiesEdited(void)
{
	SEditorTest				sTest;
	CCircuitView*			pcMain;
	CInverterView*			pcInverter;
	CComponentView*			pcNew;
	CComponentProperties	cProperties;
	CCircuit*				pcCircuit;
	SFloat64Vec2			sCentre;
	size					uiIntegratedCircuits;
	size					uiTraces;
	SLogConfig				sLogConfig;

	sTest.Init();
	pcMain = sTest.cEditor.AddCircuit("Main");
	AddGroundAndOutput(pcMain);
	pcInverter = AddTestInverter(pcMain, -3, -2);
	AssertTrue(sTest.cEditor.Simulate("Main"));
	sTest.Run();
	AssertInt(TV_High, sTest.GetLevel(3, -2));
	pcCircuit = sTest.cEditor.GetSimulation()->GetCircuit();
	uiIntegratedCircuits = pcCircuit->NumIntegratedCircuits();
	uiTraces = pcCircuit->NumTraces();

	sCentre = GetCentre(pcInverter);
	sTest.Click(sCentre.x, sCentre.y);
	AssertPointer(pcInverter, sTest.cEditor.GetPropertiesComponent());
	cProperties.Init();
	sTest.cEditor.GetProperties(pcInverter, &cProperties);
	AssertTrue(cProperties.SetValue("name", "U1"));
	AssertTrue(cProperties.SetValue("inputWidth", "100"));
	gcLogger.GetConfig(&sLogConfig);
	gcLogger.SetSilent();
	pcNew = sTest.cEditor.SetProperties(pcInverter, &cProperties, ROT_East);
	gcLogger.SetConfig(&sLogConfig);
	cProperties.Kill();
	AssertNotNull(pcNew);
	AssertString("U1", pcNew->GetName());
	AssertInt(RADIX_MAX_BIT_WIDTH, ((CInverterView*)pcNew)->GetInputWidth());
	AssertTrue(sTest.cEditor.GetSelection()->Contains(pcNew));

	cProperties.Init();
	sTest.cEditor.GetProperties(pcNew, &cProperties);
	AssertTrue(cProperties.SetValue("inputWidth", "1"));
	pcNew = sTest.cEditor.SetProperties(pcNew, &cProperties, ROT_East);
	cProperties.Kill();
	sTest.Run();
	AssertInt(TV_High, sTest.GetLevel(3, -2));
	AssertSize(uiIntegratedCircuits, pcCircuit->NumIntegratedCircuits());
	AssertSize(uiTraces, pcCircuit->NumTraces());

	cProperties.Init();
	sTest.cEditor.GetProperties(pcNew, &cProperties);
	pcNew = sTest.cEditor.SetProperties(pcNew, &cProperties, ROT_South);
	cProperties.Kill();
	AssertInt(ROT_South, pcNew->GetRotation());
	AssertInt(-3, pcNew->GetPosition().x);
	AssertInt(-2, pcNew->GetPosition().y);

	sTest.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCircuitEditor(void)
{
	BeginTests();
	DataIOInit();
	DataMemoryInit();

	TestCircuitEditorSelection();
	TestCircuitEditorPortHover();
	TestCircuitEditorDrawClockDivider();
	TestCircuitEditorPlace();
	TestCircuitEditorMove();
	TestCircuitEditorMoveFromJunction();
	TestCircuitEditorMoveWire();
	TestCircuitEditorRotateAndDelete();
	TestCircuitEditorSaveLoad();
	TestCircuitEditorTraceLines();
	TestCircuitEditorPullWire();
	TestCircuitEditorRouteWire();
	TestCircuitEditorSubcircuit();
	TestCircuitEditorComponentLibraries();
	TestCircuitEditorPlaceEveryComponent();
	TestCircuitEditorPlaceUnits();
	TestCircuitEditorPropertiesRoundTrip();
	TestCircuitEditorPropertiesListed();
	TestCircuitEditorPropertiesEdited();

	DataMemoryKill();
	DataIOKill();
	TestStatistics();
}

