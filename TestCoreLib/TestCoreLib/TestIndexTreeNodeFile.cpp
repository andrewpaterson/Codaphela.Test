#include "BaseLib/Logger.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/SystemAllocator.h"
#include "BaseLib/TypeConverter.h"
#include "TestLib/Assert.h"
#include "CoreLib/IndexTreeNodeFile.h"
#include "CoreLib/IndexTreeFile.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeNodeFileSizeofs(void)
{
	AssertInt(4, sizeof(CIndexTreeNodeFile*));  //The size of a memory pointer must be (at least) 4 bytes less than CIndexTreeChildNode.
	AssertInt(8, sizeof(CFileDataIndex));  //SizeOf is 16 but only the first 12 bytes are used.

	AssertInt(12, sizeof(CIndexTreeChildNode));  //The above is why the union works 

	AssertInt(24, sizeof(CIndexTreeNodeFile)));  
	AssertInt(16, sizeof(CIndexTreeNode)));
	AssertTrue(sizeof(CIndexTreeNodeFile*) <= sizeof(CIndexTreeChildNode) - sizeof(int)));
	AssertInt(4, sizeof(int));  //Just ot be sure.
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
	AssertInt(0, cChild.iType);

	cChild.u.mpcMemory = (CIndexTreeNodeFile*)0x80808080;
	AssertInt(0, cChild.iType);
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
	CIndexTreeFile			cIndex;
	CIndexTreeNodeFile		cChildNode;
	CIndexTreeChildNode*	pcResult;

	cIndex.FakeInit();

	pcNode = (CIndexTreeNodeFile*)malloc(sizeof(CIndexTreeNodeFile) + sizeof(CIndexTreeChildNode));  //Node.  No object.  One child.
	pcNode->Init(&cIndex, NULL, 0);

	AssertTrue(pcNode->IsEmpty());
	AssertFalse(pcNode->HasNodes());
	AssertFalse(pcNode->HasData());
	AssertTrue(pcNode->ValidateNodesEmpty());

	pcNode->Contain(33, INDEX_TREE_FILE_NODE_UNALLOCATED);
	AssertFalse(pcNode->IsEmpty());
	AssertTrue(pcNode->HasNodes());
	AssertFalse(pcNode->HasData());

	gcLogger.SetBreakOnError(FALSE);
	AssertFalse(pcNode->ValidateNodesEmpty());
	gcLogger.SetBreakOnError(TRUE);

	AssertInt(33, pcNode->GetFirstIndex());
	AssertInt(33, pcNode->GetLastIndex());

	pcNode->SetMemory(33, &cChildNode);
	AssertFalse(pcNode->IsEmpty());
	AssertTrue(pcNode->HasNodes());
	AssertFalse(pcNode->HasData());
	AssertInt(1, pcNode->NumValidIndexes());
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
	FastFunctionsInit();
	TypeConverterInit();
	BeginTests();

	TestIndexTreeNodeFileSizeofs();
	TestIndexTreeNodeFileUnion();
	TestIndexTreeNodeFileRootMemory();

	TestStatistics();
	FastFunctionsKill();
	TypeConverterKill();
}

