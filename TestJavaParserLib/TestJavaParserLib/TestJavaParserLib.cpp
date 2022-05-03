#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  

#include "TestLib/Assert.h"

void TestTokenParser(void);
void TestSkipComments(void);
void TestJavaParserGetInteger(void);
void TestJavaParserGetFloat(void);
void TestJavaParserGetCharacter(void);
void TestJavaParserGetString(void);
void TestJavaParserPrintFloat(void);


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
int __cdecl main(void)
{
	_CrtSetBreakAlloc(0);
	
	int	iTotalTestsFailed;

	InitTotalStatistics();
	FastFunctionsInit();
	NumberInit();

	TestJavaParserPrintFloat();
	TestSkipComments();
	TestJavaParserGetInteger();
	TestJavaParserGetCharacter();
	TestJavaParserGetString();
	TestJavaParserGetFloat();
	TestTokenParser();

	iTotalTestsFailed = TestTotalStatistics();

	FastFunctionsKill();
	NumberKill();
	_CrtDumpMemoryLeaks();
	return iTotalTestsFailed;
}

