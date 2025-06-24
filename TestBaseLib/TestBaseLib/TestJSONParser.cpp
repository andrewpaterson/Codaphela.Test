#include "BaseLib/Logger.h"
#include "BaseLib/MemoryFile.h"
#include "BaseLib/JSONParser.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestJSONParserRead1(void)
{
	TRISTATE		tResult;
	CMarkup			cMarkup;
	CJSONParser		cJSONParser;
	char			szJSON[] = "\
{\n\
  \"painting\": [\n\
    {\n\
      \"img@src\": \"madonna.jpg\",\n\
      \"img@alt\": \"Foligno Madonna, by Raphael\"\n\
    },\n\
    {\n\
      \"caption\": [\n\
        \"This is Raphael's \\\"Foligno\\\" Madonna, painted in\",\n\
        {\n\
          \"date\": \"1511\"\n\
        }, \n\
        \"-\", \n\
        {\n\
          \"date\": \"1512\"\n\
        }, \n\
        \".\"\n\
      ]\n\
    }\n\
  ]\n\
}\n";


	cMarkup.Init();
	cJSONParser.Init(szJSON, "", &cMarkup, &gcLogger);
	tResult = cJSONParser.Parse();
	cJSONParser.Kill();

	cMarkup.Dump();

	AssertTritrue(tResult);

	cMarkup.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestJSONParserRead2(void)
{
	TRISTATE		tResult;
	CMarkup			cMarkup;
	CJSONParser		cJSONParser;
	CMarkupTag*		pcTag;
	char			szJSON[] = "\
{\n\
\"glossary\": {\n\
	\"title\": \"example glossary\",\n\
		\"GlossDiv\" : {\n\
			\"title\": \"S\",\n\
			\"GlossList\" : {\n\
				\"GlossEntry\": {\n\
					\"ID\": \"SGML\",\n\
					\"SortAs\" : \"SGML\",\n\
					\"GlossTerm\" : \"Standard Generalized Markup Language\",\n\
					\"Acronym\" : \"SGML\",\n\
					\"Abbrev\" : \"ISO 8879:1986\",\n\
					\"GlossDef\" : {\n\
						\"para\": \"A meta-markup language, used to create markup languages such as DocBook.\",\n\
						\"GlossSeeAlso\": [\"GML\", \"XML\"]\n\
					},\n\
				\"GlossSee\" : \"markup\"\n\
				}\n\
			}\n\
		}\n\
	}\n\
}\n";

	cMarkup.Init();
	cJSONParser.Init(szJSON, "", &cMarkup, &gcLogger);
	tResult = cJSONParser.Parse();
	cJSONParser.Kill();

	AssertTritrue(tResult);

	pcTag = cMarkup.GetRootTag();

	cMarkup.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestJSONParserReadAttributes(void)
{
	TRISTATE		tResult;
	CMarkup			cMarkup;
	CJSONParser		cJSONParser;
	CMarkupTag*		pcTag;
	char			szJSON[] = "\
{\"widget\": {\n\
    \"debug\": \"on\",\n\
    \"window\": {\n\
        \"title\": \"Sample Konfabulator Widget\",\n\
        \"name\": \"main_window\",\n\
        \"width\": 500,\n\
        \"height\": 500\n\
    },\n\
    \"image\": { \n\
        \"src\": \"Images/Sun.png\",\n\
        \"name\": \"sun1\",\n\
        \"hOffset\": 250,\n\
        \"vOffset\": 250,\n\
        \"alignment\": \"center\"\n\
    },\n\
    \"text\": {\n\
        \"data\": \"Click Here\",\n\
        \"size\": 36,\n\
        \"style\": \"bold\",\n\
        \"name\": \"text1\",\n\
        \"hOffset\": 250,\n\
        \"vOffset\": 100,\n\
        \"alignment\": \"center\",\n\
        \"onMouseUp\": \"sun1.opacity = (sun1.opacity / 100) * 90;\"\n\
    }\n\
}}\n";

	cMarkup.Init();
	cJSONParser.Init(szJSON, "", &cMarkup, &gcLogger);
	tResult = cJSONParser.Parse();
	cJSONParser.Kill();

	AssertTritrue(tResult);

	pcTag = cMarkup.GetRootTag();

	cMarkup.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestJSONParser65816SampleTest(void)
{
	TRISTATE		tResult;
	CMarkup			cMarkup;
	CJSONParser		cJSONParser;
	CMarkupTag*		pcTag;
	char			szJSON[] = "\
{\n\
	\"name\": \"3d e 1\",\n\
	\"initial\": {\n\
		\"pc\": 9900,\n\
		\"s\": 2191,\n\
		\"p\": 171,\n\
		\"a\": 25345,\n\
		\"x\": 100,\n\
		\"y\": 124,\n\
		\"dbr\": 26,\n\
		\"d\": 50304,\n\
		\"pbr\": 111,\n\
		\"e\": 1,\n\
		\"ram\": [\n\
			[1751932, 14],\n\
			[7284398, 187],\n\
			[7284397, 24],\n\
			[7284396, 61]\n\
		]\n\
	},\n\
	\"final\": {\n\
		\"pc\": 9903,\n\
		\"s\": 2191,\n\
		\"p\": 43,\n\
		\"a\": 25344,\n\
		\"x\": 100,\n\
		\"y\": 124,\n\
		\"dbr\": 26,\n\
		\"d\": 50304,\n\
		\"pbr\": 111,\n\
		\"e\": 1,\n\
		\"ram\": [\n\
			[1751932, 14],\n\
			[7284398, 187],\n\
			[7284397, 24],\n\
			[7284396, 61]\n\
		]\n\
	},\n\
	\"cycles\": [\n\
		[7284396, 61, \"dp-remx-\"],\n\
		[7284397, 24, \"-p-remx-\"],\n\
		[7284398, 187, \"-p-remx-\"],\n\
		[1751932, 14, \"d--remx-\"]\n\
	]\n\
}\n";

	cMarkup.Init();
	cJSONParser.Init(szJSON, "", &cMarkup, &gcLogger);
	tResult = cJSONParser.Parse();
	cJSONParser.Kill();

	AssertTritrue(tResult);

	pcTag = cMarkup.GetRootTag();

	cMarkup.Dump();

	cMarkup.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestJSONParser(void)
{
	BeginTests();
	DataMemoryInit();

	TestJSONParserRead1();
	TestJSONParserRead2();
	TestJSONParserReadAttributes();
	TestJSONParser65816SampleTest();

	DataMemoryKill();
	TestStatistics();
}

