#include "TestLib/Assert.h"
#include "CoreLib/XMLFile.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestReadExternalReference(void)
{
	CXMLFile	cXMLFile;
	CChars		szDoc;
	int			iLine;
	char		szExpected[] = "<InputDevices>\n\
  This is text &lt; and doom stuff\n\
  <RootInSecond>\n\
    Hello\n\
  </RootInSecond>\n\
  Sweet &gt; other stuff\n\
  <ThirdsRoot>\n\
    World\n\
  </ThirdsRoot>\n\
</InputDevices>\n";
	CMarkupTag*	pcTag;
	CMarkupTag*	pcSecondTag;
	CMarkupTag*	pcThirdTag;
	CChars		szText;

	cXMLFile.Init();
	cXMLFile.Read("First.xml", ".");

	szDoc.Init(16);
	iLine = cXMLFile.mcMarkup.mpcDoc->ToString(&szDoc);
	AssertInt(10, iLine);
	AssertString(szExpected, szDoc.Text());
	szDoc.Kill();

	pcTag = cXMLFile.mcMarkup.mpcDoc->GetRootTag();
	pcSecondTag = pcTag->GetTag("RootInSecond");
	AssertNotNull(pcSecondTag);
	szText.Init();
	pcSecondTag->GetText(&szText);
	szText.StripWhiteSpace(TRUE);
	AssertString("Hello", szText.Text());
	szText.Kill();

	pcTag = cXMLFile.mcMarkup.mpcDoc->GetRootTag();
	pcThirdTag = pcTag->GetTag("ThirdsRoot");
	AssertNotNull(pcThirdTag);
	szText.Init();
	pcThirdTag->GetText(&szText);
	szText.StripWhiteSpace(TRUE);
	AssertString("World", szText.Text());
	szText.Kill();

	cXMLFile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestRepeatedExternalTags(void)
{
	CXMLFile		cXMLFile;
	CChars			szDoc;
	int				iLine;
	char			szExpected[] = "<Root>\n\
  <ExtTag>\n\
    <SubTag>Look at me!  I&apos;m going to be an elite pilot.</SubTag>\n\
    <SubTag>Also *very* messed up.</SubTag>\n\
  </ExtTag>\n\
  <ExtTag>\n\
    <SubTag>Look at me!  I&apos;m going to be an elite pilot.</SubTag>\n\
    <SubTag>Also *very* messed up.</SubTag>\n\
  </ExtTag>\n\
  <ExtTag>\n\
    <SubTag>Look at me!  I&apos;m going to be an elite pilot.</SubTag>\n\
    <SubTag>Also *very* messed up.</SubTag>\n\
  </ExtTag>\n\
  <ExtTag>\n\
    <SubTag>Look at me!  I&apos;m going to be an elite pilot.</SubTag>\n\
    <SubTag>Also *very* messed up.</SubTag>\n\
  </ExtTag>\n\
</Root>\n";
	CMarkupTag*		pcRoot;
	int				iCount;
	CMarkupTag*		pcExtTag;
	CMarkupTag*		pcSubTag1;
	CMarkupTag*		pcSubTag2;
	CMarkupTag*		pcSubTag3;
	CChars			szText;
	STagIterator	sIter;

	cXMLFile.Init();
	cXMLFile.Read("File.xml", ".");

	szDoc.Init(16);
	iLine = cXMLFile.mcMarkup.mpcDoc->ToString(&szDoc);
	AssertInt(18, iLine);
	AssertString(szExpected, szDoc.Text());
	szDoc.Kill();

	pcRoot = cXMLFile.mcMarkup.mpcDoc->GetRootTag();

	iCount = 0;
	pcExtTag = pcRoot->GetTag("ExtTag", &sIter);
	while (pcExtTag)
	{
		iCount++;

		if (iCount > 4)
		{
			//This is to take care of the case where GetNextTag always get's the first tag.
			break;
		}

		pcSubTag1 = pcExtTag->GetTag("SubTag", 0);
		pcSubTag2 = pcExtTag->GetTag("SubTag", 1);
		pcSubTag3 = pcExtTag->GetTag("SubTag", 2);

		szText.Init();
		pcSubTag1->GetText(&szText);
		AssertString("Look at me!  I'm going to be an elite pilot.", szText.Text());
		szText.Kill();		
		
		szText.Init();
		pcSubTag2->GetText(&szText);
		AssertString("Also *very* messed up.", szText.Text());
		szText.Kill();

		AssertNull(pcSubTag3);

		pcExtTag = pcRoot->GetNextTag(&sIter);
	}

	AssertInt(4, iCount);
	cXMLFile.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestXMLFile(void)
{
	BeginTests();

	TestReadExternalReference();
	TestRepeatedExternalTags();

	TestStatistics();
}

