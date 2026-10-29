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
size PassifyNewlines(char *szString);
size CountNewLines(char* szString, size iLen);
size CountCarriageReturns(const char* szString, size iLen);
size CountLineFeeds(char* szString, size iLen);
struct SLogConfig
{
bool bEnabled;
bool bDebugOutput;
bool bBreakOnError;
bool bBreakOnWarning;
};
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
float32 minf(float32 f1, float32 f2);
float32 maxf(float32 f1, float32 f2);
bool FloatEqual(float32 f1, float32 f2);
bool FloatEqual(float32 f1, float32 f2, float32 fTolerance);
bool FloatGreaterThanOrEqual(float32 f1, float32 f2);
bool FloatLessThanOrEqual(float32 f1, float32 f2);
bool FloatGreaterThan(float32 f1, float32 f2);
bool FloatLessThan(float32 f1, float32 f2);
float32 RoundFloat(float32 fInput, int32 iBinaryExponent);
float32 TruncateFloat(float32 fInput, int32 iBinaryExponent);
float32 NormaliseFloat(float32 fSize, float32 fPos);
float32 NormaliseFloat(float32 fMax, float32 fMin, float32 fPos);
float32 InterpolateFloat(float32 f1, float32 f2, float32 fPos);
void InterpolateFloat(float32* fDest, float32 f1, float32 f2, float32 fPos);
float32 Float32ToleranceForDecimals(int32 iDecimals);
size FloatWholeNumbers(float32 f);
bool FloatEqual(float64 f1, float64 f2);
bool FloatEqual(float64 f1, float64 f2, float64 fTolerance);
bool DoubleGreaterThanOrEqual(float64 f1, float64 f2);
bool DoubleLessThanOrEqual(float64 f1, float64 f2);
bool DoubleGreaterThan(float64 f1, float64 f2);
bool DoubleLessThan(float64 f1, float64 f2);
float64 RoundFloat(float64 fInput, int64 iBinaryExponent);
float64 TruncateFloat(float64 fInput, int64 iBinaryExponent);
void CosSinDegrees(float64 fDegrees, float64* pfCos, float64* pfSin);
float64 NormaliseDouble(float64 fSize, float64 fPos);
float64 NormaliseDouble(float64 fMax, float64 fMin, float64 fPos);
float64 InterpolateDouble(float64 f1, float64 f2, float64 fPos);
void InterpolateDouble(float64* fDest, float64 f1, float64 f2, float64 fPos);
float64 Float64ToleranceForDecimals(int32 iDecimals);
size FloatWholeNumbers(float64 f);
bool LongDoubleEqual(float128 f1, float128 f2);
bool LongDoubleEqual(float128 f1, float128 f2, float128 fTolerance);
void SwapFloat(float32* f1, float32* f2);
float32 Float32NotANumber(void);
float64 Float64NotANumber(void);
bool IsNotANumber(float32* pf);
float128 ConvertDecimalFixedPointToLongDouble(uint64 ulliWholeNumber, uint64 ulliDecimalNumber, uint16 iNumDecimalDigits, int64 lliExponentNumber);
float32 det2x2(float32 a, float32 b, float32 c, float32 d);
float32 det3x3(float32 a1, float32 a2, float32 a3, float32 b1, float32 b2, float32 b3, float32 c1, float32 c2, float32 c3);
float64 det2x2(float64 a, float64 b, float64 c, float64 d);
float64 det3x3(float64 a1, float64 a2, float64 a3, float64 b1, float64 b2, float64 b3, float64 c1, float64 c2, float64 c3);
float32 SquareRoot(float32 f);
float64 SquareRoot(float64 f);
float128 SquareRoot(float128 f);
float32 Square(float32 f);
float64 Square(float64 f);
float128 Square(float128 f);
extern float32 gf32Nan;
extern float64 gf64Nan;
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
class CNumberDetail
{
protected:
int16 mcMaxWholeNumbers;
int16 mcMaxDecimals;
int16 mcFirstDigit;
int16 mcLastDigit;
int16 mcFlags;
};
class CNumberControl;
class CNumber : public CNumberDetail
{
public:
char mcDigits[(26 + 16)];
CNumber* Init(void);
CNumber* Init(int32 iNumber);
CNumber* Init(float32 ff);
CNumber* Init(const char* szNumber, size iLen = 0);
CNumber* Init(CNumber* pcNumber);
CNumber* Zero(void);
CNumber* One(bool bPositive = true);
CNumber* Two(bool bPositive = true);
CNumber* Half(bool bPositive = true);
CNumber* Pi(bool bPositive = true);
CNumber* E(bool bPositive = true);
CNumber* Digit(char cValue);
CNumber* Digit(int16 iDigit, char cValue);
CNumber* Copy(CNumber* pcNumber);
CNumber* Init(int16 cMaxWholeNumbers, int16 cMaxDecimals);
CNumber* Init(int32 iNumber, int16 cMaxWholeNumbers, int16 cMaxDecimals);
CNumber* Init(float32 ff, int16 cMaxWholeNumbers, int16 cMaxDecimals);
CNumber* Init(const char* szNumber, int16 cMaxWholeNumbers, int16 cMaxDecimals, size iLen = 0);
CNumber* Init(CNumber* pcNumber, int16 cMaxWholeNumbers, int16 cMaxDecimals);
CNumber* Zero(int16 cMaxWholeNumbers, int16 cMaxDecimals);
CNumber* One(int16 cMaxWholeNumbers, int16 cMaxDecimals, bool bPositive = true);
CNumber* Two(int16 cMaxWholeNumbers, int16 cMaxDecimals, bool bPositive = true);
CNumber* Half(int16 cMaxWholeNumbers, int16 cMaxDecimals, bool bPositive = true);
CNumber* Pi(int16 cMaxWholeNumbers, int16 cMaxDecimals, bool bPositive = true);
CNumber* E(int16 cMaxWholeNumbers, int16 cMaxDecimals, bool bPositive = true);
CNumber* BinaryOne(int16 iBinaryExponent, int16 cMaxWholeNumbers, int16 cMaxDecimals);
CNumber* Digit(char cValue, int16 cMaxWholeNumbers, int16 cMaxDecimals);
CNumber* Digit(int16 iDigit, char cValue, int16 cMaxWholeNumbers, int16 cMaxDecimals);
CNumber* Copy(CNumber* pcNumber, int16 cMaxWholeNumbers, int16 cMaxDecimals);
CNumber* NotANumber(void);
CNumber* Overflow(int16 iSign);
CNumber* DivisionByZero(void);
void SetFirstNonZerotDigit(int16 iDigit);
void SetLastNonZeroDigit(int16 iDigit);
void SetSign(int16 iSign);
int16 GetSign(void);
void SetFlag(int16 iFlag);
void SetPositive(bool bPositive);
void ClearFlag(int16 iFlags);
int16 GetMaxWholeNumbers(void);
int16 GetMaxDecimals(void);
int16 GetFirstNonZeroDigit(void);
int16 GetLastNonZeroDigit(void);
int16 GetDecimals(void);
int16 GetWholeNumbers(void);
size GetDigitsBetween(void);
bool IsNAN(void);
bool IsUnderflow(void);
bool IsOverflow(void);
bool IsNegative(void);
bool IsPositive(void);
bool IsPositiveOrZero(void);
bool IsClean(void);
bool IsDivisionByZero(void);
bool IsError(void);
void AddBinaryOne(int16 iBinaryExponent);
void SetDigit(int16 iDigit, char cValue);
void SetDigitUnsafe(int16 iDigit, char cValue);
void Clean(void);
void CleanRight(void);
void CleanLeft(void);
char* DigitToArray(int16 iDigit);
int16 OffsetDigit(int16 iCurrentDigit, int16 iOffset);
size GetDigitsBetween(int16 iFirst, int16 iLast);
void RoundSignificant(int16 iSignificantDigits);
void PrivateZeroDigits(int16 iFirst, int16 iLast);
void PrivateZeroEnds(void);
bool IsInteger(void);
bool DigitsEqual(CNumber* pcTest, int16 iFirstDigit, int16 iLastDigit);
bool Equals(CNumber* pcNumber);
bool GreaterThan(CNumber* pcNumber);
bool LessThan(CNumber* pcNumber);
bool GreaterThanOrEquals(CNumber* pcNumber);
bool LessThanOrEquals(CNumber* pcNumber);
bool IsZero(void);
bool IsOdd(void);
bool IsEven(void);
void PrivateAdd(CNumber* pcNumber);
void PrivateSubtract(CNumber* pcNumber);
bool PrivateGreaterThan(CNumber* pcNumber);
bool PrivateGreaterThanOrEquals(CNumber* pcNumber);
char PrivateDivide(CNumber* pcDivisor, bool* pbExact);
void PrivateUnderflow(CNumber* pcNumber);
bool PrivateNAN(CNumber* pcNumber);
bool PrivateOverflow(CNumber* pcNumber);
bool PrivateDivisionByZero(CNumber* pcNumber);
bool PrivateError(CNumber* pcNumber);
void PrivateIntegerRoot(CNumber* pcRoot);
void PrivateIntegerExponent(CNumber* pcExponent);
void PrivateIntegerExponent(int16 iExponent);
void PrivateIntegerFactorial(int16 iN, int16 cMaxWholeNumbers, int16 cMaxDecimals);
void PrivateInit(void);
void PrivateInit(size cWholeNumbers, size cMaxDecimals);
void PrivateCopy(CNumber* pcNumber, int16 cMaxWholeNumbers, int16 cMaxDecimals);
bool PrivateEquals(CNumber* pcNumber, int16 iDecimals);
size PrivateGetIndex(int16 iDigit);
CNumber* Add(CNumber* pcNumber);
CNumber* Subtract(CNumber* pcNumber);
CNumber* Multiply(CNumber* pcNumber);
CNumber* Divide(CNumber* pcNumber);
CNumber* Inverse(void);
CNumber* Negate(void);
CNumber* Absolute(void);
CNumber* Decrement(void);
CNumber* Increment(void);
CNumber* Power(CNumber* pcExponentIn);
CNumber* Root(CNumber* pcRoot);
CNumber* Antilog(CNumber* pcBase);
CNumber* Exponential(void);
CNumber* Logarithm(CNumber* pcBase);
CNumber* NaturalLogarithm(void);
CNumber* CommonLogarithm(void);
CNumber* BinaryLogarithm(void);
CNumber* SquareRoot(void);
CNumber* CubeRoot(void);
CNumber* Squared(void);
CNumber* Cubed(void);
CNumber* InverseSquared(void);
CNumber* InverseCubed(void);
CNumber* Modulus(CNumber* pcNumber);
CNumber* ArithmeticGeometricMean(CNumber* pcOther);
CNumber* LogicalNot(void);
CNumber* LogicalOr(CNumber* pcRight);
CNumber* LogicalAnd(CNumber* pcRight);
CNumber* Sine(void);
CNumber* Cosine(void);
CNumber* Tangent(void);
CNumber* ArcSine(void);
CNumber* ArcCosine(void);
CNumber* ArcTangent(void);
CNumber* HyperbolicSine(void);
CNumber* HyperbolicCosine(void);
CNumber* HyperbolicTangent(void);
CNumber* DegreesToRadians(void);
CNumber* RadiansToDegrees(void);
CNumber* Shift(int16 iOffset);
CNumber* Truncate(int16 iDigit);
CNumber* TruncateHigh(int16 iDigit);
CNumber* Integer(void);
CNumber* Fractional(void);
CNumber* Ceiling(void);
CNumber* Floor(void);
int32 IntValue(void);
float32 FloatValue(void);
float64 DoubleValue(void);
uint64 ULongValue(void);
uint64 DecimalValue(uint16* puiNumDecimals);
char GetDigitUnsafe(int16 iDigit);
char SafeGetDigit(int16 iDigit);
void Print(CChars* pcChars);
bool PrintFloating(CChars* pcChars);
void Dump(void);
void Dump(bool bNewLine);
size ByteSize(void);
};
class CTextParser;
typedef void(*TextParserSkipWhitespace)(CTextParser*);
typedef TRISTATE(*TextParserParseString)(CTextParser*, char*, size*);
typedef TRISTATE (*TextParserParseExactIdentifier)(CTextParser*, const char*);
typedef TRISTATE (*TextParserParseIdentifier)(CTextParser*, char*, size*);
struct STextParserConfig
{
TextParserSkipWhitespace fSkipWhitespace;
TextParserParseString fParseString;
TextParserParseExactIdentifier fParseExactIdentifier;
TextParserParseIdentifier fParseIdentifier;
void Init(TextParserSkipWhitespace pfSkipWhitespace, TextParserParseString pfParseString, TextParserParseExactIdentifier pfParseExactIdentifier, TextParserParseIdentifier pfParseIdentifier);
};
struct STextPosition
{
const char* szPos;
size iLine;
size iColumn;
void Init(void);
void Init(const char* szPos, size iLine, size iColumn);
void Init(const char* szStartOfText, size iLength, const char* szPosition);
void Clear(void);
};
class CChars;
class CTextPositionPrinter
{
protected:
STextPosition mcTextPosition;
CExternalString mcText;
const char* mszFilename;
public:
void Init(CExternalString* pcText, STextPosition* pcTextPosition, const char* szFilename = 0L);
void Kill(void);
void PrintPosition(CChars* pszDest);
protected:
void PrintPositionSingleLineParser(CChars* pszDest);
void PrintPositionMultilineParser(CChars* pszDest);
size UsedLength(void);
};
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
struct SENode
{
int uiNum;
uint8 iFlags;
void* pvData;
char* szName;
size uiDataSize;
};
struct SEnumeratorIterator
{
bool bValid;
SENode* psNode;
};
typedef CLinkedListTemplate<SENode> CLinkListSENode;
template<class M>
class __CEnumeratorTemplate
{
public:
CArrayTemplatePrimitive<ptr> mcIDArray;
CLinkListSENode mcList;
bool mbCaseSensitive;
public:
void Init(void);
void Kill(void);
int Get(const char* szName, M** pvData);
int Get(const char* szName, size iNameLen, M** pvData);
int GetNumMatchingWithKey(char* szName, M* pvKey, size uiKeySize);
int GetWithKey(const char* szName, M* pvKey, size uiKeySize, M** pvData, int iMatchNum = 0, char** ppszName = 0L);
int GetWithKey(const char* szName, size iNameLen, M* pvKey, size uiKeySize, M** pvData, int iMatchNum = 0, char** ppszName = 0L);
bool GetWithID(size iID, M** pvData, char** pcName);
size NumElements(void);
void StartIteration(SEnumeratorIterator* psIterator, char** ppszName, size* piID, M** ppvData);
void Iterate(SEnumeratorIterator* psIterator, char** ppszName, size* piID, M** ppvData);
void Remove(size iID);
void Remove(const char* szName);
void Swap(SENode* psNode1, SENode* psNode2);
void SwapUp(char* szName);
void SwapDown(char* szName);
void BubbleSort(void);
void RecreateIDArray(void);
void AllocateNodeData(SENode* psNode, size iLen);
protected:
int PrivateAddGetNode(const char* szName, M* pvData, size uiDataSize, size uiKeySize, int uiNum, bool bReplace, SENode** pcThisNode);
SENode* PrivateGetWithKey(const char* szName, M* pvKey, size uiKeySize, SENode* psStartNode);
SENode* PrivateGetWithKey(const char* szName, size iNameLen, M* pvKey, size uiKeySize, SENode* psStartNode);
int PrivateGetNextID(int uiNum);
void PrivateInsertID(SENode* psNode);
void PrivateRemoveID(SENode* psNode);
void PrivateRemove(SENode* psNode);
bool PrivateCompare(const char* szName, M* pvKey, size uiKeySize, SENode* psNode);
bool PrivateCompare(const char* szName, size iNameLen, M* pvKey, size uiKeySize, SENode* psNode);
};
template<class M>
class CEnumeratorTemplate : public __CEnumeratorTemplate<M>
{
public:
using __CEnumeratorTemplate<M>::mcIDArray;
using __CEnumeratorTemplate<M>::mcList;
using __CEnumeratorTemplate<M>::mbCaseSensitive;
using __CEnumeratorTemplate<M>::AllocateNodeData;
int Add(const char* szName, M* pvData, int uiNum);
int Add(const char* szName, M* pvData, size uiKeySize, int uiNum, bool bReplace = true);
int Add(char* szName, size iNameLen, M* pvData, size uiKeySize, int uiNum, bool bReplace = true);
bool WriteEnumeratorBlock(CFileWriter* pcFileWriter);
bool ReadEnumeratorBlock(CFileReader* pcFileReader);
bool WriteEnumeratorTemplate(CFileWriter* pcFileWriter);
bool ReadEnumeratorTemplate(CFileReader* pcFileReader);
protected:
bool WriteNode(CFileWriter* pcFileWriter, SENode* psNode);
bool ReadNode(CFileReader* pcFileReader, SENode* psNode);
};
int AlphabeticalComparisionCallbackCaseSensitive(const void* pvNode1, const void* pvNode2);
int AlphabeticalComparisionCallbackCaseInsensitive(const void* pvNode1, const void* pvNode2);
template<class M>
void __CEnumeratorTemplate<M>::Init(void)
{
mbCaseSensitive = true;
mcIDArray.Init();
mcList.Init(&gcSystemAllocator);
}
template<class M>
void __CEnumeratorTemplate<M>::Kill(void)
{
SENode* psNode;
psNode = mcList.GetHead();
while (psNode)
{
if (psNode->pvData)
{
if (psNode->iFlags & 1)
{
mcList.Free(psNode->pvData);
psNode->pvData = 0L;
}
}
if (psNode->szName)
{
mcList.Free(psNode->szName);
}
psNode = mcList.GetNext(psNode);
}
mcIDArray.Kill();
mcList.Kill();
}
template<class M>
void __CEnumeratorTemplate<M>::AllocateNodeData(SENode* psNode, size iLen)
{
psNode->szName = (char*)mcList.Malloc(iLen);
if (psNode->uiDataSize)
{
psNode->pvData = mcList.Malloc(psNode->uiDataSize);
}
else
{
psNode->pvData = 0L;
}
}
template<class M>
int __CEnumeratorTemplate<M>::PrivateAddGetNode(const char* szName, M* pvData, size uiDataSize, size uiKeySize, int uiNum, bool bReplace, SENode** ppsThisNode)
{
SENode* psNode;
size iLen;
psNode = PrivateGetWithKey(szName, pvData, uiKeySize, 0L);
if (psNode && bReplace)
{
PrivateRemoveID(psNode);
psNode->uiNum = -1;
if (uiNum == -1)
{
psNode->uiNum = PrivateGetNextID(uiNum);
}
else
{
psNode->uiNum = uiNum;
}
PrivateInsertID(psNode);
if (pvData)
{
if (psNode->uiDataSize != uiDataSize)
{
if (psNode->iFlags & 1)
{
mcList.Free(psNode->pvData);
psNode->pvData = 0L;
}
}
if (uiDataSize)
{
if (psNode->pvData == 0L)
{
psNode->pvData = mcList.Malloc(uiDataSize);
}
psNode->iFlags = 1;
memcpy(psNode->pvData, pvData, uiDataSize);
}
else
{
psNode->iFlags = 0;
psNode->pvData = pvData;
}
psNode->uiDataSize = uiDataSize;
}
else
{
if (psNode->pvData)
{
if (psNode->iFlags & 1)
{
mcList.Free(psNode->pvData);
}
psNode->pvData = 0L;
}
}
psNode->iFlags = 0;
psNode->uiDataSize = 0;
if (ppsThisNode) { *ppsThisNode = psNode; };
return psNode->uiNum;
}
if (psNode)
{
if (ppsThisNode) { *ppsThisNode = psNode; };
return psNode->uiNum;
}
if (psNode == 0L)
{
iLen = (size)strlen(szName) + 1;
psNode = mcList.InsertAfterTail();
psNode->iFlags = 0;
psNode->uiNum = PrivateGetNextID(uiNum);
psNode->uiDataSize = uiDataSize;
AllocateNodeData(psNode, iLen);
if (uiDataSize)
{
psNode->iFlags = 1;
if (pvData)
{
memcpy(psNode->pvData, pvData, uiDataSize);
}
}
else
{
psNode->pvData = pvData;
}
strcpy(psNode->szName, szName);
PrivateInsertID(psNode);
if (ppsThisNode) { *ppsThisNode = psNode; };
return psNode->uiNum;
}
if (ppsThisNode) { *ppsThisNode = 0L; };
return -1;
}
template<class M>
void __CEnumeratorTemplate<M>::PrivateInsertID(SENode* psNode)
{
size iID;
iID = psNode->uiNum;
mcIDArray.AddRemap(iID, (ptr)psNode);
}
template<class M>
void __CEnumeratorTemplate<M>::PrivateRemoveID(SENode* psNode)
{
size iID;
iID = psNode->uiNum;
mcIDArray.RemoveRemap(iID);
}
template<class M>
SENode* __CEnumeratorTemplate<M>::PrivateGetWithKey(const char* szName, M* pvKey, size uiKeySize, SENode* psStartNode)
{
SENode* psNode;
if (psStartNode)
{
psNode = psStartNode;
}
else
{
psNode = mcList.GetHead();
}
while (psNode)
{
if (PrivateCompare(szName, pvKey, uiKeySize, psNode))
{
return psNode;
}
psNode = mcList.GetNext(psNode);
}
return 0L;
}
template<class M>
SENode* __CEnumeratorTemplate<M>::PrivateGetWithKey(const char* szName, size iNameLen, M* pvKey, size uiKeySize, SENode* psStartNode)
{
SENode* psNode;
if (psStartNode)
{
psNode = psStartNode;
}
else
{
psNode = mcList.GetHead();
}
while (psNode)
{
if (PrivateCompare(szName, iNameLen, pvKey, uiKeySize, psNode))
{
return psNode;
}
psNode = mcList.GetNext(psNode);
}
return 0L;
}
template<class M>
int __CEnumeratorTemplate<M>::PrivateGetNextID(int uiNum)
{
if (uiNum == -1)
{
return (int)mcIDArray.NumElements();
}
return uiNum;
}
template<class M>
int __CEnumeratorTemplate<M>::Get(const char* szName, M** ppvData)
{
return GetWithKey(szName, 0L, 0, ppvData);
}
template<class M>
int __CEnumeratorTemplate<M>::Get(const char* szName, size iNameLen, M** ppvData)
{
return GetWithKey(szName, iNameLen, 0L, 0, ppvData);
}
template<class M>
int __CEnumeratorTemplate<M>::GetNumMatchingWithKey(char* szName, M* pvKey, size uiKeySize)
{
SENode* psNode;
int uiNum;
SENode* psStart;
uiNum = 0;
psStart = mcList.GetHead();
for (;;)
{
psNode = PrivateGetWithKey(szName, pvKey, uiKeySize, psStart);
if (psNode)
{
uiNum++;
psStart = mcList.GetNext(psNode);
if (!psStart)
{
break;
}
}
else
{
break;
}
}
return uiNum;
}
template<class M>
int __CEnumeratorTemplate<M>::GetWithKey(const char* szName, M* pvKey, size uiKeySize, M** ppvData, int iMatchNum, char** ppszName)
{
SENode* psNode;
int uiNum;
SENode* psStart;
uiNum = 0;
psStart = mcList.GetHead();
for (;;)
{
psNode = PrivateGetWithKey(szName, pvKey, uiKeySize, psStart);
if (psNode)
{
if (uiNum == iMatchNum)
{
if (ppvData) { *ppvData = (M*)psNode->pvData; };
if (ppszName) { *ppszName = psNode->szName; };
return psNode->uiNum;
}
uiNum++;
psStart = mcList.GetNext(psNode);
if (!psStart)
{
break;
}
}
else
{
break;
}
}
return -1;
}
template<class M>
int __CEnumeratorTemplate<M>::GetWithKey(const char* szName, size iNameLen, M* pvKey, size uiKeySize, M** ppvData, int iMatchNum, char** ppszName)
{
SENode* psNode;
size uiNum;
SENode* psStart;
uiNum = 0;
psStart = mcList.GetHead();
for (;;)
{
psNode = PrivateGetWithKey(szName, iNameLen, pvKey, uiKeySize, psStart);
if (psNode)
{
if ((int)uiNum == iMatchNum)
{
if (ppvData) { *ppvData = (M*)psNode->pvData; };
if (ppszName) { *ppszName = psNode->szName; };
return psNode->uiNum;
}
uiNum++;
psStart = mcList.GetNext(psNode);
if (!psStart)
{
break;
}
}
else
{
break;
}
}
return -1;
}
template<class M>
bool __CEnumeratorTemplate<M>::GetWithID(size iID, M** ppvData, char** ppszName)
{
SENode* psNode;
if (iID == 0xffffffffU)
{
psNode = 0L;
}
else
{
psNode = (SENode*)mcIDArray.SafeGetValue(iID, (ptr)-1);
if (psNode == (void*)-1)
{
psNode = 0L;
}
}
if (psNode)
{
if (ppvData) { *ppvData = (M*)psNode->pvData; };
if (ppszName) { *ppszName = psNode->szName; };
return true;
}
else
{
if (ppvData) { *ppvData = 0L; };
if (ppszName) { *ppszName = 0L; };
return false;
}
}
template<class M>
bool __CEnumeratorTemplate<M>::PrivateCompare(const char* szName, M* pvKey, size uiKeySize, SENode* psNode)
{
size iVal;
if (mbCaseSensitive)
{
iVal = StringCompare(szName, psNode->szName);
}
else
{
iVal = StringInsensitiveCompare(szName, psNode->szName);
}
if (iVal == 0)
{
if (uiKeySize)
{
iVal = memcmp(pvKey, psNode->pvData, uiKeySize);
}
if (iVal == 0)
{
return true;
}
}
return false;
}
template<class M>
bool __CEnumeratorTemplate<M>::PrivateCompare(const char* szName, size iNameLen, M* pvKey, size uiKeySize, SENode* psNode)
{
size iVal;
if (mbCaseSensitive)
{
iVal = memcmp(szName, psNode->szName, iNameLen);
}
else
{
iVal = MemICmp(szName, psNode->szName, iNameLen);
}
if (iVal == 0)
{
if (uiKeySize)
{
iVal = memcmp(pvKey, psNode->pvData, uiKeySize);
}
if (iVal == 0)
{
return true;
}
}
return false;
}
template<class M>
size __CEnumeratorTemplate<M>::NumElements(void)
{
SENode* psNode;
size iCount;
iCount = 0;
psNode = mcList.GetHead();
while (psNode)
{
iCount++;
psNode = mcList.GetNext(psNode);
}
return iCount;
}
template<class M>
void __CEnumeratorTemplate<M>::StartIteration(SEnumeratorIterator* psIterator, char** ppszName, size* piID, M** ppvData)
{
psIterator->psNode = mcList.GetHead();
if (psIterator->psNode)
{
psIterator->bValid = true;
if (ppszName) { *ppszName = psIterator->psNode->szName; };
if (ppvData) { *ppvData = (M*)psIterator->psNode->pvData; };
if (piID) { *piID = psIterator->psNode->uiNum; };
}
else
{
if (ppszName) { *ppszName = 0L; };
psIterator->bValid = false;
}
}
template<class M>
void __CEnumeratorTemplate<M>::Iterate(SEnumeratorIterator* psIterator, char** ppszName, size* piID, M** ppvData)
{
psIterator->psNode = mcList.GetNext(psIterator->psNode);
if (psIterator->psNode)
{
psIterator->bValid = true;
if (ppszName) { *ppszName = psIterator->psNode->szName; };
if (ppvData) { *ppvData = (M*)psIterator->psNode->pvData; };
if (piID) { *piID = psIterator->psNode->uiNum; };
}
else
{
if (ppszName) { *ppszName = 0L; };
psIterator->bValid = false;
}
}
template<class M>
void __CEnumeratorTemplate<M>::PrivateRemove(SENode* psNode)
{
if (psNode)
{
if (psNode->iFlags & 1)
{
if (psNode->pvData)
{
mcList.Free(psNode->pvData);
psNode->pvData = 0L;
}
}
PrivateRemoveID(psNode);
mcList.Remove(psNode);
}
}
template<class M>
void __CEnumeratorTemplate<M>::Remove(size iID)
{
SENode* psNode;
if ((iID >= 0) && (iID < mcIDArray.NumElements()))
{
psNode = (SENode*)mcIDArray.GetValue(iID);
PrivateRemove(psNode);
}
}
template<class M>
void __CEnumeratorTemplate<M>::Remove(const char* szName)
{
SENode* psNode;
psNode = PrivateGetWithKey(szName, 0L, 0, 0L);
PrivateRemove(psNode);
}
template<class M>
void __CEnumeratorTemplate<M>::Swap(SENode* psNode1, SENode* psNode2)
{
mcList.Swap(psNode1, psNode2);
PrivateInsertID(psNode2);
PrivateInsertID(psNode1);
}
template<class M>
void __CEnumeratorTemplate<M>::SwapUp(char* szName)
{
SENode* psNode1;
SENode* psNode2;
psNode1 = PrivateGetWithKey(szName, 0L, 0, 0L);
if (psNode1)
{
psNode2 = mcList.GetPrev(psNode1);
if (psNode2)
{
Swap(psNode1, psNode2);
}
}
}
template<class M>
void __CEnumeratorTemplate<M>::SwapDown(char* szName)
{
SENode* psNode1;
SENode* psNode2;
psNode1 = PrivateGetWithKey(szName, 0L, 0, 0L);
if (psNode1)
{
psNode2 = mcList.GetNext(psNode1);
if (psNode2)
{
Swap(psNode1, psNode2);
}
}
}
template<class M>
void __CEnumeratorTemplate<M>::RecreateIDArray(void)
{
SENode* psNode;
mcIDArray.SetArrayValues((ptr)-1);
psNode = mcList.GetHead();
while (psNode)
{
PrivateInsertID(psNode);
psNode = mcList.GetNext(psNode);
}
}
template<class M>
void __CEnumeratorTemplate<M>::BubbleSort(void)
{
if (mbCaseSensitive)
{
mcList.BubbleSort(AlphabeticalComparisionCallbackCaseSensitive);
}
else
{
mcList.BubbleSort(AlphabeticalComparisionCallbackCaseInsensitive);
}
RecreateIDArray();
}
template<class M>
int CEnumeratorTemplate<M>::Add(const char* szName, M* pvData, int uiNum)
{
return CEnumeratorTemplate<M>::Add(szName, pvData, 0, uiNum, true);
}
template<class M>
int CEnumeratorTemplate<M>::Add(const char* szName, M* pvData, size uiKeySize, int uiNum, bool bReplace)
{
return __CEnumeratorTemplate<M>::PrivateAddGetNode(szName, pvData, sizeof(M), uiKeySize, uiNum, bReplace, 0L);
}
template<class M>
int CEnumeratorTemplate<M>::Add(char* szName, size iNameLen, M* pvData, size uiKeySize, int uiNum, bool bReplace)
{
char sz[1024];
memcpy(sz, szName, iNameLen);
sz[iNameLen] = 0;
return __CEnumeratorTemplate<M>::PrivateAddGetNode(sz, pvData, sizeof(M), uiKeySize, uiNum, bReplace, 0L);
}
template<class M>
bool CEnumeratorTemplate<M>::WriteEnumeratorTemplate(CFileWriter* pcFileWriter)
{
return WriteEnumeratorBlock(pcFileWriter);
}
template<class M>
bool CEnumeratorTemplate<M>::ReadEnumeratorTemplate(CFileReader* pcFileReader)
{
return ReadEnumeratorBlock(pcFileReader);
}
template<class M>
bool CEnumeratorTemplate<M>::WriteEnumeratorBlock(CFileWriter* pcFileWriter)
{
SENode* psNode;
if (!pcFileWriter->WriteBool(mbCaseSensitive))
{
return false;
}
if (!pcFileWriter->WriteSize(mcList.NumElements()))
{
return false;
}
psNode = mcList.GetHead();
while (psNode)
{
if (!WriteNode(pcFileWriter, psNode))
{
return false;
}
psNode = mcList.GetNext(psNode);
}
return true;
}
template<class M>
bool CEnumeratorTemplate<M>::ReadEnumeratorBlock(CFileReader* pcFileReader)
{
SENode* psNode;
size uiNumElements;
size i;
this->Init();
if (!pcFileReader->ReadBool(&mbCaseSensitive))
{
return false;
}
if (!pcFileReader->ReadSize(&uiNumElements))
{
return false;
}
for (i = 0; i < uiNumElements; i++)
{
psNode = mcList.InsertAfterTail();
if (!ReadNode(pcFileReader, psNode))
{
return false;
}
}
this->RecreateIDArray();
return true;
}
template<class M>
bool CEnumeratorTemplate<M>::WriteNode(CFileWriter* pcFileWriter, SENode* psNode)
{
if (!pcFileWriter->WriteInt32((int32)psNode->uiNum))
{
return false;
}
if (!pcFileWriter->WriteInt8(psNode->iFlags))
{
return false;
}
if (!pcFileWriter->WriteSize(psNode->uiDataSize))
{
return false;
}
if (!pcFileWriter->WriteString(psNode->szName))
{
return false;
}
if (psNode->uiDataSize)
{
if (!pcFileWriter->WriteData(psNode->pvData, psNode->uiDataSize))
{
return false;
}
}
return true;
}
template<class M>
bool CEnumeratorTemplate<M>::ReadNode(CFileReader* pcFileReader, SENode* psNode)
{
int32 iNum;
size iNameLength;
psNode->szName = 0L;
psNode->pvData = 0L;
psNode->uiDataSize = 0;
psNode->iFlags = 0;
if (!pcFileReader->ReadInt32(&iNum))
{
return false;
}
psNode->uiNum = iNum;
if (!pcFileReader->ReadInt8(&psNode->iFlags))
{
return false;
}
if (!pcFileReader->ReadSize(&psNode->uiDataSize))
{
return false;
}
if (!pcFileReader->ReadStringLength(&iNameLength))
{
return false;
}
AllocateNodeData(psNode, iNameLength);
if (!pcFileReader->ReadData(psNode->szName, iNameLength))
{
return false;
}
if (psNode->uiDataSize)
{
if (!pcFileReader->ReadData(psNode->pvData, psNode->uiDataSize))
{
return false;
}
}
return true;
}
typedef CArrayTemplate<STextPosition> CArrayTextPosition;
struct SParseState
{
STextPosition sCurrent;
CArrayTextPosition asPrev;
void Init(void);
void Kill(void);
};
enum ETextParseError
{
TPE_EndOfFile,
TPE_SyntaxError,
TPE_NotSet,
};
class CTextParser
{
public:
const char* mszStartOfText;
size miTextLen;
const char* mszParserPos;
const char* mszEndOfText;
bool mbCaseSensitive;
bool mbOutsideText;
CArrayTextPosition masPositions;
size miLine;
size miColumn;
bool mbAnnotated;
ETextParseError meError;
STextParserConfig msConfig;
bool Init(const char* szText, size iTextLen);
bool Init(const char* szText);
bool Init(CChars* szText);
bool Init(void);
bool Init(const char* szText, STextParserConfig* psConfig);
bool Init(const char* szText, size iTextLen, STextParserConfig* psConfig);
void Kill(void);
bool IsEmpty(void);
void SetStringParser(TextParserParseString fParseString);
void SetIdentifierParser(TextParserParseIdentifier fParseIdentifier);
void SetExactIdentifierParser(TextParserParseExactIdentifier fParseExactIdentifier);
void StepRight(void);
void StepLeft(void);
void TestEnd(void);
void SkipWhitespace(void);
void SkipNewLine(void);
void Restart(void);
void SaveState(SParseState* psTextPosition);
void LoadState(SParseState* psTextPosition);
void PushPosition(void);
void PopPosition(void);
void PassPosition(void);
bool IsWhitespace(char cCurrent);
void PassPositions(size iNum);
void PopPositions(size iNum);
void LastPosition(void);
STextPosition* GetPosition(STextPosition* psPosition);
void SetPosition(STextPosition* psPosition);
size Line(void);
size Column(void);
size Length(void);
size RemainingLength(void);
size UsedLength(void);
TRISTATE GetExactCharacter(char c, bool bSkipWhitespace = true);
TRISTATE GetExactCaseInsensitiveCharacter(char c, bool bSkipWhitespace = true);
TRISTATE GetEnumeratedCharacter(char* szCharacters, char* c, bool bSkipWhitespace = true);
TRISTATE GetCharacter(char* pc);
TRISTATE GetEscapeCode(char* c);
TRISTATE GetExactIdentifier(const char* szIdentifier, bool bSkipWhitespace = true);
TRISTATE GetIdentifier(char* szIdentifier, size* piLength = 0L, bool bSkipWhitespace = true);
TRISTATE GetString(char* szString, size* piLength = 0L, bool bSkipWhitespace = true);
TRISTATE GetExactCharacterSequence(const char* szSequence, bool bSkipWhitespace = true);
TRISTATE GetExactCaseInsensitiveCharacterSequence(const char* szSequence, bool bSkipWhitespace = true);
TRISTATE GetDigit(uint16* pi, uint16 uiBase = 10);
TRISTATE GetSign(int16* pi);
TRISTATE GetDigits(uint64* pulli, int16* piSign, uint16* puiNumDigits, bool bSkipWhitespace = true, bool bTestSign = true, uint16 uiBase = 10, uint16 uiAllowedSeparator = 0x0000);
TRISTATE GetInteger(uint64* pulli, int16* piSign, uint16* puiNumDigits = 0L, bool bSkipWhitespace = true);
TRISTATE GetInteger(int64* pi, uint16* puiNumDigits = 0L, bool bSkipWhitespace = true);
TRISTATE GetInteger(uint32* pui, int16* piSign, uint16* puiNumDigits = 0L, bool bSkipWhitespace = true);
TRISTATE GetInteger(int32* pi, uint16* puiNumDigits = 0L, bool bSkipWhitespace = true);
TRISTATE GetHexadecimal(uint64* pulli, uint16* puiNumDigits = 0L, bool bSkipWhitespace = true);
TRISTATE GetHexadecimalPart(uint64* pulli, uint16* puiNumDigits, uint16 iMaxDigits = 16);
TRISTATE GetOctal(uint64* pulli, uint16* puiNumDigits = 0L, bool bSkipWhitespace = true);
TRISTATE GetFloat(float* pf, bool bSkipWhitespace = true);
TRISTATE GetFloat(double* pf, bool bSkipWhitespace = true);
TRISTATE GetNumber(CNumber* pcNumber, bool bSkipWhitespace = true);
TRISTATE GetNumber(CNumber* pcNumber, int16 cMaxWholeNumbers, int16 cMaxDecimals, bool bSkipWhitespace = true);
TRISTATE GetIntegerLiteral(uint64* pulli, uint16 iAllowedPrefix, uint16* piBase, uint16 iAllowedSuffix, uint16* piSuffix, uint16 uiAllowedSeparator, uint16* puiNumDigits, bool bSkipWhitespace);
TRISTATE GetCharacterLiteral(uint16* pc, bool bAllowUTF16, uint16* piCharacterWidth, bool bSkipWhitespace);
TRISTATE GetStringLiteral(void* szDest, size uiDestByteLength, bool bAllowUTF16, size* piCharacterCount, uint16* piCharacterWidth, bool bSkipWhitespace);
TRISTATE GetFloatLiteral(float128* pldf, uint16 iAllowedPrefix, uint16* piBase, uint16 iAllowedSuffix, uint16* piSuffix, uint16 iAllowedExponent, uint16* piExponent, uint16 uiAllowedSeparator, uint16* piNumWholeDigits, uint16* piNumDecimalDigits, uint16* piNumExponentDigits, bool bSkipWhitespace);
TRISTATE FindExactIdentifier(char* szIdentifier);
TRISTATE FindExactCharacterSequence(const char* szSequence);
TRISTATE FindStartOfLine(void);
TRISTATE FindEndOfLine(void);
TRISTATE FindWhitespace(void);
TRISTATE GetHFExactIdentifierAndInteger(char* szIdentifier, int64* piInt);
TRISTATE GetHFExactIdentifierAndString(char* szIdentifier, char* szString);
TRISTATE GetHFOpeningQuote(char* pcDestQuoteType);
TRISTATE GetHFClosingQuote(char cQuoteType);
TRISTATE ReadLine(CTextParser* pcLine);
TRISTATE GetDebugCharacterSequence(char* szSequence);
TRISTATE SkipUTF8BOM(void);
void SetErrorEndOfFile(void);
void SetErrorSyntaxError(void);
void AppendError(CChars* pszDest);
void GetText(CExternalString* pcDest);
void PrintPosition(CChars* pszDest);
void PrintPositionSingleLineParser(CChars* pszDest);
void PrintPositionMultilineParser(CChars* pszDest);
bool IsOutside(void);
char Current(void);
char Current(int iIndex);
const char* Start(void);
const char* End(void);
const char* Position(void);
const char* Position(int iIndex);
void Dump(void);
template<class M> TRISTATE GetEnumeratorIdentifier(__CEnumeratorTemplate<M>* pcEnumerator, size* piID, bool bSkipWhitespace = true);
template<class M> TRISTATE GetEnumeratorSequence(__CEnumeratorTemplate<M>* pcEnumerator, size* piID, bool bSkipWhitespace = true);
void GetLineLocationMarkerString(CChars* pszDest);
protected:
TRISTATE GetSingleInteger(char cCurrent, uint64* pulli, uint16* piBase, uint16* puiNumDigits);
uint16 GetDigit(char cCurrent, uint16 uiBase);
bool IsDigit(char cCurrent, uint16 uiBase);
TRISTATE GetIntegerSuffix(uint16* piSuffix, uint16 iAllowedSuffix);
TRISTATE GetIntegerSeparator(uint16 uiAllowedSeparator);
TRISTATE GetCharacterLiteral(uint16* pc, bool bAllowUTF16, uint16* piCharacterWidth);
uint16 ChangeWidth(uint16 iWidth, uint16 iOldWidth, void* szDest, size uiDestByteLength, size iLength);
TRISTATE GetFloatSuffix(uint16* piSuffix, uint16 iAllowedSuffix);
float128 MakeLongDouble(uint16 uiBase, uint64 ulliWholeNumber, uint64 ulliDecimalNumber, uint16 iNumDecimalDigits, int64 lliExponentNumber);
};
TRISTATE ParseInteger(int64* pi, char* szText);
TRISTATE ParseFloat(double* pf, char* szText);
template<class M>
TRISTATE CTextParser::GetEnumeratorIdentifier(__CEnumeratorTemplate<M>* pcEnumerator, size* piID, bool bSkipWhitespace)
{
char* szName;
SEnumeratorIterator sIterator;
size iID;
TRISTATE tReturn;
size iLongestLength;
size iLength;
bool bFound;
STextPosition sStartPosition;
STextPosition sFoundPosition;
GetPosition(&sStartPosition);
if (bSkipWhitespace)
{
SkipWhitespace();
}
iLongestLength = 0;
bFound = false;
pcEnumerator->StartIteration(&sIterator, &szName, &iID, 0L);
while (sIterator.bValid)
{
tReturn = GetExactIdentifier(szName, false);
if (tReturn == TRITRUE)
{
iLength = strlen(szName);
if (iLength > iLongestLength)
{
iLongestLength = iLength;
*piID = iID;
bFound = true;
GetPosition(&sFoundPosition);
}
SetPosition(&sStartPosition);
}
else if (tReturn == TRIERROR)
{
return TRIERROR;
}
pcEnumerator->Iterate(&sIterator, &szName, &iID, 0L);
}
if (bFound)
{
SetPosition(&sFoundPosition);
return TRITRUE;
}
else
{
SetPosition(&sStartPosition);
*piID = ((size)-1);
return TRIFALSE;
}
}
template<class M>
TRISTATE CTextParser::GetEnumeratorSequence(__CEnumeratorTemplate<M>* pcEnumerator, size* piID, bool bSkipWhitespace)
{
char* szName;
SEnumeratorIterator sIterator;
size iID;
TRISTATE tReturn;
size iLongestLength;
size iLength;
bool bFound;
STextPosition sStartPosition;
STextPosition sFoundPosition;
GetPosition(&sStartPosition);
if (bSkipWhitespace)
{
SkipWhitespace();
}
iLongestLength = 0;
bFound = false;
pcEnumerator->StartIteration(&sIterator, &szName, &iID, 0L);
while(sIterator.bValid)
{
tReturn = GetExactCharacterSequence(szName, false);
if (tReturn == TRITRUE)
{
iLength = strlen(szName);
if (iLength > iLongestLength)
{
iLongestLength = iLength;
*piID = iID;
bFound = true;
GetPosition(&sFoundPosition);
}
SetPosition(&sStartPosition);
}
else if (tReturn == TRIERROR)
{
return TRIERROR;
}
pcEnumerator->Iterate(&sIterator, &szName, &iID, 0L);
}
if (bFound)
{
SetPosition(&sFoundPosition);
return TRITRUE;
}
else
{
SetPosition(&sStartPosition);
*piID = ((size)-1);
return TRIFALSE;
}
}
char GetEscapeCode(char cCurrent);
char* GetEscapeString(char cCurrent, char* szDest);
char* GetEscapeString(uint8 cCurrent, char* szDest);
char* GetEscapeString(char16 cCurrent, char* szDest);
void SkipCPPWhitespace(CTextParser* pcTextParser);
TRISTATE ParseCPPString(CTextParser* pcTextParser, char* szString, size* piLength);
TRISTATE ParseCPPExactIdentifier(CTextParser* pcTextParser, const char* szIdentifier);
TRISTATE ParseCPPIdentifier(CTextParser* pcTextParser, char* szIdentifier, size* piLength);
bool CTextParser::Init(const char* szText)
{
return Init(szText, strlen(szText));
}
bool CTextParser::Init(CChars* szText)
{
return Init(szText->Text(), szText->Length());
}
bool CTextParser::Init(void)
{
return Init(0L, (size)0);
}
bool CTextParser::Init(const char* szText, size iTextLen)
{
STextParserConfig sConfig;
sConfig.Init(SkipCPPWhitespace, ParseCPPString, ParseCPPExactIdentifier, ParseCPPIdentifier);
return Init(szText, iTextLen, &sConfig);
}
bool CTextParser::Init(const char* szText, STextParserConfig* psConfig)
{
return Init(szText, strlen(szText), psConfig);
}
bool CTextParser::Init(const char* szText, size iTextLen, STextParserConfig* psConfig)
{
msConfig = *psConfig;
if (szText == 0L)
{
meError = TPE_NotSet;
miLine = 0;
miColumn = 0;
mszStartOfText = 0L;
mszParserPos = 0L;
mszEndOfText = 0L;
miTextLen = 0;
mbCaseSensitive = true;
mbAnnotated = false;
mbOutsideText = true;
masPositions.Init();
return true;
}
else if (CountCarriageReturns(szText, iTextLen) == 0)
{
meError = TPE_NotSet;
miLine = 0;
miColumn = 0;
mszStartOfText = szText;
mszParserPos = szText;
mszEndOfText = &mszStartOfText[iTextLen - 1];
miTextLen = iTextLen;
mbCaseSensitive = true;
mbAnnotated = false;
TestEnd();
masPositions.Init();
PushPosition();
return true;
}
else
{
meError = TPE_NotSet;
miLine = 0;
miColumn = 0;
mszStartOfText = 0L;
mszParserPos = 0L;
mszEndOfText = 0L;
miTextLen = 0;
masPositions.Init();
gcLogger.Error2(MethodToString("/home/r2d2/Codaphela/commonlibraries/BaseLib/TextParser.cpp", 142, __PRETTY_FUNCTION__), " Parsed text contains carriage returns.", 0L);
return false;
}
}
void CTextParser::Kill(void)
{
mszParserPos = 0L;
mszStartOfText = 0L;
miTextLen = 0;
mszEndOfText = 0L;
masPositions.Pop();
masPositions.Kill();
}
bool CTextParser::IsEmpty(void)
{
return miTextLen <= 0;
}
void SParseState::Init(void)
{
sCurrent.Init();
asPrev.Init();
}
void SParseState::Kill(void)
{
sCurrent.Init();
asPrev.Kill();
}
void CTextParser::SetStringParser(TextParserParseString fParseString)
{
msConfig.fParseString = fParseString;
}
void CTextParser::SetIdentifierParser(TextParserParseIdentifier fParseIdentifier)
{
msConfig.fParseIdentifier = fParseIdentifier;
}
void CTextParser::SetExactIdentifierParser(TextParserParseExactIdentifier fParseExactIdentifier)
{
msConfig.fParseExactIdentifier = fParseExactIdentifier;
}
void CTextParser::StepRight(void)
{
if (mszParserPos <= mszEndOfText)
{
if (*mszParserPos == '\n')
{
miLine++;
miColumn = 0;
}
else
{
miColumn++;
}
mszParserPos = &mszParserPos[1];
}
TestEnd();
}
void CTextParser::StepLeft(void)
{
const char* szSearchPos;
if (mszParserPos >= mszStartOfText)
{
mszParserPos = &mszParserPos[-1];
if ((mszParserPos >= mszStartOfText) && (*mszParserPos == '\n'))
{
miLine--;
szSearchPos = &mszParserPos[-1];
miColumn = 0;
if (szSearchPos > mszStartOfText)
{
for (;;)
{
if ((*szSearchPos == '\n') || (szSearchPos == mszStartOfText))
{
break;
}
miColumn++;
szSearchPos = &szSearchPos[-1];
}
}
}
else
{
miColumn--;
}
}
TestEnd();
}
void CTextParser::TestEnd(void)
{
if ((mszParserPos >= mszStartOfText) && (mszParserPos <= mszEndOfText))
{
mbOutsideText = false;
return;
}
mbOutsideText = true;
}
bool CTextParser::IsWhitespace(char cCurrent)
{
return ((cCurrent == ' ') || (cCurrent == '\n') || (cCurrent == '\t'));
}
void CTextParser::SkipWhitespace(void)
{
msConfig.fSkipWhitespace(this);
}
void CTextParser::SkipNewLine(void)
{
char cCurrent;
if (mbOutsideText)
{
return;
}
cCurrent = mszParserPos[0];
if (cCurrent == '\n')
{
StepRight();
}
else if (mszParserPos == mszEndOfText)
{
StepRight();
}
}
TRISTATE CTextParser::GetExactCharacter(char c, bool bSkipWhitespace)
{
if (bSkipWhitespace)
{
SkipWhitespace();
}
if (!mbOutsideText)
{
if (*mszParserPos == c)
{
StepRight();
return TRITRUE;
}
return TRIFALSE;
}
else
{
SetErrorEndOfFile();
return TRIERROR;
}
}
TRISTATE CTextParser::GetExactCaseInsensitiveCharacter(char c, bool bSkipWhitespace)
{
char c1;
char c2;
if (bSkipWhitespace)
{
SkipWhitespace();
}
if (!mbOutsideText)
{
c1 = ToUpper(mszParserPos[0]);
c2 = ToUpper(c);
if (c1 == c2)
{
StepRight();
return TRITRUE;
}
return TRIFALSE;
}
else
{
SetErrorEndOfFile();
return TRIERROR;
}
}
TRISTATE CTextParser::GetEnumeratedCharacter(char* szCharacters, char* c, bool bSkipWhitespace)
{
size iNumCharacters;
char cCurrent;
TRISTATE tResult;
size i;
if (bSkipWhitespace)
{
SkipWhitespace();
}
iNumCharacters = strlen(szCharacters);
for (i = 0; i < iNumCharacters; i++)
{
cCurrent = szCharacters[i];
tResult = GetExactCharacter(cCurrent, false);
if (tResult == TRIERROR) { return TRIERROR; };
if (tResult == TRITRUE)
{
if (c != 0L)
{
*c = cCurrent;
return TRITRUE;
}
}
}
return TRIFALSE;
}
TRISTATE CTextParser::GetCharacter(char* pc)
{
if (!mbOutsideText)
{
*pc = mszParserPos[0];
StepRight();
return TRITRUE;
}
else
{
SetErrorEndOfFile();
return TRIERROR;
}
}
TRISTATE CTextParser::GetExactCharacterSequence(const char* szSequence, bool bSkipWhitespace)
{
char cCurrent;
size iPos;
iPos = 0;
PushPosition();
if (bSkipWhitespace)
{
SkipWhitespace();
}
if (mbOutsideText)
{
PopPosition();
SetErrorEndOfFile();
return TRIERROR;
}
for (;;)
{
if (szSequence[iPos] == 0)
{
PassPosition();
return TRITRUE;
}
if (!mbOutsideText)
{
cCurrent = mszParserPos[0];
if (cCurrent == szSequence[iPos])
{
StepRight();
iPos++;
}
else
{
PopPosition();
return TRIFALSE;
}
}
else
{
PopPosition();
return TRIFALSE;
}
}
}
TRISTATE CTextParser::GetExactCaseInsensitiveCharacterSequence(const char* szSequence, bool bSkipWhitespace)
{
size iPos;
char c1;
char c2;
PushPosition();
if (bSkipWhitespace)
{
SkipWhitespace();
}
iPos = 0;
if (mbOutsideText)
{
PopPosition();
SetErrorEndOfFile();
return TRIERROR;
}
for (;;)
{
if (szSequence[iPos] == 0)
{
PassPosition();
return TRITRUE;
}
if (!mbOutsideText)
{
c1 = ToUpper(mszParserPos[0]);
c2 = ToUpper(szSequence[iPos]);
if (c1 == c2)
{
StepRight();
iPos++;
}
else
{
PopPosition();
return TRIFALSE;
}
}
else
{
PopPosition();
return TRIFALSE;
}
}
}
TRISTATE CTextParser::GetDebugCharacterSequence(char* szSequence)
{
TRISTATE tResult;
PushPosition();
tResult = GetExactCharacterSequence(szSequence);
PopPosition();
return tResult;
}
TRISTATE CTextParser::SkipUTF8BOM(void)
{
TRISTATE tResult;
tResult = GetExactCharacterSequence("\xEF\xBB\xBF");
return tResult;
}
TRISTATE CTextParser::GetExactIdentifier(const char* szIdentifier, bool bSkipWhitespace)
{
TRISTATE tResult;
PushPosition();
if (bSkipWhitespace)
{
SkipWhitespace();
}
tResult = msConfig.fParseExactIdentifier(this, szIdentifier);
if ((tResult == TRIERROR) || (tResult == TRIFALSE))
{
PopPosition();
return tResult;
}
else
{
PassPosition();
return tResult;
}
}
TRISTATE CTextParser::GetIdentifier(char* szIdentifier, size* piLength, bool bSkipWhitespace)
{
TRISTATE tResult;
PushPosition();
if (bSkipWhitespace)
{
SkipWhitespace();
}
tResult = msConfig.fParseIdentifier(this, szIdentifier, piLength);
if ((tResult == TRIERROR) || (tResult == TRIFALSE))
{
PopPosition();
return tResult;
}
else
{
PassPosition();
return tResult;
}
}
TRISTATE CTextParser::GetString(char* szString, size* piLength, bool bSkipWhitespace)
{
TRISTATE tResult;
PushPosition();
if (bSkipWhitespace)
{
SkipWhitespace();
}
tResult = msConfig.fParseString(this, szString, piLength);
if ((tResult == TRIERROR) || (tResult == TRIFALSE))
{
PopPosition();
return tResult;
}
else
{
PassPosition();
return tResult;
}
}
TRISTATE CTextParser::GetEscapeCode(char* c)
{
char cReturn;
if (!mbOutsideText)
{
cReturn = ::GetEscapeCode(mszParserPos[0]);
if (cReturn == '@')
{
SetErrorSyntaxError();
return TRIERROR;
}
else
{
*c = cReturn;
}
StepRight();
return TRITRUE;
}
else
{
SetErrorEndOfFile();
return TRIERROR;
}
}
TRISTATE CTextParser::GetDigit(uint16* pi, uint16 uiBase)
{
char cCurrent;
uint16 iDigit;
if (!mbOutsideText)
{
cCurrent = mszParserPos[0];
iDigit = GetDigit(cCurrent, uiBase);
if (iDigit != 0xffff)
{
*pi = iDigit;
StepRight();
return TRITRUE;
}
else
{
return TRIFALSE;
}
}
else
{
SetErrorEndOfFile();
return TRIERROR;
}
}
uint16 CTextParser::GetDigit(char cCurrent, uint16 uiBase)
{
if (uiBase <= 10)
{
if ((cCurrent >= '0') && (cCurrent <= ('0' + uiBase - 1)))
{
return (uint16)(cCurrent - '0');
}
else
{
return 0xffff;
}
}
else
{
cCurrent = ToUpper(cCurrent);
if ((cCurrent >= '0') && (cCurrent <= '9'))
{
return (uint16)(cCurrent - '0');
}
else if ((cCurrent >= 'A') && (cCurrent <= ('A' + uiBase - 11)))
{
return (uint16)(cCurrent - 'A' + 10);
}
else
{
return 0xffff;
}
}
}
bool CTextParser::IsDigit(char cCurrent, uint16 uiBase)
{
if (uiBase <= 10)
{
if ((cCurrent >= '0') && (cCurrent <= ('0' + uiBase - 1)))
{
return true;
}
else
{
return false;
}
}
else
{
cCurrent = ToUpper(cCurrent);
if ((cCurrent >= '0') && (cCurrent <= '9'))
{
return true;
}
else if ((cCurrent >= 'A') && (cCurrent <= ('A' + uiBase - 11)))
{
return true;
}
else
{
return false;
}
}
}
TRISTATE CTextParser::GetIntegerSuffix(uint16* piSuffix, uint16 iAllowedSuffix)
{
char cCurrent;
bool bU;
bool bL;
if (!mbOutsideText)
{
bU = false;
bL = false;
PushPosition();
cCurrent = mszParserPos[0];
if ((iAllowedSuffix & 0x0100) || (iAllowedSuffix & 0x0080) || (iAllowedSuffix & 0x0040))
{
if ((cCurrent == 'u') || (cCurrent == 'U'))
{
bU = true;
StepRight();
if (mbOutsideText)
{
*piSuffix = 0x0040;
PassPosition();
return TRITRUE;
}
}
else if ((cCurrent == 'l') || (cCurrent == 'L'))
{
}
else
{
PopPosition();
return TRIFALSE;
}
}
cCurrent = mszParserPos[0];
if ((iAllowedSuffix & 0x0100) || (iAllowedSuffix & 0x0080) || (iAllowedSuffix & 0x0020) || (iAllowedSuffix & 0x0010))
{
if ((cCurrent == 'l') || (cCurrent == 'L'))
{
bL = true;
StepRight();
if (mbOutsideText)
{
if (bU)
{
*piSuffix = 0x0080;
}
else
{
*piSuffix = 0x0010;
}
PassPosition();
return TRITRUE;
}
}
else
{
if (bU && bL)
{
*piSuffix = 0x0080;
}
else if (bL && !bU)
{
*piSuffix = 0x0010;
}
else if (!bL && !bU)
{
*piSuffix = 0x0000;
}
PassPosition();
return TRITRUE;
}
}
cCurrent = mszParserPos[0];
if ((iAllowedSuffix & 0x0100) || (iAllowedSuffix & 0x0020))
{
if ((cCurrent == 'l') || (cCurrent == 'L'))
{
StepRight();
if (mbOutsideText)
{
if (bU && bL)
{
*piSuffix = 0x0100;
}
else if (!bU && bL)
{
*piSuffix = 0x0020;
}
else
{
PopPosition();
return TRIFALSE;
}
PassPosition();
return TRITRUE;
}
else
{
if (bU && bL)
{
*piSuffix = 0x0100;
}
else if (!bU && bL)
{
*piSuffix = 0x0020;
}
else
{
PopPosition();
return TRIFALSE;
}
PassPosition();
return TRITRUE;
}
}
else
{
if (bU && bL)
{
*piSuffix = 0x0080;
}
else if (!bU && bL)
{
*piSuffix = 0x0010;
}
else
{
PopPosition();
return TRIFALSE;
}
PassPosition();
return TRITRUE;
}
}
else
{
if (bU && bL)
{
*piSuffix = 0x0080;
}
else if (!bU && bL)
{
*piSuffix = 0x0010;
}
else
{
PopPosition();
return TRIFALSE;
}
PassPosition();
return TRITRUE;
}
PopPosition();
return TRIFALSE;
}
else
{
SetErrorEndOfFile();
return TRIERROR;
}
}
TRISTATE CTextParser::GetFloatSuffix(uint16* piSuffix, uint16 iAllowedSuffix)
{
char cCurrent;
if (!mbOutsideText)
{
PushPosition();
cCurrent = mszParserPos[0];
if ((iAllowedSuffix & 0x0200) && ((cCurrent == 'f') || (cCurrent == 'F')))
{
StepRight();
*piSuffix = 0x0200;
PassPosition();
return TRITRUE;
}
if ((iAllowedSuffix & 0x0400) && ((cCurrent == 'd') || (cCurrent == 'D')))
{
StepRight();
*piSuffix = 0x0400;
PassPosition();
return TRITRUE;
}
if ((iAllowedSuffix & 0x0800) && ((cCurrent == 'l') || (cCurrent == 'L')))
{
StepRight();
*piSuffix = 0x0400;
PassPosition();
return TRITRUE;
}
PopPosition();
return TRIFALSE;
}
else
{
SetErrorEndOfFile();
return TRIERROR;
}
}
TRISTATE CTextParser::GetSign(int16* pi)
{
char cCurrent;
if (!mbOutsideText)
{
*pi = 1;
cCurrent = mszParserPos[0];
if (cCurrent == '-')
{
*pi = -1;
StepRight();
return TRITRUE;
}
else if (cCurrent == '+')
{
StepRight();
return TRITRUE;
}
else return TRIFALSE;
}
else
{
SetErrorEndOfFile();
return TRIERROR;
}
}
TRISTATE CTextParser::GetInteger(uint64* pulli, int16* piSign, uint16* puiNumDigits, bool bSkipWhitespace)
{
TRISTATE tResult;
PushPosition();
if (bSkipWhitespace)
{
SkipWhitespace();
}
if (mbOutsideText)
{
PopPosition();
SetErrorEndOfFile();
return TRIERROR;
}
tResult = GetDigits(pulli, piSign, puiNumDigits, bSkipWhitespace);
if (tResult == TRITRUE)
{
if (*mszParserPos == '.')
{
PopPosition();
return TRIFALSE;
}
PassPosition();
return TRITRUE;
}
PopPosition();
return tResult;
}
TRISTATE CTextParser::GetInteger(int64* pi, uint16* puiNumDigits, bool bSkipWhitespace)
{
uint64 ulliTemp;
TRISTATE tReturn;
int16 iSign;
tReturn = GetInteger(&ulliTemp, &iSign, puiNumDigits, bSkipWhitespace);
*pi = ulliTemp * iSign;
return tReturn;
}
TRISTATE CTextParser::GetInteger(uint32* pui, int16* piSign, uint16* puiNumDigits, bool bSkipWhitespace)
{
uint64 ulliTemp;
TRISTATE tReturn;
int16 iSign;
tReturn = GetInteger(&ulliTemp, &iSign, puiNumDigits, bSkipWhitespace);
*pui = (uint32)ulliTemp;
return tReturn;
}
TRISTATE CTextParser::GetInteger(int32* pi, uint16* puiNumDigits, bool bSkipWhitespace)
{
uint64 ulliTemp;
TRISTATE tReturn;
int16 iSign;
tReturn = GetInteger(&ulliTemp, &iSign, puiNumDigits, bSkipWhitespace);
*pi = ((int32)ulliTemp) * iSign;
return tReturn;
}
TRISTATE CTextParser::GetIntegerLiteral(uint64* pulli, uint16 iAllowedPrefix, uint16* piBase, uint16 iAllowedSuffix, uint16* piSuffix, uint16 uiAllowedSeparator, uint16* puiNumDigits, bool bSkipWhitespace)
{
char cCurrent;
char cNext;
bool bFirstZero;
uint16 uiBase;
TRISTATE tResult;
uint16 iSuffix;
bool bSeparator;
PushPosition();
if (bSkipWhitespace)
{
SkipWhitespace();
}
uiBase = 10;
if (!mbOutsideText)
{
cCurrent = mszParserPos[0];
StepRight();
if (mbOutsideText)
{
if (piSuffix) { *piSuffix = 0x0000; };
return GetSingleInteger(cCurrent, pulli, piBase, puiNumDigits);
}
else
{
bFirstZero = cCurrent == '0';
cNext = mszParserPos[0];
if (bFirstZero)
{
if ((cNext == 'x' || cNext == 'X') && (iAllowedPrefix & 0x0004))
{
uiBase = 16;
}
else if ((cNext == 'b' || cNext == 'B') && (iAllowedPrefix & 0x0001))
{
uiBase = 2;
}
}
bSeparator = (((cNext == '_') && (uiAllowedSeparator & 0x4000)) ||
((cNext == '\'') && (uiAllowedSeparator & 0x8000)));
if (!IsDigit(cNext, uiBase) && uiBase == 10 && !bSeparator)
{
iSuffix = 0x0000;
tResult = GetIntegerSuffix(&iSuffix, iAllowedSuffix);
if (tResult == TRITRUE || tResult == TRIFALSE)
{
if (piSuffix) { *piSuffix = iSuffix; };
return GetSingleInteger(cCurrent, pulli, piBase, puiNumDigits);
}
else
{
PassPosition();
return TRIFALSE;
}
}
if (bFirstZero)
{
if (uiBase == 10)
{
if (cNext >= '0' && cNext <= '7')
{
uiBase = 8;
}
}
else
{
StepRight();
}
}
else
{
StepLeft();
}
tResult = GetDigits(pulli, 0L, puiNumDigits, false, false, uiBase, uiAllowedSeparator);
if (tResult == TRITRUE)
{
iSuffix = 0x0000;
if (!mbOutsideText)
{
tResult = GetIntegerSuffix(&iSuffix, iAllowedSuffix);
if (tResult == TRIERROR)
{
PassPosition();
return TRIERROR;
}
}
PassPosition();
if (piSuffix) { *piSuffix = iSuffix; };
if (piBase) { *piBase = uiBase; };
return TRITRUE;
}
else
{
PopPosition();
return tResult;
}
}
}
else
{
PopPosition();
SetErrorEndOfFile();
return TRIERROR;
}
}
TRISTATE CTextParser::GetFloatLiteral(float128* pldf, uint16 iAllowedPrefix, uint16* piBase, uint16 iAllowedSuffix, uint16* piSuffix, uint16 iAllowedExponent, uint16* piExponent, uint16 uiAllowedSeparator, uint16* piNumWholeDigits, uint16* piNumDecinalDigits, uint16* piNumExponentDigits, bool bSkipWhitespace)
{
char cCurrent;
char cNext;
bool bFirstZero;
uint16 uiBase;
TRISTATE tResult;
uint16 iSuffix;
uint16 iExponent;
uint64 ulliWholeNumber;
uint64 ulliDecimalNumber;
int64 lliExponentNumber;
float128 ldf;
uint16 iNumWholeDigits;
uint16 iNumDecimalDigits;
uint16 iNumExponentDigits;
int16 iSign;
PushPosition();
if (bSkipWhitespace)
{
SkipWhitespace();
}
uiBase = 10;
if (!mbOutsideText)
{
cCurrent = mszParserPos[0];
StepRight();
if (mbOutsideText)
{
PopPosition();
return TRIFALSE;
}
else
{
bFirstZero = cCurrent == '0';
cNext = mszParserPos[0];
if (bFirstZero)
{
if ((cNext == 'x' || cNext == 'X') && (iAllowedPrefix & 0x0004))
{
uiBase = 16;
StepRight();
cNext = mszParserPos[0];
}
}
if (uiBase != 16)
{
StepLeft();
}
tResult = GetDigits(&ulliWholeNumber, 0L, &iNumWholeDigits, false, false, uiBase, uiAllowedSeparator);
if (tResult == TRITRUE)
{
cCurrent = mszParserPos[0];
if (cCurrent == '.')
{
StepRight();
if (mbOutsideText)
{
PassPosition();
iExponent = 0;
iNumDecimalDigits = 0;
ulliDecimalNumber = 0;
lliExponentNumber = 0;
iNumExponentDigits = 0;
iSuffix = 0x0000;
ldf = MakeLongDouble(uiBase, ulliWholeNumber, ulliDecimalNumber, iNumDecimalDigits, lliExponentNumber);
if (pldf) { *pldf = ldf; };
if (piExponent) { *piExponent = iExponent; };
if (piNumWholeDigits) { *piNumWholeDigits = iNumWholeDigits; };
if (piNumDecinalDigits) { *piNumDecinalDigits = iNumDecimalDigits; };
if (piNumExponentDigits) { *piNumExponentDigits = iNumExponentDigits; };
if (piSuffix) { *piSuffix = iSuffix; };
if (piBase) { *piBase = uiBase; };
return TRITRUE;
}
iNumDecimalDigits = 0;
ulliDecimalNumber = 0;
tResult = GetDigits(&ulliDecimalNumber, 0L, &iNumDecimalDigits, false, false, uiBase, uiAllowedSeparator);
if (tResult == TRIERROR)
{
PassPosition();
return TRIERROR;
}
iExponent = 0x0000;
if (uiBase == 10)
{
cCurrent = mszParserPos[0];
if (cCurrent == 'E' || cCurrent == 'e')
{
iExponent = 0x1000;
StepRight();
if (!mbOutsideText)
{
tResult = GetDigits((uint64*)&lliExponentNumber, &iSign, &iNumExponentDigits, false, true, uiBase, uiAllowedSeparator);
if (tResult == TRIERROR)
{
PassPosition();
return TRIERROR;
}
}
else
{
PassPosition();
return TRIERROR;
}
}
else
{
lliExponentNumber = 0;
iNumExponentDigits = 0;
}
}
else if (uiBase == 16)
{
cCurrent = mszParserPos[0];
if (cCurrent == 'P' || cCurrent == 'p')
{
iExponent = 0x2000;
StepRight();
if (!mbOutsideText)
{
tResult = GetDigits((uint64*) &lliExponentNumber, &iSign, &iNumExponentDigits, false, true, 10, uiAllowedSeparator);
if (tResult == TRIERROR)
{
PassPosition();
return TRIERROR;
}
lliExponentNumber *= iSign;
}
else
{
PassPosition();
return TRIERROR;
}
}
else
{
lliExponentNumber = 0;
iNumExponentDigits = 0;
PassPosition();
return TRIERROR;
}
}
iSuffix = 0x0000;
if (!mbOutsideText)
{
tResult = GetFloatSuffix(&iSuffix, iAllowedSuffix);
if (tResult == TRIERROR)
{
PassPosition();
return TRIERROR;
}
}
PassPosition();
ldf = MakeLongDouble(uiBase, ulliWholeNumber, ulliDecimalNumber, iNumDecimalDigits, lliExponentNumber);
if (pldf) { *pldf = ldf; };
if (piExponent) { *piExponent = iExponent; };
if (piNumWholeDigits) { *piNumWholeDigits = iNumWholeDigits; };
if (piNumDecinalDigits) { *piNumDecinalDigits = iNumDecimalDigits; };
if (piNumExponentDigits) { *piNumExponentDigits = iNumExponentDigits; };
if (piSuffix) { *piSuffix = iSuffix; };
if (piBase) { *piBase = uiBase; };
return TRITRUE;
}
else
{
PopPosition();
return TRIFALSE;
}
}
else
{
PopPosition();
return tResult;
}
}
}
else
{
PopPosition();
SetErrorEndOfFile();
return TRIERROR;
}
}
float128 CTextParser::MakeLongDouble(uint16 uiBase, uint64 ulliWholeNumber, uint64 ulliDecimalNumber, uint16 iNumDecimalDigits, int64 lliExponentNumber)
{
float128 ldf;
float128 ldfPow;
float128 ldfExp;
if (uiBase == 10)
{
return ConvertDecimalFixedPointToLongDouble(ulliWholeNumber, ulliDecimalNumber, iNumDecimalDigits, lliExponentNumber);
}
else if (uiBase == 16)
{
ldf = (float128)ulliWholeNumber;
ldfPow = 1.l / powl(16, iNumDecimalDigits);
ldf += ulliDecimalNumber * ldfPow;
if (lliExponentNumber > 0)
{
ldfExp = powl(16, (float128)lliExponentNumber);
ldf *= ldfExp;
}
else if (lliExponentNumber < 0)
{
ldfExp = 1.l / powl(16, -((float128)lliExponentNumber));
ldf *= ldfExp;
}
return ldf;
}
else
{
gcLogger.Error2(MethodToString("/home/r2d2/Codaphela/commonlibraries/BaseLib/TextParser.cpp", 1554, __PRETTY_FUNCTION__), " Cannot make double with base [", IntToString(uiBase), "].", 0L);
return 0;
}
}
TRISTATE CTextParser::GetSingleInteger(char cCurrent, uint64* pulli, uint16* piBase, uint16* puiNumDigits)
{
if (cCurrent >= '0' && cCurrent <= '9')
{
PassPosition();
if (pulli) { *pulli = cCurrent - '0'; };
if (piBase) { *piBase = 10; };
if (puiNumDigits) { *puiNumDigits = 1; };
return TRITRUE;
}
else
{
PopPosition();
return TRIFALSE;
}
}
TRISTATE CTextParser::GetDigits(uint64* pulli, int16* piSign, uint16* puiNumDigits, bool bSkipWhitespace, bool bTestSign, uint16 uiBase, uint16 uiAllowedSeparator)
{
uint64 ulliValue;
int16 iSign;
uint16 iTemp;
TRISTATE tReturn;
bool bFirstDigit;
uint16 uiNumDigits;
PushPosition();
if (bSkipWhitespace)
{
SkipWhitespace();
}
*pulli = 0;
uiNumDigits = 0;
if (!mbOutsideText)
{
ulliValue = 0;
if (bTestSign)
{
GetSign(&iSign);
}
else
{
iSign = 1;
}
bFirstDigit = true;
bool bSeparator = false;
for (;;)
{
if (!mbOutsideText)
{
tReturn = GetDigit(&iTemp, uiBase);
if (tReturn == TRITRUE)
{
uiNumDigits++;
ulliValue *= uiBase;
ulliValue += iTemp;
bSeparator = false;
}
else if (tReturn == TRIFALSE)
{
if (!bSeparator)
{
tReturn = GetIntegerSeparator(uiAllowedSeparator);
if ((tReturn == TRIFALSE) || (tReturn == TRIERROR))
{
break;
}
else
{
bSeparator = true;
}
}
else
{
break;
}
}
else if (tReturn == TRIERROR)
{
break;
}
bFirstDigit = false;
}
else
{
break;
}
}
if (bSeparator)
{
PopPosition();
return TRIFALSE;
}
if (bFirstDigit)
{
PopPosition();
return TRIFALSE;
}
else
{
PassPosition();
if (piSign) { *piSign = iSign; };
if (pulli) { *pulli = ulliValue; };
if (puiNumDigits) { *puiNumDigits = uiNumDigits; };
return TRITRUE;
}
}
else
{
PopPosition();
SetErrorEndOfFile();
return TRIERROR;
}
}
TRISTATE CTextParser::GetIntegerSeparator(uint16 uiAllowedSeparator)
{
char cCurrent;
if (!mbOutsideText)
{
if (uiAllowedSeparator & 0x8000)
{
cCurrent = mszParserPos[0];
if (cCurrent == '\'')
{
StepRight();
return TRITRUE;
}
else
{
return TRIFALSE;
}
}
if (uiAllowedSeparator & 0x4000)
{
cCurrent = mszParserPos[0];
if (cCurrent == '_')
{
StepRight();
return TRITRUE;
}
else
{
return TRIFALSE;
}
}
else
{
return TRIFALSE;
}
}
else
{
SetErrorEndOfFile();
return TRIERROR;
}
}
TRISTATE CTextParser::GetHexadecimal(uint64* pulli, uint16* puiNumDigits, bool bSkipWhitespace)
{
TRISTATE tReturn;
PushPosition();
if (bSkipWhitespace)
{
SkipWhitespace();
}
tReturn = GetExactCharacter('0', false);
if (tReturn != TRITRUE)
{
PopPosition();
return tReturn;
}
tReturn = GetExactCaseInsensitiveCharacter('X', false);
if (tReturn != TRITRUE)
{
PopPosition();
return tReturn;
}
tReturn = GetHexadecimalPart(pulli, puiNumDigits);
if (tReturn != TRITRUE)
{
PopPosition();
}
else
{
PassPosition();
}
return tReturn;
}
TRISTATE CTextParser::GetHexadecimalPart(uint64* pulli, uint16* puiNumDigits, uint16 iMaxDigits)
{
uint64 iNum;
uint16 iTemp;
TRISTATE tReturn;
uint16 uiNumDigits;
*pulli = 0;
if (!mbOutsideText)
{
iNum = 0;
uiNumDigits = 0;
for (;;)
{
if (!mbOutsideText)
{
tReturn = GetDigit(&iTemp, 16);
if (tReturn == TRITRUE)
{
uiNumDigits++;
iNum *= 16;
iNum += iTemp;
if (uiNumDigits == iMaxDigits)
{
*pulli = iNum;
if (puiNumDigits) { *puiNumDigits = uiNumDigits; };
return TRITRUE;
}
}
else if ((tReturn == TRIFALSE) || (tReturn == TRIERROR))
{
*pulli = iNum;
if (puiNumDigits) { *puiNumDigits = uiNumDigits; };
return TRITRUE;
}
}
else
{
if (uiNumDigits != 0)
{
*pulli = iNum;
if (puiNumDigits) { *puiNumDigits = uiNumDigits; };
return TRITRUE;
}
SetErrorSyntaxError();
return TRIERROR;
}
}
}
else
{
SetErrorEndOfFile();
return TRIERROR;
}
}
TRISTATE CTextParser::GetOctal(uint64* pulli, uint16* puiNumDigits, bool bSkipWhitespace)
{
uint64 iNum;
uint16 iTemp;
TRISTATE tReturn;
uint16 uiNumDigits;
PushPosition();
if (bSkipWhitespace)
{
SkipWhitespace();
}
tReturn = GetExactCharacter('0', false);
if (tReturn != TRITRUE)
{
PopPosition();
return tReturn;
}
*pulli = 0;
uiNumDigits = 0;
if (!mbOutsideText)
{
iNum = 0;
for (;;)
{
if (!mbOutsideText)
{
tReturn = GetDigit(&iTemp, 8);
if (tReturn == TRITRUE)
{
uiNumDigits++;
iNum *= 8;
iNum += iTemp;
}
else if ((tReturn == TRIFALSE) || (tReturn == TRIERROR))
{
*pulli = iNum;
if (puiNumDigits) { *puiNumDigits = uiNumDigits; };
PassPosition();
return TRITRUE;
}
}
else
{
if (uiNumDigits != 0)
{
*pulli = iNum;
if (puiNumDigits) { *puiNumDigits = uiNumDigits; };
PassPosition();
return TRITRUE;
}
PopPosition();
SetErrorSyntaxError();
return TRIERROR;
}
}
}
else
{
PopPosition();
SetErrorEndOfFile();
return TRIERROR;
}
}
TRISTATE CTextParser::GetFloat(float* pf, bool bSkipWhitespace)
{
double d;
TRISTATE t;
t = GetFloat(&d, bSkipWhitespace);
if (t == TRITRUE)
{
*pf = (float)d;
}
return t;
}
TRISTATE CTextParser::GetFloat(double* pf, bool bSkipWhitespace)
{
uint64 ulliLeft;
uint64 ulliRight;
TRISTATE tReturn;
uint16 iNumDecimals;
double fLeft;
double fRight;
double fTemp;
bool bLeft;
int16 iSign;
int16 iLeftSign;
PushPosition();
if (bSkipWhitespace)
{
SkipWhitespace();
}
*pf = 0.0f;
if (!mbOutsideText)
{
tReturn = GetDigits(&ulliLeft, &iLeftSign, 0L);
bLeft = true;
if (tReturn == TRIFALSE)
{
ulliLeft = 0;
iLeftSign = 1;
bLeft = false;
}
else if (tReturn == TRIERROR)
{
PopPosition();
SetErrorSyntaxError();
return TRIERROR;
}
fLeft = ((double)ulliLeft) * iLeftSign;
if (!mbOutsideText)
{
tReturn = GetExactCharacter('.', false);
if (tReturn == TRITRUE)
{
tReturn = GetDigits(&ulliRight, &iSign, &iNumDecimals);
if (tReturn == TRITRUE)
{
if (iSign <= 0)
{
PopPosition();
SetErrorSyntaxError();
return TRIERROR;
}
fRight = (double)ulliRight;
fTemp = powl(10.0L, -(long double)iNumDecimals);
fRight *= fTemp;
if (iLeftSign >= 0)
{
*pf = fLeft + fRight;
}
else
{
*pf = fLeft - fRight;
}
PassPosition();
return TRITRUE;
}
else
{
PopPosition();
SetErrorSyntaxError();
return TRIERROR;
}
}
else if (tReturn == TRIFALSE)
{
if (!bLeft)
{
PopPosition();
return TRIFALSE;
}
else
{
*pf = fLeft;
PassPosition();
return TRITRUE;
}
}
else
{
PopPosition();
return TRIERROR;
}
}
else
{
if (!bLeft)
{
PopPosition();
return TRIFALSE;
}
else
{
*pf = fLeft;
PassPosition();
return TRITRUE;
}
}
}
else
{
PopPosition();
SetErrorEndOfFile();
return TRIERROR;
}
}
TRISTATE CTextParser::GetNumber(CNumber* pcNumber, bool bSkipWhitespace)
{
return GetNumber(pcNumber, 26, 16, bSkipWhitespace);
}
TRISTATE CTextParser::GetNumber(CNumber* pcNumber, int16 cMaxWholeNumbers, int16 cMaxDecimals, bool bSkipWhitespace)
{
const char* szStart;
double fIgnored;
TRISTATE tResult;
int16 iLength;
CNumber* pcResult;
PushPosition();
szStart = mszParserPos;
tResult = GetFloat(&fIgnored, bSkipWhitespace);
if (tResult == TRITRUE)
{
iLength = (int16)(mszParserPos - szStart);
pcResult = pcNumber->Init(szStart, cMaxWholeNumbers, cMaxDecimals, iLength);
if (pcResult->IsNAN())
{
PopPosition();
return TRIFALSE;
}
PassPosition();
return TRITRUE;
}
else
{
PopPosition();
return tResult;
}
}
void CTextParser::SaveState(SParseState* psParserState)
{
psParserState->Init();
psParserState->sCurrent.Init(mszParserPos, miLine, miColumn);
psParserState->asPrev.Copy(&masPositions);
}
void CTextParser::LoadState(SParseState* psParserState)
{
mszParserPos = psParserState->sCurrent.szPos;
miLine = psParserState->sCurrent.iLine;
miColumn = psParserState->sCurrent.iColumn;
masPositions.Copy(&psParserState->asPrev);
TestEnd();
}
TRISTATE CTextParser::FindExactIdentifier(char* szIdentifier)
{
const char* szPosition;
TRISTATE result;
PushPosition();
SkipWhitespace();
for (;;)
{
szPosition = mszParserPos;
result = GetExactIdentifier(szIdentifier);
if (result == TRIERROR)
{
PopPosition();
return TRIFALSE;
}
else if (result == TRIFALSE)
{
StepRight();
SkipWhitespace();
}
else if (result == TRITRUE)
{
mszParserPos = szPosition;
PassPosition();
return TRITRUE;
}
}
}
TRISTATE CTextParser::FindExactCharacterSequence(const char* szSequence)
{
const char* szPosition;
TRISTATE result;
PushPosition();
for (;;)
{
szPosition = mszParserPos;
result = GetExactCharacterSequence(szSequence, false);
if (result == TRIERROR)
{
PopPosition();
return TRIFALSE;
}
else if (result == TRIFALSE)
{
StepRight();
}
else if (result == TRITRUE)
{
mszParserPos = szPosition;
PassPosition();
return TRITRUE;
}
}
}
void CTextParser::Restart(void)
{
mszParserPos = mszStartOfText;
miLine = 0;
miColumn = 0;
masPositions.Kill();
masPositions.Init();
PushPosition();
TestEnd();
}
TRISTATE CTextParser::FindStartOfLine(void)
{
char cCurrent;
PushPosition();
if (mbOutsideText)
{
PopPosition();
SetErrorEndOfFile();
return TRIERROR;
}
for (;;)
{
cCurrent = mszParserPos[0];
StepLeft();
if (mbOutsideText)
{
mszParserPos = mszStartOfText;
miColumn = 0;
PassPosition();
return TRITRUE;
}
cCurrent = mszParserPos[0];
if (cCurrent == '\n')
{
StepRight();
PassPosition();
return TRITRUE;
}
}
}
TRISTATE CTextParser::FindEndOfLine(void)
{
char cCurrent;
PushPosition();
if (mbOutsideText)
{
PopPosition();
SetErrorEndOfFile();
return TRIERROR;
}
cCurrent = 0;
for (;;)
{
cCurrent = mszParserPos[0];
if (mbOutsideText)
{
mszParserPos = mszEndOfText;
miColumn--;
PassPosition();
return TRITRUE;
}
cCurrent = mszParserPos[0];
if (cCurrent == '\n')
{
PassPosition();
return TRITRUE;
}
StepRight();
}
}
TRISTATE CTextParser::FindWhitespace(void)
{
char cCurrent;
bool bStartOfComment;
bStartOfComment = false;
for (;;)
{
if (mbOutsideText)
{
return TRIFALSE;
}
cCurrent = mszParserPos[0];
if (IsWhitespace(cCurrent))
{
return TRITRUE;
}
if (bStartOfComment)
{
if ((cCurrent == '/') || (cCurrent == '*'))
{
StepLeft();
return TRITRUE;
}
}
if (cCurrent == '/')
{
bStartOfComment = true;
}
else
{
bStartOfComment = false;
}
StepRight();
}
}
TRISTATE CTextParser::GetHFExactIdentifierAndInteger(char* szIdentifier, int64* piInt)
{
TRISTATE tReturn;
PushPosition();
tReturn = GetExactIdentifier(szIdentifier);
if ((tReturn == TRIERROR) || (tReturn == TRIFALSE))
{
PopPosition();
return tReturn;
}
tReturn = GetInteger(piInt);
if ((tReturn == TRIERROR) || (tReturn == TRIFALSE))
{
PopPosition();
return tReturn;
}
PassPosition();
return TRITRUE;
}
TRISTATE CTextParser::GetHFExactIdentifierAndString(char* szIdentifier, char* szString)
{
TRISTATE tReturn;
PushPosition();
tReturn = GetExactIdentifier(szIdentifier);
if ((tReturn == TRIERROR) || (tReturn == TRIFALSE))
{
PopPosition();
return tReturn;
}
tReturn = GetString(szString);
if ((tReturn == TRIERROR) || (tReturn == TRIFALSE))
{
PopPosition();
return tReturn;
}
PassPosition();
return TRITRUE;
}
TRISTATE CTextParser::GetHFOpeningQuote(char* pcDestQuoteType)
{
TRISTATE tSingle;
TRISTATE tDouble;
tDouble = TRIFALSE;
tSingle = GetExactCharacter('\'');
if (tSingle == TRIERROR) { return TRIERROR; };
if (tSingle == TRIFALSE)
{
tDouble = GetExactCharacter('"');
gTriState = tDouble; if ((gTriState == TRIERROR) || (gTriState == TRIFALSE)) { return TRIERROR; };
*pcDestQuoteType = '"';
return TRITRUE;
}
else
{
*pcDestQuoteType = '\'';
return TRITRUE;
}
}
TRISTATE CTextParser::GetHFClosingQuote(char cQuoteType)
{
TRISTATE tResult;
tResult = GetExactCharacter(cQuoteType);
gTriState = tResult; if ((gTriState == TRIERROR) || (gTriState == TRIFALSE)) { return TRIERROR; };
return TRITRUE;
}
TRISTATE CTextParser::ReadLine(CTextParser* pcLine)
{
const char* szStart;
const char* szEnd;
pcLine->Init();
gTriState = FindStartOfLine(); if ((gTriState == TRIERROR) || (gTriState == TRIFALSE)) { return TRIERROR; };
szStart = mszParserPos;
gTriState = FindEndOfLine(); if ((gTriState == TRIERROR) || (gTriState == TRIFALSE)) { return TRIERROR; };
szEnd = mszParserPos;
SkipNewLine();
if (mbOutsideText)
{
szEnd++;
}
pcLine->Init(szStart, (size)(szEnd - szStart));
pcLine->mbAnnotated = mbAnnotated;
return TRITRUE;
}
void CTextParser::PushPosition(void)
{
STextPosition* psTextPosition;
psTextPosition = masPositions.Push();
psTextPosition->Init(mszParserPos, miLine, miColumn);
}
void CTextParser::PopPosition(void)
{
STextPosition sTextPosition;
masPositions.Pop(&sTextPosition);
miLine = sTextPosition.iLine;
miColumn = sTextPosition.iColumn;
mszParserPos = sTextPosition.szPos;
TestEnd();
}
void CTextParser::PassPosition(void)
{
masPositions.Pop();
TestEnd();
}
void CTextParser::PassPositions(size iNum)
{
if (iNum == 0)
{
return;
}
masPositions.RemoveRange(masPositions.NumElements()-iNum, masPositions.NumElements());
TestEnd();
}
void CTextParser::PopPositions(size iNum)
{
STextPosition* psTextPosition;
psTextPosition = masPositions.Get(masPositions.NumElements()-iNum-0);
miLine = psTextPosition->iLine;
miColumn = psTextPosition->iColumn;
mszParserPos = psTextPosition->szPos;
TestEnd();
masPositions.RemoveRange(masPositions.NumElements() - iNum, masPositions.NumElements());
}
void CTextParser::LastPosition(void)
{
STextPosition* psTextPosition;
psTextPosition = masPositions.Tail();
miLine = psTextPosition->iLine;
miColumn = psTextPosition->iColumn;
mszParserPos = psTextPosition->szPos;
TestEnd();
}
STextPosition* CTextParser::GetPosition(STextPosition* psPosition)
{
psPosition->Init(mszParserPos, miLine, miColumn);
return psPosition;
}
void CTextParser::SetPosition(STextPosition* psPosition)
{
miLine = psPosition->iLine;
miColumn = psPosition->iColumn;
mszParserPos = psPosition->szPos;
TestEnd();
}
size CTextParser::Line(void)
{
return miLine;
}
size CTextParser::Column(void)
{
return miColumn;
}
size CTextParser::Length(void)
{
return (size)(mszEndOfText - mszStartOfText) + 1;
}
size CTextParser::RemainingLength(void)
{
return (size)(mszEndOfText - mszParserPos) + 1;
}
size CTextParser::UsedLength(void)
{
return (size)(mszParserPos - mszStartOfText);
}
void CTextParser::SetErrorEndOfFile(void)
{
meError = TPE_EndOfFile;
}
void CTextParser::SetErrorSyntaxError(void)
{
meError = TPE_SyntaxError;
}
void CTextParser::AppendError(CChars* pszDest)
{
pszDest->Append("parser error [");
if (meError == TPE_NotSet)
{
pszDest->Append("Not Set");
}
else if (meError == TPE_EndOfFile)
{
pszDest->Append("End of File");
}
else if (meError == TPE_SyntaxError)
{
pszDest->Append("Syntax Error");
}
pszDest->Append("]");
}
void CTextParser::GetText(CExternalString* pcDest)
{
pcDest->Init(mszStartOfText, mszEndOfText);
}
void CTextParser::PrintPosition(CChars* pszDest)
{
CChars szParserText;
size iPreviousLineEnd;
size iLineEnd;
szParserText.Fake(mszStartOfText, 0, Length() - 1);
iPreviousLineEnd = szParserText.FindFromEnd(UsedLength() - 1, "\n");
iLineEnd = szParserText.Find(UsedLength(), "\n");
if (iPreviousLineEnd == ((size)-1) && iLineEnd == ((size)-1))
{
PrintPositionSingleLineParser(pszDest);
}
else
{
PrintPositionMultilineParser(pszDest);
}
}
void CTextParser::PrintPositionSingleLineParser(CChars* pszDest)
{
CExternalString pac;
size iBefore;
pac.Init(mszStartOfText, mszEndOfText);
pszDest->Append(&pac);
iBefore = mszParserPos - mszStartOfText;
pszDest->AppendNewLine();
pszDest->Append(' ', iBefore);
pszDest->Append('^');
pszDest->AppendNewLine();
}
void CTextParser::PrintPositionMultilineParser(CChars* pszDest)
{
CChars szParserLine;
CExternalString pac;
CChars szParserText;
size iPreviousLineEnd;
size iLineEnd;
size iParserPos;
CChars szLine;
szParserText.Fake(mszStartOfText, 0, Length() - 1);
iPreviousLineEnd = szParserText.FindFromEnd(UsedLength() - 1, "\n");
iLineEnd = szParserText.Find(UsedLength(), "\n");
if (iPreviousLineEnd == ((size)-1))
{
iPreviousLineEnd = 0;
}
if (iLineEnd == ((size)-1))
{
iLineEnd = Length();
}
pac.Init(&mszStartOfText[iPreviousLineEnd], &mszStartOfText[iLineEnd]);
iParserPos = mszParserPos - mszStartOfText;
szParserLine.Init(&pac);
szParserLine.Replace("\n", " ");
szParserLine.Replace("\r", "");
szLine.Init();
szLine.Append('[');
szLine.Append(miLine + 1);
szLine.Append("]: ");
pszDest->Append(szLine);
pszDest->Append(szParserLine);
pszDest->AppendNewLine();
pszDest->Append(' ', szLine.Length());
pszDest->Append(' ', iParserPos - iPreviousLineEnd);
pszDest->Append('^');
pszDest->AppendNewLine();
szLine.Kill();
szParserLine.Kill();
}
bool CTextParser::IsOutside(void)
{
return mbOutsideText;
}
char CTextParser::Current(void)
{
return mszParserPos[0];
}
char CTextParser::Current(int iIndex)
{
return mszParserPos[iIndex];
}
const char* CTextParser::Position(void)
{
return mszParserPos;
}
const char* CTextParser::Position(int iIndex)
{
return &mszParserPos[iIndex];
}
const char* CTextParser::Start(void)
{
return mszStartOfText;
}
const char* CTextParser::End(void)
{
return mszEndOfText;
}
void CTextParser::Dump(void)
{
CChars sz;
sz.Init();
PrintPosition(&sz);
sz.DumpKill();
}
TRISTATE ParseInteger(int64* pi, char* szText)
{
CTextParser cTextParser;
TRISTATE tResult;
cTextParser.Init(szText);
tResult = cTextParser.GetInteger(pi);
cTextParser.Kill();
return tResult;
}
TRISTATE ParseFloat(double* pf, char* szText)
{
CTextParser cTextParser;
TRISTATE tResult;
double f;
int64 iExponent;
uint16 iTemp;
double fTen;
cTextParser.Init(szText);
tResult = cTextParser.GetFloat(&f);
if (tResult == TRITRUE)
{
tResult = cTextParser.GetExactCaseInsensitiveCharacter('e', false);
if (tResult == TRITRUE)
{
tResult = cTextParser.GetInteger(&iExponent, &iTemp, false);
if (tResult == TRITRUE)
{
fTen = 10.0;
*pf = pow(fTen, (double)iExponent) * f;
return TRITRUE;
}
else
{
return TRIFALSE;
}
}
else
{
*pf = f;
return TRITRUE;
}
}
else
{
return TRIFALSE;
}
cTextParser.Kill();
return tResult;
}
TRISTATE CTextParser::GetCharacterLiteral(uint16* pc, bool bAllowUTF16, uint16* piCharacterWidth, bool bSkipWhitespace)
{
TRISTATE tResult;
uint16 iWidth;
uint16 ui;
PushPosition();
if (bSkipWhitespace)
{
SkipWhitespace();
}
tResult = GetExactCharacter('\'', false);
if (tResult == TRITRUE)
{
tResult = GetCharacterLiteral(&ui, bAllowUTF16, &iWidth);
if (tResult == TRITRUE)
{
tResult = GetExactCharacter('\'', false);
if (tResult == TRITRUE)
{
PassPosition();
if (piCharacterWidth) { *piCharacterWidth = iWidth; };
if (pc) { *pc = ui; };
return TRITRUE;
}
else if (tResult == TRIFALSE)
{
PopPosition();
return TRIFALSE;
}
else
{
PassPosition();
return TRIERROR;
}
}
else if (tResult == TRIFALSE)
{
PopPosition();
return TRIFALSE;
}
else
{
PassPosition();
return TRIERROR;
}
}
else if (tResult == TRIFALSE)
{
PopPosition();
return TRIFALSE;
}
else
{
PassPosition();
return TRIERROR;
}
}
TRISTATE CTextParser::GetCharacterLiteral(uint16* pc, bool bAllowUTF16, uint16* piCharacterWidth)
{
TRISTATE tResult;
char c;
char cEscape;
uint16 iWidth;
uint16 ui;
uint64 ulli;
uint16 iNumDigits;
tResult = GetCharacter(&c);
if (tResult == TRITRUE)
{
if (c == '\\')
{
tResult = GetCharacter(&c);
if (tResult == TRITRUE)
{
cEscape = ::GetEscapeCode(c);
if (cEscape != '@' && cEscape != 0)
{
ui = cEscape;
iWidth = 1;
}
else if (IsDigit(c, 8))
{
StepLeft();
tResult = GetDigits(&ulli, 0L, &iNumDigits, false, false, 8, 0x0000);
if (tResult == TRITRUE)
{
if (ulli < 0x100)
{
ui = (uint16)ulli;
iWidth = 1;
}
else
{
return TRIERROR;
}
}
else
{
return TRIERROR;
}
}
else if (c == 'x')
{
tResult = GetDigits(&ulli, 0L, &iNumDigits, false, false, 16, 0x0000);
if (tResult == TRITRUE)
{
if (iNumDigits >= 1 && iNumDigits <= 4)
{
ui = (uint16)ulli;
if (ulli < 0x100)
{
iWidth = 1;
}
else if (ulli < 0x10000)
{
iWidth = 2;
}
else
{
return TRIERROR;
}
}
else
{
return TRIERROR;
}
}
else if (tResult == TRIFALSE)
{
return TRIFALSE;
}
else
{
return TRIERROR;
}
}
else if (c == 'u')
{
tResult = GetDigits(&ulli, 0L, &iNumDigits, false, false, 16, 0x0000);
if (tResult == TRITRUE)
{
ui = (uint16)ulli;
if (iNumDigits == 4)
{
iWidth = 2;
}
else
{
return TRIERROR;
}
}
else if (tResult == TRIFALSE)
{
return TRIFALSE;
}
else
{
return TRIERROR;
}
}
else if ((cEscape == '@') && (c == '\n'))
{
return TRIGNORED;
}
else
{
return TRIERROR;
}
*piCharacterWidth = iWidth;
*pc = ui;
return tResult;
}
else
{
return tResult;
}
}
else
{
ui = c;
iWidth = 1;
}
*piCharacterWidth = iWidth;
*pc = ui;
return tResult;
}
else
{
return TRIERROR;
}
}
TRISTATE CTextParser::GetStringLiteral(void* szDest, size uiDestByteLength, bool bAllowUTF16, size* piCharacterCount, uint16* piCharacterWidth, bool bSkipWhitespace)
{
TRISTATE tResult;
uint16 iWidth;
uint16 ui;
size iPosition;
uint16 iOldWidth;
PushPosition();
if (bSkipWhitespace)
{
SkipWhitespace();
}
tResult = GetExactCharacter('"', false);
iOldWidth = 0;
if (tResult == TRITRUE)
{
iPosition = 0;
for (;;)
{
tResult = GetExactCharacter('"', false);
if (tResult == TRITRUE)
{
if ((iOldWidth == 1) || (iOldWidth == 0))
{
((char*)(szDest))[iPosition] = '\0';
iOldWidth = 1;
}
else if (iOldWidth == 2)
{
((uint16*)(szDest))[iPosition] = 0;
}
if (piCharacterCount) { *piCharacterCount = iPosition; };
if (piCharacterWidth) { *piCharacterWidth = iOldWidth; };
PassPosition();
return TRITRUE;
}
else if (tResult == TRIERROR)
{
PassPosition();
return TRIERROR;
}
tResult = GetCharacterLiteral(&ui, bAllowUTF16, &iWidth);
if (tResult == TRITRUE)
{
iOldWidth = ChangeWidth(iWidth, iOldWidth, szDest, uiDestByteLength, iPosition);
if (iOldWidth == 1)
{
((char*)(szDest))[iPosition] = (char)ui;
}
else if (iOldWidth == 2)
{
((uint16*)(szDest))[iPosition] = ui;
}
else if (iOldWidth == 0xffff)
{
PopPosition();
return TRIERROR;
}
iPosition++;
}
else if (tResult == TRIFALSE)
{
PopPosition();
return TRIFALSE;
}
else
{
PassPosition();
return TRIERROR;
}
}
}
else if (tResult == TRIFALSE)
{
PopPosition();
return TRIFALSE;
}
else
{
PassPosition();
return TRIERROR;
}
}
uint16 CTextParser::ChangeWidth(uint16 iWidth, uint16 iOldWidth, void* szDest, size uiDestByteLength, size iLength)
{
size i;
size iByte;
char c;
if (iWidth == iOldWidth)
{
return iWidth;
}
if (iLength == 0)
{
return iWidth;
}
if ((iOldWidth == 1) && (iWidth == 2))
{
if ((iLength * 2) > uiDestByteLength)
{
return 0;
}
if (iLength != 0)
{
i = iLength;
do
{
i--;
iByte = i * 2;
c = ((char*)szDest)[i];
((char*)szDest)[iByte + 1] = '\0';
((char*)szDest)[iByte] = c;
}
while (i != 0);
}
return iWidth;
}
else if ((iOldWidth == 2) && (iWidth == 1))
{
return iOldWidth;
}
else
{
gcLogger.Error2(MethodToString("/home/r2d2/Codaphela/commonlibraries/BaseLib/TextParser.cpp", 3314, __PRETTY_FUNCTION__), " Cannot convert string with character width [", IntToString(iOldWidth), "] to new character width [", IntToString(iWidth), "].", 0L);
return 0xffff;
}
}
void CTextParser::GetLineLocationMarkerString(CChars* pszDest)
{
STextPosition sState;
TRISTATE tResult;
const char* szStartOfLine;
const char* szEndOfLine;
CChars szMarker;
GetPosition(&sState);
tResult = FindStartOfLine();
if (tResult != TRITRUE)
{
pszDest->Append("!! Could not find start of line at parser position [");
pszDest->Append((ptrdiff)(sState.szPos - mszStartOfText));
pszDest->Append("] !!");
return;
}
szStartOfLine = mszParserPos;
SetPosition(&sState);
tResult = FindEndOfLine();
if (tResult != TRITRUE)
{
pszDest->Append("!! Could not find end of line at parser position [");
pszDest->Append((ptrdiff)(sState.szPos - mszStartOfText));
pszDest->Append("] !!");
return;
}
szEndOfLine = mszParserPos;
SetPosition(&sState);
pszDest->AppendSubString(szStartOfLine, szEndOfLine);
pszDest->AppendNewLine();
szMarker.Init();
szMarker.AppendSubString(szStartOfLine, mszParserPos);
szMarker.ReplaceNonTabsWithSpace();
pszDest->Append(szMarker);
szMarker.Kill();
pszDest->Append('^');
}
