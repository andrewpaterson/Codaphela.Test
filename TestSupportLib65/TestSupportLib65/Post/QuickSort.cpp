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
void* RemapSinglePointer(const void* pvPtr, ptrdiff iOffest);
__inline void* RemapSinglePointer(const void* pvPtr, ptrdiff iOffest)
{
return &((char*)pvPtr)[iOffest];
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
typedef int (*DataCompare)(const void* pvLeft, const void* pvRight);
void BubbleSort(DataCompare fCompare, void* pvArray, lsize uiStride, lsize iNumElements);
void _quicksort(void* const pbase, lsize total_elems, lsize lsize, DataCompare cmp);
void QuickSort(DataCompare fCompare, void* pvArray, lsize uiStride, lsize uiNumElements)
{
_quicksort(pvArray, uiNumElements, uiStride, fCompare);
}
typedef struct
{
char* lo;
char* hi;
} stack_node;
void _quicksort(void* const pbase, lsize total_elems, lsize uiSize, DataCompare cmp)
{
char* base_ptr = (char*)pbase;
const lsize max_thresh = 4 * uiSize;
if (total_elems == 0)
return;
if (total_elems > 4)
{
char* lo = base_ptr;
char* hi = &lo[uiSize * (total_elems - 1)];
stack_node stack[((sizeof(char) * 8) * sizeof (lsize))];
stack_node* top = stack;
((void) ((top->lo = (0L)), (top->hi = (0L)), ++top));
while ((stack < top))
{
char* left_ptr;
char* right_ptr;
char* mid = lo + uiSize * ((hi - lo) / uiSize >> 1);
if ((*cmp) ((void*)mid, (void*)lo) < 0)
MemSwp(mid, lo, uiSize);
if ((*cmp) ((void*)hi, (void*)mid) < 0)
MemSwp(mid, hi, uiSize);
else
goto jump_over;
if ((*cmp) ((void*)mid, (void*)lo) < 0)
MemSwp(mid, lo, uiSize);
jump_over:;
left_ptr = lo + uiSize;
right_ptr = hi - uiSize;
do
{
while ((*cmp) ((void*)left_ptr, (void*)mid) < 0)
left_ptr += uiSize;
while ((*cmp) ((void*)mid, (void*)right_ptr) < 0)
right_ptr -= uiSize;
if (left_ptr < right_ptr)
{
MemSwp(left_ptr, right_ptr, uiSize);
if (mid == left_ptr)
mid = right_ptr;
else if (mid == right_ptr)
mid = left_ptr;
left_ptr += uiSize;
right_ptr -= uiSize;
}
else if (left_ptr == right_ptr)
{
left_ptr += uiSize;
right_ptr -= uiSize;
break;
}
}
while (left_ptr <= right_ptr);
if ((lsize)(right_ptr - lo) <= max_thresh)
{
if ((lsize)(hi - left_ptr) <= max_thresh)
((void) (--top, (lo = top->lo), (hi = top->hi)));
else
lo = left_ptr;
}
else if ((lsize)(hi - left_ptr) <= max_thresh)
hi = right_ptr;
else if ((right_ptr - lo) > (hi - left_ptr))
{
((void) ((top->lo = (lo)), (top->hi = (right_ptr)), ++top));
lo = left_ptr;
}
else
{
((void) ((top->lo = (left_ptr)), (top->hi = (hi)), ++top));
hi = right_ptr;
}
}
}
{
char* const end_ptr = &base_ptr[uiSize * (total_elems - 1)];
char* tmp_ptr = base_ptr;
char* thresh = ((end_ptr) < (base_ptr + max_thresh) ? (end_ptr) : (base_ptr + max_thresh));
char* run_ptr;
for (run_ptr = tmp_ptr + uiSize; run_ptr <= thresh; run_ptr += uiSize)
if ((*cmp) ((void*)run_ptr, (void*)tmp_ptr) < 0)
tmp_ptr = run_ptr;
if (tmp_ptr != base_ptr)
MemSwp(tmp_ptr, base_ptr, uiSize);
run_ptr = base_ptr + uiSize;
while ((run_ptr += uiSize) <= end_ptr)
{
tmp_ptr = run_ptr - uiSize;
while ((*cmp) ((void*)run_ptr, (void*)tmp_ptr) < 0)
tmp_ptr -= uiSize;
tmp_ptr += uiSize;
if (tmp_ptr != run_ptr)
{
char* trav;
trav = run_ptr + uiSize;
while (--trav >= run_ptr)
{
char c = *trav;
char* hi, * lo;
for (hi = lo = trav; (lo -= uiSize) >= tmp_ptr; hi = lo)
*hi = *lo;
*hi = c;
}
}
}
}
}
