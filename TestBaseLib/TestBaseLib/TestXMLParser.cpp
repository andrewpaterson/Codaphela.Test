#include "BaseLib/Logger.h"
#include "BaseLib/MemoryFile.h"
#include "BaseLib/XMLParser.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestXMLParserReadSingleTag(void)
{
	CChars			sz;
	TRISTATE		tResult;
	CMarkup			cMarkup;
	uint			uiType;
	CXMLParser		cXMLParser;
	CMarkupTag*		pcTag;
	char*			szAttribute;
	char			szXML[] = "<?xml version=\"1.0\" encoding='UTF-8'?><Imagine src=\"Sourcey\"/>";

	cMarkup.Init();
	cXMLParser.Init(szXML, "", &cMarkup, NULL);
	tResult = cXMLParser.Parse();
	cXMLParser.Kill();

	AssertTritrue(tResult);

	pcTag = cMarkup.GetRootTag();
	AssertBool(true, pcTag->Is("Imagine"));
	szAttribute = (char*)pcTag->GetNamedAttribute("src", &uiType);
	AssertInt(PT_char8Pointer, uiType);
	AssertString("Sourcey", szAttribute);

	sz.Init();
	pcTag->Print(&sz);
	AssertString("<Imagine src=\"Sourcey\"/>\n", sz.Text());
	sz.Kill();


	cMarkup.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestXMLParserRead(void)
{
	TRISTATE		tResult;
	CMarkup			cMarkup;
	uint			uiType;
	CXMLParser		cXMLParser;
	CMarkupTag*		pcTag;
	CMarkupTag*		pcChildTag;
	char*			szAttribute;
	CChars			szText;
	char			szXML[] = "\
<?xml version=\"1.0\" encoding='UTF-8'?>\n\
<painting>\n\
<img src=\"madonna.jpg\" alt='Foligno Madonna, by Raphael'/>\n\
<caption>This is Raphael's \"Foligno\" Madonna, painted in <date>1511</date>-<date>1512</date>.</caption>\n\
</painting>";
	STagIterator	sIter;

	cMarkup.Init();
	cXMLParser.Init(szXML, "", &cMarkup, NULL);
	tResult = cXMLParser.Parse();
	cXMLParser.Kill();

	AssertTritrue(tResult);

	pcTag = cMarkup.GetRootTag();
	AssertBool(true, pcTag->Is("painting"));
	pcChildTag = pcTag->GetTag("img");
	szAttribute = (char*)pcChildTag->GetNamedAttribute("alt", &uiType);
	AssertInt(PT_char8Pointer, uiType);
	AssertString("Foligno Madonna, by Raphael", szAttribute);
	szAttribute = (char*)pcChildTag->GetNamedAttribute("src", &uiType);
	AssertInt(PT_char8Pointer, uiType);
	AssertString("madonna.jpg", szAttribute);
	szAttribute = (char*)pcChildTag->GetNamedAttribute("foo", &uiType);
	AssertInt(PT_Undefined, uiType);
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
void TestXMLParserComments(void)
{
	TRISTATE		tResult;
	CMarkup			cMarkup;
	CXMLParser		cXMLParser;
	CChars			szDoc;
	CChars			szText;
	bool			bContiguous;
	STagIterator	sIter;
	char			szXML[] = "\
						  <!-- Firsts! -->\n\
						  <Channel Name=\"Flags\">\n\
						  <!--<Equals>0</Equals>-->\n\
						  <Other><!--0--></Other>\n\
						  <Other>Even<!--More-->Fun</Other>\n\
						  </Channel><! Coo-eey -->";
	char		szExpectedXML[] = "\
<Channel Name=\"Flags\">\n\
  <Other/>\n\
  <Other>EvenFun</Other>\n\
</Channel>\n";

	cMarkup.Init();
	cXMLParser.Init(szXML, "", &cMarkup, NULL);
	tResult = cXMLParser.Parse();
	cXMLParser.Kill();

	szText.Init();
	cMarkup.GetRootTag()->GetTag("Other", &sIter);
	bContiguous = cMarkup.GetRootTag()->GetNextTag(&sIter)->GetText(&szText);
	AssertString("EvenFun", szText.Text());
	szText.Kill();
	AssertBool(true, bContiguous);

	szDoc.Init();
	cMarkup.mpcDoc->Print(&szDoc);
	AssertString(szExpectedXML, szDoc.Text());

	szDoc.Kill();
	cMarkup.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestXMLParserTextToString(void)
{
	TRISTATE	tResult;
	CMarkup		cMarkup;
	CXMLParser	cXMLParser;
	CChars		szDoc;
	char		szXML[] = "\
				   <Root>\n\
				   <Tag1>Leave service control...\n\
Install<!-- Oh Hai! --> Service\n\
Install Service\n\
GEST Service CreateService error = 1073\n\
				   </Tag1>\n\
				   <Tag2>Hello<Tag3>!!!</Tag3>World\n\
				   </Tag2>\n\
				   <Tag3/>\n\
				   </Root>";
	char		szExpectedXML[] = "\
<Root>\n\
  <Tag1>\n\
    Leave service control...\n\
    Install Service\n\
    Install Service\n\
    GEST Service CreateService error = 1073\n\
  </Tag1>\n\
  <Tag2>\n\
    Hello\n\
    <Tag3>!!!</Tag3>\n\
    World\n\
  </Tag2>\n\
  <Tag3/>\n\
</Root>\n";

	//There is a bug where if the is a comment, whitespace and another comment the whitespace is lost.
	//eg: "<!-- --> <!-- -->" becomes "".
	//I doubt it will ever be a problem.

	cMarkup.Init();
	cXMLParser.Init(szXML, "", &cMarkup, NULL);
	tResult = cXMLParser.Parse();
	cXMLParser.Kill();

	szDoc.Init();
	cMarkup.mpcDoc->Print(&szDoc);
	AssertString(szExpectedXML, szDoc.Text());

	szDoc.Kill();
	cMarkup.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestXMLParserNamedReferences(void)
{
	CMarkupReference*	pcRef;
	CMarkupNamedRef*	pcNamedRef;
	TRISTATE			tResult;
	CMarkup				cMarkup;
	CXMLParser			cXMLParser;
	CMarkupDoc*			pcDoc;
	CChars				szDoc;
	char				szXML[] = "\
								  <Root>\n\
									&RootNameRef\n\
									<Tag>\n\
										&TagNameRef\n\
									</Tag>\n\
									<Tag>\n\
										Frikkie in the Snow\n\
										&TagNameRef\n\
										On Fully Automatic\n\
									</Tag>\n\
								  </Root>\n";
	char				szExpectedXML[] = "\
<Root>\n\
  &RootNameRef\n\
  <Tag>\n\
    &TagNameRef\n\
  </Tag>\n\
  <Tag>\n\
    Frikkie in the Snow\n\
    &TagNameRef\n\
    On Fully Automatic\n\
  </Tag>\n\
</Root>\n";

	cMarkup.Init();
	cXMLParser.Init(szXML, "", &cMarkup, NULL);
	tResult = cXMLParser.Parse();

	pcDoc = cXMLParser.mpcDoc;
	AssertInt(3, pcDoc->macRefs.NumElements());

	pcRef = *pcDoc->macRefs.Get(0);
	AssertBool(true, pcRef->IsNamedRef());
	pcNamedRef = (CMarkupNamedRef*)pcRef;
	AssertString("RootNameRef", pcNamedRef->mszName.Text());

	pcRef = *pcDoc->macRefs.Get(1);
	AssertBool(true, pcRef->IsNamedRef());
	pcNamedRef = (CMarkupNamedRef*)pcRef;
	AssertString("TagNameRef", pcNamedRef->mszName.Text());

	pcRef = *pcDoc->macRefs.Get(2);
	AssertBool(true, pcRef->IsNamedRef());
	pcNamedRef = (CMarkupNamedRef*)pcRef;
	AssertString("TagNameRef", pcNamedRef->mszName.Text());

	szDoc.Init();
	pcDoc->Print(&szDoc);
	AssertString(szExpectedXML, szDoc.Text());
	szDoc.Kill();

	cXMLParser.Kill();
	cMarkup.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestXMLParserErrors(void)
{
	CXMLParser		cXMLParser;
	TRISTATE		tResult;
	CMarkup			cMarkup;
	CLogger			cLogger;
	CMemoryFile		cMemory;
	SLogConfig		sLogConfig;
	char			szZero[1] = { 0 };
	char			szXML[] = "\
<Root>\n\
  <Tag name=\"\" other\"\">\n\
  </Tag>\n\
  <Tag name\"\">\n\
  </Tag>\n\
</Root>\n";

	cMemory.Init();
	cLogger.Init(&cMemory, NULL);
	sLogConfig = cLogger.SetSilent();
	cMarkup.Init();
	cXMLParser.Init(szXML, "InMemory", &cMarkup, &cLogger);
	tResult = cXMLParser.Parse();
	cMemory.Write(szZero, 1, 1);

	AssertStringStartsWith("WARNING: Expected [=].", (char*)cMemory.GetBufferPointer());

	cLogger.SetConfig(&sLogConfig);
	cXMLParser.Kill();
	cMarkup.Kill();
	cLogger.Kill();
	cMemory.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestXMLParserLogisimFile(void)
{
	CXMLParser		cXMLParser;
	TRISTATE		tResult;
	CMarkup			cMarkup;
	CLogger			cLogger;
	CMemoryFile		cMemory;
	SLogConfig		sLogConfig;
	char			szZero[1] = { 0 };
	char			szXML[] = "<lib desc=\"jar#..\\logi65816\\out\\artifacts\\logi65816.jar#net.logisim.Components\" name=\"12\"/>";

	cMemory.Init();
	cLogger.Init(&cMemory, NULL);
	sLogConfig = cLogger.SetSilent();
	cMarkup.Init();
	cXMLParser.Init(szXML, "InMemory", &cMarkup, &cLogger);
	tResult = cXMLParser.Parse();
	cMemory.Write(szZero, 1, 1);

	AssertTristate(TRITRUE, tResult);

	cLogger.SetConfig(&sLogConfig);
	cXMLParser.Kill();
	cMarkup.Kill();
	cLogger.Kill();
	cMemory.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestXMLParser(void)
{
	BeginTests();
	DataMemoryInit();

	TestXMLParserReadSingleTag();
	TestXMLParserRead();
	TestXMLParserTextToString();
	TestXMLParserComments();
	TestXMLParserNamedReferences();
	TestXMLParserErrors();
	TestXMLParserLogisimFile();

	DataMemoryKill();
	TestStatistics();
}

