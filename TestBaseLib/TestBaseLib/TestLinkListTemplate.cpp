#include "BaseLib/IntegerHelper.h"
#include "BaseLib/LinkedListTemplate.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestLinkedListTemplateIndexOf(void)
{
	CLinkedListTemplate<int>	cLinkList;
	int*					pi1;
	int*					pi2;
	int*					pi3;

	pi1 = NULL;
	pi2 = NULL;
	pi3 = NULL;

	cLinkList.Init();
	pi1 = cLinkList.InsertAfterTail();
	*pi1 = 3;
	pi2 = cLinkList.InsertAfterTail();
	*pi2 = 2;
	pi3 = cLinkList.InsertAfterTail();
	*pi3 = 1;

	AssertInt(0, cLinkList.IndexOf(pi1));
	AssertInt(1, cLinkList.IndexOf(pi2));
	AssertInt(2, cLinkList.IndexOf(pi3));

	cLinkList.BubbleSort(&CompareInt);

	AssertInt(2, cLinkList.IndexOf(pi1));
	AssertInt(1, cLinkList.IndexOf(pi2));
	AssertInt(0, cLinkList.IndexOf(pi3));

	cLinkList.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestLinkedListTemplate(void)
{
	BeginTests();

	TestLinkedListTemplateIndexOf();

	TestStatistics();
}

