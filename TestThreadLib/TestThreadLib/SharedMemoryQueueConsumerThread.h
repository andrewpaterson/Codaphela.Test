#ifndef __SHARED_MEMORY_QUEUE_CONSUMER_THREAD_H__
#define __SHARED_MEMORY_QUEUE_CONSUMER_THREAD_H__
#include <thread>
#include "ThreadLib/SharedMemoryQueue.h"
#include "ThreadLib/Thread.h"


class CSharedMemoryQueueConsumerThread : public CThread
{
CONSTRUCTABLE(CSharedMemoryQueueConsumerThread);
private:
	CSharedMemoryQueue	mcQueue;
	CThreadsDone*		mpcProducersDone;

public:
	CSharedMemoryQueueConsumerThread(void) : CThread() {}
	CSharedMemoryQueueConsumerThread(CThreadStarter* pcStarter, CThreadStateNotifer* pcNotify) : CThread(pcStarter, pcNotify) {}

	CSharedMemoryQueueConsumerThread* Init(char* szName, CThreadsDone* pcProducersDone)
	{
		mpcProducersDone = pcProducersDone;
		CThread::Init();
		mcQueue.Init(szName);
		return this;
	}

	virtual void Run(void)
	{
		BOOL	bResult;
		char	acData[256];
		size_t	uiSize;

		do
		{
			bResult = mcQueue.Pop(acData, &uiSize, 256);
			if (bResult)
			{
			}
			else
			{
				std::this_thread::yield();
			}
		} while ((mpcProducersDone->miThreadsStopped < 1) || bResult);

	}
};


#endif // __SHARED_MEMORY_QUEUE_CONSUMER_THREAD_H__


