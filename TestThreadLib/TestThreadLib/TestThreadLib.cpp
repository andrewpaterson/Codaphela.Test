//#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
//#include <crtdbg.h>  

#include "TestLib/Assert.h"


void TestSafeArrayBlock(void);


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int main(void)
{
	int iResult;

	InitTotalStatistics();

	TestSafeArrayBlock();

	iResult = TestTotalStatistics();
	return iResult;
}

