typedef unsigned long size_t;
typedef long ptrdiff_t;
typedef long long max_align_t;
typedef signed char int8_t;
typedef short int16_t;
typedef long int32_t;
typedef long long int64_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long uint32_t;
typedef unsigned long long uint64_t;
typedef signed char int_least8_t;
typedef short int_least16_t;
typedef long int_least32_t;
typedef long long int_least64_t;
typedef unsigned char uint_least8_t;
typedef unsigned short uint_least16_t;
typedef unsigned long uint_least32_t;
typedef unsigned long long uint_least64_t;
typedef int int_fast8_t;
typedef int int_fast16_t;
typedef long int_fast32_t;
typedef long long int_fast64_t;
typedef unsigned int uint_fast8_t;
typedef unsigned int uint_fast16_t;
typedef unsigned long uint_fast32_t;
typedef unsigned long long uint_fast64_t;
typedef long intptr_t;
typedef unsigned long uintptr_t;
typedef long long intmax_t;
typedef unsigned long long uintmax_t;
typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef uint8_t uint8;
typedef uint32_t uint32;
typedef uint16_t uint16;
typedef int64_t int64 ;
typedef uint64_t uint64 ;
typedef int64 int128 ;
typedef uint64 uint128 ;
typedef char char8;
typedef wchar_t char16;
typedef float float32;
typedef double float64 ;
typedef long double float128;
typedef unsigned int uint;
typedef size_t size;
typedef uintptr_t ptr;
typedef ptrdiff_t ptrdiff;
typedef size lsize;
typedef int64 longint;
typedef uint64 ulongint;
void* RemapSinglePointer(const void* pvPtr, ptrdiff iOffest);
__inline void* RemapSinglePointer(const void* pvPtr, ptrdiff iOffest)
{
return &((char*)pvPtr)[iOffest];
}
typedef int (*DataCompare)(const void* pvLeft, const void* pvRight);
struct SLLNode
{
SLLNode* psNext;
SLLNode* psPrev;
};
class CLinkedList
{
protected:
SLLNode* mpsHead;
SLLNode* mpsTail;
public:
void Init(void);
void Kill(void);
void InsertAfterTail(SLLNode* psNewNode);
void InsertBeforeHead(SLLNode* psNewNode);
void InsertBeforeNode(SLLNode* psExistingNode, SLLNode* psNewNode);
void InsertAfterNode(SLLNode* psExistingNode, SLLNode* psNewNode);
SLLNode* GetHead(void);
SLLNode* GetTail(void);
SLLNode* GetNext(SLLNode* psExistingNode);
SLLNode* GetPrev(SLLNode* psExistingNode);
void RemoveHead(void);
void RemoveTail(void);
void Remove(SLLNode* psNode);
bool SafeRemove(SLLNode* psNode);
void MoveToHead(SLLNode* psNode);
void MoveToTTail(SLLNode* psNode);
void RemapNode(SLLNode* psOldNode, SLLNode* psNewNode);
size NumElements(void);
SLLNode* Get(size iNum);
size IndexOf(SLLNode* psExistingNode);
bool IsInList(SLLNode* pcNode);
void BubbleSort(DataCompare fCompare, size iOffset);
void Swap(SLLNode* psNode1, SLLNode* psNode2);
void InsertIntoSorted(DataCompare fCompare, SLLNode* psNode, size iOffset);
};
void CLinkedList::Init(void)
{
mpsHead = 0L;
mpsTail = 0L;
}
void CLinkedList::Kill(void)
{
mpsHead = 0L;
mpsTail = 0L;
}
void CLinkedList::InsertAfterTail(SLLNode* psNode)
{
if (psNode)
{
psNode->psNext = 0L;
psNode->psPrev = mpsTail;
if (mpsHead == 0L)
{
mpsHead = psNode;
}
else
{
mpsTail->psNext = psNode;
}
mpsTail = psNode;
}
}
void CLinkedList::InsertBeforeHead(SLLNode* psNode)
{
if (psNode)
{
psNode->psNext = mpsHead;
psNode->psPrev = 0L;
if (mpsTail == 0L)
{
mpsTail = psNode;
}
else
{
mpsHead->psPrev = psNode;
}
mpsHead = psNode;
}
}
void CLinkedList::InsertBeforeNode(SLLNode* psExistingNode, SLLNode* psNewNode)
{
SLLNode* psPos;
SLLNode* psNode;
if ((psExistingNode == 0L) || (psNewNode == 0L))
{
return;
}
psNode = psNewNode;
psPos = psExistingNode;
psNode->psPrev = psPos->psPrev;
psNode->psNext = psPos;
if (psPos->psPrev)
{
psPos->psPrev->psNext = psNode;
}
else
{
mpsHead = psNode;
}
psPos->psPrev = psNode;
}
void CLinkedList::InsertAfterNode(SLLNode* psExistingNode, SLLNode* psNewNode)
{
SLLNode* psPos;
SLLNode* psNode;
if ((psExistingNode == 0L) || (psNewNode == 0L))
{
return;
}
psNode = psNewNode;
psPos = psExistingNode;
psNode->psPrev = psPos;
psNode->psNext = psPos->psNext;
if (psPos->psNext)
{
psPos->psNext->psPrev = psNode;
}
else
{
mpsTail = psNode;
}
psPos->psNext = psNode;
}
SLLNode* CLinkedList::GetHead(void)
{
return mpsHead;
}
SLLNode* CLinkedList::GetTail(void)
{
return mpsTail;
}
SLLNode* CLinkedList::GetNext(SLLNode* psExistingNode)
{
return psExistingNode->psNext;
}
SLLNode* CLinkedList::GetPrev(SLLNode* psExistingNode)
{
return psExistingNode->psPrev;
}
void CLinkedList::RemoveHead(void)
{
Remove(mpsHead);
}
void CLinkedList::RemoveTail(void)
{
Remove(mpsTail);
}
void CLinkedList::Remove(SLLNode* psNode)
{
if (psNode)
{
if (psNode->psPrev)
{
psNode->psPrev->psNext = psNode->psNext;
}
else
{
mpsHead = psNode->psNext;
}
if (psNode->psNext)
{
psNode->psNext->psPrev = psNode->psPrev;
}
else
{
mpsTail = psNode->psPrev;
}
}
}
bool CLinkedList::SafeRemove(SLLNode* psNode)
{
if (IsInList(psNode))
{
Remove(psNode);
return true;
}
return false;
}
void CLinkedList::MoveToHead(SLLNode* psNode)
{
Remove(psNode);
InsertBeforeHead(psNode);
}
void CLinkedList::MoveToTTail(SLLNode* psNode)
{
Remove(psNode);
InsertAfterTail(psNode);
}
void CLinkedList::RemapNode(SLLNode* psOldNode, SLLNode* psNewNode)
{
if (psNewNode->psNext)
{
psNewNode->psNext->psPrev = psNewNode;
}
else if (mpsTail == psOldNode)
{
mpsTail = psNewNode;
}
if (psNewNode->psPrev)
{
psNewNode->psPrev->psNext = psNewNode;
}
else if (mpsHead == psOldNode)
{
mpsHead = psNewNode;
}
}
size CLinkedList::NumElements(void)
{
size iCount;
SLLNode* psNode;
iCount = 0;
psNode = GetHead();
while (psNode)
{
iCount++;
psNode = GetNext(psNode);
}
return iCount;
}
SLLNode* CLinkedList::Get(size iNum)
{
size iCount;
SLLNode* psData;
psData = GetHead();
for (iCount = 0;; iCount++)
{
if (psData)
{
if (iCount == iNum)
{
return psData;
}
psData = GetNext(psData);
}
else
{
return 0L;
}
}
}
size CLinkedList::IndexOf(SLLNode* psNode)
{
size iIndex;
SLLNode* psCurrent;
iIndex = 0;
psCurrent = GetHead();
while (psCurrent)
{
if (psCurrent == psNode)
{
return iIndex;
}
iIndex++;
psCurrent = GetNext(psCurrent);
}
return -1;
}
bool CLinkedList::IsInList(SLLNode* psNode)
{
size iIndex;
iIndex = IndexOf(psNode);
return iIndex != ((size)-1);
}
void CLinkedList::BubbleSort(DataCompare fCompare, size iOffset)
{
SLLNode* psCurrent;
SLLNode* psNext;
int iResult;
bool bSwapped;
void* pvCurrent;
void* pvNext;
psCurrent = GetHead();
if (!psCurrent)
{
return;
}
bSwapped = true;
while (bSwapped)
{
psCurrent = GetHead();
psNext = GetNext(psCurrent);
bSwapped = false;
while ((psNext) && (psCurrent))
{
pvCurrent = RemapSinglePointer(psCurrent, iOffset);
pvNext = RemapSinglePointer(psNext, iOffset);
iResult = fCompare(pvCurrent, pvNext);
if (iResult > 0)
{
Swap(psCurrent, psNext);
bSwapped = true;
}
else
{
psCurrent = GetNext(psCurrent);
}
if (psCurrent)
{
psNext = GetNext(psCurrent);
}
}
}
}
void CLinkedList::Swap(SLLNode* psNode1, SLLNode* psNode2)
{
SLLNode sNodeTemp1;
SLLNode sNodeTemp2;
if ((psNode1 == 0L) || (psNode2 == 0L) || (psNode1 == psNode2))
{
return;
}
sNodeTemp1.psNext = psNode1->psNext;
sNodeTemp1.psPrev = psNode1->psPrev;
sNodeTemp2.psNext = psNode2->psNext;
sNodeTemp2.psPrev = psNode2->psPrev;
if ((psNode1->psNext != psNode2) && (psNode1->psPrev != psNode2))
{
if (sNodeTemp1.psPrev) { sNodeTemp1.psPrev->psNext = psNode2; } else { mpsHead = psNode2; }
if (sNodeTemp1.psNext) { sNodeTemp1.psNext->psPrev = psNode2; } else { mpsTail = psNode2; }
if (sNodeTemp2.psPrev) { sNodeTemp2.psPrev->psNext = psNode1; } else { mpsHead = psNode1; }
if (sNodeTemp2.psNext) { sNodeTemp2.psNext->psPrev = psNode1; } else { mpsTail = psNode1; }
psNode1->psNext = sNodeTemp2.psNext;
psNode1->psPrev = sNodeTemp2.psPrev;
psNode2->psNext = sNodeTemp1.psNext;
psNode2->psPrev = sNodeTemp1.psPrev;
}
else if (psNode1->psNext==psNode2)
{
if (sNodeTemp1.psPrev) { sNodeTemp1.psPrev->psNext=psNode2; } else { mpsHead=psNode2; }
if (sNodeTemp2.psNext) { sNodeTemp2.psNext->psPrev=psNode1; } else { mpsTail=psNode1; }
psNode1->psNext = sNodeTemp2.psNext;
psNode1->psPrev = psNode2;
psNode2->psNext = psNode1;
psNode2->psPrev = sNodeTemp1.psPrev;
}
else if (psNode1->psPrev==psNode2)
{
if (sNodeTemp1.psNext) { sNodeTemp1.psNext->psPrev=psNode2; } else { mpsTail=psNode2; }
if (sNodeTemp2.psPrev) { sNodeTemp2.psPrev->psNext=psNode1; } else { mpsHead=psNode1; }
psNode1->psNext = psNode2;
psNode1->psPrev = sNodeTemp2.psPrev;
psNode2->psNext = sNodeTemp1.psNext;
psNode2->psPrev = psNode1;
}
}
void CLinkedList::InsertIntoSorted(DataCompare fCompare, SLLNode* psNode, size iOffset)
{
SLLNode* psCurrent;
int iResult;
void* pvCurrent;
void* pvNext;
psCurrent = GetHead();
for (;;)
{
pvCurrent = RemapSinglePointer(psCurrent, iOffset);
pvNext = RemapSinglePointer(psNode, iOffset);
iResult = fCompare(pvNext, pvCurrent);
if (iResult < 0)
{
InsertBeforeNode(psCurrent, psNode);
break;
}
psCurrent = GetNext(psCurrent);
if (psCurrent == 0L)
{
InsertAfterTail(psNode);
break;
}
}
}
