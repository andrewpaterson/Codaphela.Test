#include "BaseLib/IntegerHelper.h"
#include "BaseLib/LinkedList.h"
#include "TestLib/Assert.h"


struct SLLNodeInt : public SLLNode
{
	int mi;
};


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
SLLNodeInt* Malloc(int i)
{
	SLLNodeInt*		psNode;

	psNode = (SLLNodeInt*)gcSystemAllocator.Malloc(sizeof(SLLNodeInt));
	psNode->mi = i;
	psNode->psNext = NULL;
	psNode->psPrev = NULL;

	return psNode;
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void Free(SLLNodeInt* psNode)
{
	gcSystemAllocator.Free(psNode);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestLinkedListSwap(void)
{
	SLLNodeInt*		psNode1;
	SLLNodeInt*		psNode2;
	SLLNodeInt*		psNode3;
	SLLNodeInt*		psNode4;
	CLinkedList		cList;
	SLLNode*		psNode;

	psNode1 = Malloc(1);
	psNode2 = Malloc(2);
	psNode3 = Malloc(3);
	psNode4 = Malloc(4);

	cList.Init();
	cList.InsertAfterTail(psNode1);
	cList.InsertAfterTail(psNode2);
	AssertInt(2, cList.NumElements());
	psNode = cList.GetHead();
	AssertPointer(psNode1, psNode);
	psNode = cList.GetNext(psNode);
	AssertPointer(psNode2, psNode);
	psNode = cList.GetNext(psNode);
	AssertNull(psNode);

	cList.Swap(psNode1, psNode2);
	AssertInt(2, cList.NumElements());
	psNode = cList.GetHead();
	AssertPointer(psNode2, psNode);
	psNode = cList.GetNext(psNode);
	AssertPointer(psNode1, psNode);
	psNode = cList.GetNext(psNode);
	AssertNull(psNode);

	cList.InsertAfterNode(psNode1, psNode3);
	cList.Swap(psNode1, psNode2);
	AssertInt(3, cList.NumElements());
	psNode = cList.GetHead();
	AssertPointer(psNode1, psNode);
	psNode = cList.GetNext(psNode);
	AssertPointer(psNode2, psNode);
	psNode = cList.GetNext(psNode);
	AssertPointer(psNode3, psNode);
	psNode = cList.GetNext(psNode);
	AssertNull(psNode);

	cList.Swap(psNode2, psNode3);
	AssertInt(3, cList.NumElements());
	psNode = cList.GetHead();
	AssertPointer(psNode1, psNode);
	psNode = cList.GetNext(psNode);
	AssertPointer(psNode3, psNode);
	psNode = cList.GetNext(psNode);
	AssertPointer(psNode2, psNode);
	psNode = cList.GetNext(psNode);
	AssertNull(psNode);

	cList.Swap(psNode1, psNode2);
	AssertInt(3, cList.NumElements());
	psNode = cList.GetHead();
	AssertPointer(psNode2, psNode);
	psNode = cList.GetNext(psNode);
	AssertPointer(psNode3, psNode);
	psNode = cList.GetNext(psNode);
	AssertPointer(psNode1, psNode);
	psNode = cList.GetNext(psNode);
	AssertNull(psNode);

	cList.InsertAfterNode(psNode2, psNode4);
	cList.Swap(psNode3, psNode4);
	AssertInt(4, cList.NumElements());
	psNode = cList.GetHead();
	AssertPointer(psNode2, psNode);
	psNode = cList.GetNext(psNode);
	AssertPointer(psNode3, psNode);
	psNode = cList.GetNext(psNode);
	AssertPointer(psNode4, psNode);
	psNode = cList.GetNext(psNode);
	AssertPointer(psNode1, psNode);
	psNode = cList.GetNext(psNode);
	AssertNull(psNode);

	cList.Swap(psNode1, psNode4);
	cList.Swap(psNode1, psNode3);
	cList.Swap(psNode1, psNode2);
	AssertInt(4, cList.NumElements());
	psNode = cList.GetHead();
	AssertPointer(psNode1, psNode);
	psNode = cList.GetNext(psNode);
	AssertPointer(psNode2, psNode);
	psNode = cList.GetNext(psNode);
	AssertPointer(psNode3, psNode);
	psNode = cList.GetNext(psNode);
	AssertPointer(psNode4, psNode);
	psNode = cList.GetNext(psNode);
	AssertNull(psNode);

	cList.Swap(psNode4, psNode3);
	cList.Swap(psNode4, psNode2);
	cList.Swap(psNode4, psNode1);
	cList.Swap(psNode3, psNode2);
	cList.Swap(psNode3, psNode1);
	cList.Swap(psNode2, psNode1);
	AssertInt(4, cList.NumElements());
	psNode = cList.GetHead();
	AssertPointer(psNode4, psNode);
	psNode = cList.GetNext(psNode);
	AssertPointer(psNode3, psNode);
	psNode = cList.GetNext(psNode);
	AssertPointer(psNode2, psNode);
	psNode = cList.GetNext(psNode);
	AssertPointer(psNode1, psNode);
	psNode = cList.GetNext(psNode);
	AssertNull(psNode);

	cList.BubbleSort(CompareInt, sizeof(SLLNode));

	AssertInt(4, cList.NumElements());
	psNode = cList.GetHead();
	AssertPointer(psNode1, psNode);
	psNode = cList.GetNext(psNode);
	AssertPointer(psNode2, psNode);
	psNode = cList.GetNext(psNode);
	AssertPointer(psNode3, psNode);
	psNode = cList.GetNext(psNode);
	AssertPointer(psNode4, psNode);
	psNode = cList.GetNext(psNode);
	AssertNull(psNode);

	cList.Kill();

	Free(psNode1);
	Free(psNode2);
	Free(psNode3);
	Free(psNode4);
	Pass();
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestLinkedListIndexOf(void)
{
	SLLNodeInt*		psNode0;
	SLLNodeInt*		psNode1;
	SLLNodeInt*		psNode2;
	SLLNodeInt*		psNode3;
	SLLNodeInt*		psNode4;
	SLLNodeInt*		psNode5;
	SLLNodeInt*		psNode6;
	CLinkedList		cList;

	psNode1 = Malloc(1);
	psNode2 = Malloc(2);
	psNode3 = Malloc(3);
	psNode4 = Malloc(4);
	psNode0 = Malloc(0);
	psNode5 = Malloc(5);
	psNode6 = Malloc(6);

	cList.Init();
	cList.InsertAfterTail(psNode1);
	cList.InsertAfterTail(psNode2);
	cList.InsertAfterTail(psNode3);
	cList.InsertAfterTail(psNode4);

	AssertInt(4, cList.NumElements());
	AssertInt(0, cList.IndexOf(psNode1));
	AssertInt(1, cList.IndexOf(psNode2));
	AssertInt(2, cList.IndexOf(psNode3));
	AssertInt(3, cList.IndexOf(psNode4));
	AssertInt(-1, cList.IndexOf(NULL));

	cList.InsertBeforeHead(psNode0);

	AssertInt(5, cList.NumElements());
	AssertInt(0, cList.IndexOf(psNode0));
	AssertInt(1, cList.IndexOf(psNode1));

	cList.BubbleSort(CompareIntReverse, sizeof(SLLNode));

	AssertInt(5, cList.NumElements());
	AssertInt(0, cList.IndexOf(psNode4));
	AssertInt(1, cList.IndexOf(psNode3));
	AssertInt(2, cList.IndexOf(psNode2));
	AssertInt(3, cList.IndexOf(psNode1));
	AssertInt(4, cList.IndexOf(psNode0));
	AssertInt(-1, cList.IndexOf(NULL));

	//cList.InsertIntoSorted(CompareIntReverse, psNode6, sizeof(SLLNode));

	AssertInt(5, cList.NumElements());
	AssertInt(0, cList.IndexOf(psNode6));
	AssertInt(-1, cList.IndexOf(psNode5));

	cList.Kill();

	Free(psNode0);
	Free(psNode1);
	Free(psNode2);
	Free(psNode3);
	Free(psNode4);
	Free(psNode5);
	Free(psNode6);
}


//////////////////////////////////////////////////////////////////////////
//
//
//////////////////////////////////////////////////////////////////////////
void TestLinkedList(void)
{
	BeginTests();

	//TestLinkedListIndexOf();
	TestLinkedListSwap();

	TestStatistics();
}

