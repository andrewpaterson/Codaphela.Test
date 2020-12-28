#include <thread>
#include "ThreadLib/SharedMemory.h"
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
void TestSharedMemory(void)
{
	BeginTests();

	TestSharedMemoryOneProcess();
	TestSharedMemoryTwoProcesses();

	TestStatistics();
}

