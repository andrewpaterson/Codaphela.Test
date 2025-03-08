#include "BaseLib/TextParser.h"
#include "TestLib/Assert.h"



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTextParserGetIdentifier(void)
{
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
	AssertBool(true, cTextParser.mbOutsideText);

	cTextParser.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTextParserGetIntegerLiteral(void)
{

	TRISTATE	tResult;
	CTextParser cTextParser;
	uint64		ulliValue;
	uint16		iBase;
	uint16		iSuffix;
	uint16		iNumDigits;

	cTextParser.Init("100\n");
	tResult = cTextParser.GetIntegerLiteral(&ulliValue, INTEGER_PREFIX_ALL, &iBase, INTEGER_SUFFIX_CPP, &iSuffix, NUMBER_SEPARATOR_APOSTROPHE, &iNumDigits, true);
	cTextParser.Kill();
	AssertTritrue(tResult);
	AssertLong(100LL, ulliValue);
	AssertInt(10, iBase);
	AssertInt(INTEGER_SUFFIX_NONE, iSuffix);
	AssertInt(3, iNumDigits);

	cTextParser.Init("100");
	tResult = cTextParser.GetIntegerLiteral(&ulliValue, INTEGER_PREFIX_ALL, &iBase, INTEGER_SUFFIX_CPP, &iSuffix, NUMBER_SEPARATOR_APOSTROPHE, &iNumDigits, true);
	cTextParser.Kill();
	AssertTritrue(tResult);
	AssertLong(100LL, ulliValue);
	AssertInt(10, iBase);
	AssertInt(INTEGER_SUFFIX_NONE, iSuffix);
	AssertInt(3, iNumDigits);

	cTextParser.Init("100ULL");
	tResult = cTextParser.GetIntegerLiteral(&ulliValue, INTEGER_PREFIX_ALL, &iBase, INTEGER_SUFFIX_CPP, &iSuffix, NUMBER_SEPARATOR_APOSTROPHE, &iNumDigits, true);
	cTextParser.Kill();
	AssertTritrue(tResult);
	AssertLong(100LL, ulliValue);
	AssertInt(10, iBase);
	AssertInt(INTEGER_SUFFIX_ULL, iSuffix);
	AssertInt(3, iNumDigits);

	cTextParser.Init("0x100ULL");
	tResult = cTextParser.GetIntegerLiteral(&ulliValue, INTEGER_PREFIX_ALL, &iBase, INTEGER_SUFFIX_CPP, &iSuffix, NUMBER_SEPARATOR_APOSTROPHE, &iNumDigits, true);
	cTextParser.Kill();
	AssertTritrue(tResult);
	AssertLong(256LL, ulliValue);
	AssertInt(16, iBase);
	AssertInt(INTEGER_SUFFIX_ULL, iSuffix);
	AssertInt(3, iNumDigits);

	cTextParser.Init("0x100LL");
	tResult = cTextParser.GetIntegerLiteral(&ulliValue, INTEGER_PREFIX_ALL, &iBase, INTEGER_SUFFIX_CPP, &iSuffix, NUMBER_SEPARATOR_APOSTROPHE, &iNumDigits, true);
	cTextParser.Kill();
	AssertTritrue(tResult);
	AssertLong(256LL, ulliValue);
	AssertInt(16, iBase);
	AssertInt(INTEGER_SUFFIX_LL, iSuffix);
	AssertInt(3, iNumDigits);

	cTextParser.Init("100L");
	tResult = cTextParser.GetIntegerLiteral(&ulliValue, INTEGER_PREFIX_ALL, &iBase, INTEGER_SUFFIX_CPP, &iSuffix, NUMBER_SEPARATOR_APOSTROPHE, &iNumDigits, true);
	cTextParser.Kill();
	AssertTritrue(tResult);
	AssertLong(100L, ulliValue);
	AssertInt(10, iBase);
	AssertInt(INTEGER_SUFFIX_L, iSuffix);
	AssertInt(3, iNumDigits);

	cTextParser.Init("0100");
	tResult = cTextParser.GetIntegerLiteral(&ulliValue, INTEGER_PREFIX_ALL, &iBase, INTEGER_SUFFIX_CPP, &iSuffix, NUMBER_SEPARATOR_APOSTROPHE, &iNumDigits, true);
	cTextParser.Kill();
	AssertTritrue(tResult);
	AssertLong(64L, ulliValue);
	AssertInt(8, iBase);
	AssertInt(INTEGER_SUFFIX_NONE, iSuffix);
	AssertInt(3, iNumDigits);

	cTextParser.Init("0100ul");
	tResult = cTextParser.GetIntegerLiteral(&ulliValue, INTEGER_PREFIX_ALL, &iBase, INTEGER_SUFFIX_CPP, &iSuffix, NUMBER_SEPARATOR_APOSTROPHE, &iNumDigits, true);
	cTextParser.Kill();
	AssertTritrue(tResult);
	AssertLong(64L, ulliValue);
	AssertInt(8, iBase);
	AssertInt(INTEGER_SUFFIX_UL, iSuffix);
	AssertInt(3, iNumDigits);

	cTextParser.Init("0b100");
	tResult = cTextParser.GetIntegerLiteral(&ulliValue, INTEGER_PREFIX_ALL, &iBase, INTEGER_SUFFIX_CPP, &iSuffix, NUMBER_SEPARATOR_APOSTROPHE, &iNumDigits, true);
	cTextParser.Kill();
	AssertTritrue(tResult);
	AssertLong(4LL, ulliValue);
	AssertInt(2, iBase);
	AssertInt(INTEGER_SUFFIX_NONE, iSuffix);
	AssertInt(3, iNumDigits);

	cTextParser.Init("0B100L\n");
	tResult = cTextParser.GetIntegerLiteral(&ulliValue, INTEGER_PREFIX_ALL, &iBase, INTEGER_SUFFIX_CPP, &iSuffix, NUMBER_SEPARATOR_APOSTROPHE, &iNumDigits, true);
	cTextParser.Kill();
	AssertTritrue(tResult);
	AssertLong(4LL, ulliValue);
	AssertInt(2, iBase);
	AssertInt(INTEGER_SUFFIX_L, iSuffix);
	AssertInt(3, iNumDigits);

	cTextParser.Init("0B1001'1011'0011'0100'0111'0000'1111'1010L\n");
	tResult = cTextParser.GetIntegerLiteral(&ulliValue, INTEGER_PREFIX_ALL, &iBase, INTEGER_SUFFIX_CPP, &iSuffix, NUMBER_SEPARATOR_APOSTROPHE, &iNumDigits, true);
	cTextParser.Kill();
	AssertTritrue(tResult);
	AssertLongLongIntHex(0x9b34'70faL, ulliValue);
	AssertInt(2, iBase);
	AssertInt(INTEGER_SUFFIX_L, iSuffix);
	AssertInt(32, iNumDigits);

	cTextParser.Init("0B1001'1011'0011'0100'0111'0000'1111'1010'1001'1011'0011'0100'0111'0000'1111'1010LL\n");
	tResult = cTextParser.GetIntegerLiteral(&ulliValue, INTEGER_PREFIX_ALL, &iBase, INTEGER_SUFFIX_CPP, &iSuffix, NUMBER_SEPARATOR_APOSTROPHE, &iNumDigits, true);
	cTextParser.Kill();
	AssertTritrue(tResult);
	AssertLongLongIntHex(0x9b34'70fa'9b34'70faL, ulliValue);
	AssertInt(2, iBase);
	AssertInt(INTEGER_SUFFIX_LL, iSuffix);
	AssertInt(64, iNumDigits);

	cTextParser.Init("0B1001'1011'0011'0100'0111'0000'1111'1010'1001'1011'0011'0100'0111'0000'1111'1010'LL\n");
	tResult = cTextParser.GetIntegerLiteral(&ulliValue, INTEGER_PREFIX_ALL, &iBase, INTEGER_SUFFIX_CPP, &iSuffix, NUMBER_SEPARATOR_APOSTROPHE, &iNumDigits, true);
	cTextParser.Kill();
	AssertTrifalse(tResult);

	cTextParser.Init("0B'1001'1011'0011'0100'0111'0000'1111'1010'1001'1011'0011'0100'0111'0000'1111'1010LL\n");
	tResult = cTextParser.GetIntegerLiteral(&ulliValue, INTEGER_PREFIX_ALL, &iBase, INTEGER_SUFFIX_CPP, &iSuffix, NUMBER_SEPARATOR_APOSTROPHE, &iNumDigits, true);
	cTextParser.Kill();
	AssertTritrue(tResult);

	cTextParser.Init("0xFFFF'FFFF'ffff'ffffUll");
	tResult = cTextParser.GetIntegerLiteral(&ulliValue, INTEGER_PREFIX_ALL, &iBase, INTEGER_SUFFIX_CPP, &iSuffix, NUMBER_SEPARATOR_APOSTROPHE, &iNumDigits, true);
	cTextParser.Kill();
	AssertTritrue(tResult);
	AssertLong(0XFFFF'FFFF'ffff'ffffUll, ulliValue);
	AssertInt(16, iBase);
	AssertInt(INTEGER_SUFFIX_ULL, iSuffix);
	AssertInt(16, iNumDigits);

	cTextParser.Init("A");
	tResult = cTextParser.GetIntegerLiteral(&ulliValue, INTEGER_PREFIX_ALL, &iBase, INTEGER_SUFFIX_CPP, &iSuffix, NUMBER_SEPARATOR_APOSTROPHE, &iNumDigits, true);
	cTextParser.Kill();
	AssertTrifalse(tResult);

	cTextParser.Init(" ! \n");
	tResult = cTextParser.GetIntegerLiteral(&ulliValue, INTEGER_PREFIX_ALL, &iBase, INTEGER_SUFFIX_CPP, &iSuffix, NUMBER_SEPARATOR_APOSTROPHE, &iNumDigits, true);
	cTextParser.Kill();
	AssertTrifalse(tResult);
	
	cTextParser.Init("0xAH");  //This isn't right.
	tResult = cTextParser.GetIntegerLiteral(&ulliValue, INTEGER_PREFIX_ALL, &iBase, INTEGER_SUFFIX_CPP, &iSuffix, NUMBER_SEPARATOR_APOSTROPHE, &iNumDigits, true);
	cTextParser.Kill();
	AssertTritrue(tResult);
	AssertLong(10, ulliValue);
	AssertInt(16, iBase);
	AssertInt(INTEGER_SUFFIX_NONE, iSuffix);
	AssertInt(1, iNumDigits);

	cTextParser.Init("0xA");
	tResult = cTextParser.GetIntegerLiteral(&ulliValue, INTEGER_PREFIX_ALL, NULL, INTEGER_SUFFIX_CPP, NULL, NUMBER_SEPARATOR_APOSTROPHE, NULL, true);
	cTextParser.Kill();
	AssertTritrue(tResult);
	AssertLong(10, ulliValue);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTextParserGetFloatLiteral(void)
{
	TRISTATE	tResult;
	CTextParser cTextParser;
	float96		ldValue;
	uint16		iBase;
	uint16		iSuffix;
	uint16		iNumWholeDigits;
	uint16		iNumDecimalDigits;
	uint16		iNumExponentDigits;
	uint16		iExponent;

	cTextParser.Init("100.\n");
	tResult = cTextParser.GetFloatLiteral(&ldValue, FLOAT_PREFIX_ALL, &iBase, FLOAT_SUFFIX_CPP, &iSuffix, FLOAT_EXPONENT_ALL, &iExponent, NUMBER_SEPARATOR_UNDERSCORE, &iNumWholeDigits , &iNumDecimalDigits, &iNumExponentDigits, true);
	cTextParser.Kill();
	AssertTritrue(tResult);
	AssertDouble(100, ldValue, 0);
	AssertInt(10, iBase);
	AssertInt(FLOAT_SUFFIX_NONE, iSuffix);
	AssertInt(3, iNumWholeDigits);
	AssertInt(0, iNumDecimalDigits);
	AssertInt(0, iNumExponentDigits);

	cTextParser.Init("100.f\n");
	tResult = cTextParser.GetFloatLiteral(&ldValue, FLOAT_PREFIX_ALL, &iBase, FLOAT_SUFFIX_CPP, &iSuffix, FLOAT_EXPONENT_ALL, &iExponent, NUMBER_SEPARATOR_UNDERSCORE, &iNumWholeDigits, &iNumDecimalDigits, &iNumExponentDigits, true);
	cTextParser.Kill();
	AssertTritrue(tResult);
	AssertDouble(100, ldValue, 0);
	AssertInt(10, iBase);
	AssertInt(FLOAT_SUFFIX_F, iSuffix);
	AssertInt(3, iNumWholeDigits);
	AssertInt(0, iNumDecimalDigits);
	AssertInt(0, iNumExponentDigits);

	cTextParser.Init("0x100.f\n");
	tResult = cTextParser.GetFloatLiteral(&ldValue, FLOAT_PREFIX_ALL, &iBase, FLOAT_SUFFIX_CPP, &iSuffix, FLOAT_EXPONENT_ALL, &iExponent, NUMBER_SEPARATOR_UNDERSCORE, &iNumWholeDigits, &iNumDecimalDigits, &iNumExponentDigits, true);
	cTextParser.Kill();
	AssertTrierror(tResult);

	cTextParser.Init("0x100.ap0f\n");
	tResult = cTextParser.GetFloatLiteral(&ldValue, FLOAT_PREFIX_ALL, &iBase, FLOAT_SUFFIX_CPP, &iSuffix, FLOAT_EXPONENT_ALL, &iExponent, NUMBER_SEPARATOR_UNDERSCORE, &iNumWholeDigits, &iNumDecimalDigits, &iNumExponentDigits, true);
	cTextParser.Kill();
	AssertTritrue(tResult);
	AssertDouble(0x100.ap0f, ldValue, 0);
	AssertInt(16, iBase);
	AssertInt(FLOAT_SUFFIX_F, iSuffix);
	AssertInt(3, iNumWholeDigits);
	AssertInt(1, iNumDecimalDigits);
	AssertInt(1, iNumExponentDigits);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTextParserGetIdentifierWithWhitespace()
{
	TRISTATE	tResult;
	char		szTemp[1024];
	CTextParser cTextParser;
	char		szText[] = "Hello/* Not * */ World // bleugh\n  Another/*//*/";

	cTextParser.Init(szText);
	tResult = cTextParser.GetIdentifier(szTemp);
	AssertTristate(TRITRUE, tResult);
	AssertString("Hello", szTemp);

	tResult = cTextParser.GetIdentifier(szTemp);
	AssertTristate(TRITRUE, tResult);
	AssertString("World", szTemp);

	tResult = cTextParser.GetIdentifier(szTemp);
	AssertTristate(TRITRUE, tResult);
	AssertString("Another", szTemp);

	cTextParser.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTextParserGetString()
{
	TRISTATE	tResult;
	char		szTemp[1024];
	CTextParser cTextParser;
	char		szText[] = "\"Hello /* Hey */\"/* */\"Wor\nld\"\n\"Hi\"";

	cTextParser.Init(szText);
	tResult = cTextParser.GetString(szTemp);
	AssertTristate(TRITRUE, tResult);
	AssertString("Hello /* Hey */", szTemp);

	tResult = cTextParser.GetString(szTemp);
	AssertTristate(TRITRUE, tResult);
	AssertString("Wor\nld", szTemp);

	tResult = cTextParser.GetString(szTemp);
	AssertTristate(TRITRUE, tResult);
	AssertString("Hi", szTemp);

	cTextParser.Kill();
}



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestTextParser(void)
{
	BeginTests();

	TestTextParserGetIdentifier();
	TestTextParserGetIntegerLiteral();
	TestTextParserGetFloatLiteral();
	TestTextParserGetIdentifierWithWhitespace();
	TestTextParserGetString();

	TestStatistics();
}

