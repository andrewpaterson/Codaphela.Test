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
bool CFileReader::ReadData(void* pvData, lsize iDataSize)
{
if (Read(pvData, iDataSize, 1) != 1) { return false; };
return true;
}
bool CFileReader::ReadStringLength(size* piLength)
{
return ReadSize(piLength);
}
bool CFileReader::ReadStringChars(char* szString, size iLength)
{
if (Read(szString, iLength, 1) != 1) { return false; };
return true;
}
bool CFileReader::ReadString(char* szString, size iMaxLength)
{
size iLength;
size iRead;
size iSkip;
char acSkip[64];
if (iMaxLength == 0)
{
return false;
}
if (!ReadStringLength(&iLength))
{
return false;
}
iRead = iLength;
if (iRead > iMaxLength - 1)
{
iRead = iMaxLength - 1;
}
if (!ReadStringChars(szString, iRead))
{
return false;
}
szString[iRead] = 0;
while (iRead < iLength)
{
iSkip = iLength - iRead;
if (iSkip > sizeof(acSkip))
{
iSkip = sizeof(acSkip);
}
if (!ReadStringChars(acSkip, iSkip))
{
return false;
}
iRead += iSkip;
}
return true;
}
bool CFileReader::ReadInt32(int32* pi)
{
if (Read(pi, sizeof(int32), 1) != 1) { return false; };
return true;
}
bool CFileReader::ReadInt32(uint32* pui)
{
if (Read(pui, sizeof(uint32), 1) != 1) { return false; };
return true;
}
bool CFileReader::ReadSize(lsize* pui)
{
int32 i32;
if (Read(&i32, sizeof(int32), 1) != 1) { return false; };
*pui = (lsize)(ptrdiff)i32;
return true;
}
bool CFileReader::ReadSizes(size* pai, size iLength)
{
size i;
for (i = 0; i < iLength; i++)
{
if (!ReadSize(&pai[i]))
{
return false;
}
}
return true;
}
bool CFileReader::ReadSInt(int* pi)
{
if (Read(pi, sizeof(int), 1) != 1) { return false; };
return true;
}
bool CFileReader::ReadSInt(uint* pi)
{
if (Read(pi, sizeof(uint), 1) != 1) { return false; };
return true;
}
bool CFileReader::ReadInt64(int64* plli)
{
if (Read(plli, sizeof(int64), 1) != 1) { return false; };
return true;
}
bool CFileReader::ReadInt64(uint64* pulli)
{
if (Read(pulli, sizeof(uint64), 1) != 1) { return false; };
return true;
}
bool CFileReader::ReadFloat(float32* pf)
{
if (Read(pf, sizeof(float32), 1) != 1) { return false; };
return true;
}
bool CFileReader::ReadFloat(float64* pf)
{
if (Read(pf, sizeof(float64), 1) != 1) { return false; };
return true;
}
bool CFileReader::ReadChar(char8* pc)
{
if (Read(pc, sizeof(char), 1) != 1) { return false; };
return true;
}
bool CFileReader::ReadWChar(char16* pc)
{
if (Read(pc, sizeof(char16), 1) != 1) { return false; };
return true;
}
bool CFileReader::ReadBool(bool* pb)
{
if (Read(pb, sizeof(bool), 1) != 1) { return false; };
return true;
}
bool CFileReader::ReadInt16(int16* pi)
{
if (Read(pi, sizeof(int16), 1) != 1) { return false; };
return true;
}
bool CFileReader::ReadInt16(uint16* pi)
{
if (Read(pi, sizeof(uint16), 1) != 1) { return false; };
return true;
}
bool CFileReader::ReadInt8(int8* pi)
{
if (Read(pi, sizeof(int8), 1) != 1) { return false; };
return true;
}
bool CFileReader::ReadInt8(uint8* pi)
{
if (Read(pi, sizeof(uint8), 1) != 1) { return false; };
return true;
}
bool CFileReader::ReadBits(void* pvData, size iByteLength)
{
if (Read(pvData, iByteLength, 1) != 1) { return false; };
return true;
}
bool CFileReader::ReadIntArray(int32* pai, size iLength)
{
if (Read(pai, iLength * sizeof(int32), 1) != 1) { return false; };
return true;
}
bool CFileReader::ReadLittleEndianInt16(int16* pi)
{
return ReadLittleEndianInt16((uint16*)pi);
}
bool CFileReader::ReadLittleEndianInt16(uint16* pui)
{
uint8 aui[2];
if (Read(aui, 2, 1) != 1) { return false; };
*pui = (uint16)(aui[0] | (aui[1] << 8));
return true;
}
bool CFileReader::ReadLittleEndianInt32(int32* pi)
{
return ReadLittleEndianInt32((uint32*)pi);
}
bool CFileReader::ReadLittleEndianInt32(uint32* pui)
{
uint8 aui[4];
if (Read(aui, 4, 1) != 1) { return false; };
*pui = (uint32)aui[0] | ((uint32)aui[1] << 8) | ((uint32)aui[2] << 16) | ((uint32)aui[3] << 24);
return true;
}
bool CFileReader::ReadBigEndianInt16(int16* pi)
{
return ReadBigEndianInt16((uint16*)pi);
}
bool CFileReader::ReadBigEndianInt16(uint16* pui)
{
uint8 aui[2];
if (Read(aui, 2, 1) != 1) { return false; };
*pui = (uint16)((aui[0] << 8) | aui[1]);
return true;
}
bool CFileReader::ReadBigEndianInt32(int32* pi)
{
return ReadBigEndianInt32((uint32*)pi);
}
bool CFileReader::ReadBigEndianInt32(uint32* pui)
{
uint8 aui[4];
if (Read(aui, 4, 1) != 1) { return false; };
*pui = ((uint32)aui[0] << 24) | ((uint32)aui[1] << 16) | ((uint32)aui[2] << 8) | (uint32)aui[3];
return true;
}
