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
uint8 BlendOverByte(uint32 uiDest, uint32 uiSource);
uint8 BlendEraseByte(uint32 uiDest, uint32 uiCoverage);
uint8 BlendLerpByte(uint32 uiDest, uint32 uiSource, uint32 uiCoverage);
uint8 BlendPremultipliedByte(uint32 uiSource, uint32 uiDest, uint32 uiInverseAlpha);
void BlendStraightOverPixel(uint8* puiDest, uint8* puiSource, int iCoverage);
typedef uint32 ARGB32;
uint8 Get8BitAlphaColour(ARGB32 uiColour);
uint8 Get8BitBlueColour(ARGB32 uiColour);
uint8 Get8BitGreenColour(ARGB32 uiColour);
uint8 Get8BitRedColour(ARGB32 uiColour);
uint8 Clamp8BitColour(uint32 uiColour);
ARGB32 Set8BitAlphaColour(uint32 iAlpha);
ARGB32 Set8BitBlueColour(uint32 iBlue);
ARGB32 Set8BitGreenColour(uint32 iGreen);
ARGB32 Set8BitRedColour(uint32 iRed);
ARGB32 Set8BitAlphaColour(uint8 iAlpha);
ARGB32 Set8BitBlueColour(uint8 iBlue);
ARGB32 Set8BitGreenColour(uint8 iGreen);
ARGB32 Set8BitRedColour(uint8 iRed);
float32 Convert8BitColourToFloat(ARGB32 uiColour);
uint8 ConvertFloatTo8BitColour(float32 fColour);
ARGB32 Set32BitColour(uint32 r, uint32 g, uint32 b, uint32 a);
ARGB32 Set32BitColour(uint8 r, uint8 g, uint8 b, uint8 a);
ARGB32 Set32BitColour(float32 r, float32 g, float32 b, float32 a);
ARGB32 Set32BitColour(uint32 r, uint32 g, uint32 b);
ARGB32 Set32BitColour(uint8 r, uint8 g, uint8 b);
ARGB32 Set32BitColour(float32 r, float32 g, float32 b);
void Get32BitColour(uint32* r, uint32* g, uint32* b, uint32* a, ARGB32 uiColour);
void Get32BitColour(float32* r, float32* g, float32* b, float32* a, ARGB32 uiColour);
void Get32BitColour(float32* r, float32* g, float32* b, ARGB32 uiColour);
ARGB32 Add32BitColours(ARGB32 uiColour1, ARGB32 uiColour2);
ARGB32 Subtract32BitColours(ARGB32 uiColour1, ARGB32 uiColour2);
ARGB32 Minimum32BitColour(ARGB32 uiColour1, ARGB32 uiColour2);
ARGB32 Maximum32BitColour(ARGB32 uiColour1, ARGB32 uiColour2);
ARGB32 Modulate32BitColours(ARGB32 uiColour1, ARGB32 uiColour2);
ARGB32 Weight32BitColours(ARGB32 uiColour1, ARGB32 uiColour2, float32 fWeight1);
ARGB32 BlendAlpha32BitColours(ARGB32 uiColour1, ARGB32 uiColour2);
uint8 GetM8BitAlphaColour(ARGB32 uiColour);
uint8 GetM8BitBlueColour(ARGB32 uiColour);
uint8 GetM8BitGreenColour(ARGB32 uiColour);
uint8 GetM8BitRedColour(ARGB32 uiColour);
ARGB32 SetM32BitColour(uint8 r, uint8 g, uint8 b, uint8 a);
ARGB32 SetM8BitAlphaColour(uint8 iAlpha);
ARGB32 SetM8BitBlueColour(uint8 iBlue);
ARGB32 SetM8BitGreenColour(uint8 iGreen);
ARGB32 SetM8BitRedColour(uint8 iRed);
uint32 ConvertToBGR(ARGB32 uiColour);
uint32 ConvertToBGRA(ARGB32 uiColour);
uint8 Get8BitAlphaColour(ARGB32 uiColour)
{
return (uiColour >> 24) & 0xff;
}
uint8 Get8BitBlueColour(ARGB32 uiColour)
{
return (uiColour >> 16) & 0xff;
}
uint8 Get8BitGreenColour(ARGB32 uiColour)
{
return (uiColour >> 8) & 0xff;
}
uint8 Get8BitRedColour(ARGB32 uiColour)
{
return (uiColour >> 0) & 0xff;
}
uint8 Clamp8BitColour(uint32 uiColour)
{
if (uiColour > 0xff)
{
return 0xff;
}
return uiColour;
}
ARGB32 Set8BitAlphaColour(uint32 iAlpha)
{
iAlpha = Clamp8BitColour(iAlpha);
return iAlpha << 24;
}
ARGB32 Set8BitBlueColour(uint32 iBlue)
{
iBlue = Clamp8BitColour(iBlue);
return iBlue << 16;
}
ARGB32 Set8BitGreenColour(uint32 iGreen)
{
iGreen = Clamp8BitColour(iGreen);
return iGreen << 8;
}
ARGB32 Set8BitRedColour(uint32 iRed)
{
iRed = Clamp8BitColour(iRed);
return iRed << 0;
}
ARGB32 Set8BitAlphaColour(uint8 iAlpha)
{
return iAlpha << 24;
}
ARGB32 Set8BitBlueColour(uint8 iBlue)
{
return iBlue << 16;
}
ARGB32 Set8BitGreenColour(uint8 iGreen)
{
return iGreen << 8;
}
ARGB32 Set8BitRedColour(uint8 iRed)
{
return iRed << 0;
}
float32 Convert8BitColourToFloat(ARGB32 uiColour)
{
return (float32)uiColour / 255.0f;
}
uint8 ConvertFloatTo8BitColour(float32 fColour)
{
return ((uint8)(fColour * 255.0f));
}
ARGB32 Set32BitColour(uint32 r, uint32 g, uint32 b, uint32 a)
{
ARGB32 uiColour;
uiColour = Set8BitRedColour(r);
uiColour |= Set8BitGreenColour(g);
uiColour |= Set8BitBlueColour(b);
uiColour |= Set8BitAlphaColour(a);
return uiColour;
}
ARGB32 Set32BitColour(uint8 r, uint8 g, uint8 b, uint8 a)
{
ARGB32 uiColour;
uiColour = Set8BitRedColour(r);
uiColour |= Set8BitGreenColour(g);
uiColour |= Set8BitBlueColour(b);
uiColour |= Set8BitAlphaColour(a);
return uiColour;
}
void Get32BitColour(uint32* r, uint32* g, uint32* b, uint32* a, ARGB32 uiColour)
{
*r = Get8BitRedColour(uiColour);
*g = Get8BitGreenColour(uiColour);
*b = Get8BitBlueColour(uiColour);
*a = Get8BitAlphaColour(uiColour);
}
void Get32BitColour(float32* r, float32* g, float32* b, float32* a, ARGB32 uiColour)
{
*r = Convert8BitColourToFloat(Get8BitRedColour(uiColour));
*g = Convert8BitColourToFloat(Get8BitGreenColour(uiColour));
*b = Convert8BitColourToFloat(Get8BitBlueColour(uiColour));
*a = Convert8BitColourToFloat(Get8BitAlphaColour(uiColour));
}
void Get32BitColour(float32* r, float32* g, float32* b, ARGB32 uiColour)
{
*r = Convert8BitColourToFloat(Get8BitRedColour(uiColour));
*g = Convert8BitColourToFloat(Get8BitGreenColour(uiColour));
*b = Convert8BitColourToFloat(Get8BitBlueColour(uiColour));
}
ARGB32 Add32BitColours(ARGB32 uiColour1, ARGB32 uiColour2)
{
uint32 r1, g1, b1, a1;
uint32 r2, g2, b2, a2;
Get32BitColour(&r1, &g1, &b1, &a1, uiColour1);
Get32BitColour(&r2, &g2, &b2, &a2, uiColour2);
r1 += r2;
g1 += g2;
b1 += b2;
a1 += a2;
return Set32BitColour(r1, g1, b1, a1);
}
ARGB32 Subtract32BitColours(ARGB32 uiColour1, ARGB32 uiColour2)
{
uint32 r1, g1, b1, a1;
uint32 r2, g2, b2, a2;
Get32BitColour(&r1, &g1, &b1, &a1, uiColour1);
Get32BitColour(&r2, &g2, &b2, &a2, uiColour2);
r1 -= r2;
g1 -= g2;
b1 -= b2;
a1 -= a2;
return Set32BitColour(r1, g1, b1, a1);
}
ARGB32 Minimum32BitColour(ARGB32 uiColour1, ARGB32 uiColour2)
{
uint32 r1, g1, b1, a1;
uint32 r2, g2, b2, a2;
Get32BitColour(&r1, &g1, &b1, &a1, uiColour1);
Get32BitColour(&r2, &g2, &b2, &a2, uiColour2);
if (r1 > r2) r1 = r2;
if (g1 > g2) g1 = g2;
if (b1 > b2) b1 = b2;
if (a1 > a2) a1 = a2;
return Set32BitColour(r1, g1, b1, a1);
}
ARGB32 Maximum32BitColour(ARGB32 uiColour1, ARGB32 uiColour2)
{
uint32 r1, g1, b1, a1;
uint32 r2, g2, b2, a2;
Get32BitColour(&r1, &g1, &b1, &a1, uiColour1);
Get32BitColour(&r2, &g2, &b2, &a2, uiColour2);
if (r1 < r2) r1 = r2;
if (g1 < g2) g1 = g2;
if (b1 < b2) b1 = b2;
if (a1 < a2) a1 = a2;
return Set32BitColour(r1, g1, b1, a1);
}
ARGB32 Modulate32BitColours(ARGB32 uiColour1, ARGB32 uiColour2)
{
uint32 r1, g1, b1, a1;
uint32 r2, g2, b2, a2;
Get32BitColour(&r1, &g1, &b1, &a1, uiColour1);
Get32BitColour(&r2, &g2, &b2, &a2, uiColour2);
r1 = (r1 * r2) / 255;
g1 = (g1 * g2) / 255;
b1 = (b1 * b2) / 255;
a1 = (a1 * a2) / 255;
return Set32BitColour(r1, g1, b1, a1);
}
ARGB32 Weight32BitColours(ARGB32 uiColour1, ARGB32 uiColour2, float32 fWeight1)
{
uint32 r1, g1, b1, a1;
uint32 r2, g2, b2, a2;
Get32BitColour(&r1, &g1, &b1, &a1, uiColour1);
Get32BitColour(&r2, &g2, &b2, &a2, uiColour2);
r1 = (uint32)(r1 * fWeight1 + r2 * (1.0f - fWeight1));
g1 = (uint32)(g1 * fWeight1 + g2 * (1.0f - fWeight1));
b1 = (uint32)(b1 * fWeight1 + b2 * (1.0f - fWeight1));
a1 = (uint32)(a1 * fWeight1 + a2 * (1.0f - fWeight1));
return Set32BitColour(r1, g1, b1, a1);
}
ARGB32 BlendAlpha32BitColours(ARGB32 uiColour1, ARGB32 uiColour2)
{
uint32 r1, g1, b1, a1;
uint32 r2, g2, b2, a2;
uint8 auiSource[4];
uint8 auiDest[4];
Get32BitColour(&r1, &g1, &b1, &a1, uiColour1);
Get32BitColour(&r2, &g2, &b2, &a2, uiColour2);
auiSource[0] = (uint8)a1;
auiSource[1] = (uint8)r1;
auiSource[2] = (uint8)g1;
auiSource[3] = (uint8)b1;
auiDest[0] = (uint8)a2;
auiDest[1] = (uint8)r2;
auiDest[2] = (uint8)g2;
auiDest[3] = (uint8)b2;
BlendStraightOverPixel(auiDest, auiSource, 256);
return Set32BitColour((uint32)auiDest[1], (uint32)auiDest[2], (uint32)auiDest[3], (uint32)auiDest[0]);
}
ARGB32 Set32BitColour(float32 r, float32 g, float32 b, float32 a)
{
uint8 ri, gi, bi, ai;
ri = ConvertFloatTo8BitColour(r);
gi = ConvertFloatTo8BitColour(g);
bi = ConvertFloatTo8BitColour(b);
ai = ConvertFloatTo8BitColour(a);
return Set32BitColour(ri, gi, bi, ai);
}
ARGB32 Set32BitColour(uint32 r, uint32 g, uint32 b)
{
ARGB32 uiColour;
uiColour = Set8BitRedColour(r);
uiColour |= Set8BitGreenColour(g);
uiColour |= Set8BitBlueColour(b);
uiColour |= 255 << 24;
return uiColour;
}
ARGB32 Set32BitColour(uint8 r, uint8 g, uint8 b)
{
ARGB32 uiColour;
uiColour = Set8BitRedColour(r);
uiColour |= Set8BitGreenColour(g);
uiColour |= Set8BitBlueColour(b);
uiColour |= 255 << 24;
return uiColour;
}
ARGB32 Set32BitColour(float32 r, float32 g, float32 b)
{
uint8 ri, gi, bi;
ri = ConvertFloatTo8BitColour(r);
gi = ConvertFloatTo8BitColour(g);
bi = ConvertFloatTo8BitColour(b);
return Set32BitColour(ri, gi, bi);
}
uint32 ConvertToBGR(ARGB32 uiColour)
{
SwapByte(&(((uint8*)(&uiColour))[0]), &(((uint8*)(&uiColour))[2]));
return uiColour;
}
uint32 ConvertToBGRA(ARGB32 uiColour)
{
SwapByte(&(((uint8*)(&uiColour))[0]), &(((uint8*)(&uiColour))[2]));
return uiColour;
}
uint8 GetM8BitAlphaColour(ARGB32 uiColour)
{
return (uiColour >> 24) & 0xff;
}
uint8 GetM8BitBlueColour(ARGB32 uiColour)
{
return (uiColour >> 0) & 0xff;
}
uint8 GetM8BitGreenColour(ARGB32 uiColour)
{
return (uiColour >> 8) & 0xff;
}
uint8 GetM8BitRedColour(ARGB32 uiColour)
{
return (uiColour >> 16) & 0xff;
}
ARGB32 SetM8BitAlphaColour(uint8 iAlpha)
{
return iAlpha << 24;
}
ARGB32 SetM8BitBlueColour(uint8 iBlue)
{
return iBlue << 0;
}
ARGB32 SetM8BitGreenColour(uint8 iGreen)
{
return iGreen << 8;
}
ARGB32 SetM8BitRedColour(uint8 iRed)
{
return iRed << 16;
}
ARGB32 SetM32BitColour(uint8 r, uint8 g, uint8 b, uint8 a)
{
ARGB32 uiColour;
uiColour = SetM8BitRedColour(r);
uiColour |= SetM8BitGreenColour(g);
uiColour |= SetM8BitBlueColour(b);
uiColour |= SetM8BitAlphaColour(a);
return uiColour;
}
