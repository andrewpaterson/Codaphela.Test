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
class SInt16Vec2 : public SVec2<int16, int32>
{
public:const char* ClassName(void){ return "SInt16Vec2";}size ClassSize(void){ return sizeof(SInt16Vec2);};
public:
using SVec2<int16, int32>::SVec2;
using SVec2<int16, int32>::operator=;
void Print(CChars* psx, int iWholeNumbers = -1);
int WholeNumbers(void);
};
typedef CArrayTemplate<SInt16Vec2> CArrayInt16Vec2;
int16 Int16Vec2Dot(const SInt16Vec2* pV1, const SInt16Vec2* pV2);
int16 Int16Vec2Cross(const SInt16Vec2* pV1, const SInt16Vec2* pV2);
SInt16Vec2* Int16Vec2Add(SInt16Vec2* pOut, const SInt16Vec2* pV1, const SInt16Vec2* pV2);
SInt16Vec2* Int16Vec2Subtract(SInt16Vec2* pOut, const SInt16Vec2* pV1, const SInt16Vec2* pV2);
SInt16Vec2* Int16Vec2Minimize(SInt16Vec2* pOut, const SInt16Vec2* pV1, const SInt16Vec2* pV2);
SInt16Vec2* Int16Vec2Maximize(SInt16Vec2* pOut, const SInt16Vec2* pV1, const SInt16Vec2* pV2);
SInt16Vec2* Int16Vec2Scale(SInt16Vec2* pOut, const SInt16Vec2* pV, float32 s);
SInt16Vec2* Int16Vec2Lerp(SInt16Vec2* pOut, const SInt16Vec2* pV1, const SInt16Vec2* pV2, float32 s);
void Int16Vec2MinMax(SInt16Vec2* psMin, SInt16Vec2* psMax, SInt16Vec2* asIn, int iInStride, int iNumPoints);
void Int16Vec2Swap(SInt16Vec2* ps1, SInt16Vec2* ps2);
void Int16Vec2InterpolatePosition(SInt16Vec2* psVecDest, const SInt16Vec2* psVec1, const SInt16Vec2* psVec2, float32 fWeight);
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
template<class V, class M, class N>
class CRectangle
{
public:
V msTopLeft;
V msBottomRight;
public:
void Init(void);
void Init(M iLeft, M iTop, M iRight, M iBottom);
void Init(M iWidth, M iHeight);
void Init(V sTopLeft, V sBottomRight);
void Init(V sSize);
void Init(CRectangle<V, M, N>* pcSource);
void Kill(void);
void Copy(CRectangle<V, M, N>* pcSource);
M GetLeft(void);
M GetTop(void);
M GetRight(void);
M GetBottom(void);
M GetWidth(void);
M GetHeight(void);
N GetArea(void);
void SetWidth(M iWidth);
void SetHeight(M iHeight);
void SetSize(M iWidth, M iHeight);
void SetPos(M x, M y);
void Shrink(M iShrinkLeft, M iShrinkTop, M iShrinkRight, M iShrinkBottom);
void ClipTo(CRectangle<V, M, N>* pcBounds);
bool IsValid(void);
bool IsIn(M x, M y);
bool IsIn(M iLeft, M iTop, M iRight, M iBottom);
bool Equals(CRectangle<V, M, N>* pcOther);
bool Intersect(CRectangle<V, M, N>* pcOther);
bool Inside(CRectangle<V, M, N>* pcOther);
bool Outside(CRectangle<V, M, N>* pcOther);
};
template<class V, class M, class N>
void CRectangle<V, M, N>::Init(void)
{
msTopLeft.x = 0;
msBottomRight.x = 0;
msTopLeft.y = 0;
msBottomRight.y = 0;
}
template<class V, class M, class N>
void CRectangle<V, M, N>::Init(M iLeft, M iTop, M iRight, M iBottom)
{
msTopLeft.x = iLeft;
msTopLeft.y = iTop;
msBottomRight.x = iRight;
msBottomRight.y = iBottom;
}
template<class V, class M, class N>
void CRectangle<V, M, N>::Init(M iWidth, M iHeight)
{
msTopLeft.x = 0;
msTopLeft.y = 0;
msBottomRight.x = iWidth;
msBottomRight.y = iHeight;
}
template<class V, class M, class N>
void CRectangle<V, M, N>::Init(V sTopLeft, V sBottomRight)
{
msTopLeft = sTopLeft;
msBottomRight = sBottomRight;
}
template<class V, class M, class N>
void CRectangle<V, M, N>::Init(V sSize)
{
msTopLeft.x = 0;
msTopLeft.y = 0;
msBottomRight.x = sSize.x;
msBottomRight.y = sSize.y;
}
template<class V, class M, class N>
void CRectangle<V, M, N>::Init(CRectangle<V, M, N>* pcSource)
{
Copy(pcSource);
}
template<class V, class M, class N>
void CRectangle<V, M, N>::Kill(void)
{
}
template<class V, class M, class N>
void CRectangle<V, M, N>::Copy(CRectangle<V, M, N>* pcSource)
{
msTopLeft = pcSource->msTopLeft;
msBottomRight = pcSource->msBottomRight;
}
template<class V, class M, class N>
M CRectangle<V, M, N>::GetLeft(void)
{
return msTopLeft.x;
}
template<class V, class M, class N>
M CRectangle<V, M, N>::GetTop(void)
{
return msTopLeft.y;
}
template<class V, class M, class N>
M CRectangle<V, M, N>::GetRight(void)
{
return msBottomRight.x;
}
template<class V, class M, class N>
M CRectangle<V, M, N>::GetBottom(void)
{
return msBottomRight.y;
}
template<class V, class M, class N>
M CRectangle<V, M, N>::GetWidth(void)
{
return msBottomRight.x - msTopLeft.x;
}
template<class V, class M, class N>
M CRectangle<V, M, N>::GetHeight(void)
{
return msBottomRight.y - msTopLeft.y;
}
template<class V, class M, class N>
N CRectangle<V, M, N>::GetArea(void)
{
return (N)GetWidth() * (N)GetHeight();
}
template<class V, class M, class N>
void CRectangle<V, M, N>::SetWidth(M iWidth)
{
msBottomRight.x = msTopLeft.x + iWidth;
}
template<class V, class M, class N>
void CRectangle<V, M, N>::SetHeight(M iHeight)
{
msBottomRight.y = msTopLeft.y + iHeight;
}
template<class V, class M, class N>
void CRectangle<V, M, N>::SetSize(M iWidth, M iHeight)
{
SetWidth(iWidth);
SetHeight(iHeight);
}
template<class V, class M, class N>
void CRectangle<V, M, N>::SetPos(M x, M y)
{
M iWidth;
M iHeight;
iWidth = GetWidth();
iHeight = GetHeight();
msTopLeft.x = x;
msTopLeft.y = y;
msBottomRight.x = msTopLeft.x + iWidth;
msBottomRight.y = msTopLeft.y + iHeight;
}
template<class V, class M, class N>
void CRectangle<V, M, N>::Shrink(M iShrinkLeft, M iShrinkTop, M iShrinkRight, M iShrinkBottom)
{
msTopLeft.x += iShrinkLeft;
msTopLeft.y += iShrinkTop;
msBottomRight.x -= iShrinkRight;
msBottomRight.y -= iShrinkBottom;
}
template<class V, class M, class N>
void CRectangle<V, M, N>::ClipTo(CRectangle<V, M, N>* pcBounds)
{
if (msTopLeft.x < pcBounds->msTopLeft.x)
{
msTopLeft.x = pcBounds->msTopLeft.x;
}
if (msTopLeft.y < pcBounds->msTopLeft.y)
{
msTopLeft.y = pcBounds->msTopLeft.y;
}
if (msBottomRight.x > pcBounds->msBottomRight.x)
{
msBottomRight.x = pcBounds->msBottomRight.x;
}
if (msBottomRight.y > pcBounds->msBottomRight.y)
{
msBottomRight.y = pcBounds->msBottomRight.y;
}
}
template<class V, class M, class N>
bool CRectangle<V, M, N>::IsValid(void)
{
return (msTopLeft.x <= msBottomRight.x) && (msTopLeft.y <= msBottomRight.y);
}
template<class V, class M, class N>
bool CRectangle<V, M, N>::IsIn(M x, M y)
{
return (((x >= msTopLeft.x) && (x <= msBottomRight.x)) && ((y >= msTopLeft.y) && (y <= msBottomRight.y)));
}
template<class V, class M, class N>
bool CRectangle<V, M, N>::IsIn(M iLeft, M iTop, M iRight, M iBottom)
{
return (IsIn(iLeft, iTop) && IsIn(iRight, iBottom));
}
template<class V, class M, class N>
bool CRectangle<V, M, N>::Equals(CRectangle<V, M, N>* pcOther)
{
if (pcOther)
{
if ((msTopLeft.y == pcOther->msTopLeft.y) &&
(msBottomRight.y == pcOther->msBottomRight.y) &&
(msTopLeft.x == pcOther->msTopLeft.x) &&
(msBottomRight.x == pcOther->msBottomRight.x))
{
return true;
}
}
return false;
}
template<class V, class M, class N>
bool CRectangle<V, M, N>::Intersect(CRectangle<V, M, N>* pcOther)
{
return !(msBottomRight.x <= pcOther->msTopLeft.x ||
msTopLeft.x >= pcOther->msBottomRight.x ||
msBottomRight.y <= pcOther->msTopLeft.y ||
msTopLeft.y >= pcOther->msBottomRight.y);
}
template<class V, class M, class N>
bool CRectangle<V, M, N>::Inside(CRectangle<V, M, N>* pcOther)
{
return (msTopLeft.x >= pcOther->msTopLeft.x &&
msBottomRight.x <= pcOther->msBottomRight.x &&
msTopLeft.y >= pcOther->msTopLeft.y &&
msBottomRight.y <= pcOther->msBottomRight.y);
}
template<class V, class M, class N>
bool CRectangle<V, M, N>::Outside(CRectangle<V, M, N>* pcOther)
{
return (msBottomRight.x <= pcOther->msTopLeft.x ||
msTopLeft.x >= pcOther->msBottomRight.x ||
msBottomRight.y <= pcOther->msTopLeft.y ||
msTopLeft.y >= pcOther->msBottomRight.y);
}
class CInt32Rect : public CRectangle<SInt32Vec2, int32, int64>
{
public:
using CRectangle<SInt32Vec2, int32, int64>::Init;
void Init(int64 iLeft, int64 iTop, int64 iRight, int64 iBottom);
void GrowToContain(int32 iXPos, int32 iYPos);
void GrowToContain(CInt32Rect* pcOther);
SFloat32Vec2 GetUVCoordinatesTopLeft(int32 iTextureXSize, int32 iTextureYSize);
SFloat32Vec2 GetUVCoordinatesBottomRight(int32 iTextureXSize, int32 iTextureYSize);
};
typedef CArrayTemplate<CInt32Rect> CArrayInt32Rect;
class SFloat64Vec3;
class SFloat4x4;
class SFloat64Vec2 : public SVec2<float64, float128>
{
public:const char* ClassName(void){ return "SFloat64Vec2";}size ClassSize(void){ return sizeof(SFloat64Vec2);};
public:
using SVec2<float64, float128>::SVec2;
using SVec2<float64, float128>::operator=;
void Fix(void);
int WholeNumbers(void);
void Print(CChars* psx, int iWholeNumbers = -1, int iDecimals = 2);
void Normalize(void);
bool CloselyEqual(SFloat64Vec2* ps);
bool CloselyEqual(SFloat64Vec2* ps, float64 fTolerance);
void Transform(bool bMirrorX, bool bMirrorY, float64 fRotation, float64 fScale, SFloat64Vec2* psTranslation);
};
typedef CArrayTemplate<SFloat64Vec2> CArrayFloat64Vec2;
float64 Float64Vec2Dot(const SFloat64Vec2* pV1, const SFloat64Vec2* pV2);
float64 Float64Vec2Cross(const SFloat64Vec2* pV1, const SFloat64Vec2* pV2);
SFloat64Vec2* Float64Vec2Add(SFloat64Vec2* pOut, const SFloat64Vec2* pV1, const SFloat64Vec2* pV2);
SFloat64Vec2* Float64Vec2Subtract(SFloat64Vec2* pOut, const SFloat64Vec2* pV1, const SFloat64Vec2* pV2);
SFloat64Vec2* Float64Vec2Minimize(SFloat64Vec2* pOut, const SFloat64Vec2* pV1, const SFloat64Vec2* pV2);
SFloat64Vec2* Float64Vec2Maximize(SFloat64Vec2* pOut, const SFloat64Vec2* pV1, const SFloat64Vec2* pV2);
SFloat64Vec2* Float64Vec2Scale(SFloat64Vec2* pOut, const SFloat64Vec2* pV, float64 s);
SFloat64Vec2* Float64Vec2Lerp(SFloat64Vec2* pOut, const SFloat64Vec2* pV1, const SFloat64Vec2* pV2, float64 s);
SFloat64Vec2* Float64Vec2TransformCoord(SFloat64Vec2* pOut, SFloat64Vec2* pV, SFloat4x4* psMat);
void Float64Vec2TransformCoords(SFloat64Vec2* asOut, int iOutStride, SFloat64Vec2* asIn, int iInStride, SFloat4x4* psMat, int iNumPoints);
SFloat64Vec2* Float64Vec2TransformNormal(SFloat64Vec2* pOut, SFloat64Vec2* pV, SFloat4x4* psMat);
void Float64Vec2TransformNormals(SFloat64Vec2* asOut, int iOutStride, SFloat64Vec2* asIn, int iInStride, SFloat4x4* psMat, int iNumPoints);
void Float64Vec2MinMax(SFloat64Vec2* psMin, SFloat64Vec2* psMax, SFloat64Vec2* asIn, int iInStride, int iNumPoints);
void Float64Vec2Swap(SFloat64Vec2* ps1, SFloat64Vec2* ps2);
float64 Float64Vec2ArcSweep(SFloat64Vec2* psStart, SFloat64Vec2* psEnd, SFloat64Vec2* psCenter, bool bClockwise);
void Float64Vec2InterpolatePosition(SFloat64Vec2* psVecDest, const SFloat64Vec2* psVec1, const SFloat64Vec2* psVec2, float64 fWeight);
void Float64Vec2InterpolateNormal(SFloat64Vec2* psVecDest, const SFloat64Vec2* psVec1, const SFloat64Vec2* psVec2, float64 fWeight);
void Float64Vec2RotateAboutNormalisedAxis(SFloat64Vec3* psVecDest, SFloat64Vec3 p, float64 fTheta, SFloat64Vec2 r);
void Float64Vec2Normalise(SFloat64Vec2* pOut, SFloat64Vec2* pV);
class CFloat64Rect : public CRectangle<SFloat64Vec2, float64, float128>
{
};
typedef CArrayTemplate<CFloat64Rect> CArrayFloat64Rect;
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
class SFloat32Vec4;
class SFloat64Vec2;
class SFloat4x4;
class SFloat64Vec3 : public SVec3<float64, float128>
{
public:const char* ClassName(void){ return "SFloat64Vec3";}size ClassSize(void){ return sizeof(SFloat64Vec3);};
public:
using SVec3<float64, float128>::SVec3;
using SVec3<float64, float128>::operator=;
void Fix(void);
int WholeNumbers(void);
void Print(CChars* psx, int iWholeNumbers = -1, int iDecimals = 2);
void Copy(const SFloat32Vec4* ps);
void Copy(const SFloat64Vec3* ps);
void Copy(const SFloat64Vec2* ps);
void Normalize(void);
bool CloselyEqual(SFloat64Vec3* ps);
bool CloselyEqual(SFloat64Vec3* ps, float64 fTolerance);
};
typedef CArrayTemplate<SFloat64Vec3> CArrayFloat64Vec3;
float64 Float64Vec3Dot(const SFloat64Vec3* pV1, const SFloat64Vec3* pV2);
SFloat64Vec3* Float64Vec3Cross(SFloat64Vec3* pOut, const SFloat64Vec3* pV1, const SFloat64Vec3* pV2);
SFloat64Vec3* Float64Vec3Add(SFloat64Vec3* pOut, const SFloat64Vec3* pV1, const SFloat64Vec3* pV2);
SFloat64Vec3* Float64Vec3Subtract(SFloat64Vec3* pOut, const SFloat64Vec3* pV1, const SFloat64Vec3* pV2);
SFloat64Vec3* Float64Vec3Minimize(SFloat64Vec3* pOut, const SFloat64Vec3* pV1, const SFloat64Vec3* pV2);
SFloat64Vec3* Float64Vec3Maximize(SFloat64Vec3* pOut, const SFloat64Vec3* pV1, const SFloat64Vec3* pV2);
SFloat64Vec3* Float64Vec3Scale(SFloat64Vec3* pOut, const SFloat64Vec3* pV, float64 s);
SFloat64Vec3* Float64Vec3Lerp(SFloat64Vec3* pOut, const SFloat64Vec3* pV1, const SFloat64Vec3* pV2, float64 s);
SFloat64Vec3* Float64Vec3TransformCoord(SFloat64Vec3* pOut, SFloat64Vec3* pV, SFloat4x4* psMat);
void Float64Vec3TransformCoords(SFloat64Vec3* asOut, int iOutStride, SFloat64Vec3* asIn, int iInStride, SFloat4x4* psMat, int iNumPoints);
SFloat64Vec3* Float64Vec3TransformNormal(SFloat64Vec3* pOut, SFloat64Vec3* pV, SFloat4x4* psMat);
void Float64Vec3TransformNormals(SFloat64Vec3* asOut, int iOutStride, SFloat64Vec3* asIn, int iInStride, SFloat4x4* psMat, int iNumPoints);
void Float64Vec3MinMax(SFloat64Vec3* psMin, SFloat64Vec3* psMax, SFloat64Vec3* asIn, int iInStride, int iNumPoints);
void Float64Vec3Swap(SFloat64Vec3* ps1, SFloat64Vec3* ps2);
void Float64Vec3InterpolatePosition(SFloat64Vec3* psVecDest, const SFloat64Vec3* psVec1, const SFloat64Vec3* psVec2, float64 fWeight);
void Float64Vec3InterpolateNormal(SFloat64Vec3* psVecDest, const SFloat64Vec3* psVec1, const SFloat64Vec3* psVec2, float64 fWeight);
void Float64Vec3RotateAboutNormalisedAxis(SFloat64Vec3* psVecDest, SFloat64Vec3 p, float64 fTheta, SFloat64Vec3 r);
void Float64Vec3Normalise(SFloat64Vec3* pOut, SFloat64Vec3* pV);
class SFloat64Vec2;
class SFloat64Vec3;
class SDouble4x4;
class SFloat64Vec4 : public SVec4<float64, float128>
{
public:const char* ClassName(void){ return "SFloat64Vec4";}size ClassSize(void){ return sizeof(SFloat64Vec4);};
public:
SFloat64Vec4() {};
SFloat64Vec4(float64 x, float64 y, float64 z, float64 w);
using SVec4<float64, float128>::SVec4;
using SVec4<float64, float128>::operator=;
void Fix(void);
int WholeNumbers(void);
void Print(CChars* psz, int iWholeNumbers = -1, int iDecimals = 2);
void Copy(const SFloat64Vec4* ps);
void Copy(const SFloat64Vec3* ps);
void Copy(const SFloat64Vec2* ps);
void Normalize(void);
bool CloselyEqual(SFloat64Vec4* ps);
bool CloselyEqual(SFloat64Vec4* ps, float64 fTolerance);
};
typedef CArrayTemplate<SFloat64Vec4> CArrayFloat64Vec4;
float64 Float64Vec4Dot(const SFloat64Vec4* pV1, const SFloat64Vec4* pV2);
SFloat64Vec4* Float64Vec4Add(SFloat64Vec4* pOut, const SFloat64Vec4* pV1, const SFloat64Vec4* pV2);
SFloat64Vec4* Float64Vec4Subtract(SFloat64Vec4* pOut, const SFloat64Vec4* pV1, const SFloat64Vec4* pV2);
SFloat64Vec4* Float64Vec4Minimize(SFloat64Vec4* pOut, const SFloat64Vec4* pV1, const SFloat64Vec4* pV2);
SFloat64Vec4* Float64Vec4Maximize(SFloat64Vec4* pOut, const SFloat64Vec4* pV1, const SFloat64Vec4* pV2);
SFloat64Vec4* Float64Vec4Scale(SFloat64Vec4* pOut, const SFloat64Vec4* pV, float64 s);
SFloat64Vec4* Float64Vec4Lerp(SFloat64Vec4* pOut, const SFloat64Vec4* pV1, const SFloat64Vec4* pV2, float64 s);
SFloat64Vec4* Float64Vec4TransformCoord(SFloat64Vec4* psOut, SFloat64Vec4* psV, SDouble4x4* psMat);
void Float64Vec4TransformCoords(SFloat64Vec4* asOut, int iOutStride, SFloat64Vec4* asIn, int iInStride, SDouble4x4* psMat, int iNumPoints);
SFloat64Vec4* Float64Vec4TransformNormal(SFloat64Vec4* pOut, SFloat64Vec4* pV, SDouble4x4* psMat);
void Float64Vec4TransformNormals(SFloat64Vec4* asOut, int iOutStride, SFloat64Vec4* asIn, int iInStride, SDouble4x4* psMat, int iNumPoints);
void Float64Vec4MinMax(SFloat64Vec4* psMin, SFloat64Vec4* psMax, SFloat64Vec4* asIn, int iInStride, int iNumPoints);
void Float64Vec4Swap(SFloat64Vec4* ps1, SFloat64Vec4* ps2);
void Float64Vec4InterpolatePosition(SFloat64Vec4* psVecDest, const SFloat64Vec4* psVec1, const SFloat64Vec4* psVec2, float64 fWeight);
void Float64Vec4InterpolateNormal(SFloat64Vec4* psVecDest, const SFloat64Vec4* psVec1, const SFloat64Vec4* psVec2, float64 fWeight);
void Float64Vec4Normalise(SFloat64Vec4* pOut, SFloat64Vec4* pV);
class SFloat64Vec2;
class SFloat64Vec3;
class SFloat64Vec4;
class SDouble4x4
{
public:const char* ClassName(void){ return "SDouble4x4";}size ClassSize(void){ return sizeof(SDouble4x4);};
public:
SFloat64Vec4 x;
SFloat64Vec4 y;
SFloat64Vec4 z;
SFloat64Vec4 pos;
void Init(void);
void Init(SFloat64Vec3* psX, SFloat64Vec3* psY, SFloat64Vec3* psZ, SFloat64Vec3* psPos);
void Zero(void);
bool Save(CFileWriter* pcFileWriter);
bool Load(CFileReader* pcFileReader);
void Fix(void);
void Identity(void);
bool Inverse(SDouble4x4* psOut, double* pfDeterminant);
void Adjoint(SDouble4x4* psOut);
double Determinant(void);
SFloat64Vec3* At(void);
SFloat64Vec3* Up(void);
SFloat64Vec3* Across(void);
SFloat64Vec3* Pos(void);
void Print(CChars* psz, bool bOneLine, int iWholeNumbers = -1, int iDecimals = 2);
void Dump(void);
};
typedef CArrayTemplate<SDouble4x4> CArrayDouble4x4;
SDouble4x4* Double4x4Identity(SDouble4x4* psOut);
SDouble4x4* Double4x4Multiply(SDouble4x4* psOut, SDouble4x4* psLeft, SDouble4x4* psRight);
void Double4x4RotationX(SDouble4x4* psOut, double fRad);
void Double4x4RotationY(SDouble4x4* psOut, double fRad);
void Double4x4RotationZ(SDouble4x4* psOut, double fRad);
void Double4x4RotationVector(SDouble4x4* psOut, SFloat64Vec3* psV, double fRad);
void Double4x4Translation(SDouble4x4* psOut, double x, double y, double z);
bool Double4x4Inverse(SDouble4x4* psOut, double* pfDeterminant, SDouble4x4* psIn);
SDouble4x4* Double4x4LookAtRH(SDouble4x4* psOut, const SFloat64Vec3* psEye, const SFloat64Vec3* psAt, const SFloat64Vec3* psUp);
SDouble4x4* Double4x4PerspectiveFovRH(SDouble4x4* psOut, double fFovY, double fAspect, double fZNear, double fZFar);
bool Double4x4Equals(SDouble4x4* ps1, SDouble4x4* ps2);
class SQuaternion
{
public:const char* ClassName(void){ return "SQuaternion";}size ClassSize(void){ return sizeof(SQuaternion);};
public:
float x, y, z, w;
SQuaternion() {}
SQuaternion(const float *);
SQuaternion(float x, float y, float z, float w);
SQuaternion& operator += (const SQuaternion&);
SQuaternion& operator -= (const SQuaternion&);
SQuaternion& operator *= (float);
SQuaternion& operator /= (float);
SQuaternion operator + () const;
SQuaternion operator - () const;
SQuaternion operator + (const SQuaternion&) const;
SQuaternion operator - (const SQuaternion&) const;
SQuaternion operator * (float) const;
SQuaternion operator / (float) const;
friend SQuaternion operator * (float, const SQuaternion&);
bool operator == (const SQuaternion&) const;
bool operator != (const SQuaternion&) const;
};
SFloat32Vec3* GetPosition(SFloat32Vec3* psPoints, size iStride, size iPoint);
SFloat32Vec3* GetNormal(SFloat32Vec3* psNormals, size iStride, size iNormal);
int GetIndex(SFloat32Vec3* psPoints, size iStride, SFloat32Vec3* psPosition);
typedef int sig_atomic_t;
typedef void (*__sighandler_t)(int);
__sighandler_t signal(int iSignal, __sighandler_t fHandler);
int raise(int iSignal);
class CTimer
{
private:
int64 miStart;
int64 miStart2;
public:
int64 miTotalTime;
int64 miUpdateTime;
float mfTotalTime;
float mfUpdateTime;
float mfUpdatesPerSecond;
void Init(void);
void Update(void);
void Reset(void);
void Kill(void);
float GetUpdateTimeInSeconds(void) { return mfUpdateTime; }
float GetUpdatesPerSecond(void) { return mfUpdatesPerSecond; }
float GetTotalTimeInSeconds(void) { return mfTotalTime; }
int64 GetUpdateTimeInMillieconds(void) { return miUpdateTime; }
int64 GetTotalTimeInMillieconds(void) { return miTotalTime; }
void HumanReadable(CChars* psz);
};
extern CTimer gcTimer;
int64 GetDebugTickCount(void);
void PrivateBeginTests(const char* szFile);
void PrivateTestStatistics();
int TestTotalStatistics(void);
void InitTotalStatistics(void);
bool Pass(void);
bool Failed(size iLine, const char* szFile);
bool Failed(void);
class CChars;
class CAssertStatistics
{
protected:
size miTestsRun;
size miTestsPassed;
size miTestsFailed;
CTimer mcTestTimer;
size miTotalTestsRun;
size miTotalTestsPassed;
size miTotalTestsFailed;
CTimer mcTotalTimer;
public:
void Init(void);
void Kill(void);
void Failed(void);
void Passed(void);
void Begin(const char* szFile);
void End(void);
void PrintTest(CChars* psz);
void PrintTotal(CChars* psz);
int GetTotalTestsFailed(void);
};
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
bool IsMultiLine(const char* szExpected, const char* szActual);
void ToTristateString(TRISTATE t, char* szString, size iStringLength);
void ToBoolString(bool b, char* szString, size iStringLength);
void ToCharString(uint8 c, char* szString, size iStringLength);
void ToCharString(char c, char* szString, size iStringLength);
void ToShortString(int16 i, char* szString, size iStringLength);
void ToShortString(uint16 i, char* szString, size iStringLength);
void ToIntString(int32 i, char* szString, size iStringLength);
void ToIntString(uint32 i, char* szString, size iStringLength);
void ToByteHexString(int8 i, char* szString, size iStringLength);
void ToByteHexString(uint8 i, char* szString, size iStringLength);
void ToShortHexString(int16 i, char* szString, size iStringLength);
void ToShortHexString(uint16 i, char* szString, size iStringLength);
void ToIntHexString(int32 i, char* szString, size iStringLength);
void ToIntHexString(uint32 i, char* szString, size iStringLength);
void ToLongString(int64 i, char* szString, size iStringLength);
void ToLongString(uint64 i, char* szString, size iStringLength);
void ToLongHexString(int64 i, char* szString, size iStringLength);
void ToLongHexString(uint64 i, char* szString, size iStringLength);
void ToFloatString(float f, char* sz, int iDecimals);
void ToFloat3String(SFloat32Vec3* psFloat3, char* sz, int iWholeNumbers, int iDecimals);
void ToDoubleString(double f, char* sz, int iDecimals);
void ToPointerString(void* pv, char* sz, size iStringLength);
void ToMD5String(uint8* puc, char* sz, size iStringLength);
bool Failed(const char* szExpected, const char* szActual, const char* szPrefix, size iLine, const char* szFile, bool bNewLine);
bool PrivateAssertTristate(TRISTATE tExpected, TRISTATE tActual, char* szPrefix, size iLine, const char* szFile);
bool PrivateAssertBool(bool bExpected, bool bActual, char* szPrefix, size iLine, const char* szFile);
bool PrivateAssertChar(char cExpected, char cActual, char* szPrefix, size iLine, const char* szFile);
bool PrivateAssertInt(int32 iExpected, int32 iActual, const char* szPrefix, size iLine, const char* szFile);
bool PrivateAssertInt(int32 iExpected, uint32 iActual, const char* szPrefix, size iLine, const char* szFile);
bool PrivateAssertInt(uint32 iExpected, uint32 iActual, const char* szPrefix, size iLine, const char* szFile);
bool PrivateAssertIntHex(int32 iExpected, int32 iActual, char* szPrefix, size iLine, const char* szFile);
bool PrivateAssertIntHex(int32 iExpected, uint32 iActual, char* szPrefix, size iLine, const char* szFile);
bool PrivateAssertIntHex(uint32 iExpected, uint32 iActual, char* szPrefix, size iLine, const char* szFile);
bool PrivateAssertByte(int8 iExpected, int8 iActual, char* szPrefix, size iLine, char* szFile);
bool PrivateAssertByte(int8 iExpected, uint8 iActual, char* szPrefix, size iLine, char* szFile);
bool PrivateAssertByte(uint8 iExpected, uint8 iActual, char* szPrefix, size iLine, char* szFile);
bool PrivateAssertByteHex(int8 iExpected, int8 iActual, char* szPrefix, size iLine, char* szFile);
bool PrivateAssertByteHex(int8 iExpected, uint8 iActual, char* szPrefix, size iLine, char* szFile);
bool PrivateAssertByteHex(uint8 iExpected, uint8 iActual, char* szPrefix, size iLine, char* szFile);
bool PrivateAssertShort(int16 iExpected, int16 iActual, char* szPrefix, size iLine, const char* szFile);
bool PrivateAssertShort(int16 iExpected, uint16 iActual, char* szPrefix, size iLine, const char* szFile);
bool PrivateAssertShort(uint16 iExpected, uint16 iActual, char* szPrefix, size iLine, const char* szFile);
bool PrivateAssertShortHex(int16 iExpected, int16 iActual, char* szPrefix, size iLine, const char* szFile);
bool PrivateAssertShortHex(int16 iExpected, uint16 iActual, char* szPrefix, size iLine, const char* szFile);
bool PrivateAssertShortHex(uint16 iExpected, uint16 iActual, char* szPrefix, size iLine, const char* szFile);
bool PrivateAssertLongLongInt(int64 iExpected, int64 iActual, char* szPrefix, size iLine, const char* szFile);
bool PrivateAssertLongLongIntHex(int64 iExpected, int64 iActual, char* szPrefix, size iLine, const char* szFile);
bool PrivateAssertFloat(float32 fExpected, float32 fActual, int iDecimals, char* szPrefix, size iLine, const char* szFile);
bool PrivateAssertFloat(float32 fExpected, float32 fActual, char* szPrefix, size iLine, char* szFile);
bool PrivateAssertFloat3(SFloat32Vec3 fExpected, SFloat32Vec3* pfActual, int iDecimals, char* szPrefix, size iLine, char* szFile);
bool PrivateAssertDouble(float64 fExpected, float64 fActual, int iDecimals, char* szPrefix, size iLine, const char* szFile);
bool PrivateAssertLongDouble(float128 fExpected, float128 fActual, int iDecimals, char* szPrefix, size iLine, char* szFile);
bool PrivateAssertSize(size iExpected, size iActual, char* szPrefix, size iLine, const char* szFile);
bool PrivateAssertString(const char* szExpected, const char* szActual, bool bTestCase, char* szPrefix, size iLine, const char* szFile);
bool PrivateAssertString(const char* szExpected, const uint8* szActual, bool bTestCase, char* szPrefix, size iLine, const char* szFile);
bool PrivateAssertString(const uint8* szExpected, const uint8* szActual, bool bTestCase, char* szPrefix, size iLine, const char* szFile);
bool PrivateAssertStringApproximate(const char* szExpected, const char* szActual, bool bTestCase, char* szPrefix, size iLine, const char* szFile);
bool PrivateAssertMemory(const void* pvExpected, void* pvActual, size iSize, char* szPrefix, size iLine, const char* szFile);
bool PrivateAssertZero(void* pvActual, size iSize, char* szPrefix, size iLine, const char* szFile);
bool PrivateAssertNegative(int i, char* szPrefix, size iLine, const char* szFile);
bool PrivateAssertPositive(int i, char* szPrefix, size iLine, const char* szFile);
bool PrivateAssertNumber(const char* szExpected, CNumber* pcActual, char* szPrefix, size iLine, const char* szFile);
bool PrivateAssertPointer(void* pvExpected, void* pvActual, char* szPrefix, size iLine, const char* szFile);
bool PrivateAssertNotPointer(void* pvExpected, void* pvActual, char* szPrefix, size iLine, const char* szFile);
bool PrivateAssertNotNull(void* pvActual, char* szPrefix, size iLine, const char* szFile);
bool PrivateAssertNull(void* pvActual, char* szPrefix, size iLine, const char* szFile);
bool PrivateAssertMD5(uint8* pucExpected, uint8* pucActual, char* szPrefix, size iLine, const char* szFile);
bool PrivateAssertStringStartsWith(const char* szExpected, const char* szActual, bool bTestCase, char* szPrefix, size iLine, const char* szFile);
void AssertRectangle(int32 iLeft, int32 iTop, int32 iRight, int32 iBottom, CInt32Rect* pcRectangle)
{
if (!PrivateAssertInt(iLeft, pcRectangle->GetLeft(), 0L, 13, "/home/r2d2/Codaphela/test/TestSupportLib/TestSupportLib/TestRectangle.cpp")) __builtin_trap();;;
if (!PrivateAssertInt(iTop, pcRectangle->GetTop(), 0L, 14, "/home/r2d2/Codaphela/test/TestSupportLib/TestSupportLib/TestRectangle.cpp")) __builtin_trap();;;
if (!PrivateAssertInt(iRight, pcRectangle->GetRight(), 0L, 15, "/home/r2d2/Codaphela/test/TestSupportLib/TestSupportLib/TestRectangle.cpp")) __builtin_trap();;;
if (!PrivateAssertInt(iBottom, pcRectangle->GetBottom(), 0L, 16, "/home/r2d2/Codaphela/test/TestSupportLib/TestSupportLib/TestRectangle.cpp")) __builtin_trap();;;
}
void TestRectangleClipTo(void)
{
CInt32Rect cBounds;
CInt32Rect cRectangle;
cBounds.Init(0, 0, 10, 10);
cRectangle.Init(2, 3, 8, 9);
cRectangle.ClipTo(&cBounds);
AssertRectangle(2, 3, 8, 9, &cRectangle);
cRectangle.Init(-5, -4, 15, 14);
cRectangle.ClipTo(&cBounds);
AssertRectangle(0, 0, 10, 10, &cRectangle);
cRectangle.Init(-3, 2, 6, 12);
cRectangle.ClipTo(&cBounds);
AssertRectangle(0, 2, 6, 10, &cRectangle);
cRectangle.Init(0, 0, 20, 20);
cBounds.Init(5, 6, 7, 8);
cRectangle.ClipTo(&cBounds);
AssertRectangle(5, 6, 7, 8, &cRectangle);
}
void TestRectangleGetArea(void)
{
CInt32Rect cRect;
cRect.Init(2, 3, 12, 8);
if (!PrivateAssertLongLongInt(50, cRect.GetArea(), 0L, 63, "/home/r2d2/Codaphela/test/TestSupportLib/TestSupportLib/TestRectangle.cpp")) __builtin_trap();;;
cRect.Init(0, 0, 50000, 50000);
if (!PrivateAssertLongLongInt(2500000000LL, cRect.GetArea(), 0L, 67, "/home/r2d2/Codaphela/test/TestSupportLib/TestSupportLib/TestRectangle.cpp")) __builtin_trap();;;
cRect.Init(-60000, -70000, 60000, 70000);
if (!PrivateAssertLongLongInt(16800000000LL, cRect.GetArea(), 0L, 70, "/home/r2d2/Codaphela/test/TestSupportLib/TestSupportLib/TestRectangle.cpp")) __builtin_trap();;;
}
void TestRectangleInt16(void)
{
CRectangle<SInt16Vec2, int16, int32> cRect;
cRect.Init(-100, -50, 200, 250);
if (!PrivateAssertInt(300, cRect.GetWidth(), 0L, 84, "/home/r2d2/Codaphela/test/TestSupportLib/TestSupportLib/TestRectangle.cpp")) __builtin_trap();;;
if (!PrivateAssertInt(300, cRect.GetHeight(), 0L, 85, "/home/r2d2/Codaphela/test/TestSupportLib/TestSupportLib/TestRectangle.cpp")) __builtin_trap();;;
if (!PrivateAssertInt(90000, cRect.GetArea(), 0L, 86, "/home/r2d2/Codaphela/test/TestSupportLib/TestSupportLib/TestRectangle.cpp")) __builtin_trap();;;
}
void TestRectangleFloat64(void)
{
CFloat64Rect cRect;
CFloat64Rect cOther;
SFloat64Vec2 sTopLeft;
SFloat64Vec2 sBottomRight;
sTopLeft.Init(-1.778, -30.553733);
sBottomRight.Init(17.018003, 2.6162);
cRect.Init(sTopLeft, sBottomRight);
if (!PrivateAssertDouble(18.796003, cRect.GetWidth(), 9, 0L, 105, "/home/r2d2/Codaphela/test/TestSupportLib/TestSupportLib/TestRectangle.cpp")) __builtin_trap();;;
if (!PrivateAssertDouble(33.169933, cRect.GetHeight(), 9, 0L, 106, "/home/r2d2/Codaphela/test/TestSupportLib/TestSupportLib/TestRectangle.cpp")) __builtin_trap();;;
if (!PrivateAssertDouble(18.796003 * 33.169933, (float64)cRect.GetArea(), 6, 0L, 107, "/home/r2d2/Codaphela/test/TestSupportLib/TestSupportLib/TestRectangle.cpp")) __builtin_trap();;;
if (!PrivateAssertBool(true, cRect.IsValid(), 0L, 108, "/home/r2d2/Codaphela/test/TestSupportLib/TestSupportLib/TestRectangle.cpp")) __builtin_trap();;;
if (!PrivateAssertBool(true, cRect.IsIn(0.5, -10.25), 0L, 109, "/home/r2d2/Codaphela/test/TestSupportLib/TestSupportLib/TestRectangle.cpp")) __builtin_trap();;;
if (!PrivateAssertBool(false, cRect.IsIn(17.5, 0.0), 0L, 110, "/home/r2d2/Codaphela/test/TestSupportLib/TestSupportLib/TestRectangle.cpp")) __builtin_trap();;;
cRect.SetPos(0.0, 0.0);
if (!PrivateAssertDouble(0.0, cRect.GetLeft(), 9, 0L, 114, "/home/r2d2/Codaphela/test/TestSupportLib/TestSupportLib/TestRectangle.cpp")) __builtin_trap();;;
if (!PrivateAssertDouble(18.796003, cRect.GetRight(), 9, 0L, 115, "/home/r2d2/Codaphela/test/TestSupportLib/TestSupportLib/TestRectangle.cpp")) __builtin_trap();;;
if (!PrivateAssertDouble(33.169933, cRect.GetBottom(), 9, 0L, 116, "/home/r2d2/Codaphela/test/TestSupportLib/TestSupportLib/TestRectangle.cpp")) __builtin_trap();;;
cOther.Init(10.0, 20.0, 30.0, 40.0);
if (!PrivateAssertBool(true, cRect.Intersect(&cOther), 0L, 119, "/home/r2d2/Codaphela/test/TestSupportLib/TestSupportLib/TestRectangle.cpp")) __builtin_trap();;;
cRect.ClipTo(&cOther);
if (!PrivateAssertDouble(10.0, cRect.GetLeft(), 9, 0L, 121, "/home/r2d2/Codaphela/test/TestSupportLib/TestSupportLib/TestRectangle.cpp")) __builtin_trap();;;
if (!PrivateAssertDouble(20.0, cRect.GetTop(), 9, 0L, 122, "/home/r2d2/Codaphela/test/TestSupportLib/TestSupportLib/TestRectangle.cpp")) __builtin_trap();;;
if (!PrivateAssertDouble(18.796003, cRect.GetRight(), 9, 0L, 123, "/home/r2d2/Codaphela/test/TestSupportLib/TestSupportLib/TestRectangle.cpp")) __builtin_trap();;;
if (!PrivateAssertDouble(33.169933, cRect.GetBottom(), 9, 0L, 124, "/home/r2d2/Codaphela/test/TestSupportLib/TestSupportLib/TestRectangle.cpp")) __builtin_trap();;;
if (!PrivateAssertBool(true, cRect.Inside(&cOther), 0L, 125, "/home/r2d2/Codaphela/test/TestSupportLib/TestSupportLib/TestRectangle.cpp")) __builtin_trap();;;
cOther.Init(0.25, 0.5);
if (!PrivateAssertDouble(0.125, (float64)cOther.GetArea(), 9, 0L, 128, "/home/r2d2/Codaphela/test/TestSupportLib/TestSupportLib/TestRectangle.cpp")) __builtin_trap();;;
}
void TestRectangle(void)
{
PrivateBeginTests("/home/r2d2/Codaphela/test/TestSupportLib/TestSupportLib/TestRectangle.cpp");
TestRectangleClipTo();
TestRectangleGetArea();
TestRectangleInt16();
TestRectangleFloat64();
PrivateTestStatistics();
}
