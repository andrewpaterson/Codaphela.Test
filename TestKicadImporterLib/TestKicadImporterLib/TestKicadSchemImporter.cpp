#include "BaseLib/LogToMemory.h"
#include "KicadImporterLib/KicadSchemFile.h"
#include "TestLib/Assert.h"


char gszKicadSchemTestFile[] =
	"(kicad_sch\n"
	"	(version 20250114)\n"
	"	(generator \"eeschema\")\n"
	"	(generator_version \"9.0\")\n"
	"	(uuid \"root-uuid\")\n"
	"	(paper \"A4\")\n"
	"	(title_block (title \"Test\") (date \"2026-10-24\") (rev \"V1\") (company \"Codaphela\"))\n"
	"	(lib_symbols\n"
	"		(symbol \"74xx:74HC00\" (pin_names (offset 1.016)) (exclude_from_sim no) (in_bom yes) (on_board yes)\n"
	"			(property \"Reference\" \"U\" (at 0 1.27 0) (effects (font (size 1.27 1.27))))\n"
	"			(property \"Value\" \"74HC00\" (at 0 -1.27 0) (effects (font (size 1.27 1.27)) (hide yes)))\n"
	"			(symbol \"74HC00_0_1\" (polyline (pts (xy -3.81 3.81) (xy -3.81 -3.81))))\n"
	"			(symbol \"74HC00_1_1\"\n"
	"				(pin input line (at -7.62 2.54 0) (length 7.62) (name \"~\" (effects (font (size 1.27 1.27)))) (number \"1\" (effects (font (size 1.27 1.27)))))\n"
	"				(pin input line (at -7.62 -2.54 0) (length 7.62) (name \"~\") (number \"2\"))\n"
	"				(pin output inverted (at 7.62 0 180) (length 7.62) (name \"~\") (number \"3\")))\n"
	"			(symbol \"74HC00_2_1\"\n"
	"				(pin input line (at -7.62 2.54 0) (length 7.62) (name \"~\") (number \"4\"))\n"
	"				(pin input line (at -7.62 -2.54 0) (length 7.62) (name \"~\") (number \"5\"))\n"
	"				(pin output inverted (at 7.62 0 180) (length 7.62) (name \"~\") (number \"6\")))\n"
	"			(symbol \"74HC00_5_0\"\n"
	"				(pin power_in line (at 0 12.7 270) (length 5.08) (hide yes) (name \"VCC\") (number \"14\"))\n"
	"				(pin power_in line (at 0 -12.7 90) (length 5.08) (hide yes) (name \"GND\") (number \"7\"))))\n"
	"		(symbol \"GND_1\" (power) (pin_numbers (hide yes)) (pin_names (offset 0) (hide yes)) (in_bom yes) (on_board yes)\n"
	"			(property \"Reference\" \"#PWR\" (at 0 -6.35 0) (effects (font (size 1.27 1.27)) (hide yes)))\n"
	"			(property \"Value\" \"GND\" (at 0 -3.81 0) (effects (font (size 1.27 1.27))))\n"
	"			(symbol \"GND_1_1_1\" (pin power_in line (at 0 0 270) (length 0) (name \"GND\") (number \"1\")))))\n"
	"	(symbol (lib_id \"74xx:74HC00\") (at 100 50 0) (unit 1) (body_style 1) (in_bom yes) (on_board yes) (dnp no) (uuid \"u1a\")\n"
	"		(property \"Reference\" \"U1\" (at 100 45 0) (effects (font (size 1.27 1.27))))\n"
	"		(property \"Value\" \"74HC00\" (at 100 55 0) (hide yes) (effects (font (size 1.27 1.27))))\n"
	"		(pin \"1\" (uuid \"pin-uuid\"))\n"
	"		(instances (project \"Test\" (path \"/root-uuid\" (reference \"U1\") (unit 1)))))\n"
	"	(symbol (lib_id \"74xx:74HC00\") (at 120 50 90) (mirror x) (unit 2) (convert 1) (in_bom no) (dnp yes) (uuid \"u1b\")\n"
	"		(property \"Reference\" \"U1\" (at 0 0 0)))\n"
	"	(symbol (lib_id \"power:GND\") (lib_name \"GND_1\") (at 100 70 0) (unit 1) (uuid \"g1\")\n"
	"		(property \"Reference\" \"#PWR01\" (at 100 76 0) (effects (font (size 1.27 1.27)) (hide yes)))\n"
	"		(property \"Value\" \"GND\" (at 100 74 0)))\n"
	"	(wire (pts (xy 92.38 47.46) (xy 80 47.46)) (stroke (width 0) (type default)) (uuid \"w1\"))\n"
	"	(bus (pts (xy 10 10) (xy 10 30)) (stroke (width 0) (type default)) (uuid \"b1\"))\n"
	"	(junction (at 80 47.46) (diameter 0) (color 0 0 0 0) (uuid \"j1\"))\n"
	"	(no_connect (at 92.38 52.54) (uuid \"n1\"))\n"
	"	(bus_entry (at 10 20) (size 2.54 2.54) (stroke (width 0) (type default)) (uuid \"e1\"))\n"
	"	(label \"CLK\" (at 80 47.46 0) (fields_autoplaced yes) (effects (font (size 1.27 1.27)) (justify left bottom)) (uuid \"l1\"))\n"
	"	(global_label \"RESET\" (shape input) (at 50 60 180) (effects (font (size 1.27 1.27))) (uuid \"l2\"))\n"
	"	(hierarchical_label \"D0\" (shape bidirectional) (at 60 60 0) (uuid \"l3\"))\n"
	"	(sheet (at 150 100) (size 30 20) (fields_autoplaced yes) (stroke (width 0.1524) (type solid)) (fill (color 0 0 0 0.0000)) (uuid \"s1\")\n"
	"		(property \"Sheetname\" \"LED Display\" (at 150 99 0))\n"
	"		(property \"Sheetfile\" \"LED Display.kicad_sch\" (at 150 121 0))\n"
	"		(pin \"D0\" bidirectional (at 150 105 180) (uuid \"p1\"))\n"
	"		(pin \"CLK\" input (at 180 105 0) (uuid \"p2\")))\n"
	"	(text \"Ignored\" (at 0 0 0))\n"
	"	(sheet_instances (path \"/\" (page \"1\")))\n"
	")\n";


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertKicadSchemPoint(float64 fX, float64 fY, SKicadSchemPoint* psPoint)
{
	AssertDouble(fX, psPoint->fX, 6);
	AssertDouble(fY, psPoint->fY, 6);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertKicadSchemImportError(char* szText, char* szExpectedError)
{
	CKicadSchemFile		cFile;
	CLogToMemory		cMemoryLog;
	char				szLogText[1024];
	bool				bResult;

	cMemoryLog.Start(true);
	cFile.Init();
	bResult = cFile.Import(szText, strlen(szText), "error.kicad_sch");
	cFile.Kill();
	cMemoryLog.Stop(szLogText, 1024);

	AssertFalse(bResult);
	AssertTrue(strstr(szLogText, szExpectedError) != NULL);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestKicadSchemImporterHeader(void)
{
	CKicadSchemFile	cFile;

	cFile.Init();
	AssertTrue(cFile.Import(gszKicadSchemTestFile, strlen(gszKicadSchemTestFile), "Path" _FS_ "test.kicad_sch"));

	AssertString("test.kicad_sch", cFile.GetFileName());
	AssertInt(20250114, cFile.GetVersion());
	AssertString("eeschema", cFile.GetGenerator());
	AssertString("9.0", cFile.GetGeneratorVersion());
	AssertString("root-uuid", cFile.GetUuid());
	AssertString("A4", cFile.GetPaper());
	AssertString("Test", cFile.GetTitle());
	AssertString("2026-10-24", cFile.GetDate());
	AssertString("V1", cFile.GetRevision());
	AssertString("Codaphela", cFile.GetCompany());

	AssertSize(2, cFile.NumLibSymbols());
	AssertSize(3, cFile.NumSymbols());
	AssertSize(2, cFile.NumWires());
	AssertSize(1, cFile.NumJunctions());
	AssertSize(1, cFile.NumNoConnects());
	AssertSize(1, cFile.NumBusEntries());
	AssertSize(3, cFile.NumLabels());
	AssertSize(1, cFile.NumSheets());

	cFile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestKicadSchemImporterLibSymbols(void)
{
	CKicadSchemFile			cFile;
	CKicadSchemLibSymbol*	pcLibSymbol;
	CKicadSchemLibPin*		pcPin;
	CKicadSchemProperty*	pcProperty;

	cFile.Init();
	AssertTrue(cFile.Import(gszKicadSchemTestFile, strlen(gszKicadSchemTestFile), "test.kicad_sch"));

	pcLibSymbol = cFile.GetLibSymbol("74xx:74HC00");
	AssertNotNull(pcLibSymbol);
	AssertFalse(pcLibSymbol->IsPower());
	AssertFalse(pcLibSymbol->ArePinNamesHidden());
	AssertFalse(pcLibSymbol->ArePinNumbersHidden());
	AssertInt(5, pcLibSymbol->NumUnits());
	AssertSize(8, pcLibSymbol->NumPins());
	AssertSize(2, pcLibSymbol->GetProperties()->NumProperties());

	pcProperty = pcLibSymbol->GetProperties()->Get("Value");
	AssertString("74HC00", pcProperty->GetValue());
	AssertTrue(pcProperty->IsHidden());
	AssertKicadSchemPoint(0, -1.27, pcProperty->GetPosition());
	AssertFalse(pcLibSymbol->GetProperties()->Get("Reference")->IsHidden());

	pcPin = pcLibSymbol->GetPin((size)0);
	AssertInt(KSPT_Input, pcPin->GetType());
	AssertString("line", pcPin->GetGraphicStyle());
	AssertString("~", pcPin->GetName());
	AssertString("1", pcPin->GetNumber());
	AssertKicadSchemPoint(-7.62, 2.54, pcPin->GetPosition());
	AssertDouble(0.0, pcPin->GetAngle(), 6);
	AssertDouble(7.62, pcPin->GetLength(), 6);
	AssertInt(1, pcPin->GetUnit());
	AssertInt(1, pcPin->GetBodyStyle());
	AssertFalse(pcPin->IsHidden());

	pcPin = pcLibSymbol->GetPin("3", 1, 1);
	AssertNotNull(pcPin);
	AssertInt(KSPT_Output, pcPin->GetType());
	AssertString("inverted", pcPin->GetGraphicStyle());
	AssertDouble(180.0, pcPin->GetAngle(), 6);

	AssertNull(pcLibSymbol->GetPin("4", 1, 1));
	AssertNotNull(pcLibSymbol->GetPin("4", 2, 1));

	//Unit 5 body style 0 is on unit 5 of either body style.
	pcPin = pcLibSymbol->GetPin("14", 5, 2);
	AssertNotNull(pcPin);
	AssertInt(KSPT_PowerIn, pcPin->GetType());
	AssertString("VCC", pcPin->GetName());
	AssertTrue(pcPin->IsHidden());
	AssertInt(5, pcPin->GetUnit());
	AssertInt(0, pcPin->GetBodyStyle());
	AssertNull(pcLibSymbol->GetPin("14", 1, 1));

	pcLibSymbol = cFile.GetLibSymbol("GND_1");
	AssertNotNull(pcLibSymbol);
	AssertTrue(pcLibSymbol->IsPower());
	AssertTrue(pcLibSymbol->ArePinNamesHidden());
	AssertTrue(pcLibSymbol->ArePinNumbersHidden());
	AssertInt(1, pcLibSymbol->NumUnits());
	AssertSize(1, pcLibSymbol->NumPins());

	AssertNull(cFile.GetLibSymbol("power:GND"));

	cFile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestKicadSchemImporterSymbols(void)
{
	CKicadSchemFile				cFile;
	CKicadSchemSymbol*			pcSymbol;
	CKicadSchemLibSymbol*		pcLibSymbol;
	CKicadSchemSymbolInstance*	pcInstance;
	SKicadSchemPoint			sPosition;

	cFile.Init();
	AssertTrue(cFile.Import(gszKicadSchemTestFile, strlen(gszKicadSchemTestFile), "test.kicad_sch"));

	pcSymbol = cFile.GetSymbol((size)0);
	AssertString("74xx:74HC00", pcSymbol->GetLibId());
	AssertString("", pcSymbol->GetLibName());
	AssertString("74xx:74HC00", pcSymbol->GetLibSymbolName());
	AssertString("u1a", pcSymbol->GetUuid());
	AssertString("U1", pcSymbol->GetReference());
	AssertString("74HC00", pcSymbol->GetValue());
	AssertKicadSchemPoint(100, 50, pcSymbol->GetPosition());
	AssertDouble(0.0, pcSymbol->GetAngle(), 6);
	AssertInt(KSM_None, pcSymbol->GetMirror());
	AssertInt(1, pcSymbol->GetUnit());
	AssertInt(1, pcSymbol->GetBodyStyle());
	AssertTrue(pcSymbol->IsInBom());
	AssertTrue(pcSymbol->IsOnBoard());
	AssertFalse(pcSymbol->IsDoNotPopulate());
	AssertTrue(pcSymbol->GetProperties()->Get("Value")->IsHidden());
	AssertFalse(pcSymbol->GetProperties()->Get("Reference")->IsHidden());

	AssertSize(1, pcSymbol->NumInstances());
	pcInstance = pcSymbol->GetInstance(0);
	AssertString("Test", pcInstance->GetProject());
	AssertString("/root-uuid", pcInstance->GetPath());
	AssertString("U1", pcInstance->GetReference());
	AssertInt(1, pcInstance->GetUnit());

	pcLibSymbol = cFile.GetLibSymbol(pcSymbol);
	AssertNotNull(pcLibSymbol);
	AssertTrue(cFile.GetPinPosition(&sPosition, pcSymbol, pcLibSymbol->GetPin("1", 1, 1)));
	AssertKicadSchemPoint(92.38, 47.46, &sPosition);
	AssertTrue(cFile.GetPinPosition(&sPosition, pcSymbol, pcLibSymbol->GetPin("2", 1, 1)));
	AssertKicadSchemPoint(92.38, 52.54, &sPosition);
	AssertTrue(cFile.GetPinPosition(&sPosition, pcSymbol, pcLibSymbol->GetPin("3", 1, 1)));
	AssertKicadSchemPoint(107.62, 50, &sPosition);

	pcSymbol = cFile.GetSymbol(1);
	AssertString("u1b", pcSymbol->GetUuid());
	AssertDouble(90.0, pcSymbol->GetAngle(), 6);
	AssertInt(KSM_X, pcSymbol->GetMirror());
	AssertInt(2, pcSymbol->GetUnit());
	AssertFalse(pcSymbol->IsInBom());
	AssertTrue(pcSymbol->IsDoNotPopulate());
	AssertSize(0, pcSymbol->NumInstances());

	//Rotated anticlockwise the gate's inputs are below it.  Flipped top to bottom they are above it.
	AssertTrue(cFile.GetPinPosition(&sPosition, pcSymbol, pcLibSymbol->GetPin("4", 2, 1)));
	AssertKicadSchemPoint(117.46, 42.38, &sPosition);
	AssertTrue(cFile.GetPinPosition(&sPosition, pcSymbol, pcLibSymbol->GetPin("6", 2, 1)));
	AssertKicadSchemPoint(120, 57.62, &sPosition);

	pcSymbol = cFile.GetSymbol("#PWR01");
	AssertNotNull(pcSymbol);
	AssertString("power:GND", pcSymbol->GetLibId());
	AssertString("GND_1", pcSymbol->GetLibName());
	AssertString("GND_1", pcSymbol->GetLibSymbolName());
	AssertNotNull(cFile.GetLibSymbol(pcSymbol));
	AssertTrue(cFile.GetLibSymbol(pcSymbol)->IsPower());

	AssertNull(cFile.GetSymbol("U2"));
	AssertString("u1a", cFile.GetSymbol("U1")->GetUuid());
	AssertString("g1", cFile.GetSymbolByUuid("g1")->GetUuid());

	cFile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestKicadSchemImporterTransforms(void)
{
	CKicadSchemTransform	cTransform;
	SKicadSchemPoint		sLibrary;
	SKicadSchemPoint		sSheet;

	//A pin above the symbol's centre in the library, where Y is up.
	sLibrary.Init(0, 3.81);

	AssertTrue(cTransform.Init(0, KSM_None));
	cTransform.Transform(&sSheet, &sLibrary);
	AssertKicadSchemPoint(0, -3.81, &sSheet);

	AssertTrue(cTransform.Init(90, KSM_None));
	cTransform.Transform(&sSheet, &sLibrary);
	AssertKicadSchemPoint(-3.81, 0, &sSheet);

	AssertTrue(cTransform.Init(180, KSM_None));
	cTransform.Transform(&sSheet, &sLibrary);
	AssertKicadSchemPoint(0, 3.81, &sSheet);

	AssertTrue(cTransform.Init(270, KSM_None));
	cTransform.Transform(&sSheet, &sLibrary);
	AssertKicadSchemPoint(3.81, 0, &sSheet);

	AssertTrue(cTransform.Init(0, KSM_X));
	cTransform.Transform(&sSheet, &sLibrary);
	AssertKicadSchemPoint(0, 3.81, &sSheet);

	AssertTrue(cTransform.Init(90, KSM_X));
	cTransform.Transform(&sSheet, &sLibrary);
	AssertKicadSchemPoint(-3.81, 0, &sSheet);

	AssertTrue(cTransform.Init(90, KSM_Y));
	cTransform.Transform(&sSheet, &sLibrary);
	AssertKicadSchemPoint(3.81, 0, &sSheet);

	//A pin to the right.
	sLibrary.Init(2.54, 0);

	AssertTrue(cTransform.Init(0, KSM_Y));
	cTransform.Transform(&sSheet, &sLibrary);
	AssertKicadSchemPoint(-2.54, 0, &sSheet);

	AssertTrue(cTransform.Init(90, KSM_None));
	cTransform.Transform(&sSheet, &sLibrary);
	AssertKicadSchemPoint(0, -2.54, &sSheet);

	AssertTrue(cTransform.Init(90, KSM_X));
	cTransform.Transform(&sSheet, &sLibrary);
	AssertKicadSchemPoint(0, 2.54, &sSheet);

	AssertTrue(cTransform.Init(270, KSM_Y));
	cTransform.Transform(&sSheet, &sLibrary);
	AssertKicadSchemPoint(0, 2.54, &sSheet);

	AssertFalse(cTransform.Init(45, KSM_None));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestKicadSchemImporterWiring(void)
{
	CKicadSchemFile			cFile;
	CKicadSchemWire*		pcWire;
	CKicadSchemLabel*		pcLabel;
	CKicadSchemBusEntry*	pcBusEntry;
	SKicadSchemPoint		sPoint;

	cFile.Init();
	AssertTrue(cFile.Import(gszKicadSchemTestFile, strlen(gszKicadSchemTestFile), "test.kicad_sch"));

	pcWire = cFile.GetWire(0);
	AssertFalse(pcWire->IsBus());
	AssertString("w1", pcWire->GetUuid());
	AssertKicadSchemPoint(92.38, 47.46, pcWire->GetStart());
	AssertKicadSchemPoint(80, 47.46, pcWire->GetEnd());

	sPoint.Init(80, 47.46);
	AssertTrue(pcWire->IsEnd(&sPoint));
	sPoint.Init(85.0004, 47.46);
	AssertFalse(pcWire->IsEnd(&sPoint));
	AssertTrue(pcWire->Contains(&sPoint));
	sPoint.Init(85, 47.47);
	AssertFalse(pcWire->Contains(&sPoint));
	sPoint.Init(79, 47.46);
	AssertFalse(pcWire->Contains(&sPoint));

	pcWire = cFile.GetWire(1);
	AssertTrue(pcWire->IsBus());
	sPoint.Init(10, 20);
	AssertTrue(pcWire->Contains(&sPoint));

	AssertKicadSchemPoint(80, 47.46, cFile.GetJunction(0)->GetPosition());
	AssertDouble(0, cFile.GetJunction(0)->GetDiameter(), 6);
	AssertKicadSchemPoint(92.38, 52.54, cFile.GetNoConnect(0)->GetPosition());

	pcBusEntry = cFile.GetBusEntry(0);
	AssertKicadSchemPoint(10, 20, pcBusEntry->GetPosition());
	AssertKicadSchemPoint(2.54, 2.54, pcBusEntry->GetSize());
	pcBusEntry->GetEnd(&sPoint);
	AssertKicadSchemPoint(12.54, 22.54, &sPoint);

	pcLabel = cFile.GetLabel(0);
	AssertInt(KSLT_Local, pcLabel->GetType());
	AssertString("CLK", pcLabel->GetText());
	AssertKicadSchemPoint(80, 47.46, pcLabel->GetPosition());
	AssertInt(KSLS_None, pcLabel->GetShape());

	pcLabel = cFile.GetLabel(1);
	AssertInt(KSLT_Global, pcLabel->GetType());
	AssertString("RESET", pcLabel->GetText());
	AssertDouble(180.0, pcLabel->GetAngle(), 6);
	AssertInt(KSLS_Input, pcLabel->GetShape());

	pcLabel = cFile.GetLabel(2);
	AssertInt(KSLT_Hierarchical, pcLabel->GetType());
	AssertString("D0", pcLabel->GetText());
	AssertInt(KSLS_Bidirectional, pcLabel->GetShape());

	cFile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestKicadSchemImporterSheets(void)
{
	CKicadSchemFile			cFile;
	CKicadSchemSheet*		pcSheet;
	CKicadSchemSheetPin*	pcPin;

	cFile.Init();
	AssertTrue(cFile.Import(gszKicadSchemTestFile, strlen(gszKicadSchemTestFile), "test.kicad_sch"));

	pcSheet = cFile.GetSheet(0);
	AssertString("s1", pcSheet->GetUuid());
	AssertKicadSchemPoint(150, 100, pcSheet->GetPosition());
	AssertKicadSchemPoint(30, 20, pcSheet->GetSize());
	AssertString("LED Display", pcSheet->GetSheetName());
	AssertString("LED Display.kicad_sch", pcSheet->GetSheetFile());
	AssertSize(2, pcSheet->NumPins());

	pcPin = pcSheet->GetPin("CLK");
	AssertNotNull(pcPin);
	AssertInt(KSLS_Input, pcPin->GetShape());
	AssertKicadSchemPoint(180, 105, pcPin->GetPosition());
	AssertDouble(0, pcPin->GetAngle(), 6);

	pcPin = pcSheet->GetPin((size)0);
	AssertString("D0", pcPin->GetName());
	AssertInt(KSLS_Bidirectional, pcPin->GetShape());
	AssertDouble(180, pcPin->GetAngle(), 6);
	AssertNull(pcSheet->GetPin("D1"));

	cFile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestKicadSchemImporterKicad6(void)
{
	CKicadSchemFile			cFile;
	CKicadSchemSymbol*		pcSymbol;
	CKicadSchemLibSymbol*	pcLibSymbol;
	CKicadSchemSheet*		pcSheet;
	char*					szText;

	//KiCad 6: bare hide flags, unquoted uuids and generator, (convert), "Sheet name" and a root (symbol_instances).
	szText =
		"(kicad_sch (version 20211123) (generator eeschema)\n"
		"  (uuid 42f3f274-92b6-4722-96f2-06ebe96b181d)\n"
		"  (paper \"A4\")\n"
		"  (lib_symbols\n"
		"    (symbol \"power:PWR_FLAG\" (power) (pin_numbers hide) (pin_names (offset 0) hide) (in_bom yes) (on_board yes)\n"
		"      (property \"Reference\" \"#FLG\" (id 0) (at 0 1.905 0)\n"
		"        (effects (font (size 1.27 1.27)) hide)\n"
		"      )\n"
		"      (symbol \"PWR_FLAG_0_1\" (pin power_out line (at 0 0 90) (length 0) hide\n"
		"          (name \"pwr\" (effects (font (size 1.27 1.27))))\n"
		"          (number \"1\" (effects (font (size 1.27 1.27))))))))\n"
		"  (symbol (lib_id \"power:PWR_FLAG\") (at 48.26 86.36 90) (unit 1) (convert 2)\n"
		"    (in_bom yes) (on_board yes) (fields_autoplaced)\n"
		"    (uuid 232ee51f-d92b-4256-b318-1ba4ea84d095)\n"
		"    (property \"Reference\" \"#FLG?\" (id 0) (at 46.355 86.36 0)\n"
		"      (effects (font (size 1.27 1.27)) hide)))\n"
		"  (sheet (at 10 10) (size 20 20) (uuid 11111111-0000-0000-0000-000000000000)\n"
		"    (property \"Sheet name\" \"Sub\" (id 0) (at 10 9 0))\n"
		"    (property \"Sheet file\" \"Sub.kicad_sch\" (id 1) (at 10 31 0)))\n"
		"  (symbol_instances\n"
		"    (path \"/232ee51f-d92b-4256-b318-1ba4ea84d095\"\n"
		"      (reference \"#FLG01\") (unit 1) (value \"PWR_FLAG\") (footprint \"\"))\n"
		"    (path \"/11111111-0000-0000-0000-000000000000/99999999-0000-0000-0000-000000000000\"\n"
		"      (reference \"R1\") (unit 1) (value \"10K\") (footprint \"\"))))\n";

	cFile.Init();
	AssertTrue(cFile.Import(szText, strlen(szText), "old.kicad_sch"));

	AssertInt(20211123, cFile.GetVersion());
	AssertString("eeschema", cFile.GetGenerator());
	AssertString("", cFile.GetGeneratorVersion());
	AssertString("42f3f274-92b6-4722-96f2-06ebe96b181d", cFile.GetUuid());
	AssertString("", cFile.GetTitle());

	pcLibSymbol = cFile.GetLibSymbol("power:PWR_FLAG");
	AssertTrue(pcLibSymbol->IsPower());
	AssertTrue(pcLibSymbol->ArePinNumbersHidden());
	AssertTrue(pcLibSymbol->ArePinNamesHidden());
	AssertTrue(pcLibSymbol->GetProperties()->Get("Reference")->IsHidden());
	AssertTrue(pcLibSymbol->GetPin((size)0)->IsHidden());
	AssertInt(KSPT_PowerOut, pcLibSymbol->GetPin((size)0)->GetType());
	AssertInt(0, pcLibSymbol->GetPin((size)0)->GetUnit());

	pcSymbol = cFile.GetSymbol((size)0);
	AssertString("232ee51f-d92b-4256-b318-1ba4ea84d095", pcSymbol->GetUuid());
	AssertInt(2, pcSymbol->GetBodyStyle());
	AssertTrue(pcSymbol->GetProperties()->Get("Reference")->IsHidden());
	AssertSize(1, pcSymbol->NumInstances());
	AssertString("#FLG01", pcSymbol->GetInstance(0)->GetReference());
	AssertString("", pcSymbol->GetInstance(0)->GetProject());
	AssertString("#FLG?", pcSymbol->GetReference());

	pcSheet = cFile.GetSheet(0);
	AssertString("Sub", pcSheet->GetSheetName());
	AssertString("Sub.kicad_sch", pcSheet->GetSheetFile());

	cFile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestKicadSchemImporterErrors(void)
{
	AssertKicadSchemImportError("(kicad_pcb (version 20250114))", "error.kicad_sch(1): Expected (kicad_sch at the start of the file.");
	AssertKicadSchemImportError("(kicad_sch (generator \"eeschema\"))", "Expected (version yyyymmdd) in (kicad_sch.");
	AssertKicadSchemImportError("(kicad_sch (version 20250114)\n(symbol (at 1 2 0)))", "error.kicad_sch(2): Expected (lib_id \"library:name\") in (symbol.");
	AssertKicadSchemImportError("(kicad_sch (version 20250114) (symbol (lib_id \"a:b\")))", "Expected (at x y angle) in (symbol.");
	AssertKicadSchemImportError("(kicad_sch (version 20250114) (symbol (lib_id \"a:b\") (at 1 2 0) (mirror z)))", "Expected (mirror x) or (mirror y) in (symbol.");
	AssertKicadSchemImportError("(kicad_sch (version 20250114) (wire (pts (xy 1 2))))", "Expected (pts (xy x1 y1) (xy x2 y2)) in a wire or bus.");
	AssertKicadSchemImportError("(kicad_sch (version 20250114) (wire (pts (xy 1 2) (xy 1 two))))", "Expected (pts (xy x1 y1) (xy x2 y2)) in a wire or bus.");
	AssertKicadSchemImportError("(kicad_sch (version 20250114) (junction (uuid \"j\")))", "Expected (at x y) in (junction.");
	AssertKicadSchemImportError("(kicad_sch (version 20250114) (label (at 1 2 0)))", "Expected the label's text.");
	AssertKicadSchemImportError("(kicad_sch (version 20250114) (sheet (at 1 2)))", "Expected (at x y) and (size width height) in (sheet.");
	AssertKicadSchemImportError("(kicad_sch (version 20250114) (lib_symbols (symbol \"a:b\" (symbol \"b_1\"))))", "Expected a library sub-symbol name ending in _<unit>_<body style>.");
	AssertKicadSchemImportError("(kicad_sch (version 20250114) (lib_symbols (symbol \"a:b\" (symbol \"b_1_1\" (pin sideways line (at 0 0 0)))))) ", "Unknown pin electrical type.");
	AssertKicadSchemImportError("(kicad_sch (version 20250114) (lib_symbols (symbol \"a:b\" (symbol \"b_1_1\" (pin input line)))))", "Expected (at x y angle) in (pin.");
	AssertKicadSchemImportError("(kicad_sch (version 20250114) (symbol (lib_id \"a:b\") (at 1 2 0) (property \"Reference\")))", "Expected a name and a value in (property.");
	AssertKicadSchemImportError("(kicad_sch (version 20250114)", "Could not parse KiCad schematic file [error.kicad_sch].");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestKicadSchemImporter(void)
{
	BeginTests();

	TestKicadSchemImporterHeader();
	TestKicadSchemImporterLibSymbols();
	TestKicadSchemImporterSymbols();
	TestKicadSchemImporterTransforms();
	TestKicadSchemImporterWiring();
	TestKicadSchemImporterSheets();
	TestKicadSchemImporterKicad6();
	TestKicadSchemImporterErrors();

	TestStatistics();
}

