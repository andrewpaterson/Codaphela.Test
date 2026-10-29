typedef int sig_atomic_t;
typedef void (*__sighandler_t)(int);
__sighandler_t signal(int iSignal, __sighandler_t fHandler);
int raise(int iSignal);
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
__sighandler_t gafSignalHandlers[16];
__sighandler_t signal(int iSignal, __sighandler_t fHandler)
{
__sighandler_t fPrevious;
if ((iSignal <= 0) || (iSignal >= 16))
{
return ((__sighandler_t)-1);
}
fPrevious = gafSignalHandlers[iSignal];
gafSignalHandlers[iSignal] = fHandler;
return fPrevious;
}
int raise(int iSignal)
{
__sighandler_t fHandler;
if ((iSignal <= 0) || (iSignal >= 16))
{
return -1;
}
fHandler = gafSignalHandlers[iSignal];
if (fHandler == ((__sighandler_t)1))
{
return 0;
}
if (fHandler == ((__sighandler_t)0))
{
_Exit(1);
}
gafSignalHandlers[iSignal] = ((__sighandler_t)0);
fHandler(iSignal);
return 0;
}
