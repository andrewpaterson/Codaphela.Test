#include <thread>
#include "BaseLib/GlobalMemory.h"
#include "ThreadLib/SafeArrayBlock.h"
#include "ThreadLib/VitsenityThreadPool.h"
#include "TestLib/Assert.h"
#include "Producer.h"
#include "Consumer.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestThreadStandAlone(void)
{
	CProducer		cProducer1;
	CProducer		cProducer2;
	CProducer		cProducer3;
	CProducer		cProducer4;
	CProducer		cProducer5;

	CConsumer		cConsumer1;
	CConsumer		cConsumer2;

	int				iTotalResult;
	CSafeArrayBlock cQueue;
	
	cQueue.Init(sizeof(int));
	cProducer1.Init(&cQueue, 100, 200200);
	cProducer2.Init(&cQueue, 100, 1001);
	cProducer3.Init(&cQueue, 100, 1000000);
	cProducer4.Init(&cQueue, 100, 7);
	cProducer5.Init(&cQueue, 100, 13);
	cConsumer1.Init(&cQueue);
	cConsumer2.Init(&cQueue);

	cProducer1.Start();
	cProducer2.Start();
	cProducer3.Start();
	cProducer4.Start();
	cProducer5.Start();
	cConsumer1.Start();
	cConsumer2.Start();

	for (;;)
	{
		if (cProducer1.IsDone() &&
			cProducer2.IsDone() &&
			cProducer3.IsDone() &&
			cProducer4.IsDone() &&
			cProducer5.IsDone())
		{
			cConsumer1.TryStop();
			cConsumer2.TryStop();
		}

		if (cConsumer1.IsDone() &&
			cConsumer2.IsDone())
		{
			break;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}

	iTotalResult = cConsumer1.GetResult() + cConsumer2.GetResult();

	cProducer1.Kill();
	cProducer2.Kill();
	cProducer3.Kill();
	cProducer4.Kill();
	cProducer5.Kill();
	cConsumer1.Kill();
	cConsumer2.Kill();

	AssertInt(120122100, iTotalResult);

	cQueue.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestThreadInThreadPool(void)
{
	int							iTotalResult;
	CSafeArrayBlock				cQueue;
	CVitsenityThreadPool		cPool;
	int							iNumHardwareTheads;

	iNumHardwareTheads = std::thread::hardware_concurrency();
	cQueue.Init(sizeof(int));
	cPool.Init();

	iTotalResult = 0;

	//You should probably write this test.

	cPool.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestThread(void)
{
	BeginTests();
	MemoryInit();
	FastFunctionsInit();

	TestThreadStandAlone();
	TestThreadInThreadPool();

	FastFunctionsKill();
	MemoryKill();
	TestStatistics();
}

