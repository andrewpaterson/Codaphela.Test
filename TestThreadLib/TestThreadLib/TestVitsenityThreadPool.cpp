#include "BaseLib/DebugOutput.h"
#include "BaseLib/GlobalMemory.h"
#include "BaseLib/ArrayTemplate.h"
#include "BaseLib/LogString.h"
#include "ThreadLib/VitsenityThreadPool.h"
#include "ThreadLib/SafeArrayBlock.h"
#include "TestLib/Assert.h"


#define TEST_THREAD_INTEGER_COUNT 10000


class CPusher
{
private:
	int					mix;
	int					miThreadId;
	CSafeArrayBlock*	mpcArray;
	BOOL				mbRunning;

public:
	void Init(int x, CSafeArrayBlock* pcArray)
	{
		mix = x;
		mpcArray = pcArray;
		miThreadId = -1;
		mbRunning = TRUE;
	}

	void Start(int iThreadId)
	{
		miThreadId = iThreadId;
	}

	void Run(void)
	{
		int i;

		for (i = 0; i < TEST_THREAD_INTEGER_COUNT; i++)
		{
			mpcArray->Add(&mix);
		}
		mbRunning = FALSE;
	}

	BOOL IsDone(void)
	{
		return !mbRunning;
	}
};


void RunPusher(int iThreadId, CPusher* pcPusher)
{
	pcPusher->Start(iThreadId);
	pcPusher->Run();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestVitsenityThreadPoolConcurrency(void)
{
	CSafeArrayBlock				aiArray;
	CArrayTemplate<CPusher>		acPushers;
	int							i;
	CPusher*					pcPusher;
	int							iNumHardwareTheads;
	int							iDoneCount;
	int							iPrevX;
	int							iX;
	int							iGreatherThanCount;
	CVitsenityThreadPool					cPool;

	iNumHardwareTheads = std::thread::hardware_concurrency();
	acPushers.Init();
	aiArray.Init(sizeof(int));

	for (i = 0; i < iNumHardwareTheads * 2; i++)
	{
		pcPusher = acPushers.Add();
		pcPusher->Init(i + 101, &aiArray);
	}

	cPool.Init(iNumHardwareTheads * 2);
	for (i = 0; i < iNumHardwareTheads * 2; i++)
	{
		pcPusher = acPushers.Get(i);
		cPool.Push(RunPusher, pcPusher);
	}

	iDoneCount = 0;
	while (iDoneCount != iNumHardwareTheads * 2)
	{
		iDoneCount = 0;
		for (i = 0; i < iNumHardwareTheads * 2; i++)
		{
			pcPusher = acPushers.Get(i);
			if (pcPusher->IsDone())
			{
				iDoneCount++;
			}
		}
	}

	AssertInt((iNumHardwareTheads * TEST_THREAD_INTEGER_COUNT * 2),  aiArray.NumElements());
	Pass();

	iGreatherThanCount = 0;
	iPrevX = 0;
	for (i = 0; i < aiArray.NumElements(); i++)
	{
		aiArray.Get(i, &iX);
		if (iPrevX > iX)
		{
			iGreatherThanCount++;
		}
		iPrevX = iX;
	}

	AssertTrue(iGreatherThanCount > 0);
	AssertTrue(iGreatherThanCount < aiArray.NumElements());
	Pass();

	aiArray.Kill();
	acPushers.Kill();
	cPool.Stop(TRUE);
	cPool.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestVitsenityThreadPoolInitialiseAndKill(void)
{
	CVitsenityThreadPool		cPool;

	cPool.Init();
	cPool.Kill();
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestVitsenityThreadPool(void)
{
	BeginTests();
	MemoryInit();
	FastFunctionsInit();

	TestVitsenityThreadPoolInitialiseAndKill();
	TestVitsenityThreadPoolConcurrency();

	FastFunctionsKill();
	MemoryKill();
	TestStatistics();
}

