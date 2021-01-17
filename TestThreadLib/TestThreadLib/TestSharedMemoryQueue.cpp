#include <thread>
#include "BaseLib/Logger.h"
#include "BaseLib/Chars.h"
#include "BaseLib/StdRandom.h"
#include "ThreadLib/InterProcessMutex.h"
#include "ThreadLib/ProcessFork.h"
#include "ThreadLib/SharedMemoryQueue.h"
#include "TestLib/Assert.h"
//#include "SharedMemoryQueueThread.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSharedMemoryQueueBasic(void)
{
	CSharedMemoryQueue	cQueue;
	BOOL				bResult;
	CChars				sz;
	char				szData[4 KB];
	size_t				uiDataSize;

	bResult = cQueue.Init("Test", 20 + sizeof(SMemoryCacheDescriptor));
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
	BOOL				bResult;
	int					iProduce;
	int					iTaken;
	int					iNumElements;
	CChars sz;


	cQueueProducer.Init("TestSharedMemoryQueueOne", 0);
	for (i = 0; i < 4; i++)
	{
		acQueueConsumer[i].Init("TestSharedMemoryQueueOne");
	}

	iSize = 100;
	c = 33;
	iProduce = 1000;
	cRandom.Init(723);

	for (i = 0; i < 200; i++)
	{
		iNumElements = cQueueProducer.NumElements();
		sz.Init()->Append(iNumElements)->AppendNewLine()->DumpKill();

		memset(acProducerData, c, iSize);
		cQueueProducer.Push(acProducerData, iSize);

		iNumElements = cQueueProducer.NumElements();
		sz.Init()->Append(iNumElements)->AppendNewLine()->DumpKill();

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
				iNumElements = cQueueProducer.NumElements();
				sz.Init()->Append(iNumElements)->AppendNewLine()->DumpKill();

				memset(acProducerData, c, iSize);
				cQueueProducer.Push(acProducerData, iSize);
				iProduce--;

				iNumElements = cQueueProducer.NumElements();
				sz.Init()->Append(iNumElements)->AppendNewLine()->DumpKill();

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
				sz.Init("\"")->AppendData(aacData[i - 1], uiSize, uiSize)->Append("\"")->AppendNewLine()->DumpKill();

				iTaken++;
				if (iTaken == 1000)
				{
					break;
				}
			}
			else
			{

			}
		}
	}

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
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSharedMemoryQueueMultiProcess(void)
{
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
	TestSharedMemoryQueueMultiProcess();

	TestStatistics();
}

