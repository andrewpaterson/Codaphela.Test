typedef unsigned int size_t;
typedef int ptrdiff_t;
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
void* memcpy(void* pvDest, const void* pvSource, size_t uiBytes)
{
char* pcDest;
const char* pcSource;
pcDest = (char*)pvDest;
pcSource = (const char*)pvSource;
while (uiBytes > 0)
{
*pcDest++ = *pcSource++;
uiBytes--;
}
return pvDest;
}
void* memmove(void* pvDest, const void* pvSource, size_t uiBytes)
{
char* pcDest;
const char* pcSource;
pcDest = (char*)pvDest;
pcSource = (const char*)pvSource;
if ((pcDest < pcSource) || (pcDest >= pcSource + uiBytes))
{
return memcpy(pvDest, pvSource, uiBytes);
}
pcDest += uiBytes;
pcSource += uiBytes;
while (uiBytes > 0)
{
*--pcDest = *--pcSource;
uiBytes--;
}
return pvDest;
}
void* memset(void* pvDest, int iValue, size_t uiBytes)
{
char* pcDest;
pcDest = (char*)pvDest;
while (uiBytes > 0)
{
*pcDest++ = (char)iValue;
uiBytes--;
}
return pvDest;
}
int memcmp(const void* pv1, const void* pv2, size_t uiBytes)
{
const unsigned char* puc1;
const unsigned char* puc2;
puc1 = (const unsigned char*)pv1;
puc2 = (const unsigned char*)pv2;
while (uiBytes > 0)
{
if (*puc1 != *puc2)
{
return *puc1 - *puc2;
}
puc1++;
puc2++;
uiBytes--;
}
return 0;
}
void* memchr(const void* pv, int iValue, size_t uiBytes)
{
const unsigned char* puc;
puc = (const unsigned char*)pv;
while (uiBytes > 0)
{
if (*puc == (unsigned char)iValue)
{
return (void*)puc;
}
puc++;
uiBytes--;
}
return 0;
}
size_t strlen(const char* sz)
{
const char* pc;
pc = sz;
while (*pc)
{
pc++;
}
return pc - sz;
}
char* strcpy(char* szDest, const char* szSource)
{
char* pc;
pc = szDest;
while ((*pc++ = *szSource++))
{
}
return szDest;
}
char* strncpy(char* szDest, const char* szSource, size_t uiChars)
{
size_t i;
for (i = 0; (i < uiChars) && szSource[i]; i++)
{
szDest[i] = szSource[i];
}
for (; i < uiChars; i++)
{
szDest[i] = '\0';
}
return szDest;
}
char* strcat(char* szDest, const char* szSource)
{
strcpy(szDest + strlen(szDest), szSource);
return szDest;
}
char* strncat(char* szDest, const char* szSource, size_t uiChars)
{
char* pc;
pc = szDest + strlen(szDest);
while ((uiChars > 0) && *szSource)
{
*pc++ = *szSource++;
uiChars--;
}
*pc = '\0';
return szDest;
}
int strcmp(const char* sz1, const char* sz2)
{
while (*sz1 && (*sz1 == *sz2))
{
sz1++;
sz2++;
}
return (unsigned char)*sz1 - (unsigned char)*sz2;
}
int strncmp(const char* sz1, const char* sz2, size_t uiChars)
{
while ((uiChars > 0) && *sz1 && (*sz1 == *sz2))
{
sz1++;
sz2++;
uiChars--;
}
if (uiChars == 0)
{
return 0;
}
return (unsigned char)*sz1 - (unsigned char)*sz2;
}
char* strchr(const char* sz, int c)
{
for (;;)
{
if (*sz == (char)c)
{
return (char*)sz;
}
if (!*sz)
{
return 0;
}
sz++;
}
}
char* strrchr(const char* sz, int c)
{
const char* pcFound;
pcFound = 0;
for (;;)
{
if (*sz == (char)c)
{
pcFound = sz;
}
if (!*sz)
{
return (char*)pcFound;
}
sz++;
}
}
char* strstr(const char* sz, const char* szFind)
{
size_t uiLength;
uiLength = strlen(szFind);
while (*sz)
{
if (strncmp(sz, szFind, uiLength) == 0)
{
return (char*)sz;
}
sz++;
}
return (uiLength == 0) ? (char*)sz : 0;
}
