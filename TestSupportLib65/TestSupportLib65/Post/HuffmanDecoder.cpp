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
extern const uint16 gauiDeflateLengthBase[29];
extern const uint8 gauiDeflateLengthExtra[29];
extern const uint16 gauiDeflateDistanceBase[30];
extern const uint8 gauiDeflateDistanceExtra[30];
extern const uint8 gauiDeflateCodeLengthOrder[19];
void DeflateFixedLiteralLengths(uint8* puiLengths);
void DeflateFixedDistanceLengths(uint8* puiLengths);
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
class CFileReader
{
public:
bool ReadData(void* pvData, lsize iDataSize);
bool ReadStringLength(size* piLength);
bool ReadStringChars(char* szString, size iLength);
bool ReadString(char* szString, size iMaxLength);
bool ReadInt8(int8* pi);
bool ReadInt8(uint8* pi);
bool ReadInt16(int16* pi);
bool ReadInt16(uint16* pi);
bool ReadInt32(int32* pi);
bool ReadInt32(uint32* pi);
bool ReadInt64(int64* plli);
bool ReadInt64(uint64* plli);
bool ReadSInt(int* pi);
bool ReadSInt(uint* pi);
bool ReadSize(lsize* pui);
bool ReadSizes(size* pai, size iLength);
bool ReadFloat(float32* pf);
bool ReadFloat(float64* pf);
bool ReadChar(char8* pc);
bool ReadWChar(char16* pc);
bool ReadBool(bool* pb);
bool ReadBits(void* pvData, size iByteLength);
bool ReadIntArray(int32* pai, size iLength);
bool ReadLittleEndianInt16(int16* pi);
bool ReadLittleEndianInt16(uint16* pui);
bool ReadLittleEndianInt32(int32* pi);
bool ReadLittleEndianInt32(uint32* pui);
bool ReadBigEndianInt16(int16* pi);
bool ReadBigEndianInt16(uint16* pui);
bool ReadBigEndianInt32(int32* pi);
bool ReadBigEndianInt32(uint32* pui);
template<class M>
bool ReadPrimitive(M* pc);
protected:
virtual size Read(void* pvDest, lsize iSize, lsize iCount) =0;
};
template<class M>
bool CFileReader::ReadPrimitive(M* pc)
{
if (Read(pc, sizeof(M), 1) != 1) { return false; };
return true;
}
class CBitReader
{
protected:
CFileReader* mpcFile;
uint32 muiBits;
int miNumBits;
public:
void Init(CFileReader* pcFile);
void Kill(void);
bool ReadBits(int iCount, uint32* puiValue);
bool ReadBit(uint32* puiValue);
void AlignToByte(void);
bool FillByte(void);
uint32 GetBits(void);
int NumBits(void);
void SkipBits(int iCount);
};
class CHuffmanDecoder
{
protected:
int16 maiCount[15 + 1];
int16 maiSymbols[288];
uint16 mauiFast[(1 << 9)];
int miNumCodes;
int miUnused;
public:
bool Init(uint8* puiLengths, int iNumSymbols);
void Kill(void);
bool IsComplete(void);
bool IsSingleCode(void);
bool Decode(CBitReader* pcReader, int* piSymbol);
protected:
void InitFast(uint8* puiLengths, int iNumSymbols);
bool DecodeSlow(CBitReader* pcReader, int* piSymbol);
};
bool CHuffmanDecoder::Init(uint8* puiLengths, int iNumSymbols)
{
int16 aiOffsets[15 + 1];
int iLength;
int iSymbol;
int iLeft;
for (iLength = 0; iLength <= 15; iLength++)
{
maiCount[iLength] = 0;
}
for (iSymbol = 0; iSymbol < iNumSymbols; iSymbol++)
{
maiCount[puiLengths[iSymbol]]++;
}
miNumCodes = iNumSymbols - maiCount[0];
iLeft = 1;
for (iLength = 1; iLength <= 15; iLength++)
{
iLeft <<= 1;
iLeft -= maiCount[iLength];
if (iLeft < 0)
{
miUnused = 0;
return false;
}
}
miUnused = iLeft;
aiOffsets[1] = 0;
for (iLength = 1; iLength < 15; iLength++)
{
aiOffsets[iLength + 1] = aiOffsets[iLength] + maiCount[iLength];
}
for (iSymbol = 0; iSymbol < iNumSymbols; iSymbol++)
{
if (puiLengths[iSymbol] != 0)
{
maiSymbols[aiOffsets[puiLengths[iSymbol]]] = (int16)iSymbol;
aiOffsets[puiLengths[iSymbol]]++;
}
}
InitFast(puiLengths, iNumSymbols);
return true;
}
void CHuffmanDecoder::InitFast(uint8* puiLengths, int iNumSymbols)
{
uint32 auiNextCode[15 + 1];
uint32 uiCode;
uint32 uiReversed;
uint32 uiIndex;
uint16 uiEntry;
int iLength;
int iSymbol;
int i;
memset(mauiFast, 0, sizeof(mauiFast));
uiCode = 0;
auiNextCode[1] = 0;
for (iLength = 2; iLength <= 15; iLength++)
{
uiCode = (uiCode + maiCount[iLength - 1]) << 1;
auiNextCode[iLength] = uiCode;
}
for (iSymbol = 0; iSymbol < iNumSymbols; iSymbol++)
{
iLength = puiLengths[iSymbol];
if (iLength != 0)
{
uiCode = auiNextCode[iLength];
auiNextCode[iLength]++;
if (iLength <= 9)
{
uiReversed = 0;
for (i = 0; i < iLength; i++)
{
uiReversed = (uiReversed << 1) | ((uiCode >> i) & 1);
}
uiEntry = (uint16)((iSymbol << 4) | iLength);
for (uiIndex = uiReversed; uiIndex < (1 << 9); uiIndex += 1 << iLength)
{
mauiFast[uiIndex] = uiEntry;
}
}
}
}
}
void CHuffmanDecoder::Kill(void)
{
miNumCodes = 0;
}
bool CHuffmanDecoder::IsComplete(void)
{
return miUnused == 0;
}
bool CHuffmanDecoder::IsSingleCode(void)
{
return (miNumCodes == 1) && (maiCount[1] == 1);
}
bool CHuffmanDecoder::Decode(CBitReader* pcReader, int* piSymbol)
{
uint16 uiEntry;
int iLength;
for (;;)
{
uiEntry = mauiFast[pcReader->GetBits() & ((1 << 9) - 1)];
iLength = uiEntry & ((1 << 4) - 1);
if (iLength == 0)
{
return DecodeSlow(pcReader, piSymbol);
}
if (iLength <= pcReader->NumBits())
{
pcReader->SkipBits(iLength);
*piSymbol = uiEntry >> 4;
return true;
}
if (!pcReader->FillByte())
{
return false;
}
}
}
bool CHuffmanDecoder::DecodeSlow(CBitReader* pcReader, int* piSymbol)
{
int iCode;
int iFirst;
int iIndex;
int iLength;
int iCount;
iCode = 0;
iFirst = 0;
iIndex = 0;
for (iLength = 1; iLength <= 15; iLength++)
{
if ((iLength > pcReader->NumBits()) && !pcReader->FillByte())
{
return false;
}
iCode |= (int)((pcReader->GetBits() >> (iLength - 1)) & 1);
iCount = maiCount[iLength];
if (iCode - iCount < iFirst)
{
pcReader->SkipBits(iLength);
*piSymbol = maiSymbols[iIndex + (iCode - iFirst)];
return true;
}
iIndex += iCount;
iFirst += iCount;
iFirst <<= 1;
iCode <<= 1;
}
return false;
}
