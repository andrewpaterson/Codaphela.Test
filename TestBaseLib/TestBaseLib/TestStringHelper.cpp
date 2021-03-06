#include "TestLib/Assert.h"
#include "BaseLib/StringHelper.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestStrCmp(void)
{
    int iResult;

    iResult = StringCompare("Hello", "Hello");
    AssertInt(0, iResult);

    iResult = StringCompare("", NULL);
    AssertInt(1, iResult);

    iResult = StringCompare(NULL, "");
    AssertInt(-1, iResult);

    iResult = StringCompare(NULL, NULL);
    AssertInt(0, iResult);

    iResult = StringCompare("", "");
    AssertInt(0, iResult);

    iResult = StringCompare("ABC", "XYZ");
    AssertInt(-1, iResult);

    iResult = StringCompare("xyz", "abc");
    AssertInt(1, iResult);

    iResult = StringCompare("abc", "abcd");
    AssertInt(-1, iResult);

    iResult = StringCompare("abcd", "abc");
    AssertInt(1, iResult);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestStrICmp(void)
{
    int iResult;

    iResult = StringInsensitiveCompare("Hello", "hello");
    AssertInt(0, iResult);

    iResult = StringInsensitiveCompare("", NULL);
    AssertInt(1, iResult);

    iResult = StringInsensitiveCompare(NULL, "");
    AssertInt(-1, iResult);

    iResult = StringInsensitiveCompare(NULL, NULL);
    AssertInt(0, iResult);

    iResult = StringInsensitiveCompare("", "");
    AssertInt(0, iResult);

    iResult = StringInsensitiveCompare("ABC", "XYZ");
    AssertInt(-1, iResult);

    iResult = StringInsensitiveCompare("xyz", "abc");
    AssertInt(1, iResult);

    iResult = StringInsensitiveCompare("abc", "abcd");
    AssertInt(-1, iResult);

    iResult = StringInsensitiveCompare("abcd", "abc");
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
    char    sz1[] = "Andrew";
    char    sz2[] = "andrew";

    AssertInt(0, MemICmp(sz1, sz2, 6));

    strcpy(sz1, "Bndrew");
    AssertInt(1, MemICmp(sz1, sz2, 6));
    Pass();

    AssertInt(-1, MemICmp(sz2, sz1, 6));
    Pass();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestMemSwp(void)
{
    char    sz1[] = "Andrew";
    char    sz2[] = "Claire";

    MemSwp(sz1, sz2, 6);
    AssertString("Claire", sz1);
    AssertString("Andrew", sz2);
    Pass();

    sz1[5] = '\0';
    sz2[5] = '\0';
    MemSwp(sz1, sz2, 5);
    AssertString("Andre", sz1);
    AssertString("Clair", sz2);
    Pass();

    sz1[4] = '\0';
    sz2[4] = '\0';
    MemSwp(sz1, sz2, 4);
    AssertString("Clai", sz1);
    AssertString("Andr", sz2);
    Pass();

    sz1[3] = '\0';
    sz2[3] = '\0';
    MemSwp(sz1, sz2, 3);
    AssertString("And", sz1);
    AssertString("Cla", sz2);
    Pass();

    sz1[2] = '\0';
    sz2[2] = '\0';
    MemSwp(sz1, sz2, 2);
    AssertString("Cl", sz1);
    AssertString("An", sz2);
    Pass();

    sz1[1] = '\0';
    sz2[1] = '\0';
    MemSwp(sz1, sz2, 1);
    AssertString("A", sz1);
    AssertString("C", sz2);
    Pass();

    MemSwp(sz1, sz2, 0);
    AssertString("A", sz1);
    AssertString("C", sz2);
    Pass();
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
void TestMemCmp(void)
{
    char    szAndrew[] = "Andrew";
    char    szANdrew[] = "ANdrew";
    char    szAndre[] = "Andre";
    int     iResult;

    iResult = MemCmp(szAndrew, 6, szANdrew, 6);
    AssertInt(1, iResult);
    iResult = MemCmp(szANdrew, 6, szAndrew, 6);
    AssertInt(-1, iResult);
    iResult = MemCmp(szAndrew, 6, szAndrew, 6);
    AssertInt(0, iResult);
    iResult = MemCmp(szAndre, 6, szAndrew, 6);
    AssertInt(-1, iResult);
    iResult = MemCmp(szAndrew, 6, szAndre, 6);
    AssertInt(1, iResult);
    iResult = MemCmp(szAndre, 6, szANdrew, 6);
    AssertInt(1, iResult);
    iResult = MemCmp(szANdrew, 6, szAndre, 6);
    AssertInt(-1, iResult);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestStringHelper(void)
{
	BeginTests();

    TestStrCmp();
	TestStrICmp();
	TestStrIStr();
	TestStrRev();
	TestMemICmp();
	TestIToA();
	TestToLower();
	TestToUpper();
    TestMemSwp();
    TestMemCmp();

	TestStatistics();
}

