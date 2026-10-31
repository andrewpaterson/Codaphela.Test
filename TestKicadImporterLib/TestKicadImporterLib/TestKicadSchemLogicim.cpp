#include "BaseLib/FileUtil.h"
#include "BaseLib/TextFile.h"
#include "BaseLib/GlobalDataTypesIO.h"
#include "BaseLib/DataMemory.h"
#include "BaseLib/Chars.h"
#include "BaseLib/ArrayInt.h"
#include "StandardLib/Objects.h"
#include "LogicimLib/CircuitFile.h"
#include "LogicimLib/CircuitFonts.h"
#include "LogicimLib/TunnelView.h"
#include "KicadImporterLib/KicadSchemLogicimConverter.h"
#include "TestLib/Assert.h"


#define KICAD_SCHEM_LOGICIM_FONTS		"Input" _FS_ "Fonts"
#define KICAD_SCHEM_LOGICIM_TEST_BITS	64


extern char gszKicadSchemTestFile[];
extern char gszKicadSchemBusTestFile[];
extern char gszKicadSchemNetlistTestFile[];


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestKicadSchemLogicFunction(void)
{
	CChars	szFamily;
	CChars	szPartType;

	szFamily.Init();
	AssertInt(KSLF_And, ParseKicadSchemLogicFunction("Nexperia:74LVC08APW,112_Multi", &szFamily));
	AssertString("LVC", szFamily.Text());
	AssertInt(KSLF_And, ParseKicadSchemLogicFunction("Nexperia:74LVC1G08GV,125", &szFamily));
	AssertInt(KSLF_Inverter, ParseKicadSchemLogicFunction("74LVC2G04GW-Q100H_Multi", &szFamily));
	AssertInt(KSLF_Inverter, ParseKicadSchemLogicFunction("Texas_Instruments:SN74LVC14APWRG4 _Multi", &szFamily));
	AssertInt(KSLF_Nand, ParseKicadSchemLogicFunction("74HC00", &szFamily));
	AssertString("LVC", szFamily.Text());
	AssertInt(KSLF_Nand, ParseKicadSchemLogicFunction("Texas_Instruments:SN74F30DR", &szFamily));
	AssertString("F", szFamily.Text());
	AssertInt(KSLF_Or, ParseKicadSchemLogicFunction("74AHCT32", &szFamily));
	AssertString("AHCT", szFamily.Text());
	AssertInt(KSLF_DFlipFlop, ParseKicadSchemLogicFunction("Nexperia:74LVC74APW,118_Multi", &szFamily));
	AssertInt(KSLF_Nor, ParseKicadSchemLogicFunction("74LVC02APW,118", &szFamily));
	AssertInt(KSLF_Xor, ParseKicadSchemLogicFunction("74VHCT86", &szFamily));
	AssertString("VHCT", szFamily.Text());
	AssertInt(KSLF_None, ParseKicadSchemLogicFunction("Nexperia:74LVC574APW,118", &szFamily));
	AssertInt(KSLF_None, ParseKicadSchemLogicFunction("Texas_Instruments:CD74HCT40105M", &szFamily));
	AssertInt(KSLF_None, ParseKicadSchemLogicFunction("Device:R", &szFamily));
	AssertInt(KSLF_None, ParseKicadSchemLogicFunction("W65C02S", &szFamily));
	AssertInt(KSLF_None, ParseKicadSchemLogicFunction("1748", &szFamily));
	AssertInt(KSLF_None, ParseKicadSchemLogicFunction(NULL, &szFamily));
	szFamily.Kill();

	szFamily.Init();
	szPartType.Init();
	AssertInt(KSLF_Inverter, ParseKicadSchemLogicFunction("Nexperia:74LVC2G04GW-Q100H_Multi", &szFamily, &szPartType));
	AssertString("2G04", szPartType.Text());
	AssertInt(KSLF_Inverter, ParseKicadSchemLogicFunction("SN74LVC14APWR", &szFamily, &szPartType));
	AssertString("14", szPartType.Text());
	AssertString("LVC", szFamily.Text());
	szPartType.Kill();
	szFamily.Kill();

	AssertString("Nand", KicadSchemLogicFunctionName(KSLF_Nand));
	AssertTrue(IsKicadSchemLogicimFamily("HCT"));
	AssertFalse(IsKicadSchemLogicimFamily("HC"));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestKicadSchemLogicimNames(void)
{
	AssertTrue(CKicadSchemLogicimConverter::IsGroundName("GND"));
	AssertTrue(CKicadSchemLogicimConverter::IsGroundName("gnda"));
	AssertTrue(CKicadSchemLogicimConverter::IsGroundName("VSS"));
	AssertFalse(CKicadSchemLogicimConverter::IsGroundName("VCC"));
	AssertFalse(CKicadSchemLogicimConverter::IsGroundName("+5V"));

	AssertFloat(5.0f, CKicadSchemLogicimConverter::GetSupplyVoltage("+5V"), 4);
	AssertFloat(3.3f, CKicadSchemLogicimConverter::GetSupplyVoltage("+3V3"), 4);
	AssertFloat(3.3f, CKicadSchemLogicimConverter::GetSupplyVoltage("3.3V"), 4);
	AssertFloat(12.0f, CKicadSchemLogicimConverter::GetSupplyVoltage("12VOut"), 4);
	AssertFloat(5.0f, CKicadSchemLogicimConverter::GetSupplyVoltage("VCC"), 4);

	AssertInt(ROT_East, CKicadSchemLogicimConverter::GetKicadRotation(ROT_East, 0));
	AssertInt(ROT_North, CKicadSchemLogicimConverter::GetKicadRotation(ROT_East, 90));
	AssertInt(ROT_West, CKicadSchemLogicimConverter::GetKicadRotation(ROT_East, 180));
	AssertInt(ROT_South, CKicadSchemLogicimConverter::GetKicadRotation(ROT_East, 270));
	AssertInt(ROT_South, CKicadSchemLogicimConverter::GetKicadRotation(ROT_East, -90));
	AssertInt(ROT_West, CKicadSchemLogicimConverter::GetKicadRotation(ROT_North, 90));
	AssertInt(ROT_East, CKicadSchemLogicimConverter::GetKicadRotation(ROT_South, 90));
}


//////////////////////////////////////////////////////////////////////////
//
// An L of two wires from (0, 0) right to (10, 0) and down to (10, 20),
// with a pin on its middle at (10, 5).
//
//////////////////////////////////////////////////////////////////////////
void TestKicadSchemSubnetGraph(void)
{
	CKicadSchemSubnet		cSubnet;
	CKicadSchemWire			cAcross;
	CKicadSchemWire			cDown;
	CKicadSchemSubnetGraph	cGraph;
	SKicadSchemPoint		sStart;
	SKicadSchemPoint		sCorner;
	SKicadSchemPoint		sEnd;
	SKicadSchemPoint		sMiddle;
	size					uiStart;
	size					uiEnd;
	size					uiMiddle;
	CArrayInt				aiTargets;
	CArrayInt				aiPath;
	CArrayKicadSchemPoint	asPath;
	size					i;
	bool					bHorizontal;

	sStart.Init(0, 0);
	sCorner.Init(10, 0);
	sEnd.Init(10, 20);
	sMiddle.Init(10, 5);
	cAcross.Init(&sStart, &sCorner, false);
	cDown.Init(&sCorner, &sEnd, false);
	cSubnet.Init();
	cSubnet.AddWire(&cAcross);
	cSubnet.AddWire(&cDown);

	cGraph.Init(&cSubnet);
	uiStart = cGraph.AddPoint(&sStart);
	uiEnd = cGraph.AddPoint(&sEnd);
	uiMiddle = cGraph.AddPoint(&sMiddle);
	AssertSize(uiStart, cGraph.AddPoint(&sStart));
	cGraph.Build();
	AssertSize(4, cGraph.NumPoints());
	AssertSize(3, cGraph.NumEdges());

	aiTargets.Init();
	aiTargets.Add((int)uiEnd);
	aiPath.Init();
	AssertTrue(cGraph.FindPath(uiStart, &aiTargets, &aiPath));
	AssertSize(4, aiPath.NumElements());
	AssertInt((int)uiStart, aiPath.GetValue(0));
	AssertInt((int)uiMiddle, aiPath.GetValue(2));
	AssertInt((int)uiEnd, aiPath.GetValue(3));

	asPath.Init();
	for (i = 0; i < aiPath.NumElements(); i++)
	{
		asPath.Add(cGraph.GetPoint(aiPath.GetValue(i)));
	}
	AssertDouble(1.0, CKicadSchemSubnetGraph::GetBendFraction(&asPath, &bHorizontal), 6);
	AssertTrue(bHorizontal);
	asPath.Kill();

	//Back up from the end: down (up the page) first, turning at the top, a whole way up.
	aiTargets.ReInit();
	aiTargets.Add((int)uiStart);
	aiPath.ReInit();
	AssertTrue(cGraph.FindPath(uiEnd, &aiTargets, &aiPath));
	asPath.Init();
	for (i = 0; i < aiPath.NumElements(); i++)
	{
		asPath.Add(cGraph.GetPoint(aiPath.GetValue(i)));
	}
	AssertDouble(1.0, CKicadSchemSubnetGraph::GetBendFraction(&asPath, &bHorizontal), 6);
	AssertFalse(bHorizontal);
	asPath.Kill();

	//A Z from (0, 0) to (20, 10) turning down at x 5.
	asPath.Init();
	sStart.Init(0, 0);
	asPath.Add(&sStart);
	sStart.Init(5, 0);
	asPath.Add(&sStart);
	sStart.Init(5, 10);
	asPath.Add(&sStart);
	sStart.Init(20, 10);
	asPath.Add(&sStart);
	AssertDouble(0.25, CKicadSchemSubnetGraph::GetBendFraction(&asPath, &bHorizontal), 6);
	AssertTrue(bHorizontal);
	asPath.Kill();

	asPath.Init();
	asPath.Add(&sStart);
	AssertDouble(0.5, CKicadSchemSubnetGraph::GetBendFraction(&asPath, &bHorizontal), 6);
	asPath.Kill();

	aiPath.Kill();
	aiTargets.Kill();
	cGraph.Kill();
	cSubnet.Kill();
	cDown.Kill();
	cAcross.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// The port as "owner.port (x, y)".
//
//////////////////////////////////////////////////////////////////////////
void AppendKicadSchemLogicimPort(CChars* psz, CPortView* pcPortView)
{
	psz->Append(pcPortView->GetOwner()->GetName());
	psz->Append('.');
	psz->Append(pcPortView->GetPortName(0));
	psz->Append(" (");
	psz->Append(pcPortView->GetGridPosition().x);
	psz->Append(", ");
	psz->Append(pcPortView->GetGridPosition().y);
	psz->Append(')');
}


//////////////////////////////////////////////////////////////////////////
//
// The circuit's ports joined as Logicim's wiring joins them (see
// CCircuitWiring::JoinLevel): wires that touch, ports on wires, ports at
// the same place and ports of tunnels with the same name; and their bits
// where splitters join them.  Every subnet's terminals must be joined, and
// no bit can be of two different nets.
//
//////////////////////////////////////////////////////////////////////////
void AssertKicadSchemLogicimWired(CKicadSchemLogicimConverter* pcConverter)
{
	CCircuitView*					pcCircuit;
	CArrayPortViewPtr				apcPorts;
	CArrayInt						aiParents;
	CArrayTemplatePtr<CKicadSchemNet>	apcGroupNets;
	CArrayInt						aiSubnetGroups;
	size							uiTraces;
	size							i;
	size							j;
	const char*						szName;
	const char*						szOtherName;
	SKicadSchemLogicimTerminal*		psTerminal;
	int								iGroup;
	CKicadSchemNet*					pcNet;
	size							uiSubnet;
	CChars							szFirst;
	CChars							szThis;
	CArrayInt						aiBits;
	CArrayPortBitJoin				asJoins;
	SPortBitJoin*					psJoin;
	int								iBit;

	pcCircuit = pcConverter->GetCircuit();
	apcPorts.Init();
	pcCircuit->CollectPortViews(&apcPorts);
	uiTraces = pcCircuit->NumTraces();
	aiParents.Init();
	for (i = 0; i < uiTraces + apcPorts.NumElements(); i++)
	{
		aiParents.Add((int)i);
	}
	for (i = 0; i < uiTraces; i++)
	{
		for (j = i + 1; j < uiTraces; j++)
		{
			if (pcCircuit->GetTrace(i)->Touches(pcCircuit->GetTrace(j)))
			{
				JoinKicadSchemRoots(&aiParents, (int)i, (int)j);
			}
		}
	}
	for (i = 0; i < apcPorts.NumElements(); i++)
	{
		for (j = 0; j < uiTraces; j++)
		{
			if (pcCircuit->GetTrace(j)->Contains(apcPorts.GetPtr(i)->GetGridPosition()))
			{
				JoinKicadSchemRoots(&aiParents, (int)(uiTraces + i), (int)j);
			}
		}
		szName = apcPorts.GetPtr(i)->GetOwner()->GetConnectionName();
		for (j = i + 1; j < apcPorts.NumElements(); j++)
		{
			szOtherName = apcPorts.GetPtr(j)->GetOwner()->GetConnectionName();
			if ((apcPorts.GetPtr(i)->GetGridPosition() == apcPorts.GetPtr(j)->GetGridPosition()) ||
				((szName != NULL) && (szOtherName != NULL) && (StringCompare(szName, szOtherName) == 0)))
			{
				JoinKicadSchemRoots(&aiParents, (int)(uiTraces + i), (int)(uiTraces + j));
			}
		}
	}

	//The bits of each group, joined where components (splitters) join them.
	aiBits.Init();
	for (i = 0; i < aiParents.NumElements() * KICAD_SCHEM_LOGICIM_TEST_BITS; i++)
	{
		aiBits.Add((int)i);
	}
	for (i = 0; i < pcCircuit->NumComponents(); i++)
	{
		asJoins.Init();
		pcCircuit->GetComponent(i)->GetBitJoins(&asJoins);
		for (j = 0; j < asJoins.NumElements(); j++)
		{
			psJoin = asJoins.Get(j);
			AssertTrue((psJoin->uiFromBit < KICAD_SCHEM_LOGICIM_TEST_BITS) && (psJoin->uiToBit < KICAD_SCHEM_LOGICIM_TEST_BITS));
			JoinKicadSchemRoots(&aiBits,
				FindKicadSchemRoot(&aiParents, (int)(uiTraces + apcPorts.Find(psJoin->pcFrom))) * KICAD_SCHEM_LOGICIM_TEST_BITS + (int)psJoin->uiFromBit,
				FindKicadSchemRoot(&aiParents, (int)(uiTraces + apcPorts.Find(psJoin->pcTo))) * KICAD_SCHEM_LOGICIM_TEST_BITS + (int)psJoin->uiToBit);
		}
		asJoins.Kill();
	}

	apcGroupNets.Init();
	for (i = 0; i < aiBits.NumElements(); i++)
	{
		apcGroupNets.Add(NULL);
	}
	aiSubnetGroups.Init();
	for (i = 0; i < pcConverter->NumTerminals(); i++)
	{
		aiSubnetGroups.Add(-1);
	}
	for (i = 0; i < pcConverter->NumTerminals(); i++)
	{
		psTerminal = pcConverter->GetTerminal(i);
		iGroup = FindKicadSchemRoot(&aiParents, (int)(uiTraces + apcPorts.Find(psTerminal->pcPortView)));

		//Nothing of another net, bit for bit (a bus's own terminals are many nets).
		pcNet = psTerminal->pcSubnet->GetNet();
		iBit = FindKicadSchemRoot(&aiBits, iGroup * KICAD_SCHEM_LOGICIM_TEST_BITS);
		if (!psTerminal->bBus)
		{
			if (apcGroupNets.GetPtr(iBit) == NULL)
			{
				apcGroupNets.SetPtr(iBit, pcNet);
			}
		}
		if ((!psTerminal->bBus) && (apcGroupNets.GetPtr(iBit) != pcNet))
		{
			//Names the two nets that are joined.
			szFirst.Init(pcConverter->GetCircuit()->GetTypeName());
			szFirst.Append(": ");
			szFirst.Append(apcGroupNets.GetPtr(iBit)->GetName());
			szThis.Init(pcNet->GetName());
			szThis.Append(" at ");
			AppendKicadSchemLogicimPort(&szThis, psTerminal->pcPortView);
			AssertString(szFirst.Text(), szThis.Text());
		}

		//All of its subnet: the first terminal of the subnet's group.
		for (j = 0; j < i; j++)
		{
			if (pcConverter->GetTerminal(j)->pcSubnet == psTerminal->pcSubnet)
			{
				break;
			}
		}
		uiSubnet = j;
		if (uiSubnet == i)
		{
			aiSubnetGroups.SetValue(i, iGroup);
		}
		else if (aiSubnetGroups.GetValue(uiSubnet) != iGroup)
		{
			//Names the two terminals that aren't wired together.
			szFirst.Init(pcConverter->GetCircuit()->GetTypeName());
			szFirst.Append(": ");
			AppendKicadSchemLogicimPort(&szFirst, pcConverter->GetTerminal(uiSubnet)->pcPortView);
			szThis.Init();
			AppendKicadSchemLogicimPort(&szThis, psTerminal->pcPortView);
			AssertString(szFirst.Text(), szThis.Text());
		}
	}

	aiSubnetGroups.Kill();
	apcGroupNets.Kill();
	aiBits.Kill();
	aiParents.Kill();
	apcPorts.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CComponentView* FindKicadSchemLogicimComponent(CCircuitView* pcCircuit, const char* szName)
{
	size	i;

	for (i = 0; i < pcCircuit->NumComponents(); i++)
	{
		if (StringCompare(pcCircuit->GetComponent(i)->GetName(), szName) == 0)
		{
			return pcCircuit->GetComponent(i);
		}
	}
	return NULL;
}


//////////////////////////////////////////////////////////////////////////
//
// Converts the schematic, checks its wiring and saves it as
// Output/name.xml, which must load back.
//
//////////////////////////////////////////////////////////////////////////
void AssertKicadSchemLogicimConverts(char* szName, size uiMinimumGates, size uiMinimumPlaceholders, const char* szFirstGate, char* szText = NULL, size uiPowers = 0, size uiSplitters = 0)
{
	CKicadSchemFile					cFile;
	CKicadSchemNetlist				cNetlist;
	CCircuitFonts					cFonts;
	CCircuitViews					cCircuits;
	CCircuitViews					cLoaded;
	CKicadSchemLogicimConverter		cConverter;
	CChars							szPath;
	CFileUtil						cFileUtil;
	Ptr<CFontFamily>				pFamily;
	CCircuitView*					pcLoaded;
	CChars							szUnconnected;
	size							i;
	SKicadSchemLogicimConnection*	psConnection;

	ObjectsInit();
	AssertTrue(LoadCircuitFonts(&cFonts, KICAD_SCHEM_LOGICIM_FONTS, CCO_Unknown));
	pFamily = cFonts.GetSansSerif();
	ORoot()->Add(pFamily);
	pFamily = cFonts.GetMonospaced();
	ORoot()->Add(pFamily);

	szPath.Init("Input" _FS_);
	szPath.Append(szName);
	szPath.Append(".kicad_sch");
	cFile.Init();
	if (szText == NULL)
	{
		AssertTrue(cFile.Load(szPath.Text()));
	}
	else
	{
		AssertTrue(cFile.Import(szText, strlen(szText), szPath.Text()));
	}
	cNetlist.Init(&cFile);
	AssertTrue(cNetlist.Build());

	cCircuits.Init();
	cConverter.Init(&cFile, &cNetlist, &cCircuits, &cFonts);
	AssertTrue(cConverter.Convert(szName));
	AssertTrue(cConverter.NumGates() >= uiMinimumGates);
	AssertTrue(cConverter.NumPlaceholders() >= uiMinimumPlaceholders);
	if (szText == NULL)
	{
		AssertTrue(cConverter.NumConnections() > 0);
	}
	AssertSize(0, cConverter.NumOverlaps());
	AssertSize(uiPowers, cConverter.NumPowers());
	AssertSize(uiSplitters, cConverter.NumSplitters());
	AssertTrue(cConverter.GetExcessKnotsAfter() <= cConverter.GetExcessKnotsBefore());
	if (szFirstGate != NULL)
	{
		AssertNotNull(FindKicadSchemLogicimComponent(cConverter.GetCircuit(), szFirstGate));
	}

	cFileUtil.MakeDir("Output");
	szPath.Kill();
	szPath.Init("Output" _FS_);
	szPath.Append(szName);
	szPath.Append(".xml");
	AssertTrue(SaveCircuitsFile(&cCircuits, cConverter.GetCircuit(), NULL, szPath.Text()));

	szUnconnected.Init();
	for (i = 0; i < cConverter.NumConnections(); i++)
	{
		psConnection = cConverter.GetConnection(i);
		if (!psConnection->bConnected)
		{
			AppendKicadSchemLogicimPort(&szUnconnected, cConverter.GetTerminal(psConnection->uiFrom)->pcPortView);
			szUnconnected.Append(" to ");
			AppendKicadSchemLogicimPort(&szUnconnected, cConverter.GetTerminal(psConnection->uiTo)->pcPortView);
			szUnconnected.Append("; ");
		}
	}
	AssertString("", szUnconnected.Text());
	szUnconnected.Kill();
	AssertSize(0, cConverter.NumUnconnected());
	AssertKicadSchemLogicimWired(&cConverter);

	cLoaded.Init();
	AssertTrue(LoadCircuitsFile(&cLoaded, szName, NULL, NULL, szPath.Text()));
	AssertSize(cCircuits.NumCircuits(), cLoaded.NumCircuits());
	pcLoaded = cLoaded.Get(szName);
	AssertNotNull(pcLoaded);
	AssertSize(cConverter.GetCircuit()->NumComponents(), pcLoaded->NumComponents());
	AssertSize(cConverter.GetCircuit()->NumTraces(), pcLoaded->NumTraces());
	cLoaded.Kill();

	cConverter.Kill();
	cCircuits.Kill();
	cNetlist.Kill();
	cFile.Kill();
	szPath.Kill();

	cFonts.Kill();
	ORoot()->RemoveAll();
	ObjectsFlush();
	ObjectsKill(false);
}


//////////////////////////////////////////////////////////////////////////
//
// How many of the element the converted Output/name.xml has.
//
//////////////////////////////////////////////////////////////////////////
void AssertKicadSchemLogicimElements(char* szName, char* szElement, int iExpected)
{
	CTextFile	cFile;
	CChars		szPath;
	CChars		szTag;
	int			iCount;
	char*		sz;

	szPath.Init("Output" _FS_);
	szPath.Append(szName);
	szPath.Append(".xml");
	cFile.Init();
	AssertTrue(cFile.Read(szPath.Text()));
	szTag.Init("<");
	szTag.Append(szElement);
	szTag.Append(' ');
	iCount = 0;
	for (sz = strstr(cFile.Text(), szTag.Text()); sz != NULL; sz = strstr(sz + 1, szTag.Text()))
	{
		iCount++;
	}
	AssertInt(iExpected, iCount);
	szTag.Kill();
	cFile.Kill();
	szPath.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestKicadSchemLogicimConvert(void)
{
	AssertKicadSchemLogicimConverts("Importer Test", 2, 0, "U1", gszKicadSchemTestFile, 1);
	AssertKicadSchemLogicimConverts("Netlist Test", 0, 1, NULL, gszKicadSchemNetlistTestFile, 1);
	AssertKicadSchemLogicimConverts("Bus Test", 0, 2, NULL, gszKicadSchemBusTestFile, 0, 3);
	AssertKicadSchemLogicimConverts("Clock Oscillator", 0, 3, NULL);
	AssertKicadSchemLogicimConverts("Clock Hold V1 to V2", 0, 2, NULL, NULL, 0, 1);
	AssertKicadSchemLogicimConverts("LSF0204", 0, 1, NULL);
	AssertKicadSchemLogicimConverts("LED Display", 0, 2, NULL);
	AssertKicadSchemLogicimConverts("LCD Dual 7 Segment Tester", 0, 1, NULL);
	AssertKicadSchemLogicimConverts("Power and Reset", 0, 1, NULL);
	AssertKicadSchemLogicimConverts("HCP65 MPU NMI", 10, 1, "IC8");
	AssertKicadSchemLogicimConverts("Triple MPU Clock Generator", 8, 1, NULL);
	AssertKicadSchemLogicimConverts("Flags Enable Interrupt", 0, 1, NULL, NULL, 0, 4);
	AssertKicadSchemLogicimConverts("UART Board", 0, 1, NULL, NULL, 0, 10);

	//A 74 series part drawn as units is units, and drawn whole is a package.
	AssertKicadSchemLogicimElements("HCP65 MPU NMI", "Logic74Unit", 15);
	AssertKicadSchemLogicimElements("HCP65 MPU NMI", "Logic74Package", 6);
	AssertKicadSchemLogicimElements("Flags Enable Interrupt", "Logic74Unit", 11);
	AssertKicadSchemLogicimElements("Flags Enable Interrupt", "Logic74Package", 3);
	AssertKicadSchemLogicimElements("Triple MPU Clock Generator", "Logic74Package", 3);
	AssertKicadSchemLogicimElements("Triple MPU Clock Generator", "Logic74Unit", 14);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestKicadSchemLogicim(void)
{
	BeginTests();
	DataIOInit();
	DataMemoryInit();

	TestKicadSchemLogicFunction();
	TestKicadSchemLogicimNames();
	TestKicadSchemSubnetGraph();
	TestKicadSchemLogicimConvert();

	DataMemoryKill();
	DataIOKill();
	TestStatistics();
}

