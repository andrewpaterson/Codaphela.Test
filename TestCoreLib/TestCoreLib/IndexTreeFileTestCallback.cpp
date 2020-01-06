#include "IndexTreeCallbackTestObject.h"
#include "IndexTreeFileTestCallback.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
unsigned short	CIndexTreeFileTestCallback::IndexTreeDataSize(unsigned short uiSourceSize)
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
BOOL CIndexTreeFileTestCallback::IndexTreeWriteData(void* pvDataBuffer, void* pvSource, int iFileDataSize, unsigned short uiSourceDataSize)
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
BOOL CIndexTreeFileTestCallback::IndexTreeReadData(void* pvDest, void* pvDataBuffer, unsigned short uiDestDataSize, int iFileDataSize)
{
	STestIndexTreeFileObject*		psFileObject;
	CTestIndexTreeMemoryObject*		pcMemoryObject;

	psFileObject = (STestIndexTreeFileObject*)pvDataBuffer;
	pcMemoryObject = (CTestIndexTreeMemoryObject*)pvDest;

	pcMemoryObject->Init(17, psFileObject->i2, 56, psFileObject->i4);

	return TRUE;
}

