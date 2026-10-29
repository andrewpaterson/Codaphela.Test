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
void CHuffmanEncoder::Init(uint32* puiFrequencies, int iNumSymbols, int iMaxBits)
{
uint32 auiFrequencies[288];
int i;
miNumSymbols = iNumSymbols;
memcpy(auiFrequencies, puiFrequencies, iNumSymbols * sizeof(uint32));
while (!BuildLengths(auiFrequencies, iMaxBits))
{
for (i = 0; i < iNumSymbols; i++)
{
if (auiFrequencies[i] != 0)
{
auiFrequencies[i] = (auiFrequencies[i] >> 1) | 1;
}
}
}
BuildCodes();
}
void CHuffmanEncoder::Init(uint8* puiLengths, int iNumSymbols)
{
miNumSymbols = iNumSymbols;
memcpy(mauiLengths, puiLengths, iNumSymbols);
BuildCodes();
}
void CHuffmanEncoder::Kill(void)
{
miNumSymbols = 0;
}
bool CHuffmanEncoder::BuildLengths(uint32* puiFrequencies, int iMaxBits)
{
uint32 auiWeights[(288 * 2)];
int16 aiParents[(288 * 2)];
int16 aiSymbols[288];
int16 aiActive[288];
int iNumLeaves;
int iNumNodes;
int iNumActive;
int iFirst;
int iSecond;
int i;
int iNode;
int iDepth;
int iSymbol;
memset(mauiLengths, 0, miNumSymbols);
iNumLeaves = 0;
for (iSymbol = 0; iSymbol < miNumSymbols; iSymbol++)
{
if (puiFrequencies[iSymbol] != 0)
{
aiSymbols[iNumLeaves] = (int16)iSymbol;
auiWeights[iNumLeaves] = puiFrequencies[iSymbol];
aiParents[iNumLeaves] = -1;
aiActive[iNumLeaves] = (int16)iNumLeaves;
iNumLeaves++;
}
}
if (iNumLeaves < 2)
{
mauiLengths[0] = 1;
mauiLengths[1] = 1;
if (iNumLeaves == 1)
{
mauiLengths[aiSymbols[0]] = 1;
if (aiSymbols[0] > 1)
{
mauiLengths[1] = 0;
}
}
return true;
}
iNumNodes = iNumLeaves;
iNumActive = iNumLeaves;
while (iNumActive > 1)
{
iFirst = -1;
iSecond = -1;
for (i = 0; i < iNumActive; i++)
{
iNode = aiActive[i];
if ((iFirst == -1) || (auiWeights[iNode] < auiWeights[aiActive[iFirst]]))
{
iSecond = iFirst;
iFirst = i;
}
else if ((iSecond == -1) || (auiWeights[iNode] < auiWeights[aiActive[iSecond]]))
{
iSecond = i;
}
}
auiWeights[iNumNodes] = auiWeights[aiActive[iFirst]] + auiWeights[aiActive[iSecond]];
aiParents[iNumNodes] = -1;
aiParents[aiActive[iFirst]] = (int16)iNumNodes;
aiParents[aiActive[iSecond]] = (int16)iNumNodes;
aiActive[iFirst] = (int16)iNumNodes;
aiActive[iSecond] = aiActive[iNumActive - 1];
iNumActive--;
iNumNodes++;
}
for (i = 0; i < iNumLeaves; i++)
{
iDepth = 0;
for (iNode = i; aiParents[iNode] != -1; iNode = aiParents[iNode])
{
iDepth++;
}
if (iDepth > iMaxBits)
{
return false;
}
mauiLengths[aiSymbols[i]] = (uint8)iDepth;
}
return true;
}
void CHuffmanEncoder::BuildCodes(void)
{
uint16 auiCount[15 + 1];
uint16 auiNextCode[15 + 1];
uint16 uiCode;
uint16 uiReversed;
int iLength;
int iSymbol;
int i;
memset(auiCount, 0, sizeof(auiCount));
for (iSymbol = 0; iSymbol < miNumSymbols; iSymbol++)
{
auiCount[mauiLengths[iSymbol]]++;
}
auiCount[0] = 0;
uiCode = 0;
for (iLength = 1; iLength <= 15; iLength++)
{
uiCode = (uint16)((uiCode + auiCount[iLength - 1]) << 1);
auiNextCode[iLength] = uiCode;
}
for (iSymbol = 0; iSymbol < miNumSymbols; iSymbol++)
{
iLength = mauiLengths[iSymbol];
if (iLength != 0)
{
uiCode = auiNextCode[iLength];
auiNextCode[iLength]++;
uiReversed = 0;
for (i = 0; i < iLength; i++)
{
uiReversed = (uint16)((uiReversed << 1) | ((uiCode >> i) & 1));
}
mauiCodes[iSymbol] = uiReversed;
}
else
{
mauiCodes[iSymbol] = 0;
}
}
}
void CHuffmanEncoder::Write(CBitWriter* pcWriter, int iSymbol)
{
pcWriter->WriteBits(mauiCodes[iSymbol], mauiLengths[iSymbol]);
}
int CHuffmanEncoder::GetLength(int iSymbol)
{
return mauiLengths[iSymbol];
}
uint8* CHuffmanEncoder::GetLengths(void)
{
return mauiLengths;
}
int CHuffmanEncoder::GetNumSymbols(void)
{
return miNumSymbols;
}
