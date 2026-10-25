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
#include "LogicimLib/InverterPackageView.h"
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
// Six inverters two grid units apart in a box, inputs out at -5 and
// outputs out at 6.
//
//////////////////////////////////////////////////////////////////////////
void TestInverterPackageViewGeometry(void)
{
	CInverterPackageView*	pcPackage;
	CChars					sz;
	SFloat64Vec2			sMinimum;
	SFloat64Vec2			sMaximum;

	pcPackage = NewMalloc<CInverterPackageView>();
	pcPackage->Init(0, 0, ROT_East, "U5", "LVC", false, "04", 6);
	AssertString("Inverter Package", pcPackage->GetType());
	AssertString("InverterPackage", pcPackage->GetXMLName());
	AssertString("Hex Inverter", pcPackage->GetDescription());
	sz.Init();
	pcPackage->GetPartNumber(&sz);
	AssertString("74LVC04", sz.Text());
	sz.Kill();
	AssertInt(6, pcPackage->GetUnitCount());
	AssertSize(12, pcPackage->NumPortViews());
	AssertGridPosition(-5, -5, pcPackage->GetPortView("Input 0"));
	AssertGridPosition(-5, 5, pcPackage->GetPortView("Input 5"));
	AssertGridPosition(6, -5, pcPackage->GetPortView("Output 0"));
	AssertGridPosition(6, 1, pcPackage->GetPortView("Output 3"));
	AssertTrue(pcPackage->GetUnitInput(3) == pcPackage->GetPortView("Input 3"));
	AssertTrue(pcPackage->GetUnitOutput(5) == pcPackage->GetPortView("Output 5"));
	AssertNull(pcPackage->GetUnitInput(6));
	AssertTrue(pcPackage->GetLocalBounds(&sMinimum, &sMaximum));
	AssertDouble(-5, sMinimum.x, 6);
	AssertDouble(-8, sMinimum.y, 6);
	AssertDouble(6, sMaximum.x, 6);
	AssertDouble(8, sMaximum.y, 6);

	pcPackage->SetRotation(ROT_South);
	AssertGridPosition(5, -5, pcPackage->GetPortView("Input 0"));
	SafeKill(pcPackage);

	pcPackage = NewMalloc<CInverterPackageView>();
	pcPackage->Init(0, 0, ROT_East, "", "HCT", true, "14", 6);
	AssertString("Hex Schmitt Inverter", pcPackage->GetDescription());
	AssertSize(14, pcPackage->NumPortViews());
	AssertTrue(pcPackage->GetUnitInput(0) == pcPackage->GetPortView("Input 0"));
	SafeKill(pcPackage);

	pcPackage = NewMalloc<CInverterPackageView>();
	pcPackage->Init(0, 0, ROT_East, "", "LVC", false, "1G04", 1, "My inverter");
	AssertString("My inverter", pcPackage->GetDescription());
	AssertGridPosition(-5, 0, pcPackage->GetPortView("Input"));
	AssertGridPosition(6, 0, pcPackage->GetPortView("Output"));
	SafeKill(pcPackage);

	sz.Init();
	CInverterPackageView::GetDescription(&sz, "2G14", 2);
	AssertString("Dual Schmitt Inverter", sz.Text());
	sz.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// A unit is drawn and wired as an inverter of one.
//
//////////////////////////////////////////////////////////////////////////
void TestInverterUnitViewGeometry(void)
{
	CInverterUnitView*	pcUnit;
	CInverterUnitView*	pcNext;
	int					i;

	pcUnit = NewMalloc<CInverterUnitView>();
	pcUnit->Init(10, 4, ROT_East, "U5", "LVC", false, "04", 2);
	AssertString("Inverter Unit", pcUnit->GetType());
	AssertString("InverterUnit", pcUnit->GetXMLName());
	AssertInt(2, pcUnit->GetUnit());
	AssertChar('C', pcUnit->GetUnitLetter());
	AssertString("04", pcUnit->GetPartType());
	AssertSize(2, pcUnit->NumPortViews());
	AssertGridPosition(9, 4, pcUnit->GetPortView("Input"));
	AssertGridPosition(12, 4, pcUnit->GetPortView("Output"));
	AssertTrue(pcUnit->GetPortView("Output")->IsInverting());
	AssertInt(6, pcUnit->GetUnitCount());

	//Each unit makes the next, as it is, until the part's last.
	pcNext = (CInverterUnitView*)pcUnit->NewNextUnit();
	AssertNotNull(pcNext);
	AssertChar('D', pcNext->GetUnitLetter());
	AssertString("U5", pcNext->GetName());
	AssertString("LVC", pcNext->GetFamily());
	AssertString("04", pcNext->GetPartType());
	AssertInt(10, pcNext->GetPosition().x);
	SafeKill(pcUnit);
	pcUnit = pcNext;
	for (i = 0; i < 2; i++)
	{
		pcNext = (CInverterUnitView*)pcUnit->NewNextUnit();
		AssertNotNull(pcNext);
		SafeKill(pcUnit);
		pcUnit = pcNext;
	}
	AssertChar('F', pcUnit->GetUnitLetter());
	AssertNull(pcUnit->NewNextUnit());
	SafeKill(pcUnit);

	pcUnit = NewMalloc<CInverterUnitView>();
	pcUnit->Init(0, 0, ROT_East, "U7", "LVC", false, "2G04", 0);
	AssertInt(2, pcUnit->GetUnitCount());
	pcNext = (CInverterUnitView*)pcUnit->NewNextUnit();
	AssertNotNull(pcNext);
	AssertNull(pcNext->NewNextUnit());
	SafeKill(pcNext);
	SafeKill(pcUnit);

	AssertInt(6, CInverterPackageView::GetPartUnitCount("14"));
	AssertInt(1, CInverterPackageView::GetPartUnitCount("1G04"));
	AssertInt(3, CInverterPackageView::GetPartUnitCount("3G14"));
}


//////////////////////////////////////////////////////////////////////////
//
// A package and its units placed apart, saved and loaded back.
//
//////////////////////////////////////////////////////////////////////////
void TestInverterPackageViewsFile(void)
{
	CCircuitView			cSaved;
	CCircuitView			cLoaded;
	CInverterPackageView*	pcPackage;
	CInverterUnitView*		pcUnit;
	CFileUtil				cFileUtil;
	int						i;

	cSaved.Init();
	pcPackage = NewMalloc<CInverterPackageView>();
	pcPackage->Init(0, 0, ROT_West, "U5", "LVC", false, "14", 6, "Six Schmitt");
	cSaved.Add(pcPackage);
	for (i = 0; i < 6; i++)
	{
		pcUnit = NewMalloc<CInverterUnitView>();
		pcUnit->Init(20, 4 * i, ROT_East, "U6", "LVC", false, "04", i);
		cSaved.Add(pcUnit);
	}

	cFileUtil.MakeDir("Output");
	AssertTrue(SaveCircuitFile(&cSaved, "Output" _FS_ "InverterPackages.xml"));
	cLoaded.Init();
	AssertTrue(LoadCircuitFile(&cLoaded, "Output" _FS_ "InverterPackages.xml"));
	AssertSize(7, cLoaded.NumComponents());

	pcPackage = (CInverterPackageView*)cLoaded.GetComponent(0);
	AssertString("Inverter Package", pcPackage->GetType());
	AssertString("14", pcPackage->GetPartType());
	AssertString("Six Schmitt", pcPackage->GetDescription());
	AssertInt(6, pcPackage->GetUnitCount());
	AssertInt(ROT_West, pcPackage->GetRotation());
	AssertString("U5", pcPackage->GetName());
	for (i = 0; i < 6; i++)
	{
		pcUnit = (CInverterUnitView*)cLoaded.GetComponent(1 + i);
		AssertString("Inverter Unit", pcUnit->GetType());
		AssertInt(i, pcUnit->GetUnit());
		AssertString("04", pcUnit->GetPartType());
		AssertString("LVC", pcUnit->GetFamily());
		AssertInt(4 * i, pcUnit->GetPosition().y);
	}
	cLoaded.Kill();
	cSaved.Kill();
	cFileUtil.Delete("Output" _FS_ "InverterPackages.xml");
}


//////////////////////////////////////////////////////////////////////////
//
// Each of the package's inverters inverts its own input: a supply on
// input 3 drives output 3 low and leaves the others' outputs as they were.
// A unit is an inverter too.
//
//////////////////////////////////////////////////////////////////////////
void TestInverterPackageViewSimulation(void)
{
	CFamilyVoltageConfigurationStore	cFamilies;
	CFamilyVoltageConfiguration*		pcFamily;
	CCircuitSimulation					cSimulation;
	CCircuitView						cCircuit;
	CViewPaths							cPaths;
	CViewPath*							pcPath;
	CInverterPackageView*				pcPackage;
	CInverterUnitView*					pcUnit;
	CTraceView*							pcIn;
	CTraceView*							pcOut;
	CTraceView*							pcOther;
	CTraceView*							pcUnitIn;
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
	cSimulation.Init("Inverter Package");
	cCircuit.Init();
	cPaths.Init();
	pcPath = cPaths.AddTop(&cCircuit);

	pcPackage = NewMalloc<CInverterPackageView>();
	pcPackage->Init(0, 0, ROT_East, "U5", "LVC", false, "04", 6);
	cCircuit.Add(pcPackage);
	pcIn = cCircuit.AddTrace(-10, 1, -5, 1);
	pcOut = cCircuit.AddTrace(6, 1, 10, 1);
	pcOther = cCircuit.AddTrace(6, 3, 10, 3);

	pcUnit = NewMalloc<CInverterUnitView>();
	pcUnit->Init(20, 0, ROT_East, "U6", "LVC", false, "04", 0);
	cCircuit.Add(pcUnit);
	pcUnitIn = cCircuit.AddTrace(10, 1, 10, 0);
	cCircuit.AddTrace(10, 0, 19, 0);
	pcUnitOut = cCircuit.AddTrace(22, 0, 26, 0);

	AssertTrue(cCircuit.CreateSimulation(pcPath, &cSimulation, &cFamilies));
	AssertTrue(pcPackage->GetPortView("Input 3")->GetPort(pcPath, &cSimulation, 0)->GetTrace() == pcIn->GetTrace(pcPath, &cSimulation, 0));
	AssertTrue(pcPackage->GetPortView("Output 3")->GetPort(pcPath, &cSimulation, 0)->GetTrace() == pcOut->GetTrace(pcPath, &cSimulation, 0));
	AssertTrue(pcUnit->GetPortView("Input")->GetPort(pcPath, &cSimulation, 0)->GetTrace() == pcUnitIn->GetTrace(pcPath, &cSimulation, 0));

	pcSupply = NewMalloc<CPowerSource>();
	pcSupply->Init(cSimulation.GetSubcircuitTopSimulation(), "Supply", fVcc);
	AssertTrue(pcSupply->GetPowerOutPort()->ConnectLive(pcIn->GetTrace(pcPath, &cSimulation, 0), cSimulation.GetTimeline()));
	cSimulation.GetTimeline()->Run();
	AssertInt(TV_High, pcFamily->GetValue(pcIn->GetTrace(pcPath, &cSimulation, 0)->GetVoltage(cSimulation.GetTime()), fVcc));
	AssertInt(TV_Low, pcFamily->GetValue(pcOut->GetTrace(pcPath, &cSimulation, 0)->GetVoltage(cSimulation.GetTime()), fVcc));
	AssertTrue(pcFamily->GetValue(pcOther->GetTrace(pcPath, &cSimulation, 0)->GetVoltage(cSimulation.GetTime()), fVcc) != TV_Low);
	AssertInt(TV_High, pcFamily->GetValue(pcUnitOut->GetTrace(pcPath, &cSimulation, 0)->GetVoltage(cSimulation.GetTime()), fVcc));

	cCircuit.Kill();
	cPaths.Kill();
	cSimulation.Kill();
	cFamilies.Kill();
	ObjectsKill();
}


//////////////////////////////////////////////////////////////////////////
//
// A 74LVC04 as a block, and as six units placed apart.
//
//////////////////////////////////////////////////////////////////////////
void TestInverterPackageViewsRender(void)
{
	CCircuitView			cCircuit;
	CCircuitColours			cColours;
	CCircuitFonts			cFonts;
	CInverterPackageView*	pcPackage;
	CInverterUnitView*		pcUnit;
	int						i;

	ObjectsInit();
	LoadTestCircuitFonts(&cFonts);
	cColours.InitLogicim();
	cCircuit.Init();

	pcPackage = NewMalloc<CInverterPackageView>();
	pcPackage->Init(-11, 0, ROT_East, "U5", "LVC", false, "04", 6);
	cCircuit.Add(pcPackage);
	for (i = 0; i < 6; i++)
	{
		pcUnit = NewMalloc<CInverterUnitView>();
		pcUnit->Init(2 + 6 * (i % 3), -4 + 8 * (i / 3), ROT_East, "U6", "LVC", false, "04", i);
		cCircuit.Add(pcUnit);
	}
	AssertRenderedCircuit(&cCircuit, &cColours, 760, 400, 2, NULL, NULL, true, "InverterPackages", &cFonts);

	cCircuit.Kill();
	KillTestCircuitFonts(&cFonts);
	ObjectsFlush();
	ObjectsKill(false);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestInverterPackageViews(void)
{
	BeginTests();
	DataIOInit();
	DataMemoryInit();

	TestInverterPackageViewGeometry();
	TestInverterUnitViewGeometry();
	TestInverterPackageViewsFile();
	TestInverterPackageViewSimulation();
	TestInverterPackageViewsRender();

	DataMemoryKill();
	DataIOKill();
	TestStatistics();
}

