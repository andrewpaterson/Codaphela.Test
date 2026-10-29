typedef unsigned long size_t;
typedef long ptrdiff_t;
typedef long long max_align_t;
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
uint32 TruncateLowBits(uint32 i)
{
if (i == 0)
{
return 0;
}
return 1 << GetLogBase2(i);
}
bool IsPowerOfTwo(uint32 i)
{
uint32 iPow2;
iPow2 = TruncateLowBits(i);
if (iPow2 == i)
{
return true;
}
return false;
}
uint32 GetBestHighBit(uint32 i)
{
uint32 i2;
i2 = i;
i = TruncateLowBits(i);
if (i != i2)
{
return i << 1;
}
return i;
}
size GetLogBase2(uint32 i)
{
size c;
c = 32;
do
{
c--;
if (GetBit(c, &i))
{
return c;
}
}
while (c != 0);
return 0;
}
uint8 GetByte(uint32 iInt, uint16 uiPos)
{
uiPos <<= 3;
iInt >>= uiPos;
return iInt;
}
uint32 SetByte(uint8 c, uint16 iPos)
{
uint32 uiC;
uiC = c;
iPos <<= 8;
uiC <<= iPos;
return uiC;
}
bool GetBit(size iBit, void* pvBitArray)
{
return ((uint8*)pvBitArray)[iBit / 8] & (1 << (iBit % 8));
}
bool GetBitReverseHiLo(size iBit, void* pvBitArray)
{
return ((uint8*)pvBitArray)[iBit / 8] & (1 << (7 - (iBit % 8)));
}
void SetBit(size iBit, void* pvBitArray, bool bBit)
{
if (bBit)
{
((uint8*)pvBitArray)[iBit / 8] |= (1 << (iBit % 8));
}
else
{
((uint8*)pvBitArray)[iBit / 8] &= ~(1 << (iBit % 8));
}
}
size CountBits_PopCount64(uint64 x)
{
const uint64 m1 = 0x5555555555555555LL;
const uint64 m2 = 0x3333333333333333LL;
const uint64 m4 = 0x0f0f0f0f0f0f0f0fLL;
const uint64 m5 = 0x0101010101010101LL;
x = x - ((x >> 1) & m1);
x = (x & m2) + ((x >> 2) & m2);
x = (x + (x >> 4)) & m4;
return (x * m5) >> 56;
}
size CountBits_PopCount32(uint32 i)
{
const uint32 m1 = 0x55555555;
const uint32 m2 = 0x33333333;
const uint32 m4 = 0x0f0f0f0f;
i = i - ((i >> 1) & m1);
i = (i & m2) + ((i >> 2) & m2);
i = ((i + (i >> 4)) & m4);
return (i * 0x01010101) >> 24;
}
size CountBits_PopCount16(uint16 i)
{
const uint16 m1 = 0x5555;
const uint16 m2 = 0x3333;
const uint16 m4 = 0x0f0f;
i = i - ((i >> 1) & m1);
i = (i & m2) + ((i >> 2) & m2);
i = ((i + (i >> 4)) & m4);
return (uint16)(i * 0x0101) >> 8;
}
size CountBits_PopCount8(uint8 b)
{
b = b - ((b >> 1) & 0x55);
b = (b & 0x33) + ((b >> 2) & 0x33);
return (((b + (b >> 4)) & 0x0f) * 0x01);
}
size CountBitsSingly(void* pvBitArray, size iBitLength)
{
size iCount;
size i;
for (i = 0, iCount = 0; i < iBitLength; i++)
{
if (GetBit(i, pvBitArray))
{
iCount++;
}
}
return iCount;
}
size CountDigits(int16 i)
{
int16 iCmp;
size iDigits;
i = Absolute(i);
if (i >= 10000)
{
return 5;
}
iCmp = 1;
for (iDigits = 0; iDigits < 5; iDigits++)
{
if (i < iCmp)
{
return iDigits;
}
iCmp *= 10;
}
return iDigits;
}
size CountDigits(int32 i)
{
int32 iCmp;
size iDigits;
i = Absolute(i);
if (i >= 1000000000)
{
return 10;
}
iCmp = 1;
for (iDigits = 0; iDigits < 10; iDigits++)
{
if (i < iCmp)
{
return iDigits;
}
iCmp *= 10;
}
return iDigits;
}
size CountDigits(int64 i)
{
int64 iCmp;
size iDigits;
i = Absolute(i);
if (i >= 1000000000000000000LL)
{
return 19;
}
iCmp = 1;
for (iDigits = 0; iDigits < 19; iDigits++)
{
if (i < iCmp)
{
return iDigits;
}
iCmp *= 10;
}
return iDigits;
}
size CountBits(void* pvBitArray, size iBitLength)
{
if (iBitLength == 32)
{
return CountBits_PopCount32(*((uint32*)pvBitArray));
}
else if (iBitLength == 64)
{
return CountBits_PopCount64(*((uint64*)pvBitArray));
}
else if (iBitLength == 128)
{
return CountBits_PopCount64(*((uint64*)pvBitArray)) +
CountBits_PopCount64(((uint64*)pvBitArray)[1]);
}
else if (iBitLength == 8)
{
return CountBits_PopCount8(*((uint8*)pvBitArray));
}
else if (iBitLength == 16)
{
return CountBits_PopCount16(*((uint16*)pvBitArray));
}
else
{
size iCount;
size iWords;
size i;
iWords = iBitLength / 32;
iCount = 0;
for (i = 0; i < iWords; i++)
{
iCount += CountBits_PopCount32(((uint32*)pvBitArray)[i]);
}
return iCount + CountBitsSingly(&((uint32*)pvBitArray)[iWords], iBitLength % 32);
}
}
void SetBits(size iStart, void* pvBitArray, bool bBit, size iLength)
{
size i;
size j;
for (i = 0, j = iStart; i < iLength; i++, j++)
{
SetBit(j, pvBitArray, bBit);
}
}
size FindFirstSetBit(void* pvArray, size iArraySize)
{
size iIntSize;
size i;
size iRemainder;
size iCharSize;
size iStart;
size iEnd;
bool bFound;
uint8 c;
iIntSize = iArraySize / 32;
iRemainder = iArraySize % 32;
for (i = 0; i < iIntSize; i++)
{
if (((uint32*)pvArray)[i] != 0x00000000)
{
break;
}
}
iCharSize = iRemainder / 8;
iRemainder = iRemainder % 8;
iStart = i * 4;
iEnd = iIntSize * 4 + iCharSize;
bFound = false;
for (i = iStart; i < iEnd; i++)
{
c = ((uint8*)pvArray)[i];
if (c != (uint8)0x00)
{
bFound = true;
break;
}
}
if ((i < iEnd) || (iRemainder == 0))
{
if (!bFound)
{
return ((size)-1);
}
c = ((uint8*)pvArray)[i];
iStart = i * 8;
uint8 ucCmp = 1;
if ((c & ucCmp))
return iStart;
ucCmp <<= 1;
if ((c & ucCmp))
return iStart + 1;
ucCmp <<= 1;
if ((c & ucCmp))
return iStart + 2;
ucCmp <<= 1;
if ((c & ucCmp))
return iStart + 3;
ucCmp <<= 1;
if ((c & ucCmp))
return iStart + 4;
ucCmp <<= 1;
if ((c & ucCmp))
return iStart + 5;
ucCmp <<= 1;
if ((c & ucCmp))
return iStart + 6;
ucCmp <<= 1;
if ((c & ucCmp))
return iStart + 7;
return ((size)-1);
}
else
{
c = ((uint8*)pvArray)[i];
iStart = i * 8;
uint8 ucCmp = 1;
for (i = 0; i < iRemainder; i++)
{
if ((c & ucCmp))
return iStart + i;
ucCmp <<= 1;
}
return ((size)-1);
}
}
size FindFirstClearBit(void* pvArray, size iArraySize)
{
size iIntSize;
size i;
size iRemainder;
size iCharSize;
size iStart;
size iEnd;
bool bFound;
uint8 c;
iIntSize = iArraySize / 32;
iRemainder = iArraySize % 32;
for (i = 0; i < iIntSize; i++)
{
if (((uint32*)pvArray)[i] != 0xffffffff)
{
break;
}
}
iCharSize = iRemainder / 8;
iRemainder = iRemainder % 8;
iStart = i * 4;
iEnd = iIntSize * 4 + iCharSize;
bFound = false;
for (i = iStart; i < iEnd; i++)
{
c = ((uint8*)pvArray)[i];
if (c != (uint8)0xff)
{
bFound = true;
break;
}
}
if ((i < iEnd) || (iRemainder == 0))
{
if (!bFound)
{
return ((size)-1);
}
c = ((uint8*)pvArray)[i];
iStart = i * 8;
uint8 ucCmp = 1;
if (!(c & ucCmp))
return iStart;
ucCmp <<= 1;
if (!(c & ucCmp))
return iStart + 1;
ucCmp <<= 1;
if (!(c & ucCmp))
return iStart + 2;
ucCmp <<= 1;
if (!(c & ucCmp))
return iStart + 3;
ucCmp <<= 1;
if (!(c & ucCmp))
return iStart + 4;
ucCmp <<= 1;
if (!(c & ucCmp))
return iStart + 5;
ucCmp <<= 1;
if (!(c & ucCmp))
return iStart + 6;
ucCmp <<= 1;
if (!(c & ucCmp))
return iStart + 7;
return ((size)-1);
}
else
{
c = ((uint8*)pvArray)[i];
iStart = i * 8;
uint8 ucCmp = 1;
for (i = 0; i < iRemainder; i++)
{
if (!(c & ucCmp))
return iStart + i;
ucCmp <<= 1;
}
return ((size)-1);
}
}
size FindFirstClearBit(uint32 uiBits)
{
return __builtin_ctz(~uiBits);
}
size FindFirstSetBit(uint64 uiBits)
{
return __builtin_ctzll(uiBits);
}
size FindNextSetBit(void* pvArray, size iArraySize, size iStartBit)
{
size i;
size iRemainder;
size iStart;
uint8 c;
size iResult;
size iStop;
size ij;
size iStartEight;
iRemainder = iStartBit % 8;
iStart = iStartBit / 8;
if (iRemainder != 0)
{
iStop = iArraySize < 8 ? iArraySize : 8;
c = ((uint8*)pvArray)[iStart];
ij = iStart * 8;
uint8 ucCmp = 1 << iRemainder;
for (i = iRemainder; i < iStop; i++)
{
if ((c & ucCmp))
return ij + i;
ucCmp <<= 1;
}
iStartEight = iStart * 8 + 8;
if (iStartEight < iArraySize)
{
iResult = FindFirstSetBit(&((uint8*)pvArray)[iStart + 1], iArraySize - iStartEight);
if (iResult != ((size)-1))
{
return iResult + iStartEight;
}
}
return ((size)-1);
}
else
{
iStartEight = iStartBit;
iResult = FindFirstSetBit(&((uint8*)pvArray)[iStart], iArraySize - iStartEight);
if (iResult != ((size)-1))
{
return iResult + iStartEight;
}
return iResult;
}
}
size FindNextClearBit(void* pvArray, size iArraySize, size iStartBit)
{
size i;
size iRemainder;
size iStart;
uint8 c;
size iResult;
size iStop;
size ij;
size iStartEight;
iRemainder = iStartBit % 8;
iStart = iStartBit / 8;
if (iRemainder != 0)
{
iStop = iArraySize < 8 ? iArraySize : 8;
c = ((uint8*)pvArray)[iStart];
ij = iStart * 8;
uint8 ucCmp = 1 << iRemainder;
for (i = iRemainder; i < iStop; i++)
{
if (!(c & ucCmp))
{
return ij + i;
}
ucCmp <<= 1;
}
iStartEight = iStart * 8 + 8;
if (iStartEight < iArraySize)
{
iResult = FindFirstClearBit(&((uint8*)pvArray)[iStart + 1], iArraySize - iStartEight);
if (iResult != ((size)-1))
{
return iResult + iStartEight;
}
}
return ((size)-1);
}
else
{
iStartEight = iStartBit;
iResult = FindFirstClearBit(&((uint8*)pvArray)[iStart], iArraySize - iStartEight);
if (iResult != ((size)-1))
{
return iResult + iStartEight;
}
return iResult;
}
}
size FindLastClearBit(void* pvArray, size iArraySize)
{
size i;
bool iBit;
if (iArraySize != 0)
{
i = iArraySize;
do
{
i--;
iBit = GetBit(i, pvArray);
if (iBit == 0)
{
return i;
}
}
while (i != 0);
}
return ((size)-1);
}
size FindLastSetBit(void* pvArray, size iArraySize)
{
size i;
bool iBit;
if (iArraySize != 0)
{
i = iArraySize;
do
{
i--;
iBit = GetBit(i, pvArray);
if (iBit)
{
return i;
}
}
while (i != 0);
}
return ((size)-1);
}
void SetFlagInt(uint32* piDest, uint32 iFlag, bool iFlagValue)
{
if (iFlagValue)
{
*piDest |= iFlag;
}
else
{
*piDest &= (~iFlag);
}
}
void SetFlagShort(uint16* psiDest, uint16 iFlag, bool iFlagValue)
{
if (iFlagValue)
{
*psiDest |= iFlag;
}
else
{
*psiDest &= (~iFlag);
}
}
void SetFlagByte(uint8* psiDest, uint8 iFlag, bool iFlagValue)
{
if (iFlagValue)
{
*psiDest |= iFlag;
}
else
{
*psiDest &= (~iFlag);
}
}
void SetFlagLong(uint64* piDest, uint64 iFlag, bool iFlagValue)
{
if (iFlagValue)
{
*piDest |= iFlag;
}
else
{
*piDest &= (~iFlag);
}
}
void SetFlagInt(int32* piDest, int32 iFlag, bool iFlagValue)
{
if (iFlagValue)
{
*piDest |= iFlag;
}
else
{
*piDest &= (~iFlag);
}
}
void SetFlagShort(int16* psiDest, int16 iFlag, bool iFlagValue)
{
if (iFlagValue)
{
*psiDest |= iFlag;
}
else
{
*psiDest &= (~iFlag);
}
}
void SetFlagByte(int8* psiDest, int8 iFlag, bool iFlagValue)
{
if (iFlagValue)
{
*psiDest |= iFlag;
}
else
{
*psiDest &= (~iFlag);
}
}
void SetFlagLong(int64* piDest, int64 iFlag, bool iFlagValue)
{
if (iFlagValue)
{
*piDest |= iFlag;
}
else
{
*piDest &= (~iFlag);
}
}
void SetFlagSize(size* piDest, size iFlag, bool iFlagValue)
{
if (iFlagValue)
{
*piDest |= iFlag;
}
else
{
*piDest &= (~iFlag);
}
}
void SwapInt16(int16* pi1, int16* pi2)
{
int16 i3;
i3 = *pi1;
*pi1 = *pi2;
*pi2 = i3;
}
void SwapUint16(uint16* pi1, uint16* pi2)
{
uint16 i3;
i3 = *pi1;
*pi1 = *pi2;
*pi2 = i3;
}
void SwapInt32(int32* pi1, int32* pi2)
{
int32 i3;
i3 = *pi1;
*pi1 = *pi2;
*pi2 = i3;
}
void SwapUint32(uint32* pi1, uint32* pi2)
{
uint32 i3;
i3 = *pi1;
*pi1 = *pi2;
*pi2 = i3;
}
void SwapInt(int* pi1, int* pi2)
{
int i3;
i3 = *pi1;
*pi1 = *pi2;
*pi2 = i3;
}
void SwapInt(uint* pi1, uint* pi2)
{
uint i3;
i3 = *pi1;
*pi1 = *pi2;
*pi2 = i3;
}
void SwapByte(uint8* pc1, uint8* pc2)
{
char c3;
c3 = *pc1;
*pc1= *pc2;
*pc2 = c3;
}
void SwapSize(size* pui1, size* pui2)
{
size temp;
temp = *pui2;
*pui2 = *pui1;
*pui1 = temp;
}
void SwapBit(uint8* puiByte, size uiBit1, size uiBit2)
{
bool bBit1;
bool bBit2;
bBit1 = GetBit(uiBit1, puiByte);
bBit2 = GetBit(uiBit2, puiByte);
SetBit(uiBit1, puiByte, bBit2);
SetBit(uiBit2, puiByte, bBit1);
}
void SwapBit(uint16* puiByte, size uiBit1, size uiBit2)
{
bool bBit1;
bool bBit2;
bBit1 = GetBit(uiBit1, puiByte);
bBit2 = GetBit(uiBit2, puiByte);
SetBit(uiBit1, puiByte, bBit2);
SetBit(uiBit2, puiByte, bBit1);
}
size FindFirstInt(int32* piIntArray, int32 iSearch, size iMaxLength)
{
size i;
for (i = 0; i < iMaxLength; i++)
{
if (piIntArray[i] == iSearch)
{
return i;
}
}
return ((size)-1);
}
size FindFirstByte(uint8* pcCharArray, uint8 uiSearch, size iMaxLength)
{
size i;
for (i = 0; i < iMaxLength; i++)
{
if (pcCharArray[i] == uiSearch)
{
return i;
}
}
return ((size)-1);
}
uint8 GetHighNybble(uint8 c)
{
return ((int32)c >> 4) & 0xf;
}
uint8 GetLowNybble(uint8 c)
{
return (int32)c & 0xf;
}
int32 IntAbs(int32 i)
{
if (i >= 0)
{
return i;
}
return -i;
}
int CompareByte(const void* arg1, const void* arg2)
{
if ((*((int8*)arg1)) < (*((int8*)arg2)))
{
return -1;
}
if ((*((int8*)arg1)) > (*((int8*)arg2)))
{
return 1;
}
return 0;
}
int CompareByteReverse(const void* arg1, const void* arg2)
{
if ((*((int16*)arg1)) < (*((int16*)arg2)))
{
return 1;
}
if ((*((int16*)arg1)) > (*((int16*)arg2)))
{
return -1;
}
return 0;
}
int CompareShort(const void* arg1, const void* arg2)
{
if ((*((int16*)arg1)) < (*((int16*)arg2)))
{
return -1;
}
if ((*((int16*)arg1)) > (*((int16*)arg2)))
{
return 1;
}
return 0;
}
int CompareShortReverse(const void* arg1, const void* arg2)
{
if ((*((int16*)arg1)) < (*((int16*)arg2)))
{
return 1;
}
if ((*((int16*)arg1)) > (*((int16*)arg2)))
{
return -1;
}
return 0;
}
int CompareInt(const void* arg1, const void* arg2)
{
if ((*((int*)arg1)) < (*((int*)arg2)))
{
return -1;
}
if ((*((int*)arg1)) > (*((int*)arg2)))
{
return 1;
}
return 0;
}
int CompareIntReverse(const void* arg1, const void* arg2)
{
if ((*((int*)arg1)) < (*((int*)arg2)))
{
return 1;
}
if ((*((int*)arg1)) > (*((int*)arg2)))
{
return -1;
}
return 0;
}
int CompareLong(const void* arg1, const void* arg2)
{
if ((*((int64*)arg1)) < (*((int64*)arg2)))
{
return -1;
}
if ((*((int64*)arg1)) > (*((int64*)arg2)))
{
return 1;
}
return 0;
}
int CompareLongReverse(const void* arg1, const void* arg2)
{
if ((*((int64*)arg1)) < (*((int64*)arg2)))
{
return 1;
}
if ((*((int64*)arg1)) > (*((int64*)arg2)))
{
return -1;
}
return 0;
}
uint8 GetCrumb(size iCrumb, void* pvArray)
{
size iBytePos;
size iCrumbInByte;
iBytePos = iCrumb / 4;
iCrumbInByte = iCrumb % 4;
return (((uint8*)pvArray)[iBytePos] >> (2 * iCrumbInByte)) & 0x3;
}
uint8 GetNybble(size iNybble, void* pvArray)
{
size iBytePos;
size iNybbleInByte;
iBytePos = iNybble / 2;
iNybbleInByte = iNybble % 2;
return (((uint8*)pvArray)[iBytePos] >> (4 * iNybbleInByte)) & 0xf;
}
void CopyBits(void* pvDest, size iDestOffset, void* pvSource, size iSourceOffset, size iNumBits, bool bClear)
{
size i;
bool bBit;
size iRemaining;
size iLast;
for (i = 0; i < iNumBits; i++)
{
bBit = GetBit(iSourceOffset + i, pvSource);
SetBit(iDestOffset + i, pvDest, bBit);
}
if (bClear)
{
iLast = i;
iRemaining = (8 - ((iDestOffset + iNumBits) % 8)) % 8;
for (i = 0; i < iRemaining; i++)
{
SetBit(iDestOffset + iLast + i, pvDest, 0);
}
}
}
void CopyBitsReverseHiLo(void* pvDest, size iDestOffset, void* pvSource, size iSourceOffset, size iNumBits, bool bClear)
{
size i;
bool bBit;
size iRemaining;
size iLast;
for (i = 0; i < iNumBits; i++)
{
bBit = GetBitReverseHiLo(iSourceOffset + i, pvSource);
SetBit(iDestOffset + i, pvDest, bBit);
}
if (bClear)
{
iLast = i;
iRemaining = (8 - ((iDestOffset + iNumBits) % 8)) % 8;
for (i = 0; i < iRemaining; i++)
{
SetBit(iDestOffset + iLast + i, pvDest, 0);
}
}
}
int16 ReverseShortEndianness(int16 s)
{
return (int16)ReverseShortEndianness((uint16)s);
}
int32 ReverseIntEndianness(int32 i)
{
return (int32)ReverseIntEndianness((uint32)i);
}
int64 ReverseLongEndianness(int64 i)
{
return (int64)ReverseLongEndianness((uint64)i);
}
uint16 ReverseShortEndianness(uint16 s)
{
SwapByte((uint8*)&s, ((uint8*)&s) + 1);
return s;
}
uint32 ReverseIntEndianness(uint32 i)
{
SwapByte(((uint8*)&i + 0), ((uint8*)&i) + 3);
SwapByte(((uint8*)&i + 1), ((uint8*)&i) + 2);
return i;
}
uint64 ReverseLongEndianness(uint64 i)
{
SwapByte(((uint8*)&i + 0), ((uint8*)&i) + 7);
SwapByte(((uint8*)&i + 1), ((uint8*)&i) + 6);
SwapByte(((uint8*)&i + 2), ((uint8*)&i) + 5);
SwapByte(((uint8*)&i + 3), ((uint8*)&i) + 4);
return i;
}
void ReverseEndianness(void* pv, size iSize)
{
if (iSize == 4)
{
*(uint32*)pv = ReverseIntEndianness(*(uint32*)pv);
}
if (iSize == 2)
{
*(int16*)pv = ReverseShortEndianness(*(int16*)pv);
}
if (iSize == 8)
{
*(int64*)pv = ReverseLongEndianness(*(int64*)pv);
}
}
void ReverseBytes(void* pv, size iSize)
{
size i;
size iHalf;
iHalf = iSize / 2;
for (i = 0; i < iHalf; i++)
{
SwapByte(&(((uint8*)pv)[i]), &(((uint8*)pv)[iSize - i - 1]));
}
}
size CalculateStride(size iElementSize, uint16 iAlignment)
{
int32 iByteDiff;
int32 iStride;
iByteDiff = (int)(iElementSize % iAlignment);
if (iByteDiff == 0)
{
return iElementSize;
}
else
{
iByteDiff = iAlignment - iByteDiff;
iStride = iByteDiff + (int)iElementSize;
return iStride;
}
}
uint8 CalculateOffset(int16 iOffset, uint16 iAlignment)
{
if ((iOffset == -8) && ((iAlignment == 4) || (iAlignment == 8)))
{
return 0;
}
if (iOffset < 0)
{
return (uint8)(((int32)iAlignment + ((int32)iOffset % (int32)iAlignment)) % (int32)iAlignment);
}
else
{
return (uint8)((int32)iOffset % (int32)iAlignment);
}
}
uint32 GetPowerOf2SizeDown(uint32 iInt)
{
return TruncateLowBits(iInt);
}
uint32 GetPowerOf2SizeUp(uint32 iInt)
{
return GetBestHighBit(iInt);
}
uint32 GetPowerOf2SizeAuto(uint32 iInt)
{
return TruncateLowBits((uint32)(iInt * 1.5f));
}
int32 LargestInt(int32* pInts, int32 iCount)
{
int32 iLargest;
int32 i;
iLargest = pInts[0];
for (i = 1; i < iCount; i++)
{
if (pInts[i] > iLargest)
{
iLargest = pInts[i];
}
}
return iLargest;
}
uint8 GetLowByte(uint16 uiValue)
{
return (uint8)uiValue;
}
uint8 GetHighByte(uint16 uiValue)
{
return (uint8)((uiValue & 0xFF00) >> 8);
}
uint16 SetLowByte(uint16 uiVariable, uint8 uiData)
{
return (uiVariable & 0xFF00) | uiData;
}
uint16 SetHighByte(uint16 uiVariable, uint8 uiData)
{
return (uiVariable & 0xFF) | (uiData << 8);
}
size Min(size ui1, size ui2)
{
if (ui1 < ui2)
{
return ui1;
}
else
{
return ui2;
}
}
size Max(size ui1, size ui2)
{
if (ui1 > ui2)
{
return ui1;
}
else
{
return ui2;
}
}
int8 Absolute(int8 i)
{
if (i < 0)
{
i *= -1;
}
return i;
}
int16 Absolute(int16 i)
{
if (i < 0)
{
i *= -1;
}
return i;
}
int32 Absolute(int32 i)
{
if (i < 0)
{
i *= -1;
}
return i;
}
int64 Absolute(int64 i)
{
if (i < 0)
{
i *= -1;
}
return i;
}
int16 SquareRoot(int16 i)
{
int16 iLeft = 0;
int16 iRight = i;
int16 iAns = 0;
int16 iMid;
if (i < 0)
{
return -1;
}
if (i < 2)
{
return i;
}
iLeft = 0;
iRight = i;
iAns = 0;
while (iLeft <= iRight)
{
iMid = iLeft + (iRight - iLeft) / 2;
if (iMid <= i / iMid)
{
iAns = iMid;
iLeft = iMid + 1;
}
else
{
iRight = iMid - 1;
}
}
return iAns;
}
int32 SquareRoot(int32 i)
{
int32 iLeft = 0;
int32 iRight = i;
int32 iAns = 0;
int32 iMid;
if (i < 0)
{
return -1;
}
if (i < 2)
{
return i;
}
iLeft = 0;
iRight = i;
iAns = 0;
while (iLeft <= iRight)
{
iMid = iLeft + (iRight - iLeft) / 2;
if (iMid <= i / iMid)
{
iAns = iMid;
iLeft = iMid + 1;
}
else
{
iRight = iMid - 1;
}
}
return iAns;
}
int64 SquareRoot(int64 i)
{
int64 iLeft = 0;
int64 iRight = i;
int64 iAns = 0;
int64 iMid;
if (i < 0)
{
return -1;
}
if (i < 2)
{
return i;
}
iLeft = 0;
iRight = i;
iAns = 0;
while (iLeft <= iRight)
{
iMid = iLeft + (iRight - iLeft) / 2;
if (iMid <= i / iMid)
{
iAns = iMid;
iLeft = iMid + 1;
}
else
{
iRight = iMid - 1;
}
}
return iAns;
}
