#include "BaseLib/ConstructorCall.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/DataMemory.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/Logger.h"
#include "StandardLib/Objects.h"
#include "MicroprocessorLib/CircuitSimulation.h"
#include "MicroprocessorLib/FamilyVoltageConfigurationStore.h"
#include "MicroprocessorLib/SubcircuitSimulation.h"
#include "MicroprocessorLib/Constant.h"
#include "MicroprocessorLib/Trace.h"
#include "MicroprocessorLib/Event.h"
#include "MicroprocessorLib/Timeline.h"
#include "MicroprocessorLib/LongTime.h"
#include "LogicimLib/ValueView.h"
#include "LogicimLib/BufferView.h"
#include "LogicimLib/SubcircuitInstanceView.h"
#include "LogicimLib/CircuitViews.h"
#include "LogicimLib/CircuitFile.h"
#include "TestLib/Assert.h"
#include "TestLogicimRender.h"


void LoadTestCircuitFonts(CCircuitFonts* pcFonts);
void KillTestCircuitFonts(CCircuitFonts* pcFonts);


//////////////////////////////////////////////////////////////////////////
//
// A project's circuits and a simulation to make them in.
//
//////////////////////////////////////////////////////////////////////////
struct SSubcircuitTest
{
	CFamilyVoltageConfigurationStore	cFamilies;
	CCircuitSimulation					cSimulation;
	CCircuitViews						cCircuits;

	void Init(void)
	{
		ObjectsInit();
		CEvent::ResetNextID();
		CTrace::ResetNextID();
		CViewPath::ResetNextID();
		cFamilies.Init();
		AssertTrue(cFamilies.Load("Input" _FS_ "PropagationTimes.csv"));
		cSimulation.Init("Subcircuits");
		cCircuits.Init();
	}

	//Rooted objects (fonts) leave the root changed; it isn't checked.
	void Kill(bool bRooted = false)
	{
		cCircuits.Kill();
		cSimulation.Kill();
		cFamilies.Kill();
		if (bRooted)
		{
			ObjectsFlush();
		}
		ObjectsKill(!bRooted);
	}
};


//////////////////////////////////////////////////////////////////////////
//
// A one bit pin, shown on its subcircuit's instances on the side given,
// in the middle.
//
//////////////////////////////////////////////////////////////////////////
static CPinView* AddTestPin(CCircuitView* pcCircuit, int32 x, int32 y, const char* szName, EPinAlignment eAlignment, EPinAnchour eAnchour)
{
	CPinView*		pcPin;
	SInt32Vec2		sMinimum;
	SInt32Vec2		sMaximum;

	sMinimum.Init(-2, -1);
	sMaximum.Init(0, 1);
	pcPin = NewMalloc<CPinView>();
	pcPin->Init(x, y, ROT_North, szName, "LVC", false, 1, RADIX_Binary, sMinimum, sMaximum);
	pcPin->SetSubcircuitAppearance(eAlignment, eAnchour, 0, false, false);
	pcCircuit->Add(pcPin);
	return pcPin;
}


//////////////////////////////////////////////////////////////////////////
//
// An "Inverter" subcircuit: its In pin through an inverter to its Out
// pin.
//
//////////////////////////////////////////////////////////////////////////
static CCircuitView* AddInverterSubcircuit(CCircuitViews* pcCircuits)
{
	CCircuitView*	pcCircuit;
	CInverterView*	pcInverter;

	pcCircuit = pcCircuits->Add("Inverter");
	AddTestPin(pcCircuit, -8, 3, "In", PA_Left, PAN_Centre);
	pcCircuit->AddTrace(-8, 3, -4, 3);
	pcInverter = NewMalloc<CInverterView>();
	pcInverter->Init(-3, 3, ROT_East, "", "LVC", false, 1, 1);
	pcCircuit->Add(pcInverter);
	pcCircuit->AddTrace(-1, 3, 3, 3);
	AddTestPin(pcCircuit, 3, 3, "Out", PA_Right, PAN_Centre);
	return pcCircuit;
}


//////////////////////////////////////////////////////////////////////////
//
// An instance facing North with a fixed layout, as if measured: for a
// subcircuit with one pin on the left and one on the right, its In port is
// three grid units down from it and its Out port three up.
//
//////////////////////////////////////////////////////////////////////////
static CSubcircuitInstanceView* AddTestInstance(CCircuitView* pcCircuit, int32 x, int32 y, const char* szName, CCircuitView* pcSubcircuit)
{
	CSubcircuitInstanceView*	pcInstance;
	SSubcircuitInstanceLayout	sLayout;

	sLayout.sBoxMinimum.Init(-2, -1);
	sLayout.sBoxMaximum.Init(2, 1);
	sLayout.fTypeY = 0;
	sLayout.fCommentY = 0;
	sLayout.fNameY = 0;
	pcInstance = NewMalloc<CSubcircuitInstanceView>();
	pcInstance->Init(x, y, ROT_North, szName, "", pcSubcircuit->GetTypeName(), &sLayout);
	AssertTrue(pcInstance->SetInstanceCircuitView(pcSubcircuit));
	pcCircuit->Add(pcInstance);
	return pcInstance;
}


