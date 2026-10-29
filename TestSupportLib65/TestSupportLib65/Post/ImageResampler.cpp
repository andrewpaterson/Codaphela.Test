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
class SSizeVec2 : public SVec2<size, ulongint>
{
public:const char* ClassName(void){ return "SSizeVec2";}size ClassSize(void){ return sizeof(SSizeVec2);};
public:
using SVec2<size, ulongint>::SVec2;
using SVec2<size, ulongint>::operator=;
void Print(CChars* psx, size iWholeNumbers = -1);
size WholeNumbers(void);
};
typedef CArrayTemplate<SSizeVec2> CArraySizeVec2;
SSizeVec2* SizeVec2Add(SSizeVec2* pOut, const SSizeVec2* pV1, const SSizeVec2* pV2);
SSizeVec2* SizeVec2Subtract(SSizeVec2* pOut, const SSizeVec2* pV1, const SSizeVec2* pV2);
SSizeVec2* SizeVec2Minimize(SSizeVec2* pOut, const SSizeVec2* pV1, const SSizeVec2* pV2);
SSizeVec2* SizeVec2Maximize(SSizeVec2* pOut, const SSizeVec2* pV1, const SSizeVec2* pV2);
SSizeVec2* SizeVec2Scale(SSizeVec2* pOut, const SSizeVec2* pV, float32 s);
SSizeVec2* SizeVec2Lerp(SSizeVec2* pOut, const SSizeVec2* pV1, const SSizeVec2* pV2, float32 s);
void SizeVec2MinMax(SSizeVec2* psMin, SSizeVec2* psMax, SSizeVec2* asIn, size iInStride, size iNumPoints);
void SizeVec2Swap(SSizeVec2* ps1, SSizeVec2* ps2);
void SizeVec2InterpolatePosition(SSizeVec2* psVecDest, const SSizeVec2* psVec1, const SSizeVec2* psVec2, float32 fWeight);
class SIntVec2 : public SVec2<int, longint>
{
public:const char* ClassName(void){ return "SIntVec2";}size ClassSize(void){ return sizeof(SIntVec2);};
public:
using SVec2<int, longint>::SVec2;
using SVec2<int, longint>::operator=;
void Print(CChars* psx, int iWholeNumbers = -1);
int WholeNumbers(void);
};
typedef CArrayTemplate<SIntVec2> CArrayIntVec2;
int IntVec2Dot(const SIntVec2* pV1, const SIntVec2* pV2);
int IntVec2Cross(const SIntVec2* pV1, const SIntVec2* pV2);
SIntVec2* IntVec2Add(SIntVec2* pOut, const SIntVec2* pV1, const SIntVec2* pV2);
SIntVec2* IntVec2Subtract(SIntVec2* pOut, const SIntVec2* pV1, const SIntVec2* pV2);
SIntVec2* IntVec2Minimize(SIntVec2* pOut, const SIntVec2* pV1, const SIntVec2* pV2);
SIntVec2* IntVec2Maximize(SIntVec2* pOut, const SIntVec2* pV1, const SIntVec2* pV2);
SIntVec2* IntVec2Scale(SIntVec2* pOut, const SIntVec2* pV, float32 s);
SIntVec2* IntVec2Lerp(SIntVec2* pOut, const SIntVec2* pV1, const SIntVec2* pV2, float32 s);
void IntVec2MinMax(SIntVec2* psMin, SIntVec2* psMax, SIntVec2* asIn, int iInStride, int iNumPoints);
void IntVec2Swap(SIntVec2* ps1, SIntVec2* ps2);
void IntVec2InterpolatePosition(SIntVec2* psVecDest, const SIntVec2* psVec1, const SIntVec2* psVec2, float32 fWeight);
class SUInt32Vec2 : public SVec2<uint32, uint64>
{
public:const char* ClassName(void){ return "SUInt32Vec2";}size ClassSize(void){ return sizeof(SUInt32Vec2);};
public:
using SVec2<uint32, uint64>::SVec2;
using SVec2<uint32, uint64>::operator=;
void Print(CChars* psx, uint32 iWholeNumbers = -1);
uint32 WholeNumbers(void);
};
typedef CArrayTemplate<SUInt32Vec2> CArrayUInt32Vec2;
SUInt32Vec2* UInt32Vec2Add(SUInt32Vec2* pOut, const SUInt32Vec2* pV1, const SUInt32Vec2* pV2);
SUInt32Vec2* UInt32Vec2Subtract(SUInt32Vec2* pOut, const SUInt32Vec2* pV1, const SUInt32Vec2* pV2);
SUInt32Vec2* UInt32Vec2Minimize(SUInt32Vec2* pOut, const SUInt32Vec2* pV1, const SUInt32Vec2* pV2);
SUInt32Vec2* UInt32Vec2Maximize(SUInt32Vec2* pOut, const SUInt32Vec2* pV1, const SUInt32Vec2* pV2);
SUInt32Vec2* UInt32Vec2Scale(SUInt32Vec2* pOut, const SUInt32Vec2* pV, float32 s);
SUInt32Vec2* UInt32Vec2Lerp(SUInt32Vec2* pOut, const SUInt32Vec2* pV1, const SUInt32Vec2* pV2, float32 s);
void UInt32Vec2MinMax(SUInt32Vec2* psMin, SUInt32Vec2* psMax, SUInt32Vec2* asIn, uint32 iInStride, uint32 iNumPoints);
void UInt32Vec2Swap(SUInt32Vec2* ps1, SUInt32Vec2* ps2);
void UInt32Vec2InterpolatePosition(SUInt32Vec2* psVecDest, const SUInt32Vec2* psVec1, const SUInt32Vec2* psVec2, float32 fWeight);
class CArraySize : public CArrayTemplatePrimitive<int>
{
public:
size FindUnusedInSorted(void);
void Dump(void);
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
typedef int64 OIndex;
typedef CArrayTemplatePrimitive<OIndex> CArrayOIndex;
bool IsValidIndex(OIndex oi);
char* IndexToString(OIndex oi);
typedef int sig_atomic_t;
typedef void (*__sighandler_t)(int);
__sighandler_t signal(int iSignal, __sighandler_t fHandler);
int raise(int iSignal);
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
class CMemoryFile : public CAbstractFile
{
protected:
size miFlags;
lsize miPos;
bool mbOpen;
void* mpvInitialMem;
lsize miInitialLength;
bool mbFakeArray;
CArrayLargeChar mcArray;
public:
void Init(void);
void Init(void* pvInitialMem, lsize iInitialLength);
void Kill(void);
void* GetBufferPointer(void);
lsize GetBufferSize(void);
void SetBufferPointer(void* pvBuffer);
void SetBufferSize(lsize iBufferSize);
bool Open(EFileMode eFileMode);
bool Close(void);
lsize Read(void* pvBuffer, lsize iSize, lsize iCount);
bool Seek(filePos iOffset, EFileSeekOrigin iSeekOrigin);
lsize Write(const void* pvBuffer, lsize iSize, lsize iCount);
filePos Tell(void);
bool IsOpen(void);
filePos Size(void);
bool Truncate(filePos iSize);
bool Flush(void);
bool Delete(void);
const char* GetFilename(void);
};
CMemoryFile* MemoryFile(void);
CMemoryFile* MemoryFile(void* pvInitialMem, lsize iInitialLength);
class CIndexNewOld
{
public:
OIndex moiNew;
OIndex moiOld;
void Init(OIndex oiNew, OIndex oiOld);
};
typedef CArrayTemplate<CIndexNewOld> CArrayIndexNewOld;
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
class CObjectIdentifier
{
public:
int32 meType;
CChars mszObjectName;
OIndex moi;
uint16 muiSize;
void Init(void);
void Init(OIndex oi, uint16 uiSize);
void Init(const char* szName, OIndex oi, uint16 uiSize);
void Kill(void);
bool IsNamed(void);
bool IsIndexed(void);
bool IsFat(void);
const char* GetName(void);
OIndex GetIndex();
const char* GetType(void);
uint16 GetFatSize(void);
};
class CObjectHeader : public CObjectIdentifier
{
public:
CChars mszClassName;
void Init(void);
void Kill(void);
char* ClassName(void);
char* GetIdentifier(CChars* sz);
};
class CPointerHeader : public CObjectIdentifier
{
public:
uint16 miNumEmbedded;
uint16 miEmbeddedIndex;
void Init(void);
void Kill(void);
};
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
class SMemoryCacheDescriptor
{
private:
SMemoryCacheDescriptor* mpsNext;
SMemoryCacheDescriptor* mpsPrev;
size miSize;
public:
void SetNext(SMemoryCacheDescriptor* psNext);
void SetPrev(SMemoryCacheDescriptor* psPrev);
void SetSize(size iSize);
void Clear(void);
void ClearNext(void);
void ClearPrev(void);
size GetSize(void);
SMemoryCacheDescriptor* GetNext(void);
SMemoryCacheDescriptor* GetPrev(void);
bool IsSize(size iSize);
bool IsNext(SMemoryCacheDescriptor* psDesc);
bool IsPrev(SMemoryCacheDescriptor* psDesc);
};
struct SCircularMemoryList
{
size muiCacheSize;
SMemoryCacheDescriptor* mpsTail;
SMemoryCacheDescriptor* mpsHead;
};
class CCircularMemoryList
{
friend class CMemoryCache;
protected:
SCircularMemoryList* mpsDetail;
SMemoryCacheDescriptor* mpvCache;
size miDescriptorSize;
public:
void Init(void* pvCache, size uiByteSize, size iDescriptorSize = sizeof(SMemoryCacheDescriptor));
void InitExisting(void* pvCache, size uiByteSize, size iDescriptorSize = sizeof(SMemoryCacheDescriptor));
void Kill(void);
void Remap(void* pvNewCache, size uiByteSize);
void Remap(SCircularMemoryList* pvNewCache, size uiByteSize);
void Clear(void);
size GetSize(void* pvData);
size NumElements(void);
size NumElements(size iSize);
bool IsEmpty(void);
void* StartIteration(void);
void* Iterate(void* psCurrent);
void* GetFirst(void);
void* GetLast(void);
void* GetNext(void* psCurrent);
void* GetPrev(void* psCurrent);
size GetDescriptorSize(void);
void Deallocate(void* pvData);
size GetCacheSize(void);
size GetAllocatedSize(void);
bool ValidateCache(void);
bool ValidateEnds(void);
void Dump(void);
protected:
SMemoryCacheDescriptor* OneAllocation(void);
SMemoryCacheDescriptor* InsertNext(SMemoryCacheDescriptor* psCacheBasedDescriptor);
bool Overlaps(SMemoryCacheDescriptor* pvCacheBasedNew, size uiNewSize, SMemoryCacheDescriptor* psExisting);
size RemainingAfterTail(void);
size RemainingAfter(SMemoryCacheDescriptor* psCacheBasedDescriptor);
void RemapDifferentMemory(void* pvNewCache, size uiCacheSize);
void RemapSameMemory(size uiCacheSize);
SMemoryCacheDescriptor* StartDescriptorIteration(void);
SMemoryCacheDescriptor* IterateDescriptor(SMemoryCacheDescriptor* psCacheBasedDescriptor);
SMemoryCacheDescriptor* GetFirstDescriptor(void);
SMemoryCacheDescriptor* GetNextDescriptor(SMemoryCacheDescriptor* psCacheBasedDescriptor);
SMemoryCacheDescriptor* GetPrevDescriptor(SMemoryCacheDescriptor* psCacheBasedDescriptor);
SMemoryCacheDescriptor* GetLastDescriptor(void);
void* GetData(SMemoryCacheDescriptor* psCacheBasedDescriptor);
SMemoryCacheDescriptor* GetDescriptorNoRemap(void* pvData);
SMemoryCacheDescriptor* GetCache(void);
bool CanCache(size uiDataSize);
void Deallocate(SMemoryCacheDescriptor* psCacheBasedDescriptor);
SMemoryCacheDescriptor* MapFromZeroBasedToCacheBased(SMemoryCacheDescriptor* psZeroBasedDescriptor);
SMemoryCacheDescriptor* MapFromCacheBasedToZeroBased(SMemoryCacheDescriptor* psCacheBasedDescriptor);
SMemoryCacheDescriptor* MapFromZeroBasedToCacheBased(void* pvCache, SMemoryCacheDescriptor* psZeroBasedDescriptor);
SMemoryCacheDescriptor* MapFromCacheBasedToZeroBased(void* pvCache, SMemoryCacheDescriptor* psCacheBasedDescriptor);
void SetEndsForPostAllocate(SMemoryCacheDescriptor* psCacheBasedDescriptor, SMemoryCacheDescriptor* psFirstOverlap, SMemoryCacheDescriptor* psLastOverlap);
bool IsFirst(SMemoryCacheDescriptor* psCacheBasedDescriptor);
bool IsLast(SMemoryCacheDescriptor* psCacheBasedDescriptor);
protected:
size FindOverlapping(SMemoryCacheDescriptor* psCachedBasedNew, size uiNewSize, CArrayVoidPtr* pasOverlappingCacheDescriptors);
};
class CMemoryCacheAllocation
{
friend class CMemoryCache;
protected:
uint32 muiSize;
CArrayVoidPtr mapEvictedCacheDescriptors;
SMemoryCacheDescriptor* mpsDescriptor;
uint32 miCachedSize;
public:
void Init(uint32 uiSize);
void Kill(void);
bool HasOverlaps(void);
SMemoryCacheDescriptor* Get(size iIndex);
int NumElements(void);
CArrayVoidPtr* GetEvictedArray(void);
void Dump(size iDescriptorSize);
};
class SMemoryCacheDescriptor;
class CMemoryCacheEvictionCallback
{
public:
virtual bool CacheDataEvicted(void* pvData, SMemoryCacheDescriptor* psDescriptor) =0;
};
class CMemoryCache
{
protected:
CMemoryCacheEvictionCallback* mpcEvictionCallback;
CCircularMemoryList mcMemoryList;
void* mpvCache;
public:
void Init(size uiCacheSize, CMemoryCacheEvictionCallback* pcEvictionCallback, int iDescriptorSize = sizeof(SMemoryCacheDescriptor));
void Kill(void);
void Resize(size uiNewCacheSize);
void* Allocate(size uiDataSize);
size GetSize(void* pvData);
void* StartIteration(void);
void* Iterate(void* psCurrent);
void* GetFirst(void);
void* GetLast(void);
void* GetNext(void* psCurrent);
void* GetPrev(void* psCurrent);
void Clear(void);
void Deallocate(void* pvCache);
size NumElements(void);
size NumElements(size iSize);
size GetDescriptorSize(void);
size GetCacheSize(void);
void* GetCache(void);
size GetAllocatedSize(void);
bool CanCache(size uiDataSize);
bool ValidateCache(void);
void Dump(void);
protected:
bool PreAllocate(CMemoryCacheAllocation* pcPreAllocationResult);
void* PostAllocate(CMemoryCacheAllocation* pcPreAllocated);
};
class CIndexTreeDataNode
{
protected:
SLLNode msListNode;
uint16 muiDataSize;
public:
void Init(size uiDataSize);
void Kill(void);
size GetDataSize(void);
void SetDataSize(size uiDataSize);
SLLNode* GetListNode(void);
};
class CIndexTree;
class CIndexTreeNode
{
protected:
CIndexTree* mpcIndexTree;
CIndexTreeNode* mpcParent;
uint16 muiMagic;
uint8 muiFirstIndex;
uint8 muiLastIndex;
uint8 muiIndexInParent;
uint8 msFlags;
public:
void Init(CIndexTree* pcIndexTree, CIndexTreeNode* pcParent, size uiFirstIndex, size uiLastIndex, size uiDataSize, size iClearValue, size uiIndexInParent);
void Init(CIndexTree* pcIndexTree, CIndexTreeNode* pcParent, size uiIndexInParent);
void SetData(const void* pvObject, size uiSize);
size GetDataSize(void);
CIndexTreeDataNode* GetNodeData(void);
void* GetDataPtr(void);
bool HasData(void);
void SetData(bool bHasData);
void* GetNodesMemory(void);
CIndexTreeNode* GetParent(void);
size GetIndexInParent(void);
size GetFlags(void);
size GetTransientFlags(void);
CIndexTree* GetIndexTree(void);
size NumIndexes(void);
static size NumIndexes(size uiFirstIndex, size uiLastIndex);
size GetAdditionalIndexes(size uiIndex);
bool IsEmpty(void);
bool IsDirty(void);
bool IsPathDirty(void);
bool IsDeleted(void);
bool IsPathDeleted(void);
bool IsMagic(void);
bool HasFlags(size sFlags);
void ClearFlags(size sFlags);
size GetFirstIndex(void);
size GetLastIndex(void);
bool HasNodes(void);
size NumAllocatedNodes(void);
bool ContainsIndex(size uiIndex);
void SetNodesEmpty(bool bEmpty);
void SetDirtyNode(bool bDirty);
void SetDeletedNode(bool bDirty);
void SetDirtyPath(bool bDirty);
void SetDeletedPath(bool bDirty);
void Contain(size uiIndex, size iClearValue);
void ClearOnlyNode(size uiIndex, size iClearValue);
void MoveNodesLeft(size uiNextFirstIndex);
void MoveNodesRight(size uiNewFirstIndex, size iClearValue);
void ClearLastNodes(size uiNewLastIndex, size iClearValue);
size SizeofNodeAndData(void);
size SizeofNode(void);
size SizeofNodePtr(void);
void Print(CChars* psz, bool bHex);
char* GetFlagsString(CChars* psz);
size CalculateRequiredNodeSizeForIndex(size uiIndex);
size CalculateRequiredNodeSizeForData(size uiDataSize);
size CalculateRequiredNodeSizeForCurrent(void);
protected:
void ChangeDataSize(size uiSize);
};
enum EIndexKeyReverse
{
IKR_Unknown,
IKR_No,
IKR_Yes
};
template <class M>
class CLife
{
protected:
M** mppcLifeCycleObject;
uint32 mcFlags;
public:
void _Init(void);
void Init(M** ppcLifeCycleObject, bool bMustFree, bool bMustKill);
void Kill(void);
bool MustKill(void);
bool MustFree(void);
bool IsInitialised(void);
bool HasLifeCycleObject(void);
bool IsKilled(void);
};
template <class M>
class CLifeInit
{
protected:
M* mpcLifeCycleObject;
uint8 mcFlags;
public:
void Init(M* pcLifeCycleObject, bool bMustFree = true, bool bMustKill = true);
void Null(void);
void ConfigureLife(CLife<M>* pcLife, M** ppcLifeCycleObject);
M* GetLife(void);
bool MustKill(void);
bool MustFree(void);
};
template <class M>
void CLife<M>::_Init(void)
{
mppcLifeCycleObject = 0L;
mcFlags = 0;
};
template <class M>
void CLife<M>::Init(M** ppcLifeCycleObject, bool bMustFree, bool bMustKill)
{
mppcLifeCycleObject = ppcLifeCycleObject;
mcFlags = 0xB6A45B00;
SetFlagInt(&mcFlags, 0x02, bMustFree);
SetFlagInt(&mcFlags, 0x01, bMustKill);
};
template <class SpecificClass, class SuperClass, typename ... Args>
CLifeInit<SuperClass> LifeAlloc(Args ... args)
{
CLifeInit<SuperClass> cLife;
SpecificClass* pcLife;
pcLife = NewMalloc<SpecificClass>();
pcLife->Init(args...);
cLife.Init(pcLife, true, true);
return cLife;
}
template <class SuperClass>
CLifeInit<SuperClass> LifeLocal(SuperClass* pcLifeCycleObject)
{
CLifeInit<SuperClass> cLife;
cLife.Init(pcLifeCycleObject, false, false);
return cLife;
}
template <class SuperClass>
CLifeInit<SuperClass> LifeNull(void)
{
CLifeInit<SuperClass> cLife;
cLife.Null();
return cLife;
}
template <class M>
void CLifeInit<M>::Init(M* pcLifeCycleObject, bool bMustFree, bool bMustKill)
{
mpcLifeCycleObject = pcLifeCycleObject;
mcFlags = 0;
SetFlagByte(&mcFlags, 0x02, bMustFree);
SetFlagByte(&mcFlags, 0x01, bMustKill);
}
template <class M>
void CLifeInit<M>::Null(void)
{
Init(0L, false, false);
}
template <class M>
void CLifeInit<M>::ConfigureLife(CLife<M>* pcLife, M** ppcLifeCycleObject)
{
bool bMustFree;
bool bMustKill;
bMustFree = MustFree();
bMustKill = MustKill();
pcLife->Init(ppcLifeCycleObject, bMustFree, bMustKill);
if (ppcLifeCycleObject)
{
*ppcLifeCycleObject = mpcLifeCycleObject;
}
}
template <class M>
M* CLifeInit<M>::GetLife(void)
{
return mpcLifeCycleObject;
}
template <class M>
bool CLifeInit<M>::MustKill(void)
{
return FixBool(mcFlags & 0x01);
}
template <class M>
bool CLifeInit<M>::MustFree(void)
{
return FixBool(mcFlags & 0x02);
}
template <class M>
void CLife<M>::Kill(void)
{
CKillable* mpcKillable;
if (mppcLifeCycleObject)
{
mpcKillable = *mppcLifeCycleObject;
if (mpcKillable)
{
if (MustKill())
{
mpcKillable->Kill();
mcFlags = (mcFlags & 0x000000FF) | 0x5D59B400;
}
if (MustFree())
{
free(*mppcLifeCycleObject);
}
*mppcLifeCycleObject = 0L;
}
mppcLifeCycleObject = 0L;
}
}
template <class M>
bool CLife<M>::MustKill(void)
{
return FixBool(mcFlags & 0x01);
}
template <class M>
bool CLife<M>::MustFree(void)
{
return FixBool(mcFlags & 0x02);
}
template <class M>
bool CLife<M>::IsInitialised(void)
{
return (mcFlags & ~0x000000FF) == 0xB6A45B00;
}
template <class M>
bool CLife<M>::HasLifeCycleObject(void)
{
if (mppcLifeCycleObject != 0L)
{
return *mppcLifeCycleObject != 0L;
}
return false;
}
template <class M>
bool CLife<M>::IsKilled(void)
{
return (mcFlags & ~0x000000FF) == 0x5D59B400;
}
size MinDataSize(size uiDataSize, size uiMaxDataSize);
bool CopyString(char* pvDest, char* pvSource, size iSourceLength, size iMaxDestLength);
void CopyData(void* pvDest, void* pvSource, size iSourceLength, size iMaxDestLength);
size StrDataSize(const char* pszData);
size StrKeySize(const char* pszKey);
class CIndexTreeNode;
struct SDataOrderIterator
{
CIndexTreeDataNode* pcNode;
};
class CIndexTree;
class CIndexTreeDataOrderer : public CConstructable, public CKillable
{
protected:
CLinkedList mcDataOrder;
CIndexTree* mpcIndexTree;
public:
void Init(void);
virtual void Kill(void);
void New(CIndexTreeDataNode* psNode);
virtual void Put(CIndexTreeDataNode* psNode) =0;
virtual void Get(CIndexTreeDataNode* psNode) =0;
virtual void Remove(CIndexTreeDataNode* psNode) =0;
virtual void HasKey(CIndexTreeDataNode* psNode) =0;
void SetIndexTree(CIndexTree* pcIndexTree);
bool StartIteration(SDataOrderIterator* psIter, uint8* pvDestKey, size* piKeySize, size iDestKeySize, void* pvDestData, size* piDataSize, size iDestDataSize);
bool Iterate(SDataOrderIterator* psIter, uint8* pvDestKey, size* piKeySize, size iDestKeySize, void* pvDestData, size* piDataSize, size iDestDataSize);
CIndexTreeNode* GetFirstTreeNode(void);
CIndexTreeNode* GetLastTreeNode(void);
void RemapNode(CIndexTreeDataNode* psOldNode, CIndexTreeDataNode* psNewNode);
protected:
bool IterateNode(SLLNode* psNode, SDataOrderIterator* psIter, uint8* pvDestKey, size* piKeySize, size iDestKeySize, void* pvDestData, size* piDataSize, size iDestDataSize);
};
class CIndexTree
{
friend class CIndexTreeDataOrderer;
protected:
CLife<CMallocator> mcMallocLife;
CMallocator* mpcMalloc;
CLife<CIndexTreeDataOrderer> mcDataOrdererLife;
CIndexTreeDataOrderer* mpcDataOrderer;
EIndexKeyReverse meReverseKey;
size mtSizeofNode;
size mtSizeofNodePtr;
size mtSizeofDataNode;
size miMaxDataSize;
size miMaxKeySize;
public:
void _Init(void);
bool Init(CLifeInit<CMallocator> cMalloc, EIndexKeyReverse eKeyReverse, size tSizeofNode, size tSizeofDataNode, size tSizeofNodePtr, size iMaxDataSize, size iMaxKeySize, CLifeInit<CIndexTreeDataOrderer> cDataOrderer);
virtual void Kill(void);
virtual void ReInit(void) =0;
virtual bool Remove(uint8* pvKey, size iKeySize) =0;
virtual bool HasKey(uint8* pvKey, size iKeySize) =0;
size SizeofNode(void);
size SizeofDataNode(void);
size SizeofNodePtr(void);
EIndexKeyReverse ReverseKeys(void);
size CalculateRootNodeSize(void);
size CalculateNodeSize(size iRequiredIndices, size iDataSize);
void GetNodeKey(CIndexTreeNode* pcNode, CArrayChar* pacKey);
virtual void Dump(void) =0;
CIndexTreeDataOrderer* GetDataOrderer(void);
CMallocator* GetMalloc(void);
protected:
void* Malloc(lsize uiSize);
void* Realloc(void* pv, lsize uiSize);
void Free(void* pv);
bool ValidatePut(size iKeySize, size iDataSize);
void InsertReorderData(CIndexTreeNode* pcNode);
void GetReorderData(CIndexTreeNode* pcNode);
void PutReorderData(CIndexTreeNode* pcNode);
void RemoveReorderData(CIndexTreeNode* pcNode);
void HasKeyReorderData(CIndexTreeNode* pcNode);
void FreeNode(CIndexTreeNode* pcNode);
bool StartKey(size* pi, size iKeySize);
bool LoopKey(size* pi, size iKeySize);
CIndexTreeNode* GetNodeForDataNode(CIndexTreeDataNode* pcDataNode);
CIndexTreeNode* GetNodeForData(void* pvData);
void* GetDataForDataNode(CIndexTreeDataNode* pcDataNode);
void* GetDataForNode(CIndexTreeNode* pcNode);
virtual size GetNodeKey(CIndexTreeNode* pcNode, uint8* pvDestKey, size iDestKeySize) =0;
virtual size GetNodeKeySize(CIndexTreeNode* pcNode) =0;
virtual size GetNodeDataSize(CIndexTreeNode* pcNode) =0;
virtual size GetNodeData(CIndexTreeNode* pcNode, void* pvDestData, size iDestDataSize) =0;
};
class CIndexTreeNodeDebug
{
protected:
CChars mszBadKey;
CChars mszBadNode;
public:
void Init(void);
void Kill(void);
void GenerateBad(CIndexTreeNode* pcCurrent, CArrayChar* acKey);
char* GetBadKey(void);
char* GetBadNode(void);
protected:
void GenerateBadNode(CIndexTreeNode* pcCurrent, bool bHex);
bool GenerateBadKey(CArrayChar* acKey);
};
class CIndexTreeRecursor : public CIndexTreeNodeDebug
{
protected:
CArrayChar macKey;
CIndexTreeNode* mpcCurrent;
public:
void Init(CIndexTreeNode* pcRoot);
void Kill(void);
void Push(CIndexTreeNode* pcChild, uint8 c);
void Pop(void);
void GenerateBad(void);
CIndexTreeNode* GetNode(void);
void GetKey(void* pc, size* piKeySize);
size GetKeySize(void);
};
template <class M>
class CListTemplateMinimal
{
protected:
size miNumElements;
size miRowLength;
size miTotalSize;
size miUsedElements;
size miUsedLength;
int maiFieldOffsets[1];
public:
static size TotalSize(size iNumElements, size iRowLength);
void Init(size iNumFields, size iRowLength);
void Kill(void);
M* Get(size iIndex);
M* Get(size iIndex, size* piSize);
M* Add(const M* pv, size iSize);
size NumElements(void);
size AllocatedElements(void);
};
template<class M>
size CListTemplateMinimal<M>::TotalSize(size iNumElements, size iRowLength)
{
return sizeof(CListTemplateMinimal<M>) + iNumElements * sizeof(M*) + iRowLength;
}
template<class M>
void CListTemplateMinimal<M>::Init(size iNumElements, size iRowLength)
{
miNumElements = iNumElements;
miRowLength = iRowLength;
miUsedElements = 0;
miUsedLength = 0;
miTotalSize = TotalSize(iNumElements, iRowLength);
maiFieldOffsets[0] = (int)(sizeof(CListTemplateMinimal<M>) + miNumElements * sizeof(M*));
}
template<class M>
void CListTemplateMinimal<M>::Kill(void)
{
miUsedElements = 0;
miUsedLength = 0;
}
template<class M>
M* CListTemplateMinimal<M>::Get(size iIndex)
{
return (M*)RemapSinglePointer(this, maiFieldOffsets[iIndex]);
}
template<class M>
M* CListTemplateMinimal<M>::Get(size iIndex, size* piSize)
{
if (iIndex < miNumElements - 1)
{
*piSize = maiFieldOffsets[iIndex + 1] - maiFieldOffsets[iIndex];
}
else
{
*piSize = miTotalSize - maiFieldOffsets[iIndex];
}
return (M*)RemapSinglePointer(this, maiFieldOffsets[iIndex]);
}
template<class M>
M* CListTemplateMinimal<M>::Add(const M* pv, size iSize)
{
size iStringStart;
M* pvDest;
iStringStart = (int)maiFieldOffsets[0];
pvDest = (M*)RemapSinglePointer(this, iStringStart + miUsedLength);
memcpy(pvDest, pv, iSize);
maiFieldOffsets[miUsedElements] = (int)(iStringStart + miUsedLength);
miUsedLength += iSize;
miUsedElements++;
return pvDest;
}
template<class M>
size CListTemplateMinimal<M>::NumElements(void)
{
return miUsedElements;
}
template<class M>
size CListTemplateMinimal<M>::AllocatedElements(void)
{
return miNumElements;
}
typedef CListTemplateMinimal<char> __CListCharsMinimal;
template class CListTemplateMinimal<char>;
class CListCharsMinimal : public __CListCharsMinimal
{
public:
static size TotalSize(size iNumElements, size iRowLength);
void Init(size iNumElements, size iRowLength);
size IndexOf(char* szString);
void Add(char* sz);
void Add(const char* sz, size iSize);
};
struct SCountingMemoryAllocation
{
size uiSize;
};
class CCountingAllocator : public CMallocator
{
protected:
CMallocator* mpcAlloc;
size mtUserSize;
size mtSystemSize;
public:
void Init(CMallocator* pcAlloc);
void Kill(void);
size AllocatedUserSize(void);
size AllocatedSystemSize(void);
void* Malloc(lsize uiSize);
void* Realloc(void* pv, lsize uiSize);
bool Free(void* pv);
const char* ClassName(void);
size ClassSize(void);
bool IsLocal(void);
size SizeOffset(void);
const char* ShortName(void);
};
class CIndexTreeIterator
{
protected:
CArrayTemplateEmbedded<uint8, 16> macKey;
char macData[((size)(8 *(1024LL)))];
uint32 miType;
bool mbStarted;
size miKeySize;
size miDataSize;
public:
void Init(uint32 iType);
virtual void Kill(void);
size GetDataSize(void);
void* GetData(void);
size GetKeySize(void);
uint8* GetKey(void);
virtual bool Iterate(void) =0;
protected:
void Clear(void);
void SetKey(uint8* pvKey, size uiKeySize);
};
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
class CFileUtil
{
public:
bool MakeDir(const char* szPathName);
bool RemoveDir(const char* szPathName);
bool CopyDir(const char* szSource, const char* szDest);
bool Touch(const char* szFilename);
bool TouchDir(const char* szFilename, bool bLastIsFilename = false);
bool Delete(const char* szFilename);
bool SyncFile(const char* szFilename);
bool SyncDirectory(const char* szDirectory);
bool SyncParentDirectory(const char* szFilename);
bool Exists(const char* szFilename);
bool IsDirectory(const char* szPathName);
bool Compare(const char* szFilename1, const char* szFilename2);
bool CompareSize(const char* szFilename1, const char* szFilename2);
bool Copy(const char* szSource, const char* szDest);
filePos Size(const char* szFilename);
bool MakeDirs(bool bRemoveFirst, const char* szPathName, ...);
bool RemoveDirs(const char* szPathName, ...);
bool IsAbsolutePath(const char* szPathName);
void FullPath(CChars* szPathName);
char GetDriveLetter(const char* szPathName);
void CollapsePath(CChars* szPathName);
void CurrentDirectory(CChars* szDest);
void SplitPath(const char* szPathName, CChars* szDestFilename, CChars* szDestDirectory);
void SplitPath(const char* szPathName, CArrayChars* paszComponents);
void GetFileName(CChars* szDest, char* szPathName);
void RemoveExtension(CChars* szPathName);
size FindExtension(const char* szPathName);
void AppendToPath(CChars* szPathName, const char* szItem);
void PrependToPath(CChars* szPathName, const char* szItem);
void RemoveLastFromPath(CChars* szPathName);
void RemovePath(CChars* szPathName);
bool IsExtension(const char* szFilename, const char* szExtension);
bool IsRootDirectory(const char* szPathName);
void FindFilesWithNameContaining(const char* szPathName, const char* szFilename, CArrayChars* paszFiles, bool bIncludeSubDirs = false, bool bHidden= true);
void FindFilesWithExtension(const char* szPathName, const char* szExtension, CArrayChars* paszFiles, bool bIncludeSubDirs = false, bool bHidden = true);
void FindAllDirectories(const char* szPathName, CArrayChars* paszFiles, bool bHidden = true);
bool FindAllFiles(const char* szPathName, CArrayChars* paszFiles, bool bIncludeSubDirs = false, bool bHidden = true);
void MakeNameFromDirectory(CChars* pszName, CChars* pszFilename, CChars* pszDirectory);
void FixSeparators(CChars* szPathName);
private:
bool RecurseRemoveDir(const char* szPathName);
bool RecurseCopyDir(const char* szSource, const char* szDest);
bool CopyDirEntry(const char* szSource, const char* szDest, bool bDirectory);
bool FindFiles(const char* szPathName, bool bDirectories, const char* szInName, const char* szExtension, CArrayChars* paszFiles, bool bHidden);
bool IsFindMatch(const char* szName, bool bDirectory, bool bDirectories, const char* szInName, const char* szExtension);
bool RecurseFindFiles(const char* szPathName, const char* szInName, const char* szExtension, CArrayChars* paszFiles, bool bHidden);
bool Compare(const char* szFilename1, const char* szFilename2, bool bSizeOnly);
size FindFirstSeparator(const char* szString);
size FindLastSeparator(const char* szPathName);
void RemoveLastSeparator(CChars* szPathName);
};
int CompareFileNamesNTFS(const char* szName1, const char* szName2);
struct SIntAndPointer
{
void* pvData;
uint uiType;
};
struct SNameIntAndPointer : SIntAndPointer
{
char* szName;
};
class CArrayIntAndPointer : public CArrayTemplate<SIntAndPointer>
{
public:
void Add(void* pvData, uint uiType);
void AddIfUnique(void* pvData, uint uiType);
bool Get(size iElementPos, void** pvData, uint* uiType);
void* GetPtr(size iElementPos);
void* SafeGetPtr(size iElementPos);
uint GetType(size iElementPos);
uint SafeGetType(size iElementPos);
void Set(size iElementPos, void* pvData, uint uiType);
void Remove(void* pv);
void* InsertIntoSorted(DataCompare fCompare, void* pvElement, uint uiType);
bool FindInSorted(void* pvElement, DataCompare fCompare, size* piIndex);
bool BinarySearch(void* pvData, size iLeft, size iRight, DataCompare fCompare, size* piIndex);
};
class CDiskFile : public CAbstractFile
{
public:
uint8 maFile[8];
CChars mszFilename;
void Init(const char* szFilename);
void Init(CChars szFilename);
void Kill(void);
bool Open(EFileMode eMode);
bool Close(void);
lsize Read(void* pvBuffer, lsize iSize, lsize iCount);
bool Seek(filePos iOffset, EFileSeekOrigin iSeekOrigin);
lsize Write(const void* pvBuffer, lsize iSize, lsize iCount);
filePos Tell(void);
bool IsOpen(void);
filePos Size(void);
bool Truncate(filePos iSize);
bool Flush(void);
bool Delete(void);
const char* GetFilename(void);
void SetFile(void* pvFile, size uiSize);
bool IsFile(void* pvFile, size uiSize);
void* GetFile(void);
};
CDiskFile* DiskFile(const char* szName);
struct SAlignedData
{
size uiSize;
void* pvAlloc;
uint8 iAlignment;
int8 iOffset;
};
struct SAlignedDataDesc
{
size uiSize;
uint8 iAlignment;
int8 iOffset;
void Init(size uiSize, uint8 iAlignment, int8 iOffset);
bool Write(CFileWriter* pcFileWriter);
bool Read(CFileReader* pcFileReader);
};
struct SLLAlignedNode
{
SAlignedData sAligned;
SLLNode sNode;
};
class CLinkedListBlockAligned : public CBaseLinkedListBlock
{
public:
void Init(void);
void Init(CMallocator* pcMalloc);
void Kill(void);
void* InsertAfterTail(size uiSize, uint16 iAlignment, int16 iOffset);
void* InsertBeforeHead(size uiSize, uint16 iAlignment, int16 iOffset);
void* InsertBeforeNode(void* psPos, size uiSize, uint16 iAlignment, int16 iOffset);
void* InsertAfterNode(void* psPos, size uiSize, uint16 iAlignment, int16 iOffset);
void* Add(size uiSize, uint16 iAlignment);
SLLAlignedNode* AllocateDetached(size uiSize, uint16 iAlignment, int16 iOffset);
void Remove(void* pvData);
bool SafeRemove(void* pvData);
void FreeDetached(void* psNodeData);
void FreeNode(SLLAlignedNode* psNode);
void* Grow(void* pvData, size uiNewSize);
bool Write(CFileWriter* pcFileWriter);
bool Read(CFileReader* pcFileReader);
SLLAlignedNode* CalculateActualStart(void* pvMem, uint16 iAlignment, int16 iOffset);
SLLAlignedNode* GetNode(void* pvMem);
size ByteSize(void);
protected:
size GetNodeSize(void* pvMem);
bool WriteHeader(CFileWriter* pcFileWriter);
bool WriteData(CFileWriter* pcFileWriter);
bool ReadHeader(CFileReader* pcFileReader, CMallocator* pcMalloc, size* piNumElements);
bool ReadData(CFileReader* pcFileReader, size iNumElements);
};
struct SDataMemoryAllocation
{
size uiSize;
SFNode* psFreeListNode;
};
struct SGeneralMemoryAllocation
{
size uiSize;
size uiAllocCount;
char szDebug[4];
uint32 uiUnused;
};
struct SFreeListDesc
{
CFreeList* pcFreeList;
size iStride;
void Init(size iStride);
void Init(CFreeList* pcFreeList, int iStride);
};
struct SAlignedFreeListDesc : SFreeListDesc
{
uint8 iAlignment;
int8 iOffset;
void Init(size iStride, uint16 iAlignment, int16 iOffset);
void Init(CFreeList* pcFreeList, int iStride, uint16 iAlignment, int16 iOffset);
};
struct SMemoryIterator
{
bool bInFreeLists;
SFreeListIterator sFreeListIterator;
CFreeList* pcFreeList;
void* pvLarge;
};
struct SMemory
{
bool bValid;
void* pvMem;
size uiAllocCount;
size uiSize;
void Init(void);
void Set(SGeneralMemoryAllocation* psAllocation);
void Set(SDataMemoryAllocation* psAllocation);
};
typedef CArrayTemplate<SFreeListDesc> CArrayFreeListDesc;
typedef CArrayTemplate<SAlignedFreeListDesc> CArrayFreeListAlignedDesc;
typedef CArrayTemplatePtr<CFreeList> CArrayFreeListPtrs;
int CompareAlignedFreeListDesc(const void* arg1, const void* arg2);
int CompareFreeListDesc(const void* arg1, const void* arg2);
struct SMemoryFreeListParams
{
size iMaxListSize;
size iMaxElementSize;
size iMinElementSize;
size iChunkSize;
SMemoryFreeListParams* Init(size iFreeListSize, size iPrevSize, size iChunkSize, size iHeaderSize);
bool Write(CFileWriter* pcFileWriter);
bool Read(CFileReader* pcFileReader);
};
typedef CArrayTemplate<SMemoryFreeListParams> CArrayFreeListParams;
typedef CArrayTemplate<uint16> CArrayFreeListParamIndices;
int CompareFreeListParam(const void* arg1, const void* arg2);
class CMemoryFreeListParams
{
private:
CArrayFreeListParams mcParams;
size miHeaderSize;
size muiFreeListSizeLimit;
CArrayFreeListParamIndices mcSizeIndices;
bool mbSizeIndicesValid;
public:
void Init(size iHeaderSize, bool bDefaultFreeListParams = true);
void Kill(void);
void AddParamBlock(size iFreeListSize, size iPrevSize, size iChunkSize);
void AddParamBlock(SMemoryFreeListParams* psParam);
SMemoryFreeListParams* GetFreeListParams(size iIndex);
bool Read(CFileReader* pcFileReader);
bool Write(CFileWriter* pcFileWriter);
void SetFreeListSizeLimit(size uiFreeListSizeLimit);
SMemoryFreeListParams* GetFreeListParamsForSize(size iElementSize);
size GetFreeListParamsIndexForSize(size iElementSize);
size GetFreeListSizeLimit(void);
size GetMaxFreeListElementSize(void);
size NumParams(void);
private:
void InitFreeListParams(void);
size FindFreeListParamsIndex(size uiElementSize);
void BuildSizeIndices(void);
};
class CBaseMemory
{
public:
};
extern CMemoryFreeListParams gcDataMemoryFreeListParams;
class CDataMemory : public CBaseMemory
{
private:
CLinkListFreeList mcFreeLists;
CLinkedListBlockAligned mcLargeList;
CArrayFreeListDesc mcOrder;
CMemoryFreeListParams* mpcFreeListParams;
CArrayFreeListPtrs mcFreeListsByParams;
public:
void Init(void);
void Init(CMemoryFreeListParams* pcFreeListParams);
void Kill(void);
void ReInit(void);
void Compact(void);
void* Add(size iSize);
bool Remove(void* pv);
bool RemoveMultiple(CArrayVoidPtr* pav);
size GetSize(void* pv);
CFreeList* GetFreeList(size iElementSize);
void* Grow(void* pvInitial, size iSize);
size NumElements(void);
size ByteSize(void);
CMemoryFreeListParams* GetFreeListParams(void);
SMemory StartIteration(SMemoryIterator* psIterator);
SMemory Iterate(SMemoryIterator* psIterator);
uint64 GetTotalAllocatedMemory(void);
uint64 GetTotalAllocations(void);
CFreeList* TestGetFreeListsHead(void);
void* TestGetLargeListsHead(void);
size NumFreeLists(void);
protected:
size RemoveNode(CArrayVoidPtr* pav, size i, SDataMemoryAllocation* psAlloc, SFNode* psNode, CFreeList* pcList);
size RemoveElements(CArrayVoidPtr* pav, size i, SFNode* psNode, CFreeList* pcList);
private:
CFreeList* GetOrAddFreeList(size iElementSize);
void* AllocateInFreeList(CFreeList* pcFreeList, size uiElementSize);
bool DeallocateInFreeList(CFreeList* pcFreeList, SDataMemoryAllocation* psAlloc);
void FreeFreeList(CFreeList* pcFreeList);
void* AllocateInLargeList(size uiSize);
bool DeallocateInLargeList(SDataMemoryAllocation* psAlloc);
void CopyAllocation(void* pvDest, void* pvSource, size uiDestSize, size uiSourceSize);
};
void DataMemoryInit(void);
void DataMemoryKill(void);
struct SPointerAndSize
{
void* pvData;
size iSize;
};
typedef CArrayTemplate<SPointerAndSize> CArrayTypedPointerAndSize;
class CListVariable
{
private:
CArrayTypedPointerAndSize mcArray;
CDataMemory mcFreeLists;
public:
void Init(void);
void ReInit(void);
void Kill(void);
void* Add(size iElementSize);
void* Add(void* pvElement, size iElementSize);
bool Get(size iIndex, void** pvData);
void* Get(size iIndex);
void* Get(size iIndex, size* puiElementSize);
void Set(size iIndex, void* pvData, size iElementSize);
void* Resize(size iIndex, size iElementSize = 0);
void* Grow(size iIndex, size iElementSize);
void RemoveAt(size iIndex, bool bPreserveOrder = true);
size IndexOf(void* pvElement);
bool Remove(void* pvElement);
size NumElements(void);
bool FindInSorted(void* pvElement, DataCompare fCompare, size* piIndex);
void* InsertAt(size iIndex, size iElementSize);
size InsertIntoSorted(DataCompare fCompare, void* pvElement, bool bOverwriteExisting, size iElementSize);
size GetSize(size iIndex);
private:
void PrivateFree(SPointerAndSize* psType);
void* PrivateMalloc(size iElementSize);
};
enum ELogFileCommand
{
LFC_Open,
LFC_Write,
LFC_Close,
LFC_Delete,
LFC_Truncate
};
class CLogFileCommand
{
public:
ELogFileCommand eCommand;
void Init(ELogFileCommand eCommand);
bool IsWrite(void);
bool IsOpen(void);
bool IsClose(void);
bool IsDelete(void);
bool IsTruncate(void);
const char* GetType(void);
};
class CLogFileCommandOpen : public CLogFileCommand
{
public:
EFileMode eMode;
void Init(EFileMode eMode);
bool Open(CAbstractFile* pcFile);
};
class CLogFileCommandWrite : public CLogFileCommand
{
public:
filePos iPosition;
size iSize;
void Init(filePos iPosition, size iSize);
void Init(filePos iPosition, void* pvSource, size iSize);
bool Write(CAbstractFile* pcFile);
void* GetData(void);
};
class CLogFileCommandClose : public CLogFileCommand
{
public:
void Init(void);
bool Close(CAbstractFile* pcFile);
};
class CLogFileCommandDelete : public CLogFileCommand
{
public:
void Init(void);
bool Delete(CAbstractFile* pcFile);
};
class CLogFileCommandTruncate : public CLogFileCommand
{
public:
filePos iSize;
void Init(filePos iSize);
bool Truncate(CAbstractFile* pcFile);
};
class CLogFile : public CAbstractFile
{
protected:
CListVariable macCommands;
filePos miPosition;
filePos miLength;
filePos miBackingFileLength;
CAbstractFile* mpcBackingFile;
bool mbTouched;
EFileMode meFileMode;
bool mbOpenedBackingFile;
bool mbBegun;
bool mbBackingFileExists;
bool mbSync;
public:
void Init(CAbstractFile* pcBackingFile);
void Kill(void);
bool Begin(void);
bool Commit(void);
bool End(void);
void Abort(void);
bool Open(EFileMode eFileMode);
bool Close(void);
lsize Write(const void* pvSource, lsize iSize, lsize iCount);
lsize Read(void* pvDest, lsize iSize, lsize iCount);
filePos Tell(void);
filePos Size(void);
bool Truncate(filePos iSize);
bool Seek(filePos iOffset, EFileSeekOrigin iSeekOrigin);
bool Eof(void);
bool IsOpen(void);
bool Flush(void);
bool Delete(void);
const char* GetFilename(void);
bool Commit(CAbstractFile* pcFile);
void Print(CChars* psz);
void Dump(void);
size GetNumWrites(void);
size GetWriteSize(size iIndex);
size GetNumCommands(void);
CLogFileCommandWrite* GetWriteData(size iWrite);
bool TestFindHoles(size iWriteIndex, CArrayIntAndPointer* papvOverlapping, filePos iPosition, size iLength);
bool IsBegun(void);
void SetSync(bool bSync);
protected:
bool FindTouchingWriteCommands(size iStartIndex, CArrayIntAndPointer* papvOverlapping, filePos iPosition, size iLength, bool bMustOverlap);
bool Overlaps(filePos iPosition, size iLength, CLogFileCommandWrite* psWrite);
bool AmalgamateOverlappingWrites(CArrayIntAndPointer* papvOverlapping, const void* pvSource, filePos iPosition, size iLength);
bool ExtendLastWrite(CArrayIntAndPointer* papvOverlapping, const void* pvSource, filePos iPosition, size iLength);
bool FindHoles(CArrayIntAndPointer* papvOverlapping, filePos iPosition, size iLength);
void UpdateLength(void);
size ReadFromBackingFile(void* pvDest, size iSize, size iCount);
size ReadWithNoTouchingWrites(void* pvDest, size iSize, size iCount);
size ReadFirstTouchingWrites(size iWriteIndex, void* pvDest, size iSize, size iCount);
size ReadNextTouchingWrites(size iWriteIndex, void* pvDest, size iSize, size iCount);
void CopyWritesToRead(CArrayIntAndPointer* papvOverlapping, size iByteSize, void* pvDest);
size FindNextWriteCommand(size iIndex);
bool FailBegun(char* szMethod, const char* szTask, CAbstractFile* pcFile);
bool FailFlush(char* szMethod, CAbstractFile* pcFile);
void GetSafeFilename(CChars* pszDest, CAbstractFile* pcFile);
void ExecuteCommandErrorString(CChars* pszDest, char* szMethod, CLogFileCommand* psCommand, CAbstractFile* pcFile);
void AddCommandErrorString(CChars* pszDest, char* szMethod, CLogFileCommand* psCommand, CAbstractFile* pcFile);
CLogFileCommandOpen* AddOpenCommand(EFileMode eFileMode);
CLogFileCommandWrite* AddWriteCommand(filePos iPosition, void* pvSource, size iByteLength);
CLogFileCommandWrite* AddWriteCommand(filePos iPosition, size iByteLength);
CLogFileCommandClose* AddCloseCommand(void);
CLogFileCommandDelete* AddDeleteCommand(void);
CLogFileCommandTruncate* AddTruncateCommand(filePos iSize);
};
CLogFile* LogFile(CAbstractFile* pcFile);
struct SDurableFileCommandWrite
{
size iPosition;
size iSize;
};
class CDurableFileController;
class CDurableFile : public CFileIO
{
private:
CChars mszFilename;
CChars mszRewriteName;
CFileBasic mcPrimaryFile;
CFileBasic mcRewriteFile;
CDiskFile mcPrimaryDiskFile;
CDiskFile mcRewriteDiskFile;
CDurableFileController* mpcController;
CLogFile mcLogFile;
EFileMode meOpenMode;
bool mbLogFileBegun;
bool mbAddedToController;
public:
bool Init(CDurableFileController* pcController, const char* szFilename, const char* szRewriteName);
bool Kill(void);
void InitBasic(void);
void InitError(void);
bool Commit(void);
bool Recommit(void);
void Abort(void);
bool IsDurable(void);
bool IsSync(void);
bool IsBegun(void);
size Write(filePos iDistance, const void* pvSource, size iSize, size iCount);
size Write(EFileSeekOrigin eOrigin, filePos iDistance, const void* pvSource, size iSize, size iCount);
lsize Write(const void* pvSource, lsize iSize, lsize iCount);
size Read(filePos iDistance, void* pvDest, size iSize, size iCount);
size Read(EFileSeekOrigin eOrigin, filePos iDistance, void* pvDest, size iSize, size iCount);
lsize Read(void* pvDest, lsize iSize, lsize iCount);
bool Create(void);
bool Exists(void);
filePos Tell(void);
filePos Size(void);
bool Truncate(size iSize);
size GetNumWrites(void);
void* GetWriteData(size iWrite);
void AddFile(void);
bool CheckIdentical(bool bThorough, bool bLogError);
bool Delete(void);
bool TestGetOpenedSinceBegin(void);
bool IsOpen(void);
const char* GetFilename(void);
char* GetRewriteName(void);
void Dump(void);
CFileBasic* DumpGetPrimaryFile(void);
protected:
bool Seek(EFileSeekOrigin eOrigin, filePos iDistance, bool bSeekForWrite);
bool OpenPrimaryForRead(void);
bool OpenPrimaryForWrite(void);
bool OpenPrimaryFile(bool bOpenForWrite);
};
class CDurableFile;
typedef CArrayTemplatePtr<CDurableFile> CArrayDurableFilePtr;
class CDurableSet
{
private:
CArrayDurableFilePtr mapcFiles;
CChars mszMarkStart;
CChars mszMarkRewrite;
bool mbBegun;
bool mbSync;
public:
void Init(const char* szMarkStartFile, const char* szMarkRewriteFile);
void Kill(void);
bool HasBegun(void);
void SetSync(bool bSync);
bool Recover(void);
bool Begin(void);
bool End(void);
void Abort(void);
bool Check(bool bThorough, bool bLogError);
bool Add(CDurableFile* pcFile);
size Num(void);
CDurableFile* Get(size iIndex);
bool MarkStart(void);
bool MarkRewrite(void);
bool MarkFinish(void);
private:
bool Mark(const char* szMarkFile, CChars* pszContents);
bool ReadMarkedFiles(CArrayChars* paszFiles, bool* pbComplete);
bool CopyRecoveryFiles(bool bBackupToPrimary);
bool ContainsPair(CArrayChars* paszFiles, const char* szPrimary);
void GetMarks(bool* pbMarkStart, bool* pbMarkRewrite);
bool CopyRecoveredFile(const char* szSource, const char* szDest);
bool Unmark(const char* szMarkFile);
bool CheckFilesIdentical(bool bThorough, bool bLogError);
bool CheckWriteStatus(bool bMarkStart, bool bMarkRewrite, bool bLogError);
bool CheckWriteStatus(bool bLogError);
};
enum EDurableSync
{
DS_Unknown,
DS_No,
DS_Yes
};
class CDurableFileController
{
private:
CDurableSet mcDurableSet;
CChars mszDirectory;
CChars mszRewriteDirectory;
bool mbDurable;
bool mbSync;
public:
bool Init(const char* szDirectory);
bool Init(const char* szDirectory, const char* szRewriteDirectory, const char* szMarkWrite = 0L, const char* szMarkRewrite = 0L);
void Kill(void);
bool Begin(void);
bool Begin(CDurableFile* pcFirst, ...);
bool End(void);
void Abort(void);
bool Recover(void);
bool Recover(CDurableFile* pcFirst, ...);
bool Check(bool bThorough, bool bLogError);
bool AddFile(CDurableFile* pcFile);
size NumFiles(void);
CDurableFile* GetFile(size iIndex);
bool IsBegun(void);
char* GetDirectory(void);
char* GetRewriteDirectory(void);
bool IsDurable(void);
void SetSync(EDurableSync eSync);
bool IsSync(void);
CDurableSet* GetDurableSet(void);
};
class CFileDataIndex;
class CFilePosIndex
{
public:
filePos mulliFilePos;
uint32 miFile;
public:
void Init(void);
void Init(uint32 iFile, filePos ulliFilePos);
void Kill(void);
bool HasFile(void);
void SetIndex(uint32 iFile, filePos ulliFilePos);
CFileDataIndex ToFileDataIndex(uint32 muiDataSize);
};
class CFileDataIndex
{
public:
uint32 muiIndex;
uint32 miFile;
public:
void Init(void);
void Init(uint32 iFile, uint32 uiIndex);
void Kill(void);
bool HasFile(void);
void SetIndex(uint32 iFile, uint32 uiIndex);
void SetIndex(CFileDataIndex* pcSource);
bool Equals(CFileDataIndex* pcOther);
CFilePosIndex ToFilePosIndex(size muiDataSize);
};
class CIndexTreeFileDataCallback
{
public:
virtual size IndexTreeDataSize(size uiSourceSize) =0;
virtual bool IndexTreeWriteData(void* pvDataBuffer, void* pvSource, size iFileSize, size uiSourceSize) =0;
virtual bool IndexTreeReadData(void* pvDest, void* pvDataBuffer, size uiDestSize, size iFileSize) =0;
};
class CIndexTreeNodeFile;
class CIndexTreeChildNode
{
public:
uint32 iType;
union
{
CFileDataIndex mcFile;
CIndexTreeNodeFile* mpcMemory;
} u;
void Init(CFileDataIndex cFile);
void Init(CFileDataIndex* pcFile);
void Init(uint32 iFile, uint32 uiIndex);
void Init(CIndexTreeNodeFile* pcMemory);
void Clear(void);
bool IsValid(void);
bool IsMemory(void);
bool IsFile(void);
bool IsUnallocated(void);
};
class CIndexTreeNodeFile : public CIndexTreeNode
{
private:
CFileDataIndex mcFileIndex;
public:
void Init(CIndexTree* pcIndexTree, CIndexTreeNodeFile* pcParent, size uiFirstIndex, size uiLastIndex, CFileDataIndex cFileIndex, size uiIndexInParent);
void Init(CIndexTree* pcIndexTree, CIndexTreeNodeFile* pcParent, size uiFirstIndex, size uiLastIndex, size uiIndexInParent);
void Init(CIndexTree* pcIndexTree, CIndexTreeNodeFile* pcParent, size uiFirstIndex, size uiLastIndex, size uiDataSize, size uiIndexInParent);
void Init(CIndexTree* pcIndexTree, CIndexTreeNodeFile* pcParent, CFileDataIndex cFileIndex, size uiIndexInParent);
void Init(CIndexTree* pcIndexTree, CIndexTreeNodeFile* pcParent, size uiIndexInParent);
size InitFromBuffer(void* pvBuffer, size iMaxBufferSize, CIndexTreeFileDataCallback* pcCallback);
void SetFileIndex(uint32 iFile, uint32 uiIndex);
CFileDataIndex* GetFileIndex(void);
CIndexTreeChildNode* Get(size uiIndex);
bool SetFile(size uiIndex, CFileDataIndex cFileNode);
bool SetMemory(size uiIndex, CIndexTreeNodeFile* pcNode);
bool ClearIndex(size uiIndex);
bool ClearIndexAndUncontain(size uiIndex);
CIndexTreeChildNode* GetNode(size i);
CIndexTreeChildNode* GetNodes(void);
CIndexTreeChildNode* GetFirstNode(void);
size NumValidIndexes(void);
size NumValidMemoryIndexes(void);
void RemapChildNodes(CIndexTreeNodeFile* pcOldNode, CIndexTreeNodeFile* pcNewNode);
size FindPrevLastIndex(void);
size FindNextFirstIndex(void);
void SetChildrensParent(void);
size CalculateNodeSize(void);
size CalculateDataBufferSize(CIndexTreeFileDataCallback* pcCallback);
size CalculateFileSize(CIndexTreeFileDataCallback* pcCallback);
size WriteToBuffer(void* pvBuffer, size iBufferSize, CIndexTreeFileDataCallback* pcCallback);
bool HasFile(void);
bool HasOnlyFileNodes(void);
bool HasChildWithFlags(size uiFlags);
bool ConvertToFileNode(CIndexTreeNodeFile* pcNode);
CIndexTreeNodeFile* GetValidMemoryNode(size iIndex);
bool ValidateNodesEmpty(void);
bool ValidateParent(void);
void Print(CChars* psz, bool bHex);
void Dump(void);
protected:
bool Uncontain(size uiIndex);
};
struct SIndexTreeDebugNode
{
uint32 uiIndexInFile;
uint32 uiFileIndex;
bool bEmpty;
uint16 uiDataSize;
uint16 iFileNodeSize;
uint8 uiFirstIndex;
uint8 uiLastIndex;
uint8 uiIndexInParent;
uint8 sFlags;
int InitFromBuffer(void* pvBuffer, size iBufferSize, uint32 uiFileIndex, uint32 uiIndexInFile);
void InitBroken(size uiIndexInParent);
void Print(CChars* sz);
void Dump(void);
};
typedef CArrayTemplate<SIndexTreeDebugNode> CArrayIndexTreeDebugNode;
class CArrayBit : public CMalloc
{
protected:
size miNumBits;
union
{
struct SLarge
{
void* mpvData;
} aLarge;
struct SSmall
{
uint32 ui[3];
} aSmall;
} u;
public:
void Init(void);
void Init(CMallocator* pcMalloc);
void Kill(void);
void Zero(void);
void ReInit(void);
void GrowBy(size iNumBits);
void GrowTo(size iNumBits);
bool Get(size iBit);
void Get(void* pvDest, size iDestOffset, size iOffset, size iNumBits);
void Add(bool bBit);
void Add(void* pvSource, size iSourceOffset, size iNumBits);
void Set(size iBit, bool bBit);
void Set(size iOffset, void* pvSource, size iSourceOffset, size iNumBits);
bool Read(CFileReader* pcFileReader);
bool Write(CFileWriter* pcFileWriter);
size NumElements(void);
void* GetData(void);
size ByteSize(size iNumBits);
bool IsLarge(void);
void Print(CChars* psz);
void Dump(void);
};
class CListBlock
{
protected:
CFreeList mcFreeList;
CArrayVoidPtr mapIndices;
public:
void Init(size iElementSize);
void Init(size iElementSize, uint16 iAlignment);
void Init(size iElementSize, uint16 iAlignment, int16 iOffset);
void Kill(void);
size NumElements(void);
bool IsEmpty(void);
bool IsNotEmpty(void);
size ElementSize(void);
size NumBlocks(void);
size NumElementsFromFreeList(void);
void* Add(void);
void* Add(void* pvData);
void* AddGetIndex(size* piIndex);
void* Get(size iIndex);
void* SafeGet(size iIndex);
size GetIndex(void* pvElement);
void* Tail(void);
void* InsertAt(size iIndex);
void* InsertAt(void* pvData, size iIndex);
bool Pop(void* pvData);
bool Pop(void);
void* Push(void* pvElement);
void* Push(void);
void Reverse(void);
bool Contains(void* pvData);
void RemoveAt(size iIndex, bool bPreserveOrder = true);
void RemoveRange(size iStartIndex, size iEndIndexExclusive, bool bPreserveOrder = true);
void RemoveTail(void);
bool Set(size iIndex, void* pvData);
bool SafeSet(size iIndex, void* pvData);
void Swap(size iIndex1, size iIndex2);
protected:
void* Dereference(void** pv);
};
template<class M>
class CListTemplate : public CListBlock, protected CPostMalloc<M>
{
protected:
using CPostMalloc<M>::PostMalloc;
public:
void Init(void);
void Init(uint16 iAlignment);
void Init(uint16 iAlignment, int16 iOffset);
void Kill(void);
M* Add(void);
M* Add(M* pvData);
M* AddGetIndex(size* piIndex);
M* Get(size iIndex);
M* SafeGet(size iIndex);
size GetIndex(M* pvElement);
M* Tail(void);
M* InsertAt(size iIndex);
M* InsertAt(M* pvData, size iIndex);
void Pop(M* pvData);
M* Push(M* pvElement);
M* Push(void);
bool Contains(M* pvData);
bool Set(size iIndex, M* pvData);
bool SafeSet(size iIndex, M* pvData);
};
template<class M>
void CListTemplate<M>::Init(void)
{
CListBlock::Init(sizeof(M));
}
template<class M>
void CListTemplate<M>::Init(uint16 iAlignment)
{
CListBlock::Init(sizeof(M), iAlignment);
}
template<class M>
void CListTemplate<M>::Init(uint16 iAlignment, int16 iOffset)
{
CListBlock::Init(sizeof(M), iAlignment, iOffset);
}
template<class M>
void CListTemplate<M>::Kill(void)
{
CListBlock::Kill();
}
template<class M>
M* CListTemplate<M>::Add(void)
{
return PostMalloc((M*)CListBlock::Add());
}
template<class M>
M* CListTemplate<M>::Add(M* pvData)
{
return (M*)CListBlock::Add(pvData);
}
template<class M>
M* CListTemplate<M>::AddGetIndex(size* piIndex)
{
return PostMalloc((M*)CListBlock::AddGetIndex(piIndex));
}
template<class M>
M* CListTemplate<M>::Get(size iIndex)
{
return (M*)CListBlock::Get(iIndex);
}
template<class M>
M* CListTemplate<M>::SafeGet(size iIndex)
{
return (M*)CListBlock::SafeGet(iIndex);
}
template<class M>
size CListTemplate<M>::GetIndex(M* pvElement)
{
return CListBlock::GetIndex(pvElement);
}
template<class M>
M* CListTemplate<M>::Tail(void)
{
return (M*)CListBlock::Tail();
}
template<class M>
M* CListTemplate<M>::InsertAt(size iIndex)
{
return PostMalloc((M*)CListBlock::InsertAt(iIndex));
}
template<class M>
M* CListTemplate<M>::InsertAt(M* pvData, size iIndex)
{
return PostMalloc((M*)CListBlock::InsertAt(pvData, iIndex));
}
template<class M>
void CListTemplate<M>::Pop(M* pvData)
{
CListBlock::Pop(pvData);
}
template<class M>
M* CListTemplate<M>::Push(M* pvElement)
{
return (M*)CListBlock::Push(pvElement);
}
template<class M>
M* CListTemplate<M>::Push(void)
{
return (M*)CListBlock::Push();
}
template<class M>
bool CListTemplate<M>::Contains(M* pvData)
{
return CListBlock::Contains(pvData);
}
template<class M>
bool CListTemplate<M>::Set(size iIndex, M* pvData)
{
return CListBlock::Set(iIndex, pvData);
}
template<class M>
bool CListTemplate<M>::SafeSet(size iIndex, M* pvData)
{
return CListBlock::SafeSet(iIndex, pvData);
}
class CIndexedFile
{
private:
size muiFileIndex;
CDurableFile mcFile;
size muiDataSize;
filePos miNumDatas;
uint32 muiFileNumber;
public:
bool Init(CDurableFileController* pcDurableFileControl, size uiFileIndex, const char* szFilename, const char* szRewriteName, size uiDataSize, uint32 uiFileNum);
void Kill(void);
filePos CalculateNumDatas(void);
bool IsFull(void);
filePos Write(const void* pvData);
bool Write(filePos iIndex, const void* pvData);
bool Write(filePos iIndex, const void* pvData, size iCount);
bool Read(filePos iIndex, void* pvData);
bool Read(filePos iIndex, void* pvData, size iCount);
bool Delete(filePos iIndex);
bool Delete(filePos iIndex, size iCount);
size GetFileIndex(void);
bool IsFileIndex(size uiFileIndex);
CFileBasic* DumpGetPrimaryFile(void);
const char* GetFilename(void);
uint32 GetFileNumber(void);
char* GetRewriteName(void);
size GetDataSize(void);
filePos NumDatas(void);
filePos GetUsedDataIndices(CArrayBit* pab);
filePos GetFileSize(void);
void Dump(void);
protected:
filePos Write(const void* pvData, size iCount);
};
typedef CListTemplate<CIndexedFile> CListIndexedFile;
typedef CArrayTemplatePtr<CIndexedFile> CArrayIndexedFilePtr;
struct SIndexedFileDataDescriptor
{
public:
uint32 muiDataSize;
CFilePosIndex mcFileIndex;
};
class CIndexedDataDescriptor
{
private:
SIndexedFileDataDescriptor msFileDescriptor;
void* mpvCache;
size muiCacheDataSize;
public:
void Init(size uiDataSize, CFilePosIndex* pcFilePosIndex);
void Init(size uiDataSize, void* pvCache);
void Init(size uiFileDataSize, CFilePosIndex* pcFilePosIndex, size uiCacheDataSize, void* pvCache);
size GetFileDataSize(void);
size GetCacheDataSize(void);
size GetDataSize(void);
void Cache(void* pvCache, size uiDataSize);
void ClearCache(void);
bool HasFile(void);
bool IsCached(void);
void* GetCache(void);
void SetIndexes(int iFileIndex, filePos iIndexInFile);
int GetFileIndex(void);
filePos GetPositionInFile(void);
CFileDataIndex GetFileDataIndex(void);
CFilePosIndex* GetFilePosIndex(void);
bool Update(CIndexedDataDescriptor* pcNew);
};
typedef CArrayTemplate<CIndexedDataDescriptor> CArrayIndexDescriptor;
class CIndexedFiles
{
protected:
CDurableFileController* mpcDurableFileControl;
CListIndexedFile mcFiles;
CChars mszDataExtension;
CChars mszSubDirectory;
CDurableFile mcFileDescriptors;
public:
void Init(CDurableFileController* pcDurableFileControl, const char* szSubDirectory, const char* szDataExtension, const char* szDescriptorName, const char* szDescriptorRewrite);
bool Kill(void);
bool ReadIndexedFileDescriptors(void);
bool WriteIndexedFileDescriptors(void);
bool DataFilename(char* szFile1, char* szFile2, size iDataSize, uint32 iFileNum);
CIndexedFile* GetOrCreateFile(size uiDataSize);
CIndexedFile* GetFile(size uiDataSize, uint32 iFileNum);
CIndexedFile* GetFile(uint32 uiFileIndex);
uint32 GetUniqueFileNumber(size iDataSize);
void GetFiles(CArrayIndexedFilePtr* pac);
size GetFileDataSize(uint32 uiFileIndex);
int64 NumDatas(void);
int64 NumDatas(size iDataSize);
size NumFiles(size iDataSize);
size NumFiles(void);
bool Read(CFileDataIndex* pcDataIndex, void* pvData);
bool Delete(CFileDataIndex* pcDataIndex);
CFileDataIndex WriteNew(const void* pvData, size iDataSize);
bool WriteExisting(CFileDataIndex* pcDataIndex, const void* pvData, size iDataSize);
bool IsDurable(void);
void Dump(void);
};
class CIndexTreeFileDiagnosticCallback
{
public:
void Init(void);
virtual void Kill(void);
virtual void Put(void* pvKey, size iKeySize, const void* pvData, size iDataSize);
virtual void Get(void* pvKey, size iKeySize, void* pvData, size iDataSize);
virtual void Remove(void* pvKey, size iKeySize, void* pvData, size iDataSize);
virtual void Flush(void* pvKey, size iKeySize, void* pvData, size iDataSize);
virtual void Evict(void* pvKey, size iKeySize, void* pvData, size iDataSize);
};
enum EIndexWriteThrough
{
IWT_Unknown,
IWT_No,
IWT_Yes
};
struct SIndexTreeFileUnsafeIterator
{
CIndexTreeNodeFile* pcNode;
size iIndex;
};
struct SIndexTreeFileIterator
{
CArrayTemplateEmbedded<uint8, 16> acKey;
size iKeyLength;
size iIndex;
void Init(void);
void Kill(void);
bool IsLive(void);
};
class CIndexTreeFile : public CIndexTree
{
friend class CIndexTreeEvicting;
friend class CIndexTreeWriter;
friend class CIndexTreeNodeFile;
friend class CIndexTreeFileIterator;
protected:
CIndexTreeNodeFile* mpcRoot;
CIndexedFiles mcIndexFiles;
CDurableFileController* mpcDurableFileControl;
EIndexWriteThrough meWriteThrough;
CDurableFile mcRootIndex;
CCountingAllocator mcMalloc;
CMallocator* mpcPassThruMallocLife;
CLife<CMallocator> mcPassThruMallocLife;
CIndexTreeFileDataCallback* mpcDataCallback;
CIndexTreeFileDiagnosticCallback* mpcDiagnosticCallback;
public:
bool Init(CDurableFileController* pcDurableFileControl, const char* szSubDirectory, int iMaxDataSize, int iMaxKeySize);
bool Init(CDurableFileController* pcDurableFileControl, const char* szSubDirectory, EIndexWriteThrough eWriteThrough, EIndexKeyReverse eKeyReverse);
bool Init(CDurableFileController* pcDurableFileControl, const char* szSubDirectory, EIndexWriteThrough eWriteThrough, EIndexKeyReverse eKeyReverse, CLifeInit<CIndexTreeDataOrderer> cDataOrderer);
bool Init(CDurableFileController* pcDurableFileControl, const char* szSubDirectory, CLifeInit<CMallocator> cMalloc, EIndexWriteThrough eWriteThrough, EIndexKeyReverse eKeyReverse);
bool Init(CDurableFileController* pcDurableFileControl, const char* szSubDirectory, CIndexTreeFileDataCallback* pcWriterCallback, EIndexWriteThrough eWriteThrough, EIndexKeyReverse eKeyReverse);
bool Init(CDurableFileController* pcDurableFileControl, const char* szSubDirectory, CIndexTreeFileDataCallback* pcWriterCallback, CLifeInit<CMallocator> cMalloc, EIndexWriteThrough eWriteThrough, EIndexKeyReverse eKeyReverse, CLifeInit<CIndexTreeDataOrderer> cDataOrderer);
bool Init(CDurableFileController* pcDurableFileControl, const char* szSubDirectory, CIndexTreeFileDataCallback* pcWriterCallback, CLifeInit<CMallocator> cMalloc, EIndexWriteThrough eWriteThrough, EIndexKeyReverse eKeyReverse, int iMaxDataSize, int iMaxKeySize);
bool Init(CDurableFileController* pcDurableFileControl, const char* szSubDirectory, CIndexTreeFileDataCallback* pcWriterCallback, CLifeInit<CMallocator> cMalloc, EIndexWriteThrough eWriteThrough, EIndexKeyReverse eKeyReverse, int iMaxDataSize, int iMaxKeySize, CLifeInit<CIndexTreeDataOrderer> cDataOrderer);
void Kill(void);
void ReInit(void) override;
bool Get(uint8* pvKey, size iKeySize, void* pvObject, size* piDataSize, size uiMaxDataSize);
bool Put(uint8* pvKey, size iKeySize, const void* pvObject, size iDataSize);
bool Remove(uint8* pvKey, size iKeySize);
bool HasKey(uint8* pvKey, size iKeySize);
size GetDataSize(uint8* pvKey, size iKeySize);
bool Flush(void);
bool StartIteration(SIndexTreeFileIterator* psIterator, uint8* pvKey, size* piKeySize, size iMaxKeySize, void* pvData, size* piDataSize, size iMaxDataSize);
bool Iterate(SIndexTreeFileIterator* psIterator, uint8* pvKey, size* piKeySize, size iMaxKeySize, void* pvData, size* piDataSize, size iMaxDataSize);
bool StartUnsafeIteration(SIndexTreeFileUnsafeIterator* psIterator, uint8* pvKey, size* piKeySize, size iMaxKeySize, void** ppvData, size* piDataSize);
bool UnsafeIterate(SIndexTreeFileUnsafeIterator* psIterator, uint8* pvKey, size* piKeySize, size iMaxKeySize, void** pvData, size* piDataSize);
bool StartUnsafeIteration(SIndexTreeFileUnsafeIterator* psIterator, void** ppvData, size* piDataSize);
bool UnsafeIterate(SIndexTreeFileUnsafeIterator* psIterator, void** ppvData, size* piDataSize);
bool Evict(uint8* pvKey, size iKeySize);
bool Flush(uint8* pvKey, size iKeySize);
void SetDiagnosticCallback(CIndexTreeFileDiagnosticCallback* pcCallback);
bool IsFlushed(void);
bool ValidateIndexTree(void);
bool ValidateParentIndex(void);
uint32 NumElements(void);
bool IsWriteThrough(void);
bool HasDiagnosticCallback(void);
CDurableFileController* GetController(void);
void Print(CChars* pszDest, bool bShowFlags, bool bShowSize);
void Dump(void);
protected:
bool Evict(CIndexTreeNodeFile* pcNode);
void SetWriteThrough(EIndexWriteThrough eWriteThrough);
CIndexTreeNodeFile* ParentPut(CIndexTreeNodeFile* pcParent, size uiIndexInParent, uint8 uiDataSize, uint8 uiFirstIndex, uint8 uiLastIndex);
CIndexTreeNodeFile* ParentPut(CIndexTreeNodeFile* pcParent, size uiIndexInParent, uint8 uiDataSize);
CIndexTreeNodeFile* GetRoot(void);
CIndexTreeNodeFile* GetNode(uint8* pvKey, size iKeySize);
CIndexTreeNodeFile* GetMemoryNode(uint8* pvKey, size iKeySize);
CIndexTreeNodeFile* GetNodeForData(void* pvData);
size GetNodeKeySize(CIndexTreeNode* pcNode);
size GetNodeKey(CIndexTreeNode* pcNode, uint8* pvDestKey, size iDestKeySize);
size GetNodeDataSize(CIndexTreeNode* pcNode);
size GetNodeData(CIndexTreeNode* pcNode, void* pvDestData, size iDestDataSize);
CListTemplateMinimal<char>* GetNodesKeys(CArrayVoidPtr* apvNodes);
CListCharsMinimal* GetNodesStringKeys(CArrayVoidPtr* apvNodes);
size GetNodeKeysSize(CArrayVoidPtr* apvNodes);
bool ValidateIndexTree(bool bReadNodes);
bool ValidateKey(uint8* pvKey, size iKeySize);
bool ValidateKey(char* pszKey);
size ByteSize(void);
size GetUserMemorySize(void);
size GetSystemMemorySize(void);
CIndexedFiles* GetIndexFiles(void);
void GetFiles(CArrayIndexedFilePtr* pac);
CIndexedFile* GetFile(int iFile);
uint32 NumNodes(void);
size NumMemoryNodes(void);
size NumMemoryElements(void);
size NumMemoryElements(size iSize);
void DebugKey(CChars* pszDest, uint8* pvKey, size iKeySize, bool bSkipRoot, bool bShowFlags, bool bShowSize, bool bKeyAlreadyReversed);
void PrintChildren(CChars* pszDest, bool bShowFlags, bool bShowSize);
bool InitRoot(const char* szSubDirectory);
void RecurseKill(CIndexTreeNodeFile* pcNode);
CIndexTreeNodeFile* ReadNode(CIndexTreeNodeFile* pcParent, size c);
CIndexTreeNodeFile* ReadNode(CIndexTreeNodeFile* pcParent, size c, bool bReadNode);
bool Read(CIndexTreeChildNode* pcChildNode, CIndexTreeNodeFile* pcFileNodeParent, size uiIndexInParent);
CIndexTreeNodeFile* ReadMemoryNode(CIndexTreeNodeFile* pcParent, size c);
bool HasMemoryNodes(CIndexTreeNodeFile* pcNode);
bool Write(CIndexTreeNodeFile* pcNode);
bool Delete(CIndexTreeNodeFile* pcNode);
CIndexTreeNodeFile* AllocateRoot(void);
CIndexTreeNodeFile* AllocateRoot(CFileDataIndex cFileIndex);
CIndexTreeNodeFile* AllocateNodeSingle(CIndexTreeNodeFile* pcParent, size uiIndexInParent, size uiDataSize);
CIndexTreeNodeFile* AllocateNodeRange(CIndexTreeNodeFile* pcParent, size uiIndexInParent, size uiFirstIndex, size uiLastIndex, size uiDataSize);
CIndexTreeNodeFile* AllocateNodeFromBuffer(CIndexTreeNodeFile* pcParent, size uiIndexInParent, void* pvBuffer, int iMaxBufferSize);
CIndexTreeNodeFile* ReallocateNodeForContainIndex(CIndexTreeNodeFile* pcNode, size uiIndex);
CIndexTreeNodeFile* ReallocateNodeForLargerData(CIndexTreeNodeFile* pcNode, const void* pvData, size uiDataSize);
CIndexTreeNodeFile* ReallocateNodeForSmallerData(CIndexTreeNodeFile* pcNode, const void* pvData, size uiOriginalSize);
CIndexTreeNodeFile* ReallocateNodeForUncontainIndex(CIndexTreeNodeFile* pcNode, size c);
CIndexTreeNodeFile* AllocateChildNode(CIndexTreeNodeFile* pcParent, size uiIndexInParent);
CIndexTreeNodeFile* SetNodeData(CIndexTreeNodeFile* pcCurrent, const void* pvObject, size uiDataSize);
CIndexTreeNodeFile* AllocateKey(uint8* pvKey, size iKeySize);
bool HasData(CIndexTreeNodeFile* pcNode);
void RemapNodePointers(CIndexTreeNodeFile* pcOldNode, CIndexTreeNodeFile* pcNode);
CIndexTreeNodeFile* RemoveWriteThrough(CIndexTreeNodeFile* pcCurrent);
bool RemoveWaitForFlush(CIndexTreeNodeFile* pcCurrent);
bool EvictNode(CIndexTreeNodeFile* pcCurrent);
bool Flush(CIndexTreeNodeFile** ppcCurrent);
bool CanEvict(CIndexTreeNodeFile* pcNode);
void ClearNodesFlags(CArrayVoidPtr* papNodes, uint8 uiFlags);
void FindWithFlags(CArrayVoidPtr* papNodes, uint8 uiFollowFlags, uint8 uiAddFlags);
uint32 RecurseNumElements(CIndexTreeNodeFile* pcNode);
size RecurseNumMemoryElements(CIndexTreeNodeFile* pcNode);
size RecurseNumMemoryElements(CIndexTreeNodeFile* pcNode, size iSize);
size CountListSize(void);
size RecurseCountListSize(CIndexTreeNodeFile* pcNode);
size RecurseByteSize(CIndexTreeNodeFile* pcNode);
void RecurseFindWithFlags(CIndexTreeRecursor* pcCursor, uint8 uiFollowFlags, uint8 uiAddFlags, CArrayVoidPtr* papNodes);
uint32 RecurseNumNodes(CIndexTreeRecursor* pcCursor);
size RecurseNumMemoryNodes(CIndexTreeRecursor* pcCursor);
bool ValidateLimits(bool bReadNodes);
bool RecurseValidateLimits(CIndexTreeRecursor* pcCursor, bool bReadNodes);
bool ValidateParentIndex(bool bReadNodes);
bool RecurseValidateParentIndex(CIndexTreeRecursor* pcCursor, bool bReadNodes);
bool ValidateTransientFlags(bool bReadNodes);
bool RecurseValidateTransientFlags(CIndexTreeRecursor* pcCursor, bool bReadNodes);
bool ValidateMagic(bool bReadNodes);
bool RecurseValidateMagic(CIndexTreeRecursor* pcCursor, bool bReadNodes);
bool ValidateFileIndexes(bool bReadNodes);
bool RecurseValidateFileIndexes(CIndexTreeRecursor* pcCursor, bool bReadNodes);
bool ValidateKeys(bool bReadNodes);
bool RecurseValidateKeys(CIndexTreeRecursor* pcCursor, bool bReadNodes);
CIndexTreeNodeFile* StepNext(SIndexTreeFileIterator* psIterator);
void SetIteratorKey(SIndexTreeFileIterator* psIterator, CIndexTreeNodeFile* pcNode);
bool StepNext(SIndexTreeFileUnsafeIterator* psIterator);
bool FlushDeleted(void);
bool FlushDirty(void);
bool RecurseFlushDirty(CIndexTreeRecursor* pcCursor);
bool WriteBackPathWriteThrough(CIndexTreeNodeFile* pcNode);
bool WriteBackPathCaching(CIndexTreeNodeFile* pcNode);
bool SetDirtyPath(CIndexTreeNodeFile* pcCurrent);
bool SetDeletedPath(CIndexTreeNodeFile* pcCurrent);
bool ClearDeletedPath(CIndexTreeNodeFile* pcNode);
bool ClearDirtyPath(CIndexTreeNodeFile* pcNode);
bool RemoveSetPaths(CIndexTreeNodeFile* pcCurrent);
bool DirtySetPaths(CIndexTreeNodeFile* pcCurrent);
bool RecurseIsFlushed(CIndexTreeRecursor* pcCursor);
CFileDataIndex ReadRootFileIndex(void);
bool WriteRootFileIndex(CFileDataIndex* pcRootIndex);
CIndexTreeNodeFile* DebugNode(CChars* pszDest, CIndexTreeNodeFile* pcParent, size uiIndexInParent, bool bShowFlags, bool bShowSize);
void DebugNode(CChars* pszDest, uint32 iFile, uint32 uiIndex, size uIndexFromParent, bool bShowFlags, bool bShowSize);
void DebugNodeChildren(CChars* pszDest, CIndexTreeNodeFile* pcCurrent, size uIndexFromParent, bool bShowFlags, bool bShowSize);
void ReadDebugNode(SIndexTreeDebugNode* psDebugNode, uint32 iFile, uint32 uiIndex);
void PrintChildFileIndexes(CIndexTreeNodeFile* pcCurrent, CChars* psz);
void PrintNodeFileIndexes(CIndexTreeNodeFile* pcCurrent, CChars* psz);
void RecurseDump(CChars* pszDest, CIndexTreeRecursor* pcCursor, bool bShowFlags, bool bShowSize);
void DiagnosticFlushCallback(CIndexTreeNodeFile* pcNode);
void DiagnosticEvictCallback(CIndexTreeNodeFile* pcNode);
};
class CDataReader
{
public:
virtual void Kill(void) =0;
virtual bool Get(OIndex oi, void* pvData) =0;
virtual bool Get(OIndex oi, size* puiDataSize, void* pvData, size uiMaxDataSize) =0;
virtual bool Get(const char* szName, void* pvData) =0;
virtual bool Get(const char* szName, size* puiDataSize, void* pvData, size uiMaxDataSize) =0;
virtual bool Get(CChars* szName, void* pvData) =0;
virtual bool Get(CChars* szName, size* puiDataSize, void* pvData, size uiMaxDataSize) =0;
virtual bool GetName(OIndex oi, CChars* szName) =0;
virtual bool GetName(OIndex oi, char* szName, size* puiNameLength, size uiMaxNameLength) =0;
virtual OIndex GetIndex(const char* szName) =0;
virtual OIndex GetIndex(CChars* szName) =0;
virtual bool Contains(OIndex oi) =0;
virtual bool Contains(const char* szName) =0;
virtual bool Contains(CChars* szName) =0;
virtual OIndex StartIndexIteration(SIndexTreeFileIterator* psIterator, void* pvData, size* piDataSize, size iMaxDataSize) =0;
virtual OIndex IndexIterate(SIndexTreeFileIterator* psIterator, void* pvData, size* piDataSize, size iMaxDataSize) =0;
virtual bool StartNameIteration(SIndexTreeFileIterator* psIterator, char* szKey, OIndex* poi) =0;
virtual bool NameIterate(SIndexTreeFileIterator* psIterator, char* szKey, OIndex* poi) =0;
};
class CDataConnection : public CDataReader
{
public:
virtual bool Add(OIndex oi, void* pvData, size uiDataSize) =0;
virtual bool Add(OIndex oi, const char* szName, void* pvData, size uiDataSize) =0;
virtual bool Add(OIndex oi, CChars* szName, void* pvData, size uiDataSize) =0;
virtual bool Set(OIndex oi, void* pvData) =0;
virtual bool Set(OIndex oi, void* pvData, size uiDataSize) =0;
virtual bool Set(const char* szName, void* pvData) =0;
virtual bool Set(const char* szName, void* pvData, size uiDataSize) =0;
virtual bool Set(CChars* szName, void* pvData) =0;
virtual bool Set(CChars* szName, void* pvData, size uiDataSize) =0;
virtual bool Put(OIndex oi, void* pvData, size uiDataSize) =0;
virtual bool Put(OIndex oi, const char* szName, void* pvData, size uiDataSize) =0;
virtual bool Put(OIndex oi, CChars* szName, void* pvData, size uiDataSize) =0;
virtual bool Remove(OIndex oi) =0;
virtual bool Remove(const char* szName) =0;
virtual bool Remove(CChars* szName) =0;
virtual bool Flush(void) =0;
virtual bool Flush(bool bClearCache) =0;
virtual bool IsWriteThrough(void) =0;
};
class CIndexTreeDataOrderer;
class CIndexTreeNodeMemory : public CIndexTreeNode
{
public:
void Init(CIndexTree* pcIndexTree, CIndexTreeNode* pcParent, size uiFirstIndex, size uiLastIndex, size uiIndexInParent);
void Init(CIndexTree* pcIndexTree, CIndexTreeNode* pcParent, size uiIndexInParent);
CIndexTreeNodeMemory* Get(size uiIndex);
void Set(size uiIndex, CIndexTreeNodeMemory* pcNode);
void ClearIndex(size uiIndex);
bool ClearAndUncontain(size uiIndex);
CIndexTreeNodeMemory* GetNode(size i);
CIndexTreeNodeMemory** GetNodes(void);
size NumValidIndexes(void);
CIndexTreeNodeMemory* GetParent(void);
void RemapChildNodes(CIndexTreeNodeMemory* pcOldNode, CIndexTreeNodeMemory* pcNewNode);
void RemapvDataLinks(CIndexTreeNodeMemory* pcOldNode, CIndexTreeDataOrderer* pcDataOrderer);
void Contain(size uiIndex);
size FindPrevLastIndex(void);
size FindNextFirstIndex(void);
size FindIndex(CIndexTreeNodeMemory* pcChild);
void SetChildrensParent(void);
bool ValidateNodesEmpty(void);
void Print(CChars* psz, bool bHex);
void Dump(void);
bool Uncontain(size uiIndex);
};
class CAccessDataOrderer : public CIndexTreeDataOrderer
{
public:const char* ClassName(void){ return "CAccessDataOrderer";}size ClassSize(void){ return sizeof(CAccessDataOrderer);}
public:
void Init(void);
void Kill(void);
void Put(CIndexTreeDataNode* psNode);
void Get(CIndexTreeDataNode* psNode);
void Remove(CIndexTreeDataNode* psNode);
void HasKey(CIndexTreeDataNode* psNode);
public:
static CLifeInit<CIndexTreeDataOrderer> Create(void);
};
class CIndexTreeConfig
{
protected:
CLifeInit<CMallocator> mcMalloc;
CLifeInit<CIndexTreeDataOrderer> mcDataOrderer;
size miMaxDataSize;
size miMaxKeySize;
EIndexKeyReverse meKeyReverse;
public:
void Init(CLifeInit<CMallocator> cMalloc, EIndexKeyReverse eKeyReverse, size iMaxDataSize, size iMaxKeySize, CLifeInit<CIndexTreeDataOrderer> cDataOrderer);
bool Init(CFileReader* pcFileReader);
virtual void Kill(void) =0;
virtual bool Write(CFileWriter* pcFileWrite);
CLifeInit<CMallocator> GetMalloc(void);
EIndexKeyReverse GetKeyReverse(void);
size GetMaxDataSize(void);
size GetMaxKeySize(void);
CLifeInit<CIndexTreeDataOrderer> GetDataOrderer(void);
protected:
virtual bool Read(CFileReader* pcFileReader);
EIndexKeyReverse ReadKeyReverse(CFileReader* pcFileReader);
bool WriteKeyReverse(CFileWriter* pcFileWriter, EIndexKeyReverse eKeyReverse);
CIndexTreeDataOrderer* ReadDataOrderer(CFileReader* pcFileReader);
bool WriteDataOrderer(CFileWriter* pcFileWriter, CIndexTreeDataOrderer*);
};
class CIndexTreeMemoryConfig : public CIndexTreeConfig
{
public:
void Init(CLifeInit<CMallocator> cMalloc, EIndexKeyReverse eKeyReverse, int iMaxDataSize, int iMaxKeySize, CLifeInit<CIndexTreeDataOrderer> cDataOrderer);
bool Init(CFileReader* pcFileReader);
void Kill(void);
bool Write(CFileWriter* pcFileWriter);
bool Read(CFileReader* pcFileReader);
};
struct SIndexTreeMemoryUnsafeIterator
{
CIndexTreeNodeMemory* pcNode;
size iIndex;
};
struct SIndexTreeMemoryIterator
{
CArrayTemplateEmbedded<uint8, 16> acKey;
size iKeyLength;
size iIndex;
void Init(void);
void Kill(void);
bool IsLive(void);
};
struct SIndexIOElement
{
size iKeySize;
size iValueSize;
void* pvData;
void Init(size iKeySize, size iValueSize, void* pvData);
};
class CIndexTreeDataSize
{
public:
virtual size AdjustDataSize(void* pvValue, size iValueSize) =0;
};
class CIndexTreeMemory : public CIndexTree, public CDataIO, public CIndexTreeDataSize
{
friend class CIndexTreeWriter;
friend class CIndexTreeMemoryIterator;
protected:
CIndexTreeNodeMemory* mpcRoot;
size miSize;
CDataFree* mpcDataFree;
CDataIO* mpcDataIO;
CIndexTreeDataSize* mpcDataSize;
public:
void _Init(void);
void Init(void);
void Init(EIndexKeyReverse eKeyReverse);
void Init(EIndexKeyReverse eKeyReverse, CLifeInit<CIndexTreeDataOrderer> cDataOrderer);
void Init(CLifeInit<CMallocator> cMalloc, EIndexKeyReverse eKeyReverse);
void Init(CLifeInit<CMallocator> cMalloc, EIndexKeyReverse eKeyReverse, size iMaxDataSize, size iMaxKeySize);
void Init(CLifeInit<CMallocator> cMalloc, CDataIO* pcDataIO, CIndexTreeDataSize* pcDataSize, CDataFree* pcDataFree);
void Init(CIndexTreeConfig* pcConfig, CDataIO* pcDataIO, CIndexTreeDataSize* pcDataSize, CDataFree* pcDataFree);
void Init(CLifeInit<CMallocator> cMalloc, EIndexKeyReverse eKeyReverse, size iMaxDataSize, size iMaxKeySize, CLifeInit<CIndexTreeDataOrderer> cDataOrderer);
void Init(CLifeInit<CMallocator> cMalloc, EIndexKeyReverse eKeyReverse, size iMaxDataSize, size iMaxKeySize, CLifeInit<CIndexTreeDataOrderer> cDataOrderer, CDataIO* pcDataIO, CIndexTreeDataSize* pcDataSize, CDataFree* pcDataFree);
void Kill(void) override;
void ReInit(void) override;
bool Get(uint8* pvKey, size iKeySize, void* pvDestData, size* puiDataSize, size uiMaxDataSize);
bool GetLongestPartial(uint8* pvKey, size iKeySize, void* pvDestData, size* puiDataSize, size uiMaxDataSize);
void* Put(uint8* pvKey, size iKeySize, const void* pvData, size iDataSize);
bool Remove(uint8* pvKey, size iKeySize);
bool HasKey(uint8* pvKey, size iKeySize);
size GetDataSize(uint8* pvKey, size iKeySize);
void FindAll(CArrayVoidPtr* papvElements);
size GetKey(void* pvData, uint8* pvDestKey, size iDestKeySize);
size NumElements(void);
void SetDataFreeCallback(CDataFree* pcDataFree);
void SetDataIOCallback(CDataIO* pcDataIO, CIndexTreeDataSize* pcDataSize);
bool StartIteration(SIndexTreeMemoryIterator* psIterator, uint8* pvKey, size* piKeySize, size iMaxKeySize, void* pvData, size* puiDataSize, size uiMaxDataSize);
bool Iterate(SIndexTreeMemoryIterator* psIterator, uint8* pvKey, size* piKeySize, size iMaxKeySize, void* pvData, size* puiDataSize, size uiMaxDataSize);
bool StartIteration(SIndexTreeMemoryUnsafeIterator* psIterator, uint8* pvKey, size* piKeySize, size iMaxKeySize, void** ppvData, size* puiDataSize);
bool Iterate(SIndexTreeMemoryUnsafeIterator* psIterator, uint8* pvKey, size* piKeySize, size iMaxKeySize, void** ppvData, size* puiDataSize);
bool StartIteration(SIndexTreeMemoryUnsafeIterator* psIterator, void** ppvData, size* puiDataSize);
bool Iterate(SIndexTreeMemoryUnsafeIterator* psIterator, void** ppvData, size* puiDataSize);
size ByteSize(void);
bool Write(CFileWriter* pcFileWriter);
bool Read(CFileReader* pcFileReader);
bool Read(CFileReader* pcFileReader, CDataIO* pcDataIO, CIndexTreeDataSize* pcDataSize, CDataFree* pcDataFree);
bool WriteConfig(CFileWriter* pcFileWriter);
bool ReadConfig(CFileReader* pcFileReader, CDataIO* pcDataIO, CIndexTreeDataSize* pcDataSize, CDataFree* pcDataFree);
bool WriteElement(CFileWriter* pcFileWriter, void* pvKey, size iKeySize, void* pvData, size iDataSize);
bool ReadElement(CFileReader* pcFileReader);
bool WriteIndexTreeHeader(CFileWriter* pcFileWriter);
size ReadIndexTreeHeader(CFileReader* pcFileReader);
size ReadIndexTreeHeader(CFileReader* pcFileReader, CDataIO* pcDataIO, CIndexTreeDataSize* pcDataSize, CDataFree* pcDataFree);
bool WriteElements(CFileWriter* pcFileWriter);
bool ReadElements(CFileReader* pcFileReader, size iCount);
bool WriteData(CFileWriter* pcFileWriter, void* pvData) override;
bool ReadData(CFileReader* pcFileReader, void* pvData) override;
bool ValidateIndexTree(void);
CIndexTreeNodeMemory* GetRoot(void);
size CountListSize(void);
size NonNullElements(void);
void Print(CChars* pszDest, bool bShowFlags, bool bShowSize);
void Dump(void);
protected:
CIndexTreeNodeMemory* GetNode(uint8* pvKey, size iKeySize);
CIndexTreeNodeMemory* GetNodeFromLongestPartialKey(uint8* pvKey, size iKeySize);
CIndexTreeNodeMemory* GetNodeForData(void* pvData);
size GetNodeKeySize(CIndexTreeNode* pcNode);
size GetNodeKey(CIndexTreeNode* pcNode, uint8* pvDestKey, size iDestKeySize);
size GetNodeDataSize(CIndexTreeNode* pcNode);
size GetNodeData(CIndexTreeNode* pcNode, void* pvDestData, size iDestDataSize);
bool GetNodeData(CIndexTreeNodeMemory* pcNode, size& uiDataSize, size* puiDataSize, void* pvDestData, size uiMaxDataSize);
void RecurseKill(CIndexTreeNodeMemory* pcNode);
CIndexTreeNodeMemory* AllocateRoot(void);
CIndexTreeNodeMemory* AllocateNode(CIndexTreeNodeMemory* pcParent, size uiIndexInParent);
bool Remove(CIndexTreeNodeMemory* pcCurrent);
CIndexTreeNodeMemory* ReallocateNodeForIndex(CIndexTreeNodeMemory* pcNode, size uiIndex);
CIndexTreeNodeMemory* ReallocateNodeForLargerData(CIndexTreeNodeMemory* pcNode, const void* pvData, size uiDataSize);
CIndexTreeNodeMemory* ReallocateNodeForSmallerData(CIndexTreeNodeMemory* pcNode, const void* pvData, size uiDataSize);
CIndexTreeNodeMemory* ReallocateNodeForRemove(CIndexTreeNodeMemory* pcNode, size tNewNodeSize);
CIndexTreeNodeMemory* GetOrAllocateKey(uint8* pvKey, size iKeySize);
CIndexTreeNodeMemory* SetNodeData(CIndexTreeNodeMemory* pcCurrent, const void* pvData, size uiDataSize);
void RemapNodePointers(CIndexTreeNodeMemory* pcOldNode, CIndexTreeNodeMemory* pcNode);
CIndexTreeNodeMemory* SetOldWithCurrent(CIndexTreeNodeMemory* pcParent, size uiIndexInParent);
void RecurseFindAll(CIndexTreeNodeMemory* pcNode, CArrayVoidPtr* papvElements);
size RecurseSize(CIndexTreeNodeMemory* pcNode);
size RecurseNumNodes(CIndexTreeNodeMemory* pcNode);
size RecurseCountListSize(CIndexTreeNodeMemory* pcNode);
size RecurseByteSize(CIndexTreeNodeMemory* pcNode);
bool ValidateLimits(void);
bool RecurseValidateLimits(CIndexTreeRecursor* pcCursor);
bool ValidateParentIndex(void);
bool RecurseValidateParentIndex(CIndexTreeRecursor* pcCursor);
bool ValidateNodeTree(void);
bool RecurseValidateNodeTree(CIndexTreeRecursor* pcCursor);
size RecurseNonNullElements(CIndexTreeNodeMemory* pcNode);
size NumAllocatedNodes(void);
bool StepNext(SIndexTreeMemoryUnsafeIterator* psIterator);
void SetIteratorKey(SIndexTreeMemoryIterator* psIterator, CIndexTreeNodeMemory* pcNode);
bool ValidateSize(void);
size RecurseSize(void);
void PrintChildren(CChars* pszDest, bool bShowFlags, bool bShowSize);
void DebugNodeChildren(CChars* pszDest, CIndexTreeNodeMemory* pcCurrent, size uIndexFromParent, bool bShowFlags, bool bShowSize);
void RecursePrintNodes(CChars* pszDest, CIndexTreeRecursor* pcCursor, bool bShowFlags, bool bShowSize);
void DebugKey(CChars* pszDest, uint8* pvKey, size iKeySize, bool bSkipRoot, bool bShowFlags, bool bShowSize, bool bKeyAlreadyReversed);
CIndexTreeNodeMemory* DebugNode(CChars* pszDest, CIndexTreeNodeMemory* pcParent, size uiIndexInParent, bool bShowFlags, bool bShowSize);
size AdjustDataSize(void* pvValue, size iValueSize);
};
struct SIndexesIterator : public SIndexTreeMemoryIterator
{
};
class CIndexedObjects
{
protected:
CIndexTreeMemory mcIndexes;
public:
void Init(void);
void Kill(void);
CBaseObject* Get(OIndex oi);
bool Has(OIndex oi);
bool Add(OIndex oi, CBaseObject* pvMemory);
bool Remove(OIndex oi);
size NumIndexed(void);
void Print(CChars* pszDest, bool bShowFlags, bool bShowSize);
OIndex StartIteration(SIndexesIterator* psIterator);
OIndex Iterate(SIndexesIterator* psIterator);
CIndexTreeMemory* GetIndexes(void);
};
class CNamedIndexedObjects
{
protected:
CIndexTreeMemory mcMemoryNames;
CIndexedObjects mcMemoryIndexedObjects;
public:
void Init(void);
void Kill(void);
void ReInit(void);
CBaseObject* Get(OIndex oi);
CBaseObject* Get(const char* szName);
CBaseObject* Get(const char* szObjectName, OIndex oi);
bool Has(OIndex oi);
bool Has(char* szName);
bool AddIntoMemoryWithIndex(CBaseObject* pvObject);
bool AddIntoMemoryWithNameAndIndex(CBaseObject* pvObject);
bool RemoveIndex(OIndex oi);
bool RemoveName(char* szName);
size NumIndexed(void);
size NumNames(void);
CIndexedObjects* GetObjects(void);
CIndexTreeMemory* GetNames(void);
CBaseObject* StartIteration(SIndexesIterator* psIter);
CBaseObject* Iterate(SIndexesIterator* psIter);
bool ValidateNoDirty(void);
bool FreeObjects(void);
bool RemoveIdentifiers(CBaseObject* pcObject);
void FreeObject(CBaseObject* pcObject);
void Dump(void);
};
class CGeneralMemory : public CBaseMemory
{
private:
CLinkListFreeList mcFreeLists;
CLinkedListBlockAligned mcLargeList;
CArrayFreeListAlignedDesc mcOrder;
CMemoryFreeListParams mcFreeListParams;
uint8 miDefaultAlignment;
CArrayFreeListPtrs mcDefaultFreeLists;
size muiAllocCount;
size muiBreakAlloc;
bool mbBreakOnAlloc;
public:
void Init(void);
void Init(uint16 iDefaultAlignment, bool bDefaultFreeListParams = true);
void Kill(void);
void Compact(void);
void* Add(size iSize);
void* Add(size iSize, uint16 iAlignment, int16 iOffset = 0);
bool Remove(void* pv);
size RemoveMultiple(CArrayVoidPtr* pav);
size GetSize(void* pv);
SFNode* GetNode(void* pv);
CFreeList* GetFreeList(size iElementSize, uint16 iAlignment, int16 iOffset);
CFreeList* GetFreeList(size iElementSize);
void* Grow(void* pvInitial, size iSize);
void SetDebugName(void* pv, char (*pszDebug)[4]);
void BreakOnAdd(size uiAllocCount);
size NumElements(void);
size ByteSize(void);
CMemoryFreeListParams* GetFreeListParams(void);
size GetDefaultAlignment(void);
SMemory StartIteration(SMemoryIterator* psIterator);
SMemory Iterate(SMemoryIterator* psIterator);
uint64 GetTotalAllocatedMemory(void);
uint64 GetTotalAllocations(void);
CFreeList* TestGetFreeListsHead(void);
void* TestGetLargeListsHead(void);
size NumFreeLists(void);
protected:
size RemoveNode(CArrayVoidPtr* pav, size i, SGeneralMemoryAllocation* psAlloc, SFNode* psNode, CFreeList* pcList);
size RemoveElements(CArrayVoidPtr* pav, size i, SFNode* psNode, CFreeList* pcList);
private:
CFreeList* GetOrAddFreeList(size iElementSize, uint16 iAlignment, int16 iOffset);
void* AllocateInFreeList(CFreeList* pcFreeList, size uiElementSize);
bool DeallocateInFreeList(CFreeList* pcFreeList, SGeneralMemoryAllocation* psAlloc);
void FreeFreeList(CFreeList* pcFreeList);
void* AllocateInLargeList(size uiSize, uint16 iAlignment, int16 iOffset);
bool DeallocateInLargeList(SGeneralMemoryAllocation* psAlloc);
void CopyAllocation(void* pvDest, void* pvSource, size uiDestSize, size uiSourceSize);
};
class CLocalMallocator : public CMallocator
{
public:
virtual void Kill(void) =0;
bool IsLocal(void) override;
virtual bool Read(CFileReader* pcFileReader) =0;
virtual bool Write(CFileWriter* pcFileWriter) =0;
const char* ShortName(void);
};
class CMemoryAllocator : public CLocalMallocator
{
public:const char* ClassName(void){ return "CMemoryAllocator";}size ClassSize(void){ return sizeof(CMemoryAllocator);}
protected:
CGeneralMemory mcMemory;
public:
void Init(void);
void Init(int iDefaultAlignment, bool bDefaultFreeListParams = true);
void Kill(void);
void* Malloc(lsize uiSize) override;
void* Malloc(lsize uiSize, char(**pacDebugName)[4]) override;
void* Realloc(void* pv, lsize uiSize) override;
bool Free(void* pv) override;
size FreeMultiple(CArrayVoidPtr* pav) override;
const char* GetName(void);
bool Read(CFileReader* pcFileReader) override;
bool Write(CFileWriter* pcFileWriter) override;
CGeneralMemory* GetMemory(void);
size SizeOffset(void);
public:
static CLifeInit<CMallocator> Create(void);
static CLifeInit<CMallocator> Create(int iDefaultAlignment, bool bDefaultFreeListParams = true);
};
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
class CConstructors
{
protected:
CMapStringBlock mcConstructors;
public:
void Init(void);
void Kill(void);
template<class M> M* Add(const char* szClassName);
template<class M> M* Add(void);
template<class M> M* Get(void);
template<class M> M* Get(size* puiSize);
void* Get(const char* szConstructorName, size* puiSize);
void* Construct(const char* szConstructorName, CMallocator* pcMalloc, char(**pacDebugName)[4] = 0L);
void* Construct(const char* szConstructorName, CMallocator* pcMalloc, size uiAdditionalSize, char(**pacDebugName)[4] = 0L);
size NumConstructors(void);
bool Contains(const char* szName);
bool ValidateMemoryInitialised(void);
protected:
bool ValidateNotAdded(const char* szClassName);
};
template<class M>
M* StackConstruct(CStackMemory<>* pcStack)
{
M* pvM;
size iSize;
iSize = sizeof(M);
pvM = (M*)pcStack->Init(iSize);
memset(pvM, 0, iSize);
new(pvM) M();
return pvM;
}
template<class M>
M* CConstructors::Add(const char* szClassName)
{
M* pvM;
int iSize;
if (!ValidateNotAdded(szClassName))
{
return 0L;
}
iSize = sizeof(M);
pvM = (M*)mcConstructors.Put(szClassName, iSize);
memset(pvM, 0, iSize);
new(pvM) M();
return pvM;
}
template<class M>
M* CConstructors::Add(void)
{
M* pvM;
size iSize;
CStackMemory<> cStack;
const char* szClassName;
bool bResult;
pvM = StackConstruct<M>(&cStack);
szClassName = pvM->ClassName();
if (!ValidateNotAdded(szClassName))
{
cStack.Kill();
return 0L;
}
iSize = pvM->ClassSize();
bResult = mcConstructors.Put(szClassName, pvM, iSize);
if (!bResult)
{
cStack.Kill();
return 0L;
}
pvM = (M*)mcConstructors.Get(szClassName);
cStack.Kill();
return pvM;
}
template<class M>
M* CConstructors::Get(void)
{
M* pvM1;
M* pvM2;
CStackMemory<> cStack;
const char* szClassName;
pvM1 = StackConstruct<M>(&cStack);
szClassName = pvM1->ClassName();
pvM2 = (M*)mcConstructors.Get(szClassName);
if (pvM2)
{
if (StringCompare(pvM2->ClassName(), szClassName) == 0)
{
cStack.Kill();
return pvM2;
}
}
cStack.Kill();
return 0L;
}
template<class M>
M* CConstructors::Get(size* puiSize)
{
M* pvM1;
M* pvM2;
CStackMemory<> cStack;
const char* szClassName;
pvM1 = StackConstruct<M>(&cStack);
szClassName = pvM1->ClassName();
pvM2 = (M*)mcConstructors.Get(szClassName, puiSize);
if (pvM2)
{
if (StringCompare(pvM2->ClassName(), szClassName) == 0)
{
cStack.Kill();
return pvM2;
}
}
cStack.Kill();
return 0L;
}
class CUnknown;
typedef CArrayTemplatePtr<CUnknown> CArrayUnknownPtr;
class CIterableList;
template<class M>
class SIteratorTemplate
{
public:
CIterableList* pcList;
SFreeListIterator sIter;
};
class SIteratorUnknown
{
public:
CIterableList* pcList;
SFreeListIterator sIter;
};
class CIterableList
{
public:
CFreeList mcFreeListPtrs;
CChars mszName;
void Init(const char* szName);
void Kill(void);
void Add(CUnknown* pcUnknown);
bool Remove(CUnknown* pcUnknown);
bool Is(const char* szName);
template<class M>
M* StartIteration(SIteratorTemplate<M>* psIter);
template<class M>
M* Iterate(SIteratorTemplate<M>* psIter);
CUnknown* StartIteration(SIteratorUnknown* psIter);
CUnknown* Iterate(SIteratorUnknown* psIter);
};
typedef CLinkedListTemplate<CIterableList> CLinkListIterableList;
class CIterables
{
public:
CLinkListIterableList mcIterableLists;
void Init(void);
void Kill(void);
template<class M>
M* StartIteration(SIteratorTemplate<M>* psIter);
template<class M>
M* Iterate(SIteratorTemplate<M>* psIter);
CUnknown* StartIteration(char* szName, SIteratorUnknown* psIter);
CUnknown* Iterate(SIteratorUnknown* psIter);
void Add(CUnknown* pcUnknown);
bool Remove(CUnknown* pcUnknown);
template<class M>
void RemoveDuringIteration(SIteratorTemplate<M>* psIter);
};
template<class M>
M* CIterableList::StartIteration(SIteratorTemplate<M>* psIter)
{
M** ppv;
psIter->pcList = this;
ppv = (M**)mcFreeListPtrs.StartIteration(&psIter->sIter);
if (ppv)
{
return *ppv;
}
return 0L;
}
template<class M>
M* CIterableList::Iterate(SIteratorTemplate<M>* psIter)
{
M** ppv;
ppv = (M**)mcFreeListPtrs.Iterate(&psIter->sIter);
if (ppv)
{
return *ppv;
}
return 0L;
}
template<class M>
M* CIterables::StartIteration(SIteratorTemplate<M>* psIter)
{
CIterableList* pcList;
M vTemp;
if (vTemp.Iterable())
{
pcList = mcIterableLists.GetHead();
while (pcList)
{
if (pcList->Is(vTemp.ClassName()))
{
return pcList->StartIteration(psIter);
}
pcList = mcIterableLists.GetNext(pcList);
}
psIter->pcList = 0L;
psIter->sIter.psCurrent = 0L;
}
return 0L;
}
template<class M>
M* CIterables::Iterate(SIteratorTemplate<M>* psIter)
{
M** ppv;
if (psIter->pcList)
{
ppv = (M**)psIter->pcList->mcFreeListPtrs.Iterate(&psIter->sIter);
if (ppv)
{
return *ppv;
}
}
return 0L;
}
template<class M>
void CIterables::RemoveDuringIteration(SIteratorTemplate<M>* psIter)
{
M** ppv;
ppv = (M**)psIter->pcList->mcFreeListPtrs.GetElement(psIter->sIter.psCurrent, psIter->sIter.iPosition);
psIter->pcList->mcFreeListPtrs.RemoveDuringIteration(&psIter->sIter);
if (ppv)
{
(*ppv)->Kill();
}
}
class CUnknowns
{
protected:
CIterables mcIterables;
CChars mszName;
CConstructors* mpcConstructors;
CLife<CMallocator> mcMallocLife;
CMallocator* mpcMalloc;
size miNumElements;
public:
void Init(const char* szName, CConstructors* pcConstructors);
void Init(CLifeInit<CMallocator> cMalloc, const char* szName, CConstructors* pcConstructors);
void Kill(void);
bool Remove(CUnknown* pcUnknown);
template<class M> M* Add(void);
template<class M> M* Add(size uiAdditionalSize);
CUnknown* Add(const char* szClassName);
CUnknown* Add(const char* szClassName, size uiAdditionalSize);
CUnknown* AddFromHeader(CFileReader* pcFile);
template<class M> void AddConstructor(void);
template<class M> M* GetConstructor(void);
template<class M> M* GetConstructor(size* puiSize);
CConstructors* GetConstructors(void);
bool LoadUnknown(CFileReader* pcFile, CUnknown** ppcUnknown);
bool SaveUnknown(CFileWriter* pcFile, CUnknown* pcUnknown);
template<class M> M* StartIteration(SIteratorTemplate<M>* psIter);
template<class M> M* Iterate(SIteratorTemplate<M>* psIter);
CUnknown* StartIteration(char* szClassName, SIteratorUnknown* psIter);
CUnknown* Iterate(SIteratorUnknown* psIter);
template<class M> void RemoveDuringIteration(SIteratorTemplate<M>* psIter);
void DumpAllocationDetail(CUnknown* pcUnknown);
size NumElements(void);
void Dump(void);
size GetIterableListsHeadNumElements(void);
void RemoveInKill(CUnknown* pcUnknown);
void RemoveInKill(CArrayUnknownPtr* papcObjectPts);
protected:
CUnknown* AddExisting(CUnknown* pcExisting, char(*pszDebug)[4]);
void DebugName(CUnknown* pcUnknown, char (*pszDebug)[4]);
bool IsFreed(CUnknown* pcUnknown);
};
extern CUnknowns gcUnknowns;
extern bool gbUnknowns;
void UnknownsInit(void);
void UnknownsKill(void);
template<class M>
M* CUnknowns::Add(void)
{
return Add<M>(0);
}
template<class M>
M* CUnknowns::Add(size uiAdditionalSize)
{
M* pv;
char(* acDebug)[4];
size uiSize;
uiSize = sizeof(M);
pv = (M*)mpcMalloc->Malloc(uiSize + uiAdditionalSize, &acDebug);
if (pv)
{
memset(pv, 0, uiSize + uiAdditionalSize);
new(pv) M();
if (!pv->IsUnknown())
{
mpcMalloc->Free(pv);
return 0L;
}
pv = (M*)AddExisting(pv, acDebug);
return pv;
}
else
{
return 0L;
}
}
template<class M>
M* CUnknowns::StartIteration(SIteratorTemplate<M>* psIter)
{
return mcIterables.StartIteration(psIter);
}
template<class M>
M* CUnknowns::Iterate(SIteratorTemplate<M>* psIter)
{
return mcIterables.Iterate(psIter);
}
template<class M>
void CUnknowns::RemoveDuringIteration(SIteratorTemplate<M>* psIter)
{
mcIterables.RemoveDuringIteration(psIter);
}
template<class M>
void CUnknowns::AddConstructor(void)
{
if (mpcConstructors)
{
mpcConstructors->Add<M>();
}
else
{
gcLogger.Error2(MethodToString("/home/r2d2/Codaphela/commonlibraries/StandardLib/Unknowns.h", 190, __PRETTY_FUNCTION__), " Constructors for Unknowns is NULL.", 0L);
}
}
template<class M>
M* CUnknowns::GetConstructor(void)
{
if (mpcConstructors)
{
return mpcConstructors->Get<M>();
}
else
{
gcLogger.Error2(MethodToString("/home/r2d2/Codaphela/commonlibraries/StandardLib/Unknowns.h", 208, __PRETTY_FUNCTION__), " Constructors for Unknowns is NULL.", 0L);
return 0L;
}
}
template<class M>
M* CUnknowns::GetConstructor(size* puiSize)
{
if (mpcConstructors)
{
return mpcConstructors->Get<M>(puiSize);
}
else
{
gcLogger.Error2(MethodToString("/home/r2d2/Codaphela/commonlibraries/StandardLib/Unknowns.h", 227, __PRETTY_FUNCTION__), " Constructors for Unknowns is NULL.", 0L);
return 0L;
}
}
CPointer Null(void);
template<class M>
Ptr<M> Null(void);
template<class M>
Ptr<M> Null(void)
{
return Ptr<M>();
}
enum EFileNodeType
{
FNT_Unknown,
FNT_Directory,
FNT_File,
};
class CBaseFileNode
{
protected:
CChars mszName;
EFileNodeType meType;
CBaseFileNode* mpcParent;
public:
void Init(const char* szName, EFileNodeType eType, CBaseFileNode* pcParent);
void Kill(void);
char* GetName(void);
char* GetFullName(CChars* pszDest);
bool Is(const char* szName);
bool IsDirectory(void);
bool IsFile(void);
CBaseFileNode* GetParent(void);
};
template <class M>
class CFileNode;
template <class M>
class CFileNodeDirectory
{
friend class CPackFiles;
friend class CFileSystem;
protected:
CFreeList maNodeFiles;
public:
void Init(void);
void Kill(void);
CFileNode<M>* Get(const char* szName);
CFileNode<M>* AddFile(char* szName, CFileNode<M>* pcParent);
CFileNode<M>* AddDirectory(const char* szName, CFileNode<M>* pcParent);
void FixParents(CFileNode<M>* pcContaintingNode);
};
template <class M>
void CFileNodeDirectory<M>::Init(void)
{
maNodeFiles.Init(sizeof(CFileNode<M>));
}
template <class M>
void CFileNodeDirectory<M>::Kill(void)
{
size i;
CFileNode<M>* pcChild;
for (i = 0; i < maNodeFiles.NumElements(); i++)
{
pcChild = (CFileNode<M>*)maNodeFiles.Get(i);
pcChild->Kill();
}
maNodeFiles.Kill();
}
template <class M>
CFileNode<M>* CFileNodeDirectory<M>::Get(const char* szName)
{
size i;
CFileNode<M>* pcNode;
for (i = 0; i < maNodeFiles.NumElements(); i++)
{
pcNode = (CFileNode<M>*)maNodeFiles.Get(i);
if (pcNode->Is(szName))
{
return pcNode;
}
}
return 0L;
}
template <class M>
CFileNode<M>* CFileNodeDirectory<M>::AddDirectory(const char* szName, CFileNode<M>* pcParent)
{
CFileNode<M>* pcNode;
pcNode = (CFileNode<M>*)maNodeFiles.Add();
pcNode->InitDirectory(szName, pcParent);
return pcNode;
}
template <class M>
CFileNode<M>* CFileNodeDirectory<M>::AddFile(char* szName, CFileNode<M>* pcParent)
{
CFileNode<M>* pcNode;
pcNode = (CFileNode<M>*)maNodeFiles.Add();
pcNode->InitFile(szName, pcParent);
return pcNode;
}
template <class M>
void CFileNodeDirectory<M>::FixParents(CFileNode<M>* pcContaintingNode)
{
size i;
CFileNode<M>* pcNode;
CFileNodeDirectory<M>* pcDirectory;
for (i = 0; i < maNodeFiles.NumElements(); i++)
{
pcNode = (CFileNode<M>*)maNodeFiles.Get(i);
pcNode->mpcParent = pcContaintingNode;
if (pcNode->IsDirectory())
{
pcDirectory = pcNode->Directory();
pcDirectory->FixParents(pcNode);
}
}
}
class CPackFileNode
{
protected:
filePos muiFilePos;
filePos muiSize;
bool mbNameWritten;
public:
void Init(void);
void Kill(void);
bool Load(CFileReader* pcReader);
bool Save(CFileWriter* pcWriter);
filePos FilePos(void);
filePos Size(void);
bool IsNameWritten(void);
bool IsInitialised(void);
void SetFilePos(filePos iFilePos);
void IncreaseSize(filePos iSize);
};
template <class M>
class CFileNode : public CBaseFileNode
{
friend class CFileNodeDirectory<M>;
protected:
union
{
CFileNodeDirectory<M> msDirectory;
M msFile;
} u;
public:
void InitFile(const char* szName, CFileNode* pcParent);
void InitDirectory(const char* szName, CFileNode* pcParent);
void Kill(void);
CFileNodeDirectory<M>* Directory(void);
M* File(void);
};
template <class M>
void CFileNode<M>::InitFile(const char* szName, CFileNode* pcParent)
{
Init(szName, FNT_File, pcParent);
u.msFile.Init();
}
template <class M>
void CFileNode<M>::InitDirectory(const char* szName, CFileNode* pcParent)
{
Init(szName, FNT_Directory, pcParent);
meType = FNT_Directory;
u.msDirectory.Init();
}
template <class M>
void CFileNode<M>::Kill(void)
{
if (meType == FNT_File)
{
u.msFile.Kill();
}
else if (meType == FNT_Directory)
{
u.msDirectory.Kill();
}
CBaseFileNode::Kill();
}
template <class M>
CFileNodeDirectory<M>* CFileNode<M>::Directory(void)
{
return &u.msDirectory;
}
template <class M>
M* CFileNode<M>::File(void)
{
return &u.msFile;
}
class CPackFiles;
class CPackFile : public CAbstractFile
{
public:
CPackFiles* mpcPackFiles;
CPackFileNode* mpsPackFileNode;
size miPos;
EFileMode meMode;
void Init(CPackFiles* pcPackFiles, CPackFileNode* psPackFileNode);
void Kill(void);
bool Open(EFileMode eFileMode);
bool Close(void);
lsize Read(void* pvBuffer, lsize iSize, lsize iCount);
bool Seek(filePos iOffset, EFileSeekOrigin iSeekOrigin);
lsize Write(const void* pvBuffer, lsize iSize, lsize iCount);
filePos Tell(void);
bool IsOpen(void);
filePos Size(void);
bool Truncate(filePos iSize);
bool Flush(void);
bool Delete(void);
const char* GetFilename(void);
};
CPackFile* PackFile(CPackFiles* pcPackFiles, CPackFileNode* psPackFile);
template <class M>
class CFilenames
{
protected:
CFileNode<M> mcRoot;
bool mbParentsValid;
public:
void Init(void);
void Kill(void);
CFileNode<M>* GetRoot(void);
CFileNode<M>* GetNode(const char* szFullName);
CFileNode<M>* AddFile(const char* szFullName);
M* GetNearestFile(const char* szFullName, CChars* pszRemaining);
void FixParents(void);
};
template <class M>
void CFilenames<M>::Init(void)
{
mcRoot.InitDirectory("", 0L);
mbParentsValid = false;
}
template <class M>
void CFilenames<M>::Kill(void)
{
mcRoot.Kill();
}
template <class M>
CFileNode<M>* CFilenames<M>::GetRoot(void)
{
return &mcRoot;
}
template <class M>
CFileNode<M>* CFilenames<M>::GetNode(const char* szFullName)
{
CChars szFake;
CArrayChars asNames;
size i;
char* szName;
CFileNode<M>* pcCurrent;
CFileNode<M>* pcChild;
asNames.Init();
szFake.Fake(szFullName);
szFake.Split(&asNames, '/');
pcCurrent = &mcRoot;
pcChild = 0L;
for (i = 0; i < asNames.NumElements(); i++)
{
szName = asNames.GetText(i);
if (pcCurrent->IsDirectory())
{
pcChild = pcCurrent->Directory()->Get(szName);
if (pcChild == 0L)
{
break;
}
}
else
{
pcChild = 0L;
break;
}
pcCurrent = pcChild;
}
asNames.Kill();
return pcChild;
}
template <class M>
CFileNode<M>* CFilenames<M>::AddFile(const char* szFullName)
{
CChars szFake;
CArrayChars asNames;
size i;
char* szName;
CFileNode<M>* pcCurrent;
CFileNode<M>* pcChild;
mbParentsValid = false;
asNames.Init();
szFake.Fake(szFullName);
szFake.Split(&asNames, '/');
pcCurrent = &mcRoot;
pcChild = 0L;
for (i = 0; i < asNames.NumElements(); i++)
{
szName = asNames.GetText(i);
if (pcCurrent->IsDirectory())
{
pcChild = pcCurrent->Directory()->Get(szName);
}
else
{
pcChild = 0L;
break;
}
if (pcChild == 0L)
{
if (i != asNames.NumElements() - 1)
{
pcChild = pcCurrent->Directory()->AddDirectory(szName, pcCurrent);
}
else
{
pcChild = pcCurrent->Directory()->AddFile(szName, pcCurrent);
}
}
pcCurrent = pcChild;
}
asNames.Kill();
return pcChild;
}
template <class M>
M* CFilenames<M>::GetNearestFile(const char* szFullName, CChars* pszRemaining)
{
CChars szFake;
CArrayChars asNames;
size i;
CFileNode<M>* pcCurrent;
CFileNode<M>* pcChild;
size iRemain;
CChars* szName;
asNames.Init();
szFake.Fake(szFullName);
szFake.Split(&asNames, '/');
pcCurrent = &mcRoot;
pcChild = 0L;
iRemain = 0;
for (i = 0; i < asNames.NumElements(); i++)
{
szName = asNames.Get(i);
if (pcCurrent->IsDirectory())
{
pcChild = pcCurrent->Directory()->Get(szName->Text());
if (pcChild == 0L)
{
asNames.Kill();
return 0L;
}
}
else
{
pszRemaining->AppendSubString(szFullName, iRemain, szFake.Length());
asNames.Kill();
return pcCurrent->File();
}
iRemain += (szName->Length()+1);
pcCurrent = pcChild;
}
asNames.Kill();
if (pcCurrent->IsFile())
{
return pcCurrent->File();
}
return 0L;
}
template <class M>
void CFilenames<M>::FixParents(void)
{
if (!mbParentsValid)
{
mcRoot.Directory()->FixParents(&mcRoot);
mbParentsValid = true;
}
}
class CFileNodeSystemFile
{
protected:
CChars mszFullPath;
int miExtensionIndex;
public:
void Init(void);
void Kill(void);
char* GetFullName(void);
void SetFullName(char* szFullName);
char* GetExtension(void);
};
typedef CFileNode<CFileNodeSystemFile> CSystemFileNode;
typedef CFileNodeDirectory<CFileNodeSystemFile> CSystemDirectoryNode;
typedef CFilenames<CFileNodeSystemFile> CSystemFilenames;
typedef CArrayTemplatePtr<CSystemFileNode> CArraySystemFilePtr;
struct SFileSystemIteratorPosition
{
CSystemFileNode* pcNode;
int iIndex;
};
typedef CArrayTemplate<SFileSystemIteratorPosition> CArrayFileSystemIteratorPosition;
class CFileSystemIterator
{
protected:
CArrayFileSystemIteratorPosition macDepth;
CSystemFileNode* mpcCurrent;
public:
void Init(void);
void Kill(void);
void Push(CSystemFileNode* pcNode);
SFileSystemIteratorPosition* Peek(void);
void Pop(void);
void SetCurrent(CSystemFileNode* pcNode);
CSystemFileNode* Current(void);
};
class CFileSystem
{
protected:
CSystemFilenames mcNames;
CChars mszDirectory;
public:
void Init(const char* szDirectory);
void Kill(void);
char* GetFilename(const char* szFilename);
CFileNodeSystemFile* GetFileNode(const char* szName, CChars* pszRemainingName);
CChars* GetFullDirectoryName(void);
void GetFiles(CArraySystemFilePtr* pcSystemFiles);
void GetFiles(CArraySystemFilePtr* pcSystemFiles, const char* szExtension);
CSystemFileNode* StartIteration(CFileSystemIterator* psIter);
CSystemFileNode* Iterate(CFileSystemIterator* psIter);
void StopIteration(CFileSystemIterator* psIter);
protected:
void ReadDirectory(void);
};
class CPackFileNode;
struct SPackFileReadPtrPosition
{
CPackFileNode* psPackFile;
filePos iLastReadPos;
};
typedef CArrayTemplate<SPackFileReadPtrPosition> CArrayPackFileReadPtrs;
class CPackFileReadArray
{
protected:
CArrayPackFileReadPtrs maPtrs;
public:
void Init(void);
void Kill(void);
filePos GetReadPos(CPackFileNode* psPackFile);
void SetReadPos(CPackFileNode* psPackFile, filePos iLastReadPos);
void BeginReadPos(CPackFileNode* psPackFile);
};
enum EPackFileMode
{
PFM_Read,
PFM_Write,
};
typedef CFileNode<CPackFileNode> CFileNodePackFileNode;
typedef CFilenames<CPackFileNode> CFilenamesPackFileNode;
typedef CArrayTemplatePtr<CFileNodePackFileNode> CArrayPackFileNodePtrs;
struct SPackFileIteratorPosition
{
CFileNodePackFileNode* pcNode;
size iIndex;
};
typedef CArrayTemplate<SPackFileIteratorPosition> CArrayPackFileIteratorPosition;
class CPackFileIterator
{
protected:
CArrayPackFileIteratorPosition macDepth;
CFileNodePackFileNode* mpcCurrent;
public:
void Init(void);
void Kill(void);
void Push(CFileNodePackFileNode* pcNode);
SPackFileIteratorPosition* Peek(void);
void Pop(void);
void SetCurrent(CFileNodePackFileNode* pcNode);
CFileNodePackFileNode* Current(void);
};
enum EFileIteratorReturnType
{
FIRT_Unknown,
FIRT_FileSystem,
FIRT_PackFiles,
};
class CFileIteratorReturn
{
protected:
EFileIteratorReturnType meType;
CChars mszFullName;
CBaseFileNode* mpsNode;
uint32 miFileRank;
public:
void Init(void);
void Init(EFileIteratorReturnType eType, CBaseFileNode* pcNode, uint32 iFileRank);
void Kill(void);
void InsertInName(size iIndex, const char* szText);
EFileIteratorReturnType GetType(void);
char* GetFullName(void);
CBaseFileNode* GetNode(void);
uint32 GetFileRank(void);
};
class CFileIterator
{
public:
uint32 miPackFileIndex;
CPackFileIterator mcPackFileIterator;
CFileSystemIterator mcFileSystemIterator;
bool mbMoveOn;
bool mbFileSystem;
CFileIteratorReturn mcCurrent;
bool mbHasCurrent;
void Init(void);
void Kill(void);
CFileIteratorReturn* GetCurrent(void);
CFileIteratorReturn* SetCurrent(EFileIteratorReturnType eType, CBaseFileNode* pcNode, int iFileRank, char* szOffset);
CFileIteratorReturn* SetCurrent(void);
};
class CPackFile;
class CPackFiles
{
friend class CPackFile;
protected:
CFileBasic mcFile;
CFilenamesPackFileNode mcNames;
EPackFileMode meMode;
filePos miNodes;
filePos miNextNodesPtr;
CPackFileNode* mpsLastAccessed;
filePos miPosition;
CPackFileReadArray maReads;
public:
bool Init(CAbstractFile* pcFile, EPackFileMode eMode);
void Kill(void);
bool IsWriteMode(void);
bool IsReadMode(void);
CPackFile* WriteOpen(const char* szFilename);
CPackFile* ReadOpen(const char* szFilename);
bool AddFile(CAbstractFile* pcFile, char* szFilename);
bool AddDirectory(const char* szDirectory, const char* szPackDirectory = 0L);
CFileNodePackFileNode* StartIteration(CPackFileIterator* psIter);
CFileNodePackFileNode* Iterate(CPackFileIterator* psIter);
void StopIteration(CPackFileIterator* psIter);
void GetFiles(CArrayPackFileNodePtrs* pcPackFiles);
CFileNodePackFileNode* GetNode(const char* szFullName);
bool Unpack(const char* szDirectory);
void FixParents(void);
const char* GetFilename(void);
protected:
bool BeginRead(void);
bool BeginWrite(void);
bool EndRead(void);
bool EndWrite(void);
bool Close(CPackFile* pcPackFile);
size Read(CPackFileNode* psPackFile, void* pvBuffer, size iSize, size iCount);
bool Seek(CPackFileNode* psPackFile, filePos iOffset, EFileSeekOrigin iSeekOrigin);
size Write(CPackFileNode* psPackFile, const void* pvBuffer, size iSize, size iCount);
filePos Tell(CPackFileNode* psPackFile);
bool Flush(void);
CFileNodePackFileNode* AddFile(const char* szFullName);
size PrivateRead(CPackFileNode* psPackFile, void* pvBuffer, size iSize, size iCount);
bool PrivateSeek(CPackFileNode* psPackFile, filePos iOffset, EFileSeekOrigin iSeekOrigin);
bool ChangeReadFiles(CPackFileNode* psPackFile);
const char* ClassName(void);
bool WriteHeader(void);
bool ReadHeader(void);
bool ReadNodes(void);
bool ReadNode(void);
bool WriteNodes(void);
uint32 GetNumUnwrittenNames(void);
uint32 RecurseGetNumUnwrittenNames(CFileNodePackFileNode* pcNode);
bool WriteUnwrittenNames(void);
bool RecurseWriteUnwrittenNames(CFileNodePackFileNode* pcNode, CChars* pszPath);
bool RecurseUnpack(CFileNodePackFileNode* pcNode, const char* szDestination);
};
class CPackFileOffset
{
public:
CPackFiles mcPackFiles;
CChars mszOffset;
uint32 miFileRank;
bool Init(const char* szPackFileOffset, const char* szPackFileDirectory, uint32 iFileRank);
void Kill(void);
};
typedef CArrayTemplate<CPackFileOffset> CArrayPackFiles;
class CFiles
{
protected:
CFileSystem mcFileSystem;
CArrayPackFiles mcPackFilesArray;
CChars mszPackFilesExtension;
public:
bool Init(const char* szDirectory, const char* szPackFilesExtension);
void Kill(void);
size GetNumPackFiles(void);
CAbstractFile* GetFile(const char* szFullName);
CFileIteratorReturn* StartIteration(CFileIterator* pcIter);
CFileIteratorReturn* Iterate(CFileIterator* pcIter);
void StopIteration(CFileIterator* pcIter);
void GetFilenames(CMapStringInt* cFilenames);
CPackFiles* GetPackFiles(size iIndex);
protected:
CDiskFile* GetSystemFile(const char* szFullName);
CPackFile* GetPackFile(const char* szFullName);
CPackFile* GetPackFile(CPackFileOffset* pcPackFiles, const char* szFullName);
bool AddPackFile(CFileNodeSystemFile* pcFileNodeSystemFile);
bool AddPackFiles(void);
CFileIteratorReturn* IterateOnFileSystem(CFileIterator* pcIter);
CFileIteratorReturn* IterateInPackFiles(CFileIterator* pcIter);
CFileIteratorReturn* IterateInPackFiles(CFileIterator* pcIter, CFileNodePackFileNode* pcPackFileNode, CPackFileOffset* pcPackFiles);
CFileIteratorReturn* IterateFileSystemNode(CFileIterator* pcIter, CSystemFileNode* pcSystemFileNode);
};
int ComparePackFileOffset(const void* arg1, const void* arg2);
struct SSetIterator
{
size iIndex;
bool bStepFirst;
};
enum EArrayUnsetReturn
{
AUR_NoChange,
AUR_SetNull,
AUR_MustRemove,
};
class CArrayCommonUnknown : public CUnknown
{
public:const char* ClassName(void){ return "CArrayCommonUnknown";}size ClassSize(void){ return sizeof(CArrayCommonUnknown);}
protected:
uint16 muiFlags;
DataCompare mfCompare;
private:
CArrayUnknownPtr mcArray;
size miNonNullElements;
bool PrivateIterate(SSetIterator* psIter, CUnknown** ppcUnknown);
void PrivateKill(void);
public:
void _Init(void);
void Init(bool bTypeKnown, bool bKillElements, bool bUnique, bool bIgnoreNull, bool bPreserveOrder, DataCompare fCompare);
void Init(bool bTypeKnown, bool bKillElements, bool bUnique, bool bIgnoreNull, bool bPreserveOrder, DataCompare fCompare, size iChunkSize);
void Kill(void) override;
virtual void ReInit(void);
bool Save(CFileWriter* pcFile) override;
bool Load(CFileReader* pcFile) override;
size NumElements(void);
void KillElements(bool bKill);
void Sort(void);
bool IsSorted(void);
bool CalculateIsSorted(void);
bool IsMustSort(void);
bool Contains(CUnknown* pcUnknown);
size Find(CUnknown* pcUnknown);
size FindNext(CUnknown* pcUnknown, size uiStartIndex);
void CleanNullsIfNecessary(bool bCleanNullsIfNecessary);
void CleanNullsIfNecessary(void);
void CleanNullsBeforeBinarySearch(void);
void CleanNulls(void);
bool Add(CUnknown* pcUnknown, bool bCleanNullsIfNecessary = true);
bool AddAll(CArrayCommonUnknown* pcSource);
bool Set(size iIndex, CUnknown* pcUnknown, bool bCleanNullsIfNecessary = true);
bool Insert(size iIndex, CUnknown* pcUnknown);
size InsertIntoSorted(DataCompare fCompare, CUnknown* pcUnknown, bool bOverwriteExisting);
bool RemoveEnd(size iIndexInclusive);
virtual size Remove(CUnknown* pcUnknown);
bool Remove(size iIndex, bool bCleanNullsIfNecessary = true);
bool RemoveLast(bool bCleanNullsIfNecessary = true);
bool RemoveDuringIteration(SSetIterator* psIter);
EArrayUnsetReturn Unset(size iIndex);
CUnknown* First(void);
CUnknown* Last(void);
bool StartIteration(SSetIterator* psIter, CUnknown** ppcUnknown);
bool Iterate(SSetIterator* psIter, CUnknown** ppcUnknown);
void PreserveOrder(bool bPreserveOrder);
void TypeKnown(bool bTypeKnown);
bool IsKillElements(void);
bool IsEmpty(void);
bool IsNotEmpty(void);
void UnsafeSet(size iIndex, CUnknown* pcUnknown);
CUnknown* UnsafeGet(size iIndex);
CUnknown** UnsafeGetPointer(size iIndex);
size UnsafeNumElements(void);
size UnsafeNonNullElements(void);
bool ReadArrayHeader(CFileReader* pcFile, uint16* piFlags, size* piNumElements);
bool WriteArrayHeader(CFileWriter* pcFile);
void PostLoad(uint16 iFlags);
void SetChunkSize(size iChunkSize);
void GrowTo(size iNumElements);
protected:
virtual bool ReadElement(CFileReader* pcFile, CUnknown** ppcUnknown);
virtual bool WriteElement(CFileWriter* pcFile, CUnknown* pcUnknown);
bool WriteElements(CFileWriter* pcFile);
bool ReadElements(CFileReader* pcFile, size iNumElements);
};
class CArrayUnknown : public CArrayCommonUnknown
{
public:const char* ClassName(void){ return "CArrayUnknown";}size ClassSize(void){ return sizeof(CArrayUnknown);}
public:
void Init(void);
void Kill(void) override;
template<class M>
M* Add(void);
bool Add(CUnknown* pcUnknown);
template<class M>
M* Insert(size iIndex);
bool Insert(size iIndex, CUnknown* pcUnknown);
CUnknown* Get(size iIndex);
void Set(size iIndex, CUnknown* pcUnknown);
void Remove(size iIndex);
size Remove(CUnknown* pcUnknown) override;
};
template<class M>
M* CArrayUnknown::Add(void)
{
M* pv;
pv = gcUnknowns.Add<M>();
CArrayCommonUnknown::Add(pv);
return pv;
}
template<class M>
M* CArrayUnknown::Insert(size iIndex)
{
M* pv;
pv = gcUnknowns.Add<M>();
CArrayCommonUnknown::Insert(iIndex, pv);
return pv;
}
class CMapCommonUnknown : public CUnknown, public CDataIO, public CDataFree
{
public:const char* ClassName(void){ return "CMapCommonUnknown";}size ClassSize(void){ return sizeof(CMapCommonUnknown);}
protected:
uint16 miFlags;
public:
void _Init(void);
void Init(bool bKillElements = true, bool bOverwriteExisting = true);
void Kill(void);
virtual bool Save(CFileWriter* pcFile) =0;
virtual bool Load(CFileReader* pcFile) =0;
virtual size NumElements(void) =0;
virtual size GetSortedSize(void) =0;
virtual size GetHoldingSize(void) =0;
bool IsKillElements(void);
bool IsOverwriteExisting(void);
bool IsEmpty(void);
bool IsNotEmpty(void);
};
class CMapStringUnknown : public CMapCommonUnknown
{
public:const char* ClassName(void){ return "CMapStringUnknown";}size ClassSize(void){ return sizeof(CMapStringUnknown);}
private:
CMapStringTemplate<CUnknown*> mcMap;
public:
void Init(bool bKillElements = true, bool bOverwriteExisting = true);
void Kill(void);
bool Save(CFileWriter* pcFile);
bool Load(CFileReader* pcFile);
template<class M>
M* Put(const char* szKey);
bool Put(const char* szKey, CUnknown* pcValue);
CUnknown* Get(const char* szKey);
size NumElements(void);
size GetSortedSize(void);
size GetHoldingSize(void);
bool StartIteration(SMapIterator* psIterator, char** ppvKey, CUnknown** ppvData);
bool Iterate(SMapIterator* psIterator, char** ppvKey, CUnknown** ppvData);
void Pack(void);
protected:
void FreeData(void* pvData) override;
bool WriteData(CFileWriter* pcFile, void* pvData) override;
bool ReadData(CFileReader* pcFile, void* pvData) override;
};
template<class M>
M* CMapStringUnknown::Put(const char* szKey)
{
M* pv;
bool bResult;
if (!StrEmpty(szKey))
{
pv = gcUnknowns.Add<M>();
bResult = Put(szKey, pv);
if (bResult)
{
return pv;
}
else
{
gcUnknowns.RemoveInKill(pv);
return 0L;
}
}
else
{
return 0L;
}
}
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
class CObjectSource;
class CObjectsSource : public CUnknown
{
public:const char* ClassName(void){ return "CObjectsSource";}size ClassSize(void){ return sizeof(CObjectsSource);}
protected:
CFiles mcFiles;
CArrayUnknown macSources;
CMapStringUnknown mmszpcConverters;
public:
void Init(void);
void Kill(void);
template<class TConverter> TConverter* AddConverter(void);
template<class TConverter> CObjectSource* AddSource(CAbstractFile* pcFile, const char* szFilename);
CObjectSource* GetSource(const char* szObjectName);
};
template<class TConverter>
CObjectSource* CObjectsSource::AddSource(CAbstractFile* pcFile, const char* szFilename)
{
TConverter* pcConveter;
CObjectSource* pcSource;
pcConveter = AddConverter<TConverter>();
pcSource = pcConveter->CreateSource(pcFile, szFilename);
if (pcSource)
{
macSources.Add(pcSource);
return pcSource;
}
else
{
return 0L;
}
}
template<class TConverter>
TConverter* CObjectsSource::AddConverter(void)
{
TConverter* pcConveter;
TConverter t;
const char* szClassName;
CUnknown* pcExistingConverter;
szClassName = t.ClassName();
pcExistingConverter = mmszpcConverters.Get((char*)szClassName);
if (!pcExistingConverter)
{
pcConveter = gcUnknowns.Add<TConverter>();
pcConveter->Init();
mmszpcConverters.Put((char*)szClassName, pcConveter);
return pcConveter;
}
else
{
return (TConverter*)pcExistingConverter;
}
}
class CSetUnknown : public CArrayCommonUnknown
{
public:const char* ClassName(void){ return "CSetUnknown";}size ClassSize(void){ return sizeof(CSetUnknown);}
public:
void Init(bool bSortPointers);
void Init(size iChunkSize, bool bSortPointers);
void Init(bool bKillElements, bool bUnique, bool bIgnoreNull, bool bPreserveOrder, size iChunkSize, bool bSortPointers);
void Kill(void) override;
template<class M>
M* Add(void);
void Add(CUnknown* pcUnknown);
size Remove(CUnknown* pcUnknown) override;
void RemoveDuringIteration(SSetIterator* psIter);
bool StartIteration(SSetIterator* psIter, CUnknown** ppcUnknown);
bool Iterate(SSetIterator* psIter, CUnknown** ppcUnknown);
};
template<class M>
M* CSetUnknown::Add(void)
{
M* pv;
pv = gcUnknowns.Add<M>();
Add(pv);
return pv;
}
class CObjects;
class CCollection : public CBaseObject
{
public:const char* ClassName(void){ return "CCollection";}size ClassSize(void){ return sizeof(CCollection);}
protected:
bool mbSubRoot;
public:
void Init(void);
void Kill(void) final;
bool IsCollection(void) override;
bool IsObject(void) override;
CBaseObject* Dehollow(void);
virtual void TouchAll(void) =0;
virtual void KillAll(void) =0;
bool RemoveAll(void);
virtual size NumElements(void) =0;
size Length(void);
size Size(void);
virtual size NonNullElements(void) =0;
virtual bool IsEmpty(void) =0;
bool Clear(void);
void MakeSubRoot(void);
bool IsSubRoot(void);
void BaseValidatePointerTos(void) override;
void ValidateConsistency(void);
protected:
void Class(void) override;
void PreFields(void) override;
void EmbedFields(void);
bool RemovePointerToTryFree(CBaseObject* pcPointedTo);
bool RemovePointerToDontFree(CBaseObject* pcPointedTo);
bool AddObjectFrom(CEmbeddedObject* pcObject, bool bResult, bool bValidate);
bool RemoveObjectTryFree(CEmbeddedObject* pcObject, bool bResult, bool bValidate);
bool RemoveObjectCopiesTryFree(CEmbeddedObject* pcObject, size uiRemoved, bool bValidate);
virtual void SetPointedTosDistToRoot(int iDistToRoot) =0;
void SetPointerTosExpectedDistToRoot(int iDistToRoot);
};
class CArrayCommonObject : public CCollection
{
public:const char* ClassName(void){ return "CArrayCommonObject";}size ClassSize(void){ return sizeof(CArrayCommonObject);}
protected:
CArrayCommonUnknown mcArray;
bool mbSorted;
public:
~CArrayCommonObject();
void Init(bool bUnique, bool bIgnoreNull, bool bPreserveOrder, bool bSortPointers);
void Class(void) override;
bool Add(CPointer& pObject);
bool Add(CEmbeddedObject* pcObject);
bool AddAll(CArrayCommonObject* pcArray);
bool Set(size iIndex, CPointer& pObject);
CEmbeddedObject* Dereference(CEmbeddedObject** ppcObject);
bool Remove(CPointer& pObject);
bool Remove(CEmbeddedObject* pcObject);
bool RemoveAll(CArrayCommonObject* pcArray);
bool RemoveAll(void);
bool RemoveEnd(size iIndexInclusive);
bool Contains(CPointer& pObject);
size NumElements(void) override;
size NonNullElements(void) override;
bool IsEmpty(void) override;
size NumPointerTos(void) override;
size BaseNumPointerTos(void) override;
void GetPointerTos(CArrayEmbeddedObjectPtr* papcTos) override;
void BaseGetPointerTos(CArrayEmbeddedObjectPtr* papcTos) override;
bool ContainsPointerTo(CEmbeddedObject* pcEmbedded) override;
void RemoveAllPointerTosDontFree(void) override;
bool RemoveAllPointerTosTryFree(void) override;
void CollectAndClearPointerTosInvalidDistToRootObjects(CDistCalculatorParameters* pcParameters) override;
void GrowTo(size iNumElements);
bool Save(CObjectWriter* pcFile) override;
bool Load(CObjectReader* pcFile) override;
void Sort(void);
CBaseObject* UnsafeGetObject(size iIndex);
bool UnsafeRemove(CBaseObject* pcObject);
CEmbeddedObject* GetEmbeddedObject(size iIndex) override;
void ValidatePointerTos(void) override;
CPointer StartIterationPointer(SSetIterator* psIter, bool* pbExists);
CPointer IteratePointer(SSetIterator* psIter, bool* pbExists);
void TouchAll(void) override;
void KillAll(void) override;
void EnsureSorted(void);
bool IsSorted(void);
bool CalculateIsSorted(void);
bool IsMustSort(void);
protected:
void PreFields(void) override;
void FreePointers(void) override;
void Free(void) override;
void RemovePointerTo(CEmbeddedObject* pcTo) override;
size RemapPointerTos(CEmbeddedObject* pcOld, CEmbeddedObject* pcNew) override;
void SetPointedTosDistToRoot(int iDistToRoot) override;
void UpdateAttachedEmbeddedObjectPointerTosDistToRoot(CDistCalculatorParameters* pcParameters, int iExpectedDist) override;
bool InsertAt(size iIndex, CPointer& pObject);
bool InsertAt(size iIndex, CEmbeddedObject* pcObject);
bool RemoveAt(size iIndex);
};
class CSetObject : public CArrayCommonObject
{
public:const char* ClassName(void){ return "CSetObject";}size ClassSize(void){ return sizeof(CSetObject);}
public:~CSetObject(void){ Kill();}
public:
void Init(bool bSortPointers = true);
CPointer UnsafeGet(size iIndex);
CBaseObject* UnsafeGetObject(size iIndex);
void RemoveDuringIteration(SSetIterator* psIter);
CPointer StartIteration(SSetIterator* psIter);
CPointer Iterate(SSetIterator* psIter);
template<class M> Ptr<M> StartIteration(SSetIterator* psIter);
template<class M> Ptr<M> Iterate(SSetIterator* psIter);
void TouchAll(void);
void Dump(void);
};
template<class M>
Ptr<M> CSetObject::StartIteration(SSetIterator* psIter)
{
bool bExists;
return (M*)StartIterationPointer(psIter, &bExists);
}
template<class M>
Ptr<M> CSetObject::Iterate(SSetIterator* psIter)
{
bool bExists;
return (M*)IteratePointer(psIter, &bExists);
}
class CObjects;
class CRoot : public CObject
{
friend class CObjects;
friend class CUnknowns;
public:const char* ClassName(void){ return "CRoot";}size ClassSize(void){ return sizeof(CRoot);}
public:~CRoot(void){ Kill();}
protected:
Ptr<CSetObject> mpObjects;
CObjects* mpcObjectsAllocatingFrom;
public:
CRoot();
void Init(void);
void Class(void) override;
void Free(void) override;
void Add(CPointer& pObject);
bool Remove(CPointer& pObject);
bool Remove(CBaseObject* pcObject);
bool RemoveAll(void);
bool IsRoot(void);
bool IsSubRoot(void);
bool Load(CObjectReader* pcFile) override;
CPointer UnsafeGet(int iIndex);
template<class M> Ptr<M> UnsafeGet(int iIndex);
CPointer Get(const char* szObjectName);
template<class M> Ptr<M> Get(const char* szObjectName);
Ptr<CSetObject> GetAll(void);
template<class M> Ptr<M> GetFirst(void);
size NumObjects(void);
void CreateSet(void);
void NullifySet(void);
CSetObject* TestGetSet(void);
bool IsSetHollow(void);
void Add(CPointer& pO1, CPointer& pO2);
void Add(CPointer& pO1, CPointer& pO2, CPointer& pO3);
void TouchAll(void);
void KillAll(void);
protected:
void KillInternal(bool bHeapFromChanged, bool bValidateNotEmbedded) override;
};
template<class M>
Ptr<M> CRoot::UnsafeGet(int iIndex)
{
Ptr<M> pM = UnsafeGet(iIndex);
return pM;
}
template<class M>
Ptr<M> CRoot::Get(const char* szObjectName)
{
Ptr<M> pM = Get(szObjectName);
return pM;
}
template<class M>
Ptr<M> CRoot::GetFirst(void)
{
return UnsafeGet<M>(0);
}
class CSequenceConfig : public CConstructable, public CKillable
{
public:const char* ClassName(void){ return "CSequenceConfig";}size ClassSize(void){ return sizeof(CSequenceConfig);}
public:
void Kill(void);
virtual const char* Getdirectory(void) =0;
virtual EDurableSync GetSync(void) =0;
virtual size GetBlockSize(void) =0;
};
class CSequenceConnection
{
public:
virtual OIndex GetNext(void) =0;
virtual OIndex PeekNext(void) =0;
};
class CSequence : public CSequenceConnection
{
protected:
CDurableFileController mcFileController;
OIndex moiNext;
OIndex moiReserved;
CDurableFile mcFile;
CSequenceConfig* mpcConfig;
CLife<CSequenceConfig> mcConfig;
public:
bool Init(CLifeInit<CSequenceConfig> cConfig);
void Kill(void);
OIndex GetNext(void);
OIndex PeekNext(void);
protected:
OIndex ReadIndex(void);
bool WriteIndex(OIndex oi);
bool Reserve(OIndex oiReserved);
};
class CIndexGenerator
{
protected:
CSequence mcSequence;
public:
void Init(CLifeInit<CSequenceConfig> cConfig);
void Kill(void);
OIndex PopIndex(void);
OIndex PeekIndex(void);
};
template<class M, class D>
class CMapTemplateTemplate : public CMapBlock
{
public:
D* Get(M* psKey);
D* Put(M* psKey);
bool Put(M* psKey, D* psData);
bool HasKey(M* psKey);
bool Remove(M* psKey);
bool PutInSorted(size iIndex, M** ppsKey, D** ppsData);
};
template<class M, class D>
D* CMapTemplateTemplate<M, D>::Get(M* psKey)
{
void* pvData;
pvData = CMapBlock::Get(psKey, sizeof(M));
return (D*)pvData;
}
template<class M, class D>
D* CMapTemplateTemplate<M, D>::Put(M* psKey)
{
return (D*)CMapBlock::Put(psKey, sizeof(M), sizeof(D));
}
template<class M, class D>
bool CMapTemplateTemplate<M, D>::Put(M* psKey, D* psData)
{
return CMapBlock::Put(psKey, sizeof(M), psData, sizeof(D));
}
template<class M, class D>
bool CMapTemplateTemplate<M, D>::HasKey(M* psKey)
{
return CMapBlock::HasKey(psKey, sizeof(M));
}
template<class M, class D>
bool CMapTemplateTemplate<M, D>::Remove(M* psKey)
{
return CMapBlock::Remove(psKey, sizeof(M));
}
template<class M, class D>
bool CMapTemplateTemplate<M, D>::PutInSorted(size iIndex, M** ppsKey, D** ppsData)
{
return CMapBlock::PutInSorted(iIndex, (void**)ppsKey, sizeof(M), (void**)ppsData, sizeof(D));
}
template<class M, class D>
class CMapPrimitiveTemplate : public CMapTemplateTemplate<M , D>
{
public:
D* Get(M iKey);
D* Put(M iKey);
bool Put(M iKey, D* psData);
bool HasKey(M iKey);
bool Remove(M iKey);
};
template<class M, class D>
D* CMapPrimitiveTemplate<M, D>::Get(M iKey)
{
return CMapTemplateTemplate<M, D>::Get(&iKey);
}
template<class M, class D>
D* CMapPrimitiveTemplate<M, D>::Put(M iKey)
{
return CMapTemplateTemplate<M, D>::Put(&iKey);
}
template<class M, class D>
bool CMapPrimitiveTemplate<M, D>::Put(M iKey, D* psData)
{
return CMapTemplateTemplate<M, D>::Put(&iKey, psData);
}
template<class M, class D>
bool CMapPrimitiveTemplate<M, D>::HasKey(M iKey)
{
return CMapTemplateTemplate<M, D>::HasKey(&iKey);
}
template<class M, class D>
bool CMapPrimitiveTemplate<M, D>::Remove(M iKey)
{
return CMapTemplateTemplate<M, D>::Remove(&iKey);
}
template<class D>
class CMapIntTemplate : public CMapPrimitiveTemplate<int, D>
{
public:
void Init(bool bOverwrite = true);
void Init(CMallocator* pcMalloc, bool bOverwrite = true);
bool Read(CFileReader* pcFileReader);
};
template<class D>
void CMapIntTemplate<D>::Init(bool bOverwrite)
{
Init(&gcSystemAllocator, bOverwrite);
}
template<class D>
void CMapIntTemplate<D>::Init(CMallocator* pcMalloc, bool bOverwrite)
{
CMapTemplateTemplate<int, D>::Init(pcMalloc, &CompareInt, bOverwrite);
};
template<class D>
bool CMapIntTemplate<D>::Read(CFileReader* pcFileReader)
{
return CMapTemplateTemplate<int32, D>::Read(pcFileReader, &CompareLong);
}
class CClasses;
class CUnmanagedClasses
{
private:
CClasses* mpcClasses;
size uiNumUnmanagedClasses;
protected:
CClass* mpcUndefined;
CClass* mpcVoidPointer;
CClass* mpcInt8;
CClass* mpcInt16;
CClass* mpcInt32;
CClass* mpcInt64;
CClass* mpcUInt8;
CClass* mpcUInt16;
CClass* mpcUInt32;
CClass* mpcUInt64;
CClass* mpcFloat32;
CClass* mpcFloat64;
CClass* mpcM2float32;
CClass* mpcM3float32;
CClass* mpcM4float32;
CClass* mpcM2float64;
CClass* mpcM3float64;
CClass* mpcM4float64;
CClass* mpcM2int32;
CClass* mpcM3int32;
CClass* mpcM4int32;
CClass* mpcM4x4float32;
CClass* mpcBool;
CClass* mpcVoid;
CClass* mpcChar8;
CClass* mpcChar16;
CClass* mpcString;
CClass* mpcStringImmutable;
CClass* mpcNumber;
CClass* mpcDate;
CClass* mpcDateTime;
CClass* mpcEnum;
CClass* mpcBit;
CClass* mpcCrumb;
CClass* mpcTribble;
CClass* mpcNybble;
CClass* mpcNickle;
CClass* mpcSixbits;
public:
void Init(CClasses* pcClasses);
void Kill(void);
CClass* GetUndefined(void);
CClass* GetVoidPointer(void);
CClass* GetByte(void);
CClass* GetShort(void);
CClass* GetInt(void);
CClass* GetLong(void);
CClass* GetUByte(void);
CClass* GetUShort(void);
CClass* GetUInt(void);
CClass* GetULong(void);
CClass* GetFloat(void);
CClass* GetDouble(void);
CClass* GetFloat2(void);
CClass* GetFloat3(void);
CClass* GetFloat4(void);
CClass* GetDouble2(void);
CClass* GetDouble3(void);
CClass* GetDouble4(void);
CClass* GetInt2(void);
CClass* GetInt3(void);
CClass* GetInt4(void);
CClass* GetFloat4x4(void);
CClass* GetBool(void);
CClass* GetVoid(void);
CClass* GetChar(void);
CClass* GetWidechar(void);
CClass* GetString(void);
CClass* GetStringImmutable(void);
CClass* GetNumber(void);
CClass* GetDate(void);
CClass* GetDateTime(void);
CClass* GetBit(void);
CClass* GetCrumb(void);
CClass* GetTribble(void);
CClass* GetNybble(void);
CClass* GetNickle(void);
CClass* GetSixbits(void);
CClass* GetEnum(void);
protected:
CClass* AddClassByPrettyName(EPrimitiveType eType);
CClass* AddClassByCPPName(EPrimitiveType eType);
CClass* AddClass(EPrimitiveType eType, const char* szName, size iSize);
};
class CGlobalMemoryAllocator : public CMallocator
{
public:const char* ClassName(void){ return "CGlobalMemoryAllocator";}size ClassSize(void){ return sizeof(CGlobalMemoryAllocator);}
public:
void Kill(void);
void* Malloc(lsize uiSize);
void* Realloc(void* pv, lsize uiSize);
bool Free(void* pv);
bool IsLocal(void);
size SizeOffset(void);
const char* ShortName(void);
};
extern CGeneralMemory gcMemory;
extern CGlobalMemoryAllocator gcMemoryAllocator;
class CMapStringString : public CMapStringBlock
{
public:
char* Get(const char* szKey);
char* Get(uint8* szKey);
bool Put(const char* szKey, const char* szValue);
bool Put(uint8* szKey, const char* szValue);
void Dump(void);
};
class CMallocators
{
protected:
CMapStringTemplate<CMallocator*> mmszClasses;
CMapStringString mmShortNames;
public:
void Init(void);
void Kill(void);
bool Add(CMallocator* pcMalloc);
CMallocator* Read(CFileReader* pcFileReader);
bool Write(CFileWriter* pcFileWriter, CMallocator* pcMalloc);
};
extern CMallocators gcMallocators;
extern CConstructors gcConstructors;
extern bool gbMemory;
void MemoryInit(void);
void MemoryInit(uint16 iDefaultAlignment, bool bDefaultFreeListParams = true);
void MemoryKill(void);
bool MemoryValidate(void);
class CClasses;
class CPrimitiveClasses
{
private:
CClasses* mpcClasses;
protected:
CClass* mpcInt8;
CClass* mpcInt16;
CClass* mpcInt32;
CClass* mpcInt64;
CClass* mpcUInt8;
CClass* mpcUInt16;
CClass* mpcUInt32;
CClass* mpcUInt64;
CClass* mpcFloat32;
CClass* mpcFloat64;
CClass* mpcBool;
CClass* mpcVoid;
CClass* mpcChar8;
CClass* mpcChar16;
public:
void Init(CClasses* pcClasses);
void Kill(void);
CClass* GetByte(void);
CClass* GetShort(void);
CClass* GetInt(void);
CClass* GetLong(void);
CClass* GetUByte(void);
CClass* GetUShort(void);
CClass* GetUInt(void);
CClass* GetULong(void);
CClass* GetFloat(void);
CClass* GetDouble(void);
CClass* GetBool(void);
CClass* GetVoid(void);
CClass* GetChar(void);
CClass* GetWidechar(void);
protected:
template<class Class>
CClass* AddClass(EPrimitiveType eFieldType);
template<class Class>
CClass* AddClassWithConstructorAndIO(EPrimitiveType eFieldType);
CClass* AddClass(const char* szClassName, size uiClassSize, EPrimitiveType eFieldType, size eFieldOffest);
CClass* AddVoid(void);
};
template<class Class>
CClass* CPrimitiveClasses::AddClass(EPrimitiveType eFieldType)
{
Class cInstance;
size uiOffset;
CClass* pcClass;
uiOffset = (char*)(&cInstance.mVal) - (char*)(&cInstance);
pcClass = AddClass(cInstance.ClassName(), cInstance.ClassSize(), eFieldType, uiOffset);
return pcClass;
}
extern CDatasIO gcDataTypesIO;
extern bool gbDataTypesIO;
void DataIOInit(void);
void DataIOKill(void);
bool DataIOValidate(void);
typedef CMapStringTemplate<CClass*> CMapClassesByName;
typedef CMapIntTemplate<CClass*> CMapClassesByType;
class CObjects;
class CClasses
{
protected:
CMapClassesByName mmcpClassesByName;
CMapClassesByType mmcpClassesByType;
CFreeList maClasses;
CUnmanagedClasses mcUnmanaged;
CPrimitiveClasses mcPrimitive;
uint32 muiCurrentClassType;
CClass* mpcPointer;
public:
void Init(CObjects* pcObjects);
void Kill(void);
void AddSystemClasses(void);
CClass* Get(const char* szClassName);
CClass* Get(EPrimitiveType eType);
CClass* Get(uint32 iType);
CClass* GetValid(EPrimitiveType eType);
CClass* Add(const char* szClassName, size uiSize, EPrimitiveType eType);
CClass* Add(const char* szClassName, size uiSize);
CClass* GetPointer(void);
CUnmanagedClasses* GetUnmanagedClasses(void);
CPrimitiveClasses* GetPrimitiveClasses(void);
void ValidateType(EPrimitiveType eType);
template<class Class>
void AddConstructorAndIO(void);
template<class Class>
void AddSystemClassAndConstructor(void);
template<class Class>
void AddConstructor(void);
protected:
uint32 GetNextClassType(void);
};
template<class Class>
void CClasses::AddConstructorAndIO(void)
{
const char* szClassName;
SDataIO* psIO;
bool bConstructor;
CStackMemory<> cStack;
Class* pcClass;
pcClass = StackConstruct<Class>(&cStack);
szClassName = pcClass->ClassName();
cStack.Kill();
psIO = gcDataTypesIO.GetIO(szClassName);
if (!psIO)
{
gcDataTypesIO.Add<Class>();
}
bConstructor = gcConstructors.Contains(szClassName);
if (!bConstructor)
{
gcConstructors.Add<Class>();
}
}
template<class Class>
void CClasses::AddSystemClassAndConstructor(void)
{
bool bConstructor;
Class* pvM;
CClass* pcClass;
CStackMemory<> cStack;
const char* szClassName;
pvM = StackConstruct<Class>(&cStack);
szClassName = pvM->ClassName();
pcClass = pvM->CBaseObject::CompleteClass(this);
pcClass->System();
bConstructor = gcConstructors.Contains(szClassName);
if (!bConstructor)
{
gcConstructors.Add<Class>();
}
cStack.Kill();
}
template<class Class>
void CClasses::AddConstructor(void)
{
bool bConstructor;
Class* pvM;
CStackMemory<> cStack;
const char* szClassName;
pvM = StackConstruct<Class>(&cStack);
szClassName = pvM->ClassName();
bConstructor = gcConstructors.Contains(szClassName);
if (!bConstructor)
{
gcConstructors.Add<Class>();
}
cStack.Kill();
}
class CFreeObjects : public CObject
{
protected:
Ptr<CSetObject> mpFreeObjects;
public:
void Init(void);
void Free(void) override;
void Class(void) override;
bool Save(CObjectWriter* pcFile) override;
bool Load(CObjectReader* pcFile) override;
template<class M> M* Add(Ptr<M>& p);
CBaseObject* Add(CPointer &p);
bool Remove(CBaseObject* pcObject);
size NumObjects(void);
CBaseObject* UnsafeGetObject(size iIndex);
};
template<class M>
M* CFreeObjects::Add(Ptr<M>& p)
{
return (M*)Add((CPointer&)p);
}
class CDistCalculator
{
private:
CDistToRootCalculator mcDistToRootCalculator;
CDistToStackCalculator mcDistToStackCalculator;
CDistCalculatorParameters mcParameters;
public:
void Init(void);
void Kill(void);
CArrayBaseObjectPtr* Calculate(CBaseObject* pcFromChanged, bool bHeapFromChanged);
CArrayBaseObjectPtr* CalculateHeapFromChanged(CBaseObject* pcFromChanged);
CArrayBaseObjectPtr* CalculateStackFromChanged(CBaseObject* pcFromChanged);
void Print(CChars* psz);
void Dump(void);
};
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
Ptr<CRoot> ORoot(void);
template <class SpecificClass, typename ... Args>
Ptr<SpecificClass> OMalloc(Args ... args);
template <class SpecificClass, typename ... Args>
Ptr<SpecificClass> ONMalloc(const char* szObjectName, Args ... args);
typedef void (*AllocationCallback)(CBaseObject*);
typedef void (*HollocationCallback)(CBaseObject*);
typedef void (*DestructionCallback)(CBaseObject*);
class CHollowObject;
class CFreeObjects;
class CObjects
{
friend class CBaseObject;
friend class CInternalObjectDeserialiser;
protected:
bool mbInitialised;
CUnknowns* mpcUnknownsAllocatingFrom;
CNamedIndexedObjects mcMemory;
CObjectsSource mcSource;
CClasses mcClasses;
CDataConnection* mpcDataConnection;
CSequenceConnection* mpcSequenceConnection;
CDistCalculator mcDistCalculator;
AllocationCallback mAllocationCallback;
HollocationCallback mHollocationCallback;
DestructionCallback mDestructionCallback;
bool mbValidateConsistency;
CObjectRemovalContext mcRemovalContext;
public:
CObjects();
void Init(CUnknowns* pcUnknownsAllocatingFrom, CDataConnection* pcDataConnection, CSequenceConnection* pcSequenceConnection);
void Kill(void);
template<class M> void AddConstructor(void);
template<class M> CObjectSource* AddSource(CAbstractFile* pcFile, const char* szFilename);
bool Flush(void);
bool ForceSave(CBaseObject* pcObject);
CPointer Get(OIndex oi);
CPointer Get(const char* szObjectName);
template<class M> Ptr<M> Get(OIndex oi);
template<class M> Ptr<M> Get(const char* szObjectName);
bool Contains(const char* szObjectName);
bool Contains(OIndex oi);
template<class M> Ptr<M> Malloc(void);
template<class M> Ptr<M> Malloc(const char* szObjectName);
Ptr<CRoot> Root(void);
void LogicalDirty(CBaseObject* pcObject);
bool Remove(CArrayBaseObjectPtr* papcKilled);
bool Remove(CArrayBaseObjectPtr* papcKilled, CArrayBaseObjectPtr* papcKilledAfter);
CPointer Null(void);
template<class M> Ptr<M> Null(void);
size NumMemoryIndexes(void);
size NumMemoryNames(void);
int64 NumDatabaseIndexes(void);
int64 NumDatabaseNames(void);
CSequenceConnection* GetIndexGenerator(void);
CNamedIndexedObjects* GetMemory(void);
bool EvictInMemory(void);
CBaseObject* Dehollow(OIndex oi);
CBaseObject* Dehollow(char* szObjectName);
bool ReplaceBaseObject(CBaseObject* pvExisting, CBaseObject* pvObject);
bool TestRemoveMemoryIdentifiers(CBaseObject* pvObject);
CStackPointers* GetStackPointers(void);
CClasses* GetClasses(void);
CConstructors* GetConstructors(void);
OIndex StartMemoryIteration(SIndexesIterator* psIter);
OIndex IterateMemory(SIndexesIterator* psIter);
CPointer TestGetFromMemory(OIndex oi);
CPointer TestGetFromMemory(const char* szName);
Ptr<CFreeObjects> FreeObjects(void);
template<class M> M* AddFreeObject(Ptr<M>& p);
CBaseObject* AddFreeObject(CPointer &p);
bool RemoveFreeObject(CBaseObject* pcObject);
size NumFreeObjects(void);
void PrintMemoryNames(CChars* psz);
void PrintStackPointers(CChars* psz, bool bPointerMemory = true);
void PrintGraph(CChars* psz, bool bPointerMemory = true);
void DumpMemoryUseIteration(void);
void DumpMemoryUseRecursion(void);
void DumpNames(void);
void DumpGraph(void);
void DumpMemoryNames(void);
void DumpStackPointers(void);
void ValidateEmpty(void);
void ValidateObjectsConsistency(void);
void SetAllocationCallback(AllocationCallback fAllocationCallback);
void SetHollocationCallback(HollocationCallback fHollocationCallback);
void SetDestructionCallback(DestructionCallback fDestructionCallback);
void EnableValidation(void);
void DisableValidation(void);
protected:
Ptr<CRoot> GetRoot(void);
bool HasRoot(void);
bool AddIntoMemory(CBaseObject* pvObject);
bool AddIntoMemoryWithIndex(CBaseObject* pvObject);
bool AddIntoMemoryWithNameAndIndex(CBaseObject* pvObject);
template<class M> Ptr<M> PointTo(M* pcObject);
template<class M> Ptr<M> PointToSetDirty(M* pcObject);
template<class M> M* AllocateUninitialisedByTemplate(void);
template<class M> M* AllocateUninitialisedByTemplate(const char* szObjectName);
template<class M> M* AllocateUninitialisedByTemplate(OIndex oi, size uiAdditionalBytes);
template<class M> M* AllocateUninitialisedByTemplate(const char* szObjectName, OIndex oi, size uiAdditionalBytes);
CBaseObject* AllocateUninitialisedByClassName(const char* szClassName, OIndex oi);
CBaseObject* AllocateUninitialisedByClassName(const char* szClassName, const char* szObjectName, OIndex oi);
bool ValidateCanAllocate(const char* szClassName);
bool ValidateCanAllocate(void);
CBaseObject* GetFromMemory(OIndex oi);
CBaseObject* GetFromMemory(const char* szObjectName);
CBaseObject* GetFromMemory(const char* szObjectName, OIndex oi);
CBaseObject* GetFromDatabase(OIndex oi);
CBaseObject* GetFromDatabase(const char* szObjectName);
CBaseObject* GetFromSources(const char* szObjectName);
OIndex GetNextIndex(void);
void FreeInternal(CArrayBaseObjectPtr* papcObjectPts);
void RemoveAllPointerTos(CArrayBaseObjectPtr* papcObjectPts);
void RemoveAllHeapFroms(CArrayBaseObjectPtr* papcObjectPts);
void DoneKill(CArrayBaseObjectPtr* papcObjectPts);
void KillObjects(CArrayBaseObjectPtr* papcObjectPts);
bool ValidateNoEmbedded(CArrayBaseObjectPtr* papcObjectPts);
void RecurseDumpGraph(CChars* psz, CEmbeddedObject* pcObject, int iLevel, bool bEmbedded, bool bPointerMemory);
void ValidateSceneGraph(void);
void ValidateIndexedObjects(void);
void ClearValidationFlags(void);
void ValidateObjectInternals(void);
void RecurseValidateSceneGraph(CBaseObject* pcBaseObject);
CHollowObject* AllocateHollow(size uiNumEmbedded, OIndex oi);
CHollowObject* AllocateHollow(size uiNumEmbedded, OIndex oi, uint16 uiFatSize);
CHollowObject* AllocateHollow(size uiNumEmbedded, const char* szObjectName, OIndex oi);
CHollowObject* AllocateHollow(size uiNumEmbedded, const char* szObjectName, OIndex oi, uint16 uiFatSize);
void AppenedHollowEmbeddedObjects(CBaseObject* pcHollow, size uiNumEmbedded, void* pvEmbedded) ;
void PrintMemoryUseIteration(CChars* psz);
void PrintMemoryUseRecursion(CChars* psz);
void UnsetDumpFlags(void);
public:
CBaseObject* AllocateUninitialisedByClassNameAndAddIntoMemory(const char* szClassName);
CBaseObject* AllocateNamedUninitialisedByClassNameAndAddIntoMemory(const char* szClassName, const char* szObjectName);
CBaseObject* AllocateForInternalDeserialisationWithIndex(char* szClassName, OIndex oi);
CHollowObject* AllocateInternalHollowWithIndex(OIndex oi, size uiNumEmbedded, uint16 uiObjectSize);
CHollowObject* AllocateInternalHollowWithNameAndIndex(const char* szObjectName, OIndex oi, size uiNumEmbedded, uint16 uiObjectSize);
CBaseObject* GetNamedObjectInMemoryAndReplaceOrAllocateUninitialisedWithSameName(const char* szClassName, const char* szObjectName);
CBaseObject* GetExternalNamedObjectInMemoryOrAllocateHollow(char* szObjectName, size uiNumEmbedded);
protected:
CBaseObject* AllocateForInternalDeserialisationWithNameAndIndex(char* szClassName, char* szObjectName, OIndex oiForced, OIndex* poiExisting);
CBaseObject* ConvertFatHollowToUninitialisedByClassName(CHollowObject* pcHollowObject, const char* szClassName);
void RemapFatHollowEmbeddedObjects(CBaseObject* pcObject, size uiNumEmbedded, void* pvHollowEmbedded);
};
extern CObjects gcObjects;
extern bool gbObjects;
void ObjectsInit(void);
void ObjectsInit(CDataConnection* pcDataConnection, CSequenceConnection* pcSequenceConnection);
void ObjectsInit(CUnknowns* pcUnknowns, CDataConnection* pcDataConnection, CSequenceConnection* pcSequenceConnection);
void ObjectsKill(bool bValidate = true);
bool ObjectsValidate(void);
bool ObjectsFlush(void);
void ObjectsDump(void);
void LogObjectAllocation(CBaseObject* pcObject, const char* szMethod);
void LogObjectDestruction(CBaseObject* pcObject, const char* szMethod);
template<class SpecificClass>
SpecificClass* CObjects::AllocateUninitialisedByTemplate(OIndex oi, size uiAdditionalBytes)
{
SpecificClass* pcObject;
bool bResult;
bResult = ValidateCanAllocate();
if (!bResult)
{
return 0L;
}
pcObject = mpcUnknownsAllocatingFrom->Add<SpecificClass>(uiAdditionalBytes);
if (pcObject)
{
pcObject->Allocate(this);
pcObject->InitIdentifiers("", oi);
}
return pcObject;
}
template<class SpecificClass>
SpecificClass* CObjects::AllocateUninitialisedByTemplate(const char* szObjectName, OIndex oi, size uiAdditionalBytes)
{
SpecificClass* pcObject;
bool bResult;
bResult = ValidateCanAllocate();
if (!bResult)
{
return 0L;
}
pcObject = mpcUnknownsAllocatingFrom->Add<SpecificClass>(uiAdditionalBytes);
if (pcObject)
{
pcObject->Allocate(this);
pcObject->InitIdentifiers(szObjectName, oi);
}
return pcObject;
}
template<class SpecificClass>
SpecificClass* CObjects::AllocateUninitialisedByTemplate(void)
{
OIndex oi;
oi = GetIndexGenerator()->GetNext();
return AllocateUninitialisedByTemplate<SpecificClass>(oi, 0);
}
template<class SpecificClass>
SpecificClass* CObjects::AllocateUninitialisedByTemplate(const char* szObjectName)
{
OIndex oi;
oi = GetNextIndex();
return AllocateUninitialisedByTemplate<SpecificClass>(szObjectName, oi, 0);
}
template<class SpecificClass>
Ptr<SpecificClass> CObjects::Null(void)
{
Ptr<SpecificClass> pObject;
return pObject;
}
template<class SpecificClass>
Ptr<SpecificClass> CObjects::PointTo(SpecificClass* pcObject)
{
Ptr<SpecificClass> pObject;
if (pcObject)
{
pObject.AssignObject(pcObject);
}
return pObject;
}
template<class SpecificClass>
Ptr<SpecificClass> CObjects::PointToSetDirty(SpecificClass* pcObject)
{
Ptr<SpecificClass> pObject;
if (pcObject)
{
pObject.AssignObject(pcObject);
pcObject->SetDirty(true);
}
return pObject;
}
template<class SpecificClass>
Ptr<SpecificClass> CObjects::Malloc(void)
{
bool bResult;
SpecificClass* pcObject = AllocateUninitialisedByTemplate<SpecificClass>();
if (pcObject)
{
bResult = AddIntoMemoryWithIndex(pcObject);
if (bResult)
{
return PointToSetDirty(pcObject);
}
else
{
pcObject->KillInternal(false, true);
return 0L;
}
}
else
{
return 0L;
}
}
template<class SpecificClass>
Ptr<SpecificClass> CObjects::Malloc(const char* szObjectName)
{
bool bResult;
SpecificClass* pcObject = AllocateUninitialisedByTemplate<SpecificClass>(szObjectName);
if (pcObject)
{
bResult = AddIntoMemoryWithNameAndIndex(pcObject);
if (bResult)
{
return PointToSetDirty(pcObject);
}
else
{
pcObject->KillInternal(false, true);
return 0L;
}
}
else
{
return 0L;
}
}
template<class SpecificClass>
Ptr<SpecificClass> CObjects::Get(OIndex oi)
{
SpecificClass* pcObject = (SpecificClass*)mcMemory.Get(oi);
return PointTo<SpecificClass>(pcObject);
}
template<class SpecificClass>
Ptr<SpecificClass> CObjects::Get(const char* szObjectName)
{
SpecificClass* pcObject = (SpecificClass*)mcMemory.Get(szObjectName);
return PointTo<SpecificClass>(pcObject);
}
template<class SpecificClass>
void CObjects::AddConstructor(void)
{
SpecificClass* pcClass;
if (mpcUnknownsAllocatingFrom == 0L)
{
gcLogger.Error2(MethodToString("/home/r2d2/Codaphela/commonlibraries/StandardLib/Objects.h", 470, __PRETTY_FUNCTION__), " UnknownsAllocatingFrom is NULL.  Probably Objects has not been initialsed.", 0L);
}
pcClass = mpcUnknownsAllocatingFrom->GetConstructor<SpecificClass>();
if (!pcClass)
{
mpcUnknownsAllocatingFrom->AddConstructor<SpecificClass>();
}
}
template<class SpecificClass>
CObjectSource* CObjects::AddSource(CAbstractFile* pcFile, const char* szFilename)
{
return mcSource.AddSource<SpecificClass>(pcFile, szFilename);
}
template<class M>
M* CObjects::AddFreeObject(Ptr<M>& p)
{
return FreeObjects()->Add(p);
}
template <class SpecificClass, typename ... Args>
Ptr<SpecificClass> OMalloc(Args ... args)
{
Ptr<SpecificClass> pObject = gcObjects.Malloc<SpecificClass>();
if (pObject.IsNotNull())
{
pObject->Init(args...);
}
return pObject;
}
template <class SpecificClass, typename ... Args>
Ptr<SpecificClass> ONMalloc(const char* szObjectName, Args ... args)
{
Ptr<SpecificClass> pObject = gcObjects.Malloc<SpecificClass>(szObjectName);
if (pObject.IsNotNull())
{
pObject->Init(args...);
}
return pObject;
}
template <class SpecificClass>
Ptr<SpecificClass> OMallocNoI()
{
return gcObjects.Malloc<SpecificClass>();
}
template <class SpecificClass>
Ptr<SpecificClass> ONMallocNoI(char* szObjectName)
{
return gcObjects.Malloc<SpecificClass>(szObjectName);
}
template <class SpecificClass, typename ... Args>
Ptr<SpecificClass> ONMallocNoI(const char* szObjectName, Args ... args)
{
return gcObjects.Malloc<SpecificClass>((char*)szObjectName);
}
class CBaseObject;
class CDependentReadObject : public CObjectIdentifier
{
protected:
int miFlags;
public:
void Init(CObjectIdentifier* pcObjectIdentifier);
void Kill(void);
char* GetName(void);
OIndex GetOldIndex(void);
void SetRead(void);
void SetExisting(void);
bool IsRead(void);
bool ExistsInObjects(void);
};
int CompareDependentReadObject(const void* ps1, const void* ps2);
typedef CArrayTemplate<CDependentReadObject> CArrayDependentReadObject;
class CBaseObject;
class CEmbeddedObject;
class CDependentReadPointer
{
public:
CEmbeddedObject** mppcPointedFrom;
CBaseObject* mpcContaining;
OIndex moiPointedTo;
uint16 miNumEmbedded;
uint16 miEmbeddedIndex;
void Init(CEmbeddedObject** ppcPointedFrom, CBaseObject* pcContaining, OIndex oiPointedTo, uint16 iNumEmbedded, uint16 iEmbeddedIndex);
};
typedef CArrayTemplate<CDependentReadPointer> CArrayDependentReadPointer;
class CDependentReadObjects
{
public:
void Init(void);
void Kill(void);
virtual bool AddDependent(CObjectIdentifier* pcHeader, CEmbeddedObject** ppcPtrToBeUpdated, CBaseObject* pcObjectContainingPtrToBeUpdated, uint16 iNumEmbedded, uint16 iEmbeddedIndex) =0;
virtual bool AddReverseDependent(CObjectIdentifier* pcHeader, CEmbeddedObject** ppcPtrToBeUpdated, CBaseObject* pcObjectContainingHeapFrom, uint16 iNumEmbedded, uint16 iEmbeddedIndex, int iDistToRoot) =0;
virtual CBaseObject* AllocateForDeserialisation(CObjectHeader* pcHeader) =0;
protected:
void AddHeapFrom(CEmbeddedObject* pcBaseObject, CBaseObject* pcContaining);
};
class CObjectHeader;
class CObjectIdentifier;
class CObjectReader : public CFileReader
{
protected:
CDependentReadObjects* mpcDependents;
CFileBasic mcFile;
public:
bool Init(CAbstractFile* pcFile, CDependentReadObjects* pcDependents);
void Kill(void);
CBaseObject* Read(void);
bool ReadHeapFroms(CBaseObject* pcThis);
bool ReadPointer(CPointer* pObject);
bool ReadIdentifier(CObjectIdentifier* pcPointerHeader);
bool ReadObjectHeader(CObjectHeader* pcObjectHeader);
bool ReadDependent(CEmbeddedObject** ppcObjectPtr, CBaseObject* pcContaining);
bool ReadReverseDependent(CEmbeddedObject** ppcObjectPtr, CBaseObject* pcContaining);
protected:
lsize Read(void* pvDest, lsize iSize, lsize iCount);
};
class CBaseObject;
class CDependentWriteObject
{
public:
CBaseObject* mpcObject;
bool mbWritten;
public:
void Init(CBaseObject* pcObject, bool bWritten);
};
int CompareDependentWriteObject(const void* ps1, const void* ps2);
typedef CArrayTemplate<CDependentWriteObject> CArrayDependentWriteObject;
class CDependentWriteObjects
{
protected:
CArrayDependentWriteObject mcObjects;
size miGetIndex;
public:
void Init(void);
void Kill(void);
void Add(CBaseObject* pcObject);
CBaseObject* GetUnwritten(void);
void Mark(CBaseObject* pcObject);
};
class CObjectWriter : public CFileWriter
{
protected:
CFileBasic mcFile;
CDependentWriteObjects* mpcDependentObjects;
public:
bool Init(CAbstractFile* pcFile, CDependentWriteObjects* pcDependentObjects);
void Kill(void);
bool Write(CBaseObject* pcThis);
bool WriteHeapFroms(CBaseObject* pcThis);
bool WritePointer(CPointer& pObject);
bool WritePointer(CPointer* pObject);
bool WriteDependent(CEmbeddedObject* pcBaseObject, bool bFatHollow);
protected:
bool WriteObjectHeader(CObjectHeader* pcHeader);
bool WriteIdentifier(CObjectIdentifier* pcObjectIdentifier);
void InitObjectHeader(CObjectHeader* pcHeader, CBaseObject* pcObject, bool bFatHollow);
void InitIdentifier(CObjectIdentifier* pcObjectIdentifier, CBaseObject* pcObject, bool bFatHollow);
lsize Write(const void* pvSource, lsize iSize, lsize iCount);
};
class CChannelDebugDescriptor
{
public:
const char* mszLongName;
const char* mszShortName;
void Init(const char* szLongName, const char* szShortName);
void Kill(void);
};
typedef CMapIntTemplate<CChannelDebugDescriptor> CMapIntChannelDescriptor;
struct SChannel
{
size iChannel;
EPrimitiveType eType;
bool bReverse;
void Init(size iChannel, EPrimitiveType eType, bool bReverse);
};
typedef CArrayTemplate<SChannel> CArrayChannel;
struct SChannelsChangingDesc
{
CArrayChannel asAddedChannels;
CArrayChannel asRemovedChannels;
size iSize;
void* pvUserData;
void Init();
void Kill();
};
class CChannel : public SChannel
{
public:
size miByteSize;
size miBitSize;
size miByteOffset;
size miBitOffset;
void Init(size iChannel, EPrimitiveType eType, bool bReverse);
void Init(size iChannel, EPrimitiveType eType, size iByteSize, size iBitSize, size iByteOffset, size iBitOffset, bool bReverse = false);
bool Is8BitAligned(void);
};
typedef CArrayTemplate<CChannel> CArrayChannelOffset;
class CChannels : public CObject
{
public:const char* ClassName(void){ return "CChannels";}size ClassSize(void){ return sizeof(CChannels);}
public:~CChannels(void){ Kill();}
protected:
CArrayChannelOffset masChannelOffsets;
size miSize;
size miByteStride;
size miBitStride;
bool mbOnlyBasicTypes;
CArrayChar mabData;
char* mpvUserData;
SChannelsChangingDesc* mpsChangingDesc;
char* mpvDataCache;
CMapIntChannelDescriptor* mpmicChannelDebugs;
public:
void Init(void);
void Init(size iSize, EPrimitiveType eType, size iFirst, ...);
void Init(size iSize, void* pvUserData, EPrimitiveType eType, size iFirst, ...);
void Init(CChannels* pcSource);
void Class(void) override;
void Free(void) override;
void ReInit(void);
bool Save(CObjectWriter* pcFile) override;
bool Load(CObjectReader* pcFile) override;
void BeginChange(void);
void SetSize(size iSize);
void PrivateAddChannel(size iChannel, EPrimitiveType eType, bool bReverse);
void AddChannel(SChannel* psChannel);
void AddChannel(size iChannel, EPrimitiveType eType, bool bReverse = false);
void AddChannel(size iChannel, EPrimitiveType eType, const char* szShortName, const char* szLongName = 0L, bool bReverse = false);
void AddChannel(size iChannel1, size iChannel2, EPrimitiveType eType, bool bReverse = false);
void AddChannel(size iChannel1, size iChannel2, size iChannel3, EPrimitiveType eType, bool bReverse = false);
void AddChannel(size iChannel1, size iChannel2, size iChannel3, size iChannel4, EPrimitiveType eType, bool bReverse = false);
void AddChannels(CArrayChannel* pasChannels);
void AddChannels(CChannels* pcSourceChannels);
bool RemoveChannel(size iChannel);
void SetData(void* pvMem);
void ByteAlign(void);
bool RenameChannel(size iOldName, size iNewName);
bool EndChange(void);
bool IsChanging(void);
bool IsSameFormat(CChannels* psOther);
bool IsChannelRemoved(size iChannel);
bool IsChannelAdded(size iChannel);
bool IsIgnored(void);
bool Is8BitAligned(size iBitStart, size iBitLength);
size CalculateByteStride(size iBitStride);
size CalculateByteSize(size iBitStride, size iSize);
void AllocateData(void);
void FreeData(void);
void Copy(CChannels* pcData);
void CopyIntoInitialised(CChannels* pcSource);
void Black(void);
void White(void);
void Dump(size iLineLength);
char* GetData(void);
bool IsUserAllocated(void);
CChannel* GetChannel(size iChannel);
size GetNumChannels(void);
CChannel* GetChannelAtIndex(size iIndex);
void GetNative(size iPos, CChannel* pcChannel, void* pvDest);
void SetNative(size iPos, CChannel* pcChannel, void* pvSource);
size GetIndexOfChannel(CChannel* pcChannel);
size GetIndexOfChannel(size iChannel);
bool HasChannel(size iChannel);
bool HasChannel(size iChannel1, size iChannel2);
bool HasChannel(size iChannel1, size iChannel2, size iChannel3);
bool HasChannels(size iFirst, ...);
size GetSize(void);
size GetByteSize(void);
CArrayChannelOffset* GetChannelOffsets(void);
size GetByteStride(void);
size GetBitStride(void);
const char* GetChannelLongName(size iChannel);
const char* GetChannelShortName(size iChannel);
size NumChannels(void);
void GetAllChannels(CArraySize* paiChannels);
void GetAllChannels(CArrayChannel* pasChannels);
EPrimitiveType GetPrimitiveType(void);
void GetAllPrimitiveTypes(CArrayInt* paiPrimitiveTypes);
void GetChannelsForType(EPrimitiveType eType, CArraySize* paiChannels);
bool IsOnlyBasicTypes(void);
void SetByteStride(size iByteStride);
void SetBitStrideFromByteStride(void);
bool IsValid(size iPos);
void SetChannelDebugNames(size iChannel, const char* szShortName, const char* szLongName);
EPrimitiveType GetLargestPrimitiveType(void);
protected:
void PrivateInit(void);
void Recalculate(void);
bool CanAddChannels(void);
void CopyChannelDebugs(CMapIntChannelDescriptor* mpmicSourceChannelDebugs);
};
class CArrayObject : public CArrayCommonObject
{
public:const char* ClassName(void){ return "CArrayObject";}size ClassSize(void){ return sizeof(CArrayObject);}
public:
void Init(void);
bool Add(CPointer& pObject);
bool AddAll(Ptr<CArrayObject> pcArray);
CPointer Get(size iIndex);
bool Insert(size iIndex, CPointer& pObject);
bool Remove(size iIndex);
bool Remove(CPointer& pObject);
template<class M>
Ptr<M> Get(size iIndex);
};
template<class M>
Ptr<M> CArrayObject::Get(size iIndex)
{
return (M*)Get(iIndex);
}
template<class M = CBaseObject>
class CArray final : public CArrayObject
{
public:const char* ClassName(void){ return "CArray";}size ClassSize(void){ return sizeof(CArray);}
public:
void Init(void);
void Add(Ptr<M> pObject);
void AddAll(Ptr<CArrayCommonObject> pcArray);
bool Insert(size iIndex, Ptr<M> pObject);
Ptr<M> Get(size iIndex);
bool Set(size iIndex, Ptr<M> pObject);
Ptr<M> StartIteration(SSetIterator* psIter, bool* pbExists);
Ptr<M> Iterate(SSetIterator* psIter, bool* pbExists);
bool RemoveAt(size iIndex);
bool Remove(Ptr<M> pObject);
};
template<class M>
void CArray<M>::Init(void)
{
CArrayObject::Init();
}
template<class M>
void CArray<M>::Add(Ptr<M> pObject)
{
CArrayObject::Add(pObject);
}
template<class M>
void CArray<M>::AddAll(Ptr<CArrayCommonObject> pcArray)
{
pcArray->ClassName();
CArrayObject::AddAll((CArrayCommonObject*)pcArray.Dereference());
}
template<class M>
bool CArray<M>::Insert(size iIndex, Ptr<M> pObject)
{
return CArrayObject::Insert(iIndex, pObject);
}
template<class M>
bool CArray<M>::Set(size iIndex, Ptr<M> pObject)
{
return CArrayObject::Set(iIndex, pObject);
}
template<class M>
Ptr<M> CArray<M>::StartIteration(SSetIterator* psIter, bool* pbExists)
{
return CArrayObject::StartIterationPointer(psIter, pbExists);
}
template<class M>
Ptr<M> CArray<M>::Iterate(SSetIterator* psIter, bool* pbExists)
{
return CArrayObject::IteratePointer(psIter, pbExists);
}
template<class M>
Ptr<M> CArray<M>::Get(size iIndex)
{
return CArrayObject::Get(iIndex);
}
template<class M>
bool CArray<M>::RemoveAt(size iIndex)
{
return CArrayObject::RemoveAt(iIndex);
}
template<class M>
bool CArray<M>::Remove(Ptr<M> pObject)
{
return CArrayObject::Remove(pObject);
}
class CMapIntString : public CMapIntTemplate<char*>
{
protected:
CDataMemory mcMemory;
public:
void Init(bool bOverwrite = true);
void Init(CMallocator* pcMalloc, bool bOverwrite = true);
void Kill(void);
char* Get(int iKey);
bool Put(int iKey, const char* szValue);
void Dump(void);
};
enum EChannelType
{
CT_Unknown,
CT_Red = 1,
CT_Green,
CT_Blue,
CT_Hue,
CT_Saturation,
CT_Value,
CT_Intensity,
CT_X,
CT_Y,
CT_Z,
CT_U,
CT_V,
CT_Ignored,
CT_Index,
NUM_CHANNEL_TYPES = 256,
};
typedef size EChannel;
void PrintChannelType(EChannelType eType, CChars* psz);
enum EImagePurpose
{
IP_Unknown,
IP_Diffuse,
IP_Specular,
IP_Illumination,
IP_Opacity,
IP_Normal,
IP_Bump,
IP_UVAdjust,
IP_Detail,
IP_Decal,
IP_Mask,
IP_PaletteBase,
IP_Palette0 = IP_PaletteBase,
IP_Palette1,
};
class CImageChannelsSource : public CUnknown
{
public:const char* ClassName(void){ return "CImageChannelsSource";}size ClassSize(void){ return sizeof(CImageChannelsSource);};
public:
void Kill(void);
virtual size NumChannels(void) =0;
virtual SChannel GetChannel(size iIndex) =0;
};
class CChannelRGB : CImageChannelsSource
{
public:const char* ClassName(void){ return "CChannelRGB";}size ClassSize(void){ return sizeof(CChannelRGB);};
public:
static CImageChannelsSource* Get(void);
size NumChannels(void);
SChannel GetChannel(size iIndex);
};
class CChannelRGBA : CImageChannelsSource
{
public:const char* ClassName(void){ return "CChannelRGBA";}size ClassSize(void){ return sizeof(CChannelRGBA);};
public:
static CImageChannelsSource* Get(void);
size NumChannels(void);
SChannel GetChannel(size iIndex);
};
class CChannelRGBX : CImageChannelsSource
{
public:const char* ClassName(void){ return "CChannelRGBX";}size ClassSize(void){ return sizeof(CChannelRGBX);};
public:
static CImageChannelsSource* Get(void);
size NumChannels(void);
SChannel GetChannel(size iIndex);
};
void PrintImagePurpose(EImagePurpose ePurpose, CChars* psz);
extern CMapIntString gmiszImageChannelLongNames;
extern CMapIntString gmiszImageChannelShortNames;
void ImageChannelDescriptorInit(void);
void ImageChannelDescriptorKill(void);
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
struct SImageColour
{
uint8 c[16];
void Zero(void);
void Full(void);
bool IsZero(size iDataSize);
bool Equals(SImageColour* psColour, size iDataSize);
bool Equals(void* pvColour, size iDataSize);
};
class CImageColour : public CUnknown
{
public:const char* ClassName(void){ return "CImageColour";}size ClassSize(void){ return sizeof(CImageColour);};
public:
void Init(void);
void Kill(void);
virtual float32 GetValue(EChannel eChannel) =0;
virtual void GetChannels(CArraySize* pai) =0;
};
class CImageColourRGB : public CImageColour
{
public:const char* ClassName(void){ return "CImageColourRGB";}size ClassSize(void){ return sizeof(CImageColourRGB);};
public:
float32 r;
float32 g;
float32 b;
void Init(float32 r, float32 g, float32 b);
float32 GetValue(EChannel eChannel);
void GetChannels(CArraySize* pai);
bool Load(CFileReader* pcFile);
bool Save(CFileWriter* pcFile);
};
class CImageColourARGB : public CImageColour
{
public:const char* ClassName(void){ return "CImageColourARGB";}size ClassSize(void){ return sizeof(CImageColourARGB);};
public:
float32 a;
float32 r;
float32 g;
float32 b;
void Init(float32 a, float32 r, float32 g, float32 b);
void Zero(void);
float32 GetValue(EChannel eChannel);
void GetChannels(CArraySize* pai);
bool Load(CFileReader* pcFile);
bool Save(CFileWriter* pcFile);
};
class CImageColourOpacity : public CImageColour
{
public:const char* ClassName(void){ return "CImageColourOpacity";}size ClassSize(void){ return sizeof(CImageColourOpacity);};
public:
float32 a;
void Init(float32 a);
float32 GetValue(EChannel eChannel);
void GetChannels(CArraySize* pai);
bool Load(CFileReader* pcFile);
bool Save(CFileWriter* pcFile);
};
class CImageColourSpecular : public CImageColour
{
public:const char* ClassName(void){ return "CImageColourSpecular";}size ClassSize(void){ return sizeof(CImageColourSpecular);};
public:
float32 s;
void Init(float32 s);
float32 GetValue(EChannel eChannel);
void GetChannels(CArraySize* pai);
bool Load(CFileReader* pcFile);
bool Save(CFileWriter* pcFile);
};
class CImageColourNormal : public CImageColour
{
public:const char* ClassName(void){ return "CImageColourNormal";}size ClassSize(void){ return sizeof(CImageColourNormal);};
public:
float32 x;
float32 y;
float32 z;
void Init(float32 x, float32 y, float32 z);
float32 GetValue(EChannel eChannel);
void GetChannels(CArraySize* pai);
bool Load(CFileReader* pcFile);
bool Save(CFileWriter* pcFile);
};
class CImageColourCombo2 : public CImageColour
{
public:const char* ClassName(void){ return "CImageColourCombo2";}size ClassSize(void){ return sizeof(CImageColourCombo2);};
public:
CImageColour* cImageColours[2];
void Init(CImageColour* pc1, CImageColour* pc2);
float32 GetValue(EChannel eChannel);
void GetChannels(CArraySize* pai);
};
enum EColourOrder
{
CCO_Unknown,
CCO_RGB,
CCO_BRG,
CCO_GBR,
CCO_BGR,
CCO_RBG,
CCO_GRB,
};
enum EColourFormat
{
CFT_Unknown,
CFT_RGB,
CFT_RGBX,
CFT_XRGB,
CFT_RGBA,
CFT_ARGB,
};
enum ERGBColourBits
{
CRGB_Unknown,
CRGB_24bit,
CRGB_30bit,
CRGB_36bit,
CRGB_48bit,
CRGB_Float3,
CRGB_8bit332,
CRGB_8bit323,
CRGB_8bit233,
CRGB_6bit,
CRGB_15bit,
CRGB_16bit,
};
enum ERGBAlphaBits
{
ARGB_Unknown,
ARGB_None,
ARGB_8bit,
ARGB_10bit,
ARGB_12bit,
ARGB_16bit,
ARGB_Float,
ARGB_2bit,
};
enum EColourOpacity
{
CPO_Unknown,
CPO_None,
CPO_Opaque,
CPO_Translucent,
CPO_Transparent,
};
class CColourFormatHelper
{
public:
EColourFormat meFormat;
EColourOrder meOrder;
ERGBColourBits meColourBits;
ERGBAlphaBits meAlphaBits;
void Init(EColourFormat eFormat, EColourOrder eOrder, ERGBColourBits eColourBits, ERGBAlphaBits eAlphaBits);
size GetNumChannels(void);
EChannel GetChannel(size uiIndex);
EPrimitiveType GetType(size uiIndex);
EChannel GetColourChannel(size uiIndex);
EPrimitiveType GetColourType(size uiIndex);
EPrimitiveType GetAlphaType(void);
size GetFirstColourIndex(void);
size GetAlphaIndex(void);
};
struct SImageChangingDesc
{
uint32 uiWidth;
uint32 uiHeight;
};
class CImageCelBlitterCache;
class CImage : public CObject
{
friend class CImageCopier;
friend class CImageAccessor;
friend class CImageDivider;
public:const char* ClassName(void){ return "CImage";}size ClassSize(void){ return sizeof(CImage);};
public:~CImage(void){ Kill();};
public:
CChannels mcChannels;
SUInt32Vec2 msSize;
SImageChangingDesc* mpsImageChangingDesc;
Ptr<CImageCelBlitterCache> mpBlitterCache;
public:
void Init(void);
void Init(uint32 uiWidth, uint32 uiHeight);
void Init(uint32 uiWidth, uint32 uiHeight, EPrimitiveType eType, EChannel eFirst, ...);
void Init(uint32 uiWidth, uint32 uiHeight, void* pvUserData, EPrimitiveType eType, EChannel eFirst, ...);
void Init(uint32 uiWidth, uint32 uiHeight, CImageChannelsSource* pcSource);
void Init(uint32 uiWidth, uint32 uiHeight, void* pvUserData, CImageChannelsSource* pcSource);
void Init(uint32 uiWidth, uint32 uiHeight, Ptr<CImage> pcChannelsSource);
void Init(uint32 uiWidth, uint32 uiHeight, EColourFormat eFormat, EColourOrder eOrder, ERGBColourBits eColourBits, ERGBAlphaBits eAlphaBits);
void Init(uint32 uiWidth, uint32 uiHeight, CColourFormatHelper* pcHelper);
void Init(uint32 uiWidth, uint32 uiHeight, CArrayChannel* pasNewChannels);
void Init(Ptr<CImage> pcChannelsSource);
void Class(void) override;
void Free(void) override;
void ReInit(void);
void ReInit(uint32 uiWidth, uint32 uiHeight, EPrimitiveType eType, EChannel eFirst, ...);
bool Save(CObjectWriter* pcFile) override;
bool Load(CObjectReader* pcFile) override;
void BeginChange(void);
void AddChannel(SChannel* psChannel);
void AddChannel(size iChannel, EPrimitiveType eType, bool bReverse = false);
void AddChannel(size iChannel, EPrimitiveType eType, char* szShortName, char* szLongName = 0L, bool bReverse = false);
bool AddChannel(Ptr<CImage> pcSourceImage, size iChannel, EPrimitiveType eType);
void AddChannel(size iChannel1, size iChannel2, EPrimitiveType eType, bool bReverse = false);
void AddChannel(size iChannel1, size iChannel2, size iChannel3, EPrimitiveType eType, bool bReverse = false);
void AddChannel(size iChannel1, size iChannel2, size iChannel3, size iChannel4, EPrimitiveType eType, bool bReverse = false);
void AddChannels(CImageChannelsSource* pcSource);
void AddChannels(CArrayChannel* pasChannels);
void AddChannels(Ptr<CImage> pcSourceChannels);
bool RemoveChannel(size iChannel);
void RemovePurpose(EImagePurpose ePurpose);
void SetSize(uint32 uiWidth, uint32 uiHeight);
uint32 GetHeight(void);
uint32 GetWidth(void);
uint32 GetImageHeight(void);
uint32 GetImageWidth(void);
void ByteAlignChannels(void);
bool RenameChannel(size iOldName, size iNewName);
bool EndChange(void);
bool IsChanging(void);
Ptr<CImageCelBlitterCache> GetBlitterCache(void);
void Copy(Ptr<CImage> pcSource);
void CopyIntoInitialised(Ptr<CImage> pcSource);
void Black(void);
void White(void);
void SetData(void* pvData);
void* GetData(void);
size GetByteSize(void);
CChannels* GetChannels(void);
size GetPixelSize(void);
size GetPixelByteStride(void);
size GetPixelBitStride(void);
SSizeVec2 GetDimension(void);
bool IsSameFormat(Ptr<CImage> psOther);
bool IsValid(int x, int y);
CChannel* GetChannel(size iChannel);
CChannel* GetChannelAtIndex(size iIndex);
void GetAllChannels(CArraySize* paiChannels);
void GetAllChannels(CArrayChannel* pasChannels);
EPrimitiveType GetPrimitiveType(void);
void GetAllPrimitiveTypes(CArrayInt* paiPrimitiveTypes);
void GetChannelsForType(EPrimitiveType eType, CArraySize* paiChannels);
size NumChannels(void);
const char* GetChannelLongName(size iChannel);
const char* GetChannelShortName(size iChannel);
bool HasChannel(size iChannel);
bool HasChannels(size iFirst, ...);
CArrayChannelOffset* GetChannelOffsets(void);
EColourOrder GetColourOrder(void);
EColourFormat GetColourFormat(void);
ERGBColourBits GetColourBits(void);
ERGBAlphaBits GetAlphaBits(void);
void SetChannelDebugNames(size iChannel);
bool Matches(CColourFormatHelper* pcHelper, bool bReverse = false);
bool Matches(CArrayChannel* pasChannels);
void Print(CChars* psz);
void Dump(void);
protected:
void PrivateInit(void);
};
typedef CArray<CImage> CArrayImage;
class CChannelAccessor
{
public:
size miAccessByteSize;
size miAccessBitSize;
EPrimitiveType meAccessType;
size miChannelByteOffset;
size miChannelByteSize;
EPrimitiveType meChannelType;
bool mbChannelReverse;
size miChannelBitSize;
size miChannelBitOffset;
size miChannel;
void Init(size iAccessByteSize, size iAccessBitSize, EPrimitiveType eAccessType, size iChannelByteOffset, size iChannelByteSize, EPrimitiveType eChannelType, bool bChannelReverse, size iChannelBitSize, size iChannelBitOffset, size iChannel);
void GetNative(void* pvBase, void* pvDest);
void GetAs(EPrimitiveType eType, void* pvBase, void* pvDest);
void GetAsSub(EPrimitiveType eType, void* pvBase, size iBitOffset, void* pvDest);
void SetNative(void* pvBase, void* pvSource);
void SetFrom(EPrimitiveType eType, void* pvBase, void* pvSource);
void SetFromSub(EPrimitiveType eType, void* pvBase, size iBitOffset, void* pvSource);
void GetBits(void* pvBase, size iBitOffset, size iNumBits, void* pvDest);
void SetBits(void* pvBase, size iBitOffset, size iNumBits, void* pvSource);
};
typedef CArrayTemplate<CChannelAccessor> CArrayChannelAccessor;
class CChannelsAccessor : public CUnknown
{
public:const char* ClassName(void){ return "CChannelsAccessor";}size ClassSize(void){ return sizeof(CChannelsAccessor);}
protected:
CChannels* mpcChannels;
CArrayChannelAccessor macAccessors;
size miByteSize;
size miBitSize;
CStackMemory<8> msBuffer;
public:
void Init(CChannels* pcChannels, CArrayChannelAccessor* pcAccessors, size iByteSize, size iBitSize);
virtual void Kill(void);
virtual void* Get(size iPos) =0;
virtual void Set(size iPos, void* pvData) =0;
virtual bool IsContiguous(void);
EPrimitiveType GetType(void);
size GetBitSize(void);
size GetByteSize(void);
size GetBufferSize(void);
CArrayChannelAccessor* GetAccessors(void);
CChannels* GetChannels(void);
};
struct SChannelAccess
{
size iChannel;
EPrimitiveType eType;
};
typedef CArrayTemplate<SChannelAccess> CArrayChannelAccess;
class CChannelsAccessorCreatorParams
{
protected:
CChannels* mpcChannels;
CArrayChannelAccess masAccesses;
CArrayChannelAccessor macAccessors;
bool mbContiguous;
bool mbSourceTypesSame;
bool mbChannelByteAligned;
bool mbAccessByteAligned;
size muiBitSize;
size muiByteSize;
public:
void Init(CChannels* pcChannels);
void Kill(void);
void AddAccess(size iChannel, EPrimitiveType eType = PT_Undefined);
void AddAccess(size iChannel1, size iChannel2, EPrimitiveType eType = PT_Undefined);
void AddAccess(size iChannel1, size iChannel2, size iChannel3, EPrimitiveType eType = PT_Undefined);
void AddAccess(size iChannel1, size iChannel2, size iChannel3, size iChannel4, EPrimitiveType eType = PT_Undefined);
void AddAccess(CArraySize* paiChannels, EPrimitiveType eType = PT_Undefined);
void AddAccess(CChannel* pcChannel);
void AddAccess(CChannels* pcChannels);
void AddAccess(CChannelAccessor* pcChannel);
void AddAccess(CChannelsAccessor* pcChannels);
bool CreateAccessorParams(void);
CArrayChannelAccessor* GetAccessors(void);
CArrayChannelAccess* GetAccesss(void);
bool IsContiguous(void);
bool IsSourceTypesSame(void);
bool IsChannelByteAligned(void);
bool IsAccessByteAligned(void);
size GetBitSize(void);
size GetByteSize(void);
CChannels* GetChannels(void);
protected:
bool CalculateEmpty(void);
bool CalculateContiguous(void);
bool CalculateSourceTypesSame(void);
bool CalculateChannelByteAligned(void);
bool CalculateAccessByteAligned(void);
size CalclulateBitSize(void);
};
class CChannelsAccessorCreator
{
public:
CChannelsAccessorCreatorParams mcParams;
void Init(CChannels* pcChannels);
void Kill(void);
CChannelsAccessor* Create(void);
CChannelsAccessor* CreateAndKill(void);
static CChannelsAccessor* CreateSingleChannelAccessor(CChannels* pcChannels, size iChannel, EPrimitiveType eType = PT_Undefined);
void AddAccess(size iChannel, EPrimitiveType eType = PT_Undefined);
void AddAccess(size iChannel1, size iChannel2, EPrimitiveType eType = PT_Undefined);
void AddAccess(size iChannel1, size iChannel2, size iChannel3, EPrimitiveType eType = PT_Undefined);
void AddAccess(size iChannel1, size iChannel2, size iChannel3, size iChannel4, EPrimitiveType eType = PT_Undefined);
void AddAccess(CArraySize* paiChannels, EPrimitiveType eType = PT_Undefined);
void AddAccess(CChannel* pcChannel);
void AddAccess(CChannels* pcChannels);
void AddAccess(CChannelAccessor* pcChannel);
void AddAccess(CChannelsAccessor* pcChannels);
};
class CImage;
class CImageAccessor : public CUnknown
{
public:const char* ClassName(void){ return "CImageAccessor";}size ClassSize(void){ return sizeof(CImageAccessor);};
protected:
CChannelsAccessor* mpcAccessor;
CImage* mpcImage;
uint32 miWidth;
bool mbKillChannelAccessor;
public:
void Init(CImage* pcImage, CChannelsAccessor* pcAccessor, bool bKillChannelAccessor);
virtual void Kill(void);
virtual void* Get(int32 x, int32 y);
virtual void Set(int32 x, int32 y, void* pvData);
size GetBufferSize(void);
virtual void SyncDataCache(void);
void Get(int32 x, int32 y, void* pvDest);
bool IsValid(int32 x, int32 y);
void* SafeGet(int32 x, int32 y);
void SafeSet(int32 x, int32 y, void* pvData);
bool MakeColour(SImageColour* psDest, CImageColour* pcColour);
bool IsEmpty(void);
EPrimitiveType GetType(void);
size GetBitSize(void);
size GetByteSize(void);
CChannelsAccessor* GetAccessor(void);
CImage* GetImage(void);
uint32 GetWidth(void);
};
class CImageAccessorCreator
{
public:
static CImageAccessor* CreateEmpty(void);
static CImageAccessor* Create(CImage* pcImage, size iFirst, ...);
static CImageAccessor* Create(CImage* pcImage);
static CImageAccessor* Create(CImage* pcImage, CImage* pcChannels);
static CImageAccessor* Create(CImage* pcImage, CArraySize* paiChannels);
static CImageAccessor* Create(CImage* pcImage, CImageColour* pcColour);
protected:
CChannelsAccessorCreator mcCreator;
CImage* mpcImage;
public:
void Init(CImage* pcImage);
void Kill(void);
CImageAccessor* Create(void);
CImageAccessor* CreateAndKill(void);
void AddAccess(EChannel iChannel, EPrimitiveType eType = PT_Undefined);
void AddAccess(EChannel iChannel1, EChannel iChannel2, EPrimitiveType eType = PT_Undefined);
void AddAccess(EChannel iChannel1, EChannel iChannel2, EChannel iChannel3, EPrimitiveType eType = PT_Undefined);
void AddAccess(EChannel iChannel1, EChannel iChannel2, EChannel iChannel3, EChannel iChannel4, EPrimitiveType eType = PT_Undefined);
void AddAccess(CArraySize* paiChannels, EPrimitiveType eType = PT_Undefined);
void AddAccess(CImage* pcImage);
void AddAccess(CImageAccessor* pcChannels);
void AddAccess(CImageColour* pcColour);
void AddAccessFromIntersectionOf(CArraySize* paiChannels1, CArraySize* paiChannels2);
};
struct SBilinearAxis
{
int32* paiFirst;
int32* paiSecond;
int32* paiFraction;
void Init(uint32 uiSourceSize, uint32 uiDestSize);
void Kill(void);
};
bool ResampleBilinear(Ptr<CImage> pcSource, Ptr<CImage> pcDest);
bool ResampleBicubic(Ptr<CImage> pcSource, Ptr<CImage> pcDest);
bool ResampleSmart(Ptr<CImage> pcSource, Ptr<CImage> pcDest);
class CImageModifier : public CObject
{
public:const char* ClassName(void){ return "CImageModifier";}size ClassSize(void){ return sizeof(CImageModifier);};
public:~CImageModifier(void){ Kill();};
public:
void Class(void) override;
void Free(void) override;
bool Save(CObjectWriter* pcFile) override;
bool Load(CObjectReader* pcFile) override;
virtual Ptr<CImage> Modify(Ptr<CImage> pcImage) =0;
};
enum EPow2Style
{
RS_Unknown,
RS_Up,
RS_Down,
RS_Auto
};
enum EImageResample
{
IR_NearestNeighbour,
IR_Bilinear,
IR_Bicubic,
IR_Smart,
};
class CImage;
class CImageResampler : public CImageModifier
{
public:const char* ClassName(void){ return "CImageResampler";}size ClassSize(void){ return sizeof(CImageResampler);};
public:~CImageResampler(void){ Kill();};
private:
void GetPowerOf2Size(EPow2Style eStyle, int iSourceWidth, int iSourceHeight, int* piDestWidth, int* piDestHeight);
Ptr<CImage> ResampleTo(Ptr<CImage> pcSource);
public:
EImageResample meResample;
int miWidth;
int miHeight;
EPow2Style meStyle;
void Init(EImageResample eResample, EPow2Style eStyle);
void Init(EImageResample eResample, int iWidth, int iHeight);
void Class(void) override;
Ptr<CImage> Modify(Ptr<CImage> pcImage);
};
void CImageResampler::Init(EImageResample eResample, EPow2Style eStyle)
{
PreInit();
Init(eResample, -1, -1);
meStyle = eStyle;
PostInit();
}
void CImageResampler::Init(EImageResample eResample, int iWidth, int iHeight)
{
PreInit();
meResample = eResample;
miWidth = iWidth;
miHeight = iHeight;
meStyle = RS_Unknown;
PostInit();
}
void CImageResampler::Class(void)
{
CImageModifier::Class();
UnmanagedEnum(&meResample, "meResample");
UnmanagedInt32(&miWidth, "miWidth");
UnmanagedInt32(&miHeight, "miHeight");
UnmanagedEnum(&meStyle, "meStyle");
}
Ptr<CImage> CImageResampler::Modify(Ptr<CImage> pcImage)
{
Ptr<CImage> pcDest;
if (meStyle != RS_Unknown)
{
GetPowerOf2Size(meStyle, pcImage->GetWidth(), pcImage->GetHeight(), &miWidth, &miHeight);
}
if ((pcImage->GetWidth() == (uint32)miWidth) && (pcImage->GetHeight() == (uint32)miHeight))
{
return pcImage;
}
pcDest = ResampleTo(pcImage);
return pcDest;
}
Ptr<CImage> CImageResampler::ResampleTo(Ptr<CImage> pcSource)
{
float32 fdx;
float32 fdy;
float32 fWidth;
float32 fHeight;
CImageAccessor* pcSourceAccessor;
CImageAccessor* pcDestAccessor;
float32 fsx;
float32 fsy;
float32 fSourceWidth;
float32 fSourceHeight;
float32 fScalex;
float32 fScaley;
SImageColour* psColour;
Ptr<CImage> pcDest;
bool bResampled;
pcDest = OMalloc<CImage>();
pcDest->BeginChange();
pcDest->AddChannels(&pcSource);
pcDest->SetSize(miWidth, miHeight);
pcDest->EndChange();
pcSourceAccessor = CImageAccessorCreator::Create(&pcSource, &pcSource);
pcDestAccessor = CImageAccessorCreator::Create(&pcDest, &pcDest);
if ((pcSource->GetWidth() == (uint32)miWidth) && (pcSource->GetHeight() == (uint32)miHeight))
{
gcLogger.Error2(MethodToString("/home/r2d2/Codaphela/commonlibraries/SupportLib/ImageResampler.cpp", 139, __PRETTY_FUNCTION__), " Implement this.  Copy does not work.");
}
else
{
fWidth = (float32)pcDest->GetWidth();
fHeight = (float32)pcDest->GetHeight();
fSourceWidth = (float32)pcSource->GetWidth();
fSourceHeight = (float32)pcSource->GetHeight();
fScalex = fSourceWidth/fWidth;
fScaley = fSourceHeight/fHeight;
bResampled = false;
if (meResample == IR_Bilinear)
{
bResampled = ResampleBilinear(pcSource, pcDest);
}
else if (meResample == IR_Bicubic)
{
bResampled = ResampleBicubic(pcSource, pcDest);
}
else if (meResample == IR_Smart)
{
bResampled = ResampleSmart(pcSource, pcDest);
}
if (!bResampled)
{
for (fdy = 0.5f; fdy < fHeight; fdy++)
{
fsy = fScaley * fdy;
for (fdx = 0.5f; fdx < fWidth; fdx++)
{
fsx = fScalex * fdx;
psColour = (SImageColour*)pcSourceAccessor->Get((int)fsx, (int)fsy);
pcDestAccessor->Set((int)fdx, (int)fdy, psColour);
}
}
}
}
pcSourceAccessor->Kill();
pcDestAccessor->Kill();
return pcDest;
}
void CImageResampler::GetPowerOf2Size(EPow2Style eStyle, int iSourceWidth, int iSourceHeight, int* piDestWidth, int* piDestHeight)
{
if (eStyle == RS_Up)
{
*piDestWidth = GetPowerOf2SizeUp(iSourceWidth);
*piDestHeight = GetPowerOf2SizeUp(iSourceHeight);
}
else if (eStyle == RS_Down)
{
*piDestWidth = GetPowerOf2SizeDown(iSourceWidth);
*piDestHeight = GetPowerOf2SizeDown(iSourceHeight);
}
else if (eStyle == RS_Auto)
{
*piDestWidth = GetPowerOf2SizeAuto(iSourceWidth);
*piDestHeight = GetPowerOf2SizeAuto(iSourceHeight);
}
}
