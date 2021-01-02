#include <thread>
#include "BaseLib/Logger.h"
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
void TestSharedMemoryQueueOne(void)
{
	CSharedMemoryQueue	cQueue;
	BOOL				bResult;
	CChars				sz;
	char				szData[4 KB];
	size_t				uiDataSize;

	bResult = cQueue.Init(TRUE, "Test", 20 + sizeof(SMemoryCacheDescriptor));
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
	AssertInt(32, cQueue.GetCacheSize());
	Pass();

	bResult = cQueue.Pop(szData, &uiDataSize, 4 KB);
	AssertTrue(bResult);
	AssertInt(20, uiDataSize);
	AssertString("C", szData);
	AssertTrue(cQueue.IsEmpty());
	AssertInt(32, cQueue.GetCacheSize());
	Pass();


	bResult = cQueue.Pop(szData, &uiDataSize, 4 KB);
	AssertTrue(bResult);
	AssertInt(20, uiDataSize);
	AssertString("B", szData);
	AssertTrue(cQueue.IsEmpty());
	AssertInt(32, cQueue.GetCacheSize());
	Pass();

	cQueue.Kill();
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

	TestSharedMemoryQueueOne();
	TestSharedMemoryQueueMultiThread();
	TestSharedMemoryQueueMultiProcess();

	TestStatistics();
}

