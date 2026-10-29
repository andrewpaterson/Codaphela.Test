typedef unsigned long size_t;
typedef long ptrdiff_t;
typedef long long max_align_t;
extern "C"
{
void* memcpy(void* pvDest, const void* pvSource, size_t uiBytes);
void* memmove(void* pvDest, const void* pvSource, size_t uiBytes);
void* memset(void* pvDest, int iValue, size_t uiBytes);
int memcmp(const void* pv1, const void* pv2, size_t uiBytes);
void* memchr(const void* pv, int iValue, size_t uiBytes);
size_t strlen(const char* sz);
char* strcpy(char* szDest, const char* szSource);
char* strncpy(char* szDest, const char* szSource, size_t uiChars);
char* strcat(char* szDest, const char* szSource);
char* strncat(char* szDest, const char* szSource, size_t uiChars);
int strcmp(const char* sz1, const char* sz2);
int strncmp(const char* sz1, const char* sz2, size_t uiChars);
char* strchr(const char* sz, int c);
char* strrchr(const char* sz, int c);
char* strstr(const char* sz, const char* szFind);
}
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
struct STrueMallocatorBlock
{
size uiPreviousSize;
size uiSize;
STrueMallocatorBlock* psNextFree;
STrueMallocatorBlock* psPreviousFree;
};
class CTrueMallocator
{
protected:
uint8* mpuiStart;
STrueMallocatorBlock* mpsEnd;
uint32 muiFirstBitmap;
uint32 mauiSecondBitmaps[(32 - (4 + 3) + 1)];
STrueMallocatorBlock* mapsFree[(32 - (4 + 3) + 1)][(1 << 4)];
size muiNumAllocations;
size muiAllocatedBytes;
public:
bool Init(void* pvMemory, size uiBytes);
void Kill(void);
void* Malloc(lsize uiBytes);
void* Realloc(void* pv, lsize uiBytes);
void Free(void* pv);
size Size(void* pv);
size NumAllocations(void);
size AllocatedBytes(void);
size LargestFree(void);
bool Contains(void* pv);
bool IsValid(void);
protected:
size BlockSize(size uiBytes);
void Mapping(size uiSize, int* piFirst, int* piSecond);
STrueMallocatorBlock* FindFree(size uiSize);
void InsertFree(STrueMallocatorBlock* psBlock);
void RemoveFree(STrueMallocatorBlock* psBlock);
STrueMallocatorBlock* Next(STrueMallocatorBlock* psBlock);
void MarkFree(STrueMallocatorBlock* psBlock, size uiSize);
void Split(STrueMallocatorBlock* psBlock, size uiSize);
};
static int TrueMallocatorHighestBit(uint32 ui)
{
return 31 - __builtin_clz(ui);
}
static int TrueMallocatorLowestBit(uint32 ui)
{
return __builtin_ctz(ui);
}
bool CTrueMallocator::Init(void* pvMemory, size uiBytes)
{
size uiStart;
size uiEnd;
size uiSize;
STrueMallocatorBlock* psBlock;
int i;
int j;
muiFirstBitmap = 0;
for (i = 0; i < (32 - (4 + 3) + 1); i++)
{
mauiSecondBitmaps[i] = 0;
for (j = 0; j < (1 << 4); j++)
{
mapsFree[i][j] = 0L;
}
}
muiNumAllocations = 0;
muiAllocatedBytes = 0;
mpuiStart = 0L;
mpsEnd = 0L;
uiStart = ((size)pvMemory + ((size)1 << 3) - 1) & ~(((size)1 << 3) - 1);
uiEnd = ((size)pvMemory + uiBytes) & ~(((size)1 << 3) - 1);
if ((uiEnd <= uiStart) || (uiEnd - uiStart < (sizeof(STrueMallocatorBlock)) + (2 * sizeof(size))))
{
return false;
}
if (uiEnd - uiStart > ((size)0x40000000) + (2 * sizeof(size)))
{
uiEnd = uiStart + ((size)0x40000000) + (2 * sizeof(size));
}
mpuiStart = (uint8*)uiStart;
mpsEnd = (STrueMallocatorBlock*)(uiEnd - (2 * sizeof(size)));
mpsEnd->uiPreviousSize = 0;
mpsEnd->uiSize = 0;
uiSize = (size)((uint8*)mpsEnd - mpuiStart);
psBlock = (STrueMallocatorBlock*)mpuiStart;
psBlock->uiPreviousSize = 0;
psBlock->uiSize = 0;
MarkFree(psBlock, uiSize);
InsertFree(psBlock);
return true;
}
void CTrueMallocator::Kill(void)
{
mpuiStart = 0L;
mpsEnd = 0L;
muiFirstBitmap = 0;
muiNumAllocations = 0;
muiAllocatedBytes = 0;
}
void* CTrueMallocator::Malloc(lsize uiBytes)
{
STrueMallocatorBlock* psBlock;
size uiSize;
uiSize = BlockSize(uiBytes);
if (uiSize == 0)
{
return 0L;
}
psBlock = FindFree(uiSize);
if (!psBlock)
{
return 0L;
}
RemoveFree(psBlock);
psBlock->uiSize &= ~(size)1;
Next(psBlock)->uiSize &= ~(size)2;
Split(psBlock, uiSize);
muiNumAllocations++;
muiAllocatedBytes += psBlock->uiSize & ~(size)3;
return (uint8*)psBlock + (2 * sizeof(size));
}
void* CTrueMallocator::Realloc(void* pv, lsize uiBytes)
{
STrueMallocatorBlock* psBlock;
STrueMallocatorBlock* psNext;
size uiSize;
size uiCurrent;
void* pvNew;
if (!pv)
{
return Malloc(uiBytes);
}
uiSize = BlockSize(uiBytes);
if (uiSize == 0)
{
return 0L;
}
psBlock = (STrueMallocatorBlock*)((uint8*)pv - (2 * sizeof(size)));
uiCurrent = psBlock->uiSize & ~(size)3;
if (uiSize <= uiCurrent)
{
Split(psBlock, uiSize);
muiAllocatedBytes -= uiCurrent - (psBlock->uiSize & ~(size)3);
return pv;
}
psNext = Next(psBlock);
if ((psNext->uiSize & 1) && (uiCurrent + (psNext->uiSize & ~(size)3) >= uiSize))
{
RemoveFree(psNext);
psBlock->uiSize += psNext->uiSize & ~(size)3;
Next(psBlock)->uiSize &= ~(size)2;
Split(psBlock, uiSize);
muiAllocatedBytes += (psBlock->uiSize & ~(size)3) - uiCurrent;
return pv;
}
pvNew = Malloc(uiBytes);
if (!pvNew)
{
return 0L;
}
memcpy(pvNew, pv, uiCurrent - (2 * sizeof(size)));
Free(pv);
return pvNew;
}
void CTrueMallocator::Free(void* pv)
{
STrueMallocatorBlock* psBlock;
STrueMallocatorBlock* psNext;
STrueMallocatorBlock* psPrevious;
size uiSize;
if (!pv)
{
return;
}
psBlock = (STrueMallocatorBlock*)((uint8*)pv - (2 * sizeof(size)));
uiSize = psBlock->uiSize & ~(size)3;
muiNumAllocations--;
muiAllocatedBytes -= uiSize;
psNext = Next(psBlock);
if (psNext->uiSize & 1)
{
RemoveFree(psNext);
uiSize += psNext->uiSize & ~(size)3;
}
if (psBlock->uiSize & 2)
{
psPrevious = (STrueMallocatorBlock*)((uint8*)psBlock - psBlock->uiPreviousSize);
RemoveFree(psPrevious);
uiSize += psPrevious->uiSize & ~(size)3;
psBlock = psPrevious;
}
MarkFree(psBlock, uiSize);
InsertFree(psBlock);
}
size CTrueMallocator::Size(void* pv)
{
STrueMallocatorBlock* psBlock;
psBlock = (STrueMallocatorBlock*)((uint8*)pv - (2 * sizeof(size)));
return (psBlock->uiSize & ~(size)3) - (2 * sizeof(size));
}
size CTrueMallocator::NumAllocations(void)
{
return muiNumAllocations;
}
size CTrueMallocator::AllocatedBytes(void)
{
return muiAllocatedBytes;
}
size CTrueMallocator::LargestFree(void)
{
STrueMallocatorBlock* psBlock;
size uiLargest;
size uiSize;
int iFirst;
int iSecond;
if (muiFirstBitmap == 0)
{
return 0;
}
iFirst = TrueMallocatorHighestBit(muiFirstBitmap);
iSecond = TrueMallocatorHighestBit(mauiSecondBitmaps[iFirst]);
uiLargest = 0;
for (psBlock = mapsFree[iFirst][iSecond]; psBlock; psBlock = psBlock->psNextFree)
{
uiSize = psBlock->uiSize & ~(size)3;
uiLargest = (uiSize > uiLargest) ? uiSize : uiLargest;
}
return uiLargest - (2 * sizeof(size));
}
bool CTrueMallocator::Contains(void* pv)
{
return ((uint8*)pv >= mpuiStart) && ((uint8*)pv < (uint8*)mpsEnd);
}
bool CTrueMallocator::IsValid(void)
{
STrueMallocatorBlock* psBlock;
STrueMallocatorBlock* psNext;
STrueMallocatorBlock* psListed;
size uiSize;
size uiNumUsed;
size uiUsedBytes;
size uiNumFree;
size uiNumListed;
bool bPreviousFree;
int iFirst;
int iSecond;
int i;
int j;
if (!mpsEnd)
{
return false;
}
uiNumUsed = 0;
uiUsedBytes = 0;
uiNumFree = 0;
bPreviousFree = false;
for (psBlock = (STrueMallocatorBlock*)mpuiStart; psBlock != mpsEnd; psBlock = psNext)
{
uiSize = psBlock->uiSize & ~(size)3;
if ((uiSize < (sizeof(STrueMallocatorBlock))) || (uiSize & (((size)1 << 3) - 1)) || (uiSize > (size)((uint8*)mpsEnd - (uint8*)psBlock)))
{
return false;
}
if (((psBlock->uiSize & 2) != 0) != bPreviousFree)
{
return false;
}
psNext = Next(psBlock);
if (psBlock->uiSize & 1)
{
if (bPreviousFree || (psNext->uiPreviousSize != uiSize))
{
return false;
}
Mapping(uiSize, &iFirst, &iSecond);
for (psListed = mapsFree[iFirst][iSecond]; psListed && (psListed != psBlock); psListed = psListed->psNextFree)
{
}
if (!psListed)
{
return false;
}
uiNumFree++;
bPreviousFree = true;
}
else
{
uiNumUsed++;
uiUsedBytes += uiSize;
bPreviousFree = false;
}
}
if ((((mpsEnd->uiSize & 2) != 0) != bPreviousFree) || (mpsEnd->uiSize & ~(size)2))
{
return false;
}
if ((uiNumUsed != muiNumAllocations) || (uiUsedBytes != muiAllocatedBytes))
{
return false;
}
uiNumListed = 0;
for (i = 0; i < (32 - (4 + 3) + 1); i++)
{
if (((muiFirstBitmap >> i) & 1) != (uint32)(mauiSecondBitmaps[i] != 0))
{
return false;
}
for (j = 0; j < (1 << 4); j++)
{
if (((mauiSecondBitmaps[i] >> j) & 1) != (uint32)(mapsFree[i][j] != 0L))
{
return false;
}
for (psBlock = mapsFree[i][j]; psBlock; psBlock = psBlock->psNextFree)
{
if (!(psBlock->uiSize & 1) || (psBlock->psNextFree && (psBlock->psNextFree->psPreviousFree != psBlock)))
{
return false;
}
uiNumListed++;
}
}
}
return uiNumListed == uiNumFree;
}
size CTrueMallocator::BlockSize(size uiBytes)
{
size uiSize;
if (uiBytes > ((size)0x40000000) - (2 * sizeof(size)) - ((size)1 << 3))
{
return 0;
}
uiSize = (uiBytes + (2 * sizeof(size)) + ((size)1 << 3) - 1) & ~(((size)1 << 3) - 1);
return (uiSize < (sizeof(STrueMallocatorBlock))) ? (sizeof(STrueMallocatorBlock)) : uiSize;
}
void CTrueMallocator::Mapping(size uiSize, int* piFirst, int* piSecond)
{
int iHighest;
if (uiSize < ((size)1 << (4 + 3)))
{
*piFirst = 0;
*piSecond = (int)(uiSize >> 3);
}
else
{
iHighest = TrueMallocatorHighestBit((uint32)uiSize);
*piFirst = iHighest - (4 + 3) + 1;
*piSecond = (int)((uiSize >> (iHighest - 4)) ^ (1 << 4));
}
}
STrueMallocatorBlock* CTrueMallocator::FindFree(size uiSize)
{
STrueMallocatorBlock* psBlock;
uint32 uiMap;
size uiRounded;
int iFirst;
int iSecond;
uiRounded = uiSize;
if (uiSize >= ((size)1 << (4 + 3)))
{
uiRounded += ((size)1 << (TrueMallocatorHighestBit((uint32)uiSize) - 4)) - 1;
}
Mapping(uiRounded, &iFirst, &iSecond);
if (iFirst < (32 - (4 + 3) + 1))
{
uiMap = mauiSecondBitmaps[iFirst] & (~(uint32)0 << iSecond);
if (uiMap == 0)
{
uiMap = muiFirstBitmap & (~(uint32)0 << (iFirst + 1));
if (uiMap != 0)
{
iFirst = TrueMallocatorLowestBit(uiMap);
uiMap = mauiSecondBitmaps[iFirst];
}
}
if (uiMap != 0)
{
iSecond = TrueMallocatorLowestBit(uiMap);
return mapsFree[iFirst][iSecond];
}
}
Mapping(uiSize, &iFirst, &iSecond);
for (psBlock = mapsFree[iFirst][iSecond]; psBlock; psBlock = psBlock->psNextFree)
{
if ((psBlock->uiSize & ~(size)3) >= uiSize)
{
return psBlock;
}
}
return 0L;
}
void CTrueMallocator::InsertFree(STrueMallocatorBlock* psBlock)
{
STrueMallocatorBlock* psHead;
int iFirst;
int iSecond;
Mapping(psBlock->uiSize & ~(size)3, &iFirst, &iSecond);
psHead = mapsFree[iFirst][iSecond];
psBlock->psNextFree = psHead;
psBlock->psPreviousFree = 0L;
if (psHead)
{
psHead->psPreviousFree = psBlock;
}
mapsFree[iFirst][iSecond] = psBlock;
muiFirstBitmap |= (uint32)1 << iFirst;
mauiSecondBitmaps[iFirst] |= (uint32)1 << iSecond;
}
void CTrueMallocator::RemoveFree(STrueMallocatorBlock* psBlock)
{
int iFirst;
int iSecond;
Mapping(psBlock->uiSize & ~(size)3, &iFirst, &iSecond);
if (psBlock->psNextFree)
{
psBlock->psNextFree->psPreviousFree = psBlock->psPreviousFree;
}
if (psBlock->psPreviousFree)
{
psBlock->psPreviousFree->psNextFree = psBlock->psNextFree;
}
else
{
mapsFree[iFirst][iSecond] = psBlock->psNextFree;
if (!psBlock->psNextFree)
{
mauiSecondBitmaps[iFirst] &= ~((uint32)1 << iSecond);
if (mauiSecondBitmaps[iFirst] == 0)
{
muiFirstBitmap &= ~((uint32)1 << iFirst);
}
}
}
}
STrueMallocatorBlock* CTrueMallocator::Next(STrueMallocatorBlock* psBlock)
{
return (STrueMallocatorBlock*)((uint8*)psBlock + (psBlock->uiSize & ~(size)3));
}
void CTrueMallocator::MarkFree(STrueMallocatorBlock* psBlock, size uiSize)
{
STrueMallocatorBlock* psNext;
psBlock->uiSize = uiSize | 1 | (psBlock->uiSize & 2);
psNext = Next(psBlock);
psNext->uiPreviousSize = uiSize;
psNext->uiSize |= 2;
}
void CTrueMallocator::Split(STrueMallocatorBlock* psBlock, size uiSize)
{
STrueMallocatorBlock* psRest;
STrueMallocatorBlock* psNext;
size uiTotal;
size uiRest;
uiTotal = psBlock->uiSize & ~(size)3;
if (uiTotal - uiSize < (sizeof(STrueMallocatorBlock)))
{
return;
}
psBlock->uiSize = uiSize | (psBlock->uiSize & 3);
psRest = Next(psBlock);
uiRest = uiTotal - uiSize;
psRest->uiSize = uiRest;
psNext = Next(psRest);
if (psNext->uiSize & 1)
{
RemoveFree(psNext);
uiRest += psNext->uiSize & ~(size)3;
}
MarkFree(psRest, uiRest);
InsertFree(psRest);
}
