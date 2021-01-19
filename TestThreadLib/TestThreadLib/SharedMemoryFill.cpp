#include "ThreadLib/ResizableSharedMemory.h"
#include "ThreadLib/InterProcessMutex.h"
#include "ThreadLib/InterProcessHold.h"
#include "ThreadLib/InterProcessDone.h"
#include "SharedMemoryFill.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CSharedMemoryFill::Init(char* szSharedMemoryName, char* szMutexName, char* szFillChar, int iChunkSize)
{
	mszSharedMemoryName = szSharedMemoryName;
	mszMutexName = szMutexName;
	mszFillChar = szFillChar;
	miResult = 0;
	miChunkSize = iChunkSize;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void CSharedMemoryFill::Run(void)
{
	CResizableSharedMemory	cSharedClient;
	CInterProcessMutex		cMutex;
	unsigned int*			puiPosition;
	unsigned int			uiStop;
	void*					pvDest;
	CInterProcessHold		cHold;
	CInterProcessDone		cDone;

	uiStop = 16000 + sizeof(int);

	cMutex.Init(mszMutexName);
	cMutex.Connect();

	cHold.Init(mszSharedMemoryName, ":H");
	cHold.Touch();
	cDone.Init(mszSharedMemoryName, ":D");
	cDone.Open();

	cSharedClient.Init(mszSharedMemoryName, mszFillChar);

	for (;;)
	{
		cMutex.Lock();

		puiPosition = (unsigned int*)cSharedClient.Touch();
		if (puiPosition == NULL)
		{
			cSharedClient.Close();
			cSharedClient.Kill();
			cMutex.Unlock();
			cHold.Kill();
			cDone.Stop();
			cDone.Kill();

			miResult = 1;
			return;
		}

		if ((*puiPosition) == uiStop)
		{
			cSharedClient.Close();
			cMutex.Unlock();

			cHold.Wait();
			cHold.Kill();

			cMutex.Lock();
			cSharedClient.Kill();
			cMutex.Unlock();

			cDone.Stop();
			cDone.Kill();

			miResult = 0;
			return;
		}

		pvDest = RemapSinglePointer(puiPosition, (*puiPosition));
		memset(pvDest, *mszFillChar, miChunkSize);
		(*puiPosition) = (*puiPosition) + miChunkSize;
		cSharedClient.Resize((*puiPosition) + miChunkSize);

		cMutex.Unlock();
	}
}

