typedef unsigned int size_t;
typedef int ptrdiff_t;
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
int rand(void);
void srand(unsigned int uiSeed);
void qsort(void* pvBase, size_t uiCount, size_t uiBytes, int (*fCompare)(const void*, const void*));
void abort(void);
void exit(int iStatus);
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
struct SHeapBlock
{
size_t uiSize;
SHeapBlock* psNext;
};
SHeapBlock* gpsFreeBlocks = 0;
char* gpcHeapTop = (char*)0x80000;
void* malloc(size_t uiBytes)
{
SHeapBlock* psBlock;
SHeapBlock* psPrevious;
SHeapBlock* psRest;
size_t uiSize;
uiSize = ((uiBytes + 3) & ~3) + sizeof(SHeapBlock);
psPrevious = 0;
for (psBlock = gpsFreeBlocks; psBlock; psBlock = psBlock->psNext)
{
if (psBlock->uiSize >= uiSize)
{
if (psBlock->uiSize >= uiSize + sizeof(SHeapBlock) + 4)
{
psRest = (SHeapBlock*)((char*)psBlock + uiSize);
psRest->uiSize = psBlock->uiSize - uiSize;
psRest->psNext = psBlock->psNext;
psBlock->uiSize = uiSize;
psBlock->psNext = psRest;
}
if (psPrevious)
{
psPrevious->psNext = psBlock->psNext;
}
else
{
gpsFreeBlocks = psBlock->psNext;
}
return (char*)psBlock + sizeof(SHeapBlock);
}
psPrevious = psBlock;
}
if (gpcHeapTop + uiSize > (char*)0x100000)
{
return 0;
}
psBlock = (SHeapBlock*)gpcHeapTop;
psBlock->uiSize = uiSize;
gpcHeapTop += uiSize;
return (char*)psBlock + sizeof(SHeapBlock);
}
void free(void* pv)
{
SHeapBlock* psBlock;
if (!pv)
{
return;
}
psBlock = (SHeapBlock*)((char*)pv - sizeof(SHeapBlock));
psBlock->psNext = gpsFreeBlocks;
gpsFreeBlocks = psBlock;
}
void* calloc(size_t uiCount, size_t uiBytes)
{
void* pv;
pv = malloc(uiCount * uiBytes);
if (pv)
{
memset(pv, 0, uiCount * uiBytes);
}
return pv;
}
void* realloc(void* pv, size_t uiBytes)
{
SHeapBlock* psBlock;
void* pvNew;
size_t uiOld;
if (!pv)
{
return malloc(uiBytes);
}
psBlock = (SHeapBlock*)((char*)pv - sizeof(SHeapBlock));
uiOld = psBlock->uiSize - sizeof(SHeapBlock);
if (uiOld >= uiBytes)
{
return pv;
}
pvNew = malloc(uiBytes);
if (pvNew)
{
memcpy(pvNew, pv, uiOld);
free(pv);
}
return pvNew;
}
int abs(int i)
{
return (i < 0) ? -i : i;
}
long labs(long i)
{
return (i < 0) ? -i : i;
}
long strtol(const char* sz, char** pszEnd, int iBase)
{
return (long)strtoul(sz, pszEnd, iBase);
}
unsigned long strtoul(const char* sz, char** pszEnd, int iBase)
{
unsigned long ulValue;
int iDigit;
bool bNegative;
while ((*sz == ' ') || (*sz == '\t') || (*sz == '\n') || (*sz == '\r'))
{
sz++;
}
bNegative = false;
if ((*sz == '-') || (*sz == '+'))
{
bNegative = *sz == '-';
sz++;
}
if (((iBase == 0) || (iBase == 16)) && (sz[0] == '0') && ((sz[1] == 'x') || (sz[1] == 'X')))
{
iBase = 16;
sz += 2;
}
else if ((iBase == 0) && (sz[0] == '0'))
{
iBase = 8;
}
else if (iBase == 0)
{
iBase = 10;
}
ulValue = 0;
for (;;)
{
if ((*sz >= '0') && (*sz <= '9'))
{
iDigit = *sz - '0';
}
else if ((*sz >= 'a') && (*sz <= 'z'))
{
iDigit = *sz - 'a' + 10;
}
else if ((*sz >= 'A') && (*sz <= 'Z'))
{
iDigit = *sz - 'A' + 10;
}
else
{
break;
}
if (iDigit >= iBase)
{
break;
}
ulValue = ulValue * iBase + iDigit;
sz++;
}
if (pszEnd)
{
*pszEnd = (char*)sz;
}
return bNegative ? (unsigned long)(-(long)ulValue) : ulValue;
}
int atoi(const char* sz)
{
return (int)strtol(sz, 0, 10);
}
long atol(const char* sz)
{
return strtol(sz, 0, 10);
}
unsigned int guiRandom = 1;
int rand(void)
{
guiRandom = guiRandom * 1103525245 + 12345;
return (int)((guiRandom / 65536) % (0x7fff + 1));
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
for (;;)
{
}
}
void exit(int iStatus)
{
abort();
}
