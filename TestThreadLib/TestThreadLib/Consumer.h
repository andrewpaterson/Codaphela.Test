#ifndef __CONSUMER_H__
#define __CONSUMER_H__
#include "ThreadLib/Thread.h"
#include "ThreadLib/SafeArrayBlock.h"


class CConsumer : public CThread
{
CONSTRUCTABLE(CConsumer);
private:
	CSafeArrayBlock*	mpcQueue;
	int					miResult;

public:
	CConsumer(void) : CThread() {}
	CConsumer(CThreadStarter* pcStarter, CThreadStateNotifer* pcNotify) : CThread(pcStarter, pcNotify)	{}

	CConsumer* Init(CSafeArrayBlock* pcQueue)
	{
		CThread::Init();
		mpcQueue = pcQueue;
		miResult = 0;
		return this;
	}

	virtual void Run(void)
	{
		int		iResult;
		BOOL	bResult;

		while (IsRunning() || mpcQueue->IsNotEmpty())
		{
			bResult = mpcQueue->PopFirst(&iResult);
			if (bResult)
			{
				miResult += iResult;
			}
		}
	}

	int GetResult(void)
	{
		return miResult;
	}
};


#endif // __CONSUMER_H__

