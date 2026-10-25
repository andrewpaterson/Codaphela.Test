#include "BaseLib/LogToMemory.h"
#include "KicadImporterLib/KicadSchemParser.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
TRISTATE ParseKicadSchemText(char* szText, CKicadSchemExpressions* pcExpressions)
{
	CKicadSchemParser	cParser;
	TRISTATE			tResult;

	cParser.Init(szText, strlen(szText), "none.kicad_sch", pcExpressions);
	tResult = cParser.Parse();
	cParser.Kill();
	return tResult;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertKicadSchemParseError(char* szText, char* szExpectedError)
{
	CKicadSchemExpressions	cExpressions;
	CLogToMemory			cMemoryLog;
	char					szLogText[1024];
	TRISTATE				tResult;

	cMemoryLog.Start(true);
	cExpressions.Init();
	tResult = ParseKicadSchemText(szText, &cExpressions);
	cExpressions.Kill();
	cMemoryLog.Stop(szLogText, 1024);

	AssertTrierror(tResult);
	AssertTrue(strstr(szLogText, szExpectedError) != NULL);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestKicadSchemParserLists(void)
{
	CKicadSchemExpressions	cExpressions;
	CKicadSchemExpression*	pcRoot;
	CKicadSchemExpression*	pcAt;
	CKicadSchemExpression*	pcEmpty;
	TRISTATE				tResult;
	float64					f;
	int32					i;

	cExpressions.Init();
	tResult = ParseKicadSchemText("(kicad_sch\n\t(version 20250114)\n\t(at 1.27 -2.54 90)\n\t(fields_autoplaced)\n)\n", &cExpressions);
	AssertTritrue(tResult);

	pcRoot = cExpressions.GetRoot();
	AssertNotNull(pcRoot);
	AssertTrue(pcRoot->IsList());
	AssertTrue(pcRoot->Is("kicad_sch"));
	AssertString("kicad_sch", pcRoot->GetText());
	AssertSize(1, pcRoot->GetLine());
	AssertSize(3, pcRoot->NumChildren());
	AssertSize(8, cExpressions.NumExpressions());

	AssertTrue(pcRoot->GetChildInt("version", &i));
	AssertInt(20250114, i);

	pcAt = pcRoot->FindChild("at");
	AssertNotNull(pcAt);
	AssertSize(3, pcAt->GetLine());
	AssertSize(3, pcAt->NumChildren());
	AssertTrue(pcAt->GetChild(0)->IsSymbol());
	AssertString("1.27", pcAt->GetAtomText(0));
	AssertTrue(pcAt->GetDouble(0, &f));
	AssertDouble(1.27, f, 10);
	AssertTrue(pcAt->GetDouble(1, &f));
	AssertDouble(-2.54, f, 10);
	AssertTrue(pcAt->GetInt(2, &i));
	AssertInt(90, i);
	AssertFalse(pcAt->GetDouble(3, &f));
	AssertNull(pcAt->GetChild(3));

	pcEmpty = pcRoot->FindChild("fields_autoplaced");
	AssertNotNull(pcEmpty);
	AssertSize(0, pcEmpty->NumChildren());
	AssertNull(pcRoot->FindChild("missing"));

	cExpressions.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestKicadSchemParserAtoms(void)
{
	CKicadSchemExpressions	cExpressions;
	CKicadSchemExpression*	pcRoot;
	CKicadSchemExpression*	pcProperty;
	CKicadSchemExpression*	pcText;
	TRISTATE				tResult;
	bool					b;

	cExpressions.Init();
	tResult = ParseKicadSchemText(
		"(kicad_sch (generator eeschema) (uuid 42f3f274-92b6-4722-96f2-06ebe96b181d)\n"
		"  (property \"Reference\" \"U1\" (hide yes))\n"
		"  (text \"Say \\\"hi\\\"\\nC:\\\\Temp (x)\")\n"
		"  (in_bom no)\n"
		"  (pin passive line))", &cExpressions);
	AssertTritrue(tResult);

	pcRoot = cExpressions.GetRoot();
	AssertString("eeschema", pcRoot->GetChildText("generator"));
	AssertTrue(pcRoot->FindChild("generator")->GetChild(0)->IsSymbol());
	AssertString("42f3f274-92b6-4722-96f2-06ebe96b181d", pcRoot->GetChildText("uuid"));

	pcProperty = pcRoot->FindChild("property");
	AssertTrue(pcProperty->GetChild(0)->IsString());
	AssertString("Reference", pcProperty->GetAtomText(0));
	AssertString("U1", pcProperty->GetAtomText(1));
	AssertNull(pcProperty->GetAtomText(2));
	AssertTrue(pcProperty->GetChildYesNo("hide", &b));
	AssertTrue(b);

	pcText = pcRoot->FindChild("text");
	AssertString("Say \"hi\"\nC:\\Temp (x)", pcText->GetAtomText(0));

	AssertTrue(pcRoot->GetChildYesNo("in_bom", &b));
	AssertFalse(b);
	AssertFalse(pcRoot->GetChildYesNo("on_board", &b));

	AssertTrue(pcRoot->FindChild("pin")->ContainsSymbol("passive"));
	AssertFalse(pcRoot->FindChild("pin")->ContainsSymbol("input"));

	cExpressions.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestKicadSchemParserNumbers(void)
{
	float64	f;
	int32	i;

	AssertTrue(ParseKicadSchemDouble("0", &f));
	AssertDouble(0.0, f, 10);
	AssertTrue(ParseKicadSchemDouble("-0.635", &f));
	AssertDouble(-0.635, f, 10);
	AssertTrue(ParseKicadSchemDouble("-.5", &f));
	AssertDouble(-0.5, f, 10);
	AssertTrue(ParseKicadSchemDouble("+12.", &f));
	AssertDouble(12.0, f, 10);
	AssertTrue(ParseKicadSchemDouble("101.6", &f));
	AssertTrue(f == 101.6);
	AssertTrue(ParseKicadSchemDouble("1.27e2", &f));
	AssertDouble(127.0, f, 10);
	AssertTrue(ParseKicadSchemDouble("5E-3", &f));
	AssertDouble(0.005, f, 10);

	AssertFalse(ParseKicadSchemDouble("", &f));
	AssertFalse(ParseKicadSchemDouble("-", &f));
	AssertFalse(ParseKicadSchemDouble(".", &f));
	AssertFalse(ParseKicadSchemDouble("1.2.3", &f));
	AssertFalse(ParseKicadSchemDouble("1e", &f));
	AssertFalse(ParseKicadSchemDouble("yes", &f));
	AssertFalse(ParseKicadSchemDouble("12mm", &f));

	AssertTrue(ParseKicadSchemInt("-270", &i));
	AssertInt(-270, i);
	AssertTrue(ParseKicadSchemInt("2147483647", &i));
	AssertInt(2147483647, i);
	AssertFalse(ParseKicadSchemInt("2147483648", &i));
	AssertFalse(ParseKicadSchemInt("1.5", &i));
	AssertFalse(ParseKicadSchemInt("", &i));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestKicadSchemParserPrint(void)
{
	CKicadSchemExpressions	cExpressions;
	CChars					sz;
	TRISTATE				tResult;

	cExpressions.Init();
	tResult = ParseKicadSchemText("\xEF\xBB\xBF  (kicad_sch\n  (version 20250114)\t(property \"Va\\\"lue\" \"a\\nb\")  (x)\n)\n\n", &cExpressions);
	AssertTritrue(tResult);

	sz.Init();
	cExpressions.GetRoot()->Print(&sz);
	AssertString("(kicad_sch (version 20250114) (property \"Va\\\"lue\" \"a\\nb\") (x))", sz.Text());
	sz.Kill();

	cExpressions.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestKicadSchemParserErrors(void)
{
	AssertKicadSchemParseError("", "Expected '(' to start the file.");
	AssertKicadSchemParseError("kicad_sch", "Expected '(' to start the file.");
	AssertKicadSchemParseError("(kicad_sch (version 1)", "Expected ')' to close (kicad_sch from line 1.");
	AssertKicadSchemParseError("(kicad_sch\n(at 1 2\n)", "Expected ')' to close (kicad_sch from line 1.");
	AssertKicadSchemParseError("(kicad_sch (at 1 2)) (extra)", "Expected the end of the file after the last ')'.");
	AssertKicadSchemParseError("(kicad_sch ( ))", "Expected a name after '('.");
	AssertKicadSchemParseError("(\"kicad_sch\")", "Expected a name after '('.");
	AssertKicadSchemParseError("(kicad_sch (text \"unclosed))", "Expected '\"' to close the string.");
	AssertKicadSchemParseError("(kicad_sch (text \"unclosed\\", "Expected '\"' to close the string.");
	AssertKicadSchemParseError("(kicad_sch\n  (at 1 2) )\n )", "none.kicad_sch(3,2)");
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestKicadSchemParserCarriageReturns(void)
{
	CKicadSchemParser		cParser;
	CKicadSchemExpressions	cExpressions;
	CLogToMemory			cMemoryLog;
	char					szLogText[400];
	bool					bResult;

	//CTextParser does not accept carriage returns.  Text must be passified first.
	cMemoryLog.Start(true);
	cExpressions.Init();
	bResult = cParser.Init("(kicad_sch\r\n)\r\n", 15, "none.kicad_sch", &cExpressions);
	cParser.Kill();
	cExpressions.Kill();
	cMemoryLog.Stop(szLogText, 400);

	AssertFalse(bResult);
	AssertTrue(strstr(szLogText, "carriage returns") != NULL);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestKicadSchemParser(void)
{
	BeginTests();

	TestKicadSchemParserLists();
	TestKicadSchemParserAtoms();
	TestKicadSchemParserNumbers();
	TestKicadSchemParserPrint();
	TestKicadSchemParserErrors();
	TestKicadSchemParserCarriageReturns();

	TestStatistics();
}

