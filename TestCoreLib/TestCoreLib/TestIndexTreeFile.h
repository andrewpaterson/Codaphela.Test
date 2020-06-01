#ifndef __TEST_INDEX_TREE_FILE_H__
#define __TEST_INDEX_TREE_FILE_H__
#include "CoreLib/IndexTreeFile.h"


class CTestIndexTreeFile : public CIndexTreeFile
{
public:
	void FakeInit(EIndexKeyReverse eKeyReverse)
	{
		CIndexTreeFile::FakeInit(eKeyReverse);
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
};


#endif // __TEST_INDEX_TREE_FILE_H__


