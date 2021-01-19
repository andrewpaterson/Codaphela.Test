#ifndef __SHARED_MEMORY_QUEUE_CONSUMER_THREAD_H__
#define __SHARED_MEMORY_QUEUE_CONSUMER_THREAD_H__
#include <thread>
#include "ThreadLib/SharedMemoryQueue.h"
#include "ThreadLib/Thread.h"
#include "SharedMemoryQueueTheadElement.h"


#define THREADED_SHARED_QUEUE_PRODUCE_SIZE 20000
class CSharedMemoryQueueConsumerThread : public CThread
{
CONSTRUCTABLE(CSharedMemoryQueueConsumerThread);
private:
	CSharedMemoryQueue	mcQueue;
	CThreadsDone*		mpcProducersDone;
	char(*				maszData)[THREADED_SHARED_QUEUE_PRODUCE_SIZE][257];

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
	CSharedMemoryQueueConsumerThread* Init(char* szName, CThreadsDone* pcProducersDone, char(* aszData)[THREADED_SHARED_QUEUE_PRODUCE_SIZE][257])
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
	void Kill()
	{
		mcQueue.Kill();
		CThread::Kill();
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	void Run(void)
	{
		BOOL						bResult;
		SSharedMemoryQueueElement	sConsumerData;
		size_t						uiSize;

		do
		{
			bResult = mcQueue.Pop(&sConsumerData, &uiSize, sizeof(SSharedMemoryQueueElement));
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

