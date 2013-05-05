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
	AssertString("aabbc", cac.pvArray);

	cac.BatchInsertElements(0, 3, 2, 2);

	cac.pvArray[0]=cac.pvArray[1]=cac.pvArray[2]='_';
	cac.pvArray[5]=cac.pvArray[6]=cac.pvArray[7]='_';
	AssertString("___aa___bbc", cac.pvArray);

	cac.InsertNumElementsAt(2, 1);

	cac.pvArray[1]=cac.pvArray[2]='X';
	AssertString("_XX__aa___bbc", cac.pvArray);

	cac.Kill();

	cac.Init("ABCDEFGHIJK");
	cac.BatchRemoveElements(2, 2, 3, 3);
	AssertString("ABEHK", cac.pvArray);

	cac.Kill();

	TestStatistics();
}

