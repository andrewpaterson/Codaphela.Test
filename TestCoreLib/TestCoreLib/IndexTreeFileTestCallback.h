#ifndef __INDEX_TREE_FILE_TEST_CALLBACK_H__
#define __INDEX_TREE_FILE_TEST_CALLBACK_H__
#include "CoreLib/IndexTreeFileCallback.h"


class CIndexTreeFileTestCallback : public CIndexTreeFileCallback
{
public:
	unsigned short	IndexTreeDataSize(unsigned short uiSourceSize);
	BOOL			IndexTreeWriteData(void* pvDataBuffer, void* pvSource, int iFileDataSize, unsigned short uiSourceDataSize);
	BOOL			IndexTreeReadData(void* pvDest, void* pvDataBuffer, unsigned short uiDestDataSize, int iFileDataSize);
};


#endif // __INDEX_TREE_FILE_TEST_CALLBACK_H__

