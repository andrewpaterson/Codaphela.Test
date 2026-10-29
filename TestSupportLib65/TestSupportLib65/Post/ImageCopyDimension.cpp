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
struct SImageCopy
{
uint uiDestX;
uint uiDestY;
uint uiSourceX1;
uint uiSourceY1;
uint uiSourceX2;
uint uiSourceY2;
bool bValid;
void Init(int iDestX, int iDestY, int iSourceX1, int iSourceY1, int iSourceX2, int iSourceY2, int iDestWidth, int iDestHeight);
};
void SImageCopy::Init(int iDestX, int iDestY, int iSourceX1, int iSourceY1, int iSourceX2, int iSourceY2, int iDestWidth, int iDestHeight)
{
if (iDestY < 0)
{
iSourceY1 += -iDestY;
iDestY = 0;
}
if (iDestX < 0)
{
iSourceX1 += -iDestX;
iDestX = 0;
}
if ((iSourceX1 >= iSourceX2) || (iSourceY1 >= iSourceY2))
{
bValid = false;
return;
}
if (((iSourceX2 - iSourceX1) + iDestX) >= iDestWidth)
{
iSourceX2 = iSourceX1 + iDestWidth - iDestX;
}
if (((iSourceY2 - iSourceY1) + iDestY) >= iDestHeight)
{
iSourceY2 = iSourceY1 + iDestHeight - iDestY;
}
if ((iSourceX2 <= 0) || (iSourceY2 <= 0))
{
bValid = false;
return;
}
uiDestX = iDestX;
uiDestY = iDestY;
uiSourceX1 = iSourceX1;
uiSourceY1 = iSourceY1;
uiSourceX2 = iSourceX2;
uiSourceY2 = iSourceY2;
bValid = true;
}
