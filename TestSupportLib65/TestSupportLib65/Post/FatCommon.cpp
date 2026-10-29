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
void* RemapSinglePointer(const void* pvPtr, ptrdiff iOffest);
__inline void* RemapSinglePointer(const void* pvPtr, ptrdiff iOffest)
{
return &((char*)pvPtr)[iOffest];
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
char gszFatSuccess[] = "SUCCESS";
char gszFatBad[] = "BAD_FAT_CODE";
char gaszFatErrors[][34] = {"UNKNOWN_ERROR" ,
"CANNOT_READ_MEDIA",
"CANNOT_WRITE_MEDIA",
"NOT_A_DIRECTORY",
"INVALID_FILENAME",
"FILENAME_ALREADY_EXISTS",
"INVALID_PATH",
"CORRUPTED_FILE",
"ILLEGAL_FILENAME",
"FILENAME_TOO_LONG",
"NOT_A_FILE",
"FILE_NOT_FOUND",
"DIRECTORY_DOES_NOT_EXIST",
"INSUFFICIENT_DISK_SPACE",
"FEATURE_NOT_SUPPORTED",
"OPERATION_IN_PROGRESS",
"SECTOR_SIZE_NOT_SUPPORTED",
"LFN_GENERATED",
"SHORT_LFN_GENERATED",
"SEEK_FAILED",
"FILE_NOT_OPENED_FOR_WRITE_ACCESS",
"INVALID_HANDLE",
"INVALID_CLUSTER",
"INVALID_FAT_VOLUME",
"INVALID_VOLUME_LABEL",
"INVALID_FORMAT_PARAMETERS",
"ROOT_DIRECTORY_LIMIT_EXCEEDED",
"DIRECTORY_LIMIT_EXCEEDED",
"INVALID_PARAMETERS",
"FILE_HANDLE_IN_USE",
"FILE_BUFFER_NOT_SET",
"MISALIGNED_IO",
"AWAITING_DATA",
"BUFFER_TOO_BIG"};
char gaszFatAttributes[][10] = {"READ_ONLY",
"HIDDEN",
"SYSTEM",
"VOLUME_ID",
"DIRECTORY",
"ARCHIVE",
"LONG_NAME"};
uint32 GetFirstClusterFromFatEntry(SFatRawDirectoryEntry* psRawEntry, bool bFat32Volume)
{
uint32 uiCluster;
if (psRawEntry != 0L)
{
((uint16*)&uiCluster)[0] = psRawEntry->uEntry.sFatRawCommon.uiFirstClusterLowWord;
if (bFat32Volume)
{
((uint16*)&uiCluster)[1] = psRawEntry->uEntry.sFatRawCommon.uiFirstClusterHighWord;
}
else
{
((uint16*)&uiCluster)[1] = 0;
}
return uiCluster;
}
else
{
return 0xFFFFFFFF;
}
}
const char* FatAttributeToString(uint8 uiAttribute)
{
if (uiAttribute == (0x1 | 0x2 | 0x4 | 0x8))
{
return gaszFatAttributes[6];
}
if (uiAttribute & 0x1)
{
return gaszFatAttributes[0];
}
else if (uiAttribute & 0x2)
{
return gaszFatAttributes[1];
}
else if (uiAttribute & 0x4)
{
return gaszFatAttributes[2];
}
else if (uiAttribute & 0x8)
{
return gaszFatAttributes[3];
}
else if (uiAttribute & 0x10)
{
return gaszFatAttributes[4];
}
else if (uiAttribute & 0x20)
{
return gaszFatAttributes[5];
}
else
{
return "";
}
}
char* FatCodeToString(EFatCode eCode)
{
if (eCode == FAT_SUCCESS)
{
return gszFatSuccess;
}
if (eCode >= FAT_UNKNOWN_ERROR && eCode <= FAT_LAST_ERROR_ENUM)
{
return gaszFatErrors[eCode - 0x20];
}
return gszFatBad;
}
const char* FatEntryToString(SFatDirectoryEntry* psFatEntry, bool bFat32Volume)
{
uint32 uiCluster;
size iCount;
char szTemp[512];
if (psFatEntry == 0L)
{
return "NULL";
}
uiCluster = GetFirstClusterFromFatEntry(&psFatEntry->sRaw, bFat32Volume);
iCount = IncrementLogToStringCount();
memset(gaszLogToStringScratchPad[iCount], 0, 512);
StrCpySafe(gaszLogToStringScratchPad[iCount], "cluster: ", 512);
IntToString(szTemp, 512, uiCluster);
StrCatSafe(gaszLogToStringScratchPad[iCount], szTemp, 512);
StrCatSafe(gaszLogToStringScratchPad[iCount], ", sector: ", 512);
IntToString(szTemp, 512, psFatEntry->uiSectorAddress);
StrCatSafe(gaszLogToStringScratchPad[iCount], szTemp, 512);
StrCatSafe(gaszLogToStringScratchPad[iCount], ":", 512);
IntToString(szTemp, 512, psFatEntry->uiSectorOffset);
StrCatSafe(gaszLogToStringScratchPad[iCount], szTemp, 512);
return gaszLogToStringScratchPad[iCount];
}
void SFatQueryState::Init(void)
{
memset(this, 0, sizeof(SFatQueryState));
memset(uiLockedSectors, 0xff, sizeof(uint32) * 32);
}
bool SFatQueryState::Kill(CFatInfoSectorCache* pcCache)
{
int i;
uint32 uiSector;
bool bResult;
bResult = true;
for (i = 0; i < 32; i++)
{
uiSector = uiLockedSectors[i];
if (uiSector != 0xffffffff)
{
bResult &= pcCache->Unlock(uiSector);
uiLockedSectors[i] = 0xffffffff;
}
}
return bResult;
}
bool SFatQueryState::Lock(uint32 uiSector)
{
int i;
uint32 uiCheckSector;
for (i = 0; i < 32; i++)
{
uiCheckSector = uiLockedSectors[i];
if (uiCheckSector == 0xffffffff)
{
uiLockedSectors[i] = uiSector;
return true;
}
}
return false;
}
void SFatFileSystemQuery::Init(void)
{
memset(&sCurrentEntry, 0, sizeof(SFatDirectoryEntry));
sQuery.Init();
}
void SFatFileSystemQuery::Kill(CFatInfoSectorCache* pcCache)
{
sQuery.Kill(pcCache);
}
