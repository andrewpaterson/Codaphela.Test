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
class CMersenneTwister
{
private:
uint32 mauiState[624];
uint32 muiIndex;
void Twist(void);
public:
void Init(void);
void Init(uint32 iSeed);
void Kill(void);
uint32 Next(void);
int32 Next(int32 iMin, int32 iMaxInclusive);
};
class CRandom
{
private:
CMersenneTwister mcRNG;
public:
void Init(void);
void Init(uint32 iSeed);
void Kill(void);
int32 Next(int32 iMin, int32 iMaxInclusive);
};
void* operator new(size_t uiBytes);
void* operator new[](size_t uiBytes);
void operator delete(void* pv) noexcept;
void operator delete[](void* pv) noexcept;
inline void* operator new(size_t uiBytes, void* pv) noexcept { return pv; }
inline void* operator new[](size_t uiBytes, void* pv) noexcept { return pv; }
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
typedef int (*DataCompare)(const void* pvLeft, const void* pvRight);
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
int StringCompare(const char* ps1, const char* ps2);
int StringInsensitiveCompare(const char* ps1, const char* ps2);
char* StrIStr(char* ps1, const char* ps2);
int MemICmp(const void* pv1, const void* pv2, size iLength);
int MemCmp(const void* pv1, size iLen1, const void* pv2, size iLen2);
void MemSwp(const void* pv1, const void* pv2, size uiLength);
char* StrRev(char* szString);
char* StrRev(char* szString, size iLength);
const char* FindChar(const char* szString, char c, bool bReverse = false);
size FindCharIndex(char chr, const char* str, size index);
char* StrCpySafe(char* szDest, const char* szSource, size iDestLength, size* piSourceLength = 0L);
char* StrCatSafe(char* szDest, const char* szSource, size iDestLength, size* piSourceLength = 0L);
char* StrCpy(char* szDest, const char* szString, const char* szLastCharInclusive);
void StrCpySafeStripSurroundingSpaces(char* szDest, char* szSource, size uiMaxLength);
char* ToLower(char* szString);
char* ToUpper(char* szString);
char ToLower(char c);
char ToUpper(char c);
size StrPrintable(const char* szString);
size StrPrintable(const char* szString, size iLength);
size StrLen(const char* szString);
size StrLen(const char* szString, const char* szLastCharInclusive);
bool StrEmpty(const char* szString);
char* NullToEmpty(const char* szString);
char GetHexChar(size c4Bit);
size GetCharHex(char cHexChar);
size NumberOfDigits(size uiNumber);
char* NextString(const char* szCurrent);
char* ByteToString(char* szDest, size iDestLength, int8 iValue, uint16 iBase = 10);
char* ByteToString(char* szDest, size iDestLength, uint8 iValue, uint16 iBase = 10);
char* ShortToString(char* szDest, size iDestLength, int16 iValue, uint16 iBase = 10);
char* ShortToString(char* szDest, size iDestLength, uint16 iValue, uint16 iBase = 10);
char* IntToString(char* szDest, size iDestLength, int32 iValue, uint16 iBase = 10);
char* IntToString(char* szDest, size iDestLength, uint32 iValue, uint16 iBase = 10);
char* SizeToString(char* szDest, size iDestLength, size iValue, uint16 iBase = 10);
char* LongToString(char* szDest, size iDestLength, int64 lliValue, uint16 iBase = 10);
char* LongToString(char* szDest, size iDestLength, uint64 ulliValue, uint16 iBase = 10);
char* FlagsToString(char* szDest, size iDestLength, int8 iFlags);
char* FlagsToString(char* szDest, size iDestLength, uint8 iFlags);
char* FlagsToString(char* szDest, size iDestLength, int16 iFlags);
char* FlagsToString(char* szDest, size iDestLength, uint16 iFlags);
char* FlagsToString(char* szDest, size iDestLength, int32 iFlags);
char* FlagsToString(char* szDest, size iDestLength, uint32 iFlags);
char* CharToString(char* szDest, size iDestLength, char c);
char* CharToString(char* szDest, size iDestLength, uint8 c);
char* CharToString(char* szDest, size iDestLength, char16 c);
char* BoolToString(char* szDest, size iDestLength, bool b);
extern char gszDigits[17];
extern char gszEmptyString[4];
class CExternalString
{
public:
const char* msz;
size miLen;
void Init(void);
void Init(const char* sz, size iLen);
void Init(const char* szStart, const char* szLastCharInclusive);
void Clear(void);
const char* EndInclusive(void);
void Dump(void);
bool Equals(CExternalString* pcOther);
bool Equals(char* sz);
};
template<class M>
int ComparePrimitive(const void* arg1, const void* arg2)
{
if ((*((M*)arg1)) < (*((M*)arg2)))
{
return -1;
}
if ((*((M*)arg1)) > (*((M*)arg2)))
{
return 1;
}
return 0;
}
template<class M>
class CArrayTemplatePrimitive : public CArrayTemplate<M>
{
protected:
using CArrayTemplate<M>::miUsedElements;
using CArrayTemplate<M>::mpvArray;
public:
using CArrayTemplate<M>::FindInSorted;
using CArrayTemplate<M>::Resize;
using CArrayTemplate<M>::SetUsedElements;
M GetValue(size iIndex);
M SafeGetValue(size iIndex, M iNotFound);
M operator[](size iIndex);
void SetValue(size iIndex, M iElement);
void Add(M iElement);
void Add(M* paElements, size iNumElements);
void InsertAt(M iElement, size iIndex);
void SetArrayValues(M iValue);
void SetArrayValues(M iStart, M iIncrement);
void QuickSort(void);
void BubbleSort(void);
size Find(M iValue);
size AddIfUnique(M iValue);
void Swap(size iIndex1, size iIndex2);
void InsertIntoSorted(M iElement, bool bOverwriteExisting);
bool RemoveFromSorted(M iElement);
bool RemoveDuplicatesFromSorted(void);
void MakeUnique(void);
void Intersect(CArrayTemplatePrimitive<M>* pcArray1, CArrayTemplatePrimitive<M>* pcArray2);
bool IsSorted(void);
size FindFinalContiguousInSorted(void);
M Pop(void);
void Push(M iElement);
void AddRemap(size iElementPos, M iRemapNum);
void AddList(M iStop, ...);
void RemoveRemap(size iElementPos);
};
template<class M>
M CArrayTemplatePrimitive<M>::GetValue(size iIndex)
{
return (*(CArrayTemplate<M>::Get(iIndex)));
}
template<class M>
M CArrayTemplatePrimitive<M>::operator[](size iIndex)
{
return (*(CArrayTemplate<M>::Get(iIndex)));
}
template<class M>
M CArrayTemplatePrimitive<M>::SafeGetValue(size iIndex, M iNotFound)
{
if (iIndex < miUsedElements)
{
return ((M*)mpvArray)[iIndex];
}
return iNotFound;
}
template<class M>
void CArrayTemplatePrimitive<M>::SetValue(size iIndex, M iElement)
{
((M*)mpvArray)[iIndex] = iElement;
}
template<class M>
void CArrayTemplatePrimitive<M>::Add(M iElement)
{
M* pvTemp;
pvTemp = CArrayTemplate<M>::Add();
*pvTemp = iElement;
}
template<class M>
void CArrayTemplatePrimitive<M>::Add(M* paElements, size iNumElements)
{
size i;
M* pvTemp;
for (i = 0; i < iNumElements; i++)
{
pvTemp = CArrayTemplate<M>::Add();
*pvTemp = paElements[i];
}
}
template<class M>
void CArrayTemplatePrimitive<M>::InsertAt(M iElement, size iIndex)
{
M* pvTemp;
pvTemp = CArrayTemplate<M>::InsertAt(iIndex);
if (pvTemp)
{
*pvTemp = iElement;
}
}
template<class M>
void CArrayTemplatePrimitive<M>::SetArrayValues(M iValue)
{
size i;
for (i = 0; i < miUsedElements; i++)
{
((M*)mpvArray)[i] = iValue;
}
}
template<class M>
void CArrayTemplatePrimitive<M>::SetArrayValues(M iStartValue, M iIncrement)
{
size i;
for (i = 0; i < miUsedElements; i++)
{
((M*)mpvArray)[i] = iStartValue;
iStartValue += iIncrement;
}
}
template<class M>
void CArrayTemplatePrimitive<M>::QuickSort(void)
{
CArrayTemplate<M>::QuickSort(&ComparePrimitive<M>);
}
template<class M>
void CArrayTemplatePrimitive<M>::BubbleSort(void)
{
CArrayTemplate<M>::BubbleSort(&ComparePrimitive<M>);
}
template<class M>
size CArrayTemplatePrimitive<M>::Find(M iValue)
{
size i;
for (i = 0; i < miUsedElements; i++)
{
if (((M*)mpvArray)[i] == iValue)
{
return i;
}
}
return ((size)-1);
}
template<class M>
size CArrayTemplatePrimitive<M>::AddIfUnique(M iValue)
{
size iPos;
iPos = Find(iValue);
if (iPos == ((size)-1))
{
Add(iValue);
}
return iPos;
}
template<class M>
void CArrayTemplatePrimitive<M>::Swap(size iIndex1, size iIndex2)
{
M* piElement1;
M* piElement2;
M iTemp;
piElement1 = this->Get(iIndex1);
piElement2 = this->Get(iIndex2);
iTemp = (*piElement1);
(*piElement1) = (*piElement2);
(*piElement2) = iTemp;
}
template<class M>
void CArrayTemplatePrimitive<M>::InsertIntoSorted(M iElement, bool bOverwriteExisting)
{
size iPos;
bool bExists;
bExists = FindInSorted(&iElement, ComparePrimitive<M>, &iPos);
if (iPos < miUsedElements)
{
if (!bExists)
{
InsertAt(iElement, iPos);
}
else
{
if (bOverwriteExisting)
{
CArrayTemplate<M>::Set(iPos, &iElement);
}
else
{
InsertAt(iElement, iPos);
}
}
}
else
{
Add(iElement);
}
}
template<class M>
bool CArrayTemplatePrimitive<M>::RemoveFromSorted(M iElement)
{
size iPos;
bool bExists;
bExists = FindInSorted(&iElement, ComparePrimitive<M>, &iPos);
if (bExists)
{
this->RemoveAt(iPos, true);
return true;
}
return false;
}
template<class M>
bool CArrayTemplatePrimitive<M>::RemoveDuplicatesFromSorted(void)
{
size i;
M iValue;
M iCurrent;
bool bAnyRemoved;
size iWrite;
bAnyRemoved = false;
if (miUsedElements > 0)
{
iCurrent = GetValue(0);
iWrite = 1;
for (i = 1; i < miUsedElements; i++)
{
iValue = GetValue(i);
if (iValue != iCurrent)
{
SetValue(iWrite, iValue);
iCurrent = iValue;
iWrite++;
}
else
{
bAnyRemoved = true;
}
}
if (bAnyRemoved)
{
Resize(iWrite);
}
}
return bAnyRemoved;
}
template<class M>
void CArrayTemplatePrimitive<M>::MakeUnique(void)
{
QuickSort();
RemoveDuplicatesFromSorted();
}
template<class M>
void CArrayTemplatePrimitive<M>::Intersect(CArrayTemplatePrimitive<M>* pcArray1, CArrayTemplatePrimitive<M>* pcArray2)
{
size i;
size j;
M x;
M y;
for (i = 0; i < pcArray1->NumElements(); i++)
{
x = pcArray1->GetValue(i);
for (j = 0; j < pcArray2->NumElements(); j++)
{
y = pcArray2->GetValue(j);
if (x == y)
{
Add(x);
break;
}
}
}
}
template<class M>
bool CArrayTemplatePrimitive<M>::IsSorted(void)
{
size i;
M iValue;
M iLast;
if (miUsedElements > 1)
{
iLast = GetValue(0);
for (i = 1; i < miUsedElements; i++)
{
iValue = GetValue(i);
if (i != 0)
{
if (iValue < iLast)
{
return false;
}
}
iLast = iValue;
}
return true;
}
else
{
return true;
}
}
template<class M>
size CArrayTemplatePrimitive<M>::FindFinalContiguousInSorted(void)
{
size i;
M iValue;
if (miUsedElements == 0)
{
return ((size)-1);
}
for (i = 0; i < miUsedElements; i++)
{
iValue = GetValue(i);
if ((M)i != iValue)
{
if (i > 0)
{
return i - 1;
}
else
{
return ((size)-1);
}
}
}
return miUsedElements - 1;
}
template<class M>
M CArrayTemplatePrimitive<M>::Pop(void)
{
M i;
CArrayTemplate<M>::Pop(&i);
return i;
}
template<class M>
void CArrayTemplatePrimitive<M>::Push(M iElement)
{
Add(iElement);
}
template<class M>
void CArrayTemplatePrimitive<M>::AddRemap(size iElementPos, M iRemapNum)
{
M* pi;
size iIndex;
size iNumToAdd;
size iMinusOne;
if (miUsedElements > iElementPos)
{
pi = CArrayTemplate<M>::Get(iElementPos);
(*pi) = iRemapNum;
}
else
{
iMinusOne = ((size)-1);
iNumToAdd = (iElementPos - miUsedElements);
for (iIndex = 0; iIndex < iNumToAdd; iIndex++)
{
Add((M)iMinusOne);
}
Add(iRemapNum);
}
}
template<class M>
void CArrayTemplatePrimitive<M>::RemoveRemap(size iElementPos)
{
M* pi;
size iIndex;
size iCutDown;
if (iElementPos < miUsedElements)
{
pi = CArrayTemplate<M>::Get(iElementPos);
(*pi) = -1;
}
iCutDown = miUsedElements;
iIndex = miUsedElements;
if (iIndex != 0)
{
do
{
iIndex--;
pi = CArrayTemplate<M>::Get(iIndex);
if (*pi == (M)-1)
{
iCutDown = iIndex;
}
else
{
break;
}
if (iIndex == 0)
{
break;
}
}
while (iIndex != 0);
}
if (iCutDown != miUsedElements)
{
SetUsedElements(iCutDown);
}
}
template<class M>
void CArrayTemplatePrimitive<M>::AddList(M iStop, ...)
{
va_list vaMarker;
M iValue;
((vaMarker) = (char*)&(iStop) + sizeof(iStop));
iValue = (*(M*)(((vaMarker) += sizeof(M)) - sizeof(M)));
while (iValue != iStop)
{
Add(iValue);
iValue = (*(M*)(((vaMarker) += sizeof(M)) - sizeof(M)));
}
((vaMarker) = 0);
}
template<class M>
class CArrayLargeTemplatePrimitive : public CArrayLargeTemplate<M>
{
protected:
using CArrayLargeTemplate<M>::miUsedElements;
using CArrayLargeTemplate<M>::mpvArray;
public:
using CArrayLargeTemplate<M>::FindInSorted;
using CArrayLargeTemplate<M>::Resize;
using CArrayLargeTemplate<M>::SetUsedElements;
M GetValue(lsize iIndex);
M SafeGetValue(lsize iIndex, M iNotFound);
M operator[](lsize iIndex);
void SetValue(lsize iIndex, M iElement);
void Add(M iElement);
void Add(M* paElements, lsize iNumElements);
void InsertAt(M iElement, lsize iIndex);
void SetArrayValues(M iValue);
void SetArrayValues(M iStart, M iIncrement);
void QuickSort(void);
void BubbleSort(void);
lsize Find(M iValue);
lsize AddIfUnique(M iValue);
void Swap(lsize iIndex1, lsize iIndex2);
void InsertIntoSorted(M iElement, bool bOverwriteExisting);
bool RemoveFromSorted(M iElement);
bool RemoveDuplicatesFromSorted(void);
void MakeUnique(void);
void Intersect(CArrayLargeTemplatePrimitive<M>* pcArray1, CArrayLargeTemplatePrimitive<M>* pcArray2);
bool IsSorted(void);
lsize FindFinalContiguousInSorted(void);
M Pop(void);
void Push(M iElement);
void AddRemap(lsize iElementPos, M iRemapNum);
void AddList(M iStop, ...);
void RemoveRemap(lsize iElementPos);
};
template<class M>
M CArrayLargeTemplatePrimitive<M>::GetValue(lsize iIndex)
{
return (*(CArrayLargeTemplate<M>::Get(iIndex)));
}
template<class M>
M CArrayLargeTemplatePrimitive<M>::operator[](lsize iIndex)
{
return (*(CArrayLargeTemplate<M>::Get(iIndex)));
}
template<class M>
M CArrayLargeTemplatePrimitive<M>::SafeGetValue(lsize iIndex, M iNotFound)
{
if (iIndex < miUsedElements)
{
return ((M*)mpvArray)[iIndex];
}
return iNotFound;
}
template<class M>
void CArrayLargeTemplatePrimitive<M>::SetValue(lsize iIndex, M iElement)
{
((M*)mpvArray)[iIndex] = iElement;
}
template<class M>
void CArrayLargeTemplatePrimitive<M>::Add(M iElement)
{
M* pvTemp;
pvTemp = CArrayLargeTemplate<M>::Add();
*pvTemp = iElement;
}
template<class M>
void CArrayLargeTemplatePrimitive<M>::Add(M* paElements, lsize iNumElements)
{
lsize i;
M* pvTemp;
for (i = 0; i < iNumElements; i++)
{
pvTemp = CArrayLargeTemplate<M>::Add();
*pvTemp = paElements[i];
}
}
template<class M>
void CArrayLargeTemplatePrimitive<M>::InsertAt(M iElement, lsize iIndex)
{
M* pvTemp;
pvTemp = CArrayLargeTemplate<M>::InsertAt(iIndex);
if (pvTemp)
{
*pvTemp = iElement;
}
}
template<class M>
void CArrayLargeTemplatePrimitive<M>::SetArrayValues(M iValue)
{
lsize i;
for (i = 0; i < miUsedElements; i++)
{
((M*)mpvArray)[i] = iValue;
}
}
template<class M>
void CArrayLargeTemplatePrimitive<M>::SetArrayValues(M iStartValue, M iIncrement)
{
lsize i;
for (i = 0; i < miUsedElements; i++)
{
((M*)mpvArray)[i] = iStartValue;
iStartValue += iIncrement;
}
}
template<class M>
void CArrayLargeTemplatePrimitive<M>::QuickSort(void)
{
CArrayLargeTemplate<M>::QuickSort(&ComparePrimitive<M>);
}
template<class M>
void CArrayLargeTemplatePrimitive<M>::BubbleSort(void)
{
CArrayLargeTemplate<M>::BubbleSort(&ComparePrimitive<M>);
}
template<class M>
lsize CArrayLargeTemplatePrimitive<M>::Find(M iValue)
{
lsize i;
for (i = 0; i < miUsedElements; i++)
{
if (((M*)mpvArray)[i] == iValue)
{
return i;
}
}
return ((lsize)-1);
}
template<class M>
lsize CArrayLargeTemplatePrimitive<M>::AddIfUnique(M iValue)
{
lsize iPos;
iPos = Find(iValue);
if (iPos == ((lsize)-1))
{
Add(iValue);
}
return iPos;
}
template<class M>
void CArrayLargeTemplatePrimitive<M>::Swap(lsize iIndex1, lsize iIndex2)
{
M* piElement1;
M* piElement2;
M iTemp;
piElement1 = this->Get(iIndex1);
piElement2 = this->Get(iIndex2);
iTemp = (*piElement1);
(*piElement1) = (*piElement2);
(*piElement2) = iTemp;
}
template<class M>
void CArrayLargeTemplatePrimitive<M>::InsertIntoSorted(M iElement, bool bOverwriteExisting)
{
lsize iPos;
bool bExists;
bExists = FindInSorted(&iElement, ComparePrimitive<M>, &iPos);
if (iPos < miUsedElements)
{
if (!bExists)
{
InsertAt(iElement, iPos);
}
else
{
if (bOverwriteExisting)
{
CArrayLargeTemplate<M>::Set(iPos, &iElement);
}
else
{
InsertAt(iElement, iPos);
}
}
}
else
{
Add(iElement);
}
}
template<class M>
bool CArrayLargeTemplatePrimitive<M>::RemoveFromSorted(M iElement)
{
lsize iPos;
bool bExists;
bExists = FindInSorted(&iElement, ComparePrimitive<M>, &iPos);
if (bExists)
{
this->RemoveAt(iPos, true);
return true;
}
return false;
}
template<class M>
bool CArrayLargeTemplatePrimitive<M>::RemoveDuplicatesFromSorted(void)
{
lsize i;
M iValue;
M iCurrent;
bool bAnyRemoved;
lsize iWrite;
bAnyRemoved = false;
if (miUsedElements > 0)
{
iCurrent = GetValue(0);
iWrite = 1;
for (i = 1; i < miUsedElements; i++)
{
iValue = GetValue(i);
if (iValue != iCurrent)
{
SetValue(iWrite, iValue);
iCurrent = iValue;
iWrite++;
}
else
{
bAnyRemoved = true;
}
}
if (bAnyRemoved)
{
Resize(iWrite);
}
}
return bAnyRemoved;
}
template<class M>
void CArrayLargeTemplatePrimitive<M>::MakeUnique(void)
{
QuickSort();
RemoveDuplicatesFromSorted();
}
template<class M>
void CArrayLargeTemplatePrimitive<M>::Intersect(CArrayLargeTemplatePrimitive<M>* pcArray1, CArrayLargeTemplatePrimitive<M>* pcArray2)
{
lsize i;
lsize j;
M x;
M y;
for (i = 0; i < pcArray1->NumElements(); i++)
{
x = pcArray1->GetValue(i);
for (j = 0; j < pcArray2->NumElements(); j++)
{
y = pcArray2->GetValue(j);
if (x == y)
{
Add(x);
break;
}
}
}
}
template<class M>
bool CArrayLargeTemplatePrimitive<M>::IsSorted(void)
{
lsize i;
M iValue;
M iLast;
if (miUsedElements > 1)
{
iLast = GetValue(0);
for (i = 1; i < miUsedElements; i++)
{
iValue = GetValue(i);
if (i != 0)
{
if (iValue < iLast)
{
return false;
}
}
iLast = iValue;
}
return true;
}
else
{
return true;
}
}
template<class M>
lsize CArrayLargeTemplatePrimitive<M>::FindFinalContiguousInSorted(void)
{
lsize i;
M iValue;
if (miUsedElements == 0)
{
return ((lsize)-1);
}
for (i = 0; i < miUsedElements; i++)
{
iValue = GetValue(i);
if ((M)i != iValue)
{
if (i > 0)
{
return i - 1;
}
else
{
return ((lsize)-1);
}
}
}
return miUsedElements - 1;
}
template<class M>
M CArrayLargeTemplatePrimitive<M>::Pop(void)
{
M i;
CArrayLargeTemplate<M>::Pop(&i);
return i;
}
template<class M>
void CArrayLargeTemplatePrimitive<M>::Push(M iElement)
{
Add(iElement);
}
template<class M>
void CArrayLargeTemplatePrimitive<M>::AddRemap(lsize iElementPos, M iRemapNum)
{
M* pi;
lsize iIndex;
lsize iNumToAdd;
lsize iMinusOne;
if (miUsedElements > iElementPos)
{
pi = CArrayLargeTemplate<M>::Get(iElementPos);
(*pi) = iRemapNum;
}
else
{
iMinusOne = ((lsize)-1);
iNumToAdd = (iElementPos - miUsedElements);
for (iIndex = 0; iIndex < iNumToAdd; iIndex++)
{
Add((M)iMinusOne);
}
Add(iRemapNum);
}
}
template<class M>
void CArrayLargeTemplatePrimitive<M>::RemoveRemap(lsize iElementPos)
{
M* pi;
lsize iIndex;
lsize iCutDown;
if (iElementPos < miUsedElements)
{
pi = CArrayLargeTemplate<M>::Get(iElementPos);
(*pi) = -1;
}
iCutDown = miUsedElements;
iIndex = miUsedElements;
if (iIndex != 0)
{
do
{
iIndex--;
pi = CArrayLargeTemplate<M>::Get(iIndex);
if (*pi == (M)-1)
{
iCutDown = iIndex;
}
else
{
break;
}
if (iIndex == 0)
{
break;
}
}
while (iIndex != 0);
}
if (iCutDown != miUsedElements)
{
SetUsedElements(iCutDown);
}
}
template<class M>
void CArrayLargeTemplatePrimitive<M>::AddList(M iStop, ...)
{
va_list vaMarker;
M iValue;
((vaMarker) = (char*)&(iStop) + sizeof(iStop));
iValue = (*(M*)(((vaMarker) += sizeof(M)) - sizeof(M)));
while (iValue != iStop)
{
Add(iValue);
iValue = (*(M*)(((vaMarker) += sizeof(M)) - sizeof(M)));
}
((vaMarker) = 0);
}
class CArrayChar: public CArrayTemplatePrimitive<char>
{
public:
void AddList(char iStop, ...);
};
class CArrayLargeChar: public CArrayLargeTemplatePrimitive<char>
{
public:
void AddList(char iStop, ...);
};
bool IsWhitespace(char c, bool bIncludeNewLines = true);
class CArrayInt : public CArrayTemplatePrimitive<int>
{
public:
size FindUnusedInSorted(void);
void Dump(void);
};
struct SStringAlloc
{
CMallocator* pcMalloc;
char* szString;
size uiLength;
};
union UString
{
SStringAlloc sStringAlloc;
char sz[12];
};
class CChars;
class CCharsImmutable
{
public:const char* ClassName(void){ return "CCharsImmutable";}size ClassSize(void){ return sizeof(CCharsImmutable);}
friend class CFileReader;
friend class CFileWriter;
protected:
bool mbMallocated;
UString muString;
public:
void _Init(void);
void Init(const char* sz);
void Init(const char* sz, CMallocator* pcMalloc);
void Init(const char* sz, size uiLength);
void Init(const char* sz, size uiLength, CMallocator* pcMalloc);
void Init(void);
void InitLength(size uiLength);
void InitLength(size uiLength, CMallocator* pcMalloc);
void Kill(void);
void Dump(void);
char* Text(void);
size Length(void);
void Set(const char* sz);
bool Empty(void);
bool Equals(const char* szString);
bool Equals(const char* szString, size iLen);
bool Equals(CChars* pszString);
bool EqualsIgnoreCase(const char* szString);
bool EqualsIgnoreCase(CChars* pszString);
bool Contains(const char* szString);
bool ContainsIgnoreCase(const char* szString);
bool Contains(char c);
bool EndsWith(const char* szString);
bool EndsWithIgnoreCase(const char* szString);
bool EndsWith(char c);
bool StartsWith(const char* szString);
bool StartsWithIgnoreCase(const char* szString);
bool StartsWith(char c);
bool SubStringEquals(size iStart, const char* szString);
bool SubStringEqualsIgnoreCase(size iStart, const char* szString);
size FindFromEnd(const char* szString);
size FindFromEnd(size iPos, const char* szString);
size FindFromEnd(char c);
size FindFromEnd(size iIndex, char c);
size Find(const char* szString);
size Find(size iPos, const char* szString);
size Find(size iPos, char c);
size Find(char c);
bool WriteString(CFileWriter* pcWriter);
bool ReadString(CFileReader* pcReader);
};
class CArrayChars;
class CChars
{
public:const char* ClassName(void){ return "CChars";}size ClassSize(void){ return sizeof(CChars);}
friend class CFileReader;
friend class CFileWriter;
protected:
CArrayChar mcText;
public:
void _Init(void);
CChars* Init(void);
CChars* Init(const char* szString);
CChars* Init(CChars szString);
CChars* Init(CChars* psz);
CChars* Init(const char* szString, size iStartInclusive);
CChars* Init(CChars szString, size iStartInclusive, size iEndExclusive);
CChars* Init(const char* szString, size iStartInclusive, size iEndExclusive);
CChars* Init(char cPadCharacter, size iNumber);
CChars* Init(CExternalString* pcString);
CChars* InitList(const char* szFirst, ...);
CChars* InitList(CChars* szFirst, ...);
CChars* InitLength(size iLength);
CChars* InitLength(CMallocator* pcMalloc, size iLength);
bool InitData2(const char* szData, size iDataLength);
void Kill(void);
void DumpKill(void);
void Fake(const char* szString);
void Fake(const char* szString, size iStartInclusive, size iEndExclusive);
CChars* ReInit(void);
size Length(void);
void Set(const char* szString);
void Set(CChars szString);
void Set(CChars* psz);
CChars* Append(const char* szString);
CChars* Append(const char* szString, size iStrlen);
CChars* Append(CChars szString);
CChars* Append(CChars* psz);
CChars* Append(CCharsImmutable* psz);
CChars* Append(char cPadCharacter);
CChars* Append(char cPadCharacter, size iNumber);
CChars* Append(int32 i);
CChars* Append(int32 i, uint16 iBase);
CChars* Append(uint32 ui);
CChars* Append(uint32 ui, uint16 iBase);
CChars* Append(float f, size iMaxDecimals = -1, bool bAppendF = false);
CChars* Append(double d, size iMaxDecimals = -1, bool bAppendD = false);
CChars* Append(int64 lli);
CChars* Append(uint64 ulli);
CChars* Append(CExternalString* pcString);
CChars* AppendList(const char* szFirst, ...);
CChars* AppendQuoted(char c);
CChars* AppendQuoted(const char* szString);
CChars* AppendNewLine(void);
CChars* AppendNewLine(CChars szString);
CChars* AppendCarriageReturn(void);
CChars* AppendHexHiLo(void* pv, size iNumBytes);
CChars* AppendHexLoHi(void* pv, size iNumBytes);
CChars* AppendSubString(const char* szString, size iLength);
CChars* AppendSubString(CChars szString, size iStartInclusive, size iEndExclusive);
CChars* AppendSubString(CChars* pszString, size iStartInclusive, size iEndExclusive);
CChars* AppendSubString(const char* szString, size iStartInclusive, size iEndExclusive);
CChars* AppendSubString(const char* szStartInclusive, const char* szEndExclusive);
CChars* AppendBool(bool bValue);
CChars* AppendBool(bool bValue, const char* szTrue, const char* szFalse);
CChars* AppendData(const char* szData, size iMaxLength);
CChars* AppendData(const char* szData, size iDataLength, size iMaxLength);
bool AppendData2(const char* szData, size iDataLength);
CChars* AppendPointer(void* pv);
bool AppendFlag(uint32 msFlags, uint32 uiFlag, const char* szFlagName, bool bAppendComma = false);
void Insert(size iPos, char c);
void Insert(size iPos, char c, size uiCount);
void Insert(size iPos, const char* szString);
void Insert(size iPos, CChars* pszString);
void Minimize(void);
char* Text(void);
char* Text(size iIndex);
bool Empty(void);
void LeftAlign(CChars szString, char cPadCharacter, size iWidth);
void LeftAlign(const char* szString, char cPadCharacter, size iWidth);
void RightAlign(CChars szString, char cPadCharacter, size iWidth);
void RightAlign(const char* szString, char cPadCharacter, size iWidth);
void RightAlign(size uiOffset, char cPadCharacter, size uiWidth);
void RightAlign(char cPadCharacter, size iWidth);
void RemoveLastCharacter(void);
void RemoveFromStart(size iNumChars);
void RemoveFromEnd(size iNumChars);
void Remove(size iStartInclusive, size iEndExclusive);
void RemoveEnd(size iIndex);
void RemoveCharacter(size iPos);
void Split(CArrayChars* aszDest, char cSplitter);
void SplitLines(CArrayChars* aszDest);
bool Equals(const char* szString);
bool Equals(CChars szString);
bool Equals(const char* szString, size iLen);
bool Equals(CChars* pszString);
bool EqualsIgnoreCase(const char* szString);
bool EqualsIgnoreCase(CChars szString);
bool Contains(const char* szString);
bool ContainsIgnoreCase(const char* szString);
bool Contains(char c);
bool EndsWith(const char* szString);
bool EndsWithIgnoreCase(const char* szString);
bool EndsWith(char c);
bool StartsWith(const char* szString);
bool StartsWithIgnoreCase(const char* szString);
bool StartsWith(char c);
size Occurrences(const char* szString);
bool SubStringEquals(size iStart, const char* szString);
bool SubStringEqualsIgnoreCase(size iStart, const char* szString);
size FindFromEnd(const char* szString);
size FindFromEnd(size iPos, const char* szString);
size FindFromEnd(char c);
size FindFromEnd(size iIndex, char c);
size Find(const char* szString);
size Find(size iPos, const char* szString);
size Find(size iPos, char c);
size Find(char c);
size FindDigit(size iStartIndex);
char GetChar(size iIndex);
void SetChar(size iPos, char c);
void Difference(CArrayInt* paiNewToOldIndices, CArrayInt* paiOldToNewIndices, CChars szOldString);
bool IsWhitespace(size iPos, bool bIncludeNewLines);
bool IsWhitespace(void);
void SetLength(size iLength);
size StripWhitespace(bool bIncludeNewLines = false);
int Compare(CChars* szOther);
int Compare(const char* szOther);
int CompareIgnoreCase(CChars* szOther);
int CompareIgnoreCase(const char* szOther);
size Replace(char cFind, char cReplace);
size Replace(const char* szFind, const char* szReplace);
void Overwrite(size iPos, const char* szReplace);
void Reverse(void);
void Clear(void);
size CountNewLines(void);
size Count(char c);
void LowerCase(void);
void UpperCase(void);
void ReplaceNonTabsWithSpace(void);
bool WriteString(CFileWriter* pcWriter);
bool ReadString(CFileReader* pcReader);
bool ReadChars(CFileReader* pcReader);
char* CopyIntoBuffer(char* szDest, size iDestLength);
void PassifyNewlines(void);
void MakeCPlusPlus(void);
char* FindLineContaining(const char* szPosition, size* piLineNumber);
void Dump(void);
static void Dump(const char* szString);
protected:
char* PrivateGrow(size iNumberOfCharacters);
size ReplaceWithLonger(const char* szFind, const char* szReplace, size iFindLen, size iDifference);
size ReplaceWithShorter(const char* szFind, const char* szReplace, size iReplaceLen, size iFindLen, size iDifference);
size ReplaceWithEqualLength(const char* szFind, const char* szReplace, size iFindLen);
size FindEndOfLeadingWhitespace(bool bIncludeNewLines);
size FindStartOfTrailingWhitespace(bool bIncludeNewLines);
void SetNonNull(const char* szString, size iLen);
void SetEmpty(void);
void CleanIfEmpty(void);
void InitEmpty(void);
bool IsFakeEmpty(void);
void Unfake(void);
void UnfakeIfFakeEmpty(void);
};
class CLargeChars
{
public:const char* ClassName(void){ return "CLargeChars";}size ClassSize(void){ return sizeof(CLargeChars);}
friend class CFileReader;
friend class CFileWriter;
protected:
CArrayLargeChar mcText;
public:
void _Init(void);
CLargeChars* Init(void);
CLargeChars* Init(const char* szString);
CLargeChars* Init(CLargeChars szString);
CLargeChars* Init(CLargeChars* psz);
CLargeChars* Init(const char* szString, lsize iStartInclusive);
CLargeChars* Init(CLargeChars szString, lsize iStartInclusive, lsize iEndExclusive);
CLargeChars* Init(const char* szString, lsize iStartInclusive, lsize iEndExclusive);
CLargeChars* Init(char cPadCharacter, lsize iNumber);
CLargeChars* Init(CExternalString* pcString);
CLargeChars* InitList(const char* szFirst, ...);
CLargeChars* InitList(CLargeChars* szFirst, ...);
CLargeChars* InitLength(lsize iLength);
CLargeChars* InitLength(CMallocator* pcMalloc, lsize iLength);
bool InitData2(const char* szData, lsize iDataLength);
void Kill(void);
void DumpKill(void);
void Fake(const char* szString);
void Fake(const char* szString, lsize iStartInclusive, lsize iEndExclusive);
CLargeChars* ReInit(void);
lsize Length(void);
void Set(const char* szString);
void Set(CLargeChars szString);
void Set(CLargeChars* psz);
CLargeChars* Append(const char* szString);
CLargeChars* Append(const char* szString, lsize iStrlen);
CLargeChars* Append(CLargeChars szString);
CLargeChars* Append(CLargeChars* psz);
CLargeChars* Append(CChars szString);
CLargeChars* Append(CChars* psz);
CLargeChars* Append(CCharsImmutable* psz);
CLargeChars* Append(char cPadCharacter);
CLargeChars* Append(char cPadCharacter, lsize iNumber);
CLargeChars* Append(int32 i);
CLargeChars* Append(int32 i, uint16 iBase);
CLargeChars* Append(uint32 ui);
CLargeChars* Append(uint32 ui, uint16 iBase);
CLargeChars* Append(float f, lsize iMaxDecimals = -1, bool bAppendF = false);
CLargeChars* Append(double d, lsize iMaxDecimals = -1, bool bAppendD = false);
CLargeChars* Append(int64 lli);
CLargeChars* Append(uint64 ulli);
CLargeChars* Append(CExternalString* pcString);
CLargeChars* AppendList(const char* szFirst, ...);
CLargeChars* AppendQuoted(char c);
CLargeChars* AppendQuoted(const char* szString);
CLargeChars* AppendNewLine(void);
CLargeChars* AppendNewLine(CLargeChars szString);
CLargeChars* AppendCarriageReturn(void);
CLargeChars* AppendHexHiLo(void* pv, lsize iNumBytes);
CLargeChars* AppendHexLoHi(void* pv, lsize iNumBytes);
CLargeChars* AppendSubString(const char* szString, lsize iLength);
CLargeChars* AppendSubString(CLargeChars szString, lsize iStartInclusive, lsize iEndExclusive);
CLargeChars* AppendSubString(CLargeChars* pszString, lsize iStartInclusive, lsize iEndExclusive);
CLargeChars* AppendSubString(const char* szString, lsize iStartInclusive, lsize iEndExclusive);
CLargeChars* AppendSubString(const char* szStartInclusive, const char* szEndExclusive);
CLargeChars* AppendBool(bool bValue);
CLargeChars* AppendBool(bool bValue, const char* szTrue, const char* szFalse);
CLargeChars* AppendData(const char* szData, lsize iMaxLength);
CLargeChars* AppendData(const char* szData, lsize iDataLength, lsize iMaxLength);
bool AppendData2(const char* szData, lsize iDataLength);
CLargeChars* AppendPointer(void* pv);
bool AppendFlag(uint32 msFlags, uint32 uiFlag, const char* szFlagName, bool bAppendComma = false);
void Insert(lsize iPos, char c);
void Insert(lsize iPos, char c, lsize uiCount);
void Insert(lsize iPos, const char* szString);
void Insert(lsize iPos, CLargeChars* pszString);
void Minimize(void);
char* Text(void);
char* Text(lsize iIndex);
bool Empty(void);
void LeftAlign(CLargeChars szString, char cPadCharacter, lsize iWidth);
void LeftAlign(const char* szString, char cPadCharacter, lsize iWidth);
void RightAlign(CLargeChars szString, char cPadCharacter, lsize iWidth);
void RightAlign(const char* szString, char cPadCharacter, lsize iWidth);
void RightAlign(lsize uiOffset, char cPadCharacter, lsize uiWidth);
void RightAlign(char cPadCharacter, lsize iWidth);
void RemoveLastCharacter(void);
void RemoveFromStart(lsize iNumChars);
void RemoveFromEnd(lsize iNumChars);
void Remove(lsize iStartInclusive, lsize iEndExclusive);
void RemoveEnd(lsize iIndex);
void RemoveCharacter(lsize iPos);
void Split(CArrayChars* aszDest, char cSplitter);
void SplitLines(CArrayChars* aszDest);
bool Equals(const char* szString);
bool Equals(CLargeChars szString);
bool Equals(const char* szString, lsize iLen);
bool Equals(CLargeChars* pszString);
bool EqualsIgnoreCase(const char* szString);
bool EqualsIgnoreCase(CLargeChars szString);
bool Contains(const char* szString);
bool ContainsIgnoreCase(const char* szString);
bool Contains(char c);
bool EndsWith(const char* szString);
bool EndsWithIgnoreCase(const char* szString);
bool EndsWith(char c);
bool StartsWith(const char* szString);
bool StartsWithIgnoreCase(const char* szString);
bool StartsWith(char c);
lsize Occurrences(const char* szString);
bool SubStringEquals(lsize iStart, const char* szString);
bool SubStringEqualsIgnoreCase(lsize iStart, const char* szString);
lsize FindFromEnd(const char* szString);
lsize FindFromEnd(lsize iPos, const char* szString);
lsize FindFromEnd(char c);
lsize FindFromEnd(lsize iIndex, char c);
lsize Find(const char* szString);
lsize Find(lsize iPos, const char* szString);
lsize Find(lsize iPos, char c);
lsize Find(char c);
lsize FindDigit(lsize iStartIndex);
char GetChar(lsize iIndex);
void SetChar(lsize iPos, char c);
void Difference(CArrayInt* paiNewToOldIndices, CArrayInt* paiOldToNewIndices, CLargeChars szOldString);
bool IsWhitespace(lsize iPos, bool bIncludeNewLines);
bool IsWhitespace(void);
void SetLength(lsize iLength);
lsize StripWhitespace(bool bIncludeNewLines = false);
int Compare(CLargeChars* szOther);
int Compare(const char* szOther);
int CompareIgnoreCase(CLargeChars* szOther);
int CompareIgnoreCase(const char* szOther);
lsize Replace(char cFind, char cReplace);
lsize Replace(const char* szFind, const char* szReplace);
void Overwrite(lsize iPos, const char* szReplace);
void Reverse(void);
void Clear(void);
lsize CountNewLines(void);
lsize Count(char c);
void LowerCase(void);
void UpperCase(void);
void ReplaceNonTabsWithSpace(void);
bool WriteString(CFileWriter* pcWriter);
bool ReadString(CFileReader* pcReader);
bool ReadChars(CFileReader* pcReader);
char* CopyIntoBuffer(char* szDest, lsize iDestLength);
void PassifyNewlines(void);
void MakeCPlusPlus(void);
char* FindLineContaining(const char* szPosition, lsize* piLineNumber);
void Dump(void);
static void Dump(const char* szString);
protected:
char* PrivateGrow(lsize iNumberOfCharacters);
lsize ReplaceWithLonger(const char* szFind, const char* szReplace, lsize iFindLen, lsize iDifference);
lsize ReplaceWithShorter(const char* szFind, const char* szReplace, lsize iReplaceLen, lsize iFindLen, lsize iDifference);
lsize ReplaceWithEqualLength(const char* szFind, const char* szReplace, lsize iFindLen);
lsize FindEndOfLeadingWhitespace(bool bIncludeNewLines);
lsize FindStartOfTrailingWhitespace(bool bIncludeNewLines);
void SetNonNull(const char* szString, lsize iLen);
void SetEmpty(void);
void CleanIfEmpty(void);
void InitEmpty(void);
bool IsFakeEmpty(void);
void Unfake(void);
void UnfakeIfFakeEmpty(void);
};
int CompareChars(const void* arg1, const void* arg2);
int CompareCharsIgnoreCase(const void* arg1, const void* arg2);
class CRandom;
typedef CArrayTemplate<CChars> __CArrayChars;
class CArrayChars
{
public:
__CArrayChars mcArray;
bool mbFaked;
void _Init(void);
void Init(void);
void Init(const char* szFirst, ...);
void Init(CArrayChars* pasz);
void Fake(void);
void ReInit(void);
void Kill(void);
size NumElements(void);
CChars* Add(CChars cChars);
CChars* Add(CChars* pcChars);
CChars* Add(const char* szString);
CChars* Add(void);
CChars* Add(const char* szString, size iStartInclusive, size iEndExclusive);
CChars* Add(const char* szText, char* szLastCharInclusive);
CChars* AddLength(size uiLength);
CChars* AddIfUnique(char* szString);
CChars* AddIfUnique(CChars cChars);
void AddList(const char* sz, ...);
CChars* InsertIntoSorted(char* szText, char* szLastCharInclusive);
CChars* InsertIntoSorted(CChars* psz);
void Remove(CChars* pcChars);
void Remove(const char* szString);
void Remove(size iIndex);
bool RemoveTail(void);
CChars* Get(size iIndex);
CChars* Tail(void);
char* GetText(size iIndex);
size GetIndex(const char* szStart, size iLen);
size GetIndex(const char* szStart);
size GetIndex(CChars* psz);
size GetSubStringIndex(const char* szStart);
size FindInSorted(const char* szString, bool bCaseSensitive = true);
size FindInSorted(CChars* szString, bool bCaseSensitive = true);
void Copy(CArrayChars* pcSource);
bool Equals(CArrayChars* pcOther);
bool Contains(const char* szText);
bool Contains(CChars* psz);
bool ContainsSubString(const char* szText);
void QuickSort(bool bCaseSensitive = true);
void BubbleSort(bool bCaseSensitive = true);
void Shuffle(CRandom* pcRandom = 0L);
bool Split(const char* szString, char cSplitter);
size GetLongestChars(void);
char GetCharAt(size x, size y);
void Finalise(void);
void Print(CChars* psz);
void Dump(void);
};
extern CArrayChars gaszArchaicWords;
extern CArrayChars gaszArchaicDefinitions;
extern CArrayChars gaszCommonWords;
class CRandom;
void GetArchaicDefinitions(CArrayChars* pasz);
void GetArchaicWords(CArrayChars* pasz);
void GetCommonWords(CArrayChars* pasz);
void PrintRandomWords(CChars* psz, CRandom* pcRandom, bool bIncludeArchaic, uint32 iWordCount);
void WordsInit(void);
void WordsKill(void);
CArrayChars gaszArchaicWords;
CArrayChars gaszArchaicDefinitions;
CArrayChars gaszCommonWords;
void GetArchaicDefinitions(CArrayChars* pasz)
{
pasz->Add("abroad: out of doors");
pasz->Add("accouchement: birthing");
pasz->Add("advertisement: a notice to readers in a book");
pasz->Add("afeard / afeared: frightened");
pasz->Add("affright: frighten(someone)");
pasz->Add("ague: malaria or a similar illness");
pasz->Add("aliment: food; nourishment");
pasz->Add("ambuscade: an ambush");
pasz->Add("animalcule: a microscopic animal");
pasz->Add("apothecary: a person who prepared and sold medicine");
pasz->Add("appetency: a longing or desire");
pasz->Add("assay: attempt");
pasz->Add("asunder: apart");
pasz->Add("audition: the power of hearing");
pasz->Add("aught: anything at all");
pasz->Add("avaunt: go away");
pasz->Add("bane: poison");
pasz->Add("baseborn: of low birth or social standing");
pasz->Add("bedlam: an asylum");
pasz->Add("behold: see or observe");
pasz->Add("behoof: benefit or advantage");
pasz->Add("beldam: an old woman");
pasz->Add("bethink oneself of: remember; recollect");
pasz->Add("betimes: in good time; early");
pasz->Add("bibliopole: a dealer in books");
pasz->Add("bijoux: jewellery; trinkets");
pasz->Add("billow: a large sea wave");
pasz->Add("blackguard: a scoundrel");
pasz->Add("blow: produce flowers or be in flower");
pasz->Add("bodkin: a dagger");
pasz->Add("bootless(of a task) ineffectual; useless");
pasz->Add("breech: a person's buttocks");
pasz->Add("bridewell: a prison or reform school for petty offenders");
pasz->Add("brimstone: sulphur");
pasz->Add("bruit: a report or rumour");
pasz->Add("buck: a fashionable and daring young man");
pasz->Add("bumper: a generous glass of an alcoholic drink");
pasz->Add("burgess: a full citizen of a town or borough");
pasz->Add("buss: a kiss");
pasz->Add("caboose: a kitchen on a ship's deck");
pasz->Add("cadet: a younger son or daughter");
pasz->Add("caducity: the infirmity of old age; senility");
pasz->Add("camelopard: a giraffe");
pasz->Add("cannonade: bombard");
pasz->Add("carl: a man of low birth");
pasz->Add("ceil: line or plaster the roof of(a building)");
pasz->Add("champaign: open level countryside");
pasz->Add("chapman: a peddler");
pasz->Add("chicane: deceive; hoodwink");
pasz->Add("circumjacent: surrounding");
pasz->Add("cicisbeo: a married woman's male companion or lover");
pasz->Add("cispontine: on the north side of the Thames in London");
pasz->Add("cleanse: restore to health");
pasz->Add("clerk: a literate or scholarly person");
pasz->Add("clew: a ball of thread");
pasz->Add("clout: a piece of cloth or clothing");
pasz->Add("collogue: talk confidentially");
pasz->Add("commend: entrust someone or something to");
pasz->Add("commons: provisions shared in common; rations");
pasz->Add("communicant: a person who imparts information");
pasz->Add("compass: encircle or surround");
pasz->Add("compeer: a companion or close associate");
pasz->Add("con: study attentively or learn by heart(a piece of writing)");
pasz->Add("condition: social position");
pasz->Add("conjure: implore(someone) to do something");
pasz->Add("contemn: treat or regard with contempt");
pasz->Add("contumely: insolent or insulting language or treatment");
pasz->Add("cordwainer: a shoemaker");
pasz->Add("corrupt: rotten or putrid");
pasz->Add("corse: a corpse");
pasz->Add("cottier: a rural labourer living in a cottage");
pasz->Add("coxcomb: a vain and conceited man; a dandy");
pasz->Add("coz: cousin");
pasz->Add("crinkum - crankum: elaborate decoration or detail");
pasz->Add("crookback: a person with a hunchback");
pasz->Add("crumpet: a person's head");
pasz->Add("cruse: an earthenware pot or jar");
pasz->Add("cully: a friendly form of address for a man");
pasz->Add("cutpurse: a pickpocket");
pasz->Add("dame: an elderly or mature woman");
pasz->Add("damsel: a young unmarried woman");
pasz->Add("dandiprat: a young or insignificant person");
pasz->Add("darbies: handcuffs");
pasz->Add("dark: ignorant");
pasz->Add("degrade: reduce to a lower rank, especially as a punishment");
pasz->Add("degree: social or official rank");
pasz->Add("delate: report(an offence)");
pasz->Add("demesne: a region or domain");
pasz->Add("demit: resign from(an office or position)");
pasz->Add("demoralize: corrupt the morals of");
pasz->Add("dight: clothed or equipped");
pasz->Add("discover: divulge(a secret)");
pasz->Add("disport: frolic");
pasz->Add("dispraise: censure or criticize");
pasz->Add("divers: of varying types; several");
pasz->Add("doit: a very small amount of money");
pasz->Add("dot: a dowry from which only the interest or annual income was available to the husband");
pasz->Add("doxy: a lover or mistress");
pasz->Add("drab: a slovenly woman");
pasz->Add("drought: thirst");
pasz->Add("egad: exclamation of surprise, anger, or affirmation");
pasz->Add("embarrass: hamper or impede");
pasz->Add("embouchure: the mouth of a river");
pasz->Add("equipage: gear; equipment");
pasz->Add("ere: before(in time)");
pasz->Add("espousal: a marriage or engagement");
pasz->Add("estate: a particular state, period, or condition in life");
pasz->Add("esurient: hungry");
pasz->Add("expectations: one's prospects of inheritance");
pasz->Add("expiry: death");
pasz->Add("fain: pleased or willing under the circumstances");
pasz->Add("fainéant: an idle or ineffective person");
pasz->Add("fair: beautiful");
pasz->Add("fandangle: a useless or purely ornamental thing");
pasz->Add("fane: a shrine or temple");
pasz->Add("fare: travel");
pasz->Add("fell: an animal skin; a pelt");
pasz->Add("feminal: feminine; womanly");
pasz->Add("fervent: hot or glowing");
pasz->Add("fie: exclamation used to express disgust or outrage");
pasz->Add("filibeg: a kilt");
pasz->Add("fishwife: a woman who sells fish");
pasz->Add("fizgig: a silly or flirtatious young woman");
pasz->Add("flux: diarrhoea or dysentery");
pasz->Add("forfend: avert or prevent(something evil or unpleasant)");
pasz->Add("forsooth: indeed");
pasz->Add("fourscore: eighty");
pasz->Add("freak: a whim");
pasz->Add("frore: frozen or frosty");
pasz->Add("froward(of a person) difficult to deal with; contrary");
pasz->Add("fruit: offspring");
pasz->Add("fudge: nonsense");
pasz->Add("furbish: polish(a weapon)");
pasz->Add("gadzooks: an expression of surprise or annoyance");
pasz->Add("gage: a valued object deposited as a guarantee");
pasz->Add("gallant: a dashing gentleman");
pasz->Add("gammer: an old woman");
pasz->Add("garland: a literary anthology");
pasz->Add("garth: a yard or garden");
pasz->Add("gaud: a trinket");
pasz->Add("gentle: noble or courteous");
pasz->Add("glabriety: baldness");
pasz->Add("glaciate: freeze over");
pasz->Add("glebe: a meadow");
pasz->Add("glim: a candle");
pasz->Add("go - cart: a baby walker");
pasz->Add("God's acre: a churchyard");
pasz->Add("goodly: attractive, excellent, or virtuous");
pasz->Add("goody(with a name) an elderly woman of humble position");
pasz->Add("grateful: received with gratitude");
pasz->Add("greenwood: a forest");
pasz->Add("grimalkin: a cat");
pasz->Add("gudgeon: a credulous person");
pasz->Add("guerdon: a reward");
pasz->Add("gyve: a fetter or shackle");
pasz->Add("habiliment: clothing");
pasz->Add("halt: lame");
pasz->Add("handmaid: a female servant");
pasz->Add("hearken: listen");
pasz->Add("hence: from here");
pasz->Add("herbary: a herb garden");
pasz->Add("hereat: as a result of this");
pasz->Add("hereunto: to this document");
pasz->Add("hereupon: after or as a result of this");
pasz->Add("hie: go quickly");
pasz->Add("hight: named");
pasz->Add("hither: to or toward this place");
pasz->Add("hoar: frost");
pasz->Add("horse - coper: a person who deals in horses");
pasz->Add("horseless carriage: a car");
pasz->Add("host: an army");
pasz->Add("howbeit: nevertheless");
pasz->Add("husbandman: a farmer");
pasz->Add("immedicable: untreatable");
pasz->Add("imminent: overhanging");
pasz->Add("indite: write; compose");
pasz->Add("inscribe: enter the name of(someone) on a list");
pasz->Add("in sooth: actually");
pasz->Add("intelligence: news");
pasz->Add("intelligencer: a person who gathers intelligence");
pasz->Add("invest: surround(a place) in order to besiege or blockade it");
pasz->Add("iron horse: a steam locomotive");
pasz->Add("izzard: the letter Z");
pasz->Add("jade: a bad - tempered or disreputable woman");
pasz->Add("jakes: an outdoor toilet");
pasz->Add("job: turn a public office or a position of trust to private advantage");
pasz->Add("kickshaw: a fancy but insubstantial cooked dish");
pasz->Add("kine: cows collectively");
pasz->Add("kirtle: a woman's gown or a man's tunic");
pasz->Add("knave: a dishonest or unscrupulous man");
pasz->Add("larcener: thief");
pasz->Add("latchet: a narrow thong or lace for fastening a shoe or sandal");
pasz->Add("laud: praise");
pasz->Add("laver: a basin or similar container used for washing oneself");
pasz->Add("learn: teach");
pasz->Add("leech: a doctor or healer");
pasz->Add("leman: a lover or sweetheart");
pasz->Add("let: hinder");
pasz->Add("levant: abscond leaving unpaid debts");
pasz->Add("Levant: the eastern part of the Mediterranean");
pasz->Add("levy: a body of enlisted troops");
pasz->Add("lief: as happily; as gladly");
pasz->Add("like enough: probably");
pasz->Add("loathly: repulsive");
pasz->Add("lordling: a minor lord");
pasz->Add("love apple: a tomato");
pasz->Add("Lucifer: a match");
pasz->Add("lurdan: an idle or incompetent person");
pasz->Add("lying - in: seclusion before and after childbirth");
pasz->Add("magdalen: a reformed prostitute");
pasz->Add("mage: a magician or learned person");
pasz->Add("magnify: glorify; extol");
pasz->Add("maid: a girl or young woman");
pasz->Add("malapert: presumptuous and impudent");
pasz->Add("malison: a curse");
pasz->Add("man - at - arms: a soldier");
pasz->Add("marry: an expression of surprise, indignation, or emphatic assertion");
pasz->Add("mayhap: perhaps; possibly");
pasz->Add("mazed: bewildered");
pasz->Add("measure: a dance");
pasz->Add("meat: food of any kind");
pasz->Add("mechanical: a manual worker");
pasz->Add("meet: suitable or proper");
pasz->Add("melodist: a singer");
pasz->Add("methinks: it seems to me");
pasz->Add("moil: drudgery");
pasz->Add("mooncalf: a foolish person");
pasz->Add("morrow, the: the following day");
pasz->Add("mummer: an actor in the theatre");
pasz->Add("natheless: nevertheless");
pasz->Add("natural: a person born with impaired intelligence");
pasz->Add("naught: nothing");
pasz->Add("nay: no");
pasz->Add("neat: a bovine animal or animals");
pasz->Add("nice: fastidious");
pasz->Add("nigh: near");
pasz->Add("nithing: a contemptible or despicable person");
pasz->Add("noise(something) about: talk about or make known publicly");
pasz->Add("nubbing - cheat: a gallows");
pasz->Add("numbles: a deer's entrails as food");
pasz->Add("orison: a prayer");
pasz->Add("orts: scraps; remains");
pasz->Add("otherwhere: elsewhere");
pasz->Add("otiose: lazy; slothful");
pasz->Add("overbrim: spill; overflow");
pasz->Add("overleap: jump over or across");
pasz->Add("overset: capsize; flip over");
pasz->Add("pale: an area within determined bounds or subject to a particular jurisdiction");
pasz->Add("palfrey: a docile riding horse");
pasz->Add("pate: a person's head");
pasz->Add("paynim: a pagan");
pasz->Add("peccant: sinful; offending");
pasz->Add("peeler: a police officer");
pasz->Add("pelf: money, especially when gained dishonestly");
pasz->Add("peradventure: perhaps");
pasz->Add("perchance: by some chance");
pasz->Add("peregrinate: travel or wander from place to place");
pasz->Add("periapt: a charm or amulet");
pasz->Add("pest: bubonic plague");
pasz->Add("pestilence: a fatal epidemic disease, especially bubonic plague");
pasz->Add("peterman: a thief or safecracker");
pasz->Add("physic: medicinal drugs or medical treatment");
pasz->Add("picaroon: a scoundrel");
pasz->Add("piepowder: a traveller or an itinerant merchant or trader");
pasz->Add("pismire: an ant");
pasz->Add("pistoleer: a soldier armed with a pistol");
pasz->Add("plain over: lament; cry over");
pasz->Add("plight: solemnly pledge or promise(faith or loyalty)");
pasz->Add("pollard: an animal that has lost its horns or cast its antlers");
pasz->Add("poltroon: an utter coward");
pasz->Add("popinjay: a parrot");
pasz->Add("pore on: think about");
pasz->Add("portage: the action of carrying or transporting");
pasz->Add("portion: a dowry");
pasz->Add("portion: a person's destiny or lot");
pasz->Add("posy: a short motto or line of verse inscribed inside a ring");
pasz->Add("potation: a beverage");
pasz->Add("pouncet - box: a small box with a perforated lid used for holding a substance impregnated with perfume");
pasz->Add("prithee: please");
pasz->Add("profess: teach(a subject) as a professor");
pasz->Add("purblind: short - sighted");
pasz->Add("purfle: an ornamental or embroidered edge of a garment");
pasz->Add("pythoness: a woman believed to be possessed by a spirit and to be able to foresee the future");
pasz->Add("quaggy: marshy or boggy");
pasz->Add("quality: high social standing");
pasz->Add("quean: an impudent girl or woman");
pasz->Add("quick, the: the living");
pasz->Add("quidnunc: an inquisitive, gossipy person");
pasz->Add("quiz: look intently at(someone)");
pasz->Add("quoth: said(in I / he / she quoth)");
pasz->Add("rack(of a cloud) be driven by the wind");
pasz->Add("raiment: clothing");
pasz->Add("rapscallion: a mischievous person");
pasz->Add("rathe - ripe(of fruit) ripening early in the year; (of a person) precocious");
pasz->Add("reave: carry out a plundering raid");
pasz->Add("receipt: a recipe");
pasz->Add("recipe: a medical prescription");
pasz->Add("recompense: punish or reward appropriately");
pasz->Add("recreant: cowardly");
pasz->Add("rede: advice or counsel");
pasz->Add("reduce: besiege and capture(a town or fortress)");
pasz->Add("relieve: make(something) stand out");
pasz->Add("remit: diminish");
pasz->Add("repair: an abode or haunt");
pasz->Add("repulsive: lacking friendliness or sympathy");
pasz->Add("riband: a ribbon");
pasz->Add("rover: a pirate");
pasz->Add("rude: ignorant and uneducated");
pasz->Add("ruth: a feeling of pity, distress, or grief");
pasz->Add("sables: black mourning clothes");
pasz->Add("sacring: the consecration of a bishop, a sovereign, or the Eucharistic elements");
pasz->Add("saddle - bow: the pommel of a saddle");
pasz->Add("salamander: a red - hot iron or poker");
pasz->Add("sanative: healing");
pasz->Add("sanguinary: involving or causing much bloodshed");
pasz->Add("sap: make(a building, etc.) insecure by removing its foundations");
pasz->Add("saturnism: lead poisoning");
pasz->Add("scantling: a specimen, sample, or small amount");
pasz->Add("scapegrace: a mischievous person; a rascal");
pasz->Add("scaramouch: a boastful but cowardly person");
pasz->Add("schoolman: a teacher");
pasz->Add("science: knowledge");
pasz->Add("sciolist: a person who pretends to be knowledgeable");
pasz->Add("scold: a woman who nags or grumbles constantly");
pasz->Add("scot: a tax - like payment");
pasz->Add("scrag: a neck");
pasz->Add("scruple: a very small amount of something, especially a quality");
pasz->Add("scullion: a menial servant");
pasz->Add("scurvy: worthless or contemptible");
pasz->Add("sea coal: mineral coal");
pasz->Add("sea smoke: fog");
pasz->Add("seizing: a length of cord or rope on board a ship");
pasz->Add("sennight: a week");
pasz->Add("sepulture: burial");
pasz->Add("shambles: a slaughterhouse");
pasz->Add("shrift: forgiveness");
pasz->Add("shrive(of a priest) absolve(a person making a confession)");
pasz->Add("silly: helpless; defenceless");
pasz->Add("sippet: a small piece of bread or toast for dipping into soup or sauce");
pasz->Add("skirt: an edge, border, or extreme part");
pasz->Add("slay: kill in a violent way");
pasz->Add("slipshod(of shoes) worn down at the heel");
pasz->Add("slugabed: a lazy person who stays in bed late");
pasz->Add("small beer: weak beer");
pasz->Add("smite: defeat or conquer");
pasz->Add("soak: drink heavily");
pasz->Add("soft tack: bread, especially as rations for sailors or soldiers");
pasz->Add("soil: a stain");
pasz->Add("sooth: truth");
pasz->Add("sore: extremely; severely");
pasz->Add("speed: success; prosperity");
pasz->Add("spence: a pantry or larder");
pasz->Add("statuary: a sculptor");
pasz->Add("steed: a horse");
pasz->Add("stoup: a container for drinking beer, etc.; a flagon");
pasz->Add("stripe: a blow with a lash");
pasz->Add("strumpet: a female prostitute or a promiscuous woman");
pasz->Add("success: a good or bad outcome");
pasz->Add("suffer: endure; tolerate");
pasz->Add("surety, of / for a: for certain");
pasz->Add("swain: a country youth");
pasz->Add("swash: flamboyantly swagger about or wield a sword");
pasz->Add("sweeting: darling");
pasz->Add("sweetmeat: an item of confectionery or sweet food");
pasz->Add("taiga: a forest");
pasz->Add("tantivy: a rapid gallop or ride");
pasz->Add("tapster: a person who serves at a bar");
pasz->Add("tenter: a person in charge of something, especially factory machinery");
pasz->Add("thenceforth: from that time, place, or point onward");
pasz->Add("thereunto: to that");
pasz->Add("therewith: with or in the thing mentioned");
pasz->Add("thither: to or toward that place");
pasz->Add("thrice: three times");
pasz->Add("tilt with: engage in a contest with");
pasz->Add("timbrel: a tambourine or similar instrument");
pasz->Add("tithe: a tenth");
pasz->Add("tocsin: an alarm bell or signal");
pasz->Add("tope: drink to excess");
pasz->Add("trespass: a sin or offence");
pasz->Add("trig: neat and smart");
pasz->Add("trigon: a triangle");
pasz->Add("troth: faith or loyalty when pledged in a solemn undertaking");
pasz->Add("truck: an exchange or transaction");
pasz->Add("turnkey: a jailer");
pasz->Add("tweeny: a maid who assisted both the cook and the housemaid");
pasz->Add("twelvemonth: a year");
pasz->Add("uncle: a pawnbroker");
pasz->Add("uncommon: remarkably");
pasz->Add("up to snuff: up to the required standard");
pasz->Add("usher: an assistant teacher");
pasz->Add("vale: a farewell; a send - off");
pasz->Add("varlet: an unprincipled rogue");
pasz->Add("venery: hunting");
pasz->Add("verily: truly; certainly");
pasz->Add("verse: a line of poetry");
pasz->Add("very: real; genuine");
pasz->Add("virtue: virginity");
pasz->Add("visionary: existing only in the imagination");
pasz->Add("wain: a wagon or cart");
pasz->Add("wait on / upon: pay a respectful visit to");
pasz->Add("waits: street singers of Christmas carols");
pasz->Add("ware of: aware of");
pasz->Add("wassail: revelry");
pasz->Add("wast: second person singular past of be");
pasz->Add("watch: remain awake as religious observance");
pasz->Add("watchful: wakeful");
pasz->Add("watchword: a military password");
pasz->Add("weasand: the oesophagus or gullet");
pasz->Add("ween: think or suppose; be of the opinion");
pasz->Add("wench: a girl or young woman");
pasz->Add("whence: from what place or source");
pasz->Add("whereat: at which");
pasz->Add("wherefore: for what reason");
pasz->Add("wherewith: with or by which");
pasz->Add("whilom: formerly");
pasz->Add("white goods: domestic linen");
pasz->Add("whither: to what place or state");
pasz->Add("wife: a woman, especially an old or uneducated one");
pasz->Add("wight: a person of a specified kind");
pasz->Add("wise: manner, way, or extent");
pasz->Add("withal: in addition");
pasz->Add("without: outside");
pasz->Add("wondrous: wonderfully");
pasz->Add("wont: accustomed");
pasz->Add("wonted: usual");
pasz->Add("wool - stapler: a dealer in wool");
pasz->Add("wright: a maker or builder");
pasz->Add("yclept: by the name of");
pasz->Add("ye: you");
pasz->Add("yea: yes");
pasz->Add("yoke: the amount of land that one pair of oxen could plough in a day");
pasz->Add("yonder: over there");
pasz->Add("zounds: an expression of surprise or indignation");
}
void GetArchaicWords(CArrayChars* pasz)
{
uint32 i;
CChars* pszDefinition;
size iIndex;
CChars sz;
for (i = 0; i < gaszArchaicDefinitions.NumElements(); i++)
{
pszDefinition = gaszArchaicDefinitions.Get(i);
iIndex = pszDefinition->Find(':');
if (iIndex != ((size)-1))
{
sz.Init(pszDefinition->Text(), 0, iIndex);
gaszArchaicWords.Add(sz);
sz.Kill();
}
else
{
gaszArchaicWords.Add(pszDefinition->Text());
}
}
}
void GetCommonWords(CArrayChars* pasz)
{
uint32 i;
char* sz;
pasz->Add("a");
pasz->Add("ability");
pasz->Add("able");
pasz->Add("about");
pasz->Add("above");
pasz->Add("accept");
pasz->Add("according");
pasz->Add("account");
pasz->Add("across");
pasz->Add("act");
pasz->Add("action");
pasz->Add("activity");
pasz->Add("actually");
pasz->Add("add");
pasz->Add("address");
pasz->Add("administration");
pasz->Add("admit");
pasz->Add("adult");
pasz->Add("affect");
pasz->Add("after");
pasz->Add("again");
pasz->Add("against");
pasz->Add("age");
pasz->Add("agency");
pasz->Add("agent");
pasz->Add("ago");
pasz->Add("agree");
pasz->Add("agreement");
pasz->Add("ahead");
pasz->Add("air");
pasz->Add("all");
pasz->Add("allow");
pasz->Add("almost");
pasz->Add("alone");
pasz->Add("along");
pasz->Add("already");
pasz->Add("also");
pasz->Add("although");
pasz->Add("always");
pasz->Add("American");
pasz->Add("among");
pasz->Add("amount");
pasz->Add("analysis");
pasz->Add("and");
pasz->Add("animal");
pasz->Add("another");
pasz->Add("answer");
pasz->Add("any");
pasz->Add("anyone");
pasz->Add("anything");
pasz->Add("appear");
pasz->Add("apply");
pasz->Add("approach");
pasz->Add("area");
pasz->Add("argue");
pasz->Add("arm");
pasz->Add("around");
pasz->Add("arrive");
pasz->Add("art");
pasz->Add("article");
pasz->Add("artist");
pasz->Add("as");
pasz->Add("ask");
pasz->Add("assume");
pasz->Add("at");
pasz->Add("attack");
pasz->Add("attention");
pasz->Add("attorney");
pasz->Add("audience");
pasz->Add("author");
pasz->Add("authority");
pasz->Add("available");
pasz->Add("avoid");
pasz->Add("away");
pasz->Add("baby");
pasz->Add("back");
pasz->Add("bad");
pasz->Add("bag");
pasz->Add("ball");
pasz->Add("bank");
pasz->Add("bar");
pasz->Add("base");
pasz->Add("be");
pasz->Add("beat");
pasz->Add("beautiful");
pasz->Add("because");
pasz->Add("become");
pasz->Add("bed");
pasz->Add("before");
pasz->Add("begin");
pasz->Add("behavior");
pasz->Add("behind");
pasz->Add("believe");
pasz->Add("benefit");
pasz->Add("best");
pasz->Add("better");
pasz->Add("between");
pasz->Add("beyond");
pasz->Add("big");
pasz->Add("bill");
pasz->Add("billion");
pasz->Add("bit");
pasz->Add("black");
pasz->Add("blood");
pasz->Add("blue");
pasz->Add("board");
pasz->Add("body");
pasz->Add("book");
pasz->Add("born");
pasz->Add("both");
pasz->Add("box");
pasz->Add("boy");
pasz->Add("break");
pasz->Add("bring");
pasz->Add("brother");
pasz->Add("budget");
pasz->Add("build");
pasz->Add("building");
pasz->Add("business");
pasz->Add("but");
pasz->Add("buy");
pasz->Add("by");
pasz->Add("call");
pasz->Add("camera");
pasz->Add("campaign");
pasz->Add("can");
pasz->Add("cancer");
pasz->Add("candidate");
pasz->Add("capital");
pasz->Add("car");
pasz->Add("card");
pasz->Add("care");
pasz->Add("career");
pasz->Add("carry");
pasz->Add("case");
pasz->Add("catch");
pasz->Add("cause");
pasz->Add("cell");
pasz->Add("center");
pasz->Add("central");
pasz->Add("century");
pasz->Add("certain");
pasz->Add("certainly");
pasz->Add("chair");
pasz->Add("challenge");
pasz->Add("chance");
pasz->Add("change");
pasz->Add("character");
pasz->Add("charge");
pasz->Add("check");
pasz->Add("child");
pasz->Add("choice");
pasz->Add("choose");
pasz->Add("church");
pasz->Add("citizen");
pasz->Add("city");
pasz->Add("civil");
pasz->Add("claim");
pasz->Add("class");
pasz->Add("clear");
pasz->Add("clearly");
pasz->Add("close");
pasz->Add("coach");
pasz->Add("cold");
pasz->Add("collection");
pasz->Add("college");
pasz->Add("color");
pasz->Add("come");
pasz->Add("commercial");
pasz->Add("common");
pasz->Add("community");
pasz->Add("company");
pasz->Add("compare");
pasz->Add("computer");
pasz->Add("concern");
pasz->Add("condition");
pasz->Add("conference");
pasz->Add("Congress");
pasz->Add("consider");
pasz->Add("consumer");
pasz->Add("contain");
pasz->Add("continue");
pasz->Add("control");
pasz->Add("cost");
pasz->Add("could");
pasz->Add("country");
pasz->Add("couple");
pasz->Add("course");
pasz->Add("court");
pasz->Add("cover");
pasz->Add("create");
pasz->Add("crime");
pasz->Add("cultural");
pasz->Add("culture");
pasz->Add("cup");
pasz->Add("current");
pasz->Add("customer");
pasz->Add("cut");
pasz->Add("dark");
pasz->Add("data");
pasz->Add("daughter");
pasz->Add("day");
pasz->Add("dead");
pasz->Add("deal");
pasz->Add("death");
pasz->Add("debate");
pasz->Add("decade");
pasz->Add("decide");
pasz->Add("decision");
pasz->Add("deep");
pasz->Add("defense");
pasz->Add("degree");
pasz->Add("Democrat");
pasz->Add("democratic");
pasz->Add("describe");
pasz->Add("design");
pasz->Add("despite");
pasz->Add("detail");
pasz->Add("determine");
pasz->Add("develop");
pasz->Add("development");
pasz->Add("die");
pasz->Add("difference");
pasz->Add("different");
pasz->Add("difficult");
pasz->Add("dinner");
pasz->Add("direction");
pasz->Add("director");
pasz->Add("discover");
pasz->Add("discuss");
pasz->Add("discussion");
pasz->Add("disease");
pasz->Add("do");
pasz->Add("doctor");
pasz->Add("dog");
pasz->Add("door");
pasz->Add("down");
pasz->Add("draw");
pasz->Add("dream");
pasz->Add("drive");
pasz->Add("drop");
pasz->Add("drug");
pasz->Add("during");
pasz->Add("each");
pasz->Add("early");
pasz->Add("east");
pasz->Add("easy");
pasz->Add("eat");
pasz->Add("economic");
pasz->Add("economy");
pasz->Add("edge");
pasz->Add("education");
pasz->Add("effect");
pasz->Add("effort");
pasz->Add("eight");
pasz->Add("either");
pasz->Add("election");
pasz->Add("else");
pasz->Add("employee");
pasz->Add("end");
pasz->Add("energy");
pasz->Add("enjoy");
pasz->Add("enough");
pasz->Add("enter");
pasz->Add("entire");
pasz->Add("environment");
pasz->Add("environmental");
pasz->Add("especially");
pasz->Add("establish");
pasz->Add("even");
pasz->Add("evening");
pasz->Add("event");
pasz->Add("ever");
pasz->Add("every");
pasz->Add("everybody");
pasz->Add("everyone");
pasz->Add("everything");
pasz->Add("evidence");
pasz->Add("exactly");
pasz->Add("example");
pasz->Add("executive");
pasz->Add("exist");
pasz->Add("expect");
pasz->Add("experience");
pasz->Add("expert");
pasz->Add("explain");
pasz->Add("eye");
pasz->Add("face");
pasz->Add("fact");
pasz->Add("factor");
pasz->Add("fail");
pasz->Add("fall");
pasz->Add("family");
pasz->Add("far");
pasz->Add("fast");
pasz->Add("father");
pasz->Add("fear");
pasz->Add("federal");
pasz->Add("feel");
pasz->Add("feeling");
pasz->Add("few");
pasz->Add("field");
pasz->Add("fight");
pasz->Add("figure");
pasz->Add("fill");
pasz->Add("film");
pasz->Add("final");
pasz->Add("finally");
pasz->Add("financial");
pasz->Add("find");
pasz->Add("fine");
pasz->Add("finger");
pasz->Add("finish");
pasz->Add("fire");
pasz->Add("firm");
pasz->Add("first");
pasz->Add("fish");
pasz->Add("five");
pasz->Add("floor");
pasz->Add("fly");
pasz->Add("focus");
pasz->Add("follow");
pasz->Add("food");
pasz->Add("foot");
pasz->Add("for");
pasz->Add("force");
pasz->Add("foreign");
pasz->Add("forget");
pasz->Add("form");
pasz->Add("former");
pasz->Add("forward");
pasz->Add("four");
pasz->Add("free");
pasz->Add("friend");
pasz->Add("from");
pasz->Add("front");
pasz->Add("full");
pasz->Add("fund");
pasz->Add("future");
pasz->Add("game");
pasz->Add("garden");
pasz->Add("gas");
pasz->Add("general");
pasz->Add("generation");
pasz->Add("get");
pasz->Add("girl");
pasz->Add("give");
pasz->Add("glass");
pasz->Add("go");
pasz->Add("goal");
pasz->Add("good");
pasz->Add("government");
pasz->Add("great");
pasz->Add("green");
pasz->Add("ground");
pasz->Add("group");
pasz->Add("grow");
pasz->Add("growth");
pasz->Add("guess");
pasz->Add("gun");
pasz->Add("guy");
pasz->Add("hair");
pasz->Add("half");
pasz->Add("hand");
pasz->Add("hang");
pasz->Add("happen");
pasz->Add("happy");
pasz->Add("hard");
pasz->Add("have");
pasz->Add("he");
pasz->Add("head");
pasz->Add("health");
pasz->Add("hear");
pasz->Add("heart");
pasz->Add("heat");
pasz->Add("heavy");
pasz->Add("help");
pasz->Add("her");
pasz->Add("here");
pasz->Add("herself");
pasz->Add("high");
pasz->Add("him");
pasz->Add("himself");
pasz->Add("his");
pasz->Add("history");
pasz->Add("hit");
pasz->Add("hold");
pasz->Add("home");
pasz->Add("hope");
pasz->Add("hospital");
pasz->Add("hot");
pasz->Add("hotel");
pasz->Add("hour");
pasz->Add("house");
pasz->Add("how");
pasz->Add("however");
pasz->Add("huge");
pasz->Add("human");
pasz->Add("hundred");
pasz->Add("husband");
pasz->Add("I");
pasz->Add("idea");
pasz->Add("identify");
pasz->Add("if");
pasz->Add("image");
pasz->Add("imagine");
pasz->Add("impact");
pasz->Add("important");
pasz->Add("improve");
pasz->Add("in");
pasz->Add("include");
pasz->Add("including");
pasz->Add("increase");
pasz->Add("indeed");
pasz->Add("indicate");
pasz->Add("individual");
pasz->Add("industry");
pasz->Add("information");
pasz->Add("inside");
pasz->Add("instead");
pasz->Add("institution");
pasz->Add("interest");
pasz->Add("interesting");
pasz->Add("international");
pasz->Add("interview");
pasz->Add("into");
pasz->Add("investment");
pasz->Add("involve");
pasz->Add("issue");
pasz->Add("it");
pasz->Add("item");
pasz->Add("its");
pasz->Add("itself");
pasz->Add("job");
pasz->Add("join");
pasz->Add("just");
pasz->Add("keep");
pasz->Add("key");
pasz->Add("kid");
pasz->Add("kill");
pasz->Add("kind");
pasz->Add("kitchen");
pasz->Add("know");
pasz->Add("knowledge");
pasz->Add("land");
pasz->Add("language");
pasz->Add("large");
pasz->Add("last");
pasz->Add("late");
pasz->Add("later");
pasz->Add("laugh");
pasz->Add("law");
pasz->Add("lawyer");
pasz->Add("lay");
pasz->Add("lead");
pasz->Add("leader");
pasz->Add("learn");
pasz->Add("least");
pasz->Add("leave");
pasz->Add("left");
pasz->Add("leg");
pasz->Add("legal");
pasz->Add("less");
pasz->Add("let");
pasz->Add("letter");
pasz->Add("level");
pasz->Add("lie");
pasz->Add("life");
pasz->Add("light");
pasz->Add("like");
pasz->Add("likely");
pasz->Add("line");
pasz->Add("list");
pasz->Add("listen");
pasz->Add("little");
pasz->Add("live");
pasz->Add("local");
pasz->Add("long");
pasz->Add("look");
pasz->Add("lose");
pasz->Add("loss");
pasz->Add("lot");
pasz->Add("love");
pasz->Add("low");
pasz->Add("machine");
pasz->Add("magazine");
pasz->Add("main");
pasz->Add("maintain");
pasz->Add("major");
pasz->Add("majority");
pasz->Add("make");
pasz->Add("man");
pasz->Add("manage");
pasz->Add("management");
pasz->Add("manager");
pasz->Add("many");
pasz->Add("market");
pasz->Add("marriage");
pasz->Add("material");
pasz->Add("matter");
pasz->Add("may");
pasz->Add("maybe");
pasz->Add("me");
pasz->Add("mean");
pasz->Add("measure");
pasz->Add("media");
pasz->Add("medical");
pasz->Add("meet");
pasz->Add("meeting");
pasz->Add("member");
pasz->Add("memory");
pasz->Add("mention");
pasz->Add("message");
pasz->Add("method");
pasz->Add("middle");
pasz->Add("might");
pasz->Add("military");
pasz->Add("million");
pasz->Add("mind");
pasz->Add("minute");
pasz->Add("miss");
pasz->Add("mission");
pasz->Add("model");
pasz->Add("modern");
pasz->Add("moment");
pasz->Add("money");
pasz->Add("month");
pasz->Add("more");
pasz->Add("morning");
pasz->Add("most");
pasz->Add("mother");
pasz->Add("mouth");
pasz->Add("move");
pasz->Add("movement");
pasz->Add("movie");
pasz->Add("Mr");
pasz->Add("Mrs");
pasz->Add("much");
pasz->Add("music");
pasz->Add("must");
pasz->Add("my");
pasz->Add("myself");
pasz->Add("n't");
pasz->Add("name");
pasz->Add("nation");
pasz->Add("national");
pasz->Add("natural");
pasz->Add("nature");
pasz->Add("near");
pasz->Add("nearly");
pasz->Add("necessary");
pasz->Add("need");
pasz->Add("network");
pasz->Add("never");
pasz->Add("new");
pasz->Add("news");
pasz->Add("newspaper");
pasz->Add("next");
pasz->Add("nice");
pasz->Add("night");
pasz->Add("no");
pasz->Add("none");
pasz->Add("nor");
pasz->Add("north");
pasz->Add("not");
pasz->Add("note");
pasz->Add("nothing");
pasz->Add("notice");
pasz->Add("now");
pasz->Add("number");
pasz->Add("occur");
pasz->Add("of");
pasz->Add("off");
pasz->Add("offer");
pasz->Add("office");
pasz->Add("officer");
pasz->Add("official");
pasz->Add("often");
pasz->Add("oh");
pasz->Add("oil");
pasz->Add("ok");
pasz->Add("old");
pasz->Add("on");
pasz->Add("once");
pasz->Add("one");
pasz->Add("only");
pasz->Add("onto");
pasz->Add("open");
pasz->Add("operation");
pasz->Add("opportunity");
pasz->Add("option");
pasz->Add("or");
pasz->Add("order");
pasz->Add("organization");
pasz->Add("other");
pasz->Add("others");
pasz->Add("our");
pasz->Add("out");
pasz->Add("outside");
pasz->Add("over");
pasz->Add("own");
pasz->Add("owner");
pasz->Add("page");
pasz->Add("pain");
pasz->Add("painting");
pasz->Add("paper");
pasz->Add("parent");
pasz->Add("part");
pasz->Add("participant");
pasz->Add("particular");
pasz->Add("particularly");
pasz->Add("partner");
pasz->Add("party");
pasz->Add("pass");
pasz->Add("past");
pasz->Add("patient");
pasz->Add("pattern");
pasz->Add("pay");
pasz->Add("peace");
pasz->Add("people");
pasz->Add("per");
pasz->Add("perform");
pasz->Add("performance");
pasz->Add("perhaps");
pasz->Add("period");
pasz->Add("person");
pasz->Add("personal");
pasz->Add("phone");
pasz->Add("physical");
pasz->Add("pick");
pasz->Add("picture");
pasz->Add("piece");
pasz->Add("place");
pasz->Add("plan");
pasz->Add("plant");
pasz->Add("play");
pasz->Add("player");
pasz->Add("PM");
pasz->Add("point");
pasz->Add("police");
pasz->Add("policy");
pasz->Add("political");
pasz->Add("politics");
pasz->Add("poor");
pasz->Add("popular");
pasz->Add("population");
pasz->Add("position");
pasz->Add("positive");
pasz->Add("possible");
pasz->Add("power");
pasz->Add("practice");
pasz->Add("prepare");
pasz->Add("present");
pasz->Add("president");
pasz->Add("pressure");
pasz->Add("pretty");
pasz->Add("prevent");
pasz->Add("price");
pasz->Add("private");
pasz->Add("probably");
pasz->Add("problem");
pasz->Add("process");
pasz->Add("produce");
pasz->Add("product");
pasz->Add("production");
pasz->Add("professional");
pasz->Add("professor");
pasz->Add("program");
pasz->Add("project");
pasz->Add("property");
pasz->Add("protect");
pasz->Add("prove");
pasz->Add("provide");
pasz->Add("public");
pasz->Add("pull");
pasz->Add("purpose");
pasz->Add("push");
pasz->Add("put");
pasz->Add("quality");
pasz->Add("question");
pasz->Add("quickly");
pasz->Add("quite");
pasz->Add("race");
pasz->Add("radio");
pasz->Add("raise");
pasz->Add("range");
pasz->Add("rate");
pasz->Add("rather");
pasz->Add("reach");
pasz->Add("read");
pasz->Add("ready");
pasz->Add("real");
pasz->Add("reality");
pasz->Add("realize");
pasz->Add("really");
pasz->Add("reason");
pasz->Add("receive");
pasz->Add("recent");
pasz->Add("recently");
pasz->Add("recognize");
pasz->Add("record");
pasz->Add("red");
pasz->Add("reduce");
pasz->Add("reflect");
pasz->Add("region");
pasz->Add("relate");
pasz->Add("relationship");
pasz->Add("religious");
pasz->Add("remain");
pasz->Add("remember");
pasz->Add("remove");
pasz->Add("report");
pasz->Add("represent");
pasz->Add("Republican");
pasz->Add("require");
pasz->Add("research");
pasz->Add("resource");
pasz->Add("respond");
pasz->Add("response");
pasz->Add("responsibility");
pasz->Add("rest");
pasz->Add("result");
pasz->Add("return");
pasz->Add("reveal");
pasz->Add("rich");
pasz->Add("right");
pasz->Add("rise");
pasz->Add("risk");
pasz->Add("road");
pasz->Add("rock");
pasz->Add("role");
pasz->Add("room");
pasz->Add("rule");
pasz->Add("run");
pasz->Add("safe");
pasz->Add("same");
pasz->Add("save");
pasz->Add("say");
pasz->Add("scene");
pasz->Add("school");
pasz->Add("science");
pasz->Add("scientist");
pasz->Add("score");
pasz->Add("sea");
pasz->Add("season");
pasz->Add("seat");
pasz->Add("second");
pasz->Add("section");
pasz->Add("security");
pasz->Add("see");
pasz->Add("seek");
pasz->Add("seem");
pasz->Add("sell");
pasz->Add("send");
pasz->Add("senior");
pasz->Add("sense");
pasz->Add("series");
pasz->Add("serious");
pasz->Add("serve");
pasz->Add("service");
pasz->Add("set");
pasz->Add("seven");
pasz->Add("several");
pasz->Add("sex");
pasz->Add("sexual");
pasz->Add("shake");
pasz->Add("share");
pasz->Add("she");
pasz->Add("shoot");
pasz->Add("short");
pasz->Add("shot");
pasz->Add("should");
pasz->Add("shoulder");
pasz->Add("show");
pasz->Add("side");
pasz->Add("sign");
pasz->Add("significant");
pasz->Add("similar");
pasz->Add("simple");
pasz->Add("simply");
pasz->Add("since");
pasz->Add("sing");
pasz->Add("single");
pasz->Add("sister");
pasz->Add("sit");
pasz->Add("site");
pasz->Add("situation");
pasz->Add("six");
pasz->Add("size");
pasz->Add("skill");
pasz->Add("skin");
pasz->Add("small");
pasz->Add("smile");
pasz->Add("so");
pasz->Add("social");
pasz->Add("society");
pasz->Add("soldier");
pasz->Add("some");
pasz->Add("somebody");
pasz->Add("someone");
pasz->Add("something");
pasz->Add("sometimes");
pasz->Add("son");
pasz->Add("song");
pasz->Add("soon");
pasz->Add("sort");
pasz->Add("sound");
pasz->Add("source");
pasz->Add("south");
pasz->Add("southern");
pasz->Add("space");
pasz->Add("speak");
pasz->Add("special");
pasz->Add("specific");
pasz->Add("speech");
pasz->Add("spend");
pasz->Add("sport");
pasz->Add("spring");
pasz->Add("staff");
pasz->Add("stage");
pasz->Add("stand");
pasz->Add("standard");
pasz->Add("star");
pasz->Add("start");
pasz->Add("state");
pasz->Add("statement");
pasz->Add("station");
pasz->Add("stay");
pasz->Add("step");
pasz->Add("still");
pasz->Add("stock");
pasz->Add("stop");
pasz->Add("store");
pasz->Add("story");
pasz->Add("strategy");
pasz->Add("street");
pasz->Add("strong");
pasz->Add("structure");
pasz->Add("student");
pasz->Add("study");
pasz->Add("stuff");
pasz->Add("style");
pasz->Add("subject");
pasz->Add("success");
pasz->Add("successful");
pasz->Add("such");
pasz->Add("suddenly");
pasz->Add("suffer");
pasz->Add("suggest");
pasz->Add("summer");
pasz->Add("support");
pasz->Add("sure");
pasz->Add("surface");
pasz->Add("system");
pasz->Add("table");
pasz->Add("take");
pasz->Add("talk");
pasz->Add("task");
pasz->Add("tax");
pasz->Add("teach");
pasz->Add("teacher");
pasz->Add("team");
pasz->Add("technology");
pasz->Add("television");
pasz->Add("tell");
pasz->Add("ten");
pasz->Add("tend");
pasz->Add("term");
pasz->Add("test");
pasz->Add("than");
pasz->Add("thank");
pasz->Add("that");
pasz->Add("the");
pasz->Add("their");
pasz->Add("them");
pasz->Add("themselves");
pasz->Add("then");
pasz->Add("theory");
pasz->Add("there");
pasz->Add("these");
pasz->Add("they");
pasz->Add("thing");
pasz->Add("think");
pasz->Add("third");
pasz->Add("this");
pasz->Add("those");
pasz->Add("though");
pasz->Add("thought");
pasz->Add("thousand");
pasz->Add("threat");
pasz->Add("three");
pasz->Add("through");
pasz->Add("throughout");
pasz->Add("throw");
pasz->Add("thus");
pasz->Add("time");
pasz->Add("to");
pasz->Add("today");
pasz->Add("together");
pasz->Add("tonight");
pasz->Add("too");
pasz->Add("top");
pasz->Add("total");
pasz->Add("tough");
pasz->Add("toward");
pasz->Add("town");
pasz->Add("trade");
pasz->Add("traditional");
pasz->Add("training");
pasz->Add("travel");
pasz->Add("treat");
pasz->Add("treatment");
pasz->Add("tree");
pasz->Add("trial");
pasz->Add("trip");
pasz->Add("trouble");
pasz->Add("true");
pasz->Add("truth");
pasz->Add("try");
pasz->Add("turn");
pasz->Add("TV");
pasz->Add("two");
pasz->Add("type");
pasz->Add("under");
pasz->Add("understand");
pasz->Add("unit");
pasz->Add("until");
pasz->Add("up");
pasz->Add("upon");
pasz->Add("us");
pasz->Add("use");
pasz->Add("usually");
pasz->Add("value");
pasz->Add("various");
pasz->Add("very");
pasz->Add("victim");
pasz->Add("view");
pasz->Add("violence");
pasz->Add("visit");
pasz->Add("voice");
pasz->Add("vote");
pasz->Add("wait");
pasz->Add("walk");
pasz->Add("wall");
pasz->Add("want");
pasz->Add("war");
pasz->Add("watch");
pasz->Add("water");
pasz->Add("way");
pasz->Add("we");
pasz->Add("weapon");
pasz->Add("wear");
pasz->Add("week");
pasz->Add("weight");
pasz->Add("well");
pasz->Add("west");
pasz->Add("western");
pasz->Add("what");
pasz->Add("whatever");
pasz->Add("when");
pasz->Add("where");
pasz->Add("whether");
pasz->Add("which");
pasz->Add("while");
pasz->Add("white");
pasz->Add("who");
pasz->Add("whole");
pasz->Add("whom");
pasz->Add("whose");
pasz->Add("why");
pasz->Add("wide");
pasz->Add("wife");
pasz->Add("will");
pasz->Add("win");
pasz->Add("wind");
pasz->Add("window");
pasz->Add("wish");
pasz->Add("with");
pasz->Add("within");
pasz->Add("without");
pasz->Add("woman");
pasz->Add("wonder");
pasz->Add("word");
pasz->Add("work");
pasz->Add("worker");
pasz->Add("world");
pasz->Add("worry");
pasz->Add("would");
pasz->Add("write");
pasz->Add("writer");
pasz->Add("wrong");
pasz->Add("yard");
pasz->Add("yeah");
pasz->Add("year");
pasz->Add("yes");
pasz->Add("yet");
pasz->Add("you");
pasz->Add("young");
pasz->Add("your");
pasz->Add("yourself");
for (i = 0; i < pasz->NumElements(); i++)
{
sz = pasz->Get(i)->Text();
ToLower(sz);
}
}
void PrintRandomWords(CChars* psz, CRandom* pcRandom, bool bIncludeArchaic, uint32 iWordCount)
{
size iMaxWords;
uint32 i;
uint32 iWordNum;
size iCommonWords;
bool bFirst;
iCommonWords = gaszCommonWords.NumElements();
iMaxWords = iCommonWords;
if (bIncludeArchaic)
{
iMaxWords += gaszArchaicWords.NumElements();
}
bFirst = true;
for (i = 0; i < iWordCount; i++)
{
if (!bFirst)
{
psz->Append(" ");
}
else
{
bFirst = false;
}
iWordNum = pcRandom->Next(0, (int)(iMaxWords - 1));
if (iWordNum > gaszCommonWords.NumElements())
{
psz->Append(gaszArchaicWords.Get(iWordNum - iCommonWords));
}
else
{
psz->Append(gaszCommonWords.Get(iWordNum));
}
}
}
void WordsInit(void)
{
gaszArchaicWords.Init();
gaszArchaicDefinitions.Init();
gaszCommonWords.Init();
GetArchaicDefinitions(&gaszArchaicDefinitions);
GetArchaicWords(&gaszArchaicWords);
GetCommonWords(&gaszCommonWords);
}
void WordsKill(void)
{
gaszArchaicWords.Kill();
gaszArchaicDefinitions.Kill();
gaszCommonWords.Kill();
}
