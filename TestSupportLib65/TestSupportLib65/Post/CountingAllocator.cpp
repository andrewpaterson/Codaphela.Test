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
void* RemapSinglePointer(const void* pvPtr, ptrdiff iOffest);
__inline void* RemapSinglePointer(const void* pvPtr, ptrdiff iOffest)
{
return &((char*)pvPtr)[iOffest];
}
template<class T, class M>
M* HeaderGetData(T* pv)
{
if (pv == 0L)
{
return 0L;
}
return (M*)RemapSinglePointer(pv, sizeof(T));
}
template<class T, class M>
T* DataGetHeader(M* pv)
{
if (pv == 0L)
{
return 0L;
}
return (T*)RemapSinglePointer(pv, -(ptrdiff_t)sizeof(T));
}
class _CForceVirtualSuper1
{
virtual void _ForceVirtual1(void) {};
};
class _CForceVirtualSuper2
{
virtual void _ForceVirtual2(void) {};
};
class CConstructable : public _CForceVirtualSuper1, public _CForceVirtualSuper2
{
public:
virtual const char* ClassName(void) =0;
virtual size ClassSize(void) =0;
};
class CChars;
class CKillable
{
public:
virtual void Kill(void) =0;
virtual void Print(CChars* psz);
};
class CFileReader;
class CFileWriter;
template<class M>
class CArrayTemplatePtr;
typedef CArrayTemplatePtr<void> CArrayVoidPtr;
class CMallocator : public CConstructable, public CKillable
{
public:
virtual void* Malloc(lsize uiSize) =0;
virtual void* Malloc(lsize uiSize, char(** pacDebugName)[4]);
virtual void* Realloc(void* pv, lsize uiSize) =0;
virtual bool Free(void* pv) =0;
virtual size FreeMultiple(CArrayVoidPtr* pav);
virtual bool IsLocal(void) =0;
virtual size SizeOffset(void) =0;
virtual const char* ShortName(void) =0;
};
extern size guiMaxDebugAllocatorSize;
void InitAllocatorDebug(size uiMaxDebugAllocatorSize);
void KillAllocatorDebug(void);
CMallocator* ReadMallocator(CFileReader* pcFileReader);
bool WriteMallocator(CFileWriter* pcFileWriter, CMallocator* pcMalloc);
struct SCountingMemoryAllocation
{
size uiSize;
};
class CCountingAllocator : public CMallocator
{
protected:
CMallocator* mpcAlloc;
size mtUserSize;
size mtSystemSize;
public:
void Init(CMallocator* pcAlloc);
void Kill(void);
size AllocatedUserSize(void);
size AllocatedSystemSize(void);
void* Malloc(lsize uiSize);
void* Realloc(void* pv, lsize uiSize);
bool Free(void* pv);
const char* ClassName(void);
size ClassSize(void);
bool IsLocal(void);
size SizeOffset(void);
const char* ShortName(void);
};
void CCountingAllocator::Init(CMallocator* pcAlloc)
{
mpcAlloc = pcAlloc;
mtUserSize = 0;
mtSystemSize = 0;
}
void CCountingAllocator::Kill(void)
{
mtUserSize = 0;
mtSystemSize = 0;
mpcAlloc = 0L;
}
size CCountingAllocator::AllocatedUserSize(void)
{
return mtUserSize;
}
size CCountingAllocator::AllocatedSystemSize(void)
{
return mtSystemSize;
}
void* CCountingAllocator::Malloc(lsize uiSize)
{
SCountingMemoryAllocation* ps;
void* pv;
size tOffset;
size tAllocSize;
size tSystemSize;
tOffset = mpcAlloc->SizeOffset();
if (tOffset == 0)
{
tAllocSize = uiSize + sizeof(SCountingMemoryAllocation);
tSystemSize = tAllocSize;
}
else
{
tAllocSize = uiSize;
tSystemSize = uiSize + tOffset;
}
pv = mpcAlloc->Malloc(tAllocSize);
if (pv)
{
mtUserSize += uiSize;
mtSystemSize += tSystemSize;
if (tOffset == 0)
{
ps = (SCountingMemoryAllocation*)pv;
ps->uiSize = uiSize;
return HeaderGetData<SCountingMemoryAllocation, void>(ps);
}
}
return pv;
}
void* CCountingAllocator::Realloc(void* pv, lsize uiSize)
{
SCountingMemoryAllocation* ps;
size tOffset;
size tAllocSize;
size tSystemSize;
tOffset = mpcAlloc->SizeOffset();
if (tOffset == 0)
{
tAllocSize = uiSize + sizeof(SCountingMemoryAllocation);
tSystemSize = tAllocSize;
}
else
{
tAllocSize = uiSize;
tSystemSize = uiSize + tOffset;
}
if (pv)
{
if (tOffset == 0)
{
ps = DataGetHeader<SCountingMemoryAllocation, void>(pv);
mtUserSize -= ps->uiSize;
mtSystemSize -= (ps->uiSize + sizeof(SCountingMemoryAllocation));
}
else
{
ps = (SCountingMemoryAllocation*)RemapSinglePointer(pv, -(ptrdiff_t)tOffset);
mtUserSize -= ps->uiSize;
mtSystemSize -= (ps->uiSize + tOffset);
}
}
if (tOffset == 0)
{
ps = (SCountingMemoryAllocation*)mpcAlloc->Realloc(DataGetHeader<SCountingMemoryAllocation, void>(pv), tAllocSize);
if (ps)
{
mtUserSize += uiSize;
mtSystemSize += tSystemSize;
ps->uiSize = uiSize;
return HeaderGetData<SCountingMemoryAllocation, void>(ps);
}
return ps;
}
else
{
pv = mpcAlloc->Realloc(pv, tAllocSize);
if (pv)
{
mtUserSize += uiSize;
mtSystemSize += tSystemSize;
}
return pv;
}
}
bool CCountingAllocator::Free(void* pv)
{
SCountingMemoryAllocation* ps;
size tOffset;
tOffset = mpcAlloc->SizeOffset();
if (pv)
{
if (tOffset == 0)
{
ps = DataGetHeader<SCountingMemoryAllocation, void>(pv);
mtUserSize -= ps->uiSize;
mtSystemSize -= (ps->uiSize + sizeof(SCountingMemoryAllocation));
return mpcAlloc->Free(ps);
}
else
{
ps = (SCountingMemoryAllocation*)RemapSinglePointer(pv, -(ptrdiff_t)tOffset);
mtUserSize -= ps->uiSize;
mtSystemSize -= (ps->uiSize + tOffset);
return mpcAlloc->Free(pv);
}
}
return false;
}
const char* CCountingAllocator::ClassName(void)
{
return mpcAlloc->ClassName();
}
size CCountingAllocator::ClassSize(void)
{
return mpcAlloc->ClassSize();
}
bool CCountingAllocator::IsLocal(void)
{
return mpcAlloc->IsLocal();
}
size CCountingAllocator::SizeOffset(void)
{
size tOffset;
tOffset = mpcAlloc->SizeOffset();
if (tOffset == 0)
{
return sizeof(SCountingMemoryAllocation);
}
else
{
return tOffset;
}
}
const char* CCountingAllocator::ShortName(void)
{
return ClassName();
}
