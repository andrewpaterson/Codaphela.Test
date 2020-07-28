#include "IndexTreeCallbackTestObject.h"
#include "IndexTreeFileDataTestCallback.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
unsigned short	CIndexTreeFileDataTestCallback::IndexTreeDataSize(unsigned short uiSourceSize)
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
BOOL CIndexTreeFileDataTestCallback::IndexTreeWriteData(void* pvDataBuffer, void* pvSource, int iFileDataSize, unsigned short uiSourceDataSize)
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
BOOL CIndexTreeFileDataTestCallback::IndexTreeReadData(void* pvDest, void* pvDataBuffer, unsigned short uiDestDataSize, int iFileDataSize)
{
	STestIndexTreeFileObject*		psFileObject;
	CTestIndexTreeMemoryObject*		pcMemoryObject;

	psFileObject = (STestIndexTreeFileObject*)pvDataBuffer;
	pcMemoryObject = (CTestIndexTreeMemoryObject*)pvDest;

	pcMemoryObject->Init(17, psFileObject->i2, 56, psFileObject->i4);

	return TRUE;
}

