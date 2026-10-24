#include "BaseLib/ConstructorCall.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/DataMemory.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/TextFile.h"
#include "StandardLib/Objects.h"
#include "MicroprocessorLib/CircuitSimulation.h"
#include "MicroprocessorLib/FamilyVoltageConfigurationStore.h"
#include "MicroprocessorLib/Timeline.h"
#include "MicroprocessorLib/Trace.h"
#include "MicroprocessorLib/Event.h"
#include "LogicimLib/AndGateView.h"
#include "LogicimLib/OrGateView.h"
#include "LogicimLib/BufferView.h"
#include "LogicimLib/PowerSourceView.h"
#include "LogicimLib/ComponentViewFactory.h"
#include "LogicimLib/CircuitFile.h"
#include "TestLib/Assert.h"
#include "TestLogicimRender.h"


//////////////////////////////////////////////////////////////////////////
//
// One of each view, with properties other than the defaults.
//
//////////////////////////////////////////////////////////////////////////
void AddEveryCircuitFileView(CCircuitView* pcCircuit)
{
	CAndGateView*	pcAnd;
	CNandGateView*	pcNand;
	COrGateView*	pcOr;
	CNorGateView*	pcNor;
	CXorGateView*	pcXor;
	CXnorGateView*	pcXnor;
	CBufferView*	pcBuffer;
	CInverterView*	pcInverter;
	CGroundView*	pcGround;

	pcAnd = NewMalloc<CAndGateView>();
	pcAnd->Init(-30, -5, ROT_West, "U1", "LVC", false, 2, 1);
	pcCircuit->Add(pcAnd);
	pcNand = NewMalloc<CNandGateView>();
	pcNand->Init(-20, -5, ROT_East, "Nand <&> \"1\"", "HC", true, 3, 1);
	pcCircuit->Add(pcNand);
	pcOr = NewMalloc<COrGateView>();
	pcOr->Init(-10, -5, ROT_South, "", "LVC", false, 4, 2);
	pcCircuit->Add(pcOr);
	pcNor = NewMalloc<CNorGateView>();
	pcNor->Init(0, -5, ROT_North, "", "LVC", false, 2, 1);
	pcCircuit->Add(pcNor);
	pcXor = NewMalloc<CXorGateView>();
	pcXor->Init(10, -5, ROT_West, "", "LVC", false, 2, 1);
	pcCircuit->Add(pcXor);
	pcXnor = NewMalloc<CXnorGateView>();
	pcXnor->Init(20, -5, ROT_West, "", "LVC", false, 5, 1);
	pcCircuit->Add(pcXnor);
	pcBuffer = NewMalloc<CBufferView>();
	pcBuffer->Init(30, -5, ROT_West, "", "LVC", false, 3, 8);
	pcCircuit->Add(pcBuffer);
	pcInverter = NewMalloc<CInverterView>();
	pcInverter->Init(-3, 6, ROT_West, "", "LVC", false, 1, 1);
	pcCircuit->Add(pcInverter);
	pcGround = NewMalloc<CGroundView>();
	pcGround->Init(-8, 6, ROT_North, "G");
	pcCircuit->Add(pcGround);
	pcCircuit->AddTraces(-8, 6, -4, 7);
	pcCircuit->AddTrace(-1, 6, 6, 6);
}


