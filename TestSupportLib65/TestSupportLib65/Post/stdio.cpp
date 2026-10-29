typedef unsigned long size_t;
typedef long ptrdiff_t;
typedef long long max_align_t;
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
extern "C"
{
int HostOpen(const char* szPath, int iMode);
int HostClose(int iHandle);
uint32_t HostRead(int iHandle, void* pvBuffer, uint32_t uiBytes);
uint32_t HostWrite(int iHandle, const void* pvBuffer, uint32_t uiBytes);
int HostSeek(int iHandle, long long llOffset, int iOrigin);
long long HostTell(int iHandle);
long long HostSize(int iHandle);
int HostTruncate(int iHandle, long long llSize);
int HostFlush(int iHandle);
int HostDelete(const char* szPath);
int HostRename(const char* szOld, const char* szNew);
int HostExists(const char* szPath);
long long HostFileSize(const char* szPath);
int HostMakeDir(const char* szPath);
int HostRemoveDir(const char* szPath);
int HostIsDirectory(const char* szPath);
int HostTouch(const char* szPath);
int HostCurrentDirectory(char* szDest, uint32_t uiSize);
int HostFindFile(const char* szDirectory, uint32_t uiIndex, char* szName, uint32_t uiSize);
}
struct FILE
{
int iKind;
int iHandle;
int iError;
int iEnd;
};
static FILE gsStdin = { 0, 0, 0, 1 };
static FILE gsStdout = { 1, 0, 0, 0 };
static FILE gsStderr = { 1, 0, 0, 0 };
FILE* stdin = &gsStdin;
FILE* stdout = &gsStdout;
FILE* stderr = &gsStderr;
struct SFormatOutput
{
FILE* pcFile;
char* szDest;
size_t uiSize;
size_t uiCount;
};
static void ConsoleWrite(char c)
{
*(volatile char*)0x00FF0100 = c;
}
int fputc(int c, FILE* pcFile)
{
char cByte;
cByte = (char)c;
if (fwrite(&cByte, 1, 1, pcFile) != 1)
{
return (-1);
}
return (unsigned char)c;
}
int putchar(int c)
{
return fputc(c, stdout);
}
int fputs(const char* sz, FILE* pcFile)
{
while (*sz)
{
if (fputc(*sz, pcFile) == (-1))
{
return (-1);
}
sz++;
}
return 0;
}
int puts(const char* sz)
{
if (fputs(sz, stdout) == (-1))
{
return (-1);
}
return putchar('\n');
}
FILE* fopen(const char* szName, const char* szMode)
{
FILE* pcFile;
int iMode;
int iHandle;
if (szMode[0] == 'r')
{
iMode = 0x01;
}
else if (szMode[0] == 'w')
{
iMode = 0x02 | 0x04 | 0x08;
}
else if (szMode[0] == 'a')
{
iMode = 0x02 | 0x04 | 0x10;
}
else
{
return 0L;
}
if (strchr(szMode, '+'))
{
iMode |= 0x01 | 0x02;
}
iHandle = HostOpen(szName, iMode);
if (iHandle == 0)
{
return 0L;
}
pcFile = (FILE*)malloc(sizeof(FILE));
pcFile->iKind = 2;
pcFile->iHandle = iHandle;
pcFile->iError = 0;
pcFile->iEnd = 0;
return pcFile;
}
int fclose(FILE* pcFile)
{
int iResult;
if (!pcFile || (pcFile->iKind != 2))
{
return (-1);
}
iResult = HostClose(pcFile->iHandle) ? 0 : (-1);
pcFile->iKind = 0;
free(pcFile);
return iResult;
}
size_t fread(void* pv, size_t uiSize, size_t uiCount, FILE* pcFile)
{
size_t uiBytes;
size_t uiRead;
if (!pcFile || (pcFile->iKind != 2) || (uiSize == 0) || (uiCount == 0))
{
return 0;
}
uiBytes = uiSize * uiCount;
uiRead = HostRead(pcFile->iHandle, pv, uiBytes);
if (uiRead < uiBytes)
{
pcFile->iEnd = 1;
}
return uiRead / uiSize;
}
size_t fwrite(const void* pv, size_t uiSize, size_t uiCount, FILE* pcFile)
{
const char* pc;
size_t uiBytes;
size_t i;
if (!pcFile || (uiSize == 0) || (uiCount == 0))
{
return 0;
}
uiBytes = uiSize * uiCount;
if (pcFile->iKind == 1)
{
pc = (const char*)pv;
for (i = 0; i < uiBytes; i++)
{
ConsoleWrite(pc[i]);
}
return uiCount;
}
if (pcFile->iKind == 2)
{
return HostWrite(pcFile->iHandle, pv, uiBytes) / uiSize;
}
return 0;
}
int fseek(FILE* pcFile, long iOffset, int iOrigin)
{
if (!pcFile || (pcFile->iKind != 2))
{
return -1;
}
pcFile->iEnd = 0;
return HostSeek(pcFile->iHandle, iOffset, iOrigin) ? 0 : -1;
}
long ftell(FILE* pcFile)
{
if (!pcFile || (pcFile->iKind != 2))
{
return -1;
}
return (long)HostTell(pcFile->iHandle);
}
int fflush(FILE* pcFile)
{
if (pcFile && (pcFile->iKind == 2))
{
return HostFlush(pcFile->iHandle) ? 0 : (-1);
}
return 0;
}
int feof(FILE* pcFile)
{
return pcFile ? pcFile->iEnd : 1;
}
int fgetc(FILE* pcFile)
{
unsigned char c;
if (fread(&c, 1, 1, pcFile) != 1)
{
return (-1);
}
return c;
}
int remove(const char* szName)
{
return HostDelete(szName) ? 0 : -1;
}
int rename(const char* szOld, const char* szNew)
{
return HostRename(szOld, szNew) ? 0 : -1;
}
static void Emit(SFormatOutput* psOutput, char c)
{
if (psOutput->pcFile)
{
fputc(c, psOutput->pcFile);
}
else if (psOutput->uiCount + 1 < psOutput->uiSize)
{
psOutput->szDest[psOutput->uiCount] = c;
}
psOutput->uiCount++;
}
static void EmitRepeated(SFormatOutput* psOutput, char c, int iCount)
{
while (iCount > 0)
{
Emit(psOutput, c);
iCount--;
}
}
static void EmitField(SFormatOutput* psOutput, const char* szPrefix, const char* szDigits, int iDigits, int iZeros, int iWidth, int iFlags)
{
int iPrefix;
int iPadding;
iPrefix = (int)strlen(szPrefix);
iPadding = iWidth - iPrefix - iZeros - iDigits;
if ((iPadding > 0) && !(iFlags & 0x01) && !(iFlags & 0x02))
{
EmitRepeated(psOutput, ' ', iPadding);
iPadding = 0;
}
while (*szPrefix)
{
Emit(psOutput, *szPrefix);
szPrefix++;
}
if ((iPadding > 0) && !(iFlags & 0x01))
{
EmitRepeated(psOutput, '0', iPadding);
iPadding = 0;
}
EmitRepeated(psOutput, '0', iZeros);
while (iDigits > 0)
{
Emit(psOutput, *szDigits);
szDigits++;
iDigits--;
}
EmitRepeated(psOutput, ' ', iPadding);
}
static void FormatInteger(SFormatOutput* psOutput, unsigned long long ullValue, bool bNegative, int iBase, int iWidth, int iPrecision, int iFlags)
{
char acDigits[24];
char szPrefix[4];
int iDigits;
int iZeros;
int iDigit;
const char* szAlphabet;
szAlphabet = (iFlags & 0x20) ? "0123456789ABCDEF" : "0123456789abcdef";
iDigits = 0;
while (ullValue != 0)
{
iDigit = (int)(ullValue % (unsigned)iBase);
ullValue /= (unsigned)iBase;
acDigits[sizeof(acDigits) - 1 - iDigits] = szAlphabet[iDigit];
iDigits++;
}
if ((iDigits == 0) && (iPrecision != 0))
{
acDigits[sizeof(acDigits) - 1] = '0';
iDigits = 1;
}
szPrefix[0] = 0;
if (bNegative)
{
strcpy(szPrefix, "-");
}
else if (iFlags & 0x04)
{
strcpy(szPrefix, "+");
}
else if (iFlags & 0x08)
{
strcpy(szPrefix, " ");
}
if ((iFlags & 0x10) && (iDigits > 0) && !((iDigits == 1) && (acDigits[sizeof(acDigits) - 1] == '0')))
{
if (iBase == 16)
{
strcat(szPrefix, (iFlags & 0x20) ? "0X" : "0x");
}
else if ((iBase == 8) && (iPrecision <= iDigits))
{
strcat(szPrefix, "0");
}
}
iZeros = (iPrecision > iDigits) ? iPrecision - iDigits : 0;
if (iPrecision >= 0)
{
iFlags &= ~0x02;
}
EmitField(psOutput, szPrefix, &acDigits[sizeof(acDigits) - iDigits], iDigits, iZeros, iWidth, iFlags);
}
static void DecimalDigits(double dValue, char* acDigits, int iCount, int* piExponent)
{
int iExponent;
int i;
int iDigit;
iExponent = 0;
if (dValue != 0.0)
{
while (dValue >= 1e16)
{
dValue /= 1e16;
iExponent += 16;
}
while (dValue >= 10.0)
{
dValue /= 10.0;
iExponent++;
}
while (dValue < 1e-16)
{
dValue *= 1e16;
iExponent -= 16;
}
while (dValue < 1.0)
{
dValue *= 10.0;
iExponent--;
}
}
for (i = 0; i < iCount; i++)
{
iDigit = (int)dValue;
if (iDigit > 9)
{
iDigit = 9;
}
acDigits[i] = (char)('0' + iDigit);
dValue = (dValue - iDigit) * 10.0;
}
*piExponent = iExponent;
}
static bool RoundDigits(char* acDigits, int iKeep, int iCount)
{
int i;
if ((iKeep >= iCount) || (acDigits[iKeep] < '5'))
{
return false;
}
for (i = iKeep - 1; i >= 0; i--)
{
if (acDigits[i] != '9')
{
acDigits[i]++;
return false;
}
acDigits[i] = '0';
}
if (iKeep > 0)
{
acDigits[0] = '1';
}
return true;
}
static void FormatFloat(SFormatOutput* psOutput, double dValue, char cConversion, int iWidth, int iPrecision, int iFlags)
{
char acDigits[40 + 2];
char acText[40 * 2 + 400];
char szPrefix[2];
int iExponent;
int iLength;
int iKeep;
int i;
int iDigit;
bool bNegative;
bool bExponent;
bool bTrim;
char cLower;
cLower = (char)(cConversion | 0x20);
if ((cConversion >= 'A') && (cConversion <= 'Z'))
{
iFlags |= 0x20;
}
if (iPrecision < 0)
{
iPrecision = 6;
}
bNegative = (dValue < 0.0) || ((dValue == 0.0) && (1.0 / dValue < 0.0));
if (bNegative)
{
dValue = -dValue;
}
szPrefix[0] = bNegative ? '-' : (iFlags & 0x04) ? '+' : (iFlags & 0x08) ? ' ' : 0;
szPrefix[1] = 0;
if (dValue != dValue)
{
EmitField(psOutput, szPrefix, (iFlags & 0x20) ? "NAN" : "nan", 3, 0, iWidth, iFlags & ~0x02);
return;
}
if (dValue > 1.7976931348623157e308)
{
EmitField(psOutput, szPrefix, (iFlags & 0x20) ? "INF" : "inf", 3, 0, iWidth, iFlags & ~0x02);
return;
}
DecimalDigits(dValue, acDigits, 40, &iExponent);
if (dValue == 0.0)
{
iExponent = 0;
}
bTrim = false;
bExponent = (cLower == 'e');
if (cLower == 'g')
{
if (iPrecision == 0)
{
iPrecision = 1;
}
if (RoundDigits(acDigits, iPrecision, 40))
{
iExponent++;
}
bExponent = (iExponent < -4) || (iExponent >= iPrecision);
iPrecision = bExponent ? iPrecision - 1 : iPrecision - 1 - iExponent;
bTrim = !(iFlags & 0x10);
}
iLength = 0;
if (bExponent)
{
if ((cLower != 'g') && RoundDigits(acDigits, iPrecision + 1, 40))
{
iExponent++;
}
acText[iLength++] = acDigits[0];
if ((iPrecision > 0) || (iFlags & 0x10))
{
acText[iLength++] = '.';
}
for (i = 1; i <= iPrecision; i++)
{
acText[iLength++] = (i < 40) ? acDigits[i] : '0';
}
}
else
{
iKeep = iExponent + 1 + iPrecision;
if (iKeep < 0)
{
for (i = 0; i < 40; i++)
{
acDigits[i] = '0';
}
}
else if ((cLower != 'g') && RoundDigits(acDigits, iKeep, 40))
{
iExponent++;
}
else if ((iKeep == 0) && (acDigits[0] >= '5'))
{
acDigits[0] = '1';
iExponent++;
}
else if (iKeep == 0)
{
acDigits[0] = '0';
}
if (iExponent < 0)
{
acText[iLength++] = '0';
}
for (i = 0; i <= iExponent; i++)
{
acText[iLength++] = (i < 40) ? acDigits[i] : '0';
}
if ((iPrecision > 0) || (iFlags & 0x10))
{
acText[iLength++] = '.';
}
for (i = 1; i <= iPrecision; i++)
{
iDigit = iExponent + i;
acText[iLength++] = ((iDigit >= 0) && (iDigit < 40)) ? acDigits[iDigit] : '0';
}
}
if (bTrim)
{
for (i = 0; (i < iLength) && (acText[i] != '.'); i++)
{
}
if (i < iLength)
{
while (acText[iLength - 1] == '0')
{
iLength--;
}
if (acText[iLength - 1] == '.')
{
iLength--;
}
}
}
if (bExponent)
{
acText[iLength++] = (iFlags & 0x20) ? 'E' : 'e';
acText[iLength++] = (iExponent < 0) ? '-' : '+';
if (iExponent < 0)
{
iExponent = -iExponent;
}
if (iExponent >= 100)
{
acText[iLength++] = (char)('0' + iExponent / 100);
}
acText[iLength++] = (char)('0' + (iExponent / 10) % 10);
acText[iLength++] = (char)('0' + iExponent % 10);
}
EmitField(psOutput, szPrefix, acText, iLength, 0, iWidth, iFlags);
}
static int Format(SFormatOutput* psOutput, const char* szFormat, va_list vaArguments)
{
int iFlags;
int iWidth;
int iPrecision;
int iLength;
char c;
long long llValue;
unsigned long long ullValue;
const char* sz;
int iBytes;
char szChar[2];
szChar[1] = 0;
while (*szFormat)
{
c = *szFormat++;
if (c != '%')
{
Emit(psOutput, c);
continue;
}
iFlags = 0;
for (;;)
{
c = *szFormat;
if (c == '-') iFlags |= 0x01;
else if (c == '0') iFlags |= 0x02;
else if (c == '+') iFlags |= 0x04;
else if (c == ' ') iFlags |= 0x08;
else if (c == '#') iFlags |= 0x10;
else break;
szFormat++;
}
iWidth = 0;
if (*szFormat == '*')
{
iWidth = (*(int*)(((vaArguments) += sizeof(int)) - sizeof(int)));
if (iWidth < 0)
{
iFlags |= 0x01;
iWidth = -iWidth;
}
szFormat++;
}
while ((*szFormat >= '0') && (*szFormat <= '9'))
{
iWidth = iWidth * 10 + (*szFormat - '0');
szFormat++;
}
iPrecision = -1;
if (*szFormat == '.')
{
szFormat++;
iPrecision = 0;
if (*szFormat == '*')
{
iPrecision = (*(int*)(((vaArguments) += sizeof(int)) - sizeof(int)));
szFormat++;
}
while ((*szFormat >= '0') && (*szFormat <= '9'))
{
iPrecision = iPrecision * 10 + (*szFormat - '0');
szFormat++;
}
}
iLength = 0;
iBytes = 4;
for (;;)
{
c = *szFormat;
if (c == 'h')
{
iLength = (iLength == 'h') ? 'H' : 'h';
}
else if (c == 'l')
{
iBytes = (iLength == 'l') ? 8 : 4;
iLength = 'l';
}
else if ((c == 'j') || (c == 'q')) iBytes = 8;
else if ((c == 'z') || (c == 't')) iBytes = 4;
else if (c == 'L') iLength = 'L';
else if ((c == 'I') && (szFormat[1] == '6') && (szFormat[2] == '4'))
{
iBytes = 8;
szFormat += 2;
}
else break;
szFormat++;
}
c = *szFormat;
if (c == 0)
{
break;
}
szFormat++;
switch (c)
{
case 'd':
case 'i':
llValue = (iBytes == 8) ? (*(long long*)(((vaArguments) += sizeof(long long)) - sizeof(long long))) : (long long)(*(int*)(((vaArguments) += sizeof(int)) - sizeof(int)));
if (iLength == 'h')
{
llValue = (short)llValue;
}
else if (iLength == 'H')
{
llValue = (signed char)llValue;
}
ullValue = (llValue < 0) ? (unsigned long long)0 - (unsigned long long)llValue : (unsigned long long)llValue;
FormatInteger(psOutput, ullValue, llValue < 0, 10, iWidth, iPrecision, iFlags);
break;
case 'u':
case 'x':
case 'X':
case 'o':
case 'b':
ullValue = (iBytes == 8) ? (*(unsigned long long*)(((vaArguments) += sizeof(unsigned long long)) - sizeof(unsigned long long))) : (unsigned long long)(*(unsigned int*)(((vaArguments) += sizeof(unsigned int)) - sizeof(unsigned int)));
if (iLength == 'h')
{
ullValue = (unsigned short)ullValue;
}
else if (iLength == 'H')
{
ullValue = (unsigned char)ullValue;
}
if (c == 'X')
{
iFlags |= 0x20;
}
FormatInteger(psOutput, ullValue, false, (c == 'u') ? 10 : (c == 'o') ? 8 : (c == 'b') ? 2 : 16, iWidth, iPrecision, iFlags & ~(0x04 | 0x08));
break;
case 'p':
ullValue = (unsigned long long)(size_t)(*(void**)(((vaArguments) += sizeof(void*)) - sizeof(void*)));
FormatInteger(psOutput, ullValue, false, 16, iWidth, 8, (iFlags & 0x01) | 0x10);
break;
case 'c':
szChar[0] = (char)(*(int*)(((vaArguments) += sizeof(int)) - sizeof(int)));
EmitField(psOutput, "", szChar, 1, 0, iWidth, iFlags & ~0x02);
break;
case 's':
sz = (*(const char**)(((vaArguments) += sizeof(const char*)) - sizeof(const char*)));
if (!sz)
{
sz = "(null)";
}
iBytes = (int)strlen(sz);
if ((iPrecision >= 0) && (iPrecision < iBytes))
{
iBytes = iPrecision;
}
EmitField(psOutput, "", sz, iBytes, 0, iWidth, iFlags & ~0x02);
break;
case 'f':
case 'F':
case 'e':
case 'E':
case 'g':
case 'G':
FormatFloat(psOutput, (*(double*)(((vaArguments) += sizeof(double)) - sizeof(double))), c, iWidth, iPrecision, iFlags);
break;
case 'n':
*(*(int**)(((vaArguments) += sizeof(int*)) - sizeof(int*))) = (int)psOutput->uiCount;
break;
default:
Emit(psOutput, c);
break;
}
}
if (!psOutput->pcFile && (psOutput->uiSize > 0))
{
psOutput->szDest[(psOutput->uiCount < psOutput->uiSize) ? psOutput->uiCount : psOutput->uiSize - 1] = 0;
}
return (int)psOutput->uiCount;
}
int vsnprintf(char* szDest, size_t uiSize, const char* szFormat, va_list vaArguments)
{
SFormatOutput sOutput;
sOutput.pcFile = 0L;
sOutput.szDest = szDest;
sOutput.uiSize = uiSize;
sOutput.uiCount = 0;
return Format(&sOutput, szFormat, vaArguments);
}
int vsprintf(char* szDest, const char* szFormat, va_list vaArguments)
{
return vsnprintf(szDest, 0x7FFFFFFF, szFormat, vaArguments);
}
int vfprintf(FILE* pcFile, const char* szFormat, va_list vaArguments)
{
SFormatOutput sOutput;
sOutput.pcFile = pcFile;
sOutput.szDest = 0L;
sOutput.uiSize = 0;
sOutput.uiCount = 0;
return Format(&sOutput, szFormat, vaArguments);
}
int vprintf(const char* szFormat, va_list vaArguments)
{
return vfprintf(stdout, szFormat, vaArguments);
}
int printf(const char* szFormat, ...)
{
va_list vaArguments;
int iResult;
((vaArguments) = (char*)&(szFormat) + sizeof(szFormat));
iResult = vfprintf(stdout, szFormat, vaArguments);
((vaArguments) = 0);
return iResult;
}
int fprintf(FILE* pcFile, const char* szFormat, ...)
{
va_list vaArguments;
int iResult;
((vaArguments) = (char*)&(szFormat) + sizeof(szFormat));
iResult = vfprintf(pcFile, szFormat, vaArguments);
((vaArguments) = 0);
return iResult;
}
int sprintf(char* szDest, const char* szFormat, ...)
{
va_list vaArguments;
int iResult;
((vaArguments) = (char*)&(szFormat) + sizeof(szFormat));
iResult = vsnprintf(szDest, 0x7FFFFFFF, szFormat, vaArguments);
((vaArguments) = 0);
return iResult;
}
int snprintf(char* szDest, size_t uiSize, const char* szFormat, ...)
{
va_list vaArguments;
int iResult;
((vaArguments) = (char*)&(szFormat) + sizeof(szFormat));
iResult = vsnprintf(szDest, uiSize, szFormat, vaArguments);
((vaArguments) = 0);
return iResult;
}
