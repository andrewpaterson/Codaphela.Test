#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  

#include "TestLib/Assert.h"


void TestPreprocessor(void);
void TestProject(void);


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int __cdecl main(void)
{
	_CrtSetBreakAlloc(15105);
	
	int	iTotalTestsFailed;

	InitTotalStatistics();

	//TestPreprocessor();
	TestProject();

	iTotalTestsFailed = TestTotalStatistics();

	_CrtDumpMemoryLeaks();
	return iTotalTestsFailed;
}

