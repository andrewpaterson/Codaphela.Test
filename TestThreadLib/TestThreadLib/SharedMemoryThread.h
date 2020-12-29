#ifndef __SHARED_MEMORY_THREAD_H__
#define __SHARED_MEMORY_THREAD_H__
#include "ThreadLib/SharedMemory.h"
#include "ThreadLib/InterProcessMutex.h"
#include "ThreadLib/Thread.h"


class CSharedMemoryThread : public CThread
{
CONSTRUCTABLE(CSharedMemoryThread);
private:
	char*	mszSharedMemoryName;
	char*	mszMutexName;
	char*	mszFillChar;
	int		miResult;

public:
	CSharedMemoryThread(void) : CThread() {}
	CSharedMemoryThread(CThreadStarter* pcStarter, CThreadStateNotifer* pcNotify) : CThread(pcStarter, pcNotify) {}

	CSharedMemoryThread* Init(char* szSharedMemoryName, char* szMutexName, char* szFillChar)
	{
		CThread::Init();
		this->mszSharedMemoryName = szSharedMemoryName;
		this->mszMutexName = szMutexName;
		this->mszFillChar = szFillChar;
		miResult = 0;
		return this;
	}

	virtual void Run(void)
	{
		CSharedMemory			cSharedClient;
		BOOL					bResult;
		CInterProcessMutex		cMutex;
		unsigned int*			puiPosition;

		cMutex.Init(mszMutexName);
		cMutex.Connect();

		cSharedClient.Init(mszSharedMemoryName);

		for (;;)
		{
			cMutex.Lock();
			bResult = cSharedClient.Connect();
			if (!bResult)
			{
				cSharedClient.Close();
				cSharedClient.Kill();
				cMutex.Unlock();
				miResult = 1;
				return;
			}

			puiPosition = (unsigned int*)cSharedClient.GetMemory();
			if (puiPosition == NULL)
			{
				cSharedClient.Close();
				cSharedClient.Kill();
				cMutex.Unlock();
				miResult = 1;
				return;
			}

			if ((*puiPosition) == 4 + 16 * 1000)
			{
				cSharedClient.Close();
				cSharedClient.Kill();
				cMutex.Unlock();

				miResult = 0;
				return;

			}

			memset(RemapSinglePointer(puiPosition, (*puiPosition)), *mszFillChar, 16);

			(*puiPosition) = (*puiPosition) + 16;
			cMutex.Unlock();
		}
	}
};


#endif // __SHARED_MEMORY_THREAD_H__

