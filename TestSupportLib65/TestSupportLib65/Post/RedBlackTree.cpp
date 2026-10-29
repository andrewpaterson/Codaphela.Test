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
void* RemapSinglePointer(const void* pvPtr, ptrdiff iOffest);
__inline void* RemapSinglePointer(const void* pvPtr, ptrdiff iOffest)
{
return &((char*)pvPtr)[iOffest];
}
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
typedef int (*DataCompare)(const void* pvLeft, const void* pvRight);
template<class T, class M>
M* HeaderGetData(T* pv)
{
if (pv == 0L)
{
return 0L;
}
return (M*)RemapSinglePointer(pv, sizeof(T));
}
template<class T, class M>
T* DataGetHeader(M* pv)
{
if (pv == 0L)
{
return 0L;
}
return (T*)RemapSinglePointer(pv, -(ptrdiff_t)sizeof(T));
}
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
enum TRISTATE
{
TRITRUE = true,
TRIFALSE = false,
TRIGNORED = 0xfffffffe,
TRIERROR = 0xffffffff
};
extern TRISTATE gTriState;
TRISTATE Negate(TRISTATE tristate);
TRISTATE Fix(TRISTATE tristate);
bool NotTrue(TRISTATE tristate);
typedef int64 filePos;
class CFileReader
{
public:
bool ReadData(void* pvData, lsize iDataSize);
bool ReadStringLength(size* piLength);
bool ReadStringChars(char* szString, size iLength);
bool ReadString(char* szString, size iMaxLength);
bool ReadInt8(int8* pi);
bool ReadInt8(uint8* pi);
bool ReadInt16(int16* pi);
bool ReadInt16(uint16* pi);
bool ReadInt32(int32* pi);
bool ReadInt32(uint32* pi);
bool ReadInt64(int64* plli);
bool ReadInt64(uint64* plli);
bool ReadSInt(int* pi);
bool ReadSInt(uint* pi);
bool ReadSize(lsize* pui);
bool ReadSizes(size* pai, size iLength);
bool ReadFloat(float32* pf);
bool ReadFloat(float64* pf);
bool ReadChar(char8* pc);
bool ReadWChar(char16* pc);
bool ReadBool(bool* pb);
bool ReadBits(void* pvData, size iByteLength);
bool ReadIntArray(int32* pai, size iLength);
bool ReadLittleEndianInt16(int16* pi);
bool ReadLittleEndianInt16(uint16* pui);
bool ReadLittleEndianInt32(int32* pi);
bool ReadLittleEndianInt32(uint32* pui);
bool ReadBigEndianInt16(int16* pi);
bool ReadBigEndianInt16(uint16* pui);
bool ReadBigEndianInt32(int32* pi);
bool ReadBigEndianInt32(uint32* pui);
template<class M>
bool ReadPrimitive(M* pc);
protected:
virtual size Read(void* pvDest, lsize iSize, lsize iCount) =0;
};
template<class M>
bool CFileReader::ReadPrimitive(M* pc)
{
if (Read(pc, sizeof(M), 1) != 1) { return false; };
return true;
}
class CFileWriter
{
public:
bool WriteData(const void* pvData, lsize iDataSize);
bool WriteString(const char* szString);
bool WriteInt(int i);
bool WriteInt(uint i);
bool WriteInt8(int8 i);
bool WriteInt8(uint8 i);
bool WriteInt16(int16 i);
bool WriteInt16(uint16 i);
bool WriteInt32(int32 i);
bool WriteInt32(uint32 i);
bool WriteInt64(int64 i);
bool WriteInt64(uint64 i);
bool WriteSize(lsize ui);
bool WriteSizes(size* pai, size iLength);
bool WriteSInt(int i);
bool WriteSInt(uint i);
bool WriteFloat(float32 f);
bool WriteFloat(float64 f);
bool WriteChar(char8 c);
bool WriteWChar(char16 c);
bool WriteBool(bool b);
bool WriteBits(void* pvData, size iBitLength);
bool WriteIntArray(int32* pai, size iLength);
bool WriteLittleEndianInt16(int16 i);
bool WriteLittleEndianInt16(uint16 ui);
bool WriteLittleEndianInt32(int32 i);
bool WriteLittleEndianInt32(uint32 ui);
bool WriteBigEndianInt16(int16 i);
bool WriteBigEndianInt16(uint16 ui);
bool WriteBigEndianInt32(int32 i);
bool WriteBigEndianInt32(uint32 ui);
template<class M>
bool WritePrimitive(M c);
protected:
virtual size Write(const void* pvSource, lsize iSize, lsize iCount) =0;
};
template<class M>
bool CFileWriter::WritePrimitive(M c)
{
if (Write(&c, sizeof(M), 1) != 1) { return false; };
return true;
}
class CFileIO : public CFileReader, public CFileWriter
{
};
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
class CMalloc
{
protected:
CMallocator* mpcMalloc;
public:
void Init(CMallocator* pcMalloc);
void Kill(void);
void* Malloc(lsize uiSize);
void* Realloc(void* pv, lsize iMemSize);
void Free(void* pv);
bool IsMallocInitialised(void);
bool IsMalloc(CMallocator* pcMalloc);
};
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
struct SLinkedListBlockDesc
{
size iNumElements;
size uiNodeSize;
void Init(size iNumElements, size uiNodeSize);
bool Write(CFileWriter* pcFileWriter);
bool Read(CFileReader* pcFileReader);
};
struct SLinkedListTemplateDesc
{
size iNumElements;
size uiNodeSize;
size uiDataSize;
void Init(size iNumElements, size uiNodeSize, size uiDataSize);
bool Write(CFileWriter* pcFileWriter);
bool Read(CFileReader* pcFileReader);
};
class CBaseLinkedListBlock : public CMalloc
{
protected:
CLinkedList mcList;
size muiNodeSize;
public:
void Init(size uiNodeSize);
void Init(CMallocator* pcMalloc, size uiNodeSize);
void Kill(void);
void* InsertAfterTail(size uiDataSize);
void* InsertBeforeHead(size uiDataSize);
void* InsertBeforeNode(size uiDataSize, void* psPos);
void* InsertAfterNode(size uiDataSize, void* psPos);
void* GetHead(void);
void* GetTail(void);
void* GetNext(void* pvData);
void* GetPrev(void* pvData);
void RemoveTail(void);
void Remove(void* pvData);
bool SafeRemove(void* pvData);
void MoveToHead(void* pvData);
void MoveToTTail(void* pvData);
void* InsertDetachedAfterTail(SLLNode* psNode);
void* InsertDetachedBeforeHead(SLLNode* psNode);
void* InsertDetachedBeforeNode(SLLNode* psData, SLLNode* psPos);
void* InsertDetachedAfterNode(SLLNode* psData, SLLNode* psPos);
void Detach(SLLNode* psNodeHeader);
void Detach(void* pvData);
void FreeDetached(void* pvData);
size NumElements(void);
void* Get(size iNum);
size IndexOf(void* pvData);
bool IsInList(void* pvData);
void BubbleSort(DataCompare fCompare);
void InsertDetachedIntoSorted(DataCompare fCompare, void* pvData);
protected:
SLLNode* AllocateDetached(size uiDataSize);
void Swap(void* psData1, void* psData2);
void* NodeGetData(SLLNode* psNode);
SLLNode* DataGetNode(void* pvData);
};
struct SLLBlockNode : public SLLNode
{
size uiSize;
};
class CLinkedListBlock : public CBaseLinkedListBlock
{
public:
void Init(void);
void Init(CMallocator* pcMalloc);
void Kill(void);
void* Add(size uiDataSize);
size ByteSize(void);
bool Write(CFileWriter* pcFileWriter);
bool Read(CFileReader* pcFileReader);
void InsertDetachedAfterTail(void* pvData);
void* InsertAfterTail(size uiDataSize);
void* InsertBeforeHead(size uiDataSize);
void* InsertBeforeNode(size uiDataSize, void* psPos);
void* InsertAfterNode(size uiDataSize, void* psPos);
protected:
size GetNodeSize(void* psData);
size GetDataSize(void* pvData);
SLLBlockNode* AllocateDetached(size uiDataSize);
SLLBlockNode* DataGetNode(void *pvData);
bool WriteHeader(CFileWriter* pcFileWriter);
bool WriteData(CFileWriter* pcFileWriter);
bool ReadHeader(CFileReader* pcFileReader, CMallocator* pcMalloc, size* piNumElements);
bool ReadData(CFileReader* pcFileReader, size iNumElements);
};
void* operator new(size_t uiBytes);
void* operator new[](size_t uiBytes);
void operator delete(void* pv) noexcept;
void operator delete[](void* pv) noexcept;
inline void* operator new(size_t uiBytes, void* pv) noexcept { return pv; }
inline void* operator new[](size_t uiBytes, void* pv) noexcept { return pv; }
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
class CSystemAllocator : public CMallocator
{
public:const char* ClassName(void){ return "CSystemAllocator";}size ClassSize(void){ return sizeof(CSystemAllocator);}
public:
void Kill(void);
void* Malloc(lsize uiSize);
void* Realloc(void* pv, lsize iMemSize);
bool Free(void* pv);
bool IsLocal(void);
size SizeOffset(void);
const char* ShortName(void);
};
extern CSystemAllocator gcSystemAllocator;
template<class M>
class CLinkedListTemplate : public CBaseLinkedListBlock, public CPostMalloc<M>
{
private:
uint32 muiDataSize;
public:
void Init(void);
void Init(CMallocator* pcMalloc);
void Kill(void);
M* InsertAfterTail(void);
M* InsertBeforeHead(void);
M* InsertBeforeNode(M* psPos);
M* InsertAfterNode(M* psPos);
M* Add(void);
M* GetHead(void);
M* GetTail(void);
M* GetNext(M* pvData);
M* GetPrev(M* pvData);
void Remove(M* pvData);
bool SafeRemove(M* pvData);
size ByteSize(void);
bool Write(CFileWriter* pcFileWriter);
bool Read(CFileReader* pcFileReader);
void InsertDetachedAfterTail(M* pvData);
protected:
SLLNode* AllocateDetached(void);
SLLNode* DataGetNode(M* pvData);
bool WriteHeader(CFileWriter* pcFileWriter);
bool WriteData(CFileWriter* pcFileWriter);
bool ReadHeader(CFileReader* pcFileReader, CMallocator* pcMalloc, size* piNumElements);
bool ReadData(CFileReader* pcFileReader, size iNumElements);
};
template<class M>
void CLinkedListTemplate<M>::Init(void)
{
Init(&gcSystemAllocator);
}
template<class M>
void CLinkedListTemplate<M>::Init(CMallocator* pcMalloc)
{
CBaseLinkedListBlock::Init(pcMalloc, sizeof(SLLNode));
muiDataSize = sizeof(M);
}
template<class M>
void CLinkedListTemplate<M>::Kill(void)
{
CBaseLinkedListBlock::Kill();
}
template<class M>
M* CLinkedListTemplate<M>::GetHead(void)
{
return (M*)CBaseLinkedListBlock::GetHead();
}
template<class M>
M* CLinkedListTemplate<M>::GetTail(void)
{
return (M*)CBaseLinkedListBlock::GetTail();
}
template<class M>
M* CLinkedListTemplate<M>::GetNext(M* pvData)
{
return (M*)CBaseLinkedListBlock::GetNext(pvData);
}
template<class M>
M* CLinkedListTemplate<M>::GetPrev(M* pvData)
{
return (M*)CBaseLinkedListBlock::GetPrev(pvData);
}
template<class M>
void CLinkedListTemplate<M>::Remove(M* pvData)
{
CBaseLinkedListBlock::Remove(pvData);
}
template<class M>
bool CLinkedListTemplate<M>::SafeRemove(M* pvData)
{
return (M*)CBaseLinkedListBlock::SafeRemove(pvData);
}
template<class M>
size CLinkedListTemplate<M>::ByteSize(void)
{
size iSize;
M* pvNode;
iSize = 0;
pvNode = GetHead();
while (pvNode)
{
iSize += muiNodeSize + muiDataSize;
pvNode = GetNext(pvNode);
}
return iSize;
}
template<class M>
M* CLinkedListTemplate<M>::InsertAfterTail(void)
{
SLLNode* psNode;
psNode = AllocateDetached();
return (M*)CBaseLinkedListBlock::InsertDetachedAfterTail(psNode);
}
template<class M>
M* CLinkedListTemplate<M>::Add(void)
{
return InsertAfterTail();
}
template<class M>
M* CLinkedListTemplate<M>::InsertBeforeHead(void)
{
SLLNode* psNode;
psNode = AllocateDetached();
return (M*)CBaseLinkedListBlock::InsertDetachedBeforeHead(psNode);
}
template<class M>
M* CLinkedListTemplate<M>::InsertBeforeNode(M* psPos)
{
SLLNode* psNode;
SLLNode* psNodePos;
psNodePos = DataGetNode(psPos);
psNode = AllocateDetached();
return (M*)CBaseLinkedListBlock::InsertDetachedBeforeNode(psNode, psNodePos);
}
template<class M>
M* CLinkedListTemplate<M>::InsertAfterNode(M* psPos)
{
SLLNode* psNode;
SLLNode* psNodePos;
psNodePos = DataGetNode(psPos);
psNode = AllocateDetached();
return (M*)CBaseLinkedListBlock::InsertDetachedAfterNode(psNode, psNodePos);
}
template<class M>
SLLNode* CLinkedListTemplate<M>::AllocateDetached(void)
{
return CBaseLinkedListBlock::AllocateDetached(muiDataSize);
}
template<class M>
SLLNode* CLinkedListTemplate<M>::DataGetNode(M* pvData)
{
return (SLLNode*)CBaseLinkedListBlock::DataGetNode(pvData);
}
template<class M>
void CLinkedListTemplate<M>::InsertDetachedAfterTail(M* pvData)
{
SLLNode* psNode;
psNode = DataGetNode(pvData);
CBaseLinkedListBlock::InsertDetachedAfterTail(psNode);
}
template<class M>
bool CLinkedListTemplate<M>::Write(CFileWriter* pcFileWriter)
{
bool bResult;
bResult = WriteMallocator(pcFileWriter, mpcMalloc);
if (!bResult)
{
return false;
}
bResult = WriteHeader(pcFileWriter);
if (!bResult)
{
return false;
}
bResult = WriteData(pcFileWriter);
return bResult;
}
template<class M>
bool CLinkedListTemplate<M>::WriteHeader(CFileWriter* pcFileWriter)
{
SLinkedListTemplateDesc sHeader;
size iNumElements;
iNumElements = NumElements();
sHeader.Init(iNumElements, 8, muiDataSize);
if (!sHeader.Write(pcFileWriter))
{
return false;
}
return true;
}
template<class M>
bool CLinkedListTemplate<M>::WriteData(CFileWriter* pcFileWriter)
{
M* pvData;
pvData = GetHead();
while (pvData)
{
if (!pcFileWriter->WriteData(pvData, muiDataSize))
{
return false;
}
pvData = GetNext(pvData);
}
return true;
}
template<class M>
bool CLinkedListTemplate<M>::Read(CFileReader* pcFileReader)
{
size iNumElements;
bool bResult;
CMallocator* pcMalloc;
pcMalloc = ReadMallocator(pcFileReader);
if (pcMalloc == 0L)
{
return false;
}
bResult = ReadHeader(pcFileReader, pcMalloc, &iNumElements);
if (!bResult)
{
return false;
}
bResult = ReadData(pcFileReader, iNumElements);
return bResult;
}
template<class M>
bool CLinkedListTemplate<M>::ReadHeader(CFileReader* pcFileReader, CMallocator* pcMalloc, size* piNumElements)
{
SLinkedListTemplateDesc sDesc;
if (!sDesc.Read(pcFileReader))
{
return false;
}
if (8 != sDesc.uiNodeSize)
{
return false;
}
if (sizeof(M) != sDesc.uiDataSize)
{
return false;
}
Init(pcMalloc);
*piNumElements = sDesc.iNumElements;
return true;
}
template<class M>
bool CLinkedListTemplate<M>::ReadData(CFileReader* pcFileReader, size iNumElements)
{
size i;
M* pvData;
for (i = 0; i < iNumElements; i++)
{
pvData = InsertAfterTail();
if (!pcFileReader->ReadData(pvData, muiDataSize))
{
return false;
}
}
return true;
}
class CSlabAllocator : public CMallocator
{
public:const char* ClassName(void){ return "CSlabAllocator";}size ClassSize(void){ return sizeof(CSlabAllocator);}
public:
void Kill(void);
void* Malloc(lsize uiSize);
void* Realloc(void* pv, lsize uiSize);
bool Free(void* pv);
bool IsLocal(void);
size SizeOffset(void);
const char* ShortName(void);
protected:
void* AllocateSlab(void);
void FreeSlab(void* pvSlab);
};
extern CSlabAllocator gcSlabAllocator;
void* GetSlab(void* pv);
class CFreeList;
struct SFNode
{
uint8 bFull;
int8 iOffset;
uint32 uiUsed;
size uiChunkSize;
CFreeList* pcList;
SFNode* psNextNotFull;
SFNode* psPrevNotFull;
};
struct SFreeListParams
{
uint8 uiAlignment;
int8 iOffset;
uint16 uiElementSize;
};
struct SFreeListIterator
{
SFNode* psCurrent;
size iPosition;
};
class CFreeList
{
protected:
CLinkedListBlock mcList;
SFNode* mpsUnused;
SFNode* mpsNotFullHead;
size muiNumElements;
uint8 muiOffset;
int8 miSuppliedOffset;
uint8 muiAlignment;
uint8 muiMagic;
uint16 muiStride;
uint16 muiElementSize;
bool mbSlabs;
public:
void Init(size uiElementSize);
void Init(size uiElementSize, size uiAlignment);
void Init(size uiElementSize, size uiAlignment, int16 iOffset);
void Init(size uiElementSize, size uiAlignment, int16 iOffset, bool bSlabs);
void Kill(void);
void* Add(SFNode** ppsNode = 0L);
void* Add(void* pvData);
bool Remove(void* pvData);
bool Remove(SFNode* psNode, void* pvData);
void* Get(size iElement);
void* StartIteration(SFreeListIterator* psIterator);
void* Iterate(SFreeListIterator* psIterator);
bool RemoveDuringIteration(SFreeListIterator* psIterator);
bool Contains(void* pvData, bool bIsAllocated = true);
size NumElements(void);
bool HasElements(void);
size NumNodeElements(SFNode* psNode);
size NumNodes(void);
void SetAdditionalSize(size iSize);
size GetElementSize(void);
size GetElementStride(void);
size GetNumAllocatedChunks(void);
SFNode* GetNode(size iNode);
void* GetElement(SFNode* psNode, size iPosition);
uint8 GetOffset(void);
uint8 GetAlignment(void);
void* GetBitArray(SFNode* psNode);
SFNode* FindNode(void* pvData, bool bIsAllocated = true);
size ByteSize(void);
void* GetFirstNodeElement(SFNode* psNode);
void* GetLastNodeElement(SFNode* psNode);
void RemoveNode(SFNode* psNode);
void GetParams(SFreeListParams* psParams);
static SFNode* GetSlabNode(void* pvData);
protected:
SFNode* AllocateNew(void);
void Deallocate(SFNode* psNode);
void* AllocateExisting(SFNode* psNode, size iPosition);
void LinkNotFull(SFNode* psNode);
void UnlinkNotFull(SFNode* psNode);
size FindFirstFreePosition(SFNode* psNode);
bool FindNextAllocatedElement(SFreeListIterator* psIterator);
bool FindPrevAllocatedElement(SFreeListIterator* psIterator);
bool RemoveExisiting(SFNode* psNode, size iPosition);
size CalculateStride(void);
uint8 CalculateOffset(int16 iOffset);
size CalculateBitArraySize(size uiChunkSize);
size CalculateNodeSize(size uiChunkSize);
size CalculateSlabChunkSize(void);
uint8 CalculateOffset(SFNode* psNode);
void* GetElementInNode(SFNode* psNode, size iPosition);
bool IsElementInNodeAllocated(SFNode* psNode, size iPosition);
bool RemoveExisiting(SFNode* psNode, void* pvData);
};
typedef CLinkedListTemplate<CFreeList> CLinkListFreeList;
struct SRedBlackNode
{
SRedBlackNode* psParent;
SRedBlackNode* psLeft;
SRedBlackNode* psRight;
int32 iColour;
SRedBlackNode* GetNext(void);
SRedBlackNode* GetPrevious(void);
SRedBlackNode* GetLeftmost(void);
SRedBlackNode* GetRightmost(void);
};
struct SRedBlackTreeIterator
{
SRedBlackNode* psCurrent;
SRedBlackNode* psStop;
};
class CRedBlackTree
{
protected:
CFreeList mcNodes;
SRedBlackNode* mpsRoot;
DataCompare mfCompare;
size miKeyOffset;
size miElementSize;
size miNumElements;
public:
void Init(size iElementSize, size iKeyOffset, DataCompare fCompare);
void Kill(void);
void* Add(void* pvElement);
void* Put(void* pvElement);
void* Get(void* pvKey);
void* GetOnOrBefore(void* pvKey);
void* GetOnOrAfter(void* pvKey);
void* GetFirst(void);
void* GetLast(void);
void* GetNext(void* pvElement);
void* GetPrevious(void* pvElement);
bool Contains(void* pvKey);
bool Remove(void* pvKey);
void RemoveElement(void* pvElement);
void RemoveAll(void);
size NumElements(void);
bool IsEmpty(void);
void* StartIteration(SRedBlackTreeIterator* psIter);
void* StartIteration(SRedBlackTreeIterator* psIter, void* pvStartKey, void* pvEndKey);
void* Iterate(SRedBlackTreeIterator* psIter);
bool IsValid(void);
SRedBlackNode* TestGetRoot(void);
protected:
SRedBlackNode* FindNode(void* pvKey);
SRedBlackNode* FindNodeOnOrBefore(void* pvKey);
SRedBlackNode* FindNodeOnOrAfter(void* pvKey);
void* GetKey(SRedBlackNode* psNode);
void* GetData(SRedBlackNode* psNode);
SRedBlackNode* GetNode(void* pvElement);
void FixAfterAdd(SRedBlackNode* psNode);
void FixDoubleRed(SRedBlackNode* psChild);
void RemoveNode(SRedBlackNode* psNode);
void FixAfterRemove(SRedBlackNode* psNode, SRedBlackNode* psParent);
void Replace(SRedBlackNode* psNode, SRedBlackNode* psReplacement);
void RotateLeft(SRedBlackNode* psNode);
void RotateRight(SRedBlackNode* psNode);
int RecurseValidate(SRedBlackNode* psNode, size* piCount);
};
template<class M>
class CRedBlackTreeTemplate : public CRedBlackTree
{
public:
void Init(size iKeyOffset, DataCompare fCompare);
M* Add(M* pvElement);
M* Put(M* pvElement);
M* Get(void* pvKey);
M* GetOnOrBefore(void* pvKey);
M* GetOnOrAfter(void* pvKey);
M* GetFirst(void);
M* GetLast(void);
M* GetNext(M* pvElement);
M* GetPrevious(M* pvElement);
M* StartIteration(SRedBlackTreeIterator* psIter);
M* StartIteration(SRedBlackTreeIterator* psIter, void* pvStartKey, void* pvEndKey);
M* Iterate(SRedBlackTreeIterator* psIter);
};
template<class M>
void CRedBlackTreeTemplate<M>::Init(size iKeyOffset, DataCompare fCompare)
{
CRedBlackTree::Init(sizeof(M), iKeyOffset, fCompare);
}
template<class M>
M* CRedBlackTreeTemplate<M>::Add(M* pvElement)
{
return (M*)CRedBlackTree::Add(pvElement);
}
template<class M>
M* CRedBlackTreeTemplate<M>::Put(M* pvElement)
{
return (M*)CRedBlackTree::Put(pvElement);
}
template<class M>
M* CRedBlackTreeTemplate<M>::Get(void* pvKey)
{
return (M*)CRedBlackTree::Get(pvKey);
}
template<class M>
M* CRedBlackTreeTemplate<M>::GetOnOrBefore(void* pvKey)
{
return (M*)CRedBlackTree::GetOnOrBefore(pvKey);
}
template<class M>
M* CRedBlackTreeTemplate<M>::GetOnOrAfter(void* pvKey)
{
return (M*)CRedBlackTree::GetOnOrAfter(pvKey);
}
template<class M>
M* CRedBlackTreeTemplate<M>::GetFirst(void)
{
return (M*)CRedBlackTree::GetFirst();
}
template<class M>
M* CRedBlackTreeTemplate<M>::GetLast(void)
{
return (M*)CRedBlackTree::GetLast();
}
template<class M>
M* CRedBlackTreeTemplate<M>::GetNext(M* pvElement)
{
return (M*)CRedBlackTree::GetNext(pvElement);
}
template<class M>
M* CRedBlackTreeTemplate<M>::GetPrevious(M* pvElement)
{
return (M*)CRedBlackTree::GetPrevious(pvElement);
}
template<class M>
M* CRedBlackTreeTemplate<M>::StartIteration(SRedBlackTreeIterator* psIter)
{
return (M*)CRedBlackTree::StartIteration(psIter);
}
template<class M>
M* CRedBlackTreeTemplate<M>::StartIteration(SRedBlackTreeIterator* psIter, void* pvStartKey, void* pvEndKey)
{
return (M*)CRedBlackTree::StartIteration(psIter, pvStartKey, pvEndKey);
}
template<class M>
M* CRedBlackTreeTemplate<M>::Iterate(SRedBlackTreeIterator* psIter)
{
return (M*)CRedBlackTree::Iterate(psIter);
}
SRedBlackNode* SRedBlackNode::GetNext(void)
{
SRedBlackNode* psNode;
if (psRight)
{
return psRight->GetLeftmost();
}
psNode = this;
while (psNode->psParent && (psNode == psNode->psParent->psRight))
{
psNode = psNode->psParent;
}
return psNode->psParent;
}
SRedBlackNode* SRedBlackNode::GetPrevious(void)
{
SRedBlackNode* psNode;
if (psLeft)
{
return psLeft->GetRightmost();
}
psNode = this;
while (psNode->psParent && (psNode == psNode->psParent->psLeft))
{
psNode = psNode->psParent;
}
return psNode->psParent;
}
SRedBlackNode* SRedBlackNode::GetLeftmost(void)
{
SRedBlackNode* psNode;
psNode = this;
while (psNode->psLeft)
{
psNode = psNode->psLeft;
}
return psNode;
}
SRedBlackNode* SRedBlackNode::GetRightmost(void)
{
SRedBlackNode* psNode;
psNode = this;
while (psNode->psRight)
{
psNode = psNode->psRight;
}
return psNode;
}
static bool IsRed(SRedBlackNode* psNode)
{
return psNode && (psNode->iColour == 0);
}
static bool IsBlack(SRedBlackNode* psNode)
{
return !IsRed(psNode);
}
void CRedBlackTree::Init(size iElementSize, size iKeyOffset, DataCompare fCompare)
{
mcNodes.Init(sizeof(SRedBlackNode) + iElementSize, 8);
mpsRoot = 0L;
mfCompare = fCompare;
miKeyOffset = iKeyOffset;
miElementSize = iElementSize;
miNumElements = 0;
}
void CRedBlackTree::Kill(void)
{
mcNodes.Kill();
mpsRoot = 0L;
miNumElements = 0;
}
void* CRedBlackTree::Add(void* pvElement)
{
SRedBlackNode* psNode;
SRedBlackNode* psParent;
void* pvKey;
int iCompare;
pvKey = RemapSinglePointer(pvElement, miKeyOffset);
psParent = 0L;
iCompare = 0;
psNode = mpsRoot;
while (psNode)
{
iCompare = mfCompare(pvKey, GetKey(psNode));
if (iCompare == 0)
{
return 0L;
}
psParent = psNode;
if (iCompare < 0)
{
psNode = psNode->psLeft;
}
else
{
psNode = psNode->psRight;
}
}
psNode = (SRedBlackNode*)mcNodes.Add();
psNode->psParent = psParent;
psNode->psLeft = 0L;
psNode->psRight = 0L;
memcpy(GetData(psNode), pvElement, miElementSize);
if (psParent == 0L)
{
mpsRoot = psNode;
}
else if (iCompare < 0)
{
psParent->psLeft = psNode;
}
else
{
psParent->psRight = psNode;
}
miNumElements++;
FixAfterAdd(psNode);
return GetData(psNode);
}
void* CRedBlackTree::Put(void* pvElement)
{
SRedBlackNode* psNode;
psNode = FindNode(RemapSinglePointer(pvElement, miKeyOffset));
if (psNode)
{
memcpy(GetData(psNode), pvElement, miElementSize);
return GetData(psNode);
}
return Add(pvElement);
}
void* CRedBlackTree::Get(void* pvKey)
{
return GetData(FindNode(pvKey));
}
void* CRedBlackTree::GetOnOrBefore(void* pvKey)
{
return GetData(FindNodeOnOrBefore(pvKey));
}
void* CRedBlackTree::GetOnOrAfter(void* pvKey)
{
return GetData(FindNodeOnOrAfter(pvKey));
}
void* CRedBlackTree::GetFirst(void)
{
if (mpsRoot)
{
return GetData(mpsRoot->GetLeftmost());
}
return 0L;
}
void* CRedBlackTree::GetLast(void)
{
if (mpsRoot)
{
return GetData(mpsRoot->GetRightmost());
}
return 0L;
}
void* CRedBlackTree::GetNext(void* pvElement)
{
return GetData(GetNode(pvElement)->GetNext());
}
void* CRedBlackTree::GetPrevious(void* pvElement)
{
return GetData(GetNode(pvElement)->GetPrevious());
}
bool CRedBlackTree::Contains(void* pvKey)
{
return FindNode(pvKey) != 0L;
}
bool CRedBlackTree::Remove(void* pvKey)
{
SRedBlackNode* psNode;
psNode = FindNode(pvKey);
if (psNode)
{
RemoveNode(psNode);
return true;
}
return false;
}
void CRedBlackTree::RemoveElement(void* pvElement)
{
RemoveNode(GetNode(pvElement));
}
void CRedBlackTree::RemoveAll(void)
{
mcNodes.Kill();
mcNodes.Init(sizeof(SRedBlackNode) + miElementSize, 8);
mpsRoot = 0L;
miNumElements = 0;
}
size CRedBlackTree::NumElements(void)
{
return miNumElements;
}
bool CRedBlackTree::IsEmpty(void)
{
return miNumElements == 0;
}
void* CRedBlackTree::StartIteration(SRedBlackTreeIterator* psIter)
{
if (mpsRoot)
{
psIter->psCurrent = mpsRoot->GetLeftmost();
psIter->psStop = mpsRoot->GetRightmost();
}
else
{
psIter->psCurrent = 0L;
psIter->psStop = 0L;
}
return GetData(psIter->psCurrent);
}
void* CRedBlackTree::StartIteration(SRedBlackTreeIterator* psIter, void* pvStartKey, void* pvEndKey)
{
SRedBlackNode* psFirst;
SRedBlackNode* psLast;
psIter->psCurrent = 0L;
psIter->psStop = 0L;
if (mpsRoot == 0L)
{
return 0L;
}
if (pvStartKey)
{
psFirst = FindNodeOnOrAfter(pvStartKey);
}
else
{
psFirst = mpsRoot->GetLeftmost();
}
if (pvEndKey)
{
psLast = FindNodeOnOrBefore(pvEndKey);
}
else
{
psLast = mpsRoot->GetRightmost();
}
if (psFirst && psLast && (mfCompare(GetKey(psFirst), GetKey(psLast)) <= 0))
{
psIter->psCurrent = psFirst;
psIter->psStop = psLast;
}
return GetData(psIter->psCurrent);
}
void* CRedBlackTree::Iterate(SRedBlackTreeIterator* psIter)
{
if ((psIter->psCurrent == 0L) || (psIter->psCurrent == psIter->psStop))
{
psIter->psCurrent = 0L;
psIter->psStop = 0L;
return 0L;
}
psIter->psCurrent = psIter->psCurrent->GetNext();
return GetData(psIter->psCurrent);
}
bool CRedBlackTree::IsValid(void)
{
SRedBlackNode* psNode;
SRedBlackNode* psNext;
size iCount;
if (mpsRoot)
{
if ((mpsRoot->psParent != 0L) || IsRed(mpsRoot))
{
return false;
}
psNode = mpsRoot->GetLeftmost();
psNext = psNode->GetNext();
while (psNext)
{
if (mfCompare(GetKey(psNode), GetKey(psNext)) >= 0)
{
return false;
}
psNode = psNext;
psNext = psNode->GetNext();
}
}
iCount = 0;
if (RecurseValidate(mpsRoot, &iCount) < 0)
{
return false;
}
return iCount == miNumElements;
}
SRedBlackNode* CRedBlackTree::TestGetRoot(void)
{
return mpsRoot;
}
SRedBlackNode* CRedBlackTree::FindNode(void* pvKey)
{
SRedBlackNode* psNode;
int iCompare;
psNode = mpsRoot;
while (psNode)
{
iCompare = mfCompare(pvKey, GetKey(psNode));
if (iCompare == 0)
{
return psNode;
}
else if (iCompare < 0)
{
psNode = psNode->psLeft;
}
else
{
psNode = psNode->psRight;
}
}
return 0L;
}
SRedBlackNode* CRedBlackTree::FindNodeOnOrBefore(void* pvKey)
{
SRedBlackNode* psNode;
SRedBlackNode* psSmaller;
int iCompare;
psNode = mpsRoot;
psSmaller = 0L;
while (psNode)
{
iCompare = mfCompare(pvKey, GetKey(psNode));
if (iCompare == 0)
{
return psNode;
}
else if (iCompare < 0)
{
psNode = psNode->psLeft;
}
else
{
psSmaller = psNode;
psNode = psNode->psRight;
}
}
return psSmaller;
}
SRedBlackNode* CRedBlackTree::FindNodeOnOrAfter(void* pvKey)
{
SRedBlackNode* psNode;
SRedBlackNode* psLarger;
int iCompare;
psNode = mpsRoot;
psLarger = 0L;
while (psNode)
{
iCompare = mfCompare(pvKey, GetKey(psNode));
if (iCompare == 0)
{
return psNode;
}
else if (iCompare < 0)
{
psLarger = psNode;
psNode = psNode->psLeft;
}
else
{
psNode = psNode->psRight;
}
}
return psLarger;
}
void* CRedBlackTree::GetKey(SRedBlackNode* psNode)
{
return RemapSinglePointer(psNode, sizeof(SRedBlackNode) + miKeyOffset);
}
void* CRedBlackTree::GetData(SRedBlackNode* psNode)
{
return HeaderGetData<SRedBlackNode, void>(psNode);
}
SRedBlackNode* CRedBlackTree::GetNode(void* pvElement)
{
return DataGetHeader<SRedBlackNode, void>(pvElement);
}
void CRedBlackTree::FixAfterAdd(SRedBlackNode* psNode)
{
if (psNode->psParent == 0L)
{
psNode->iColour = 1;
}
else
{
psNode->iColour = 0;
if (IsRed(psNode->psParent))
{
FixDoubleRed(psNode);
}
}
}
void CRedBlackTree::FixDoubleRed(SRedBlackNode* psChild)
{
SRedBlackNode* psParent;
SRedBlackNode* psGrandParent;
SRedBlackNode* n1;
SRedBlackNode* n2;
SRedBlackNode* n3;
SRedBlackNode* t1;
SRedBlackNode* t2;
SRedBlackNode* t3;
SRedBlackNode* t4;
psParent = psChild->psParent;
psGrandParent = psParent->psParent;
if (psGrandParent == 0L)
{
psParent->iColour = 1;
return;
}
if (psParent == psGrandParent->psLeft)
{
n3 = psGrandParent;
t4 = psGrandParent->psRight;
if (psChild == psParent->psLeft)
{
n1 = psChild;
n2 = psParent;
t1 = psChild->psLeft;
t2 = psChild->psRight;
t3 = psParent->psRight;
}
else
{
n1 = psParent;
n2 = psChild;
t1 = psParent->psLeft;
t2 = psChild->psLeft;
t3 = psChild->psRight;
}
}
else
{
n1 = psGrandParent;
t1 = psGrandParent->psLeft;
if (psChild == psParent->psLeft)
{
n2 = psChild;
n3 = psParent;
t2 = psChild->psLeft;
t3 = psChild->psRight;
t4 = psParent->psRight;
}
else
{
n2 = psParent;
n3 = psChild;
t2 = psParent->psLeft;
t3 = psChild->psLeft;
t4 = psChild->psRight;
}
}
Replace(psGrandParent, n2);
n1->psLeft = t1;
n1->psRight = t2;
n2->psLeft = n1;
n2->psRight = n3;
n3->psLeft = t3;
n3->psRight = t4;
n1->psParent = n2;
n3->psParent = n2;
if (t1) t1->psParent = n1;
if (t2) t2->psParent = n1;
if (t3) t3->psParent = n3;
if (t4) t4->psParent = n3;
n2->iColour = 0;
n1->iColour = 1;
n3->iColour = 1;
if (n2 == mpsRoot)
{
n2->iColour = 1;
}
else if (IsRed(n2->psParent))
{
FixDoubleRed(n2);
}
}
void CRedBlackTree::RemoveNode(SRedBlackNode* psNode)
{
SRedBlackNode* psSuccessor;
SRedBlackNode* psChild;
SRedBlackNode* psChildParent;
int32 iRemovedColour;
iRemovedColour = psNode->iColour;
if (psNode->psLeft == 0L)
{
psChild = psNode->psRight;
psChildParent = psNode->psParent;
Replace(psNode, psChild);
}
else if (psNode->psRight == 0L)
{
psChild = psNode->psLeft;
psChildParent = psNode->psParent;
Replace(psNode, psChild);
}
else
{
psSuccessor = psNode->psRight->GetLeftmost();
iRemovedColour = psSuccessor->iColour;
psChild = psSuccessor->psRight;
if (psSuccessor->psParent == psNode)
{
psChildParent = psSuccessor;
}
else
{
psChildParent = psSuccessor->psParent;
Replace(psSuccessor, psChild);
psSuccessor->psRight = psNode->psRight;
psSuccessor->psRight->psParent = psSuccessor;
}
Replace(psNode, psSuccessor);
psSuccessor->psLeft = psNode->psLeft;
psSuccessor->psLeft->psParent = psSuccessor;
psSuccessor->iColour = psNode->iColour;
}
if (iRemovedColour == 1)
{
FixAfterRemove(psChild, psChildParent);
}
mcNodes.Remove(psNode);
miNumElements--;
}
void CRedBlackTree::FixAfterRemove(SRedBlackNode* psNode, SRedBlackNode* psParent)
{
SRedBlackNode* psSibling;
while ((psNode != mpsRoot) && IsBlack(psNode))
{
if (psNode == psParent->psLeft)
{
psSibling = psParent->psRight;
if (IsRed(psSibling))
{
psSibling->iColour = 1;
psParent->iColour = 0;
RotateLeft(psParent);
psSibling = psParent->psRight;
}
if (IsBlack(psSibling->psLeft) && IsBlack(psSibling->psRight))
{
psSibling->iColour = 0;
psNode = psParent;
psParent = psNode->psParent;
}
else
{
if (IsBlack(psSibling->psRight))
{
psSibling->psLeft->iColour = 1;
psSibling->iColour = 0;
RotateRight(psSibling);
psSibling = psParent->psRight;
}
psSibling->iColour = psParent->iColour;
psParent->iColour = 1;
psSibling->psRight->iColour = 1;
RotateLeft(psParent);
psNode = mpsRoot;
}
}
else
{
psSibling = psParent->psLeft;
if (IsRed(psSibling))
{
psSibling->iColour = 1;
psParent->iColour = 0;
RotateRight(psParent);
psSibling = psParent->psLeft;
}
if (IsBlack(psSibling->psLeft) && IsBlack(psSibling->psRight))
{
psSibling->iColour = 0;
psNode = psParent;
psParent = psNode->psParent;
}
else
{
if (IsBlack(psSibling->psLeft))
{
psSibling->psRight->iColour = 1;
psSibling->iColour = 0;
RotateLeft(psSibling);
psSibling = psParent->psLeft;
}
psSibling->iColour = psParent->iColour;
psParent->iColour = 1;
psSibling->psLeft->iColour = 1;
RotateRight(psParent);
psNode = mpsRoot;
}
}
}
if (psNode)
{
psNode->iColour = 1;
}
}
void CRedBlackTree::Replace(SRedBlackNode* psNode, SRedBlackNode* psReplacement)
{
if (psNode->psParent == 0L)
{
mpsRoot = psReplacement;
}
else if (psNode == psNode->psParent->psLeft)
{
psNode->psParent->psLeft = psReplacement;
}
else
{
psNode->psParent->psRight = psReplacement;
}
if (psReplacement)
{
psReplacement->psParent = psNode->psParent;
}
}
void CRedBlackTree::RotateLeft(SRedBlackNode* psNode)
{
SRedBlackNode* psRight;
psRight = psNode->psRight;
psNode->psRight = psRight->psLeft;
if (psRight->psLeft)
{
psRight->psLeft->psParent = psNode;
}
Replace(psNode, psRight);
psRight->psLeft = psNode;
psNode->psParent = psRight;
}
void CRedBlackTree::RotateRight(SRedBlackNode* psNode)
{
SRedBlackNode* psLeft;
psLeft = psNode->psLeft;
psNode->psLeft = psLeft->psRight;
if (psLeft->psRight)
{
psLeft->psRight->psParent = psNode;
}
Replace(psNode, psLeft);
psLeft->psRight = psNode;
psNode->psParent = psLeft;
}
int CRedBlackTree::RecurseValidate(SRedBlackNode* psNode, size* piCount)
{
int iLeftHeight;
int iRightHeight;
if (psNode == 0L)
{
return 1;
}
(*piCount)++;
if ((psNode->iColour != 0) && (psNode->iColour != 1))
{
return -1;
}
if (psNode->psLeft && (psNode->psLeft->psParent != psNode))
{
return -1;
}
if (psNode->psRight && (psNode->psRight->psParent != psNode))
{
return -1;
}
if (IsRed(psNode) && (IsRed(psNode->psLeft) || IsRed(psNode->psRight)))
{
return -1;
}
iLeftHeight = RecurseValidate(psNode->psLeft, piCount);
iRightHeight = RecurseValidate(psNode->psRight, piCount);
if ((iLeftHeight < 0) || (iLeftHeight != iRightHeight))
{
return -1;
}
if (psNode->iColour == 1)
{
return iLeftHeight + 1;
}
return iLeftHeight;
}
