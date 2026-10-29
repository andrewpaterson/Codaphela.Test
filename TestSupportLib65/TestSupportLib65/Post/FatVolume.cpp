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
int isalnum(int c);
int isalpha(int c);
int isblank(int c);
int iscntrl(int c);
int isdigit(int c);
int isgraph(int c);
int islower(int c);
int isprint(int c);
int ispunct(int c);
int isspace(int c);
int isupper(int c);
int isxdigit(int c);
int tolower(int c);
int toupper(int c);
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
bool MemCompare(const char* szName1, const char* szName2, CChars* psz1, CChars* psz2, void* pvMem1, void* pvMem2, filePos iLength1, filePos iLength2);
int64 FatDecodeDateTime(uint16 date, uint16 time);
uint16 GetSystemClockDate(void);
uint16 GetSystemClockTime(void);
typedef long time_t;
typedef long clock_t;
struct tm
{
int tm_sec;
int tm_min;
int tm_hour;
int tm_mday;
int tm_mon;
int tm_year;
int tm_wday;
int tm_yday;
int tm_isdst;
};
extern "C"
{
time_t time(time_t* ptTime);
clock_t clock(void);
struct tm* localtime(const time_t* ptTime);
struct tm* gmtime(const time_t* ptTime);
time_t mktime(struct tm* psTime);
double difftime(time_t tEnd, time_t tStart);
size_t strftime(char* szDest, size_t uiMax, const char* szFormat, const struct tm* psTime);
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
class CFileDrive
{
protected:
uint64 muiMaxSector;
uint32 muiSectorSize;
public:
void Init(uint32 uiSectorSize);
virtual void Kill(void) =0;
virtual bool Read(uint64 uiSector, void* pvData) =0;
virtual bool Read(uint64 uiSector, uint32 uiNumSectors, void* pvData) =0;
virtual bool Write(uint64 uiSector, void* pvData) =0;
virtual bool Write(uint64 uiSector, uint32 uiNumSectors, void* pvData) =0;
virtual bool Erase(uint64 uiStartSector, uint64 uiStopSectorInclusive) =0;
uint64 GetTotalSectors(void);
uint32 GetSectorSize(void);
virtual uint32 GetPageSize(void);
uint64 SetMaxSectorForTesting(uint64 uiMaxSector);
};
struct SFatCache
{
void* pvCachedSector;
uint32 uiTimeStamp;
void Clear(void);
uint8* Get(void);
bool IsValid(void);
};
class CFatSectorCache
{
public:
uint64 muiCreationStamp;
uint32 muiInfoSector;
uint16 muiLocks;
bool mbDirty;
void Init(uint32 uiInfoSector, uint64 uiCreationStamp);
void* GetCache(void);
void Lock(void);
bool Unlock(void);
void Dirty(void);
};
class CFatInfoSectorCache
{
protected:
CLinkedListBlock mllcCachedSectors;
uint16 muiSectorSize;
uint16 muiMinimumUnlockedCaches;
uint16 muiCaches;
CFileDrive* mpcDrive;
uint64 muiCreationStamp;
public:
void Init(CFileDrive* pcDrive, uint16 uiMinimumUnlockedCaches);
bool Kill(void);
SFatCache ReadSector(uint32 uiInfoSector);
void Lock(SFatCache sSectorCache);
bool Unlock(SFatCache sSectorCache);
bool Unlock(uint32 uiSector);
uint16 GetNumAllocatedSectors(void);
uint16 GetNumCachedSectors(void);
uint16 GetLockedCachedSectors(void);
void Dirty(SFatCache sSectorCache);
bool Flush(void);
bool ValidateTimeStamp(SFatCache sSectorCache);
void Dump(void);
protected:
CFatSectorCache* AddNewCache(void);
CFatSectorCache* GetOrCacheSector(uint32 uiInfoSector);
CFatSectorCache* InitialiseCache(uint32 uiInfoSector, CFatSectorCache* pcCachedSector);
bool FlushCache(CFatSectorCache* pcCachedSector);
SFatCache FindCachedSector(uint32 uiInfoSector);
};
typedef uint32 fatEntry;__pragma(pack(push,1))
struct SFatRawDirectoryEntry
{
union
{
struct SFatRawCommon
{
uint8 szShortName[11];
uint8 uiAttributes;
uint8 uiReserved;
uint8 uiCreateTimeTenths;
uint16 uiCreateTime;
uint16 uiCreateDate;
uint16 uiAccessDate;
uint16 uiFirstClusterHighWord;
uint16 uiModifyTime;
uint16 uiModifyDate;
uint16 uiFirstClusterLowWord;
uint32 uiSize;
} sFatRawCommon;
struct SFatRawLongFileName
{
uint8 uiSequence;
uint8 auiChars1[10];
uint8 uiAttributes;
uint8 uiType;
uint8 uiChecksum;
uint8 auiChars2[12];
uint16 uiFirstCluster;
uint8 auiChars3[4];
} sFatRawLongFileName;
} uEntry;
};__pragma(pack(pop))__pragma(pack(push,1))
struct SFatFileSystemInfo
{
uint32 uiTrailSignature;
uint8 uiReserved2[12];
uint32 uiNextFreeCluster;
uint32 uiNumFreeClusters;
uint32 uiStructSignature;
uint8 uiReserved1[480];
uint32 uiLeadSignature;
};__pragma(pack(pop))__pragma(pack(push,1))
struct SFatPartitionEntry
{
uint8 uiStatus;
uint8 uiFirstCylinderHeadSectorSector[3];
uint8 uiPartitionType;
uint8 uiLastCylinderHeadSectorSector[3];
uint32 uiLBAFirstSector;
uint32 uiTotalSectors;
};__pragma(pack(pop))__pragma(pack(push,1))
struct SFatBIOSParameterBlock
{
uint8 uiJumpInstrustion[3];
char szOEMName[8];
uint16 uiBytsPerSector;
uint8 uiSectorsPerCluster;
uint16 uiReservedSectorCount;
uint8 uiNumFileAllocationTables;
uint16 uiRootEntryCount;
uint16 uiTotalSectorsFat16;
uint8 uiMediaType;
uint16 uiFATSzFat16;
uint16 uiSectorsPerTrack;
uint16 uiNumHeads;
uint32 uiNumHiddenSectors;
uint32 uiTotalSectorsFat32;
union
{
struct SFat16BPB
{
uint8 uiDriverNumber;
uint8 uiReserved1;
uint8 uiBootSignature;
uint32 uiVolumeID;
char szVolumeLabel[11];
char szFileSystemType[8];
char acPad1[8];
uint32 uiPad2;
uint8 uiPad3;
uint8 auiExtraPadding[15];
} sFat16;
struct SFat32BPB
{
uint32 uiFATSzFat32;
uint16 uiExtendedFlags;
uint16 uiFileSystemVersion;
uint32 uiRootCluster;
uint16 uiFileSystemInformation;
uint16 uiBackupBootSector;
uint8 auiReserved[12];
uint8 uiDriverNumber;
uint8 uiReserved1;
uint8 uiBootSignature;
uint32 uiVolumeID;
char szVolumeLabel[11];
char szFileSystemType[8];
} sFat32;
} uFatEx;
};__pragma(pack(pop))
struct SFatDirectoryEntry
{
uint8 szName[255 + 1];
uint8 uiAttributes;
time_t tCreateTime;
time_t tModifyTime;
time_t tAccessTime;
uint32 uiSize;
uint32 uiSectorAddress;
uint16 uiSectorOffset;
SFatRawDirectoryEntry sRaw;
};
uint32 GetFirstClusterFromFatEntry(SFatRawDirectoryEntry* psRawEntry, bool bFat32Volume);
const char* FatEntryToString(SFatDirectoryEntry* psFatEntry, bool bFat32Volume);
const char* FatAttributeToString(uint8 uiAttribute);
enum EFatSeek
{
FAT_SEEK_START = 0x1,
FAT_SEEK_CURRENT = 0x2,
FAT_SEEK_END = 0x3
};
enum EFatCode
{
FAT_SUCCESS = 0x0,
FAT_UNKNOWN_ERROR = 0x20 + 0x1,
FAT_CANNOT_READ_MEDIA = 0x20 + 0x2,
FAT_CANNOT_WRITE_MEDIA = 0x20 + 0x3,
FAT_NOT_A_DIRECTORY = 0x20 + 0x4,
FAT_INVALID_FILENAME = 0x20 + 0x5,
FAT_FILENAME_ALREADY_EXISTS = 0x20 + 0x6,
FAT_INVALID_PATH = 0x20 + 0x7,
FAT_CORRUPTED_FILE = 0x20 + 0x8,
FAT_ILLEGAL_FILENAME = 0x20 + 0x9,
FAT_FILENAME_TOO_LONG = 0x20 + 0xA,
FAT_NOT_A_FILE = 0x20 + 0xB,
FAT_FILE_NOT_FOUND = 0x20 + 0xC,
FAT_DIRECTORY_DOES_NOT_EXIST = 0x20 + 0xD,
FAT_INSUFFICIENT_DISK_SPACE = 0x20 + 0xE,
FAT_FEATURE_NOT_SUPPORTED = 0x20 + 0xF,
FAT_OP_IN_PROGRESS = 0x20 + 0x10,
FAT_SECTOR_SIZE_NOT_SUPPORTED = 0x20 + 0x11,
FAT_LFN_GENERATED = 0x20 + 0x12,
FAT_SHORT_LFN_GENERATED = 0x20 + 0x13,
FAT_SEEK_FAILED = 0x20 + 0x14,
FAT_FILE_NOT_OPENED_FOR_WRITE_ACCESS= 0x20 + 0x15,
FAT_INVALID_HANDLE = 0x20 + 0x16,
FAT_INVALID_CLUSTER = 0x20 + 0x17,
FAT_INVALID_FAT_VOLUME = 0x20 + 0x18,
FAT_INVALID_VOLUME_LABEL = 0x20 + 0x19,
FAT_INVALID_FORMAT_PARAMETERS = 0x20 + 0x1A,
FAT_ROOT_DIRECTORY_LIMIT_EXCEEDED = 0x20 + 0x1B,
FAT_DIRECTORY_LIMIT_EXCEEDED = 0x20 + 0x1C,
FAT_INVALID_PARAMETERS = 0x20 + 0x1D,
FAT_FILE_HANDLE_IN_USE = 0x20 + 0x1E,
FAT_INVALID_FAT_CACHE = 0x20 + 0x1F,
FAT_NO_CACHE_LOCK = 0x20 + 0x20,
FAT_SHORT_NAME_FOUND = 0x20 + 0x21,
FAT_NOT_ALL_CLUSTERS_ALLOCATED = 0x20 + 0x22,
FAT_LAST_ERROR_ENUM = FAT_SHORT_NAME_FOUND
};
char* FatCodeToString(EFatCode eCode);
struct SFatQueryState
{
uint8 uiAttributes;
uint16 uiCurrentSector;
uint32 uiCurrentCluster;
SFatRawDirectoryEntry* psCurrentEntryRaw;
SFatRawDirectoryEntry* psFirstEntryRaw;
uint16 auiLongFilename[255 + 1];
uint8 uiSequence;
uint8 uiChecksum;
SFatCache sBuffer;
uint32 uiLockedSectors[32];
void Init(void);
bool Kill(CFatInfoSectorCache* pcCache);
bool Lock(uint32 uiSector);
};
struct SFatFileSystemQuery
{
SFatDirectoryEntry sCurrentEntry;
SFatQueryState sQuery;
void Init(void);
void Kill(CFatInfoSectorCache* pcCache);
};
enum EFatFileSystemType
{
FAT_FS_TYPE_UNSPECIFIED,
FAT_FS_TYPE_FAT12,
FAT_FS_TYPE_FAT16,
FAT_FS_TYPE_FAT32
};
static const char ILLEGAL_CHARS[] = { 0x22, 0x2A, 0x2B, 0x2C, 0x2E, 0x2F, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x5B, 0x5C, 0x5D, 0x7C };
EFatCode GetFatLongNameForEntry(uint16* puiDest, char* szSource);
bool CompareFatShortName(char* szName1, char* szName2);
int CompareFatLongName(uint16* puiName1, uint16* puiName2);
EFatCode GetFatShortNameForEntry(char* szDest, const char* szSource, bool bLFNDisabled);
void ConvertFATShortInternalNameInto8Dot3Format(uint8* puiDest, const uint8* puiSource);
EFatCode MatchesFatFileName(bool* pbMatch, bool* pbUsingLFN, char* szConstructedShortFileName, uint16* puiTargetFileLongName, char* szCurrentLevelPath, uint16* auiLongFilename, uint8* auiShortName);
void ConstructFatLongFileNameFromShortName(uint16* auiLongFilename, char* szShortName, bool bLowercaseBase, bool bLowercaseExtension);
const char* StepPathOverSlash(const char* szPathName);
const char* StepPathToSlash(const char* szPathName);
void CopyLongFilenameIntoString(char* szDestination, uint16* auiSource);
bool IsIllegalFilenameCharacter(char c);
bool IsIllegalFilename(const char* szName, uint16 uiLength);
void GenerateShortNameWithSuffix(uint16 uiNameSuffix, uint8* szShortName);
void ParsePathAndFilename(const char* szPath, char* szPathPart, const char** pszFilenamePart);
class CFatVolume
{
protected:
uint32 muiID;
uint32 muiFatSize;
uint32 muiRootCluster;
uint32 muiRootSector;
uint32 muiFirstDataSector;
uint32 muiHiddenSectors;
uint32 muiNoOfSectors;
uint32 muiNoOfDataSectors;
uint32 muiNoOfClusters;
uint32 muiNoOfReservedSectors;
uint32 muiNextFreeCluster;
uint32 muiTotalFreeClusters;
uint32 muiFileSystemInfoSector;
uint32 muiBytesPerCluster;
uint16 muiRootDirectorySectors;
uint16 muiBytesPerSector;
uint16 muiNoOfSectorsPerCluster;
bool mbUseLongFilenames;
EFatFileSystemType meFileSystem;
uint8 muiNoOfFatTables;
CChars mszLabel;
CFileDrive* mpcDevice;
CFatInfoSectorCache mcSectorCache;
SFatBIOSParameterBlock msBPB;
public:
EFatCode Mount(CFileDrive* pcDevice);
EFatCode Unmount(void);
EFatCode Flush(void);
bool Erase(uint32 uiStartSector, uint32 uiStopSectorInclusive);
EFatCode CreateDirectory(const char* szDirectory);
EFatCode Rename(const char* szOriginalFilename, const char* szNewFilename);
EFatCode Delete(const char* szFilename);
EFatCode AllocateClusters(uint32 uiClustersNeeded, uint32 uiCursorClusterInVolume, uint32* puiNewClusterInVolume, uint32 uiPreviousCluster);
EFatCode FreeDirectoryEntry(SFatDirectoryEntry* psEntry);
SFatCache ReadSector(uint32 uiFatInfoSector, bool bLock = false);
void DirtySector(SFatCache sCachedSector);
void CalculateFATIndexAndOffset(uint32* puiOffsetInSector, uint32 uiClusterIndex, uint32* puiSector);
EFatCode GetFileEntry(const char* szPath, SFatDirectoryEntry* psEntry);
uint32 CalculateFirstSectorOfCluster(uint32 uiCluster);
EFatCode GetNextClusterEntry(uint32 uiCurrentCluster, fatEntry* puiNextCluster);
EFatCode SeekByClusterCount(uint32 uiClusterIndex, uint16 uiClusterCount, uint32* puiNewClusterIndex);
bool FatIsEOFEntry(fatEntry uiFat);
EFatCode FreeChain(uint32 uiClusterIndex);
EFatCode SetClusterEntry(uint32 uiClusterIndex, fatEntry uiClusterInVolume);
EFatCode ReadFatEntry(uint32 uiOffsetInSector, uint32 uiClusterIndex, uint32 uiFat12Sector, fatEntry* puiFatEntry);
EFatCode UpdateDirectoryEntry(SFatDirectoryEntry* psEntry, uint32 uiFirstCluster, uint32 uiNewClusterInVolume, uint32 uiClustersInFile);
EFatCode FindFirstFATEntry(const char* szParentPath, uint8 uiAttributes, SFatDirectoryEntry** ppsDirectoryEntry, SFatFileSystemQuery* psQuery);
EFatCode FindNextFATEntry(SFatDirectoryEntry** ppsDirectoryEntry, SFatFileSystemQuery* psQuery);
EFatCode CreateFATEntry(SFatRawDirectoryEntry* psParentDirectory, const char* szName, uint8 uiAttributes, uint32 uiEntryCluster, SFatDirectoryEntry* psNewEntry);
fatEntry GetEndOfClusterMarker(void);
fatEntry GetBadClusterMarker(void);
fatEntry GetClusterEntryMask(void);
uint32 GetEntryCluster(SFatRawDirectoryEntry* psEntry);
EFatCode ValidateFatCache(SFatCache sCache);
void FillDirectoryEntryFromRawEntry(SFatDirectoryEntry* psEntry, SFatRawDirectoryEntry* psRawEntry);
uint32 GetClusterSize(void);
uint32 GetID(void);
uint32 GetFatSize(void);
uint32 GetFirstDataSector(void);
uint32 GetNoOfSectors(void);
uint32 GetNoOfDataSectors(void);
uint32 GetNumClusters(void);
uint32 GetNoOfReservedSectors(void);
uint32 GetNextFreeCluster(void);
uint32 GetTotalFreeClusters(void);
uint32 GetFileSystemInfoSector(void);
uint16 GetRootDirectorySectors(void);
uint16 GetSectorSize(void);
uint16 NumSectorsPerCluster(void);
bool IsUseLongFilenames(void);
EFatFileSystemType GetFileSystemType(void);
uint8 GetNoOfFatTables(void);
char* GetLabel(void);
CFileDrive* GetFileDrive(void);
uint32 GetRootCluster(void);
uint32 GetRootSector(void);
uint32 GetPageSize(void);
CFatInfoSectorCache* GetSectorCache(void);
protected:
EFatCode InitialiseFat32FileSystemInfo(void);
bool InitialiseVolumeParametersFromBPB(uint8* puiPartitionsTried, SFatBIOSParameterBlock* psBPB, uint32 uiHiddenSectors);
EFatCode QueryFirstEntry(SFatRawDirectoryEntry* directory, uint8 attributes, SFatQueryState* query, bool bBufferLocked);
EFatCode QueryNextEntry(SFatQueryState* psQuery, bool bBufferLocked, bool bFirstEntry);
uint32 AllocateDirectoryCluster(SFatRawDirectoryEntry* parent, EFatCode* peResult);
uint32 AllocateDataCluster(uint32 uiClusterCount, bool bEraseCluster, EFatCode* peResult, uint32 uiPreviousCluster);
uint32 AllocateDataClusterEx(uint32 uiClusterCount, bool bEraseCluster, uint32 uiPageSize, EFatCode* peResult, uint32 uiPreviousCluster);
uint32 AllocateClusters(SFatRawDirectoryEntry* psParentDirectory, uint32 uiClusterCount, bool bEraseCluster, uint32 uiPageSize, EFatCode* peResult, uint32 uiPreviousCluster);
EFatCode FreeFat12Chain(bool* pbFat12MultiStepProgress, uint32* puiFreedClusterIndex, uint32* puiSector, uint32* puiOffsetInSector);
EFatCode FreeFat16Chain(uint32* puiFreedClusterIndex, uint32 uiSector, uint32 uiOffsetInSector);
EFatCode FreeFat32Chain(uint32* puiFreedClusterIndex, uint32 uiSector, uint32 uiOffsetInSector);
uint32 CalculateFATEntryIndex(uint32 uiClusterIndexInFAT);
uint8 FatLongEntryChecksum(char* szFilename);
uint32 CalculateRootSector(void);
EFatCode SetFat12ClusterEntry(uint32 uiClusterIndex, fatEntry uiClusterInVolume, uint32 uiFirstClusterSector, uint16 uiOffsetInSector);
EFatCode SetFat16ClusterEntry(fatEntry uiClusterInVolume, uint32 uiFirstClusterSector, uint16 uiOffsetInSector);
EFatCode SetFat32ClusterEntry(fatEntry uiClusterInVolume, uint32 uiFirstClusterSector, uint16 uiOffsetInSector);
EFatCode IncreaseFat12ClusterAddress(uint32* puiClusterIndex, uint32* puiSector, uint32* puiOffsetInSector, bool* pbFat12OddClusterBeingProcessed, bool* pbFat12MultiStepProgress);
EFatCode IncreaseFat16ClusterAddress(uint32* puiClusterIndex, uint32 uiSector, uint32 uiOffsetInSector);
EFatCode IncreaseFat32ClusterAddress(uint32* puiClusterIndex, uint32 uiSector, uint32 uiOffsetInSector);
EFatCode ReadFat12Entry(uint32 uiOffsetInSector, uint32 uiCluster, uint32 uiSector, fatEntry* puiFatEntry);
EFatCode ReadFat16Entry(uint32 uiOffsetInSector, uint32 uiSector, fatEntry* puiFatEntry);
EFatCode ReadFat32Entry(uint32 uiOffsetInSector, uint32 uiSector, fatEntry* puiFatEntry);
EFatCode WriteFat12Entry(uint32 uiOffsetInSector, uint32 uiPreviousOffset, uint32 uiCluster, uint32 uiSector, uint32 uiPreviousSector, fatEntry uiPreviousFatEntry);
EFatCode WriteFat16Entry(uint32 uiOffsetInSector, uint32 uiPreviousOffset, uint32 uiCluster, uint32 uiSector, uint32 uiPreviousSector, fatEntry uiPreviousFatEntry);
EFatCode WriteFat32Entry(uint32 uiOffsetInSector, uint32 uiPreviousEntryOffset, uint32 uiClusterIndexInTable, uint32 uiSector, uint32 uiPreviousSector, fatEntry uiPreviousFatEntry);
EFatCode WriteAllocatedFatEntry(uint32 uiClusterIndexInTable, uint32 uiOffsetInSector, uint32 uiSector, fatEntry uiPreviousFatEntry, uint32 uiPreviousSector, uint32 uiPreviousEntryOffset);
void SetNextFreeCluster(uint32 uiCluster);
void SetTotalFreeClusters(uint32 uiTotalFreeClusters);
uint32 FindNextPageCluster(uint32 uiPageSize, uint32 uiCluster, uint16 uiStep);
bool HasNextFreeCluser(void);
uint16 CalculateClusterStepSize(uint32 uiPageSize);
EFatCode WrapAllocate(uint32 uiStartCluster, uint32 uiLastFatEntry, bool* pbWrappedAround, uint32* puiClusterIndex, uint32* puiOffsetInSector, uint32* puiFirstClusterSector);
EFatCode InitialiseAllocatedFatCluster(SFatRawDirectoryEntry* psParentDirectory, uint32 uiCluster, bool bZero);
EFatCode EraseClusterContents(uint32 uiCluster);
EFatCode InitializeDirectoryCluster(SFatRawDirectoryEntry* psDirectoryParent, uint32 uiCluster);
void InitialiseDottyDirectoryEntry(SFatRawDirectoryEntry* psEntries, const char* sz, uint32 uiCluster);
bool IsFreeFat(fatEntry uifat);
EFatCode CreateFakeRootEntry(SFatDirectoryEntry* psEntry);
fatEntry GetDirectoryCluster(SFatRawDirectoryEntry* psParentDirectory);
uint32 GetDirectorySector(SFatRawDirectoryEntry* psParentDirectory);
EFatCode FindEnoughEntries(fatEntry* puiLastDirectoryCluster, fatEntry* puiDirectoryCluster, uint32* puiFirstSectorOfCluster, uint32* puiSector, int* piLFNEntriesFound, SFatRawDirectoryEntry** ppsParentEntry, SFatRawDirectoryEntry* psParentDirectory, int iLFNEntriesNeeded);
EFatCode RewindFoundEntries(SFatRawDirectoryEntry** ppsParentEntry, uint32* puiFirstSectorOfCluster, fatEntry* puiDirectoryCluster, int iLFNEntriesFound, fatEntry uiLastDirectoryCluster, uint32 uiSector);
EFatCode FindBiosParameterBlock(SFatCache sMBRSector);
bool CheckSectorsPerClusterIsPowerOfTwo(uint8 uiSectorsPerCluster);
bool CheckFileAllocationTableLargeEnough(EFatFileSystemType eFileSystem, uint32 uiFatSize, uint32 uiNoOfClusters, uint16 uiBytesPerSector);
EFatCode GenerateUniqueShortNameWithSuffix(SFatRawDirectoryEntry* psParentDirectory, uint8* szShortName);
void InitialiseNewEntry(SFatDirectoryEntry* psNewEntry, const char* szName, uint8 uiAttributes, uint32 uiEntryCluster);
void InitialiseParentEntry(SFatRawDirectoryEntry* psParentEntry, const char* szName, char uiChecksum, int iLFNEntriesNeeded, int iLFNEntriesFound);
void SetQueryLongFilenamePart(SFatQueryState* psQuery, int8 iLongOffset, uint8* puiChars, int8 iRawOffset);
void SetQueryLongFilenamePart(SFatQueryState* psQuery);
EFatCode FindNextRawDirectoryEntry(SFatQueryState* psQuery);
uint16 LongNameCharToWideChar(uint16 uiLFNIndex, uint16 uiNameLength, const char* szName, uint16 uiNameIndex);
void GenerateDirectoryEntryNameParts(uint8* aui, uint16 uiLFNIndex, uint16 uiNameLength, const char* szName, uint16 uiNameIndex);
EFatCode InitialiseVolumeLabel(void);
EFatCode FindNextRawDirectoryEntrySectorInCluster(uint32* puiSector, SFatQueryState* psQuery);
EFatCode FindNextRawDirectoryEntryCluster(uint32* puiSector, SFatQueryState* psQuery);
bool IsFreeDirectoryEntry(SFatRawDirectoryEntry* psEntry);
bool IsLastDirectoryEntry(SFatRawDirectoryEntry* psEntry);
void ProcessQueryLongFileNameEntry(SFatQueryState* psQuery);
void ConstructQueryLongFileNameFromShortName(SFatQueryState* psQuery);
EFatCode EraseClusterChainContents(fatEntry uiCluster);
uint32 GetRootDirectorySector(void);
bool HasNoMoreEntries(SFatFileSystemQuery* psQuery);
EFatCode TerminalQueryEntry(SFatFileSystemQuery* psQuery);
uint32 CalculateQuerySector(SFatFileSystemQuery* psQuery);
uint32 CalculateQuerySectorOffset(SFatFileSystemQuery* psQuery);
EFatCode CheckEntryName(const char* szName);
EFatCode WriteFATEntry(SFatDirectoryEntry* psNewEntry, const char* szName, SFatRawDirectoryEntry* psParentDirectory, int iLFNEntriesNeeded);
bool IsRootDirectoryCluster(uint32 uiDirectoryCluster);
EFatCode IncrementDirectorySector(uint32* puiSector, uint32 uiFirstSectorOfCluster, fatEntry uiDirectoryCluster);
EFatCode IncrementOrAllocateDirectoryCluster(uint32* puiSector, fatEntry* puiDirectoryCluster, fatEntry uiLastDirectoryCluster);
EFatCode CreateDirectory(const char* szDirectory, SFatDirectoryEntry* psEntry);
EFatCode Delete(SFatDirectoryEntry* psEntry, const char* szNamePart, char* szPathPart, uint8 uiChecksum);
void CopyRawEntry(SFatDirectoryEntry* psOriginalEntry, SFatDirectoryEntry* psNewEntry);
EFatCode Rename(const char* szOriginalParent, uint8 uiChecksum);
};
int ComparePtr(const void* arg1, const void* arg2);
int ComparePtrPtr(const void* arg1, const void* arg2);
bool CFatVolume::CheckFileAllocationTableLargeEnough(EFatFileSystemType eFileSystem, uint32 uiFatSize, uint32 uiNoOfClusters, uint16 uiBytesPerSector)
{
switch (eFileSystem)
{
case FAT_FS_TYPE_FAT12:
{
if (uiFatSize < (((uiNoOfClusters + (uiNoOfClusters >> 1)) + uiBytesPerSector - 1) / uiBytesPerSector))
{
return false;
}
break;
}
case FAT_FS_TYPE_FAT16:
{
if (uiFatSize < (((uiNoOfClusters * 2) + uiBytesPerSector - 1) / uiBytesPerSector))
{
return false;
}
break;
}
case FAT_FS_TYPE_FAT32:
{
if (uiFatSize < (((uiNoOfClusters * 4) + uiBytesPerSector - 1) / uiBytesPerSector))
{
return false;
}
break;
}
default:
break;
}
return true;
}
bool CFatVolume::CheckSectorsPerClusterIsPowerOfTwo(uint8 uiSectorsPerCluster)
{
while (uiSectorsPerCluster != 1)
{
if (uiSectorsPerCluster & 1)
{
return false;
}
uiSectorsPerCluster >>= 1;
}
return true;
}
bool CFatVolume::InitialiseVolumeParametersFromBPB(uint8* puiPartitionsTried, SFatBIOSParameterBlock* psBPB, uint32 uiHiddenSectors)
{
muiRootDirectorySectors = ((psBPB->uiRootEntryCount * 32) + (psBPB->uiBytsPerSector - 1)) / psBPB->uiBytsPerSector;
muiFatSize = (psBPB->uiFATSzFat16) ? psBPB->uiFATSzFat16 : psBPB->uFatEx.sFat32.uiFATSzFat32;
muiNoOfSectors = (psBPB->uiTotalSectorsFat16) ? psBPB->uiTotalSectorsFat16 : psBPB->uiTotalSectorsFat32;
muiNoOfDataSectors = muiNoOfSectors - (psBPB->uiReservedSectorCount + (psBPB->uiNumFileAllocationTables * muiFatSize) + muiRootDirectorySectors);
muiNoOfClusters = muiNoOfDataSectors / psBPB->uiSectorsPerCluster;
muiBytesPerSector = psBPB->uiBytsPerSector;
meFileSystem = (muiNoOfClusters < 4085) ? FAT_FS_TYPE_FAT12 : (muiNoOfClusters < 65525) ? FAT_FS_TYPE_FAT16 : FAT_FS_TYPE_FAT32;
if (!CheckFileAllocationTableLargeEnough(meFileSystem, muiFatSize, muiNoOfClusters, muiBytesPerSector))
{
(*puiPartitionsTried)++;
return false;
}
muiHiddenSectors = uiHiddenSectors;
muiFirstDataSector = psBPB->uiReservedSectorCount + muiHiddenSectors + (psBPB->uiNumFileAllocationTables * muiFatSize) + muiRootDirectorySectors;
muiNoOfReservedSectors = psBPB->uiReservedSectorCount + muiHiddenSectors;
muiNoOfSectorsPerCluster = psBPB->uiSectorsPerCluster;
muiNoOfFatTables = psBPB->uiNumFileAllocationTables;
muiFileSystemInfoSector = psBPB->uFatEx.sFat32.uiFileSystemInformation;
muiBytesPerCluster = muiBytesPerSector * muiNoOfSectorsPerCluster;
if (meFileSystem == FAT_FS_TYPE_FAT16)
{
muiID = psBPB->uFatEx.sFat16.uiVolumeID;
mszLabel.Kill();
mszLabel.Init(psBPB->uFatEx.sFat16.szVolumeLabel, 0, 10);
mszLabel.StripWhitespace();
}
else if (meFileSystem == FAT_FS_TYPE_FAT32)
{
muiID = psBPB->uFatEx.sFat32.uiVolumeID;
mszLabel.Kill();
mszLabel.Init(psBPB->uFatEx.sFat32.szVolumeLabel, 0, 10);
mszLabel.StripWhitespace();
}
if (meFileSystem == FAT_FS_TYPE_FAT32)
{
muiRootCluster = psBPB->uFatEx.sFat32.uiRootCluster;
}
else
{
muiRootCluster = 0;
}
muiRootSector = CalculateRootSector();
return true;
}
EFatCode CFatVolume::FindBiosParameterBlock(SFatCache sMBRSector)
{
uint32 uiHiddenSectors;
SFatPartitionEntry* psPartitionEntry;
uint8 uiPartitionsTried;
EFatCode eResult;
bool bContinue;
SFatCache sLBASector;
uint32 uiFATSector;
SFatCache sFATSector;
eResult = ValidateFatCache(sMBRSector);
if (eResult != FAT_SUCCESS) { return eResult; };
uiHiddenSectors = 0;
memcpy(&msBPB, sMBRSector.Get(), sizeof(SFatBIOSParameterBlock));
uiPartitionsTried = 0;
psPartitionEntry = (SFatPartitionEntry*)(sMBRSector.Get() + 0x1BE);
for (;;)
{
eResult = ValidateFatCache(sMBRSector);
if (eResult != FAT_SUCCESS) { return eResult; };
if (uiPartitionsTried > 0)
{
if (uiPartitionsTried > 4)
{
return FAT_INVALID_FAT_VOLUME;
}
if (uiPartitionsTried > 1)
{
psPartitionEntry++;
}
uiHiddenSectors = psPartitionEntry->uiLBAFirstSector;
if (psPartitionEntry->uiLBAFirstSector + psPartitionEntry->uiTotalSectors > mpcDevice->GetTotalSectors())
{
uiPartitionsTried++;
continue;
}
sLBASector = mcSectorCache.ReadSector(psPartitionEntry->uiLBAFirstSector); if (!sLBASector.IsValid()) { return FAT_CANNOT_READ_MEDIA; };
memcpy(&msBPB, sLBASector.pvCachedSector, sizeof(SFatBIOSParameterBlock));
}
if (msBPB.uiBytsPerSector > 0x200)
{
return FAT_SECTOR_SIZE_NOT_SUPPORTED;
}
if (!msBPB.uiBytsPerSector || !msBPB.uiSectorsPerCluster)
{
uiPartitionsTried++;
continue;
}
if (!CheckSectorsPerClusterIsPowerOfTwo(msBPB.uiSectorsPerCluster))
{
uiPartitionsTried++;
continue;
}
bContinue = !InitialiseVolumeParametersFromBPB(&uiPartitionsTried, &msBPB, uiHiddenSectors);
if (bContinue)
{
continue;
}
uiFATSector = muiNoOfReservedSectors;
sFATSector = mcSectorCache.ReadSector(uiFATSector); if (!sFATSector.IsValid()) { return FAT_CANNOT_READ_MEDIA; };
if (sFATSector.Get()[0] != msBPB.uiMediaType)
{
uiPartitionsTried++;
continue;
}
return FAT_SUCCESS;
}
}
EFatCode CFatVolume::InitialiseVolumeLabel(void)
{
EFatCode eResult;
SFatQueryState sQuery;
sQuery.Init();
eResult = QueryFirstEntry(0, 0x8, &sQuery, 1);
if (eResult == FAT_SUCCESS)
{
if (sQuery.psCurrentEntryRaw->uEntry.sFatRawCommon.szShortName[0] != '\0')
{
if (sQuery.psCurrentEntryRaw->uEntry.sFatRawCommon.uiAttributes == 0x8)
{
mszLabel.Kill();
mszLabel.Init((char*)sQuery.psCurrentEntryRaw->uEntry.sFatRawCommon.szShortName, 0, 10);
mszLabel.StripWhitespace();
}
}
}
sQuery.Kill(GetSectorCache());
return eResult;
}
EFatCode CFatVolume::Mount(CFileDrive* pcDevice)
{
SFatCache sMBRSector;
EFatCode eResult;
mcSectorCache.Init(pcDevice, 3);
mszLabel.Init();
mpcDevice = pcDevice;
sMBRSector = mcSectorCache.ReadSector(0); if (!sMBRSector.IsValid()) { return FAT_CANNOT_READ_MEDIA; };
eResult = FindBiosParameterBlock(sMBRSector);
if (eResult != FAT_SUCCESS)
{
return eResult;
}
eResult = InitialiseVolumeLabel();
if (eResult != FAT_SUCCESS) { return eResult; };
if ((meFileSystem == FAT_FS_TYPE_FAT32) && (muiFileSystemInfoSector > 0) && (muiFileSystemInfoSector != 0xFFFFFFFF))
{
eResult = InitialiseFat32FileSystemInfo();
if (eResult != FAT_SUCCESS) { return eResult; };
}
return FAT_SUCCESS;
}
EFatCode CFatVolume::Unmount(void)
{
SFatFileSystemInfo* psFileSystemInfo;
EFatCode eResult;
SFatCache sBuffer;
bool bResult;
if (meFileSystem == FAT_FS_TYPE_FAT32 && muiFileSystemInfoSector != 0xFFFFFFFF)
{
sBuffer = mcSectorCache.ReadSector(muiFileSystemInfoSector); if (!sBuffer.IsValid()) { return FAT_CANNOT_READ_MEDIA; };
psFileSystemInfo = (SFatFileSystemInfo*)sBuffer.Get();
psFileSystemInfo->uiNextFreeCluster = GetNextFreeCluster();
psFileSystemInfo->uiNumFreeClusters = GetTotalFreeClusters();
psFileSystemInfo->uiLeadSignature = 0x41615252;
psFileSystemInfo->uiStructSignature = 0x61417272;
psFileSystemInfo->uiTrailSignature = 0xAA550000;
DirtySector(sBuffer);
eResult = Flush();
if (eResult != FAT_SUCCESS) { return eResult; };
}
mszLabel.Kill();
bResult = mcSectorCache.Kill();
if (bResult)
{
return FAT_SUCCESS;
}
else
{
return FAT_NO_CACHE_LOCK;
}
}
EFatCode CFatVolume::InitialiseFat32FileSystemInfo(void)
{
SFatFileSystemInfo* psFileSystemInfo;
SFatCache sInfoSector;
muiFileSystemInfoSector = muiHiddenSectors + muiFileSystemInfoSector;
sInfoSector = mcSectorCache.ReadSector(muiFileSystemInfoSector); if (!sInfoSector.IsValid()) { return FAT_CANNOT_READ_MEDIA; };
psFileSystemInfo = (SFatFileSystemInfo*)sInfoSector.Get();
if (psFileSystemInfo->uiLeadSignature == 0x41615252 && psFileSystemInfo->uiStructSignature == 0x61417272 && psFileSystemInfo->uiTrailSignature == 0xAA550000)
{
muiNextFreeCluster = psFileSystemInfo->uiNextFreeCluster;
if (psFileSystemInfo->uiNumFreeClusters < muiNoOfClusters)
{
muiTotalFreeClusters = psFileSystemInfo->uiNumFreeClusters;
}
else
{
muiTotalFreeClusters = muiNoOfClusters - 1;
}
}
else
{
muiNextFreeCluster = 0xFFFFFFFF;
muiTotalFreeClusters = muiNoOfClusters - 1;
}
return FAT_SUCCESS;
}
EFatCode CFatVolume::Flush(void)
{
bool bSuccess;
bSuccess = mcSectorCache.Flush();
if (!bSuccess)
{
return FAT_CANNOT_WRITE_MEDIA;
}
else
{
return FAT_SUCCESS;
}
}
bool CFatVolume::Erase(uint32 uiStartSector, uint32 uiStopSectorInclusive)
{
return mpcDevice->Erase(uiStartSector, uiStopSectorInclusive);
}
EFatCode CFatVolume::QueryFirstEntry(SFatRawDirectoryEntry* psDirectoryEntry, uint8 attributes, SFatQueryState* psQuery, bool bBufferLocked)
{
uint32 uiFirstSector;
EFatCode eResult;
psQuery->auiLongFilename[0] = 0;
if ((psDirectoryEntry == 0L) ||
(psDirectoryEntry->uEntry.sFatRawCommon.uiFirstClusterHighWord == 0 && psDirectoryEntry->uEntry.sFatRawCommon.uiFirstClusterLowWord == 0))
{
psQuery->uiCurrentCluster = GetRootCluster();
uiFirstSector = GetRootSector();
}
else
{
if (!(psDirectoryEntry->uEntry.sFatRawCommon.uiAttributes & 0x10))
{
return FAT_NOT_A_DIRECTORY;
}
psQuery->uiCurrentCluster = GetFirstClusterFromFatEntry(psDirectoryEntry, meFileSystem == FAT_FS_TYPE_FAT32);
uiFirstSector = CalculateFirstSectorOfCluster(psQuery->uiCurrentCluster);
}
psQuery->sBuffer = ReadSector(uiFirstSector, true);
if (!psQuery->sBuffer.IsValid())
{
return FAT_CANNOT_READ_MEDIA;
}
if (!psQuery->Lock(uiFirstSector))
{
return FAT_NO_CACHE_LOCK;
}
psQuery->psFirstEntryRaw = (SFatRawDirectoryEntry*)psQuery->sBuffer.Get();
psQuery->psCurrentEntryRaw = (SFatRawDirectoryEntry*)psQuery->sBuffer.Get();
psQuery->uiAttributes = attributes;
psQuery->uiCurrentSector = 0;
eResult = QueryNextEntry(psQuery, bBufferLocked, true);
return eResult;
}
void CFatVolume::SetQueryLongFilenamePart(SFatQueryState* psQuery, int8 iLongOffset, uint8* puiChars, int8 iRawOffset)
{
((uint8*)&psQuery->auiLongFilename[((psQuery->uiSequence - 1) * 13) + iLongOffset])[0] = puiChars[iRawOffset + 0];
((uint8*)&psQuery->auiLongFilename[((psQuery->uiSequence - 1) * 13) + iLongOffset])[1] = puiChars[iRawOffset + 1];
}
void CFatVolume::SetQueryLongFilenamePart(SFatQueryState* psQuery)
{
SetQueryLongFilenamePart(psQuery, 0, psQuery->psCurrentEntryRaw->uEntry.sFatRawLongFileName.auiChars1, 0);
SetQueryLongFilenamePart(psQuery, 1, psQuery->psCurrentEntryRaw->uEntry.sFatRawLongFileName.auiChars1, 2);
SetQueryLongFilenamePart(psQuery, 2, psQuery->psCurrentEntryRaw->uEntry.sFatRawLongFileName.auiChars1, 4);
SetQueryLongFilenamePart(psQuery, 3, psQuery->psCurrentEntryRaw->uEntry.sFatRawLongFileName.auiChars1, 6);
SetQueryLongFilenamePart(psQuery, 4, psQuery->psCurrentEntryRaw->uEntry.sFatRawLongFileName.auiChars1, 8);
SetQueryLongFilenamePart(psQuery, 5, psQuery->psCurrentEntryRaw->uEntry.sFatRawLongFileName.auiChars2, 0);
SetQueryLongFilenamePart(psQuery, 6, psQuery->psCurrentEntryRaw->uEntry.sFatRawLongFileName.auiChars2, 2);
SetQueryLongFilenamePart(psQuery, 7, psQuery->psCurrentEntryRaw->uEntry.sFatRawLongFileName.auiChars2, 4);
SetQueryLongFilenamePart(psQuery, 8, psQuery->psCurrentEntryRaw->uEntry.sFatRawLongFileName.auiChars2, 6);
if (psQuery->uiSequence < 20)
{
SetQueryLongFilenamePart(psQuery, 9, psQuery->psCurrentEntryRaw->uEntry.sFatRawLongFileName.auiChars2, 8);
SetQueryLongFilenamePart(psQuery, 10, psQuery->psCurrentEntryRaw->uEntry.sFatRawLongFileName.auiChars2, 10);
SetQueryLongFilenamePart(psQuery, 11, psQuery->psCurrentEntryRaw->uEntry.sFatRawLongFileName.auiChars3, 0);
SetQueryLongFilenamePart(psQuery, 12, psQuery->psCurrentEntryRaw->uEntry.sFatRawLongFileName.auiChars3, 2);
}
}
EFatCode CFatVolume::FindNextRawDirectoryEntrySectorInCluster(uint32* puiSector, SFatQueryState* psQuery)
{
fatEntry uiFat;
EFatCode eResult;
eResult = GetNextClusterEntry(psQuery->uiCurrentCluster, &uiFat);
if (eResult != FAT_SUCCESS) { return eResult; };
if (FatIsEOFEntry(uiFat))
{
psQuery->psCurrentEntryRaw->uEntry.sFatRawCommon.szShortName[0] = '\0';
return FAT_SHORT_NAME_FOUND;
}
psQuery->uiCurrentCluster = uiFat;
psQuery->uiCurrentSector = 0;
*puiSector = CalculateFirstSectorOfCluster(psQuery->uiCurrentCluster) + psQuery->uiCurrentSector;
return FAT_SUCCESS;
}
bool CFatVolume::IsRootDirectoryCluster(uint32 uiDirectoryCluster)
{
return uiDirectoryCluster == 0;
}
EFatCode CFatVolume::FindNextRawDirectoryEntryCluster(uint32* puiSector, SFatQueryState* psQuery)
{
psQuery->uiCurrentSector++;
if (IsRootDirectoryCluster(psQuery->uiCurrentCluster))
{
if (psQuery->uiCurrentSector == GetRootDirectorySectors())
{
psQuery->psCurrentEntryRaw->uEntry.sFatRawCommon.szShortName[0] = '\0';
return FAT_SHORT_NAME_FOUND;
}
*puiSector = GetRootDirectorySector() + psQuery->uiCurrentSector;
}
else
{
*puiSector = CalculateFirstSectorOfCluster(psQuery->uiCurrentCluster) + psQuery->uiCurrentSector;
}
return FAT_SUCCESS;
}
EFatCode CFatVolume::FindNextRawDirectoryEntry(SFatQueryState* psQuery)
{
uint32 uiSector;
EFatCode eResult;
eResult = ValidateFatCache(psQuery->sBuffer);
if (eResult != FAT_SUCCESS) { return eResult; };
if (((uintptr_t)psQuery->psCurrentEntryRaw - (uintptr_t)psQuery->psFirstEntryRaw) == (uint32)GetSectorSize() - 0x20)
{
if ((psQuery->uiCurrentCluster > 0) && (psQuery->uiCurrentSector == NumSectorsPerCluster() - 1))
{
eResult = FindNextRawDirectoryEntrySectorInCluster(&uiSector, psQuery);
if (eResult != FAT_SUCCESS) { return eResult; };
}
else
{
eResult = FindNextRawDirectoryEntryCluster(&uiSector, psQuery);
if (eResult != FAT_SUCCESS) { return eResult; };
}
eResult = ValidateFatCache(psQuery->sBuffer);
if (eResult != FAT_SUCCESS) { return eResult; };
psQuery->sBuffer = ReadSector(uiSector, true);
if (!psQuery->sBuffer.IsValid())
{
return FAT_CANNOT_READ_MEDIA;
}
if (!psQuery->Lock(uiSector))
{
return FAT_NO_CACHE_LOCK;
}
psQuery->psFirstEntryRaw = (SFatRawDirectoryEntry*)psQuery->sBuffer.Get();
psQuery->psCurrentEntryRaw = (SFatRawDirectoryEntry*)psQuery->sBuffer.Get();
}
else
{
psQuery->psCurrentEntryRaw++;
}
return FAT_SUCCESS;
}
bool CFatVolume::IsFreeDirectoryEntry(SFatRawDirectoryEntry* psEntry)
{
return *psEntry->uEntry.sFatRawCommon.szShortName == 0xE5 || IsLastDirectoryEntry(psEntry);
}
bool CFatVolume::IsLastDirectoryEntry(SFatRawDirectoryEntry* psEntry)
{
return *psEntry->uEntry.sFatRawCommon.szShortName == '\0';
}
void CFatVolume::ProcessQueryLongFileNameEntry(SFatQueryState* psQuery)
{
if (psQuery->psCurrentEntryRaw->uEntry.sFatRawLongFileName.uiSequence & 0x40)
{
psQuery->uiSequence = (psQuery->psCurrentEntryRaw->uEntry.sFatRawLongFileName.uiSequence ^ 0x40) + 1;
psQuery->uiChecksum = psQuery->psCurrentEntryRaw->uEntry.sFatRawLongFileName.uiChecksum;
memset(psQuery->auiLongFilename, 0, sizeof(uint16) * (255 + 1));
}
if (psQuery->uiChecksum == psQuery->psCurrentEntryRaw->uEntry.sFatRawLongFileName.uiChecksum &&
(psQuery->uiSequence == (psQuery->psCurrentEntryRaw->uEntry.sFatRawLongFileName.uiSequence & (0xFF ^ 0x40)) + 1))
{
psQuery->uiSequence = psQuery->psCurrentEntryRaw->uEntry.sFatRawLongFileName.uiSequence & (0xFF ^ 0x40);
SetQueryLongFilenamePart(psQuery);
}
else
{
psQuery->uiChecksum = 0;
}
}
void CFatVolume::ConstructQueryLongFileNameFromShortName(SFatQueryState* psQuery)
{
::ConstructFatLongFileNameFromShortName(psQuery->auiLongFilename, (char*)psQuery->psCurrentEntryRaw->uEntry.sFatRawCommon.szShortName, psQuery->psCurrentEntryRaw->uEntry.sFatRawCommon.uiReserved & 0x08, psQuery->psCurrentEntryRaw->uEntry.sFatRawCommon.uiReserved & 0x10);
}
EFatCode CFatVolume::QueryNextEntry(SFatQueryState* psQuery, bool bBufferLocked, bool bFirstEntry)
{
bool bPass;
EFatCode eResult;
do
{
if (!bFirstEntry)
{
eResult = FindNextRawDirectoryEntry(psQuery);
if (eResult == FAT_SHORT_NAME_FOUND)
{
return FAT_SUCCESS;
}
else if (eResult != FAT_SUCCESS)
{
return eResult;
}
}
else
{
bFirstEntry = false;
}
if (psQuery->psCurrentEntryRaw->uEntry.sFatRawCommon.uiAttributes == (0x1 | 0x2 | 0x4 | 0x8) && !IsFreeDirectoryEntry(psQuery->psCurrentEntryRaw))
{
ProcessQueryLongFileNameEntry(psQuery);
bPass = (psQuery->uiAttributes == (0x1 | 0x2 | 0x4 | 0x8));
}
else
{
bPass =
(!(psQuery->psCurrentEntryRaw->uEntry.sFatRawCommon.uiAttributes & 0x2) || (psQuery->uiAttributes & 0x2)) &&
(!(psQuery->psCurrentEntryRaw->uEntry.sFatRawCommon.uiAttributes & 0x4) || (psQuery->uiAttributes & 0x4)) &&
(!(psQuery->psCurrentEntryRaw->uEntry.sFatRawCommon.uiAttributes & 0x8) || (psQuery->uiAttributes & 0x8)) &&
(!(psQuery->psCurrentEntryRaw->uEntry.sFatRawCommon.uiAttributes & (0x1 | 0x2 | 0x4 | 0x8)) || (psQuery->uiAttributes & (0x1 | 0x2 | 0x4 | 0x8)));
}
}
while (!bPass || psQuery->psCurrentEntryRaw->uEntry.sFatRawCommon.szShortName[0] == 0xE5);
if (psQuery->psCurrentEntryRaw->uEntry.sFatRawCommon.szShortName[0] != '\0')
{
if (psQuery->uiChecksum != FatLongEntryChecksum((char*)psQuery->psCurrentEntryRaw->uEntry.sFatRawCommon.szShortName))
{
psQuery->auiLongFilename[0] = 0;
}
}
if (psQuery->auiLongFilename[0] == 0 && (psQuery->psCurrentEntryRaw->uEntry.sFatRawCommon.uiReserved & (0x10 | 0x08)))
{
ConstructQueryLongFileNameFromShortName(psQuery);
}
return FAT_SUCCESS;
}
EFatCode CFatVolume::GetNextClusterEntry(uint32 uiCurrentCluster, fatEntry* puiNextCluster)
{
uint32 uiFirstClusterSector;
uint32 uiOffsetInSector;
EFatCode eResult;
CalculateFATIndexAndOffset(&uiOffsetInSector, uiCurrentCluster, &uiFirstClusterSector);
eResult = ReadFatEntry(uiOffsetInSector, uiCurrentCluster, uiFirstClusterSector, puiNextCluster);
return eResult;
}
EFatCode CFatVolume::EraseClusterChainContents(fatEntry uiCluster)
{
uint32 uiStartSector;
uint32 uiEndSector;
EFatCode eResult;
bool bSuccess;
while (!FatIsEOFEntry(uiCluster))
{
uiStartSector = CalculateFirstSectorOfCluster(uiCluster);
uiEndSector = uiStartSector + NumSectorsPerCluster();
bSuccess = Erase(uiStartSector, uiEndSector - 1);
if (!bSuccess)
{
return FAT_CANNOT_WRITE_MEDIA;
}
eResult = GetNextClusterEntry(uiCluster, &uiCluster);
if (eResult != FAT_SUCCESS) { return eResult; };
}
return FAT_SUCCESS;
}
EFatCode CFatVolume::AllocateClusters(uint32 uiClustersNeeded, uint32 uiCluster, uint32* puiNewClusterInVolume, uint32 uiPreviousCluster)
{
uint32 uiPageSize;
EFatCode eResult;
uiPageSize = GetPageSize();
if (uiPageSize > NumSectorsPerCluster())
{
uint32 uiClustersPerPage = uiPageSize / NumSectorsPerCluster();
if (uiClustersNeeded % uiClustersPerPage > 0)
{
uiClustersNeeded += uiClustersPerPage - (uiClustersNeeded % uiClustersPerPage);
}
if ((uiClustersNeeded % uiClustersPerPage) != 0)
{
return FAT_UNKNOWN_ERROR;
}
*puiNewClusterInVolume = AllocateDataClusterEx(uiClustersNeeded, false, uiPageSize, &eResult, uiPreviousCluster);
if (eResult != FAT_SUCCESS)
{
return eResult;
}
}
else
{
*puiNewClusterInVolume = AllocateDataCluster(uiClustersNeeded, false, &eResult, uiPreviousCluster);
if (eResult != FAT_SUCCESS)
{
return eResult;
}
}
eResult = EraseClusterChainContents(*puiNewClusterInVolume);
return eResult;
}
uint32 CFatVolume::AllocateDirectoryCluster(SFatRawDirectoryEntry* parent, EFatCode* peResult)
{
return AllocateClusters(parent, 1, true, 1, peResult, GetEndOfClusterMarker());
}
uint32 CFatVolume::AllocateDataCluster(uint32 uiClusterCount, bool bEraseCluster, EFatCode* peResult, uint32 uiPreviousCluster)
{
return AllocateClusters(0L, uiClusterCount, bEraseCluster, 1, peResult, uiPreviousCluster);
}
uint32 CFatVolume::AllocateDataClusterEx(uint32 uiClusterCount, bool bEraseCluster, uint32 uiPageSize, EFatCode* peResult, uint32 uiPreviousCluster)
{
return AllocateClusters(0L, uiClusterCount, bEraseCluster, uiPageSize, peResult, uiPreviousCluster);
}
uint32 CFatVolume::FindNextPageCluster(uint32 uiPageSize, uint32 uiCluster, uint16 uiStep)
{
uint32 uiSector;
uint16 uiStepCount;
if (NumSectorsPerCluster() < uiPageSize)
{
uiStepCount = 0;
uiSector = CalculateFirstSectorOfCluster(uiCluster);
while (uiSector % uiPageSize && uiStepCount < uiStep)
{
uiCluster++;
uiStepCount++;
uiSector = CalculateFirstSectorOfCluster(uiCluster);
}
}
return uiCluster;
}
fatEntry CFatVolume::GetEndOfClusterMarker(void)
{
switch (meFileSystem)
{
case FAT_FS_TYPE_FAT12:
return 0x00000FFF;
case FAT_FS_TYPE_FAT16:
return 0x0000FFFF;
case FAT_FS_TYPE_FAT32:
return 0x0FFFFFFF;
default:
break;
}
return 0;
}
fatEntry CFatVolume::GetBadClusterMarker(void)
{
switch (meFileSystem)
{
case FAT_FS_TYPE_FAT12:
return 0x00000FF7;
case FAT_FS_TYPE_FAT16:
return 0x0000FFF7;
case FAT_FS_TYPE_FAT32:
return 0x0FFFFFF7;
default:
break;
}
return 0;
}
fatEntry CFatVolume::GetClusterEntryMask(void)
{
switch (meFileSystem)
{
case FAT_FS_TYPE_FAT12:
return 0x00000FFF;
case FAT_FS_TYPE_FAT16:
return 0x0000FFFF;
case FAT_FS_TYPE_FAT32:
return 0x0FFFFFFF;
default:
break;
}
return 0;
}
uint32 CFatVolume::GetEntryCluster(SFatRawDirectoryEntry* psEntry)
{
fatEntry uiClusterEntryMask;
fatEntry uiEntry;
uiClusterEntryMask = GetClusterEntryMask();
uiEntry = psEntry->uEntry.sFatRawCommon.uiFirstClusterLowWord | (uint32)psEntry->uEntry.sFatRawCommon.uiFirstClusterHighWord << 16;
uiEntry &= uiClusterEntryMask;
return uiEntry;
}
bool CFatVolume::HasNextFreeCluser(void)
{
if (muiNextFreeCluster != 0xFFFFFFFF)
{
if (muiNextFreeCluster <= muiNoOfClusters + 1)
{
return true;
}
}
return false;
}
uint16 CFatVolume::CalculateClusterStepSize(uint32 uiPageSize)
{
if (NumSectorsPerCluster() < uiPageSize)
{
return (uint16)(uiPageSize / NumSectorsPerCluster());
}
else
{
return 1;
}
}
EFatCode CFatVolume::EraseClusterContents(uint32 uiCluster)
{
bool bSuccess;
uint16 uiSectorsPerCluster;
uint32 uiCurrentSector;
uiCurrentSector = CalculateFirstSectorOfCluster(uiCluster);
uiSectorsPerCluster = NumSectorsPerCluster();
bSuccess = mpcDevice->Erase(uiCurrentSector, uiCurrentSector + uiSectorsPerCluster - 1);
if (bSuccess)
{
return FAT_SUCCESS;
}
else
{
return FAT_CANNOT_WRITE_MEDIA;
}
}
void CFatVolume::InitialiseDottyDirectoryEntry(SFatRawDirectoryEntry* psEntries, const char* sz, uint32 uiCluster)
{
psEntries->uEntry.sFatRawCommon.szShortName[0x0] = sz[0];
psEntries->uEntry.sFatRawCommon.szShortName[0x1] = sz[1];
psEntries->uEntry.sFatRawCommon.szShortName[0x2] = ' ';
psEntries->uEntry.sFatRawCommon.szShortName[0x3] = ' ';
psEntries->uEntry.sFatRawCommon.szShortName[0x4] = ' ';
psEntries->uEntry.sFatRawCommon.szShortName[0x5] = ' ';
psEntries->uEntry.sFatRawCommon.szShortName[0x6] = ' ';
psEntries->uEntry.sFatRawCommon.szShortName[0x7] = ' ';
psEntries->uEntry.sFatRawCommon.szShortName[0x8] = ' ';
psEntries->uEntry.sFatRawCommon.szShortName[0x9] = ' ';
psEntries->uEntry.sFatRawCommon.szShortName[0xA] = ' ';
psEntries->uEntry.sFatRawCommon.uiAttributes = 0x10;
psEntries->uEntry.sFatRawCommon.uiSize = 0x0;
psEntries->uEntry.sFatRawCommon.uiReserved = 0;
psEntries->uEntry.sFatRawCommon.uiFirstClusterLowWord = (uint16)uiCluster;
psEntries->uEntry.sFatRawCommon.uiFirstClusterHighWord = (uint16)(uiCluster >> 16);
psEntries->uEntry.sFatRawCommon.uiCreateDate = GetSystemClockDate();
psEntries->uEntry.sFatRawCommon.uiCreateTime = GetSystemClockTime();
psEntries->uEntry.sFatRawCommon.uiModifyDate = psEntries->uEntry.sFatRawCommon.uiCreateDate;
psEntries->uEntry.sFatRawCommon.uiModifyTime = psEntries->uEntry.sFatRawCommon.uiCreateTime;
psEntries->uEntry.sFatRawCommon.uiAccessDate = psEntries->uEntry.sFatRawCommon.uiCreateDate;
psEntries->uEntry.sFatRawCommon.uiCreateTimeTenths = 0xc6;
}
EFatCode CFatVolume::InitializeDirectoryCluster(SFatRawDirectoryEntry* psDirectoryParent, uint32 uiCluster)
{
uint32 uiFirstClusterSector;
SFatRawDirectoryEntry* psEntries;
SFatCache sBuffer;
bool bSuccess;
uint32 uiLastClusterSector;
uint32 uiSector;
uiSector = CalculateFirstSectorOfCluster(uiCluster);
sBuffer = mcSectorCache.ReadSector(uiSector); if (!sBuffer.IsValid()) { return FAT_CANNOT_READ_MEDIA; };
psEntries = (SFatRawDirectoryEntry*)sBuffer.Get();
memset(psEntries, 0, GetSectorSize());
InitialiseDottyDirectoryEntry(psEntries, ". ", uiCluster);
psEntries++;
InitialiseDottyDirectoryEntry(psEntries, "..", GetEntryCluster(psDirectoryParent));
DirtySector(sBuffer);
if (meFileSystem == FAT_FS_TYPE_FAT32)
{
uint32 uiParentCluster;
uiParentCluster = GetFirstClusterFromFatEntry(psDirectoryParent, true);
if (GetRootCluster() == uiParentCluster)
{
psEntries->uEntry.sFatRawCommon.uiFirstClusterLowWord = 0;
psEntries->uEntry.sFatRawCommon.uiFirstClusterHighWord = 0;
}
}
uiFirstClusterSector = CalculateFirstSectorOfCluster(uiCluster) + 1;
uiLastClusterSector = uiFirstClusterSector + NumSectorsPerCluster() - 2;
if (uiLastClusterSector >= uiFirstClusterSector)
{
bSuccess = mpcDevice->Erase(uiFirstClusterSector, uiLastClusterSector);
if (!bSuccess)
{
return FAT_CANNOT_WRITE_MEDIA;
}
}
return FAT_SUCCESS;
}
EFatCode CFatVolume::InitialiseAllocatedFatCluster(SFatRawDirectoryEntry* psParentDirectory, uint32 uiCluster, bool bZero)
{
EFatCode eResult;
if (psParentDirectory)
{
eResult = InitializeDirectoryCluster(psParentDirectory, uiCluster);
if (eResult != FAT_SUCCESS) { return eResult; };
}
else
{
if (bZero)
{
eResult = EraseClusterContents(uiCluster);
if (eResult != FAT_SUCCESS) { return eResult; };
}
}
return FAT_SUCCESS;
}
EFatCode CFatVolume::WrapAllocate(uint32 uiStartCluster, uint32 uiLastFatEntry, bool* pbWrappedAround, uint32* puiClusterIndex, uint32* puiOffsetInSector, uint32* puiFirstClusterSector)
{
if (uiStartCluster > 2 && !*pbWrappedAround)
{
*puiClusterIndex = 2;
*pbWrappedAround = true;
CalculateFATIndexAndOffset(puiOffsetInSector, *puiClusterIndex, puiFirstClusterSector);
return FAT_SUCCESS;
}
else if (*pbWrappedAround && (*puiClusterIndex >= uiStartCluster))
{
if (!FatIsEOFEntry(uiLastFatEntry))
{
FreeChain(uiLastFatEntry);
}
return FAT_INSUFFICIENT_DISK_SPACE;
}
else
{
return FAT_UNKNOWN_ERROR;
}
}
EFatCode CFatVolume::WriteFat12Entry(uint32 uiOffsetInSector, uint32 uiPreviousOffset, uint32 uiCluster, uint32 uiSector, uint32 uiPreviousSector, fatEntry uiLastFatEntry)
{
bool bNextSector;
SFatCache sBuffer;
uint8* puiBuffer;
sBuffer = mcSectorCache.ReadSector(uiSector); if (!sBuffer.IsValid()) { return FAT_CANNOT_READ_MEDIA; };
puiBuffer = sBuffer.Get();
if (uiCluster & 1)
{
puiBuffer[uiOffsetInSector] &= 0x0F;
puiBuffer[uiOffsetInSector] |= (uint8)(0x00000FFF << 4);
}
else
{
puiBuffer[uiOffsetInSector] = (uint8)0x00000FFF;
}
DirtySector(sBuffer);
if (uiOffsetInSector == (uint32)GetSectorSize() - 1)
{
sBuffer = mcSectorCache.ReadSector(uiSector + 1); if (!sBuffer.IsValid()) { return FAT_CANNOT_READ_MEDIA; };
puiBuffer = sBuffer.Get();
bNextSector = true;
}
else
{
bNextSector = false;
}
if (uiCluster & 1)
{
puiBuffer[bNextSector ? 0 : (uiOffsetInSector + 1)] = ((uint16)0x00000FFF << 4) >> 8;
}
else
{
puiBuffer[bNextSector ? 0 : (uiOffsetInSector + 1)] &= 0xF0;
puiBuffer[bNextSector ? 0 : (uiOffsetInSector + 1)] |= 0x00000FFF >> 8;
}
DirtySector(sBuffer);
if (uiLastFatEntry != 0x00000FFF)
{
sBuffer = mcSectorCache.ReadSector(uiPreviousSector); if (!sBuffer.IsValid()) { return FAT_CANNOT_READ_MEDIA; };
puiBuffer = sBuffer.Get();
if (uiLastFatEntry & 1)
{
puiBuffer[uiPreviousOffset] &= 0x0F;
puiBuffer[uiPreviousOffset] |= (uint8)(uiCluster << 4);
}
else
{
puiBuffer[uiPreviousOffset] = (uint8)uiCluster;
}
DirtySector(sBuffer);
if (uiPreviousOffset == (uint32)GetSectorSize() - 1)
{
sBuffer = mcSectorCache.ReadSector(uiPreviousSector + 1); if (!sBuffer.IsValid()) { return FAT_CANNOT_READ_MEDIA; };
puiBuffer = sBuffer.Get();
bNextSector = true;
}
if (uiLastFatEntry & 1)
{
puiBuffer[bNextSector ? 0 : (uiPreviousOffset + 1)] = ((uint16)uiCluster << 4) >> 8;
}
else
{
puiBuffer[bNextSector ? 0 : (uiPreviousOffset + 1)] &= 0xF0;
puiBuffer[bNextSector ? 0 : (uiPreviousOffset + 1)] |= (uint8)(uiCluster >> 8);
}
DirtySector(sBuffer);
}
return FAT_SUCCESS;
}
EFatCode CFatVolume::WriteFat16Entry(uint32 uiOffsetInSector, uint32 uiPreviousOffset, uint32 uiCluster, uint32 uiSector, uint32 uiPreviousSector, fatEntry uiLastFatEntry)
{
SFatCache sBuffer;
uint8* puiBuffer;
sBuffer = mcSectorCache.ReadSector(uiSector); if (!sBuffer.IsValid()) { return FAT_CANNOT_READ_MEDIA; };
puiBuffer = sBuffer.Get();
*((uint16*)&puiBuffer[uiOffsetInSector]) = 0x0000FFFF;
DirtySector(sBuffer);
if (uiLastFatEntry != 0x0000FFFF)
{
sBuffer = mcSectorCache.ReadSector(uiPreviousSector); if (!sBuffer.IsValid()) { return FAT_CANNOT_READ_MEDIA; };
puiBuffer = sBuffer.Get();
*((uint16*)&puiBuffer[uiPreviousOffset]) = (uint16)uiCluster;
DirtySector(sBuffer);
}
return FAT_SUCCESS;
}
EFatCode CFatVolume::WriteFat32Entry(uint32 uiOffsetInSector, uint32 uiLastEntryOffset, uint32 uiClusterIndexInTable, uint32 uiSector, uint32 uiPreviousSector, fatEntry uiLastFatEntry)
{
SFatCache sBuffer;
uint8* puiBuffer;
sBuffer = mcSectorCache.ReadSector(uiSector); if (!sBuffer.IsValid()) { return FAT_CANNOT_READ_MEDIA; };
puiBuffer = sBuffer.Get();
*((uint32*)&puiBuffer[uiOffsetInSector]) = 0x0FFFFFFF;
DirtySector(sBuffer);
if (uiLastFatEntry != 0x0FFFFFFF)
{
sBuffer = mcSectorCache.ReadSector(uiPreviousSector); if (!sBuffer.IsValid()) { return FAT_CANNOT_READ_MEDIA; };
puiBuffer = sBuffer.Get();
*((uint32*)&puiBuffer[uiLastEntryOffset]) = (*((uint32*)&puiBuffer[uiLastEntryOffset]) & (~0x0FFFFFFF)) | (uiClusterIndexInTable & 0x0FFFFFFF);
DirtySector(sBuffer);
}
return FAT_SUCCESS;
}
EFatCode CFatVolume::WriteAllocatedFatEntry(uint32 uiClusterIndexInTable, uint32 uiOffsetInSector, uint32 uiSector, fatEntry uiPreviousFatEntry, uint32 uiPreviousSector, uint32 uiPreviousEntryOffset)
{
SetNextFreeCluster(uiClusterIndexInTable + 1);
SetTotalFreeClusters(GetTotalFreeClusters() - 1);
switch (meFileSystem)
{
case FAT_FS_TYPE_FAT12:
{
return WriteFat12Entry(uiOffsetInSector, uiPreviousEntryOffset, uiClusterIndexInTable, uiSector, uiPreviousSector, uiPreviousFatEntry);
}
case FAT_FS_TYPE_FAT16:
{
return WriteFat16Entry(uiOffsetInSector, uiPreviousEntryOffset, uiClusterIndexInTable, uiSector, uiPreviousSector, uiPreviousFatEntry);
}
case FAT_FS_TYPE_FAT32:
{
return WriteFat32Entry(uiOffsetInSector, uiPreviousEntryOffset, uiClusterIndexInTable, uiSector, uiPreviousSector, uiPreviousFatEntry);
}
default:
break;
}
return FAT_UNKNOWN_ERROR;
}
uint32 CFatVolume::AllocateClusters(SFatRawDirectoryEntry* psParentDirectory, uint32 uiClusterCount, bool bEraseCluster, uint32 uiPageSize, EFatCode* peResult, uint32 uiPreviousCluster)
{
uint32 uiFirstClusterSector;
uint32 uiCurrentSector;
fatEntry uiCluster;
uint32 uiOffsetInSector = 0;
fatEntry uiLastClusterIndex;
fatEntry uiFatEntry;
uint32 uiFirstEmptyCluster;
uint32 uiLastClusterSector;
uint32 uiLastEntryOffset;
uint32 uiStartCluster;
bool bWrappedAround;
uint16 uiClusterStep;
int iCount;
if ((uiClusterCount > 1) && (psParentDirectory != 0L))
{
*peResult = FAT_UNKNOWN_ERROR;
return 0;
}
if (uiClusterCount == 0)
{
*peResult = FAT_UNKNOWN_ERROR;
return 0;
}
uiCluster = 2;
uiFirstEmptyCluster = 0;
if (HasNextFreeCluser())
{
uiCluster = GetNextFreeCluster();
}
uiClusterStep = CalculateClusterStepSize(uiPageSize);
uiCluster = FindNextPageCluster(uiPageSize, uiCluster, uiClusterStep);
if (!FatIsEOFEntry(uiPreviousCluster))
{
CalculateFATIndexAndOffset(&uiLastEntryOffset, uiPreviousCluster, &uiLastClusterSector);
}
else
{
uiLastClusterSector = 0;
uiLastEntryOffset = 0;
}
CalculateFATIndexAndOffset(&uiOffsetInSector, uiCluster, &uiFirstClusterSector);
uiStartCluster = uiCluster;
uiLastClusterIndex = uiPreviousCluster;
for (iCount = 0;; iCount++)
{
uiCurrentSector = uiFirstClusterSector;
bWrappedAround = false;
do
{
if ((uiCluster > GetNumClusters() + 1))
{
*peResult = WrapAllocate(uiStartCluster, uiLastClusterIndex, &bWrappedAround, &uiCluster, &uiOffsetInSector, &uiFirstClusterSector);
if (*peResult != FAT_SUCCESS)
{
return 0;
}
break;
}
*peResult = ReadFatEntry(uiOffsetInSector, uiCluster, uiFirstClusterSector, &uiFatEntry);
if (*peResult != FAT_SUCCESS)
{
return 0;
}
bool bIsFatFree = IsFreeFat(uiFatEntry);
if (bIsFatFree)
{
if (uiFirstEmptyCluster == 0)
{
uiFirstEmptyCluster = uiCluster;
}
*peResult = WriteAllocatedFatEntry(uiCluster, uiOffsetInSector, uiFirstClusterSector, uiLastClusterIndex, uiLastClusterSector, uiLastEntryOffset);
if (*peResult != FAT_SUCCESS)
{
return 0;
}
uiClusterCount--;
if (uiClusterCount == 0)
{
*peResult = InitialiseAllocatedFatCluster(psParentDirectory, uiCluster, bEraseCluster);
if (*peResult != FAT_SUCCESS)
{
return 0;
}
return uiFirstEmptyCluster;
}
uiLastClusterIndex = uiCluster;
uiLastClusterSector = uiFirstClusterSector;
uiLastEntryOffset = uiOffsetInSector;
}
if (uiFirstEmptyCluster == 0)
{
uiCluster += uiClusterStep;
}
else
{
uiCluster++;
}
CalculateFATIndexAndOffset(&uiOffsetInSector, uiCluster, &uiFirstClusterSector);
}
while (uiCurrentSector == uiFirstClusterSector);
}
}
EFatCode CFatVolume::UpdateDirectoryEntry(SFatDirectoryEntry* psEntry, uint32 uiFirstCluster, uint32 uiNewClusterInVolume, uint32 uiClustersInFile)
{
SFatCache sBuffer;
if (IsRootDirectoryCluster(uiFirstCluster))
{
psEntry->sRaw.uEntry.sFatRawCommon.uiFirstClusterLowWord = (uint16)uiNewClusterInVolume;
psEntry->sRaw.uEntry.sFatRawCommon.uiFirstClusterHighWord = (uint16)(uiNewClusterInVolume >> 16);
psEntry->sRaw.uEntry.sFatRawCommon.uiAttributes = 0x20;
sBuffer = mcSectorCache.ReadSector(psEntry->uiSectorAddress); if (!sBuffer.IsValid()) { return FAT_CANNOT_READ_MEDIA; };
memcpy(sBuffer.Get() + psEntry->uiSectorOffset, &psEntry->sRaw, sizeof(SFatRawDirectoryEntry));
DirtySector(sBuffer);
}
return FAT_SUCCESS;
}
EFatCode CFatVolume::SetFat12ClusterEntry(uint32 uiClusterIndex, fatEntry uiClusterInVolume, uint32 uiFirstClusterSector, uint16 uiOffsetInSector)
{
uint8* puiBuffer;
SFatCache sBuffer;
sBuffer = mcSectorCache.ReadSector(uiFirstClusterSector); if (!sBuffer.IsValid()) { return FAT_CANNOT_READ_MEDIA; };
puiBuffer = sBuffer.Get();
if (uiClusterIndex & 1)
{
uiClusterInVolume <<= 4;
puiBuffer[uiOffsetInSector] &= 0x0F;
puiBuffer[uiOffsetInSector] |= (uint8)uiClusterInVolume;
}
else
{
puiBuffer[uiOffsetInSector] = (uint8)uiClusterInVolume;
}
DirtySector(sBuffer);
if (uiOffsetInSector == GetSectorSize() - 1)
{
sBuffer = mcSectorCache.ReadSector(uiFirstClusterSector + 1); if (!sBuffer.IsValid()) { return FAT_CANNOT_READ_MEDIA; };
puiBuffer = sBuffer.Get();
uiOffsetInSector = 0;
}
else
{
uiOffsetInSector++;
}
if (uiClusterIndex & 1)
{
puiBuffer[uiOffsetInSector] = ((uint16)uiClusterInVolume) >> 8;
}
else
{
puiBuffer[uiOffsetInSector] &= 0xF0;
puiBuffer[uiOffsetInSector] |= ((uint16)uiClusterInVolume) >> 8;
}
DirtySector(sBuffer);
return FAT_SUCCESS;
}
EFatCode CFatVolume::SetFat16ClusterEntry(fatEntry uiClusterInVolume, uint32 uiFirstClusterSector, uint16 uiOffsetInSector)
{
uint8* puiBuffer;
SFatCache sBuffer;
sBuffer = mcSectorCache.ReadSector(uiFirstClusterSector); if (!sBuffer.IsValid()) { return FAT_CANNOT_READ_MEDIA; };
puiBuffer = sBuffer.Get();
*((uint16*)&puiBuffer[uiOffsetInSector]) = (uint16)uiClusterInVolume;
DirtySector(sBuffer);
return FAT_SUCCESS;
}
EFatCode CFatVolume::SetFat32ClusterEntry(fatEntry uiClusterInVolume, uint32 uiFirstClusterSector, uint16 uiOffsetInSector)
{
uint8* puiBuffer;
SFatCache sBuffer;
sBuffer = mcSectorCache.ReadSector(uiFirstClusterSector); if (!sBuffer.IsValid()) { return FAT_CANNOT_READ_MEDIA; };
puiBuffer = sBuffer.Get();
*((uint32*)&puiBuffer[uiOffsetInSector]) = uiClusterInVolume & 0x0FFFFFFF;
DirtySector(sBuffer);
return FAT_SUCCESS;
}
EFatCode CFatVolume::SetClusterEntry(uint32 uiClusterIndex, fatEntry uiClusterInVolume)
{
uint32 uiFirstClusterSector;
uint32 uiOffsetInSector;
EFatCode eResult;
CalculateFATIndexAndOffset(&uiOffsetInSector, uiClusterIndex, &uiFirstClusterSector);
switch (meFileSystem)
{
case FAT_FS_TYPE_FAT12:
{
eResult = SetFat12ClusterEntry(uiClusterIndex, uiClusterInVolume, uiFirstClusterSector, uiOffsetInSector);
return eResult;
}
case FAT_FS_TYPE_FAT16:
{
eResult = SetFat16ClusterEntry(uiClusterInVolume, uiFirstClusterSector, uiOffsetInSector);
return eResult;
}
case FAT_FS_TYPE_FAT32:
{
eResult = SetFat32ClusterEntry(uiClusterInVolume, uiFirstClusterSector, uiOffsetInSector);
return eResult;
}
default:
break;
}
return FAT_UNKNOWN_ERROR;
}
EFatCode CFatVolume::IncreaseFat12ClusterAddress(uint32* puiClusterIndex, uint32* puiSector, uint32* puiOffsetInSector, bool* pbFat12OddClusterBeingProcessed, bool* pbFat12MultiStepProgress)
{
SFatCache sBuffer;
uint8* puiBuffer;
sBuffer = mcSectorCache.ReadSector(*puiSector); if (!sBuffer.IsValid()) { return FAT_CANNOT_READ_MEDIA; };
puiBuffer = sBuffer.Get();
if (!*pbFat12MultiStepProgress)
{
*pbFat12OddClusterBeingProcessed = *puiClusterIndex & 1;
*puiClusterIndex = 0;
((uint8*)&puiClusterIndex)[0] = puiBuffer[*puiOffsetInSector];
}
if (*puiOffsetInSector == (uint32)GetSectorSize() - 1)
{
(*puiSector)++;
*puiOffsetInSector = 0;
*pbFat12MultiStepProgress = true;
return FAT_SUCCESS;
}
else if (!*pbFat12MultiStepProgress)
{
(*puiOffsetInSector)++;
}
((uint8*)&puiClusterIndex)[1] = puiBuffer[*puiOffsetInSector];
if (*pbFat12OddClusterBeingProcessed)
{
*puiClusterIndex >>= 4;
}
else
{
*puiClusterIndex &= 0x00000FFF;
}
*pbFat12MultiStepProgress = false;
return FAT_SUCCESS;
}
EFatCode CFatVolume::IncreaseFat16ClusterAddress(uint32* puiClusterIndex, uint32 uiSector, uint32 uiOffsetInSector)
{
SFatCache sBuffer;
uint8* puiBuffer;
sBuffer = mcSectorCache.ReadSector(uiSector); if (!sBuffer.IsValid()) { return FAT_CANNOT_READ_MEDIA; };
puiBuffer = sBuffer.Get();
*puiClusterIndex = *((uint16*)&puiBuffer[uiOffsetInSector]);
return FAT_SUCCESS;
}
EFatCode CFatVolume::IncreaseFat32ClusterAddress(uint32* puiClusterIndex, uint32 uiSector, uint32 uiOffsetInSector)
{
SFatCache sBuffer;
uint8* puiBuffer;
sBuffer = mcSectorCache.ReadSector(uiSector); if (!sBuffer.IsValid()) { return FAT_CANNOT_READ_MEDIA; };
puiBuffer = sBuffer.Get();
*puiClusterIndex = *((uint32*)&puiBuffer[uiOffsetInSector]) & 0x0FFFFFFF;
return FAT_SUCCESS;
}
EFatCode CFatVolume::SeekByClusterCount(uint32 uiClusterIndex, uint16 uiClusterCount, uint32* puiNewClusterIndex)
{
uint32 uiOffsetInSector;
uint32 uiFirstClusterSector;
uint32 uiCurrentSector;
bool bFat12OddClusterBeingProcessed;
bool bFat12MultiStepProgress;
EFatCode eResult;
if (uiClusterCount == 0)
{
*puiNewClusterIndex = uiClusterIndex;
return FAT_SUCCESS;
}
CalculateFATIndexAndOffset(&uiOffsetInSector, uiClusterIndex, &uiFirstClusterSector);
bFat12OddClusterBeingProcessed = false;
bFat12MultiStepProgress = false;
for (;;)
{
uiCurrentSector = uiFirstClusterSector;
while (uiCurrentSector == uiFirstClusterSector)
{
if (uiClusterIndex < 2)
{
return FAT_INVALID_CLUSTER;
}
switch (meFileSystem)
{
case FAT_FS_TYPE_FAT12:
{
eResult = IncreaseFat12ClusterAddress(&uiClusterIndex, &uiFirstClusterSector, &uiOffsetInSector, &bFat12OddClusterBeingProcessed, &bFat12MultiStepProgress);
if (eResult != FAT_SUCCESS) { return eResult; };
if (uiOffsetInSector != 0)
{
break;
}
else
{
continue;
}
}
case FAT_FS_TYPE_FAT16:
{
eResult = IncreaseFat16ClusterAddress(&uiClusterIndex, uiFirstClusterSector, uiOffsetInSector);
if (eResult != FAT_SUCCESS) { return eResult; };
break;
}
case FAT_FS_TYPE_FAT32:
{
eResult = IncreaseFat32ClusterAddress(&uiClusterIndex, uiFirstClusterSector, uiOffsetInSector);
if (eResult != FAT_SUCCESS) { return eResult; };
break;
}
default:
break;
}
if (FatIsEOFEntry(uiClusterIndex))
{
return FAT_UNKNOWN_ERROR;
}
uiClusterCount--;
if (uiClusterCount == 0)
{
*puiNewClusterIndex = (uint32)uiClusterIndex;
return FAT_SUCCESS;
}
CalculateFATIndexAndOffset(&uiOffsetInSector, uiClusterIndex, &uiFirstClusterSector);
}
}
}
EFatCode CFatVolume::FreeDirectoryEntry(SFatDirectoryEntry* psEntry)
{
uint32 uiCluster;
EFatCode eResult;
SFatCache sBuffer;
uiCluster = GetFirstClusterFromFatEntry(&psEntry->sRaw, meFileSystem == FAT_FS_TYPE_FAT32);
if (uiCluster != 0)
{
psEntry->sRaw.uEntry.sFatRawCommon.uiFirstClusterLowWord = 0;
psEntry->sRaw.uEntry.sFatRawCommon.uiFirstClusterHighWord = 0;
psEntry->sRaw.uEntry.sFatRawCommon.uiSize = 0x0;
FillDirectoryEntryFromRawEntry(psEntry, &psEntry->sRaw);
sBuffer = mcSectorCache.ReadSector(psEntry->uiSectorAddress); if (!sBuffer.IsValid()) { return FAT_CANNOT_READ_MEDIA; };
memcpy(sBuffer.Get() + psEntry->uiSectorOffset, &psEntry->sRaw, sizeof(SFatRawDirectoryEntry));
DirtySector(sBuffer);
eResult = FreeChain(uiCluster);
return eResult;
}
else
{
return FAT_SUCCESS;
}
}
void CFatVolume::CalculateFATIndexAndOffset(uint32* puiOffsetInSector, uint32 uiClusterIndex, uint32* puiSector)
{
*puiOffsetInSector = CalculateFATEntryIndex(uiClusterIndex);
*puiSector = GetNoOfReservedSectors() + (*puiOffsetInSector / GetSectorSize());
*puiOffsetInSector = *puiOffsetInSector % GetSectorSize();
}
uint32 CFatVolume::CalculateFATEntryIndex(uint32 uiClusterIndexInFAT)
{
switch (meFileSystem)
{
case FAT_FS_TYPE_FAT12:
return uiClusterIndexInFAT + (uiClusterIndexInFAT >> 1);
case FAT_FS_TYPE_FAT16:
return uiClusterIndexInFAT * 2;
case FAT_FS_TYPE_FAT32:
return uiClusterIndexInFAT * 4;
default:
break;
}
return 0xFFFFFFFF;
}
SFatCache CFatVolume::ReadSector(uint32 uiFatInfoSector, bool bLock)
{
SFatCache sSectorCache;
sSectorCache = mcSectorCache.ReadSector(uiFatInfoSector);
if ((sSectorCache.pvCachedSector != 0L) && bLock)
{
mcSectorCache.Lock(sSectorCache);
}
return sSectorCache;
}
void CFatVolume::DirtySector(SFatCache sCachedSector)
{
mcSectorCache.Dirty(sCachedSector);
}
uint8 CFatVolume::FatLongEntryChecksum(char* szFilename)
{
uint16 len;
uint8 sum = 0;
for (len = 11; len != 0; len--)
{
sum = ((sum & 1) ? 0x80 : 0) + (sum >> 1) + *szFilename++;
}
return sum;
}
uint32 CFatVolume::GetPageSize(void)
{
return mpcDevice->GetPageSize();
}
bool CFatVolume::FatIsEOFEntry(fatEntry uiFat)
{
switch (meFileSystem)
{
case FAT_FS_TYPE_FAT12:
return uiFat >= 0x0FF8;
case FAT_FS_TYPE_FAT16:
return uiFat >= 0xFFF8;
case FAT_FS_TYPE_FAT32:
return uiFat >= 0x0FFFFFF8;
default:
break;
}
return false;
}
uint32 CFatVolume::CalculateRootSector(void)
{
if (meFileSystem == FAT_FS_TYPE_FAT32)
{
return CalculateFirstSectorOfCluster(muiRootCluster);
}
else
{
return muiNoOfReservedSectors + (muiNoOfFatTables * muiFatSize);
}
}
uint32 CFatVolume::CalculateFirstSectorOfCluster(uint32 uiCluster)
{
return (((uiCluster - 2) * muiNoOfSectorsPerCluster) + muiFirstDataSector);
}
EFatCode CFatVolume::ReadFat12Entry(uint32 uiOffsetInSector, uint32 uiCluster, uint32 uiSector, fatEntry* puiFatEntry)
{
fatEntry uiFatEntry;
bool bNextSector;
SFatCache sBuffer;
uiFatEntry = 0;
sBuffer = mcSectorCache.ReadSector(uiSector); if (!sBuffer.IsValid()) { return FAT_CANNOT_READ_MEDIA; };
((uint8*)&uiFatEntry)[0] = sBuffer.Get()[uiOffsetInSector];
if (uiOffsetInSector == (uint32)GetSectorSize() - 1)
{
sBuffer = mcSectorCache.ReadSector(uiSector + 1); if (!sBuffer.IsValid()) { return FAT_CANNOT_READ_MEDIA; };
bNextSector = true;
}
else
{
bNextSector = false;
}
((uint8*)&uiFatEntry)[1] = sBuffer.Get()[bNextSector ? 0 : (uiOffsetInSector + 1)];
if (uiCluster & 0x1)
{
uiFatEntry >>= 4;
}
else
{
uiFatEntry &= 0x00000FFF;
}
*puiFatEntry = uiFatEntry;
return FAT_SUCCESS;
}
EFatCode CFatVolume::ReadFat16Entry(uint32 uiOffsetInSector, uint32 uiSector, fatEntry* puiFatEntry)
{
SFatCache sBuffer;
sBuffer = mcSectorCache.ReadSector(uiSector); if (!sBuffer.IsValid()) { return FAT_CANNOT_READ_MEDIA; };
*puiFatEntry = *((uint16*)&(sBuffer.Get()[uiOffsetInSector]));
return FAT_SUCCESS;
}
EFatCode CFatVolume::ReadFat32Entry(uint32 uiOffsetInSector, uint32 uiSector, fatEntry* puiFatEntry)
{
SFatCache sBuffer;
sBuffer = mcSectorCache.ReadSector(uiSector); if (!sBuffer.IsValid()) { return FAT_CANNOT_READ_MEDIA; };
*puiFatEntry = *((uint32*)&(sBuffer.Get()[uiOffsetInSector])) & 0x0FFFFFFF;
return FAT_SUCCESS;
}
EFatCode CFatVolume::ReadFatEntry(uint32 uiOffsetInSector, uint32 uiClusterIndex, uint32 uiSector, fatEntry* puiFatEntry)
{
EFatCode eResult;
switch (meFileSystem)
{
case FAT_FS_TYPE_FAT12:
{
eResult = ReadFat12Entry(uiOffsetInSector, uiClusterIndex, uiSector, puiFatEntry);
break;
}
case FAT_FS_TYPE_FAT16:
{
eResult = ReadFat16Entry(uiOffsetInSector, uiSector, puiFatEntry);
break;
}
case FAT_FS_TYPE_FAT32:
{
eResult = ReadFat32Entry(uiOffsetInSector, uiSector, puiFatEntry);
break;
}
default:
eResult = FAT_UNKNOWN_ERROR;
break;
}
return eResult;
}
EFatCode CFatVolume::FreeFat12Chain(bool* pbFat12MultiStepProgress, uint32* puiFreedClusterIndex, uint32* puiSector, uint32* puiOffsetInSector)
{
SFatCache sBuffer;
uint8* puiBuffer;
sBuffer = mcSectorCache.ReadSector(*puiSector); if (!sBuffer.IsValid()) { return FAT_CANNOT_READ_MEDIA; };
puiBuffer = sBuffer.Get();
if (!*pbFat12MultiStepProgress)
{
*pbFat12MultiStepProgress = *puiFreedClusterIndex & 1;
*puiFreedClusterIndex = 0;
((uint8*)puiFreedClusterIndex)[0] = puiBuffer[*puiOffsetInSector];
if (*pbFat12MultiStepProgress)
{
puiBuffer[*puiOffsetInSector] &= 0x0F;
}
else
{
puiBuffer[*puiOffsetInSector] = 0x0000;
}
DirtySector(sBuffer);
}
if (*puiOffsetInSector == (uint32)GetSectorSize() - 1)
{
(*puiSector)++;
*puiOffsetInSector = 0;
*pbFat12MultiStepProgress = true;
return FAT_SUCCESS;
}
else if (!*pbFat12MultiStepProgress)
{
(*puiOffsetInSector)++;
}
((uint8*)puiFreedClusterIndex)[1] = puiBuffer[*puiOffsetInSector];
if (*pbFat12MultiStepProgress)
{
*puiFreedClusterIndex >>= 4;
}
else
{
*puiFreedClusterIndex &= 0xFFF;
}
if (*pbFat12MultiStepProgress)
{
puiBuffer[*puiOffsetInSector] = 0x0000;
}
else
{
puiBuffer[*puiOffsetInSector] &= 0xF0;
}
DirtySector(sBuffer);
*pbFat12MultiStepProgress = false;
return FAT_SUCCESS;
}
EFatCode CFatVolume::FreeFat16Chain(uint32* puiFreedClusterIndex, uint32 uiSector, uint32 uiOffsetInSector)
{
SFatCache sBuffer;
sBuffer = mcSectorCache.ReadSector(uiSector); if (!sBuffer.IsValid()) { return FAT_CANNOT_READ_MEDIA; };
*puiFreedClusterIndex = *((uint16*)&(sBuffer.Get()[uiOffsetInSector]));
*((uint16*)&(sBuffer.Get()[uiOffsetInSector])) = 0x0000;
DirtySector(sBuffer);
return FAT_SUCCESS;
}
EFatCode CFatVolume::FreeFat32Chain(uint32* puiFreedClusterIndex, uint32 uiSector, uint32 uiOffsetInSector)
{
SFatCache sBuffer;
sBuffer = mcSectorCache.ReadSector(uiSector); if (!sBuffer.IsValid()) { return FAT_CANNOT_READ_MEDIA; };
*puiFreedClusterIndex = *((uint32*)&(sBuffer.Get()[uiOffsetInSector])) & 0x0FFFFFFF;
*((uint32*)&(sBuffer.Get()[uiOffsetInSector])) &= (~0x0FFFFFFF);
DirtySector(sBuffer);
return FAT_SUCCESS;
}
EFatCode CFatVolume::FreeChain(uint32 uiClusterIndex)
{
EFatCode eResult;
uint32 uiOffsetInSector;
uint32 uiFirstClusterSector;
uint32 uiCurrentSector;
bool bFat12OddClusterBeingProcessed = false;
CalculateFATIndexAndOffset(&uiOffsetInSector, uiClusterIndex, &uiFirstClusterSector);
for (;;)
{
uiCurrentSector = uiFirstClusterSector;
while (uiCurrentSector == uiFirstClusterSector)
{
if (uiClusterIndex < 2)
{
return FAT_INVALID_CLUSTER;
}
switch (meFileSystem)
{
case FAT_FS_TYPE_FAT12:
{
eResult = FreeFat12Chain(&bFat12OddClusterBeingProcessed, &uiClusterIndex, &uiFirstClusterSector, &uiOffsetInSector);
if (eResult != FAT_SUCCESS) { return eResult; };
if (uiOffsetInSector != 0)
{
break;
}
else
{
continue;
}
}
case FAT_FS_TYPE_FAT16:
{
eResult = FreeFat16Chain(&uiClusterIndex, uiFirstClusterSector, uiOffsetInSector);
if (eResult != FAT_SUCCESS) { return eResult; };
break;
}
case FAT_FS_TYPE_FAT32:
{
eResult = FreeFat32Chain(&uiClusterIndex, uiFirstClusterSector, uiOffsetInSector);
if (eResult != FAT_SUCCESS) { return eResult; };
break;
}
default:
break;
}
SetTotalFreeClusters(GetTotalFreeClusters() + 1);
if (FatIsEOFEntry(uiClusterIndex))
{
return FAT_SUCCESS;
}
CalculateFATIndexAndOffset(&uiOffsetInSector, uiClusterIndex, &uiFirstClusterSector);
}
}
}
bool CFatVolume::IsFreeFat(fatEntry uifat)
{
switch (meFileSystem)
{
case FAT_FS_TYPE_FAT32:
return (uifat & 0x0FFFFFFF) == 0;
case FAT_FS_TYPE_FAT16:
return (uifat & 0x0000FFFF) == 0;
case FAT_FS_TYPE_FAT12:
return (uifat & 0x00000FFF) == 0;
default:
break;
}
return true;
}
void CFatVolume::SetNextFreeCluster(uint32 uiCluster)
{
muiNextFreeCluster = uiCluster;
}
void CFatVolume::SetTotalFreeClusters(uint32 muiTotalFreeClusters)
{
muiTotalFreeClusters = muiTotalFreeClusters;
}
EFatCode CFatVolume::CreateFakeRootEntry(SFatDirectoryEntry* psEntry)
{
uint32 uiRootCluster;
strcpy((char*)psEntry->szName, "ROOT");
GetFatShortNameForEntry((char*)psEntry->sRaw.uEntry.sFatRawCommon.szShortName, (char*)psEntry->szName, 1);
psEntry->uiAttributes = psEntry->sRaw.uEntry.sFatRawCommon.uiAttributes = 0x10;
psEntry->uiSize = psEntry->sRaw.uEntry.sFatRawCommon.uiSize = 0x0;
psEntry->uiSectorAddress = 0;
psEntry->uiSectorOffset = 0;
uiRootCluster = GetRootCluster();
psEntry->sRaw.uEntry.sFatRawCommon.uiFirstClusterLowWord = (uint16)uiRootCluster;
psEntry->sRaw.uEntry.sFatRawCommon.uiFirstClusterHighWord = (uint16)(uiRootCluster >> 16);
return FAT_SUCCESS;
}
const char* FindNextPathItem(const char* szPath, char* szCurrentLevelPath)
{
char* szPathLevel;
szPathLevel = szCurrentLevelPath;
szPath = StepPathOverSlash(szPath);
uint16 uiCount = 0;
while (*szPath != '\0' && *szPath != '\\')
{
if (uiCount++ > 260)
{
return 0L;
}
*szPathLevel++ = *szPath++;
}
*szPathLevel = 0;
return szPath;
}
uint32 CFatVolume::GetRootDirectorySector(void)
{
return GetNoOfReservedSectors() + (GetNoOfFatTables() * GetFatSize());
}
bool CFatVolume::HasNoMoreEntries(SFatFileSystemQuery* psQuery)
{
return psQuery->sQuery.psCurrentEntryRaw == 0L;
}
EFatCode CFatVolume::TerminalQueryEntry(SFatFileSystemQuery* psQuery)
{
psQuery->sCurrentEntry.szName[0] = '\0';
return FAT_SUCCESS;
}
uint32 CFatVolume::CalculateQuerySector(SFatFileSystemQuery* psQuery)
{
if (IsRootDirectoryCluster(psQuery->sQuery.uiCurrentCluster))
{
return GetRootDirectorySector() + psQuery->sQuery.uiCurrentSector;
}
else
{
return CalculateFirstSectorOfCluster(psQuery->sQuery.uiCurrentCluster) + psQuery->sQuery.uiCurrentSector;
}
}
uint32 CFatVolume::CalculateQuerySectorOffset(SFatFileSystemQuery* psQuery)
{
return (uint16)(((uintptr_t)psQuery->sQuery.psCurrentEntryRaw) - ((uintptr_t)psQuery->sQuery.psFirstEntryRaw));
}
EFatCode CFatVolume::FindFirstFATEntry(const char* szParentPath, uint8 uiAttributes, SFatDirectoryEntry** ppsDirectoryEntry, SFatFileSystemQuery* psQuery)
{
EFatCode eResult;
SFatDirectoryEntry sParentEntry;
szParentPath = StepPathOverSlash(szParentPath);
if (szParentPath != 0L)
{
eResult = GetFileEntry(szParentPath, &sParentEntry);
if (eResult != FAT_SUCCESS) { return eResult; };
eResult = QueryFirstEntry(&sParentEntry.sRaw, uiAttributes, &psQuery->sQuery, 0);
if (eResult != FAT_SUCCESS) { return eResult; };
}
else
{
eResult = QueryFirstEntry(0, uiAttributes, &psQuery->sQuery, 0);
if (eResult != FAT_SUCCESS) { return eResult; };
}
if (HasNoMoreEntries(psQuery))
{
return TerminalQueryEntry(psQuery);
}
FillDirectoryEntryFromRawEntry(&psQuery->sCurrentEntry, psQuery->sQuery.psCurrentEntryRaw);
psQuery->sCurrentEntry.uiSectorAddress = CalculateQuerySector(psQuery);
psQuery->sCurrentEntry.uiSectorOffset = CalculateQuerySectorOffset(psQuery);
psQuery->sCurrentEntry.sRaw = *psQuery->sQuery.psCurrentEntryRaw;
CopyLongFilenameIntoString((char*)psQuery->sCurrentEntry.szName, psQuery->sQuery.auiLongFilename);
if (ppsDirectoryEntry) { *ppsDirectoryEntry = &psQuery->sCurrentEntry; };
return FAT_SUCCESS;
}
EFatCode CFatVolume::FindNextFATEntry(SFatDirectoryEntry** ppsDirectoryEntry, SFatFileSystemQuery* psQuery)
{
EFatCode eResult;
eResult = QueryNextEntry(&psQuery->sQuery, false, false);
if (eResult != FAT_SUCCESS)
{
return eResult;
}
if (HasNoMoreEntries(psQuery))
{
return TerminalQueryEntry(psQuery);
}
FillDirectoryEntryFromRawEntry(&psQuery->sCurrentEntry, psQuery->sQuery.psCurrentEntryRaw);
psQuery->sCurrentEntry.uiSectorAddress = CalculateQuerySector(psQuery);
psQuery->sCurrentEntry.uiSectorOffset = CalculateQuerySectorOffset(psQuery);
psQuery->sCurrentEntry.sRaw = *psQuery->sQuery.psCurrentEntryRaw;
CopyLongFilenameIntoString((char*)psQuery->sCurrentEntry.szName, psQuery->sQuery.auiLongFilename);
if (ppsDirectoryEntry) { *ppsDirectoryEntry = &psQuery->sCurrentEntry; };
return FAT_SUCCESS;
}
void CFatVolume::FillDirectoryEntryFromRawEntry(SFatDirectoryEntry* psEntry, SFatRawDirectoryEntry* psRawEntry)
{
ConvertFATShortInternalNameInto8Dot3Format(psEntry->szName, (uint8*)psRawEntry->uEntry.sFatRawCommon.szShortName);
psEntry->uiAttributes = psRawEntry->uEntry.sFatRawCommon.uiAttributes;
psEntry->uiSize = psRawEntry->uEntry.sFatRawCommon.uiSize;
psEntry->tCreateTime = FatDecodeDateTime(psRawEntry->uEntry.sFatRawCommon.uiCreateDate, psRawEntry->uEntry.sFatRawCommon.uiCreateTime);
psEntry->tModifyTime = FatDecodeDateTime(psRawEntry->uEntry.sFatRawCommon.uiModifyDate, psRawEntry->uEntry.sFatRawCommon.uiModifyTime);
psEntry->tAccessTime = FatDecodeDateTime(psRawEntry->uEntry.sFatRawCommon.uiAccessDate, 0);
psEntry->sRaw = *psRawEntry;
}
EFatCode CFatVolume::GenerateUniqueShortNameWithSuffix(SFatRawDirectoryEntry* psParentDirectory, uint8* szShortName)
{
SFatQueryState sQuery;
uint16 uiNameSuffix;
bool bIsValidEntry;
EFatCode eResult;
uiNameSuffix = 0;
sQuery.Init();
do
{
bIsValidEntry = true;
eResult = QueryFirstEntry(psParentDirectory, 0, &sQuery, 0);
if (eResult != FAT_SUCCESS)
{
break;
}
GenerateShortNameWithSuffix(uiNameSuffix, szShortName);
uiNameSuffix++;
while (sQuery.psCurrentEntryRaw->uEntry.sFatRawCommon.szShortName[0] != '\0')
{
if (memcmp(sQuery.psCurrentEntryRaw->uEntry.sFatRawCommon.szShortName, szShortName, 11) == 0)
{
bIsValidEntry = false;
break;
}
eResult = QueryNextEntry(&sQuery, false, false);
if (eResult != FAT_SUCCESS)
{
break;
}
}
if (eResult != FAT_SUCCESS)
{
break;
}
if (!bIsValidEntry)
{
GenerateShortNameWithSuffix(uiNameSuffix, szShortName);
uiNameSuffix++;
}
}
while (!bIsValidEntry);
sQuery.Kill(GetSectorCache());
return eResult;
}
void CFatVolume::InitialiseNewEntry(SFatDirectoryEntry* psNewEntry, const char* szName, uint8 uiAttributes, uint32 uiEntryCluster)
{
strcpy((char*)psNewEntry->szName, szName);
psNewEntry->uiAttributes = uiAttributes;
psNewEntry->uiSize = 0;
psNewEntry->sRaw.uEntry.sFatRawCommon.uiAttributes = uiAttributes;
psNewEntry->sRaw.uEntry.sFatRawCommon.uiReserved = 0;
psNewEntry->sRaw.uEntry.sFatRawCommon.uiSize = 0;
psNewEntry->sRaw.uEntry.sFatRawCommon.uiFirstClusterLowWord = (uint16)uiEntryCluster;
psNewEntry->sRaw.uEntry.sFatRawCommon.uiFirstClusterHighWord = (uint16)(uiEntryCluster >> 16);
psNewEntry->sRaw.uEntry.sFatRawCommon.uiCreateTimeTenths = 0;
psNewEntry->sRaw.uEntry.sFatRawCommon.uiCreateDate = GetSystemClockDate();
psNewEntry->sRaw.uEntry.sFatRawCommon.uiCreateTime = GetSystemClockTime();
psNewEntry->sRaw.uEntry.sFatRawCommon.uiModifyDate = psNewEntry->sRaw.uEntry.sFatRawCommon.uiCreateDate;
psNewEntry->sRaw.uEntry.sFatRawCommon.uiModifyTime = psNewEntry->sRaw.uEntry.sFatRawCommon.uiCreateTime;
psNewEntry->sRaw.uEntry.sFatRawCommon.uiAccessDate = psNewEntry->sRaw.uEntry.sFatRawCommon.uiCreateDate;
psNewEntry->tCreateTime = FatDecodeDateTime(psNewEntry->sRaw.uEntry.sFatRawCommon.uiCreateDate, psNewEntry->sRaw.uEntry.sFatRawCommon.uiCreateTime);
psNewEntry->tModifyTime = FatDecodeDateTime(psNewEntry->sRaw.uEntry.sFatRawCommon.uiModifyDate, psNewEntry->sRaw.uEntry.sFatRawCommon.uiModifyTime);
psNewEntry->tAccessTime = FatDecodeDateTime(psNewEntry->sRaw.uEntry.sFatRawCommon.uiAccessDate, 0);
}
uint16 CFatVolume::LongNameCharToWideChar(uint16 uiLFNIndex, uint16 uiNameLength, const char* szName, uint16 uiNameIndex)
{
if (uiLFNIndex + uiNameIndex > uiNameLength)
{
return 0xFFFF;
}
else
{
return (uint16)szName[uiLFNIndex + uiNameIndex];
}
}
void CFatVolume::GenerateDirectoryEntryNameParts(uint8* aui, uint16 uiLFNIndex, uint16 uiNameLength, const char* szName, uint16 uiNameIndex)
{
uint16 uiWideChar;
uiWideChar = LongNameCharToWideChar(uiLFNIndex, uiNameLength, szName, uiNameIndex);
aui[0x0] = (uint8)uiWideChar;
aui[0x1] = (uint8)(uiWideChar >> 8);
}
void CFatVolume::InitialiseParentEntry(SFatRawDirectoryEntry* psParentEntry, const char* szName, char uiChecksum, int iLFNEntriesNeeded, int iLFNEntriesFound)
{
uint16 uiLFNIndex;
uint16 uiNameLength;
psParentEntry->uEntry.sFatRawLongFileName.uiChecksum = uiChecksum;
psParentEntry->uEntry.sFatRawCommon.uiAttributes = (0x1 | 0x2 | 0x4 | 0x8);
psParentEntry->uEntry.sFatRawLongFileName.uiFirstCluster = 0;
psParentEntry->uEntry.sFatRawLongFileName.uiType = 0;
if (iLFNEntriesFound == iLFNEntriesNeeded - 1)
{
psParentEntry->uEntry.sFatRawLongFileName.uiSequence = (uint8)iLFNEntriesFound | 0x40;
}
else
{
psParentEntry->uEntry.sFatRawLongFileName.uiSequence = (uint8)iLFNEntriesFound;
}
uiNameLength = (uint16)strlen(szName);
uiLFNIndex = ((iLFNEntriesFound - 1) * 13);
GenerateDirectoryEntryNameParts(&psParentEntry->uEntry.sFatRawLongFileName.auiChars1[0x0], uiLFNIndex, uiNameLength, szName, 0x0);
GenerateDirectoryEntryNameParts(&psParentEntry->uEntry.sFatRawLongFileName.auiChars1[0x2], uiLFNIndex, uiNameLength, szName, 0x1);
GenerateDirectoryEntryNameParts(&psParentEntry->uEntry.sFatRawLongFileName.auiChars1[0x4], uiLFNIndex, uiNameLength, szName, 0x2);
GenerateDirectoryEntryNameParts(&psParentEntry->uEntry.sFatRawLongFileName.auiChars1[0x6], uiLFNIndex, uiNameLength, szName, 0x3);
GenerateDirectoryEntryNameParts(&psParentEntry->uEntry.sFatRawLongFileName.auiChars1[0x8], uiLFNIndex, uiNameLength, szName, 0x4);
GenerateDirectoryEntryNameParts(&psParentEntry->uEntry.sFatRawLongFileName.auiChars2[0x0], uiLFNIndex, uiNameLength, szName, 0x5);
GenerateDirectoryEntryNameParts(&psParentEntry->uEntry.sFatRawLongFileName.auiChars2[0x2], uiLFNIndex, uiNameLength, szName, 0x6);
GenerateDirectoryEntryNameParts(&psParentEntry->uEntry.sFatRawLongFileName.auiChars2[0x4], uiLFNIndex, uiNameLength, szName, 0x7);
GenerateDirectoryEntryNameParts(&psParentEntry->uEntry.sFatRawLongFileName.auiChars2[0x6], uiLFNIndex, uiNameLength, szName, 0x8);
GenerateDirectoryEntryNameParts(&psParentEntry->uEntry.sFatRawLongFileName.auiChars2[0x8], uiLFNIndex, uiNameLength, szName, 0x9);
GenerateDirectoryEntryNameParts(&psParentEntry->uEntry.sFatRawLongFileName.auiChars2[0xA], uiLFNIndex, uiNameLength, szName, 0xA);
GenerateDirectoryEntryNameParts(&psParentEntry->uEntry.sFatRawLongFileName.auiChars3[0x0], uiLFNIndex, uiNameLength, szName, 0xB);
GenerateDirectoryEntryNameParts(&psParentEntry->uEntry.sFatRawLongFileName.auiChars3[0x2], uiLFNIndex, uiNameLength, szName, 0xC);
}
EFatCode CFatVolume::ValidateFatCache(SFatCache sCache)
{
if (mcSectorCache.ValidateTimeStamp(sCache))
{
return FAT_SUCCESS;
}
else
{
return FAT_INVALID_FAT_CACHE;
}
}
fatEntry CFatVolume::GetDirectoryCluster(SFatRawDirectoryEntry* psParentDirectory)
{
fatEntry uiDirectoryCluster;
if ((psParentDirectory != 0L) && (psParentDirectory->uEntry.sFatRawCommon.uiFirstClusterLowWord != 0 || psParentDirectory->uEntry.sFatRawCommon.uiFirstClusterHighWord != 0))
{
uiDirectoryCluster = GetFirstClusterFromFatEntry(psParentDirectory, meFileSystem == FAT_FS_TYPE_FAT32);
}
else
{
uiDirectoryCluster = GetRootCluster();
}
return uiDirectoryCluster;
}
uint32 CFatVolume::GetDirectorySector(SFatRawDirectoryEntry* psParentDirectory)
{
uint32 uiFirstSectorOfCluster;
if ((psParentDirectory != 0L) && (psParentDirectory->uEntry.sFatRawCommon.uiFirstClusterLowWord != 0 || psParentDirectory->uEntry.sFatRawCommon.uiFirstClusterHighWord != 0))
{
uiFirstSectorOfCluster = 0;
}
else
{
uiFirstSectorOfCluster = GetRootSector();
}
return uiFirstSectorOfCluster;
}
EFatCode CFatVolume::FindEnoughEntries(fatEntry* puiLastDirectoryCluster, fatEntry* puiDirectoryCluster, uint32* puiFirstSectorOfCluster, uint32* puiSector, int* piLFNEntriesFound, SFatRawDirectoryEntry** ppsParentEntry, SFatRawDirectoryEntry* psParentDirectory, int iLFNEntriesNeeded)
{
uint32 uiFirstSectorOfCluster;
fatEntry uiDirectoryCluster;
EFatCode eResult;
uint32 uiSector;
int iLFNEntriesFound;
bool bAllLFNEntriesFound;
SFatCache sBuffer;
SFatRawDirectoryEntry* psParentEntry;
uintptr_t puiLastEntryAddress;
uint16 uiDirectoryEntries;
uiDirectoryCluster = GetDirectoryCluster(psParentDirectory);
uiFirstSectorOfCluster = GetDirectorySector(psParentDirectory);
uiDirectoryEntries = 0;
iLFNEntriesFound = 0;
bAllLFNEntriesFound = false;
sBuffer.Clear();
psParentEntry = 0L;
for (;;)
{
if (!IsRootDirectoryCluster(uiDirectoryCluster))
{
uiFirstSectorOfCluster = CalculateFirstSectorOfCluster(uiDirectoryCluster);
}
uiSector = uiFirstSectorOfCluster;
while (IsRootDirectoryCluster(uiDirectoryCluster) || uiSector < (uiFirstSectorOfCluster + NumSectorsPerCluster()))
{
sBuffer = mcSectorCache.ReadSector(uiSector); if (!sBuffer.IsValid()) { return FAT_CANNOT_READ_MEDIA; };
puiLastEntryAddress = ((uintptr_t)sBuffer.Get() + GetSectorSize()) - 0x20;
psParentEntry = (SFatRawDirectoryEntry*)sBuffer.Get();
while ((uintptr_t)psParentEntry <= puiLastEntryAddress)
{
if ((uiDirectoryEntries + iLFNEntriesNeeded) == 0xFFFF)
{
return FAT_DIRECTORY_LIMIT_EXCEEDED;
}
uiDirectoryEntries++;
if (IsFreeDirectoryEntry(psParentEntry))
{
iLFNEntriesFound++;
if (IsLastDirectoryEntry(psParentEntry) || iLFNEntriesFound == iLFNEntriesNeeded)
{
bAllLFNEntriesFound = true;
break;
}
}
else
{
iLFNEntriesFound = 0;
}
psParentEntry++;
}
if (bAllLFNEntriesFound)
{
break;
}
uiSector++;
if (IsRootDirectoryCluster(uiDirectoryCluster))
{
if (uiSector > uiFirstSectorOfCluster + GetRootDirectorySectors())
{
return FAT_ROOT_DIRECTORY_LIMIT_EXCEEDED;
}
}
}
if (bAllLFNEntriesFound)
{
break;
}
*puiLastDirectoryCluster = uiDirectoryCluster;
eResult = GetNextClusterEntry(uiDirectoryCluster, &uiDirectoryCluster);
if (eResult != FAT_SUCCESS) { return eResult; };
if (FatIsEOFEntry(uiDirectoryCluster))
{
fatEntry uiNewFat;
uiNewFat = AllocateDataCluster(1, true, &eResult, GetEndOfClusterMarker());
if (eResult != FAT_SUCCESS) { return eResult; };
eResult = SetClusterEntry(*puiLastDirectoryCluster, uiNewFat);
if (eResult != FAT_SUCCESS) { return eResult; };
uiDirectoryCluster = uiNewFat;
}
}
*puiDirectoryCluster = uiDirectoryCluster;
*ppsParentEntry = psParentEntry;
*puiSector = uiSector;
*piLFNEntriesFound = iLFNEntriesFound;
*puiFirstSectorOfCluster = uiFirstSectorOfCluster;
return FAT_SUCCESS;
}
EFatCode CFatVolume::RewindFoundEntries(SFatRawDirectoryEntry** ppsParentEntry, uint32* puiFirstSectorOfCluster, fatEntry* puiDirectoryCluster, int iLFNEntriesFound, fatEntry uiLastDirectoryCluster, uint32 uiSector)
{
uintptr_t puiLastEntryAddress;
SFatCache sBuffer;
SFatRawDirectoryEntry* psParentEntry;
uint32 uiFirstSectorOfCluster;
fatEntry uiDirectoryCluster;
uiFirstSectorOfCluster = *puiFirstSectorOfCluster;
uiDirectoryCluster = *puiDirectoryCluster;
psParentEntry = *ppsParentEntry;
while (iLFNEntriesFound > 1)
{
sBuffer = mcSectorCache.ReadSector(uiSector); if (!sBuffer.IsValid()) { return FAT_CANNOT_READ_MEDIA; };
puiLastEntryAddress = ((uintptr_t)sBuffer.Get() + GetSectorSize()) - 0x20;
if ((uintptr_t)psParentEntry > (uintptr_t)sBuffer.Get())
{
psParentEntry--;
}
else
{
if (uiSector > uiFirstSectorOfCluster)
{
uiSector--;
}
else
{
if (IsRootDirectoryCluster(uiLastDirectoryCluster))
{
uiFirstSectorOfCluster = GetRootDirectorySector();
}
else
{
uiDirectoryCluster = uiLastDirectoryCluster;
uiFirstSectorOfCluster = CalculateFirstSectorOfCluster(uiDirectoryCluster);
}
uiSector = uiFirstSectorOfCluster + NumSectorsPerCluster();
}
sBuffer = mcSectorCache.ReadSector(uiSector); if (!sBuffer.IsValid()) { return FAT_CANNOT_READ_MEDIA; };
puiLastEntryAddress = ((uintptr_t)sBuffer.Get() + GetSectorSize()) - 0x20;
psParentEntry = (SFatRawDirectoryEntry*)puiLastEntryAddress;
}
iLFNEntriesFound--;
}
*ppsParentEntry = psParentEntry;
*puiFirstSectorOfCluster = uiFirstSectorOfCluster;
*puiDirectoryCluster = uiDirectoryCluster;
return FAT_SUCCESS;
}
EFatCode CFatVolume::CheckEntryName(const char* szName)
{
uint16 uiLength;
uiLength = (uint16)strlen(szName);
if (uiLength > 255)
{
return FAT_FILENAME_TOO_LONG;
}
if (IsIllegalFilename(szName, uiLength))
{
return FAT_INVALID_FILENAME;
}
return FAT_SUCCESS;
}
EFatCode CFatVolume::IncrementDirectorySector(uint32* puiSector, uint32 uiFirstSectorOfCluster, fatEntry uiDirectoryCluster)
{
(*puiSector)++;
if (IsRootDirectoryCluster(uiDirectoryCluster))
{
if ((*puiSector) > uiFirstSectorOfCluster + GetRootDirectorySectors())
{
return FAT_ROOT_DIRECTORY_LIMIT_EXCEEDED;
}
}
return FAT_SUCCESS;
}
EFatCode CFatVolume::IncrementOrAllocateDirectoryCluster(uint32* puiSector, fatEntry* puiDirectoryCluster, fatEntry uiLastDirectoryCluster)
{
EFatCode eResult;
eResult = GetNextClusterEntry(*puiDirectoryCluster, puiDirectoryCluster);
if (eResult != FAT_SUCCESS) { return eResult; };
if (FatIsEOFEntry(*puiDirectoryCluster))
{
fatEntry uiNewFat = AllocateDataCluster(1, true, &eResult, uiLastDirectoryCluster);
if (eResult != FAT_SUCCESS) { return eResult; };
eResult = SetClusterEntry(uiLastDirectoryCluster, uiNewFat);
if (eResult != FAT_SUCCESS) { return eResult; };
*puiDirectoryCluster = uiNewFat;
}
*puiSector = CalculateFirstSectorOfCluster(*puiDirectoryCluster);
return FAT_SUCCESS;
}
EFatCode CFatVolume::WriteFATEntry(SFatDirectoryEntry* psNewEntry, const char* szName, SFatRawDirectoryEntry* psParentDirectory, int iLFNEntriesNeeded)
{
EFatCode eResult;
uint32 uiSector;
int iLFNEntriesFound;
uint32 uiFirstSectorOfCluster;
fatEntry uiDirectoryCluster;
fatEntry uiLastDirectoryCluster;
char uiChecksum;
SFatCache sBuffer;
uintptr_t puiLastEntryAddress;
SFatRawDirectoryEntry* psParentEntry;
iLFNEntriesFound = 0;
uiSector = 0;
uiDirectoryCluster = 0;
uiFirstSectorOfCluster = 0;
uiLastDirectoryCluster = 0;
eResult = FindEnoughEntries(&uiLastDirectoryCluster, &uiDirectoryCluster, &uiFirstSectorOfCluster, &uiSector, &iLFNEntriesFound, &psParentEntry, psParentDirectory, iLFNEntriesNeeded);
if (eResult != FAT_SUCCESS) { return eResult; };
eResult = RewindFoundEntries(&psParentEntry, &uiFirstSectorOfCluster, &uiDirectoryCluster, iLFNEntriesFound, uiLastDirectoryCluster, uiSector);
if (eResult != FAT_SUCCESS) { return eResult; };
uiChecksum = FatLongEntryChecksum((char*)psNewEntry->sRaw.uEntry.sFatRawCommon.szShortName);
iLFNEntriesFound = iLFNEntriesNeeded;
while (iLFNEntriesFound--)
{
if (iLFNEntriesFound > 0)
{
sBuffer = mcSectorCache.ReadSector(uiSector); if (!sBuffer.IsValid()) { return FAT_CANNOT_READ_MEDIA; };
puiLastEntryAddress = ((uintptr_t)sBuffer.Get() + GetSectorSize()) - 0x20;
InitialiseParentEntry(psParentEntry, szName, uiChecksum, iLFNEntriesNeeded, iLFNEntriesFound);
DirtySector(sBuffer);
if ((uintptr_t)psParentEntry < (uintptr_t)puiLastEntryAddress)
{
psParentEntry++;
}
else
{
if (IsRootDirectoryCluster(uiDirectoryCluster) || uiSector < uiFirstSectorOfCluster + NumSectorsPerCluster() - 1)
{
eResult = IncrementDirectorySector(&uiSector, uiFirstSectorOfCluster, uiDirectoryCluster);
if (eResult != FAT_SUCCESS) { return eResult; };
}
else
{
uiLastDirectoryCluster = uiDirectoryCluster;
eResult = IncrementOrAllocateDirectoryCluster(&uiSector, &uiDirectoryCluster, uiLastDirectoryCluster);
if (eResult != FAT_SUCCESS) { return eResult; };
}
sBuffer = mcSectorCache.ReadSector(uiSector); if (!sBuffer.IsValid()) { return FAT_CANNOT_READ_MEDIA; };
puiLastEntryAddress = ((uintptr_t)sBuffer.Get() + GetSectorSize()) - 0x20;
psParentEntry = (SFatRawDirectoryEntry*)sBuffer.Get();
}
}
else
{
eResult = ValidateFatCache(sBuffer);
if (eResult != FAT_SUCCESS) { return eResult; };
*psParentEntry = psNewEntry->sRaw;
DirtySector(sBuffer);
}
}
eResult = ValidateFatCache(sBuffer);
if (eResult != FAT_SUCCESS) { return eResult; };
psNewEntry->uiSectorAddress = uiSector;
psNewEntry->uiSectorOffset = (uint16)((uintptr_t)psParentEntry - (uintptr_t)sBuffer.Get());
return FAT_SUCCESS;
}
EFatCode CFatVolume::CreateFATEntry(SFatRawDirectoryEntry* psParentDirectory, const char* szName, uint8 uiAttributes, uint32 uiEntryCluster, SFatDirectoryEntry* psNewEntry)
{
EFatCode eResult;
int iLFNEntriesNeeded;
eResult = CheckEntryName(szName);
if (eResult != FAT_SUCCESS) { return eResult; };
memset(&psNewEntry->sRaw, 0, sizeof(SFatRawDirectoryEntry));
eResult = GetFatShortNameForEntry((char*)psNewEntry->sRaw.uEntry.sFatRawCommon.szShortName, szName, false);
if (eResult != FAT_SUCCESS && eResult != FAT_LFN_GENERATED)
{
return FAT_INVALID_FILENAME;
}
if (eResult == FAT_LFN_GENERATED)
{
eResult = GenerateUniqueShortNameWithSuffix(psParentDirectory, psNewEntry->sRaw.uEntry.sFatRawCommon.szShortName);
if (eResult != FAT_SUCCESS) { return eResult; };
iLFNEntriesNeeded = (int)((strlen(szName) + 12) / 13) + 1;
}
else
{
iLFNEntriesNeeded = 0;
}
if (IsRootDirectoryCluster(uiEntryCluster) && (uiAttributes & 0x10))
{
uiEntryCluster = AllocateDirectoryCluster(psParentDirectory, &eResult);
if (eResult != FAT_SUCCESS) { return eResult; };
}
InitialiseNewEntry(psNewEntry, szName, uiAttributes, uiEntryCluster);
eResult = WriteFATEntry(psNewEntry, szName, psParentDirectory, iLFNEntriesNeeded);
return eResult;
}
EFatCode CFatVolume::CreateDirectory(const char* szDirectory, SFatDirectoryEntry* psEntry)
{
size uiPathLength;
const char* szPathScanner;
char szFilePath[260 + 1];
SFatDirectoryEntry sParentEntry;
EFatCode eResult;
uiPathLength = strlen(szDirectory);
szPathScanner = szDirectory + (uiPathLength - 0x1);
if (szPathScanner[0] == '\\')
{
return FAT_INVALID_FILENAME;
}
szPathScanner = StepPathToSlash(szPathScanner);
uiPathLength = (size)(szPathScanner - szDirectory);
memcpy(szFilePath, szDirectory, uiPathLength);
szFilePath[uiPathLength] = '\0';
szPathScanner++;
eResult = GetFileEntry(szFilePath, &sParentEntry);
if (eResult != FAT_SUCCESS) { return eResult; };
if (sParentEntry.szName[0] == '\0')
{
return FAT_DIRECTORY_DOES_NOT_EXIST;
}
eResult = CreateFATEntry(&sParentEntry.sRaw, szPathScanner, 0x10, 0, psEntry);
return eResult;
}
EFatCode CFatVolume::CreateDirectory(const char* szDirectory)
{
EFatCode eResult;
SFatDirectoryEntry sEntry;
if (StrEmpty(szDirectory) || strlen(szDirectory) > 260)
{
return FAT_INVALID_FILENAME;
}
eResult = GetFileEntry(szDirectory, &sEntry);
if (eResult != FAT_SUCCESS) { return eResult; };
if (sEntry.szName[0] == '\0')
{
eResult = CreateDirectory(szDirectory, &sEntry);
return eResult;
}
return FAT_FILENAME_ALREADY_EXISTS;
}
EFatCode CFatVolume::GetFileEntry(const char* szPath, SFatDirectoryEntry* psEntry)
{
EFatCode eResult;
bool bMatch;
char szConstructedShortFileName[13];
SFatRawDirectoryEntry* psCurrentEntry;
SFatQueryState sQuery;
bool bLongFilename;
uint16 auiConstructedLongFilename[260 + 1];
char szCurrentLevelPath[260 + 1];
szPath = StepPathOverSlash(szPath);
if (szPath[0] != '\0')
{
psCurrentEntry = 0L;
}
else
{
return CreateFakeRootEntry(psEntry);
}
memset(szCurrentLevelPath, 0, 260 + 1);
sQuery.Init();
do
{
szPath = FindNextPathItem(szPath, szCurrentLevelPath);
if (szPath == 0L)
{
eResult = FAT_INVALID_FILENAME;
break;
}
eResult = QueryFirstEntry(psCurrentEntry, 0, &sQuery, true);
if (eResult != FAT_SUCCESS)
{
break;
}
if (sQuery.psCurrentEntryRaw->uEntry.sFatRawCommon.szShortName[0] == '\0')
{
psEntry->szName[0] = '\0';
sQuery.Kill(GetSectorCache());
return FAT_SUCCESS;
}
eResult = MatchesFatFileName(&bMatch, &bLongFilename, szConstructedShortFileName, auiConstructedLongFilename, szCurrentLevelPath, sQuery.auiLongFilename, sQuery.psCurrentEntryRaw->uEntry.sFatRawCommon.szShortName);
if (eResult != FAT_SUCCESS)
{
break;
}
while (!bMatch)
{
eResult = QueryNextEntry(&sQuery, true, false);
if (eResult != FAT_SUCCESS)
{
break;
}
eResult = ValidateFatCache(sQuery.sBuffer);
if (eResult != FAT_SUCCESS) { return eResult; };
if (IsLastDirectoryEntry(sQuery.psCurrentEntryRaw))
{
psEntry->szName[0] = '\0';
sQuery.Kill(GetSectorCache());
return FAT_SUCCESS;
}
if (bLongFilename)
{
bMatch = CompareFatLongName(auiConstructedLongFilename, sQuery.auiLongFilename) || CompareFatShortName(szConstructedShortFileName, (char*)sQuery.psCurrentEntryRaw->uEntry.sFatRawCommon.szShortName);
}
else
{
bMatch = CompareFatShortName(szConstructedShortFileName, (char*)sQuery.psCurrentEntryRaw->uEntry.sFatRawCommon.szShortName);
}
}
if (eResult != FAT_SUCCESS)
{
break;
}
psCurrentEntry = sQuery.psCurrentEntryRaw;
}
while (szPath[0] != '\0');
if (eResult == FAT_SUCCESS)
{
eResult = ValidateFatCache(sQuery.sBuffer);
if (eResult != FAT_SUCCESS) { return eResult; };
ConvertFATShortInternalNameInto8Dot3Format(psEntry->szName, (uint8*)sQuery.psCurrentEntryRaw->uEntry.sFatRawCommon.szShortName);
psEntry->uiAttributes = sQuery.psCurrentEntryRaw->uEntry.sFatRawCommon.uiAttributes;
psEntry->uiSize = sQuery.psCurrentEntryRaw->uEntry.sFatRawCommon.uiSize;
psEntry->tCreateTime = FatDecodeDateTime(sQuery.psCurrentEntryRaw->uEntry.sFatRawCommon.uiCreateDate, sQuery.psCurrentEntryRaw->uEntry.sFatRawCommon.uiCreateTime);
psEntry->tModifyTime = FatDecodeDateTime(sQuery.psCurrentEntryRaw->uEntry.sFatRawCommon.uiModifyDate, sQuery.psCurrentEntryRaw->uEntry.sFatRawCommon.uiModifyTime);
psEntry->tAccessTime = FatDecodeDateTime(sQuery.psCurrentEntryRaw->uEntry.sFatRawCommon.uiAccessDate, 0);
if (IsRootDirectoryCluster(sQuery.uiCurrentCluster))
{
psEntry->uiSectorAddress = GetRootDirectorySector() + sQuery.uiCurrentSector;
}
else
{
psEntry->uiSectorAddress = CalculateFirstSectorOfCluster(sQuery.uiCurrentCluster) + sQuery.uiCurrentSector;
}
psEntry->uiSectorOffset = (uint16)((uintptr_t)sQuery.psCurrentEntryRaw - (uintptr_t)sQuery.psFirstEntryRaw);
psEntry->sRaw = *sQuery.psCurrentEntryRaw;
}
sQuery.Kill(GetSectorCache());
return eResult;
}
EFatCode CFatVolume::Delete(SFatDirectoryEntry* psEntry, const char* szNamePart, char* szPathPart, uint8 uiChecksum)
{
EFatCode eResult;
SFatFileSystemQuery sQuery;
SFatCache sBuffer;
sQuery.Init();
eResult = FindFirstFATEntry(szPathPart, (0x1 | 0x2 | 0x4 | 0x8), 0, &sQuery);
if (eResult == FAT_SUCCESS)
{
while (sQuery.sCurrentEntry.sRaw.uEntry.sFatRawCommon.szShortName[0] != '\0')
{
if (sQuery.sCurrentEntry.sRaw.uEntry.sFatRawLongFileName.uiChecksum == uiChecksum)
{
sQuery.sCurrentEntry.sRaw.uEntry.sFatRawCommon.szShortName[0] = (char)0xE5;
sBuffer = mcSectorCache.ReadSector(sQuery.sCurrentEntry.uiSectorAddress);
if (!sBuffer.IsValid())
{
eResult = FAT_CANNOT_READ_MEDIA;
break;
}
memcpy(sBuffer.Get() + sQuery.sCurrentEntry.uiSectorOffset, &sQuery.sCurrentEntry.sRaw, sizeof(psEntry->sRaw));
DirtySector(sBuffer);
}
eResult = FindNextFATEntry(0, &sQuery);
if (eResult != FAT_SUCCESS)
{
break;
}
}
}
sQuery.Kill(GetSectorCache());
return eResult;
}
EFatCode CFatVolume::Delete(const char* szFilename)
{
EFatCode eResult;
uint32 uiFirstCluster;
SFatDirectoryEntry sEntry;
char szPathPart[260];
const char* szNamePart;
uint8 uiChecksum;
SFatCache sBuffer;
eResult = GetFileEntry(szFilename, &sEntry);
if (eResult != FAT_SUCCESS) { return eResult; };
if (sEntry.szName[0] != '\0')
{
uiChecksum = FatLongEntryChecksum((char*)sEntry.sRaw.uEntry.sFatRawCommon.szShortName);
if (sEntry.uiAttributes & 0x10)
{
return FAT_NOT_A_FILE;
}
uiFirstCluster = GetFirstClusterFromFatEntry(&sEntry.sRaw, meFileSystem == FAT_FS_TYPE_FAT32);
if (uiFirstCluster)
{
eResult = FreeChain(uiFirstCluster);
if (eResult != FAT_SUCCESS) { return eResult; };
}
sEntry.sRaw.uEntry.sFatRawCommon.szShortName[0] = (char)0xE5;
sBuffer = mcSectorCache.ReadSector(sEntry.uiSectorAddress); if (!sBuffer.IsValid()) { return FAT_CANNOT_READ_MEDIA; };
memcpy(sBuffer.Get() + sEntry.uiSectorOffset, &sEntry.sRaw, sizeof(sEntry.sRaw));
DirtySector(sBuffer);
}
else
{
return FAT_FILE_NOT_FOUND;
}
ParsePathAndFilename(szFilename, szPathPart, &szNamePart);
eResult = Delete(&sEntry, szNamePart, szPathPart, uiChecksum);
return eResult;
}
void CFatVolume::CopyRawEntry(SFatDirectoryEntry* psOriginalEntry, SFatDirectoryEntry* psNewEntry)
{
psNewEntry->sRaw.uEntry.sFatRawCommon.uiAccessDate = psOriginalEntry->sRaw.uEntry.sFatRawCommon.uiAccessDate;
psNewEntry->sRaw.uEntry.sFatRawCommon.uiAttributes = psOriginalEntry->sRaw.uEntry.sFatRawCommon.uiAttributes;
psNewEntry->sRaw.uEntry.sFatRawCommon.uiCreateDate = psOriginalEntry->sRaw.uEntry.sFatRawCommon.uiCreateDate;
psNewEntry->sRaw.uEntry.sFatRawCommon.uiCreateTime = psOriginalEntry->sRaw.uEntry.sFatRawCommon.uiCreateTime;
psNewEntry->sRaw.uEntry.sFatRawCommon.uiCreateTimeTenths = psOriginalEntry->sRaw.uEntry.sFatRawCommon.uiCreateTimeTenths;
psNewEntry->sRaw.uEntry.sFatRawCommon.uiFirstClusterHighWord = psOriginalEntry->sRaw.uEntry.sFatRawCommon.uiFirstClusterHighWord;
psNewEntry->sRaw.uEntry.sFatRawCommon.uiFirstClusterLowWord = psOriginalEntry->sRaw.uEntry.sFatRawCommon.uiFirstClusterLowWord;
psNewEntry->sRaw.uEntry.sFatRawCommon.uiModifyDate = psOriginalEntry->sRaw.uEntry.sFatRawCommon.uiModifyDate;
psNewEntry->sRaw.uEntry.sFatRawCommon.uiModifyTime = psOriginalEntry->sRaw.uEntry.sFatRawCommon.uiModifyTime;
psNewEntry->sRaw.uEntry.sFatRawCommon.uiReserved = psOriginalEntry->sRaw.uEntry.sFatRawCommon.uiReserved;
psNewEntry->sRaw.uEntry.sFatRawCommon.uiSize = psOriginalEntry->sRaw.uEntry.sFatRawCommon.uiSize;
}
EFatCode CFatVolume::Rename(const char* szOriginalParent, uint8 uiChecksum)
{
SFatFileSystemQuery sQuery;
EFatCode eResult;
SFatCache sBuffer;
sQuery.Init();
eResult = FindFirstFATEntry(szOriginalParent, (0x1 | 0x2 | 0x4 | 0x8), 0, &sQuery);
if (eResult == FAT_SUCCESS)
{
while (sQuery.sCurrentEntry.sRaw.uEntry.sFatRawCommon.szShortName[0] != '\0')
{
if (sQuery.sCurrentEntry.sRaw.uEntry.sFatRawLongFileName.uiChecksum == uiChecksum)
{
sQuery.sCurrentEntry.sRaw.uEntry.sFatRawCommon.szShortName[0] = (char)0xE5;
sBuffer = mcSectorCache.ReadSector(sQuery.sCurrentEntry.uiSectorAddress);
if (!sBuffer.IsValid())
{
eResult = FAT_CANNOT_READ_MEDIA;
break;
}
memcpy(sBuffer.Get() + sQuery.sCurrentEntry.uiSectorOffset, &sQuery.sCurrentEntry.sRaw, sizeof(sQuery.sCurrentEntry.sRaw));
DirtySector(sBuffer);
}
eResult = FindNextFATEntry(0, &sQuery);
if (eResult != FAT_SUCCESS)
{
break;
}
}
}
sQuery.Kill(GetSectorCache());
return eResult;
}
EFatCode CFatVolume::Rename(const char* szOriginalFilename, const char* szNewFilename)
{
EFatCode eResult;
uint32 uiEntryCluster;
char szNewParent[256];
const char* szOriginalFilenamePart;
SFatDirectoryEntry sOriginalEntry;
SFatDirectoryEntry sNewEntry;
uint8 uiChecksum = 0;
char szOriginalParent[256];
const char* szNewFilenamePart;
SFatCache sBuffer;
ParsePathAndFilename(szOriginalFilename, szOriginalParent, &szOriginalFilenamePart);
ParsePathAndFilename(szNewFilename, szNewParent, &szNewFilenamePart);
GetFileEntry(szNewFilename, &sNewEntry);
if (*sNewEntry.szName != 0)
{
return FAT_FILENAME_ALREADY_EXISTS;
}
GetFileEntry(szOriginalFilename, &sOriginalEntry);
if (sOriginalEntry.szName[0] != '\0')
{
SFatDirectoryEntry parent;
uiChecksum = FatLongEntryChecksum((char*)sOriginalEntry.sRaw.uEntry.sFatRawCommon.szShortName);
uiEntryCluster = GetFirstClusterFromFatEntry(&sOriginalEntry.sRaw, GetFileSystemType() == FAT_FS_TYPE_FAT32);
eResult = GetFileEntry(szNewParent, &parent);
if (eResult != FAT_SUCCESS) { return eResult; };
eResult = CreateFATEntry(&parent.sRaw, szNewFilenamePart, sOriginalEntry.uiAttributes, uiEntryCluster, &sNewEntry);
if (eResult != FAT_SUCCESS) { return eResult; };
CopyRawEntry(&sOriginalEntry, &sNewEntry);
sBuffer = mcSectorCache.ReadSector(sNewEntry.uiSectorAddress); if (!sBuffer.IsValid()) { return FAT_CANNOT_READ_MEDIA; };
memcpy(sBuffer.Get() + sNewEntry.uiSectorOffset, &sNewEntry.sRaw, sizeof(sNewEntry.sRaw));
DirtySector(sBuffer);
sOriginalEntry.sRaw.uEntry.sFatRawCommon.szShortName[0] = (char)0xE5;
sBuffer = mcSectorCache.ReadSector(sOriginalEntry.uiSectorAddress); if (!sBuffer.IsValid()) { return FAT_CANNOT_READ_MEDIA; };
memcpy(sBuffer.Get() + sOriginalEntry.uiSectorOffset, &sOriginalEntry.sRaw, sizeof(sOriginalEntry.sRaw));
DirtySector(sBuffer);
}
else
{
return FAT_FILE_NOT_FOUND;
}
eResult = Rename(szOriginalParent, uiChecksum);
return eResult;
}
uint32 CFatVolume::GetClusterSize(void) { return muiBytesPerCluster; }
uint32 CFatVolume::GetID(void) { return muiID; }
uint32 CFatVolume::GetFatSize(void) { return muiFatSize; }
uint32 CFatVolume::GetRootCluster(void) { return muiRootCluster; }
uint32 CFatVolume::GetRootSector(void) { return muiRootSector; }
uint32 CFatVolume::GetFirstDataSector(void) { return muiFirstDataSector; }
uint32 CFatVolume::GetNoOfSectors(void) { return muiNoOfSectors; }
uint32 CFatVolume::GetNoOfDataSectors(void) { return muiNoOfDataSectors; }
uint32 CFatVolume::GetNumClusters(void) { return muiNoOfClusters; }
uint32 CFatVolume::GetNoOfReservedSectors(void) { return muiNoOfReservedSectors; }
uint32 CFatVolume::GetNextFreeCluster(void) { return muiNextFreeCluster; }
uint32 CFatVolume::GetTotalFreeClusters(void) { return muiTotalFreeClusters; }
uint32 CFatVolume::GetFileSystemInfoSector(void) { return muiFileSystemInfoSector; }
uint16 CFatVolume::GetRootDirectorySectors(void) { return muiRootDirectorySectors; }
uint16 CFatVolume::GetSectorSize(void) { return muiBytesPerSector; }
uint16 CFatVolume::NumSectorsPerCluster(void) { return muiNoOfSectorsPerCluster; }
bool CFatVolume::IsUseLongFilenames(void) { return mbUseLongFilenames; }
EFatFileSystemType CFatVolume::GetFileSystemType(void) { return meFileSystem; }
uint8 CFatVolume::GetNoOfFatTables(void) { return muiNoOfFatTables; }
char* CFatVolume::GetLabel(void) { return mszLabel.Text(); }
CFileDrive* CFatVolume::GetFileDrive(void) { return mpcDevice; }
CFatInfoSectorCache* CFatVolume::GetSectorCache(void) { return &mcSectorCache; }
