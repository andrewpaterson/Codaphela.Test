#include "BaseLib/ConstructorCall.h"
#include "BaseLib/PointerFunctions.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/DataMemory.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/TextFile.h"
#include "BaseLib/XMLFile.h"
#include "StandardLib/Objects.h"
#include "MicroprocessorLib/CircuitSimulation.h"
#include "MicroprocessorLib/FamilyVoltageConfigurationStore.h"
#include "MicroprocessorLib/Timeline.h"
#include "MicroprocessorLib/Trace.h"
#include "MicroprocessorLib/Event.h"
#include "MicroprocessorLib/LongTime.h"
#include "MicroprocessorLib/Voltage.h"
#include "MicroprocessorLib/PowerSource.h"
#include "MicroprocessorLib/PowerOutPort.h"
#include "MicroprocessorLib/LogicPort.h"
#include "MicroprocessorLib/IntegratedCircuit.h"
#include "MicroprocessorLib/ClockOscillator.h"
#include "MicroprocessorLib/Constant.h"
#include "MicroprocessorLib/Counter.h"
#include "MicroprocessorLib/DTypeFlipFlop.h"
#include "MicroprocessorLib/Oscilloscope.h"
#include "MicroprocessorLib/AndGate.h"
#include "LogicimLib/AndGateView.h"
#include "LogicimLib/BufferView.h"
#include "LogicimLib/CircuitFile.h"
#include "LogicimLib/StateXML.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
// A NAND enabled by the trace of the first wire and two inverters in a
// ring, then a buffer.
//
//////////////////////////////////////////////////////////////////////////
void AddRingOscillatorViews(CCircuitView* pcCircuit)
{
	CNandGateView*	pcNand;
	CInverterView*	pcInverter;
	CBufferView*	pcBuffer;

	pcNand = NewMalloc<CNandGateView>();
	pcNand->Init(-17, 0, ROT_West, "U1", "LVC", false, 2, 1);
	pcCircuit->Add(pcNand);
	pcInverter = NewMalloc<CInverterView>();
	pcInverter->Init(-11, 0, ROT_West, "U2", "LVC", false, 1, 1);
	pcCircuit->Add(pcInverter);
	pcInverter = NewMalloc<CInverterView>();
	pcInverter->Init(-6, 0, ROT_West, "U3", "LVC", false, 1, 1);
	pcCircuit->Add(pcInverter);
	pcBuffer = NewMalloc<CBufferView>();
	pcBuffer->Init(2, 0, ROT_West, "U4", "LVC", false, 1, 1);
	pcCircuit->Add(pcBuffer);
	pcCircuit->AddTrace(-25, -1, -18, -1);
	pcCircuit->AddTrace(-14, 0, -12, 0);
	pcCircuit->AddTrace(-9, 0, -7, 0);
	pcCircuit->AddTrace(-4, 0, 1, 0);
	pcCircuit->AddTrace(-1, 0, -1, 4);
	pcCircuit->AddTrace(-1, 4, -20, 4);
	pcCircuit->AddTrace(-20, 4, -20, 1);
	pcCircuit->AddTrace(-20, 1, -18, 1);
	pcCircuit->AddTrace(3, 0, 9, 0);
}


//////////////////////////////////////////////////////////////////////////
//
// A supply on the enable wire.  Supplies keep no state, so the one in a
// loaded simulation is wired on quietly, as if it had always been there.
//
//////////////////////////////////////////////////////////////////////////
CPowerSource* AddRingEnable(CCircuitSimulation* pcSimulation, CCircuitView* pcCircuit, float32 fVoltage, bool bLive)
{
	CPowerSource*	pcSupply;

	pcSupply = NewMalloc<CPowerSource>();
	pcSupply->Init(pcSimulation->GetSubcircuitTopSimulation(), "Enable", fVoltage);
	if (bLive)
	{
		AssertTrue(pcSupply->GetPowerOutPort()->ConnectLive(pcCircuit->GetTrace(0)->GetTrace(0), pcSimulation->GetTimeline()));
	}
	else
	{
		AssertTrue(pcSupply->GetPowerOutPort()->Connect(pcCircuit->GetTrace(0)->GetTrace(0)));
	}
	return pcSupply;
}


