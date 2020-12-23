//#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
//#include <crtdbg.h>  

#include "TestLib/Assert.h"


void TestReferences(void);
void TestSafeArrayBlock(void);
void TestVitsenityThreadPool(void);
void TestThread(void);
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
	TestThread();
	TestVitsenityThreadPool();
	TestSafeArrayBlock();
	TestThreadPool();

	iResult = TestTotalStatistics();
	return iResult;
}

