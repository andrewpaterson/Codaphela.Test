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
struct SLogConfig
{
bool bEnabled;
bool bDebugOutput;
bool bBreakOnError;
bool bBreakOnWarning;
};
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
size IncrementLogToStringCount(void);
char* CharToString(char c);
char* CharToString(uint8 c);
char* CharToString(char16 c);
char* ByteToString(int8 i, uint16 iBase = 10);
char* ByteToString(uint8 i, uint16 iBase = 10);
char* ShortToString(int16 i, uint16 iBase = 10);
char* ShortToString(uint16 i, uint16 iBase = 10);
char* IntToString(int32 i, uint16 iBase = 10);
char* IntToString(uint32 i, uint16 iBase = 10);
char* LongToString(int64 lli, uint16 iBase = 10);
char* LongToString(uint64 ulli, uint16 iBase = 10);
char* FloatToString(float f, uint16 iDecimals = -1);
char* DoubleToString(double d, uint16 iDecimals = -1);
char* SizeToString(size i, uint16 iBase = 10);
char* SIntToString(int i, uint16 iBase = 10);
char* SIntToString(uint i, uint16 iBase = 10);
char* PointerToString(void* pv);
char* MethodToString(const char* szFile, size iLine, const char* szFunction);
char* IntToFlags(uint32 iInt);
char* ShortToFlags(uint16 siShort);
char* StringToString(const char* sz);
const char* StringToString(const char* szStart, const char* szLastCharInclusive);
char* BoolToString(bool b);
extern thread_local char gaszLogToStringScratchPad[32][512];
extern thread_local size giLogToStringCount;
typedef int (*DataCompare)(const void* pvLeft, const void* pvRight);
int ComparePtr(const void* arg1, const void* arg2);
int ComparePtrPtr(const void* arg1, const void* arg2);
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
struct SArrayTemplateHeader
{
size miElementSize;
size miUsedElements;
size miChunkSize;
bool Write(CFileWriter* pcFileWriter);
bool Read(CFileReader* pcFileReader);
};
class CRandom;
class CArrayBlock : public CMalloc, protected SArrayTemplateHeader
{
protected:
size miNumElements;
void* mpvArray;
public:
void _Init(void);
void Init(size iElementSize);
void Init(CMallocator* pcMalloc, size iElementSize);
void Init(CMallocator* pcMalloc, size iElementSize, size iChunkSize);
void Init(CMallocator* pcMalloc, size iElementSize, void* pvData, size uiNumData);
void ReInit(void);
void Finalise(void);
void Fake(size iElementSize, void* pvData, size iNum, size iChunkSize = 1);
void Kill(void);
void SetAllocateSize(size iSize);
void FakeSetUsedElements(size iUsedElements);
size NumElements(void);
bool IsEmpty(void);
bool IsNotEmpty(void);
size AllocatedElements(void);
size ElementSize(void);
void* Add(void);
void* Add(void* pvData);
void* AddGetIndex(size* piIndex);
size AddExistingGetIndex(void* pvData);
size AddIfUnique(void* pvData);
size AddIfUniqueKey(void* pvData, size iKeyOffset, size iKeySize);
void Copy(CArrayBlock* pcOtherArray);
void* Get(size iIndex);
void* SafeGet(size iIndex);
size GetAdjustedIndex(size iIndex);
void* GetData(void);
void GetHeader(SArrayTemplateHeader* psHeader);
size GetIndex(void* pvData);
void* Tail(void);
void* InsertArrayAfterEnd(CArrayBlock* pcOtherArray);
void* InsertArrayAt(CArrayBlock* pcOtherArray, size iIndex);
void* InsertArrayBeforeStart(CArrayBlock* pcOtherArray);
void* InsertAt(size iIndex);
void* InsertAt(void* pvData, size iIndex);
void* InsertBlockAfterEnd(void* paElements, size iLength);
void* InsertBlockAt(void* paElements, size iIndex, size iLength);
void* InsertBlockBeforeStart(void* paElements, size iLength);
size InsertIntoSorted(DataCompare fCompare, void* pvData, bool bOverwriteExisting);
void* InsertNumAt(size iNumElements, size iIndex);
void InsertBatch(size iFirstIndex, size iNumInBatch, size iNumBatches, size iStrideToNextBatch);
bool Pop(void* pvDest);
bool Pop(void);
void Push(void* pvData);
void* Push(void);
void* PushCopy(void);
bool PopFirst(void* pvData);
bool PopFirst(void);
size AddNum(size iNumElements);
size RemoveNum(size iNumElements);
void* GrowToAtLeastNumElements(size iNumElements, bool bClear = false, uint8 iClear = 0);
size Resize(size iNumElements);
void Sort(DataCompare fCompare);
void BubbleSort(DataCompare fCompare);
void QuickSort(DataCompare fCompare);
void TimSort(DataCompare fCompare);
bool IsSorted(DataCompare fCompare);
void Reverse(void);
void Shuffle(CRandom* pcRandom = 0L);
bool Contains(void* pvData);
bool Equals(CArrayBlock* pcOtherArray);
size Find(void* pvData);
bool FindInSorted(void* pvData, DataCompare fCompare, size* piIndex);
size FindWithIntKey(int iKey);
size FindWithIntKey(int iKey, size iKeyOffset);
size FindWithKey(void* pvData, size iKeyOffset, size iKeySize);
void RemoveAt(size iIndex, bool bPreserveOrder = true);
void RemoveAt(size* paiIndex, size iNumElements, bool bPreserveOrder = true);
void RemoveRange(size iStartIndex, size iEndIndexExclusive, bool bPreserveOrder = true);
bool RemoveTail(void);
bool RemoveFirst(void);
void RemoveBatch(size iFirstIndex, size iNumInBatch, size iNumBatches, size iStrideToNextBatch);
void RemoveAll(void);
bool Remove(void* pvData, bool bPreserveOrder = true);
size RemoveArray(CArrayBlock* pcOtherArray, bool bPreserveOrder = true);
size RemoveArrayFromSorted(CArrayBlock* pcOtherArray, DataCompare fCompare);
void Set(size iIndex, void* pvData);
bool SafeSet(size iIndex, void* pvData);
void Swap(size iIndex1, size iIndex2);
void Zero(void);
void One(void);
size ByteSize(void);
size ChunkSize(void);
size SetUsedElements(size iNumElements);
size RemoveAtNoDeallocate(size iIndex);
bool SetChunkSize(size iChunkSize);
bool Write(CFileWriter* pcFileWriter);
bool Read(CFileReader* pcFileReader);
bool WriteAllocatorAndHeader(CFileWriter* pcFileWriter);
bool WriteHeader(CFileWriter* pcFileWriter);
bool WriteHeader(CFileWriter* pcFileWriter, size uiFileElementSize);
bool ReadAllocatorAndHeader(CFileReader* pcFileReader);
bool ReadHeader(CFileReader* pcFileReader, CMallocator* pcMalloc);
bool ReadHeader(CFileReader* pcFileReader, CMallocator* pcMalloc, size uiFileElementSize, size uiElementSize);
protected:
bool BinarySearch(void* pvData, size iLeft, size iRight, DataCompare fCompare, size* piIndex);
void* CopyArrayInto(CArrayBlock* pcOtherArray, size iIndex);
void* CopyBlockInto(void* paElements, size iLength, size iIndex);
void PrivateRemoveAt(size iIndex, bool bPreserveOrder, size iDataSize);
void PrivateRemoveRange(size iStartIndex, size iEndIndexExclusive, bool bPreserveOrder, size iDataSize);
size RemoveAtNoDeallocate(size iIndex, bool bPreserveOrder, size iDataSize);
void SetArraySize(size iNumElements);
};
struct SArrayLargeTemplateHeader
{
lsize miElementSize;
lsize miUsedElements;
lsize miChunkSize;
bool Write(CFileWriter* pcFileWriter);
bool Read(CFileReader* pcFileReader);
};
class CRandom;
class CArrayLargeBlock : public CMalloc, protected SArrayLargeTemplateHeader
{
protected:
lsize miNumElements;
void* mpvArray;
public:
void _Init(void);
void Init(lsize iElementSize);
void Init(CMallocator* pcMalloc, lsize iElementSize);
void Init(CMallocator* pcMalloc, lsize iElementSize, lsize iChunkSize);
void Init(CMallocator* pcMalloc, lsize iElementSize, void* pvData, lsize uiNumData);
void ReInit(void);
void Finalise(void);
void Fake(lsize iElementSize, void* pvData, lsize iNum, lsize iChunkSize = 1);
void Kill(void);
void SetAllocateSize(lsize iSize);
void FakeSetUsedElements(lsize iUsedElements);
lsize NumElements(void);
bool IsEmpty(void);
bool IsNotEmpty(void);
lsize AllocatedElements(void);
lsize ElementSize(void);
void* Add(void);
void* Add(void* pvData);
void* AddGetIndex(lsize* piIndex);
lsize AddExistingGetIndex(void* pvData);
lsize AddIfUnique(void* pvData);
lsize AddIfUniqueKey(void* pvData, lsize iKeyOffset, lsize iKeySize);
void Copy(CArrayLargeBlock* pcOtherArray);
void* Get(lsize iIndex);
void* SafeGet(lsize iIndex);
lsize GetAdjustedIndex(lsize iIndex);
void* GetData(void);
void GetHeader(SArrayLargeTemplateHeader* psHeader);
lsize GetIndex(void* pvData);
void* Tail(void);
void* InsertArrayAfterEnd(CArrayLargeBlock* pcOtherArray);
void* InsertArrayAt(CArrayLargeBlock* pcOtherArray, lsize iIndex);
void* InsertArrayBeforeStart(CArrayLargeBlock* pcOtherArray);
void* InsertAt(lsize iIndex);
void* InsertAt(void* pvData, lsize iIndex);
void* InsertBlockAfterEnd(void* paElements, lsize iLength);
void* InsertBlockAt(void* paElements, lsize iIndex, lsize iLength);
void* InsertBlockBeforeStart(void* paElements, lsize iLength);
lsize InsertIntoSorted(DataCompare fCompare, void* pvData, bool bOverwriteExisting);
void* InsertNumAt(lsize iNumElements, lsize iIndex);
void InsertBatch(lsize iFirstIndex, lsize iNumInBatch, lsize iNumBatches, lsize iStrideToNextBatch);
bool Pop(void* pvDest);
bool Pop(void);
void Push(void* pvData);
void* Push(void);
void* PushCopy(void);
bool PopFirst(void* pvData);
bool PopFirst(void);
lsize AddNum(lsize iNumElements);
lsize RemoveNum(lsize iNumElements);
void* GrowToAtLeastNumElements(lsize iNumElements, bool bClear = false, uint8 iClear = 0);
lsize Resize(lsize iNumElements);
void Sort(DataCompare fCompare);
void BubbleSort(DataCompare fCompare);
void QuickSort(DataCompare fCompare);
void TimSort(DataCompare fCompare);
bool IsSorted(DataCompare fCompare);
void Reverse(void);
void Shuffle(CRandom* pcRandom = 0L);
bool Contains(void* pvData);
bool Equals(CArrayLargeBlock* pcOtherArray);
lsize Find(void* pvData);
bool FindInSorted(void* pvData, DataCompare fCompare, lsize* piIndex);
lsize FindWithIntKey(int iKey);
lsize FindWithIntKey(int iKey, lsize iKeyOffset);
lsize FindWithKey(void* pvData, lsize iKeyOffset, lsize iKeySize);
void RemoveAt(lsize iIndex, bool bPreserveOrder = true);
void RemoveAt(lsize* paiIndex, lsize iNumElements, bool bPreserveOrder = true);
void RemoveRange(lsize iStartIndex, lsize iEndIndexExclusive, bool bPreserveOrder = true);
bool RemoveTail(void);
bool RemoveFirst(void);
void RemoveBatch(lsize iFirstIndex, lsize iNumInBatch, lsize iNumBatches, lsize iStrideToNextBatch);
void RemoveAll(void);
bool Remove(void* pvData, bool bPreserveOrder = true);
lsize RemoveArray(CArrayLargeBlock* pcOtherArray, bool bPreserveOrder = true);
lsize RemoveArrayFromSorted(CArrayLargeBlock* pcOtherArray, DataCompare fCompare);
void Set(lsize iIndex, void* pvData);
bool SafeSet(lsize iIndex, void* pvData);
void Swap(lsize iIndex1, lsize iIndex2);
void Zero(void);
void One(void);
lsize ByteSize(void);
lsize ChunkSize(void);
lsize SetUsedElements(lsize iNumElements);
lsize RemoveAtNoDeallocate(lsize iIndex);
bool SetChunkSize(lsize iChunkSize);
bool Write(CFileWriter* pcFileWriter);
bool Read(CFileReader* pcFileReader);
bool WriteAllocatorAndHeader(CFileWriter* pcFileWriter);
bool WriteHeader(CFileWriter* pcFileWriter);
bool WriteHeader(CFileWriter* pcFileWriter, lsize uiFileElementSize);
bool ReadAllocatorAndHeader(CFileReader* pcFileReader);
bool ReadHeader(CFileReader* pcFileReader, CMallocator* pcMalloc);
bool ReadHeader(CFileReader* pcFileReader, CMallocator* pcMalloc, lsize uiFileElementSize, lsize uiElementSize);
protected:
bool BinarySearch(void* pvData, lsize iLeft, lsize iRight, DataCompare fCompare, lsize* piIndex);
void* CopyArrayInto(CArrayLargeBlock* pcOtherArray, lsize iIndex);
void* CopyBlockInto(void* paElements, lsize iLength, lsize iIndex);
void PrivateRemoveAt(lsize iIndex, bool bPreserveOrder, lsize iDataSize);
void PrivateRemoveRange(lsize iStartIndex, lsize iEndIndexExclusive, bool bPreserveOrder, lsize iDataSize);
lsize RemoveAtNoDeallocate(lsize iIndex, bool bPreserveOrder, lsize iDataSize);
void SetArraySize(lsize iNumElements);
};
template<class M>
class CArrayTemplate : public CArrayBlock, protected CPostMalloc<M>
{
public:
void Init(void);
void Init(CMallocator* pcMalloc);
void Init(CMallocator* pcMalloc, size iChunkSize);
void Init(CMallocator* pcMalloc, M* pvData, size uiNumData);
void Fake(M* pvData, size iNum, size iChunkSize = 1);
void Kill(void);
M* Add(void);
M* Add(M* pvData);
M* AddGetIndex(size* piIndex);
size AddIfUnique(M* pvData);
size AddIfUniqueKey(M* pvData, size iKeyOffset, size iKeySize);
void Copy(CArrayTemplate<M>* pcOtherArray);
M* Get(size iIndex);
M* SafeGet(size iIndex);
M* GetData(void);
size GetIndex(M* pvData);
M* Tail(void);
M& operator[](size iIndex);
M* InsertArrayAfterEnd(CArrayTemplate<M>* pcOtherArray);
M* InsertArrayAt(CArrayTemplate<M>* pcOtherArray, size iIndex);
M* InsertArrayBeforeStart(CArrayTemplate<M>* pcOtherArray);
M* InsertAt(size iIndex);
M* InsertAt(M* pvData, size iIndex);
M* InsertBlockAfterEnd(M* paElements, size iLength);
M* InsertBlockAt(M* paElements, size iLength, size iIndex);
M* InsertBlockBeforeStart(M* paElements, size iLength);
size InsertIntoSorted(DataCompare fCompare, M* pvData, bool bOverwriteExisting);
M* InsertNumAt(size iNumElements, size iIndex);
size RemoveArray(CArrayTemplate<M>* pcOtherArray, bool bPreserveOrder = true);
size RemoveArrayFromSorted(CArrayTemplate<M>* pcOtherArray, DataCompare fCompare);
bool Pop(M* pvData);
bool Pop(void);
void Push(M* pvData);
M* Push(void);
M* PushCopy(void);
bool Contains(M* pvData);
bool Equals(CArrayTemplate<M>* pcOtherArray);
size Find(M* pvData);
bool FindInSorted(M* pvData, DataCompare fCompare, size* piIndex);
size FindWithKey(M* pvData, size iKeyOffset, size iKeySize);
void Set(size iIndex, M* pvData);
bool SafeSet(size iIndex, M* pvData);
};
template<class M> void CArrayTemplate<M>::Init(void) { CArrayBlock::Init(sizeof(M)); }
template<class M> void CArrayTemplate<M>::Init(CMallocator* pcMalloc) { CArrayBlock::Init(pcMalloc, sizeof(M)); }
template<class M> void CArrayTemplate<M>::Init(CMallocator* pcMalloc, size iChunkSize) { CArrayBlock::Init(pcMalloc, sizeof(M), iChunkSize); }
template<class M> void CArrayTemplate<M>::Init(CMallocator* pcMalloc, M* pvData, size uiNumData) { CArrayBlock::Init(pcMalloc, sizeof(M), pvData, uiNumData); }
template<class M> void CArrayTemplate<M>::Kill(void) { CArrayBlock::Kill(); }
template<class M> M* CArrayTemplate<M>::SafeGet(size iIndex) { return (M*)CArrayBlock::SafeGet(iIndex); }
template<class M> bool CArrayTemplate<M>::SafeSet(size iIndex, M* pvData) { return CArrayBlock::SafeSet(iIndex, pvData); }
template<class M> M* CArrayTemplate<M>::Add(void) { return this->PostMalloc((M*)CArrayBlock::Add()); }
template<class M> M* CArrayTemplate<M>::AddGetIndex(size* piIndex) { return this->PostMalloc((M*)CArrayBlock::AddGetIndex(piIndex)); }
template<class M> M* CArrayTemplate<M>::Add(M* pvData) { return (M*)CArrayBlock::Add(pvData); }
template<class M> void CArrayTemplate<M>::Set(size iIndex, M* pvData) { return CArrayBlock::Set(iIndex, pvData); }
template<class M> M* CArrayTemplate<M>::InsertAt(size iIndex) { return this->PostMalloc((M*)CArrayBlock::InsertAt(iIndex)); }
template<class M> M* CArrayTemplate<M>::InsertAt(M* pvData, size iIndex) { return (M*)CArrayBlock::InsertAt(pvData, iIndex); }
template<class M> void CArrayTemplate<M>::Copy(CArrayTemplate* pcOtherArray) { CArrayBlock::Copy(pcOtherArray); }
template<class M>
void CArrayTemplate<M>::Push(M* pvData)
{
CArrayBlock::Push(pvData);
}
template<class M>
M* CArrayTemplate<M>::Push(void)
{
return Add();
}
template<class M>
M* CArrayTemplate<M>::PushCopy(void)
{
return (M*)CArrayBlock::PushCopy();
}
template<class M>
bool CArrayTemplate<M>::Pop(M* pvData)
{
return CArrayBlock::Pop(pvData);
}
template<class M>
bool CArrayTemplate<M>::Pop(void)
{
return CArrayBlock::Pop();
}
template<class M>
M* CArrayTemplate<M>::Tail(void)
{
return (M*)CArrayBlock::Tail();
}
template<class M>
size CArrayTemplate<M>::AddIfUnique(M* pvData)
{
return CArrayBlock::AddIfUnique(pvData);
}
template<class M>
size CArrayTemplate<M>::Find(M* pvData)
{
return CArrayBlock::Find(pvData);
}
template<class M>
bool CArrayTemplate<M>::Contains(M* pvData)
{
return CArrayBlock::Contains(pvData);
}
template<class M>
size CArrayTemplate<M>::AddIfUniqueKey(M* pvData, size iKeyOffset, size iKeySize)
{
return CArrayBlock::AddIfUniqueKey(pvData, iKeyOffset, iKeySize);
}
template<class M>
size CArrayTemplate<M>::FindWithKey(M* pvData, size iKeyOffset, size iKeySize)
{
return CArrayBlock::FindWithKey(pvData, iKeyOffset, iKeySize);
}
template<class M>
bool CArrayTemplate<M>::Equals(CArrayTemplate<M>* pcOtherArray)
{
return CArrayBlock::Equals(pcOtherArray);
}
template<class M>
size CArrayTemplate<M>::InsertIntoSorted(DataCompare fCompare, M* pvData, bool bOverwriteExisting)
{
return CArrayBlock::InsertIntoSorted(fCompare, pvData, bOverwriteExisting);
}
template<class M>
bool CArrayTemplate<M>::FindInSorted(M* pvData, DataCompare fCompare, size* piIndex)
{
return CArrayBlock::FindInSorted(pvData, fCompare, piIndex);
}
template<class M>
M* CArrayTemplate<M>::InsertArrayAfterEnd(CArrayTemplate<M>* pcOtherArray)
{
return (M*)CArrayBlock::InsertArrayAfterEnd(pcOtherArray);
}
template<class M>
M* CArrayTemplate<M>::InsertArrayBeforeStart(CArrayTemplate<M>* pcOtherArray)
{
return (M*)CArrayBlock::InsertArrayBeforeStart(pcOtherArray);
}
template<class M>
M* CArrayTemplate<M>::InsertArrayAt(CArrayTemplate<M>* pcOtherArray, size iIndex)
{
return (M*)CArrayBlock::InsertArrayAt(pcOtherArray, iIndex);
}
template<class M>
M* CArrayTemplate<M>::InsertNumAt(size iNumElements, size iIndex)
{
return this->PostMalloc((M*)CArrayBlock::InsertNumAt(iNumElements, iIndex), iNumElements, miElementSize);
}
template<class M>
M* CArrayTemplate<M>::InsertBlockAfterEnd(M* paElements, size iLength)
{
return (M*)CArrayBlock::InsertBlockAfterEnd(paElements, iLength);
}
template<class M>
M* CArrayTemplate<M>::InsertBlockBeforeStart(M* paElements, size iLength)
{
return (M*)CArrayBlock::InsertBlockBeforeStart(paElements, iLength);
}
template<class M>
M* CArrayTemplate<M>::InsertBlockAt(M* paElements, size iLength, size iIndex)
{
return (M*)CArrayBlock::InsertBlockAt(paElements, iLength, iIndex);
}
template<class M>
M* CArrayTemplate<M>::Get(size iIndex)
{
return (M*)CArrayBlock::Get(iIndex);
}
template<class M>
size CArrayTemplate<M>::GetIndex(M* pvData)
{
return CArrayBlock::GetIndex(pvData);
}
template<class M>
M* CArrayTemplate<M>::GetData(void)
{
return (M*)CArrayBlock::GetData();
}
template<class M>
void CArrayTemplate<M>::Fake(M* pvData, size iNum, size iChunkSize)
{
CArrayBlock::Fake(sizeof(M), pvData, iNum, iChunkSize);
}
template<class M>
M& CArrayTemplate<M>::operator[](size iIndex)
{
return ((M*)this->mpvArray)[iIndex];
}
template<class M>
size CArrayTemplate<M>::RemoveArray(CArrayTemplate<M>* pcOtherArray, bool bPreserveOrder)
{
return CArrayBlock::RemoveArray(pcOtherArray, bPreserveOrder);
}
template<class M>
size CArrayTemplate<M>::RemoveArrayFromSorted(CArrayTemplate<M>* pcOtherArray, DataCompare fCompare)
{
return CArrayBlock::RemoveArrayFromSorted(pcOtherArray, fCompare);
}
template<class M>
class CArrayLargeTemplate : public CArrayLargeBlock, protected CPostMalloc<M>
{
public:
void Init(void);
void Init(CMallocator* pcMalloc);
void Init(CMallocator* pcMalloc, lsize iChunkSize);
void Init(CMallocator* pcMalloc, M* pvData, lsize uiNumData);
void Fake(M* pvData, lsize iNum, lsize iChunkSize = 1);
void Kill(void);
M* Add(void);
M* Add(M* pvData);
M* AddGetIndex(lsize* piIndex);
lsize AddIfUnique(M* pvData);
lsize AddIfUniqueKey(M* pvData, lsize iKeyOffset, lsize iKeySize);
void Copy(CArrayLargeTemplate<M>* pcOtherArray);
M* Get(lsize iIndex);
M* SafeGet(lsize iIndex);
M* GetData(void);
lsize GetIndex(M* pvData);
M* Tail(void);
M& operator[](lsize iIndex);
M* InsertArrayAfterEnd(CArrayLargeTemplate<M>* pcOtherArray);
M* InsertArrayAt(CArrayLargeTemplate<M>* pcOtherArray, lsize iIndex);
M* InsertArrayBeforeStart(CArrayLargeTemplate<M>* pcOtherArray);
M* InsertAt(lsize iIndex);
M* InsertAt(M* pvData, lsize iIndex);
M* InsertBlockAfterEnd(M* paElements, lsize iLength);
M* InsertBlockAt(M* paElements, lsize iLength, lsize iIndex);
M* InsertBlockBeforeStart(M* paElements, lsize iLength);
lsize InsertIntoSorted(DataCompare fCompare, M* pvData, bool bOverwriteExisting);
M* InsertNumAt(lsize iNumElements, lsize iIndex);
lsize RemoveArray(CArrayLargeTemplate<M>* pcOtherArray, bool bPreserveOrder = true);
lsize RemoveArrayFromSorted(CArrayLargeTemplate<M>* pcOtherArray, DataCompare fCompare);
bool Pop(M* pvData);
bool Pop(void);
void Push(M* pvData);
M* Push(void);
M* PushCopy(void);
bool Contains(M* pvData);
bool Equals(CArrayLargeTemplate<M>* pcOtherArray);
lsize Find(M* pvData);
bool FindInSorted(M* pvData, DataCompare fCompare, lsize* piIndex);
lsize FindWithKey(M* pvData, lsize iKeyOffset, lsize iKeySize);
void Set(lsize iIndex, M* pvData);
bool SafeSet(lsize iIndex, M* pvData);
};
template<class M> void CArrayLargeTemplate<M>::Init(void) { CArrayLargeBlock::Init(sizeof(M)); }
template<class M> void CArrayLargeTemplate<M>::Init(CMallocator* pcMalloc) { CArrayLargeBlock::Init(pcMalloc, sizeof(M)); }
template<class M> void CArrayLargeTemplate<M>::Init(CMallocator* pcMalloc, lsize iChunkSize) { CArrayLargeBlock::Init(pcMalloc, sizeof(M), iChunkSize); }
template<class M> void CArrayLargeTemplate<M>::Init(CMallocator* pcMalloc, M* pvData, lsize uiNumData) { CArrayLargeBlock::Init(pcMalloc, sizeof(M), pvData, uiNumData); }
template<class M> void CArrayLargeTemplate<M>::Kill(void) { CArrayLargeBlock::Kill(); }
template<class M> M* CArrayLargeTemplate<M>::SafeGet(lsize iIndex) { return (M*)CArrayLargeBlock::SafeGet(iIndex); }
template<class M> bool CArrayLargeTemplate<M>::SafeSet(lsize iIndex, M* pvData) { return CArrayLargeBlock::SafeSet(iIndex, pvData); }
template<class M> M* CArrayLargeTemplate<M>::Add(void) { return this->PostMalloc((M*)CArrayLargeBlock::Add()); }
template<class M> M* CArrayLargeTemplate<M>::AddGetIndex(lsize* piIndex) { return this->PostMalloc((M*)CArrayLargeBlock::AddGetIndex(piIndex)); }
template<class M> M* CArrayLargeTemplate<M>::Add(M* pvData) { return (M*)CArrayLargeBlock::Add(pvData); }
template<class M> void CArrayLargeTemplate<M>::Set(lsize iIndex, M* pvData) { return CArrayLargeBlock::Set(iIndex, pvData); }
template<class M> M* CArrayLargeTemplate<M>::InsertAt(lsize iIndex) { return this->PostMalloc((M*)CArrayLargeBlock::InsertAt(iIndex)); }
template<class M> M* CArrayLargeTemplate<M>::InsertAt(M* pvData, lsize iIndex) { return (M*)CArrayLargeBlock::InsertAt(pvData, iIndex); }
template<class M> void CArrayLargeTemplate<M>::Copy(CArrayLargeTemplate* pcOtherArray) { CArrayLargeBlock::Copy(pcOtherArray); }
template<class M>
void CArrayLargeTemplate<M>::Push(M* pvData)
{
CArrayLargeBlock::Push(pvData);
}
template<class M>
M* CArrayLargeTemplate<M>::Push(void)
{
return Add();
}
template<class M>
M* CArrayLargeTemplate<M>::PushCopy(void)
{
return (M*)CArrayLargeBlock::PushCopy();
}
template<class M>
bool CArrayLargeTemplate<M>::Pop(M* pvData)
{
return CArrayLargeBlock::Pop(pvData);
}
template<class M>
bool CArrayLargeTemplate<M>::Pop(void)
{
return CArrayLargeBlock::Pop();
}
template<class M>
M* CArrayLargeTemplate<M>::Tail(void)
{
return (M*)CArrayLargeBlock::Tail();
}
template<class M>
lsize CArrayLargeTemplate<M>::AddIfUnique(M* pvData)
{
return CArrayLargeBlock::AddIfUnique(pvData);
}
template<class M>
lsize CArrayLargeTemplate<M>::Find(M* pvData)
{
return CArrayLargeBlock::Find(pvData);
}
template<class M>
bool CArrayLargeTemplate<M>::Contains(M* pvData)
{
return CArrayLargeBlock::Contains(pvData);
}
template<class M>
lsize CArrayLargeTemplate<M>::AddIfUniqueKey(M* pvData, lsize iKeyOffset, lsize iKeySize)
{
return CArrayLargeBlock::AddIfUniqueKey(pvData, iKeyOffset, iKeySize);
}
template<class M>
lsize CArrayLargeTemplate<M>::FindWithKey(M* pvData, lsize iKeyOffset, lsize iKeySize)
{
return CArrayLargeBlock::FindWithKey(pvData, iKeyOffset, iKeySize);
}
template<class M>
bool CArrayLargeTemplate<M>::Equals(CArrayLargeTemplate<M>* pcOtherArray)
{
return CArrayLargeBlock::Equals(pcOtherArray);
}
template<class M>
lsize CArrayLargeTemplate<M>::InsertIntoSorted(DataCompare fCompare, M* pvData, bool bOverwriteExisting)
{
return CArrayLargeBlock::InsertIntoSorted(fCompare, pvData, bOverwriteExisting);
}
template<class M>
bool CArrayLargeTemplate<M>::FindInSorted(M* pvData, DataCompare fCompare, lsize* piIndex)
{
return CArrayLargeBlock::FindInSorted(pvData, fCompare, piIndex);
}
template<class M>
M* CArrayLargeTemplate<M>::InsertArrayAfterEnd(CArrayLargeTemplate<M>* pcOtherArray)
{
return (M*)CArrayLargeBlock::InsertArrayAfterEnd(pcOtherArray);
}
template<class M>
M* CArrayLargeTemplate<M>::InsertArrayBeforeStart(CArrayLargeTemplate<M>* pcOtherArray)
{
return (M*)CArrayLargeBlock::InsertArrayBeforeStart(pcOtherArray);
}
template<class M>
M* CArrayLargeTemplate<M>::InsertArrayAt(CArrayLargeTemplate<M>* pcOtherArray, lsize iIndex)
{
return (M*)CArrayLargeBlock::InsertArrayAt(pcOtherArray, iIndex);
}
template<class M>
M* CArrayLargeTemplate<M>::InsertNumAt(lsize iNumElements, lsize iIndex)
{
return this->PostMalloc((M*)CArrayLargeBlock::InsertNumAt(iNumElements, iIndex), iNumElements, miElementSize);
}
template<class M>
M* CArrayLargeTemplate<M>::InsertBlockAfterEnd(M* paElements, lsize iLength)
{
return (M*)CArrayLargeBlock::InsertBlockAfterEnd(paElements, iLength);
}
template<class M>
M* CArrayLargeTemplate<M>::InsertBlockBeforeStart(M* paElements, lsize iLength)
{
return (M*)CArrayLargeBlock::InsertBlockBeforeStart(paElements, iLength);
}
template<class M>
M* CArrayLargeTemplate<M>::InsertBlockAt(M* paElements, lsize iLength, lsize iIndex)
{
return (M*)CArrayLargeBlock::InsertBlockAt(paElements, iLength, iIndex);
}
template<class M>
M* CArrayLargeTemplate<M>::Get(lsize iIndex)
{
return (M*)CArrayLargeBlock::Get(iIndex);
}
template<class M>
lsize CArrayLargeTemplate<M>::GetIndex(M* pvData)
{
return CArrayLargeBlock::GetIndex(pvData);
}
template<class M>
M* CArrayLargeTemplate<M>::GetData(void)
{
return (M*)CArrayLargeBlock::GetData();
}
template<class M>
void CArrayLargeTemplate<M>::Fake(M* pvData, lsize iNum, lsize iChunkSize)
{
CArrayLargeBlock::Fake(sizeof(M), pvData, iNum, iChunkSize);
}
template<class M>
M& CArrayLargeTemplate<M>::operator[](lsize iIndex)
{
return ((M*)this->mpvArray)[iIndex];
}
template<class M>
lsize CArrayLargeTemplate<M>::RemoveArray(CArrayLargeTemplate<M>* pcOtherArray, bool bPreserveOrder)
{
return CArrayLargeBlock::RemoveArray(pcOtherArray, bPreserveOrder);
}
template<class M>
lsize CArrayLargeTemplate<M>::RemoveArrayFromSorted(CArrayLargeTemplate<M>* pcOtherArray, DataCompare fCompare)
{
return CArrayLargeBlock::RemoveArrayFromSorted(pcOtherArray, fCompare);
}
template<class M>
class CArrayTemplatePtr : public CArrayTemplate<M*>
{
public:
void Init(void);
void Init(CMallocator* pcMalloc);
void Init(CMallocator* pcMalloc, size iChunkSize);
void Kill(void);
void Add(M* pv);
bool Get(size iIndex, M** pv);
M** Get(size iIndex);
M* GetPtr(size iIndex);
M* SafeGetPtr(size iIndex);
void SetPtr(size iIndex, M* pv);
size RemoveArray(CArrayTemplatePtr<M>* pcOtherArray, bool bPreserveOrder = true);
size RemoveArrayFromSorted(CArrayTemplatePtr<M>* pcOtherArray);
void Sort(void);
void QuickSort(void);
void TimSort(void);
void BubbleSort(void);
void Sort(DataCompare fCompare);
void BubbleSort(DataCompare fCompare);
void QuickSort(DataCompare fCompare);
void TimSort(DataCompare fCompare);
size Find(M* pv);
void Push(M* pv);
M* Pop(void);
bool ContainsVoidPtr(void* pv);
};
template<class M>
void CArrayTemplatePtr<M>::Init(void)
{
CArrayTemplate<M*>::Init();
}
template<class M>
void CArrayTemplatePtr<M>::Init(CMallocator* pcMalloc)
{
CArrayTemplate<M*>::Init(pcMalloc);
}
template<class M>
void CArrayTemplatePtr<M>::Init(CMallocator* pcMalloc, size iChunkSize)
{
CArrayTemplate<M*>::Init(pcMalloc, iChunkSize);
}
template<class M>
void CArrayTemplatePtr<M>::Kill(void)
{
CArrayTemplate<M*>::Kill();
}
template<class M>
void CArrayTemplatePtr<M>::Add(M* pv)
{
M** pvTemp;
pvTemp = CArrayTemplate<M*>::Add();
*pvTemp = pv;
}
template<class M>
bool CArrayTemplatePtr<M>::Get(size iIndex, M** pv)
{
M** pvTemp;
pvTemp = CArrayTemplate<M*>::SafeGet(iIndex);
if (pvTemp)
{
*pv = *pvTemp;
return true;
}
else
{
return false;
}
}
template<class M>
M** CArrayTemplatePtr<M>::Get(size iIndex)
{
return CArrayTemplate<M*>::Get(iIndex);
}
template<class M>
M* CArrayTemplatePtr<M>::GetPtr(size iIndex)
{
return *CArrayTemplate<M*>::Get(iIndex);
}
template<class M>
M* CArrayTemplatePtr<M>::SafeGetPtr(size iIndex)
{
M** ppv;
ppv = CArrayTemplate<M*>::SafeGet(iIndex);
if (ppv)
{
return *ppv;
}
else
{
return 0L;
}
}
template<class M>
void CArrayTemplatePtr<M>::SetPtr(size iIndex, M* pv)
{
CArrayTemplate<M*>::Set(iIndex, &pv);
}
template<class M>
void CArrayTemplatePtr<M>::Sort(void)
{
TimSort();
}
template<class M>
void CArrayTemplatePtr<M>::QuickSort(void)
{
CArrayBlock::QuickSort(&ComparePtrPtr);
}
template<class M>
void CArrayTemplatePtr<M>::TimSort(void)
{
CArrayBlock::TimSort(&ComparePtrPtr);
}
template<class M>
void CArrayTemplatePtr<M>::BubbleSort(void)
{
CArrayBlock::BubbleSort(&ComparePtrPtr);
}
template<class M>
void CArrayTemplatePtr<M>::Sort(DataCompare fCompare)
{
TimSort(fCompare);
}
template<class M>
void CArrayTemplatePtr<M>::BubbleSort(DataCompare fCompare)
{
CArrayBlock::BubbleSort(fCompare);
}
template<class M>
void CArrayTemplatePtr<M>::QuickSort(DataCompare fCompare)
{
CArrayBlock::QuickSort(fCompare);
}
template<class M>
void CArrayTemplatePtr<M>::TimSort(DataCompare fCompare)
{
CArrayBlock::TimSort(fCompare);
}
template<class M>
size CArrayTemplatePtr<M>::Find(M* pv)
{
size i;
M** pvData;
pvData = this->GetData();
for (i = 0; i < this->NumElements(); i++)
{
if (pvData[i] == pv)
{
return i;
}
}
return ((size)-1);
}
template<class M>
void CArrayTemplatePtr<M>::Push(M* pv)
{
Add(pv);
}
template<class M>
M* CArrayTemplatePtr<M>::Pop(void)
{
M* pv;
CArrayTemplate<M*>::Pop(&pv);
return pv;
}
template<class M>
bool CArrayTemplatePtr<M>::ContainsVoidPtr(void* pv)
{
size uiNumElements;
size ui;
M* pvObject;
uiNumElements = this->NumElements();
for (ui = 0; ui < uiNumElements; ui++)
{
pvObject = GetPtr(ui);
if (pvObject == pv)
{
return true;
}
}
return false;
}
template<class M>
size CArrayTemplatePtr<M>::RemoveArray(CArrayTemplatePtr<M>* pcOtherArray, bool bPreserveOrder)
{
return CArrayTemplate<M*>::RemoveArray(pcOtherArray, bPreserveOrder);
}
template<class M>
size CArrayTemplatePtr<M>::RemoveArrayFromSorted(CArrayTemplatePtr<M>* pcOtherArray)
{
return CArrayTemplate<M*>::RemoveArrayFromSorted(pcOtherArray, ComparePtrPtr);
}
enum EFileMode
{
EFM_Unknown,
EFM_Write_Create,
EFM_Read,
EFM_Read_Create,
EFM_ReadWrite,
EFM_ReadWrite_Create,
};
enum EFileSeekOrigin
{
EFSO_SET = 0,
EFSO_CURRENT = 1,
EFSO_END = 2
};
bool IsFileModeWritable(EFileMode eFileMode);
bool IsFileModeReadable(EFileMode eFileMode);
bool IsFileModeReadOnly(EFileMode eFileMode);
bool IsFileModeCreate(EFileMode eFileMode);
class CAbstractFile
{
public:
bool mbBasicFileMustFree;
public:
void Init(void);
virtual void Kill(void) =0;
virtual bool Open(EFileMode eFileMode) =0;
virtual bool Close(void) =0;
virtual lsize Read(void* pvBuffer, lsize iSize, lsize iCount) =0;
virtual bool Seek(filePos iOffset, EFileSeekOrigin iSeekOrigin) =0;
virtual lsize Write(const void* pvBuffer, lsize iSize, lsize iCount) =0;
virtual filePos Tell(void) =0;
virtual bool IsOpen(void) =0;
virtual filePos Size(void) =0;
virtual bool Truncate(filePos iSize) =0;
virtual bool Flush(void) =0;
virtual bool Delete(void) =0;
virtual const char* GetFilename(void) =0;
};
class CMutex
{
friend class CConditionVariable;
protected:
alignas(8) uint8 maMutex[48];
public:
void Init(void);
void Kill(void);
void Lock(void);
void Unlock(void);
};
typedef CArrayTemplatePtr<CAbstractFile> CArrayFile;
class CAbstractFile;
class CLogger
{
protected:
CArrayFile mapcFiles;
SLogConfig msConfig;
CAbstractFile* mpcDebugOutputFile;
CMutex mcMutex;
public:
void Init(void);
void Init(const char* szName);
void Init(CAbstractFile* pcFile, const char* szName);
void Kill(void);
void Add(const char* szText);
void Add(const char* szErrorLevel, const char* szText);
bool Error(const char* szText);
bool Error2(const char* szText, ...);
bool Warning(const char* szText);
bool Warning2(const char* szText, ...);
void Info(const char* szText);
void Info2(const char* szText, ...);
void Debug(const char* szText);
void Debug2(const char* szText, ...);
void Disable(void);
void Enable(void);
void SetBreakOnError(bool bBreakOnError);
void SetBreakOnWarning(bool bBreakOnWarning);
SLogConfig SetSilent(bool bBreakOnError = false);
void SetConfig(SLogConfig* psConfig);
void GetConfig(SLogConfig* psConfig);
void AddOutput(CAbstractFile* pcFile);
void RemoveOutput(CAbstractFile* pcFile);
void Break(void);
protected:
void Lock(void);
void Unlock(void);
};
extern CLogger gcLogger;
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
void QuickSort(DataCompare fCompare, void* pvArray, lsize uiStride, lsize uiNumElements);
void BubbleSort(DataCompare fCompare, void* pvArray, lsize uiStride, lsize iNumElements);
template<class M, int8 I>
class CArrayTemplateEmbedded : protected CPostMalloc<M>
{
protected:
using CPostMalloc<M>::PostMalloc;
uint8 miUsedElements;
uint8 muiFlags;
union
{
CArrayTemplate<M> mcArray;
M mam[I];
};
protected:
void BecomeArray(size iUsedElements);
void BecomeEmbedded(size iUsedElements);
public:
CArrayTemplateEmbedded() {}
CArrayTemplateEmbedded(CArrayTemplateEmbedded &&) {}
CArrayTemplateEmbedded(const CArrayTemplateEmbedded&) = default;
CArrayTemplateEmbedded& operator = (const CArrayTemplateEmbedded&) = default;
public:
void Init(void);
void Kill(void);
void ReInit(void);
M* Add(void);
M* Add(M* pvData);
void AddPtr(void* pv);
size ByteSize(void);
size EmbeddedSize(void);
M* Get(size iIndex);
M* GetData(void);
M* SafeGet(size iIndex);
M* Tail(void);
size GetIndex(M* pvElement);
size Find(M* pvElement);
void Set(size iIndex, M* pvData);
void SafeSet(size iIndex, M* pvData);
size AddNum(size iNumElements);
M* InsertAt(size iIndex);
M* InsertAt(M* pvData, size iIndex);
size Resize(size iNumElements);
bool IsEmpty(void);
bool IsNotEmpty(void);
bool IsEmbedded(void);
bool IsArray(void);
size NumElements(void);
bool Remove(M* pvElement, bool bPreserveOrder = true);
void RemoveAt(size iIndex, bool bPreserveOrder = true);
bool RemoveTail(void);
bool RemoveFirst(void);
template<int8 J> void Copy(CArrayTemplateEmbedded<M, J>* pcArrayTemplateEmbedded);
bool TestInternalConsistency(void);
void Zero(void);
bool Write(CFileWriter* pcFileWriter);
bool Read(CFileReader* pcFileReader);
void Swap(size iIndex1, size iIndex2);
void QuickSort(DataCompare fCompare);
void BubbleSort(DataCompare fCompare);
bool FindInSorted(M* pvData, DataCompare fCompare, size* piIndex);
bool Pop(M* pvDest);
bool Pop(void);
void Push(M* pvData);
M* Push(void);
M* PushCopy(void);
};
template<class M, int8 I>
void CArrayTemplateEmbedded<M, I>::Init(void)
{
miUsedElements = 0;
muiFlags = 0x01;
}
template<class M, int8 I>
void CArrayTemplateEmbedded<M, I>::Kill(void)
{
if (IsArray())
{
mcArray.Kill();
}
miUsedElements = 0xFF;
muiFlags = 0;
}
template<class M, int8 I>
void CArrayTemplateEmbedded<M, I>::ReInit(void)
{
uint8 uiFlags;
uiFlags = muiFlags;
Kill();
Init();
muiFlags |= (uiFlags & 0xFC);
}
template<class M, int8 I>
bool CArrayTemplateEmbedded<M, I>::IsEmbedded(void)
{
return muiFlags & 0x01;
}
template<class M, int8 I>
bool CArrayTemplateEmbedded<M, I>::IsArray(void)
{
return muiFlags & 0x02;
}
template<class M, int8 I>
void CArrayTemplateEmbedded<M, I>::BecomeArray(size iUsedElements)
{
M am[I];
memcpy(am, mam, miUsedElements * sizeof(M));
mcArray.Init();
mcArray.AddNum(iUsedElements);
memcpy(mcArray.GetData(), am, miUsedElements * sizeof(M));
miUsedElements = 0xFF;
SetFlagByte(&muiFlags, 0x02, true);
SetFlagByte(&muiFlags, 0x01, false);
}
template<class M, int8 I>
void CArrayTemplateEmbedded<M, I>::BecomeEmbedded(size iUsedElements)
{
M am[I];
memcpy(am, mcArray.GetData(), iUsedElements * sizeof(M));
mcArray.Kill();
memcpy(mam, am, iUsedElements * sizeof(M));
miUsedElements = (uint8)iUsedElements;
SetFlagByte(&muiFlags, 0x01, true);
SetFlagByte(&muiFlags, 0x02, false);
}
template<class M, int8 I>
M* CArrayTemplateEmbedded<M, I>::Add(void)
{
M* pv;
if (IsEmbedded())
{
if (miUsedElements + 1 > I)
{
BecomeArray(miUsedElements + 1);
pv = mcArray.Tail();
}
else
{
miUsedElements++;
pv = &mam[miUsedElements - 1];
}
}
else
{
pv = mcArray.Add();
}
return PostMalloc(pv);
}
template<class M, int8 I>
M* CArrayTemplateEmbedded<M, I>::Add(M* pvData)
{
M* pvAdded;
pvAdded = Add();
memcpy(pvAdded, pvData, sizeof(M));
return pvAdded;
}
template<class M, int8 I>
void CArrayTemplateEmbedded<M, I>::AddPtr(void* pv)
{
void** pvTemp;
pvTemp = (void**)Add();
*pvTemp = pv;
}
template<class M, int8 I>
size CArrayTemplateEmbedded<M, I>::ByteSize(void)
{
if (IsEmbedded())
{
(size)miUsedElements * sizeof(M);
}
else
{
return mcArray.ByteSize();
}
}
template<class M, int8 I>
size CArrayTemplateEmbedded<M, I>::EmbeddedSize(void)
{
return I;
}
template<class M, int8 I>
M* CArrayTemplateEmbedded<M, I>::Get(size iIndex)
{
if (IsEmbedded())
{
if (iIndex < miUsedElements)
{
return &mam[iIndex];
}
return 0L;
}
else
{
return mcArray.SafeGet(iIndex);
}
}
template<class M, int8 I>
M* CArrayTemplateEmbedded<M, I>::GetData(void)
{
if (IsEmbedded())
{
return mam;
}
else
{
return mcArray.GetData();
}
}
template<class M, int8 I>
void CArrayTemplateEmbedded<M, I>::Set(size iIndex, M* pvData)
{
M* pvAdded;
pvAdded = Get(iIndex);
memcpy(pvAdded, pvData, sizeof(M));
}
template<class M, int8 I>
void CArrayTemplateEmbedded<M, I>::SafeSet(size iIndex, M* pvData)
{
if (iIndex < miUsedElements)
{
Set(iIndex, pvData);
}
}
template<class M, int8 I>
size CArrayTemplateEmbedded<M, I>::GetIndex(M* pvElement)
{
size uiIndex;
size tDifference;
tDifference = (size)((ptr)pvElement - (ptr)GetData());
if (tDifference % sizeof(M) != 0)
{
return ((size)-1);
}
uiIndex = (tDifference / sizeof(M));
if (uiIndex >= NumElements())
{
return ((size)-1);
}
return uiIndex;
}
template<class M, int8 I>
size CArrayTemplateEmbedded<M, I>::Find(M* pvData)
{
M* pIndex;
size i;
size uiNumElements;
if (IsEmbedded())
{
uiNumElements = miUsedElements;
for (i = 0; i < uiNumElements; i++)
{
pIndex = &mam[i];
if (memcmp(pIndex, pvData, sizeof(M)) == 0)
{
return i;
}
}
}
else
{
return mcArray.Find(pvData);
}
return ((size)-1);
}
template<class M, int8 I>
size CArrayTemplateEmbedded<M, I>::AddNum(size iNumElements)
{
size iOldUsedElements;
if (IsEmbedded())
{
iOldUsedElements = miUsedElements;
if ((size)iOldUsedElements + iNumElements > I)
{
BecomeArray((size)iOldUsedElements + iNumElements);
return iOldUsedElements;
}
else
{
miUsedElements += (uint8)iNumElements;
return iOldUsedElements;
}
}
else
{
return mcArray.AddNum(iNumElements);
}
}
template<class M, int8 I>
size CArrayTemplateEmbedded<M, I>::Resize(size iNumElements)
{
size iOldUsedElements;
iOldUsedElements = miUsedElements;
if (IsEmbedded())
{
if (iNumElements > I)
{
BecomeArray(iNumElements);
return iOldUsedElements;
}
else
{
miUsedElements = (uint8)iNumElements;
return iOldUsedElements;
}
}
else
{
if (iNumElements <= I)
{
BecomeEmbedded(iNumElements);
return iOldUsedElements;
}
else
{
return mcArray.Resize(iNumElements);
}
}
}
template<class M, int8 I>
M* CArrayTemplateEmbedded<M, I>::InsertAt(size iIndex)
{
void* pSource;
void* pDest;
M* pv;
size iOldUsedElements;
if (IsEmbedded())
{
iOldUsedElements = miUsedElements;
if (miUsedElements + 1 > I)
{
BecomeArray(iOldUsedElements + 1);
pSource = mcArray.Get(iIndex);
pDest = RemapSinglePointer(pSource, sizeof(M));
memmove(pDest, pSource, sizeof(M) * (iOldUsedElements - iIndex));
pv = (M*)pSource;
}
else
{
miUsedElements++;
pSource = &mam[iIndex];
pDest = RemapSinglePointer(pSource, sizeof(M));
memmove(pDest, pSource, sizeof(M) * (iOldUsedElements - iIndex));
pv = (M*)pSource;
}
}
else
{
pv = mcArray.InsertAt(iIndex);
}
return PostMalloc(pv);
}
template<class M, int8 I>
M* CArrayTemplateEmbedded<M, I>::InsertAt(M* pvData, size iIndex)
{
M* pvAdded;
pvAdded = InsertAt(iIndex);
memcpy(pvAdded, pvData, sizeof(M));
return pvAdded;
}
template<class M, int8 I>
bool CArrayTemplateEmbedded<M, I>::IsEmpty(void)
{
return NumElements() == 0;
}
template<class M, int8 I>
bool CArrayTemplateEmbedded<M, I>::IsNotEmpty(void)
{
return NumElements() != 0;
}
template<class M, int8 I>
size CArrayTemplateEmbedded<M, I>::NumElements(void)
{
if (IsEmbedded())
{
return miUsedElements;
}
else if (IsArray())
{
return mcArray.NumElements();
}
else
{
return 0;
}
}
template<class M, int8 I>
bool CArrayTemplateEmbedded<M, I>::Remove(M* pvData, bool bPreserveOrder)
{
size iIndex;
iIndex = Find(pvData);
if (iIndex != ((size)-1))
{
RemoveAt(iIndex, bPreserveOrder);
return true;
}
else
{
return false;
}
}
template<class M, int8 I>
void CArrayTemplateEmbedded<M, I>::RemoveAt(size iIndex, bool bPreserveOrder)
{
void* pvSource;
void* pvDest;
size iMove;
if (IsEmbedded())
{
pvDest = Get(iIndex);
if (pvDest)
{
pvSource = RemapSinglePointer(pvDest, sizeof(M));
miUsedElements--;
iMove = (size)miUsedElements - iIndex;
if (iMove > 0)
{
memmove(pvDest, pvSource, sizeof(M) * iMove);
}
}
}
else
{
mcArray.RemoveAt(iIndex, bPreserveOrder);
if (mcArray.NumElements() <= I)
{
BecomeEmbedded(mcArray.NumElements());
}
}
}
template<class M, int8 I>
M* CArrayTemplateEmbedded<M, I>::SafeGet(size iIndex)
{
return Get(iIndex);
}
template<class M, int8 I>
template<int8 J>
void CArrayTemplateEmbedded<M, I>::Copy(CArrayTemplateEmbedded<M, J>* pcArrayTemplateEmbedded)
{
size i;
size iNumElements;
M* pvData;
iNumElements = pcArrayTemplateEmbedded->NumElements();
for (i = 0; i < iNumElements; i++)
{
pvData = pcArrayTemplateEmbedded->Get(i);
Add(pvData);
}
}
template<class M, int8 I>
bool CArrayTemplateEmbedded<M, I>::TestInternalConsistency(void)
{
if (IsEmbedded())
{
if (muiFlags & 0x02)
{
return false;
}
return miUsedElements <= I;
}
else if (IsArray())
{
if (muiFlags & 0x01)
{
return false;
}
if (miUsedElements != 0xFF)
{
return false;
}
if (sizeof(M) != mcArray.ElementSize())
{
return false;
}
return true;
}
else
{
return false;
}
}
template<class M, int8 I>
void CArrayTemplateEmbedded<M, I>::Zero(void)
{
if (IsEmbedded())
{
if (miUsedElements != 0)
{
memset(mam, 0, miUsedElements * sizeof(M));
}
}
else
{
mcArray.Zero();
}
}
template<class M, int8 I>
bool CArrayTemplateEmbedded<M, I>::Write(CFileWriter* pcFileWriter)
{
return false;
}
template<class M, int8 I>
bool CArrayTemplateEmbedded<M, I>::Read(CFileReader* pcFileReader)
{
return false;
}
template<class M, int8 I>
void CArrayTemplateEmbedded<M, I>::Swap(size iIndex1, size iIndex2)
{
M* pv1;
M* pv2;
M v;
pv1 = Get(iIndex1);
pv2 = Get(iIndex2);
v = *pv1;
*pv1 = *pv2;
*pv2 = v;
}
template<class M, int8 I>
void CArrayTemplateEmbedded<M, I>::QuickSort(DataCompare fCompare)
{
::QuickSort(fCompare, GetData(), sizeof(M), NumElements());
}
template<class M, int8 I>
void CArrayTemplateEmbedded<M, I>::BubbleSort(DataCompare fCompare)
{
::BubbleSort(fCompare, GetData(), sizeof(M), NumElements());
}
template<class M, int8 I>
bool CArrayTemplateEmbedded<M, I>::FindInSorted(M* pvData, DataCompare fCompare, size* piIndex)
{
size iLeft;
size iRight;
size iMiddle;
int iResultMiddle;
if (NumElements() == 0)
{
*piIndex = 0;
return false;
}
iLeft = 0;
iRight = NumElements() - 1;
iResultMiddle = 0;
iMiddle = 0;
while (iLeft <= iRight)
{
iMiddle = (iLeft + iRight) >> 1;
iResultMiddle = fCompare(pvData, Get(iMiddle));
if (iResultMiddle == 0)
{
*piIndex = iMiddle;
return true;
}
else if (iResultMiddle < 0)
{
if (iMiddle == 0)
{
break;
}
iRight = iMiddle - 1;
}
else
{
iLeft = iMiddle + 1;
}
}
if (iResultMiddle > 0)
{
*piIndex = (iMiddle + 1);
}
else
{
*piIndex = iMiddle;
}
return false;
}
template<class M, int8 I>
void CArrayTemplateEmbedded<M, I>::Push(M* pvData)
{
CArrayBlock::Push(pvData);
}
template<class M, int8 I>
M* CArrayTemplateEmbedded<M, I>::Push(void)
{
return Add();
}
template<class M, int8 I>
M* CArrayTemplateEmbedded<M, I>::PushCopy(void)
{
M* pvDest;
M* pvSource;
if (NumElements() > 0)
{
pvDest = Add();
pvSource = Get(miUsedElements - 2);
memcpy(pvDest, pvSource, sizeof(M));
return pvDest;
}
else
{
return 0L;
}
}
template<class M, int8 I>
bool CArrayTemplateEmbedded<M, I>::Pop(M* pvDest)
{
void* pvSource;
size iNumElements;
iNumElements = NumElements();
if (iNumElements != 0)
{
pvSource = Get(iNumElements - 1);
memcpy(pvDest, pvSource, sizeof(M));
RemoveAt(iNumElements - 1);
return true;
}
else
{
memset(pvDest, 0, sizeof(M));
return false;
}
}
template<class M, int8 I>
bool CArrayTemplateEmbedded<M, I>::Pop(void)
{
return RemoveTail();
}
template<class M, int8 I>
M* CArrayTemplateEmbedded<M, I>::Tail(void)
{
return (M*)CArrayBlock::Tail();
}
template<class M, int8 I>
bool CArrayTemplateEmbedded<M, I>::RemoveTail(void)
{
size iNumElements;
iNumElements = NumElements();
if (iNumElements != 0)
{
RemoveAt(iNumElements - 1);
return true;
}
return false;
}
template<class M, int8 I>
bool CArrayTemplateEmbedded<M, I>::RemoveFirst(void)
{
size iNumElements;
iNumElements = NumElements();
if (iNumElements != 0)
{
RemoveAt(0);
return true;
}
return false;
}
template<class M, int8 I>
class CArrayTemplateEmbeddedPtr : public CArrayTemplateEmbedded<M*, I>
{
public:
void Init(void);
void Kill(void);
void Add(M* pv);
M* GetPtr(size iIndex);
bool Get(size iIndex, M** pv);
M** Get(size iIndex);
M* HeadPtr(void);
M* TailPtr(void);
void QuickSort(void);
size Find(M* pv);
void Push(M* pv);
M* Pop(void);
};
template<class M, int8 I>
void CArrayTemplateEmbeddedPtr<M, I>::Init(void)
{
CArrayTemplateEmbedded<M*, I>::Init();
}
template<class M, int8 I>
void CArrayTemplateEmbeddedPtr<M, I>::Kill(void)
{
CArrayTemplateEmbedded<M*, I>::Kill();
}
template<class M, int8 I>
void CArrayTemplateEmbeddedPtr<M, I>::Add(M* pv)
{
M** pvTemp;
pvTemp = CArrayTemplateEmbedded<M*, I>::Add();
*pvTemp = pv;
}
template<class M, int8 I>
bool CArrayTemplateEmbeddedPtr<M, I>::Get(size iIndex, M** pv)
{
M** pvTemp;
pvTemp = CArrayTemplateEmbedded<M*, I>::SafeGet(iIndex);
if (pvTemp)
{
*pv = *pvTemp;
return true;
}
else
{
return false;
}
}
template<class M, int8 I>
M** CArrayTemplateEmbeddedPtr<M, I>::Get(size iIndex)
{
return CArrayTemplateEmbedded<M*, I>::Get(iIndex);
}
template<class M, int8 I>
M* CArrayTemplateEmbeddedPtr<M, I>::GetPtr(size iIndex)
{
return *CArrayTemplateEmbedded<M*, I>::Get(iIndex);
}
template<class M, int8 I>
M* CArrayTemplateEmbeddedPtr<M, I>::HeadPtr(void)
{
if (this->NumElements() > 0)
{
return GetPtr(0);
}
else
{
return 0L;
}
}
template<class M, int8 I>
M* CArrayTemplateEmbeddedPtr<M, I>::TailPtr(void)
{
size iNumElements;
iNumElements = this->NumElements();
if (iNumElements > 0)
{
return GetPtr(iNumElements - 1);
}
else
{
return 0L;
}
}
template<class M, int8 I>
void CArrayTemplateEmbeddedPtr<M, I>::QuickSort(void)
{
CArrayTemplateEmbedded<M*, I>::QuickSort(&ComparePtrPtr);
}
template<class M, int8 I>
size CArrayTemplateEmbeddedPtr<M, I>::Find(M* pv)
{
size i;
M** pvData;
size uiNumElements;
pvData = this->GetData();
uiNumElements = this->NumElements();
for (i = 0; i < uiNumElements; i++)
{
if (pvData[i] == pv)
{
return i;
}
}
return ((size)-1);
}
template<class M, int8 I>
void CArrayTemplateEmbeddedPtr<M, I>::Push(M* pv)
{
Add(pv);
}
template<class M, int8 I>
M* CArrayTemplateEmbeddedPtr<M, I>::Pop(void)
{
M* pv;
CArrayTemplateEmbedded<M*, I>::Pop(&pv);
return pv;
}
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
enum EStackPointerType
{
SPT_Unknown,
SPT_Pointer,
SPT_Collection
};
class CPointer;
class CCollection;
class CEmbeddedObject;
struct SStackPointer
{
EStackPointerType meType;
union
{
CPointer* pcPointer;
CCollection* pcCollection;
void* pvPointer;
} u;
};
class CStackPointer
{
protected:
CStackPointer* mpcNext;
SStackPointer msPointer;
public:
void Init(void);
void Init(CPointer* pcPointer);
void Init(CCollection* pcCollection);
void Kill(void);
void SetNext(CStackPointer* pcNext);
int NumPointers(void);
CStackPointer* FindLast(void);
CStackPointer* GetNext(void);
CStackPointer* Remove(CPointer* pcPointer, CFreeList* pcFreeList, bool* pbRemoved);
CStackPointer* Remove(CCollection* pcCollection, CFreeList* pcFreeList, bool* pbRemoved);
void RemoveAll(CFreeList* pcFreeList);
void ClearPointer(void);
CStackPointer* ClearPointerGetNext(CEmbeddedObject* pcPointedTo);
EStackPointerType GetType(void);
SStackPointer* Get(void);
protected:
CStackPointer* Remove(EStackPointerType eType, void* pvPointer, CFreeList* pcFreeList, bool* pbRemoved);
};
class CEmbeddedObject;
typedef CArrayTemplatePtr<CEmbeddedObject> CArrayEmbeddedObjectPtr;
typedef CArrayTemplateEmbeddedPtr<CEmbeddedObject, 8> CArrayEmbeddedObjectPtrE8;
class CBaseObject;
typedef CArrayTemplatePtr<CBaseObject> CArrayBaseObjectPtr;
typedef CArrayTemplateEmbeddedPtr<CBaseObject, 32> CArrayBaseObjectPtrE32;
class CPointer;
typedef CArrayTemplateEmbedded<SStackPointer, 32> CArrayStackPointerE32;
class CRemovalPointerContainer
{
protected:
CArrayBaseObjectPtr mapcKilled;
CArrayBaseObjectPtr* mpapcKilled;
public:
void Init(CArrayBaseObjectPtr* papcKilled, bool bFreeArray);
void Kill(void);
CArrayBaseObjectPtr* GetKilled(void);
};
typedef CArrayTemplateEmbedded<CRemovalPointerContainer, 4> CArrayRemovalPointerContainerE4;
class CObjectRemovalContext
{
protected:
CArrayRemovalPointerContainerE4 maapcRemovedObjects;
CArrayBaseObjectPtr mapcRemainingObjects;
CArrayBaseObjectPtr mapcKilledObjects;
public:
void Init(void);
void Kill(void);
CArrayBaseObjectPtr* Start(CArrayBaseObjectPtr* papcKilled);
CArrayBaseObjectPtr* Done(void);
void Push(CArrayBaseObjectPtr* papcKilled);
bool IsBusy(void);
void Clear(void);
};
void CObjectRemovalContext::Init(void)
{
maapcRemovedObjects.Init();
mapcRemainingObjects.Init();
mapcKilledObjects.Init();
}
void CObjectRemovalContext::Kill(void)
{
mapcKilledObjects.Kill();
mapcRemainingObjects.Kill();
if (IsBusy() || (maapcRemovedObjects.NumElements() != 0))
{
gcLogger.Error2(MethodToString("/home/r2d2/Codaphela/commonlibraries/StandardLib/ObjectsRemovalContext.cpp", 27, __PRETTY_FUNCTION__), " Killing ObjectRemovalContext whist still performing a removal.", 0L);
}
maapcRemovedObjects.Kill();
}
CArrayBaseObjectPtr* CObjectRemovalContext::Start(CArrayBaseObjectPtr* papcKilled)
{
CRemovalPointerContainer* pcContainer;
pcContainer = maapcRemovedObjects.Add();
pcContainer->Init(papcKilled, false);
return papcKilled;
}
CArrayBaseObjectPtr* CObjectRemovalContext::Done(void)
{
CArrayBaseObjectPtr* apcPreviouslyKilled;
CRemovalPointerContainer* pcContainer;
pcContainer = maapcRemovedObjects.Get(0);
apcPreviouslyKilled = pcContainer->GetKilled();
mapcKilledObjects.InsertArrayAfterEnd(apcPreviouslyKilled);
pcContainer->Kill();
maapcRemovedObjects.RemoveAt(0);
if (IsBusy())
{
pcContainer = maapcRemovedObjects.Get(0);
mapcRemainingObjects.ReInit();
mapcRemainingObjects.InsertArrayAfterEnd(pcContainer->GetKilled());
mapcRemainingObjects.Sort();
mapcRemainingObjects.RemoveArrayFromSorted(&mapcKilledObjects);
return &mapcRemainingObjects;
}
else
{
Clear();
return 0L;
}
}
void CObjectRemovalContext::Push(CArrayBaseObjectPtr* papcKilled)
{
CRemovalPointerContainer* pcContainer;
pcContainer = maapcRemovedObjects.Add();
pcContainer->Init(papcKilled, true);
}
bool CObjectRemovalContext::IsBusy(void)
{
return maapcRemovedObjects.NumElements() != 0;
}
void CObjectRemovalContext::Clear(void)
{
maapcRemovedObjects.ReInit();
mapcRemainingObjects.ReInit();
mapcKilledObjects.ReInit();
}
