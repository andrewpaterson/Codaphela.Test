//#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
//#include <crtdbg.h>  

#include "TestLib/Assert.h"


void TestReferences(void);
void TestSafeArrayBlock(void);
void TestThreadPool(void);


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int main(void)
{
	int iResult;

	InitTotalStatistics();

	TestReferences();
	TestThreadPool();
	TestSafeArrayBlock();

	iResult = TestTotalStatistics();
	return iResult;
}

