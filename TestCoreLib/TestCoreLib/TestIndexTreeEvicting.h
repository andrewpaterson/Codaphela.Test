#ifndef __TEST_INDEX_TREE_EVICTING_H__
#define __TEST_INDEX_TREE_EVICTING_H__
#include "CoreLib/IndexTreeEvicting.h"


class CTestIndexTreeEvicting : public CIndexTreeEvicting
{
public:
	CIndexTreeNodeFile* GetRoot(void)
	{
		return CIndexTreeEvicting::GetRoot();
	}

	size_t GetSystemMemorySize(void)
	{
		return CIndexTreeEvicting::GetSystemMemorySize();
	}

	int NumMemoryNodes(void)
	{
		return CIndexTreeEvicting::NumMemoryNodes();
	}

	int NumMemoryElements(void)
	{
		return CIndexTreeEvicting::NumMemoryElements();
	}
};


#endif // !__TEST_INDEX_TREE_EVICTING_H__

