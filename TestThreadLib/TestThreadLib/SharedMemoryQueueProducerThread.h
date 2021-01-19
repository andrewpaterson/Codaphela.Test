#ifndef __SHARED_MEMORY_QUEUE_PRODUCER_THREAD_H__
#define __SHARED_MEMORY_QUEUE_PRODUCER_THREAD_H__
#include "ThreadLib/SharedMemoryQueue.h"
#include "ThreadLib/Thread.h"
#include "SharedMemoryQueueTheadElement.h"
#include "SharedMemoryQueueConsumerThread.h"


class CSharedMemoryQueueProducerThread : public CThread
{
CONSTRUCTABLE(CSharedMemoryQueueProducerThread);
private:
	CSharedMemoryQueue	mcQueue;

public:
	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	CSharedMemoryQueueProducerThread(void) : CThread() {}
	CSharedMemoryQueueProducerThread(CThreadStarter* pcStarter, CThreadStateNotifer* pcNotify) : CThread(pcStarter, pcNotify) {}

	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	CSharedMemoryQueueProducerThread* Init(char* szName)
	{
		CThread::Init();
		mcQueue.Init(szName, 0);
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
		int								iProduce;
		SSharedMemoryQueueElement		sProducerData;
		int								iSize;
		char							c;
		BOOL							bDone;

		bDone = FALSE;
		iSize = 100;
		c = 33;
		for (iProduce = 0; iProduce < THREADED_SHARED_QUEUE_PRODUCE_SIZE; iProduce++)
		{
			memset(sProducerData.sz, c, iSize);
			sProducerData.sz[iSize] = '\0';
			sProducerData.sHeader.miIndex = iProduce;
			sProducerData.sHeader.muiSize = iSize + 1 + sizeof(SSharedMemoryQueueElementHeader);
			mcQueue.Push(&sProducerData, sProducerData.sHeader.muiSize);

			iSize++;
			if (iSize == 256)
			{
				iSize = 100;
			}

			c++;
			if (c == 122)
			{
				c = 33;
			}
		}
		bDone = TRUE;
	}
};


#endif // __SHARED_MEMORY_QUEUE_PRODUCER_THREAD_H__

