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
char GetEscapeCode(char cCurrent);
char* GetEscapeString(char cCurrent, char* szDest);
char* GetEscapeString(uint8 cCurrent, char* szDest);
char* GetEscapeString(char16 cCurrent, char* szDest);
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
char gszDigits[17] = { "0123456789abcdef" };
char gszEmptyString[4] = { '\0', '\0', '\0', '\0' };
int StringCompare(const char* ps1, const char* ps2)
{
int s1;
int s2;
if ((ps1 == 0L) && (ps2 == 0L))
{
return 0;
}
if (ps1 == 0L)
{
return -1;
}
if (ps2 == 0L)
{
return 1;
}
do
{
s1 = *ps1++;
s2 = *ps2++;
if (s1 == 0)
break;
}
while (s1 == s2);
return (s1 < s2) ? -1 : (s1 > s2);
}
int StringInsensitiveCompare(const char* ps1, const char* ps2)
{
int s1;
int s2;
if ((ps1 == 0L) && (ps2 == 0L))
{
return 0;
}
if (ps1 == 0L)
{
return -1;
}
if (ps2 == 0L)
{
return 1;
}
do
{
s1 = *ps1++;
s2 = *ps2++;
if (s1 == 0)
break;
s1 = ToLower(s1);
s2 = ToLower(s2);
}
while (s1 == s2);
return (s1 < s2) ? -1 : (s1 > s2);
}
int MemICmp(const void* pv1, const void* pv2, size iLength)
{
size i;
uint8 c1;
uint8 c2;
if ((pv1 == 0L) && (pv2 == 0L))
{
return 0;
}
if (pv1 == 0L)
{
return -1;
}
if (pv2 == 0L)
{
return 1;
}
if (iLength == 0)
{
return 0;
}
for (i = 0; i < iLength; i++)
{
c1 = (uint8)ToLower(((char*)pv1)[i]);
c2 = (uint8)ToLower(((char*)pv2)[i]);
if (c1 != c2)
{
return (c1 < c2) ? -1 : 1;
}
}
return 0;
}
int MemCmp(const void* pv1, size iLen1, const void* pv2, size iLen2)
{
size iSize;
int iResult;
iSize = iLen1;
if (iSize == iLen2)
{
iResult = memcmp(pv1, pv2, iSize);
}
else if (iSize < iLen2)
{
iResult = memcmp(pv1, pv2, iSize);
if (iResult == 0)
{
iResult = -1;
}
}
else
{
iSize = iLen2;
iResult = memcmp(pv1, pv2, iSize);
if (iResult == 0)
{
iResult = 1;
}
}
if (iResult < -1)
{
iResult = -1;
}
else if (iResult > 1)
{
iResult = 1;
}
return iResult;
}
void MemSwp(const void* pv1, const void* pv2, size uiLength)
{
size i;
size iIntLength;
int iTemp;
size iRemainder;
char cTemp;
size iCharIndex;
iIntLength = uiLength / sizeof(int);
iRemainder = uiLength % sizeof(int);
for (i = 0; i < iIntLength; i++)
{
iTemp = ((int*)pv1)[i];
((int*)pv1)[i] = ((int*)pv2)[i];
((int*)pv2)[i] = iTemp;
}
iCharIndex = iIntLength * sizeof(int);
for (i = 0; i < iRemainder; i++)
{
cTemp = ((char*)pv1)[iCharIndex + i];
((char*)pv1)[iCharIndex + i] = ((char*)pv2)[iCharIndex + i];
((char*)pv2)[iCharIndex + i] = cTemp;
}
}
char* ByteToString(char* szDest, size iDestLength, int8 iValue, uint16 iBase)
{
return ShortToString(szDest, iDestLength, (int16)iValue, iBase);
}
char* ByteToString(char* szDest, size iDestLength, uint8 iValue, uint16 iBase)
{
return ShortToString(szDest, iDestLength, (uint16)iValue, iBase);
}
char* ShortToString(char* szDest, size iDestLength, int16 iValue, uint16 iBase)
{
int16 iQuotient;
uint16 iDigit;
size iPos;
bool bNegative;
if (iBase != 10)
{
return ShortToString(szDest, iDestLength, (uint16)iValue, iBase);
}
bNegative = iValue < 0;
if (bNegative)
{
if (iValue == (int16)0x8000)
{
StrCpySafe(szDest, "-32768", iDestLength);
return szDest;
}
iValue *= -1;
}
iQuotient = iValue;
iPos = 0;
do
{
iDigit = iQuotient % iBase;
iQuotient /= iBase;
szDest[iPos] = gszDigits[iDigit];
iPos++;
}
while (iQuotient != 0);
if (bNegative)
{
szDest[iPos] = '-';
iPos++;
}
szDest[iPos] = '\0';
StrRev(szDest, iPos);
return szDest;
}
char* ShortToString(char* szDest, size iDestLength, uint16 iValue, uint16 iBase)
{
uint16 iQuotient;
uint16 iDigit;
size iPos;
if (iBase < 2 || iBase > 16)
{
szDest[0] = 0;
return szDest;
}
iQuotient = iValue;
iPos = 0;
do
{
iDigit = iQuotient % iBase;
iQuotient /= iBase;
szDest[iPos] = gszDigits[iDigit];
iPos++;
}
while (iQuotient != 0);
szDest[iPos] = '\0';
StrRev(szDest, iPos);
return szDest;
}
char* IntToString(char* szDest, size iDestLength, int32 iValue, uint16 iBase)
{
int32 iQuotient;
uint16 iDigit;
size iPos;
bool bNegative;
if (iBase != 10)
{
return IntToString(szDest, iDestLength, (uint32)iValue, iBase);
}
bNegative = iValue < 0;
if (bNegative)
{
if (iValue == (int32)0x80000000)
{
StrCpySafe(szDest, "-2147483648", iDestLength);
return szDest;
}
iValue *= -1;
}
iQuotient = iValue;
iPos = 0;
do
{
iDigit = iQuotient % iBase;
iQuotient /= iBase;
szDest[iPos] = gszDigits[iDigit];
iPos++;
}
while (iQuotient != 0);
if (bNegative)
{
szDest[iPos] = '-';
iPos++;
}
szDest[iPos] = '\0';
StrRev(szDest, iPos);
return szDest;
}
char* IntToString(char* szDest, size iDestLength, uint32 iValue, uint16 iBase)
{
uint32 iQuotient;
uint16 iDigit;
size iPos;
if (iBase < 2 || iBase > 16)
{
szDest[0] = 0;
return szDest;
}
iQuotient = iValue;
iPos = 0;
do
{
iDigit = iQuotient % iBase;
iQuotient /= iBase;
szDest[iPos] = gszDigits[iDigit];
iPos++;
}
while (iQuotient != 0);
szDest[iPos] = '\0';
StrRev(szDest, iPos);
return szDest;
}
char* SizeToString(char* szDest, size iDestLength, size iValue, uint16 iBase)
{
if (sizeof(size) == 2)
{
return ShortToString(szDest, iDestLength, (uint16)iValue, iBase);
}
else if (sizeof(size) == 4)
{
return IntToString(szDest, iDestLength, (uint32)iValue, iBase);
}
else if (sizeof(size) == 8)
{
return LongToString(szDest, iDestLength, (uint64)iValue, iBase);
}
return 0L;
}
char* LongToString(char* szDest, size iDestLength, uint64 ulliValue, uint16 iBase)
{
uint64 ulliQuotient;
uint16 iDigit;
size iPos;
if (iBase < 2 || iBase > 16)
{
szDest[0] = 0;
return szDest;
}
ulliQuotient = ulliValue;
iPos = 0;
do
{
iDigit = (uint32)(ulliQuotient % iBase);
ulliQuotient /= iBase;
szDest[iPos] = gszDigits[iDigit];
iPos++;
}
while (ulliQuotient != 0);
szDest[iPos] = '\0';
StrRev(szDest, iPos);
return szDest;
}
char* LongToString(char* szDest, size iDestLength, int64 lliValue, uint16 iBase)
{
int64 lliQuotient;
uint16 iDigit;
size iPos;
bool bNegative;
if (iBase != 10)
{
return LongToString(szDest, iDestLength, (uint64)lliValue, iBase);
}
bNegative = lliValue < 0;
if (bNegative && (iBase == 10))
{
if (lliValue == (int64)0x8000000000000000LL)
{
StrCpySafe(szDest, "-9223372036854775808", iDestLength);
return szDest;
}
lliValue *= -1;
}
lliQuotient = lliValue;
iPos = 0;
do
{
iDigit = (int)(lliQuotient % iBase);
lliQuotient /= iBase;
szDest[iPos] = gszDigits[iDigit];
iPos++;
}
while (lliQuotient != 0);
if (bNegative && (iBase == 10))
{
szDest[iPos] = '-';
iPos++;
}
szDest[iPos] = '\0';
StrRev(szDest, iPos);
return szDest;
}
char* StrRev(char* szString, size iLength)
{
size i;
size j;
char c;
if (iLength <= 1)
{
return szString;
}
for (i = 0, j = iLength - 1; i < iLength / 2; i++, j--)
{
c = szString[j];
szString[j] = szString[i];
szString[i] = c;
}
return szString;
}
char* StrRev(char* szString)
{
size iLength;
iLength = strlen(szString);
return StrRev(szString, iLength);
}
char* StrIStr(char* ps1, const char* ps2)
{
size iS1Len;
size iS2Len;
size iSearchCount;
size i;
if ((ps1 == 0L) || (ps2 == 0L))
{
return 0L;
}
iS1Len = strlen(ps1);
iS2Len = strlen(ps2);
if ((iS1Len == 0) || (iS2Len == 0))
{
return 0L;
}
if (iS2Len > iS1Len)
{
return 0L;
}
iSearchCount = iS1Len - iS2Len;
for (i = 0; i <= iSearchCount; i++)
{
if (MemICmp(ps2, &ps1[i], iS2Len) == 0)
{
return &ps1[i];
}
}
return 0L;
}
const char* FindChar(const char* szString, char c, bool bReverse)
{
size iLen;
size i;
if (szString)
{
iLen = strlen(szString);
if (bReverse)
{
if (iLen == 0)
{
return 0L;
}
i = iLen;
do
{
i--;
if (szString[i] == c)
{
return &szString[i];
}
}
while (i != 0);
}
else
{
for (i = 0; i < iLen; i++)
{
if (szString[i] == c)
{
return &szString[i];
}
}
}
}
return 0L;
}
size FindCharIndex(char chr, const char* str, size index)
{
size i;
i = 0;
str = &str[index];
while (str[i] != '\0')
{
if (str[i] == chr)
{
return i;
}
i++;
}
return ((size)-1);
}
void StrCpySafeStripSurroundingSpaces(char* szDest, char* szSource, size uiMaxLength)
{
size uiSourceLength;
size uiLeadSpaces;
size uiLastChar;
size i;
char* szFirstCharOfDest;
uiLeadSpaces = 0;
uiLastChar = 0;
szFirstCharOfDest = szDest;
uiSourceLength = strlen(szSource);
for (i = 0; i < uiSourceLength && szSource[i] == ' '; i++)
{
uiLeadSpaces++;
}
if (uiSourceLength == uiLeadSpaces)
{
*szDest = '\0';
return;
}
uiLastChar = uiSourceLength;
do uiLastChar--;
while (uiLastChar != 0 && (szSource[uiLastChar] == ' '));
for (i = uiLeadSpaces; i <= uiLastChar; i++)
{
*szDest++ = szSource[i];
if (!uiMaxLength--)
{
*szFirstCharOfDest = '\0';
return;
}
}
*szDest = '\0';
}
char* StrCpySafe(char* szDest, const char* szSource, size iDestLength, size* piSourceLength)
{
size iLen;
iLen = strlen(szSource);
if (piSourceLength) { *piSourceLength = iLen; };
if (iDestLength == 0)
{
return szDest;
}
if (iLen >= iDestLength)
{
iLen = iDestLength-1;
}
memcpy(szDest, szSource, iLen);
szDest[iLen] = 0;
return szDest;
}
char* StrCatSafe(char* szDest, const char* szSource, size iDestLength, size* piSourceLength)
{
size iLen;
char* pcEnd;
size iDestLen;
size iRemaining;
iLen = strlen(szSource);
if (piSourceLength) { *piSourceLength = iLen; };
if (iDestLength == 0)
{
return szDest;
}
pcEnd = (char*)memchr(szDest, 0, iDestLength);
if (pcEnd == 0L)
{
szDest[iDestLength - 1] = 0;
return szDest;
}
iDestLen = pcEnd - szDest;
iRemaining = iDestLength - iDestLen;
if (iLen >= iRemaining)
{
iLen = iRemaining - 1;
}
memcpy(pcEnd, szSource, iLen);
pcEnd[iLen] = 0;
return szDest;
}
char* ToLower(char* szString)
{
size iLen;
size i;
char c;
if (szString)
{
iLen = strlen(szString);
for (i = 0; i < iLen; i++)
{
c = szString[i];
if ((c >= 'A') && (c <= 'Z'))
{
szString[i] = c + 'a' - 'A';
}
}
}
return szString;
}
char* ToUpper(char* szString)
{
size iLen;
size i;
char c;
if (szString)
{
iLen = strlen(szString);
for (i = 0; i < iLen; i++)
{
c = szString[i];
if ((c >= 'a') && (c <= 'z'))
{
szString[i] = c + 'A' - 'a';
}
}
}
return szString;
}
char ToLower(char c)
{
if ((c >= 'A') && (c <= 'Z'))
{
return c + 'a' - 'A';
}
return c;
}
char ToUpper(char c)
{
if ((c >= 'a') && (c <= 'z'))
{
return c + 'A' - 'a';
}
return c;
}
size StrPrintable(const char* szString)
{
size i;
uint8 c;
size iPrintable;
if (StrEmpty(szString))
{
return 0;
}
iPrintable = 0;
for (i = 0; ; i++)
{
c = szString[i];
if ((c >= 32) && (c <= 126))
{
iPrintable++;
}
else if (c == '\0')
{
break;
}
}
return iPrintable;
}
size StrPrintable(const char* szString, size iLength)
{
size i;
uint8 c;
size iPrintable;
iPrintable = 0;
for (i = 0; i < iLength; i++)
{
c = szString[i];
if ((c >= 32) && (c <= 126))
{
iPrintable++;
}
}
return iPrintable;
}
size StrLen(const char* szString)
{
return strlen(szString);
}
size StrLen(const char* szString, const char* szLastCharInclusive)
{
if (szLastCharInclusive)
{
if (szLastCharInclusive < szString)
{
return 0;
}
return szLastCharInclusive - szString + 1;
}
else
{
return strlen(szString);
}
}
bool StrEmpty(const char* szString)
{
if (szString)
{
return *szString == 0;
}
else
{
return true;
}
}
char* NullToEmpty(const char* szString)
{
if (szString == 0L)
{
return gszEmptyString;
}
else
{
return (char*)szString;
}
}
char* StrCpy(char* szDest, const char* szString, const char* szLastCharInclusive)
{
size uiLength;
uiLength = StrLen(szString, szLastCharInclusive);
memcpy(szDest, szString, uiLength);
szDest[uiLength] = '\0';
return szDest;
}
char GetHexChar(size c4Bit)
{
if (c4Bit < 10)
{
return '0' + (char)c4Bit;
}
else if (c4Bit < 16)
{
return 'a' + (char)c4Bit - 10;
}
else
{
return '?';
}
}
size GetCharHex(char cHexChar)
{
if (cHexChar >= '0' && cHexChar <= '9')
{
return cHexChar - '0';
}
else if (cHexChar >= 'a' && cHexChar <= 'f')
{
return cHexChar - 'a' + 10;
}
else
{
return 0xffffffffU;
}
}
char* FlagsToString(char* szDest, size iDestLength, uint8* pvMem, size iByteCount)
{
size iIndex;
uint8 iBit;
size i;
size iByte;
size iBitIndex;
uint8 iBitMask;
bool bAppendedSpace;
if ((iDestLength == 0) || (iByteCount > 16))
{
return szDest;
}
iIndex = 0;
iByte = iByteCount-1;
iBitIndex = 0;
iBitMask = 0x80;
for (i = 0; i < iDestLength; i++)
{
iBit = iBitMask & pvMem[iByte];
if (iBit)
{
szDest[iIndex] = '1';
iIndex++; if (iIndex == iDestLength) { break; };
}
else
{
szDest[iIndex] = '0';
iIndex++; if (iIndex == iDestLength) { break; };
}
iBitIndex++;
iBitMask >>= 1;
bAppendedSpace = false;
if (iBitIndex == 8)
{
iBitMask = 0x80;
iBitIndex = 0;
iByte--;
szDest[iIndex] = ' ';
bAppendedSpace = true;
iIndex++; if (iIndex == iDestLength) { break; };
if (iByte == ((size)-1))
{
break;
}
}
}
if ((iIndex == iDestLength) || (bAppendedSpace))
{
iIndex--;
}
szDest[iIndex] = '\0';
return szDest;
}
char* FlagsToString(char* szDest, size iDestLength, int32 iFlags)
{
return FlagsToString(szDest, iDestLength, (uint8*)&iFlags, 4);
}
char* FlagsToString(char* szDest, size iDestLength, int16 iFlags)
{
return FlagsToString(szDest, iDestLength, (uint8*)&iFlags, 2);
}
char* FlagsToString(char* szDest, size iDestLength, int8 iFlags)
{
return FlagsToString(szDest, iDestLength, (uint8*)&iFlags, 1);
}
char* FlagsToString(char* szDest, size iDestLength, uint32 iFlags)
{
return FlagsToString(szDest, iDestLength, (uint8*)&iFlags, 4);
}
char* FlagsToString(char* szDest, size iDestLength, uint16 iFlags)
{
return FlagsToString(szDest, iDestLength, (uint8*)&iFlags, 2);
}
char* FlagsToString(char* szDest, size iDestLength, uint8 iFlags)
{
return FlagsToString(szDest, iDestLength, (uint8*)&iFlags, 1);
}
char* CharToString(char* szDest, size iDestLength, char c)
{
return CharToString(szDest, iDestLength, (uint8)c);
}
char* CharToString(char* szDest, size iDestLength, uint8 c)
{
char sz[10];
size iIndex;
size iLength;
if (iDestLength == 0)
{
return szDest;
}
iIndex = 0;
szDest[iIndex] = '\'';
iIndex++;
if (iIndex >= iDestLength) { szDest[iDestLength - 1] = '\0'; return szDest; };
GetEscapeString(c, sz);
StrCpySafe(&szDest[iIndex], sz, iDestLength - iIndex, &iLength);
iIndex += iLength;
if (iIndex >= iDestLength) { szDest[iDestLength - 1] = '\0'; return szDest; };
szDest[iIndex] = '\'';
iIndex++;
if (iIndex >= iDestLength) { szDest[iDestLength - 1] = '\0'; return szDest; };
szDest[iIndex] = '\0';
return szDest;
}
char* CharToString(char* szDest, size iDestLength, char16 c)
{
char sz[10];
size iIndex;
size iLength;
if (iDestLength == 0)
{
return szDest;
}
iIndex = 0;
szDest[iIndex] = '\'';
iIndex++;
if (iIndex >= iDestLength) { szDest[iDestLength - 1] = '\0'; return szDest; };
GetEscapeString(c, sz);
StrCpySafe(&szDest[iIndex], sz, iDestLength - iIndex, &iLength);
iIndex += iLength;
if (iIndex >= iDestLength) { szDest[iDestLength - 1] = '\0'; return szDest; };
szDest[iIndex] = '\'';
iIndex++;
if (iIndex >= iDestLength) { szDest[iDestLength - 1] = '\0'; return szDest; };
szDest[iIndex] = '\0';
return szDest;
}
char* BoolToString(char* szDest, size iDestLength, bool b)
{
if (b)
{
StrCpySafe(szDest, "true", iDestLength);
}
else
{
StrCpySafe(szDest, "false", iDestLength);
}
return szDest;
}
size NumberOfDigits(size uiNumber)
{
long double f;
if (uiNumber == 0)
{
return 1;
}
f = log10((double)uiNumber);
f = floorl(f) + 1;
return (size)f;
}
char* NextString(const char* szCurrent)
{
size uiLength;
uiLength = StrLen(szCurrent);
return (char*)&szCurrent[uiLength + 1];
}
