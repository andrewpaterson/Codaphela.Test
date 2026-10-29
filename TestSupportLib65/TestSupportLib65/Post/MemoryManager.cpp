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
struct SMMNode : public SLLNode
{
uint16 uiSize;
uint8 uiFlags;
};
class CMemoryManager
{
protected:
CLinkedList mcLinkedList;
void* mpvHeapStart;
void* mpvHeapEnd;
SMMNode* mapsEmpty[32];
uint16 muiEmptyCacheSize;
uint16 muiCacheSize;
bool mbCacheFull;
public:
void Init(void* pvHeapStart, void* pvHeapEnd);
void Kill(void);
void* Allocate(uint32 uiSize);
void Deallocate(void* pvData);
void DisableEmptyCache(void);
SMMNode* StartIteration(void);
SMMNode* Iterate(SMMNode* psNode);
uint32 GetNumAllocations(bool bIncludeUnused);
uint32 GetUnusedAllocationSize(void);
uint32 GetUsedAllocationSize(void);
uint32 GetRemaingTailSize(void);
uint32 GetTotalSize(void);
protected:
void* AllocateNodeInUnused(SMMNode* psUnusedNode, uint32 uiUnusedNodeSize, uint32 uiAllocateSize);
void* AllocateNodeAfterEnd(uint32 uiSize);
void DeallocateLastNode(SMMNode* psNode);
void ClearEmptyCache(void);
void EvictUnsedEmptyCache(SMMNode* psAltered);
void InsertEmptyIntoCache(SMMNode* psEmpty);
};
uint32 GetMMNodeDataSize(SMMNode* psNode);
void CMemoryManager::Init(void* pvHeapStart, void* pvHeapEnd)
{
mcLinkedList.Init();
mpvHeapStart = pvHeapStart;
mpvHeapEnd = pvHeapEnd;
muiCacheSize = 32;
ClearEmptyCache();
mbCacheFull = false;
}
void CMemoryManager::Kill(void)
{
ClearEmptyCache();
mcLinkedList.Kill();
mpvHeapStart = 0L;
mpvHeapEnd = 0L;
}
void CMemoryManager::DisableEmptyCache(void)
{
muiCacheSize = 0;
mbCacheFull = true;
}
void CMemoryManager::ClearEmptyCache(void)
{
uint16 ui;
muiEmptyCacheSize = 0;
for (ui = 0; ui < muiCacheSize; ui++)
{
mapsEmpty[ui] = 0L;
}
}
uint32 GetMMNodeDataSize(SMMNode* psNode)
{
uint32 uiSize;
uiSize = psNode->uiSize;
psNode->uiSize |= (uint32)(psNode->uiFlags & 0x7f) << 16;
return uiSize;
}
void SetUsedMMNodeDataSize(SMMNode* psNode, uint32 uiSize)
{
psNode->uiSize = uiSize;
psNode->uiFlags = (uiSize >> 16) | 0x80;
}
void SetUnusedMMNodeDataSize(SMMNode* psNode, uint32 uiSize)
{
psNode->uiSize = uiSize;
psNode->uiFlags = (uiSize >> 16) & (~0x80);
}
SMMNode* GetNodeForData(void* pvData)
{
SMMNode* psNode;
psNode = (SMMNode*)RemapSinglePointer(pvData, -(ptrdiff_t)(sizeof(SMMNode)));
return psNode;
}
void MarkNodeRemoved(SMMNode* psNode)
{
psNode->psNext = 0L;
psNode->psPrev = 0L;
psNode->uiFlags = 0xff;
psNode->uiSize = 0xffff;
}
void* CMemoryManager::Allocate(uint32 uiSize)
{
SMMNode* psNode;
uint32 uiNodeSize;
if (uiSize == 0)
{
return 0L;
}
uiSize += sizeof(SMMNode);
if (uiSize > 0x4f'ff'ff)
{
return 0L;
}
psNode = (SMMNode*)mcLinkedList.GetTail();
while (psNode)
{
if (!(psNode->uiFlags & 0x80))
{
uiNodeSize = GetMMNodeDataSize(psNode);
if (uiNodeSize >= uiSize)
{
return AllocateNodeInUnused(psNode, uiNodeSize, uiSize);
}
}
psNode = (SMMNode*)psNode->psPrev;
}
return AllocateNodeAfterEnd(uiSize);
}
void* CMemoryManager::AllocateNodeInUnused(SMMNode* psUnusedNode, uint32 uiUnusedNodeSize, uint32 uiAllocateSize)
{
uint32 uiCompareSize;
SMMNode* psNewUnusedNode;
void* pvData;
pvData = RemapSinglePointer(psUnusedNode, sizeof(SMMNode));
uiCompareSize = uiUnusedNodeSize - (uint32)sizeof(SMMNode) - 4;
SetUsedMMNodeDataSize(psUnusedNode, uiAllocateSize);
if (uiAllocateSize >= uiCompareSize)
{
return pvData;
}
psNewUnusedNode = (SMMNode*)RemapSinglePointer(psUnusedNode, uiAllocateSize);
mcLinkedList.InsertAfterNode(psUnusedNode, (SLLNode*)psNewUnusedNode);
uiUnusedNodeSize = (uint32)((size)psNewUnusedNode->psNext - (size)psNewUnusedNode);
SetUnusedMMNodeDataSize(psNewUnusedNode, uiUnusedNodeSize);
return pvData;
}
void* CMemoryManager::AllocateNodeAfterEnd(uint32 uiSize)
{
SMMNode* psNode;
uint32 uiNodeSize;
void* pvData;
uint32 uiRemaingSize;
psNode = (SMMNode*)mcLinkedList.GetTail();
if (psNode == 0L)
{
psNode = (SMMNode*)mpvHeapStart;
}
else
{
uiNodeSize = GetMMNodeDataSize(psNode);
psNode = (SMMNode*)RemapSinglePointer(psNode, uiNodeSize);
}
uiRemaingSize = (uint32)((size)mpvHeapEnd - (size)psNode + 1);
if (uiSize <= uiRemaingSize)
{
SetUsedMMNodeDataSize(psNode, uiSize);
mcLinkedList.InsertAfterTail(psNode);
pvData = RemapSinglePointer(psNode, sizeof(SMMNode));
return pvData;
}
else
{
return 0L;
}
}
void CMemoryManager::DeallocateLastNode(SMMNode* psNode)
{
SMMNode* psPrev;
while ((psNode->uiFlags & 0x80) == 0)
{
psPrev = (SMMNode*)psNode->psPrev;
mcLinkedList.Remove(psNode);
MarkNodeRemoved(psNode);
if (psPrev == 0L)
{
return;
}
psNode = psPrev;
}
}
void CMemoryManager::EvictUnsedEmptyCache(SMMNode* psAltered)
{
uint16 ui;
SMMNode* psNext;
bool bLast;
if (muiEmptyCacheSize == 0)
{
return;
}
bLast = true;
psNext = (SMMNode*)psAltered->psNext;
if (psNext)
{
if (muiEmptyCacheSize != 0)
{
ui = muiEmptyCacheSize;
do
{
ui--;
if ((mapsEmpty[ui] >= psAltered) && (mapsEmpty[ui] < psNext))
{
if (bLast)
{
muiEmptyCacheSize--;
}
mapsEmpty[ui] = 0L;
mbCacheFull = false;
}
else
{
bLast = false;
}
}
while (ui != 0);
}
}
else
{
if (muiEmptyCacheSize != 0)
{
ui = muiEmptyCacheSize;
do
{
ui--;
if ((mapsEmpty[ui] >= psAltered))
{
if (bLast)
{
muiEmptyCacheSize--;
}
else
{
bLast = false;
}
mapsEmpty[ui] = 0L;
mbCacheFull = false;
}
}
while (ui != 0);
}
}
}
void CMemoryManager::InsertEmptyIntoCache(SMMNode* psEmpty)
{
uint16 ui;
if (mbCacheFull)
{
return;
}
for (ui = 0; ui < muiEmptyCacheSize; ui++)
{
if (mapsEmpty[ui] == 0L)
{
mapsEmpty[ui] = psEmpty;
return;
}
}
for (; ui < muiCacheSize; ui++)
{
if (mapsEmpty[ui] == 0L)
{
muiEmptyCacheSize++;
mapsEmpty[ui] = psEmpty;
return;
}
}
mbCacheFull = true;
}
void CMemoryManager::Deallocate(void* pvData)
{
SMMNode* psNode;
SMMNode* psNext;
SMMNode* psCurrent;
uint32 uiUnusedNodeSize;
if (pvData == 0L)
{
return;
}
psNode = GetNodeForData(pvData);
psNode->uiFlags &= (~0x80);
psNext = (SMMNode*)psNode->psNext;
if (psNext == 0L)
{
DeallocateLastNode(psNode);
return;
}
psCurrent = 0L;
while (psNode && ((psNode->uiFlags & 0x80) == 0))
{
psCurrent = psNode;
psNode = (SMMNode*)psNode->psPrev;
}
psNode = psCurrent;
psNext = (SMMNode*)psNode->psNext;
if ((psNext->uiFlags & 0x80) == 0)
{
while ((psNext->uiFlags & 0x80) == 0)
{
psNode = psNext;
psNext = (SMMNode*)psNode->psNext;
mcLinkedList.Remove(psNode);
MarkNodeRemoved(psNode);
}
}
uiUnusedNodeSize = (uint32)((size)psCurrent->psNext - (size)psCurrent);
SetUnusedMMNodeDataSize(psCurrent, uiUnusedNodeSize);
EvictUnsedEmptyCache(psCurrent);
InsertEmptyIntoCache(psCurrent);
}
SMMNode* CMemoryManager::StartIteration(void)
{
return (SMMNode*)mcLinkedList.GetHead();
}
SMMNode* CMemoryManager::Iterate(SMMNode* psNode)
{
return (SMMNode*)psNode->psNext;
}
uint32 CMemoryManager::GetNumAllocations(bool bIncludeUnused)
{
SMMNode* psNode;
uint32 uiCount;
uiCount = 0;
psNode = (SMMNode*)mcLinkedList.GetHead();
while (psNode)
{
if (bIncludeUnused || psNode->uiFlags & 0x80)
{
uiCount++;
}
psNode = (SMMNode*)psNode->psNext;
}
return uiCount;
}
uint32 CMemoryManager::GetUnusedAllocationSize(void)
{
SMMNode* psNode;
uint32 uiSize;
uiSize = 0;
psNode = (SMMNode*)mcLinkedList.GetHead();
while (psNode)
{
if (!(psNode->uiFlags & 0x80))
{
uiSize += GetMMNodeDataSize(psNode);
}
psNode = (SMMNode*)psNode->psNext;
}
return uiSize;
}
uint32 CMemoryManager::GetUsedAllocationSize(void)
{
SMMNode* psNode;
uint32 uiSize;
uiSize = 0;
psNode = (SMMNode*)mcLinkedList.GetHead();
while (psNode)
{
if (psNode->uiFlags & 0x80)
{
uiSize += GetMMNodeDataSize(psNode);
}
psNode = (SMMNode*)psNode->psNext;
}
return uiSize;
}
uint32 CMemoryManager::GetRemaingTailSize(void)
{
SMMNode* psNode;
psNode = (SMMNode*)mcLinkedList.GetTail();
if (psNode)
{
return (uint32)((size)mpvHeapEnd - (size)psNode - GetMMNodeDataSize(psNode) + 1);
}
else
{
return (uint32)((size)mpvHeapEnd - (size)mpvHeapStart + 1);
}
}
uint32 CMemoryManager::GetTotalSize(void)
{
return (uint32)((size)mpvHeapEnd - (size)mpvHeapStart + 1);
}
