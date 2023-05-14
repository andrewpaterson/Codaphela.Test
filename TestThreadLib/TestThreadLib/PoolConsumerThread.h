#ifndef __POOL_CONSUMER_THREAD_H__
#define __POOL_CONSUMER_THREAD_H__
#include "ThreadLib/Thread.h"
#include "ThreadLib/SafeArrayBlock.h"


class CPoolConsumerThread : public CThread
{
CONSTRUCTABLE(CPoolConsumerThread);
private:
	CSafeArrayBlock*	mpcQueue;
	int					miResult;

public:
	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	CPoolConsumerThread(void) : CThread() {}
	CPoolConsumerThread(CThreadStarter* pcStarter, CThreadStateNotifer* pcNotify) : CThread(pcStarter, pcNotify)	{}


	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	CPoolConsumerThread* Init(CSafeArrayBlock* pcQueue)
	{
		CThread::Init();
		mpcQueue = pcQueue;
		miResult = 0;
		return this;
	}


	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	virtual void Run(void)
	{
		int		iResult;
		bool	bResult;

		while (IsRunning() || mpcQueue->IsNotEmpty())
		{
			bResult = mpcQueue->PopFirst(&iResult);
			if (bResult)
			{
				miResult += iResult;
			}
		}
	}


	//////////////////////////////////////////////////////////////////////////
	//
	//
	//////////////////////////////////////////////////////////////////////////
	int GetResult(void)
	{
		return miResult;
	}
};


#endif // !__POOL_CONSUMER_THREAD_H__

