#include "BaseLib/ArrayIntMinimal.h"
#include "BaseLib/ArrayCharMinimal.h"
#include "TestLib/Assert.h"


void TestArrayMinimalTemplateChar(void)
{
	CArrayCharMinimal	cac;

	CArrayCharMinimal	cac;

	cac.Init("aabbc");
	AssertString("aabbc", cac.GetArray());

	cac.BatchInsertElements(0, 3, 2, 2);

	cac.GetArray()[0] = cac.GetArray()[1] = cac.GetArray()[2]='_';
	cac.GetArray()[5] = cac.GetArray()[6] = cac.GetArray()[7]='_';
	AssertString("___aa___bbc", cac.GetArray());

	cac.InsertNumElementsAt(2, 1);

	cac.GetArray()[1]=cac.GetArray()[2]='X';
	AssertString("_XX__aa___bbc", cac.GetArray());

	cac.Kill();

	cac.Init("ABCDEFGHIJK");
	cac.BatchRemoveElements(2, 2, 3, 3);
	AssertString("ABEHK", cac.GetArray());

	cac.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayMinimalTemplateInt(void)
{
	CArrayIntMinimal	cai;

	cai.Init();
	cai.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArrayMinimalTemplate(void)
{
	BeginTests();

	TestArrayMinimalTemplateChar();
	TestArrayMinimalTemplateInt();

	TestStatistics();
}

