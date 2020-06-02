#ifndef __TEST_INDEX_TREE_MEMORY_H__
#define __TEST_INDEX_TREE_MEMORY_H__
#include "BaseLib/IndexTreeMemory.h"


class CTestIndexTreeMemory : public CIndexTreeMemory
{
public:
	void FakeInit(EIndexKeyReverse eKeyReverse)
	{
		//This exists so that TreeNodes can be tested without a full tree.  All they need to do is query the size of their child nodes.
		//Kill should not be called.
		CIndexTree::Init(NULL, eKeyReverse, sizeof(CIndexTreeNodeMemory), sizeof(CIndexTreeNodeMemory) + sizeof(CIndexTreeDataNode), sizeof(CIndexTreeNodeMemory*), MAX_DATA_SIZE, MAX_KEY_SIZE);
		mpcRoot = NULL;
		miSize = 0;
	}

	CIndexTreeNodeMemory* GetRoot(void)
	{
		return CIndexTreeMemory::GetRoot();
	}

	CIndexTreeNodeMemory* GetNode(void* pvKey, int iKeySize)
	{
		return CIndexTreeMemory::GetNode(pvKey, iKeySize);
	}

	BOOL ValidateSize(void)
	{
		return CIndexTreeMemory::ValidateSize();
	}

	int NumAllocatedNodes(void)
	{
		return CIndexTreeMemory::NumAllocatedNodes();
	}

	int RecurseSize(void)
	{
		return CIndexTreeMemory::RecurseSize();
	}
};


#endif // __TEST_INDEX_TREE_MEMORY_H__

