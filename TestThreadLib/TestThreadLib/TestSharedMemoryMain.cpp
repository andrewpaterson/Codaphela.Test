#include "ThreadLib/SharedMemory.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
int TestSharedMemoryProcessMain(int argc, char* argv[])
{
	CSharedMemory	cSharedClient;
	BOOL			bResult;
	unsigned char*	pcClient;
	int				i;
	int				iMemorySize;

	if (argc == 2)
	{
		iMemorySize = atoi(argv[1]);
		bResult = cSharedClient.Connect(argv[0], 256);
		if (!bResult)
		{
			return 1;
		}

		pcClient = (unsigned char*)cSharedClient.GetMemory();
		if (pcClient == NULL)
		{
			cSharedClient.Close();
			return 1;
		}

		for (i = 0; i <= 255; i++)
		{
			pcClient[i] = 255 - pcClient[i];
		}
		
		cSharedClient.Close();
		return 0;
	}
	else
	{
		return 1;
	}
}

