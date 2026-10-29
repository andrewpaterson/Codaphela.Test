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
extern const uint16 gauiDeflateLengthBase[29];
extern const uint8 gauiDeflateLengthExtra[29];
extern const uint16 gauiDeflateDistanceBase[30];
extern const uint8 gauiDeflateDistanceExtra[30];
extern const uint8 gauiDeflateCodeLengthOrder[19];
void DeflateFixedLiteralLengths(uint8* puiLengths);
void DeflateFixedDistanceLengths(uint8* puiLengths);
const uint16 gauiDeflateLengthBase[29] =
{
3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 15, 17, 19, 23, 27, 31, 35, 43, 51, 59, 67, 83, 99, 115, 131, 163, 195, 227, 258
};
const uint8 gauiDeflateLengthExtra[29] =
{
0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 0
};
const uint16 gauiDeflateDistanceBase[30] =
{
1, 2, 3, 4, 5, 7, 9, 13, 17, 25, 33, 49, 65, 97, 129, 193, 257, 385, 513, 769, 1025, 1537, 2049, 3073, 4097, 6145, 8193, 12289, 16385, 24577
};
const uint8 gauiDeflateDistanceExtra[30] =
{
0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13
};
const uint8 gauiDeflateCodeLengthOrder[19] =
{
16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15
};
void DeflateFixedLiteralLengths(uint8* puiLengths)
{
int i;
for (i = 0; i < 144; i++)
{
puiLengths[i] = 8;
}
for (; i < 256; i++)
{
puiLengths[i] = 9;
}
for (; i < 280; i++)
{
puiLengths[i] = 7;
}
for (; i < 288; i++)
{
puiLengths[i] = 8;
}
}
void DeflateFixedDistanceLengths(uint8* puiLengths)
{
int i;
for (i = 0; i < 30; i++)
{
puiLengths[i] = 5;
}
}