//////////////////////////////////////////////////////////////////////////
//
// The format: a view's properties as attributes, then the wires.
//
//////////////////////////////////////////////////////////////////////////
void TestCircuitFileXML(void)
{
	CCircuitView	cCircuit;
	CXMLWriter		cWriter;
	char			szExpected[] = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<Logicim version=\"1\">\n\
  <Circuit>\n\
    <AndGate name=\"U1\" x=\"-30\" y=\"-5\" rotation=\"West\" family=\"LVC\" explicitPowerPorts=\"false\" inputCount=\"2\" inputWidth=\"1\"/>\n\
    <NandGate name=\"Nand &lt;&amp;&gt; &quot;1&quot;\" x=\"-20\" y=\"-5\" rotation=\"East\" family=\"HC\" explicitPowerPorts=\"true\" inputCount=\"3\" inputWidth=\"1\"/>\n\
    <OrGate name=\"\" x=\"-10\" y=\"-5\" rotation=\"South\" family=\"LVC\" explicitPowerPorts=\"false\" inputCount=\"4\" inputWidth=\"2\"/>\n\
    <NorGate name=\"\" x=\"0\" y=\"-5\" rotation=\"North\" family=\"LVC\" explicitPowerPorts=\"false\" inputCount=\"2\" inputWidth=\"1\"/>\n\
    <XorGate name=\"\" x=\"10\" y=\"-5\" rotation=\"West\" family=\"LVC\" explicitPowerPorts=\"false\" inputCount=\"2\" inputWidth=\"1\"/>\n\
    <XnorGate name=\"\" x=\"20\" y=\"-5\" rotation=\"West\" family=\"LVC\" explicitPowerPorts=\"false\" inputCount=\"5\" inputWidth=\"1\"/>\n\
    <Buffer name=\"\" x=\"30\" y=\"-5\" rotation=\"West\" family=\"LVC\" explicitPowerPorts=\"false\" inputCount=\"3\" inputWidth=\"8\"/>\n\
    <Inverter name=\"\" x=\"-3\" y=\"6\" rotation=\"West\" family=\"LVC\" explicitPowerPorts=\"false\" inputCount=\"1\" inputWidth=\"1\"/>\n\
    <Ground name=\"G\" x=\"-8\" y=\"6\" rotation=\"North\"/>\n\
    <Trace x0=\"-8\" y0=\"6\" x1=\"-4\" y1=\"6\"/>\n\
    <Trace x0=\"-4\" y0=\"6\" x1=\"-4\" y1=\"7\"/>\n\
    <Trace x0=\"-1\" y0=\"6\" x1=\"6\" y1=\"6\"/>\n\
  </Circuit>\n\
</Logicim>\n";

	cCircuit.Init();
	AddEveryCircuitFileView(&cCircuit);
	cWriter.Init();
	SaveCircuitXML(&cCircuit, &cWriter);
	AssertString(szExpected, cWriter.GetText());
	cWriter.Kill();
	cCircuit.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// Every view the factory knows makes itself and names itself the same way.
//
//////////////////////////////////////////////////////////////////////////
void TestCircuitFileFactory(void)
{
	size				i;
	CComponentView*		pcView;

	AssertSize(9, NumComponentViewTypes());
	for (i = 0; i < NumComponentViewTypes(); i++)
	{
		pcView = NewComponentView(GetComponentViewXMLName(i));
		AssertNotNull(pcView);
		AssertString(GetComponentViewXMLName(i), pcView->GetXMLName());
		free(pcView);
	}
	AssertNull(NewComponentView("Toaster"));
	AssertTrue(GetComponentViewXMLName(NumComponentViewTypes()) == NULL);
}


//////////////////////////////////////////////////////////////////////////
//
// A loaded circuit saves the same, has the same ports in the same places
// and simulates and draws as the one saved.
//
//////////////////////////////////////////////////////////////////////////
void TestCircuitFileRoundTrip(void)
{
	CFamilyVoltageConfigurationStore	cFamilies;
	CCircuitSimulation					cSimulation;
	CCircuitView						cSaved;
	CCircuitView						cLoaded;
	CCircuitColours						cColours;
	CXMLWriter							cSavedText;
	CXMLWriter							cLoadedText;
	CFileUtil							cFileUtil;
	size								i;
	size								j;
	CComponentView*						pcSaved;
	CComponentView*						pcLoaded;
	SInt32Vec2							sSavedPosition;
	SInt32Vec2							sLoadedPosition;

	cSaved.Init();
	AddEveryCircuitFileView(&cSaved);
	cFileUtil.MakeDir("Output");
	AssertTrue(SaveCircuitFile(&cSaved, "Output" _FS_ "Every.xml"));

	cLoaded.Init();
	AssertTrue(LoadCircuitFile(&cLoaded, "Output" _FS_ "Every.xml"));
	AssertSize(cSaved.NumComponents(), cLoaded.NumComponents());
	AssertSize(cSaved.NumTraces(), cLoaded.NumTraces());

	cSavedText.Init();
	SaveCircuitXML(&cSaved, &cSavedText);
	cLoadedText.Init();
	SaveCircuitXML(&cLoaded, &cLoadedText);
	AssertString(cSavedText.GetText(), cLoadedText.GetText());
	cLoadedText.Kill();
	cSavedText.Kill();

	for (i = 0; i < cSaved.NumComponents(); i++)
	{
		pcSaved = cSaved.GetComponent(i);
		pcLoaded = cLoaded.GetComponent(i);
		AssertString(pcSaved->GetType(), pcLoaded->GetType());
		AssertSize(pcSaved->NumPortViews(), pcLoaded->NumPortViews());
		for (j = 0; j < pcSaved->NumPortViews(); j++)
		{
			sSavedPosition = pcSaved->GetPortView(j)->GetGridPosition();
			sLoadedPosition = pcLoaded->GetPortView(j)->GetGridPosition();
			AssertInt(sSavedPosition.x, sLoadedPosition.x);
			AssertInt(sSavedPosition.y, sLoadedPosition.y);
			AssertSize(pcSaved->GetPortView(j)->NumPortNames(), pcLoaded->GetPortView(j)->NumPortNames());
		}
	}
	cLoaded.Kill();
	cSaved.Kill();

	//The circuit of TestCircuitViewGroundDrivesInverters, from its file, draws as that test's reference.
	ObjectsInit();
	CEvent::ResetNextID();
	CTrace::ResetNextID();
	cFamilies.Init();
	AssertTrue(cFamilies.Load("Input" _FS_ "PropagationTimes.csv"));
	cSimulation.Init("Ground");
	cLoaded.Init();
	cColours.InitLogicim();
	AssertTrue(LoadCircuitFile(&cLoaded, "Input" _FS_ "GroundInverters.xml"));
	AssertTrue(cLoaded.CreateSimulation(&cSimulation, &cFamilies));
	cSimulation.GetTimeline()->Run();
	AssertRenderedCircuit(&cLoaded, &cColours, 420, 160, 2, cSimulation.GetTime(), true, "GroundInverters");
	cLoaded.Kill();
	cSimulation.Kill();
	cFamilies.Kill();
	ObjectsKill();

	cFileUtil.Delete("Output" _FS_ "Every.xml");
	cFileUtil.RemoveDir("Output");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
bool LoadCircuitText(CCircuitView* pcCircuit, const char* szText)
{
	CTextFile	cText;
	CFileUtil	cFileUtil;
	bool		bResult;

	cFileUtil.MakeDir("Output");
	cText.Init(szText);
	cText.Write("Output" _FS_ "Bad.xml");
	cText.Kill();
	bResult = LoadCircuitFile(pcCircuit, "Output" _FS_ "Bad.xml");
	cFileUtil.Delete("Output" _FS_ "Bad.xml");
	cFileUtil.RemoveDir("Output");
	return bResult;
}


//////////////////////////////////////////////////////////////////////////
//
// Files that can't be read fail and leave what was read before the
// problem.
//
//////////////////////////////////////////////////////////////////////////
void TestCircuitFileErrors(void)
{
	CCircuitView	cCircuit;
	SLogConfig		sLogConfig;
	char			szHeader[] = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
	CChars			sz;

	gcLogger.GetConfig(&sLogConfig);
	gcLogger.SetSilent();

	cCircuit.Init();
	AssertFalse(LoadCircuitFile(&cCircuit, "Output" _FS_ "Missing.xml"));

	sz.Init(szHeader);
	sz.Append("<Circuit/>\n");
	AssertFalse(LoadCircuitText(&cCircuit, sz.Text()));
	sz.Kill();

	sz.Init(szHeader);
	sz.Append("<Logicim version=\"2\"><Circuit/></Logicim>\n");
	AssertFalse(LoadCircuitText(&cCircuit, sz.Text()));
	sz.Kill();

	sz.Init(szHeader);
	sz.Append("<Logicim version=\"1\"></Logicim>\n");
	AssertFalse(LoadCircuitText(&cCircuit, sz.Text()));
	sz.Kill();

	sz.Init(szHeader);
	sz.Append("<Logicim version=\"1\"><Circuit><Ground x=\"1\" y=\"2\" rotation=\"West\"/><Toaster/></Circuit></Logicim>\n");
	AssertFalse(LoadCircuitText(&cCircuit, sz.Text()));
	AssertSize(1, cCircuit.NumComponents());
	AssertString("", cCircuit.GetComponent(0)->GetName());
	sz.Kill();

	sz.Init(szHeader);
	sz.Append("<Logicim version=\"1\"><Circuit><Ground x=\"1\" y=\"two\" rotation=\"West\"/></Circuit></Logicim>\n");
	AssertFalse(LoadCircuitText(&cCircuit, sz.Text()));
	sz.Kill();

	sz.Init(szHeader);
	sz.Append("<Logicim version=\"1\"><Circuit><Ground x=\"1\" y=\"2\" rotation=\"Up\"/></Circuit></Logicim>\n");
	AssertFalse(LoadCircuitText(&cCircuit, sz.Text()));
	sz.Kill();

	sz.Init(szHeader);
	sz.Append("<Logicim version=\"1\"><Circuit><AndGate x=\"1\" y=\"2\" rotation=\"West\" inputCount=\"2\" inputWidth=\"1\"/></Circuit></Logicim>\n");
	AssertFalse(LoadCircuitText(&cCircuit, sz.Text()));
	sz.Kill();

	sz.Init(szHeader);
	sz.Append("<Logicim version=\"1\"><Circuit><OrGate x=\"1\" y=\"2\" rotation=\"West\" family=\"LVC\" inputCount=\"0\" inputWidth=\"1\"/></Circuit></Logicim>\n");
	AssertFalse(LoadCircuitText(&cCircuit, sz.Text()));
	sz.Kill();

	sz.Init(szHeader);
	sz.Append("<Logicim version=\"1\"><Circuit><Trace x0=\"1\" y0=\"2\" x1=\"3\"/></Circuit></Logicim>\n");
	AssertFalse(LoadCircuitText(&cCircuit, sz.Text()));
	sz.Kill();

	//Explicit power ports default to implicit; nothing else was added by the failures.
	sz.Init(szHeader);
	sz.Append("<Logicim version=\"1\"><Circuit><OrGate x=\"1\" y=\"2\" rotation=\"West\" family=\"LVC\" inputCount=\"3\" inputWidth=\"1\"/></Circuit></Logicim>\n");
	AssertTrue(LoadCircuitText(&cCircuit, sz.Text()));
	sz.Kill();
	AssertSize(2, cCircuit.NumComponents());
	AssertSize(0, cCircuit.NumTraces());
	AssertFalse(((CIntegratedCircuitView*)cCircuit.GetComponent(1))->IsExplicitPowerPorts());
	AssertSize(4, cCircuit.GetComponent(1)->NumPortViews());
	cCircuit.Kill();

	gcLogger.SetConfig(&sLogConfig);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCircuitFile(void)
{
	BeginTests();
	DataIOInit();
	DataMemoryInit();

	TestCircuitFileXML();
	TestCircuitFileFactory();
	TestCircuitFileRoundTrip();
	TestCircuitFileErrors();

	DataMemoryKill();
	DataIOKill();
	TestStatistics();
}