//////////////////////////////////////////////////////////////////////////
//
// Saved part way through oscillating and loaded into another simulation,
// the ring saves the same and then runs on exactly as the original.
//
//////////////////////////////////////////////////////////////////////////
void TestSimulationStateRingRoundTrip(void)
{
	CFamilyVoltageConfigurationStore	cFamilies;
	float32								fVcc;
	CCircuitSimulation					cOriginal;
	CCircuitSimulation					cLoaded;
	CCircuitView						cOriginalView;
	CCircuitView						cLoadedView;
	CPowerSource*						pcLow;
	CXMLWriter							cOriginalText;
	CXMLWriter							cLoadedText;
	CFileUtil							cFileUtil;
	int									iStep;
	size								i;
	float32								fOriginal;
	float32								fLoaded;
	bool								bSame;
	int									iTransitions;
	float32								fLastNandVoltage;

	ObjectsInit();
	CEvent::ResetNextID();
	CTrace::ResetNextID();
	cFamilies.Init();
	AssertTrue(cFamilies.Load("Input" _FS_ "PropagationTimes.csv"));
	fVcc = cFamilies.Get("LVC")->GetDefaultVoltageConfiguration(DEFAULT_LOGIC_LEVEL)->GetVcc();

	cOriginal.Init("Ring");
	cOriginalView.Init();
	AddRingOscillatorViews(&cOriginalView);
	AssertTrue(cOriginalView.CreateSimulation(&cOriginal, &cFamilies));
	pcLow = AddRingEnable(&cOriginal, &cOriginalView, 0.0f, true);
	cOriginal.GetTimeline()->Run();
	pcLow->GetPowerOutPort()->Disconnect(cOriginal.GetTimeline());
	AddRingEnable(&cOriginal, &cOriginalView, fVcc, true);
	cOriginal.RunToTime(NanosecondsToTime((int64)37));
	AssertTrue(cOriginal.GetTimeline()->NumSimultaneousEvents() > 0);

	cFileUtil.MakeDir("Output");
	AssertTrue(SaveCircuitFile(&cOriginalView, &cOriginal, "Output" _FS_ "Ring.xml"));

	cLoaded.Init("Ring");
	cLoadedView.Init();
	AssertTrue(LoadCircuitFile(&cLoadedView, &cLoaded, &cFamilies, "Output" _FS_ "Ring.xml"));
	AddRingEnable(&cLoaded, &cLoadedView, fVcc, false);
	AssertLong(cOriginal.GetTime(), cLoaded.GetTime());
	AssertSize(cOriginal.GetTimeline()->NumSimultaneousEvents(), cLoaded.GetTimeline()->NumSimultaneousEvents());

	cOriginalText.Init();
	SaveCircuitXML(&cOriginalView, &cOriginal, &cOriginalText);
	cLoadedText.Init();
	SaveCircuitXML(&cLoadedView, &cLoaded, &cLoadedText);
	AssertString(cOriginalText.GetText(), cLoadedText.GetText());
	cLoadedText.Kill();
	cOriginalText.Kill();

	bSame = true;
	iTransitions = 0;
	fLastNandVoltage = cOriginalView.GetTrace(1)->GetTrace(0)->GetVoltage(cOriginal.GetTime());
	for (iStep = 0; (iStep < 300) && bSame; iStep++)
	{
		cOriginal.RunToTime(NanosecondsToTime((int64)1));
		cLoaded.RunToTime(NanosecondsToTime((int64)1));
		bSame = cOriginal.GetTime() == cLoaded.GetTime();
		for (i = 0; (i < cOriginalView.NumTraces()) && bSame; i++)
		{
			fOriginal = cOriginalView.GetTrace(i)->GetTrace(0)->GetVoltage(cOriginal.GetTime());
			fLoaded = cLoadedView.GetTrace(i)->GetTrace(0)->GetVoltage(cLoaded.GetTime());
			bSame = (fOriginal == fLoaded) || (!IsVoltage(fOriginal) && !IsVoltage(fLoaded));
		}
		fOriginal = cOriginalView.GetTrace(1)->GetTrace(0)->GetVoltage(cOriginal.GetTime());
		if ((fOriginal > fVcc / 2) != (fLastNandVoltage > fVcc / 2))
		{
			iTransitions++;
		}
		fLastNandVoltage = fOriginal;
	}
	AssertTrue(bSame);
	AssertInt(300, iStep);
	AssertTrue(iTransitions >= 4);

	cLoadedView.Kill();
	cLoaded.Kill();
	cOriginalView.Kill();
	cOriginal.Kill();
	cFamilies.Kill();
	ObjectsKill();

	cFileUtil.Delete("Output" _FS_ "Ring.xml");
	cFileUtil.RemoveDir("Output");
}


