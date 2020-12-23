#ifndef __PRODUCER_H__
#define __PRODUCER_H__
#include "ThreadLib/Thread.h"
#include "ThreadLib/SafeArrayBlock.h"


class CProducer : public CThread
{
CONSTRUCTABLE(CProducer);
private:
	CSafeArrayBlock*	mpcQueue;
	int					miProductionCount;
	int					miProductionValue;

public:
	CProducer(void) : CThread() {}
	CProducer(CThreadStarter* pcStarter, CThreadStateNotifer* pcNotify) : CThread(pcStarter, pcNotify) {}

	CProducer* Init(CSafeArrayBlock* pcQueue, int iProductionCount, int iProductionValue)
	{
		CThread::Init();
		mpcQueue = pcQueue;
		miProductionCount = iProductionCount;
		miProductionValue = iProductionValue;
		return this;
	}

	virtual void Run(void)
	{
		int i;
		for (i = 0; i < miProductionCount && IsRunning(); i++)
		{
			mpcQueue->Push(&miProductionValue);
		}
		i = 0;
	}
};


#endif // __PRODUCER_H__

