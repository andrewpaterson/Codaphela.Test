//#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  

//#include <crtdbg.h>  

#include "BaseLib/Logger.h"
#include "ThreadLib/MainProcessDirector.h"
#include "TestLib/Assert.h"

int ClientMain(int argc, char* argv[]);

void TestMainProcessDirector(int argc, char* argv[]);
void TestReferences(void);
void TestSafeArrayBlock(void);
void TestVitsenityThreadPool(void);
void TestThread(void);
void TestThreadPool(void);
void TestProcess(void);


int TestThreadLib(int argc, char* argv[])
{
	int iResult;

	InitTotalStatistics();

	TestMainProcessDirector(argc, argv);
	TestReferences();
	TestThread();
	TestVitsenityThreadPool();
	TestSafeArrayBlock();
	TestThreadPool();
	TestProcess();

	iResult = TestTotalStatistics();
	return iResult;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
	CMainProcessDirector	cDirector;
	BOOL					bMainRan;

	cDirector.Init();
	cDirector.AddRedirect("Client", ClientMain);
	cDirector.AddRedirect("Test", TestThreadLib);
	bMainRan = cDirector.Run(argc, argv);
	if (!bMainRan)
	{
		gcLogger.Init();
		gcLogger.Error2(__METHOD__, " TestThreadLib must be run with command line parameter [--test param1 --param:2]", NULL);
		gcLogger.Kill();
	}
	return cDirector.GetResult();
}

