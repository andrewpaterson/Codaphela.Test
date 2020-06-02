#ifndef __TEST_INDEX_TREE_FILE_H__
#define __TEST_INDEX_TREE_FILE_H__
#include "CoreLib/IndexTreeFile.h"


class CTestIndexTreeFile : public CIndexTreeFile
{
public:
	void FakeInit(EIndexKeyReverse eKeyReverse)
	{
		CIndexTree::Init(&gcSystemAllocator, eKeyReverse, sizeof(CIndexTreeNodeFile), sizeof(CIndexTreeNodeFile) + sizeof(CIndexTreeDataNode), sizeof(CIndexTreeChildNode), MAX_DATA_SIZE, MAX_KEY_SIZE, NULL);
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

	BOOL ValidateIndexTree(BOOL bReadNodes)
	{
		return CIndexTreeFile::ValidateIndexTree(bReadNodes);
	}

	BOOL ValidateIndexTree(void)
	{
		return CIndexTreeFile::ValidateIndexTree();
	}

	BOOL ValidateKey(void* pvKey, int iKeySize)
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

	BOOL GetNodeKey(CIndexTreeNodeFile* pcNode, unsigned char* pvDestKey, int iDestSize)
	{
		return CIndexTreeFile::GetNodeKey(pcNode, pvDestKey, iDestSize);
	}

	CIndexTreeNodeFile* GetRoot(void)
	{
		return CIndexTreeFile::GetRoot();
	}

	void FindKey(CIndexTreeNodeFile* pcNode, CArrayChar* pacKey)
	{
		CIndexTreeFile::FindKey(pcNode, pacKey);
	}

	void FindKey(CIndexTreeNodeFile* pcNode, unsigned char* uiKey, int* piKeySize)
	{
		CIndexTreeFile::FindKey(pcNode, uiKey, piKeySize);
	}

	CListCharsMinimal* FindStringKeys(CArrayVoidPtr* apvNodes)
	{
		return CIndexTreeFile::FindStringKeys(apvNodes);
	}
};


#endif // __TEST_INDEX_TREE_FILE_H__


