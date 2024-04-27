#ifndef __INDEX_TREE_FILE_TEST_CALLBACK_H__
#define __INDEX_TREE_FILE_TEST_CALLBACK_H__
#include "BaseLib/IndexTreeFileDataCallback.h"


class CIndexTreeFileDataTestCallback : public CIndexTreeFileDataCallback
{
public:
	uint16			IndexTreeDataSize(uint16 uiSourceSize);
	bool			IndexTreeWriteData(void* pvDataBuffer, void* pvSource, int iFileDataSize, uint16 uiSourceDataSize);
	bool			IndexTreeReadData(void* pvDest, void* pvDataBuffer, uint16 uiDestDataSize, int iFileDataSize);
};


#endif // __INDEX_TREE_FILE_TEST_CALLBACK_H__

