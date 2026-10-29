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
char GetEscapeCode(char cCurrent);
char* GetEscapeString(char cCurrent, char* szDest);
char* GetEscapeString(uint8 cCurrent, char* szDest);
char* GetEscapeString(char16 cCurrent, char* szDest);
char GetEscapeCode(char cCurrent)
{
if (cCurrent == 'n')
{
return '\n';
}
else if (cCurrent == '\\')
{
return '\\';
}
else if (cCurrent == '\"')
{
return '\"';
}
else if (cCurrent == '\'')
{
return '\'';
}
else if (cCurrent == '?')
{
return '\?';
}
else if (cCurrent == '0')
{
return '\0';
}
else if (cCurrent == 'a')
{
return '\a';
}
else if (cCurrent == 'b')
{
return '\b';
}
else if (cCurrent == 'f')
{
return '\f';
}
else if (cCurrent == 'r')
{
return '\r';
}
else if (cCurrent == 't')
{
return '\t';
}
else if (cCurrent == 'v')
{
return '\v';
}
return '@';
}
void StrEscapeUnicode(char16 c, char* szDest)
{
char c1;
char c2;
char c3;
char c4;
c1 = (c & 0xf);
c2 = (c & 0xf0) >> 4;
c3 = (c & 0xf00) >> 8;
c4 = (c & 0xf000) >> 12;
szDest[0] = '\\';
szDest[1] = 'u';
szDest[2] = GetHexChar(c4);
szDest[3] = GetHexChar(c3);
szDest[4] = GetHexChar(c2);
szDest[5] = GetHexChar(c1);
szDest[6] = '\0';
}
void StrEscapeHex(char c, char* szDest)
{
char cRight;
char cLeft;
cRight = (c & 0xf);
cLeft = (c & 0xf0) >> 4;
szDest[0] = '\\';
szDest[1] = 'x';
szDest[2] = GetHexChar(cLeft);
szDest[3] = GetHexChar(cRight);
szDest[4] = '\0';
}
void StrEscapeChar(char c, char* szDest)
{
szDest[0] = '\\';
szDest[1] = c;
szDest[2] = '\0';
}
char* GetEscapeString(char cCurrent, char* szDest)
{
return GetEscapeString((uint8)cCurrent, szDest);
}
char* GetEscapeString(uint8 cCurrent, char* szDest)
{
if (cCurrent == '\\')
{
StrEscapeChar('\\', szDest);
}
else if (cCurrent == '\n')
{
StrEscapeChar('n', szDest);
}
else if (cCurrent == '\"')
{
StrEscapeChar('\"', szDest);
}
else if (cCurrent == '\'')
{
StrEscapeChar('\'', szDest);
}
else if (cCurrent == '\?')
{
StrEscapeChar('?', szDest);
}
else if (cCurrent == '\0')
{
StrEscapeChar('0', szDest);
}
else if (cCurrent == '\a')
{
StrEscapeChar('a', szDest);
}
else if (cCurrent == '\b')
{
StrEscapeChar('b', szDest);
}
else if (cCurrent == '\f')
{
StrEscapeChar('f', szDest);
}
else if (cCurrent == '\r')
{
StrEscapeChar('r', szDest);
}
else if (cCurrent == '\t')
{
StrEscapeChar('t', szDest);
}
else if (cCurrent == '\v')
{
StrEscapeChar('v', szDest);
}
else if (((cCurrent >= 32) && (cCurrent <= 126)) || (cCurrent == 128) || ((cCurrent >= 130) && (cCurrent <= 254)))
{
szDest[0] = cCurrent;
szDest[1] = '\0';
}
else
{
StrEscapeHex(cCurrent, szDest);
}
return szDest;
}
char* GetEscapeString(char16 cCurrent, char* szDest)
{
StrEscapeUnicode(cCurrent, szDest);
return szDest;
}
