#include "BaseLib/StringHelper.h"
#include "BaseLib/TextFile.h"
#include "BaseLib/ArrayChars.h"
#include "KicadImporterLib/KicadSchemParser.h"
#include "KicadImporterLib/KicadSchemNetlist.h"
#include "TestLib/Assert.h"


//Two resistors and a symbol with a hidden power pin.  Wire A joins R1.1 and R2.1 at its ends.  Wire B crosses A
//without a junction, so they aren't joined; label X is on its end.  Wire C joins R1.2 and R3.2 at its ends and R2.2
//in its middle.  Wire D ends on C's middle and has another label X on its other end, so B, C and D are net X.  R3.1
//has a global label VCC, which is the net of the VCC power symbol and of U1's hidden VCC power input pin.
char gszKicadSchemNetlistTestFile[] =
	"(kicad_sch (version 20250114) (generator \"eeschema\") (uuid \"root\") (paper \"A4\")\n"
	"	(lib_symbols\n"
	"		(symbol \"Device:R\" (property \"Reference\" \"R\") (property \"Value\" \"R\")\n"
	"			(symbol \"R_1_1\"\n"
	"				(pin passive line (at 0 3.81 270) (length 1.27) (name \"~\") (number \"1\"))\n"
	"				(pin passive line (at 0 -3.81 90) (length 1.27) (name \"~\") (number \"2\"))))\n"
	"		(symbol \"Test:U\" (property \"Reference\" \"U\") (property \"Value\" \"U\")\n"
	"			(symbol \"U_1_1\"\n"
	"				(pin input line (at -5.08 0 0) (length 2.54) (name \"IN\") (number \"1\"))\n"
	"				(pin power_in line (at 0 5.08 270) (length 2.54) (hide yes) (name \"VCC\") (number \"2\"))))\n"
	"		(symbol \"power:VCC\" (power) (property \"Reference\" \"#PWR\") (property \"Value\" \"VCC\")\n"
	"			(symbol \"VCC_1_1\" (pin power_in line (at 0 0 90) (length 0) (hide yes) (name \"VCC\") (number \"1\")))))\n"
	"	(symbol (lib_id \"Device:R\") (at 50 50 0) (unit 1) (uuid \"r1\") (property \"Reference\" \"R1\") (property \"Value\" \"1k\"))\n"
	"	(symbol (lib_id \"Device:R\") (at 70 50 0) (unit 1) (uuid \"r2\") (property \"Reference\" \"R2\") (property \"Value\" \"1k\"))\n"
	"	(symbol (lib_id \"Device:R\") (at 90 50 0) (unit 1) (uuid \"r3\") (property \"Reference\" \"R3\") (property \"Value\" \"1k\"))\n"
	"	(symbol (lib_id \"Test:U\") (at 120 50 0) (unit 1) (uuid \"u1\") (property \"Reference\" \"U1\") (property \"Value\" \"U\"))\n"
	"	(symbol (lib_id \"power:VCC\") (at 100 40 0) (unit 1) (uuid \"p1\") (property \"Reference\" \"#PWR01\") (property \"Value\" \"VCC\"))\n"
	"	(wire (pts (xy 50 46.19) (xy 70 46.19)) (uuid \"wa\"))\n"
	"	(wire (pts (xy 60 40) (xy 60 60)) (uuid \"wb\"))\n"
	"	(wire (pts (xy 50 53.81) (xy 90 53.81)) (uuid \"wc\"))\n"
	"	(wire (pts (xy 80 53.81) (xy 80 65)) (uuid \"wd\"))\n"
	"	(bus (pts (xy 10 10) (xy 10 30)) (uuid \"b1\"))\n"
	"	(label \"X\" (at 60 60 0) (uuid \"l1\"))\n"
	"	(label \"X\" (at 80 65 0) (uuid \"l2\"))\n"
	"	(global_label \"VCC\" (shape input) (at 90 46.19 0) (uuid \"l3\"))\n"
	"	(no_connect (at 200 200) (uuid \"n1\"))\n"
	")\n";


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestKicadSchemNetlistHandmade(void)
{
	CKicadSchemFile		cFile;
	CKicadSchemNetlist	cNetlist;
	CKicadSchemNet*		pcNet;
	CKicadSchemSubnet*	pcSubnet;

	cFile.Init();
	AssertTrue(cFile.Import(gszKicadSchemNetlistTestFile, strlen(gszKicadSchemNetlistTestFile), "netlist.kicad_sch"));
	cNetlist.Init(&cFile);
	AssertTrue(cNetlist.Build());

	AssertSize(7, cNetlist.NumSubnets());
	AssertSize(4, cNetlist.NumNets());

	pcNet = cNetlist.GetPinNet("R1", "1");
	AssertNotNull(pcNet);
	AssertString("Net-(R1-Pad1)", pcNet->GetName());
	AssertInt(KSNNS_Pin, pcNet->GetNameSource());
	AssertSize(1, pcNet->NumSubnets());
	AssertSize(2, pcNet->NumPins());
	AssertTrue(pcNet == cNetlist.GetPinNet("R2", "1"));
	pcSubnet = cNetlist.GetPinSubnet("R1", "1");
	AssertSize(1, pcSubnet->NumWires());
	AssertString("wa", pcSubnet->GetWire(0)->GetUuid());

	pcNet = cNetlist.GetNet("X");
	AssertNotNull(pcNet);
	AssertInt(KSNNS_Local, pcNet->GetNameSource());
	AssertSize(2, pcNet->NumSubnets());
	AssertSize(3, pcNet->NumPins());
	AssertTrue(pcNet == cNetlist.GetPinNet("R1", "2"));
	AssertTrue(pcNet == cNetlist.GetPinNet("R2", "2"));
	AssertTrue(pcNet == cNetlist.GetPinNet("R3", "2"));
	pcSubnet = cNetlist.GetPinSubnet("R2", "2");
	AssertSize(2, pcSubnet->NumWires());
	AssertSize(1, pcSubnet->NumLabels());
	AssertTrue(pcSubnet->GetNet() == pcNet);

	pcNet = cNetlist.GetNet("VCC");
	AssertNotNull(pcNet);
	AssertInt(KSNNS_Global, pcNet->GetNameSource());
	AssertSize(3, pcNet->NumSubnets());
	AssertSize(3, pcNet->NumPins());
	AssertTrue(pcNet == cNetlist.GetPinNet("R3", "1"));
	AssertTrue(pcNet == cNetlist.GetPinNet("U1", "2"));
	AssertTrue(pcNet == cNetlist.GetPinNet("#PWR01", "1"));

	pcNet = cNetlist.GetPinNet("U1", "1");
	AssertNotNull(pcNet);
	AssertString("Net-(U1-Pad1)", pcNet->GetName());
	AssertSize(1, pcNet->NumPins());

	AssertNull(cNetlist.GetPinNet("R4", "1"));
	AssertNull(cNetlist.GetNet("Y"));

	cNetlist.Kill();
	cFile.Kill();
}


