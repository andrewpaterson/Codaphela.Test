#include "BaseLib/TextParser.h"
#include "BaseLib/Numbers.h"
#include "TestLib/Assert.h"


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
void TestSkipWhiteSpaceWithCStyleComments(void)
{
	CTextParser		cParser;
	char			szIdentifier[1 KB];
	int				iLength;
	TRISTATE		/* / * Hello */ tResult;

	cParser.Init("  /* /* Hello */  X");
	cParser.SkipWhiteSpace();
	tResult = cParser.GetIdentifier(szIdentifier, &iLength, FALSE, FALSE);
	AssertTristate(TRITRUE, tResult);
	AssertString("X", szIdentifier);
	cParser.Kill();
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
void TestSkipWhiteSpaceWithCppStyleComments(void)
{
	CTextParser		cParser;
	char			szIdentifier[1 KB];
	int				iLength;
	TRISTATE		tResult;  //

	cParser.Init("  //\n  //\n  X");
	cParser.SkipWhiteSpace();
	tResult = cParser.GetIdentifier(szIdentifier, &iLength, FALSE, FALSE);
	AssertTristate(TRITRUE, tResult);
	AssertString("X", szIdentifier);
	cParser.Kill();
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
void TestSkipCStyleComment(void)
{
	CTextParser		cParser;
	char			szComment[1 KB];
	int				iLength;
	TRISTATE		tResult;

	cParser.Init("  /*Hello*/  X");
	tResult = cParser.GetComment(szComment, &iLength, TRUE);
	AssertTristate(TRITRUE, tResult);
	AssertString("Hello", szComment);
	cParser.Kill();
}


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
void TestSkipCppStyleComment(void)
{
	CTextParser		cParser;
	char			szComment[1 KB];
	int				iLength;
	TRISTATE		tResult;

	cParser.Init("  //Hello\n  //World");
	tResult = cParser.GetComment(szComment, &iLength, TRUE);
	AssertTristate(TRITRUE, tResult);
	AssertString("Hello", szComment);
	tResult = cParser.GetComment(szComment, &iLength, TRUE);
	AssertTristate(TRITRUE, tResult);
	AssertString("World", szComment);
	cParser.Kill();
}



//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
void TestSkipComments(void)
{
	BeginTests();

	TestSkipWhiteSpaceWithCppStyleComments();
	TestSkipWhiteSpaceWithCStyleComments();
	TestSkipCppStyleComment();
	TestSkipCStyleComment();

	TestStatistics();
}

