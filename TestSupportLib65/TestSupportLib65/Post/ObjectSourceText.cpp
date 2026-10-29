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
typedef uint32 chunkName;
struct SChunkFileHeader
{
chunkName miUserID;
filePos miChunkNamesPos;
char macMD5Hash[16];
uint32 miMagic;
void WriteInit(chunkName iUserID);
};
class CChunkHeader
{
public:
chunkName miName;
filePos miChunkSize;
filePos miChunkIndexPos;
char macMD5Hash[16];
uint32 miMagic;
void WriteInit(void);
};
class CFileBasic : public CFileIO
{
protected:
CAbstractFile* mpcFile;
public:
void Init(CAbstractFile* pcFile);
void Kill(void);
bool Open(EFileMode eMode);
bool Close();
bool Seek(filePos iOffset, EFileSeekOrigin eOrigin);
bool Seek(filePos iOffset);
bool Flush(void);
bool Delete(void);
bool IsOpen(void);
filePos GetFileLength(void);
filePos GetFilePos(void);
filePos Tell(void);
filePos Size(void);
bool Truncate(filePos iSize);
const char* GetFilename(void);
lsize Write(const void* pvSource, lsize iSize, lsize iCount);
lsize Read(void* pvDest, lsize iSize, lsize iCount);
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
class CDataFree
{
public:
virtual void FreeData(void* pvData) =0;
};
struct SDataTypeIO
{
bool Save(CFileWriter* pcFileWriter);
bool Load(CFileReader* pcFileReader);
};
typedef bool (SDataTypeIO::*DataIO_FileWriter)(CFileWriter*);
typedef bool (SDataTypeIO::*DataIO_FileReader)(CFileReader*);
struct SDataIO
{
DataIO_FileWriter fWriter;
DataIO_FileReader fReader;
};
class CDataIO
{
public:
virtual bool WriteData(CFileWriter* pcFileWriter, void* pvData) =0;
virtual bool ReadData(CFileReader* pcFileReader, void* pvData) =0;
};
template<class M>
bool SaveMultiple(M* psThis, CFileWriter* pcFileWriter, size uiCount)
{
size i;
bool bResult;
for (i = 0; i < uiCount; i++)
{
bResult = psThis->Save(pcFileWriter);
if (!bResult)
{
return false;
}
psThis++;
}
return true;
}
template<class M>
bool LoadMultiple(M* psThis, CFileReader* pcFileReader, size uiCount)
{
size i;
bool bResult;
for (i = 0; i < uiCount; i++)
{
bResult = psThis->Load(pcFileReader);
if (!bResult)
{
return false;
}
psThis++;
}
return true;
}
class CMapBlock;
struct SMNode
{
size iKeySize;
size iValueSize;
DataCompare fKeyCompare;
int KeyCompare(const void* arg1, const void* arg2);
};
int CompareMNode(const void* arg1, const void* arg2);
int CompareMNodeKey(const void* arg1, const void* arg2);
typedef CArrayTemplate<CArrayBlock> CArrayArrayBlock;
struct SArraySortedIterator
{
size iArrayBlock;
size iIndex;
};
class CChars;
class CArrayBlockSorted : public CMalloc
{
protected:
CArrayBlock maSortedArray;
CArrayArrayBlock maaHoldingArrays;
DataCompare mfCompare;
size* mapiInsertionIndices;
size miElementSize;
size miHoldingBufferSize;
bool mbOverwrite;
public:
void _Init(void);
void Init(size iElementSize, DataCompare fCompare);
void Init(size iElementSize, size iHoldingBufferSize, size iHoldingBuffers, DataCompare fCompare);
void Init(CMallocator* pcMalloc, size iElementSize, size iHoldingBufferSize, size iHoldingBuffers, DataCompare fCompare);
void Kill(void);
bool Add(void* pv);
void* Get(void* pv);
bool Contains(void* pv);
bool Remove(void* pv);
void* StartIteration(SArraySortedIterator* psIter);
void* Iterate(SArraySortedIterator* psIter);
void* GetIterated(SArraySortedIterator* psIter);
size ByteSize(void);
bool WriteHeader(CFileWriter* pcFileWriter);
bool WriteHeader(CFileWriter* pcFileWriter, size uiFileElementSize);
bool Write(CFileWriter* pcFileWriter);
bool ReadHeader(CMallocator* pcMalloc, CFileReader* pcFileReader, DataCompare fCompare);
bool ReadHeader(CMallocator* pcMalloc, CFileReader* pcFileReader, DataCompare fCompare, size uiFileElementSize, size uiElementSize);
bool Read(CFileReader* pcFileReader, DataCompare fCompare);
void SetOverwrite(bool bOverwrite);
size NumElements(void);
size GetSortedSize(void);
size GetHoldingSize(void);
void* GetInSorted(size iIndex);
void* GetInHolding(size iArray, size iIndex);
size InsertHoldingIntoSorted(void);
CArrayBlock* GetSortedArray(void);
void Print(CChars* psz);
void Dump(void);
size Sort(void);
bool IsSorted(void);
DataCompare GetCompare(void);
protected:
bool AddIntoHoldingArrays(void* pv, bool* pbUpdateSortedArray);
void ClearHoldingArrays(void);
void MergeHoldingArrays(CArrayBlock* paMergedArray);
void SortMerge(CArrayBlock* paMergedArray);
void InsertHoldingIntoSorted(size* paiInsertionIndices, size oldLength, CArrayBlock* paSourceArray);
size* CalculateInsertionIndices(CArrayBlock* paMergedHoldingArrays);
void* FindInHoldingArrays(void* pv);
void* FindInSortedArray(void* pv);
bool RemoveFromHoldingArrays(void* pv);
bool RemoveFromSortedArray(void* pv);
CArrayBlock* GetArrayBlock(size iIndex);
bool InsertIntoArrayBlock(CArrayBlock* paBlock, void* pv);
};
struct SMapIterator : SArraySortedIterator
{
};
class CMapBlock : public CMalloc, public CDataIO
{
friend struct SMNode;
protected:
CArrayBlockSorted mapArray;
size miLargestKeySize;
bool mbOverwrite;
CDataFree* mpcDataFree;
CDataIO* mpcDataIO;
DataCompare mfKeyCompare;
public:
void _Init(void);
void Init(bool bOverwrite = true);
void Init(CMallocator* pcMalloc, bool bOverwrite = true);
void Init(DataCompare fKeyCompare, bool bOverwrite = true);
void Init(CMallocator* pcMalloc, DataCompare fKeyCompare, bool bOverwrite = true);
void Init(CMallocator* pcMalloc, DataCompare fKeyCompare, DataCompare fNodeCompare, bool bOverwrite);
void Kill(void);
void ReInit(void);
bool Get(const void* pvKey, size iKeySize, void** ppvData, size* piDataSize);
void* Get(const void* pvKey, size iKeySize);
SMNode* GetNode(const void* pvKey, size iKeySize);
SMNode* GetNode(SMapIterator* psIterator);
void* Put(const void* pvKey, size iKeySize, size iDataSize);
bool Put(const void* psKey, size iKeySize, const void* pvData, size iDataSize);
bool Remove(const void* pvKey, size iKeySize);
size DataSize(void* pvKey, size iKeySize);
bool HasKey(const void* pvKey, size iKeySize);
size NumElements(void);
size GetSortedSize(void);
size GetHoldingSize(void);
size NonNullElements(void);
CArrayBlockSorted* GetArray(void);
void SetDataFreeCallback(CDataFree* pcDataFree);
void SetDataIOCallback(CDataIO* pcDataIO);
bool StartIteration(SMapIterator* psIterator, void** ppvKey, size* piKeySize, void** ppvData, size* piDataSize);
bool Iterate(SMapIterator* psIterator, void** ppvKey, size* piKeySize, void** ppvData, size* piDataSize);
bool Write(CFileWriter* pcFileWriter);
bool Read(CFileReader* pcFileReader);
bool Read(CFileReader* pcFileReader, DataCompare fKeyCompare);
bool Read(CFileReader* pcFileReader, DataCompare fKeyCompare, CDataIO* pcDataIO, CDataFree* pcDataFree);
bool WriteMapBlockHeader(CFileWriter* pcFileWriter);
bool ReadMapBlockHeader(CFileReader* pcFileReader, DataCompare fKeyCompare, CDataIO* pcDataIO, CDataFree* pcDataFree);
bool WriteMapBlockElements(CFileWriter* pcFileWriter);
bool ReadMapBlockElements(CFileReader* pcFileReader);
size ByteSize(void);
void Dump(void);
void Pack(void);
public:
SMNode* WriteSizes(CFileWriter* pcFileWriter, size iIndex);
SMNode* ReadSizes(CFileReader* pcFileReader, size iIndex);
void* GetValue(SMNode* psNode);
void* GetKey(SMNode* psNode);
static void RemapKeyAndData(SMNode* psNode, void** ppvKey, void** ppvData);
size Sort(void);
bool IsSorted(void);
SMNode* AllocateNode(size iKeySize, size iDataSize);
void FreeNode(SMNode* psNode);
bool GetInSorted(size iIndex, void** ppvKey, void** ppvData);
bool PutInSorted(size iIndex, void** ppvKey, size uiKeySize, void** ppvData, size uiValueSize);
void* GetKeyInSorted(size iIndex);
protected:
void InsertHoldingIntoSorted(void);
bool WriteData(CFileWriter* pcFileWriter, void* pvData);
bool ReadData(CFileReader* pcFileReader, void* pvData);
};
class CMapStringBlock : public CMapBlock
{
public:
void Init(bool bCaseSensitive = true, bool bOverwrite = true);
void Init(CMallocator* pcMalloc, bool bCaseSensitive = true, bool bOverwrite = true);
void Kill(void);
void* Get(const char* szKey);
void* Get(const char* szKey, size* puiDataSize);
void* Put(const char* szKey, size uiDataSize);
bool Put(const char* szKey, const void* psData, size uiDataSize);
bool Remove(const char* szKey);
bool HasKey(const char* szKey);
bool WriteCaseSensitivity(CFileWriter* pcFileWriter);
bool Write(CFileWriter* pcFileWriter);
DataCompare ReadCaseSensitivity(CFileReader* pcFileReader);
bool Read(CFileReader* pcFileReader);
bool Read(CFileReader* pcFileReader, CDataIO* pcDataIO, CDataFree* pcDataFree);
char* GetKeyForData(void* psData);
bool IsCaseSensitive(void);
void SetCaseSensitive(bool bCaseSensitive);
void GetKeysAsString(CChars* pszDest, char* szSeparator);
protected:
DataCompare CalculateCompareFunc(bool bCaseSensitive);
};
template<class D>
class CMapStringTemplate : public CMapStringBlock
{
friend class CMapStringUnknown;
public:
D* Get(const char* szKey);
D* Put(const char* szKey);
bool Put(const char* szKey, D* psData);
};
template<class D>
D* CMapStringTemplate<D>::Get(const char* szKey)
{
return (D*)CMapStringBlock::Get(szKey);
}
template<class D>
D* CMapStringTemplate<D>::Put(const char* szKey)
{
return (D*)CMapStringBlock::Put(szKey, sizeof(D));
}
template<class D>
bool CMapStringTemplate<D>::Put(const char* szKey, D* psData)
{
return CMapStringBlock::Put(szKey, psData, sizeof(D));
}
template<class D>
class CMapStringPrimitive : public CMapStringTemplate<D>
{
public:
using CMapStringTemplate<D>::StartIteration;
using CMapStringTemplate<D>::Iterate;
D Get(const char* szKey, D sNullValue = -1);
bool Put(const char* szKey, D sData);
char* GetWithValue(D sData);
};
template<class D>
D CMapStringPrimitive<D>::Get(const char* szKey, D sNullValue)
{
D* psData;
psData = (CMapStringTemplate<D>::Get(szKey));
if (psData)
{
return *psData;
}
else
{
return sNullValue;
}
}
template<class D>
bool CMapStringPrimitive<D>::Put(const char* szKey, D sData)
{
return CMapStringTemplate<D>::Put(szKey, &sData);
}
template<class D>
char* CMapStringPrimitive<D>::GetWithValue(D sData)
{
SMapIterator sIter;
char* szKey;
D* piData;
bool bResult;
bResult = StartIteration(&sIter, (void**)&szKey, 0L, (void**)&piData, 0L);
while (bResult)
{
if (*piData == sData)
{
return szKey;
}
bResult = Iterate(&sIter, (void**)&szKey, 0L, (void**)&piData, 0L);
}
return 0L;
}
class CMapStringInt : public CMapStringPrimitive<int32>
{
};
struct SChunkIndex
{
chunkName miName;
filePos miChunkSize;
filePos miChunkDataPos;
void Init(filePos iChunkDataPos, chunkName iName, filePos iChunkSize);
};
typedef CArrayTemplate<SChunkIndex> CChunkIndexArray;
class CChunkIndex
{
protected:
chunkName miSearchName;
size miCurrChunkNum;
public:
CChunkIndexArray mcChunkIndices;
void ReadInit(void);
void WriteInit(void);
void Kill(void);
size FindFirstChunkWithName(chunkName iName);
size FindNextChunkWithName(void);
size GetNumChunksWithName(chunkName iName);
};
struct SMD5Context
{
uint32 i[2];
uint32 buf[4];
uint8 in[64];
uint8 digest[16];
};
void MD5Init(SMD5Context* mdContext);
void MD5Update(SMD5Context* mdContext, uint8*, uint32);
void MD5Final(SMD5Context* mdContext);
void MD5Transform(uint32*, uint32*);
void MD5Dump(SMD5Context* ctx);
class CChunkStackElement
{
public:
CChunkHeader sHeader;
filePos iChunkHeaderPos;
bool bContainsChunks;
CChunkIndex cChunkIndex;
SMD5Context sMD5Context;
void Init(filePos iFilePos);
};
typedef CArrayTemplate<CChunkStackElement> CChunkStack;
class CChunkFile : public CFileBasic
{
protected:
CChunkStack mcChunkStack;
bool mbLastHashCheck;
CMapStringInt mmsziNames;
SChunkFileHeader msHeader;
chunkName miLastName;
bool __PrivateReadChunkBegin(void);
bool __PrivateReadChunkIndex(filePos iIndexPos, CChunkIndex* pcIndex);
public:
void _Init(void);
void Init(CAbstractFile* pcFile);
void Kill(void);
bool ReadOpen(void);
bool ReadClose(void);
bool WriteOpen(void);
bool WriteOpen(chunkName iUserID);
bool WriteClose(void);
size FindFirstChunkWithName(const char* szName);
size FindNextChunkWithName(void);
size GetNumChunks(void);
void* GetMD5Hash(void);
bool ContainsChunks(void);
bool ReadChunkBegin(size iChunkIndex);
bool ReadChunkBegin(const char* szName);
bool ReadChunkEnd(void);
bool ReadChunkEnd(size iNumChunksToEnd);
bool ReadChunkEndAll(void);
bool WriteChunkBegin(void);
bool WriteChunkEnd(const char* szChunkName);
size StackDepth(void);
filePos ChunkSize(void);
filePos ChunkStart(void);
char* GetTailChunkNameForIndex(size iIndex);
bool SeekStart(void);
protected:
size FindFirstChunkWithID(chunkName iName);
size GetNumChunksWithID(chunkName iName);
bool ReadChunkNames(void);
bool WriteChunkNames(void);
bool WriteChunkEnd(chunkName iChunkName);
bool WriteBasic(const void* pvSource, size uiSize);
chunkName GetTailChunkNameIndex(size iChunkNum);
};
class CUnknowns;
class CUnknown : public CConstructable, public CKillable
{
public:const char* ClassName(void){ return "CUnknown";}size ClassSize(void){ return sizeof(CUnknown);}
protected:
CUnknowns* mpcUnknownsThisIn;
public:
CUnknown();
void SetUnknowns(CUnknowns* pcUnknowns);
void Kill(void) override;
virtual bool IsUnknown(void);
virtual bool Iterable(void);
bool SaveHeader(CFileWriter* pcFile);
virtual bool Save(CFileWriter* pcFile);
virtual bool Load(CFileReader* pcFile);
void Print(CChars* psz) override;
void Dump(void);
virtual int Compare(CUnknown* pcRight);
CUnknowns* GetUnknownsThisIn(void);
void SetNotInUnknowns(void);
void NotImplemented(char* szMethod);
};
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
int ComparePtr(const void* arg1, const void* arg2);
int ComparePtrPtr(const void* arg1, const void* arg2);
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
typedef int64 OIndex;
typedef CArrayTemplatePrimitive<OIndex> CArrayOIndex;
bool IsValidIndex(OIndex oi);
char* IndexToString(OIndex oi);
typedef int sig_atomic_t;
typedef void (*__sighandler_t)(int);
__sighandler_t signal(int iSignal, __sighandler_t fHandler);
int raise(int iSignal);
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
class CStackPointers
{
protected:
CFreeList mcFreeList;
public:
void Init(void);
void Kill(void);
CStackPointer* Add(CPointer* pcPointer);
CStackPointer* Add(CPointer* pcPointer, CStackPointer* pcFirst);
CStackPointer* Add(CCollection* pcCollection);
CStackPointer* Add(CCollection* pcCollection, CStackPointer* pcFirst);
bool SetLastNext(CStackPointer* pcStackPointer, CStackPointer* pcFirst);
void RemoveAll(CStackPointer* pcFirst);
CStackPointer* Remove(CStackPointer* pcFirst, CPointer* pcPointer, bool* pbRemoved);
CStackPointer* Remove(CStackPointer* pcFirst, CCollection* pcCollection, bool* pbRemoved);
void ClearAllPointers(void);
size NumElements(void);
CStackPointer* Get(size uiIndex);
CStackPointer* StartIteration(SFreeListIterator* psIter);
CStackPointer* Iterate(SFreeListIterator* psIter);
};
extern CStackPointers gcStackPointers;
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
class CEmbeddedObject;
typedef CArrayTemplatePtr<CEmbeddedObject> CArrayEmbeddedObjectPtr;
typedef CArrayTemplateEmbeddedPtr<CEmbeddedObject, 8> CArrayEmbeddedObjectPtrE8;
class CBaseObject;
typedef CArrayTemplatePtr<CBaseObject> CArrayBaseObjectPtr;
typedef CArrayTemplateEmbeddedPtr<CBaseObject, 32> CArrayBaseObjectPtrE32;
class CPointer;
typedef CArrayTemplateEmbedded<SStackPointer, 32> CArrayStackPointerE32;
class CBaseObject;
struct SDistToRoot
{
CBaseObject* pcObject;
int iExpectedDist;
};
typedef CArrayTemplate<SDistToRoot> CArrayDistToRoot;
class CDistCalculatorParameters
{
private:
CArrayBaseObjectPtrE32 mapcTouched;
CArrayDistToRoot macExpectedDists;
CArrayBaseObjectPtrE32 mapcDetachedFromRoot;
CArrayBaseObjectPtr mapcCompletelyDetached;
public:
void Init(void);
void Kill(void);
void AddExpectedDist(CBaseObject* pcObject, int iExpectedDist);
SDistToRoot* GetLowestExpectedDist(void);
size NumExpectedDists(void);
SDistToRoot* GetExpectedDist(int iIndex);
SDistToRoot* GetExpectedDist(CBaseObject* pcObject);
void RemoveExpectedDist(int iIndex);
void RemoveExpectedDist(SDistToRoot* psDistToRoot);
void AddDetachedFromRoot(CBaseObject* pcObject);
size NumDetachedFromRoot(void);
CBaseObject* GetDetachedFromRoot(size iIndex);
void AddCompletelyDetached(CBaseObject* pcObject);
size NumCompletelyDetached(void);
CBaseObject* GetCompletelyDetached(size iIndex);
void RemoveCompletelyDetached(size iIndex);
void CopyRootDetachedToCompletelyDetached(void);
CArrayBaseObjectPtr* GetCompletelyDetachedArray(void);
void AddTouched(CBaseObject* pcObject);
size NumTouched(void);
CBaseObject* GetTouched(size iIndex);
void ClearTouchedFlags(void);
void Print(CChars* psz, bool bCommaSeparate = true);
void Dump(void);
void PrintArray(CChars* psz, CArrayBaseObjectPtrE32* pcArray, bool bCommaSeparate);
void PrintArray(CChars* psz, CArrayBaseObjectPtr* pcArray, bool bCommaSeparate);
void PrintArray(CChars* psz, CArrayDistToRoot* pcArray, bool bCommaSeparate);
};
class CDistToRootCalculator
{
friend class CDistCalculator;
public:
void Calculate(CBaseObject* pcObject, CDistCalculatorParameters* pcParameters);
protected:
void CollectAndClearInvalidRootDistances(CBaseObject* pcFromChanged, CDistCalculatorParameters* pcParameters);
void UpdateAttachedTosDistToRoot(CDistCalculatorParameters* pcParameters);
void ResetObjectsToUnattachedDistToRoot(CDistCalculatorParameters* pcParameters);
void ValidateExpectedDistStartingObjects(CBaseObject* pcObject, CDistCalculatorParameters* pcParameters);
};
class CDistToStackCalculator
{
friend class CDistCalculator;
public:
void Calculate(CBaseObject* pcFromChanged, CDistCalculatorParameters* pcParameters);
void CalculateFromTouched(CDistCalculatorParameters* pcParameters);
void ResetObjectsToUnknownDistToStack(CDistCalculatorParameters* pcParameters);
protected:
size CollectDetachedAndSetDistToStackZero(CDistCalculatorParameters* pcParameters);
void InitialiseCompletelyDetached(CDistCalculatorParameters* pcParameters);
int UpdateDistToStackForObjectsWithFromStackDist(CDistCalculatorParameters* pcParameters);
void UpdateDistToStackForAllObjects(CDistCalculatorParameters* pcParameters);
void ResetObjectsToUnattachedDistToRoot(CDistCalculatorParameters* pcParameters);
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
class CObject;
class CPrimitiveObject
{
private:
uint16 muiClassType;
uint16 muiNegativeEmbeddingOffset;
public:
CPrimitiveObject(EPrimitiveType eType);
EPrimitiveType GetClassType(void);
void SetEmbedding(CObject* pcEmbedding);
void SetDirty(void);
CObject* Embedding(void);
};
void LogPrimitiveAccessDebug(CPrimitiveObject* pvThis, const char* szMethod);
void LogPrimitiveAssignDebug(CPrimitiveObject* pvThis, const char* szMethod);
template<class PRIMITIVE_TYPE>
class CPrimitive : public CPrimitiveObject
{
friend class CPrimitiveClasses;
protected:
PRIMITIVE_TYPE mVal;
public:
CPrimitive(EPrimitiveType eType) : CPrimitiveObject(eType) {}
void Assign(PRIMITIVE_TYPE val)
{
LogPrimitiveAssignDebug((CPrimitiveObject*)this, __PRETTY_FUNCTION__);
if (mVal != val)
{
mVal = val;
SetDirty();
}
}
operator PRIMITIVE_TYPE() const
{
LogPrimitiveAccessDebug((CPrimitiveObject*)this, __PRETTY_FUNCTION__);
return mVal;
}
PRIMITIVE_TYPE* GetPrimitivePointer(void)
{
return &mVal;
}
};
enum EFreeResult
{
FR_Error,
FR_Freed,
FR_NotFreed,
};
class CObject;
class CObjects;
class CObjectWriter;
class CObjectReader;
class CClass;
class CPointer;
class CEmbeddedObject;
struct SHeapFromPointer
{
CBaseObject* pcFrom;
CEmbeddedObject* pcTo;
CPointer* pcPointer;
};
typedef CArrayTemplate<SHeapFromPointer> CArrayHeapFromPointer;
class CEmbeddedObject : public CUnknown
{
friend class CPointer;
friend class CCollection;
public:const char* ClassName(void){ return "CEmbeddedObject";}size ClassSize(void){ return sizeof(CEmbeddedObject);}
protected:
CBaseObject* mpcEmbedded;
CArrayTemplateEmbeddedPtr<CBaseObject, 4> mapHeapFromObjects;
CArrayTemplateEmbeddedPtr<CBaseObject, 2> mapHeapFromCollections;
CStackPointer* mpcStackFroms;
public:
CEmbeddedObject();
~CEmbeddedObject();
void Kill(void);
virtual void KillInternal(bool bHeapFromChanged, bool bValidateNotEmbedded);
virtual void Evict(void);
virtual void FreeInternal(void) =0;
virtual void DoneKill(bool bAllocatedInObjects) =0;
virtual void FreePointers(void);
void PostRemapFroms(void);
virtual bool Save(CObjectWriter* pcFile) =0;
virtual bool Load(CObjectReader* pcFile) =0;
virtual bool IsHollow(void) =0;
virtual size RemapPointerTos(CEmbeddedObject* pcOld, CEmbeddedObject* mpcObject);
virtual bool SetDistToRoot(int iDistToRoot) =0;
virtual void SetPointerTosExpectedDistToRoot(int iDistToRoot) =0;
virtual bool TestedForRoot(void) =0;
virtual int GetDistToRoot(void) =0;
virtual int GetDistToStack(void) =0;
virtual OIndex GetIndex(void);
virtual bool IsNamed(void);
virtual char* GetName(void);
virtual void FreeIdentifiers(void);
virtual bool IsDirty(void) =0;
virtual void SetDirty(bool bDirty) =0;
void LogicalDirty(void);
virtual bool IsBaseObject(void);
virtual void RemovePointerTo(CEmbeddedObject* pcTo) =0;
CBaseObject* GetEmbeddingContainer(void);
bool IsEmbeddingContainerAllocatedInObjects(void);
bool IsEmbedded(void);
bool IsNotEmbedded(void);
virtual bool IsInitialised(void) =0;
bool IsInStack(void);
virtual bool IsRoot(void) =0;
virtual size GetEmbeddedIndex(CEmbeddedObject* pcEmbedded);
virtual size NumEmbedded(void) =0;
void SetEmbedding(CBaseObject* pcEmbedded);
virtual CEmbeddedObject* GetEmbeddedObject(size iIndex) =0;
virtual CBaseObject* Dehollow(void) =0;
bool IsAllocatedInObjects(void);
virtual void ValidateConsistency(void) =0;
void ValidateFrom(CBaseObject* pcBaseObject);
void ValidateFroms(void);
void ValidatePointerTo(CEmbeddedObject* pcPointedTo);
virtual void ValidatePointerTos(void);
virtual size NumPointerTos(void) =0;
virtual size BaseNumPointerTos(void);
virtual void GetPointerTos(CArrayEmbeddedObjectPtr* papcTos) =0;
virtual void BaseGetPointerTos(CArrayEmbeddedObjectPtr* papcTos);
virtual void CollectAndClearPointerTosInvalidDistToRootObjects(CDistCalculatorParameters* pcParameters);
virtual size CollectDetachedFroms(CDistCalculatorParameters* pcParameters) =0;
bool HasHeapFroms(void);
void AddHeapFrom(CBaseObject* pcFromObject, bool bValidate);
EFreeResult RemoveHeapFromTryFree(CBaseObject* pcFromObject, bool bValidate);
virtual size NumHeapFroms(void);
CBaseObject* GetHeapFrom(size iFromIndex);
void AddHeapPointerForRemap(CBaseObject* pcFromObject);
void GetHeapFromPointers(CArrayHeapFromPointer* pacPointers);
virtual void GetPointerFieldsTo(CEmbeddedObject* pcTo, CArrayHeapFromPointer* pacPointers);
bool AddStackFrom(CPointer* pcPointer, bool bValidate);
bool AddStackFrom(CCollection* pcCollection, bool bValidate);
bool AddStackPointersForRemap(CStackPointer* pcStackPointer);
bool HasStackFroms(void);
bool PrivateRemoveStackFrom(CPointer* pcPointer);
bool PrivateRemoveStackFrom(CCollection* pcCollection);
EFreeResult RemoveStackFromTryFree(CPointer* pcPointer);
EFreeResult RemoveStackFromTryFree(CCollection* pcCollection);
virtual size NumStackFroms(void);
CStackPointer* GetFirstStackFrom(void);
virtual CEmbeddedObject* GetClosestHeapFromToStack(void);
size NumTotalFroms(void);
bool ContainsFrom(CEmbeddedObject* pcBaseObject);
virtual CEmbeddedObject* GetClosestFromToRoot(void);
virtual CClass* GetClass(void) =0;
virtual void CopyFields(CEmbeddedObject* pcOther);
virtual bool HasNes(void) =0;
virtual bool HasNesPointerToThis(CEmbeddedObject* pcBaseObject) =0;
CEmbeddedObject* GetNesPointerFrom(size* piStart);
CObjects* GetObjects(void);
virtual CObjects* GetObjectsThisIn(void) =0;
char* PrintObject(CChars* psz);
char* PrintObject(CChars* psz, bool bEmbedded, bool bPointerMemory = true);
bool FailExpectedToBeInitialised(char* szMethod);
bool FailExpectedToNotBeInitialised(char* szMethod);
bool FailCantInitFreedObject(char* szMethod);
bool FailNotExpectedToBeEmbedded(char* szMethod);
bool TestRemoveHeapFrom(CBaseObject* pcFromObject);
bool TestRemoveStackFrom(CPointer* pcPointer);
void DumpHeapFroms(void);
protected:
bool LinkStackFrom(CStackPointer* pcStackPointer);
virtual void Allocate(CObjects* pcObjects);
void AddHeapPointer(CBaseObject* pcFromObject);
virtual void RemoveAllHeapFroms(void);
virtual void RemoveAllStackFroms(void);
bool PrivateRemoveHeapFrom(CBaseObject* pcFrom);
virtual void GetStackFroms(CArrayStackPointerE32* papcFroms);
virtual void GetHeapFroms(CArrayBaseObjectPtrE32* papcFroms);
CStackPointers* GetStackPointers(void);
virtual CEmbeddedObject* GetClosestFromForCanFindRoot(void);
virtual void UpdateAttachedEmbeddedObjectPointerTosDistToRoot(CDistCalculatorParameters* pcParameters, int iExpectedDist) =0;
void ValidateObjectsConsistency(bool bValidate);
};
char* ObjectToString(CEmbeddedObject* pcObject);
char* ObjectToString(CEmbeddedObject* pcObject, bool bEmbedded);
extern bool gbLogPointer;
class CEmbeddedObject;
class CObject;
class CObjectReader;
class CPointer
{
template<class M>
friend class Ptr;
protected:
CEmbeddedObject* mpcObject;
CObject* mpcEmbedding;
public:
CPointer();
CPointer(CEmbeddedObject* pcObject);
CPointer(CPointer& pcPointer);
CPointer(const CPointer& pcPointer);
~CPointer();
void operator = (CEmbeddedObject* pcObject);
void operator = (CPointer& pcPointer);
void operator = (const CPointer& pcPointer);
CEmbeddedObject* operator -> ();
CEmbeddedObject* operator & ();
bool operator ! ();
bool operator == (const CPointer& pcPointer);
bool operator != (const CPointer& pcPointer);
bool operator == (void* pcPointer);
bool operator != (void* pcPointer);
void SetEmbedding(CObject* pcEmbedding);
bool IsNotNull(void) const;
bool IsNull(void) const;
bool IsNotEqual(CPointer& pcPointer);
bool IsEqual(CPointer& pcPointer);
bool IsEqual(CEmbeddedObject* pcObject);
CPointer* This(void);
CObject* Embedding(void);
CEmbeddedObject* Object(void) const;
CEmbeddedObject** ObjectPtr(void);
void UnsafePointTo(CEmbeddedObject* pcNewObject);
CBaseObject* BaseObject(void);
size MorphInto(CEmbeddedObject* pcNew);
bool IsHollow(void);
bool Load(CObjectReader* pcFile);
int GetDistToRoot(void);
int GetDistToStack(void);
OIndex GetIndex(void);
char* GetName(void);
bool IsNamed(void);
const char* ClassName(void);
CClass* GetClass(void);
bool IsDirty(void);
void LogicalDirty(void);
bool IsEmbeddingAllocatedInObjects(void);
void Kill(void);
void AssignObject(CEmbeddedObject* pcObject);
CEmbeddedObject* Dereference(void);
CEmbeddedObject* DereferenceArrow(void);
void AddHeapFrom(CBaseObject* pcFrom);
void PointToNull(void);
CEmbeddedObject* Return(void);
void UnsafeClearObject(void);
size NumStackFroms(void);
size NumHeapFroms(void);
size NumEmbedded(void);
size NumPointerTos(void);
void DumpFroms(void);
void DumpPointerTos(void);
void Dump(void);
protected:
void PointTo(CEmbeddedObject* pcObject);
bool IsEmbeddingHeld(void);
};
void LogPointerDebug(CPointer* pvThis, const char* szMethod);
class CObject;
template<class M = CEmbeddedObject>
class Ptr : public CPointer
{
public:
Ptr() : CPointer() {};
Ptr(CEmbeddedObject* pcObject) : CPointer(pcObject) {};
Ptr(CPointer& cPointer) : CPointer(cPointer) {};
Ptr(const CPointer& cPointer) : CPointer(cPointer) {};
Ptr(Ptr& cPointer) : CPointer(cPointer) {};
Ptr(const Ptr& cPointer) : CPointer(cPointer) {};
using CPointer::operator =;
Ptr& operator = (const Ptr& cPointer) { CPointer::operator = (cPointer); return *this; };
M* operator -> ();
M* operator & ();
Ptr<M> operator + (Ptr<M> obj);
Ptr<M> operator + (const char* sz);
explicit operator bool() const;
const char* TemplateClassName(void);
};
bool IsValidPointerClassAllowNull(char* szParameter, const char* szInstanceClassName, const char* szExpectedClassName);
bool FailValidPointerClassAllowNull(char* szMethod, char* szParameter, const char* szInstanceClassName, const char* szExpectedClassName);
template<class M>
M* Ptr<M>::operator -> ()
{
return (M*)DereferenceArrow();
}
template<class M>
M* Ptr<M>::operator & ()
{
return (M*)Dereference();
}
template<class M>
Ptr<M> Ptr<M>::operator + (Ptr<M> pObject)
{
M* p = (M*)DereferenceArrow();
if (p)
{
return p->AddOperator(pObject);
}
else
{
return Ptr();
}
}
template<class M>
Ptr<M> Ptr<M>::operator + (const char* sz)
{
M* p = (M*)DereferenceArrow();
if (p)
{
return p->AddOperator(sz);
}
else
{
return Ptr();
}
}
template<class M>
Ptr<M>::operator bool() const
{
return mpcObject != 0L;
}
template<class M>
const char* Ptr<M>::TemplateClassName(void)
{
const char* szClassName;
M m;
szClassName = m.ClassName();
return szClassName;
}
class Int8 : public CPrimitive<int8> { public:const char* ClassName(void){ return "Int8";}size ClassSize(void){ return sizeof(Int8);} public: Int8() : CPrimitive(PT_char8) {} Int8& operator= (int8 val) { Assign(val); return *this; } bool Save(CFileWriter* pcFile) { return pcFile-> WriteInt8 (mVal); } bool Load(CFileReader* pcFile) { return pcFile-> ReadInt8 (&mVal); } };
class UInt8 : public CPrimitive<uint8> { public:const char* ClassName(void){ return "UInt8";}size ClassSize(void){ return sizeof(UInt8);} public: UInt8() : CPrimitive(PT_uint8) {} UInt8& operator= (uint8 val) { Assign(val); return *this; } bool Save(CFileWriter* pcFile) { return pcFile-> WriteInt8 (mVal); } bool Load(CFileReader* pcFile) { return pcFile-> ReadInt8 (&mVal); } };
class SInt : public CPrimitive<int> { public:const char* ClassName(void){ return "SInt";}size ClassSize(void){ return sizeof(SInt);} public: SInt() : CPrimitive(PT_int) {} SInt& operator= (int val) { Assign(val); return *this; } bool Save(CFileWriter* pcFile) { return pcFile-> WriteSInt (mVal); } bool Load(CFileReader* pcFile) { return pcFile-> ReadSInt (&mVal); } };
class SUInt : public CPrimitive<uint> { public:const char* ClassName(void){ return "SUInt";}size ClassSize(void){ return sizeof(SUInt);} public: SUInt() : CPrimitive(PT_uint) {} SUInt& operator= (uint val) { Assign(val); return *this; } bool Save(CFileWriter* pcFile) { return pcFile-> WriteSInt (mVal); } bool Load(CFileReader* pcFile) { return pcFile-> ReadSInt (&mVal); } };
class Int16 : public CPrimitive<int16> { public:const char* ClassName(void){ return "Int16";}size ClassSize(void){ return sizeof(Int16);} public: Int16() : CPrimitive(PT_int16) {} Int16& operator= (int16 val) { Assign(val); return *this; } bool Save(CFileWriter* pcFile) { return pcFile-> WriteInt16 (mVal); } bool Load(CFileReader* pcFile) { return pcFile-> ReadInt16 (&mVal); } };
class UInt16 : public CPrimitive<uint16> { public:const char* ClassName(void){ return "UInt16";}size ClassSize(void){ return sizeof(UInt16);} public: UInt16() : CPrimitive(PT_uint16) {} UInt16& operator= (uint16 val) { Assign(val); return *this; } bool Save(CFileWriter* pcFile) { return pcFile-> WriteInt16 (mVal); } bool Load(CFileReader* pcFile) { return pcFile-> ReadInt16 (&mVal); } };
class Int32 : public CPrimitive<int32> { public:const char* ClassName(void){ return "Int32";}size ClassSize(void){ return sizeof(Int32);} public: Int32() : CPrimitive(PT_int32) {} Int32& operator= (int32 val) { Assign(val); return *this; } bool Save(CFileWriter* pcFile) { return pcFile-> WriteInt32 (mVal); } bool Load(CFileReader* pcFile) { return pcFile-> ReadInt32 (&mVal); } };
class UInt32 : public CPrimitive<uint32> { public:const char* ClassName(void){ return "UInt32";}size ClassSize(void){ return sizeof(UInt32);} public: UInt32() : CPrimitive(PT_uint32) {} UInt32& operator= (uint32 val) { Assign(val); return *this; } bool Save(CFileWriter* pcFile) { return pcFile-> WriteInt32 (mVal); } bool Load(CFileReader* pcFile) { return pcFile-> ReadInt32 (&mVal); } };
class Int64 : public CPrimitive<int64> { public:const char* ClassName(void){ return "Int64";}size ClassSize(void){ return sizeof(Int64);} public: Int64() : CPrimitive(PT_int64) {} Int64& operator= (int64 val) { Assign(val); return *this; } bool Save(CFileWriter* pcFile) { return pcFile-> WriteInt64 (mVal); } bool Load(CFileReader* pcFile) { return pcFile-> ReadInt64 (&mVal); } };
class UInt64 : public CPrimitive<uint64> { public:const char* ClassName(void){ return "UInt64";}size ClassSize(void){ return sizeof(UInt64);} public: UInt64() : CPrimitive(PT_uint64) {} UInt64& operator= (uint64 val) { Assign(val); return *this; } bool Save(CFileWriter* pcFile) { return pcFile-> WriteInt64 (mVal); } bool Load(CFileReader* pcFile) { return pcFile-> ReadInt64 (&mVal); } };
class Bool : public CPrimitive<bool> { public:const char* ClassName(void){ return "Bool";}size ClassSize(void){ return sizeof(Bool);} public: Bool() : CPrimitive(PT_bool) {} Bool& operator= (bool val) { Assign(val); return *this; } bool Save(CFileWriter* pcFile) { return pcFile-> WriteBool (mVal); } bool Load(CFileReader* pcFile) { return pcFile-> ReadBool (&mVal); } };
class SSize : public CPrimitive<size> { public:const char* ClassName(void){ return "SSize";}size ClassSize(void){ return sizeof(SSize);} public: SSize() : CPrimitive(PT_size) {} SSize& operator= (size val) { Assign(val); return *this; } bool Save(CFileWriter* pcFile) { return pcFile-> WriteSize (mVal); } bool Load(CFileReader* pcFile) { return pcFile-> ReadSize (&mVal); } };
class Float32 : public CPrimitive<float32> { public:const char* ClassName(void){ return "Float32";}size ClassSize(void){ return sizeof(Float32);} public: Float32() : CPrimitive(PT_float32) {} Float32& operator= (float32 val) { Assign(val); return *this; } bool Save(CFileWriter* pcFile) { return pcFile-> WriteFloat (mVal); } bool Load(CFileReader* pcFile) { return pcFile-> ReadFloat (&mVal); } };
class Float64 : public CPrimitive<float64> { public:const char* ClassName(void){ return "Float64";}size ClassSize(void){ return sizeof(Float64);} public: Float64() : CPrimitive(PT_float64) {} Float64& operator= (float64 val) { Assign(val); return *this; } bool Save(CFileWriter* pcFile) { return pcFile-> WriteFloat (mVal); } bool Load(CFileReader* pcFile) { return pcFile-> ReadFloat (&mVal); } };
class Char8 : public CPrimitive<char8> { public:const char* ClassName(void){ return "Char8";}size ClassSize(void){ return sizeof(Char8);} public: Char8() : CPrimitive(PT_char8) {} Char8& operator= (char8 val) { Assign(val); return *this; } bool Save(CFileWriter* pcFile) { return pcFile-> WriteChar (mVal); } bool Load(CFileReader* pcFile) { return pcFile-> ReadChar (&mVal); } };
class Char16 : public CPrimitive<char16> { public:const char* ClassName(void){ return "Char16";}size ClassSize(void){ return sizeof(Char16);} public: Char16() : CPrimitive(PT_char16) {} Char16& operator= (char16 val) { Assign(val); return *this; } bool Save(CFileWriter* pcFile) { return pcFile-> WriteWChar (mVal); } bool Load(CFileReader* pcFile) { return pcFile-> ReadWChar (&mVal); } };
class Void : public CPrimitiveObject
{
public:const char* ClassName(void){ return "Void";}size ClassSize(void){ return sizeof(Void);};
public:
Void() : CPrimitiveObject(PT_void)
{
}
bool Save(CFileWriter* pcFile)
{
return true;
}
bool Load(CFileReader* pcFile)
{
return true;
}
};
typedef CArrayTemplatePtr<void> CArrayVoidPtr;
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
enum EDateRounding
{
DR_Truncate,
DR_RoundDown,
};
class CDate
{
public:const char* ClassName(void){ return "CDate";}size ClassSize(void){ return sizeof(CDate);}
public:
int16 msYear;
int8 mcMonth;
int8 mcDay;
void Init(void);
void Init(int16 sYear, int8 cMonth, int8 cDay);
void Today(void);
void Tomorrow(void);
void Yesterday(void);
void AddDays(int iDays);
void SubtractDays(int iDays);
void ToStringCCYYMMDD(CChars* psz);
size DaysInYear(void);
size YearsBetween(CDate* pcOther, EDateRounding eRounding);
size MonthsBetween(CDate* pcOther, EDateRounding eRounding);
size GetYear(void);
size GetMonth(void);
size GetDayInMonth(void);
size GetDayInYear(void);
int CompareTo(CDate* pcRight);
bool Equals(CDate* pcRight);
bool After(CDate* pcRight);
bool Before(CDate* pcRight);
bool Save(CFileWriter* pcFileWriter);
bool Load(CFileReader* pcFileReader);
};
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
template<class M, class N>
class SVec2
{
public:
M x;
M y;
public:
SVec2() {};
SVec2<M, N>(const M*);
SVec2<M, N>(const SVec2<M, N>& v);
SVec2<M, N>(M x, M y);
SVec2<M, N>& operator = (const SVec2<M, N>& v);
SVec2<M, N>& operator += (const SVec2<M, N>&);
SVec2<M, N>& operator -= (const SVec2<M, N>&);
SVec2<M, N>& operator *= (M);
SVec2<M, N>& operator /= (M);
SVec2<M, N> operator + () const;
SVec2<M, N> operator - () const;
SVec2<M, N> operator + (const SVec2<M, N>&) const;
SVec2<M, N> operator - (const SVec2<M, N>&) const;
SVec2<M, N> operator * (M) const;
SVec2<M, N> operator / (M) const;
bool operator == (const SVec2<M, N>&) const;
bool operator != (const SVec2<M, N>&) const;
void Init(M x, M y);
void Init(const SVec2<M, N>& v);
void Init(SVec2* pv);
void Zero(void);
bool Save(CFileWriter* pcFileWriter);
bool Load(CFileReader* pcFileReader);
void Add(const SVec2<M, N>& v);
void Add(SVec2<M, N>* pv);
void Subtract(const SVec2<M, N>& v);
void Subtract(SVec2<M, N>* pv);
N SquareMagnitude(void);
M Magnitude(void);
void Maximise(const SVec2<M, N>& v);
void Maximise(SVec2<M, N>* pv);
void Maximise(M x, M y);
bool Contains(M x, M y);
};
template<class M, class N>
SVec2<M, N>::SVec2(const M* pf)
{
x = pf[0];
y = pf[1];
}
template<class M, class N>
SVec2<M, N>::SVec2(const SVec2<M, N>& v)
{
x = v.x;
y = v.y;
}
template<class M, class N>
SVec2<M, N>& SVec2<M, N>::operator = (const SVec2<M, N>& v)
{
x = v.x;
y = v.y;
return *this;
}
template<class M, class N>
SVec2<M, N>::SVec2(M fx, M fy)
{
x = fx;
y = fy;
}
template<class M, class N>
SVec2<M, N>& SVec2<M, N>::operator += (const SVec2<M, N>& v)
{
x += v.x;
y += v.y;
return *this;
}
template<class M, class N>
SVec2<M, N>& SVec2<M, N>::operator -= (const SVec2<M, N>& v)
{
x -= v.x;
y -= v.y;
return *this;
}
template<class M, class N>
SVec2<M, N>& SVec2<M, N>::operator *= (M f)
{
x *= f;
y *= f;
return *this;
}
template<class M, class N>
SVec2<M, N>& SVec2<M, N>::operator /= (M f)
{
M fInv = 1.0f / f;
x *= fInv;
y *= fInv;
return *this;
}
template<class M, class N>
SVec2<M, N> SVec2<M, N>::operator + () const
{
return *this;
}
template<class M, class N>
SVec2<M, N> SVec2<M, N>::operator - () const
{
return SVec2(-x, -y);
}
template<class M, class N>
SVec2<M, N> SVec2<M, N>::operator + (const SVec2<M, N>& v) const
{
return SVec2(x + v.x, y + v.y);
}
template<class M, class N>
SVec2<M, N> SVec2<M, N>::operator - (const SVec2<M, N>& v) const
{
return SVec2(x - v.x, y - v.y);
}
template<class M, class N>
SVec2<M, N> SVec2<M, N>::operator * (M f) const
{
return SVec2(x * f, y * f);
}
template<class M, class N>
SVec2<M, N> SVec2<M, N>::operator / (M f) const
{
M fInv = 1.0f / f;
return SVec2(x * fInv, y * fInv);
}
template<class M, class N>
SVec2<M, N> operator * (M f, const SVec2<M, N>& v)
{
return SVec2<M, N>(f * v.x, f * v.y);
}
template<class M, class N>
bool SVec2<M, N>::operator == (const SVec2<M, N>& v) const
{
return x == v.x && y == v.y;
}
template<class M, class N>
bool SVec2<M, N>::operator != (const SVec2<M, N>& v) const
{
return x != v.x || y != v.y;
}
template<class M, class N>
void SVec2<M, N>::Init(M x, M y)
{
this->x = x;
this->y = y;
}
template<class M, class N>
void SVec2<M, N>::Init(const SVec2<M, N>& v)
{
x = v.x;
y = v.y;
}
template<class M, class N>
void SVec2<M, N>::Init(SVec2* pv)
{
x = pv->x;
y = pv->y;
}
template<class M, class N>
void SVec2<M, N>::Zero(void)
{
x = 0;
y = 0;
}
template<class M, class N>
bool SVec2<M, N>::Save(CFileWriter* pcFileWriter)
{
bool bResult;
bResult = pcFileWriter->WritePrimitive<M>(x);
bResult &= pcFileWriter->WritePrimitive<M>(y);
return bResult;
}
template<class M, class N>
bool SVec2<M, N>::Load(CFileReader* pcFileReader)
{
bool bResult;
bResult = pcFileReader->ReadPrimitive<M>(&x);
bResult &= pcFileReader->ReadPrimitive<M>(&y);
return bResult;
}
template<class M, class N>
void SVec2<M, N>::Add(const SVec2<M, N>& v)
{
x += v.x;
y += v.y;
}
template<class M, class N>
void SVec2<M, N>::Add(SVec2<M, N>* pv)
{
x += pv->x;
y += pv->y;
}
template<class M, class N>
void SVec2<M, N>::Subtract(const SVec2<M, N>& v)
{
x -= v.x;
y -= v.y;
}
template<class M, class N>
void SVec2<M, N>::Subtract(SVec2<M, N>* pv)
{
x -= pv->x;
y -= pv->y;
}
template<class M, class N>
N SVec2<M, N>::SquareMagnitude(void)
{
return (N)x*(N)x + (N)y*(N)y;
}
template<class M, class N>
M SVec2<M, N>::Magnitude(void)
{
return (M)SquareRoot((N)SquareMagnitude());
}
template<class M, class N>
void SVec2<M, N>::Maximise(const SVec2<M, N>& v)
{
Maximise(v.x, v.y);
}
template<class M, class N>
void SVec2<M, N>::Maximise(SVec2<M, N>* pv)
{
Maximise(pv->x, pv->y);
}
template<class M, class N>
void SVec2<M, N>::Maximise(M x, M y)
{
if (x > this->x)
{
this->x = x;
}
if (y > this->y)
{
this->y = y;
}
}
template<class M, class N>
bool SVec2<M, N>::Contains(M x, M y)
{
if ((x >= 0) && (y >= 0) && (x < this->x) && (y < this->y))
{
return true;
}
return false;
}
class SFloat32Vec4;
class SFloat32Vec3;
class SFloat4x4;
class SFloat32Vec2 : public SVec2<float32, float64>
{
public:const char* ClassName(void){ return "SFloat32Vec2";}size ClassSize(void){ return sizeof(SFloat32Vec2);};
public:
using SVec2<float32, float64>::SVec2;
using SVec2<float32, float64>::operator=;
void Fix(void);
int WholeNumbers(void);
void Print(CChars* psx, int iWholeNumbers = -1, int iDecimals = 2);
void Normalize(void);
bool CloselyEqual(SFloat32Vec2* ps);
bool CloselyEqual(SFloat32Vec2* ps, float32 fTolerance);
};
typedef CArrayTemplate<SFloat32Vec2> CArrayFloat32Vec2;
float32 Float32Vec2Dot(const SFloat32Vec2* pV1, const SFloat32Vec2* pV2);
float32 Float32Vec2Cross(const SFloat32Vec2* pV1, const SFloat32Vec2* pV2);
SFloat32Vec2* Float32Vec2Add(SFloat32Vec2* pOut, const SFloat32Vec2* pV1, const SFloat32Vec2* pV2);
SFloat32Vec2* Float32Vec2Subtract(SFloat32Vec2* pOut, const SFloat32Vec2* pV1, const SFloat32Vec2* pV2);
SFloat32Vec2* Float32Vec2Minimize(SFloat32Vec2* pOut, const SFloat32Vec2* pV1, const SFloat32Vec2* pV2);
SFloat32Vec2* Float32Vec2Maximize(SFloat32Vec2* pOut, const SFloat32Vec2* pV1, const SFloat32Vec2* pV2);
SFloat32Vec2* Float32Vec2Scale(SFloat32Vec2* pOut, const SFloat32Vec2* pV, float32 s);
SFloat32Vec2* Float32Vec2Lerp(SFloat32Vec2* pOut, const SFloat32Vec2* pV1, const SFloat32Vec2* pV2, float32 s);
SFloat32Vec2* Float32Vec2TransformCoord(SFloat32Vec2* pOut, SFloat32Vec2* pV, SFloat4x4* psMat);
void Float32Vec2TransformCoords(SFloat32Vec2* asOut, int iOutStride, SFloat32Vec2* asIn, int iInStride, SFloat4x4* psMat, int iNumPoints);
SFloat32Vec2* Float32Vec2TransformNormal(SFloat32Vec2* pOut, SFloat32Vec2* pV, SFloat4x4* psMat);
void Float32Vec2TransformNormals(SFloat32Vec2* asOut, int iOutStride, SFloat32Vec2* asIn, int iInStride, SFloat4x4* psMat, int iNumPoints);
void Float32Vec2MinMax(SFloat32Vec2* psMin, SFloat32Vec2* psMax, SFloat32Vec2* asIn, int iInStride, int iNumPoints);
void Float32Vec2Swap(SFloat32Vec2* ps1, SFloat32Vec2* ps2);
void Float32Vec2InterpolatePosition(SFloat32Vec2* psVecDest, const SFloat32Vec2* psVec1, const SFloat32Vec2* psVec2, float32 fWeight);
void Float32Vec2InterpolateNormal(SFloat32Vec2* psVecDest, const SFloat32Vec2* psVec1, const SFloat32Vec2* psVec2, float32 fWeight);
void Float32Vec2RotateAboutNormalisedAxis(SFloat32Vec3* psVecDest, SFloat32Vec3 p, float32 fTheta, SFloat32Vec2 r);
void Float32Vec2Normalise(SFloat32Vec2* pOut, SFloat32Vec2* pV);
template<class M, class N>
class SVec3
{
public:
M x;
M y;
M z;
public:
SVec3() {};
SVec3<M, N>(const M*);
SVec3<M, N>(const SVec3<M, N>& v);
SVec3<M, N>(M x, M y, M z);
SVec3<M, N>& operator = (const SVec3<M, N>& v);
SVec3<M, N>& operator += (const SVec3<M, N>&);
SVec3<M, N>& operator -= (const SVec3<M, N>&);
SVec3<M, N>& operator *= (M);
SVec3<M, N>& operator /= (M);
SVec3<M, N> operator + () const;
SVec3<M, N> operator - () const;
SVec3<M, N> operator + (const SVec3<M, N>&) const;
SVec3<M, N> operator - (const SVec3<M, N>&) const;
SVec3<M, N> operator * (M) const;
SVec3<M, N> operator / (M) const;
bool operator == (const SVec3<M, N>&) const;
bool operator != (const SVec3<M, N>&) const;
void Init(M x, M y, M z);
void Init(const SVec3<M, N>& v);
void Init(SVec3* pv);
void Zero(void);
bool Save(CFileWriter* pcFileWriter);
bool Load(CFileReader* pcFileReader);
void Add(const SVec3<M, N>& v);
void Add(SVec3<M, N>* pv);
void Subtract(const SVec3<M, N>& v);
void Subtract(SVec3<M, N>* pv);
N SquareMagnitude(void);
M Magnitude(void);
};
template<class M, class N>
SVec3<M, N>::SVec3(const M* pf)
{
x = pf[0];
y = pf[1];
z = pf[2];
}
template<class M, class N>
SVec3<M, N>::SVec3(const SVec3<M, N>& v)
{
x = v.x;
y = v.y;
z = v.z;
}
template<class M, class N>
SVec3<M, N>& SVec3<M, N>::operator = (const SVec3<M, N>& v)
{
x = v.x;
y = v.y;
z = v.z;
return *this;
}
template<class M, class N>
SVec3<M, N>::SVec3(M x, M y, M z)
{
this->x = x;
this->y = y;
this->z = z;
}
template<class M, class N>
SVec3<M, N>& SVec3<M, N>::operator += (const SVec3<M, N>& v)
{
x += v.x;
y += v.y;
z += v.z;
return *this;
}
template<class M, class N>
SVec3<M, N>& SVec3<M, N>::operator -= (const SVec3<M, N>& v)
{
x -= v.x;
y -= v.y;
z -= v.z;
return *this;
}
template<class M, class N>
SVec3<M, N>& SVec3<M, N>::operator *= (M f)
{
x *= f;
y *= f;
z *= f;
return *this;
}
template<class M, class N>
SVec3<M, N>& SVec3<M, N>::operator /= (M f)
{
M fInv = 1.0f / f;
x *= fInv;
y *= fInv;
z *= fInv;
return *this;
}
template<class M, class N>
SVec3<M, N> SVec3<M, N>::operator + () const
{
return *this;
}
template<class M, class N>
SVec3<M, N> SVec3<M, N>::operator - () const
{
return SVec3(-x, -y, -z);
}
template<class M, class N>
SVec3<M, N> SVec3<M, N>::operator + (const SVec3<M, N>& v) const
{
return SVec3(x + v.x, y + v.y, z + v.z);
}
template<class M, class N>
SVec3<M, N> SVec3<M, N>::operator - (const SVec3<M, N>& v) const
{
return SVec3(x - v.x, y - v.y, z - v.z);
}
template<class M, class N>
SVec3<M, N> SVec3<M, N>::operator * (M f) const
{
return SVec3(x * f, y * f, z * f);
}
template<class M, class N>
SVec3<M, N> SVec3<M, N>::operator / (M f) const
{
M fInv = 1.0f / f;
return SVec3(x * fInv, y * fInv, z * fInv);
}
template<class M, class N>
SVec3<M, N> operator * (M f, const SVec3<M, N>& v)
{
return SVec3(f * v.x, f * v.y, f * v.z);
}
template<class M, class N>
bool SVec3<M, N>::operator == (const SVec3<M, N>& v) const
{
return x == v.x && y == v.y && z == v.z;
}
template<class M, class N>
bool SVec3<M, N>::operator != (const SVec3<M, N>& v) const
{
return x != v.x || y != v.y || z != v.z;
}
template<class M, class N>
void SVec3<M, N>::Init(M x, M y, M z)
{
this->x = x;
this->y = y;
this->z = z;
}
template<class M, class N>
void SVec3<M, N>::Init(const SVec3<M, N>& v)
{
x = v.x;
y = v.y;
z = v.z;
}
template<class M, class N>
void SVec3<M, N>::Init(SVec3<M, N>* pv)
{
x = pv->x;
y = pv->y;
z = pv->z;
}
template<class M, class N>
void SVec3<M, N>::Zero(void)
{
x = y = z = 0.0f;
}
template<class M, class N>
void SVec3<M, N>::Add(const SVec3<M, N>& v)
{
x += v.x;
y += v.y;
z += v.z;
}
template<class M, class N>
void SVec3<M, N>::Add(SVec3<M, N>* pv)
{
x += pv->x;
y += pv->y;
z += pv->z;
}
template<class M, class N>
void SVec3<M, N>::Subtract(const SVec3<M, N>& v)
{
x -= v.x;
y -= v.y;
z -= v.z;
}
template<class M, class N>
void SVec3<M, N>::Subtract(SVec3<M, N>* pv)
{
x -= pv->x;
y -= pv->y;
z -= pv->z;
}
template<class M, class N>
M SVec3<M, N>::Magnitude(void)
{
return (M)SquareRoot((N)SquareMagnitude());
}
template<class M, class N>
N SVec3<M, N>::SquareMagnitude(void)
{
return (N)x*(N)x + (N)y*(N)y + (N)z*(N)z;
}
template<class M, class N>
bool SVec3<M, N>::Save(CFileWriter* pcFileWriter)
{
bool bResult;
bResult = pcFileWriter->WritePrimitive<M>(x);
bResult &= pcFileWriter->WritePrimitive<M>(y);
bResult &= pcFileWriter->WritePrimitive<M>(z);
return bResult;
}
template<class M, class N>
bool SVec3<M, N>::Load(CFileReader* pcFileReader)
{
bool bResult;
bResult = pcFileReader->ReadPrimitive<M>(&x);
bResult &= pcFileReader->ReadPrimitive<M>(&y);
bResult &= pcFileReader->ReadPrimitive<M>(&z);
return bResult;
}
class SFloat32Vec4;
class SFloat32Vec2;
class SFloat4x4;
class SFloat32Vec3 : public SVec3<float32, float64>
{
public:const char* ClassName(void){ return "SFloat32Vec3";}size ClassSize(void){ return sizeof(SFloat32Vec3);};
public:
SFloat32Vec3() {};
SFloat32Vec3(float32 x, float32 y, float32 z);
using SVec3<float32, float64>::SVec3;
using SVec3<float32, float64>::operator =;
void Fix(void);
int WholeNumbers(void);
void Print(CChars* psx, int iWholeNumbers = -1, int iDecimals = 2);
void Copy(const SFloat32Vec4* ps);
void Copy(const SFloat32Vec3* ps);
void Copy(const SFloat32Vec2* ps);
void Normalize(void);
bool CloselyEqual(SFloat32Vec3* ps);
bool CloselyEqual(SFloat32Vec3* ps, float32 fTolerance);
};
typedef CArrayTemplate<SFloat32Vec3> CArrayFloat32Vec3;
float32 Float32Vec3Dot(const SFloat32Vec3* pV1, const SFloat32Vec3* pV2);
SFloat32Vec3* Float32Vec3Cross(SFloat32Vec3* pOut, const SFloat32Vec3* pV1, const SFloat32Vec3* pV2);
SFloat32Vec3* Float32Vec3Add(SFloat32Vec3* pOut, const SFloat32Vec3* pV1, const SFloat32Vec3* pV2);
SFloat32Vec3* Float32Vec3Subtract(SFloat32Vec3* pOut, const SFloat32Vec3* pV1, const SFloat32Vec3* pV2);
SFloat32Vec3* Float32Vec3Minimize(SFloat32Vec3* pOut, const SFloat32Vec3* pV1, const SFloat32Vec3* pV2);
SFloat32Vec3* Float32Vec3Maximize(SFloat32Vec3* pOut, const SFloat32Vec3* pV1, const SFloat32Vec3* pV2);
SFloat32Vec3* Float32Vec3Scale(SFloat32Vec3* pOut, const SFloat32Vec3* pV, float32 s);
SFloat32Vec3* Float32Vec3Lerp(SFloat32Vec3* pOut, const SFloat32Vec3* pV1, const SFloat32Vec3* pV2, float32 s);
SFloat32Vec3* Float32Vec3TransformCoord(SFloat32Vec3* pOut, SFloat32Vec3* pV, SFloat4x4* psMat);
void Float32Vec3TransformCoords(SFloat32Vec3* asOut, int iOutStride, SFloat32Vec3* asIn, int iInStride, SFloat4x4* psMat, int iNumPoints);
SFloat32Vec3* Float32Vec3TransformNormal(SFloat32Vec3* pOut, SFloat32Vec3* pV, SFloat4x4* psMat);
void Float32Vec3TransformNormals(SFloat32Vec3* asOut, int iOutStride, SFloat32Vec3* asIn, int iInStride, SFloat4x4* psMat, int iNumPoints);
void Float32Vec3MinMax(SFloat32Vec3* psMin, SFloat32Vec3* psMax, SFloat32Vec3* asIn, int iInStride, int iNumPoints);
void Float32Vec3Swap(SFloat32Vec3* ps1, SFloat32Vec3* ps2);
void Float32Vec3InterpolatePosition(SFloat32Vec3* psVecDest, const SFloat32Vec3* psVec1, const SFloat32Vec3* psVec2, float32 fWeight);
void Float32Vec3InterpolateNormal(SFloat32Vec3* psVecDest, const SFloat32Vec3* psVec1, const SFloat32Vec3* psVec2, float32 fWeight);
void Float32Vec3RotateAboutNormalisedAxis(SFloat32Vec3* psVecDest, SFloat32Vec3 p, float32 fTheta, SFloat32Vec3 r);
void Float32Vec3Normalise(SFloat32Vec3* pOut, SFloat32Vec3* pV);
template<class M, class N>
class SVec4
{
public:
M x;
M y;
M z;
M w;
public:
SVec4() {};
SVec4<M, N>(const M*);
SVec4<M, N>(const SVec4<M, N>& v);
SVec4<M, N>(const SVec3<M, N>& v, M w);
SVec4<M, N>(M x, M y, M z, M w);
SVec4<M, N>& operator = (const SVec4<M, N>& v);
SVec4<M, N>& operator += (const SVec4<M, N>&);
SVec4<M, N>& operator -= (const SVec4<M, N>&);
SVec4<M, N>& operator *= (M);
SVec4<M, N>& operator /= (M);
SVec4<M, N> operator + () const;
SVec4<M, N> operator - () const;
SVec4<M, N> operator + (const SVec4<M, N>&) const;
SVec4<M, N> operator - (const SVec4<M, N>&) const;
SVec4<M, N> operator * (M) const;
SVec4<M, N> operator / (M) const;
bool operator == (const SVec4<M, N>&) const;
bool operator != (const SVec4<M, N>&) const;
void Init(M x, M y, M z, M w);
void Init(const SVec4<M, N>& v);
void Init(SVec4* pv);
void Zero(void);
bool Save(CFileWriter* pcFileWriter);
bool Load(CFileReader* pcFileReader);
void Add(const SVec4<M, N>& v);
void Add(SVec4<M, N>* pv);
void Subtract(const SVec4<M, N>& v);
void Subtract(SVec4<M, N>* pv);
N SquareMagnitude(void);
M Magnitude(void);
};
template<class M, class N>
SVec4<M, N>::SVec4(const M *pf)
{
x = pf[0];
y = pf[1];
z = pf[2];
w = pf[3];
}
template<class M, class N>
SVec4<M, N>::SVec4(const SVec4<M, N>& v)
{
x = v.x;
y = v.y;
z = v.z;
w = v.w;
}
template<class M, class N>
SVec4<M, N>& SVec4<M, N>::operator = (const SVec4<M, N>& v)
{
x = v.x;
y = v.y;
z = v.z;
w = v.w;
return *this;
}
template<class M, class N>
SVec4<M, N>::SVec4(const SVec3<M, N>& v, M w)
{
x = v.x;
y = v.y;
z = v.z;
w = w;
}
template<class M, class N>
SVec4<M, N>::SVec4(M fx, M fy, M fz, M fw)
{
x = fx;
y = fy;
z = fz;
w = fw;
}
template<class M, class N>
SVec4<M, N>& SVec4<M, N>::operator += (const SVec4<M, N>& v)
{
x += v.x;
y += v.y;
z += v.z;
w += v.w;
return *this;
}
template<class M, class N>
SVec4<M, N>& SVec4<M, N>::operator -= (const SVec4<M, N>& v)
{
x -= v.x;
y -= v.y;
z -= v.z;
w -= v.w;
return *this;
}
template<class M, class N>
SVec4<M, N>& SVec4<M, N>::operator *= (M f)
{
x *= f;
y *= f;
z *= f;
w *= f;
return *this;
}
template<class M, class N>
SVec4<M, N>& SVec4<M, N>::operator /= (M f)
{
M fInv = 1.0f / f;
x *= fInv;
y *= fInv;
z *= fInv;
w *= fInv;
return *this;
}
template<class M, class N>
SVec4<M, N> SVec4<M, N>::operator + () const
{
return *this;
}
template<class M, class N>
SVec4<M, N> SVec4<M, N>::operator - () const
{
return SVec4(-x, -y, -z, -w);
}
template<class M, class N>
SVec4<M, N> SVec4<M, N>::operator + (const SVec4<M, N>& v) const
{
return SVec4(x + v.x, y + v.y, z + v.z, w + v.w);
}
template<class M, class N>
SVec4<M, N> SVec4<M, N>::operator - (const SVec4<M, N>& v) const
{
return SVec4(x - v.x, y - v.y, z - v.z, w - v.w);
}
template<class M, class N>
SVec4<M, N> SVec4<M, N>::operator * (M f) const
{
return SVec4(x * f, y * f, z * f, w * f);
}
template<class M, class N>
SVec4<M, N> SVec4<M, N>::operator / (M f) const
{
M fInv = 1.0f / f;
return SVec4(x * fInv, y * fInv, z * fInv, w * fInv);
}
template<class M, class N>
SVec4<M, N> operator * (M f, const SVec4<M, N>& v)
{
return SVec4(f * v.x, f * v.y, f * v.z, f * v.w);
}
template<class M, class N>
bool SVec4<M, N>::operator == (const SVec4<M, N>& v) const
{
return x == v.x && y == v.y && z == v.z && w == v.w;
}
template<class M, class N>
bool SVec4<M, N>::operator != (const SVec4<M, N>& v) const
{
return x != v.x || y != v.y || z != v.z || w != v.w;
}
template<class M, class N>
void SVec4<M, N>::Init(M x, M y, M z, M w)
{
this->x = x;
this->y = y;
this->z = z;
this->w = w;
}
template<class M, class N>
void SVec4<M, N>::Init(const SVec4<M, N>& v)
{
x = v.x;
y = v.y;
z = v.z;
w = v.w;
}
template<class M, class N>
void SVec4<M, N>::Init(SVec4* pv)
{
x = pv->x;
y = pv->y;
z = pv->z;
w = pv->w;
}
template<class M, class N>
void SVec4<M, N>::Zero(void)
{
x = 0.0f;
y = 0.0f;
z = 0.0f;
w = 0.0f;
}
template<class M, class N>
bool SVec4<M, N>::Save(CFileWriter* pcFileWriter)
{
bool bResult;
bResult = pcFileWriter->WritePrimitive<M>(x);
bResult &= pcFileWriter->WritePrimitive<M>(y);
bResult &= pcFileWriter->WritePrimitive<M>(z);
bResult &= pcFileWriter->WritePrimitive<M>(w);
return bResult;
}
template<class M, class N>
bool SVec4<M, N>::Load(CFileReader* pcFileReader)
{
bool bResult;
bResult = pcFileReader->ReadPrimitive<M>(&x);
bResult &= pcFileReader->ReadPrimitive<M>(&y);
bResult &= pcFileReader->ReadPrimitive<M>(&z);
bResult &= pcFileReader->ReadPrimitive<M>(&w);
return bResult;
}
template<class M, class N>
void SVec4<M, N>::Add(const SVec4<M, N>& v)
{
x += v.x;
y += v.y;
z += v.z;
w += v.w;
}
template<class M, class N>
void SVec4<M, N>::Add(SVec4<M, N>* pv)
{
x += pv->x;
y += pv->y;
z += pv->z;
w += pv->w;
}
template<class M, class N>
void SVec4<M, N>::Subtract(const SVec4<M, N>& v)
{
x -= v.x;
y -= v.y;
z -= v.z;
w -= v.w;
}
template<class M, class N>
void SVec4<M, N>::Subtract(SVec4<M, N>* pv)
{
x -= pv->x;
y -= pv->y;
z -= pv->z;
w -= pv->w;
}
template<class M, class N>
M SVec4<M, N>::Magnitude(void)
{
return (M)SquareRoot((N)SquareMagnitude());
}
template<class M, class N>
N SVec4<M, N>::SquareMagnitude(void)
{
return (N)x * (N)x + (N)y * (N)y + (N)z * (N)z + (N)w * (N)w;
}
class SFloat32Vec2;
class SFloat32Vec3;
class SFloat4x4;
class SFloat32Vec4 : public SVec4<float32, float64>
{
public:const char* ClassName(void){ return "SFloat32Vec4";}size ClassSize(void){ return sizeof(SFloat32Vec4);};
public:
SFloat32Vec4() {};
SFloat32Vec4(float32 x, float32 y, float32 z, float32 w);
using SVec4<float32, float64>::SVec4;
using SVec4<float32, float64>::operator=;
void Fix(void);
int WholeNumbers(void);
void Print(CChars* psz, int iWholeNumbers = -1, int iDecimals = 2);
void Copy(const SFloat32Vec4* ps);
void Copy(const SFloat32Vec3* ps);
void Copy(const SFloat32Vec2* ps);
void Normalize(void);
bool CloselyEqual(SFloat32Vec4* ps);
bool CloselyEqual(SFloat32Vec4* ps, float32 fTolerance);
};
typedef CArrayTemplate<SFloat32Vec4> CArrayFloat32Vec4;
float32 Float32Vec4Dot(const SFloat32Vec4* pV1, const SFloat32Vec4* pV2);
SFloat32Vec4* Float32Vec4Add(SFloat32Vec4* pOut, const SFloat32Vec4* pV1, const SFloat32Vec4* pV2);
SFloat32Vec4* Float32Vec4Subtract(SFloat32Vec4* pOut, const SFloat32Vec4* pV1, const SFloat32Vec4* pV2);
SFloat32Vec4* Float32Vec4Minimize(SFloat32Vec4* pOut, const SFloat32Vec4* pV1, const SFloat32Vec4* pV2);
SFloat32Vec4* Float32Vec4Maximize(SFloat32Vec4* pOut, const SFloat32Vec4* pV1, const SFloat32Vec4* pV2);
SFloat32Vec4* Float32Vec4Scale(SFloat32Vec4* pOut, const SFloat32Vec4* pV, float32 s);
SFloat32Vec4* Float32Vec4Lerp(SFloat32Vec4* pOut, const SFloat32Vec4* pV1, const SFloat32Vec4* pV2, float32 s);
SFloat32Vec4* Float32Vec4TransformCoord(SFloat32Vec4* psOut, SFloat32Vec4* psV, SFloat4x4* psMat);
void Float32Vec4TransformCoords(SFloat32Vec4* asOut, int iOutStride, SFloat32Vec4* asIn, int iInStride, SFloat4x4* psMat, int iNumPoints);
SFloat32Vec4* Float32Vec4TransformNormal(SFloat32Vec4* pOut, SFloat32Vec4* pV, SFloat4x4* psMat);
void Float32Vec4TransformNormals(SFloat32Vec4* asOut, int iOutStride, SFloat32Vec4* asIn, int iInStride, SFloat4x4* psMat, int iNumPoints);
void Float32Vec4MinMax(SFloat32Vec4* psMin, SFloat32Vec4* psMax, SFloat32Vec4* asIn, int iInStride, int iNumPoints);
void Float32Vec4Swap(SFloat32Vec4* ps1, SFloat32Vec4* ps2);
void Float32Vec4InterpolatePosition(SFloat32Vec4* psVecDest, const SFloat32Vec4* psVec1, const SFloat32Vec4* psVec2, float32 fWeight);
void Float32Vec4InterpolateNormal(SFloat32Vec4* psVecDest, const SFloat32Vec4* psVec1, const SFloat32Vec4* psVec2, float32 fWeight);
void Float32Vec4Normalise(SFloat32Vec4* pOut, SFloat32Vec4* pV);
class SFloat32Vec2;
class SFloat32Vec3;
class SFloat32Vec4;
class SFloat4x4
{
public:const char* ClassName(void){ return "SFloat4x4";}size ClassSize(void){ return sizeof(SFloat4x4);};
public:
SFloat32Vec4 x;
SFloat32Vec4 y;
SFloat32Vec4 z;
SFloat32Vec4 pos;
void Init(void);
void Init(SFloat32Vec3* psX, SFloat32Vec3* psY, SFloat32Vec3* psZ, SFloat32Vec3* psPos);
void Zero(void);
bool Save(CFileWriter* pcFileWriter);
bool Load(CFileReader* pcFileReader);
void Fix(void);
void Identity(void);
bool Inverse(SFloat4x4* psOut, float* pfDeterminant);
void Adjoint(SFloat4x4* psOut);
float Determinant(void);
SFloat32Vec3* At(void);
SFloat32Vec3* Up(void);
SFloat32Vec3* Across(void);
SFloat32Vec3* Pos(void);
void Print(CChars* psz, bool bOneLine, int iWholeNumbers = -1, int iDecimals = 2);
void Dump(void);
};
typedef CArrayTemplate<SFloat4x4> CArrayFloat4x4;
SFloat4x4* Float4x4Identity(SFloat4x4* psOut);
SFloat4x4* Float4x4Multiply(SFloat4x4* psOut, SFloat4x4* psLeft, SFloat4x4* psRight);
void Float4x4RotationX(SFloat4x4* psOut, float fRad);
void Float4x4RotationY(SFloat4x4* psOut, float fRad);
void Float4x4RotationZ(SFloat4x4* psOut, float fRad);
void Float4x4RotationVector(SFloat4x4* psOut, SFloat32Vec3* psV, float fRad);
void Float4x4Translation(SFloat4x4* psOut, float x, float y, float z);
bool Float4x4Inverse(SFloat4x4* psOut, float* pfDeterminant, SFloat4x4* psIn);
SFloat4x4* Float4x4LookAtRH(SFloat4x4* psOut, const SFloat32Vec3* psEye, const SFloat32Vec3* psAt, const SFloat32Vec3* psUp);
SFloat4x4* Float4x4PerspectiveFovRH(SFloat4x4* psOut, float fFovY, float fAspect, float fZNear, float fZFar);
bool Float4x4Equals(SFloat4x4* ps1, SFloat4x4* ps2);
class SInt32Vec2 : public SVec2<int32, int64>
{
public:const char* ClassName(void){ return "SInt32Vec2";}size ClassSize(void){ return sizeof(SInt32Vec2);};
public:
using SVec2<int32, int64>::SVec2;
using SVec2<int32, int64>::operator=;
void Print(CChars* psx, int iWholeNumbers = -1);
int WholeNumbers(void);
};
typedef CArrayTemplate<SInt32Vec2> CArrayInt32Vec2;
int32 Int32Vec2Dot(const SInt32Vec2* pV1, const SInt32Vec2* pV2);
int32 Int32Vec2Cross(const SInt32Vec2* pV1, const SInt32Vec2* pV2);
SInt32Vec2* Int32Vec2Add(SInt32Vec2* pOut, const SInt32Vec2* pV1, const SInt32Vec2* pV2);
SInt32Vec2* Int32Vec2Subtract(SInt32Vec2* pOut, const SInt32Vec2* pV1, const SInt32Vec2* pV2);
SInt32Vec2* Int32Vec2Minimize(SInt32Vec2* pOut, const SInt32Vec2* pV1, const SInt32Vec2* pV2);
SInt32Vec2* Int32Vec2Maximize(SInt32Vec2* pOut, const SInt32Vec2* pV1, const SInt32Vec2* pV2);
SInt32Vec2* Int32Vec2Scale(SInt32Vec2* pOut, const SInt32Vec2* pV, float32 s);
SInt32Vec2* Int32Vec2Lerp(SInt32Vec2* pOut, const SInt32Vec2* pV1, const SInt32Vec2* pV2, float32 s);
void Int32Vec2MinMax(SInt32Vec2* psMin, SInt32Vec2* psMax, SInt32Vec2* asIn, int iInStride, int iNumPoints);
void Int32Vec2Swap(SInt32Vec2* ps1, SInt32Vec2* ps2);
void Int32Vec2InterpolatePosition(SInt32Vec2* psVecDest, const SInt32Vec2* psVec1, const SInt32Vec2* psVec2, float32 fWeight);
class SInt32Vec3 : public SVec3<int32, int64>
{
public:const char* ClassName(void){ return "SInt32Vec3";}size ClassSize(void){ return sizeof(SInt32Vec3);};
public:
using SVec3<int32, int64>::SVec3;
using SVec3<int32, int64>::operator=;
void Print(CChars* psx, int iWholeNumbers = -1);
int WholeNumbers(void);
};
typedef CArrayTemplate<SInt32Vec3> CArrayInt32Vec3;
int32 Int32Vec3Dot(const SInt32Vec3* pV1, const SInt32Vec3* pV2);
SInt32Vec3* Int32Vec3Cross(SInt32Vec3* pOut, const SInt32Vec3* pV1, const SInt32Vec3* pV2);
SInt32Vec3* Int32Vec3Add(SInt32Vec3* pOut, const SInt32Vec3* pV1, const SInt32Vec3* pV2);
SInt32Vec3* Int32Vec3Subtract(SInt32Vec3* pOut, const SInt32Vec3* pV1, const SInt32Vec3* pV2);
SInt32Vec3* Int32Vec3Minimize(SInt32Vec3* pOut, const SInt32Vec3* pV1, const SInt32Vec3* pV2);
SInt32Vec3* Int32Vec3Maximize(SInt32Vec3* pOut, const SInt32Vec3* pV1, const SInt32Vec3* pV2);
SInt32Vec3* Int32Vec3Scale(SInt32Vec3* pOut, const SInt32Vec3* pV, float32 s);
SInt32Vec3* Int32Vec3Lerp(SInt32Vec3* pOut, const SInt32Vec3* pV1, const SInt32Vec3* pV2, float32 s);
void Int32Vec3MinMax(SInt32Vec3* psMin, SInt32Vec3* psMax, SInt32Vec3* asIn, int iInStride, int iNumPoints);
void Int32Vec3Swap(SInt32Vec3* ps1, SInt32Vec3* ps2);
void Int32Vec3InterpolatePosition(SInt32Vec3* psVecDest, const SInt32Vec3* psVec1, const SInt32Vec3* psVec3, float32 fWeight);
class SInt32Vec4 : public SVec4<int32, int64>
{
public:const char* ClassName(void){ return "SInt32Vec4";}size ClassSize(void){ return sizeof(SInt32Vec4);};
public:
SInt32Vec4() {};
SInt32Vec4(int32 x, int32 y, int32 z, int32 w);
using SVec4<int32, int64>::SVec4;
using SVec4<int32, int64>::operator=;
void Print(CChars* psz, int iWholeNumbers = -1);
int WholeNumbers(void);
};
typedef CArrayTemplate<SInt32Vec4> CArrayInt32Vec4;
int32 Int32Vec4Dot(const SInt32Vec4* pV1, const SInt32Vec4* pV2);
SInt32Vec4* Int32Vec4Add(SInt32Vec4* pOut, const SInt32Vec4* pV1, const SInt32Vec4* pV2);
SInt32Vec4* Int32Vec4Subtract(SInt32Vec4* pOut, const SInt32Vec4* pV1, const SInt32Vec4* pV2);
SInt32Vec4* Int32Vec4Minimize(SInt32Vec4* pOut, const SInt32Vec4* pV1, const SInt32Vec4* pV2);
SInt32Vec4* Int32Vec4Maximize(SInt32Vec4* pOut, const SInt32Vec4* pV1, const SInt32Vec4* pV2);
SInt32Vec4* Int32Vec4Scale(SInt32Vec4* pOut, const SInt32Vec4* pV, float32 s);
SInt32Vec4* Int32Vec4Lerp(SInt32Vec4* pOut, const SInt32Vec4* pV1, const SInt32Vec4* pV2, float32 s);
void Int32Vec4MinMax(SInt32Vec4* psMin, SInt32Vec4* psMax, SInt32Vec4* asIn, int iInStride, int iNumPoints);
void Int32Vec4Swap(SInt32Vec4* ps1, SInt32Vec4* ps2);
void Int32Vec4InterpolatePosition(SInt32Vec4* psVecDest, const SInt32Vec4* psVec1, const SInt32Vec4* psVec2, float32 fWeight);
class CDatasIO
{
protected:
CMapStringBlock mcDataIOs;
public:
void Init(void);
void Kill(void);
void Add(const char* szFilename, DataIO_FileWriter fSpecificClassFileSave, DataIO_FileReader fSpecificClassFileLoad);
template<class Class>
void Add(const char* szClassName);
template<class Class>
void Add(void);
DataIO_FileWriter GetFileWriter(const char* szClassName);
DataIO_FileReader GetFileReader(const char* szClassName);
template<class Class>
DataIO_FileWriter GetFileWriter(void);
template<class Class>
DataIO_FileReader GetFileReader(void);
SDataIO* GetIO(const char* szClassName);
size NumDataIOs(void);
};
template<class Class>
void CDatasIO::Add(const char* szConstructorName)
{
SDataIO* psIO;
bool(Class::* fSpecificClassFileSave)(CFileWriter*);
bool(Class::* fSpecificClassFileLoad)(CFileReader*);
fSpecificClassFileSave = &Class::Save;
fSpecificClassFileLoad = &Class::Load;
psIO = (SDataIO*)mcDataIOs.Put(szConstructorName, sizeof(SDataIO));
psIO->fWriter = (DataIO_FileWriter)fSpecificClassFileSave;
psIO->fReader = (DataIO_FileReader)fSpecificClassFileLoad;
}
template<class Class>
void CDatasIO::Add(void)
{
Class m;
SDataIO* psIO;
bool(Class::* fSpecificClassFileSave)(CFileWriter*);
bool(Class::* fSpecificClassFileLoad)(CFileReader*);
fSpecificClassFileSave = &Class::Save;
fSpecificClassFileLoad = &Class::Load;
psIO = (SDataIO*)mcDataIOs.Put(m.ClassName(), sizeof(SDataIO));
psIO->fWriter = (DataIO_FileWriter)fSpecificClassFileSave;
psIO->fReader = (DataIO_FileReader)fSpecificClassFileLoad;
}
template<class Class>
DataIO_FileWriter CDatasIO::GetFileWriter(void)
{
Class m;
return GetFileWriter((char*)m.ClassName());
}
template<class Class>
DataIO_FileReader CDatasIO::GetFileReader(void)
{
Class m;
return GetFileReader((char*)m.ClassName());
}
class CClass;
class CClasses;
class CField : public CUnknown
{
public:const char* ClassName(void){ return "CField";}size ClassSize(void){ return sizeof(CField);}
protected:
size muiOffset;
CClass* mpcFieldClass;
CClass* mpcContainingClass;
public:
void Init(CClass* pcFieldClass, size uiOffset, CClass* pcContainingClass, const char* szName);
void Kill(void);
CClasses* GetClasses(void);
char* GetName(void);
CClass* GetClass(void);
virtual size GetSizeOf(void) =0;
virtual bool IsArray(void);
size GetOffset(void);
virtual bool IsPointer(void);
virtual bool IsPrimitive(void);
virtual bool IsUnmanaged(void);
virtual bool IsEmbeddedObject(void);
virtual SDataIO* GetDataIO(void);
protected:
virtual size GetNameOffset(void) =0;
};
class CPointer;
class CBaseObject;
class CPointerField : public CField
{
public:const char* ClassName(void){ return "CPointerField";}size ClassSize(void){ return sizeof(CPointerField);}
protected:
bool mbDoNoFreePointedTo;
public:
void Init(ptrdiff_t iOffset, CClass* pcContainingClass, const char* szName);
void Kill(void);
bool IsPointer(void);
size GetSizeOf(void);
size GetNameOffset(void);
CPointer* GetPointer(CBaseObject* pcFieldContainer);
void DoNotFreePointedTo(bool bValue);
bool IsDoNotFreePointedTo(void);
};
class CBaseObject;
class CEmbeddedObjectField : public CField
{
public:const char* ClassName(void){ return "CEmbeddedObjectField";}size ClassSize(void){ return sizeof(CEmbeddedObjectField);}
public:
void Init(CClass* pcFieldClass, size uiOffset, CClass* pcContainingClass, const char* szName);
void Kill(void);
bool IsEmbeddedObject(void);
size GetSizeOf(void);
size GetNameOffset(void);
CBaseObject* GetEmbeddedObject(CBaseObject* pcFieldContainer);
};
class CPrimitiveObject;
class CBaseObject;
class CPrimitiveField : public CField
{
public:const char* ClassName(void){ return "CPrimitiveField";}size ClassSize(void){ return sizeof(CPrimitiveField);}
protected:
SDataIO* mpcIO;
size muiValueOffset;
public:
void Init(CClass* pcFieldClass, ptrdiff_t iOffset, ptrdiff_t iValueOffset, CClass* pcContainingClass, SDataIO* pcIO, const char* szName);
void Kill(void);
bool IsPrimitive(void);
size GetSizeOf(void);
size GetNameOffset(void);
SDataIO* GetDataIO(void);
CPrimitiveObject* GetPrimitiveObject(CBaseObject* pcFieldContainer);
void* GetValue(CBaseObject* pcFieldContainer);
};
class CBaseObject;
class CUnmanagedField : public CField
{
public:const char* ClassName(void){ return "CUnmanagedField";}size ClassSize(void){ return sizeof(CUnmanagedField);}
protected:
size muiLength;
size muiElementSize;
public:
void Init(EPrimitiveType eType, ptrdiff_t iOffset, CClass* pcContainingClass, const char* szName);
void Init(EPrimitiveType eType, ptrdiff_t iOffset, CClass* pcContainingClass, size uiLength, const char* szName);
void Init(EPrimitiveType eType, ptrdiff_t iOffset, CClass* pcContainingClass, size uiElementSize, size uiLength, const char* szName);
void Kill(void);
bool IsArray(void);
size GetLength(void);
bool IsUnmanaged(void);
void* GetData(CBaseObject* pcFieldContainer);
size GetSizeOf(void);
size GetNameOffset(void);
};
class CPointer;
class CBaseObject;
class CPrimitiveObject;
class CClasses;
class CClass : public CPostMalloc<CField>
{
protected:
CChars mszClassName;
size muiSize;
EPrimitiveType meType;
uint16 muiFlags;
CClasses* mpcClassesThisIn;
CLinkedListBlock macFields;
CArrayVoidPtr mapcPointers;
CArrayVoidPtr mapcEmbeddedObjects;
CArrayVoidPtr mapcPrimitives;
CArrayVoidPtr mapcUnmanaged;
public:
void Init(const char* szClassName, size uiSize, EPrimitiveType eType, CClasses* pcClasses);
void Kill(void);
void Complete(void);
CPointerField* Pointer(CBaseObject* pcThis, CPointer* pcPointer, const char* szFieldName);
CPrimitiveField* Primitive(CBaseObject* pcThis, CPrimitiveObject* pcPrimitive, void* pvPrimitive, const char* szFieldName);
CEmbeddedObjectField* Embedded(CBaseObject* pcThis, CBaseObject* pcObject, const char* szFieldName);
CClasses* GetClasses(void);
char* GetName(void);
EPrimitiveType GetType(void);
size GetSizeOf(void);
CField* GetField(const char* szFieldName);
void Unmanaged(void);
void System(void);
void Primitive(void);
void Nes(void);
bool IsComplete(void);
bool IsUnmanaged(void);
bool IsPrimitive(void);
bool IsSystem(void);
bool HasNes(void);
CArrayVoidPtr* GetPointerFields(void);
CArrayVoidPtr* GetEmbeddedObjectFields(void);
CArrayVoidPtr* GetPrimitiveFields(void);
CArrayVoidPtr* GetUnmanagedFields(void);
CClass* GetClass(EPrimitiveType eType);
CUnmanagedField* AddUnmanaged(const char* szFieldName);
CPrimitiveField* AddPrimitive(const char* szFieldName);
public:
CPrimitiveField* Primitive(CBaseObject* pcThis, SInt* pcPrimitive, const char* szFieldName);
CPrimitiveField* Primitive(CBaseObject* pcThis, SSize* pcPrimitive, const char* szFieldName);
CPrimitiveField* Primitive(CBaseObject* pcThis, Int8* pcPrimitive, const char* szFieldName);
CPrimitiveField* Primitive(CBaseObject* pcThis, UInt8* pcPrimitive, const char* szFieldName);
CPrimitiveField* Primitive(CBaseObject* pcThis, Int16* pcPrimitive, const char* szFieldName);
CPrimitiveField* Primitive(CBaseObject* pcThis, UInt16* pcPrimitive, const char* szFieldName);
CPrimitiveField* Primitive(CBaseObject* pcThis, Int32* pcPrimitive, const char* szFieldName);
CPrimitiveField* Primitive(CBaseObject* pcThis, UInt32* pcPrimitive, const char* szFieldName);
CPrimitiveField* Primitive(CBaseObject* pcThis, Int64* pcPrimitive, const char* szFieldName);
CPrimitiveField* Primitive(CBaseObject* pcThis, UInt64* pcPrimitive, const char* szFieldName);
CPrimitiveField* Primitive(CBaseObject* pcThis, Bool* pcPrimitive, const char* szFieldName);
CPrimitiveField* Primitive(CBaseObject* pcThis, Float32* pcPrimitive, const char* szFieldName);
CPrimitiveField* Primitive(CBaseObject* pcThis, Float64* pcPrimitive, const char* szFieldName);
CPrimitiveField* Primitive(CBaseObject* pcThis, Char8* pcPrimitive, const char* szFieldName);
CPrimitiveField* Primitive(CBaseObject* pcThis, Char16* pcPrimitive, const char* szFieldName);
void UnmanagedInt8(CBaseObject* pcThis, int8* pc, const char* szFieldName);
void UnmanagedInt8(CBaseObject* pcThis, int8* pac, size uiLength, const char* szFieldName);
void UnmanagedInt16(CBaseObject* pcThis, int16* pi, const char* szFieldName);
void UnmanagedInt16(CBaseObject* pcThis, int16* pai, size uiLength, const char* szFieldName);
void UnmanagedInt32(CBaseObject* pcThis, int32* pi, const char* szFieldName);
void UnmanagedInt32(CBaseObject* pcThis, int32* pai, size uiLength, const char* szFieldName);
void UnmanagedInt64(CBaseObject* pcThis, int64* pi, const char* szFieldName);
void UnmanagedInt64(CBaseObject* pcThis, int64* pai, size uiLength, const char* szFieldName);
void UnmanagedSInt(CBaseObject* pcThis, int* pi, const char* szFieldName);
void UnmanagedSInt(CBaseObject* pcThis, int* pai, size uiLength, const char* szFieldName);
void UnmanagedUInt8(CBaseObject* pcThis, uint8* pc, const char* szFieldName);
void UnmanagedUInt8(CBaseObject* pcThis, uint8* pac, size uiLength, const char* szFieldName);
void UnmanagedUInt16(CBaseObject* pcThis, uint16* pi, const char* szFieldName);
void UnmanagedUInt16(CBaseObject* pcThis, uint16* pai, size uiLength, const char* szFieldName);
void UnmanagedUInt32(CBaseObject* pcThis, uint32* pi, const char* szFieldName);
void UnmanagedUInt32(CBaseObject* pcThis, uint32* pai, size uiLength, const char* szFieldName);
void UnmanagedUInt64(CBaseObject* pcThis, uint64* pi, const char* szFieldName);
void UnmanagedUInt64(CBaseObject* pcThis, uint64* pai, size uiLength, const char* szFieldName);
void UnmanagedSUInt(CBaseObject* pcThis, uint* pi, const char* szFieldName);
void UnmanagedSUInt(CBaseObject* pcThis, uint* pai, size uiLength, const char* szFieldName);
void UnmanagedSize(CBaseObject* pcThis, size* pi, const char* szFieldName);
void UnmanagedSize(CBaseObject* pcThis, size* pai, size uiLength, const char* szFieldName);
void UnmanagedFloat(CBaseObject* pcThis, float32* pf, const char* szFieldName);
void UnmanagedFloat(CBaseObject* pcThis, float32* paf, size uiLength, const char* szFieldName);
void UnmanagedFloat(CBaseObject* pcThis, float64* pf, const char* szFieldName);
void UnmanagedFloat(CBaseObject* pcThis, float64* paf, size uiLength, const char* szFieldName);
void UnmanagedFloat(CBaseObject* pcThis, float128* pf, const char* szFieldName);
void UnmanagedFloat(CBaseObject* pcThis, float128* paf, size uiLength, const char* szFieldName);
void UnmanagedChar(CBaseObject* pcThis, char8* pc, const char* szFieldName);
void UnmanagedChar(CBaseObject* pcThis, char8* pac, size uiLength, const char* szFieldName);
void UnmanagedChar(CBaseObject* pcThis, char16* pc, const char* szFieldName);
void UnmanagedChar(CBaseObject* pcThis, char16* pac, size uiLength, const char* szFieldName);
void UnmanagedBool(CBaseObject* pcThis, bool* pb, const char* szFieldName);
void UnmanagedBool(CBaseObject* pcThis, bool* pab, size uiLength, const char* szFieldName);
void UnmanagedEnum(CBaseObject* pcThis, void* pe, const char* szFieldName);
void UnmanagedString(CBaseObject* pcThis, CChars* pcChars, const char* szFieldName);
void UnmanagedString(CBaseObject* pcThis, CCharsImmutable* pcChars, const char* szFieldName);
void UnmanagedNumber(CBaseObject* pcThis, CNumber* pcNumber, const char* szFieldName);
void UnmanagedDate(CBaseObject* pcThis, CDate* pcDate, const char* szFieldName);
void UnmanagedData(CBaseObject* pcThis, void* pv, size uiSizeof, const char* szFieldName);
void UnmanagedVoid(CBaseObject* pcThis, void* pv, const char* szFieldName);
void UnmanagedUnknown(CBaseObject* pcThis, void* pv, size uiSizeof, const char* szFieldName);
void UnmanagedPointer(CBaseObject* pcThis, void** pv, const char* szFieldName);
void Unmanaged2Float(CBaseObject* pcThis, SFloat32Vec2* pf, const char* szFieldName);
void Unmanaged2Float(CBaseObject* pcThis, SFloat32Vec2* pf, size uiLength, const char* szFieldName);
void Unmanaged3Float(CBaseObject* pcThis, SFloat32Vec3* pf, const char* szFieldName);
void Unmanaged3Float(CBaseObject* pcThis, SFloat32Vec3* pf, size uiLength, const char* szFieldName);
void Unmanaged4Float(CBaseObject* pcThis, SFloat32Vec4* pf, const char* szFieldName);
void Unmanaged4Float(CBaseObject* pcThis, SFloat32Vec4* pf, size uiLength, const char* szFieldName);
void Unmanaged4x4Float(CBaseObject* pcThis, SFloat4x4* pf, const char* szFieldName);
void Unmanaged4x4Float(CBaseObject* pcThis, SFloat4x4* pf, size uiLength, const char* szFieldName);
void Unmanaged2Int(CBaseObject* pcThis, SInt32Vec2* pf, const char* szFieldName);
void Unmanaged2Int(CBaseObject* pcThis, SInt32Vec2* pf, size uiLength, const char* szFieldName);
void Unmanaged3Int(CBaseObject* pcThis, SInt32Vec3* pf, const char* szFieldName);
void Unmanaged3Int(CBaseObject* pcThis, SInt32Vec3* pf, size uiLength, const char* szFieldName);
void Unmanaged4Int(CBaseObject* pcThis, SInt32Vec4* pf, const char* szFieldName);
void Unmanaged4Int(CBaseObject* pcThis, SInt32Vec4* pf, size uiLength, const char* szFieldName);
protected:
CField* AddField(size uiFieldSize, const char* szName);
void Unmanaged(CBaseObject* pcThis, EPrimitiveType eType, void* pv, const char* szFieldName);
void Unmanaged(CBaseObject* pcThis, EPrimitiveType eType, void* pv, size uiLength, const char* szFieldName);
size ComputeSize(void);
};
class CObjectReader;
class CObjectWriter;
class CObjects;
class CObjectRemapFrom;
class CBaseObject : public CEmbeddedObject
{
template<class M>
friend class Ptr;
friend class CPointer;
friend class CArrayCommonObject;
friend class CIndexObject;
friend class CMapObject;
friend class CObject;
friend class CObjects;
friend class CObjectRemapFrom;
friend class CEmbeddedObject;
friend class CObjectWriter;
friend class CObjectReader;
friend class CNamedIndexedObjects;
public:const char* ClassName(void){ return "CBaseObject";}size ClassSize(void){ return sizeof(CBaseObject);}
protected:
OIndex moi;
CCharsImmutable mon;
CObjects* mpcObjectsThisIn;
CClass* mpcClass;
int miDistToRoot;
int miDistToStack;
uint16 muiFlags;
uint16 muiNumEmbedded;
uint16 muiPreInits;
uint16 muiPostInits;
public:
CBaseObject();
CBaseObject(const CBaseObject&) = delete;
~CBaseObject();
protected:
virtual void Class(void) =0;
public:
bool InitIdentifiers(const char* szName, OIndex oi);
void Kill(void) override;
virtual void Free(void) =0;
virtual bool Flush(void);
bool Save(CObjectWriter* pcFile) override;
bool Load(CObjectReader* pcFile) override;
OIndex GetIndex(void) override;
void FreeIdentifiers(void) override;
bool IsRoot(void);
virtual bool IsSubRoot(void);
bool IsHollow(void);
virtual bool IsCollection(void) =0;
virtual bool IsObject(void) =0;
bool IsNamed(void) override;
bool IsInvalidated(void);
bool IsDirty(void);
bool IsUpdateAttachedPointerTosDistToRoot(void);
bool IsInitialised(void);
bool HasClass(void);
CClass* GetClass(void);
bool IsKilled(void);
bool IsNamed(const char* szName);
char* GetName(void) override;
size SerialisedSize(void);
virtual char* PrintIdentifier(CChars* psz);
void PrintState(CChars* psz);
void PrintFlagsShorthand(CChars* psz);
void PrintFlags(CChars* psz);
void Print(CChars* psz) override;
size NumEmbedded(void);
virtual void SetPointerTosExpectedDistToRoot(int iDistToRoot) =0;
void SetDirty(bool bDirty);
int GetDistToRoot(void);
int GetDistToStack(void);
virtual bool SetDistToRoot(int iDistToRoot) override;
bool TestedForRoot(void);
void UpdateAttachedTosDistToRoot(CDistCalculatorParameters* pcParameters);
void CollectValidDistStartingObjectsAndSetClearedToRoot(CBaseObject* pcTo, CDistCalculatorParameters* pcParameters);
void CollectAndClearInvalidDistToRootObjects(CDistCalculatorParameters* pcParameters);
virtual bool IsDistToRootValid(void);
size CollectDetachedAndSetDistToStackZero(CDistCalculatorParameters* pcParameters);
size CollectDetachedFroms(CDistCalculatorParameters* pcParameters);
void AddExpectedDistToRoot(CEmbeddedObject* pcPointedTo, int iExpectedDist, CDistCalculatorParameters* pcParameters);
void ClearDistTouchedFlags(void);
bool HasDistTouchedFlag(void);
bool TestedForSanity(void);
CObjects* GetObjectsThisIn(void);
CClasses* GetClasses(void);
virtual bool SetDistToStack(int iDistToStack);
virtual void InitDistToStack(void);
CClass* CompleteClass(CClasses* pcClasses);
void CopyFields(CEmbeddedObject* pcOther) override;
virtual bool ContainsPointerTo(CEmbeddedObject* pcEmbedded);
CEmbeddedObject* TestGetPointerTo(size iToIndex);
size TestGetNumEmbeddedFromFlags(void);
void ClearFlagNumEmbedded(void);
virtual void SetFlag(uint16 iFlag, uint16 iFlagValue);
uint16 GetFlags(void);
bool CanFindRoot(void);
bool CanFindRootThroughValidPath(void);
void StopDestructor(void);
bool HasNes(void) override;
void GetNesPointerToThis(CArrayEmbeddedObjectPtrE8* papNesObjectsPointingToThis);
bool IsNesPointedTo(void);
bool HasNesPointerToThis(CEmbeddedObject* pcBaseObject) override;
void DumpFroms(void);
void DumpPointerTos(void);
virtual void Dump(void);
void DumpFlags(void);
void ValidateFlagSet(uint16 iFlag, const char* szFlag);
void ValidateFlagNotSet(uint16 iFlag, const char* szFlag);
void ValidateContainerFlag(void);
void ValidateFlags(void);
void ValidateDistToRoot(void);
void ValidateIndex(void);
void ValidateObjectsThisIn(void);
void ValidateCanFindRoot(void);
virtual void ValidateEmbeddedConsistency(void);
virtual void ValidateObjectIdentifiers(void);
void ValidateBaseObjectDetail(void);
void ValidateAllocation(void);
bool FailHasClassFlag(char* szMethod);
bool FailHasClassField(char* szMethod);
void ValidateInitCalled(void);
void ValidateKillCalled(void);
virtual void ValidateInternalConsistency(void);
protected:
void Allocate(CObjects* pcObjects) override;
void PreClass(void);
void SetClass(CClass* pcClass);
void PreInit(void);
void PostInit(void);
virtual void Initialised(void);
virtual void PreFields(void);
virtual void EmbedFields(void) =0;
void FreeInternal(void) override;
void DoneKill(bool bAllocatedInObjects) override;
void KillInternal(bool bHeapFromChanged, bool bValidateNotEmbedded) override;
EFreeResult TryFree(bool bHeapFromChanged);
void RemoveInKillOrder(CArrayBaseObjectPtr* papcKilled);
virtual void RemoveAllPointerTosDontFree(void) =0;
virtual bool RemoveAllPointerTosTryFree(void) =0;
bool SaveManaged(CObjectWriter* pcFile);
bool LoadManaged(CObjectReader* pcFile);
bool SaveHeapFroms(CObjectWriter* pcFile);
bool LoadHeapFroms(CObjectReader* pcFile);
size RemapPointerTos(CEmbeddedObject* pcOld, CEmbeddedObject* pcNew) =0;
void RemoveToFromDontFree(CEmbeddedObject* pcPointedTo);
void SetExpectedDistToRoot(int iExpectedDistToRoot);
void SetCalculatedDistToRoot(void);
int CalculateDistToRootFromPointedFroms(void);
virtual int CalculateDistToRootFromPointedFroms(int iDistToRoot);
bool IsBaseObject(void);
uint16 GetNumEmbeddedFromFlags(void);
void SetFlagNumEmbedded(size iNumEmbedded);
bool IsMarkedUnreachable(void);
void ReplaceOneWithX(char* szDest, char* szMask);
void ContainerPreInit(void);
void ContainerPostInit(void);
bool SaveEmbeddedObjectsManaged(CObjectWriter* pcFile);
bool SavePointers(CObjectWriter* pcFile);
bool SavePrimitives(CObjectWriter* pcFile);
bool SaveUnmanaged(CObjectWriter* pcFile);
bool SaveEmbeddedObjectsHeapFroms(CObjectWriter* pcFile);
bool LoadEmbeddedObjectsManaged(CObjectReader* pcFile);
bool LoadPointers(CObjectReader* pcFile);
bool LoadPrimitives(CObjectReader* pcFile);
bool LoadUnmanaged(CObjectReader* pcFile);
bool LoadEmbeddedObjectsHeapFroms(CObjectReader* pcFile);
virtual void BaseValidatePointerTos(void) =0;
void Nes(CPointerField* pcField);
CPointerField* Pointer(CPointer* pcPointer, const char* szFieldName);
CEmbeddedObjectField* Embedded(CBaseObject* pcObject, const char* szFieldName);
CPrimitiveField* Primitive(SInt* pcPrimitive, const char* szFieldName);
CPrimitiveField* Primitive(SSize* pcPrimitive, const char* szFieldName);
CPrimitiveField* Primitive(Int8* pcPrimitive, const char* szFieldName);
CPrimitiveField* Primitive(UInt8* pcPrimitive, const char* szFieldName);
CPrimitiveField* Primitive(Int16* pcPrimitive, const char* szFieldName);
CPrimitiveField* Primitive(UInt16* pcPrimitive, const char* szFieldName);
CPrimitiveField* Primitive(Int32* pcPrimitive, const char* szFieldName);
CPrimitiveField* Primitive(UInt32* pcPrimitive, const char* szFieldName);
CPrimitiveField* Primitive(Int64* pcPrimitive, const char* szFieldName);
CPrimitiveField* Primitive(UInt64* pcPrimitive, const char* szFieldName);
CPrimitiveField* Primitive(Bool* pcPrimitive, const char* szFieldName);
CPrimitiveField* Primitive(Float32* pcPrimitive, const char* szFieldName);
CPrimitiveField* Primitive(Float64* pcPrimitive, const char* szFieldName);
CPrimitiveField* Primitive(Char8* pcPrimitive, const char* szFieldName);
CPrimitiveField* Primitive(Char16* pcPrimitive, const char* szFieldName);
void UnmanagedInt8(int8* pc, const char* szFieldName);
void UnmanagedInt8(int8* pac, size uiLength, const char* szFieldName);
void UnmanagedInt16(int16* pi, const char* szFieldName);
void UnmanagedInt16(int16* pai, size uiLength, const char* szFieldName);
void UnmanagedInt32(int32* pi, const char* szFieldName);
void UnmanagedInt32(int32* pai, size uiLength, const char* szFieldName);
void UnmanagedInt64(int64* pi, const char* szFieldName);
void UnmanagedInt64(int64* pai, size uiLength, const char* szFieldName);
void UnmanagedSInt(int* pi, const char* szFieldName);
void UnmanagedSInt(int* pai, size uiLength, const char* szFieldName);
void UnmanagedUInt8(uint8* pc, const char* szFieldName);
void UnmanagedUInt8(uint8* pac, size uiLength, const char* szFieldName);
void UnmanagedUInt16(uint16* pi, const char* szFieldName);
void UnmanagedUInt16(uint16* pai, size uiLength, const char* szFieldName);
void UnmanagedUInt32(uint32* pi, const char* szFieldName);
void UnmanagedUInt32(uint32* pai, size uiLength, const char* szFieldName);
void UnmanagedUInt64(uint64* pi, const char* szFieldName);
void UnmanagedUInt64(uint64* pai, size uiLength, const char* szFieldName);
void UnmanagedSUInt(uint* pi, const char* szFieldName);
void UnmanagedSUInt(uint* pai, size uiLength, const char* szFieldName);
void UnmanagedSize(size* pi, const char* szFieldName);
void UnmanagedSize(size* pai, size uiLength, const char* szFieldName);
void UnmanagedFloat(float32* pf, const char* szFieldName);
void UnmanagedFloat(float32* paf, size uiLength, const char* szFieldName);
void UnmanagedFloat(float64* pf, const char* szFieldName);
void UnmanagedFloat(float64* paf, size uiLength, const char* szFieldName);
void UnmanagedFloat(float128* pf, const char* szFieldName);
void UnmanagedFloat(float128* paf, size uiLength, const char* szFieldName);
void UnmanagedChar(char8* pc, const char* szFieldName);
void UnmanagedChar(char8* pac, size uiLength, const char* szFieldName);
void UnmanagedChar(char16* pc, const char* szFieldName);
void UnmanagedChar(char16* pac, size uiLength, const char* szFieldName);
void UnmanagedBool(bool* pb, const char* szFieldName);
void UnmanagedBool(bool* pab, size uiLength, const char* szFieldName);
void UnmanagedEnum(void* pe, const char* szFieldName);
void UnmanagedString(CChars* pcChars, const char* szFieldName);
void UnmanagedString(CCharsImmutable* pcChars, const char* szFieldName);
void UnmanagedNumber(CNumber* pcNumber, const char* szFieldName);
void UnmanagedDate(CDate* pcDate, const char* szFieldName);
void UnmanagedData(void* pv, size uiSizeof, const char* szFieldName);
void UnmanagedUnknown(void* pv, size uiSizeof, const char* szFieldName);
void UnmanagedPointer(void** pv, const char* szFieldName);
void Unmanaged2Float(SFloat32Vec2* pf, const char* szFieldName);
void Unmanaged2Float(SFloat32Vec2* pf, size uiLength, const char* szFieldName);
void Unmanaged3Float(SFloat32Vec3* pf, const char* szFieldName);
void Unmanaged3Float(SFloat32Vec3* pf, size uiLength, const char* szFieldName);
void Unmanaged4Float(SFloat32Vec4* pf, const char* szFieldName);
void Unmanaged4Float(SFloat32Vec4* pf, size uiLength, const char* szFieldName);
void Unmanaged4x4Float(SFloat4x4* pf, const char* szFieldName);
void Unmanaged4x4Float(SFloat4x4* pf, size uiLength, const char* szFieldName);
void Unmanaged2Int(SInt32Vec2* pf, const char* szFieldName);
void Unmanaged2Int(SInt32Vec2* pf, size uiLength, const char* szFieldName);
void Unmanaged3Int(SInt32Vec3* pf, const char* szFieldName);
void Unmanaged3Int(SInt32Vec3* pf, size uiLength, const char* szFieldName);
void Unmanaged4Int(SInt32Vec4* pf, const char* szFieldName);
void Unmanaged4Int(SInt32Vec4* pf, size uiLength, const char* szFieldName);
private:
bool ClipName(void);
};
class CObject : public CBaseObject
{
template<class M>
friend class Ptr;
friend class CPointer;
friend class CObjects;
friend class CExternalObjectDeserialiser;
public:const char* ClassName(void){ return "CObject";}size ClassSize(void){ return sizeof(CObject);}
protected:
CArrayTemplateEmbeddedPtr<CPointer, 5> mapPointers;
CArrayTemplateEmbeddedPtr<CBaseObject, 3> mapEmbedded;
public:
CObject();
~CObject();
void Allocate(CObjects* pcObjects);
void Kill(void) final override;
bool IsCollection(void) override;
bool IsObject(void) override;
void GetPointerFieldsTo(CEmbeddedObject* pcTo, CArrayHeapFromPointer* pacPointers) override;
void SetPointerTosExpectedDistToRoot(int iDistToRoot);
bool IsDirty(void);
size GetEmbeddedIndex(CEmbeddedObject* pcEmbedded);
size NumEmbedded(void);
size CountNumEmbedded(void);
CEmbeddedObject* GetEmbeddedObject(size iIndex);
CBaseObject* Dehollow(void);
size NumHeapFroms(void);
size NumStackFroms(void);
void SetFlag(uint16 iFlag, uint16 iFlagValue);
void GetHeapFroms(CArrayBaseObjectPtrE32* papcFroms);
void GetStackFroms(CArrayStackPointerE32* papcFroms);
CBaseObject* GetClosestFromToRoot(void);
CBaseObject* GetClosestHeapFromToStack(void);
size NumPointerTos(void);
size BaseNumPointerTos(void);
void GetPointerTos(CArrayEmbeddedObjectPtr* papcTos);
void BaseGetPointerTos(CArrayEmbeddedObjectPtr* papcTos);
bool ContainsPointerTo(CEmbeddedObject* pcEmbedded);
void CollectAndClearPointerTosInvalidDistToRootObjects(CDistCalculatorParameters* pcParameters);
void BaseCollectAndClearPointerTosInvalidDistToRootObjects(CDistCalculatorParameters* pcParameters);
size CollectDetachedFroms(CDistCalculatorParameters* pcParameters);
size GetFieldPointerToIndex(CPointer* pcFieldPointer);
size GetNumFieldPointerTos(void);
CPointer* GetFieldPointerTo(size iIndex);
void CopyFields(CEmbeddedObject* pcOther) override;
void ValidatePointerTos(void);
void ValidateConsistency(void);
protected:
void EmbedFields(void) override;
void FreeInternal(void) override;
void DoneKill(bool bAllocatedInObjects) override;
void FreePointers(void) override;
void RemovePointerTo(CEmbeddedObject* pcTo);
void RemoveAllPointerTosDontFree(void);
bool RemoveAllPointerTosTryFree(void);
void RemoveAllHeapFroms(void) override;
void RemoveAllStackFroms(void) override;
CBaseObject* GetClosestFromForCanFindRoot(void);
size RemapPointerTos(CEmbeddedObject* pcOld, CEmbeddedObject* pcNew) override;
void UpdateAttachedEmbeddedObjectPointerTosDistToRoot(CDistCalculatorParameters* pcParameters, int iExpectedDist);
void BaseUpdateAttachedEmbeddedObjectPointerTosDistToRoot(CDistCalculatorParameters* pcParameters, int iExpectedDist);
int CalculateDistToRootFromPointedFroms(int iDistToRoot);
void SetPointedTosDistToRoot(int iDistToRoot);
bool SetDistToRoot(int iDistToRoot) override;
bool SetDistToStack(int iDistToStack) override;
void InitDistToStack(void);
bool RecurseGetEmbeddedIndex(CEmbeddedObject* pcTest, size* piIndex);
CEmbeddedObject* RecurseGetEmbeddedObject(size iIndex, size* iCount);
bool RecurseGetFieldPointerToIndex(CPointer* pcTest, size* piIndex);
CPointer* RecurseGetFieldPointerTo(size iIndex, size* piCount);
void BaseValidatePointerTos(void);
void ValidateEmbeddedConsistency(void);
bool IsDistToRootValid(void);
void EmbedPointerFields(void);
void EmbedEmbeddedObjectFields(void);
void ClassNotImplemented(void);
};
struct SSerialisedName
{
int32 miLength;
char msz[4];
};__pragma(pack(push,1))
class CSerialisedObject
{
protected:
uint32 miLength;
char mszMagic[4];
char mszType[4];
uint32 miIgnored;
OIndex moi;
uint16 muiSize;
SSerialisedName msName;
public:
bool IsNamed(void);
bool IsIndexed(void);
bool IsVoid(void);
char* GetName(void);
OIndex GetIndex(void);
size GetLength(void);
void SetLength(size iLength);
};__pragma(pack(pop))
class CExternalObjectReader : public CUnknown
{
public:const char* ClassName(void){ return "CExternalObjectReader";}size ClassSize(void){ return sizeof(CExternalObjectReader);}
public:
void Kill(void);
virtual bool Begin(void);
virtual CSerialisedObject* Read(const char* szObjectName) =0;
virtual CSerialisedObject* Read(OIndex oi) =0;
virtual bool End(void);
protected:
CSerialisedObject* ReadSerialised(CFileReader* pcReader);
};
class CSerialisedObject;
class CObjectConverter;
class CObjectSource : public CUnknown
{
public:const char* ClassName(void){ return "CObjectSource";}size ClassSize(void){ return sizeof(CObjectSource);}
protected:
CObjectConverter* mpcConverter;
CAbstractFile* mpcFile;
public:
void Init(CObjectConverter* pcConverter, CAbstractFile* pcFile, const char* szFilename);
void Kill(void);
virtual CBaseObject* Convert(const char* szFullName) =0;
virtual bool Contains(const char* szFullName) =0;
virtual bool IsNative(void);
virtual bool IsMultiSource(void);
CAbstractFile* GetFile(void);
virtual CExternalObjectReader* GetReader(void);
};
class CObjectSingleSource : public CObjectSource
{
public:const char* ClassName(void){ return "CObjectSingleSource";}size ClassSize(void){ return sizeof(CObjectSingleSource);}
protected:
CChars mszObjectName;
public:
void Init(CObjectConverter* pcConverter, CAbstractFile* pcFile, const char* szObjectName);
void Kill(void);
CBaseObject* Convert(const char* szFullName);
bool Contains(const char* szFullName);
};
class CObjectSourceText : public CObjectSingleSource
{
public:const char* ClassName(void){ return "CObjectSource";}size ClassSize(void){ return sizeof(CObjectSource);}
public:
void Init(CObjectConverter* pcConverter, CAbstractFile* pcFile, const char* szFilename);
void Kill(void);
};
class CHollowObject : public CBaseObject
{
public:const char* ClassName(void){ return "CHollowObject";}size ClassSize(void){ return sizeof(CHollowObject);}
protected:
uint16 muiSize;
public:
CHollowObject();
~CHollowObject();
void Init(size iNumEmbedded);
void Init(size iNumEmbedded, uint16 uiFatSize);
void Kill(void) final;
bool IsHollow(void) override;
bool IsFatHollow(void);
uint16 GetFatSize(void);
bool Save(CObjectWriter* pcFile) override;
bool Load(CObjectReader* pcFile) override;
bool IsCollection(void) override;
bool IsObject(void) override;
void SetPointerTosExpectedDistToRoot(int iDistToRoot);
void GetPointerTos(CArrayEmbeddedObjectPtr* papcTos);
size NumPointerTos(void);
CEmbeddedObject* GetEmbeddedObject(size iIndex);
size GetEmbeddedIndex(CEmbeddedObject* pcEmbedded);
size NumEmbedded(void);
size NumHeapFroms(void);
size NumStackFroms(void);
void RemoveAllPointerTosDontFree(void);
bool RemoveAllPointerTosTryFree(void);
void BaseValidatePointerTos(void);
void ValidateConsistency(void);
bool HasNes(void) override;
bool HasNesPointerToThis(CEmbeddedObject* pcBaseObject) override;
protected:
void EmbedFields(void);
void Class(void) override;
CBaseObject* Dehollow(void);
void FreePointers(void) override;
void Free(void) override;
size RemapPointerTos(CEmbeddedObject* pcOld, CEmbeddedObject* pcNew);
void RemovePointerTo(CEmbeddedObject* pcTo);
virtual CEmbeddedObject* GetRemappedEmbeddedObject(size iIndex);
void UpdateAttachedEmbeddedObjectPointerTosDistToRoot(CDistCalculatorParameters* pcParameters, int iExpectedDist);
};
class CObjectConverter : public CUnknown
{
public:const char* ClassName(void){ return "CObjectConverter";}size ClassSize(void){ return sizeof(CObjectConverter);}
public:
void Kill(void);
virtual const char* GetFileExtension(void) =0;
virtual bool IsFor(CAbstractFile* pcFile) =0;
virtual CObjectSource* CreateSource(CAbstractFile* pcFile, const char* szFilename) =0;
virtual CBaseObject* Convert(CObjectSource* pcSource, const char* szObjectName) =0;
};
class CObjectSource;
class CObjectConverterText : public CObjectConverter
{
public:const char* ClassName(void){ return "CObjectConverterText";}size ClassSize(void){ return sizeof(CObjectConverterText);}
public:
void Init(void);
void Kill(void);
const char* GetFileExtension(void);
bool IsFor(CAbstractFile* pcFile);
CObjectSource* CreateSource(CAbstractFile* pcFile, const char* szFilename);
CBaseObject* Convert(CObjectSource* pcSource, const char* szObjectName);
};
void CObjectSourceText::Init(CObjectConverter* pcConverter, CAbstractFile* pcFile, const char* szFilename)
{
CObjectSingleSource::Init(pcConverter, pcFile, szFilename);
}
void CObjectSourceText::Kill(void)
{
CObjectSingleSource::Kill();
}