//Two placeholders U1 (pins 1 to 4 on its right) and U2 (pins 1 to 4 on its left) with the bus D[0..3] between them.
//U1's pins are wired to entries on the bus's left, labelled D0 to D3 from the top; U2's to entries on its right,
//labelled D3 to D0 from the top, so the bus crosses them over.  A second bus, unlabelled, has one entry on a wire
//labelled X.  Each D net is two subnets joined by the bus.
char gszKicadSchemBusTestFile[] =
	"(kicad_sch (version 20250114) (generator \"eeschema\") (uuid \"root\") (paper \"A4\")\n"
	"	(lib_symbols\n"
	"		(symbol \"Test:Four\" (property \"Reference\" \"U\") (property \"Value\" \"Four\")\n"
	"			(symbol \"Four_1_1\"\n"
	"				(pin passive line (at 5.08 2.54 180) (length 2.54) (name \"P1\") (number \"1\"))\n"
	"				(pin passive line (at 5.08 0 180) (length 2.54) (name \"P2\") (number \"2\"))\n"
	"				(pin passive line (at 5.08 -2.54 180) (length 2.54) (name \"P3\") (number \"3\"))\n"
	"				(pin passive line (at 5.08 -5.08 180) (length 2.54) (name \"P4\") (number \"4\"))))\n"
	"		(symbol \"Test:FourLeft\" (property \"Reference\" \"U\") (property \"Value\" \"FourLeft\")\n"
	"			(symbol \"FourLeft_1_1\"\n"
	"				(pin passive line (at -5.08 2.54 0) (length 2.54) (name \"P1\") (number \"1\"))\n"
	"				(pin passive line (at -5.08 0 0) (length 2.54) (name \"P2\") (number \"2\"))\n"
	"				(pin passive line (at -5.08 -2.54 0) (length 2.54) (name \"P3\") (number \"3\"))\n"
	"				(pin passive line (at -5.08 -5.08 0) (length 2.54) (name \"P4\") (number \"4\")))))\n"
	"	(symbol (lib_id \"Test:Four\") (at 50.8 50.8 0) (unit 1) (uuid \"u1\") (property \"Reference\" \"U1\") (property \"Value\" \"Four\"))\n"
	"	(symbol (lib_id \"Test:FourLeft\") (at 101.6 50.8 0) (unit 1) (uuid \"u2\") (property \"Reference\" \"U2\") (property \"Value\" \"FourLeft\"))\n"
	"	(wire (pts (xy 55.88 48.26) (xy 73.66 48.26)) (uuid \"w1\"))\n"
	"	(wire (pts (xy 55.88 50.8) (xy 73.66 50.8)) (uuid \"w2\"))\n"
	"	(wire (pts (xy 55.88 53.34) (xy 73.66 53.34)) (uuid \"w3\"))\n"
	"	(wire (pts (xy 55.88 55.88) (xy 73.66 55.88)) (uuid \"w4\"))\n"
	"	(wire (pts (xy 81.28 48.26) (xy 96.52 48.26)) (uuid \"w5\"))\n"
	"	(wire (pts (xy 81.28 50.8) (xy 96.52 50.8)) (uuid \"w6\"))\n"
	"	(wire (pts (xy 81.28 53.34) (xy 96.52 53.34)) (uuid \"w7\"))\n"
	"	(wire (pts (xy 81.28 55.88) (xy 96.52 55.88)) (uuid \"w8\"))\n"
	"	(bus (pts (xy 76.2 40.64) (xy 76.2 60.96)) (uuid \"b1\"))\n"
	"	(bus (pts (xy 76.2 40.64) (xy 78.74 40.64)) (uuid \"b2\"))\n"
	"	(bus (pts (xy 78.74 40.64) (xy 78.74 60.96)) (uuid \"b3\"))\n"
	"	(bus_entry (at 73.66 48.26) (size 2.54 2.54) (uuid \"e1\"))\n"
	"	(bus_entry (at 73.66 50.8) (size 2.54 2.54) (uuid \"e2\"))\n"
	"	(bus_entry (at 73.66 53.34) (size 2.54 2.54) (uuid \"e3\"))\n"
	"	(bus_entry (at 73.66 55.88) (size 2.54 2.54) (uuid \"e4\"))\n"
	"	(bus_entry (at 81.28 48.26) (size -2.54 2.54) (uuid \"e5\"))\n"
	"	(bus_entry (at 81.28 50.8) (size -2.54 2.54) (uuid \"e6\"))\n"
	"	(bus_entry (at 81.28 53.34) (size -2.54 2.54) (uuid \"e7\"))\n"
	"	(bus_entry (at 81.28 55.88) (size -2.54 2.54) (uuid \"e8\"))\n"
	"	(label \"D[0..3]\" (at 76.2 45.72 90) (uuid \"lb\"))\n"
	"	(label \"D0\" (at 60.96 48.26 0) (uuid \"l1\"))\n"
	"	(label \"D1\" (at 60.96 50.8 0) (uuid \"l2\"))\n"
	"	(label \"D2\" (at 60.96 53.34 0) (uuid \"l3\"))\n"
	"	(label \"D3\" (at 60.96 55.88 0) (uuid \"l4\"))\n"
	"	(label \"D3\" (at 88.9 48.26 0) (uuid \"l5\"))\n"
	"	(label \"D2\" (at 88.9 50.8 0) (uuid \"l6\"))\n"
	"	(label \"D1\" (at 88.9 53.34 0) (uuid \"l7\"))\n"
	"	(label \"D0\" (at 88.9 55.88 0) (uuid \"l8\"))\n"
	"	(bus (pts (xy 120 40) (xy 120 60)) (uuid \"b4\"))\n"
	"	(wire (pts (xy 122.54 47.46) (xy 130 47.46)) (uuid \"w9\"))\n"
	"	(bus_entry (at 120 45) (size 2.54 2.46) (uuid \"e9\"))\n"
	"	(label \"X\" (at 130 47.46 0) (uuid \"l9\"))\n"
	")\n";


