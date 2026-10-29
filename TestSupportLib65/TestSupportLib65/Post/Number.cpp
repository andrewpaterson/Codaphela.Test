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
class CFileReader;
class CFileWriter;
enum EPrimitiveType
{
PT_Undefined,
PT_int8,
PT_int16,
PT_int32,
PT_int64,
PT_uint8,
PT_uint16,
PT_uint32,
PT_uint64,
PT_float32,
PT_float64,
PT_float96,
PT_char8,
PT_char16,
PT_M2float32,
PT_M3float32,
PT_M4float32,
PT_M2float64,
PT_M3float64,
PT_M4float64,
PT_M2int32,
PT_M3int32,
PT_M4int32,
PT_bool,
PRIMTIVE_OPERATOR_END,
PT_bit,
PT_crumb,
PT_tribble,
PT_nybble,
PT_nickle,
PT_sixbits,
PRIMTIVE_CONVERTER_END,
PT_M4x4float32,
PT_M4x4float64,
PT_String,
PT_StringImmutable,
PT_Number,
PT_Date,
PT_DateTime,
PT_void,
PT_Pointer,
PT_Data,
PT_Enum,
PT_char8Pointer,
PT_char16Pointer,
PT_int,
PT_uint,
PT_size,
NUM_PRIMITIVE_TYPES,
CLASS_TYPES = 0x80,
};
EPrimitiveType IntPrimitive(void);
EPrimitiveType SizePrimitive(void);
EPrimitiveType UIntPrimitive(void);
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
struct SStackMark
{
size miUsedMemory;
size miElements;
void Init(size iUsedMemory, size iElements);
};
typedef CArrayTemplate<SStackMark> CArrayStackMarks;
class CStackMarkExtended
{
public:
CArrayStackMarks mcMarks;
size muiElements;
void Init(size iElements);
void Kill(void);
void Add(SStackMark sMark);
};
class CMemoryStack
{
protected:
void* mpvMemory;
size miMemorySize;
size miUsedMemory;
size miElements;
public:
void Init(size iSize);
void* Allocate(size iSize);
void Clear(void);
void Kill(void);
void* Add(size iSize);
void Remove(void);
void Remove(size iNumToRemove);
SStackMark Mark(void);
void Rollback(SStackMark* psMark);
size GetTotalMemory(void);
size GetUsedMemory(void);
size GetRemainingMemory(void);
void* GetData(void);
size NumElements(void);
};
typedef CArrayTemplate<CMemoryStack> CArrayMemoryStack;
class CMemoryStackExtended
{
protected:
CArrayMemoryStack mcStacks;
size muiChunkSize;
size muiElements;
public:
void Init(size iChunkSize);
void Clear(void);
void Kill(void);
void* Add(size iSize);
void Remove(void);
void Remove(size iNumToRemove);
void Mark(CStackMarkExtended* psMark);
void Rollback(CStackMarkExtended* psMark);
size GetTotalMemory(void);
size GetUsedMemory(void);
CMemoryStack* GetStack(size iIndex);
size NumStacks(void);
size NumElements(void);
};
struct SSPNode
{
public:
size iSize;
bool bUsed;
};
struct SScratchPadParams
{
int32 iChunkSize;
};
class CScratchPad
{
protected:
CMemoryStackExtended mcScratchPad;
size miSourceChunkSize;
public:
void Init(void);
void Init(size uiChunkSize);
void Kill(void);
void* Add(size uiSize);
void Reset(void);
size GetMemorySize(void);
size GetUsedSize(void);
void GetParams(SScratchPadParams* psParams);
};
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
class CNumberControl
{
protected:
CMemoryStackExtended mcScratchPad;
CNumber mc_pi;
CNumber mc_e;
union { CNumber c; char a[(1 + 255 + sizeof(CNumberDetail))]; } mc_pi_lots;
union { CNumber c; char a[(1 + 255 + sizeof(CNumberDetail))]; } mc_e_lots;
public:
void Init(size uiScratchPadSize);
void Kill(void);
void Pi(CNumber* pcDest, bool bPositive = true);
void Pi(CNumber* pcDest, int16 cMaxWholeNumbers, int16 cMaxDecimals, bool bPositive = true);
void E(CNumber* pcDest, bool bPositive = true);
void E(CNumber* pcDest, int16 cMaxWholeNumbers, int16 cMaxDecimals, bool bPositive = true);
CNumber* Add(void);
CNumber* Add(int16 cMaxWholeNumbers, int16 cMaxDecimals);
void Remove(void);
void Remove(int iNumToRemove);
int NumElements(void);
};
extern CNumberControl gcNumberControl;
extern bool gbNumberControl;
void NumberInit(size uiScratchPadSize = (1 *(1024LL*1024LL)));
void NumberKill(void);
bool IsNumberControlInitialised(void);
bool FailNumberControlInitialised(char* szMethod);
int ComparePtr(const void* arg1, const void* arg2);
int ComparePtrPtr(const void* arg1, const void* arg2);
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
void CNumber::PrivateInit(void)
{
memset(this, 0, (26 + 16 + sizeof(CNumberDetail)));
mcMaxWholeNumbers = 26;
mcMaxDecimals = 16;
}
void CNumber::PrivateInit(size cWholeNumbers, size cMaxDecimals)
{
memset(this, 0, (cWholeNumbers + cMaxDecimals + sizeof(CNumberDetail)));
mcMaxWholeNumbers = (int16)cWholeNumbers;
mcMaxDecimals = (int16)cMaxDecimals;
}
CNumber* CNumber::Init(int16 cMaxWholeNumbers, int16 cMaxDecimals)
{
PrivateInit(cMaxWholeNumbers, cMaxDecimals);
SetFirstNonZerotDigit(1);
SetLastNonZeroDigit(1);
SetSign(1);
return this;
}
CNumber* CNumber::Init(void)
{
PrivateInit();
SetFirstNonZerotDigit(1);
SetLastNonZeroDigit(1);
SetSign(1);
return this;
}
CNumber* CNumber::Init(int32 iNumber, int16 cMaxWholeNumbers, int16 cMaxDecimals)
{
int32 iRemainder;
int16 iCount;
int16 iIndex;
PrivateInit(cMaxWholeNumbers, cMaxDecimals);
SetLastNonZeroDigit(1);
if (iNumber < 0)
{
iNumber = -iNumber;
SetSign(-1);
}
else
{
SetSign(1);
}
iCount = 0;
for (;;)
{
iRemainder = iNumber % 10;
iNumber = iNumber / 10;
iIndex = mcMaxWholeNumbers - iCount-1;
if (iIndex < 0)
{
Overflow(GetSign());
}
mcDigits[iIndex] = iRemainder;
iCount ++;
if (iNumber == 0)
{
break;
}
}
SetFirstNonZerotDigit(iCount);
CleanRight();
return this;
}
CNumber* CNumber::Init(int32 iNumber)
{
return Init(iNumber, 26, 16);
}
CNumber* CNumber::Init(float32 ff, int16 cMaxWholeNumbers, int16 cMaxDecimals)
{
int32 i;
int32 e;
int32 f;
int32 s;
int32 iCount;
int32 iBitMask;
PrivateInit(cMaxWholeNumbers, cMaxDecimals);
i = *((int32*)((void*)&ff));
s = (i & 0x80000000) >> 31;
e = (i & 0x7F800000) >> 23;
f = (i & 0x007FFFFF);
if ((e == 255) && (f != 0))
{
SetFlag(0x02);
return this;
}
if ((e == 255) && (f == 0))
{
return Overflow(-s);
}
if ((e == 0) && (f == 0))
{
SetFirstNonZerotDigit(1);
SetLastNonZeroDigit(1);
SetSign(-s);
return this;
}
if (e > 0)
{
e = e - 127;
AddBinaryOne(e);
for (iCount = 0; iCount < 23; iCount++)
{
iBitMask = 1 << (22-iCount);
if (f & iBitMask)
{
AddBinaryOne(e - iCount - 1);
}
}
}
else if (e == 0)
{
SetFirstNonZerotDigit(1);
SetLastNonZeroDigit(1);
SetFlag(0x08);
}
SetSign(-s);
Clean();
RoundSignificant(8);
return this;
}
CNumber* CNumber::Init(float32 ff)
{
return Init(ff, 26, 16);
}
CNumber* CNumber::BinaryOne(int16 iBinaryExponent, int16 cMaxWholeNumbers, int16 cMaxDecimals)
{
int32 iNumber;
if ((iBinaryExponent < 32) && (iBinaryExponent >= 0))
{
iNumber = 1 << iBinaryExponent;
Init(iNumber, cMaxWholeNumbers, cMaxDecimals);
}
else if ((iBinaryExponent < 0) && (iBinaryExponent > -32))
{
iNumber = 1 << (-iBinaryExponent);
Init(iNumber, cMaxWholeNumbers, cMaxDecimals);
Inverse();
}
else if (iBinaryExponent >= 32)
{
}
else if (iBinaryExponent <= -32)
{
}
return this;
}
CNumber* CNumber::Init(const char* szNumber, int16 cMaxWholeNumbers, int16 cMaxDecimals, size iLen)
{
CStackMemory<64> cStack;
char* cDigits;
int16 iSign;
int16 iDecimalPoint;
size i;
char c;
int16 iPos;
bool bAnyDigits;
int16 iNonZero;
PrivateInit(cMaxWholeNumbers, cMaxDecimals);
if (iLen == 0)
{
iLen = strlen(szNumber);
}
if (iLen >= 0x7fff)
{
return NotANumber();
}
cDigits = (char*)cStack.Init(iLen + 1);
iPos = 0;
bAnyDigits = false;
iNonZero = -1;
iDecimalPoint = 0;
iSign = 1;
for (i = 0; i < iLen; i++)
{
c = szNumber[i];
if ((c >= '0') && (c <= '9'))
{
bAnyDigits = true;
if ((c != '0') && (iNonZero == -1))
{
iNonZero = iPos;
}
cDigits[iPos] = c - '0';
iPos++;
}
else if (c == '.')
{
if (iDecimalPoint != 0)
{
cStack.Kill();
SetFlag(0x02);
return this;
}
if (!bAnyDigits)
{
cDigits[iPos] = 0;
iPos++;
bAnyDigits = true;
}
iDecimalPoint = iPos;
}
else if (c == '-')
{
if (!bAnyDigits)
{
iSign = -1;
}
else
{
cStack.Kill();
SetFlag(0x02);
return this;
}
}
}
if (!bAnyDigits)
{
cStack.Kill();
return NotANumber();
}
if (iNonZero == -1)
{
cStack.Kill();
Zero(mcMaxWholeNumbers, mcMaxDecimals);
return this;
}
if (iDecimalPoint == 0)
{
iDecimalPoint = iPos;
}
if (iDecimalPoint - iNonZero > mcMaxWholeNumbers)
{
cStack.Kill();
return Overflow(iSign);
}
if (iPos - iDecimalPoint > mcMaxDecimals)
{
iPos = iPos - (iPos - iDecimalPoint - mcMaxDecimals);
SetFlag(0x08);
}
memcpy(&mcDigits[mcMaxWholeNumbers-iDecimalPoint], cDigits, iPos);
cStack.Kill();
SetFirstNonZerotDigit(iDecimalPoint);
SetLastNonZeroDigit(-(iPos-iDecimalPoint));
SetSign(iSign);
Clean();
return this;
}
CNumber* CNumber::Init(const char* szNumber, size iLen)
{
return Init(szNumber, 26, 16, iLen);
}
CNumber* CNumber::Init(CNumber* pcNumber, int16 cMaxWholeNumbers, int16 cMaxDecimals)
{
if ((cMaxWholeNumbers + cMaxDecimals) == (pcNumber->mcMaxWholeNumbers + pcNumber->mcMaxDecimals))
{
memcpy(this, pcNumber, (cMaxWholeNumbers + cMaxDecimals + sizeof(CNumberDetail)));
return this;
}
else
{
PrivateCopy(pcNumber, cMaxWholeNumbers, cMaxDecimals);
return this;
}
}
CNumber* CNumber::Init(CNumber* pcNumber)
{
if ((26 + 16) == (pcNumber->mcMaxWholeNumbers + pcNumber->mcMaxDecimals))
{
memcpy(this, pcNumber, 52);
return this;
}
else
{
PrivateCopy(pcNumber, 26, 16);
return this;
}
}
CNumber* CNumber::Zero(int16 cMaxWholeNumbers, int16 cMaxDecimals)
{
return Init(cMaxWholeNumbers, cMaxDecimals);
}
CNumber* CNumber::Zero(void)
{
return Init();
}
CNumber* CNumber::One(int16 cMaxWholeNumbers, int16 cMaxDecimals, bool bPositive)
{
PrivateInit(cMaxWholeNumbers, cMaxDecimals);
SetFirstNonZerotDigit(1);
SetLastNonZeroDigit(1);
SetDigitUnsafe(1, 1);
SetPositive(bPositive);
return this;
}
CNumber* CNumber::One(bool bPositive)
{
PrivateInit();
SetFirstNonZerotDigit(1);
SetLastNonZeroDigit(1);
SetDigitUnsafe(1, 1);
SetPositive(bPositive);
return this;
}
CNumber* CNumber::Two(int16 cMaxWholeNumbers, int16 cMaxDecimals, bool bPositive)
{
PrivateInit(cMaxWholeNumbers, cMaxDecimals);
SetFirstNonZerotDigit(1);
SetLastNonZeroDigit(1);
SetDigitUnsafe(1, 2);
SetPositive(bPositive);
return this;
}
CNumber* CNumber::Two(bool bPositive)
{
PrivateInit();
SetFirstNonZerotDigit(1);
SetLastNonZeroDigit(1);
SetDigitUnsafe(1, 2);
SetPositive(bPositive);
return this;
}
CNumber* CNumber::Half(int16 cMaxWholeNumbers, int16 cMaxDecimals, bool bPositive)
{
PrivateInit(cMaxWholeNumbers, cMaxDecimals);
SetFirstNonZerotDigit(1);
SetLastNonZeroDigit(1);
SetDigitUnsafe(1, 2);
SetPositive(bPositive);
return this;
}
CNumber* CNumber::Half(bool bPositive)
{
PrivateInit();
SetFirstNonZerotDigit(-1);
SetLastNonZeroDigit(-1);
SetDigitUnsafe(-1, 5);
SetPositive(bPositive);
return this;
}
CNumber* CNumber::Pi(int16 cMaxWholeNumbers, int16 cMaxDecimals, bool bPositive)
{
gcNumberControl.Pi(this, cMaxWholeNumbers, cMaxDecimals, bPositive);
return this;
}
CNumber* CNumber::Pi(bool bPositive)
{
gcNumberControl.Pi(this, bPositive);
return this;
}
CNumber* CNumber::E(int16 cMaxWholeNumbers, int16 cMaxDecimals, bool bPositive)
{
gcNumberControl.E(this, cMaxWholeNumbers, cMaxDecimals, bPositive);
return this;
}
CNumber* CNumber::E(bool bPositive)
{
gcNumberControl.E(this, bPositive);
return this;
}
CNumber* CNumber::Copy(CNumber* pcNumber, int16 cMaxWholeNumbers, int16 cMaxDecimals)
{
return Init(pcNumber, cMaxWholeNumbers, cMaxDecimals);
}
CNumber* CNumber::Copy(CNumber* pcNumber)
{
return Init(pcNumber);
}
CNumber* CNumber::NotANumber(void)
{
mcFirstDigit = 0;
mcLastDigit = 0;
SetFlag(0x02);
return this;
}
CNumber* CNumber::DivisionByZero(void)
{
mcFirstDigit = 0;
mcLastDigit = 0;
SetFlag(0x10);
return this;
}
CNumber* CNumber::Overflow(int16 iSign)
{
mcFirstDigit = 0;
mcLastDigit = 0;
SetSign(iSign);
SetFlag(0x04);
return this;
}
CNumber* CNumber::Digit(char cValue, int16 cMaxWholeNumbers, int16 cMaxDecimals)
{
Zero(cMaxWholeNumbers, cMaxDecimals);
if ((cValue >= 0) && (cValue <= 9))
{
SetDigitUnsafe(1, cValue);
}
else if ((cValue < 0) && (cValue >= -9))
{
SetDigitUnsafe(1, -cValue);
SetSign(-1);
}
else
{
return NotANumber();
}
return this;
}
CNumber* CNumber::Digit(char cValue)
{
Zero();
if ((cValue >= 0) && (cValue <= 9))
{
SetDigitUnsafe(1, cValue);
}
else if ((cValue < 0) && (cValue >= -9))
{
SetDigitUnsafe(1, -cValue);
SetSign(-1);
}
else
{
return NotANumber();
}
return this;
}
CNumber* CNumber::Digit(int16 iDigit, char cValue, int16 cMaxWholeNumbers, int16 cMaxDecimals)
{
Zero(cMaxWholeNumbers, cMaxDecimals);
if ((cValue >= 0) && (cValue <= 9))
{
SetDigit(iDigit, cValue);
}
else if ((cValue < 0) && (cValue >= -9))
{
SetDigit(iDigit, -cValue);
SetSign(-1);
}
else
{
return NotANumber();
}
return this;
}
CNumber* CNumber::Digit(int16 iDigit, char cValue)
{
Zero();
if ((cValue >= 0) && (cValue <= 9))
{
SetDigit(iDigit, cValue);
}
else if ((cValue < 0) && (cValue >= -9))
{
SetDigit(iDigit, -cValue);
SetSign(-1);
}
else
{
return NotANumber();
}
return this;
}
void CNumber::AddBinaryOne(int16 iBinaryExponent)
{
CNumber* pcNumber;
pcNumber = gcNumberControl.Add(mcMaxWholeNumbers, mcMaxDecimals);
pcNumber->BinaryOne(iBinaryExponent, mcMaxWholeNumbers, mcMaxDecimals);
Add(pcNumber);
gcNumberControl.Remove();
}
void CNumber::SetFirstNonZerotDigit(int16 iDigit)
{
mcFirstDigit = iDigit;
}
void CNumber::SetLastNonZeroDigit(int16 iDigit)
{
mcLastDigit = iDigit;
}
int16 CNumber::GetFirstNonZeroDigit(void)
{
return mcFirstDigit;
}
int16 CNumber::GetLastNonZeroDigit(void)
{
return mcLastDigit;
}
void CNumber::SetSign(int16 iSign)
{
if (iSign < 0)
{
SetFlag(0x01);
}
else
{
ClearFlag(0x01);
}
}
void CNumber::SetPositive(bool bPositive)
{
if (bPositive)
{
ClearFlag(0x01);
}
else
{
SetFlag(0x01);
}
}
int16 CNumber::GetSign(void)
{
if (IsNegative())
{
return -1;
}
return 1;
}
bool CNumber::IsZero(void)
{
int16 iLast;
int16 iFirst;
iFirst = GetFirstNonZeroDigit();
iLast = GetLastNonZeroDigit();
if ((iFirst == 1) && (iLast == 1) && (GetDigitUnsafe(1) == 0))
{
return true;
}
return false;
}
bool CNumber::IsOdd(void)
{
int16 iLast;
char cDigit;
if (IsError())
{
return false;
}
iLast = GetLastNonZeroDigit();
if (iLast > 1)
{
return false;
}
if (iLast <= -1)
{
return false;
}
cDigit = GetDigitUnsafe(1);
return (cDigit % 2) == 1;
}
bool CNumber::IsEven(void)
{
int16 iLast;
char cDigit;
if (IsError())
{
return false;
}
iLast = GetLastNonZeroDigit();
if (iLast > 1)
{
return true;
}
if (iLast <= -1)
{
return false;
}
cDigit = GetDigitUnsafe(1);
return (cDigit % 2) == 0;
}
bool CNumber::IsDivisionByZero(void)
{
return mcFlags & 0x10;
}
bool CNumber::IsError(void)
{
if (IsOverflow())
{
return true;
}
if (IsNAN())
{
return true;
}
if (IsDivisionByZero())
{
return true;
}
return false;
}
void CNumber::SetFlag(int16 iFlag)
{
mcFlags |= iFlag;
}
void CNumber::ClearFlag(int16 iFlag)
{
mcFlags &= ~iFlag;
}
int16 CNumber::GetDecimals(void)
{
int16 iLast;
iLast = GetLastNonZeroDigit();
if (iLast < 0)
{
return -iLast;
}
else
{
return 0;
}
}
int16 CNumber::GetMaxWholeNumbers(void)
{
return mcMaxWholeNumbers;
}
int16 CNumber::GetMaxDecimals(void)
{
return mcMaxDecimals;
}
void CNumber::CleanLeft(void)
{
int16 i;
char c;
int16 iFirst;
int16 iLast;
bool bAnyNonZero;
int16 iFirstDiscovered;
iFirst = GetFirstNonZeroDigit();
iLast = GetLastNonZeroDigit();
bAnyNonZero = false;
for (i = iFirst; i >= iLast; i--)
{
if (i != 0)
{
c = GetDigitUnsafe(i);
if ((c != 0) && (!bAnyNonZero))
{
bAnyNonZero = true;
iFirstDiscovered = i;
break;
}
}
}
if (!bAnyNonZero)
{
SetFirstNonZerotDigit(1);
SetLastNonZeroDigit(1);
SetSign(1);
return;
}
if (iFirst != iFirstDiscovered)
{
SetFirstNonZerotDigit(iFirstDiscovered);
iFirst = iFirstDiscovered;
}
}
void CNumber::CleanRight(void)
{
int16 i;
char c;
int16 iFirst;
int16 iLast;
bool bAnyNonZero;
int16 iLastDiscovered;
iFirst = GetFirstNonZeroDigit();
iLast = GetLastNonZeroDigit();
bAnyNonZero = false;
for (i = iLast; i <= iFirst; i++)
{
if (i != 0)
{
c = GetDigitUnsafe(i);
if ((c != 0) && (!bAnyNonZero))
{
bAnyNonZero = true;
iLastDiscovered = i;
break;
}
}
}
if (!bAnyNonZero)
{
SetFirstNonZerotDigit(1);
SetLastNonZeroDigit(1);
SetSign(1);
return;
}
if (iLast != iLastDiscovered)
{
SetLastNonZeroDigit(iLastDiscovered);
iLast = iLastDiscovered;
}
}
void CNumber::Clean(void)
{
CleanLeft();
CleanRight();
PrivateZeroEnds();
}
int16 CNumber::OffsetDigit(int16 iCurrentDigit, int16 iOffset)
{
if (iCurrentDigit < 0)
{
iCurrentDigit += iOffset;
if (iCurrentDigit >= 0)
{
iCurrentDigit++;
}
return iCurrentDigit;
}
else if (iCurrentDigit > 0)
{
iCurrentDigit += iOffset;
if (iCurrentDigit <= 0)
{
iCurrentDigit--;
}
return iCurrentDigit;
}
return 0;
}
size CNumber::GetDigitsBetween(int16 iFirst, int16 iLast)
{
if (iFirst < iLast)
{
return 0;
}
if (((iFirst > 0) && (iLast > 0)) || ((iFirst < 0) && (iLast < 0)))
{
return iFirst - iLast + 1;
}
else if ((iFirst > 0) && (iLast < 0))
{
return iFirst - iLast;
}
return 0;
}
void CNumber::RoundSignificant(int16 iSignificantDigits)
{
int16 iDigits;
int16 iDifference;
int16 iLast;
int16 iNewLast;
char cBeyondDigit;
CNumber* pcRound;
int16 iBeyondLast;
if (iSignificantDigits <= 0)
{
return;
}
iDigits = (int16)GetDigitsBetween();
if (iDigits > iSignificantDigits)
{
iLast = GetLastNonZeroDigit();
iDifference = iDigits - iSignificantDigits;
iNewLast = OffsetDigit(iLast, iDifference);
iBeyondLast = OffsetDigit(iNewLast, -1);
cBeyondDigit = GetDigitUnsafe(iBeyondLast);
if (cBeyondDigit >= 5)
{
pcRound = gcNumberControl.Add(mcMaxWholeNumbers, mcMaxDecimals);
pcRound->Digit(iNewLast, 1 * GetSign(), mcMaxWholeNumbers, mcMaxDecimals);
Add(pcRound);
gcNumberControl.Remove();
}
SetLastNonZeroDigit(iNewLast);
PrivateZeroDigits(iBeyondLast, iLast);
Clean();
}
}
void CNumber::PrivateZeroDigits(int16 iFirst, int16 iLast)
{
size iLength;
char* pcStart;
pcStart = DigitToArray(iFirst);
iLength = GetDigitsBetween(iFirst, iLast);
memset(pcStart, (uint8)0, iLength);
}
void CNumber::PrivateZeroEnds(void)
{
int16 iFirst;
int16 iLast;
iFirst = OffsetDigit(GetFirstNonZeroDigit(), 1);
if (iFirst <= mcMaxWholeNumbers)
{
memset(mcDigits, (uint8)0, GetDigitsBetween(mcMaxWholeNumbers, iFirst));
}
iLast = GetLastNonZeroDigit();
if (iLast > -mcMaxDecimals)
{
iLast = OffsetDigit(iLast, -1);
PrivateZeroDigits(iLast, -mcMaxDecimals);
}
}
bool CNumber::IsInteger(void)
{
int32 iLast;
iLast = GetLastNonZeroDigit();
if (iLast > 0)
{
return true;
}
return false;
}
bool CNumber::DigitsEqual(CNumber* pcTest, int16 iFirstDigit, int16 iLastDigit)
{
int32 iResult;
iResult = memcmp(DigitToArray(iFirstDigit), pcTest->DigitToArray(iLastDigit), GetDigitsBetween(iFirstDigit, iLastDigit));
return iResult == 0;
}
CNumber* CNumber::Integer(void)
{
return Truncate(-1);
}
CNumber* CNumber::Ceiling(void)
{
CNumber* pcTemp;
CNumber* pcOne;
pcTemp = gcNumberControl.Add(mcMaxWholeNumbers, mcMaxDecimals);
pcTemp->Init(this, mcMaxWholeNumbers, mcMaxDecimals);
pcTemp->Fractional();
Integer();
if (!pcTemp->IsZero())
{
pcOne = gcNumberControl.Add(mcMaxWholeNumbers, mcMaxDecimals);
pcOne->One();
Add(pcOne);
gcNumberControl.Remove();
}
gcNumberControl.Remove();
return this;
}
CNumber* CNumber::Floor(void)
{
return Integer();
}
CNumber* CNumber::Fractional(void)
{
return TruncateHigh(1);
}
CNumber* CNumber::Shift(int16 iOffset)
{
int16 iFirst;
int16 iLast;
size iLength;
int16 iStart;
char* pcOld;
char* pcNew;
if (iOffset == 0)
{
return this;
}
if (IsOverflow() || IsNAN())
{
return this;
}
if (IsZero())
{
return this;
}
iFirst = GetFirstNonZeroDigit();
iLast = GetLastNonZeroDigit();
iStart = iFirst;
iFirst = OffsetDigit(iFirst, iOffset);
if (iFirst > mcMaxWholeNumbers)
{
return Overflow(GetSign());
}
if (iFirst < -mcMaxDecimals)
{
Init(mcMaxWholeNumbers, mcMaxDecimals);
SetFlag(0x08);
return this;
}
iLast = OffsetDigit(iLast, iOffset);
if (iLast < -mcMaxDecimals)
{
SetFlag(0x08);
iLast = -mcMaxDecimals;
}
iLength = GetDigitsBetween(iFirst, iLast);
pcOld = DigitToArray(iStart);
pcNew = DigitToArray(iFirst);
memmove(pcNew, pcOld, (int)iLength);
SetFirstNonZerotDigit(iFirst);
SetLastNonZeroDigit(iLast);
if (iOffset > 0)
{
iLast = OffsetDigit(iLast, -1);
pcNew = DigitToArray(iLast);
memset(pcNew, (uint8)0, iOffset);
}
else
{
memset(pcOld, (uint8)0, -iOffset);
}
return this;
}
CNumber* CNumber::Truncate(int16 iDigitToTruncateInclusive)
{
int16 iLast;
iLast = GetLastNonZeroDigit();
if (iDigitToTruncateInclusive >= iLast)
{
PrivateZeroDigits(iDigitToTruncateInclusive, iLast);
CleanRight();
}
return this;
}
CNumber* CNumber::TruncateHigh(int16 iDigit)
{
int16 iFirst;
iFirst = GetFirstNonZeroDigit();
if (iDigit <= iFirst)
{
PrivateZeroDigits(iFirst, iDigit);
CleanLeft();
}
return this;
}
bool CNumber::IsClean(void)
{
CNumber* pcTest;
bool bResult;
pcTest = gcNumberControl.Add(mcMaxWholeNumbers, mcMaxDecimals);
pcTest->Init(this, mcMaxWholeNumbers, mcMaxDecimals);
pcTest->Clean();
bResult = Equals(pcTest);
gcNumberControl.Remove();
return bResult;
}
int16 CNumber::GetWholeNumbers(void)
{
int16 iFirst;
iFirst = GetFirstNonZeroDigit();
if (iFirst > 0)
{
return iFirst;
}
else
{
return 0;
}
}
size CNumber::GetDigitsBetween(void)
{
int16 iLast;
int16 iFirst;
iFirst = GetFirstNonZeroDigit();
iLast = GetLastNonZeroDigit();
return GetDigitsBetween(iFirst, iLast);
}
bool CNumber::IsNAN(void)
{
return mcFlags & 0x02;
}
bool CNumber::IsUnderflow(void)
{
return mcFlags & 0x08;
}
bool CNumber::IsOverflow(void)
{
return mcFlags & 0x04;
}
bool CNumber::IsNegative(void)
{
return FixBool(mcFlags & 0x01);
}
bool CNumber::IsPositive(void)
{
return !IsNegative() && !IsZero();
}
bool CNumber::IsPositiveOrZero(void)
{
return !IsNegative();
}
bool CNumber::PrivateEquals(CNumber* pcNumber, int16 iDecimals)
{
int32 iThisLastDigit;
int32 iOtherLastDigit;
int32 iThisFirstDigit;
int32 iOtherFirstDigit;
int32 iResult;
if (IsError())
{
return false;
}
iThisFirstDigit = GetFirstNonZeroDigit();
iThisLastDigit = GetLastNonZeroDigit();
iOtherFirstDigit = pcNumber->GetFirstNonZeroDigit();
iOtherLastDigit = pcNumber->GetLastNonZeroDigit();
if (IsNegative() != pcNumber->IsNegative())
{
return false;
}
if (iThisLastDigit < -iDecimals)
{
iThisLastDigit = -iDecimals;
}
if (iOtherLastDigit < -iDecimals)
{
iOtherLastDigit = -iDecimals;
}
if ((iThisFirstDigit != iOtherFirstDigit) || (iThisLastDigit != iOtherLastDigit))
{
return false;
}
iResult = memcmp(DigitToArray(iThisFirstDigit), pcNumber->DigitToArray(iOtherFirstDigit), GetDigitsBetween(iThisFirstDigit, iThisLastDigit));
return iResult == 0;
}
bool CNumber::Equals(CNumber* pcNumber)
{
return PrivateEquals(pcNumber, mcMaxDecimals);
}
bool CNumber::GreaterThan(CNumber* pcNumber)
{
bool bThisNegative;
bool bOtherNegative;
bool bThisZero;
bool bOtherZero;
bThisNegative = IsNegative();
bOtherNegative = pcNumber->IsNegative();
bThisZero = IsZero();
bOtherZero = pcNumber->IsZero();
if (bThisZero)
{
if (bOtherZero)
{
return false;
}
else if (bOtherNegative)
{
return true;
}
else
{
return false;
}
}
else if (bThisNegative)
{
if (bOtherZero)
{
return false;
}
else if (bOtherNegative)
{
return !PrivateGreaterThanOrEquals(pcNumber);
}
else
{
return false;
}
}
else
{
if (bOtherZero)
{
return true;
}
else if (bOtherNegative)
{
return true;
}
else
{
return PrivateGreaterThan(pcNumber);
}
}
}
bool CNumber::GreaterThanOrEquals(CNumber* pcNumber)
{
bool bThisNegative;
bool bOtherNegative;
bool bThisZero;
bool bOtherZero;
bThisNegative = IsNegative();
bOtherNegative = pcNumber->IsNegative();
bThisZero = IsZero();
bOtherZero = pcNumber->IsZero();
if (bThisZero)
{
if (bOtherZero)
{
return true;
}
else if (bOtherNegative)
{
return true;
}
else
{
return false;
}
}
else if (bThisNegative)
{
if (bOtherZero)
{
return false;
}
else if (bOtherNegative)
{
return !PrivateGreaterThan(pcNumber);
}
else
{
return false;
}
}
else
{
if (bOtherZero)
{
return true;
}
else if (bOtherNegative)
{
return true;
}
else
{
return PrivateGreaterThanOrEquals(pcNumber);
}
}
}
bool CNumber::LessThan(CNumber* pcNumber)
{
return !GreaterThanOrEquals(pcNumber);
}
bool CNumber::LessThanOrEquals(CNumber* pcNumber)
{
return !GreaterThan(pcNumber);
}
bool CNumber::PrivateGreaterThan(CNumber* pcNumber)
{
int32 iThisLastDigit;
int32 iOtherLastDigit;
int32 iThisFirstDigit;
int32 iOtherFirstDigit;
int32 iResult;
if (IsZero())
{
return false;
}
if (pcNumber->IsZero())
{
return true;
}
iThisFirstDigit = GetFirstNonZeroDigit();
iThisLastDigit = GetLastNonZeroDigit();
iOtherFirstDigit = pcNumber->GetFirstNonZeroDigit();
iOtherLastDigit = pcNumber->GetLastNonZeroDigit();
if (iOtherLastDigit > iThisLastDigit)
{
}
if (iThisFirstDigit > iOtherFirstDigit)
{
return true;
}
else if (iOtherFirstDigit > iThisFirstDigit)
{
return false;
}
iResult = memcmp(DigitToArray(iThisFirstDigit), pcNumber->DigitToArray(iThisFirstDigit), GetDigitsBetween(iThisFirstDigit, iThisLastDigit));
if (iResult > 0)
{
return true;
}
else if (iResult < 0)
{
return false;
}
else if (iThisLastDigit < iOtherLastDigit)
{
return true;
}
else
{
return false;
}
}
bool CNumber::PrivateGreaterThanOrEquals(CNumber* pcNumber)
{
int32 iThisLastDigit;
int32 iOtherLastDigit;
int32 iThisFirstDigit;
int32 iOtherFirstDigit;
int32 iResult;
if (pcNumber->IsZero())
{
return true;
}
if (IsZero())
{
return false;
}
iThisFirstDigit = GetFirstNonZeroDigit();
iThisLastDigit = GetLastNonZeroDigit();
iOtherFirstDigit = pcNumber->GetFirstNonZeroDigit();
iOtherLastDigit = pcNumber->GetLastNonZeroDigit();
if (iOtherLastDigit > iThisLastDigit)
{
}
if (iThisFirstDigit > iOtherFirstDigit)
{
return true;
}
else if (iOtherFirstDigit > iThisFirstDigit)
{
return false;
}
iResult = memcmp(DigitToArray(iThisFirstDigit), pcNumber->DigitToArray(iThisFirstDigit), GetDigitsBetween(iThisFirstDigit, iThisLastDigit));
if (iResult > 0)
{
return true;
}
else if (iResult < 0)
{
return false;
}
else if (iThisLastDigit > iOtherLastDigit)
{
return false;
}
else
{
return true;
}
}
CNumber* CNumber::Add(CNumber* pcNumber)
{
bool bThisNegative;
bool bOtherNegative;
CNumber* pcTemp;
bThisNegative = IsNegative();
bOtherNegative = pcNumber->IsNegative();
if (!bThisNegative && !bOtherNegative)
{
PrivateAdd(pcNumber);
}
else if (bThisNegative && bOtherNegative)
{
PrivateAdd(pcNumber);
SetSign(-1);
}
else if (!bThisNegative && bOtherNegative)
{
if (PrivateGreaterThanOrEquals(pcNumber))
{
PrivateSubtract(pcNumber);
}
else
{
pcTemp = gcNumberControl.Add(mcMaxWholeNumbers, mcMaxDecimals);
pcTemp->Init(pcNumber, mcMaxWholeNumbers, mcMaxDecimals);
pcTemp->PrivateSubtract(this);
Copy(pcTemp, mcMaxWholeNumbers, mcMaxDecimals);
gcNumberControl.Remove();
SetSign(-1);
}
}
else if (bThisNegative && !bOtherNegative)
{
if (PrivateGreaterThanOrEquals(pcNumber))
{
PrivateSubtract(pcNumber);
SetSign(-1);
}
else
{
pcTemp = gcNumberControl.Add(mcMaxWholeNumbers, mcMaxDecimals);
pcTemp->Init(pcNumber, mcMaxWholeNumbers, mcMaxDecimals);
pcTemp->PrivateSubtract(this);
Copy(pcTemp, mcMaxWholeNumbers, mcMaxDecimals);
gcNumberControl.Remove();
}
}
return this;
}
CNumber* CNumber::Subtract(CNumber* pcNumber)
{
bool bThisNegative;
bool bOtherNegative;
CNumber* pcTemp;
bThisNegative = IsNegative();
bOtherNegative = pcNumber->IsNegative();
if (!bThisNegative && bOtherNegative)
{
PrivateAdd(pcNumber);
}
else if (bThisNegative && !bOtherNegative)
{
PrivateAdd(pcNumber);
SetSign(-1);
}
else if (bThisNegative && bOtherNegative)
{
if (PrivateGreaterThanOrEquals(pcNumber))
{
PrivateSubtract(pcNumber);
SetSign(-1);
}
else
{
pcTemp = gcNumberControl.Add(mcMaxWholeNumbers, mcMaxDecimals);
pcTemp->Init(pcNumber, mcMaxWholeNumbers, mcMaxDecimals);
pcTemp->PrivateSubtract(this);
Copy(pcTemp, mcMaxWholeNumbers, mcMaxDecimals);
gcNumberControl.Remove();
SetSign(1);
}
}
else if (!bThisNegative && !bOtherNegative)
{
if (PrivateGreaterThanOrEquals(pcNumber))
{
PrivateSubtract(pcNumber);
}
else
{
pcTemp = gcNumberControl.Add(mcMaxWholeNumbers, mcMaxDecimals);
pcTemp->Init(pcNumber, mcMaxWholeNumbers, mcMaxDecimals);
pcTemp->PrivateSubtract(this);
Copy(pcTemp, mcMaxWholeNumbers, mcMaxDecimals);
SetSign(-1);
gcNumberControl.Remove();
}
}
return this;
}
bool CNumber::PrivateError(CNumber* pcNumber)
{
if (PrivateNAN(pcNumber))
{
return true;
}
if (PrivateOverflow(pcNumber))
{
return true;
}
if (PrivateDivisionByZero(pcNumber))
{
return true;
}
PrivateUnderflow(pcNumber);
return false;
}
void CNumber::PrivateAdd(CNumber* pcNumber)
{
int32 i;
char cCarry;
int32 iThisLastDigit;
int32 iOtherLastDigit;
int32 iLast;
int32 iFirst;
int32 iThisFirstDigit;
int32 iOtherFirstDigit;
char cThisDigit;
char cOtherDigit;
char cResult;
if (PrivateError(pcNumber)) return;
iThisLastDigit = GetLastNonZeroDigit();
iOtherLastDigit = pcNumber->GetLastNonZeroDigit();
iLast = iThisLastDigit;
if (iOtherLastDigit < iThisLastDigit)
{
SetLastNonZeroDigit(iOtherLastDigit);
iLast = iOtherLastDigit;
}
iThisFirstDigit = GetFirstNonZeroDigit();
iOtherFirstDigit = pcNumber->GetFirstNonZeroDigit();
iFirst = iThisFirstDigit;
if (iThisFirstDigit < iOtherFirstDigit)
{
iFirst = iOtherFirstDigit;
}
cCarry = 0;
for (i = iLast; i <= iFirst; i++)
{
if (i != 0)
{
cThisDigit = SafeGetDigit(i);
cOtherDigit = pcNumber->SafeGetDigit(i);
cResult = cThisDigit + cOtherDigit + cCarry;
if (cResult < 10)
{
cCarry = 0;
}
else
{
cCarry = 1;
cResult -= 10;
}
SetDigitUnsafe(i, cResult);
}
}
if (cCarry > 0)
{
if (i == 0)
{
i++;
}
if (i <= mcMaxWholeNumbers)
{
SetDigitUnsafe(i, cCarry);
}
else
{
Overflow(GetSign());
return;
}
}
SetFirstNonZerotDigit(i);
Clean();
}
void CNumber::PrivateSubtract(CNumber* pcNumber)
{
char cCarry;
int32 iThisLastDigit;
int32 iOtherLastDigit;
int32 iThisFirstDigit;
int32 iOtherFirstDigit;
char cThisDigit;
char cOtherDigit;
char cResult;
int32 iThisLastIndex;
int32 iOtherLastIndex;
int32 iThisFirstIndex;
int32 iOtherFirstIndex;
int16 iDiff;
int32 iThisIndex;
int32 iOtherIndex;
if (PrivateError(pcNumber)) return;
iThisFirstDigit = GetFirstNonZeroDigit();
iOtherFirstDigit = pcNumber->GetFirstNonZeroDigit();
iThisLastDigit = GetLastNonZeroDigit();
iOtherLastDigit = pcNumber->GetLastNonZeroDigit();
if (iOtherLastDigit < -mcMaxDecimals)
{
SetFlag(0x08);
iOtherLastDigit = -mcMaxDecimals;
}
iThisLastIndex = (int32)PrivateGetIndex(iThisLastDigit);
iOtherLastIndex = (int32)pcNumber->PrivateGetIndex(iOtherLastDigit);
iThisFirstIndex = (int32)PrivateGetIndex(iThisFirstDigit);
iOtherFirstIndex = (int32)pcNumber->PrivateGetIndex(iOtherFirstDigit);
cCarry = 0;
if (iOtherLastDigit < iThisLastDigit)
{
SetLastNonZeroDigit(iOtherLastDigit);
iDiff = (int16)(GetDigitsBetween(iThisLastDigit, iOtherLastDigit)) - 1;
iThisIndex = (int32)PrivateGetIndex(iOtherLastDigit);
for (iOtherIndex = iOtherLastIndex; iOtherIndex > iOtherLastIndex - iDiff; iOtherIndex--, iThisIndex--)
{
cThisDigit = 10;
cOtherDigit = pcNumber->mcDigits[iOtherIndex];
cResult = cThisDigit - (cOtherDigit + cCarry);
if (cResult >= 10)
{
cCarry = 0;
cResult -= 10;
}
else
{
cCarry = 1;
}
mcDigits[iThisIndex] = cResult;
}
}
else if (iThisLastDigit < iOtherLastDigit)
{
iDiff = (int16)(GetDigitsBetween(iOtherLastDigit, iThisLastDigit)) - 1;
iOtherIndex = (int32)pcNumber->PrivateGetIndex(iThisLastDigit);
for (iThisIndex = iThisLastIndex; iThisIndex > iThisLastIndex - iDiff; iOtherIndex--, iThisIndex--)
{
cThisDigit = mcDigits[iThisIndex] + 10;
cOtherDigit = 0;
cResult = cThisDigit - (cOtherDigit + cCarry);
if (cResult >= 10)
{
cCarry = 0;
cResult -= 10;
}
else
{
cCarry = 1;
}
mcDigits[iThisIndex] = cResult;
}
}
else
{
iOtherIndex = iOtherLastIndex;
iThisIndex = iThisLastIndex;
}
for (; iOtherIndex >= iOtherFirstIndex; iOtherIndex--, iThisIndex--)
{
cThisDigit = mcDigits[iThisIndex] + 10;
cOtherDigit = pcNumber->mcDigits[iOtherIndex];
cResult = cThisDigit - (cOtherDigit + cCarry);
if (cResult >= 10)
{
cCarry = 0;
cResult -= 10;
}
else
{
cCarry = 1;
}
mcDigits[iThisIndex] = cResult;
}
for (; iThisIndex >= iThisFirstIndex; iOtherIndex--, iThisIndex--)
{
cThisDigit = mcDigits[iThisIndex] + 10;
cOtherDigit = 0;
cResult = cThisDigit - (cOtherDigit + cCarry);
if (cResult >= 10)
{
cCarry = 0;
cResult -= 10;
}
else
{
cCarry = 1;
}
mcDigits[iThisIndex] = cResult;
}
Clean();
}
size CNumber::PrivateGetIndex(int16 iDigit)
{
if (iDigit > 0)
{
return mcMaxWholeNumbers-iDigit;
}
else
{
return mcMaxWholeNumbers - iDigit - 1;
}
}
CNumber* CNumber::Multiply(CNumber* pcMultiplicand)
{
char cCarry;
int32 iThisLastDigit;
int32 iMultiplicandLastDigit;
int32 iThisFirstDigit;
int32 iMultiplicandFirstDigit;
char cThisDigit;
char cOtherDigit;
int32 i;
int32 j;
int32 iResultantDigit;
int32 iThisDigit;
int32 iOtherDigit;
char cResult;
CNumber* pcResult;
CNumber* pcLine;
int32 iFirstSignificantDigit;
int32 iDecimals;
if (PrivateError(pcMultiplicand)) return this;
if ((pcMultiplicand->IsZero()) || (IsZero()))
{
return Zero(mcMaxWholeNumbers, mcMaxDecimals);
}
iThisLastDigit = GetLastNonZeroDigit();
iThisFirstDigit = GetFirstNonZeroDigit();
iMultiplicandLastDigit = pcMultiplicand->GetLastNonZeroDigit();
iMultiplicandFirstDigit = pcMultiplicand->GetFirstNonZeroDigit();
iDecimals = mcMaxDecimals + 3;
pcResult = gcNumberControl.Add(mcMaxWholeNumbers, iDecimals);
if (!pcResult)
{
return 0L;
}
pcLine = gcNumberControl.Add(mcMaxWholeNumbers, iDecimals);
pcResult->Init(mcMaxWholeNumbers, iDecimals);
for (j = iMultiplicandLastDigit; j <= iMultiplicandFirstDigit; j++)
{
if (j != 0)
{
iOtherDigit = j;
if (j > 0)
{
iOtherDigit--;
}
cOtherDigit = pcMultiplicand->GetDigitUnsafe(j);
cCarry = 0;
iResultantDigit = (iThisFirstDigit > 0 ? iThisFirstDigit-1 : iThisFirstDigit) + iOtherDigit;
iResultantDigit = iResultantDigit >= 0 ? iResultantDigit+1 : iResultantDigit;
if (iResultantDigit > mcMaxWholeNumbers)
{
gcNumberControl.Remove(1+1);
return Overflow(GetSign() * pcMultiplicand->GetSign());
}
else
{
iFirstSignificantDigit = iResultantDigit;
}
pcLine->Init(mcMaxWholeNumbers, iDecimals);
iResultantDigit = (iThisLastDigit > 0 ? iThisLastDigit-1 : iThisLastDigit) + iOtherDigit;
iResultantDigit = iResultantDigit >= 0 ? iResultantDigit+1 : iResultantDigit;
if (iResultantDigit < -iDecimals)
{
pcLine->SetFlag(0x08);
pcLine->SetLastNonZeroDigit(-iDecimals);
}
else
{
pcLine->SetLastNonZeroDigit(iResultantDigit);
}
for (i = iThisLastDigit; i <= iThisFirstDigit; i++)
{
if (i != 0)
{
iThisDigit = i;
if (i > 0)
{
iThisDigit--;
}
iResultantDigit = iThisDigit+iOtherDigit;
if (iResultantDigit >= 0)
{
iResultantDigit++;
}
cThisDigit = GetDigitUnsafe(i);
cResult = cThisDigit * cOtherDigit + cCarry;
cCarry = cResult / 10;
cResult %= 10;
if (iResultantDigit >= -iDecimals)
{
pcLine->SetDigitUnsafe(iResultantDigit, cResult);
}
}
}
if (cCarry != 0)
{
iFirstSignificantDigit = OffsetDigit(iFirstSignificantDigit, 1);
if (iFirstSignificantDigit > mcMaxWholeNumbers)
{
gcNumberControl.Remove(1+1);
return Overflow(GetSign() * pcMultiplicand->GetSign());
}
pcLine->SetDigitUnsafe(iFirstSignificantDigit, cCarry);
}
pcLine->SetFirstNonZerotDigit(iFirstSignificantDigit);
pcResult->Add(pcLine);
if (pcResult->IsOverflow())
{
gcNumberControl.Remove(1+1);
return Overflow(GetSign()*pcMultiplicand->GetSign());
}
}
}
pcResult->SetSign(GetSign() * pcMultiplicand->GetSign());
pcResult->Clean();
Init(pcResult, mcMaxWholeNumbers, mcMaxDecimals);
gcNumberControl.Remove(1+1);
return this;
}
CNumber* CNumber::Divide(CNumber* pcDivisorIn)
{
CNumber* pcDivisor;
CNumber* pcPartialDividend;
char cThisDigit;
char cPartialQuotient;
CNumber* pcQuotient;
int32 iDividendDigit;
int32 iQuotientDigit;
bool bExact;
int32 iLastDigit;
int32 iLastDivisorDigit;
int32 iDecimals;
if (PrivateError(pcDivisorIn)) return this;
if (pcDivisorIn->IsZero()) return DivisionByZero();
iDecimals = mcMaxDecimals + 3;
pcDivisor = gcNumberControl.Add(mcMaxWholeNumbers, iDecimals);
pcPartialDividend = gcNumberControl.Add(mcMaxWholeNumbers + 1, iDecimals);
pcQuotient = gcNumberControl.Add(mcMaxWholeNumbers, iDecimals);
pcDivisor->Init(pcDivisorIn, mcMaxWholeNumbers, iDecimals);
pcDivisor->Absolute();
iLastDivisorDigit = pcDivisor->GetLastNonZeroDigit();
iDividendDigit = GetFirstNonZeroDigit();
iLastDigit = GetLastNonZeroDigit();
cThisDigit = GetDigitUnsafe(iDividendDigit);
pcPartialDividend->Digit(iLastDivisorDigit, cThisDigit, mcMaxWholeNumbers + 1, iDecimals);
if (iLastDivisorDigit > 0)
{
iLastDivisorDigit--;
}
iQuotientDigit = OffsetDigit(iDividendDigit, -iLastDivisorDigit);
iLastDivisorDigit = pcDivisor->GetLastNonZeroDigit();
pcQuotient->Init(mcMaxWholeNumbers, iDecimals);
for (;;)
{
cPartialQuotient = pcPartialDividend->PrivateDivide(pcDivisor, &bExact);
if (!((iQuotientDigit > mcMaxWholeNumbers) && (cPartialQuotient == 0)))
{
pcQuotient->SetDigit(iQuotientDigit, cPartialQuotient);
if (pcQuotient->IsOverflow())
{
gcNumberControl.Remove(3);
return Overflow(GetSign()*pcDivisorIn->GetSign());
}
}
iDividendDigit = OffsetDigit(iDividendDigit, -1);
iQuotientDigit = OffsetDigit(iQuotientDigit, -1);
if (iQuotientDigit < -iDecimals)
{
pcQuotient->SetFlag(0x08);
break;
}
cThisDigit = GetDigitUnsafe(iDividendDigit);
if (bExact)
{
if (iDividendDigit < iLastDigit)
{
break;
}
pcPartialDividend->Digit(iLastDivisorDigit, cThisDigit, mcMaxWholeNumbers + 1, iDecimals);
}
else
{
pcPartialDividend->Shift(1);
pcPartialDividend->SetDigit(iLastDivisorDigit, cThisDigit);
}
}
pcQuotient->SetSign(GetSign() * pcDivisorIn->GetSign());
pcQuotient->Clean();
Init(pcQuotient, mcMaxWholeNumbers, mcMaxDecimals);
gcNumberControl.Remove(3);
return this;
}
char CNumber::PrivateDivide(CNumber* pcDivisor, bool* pbExact)
{
char cDigit;
cDigit = 0;
for (;;)
{
if (pcDivisor->GreaterThan(this))
{
if (IsZero())
{
*pbExact = true;
return cDigit;
}
else
{
*pbExact = false;
return cDigit;
}
}
cDigit++;
Subtract(pcDivisor);
}
}
void CNumber::PrivateUnderflow(CNumber* pcNumber)
{
if (pcNumber->IsUnderflow())
{
this->SetFlag(0x08);
}
}
bool CNumber::PrivateNAN(CNumber* pcNumber)
{
if (pcNumber->IsNAN())
{
NotANumber();
return true;
}
else if (IsNAN())
{
return true;
}
return false;
}
bool CNumber::PrivateDivisionByZero(CNumber* pcNumber)
{
if (pcNumber->IsDivisionByZero())
{
DivisionByZero();
return true;
}
else if (IsDivisionByZero())
{
return true;
}
return false;
}
bool CNumber::PrivateOverflow(CNumber* pcNumber)
{
if (pcNumber->IsOverflow() && IsOverflow())
{
if (IsNegative() != pcNumber->IsNegative())
{
NotANumber();
}
return true;
}
else if (pcNumber->IsOverflow())
{
Overflow(pcNumber->GetSign());
return true;
}
else if (IsOverflow())
{
return true;
}
return false;
}
void CNumber::PrivateIntegerFactorial(int16 iN, int16 cMaxWholeNumbers, int16 cMaxDecimals)
{
CNumber* pcI;
int16 i;
if (iN < 0)
{
NotANumber();
return;
}
One(cMaxWholeNumbers, cMaxWholeNumbers);
if (iN == 1)
{
return;
}
pcI = gcNumberControl.Add(mcMaxWholeNumbers, mcMaxDecimals);
pcI->One(mcMaxWholeNumbers, mcMaxDecimals);
for (i = 1; i <= iN; i++)
{
Multiply(pcI);
if (IsOverflow())
{
return;
}
pcI->Increment();
}
gcNumberControl.Remove();
}
void CNumber::PrivateIntegerRoot(CNumber* pcRoot)
{
CNumber* pcX_k;
CNumber* pcX_k1;
CNumber* pcOne;
CNumber* pcOneOverRoot;
CNumber* pcRootMinusOne;
CNumber* pcX_kTimesRootMinusOne;
CNumber* pcX_kToPowerRootMinusOne;
CNumber* pcBaseOver;
int32 iIterations;
int32 iDecimals;
CNumber* pcThis;
iDecimals = mcMaxDecimals + 3;
pcX_k = gcNumberControl.Add(mcMaxWholeNumbers, iDecimals);
pcX_k1 = gcNumberControl.Add(mcMaxWholeNumbers, iDecimals);
pcOne = gcNumberControl.Add(mcMaxWholeNumbers, iDecimals);
pcOneOverRoot = gcNumberControl.Add(mcMaxWholeNumbers, iDecimals);
pcRootMinusOne = gcNumberControl.Add(mcMaxWholeNumbers, iDecimals);
pcX_kTimesRootMinusOne = gcNumberControl.Add(mcMaxWholeNumbers, iDecimals);
pcX_kToPowerRootMinusOne = gcNumberControl.Add(mcMaxWholeNumbers, iDecimals);
pcBaseOver = gcNumberControl.Add(mcMaxWholeNumbers, iDecimals);
pcThis = gcNumberControl.Add(mcMaxWholeNumbers, iDecimals);
pcThis->Init(this, mcMaxWholeNumbers, iDecimals);
pcOne->One(mcMaxWholeNumbers, iDecimals);
pcX_k->One(mcMaxWholeNumbers, iDecimals);
pcRootMinusOne->Init(pcRoot, mcMaxWholeNumbers, iDecimals)->Decrement();
pcOneOverRoot->Init(pcRoot, mcMaxWholeNumbers, iDecimals)->Inverse();
for (iIterations = 0; ; iIterations++)
{
pcX_kTimesRootMinusOne->Init(pcX_k, mcMaxWholeNumbers, iDecimals)->Multiply(pcRootMinusOne);
pcX_kToPowerRootMinusOne->Init(pcX_k, mcMaxWholeNumbers, iDecimals)->PrivateIntegerExponent(pcRootMinusOne);
pcBaseOver->Init(pcThis, mcMaxWholeNumbers, iDecimals)->Divide(pcX_kToPowerRootMinusOne);
pcX_k1->Init(pcBaseOver, mcMaxWholeNumbers, iDecimals)->Add(pcX_kTimesRootMinusOne);
pcX_k1->Multiply(pcOneOverRoot);
if (pcX_k1->PrivateEquals(pcX_k, mcMaxDecimals))
{
Init(pcX_k1, mcMaxWholeNumbers, mcMaxDecimals);
break;
}
pcX_k->Init(pcX_k1, mcMaxWholeNumbers, iDecimals);
}
gcNumberControl.Remove(9);
}
void CNumber::PrivateCopy(CNumber* pcNumber, int16 cMaxWholeNumbers, int16 cMaxDecimals)
{
int16 iOtherFirst;
int16 iOtherLast;
size iLength;
mcMaxWholeNumbers = cMaxWholeNumbers;
mcMaxDecimals = cMaxDecimals;
mcFlags = 0;
if (pcNumber->IsError())
{
mcFlags = pcNumber->mcFlags;
return;
}
iOtherFirst = pcNumber->GetFirstNonZeroDigit();
iOtherLast = pcNumber->GetLastNonZeroDigit();
if (iOtherFirst > mcMaxWholeNumbers)
{
Overflow(pcNumber->GetSign());
return;
}
if (iOtherFirst < -(mcMaxDecimals))
{
Init(cMaxWholeNumbers, cMaxDecimals);
SetFlag(0x08);
return;
}
if (iOtherLast < -(mcMaxDecimals))
{
iOtherLast = -(mcMaxDecimals);
SetFlag(0x08);
}
iLength = GetDigitsBetween(iOtherFirst, iOtherLast);
memcpy(DigitToArray(iOtherFirst), pcNumber->DigitToArray(iOtherFirst), iLength);
SetFirstNonZerotDigit(iOtherFirst);
SetLastNonZeroDigit(iOtherLast);
SetSign(pcNumber->GetSign());
if (pcNumber->IsUnderflow())
{
SetFlag(0x08);
}
Clean();
}
void CNumber::PrivateIntegerExponent(int16 iExponent)
{
CNumber* pcResult;
CNumber* pcBase;
int32 iDecimals;
if (iExponent == 0)
{
One(mcMaxWholeNumbers, mcMaxDecimals);
return;
}
else if (iExponent == 1)
{
return;
}
else if (iExponent == 2)
{
Squared();
return;
}
else if (iExponent == 3)
{
Cubed();
return;
}
else if (iExponent > 0)
{
iDecimals = mcMaxDecimals + 3;
pcResult = gcNumberControl.Add(mcMaxWholeNumbers, iDecimals);
pcBase = gcNumberControl.Add(mcMaxWholeNumbers, iDecimals);
pcResult->One(mcMaxWholeNumbers, iDecimals);
pcBase->Init(this, mcMaxWholeNumbers, iDecimals);
for (;;)
{
if (iExponent & 1)
{
pcResult->Multiply(pcBase);
}
iExponent >>= 1;
if (iExponent == 0)
{
break;
}
pcBase->Squared();
}
Init(pcResult, mcMaxWholeNumbers, mcMaxDecimals);
gcNumberControl.Remove(1 + 1);
}
else if (iExponent == -1)
{
Inverse();
}
else if (iExponent == -2)
{
InverseSquared();
}
else if (iExponent == -3)
{
InverseCubed();
}
else if (iExponent < 0)
{
iExponent = -iExponent;
iDecimals = mcMaxDecimals + 3;
pcResult = gcNumberControl.Add(mcMaxWholeNumbers, iDecimals);
pcBase = gcNumberControl.Add(mcMaxWholeNumbers, iDecimals);
pcResult->One(mcMaxWholeNumbers, iDecimals);
pcBase->Init(this, mcMaxWholeNumbers, iDecimals);
for (;;)
{
if (iExponent & 1)
{
pcResult->Multiply(pcBase);
}
iExponent >>= 1;
if (iExponent == 0)
{
break;
}
pcBase->Squared();
}
Init(pcResult, mcMaxWholeNumbers, mcMaxDecimals);
gcNumberControl.Remove(1 + 1);
Inverse();
}
}
void CNumber::PrivateIntegerExponent(CNumber* pcExponentIn)
{
CNumber* pcResult;
CNumber* pcExponent;
CNumber* pcTwo;
int32 n;
if (pcExponentIn->GetFirstNonZeroDigit() <= 9)
{
n = pcExponentIn->IntValue();
PrivateIntegerExponent(n);
}
else
{
pcResult = gcNumberControl.Add(mcMaxWholeNumbers, mcMaxDecimals);
pcExponent = gcNumberControl.Add(mcMaxWholeNumbers, mcMaxDecimals);
pcTwo = gcNumberControl.Add(mcMaxWholeNumbers, mcMaxDecimals);
pcExponent->Init(pcExponentIn, mcMaxWholeNumbers, mcMaxDecimals);
pcResult->One(mcMaxWholeNumbers, mcMaxDecimals);
pcTwo->Init(2, mcMaxWholeNumbers, mcMaxDecimals);
while (!pcExponent->IsZero())
{
if (pcExponent->IsOdd())
{
pcResult->Multiply(this);
pcExponent->Decrement();
}
Squared();
pcExponent->Divide(pcTwo);
}
Init(pcResult, mcMaxWholeNumbers, mcMaxDecimals);
gcNumberControl.Remove(3);
}
}
CNumber* CNumber::Modulus(CNumber* pcNumber)
{
return this;
}
CNumber* CNumber::Inverse(void)
{
CNumber* pcOne;
pcOne = gcNumberControl.Add(mcMaxWholeNumbers, mcMaxDecimals);
pcOne->One(mcMaxWholeNumbers, mcMaxDecimals)->Divide(this);
Copy(pcOne, mcMaxWholeNumbers, mcMaxDecimals);
gcNumberControl.Remove();
return this;
}
CNumber* CNumber::InverseSquared(void)
{
Squared();
Inverse();
return this;
}
CNumber* CNumber::InverseCubed(void)
{
Cubed();
Inverse();
return this;
}
CNumber* CNumber::Negate(void)
{
if (IsNegative())
{
SetSign(1);
}
else
{
SetSign(-1);
}
return this;
}
CNumber* CNumber::Absolute(void)
{
ClearFlag(0x01);
return this;
}
CNumber* CNumber::Decrement(void)
{
CNumber* pcOne;
pcOne = gcNumberControl.Add(mcMaxWholeNumbers, mcMaxDecimals);
Subtract(pcOne->One(mcMaxWholeNumbers, mcMaxDecimals));
gcNumberControl.Remove();
return this;
}
CNumber* CNumber::LogicalNot(void)
{
CNumber* pcZero;
pcZero = gcNumberControl.Add(mcMaxWholeNumbers, mcMaxDecimals);
if (Equals(pcZero->Zero()))
{
One();
}
else
{
Zero(mcMaxWholeNumbers, mcMaxDecimals);
}
gcNumberControl.Remove();
return this;
}
CNumber* CNumber::LogicalOr(CNumber* pcRight)
{
CNumber* pcZero;
bool bLeftZero;
bool bRightZero;
pcZero = gcNumberControl.Add(mcMaxWholeNumbers, mcMaxDecimals);
bLeftZero = Equals(pcZero->Zero());
bRightZero = pcRight->Equals(pcZero);
if (bLeftZero && bRightZero)
{
Zero(mcMaxWholeNumbers, mcMaxDecimals);
}
else
{
One();
}
gcNumberControl.Remove();
return this;
}
CNumber* CNumber::LogicalAnd(CNumber* pcRight)
{
CNumber* pcZero;
bool bLeftZero;
bool bRightZero;
pcZero = gcNumberControl.Add(mcMaxWholeNumbers, mcMaxDecimals);
bLeftZero = Equals(pcZero->Zero());
bRightZero = pcRight->Equals(pcZero);
if (bLeftZero || bRightZero)
{
Zero(mcMaxWholeNumbers, mcMaxDecimals);
}
else
{
One();
}
gcNumberControl.Remove();
return this;
}
CNumber* CNumber::Increment(void)
{
CNumber* pcOne;
pcOne = gcNumberControl.Add(mcMaxWholeNumbers, mcMaxDecimals);
Add(pcOne->One(mcMaxWholeNumbers, mcMaxDecimals));
gcNumberControl.Remove();
return this;
}
CNumber* CNumber::Power(CNumber* pcExponentIn)
{
CNumber* pcResult;
int32 iDecimals;
CNumber* pcExponent;
if (pcExponentIn->IsInteger())
{
PrivateIntegerExponent(pcExponentIn);
return this;
}
iDecimals = mcMaxDecimals*2;
pcResult = gcNumberControl.Add(mcMaxWholeNumbers, iDecimals);
pcExponent = gcNumberControl.Add(mcMaxWholeNumbers, iDecimals);
pcExponent->Copy(pcExponentIn, mcMaxWholeNumbers, iDecimals);
pcResult->Init(this, mcMaxWholeNumbers, iDecimals);
pcResult->NaturalLogarithm();
pcResult->Multiply(pcExponent);
pcResult->Exponential();
Init(pcResult, mcMaxWholeNumbers, mcMaxDecimals);
gcNumberControl.Remove(1+1);
return this;
}
CNumber* CNumber::Root(CNumber* pcRootIn)
{
CNumber* pcResult;
CNumber* pcRoot;
int32 iDecimals;
if (pcRootIn->IsInteger())
{
PrivateIntegerRoot(pcRootIn);
return this;
}
iDecimals = mcMaxDecimals*2;
pcResult = gcNumberControl.Add(mcMaxWholeNumbers, iDecimals);
pcRoot = gcNumberControl.Add(mcMaxWholeNumbers, iDecimals);
pcResult->Init(this, mcMaxWholeNumbers, iDecimals);
pcRoot->Init(pcRootIn, mcMaxWholeNumbers, iDecimals);
pcResult->NaturalLogarithm();
pcResult->Divide(pcRoot);
pcResult->Exponential();
Init(pcResult, mcMaxWholeNumbers, mcMaxDecimals);
gcNumberControl.Remove(1+1);
return this;
}
CNumber* CNumber::Antilog(CNumber* pcBase)
{
CNumber* pcResult;
pcResult = gcNumberControl.Add(mcMaxWholeNumbers, mcMaxDecimals);
pcResult->Init(pcBase, mcMaxWholeNumbers, mcMaxDecimals);
pcResult->Power(this);
Init(pcResult, mcMaxWholeNumbers, mcMaxDecimals);
gcNumberControl.Remove();
return this;
}
CNumber* CNumber::ArithmeticGeometricMean(CNumber* pcOther)
{
CNumber* pcAn;
CNumber* pcGn;
CNumber* pcAn_1;
CNumber* pcGn_1;
int32 iDecimals;
CNumber* pcTwo;
iDecimals = mcMaxDecimals;
pcAn = gcNumberControl.Add(mcMaxWholeNumbers, iDecimals);
pcGn = gcNumberControl.Add(mcMaxWholeNumbers, iDecimals);
pcAn_1 = gcNumberControl.Add(mcMaxWholeNumbers, iDecimals);
pcGn_1 = gcNumberControl.Add(mcMaxWholeNumbers, iDecimals);
pcTwo = gcNumberControl.Add(mcMaxWholeNumbers, iDecimals);
pcTwo->Init(2, mcMaxWholeNumbers, iDecimals);
pcAn->Init(this, mcMaxWholeNumbers, iDecimals);
pcGn->Init(pcOther, mcMaxWholeNumbers, iDecimals);
for (;;)
{
pcAn_1->Init(pcAn, mcMaxWholeNumbers, mcMaxDecimals);
pcAn_1->Add(pcGn);
pcAn_1->Divide(pcTwo);
pcGn_1->Init(pcAn, mcMaxWholeNumbers, mcMaxDecimals);
pcGn_1->Multiply(pcGn);
pcGn_1->SquareRoot();
if (pcAn_1->Equals(pcGn_1))
{
break;
}
pcAn->Init(pcAn_1, mcMaxWholeNumbers, iDecimals);
pcGn->Init(pcGn_1, mcMaxWholeNumbers, iDecimals);
}
this->Copy(pcAn_1, mcMaxWholeNumbers, mcMaxDecimals);
gcNumberControl.Remove(5);
return this;
}
CNumber* CNumber::Exponential(void)
{
int32 i;
CNumber* pcFractional;
CNumber* pcIntegral;
CNumber* pcOne;
CNumber* pcPart;
CNumber* pcNumber;
CNumber* pcE;
CNumber* pcResult;
int32 iDecimals;
iDecimals = mcMaxDecimals + mcMaxWholeNumbers + 3;
pcFractional = gcNumberControl.Add(mcMaxWholeNumbers, iDecimals);
pcIntegral = gcNumberControl.Add(mcMaxWholeNumbers, iDecimals);
pcOne = gcNumberControl.Add(mcMaxWholeNumbers, iDecimals);
pcResult = gcNumberControl.Add(mcMaxWholeNumbers, iDecimals);
pcResult->Init(this, mcMaxWholeNumbers, iDecimals);
pcIntegral->Init(this, mcMaxWholeNumbers, iDecimals);
pcFractional->Init(this, mcMaxWholeNumbers, iDecimals);
pcFractional->Fractional();
pcIntegral->Integer();
pcOne->One(mcMaxWholeNumbers, iDecimals);
if (IsZero())
{
gcNumberControl.Remove(4);
return One(mcMaxWholeNumbers, mcMaxDecimals);
}
pcPart = gcNumberControl.Add(mcMaxWholeNumbers, iDecimals);
pcNumber = gcNumberControl.Add(mcMaxWholeNumbers, iDecimals);
pcE = gcNumberControl.Add(mcMaxWholeNumbers, iDecimals);
pcResult->One(mcMaxWholeNumbers, iDecimals);
for (i = iDecimals; i >= 1; i--)
{
pcPart->Init(pcFractional, mcMaxWholeNumbers, iDecimals);
pcNumber->Init(i, mcMaxWholeNumbers, iDecimals);
pcPart->Divide(pcNumber);
pcResult->Multiply(pcPart);
pcResult->Increment();
}
pcE->E(mcMaxWholeNumbers, iDecimals);
if (!pcIntegral->IsNegative())
{
pcE->PrivateIntegerExponent(pcIntegral);
}
else
{
pcE->PrivateIntegerExponent(pcIntegral->Absolute());
pcE->Inverse();
}
pcResult->Multiply(pcE);
Init(pcResult, mcMaxWholeNumbers, mcMaxDecimals);
gcNumberControl.Remove(7);
return this;
}
CNumber* CNumber::Logarithm(CNumber* pcBase)
{
CNumber* pcOne;
int32 iInteger;
CNumber* pcInverseBase;
CNumber* pcDecimal;
CNumber* pcPartial;
CNumber* pcPointFive;
CNumber* pcResult;
int32 i;
int32 iSign;
int32 iDecimals;
if (PrivateError(pcBase))
{
return this;
}
if ((IsZero()) || (IsNegative()))
{
return NotANumber();
}
iDecimals = mcMaxDecimals;
pcOne = gcNumberControl.Add(mcMaxWholeNumbers, iDecimals);
pcOne->One(mcMaxDecimals, iDecimals);
pcResult = gcNumberControl.Add(mcMaxWholeNumbers, iDecimals);
pcResult->Copy(this, mcMaxWholeNumbers, iDecimals);
if (pcResult->Equals(pcOne))
{
gcNumberControl.Remove(1+1);
return Zero(mcMaxWholeNumbers, mcMaxDecimals);
}
iSign = 1;
if (pcResult->LessThan(pcOne))
{
iSign = -1;
pcResult->Inverse();
}
iInteger = 0;
if (pcBase->LessThan(pcOne))
{
gcNumberControl.Remove(1+1);
return NotANumber();
}
pcInverseBase = gcNumberControl.Add(mcMaxWholeNumbers, iDecimals);
pcInverseBase->Init(pcBase, mcMaxWholeNumbers, iDecimals);
pcInverseBase->Inverse();
while (pcResult->LessThan(pcOne))
{
iInteger--;
pcResult->Multiply(pcBase);
}
while (pcResult->GreaterThanOrEquals(pcBase))
{
iInteger++;
pcResult->Multiply(pcInverseBase);
}
pcPointFive = gcNumberControl.Add(mcMaxWholeNumbers, iDecimals);
pcPartial = gcNumberControl.Add(mcMaxWholeNumbers, iDecimals);
pcDecimal = gcNumberControl.Add(mcMaxWholeNumbers, iDecimals);
pcPointFive->Init("0.5", mcMaxWholeNumbers, iDecimals);
pcPartial->Init(pcPointFive, mcMaxWholeNumbers, iDecimals);
pcDecimal->Zero(mcMaxWholeNumbers, iDecimals);
pcResult->Squared();
for (i = 0;; i++)
{
if (pcResult->GreaterThanOrEquals(pcBase))
{
pcDecimal->Add(pcPartial);
pcResult->Divide(pcBase);
}
pcPartial->Multiply(pcPointFive);
if (pcPartial->IsZero() || (pcPartial->GetFirstNonZeroDigit() <= -mcMaxDecimals))
{
break;
}
pcResult->Squared();
}
pcResult->Init(iInteger, mcMaxWholeNumbers, iDecimals);
pcResult->Add(pcDecimal);
pcResult->SetSign(iSign);
Copy(pcResult, mcMaxWholeNumbers, mcMaxDecimals);
gcNumberControl.Remove(6);
return this;
}
CNumber* CNumber::NaturalLogarithm(void)
{
CNumber* pcE;
int32 iDecimals;
CNumber* pcResult;
iDecimals = mcMaxDecimals + 3;
if (iDecimals > 50)
{
iDecimals++;
if (iDecimals > 100)
{
iDecimals++;
}
}
pcE = gcNumberControl.Add(mcMaxWholeNumbers, iDecimals);
pcResult = gcNumberControl.Add(mcMaxWholeNumbers, iDecimals);
pcE->E(mcMaxWholeNumbers, iDecimals);
pcResult->Copy(this, mcMaxWholeNumbers, iDecimals);
pcResult->Logarithm(pcE);
Copy(pcResult, mcMaxWholeNumbers, mcMaxDecimals);
gcNumberControl.Remove(1+1);
return this;
}
CNumber* CNumber::CommonLogarithm(void)
{
CNumber* pcTen;
pcTen = gcNumberControl.Add(mcMaxWholeNumbers, mcMaxDecimals);
Logarithm(pcTen->Init(10, mcMaxWholeNumbers, mcMaxDecimals));
gcNumberControl.Remove();
return this;
}
CNumber* CNumber::BinaryLogarithm(void)
{
CNumber* pcTwo;
pcTwo = gcNumberControl.Add(mcMaxWholeNumbers, mcMaxDecimals);
Logarithm(pcTwo->Init(2, mcMaxWholeNumbers, mcMaxDecimals));
gcNumberControl.Remove();
return this;
}
CNumber* CNumber::SquareRoot(void)
{
CNumber* pcTwo;
pcTwo = gcNumberControl.Add(mcMaxWholeNumbers, mcMaxDecimals);
PrivateIntegerRoot(pcTwo->Init(2, mcMaxWholeNumbers, mcMaxDecimals));
gcNumberControl.Remove();
return this;
}
CNumber* CNumber::CubeRoot(void)
{
CNumber* pcThree;
pcThree = gcNumberControl.Add(mcMaxWholeNumbers, mcMaxDecimals);
PrivateIntegerRoot(pcThree->Init(3, mcMaxWholeNumbers, mcMaxDecimals));
gcNumberControl.Remove();
return this;
}
CNumber* CNumber::Squared(void)
{
CNumber* pcTemp;
pcTemp = gcNumberControl.Add(mcMaxWholeNumbers, mcMaxDecimals);
Multiply(pcTemp->Init(this, mcMaxWholeNumbers, mcMaxDecimals));
gcNumberControl.Remove();
return this;
}
CNumber* CNumber::Cubed(void)
{
CNumber* pcTemp;
pcTemp = gcNumberControl.Add(mcMaxWholeNumbers, mcMaxDecimals);
Multiply(pcTemp->Init(this, mcMaxWholeNumbers, mcMaxDecimals));
Multiply(pcTemp);
gcNumberControl.Remove();
return this;
}
CNumber* CNumber::Sine(void)
{
return this;
}
CNumber* CNumber::Cosine(void)
{
return this;
}
CNumber* CNumber::Tangent(void)
{
return this;
}
CNumber* CNumber::ArcSine(void)
{
return this;
}
CNumber* CNumber::ArcCosine(void)
{
return this;
}
CNumber* CNumber::ArcTangent(void)
{
return this;
}
CNumber* CNumber::HyperbolicSine(void)
{
return this;
}
CNumber* CNumber::HyperbolicCosine(void)
{
return this;
}
CNumber* CNumber::HyperbolicTangent(void)
{
return this;
}
CNumber* CNumber::DegreesToRadians(void)
{
return this;
}
CNumber* CNumber::RadiansToDegrees(void)
{
return this;
}
int32 CNumber::IntValue(void)
{
int16 iFirst;
int32 i;
int32 iTimes;
char iValue;
int32 iResult;
iFirst = GetFirstNonZeroDigit();
if ((iFirst < 0) || (IsZero()))
{
return 0;
}
iTimes = 1;
iResult = 0;
for (i = 1; i <= iFirst; i++)
{
iValue = GetDigitUnsafe(i);
iResult += (iValue*iTimes);
iTimes *= 10;
}
iResult *= GetSign();
return iResult;
}
uint64 CNumber::ULongValue(void)
{
int16 iFirst;
int32 i;
uint64 iTimes;
char iValue;
uint64 iResult;
iFirst = GetFirstNonZeroDigit();
if ((iFirst < 0) || (IsZero()))
{
return 0;
}
iTimes = 1;
iResult = 0;
for (i = 1; i <= iFirst; i++)
{
iValue = GetDigitUnsafe(i);
iResult += (iValue * iTimes);
iTimes *= 10;
}
iResult *= GetSign();
return iResult;
}
uint64 CNumber::DecimalValue(uint16* puiNumDecimals)
{
int16 iLast;
int32 i;
uint64 iTimes;
char iValue;
uint64 iResult;
uint16 uiNumDecimals;
iLast = GetLastNonZeroDigit();
if ((iLast > 0) || (IsZero()))
{
if (puiNumDecimals) { *puiNumDecimals = (uint16)0; };
return 0;
}
iTimes = 1;
iResult = 0;
for (i = iLast; i <= -1; i++)
{
iValue = GetDigitUnsafe(i);
iResult += (iValue * iTimes);
iTimes *= 10;
}
if (iLast <= -1)
{
uiNumDecimals = (uint16)-iLast;
}
else
{
uiNumDecimals = 0;
}
if (puiNumDecimals) { *puiNumDecimals = uiNumDecimals; };
return iResult;
}
float32 CNumber::FloatValue(void)
{
float32 fValue;
uint64 uiWholeNumbers;
uint64 uiDecimalNumbers;
uint16 uiNumDecimals;
uiWholeNumbers = ULongValue();
if (IsNegative())
{
uiWholeNumbers = (uint64)0 - uiWholeNumbers;
}
uiDecimalNumbers = DecimalValue(&uiNumDecimals);
fValue = (float32)ConvertDecimalFixedPointToLongDouble(uiWholeNumbers, uiDecimalNumbers, uiNumDecimals, 0);
return IsNegative() ? -fValue : fValue;
}
float64 CNumber::DoubleValue(void)
{
float64 fValue;
uint64 uiWholeNumbers;
uint64 uiDecimalNumbers;
uint16 uiNumDecimals;
uiWholeNumbers = ULongValue();
if (IsNegative())
{
uiWholeNumbers = (uint64)0 - uiWholeNumbers;
}
uiDecimalNumbers = DecimalValue(&uiNumDecimals);
fValue = (float64)ConvertDecimalFixedPointToLongDouble(uiWholeNumbers, uiDecimalNumbers, uiNumDecimals, 0);
return IsNegative() ? -fValue : fValue;
}
char CNumber::SafeGetDigit(int16 iDigit)
{
if (iDigit <= mcFirstDigit && iDigit >= mcLastDigit)
{
if ((iDigit > 0) && (iDigit <= mcMaxWholeNumbers))
{
return mcDigits[mcMaxWholeNumbers - iDigit];
}
else if ((iDigit >= -mcMaxDecimals) && (iDigit < 0))
{
return mcDigits[mcMaxWholeNumbers - iDigit - 1];
}
}
return 0;
}
char CNumber::GetDigitUnsafe(int16 iDigit)
{
if ((iDigit > 0) && (iDigit <= mcMaxWholeNumbers))
{
return mcDigits[mcMaxWholeNumbers-iDigit];
}
else if ((iDigit >= -mcMaxDecimals) && (iDigit < 0))
{
return mcDigits[mcMaxWholeNumbers-iDigit-1];
}
else
{
return 0;
}
}
void CNumber::SetDigit(int16 iDigit, char cValue)
{
int16 iFirstDigit;
int16 iLastDigit;
char* pcValue;
bool bWasZero;
if (iDigit > mcMaxWholeNumbers)
{
Overflow(GetSign());
}
else if (iDigit < -mcMaxDecimals)
{
SetFlag(0x08);
}
else if (iDigit == 0)
{
if (cValue != '.')
{
SetFlag(0x02);
}
}
else
{
if ((cValue >= 1) && (cValue <= 9))
{
bWasZero = IsZero();
pcValue = DigitToArray(iDigit);
*pcValue = cValue;
iFirstDigit = GetFirstNonZeroDigit();
if (iDigit > iFirstDigit)
{
SetFirstNonZerotDigit(iDigit);
}
iLastDigit = GetLastNonZeroDigit();
if (iDigit < iLastDigit)
{
SetLastNonZeroDigit(iDigit);
}
if (bWasZero)
{
Clean();
}
}
else if (cValue == 0)
{
pcValue = DigitToArray(iDigit);
*pcValue = cValue;
iFirstDigit = GetFirstNonZeroDigit();
if (iDigit == iFirstDigit)
{
CleanRight();
}
iLastDigit = GetLastNonZeroDigit();
if (iDigit == iLastDigit)
{
CleanLeft();
}
}
else
{
NotANumber();
}
}
}
void CNumber::SetDigitUnsafe(int16 iDigit, char cValue)
{
char* pcValue;
pcValue = DigitToArray(iDigit);
*pcValue = cValue;
}
char* CNumber::DigitToArray(int16 iDigit)
{
if (iDigit > 0)
{
return &mcDigits[mcMaxWholeNumbers - iDigit];
}
else if (iDigit < 0)
{
return &mcDigits[mcMaxWholeNumbers - iDigit - 1];
}
return 0L;
}
bool CNumber::PrintFloating(CChars* pcChars)
{
int32 iFirstDigit;
int32 iLastDigit;
int32 i;
char c;
int32 iStart;
int32 iStop;
if (IsNAN())
{
pcChars->Append("nan");
return false;
}
if (IsDivisionByZero())
{
pcChars->Append("nan");
return false;
}
if (IsNegative())
{
pcChars->Append("-");
}
if (IsOverflow())
{
pcChars->Append("inf");
return false;
}
iFirstDigit = GetFirstNonZeroDigit();
iLastDigit = GetLastNonZeroDigit();
iStart = iFirstDigit;
iStop = iLastDigit;
if ((iStart >= 1) && (iStop <= -1))
{
for (i = iStart; i >= iStop; i--)
{
if (i != 0)
{
c = GetDigitUnsafe(i) + '0';
pcChars->Append(c);
}
else
{
pcChars->Append('.');
}
}
}
else if ((iStart >= 1) && (iStop == 1))
{
for (i = iStart; i >= iStop; i--)
{
c = GetDigitUnsafe(i) + '0';
pcChars->Append(c);
}
pcChars->Append('.');
}
else if ((iStart >= 1) && (iStart <= 8) && (iStop >= 1) && (iStop <= 4))
{
for (i = iStart; i >= iStop; i--)
{
c = GetDigitUnsafe(i) + '0';
pcChars->Append(c);
}
pcChars->Append('0', iStop - 1);
pcChars->Append('.');
}
else if ((iStart >= 1) && (iStop >= 1))
{
for (i = iStart; i >= iStop; i--)
{
c = GetDigitUnsafe(i) + '0';
pcChars->Append(c);
if (i == iStart)
{
pcChars->Append('.');
}
}
pcChars->Append('e');
pcChars->Append('+');
pcChars->Append(iStart - 1);
}
else if ((iStart <= -1) && (iStart >= -4) && (iStop <= -1))
{
pcChars->Append('0');
pcChars->Append('.');
pcChars->Append('0', (-iStart) -1);
for (i = iStart; i >= iStop; i--)
{
c = GetDigitUnsafe(i) + '0';
pcChars->Append(c);
}
}
else if ((iStart < 0) && (iStop < 0))
{
for (i = iStart; i >= iStop; i--)
{
c = GetDigitUnsafe(i) + '0';
pcChars->Append(c);
if (i == iStart)
{
pcChars->Append('.');
}
}
pcChars->Append('e');
pcChars->Append(iStart);
}
if (!IsClean())
{
pcChars->Append(" (Unclean!)");
}
return true;
}
void CNumber::Print(CChars* pcChars)
{
int32 iFirstDigit;
int32 iLastDigit;
int32 i;
char c;
int32 iStart;
int32 iStop;
if (IsNAN())
{
pcChars->Append("Not a number");
return;
}
if (IsDivisionByZero())
{
pcChars->Append("Division by zero");
return;
}
if (IsOverflow())
{
if (!IsNegative())
{
pcChars->Append("Positive ");
}
else
{
pcChars->Append("Negative ");
}
pcChars->Append("overflow");
return;
}
if (IsNegative())
{
pcChars->Append("-");
}
iFirstDigit = GetFirstNonZeroDigit();
iLastDigit = GetLastNonZeroDigit();
iStart = iFirstDigit;
if (iFirstDigit < 0)
{
iStart = 1;
}
iStop = iLastDigit;
if (iLastDigit > 0)
{
iStop = 1;
}
for (i = iStart; i >= iStop; i--)
{
if (i != 0)
{
c = SafeGetDigit(i) + '0';
pcChars->Append(c);
}
else
{
pcChars->Append('.');
}
}
if (!IsClean())
{
pcChars->Append(" (Unclean!)");
}
}
void CNumber::Dump(void)
{
Dump(true);
}
void CNumber::Dump(bool bNewLine)
{
CChars sz;
sz.Init();
Print(&sz);
if (bNewLine)
{
sz.AppendNewLine();
}
sz.Dump();
sz.Kill();
}
size CNumber::ByteSize(void)
{
return (mcMaxWholeNumbers + mcMaxDecimals + sizeof(CNumberDetail));
}
