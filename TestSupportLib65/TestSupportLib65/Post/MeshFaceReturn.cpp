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
class CMFRet
{
public:
int miFirstFace;
uint8 manCorners[4];
void PackEmpty(void);
void Pack(int iFirstFace, int iCorner1, int iCorner2, int iCorner3, int iNewEdges);
void Pack(int iFirstFace, int iCorner1, int iCorner2, int iCorner3, int iCorner4, int iCorner5, int iCorner6, int iNewEdges);
void Pack2(CMFRet r2);
void Repack(int iCorner1, int iCorner2, int iCorner3);
void Repack(int iCorner1, int iCorner2, int iCorner3, int iCorner4, int iCorner5, int iCorner6);
void PackOverflow(void);
int NumFaces(void);
int NewEdges(void);
void Unpack1(int* piCorner1, int* piCorner2, int* piCorner3);
void Unpack2(int* piCorner4, int* piCorner5, int* piCorner6);
};
void CMFRet::PackEmpty(void)
{
manCorners[1] = 0;
}
void CMFRet::PackOverflow(void)
{
manCorners[1] = 3 << 4;
}
void CMFRet::Pack(int iFirstFace, int iCorner1, int iCorner2, int iCorner3, int iNewEdges)
{
miFirstFace = iFirstFace;
manCorners[0] = (uint8)(iCorner1 | iCorner2 << 4);
manCorners[1] = (uint8)(iCorner3 | 1 << 4);
manCorners[3] = (uint8)(iNewEdges << 4);
}
void CMFRet::Pack(int iFirstFace, int iCorner1, int iCorner2, int iCorner3, int iCorner4, int iCorner5, int iCorner6, int iNewEdges)
{
miFirstFace = iFirstFace;
manCorners[0] = (uint8)(iCorner1 | iCorner2 << 4);
manCorners[1] = (uint8)(iCorner3 | 2 << 4);
manCorners[2] = (uint8)(iCorner4 | iCorner5 << 4);
manCorners[3] = (uint8)(iCorner6 | iNewEdges << 4);
}
void CMFRet::Pack2(CMFRet r2)
{
manCorners[1] |= 2 << 4;
manCorners[1] &= 0xef;
manCorners[2] = r2.manCorners[0];
manCorners[3] = ((manCorners[3] & 0xf0) + (r2.manCorners[3] & 0xf0)) | (r2.manCorners[1] & 0xf);
}
void CMFRet::Repack(int iCorner1, int iCorner2, int iCorner3, int iCorner4, int iCorner5, int iCorner6)
{
manCorners[0] = (uint8)(iCorner1 | iCorner2 << 4);
manCorners[1] = (manCorners[1] & 0xf0) | (uint8)(iCorner3);
manCorners[2] = (uint8)(iCorner4 | iCorner5 << 4);
manCorners[3] = (manCorners[3] & 0xf0) | (uint8)(iCorner6);
}
void CMFRet::Repack(int iCorner1, int iCorner2, int iCorner3)
{
manCorners[0] = (uint8)(iCorner1 | iCorner2 << 4);
manCorners[1] = (manCorners[1] & 0xf0) | (uint8)(iCorner3);
}
int CMFRet::NumFaces(void)
{
return manCorners[1] >> 4;
}
int CMFRet::NewEdges(void)
{
return manCorners[3] >> 4;
}
void CMFRet::Unpack1(int* piCorner1, int* piCorner2, int* piCorner3)
{
*piCorner1 = manCorners[0] & 0xf;
*piCorner2 = manCorners[0] >> 4;
*piCorner3 = manCorners[1] & 0xf;
}
void CMFRet::Unpack2(int* piCorner4, int* piCorner5, int* piCorner6)
{
*piCorner4 = manCorners[2] & 0xf;
*piCorner5 = manCorners[2] >> 4;
*piCorner6 = manCorners[3] & 0xf;
}
