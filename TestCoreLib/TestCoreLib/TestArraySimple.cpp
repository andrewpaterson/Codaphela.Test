#include "BaseLib/AdditionalTypes.h"
#include "BaseLib/ArraySimpleChar.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestArraySimple(void)
{
	BeginTests();

	CArraySimpleChar	cac;

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

	TestStatistics();
}

