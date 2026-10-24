#include "BaseLib/ConstructorCall.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/DataMemory.h"
#include "StandardLib/Objects.h"
#include "MicroprocessorLib/CircuitSimulation.h"
#include "MicroprocessorLib/FamilyVoltageConfigurationStore.h"
#include "MicroprocessorLib/Constant.h"
#include "MicroprocessorLib/Counter.h"
#include "MicroprocessorLib/Trace.h"
#include "MicroprocessorLib/Event.h"
#include "MicroprocessorLib/Timeline.h"
#include "LogicimLib/ValueView.h"
#include "LogicimLib/FlipFlopView.h"
#include "LogicimLib/CounterView.h"
#include "LogicimLib/CircuitView.h"
#include "LogicimLib/CircuitFile.h"
#include "TestLib/Assert.h"
#include "TestLogicimRender.h"


#define TEXT_VIEW_FONTS		"Input" _FS_ "Fonts"


//////////////////////////////////////////////////////////////////////////
//
// The fonts rooted, so their glyphs aren't walked for each pointer
// change.
//
//////////////////////////////////////////////////////////////////////////
void LoadTestCircuitFonts(CCircuitFonts* pcFonts)
{
	Ptr<CFontFamily>	pFamily;

	AssertTrue(LoadCircuitFonts(pcFonts, TEXT_VIEW_FONTS, CCO_Unknown));
	pFamily = pcFonts->GetSansSerif();
	ORoot()->Add(pFamily);
	pFamily = pcFonts->GetMonospaced();
	ORoot()->Add(pFamily);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void KillTestCircuitFonts(CCircuitFonts* pcFonts)
{
	pcFonts->Kill();
	ORoot()->RemoveAll();
}


//////////////////////////////////////////////////////////////////////////
//
// Widths are whole pixels at the font size, in grid units.  Java gives the
// same widths for these (Liberation Mono's Xs are Courier New's 0.6 em).
//
//////////////////////////////////////////////////////////////////////////
void TestCircuitFontsMeasure(void)
{
	CCircuitFonts		cFonts;
	SCircuitTextSize	sSize;

	ObjectsInit();
	LoadTestCircuitFonts(&cFonts);

	sSize = cFonts.Measure(CF_Monospaced, 10, "X");
	AssertDouble(0.6, sSize.fWidth, 9);
	sSize = cFonts.Measure(CF_Monospaced, 10, "XXXXXXXX");
	AssertDouble(4.8, sSize.fWidth, 9);
	sSize = cFonts.Measure(CF_Monospaced, 13, "XX");
	AssertDouble(1.6, sSize.fWidth, 9);
	sSize = cFonts.Measure(CF_SansSerif, 10, "XX");
	AssertDouble(1.4, sSize.fWidth, 9);
	sSize = cFonts.Measure(CF_SansSerif, 10, "Up Counter");
	AssertDouble(5.3, sSize.fWidth, 9);
	sSize = cFonts.Measure(CF_SansSerif, 10, "");
	AssertDouble(0.0, sSize.fWidth, 9);
	AssertTrue(sSize.fHeight > 1.0);
	sSize = cFonts.Measure(CF_SansSerifBold, 10, "Clock");
	AssertDouble(2.8, sSize.fWidth, 9);

	KillTestCircuitFonts(&cFonts);
	ObjectsFlush();
	ObjectsKill(false);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertTraceValues(const char* szExpected, const char* szBits, ERadix eRadix)
{
	STraceValue	asValues[RADIX_MAX_BIT_WIDTH];
	int			iBitWidth;
	int			i;
	CChars		sz;

	//szBits is written most significant bit first.
	iBitWidth = (int)strlen(szBits);
	for (i = 0; i < iBitWidth; i++)
	{
		switch (szBits[iBitWidth - 1 - i])
		{
		case '1':
			asValues[i].Init(TV_High);
			break;
		case '0':
			asValues[i].Init(TV_Low);
			break;
		case 'X':
			asValues[i].Init(TV_Unsettled);
			break;
		default:
			asValues[i].Init(TV_Undriven);
			break;
		}
	}
	sz.Init();
	AppendTraceValues(&sz, asValues, iBitWidth, eRadix, CalculateMaxDigits(eRadix, iBitWidth));
	AssertString(szExpected, sz.Text());
	sz.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestRadix(void)
{
	AssertInt(8, CalculateMaxDigits(RADIX_Binary, 8));
	AssertInt(1, CalculateMaxDigits(RADIX_Hexadecimal, 1));
	AssertInt(2, CalculateMaxDigits(RADIX_Hexadecimal, 8));
	AssertInt(3, CalculateMaxDigits(RADIX_Hexadecimal, 9));
	AssertInt(2, CalculateMaxDigits(RADIX_Decimal, 4));
	AssertInt(3, CalculateMaxDigits(RADIX_Decimal, 8));
	AssertInt(5, CalculateMaxDigits(RADIX_Decimal, 16));
	AssertInt(20, CalculateMaxDigits(RADIX_Decimal, 64));
	AssertInt(1, CalculateMaxDigits(RADIX_Decimal, 1));

	AssertTraceValues("10100101", "10100101", RADIX_Binary);
	AssertTraceValues("1X.0", "1X.0", RADIX_Binary);
	AssertTraceValues("A5", "10100101", RADIX_Hexadecimal);
	AssertTraceValues("1A5", "110100101", RADIX_Hexadecimal);
	AssertTraceValues(".5", "1.100101", RADIX_Hexadecimal);
	AssertTraceValues("X5", "X01.0101", RADIX_Hexadecimal);
	AssertTraceValues("165", "10100101", RADIX_Decimal);
	AssertTraceValues("0", "0000", RADIX_Decimal);
	AssertTraceValues("...", "1010.101", RADIX_Decimal);
	AssertTraceValues("XXX", "1010X101", RADIX_Decimal);
	AssertTraceValues("18446744073709551615", "1111111111111111111111111111111111111111111111111111111111111111", RADIX_Decimal);

	AssertString("hexadecimal", RadixToString(RADIX_Hexadecimal));
	AssertInt(RADIX_Binary, StringToRadix("binary"));
	AssertInt(RADIX_Decimal, StringToRadix("decimal"));
	AssertInt(RADIX_Cannot, StringToRadix("octal"));
	AssertInt(RADIX_Cannot, StringToRadix(NULL));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertValueBox(int32 iLeft, int32 iTop, int32 iRight, int32 iBottom, CValueView* pcView)
{
	SInt32Vec2	sMinimum;
	SInt32Vec2	sMaximum;

	pcView->GetBox(&sMinimum, &sMaximum);
	AssertInt(iLeft, sMinimum.x);
	AssertInt(iTop, sMinimum.y);
	AssertInt(iRight, sMaximum.x);
	AssertInt(iBottom, sMaximum.y);
}


//////////////////////////////////////////////////////////////////////////
//
// A new constant or probe is as long as its widest value and half a grid
// unit, rounded up, as Logicim's.
//
//////////////////////////////////////////////////////////////////////////
void TestValueViewMeasuredBox(void)
{
	CCircuitFonts	cFonts;
	CConstantView	cConstant;
	CProbeView		cProbe;
	SFloat64Vec2	sMinimum;
	SFloat64Vec2	sMaximum;

	ObjectsInit();
	LoadTestCircuitFonts(&cFonts);

	//One hexadecimal digit: 0.6 + 0.5 is 2.
	cConstant.Init(0, 0, ROT_North, "", "LVC", false, 1, RADIX_Hexadecimal, &cFonts);
	AssertValueBox(-1, 0, 1, 2, &cConstant);
	AssertTrue(cConstant.GetLocalBounds(&sMinimum, &sMaximum));
	AssertDouble(-1.0, sMinimum.x, 9);
	AssertDouble(0.0, sMinimum.y, 9);
	AssertDouble(1.0, sMaximum.x, 9);
	AssertDouble(2.0, sMaximum.y, 9);
	cConstant.Kill();

	//Eight digits: 4.8 + 0.5 is 6.
	cConstant.Init(0, 0, ROT_North, "", "LVC", false, 8, RADIX_Binary, &cFonts);
	AssertValueBox(-1, 0, 1, 6, &cConstant);
	cConstant.Kill();
	cConstant.Init(0, 0, ROT_North, "", "LVC", false, 32, RADIX_Hexadecimal, &cFonts);
	AssertValueBox(-1, 0, 1, 6, &cConstant);
	cConstant.Kill();

	//65535: 3.0 + 0.5 is 4.
	cProbe.Init(0, 0, ROT_North, "", "LVC", false, 16, RADIX_Decimal, &cFonts);
	AssertValueBox(-1, 0, 1, 4, &cProbe);
	AssertSize(1, cProbe.NumPortViews());
	AssertSize(16, cProbe.GetPortView((size)0)->NumPortNames());
	AssertString("Input 15", cProbe.GetPortView((size)0)->GetPortName(15));
	cProbe.Kill();

	cProbe.Init(0, 0, ROT_North, "", "LVC", true, 1, RADIX_Binary, &cFonts);
	AssertValueBox(-1, 0, 1, 2, &cProbe);
	AssertSize(3, cProbe.NumPortViews());
	AssertInt(-1, cProbe.GetPortView("VCC")->GetRelativePosition().x);
	AssertInt(1, cProbe.GetPortView("VCC")->GetRelativePosition().y);
	AssertInt(1, cProbe.GetPortView("GND")->GetRelativePosition().x);
	cProbe.Kill();

	KillTestCircuitFonts(&cFonts);
	ObjectsFlush();
	ObjectsKill(false);
}


//////////////////////////////////////////////////////////////////////////
//
// The box is saved and loaded, not measured again, so a constant keeps its
// size whatever fonts are about (here none).
//
//////////////////////////////////////////////////////////////////////////
void TestValueViewBoxKept(void)
{
	CCircuitFonts	cFonts;
	CCircuitView	cSaved;
	CCircuitView	cLoaded;
	CConstantView*	pcConstant;
	CXMLWriter		cWriter;
	CFileUtil		cFileUtil;
	char			szExpected[] = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<Logicim version=\"1\">\n\
  <Circuit>\n\
    <Constant name=\"K\" x=\"3\" y=\"4\" rotation=\"West\" family=\"LVC\" explicitPowerPorts=\"false\" bitWidth=\"8\" radix=\"binary\" left=\"-1\" top=\"0\" right=\"1\" bottom=\"6\"/>\n\
  </Circuit>\n\
</Logicim>\n";

	ObjectsInit();
	LoadTestCircuitFonts(&cFonts);
	cSaved.Init();
	pcConstant = NewMalloc<CConstantView>();
	pcConstant->Init(3, 4, ROT_West, "K", "LVC", false, 8, RADIX_Binary, &cFonts);
	cSaved.Add(pcConstant);
	cWriter.Init();
	SaveCircuitXML(&cSaved, &cWriter);
	AssertString(szExpected, cWriter.GetText());
	cWriter.Kill();
	cFileUtil.MakeDir("Output");
	AssertTrue(SaveCircuitFile(&cSaved, "Output" _FS_ "Constant.xml"));
	cSaved.Kill();
	KillTestCircuitFonts(&cFonts);
	ObjectsFlush();
	ObjectsKill(false);

	cLoaded.Init();
	AssertTrue(LoadCircuitFile(&cLoaded, "Output" _FS_ "Constant.xml"));
	AssertSize(1, cLoaded.NumComponents());
	pcConstant = (CConstantView*)cLoaded.GetComponent(0);
	AssertString("Constant", pcConstant->GetType());
	AssertInt(8, pcConstant->GetBitWidth());
	AssertInt(RADIX_Binary, pcConstant->GetRadix());
	AssertValueBox(-1, 0, 1, 6, pcConstant);
	cLoaded.Kill();
	cFileUtil.Delete("Output" _FS_ "Constant.xml");
	cFileUtil.RemoveDir("Output");
}


//////////////////////////////////////////////////////////////////////////
//
// A clock port has a notch on the box's edge pointing in; other ports
// don't.
//
//////////////////////////////////////////////////////////////////////////
void TestClockNotch(void)
{
	CDTypeFlipFlopView	cFlipFlop;
	CCounterView		cCounter;
	SFloat64Vec2*		asNotch;

	cFlipFlop.Init(0, 0, ROT_North, "", "LVC", false);
	AssertTrue(cFlipFlop.GetPortView("CP")->IsClock());
	AssertFalse(cFlipFlop.GetPortView("D")->IsClock());
	asNotch = cFlipFlop.GetPortView("CP")->GetClockNotch();
	AssertDouble(-2.5, asNotch[0].x, 9);
	AssertDouble(3.0, asNotch[0].y, 9);
	AssertDouble(-3.0, asNotch[1].x, 9);
	AssertDouble(2.5, asNotch[1].y, 9);
	AssertDouble(-3.5, asNotch[2].x, 9);
	AssertDouble(3.0, asNotch[2].y, 9);
	cFlipFlop.Kill();

	cCounter.Init(0, 0, ROT_North, "", "LVC", false, 4, 15);
	AssertTrue(cCounter.GetPortView("Clock")->IsClock());
	asNotch = cCounter.GetPortView("Clock")->GetClockNotch();
	AssertDouble(-6.0, asNotch[1].x, 9);
	AssertDouble(5.5, asNotch[1].y, 9);
	cCounter.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void SetConstant(CConstantView* pcView, int64 iValue, CViewPath* pcViewPath, CCircuitSimulation* pcSimulation)
{
	CConstant*	pcConstant;

	pcConstant = (CConstant*)pcView->GetComponent(pcViewPath, pcSimulation);
	pcConstant->SetConstantValue(iValue);
	pcConstant->SimulationStarted(pcSimulation->GetTimeline());
}


//////////////////////////////////////////////////////////////////////////
//
// Text read across and, on components facing North or South, down.
// Values are read from the running simulation.
//
//////////////////////////////////////////////////////////////////////////
void TestTextViewsRender(void)
{
	CFamilyVoltageConfigurationStore	cFamilies;
	CCircuitSimulation					cSimulation;
	CCircuitView						cCircuit;
	CViewPaths							cPaths;
	CViewPath*							pcPath;
	CCircuitColours						cColours;
	CCircuitFonts						cFonts;
	CConstantView*						pcConstant8;
	CConstantView*						pcConstant1;
	CConstantView*						pcConstantNorth;
	CProbeView*							pcProbe8;
	CProbeView*							pcProbe1;
	CProbeView*							pcProbeSouth;
	CDTypeFlipFlopView*					pcFlipFlop;
	CCounterView*						pcCounter;
	CChars								szValue;

	ObjectsInit();
	CEvent::ResetNextID();
	CTrace::ResetNextID();
	LoadTestCircuitFonts(&cFonts);
	cFamilies.Init();
	AssertTrue(cFamilies.Load("Input" _FS_ "PropagationTimes.csv"));
	cSimulation.Init("Text");
	cCircuit.Init();
	cPaths.Init();
	pcPath = cPaths.AddTop(&cCircuit);
	cColours.InitLogicim();

	pcConstant8 = NewMalloc<CConstantView>();
	pcConstant8->Init(-38, -8, ROT_West, "", "LVC", false, 8, RADIX_Hexadecimal, &cFonts);
	cCircuit.Add(pcConstant8);
	pcProbe8 = NewMalloc<CProbeView>();
	pcProbe8->Init(-24, -8, ROT_East, "", "LVC", false, 8, RADIX_Hexadecimal, &cFonts);
	cCircuit.Add(pcProbe8);
	cCircuit.AddTrace(-38, -8, -24, -8);

	pcConstant1 = NewMalloc<CConstantView>();
	pcConstant1->Init(-38, 0, ROT_West, "", "LVC", false, 1, RADIX_Binary, &cFonts);
	cCircuit.Add(pcConstant1);
	pcProbe1 = NewMalloc<CProbeView>();
	pcProbe1->Init(-28, 0, ROT_East, "", "LVC", false, 1, RADIX_Binary, &cFonts);
	cCircuit.Add(pcProbe1);
	cCircuit.AddTrace(-38, 0, -28, 0);

	pcConstantNorth = NewMalloc<CConstantView>();
	pcConstantNorth->Init(-14, -9, ROT_North, "", "LVC", false, 16, RADIX_Decimal, &cFonts);
	cCircuit.Add(pcConstantNorth);
	pcProbeSouth = NewMalloc<CProbeView>();
	pcProbeSouth->Init(-14, 8, ROT_South, "", "LVC", false, 4, RADIX_Binary, &cFonts);
	cCircuit.Add(pcProbeSouth);

	pcFlipFlop = NewMalloc<CDTypeFlipFlopView>();
	pcFlipFlop->Init(-2, 0, ROT_West, "", "LVC", false);
	cCircuit.Add(pcFlipFlop);
	pcFlipFlop = NewMalloc<CDTypeFlipFlopView>();
	pcFlipFlop->Init(11, 0, ROT_North, "", "LVC", false);
	cCircuit.Add(pcFlipFlop);
	pcCounter = NewMalloc<CCounterView>();
	pcCounter->Init(31, 0, ROT_West, "", "LVC", false, 4, 15);
	cCircuit.Add(pcCounter);

	//Starting resets the constants to 0, so their values are set after and driven again.
	AssertTrue(cCircuit.CreateSimulation(pcPath, &cSimulation, &cFamilies));
	SetConstant(pcConstant8, 0xA5, pcPath, &cSimulation);
	SetConstant(pcConstant1, 1, pcPath, &cSimulation);
	SetConstant(pcConstantNorth, 1234, pcPath, &cSimulation);
	((CCounter*)pcCounter->GetComponent(pcPath, &cSimulation))->SetCount(0xC);
	cSimulation.GetTimeline()->Run();

	szValue.Init();
	pcProbe8->GetValueText(&szValue, pcPath, &cSimulation);
	AssertString("A5", szValue.Text());
	szValue.ReInit();
	pcProbe1->GetValueText(&szValue, pcPath, &cSimulation);
	AssertString("1", szValue.Text());
	szValue.ReInit();
	//Without a wire there's no trace to read (as Logicim).
	pcConstantNorth->GetValueText(&szValue, pcPath, &cSimulation);
	AssertString(".....", szValue.Text());
	szValue.ReInit();
	pcProbeSouth->GetValueText(&szValue, pcPath, &cSimulation);
	AssertString("....", szValue.Text());
	szValue.ReInit();
	pcProbe8->GetValueText(&szValue, NULL, NULL);
	AssertString("", szValue.Text());
	szValue.Kill();

	AssertRenderedCircuit(&cCircuit, &cColours, 1400, 340, 1.5, pcPath, &cSimulation, true, "TextViews", &cFonts);
	cColours.Kill();
	cColours.InitDark();
	AssertRenderedCircuit(&cCircuit, &cColours, 1400, 340, 1.5, pcPath, &cSimulation, true, "TextViewsDark", &cFonts);
	AssertRenderedCircuit(&cCircuit, &cColours, 700, 170, 0.75, pcPath, &cSimulation, false, "TextViewsSmall", &cFonts);

	cCircuit.Kill();
	cPaths.Kill();
	cSimulation.Kill();
	cFamilies.Kill();
	cColours.Kill();
	KillTestCircuitFonts(&cFonts);
	ObjectsFlush();
	ObjectsKill(false);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTextViews(void)
{
	BeginTests();

	DataIOInit();
	DataMemoryInit();

	TestCircuitFontsMeasure();
	TestRadix();
	TestValueViewMeasuredBox();
	TestValueViewBoxKept();
	TestClockNotch();
	TestTextViewsRender();

	DataMemoryKill();
	DataIOKill();

	TestStatistics();
}
