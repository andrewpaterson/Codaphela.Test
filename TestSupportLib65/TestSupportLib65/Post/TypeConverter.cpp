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
class CChars;
class CUserError
{
private:
char mszUserError[4096];
bool mbUserError;
public:
void Init(void);
void Kill(void);
bool Set(const char* szError);
bool Set2(const char* szError, ...);
bool Set(CChars* pszError, bool bKillErrorString = true);
char* Get(void);
};
extern CUserError gcUserError;
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
typedef void (*ConversionFunc) (void* pvDest, void* pvSource);
class CTypeConverter
{
ConversionFunc mapvScaleTuncateConversion[PRIMTIVE_CONVERTER_END][PRIMTIVE_CONVERTER_END];
public:
void Init(void);
void Kill(void);
void Do(EPrimitiveType eDest, void* pvDest, EPrimitiveType eSource, void* pvSource);
};
extern CTypeConverter gcTypeConverter;
void TypeConverterInit(void);
void TypeConverterKill(void);
CTypeConverter gcTypeConverter;
void ConvertScaleTruncate_float64_To_int8(int8* psDest, float64* pf) { if (*pf >= (float64)0) if (*pf >= (float64)1) *psDest = (int8)0x7f; else *psDest = (int8)(0x7f * *pf); else if (*pf <= -(float64)1) *psDest = (int8)0x80; else *psDest = (int8)(0x80 * *pf); }
void ConvertScaleTruncate_float32_To_int8(int8* psDest, float32* pf) { if (*pf >= (float32)0) if (*pf >= (float32)1) *psDest = (int8)0x7f; else *psDest = (int8)(0x7f * *pf); else if (*pf <= -(float32)1) *psDest = (int8)0x80; else *psDest = (int8)(0x80 * *pf); }
void ConvertScaleTruncate_int64_To_int8(int8* psDest, int64* pi) { *psDest = (int8)(*pi / (int64)(((uint64)0x7fffffffffffffffLL + 1) / (0x7f + 1))); }
void ConvertScaleTruncate_int32_To_int8(int8* psDest, int32* pi) { *psDest = (int8)(*pi / (int32)(((uint32)0x7fffffff + 1) / (0x7f + 1))); }
void ConvertScaleTruncate_int16_To_int8(int8* psDest, int16* pi) { *psDest = (int8)(*pi / (int16)(((uint16)0x7fff + 1) / (0x7f + 1))); }
void ConvertScaleTruncate_int8_To_int8(int8* psDest, int8* pi) { *psDest = (int8)(*pi / (int8)(((uint8)0x7f + 1) / (0x7f + 1))); }
void ConvertScaleTruncate_uint64_To_int8(int8* psDest, uint64* pi) { *psDest = (int8)(*pi / ((((uint64)0x7fffffffffffffffLL + 1) / (0x7f + 1)) * 2)); }
void ConvertScaleTruncate_uint32_To_int8(int8* psDest, uint32* pi) { *psDest = (int8)(*pi / ((((uint32)0x7fffffff + 1) / (0x7f + 1)) * 2)); }
void ConvertScaleTruncate_uint16_To_int8(int8* psDest, uint16* pi) { *psDest = (int8)(*pi / ((((uint16)0x7fff + 1) / (0x7f + 1)) * 2)); }
void ConvertScaleTruncate_uint8_To_int8(int8* psDest, uint8* pi) { *psDest = (int8)(*pi / ((((uint8)0x7f + 1) / (0x7f + 1)) * 2)); }
void ConvertScaleTruncate_float64_To_uint8(uint8* psDest, float64* pf) { if (*pf >= (float64)0) if (*pf >= (float64)1) * psDest = (uint8)0xff; else * psDest = (uint8)(0xff * *pf); else * psDest = (uint8)0x00; }
void ConvertScaleTruncate_float32_To_uint8(uint8* psDest, float32* pf) { if (*pf >= (float32)0) if (*pf >= (float32)1) * psDest = (uint8)0xff; else * psDest = (uint8)(0xff * *pf); else * psDest = (uint8)0x00; }
void ConvertScaleTruncate_int64_To_uint8(uint8* psDest, int64* pi) { *psDest = *pi >= 0 ? (uint8)(*pi / ((((uint64)0x7fffffffffffffffLL + 1) / (0x7f + 1)) / 2)) : 0; }
void ConvertScaleTruncate_int32_To_uint8(uint8* psDest, int32* pi) { *psDest = *pi >= 0 ? (uint8)(*pi / ((((uint32)0x7fffffff + 1) / (0x7f + 1)) / 2)) : 0; }
void ConvertScaleTruncate_int16_To_uint8(uint8* psDest, int16* pi) { *psDest = *pi >= 0 ? (uint8)(*pi / ((((uint16)0x7fff + 1) / (0x7f + 1)) / 2)) : 0; }
void ConvertScaleTruncate_int8_To_uint8(uint8* psDest, int8* pi) { *psDest = *pi >= 0 ? (*pi * 2 + (*pi > 0x40 ? 1 : 0)) : 0; }
void ConvertScaleTruncate_uint64_To_uint8(uint8* psDest, uint64* pi) { *psDest = (uint8)(*pi / (((uint64)0x7fffffffffffffffLL + 1) / (0x7f + 1))); }
void ConvertScaleTruncate_uint32_To_uint8(uint8* psDest, uint32* pi) { *psDest = (uint8)(*pi / (((uint32)0x7fffffff + 1) / (0x7f + 1))); }
void ConvertScaleTruncate_uint16_To_uint8(uint8* psDest, uint16* pi) { *psDest = (uint8)(*pi / (((uint16)0x7fff + 1) / (0x7f + 1))); }
void ConvertScaleTruncate_uint8_To_uint8(uint8* psDest, uint8* pi) { *psDest = (uint8)(*pi / (((uint8)0x7f + 1) / (0x7f + 1))); }
void ConvertScaleTruncate_float64_To_int16(int16* psDest, float64* pf) { if (*pf >= (float64)0) if (*pf >= (float64)1) *psDest = (int16)0x7fff; else *psDest = (int16)(0x7fff * *pf); else if (*pf <= -(float64)1) *psDest = (int16)0x8000; else *psDest = (int16)(0x8000 * *pf); }
void ConvertScaleTruncate_float32_To_int16(int16* psDest, float32* pf) { if (*pf >= (float32)0) if (*pf >= (float32)1) *psDest = (int16)0x7fff; else *psDest = (int16)(0x7fff * *pf); else if (*pf <= -(float32)1) *psDest = (int16)0x8000; else *psDest = (int16)(0x8000 * *pf); }
void ConvertScaleTruncate_int64_To_int16(int16* psDest, int64* pi) { *psDest = (int16)(*pi / (int64)(((uint64)0x7fffffffffffffffLL + 1) / (0x7fff + 1))); }
void ConvertScaleTruncate_int32_To_int16(int16* psDest, int32* pi) { *psDest = (int16)(*pi / (int32)(((uint32)0x7fffffff + 1) / (0x7fff + 1))); }
void ConvertScaleTruncate_int16_To_int16(int16* psDest, int16* pi) { *psDest = (int16)(*pi / (int16)(((uint16)0x7fff + 1) / (0x7fff + 1))); }
void ConvertScaleTruncate_int8_To_int16(int16* psDest, int8* pi) { *psDest = ((int16)*pi << 8) | *pi; }
void ConvertScaleTruncate_uint64_To_int16(int16* psDest, uint64* pi) { *psDest = (int16)(*pi / ((((uint64)0x7fffffffffffffffLL + 1) / (0x7fff + 1)) * 2)); }
void ConvertScaleTruncate_uint32_To_int16(int16* psDest, uint32* pi) { *psDest = (int16)(*pi / ((((uint32)0x7fffffff + 1) / (0x7fff + 1)) * 2)); }
void ConvertScaleTruncate_uint16_To_int16(int16* psDest, uint16* pi) { *psDest = (int16)(*pi / ((((uint16)0x7fff + 1) / (0x7fff + 1)) * 2)); }
void ConvertScaleTruncate_uint8_To_int16(int16* psDest, uint8* pi) { *psDest = ((int16)*pi << 7) | *pi; }
void ConvertScaleTruncate_float64_To_uint16(uint16* psDest, float64* pf) { if (*pf >= (float64)0) if (*pf >= (float64)1) * psDest = (uint16)0xffff; else * psDest = (uint16)(0xffff * *pf); else * psDest = (uint16)0x0000; }
void ConvertScaleTruncate_float32_To_uint16(uint16* psDest, float32* pf) { if (*pf >= (float32)0) if (*pf >= (float32)1) * psDest = (uint16)0xffff; else * psDest = (uint16)(0xffff * *pf); else * psDest = (uint16)0x0000; }
void ConvertScaleTruncate_int64_To_uint16(uint16* psDest, int64* pi) { *psDest = *pi >= 0 ? (uint16)(*pi / ((((uint64)0x7fffffffffffffffLL + 1) / (0x7fff + 1)) / 2)) : 0; }
void ConvertScaleTruncate_int32_To_uint16(uint16* psDest, int32* pi) { *psDest = *pi >= 0 ? (uint16)(*pi / ((((uint32)0x7fffffff + 1) / (0x7fff + 1)) / 2)) : 0; }
void ConvertScaleTruncate_int16_To_uint16(uint16* psDest, int16* pi) { *psDest = *pi >= 0 ? (*pi * 2 + (*pi > 0x4000 ? 1 : 0)) : 0; }
void ConvertScaleTruncate_int8_To_uint16(uint16* psDest, int8* pi) { *psDest = *pi >= 0 ? ((uint16)*pi << 9) | *pi << 1: 0; }
void ConvertScaleTruncate_uint64_To_uint16(uint16* psDest, uint64* pi) { *psDest = (uint16)(*pi / (((uint64)0x7fffffffffffffffLL + 1) / (0x7fff + 1))); }
void ConvertScaleTruncate_uint32_To_uint16(uint16* psDest, uint32* pi) { *psDest = (uint16)(*pi / (((uint32)0x7fffffff + 1) / (0x7fff + 1))); }
void ConvertScaleTruncate_uint16_To_uint16(uint16* psDest, uint16* pi) { *psDest = *pi; }
void ConvertScaleTruncate_uint8_To_uint16(uint16* psDest, uint8* pi) { *psDest = ((uint16)*pi << 8) | *pi; }
void ConvertScaleTruncate_float64_To_int32 (int32* piDest, float64* pf) { *piDest = (int32)((float64)0xffffffff * *pf); }
void ConvertScaleTruncate_float32_To_int32 (int32* piDest, float32* pf) { *piDest = (int32)((float32)0xffffffff * *pf); }
void ConvertScaleTruncate_int64_To_int32 (int32* piDest, int64* pi) { *piDest = (int32)(*pi / 0x100000001LL); }
void ConvertScaleTruncate_int32_To_int32 (int32* piDest, int32* pi) { *piDest = *pi; }
void ConvertScaleTruncate_int16_To_int32 (int32* piDest, int16* pi) { *piDest = ((int32)*pi << 16) | *pi; }
void ConvertScaleTruncate_int8_To_int32 (int32* piDest, int8* pi) { *piDest = ((int32)*pi << 24) | ((int32)*pi << 16) | ((int32)*pi << 8) | *pi; }
void ConvertScaleTruncate_uint64_To_int32 (int32* piDest, uint64* pi) { *piDest = (int32)(*pi / 0x100000001LL); }
void ConvertScaleTruncate_uint32_To_int32 (int32* piDest, uint32* pi) { *piDest = *pi; }
void ConvertScaleTruncate_uint16_To_int32 (int32* piDest, uint16* pi) { *piDest = ((int32)*pi << 16) | *pi; }
void ConvertScaleTruncate_uint8_To_int32 (int32* piDest, uint8* pi) { *piDest = ((int32)*pi << 24) | ((int32)*pi << 16) | ((int32)*pi << 8) | *pi; }
void ConvertScaleTruncate_float64_To_uint32 (uint32* psDest, float64* pf) { *psDest = (uint32)((float64)0xffffffff * *pf); }
void ConvertScaleTruncate_float32_To_uint32 (uint32* piDest, float32* pf) { *piDest = (uint32)((float32)0xffffffff * *pf); }
void ConvertScaleTruncate_int64_To_uint32 (uint32* piDest, int64* pi) { *piDest = (uint32)(*pi / 0x100000001LL); }
void ConvertScaleTruncate_int32_To_uint32 (uint32* piDest, int32* pi) { *piDest = *pi; }
void ConvertScaleTruncate_int16_To_uint32 (uint32* piDest, int16* pi) { *piDest = ((uint32)*pi << 16) | *pi; }
void ConvertScaleTruncate_int8_To_uint32 (uint32* piDest, int8* pi) { *piDest = ((uint32)*pi << 24) | ((int32)*pi << 16) | ((int32)*pi << 8) | *pi; }
void ConvertScaleTruncate_uint64_To_uint32 (uint32* piDest, uint64* pi) { *piDest = (uint32)(*pi / 0x100000001LL); }
void ConvertScaleTruncate_uint32_To_uint32 (uint32* piDest, uint32* pi) { *piDest = *pi; }
void ConvertScaleTruncate_uint16_To_uint32 (uint32* piDest, uint16* pi) { *piDest = ((uint32)*pi << 16) | *pi; }
void ConvertScaleTruncate_uint8_To_uint32 (uint32* piDest, uint8* pi) { *piDest = ((uint32)*pi << 24) | ((int32)*pi << 16) | ((int32)*pi << 8) | *pi; }
void ConvertScaleTruncate_float64_To_int64 (int64* piDest, float64* pf) { *piDest = (int64)((float64)0xffffffffffffffffLL * *pf); }
void ConvertScaleTruncate_float32_To_int64 (int64* piDest, float32* pf) { *piDest = (int64)((float32)0xffffffffffffffffLL * *pf); }
void ConvertScaleTruncate_int64_To_int64 (int64* piDest, int64* pi) { *piDest = *pi; }
void ConvertScaleTruncate_int32_To_int64 (int64* piDest, int32* pi) { *piDest = ((int64)*pi << 32) | *pi; }
void ConvertScaleTruncate_int16_To_int64 (int64* piDest, int16* pi) { *piDest = ((int64)*pi << 48) | ((int64)*pi << 32) | ((int64)*pi << 16) | *pi; }
void ConvertScaleTruncate_int8_To_int64 (int64* piDest, int8* pi) { *piDest = ((int64)*pi << 56) | ((int64)*pi << 48) | ((int64)*pi << 40) | ((int64)*pi << 32) | ((int64)*pi << 24) | ((int64)*pi << 16) | ((int64)*pi << 8) | *pi; }
void ConvertScaleTruncate_uint64_To_int64 (int64* piDest, uint64* pi) { *piDest = *pi; }
void ConvertScaleTruncate_uint32_To_int64 (int64* piDest, uint32* pi) { *piDest = ((int64)*pi << 32) | *pi; }
void ConvertScaleTruncate_uint16_To_int64 (int64* piDest, uint16* pi) { *piDest = ((int64)*pi << 48) | ((int64)*pi << 32) | ((int64)*pi << 16) | *pi; }
void ConvertScaleTruncate_uint8_To_int64 (int64* piDest, uint8* pi) { *piDest = ((int64)*pi << 56) | ((int64)*pi << 48) | ((int64)*pi << 40) | ((int64)*pi << 32) | ((int64)*pi << 24) | ((int64)*pi << 16) | ((int64)*pi << 8) | *pi; }
void ConvertScaleTruncate_float64_To_uint64 (uint64* psDest, float64* pf) { *psDest = (uint64)((float64)0xffffffffffffffffLL * *pf); }
void ConvertScaleTruncate_float32_To_uint64 (uint64* piDest, float32* pf) { *piDest = (uint64)((float32)0xffffffffffffffffLL * *pf); }
void ConvertScaleTruncate_int64_To_uint64 (uint64* piDest, int64* pi) { *piDest = *pi; }
void ConvertScaleTruncate_int32_To_uint64 (uint64* piDest, int32* pi) { *piDest = ((uint64)*pi << 32) | *pi; }
void ConvertScaleTruncate_int16_To_uint64 (uint64* piDest, int16* pi) { *piDest = ((uint64)*pi << 48) | ((uint64)*pi << 32) | ((uint64)*pi << 16) | *pi; }
void ConvertScaleTruncate_int8_To_uint64 (uint64* piDest, int8* pi) { *piDest = ((uint64)*pi << 56) | ((uint64)*pi << 48) | ((uint64)*pi << 40) | ((uint64)*pi << 32) | ((uint64)*pi << 24) | ((uint64)*pi << 16) | ((uint64)*pi << 8) | *pi; }
void ConvertScaleTruncate_uint64_To_uint64 (uint64* piDest, uint64* pi) { *piDest = *pi; }
void ConvertScaleTruncate_uint32_To_uint64 (uint64* piDest, uint32* pi) { *piDest = ((uint64)*pi << 32) | *pi; }
void ConvertScaleTruncate_uint16_To_uint64 (uint64* piDest, uint16* pi) { *piDest = ((uint64)*pi << 48) | ((uint64)*pi << 32) | ((uint64)*pi << 16) | *pi; }
void ConvertScaleTruncate_uint8_To_uint64 (uint64* piDest, uint8* pi) { *piDest = ((uint64)*pi << 56) | ((uint64)*pi << 48) | ((uint64)*pi << 40) | ((uint64)*pi << 32) | ((uint64)*pi << 24) | ((uint64)*pi << 16) | ((uint64)*pi << 8) | *pi; }
void ConvertScaleTruncate_float64_To_float32(float32* pfDest, float64* pf) { *pfDest = (float32)*pf; }
void ConvertScaleTruncate_float32_To_float32(float32* pfDest, float32* pf) { *pfDest = *pf; }
void ConvertScaleTruncate_int64_To_float32 (float32* pfDest, int64* pi) { *pfDest = (float32)*pi / 0xffffffffffffffffLL; }
void ConvertScaleTruncate_int32_To_float32 (float32* pfDest, int32* pi) { *pfDest = (float32)*pi / 0xffffffff; }
void ConvertScaleTruncate_int16_To_float32 (float32* pfDest, int16* pi) { *pfDest = (float32)*pi / 0xffff; }
void ConvertScaleTruncate_int8_To_float32 (float32* pfDest, int8* pi) { *pfDest = (float32)*pi / 0xff; }
void ConvertScaleTruncate_uint64_To_float32 (float32* pfDest, uint64* pi) { *pfDest = (float32)*pi / 0xffffffffffffffffLL; }
void ConvertScaleTruncate_uint32_To_float32 (float32* pfDest, uint32* pi) { *pfDest = (float32)*pi / 0xffffffff; }
void ConvertScaleTruncate_uint16_To_float32 (float32* pfDest, uint16* pi) { *pfDest = (float32)*pi / 0xffff; }
void ConvertScaleTruncate_uint8_To_float32 (float32* pfDest, uint8* pi) { *pfDest = (float32)*pi / 0xff; }
void ConvertScaleTruncate_float64_To_float64(float64* pfDest, float64* pf) { *pfDest = *pf; }
void ConvertScaleTruncate_float32_To_float64(float64* pfDest, float32* pf) { *pfDest = *pf; }
void ConvertScaleTruncate_int64_To_float64 (float64* pfDest, int64* pi) { *pfDest = (float64)*pi / 0xffffffffffffffffLL; }
void ConvertScaleTruncate_int32_To_float64 (float64* pfDest, int32* pi) { *pfDest = (float64)*pi / 0xffffffff; }
void ConvertScaleTruncate_int16_To_float64 (float64* pfDest, int16* pi) { *pfDest = (float64)*pi / 0xffff; }
void ConvertScaleTruncate_int8_To_float64 (float64* pfDest, int8* pi) { *pfDest = (float64)*pi / 0xff; }
void ConvertScaleTruncate_uint64_To_float64 (float64* pfDest, uint64* pi) { *pfDest = (float64)*pi / 0xffffffffffffffffLL; }
void ConvertScaleTruncate_uint32_To_float64 (float64* pfDest, uint32* pi) { *pfDest = (float64)*pi / 0xffffffff; }
void ConvertScaleTruncate_uint16_To_float64 (float64* pfDest, uint16* pi) { *pfDest = (float64)*pi / 0xffff; }
void ConvertScaleTruncate_uint8_To_float64 (float64* pfDest, uint8* pi) { *pfDest = (float64)*pi / 0xff; }
void ConvertScaleTruncate_uint8_To_Sixbits (uint8* psDest, uint8* pi) { *psDest = *pi / (0xff/0x3f); }
void ConvertScaleTruncate_uint16_To_Sixbits (uint8* psDest, uint16* pi) { *psDest = *pi / (0xffff/0x3f); }
void ConvertScaleTruncate_uint32_To_Sixbits (uint8* psDest, uint32* pi) { *psDest = *pi / (0xffffffff/0x3f); }
void ConvertScaleTruncate_float64_To_Sixbits(uint8* psDest, float64* pf) { *psDest = (uint8)(*pf * (float64)0x3f); }
void ConvertScaleTruncate_float32_To_Sixbits(uint8* psDest, float32* pf) { *psDest = (uint8)(*pf * (float32)0x3f); }
void ConvertScaleTruncate_uint8_To_Nickle (uint8* psDest, uint8* pi) { *psDest = *pi / (0xff/0x1f); }
void ConvertScaleTruncate_uint16_To_Nickle (uint8* psDest, uint16* pi) { *psDest = *pi / (0xffff/0x1f); }
void ConvertScaleTruncate_uint32_To_Nickle (uint8* psDest, uint32* pi) { *psDest = *pi / (0xffffffff/0x1f); }
void ConvertScaleTruncate_float64_To_Nickle (uint8* psDest, float64* pf) { *psDest = (uint8)(*pf * (float64)0x1f); }
void ConvertScaleTruncate_float32_To_Nickle (uint8* psDest, float32* pf) { *psDest = (uint8)(*pf * (float32)0x1f); }
void ConvertScaleTruncate_uint8_To_Nybble (uint8* psDest, uint8* pi) { *psDest = *pi / (0xff/0xf); }
void ConvertScaleTruncate_uint16_To_Nybble (uint8* psDest, uint16* pi) { *psDest = *pi / (0xffff/0xf); }
void ConvertScaleTruncate_uint32_To_Nybble (uint8* psDest, uint32* pi) { *psDest = *pi / (0xffffffff/0xf); }
void ConvertScaleTruncate_float64_To_Nybble (uint8* psDest, float64* pf) { *psDest = (uint8)(*pf * (float64)0xf); }
void ConvertScaleTruncate_float32_To_Nybble (uint8* psDest, float32* pf) { *psDest = (uint8)(*pf * (float32)0xf); }
void ConvertScaleTruncate_int64_To_Tribble (uint8* psDest, int64* pi) { *psDest = *pi >= 0 ? (uint8)(*pi / (0x7fffffffffffffffLL / 0x7LL)) : 0LL; }
void ConvertScaleTruncate_int32_To_Tribble (uint8* psDest, int32* pi) { *psDest = *pi >= 0 ? (*pi / (0x7fffffff / 0x7)) : 0; }
void ConvertScaleTruncate_int16_To_Tribble (uint8* psDest, int16* pi) { *psDest = *pi >= 0 ? (*pi / (0x7fff / 0x7)) : 0; }
void ConvertScaleTruncate_int8_To_Tribble (uint8* psDest, int8* pi) { *psDest = *pi >= 0 ? (*pi / (0x7f / 0x7)) : 0; }
void ConvertScaleTruncate_float32_To_Tribble(uint8* psDest, float32* pf) { *psDest = (uint8)(*pf * (float32)0x7); }
void ConvertScaleTruncate_float64_To_Tribble(uint8* psDest, float64* pf) { *psDest = (uint8)(*pf * (float64)0x7); }
void ConvertScaleTruncate_uint64_To_Tribble (uint8* psDest, uint64* pi) { *psDest = (uint8)(*pi / (0xffffffffffffffffULL / 0x7ULL)); }
void ConvertScaleTruncate_uint32_To_Tribble (uint8* psDest, uint32* pi) { *psDest = *pi / (0xffffffff / 0x7); }
void ConvertScaleTruncate_uint16_To_Tribble (uint8* psDest, uint16* pi) { *psDest = *pi / (0xffff / 0x7); }
void ConvertScaleTruncate_uint8_To_Tribble (uint8* psDest, uint8* pi) { *psDest = *pi / (0xff / 0x7); }
void ConvertScaleTruncate_Bit_To_Tribble (uint8* psDest, uint8* pi) { *psDest = *pi == 0 ? 0 : 0x7; }
void ConvertScaleTruncate_Crumb_To_Tribble (uint8* psDest, uint8* pi) { *psDest = ((*pi & 0x3) << 1) + (*pi & 0x3) > 2 ? 1 : 0; }
void ConvertScaleTruncate_Tribble_To_Tribble(uint8* psDest, uint8* pi) { *psDest = (*pi & 0x7); }
void ConvertScaleTruncate_Nybble_To_Tribble (uint8* psDest, uint8* pi) { *psDest = (*pi & 0xf) >> 1; }
void ConvertScaleTruncate_Nickle_To_Tribble (uint8* psDest, uint8* pi) { *psDest = (*pi & 0x1f) >> 2; }
void ConvertScaleTruncate_Sixbits_To_Tribble(uint8* psDest, uint8* pi) { *psDest = (*pi & 0x3f) >> 3; }
void ConvertScaleTruncate_int64_To_Crumb (uint8* psDest, int64* pi) { *psDest = *pi >= 0 ? (uint8)(*pi / (0x7fffffffffffffffLL / 0x3LL)) : 0LL; }
void ConvertScaleTruncate_int32_To_Crumb (uint8* psDest, int32* pi) { *psDest = *pi >= 0 ? (*pi / (0x7fffffff / 0x3)) : 0; }
void ConvertScaleTruncate_int16_To_Crumb (uint8* psDest, int16* pi) { *psDest = *pi >= 0 ? (*pi / (0x7fff / 0x3)) : 0; }
void ConvertScaleTruncate_int8_To_Crumb (uint8* psDest, int8* pi) { *psDest = *pi >= 0 ? (*pi / (0x7f / 0x3)) : 0; }
void ConvertScaleTruncate_float32_To_Crumb (uint8* psDest, float32* pf) { *psDest = (uint8)(*pf * (float32)0x3); }
void ConvertScaleTruncate_float64_To_Crumb (uint8* psDest, float64* pf) { *psDest = (uint8)(*pf * (float64)0x3); }
void ConvertScaleTruncate_uint64_To_Crumb (uint8* psDest, uint64* pi) { *psDest = (uint8)(*pi / (0xffffffffffffffffULL / 0x3ULL)); }
void ConvertScaleTruncate_uint32_To_Crumb (uint8* psDest, uint32* pi) { *psDest = *pi / (0xffffffff / 0x3); }
void ConvertScaleTruncate_uint16_To_Crumb (uint8* psDest, uint16* pi) { *psDest = *pi / (0xffff / 0x3); }
void ConvertScaleTruncate_uint8_To_Crumb (uint8* psDest, uint8* pi) { *psDest = *pi / (0xff / 0x3); }
void ConvertScaleTruncate_Bit_To_Crumb (uint8* psDest, uint8* pi) { *psDest = *pi == 0 ? 0 : 0x3; }
void ConvertScaleTruncate_Crumb_To_Crumb (uint8* psDest, uint8* pi) { *psDest = (*pi & 0x3); }
void ConvertScaleTruncate_Tribble_To_Crumb (uint8* psDest, uint8* pi) { *psDest = (*pi & 0x7) >> 1; }
void ConvertScaleTruncate_Nybble_To_Crumb (uint8* psDest, uint8* pi) { *psDest = (*pi & 0xf) >> 2; }
void ConvertScaleTruncate_Nickle_To_Crumb (uint8* psDest, uint8* pi) { *psDest = (*pi & 0x1f) >> 3; }
void ConvertScaleTruncate_Sixbits_To_Crumb (uint8* psDest, uint8* pi) { *psDest = (*pi & 0x3f) >> 4; }
void ConvertScaleTruncate_uint8_To_Bit (uint8* psDest, uint8* pi) { *psDest = *pi / (0xff); }
void ConvertScaleTruncate_uint16_To_Bit (uint8* psDest, uint16* pi) { *psDest = *pi / (0xffff); }
void ConvertScaleTruncate_uint32_To_Bit (uint8* psDest, uint32* pi) { *psDest = *pi / (0xffffffff); }
void ConvertScaleTruncate_float64_To_Bit(uint8* psDest, float64* pf) { *psDest = (uint8)*pf; }
void ConvertScaleTruncate_float32_To_Bit(uint8* psDest, float32* pf) { *psDest = (uint8)*pf; }
void ConvertScaleTruncate_Sixbits_To_uint16 (uint16* pDest, uint8* pi) { uint16 t = (*pi & 0x3f); *pDest = (t << 10) + (t << 4) + (t >> 2); }
void ConvertScaleTruncate_Nickle_To_uint16 (uint16* pDest, uint8* pi) { uint16 t = (*pi & 0x1f); *pDest = (t << 11) + (t << 6) + (t << 1) + (t >> 4); }
void ConvertScaleTruncate_Nybble_To_uint16 (uint16* pDest, uint8* pi) { uint16 t = (*pi & 0x0f); *pDest = (t << 12) + (t << 8) + (t << 4) + t; }
void ConvertScaleTruncate_ThreeBits_To_uint16 (uint16* pDest, uint8* pi) { *pDest = (uint16)((float32)*pi * (65535.0f/7.0f)); }
void ConvertScaleTruncate_Crumb_To_uint16 (uint16* pDest, uint8* pi) { *pDest = (uint16)*pi * (0xffff/3); }
void ConvertScaleTruncate_Bit_To_uint16 (uint16* pDest, uint8* pi) { *pDest = (uint16)*pi * 0xffff; }
void ConvertScaleTruncate_Sixbits_To_uint8 (uint8* pDest, uint8* pi) { *pDest = (uint8)((float32)*pi * (255.0f/63.0f)); }
void ConvertScaleTruncate_Nickle_To_uint8 (uint8* pDest, uint8* pi) { *pDest = (uint8)((float32)*pi * (255.0f/31.0f)); }
void ConvertScaleTruncate_Nybble_To_uint8 (uint8* pDest, uint8* pi) { *pDest = (uint8)((float32)*pi * (255.0f/15.0f)); }
void ConvertScaleTruncate_ThreeBits_To_uint8 (uint8* pDest, uint8* pi) { *pDest = (uint8)((float32)*pi * (255.0f/7.0f)); }
void ConvertScaleTruncate_Crumb_To_uint8 (uint8* pDest, uint8* pi) { *pDest = (uint8)*pi * (0xff/3); }
void ConvertScaleTruncate_Bit_To_uint8 (uint8* pDest, uint8* pi) { *pDest = (uint8)*pi * 0xff; }
void ConvertScaleTruncate_Sixbits_To_uint32 (uint32* pDest, uint8* pi) { *pDest = (uint32)((float32)*pi * (4294967295.0f/63.0f)); }
void ConvertScaleTruncate_Nickle_To_uint32 (uint32* pDest, uint8* pi) { *pDest = (uint32)((float32)*pi * (4294967295.0f/31.0f)); }
void ConvertScaleTruncate_Nybble_To_uint32 (uint32* pDest, uint8* pi) { *pDest = (uint32)((float32)*pi * (4294967295.0f/15.0f)); }
void ConvertScaleTruncate_ThreeBits_To_uint32 (uint32* pDest, uint8* pi) { *pDest = (uint32)((float32)*pi * (4294967295.0f/7.0f)); }
void ConvertScaleTruncate_Crumb_To_uint32 (uint32* pDest, uint8* pi) { *pDest = (uint32)*pi * (0xffffffff/3); }
void ConvertScaleTruncate_Bit_To_uint32 (uint32* pDest, uint8* pi) { *pDest = (uint32)*pi * 0xffffffff; }
void ConvertScaleTruncate_Sixbits_To_float32 (float32* pDest, uint8* pi) { *pDest = (float32)*pi * (1.0f/63.0f); }
void ConvertScaleTruncate_Nickle_To_float32 (float32* pDest, uint8* pi) { *pDest = (float32)*pi * (1.0f/31.0f); }
void ConvertScaleTruncate_Nybble_To_float32 (float32* pDest, uint8* pi) { *pDest = (float32)*pi * (1.0f/15.0f); }
void ConvertScaleTruncate_ThreeBits_To_float32 (float32* pDest, uint8* pi) { *pDest = (float32)*pi * (1.0f/7.0f); }
void ConvertScaleTruncate_Crumb_To_float32 (float32* pDest, uint8* pi) { *pDest = (float32)*pi * (1.0f/3.0f); }
void ConvertScaleTruncate_Bit_To_float32 (float32* pDest, uint8* pi) { *pDest = (float32)*pi * (1.0f/1.0f); }
void ConvertScaleTruncate_int32_To_Bit(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_int32_To_Crumb(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_int32_To_Nybble(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_int32_To_Nickle(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_int32_To_Sixbits(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_int16_To_Bit(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_int16_To_Crumb(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_int16_To_Nybble(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_int16_To_Nickle(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_int16_To_Sixbits(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_int8_To_Bit(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_int8_To_Crumb(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_int8_To_Nybble(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_int8_To_Nickle(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_int8_To_Sixbits(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_float32_To_Nickle(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_float32_To_Sixbits(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Bit_To_int32(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Bit_To_int16(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Bit_To_int8(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Bit_To_Bit(void* pvDest, void* pvSource) { *(uint8*)pvDest = (*(uint8*)pvSource) & 0x01; }
void ConvertScaleTruncate_Bit_To_Crumb(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Bit_To_Nybble(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Bit_To_Nickle(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Bit_To_Sixbits(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Crumb_To_int32(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Crumb_To_int16(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Crumb_To_int8(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Crumb_To_Bit(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Crumb_To_Crumb(void* pvDest, void* pvSource) { *(uint8*)pvDest = (*(uint8*)pvSource) & 0x03; }
void ConvertScaleTruncate_Crumb_To_Nybble(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Crumb_To_Nickle(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Crumb_To_Sixbits(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Nybble_To_int32(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Nybble_To_int16(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Nybble_To_int8(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Nybble_To_Bit(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Nybble_To_Crumb(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Nybble_To_Nybble(void* pvDest, void* pvSource) { *(uint8*)pvDest = (*(uint8*)pvSource) & 0x0f; }
void ConvertScaleTruncate_Nybble_To_Nickle(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Nybble_To_Sixbits(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Nickle_To_int32(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Nickle_To_int16(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Nickle_To_int8(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Nickle_To_Bit(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Nickle_To_Crumb(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Nickle_To_Nybble(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Nickle_To_Nickle(void* pvDest, void* pvSource) { *(uint8*)pvDest = (*(uint8*)pvSource) & 0x1f; }
void ConvertScaleTruncate_Nickle_To_Sixbits(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Sixbits_To_int32(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Sixbits_To_int16(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Sixbits_To_int8(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Sixbits_To_Bit(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Sixbits_To_Crumb(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Sixbits_To_Nybble(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Sixbits_To_Nickle(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Sixbits_To_Sixbits(void* pvDest, void* pvSource) { *(uint8*)pvDest = (*(uint8*)pvSource) & 0x3f; }
void ConvertScaleTruncate_int64_To_Bit(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_int64_To_Crumb(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_int64_To_Nybble(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_int64_To_Nickle(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_int64_To_Sixbits(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_float64_To_Nickle(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_float64_To_Sixbits(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_uint64_To_Bit(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_uint64_To_Crumb(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_uint64_To_Nybble(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_uint64_To_Nickle(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_uint64_To_Sixbits(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Bit_To_int64(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Bit_To_float64(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Bit_To_uint64(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Crumb_To_int64(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Tribble_To_int64(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Crumb_To_float64(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Crumb_To_uint64(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Nybble_To_int64(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Nybble_To_float64(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Nybble_To_uint64(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Nickle_To_int64(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Nickle_To_float64(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Nickle_To_uint64(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Sixbits_To_int64(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Sixbits_To_float64(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Sixbits_To_uint64(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Tribble_To_int32(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Tribble_To_int16(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Tribble_To_int8(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Tribble_To_float32(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Tribble_To_float64(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Tribble_To_uint64(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Tribble_To_uint32(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Tribble_To_uint16(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Tribble_To_uint8(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Tribble_To_Bit(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Tribble_To_Nybble(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Tribble_To_Nickle(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConvertScaleTruncate_Tribble_To_Sixbits(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types"); }
void ConversionInvalid(void* pvDest, void* pvSource) { gcUserError.Set("Conversion not defined for types (invalid)."); }
void CTypeConverter::Init(void)
{
int32 iDest;
int32 iSource;
for (iDest = 0; iDest < PRIMTIVE_CONVERTER_END; iDest++)
{
for (iSource = 0; iSource < PRIMTIVE_CONVERTER_END; iSource++)
{
mapvScaleTuncateConversion[iDest][iSource] = ConversionInvalid;
}
}
mapvScaleTuncateConversion[PT_int64][PT_int64] = (ConversionFunc)&ConvertScaleTruncate_int64_To_int64;
mapvScaleTuncateConversion[PT_int32][PT_int64] = (ConversionFunc)&ConvertScaleTruncate_int64_To_int32;
mapvScaleTuncateConversion[PT_int16][PT_int64] = (ConversionFunc)&ConvertScaleTruncate_int64_To_int16;
mapvScaleTuncateConversion[PT_char8][PT_int64] = (ConversionFunc)&ConvertScaleTruncate_int64_To_int8;
mapvScaleTuncateConversion[PT_int8][PT_int64] = (ConversionFunc)&ConvertScaleTruncate_int64_To_int8;
mapvScaleTuncateConversion[PT_float32][PT_int64] = (ConversionFunc)&ConvertScaleTruncate_int64_To_float32;
mapvScaleTuncateConversion[PT_float64][PT_int64] = (ConversionFunc)&ConvertScaleTruncate_int64_To_float64;
mapvScaleTuncateConversion[PT_uint64][PT_int64] = (ConversionFunc)&ConvertScaleTruncate_int64_To_uint64;
mapvScaleTuncateConversion[PT_uint32][PT_int64] = (ConversionFunc)&ConvertScaleTruncate_int64_To_uint32;
mapvScaleTuncateConversion[PT_uint16][PT_int64] = (ConversionFunc)&ConvertScaleTruncate_int64_To_uint16;
mapvScaleTuncateConversion[PT_uint8][PT_int64] = (ConversionFunc)&ConvertScaleTruncate_int64_To_uint8;
mapvScaleTuncateConversion[PT_bit][PT_int64] = (ConversionFunc)&ConvertScaleTruncate_int64_To_Bit;
mapvScaleTuncateConversion[PT_crumb][PT_int64] = (ConversionFunc)&ConvertScaleTruncate_int64_To_Crumb;
mapvScaleTuncateConversion[PT_tribble][PT_int64] = (ConversionFunc)&ConvertScaleTruncate_int64_To_Tribble;
mapvScaleTuncateConversion[PT_nybble][PT_int64] = (ConversionFunc)&ConvertScaleTruncate_int64_To_Nybble;
mapvScaleTuncateConversion[PT_nickle][PT_int64] = (ConversionFunc)&ConvertScaleTruncate_int64_To_Nickle;
mapvScaleTuncateConversion[PT_sixbits][PT_int64] = (ConversionFunc)&ConvertScaleTruncate_int64_To_Sixbits;
mapvScaleTuncateConversion[PT_int64][PT_int32] = (ConversionFunc)&ConvertScaleTruncate_int32_To_int64;
mapvScaleTuncateConversion[PT_int32][PT_int32] = (ConversionFunc)&ConvertScaleTruncate_int32_To_int32;
mapvScaleTuncateConversion[PT_int16][PT_int32] = (ConversionFunc)&ConvertScaleTruncate_int32_To_int16;
mapvScaleTuncateConversion[PT_char8][PT_int32] = (ConversionFunc)&ConvertScaleTruncate_int32_To_int8;
mapvScaleTuncateConversion[PT_int8][PT_int32] = (ConversionFunc)&ConvertScaleTruncate_int32_To_int8;
mapvScaleTuncateConversion[PT_float32][PT_int32] = (ConversionFunc)&ConvertScaleTruncate_int32_To_float32;
mapvScaleTuncateConversion[PT_float64][PT_int32] = (ConversionFunc)&ConvertScaleTruncate_int32_To_float64;
mapvScaleTuncateConversion[PT_uint64][PT_int32] = (ConversionFunc)&ConvertScaleTruncate_int32_To_uint64;
mapvScaleTuncateConversion[PT_uint32][PT_int32] = (ConversionFunc)&ConvertScaleTruncate_int32_To_uint32;
mapvScaleTuncateConversion[PT_uint16][PT_int32] = (ConversionFunc)&ConvertScaleTruncate_int32_To_uint16;
mapvScaleTuncateConversion[PT_uint8][PT_int32] = (ConversionFunc)&ConvertScaleTruncate_int32_To_uint8;
mapvScaleTuncateConversion[PT_bit][PT_int32] = (ConversionFunc)&ConvertScaleTruncate_int32_To_Bit;
mapvScaleTuncateConversion[PT_crumb][PT_int32] = (ConversionFunc)&ConvertScaleTruncate_int32_To_Crumb;
mapvScaleTuncateConversion[PT_tribble][PT_int32] = (ConversionFunc)&ConvertScaleTruncate_int32_To_Tribble;
mapvScaleTuncateConversion[PT_nybble][PT_int32] = (ConversionFunc)&ConvertScaleTruncate_int32_To_Nybble;
mapvScaleTuncateConversion[PT_nickle][PT_int32] = (ConversionFunc)&ConvertScaleTruncate_int32_To_Nickle;
mapvScaleTuncateConversion[PT_sixbits][PT_int32] = (ConversionFunc)&ConvertScaleTruncate_int32_To_Sixbits;
mapvScaleTuncateConversion[PT_int64][PT_int16] = (ConversionFunc)&ConvertScaleTruncate_int16_To_int64;
mapvScaleTuncateConversion[PT_int32][PT_int16] = (ConversionFunc)&ConvertScaleTruncate_int16_To_int32;
mapvScaleTuncateConversion[PT_int16][PT_int16] = (ConversionFunc)&ConvertScaleTruncate_int16_To_int16;
mapvScaleTuncateConversion[PT_char8][PT_int16] = (ConversionFunc)&ConvertScaleTruncate_int16_To_int8;
mapvScaleTuncateConversion[PT_int8][PT_int16] = (ConversionFunc)&ConvertScaleTruncate_int16_To_int8;
mapvScaleTuncateConversion[PT_float32][PT_int16] = (ConversionFunc)&ConvertScaleTruncate_int16_To_float32;
mapvScaleTuncateConversion[PT_float64][PT_int16] = (ConversionFunc)&ConvertScaleTruncate_int16_To_float64;
mapvScaleTuncateConversion[PT_uint64][PT_int16] = (ConversionFunc)&ConvertScaleTruncate_int16_To_uint64;
mapvScaleTuncateConversion[PT_uint32][PT_int16] = (ConversionFunc)&ConvertScaleTruncate_int16_To_uint32;
mapvScaleTuncateConversion[PT_uint16][PT_int16] = (ConversionFunc)&ConvertScaleTruncate_int16_To_uint16;
mapvScaleTuncateConversion[PT_uint8][PT_int16] = (ConversionFunc)&ConvertScaleTruncate_int16_To_uint8;
mapvScaleTuncateConversion[PT_bit][PT_int16] = (ConversionFunc)&ConvertScaleTruncate_int16_To_Bit;
mapvScaleTuncateConversion[PT_crumb][PT_int16] = (ConversionFunc)&ConvertScaleTruncate_int16_To_Crumb;
mapvScaleTuncateConversion[PT_tribble][PT_int16] = (ConversionFunc)&ConvertScaleTruncate_int16_To_Tribble;
mapvScaleTuncateConversion[PT_nybble][PT_int16] = (ConversionFunc)&ConvertScaleTruncate_int16_To_Nybble;
mapvScaleTuncateConversion[PT_nickle][PT_int16] = (ConversionFunc)&ConvertScaleTruncate_int16_To_Nickle;
mapvScaleTuncateConversion[PT_sixbits][PT_int16] = (ConversionFunc)&ConvertScaleTruncate_int16_To_Sixbits;
mapvScaleTuncateConversion[PT_int64][PT_char8] = (ConversionFunc)&ConvertScaleTruncate_int8_To_int64;
mapvScaleTuncateConversion[PT_int32][PT_char8] = (ConversionFunc)&ConvertScaleTruncate_int8_To_int32;
mapvScaleTuncateConversion[PT_int16][PT_char8] = (ConversionFunc)&ConvertScaleTruncate_int8_To_int16;
mapvScaleTuncateConversion[PT_char8][PT_char8] = (ConversionFunc)&ConvertScaleTruncate_int8_To_int8;
mapvScaleTuncateConversion[PT_int8][PT_char8] = (ConversionFunc)&ConvertScaleTruncate_int8_To_int8;
mapvScaleTuncateConversion[PT_float32][PT_char8] = (ConversionFunc)&ConvertScaleTruncate_int8_To_float32;
mapvScaleTuncateConversion[PT_float64][PT_char8] = (ConversionFunc)&ConvertScaleTruncate_int8_To_float64;
mapvScaleTuncateConversion[PT_uint64][PT_char8] = (ConversionFunc)&ConvertScaleTruncate_int8_To_uint64;
mapvScaleTuncateConversion[PT_uint32][PT_char8] = (ConversionFunc)&ConvertScaleTruncate_int8_To_uint32;
mapvScaleTuncateConversion[PT_uint16][PT_char8] = (ConversionFunc)&ConvertScaleTruncate_int8_To_uint16;
mapvScaleTuncateConversion[PT_uint8][PT_char8] = (ConversionFunc)&ConvertScaleTruncate_int8_To_uint8;
mapvScaleTuncateConversion[PT_bit][PT_char8] = (ConversionFunc)&ConvertScaleTruncate_int8_To_Bit;
mapvScaleTuncateConversion[PT_crumb][PT_char8] = (ConversionFunc)&ConvertScaleTruncate_int8_To_Crumb;
mapvScaleTuncateConversion[PT_tribble][PT_char8] = (ConversionFunc)&ConvertScaleTruncate_int8_To_Tribble;
mapvScaleTuncateConversion[PT_nybble][PT_char8] = (ConversionFunc)&ConvertScaleTruncate_int8_To_Nybble;
mapvScaleTuncateConversion[PT_nickle][PT_char8] = (ConversionFunc)&ConvertScaleTruncate_int8_To_Nickle;
mapvScaleTuncateConversion[PT_sixbits][PT_char8] = (ConversionFunc)&ConvertScaleTruncate_int8_To_Sixbits;
mapvScaleTuncateConversion[PT_int64][PT_int8] = (ConversionFunc)&ConvertScaleTruncate_int8_To_int64;
mapvScaleTuncateConversion[PT_int32][PT_int8] = (ConversionFunc)&ConvertScaleTruncate_int8_To_int32;
mapvScaleTuncateConversion[PT_int16][PT_int8] = (ConversionFunc)&ConvertScaleTruncate_int8_To_int16;
mapvScaleTuncateConversion[PT_int8][PT_int8] = (ConversionFunc)&ConvertScaleTruncate_int8_To_int8;
mapvScaleTuncateConversion[PT_float32][PT_int8] = (ConversionFunc)&ConvertScaleTruncate_int8_To_float32;
mapvScaleTuncateConversion[PT_float64][PT_int8] = (ConversionFunc)&ConvertScaleTruncate_int8_To_float64;
mapvScaleTuncateConversion[PT_uint64][PT_int8] = (ConversionFunc)&ConvertScaleTruncate_int8_To_uint64;
mapvScaleTuncateConversion[PT_uint32][PT_int8] = (ConversionFunc)&ConvertScaleTruncate_int8_To_uint32;
mapvScaleTuncateConversion[PT_uint16][PT_int8] = (ConversionFunc)&ConvertScaleTruncate_int8_To_uint16;
mapvScaleTuncateConversion[PT_uint8][PT_int8] = (ConversionFunc)&ConvertScaleTruncate_int8_To_uint8;
mapvScaleTuncateConversion[PT_bit][PT_int8] = (ConversionFunc)&ConvertScaleTruncate_int8_To_Bit;
mapvScaleTuncateConversion[PT_crumb][PT_int8] = (ConversionFunc)&ConvertScaleTruncate_int8_To_Crumb;
mapvScaleTuncateConversion[PT_tribble][PT_int8] = (ConversionFunc)&ConvertScaleTruncate_int8_To_Tribble;
mapvScaleTuncateConversion[PT_nybble][PT_int8] = (ConversionFunc)&ConvertScaleTruncate_int8_To_Nybble;
mapvScaleTuncateConversion[PT_nickle][PT_int8] = (ConversionFunc)&ConvertScaleTruncate_int8_To_Nickle;
mapvScaleTuncateConversion[PT_sixbits][PT_int8] = (ConversionFunc)&ConvertScaleTruncate_int8_To_Sixbits;
mapvScaleTuncateConversion[PT_int64][PT_float32] = (ConversionFunc)&ConvertScaleTruncate_float32_To_int64;
mapvScaleTuncateConversion[PT_int32][PT_float32] = (ConversionFunc)&ConvertScaleTruncate_float32_To_int32;
mapvScaleTuncateConversion[PT_int16][PT_float32] = (ConversionFunc)&ConvertScaleTruncate_float32_To_int16;
mapvScaleTuncateConversion[PT_char8][PT_float32] = (ConversionFunc)&ConvertScaleTruncate_float32_To_int8;
mapvScaleTuncateConversion[PT_int8][PT_float32] = (ConversionFunc)&ConvertScaleTruncate_float32_To_int8;
mapvScaleTuncateConversion[PT_float32][PT_float32] = (ConversionFunc)&ConvertScaleTruncate_float32_To_float32;
mapvScaleTuncateConversion[PT_float64][PT_float32] = (ConversionFunc)&ConvertScaleTruncate_float32_To_float64;
mapvScaleTuncateConversion[PT_uint64][PT_float32] = (ConversionFunc)&ConvertScaleTruncate_float32_To_uint64;
mapvScaleTuncateConversion[PT_uint32][PT_float32] = (ConversionFunc)&ConvertScaleTruncate_float32_To_uint32;
mapvScaleTuncateConversion[PT_uint16][PT_float32] = (ConversionFunc)&ConvertScaleTruncate_float32_To_uint16;
mapvScaleTuncateConversion[PT_uint8][PT_float32] = (ConversionFunc)&ConvertScaleTruncate_float32_To_uint8;
mapvScaleTuncateConversion[PT_bit][PT_float32] = (ConversionFunc)&ConvertScaleTruncate_float32_To_Bit;
mapvScaleTuncateConversion[PT_crumb][PT_float32] = (ConversionFunc)&ConvertScaleTruncate_float32_To_Crumb;
mapvScaleTuncateConversion[PT_tribble][PT_float32] = (ConversionFunc)&ConvertScaleTruncate_float32_To_Tribble;
mapvScaleTuncateConversion[PT_nybble][PT_float32] = (ConversionFunc)&ConvertScaleTruncate_float32_To_Nybble;
mapvScaleTuncateConversion[PT_nickle][PT_float32] = (ConversionFunc)&ConvertScaleTruncate_float32_To_Nickle;
mapvScaleTuncateConversion[PT_sixbits][PT_float32] = (ConversionFunc)&ConvertScaleTruncate_float32_To_Sixbits;
mapvScaleTuncateConversion[PT_int64][PT_float64] = (ConversionFunc)&ConvertScaleTruncate_float64_To_int64;
mapvScaleTuncateConversion[PT_int32][PT_float64] = (ConversionFunc)&ConvertScaleTruncate_float64_To_int32;
mapvScaleTuncateConversion[PT_int16][PT_float64] = (ConversionFunc)&ConvertScaleTruncate_float64_To_int16;
mapvScaleTuncateConversion[PT_char8][PT_float64] = (ConversionFunc)&ConvertScaleTruncate_float64_To_int8;
mapvScaleTuncateConversion[PT_int8][PT_float64] = (ConversionFunc)&ConvertScaleTruncate_float64_To_int8;
mapvScaleTuncateConversion[PT_float32][PT_float64] = (ConversionFunc)&ConvertScaleTruncate_float64_To_float32;
mapvScaleTuncateConversion[PT_float64][PT_float64] = (ConversionFunc)&ConvertScaleTruncate_float64_To_float64;
mapvScaleTuncateConversion[PT_uint64][PT_float64] = (ConversionFunc)&ConvertScaleTruncate_float64_To_uint64;
mapvScaleTuncateConversion[PT_uint32][PT_float64] = (ConversionFunc)&ConvertScaleTruncate_float64_To_uint32;
mapvScaleTuncateConversion[PT_uint16][PT_float64] = (ConversionFunc)&ConvertScaleTruncate_float64_To_uint16;
mapvScaleTuncateConversion[PT_uint8][PT_float64] = (ConversionFunc)&ConvertScaleTruncate_float64_To_uint8;
mapvScaleTuncateConversion[PT_bit][PT_float64] = (ConversionFunc)&ConvertScaleTruncate_float64_To_Bit;
mapvScaleTuncateConversion[PT_crumb][PT_float64] = (ConversionFunc)&ConvertScaleTruncate_float64_To_Crumb;
mapvScaleTuncateConversion[PT_tribble][PT_float64] = (ConversionFunc)&ConvertScaleTruncate_float64_To_Tribble;
mapvScaleTuncateConversion[PT_nybble][PT_float64] = (ConversionFunc)&ConvertScaleTruncate_float64_To_Nybble;
mapvScaleTuncateConversion[PT_nickle][PT_float64] = (ConversionFunc)&ConvertScaleTruncate_float64_To_Nickle;
mapvScaleTuncateConversion[PT_sixbits][PT_float64] = (ConversionFunc)&ConvertScaleTruncate_float64_To_Sixbits;
mapvScaleTuncateConversion[PT_int64][PT_uint64] = (ConversionFunc)&ConvertScaleTruncate_uint64_To_int64;
mapvScaleTuncateConversion[PT_int32][PT_uint64] = (ConversionFunc)&ConvertScaleTruncate_uint64_To_int32;
mapvScaleTuncateConversion[PT_int16][PT_uint64] = (ConversionFunc)&ConvertScaleTruncate_uint64_To_int16;
mapvScaleTuncateConversion[PT_char8][PT_uint64] = (ConversionFunc)&ConvertScaleTruncate_uint64_To_int8;
mapvScaleTuncateConversion[PT_int8][PT_uint64] = (ConversionFunc)&ConvertScaleTruncate_uint64_To_int8;
mapvScaleTuncateConversion[PT_float32][PT_uint64] = (ConversionFunc)&ConvertScaleTruncate_uint64_To_float32;
mapvScaleTuncateConversion[PT_float64][PT_uint64] = (ConversionFunc)&ConvertScaleTruncate_uint64_To_float64;
mapvScaleTuncateConversion[PT_uint64][PT_uint64] = (ConversionFunc)&ConvertScaleTruncate_uint64_To_uint64;
mapvScaleTuncateConversion[PT_uint32][PT_uint64] = (ConversionFunc)&ConvertScaleTruncate_uint64_To_uint32;
mapvScaleTuncateConversion[PT_uint16][PT_uint64] = (ConversionFunc)&ConvertScaleTruncate_uint64_To_uint16;
mapvScaleTuncateConversion[PT_uint8][PT_uint64] = (ConversionFunc)&ConvertScaleTruncate_uint64_To_uint8;
mapvScaleTuncateConversion[PT_bit][PT_uint64] = (ConversionFunc)&ConvertScaleTruncate_uint64_To_Bit;
mapvScaleTuncateConversion[PT_crumb][PT_uint64] = (ConversionFunc)&ConvertScaleTruncate_uint64_To_Crumb;
mapvScaleTuncateConversion[PT_tribble][PT_uint64] = (ConversionFunc)&ConvertScaleTruncate_uint64_To_Tribble;
mapvScaleTuncateConversion[PT_nybble][PT_uint64] = (ConversionFunc)&ConvertScaleTruncate_uint64_To_Nybble;
mapvScaleTuncateConversion[PT_nickle][PT_uint64] = (ConversionFunc)&ConvertScaleTruncate_uint64_To_Nickle;
mapvScaleTuncateConversion[PT_sixbits][PT_uint64] = (ConversionFunc)&ConvertScaleTruncate_uint64_To_Sixbits;
mapvScaleTuncateConversion[PT_int64][PT_uint32] = (ConversionFunc)&ConvertScaleTruncate_uint32_To_int64;
mapvScaleTuncateConversion[PT_int32][PT_uint32] = (ConversionFunc)&ConvertScaleTruncate_uint32_To_int32;
mapvScaleTuncateConversion[PT_int16][PT_uint32] = (ConversionFunc)&ConvertScaleTruncate_uint32_To_int16;
mapvScaleTuncateConversion[PT_char8][PT_uint32] = (ConversionFunc)&ConvertScaleTruncate_uint32_To_int8;
mapvScaleTuncateConversion[PT_int8][PT_uint32] = (ConversionFunc)&ConvertScaleTruncate_uint32_To_int8;
mapvScaleTuncateConversion[PT_float32][PT_uint32] = (ConversionFunc)&ConvertScaleTruncate_uint32_To_float32;
mapvScaleTuncateConversion[PT_float64][PT_uint32] = (ConversionFunc)&ConvertScaleTruncate_uint32_To_float64;
mapvScaleTuncateConversion[PT_uint64][PT_uint32] = (ConversionFunc)&ConvertScaleTruncate_uint32_To_uint64;
mapvScaleTuncateConversion[PT_uint32][PT_uint32] = (ConversionFunc)&ConvertScaleTruncate_uint32_To_uint32;
mapvScaleTuncateConversion[PT_uint16][PT_uint32] = (ConversionFunc)&ConvertScaleTruncate_uint32_To_uint16;
mapvScaleTuncateConversion[PT_uint8][PT_uint32] = (ConversionFunc)&ConvertScaleTruncate_uint32_To_uint8;
mapvScaleTuncateConversion[PT_bit][PT_uint32] = (ConversionFunc)&ConvertScaleTruncate_uint32_To_Bit;
mapvScaleTuncateConversion[PT_crumb][PT_uint32] = (ConversionFunc)&ConvertScaleTruncate_uint32_To_Crumb;
mapvScaleTuncateConversion[PT_tribble][PT_uint32] = (ConversionFunc)&ConvertScaleTruncate_uint32_To_Tribble;
mapvScaleTuncateConversion[PT_nybble][PT_uint32] = (ConversionFunc)&ConvertScaleTruncate_uint32_To_Nybble;
mapvScaleTuncateConversion[PT_nickle][PT_uint32] = (ConversionFunc)&ConvertScaleTruncate_uint32_To_Nickle;
mapvScaleTuncateConversion[PT_sixbits][PT_uint32] = (ConversionFunc)&ConvertScaleTruncate_uint32_To_Sixbits;
mapvScaleTuncateConversion[PT_int64][PT_uint16] = (ConversionFunc)&ConvertScaleTruncate_uint16_To_int64;
mapvScaleTuncateConversion[PT_int32][PT_uint16] = (ConversionFunc)&ConvertScaleTruncate_uint16_To_int32;
mapvScaleTuncateConversion[PT_int16][PT_uint16] = (ConversionFunc)&ConvertScaleTruncate_uint16_To_int16;
mapvScaleTuncateConversion[PT_char8][PT_uint16] = (ConversionFunc)&ConvertScaleTruncate_uint16_To_int8;
mapvScaleTuncateConversion[PT_int8][PT_uint16] = (ConversionFunc)&ConvertScaleTruncate_uint16_To_int8;
mapvScaleTuncateConversion[PT_float32][PT_uint16] = (ConversionFunc)&ConvertScaleTruncate_uint16_To_float32;
mapvScaleTuncateConversion[PT_float64][PT_uint16] = (ConversionFunc)&ConvertScaleTruncate_uint16_To_float64;
mapvScaleTuncateConversion[PT_uint64][PT_uint16] = (ConversionFunc)&ConvertScaleTruncate_uint16_To_uint64;
mapvScaleTuncateConversion[PT_uint32][PT_uint16] = (ConversionFunc)&ConvertScaleTruncate_uint16_To_uint32;
mapvScaleTuncateConversion[PT_uint16][PT_uint16] = (ConversionFunc)&ConvertScaleTruncate_uint16_To_uint16;
mapvScaleTuncateConversion[PT_uint8][PT_uint16] = (ConversionFunc)&ConvertScaleTruncate_uint16_To_uint8;
mapvScaleTuncateConversion[PT_bit][PT_uint16] = (ConversionFunc)&ConvertScaleTruncate_uint16_To_Bit;
mapvScaleTuncateConversion[PT_crumb][PT_uint16] = (ConversionFunc)&ConvertScaleTruncate_uint16_To_Crumb;
mapvScaleTuncateConversion[PT_tribble][PT_uint16] = (ConversionFunc)&ConvertScaleTruncate_uint16_To_Tribble;
mapvScaleTuncateConversion[PT_nybble][PT_uint16] = (ConversionFunc)&ConvertScaleTruncate_uint16_To_Nybble;
mapvScaleTuncateConversion[PT_nickle][PT_uint16] = (ConversionFunc)&ConvertScaleTruncate_uint16_To_Nickle;
mapvScaleTuncateConversion[PT_sixbits][PT_uint16] = (ConversionFunc)&ConvertScaleTruncate_uint16_To_Sixbits;
mapvScaleTuncateConversion[PT_int64][PT_uint8] = (ConversionFunc)&ConvertScaleTruncate_uint8_To_int64;
mapvScaleTuncateConversion[PT_int32][PT_uint8] = (ConversionFunc)&ConvertScaleTruncate_uint8_To_int32;
mapvScaleTuncateConversion[PT_int16][PT_uint8] = (ConversionFunc)&ConvertScaleTruncate_uint8_To_int16;
mapvScaleTuncateConversion[PT_char8][PT_uint8] = (ConversionFunc)&ConvertScaleTruncate_uint8_To_int8;
mapvScaleTuncateConversion[PT_int8][PT_uint8] = (ConversionFunc)&ConvertScaleTruncate_uint8_To_int8;
mapvScaleTuncateConversion[PT_float32][PT_uint8] = (ConversionFunc)&ConvertScaleTruncate_uint8_To_float32;
mapvScaleTuncateConversion[PT_float64][PT_uint8] = (ConversionFunc)&ConvertScaleTruncate_uint8_To_float64;
mapvScaleTuncateConversion[PT_uint64][PT_uint8] = (ConversionFunc)&ConvertScaleTruncate_uint8_To_uint64;
mapvScaleTuncateConversion[PT_uint32][PT_uint8] = (ConversionFunc)&ConvertScaleTruncate_uint8_To_uint32;
mapvScaleTuncateConversion[PT_uint16][PT_uint8] = (ConversionFunc)&ConvertScaleTruncate_uint8_To_uint16;
mapvScaleTuncateConversion[PT_uint8][PT_uint8] = (ConversionFunc)&ConvertScaleTruncate_uint8_To_uint8;
mapvScaleTuncateConversion[PT_bit][PT_uint8] = (ConversionFunc)&ConvertScaleTruncate_uint8_To_Bit;
mapvScaleTuncateConversion[PT_crumb][PT_uint8] = (ConversionFunc)&ConvertScaleTruncate_uint8_To_Crumb;
mapvScaleTuncateConversion[PT_tribble][PT_uint8] = (ConversionFunc)&ConvertScaleTruncate_uint8_To_Tribble;
mapvScaleTuncateConversion[PT_nybble][PT_uint8] = (ConversionFunc)&ConvertScaleTruncate_uint8_To_Nybble;
mapvScaleTuncateConversion[PT_nickle][PT_uint8] = (ConversionFunc)&ConvertScaleTruncate_uint8_To_Nickle;
mapvScaleTuncateConversion[PT_sixbits][PT_uint8] = (ConversionFunc)&ConvertScaleTruncate_uint8_To_Sixbits;
mapvScaleTuncateConversion[PT_int64][PT_bit] = (ConversionFunc)&ConvertScaleTruncate_Bit_To_int64;
mapvScaleTuncateConversion[PT_int32][PT_bit] = (ConversionFunc)&ConvertScaleTruncate_Bit_To_int32;
mapvScaleTuncateConversion[PT_int16][PT_bit] = (ConversionFunc)&ConvertScaleTruncate_Bit_To_int16;
mapvScaleTuncateConversion[PT_char8][PT_bit] = (ConversionFunc)&ConvertScaleTruncate_Bit_To_int8;
mapvScaleTuncateConversion[PT_int8][PT_bit] = (ConversionFunc)&ConvertScaleTruncate_Bit_To_int8;
mapvScaleTuncateConversion[PT_float32][PT_bit] = (ConversionFunc)&ConvertScaleTruncate_Bit_To_float32;
mapvScaleTuncateConversion[PT_float64][PT_bit] = (ConversionFunc)&ConvertScaleTruncate_Bit_To_float64;
mapvScaleTuncateConversion[PT_uint64][PT_bit] = (ConversionFunc)&ConvertScaleTruncate_Bit_To_uint64;
mapvScaleTuncateConversion[PT_uint32][PT_bit] = (ConversionFunc)&ConvertScaleTruncate_Bit_To_uint32;
mapvScaleTuncateConversion[PT_uint16][PT_bit] = (ConversionFunc)&ConvertScaleTruncate_Bit_To_uint16;
mapvScaleTuncateConversion[PT_uint8][PT_bit] = (ConversionFunc)&ConvertScaleTruncate_Bit_To_uint8;
mapvScaleTuncateConversion[PT_bit][PT_bit] = (ConversionFunc)&ConvertScaleTruncate_Bit_To_Bit;
mapvScaleTuncateConversion[PT_crumb][PT_bit] = (ConversionFunc)&ConvertScaleTruncate_Bit_To_Crumb;
mapvScaleTuncateConversion[PT_tribble][PT_bit] = (ConversionFunc)&ConvertScaleTruncate_Bit_To_Tribble;
mapvScaleTuncateConversion[PT_nybble][PT_bit] = (ConversionFunc)&ConvertScaleTruncate_Bit_To_Nybble;
mapvScaleTuncateConversion[PT_nickle][PT_bit] = (ConversionFunc)&ConvertScaleTruncate_Bit_To_Nickle;
mapvScaleTuncateConversion[PT_sixbits][PT_bit] = (ConversionFunc)&ConvertScaleTruncate_Bit_To_Sixbits;
mapvScaleTuncateConversion[PT_int64][PT_crumb] = (ConversionFunc)&ConvertScaleTruncate_Crumb_To_int64;
mapvScaleTuncateConversion[PT_int32][PT_crumb] = (ConversionFunc)&ConvertScaleTruncate_Crumb_To_int32;
mapvScaleTuncateConversion[PT_int16][PT_crumb] = (ConversionFunc)&ConvertScaleTruncate_Crumb_To_int16;
mapvScaleTuncateConversion[PT_char8][PT_crumb] = (ConversionFunc)&ConvertScaleTruncate_Crumb_To_int8;
mapvScaleTuncateConversion[PT_int8][PT_crumb] = (ConversionFunc)&ConvertScaleTruncate_Crumb_To_int8;
mapvScaleTuncateConversion[PT_float32][PT_crumb] = (ConversionFunc)&ConvertScaleTruncate_Crumb_To_float32;
mapvScaleTuncateConversion[PT_float64][PT_crumb] = (ConversionFunc)&ConvertScaleTruncate_Crumb_To_float64;
mapvScaleTuncateConversion[PT_uint64][PT_crumb] = (ConversionFunc)&ConvertScaleTruncate_Crumb_To_uint64;
mapvScaleTuncateConversion[PT_uint32][PT_crumb] = (ConversionFunc)&ConvertScaleTruncate_Crumb_To_uint32;
mapvScaleTuncateConversion[PT_uint16][PT_crumb] = (ConversionFunc)&ConvertScaleTruncate_Crumb_To_uint16;
mapvScaleTuncateConversion[PT_uint8][PT_crumb] = (ConversionFunc)&ConvertScaleTruncate_Crumb_To_uint8;
mapvScaleTuncateConversion[PT_bit][PT_crumb] = (ConversionFunc)&ConvertScaleTruncate_Crumb_To_Bit;
mapvScaleTuncateConversion[PT_crumb][PT_crumb] = (ConversionFunc)&ConvertScaleTruncate_Crumb_To_Crumb;
mapvScaleTuncateConversion[PT_tribble][PT_crumb] = (ConversionFunc)&ConvertScaleTruncate_Crumb_To_Tribble;
mapvScaleTuncateConversion[PT_nybble][PT_crumb] = (ConversionFunc)&ConvertScaleTruncate_Crumb_To_Nybble;
mapvScaleTuncateConversion[PT_nickle][PT_crumb] = (ConversionFunc)&ConvertScaleTruncate_Crumb_To_Nickle;
mapvScaleTuncateConversion[PT_sixbits][PT_crumb] = (ConversionFunc)&ConvertScaleTruncate_Crumb_To_Sixbits;
mapvScaleTuncateConversion[PT_int64][PT_tribble] = (ConversionFunc)&ConvertScaleTruncate_Tribble_To_int64;
mapvScaleTuncateConversion[PT_int32][PT_tribble] = (ConversionFunc)&ConvertScaleTruncate_Tribble_To_int32;
mapvScaleTuncateConversion[PT_int16][PT_tribble] = (ConversionFunc)&ConvertScaleTruncate_Tribble_To_int16;
mapvScaleTuncateConversion[PT_char8][PT_tribble] = (ConversionFunc)&ConvertScaleTruncate_Tribble_To_int8;
mapvScaleTuncateConversion[PT_int8][PT_tribble] = (ConversionFunc)&ConvertScaleTruncate_Tribble_To_int8;
mapvScaleTuncateConversion[PT_float32][PT_tribble] = (ConversionFunc)&ConvertScaleTruncate_Tribble_To_float32;
mapvScaleTuncateConversion[PT_float64][PT_tribble] = (ConversionFunc)&ConvertScaleTruncate_Tribble_To_float64;
mapvScaleTuncateConversion[PT_uint64][PT_tribble] = (ConversionFunc)&ConvertScaleTruncate_Tribble_To_uint64;
mapvScaleTuncateConversion[PT_uint32][PT_tribble] = (ConversionFunc)&ConvertScaleTruncate_Tribble_To_uint32;
mapvScaleTuncateConversion[PT_uint16][PT_tribble] = (ConversionFunc)&ConvertScaleTruncate_Tribble_To_uint16;
mapvScaleTuncateConversion[PT_uint8][PT_tribble] = (ConversionFunc)&ConvertScaleTruncate_Tribble_To_uint8;
mapvScaleTuncateConversion[PT_bit][PT_tribble] = (ConversionFunc)&ConvertScaleTruncate_Tribble_To_Bit;
mapvScaleTuncateConversion[PT_crumb][PT_tribble] = (ConversionFunc)&ConvertScaleTruncate_Tribble_To_Crumb;
mapvScaleTuncateConversion[PT_tribble][PT_tribble] = (ConversionFunc)&ConvertScaleTruncate_Tribble_To_Tribble;
mapvScaleTuncateConversion[PT_nybble][PT_tribble] = (ConversionFunc)&ConvertScaleTruncate_Tribble_To_Nybble;
mapvScaleTuncateConversion[PT_nickle][PT_tribble] = (ConversionFunc)&ConvertScaleTruncate_Tribble_To_Nickle;
mapvScaleTuncateConversion[PT_sixbits][PT_tribble] = (ConversionFunc)&ConvertScaleTruncate_Tribble_To_Sixbits;
mapvScaleTuncateConversion[PT_int64][PT_nybble] = (ConversionFunc)&ConvertScaleTruncate_Nybble_To_int64;
mapvScaleTuncateConversion[PT_int32][PT_nybble] = (ConversionFunc)&ConvertScaleTruncate_Nybble_To_int32;
mapvScaleTuncateConversion[PT_int16][PT_nybble] = (ConversionFunc)&ConvertScaleTruncate_Nybble_To_int16;
mapvScaleTuncateConversion[PT_char8][PT_nybble] = (ConversionFunc)&ConvertScaleTruncate_Nybble_To_int8;
mapvScaleTuncateConversion[PT_int8][PT_nybble] = (ConversionFunc)&ConvertScaleTruncate_Nybble_To_int8;
mapvScaleTuncateConversion[PT_float32][PT_nybble] = (ConversionFunc)&ConvertScaleTruncate_Nybble_To_float32;
mapvScaleTuncateConversion[PT_float64][PT_nybble] = (ConversionFunc)&ConvertScaleTruncate_Nybble_To_float64;
mapvScaleTuncateConversion[PT_uint64][PT_nybble] = (ConversionFunc)&ConvertScaleTruncate_Nybble_To_uint64;
mapvScaleTuncateConversion[PT_uint32][PT_nybble] = (ConversionFunc)&ConvertScaleTruncate_Nybble_To_uint32;
mapvScaleTuncateConversion[PT_uint16][PT_nybble] = (ConversionFunc)&ConvertScaleTruncate_Nybble_To_uint16;
mapvScaleTuncateConversion[PT_uint8][PT_nybble] = (ConversionFunc)&ConvertScaleTruncate_Nybble_To_uint8;
mapvScaleTuncateConversion[PT_bit][PT_nybble] = (ConversionFunc)&ConvertScaleTruncate_Nybble_To_Bit;
mapvScaleTuncateConversion[PT_crumb][PT_nybble] = (ConversionFunc)&ConvertScaleTruncate_Nybble_To_Crumb;
mapvScaleTuncateConversion[PT_tribble][PT_nybble] = (ConversionFunc)&ConvertScaleTruncate_Nybble_To_Tribble;
mapvScaleTuncateConversion[PT_nybble][PT_nybble] = (ConversionFunc)&ConvertScaleTruncate_Nybble_To_Nybble;
mapvScaleTuncateConversion[PT_nickle][PT_nybble] = (ConversionFunc)&ConvertScaleTruncate_Nybble_To_Nickle;
mapvScaleTuncateConversion[PT_sixbits][PT_nybble] = (ConversionFunc)&ConvertScaleTruncate_Nybble_To_Sixbits;
mapvScaleTuncateConversion[PT_int64][PT_nickle] = (ConversionFunc)&ConvertScaleTruncate_Nickle_To_int64;
mapvScaleTuncateConversion[PT_int32][PT_nickle] = (ConversionFunc)&ConvertScaleTruncate_Nickle_To_int32;
mapvScaleTuncateConversion[PT_int16][PT_nickle] = (ConversionFunc)&ConvertScaleTruncate_Nickle_To_int16;
mapvScaleTuncateConversion[PT_char8][PT_nickle] = (ConversionFunc)&ConvertScaleTruncate_Nickle_To_int8;
mapvScaleTuncateConversion[PT_int8][PT_nickle] = (ConversionFunc)&ConvertScaleTruncate_Nickle_To_int8;
mapvScaleTuncateConversion[PT_float32][PT_nickle] = (ConversionFunc)&ConvertScaleTruncate_Nickle_To_float32;
mapvScaleTuncateConversion[PT_float64][PT_nickle] = (ConversionFunc)&ConvertScaleTruncate_Nickle_To_float64;
mapvScaleTuncateConversion[PT_uint64][PT_nickle] = (ConversionFunc)&ConvertScaleTruncate_Nickle_To_uint64;
mapvScaleTuncateConversion[PT_uint32][PT_nickle] = (ConversionFunc)&ConvertScaleTruncate_Nickle_To_uint32;
mapvScaleTuncateConversion[PT_uint16][PT_nickle] = (ConversionFunc)&ConvertScaleTruncate_Nickle_To_uint16;
mapvScaleTuncateConversion[PT_uint8][PT_nickle] = (ConversionFunc)&ConvertScaleTruncate_Nickle_To_uint8;
mapvScaleTuncateConversion[PT_bit][PT_nickle] = (ConversionFunc)&ConvertScaleTruncate_Nickle_To_Bit;
mapvScaleTuncateConversion[PT_crumb][PT_nickle] = (ConversionFunc)&ConvertScaleTruncate_Nickle_To_Crumb;
mapvScaleTuncateConversion[PT_tribble][PT_nickle] = (ConversionFunc)&ConvertScaleTruncate_Nickle_To_Tribble;
mapvScaleTuncateConversion[PT_nybble][PT_nickle] = (ConversionFunc)&ConvertScaleTruncate_Nickle_To_Nybble;
mapvScaleTuncateConversion[PT_nickle][PT_nickle] = (ConversionFunc)&ConvertScaleTruncate_Nickle_To_Nickle;
mapvScaleTuncateConversion[PT_sixbits][PT_nickle] = (ConversionFunc)&ConvertScaleTruncate_Nickle_To_Sixbits;
mapvScaleTuncateConversion[PT_int64][PT_sixbits] = (ConversionFunc)&ConvertScaleTruncate_Sixbits_To_int64;
mapvScaleTuncateConversion[PT_int32][PT_sixbits] = (ConversionFunc)&ConvertScaleTruncate_Sixbits_To_int32;
mapvScaleTuncateConversion[PT_int16][PT_sixbits] = (ConversionFunc)&ConvertScaleTruncate_Sixbits_To_int16;
mapvScaleTuncateConversion[PT_char8][PT_sixbits] = (ConversionFunc)&ConvertScaleTruncate_Sixbits_To_int8;
mapvScaleTuncateConversion[PT_int8][PT_sixbits] = (ConversionFunc)&ConvertScaleTruncate_Sixbits_To_int8;
mapvScaleTuncateConversion[PT_float32][PT_sixbits] = (ConversionFunc)&ConvertScaleTruncate_Sixbits_To_float32;
mapvScaleTuncateConversion[PT_float64][PT_sixbits] = (ConversionFunc)&ConvertScaleTruncate_Sixbits_To_float64;
mapvScaleTuncateConversion[PT_uint64][PT_sixbits] = (ConversionFunc)&ConvertScaleTruncate_Sixbits_To_uint64;
mapvScaleTuncateConversion[PT_uint32][PT_sixbits] = (ConversionFunc)&ConvertScaleTruncate_Sixbits_To_uint32;
mapvScaleTuncateConversion[PT_uint16][PT_sixbits] = (ConversionFunc)&ConvertScaleTruncate_Sixbits_To_uint16;
mapvScaleTuncateConversion[PT_uint8][PT_sixbits] = (ConversionFunc)&ConvertScaleTruncate_Sixbits_To_uint8;
mapvScaleTuncateConversion[PT_bit][PT_sixbits] = (ConversionFunc)&ConvertScaleTruncate_Sixbits_To_Bit;
mapvScaleTuncateConversion[PT_crumb][PT_sixbits] = (ConversionFunc)&ConvertScaleTruncate_Sixbits_To_Crumb;
mapvScaleTuncateConversion[PT_tribble][PT_sixbits] = (ConversionFunc)&ConvertScaleTruncate_Sixbits_To_Tribble;
mapvScaleTuncateConversion[PT_nybble][PT_sixbits] = (ConversionFunc)&ConvertScaleTruncate_Sixbits_To_Nybble;
mapvScaleTuncateConversion[PT_nickle][PT_sixbits] = (ConversionFunc)&ConvertScaleTruncate_Sixbits_To_Nickle;
mapvScaleTuncateConversion[PT_sixbits][PT_sixbits] = (ConversionFunc)&ConvertScaleTruncate_Sixbits_To_Sixbits;
}
void CTypeConverter::Kill(void)
{
}
void CTypeConverter::Do(EPrimitiveType eDest, void* pvDest, EPrimitiveType eSource, void* pvSource)
{
if ((eSource < PRIMTIVE_CONVERTER_END) && (eDest < PRIMTIVE_CONVERTER_END))
{
mapvScaleTuncateConversion[eDest][eSource](pvDest, pvSource);
return;
}
gcUserError.Set("Conversion not defined for types (out of bounds).");
}
void TypeConverterInit(void)
{
gcTypeConverter.Init();
}
void TypeConverterKill(void)
{
gcTypeConverter.Kill();
}
