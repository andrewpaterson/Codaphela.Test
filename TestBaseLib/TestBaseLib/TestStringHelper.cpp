#include "TestLib/Assert.h"
#include "BaseLib/StringHelper.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestStrICmp(void)
{
    int iResult;

    iResult = StrICmp("Hello", "hello");
    AssertInt(0, iResult);

    iResult = StrICmp("", NULL);
    AssertInt(1, iResult);

    iResult = StrICmp(NULL, "");
    AssertInt(-1, iResult);

    iResult = StrICmp(NULL, NULL);
    AssertInt(0, iResult);

    iResult = StrICmp("", "");
    AssertInt(0, iResult);

    iResult = StrICmp("ABC", "XYZ");
    AssertInt(-23, iResult);

    iResult = StrICmp("xyz", "abc");
    AssertInt(23, iResult);

    iResult = StrICmp("abc", "abcd");
    AssertInt(-1, iResult);

    iResult = StrICmp("abcd", "abc");
    AssertInt(1, iResult);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestStrIStr(void)
{
    char    szFooBar[] = "FooBar";
    char*   sz;

    sz = StrIStr(szFooBar, "bar");
    AssertString("Bar", sz);

	sz = StrIStr(szFooBar, "FOO");
	AssertString("FooBar", sz);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMemICmp(void)
{
    //Ah, fuckit.
}



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestStrRev(void)
{
    char    szAndrew[] = "Andrew";
    char    szCat[] = "cat";
    char    szMinus[] = "1-";

    StrRev(szCat);
    AssertString("tac", szCat);

    StrRev(szAndrew);
    AssertString("werdnA", szAndrew);

    StrRev(szMinus);
    AssertString("-1", szMinus);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIToA(void)
{
    char    sz[256];

    IToA(7, sz, 10);
    AssertString("7", sz);

    IToA(456, sz, 10);
    AssertString("456", sz);

    IToA(12, sz, 10);
    AssertString("12", sz);

    IToA(-1, sz, 10);
    AssertString("-1", sz);

    IToA(-32456, sz, 10);
    AssertString("-32456", sz);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestToLower(void)
{
	char	szTest[] = "In The Age of C:\\ to Fractions %^&222";
	char	szExpected[] = "in the age of c:\\ to fractions %^&222";

	ToLower(szTest);
	AssertString(szExpected, szTest);
}



//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestToUpper(void)
{
	char	szTest[] = "In The Age of C:\\ to Fractions %^&222";
	char	szExpected[] = "IN THE AGE OF C:\\ TO FRACTIONS %^&222";

	ToUpper(szTest);
	AssertString(szExpected, szTest);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestStringHelper(void)
{
	BeginTests();

	TestStrICmp();
	TestStrIStr();
	TestStrRev();
	TestMemICmp();
	TestIToA();
	TestToLower();
	TestToUpper();

	TestStatistics();
}

