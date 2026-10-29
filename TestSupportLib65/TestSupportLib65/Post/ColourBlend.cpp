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
uint8 BlendOverByte(uint32 uiDest, uint32 uiSource);
uint8 BlendEraseByte(uint32 uiDest, uint32 uiCoverage);
uint8 BlendLerpByte(uint32 uiDest, uint32 uiSource, uint32 uiCoverage);
uint8 BlendPremultipliedByte(uint32 uiSource, uint32 uiDest, uint32 uiInverseAlpha);
void BlendStraightOverPixel(uint8* puiDest, uint8* puiSource, int iCoverage);
uint8 BlendOverByte(uint32 uiDest, uint32 uiSource)
{
return (uint8)(uiSource + DivideRound((int64)uiDest * (255 - uiSource), 255));
}
uint8 BlendEraseByte(uint32 uiDest, uint32 uiCoverage)
{
return (uint8)DivideRound((int64)uiDest * (255 - uiCoverage), 255);
}
uint8 BlendLerpByte(uint32 uiDest, uint32 uiSource, uint32 uiCoverage)
{
return (uint8)DivideRound((int64)uiDest * (255 - uiCoverage) + (int64)uiSource * uiCoverage, 255);
}
uint8 BlendPremultipliedByte(uint32 uiSource, uint32 uiDest, uint32 uiInverseAlpha)
{
uint32 uiResult;
uiResult = uiSource + (uiDest * uiInverseAlpha + 127) / 255;
if (uiResult > 255)
{
uiResult = 255;
}
return (uint8)uiResult;
}
void BlendStraightOverPixel(uint8* puiDest, uint8* puiSource, int iCoverage)
{
int64 iSourceOpacity;
int64 iDestOpacity;
int64 iOpacity;
int i;
iSourceOpacity = (int64)puiSource[0] * iCoverage;
if ((puiDest[0] == 0) || (iSourceOpacity == 65280))
{
puiDest[0] = (uint8)((iSourceOpacity + 128) / 256);
for (i = 1; i < 4; i++)
{
puiDest[i] = puiSource[i];
}
return;
}
iDestOpacity = (int64)puiDest[0] * 256;
iOpacity = iSourceOpacity * 65280 + iDestOpacity * (65280 - iSourceOpacity);
if (iOpacity == 0)
{
return;
}
for (i = 1; i < 4; i++)
{
puiDest[i] = (uint8)(((int64)puiSource[i] * iSourceOpacity * 65280 + (int64)puiDest[i] * iDestOpacity * (65280 - iSourceOpacity) + iOpacity / 2) / iOpacity);
}
puiDest[0] = (uint8)((iOpacity + 65280 * 128) / (65280 * 256));
}
