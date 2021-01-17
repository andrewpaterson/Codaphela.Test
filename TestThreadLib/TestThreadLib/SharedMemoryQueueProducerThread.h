#ifndef __SHARED_MEMORY_QUEUE_PRODUCER_THREAD_H__
#define __SHARED_MEMORY_QUEUE_PRODUCER_THREAD_H__
#include "ThreadLib/SharedMemoryQueue.h"
#include "ThreadLib/Thread.h"


class CSharedMemoryQueueProducerThread : public CThread
{
CONSTRUCTABLE(CSharedMemoryQueueProducerThread);
private:
	CSharedMemoryQueue	mcQueue;

public:
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
	virtual void Run(void)
	{
		int		iProduce;
		char	acProducerData[256];
		int		iSize;
		char	c;
		BOOL	bDone;

		bDone = FALSE;
		iSize = 100;
		c = 33;
		for (iProduce = 1000; iProduce >= 0; iProduce--)
		{
			memset(acProducerData, c, iSize);
			mcQueue.Push(acProducerData, iSize);

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

