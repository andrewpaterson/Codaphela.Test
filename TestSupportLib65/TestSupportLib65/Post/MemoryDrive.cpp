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
void* RemapSinglePointer(const void* pvPtr, ptrdiff iOffest);
__inline void* RemapSinglePointer(const void* pvPtr, ptrdiff iOffest)
{
return &((char*)pvPtr)[iOffest];
}
class CFileDrive
{
protected:
uint64 muiMaxSector;
uint32 muiSectorSize;
public:
void Init(uint32 uiSectorSize);
virtual void Kill(void) =0;
virtual bool Read(uint64 uiSector, void* pvData) =0;
virtual bool Read(uint64 uiSector, uint32 uiNumSectors, void* pvData) =0;
virtual bool Write(uint64 uiSector, void* pvData) =0;
virtual bool Write(uint64 uiSector, uint32 uiNumSectors, void* pvData) =0;
virtual bool Erase(uint64 uiStartSector, uint64 uiStopSectorInclusive) =0;
uint64 GetTotalSectors(void);
uint32 GetSectorSize(void);
virtual uint32 GetPageSize(void);
uint64 SetMaxSectorForTesting(uint64 uiMaxSector);
};
class CMemoryDrive : public CFileDrive
{
protected:
void* mpvData;
uint64 muiDataSize;
public:
bool Init(uint64 uiSizeInBytes, uint32 uiSectorSize);
void Kill(void);
bool Read(uint64 uiSector, void* pvData);
bool Read(uint64 uiSector, uint32 uiNumSectors, void* pvData);
bool Write(uint64 uiSector, void* pvData);
bool Write(uint64 uiSector, uint32 uiNumSectors, void* pvData);
bool Erase(uint64 uiStartSector, uint64 uiStopSectorInclusive);
bool Erase(void);
void* GetMemory(void);
};
bool CMemoryDrive::Init(uint64 uiSizeInBytes, uint32 uiSectorSize)
{
uint64 uiSectorCount;
uint64 uiSectorRemainder;
CFileDrive::Init(uiSectorSize);
uiSectorCount = uiSizeInBytes / uiSectorSize;
uiSectorRemainder = uiSizeInBytes % uiSectorSize;
mpvData = 0L;
if (uiSectorRemainder != 0)
{
uiSectorCount++;
}
muiDataSize = uiSectorCount * muiSectorSize;
mpvData = malloc((size)muiDataSize);
if (mpvData)
{
memset(mpvData, 0, (size)muiDataSize);
muiMaxSector = uiSectorCount;
return true;
}
else
{
return false;
}
}
void CMemoryDrive::Kill(void)
{
if (mpvData) { free(mpvData); mpvData = 0L; };
}
bool CMemoryDrive::Read(uint64 uiSector, void* pvData)
{
if (uiSector < muiMaxSector)
{
memcpy(pvData, RemapSinglePointer(mpvData, (size)(uiSector * muiSectorSize)), muiSectorSize);
return true;
}
else
{
return false;
}
}
bool CMemoryDrive::Read(uint64 uiSector, uint32 uiNumSectors, void* pvData)
{
uint64 uiEnd;
void* pvSource;
uiEnd = uiSector + uiNumSectors - 1;
if (uiSector >= muiMaxSector)
{
return false;
}
if (uiNumSectors == 0)
{
return true;
}
if (uiEnd >= muiMaxSector)
{
return false;
}
pvSource = RemapSinglePointer(mpvData, (size)(uiSector * muiSectorSize));
memcpy(pvData, pvSource, muiSectorSize * uiNumSectors);
return true;
}
bool CMemoryDrive::Write(uint64 uiSector, void* pvData)
{
if (uiSector < muiMaxSector)
{
memcpy(RemapSinglePointer(mpvData, (size)(uiSector * muiSectorSize)), pvData, muiSectorSize);
return true;
}
else
{
return false;
}
}
bool CMemoryDrive::Write(uint64 uiSector, uint32 uiNumSectors, void* pvData)
{
uint64 uiEnd;
uiEnd = uiSector + uiNumSectors - 1;
if (uiSector >= muiMaxSector)
{
return false;
}
if (uiNumSectors == 0)
{
return true;
}
if (uiEnd >= muiMaxSector)
{
return false;
}
memcpy(RemapSinglePointer(mpvData, (size)(uiSector * muiSectorSize)), pvData, muiSectorSize * uiNumSectors);
return true;
}
bool CMemoryDrive::Erase(uint64 uiStartSector, uint64 uiStopSectorInclusive)
{
if ((uiStartSector < muiMaxSector) && (uiStopSectorInclusive < muiMaxSector) && (uiStopSectorInclusive >= uiStartSector))
{
memset(RemapSinglePointer(mpvData, (ptrdiff_t)(uiStartSector * muiSectorSize)), 0, (size)(((uiStopSectorInclusive - uiStartSector) + 1) * muiSectorSize));
return true;
}
else
{
return false;
}
}
bool CMemoryDrive::Erase(void)
{
memset(mpvData, 0, (size)muiMaxSector * muiSectorSize);
return true;
}
void* CMemoryDrive::GetMemory(void)
{
return mpvData;
}
