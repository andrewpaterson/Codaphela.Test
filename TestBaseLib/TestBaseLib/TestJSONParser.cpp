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
	CMarkupTag*		pcTag;
	CMarkupTag*		pcChildTag;
	char*			szAttribute;
	CChars			szText;
	STagIterator	sIter;
	uint			uiType;
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

	pcTag = cMarkup.GetRootTag();
	AssertBool(true, pcTag->Is("painting"));
	pcChildTag = pcTag->GetTag("img");
	szAttribute = (char*)pcChildTag->GetAttribute("alt", &uiType);
	AssertInt(PT_char8Pointer, uiType);
	AssertString("Foligno Madonna, by Raphael", szAttribute);
	szAttribute = (char*)pcChildTag->GetAttribute("src", &uiType);
	AssertInt(PT_char8Pointer, uiType);
	AssertString("madonna.jpg", szAttribute);
	szAttribute = (char*)pcChildTag->GetAttribute("foo", &uiType);
	AssertInt(PT_char8Pointer, uiType);
	AssertNull(szAttribute);

	pcTag = pcTag->GetTag("caption");
	AssertBool(true, pcTag->Is("caption"));

	szText.Init();
	pcTag->GetText(&szText);
	AssertString("This is Raphael's \"Foligno\" Madonna, painted in ", szText.Text());
	szText.Kill();

	pcChildTag = pcTag->GetTag("date", &sIter);
	szText.Init();
	pcChildTag->GetText(&szText);
	AssertString("1511", szText.Text());
	szText.Kill();

	pcChildTag = pcTag->GetNextTag(&sIter);
	szText.Init();
	pcChildTag->GetText(&szText);
	AssertString("1512", szText.Text());
	szText.Kill();

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

	cMarkup.Dump();

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
void TestJSONParser(void)
{
	BeginTests();
	DataMemoryInit();

	TestJSONParserRead1();
	TestJSONParserRead2();
	TestJSONParserReadAttributes();

	DataMemoryKill();
	TestStatistics();
}

