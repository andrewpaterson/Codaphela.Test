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
extern int errno;
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
struct STrueMallocatorBlock
{
size uiPreviousSize;
size uiSize;
STrueMallocatorBlock* psNextFree;
STrueMallocatorBlock* psPreviousFree;
};
class CTrueMallocator
{
protected:
uint8* mpuiStart;
STrueMallocatorBlock* mpsEnd;
uint32 muiFirstBitmap;
uint32 mauiSecondBitmaps[(32 - (4 + 3) + 1)];
STrueMallocatorBlock* mapsFree[(32 - (4 + 3) + 1)][(1 << 4)];
size muiNumAllocations;
size muiAllocatedBytes;
public:
bool Init(void* pvMemory, size uiBytes);
void Kill(void);
void* Malloc(lsize uiBytes);
void* Realloc(void* pv, lsize uiBytes);
void Free(void* pv);
size Size(void* pv);
size NumAllocations(void);
size AllocatedBytes(void);
size LargestFree(void);
bool Contains(void* pv);
bool IsValid(void);
protected:
size BlockSize(size uiBytes);
void Mapping(size uiSize, int* piFirst, int* piSecond);
STrueMallocatorBlock* FindFree(size uiSize);
void InsertFree(STrueMallocatorBlock* psBlock);
void RemoveFree(STrueMallocatorBlock* psBlock);
STrueMallocatorBlock* Next(STrueMallocatorBlock* psBlock);
void MarkFree(STrueMallocatorBlock* psBlock, size uiSize);
void Split(STrueMallocatorBlock* psBlock, size uiSize);
};
int errno = 0;
CTrueMallocator gcHeap;
bool gbHeap = false;
extern "C" char _end;
static void InitHeap(void)
{
uint32_t uiMemorySize;
uint32_t uiStart;
uint32_t uiEnd;
uiMemorySize = (*(volatile uint32_t*)0x00FF0300);
if (uiMemorySize > 0x1000000)
{
uiStart = 0x1000000;
uiEnd = uiMemorySize;
}
else if (uiMemorySize > 0x200000)
{
uiStart = (uint32_t)&_end;
uiStart = (uiStart > 0x200000) ? ((uiStart + 15) & ~(uint32_t)15) : 0x200000;
uiEnd = (uiMemorySize < 0xFF0000) ? uiMemorySize : 0xFF0000;
}
else
{
uiStart = 0x80000;
uiEnd = 0x100000;
}
gcHeap.Init((void*)uiStart, uiEnd - uiStart);
gbHeap = true;
}
void* malloc(size_t uiBytes)
{
if (!gbHeap)
{
InitHeap();
}
return gcHeap.Malloc(uiBytes);
}
void free(void* pv)
{
gcHeap.Free(pv);
}
void* calloc(size_t uiCount, size_t uiBytes)
{
void* pv;
if ((uiBytes != 0) && (uiCount > (size_t)-1 / uiBytes))
{
return 0L;
}
pv = malloc(uiCount * uiBytes);
if (pv)
{
memset(pv, 0, uiCount * uiBytes);
}
return pv;
}
void* realloc(void* pv, size_t uiBytes)
{
if (!gbHeap)
{
InitHeap();
}
return gcHeap.Realloc(pv, uiBytes);
}
int abs(int i)
{
return (i < 0) ? -i : i;
}
long labs(long i)
{
return (i < 0) ? -i : i;
}
static int DigitValue(char c)
{
if (isdigit(c))
{
return c - '0';
}
if (islower(c))
{
return c - 'a' + 10;
}
if (isupper(c))
{
return c - 'A' + 10;
}
return 36;
}
static bool ParseInteger(const char* sz, char** pszEnd, int iBase, unsigned long long ullMaximum, unsigned long long* pullValue, bool* pbNegative, bool* pbOverflow)
{
const char* szStart;
unsigned long long ullValue;
unsigned long long ullLimit;
int iLimitDigit;
int iDigit;
bool bDigits;
szStart = sz;
while (isspace(*sz))
{
sz++;
}
*pbNegative = false;
if ((*sz == '-') || (*sz == '+'))
{
*pbNegative = *sz == '-';
sz++;
}
if (((iBase == 0) || (iBase == 16)) && (sz[0] == '0') && ((sz[1] == 'x') || (sz[1] == 'X')) && (DigitValue(sz[2]) < 16))
{
iBase = 16;
sz += 2;
}
else if (iBase == 0)
{
iBase = (sz[0] == '0') ? 8 : 10;
}
ullLimit = ullMaximum / (unsigned)iBase;
iLimitDigit = (int)(ullMaximum % (unsigned)iBase);
ullValue = 0;
bDigits = false;
*pbOverflow = false;
for (;;)
{
iDigit = DigitValue(*sz);
if (iDigit >= iBase)
{
break;
}
if ((ullValue > ullLimit) || ((ullValue == ullLimit) && (iDigit > iLimitDigit)))
{
*pbOverflow = true;
}
else
{
ullValue = ullValue * (unsigned)iBase + (unsigned)iDigit;
}
bDigits = true;
sz++;
}
if (pszEnd)
{
*pszEnd = (char*)(bDigits ? sz : szStart);
}
*pullValue = ullValue;
return bDigits;
}
long strtol(const char* sz, char** pszEnd, int iBase)
{
unsigned long long ullValue;
bool bNegative;
bool bOverflow;
if (!ParseInteger(sz, pszEnd, iBase, 0xffffffffUL, &ullValue, &bNegative, &bOverflow))
{
return 0;
}
if (bNegative)
{
if (bOverflow || (ullValue > (unsigned long)2147483647L + 1))
{
errno = 34;
return (-2147483647L - 1);
}
return (long)((unsigned long)0 - (unsigned long)ullValue);
}
if (bOverflow || (ullValue > (unsigned long)2147483647L))
{
errno = 34;
return 2147483647L;
}
return (long)ullValue;
}
unsigned long strtoul(const char* sz, char** pszEnd, int iBase)
{
unsigned long long ullValue;
bool bNegative;
bool bOverflow;
if (!ParseInteger(sz, pszEnd, iBase, 0xffffffffUL, &ullValue, &bNegative, &bOverflow))
{
return 0;
}
if (bOverflow)
{
errno = 34;
return 0xffffffffUL;
}
return bNegative ? (unsigned long)0 - (unsigned long)ullValue : (unsigned long)ullValue;
}
long long strtoll(const char* sz, char** pszEnd, int iBase)
{
unsigned long long ullValue;
bool bNegative;
bool bOverflow;
if (!ParseInteger(sz, pszEnd, iBase, 0xffffffffffffffffULL, &ullValue, &bNegative, &bOverflow))
{
return 0;
}
if (bNegative)
{
if (bOverflow || (ullValue > (unsigned long long)9223372036854775807LL + 1))
{
errno = 34;
return (-9223372036854775807LL - 1);
}
return (long long)((unsigned long long)0 - ullValue);
}
if (bOverflow || (ullValue > (unsigned long long)9223372036854775807LL))
{
errno = 34;
return 9223372036854775807LL;
}
return (long long)ullValue;
}
unsigned long long strtoull(const char* sz, char** pszEnd, int iBase)
{
unsigned long long ullValue;
bool bNegative;
bool bOverflow;
if (!ParseInteger(sz, pszEnd, iBase, 0xffffffffffffffffULL, &ullValue, &bNegative, &bOverflow))
{
return 0;
}
if (bOverflow)
{
errno = 34;
return 0xffffffffffffffffULL;
}
return bNegative ? (unsigned long long)0 - ullValue : ullValue;
}
static bool MatchIgnoreCase(const char* sz, const char* szWord)
{
while (*szWord)
{
if (tolower((unsigned char)*sz) != *szWord)
{
return false;
}
sz++;
szWord++;
}
return true;
}
double strtod(const char* sz, char** pszEnd)
{
const char* szStart;
const char* szExponent;
unsigned long long ullDigits;
int iDigits;
int iExponent;
int iExponentValue;
bool bNegative;
bool bNegativeExponent;
bool bAny;
double dValue;
double dScale;
double dPower;
int iPower;
szStart = sz;
while (isspace((unsigned char)*sz))
{
sz++;
}
bNegative = false;
if ((*sz == '-') || (*sz == '+'))
{
bNegative = *sz == '-';
sz++;
}
if (MatchIgnoreCase(sz, "inf"))
{
sz += MatchIgnoreCase(sz, "infinity") ? 8 : 3;
if (pszEnd)
{
*pszEnd = (char*)sz;
}
return bNegative ? -__builtin_huge_val() : __builtin_huge_val();
}
if (MatchIgnoreCase(sz, "nan"))
{
if (pszEnd)
{
*pszEnd = (char*)(sz + 3);
}
ullDigits = 0x7FF8000000000000ULL;
memcpy(&dValue, &ullDigits, sizeof(double));
return dValue;
}
ullDigits = 0;
iDigits = 0;
iExponent = 0;
bAny = false;
while ((*sz >= '0') && (*sz <= '9'))
{
if (iDigits < 19)
{
ullDigits = ullDigits * 10 + (unsigned)(*sz - '0');
if (ullDigits != 0)
{
iDigits++;
}
}
else
{
iExponent++;
}
bAny = true;
sz++;
}
if (*sz == '.')
{
sz++;
while ((*sz >= '0') && (*sz <= '9'))
{
if (iDigits < 19)
{
ullDigits = ullDigits * 10 + (unsigned)(*sz - '0');
if (ullDigits != 0)
{
iDigits++;
}
iExponent--;
}
bAny = true;
sz++;
}
}
if (!bAny)
{
if (pszEnd)
{
*pszEnd = (char*)szStart;
}
return 0.0;
}
if ((*sz == 'e') || (*sz == 'E'))
{
szExponent = sz;
sz++;
bNegativeExponent = false;
if ((*sz == '-') || (*sz == '+'))
{
bNegativeExponent = *sz == '-';
sz++;
}
if ((*sz >= '0') && (*sz <= '9'))
{
iExponentValue = 0;
while ((*sz >= '0') && (*sz <= '9'))
{
if (iExponentValue < 10000)
{
iExponentValue = iExponentValue * 10 + (*sz - '0');
}
sz++;
}
iExponent += bNegativeExponent ? -iExponentValue : iExponentValue;
}
else
{
sz = szExponent;
}
}
if (pszEnd)
{
*pszEnd = (char*)sz;
}
dValue = (double)ullDigits;
if (dValue != 0.0)
{
iPower = (iExponent < 0) ? -iExponent : iExponent;
dScale = 1.0;
dPower = 10.0;
while (iPower > 0)
{
if (iPower & 1)
{
dScale *= dPower;
}
dPower *= dPower;
iPower >>= 1;
}
if (iExponent < 0)
{
if (iExponent < -300)
{
dValue /= 1e300;
dScale /= 1e300;
}
dValue /= dScale;
}
else
{
dValue *= dScale;
}
if ((dValue == 0.0) || (dValue > 1.7976931348623157e308))
{
errno = 34;
}
}
return bNegative ? -dValue : dValue;
}
float strtof(const char* sz, char** pszEnd)
{
return (float)strtod(sz, pszEnd);
}
long double strtold(const char* sz, char** pszEnd)
{
return strtod(sz, pszEnd);
}
double atof(const char* sz)
{
return strtod(sz, 0L);
}
int atoi(const char* sz)
{
return (int)strtol(sz, 0L, 10);
}
long atol(const char* sz)
{
return strtol(sz, 0L, 10);
}
uint32_t guiRandom = 1;
int rand(void)
{
guiRandom = guiRandom * 1103515245UL + 12345;
return (int)((guiRandom / 65536) % ((uint32_t)0x7fff + 1));
}
void srand(unsigned int uiSeed)
{
guiRandom = uiSeed;
}
void qsort(void* pvBase, size_t uiCount, size_t uiBytes, int (*fCompare)(const void*, const void*))
{
char* pcBase;
char* pcKey;
size_t i;
size_t j;
size_t k;
char c;
pcBase = (char*)pvBase;
for (i = 1; i < uiCount; i++)
{
for (j = i; j > 0; j--)
{
pcKey = pcBase + j * uiBytes;
if (fCompare(pcKey - uiBytes, pcKey) <= 0)
{
break;
}
for (k = 0; k < uiBytes; k++)
{
c = pcKey[k];
pcKey[k] = pcKey[k - uiBytes];
pcKey[k - uiBytes] = c;
}
}
}
}
void abort(void)
{
_Exit(1);
}
typedef void (*FAtExit)(void);
static FAtExit gafAtExit[32];
static int giAtExits;
int atexit(void (*fFunction)(void))
{
if (giAtExits == 32)
{
return -1;
}
gafAtExit[giAtExits] = fFunction;
giAtExits++;
return 0;
}
extern "C" void __RunAtExit(void);
void __RunAtExit(void)
{
while (giAtExits > 0)
{
giAtExits--;
gafAtExit[giAtExits]();
}
}
typedef void (*FFinalise)(void);
extern "C" char _fini_start;
extern "C" char _fini_end;
void exit(int iStatus)
{
FFinalise* pfFinalise;
__RunAtExit();
pfFinalise = (FFinalise*)&_fini_end;
while (pfFinalise != (FFinalise*)&_fini_start)
{
pfFinalise--;
(*pfFinalise)();
}
_Exit(iStatus);
}
