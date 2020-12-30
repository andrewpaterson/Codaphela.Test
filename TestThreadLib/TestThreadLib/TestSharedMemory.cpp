#include <thread>
#include "BaseLib/Logger.h"
#include "BaseLib/StdRandom.h"
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

	pcOwner = (char*)cSharedOwner.Touch();
	AssertNotNull(pcOwner);

	for (i = 0; i < 256; i++)
	{
		pcOwner[i] = (char)i;
	}

	cSharedClient.Init("Local\\TestSharedMemoryOneProcess");
	bResult = cSharedClient.Connect();
	AssertTrue(bResult);

	pcClient = (char*)cSharedClient.Touch();
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

	pcOwner = (char*)cSharedOwner.Touch();
	AssertNotNull(pcOwner);

	for (i = 0; i < 3940; i++)
	{
		pcOwner[i] = (char)i;
	}

	cSharedClient.Init("Local\\TestSharedMemoryResizeOneProcess");
	pcClient = (char*)cSharedClient.Touch();
	AssertNotNull(pcClient);

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

	pcClient = (char*)cSharedClient.Resize(3940 + 16);
	AssertNotNull(pcClient);
	for (i = 0; i < 3940; i++)
	{
		AssertChar((char)i, pcClient[i]);
	}

	pcOwner = (char*)cSharedOwner.Touch();
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

	pcOwner = (unsigned char*)cSharedOwner.Touch();
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
void TestSharedMemoryResizeOneProcessFill(void)
{
	CSharedMemory	cSharedOwner;
	CSharedMemory	cSharedClient[4];
	CSharedMemory* pcSharedClient;
	BOOL			bResult;
	char* pcMemory;
	int				i;
	int				iChunkSize;
	unsigned int* puiPosition;
	char			szMemoryName[] = { "Local\\TestSharedMemoryResizeOneProcessFill" };
	CRandom			cRandom;
	unsigned int	uiStop;
	char			cFillChar;
	void* pvDest;

	iChunkSize = 128;
	uiStop = 16000 + sizeof(int);

	cSharedOwner.Init(szMemoryName);
	bResult = cSharedOwner.Create(sizeof(int) + iChunkSize);
	AssertTrue(bResult);

	pcMemory = (char*)cSharedOwner.Touch();
	memset(pcMemory, 0, sizeof(int) + iChunkSize);
	puiPosition = (unsigned int*)pcMemory;
	*puiPosition = 4;

	for (i = 0; i < 4; i++)
	{
		cSharedClient[i].Init(szMemoryName);
	}

	cSharedClient[0].Connect();
	cSharedOwner.Close();

	cRandom.Init(77);

	for (;;)
	{
		i = cRandom.Next(0, 3);
		pcSharedClient = &cSharedClient[i];
		cFillChar = 'A' + (char)i;

		puiPosition = (unsigned int*)pcSharedClient->Touch();
		if (puiPosition == NULL)
		{
			pcSharedClient->Close();
			pcSharedClient->Kill();
			AssertTrue(FALSE);
			break;
		}

		if ((*puiPosition) == uiStop)
		{
			pcSharedClient->Close();
			pcSharedClient->Kill();
			break;
		}

		pvDest = RemapSinglePointer(puiPosition, (*puiPosition));
		memset(pvDest, cFillChar, iChunkSize);

		(*puiPosition) = (*puiPosition) + iChunkSize;

		pcSharedClient->Resize((*puiPosition) + iChunkSize);
	}

	cSharedOwner.Connect();
	for (i = 0; i < 4; i++)
	{
		cSharedClient[i].Close();
		cSharedClient[i].Kill();
	}

	CChars	sz;
	int		iA;
	int		iB;
	int		iC;
	int		iD;
	pcMemory = (char*)RemapSinglePointer(cSharedOwner.Touch(), sizeof(int));
	for (i = 0; i < 16000 / iChunkSize; i++)
	{
		sz.Init();
		sz.Append(pcMemory, iChunkSize);
		sz.AppendNewLine();

		iA = sz.Count('A');
		iB = sz.Count('B');
		iC = sz.Count('C');
		iD = sz.Count('D');

		AssertTrue(iA == iChunkSize || iB == iChunkSize || iC == iChunkSize || iD == iChunkSize);
		AssertTrue(iA + iB + iC + iD == iChunkSize);

		sz.Kill();
		pcMemory = (char*)RemapSinglePointer(pcMemory, iChunkSize);
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
	int						iChunkSize;
	int						i;

	cMutex.Init(szMutexName);
	bResult = cMutex.Create();
	AssertTrue(bResult);
	iChunkSize = 129;

	cSharedOwner.Init(szSharedMemoryName, "Owner");
	bResult = cSharedOwner.Create(sizeof(int) + iChunkSize);
	AssertTrue(bResult);

	puiPosition = (unsigned int*)cSharedOwner.Touch();
	AssertNotNull(puiPosition);

	memset(puiPosition, 0, sizeof(int) + iChunkSize);
	*puiPosition = sizeof(int);

	cThreadA.Init(szSharedMemoryName, szMutexName, "A", iChunkSize);
	cThreadB.Init(szSharedMemoryName, szMutexName, "B", iChunkSize);
	cThreadC.Init(szSharedMemoryName, szMutexName, "C", iChunkSize);
	cThreadD.Init(szSharedMemoryName, szMutexName, "D", iChunkSize);

	cThreadA.Start();
	cThreadB.Start();
	cThreadC.Start();
	cThreadD.Start();


	for (;;)
	{
		bResult = cMutex.Lock();

		puiPosition = (unsigned int*)cSharedOwner.Touch();
		AssertNotNull(puiPosition);
		uiPosition = *puiPosition;

		bResult = cMutex.Unlock();

		if (uiPosition == 16000 + sizeof(int))
		{
			break;
		}

		std::this_thread::sleep_for(std::chrono::microseconds(1));
	}

	cThreadA.Kill();
	cThreadB.Kill();
	cThreadC.Kill();
	cThreadD.Kill();

	CChars	sz;
	int		iA;
	int		iB;
	int		iC;
	int		iD;
	char*	pcMemory;

	pcMemory = (char*)RemapSinglePointer(cSharedOwner.Touch(), sizeof(int));
	for (i = 0; i < 16000 / iChunkSize; i++)
	{
		sz.Init();
		sz.Append(pcMemory, iChunkSize);
		sz.AppendNewLine();

		iA = sz.Count('A');
		iB = sz.Count('B');
		iC = sz.Count('C');
		iD = sz.Count('D');

		AssertTrue(iA == iChunkSize || iB == iChunkSize || iC == iChunkSize || iD == iChunkSize);
		AssertTrue(iA + iB + iC + iD == iChunkSize);

		sz.Kill();
		pcMemory = (char*)RemapSinglePointer(pcMemory, iChunkSize);
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
	char				szSharedMemoryName[] = { "Local\\TestSharedMemoryResizeMultiProcess" };
	char				szMutexName[] = { "Local\\TestMutexResizeMultiProcess" };
	unsigned int*		puiPosition;
	unsigned int		uiPosition;
	int					iChunkSize;

	cMutex.Init(szMutexName);
	bResult = cMutex.Create();
	AssertTrue(bResult);
	iChunkSize = 16;

	cSharedOwner.Init(szSharedMemoryName);
	bResult = cSharedOwner.Create(sizeof(int) + iChunkSize);
	AssertTrue(bResult);

	puiPosition = (unsigned int*)cSharedOwner.Touch();
	AssertNotNull(puiPosition);

	memset(puiPosition, 0, sizeof(int) + iChunkSize);
	*puiPosition = sizeof(int);

	ForkProcess("--test-shared-memory", szSharedMemoryName, szMutexName, "A", FALSE);
	ForkProcess("--test-shared-memory", szSharedMemoryName, szMutexName, "B", FALSE);
	ForkProcess("--test-shared-memory", szSharedMemoryName, szMutexName, "C", FALSE);
	ForkProcess("--test-shared-memory", szSharedMemoryName, szMutexName, "D", FALSE);
	
	for (;;)
	{
		bResult = cMutex.Lock();

		puiPosition = (unsigned int*)cSharedOwner.Touch();
		AssertNotNull(puiPosition);
		uiPosition = *puiPosition;
		bResult = cMutex.Unlock();

		if (uiPosition == 16000 + sizeof(int))
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
	TestSharedMemoryResizeOneProcessFill();
	TestSharedMemoryResizeMultiThread();
	//TestSharedMemoryResizeMultiProcess();

	TestStatistics();
}


