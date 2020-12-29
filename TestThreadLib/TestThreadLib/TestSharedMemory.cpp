#include <thread>
#include "BaseLib/Logger.h"
#include "ThreadLib/SharedMemory.h"
#include "ThreadLib/InterProcessMutex.h"
#include "ThreadLib/ProcessFork.h"
#include "ThreadLib/Thread.h"
#include "TestLib/Assert.h"
#include "SharedMemoryThread.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSharedMemoryOneProcess(void)
{
	CSharedMemory	cSharedOwner;
	CSharedMemory	cSharedClient;
	BOOL			bResult;
	char*			pcOwner;
	char*			pcClient;
	int				i;

	cSharedOwner.Init("Local\\TestSharedMemoryOneProcess");
	bResult = cSharedOwner.Create(256);
	AssertTrue(bResult);

	pcOwner = (char*)cSharedOwner.GetMemory();
	AssertNotNull(pcOwner);

	for (i = 0; i < 256; i++)
	{
		pcOwner[i] = (char)i;
	}

	cSharedClient.Init("Local\\TestSharedMemoryOneProcess");
	bResult = cSharedClient.Connect();
	AssertTrue(bResult);

	pcClient = (char*)cSharedClient.GetMemory();
	AssertNotNull(pcClient);

	for (i = 0; i < 256; i++)
	{
		AssertChar((char)i, pcClient[i]);
	}

	cSharedOwner.Close();
	cSharedOwner.Kill();

	cSharedClient.Close();
	cSharedClient.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSharedMemoryResizeOneProcess(void)
{
	CSharedMemory	cSharedOwner;
	CSharedMemory	cSharedClient;
	CSharedMemory	cSharedNewOwner;
	BOOL			bResult;
	char*			pcOwner;
	char*			pcClient;
	int				i;
	int				iStillMapped;

	cSharedOwner.Init("Local\\TestSharedMemoryResizeOneProcess");
	bResult = cSharedOwner.Create(3940);
	AssertTrue(bResult);

	pcOwner = (char*)cSharedOwner.GetMemory();
	AssertNotNull(pcOwner);

	for (i = 0; i < 3940; i++)
	{
		pcOwner[i] = (char)i;
	}

	cSharedClient.Init("Local\\TestSharedMemoryResizeOneProcess");
	bResult = cSharedClient.Connect();
	AssertTrue(bResult);

	pcClient = (char*)cSharedClient.GetMemory();
	AssertNotNull(pcClient);
	for (i = 0; i < 3940; i++)
	{
		AssertChar((char)i, pcClient[i]);
	}

	cSharedOwner.Close();

	cSharedNewOwner.Init("Local\\TestSharedMemoryResizeOneProcess");
	gcLogger.SetBreakOnError(FALSE);
	bResult = cSharedNewOwner.Create(3940 + 16);
	gcLogger.SetBreakOnError(TRUE);
	AssertFalse(bResult);
	cSharedNewOwner.Kill();

	cSharedClient.Resize(3940 + 16);
	pcClient = (char*)cSharedClient.GetMemory();
	AssertNotNull(pcClient);
	for (i = 0; i < 3940; i++)
	{
		AssertChar((char)i, pcClient[i]);
	}

	bResult = cSharedOwner.Connect();
	AssertTrue(bResult);

	pcOwner = (char*)cSharedOwner.GetMemory();
	AssertNotNull(pcOwner);
	for (i = 0; i < 3940; i++)
	{
		AssertChar((char)i, pcOwner[i]);
	}

	iStillMapped = cSharedOwner.Close();
	AssertInt(1, iStillMapped);
	iStillMapped = cSharedClient.Close();
	AssertInt(0, iStillMapped);

	cSharedNewOwner.Init("Local\\TestSharedMemoryResizeOneProcess");
	bResult = cSharedNewOwner.Connect();
	AssertFalse(bResult);
	cSharedNewOwner.Kill();

	cSharedOwner.Kill();
	cSharedClient.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSharedMemoryTwoProcesses(void)
{
	CSharedMemory	cSharedOwner;
	BOOL			bResult;
	unsigned char*	pcOwner;
	int				i, j;
	char			szSharedMemoryName[] = {"Local\\TestSharedMemoryTwoProcesses"};
	BOOL			bAllMatch;

	cSharedOwner.Init(szSharedMemoryName);
	bResult = cSharedOwner.Create(256);
	AssertTrue(bResult);

	pcOwner = (unsigned char*)cSharedOwner.GetMemory();
	AssertNotNull(pcOwner);

	for (i = 0; i < 256; i++)
	{
		pcOwner[i] = (char)i;
	}

	ForkProcess("--test-shared-memory", szSharedMemoryName, "256", FALSE);

	for (j = 0; j < 50; j++)
	{
		bAllMatch = TRUE;
		for (i = 0; i < 256; i++)
		{
			if (255 - (unsigned char)i != pcOwner[i])
			{
				bAllMatch = FALSE;
				break;
			}
		}

		if (bAllMatch)
		{
			Pass();
			break;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}
	AssertTrue(bAllMatch);

	for (i = 0; i < 256; i++)
	{
		AssertChar(255 - (unsigned char)i, pcOwner[i]);
	}

	cSharedOwner.Close();
	cSharedOwner.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSharedMemoryResizeMultiThread(void)
{
	CSharedMemory			cSharedOwner;
	CInterProcessMutex		cMutex;
	BOOL					bResult;
	char					szSharedMemoryName[] = { "Local\\TestSharedMemoryResizeMultiThread" };
	char					szMutexName[] = { "Local\\TestMutexResizeMultiThread" };
	unsigned int*			puiPosition;
	unsigned int			uiPosition;
	CSharedMemoryThread		cThreadA;
	CSharedMemoryThread		cThreadB;
	CSharedMemoryThread		cThreadC;
	CSharedMemoryThread		cThreadD;

	cMutex.Init(szMutexName);
	bResult = cMutex.Create();
	AssertTrue(bResult);

	cSharedOwner.Init(szSharedMemoryName);
	bResult = cSharedOwner.Create(4 + 16);
	AssertTrue(bResult);

	puiPosition = (unsigned int*)cSharedOwner.GetMemory();
	AssertNotNull(puiPosition);

	memset(puiPosition, 0, 4 + 16);
	*puiPosition = 4;

	cThreadA.Init(szSharedMemoryName, szMutexName, "A");
	cThreadB.Init(szSharedMemoryName, szMutexName, "B");
	cThreadC.Init(szSharedMemoryName, szMutexName, "C");
	cThreadD.Init(szSharedMemoryName, szMutexName, "D");

	cThreadA.Start();
	cThreadB.Start();
	cThreadC.Start();
	cThreadD.Start();

	for (;;)
	{
		bResult = cMutex.Lock();
		cSharedOwner.Touch();

		puiPosition = (unsigned int*)cSharedOwner.GetMemory();
		AssertNotNull(puiPosition);
		uiPosition = *puiPosition;
		bResult = cMutex.Unlock();

		if (uiPosition == 4 + 16 * 1000)
		{
			break;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}

	cThreadA.Kill();
	cThreadB.Kill();
	cThreadC.Kill();
	cThreadD.Kill();

	cSharedOwner.Close();
	cSharedOwner.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSharedMemoryResizeMultiProcess(void)
{
	CSharedMemory		cSharedOwner;
	CInterProcessMutex	cMutex;
	BOOL				bResult;
	char				szSharedMemoryName[] = { "Local\\TestSharedMemoryResizeMultiProcess" };
	char				szMutexName[] = { "Local\\TestMutexResizeMultiProcess" };
	unsigned int*		puiPosition;
	unsigned int		uiPosition;

	cMutex.Init(szMutexName);
	bResult = cMutex.Create();
	AssertTrue(bResult);

	cSharedOwner.Init(szSharedMemoryName);
	bResult = cSharedOwner.Create(4 + 16);
	AssertTrue(bResult);

	puiPosition = (unsigned int*)cSharedOwner.GetMemory();
	AssertNotNull(puiPosition);

	memset(puiPosition, 0, 4 + 16);
	*puiPosition = 4;

	ForkProcess("--test-shared-memory", szSharedMemoryName, szMutexName, "A", FALSE);
	ForkProcess("--test-shared-memory", szSharedMemoryName, szMutexName, "B", FALSE);
	ForkProcess("--test-shared-memory", szSharedMemoryName, szMutexName, "C", FALSE);
	ForkProcess("--test-shared-memory", szSharedMemoryName, szMutexName, "D", FALSE);
	
	for (;;)
	{
		bResult = cMutex.Lock();
		cSharedOwner.Touch();

		puiPosition = (unsigned int*)cSharedOwner.GetMemory();
		AssertNotNull(puiPosition);
		uiPosition = *puiPosition;
		bResult = cMutex.Unlock();

		if (uiPosition == 4 + 16 * 1000)
		{
			break;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}

	cSharedOwner.Close();
	cSharedOwner.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSharedMemory(void)
{
	BeginTests();

	//TestSharedMemoryOneProcess();
	//TestSharedMemoryTwoProcesses();
	//TestSharedMemoryResizeOneProcess();
	TestSharedMemoryResizeMultiThread();
	//TestSharedMemoryResizeMultiProcess();

	TestStatistics();
}

