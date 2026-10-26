#include <string.h>
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
#include "LogicimLib/W65C816View.h"
#include "LogicimLib/ClockView.h"
#include "LogicimLib/ValueView.h"
#include "LogicimLib/TunnelView.h"
#include "LogicimLib/PowerSourceView.h"
#include "MicroprocessorLib/W65C816Chip.h"
#include "MicroprocessorLib/W65C816InstructionFactory.h"
#include "MicroprocessorLib/65C64Chip.h"
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
	pcNand->Init(-17, 0, ROT_East, "U1", "LVC", false, 2, 1);
	pcCircuit->Add(pcNand);
	pcInverter = NewMalloc<CInverterView>();
	pcInverter->Init(-11, 0, ROT_East, "U2", "LVC", false, 1, 1);
	pcCircuit->Add(pcInverter);
	pcInverter = NewMalloc<CInverterView>();
	pcInverter->Init(-6, 0, ROT_East, "U3", "LVC", false, 1, 1);
	pcCircuit->Add(pcInverter);
	pcBuffer = NewMalloc<CBufferView>();
	pcBuffer->Init(2, 0, ROT_East, "U4", "LVC", false, 1, 1);
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
CPowerSource* AddRingEnable(CCircuitSimulation* pcSimulation, CCircuitView* pcCircuit, CViewPath* pcViewPath, float32 fVoltage, bool bLive)
{
	CPowerSource*	pcSupply;

	pcSupply = &OMalloc<CPowerSource>(pcSimulation->GetSubcircuitTopSimulation(), "Enable", fVoltage);
	if (bLive)
	{
		AssertTrue(pcSupply->GetPowerOutPort()->ConnectLive(pcCircuit->GetTrace(0)->GetTrace(pcViewPath, pcSimulation, 0), pcSimulation->GetTimeline()));
	}
	else
	{
		AssertTrue(pcSupply->GetPowerOutPort()->Connect(pcCircuit->GetTrace(0)->GetTrace(pcViewPath, pcSimulation, 0)));
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
	CViewPaths							cPaths;
	CViewPath*							pcOriginalPath;
	CViewPath*							pcLoadedPath;
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
	cPaths.Init();
	pcOriginalPath = cPaths.AddTop(&cOriginalView);
	AddRingOscillatorViews(&cOriginalView);
	AssertTrue(cOriginalView.CreateSimulation(pcOriginalPath, &cOriginal, &cFamilies));
	pcLow = AddRingEnable(&cOriginal, &cOriginalView, pcOriginalPath, 0.0f, true);
	cOriginal.GetTimeline()->Run();
	pcLow->GetPowerOutPort()->Disconnect(cOriginal.GetTimeline());
	AddRingEnable(&cOriginal, &cOriginalView, pcOriginalPath, fVcc, true);
	cOriginal.RunToTime(NanosecondsToTime((int64)37));
	AssertTrue(cOriginal.GetTimeline()->NumSimultaneousEvents() > 0);

	cFileUtil.MakeDir("Output");
	AssertTrue(SaveCircuitFile(&cOriginalView, pcOriginalPath, &cOriginal, "Output" _FS_ "Ring.xml"));

	cLoaded.Init("Ring");
	cLoadedView.Init();
	pcLoadedPath = cPaths.AddTop(&cLoadedView);
	AssertTrue(LoadCircuitFile(&cLoadedView, pcLoadedPath, &cLoaded, &cFamilies, "Output" _FS_ "Ring.xml"));
	AddRingEnable(&cLoaded, &cLoadedView, pcLoadedPath, fVcc, false);
	AssertLong(cOriginal.GetTime(), cLoaded.GetTime());
	AssertSize(cOriginal.GetTimeline()->NumSimultaneousEvents(), cLoaded.GetTimeline()->NumSimultaneousEvents());

	cOriginalText.Init();
	SaveCircuitXML(&cOriginalView, pcOriginalPath, &cOriginal, &cOriginalText);
	cLoadedText.Init();
	SaveCircuitXML(&cLoadedView, pcLoadedPath, &cLoaded, &cLoadedText);
	AssertString(cOriginalText.GetText(), cLoadedText.GetText());
	cLoadedText.Kill();
	cOriginalText.Kill();

	bSame = true;
	iTransitions = 0;
	fLastNandVoltage = cOriginalView.GetTrace(1)->GetTrace(pcOriginalPath, &cOriginal, 0)->GetVoltage(cOriginal.GetTime());
	for (iStep = 0; (iStep < 300) && bSame; iStep++)
	{
		cOriginal.RunToTime(NanosecondsToTime((int64)1));
		cLoaded.RunToTime(NanosecondsToTime((int64)1));
		bSame = cOriginal.GetTime() == cLoaded.GetTime();
		for (i = 0; (i < cOriginalView.NumTraces()) && bSame; i++)
		{
			fOriginal = cOriginalView.GetTrace(i)->GetTrace(pcOriginalPath, &cOriginal, 0)->GetVoltage(cOriginal.GetTime());
			fLoaded = cLoadedView.GetTrace(i)->GetTrace(pcLoadedPath, &cLoaded, 0)->GetVoltage(cLoaded.GetTime());
			bSame = (fOriginal == fLoaded) || (!IsVoltage(fOriginal) && !IsVoltage(fLoaded));
		}
		fOriginal = cOriginalView.GetTrace(1)->GetTrace(pcOriginalPath, &cOriginal, 0)->GetVoltage(cOriginal.GetTime());
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
	cPaths.Kill();
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
	CViewPaths							cPaths;
	CViewPath*							pcPath;
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
	cPaths.Init();
	pcPath = cPaths.AddTop(&cCircuit);
	AssertTrue(LoadCircuitFile(&cCircuit, pcPath, &cSimulation, &cFamilies, "Input" _FS_ "GroundInverters.xml"));
	cSimulation.GetTimeline()->Run();
	AssertInt(TV_High, pcFamily->GetValue(cCircuit.GetTrace(2)->GetTrace(pcPath, &cSimulation, 0)->GetVoltage(cSimulation.GetTime()), fVcc));
	AssertInt(TV_High, pcFamily->GetValue(cCircuit.GetTrace(3)->GetTrace(pcPath, &cSimulation, 0)->GetVoltage(cSimulation.GetTime()), fVcc));
	cCircuit.Kill();
	cPaths.Kill();
	cSimulation.Kill();
	cFamilies.Kill();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
// The IC's state element, as a saved simulation has it.
//
//////////////////////////////////////////////////////////////////////////
void SaveStateXML(CXMLWriter* pcWriter, CIntegratedCircuit* pcIntegratedCircuit)
{
	AssertTrue(pcIntegratedCircuit->GetStateXMLName() != NULL);
	pcWriter->Begin(pcIntegratedCircuit->GetStateXMLName());
	pcIntegratedCircuit->SaveXML(pcWriter);
	pcWriter->End();
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
	CFileUtil	cFileUtil;
	CMarkupTag*	pcTag;

	cWriter.Init();
	cWriter.Begin("Root");
	SaveStateXML(&cWriter, pcSaved);
	cWriter.End();
	cFileUtil.MakeDir("Output");
	AssertTrue(cWriter.Write("Output" _FS_ "State.xml"));
	cWriter.Kill();

	cFile.Init();
	AssertTrue(cFile.Read("State.xml", "Output"));
	pcTag = cFile.mcMarkup.mpcDoc->GetRootTag()->GetTag(pcLoaded->GetStateXMLName());
	AssertNotNull(pcTag);
	AssertTrue(pcLoaded->LoadXML(pcTag));
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

	cFresh.Init();
	SaveStateXML(&cFresh, pcFresh);
	cOther.Init();
	SaveStateXML(&cOther, pcIntegratedCircuit);
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
		apcClock[i] = &OMalloc<CClockOscillator>(pcTop, "Clock", OMalloc<CClockOscillatorPins>(pcFamily, true), 1000000.0f);
		apcConstant[i] = &OMalloc<CConstant>(pcTop, "Constant", OMalloc<CConstantPins>(pcFamily, 8), 0x12);
		apcCounter[i] = &OMalloc<CCounter>(pcTop, "Counter", OMalloc<CCounterPins>(pcFamily, 4), 4, 15);
		apcFlop[i] = &OMalloc<CDTypeFlipFlop>(pcTop, "Flop", OMalloc<CDTypeFlipFlopPins>(pcFamily));
		apcScope[i] = &OMalloc<COscilloscope>(pcTop, "Scope", OMalloc<COscilloscopePins>(2), 1000000.0f, 1, 3);
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
	apcClock[1] = &OMalloc<CClockOscillator>(pcTop, "Clock", OMalloc<CClockOscillatorPins>(pcFamily, true), 1000000.0f);
	apcConstant[1] = &OMalloc<CConstant>(pcTop, "Constant", OMalloc<CConstantPins>(pcFamily, 8), 0x12);
	apcCounter[1] = &OMalloc<CCounter>(pcTop, "Counter", OMalloc<CCounterPins>(pcFamily, 4), 4, 15);
	apcFlop[1] = &OMalloc<CDTypeFlipFlop>(pcTop, "Flop", OMalloc<CDTypeFlipFlopPins>(pcFamily));
	apcScope[1] = &OMalloc<COscilloscope>(pcTop, "Scope", OMalloc<COscilloscopePins>(2), 1000000.0f, 1, 3);
	AssertSameStateXML(apcClock[1], apcClock[0]);
	AssertSameStateXML(apcConstant[1], apcConstant[0]);
	AssertSameStateXML(apcCounter[1], apcCounter[0]);
	AssertSameStateXML(apcFlop[1], apcFlop[0]);
	AssertSameStateXML(apcScope[1], apcScope[0]);
	AssertLong(0x12, apcConstant[0]->GetConstantValue());

	pcAnd = &OMalloc<CAndGate>(pcTop, "And", OMalloc<CAndGatePins>(2, pcFamily));
	AssertTrue(pcAnd->GetStateXMLName() == NULL);

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
	CViewPaths							cPaths;
	CTextFile							cText;
	CFileUtil							cFileUtil;
	CChars								sz;
	bool								bResult;

	sz.Init("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<Logicim version=\"2\"><Circuit>");
	sz.Append("<Inverter name=\"\" x=\"0\" y=\"0\" rotation=\"East\" family=\"LVC\" inputCount=\"1\" inputWidth=\"1\"/>");
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
	cPaths.Init();
	bResult = LoadCircuitFile(&cCircuit, cPaths.AddTop(&cCircuit), &cSimulation, &cFamilies, "Output" _FS_ "BadSimulation.xml");
	cCircuit.Kill();
	cPaths.Kill();
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
// A W65C816 reading NOPs (0xEA) off its data bus, clocked at 4MHz, with
// its reset, interrupt, RDY and BE inputs held high through tunnels.
//
//////////////////////////////////////////////////////////////////////////
CW65C816View* AddNOPProcessorViews(CCircuitView* pcCircuit)
{
	CW65C816View*		pcMPU;
	CClockView*			pcClock;
	CConstantView*		pcData;
	CPositivePowerView*	pcPower;
	CTunnelView*		pcTunnel;
	SInt32Vec2			sPosition;
	SInt32Vec2			sMinimum;
	SInt32Vec2			sMaximum;
	SFloat64Vec2		sTunnelMinimum;
	SFloat64Vec2		sTunnelMaximum;
	const char*			aszHigh[] = { "RESB", "NMIB", "IRQB", "ABORTB", "RDY", "BE" };
	size				i;

	pcMPU = NewMalloc<CW65C816View>();
	pcMPU->Init(0, 0, ROT_East, "MPU", "LVC", false);
	pcCircuit->Add(pcMPU);

	sPosition = pcMPU->GetPortView("PHI2")->GetGridPosition();
	pcClock = NewMalloc<CClockView>();
	pcClock->Init(sPosition.x - 4, sPosition.y + 1, ROT_North, "Clock", "LVC", false, 4000000, false);
	pcCircuit->Add(pcClock);
	pcCircuit->AddTrace(sPosition.x - 4, sPosition.y, sPosition.x, sPosition.y);

	sPosition = pcMPU->GetPortView("Data 0")->GetGridPosition();
	sMinimum.Init(-2, -1);
	sMaximum.Init(0, 1);
	pcData = NewMalloc<CConstantView>();
	pcData->Init(sPosition.x, sPosition.y, ROT_West, "Data", "LVC", false, 8, RADIX_Hexadecimal, sMinimum, sMaximum);
	pcCircuit->Add(pcData);

	sTunnelMinimum.Init(0, -0.65);
	sTunnelMaximum.Init(3, 0.65);
	pcPower = NewMalloc<CPositivePowerView>();
	pcPower->Init(-30, -20, ROT_South, "High", 3.3f);
	pcCircuit->Add(pcPower);
	pcTunnel = NewMalloc<CTunnelView>();
	pcTunnel->Init(-30, -19, ROT_South, "high", false, sTunnelMinimum, sTunnelMaximum);
	pcCircuit->Add(pcTunnel);
	for (i = 0; i < sizeof(aszHigh) / sizeof(const char*); i++)
	{
		sPosition = pcMPU->GetPortView(aszHigh[i])->GetGridPosition();
		pcTunnel = NewMalloc<CTunnelView>();
		pcTunnel->Init(sPosition.x, sPosition.y, ROT_West, "high", false, sTunnelMinimum, sTunnelMaximum);
		pcCircuit->Add(pcTunnel);
	}
	return pcMPU;
}


//////////////////////////////////////////////////////////////////////////
//
// Every register, flag and latch of a W65C816's core comes back as it was
// saved.
//
//////////////////////////////////////////////////////////////////////////
void TestSimulationStateW65C816Core(void)
{
	CFamilyVoltageConfigurationStore	cFamilies;
	CCircuitSimulation					cSimulation;
	CW65C816Chip*						apcChip[2];
	SW65CCoreState						sSet;
	SW65CCoreState						sGot;
	size								i;

	CW65C816InstructionFactory::GetInstance()->Init();
	ObjectsInit();
	cFamilies.Init();
	AssertTrue(cFamilies.Load("Input" _FS_ "PropagationTimes.csv"));
	cSimulation.Init("Core");
	for (i = 0; i < 2; i++)
	{
		apcChip[i] = &OMalloc<CW65C816Chip>(cSimulation.GetSubcircuitTopSimulation(), "MPU", OMalloc<CW65C816ChipPins>(cFamilies.Get("LVC")));
	}

	memset(&sSet, 0, sizeof(SW65CCoreState));
	sSet.bEmulationFlag = false;
	sSet.bZeroFlag = true;
	sSet.bNegativeFlag = true;
	sSet.bDecimalFlag = true;
	sSet.bInterruptDisableFlag = false;
	sSet.bAccumulatorWidthFlag = true;
	sSet.bIndexWidthFlag = false;
	sSet.bCarryFlag = true;
	sSet.bOverflowFlag = true;
	sSet.bBreakFlag = true;
	sSet.uiAccumulator = 0x1234;
	sSet.uiXIndex = 0x2345;
	sSet.uiYIndex = 0x3456;
	sSet.uiDataBank = 0x45;
	sSet.uiDirectPage = 0x5678;
	sSet.cProgramCounter.Init(0x67, 0x789A);
	sSet.uiStackPointer = 0x89AB;
	sSet.iCycle = 3;
	sSet.iNextCycle = 4;
	sSet.uiOpcodeIndex = 0xA9;
	sSet.bStopped = false;
	sSet.bWaiting = true;
	sSet.uiEmulationStatusBits = 0x30;
	sSet.uiAbortProcessRegister = 0x9A;
	sSet.uiAbortAccumulator = 0xABCD;
	sSet.uiAbortXIndex = 0xBCDE;
	sSet.uiAbortYIndex = 0xCDEF;
	sSet.uiAbortDataBank = 0xDE;
	sSet.uiAbortDirectPage = 0xEF01;
	sSet.cAbortProgramCounter.Init(0xF0, 0x0123);
	sSet.uiAbortStackPointer = 0x1357;
	sSet.cAddress.Init(0x24, 0x6802);
	sSet.uiData = 0x468A;
	sSet.uiIOData = 0x57;
	sSet.uiDirectOffset = 0x79;
	sSet.cNewProgramCounter.Init(0x9B, 0xBDF0);
	sSet.bBusEnable = false;
	sSet.bIrq = true;
	sSet.bAbort = true;
	sSet.bNextInstruction = true;
	sSet.bNmi = true;
	sSet.bPreviousClockLow = true;
	sSet.bPreviousClockHigh = false;
	sSet.uiResetCount = 2;
	apcChip[0]->GetMPU()->SetState(&sSet);

	SaveAndLoadState(apcChip[0], apcChip[1]);
	apcChip[1]->GetMPU()->GetState(&sGot);
	AssertBool(sSet.bEmulationFlag, sGot.bEmulationFlag);
	AssertBool(sSet.bDecimalFlag, sGot.bDecimalFlag);
	AssertBool(sSet.bWaiting, sGot.bWaiting);
	AssertBool(sSet.bPreviousClockLow, sGot.bPreviousClockLow);
	AssertInt(0x1234, sGot.uiAccumulator);
	AssertInt(0x45, sGot.uiDataBank);
	AssertInt(0x67, sGot.cProgramCounter.GetBank());
	AssertInt(0x789A, sGot.cProgramCounter.GetOffset());
	AssertInt(3, sGot.iCycle);
	AssertInt(0xA9, sGot.uiOpcodeIndex);
	AssertInt(0xF0, sGot.cAbortProgramCounter.GetBank());
	AssertInt(0x6802, sGot.cAddress.GetOffset());
	AssertInt(0x9B, sGot.cNewProgramCounter.GetBank());
	AssertInt(2, sGot.uiResetCount);

	//The whole state comes back, so no field is missing from what's saved, and saves the same from both.
	AssertMemory(&sSet, &sGot, sizeof(SW65CCoreState));
	AssertSameStateXML(apcChip[0], apcChip[1]);

	cSimulation.Kill();
	cFamilies.Kill();
	ObjectsKill();
	CW65C816InstructionFactory::GetInstance()->Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// Sets the state on the first chip, saves it, loads it into the second and
// asserts the second's whole state is the same.
//
//////////////////////////////////////////////////////////////////////////
void Assert65C64StateLoads(C65C64Chip* pcSaved, C65C64Chip* pcLoaded, S65C64CoreState* psState)
{
	S65C64CoreState	sSaved;
	S65C64CoreState	sLoaded;

	pcSaved->GetMPU()->SetState(psState);
	SaveAndLoadState(pcSaved, pcLoaded);
	memset(&sSaved, 0, sizeof(S65C64CoreState));
	pcSaved->GetMPU()->GetState(&sSaved);
	memset(&sLoaded, 0, sizeof(S65C64CoreState));
	pcLoaded->GetMPU()->GetState(&sLoaded);
	AssertMemory(&sSaved, &sLoaded, sizeof(S65C64CoreState));
	AssertInt(psState->eInstruction, sLoaded.eInstruction);
	AssertInt(psState->eDecoded, sLoaded.eDecoded);
}


//////////////////////////////////////////////////////////////////////////
//
// Every register, latch and transfer of a 65C64's core comes back as it
// was saved, as do which instruction it's running and what it decoded.
//
//////////////////////////////////////////////////////////////////////////
void TestSimulationState65C64Core(void)
{
	CFamilyVoltageConfigurationStore	cFamilies;
	CCircuitSimulation					cSimulation;
	C65C64Chip*							apcChip[2];
	S65C64CoreState						sState;
	size								i;

	ObjectsInit();
	cFamilies.Init();
	AssertTrue(cFamilies.Load("Input" _FS_ "PropagationTimes.csv"));
	cSimulation.Init("Core");
	for (i = 0; i < 2; i++)
	{
		apcChip[i] = &OMalloc<C65C64Chip>(cSimulation.GetSubcircuitTopSimulation(), "MPU", OMalloc<C65C64ChipPins>(cFamilies.Get("LVC")));
	}

	//An interrupt part way through with a transfer pending.
	memset(&sState, 0, sizeof(S65C64CoreState));
	sState.uiA = 0xFEDCBA9876543210ULL;
	sState.uiB = 0x0123456789ABCDEFULL;
	sState.uiX = 0x8000000000000001ULL;
	sState.uiY = 0x42;
	sState.uiS = 0x0001FFF0;
	sState.uiV = 0x12345678;
	sState.uiW = 0x9ABCDEF0;
	sState.uiC = 0x00001010;
	sState.uiP = 0x05C3;
	sState.uiInterruptDepth = 2;
	sState.uiDI = 0xFFFFFFFFFFFFFFFFULL;
	sState.uiOperationBytes = 4;
	sState.auiOperandWords[0] = 0x1111;
	sState.auiOperandWords[3] = 0xFFFF;
	sState.uiPointerAddress = 0x4000;
	sState.uiPointer = 0x2000;
	sState.uiNumPointerWords = 2;
	sState.uiEffectiveAddress = 0x4001;
	sState.uiVectorAddress = 0xFFFFFFE8;
	sState.uiVector = 0x00003000;
	sState.asTransfers[0].uiAddress = 0x0001FFFC;
	sState.asTransfers[0].uiBytes = 4;
	sState.asTransfers[0].bWrite = true;
	sState.asTransfers[0].uiValue = 0x1010;
	sState.aePulled[0] = R65_Zero;
	sState.asTransfers[1].uiAddress = 0x0001FFFA;
	sState.asTransfers[1].uiBytes = 2;
	sState.asTransfers[1].bRead = true;
	sState.asTransfers[1].bWrite = true;
	sState.asTransfers[1].uiValue = 0x05C3;
	sState.aePulled[1] = R65_Y;
	sState.uiNumTransfers = 2;
	sState.uiOpcode = 0x4045;
	sState.eDecoded = DK65_Interrupt;
	sState.uiDecodedVector = VECTOR_65C64_LEVEL;
	sState.eInstruction = IK65_Interrupt;
	sState.iCycle = 3;
	sState.iNextCycle = 4;
	sState.bNextInstruction = false;
	sState.bWaiting = true;
	sState.uiWakeMask = 0x1F;
	sState.uiPendingEdges = 0x0A;
	sState.uiEdgeLow = 0x05;
	sState.bLevelInterrupt = true;
	sState.uiIOData = 0xBEEF;
	sState.bPreviousClockLow = true;
	sState.bReset = true;
	Assert65C64StateLoads(apcChip[0], apcChip[1], &sState);

	//An instruction from its opcode.
	memset(&sState, 0, sizeof(S65C64CoreState));
	sState.uiS = 0x0001FFFF;
	sState.uiC = 0x00001008;
	sState.uiOpcode = 0x0820;
	sState.eDecoded = DK65_Opcode;
	sState.eInstruction = IK65_Opcode;
	sState.iCycle = 2;
	sState.iNextCycle = 3;
	Assert65C64StateLoads(apcChip[0], apcChip[1], &sState);

	cSimulation.Kill();
	cFamilies.Kill();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
// The text without its id="n" attributes.
//
//////////////////////////////////////////////////////////////////////////
void RemoveEventIDs(CChars* psz, const char* szText)
{
	const char*	szID;
	const char*	szEnd;

	for (;;)
	{
		szID = strstr(szText, " id=\"");
		if (szID == NULL)
		{
			psz->Append(szText);
			return;
		}
		psz->Append(szText, szID - szText);
		szEnd = strchr(szID + 5, '"');
		szText = (szEnd != NULL) ? szEnd + 1 : szID + 5;
	}
}


//////////////////////////////////////////////////////////////////////////
//
// A W65C816 saved part way through running NOPs and loaded into another
// simulation saves the same and then runs on exactly as the original.
//
//////////////////////////////////////////////////////////////////////////
void TestSimulationStateW65C816RoundTrip(void)
{
	CFamilyVoltageConfigurationStore	cFamilies;
	CCircuitSimulation					cOriginal;
	CCircuitSimulation					cLoaded;
	CCircuitView						cOriginalView;
	CCircuitView						cLoadedView;
	CViewPaths							cPaths;
	CViewPath*							pcOriginalPath;
	CViewPath*							pcLoadedPath;
	CW65C816View*						pcMPU;
	CConstant*							pcData;
	CXMLWriter							cOriginalText;
	CXMLWriter							cLoadedText;
	CFileUtil							cFileUtil;
	SW65CCoreState						sState;
	uint16								uiFirstPC;
	CW65C816Chip*						pcOriginalChip;
	CW65C816Chip*						pcLoadedChip;
	CChars								szOriginal;
	CChars								szLoaded;

	CW65C816InstructionFactory::GetInstance()->Init();
	ObjectsInit();
	CEvent::ResetNextID();
	CTrace::ResetNextID();
	cFamilies.Init();
	AssertTrue(cFamilies.Load("Input" _FS_ "PropagationTimes.csv"));

	cOriginal.Init("MPU");
	cOriginalView.Init();
	cPaths.Init();
	pcOriginalPath = cPaths.AddTop(&cOriginalView);
	pcMPU = AddNOPProcessorViews(&cOriginalView);
	AssertTrue(cOriginalView.CreateSimulation(pcOriginalPath, &cOriginal, &cFamilies));
	pcData = (CConstant*)cOriginalView.GetComponent(2)->GetComponent(pcOriginalPath, &cOriginal);
	pcData->SetConstantValue(0xEA);
	pcData->SimulationStarted(cOriginal.GetTimeline());
	cOriginal.RunToTime(NanosecondsToTime((int64)10000));
	pcOriginalChip = (CW65C816Chip*)pcMPU->GetComponent(pcOriginalPath, &cOriginal);
	pcOriginalChip->GetMPU()->GetState(&sState);
	uiFirstPC = sState.cProgramCounter.GetOffset();
	AssertFalse(sState.bStopped);

	cFileUtil.MakeDir("Output");
	AssertTrue(SaveCircuitFile(&cOriginalView, pcOriginalPath, &cOriginal, "Output" _FS_ "MPU.xml"));

	cLoaded.Init("MPU");
	cLoadedView.Init();
	pcLoadedPath = cPaths.AddTop(&cLoadedView);
	AssertTrue(LoadCircuitFile(&cLoadedView, pcLoadedPath, &cLoaded, &cFamilies, "Output" _FS_ "MPU.xml"));
	AssertLong(cOriginal.GetTime(), cLoaded.GetTime());

	cOriginalText.Init();
	SaveCircuitXML(&cOriginalView, pcOriginalPath, &cOriginal, &cOriginalText);
	AssertTrue(strstr(cOriginalText.GetText(), "<W65C816State ") != NULL);
	cLoadedText.Init();
	SaveCircuitXML(&cLoadedView, pcLoadedPath, &cLoaded, &cLoadedText);
	AssertString(cOriginalText.GetText(), cLoadedText.GetText());
	cLoadedText.Kill();
	cOriginalText.Kill();

	//Both simulations take new event ids from the one counter, so the ids of events made since differ.
	cOriginal.RunToTime(NanosecondsToTime((int64)10000));
	cLoaded.RunToTime(NanosecondsToTime((int64)10000));
	cOriginalText.Init();
	SaveCircuitXML(&cOriginalView, pcOriginalPath, &cOriginal, &cOriginalText);
	cLoadedText.Init();
	SaveCircuitXML(&cLoadedView, pcLoadedPath, &cLoaded, &cLoadedText);
	szOriginal.Init();
	RemoveEventIDs(&szOriginal, cOriginalText.GetText());
	szLoaded.Init();
	RemoveEventIDs(&szLoaded, cLoadedText.GetText());
	AssertString(szOriginal.Text(), szLoaded.Text());
	szLoaded.Kill();
	szOriginal.Kill();
	cLoadedText.Kill();
	cOriginalText.Kill();

	//NOPs move the program counter on a byte at a time.
	pcLoadedChip = (CW65C816Chip*)cLoadedView.GetComponent(0)->GetComponent(pcLoadedPath, &cLoaded);
	pcLoadedChip->GetMPU()->GetState(&sState);
	AssertTrue(sState.cProgramCounter.GetOffset() != uiFirstPC);
	AssertInt(0xEA, sState.uiOpcodeIndex);

	cLoadedView.Kill();
	cLoaded.Kill();
	cOriginalView.Kill();
	cOriginal.Kill();
	cPaths.Kill();
	cFamilies.Kill();
	ObjectsKill();
	CW65C816InstructionFactory::GetInstance()->Kill();

	cFileUtil.Delete("Output" _FS_ "MPU.xml");
	cFileUtil.RemoveDir("Output");
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
	TestSimulationStateW65C816Core();
	TestSimulationState65C64Core();
	TestSimulationStateW65C816RoundTrip();
	TestSimulationStateFreshStart();
	TestSimulationStateErrors();

	DataMemoryKill();
	DataIOKill();
	TestStatistics();
}

