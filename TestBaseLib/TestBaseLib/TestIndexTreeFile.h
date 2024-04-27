#ifndef __TEST_INDEX_TREE_FILE_H__
#define __TEST_INDEX_TREE_FILE_H__
#include "BaseLib/IndexTreeFile.h"


class CTestIndexTreeFile : public CIndexTreeFile
{
public:
	void FakeInit(EIndexKeyReverse eKeyReverse)
	{
		CIndexTree::Init(LifeLocal<CMallocator>(&gcSystemAllocator), eKeyReverse, sizeof(CIndexTreeNodeFile), sizeof(CIndexTreeNodeFile) + sizeof(CIndexTreeDataNode), sizeof(CIndexTreeChildNode), MAX_DATA_SIZE, MAX_KEY_SIZE, LifeNull<CIndexTreeDataOrderer>());
		mpcRoot = NULL;
		mpcDurableFileControl = NULL;
	}

	size_t ByteSize(void)
	{
		return CIndexTreeFile::ByteSize();
	}

	size_t GetUserMemorySize(void)
	{
		return CIndexTreeFile::ByteSize();
	}
	size_t GetSystemMemorySize(void)
	{
		return CIndexTreeFile::GetSystemMemorySize();
	}

	CIndexedFiles* GetIndexFiles(void)
	{
		return CIndexTreeFile::GetIndexFiles();
	}

	void GetFiles(CArrayIndexedFilePtr* pac)
	{
		return CIndexTreeFile::GetFiles(pac);
	}

	CIndexedFile* GetFile(int iFile)
	{
		return CIndexTreeFile::GetFile(iFile);
	}

	int NumNodes(void)
	{
		return CIndexTreeFile::NumNodes();
	}

	int NumMemoryNodes(void)
	{
		return CIndexTreeFile::NumMemoryNodes();
	}

	int NumMemoryElements(void)
	{
		return CIndexTreeFile::NumMemoryElements();
	}

	void SetWriteThrough(EIndexWriteThrough eWriteThrough)
	{
		CIndexTreeFile::SetWriteThrough(eWriteThrough);
	}

	bool ValidateIndexTree(bool bReadNodes)
	{
		return CIndexTreeFile::ValidateIndexTree(bReadNodes);
	}

	bool ValidateIndexTree(void)
	{
		return CIndexTreeFile::ValidateIndexTree();
	}

	bool ValidateKey(void* pvKey, int iKeySize)
	{
		return CIndexTreeFile::ValidateKey(pvKey, iKeySize);
	}

	CIndexTreeNodeFile* GetNode(void* pvKey, int iKeySize)
	{
		return CIndexTreeFile::GetNode(pvKey, iKeySize);
	}

	int GetNodeKeySize(CIndexTreeNodeFile* pcNode)
	{
		return CIndexTreeFile::GetNodeKeySize(pcNode);
	}

	int GetNodeKey(CIndexTreeNodeFile* pcNode, char* pvDestKey, int iDestKeySize)
	{
		return CIndexTreeFile::GetNodeKey(pcNode, pvDestKey, iDestKeySize);
	}

	CIndexTreeNodeFile* GetRoot(void)
	{
		return CIndexTreeFile::GetRoot();
	}

	void GetNodeKey(CIndexTreeNodeFile* pcNode, CArrayChar* pacKey)
	{
		CIndexTree::GetNodeKey(pcNode, pacKey);
	}

	CListCharsMinimal* GetNodesStringKeys(CArrayVoidPtr* apvNodes)
	{
		return CIndexTreeFile::GetNodesStringKeys(apvNodes);
	}
};


#endif // __TEST_INDEX_TREE_FILE_H__


