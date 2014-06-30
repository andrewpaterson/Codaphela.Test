#include "BaseLib/IndexTree.h"
#include "TestLib/Assert.h"
#include "TestIndexTreeObject.h"


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeNodeInit(void)
{
	CIndexTreeNode	cNode;
	CIndexTreeNode	cObject;
	long long int	uiObject;
	CIndexTreeNode*	pcObject;

	uiObject = 0xA27384234FFLL;

	cNode.Init(NULL);
	AssertTrue(cNode.IsEmpty());
	AssertFalse(cObject.HasNodes());

	cNode.Contain(33);
	AssertTrue(cNode.IsEmpty());
	AssertTrue(cNode.HasNodes());
	AssertInt(33, cNode.GetFirstIndex());
	AssertInt(33, cNode.GetLastIndex());

	cNode.Set(33, &cObject);
	AssertFalse(cNode.IsEmpty());
	AssertTrue(cNode.HasNodes());

	pcObject = cNode.Get(33);
	AssertPointer(&cObject, pcObject);

	AssertFalse(cNode.ContainsIndex(32));
	AssertTrue(cNode.ContainsIndex(33));
	AssertFalse(cNode.ContainsIndex(34));
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
CIndexTreeNode* TestIndexTreeNodeMalloc(void)
{
	int					iSize;
	CIndexTreeNode*		pcNode;

	iSize = sizeof(CIndexTreeNode) + (MAX_UCHAR-1) * sizeof(CIndexTreeNode*);
	pcNode = (CIndexTreeNode*)malloc(iSize);
	memset(pcNode, 0xfffefdfc, iSize);
	return pcNode;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeNodeFree(CIndexTreeNode* pcNode)
{
	free(pcNode);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeNodeContain(void)
{
	CIndexTreeNode*	pcNode1;
	CIndexTreeNode*	pcNode2;
	CIndexTreeNode*	pcNode3;
	CIndexTreeNode*	pcNode4;
	CIndexTreeNode*	pcNode5;
	CIndexTreeNode*	pcNode6;

	pcNode1 = TestIndexTreeNodeMalloc();
	pcNode2 = TestIndexTreeNodeMalloc();
	pcNode3 = TestIndexTreeNodeMalloc();
	pcNode4 = TestIndexTreeNodeMalloc();
	pcNode5 = TestIndexTreeNodeMalloc();
	pcNode6 = TestIndexTreeNodeMalloc();

	pcNode1->Init(NULL);
	pcNode1->Contain(8);
	AssertInt(8, pcNode1->GetFirstIndex());
	AssertInt(1, pcNode1->GetNumIndexes());
	AssertInt(8, pcNode1->GetLastIndex());
	AssertTrue(pcNode1->ContainsIndex(8));
	AssertNull(pcNode1->Get(8));
	pcNode1->Set(8, pcNode2);
	AssertNotNull(pcNode1->Get(8));

	pcNode1->Contain(9);
	AssertInt(8, pcNode1->GetFirstIndex());
	AssertInt(2, pcNode1->GetNumIndexes());
	AssertInt(9, pcNode1->GetLastIndex());
	AssertNull(pcNode1->Get(9));
	pcNode1->Set(9, pcNode3);
	AssertNotNull(pcNode1->Get(9));
	
	pcNode1->Contain(7);
	AssertInt(7, pcNode1->GetFirstIndex());
	AssertInt(3, pcNode1->GetNumIndexes());
	AssertInt(9, pcNode1->GetLastIndex());
	AssertNull(pcNode1->Get(7));
	pcNode1->Set(7, pcNode4);
	AssertNotNull(pcNode1->Get(7));

	pcNode1->Contain(2);
	AssertInt(2, pcNode1->GetFirstIndex());
	AssertInt(8, pcNode1->GetNumIndexes());
	AssertInt(9, pcNode1->GetLastIndex());
	AssertNull(pcNode1->Get(2));
	AssertNull(pcNode1->Get(3));
	AssertNull(pcNode1->Get(4));
	AssertNull(pcNode1->Get(5));
	AssertNull(pcNode1->Get(6));
	AssertNotNull(pcNode1->Get(7));
	pcNode1->Set(2, pcNode5);
	AssertNotNull(pcNode1->Get(2));
	AssertNull(pcNode1->Get(3));
	AssertNull(pcNode1->Get(4));
	AssertNull(pcNode1->Get(5));
	AssertNull(pcNode1->Get(6));
	AssertNotNull(pcNode1->Get(7));

	pcNode1->Contain(14);
	AssertInt(2, pcNode1->GetFirstIndex());
	AssertInt(13, pcNode1->GetNumIndexes());
	AssertInt(14, pcNode1->GetLastIndex());
	AssertNotNull(pcNode1->Get(9));
	AssertNull(pcNode1->Get(10));
	AssertNull(pcNode1->Get(11));
	AssertNull(pcNode1->Get(12));
	AssertNull(pcNode1->Get(13));
	AssertNull(pcNode1->Get(14));
	pcNode1->Set(14, pcNode6);
	AssertNotNull(pcNode1->Get(9));
	AssertNull(pcNode1->Get(10));
	AssertNull(pcNode1->Get(11));
	AssertNull(pcNode1->Get(12));
	AssertNull(pcNode1->Get(13));
	AssertNotNull(pcNode1->Get(14));

	AssertNull(pcNode1->Get(1));
	pcNode1->Set(1, pcNode5);
	AssertNull(pcNode1->Get(1));
	AssertNull(pcNode1->Get(15));
	pcNode1->Set(15, pcNode5);
	AssertNull(pcNode1->Get(15));

	AssertFalse(pcNode1->ContainsIndex(1));
	AssertTrue(pcNode1->ContainsIndex(2));
	AssertTrue(pcNode1->ContainsIndex(14));
	AssertFalse(pcNode1->ContainsIndex(15));

	AssertPointer(pcNode5, pcNode1->GetNode(0));
	AssertNull(pcNode1->GetNode(1));
	AssertNull(pcNode1->GetNode(2));
	AssertNull(pcNode1->GetNode(3));
	AssertNull(pcNode1->GetNode(4));
	AssertPointer(pcNode4, pcNode1->GetNode(5));
	AssertPointer(pcNode2, pcNode1->GetNode(6));
	AssertPointer(pcNode3, pcNode1->GetNode(7));
	AssertNull(pcNode1->GetNode(8));
	AssertNull(pcNode1->GetNode(9));
	AssertNull(pcNode1->GetNode(10));
	AssertNull(pcNode1->GetNode(11));
	AssertPointer(pcNode6, pcNode1->GetNode(12));

	AssertPointer(pcNode5, pcNode1->Get(2));
	AssertNull(pcNode1->Get(3));
	AssertNull(pcNode1->Get(4));
	AssertNull(pcNode1->Get(5));
	AssertNull(pcNode1->Get(6));
	AssertPointer(pcNode4, pcNode1->Get(7));
	AssertPointer(pcNode2, pcNode1->Get(8));
	AssertPointer(pcNode3, pcNode1->Get(9));
	AssertNull(pcNode1->Get(10));
	AssertNull(pcNode1->Get(11));
	AssertNull(pcNode1->Get(12));
	AssertNull(pcNode1->Get(13));
	AssertPointer(pcNode6, pcNode1->Get(14));

	TestIndexTreeNodeFree(pcNode6);
	TestIndexTreeNodeFree(pcNode5);
	TestIndexTreeNodeFree(pcNode4);
	TestIndexTreeNodeFree(pcNode3);
	TestIndexTreeNodeFree(pcNode2);
	TestIndexTreeNodeFree(pcNode1);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestIndexTreeNode(void)
{
	BeginTests();

	TestIndexTreeNodeInit();
	TestIndexTreeNodeContain();

	TestStatistics();
}

