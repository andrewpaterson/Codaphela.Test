#include <thread>
#include "BaseLib/Logger.h"
#include "BaseLib/StdRandom.h"
#include "ThreadLib/ResizableSharedMemory.h"
#include "ThreadLib/InterProcessMutex.h"
#include "ThreadLib/ProcessFork.h"
#include "ThreadLib/Thread.h"
#include "ThreadLib/ThreadsDone.h"
#include "TestLib/Assert.h"
#include "SharedMemoryThread.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void AssertMappedFile(char* szName, int iExpectedMappedCount)
{
	HANDLE			hMapFile;
	SSharedMemoryDescriptor* psDescriptor;

	hMapFile = OpenFileMapping(
		FILE_MAP_ALL_ACCESS,
		FALSE,
		szName);

	if (iExpectedMappedCount > 0)
	{
		if (hMapFile == NULL)
		{
			AssertTrue(hMapFile != NULL);
		}
		else
		{
			psDescriptor = (SSharedMemoryDescriptor*)MapViewOfFile(
				hMapFile,
				FILE_MAP_ALL_ACCESS,
				0,
				0,
				sizeof(SSharedMemoryDescriptor));
			AssertInt(psDescriptor->iMapCount, iExpectedMappedCount);
			UnmapViewOfFile(psDescriptor);
			CloseHandle(hMapFile);
		}
	}
	else
	{
		if (hMapFile != NULL)
		{
			CloseHandle(hMapFile);
		}
		AssertTrue(hMapFile == NULL);
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSharedMemoryOneProcess(void)
{
	CResizableSharedMemory	cSharedOwner;
	CResizableSharedMemory	cSharedClient;
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
	AssertMappedFile("Local\\TestSharedMemoryOneProcess:0", 2);

	cSharedOwner.Close();
	cSharedOwner.Kill();
	AssertMappedFile("Local\\TestSharedMemoryOneProcess:0", 1);

	cSharedClient.Close();
	cSharedClient.Kill();
	AssertMappedFile("Local\\TestSharedMemoryOneProcess:0", 0);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSharedMemoryResizeOneProcess(void)
{
	CResizableSharedMemory	cSharedOwner;
	CResizableSharedMemory	cSharedClient;
	CResizableSharedMemory	cSharedNewOwner;
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
	AssertTrue(bResult);
	cSharedNewOwner.Close();
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
	CResizableSharedMemory	cSharedOwner;
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
	CResizableSharedMemory	cSharedOwner;
	CResizableSharedMemory	cSharedClient[4];
	CResizableSharedMemory*	pcSharedClient;
	BOOL					bResult;
	char*					pcMemory;
	int						i;
	int						iChunkSize;
	unsigned int*			puiPosition;
	char					szMemoryName[] = { "Local\\TestSharedMemoryResizeOneProcessFill" };
	CRandom					cRandom;
	unsigned int			uiStop;
	char					cFillChar;
	void*					pvDest;

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
void TestSharedMemoryResizeOneProcessResizeAndRelease(void)
{
	CResizableSharedMemory	cSharedOwner;
	CResizableSharedMemory	cSharedClient[4];
	BOOL					bResult;
	int						i;
	char					szMemoryName[] = { "Local\\TestSharedMemoryResizeOneProcessResizeAndRelease" };
	CRandom					cRandom;

	cSharedOwner.Init(szMemoryName);
	bResult = cSharedOwner.Create(3000);
	AssertTrue(bResult);

	cSharedOwner.Touch();

	for (i = 0; i < 4; i++)
	{
		cSharedClient[i].Init(szMemoryName);
		cSharedClient[i].Touch();
	}

	cSharedClient[0].Resize(6700);
	cSharedClient[1].Touch();
	cSharedClient[2].Touch();
	cSharedClient[3].Touch();

	for (i = 0; i < 4; i++)
	{
		cSharedClient[i].Close();
	}

	cSharedOwner.Touch();
	cSharedOwner.Close();

	for (i = 0; i < 4; i++)
	{
		cSharedClient[i].Kill();
	}
	cSharedOwner.Kill();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestSharedMemoryResizeMultiThread(void)
{
	CResizableSharedMemory	cSharedOwner;
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
	CThreadsDone			cThreadsDone;

	cMutex.Init(szMutexName);
	bResult = cMutex.Create();
	AssertTrue(bResult);
	iChunkSize = 128;

	cSharedOwner.Init(szSharedMemoryName, "Owner");
	bResult = cSharedOwner.Create(sizeof(int) + iChunkSize);
	AssertTrue(bResult);

	puiPosition = (unsigned int*)cSharedOwner.Touch();
	AssertNotNull(puiPosition);

	memset(puiPosition, 0, sizeof(int) + iChunkSize);
	*puiPosition = sizeof(int);

	cThreadsDone.Init();
	cThreadA.Init(szSharedMemoryName, szMutexName, "A", iChunkSize)->AddNotifier(&cThreadsDone);
	cThreadB.Init(szSharedMemoryName, szMutexName, "B", iChunkSize)->AddNotifier(&cThreadsDone);
	cThreadC.Init(szSharedMemoryName, szMutexName, "C", iChunkSize)->AddNotifier(&cThreadsDone);
	cThreadD.Init(szSharedMemoryName, szMutexName, "D", iChunkSize)->AddNotifier(&cThreadsDone);

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

	while (cThreadsDone.miThreadsStopped < 4)
	{
		std::this_thread::yield();
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
	CResizableSharedMemory		cSharedOwner;
	CInterProcessMutex	cMutex;
	BOOL				bResult;
	char				szSharedMemoryName[] = { "Local\\TestSharedMemoryResizeMultiProcess" };
	char				szMutexName[] = { "Local\\TestMutexResizeMultiProcess" };
	unsigned int*		puiPosition;
	unsigned int		uiPosition;
	int					iChunkSize;
	char				szChunkSize[16];

	cMutex.Init(szMutexName);
	bResult = cMutex.Create();
	AssertTrue(bResult);
	iChunkSize = 16;
	IToA(iChunkSize, szChunkSize);

	cSharedOwner.Init(szSharedMemoryName);
	bResult = cSharedOwner.Create(sizeof(int) + iChunkSize);
	AssertTrue(bResult);

	puiPosition = (unsigned int*)cSharedOwner.Touch();
	AssertNotNull(puiPosition);

	memset(puiPosition, 0, sizeof(int) + iChunkSize);
	*puiPosition = sizeof(int);

	ForkProcess("--test-shared-memory", szSharedMemoryName, szMutexName, "A", szChunkSize, FALSE);
	ForkProcess("--test-shared-memory", szSharedMemoryName, szMutexName, "B", szChunkSize, FALSE);
	ForkProcess("--test-shared-memory", szSharedMemoryName, szMutexName, "C", szChunkSize, FALSE);
	ForkProcess("--test-shared-memory", szSharedMemoryName, szMutexName, "D", szChunkSize, FALSE);
	
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

	//TestSharedMemoryOneProcess();
	//TestSharedMemoryTwoProcesses();
	//TestSharedMemoryResizeOneProcess();
	//TestSharedMemoryResizeOneProcessFill();
	//TestSharedMemoryResizeOneProcessResizeAndRelease();
	TestSharedMemoryResizeMultiThread();
	//TestSharedMemoryResizeMultiProcess();

	TestStatistics();
}

