#include "BaseLib/ConstructorCall.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/DataMemory.h"
#include "BaseLib/StringHelper.h"
#include "StandardLib/Objects.h"
#include "MicroprocessorLib/CircuitSimulation.h"
#include "MicroprocessorLib/FamilyVoltageConfigurationStore.h"
#include "MicroprocessorLib/Constant.h"
#include "MicroprocessorLib/Oscilloscope.h"
#include "MicroprocessorLib/Trace.h"
#include "MicroprocessorLib/Event.h"
#include "MicroprocessorLib/Timeline.h"
#include "MicroprocessorLib/LongTime.h"
#include "MicroprocessorLib/W65C816InstructionFactory.h"
#include "LogicimLib/ValueView.h"
#include "LogicimLib/ClockView.h"
#include "LogicimLib/LabelView.h"
#include "LogicimLib/PowerSourceView.h"
#include "LogicimLib/TunnelView.h"
#include "LogicimLib/SplitterView.h"
#include "LogicimLib/OscilloscopeView.h"
#include "LogicimLib/W65C816View.h"
#include "LogicimLib/65C64View.h"
#include "LogicimLib/CircuitView.h"
#include "TestLib/Assert.h"
#include "TestLogicimRender.h"


void LoadTestCircuitFonts(CCircuitFonts* pcFonts);
void KillTestCircuitFonts(CCircuitFonts* pcFonts);


//////////////////////////////////////////////////////////////////////////
//
// A circuit and the simulation it's made in.
//
//////////////////////////////////////////////////////////////////////////
struct SWiringTest
{
	CFamilyVoltageConfigurationStore	cFamilies;
	CCircuitSimulation					cSimulation;
	CCircuitView						cCircuit;

	void Init(void)
	{
		ObjectsInit();
		CEvent::ResetNextID();
		CTrace::ResetNextID();
		cFamilies.Init();
		AssertTrue(cFamilies.Load("Input" _FS_ "PropagationTimes.csv"));
		cSimulation.Init("Wiring");
		cCircuit.Init();
	}