//////////////////////////////////////////////////////////////////////////
//
// A file without a simulation starts one afresh.
//
//////////////////////////////////////////////////////////////////////////
void TestSimulationStateFreshStart(void)
{
	CFamilyVoltageConfigurationStore	cFamilies;
	CFamilyVoltageConfiguration*		pcFamily;
	CCircuitSimulation					cSimulation;
	CCircuitView						cCircuit;
	float32								fVcc;

	ObjectsInit();
	CEvent::ResetNextID();
	CTrace::ResetNextID();
	cFamilies.Init();
	AssertTrue(cFamilies.Load("Input" _FS_ "PropagationTimes.csv"));
	pcFamily = cFamilies.Get("LVC");
	fVcc = pcFamily->GetDefaultVoltageConfiguration(DEFAULT_LOGIC_LEVEL)->GetVcc();
	cSimulation.Init("Ground");
	cCircuit.Init();
	AssertTrue(LoadCircuitFile(&cCircuit, &cSimulation, &cFamilies, "Input" _FS_ "GroundInverters.xml"));
	cSimulation.GetTimeline()->Run();
	AssertInt(TV_High, pcFamily->GetValue(cCircuit.GetTrace(2)->GetTrace(0)->GetVoltage(cSimulation.GetTime()), fVcc));
	AssertInt(TV_High, pcFamily->GetValue(cCircuit.GetTrace(3)->GetTrace(0)->GetVoltage(cSimulation.GetTime()), fVcc));
	cCircuit.Kill();
	cSimulation.Kill();
	cFamilies.Kill();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
// Saves what the IC remembers inside a root element, reads the file back
// and loads it into the other IC.
//
//////////////////////////////////////////////////////////////////////////
void SaveAndLoadState(CIntegratedCircuit* pcSaved, CIntegratedCircuit* pcLoaded)
{
	CXMLWriter	cWriter;
	CXMLFile	cFile;
	CStateXML*	pcStateXML;
	CFileUtil	cFileUtil;
	CMarkupTag*	pcTag;

	pcStateXML = FindStateXMLForIntegratedCircuit(pcSaved);
	AssertNotNull(pcStateXML);
	cWriter.Init();
	cWriter.Begin("Root");
	pcStateXML->Save(&cWriter, pcSaved);
	cWriter.End();
	cFileUtil.MakeDir("Output");
	AssertTrue(cWriter.Write("Output" _FS_ "State.xml"));
	cWriter.Kill();

	cFile.Init();
	AssertTrue(cFile.Read("State.xml", "Output"));
	pcTag = cFile.mcMarkup.mpcDoc->GetRootTag()->GetTag(pcStateXML->GetXMLName());
	AssertNotNull(pcTag);
	AssertTrue(FindStateXMLForElement(pcStateXML->GetXMLName()) == pcStateXML);
	AssertTrue(pcStateXML->Load(pcTag, pcLoaded));
	cFile.Kill();

	cFileUtil.Delete("Output" _FS_ "State.xml");
	cFileUtil.RemoveDir("Output");
}


//////////////////////////////////////////////////////////////////////////
//
// Asserts the IC saves the same state as the fresh one of its kind.
//
//////////////////////////////////////////////////////////////////////////
void AssertSameStateXML(CIntegratedCircuit* pcFresh, CIntegratedCircuit* pcIntegratedCircuit)
{
	CXMLWriter	cFresh;
	CXMLWriter	cOther;
	CStateXML*	pcStateXML;

	pcStateXML = FindStateXMLForIntegratedCircuit(pcFresh);
	cFresh.Init();
	pcStateXML->Save(&cFresh, pcFresh);
	cOther.Init();
	pcStateXML->Save(&cOther, pcIntegratedCircuit);
	AssertString(cFresh.GetText(), cOther.GetText());
	cOther.Kill();
	cFresh.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// What each kind of IC remembers comes back as it was saved.  Gates
// remember nothing.
//
//////////////////////////////////////////////////////////////////////////
void TestSimulationStateStates(void)
{
	CFamilyVoltageConfigurationStore	cFamilies;
	CFamilyVoltageConfiguration*		pcFamily;
	CCircuitSimulation					cSimulation;
	CSubcircuitSimulation*				pcTop;
	CClockOscillator*					apcClock[2];
	CConstant*							apcConstant[2];
	CCounter*							apcCounter[2];
	CDTypeFlipFlop*						apcFlop[2];
	COscilloscope*						apcScope[2];
	CClockOscillatorPins*				pcClockPins;
	CConstantPins*						pcConstantPins;
	CCounterPins*						pcCounterPins;
	CDTypeFlipFlopPins*					pcFlopPins;
	COscilloscopePins*					pcScopePins;
	CAndGatePins*						pcAndPins;
	CAndGate*							pcAnd;
	int									i;

	ObjectsInit();
	cFamilies.Init();
	AssertTrue(cFamilies.Load("Input" _FS_ "PropagationTimes.csv"));
	pcFamily = cFamilies.Get("LVC");
	cSimulation.Init("States");
	pcTop = cSimulation.GetSubcircuitTopSimulation();
	for (i = 0; i < 2; i++)
	{
		pcClockPins = NewMalloc<CClockOscillatorPins>();
		pcClockPins->Init(pcFamily, true);
		apcClock[i] = NewMalloc<CClockOscillator>();
		apcClock[i]->Init(pcTop, "Clock", pcClockPins, 1000000.0f);
		pcConstantPins = NewMalloc<CConstantPins>();
		pcConstantPins->Init(pcFamily, 8);
		apcConstant[i] = NewMalloc<CConstant>();
		apcConstant[i]->Init(pcTop, "Constant", pcConstantPins, 0x12);
		pcCounterPins = NewMalloc<CCounterPins>();
		pcCounterPins->Init(pcFamily, 4);
		apcCounter[i] = NewMalloc<CCounter>();
		apcCounter[i]->Init(pcTop, "Counter", pcCounterPins, 4, 15);
		pcFlopPins = NewMalloc<CDTypeFlipFlopPins>();
		pcFlopPins->Init(pcFamily);
		apcFlop[i] = NewMalloc<CDTypeFlipFlop>();
		apcFlop[i]->Init(pcTop, "Flop", pcFlopPins);
		pcScopePins = NewMalloc<COscilloscopePins>();
		pcScopePins->Init(2);
		apcScope[i] = NewMalloc<COscilloscope>();
		apcScope[i]->Init(pcTop, "Scope", pcScopePins, 1000000.0f, 1, 3);
	}

	//Made, they remember how they start.
	AssertFalse(apcClock[1]->IsHigh());
	AssertLong(0, apcClock[1]->GetFullTicks());
	AssertLong(0x12, apcConstant[1]->GetConstantValue());
	AssertInt(0, (int)apcCounter[1]->GetCount());
	AssertFalse(apcFlop[1]->GetState());
	AssertSize(3, apcScope[1]->GetSampleCount());
	AssertTrue(apcScope[1]->GetMaxVoltage(1, 2) == 0.0f);

	apcClock[0]->SetHigh(true);
	apcClock[0]->SetFullTicks(123456789012LL);
	SaveAndLoadState(apcClock[0], apcClock[1]);
	AssertTrue(apcClock[1]->IsHigh());
	AssertLong(123456789012LL, apcClock[1]->GetFullTicks());

	apcConstant[0]->SetConstantValue(-1234567890123LL);
	SaveAndLoadState(apcConstant[0], apcConstant[1]);
	AssertLong(-1234567890123LL, apcConstant[1]->GetConstantValue());

	apcCounter[0]->SetCount(0xFFFFFFF0);
	apcCounter[0]->SetTerminal(true);
	SaveAndLoadState(apcCounter[0], apcCounter[1]);
	AssertInt((int)0xFFFFFFF0, (int)apcCounter[1]->GetCount());
	AssertTrue(apcCounter[1]->IsTerminal());

	apcFlop[0]->SetState(true);
	SaveAndLoadState(apcFlop[0], apcFlop[1]);
	AssertTrue(apcFlop[1]->GetState());

	apcScope[0]->SetVoltages(0, 0, 0.1f, 3.3f);
	apcScope[0]->SetVoltages(0, 2, -0.25f, 1.0f / 3.0f);
	apcScope[0]->SetVoltages(1, 1, 5.0f, 7.0f);
	apcScope[0]->SetTickPosition(2);
	SaveAndLoadState(apcScope[0], apcScope[1]);
	AssertSize(2, apcScope[1]->GetTickPosition());
	AssertTrue(apcScope[1]->GetMinVoltage(0, 0) == 0.1f);
	AssertTrue(apcScope[1]->GetMaxVoltage(0, 0) == 3.3f);
	AssertTrue(apcScope[1]->GetMinVoltage(0, 2) == -0.25f);
	AssertTrue(apcScope[1]->GetMaxVoltage(0, 2) == 1.0f / 3.0f);
	AssertTrue(apcScope[1]->GetMaxVoltage(1, 1) == 7.0f);
	AssertTrue(apcScope[1]->GetMinVoltage(1, 2) == 0.0f);

	//Resetting sets everything they remember back to how a fresh one starts.
	for (i = 0; i < 2; i++)
	{
		apcClock[i]->ResetState();
		apcConstant[i]->ResetState();
		apcCounter[i]->ResetState();
		apcFlop[i]->ResetState();
		apcScope[i]->ResetState();
	}
	pcClockPins = NewMalloc<CClockOscillatorPins>();
	pcClockPins->Init(pcFamily, true);
	apcClock[1] = NewMalloc<CClockOscillator>();
	apcClock[1]->Init(pcTop, "Clock", pcClockPins, 1000000.0f);
	pcConstantPins = NewMalloc<CConstantPins>();
	pcConstantPins->Init(pcFamily, 8);
	apcConstant[1] = NewMalloc<CConstant>();
	apcConstant[1]->Init(pcTop, "Constant", pcConstantPins, 0x12);
	pcCounterPins = NewMalloc<CCounterPins>();
	pcCounterPins->Init(pcFamily, 4);
	apcCounter[1] = NewMalloc<CCounter>();
	apcCounter[1]->Init(pcTop, "Counter", pcCounterPins, 4, 15);
	pcFlopPins = NewMalloc<CDTypeFlipFlopPins>();
	pcFlopPins->Init(pcFamily);
	apcFlop[1] = NewMalloc<CDTypeFlipFlop>();
	apcFlop[1]->Init(pcTop, "Flop", pcFlopPins);
	pcScopePins = NewMalloc<COscilloscopePins>();
	pcScopePins->Init(2);
	apcScope[1] = NewMalloc<COscilloscope>();
	apcScope[1]->Init(pcTop, "Scope", pcScopePins, 1000000.0f, 1, 3);
	AssertSameStateXML(apcClock[1], apcClock[0]);
	AssertSameStateXML(apcConstant[1], apcConstant[0]);
	AssertSameStateXML(apcCounter[1], apcCounter[0]);
	AssertSameStateXML(apcFlop[1], apcFlop[0]);
	AssertSameStateXML(apcScope[1], apcScope[0]);
	AssertLong(0x12, apcConstant[0]->GetConstantValue());

	pcAndPins = NewMalloc<CAndGatePins>();
	pcAndPins->Init(2, pcFamily);
	pcAnd = NewMalloc<CAndGate>();
	pcAnd->Init(pcTop, "And", pcAndPins);
	AssertNull(FindStateXMLForIntegratedCircuit(pcAnd));
	AssertNull(FindStateXMLForElement("Toaster"));

	cSimulation.Kill();
	cFamilies.Kill();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
bool LoadSimulationText(const char* szSimulation)
{
	CFamilyVoltageConfigurationStore	cFamilies;
	CCircuitSimulation					cSimulation;
	CCircuitView						cCircuit;
	CTextFile							cText;
	CFileUtil							cFileUtil;
	CChars								sz;
	bool								bResult;

	sz.Init("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<Logicim version=\"1\"><Circuit>");
	sz.Append("<Inverter name=\"\" x=\"0\" y=\"0\" rotation=\"West\" family=\"LVC\" inputCount=\"1\" inputWidth=\"1\"/>");
	sz.Append("<Ground name=\"\" x=\"-1\" y=\"0\" rotation=\"North\"/>");
	sz.Append("</Circuit>");
	sz.Append(szSimulation);
	sz.Append("</Logicim>\n");
	cFileUtil.MakeDir("Output");
	cText.Init(sz.Text());
	cText.Write("Output" _FS_ "BadSimulation.xml");
	cText.Kill();
	sz.Kill();

	ObjectsInit();
	cFamilies.Init();
	cFamilies.Load("Input" _FS_ "PropagationTimes.csv");
	cSimulation.Init("Bad");
	cCircuit.Init();
	bResult = LoadCircuitFile(&cCircuit, &cSimulation, &cFamilies, "Output" _FS_ "BadSimulation.xml");
	cCircuit.Kill();
	cSimulation.Kill();
	cFamilies.Kill();
	ObjectsKill();

	cFileUtil.Delete("Output" _FS_ "BadSimulation.xml");
	cFileUtil.RemoveDir("Output");
	return bResult;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSimulationStateErrors(void)
{
	SLogConfig	sLogConfig;

	gcLogger.GetConfig(&sLogConfig);
	gcLogger.SetSilent();

	AssertTrue(LoadSimulationText("<Simulation name=\"S\" time=\"10\" previousEventTime=\"5\" eventTime=\"10\"><Component index=\"0\"><Port name=\"Input\"><TransitionEvent time=\"20\" id=\"7\" voltage=\"0\"/></Port></Component></Simulation>"));
	AssertFalse(LoadSimulationText("<Simulation name=\"S\" time=\"10\" previousEventTime=\"5\"/>"));
	AssertFalse(LoadSimulationText("<Simulation name=\"S\" time=\"10\" previousEventTime=\"5\" eventTime=\"10\"><Component index=\"2\"/></Simulation>"));
	AssertFalse(LoadSimulationText("<Simulation name=\"S\" time=\"10\" previousEventTime=\"5\" eventTime=\"10\"><Thing/></Simulation>"));
	AssertFalse(LoadSimulationText("<Simulation name=\"S\" time=\"10\" previousEventTime=\"5\" eventTime=\"10\"><Component index=\"0\"><Port name=\"Nope\"/></Component></Simulation>"));
	AssertFalse(LoadSimulationText("<Simulation name=\"S\" time=\"10\" previousEventTime=\"5\" eventTime=\"10\"><Component index=\"0\"><Port name=\"Input\"><TransitionEvent time=\"10\" id=\"7\" voltage=\"0\"/></Port></Component></Simulation>"));
	AssertFalse(LoadSimulationText("<Simulation name=\"S\" time=\"10\" previousEventTime=\"5\" eventTime=\"10\"><Component index=\"0\"><Port name=\"Output\"><Output type=\"Wobble\" time=\"3\"/></Port></Component></Simulation>"));
	AssertFalse(LoadSimulationText("<Simulation name=\"S\" time=\"10\" previousEventTime=\"5\" eventTime=\"10\"><Component index=\"0\"><Toaster/></Component></Simulation>"));
	AssertFalse(LoadSimulationText("<Simulation name=\"S\" time=\"10\" previousEventTime=\"5\" eventTime=\"10\"><Component index=\"1\"><TickEvent time=\"20\" id=\"1\"/></Component></Simulation>"));
	AssertFalse(LoadSimulationText("<Simulation name=\"S\" time=\"10\" previousEventTime=\"5\" eventTime=\"10\"><Component index=\"0\"><ClockOscillatorState high=\"true\" fullTicks=\"1\"/></Component></Simulation>"));

	gcLogger.SetConfig(&sLogConfig);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSimulationState(void)
{
	BeginTests();
	DataIOInit();
	DataMemoryInit();

	TestSimulationStateStates();
	TestSimulationStateRingRoundTrip();
	TestSimulationStateFreshStart();
	TestSimulationStateErrors();

	DataMemoryKill();
	DataIOKill();
	TestStatistics();
}

