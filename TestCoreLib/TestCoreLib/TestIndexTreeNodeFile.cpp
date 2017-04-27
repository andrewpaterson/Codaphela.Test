#include "BaseLib/Logger.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/SystemAllocator.h"
#include "TestLib/Assert.h"
#include "CoreLib/IndexTreeNodeFile.h"
#include "CoreLib/IndexTreeFile.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeNodeFileSizeofs(void)
{
	AssertInt(4, sizeof(CIndexTreeNodeFile*));
	AssertInt(16, sizeof(CFileIndex));  //SizeOf is 16 but only the first 12 bytes are used.
	AssertInt(16, sizeof(SIndexTreeChildFile));  //SizeOf is 16 but only the last 4 bytes are used.
	AssertInt(16, sizeof(CIndexTreeChildNode));  //The above is why the union works 

	AssertTrue(sizeof(CIndexTreeNodeFile*) <= 12);  //The size of a memory pointer may not be more than 12 bytes.
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeNodeFileUnion(void)
{
	CIndexTreeChildNode		cChild;

	memset(&cChild, 0, sizeof(CIndexTreeChildNode));
	cChild.u.mcFile.Init();
	AssertInt(0, cChild.u.msType.iType);

	cChild.u.mpcMemory = (CIndexTreeNodeFile*)0x80808080;
	AssertInt(0, cChild.u.msType.iType);
	AssertFalse(cChild.IsValid());

	memset(&cChild, 1, sizeof(CIndexTreeChildNode));
	AssertTrue(cChild.IsValid());
	AssertTrue(cChild.IsMemory());
	AssertFalse(cChild.IsFile());

	memset(&cChild, 2, sizeof(CIndexTreeChildNode));
	AssertTrue(cChild.IsValid());
	AssertFalse(cChild.IsMemory());
	AssertTrue(cChild.IsFile());
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeNodeFileRootMemory(void)
{
	CIndexTreeNodeFile*		pcNode;
	CIndexTreeFile		cIndex;
	CIndexTreeNodeFile		cChildNode;
	CIndexTreeChildNode*	pcResult;

	cIndex.FakeInit();

	pcNode = (CIndexTreeNodeFile*)malloc(sizeof(CIndexTreeNodeFile) + sizeof(CIndexTreeChildNode));  //Node.  No object.  One child.
	pcNode->Init(&cIndex, NULL);

	AssertTrue(pcNode->IsEmpty());
	AssertFalse(pcNode->HasNodes());
	AssertFalse(pcNode->HasObject());
	AssertTrue(pcNode->ValidateNodesEmpty());

	pcNode->Contain(33);
	AssertFalse(pcNode->IsEmpty());
	AssertTrue(pcNode->HasNodes());
	AssertFalse(pcNode->HasObject());

	gcLogger.SetBreakOnError(FALSE);
	AssertFalse(pcNode->ValidateNodesEmpty());
	gcLogger.SetBreakOnError(TRUE);

	AssertInt(33, pcNode->GetFirstIndex());
	AssertInt(33, pcNode->GetLastIndex());

	pcNode->Set(33, &cChildNode);
	AssertFalse(pcNode->IsEmpty());
	AssertTrue(pcNode->HasNodes());
	AssertFalse(pcNode->HasObject());
	AssertInt(1, pcNode->NumInitialisedIndexes());
	AssertTrue(pcNode->ValidateNodesEmpty());

	pcResult = pcNode->Get(33);
	AssertTrue(pcResult->IsMemory());
	AssertPointer(&cChildNode, pcResult->u.mpcMemory);

	AssertFalse(pcNode->ContainsIndex(32));
	AssertTrue(pcNode->ContainsIndex(33));
	AssertFalse(pcNode->ContainsIndex(34));

	free(pcNode);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeNodeFile(void)
{
	BeginTests();

	TestIndexTreeNodeFileSizeofs();
	TestIndexTreeNodeFileUnion();
	TestIndexTreeNodeFileRootMemory();

	TestStatistics();
}

