#include "BaseLib/DebugOutput.h"
#include "BaseLib/Logger.h"
#include "ThreadLib/SharedMemory.h"
#include "ThreadLib/InterProcessMutex.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int TestSharedMemoryProcessReverse(char* szSharedMemoryName, char* szMemorySize)
{
	CSharedMemory	cSharedClient;
	unsigned char*	pcClient;
	int				i;
	int				iMemorySize;
	
	iMemorySize = atoi(szMemorySize);
	cSharedClient.Init(szSharedMemoryName);

	pcClient = (unsigned char*)cSharedClient.Touch();
	if (pcClient == NULL)
	{
		cSharedClient.Close();
		return 1;
	}

	for (i = 0; i < iMemorySize; i++)
	{
		pcClient[i] = 255 - pcClient[i];
	}

	cSharedClient.Close();
	cSharedClient.Kill();

	return 0;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int TestSharedMemoryProcessFill(char* szSharedMemoryName, char* szMutexName, char* szFillChar, char* szChunkSize, char* szMaxBuffers)
{
	CSharedMemory			cSharedClient;
	CInterProcessMutex		cMutex;
	unsigned int*			puiPosition;
	int						iChunkSize;
	int						iMaxBuffers;

	iChunkSize = atoi(szChunkSize);
	iMaxBuffers = atoi(szMaxBuffers);

	cMutex.Init(szMutexName);
	cMutex.Connect();

	cSharedClient.Init(szSharedMemoryName);

	for (;;)
	{
		cMutex.Lock();

		puiPosition = (unsigned int*)cSharedClient.Touch();
		if (puiPosition == NULL)
		{
			cSharedClient.Close();
			cSharedClient.Kill();
			cMutex.Unlock();
			return 1;
		}

		if ((*puiPosition) == 16000 + sizeof(int))
		{
			cSharedClient.Close();
			cSharedClient.Kill();
			cMutex.Unlock();

			return 0;
		}

		memset(RemapSinglePointer(puiPosition, (*puiPosition)), *szFillChar, iChunkSize);

		(*puiPosition) = (*puiPosition) + iChunkSize;
		cMutex.Unlock();
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int TestSharedMemoryProcessMain(int argc, char* argv[])
{
	if (argc == 2)
	{
		return TestSharedMemoryProcessReverse(argv[0], argv[1]);
	}
	else if (argc == 5)
	{
		return TestSharedMemoryProcessFill(argv[0], argv[1], argv[2], argv[3], argv[4]);
	}
	else
	{
		return 1;
	}
}