//////////////////////////////////////////////////////////////////////////
//
// The bus wires that touch are one bus, named by its label, with the
// members its label names in order and the entries tapping it.  The
// unlabelled bus's member is its tap's net.
//
//////////////////////////////////////////////////////////////////////////
void TestKicadSchemNetlistBuses(void)
{
	CKicadSchemFile		cFile;
	CKicadSchemNetlist	cNetlist;
	CKicadSchemBus*		pcBus;
	SKicadSchemBusTap*	psTap;
	CArrayChars			aszMembers;
	size				i;

	cFile.Init();
	AssertTrue(cFile.Import(gszKicadSchemBusTestFile, strlen(gszKicadSchemBusTestFile), "bus.kicad_sch"));
	cNetlist.Init(&cFile);
	AssertTrue(cNetlist.Build());

	AssertSize(2, cNetlist.NumBuses());
	AssertSize(2, cNetlist.NumBusNets());
	pcBus = cNetlist.GetBus("D[0..3]");
	AssertNotNull(pcBus);
	AssertSize(3, pcBus->GetSubnet()->NumWires());
	AssertSize(1, pcBus->NumLabels());
	AssertSize(4, pcBus->NumMembers());
	AssertString("D0", pcBus->GetMember(0));
	AssertString("D3", pcBus->GetMember(3));
	AssertSize(2, pcBus->GetMemberIndex("D2"));
	AssertSize(8, pcBus->NumTaps());
	for (i = 0; i < pcBus->NumTaps(); i++)
	{
		psTap = pcBus->GetTap(i);
		AssertTrue(psTap->bVertical);
		AssertNotNull(psTap->pcMember->GetNet());
	}
	AssertString("D3", pcBus->GetTap(4)->pcMember->GetNet()->GetName());
	AssertDouble(78.74, pcBus->GetTap(4)->sBusPoint.fX, 6);
	AssertDouble(81.28, pcBus->GetTap(4)->sWirePoint.fX, 6);
	AssertTrue(pcBus->GetSubnet()->GetNet() == cNetlist.GetBusNet(0));
	AssertString("D[0..3]", cNetlist.GetBusNet(0)->GetName());
	AssertTrue(cNetlist.IsBusLabel(pcBus->GetLabel(0)));

	pcBus = cNetlist.GetBus(1);
	AssertNull(pcBus->GetName());
	AssertSize(1, pcBus->NumMembers());
	AssertString("X", pcBus->GetMember(0));
	AssertSize(2, cNetlist.GetNet("D0")->NumSubnets());
	AssertSize(2, cNetlist.GetNet("D0")->NumPins());

	aszMembers.Init();
	AssertTrue(ParseKicadSchemBusMembers("A[0..23]", &aszMembers));
	AssertSize(24, aszMembers.NumElements());
	AssertString("A23", aszMembers.GetText(23));
	aszMembers.ReInit();
	AssertTrue(ParseKicadSchemBusMembers("Red[7..5]", &aszMembers));
	AssertSize(3, aszMembers.NumElements());
	AssertString("Red7", aszMembers.GetText(0));
	AssertString("Red5", aszMembers.GetText(2));
	aszMembers.ReInit();
	AssertFalse(ParseKicadSchemBusMembers("TC_{0..3}", &aszMembers));
	AssertFalse(ParseKicadSchemBusMembers("D[0..7]x", &aszMembers));
	AssertFalse(ParseKicadSchemBusMembers("[0..7]", &aszMembers));
	AssertFalse(ParseKicadSchemBusMembers("D[a..7]", &aszMembers));
	AssertFalse(ParseKicadSchemBusMembers("D0", &aszMembers));
	AssertSize(0, aszMembers.NumElements());
	aszMembers.Kill();

	cNetlist.Kill();
	cFile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// The names sorted and joined by spaces.
//
//////////////////////////////////////////////////////////////////////////
void AppendSortedNames(CChars* psz, CArrayChars* paszNames)
{
	size	i;

	paszNames->QuickSort();
	for (i = 0; i < paszNames->NumElements(); i++)
	{
		if (i != 0)
		{
			psz->Append(' ');
		}
		psz->Append(paszNames->GetText(i));
	}
}


//////////////////////////////////////////////////////////////////////////
//
// The unique reference.pin of the net's pins, sorted and joined by
// spaces.  Power symbols aren't in KiCad's netlists.
//
//////////////////////////////////////////////////////////////////////////
void GetKicadSchemNetPinNames(CChars* psz, CKicadSchemFile* pcFile, CKicadSchemNet* pcNet)
{
	CArrayChars			aszPins;
	size				i;
	size				j;
	CKicadSchemSubnet*	pcSubnet;
	SKicadSchemNetPin*	psPin;
	CChars				szPin;

	aszPins.Init();
	for (i = 0; i < pcNet->NumSubnets(); i++)
	{
		pcSubnet = pcNet->GetSubnet(i);
		for (j = 0; j < pcSubnet->NumPins(); j++)
		{
			psPin = pcSubnet->GetPin(j);
			if (!pcFile->GetLibSymbol(psPin->pcSymbol)->IsPower())
			{
				szPin.Init(psPin->pcSymbol->GetReference());
				szPin.Append('.');
				szPin.Append(psPin->pcPin->GetNumber());
				aszPins.AddIfUnique(szPin.Text());
				szPin.Kill();
			}
		}
	}
	AppendSortedNames(psz, &aszPins);
	aszPins.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void GetKicadNetlistNodeNames(CChars* psz, CKicadSchemExpression* pcNet)
{
	CArrayChars				aszPins;
	size					i;
	CKicadSchemExpression*	pcNode;
	CChars					szPin;

	aszPins.Init();
	for (i = 0; i < pcNet->NumChildren(); i++)
	{
		pcNode = pcNet->GetChild(i);
		if (pcNode->Is("node"))
		{
			szPin.Init(pcNode->GetChildText("ref"));
			szPin.Append('.');
			szPin.Append(pcNode->GetChildText("pin"));
			aszPins.AddIfUnique(szPin.Text());
			szPin.Kill();
		}
	}
	AppendSortedNames(psz, &aszPins);
	aszPins.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
// Whether every part of the net is marked as not connected.
//
//////////////////////////////////////////////////////////////////////////
bool IsKicadSchemNetNoConnect(CKicadSchemNet* pcNet)
{
	size	i;

	for (i = 0; i < pcNet->NumSubnets(); i++)
	{
		if (!pcNet->GetSubnet(i)->IsNoConnect())
		{
			return false;
		}
	}
	return true;
}


//////////////////////////////////////////////////////////////////////////
//
// KiCad names local nets "/name" and global nets "name".  Nets it named
// from a pin can have any name here.
//
//////////////////////////////////////////////////////////////////////////
bool IsKicadSchemNetNamed(CKicadSchemNet* pcNet, char* szKicadName)
{
	CChars	szName;
	bool	bResult;

	if (szKicadName[0] == '/')
	{
		return (StringCompare(&szKicadName[1], pcNet->GetName()) == 0) && (pcNet->GetNameSource() == KSNNS_Local);
	}

	szName.Init(szKicadName);
	if (szName.StartsWith("Net-(") || szName.StartsWith("unconnected-("))
	{
		bResult = true;
	}
	else
	{
		bResult = (StringCompare(szKicadName, pcNet->GetName()) == 0) && (pcNet->GetNameSource() == KSNNS_Global);
	}
	szName.Kill();
	return bResult;
}


//////////////////////////////////////////////////////////////////////////
//
// Every net in the netlist kicad-cli exported from the schematic
// (sch export netlist --format kicadsexpr) is a net here with the same
// pins and name, and there are no others.  Nets are matched by their pins,
// not looked up by a pin, as an unannotated schematic has many "U?".  The
// schematic must have no sheets: kicad-cli
// follows them and the netlist here is of one sheet.  KiCad sometimes
// leaves out a pin with a no-connect flag on it (the resistor networks'
// unused pins in LED Display, but not Clock Oscillator's crystal pins), so
// a no-connected net here needn't be in KiCad's.
//
//////////////////////////////////////////////////////////////////////////
void AssertKicadSchemNetlistMatches(char* szName)
{
	CKicadSchemFile			cFile;
	CKicadSchemNetlist		cNetlist;
	CChars					szPath;
	CTextFile				cTextFile;
	CKicadSchemParser		cParser;
	CKicadSchemExpressions	cExpressions;
	CKicadSchemExpression*	pcNets;
	CKicadSchemExpression*	pcKicadNet;
	CKicadSchemExpression*	pcNode;
	CKicadSchemNet*			pcNet;
	char*					szNetName;
	CChars					szExpected;
	CChars					szActual;
	size					i;
	size					j;
	size					uiKicadNets;
	size					uiNets;
	CArrayChars				aszKicadNets;
	CArrayChars				aszNets;

	szPath.Init("Input" _FS_);
	szPath.Append(szName);
	szPath.Append(".kicad_sch");
	cFile.Init();
	AssertTrue(cFile.Load(szPath.Text()));
	cNetlist.Init(&cFile);
	AssertTrue(cNetlist.Build());

	szPath.Kill();
	szPath.Init("Input" _FS_);
	szPath.Append(szName);
	szPath.Append(".net");
	cTextFile.Init();
	AssertTrue(cTextFile.Read(szPath.Text()));
	cTextFile.PassifyNewlines();
	cExpressions.Init();
	AssertTrue(cParser.Init(cTextFile.Text(), cTextFile.Length(), szPath.Text(), &cExpressions));
	AssertTritrue(cParser.Parse());
	cParser.Kill();

	aszNets.Init();
	for (i = 0; i < cNetlist.NumNets(); i++)
	{
		GetKicadSchemNetPinNames(aszNets.Add(), &cFile, cNetlist.GetNet(i));
	}

	pcNets = cExpressions.GetRoot()->FindChild("nets");
	AssertNotNull(pcNets);
	aszKicadNets.Init();
	uiKicadNets = 0;
	for (i = 0; i < pcNets->NumChildren(); i++)
	{
		pcKicadNet = pcNets->GetChild(i);
		pcNode = pcKicadNet->FindChild("node");
		if (pcNode == NULL)
		{
			continue;
		}
		uiKicadNets++;

		szExpected.Init();
		GetKicadNetlistNodeNames(&szExpected, pcKicadNet);
		aszKicadNets.Add(szExpected.Text());
		szNetName = pcKicadNet->GetChildText("name");
		for (j = 0; j < cNetlist.NumNets(); j++)
		{
			if (aszNets.Get(j)->Equals(szExpected.Text()) && IsKicadSchemNetNamed(cNetlist.GetNet(j), szNetName))
			{
				break;
			}
		}
		if (j == cNetlist.NumNets())
		{
			//Shows the net here with the KiCad net's first pin.
			szActual.Init(szName);
			szActual.Append(' ');
			szActual.Append(szNetName);
			szActual.Append(": ");
			pcNet = cNetlist.GetPinNet(pcNode->GetChildText("ref"), pcNode->GetChildText("pin"));
			if (pcNet != NULL)
			{
				szActual.Append(pcNet->GetName());
				szActual.Append(": ");
				GetKicadSchemNetPinNames(&szActual, &cFile, pcNet);
			}
			szExpected.Insert(0, ": ");
			szExpected.Insert(0, szNetName);
			szExpected.Insert(0, ' ');
			szExpected.Insert(0, szName);
			AssertString(szExpected.Text(), szActual.Text());
		}
		szExpected.Kill();
	}

	uiNets = 0;
	for (i = 0; i < cNetlist.NumNets(); i++)
	{
		szActual.Init(aszNets.Get(i));
		if (!szActual.Empty())
		{
			if (aszKicadNets.Contains(szActual.Text()))
			{
				uiNets++;
			}
			else if (!IsKicadSchemNetNoConnect(cNetlist.GetNet(i)))
			{
				//Names the net KiCad doesn't have.
				szActual.Insert(0, ' ');
				szActual.Insert(0, szName);
				AssertString("", szActual.Text());
			}
		}
		szActual.Kill();
	}
	AssertSize(uiKicadNets, uiNets);
	aszKicadNets.Kill();
	aszNets.Kill();

	cExpressions.Kill();
	cTextFile.Kill();
	szPath.Kill();
	cNetlist.Kill();
	cFile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestKicadSchemNetlistKicad(void)
{
	AssertKicadSchemNetlistMatches("Clock Oscillator");
	AssertKicadSchemNetlistMatches("LED Display");
	AssertKicadSchemNetlistMatches("Clock Hold V1 to V2");
	AssertKicadSchemNetlistMatches("LSF0204");
	AssertKicadSchemNetlistMatches("Power and Reset");
	AssertKicadSchemNetlistMatches("HCP65 MPU NMI");
	AssertKicadSchemNetlistMatches("Triple MPU Clock Generator");
	AssertKicadSchemNetlistMatches("Flags Enable Interrupt");
	AssertKicadSchemNetlistMatches("UART Board");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestKicadSchemNetlist(void)
{
	BeginTests();

	TestKicadSchemNetlistHandmade();
	TestKicadSchemNetlistBuses();
	TestKicadSchemNetlistKicad();

	TestStatistics();
}

