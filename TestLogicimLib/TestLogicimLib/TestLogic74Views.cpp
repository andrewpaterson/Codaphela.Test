#include "BaseLib/ConstructorCall.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/DataMemory.h"
#include "BaseLib/FileUtil.h"
#include "StandardLib/Objects.h"
#include "MicroprocessorLib/CircuitSimulation.h"
#include "MicroprocessorLib/FamilyVoltageConfigurationStore.h"
#include "MicroprocessorLib/PowerSource.h"
#include "MicroprocessorLib/Trace.h"
#include "MicroprocessorLib/Event.h"
#include "MicroprocessorLib/Timeline.h"
#include "LogicimLib/Logic74View.h"
#include "LogicimLib/ComponentViewFactory.h"
#include "LogicimLib/CircuitView.h"
#include "LogicimLib/CircuitFile.h"
#include "LogicimLib/CircuitColours.h"
#include "TestLib/Assert.h"
#include "TestLogicimRender.h"


void LoadTestCircuitFonts(CCircuitFonts* pcFonts);
void KillTestCircuitFonts(CCircuitFonts* pcFonts);
void AssertGridPosition(int32 x, int32 y, CPortView* pcPortView);


//////////////////////////////////////////////////////////////////////////
//
// Part types are found by their row, a small logic part by the type after
// its G with the count before it.
//
//////////////////////////////////////////////////////////////////////////
void TestLogic74Parts(void)
{
	SLogic74PartType	sType;
	CChars				sz;

	AssertTrue(FindLogic74Part(&sType, "00"));
	AssertString("00", sType.psPart->szPartType);
	AssertInt(GF_Nand, sType.psPart->eGateFunction);
	AssertInt(4, sType.iUnitCount);
	AssertInt(2, sType.psPart->iInputCount);
	sz.Init();
	GetLogic74Description(&sz, &sType);
	AssertString("Quad 2-Input NAND", sz.Text());
	sz.Kill();

	AssertTrue(FindLogic74Part(&sType, "2G04"));
	AssertString("04", sType.psPart->szPartType);
	AssertInt(2, sType.iUnitCount);
	sz.Init();
	GetLogic74Description(&sz, &sType);
	AssertString("Dual Inverter", sz.Text());
	sz.Kill();

	AssertTrue(FindLogic74Part(&sType, "1G332"));
	AssertInt(GF_Or, sType.psPart->eGateFunction);
	AssertInt(1, sType.iUnitCount);
	AssertInt(3, sType.psPart->iInputCount);

	AssertTrue(FindLogic74Part(&sType, "14"));
	sz.Init();
	GetLogic74Description(&sz, &sType);
	AssertString("Hex Schmitt Inverter", sz.Text());
	sz.Kill();

	AssertFalse(FindLogic74Part(&sType, "9999"));
	AssertNull(sType.psPart);
	AssertFalse(FindLogic74Part(&sType, ""));
	AssertFalse(FindLogic74Part(&sType, NULL));

	sz.Init();
	GetLogic74PartNumber(&sz, "HCT", "00");
	AssertString("74HCT00", sz.Text());
	sz.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// A quad NAND's gates are four grid units apart in a box, their inputs out
// at -5 and their outputs out at 6.  An inverter part's are two apart.
//
//////////////////////////////////////////////////////////////////////////
void TestLogic74PackageViewGeometry(void)
{
	CLogic74PackageView*	pcPackage;
	CChars					sz;
	SFloat64Vec2			sMinimum;
	SFloat64Vec2			sMaximum;

	pcPackage = NewMalloc<CLogic74PackageView>();
	pcPackage->Init(0, 0, ROT_East, "U5", "LVC", false, "00");
	AssertString("74 Series Package", pcPackage->GetType());
	AssertString("Logic74Package", pcPackage->GetXMLName());
	sz.Init();
	pcPackage->GetDescription(&sz);
	AssertString("Quad 2-Input NAND", sz.Text());
	sz.Kill();
	sz.Init();
	pcPackage->GetPartNumber(&sz);
	AssertString("74LVC00", sz.Text());
	sz.Kill();
	AssertInt(4, pcPackage->GetUnitCount());
	AssertSize(12, pcPackage->NumPortViews());
	AssertGridPosition(-5, -7, pcPackage->GetPortView("1A"));
	AssertGridPosition(-5, -5, pcPackage->GetPortView("1B"));
	AssertGridPosition(6, -6, pcPackage->GetPortView("1Y"));
	AssertGridPosition(-5, 7, pcPackage->GetPortView("4B"));
	AssertGridPosition(6, 6, pcPackage->GetPortView("4Y"));
	AssertNull(pcPackage->GetPortView("5A"));
	AssertTrue(pcPackage->GetLocalBounds(&sMinimum, &sMaximum));
	AssertDouble(-5, sMinimum.x, 6);
	AssertDouble(-10, sMinimum.y, 6);
	AssertDouble(6, sMaximum.x, 6);
	AssertDouble(10, sMaximum.y, 6);
	pcPackage->Kill();

	pcPackage = NewMalloc<CLogic74PackageView>();
	pcPackage->Init(0, 0, ROT_East, "U6", "LVC", false, "04");
	AssertSize(12, pcPackage->NumPortViews());
	AssertGridPosition(-5, -5, pcPackage->GetPortView("1A"));
	AssertGridPosition(6, -5, pcPackage->GetPortView("1Y"));
	AssertGridPosition(-5, 5, pcPackage->GetPortView("6A"));
	AssertTrue(pcPackage->GetLocalBounds(&sMinimum, &sMaximum));
	AssertDouble(-8, sMinimum.y, 6);
	AssertDouble(8, sMaximum.y, 6);
	pcPackage->Kill();

	pcPackage = NewMalloc<CLogic74PackageView>();
	pcPackage->Init(0, 0, ROT_East, "U7", "LVC", false, "86");
	AssertGridPosition(-5, -7, pcPackage->GetPortView("1A"));
	AssertGridPosition(6, 6, pcPackage->GetPortView("4Y"));
	pcPackage->Kill();

	//A part with no row is an empty box.
	pcPackage = NewMalloc<CLogic74PackageView>();
	pcPackage->Init(0, 0, ROT_East, "U8", "LVC", false, "9999");
	AssertNull(pcPackage->GetPart());
	AssertSize(0, pcPackage->NumPortViews());
	pcPackage->Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// A unit is drawn and ported as the generic gate is, and goes on to the
// part's next unit until its last.
//
//////////////////////////////////////////////////////////////////////////
void TestLogic74UnitViewGeometry(void)
{
	CLogic74UnitView*	pcUnit;
	CComponentView*		pcNext;
	int					i;

	pcUnit = NewMalloc<CLogic74UnitView>();
	pcUnit->Init(10, 4, ROT_East, "U5", "LVC", false, "00", 2);
	AssertString("74 Series Unit", pcUnit->GetType());
	AssertString("Logic74Unit", pcUnit->GetXMLName());
	AssertInt(2, pcUnit->GetUnit());
	AssertChar('C', pcUnit->GetUnitLetter());
	AssertString("00", pcUnit->GetPartType());
	AssertInt(4, pcUnit->GetUnitCount());
	AssertSize(3, pcUnit->NumPortViews());
	AssertGridPosition(9, 3, pcUnit->GetPortView("Input 0"));
	AssertGridPosition(9, 5, pcUnit->GetPortView("Input 1"));
	AssertGridPosition(13, 4, pcUnit->GetPortView("Output"));
	AssertTrue(pcUnit->GetPortView("Output")->IsInverting());

	pcNext = pcUnit->NewNextUnit();
	AssertNotNull(pcNext);
	AssertChar('D', ((CLogic74UnitView*)pcNext)->GetUnitLetter());
	AssertString("U5", pcNext->GetName());
	AssertNull(pcNext->NewNextUnit());
	pcNext->Kill();
	pcUnit->Kill();

	//An inverter unit is a triangle with a bubble.
	pcUnit = NewMalloc<CLogic74UnitView>();
	pcUnit->Init(10, 4, ROT_East, "U6", "LVC", false, "04", 0);
	AssertSize(2, pcUnit->NumPortViews());
	AssertGridPosition(9, 4, pcUnit->GetPortView("Input"));
	AssertGridPosition(12, 4, pcUnit->GetPortView("Output"));
	AssertTrue(pcUnit->GetPortView("Output")->IsInverting());
	AssertInt(6, pcUnit->GetUnitCount());
	for (i = 0; i < 5; i++)
	{
		pcNext = pcUnit->NewNextUnit();
		AssertNotNull(pcNext);
		pcUnit->Kill();
		pcUnit = (CLogic74UnitView*)pcNext;
	}
	AssertChar('F', pcUnit->GetUnitLetter());
	AssertNull(pcUnit->NewNextUnit());
	pcUnit->Kill();

	//An exclusive OR's inputs are a grid unit further back.
	pcUnit = NewMalloc<CLogic74UnitView>();
	pcUnit->Init(0, 0, ROT_East, "U7", "LVC", false, "2G86", 1);
	AssertInt(2, pcUnit->GetUnitCount());
	AssertGridPosition(-2, -1, pcUnit->GetPortView("Input 0"));
	AssertGridPosition(2, 0, pcUnit->GetPortView("Output"));
	AssertFalse(pcUnit->GetPortView("Output")->IsInverting());
	pcUnit->Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// A package and its units placed apart, saved and loaded back.
//
//////////////////////////////////////////////////////////////////////////
void TestLogic74ViewsFile(void)
{
	CCircuitView			cSaved;
	CCircuitView			cLoaded;
	CLogic74PackageView*	pcPackage;
	CLogic74UnitView*		pcUnit;
	CFileUtil				cFileUtil;
	int						i;

	cSaved.Init();
	pcPackage = NewMalloc<CLogic74PackageView>();
	pcPackage->Init(0, 0, ROT_West, "U5", "HCT", false, "14");
	cSaved.Add(pcPackage);
	for (i = 0; i < 4; i++)
	{
		pcUnit = NewMalloc<CLogic74UnitView>();
		pcUnit->Init(20, 6 * i, ROT_East, "U6", "LVC", false, "08", i);
		cSaved.Add(pcUnit);
	}

	cFileUtil.MakeDir("Output");
	AssertTrue(SaveCircuitFile(&cSaved, "Output" _FS_ "Logic74Parts.xml"));
	cLoaded.Init();
	AssertTrue(LoadCircuitFile(&cLoaded, "Output" _FS_ "Logic74Parts.xml"));
	AssertSize(5, cLoaded.NumComponents());

	pcPackage = (CLogic74PackageView*)cLoaded.GetComponent(0);
	AssertString("74 Series Package", pcPackage->GetType());
	AssertString("14", pcPackage->GetPartType());
	AssertString("HCT", pcPackage->GetFamily());
	AssertInt(6, pcPackage->GetUnitCount());
	AssertInt(ROT_West, pcPackage->GetRotation());
	AssertString("U5", pcPackage->GetName());
	for (i = 0; i < 4; i++)
	{
		pcUnit = (CLogic74UnitView*)cLoaded.GetComponent(1 + i);
		AssertString("74 Series Unit", pcUnit->GetType());
		AssertInt(i, pcUnit->GetUnit());
		AssertString("08", pcUnit->GetPartType());
		AssertInt(6 * i, pcUnit->GetPosition().y);
	}
	cLoaded.Kill();
	cSaved.Kill();
	cFileUtil.Delete("Output" _FS_ "Logic74Parts.xml");
}


//////////////////////////////////////////////////////////////////////////
//
// Each of a quad NAND's gates follows its own inputs: a supply on 2A and
// 2B drives 2Y low and leaves the others' outputs as they were.  A NAND
// unit with one input high and the other unwired drives nothing.
//
//////////////////////////////////////////////////////////////////////////
void TestLogic74ViewsSimulation(void)
{
	CFamilyVoltageConfigurationStore	cFamilies;
	CFamilyVoltageConfiguration*		pcFamily;
	CCircuitSimulation					cSimulation;
	CCircuitView						cCircuit;
	CViewPaths							cPaths;
	CViewPath*							pcPath;
	CLogic74PackageView*				pcPackage;
	CLogic74UnitView*					pcUnit;
	CTraceView*							pcIn;
	CTraceView*							pcOut;
	CTraceView*							pcOther;
	CTraceView*							pcUnitOut;
	CPowerSource*						pcSupply;
	float32								fVcc;

	ObjectsInit();
	CEvent::ResetNextID();
	CTrace::ResetNextID();
	cFamilies.Init();
	AssertTrue(cFamilies.Load("Input" _FS_ "PropagationTimes.csv"));
	pcFamily = cFamilies.Get("LVC");
	fVcc = pcFamily->GetDefaultVoltageConfiguration(DEFAULT_LOGIC_LEVEL)->GetVcc();
	cSimulation.Init("Logic 74 Parts");
	cCircuit.Init();
	cPaths.Init();
	pcPath = cPaths.AddTop(&cCircuit);

	//2A at (-5, -3) and 2B at (-5, -1) both on the input trace.
	pcPackage = NewMalloc<CLogic74PackageView>();
	pcPackage->Init(0, 0, ROT_East, "U5", "LVC", false, "00");
	cCircuit.Add(pcPackage);
	pcIn = cCircuit.AddTrace(-10, -3, -5, -3);
	cCircuit.AddTrace(-8, -3, -8, -1);
	cCircuit.AddTrace(-8, -1, -5, -1);
	pcOut = cCircuit.AddTrace(6, -2, 10, -2);
	pcOther = cCircuit.AddTrace(6, 2, 10, 2);

	pcUnit = NewMalloc<CLogic74UnitView>();
	pcUnit->Init(20, 0, ROT_East, "U6", "LVC", false, "00", 0);
	cCircuit.Add(pcUnit);
	cCircuit.AddTrace(-10, -3, -10, -12);
	cCircuit.AddTrace(-10, -12, 15, -12);
	cCircuit.AddTrace(15, -12, 15, -1);
	cCircuit.AddTrace(15, -1, 19, -1);
	pcUnitOut = cCircuit.AddTrace(23, 0, 26, 0);

	AssertTrue(cCircuit.CreateSimulation(pcPath, &cSimulation, &cFamilies));
	AssertTrue(pcPackage->GetPortView("2A")->GetPort(pcPath, &cSimulation, 0)->GetTrace() == pcIn->GetTrace(pcPath, &cSimulation, 0));
	AssertTrue(pcPackage->GetPortView("2B")->GetPort(pcPath, &cSimulation, 0)->GetTrace() == pcIn->GetTrace(pcPath, &cSimulation, 0));
	AssertTrue(pcPackage->GetPortView("2Y")->GetPort(pcPath, &cSimulation, 0)->GetTrace() == pcOut->GetTrace(pcPath, &cSimulation, 0));
	AssertTrue(pcUnit->GetPortView("Input 0")->GetPort(pcPath, &cSimulation, 0)->GetTrace() == pcIn->GetTrace(pcPath, &cSimulation, 0));

	pcSupply = &OMalloc<CPowerSource>(cSimulation.GetSubcircuitTopSimulation(), "Supply", fVcc);
	AssertTrue(pcSupply->GetPowerOutPort()->ConnectLive(pcIn->GetTrace(pcPath, &cSimulation, 0), cSimulation.GetTimeline()));
	cSimulation.GetTimeline()->Run();
	AssertInt(TV_High, pcFamily->GetValue(pcIn->GetTrace(pcPath, &cSimulation, 0)->GetVoltage(cSimulation.GetTime()), fVcc));
	AssertInt(TV_Low, pcFamily->GetValue(pcOut->GetTrace(pcPath, &cSimulation, 0)->GetVoltage(cSimulation.GetTime()), fVcc));
	AssertTrue(pcFamily->GetValue(pcOther->GetTrace(pcPath, &cSimulation, 0)->GetVoltage(cSimulation.GetTime()), fVcc) != TV_Low);
	AssertTrue(pcFamily->GetValue(pcUnitOut->GetTrace(pcPath, &cSimulation, 0)->GetVoltage(cSimulation.GetTime()), fVcc) != TV_Low);

	cCircuit.Kill();
	cPaths.Kill();
	cSimulation.Kill();
	cFamilies.Kill();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
// Gate parts as blocks, and a NAND part's and an inverter part's units
// placed apart.
//
//////////////////////////////////////////////////////////////////////////
void TestLogic74ViewsRender(void)
{
	CCircuitView			cCircuit;
	CCircuitColours			cColours;
	CCircuitFonts			cFonts;
	CLogic74PackageView*	pcPackage;
	CLogic74UnitView*		pcUnit;
	int						i;
	const char*				aszPackages[] = { "00", "04", "86", "11", "20" };

	ObjectsInit();
	LoadTestCircuitFonts(&cFonts);
	cColours.InitLogicim();
	cCircuit.Init();

	for (i = 0; i < 5; i++)
	{
		pcPackage = NewMalloc<CLogic74PackageView>();
		pcPackage->Init(-26 + 13 * i, -5, ROT_East, "U5", "LVC", false, aszPackages[i]);
		cCircuit.Add(pcPackage);
	}
	for (i = 0; i < 4; i++)
	{
		pcUnit = NewMalloc<CLogic74UnitView>();
		pcUnit->Init(-24 + 7 * i, 12, ROT_East, "U6", "LVC", false, "00", i);
		cCircuit.Add(pcUnit);
	}
	for (i = 0; i < 4; i++)
	{
		pcUnit = NewMalloc<CLogic74UnitView>();
		pcUnit->Init(6 + 7 * i, 12, ROT_East, "U7", "LVC", false, i < 2 ? "32" : "02", i);
		cCircuit.Add(pcUnit);
	}
	AssertRenderedCircuit(&cCircuit, &cColours, 1440, 720, 2, NULL, NULL, true, "Logic74Parts", &cFonts);

	cCircuit.Kill();
	KillTestCircuitFonts(&cFonts);
	ObjectsFlush();
	ObjectsKill(false);
}


//////////////////////////////////////////////////////////////////////////
//
// The generic blocks at their placed sizes, and the real parts made from
// them, labelled as their parts are.
//
//////////////////////////////////////////////////////////////////////////
void TestLogic74BlocksRender(void)
{
	CCircuitView			cCircuit;
	CCircuitColours			cColours;
	CCircuitFonts			cFonts;
	CLogicBlockView*		pcBlock;
	CLogic74PackageView*	pcPackage;
	CLogic74UnitView*		pcUnit;
	SLogicBlockParams		sParams;
	int						i;
	const char*				aszBlocks[] = { "Register", "Latch", "BusBuffer", "BusTransceiver", "Multiplexer", "Decoder", "Adder", "Comparator" };
	const char*				aszPackages[] = { "574", "16373", "244", "541", "125", "245", "157", "3253", "138", "283", "521", "161", "74" };
	ELogicBlockKind			eKind;

	ObjectsInit();
	LoadTestCircuitFonts(&cFonts);
	cColours.InitLogicim();
	cCircuit.Init();

	for (i = 0; i < 8; i++)
	{
		AssertTrue(CLogicBlockView::FindKind(aszBlocks[i], &eKind));
		CLogicBlockView::GetDefaultParams(eKind, &sParams);
		pcBlock = (CLogicBlockView*)NewComponentView(aszBlocks[i]);
		pcBlock->Init(-60 + 15 * i, -36, ROT_East, "U1", "LVC", false, eKind, &sParams);
		AssertString(aszBlocks[i], pcBlock->GetXMLName());
		cCircuit.Add(pcBlock);
	}
	for (i = 0; i < 13; i++)
	{
		pcPackage = NewMalloc<CLogic74PackageView>();
		pcPackage->Init(-60 + 15 * (i % 9), -2 + 36 * (i / 9), ROT_East, "U2", "LVC", false, aszPackages[i]);
		AssertNotNull(pcPackage->GetPart());
		cCircuit.Add(pcPackage);
	}
	for (i = 0; i < 2; i++)
	{
		pcUnit = NewMalloc<CLogic74UnitView>();
		pcUnit->Init(5 + 10 * i, 34, ROT_East, "U3", "LVC", false, "74", i);
		cCircuit.Add(pcUnit);
	}
	AssertRenderedCircuit(&cCircuit, &cColours, 2800, 2200, 2, NULL, NULL, true, "Logic74Blocks", &cFonts);

	cCircuit.Kill();
	KillTestCircuitFonts(&cFonts);
	ObjectsFlush();
	ObjectsKill(false);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestLogic74Views(void)
{
	BeginTests();
	DataIOInit();
	DataMemoryInit();

	TestLogic74Parts();
	TestLogic74PackageViewGeometry();
	TestLogic74UnitViewGeometry();
	TestLogic74ViewsFile();
	TestLogic74ViewsSimulation();
	TestLogic74ViewsRender();
	TestLogic74BlocksRender();

	DataMemoryKill();
	DataIOKill();
	TestStatistics();
}

