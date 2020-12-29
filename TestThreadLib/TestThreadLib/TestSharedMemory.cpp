#include <thread>
#include "ThreadLib/SharedMemory.h"
#include "ThreadLib/InterProcessMutex.h"
#include "ThreadLib/ProcessFork.h"
#include "TestLib/Assert.h"


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
	char* pcOwner;
	char* pcClient;
	int				i;

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
	bResult = cSharedNewOwner.Create(3940 + 16);
	AssertTrue(bResult);


	cSharedClient.Resize(3940 + 16);
	bResult = cSharedClient.Connect();
	AssertTrue(bResult);

	pcClient = (char*)cSharedClient.GetMemory();
	AssertNotNull(pcClient);

	for (i = 0; i < 3940; i++)
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
void TestSharedMemoryResizeMultiProcess(void)
{
	CSharedMemory		cSharedOwner;
	CInterProcessMutex	cMutex;
	BOOL				bResult;
	char				szSharedMemoryName[] = { "Local\\TestSharedMemoryTwoProcesses" };
	char				szMutexName[] = { "Local\\TestMutexTwoProcesses" };
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
		cMutex.Lock();
		cSharedOwner.Touch();

		puiPosition = (unsigned int*)cSharedOwner.GetMemory();
		AssertNotNull(puiPosition);
		uiPosition = *puiPosition;
		cMutex.Unlock();

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

	TestSharedMemoryOneProcess();
	TestSharedMemoryTwoProcesses();
	TestSharedMemoryResizeOneProcess();
	TestSharedMemoryResizeMultiProcess();

	TestStatistics();
}

