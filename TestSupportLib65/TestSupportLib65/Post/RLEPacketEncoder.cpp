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
class CRLEPacketEncoder
{
protected:
size muiElementSize;
public:
void Init(size uiElementSize);
void Kill(void);
size Encode(uint8* puiSource, int iNumElements, uint8* puiDest);
size GetMaxEncodedSize(int iNumElements);
protected:
bool IsSameElement(uint8* puiSource, int iFirst, int iSecond);
};
void CRLEPacketEncoder::Init(size uiElementSize)
{
muiElementSize = uiElementSize;
}
void CRLEPacketEncoder::Kill(void)
{
muiElementSize = 0;
}
bool CRLEPacketEncoder::IsSameElement(uint8* puiSource, int iFirst, int iSecond)
{
return memcmp(&puiSource[iFirst * muiElementSize], &puiSource[iSecond * muiElementSize], muiElementSize) == 0;
}
size CRLEPacketEncoder::Encode(uint8* puiSource, int iNumElements, uint8* puiDest)
{
size uiPos;
int x;
int iRun;
int iRaw;
uiPos = 0;
x = 0;
while (x < iNumElements)
{
iRun = 1;
while ((x + iRun < iNumElements) && (iRun < 128) && IsSameElement(puiSource, x, x + iRun))
{
iRun++;
}
if (iRun > 1)
{
puiDest[uiPos] = (uint8)(0x80 | (iRun - 1));
memcpy(&puiDest[uiPos + 1], &puiSource[x * muiElementSize], muiElementSize);
uiPos += 1 + muiElementSize;
x += iRun;
}
else
{
iRaw = 1;
while ((x + iRaw < iNumElements) && (iRaw < 128))
{
if ((x + iRaw + 1 < iNumElements) && IsSameElement(puiSource, x + iRaw, x + iRaw + 1))
{
break;
}
iRaw++;
}
puiDest[uiPos] = (uint8)(iRaw - 1);
memcpy(&puiDest[uiPos + 1], &puiSource[x * muiElementSize], iRaw * muiElementSize);
uiPos += 1 + iRaw * muiElementSize;
x += iRaw;
}
}
return uiPos;
}
size CRLEPacketEncoder::GetMaxEncodedSize(int iNumElements)
{
return (size)iNumElements * (muiElementSize + 1);
}