	//Rooted objects (fonts) leave the root changed; it isn't checked.
	void Kill(bool bRooted = false)
	{
		cCircuit.Kill();
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
// Constants and probes two grid units long; a constant's value is set
// after the start, which resets it.
//
//////////////////////////////////////////////////////////////////////////
CConstantView* AddWiringConstant(CCircuitView* pcCircuit, int32 x, int32 y, ERotation eRotation, int32 iBitWidth, ERadix eRadix)
{
	CConstantView*	pcConstant;
	SInt32Vec2		sMinimum;
	SInt32Vec2		sMaximum;

	sMinimum.Init(-1, 0);
	sMaximum.Init(1, 2);
	pcConstant = NewMalloc<CConstantView>();
	pcConstant->Init(x, y, eRotation, "", "LVC", false, iBitWidth, eRadix, sMinimum, sMaximum);
	pcCircuit->Add(pcConstant);
	return pcConstant;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CProbeView* AddWiringProbe(CCircuitView* pcCircuit, int32 x, int32 y, ERotation eRotation, int32 iBitWidth, ERadix eRadix)
{
	CProbeView*		pcProbe;
	SInt32Vec2		sMinimum;
	SInt32Vec2		sMaximum;

	sMinimum.Init(-1, 0);
	sMaximum.Init(1, 2);
	pcProbe = NewMalloc<CProbeView>();
	pcProbe->Init(x, y, eRotation, "", "LVC", false, iBitWidth, eRadix, sMinimum, sMaximum);
	pcCircuit->Add(pcProbe);
	return pcProbe;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CTunnelView* AddWiringTunnel(CCircuitView* pcCircuit, int32 x, int32 y, ERotation eRotation, const char* szName, bool bDoubleSided, float64 fLength)
{
	CTunnelView*	pcTunnel;
	SFloat64Vec2	sMinimum;
	SFloat64Vec2	sMaximum;

	sMinimum.Init(-0.65, -fLength);
	sMaximum.Init(0.65, 0);
	pcTunnel = NewMalloc<CTunnelView>();
	pcTunnel->Init(x, y, eRotation, szName, bDoubleSided, sMinimum, sMaximum);
	pcCircuit->Add(pcTunnel);
	return pcTunnel;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void SetWiringConstant(CConstantView* pcView, int64 iValue, CCircuitSimulation* pcSimulation)
{
	CConstant*	pcConstant;

	pcConstant = (CConstant*)pcView->GetComponent();
	pcConstant->SetConstantValue(iValue);
	pcConstant->SimulationStarted(pcSimulation->GetTimeline());
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertValueText(const char* szExpected, CValueView* pcView, CCircuitSimulation* pcSimulation)
{
	CChars	sz;

	sz.Init();
	pcView->GetValueText(&sz, pcSimulation->GetTime());
	AssertString(szExpected, sz.Text());
	sz.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CTrace* GetPortViewTrace(CComponentView* pcView, size uiPortView, size uiBit)
{
	return pcView->GetPortView(uiPortView)->GetPort(uiBit)->GetTrace();
}


//////////////////////////////////////////////////////////////////////////
//
// Tunnels with the same name, ignoring case and the spaces around it, are
// one net; others aren't.  A double sided tunnel joins its two ends.
//
//////////////////////////////////////////////////////////////////////////
void TestWiringTunnels(void)
{
	SWiringTest		sTest;
	CConstantView*	pcConstant;
	CConstantView*	pcConstant2;
	CProbeView*		pcProbe;
	CProbeView*		pcOther;
	CProbeView*		pcDouble;
	CTunnelView*	pcTunnel;

	sTest.Init();
	pcConstant = AddWiringConstant(&sTest.cCircuit, 0, 0, ROT_West, 8, RADIX_Hexadecimal);
	sTest.cCircuit.AddTrace(0, 0, 4, 0);
	pcTunnel = AddWiringTunnel(&sTest.cCircuit, 4, 0, ROT_West, "Bus", false, 3);
	AssertString("bus", pcTunnel->GetConnectionName());
	AssertFalse(pcTunnel->MakesComponent());
	AddWiringTunnel(&sTest.cCircuit, 20, 0, ROT_East, " BUS ", false, 3);
	sTest.cCircuit.AddTrace(20, 0, 24, 0);
	pcProbe = AddWiringProbe(&sTest.cCircuit, 24, 0, ROT_East, 8, RADIX_Hexadecimal);
	AddWiringTunnel(&sTest.cCircuit, 20, 10, ROT_East, "Bus2", false, 3);
	sTest.cCircuit.AddTrace(20, 10, 24, 10);
	pcOther = AddWiringProbe(&sTest.cCircuit, 24, 10, ROT_East, 8, RADIX_Hexadecimal);

	//Double sided, 4 long: its ends are at 0, 20 and 0, 16.
	pcConstant2 = AddWiringConstant(&sTest.cCircuit, -6, 20, ROT_West, 4, RADIX_Hexadecimal);
	sTest.cCircuit.AddTrace(-6, 20, 0, 20);
	pcTunnel = AddWiringTunnel(&sTest.cCircuit, 0, 20, ROT_North, "Through", true, 4);
	AssertSize(2, pcTunnel->NumPortViews());
	AssertInt(0, pcTunnel->GetPortView(1)->GetGridPosition().x);
	AssertInt(16, pcTunnel->GetPortView(1)->GetGridPosition().y);
	sTest.cCircuit.AddTrace(0, 16, 6, 16);
	pcDouble = AddWiringProbe(&sTest.cCircuit, 6, 16, ROT_East, 4, RADIX_Hexadecimal);

	AssertTrue(sTest.cCircuit.CreateSimulation(&sTest.cSimulation, &sTest.cFamilies));
	SetWiringConstant(pcConstant, 0x5A, &sTest.cSimulation);
	SetWiringConstant(pcConstant2, 0xC, &sTest.cSimulation);
	sTest.cSimulation.GetTimeline()->Run();

	AssertValueText("5A", pcProbe, &sTest.cSimulation);
	AssertTrue(GetPortViewTrace(pcConstant, 0, 7) == GetPortViewTrace(pcProbe, 0, 7));
	AssertValueText("..", pcOther, &sTest.cSimulation);
	AssertTrue(GetPortViewTrace(pcConstant, 0, 0) != GetPortViewTrace(pcOther, 0, 0));
	AssertValueText("C", pcDouble, &sTest.cSimulation);

	sTest.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// A splitter's bus bits and end bits share traces, both ways.
//
//////////////////////////////////////////////////////////////////////////
void TestWiringSplitter(void)
{
	SWiringTest		sTest;
	CSplitterView*	pcSplitter;
	CConstantView*	pcConstant;
	CConstantView*	pcLow;
	CConstantView*	pcHigh;
	CProbeView*		pcProbeLow;
	CProbeView*		pcProbeHigh;
	CProbeView*		pcProbe;
	CChars			sz;
	CArrayInt		aiBits;

	sTest.Init();

	//Left handed, start offset 1: the bus is at 11, -1 and the ends at 10, 2 and 8, 2.
	pcSplitter = NewMalloc<CSplitterView>();
	pcSplitter->Init(10, 0, ROT_North, "S", 8, 2, 2, SA_LeftHanded, -1);
	sTest.cCircuit.Add(pcSplitter);
	AssertInt(11, pcSplitter->GetStartPortView()->GetGridPosition().x);
	AssertInt(-1, pcSplitter->GetStartPortView()->GetGridPosition().y);
	AssertInt(10, pcSplitter->GetEndPortView(0)->GetGridPosition().x);
	AssertInt(8, pcSplitter->GetEndPortView(1)->GetGridPosition().x);
	AssertInt(2, pcSplitter->GetEndPortView(1)->GetGridPosition().y);
	AssertString("End 4", pcSplitter->GetEndPortView(1)->GetPortName(0));
	pcConstant = AddWiringConstant(&sTest.cCircuit, 11, -1, ROT_South, 8, RADIX_Hexadecimal);
	pcProbeLow = AddWiringProbe(&sTest.cCircuit, 10, 2, ROT_South, 4, RADIX_Hexadecimal);
	pcProbeHigh = AddWiringProbe(&sTest.cCircuit, 8, 2, ROT_South, 4, RADIX_Hexadecimal);

	//The other way: two nybbles into the ends, the byte out of the bus.
	pcSplitter = NewMalloc<CSplitterView>();
	pcSplitter->Init(40, 0, ROT_North, "M", 8, 2, 2, SA_LeftHanded, -1);
	sTest.cCircuit.Add(pcSplitter);
	pcProbe = AddWiringProbe(&sTest.cCircuit, 41, -1, ROT_South, 8, RADIX_Hexadecimal);
	pcLow = AddWiringConstant(&sTest.cCircuit, 40, 2, ROT_South, 4, RADIX_Hexadecimal);
	pcHigh = AddWiringConstant(&sTest.cCircuit, 38, 2, ROT_South, 4, RADIX_Hexadecimal);

	AssertTrue(sTest.cCircuit.CreateSimulation(&sTest.cSimulation, &sTest.cFamilies));
	SetWiringConstant(pcConstant, 0xA5, &sTest.cSimulation);
	SetWiringConstant(pcLow, 0x3, &sTest.cSimulation);
	SetWiringConstant(pcHigh, 0xC, &sTest.cSimulation);
	sTest.cSimulation.GetTimeline()->Run();

	AssertValueText("5", pcProbeLow, &sTest.cSimulation);
	AssertValueText("A", pcProbeHigh, &sTest.cSimulation);
	AssertTrue(GetPortViewTrace(pcConstant, 0, 5) == GetPortViewTrace(pcProbeHigh, 0, 1));
	AssertValueText("C3", pcProbe, &sTest.cSimulation);

	//The labels on the ends.
	aiBits.Init();
	sz.Init();
	aiBits.Add(0);
	aiBits.Add(1);
	aiBits.Add(2);
	aiBits.Add(3);
	CSplitterView::AppendBitsText(&sz, &aiBits);
	AssertString("0-3", sz.Text());
	sz.ReInit();
	aiBits.ReInit();
	aiBits.Add(0);
	aiBits.Add(1);
	aiBits.Add(5);
	aiBits.Add(7);
	aiBits.Add(8);
	aiBits.Add(9);
	CSplitterView::AppendBitsText(&sz, &aiBits);
	AssertString("0,1,5,7-9", sz.Text());
	sz.Kill();
	aiBits.Kill();

	sTest.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// Bits go to the end their split index names, in order on the end, and
// splitters can follow each other.
//
//////////////////////////////////////////////////////////////////////////
void TestWiringSplitterIndicesAndChains(void)
{
	SWiringTest		sTest;
	CSplitterView*	pcSplitter;
	CConstantView*	pcConstant;
	CConstantView*	pcByte;
	CProbeView*		pcOdd;
	CProbeView*		pcEven;
	CProbeView*		pcLowPair;
	CProbeView*		pcHighPair;
	int				aiSplitIndices[4] = { 1, 0, 1, 0 };

	sTest.Init();

	//Odd bits to end 0, even bits to end 1.
	pcSplitter = NewMalloc<CSplitterView>();
	pcSplitter->Init(0, 0, ROT_North, "", 4, 2, 2, SA_RightHanded, 0, aiSplitIndices);
	sTest.cCircuit.Add(pcSplitter);
	AssertInt(0, pcSplitter->GetStartPortView()->GetGridPosition().x);
	AssertInt(2, pcSplitter->GetEndPortView(1)->GetGridPosition().x);
	pcConstant = AddWiringConstant(&sTest.cCircuit, 0, -1, ROT_South, 4, RADIX_Binary);
	pcOdd = AddWiringProbe(&sTest.cCircuit, 0, 2, ROT_South, 2, RADIX_Binary);
	pcEven = AddWiringProbe(&sTest.cCircuit, 2, 2, ROT_South, 2, RADIX_Binary);

	//A byte split in two and the low nybble split again, through a wire.
	pcSplitter = NewMalloc<CSplitterView>();
	pcSplitter->Init(20, 0, ROT_North, "", 8, 2, 2, SA_LeftHanded, -1);
	sTest.cCircuit.Add(pcSplitter);
	pcByte = AddWiringConstant(&sTest.cCircuit, 21, -1, ROT_South, 8, RADIX_Hexadecimal);
	sTest.cCircuit.AddTrace(20, 2, 20, 6);
	sTest.cCircuit.AddTrace(20, 6, 31, 6);
	pcSplitter = NewMalloc<CSplitterView>();
	pcSplitter->Init(30, 8, ROT_North, "", 4, 2, 2, SA_LeftHanded, -1);
	sTest.cCircuit.Add(pcSplitter);
	sTest.cCircuit.AddTrace(31, 6, 31, 7);
	pcLowPair = AddWiringProbe(&sTest.cCircuit, 30, 10, ROT_South, 2, RADIX_Hexadecimal);
	pcHighPair = AddWiringProbe(&sTest.cCircuit, 28, 10, ROT_South, 2, RADIX_Hexadecimal);

	AssertTrue(sTest.cCircuit.CreateSimulation(&sTest.cSimulation, &sTest.cFamilies));
	SetWiringConstant(pcConstant, 6, &sTest.cSimulation);
	SetWiringConstant(pcByte, 0xA6, &sTest.cSimulation);
	sTest.cSimulation.GetTimeline()->Run();

	//0110: bits 1 and 3 are 1 and 0, bits 0 and 2 are 0 and 1.
	AssertValueText("01", pcOdd, &sTest.cSimulation);
	AssertValueText("10", pcEven, &sTest.cSimulation);
	AssertTrue(GetPortViewTrace(pcConstant, 0, 3) == GetPortViewTrace(pcOdd, 0, 1));
	AssertTrue(GetPortViewTrace(pcConstant, 0, 2) == GetPortViewTrace(pcEven, 0, 1));

	//0110: bits 0 and 1 are 2, bits 2 and 3 are 1.
	AssertValueText("2", pcLowPair, &sTest.cSimulation);
	AssertValueText("1", pcHighPair, &sTest.cSimulation);
	AssertTrue(GetPortViewTrace(pcByte, 0, 1) == GetPortViewTrace(pcLowPair, 0, 1));

	sTest.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// A pin reads its trace levels; a label makes no component.
//
//////////////////////////////////////////////////////////////////////////
void TestWiringPinAndLabel(void)
{
	SWiringTest		sTest;
	CConstantView*	pcConstant;
	CPinView*		pcPin;
	CLabelView*		pcLabel;
	SInt32Vec2		sMinimum;
	SInt32Vec2		sMaximum;
	SFloat64Vec2	sFloatMinimum;
	SFloat64Vec2	sFloatMaximum;

	sTest.Init();
	pcConstant = AddWiringConstant(&sTest.cCircuit, 0, 0, ROT_West, 4, RADIX_Hexadecimal);
	sTest.cCircuit.AddTrace(0, 0, 6, 0);
	sMinimum.Init(-1, 0);
	sMaximum.Init(1, 2);
	pcPin = NewMalloc<CPinView>();
	pcPin->Init(6, 0, ROT_East, "D", "LVC", false, 4, RADIX_Hexadecimal, sMinimum, sMaximum);
	sTest.cCircuit.Add(pcPin);
	sFloatMinimum.Init(-0.5, -3);
	sFloatMaximum.Init(0.5, 0.25);
	pcLabel = NewMalloc<CLabelView>();
	pcLabel->Init(0, 6, ROT_West, "Note", TA_Left, false, true, true, sFloatMinimum, sFloatMaximum);
	sTest.cCircuit.Add(pcLabel);

	AssertTrue(sTest.cCircuit.CreateSimulation(&sTest.cSimulation, &sTest.cFamilies));
	AssertNull(pcLabel->GetComponent());
	AssertString("Pin", pcPin->GetComponent()->GetType());
	SetWiringConstant(pcConstant, 9, &sTest.cSimulation);
	sTest.cSimulation.GetTimeline()->Run();
	AssertValueText("9", pcPin, &sTest.cSimulation);

	sTest.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// A clock toggles a probe and draws its wave in its voltage's colour; an
// oscilloscope samples it.
//
//////////////////////////////////////////////////////////////////////////
void TestWiringClockAndOscilloscope(void)
{
	SWiringTest			sTest;
	CClockView*			pcClock;
	CProbeView*			pcProbe;
	COscilloscopeView*	pcScope;
	COscilloscope*		pcOscilloscope;
	size				i;
	size				uiHigh;
	size				uiLow;
	CChars				szFirst;
	CChars				szSecond;

	sTest.Init();
	pcClock = NewMalloc<CClockView>();
	pcClock->Init(0, 0, ROT_North, "Clk", "LVC", false, 10000000, false);
	sTest.cCircuit.Add(pcClock);
	AssertInt(0, pcClock->GetPortView("Output")->GetGridPosition().x);
	AssertInt(-1, pcClock->GetPortView("Output")->GetGridPosition().y);
	sTest.cCircuit.AddTrace(0, -1, 0, -4);
	sTest.cCircuit.AddTrace(0, -4, 6, -4);
	pcProbe = AddWiringProbe(&sTest.cCircuit, 6, -4, ROT_East, 1, RADIX_Binary);
	sTest.cCircuit.AddTrace(0, -4, 0, -10);
	pcScope = NewMalloc<COscilloscopeView>();
	pcScope->Init(0, -10, ROT_North, "Scope", "LVC", 1, 4, 8, 2, 100000000);
	sTest.cCircuit.Add(pcScope);

	AssertTrue(sTest.cCircuit.CreateSimulation(&sTest.cSimulation, &sTest.cFamilies));
	sTest.cSimulation.RunToTime(NanosecondsToTime((int64)125));
	szFirst.Init();
	pcProbe->GetValueText(&szFirst, sTest.cSimulation.GetTime());
	sTest.cSimulation.RunToTime(NanosecondsToTime((int64)50));
	szSecond.Init();
	pcProbe->GetValueText(&szSecond, sTest.cSimulation.GetTime());
	AssertTrue(((StringCompare(szFirst.Text(), "0") == 0) && (StringCompare(szSecond.Text(), "1") == 0)) ||
			   ((StringCompare(szFirst.Text(), "1") == 0) && (StringCompare(szSecond.Text(), "0") == 0)));
	szSecond.Kill();
	szFirst.Kill();

	pcOscilloscope = (COscilloscope*)pcScope->GetComponent();
	AssertSize(32, pcOscilloscope->GetSampleCount());
	uiHigh = 0;
	uiLow = 0;
	for (i = 0; i < pcOscilloscope->GetSampleCount(); i++)
	{
		if (pcOscilloscope->GetMaxVoltage(0, i) > 2.0f)
		{
			uiHigh++;
		}
		if (pcOscilloscope->GetMinVoltage(0, i) < 1.0f)
		{
			uiLow++;
		}
	}
	AssertTrue(uiHigh > 4);
	AssertTrue(uiLow > 4);

	sTest.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// A W65C816 clocked from reset shows its registers and flags.
//
//////////////////////////////////////////////////////////////////////////
void TestWiringW65C816(void)
{
	SWiringTest			sTest;
	CW65C816View*		pcMPU;
	CClockView*			pcClock;
	CCircuitColours		cColours;
	CCircuitFonts		cFonts;
	SInt32Vec2			sPHI2;

	CW65C816InstructionFactory::GetInstance()->Init();
	sTest.Init();
	cColours.InitLogicim();
	LoadTestCircuitFonts(&cFonts);
	pcMPU = NewMalloc<CW65C816View>();
	pcMPU->Init(0, 0, ROT_West, "MPU", "LVC", false);
	sTest.cCircuit.Add(pcMPU);
	AssertTrue(pcMPU->GetPortView("PHI2")->IsClock());
	AssertSize(16, pcMPU->GetPortView("Address 0")->NumPortNames());
	AssertString("RES", pcMPU->GetDetail(W65C816_OpCodeName));
	AssertTrue(pcMPU->IsFlagSet(W65C816_Emulation));
	AssertFalse(pcMPU->IsFlagVisible(W65C816_MemoryWidth));

	sPHI2 = pcMPU->GetPortView("PHI2")->GetGridPosition();
	pcClock = NewMalloc<CClockView>();
	pcClock->Init(sPHI2.x - 4, sPHI2.y + 1, ROT_North, "Clk", "LVC", false, 1000000, false);
	sTest.cCircuit.Add(pcClock);
	sTest.cCircuit.AddTrace(sPHI2.x - 4, sPHI2.y, sPHI2.x, sPHI2.y);

	AssertTrue(sTest.cCircuit.CreateSimulation(&sTest.cSimulation, &sTest.cFamilies));
	sTest.cSimulation.RunToTime(NanosecondsToTime((int64)5000));
	AssertRenderedCircuit(&sTest.cCircuit, &cColours, 700, 640, 1.5, sTest.cSimulation.GetTime(), false, "W65C816Running", &cFonts);
	AssertTrue(pcMPU->IsFlagSet(W65C816_Emulation));
	AssertString("B", pcMPU->GetFlagText(W65C816_IndexWidthOrBreak));

	cColours.Kill();
	KillTestCircuitFonts(&cFonts);
	sTest.Kill(true);
	CW65C816InstructionFactory::GetInstance()->Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// A 65C64 clocked from reset shows its registers and flags.
//
//////////////////////////////////////////////////////////////////////////
void TestWiring65C64(void)
{
	SWiringTest			sTest;
	C65C64View*			pcMPU;
	CClockView*			pcClock;
	CCircuitColours		cColours;
	CCircuitFonts		cFonts;
	SInt32Vec2			sPHI2;

	sTest.Init();
	cColours.InitLogicim();
	LoadTestCircuitFonts(&cFonts);
	pcMPU = NewMalloc<C65C64View>();
	pcMPU->Init(0, 0, ROT_West, "CPU", "LVC", false);
	sTest.cCircuit.Add(pcMPU);
	AssertTrue(pcMPU->GetPortView("PHI2")->IsClock());
	AssertTrue(pcMPU->GetPortView("RESB")->IsInverting());
	AssertSize(32, pcMPU->GetPortView("Address 0")->NumPortNames());
	AssertSize(16, pcMPU->GetPortView("Data 0")->NumPortNames());
	AssertSize(1, pcMPU->GetPortView("EIRQB 3")->NumPortNames());
	AssertString("RES", pcMPU->GetDetail(C65C64_OpCodeName));
	AssertFalse(pcMPU->IsFlagSet(C65C64_EdgeDisable));

	sPHI2 = pcMPU->GetPortView("PHI2")->GetGridPosition();
	pcClock = NewMalloc<CClockView>();
	pcClock->Init(sPHI2.x - 4, sPHI2.y + 1, ROT_North, "Clk", "LVC", false, 1000000, false);
	sTest.cCircuit.Add(pcClock);
	sTest.cCircuit.AddTrace(sPHI2.x - 4, sPHI2.y, sPHI2.x, sPHI2.y);

	AssertTrue(sTest.cCircuit.CreateSimulation(&sTest.cSimulation, &sTest.cFamilies));
	sTest.cSimulation.RunToTime(NanosecondsToTime((int64)5000));
	AssertRenderedCircuit(&sTest.cCircuit, &cColours, 820, 820, 1.5, sTest.cSimulation.GetTime(), false, "65C64Running", &cFonts);
	AssertString("RES", pcMPU->GetDetail(C65C64_OpCodeName));
	AssertString("3", pcMPU->GetDetail(C65C64_Cycle));
	AssertString("0x0001ffff", pcMPU->GetDetail(C65C64_Stack));
	AssertString("a8 b8 x8 y8", pcMPU->GetDetail(C65C64_Widths));
	AssertTrue(pcMPU->IsFlagSet(C65C64_EdgeDisable));
	AssertTrue(pcMPU->IsFlagSet(C65C64_LevelDisable));
	AssertFalse(pcMPU->IsFlagSet(C65C64_Carry));

	cColours.Kill();
	KillTestCircuitFonts(&cFonts);
	sTest.Kill(true);
}


//////////////////////////////////////////////////////////////////////////
//
// The new views with Logicim's default properties (top row, matching a
// Logicim render) and with others (bottom row), drawn without a
// simulation.
//
//////////////////////////////////////////////////////////////////////////
void TestWiringRenderViews(void)
{
	CCircuitView		cCircuit;
	CCircuitColours		cColours;
	CCircuitFonts		cFonts;
	CClockView*			pcClock;
	CPositivePowerView*	pcPower;
	CPinView*			pcPin;
	CSplitterView*		pcSplitter;
	CTunnelView*		pcTunnel;
	CLabelView*			pcLabel;
	COscilloscopeView*	pcScope;

	ObjectsInit();
	LoadTestCircuitFonts(&cFonts);
	cColours.InitLogicim();
	cCircuit.Init();

	pcClock = NewMalloc<CClockView>();
	pcClock->Init(-40, -6, ROT_West, "", "LVC", false, 25000000, false);
	cCircuit.Add(pcClock);
	pcPower = NewMalloc<CPositivePowerView>();
	pcPower->Init(-32, -6, ROT_North, "", 3.3f);
	cCircuit.Add(pcPower);
	pcPin = NewMalloc<CPinView>();
	pcPin->Init(-26, -6, ROT_West, "Pin", "LVC", false, 1, RADIX_Binary, &cFonts);
	cCircuit.Add(pcPin);
	pcSplitter = NewMalloc<CSplitterView>();
	pcSplitter->Init(-18, -6, ROT_North, "", 2, 2, 2, SA_LeftHanded, -1);
	cCircuit.Add(pcSplitter);
	pcTunnel = NewMalloc<CTunnelView>();
	pcTunnel->Init(-12, -6, ROT_North, "  ", false, &cFonts);
	cCircuit.Add(pcTunnel);
	pcLabel = NewMalloc<CLabelView>();
	pcLabel->Init(-8, -6, ROT_North, "  ", TA_Left, false, true, true, &cFonts);
	cCircuit.Add(pcLabel);
	pcScope = NewMalloc<COscilloscopeView>();
	pcScope->Init(0, -8, ROT_North, "", "LVC", 2, 32, 30, 4, 6000000000.0);
	cCircuit.Add(pcScope);

	pcClock = NewMalloc<CClockView>();
	pcClock->Init(-42, 8, ROT_West, "", "LVC", false, 25000000, true);
	cCircuit.Add(pcClock);
	pcPower = NewMalloc<CPositivePowerView>();
	pcPower->Init(-38, 8, ROT_North, "", 5.0f);
	cCircuit.Add(pcPower);
	pcPin = NewMalloc<CPinView>();
	pcPin->Init(-22, 8, ROT_West, "Address", "LVC", false, 8, RADIX_Hexadecimal, &cFonts);
	cCircuit.Add(pcPin);
	pcSplitter = NewMalloc<CSplitterView>();
	pcSplitter->Init(-14, 8, ROT_North, "", 8, 3, 2, SA_RightHanded, 1);
	cCircuit.Add(pcSplitter);
	pcTunnel = NewMalloc<CTunnelView>();
	pcTunnel->Init(-2, 8, ROT_West, "Bus", false, &cFonts);
	cCircuit.Add(pcTunnel);
	pcTunnel = NewMalloc<CTunnelView>();
	pcTunnel->Init(0, 12, ROT_East, "Data", true, &cFonts);
	cCircuit.Add(pcTunnel);
	pcLabel = NewMalloc<CLabelView>();
	pcLabel->Init(18, 8, ROT_West, "Centred label", TA_Centre, true, false, true, &cFonts);
	cCircuit.Add(pcLabel);
	pcLabel = NewMalloc<CLabelView>();
	pcLabel->Init(24, 12, ROT_North, "Down", TA_Left, false, false, false, &cFonts);
	cCircuit.Add(pcLabel);

	AssertRenderedCircuit(&cCircuit, &cColours, 900, 340, 1, -1, true, "NewViews", &cFonts);
	cColours.Kill();
	cColours.InitDark();
	AssertRenderedCircuit(&cCircuit, &cColours, 900, 340, 1, -1, true, "NewViewsDark", &cFonts);

	cCircuit.Kill();
	cColours.Kill();
	KillTestCircuitFonts(&cFonts);
	ObjectsFlush();
	ObjectsKill(false);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestWiring(void)
{
	BeginTests();

	DataIOInit();
	DataMemoryInit();

	TestWiringTunnels();
	TestWiringSplitter();
	TestWiringSplitterIndicesAndChains();
	TestWiringPinAndLabel();
	TestWiringClockAndOscilloscope();
	TestWiringW65C816();
	TestWiring65C64();
	TestWiringRenderViews();

	DataMemoryKill();
	DataIOKill();

	TestStatistics();
}
