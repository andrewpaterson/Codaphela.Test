#include "BaseLib/Logger.h"
#include "BaseLib/MemoryFile.h"
#include "CoreLib/XMLParser.h"
#include "TestLib/Assert.h"
#include "TestXMLParser.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestReadXML(void)
{
	TRISTATE		tResult;
	CMarkup			cMarkup;
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
	cXMLParser.Init(&cMarkup, NULL);
	tResult = cXMLParser.Parse(szXML, "");
	cXMLParser.Kill();

	pcTag = cMarkup.GetRootTag();
	AssertBool(TRUE, pcTag->Is("painting"));
	pcChildTag = pcTag->GetTag("img");
	szAttribute = pcChildTag->GetAttribute("alt");
	AssertString("Foligno Madonna, by Raphael", szAttribute);
	szAttribute = pcChildTag->GetAttribute("src");
	AssertString("madonna.jpg", szAttribute);
	szAttribute = pcChildTag->GetAttribute("foo");
	AssertNull(szAttribute);

	pcTag = pcTag->GetTag("caption");
	AssertBool(TRUE, pcTag->Is("caption"));

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
void TestXMLComments(void)
{
	TRISTATE		tResult;
	CMarkup			cMarkup;
	CXMLParser		cXMLParser;
	CChars			szDoc;
	CChars			szText;
	BOOL			bContiguous;
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
	cXMLParser.Init(&cMarkup, NULL);
	tResult = cXMLParser.Parse(szXML, "");
	cXMLParser.Kill();

	szText.Init();
	cMarkup.GetRootTag()->GetTag("Other", &sIter);
	bContiguous = cMarkup.GetRootTag()->GetNextTag(&sIter)->GetText(&szText);
	AssertString("EvenFun", szText.Text());
	szText.Kill();
	AssertBool(TRUE, bContiguous);

	szDoc.Init();
	cMarkup.mpcDoc->ToString(&szDoc);
	AssertString(szExpectedXML, szDoc.Text());

	szDoc.Kill();
	cMarkup.Kill();
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestXMLTextToString(void)
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
	cXMLParser.Init(&cMarkup, NULL);
	tResult = cXMLParser.Parse(szXML, "");
	cXMLParser.Kill();

	szDoc.Init();
	cMarkup.mpcDoc->ToString(&szDoc);
	AssertString(szExpectedXML, szDoc.Text());

	szDoc.Kill();
	cMarkup.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestNamedReferences(void)
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
	cXMLParser.Init(&cMarkup, NULL);
	tResult = cXMLParser.Parse(szXML, "");

	pcDoc = cXMLParser.mpcDoc;
	AssertInt(3, pcDoc->macRefs.NumElements());

	pcRef = *pcDoc->macRefs.Get(0);
	AssertBool(TRUE, pcRef->IsNamedRef());
	pcNamedRef = (CMarkupNamedRef*)pcRef;
	AssertString("RootNameRef", pcNamedRef->mszName.Text());

	pcRef = *pcDoc->macRefs.Get(1);
	AssertBool(TRUE, pcRef->IsNamedRef());
	pcNamedRef = (CMarkupNamedRef*)pcRef;
	AssertString("TagNameRef", pcNamedRef->mszName.Text());

	pcRef = *pcDoc->macRefs.Get(2);
	AssertBool(TRUE, pcRef->IsNamedRef());
	pcNamedRef = (CMarkupNamedRef*)pcRef;
	AssertString("TagNameRef", pcNamedRef->mszName.Text());

	szDoc.Init();
	pcDoc->ToString(&szDoc);
	AssertString(szExpectedXML, szDoc.Text());

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
	char			szXML[] = "\
<Root>\n\
  <Tag name=\"\" other\"\">\n\
  </Tag>\n\
  <Tag name\"\">\n\
  </Tag>\n\
</Root>\n";

	cMemory.Init();
	cLogger.Init(&cMemory, NULL);
	cLogger.SetEngineOutput(FALSE);
	cMarkup.Init();
	cXMLParser.Init(&cMarkup, &cLogger);
	tResult = cXMLParser.Parse(szXML, "InMemory");
	cMemory.cArray.Add((char)0);

	AssertString("ERROR: InMemory [2, 21]: '=' expected after attribute.\n", cMemory.cArray.GetData());

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

	TestReadXML();
	TestXMLTextToString();
	TestXMLComments();
	TestNamedReferences();
	TestXMLParserErrors();

	TestStatistics();
}

