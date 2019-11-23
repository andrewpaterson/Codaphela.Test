#include "IndexTreeCallbackTestObject.h"
#include "IndexTreeFileTestCallback.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
unsigned short	CIndexTreeFileTestCallback::DataBufferSize(unsigned short uiSourceSize)
{
	if (uiSourceSize != 0)
	{
		return sizeof(STestIndexTreeFileObject);
	}
	else
	{
		return 0;
	}
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CIndexTreeFileTestCallback::WriteData(void* pvDataBuffer, void* pvSource, int iFileDataSize, unsigned short uiSourceDataSize)
{
	STestIndexTreeFileObject*		psFileObject;
	CTestIndexTreeMemoryObject*		pcMemoryObject;
	
	psFileObject = (STestIndexTreeFileObject*)pvDataBuffer;
	pcMemoryObject = (CTestIndexTreeMemoryObject*)pvSource;

	psFileObject->Init(pcMemoryObject->mi2, pcMemoryObject->mi4);

	return TRUE;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
BOOL CIndexTreeFileTestCallback::ReadData(void* pvDest, void* pvDataBuffer, unsigned short uiDestDataSize, int iFileDataSize)
{
	STestIndexTreeFileObject*		psFileObject;
	CTestIndexTreeMemoryObject*		pcMemoryObject;

	psFileObject = (STestIndexTreeFileObject*)pvDataBuffer;
	pcMemoryObject = (CTestIndexTreeMemoryObject*)pvDest;

	pcMemoryObject->Init(17, psFileObject->i2, 56, psFileObject->i4);

	return TRUE;
}