//////////////////////////////////////////////////////////////////////////
//
// A one bit constant whose port is on the grid point.
//
//////////////////////////////////////////////////////////////////////////
static CConstantView* AddTestConstant(CCircuitView* pcCircuit, SInt32Vec2 sPosition)
{
	CConstantView*	pcConstant;
	SInt32Vec2		sMinimum;
	SInt32Vec2		sMaximum;

	sMinimum.Init(-2, -1);
	sMaximum.Init(0, 1);
	pcConstant = NewMalloc<CConstantView>();
	pcConstant->Init(sPosition.x, sPosition.y, ROT_South, "", "LVC", false, 1, RADIX_Binary, sMinimum, sMaximum);
	pcCircuit->Add(pcConstant);
	return pcConstant;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
static CProbeView* AddTestProbe(CCircuitView* pcCircuit, SInt32Vec2 sPosition)
{
	CProbeView*		pcProbe;
	SInt32Vec2		sMinimum;
	SInt32Vec2		sMaximum;

	sMinimum.Init(-2, -1);
	sMaximum.Init(0, 1);
	pcProbe = NewMalloc<CProbeView>();
	pcProbe->Init(sPosition.x, sPosition.y, ROT_North, "", "LVC", false, 1, RADIX_Binary, sMinimum, sMaximum);
	pcCircuit->Add(pcProbe);
	return pcProbe;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
static SInt32Vec2 GetPinPosition(CSubcircuitInstanceView* pcInstance, const char* szPinName)
{
	return pcInstance->GetPin(szPinName)->pcPortView->GetGridPosition();
}


//////////////////////////////////////////////////////////////////////////
//
// Sets the constant after the start, which resets it, and runs the
// simulation until it settles.
//
//////////////////////////////////////////////////////////////////////////
static void SetTestConstant(CConstantView* pcView, int64 iValue, CViewPath* pcViewPath, CCircuitSimulation* pcSimulation)
{
	CConstant*	pcConstant;

	pcConstant = (CConstant*)pcView->GetComponent(pcViewPath, pcSimulation);
	pcConstant->SetConstantValue(iValue);
	pcConstant->SimulationStarted(pcSimulation->GetTimeline());
	pcSimulation->GetTimeline()->Run();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
static void AssertProbe(const char* szExpected, CProbeView* pcProbe, CViewPath* pcViewPath, CCircuitSimulation* pcSimulation)
{
	CChars	sz;

	sz.Init();
	pcProbe->GetValueText(&sz, pcViewPath, pcSimulation);
	AssertString(szExpected, sz.Text());
	sz.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// An instance shows its subcircuit's pins as port views, one port per bit
// named for the pin, and a circuit can only be added once by type.
//
//////////////////////////////////////////////////////////////////////////
void TestSubcircuitInstancePins(void)
{
	SSubcircuitTest				sTest;
	CCircuitView*				pcInverter;
	CCircuitView*				pcTop;
	CSubcircuitInstanceView*	pcInstance;
	CChars						sz;
	SLogConfig					sLogConfig;

	sTest.Init();
	pcInverter = AddInverterSubcircuit(&sTest.cCircuits);
	pcTop = sTest.cCircuits.Add("Top");
	pcInstance = AddTestInstance(pcTop, 10, 20, "U1", pcInverter);

	gcLogger.GetConfig(&sLogConfig);
	gcLogger.SetSilent();
	AssertNull(sTest.cCircuits.Add("Top"));
	AssertNull(sTest.cCircuits.Add(""));
	gcLogger.SetConfig(&sLogConfig);
	AssertSize(2, sTest.cCircuits.NumCircuits());
	AssertTrue(sTest.cCircuits.Get("Inverter") == pcInverter);
	AssertNotNull(sTest.cCircuits.GetTopPath(pcTop));

	AssertString("Subcircuit", pcInstance->GetType());
	AssertString("Inverter", pcInstance->GetTypeName());
	AssertTrue(pcInstance->GetInstanceCircuitView() == pcInverter);
	AssertTrue(pcInstance->GetCircuitInstanceView() == pcInstance);
	AssertSize(2, pcInstance->NumPins());
	AssertSize(2, pcInstance->NumPortViews());
	AssertString("In 0", pcInstance->GetPin("In")->pcPortView->GetPortName(0));
	AssertString("Out 0", pcInstance->GetPin("Out")->pcPortView->GetPortName(0));
	AssertInt(10, GetPinPosition(pcInstance, "In").x);
	AssertInt(23, GetPinPosition(pcInstance, "In").y);
	AssertInt(10, GetPinPosition(pcInstance, "Out").x);
	AssertInt(17, GetPinPosition(pcInstance, "Out").y);
	AssertNull(pcInstance->GetPin("Nope"));

	sz.Init();
	pcInstance->AppendDescription(&sz);
	AssertString("Inverter (U1)", sz.Text());
	sz.Kill();

	sTest.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// A signal goes in through an instance's pin, through the subcircuit's
// inverter and out through its other pin, on one trace each side of each
// pin.
//
//////////////////////////////////////////////////////////////////////////
void TestSubcircuitSignalThrough(void)
{
	SSubcircuitTest				sTest;
	CCircuitView*				pcInverter;
	CCircuitView*				pcTop;
	CSubcircuitInstanceView*	pcInstance;
	CConstantView*				pcConstant;
	CProbeView*					pcProbe;
	CViewPath*					pcTopPath;
	CViewPath*					pcChild;
	CCircuitSimulation*			pcSimulation;
	CPinView*					pcIn;

	sTest.Init();
	pcSimulation = &sTest.cSimulation;
	pcInverter = AddInverterSubcircuit(&sTest.cCircuits);
	pcTop = sTest.cCircuits.Add("Top");
	pcInstance = AddTestInstance(pcTop, 0, 0, "U1", pcInverter);
	pcConstant = AddTestConstant(pcTop, GetPinPosition(pcInstance, "In"));
	pcProbe = AddTestProbe(pcTop, GetPinPosition(pcInstance, "Out"));
	pcTopPath = sTest.cCircuits.GetTopPath(pcTop);

	AssertTrue(pcTop->CreateSimulation(pcTopPath, pcSimulation, &sTest.cFamilies));
	pcChild = pcTopPath->FindChild(pcInstance);
	AssertNotNull(pcChild);
	AssertSize(2, pcChild->Length());
	AssertTrue(pcChild->GetPrevious() == pcTopPath);
	AssertTrue(pcChild->GetCircuitView() == pcInverter);
	AssertTrue(pcChild->GetSubcircuitSimulation(pcSimulation)->IsInstance());
	AssertTrue(pcChild->GetSubcircuitSimulation(pcSimulation) != pcTopPath->GetSubcircuitSimulation(pcSimulation));
	AssertString("Subcircuit instance", pcInstance->GetComponent(pcTopPath, pcSimulation)->GetType());

	//The instance's port for In, the pin inside and the inverter's input are on one trace.
	pcIn = pcInstance->GetPin("In")->pcPin;
	AssertNotNull(pcInstance->GetPin("In")->pcPortView->GetPort(pcTopPath, pcSimulation, 0)->GetTrace());
	AssertTrue(pcInstance->GetPin("In")->pcPortView->GetPort(pcTopPath, pcSimulation, 0)->GetTrace() == pcIn->GetPortView((size)0)->GetPort(pcChild, pcSimulation, 0)->GetTrace());
	AssertTrue(pcIn->GetPortView((size)0)->GetPort(pcChild, pcSimulation, 0)->GetTrace() == pcInverter->GetTrace(0)->GetTrace(pcChild, pcSimulation, 0));
	AssertNull(pcIn->GetComponent(pcTopPath, pcSimulation));

	SetTestConstant(pcConstant, 1, pcTopPath, pcSimulation);
	AssertProbe("0", pcProbe, pcTopPath, pcSimulation);
	SetTestConstant(pcConstant, 0, pcTopPath, pcSimulation);
	AssertProbe("1", pcProbe, pcTopPath, pcSimulation);

	pcTop->DisconnectSimulation(pcTopPath, pcSimulation);
	AssertFalse(pcTopPath->ContainsCircuitSimulation(pcSimulation));
	AssertFalse(pcChild->ContainsCircuitSimulation(pcSimulation));
	AssertSize(0, pcInstance->NumComponents());
	AssertSize(0, pcIn->NumComponents());

	sTest.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// Two instances of one subcircuit share its views, which make a component
// for each instance, and work apart.
//
//////////////////////////////////////////////////////////////////////////
void TestSubcircuitReused(void)
{
	SSubcircuitTest				sTest;
	CCircuitView*				pcInverter;
	CCircuitView*				pcTop;
	CSubcircuitInstanceView*	pcFirst;
	CSubcircuitInstanceView*	pcSecond;
	CConstantView*				pcFirstConstant;
	CConstantView*				pcSecondConstant;
	CProbeView*					pcFirstProbe;
	CProbeView*					pcSecondProbe;
	CViewPath*					pcTopPath;
	CCircuitSimulation*			pcSimulation;
	CComponentView*				pcInverterGate;

	sTest.Init();
	pcSimulation = &sTest.cSimulation;
	pcInverter = AddInverterSubcircuit(&sTest.cCircuits);
	pcTop = sTest.cCircuits.Add("Top");
	pcFirst = AddTestInstance(pcTop, 0, 0, "U1", pcInverter);
	pcSecond = AddTestInstance(pcTop, 10, 0, "U2", pcInverter);
	pcFirstConstant = AddTestConstant(pcTop, GetPinPosition(pcFirst, "In"));
	pcSecondConstant = AddTestConstant(pcTop, GetPinPosition(pcSecond, "In"));
	pcFirstProbe = AddTestProbe(pcTop, GetPinPosition(pcFirst, "Out"));
	pcSecondProbe = AddTestProbe(pcTop, GetPinPosition(pcSecond, "Out"));
	pcTopPath = sTest.cCircuits.GetTopPath(pcTop);

	AssertTrue(pcTop->CreateSimulation(pcTopPath, pcSimulation, &sTest.cFamilies));
	pcInverterGate = pcInverter->GetComponent(1);
	AssertSize(2, pcInverterGate->NumComponents());
	AssertTrue(pcInverterGate->GetComponent(pcTopPath->FindChild(pcFirst), pcSimulation) != pcInverterGate->GetComponent(pcTopPath->FindChild(pcSecond), pcSimulation));
	AssertTrue(pcTopPath->FindChild(pcFirst)->GetSubcircuitSimulation(pcSimulation) != pcTopPath->FindChild(pcSecond)->GetSubcircuitSimulation(pcSimulation));

	SetTestConstant(pcFirstConstant, 1, pcTopPath, pcSimulation);
	SetTestConstant(pcSecondConstant, 0, pcTopPath, pcSimulation);
	AssertProbe("0", pcFirstProbe, pcTopPath, pcSimulation);
	AssertProbe("1", pcSecondProbe, pcTopPath, pcSimulation);

	sTest.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// A "Double" subcircuit: two inverters in series, as two Inverter
// instances, so its Out is its In.
//
//////////////////////////////////////////////////////////////////////////
static CCircuitView* AddDoubleSubcircuit(CCircuitViews* pcCircuits, CCircuitView* pcInverter)
{
	CCircuitView*	pcCircuit;

	pcCircuit = pcCircuits->Add("Double");
	AddTestPin(pcCircuit, 0, 3, "In", PA_Left, PAN_Centre);
	AddTestInstance(pcCircuit, 0, 0, "I1", pcInverter);
	AddTestInstance(pcCircuit, 0, -6, "I2", pcInverter);
	AddTestPin(pcCircuit, 0, -9, "Out", PA_Right, PAN_Centre);
	return pcCircuit;
}


//////////////////////////////////////////////////////////////////////////
//
// Subcircuits in subcircuits: two Doubles each hold two Inverters, so the
// inverter is made four times, once for each path down to it.
//
//////////////////////////////////////////////////////////////////////////
void TestSubcircuitNested(void)
{
	SSubcircuitTest				sTest;
	CCircuitView*				pcInverter;
	CCircuitView*				pcDouble;
	CCircuitView*				pcTop;
	CSubcircuitInstanceView*	pcFirst;
	CSubcircuitInstanceView*	pcSecond;
	CConstantView*				pcFirstConstant;
	CConstantView*				pcSecondConstant;
	CProbeView*					pcFirstProbe;
	CProbeView*					pcSecondProbe;
	CViewPath*					pcTopPath;
	CViewPath*					pcDoublePath;
	CViewPath*					pcInverterPath;
	CCircuitSimulation*			pcSimulation;
	CChars						sz;

	sTest.Init();
	pcSimulation = &sTest.cSimulation;
	pcInverter = AddInverterSubcircuit(&sTest.cCircuits);
	pcDouble = AddDoubleSubcircuit(&sTest.cCircuits, pcInverter);
	pcTop = sTest.cCircuits.Add("Top");
	pcFirst = AddTestInstance(pcTop, 0, 0, "D1", pcDouble);
	pcSecond = AddTestInstance(pcTop, 10, 0, "D2", pcDouble);
	pcFirstConstant = AddTestConstant(pcTop, GetPinPosition(pcFirst, "In"));
	pcSecondConstant = AddTestConstant(pcTop, GetPinPosition(pcSecond, "In"));
	pcFirstProbe = AddTestProbe(pcTop, GetPinPosition(pcFirst, "Out"));
	pcSecondProbe = AddTestProbe(pcTop, GetPinPosition(pcSecond, "Out"));
	pcTopPath = sTest.cCircuits.GetTopPath(pcTop);

	AssertTrue(pcTop->CreateSimulation(pcTopPath, pcSimulation, &sTest.cFamilies));
	AssertSize(4, pcInverter->GetComponent(1)->NumComponents());
	AssertSize(2, pcDouble->GetComponent(1)->NumComponents());
	pcDoublePath = pcTopPath->FindChild(pcFirst);
	pcInverterPath = pcDoublePath->FindChild((CSubcircuitInstanceView*)pcDouble->GetComponent(2));
	AssertSize(3, pcInverterPath->Length());
	AssertTrue(pcInverterPath->GetPrevious() == pcDoublePath);
	sz.Init();
	pcInverterPath->AppendDescription(&sz);
	AssertString("Top -> Double (D1) -> Inverter (I2)", sz.Text());
	sz.Kill();

	SetTestConstant(pcFirstConstant, 1, pcTopPath, pcSimulation);
	SetTestConstant(pcSecondConstant, 0, pcTopPath, pcSimulation);
	AssertProbe("1", pcFirstProbe, pcTopPath, pcSimulation);
	AssertProbe("0", pcSecondProbe, pcTopPath, pcSimulation);
	SetTestConstant(pcFirstConstant, 0, pcTopPath, pcSimulation);
	AssertProbe("0", pcFirstProbe, pcTopPath, pcSimulation);

	pcTop->DisconnectSimulation(pcTopPath, pcSimulation);
	AssertSize(0, pcInverter->GetComponent(1)->NumComponents());
	AssertFalse(pcInverterPath->ContainsCircuitSimulation(pcSimulation));

	sTest.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// A circuit with subcircuits simulated twice at once.
//
//////////////////////////////////////////////////////////////////////////
void TestSubcircuitTwoSimulations(void)
{
	SSubcircuitTest				sTest;
	CCircuitSimulation			cSecond;
	CCircuitView*				pcInverter;
	CCircuitView*				pcTop;
	CSubcircuitInstanceView*	pcInstance;
	CConstantView*				pcConstant;
	CProbeView*					pcProbe;
	CViewPath*					pcTopPath;

	sTest.Init();
	cSecond.Init("Second");
	pcInverter = AddInverterSubcircuit(&sTest.cCircuits);
	pcTop = sTest.cCircuits.Add("Top");
	pcInstance = AddTestInstance(pcTop, 0, 0, "U1", pcInverter);
	pcConstant = AddTestConstant(pcTop, GetPinPosition(pcInstance, "In"));
	pcProbe = AddTestProbe(pcTop, GetPinPosition(pcInstance, "Out"));
	pcTopPath = sTest.cCircuits.GetTopPath(pcTop);

	AssertTrue(pcTop->CreateSimulation(pcTopPath, &sTest.cSimulation, &sTest.cFamilies));
	AssertTrue(pcTop->CreateSimulation(pcTopPath, &cSecond, &sTest.cFamilies));
	AssertSize(2, pcInverter->GetComponent(1)->NumComponents());
	AssertSize(2, pcTopPath->FindChild(pcInstance)->NumCircuitSimulations());

	SetTestConstant(pcConstant, 1, pcTopPath, &sTest.cSimulation);
	SetTestConstant(pcConstant, 0, pcTopPath, &cSecond);
	AssertProbe("0", pcProbe, pcTopPath, &sTest.cSimulation);
	AssertProbe("1", pcProbe, pcTopPath, &cSecond);

	pcTop->DisconnectSimulation(pcTopPath, &sTest.cSimulation);
	AssertSize(1, pcInverter->GetComponent(1)->NumComponents());
	AssertProbe("1", pcProbe, pcTopPath, &cSecond);

	cSecond.Kill();
	sTest.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// A "Pair" subcircuit holding Inverter three times: A through I1 to X,
// and B through I2 and then I3 to Y, so X is not A and Y is B.  I2's Out
// meets I3's In on a net inside the Pair.  Its components are A, I1, X,
// B, I2, I3 and Y.
//
//////////////////////////////////////////////////////////////////////////
static CCircuitView* AddPairSubcircuit(CCircuitViews* pcCircuits, CCircuitView* pcInverter)
{
	CCircuitView*	pcCircuit;

	pcCircuit = pcCircuits->Add("Pair");
	AddTestPin(pcCircuit, 0, 3, "A", PA_Left, PAN_Centre);
	AddTestInstance(pcCircuit, 0, 0, "I1", pcInverter);
	AddTestPin(pcCircuit, 0, -3, "X", PA_Right, PAN_Centre);
	AddTestPin(pcCircuit, 10, 3, "B", PA_Left, PAN_Centre);
	AddTestInstance(pcCircuit, 10, 0, "I2", pcInverter);
	AddTestInstance(pcCircuit, 10, -6, "I3", pcInverter);
	AddTestPin(pcCircuit, 10, -9, "Y", PA_Right, PAN_Centre);
	return pcCircuit;
}


//////////////////////////////////////////////////////////////////////////
//
// Pins on each of a Pair instance's ports, named for the Pair's pins and
// the suffix, in the order A, B, X, Y.
//
//////////////////////////////////////////////////////////////////////////
static void AddPairInstancePins(CCircuitView* pcCircuit, CSubcircuitInstanceView* pcPair, const char* szSuffix)
{
	const char*		aszPins[4] = { "A", "B", "X", "Y" };
	size			i;
	CChars			szName;
	SInt32Vec2		sPosition;

	for (i = 0; i < 4; i++)
	{
		szName.Init(aszPins[i]);
		szName.Append(szSuffix);
		sPosition = GetPinPosition(pcPair, aszPins[i]);
		AddTestPin(pcCircuit, sPosition.x, sPosition.y, szName.Text(), (i < 2) ? PA_Left : PA_Right, PAN_Centre);
		szName.Kill();
	}
}


//////////////////////////////////////////////////////////////////////////
//
// A "Quad" subcircuit holding Pair twice, P1 and P2, with their pins as
// its own: A1, B1, X1, Y1 and then A2, B2, X2, Y2 after the two Pairs.
//
//////////////////////////////////////////////////////////////////////////
static CCircuitView* AddQuadSubcircuit(CCircuitViews* pcCircuits, CCircuitView* pcPair)
{
	CCircuitView*				pcCircuit;
	CSubcircuitInstanceView*	pcFirst;
	CSubcircuitInstanceView*	pcSecond;

	pcCircuit = pcCircuits->Add("Quad");
	pcFirst = AddTestInstance(pcCircuit, 0, 0, "P1", pcPair);
	pcSecond = AddTestInstance(pcCircuit, 10, 0, "P2", pcPair);
	AddPairInstancePins(pcCircuit, pcFirst, "1");
	AddPairInstancePins(pcCircuit, pcSecond, "2");
	return pcCircuit;
}


//////////////////////////////////////////////////////////////////////////
//
// Top holding Quad twice (Q1 and Q2) and, with bTopPairs, Pair twice too
// (T1 and T2), with a constant on each of their inputs and a probe on
// each of their outputs.  Input i comes out on output i, inverted if i is
// even (an A going out on an X) and as it is if i is odd (a B going out
// on a Y).
//
//////////////////////////////////////////////////////////////////////////
#define REUSED_MAX_INPUTS	12


struct SReusedCircuit
{
	CCircuitView*				pcInverter;
	CCircuitView*				pcPair;
	CCircuitView*				pcQuad;
	CCircuitView*				pcTop;
	CSubcircuitInstanceView*	apcQuads[2];
	CSubcircuitInstanceView*	apcPairs[2];
	size						uiInputs;
	CConstantView*				apcInputs[REUSED_MAX_INPUTS];
	CProbeView*					apcOutputs[REUSED_MAX_INPUTS];
	CViewPath*					pcTopPath;

	void Init(CCircuitViews* pcCircuits, bool bTopPairs)
	{
		const char*		aszQuadInputs[4] = { "A1", "B1", "A2", "B2" };
		const char*		aszQuadOutputs[4] = { "X1", "Y1", "X2", "Y2" };
		const char*		aszPairInputs[2] = { "A", "B" };
		const char*		aszPairOutputs[2] = { "X", "Y" };
		size			i;

		pcInverter = AddInverterSubcircuit(pcCircuits);
		pcPair = AddPairSubcircuit(pcCircuits, pcInverter);
		pcQuad = AddQuadSubcircuit(pcCircuits, pcPair);
		pcTop = pcCircuits->Add("Top");
		apcQuads[0] = AddTestInstance(pcTop, 0, 0, "Q1", pcQuad);
		apcQuads[1] = AddTestInstance(pcTop, 20, 0, "Q2", pcQuad);
		uiInputs = 0;
		for (i = 0; i < 8; i++)
		{
			AddInput(apcQuads[i / 4], aszQuadInputs[i % 4], aszQuadOutputs[i % 4]);
		}
		apcPairs[0] = NULL;
		apcPairs[1] = NULL;
		if (bTopPairs)
		{
			apcPairs[0] = AddTestInstance(pcTop, 40, 0, "T1", pcPair);
			apcPairs[1] = AddTestInstance(pcTop, 50, 0, "T2", pcPair);
			for (i = 0; i < 4; i++)
			{
				AddInput(apcPairs[i / 2], aszPairInputs[i % 2], aszPairOutputs[i % 2]);
			}
		}
		pcTopPath = pcCircuits->GetTopPath(pcTop);
	}

	void AddInput(CSubcircuitInstanceView* pcInstance, const char* szInput, const char* szOutput)
	{
		apcInputs[uiInputs] = AddTestConstant(pcTop, GetPinPosition(pcInstance, szInput));
		apcOutputs[uiInputs] = AddTestProbe(pcTop, GetPinPosition(pcInstance, szOutput));
		uiInputs++;
	}

	//Sets bit i of uiBits on input i, without running the simulation.
	void SetInputs(uint32 uiBits, CCircuitSimulation* pcSimulation)
	{
		size		i;
		CConstant*	pcConstant;

		for (i = 0; i < uiInputs; i++)
		{
			pcConstant = (CConstant*)apcInputs[i]->GetComponent(pcTopPath, pcSimulation);
			pcConstant->SetConstantValue((uiBits >> i) & 1);
			pcConstant->SimulationStarted(pcSimulation->GetTimeline());
		}
	}

	//The X outputs (even i) are as uiXBits would make them and the Y outputs (odd i) as uiYBits would, so a
	//simulation part way through a change can be checked: an X is one inverter from its input and a Y two.
	void AssertOutputs(uint32 uiXBits, uint32 uiYBits, CCircuitSimulation* pcSimulation)
	{
		size		i;
		uint32		uiBit;

		for (i = 0; i < uiInputs; i++)
		{
			if ((i % 2) == 0)
			{
				uiBit = 1 - ((uiXBits >> i) & 1);
			}
			else
			{
				uiBit = (uiYBits >> i) & 1;
			}
			AssertProbe((uiBit == 1) ? "1" : "0", apcOutputs[i], pcTopPath, pcSimulation);
		}
	}

	void AssertOutputs(uint32 uiBits, CCircuitSimulation* pcSimulation)
	{
		AssertOutputs(uiBits, uiBits, pcSimulation);
	}

	void RunInputs(uint32 uiBits, CCircuitSimulation* pcSimulation)
	{
		SetInputs(uiBits, pcSimulation);
		pcSimulation->GetTimeline()->Run();
	}
};


//////////////////////////////////////////////////////////////////////////
//
// The traces of the Inverter's two wires on every path through an
// instance down to it in the simulation, each once.
//
//////////////////////////////////////////////////////////////////////////
static void CollectInverterTraces(CArrayTemplatePtr<CTrace>* papcTraces, CArrayViewPathPtr* papcInverterPaths, CCircuitView* pcInverter, CCircuitSimulation* pcSimulation)
{
	size		i;
	size		uiWire;
	CViewPath*	pcViewPath;
	CTrace*		pcTrace;

	for (i = 0; i < papcInverterPaths->NumElements(); i++)
	{
		pcViewPath = papcInverterPaths->GetPtr(i);
		if (!pcViewPath->IsTop())
		{
			AssertTrue(pcViewPath->ContainsCircuitSimulation(pcSimulation));
			for (uiWire = 0; uiWire < 2; uiWire++)
			{
				pcTrace = pcInverter->GetTrace(uiWire)->GetTrace(pcViewPath, pcSimulation, 0);
				AssertNotNull(pcTrace);
				if (papcTraces->Find(pcTrace) == ARRAY_ELEMENT_NOT_FOUND)
				{
					papcTraces->Add(pcTrace);
				}
			}
		}
	}
}


//////////////////////////////////////////////////////////////////////////
//
// The number of distinct traces on the Inverter's wires over all the
// paths down to it in each of the simulations given, added up as they're
// collected (pcSecond may be NULL).
//
//////////////////////////////////////////////////////////////////////////
static void AssertInverterTraces(size uiFirst, size uiBoth, CViewPaths* pcViewPaths, CCircuitView* pcInverter, CCircuitSimulation* pcFirst, CCircuitSimulation* pcSecond)
{
	CArrayViewPathPtr			apcInverterPaths;
	CArrayTemplatePtr<CTrace>	apcTraces;

	apcInverterPaths.Init();
	pcViewPaths->GetPathsEndingWith(pcInverter, &apcInverterPaths);
	apcTraces.Init();
	CollectInverterTraces(&apcTraces, &apcInverterPaths, pcInverter, pcFirst);
	AssertSize(uiFirst, apcTraces.NumElements());
	if (pcSecond != NULL)
	{
		CollectInverterTraces(&apcTraces, &apcInverterPaths, pcInverter, pcSecond);
		AssertSize(uiBoth, apcTraces.NumElements());
	}
	apcTraces.Kill();
	apcInverterPaths.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// How many paths end in the circuit, its own top path included.
//
//////////////////////////////////////////////////////////////////////////
static size NumPathsEndingWith(CViewPaths* pcViewPaths, CCircuitView* pcCircuit)
{
	CArrayViewPathPtr	apcPaths;
	size				uiNum;

	apcPaths.Init();
	pcViewPaths->GetPathsEndingWith(pcCircuit, &apcPaths);
	uiNum = apcPaths.NumElements();
	apcPaths.Kill();
	return uiNum;
}


//////////////////////////////////////////////////////////////////////////
//
// A subcircuit used more than once in a subcircuit that is itself used
// more than once, in two simulations at once.  Top holds Quad twice, each
// Quad holds Pair twice and each Pair holds Inverter three times, so the
// inverter is made twelve times in each simulation.  Each of the eight
// inputs into Top goes down through Quad and Pair into an Inverter and
// back out on its own trace, and the two simulations are given different
// inputs, so a trace or component shared by two paths, or by two
// simulations, shows as a wrong output.
//
//////////////////////////////////////////////////////////////////////////
void TestSubcircuitReusedInReused(void)
{
	SSubcircuitTest				sTest;
	CCircuitSimulation			cSecond;
	SReusedCircuit				sCircuit;
	CViewPaths*					pcViewPaths;
	CViewPath*					pcQuadPath;
	CViewPath*					pcPairPath;
	CViewPath*					pcSecondInverterPath;
	CViewPath*					pcThirdInverterPath;
	CTrace*						pcTrace;
	CCircuitView*				pcInverter;
	size						i;
	uint32						uiPattern;

	sTest.Init();
	cSecond.Init("Second");
	sCircuit.Init(&sTest.cCircuits, false);
	pcViewPaths = sTest.cCircuits.GetViewPaths();
	pcInverter = sCircuit.pcInverter;

	AssertTrue(sCircuit.pcTop->CreateSimulation(sCircuit.pcTopPath, &sTest.cSimulation, &sTest.cFamilies));
	AssertTrue(sCircuit.pcTop->CreateSimulation(sCircuit.pcTopPath, &cSecond, &sTest.cFamilies));

	//2 Quads x 2 Pairs x 3 Inverters in each of two simulations.
	AssertSize(24, pcInverter->GetComponent(1)->NumComponents());
	AssertSize(8, sCircuit.pcPair->GetComponent(1)->NumComponents());
	AssertSize(4, sCircuit.pcQuad->GetComponent(0)->NumComponents());
	AssertSize(13, NumPathsEndingWith(pcViewPaths, pcInverter));

	//Each Pair has five wires through its Inverters (I2's Out is I3's In), so twenty in each simulation, and none
	//shared between the simulations.
	AssertInverterTraces(20, 40, pcViewPaths, pcInverter, &sTest.cSimulation, &cSecond);

	//Q2's B2 is one trace from Top down through Quad and Pair to the wire inside I2.
	pcQuadPath = sCircuit.pcTopPath->FindChild(sCircuit.apcQuads[1]);
	pcPairPath = pcQuadPath->FindChild(sCircuit.pcQuad->GetComponent(1)->GetCircuitInstanceView());
	pcSecondInverterPath = pcPairPath->FindChild(sCircuit.pcPair->GetComponent(4)->GetCircuitInstanceView());
	pcThirdInverterPath = pcPairPath->FindChild(sCircuit.pcPair->GetComponent(5)->GetCircuitInstanceView());
	AssertSize(4, pcSecondInverterPath->Length());
	pcTrace = sCircuit.apcQuads[1]->GetPin("B2")->pcPortView->GetPort(sCircuit.pcTopPath, &sTest.cSimulation, 0)->GetTrace();
	AssertNotNull(pcTrace);
	AssertTrue(pcTrace == sCircuit.pcQuad->GetComponent(7)->GetPortView((size)0)->GetPort(pcQuadPath, &sTest.cSimulation, 0)->GetTrace());
	AssertTrue(pcTrace == sCircuit.pcPair->GetComponent(3)->GetPortView((size)0)->GetPort(pcPairPath, &sTest.cSimulation, 0)->GetTrace());
	AssertTrue(pcTrace == pcInverter->GetTrace(0)->GetTrace(pcSecondInverterPath, &sTest.cSimulation, 0));
	AssertTrue(pcTrace != pcInverter->GetTrace(0)->GetTrace(pcSecondInverterPath, &cSecond, 0));
	AssertTrue(pcInverter->GetTrace(1)->GetTrace(pcSecondInverterPath, &sTest.cSimulation, 0) == pcInverter->GetTrace(0)->GetTrace(pcThirdInverterPath, &sTest.cSimulation, 0));
	AssertTrue(pcInverter->GetTrace(1)->GetTrace(pcSecondInverterPath, &sTest.cSimulation, 0) != pcInverter->GetTrace(1)->GetTrace(pcThirdInverterPath, &sTest.cSimulation, 0));

	//Every pattern in the first simulation, with a different one in the second.
	for (uiPattern = 0; uiPattern < 256; uiPattern++)
	{
		sCircuit.RunInputs(uiPattern, &sTest.cSimulation);
		sCircuit.RunInputs((uiPattern * 37 + 11) & 0xFF, &cSecond);
		sCircuit.AssertOutputs(uiPattern, &sTest.cSimulation);
		sCircuit.AssertOutputs((uiPattern * 37 + 11) & 0xFF, &cSecond);
	}

	//Forgetting the first simulation leaves the second's twelve inverters running.
	sCircuit.pcTop->DisconnectSimulation(sCircuit.pcTopPath, &sTest.cSimulation);
	AssertSize(12, pcInverter->GetComponent(1)->NumComponents());
	for (i = 0; i < pcViewPaths->NumViewPaths(); i++)
	{
		AssertFalse(pcViewPaths->GetViewPath(i)->ContainsCircuitSimulation(&sTest.cSimulation));
	}
	sCircuit.RunInputs(0x5A, &cSecond);
	sCircuit.AssertOutputs(0x5A, &cSecond);
	sCircuit.RunInputs(0xA5, &cSecond);
	sCircuit.AssertOutputs(0xA5, &cSecond);

	cSecond.Kill();
	sTest.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// The same circuit with two Pairs on Top as well, so Pair is used at two
// depths: on Top itself and inside each Quad.  Its Inverters are made
// eighteen times in each simulation, on paths of three and four views.
//
//////////////////////////////////////////////////////////////////////////
void TestSubcircuitReusedAtTwoDepths(void)
{
	SSubcircuitTest				sTest;
	CCircuitSimulation			cSecond;
	SReusedCircuit				sCircuit;
	CViewPaths*					pcViewPaths;
	CViewPath*					pcPairPath;
	CViewPath*					pcQuadPairPath;
	CViewPath*					pcInverterPath;
	CTrace*						pcTrace;
	CCircuitView*				pcInverter;
	CComponentView*				pcFirstInverter;
	uint32						uiPattern;
	uint32						uiOther;

	sTest.Init();
	cSecond.Init("Second");
	sCircuit.Init(&sTest.cCircuits, true);
	pcViewPaths = sTest.cCircuits.GetViewPaths();
	pcInverter = sCircuit.pcInverter;
	AssertSize(12, sCircuit.uiInputs);

	AssertTrue(sCircuit.pcTop->CreateSimulation(sCircuit.pcTopPath, &sTest.cSimulation, &sTest.cFamilies));
	AssertTrue(sCircuit.pcTop->CreateSimulation(sCircuit.pcTopPath, &cSecond, &sTest.cFamilies));

	//(2 Quads x 2 Pairs + 2 Pairs) x 3 Inverters in each of two simulations.
	AssertSize(36, pcInverter->GetComponent(1)->NumComponents());
	AssertSize(12, sCircuit.pcPair->GetComponent(1)->NumComponents());
	AssertSize(19, NumPathsEndingWith(pcViewPaths, pcInverter));
	AssertSize(7, NumPathsEndingWith(pcViewPaths, sCircuit.pcPair));
	AssertInverterTraces(30, 60, pcViewPaths, pcInverter, &sTest.cSimulation, &cSecond);

	//T2's B is one trace from Top through the Pair to the wire inside its I2, a path of three views.
	pcPairPath = sCircuit.pcTopPath->FindChild(sCircuit.apcPairs[1]);
	AssertSize(2, pcPairPath->Length());
	pcInverterPath = pcPairPath->FindChild(sCircuit.pcPair->GetComponent(4)->GetCircuitInstanceView());
	AssertSize(3, pcInverterPath->Length());
	pcTrace = sCircuit.apcPairs[1]->GetPin("B")->pcPortView->GetPort(sCircuit.pcTopPath, &sTest.cSimulation, 0)->GetTrace();
	AssertNotNull(pcTrace);
	AssertTrue(pcTrace == sCircuit.pcPair->GetComponent(3)->GetPortView((size)0)->GetPort(pcPairPath, &sTest.cSimulation, 0)->GetTrace());
	AssertTrue(pcTrace == pcInverter->GetTrace(0)->GetTrace(pcInverterPath, &sTest.cSimulation, 0));

	//The Pair on Top and the Pairs in the Quads make their own inverters.
	pcQuadPairPath = sCircuit.pcTopPath->FindChild(sCircuit.apcQuads[0])->FindChild(sCircuit.pcQuad->GetComponent(0)->GetCircuitInstanceView());
	AssertSize(3, pcQuadPairPath->Length());
	pcFirstInverter = pcInverter->GetComponent(1);
	AssertTrue(pcFirstInverter->GetComponent(pcPairPath->FindChild(sCircuit.pcPair->GetComponent(1)->GetCircuitInstanceView()), &sTest.cSimulation) !=
			   pcFirstInverter->GetComponent(pcQuadPairPath->FindChild(sCircuit.pcPair->GetComponent(1)->GetCircuitInstanceView()), &sTest.cSimulation));

	//Twelve inputs: a spread of patterns in the first simulation, with others in the second.
	for (uiPattern = 0; uiPattern < 256; uiPattern++)
	{
		uiOther = (uiPattern * 0x9E5 + 0x123) & 0xFFF;
		sCircuit.RunInputs((uiPattern * 0x10F) & 0xFFF, &sTest.cSimulation);
		sCircuit.RunInputs(uiOther, &cSecond);
		sCircuit.AssertOutputs((uiPattern * 0x10F) & 0xFFF, &sTest.cSimulation);
		sCircuit.AssertOutputs(uiOther, &cSecond);
	}

	sCircuit.pcTop->DisconnectSimulation(sCircuit.pcTopPath, &cSecond);
	AssertSize(18, pcInverter->GetComponent(1)->NumComponents());
	sCircuit.RunInputs(0xF0F, &sTest.cSimulation);
	sCircuit.AssertOutputs(0xF0F, &sTest.cSimulation);

	cSecond.Kill();
	sTest.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// How long after a change on its inputs (rising or falling) the reused
// circuit's outputs change, in LVC: none has before 5.9 ns, the X outputs
// (one inverter) all have by 7.1 ns and the Y outputs (two inverters)
// none has before 9.1 ns, and all have by 10.8 ns.  Ticks to times well
// inside each of those.
//
//////////////////////////////////////////////////////////////////////////
#define REUSED_NO_OUTPUTS_NS	4.0
#define REUSED_X_OUTPUTS_NS		8.0
#define REUSED_ALL_OUTPUTS_NS	20.0


//////////////////////////////////////////////////////////////////////////
//
// Runs the simulation on by the nanoseconds, and checks it went that far
// and no further (none of these circuits has events of its own once its
// inputs settle).
//
//////////////////////////////////////////////////////////////////////////
static void TickSimulation(CCircuitSimulation* pcSimulation, float64 fNanoseconds, int64* piTime)
{
	pcSimulation->RunToTime(NanosecondsToTime(fNanoseconds));
	*piTime += NanosecondsToTime(fNanoseconds);
	AssertLong(*piTime, pcSimulation->GetTime());
}


//////////////////////////////////////////////////////////////////////////
//
// Each simulation is still at the time it was last ticked to.
//
//////////////////////////////////////////////////////////////////////////
static void AssertSimulationTimes(CCircuitSimulation* acSimulations, int64* aiTimes, size uiNum)
{
	size	i;

	for (i = 0; i < uiNum; i++)
	{
		AssertLong(aiTimes[i], acSimulations[i].GetTime());
	}
}


//////////////////////////////////////////////////////////////////////////
//
// Three simulations of the circuit with Pair at two depths, ticked apart:
// each is given new inputs and run on by a different amount in turn,
// some paused part way through a change, and after each tick every
// simulation is checked.  A simulation only moves when it's ticked, and
// one part way through a change (its X outputs changed and its Y outputs
// not yet) stays so while the others run.
//
//////////////////////////////////////////////////////////////////////////
void TestSubcircuitSimulationsTickedApart(void)
{
	SSubcircuitTest			sTest;
	SReusedCircuit			sCircuit;
	CCircuitSimulation		acSimulations[3];
	int64					aiTimes[3];
	const char*				aszNames[3] = { "One", "Two", "Three" };
	CCircuitSimulation*		pcOne;
	CCircuitSimulation*		pcTwo;
	CCircuitSimulation*		pcThree;
	size					i;

	sTest.Init();
	sCircuit.Init(&sTest.cCircuits, true);
	for (i = 0; i < 3; i++)
	{
		acSimulations[i].Init(aszNames[i]);
		AssertTrue(sCircuit.pcTop->CreateSimulation(sCircuit.pcTopPath, &acSimulations[i], &sTest.cFamilies));
		sCircuit.RunInputs(0, &acSimulations[i]);
		aiTimes[i] = acSimulations[i].GetTime();
	}
	pcOne = &acSimulations[0];
	pcTwo = &acSimulations[1];
	pcThree = &acSimulations[2];
	AssertSize(54, sCircuit.pcInverter->GetComponent(1)->NumComponents());

	//One is given new inputs and ticked a little: nothing has come out yet.
	sCircuit.SetInputs(0xFFF, pcOne);
	TickSimulation(pcOne, REUSED_NO_OUTPUTS_NS, &aiTimes[0]);
	sCircuit.AssertOutputs(0, pcOne);
	sCircuit.AssertOutputs(0, pcTwo);
	sCircuit.AssertOutputs(0, pcThree);
	AssertSimulationTimes(acSimulations, aiTimes, 3);

	//One is ticked a little more and paused part way: its Xs have changed and its Ys haven't.
	TickSimulation(pcOne, REUSED_X_OUTPUTS_NS - REUSED_NO_OUTPUTS_NS, &aiTimes[0]);
	sCircuit.AssertOutputs(0xFFF, 0, pcOne);
	sCircuit.AssertOutputs(0, pcTwo);
	AssertSimulationTimes(acSimulations, aiTimes, 3);

	//Two is given other inputs and ticked through; One stays part way and Three as it was.
	sCircuit.SetInputs(0xA5A, pcTwo);
	TickSimulation(pcTwo, REUSED_ALL_OUTPUTS_NS, &aiTimes[1]);
	sCircuit.AssertOutputs(0xA5A, pcTwo);
	sCircuit.AssertOutputs(0xFFF, 0, pcOne);
	sCircuit.AssertOutputs(0, pcThree);
	AssertSimulationTimes(acSimulations, aiTimes, 3);

	//One is ticked on and finishes its change.
	TickSimulation(pcOne, REUSED_ALL_OUTPUTS_NS - REUSED_X_OUTPUTS_NS, &aiTimes[0]);
	sCircuit.AssertOutputs(0xFFF, pcOne);
	sCircuit.AssertOutputs(0xA5A, pcTwo);
	sCircuit.AssertOutputs(0, pcThree);
	AssertSimulationTimes(acSimulations, aiTimes, 3);

	//Three is given inputs and paused part way.
	sCircuit.SetInputs(0x3C3, pcThree);
	TickSimulation(pcThree, REUSED_X_OUTPUTS_NS, &aiTimes[2]);
	sCircuit.AssertOutputs(0x3C3, 0, pcThree);
	sCircuit.AssertOutputs(0xA5A, pcTwo);
	sCircuit.AssertOutputs(0xFFF, pcOne);
	AssertSimulationTimes(acSimulations, aiTimes, 3);

	//Two changes again and is paused part way, from its last inputs; Three stays part way.
	sCircuit.SetInputs(0x5A5, pcTwo);
	TickSimulation(pcTwo, REUSED_X_OUTPUTS_NS, &aiTimes[1]);
	sCircuit.AssertOutputs(0x5A5, 0xA5A, pcTwo);
	sCircuit.AssertOutputs(0x3C3, 0, pcThree);
	sCircuit.AssertOutputs(0xFFF, pcOne);
	AssertSimulationTimes(acSimulations, aiTimes, 3);

	//One changes and is ticked a little, with the other two both part way.
	sCircuit.SetInputs(0x0F0, pcOne);
	TickSimulation(pcOne, REUSED_NO_OUTPUTS_NS, &aiTimes[0]);
	sCircuit.AssertOutputs(0xFFF, pcOne);
	sCircuit.AssertOutputs(0x5A5, 0xA5A, pcTwo);
	sCircuit.AssertOutputs(0x3C3, 0, pcThree);
	AssertSimulationTimes(acSimulations, aiTimes, 3);

	//Three, then Two, then One are ticked through, each checked as the others wait.
	TickSimulation(pcThree, REUSED_ALL_OUTPUTS_NS - REUSED_X_OUTPUTS_NS, &aiTimes[2]);
	sCircuit.AssertOutputs(0x3C3, pcThree);
	sCircuit.AssertOutputs(0x5A5, 0xA5A, pcTwo);
	sCircuit.AssertOutputs(0xFFF, pcOne);
	TickSimulation(pcTwo, REUSED_ALL_OUTPUTS_NS - REUSED_X_OUTPUTS_NS, &aiTimes[1]);
	sCircuit.AssertOutputs(0x5A5, pcTwo);
	sCircuit.AssertOutputs(0x3C3, pcThree);
	sCircuit.AssertOutputs(0xFFF, pcOne);
	TickSimulation(pcOne, REUSED_ALL_OUTPUTS_NS - REUSED_NO_OUTPUTS_NS, &aiTimes[0]);
	sCircuit.AssertOutputs(0x0F0, pcOne);
	sCircuit.AssertOutputs(0x5A5, pcTwo);
	sCircuit.AssertOutputs(0x3C3, pcThree);
	AssertSimulationTimes(acSimulations, aiTimes, 3);

	for (i = 0; i < 3; i++)
	{
		acSimulations[i].Kill();
	}
	sTest.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// A subcircuit can't be inside itself.
//
//////////////////////////////////////////////////////////////////////////
void TestSubcircuitInsideItself(void)
{
	SSubcircuitTest		sTest;
	CCircuitView*		pcLoop;
	SLogConfig			sLogConfig;

	sTest.Init();
	pcLoop = sTest.cCircuits.Add("Loop");
	AddTestPin(pcLoop, 0, 3, "In", PA_Left, PAN_Centre);
	AddTestPin(pcLoop, 0, -3, "Out", PA_Right, PAN_Centre);
	AddTestInstance(pcLoop, 10, 0, "Again", pcLoop);

	gcLogger.GetConfig(&sLogConfig);
	gcLogger.SetSilent();
	AssertFalse(pcLoop->CreateSimulation(sTest.cCircuits.GetTopPath(pcLoop), &sTest.cSimulation, &sTest.cFamilies));
	gcLogger.SetConfig(&sLogConfig);

	sTest.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// An instance of a subcircuit with two pins of one name can't be made;
// it isn't left in the circuit, and no instance simulation is left.
//
//////////////////////////////////////////////////////////////////////////
void TestSubcircuitDuplicatePinNames(void)
{
	SSubcircuitTest				sTest;
	CCircuitView*				pcTwin;
	CCircuitView*				pcTop;
	CSubcircuitInstanceView*	pcInstance;
	SLogConfig					sLogConfig;

	sTest.Init();
	pcTwin = sTest.cCircuits.Add("Twin");
	AddTestPin(pcTwin, 0, 3, "A", PA_Left, PAN_Centre);
	AddTestPin(pcTwin, 0, -3, "A", PA_Right, PAN_Centre);
	pcTop = sTest.cCircuits.Add("Top");
	pcInstance = AddTestInstance(pcTop, 10, 0, "U1", pcTwin);

	gcLogger.GetConfig(&sLogConfig);
	gcLogger.SetSilent();
	AssertFalse(pcTop->CreateSimulation(sTest.cCircuits.GetTopPath(pcTop), &sTest.cSimulation, &sTest.cFamilies));
	gcLogger.SetConfig(&sLogConfig);

	AssertSize(0, sTest.cSimulation.GetCircuit()->NumPassives());
	AssertSize(0, sTest.cSimulation.NumInstanceSimulations());
	AssertSize(0, pcInstance->NumComponents());

	sTest.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// A project with subcircuits, saved part way through its simulation and
// loaded into another, saves the same and runs on the same.
//
//////////////////////////////////////////////////////////////////////////
void TestSubcircuitFileRoundTrip(void)
{
	SSubcircuitTest				sTest;
	CCircuitViews				cLoaded;
	CCircuitSimulation			cLoadedSimulation;
	CCircuitView*				pcInverter;
	CCircuitView*				pcDouble;
	CCircuitView*				pcTop;
	CSubcircuitInstanceView*	pcInstance;
	CConstantView*				pcConstant;
	CXMLWriter					cSavedText;
	CXMLWriter					cLoadedText;
	CFileUtil					cFileUtil;
	CViewPath*					pcTopPath;
	CCircuitView*				pcLoadedTop;
	CChars						sz;

	sTest.Init();
	pcInverter = AddInverterSubcircuit(&sTest.cCircuits);
	pcDouble = AddDoubleSubcircuit(&sTest.cCircuits, pcInverter);
	pcTop = sTest.cCircuits.Add("Top");
	pcInstance = AddTestInstance(pcTop, 0, 0, "D1", pcDouble);
	pcConstant = AddTestConstant(pcTop, GetPinPosition(pcInstance, "In"));
	AddTestProbe(pcTop, GetPinPosition(pcInstance, "Out"));
	AddTestInstance(pcTop, 10, 0, "U1", pcInverter);
	pcTopPath = sTest.cCircuits.GetTopPath(pcTop);
	AssertTrue(pcTop->CreateSimulation(pcTopPath, &sTest.cSimulation, &sTest.cFamilies));
	SetTestConstant(pcConstant, 1, pcTopPath, &sTest.cSimulation);

	cFileUtil.MakeDir("Output");
	AssertTrue(SaveCircuitsFile(&sTest.cCircuits, pcTop, &sTest.cSimulation, "Output" _FS_ "Subcircuits.xml"));

	cLoaded.Init();
	cLoadedSimulation.Init("Subcircuits");
	AssertTrue(LoadCircuitsFile(&cLoaded, "Top", &cLoadedSimulation, &sTest.cFamilies, "Output" _FS_ "Subcircuits.xml"));
	AssertSize(3, cLoaded.NumCircuits());
	pcLoadedTop = cLoaded.Get("Top");
	AssertNotNull(pcLoadedTop);
	AssertTrue(((CSubcircuitInstanceView*)pcLoadedTop->GetComponent(0))->GetInstanceCircuitView() == cLoaded.Get("Double"));
	AssertLong(sTest.cSimulation.GetTime(), cLoadedSimulation.GetTime());

	cSavedText.Init();
	SaveCircuitsXML(&sTest.cCircuits, pcTop, &sTest.cSimulation, &cSavedText);
	cLoadedText.Init();
	SaveCircuitsXML(&cLoaded, pcLoadedTop, &cLoadedSimulation, &cLoadedText);
	AssertString(cSavedText.GetText(), cLoadedText.GetText());
	AssertTrue(strstr(cSavedText.GetText(), "<Subcircuit ") != NULL);
	AssertTrue(strstr(cSavedText.GetText(), "<Instance index=\"0\">") != NULL);
	AssertTrue(strstr(cSavedText.GetText(), "circuit=\"Top\"") != NULL);
	cLoadedText.Kill();
	cSavedText.Kill();

	sz.Init();
	((CProbeView*)pcLoadedTop->GetComponent(2))->GetValueText(&sz, cLoaded.GetTopPath(pcLoadedTop), &cLoadedSimulation);
	AssertString("1", sz.Text());
	sz.Kill();

	cLoaded.Kill();
	cLoadedSimulation.Kill();
	sTest.Kill();

	cFileUtil.Delete("Output" _FS_ "Subcircuits.xml");
	cFileUtil.RemoveDir("Output");
}


//////////////////////////////////////////////////////////////////////////
//
// A "Chip" with pins on every side, grouped and turned as Logicim shows
// them: inverting, clocked, anchoured at either end and weighted.
//
//////////////////////////////////////////////////////////////////////////
static CCircuitView* AddChipSubcircuit(CCircuitViews* pcCircuits)
{
	CCircuitView*	pcCircuit;
	CPinView*		pcPin;

	pcCircuit = pcCircuits->Add("Chip");
	AddTestPin(pcCircuit, 0, 0, "A", PA_Left, PAN_Negative);
	pcPin = AddTestPin(pcCircuit, 4, 0, "B", PA_Left, PAN_Negative);
	pcPin->SetSubcircuitAppearance(PA_Left, PAN_Negative, 1, false, false);
	AddTestPin(pcCircuit, 8, 0, "Reset", PA_Left, PAN_Positive);
	pcPin = AddTestPin(pcCircuit, 12, 0, "Y", PA_Right, PAN_Centre);
	pcPin->SetSubcircuitAppearance(PA_Right, PAN_Centre, 0, true, false);
	AddTestPin(pcCircuit, 16, 0, "Z", PA_Right, PAN_Centre);
	pcPin = AddTestPin(pcCircuit, 20, 0, "Clock", PA_Top, PAN_Centre);
	pcPin->SetSubcircuitAppearance(PA_Top, PAN_Centre, 0, false, true);
	AddTestPin(pcCircuit, 24, 0, "Enable", PA_Bottom, PAN_Centre);
	AddTestPin(pcCircuit, 28, 0, "Hidden", PA_NotShown, PAN_Centre);
	return pcCircuit;
}


//////////////////////////////////////////////////////////////////////////
//
// Instances measured with fonts, as Logicim lays them out, drawn while
// running.  A loaded instance keeps the layout it was saved with.
//
//////////////////////////////////////////////////////////////////////////
void TestSubcircuitLayoutRender(void)
{
	SSubcircuitTest				sTest;
	CCircuitFonts				cFonts;
	CCircuitColours				cColours;
	CCircuitView*				pcInverter;
	CCircuitView*				pcChip;
	CCircuitView*				pcTop;
	CSubcircuitInstanceView*	pcInstance;
	CSubcircuitInstanceView*	pcChipInstance;
	CSubcircuitInstanceView*	pcLoaded;
	CConstantView*				pcConstant;
	CViewPath*					pcTopPath;

	sTest.Init();
	LoadTestCircuitFonts(&cFonts);
	cColours.InitLogicim();
	pcInverter = AddInverterSubcircuit(&sTest.cCircuits);
	pcChip = AddChipSubcircuit(&sTest.cCircuits);
	pcTop = sTest.cCircuits.Add("Top");

	pcInstance = NewMalloc<CSubcircuitInstanceView>();
	pcInstance->Init(-9, 0, ROT_East, "U1", "Not", pcInverter, &cFonts);
	pcTop->Add(pcInstance);
	pcChipInstance = NewMalloc<CSubcircuitInstanceView>();
	pcChipInstance->Init(10, 0, ROT_East, "", "", pcChip, &cFonts);
	pcTop->Add(pcChipInstance);
	pcConstant = AddTestConstant(pcTop, GetPinPosition(pcInstance, "In"));
	AddTestProbe(pcTop, GetPinPosition(pcInstance, "Out"));

	AssertSize(7, pcChipInstance->NumPins());
	AssertNull(pcChipInstance->GetPin("Hidden"));
	AssertTrue(pcChipInstance->GetPin("Y")->pcPin->IsInverting());

	pcTopPath = sTest.cCircuits.GetTopPath(pcTop);
	AssertTrue(pcTop->CreateSimulation(pcTopPath, &sTest.cSimulation, &sTest.cFamilies));
	SetTestConstant(pcConstant, 1, pcTopPath, &sTest.cSimulation);

	AssertRenderedCircuit(pcTop, &cColours, 840, 360, 2, pcTopPath, &sTest.cSimulation, true, "Subcircuits", &cFonts);

	//An instance given the kept layout, as one loaded, puts its pins where they were measured.
	pcLoaded = NewMalloc<CSubcircuitInstanceView>();
	pcLoaded->Init(10, 0, ROT_East, "", "", "Chip", pcChipInstance->GetLayout());
	AssertTrue(pcLoaded->SetInstanceCircuitView(pcChip));
	AssertSize(pcChipInstance->NumPins(), pcLoaded->NumPins());
	AssertInt(GetPinPosition(pcChipInstance, "Clock").x, GetPinPosition(pcLoaded, "Clock").x);
	AssertInt(GetPinPosition(pcChipInstance, "Clock").y, GetPinPosition(pcLoaded, "Clock").y);
	AssertInt(GetPinPosition(pcChipInstance, "Reset").x, GetPinPosition(pcLoaded, "Reset").x);
	AssertInt(GetPinPosition(pcChipInstance, "Reset").y, GetPinPosition(pcLoaded, "Reset").y);
	SafeKill(pcLoaded);

	cColours.Kill();
	KillTestCircuitFonts(&cFonts);
	sTest.Kill(true);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSubcircuits(void)
{
	BeginTests();
	DataIOInit();
	DataMemoryInit();

	TestSubcircuitInstancePins();
	TestSubcircuitSignalThrough();
	TestSubcircuitReused();
	TestSubcircuitNested();
	TestSubcircuitTwoSimulations();
	TestSubcircuitReusedInReused();
	TestSubcircuitReusedAtTwoDepths();
	TestSubcircuitSimulationsTickedApart();
	TestSubcircuitInsideItself();
	TestSubcircuitDuplicatePinNames();
	TestSubcircuitFileRoundTrip();
	TestSubcircuitLayoutRender();

	DataMemoryKill();
	DataIOKill();
	TestStatistics();
}

