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
class CAdler32
{
protected:
uint32 muiA;
uint32 muiB;
public:
void Init(void);
void Update(uint8* puiData, size uiLength);
uint32 Get(void);
};
enum TRISTATE
{
TRITRUE = true,
TRIFALSE = false,
TRIGNORED = 0xfffffffe,
TRIERROR = 0xffffffff
};
extern TRISTATE gTriState;
TRISTATE Negate(TRISTATE tristate);
TRISTATE Fix(TRISTATE tristate);
bool NotTrue(TRISTATE tristate);
typedef int64 filePos;
class CFileWriter
{
public:
bool WriteData(const void* pvData, lsize iDataSize);
bool WriteString(const char* szString);
bool WriteInt(int i);
bool WriteInt(uint i);
bool WriteInt8(int8 i);
bool WriteInt8(uint8 i);
bool WriteInt16(int16 i);
bool WriteInt16(uint16 i);
bool WriteInt32(int32 i);
bool WriteInt32(uint32 i);
bool WriteInt64(int64 i);
bool WriteInt64(uint64 i);
bool WriteSize(lsize ui);
bool WriteSizes(size* pai, size iLength);
bool WriteSInt(int i);
bool WriteSInt(uint i);
bool WriteFloat(float32 f);
bool WriteFloat(float64 f);
bool WriteChar(char8 c);
bool WriteWChar(char16 c);
bool WriteBool(bool b);
bool WriteBits(void* pvData, size iBitLength);
bool WriteIntArray(int32* pai, size iLength);
bool WriteLittleEndianInt16(int16 i);
bool WriteLittleEndianInt16(uint16 ui);
bool WriteLittleEndianInt32(int32 i);
bool WriteLittleEndianInt32(uint32 ui);
bool WriteBigEndianInt16(int16 i);
bool WriteBigEndianInt16(uint16 ui);
bool WriteBigEndianInt32(int32 i);
bool WriteBigEndianInt32(uint32 ui);
template<class M>
bool WritePrimitive(M c);
protected:
virtual size Write(const void* pvSource, lsize iSize, lsize iCount) =0;
};
template<class M>
bool CFileWriter::WritePrimitive(M c)
{
if (Write(&c, sizeof(M), 1) != 1) { return false; };
return true;
}
class CBitWriter
{
protected:
CFileWriter* mpcFile;
uint32 muiBits;
int miNumBits;
uint8 mauiBuffer[4096];
size muiBufferUsed;
bool mbFailed;
public:
void Init(CFileWriter* pcFile);
void Kill(void);
void WriteBits(uint32 uiValue, int iCount);
void AlignToByte(void);
void WriteBytes(uint8* puiData, size uiLength);
bool Flush(void);
protected:
void WriteByte(uint8 uiByte);
};
extern const uint16 gauiDeflateLengthBase[29];
extern const uint8 gauiDeflateLengthExtra[29];
extern const uint16 gauiDeflateDistanceBase[30];
extern const uint8 gauiDeflateDistanceExtra[30];
extern const uint8 gauiDeflateCodeLengthOrder[19];
void DeflateFixedLiteralLengths(uint8* puiLengths);
void DeflateFixedDistanceLengths(uint8* puiLengths);
class CHuffmanEncoder
{
protected:
int miNumSymbols;
uint8 mauiLengths[288];
uint16 mauiCodes[288];
public:
void Init(uint32* puiFrequencies, int iNumSymbols, int iMaxBits);
void Init(uint8* puiLengths, int iNumSymbols);
void Kill(void);
void Write(CBitWriter* pcWriter, int iSymbol);
int GetLength(int iSymbol);
uint8* GetLengths(void);
int GetNumSymbols(void);
protected:
bool BuildLengths(uint32* puiFrequencies, int iMaxBits);
void BuildCodes(void);
};
class CDeflater
{
protected:
CFileWriter* mpcOutput;
bool mbZLib;
CBitWriter mcBits;
uint8* mpuiData;
size muiDataSize;
int32* maiHead;
int32* maiPrevious;
uint16* mauiSymbolLengths;
uint16* mauiSymbolValues;
size muiNumSymbols;
size muiBlockStart;
size muiBlockLength;
uint32 mauiLiteralFrequencies[286];
uint32 mauiDistanceFrequencies[30];
public:
bool Init(CFileWriter* pcOutput, bool bZLib);
void Kill(void);
bool Deflate(uint8* puiData, size uiSize);
protected:
int32 InsertHash(size uiPosition);
int FindMatch(size uiPosition, int32 iChain, int iPreviousLength, size* puiDistance);
void AddLiteral(uint8 uiLiteral);
void AddMatch(int iLength, size uiDistance);
void ClearBlock(void);
void WriteBlock(bool bLast);
void WriteStored(bool bLast);
void WriteSymbols(CHuffmanEncoder* pcLiteralLengths, CHuffmanEncoder* pcDistances);
size CountSymbolBits(uint8* puiLiteralLengths, uint8* puiDistances);
size BuildCodeLengthSymbols(uint8* puiLengths, int iNumLengths, uint8* puiSymbols, uint8* puiExtras);
};
int DeflateLengthCode(int iLength);
int DeflateDistanceCode(size uiDistance);
int DeflateMatchLength(uint8* puiCandidate, uint8* puiCurrent, int iMaxLength);
int DeflateLengthCode(int iLength)
{
int iCode;
for (iCode = 29 - 1; iCode > 0; iCode--)
{
if (iLength >= gauiDeflateLengthBase[iCode])
{
return iCode;
}
}
return 0;
}
int DeflateDistanceCode(size uiDistance)
{
int iCode;
for (iCode = 30 - 1; iCode > 0; iCode--)
{
if (uiDistance >= gauiDeflateDistanceBase[iCode])
{
return iCode;
}
}
return 0;
}
int DeflateMatchLength(uint8* puiCandidate, uint8* puiCurrent, int iMaxLength)
{
int iLength;
uint64 uiCandidate;
uint64 uiCurrent;
iLength = 0;
while (iLength + 8 <= iMaxLength)
{
memcpy(&uiCandidate, &puiCandidate[iLength], sizeof(uint64));
memcpy(&uiCurrent, &puiCurrent[iLength], sizeof(uint64));
if (uiCandidate != uiCurrent)
{
return iLength + (int)(FindFirstSetBit(uiCandidate ^ uiCurrent) / 8);
}
iLength += 8;
}
while ((iLength < iMaxLength) && (puiCandidate[iLength] == puiCurrent[iLength]))
{
iLength++;
}
return iLength;
}
bool CDeflater::Init(CFileWriter* pcOutput, bool bZLib)
{
mpcOutput = pcOutput;
mbZLib = bZLib;
mpuiData = 0L;
muiDataSize = 0;
maiHead = (int32*)malloc(((int32)1 << 15) * sizeof(int32));
maiPrevious = (int32*)malloc(32768 * sizeof(int32));
mauiSymbolLengths = (uint16*)malloc(16384 * sizeof(uint16));
mauiSymbolValues = (uint16*)malloc(16384 * sizeof(uint16));
if ((maiHead == 0L) || (maiPrevious == 0L) || (mauiSymbolLengths == 0L) || (mauiSymbolValues == 0L))
{
Kill();
return false;
}
return true;
}
void CDeflater::Kill(void)
{
free(maiHead);
free(maiPrevious);
free(mauiSymbolLengths);
free(mauiSymbolValues);
maiHead = 0L;
maiPrevious = 0L;
mauiSymbolLengths = 0L;
mauiSymbolValues = 0L;
mpcOutput = 0L;
}
bool CDeflater::Deflate(uint8* puiData, size uiSize)
{
size uiPosition;
size uiEnd;
size p;
int32 iChain;
int iLength;
size uiDistance;
bool bAvailable;
int iPreviousLength;
size uiPreviousDistance;
CAdler32 cAdler;
uint32 uiAdler;
mpuiData = puiData;
muiDataSize = uiSize;
memset(maiHead, 0xFF, ((int32)1 << 15) * sizeof(int32));
mcBits.Init(mpcOutput);
if (mbZLib)
{
mcBits.WriteBits(0x78, 8);
mcBits.WriteBits(0x9C, 8);
}
muiBlockStart = 0;
ClearBlock();
uiPosition = 0;
bAvailable = false;
iPreviousLength = 0;
uiPreviousDistance = 0;
while (uiPosition < uiSize)
{
iChain = InsertHash(uiPosition);
iLength = 0;
uiDistance = 0;
if ((iChain >= 0) && (iPreviousLength < 16))
{
iLength = FindMatch(uiPosition, iChain, bAvailable ? iPreviousLength : 0, &uiDistance);
}
if (bAvailable && (iPreviousLength >= 3) && (iLength <= iPreviousLength))
{
AddMatch(iPreviousLength, uiPreviousDistance);
uiEnd = uiPosition - 1 + iPreviousLength;
for (p = uiPosition + 1; p < uiEnd; p++)
{
InsertHash(p);
}
uiPosition = uiEnd;
bAvailable = false;
iPreviousLength = 0;
}
else
{
if (bAvailable)
{
AddLiteral(puiData[uiPosition - 1]);
}
bAvailable = true;
iPreviousLength = iLength;
uiPreviousDistance = uiDistance;
uiPosition++;
}
}
if (bAvailable)
{
AddLiteral(puiData[uiPosition - 1]);
}
WriteBlock(true);
mcBits.AlignToByte();
if (mbZLib)
{
cAdler.Init();
cAdler.Update(puiData, uiSize);
uiAdler = cAdler.Get();
mcBits.WriteBits(uiAdler >> 24, 8);
mcBits.WriteBits(uiAdler >> 16, 8);
mcBits.WriteBits(uiAdler >> 8, 8);
mcBits.WriteBits(uiAdler, 8);
}
mpuiData = 0L;
return mcBits.Flush();
}
int32 CDeflater::InsertHash(size uiPosition)
{
uint32 uiHash;
int32 iPrevious;
if (uiPosition + 2 >= muiDataSize)
{
return -1;
}
uiHash = (((uint32)mpuiData[uiPosition] << 10) ^ ((uint32)mpuiData[uiPosition + 1] << 5) ^ mpuiData[uiPosition + 2]) & (((int32)1 << 15) - 1);
iPrevious = maiHead[uiHash];
maiPrevious[uiPosition & (32768 - 1)] = iPrevious;
maiHead[uiHash] = (int32)uiPosition;
return iPrevious;
}
int CDeflater::FindMatch(size uiPosition, int32 iChain, int iPreviousLength, size* puiDistance)
{
int iMaxLength;
int iBest;
int iFound;
int iChainLeft;
int iLength;
uint8* puiCandidate;
uint8* puiCurrent;
int32 iNext;
iMaxLength = 258;
if (muiDataSize - uiPosition < (size)iMaxLength)
{
iMaxLength = (int)(muiDataSize - uiPosition);
}
iBest = (iPreviousLength > 3 - 1) ? iPreviousLength : 3 - 1;
if (iBest >= iMaxLength)
{
return 0;
}
iChainLeft = (iPreviousLength >= 8) ? 128 / 4 : 128;
iFound = 0;
puiCurrent = &mpuiData[uiPosition];
while ((iChain >= 0) && (iChainLeft > 0) && (uiPosition - iChain <= 32768))
{
puiCandidate = &mpuiData[iChain];
if ((puiCandidate[iBest] == puiCurrent[iBest]) && (puiCandidate[0] == puiCurrent[0]) && (puiCandidate[1] == puiCurrent[1]))
{
iLength = DeflateMatchLength(puiCandidate, puiCurrent, iMaxLength);
if (iLength > iBest)
{
iBest = iLength;
iFound = iLength;
*puiDistance = uiPosition - iChain;
if ((iLength >= 128) || (iLength >= iMaxLength))
{
break;
}
}
}
iNext = maiPrevious[iChain & (32768 - 1)];
if (iNext >= iChain)
{
break;
}
iChain = iNext;
iChainLeft--;
}
if ((iFound == 3) && (*puiDistance > 4096))
{
return 0;
}
return iFound;
}
void CDeflater::ClearBlock(void)
{
muiNumSymbols = 0;
muiBlockLength = 0;
memset(mauiLiteralFrequencies, 0, sizeof(mauiLiteralFrequencies));
memset(mauiDistanceFrequencies, 0, sizeof(mauiDistanceFrequencies));
}
void CDeflater::AddLiteral(uint8 uiLiteral)
{
mauiSymbolLengths[muiNumSymbols] = 0;
mauiSymbolValues[muiNumSymbols] = uiLiteral;
muiNumSymbols++;
mauiLiteralFrequencies[uiLiteral]++;
muiBlockLength++;
if (muiNumSymbols == 16384)
{
WriteBlock(false);
muiBlockStart += muiBlockLength;
ClearBlock();
}
}
void CDeflater::AddMatch(int iLength, size uiDistance)
{
mauiSymbolLengths[muiNumSymbols] = (uint16)iLength;
mauiSymbolValues[muiNumSymbols] = (uint16)uiDistance;
muiNumSymbols++;
mauiLiteralFrequencies[257 + DeflateLengthCode(iLength)]++;
mauiDistanceFrequencies[DeflateDistanceCode(uiDistance)]++;
muiBlockLength += iLength;
if (muiNumSymbols == 16384)
{
WriteBlock(false);
muiBlockStart += muiBlockLength;
ClearBlock();
}
}
size CDeflater::CountSymbolBits(uint8* puiLiteralLengths, uint8* puiDistances)
{
size uiBits;
size i;
int iCode;
uiBits = puiLiteralLengths[256];
for (i = 0; i < muiNumSymbols; i++)
{
if (mauiSymbolLengths[i] == 0)
{
uiBits += puiLiteralLengths[mauiSymbolValues[i]];
}
else
{
iCode = DeflateLengthCode(mauiSymbolLengths[i]);
uiBits += puiLiteralLengths[257 + iCode] + gauiDeflateLengthExtra[iCode];
iCode = DeflateDistanceCode(mauiSymbolValues[i]);
uiBits += puiDistances[iCode] + gauiDeflateDistanceExtra[iCode];
}
}
return uiBits;
}
size CDeflater::BuildCodeLengthSymbols(uint8* puiLengths, int iNumLengths, uint8* puiSymbols, uint8* puiExtras)
{
size uiCount;
int i;
int iRun;
int iChunk;
uint8 uiLength;
uiCount = 0;
i = 0;
while (i < iNumLengths)
{
uiLength = puiLengths[i];
iRun = 1;
while ((i + iRun < iNumLengths) && (puiLengths[i + iRun] == uiLength))
{
iRun++;
}
if (uiLength == 0)
{
while (iRun >= 11)
{
iChunk = (iRun < 138) ? iRun : 138;
puiSymbols[uiCount] = 18;
puiExtras[uiCount] = (uint8)(iChunk - 11);
uiCount++;
i += iChunk;
iRun -= iChunk;
}
if (iRun >= 3)
{
puiSymbols[uiCount] = 17;
puiExtras[uiCount] = (uint8)(iRun - 3);
uiCount++;
i += iRun;
iRun = 0;
}
}
else
{
puiSymbols[uiCount] = uiLength;
puiExtras[uiCount] = 0;
uiCount++;
i++;
iRun--;
while (iRun >= 3)
{
iChunk = (iRun < 6) ? iRun : 6;
puiSymbols[uiCount] = 16;
puiExtras[uiCount] = (uint8)(iChunk - 3);
uiCount++;
i += iChunk;
iRun -= iChunk;
}
}
while (iRun > 0)
{
puiSymbols[uiCount] = uiLength;
puiExtras[uiCount] = 0;
uiCount++;
i++;
iRun--;
}
}
return uiCount;
}
void CDeflater::WriteBlock(bool bLast)
{
CHuffmanEncoder cLiteralLengths;
CHuffmanEncoder cDistances;
CHuffmanEncoder cCodeLengths;
CHuffmanEncoder cFixedLiteralLengths;
CHuffmanEncoder cFixedDistances;
uint8 auiFixedLiteralLengths[288];
uint8 auiFixedDistances[30];
uint8 auiLengths[286 + 30];
uint8 auiCodeLengthSymbols[286 + 30];
uint8 auiCodeLengthExtras[286 + 30];
uint32 auiCodeLengthFrequencies[19];
static const uint8 auiCodeLengthExtraBits[3] = { 2, 3, 7 };
int iNumLiteralLengths;
int iNumDistances;
int iNumCodeLengths;
size uiNumCodeLengthSymbols;
size uiDynamicBits;
size uiFixedBits;
size uiStoredBits;
size uiNumStored;
size i;
uint8 uiSymbol;
mauiLiteralFrequencies[256]++;
cLiteralLengths.Init(mauiLiteralFrequencies, 286, 15);
cDistances.Init(mauiDistanceFrequencies, 30, 15);
iNumLiteralLengths = 286;
while ((iNumLiteralLengths > 257) && (cLiteralLengths.GetLength(iNumLiteralLengths - 1) == 0))
{
iNumLiteralLengths--;
}
iNumDistances = 30;
while ((iNumDistances > 1) && (cDistances.GetLength(iNumDistances - 1) == 0))
{
iNumDistances--;
}
memcpy(auiLengths, cLiteralLengths.GetLengths(), iNumLiteralLengths);
memcpy(&auiLengths[iNumLiteralLengths], cDistances.GetLengths(), iNumDistances);
uiNumCodeLengthSymbols = BuildCodeLengthSymbols(auiLengths, iNumLiteralLengths + iNumDistances, auiCodeLengthSymbols, auiCodeLengthExtras);
memset(auiCodeLengthFrequencies, 0, sizeof(auiCodeLengthFrequencies));
for (i = 0; i < uiNumCodeLengthSymbols; i++)
{
auiCodeLengthFrequencies[auiCodeLengthSymbols[i]]++;
}
cCodeLengths.Init(auiCodeLengthFrequencies, 19, 7);
iNumCodeLengths = 19;
while ((iNumCodeLengths > 4) && (cCodeLengths.GetLength(gauiDeflateCodeLengthOrder[iNumCodeLengths - 1]) == 0))
{
iNumCodeLengths--;
}
uiDynamicBits = 3 + 5 + 5 + 4 + 3 * iNumCodeLengths;
for (i = 0; i < uiNumCodeLengthSymbols; i++)
{
uiSymbol = auiCodeLengthSymbols[i];
uiDynamicBits += cCodeLengths.GetLength(uiSymbol);
if (uiSymbol >= 16)
{
uiDynamicBits += auiCodeLengthExtraBits[uiSymbol - 16];
}
}
uiDynamicBits += CountSymbolBits(cLiteralLengths.GetLengths(), cDistances.GetLengths());
DeflateFixedLiteralLengths(auiFixedLiteralLengths);
DeflateFixedDistanceLengths(auiFixedDistances);
uiFixedBits = 3 + CountSymbolBits(auiFixedLiteralLengths, auiFixedDistances);
uiNumStored = (muiBlockLength + 65535 - 1) / 65535;
if (uiNumStored == 0)
{
uiNumStored = 1;
}
uiStoredBits = (muiBlockLength + uiNumStored * 5) * 8;
if ((uiStoredBits <= uiFixedBits) && (uiStoredBits <= uiDynamicBits))
{
WriteStored(bLast);
}
else if (uiFixedBits <= uiDynamicBits)
{
mcBits.WriteBits(bLast ? 1 : 0, 1);
mcBits.WriteBits(1, 2);
cFixedLiteralLengths.Init(auiFixedLiteralLengths, 288);
cFixedDistances.Init(auiFixedDistances, 30);
WriteSymbols(&cFixedLiteralLengths, &cFixedDistances);
cFixedDistances.Kill();
cFixedLiteralLengths.Kill();
}
else
{
mcBits.WriteBits(bLast ? 1 : 0, 1);
mcBits.WriteBits(2, 2);
mcBits.WriteBits(iNumLiteralLengths - 257, 5);
mcBits.WriteBits(iNumDistances - 1, 5);
mcBits.WriteBits(iNumCodeLengths - 4, 4);
for (i = 0; i < (size)iNumCodeLengths; i++)
{
mcBits.WriteBits(cCodeLengths.GetLength(gauiDeflateCodeLengthOrder[i]), 3);
}
for (i = 0; i < uiNumCodeLengthSymbols; i++)
{
uiSymbol = auiCodeLengthSymbols[i];
cCodeLengths.Write(&mcBits, uiSymbol);
if (uiSymbol >= 16)
{
mcBits.WriteBits(auiCodeLengthExtras[i], auiCodeLengthExtraBits[uiSymbol - 16]);
}
}
WriteSymbols(&cLiteralLengths, &cDistances);
}
cCodeLengths.Kill();
cDistances.Kill();
cLiteralLengths.Kill();
}
void CDeflater::WriteStored(bool bLast)
{
size uiPosition;
size uiRemaining;
size uiChunk;
uiPosition = muiBlockStart;
uiRemaining = muiBlockLength;
do
{
uiChunk = (uiRemaining < 65535) ? uiRemaining : 65535;
mcBits.WriteBits((bLast && (uiChunk == uiRemaining)) ? 1 : 0, 1);
mcBits.WriteBits(0, 2);
mcBits.AlignToByte();
mcBits.WriteBits((uint32)uiChunk, 16);
mcBits.WriteBits((uint32)~uiChunk, 16);
mcBits.WriteBytes(&mpuiData[uiPosition], uiChunk);
uiPosition += uiChunk;
uiRemaining -= uiChunk;
}
while (uiRemaining > 0);
}
void CDeflater::WriteSymbols(CHuffmanEncoder* pcLiteralLengths, CHuffmanEncoder* pcDistances)
{
size i;
int iLength;
size uiDistance;
int iCode;
for (i = 0; i < muiNumSymbols; i++)
{
iLength = mauiSymbolLengths[i];
if (iLength == 0)
{
pcLiteralLengths->Write(&mcBits, mauiSymbolValues[i]);
}
else
{
iCode = DeflateLengthCode(iLength);
pcLiteralLengths->Write(&mcBits, 257 + iCode);
mcBits.WriteBits(iLength - gauiDeflateLengthBase[iCode], gauiDeflateLengthExtra[iCode]);
uiDistance = mauiSymbolValues[i];
iCode = DeflateDistanceCode(uiDistance);
pcDistances->Write(&mcBits, iCode);
mcBits.WriteBits((uint32)(uiDistance - gauiDeflateDistanceBase[iCode]), gauiDeflateDistanceExtra[iCode]);
}
}
pcLiteralLengths->Write(&mcBits, 256);
}
