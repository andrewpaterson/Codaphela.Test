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
int ComparePtr(const void* arg1, const void* arg2);
int ComparePtrPtr(const void* arg1, const void* arg2);
extern "C"
{
double fabs(double x);
float fabsf(float x);
double sqrt(double x);
float sqrtf(float x);
double sin(double x);
float sinf(float x);
double cos(double x);
float cosf(float x);
double tan(double x);
float tanf(float x);
double asin(double x);
double acos(double x);
double atan(double x);
float atanf(float x);
double atan2(double y, double x);
float atan2f(float y, float x);
double exp(double x);
float expf(float x);
double log(double x);
float logf(float x);
double log10(double x);
double pow(double x, double y);
float powf(float x, float y);
double floor(double x);
float floorf(float x);
double ceil(double x);
float ceilf(float x);
double fmod(double x, double y);
float fmodf(float x, float y);
double modf(double x, double* pdInteger);
double ldexp(double x, int iExponent);
double frexp(double x, int* piExponent);
double round(double x);
float roundf(float x);
long lround(double x);
long lroundf(float x);
long long llround(double x);
long long llroundf(float x);
double trunc(double x);
float truncf(float x);
double hypot(double x, double y);
float hypotf(float x, float y);
float asinf(float x);
float acosf(float x);
long double fabsl(long double x);
long double sqrtl(long double x);
long double floorl(long double x);
long double ceill(long double x);
long double truncl(long double x);
long double roundl(long double x);
long double fmodl(long double x, long double y);
long double powl(long double x, long double y);
long double logl(long double x);
long double log10l(long double x);
long double expl(long double x);
}
bool isnan(double x);
bool isnan(float x);
bool isinf(double x);
bool isinf(float x);
bool isfinite(double x);
bool isfinite(float x);
float32 Deg2Dot(float32 fDegrees);
float64 Deg2Dot(float64 fDegrees);
template<size I = 512>
class CStackMemory
{
private:
union
{
uint8 macOnStack[I];
uint8* mpvOffStack;
} u;
uint16 muiSize;
public:
void* Init(void);
void* Init(size iSize);
void Kill(void);
size GetStackSize(void);
void* GetStackData(void);
};
template<size I>
void* CStackMemory<I>::Init(void)
{
u.mpvOffStack = 0L;
muiSize = (uint16)I;
return u.macOnStack;
}
template<size I>
void* CStackMemory<I>::Init(size iSize)
{
if (iSize > I)
{
muiSize = I + 1;
u.mpvOffStack = (uint8*)malloc(iSize);
return u.mpvOffStack;
}
else
{
muiSize = (uint16)iSize;
u.mpvOffStack = 0L;
return u.macOnStack;
}
}
template<size I>
void CStackMemory<I>::Kill(void)
{
if (muiSize == I + 1)
{
if (u.mpvOffStack) { free(u.mpvOffStack); u.mpvOffStack = 0L; };
}
muiSize = 0;
}
template<size I>
size CStackMemory<I>::GetStackSize(void)
{
return I;
}
template<size I>
void* CStackMemory<I>::GetStackData(void)
{
if (muiSize == I + 1)
{
return u.mpvOffStack;
}
else
{
return u.macOnStack;
}
}
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
class CSafeArrayBlock
{
private:
CMutex m;
CArrayBlock c;
public:
void Init(size iElementSize);
void Init(CMallocator* pcMalloc, size iElementSize);
void Init(CMallocator* pcMalloc, size iElementSize, size iChunkSize);
void ReInit(void);
void Finalise(void);
void Kill(void);
size NumElements(void);
bool IsEmpty(void);
bool IsNotEmpty(void);
size AllocatedElements(void);
size ElementSize(void);
void Add(void* pvData);
size AddGetIndex(void* pvData);
size AddIfUnique(void* pData);
size AddIfUniqueKey(void* pData, size iKeyOffset, size iKeySize);
void Copy(CArrayBlock* pcTemplateArray);
void Copy(CSafeArrayBlock* pcTemplateArray);
size Copy(CStackMemory<>* pcTemp);
bool Get(size iIndex, void* pvDest);
bool Tail(void* pvDest);
void InsertAt(void* pvData, size iIndex);
size InsertIntoSorted(int(*fCompare)(const void*, const void*), void* pvData, bool bOverwriteExisting);
bool Pop(void* pvDest);
bool Pop(void);
void Push(void* pvData);
bool PopFirst(void* pvData);
bool PopFirst(void);
size Resize(size iNumElements);
void BubbleSort(int(*fCompare)(const void*, const void*));
void QuickSort(int(*fCompare)(const void*, const void*));
void Reverse(void);
bool Contains(void* pData);
size Find(void* pData);
bool FindInSorted(void* pData, int(*fCompare)(const void*, const void*), size* piIndex);
void RemoveAt(size iIndex, bool bPreserveOrder = true);
void RemoveRange(size iStartIndex, size iEndIndexExclusive, bool bPreserveOrder = true);
bool RemoveTail(void);
void Set(size iIndex, void* pvData);
void Swap(size iIndex1, size iIndex2);
void Zero(void);
size ByteSize(void);
size ChunkSize(void);
size SetUsedElements(size iNumElements);
bool SetChunkSize(size iChunkSize);
bool Write(CFileWriter* pcFileWriter);
bool Read(CFileReader* pcFileReader);
private:
bool MemcpyDestAndUnlock(void* pvSource, void* pvDest);
};
void CSafeArrayBlock::Init(size iElementSize)
{
m.Init();
m.Lock();
c.Init(iElementSize);
m.Unlock();
}
void CSafeArrayBlock::Init(CMallocator* pcMalloc, size iElementSize)
{
m.Init();
m.Lock();
c.Init(pcMalloc, iElementSize);
m.Unlock();
}
void CSafeArrayBlock::Init(CMallocator* pcMalloc, size iElementSize, size iChunkSize)
{
m.Init();
m.Lock();
c.Init(pcMalloc, iElementSize, iChunkSize);
m.Unlock();
}
void CSafeArrayBlock::ReInit(void)
{
m.Lock();
c.ReInit();
m.Unlock();
}
void CSafeArrayBlock::Finalise(void)
{
m.Lock();
c.Finalise();
m.Unlock();
}
void CSafeArrayBlock::Kill(void)
{
m.Lock();
c.Kill();
m.Unlock();
m.Kill();
}
size CSafeArrayBlock::NumElements(void)
{
return c.NumElements();
}
bool CSafeArrayBlock::IsEmpty(void)
{
return c.IsEmpty();
}
bool CSafeArrayBlock::IsNotEmpty(void)
{
return c.IsNotEmpty();
}
size CSafeArrayBlock::AllocatedElements(void)
{
return c.AllocatedElements();
}
size CSafeArrayBlock::ElementSize(void)
{
return c.ElementSize();
}
void CSafeArrayBlock::Add(void* pvData)
{
m.Lock();
c.Add(pvData);
m.Unlock();
}
size CSafeArrayBlock::AddGetIndex(void* pvData)
{
size iIndex;
m.Lock();
iIndex = c.AddExistingGetIndex(pvData);
m.Unlock();
return iIndex;
}
size CSafeArrayBlock::AddIfUnique(void* pvData)
{
size iIndex;
m.Lock();
iIndex = c.AddIfUnique(pvData);
m.Unlock();
return iIndex;
}
size CSafeArrayBlock::AddIfUniqueKey(void* pvData, size iKeyOffset, size iKeySize)
{
size iIndex;
m.Lock();
iIndex = c.AddIfUniqueKey(pvData, iKeyOffset, iKeySize);
m.Unlock();
return iIndex;
}
void CSafeArrayBlock::Copy(CArrayBlock* pcTemplateArray)
{
m.Lock();
c.Copy(pcTemplateArray);
m.Unlock();
}
void CSafeArrayBlock::Copy(CSafeArrayBlock* pcTemplateArray)
{
CStackMemory<> cTemp;
size iNumElements;
iNumElements = pcTemplateArray->Copy(&cTemp);
m.Lock();
c.Resize(iNumElements);
memcpy(c.GetData(), cTemp.GetStackData(), iNumElements * c.ElementSize());
m.Unlock();
}
size CSafeArrayBlock::Copy(CStackMemory<>* pcTemp)
{
size_t iByteSize;
void* pv;
size iUsedElements;
m.Lock();
iByteSize = c.ByteSize();
iUsedElements = c.NumElements();
pv = pcTemp->Init(iByteSize);
memcpy(pv, c.GetData(), iByteSize);
m.Unlock();
return iUsedElements;
}
bool CSafeArrayBlock::Get(size iIndex, void* pvDest)
{
void* pv;
m.Lock();
pv = c.SafeGet(iIndex);
return MemcpyDestAndUnlock(pv, pvDest);
}
bool CSafeArrayBlock::Tail(void* pvDest)
{
void* pv;
m.Lock();
pv = c.Tail();
return MemcpyDestAndUnlock(pv, pvDest);
}
void CSafeArrayBlock::InsertAt(void* pvData, size iIndex)
{
m.Lock();
c.InsertAt(pvData, iIndex);
m.Unlock();
}
size CSafeArrayBlock::InsertIntoSorted(int(*fCompare)(const void*, const void*), void* pvData, bool bOverwriteExisting)
{
size iIndex;
m.Lock();
iIndex = c.InsertIntoSorted(fCompare, pvData, bOverwriteExisting);
m.Unlock();
return iIndex;
}
bool CSafeArrayBlock::Pop(void* pvDest)
{
bool bResult;
m.Lock();
bResult = c.Pop(pvDest);
m.Unlock();
return bResult;
}
bool CSafeArrayBlock::Pop(void)
{
bool bResult;
m.Lock();
bResult = c.Pop();
m.Unlock();
return bResult;
}
void CSafeArrayBlock::Push(void* pvData)
{
m.Lock();
c.Push(pvData);
m.Unlock();
}
bool CSafeArrayBlock::PopFirst(void* pvDest)
{
bool bResult;
m.Lock();
bResult = c.PopFirst(pvDest);
m.Unlock();
return bResult;
}
bool CSafeArrayBlock::PopFirst(void)
{
bool bResult;
m.Lock();
bResult = c.PopFirst();
m.Unlock();
return bResult;
}
size CSafeArrayBlock::Resize(size iNumElements)
{
size iOldUsedElements;
m.Lock();
iOldUsedElements = c.Resize(iNumElements);
m.Unlock();
return iOldUsedElements;
}
void CSafeArrayBlock::BubbleSort(int(*fCompare)(const void*, const void*))
{
m.Lock();
c.BubbleSort(fCompare);
m.Unlock();
}
void CSafeArrayBlock::QuickSort(int(*fCompare)(const void*, const void*))
{
m.Lock();
c.QuickSort(fCompare);
m.Unlock();
}
void CSafeArrayBlock::Reverse(void)
{
m.Lock();
c.Reverse();
m.Unlock();
}
bool CSafeArrayBlock::Contains(void* pvData)
{
bool bResult;
m.Lock();
bResult = c.Contains(pvData);
m.Unlock();
return bResult;
}
size CSafeArrayBlock::Find(void* pvData)
{
size iIndex;
m.Lock();
iIndex = c.Find(pvData);
m.Unlock();
return iIndex;
}
bool CSafeArrayBlock::FindInSorted(void* pvData, int(*fCompare)(const void*, const void*), size* piIndex)
{
bool bResult;
m.Lock();
bResult = c.FindInSorted(pvData, fCompare, piIndex);
m.Unlock();
return bResult;
}
void CSafeArrayBlock::RemoveAt(size iIndex, bool bPreserveOrder)
{
m.Lock();
c.RemoveAt(iIndex, bPreserveOrder);
m.Unlock();
}
void CSafeArrayBlock::RemoveRange(size iStartIndex, size iEndIndexExclusive, bool bPreserveOrder)
{
m.Lock();
c.RemoveRange(iStartIndex, iEndIndexExclusive, bPreserveOrder);
m.Unlock();
}
bool CSafeArrayBlock::RemoveTail(void)
{
bool bResult;
m.Lock();
bResult = c.RemoveTail();
m.Unlock();
return bResult;
}
void CSafeArrayBlock::Set(size iIndex, void* pvData)
{
m.Lock();
c.Set(iIndex, pvData);
m.Unlock();
}
void CSafeArrayBlock::Swap(size iIndex1, size iIndex2)
{
m.Lock();
c.Swap(iIndex1, iIndex2);
m.Unlock();
}
void CSafeArrayBlock::Zero(void)
{
m.Lock();
c.Zero();
m.Unlock();
}
size CSafeArrayBlock::ByteSize(void)
{
return c.ByteSize();
}
size CSafeArrayBlock::ChunkSize(void)
{
return c.ChunkSize();
}
size CSafeArrayBlock::SetUsedElements(size iNumElements)
{
size iOldUsedElements;
m.Lock();
iOldUsedElements = c.SetUsedElements(iNumElements);
m.Unlock();
return iOldUsedElements;
}
bool CSafeArrayBlock::SetChunkSize(size iChunkSize)
{
bool bResult;
m.Lock();
bResult = c.SetChunkSize(iChunkSize);
m.Unlock();
return bResult;
}
bool CSafeArrayBlock::Write(CFileWriter* pcFileWriter)
{
bool bResult;
m.Lock();
bResult = c.Write(pcFileWriter);
m.Unlock();
return bResult;
}
bool CSafeArrayBlock::Read(CFileReader* pcFileReader)
{
bool bResult;
m.Init();
m.Lock();
bResult = c.Read(pcFileReader);
m.Unlock();
return bResult;
}
bool CSafeArrayBlock::MemcpyDestAndUnlock(void* pvSource, void* pvDest)
{
if (pvSource != 0L)
{
memcpy(pvDest, pvSource, c.ElementSize());
m.Unlock();
return true;
}
else
{
m.Unlock();
return false;
}
}
