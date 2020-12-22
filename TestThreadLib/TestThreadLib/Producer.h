#ifndef __PRODUCER_H__
#define __PRODUCER_H__
#include "ThreadLib/Thread.h"
#include "ThreadLib/SafeArrayBlock.h"


class CProducer : public CThread
{
private:
	CSafeArrayBlock*	mpcQueue;
	int					miProductionCount;
	int					miProductionValue;

public:
	void Init(CSafeArrayBlock* pcQueue, int iProductionCount, int iProductionValue)
	{
		CThread::Init();
		mpcQueue = pcQueue;
		miProductionCount = iProductionCount;
		miProductionValue = iProductionValue;
	}

	virtual void Run(void)
	{
		int i;
		for (i = 0; i < miProductionCount && IsRunning(); i++)
		{
			mpcQueue->Push(&miProductionValue);
		}
	}
};


#endif // __PRODUCER_H__

