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
	void Init(CSafeArrayBlock* pcQueue)
	{
		CThread::Init();
		mpcQueue = pcQueue;
		miResult = 0;
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

