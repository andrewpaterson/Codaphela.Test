#include <thread>
#include "BaseLib/Logger.h"
#include "BaseLib/Chars.h"
#include "BaseLib/StdRandom.h"
#include "ThreadLib/InterProcessMutex.h"
#include "ThreadLib/ProcessFork.h"
#include "ThreadLib/SharedMemoryQueue.h"
#include "ThreadLib/SharedMemory.h"
#include "ThreadLib/ThreadPool.h"
#include "ThreadLib/ThreadsDone.h"
#include "ThreadLib/InterProcessDone.h"
#include "TestLib/Assert.h"
#include "SharedMemoryQueueProducerThread.h"
#include "SharedMemoryQueueConsumerThread.h"
#include "TestSharedMemoryQueue.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSharedMemoryQueueBasic(void)
{
	CSharedMemoryQueue	cQueue;
	bool				bResult;
	CChars				sz;
	char				szData[4 KB];
	size_t				uiDataSize;

	bResult = cQueue.Init("TestSharedMemoryQueueBasic", 20 + sizeof(SMemoryCacheDescriptor));
	AssertTrue(bResult);
	AssertTrue(cQueue.IsEmpty());
	AssertInt(32, cQueue.GetCacheSize());

	sz.Init('A', 19);
	bResult = cQueue.Push(sz.Text(), sz.Length() + 1);  sz.Kill();
	AssertTrue(bResult);
	AssertFalse(cQueue.IsEmpty());
	AssertInt(32, cQueue.GetCacheSize());
	Pass();

	bResult = cQueue.Pop(szData, &uiDataSize, 4 KB);
	AssertTrue(bResult);
	AssertInt(20, uiDataSize);
	AssertString("AAAAAAAAAAAAAAAAAAA", szData);
	AssertTrue(cQueue.IsEmpty());
	AssertInt(32, cQueue.GetCacheSize());
	Pass();

	bResult = cQueue.Pop(szData, &uiDataSize, 4 KB);
	AssertFalse(bResult);
	AssertInt(0, uiDataSize);
	AssertTrue(cQueue.IsEmpty());

	sz.Init('B', 19);
	bResult = cQueue.Push(sz.Text(), sz.Length() + 1);  sz.Kill();
	AssertTrue(bResult);
	AssertFalse(cQueue.IsEmpty());
	AssertInt(32, cQueue.GetCacheSize());
	cQueue.ValidateQueue();
	Pass();

	sz.Init('C', 19);
	bResult = cQueue.Push(sz.Text(), sz.Length() + 1);  sz.Kill();
	AssertTrue(bResult);
	AssertInt(84, cQueue.GetCacheSize());
	Pass();

	bResult = cQueue.Pop(szData, &uiDataSize, 4 KB);
	AssertTrue(bResult);
	AssertInt(20, uiDataSize);
	AssertString("BBBBBBBBBBBBBBBBBBB", szData);
	AssertFalse(cQueue.IsEmpty());
	AssertInt(84, cQueue.GetCacheSize());
	Pass();

	bResult = cQueue.Pop(szData, &uiDataSize, 4 KB);
	AssertTrue(bResult);
	AssertInt(20, uiDataSize);
	AssertString("CCCCCCCCCCCCCCCCCCC", szData);
	AssertTrue(cQueue.IsEmpty());
	AssertInt(84, cQueue.GetCacheSize());
	Pass();

	cQueue.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CreateExpectedString(CChars* psz, int iProduce)
{
	int		i;
	char	c;
	char	acProducerData[256];
	int		iSize;

	iSize = 100;
	c = 33;

	for (i = 0; i < iProduce; i++)
	{
		memset(acProducerData, c, iSize);

		psz->Append((char*)acProducerData, iSize)->AppendNewLine();

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
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSharedMemoryQueueOne(void)
{
	CSharedMemoryQueue	cQueueProducer;
	CSharedMemoryQueue	acQueueConsumer[4];
	int					i;
	CRandom				cRandom;
	char				acProducerData[256];
	char				aacData[4][256];
	int					iSize;
	char				c;
	size_t				uiSize;
	bool				bResult;
	int					iProduce;
	int					iTaken;
	CChars				szExpected;
	CChars				szActual;

	cQueueProducer.Init("TestSharedMemoryQueueOne", 0);
	for (i = 0; i < 4; i++)
	{
		acQueueConsumer[i].Init("TestSharedMemoryQueueOne");
	}

	iSize = 100;
	c = 33;
	iProduce = 1000;
	cRandom.Init(723);

	szExpected.Init();
	szActual.Init();
	CreateExpectedString(&szExpected, 1000);

	for (i = 0; i < 200; i++)
	{
		memset(acProducerData, c, iSize);
		cQueueProducer.Push(acProducerData, iSize);
		iProduce--;

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
	Pass();

	AssertFalse(cQueueProducer.IsEmpty());
	Pass();
	AssertFalse(acQueueConsumer[0].IsEmpty());
	AssertFalse(acQueueConsumer[1].IsEmpty());
	AssertFalse(acQueueConsumer[2].IsEmpty());
	AssertFalse(acQueueConsumer[3].IsEmpty());
	Pass();

	iTaken = 0;
	for (;;)
	{
		i = cRandom.Next(0, 4);
		if (i == 0)
		{
			if (iProduce > 0)
			{
				memset(acProducerData, c, iSize);
				cQueueProducer.Push(acProducerData, iSize);
				iProduce--;

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
		}
		else
		{
			bResult = acQueueConsumer[i - 1].Pop(aacData[i - 1], &uiSize, 256);

			if (bResult)
			{
				szActual.Append(aacData[i - 1], uiSize)->AppendNewLine();

				iTaken++;
				if (iTaken == 1000)
				{
					break;
				}
			}
		}
	}

	AssertString(szExpected.Text(), szActual.Text());
	Pass();
	szExpected.Kill();
	szActual.Kill();

	for (i = 0; i < 4; i++)
	{
		acQueueConsumer[i].Kill();
	}
	cQueueProducer.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSharedMemoryQueueMultiThread(void)
{
	CSharedMemoryQueueProducerThread*	pcProducer;
	CSharedMemoryQueueConsumerThread*	pcConsumer1;
	CSharedMemoryQueueConsumerThread*	pcConsumer2;
	CSharedMemoryQueueConsumerThread*	pcConsumer3;
	CSharedMemoryQueueConsumerThread*	pcConsumer4;
	CThreadPool							cPool;
	CThreadsDone						cProducersDone;
	CThreadsDone						cConsumersDone;
	CChars								szExpected;
	CChars								szActual;
	int									i;
	SThreadedSharedQueueResult*			psResult;
	char								szSharedMemoryName[] = { "TestSharedMemoryQueueMultiThread" };
	CSharedMemoryQueue					cQueue;
	int									iTotalTaken;

	psResult = (SThreadedSharedQueueResult*)malloc(sizeof(SThreadedSharedQueueResult));
	memset(psResult, 0, sizeof(SThreadedSharedQueueResult));

	cPool.Init();

	cProducersDone.Init();
	cConsumersDone.Init();

	cQueue.Init(szSharedMemoryName, 0);

	pcProducer = cPool.Add<CSharedMemoryQueueProducerThread>()->Init(szSharedMemoryName);
	pcProducer->AddNotifier(&cProducersDone);

	pcProducer->Start();

	pcConsumer1 = cPool.Add<CSharedMemoryQueueConsumerThread>()->Init(szSharedMemoryName, &cProducersDone, psResult, 0);
	pcConsumer1->AddNotifier(&cConsumersDone);
	pcConsumer2 = cPool.Add<CSharedMemoryQueueConsumerThread>()->Init(szSharedMemoryName, &cProducersDone, psResult, 1);
	pcConsumer2->AddNotifier(&cConsumersDone);
	pcConsumer3 = cPool.Add<CSharedMemoryQueueConsumerThread>()->Init(szSharedMemoryName, &cProducersDone, psResult, 2);
	pcConsumer3->AddNotifier(&cConsumersDone);
	pcConsumer4 = cPool.Add<CSharedMemoryQueueConsumerThread>()->Init(szSharedMemoryName, &cProducersDone, psResult, 3);
	pcConsumer4->AddNotifier(&cConsumersDone);

	pcConsumer1->Start();
	pcConsumer2->Start();
	pcConsumer3->Start();
	pcConsumer4->Start();


	while ((cProducersDone.miThreadsStopped < 1) || (cConsumersDone.miThreadsStopped < 4))
	{
		std::this_thread::yield();
	}

	iTotalTaken = psResult->aiTaken[0] + psResult->aiTaken[1] + psResult->aiTaken[2] + psResult->aiTaken[3];
	AssertInt(THREADED_SHARED_QUEUE_PRODUCE_SIZE, iTotalTaken);

	szExpected.Init();
	CreateExpectedString(&szExpected, THREADED_SHARED_QUEUE_PRODUCE_SIZE);

	szActual.Init();
	for (i = 0; i < THREADED_SHARED_QUEUE_PRODUCE_SIZE; i++)
	{
		szActual.Append(psResult->aszData[i])->AppendNewLine();
	}

	AssertString(szExpected.Text(), szActual.Text());

	cPool.Kill();
	szExpected.Kill();
	szActual.Kill();

	cQueue.Kill();

	free(psResult);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSharedMemoryQueueMultiThreadThisProducer(void)
{
	CSharedMemoryQueue					cQueue;
	CSharedMemoryQueueConsumerThread*	pcConsumer;
	CThreadPool							cPool;
	CThreadsDone						cProducersDone;
	CThreadsDone						cConsumersDone;
	SThreadedSharedQueueResult*			psResult;
	CChars								szExpected;
	CChars								szActual;
	int									i;
	int									iProcess;
	int									iSize;
	char								c;
	bool								bDone;
	int									iProduce;
	SSharedMemoryQueueElement			sProducerData;
	char								szQueueName[] = "TestMultiThreadThisProducer";
	int									iTotalTaken;

	psResult = (SThreadedSharedQueueResult*)malloc(sizeof(SThreadedSharedQueueResult));
	memset(psResult, 0, sizeof(SThreadedSharedQueueResult));

	cPool.Init();

	cProducersDone.Init();
	cConsumersDone.Init();

	cQueue.Init(szQueueName, 0);

	iProcess = 0;

	bDone = false;
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

		if ((iProduce % 1000 == 999) && (iProcess < 4))
		{
			pcConsumer = cPool.Add<CSharedMemoryQueueConsumerThread>()->Init(szQueueName, &cProducersDone, psResult, iProcess);
			pcConsumer->AddNotifier(&cConsumersDone);
			pcConsumer->Start();
			iProcess++;
		}
	}
	bDone = true;
	cProducersDone.miThreadsStopped++;

	while (cConsumersDone.miThreadsStopped < 4)
	{
		std::this_thread::yield();
	}

	iTotalTaken = psResult->aiTaken[0] + psResult->aiTaken[1] + psResult->aiTaken[2] + psResult->aiTaken[3];
	AssertInt(THREADED_SHARED_QUEUE_PRODUCE_SIZE, iTotalTaken);

	szExpected.Init();
	CreateExpectedString(&szExpected, THREADED_SHARED_QUEUE_PRODUCE_SIZE);

	szActual.Init();
	for (i = 0; i < THREADED_SHARED_QUEUE_PRODUCE_SIZE; i++)
	{
		szActual.Append(psResult->aszData[i])->AppendNewLine();
	}
	AssertString(szExpected.Text(), szActual.Text());

	cPool.Kill();
	szExpected.Kill();
	szActual.Kill();

	free(psResult);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSharedMemoryQueueMultiProcessForkDuring(void)
{
	CSharedMemoryQueue				cQueue;
	char							szQueueName[] = "TestSharedMemoryQueueMultiProcess";
	char							szSharedResultName[] = "TestSharedMemoryQueueMultiProcessResult";
	char							szDoneName[] = "TestSharedMemoryQueueMultiProcessDone";
	int								iProduce;
	SSharedMemoryQueueElement		sProducerData;
	int								iSize;
	char							c;
	bool							bDone;
	CSharedMemory					cResult;
	SProcessSharedQueueResult*		psResult;
	CInterProcessDone				cProcessesDone;
	CChars							szExpected;
	CChars							szActual;
	int								i;
	int								iProcess;
	char							szProcess[16];
	int								iTotalTaken;

	cResult.Init(szSharedResultName);
	psResult = (SProcessSharedQueueResult*)cResult.Create(sizeof(SProcessSharedQueueResult));
	memset(psResult, 0, sizeof(SProcessSharedQueueResult));

	cProcessesDone.Init(szDoneName);
	cProcessesDone.Start();
	iProcess = 0;

	cQueue.Init(szQueueName, 0);

	iSize = 100;
	c = 33;
	bDone = false;
	for (iProduce = 0; iProduce < PROCESS_SHARED_QUEUE_PRODUCE_SIZE; iProduce++)
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

		if ((iProduce % 1000 == 999) && (iProcess < 4))
		{
			ForkProcess("--test-shared-queue", szQueueName, szSharedResultName, szDoneName, IntToString(szProcess, 16, iProcess), false);
			iProcess++;
		}
	}
	bDone = true;

	cProcessesDone.Stop();
	cProcessesDone.Wait(5);

	cQueue.Kill();
	cProcessesDone.Kill();

	iTotalTaken = psResult->aiTaken[0] + psResult->aiTaken[1] + psResult->aiTaken[2] + psResult->aiTaken[3];
	AssertInt(PROCESS_SHARED_QUEUE_PRODUCE_SIZE, iTotalTaken);

	szExpected.Init();
	CreateExpectedString(&szExpected, PROCESS_SHARED_QUEUE_PRODUCE_SIZE);

	szActual.Init();
	for (i = 0; i < PROCESS_SHARED_QUEUE_PRODUCE_SIZE; i++)
	{
		szActual.Append(psResult->aszData[i])->AppendNewLine();
	}
	AssertString(szExpected.Text(), szActual.Text());

	szActual.Kill();
	szExpected.Kill();
	
	cResult.Close();
	cResult.Kill();
}

//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSharedMemoryQueueMultiProcessForkEarly(void)
{
	CSharedMemoryQueue				cQueue;
	char							szQueueName[] = "TestSharedMemoryQueueMultiProcess";
	char							szSharedResultName[] = "TestSharedMemoryQueueMultiProcessResult";
	char							szDoneName[] = "TestSharedMemoryQueueMultiProcessDone";
	int								iProduce;
	SSharedMemoryQueueElement		sProducerData;
	int								iSize;
	char							c;
	bool							bDone;
	CSharedMemory					cResult;
	SProcessSharedQueueResult* psResult;
	CInterProcessDone				cProcessesDone;
	CChars							szExpected;
	CChars							szActual;
	int								i;
	int								iTotalTaken;

	cResult.Init(szSharedResultName);
	psResult = (SProcessSharedQueueResult*)cResult.Create(sizeof(SProcessSharedQueueResult));
	memset(psResult, 0, sizeof(SProcessSharedQueueResult));

	cProcessesDone.Init(szDoneName);
	cProcessesDone.Start();

	cQueue.Init(szQueueName, 0);
	ForkProcess("--test-shared-queue", szQueueName, szSharedResultName, szDoneName, "0", false);
	ForkProcess("--test-shared-queue", szQueueName, szSharedResultName, szDoneName, "1", false);
	ForkProcess("--test-shared-queue", szQueueName, szSharedResultName, szDoneName, "2", false);
	ForkProcess("--test-shared-queue", szQueueName, szSharedResultName, szDoneName, "3", false);

	iSize = 100;
	c = 33;
	bDone = false;
	for (iProduce = 0; iProduce < PROCESS_SHARED_QUEUE_PRODUCE_SIZE; iProduce++)
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
	bDone = true;

	cProcessesDone.Stop();
	cProcessesDone.Wait(5);

	cQueue.Kill();
	cProcessesDone.Kill();

	iTotalTaken = psResult->aiTaken[0] + psResult->aiTaken[1] + psResult->aiTaken[2] + psResult->aiTaken[3];
	AssertInt(PROCESS_SHARED_QUEUE_PRODUCE_SIZE, iTotalTaken);

	szExpected.Init();
	CreateExpectedString(&szExpected, PROCESS_SHARED_QUEUE_PRODUCE_SIZE);

	szActual.Init();
	for (i = 0; i < PROCESS_SHARED_QUEUE_PRODUCE_SIZE; i++)
	{
		szActual.Append(psResult->aszData[i])->AppendNewLine();
	}
	AssertString(szExpected.Text(), szActual.Text());

	szActual.Kill();
	szExpected.Kill();

	cResult.Close();
	cResult.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSharedMemoryQueue(void)
{
	BeginTests();

	TestSharedMemoryQueueBasic();
	TestSharedMemoryQueueOne();
	TestSharedMemoryQueueMultiThread();
	TestSharedMemoryQueueMultiThreadThisProducer();
	TestSharedMemoryQueueMultiProcessForkDuring();
	TestSharedMemoryQueueMultiProcessForkEarly();

	TestStatistics();
}

