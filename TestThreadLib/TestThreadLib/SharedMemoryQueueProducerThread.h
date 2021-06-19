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
	CChars				mszName;

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
		mszName.Init(szName);
		return this;
	}


	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	void Kill()
	{
		mszName.Kill();
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
		CSharedMemoryQueue				cQueue;
		BOOL							bResult;

		bResult = cQueue.Init(mszName.Text());
		if (!bResult)
		{
			return;
		}

		bDone = FALSE;
		iSize = 100;
		c = 33;
		for (iProduce = 0; iProduce < THREADED_SHARED_QUEUE_PRODUCE_SIZE; iProduce++)
		{
			memset(sProducerData.sz, c, iSize);
			sProducerData.sz[iSize] = '\0';
			sProducerData.sHeader.miIndex = iProduce;
			sProducerData.sHeader.muiSize = iSize + 1 + sizeof(SSharedMemoryQueueElementHeader);
			cQueue.Push(&sProducerData, sProducerData.sHeader.muiSize);

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

		cQueue.Kill();
	}
};


#endif // !__SHARED_MEMORY_QUEUE_PRODUCER_THREAD_H__

