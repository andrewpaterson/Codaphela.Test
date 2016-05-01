#include "TestLib/Assert.h"
#include "BaseLib/Chars.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestCharsSubStringEquals(void)
{
	CChars	sz;

	sz.Init("Happy");

	AssertTrue(sz.SubStringEquals(0, "Hap"));
	AssertTrue(sz.SubStringEquals(0, "Happy"));
	AssertTrue(sz.SubStringEquals(1, "app"));
	AssertTrue(sz.SubStringEquals(0, "H"));
	AssertTrue(sz.SubStringEquals(1, "a"));
	AssertTrue(sz.SubStringEquals(2, "p"));
	AssertTrue(sz.SubStringEquals(3, "p"));
	AssertTrue(sz.SubStringEquals(4, "y"));
	AssertTrue(sz.SubStringEquals(0, ""));

	AssertFalse(sz.SubStringEquals(1, "Hap"));
	AssertFalse(sz.SubStringEquals(-1, "Happy"));
	AssertFalse(sz.SubStringEquals(0, "app"));
	AssertFalse(sz.SubStringEquals(6, ""));
	AssertFalse(sz.SubStringEquals(7, ""));
	AssertFalse(sz.SubStringEquals(5, "y"));

	sz.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestChars(void)
{
	BeginTests();

	TestCharsSubStringEquals();

	TestStatistics();

}

