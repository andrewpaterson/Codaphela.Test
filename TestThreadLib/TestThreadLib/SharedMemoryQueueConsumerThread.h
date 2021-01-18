#ifndef __SHARED_MEMORY_QUEUE_CONSUMER_THREAD_H__
#define __SHARED_MEMORY_QUEUE_CONSUMER_THREAD_H__
#include <thread>
#include "ThreadLib/SharedMemoryQueue.h"
#include "ThreadLib/Thread.h"
#include "SharedMemoryQueueTheadElement.h"


class CSharedMemoryQueueConsumerThread : public CThread
{
CONSTRUCTABLE(CSharedMemoryQueueConsumerThread);
private:
	CSharedMemoryQueue	mcQueue;
	CThreadsDone*		mpcProducersDone;
	char(*				maszData)[1000][257];

public:
	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	CSharedMemoryQueueConsumerThread(void) : CThread() {}
	CSharedMemoryQueueConsumerThread(CThreadStarter* pcStarter, CThreadStateNotifer* pcNotify) : CThread(pcStarter, pcNotify) {}


	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	CSharedMemoryQueueConsumerThread* Init(char* szName, CThreadsDone* pcProducersDone, char(* aszData)[1000][257])
	{
		mpcProducersDone = pcProducersDone;
		CThread::Init();
		mcQueue.Init(szName);
		maszData = aszData;
		return this;
	}


	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	virtual void Run(void)
	{
		BOOL								bResult;
		SSharedMemoryQueueThreadElement		sConsumerData;
		size_t								uiSize;

		do
		{
			bResult = mcQueue.Pop(&sConsumerData, &uiSize, sizeof(SSharedMemoryQueueThreadElement));
			if (bResult)
			{
				strcpy((*maszData)[sConsumerData.sHeader.miIndex], sConsumerData.sz);
			}
			else
			{
				std::this_thread::yield();
			}
		} while ((mpcProducersDone->miThreadsStopped < 1) || bResult);
	}
};


#endif // __SHARED_MEMORY_QUEUE_CONSUMER_THREAD_H__

