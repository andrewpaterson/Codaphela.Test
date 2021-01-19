//#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  

//#include <crtdbg.h>  

#include "BaseLib/Logger.h"
#include "ThreadLib/MainProcessDirector.h"
#include "TestLib/Assert.h"

int TestClientProcessMain(int argc, char* argv[]);
int TestSharedMemoryProcessMain(int argc, char* argv[]);
int TestSharedQueueProcessMain(int argc, char* argv[]);

void TestMainProcessDirector(int argc, char* argv[]);
void TestReferences(void);
void TestSafeArrayBlock(void);
void TestVitsenityThreadPool(void);
void TestThread(void);
void TestThreadPool(void);
void TestProcessFork(void);
void TestSharedMemory(void);
void TestSharedMemoryQueue(void);


int TestThreadLib(int argc, char* argv[])
{
	int iResult;

	InitTotalStatistics();

	TestMainProcessDirector(argc, argv);
	//TestReferences();
	//TestThread();
	//TestVitsenityThreadPool();
	//TestSafeArrayBlock();
	//TestThreadPool();
	//TestProcessFork();
	//TestSharedMemory();
	TestSharedMemoryQueue();

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
	cDirector.AddRedirect("test", TestThreadLib);
	cDirector.AddRedirect("test-client-process", TestClientProcessMain);
	cDirector.AddRedirect("test-shared-memory", TestSharedMemoryProcessMain);
	cDirector.AddRedirect("test-shared-queue", TestSharedQueueProcessMain);
	
	bMainRan = cDirector.Run(argc, argv);
	if (!bMainRan)
	{
		gcLogger.Init();
		gcLogger.Error2(__METHOD__, " TestThreadLib must be run with command line parameter [--test param1 --param:2]", NULL);
		gcLogger.Kill();
	}
	return cDirector.GetResult();
}

