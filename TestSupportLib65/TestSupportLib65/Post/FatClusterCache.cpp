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
typedef int (*DataCompare)(const void* pvLeft, const void* pvRight);
int ComparePtr(const void* arg1, const void* arg2);
int ComparePtrPtr(const void* arg1, const void* arg2);
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
struct SClusterCache
{
uint32 uiCluster;
uint32 uiClusterFirstSector;
uint8* pvCache;
uint8* pbCachedSectors;
uint8* pbDirtySectors;
};
class CFatClusterCache
{
protected:
SClusterCache msCluster;
uint16 muiClusterSize;
uint16 muiSectorSize;
uint16 muiSectorsPerCluster;
uint16 muiBytesForBits;
CFileDrive* mpcDrive;
public:
void Init(CFileDrive* pcDrive, uint16 uiClusterSize, uint16 uiSectorSize);
void Kill(void);
bool Read(uint8* pvDestination, uint32 uiCluster, uint32 uiClusterFirstSector, uint16 uiOffset, uint32* puiLength, uint16 uiMaximumOffset);
bool Write(uint8* pvSource, uint32 uiCluster, uint32 uiClusterFirstSector, uint16 uiOffset, uint32* puiLength, uint16 uiPreviousMaximumOffset);
bool Flush(void);
void Clear(void);
uint8* GetCache(void);
bool IsSectorDirty(uint16 iSectorIndex);
bool IsSectorCached(uint16 iSectorIndex);
uint16 GetSectorsPerCluster(void);
protected:
void Invalidate(SClusterCache* psCluster);
bool Flush(SClusterCache* psCluster);
bool FlushAndInvalidate(SClusterCache* psCluster);
bool IsCached(uint32 uiSectorIndex);
bool CacheSector(SClusterCache* psCluster, uint32 uiSectorIndex);
bool SetCachedSector(size uiSectorIndex, bool bCached);
bool SetDirtySector(size uiSectorIndex, bool bDirty);
};
void CFatClusterCache::Init(CFileDrive* pcDrive, uint16 uiClusterSize, uint16 uiSectorSize)
{
muiClusterSize = uiClusterSize;
muiSectorSize = uiSectorSize;
muiSectorsPerCluster = muiClusterSize / muiSectorSize;
mpcDrive = pcDrive;
muiBytesForBits = muiSectorsPerCluster / sizeof(uint8);
msCluster.pvCache = (uint8*)malloc(uiClusterSize);
msCluster.pbCachedSectors = (uint8*)malloc(muiBytesForBits);
msCluster.pbDirtySectors = (uint8*)malloc(muiBytesForBits);
Invalidate(&msCluster);
}
void CFatClusterCache::Kill(void)
{
if (msCluster.pbDirtySectors) { free(msCluster.pbDirtySectors); msCluster.pbDirtySectors = 0L; };
if (msCluster.pbCachedSectors) { free(msCluster.pbCachedSectors); msCluster.pbCachedSectors = 0L; };
if (msCluster.pvCache) { free(msCluster.pvCache); msCluster.pvCache = 0L; };
}
bool CFatClusterCache::Read(uint8* pvDestination, uint32 uiCluster, uint32 uiClusterFirstSector, uint16 uiOffset, uint32* puiLength, uint16 uiMaximumOffset)
{
bool bResult;
uint32 uiLength;
uint16 uiFirstSectorIndex;
uint16 uiLastSectorIndexInclusive;
uint16 uiMaximumSector;
size iStart;
size iEnd;
uint16 uiNumSectors;
if (uiOffset >= muiClusterSize)
{
return false;
}
if (uiOffset > uiMaximumOffset)
{
return false;
}
if (uiMaximumOffset > muiClusterSize)
{
return false;
}
if (uiCluster != msCluster.uiCluster)
{
bResult = FlushAndInvalidate(&msCluster);
if (!bResult)
{
return false;
}
msCluster.uiCluster = uiCluster;
msCluster.uiClusterFirstSector = uiClusterFirstSector;
}
uiLength = *puiLength;
if (uiOffset + uiLength > uiMaximumOffset)
{
uiLength = uiMaximumOffset - uiOffset;
}
uiFirstSectorIndex = uiOffset / muiSectorSize;
uiLastSectorIndexInclusive = (uiOffset + (uiLength - 1)) / muiSectorSize;
uiMaximumSector = (uint16)(((int32)uiMaximumOffset - 1) / muiSectorSize);
if (uiFirstSectorIndex > uiMaximumSector)
{
return false;
}
if (uiLastSectorIndexInclusive >= muiSectorsPerCluster)
{
uiLastSectorIndexInclusive = muiSectorsPerCluster - 1;
uiLength = muiClusterSize - uiOffset;
*puiLength -= uiLength;
}
else
{
*puiLength -= uiLength;
}
for (;;)
{
iStart = FindNextClearBit(msCluster.pbCachedSectors, muiSectorsPerCluster, uiFirstSectorIndex);
if ((iStart == ((size)-1)) || (iStart > uiLastSectorIndexInclusive))
{
break;
}
iEnd = FindNextSetBit(msCluster.pbCachedSectors, muiSectorsPerCluster, iStart);
if ((iEnd == ((size)-1)) || (iEnd > uiLastSectorIndexInclusive))
{
iEnd = uiLastSectorIndexInclusive + 1;
}
uiNumSectors = (uint16)(iEnd - iStart);
mpcDrive->Read(msCluster.uiClusterFirstSector + iStart, uiNumSectors, &msCluster.pvCache[iStart * muiSectorSize]);
SetBits(iStart, msCluster.pbCachedSectors, true, uiNumSectors);
if (iEnd > uiLastSectorIndexInclusive)
{
break;
}
}
memcpy(pvDestination, &msCluster.pvCache[uiOffset], uiLength);
return true;
}
bool CFatClusterCache::Write(uint8* pvSource, uint32 uiCluster, uint32 uiClusterFirstSector, uint16 uiOffset, uint32* puiLength, uint16 uiPreviousMaximumOffset)
{
bool bResult;
uint32 uiLength;
uint16 uiFirstSectorIndex;
uint16 uiLastSectorIndexInclusive;
uint16 i;
uint16 uiPreviousMaximumSector;
uint16 uiSectorLength;
uint16 uiIndex;
if (uiOffset >= muiClusterSize)
{
return false;
}
if (uiOffset > uiPreviousMaximumOffset)
{
return false;
}
if (uiPreviousMaximumOffset > muiClusterSize)
{
return false;
}
if (uiCluster != msCluster.uiCluster)
{
bResult = FlushAndInvalidate(&msCluster);
if (!bResult)
{
return false;
}
msCluster.uiCluster = uiCluster;
msCluster.uiClusterFirstSector = uiClusterFirstSector;
}
uiLength = *puiLength;
uiFirstSectorIndex = uiOffset / muiSectorSize;
uiLastSectorIndexInclusive = (uiOffset + (uiLength - 1)) / muiSectorSize;
if (uiLastSectorIndexInclusive >= muiSectorsPerCluster)
{
uiLastSectorIndexInclusive = muiSectorsPerCluster - 1;
uiLength = muiClusterSize - uiOffset;
*puiLength -= uiLength;
}
else
{
*puiLength = 0;
}
uiPreviousMaximumSector = (uint16)(((int32)uiPreviousMaximumOffset - 1) / muiSectorSize);
if (uiFirstSectorIndex <= uiPreviousMaximumSector)
{
if ((uiOffset % muiSectorSize != 0) && (!IsCached(uiFirstSectorIndex)))
{
bResult = CacheSector(&msCluster, uiFirstSectorIndex);
if (!bResult)
{
return false;
}
}
}
uiSectorLength = muiSectorSize - uiOffset % muiSectorSize;
if (uiSectorLength > uiLength)
{
uiSectorLength = uiLength;
}
uiIndex = 0;
memcpy(&msCluster.pvCache[uiOffset], &pvSource[uiIndex], uiSectorLength);
SetCachedSector(uiFirstSectorIndex, true);
SetDirtySector(uiFirstSectorIndex, true);
uiIndex += uiSectorLength;
uiOffset += uiSectorLength;
uiLength -= uiSectorLength;
uiSectorLength = muiSectorSize;
for (i = uiFirstSectorIndex + 1; i < uiLastSectorIndexInclusive; i++)
{
memcpy(&msCluster.pvCache[uiOffset], &pvSource[uiIndex], uiSectorLength);
SetCachedSector(i, true);
SetDirtySector(i, true);
uiIndex += uiSectorLength;
uiOffset += uiSectorLength;
uiLength -= uiSectorLength;
}
if (uiFirstSectorIndex != uiLastSectorIndexInclusive)
{
if (uiLastSectorIndexInclusive <= uiPreviousMaximumSector)
{
if (((uiOffset + uiLength) % muiSectorSize != 0) && (!IsCached(uiLastSectorIndexInclusive)))
{
bResult = CacheSector(&msCluster, uiLastSectorIndexInclusive);
if (!bResult)
{
return false;
}
}
}
uiSectorLength = uiLength;
memcpy(&msCluster.pvCache[uiOffset], &pvSource[uiIndex], uiSectorLength);
SetCachedSector(uiLastSectorIndexInclusive, true);
SetDirtySector(uiLastSectorIndexInclusive, true);
uiIndex += uiSectorLength;
uiOffset += uiSectorLength;
uiLength -= uiSectorLength;
}
return true;
}
bool CFatClusterCache::Flush(void)
{
return Flush(&msCluster);
}
bool CFatClusterCache::Flush(SClusterCache* psCluster)
{
size iFirstDirtySector;
size iLastDirtySector;
bool bDone;
bool bResult;
if (psCluster->uiCluster == 0xffffffff)
{
return true;
}
iFirstDirtySector = FindFirstSetBit(psCluster->pbDirtySectors, muiSectorsPerCluster);
if (iFirstDirtySector == ((size)-1))
{
return true;
}
bDone = false;
for (;;)
{
iLastDirtySector = FindNextClearBit(psCluster->pbDirtySectors, muiSectorsPerCluster, iFirstDirtySector);
if (iLastDirtySector == ((size)-1))
{
iLastDirtySector = muiSectorsPerCluster;
bDone = true;
}
bResult = mpcDrive->Write(psCluster->uiClusterFirstSector + (uint32)iFirstDirtySector, (uint32)(iLastDirtySector - iFirstDirtySector), &psCluster->pvCache[iFirstDirtySector * muiSectorSize]);
if (!bResult)
{
return false;
}
if (bDone)
{
break;
}
iFirstDirtySector = FindNextSetBit(psCluster->pbDirtySectors, muiSectorsPerCluster, iLastDirtySector);
if (iFirstDirtySector == ((size)-1))
{
break;
}
}
memset(psCluster->pbDirtySectors, 0, muiBytesForBits);
return true;
}
bool CFatClusterCache::FlushAndInvalidate(SClusterCache* psCluster)
{
bool bResult;
bResult = Flush(psCluster);
Invalidate(psCluster);
return bResult;;
}
bool CFatClusterCache::IsCached(uint32 uiSectorIndex)
{
return GetBit(uiSectorIndex, msCluster.pbCachedSectors);
}
bool CFatClusterCache::CacheSector(SClusterCache* psCluster, uint32 uiSectorIndex)
{
bool bResult;
bResult = mpcDrive->Read(psCluster->uiClusterFirstSector + uiSectorIndex, psCluster->pvCache);
if (!bResult)
{
return false;
}
SetCachedSector(uiSectorIndex, true);
SetDirtySector(uiSectorIndex, false);
return true;
}
void CFatClusterCache::Clear(void)
{
Invalidate(&msCluster);
}
void CFatClusterCache::Invalidate(SClusterCache* psCluster)
{
psCluster->uiCluster = 0xffffffff;
memset(psCluster->pvCache, 0, muiClusterSize);
memset(psCluster->pbCachedSectors, 0, muiBytesForBits);
memset(psCluster->pbDirtySectors, 0, muiBytesForBits);
}
uint8* CFatClusterCache::GetCache(void)
{
return msCluster.pvCache;
}
bool CFatClusterCache::IsSectorDirty(uint16 iSectorIndex)
{
if (iSectorIndex < muiSectorsPerCluster)
{
return GetBit(iSectorIndex, msCluster.pbDirtySectors);
}
else
{
return false;
}
}
bool CFatClusterCache::IsSectorCached(uint16 iSectorIndex)
{
if (iSectorIndex < muiSectorsPerCluster)
{
return GetBit(iSectorIndex, msCluster.pbCachedSectors);
}
else
{
return false;
}
}
uint16 CFatClusterCache::GetSectorsPerCluster(void)
{
return muiSectorsPerCluster;
}
bool CFatClusterCache::SetCachedSector(size uiSectorIndex, bool bCached)
{
if (uiSectorIndex < muiBytesForBits)
{
SetBit(uiSectorIndex, msCluster.pbCachedSectors, bCached);
return true;
}
else
{
return false;
}
}
bool CFatClusterCache::SetDirtySector(size uiSectorIndex, bool bDirty)
{
if (uiSectorIndex < muiBytesForBits)
{
SetBit(uiSectorIndex, msCluster.pbDirtySectors, bDirty);
return true;
}
else
{
return false;
}
}
