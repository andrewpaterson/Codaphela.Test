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
float32 Deg2Dot(float32 fDegrees);
float64 Deg2Dot(float64 fDegrees);
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
float32 minf(float32 f1, float32 f2)
{
if (f1 < f2)
{
return f1;
}
return f2;
}
float32 maxf(float32 f1, float32 f2)
{
if (f1 > f2)
{
return f1;
}
return f2;
}
bool FloatEqual(float32 f1, float32 f2, float32 fTolerance)
{
if ((f2 - fTolerance > f1) || (f2 + fTolerance < f1))
{
return false;
}
return true;
}
bool FloatEqual(float32 f1, float32 f2)
{
return FloatEqual(f1, f2, (1e-5f));
}
bool FloatGreaterThanOrEqual(float32 f1, float32 f2)
{
if (f2 - (1e-5f) > f1)
{
return false;
}
return true;
}
bool FloatLessThanOrEqual(float32 f1, float32 f2)
{
if (f2 + (1e-5f) < f1)
{
return false;
}
return true;
}
bool FloatGreaterThan(float32 f1, float32 f2)
{
if (f2 + (1e-5f) >= f1)
{
return false;
}
return true;
}
bool FloatLessThan(float32 f1, float32 f2)
{
if (f2 - (1e-5f) <= f1)
{
return false;
}
return true;
}
float32 TruncateFloat(float32 fInput, int32 iBinaryExponent)
{
float32 fReturn;
uint32 iTruncated;
int32 iFloatExponent;
int32 iExponentDifference;
uint32 uiFractionMask;
int32 iMaskedBits;
iFloatExponent = *((int32*)((void*)&fInput));
iFloatExponent >>= 23;
iFloatExponent &= 0xff;
iBinaryExponent += 0x7f;
iExponentDifference = iFloatExponent - iBinaryExponent;
if (iExponentDifference >= 0)
{
iMaskedBits = 22 - (iExponentDifference - 1);
if (iMaskedBits > 0)
{
uiFractionMask = 0xffffffff;
uiFractionMask >>= iMaskedBits;
uiFractionMask <<= iMaskedBits;
iTruncated = *((int32*)((void*)&fInput));
iTruncated &= uiFractionMask;
fReturn = *((float32*)((void*)&iTruncated));
return fReturn;
}
else
{
return fInput;
}
}
else
{
return 0;
}
}
float32 RoundFloat(float32 fInput, int32 iBinaryExponent)
{
float32 fValue;
int32 iAdjustedExponent;
iAdjustedExponent = iBinaryExponent - 1 + 0x7f;
iAdjustedExponent <<= 23;
fValue = *((float32*)((void*)&iAdjustedExponent));
if (((fValue < 0.0f) && (fInput > 0.0f)) || ((fValue > 0.0f) && (fInput < 0.0f)))
{
fInput -= fValue;
}
else
{
fInput += fValue;
}
return TruncateFloat(fInput, iBinaryExponent);
}
float32 NormaliseFloat(float32 fSize, float32 fPos)
{
return ((fPos*2.0f) / fSize) -1.0f;
}
float32 NormaliseFloat(float32 fMax, float32 fMin, float32 fPos)
{
if (fMax != fMin)
{
return (fPos - fMin) / (fMax - fMin);
}
else
{
if (FloatEqual(fMax, fPos))
{
return fMax;
}
return 0.0f;
}
}
float32 InterpolateFloat(float32 f1, float32 f2, float32 fPos)
{
return (f1 * fPos) + (f2 * (1.0f - fPos));
}
void InterpolateFloat(float32* fDest, float32 f1, float32 f2, float32 fPos)
{
*fDest = InterpolateFloat(f1, f2, fPos);
}
float32 Float32ToleranceForDecimals(int32 iDecimals)
{
float64 fTolerance;
fTolerance = pow(10.0, (double)iDecimals);
fTolerance = 1.0/fTolerance;
return (float32)fTolerance;
}
size FloatWholeNumbers(float32 f)
{
float32 fCmp;
size iWholes;
fCmp = 1.0f;
f = fabsf(f);
for (iWholes = 0; iWholes < 8; iWholes++)
{
if (f < fCmp)
{
return iWholes;
}
fCmp *= 10.0f;
}
return iWholes;
}
bool FloatEqual(float64 f1, float64 f2)
{
return FloatEqual(f1, f2, (float64)(1e-5f));
}
bool FloatEqual(float64 f1, float64 f2, float64 fTolerance)
{
if ((f2 - fTolerance > f1) || (f2 + fTolerance < f1))
{
return false;
}
return true;
}
bool LongDoubleEqual(float128 f1, float128 f2)
{
return LongDoubleEqual(f1, f2, (1e-5f));
}
bool LongDoubleEqual(float128 f1, float128 f2, float128 fTolerance)
{
if ((f2 - fTolerance > f1) || (f2 + fTolerance < f1))
{
return false;
}
return true;
}
bool DoubleGreaterThanOrEqual(float64 f1, float64 f2)
{
if (f2 - (1e-5f) > f1)
{
return false;
}
return true;
}
bool DoubleLessThanOrEqual(float64 f1, float64 f2)
{
if (f2 + (1e-5f) < f1)
{
return false;
}
return true;
}
bool DoubleGreaterThan(float64 f1, float64 f2)
{
if (f2 + (1e-5f) >= f1)
{
return false;
}
return true;
}
bool DoubleLessThan(float64 f1, float64 f2)
{
if (f2 - (1e-5f) <= f1)
{
return false;
}
return true;
}
float64 TruncateFloat(float64 fInput, int64 iBinaryExponent)
{
float64 fReturn;
uint64 iTruncated;
int64 iDoubleExponent;
int64 iExponentDifference;
uint64 uiFractionMask;
int64 iMaskedBits;
iDoubleExponent = *((int64*)((void*)&fInput));
iDoubleExponent >>= 52;
iDoubleExponent &= 0xfffLL;
iBinaryExponent += 0x3ffLL;
iExponentDifference = iDoubleExponent - iBinaryExponent;
if (iExponentDifference >= 0)
{
iMaskedBits = 51 - (iExponentDifference - 1);
if (iMaskedBits > 0)
{
uiFractionMask = 0xffffffffffffffffLL;
uiFractionMask >>= iMaskedBits;
uiFractionMask <<= iMaskedBits;
iTruncated = *((int64*)((void*)&fInput));
iTruncated &= uiFractionMask;
fReturn = *((float64*)((void*)&iTruncated));
return fReturn;
}
else
{
return fInput;
}
}
else
{
return 0;
}
}
float64 RoundFloat(float64 fInput, int64 iBinaryExponent)
{
float64 fValue;
int64 iAdjustedExponent;
iAdjustedExponent = iBinaryExponent - 1 + 0x3ff;
iAdjustedExponent <<= 52;
fValue = *((float64*)((void*)&iAdjustedExponent));
if (((fValue < 0.0f) && (fInput > 0.0f)) || ((fValue > 0.0f) && (fInput < 0.0f)))
{
fInput -= fValue;
}
else
{
fInput += fValue;
}
return TruncateFloat(fInput, iBinaryExponent);
}
float64 NormaliseDouble(float64 fSize, float64 fPos)
{
return ((fPos * 2.0f) / fSize) - 1.0f;
}
float64 NormaliseDouble(float64 fMax, float64 fMin, float64 fPos)
{
if (fMax != fMin)
{
return (fPos - fMin) / (fMax - fMin);
}
else
{
if (FloatEqual(fMax, fPos))
{
return fMax;
}
return 0.0f;
}
}
float64 InterpolateDouble(float64 f1, float64 f2, float64 fPos)
{
return (f1 * fPos) + (f2 * (1.0f - fPos));
}
void InterpolateDouble(float64* fDest, float64 f1, float64 f2, float64 fPos)
{
*fDest = InterpolateDouble(f1, f2, fPos);
}
float64 Float64ToleranceForDecimals(int32 iDecimals)
{
float128 fTolerance;
fTolerance = powl(10.0, (float128)iDecimals);
fTolerance = 1.0f/fTolerance;
return fTolerance;
}
size FloatWholeNumbers(float64 f)
{
float64 fCmp;
size iWholes;
fCmp = 1.0f;
f = fabs(f);
for (iWholes = 0; iWholes < 8; iWholes++)
{
if (f < fCmp)
{
return iWholes;
}
fCmp *= 10.0f;
}
return iWholes;
}
void SwapFloat(float32* f1, float32* f2)
{
float32 temp;
temp = *f2;
*f2 = *f1;
*f1 = temp;
}
float32 Float32NotANumber(void)
{
uint32 i = 0xffffffff;
float32 f = *((float32*)((void*)&i));
return f;
}
float64 Float64NotANumber(void)
{
uint64 i = 0xffffffffffffffffLL;
float64 f = *((float64*)((void*)&i));
return f;
}
bool IsNotANumber(float32* pf)
{
return *((uint32*)((void*)pf)) == 0xffffffff;
}
float128 ConvertDecimalFixedPointToLongDouble(uint64 ulliWholeNumber, uint64 ulliDecimalNumber, uint16 iNumDecimalDigits, int64 lliExponentNumber)
{
float128 ldf;
float128 ldfPow;
float128 ldfExp;
ldf = (float128)ulliWholeNumber;
ldfPow = 1.l / powl(10, iNumDecimalDigits);
ldf += ulliDecimalNumber * ldfPow;
if (lliExponentNumber > 0)
{
ldfExp = powl(10, (float128)lliExponentNumber);
ldf *= ldfExp;
}
else if (lliExponentNumber < 0)
{
ldfExp = 1.l / powl(10, -((float128)lliExponentNumber));
ldf *= ldfExp;
}
return ldf;
}
float32 det3x3(float32 a1, float32 a2, float32 a3, float32 b1, float32 b2, float32 b3, float32 c1, float32 c2, float32 c3)
{
float32 ans;
ans = a1 * det2x2(b2, b3, c2, c3)
- b1 * det2x2(a2, a3, c2, c3)
+ c1 * det2x2(a2, a3, b2, b3);
return ans;
}
float32 det2x2(float32 a, float32 b, float32 c, float32 d)
{
float32 ans;
ans = a * d - b * c;
return ans;
}
float64 det3x3(float64 a1, float64 a2, float64 a3, float64 b1, float64 b2, float64 b3, float64 c1, float64 c2, float64 c3)
{
float64 ans;
ans = a1 * det2x2(b2, b3, c2, c3)
- b1 * det2x2(a2, a3, c2, c3)
+ c1 * det2x2(a2, a3, b2, b3);
return ans;
}
float64 det2x2(float64 a, float64 b, float64 c, float64 d)
{
float64 ans;
ans = a * d - b * c;
return ans;
}
float32 SquareRoot(float32 f)
{
return sqrtf(f);
}
float64 SquareRoot(float64 f)
{
return sqrt(f);
}
float128 SquareRoot(float128 f)
{
return sqrtl(f);
}
float32 Square(float32 f)
{
return f*f;
}
float64 Square(float64 f)
{
return f*f;
}
float128 Square(float128 f)
{
return f*f;
}
float32 gf32Nan = Float32NotANumber();
float64 gf64Nan = Float64NotANumber();
void CosSinDegrees(float64 fDegrees, float64* pfCos, float64* pfSin)
{
float64 fQuarters;
float64 fRadians;
fQuarters = fDegrees / 90.0;
if (fQuarters == floor(fQuarters))
{
switch (((int64)fQuarters % 4 + 4) % 4)
{
case 0:
*pfCos = 1;
*pfSin = 0;
return;
case 1:
*pfCos = 0;
*pfSin = 1;
return;
case 2:
*pfCos = -1;
*pfSin = 0;
return;
default:
*pfCos = 0;
*pfSin = -1;
return;
}
}
fRadians = fDegrees * 3.14159265358979323846 / 180.0;
*pfCos = cos(fRadians);
*pfSin = sin(fRadians);
}
