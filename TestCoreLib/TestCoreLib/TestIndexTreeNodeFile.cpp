#include "BaseLib/Logger.h"
#include "BaseLib/FileUtil.h"
#include "BaseLib/SystemAllocator.h"
#include "TestLib/Assert.h"
#include "CoreLib/IndexTreeNodeFile.h"
#include "CoreLib/IndexTreeBlockFile.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeNodeFileSizeofs(void)
{
	AssertInt(4, sizeof(CIndexTreeNodeFile*));
	AssertInt(16, sizeof(CFileIndex));  //Sizeof is 16 but only the first 12 bytes are used.
	AssertInt(16, sizeof(SIndexTreeChildFile));  //Sizeof is 16 but only the last 4 bytes are used.
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

	cChild.u.mpvMemory = (CIndexTreeNodeFile*)0x80808080;
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
void TestIndexTreeNodeFileInit(void)
{
	CIndexTreeNodeFile*		pcNode;
	CIndexTreeBlockFile		cIndex;
	CIndexTreeNodeFile		cChildNode;
	CIndexTreeNodeFile*		pcResult;

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
	AssertPointer(&cChildNode, pcResult);

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
	TestIndexTreeNodeFileInit();

	TestStatistics();
}


