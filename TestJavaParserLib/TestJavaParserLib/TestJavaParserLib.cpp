#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  

#include "TestLib/Assert.h"


void TestTokenParser(void);
void TestSkipComments(void);


//////////////////////////////////////////////////////////////////////////
//																		//
//																		//
//////////////////////////////////////////////////////////////////////////
int __cdecl main(void)
{
	_CrtSetBreakAlloc(0);
	
	int	iTotalTestsFailed;

	InitTotalStatistics();

	TestSkipComments();
	TestTokenParser();

	iTotalTestsFailed = TestTotalStatistics();

	_CrtDumpMemoryLeaks();
	return iTotalTestsFailed;
}
