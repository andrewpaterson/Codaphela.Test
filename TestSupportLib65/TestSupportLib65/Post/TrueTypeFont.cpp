typedef unsigned long size_t;
typedef long ptrdiff_t;
typedef long long max_align_t;
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
typedef int64 filePos;
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
class CNaiveFile
{
protected:
CChars mszFilename;
void* mpvMem;
filePos miSize;
public:
CNaiveFile();
CNaiveFile* Init(void);
CNaiveFile* Init(void* pvMem, size iSize);
void Kill(void);
void KillExceptBuffer(void);
bool Read(const char* szFilename);
bool Read(CAbstractFile* pcAbstractFile);
bool Write(const char* szFilename);
void* Get(void);
void* Get(int iOffset);
void Set(void* pvMem, size iSize);
filePos Size(void);
filePos Length(void);
int Compare(void* pvOther, size iSize);
};
int CompareFileToMemory(const char* szFilename, void* pvMem, size iLength);
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
int64 DivideRound(int64 iNumerator, int64 iDenominator);
int64 DivideFloor(int64 iNumerator, int64 iDenominator);
int64 DivideCeiling(int64 iNumerator, int64 iDenominator);
int32 FixedFromInt(int32 i, int iFractionBits);
int32 FixedFromFloat(float32 f, int iFractionBits);
int32 FloatToIntScaled(float32 f, int32 iScale);
float32 FixedToFloat(int32 iFixed, int iFractionBits);
int32 FixedConvert(int32 iFixed, int iFromFractionBits, int iToFractionBits);
int32 FixedFloor(int32 iFixed, int iFractionBits);
int32 FixedCeiling(int32 iFixed, int iFractionBits);
int32 FixedRound(int32 iFixed, int iFractionBits);
int32 FixedFraction(int32 iFixed, int iFractionBits);
int32 FixedMultiply(int32 iA, int32 iB, int iFractionBits);
int32 FixedDivide(int32 iA, int32 iB, int iFractionBits);
int32 FixedMultiplyDivide(int32 iA, int32 iB, int32 iC);
int32 FixedSquareRoot(int32 iFixed, int iFractionBits);
struct STrueTypePoint
{
int32 x;
int32 y;
bool bOnCurve;
};
typedef CArrayTemplate<STrueTypePoint> CArrayTrueTypePoint;
class CTrueTypeOutline
{
public:
CArrayTrueTypePoint macPoints;
CArrayInt maiContourEnds;
void Init(void);
void Kill(void);
void Clear(void);
size NumContours(void);
size NumPoints(void);
STrueTypePoint* GetPoint(size iIndex);
size GetContourStart(size iContour);
size GetContourEnd(size iContour);
};
struct STrueTypeGlyphMetrics
{
int iAdvanceWidth;
int iLeftSideBearing;
int iXMin;
int iYMin;
int iXMax;
int iYMax;
};
class CTrueTypeFont
{
protected:
uint8* mpuiData;
size muiSize;
size muiHeadOffset;
size muiLocaOffset;
size muiLocaLength;
size muiGlyfOffset;
size muiGlyfLength;
size muiHmtxOffset;
size muiHmtxLength;
size muiNameOffset;
size muiNameLength;
size muiCmapOffset;
size muiCmapLength;
int miCmapFormat;
int miUnitsPerEm;
int miXMin;
int miYMin;
int miXMax;
int miYMax;
bool mbLongLoca;
int miNumGlyphs;
int miAscender;
int miDescender;
int miLineGap;
int miNumHMetrics;
bool mbHasPost;
int miUnderlinePosition;
int miUnderlineThickness;
bool mbHasOS2;
int miStrikeoutPosition;
int miStrikeoutSize;
int miSubscriptYSize;
int miSubscriptYOffset;
int miSuperscriptYSize;
int miSuperscriptYOffset;
public:
void Init(void);
void Kill(void);
bool Load(char* szFilename);
bool Load(void* pvData, size uiSize);
int NumGlyphs(void);
int GetUnitsPerEm(void);
int GetAscender(void);
int GetDescender(void);
int GetLineGap(void);
void GetBounds(int* piXMin, int* piYMin, int* piXMax, int* piYMax);
bool GetName(int iNameID, CChars* psz);
bool HasPost(void);
int GetUnderlinePosition(void);
int GetUnderlineThickness(void);
bool HasOS2(void);
int GetStrikeoutPosition(void);
int GetStrikeoutSize(void);
int GetSubscriptYSize(void);
int GetSubscriptYOffset(void);
int GetSuperscriptYSize(void);
int GetSuperscriptYOffset(void);
int GetGlyphIndex(uint32 uiCodePoint);
bool GetGlyphMetrics(int iGlyph, STrueTypeGlyphMetrics* psMetrics);
bool GetGlyphOutline(int iGlyph, CTrueTypeOutline* pcOutline);
protected:
bool Parse(void);
void ParsePost(void);
void ParseOS2(void);
bool FindTable(const char* szTag, size* puiOffset, size* puiLength);
bool ChooseCmap(size uiCmapOffset, size uiCmapLength);
int GetGlyphIndexFormat4(uint32 uiCodePoint);
int GetGlyphIndexFormat12(uint32 uiCodePoint);
bool GetGlyphData(int iGlyph, size* puiOffset, size* puiLength);
bool ReadSimpleGlyph(size uiOffset, size uiLength, int iNumContours, CTrueTypeOutline* pcOutline);
bool ReadCompositeGlyph(size uiOffset, size uiLength, CTrueTypeOutline* pcOutline, int iDepth);
bool ReadGlyph(int iGlyph, CTrueTypeOutline* pcOutline, int iDepth);
bool ReadUint8(size uiOffset, uint8* pui);
bool ReadUint16(size uiOffset, uint16* pui);
bool ReadInt16(size uiOffset, int16* pi);
bool ReadUint32(size uiOffset, uint32* pui);
bool IsInFile(size uiOffset, size uiLength);
};
void CTrueTypeFont::Init(void)
{
mpuiData = 0L;
muiSize = 0;
muiHeadOffset = 0;
muiLocaOffset = 0;
muiLocaLength = 0;
muiGlyfOffset = 0;
muiGlyfLength = 0;
muiHmtxOffset = 0;
muiHmtxLength = 0;
muiNameOffset = 0;
muiNameLength = 0;
muiCmapOffset = 0;
muiCmapLength = 0;
miCmapFormat = 0;
miUnitsPerEm = 0;
miXMin = 0;
miYMin = 0;
miXMax = 0;
miYMax = 0;
mbLongLoca = false;
miNumGlyphs = 0;
miAscender = 0;
miDescender = 0;
miLineGap = 0;
miNumHMetrics = 0;
mbHasPost = false;
miUnderlinePosition = 0;
miUnderlineThickness = 0;
mbHasOS2 = false;
miStrikeoutPosition = 0;
miStrikeoutSize = 0;
miSubscriptYSize = 0;
miSubscriptYOffset = 0;
miSuperscriptYSize = 0;
miSuperscriptYOffset = 0;
}
void CTrueTypeFont::Kill(void)
{
if (mpuiData)
{
free(mpuiData);
mpuiData = 0L;
}
muiSize = 0;
}
bool CTrueTypeFont::Load(char* szFilename)
{
CNaiveFile cNaiveFile;
bool bResult;
cNaiveFile.Init();
if (!cNaiveFile.Read(szFilename))
{
cNaiveFile.Kill();
gcLogger.Error2(MethodToString("/home/r2d2/Codaphela/commonlibraries/SupportLib/TrueTypeFont.cpp", 128, __PRETTY_FUNCTION__), " Could not read [", szFilename, "].", 0L);
return false;
}
bResult = Load(cNaiveFile.Get(), (size)cNaiveFile.Size());
cNaiveFile.Kill();
if (!bResult)
{
gcLogger.Error2(MethodToString("/home/r2d2/Codaphela/commonlibraries/SupportLib/TrueTypeFont.cpp", 136, __PRETTY_FUNCTION__), " [", szFilename, "] is not a supported TrueType font.", 0L);
}
return bResult;
}
bool CTrueTypeFont::Load(void* pvData, size uiSize)
{
Kill();
Init();
if (uiSize == 0)
{
return false;
}
mpuiData = (uint8*)malloc(uiSize);
if (mpuiData == 0L)
{
return false;
}
memcpy(mpuiData, pvData, uiSize);
muiSize = uiSize;
if (!Parse())
{
Kill();
Init();
return false;
}
return true;
}
bool CTrueTypeFont::IsInFile(size uiOffset, size uiLength)
{
return (uiOffset <= muiSize) && (uiLength <= muiSize - uiOffset);
}
bool CTrueTypeFont::ReadUint8(size uiOffset, uint8* pui)
{
if (!IsInFile(uiOffset, 1))
{
return false;
}
*pui = mpuiData[uiOffset];
return true;
}
bool CTrueTypeFont::ReadUint16(size uiOffset, uint16* pui)
{
if (!IsInFile(uiOffset, 2))
{
return false;
}
*pui = (uint16)((mpuiData[uiOffset] << 8) | mpuiData[uiOffset + 1]);
return true;
}
bool CTrueTypeFont::ReadInt16(size uiOffset, int16* pi)
{
uint16 ui;
if (!ReadUint16(uiOffset, &ui))
{
return false;
}
*pi = (int16)ui;
return true;
}
bool CTrueTypeFont::ReadUint32(size uiOffset, uint32* pui)
{
if (!IsInFile(uiOffset, 4))
{
return false;
}
*pui = ((uint32)mpuiData[uiOffset] << 24) | ((uint32)mpuiData[uiOffset + 1] << 16) | ((uint32)mpuiData[uiOffset + 2] << 8) | (uint32)mpuiData[uiOffset + 3];
return true;
}
bool CTrueTypeFont::FindTable(const char* szTag, size* puiOffset, size* puiLength)
{
uint16 uiNumTables;
uint16 i;
size uiRecord;
uint32 uiOffset;
uint32 uiLength;
if (!ReadUint16(4, &uiNumTables))
{
return false;
}
for (i = 0; i < uiNumTables; i++)
{
uiRecord = 12 + (size)i * 16;
if (!IsInFile(uiRecord, 16))
{
return false;
}
if (memcmp(&mpuiData[uiRecord], szTag, 4) == 0)
{
if (!ReadUint32(uiRecord + 8, &uiOffset) || !ReadUint32(uiRecord + 12, &uiLength) || !IsInFile(uiOffset, uiLength))
{
return false;
}
*puiOffset = uiOffset;
*puiLength = uiLength;
return true;
}
}
return false;
}
bool CTrueTypeFont::Parse(void)
{
uint32 uiVersion;
uint32 uiMagic;
uint16 uiUnitsPerEm;
int16 iXMin;
int16 iYMin;
int16 iXMax;
int16 iYMax;
int16 iLocaFormat;
uint16 uiNumGlyphs;
int16 iAscender;
int16 iDescender;
int16 iLineGap;
uint16 uiNumHMetrics;
size uiHeadLength;
size uiMaxpOffset;
size uiMaxpLength;
size uiHheaOffset;
size uiHheaLength;
size uiCmapOffset;
size uiCmapLength;
if (!ReadUint32(0, &uiVersion) || ((uiVersion != 0x00010000) && (uiVersion != 0x74727565)))
{
return false;
}
if (!FindTable("head", &muiHeadOffset, &uiHeadLength) || (uiHeadLength < 54) ||
!FindTable("maxp", &uiMaxpOffset, &uiMaxpLength) || (uiMaxpLength < 6) ||
!FindTable("hhea", &uiHheaOffset, &uiHheaLength) || (uiHheaLength < 36) ||
!FindTable("hmtx", &muiHmtxOffset, &muiHmtxLength) ||
!FindTable("loca", &muiLocaOffset, &muiLocaLength) ||
!FindTable("glyf", &muiGlyfOffset, &muiGlyfLength) ||
!FindTable("cmap", &uiCmapOffset, &uiCmapLength))
{
return false;
}
if (!ReadUint32(muiHeadOffset + 12, &uiMagic) || (uiMagic != 0x5F0F3CF5))
{
return false;
}
ReadUint16(muiHeadOffset + 18, &uiUnitsPerEm);
ReadInt16(muiHeadOffset + 36, &iXMin);
ReadInt16(muiHeadOffset + 38, &iYMin);
ReadInt16(muiHeadOffset + 40, &iXMax);
ReadInt16(muiHeadOffset + 42, &iYMax);
ReadInt16(muiHeadOffset + 50, &iLocaFormat);
ReadUint16(uiMaxpOffset + 4, &uiNumGlyphs);
ReadInt16(uiHheaOffset + 4, &iAscender);
ReadInt16(uiHheaOffset + 6, &iDescender);
ReadInt16(uiHheaOffset + 8, &iLineGap);
ReadUint16(uiHheaOffset + 34, &uiNumHMetrics);
if ((uiUnitsPerEm == 0) || (iLocaFormat < 0) || (iLocaFormat > 1) || (uiNumGlyphs == 0) || (uiNumHMetrics == 0) || (uiNumHMetrics > uiNumGlyphs))
{
return false;
}
miUnitsPerEm = uiUnitsPerEm;
miXMin = iXMin;
miYMin = iYMin;
miXMax = iXMax;
miYMax = iYMax;
mbLongLoca = iLocaFormat == 1;
miNumGlyphs = uiNumGlyphs;
miAscender = iAscender;
miDescender = iDescender;
miLineGap = iLineGap;
miNumHMetrics = uiNumHMetrics;
if (muiLocaLength < ((size)miNumGlyphs + 1) * (mbLongLoca ? 4 : 2))
{
return false;
}
if (muiHmtxLength < (size)miNumHMetrics * 4 + ((size)miNumGlyphs - miNumHMetrics) * 2)
{
return false;
}
ParsePost();
ParseOS2();
if (!FindTable("name", &muiNameOffset, &muiNameLength))
{
muiNameOffset = 0;
muiNameLength = 0;
}
return ChooseCmap(uiCmapOffset, uiCmapLength);
}
bool CTrueTypeFont::ChooseCmap(size uiCmapOffset, size uiCmapLength)
{
uint16 uiNumTables;
uint16 i;
size uiRecord;
uint16 uiPlatform;
uint16 uiEncoding;
uint32 uiSubtableOffset;
uint16 uiFormat;
uint16 uiLength16;
uint32 uiLength32;
bool bUnicode;
bool bFullUnicode;
size uiSubtable;
size uiSubtableLength;
if (!ReadUint16(uiCmapOffset + 2, &uiNumTables))
{
return false;
}
for (i = 0; i < uiNumTables; i++)
{
uiRecord = uiCmapOffset + 4 + (size)i * 8;
if (!ReadUint16(uiRecord, &uiPlatform) || !ReadUint16(uiRecord + 2, &uiEncoding) || !ReadUint32(uiRecord + 4, &uiSubtableOffset))
{
return false;
}
bUnicode = (uiPlatform == 0) || ((uiPlatform == 3) && (uiEncoding == 1));
bFullUnicode = (uiPlatform == 0) || ((uiPlatform == 3) && (uiEncoding == 10));
if (!bUnicode && !bFullUnicode)
{
continue;
}
if (uiSubtableOffset >= uiCmapLength)
{
continue;
}
uiSubtable = uiCmapOffset + uiSubtableOffset;
if (!ReadUint16(uiSubtable, &uiFormat))
{
continue;
}
if ((uiFormat == 12) && bFullUnicode)
{
if (!ReadUint32(uiSubtable + 4, &uiLength32) || !IsInFile(uiSubtable, uiLength32))
{
continue;
}
uiSubtableLength = uiLength32;
}
else if ((uiFormat == 4) && bUnicode && (miCmapFormat != 12))
{
if (!ReadUint16(uiSubtable + 2, &uiLength16) || !IsInFile(uiSubtable, uiLength16))
{
continue;
}
uiSubtableLength = uiLength16;
}
else
{
continue;
}
muiCmapOffset = uiSubtable;
muiCmapLength = uiSubtableLength;
miCmapFormat = uiFormat;
}
return miCmapFormat != 0;
}
int CTrueTypeFont::NumGlyphs(void)
{
return miNumGlyphs;
}
int CTrueTypeFont::GetUnitsPerEm(void)
{
return miUnitsPerEm;
}
int CTrueTypeFont::GetAscender(void)
{
return miAscender;
}
int CTrueTypeFont::GetDescender(void)
{
return miDescender;
}
int CTrueTypeFont::GetLineGap(void)
{
return miLineGap;
}
void CTrueTypeFont::ParsePost(void)
{
size uiOffset;
size uiLength;
int16 iPosition;
int16 iThickness;
mbHasPost = false;
if (FindTable("post", &uiOffset, &uiLength) && (uiLength >= 12))
{
if (ReadInt16(uiOffset + 8, &iPosition) && ReadInt16(uiOffset + 10, &iThickness))
{
miUnderlinePosition = iPosition;
miUnderlineThickness = iThickness;
mbHasPost = true;
}
}
}
void CTrueTypeFont::ParseOS2(void)
{
size uiOffset;
size uiLength;
int16 aiValues[10];
size i;
mbHasOS2 = false;
if (FindTable("OS/2", &uiOffset, &uiLength) && (uiLength >= 30))
{
for (i = 0; i < 10; i++)
{
if (!ReadInt16(uiOffset + 10 + i * 2, &aiValues[i]))
{
return;
}
}
miSubscriptYSize = aiValues[1];
miSubscriptYOffset = aiValues[3];
miSuperscriptYSize = aiValues[5];
miSuperscriptYOffset = aiValues[7];
miStrikeoutSize = aiValues[8];
miStrikeoutPosition = aiValues[9];
mbHasOS2 = true;
}
}
bool CTrueTypeFont::HasPost(void) { return mbHasPost; }
int CTrueTypeFont::GetUnderlinePosition(void) { return miUnderlinePosition; }
int CTrueTypeFont::GetUnderlineThickness(void) { return miUnderlineThickness; }
bool CTrueTypeFont::HasOS2(void) { return mbHasOS2; }
int CTrueTypeFont::GetStrikeoutPosition(void) { return miStrikeoutPosition; }
int CTrueTypeFont::GetStrikeoutSize(void) { return miStrikeoutSize; }
int CTrueTypeFont::GetSubscriptYSize(void) { return miSubscriptYSize; }
int CTrueTypeFont::GetSubscriptYOffset(void) { return miSubscriptYOffset; }
int CTrueTypeFont::GetSuperscriptYSize(void) { return miSuperscriptYSize; }
int CTrueTypeFont::GetSuperscriptYOffset(void) { return miSuperscriptYOffset; }
void CTrueTypeFont::GetBounds(int* piXMin, int* piYMin, int* piXMax, int* piYMax)
{
*piXMin = miXMin;
*piYMin = miYMin;
*piXMax = miXMax;
*piYMax = miYMax;
}
bool CTrueTypeFont::GetName(int iNameID, CChars* psz)
{
uint16 uiCount;
uint16 uiStringOffset;
uint16 i;
size uiRecord;
uint16 uiPlatform;
uint16 uiEncoding;
uint16 uiLanguage;
uint16 uiNameID;
uint16 uiLength;
uint16 uiOffset;
int iScore;
int iBestScore;
size uiBestRecord;
bool bUTF16;
size uiString;
size j;
uint16 uiChar;
if ((muiNameLength < 6) || !ReadUint16(muiNameOffset + 2, &uiCount) || !ReadUint16(muiNameOffset + 4, &uiStringOffset))
{
return false;
}
iBestScore = 0;
uiBestRecord = 0;
for (i = 0; i < uiCount; i++)
{
uiRecord = muiNameOffset + 6 + (size)i * 12;
if (!ReadUint16(uiRecord, &uiPlatform) || !ReadUint16(uiRecord + 2, &uiEncoding) || !ReadUint16(uiRecord + 4, &uiLanguage) || !ReadUint16(uiRecord + 6, &uiNameID))
{
return false;
}
if (uiNameID != iNameID)
{
continue;
}
if ((uiPlatform == 3) && (uiEncoding == 1))
{
iScore = (uiLanguage == 0x0409) ? 4 : 3;
}
else if (uiPlatform == 0)
{
iScore = 2;
}
else if ((uiPlatform == 1) && (uiEncoding == 0))
{
iScore = 1;
}
else
{
iScore = 0;
}
if (iScore > iBestScore)
{
iBestScore = iScore;
uiBestRecord = uiRecord;
}
}
if (iBestScore == 0)
{
return false;
}
ReadUint16(uiBestRecord, &uiPlatform);
ReadUint16(uiBestRecord + 8, &uiLength);
ReadUint16(uiBestRecord + 10, &uiOffset);
uiString = muiNameOffset + uiStringOffset + uiOffset;
if (!IsInFile(uiString, uiLength))
{
return false;
}
bUTF16 = uiPlatform != 1;
if (bUTF16)
{
for (j = 0; j + 1 < uiLength; j += 2)
{
ReadUint16(uiString + j, &uiChar);
if (uiChar < 0x80)
{
psz->Append((char)uiChar);
}
else if (uiChar < 0x800)
{
psz->Append((char)(0xC0 | (uiChar >> 6)));
psz->Append((char)(0x80 | (uiChar & 0x3F)));
}
else
{
psz->Append((char)(0xE0 | (uiChar >> 12)));
psz->Append((char)(0x80 | ((uiChar >> 6) & 0x3F)));
psz->Append((char)(0x80 | (uiChar & 0x3F)));
}
}
}
else
{
for (j = 0; j < uiLength; j++)
{
uiChar = mpuiData[uiString + j];
psz->Append((uiChar < 0x80) ? (char)uiChar : '?');
}
}
return true;
}
int CTrueTypeFont::GetGlyphIndex(uint32 uiCodePoint)
{
int iGlyph;
if (miCmapFormat == 12)
{
iGlyph = GetGlyphIndexFormat12(uiCodePoint);
}
else if (miCmapFormat == 4)
{
iGlyph = GetGlyphIndexFormat4(uiCodePoint);
}
else
{
return 0;
}
if ((iGlyph < 0) || (iGlyph >= miNumGlyphs))
{
return 0;
}
return iGlyph;
}
int CTrueTypeFont::GetGlyphIndexFormat4(uint32 uiCodePoint)
{
uint16 uiSegCountX2;
size uiSegCount;
size uiEndCodes;
size uiStartCodes;
size uiDeltas;
size uiRangeOffsets;
size uiLow;
size uiHigh;
size uiMiddle;
uint16 uiEnd;
uint16 uiStart;
int16 iDelta;
uint16 uiRangeOffset;
uint16 uiGlyph;
size uiGlyphAddress;
if ((uiCodePoint > 0xFFFF) || !ReadUint16(muiCmapOffset + 6, &uiSegCountX2))
{
return 0;
}
uiSegCount = uiSegCountX2 / 2;
uiEndCodes = muiCmapOffset + 14;
uiStartCodes = uiEndCodes + uiSegCountX2 + 2;
uiDeltas = uiStartCodes + uiSegCountX2;
uiRangeOffsets = uiDeltas + uiSegCountX2;
if (!IsInFile(uiEndCodes, (size)uiSegCountX2 * 4 + 2))
{
return 0;
}
uiLow = 0;
uiHigh = uiSegCount;
while (uiLow < uiHigh)
{
uiMiddle = (uiLow + uiHigh) / 2;
if (!ReadUint16(uiEndCodes + uiMiddle * 2, &uiEnd))
{
return 0;
}
if (uiEnd < uiCodePoint)
{
uiLow = uiMiddle + 1;
}
else
{
uiHigh = uiMiddle;
}
}
if (uiLow == uiSegCount)
{
return 0;
}
if (!ReadUint16(uiStartCodes + uiLow * 2, &uiStart) || (uiStart > uiCodePoint))
{
return 0;
}
if (!ReadInt16(uiDeltas + uiLow * 2, &iDelta) || !ReadUint16(uiRangeOffsets + uiLow * 2, &uiRangeOffset))
{
return 0;
}
if (uiRangeOffset == 0)
{
return (uint16)(uiCodePoint + iDelta);
}
uiGlyphAddress = uiRangeOffsets + uiLow * 2 + uiRangeOffset + (uiCodePoint - uiStart) * 2;
if (!ReadUint16(uiGlyphAddress, &uiGlyph) || (uiGlyph == 0))
{
return 0;
}
return (uint16)(uiGlyph + iDelta);
}
int CTrueTypeFont::GetGlyphIndexFormat12(uint32 uiCodePoint)
{
uint32 uiNumGroups;
size uiGroups;
size uiLow;
size uiHigh;
size uiMiddle;
uint32 uiStart;
uint32 uiEnd;
uint32 uiStartGlyph;
if (!ReadUint32(muiCmapOffset + 12, &uiNumGroups))
{
return 0;
}
uiGroups = muiCmapOffset + 16;
if ((uiNumGroups > muiSize / 12) || !IsInFile(uiGroups, (size)uiNumGroups * 12))
{
return 0;
}
uiLow = 0;
uiHigh = uiNumGroups;
while (uiLow < uiHigh)
{
uiMiddle = (uiLow + uiHigh) / 2;
if (!ReadUint32(uiGroups + uiMiddle * 12, &uiStart) || !ReadUint32(uiGroups + uiMiddle * 12 + 4, &uiEnd))
{
return 0;
}
if (uiCodePoint < uiStart)
{
uiHigh = uiMiddle;
}
else if (uiCodePoint > uiEnd)
{
uiLow = uiMiddle + 1;
}
else
{
if (!ReadUint32(uiGroups + uiMiddle * 12 + 8, &uiStartGlyph))
{
return 0;
}
return (int)(uiStartGlyph + (uiCodePoint - uiStart));
}
}
return 0;
}
bool CTrueTypeFont::GetGlyphMetrics(int iGlyph, STrueTypeGlyphMetrics* psMetrics)
{
uint16 uiAdvance;
int16 iLeftSideBearing;
size uiOffset;
size uiLength;
int16 iXMin;
int16 iYMin;
int16 iXMax;
int16 iYMax;
bool bRead;
if ((iGlyph < 0) || (iGlyph >= miNumGlyphs))
{
return false;
}
if (iGlyph < miNumHMetrics)
{
bRead = ReadUint16(muiHmtxOffset + (size)iGlyph * 4, &uiAdvance) &&
ReadInt16(muiHmtxOffset + (size)iGlyph * 4 + 2, &iLeftSideBearing);
}
else
{
bRead = ReadUint16(muiHmtxOffset + ((size)miNumHMetrics - 1) * 4, &uiAdvance) &&
ReadInt16(muiHmtxOffset + (size)miNumHMetrics * 4 + ((size)iGlyph - miNumHMetrics) * 2, &iLeftSideBearing);
}
if (!bRead)
{
return false;
}
psMetrics->iAdvanceWidth = uiAdvance;
psMetrics->iLeftSideBearing = iLeftSideBearing;
if (!GetGlyphData(iGlyph, &uiOffset, &uiLength))
{
return false;
}
if (uiLength == 0)
{
psMetrics->iXMin = 0;
psMetrics->iYMin = 0;
psMetrics->iXMax = 0;
psMetrics->iYMax = 0;
return true;
}
if ((uiLength < 10) || !ReadInt16(uiOffset + 2, &iXMin) || !ReadInt16(uiOffset + 4, &iYMin) || !ReadInt16(uiOffset + 6, &iXMax) || !ReadInt16(uiOffset + 8, &iYMax))
{
return false;
}
psMetrics->iXMin = iXMin;
psMetrics->iYMin = iYMin;
psMetrics->iXMax = iXMax;
psMetrics->iYMax = iYMax;
return true;
}
bool CTrueTypeFont::GetGlyphData(int iGlyph, size* puiOffset, size* puiLength)
{
uint16 uiStart16;
uint16 uiEnd16;
uint32 uiStart;
uint32 uiEnd;
if ((iGlyph < 0) || (iGlyph >= miNumGlyphs))
{
return false;
}
if (mbLongLoca)
{
if (!ReadUint32(muiLocaOffset + (size)iGlyph * 4, &uiStart) || !ReadUint32(muiLocaOffset + (size)iGlyph * 4 + 4, &uiEnd))
{
return false;
}
}
else
{
if (!ReadUint16(muiLocaOffset + (size)iGlyph * 2, &uiStart16) || !ReadUint16(muiLocaOffset + (size)iGlyph * 2 + 2, &uiEnd16))
{
return false;
}
uiStart = (uint32)uiStart16 * 2;
uiEnd = (uint32)uiEnd16 * 2;
}
if ((uiEnd < uiStart) || (uiEnd > muiGlyfLength))
{
return false;
}
*puiOffset = muiGlyfOffset + uiStart;
*puiLength = uiEnd - uiStart;
return true;
}
bool CTrueTypeFont::GetGlyphOutline(int iGlyph, CTrueTypeOutline* pcOutline)
{
if (!ReadGlyph(iGlyph, pcOutline, 0))
{
pcOutline->Clear();
return false;
}
return true;
}
bool CTrueTypeFont::ReadGlyph(int iGlyph, CTrueTypeOutline* pcOutline, int iDepth)
{
size uiOffset;
size uiLength;
int16 iNumContours;
if (iDepth > 8)
{
return false;
}
if (!GetGlyphData(iGlyph, &uiOffset, &uiLength))
{
return false;
}
if (uiLength == 0)
{
return true;
}
if ((uiLength < 10) || !ReadInt16(uiOffset, &iNumContours))
{
return false;
}
if (iNumContours >= 0)
{
return ReadSimpleGlyph(uiOffset + 10, uiLength - 10, iNumContours, pcOutline);
}
else
{
return ReadCompositeGlyph(uiOffset + 10, uiLength - 10, pcOutline, iDepth);
}
}
bool CTrueTypeFont::ReadSimpleGlyph(size uiOffset, size uiLength, int iNumContours, CTrueTypeOutline* pcOutline)
{
size uiEnd;
size uiFirstPoint;
int i;
uint16 uiContourEnd;
int iLastContourEnd;
size uiNumPoints;
uint16 uiInstructionLength;
size uiPos;
size uiPoint;
uint8 uiFlag;
uint8 uiRepeat;
uint8 uiDelta8;
int16 iDelta16;
int iValue;
STrueTypePoint* psPoint;
uint8* puiFlags;
uiEnd = uiOffset + uiLength;
if (!IsInFile(uiOffset, uiLength) || ((size)iNumContours * 2 + 2 > uiLength))
{
return false;
}
if (iNumContours == 0)
{
return true;
}
uiFirstPoint = pcOutline->NumPoints();
iLastContourEnd = -1;
for (i = 0; i < iNumContours; i++)
{
if (!ReadUint16(uiOffset + (size)i * 2, &uiContourEnd))
{
return false;
}
if ((int)uiContourEnd <= iLastContourEnd)
{
if ((int)uiContourEnd < iLastContourEnd)
{
return false;
}
continue;
}
iLastContourEnd = uiContourEnd;
pcOutline->maiContourEnds.Add((int)(uiFirstPoint + uiContourEnd));
}
uiNumPoints = (size)iLastContourEnd + 1;
uiPos = uiOffset + (size)iNumContours * 2;
if (!ReadUint16(uiPos, &uiInstructionLength))
{
return false;
}
uiPos += 2 + uiInstructionLength;
if (uiPos > uiEnd)
{
return false;
}
pcOutline->macPoints.GrowToAtLeastNumElements(uiFirstPoint + uiNumPoints, true);
puiFlags = (uint8*)malloc(uiNumPoints);
if (puiFlags == 0L)
{
return false;
}
uiPoint = 0;
while (uiPoint < uiNumPoints)
{
if ((uiPos >= uiEnd) || !ReadUint8(uiPos, &uiFlag))
{
free(puiFlags);
return false;
}
uiPos++;
puiFlags[uiPoint] = uiFlag;
uiPoint++;
if (uiFlag & 0x08)
{
if ((uiPos >= uiEnd) || !ReadUint8(uiPos, &uiRepeat))
{
free(puiFlags);
return false;
}
uiPos++;
for (; (uiRepeat > 0) && (uiPoint < uiNumPoints); uiRepeat--)
{
puiFlags[uiPoint] = uiFlag;
uiPoint++;
}
}
}
iValue = 0;
for (uiPoint = 0; uiPoint < uiNumPoints; uiPoint++)
{
uiFlag = puiFlags[uiPoint];
if (uiFlag & 0x02)
{
if ((uiPos + 1 > uiEnd) || !ReadUint8(uiPos, &uiDelta8))
{
free(puiFlags);
return false;
}
uiPos++;
iValue += (uiFlag & 0x10) ? uiDelta8 : -(int)uiDelta8;
}
else if (!(uiFlag & 0x10))
{
if ((uiPos + 2 > uiEnd) || !ReadInt16(uiPos, &iDelta16))
{
free(puiFlags);
return false;
}
uiPos += 2;
iValue += iDelta16;
}
psPoint = pcOutline->GetPoint(uiFirstPoint + uiPoint);
psPoint->x = iValue;
psPoint->bOnCurve = (uiFlag & 0x01) != 0;
}
iValue = 0;
for (uiPoint = 0; uiPoint < uiNumPoints; uiPoint++)
{
uiFlag = puiFlags[uiPoint];
if (uiFlag & 0x04)
{
if ((uiPos + 1 > uiEnd) || !ReadUint8(uiPos, &uiDelta8))
{
free(puiFlags);
return false;
}
uiPos++;
iValue += (uiFlag & 0x20) ? uiDelta8 : -(int)uiDelta8;
}
else if (!(uiFlag & 0x20))
{
if ((uiPos + 2 > uiEnd) || !ReadInt16(uiPos, &iDelta16))
{
free(puiFlags);
return false;
}
uiPos += 2;
iValue += iDelta16;
}
psPoint = pcOutline->GetPoint(uiFirstPoint + uiPoint);
psPoint->y = iValue;
}
free(puiFlags);
return true;
}
bool CTrueTypeFont::ReadCompositeGlyph(size uiOffset, size uiLength, CTrueTypeOutline* pcOutline, int iDepth)
{
size uiEnd;
size uiPos;
size uiFirstPoint;
uint16 uiFlags;
uint16 uiGlyph;
int iArg1;
int iArg2;
int16 iWord1;
int16 iWord2;
uint8 uiByte1;
uint8 uiByte2;
int16 iScale;
int32 iXX;
int32 iXY;
int32 iYX;
int32 iYY;
int32 iDX;
int32 iDY;
int32 x;
int32 y;
CTrueTypeOutline cComponent;
size i;
STrueTypePoint* psSource;
STrueTypePoint* psDest;
size uiNumComponentPoints;
uiEnd = uiOffset + uiLength;
uiPos = uiOffset;
uiFirstPoint = pcOutline->NumPoints();
cComponent.Init();
do
{
if ((uiPos + 4 > uiEnd) || !ReadUint16(uiPos, &uiFlags) || !ReadUint16(uiPos + 2, &uiGlyph))
{
cComponent.Kill();
return false;
}
uiPos += 4;
if (uiFlags & 0x0001)
{
if ((uiPos + 4 > uiEnd) || !ReadInt16(uiPos, &iWord1) || !ReadInt16(uiPos + 2, &iWord2))
{
cComponent.Kill();
return false;
}
uiPos += 4;
if (uiFlags & 0x0002)
{
iArg1 = iWord1;
iArg2 = iWord2;
}
else
{
iArg1 = (uint16)iWord1;
iArg2 = (uint16)iWord2;
}
}
else
{
if ((uiPos + 2 > uiEnd) || !ReadUint8(uiPos, &uiByte1) || !ReadUint8(uiPos + 1, &uiByte2))
{
cComponent.Kill();
return false;
}
uiPos += 2;
if (uiFlags & 0x0002)
{
iArg1 = (int8)uiByte1;
iArg2 = (int8)uiByte2;
}
else
{
iArg1 = uiByte1;
iArg2 = uiByte2;
}
}
iXX = 16384;
iXY = 0;
iYX = 0;
iYY = 16384;
if (uiFlags & 0x0008)
{
if ((uiPos + 2 > uiEnd) || !ReadInt16(uiPos, &iScale))
{
cComponent.Kill();
return false;
}
uiPos += 2;
iXX = iScale;
iYY = iScale;
}
else if (uiFlags & 0x0040)
{
if ((uiPos + 4 > uiEnd) || !ReadInt16(uiPos, &iWord1) || !ReadInt16(uiPos + 2, &iWord2))
{
cComponent.Kill();
return false;
}
uiPos += 4;
iXX = iWord1;
iYY = iWord2;
}
else if (uiFlags & 0x0080)
{
if ((uiPos + 8 > uiEnd) || !ReadInt16(uiPos, &iWord1) || !ReadInt16(uiPos + 2, &iWord2))
{
cComponent.Kill();
return false;
}
iXX = iWord1;
iXY = iWord2;
if (!ReadInt16(uiPos + 4, &iWord1) || !ReadInt16(uiPos + 6, &iWord2))
{
cComponent.Kill();
return false;
}
iYX = iWord1;
iYY = iWord2;
uiPos += 8;
}
cComponent.Clear();
if (!ReadGlyph(uiGlyph, &cComponent, iDepth + 1))
{
cComponent.Kill();
return false;
}
uiNumComponentPoints = cComponent.NumPoints();
for (i = 0; i < uiNumComponentPoints; i++)
{
psSource = cComponent.GetPoint(i);
x = psSource->x;
y = psSource->y;
psSource->x = (int32)DivideRound((int64)iXX * x + (int64)iYX * y, 16384);
psSource->y = (int32)DivideRound((int64)iXY * x + (int64)iYY * y, 16384);
}
if (uiFlags & 0x0002)
{
iDX = iArg1;
iDY = iArg2;
if ((uiFlags & 0x0800) && !(uiFlags & 0x1000))
{
x = iDX;
y = iDY;
iDX = (int32)DivideRound((int64)iXX * x + (int64)iYX * y, 16384);
iDY = (int32)DivideRound((int64)iXY * x + (int64)iYY * y, 16384);
}
}
else
{
if (((size)iArg1 >= pcOutline->NumPoints() - uiFirstPoint) || ((size)iArg2 >= uiNumComponentPoints))
{
cComponent.Kill();
return false;
}
psDest = pcOutline->GetPoint(uiFirstPoint + iArg1);
psSource = cComponent.GetPoint(iArg2);
iDX = psDest->x - psSource->x;
iDY = psDest->y - psSource->y;
}
for (i = 0; i < cComponent.NumContours(); i++)
{
pcOutline->maiContourEnds.Add((int)(pcOutline->NumPoints() + cComponent.GetContourEnd(i)));
}
for (i = 0; i < uiNumComponentPoints; i++)
{
psSource = cComponent.GetPoint(i);
psDest = pcOutline->macPoints.Add();
psDest->x = psSource->x + iDX;
psDest->y = psSource->y + iDY;
psDest->bOnCurve = psSource->bOnCurve;
}
}
while (uiFlags & 0x0020);
cComponent.Kill();
return true;
}
