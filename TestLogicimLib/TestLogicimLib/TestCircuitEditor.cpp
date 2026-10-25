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
#include "LogicimLib/BufferView.h"
#include "LogicimLib/PowerSourceView.h"
#include "LogicimLib/ValueView.h"
#include "LogicimLib/SubcircuitInstanceView.h"
#include "LogicimLib/CircuitEditor.h"
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

	int GetLevel(CTraceView* pcTrace)
	{
		return GetEditorLevel(&cEditor, &cFamilies, pcTrace);
	}

	//The wire's level in the editor's simulation, TV_Unsettled when nothing drives it.
	static int GetEditorLevel(CCircuitEditor* pcEditor, CFamilyVoltageConfigurationStore* pcFamilies, CTraceView* pcTrace)
	{
		CFamilyVoltageConfiguration*	pcFamily;
		CTrace*							pcSimulated;
		float32							fVoltage;

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
static CTraceView* AddGroundAndOutput(CCircuitView* pcCircuit)
{
	CGroundView*	pcGround;

	pcGround = NewMalloc<CGroundView>();
	pcGround->Init(-8, -3, ROT_North, "");
	pcCircuit->Add(pcGround);
	pcCircuit->AddTraces(-8, -3, -4, -2);
	return pcCircuit->AddTrace(-1, -2, 6, -2);
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
	CTraceView*			pcOut;
	CComponentView*		pcPlaced;

	sTest.Init();
	pcMain = sTest.cEditor.AddCircuit("Main");
	pcOut = AddGroundAndOutput(pcMain);
	AssertTrue(sTest.cEditor.Simulate("Main"));
	sTest.Run();
	AssertInt(TV_Unsettled, sTest.GetLevel(pcOut));

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
	AssertInt(TV_High, sTest.GetLevel(pcOut));

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
// Dragging a selected inverter off its wires disconnects it and dragging
// it back connects it again.  It keeps the same component throughout (the
// simulation isn't remade) and the circuit's traces don't pile up.
//
//////////////////////////////////////////////////////////////////////////
void TestCircuitEditorMove(void)
{
	SEditorTest			sTest;
	CCircuitView*		pcMain;
	CTraceView*			pcOut;
	CInverterView*		pcInverter;
	CCircuitComponent*	pcComponent;
	SFloat64Vec2		sCentre;
	size				uiTraces;

	sTest.Init();
	pcMain = sTest.cEditor.AddCircuit("Main");
	pcOut = AddGroundAndOutput(pcMain);
	pcInverter = AddTestInverter(pcMain, -3, -2);
	AssertTrue(sTest.cEditor.Simulate("Main"));
	sTest.Run();
	AssertInt(TV_High, sTest.GetLevel(pcOut));
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
	AssertInt(TV_Unsettled, sTest.GetLevel(pcOut));
	AssertPointer(pcComponent, pcInverter->GetComponent(sTest.cEditor.GetViewPath(), sTest.cEditor.GetSimulation()));

	sTest.Drag(sCentre.x, sCentre.y + 10, sCentre.x, sCentre.y);
	AssertInt(-2, pcInverter->GetPosition().y);
	sTest.Run();
	AssertInt(TV_High, sTest.GetLevel(pcOut));
	AssertPointer(pcComponent, pcInverter->GetComponent(sTest.cEditor.GetViewPath(), sTest.cEditor.GetSimulation()));
	AssertSize(uiTraces, sTest.cEditor.GetSimulation()->GetCircuit()->NumTraces());

	sTest.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// Turning the inverter under the pointer turns it about the pointer and
// turns later placements too.  Deleting it takes its component out of the
// simulation and leaves the output undriven; deleting a selected wire
// takes it out of the circuit.
//
//////////////////////////////////////////////////////////////////////////
void TestCircuitEditorRotateAndDelete(void)
{
	SEditorTest			sTest;
	CCircuitView*		pcMain;
	CTraceView*			pcOut;
	CInverterView*		pcInverter;
	CCircuit*			pcCircuit;
	size				uiIntegratedCircuits;

	sTest.Init();
	pcMain = sTest.cEditor.AddCircuit("Main");
	pcOut = AddGroundAndOutput(pcMain);
	pcInverter = AddTestInverter(pcMain, -3, -2);
	AssertTrue(sTest.cEditor.Simulate("Main"));
	sTest.Run();
	pcCircuit = sTest.cEditor.GetSimulation()->GetCircuit();
	uiIntegratedCircuits = pcCircuit->NumIntegratedCircuits();

	sTest.PointAt(-1, -2);
	AssertPointer(pcInverter, sTest.cEditor.GetHover());
	sTest.cEditor.RotateRight();
	AssertInt(ROT_South, pcInverter->GetRotation());
	AssertInt(-1, pcInverter->GetPosition().x);
	AssertInt(-4, pcInverter->GetPosition().y);
	AssertInt(ROT_South, sTest.cEditor.GetCreationRotation());
	sTest.Run();
	AssertInt(TV_Unsettled, sTest.GetLevel(pcOut));

	sTest.cEditor.RotateLeft();
	AssertInt(ROT_East, pcInverter->GetRotation());
	AssertInt(-3, pcInverter->GetPosition().x);
	AssertInt(-2, pcInverter->GetPosition().y);
	AssertInt(ROT_East, sTest.cEditor.GetCreationRotation());
	sTest.Run();
	AssertInt(TV_High, sTest.GetLevel(pcOut));

	sTest.PointAt(-2, -2);
	AssertPointer(pcInverter, sTest.cEditor.GetHover());
	AssertTrue(sTest.cEditor.Delete());
	AssertSize(1, pcMain->NumComponents());
	AssertSize(uiIntegratedCircuits - 1, pcCircuit->NumIntegratedCircuits());
	AssertNull(sTest.cEditor.GetHover());
	sTest.Run();
	AssertInt(TV_Unsettled, sTest.GetLevel(pcOut));

	AssertSize(3, pcMain->NumTraces());
	sTest.Click(3, -2);
	AssertPointer(pcOut, sTest.cEditor.GetSelection()->GetTrace(0));
	AssertTrue(sTest.cEditor.Delete());
	AssertSize(2, pcMain->NumTraces());
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
	CTraceView*		pcOut;
	CFileUtil		cFileUtil;
	CXMLWriter		cSavedText;
	CXMLWriter		cLoadedText;
	SLogConfig		sLogConfig;

	sSaved.Init();
	pcMain = sSaved.cEditor.AddCircuit("Main");
	sSaved.cEditor.AddCircuit("Other");
	pcOut = AddGroundAndOutput(pcMain);
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
	AssertInt(TV_High, sSaved.GetLevel(pcOut));
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
	AssertInt(TV_High, SEditorTest::GetEditorLevel(&cLoaded, &sSaved.cFamilies, cLoaded.GetCircuit()->GetTrace(2)));
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
void TestCircuitEditor(void)
{
	BeginTests();
	DataIOInit();
	DataMemoryInit();

	TestCircuitEditorSelection();
	TestCircuitEditorPlace();
	TestCircuitEditorMove();
	TestCircuitEditorRotateAndDelete();
	TestCircuitEditorSaveLoad();
	TestCircuitEditorSubcircuit();

	DataMemoryKill();
	DataIOKill();
	TestStatistics();
}

