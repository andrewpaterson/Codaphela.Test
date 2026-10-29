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
int64 DivideRound(int64 iNumerator, int64 iDenominator);
int64 DivideFloor(int64 iNumerator, int64 iDenominator);
int64 DivideCeiling(int64 iNumerator, int64 iDenominator);
int32 FixedFromInt(int32 i, int iFractionBits);
int32 FixedFromFloat(float32 f, int iFractionBits);
int32 FloatToIntScaled(float32 f, int32 iScale);
float32 FixedToFloat(int32 iFixed, int iFractionBits);
int32 FixedConvert(int32 iFixed, int iFromFractionBits, int iToFractionBits);
int32 FixedFloor(int32 iFixed, int iFractionBits);
int32 FixedCeiling(int32 iFixed, int iFractionBits);
int32 FixedRound(int32 iFixed, int iFractionBits);
int32 FixedFraction(int32 iFixed, int iFractionBits);
int32 FixedMultiply(int32 iA, int32 iB, int iFractionBits);
int32 FixedDivide(int32 iA, int32 iB, int iFractionBits);
int32 FixedMultiplyDivide(int32 iA, int32 iB, int32 iC);
int32 FixedSquareRoot(int32 iFixed, int iFractionBits);
uint32 TruncateLowBits(uint32 i);
bool IsPowerOfTwo(uint32 i);
uint32 GetBestHighBit(uint32 i);
size GetLogBase2(uint32 i);
uint8 GetByte(uint32 iInt, uint16 iPos);
uint32 SetByte(uint8 c, uint16 iPos);
bool GetBit(size iBit, void* pvBitArray);
bool GetBitReverseHiLo(size iBit, void* pvBitArray);
size CountBits(void* pvBitArray, size iBitLength);
size CountBitsSingly(void* pvBitArray, size iBitLength);
size CountDigits(int16 i);
size CountDigits(int32 i);
size CountDigits(int64 i);
void SetBit(size iBit, void* pvBitArray, bool bBit);
void SetBits(size iStart, void* pvBitArray, bool bBit, size iLength);
void SetFlagByte(uint8* psiDest, uint8 iFlag, bool iFlagValue);
void SetFlagByte(int8* psiDest, int8 iFlag, bool iFlagValue);
void SetFlagShort(uint16* psiDest, uint16 iFlag, bool iFlagValue);
void SetFlagShort(int16* psiDest, int16 iFlag, bool iFlagValue);
void SetFlagInt(uint32* piDest, uint32 iFlag, bool iFlagValue);
void SetFlagInt(int32* piDest, int32 iFlag, bool iFlagValue);
void SetFlagLong(uint64* psiDest, uint64 iFlag, bool iFlagValue);
void SetFlagLong(int64* psiDest, int64 iFlag, bool iFlagValue);
void SetFlagSize(size* piDest, size iFlag, bool iFlagValue);
size FindFirstClearBit(void* pvArray, size iArraySize);
size FindFirstClearBit(uint32 uiBits);
size FindFirstSetBit(void* pvArray, size iArraySize);
size FindFirstSetBit(uint64 uiBits);
size FindLastClearBit(void* pvArray, size iArraySize);
size FindLastSetBit(void* pvArray, size iArraySize);
size FindNextSetBit(void* pvArray, size iArraySize, size iStartBit);
size FindNextClearBit(void* pvArray, size iArraySize, size iStartBit);
void SwapInt16(int16* pi1, int16* pi2);
void SwapUint16(uint16* pi1, uint16* pi2);
void SwapInt32(int32* pi1, int32* pi2);
void SwapUint32(uint32* pi1, uint32* pi2);
void SwapInt(int* pi1, int* pi2);
void SwapInt(uint* pi1, uint* pi2);
void SwapByte(uint8* pc1, uint8* pi2);
void SwapSize(size* pui1, size* pui2);
void SwapBit(uint8* puiByte, size uiBit1, size uiBit2);
void SwapBit(uint16* puiByte, size uiBit1, size uiBit2);
size FindFirstInt(int32* piIntArray, int32 iSearch, size iMaxLength);
size FindFirstByte(uint8* pcCharArray, uint8 uiSearch, size iMaxLength);
uint8 GetHighNybble(uint8 c);
uint8 GetLowNybble(uint8 c);
uint8 GetLowByte(uint16 uiValue);
uint8 GetHighByte(uint16 uiValue);
uint16 SetLowByte(uint16 uiVariable, uint8 uiData);
uint16 SetHighByte(uint16 uiVariable, uint8 uiData);
int CompareByte(const void* arg1, const void* arg2);
int CompareByteReverse(const void* arg1, const void* arg2);
int CompareShort(const void* arg1, const void* arg2);
int CompareShortReverse(const void* arg1, const void* arg2);
int CompareInt(const void* arg1, const void* arg2);
int CompareIntReverse(const void* arg1, const void* arg2);
int CompareLong(const void* arg1, const void* arg2);
int CompareLongReverse(const void* arg1, const void* arg2);
uint8 GetCrumb(size iCrumb, void* pvArray);
uint8 GetNybble(size iNybble, void* pvArray);
void CopyBits(void* pvDest, size iDestOffset, void* pvSource, size iSourceOffset, size iNumBits, bool bClear);
void CopyBitsReverseHiLo(void* pvDest, size iDestOffset, void* pvSource, size iSourceOffset, size iNumBits, bool bClear);
int16 ReverseShortEndianness(int16 s);
int32 ReverseIntEndianness(int32 i);
int64 ReverseLongEndianness(int64 i);
uint16 ReverseShortEndianness(uint16 s);
uint32 ReverseIntEndianness(uint32 i);
uint64 ReverseLongEndianness(uint64 i);
void ReverseEndianness(void* pv, size iSize);
void ReverseBytes(void* pv, size iSize);
size CalculateStride(size iElementSize, uint16 iAlignment);
uint8 CalculateOffset(int16 iOffset, uint16 iAlignment);
int32 IntAbs(int32 i);
uint32 GetPowerOf2SizeDown(uint32 iInt);
uint32 GetPowerOf2SizeUp(uint32 iInt);
uint32 GetPowerOf2SizeAuto(uint32 iInt);
int32 LargestInt(int32* pInts, int32 iCount);
size Min(size ui1, size ui2);
size Max(size ui1, size ui2);
int8 Absolute(int8 i);
int16 Absolute(int16 i);
int32 Absolute(int32 i);
int64 Absolute(int64 i);
int16 SquareRoot(int16 i);
int32 SquareRoot(int32 i);
int64 SquareRoot(int64 i);
inline bool FixBool(int32 i)
{
return i != 0;
}
inline bool FixBool(void* pv)
{
return pv != 0L;
}
class CCoverageRasteriser
{
protected:
int32* mpiCover;
int32* mpiArea;
uint8* mpuiCoverage;
int miWidth;
int miHeight;
size muiCapacity;
public:
void Init(void);
void Kill(void);
bool Begin(int iWidth, int iHeight);
void End(void);
void AddQuadratic(int32 x0, int32 y0, int32 x1, int32 y1, int32 x2, int32 y2);
void AddLine(int32 x1, int32 y1, int32 x2, int32 y2);
void Accumulate(void);
uint8* GetCoverage(void);
int GetWidth(void);
int GetHeight(void);
protected:
void AddRowLine(int iRow, int32 x1, int32 y1, int32 x2, int32 y2);
void AddCellLine(int iRow, int32 x1, int32 y1, int32 x2, int32 y2);
};
void CCoverageRasteriser::Init(void)
{
mpiCover = 0L;
mpiArea = 0L;
mpuiCoverage = 0L;
miWidth = 0;
miHeight = 0;
muiCapacity = 0;
}
void CCoverageRasteriser::Kill(void)
{
End();
}
bool CCoverageRasteriser::Begin(int iWidth, int iHeight)
{
size uiCells;
if ((iWidth < 0) || (iHeight < 0))
{
return false;
}
uiCells = (size)iWidth * iHeight;
if (uiCells == 0)
{
miWidth = iWidth;
miHeight = iHeight;
return true;
}
if (uiCells > muiCapacity)
{
End();
mpiCover = (int32*)malloc(uiCells * sizeof(int32));
mpiArea = (int32*)malloc(uiCells * sizeof(int32));
mpuiCoverage = (uint8*)malloc(uiCells);
if ((mpiCover == 0L) || (mpiArea == 0L) || (mpuiCoverage == 0L))
{
End();
return false;
}
muiCapacity = uiCells;
}
miWidth = iWidth;
miHeight = iHeight;
memset(mpiCover, 0, uiCells * sizeof(int32));
memset(mpiArea, 0, uiCells * sizeof(int32));
return true;
}
void CCoverageRasteriser::End(void)
{
free(mpiCover);
free(mpiArea);
free(mpuiCoverage);
mpiCover = 0L;
mpiArea = 0L;
mpuiCoverage = 0L;
miWidth = 0;
miHeight = 0;
muiCapacity = 0;
}
void CCoverageRasteriser::AddQuadratic(int32 x0, int32 y0, int32 x1, int32 y1, int32 x2, int32 y2)
{
int64 iDeviationX;
int64 iDeviationY;
int64 iDeviation;
int64 iNumLines;
int64 i;
int64 iDivisor;
int64 iWeight0;
int64 iWeight1;
int64 iWeight2;
int32 iLastX;
int32 iLastY;
int32 x;
int32 y;
iDeviationX = (int64)x0 - 2 * (int64)x1 + x2;
iDeviationY = (int64)y0 - 2 * (int64)y1 + y2;
iDeviation = iDeviationX * iDeviationX + iDeviationY * iDeviationY;
if (iDeviation < ((1 << 8) * (1 << 8) / 3))
{
AddLine(x0, y0, x2, y2);
return;
}
iNumLines = 1 + SquareRoot(SquareRoot(3 * iDeviation)) / 16;
iDivisor = iNumLines * iNumLines;
iLastX = x0;
iLastY = y0;
for (i = 1; i < iNumLines; i++)
{
iWeight0 = (iNumLines - i) * (iNumLines - i);
iWeight1 = 2 * i * (iNumLines - i);
iWeight2 = i * i;
x = (int32)DivideRound(iWeight0 * x0 + iWeight1 * x1 + iWeight2 * x2, iDivisor);
y = (int32)DivideRound(iWeight0 * y0 + iWeight1 * y1 + iWeight2 * y2, iDivisor);
AddLine(iLastX, iLastY, x, y);
iLastX = x;
iLastY = y;
}
AddLine(iLastX, iLastY, x2, y2);
}
void CCoverageRasteriser::AddLine(int32 x1, int32 y1, int32 x2, int32 y2)
{
int32 iYMin;
int32 iYMax;
int iRow;
int iRowStart;
int iRowEnd;
int32 iTop;
int32 iBottom;
int32 iTopX;
int32 iBottomX;
if (y1 == y2)
{
return;
}
iYMin = (y1 < y2) ? y1 : y2;
iYMax = (y1 < y2) ? y2 : y1;
iRowStart = FixedFloor(iYMin, 8);
if (iRowStart < 0)
{
iRowStart = 0;
}
iRowEnd = FixedCeiling(iYMax, 8);
if (iRowEnd > miHeight)
{
iRowEnd = miHeight;
}
for (iRow = iRowStart; iRow < iRowEnd; iRow++)
{
iTop = FixedFromInt(iRow, 8);
iBottom = FixedFromInt(iRow + 1, 8);
iTop = (iTop > iYMin) ? iTop : iYMin;
iBottom = (iBottom < iYMax) ? iBottom : iYMax;
if (iTop >= iBottom)
{
continue;
}
iTopX = x1 + (int32)DivideRound((int64)(x2 - x1) * (iTop - y1), y2 - y1);
iBottomX = x1 + (int32)DivideRound((int64)(x2 - x1) * (iBottom - y1), y2 - y1);
if (y1 < y2)
{
AddRowLine(iRow, iTopX, iTop, iBottomX, iBottom);
}
else
{
AddRowLine(iRow, iBottomX, iBottom, iTopX, iTop);
}
}
}
void CCoverageRasteriser::AddRowLine(int iRow, int32 x1, int32 y1, int32 x2, int32 y2)
{
int32 iBoundary;
int32 iStartX;
int32 iStartY;
int32 y;
iStartX = x1;
iStartY = y1;
if (x1 < x2)
{
for (iBoundary = FixedFromInt(FixedFloor(x1, 8) + 1, 8); iBoundary < x2; iBoundary += (1 << 8))
{
y = y1 + (int32)DivideRound((int64)(y2 - y1) * (iBoundary - x1), x2 - x1);
AddCellLine(iRow, iStartX, iStartY, iBoundary, y);
iStartX = iBoundary;
iStartY = y;
}
}
else if (x1 > x2)
{
for (iBoundary = FixedFromInt(FixedCeiling(x1, 8) - 1, 8); iBoundary > x2; iBoundary -= (1 << 8))
{
y = y1 + (int32)DivideRound((int64)(y2 - y1) * (iBoundary - x1), x2 - x1);
AddCellLine(iRow, iStartX, iStartY, iBoundary, y);
iStartX = iBoundary;
iStartY = y;
}
}
AddCellLine(iRow, iStartX, iStartY, x2, y2);
}
void CCoverageRasteriser::AddCellLine(int iRow, int32 x1, int32 y1, int32 x2, int32 y2)
{
int32 iHeight;
int iColumn;
int32 iLeft;
int32 iX1;
int32 iX2;
size uiCell;
iHeight = y2 - y1;
if (iHeight == 0)
{
return;
}
iColumn = FixedFloor((x1 < x2) ? x1 : x2, 8);
if (iColumn >= miWidth)
{
return;
}
if (iColumn < 0)
{
iColumn = 0;
iX1 = 0;
iX2 = 0;
}
else
{
iLeft = FixedFromInt(iColumn, 8);
iX1 = x1 - iLeft;
iX2 = x2 - iLeft;
}
uiCell = (size)iRow * miWidth + iColumn;
mpiCover[uiCell] += iHeight;
mpiArea[uiCell] += (iX1 + iX2) * iHeight;
}
void CCoverageRasteriser::Accumulate(void)
{
int x;
int y;
size uiCell;
int64 iCover;
int64 iCoverage;
for (y = 0; y < miHeight; y++)
{
iCover = 0;
for (x = 0; x < miWidth; x++)
{
uiCell = (size)y * miWidth + x;
iCover += mpiCover[uiCell];
iCoverage = iCover * 2 * (1 << 8) - mpiArea[uiCell];
if (iCoverage < 0)
{
iCoverage = -iCoverage;
}
iCoverage = DivideRound(iCoverage * 255, (2 * (1 << 8) * (1 << 8)));
mpuiCoverage[uiCell] = (uint8)((iCoverage > 255) ? 255 : iCoverage);
}
}
}
uint8* CCoverageRasteriser::GetCoverage(void)
{
return mpuiCoverage;
}
int CCoverageRasteriser::GetWidth(void)
{
return miWidth;
}
int CCoverageRasteriser::GetHeight(void)
{
return miHeight;
}
