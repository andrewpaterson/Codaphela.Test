#include "CoreLib/TextParser.h"
#include "TestLib/Assert.h"


void TestTextParser(void)
{
	BeginTests();

	char		c;
	TRISTATE	tResult;
	char		szTemp[1024];
	CTextParser cTextParser;
	char		szText[] = "\
identifier\n\
id1 id2\n\
\"string\"\n\
\"1\" \"2\"\n\
c\n\
";

	cTextParser.Init(szText);
	tResult = cTextParser.GetIdentifier(szTemp);
	AssertTristate(TRITRUE, tResult);
	AssertString("identifier", szTemp);

	tResult = cTextParser.GetExactIdentifier("id1");
	AssertTristate(TRITRUE, tResult);
	tResult = cTextParser.GetExactIdentifier("id2");
	AssertTristate(TRITRUE, tResult);

	tResult = cTextParser.GetString(szTemp);
	AssertString("string", szTemp);
	AssertTristate(TRITRUE, tResult);

	tResult = cTextParser.GetString(szTemp);
	AssertString("1", szTemp);
	AssertTristate(TRITRUE, tResult);
	tResult = cTextParser.GetString(szTemp);
	AssertString("2", szTemp);
	AssertTristate(TRITRUE, tResult);

	cTextParser.SkipWhiteSpace();
	tResult = cTextParser.GetCharacter(&c);
	AssertChar('c', c);
	AssertTristate(TRITRUE, tResult);
	cTextParser.Kill();

	cTextParser.Init("One Line");
	tResult = cTextParser.GetIdentifier(szTemp);
	AssertTristate(TRITRUE, tResult);
	AssertString("One", szTemp);
	tResult = cTextParser.GetIdentifier(szTemp);
	AssertTristate(TRITRUE, tResult);								
	AssertString("Line", szTemp);
	AssertBool(TRUE, cTextParser.mbOutsideText);

	cTextParser.Kill();

	TestStatistics();
}

