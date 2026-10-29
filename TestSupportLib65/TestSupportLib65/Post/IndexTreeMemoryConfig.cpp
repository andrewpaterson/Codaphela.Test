typedef unsigned long size_t;
typedef long ptrdiff_t;
typedef long long max_align_t;
typedef char* va_list;
struct FILE;
typedef long fpos_t;
extern "C"
{
extern FILE* stdin;
extern FILE* stdout;
extern FILE* stderr;
FILE* fopen(const char* szName, const char* szMode);
int fclose(FILE* pcFile);
size_t fread(void* pv, size_t uiSize, size_t uiCount, FILE* pcFile);
size_t fwrite(const void* pv, size_t uiSize, size_t uiCount, FILE* pcFile);
int fseek(FILE* pcFile, long iOffset, int iOrigin);
long ftell(FILE* pcFile);
int fflush(FILE* pcFile);
int feof(FILE* pcFile);
int fgetc(FILE* pcFile);
int fputc(int c, FILE* pcFile);
int fputs(const char* sz, FILE* pcFile);
int puts(const char* sz);
int putchar(int c);
int remove(const char* szName);
int rename(const char* szOld, const char* szNew);
int printf(const char* szFormat, ...);
int fprintf(FILE* pcFile, const char* szFormat, ...);
int sprintf(char* szDest, const char* szFormat, ...);
int snprintf(char* szDest, size_t uiSize, const char* szFormat, ...);
int vsprintf(char* szDest, const char* szFormat, va_list vaArguments);
int vsnprintf(char* szDest, size_t uiSize, const char* szFormat, va_list vaArguments);
int vprintf(const char* szFormat, va_list vaArguments);
int vfprintf(FILE* pcFile, const char* szFormat, va_list vaArguments);
}
extern "C"
{
void* malloc(size_t uiBytes);
void* calloc(size_t uiCount, size_t uiBytes);
void* realloc(void* pv, size_t uiBytes);
void free(void* pv);
int abs(int i);
long labs(long i);
int atoi(const char* sz);
long atol(const char* sz);
long strtol(const char* sz, char** pszEnd, int iBase);
unsigned long strtoul(const char* sz, char** pszEnd, int iBase);
long long strtoll(const char* sz, char** pszEnd, int iBase);
unsigned long long strtoull(const char* sz, char** pszEnd, int iBase);
double strtod(const char* sz, char** pszEnd);
float strtof(const char* sz, char** pszEnd);
long double strtold(const char* sz, char** pszEnd);
double atof(const char* sz);
int rand(void);
void srand(unsigned int uiSeed);
void qsort(void* pvBase, size_t uiCount, size_t uiBytes, int (*fCompare)(const void*, const void*));
void abort(void);
int atexit(void (*fFunction)(void));
void exit(int iStatus);
void _Exit(int iStatus);
}
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
class _CForceVirtualSuper1
{
virtual void _ForceVirtual1(void) {};
};
class _CForceVirtualSuper2
{
virtual void _ForceVirtual2(void) {};
};
class CConstructable : public _CForceVirtualSuper1, public _CForceVirtualSuper2
{
public:
virtual const char* ClassName(void) =0;
virtual size ClassSize(void) =0;
};
class CChars;
class CKillable
{
public:
virtual void Kill(void) =0;
virtual void Print(CChars* psz);
};
class CFileReader;
class CFileWriter;
template<class M>
class CArrayTemplatePtr;
typedef CArrayTemplatePtr<void> CArrayVoidPtr;
class CMallocator : public CConstructable, public CKillable
{
public:
virtual void* Malloc(lsize uiSize) =0;
virtual void* Malloc(lsize uiSize, char(** pacDebugName)[4]);
virtual void* Realloc(void* pv, lsize uiSize) =0;
virtual bool Free(void* pv) =0;
virtual size FreeMultiple(CArrayVoidPtr* pav);
virtual bool IsLocal(void) =0;
virtual size SizeOffset(void) =0;
virtual const char* ShortName(void) =0;
};
extern size guiMaxDebugAllocatorSize;
void InitAllocatorDebug(size uiMaxDebugAllocatorSize);
void KillAllocatorDebug(void);
CMallocator* ReadMallocator(CFileReader* pcFileReader);
bool WriteMallocator(CFileWriter* pcFileWriter, CMallocator* pcMalloc);
enum EIndexKeyReverse
{
IKR_Unknown,
IKR_No,
IKR_Yes
};
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
class CIndexTreeDataNode
{
protected:
SLLNode msListNode;
uint16 muiDataSize;
public:
void Init(size uiDataSize);
void Kill(void);
size GetDataSize(void);
void SetDataSize(size uiDataSize);
SLLNode* GetListNode(void);
};
class CIndexTreeNode;
struct SDataOrderIterator
{
CIndexTreeDataNode* pcNode;
};
class CIndexTree;
class CIndexTreeDataOrderer : public CConstructable, public CKillable
{
protected:
CLinkedList mcDataOrder;
CIndexTree* mpcIndexTree;
public:
void Init(void);
virtual void Kill(void);
void New(CIndexTreeDataNode* psNode);
virtual void Put(CIndexTreeDataNode* psNode) =0;
virtual void Get(CIndexTreeDataNode* psNode) =0;
virtual void Remove(CIndexTreeDataNode* psNode) =0;
virtual void HasKey(CIndexTreeDataNode* psNode) =0;
void SetIndexTree(CIndexTree* pcIndexTree);
bool StartIteration(SDataOrderIterator* psIter, uint8* pvDestKey, size* piKeySize, size iDestKeySize, void* pvDestData, size* piDataSize, size iDestDataSize);
bool Iterate(SDataOrderIterator* psIter, uint8* pvDestKey, size* piKeySize, size iDestKeySize, void* pvDestData, size* piDataSize, size iDestDataSize);
CIndexTreeNode* GetFirstTreeNode(void);
CIndexTreeNode* GetLastTreeNode(void);
void RemapNode(CIndexTreeDataNode* psOldNode, CIndexTreeDataNode* psNewNode);
protected:
bool IterateNode(SLLNode* psNode, SDataOrderIterator* psIter, uint8* pvDestKey, size* piKeySize, size iDestKeySize, void* pvDestData, size* piDataSize, size iDestDataSize);
};
uint32 TruncateLowBits(uint32 i);
bool IsPowerOfTwo(uint32 i);
uint32 GetBestHighBit(uint32 i);
size GetLogBase2(uint32 i);
uint8 GetByte(uint32 iInt, uint16 iPos);
uint32 SetByte(uint8 c, uint16 iPos);
bool GetBit(size iBit, void* pvBitArray);
bool GetBitReverseHiLo(size iBit, void* pvBitArray);
size CountBits(void* pvBitArray, size iBitLength);
size CountBitsSingly(void* pvBitArray, size iBitLength);
size CountDigits(int16 i);
size CountDigits(int32 i);
size CountDigits(int64 i);
void SetBit(size iBit, void* pvBitArray, bool bBit);
void SetBits(size iStart, void* pvBitArray, bool bBit, size iLength);
void SetFlagByte(uint8* psiDest, uint8 iFlag, bool iFlagValue);
void SetFlagByte(int8* psiDest, int8 iFlag, bool iFlagValue);
void SetFlagShort(uint16* psiDest, uint16 iFlag, bool iFlagValue);
void SetFlagShort(int16* psiDest, int16 iFlag, bool iFlagValue);
void SetFlagInt(uint32* piDest, uint32 iFlag, bool iFlagValue);
void SetFlagInt(int32* piDest, int32 iFlag, bool iFlagValue);
void SetFlagLong(uint64* psiDest, uint64 iFlag, bool iFlagValue);
void SetFlagLong(int64* psiDest, int64 iFlag, bool iFlagValue);
void SetFlagSize(size* piDest, size iFlag, bool iFlagValue);
size FindFirstClearBit(void* pvArray, size iArraySize);
size FindFirstClearBit(uint32 uiBits);
size FindFirstSetBit(void* pvArray, size iArraySize);
size FindFirstSetBit(uint64 uiBits);
size FindLastClearBit(void* pvArray, size iArraySize);
size FindLastSetBit(void* pvArray, size iArraySize);
size FindNextSetBit(void* pvArray, size iArraySize, size iStartBit);
size FindNextClearBit(void* pvArray, size iArraySize, size iStartBit);
void SwapInt16(int16* pi1, int16* pi2);
void SwapUint16(uint16* pi1, uint16* pi2);
void SwapInt32(int32* pi1, int32* pi2);
void SwapUint32(uint32* pi1, uint32* pi2);
void SwapInt(int* pi1, int* pi2);
void SwapInt(uint* pi1, uint* pi2);
void SwapByte(uint8* pc1, uint8* pi2);
void SwapSize(size* pui1, size* pui2);
void SwapBit(uint8* puiByte, size uiBit1, size uiBit2);
void SwapBit(uint16* puiByte, size uiBit1, size uiBit2);
size FindFirstInt(int32* piIntArray, int32 iSearch, size iMaxLength);
size FindFirstByte(uint8* pcCharArray, uint8 uiSearch, size iMaxLength);
uint8 GetHighNybble(uint8 c);
uint8 GetLowNybble(uint8 c);
uint8 GetLowByte(uint16 uiValue);
uint8 GetHighByte(uint16 uiValue);
uint16 SetLowByte(uint16 uiVariable, uint8 uiData);
uint16 SetHighByte(uint16 uiVariable, uint8 uiData);
int CompareByte(const void* arg1, const void* arg2);
int CompareByteReverse(const void* arg1, const void* arg2);
int CompareShort(const void* arg1, const void* arg2);
int CompareShortReverse(const void* arg1, const void* arg2);
int CompareInt(const void* arg1, const void* arg2);
int CompareIntReverse(const void* arg1, const void* arg2);
int CompareLong(const void* arg1, const void* arg2);
int CompareLongReverse(const void* arg1, const void* arg2);
uint8 GetCrumb(size iCrumb, void* pvArray);
uint8 GetNybble(size iNybble, void* pvArray);
void CopyBits(void* pvDest, size iDestOffset, void* pvSource, size iSourceOffset, size iNumBits, bool bClear);
void CopyBitsReverseHiLo(void* pvDest, size iDestOffset, void* pvSource, size iSourceOffset, size iNumBits, bool bClear);
int16 ReverseShortEndianness(int16 s);
int32 ReverseIntEndianness(int32 i);
int64 ReverseLongEndianness(int64 i);
uint16 ReverseShortEndianness(uint16 s);
uint32 ReverseIntEndianness(uint32 i);
uint64 ReverseLongEndianness(uint64 i);
void ReverseEndianness(void* pv, size iSize);
void ReverseBytes(void* pv, size iSize);
size CalculateStride(size iElementSize, uint16 iAlignment);
uint8 CalculateOffset(int16 iOffset, uint16 iAlignment);
int32 IntAbs(int32 i);
uint32 GetPowerOf2SizeDown(uint32 iInt);
uint32 GetPowerOf2SizeUp(uint32 iInt);
uint32 GetPowerOf2SizeAuto(uint32 iInt);
int32 LargestInt(int32* pInts, int32 iCount);
size Min(size ui1, size ui2);
size Max(size ui1, size ui2);
int8 Absolute(int8 i);
int16 Absolute(int16 i);
int32 Absolute(int32 i);
int64 Absolute(int64 i);
int16 SquareRoot(int16 i);
int32 SquareRoot(int32 i);
int64 SquareRoot(int64 i);
inline bool FixBool(int32 i)
{
return i != 0;
}
inline bool FixBool(void* pv)
{
return pv != 0L;
}
void* operator new(size_t uiBytes);
void* operator new[](size_t uiBytes);
void operator delete(void* pv) noexcept;
void operator delete[](void* pv) noexcept;
inline void* operator new(size_t uiBytes, void* pv) noexcept { return pv; }
inline void* operator new[](size_t uiBytes, void* pv) noexcept { return pv; }
void* RemapSinglePointer(const void* pvPtr, ptrdiff iOffest);
__inline void* RemapSinglePointer(const void* pvPtr, ptrdiff iOffest)
{
return &((char*)pvPtr)[iOffest];
}
template<class Class>
constexpr bool IsTriviallyDefaultConstructible(void)
{
return __is_trivially_constructible(Class);
}
template<class Class>
Class* NewMalloc(void)
{
Class* pv;
pv = (Class*)malloc(sizeof(Class));
memset(pv, 0, sizeof(Class));
new(pv) Class;
return pv;
}
template<class Class>
Class* New(Class* pv)
{
memset(pv, 0, sizeof(Class));
new(pv) Class;
return pv;
}
template<class Class>
class CPostMalloc
{
public:
Class* PostMalloc(Class* pv);
Class* PostMalloc(Class* pv, lsize iNumElements, lsize iStride);
template<class Subclass>
Class* PostMalloc(Subclass* pv);
template<class Subclass>
Class* PostMalloc(Subclass* pv, lsize iNumElements, lsize iStride);
bool RequiresVirtualFunctionTable(void);
};
template<class Class>
Class* CPostMalloc<Class>::PostMalloc(Class* pv)
{
if (!IsTriviallyDefaultConstructible<Class>())
{
new(pv) Class;
}
return pv;
}
template<class Class>
Class* CPostMalloc<Class>::PostMalloc(Class* pv, lsize iNumElements, lsize iStride)
{
lsize i;
if (RequiresVirtualFunctionTable())
{
for (i = 0; i < iNumElements; i++)
{
new(pv) Class;
pv = (Class*)RemapSinglePointer(pv, iStride);
}
}
return pv;
}
template<class Class> template<class Subclass>
Class* CPostMalloc<Class>::PostMalloc(Subclass* pv)
{
if (!IsTriviallyDefaultConstructible<Subclass>())
{
new(pv) Subclass;
}
return pv;
}
template<class Class> template<class Subclass>
Class* CPostMalloc<Class>::PostMalloc(Subclass* pv, lsize iNumElements, lsize iStride)
{
lsize i;
if (RequiresVirtualFunctionTable())
{
for (i = 0; i < iNumElements; i++)
{
new(pv) Subclass;
pv = (Subclass*)RemapSinglePointer(pv, iStride);
}
}
return pv;
}
template<class Class>
bool CPostMalloc<Class>::RequiresVirtualFunctionTable(void)
{
return !IsTriviallyDefaultConstructible<Class>();
}
template <class M>
class CLife
{
protected:
M** mppcLifeCycleObject;
uint32 mcFlags;
public:
void _Init(void);
void Init(M** ppcLifeCycleObject, bool bMustFree, bool bMustKill);
void Kill(void);
bool MustKill(void);
bool MustFree(void);
bool IsInitialised(void);
bool HasLifeCycleObject(void);
bool IsKilled(void);
};
template <class M>
class CLifeInit
{
protected:
M* mpcLifeCycleObject;
uint8 mcFlags;
public:
void Init(M* pcLifeCycleObject, bool bMustFree = true, bool bMustKill = true);
void Null(void);
void ConfigureLife(CLife<M>* pcLife, M** ppcLifeCycleObject);
M* GetLife(void);
bool MustKill(void);
bool MustFree(void);
};
template <class M>
void CLife<M>::_Init(void)
{
mppcLifeCycleObject = 0L;
mcFlags = 0;
};
template <class M>
void CLife<M>::Init(M** ppcLifeCycleObject, bool bMustFree, bool bMustKill)
{
mppcLifeCycleObject = ppcLifeCycleObject;
mcFlags = 0xB6A45B00;
SetFlagInt(&mcFlags, 0x02, bMustFree);
SetFlagInt(&mcFlags, 0x01, bMustKill);
};
template <class SpecificClass, class SuperClass, typename ... Args>
CLifeInit<SuperClass> LifeAlloc(Args ... args)
{
CLifeInit<SuperClass> cLife;
SpecificClass* pcLife;
pcLife = NewMalloc<SpecificClass>();
pcLife->Init(args...);
cLife.Init(pcLife, true, true);
return cLife;
}
template <class SuperClass>
CLifeInit<SuperClass> LifeLocal(SuperClass* pcLifeCycleObject)
{
CLifeInit<SuperClass> cLife;
cLife.Init(pcLifeCycleObject, false, false);
return cLife;
}
template <class SuperClass>
CLifeInit<SuperClass> LifeNull(void)
{
CLifeInit<SuperClass> cLife;
cLife.Null();
return cLife;
}
template <class M>
void CLifeInit<M>::Init(M* pcLifeCycleObject, bool bMustFree, bool bMustKill)
{
mpcLifeCycleObject = pcLifeCycleObject;
mcFlags = 0;
SetFlagByte(&mcFlags, 0x02, bMustFree);
SetFlagByte(&mcFlags, 0x01, bMustKill);
}
template <class M>
void CLifeInit<M>::Null(void)
{
Init(0L, false, false);
}
template <class M>
void CLifeInit<M>::ConfigureLife(CLife<M>* pcLife, M** ppcLifeCycleObject)
{
bool bMustFree;
bool bMustKill;
bMustFree = MustFree();
bMustKill = MustKill();
pcLife->Init(ppcLifeCycleObject, bMustFree, bMustKill);
if (ppcLifeCycleObject)
{
*ppcLifeCycleObject = mpcLifeCycleObject;
}
}
template <class M>
M* CLifeInit<M>::GetLife(void)
{
return mpcLifeCycleObject;
}
template <class M>
bool CLifeInit<M>::MustKill(void)
{
return FixBool(mcFlags & 0x01);
}
template <class M>
bool CLifeInit<M>::MustFree(void)
{
return FixBool(mcFlags & 0x02);
}
template <class M>
void CLife<M>::Kill(void)
{
CKillable* mpcKillable;
if (mppcLifeCycleObject)
{
mpcKillable = *mppcLifeCycleObject;
if (mpcKillable)
{
if (MustKill())
{
mpcKillable->Kill();
mcFlags = (mcFlags & 0x000000FF) | 0x5D59B400;
}
if (MustFree())
{
free(*mppcLifeCycleObject);
}
*mppcLifeCycleObject = 0L;
}
mppcLifeCycleObject = 0L;
}
}
template <class M>
bool CLife<M>::MustKill(void)
{
return FixBool(mcFlags & 0x01);
}
template <class M>
bool CLife<M>::MustFree(void)
{
return FixBool(mcFlags & 0x02);
}
template <class M>
bool CLife<M>::IsInitialised(void)
{
return (mcFlags & ~0x000000FF) == 0xB6A45B00;
}
template <class M>
bool CLife<M>::HasLifeCycleObject(void)
{
if (mppcLifeCycleObject != 0L)
{
return *mppcLifeCycleObject != 0L;
}
return false;
}
template <class M>
bool CLife<M>::IsKilled(void)
{
return (mcFlags & ~0x000000FF) == 0x5D59B400;
}
class CAccessDataOrderer : public CIndexTreeDataOrderer
{
public:const char* ClassName(void){ return "CAccessDataOrderer";}size ClassSize(void){ return sizeof(CAccessDataOrderer);}
public:
void Init(void);
void Kill(void);
void Put(CIndexTreeDataNode* psNode);
void Get(CIndexTreeDataNode* psNode);
void Remove(CIndexTreeDataNode* psNode);
void HasKey(CIndexTreeDataNode* psNode);
public:
static CLifeInit<CIndexTreeDataOrderer> Create(void);
};
class CIndexTreeConfig
{
protected:
CLifeInit<CMallocator> mcMalloc;
CLifeInit<CIndexTreeDataOrderer> mcDataOrderer;
size miMaxDataSize;
size miMaxKeySize;
EIndexKeyReverse meKeyReverse;
public:
void Init(CLifeInit<CMallocator> cMalloc, EIndexKeyReverse eKeyReverse, size iMaxDataSize, size iMaxKeySize, CLifeInit<CIndexTreeDataOrderer> cDataOrderer);
bool Init(CFileReader* pcFileReader);
virtual void Kill(void) =0;
virtual bool Write(CFileWriter* pcFileWrite);
CLifeInit<CMallocator> GetMalloc(void);
EIndexKeyReverse GetKeyReverse(void);
size GetMaxDataSize(void);
size GetMaxKeySize(void);
CLifeInit<CIndexTreeDataOrderer> GetDataOrderer(void);
protected:
virtual bool Read(CFileReader* pcFileReader);
EIndexKeyReverse ReadKeyReverse(CFileReader* pcFileReader);
bool WriteKeyReverse(CFileWriter* pcFileWriter, EIndexKeyReverse eKeyReverse);
CIndexTreeDataOrderer* ReadDataOrderer(CFileReader* pcFileReader);
bool WriteDataOrderer(CFileWriter* pcFileWriter, CIndexTreeDataOrderer*);
};
class CIndexTreeMemoryConfig : public CIndexTreeConfig
{
public:
void Init(CLifeInit<CMallocator> cMalloc, EIndexKeyReverse eKeyReverse, int iMaxDataSize, int iMaxKeySize, CLifeInit<CIndexTreeDataOrderer> cDataOrderer);
bool Init(CFileReader* pcFileReader);
void Kill(void);
bool Write(CFileWriter* pcFileWriter);
bool Read(CFileReader* pcFileReader);
};
void CIndexTreeMemoryConfig::Init(CLifeInit<CMallocator> cMalloc, EIndexKeyReverse eKeyReverse, int iMaxDataSize, int iMaxKeySize, CLifeInit<CIndexTreeDataOrderer> cDataOrderer)
{
CIndexTreeConfig::Init(cMalloc, eKeyReverse, iMaxDataSize, iMaxKeySize, cDataOrderer);
}
bool CIndexTreeMemoryConfig::Init(CFileReader* pcFileReader)
{
return CIndexTreeConfig::Init(pcFileReader);
}
void CIndexTreeMemoryConfig::Kill(void)
{
}
bool CIndexTreeMemoryConfig::Write(CFileWriter* pcFileWriter)
{
return CIndexTreeConfig::Write(pcFileWriter);
}
bool CIndexTreeMemoryConfig::Read(CFileReader* pcFileReader)
{
return CIndexTreeConfig::Read(pcFileReader);
}
