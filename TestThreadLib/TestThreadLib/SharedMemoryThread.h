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
	int		miChunkSize;

public:
	CSharedMemoryThread(void) : CThread() {}
	CSharedMemoryThread(CThreadStarter* pcStarter, CThreadStateNotifer* pcNotify) : CThread(pcStarter, pcNotify) {}

	CSharedMemoryThread* Init(char* szSharedMemoryName, char* szMutexName, char* szFillChar, int iChunkSize)
	{
		CThread::Init();
		this->mszSharedMemoryName = szSharedMemoryName;
		this->mszMutexName = szMutexName;
		this->mszFillChar = szFillChar;
		miResult = 0;
		miChunkSize = iChunkSize;
		return this;
	}


	virtual void Run(void)
	{
		CSharedMemory			cSharedClient;
		BOOL					bResult;
		CInterProcessMutex		cMutex;
		unsigned int*			puiPosition;
		unsigned int			uiStop;
		void*					pvDest;

		uiStop = 16004;

		cMutex.Init(mszMutexName);
		cMutex.Connect();

		cSharedClient.Init(mszSharedMemoryName);

		for (;;)
		{
			cMutex.Lock();
			bResult = cSharedClient.Touch();
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

			if ((*puiPosition) == uiStop)
			{
				cSharedClient.Close();
				cSharedClient.Kill();
				cMutex.Unlock();

				miResult = 0;
				return;
			}

			pvDest = RemapSinglePointer(puiPosition, (*puiPosition));
			CChars sz;
			sz.Init("Memset [");
			sz.Append(mszFillChar);
			sz.Append("] into ");
			sz.AppendHexHiLo(&puiPosition, 4);
			sz.Append(" + ");
			sz.Append(*puiPosition);
			sz.Dump();
			sz.Kill();
			
			memset(pvDest, *mszFillChar, miChunkSize);

			sz.Init(".  Done\n");
			sz.Dump();
			sz.Kill();

			(*puiPosition) = (*puiPosition) + miChunkSize;

			cSharedClient.Resize((*puiPosition) + miChunkSize);

			cMutex.Unlock();
		}
	}
};


#endif // __SHARED_MEMORY_THREAD_H__

