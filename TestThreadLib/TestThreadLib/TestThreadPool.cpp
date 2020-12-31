#include "BaseLib/DebugOutput.h"
#include "BaseLib/GlobalMemory.h"
#include "BaseLib/ArrayTemplate.h"
#include "BaseLib/LogString.h"
#include "ThreadLib/ThreadPool.h"
#include "ThreadLib/ThreadsDone.h"
#include "ThreadLib/SafeArrayBlock.h"
#include "TestLib/Assert.h"
#include "Producer.h"
#include "Consumer.h"


class CConsumerTotal : public CThreadStateNotifer
{
public:
	std::atomic<int> miTotal;

	void Init(void)
	{
		miTotal = 0;
	}

	void ThreadStateChanged(CThread* pcThread, EThreadState eState)
	{
		CConsumer* pcConsumer;

		if (eState == TS_Stopped)
		{
			pcConsumer = (CConsumer*)pcThread;
			miTotal +=  pcConsumer->GetResult();
		}
	}
};


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestThreadPoolThreadDestroyed(void)
{
	CThreadPool			cPool;
	CProducer*			pcProducer;
	CConsumer*			pcConsumer;
	CSafeArrayBlock		cQueue;
	int					i;
	CArrayVoidPtr		apcConsumers;
	CThreadsDone		cProducersDone;
	CThreadsDone		cConsumersDone;
	CConsumerTotal		cTotal;

	cQueue.Init(sizeof(int));
	cPool.Init();

	apcConsumers.Init();
	cProducersDone.Init();
	cConsumersDone.Init();
	cTotal.Init();

	for (i = 0; i < 32; i++)
	{
		pcProducer = cPool.Add<CProducer>()->Init(&cQueue, 1000, 1);
		pcProducer->AddNotifier(&cProducersDone);
		pcProducer->Start();
	}
	pcProducer = NULL;

	for (i = 0; i < 3; i++)
	{
		pcConsumer = cPool.Add<CConsumer>()->Init(&cQueue);
		pcConsumer->AddNotifier(&cConsumersDone);
		pcConsumer->AddNotifier(&cTotal);
		apcConsumers.Add(pcConsumer);
		pcConsumer->Start();
	}
	pcConsumer = NULL;

	while(cProducersDone.miThreadsStopped < 32)
	{
		std::this_thread::yield();
	}

	for (i = 0; i < apcConsumers.NumElements(); i++)
	{
		pcConsumer = (CConsumer*)apcConsumers.GetPtr(i);
		pcConsumer->TryStop();
	}

	while (cConsumersDone.miThreadsStopped < 3)
	{
		std::this_thread::yield();
	}

	AssertInt(32000, cTotal.miTotal);

	apcConsumers.Kill();
	cPool.Kill();
	cQueue.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestThreadPool(void)
{
	BeginTests();
	MemoryInit();
	FastFunctionsInit();

	TestThreadPoolThreadDestroyed();

	FastFunctionsKill();
	MemoryKill();
	TestStatistics();
}

