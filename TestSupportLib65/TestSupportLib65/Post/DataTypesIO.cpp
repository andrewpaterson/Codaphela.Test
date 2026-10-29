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
class _CForceVirtualSuper1
{
virtual void _ForceVirtual1(void) {};
};
class _CForceVirtualSuper2
{
virtual void _ForceVirtual2(void) {};
};
class CConstructable : public _CForceVirtualSuper1, public _CForceVirtualSuper2
{
public:
virtual const char* ClassName(void) =0;
virtual size ClassSize(void) =0;
};
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
class CFileIO : public CFileReader, public CFileWriter
{
};
struct SDataTypeIO
{
bool Save(CFileWriter* pcFileWriter);
bool Load(CFileReader* pcFileReader);
};
typedef bool (SDataTypeIO::*DataIO_FileWriter)(CFileWriter*);
typedef bool (SDataTypeIO::*DataIO_FileReader)(CFileReader*);
struct SDataIO
{
DataIO_FileWriter fWriter;
DataIO_FileReader fReader;
};
class CDataIO
{
public:
virtual bool WriteData(CFileWriter* pcFileWriter, void* pvData) =0;
virtual bool ReadData(CFileReader* pcFileReader, void* pvData) =0;
};
template<class M>
bool SaveMultiple(M* psThis, CFileWriter* pcFileWriter, size uiCount)
{
size i;
bool bResult;
for (i = 0; i < uiCount; i++)
{
bResult = psThis->Save(pcFileWriter);
if (!bResult)
{
return false;
}
psThis++;
}
return true;
}
template<class M>
bool LoadMultiple(M* psThis, CFileReader* pcFileReader, size uiCount)
{
size i;
bool bResult;
for (i = 0; i < uiCount; i++)
{
bResult = psThis->Load(pcFileReader);
if (!bResult)
{
return false;
}
psThis++;
}
return true;
}
struct SIOInt8 { public:const char* ClassName(void){ return "SIOInt8";}size ClassSize(void){ return sizeof(SIOInt8);} int8 mVal; bool Save(CFileWriter* pcFileWriter) { return pcFileWriter-> WriteInt8 (mVal); } bool Load(CFileReader* pcFileReader) { return pcFileReader-> ReadInt8 (&mVal); } };
struct SIOInt16 { public:const char* ClassName(void){ return "SIOInt16";}size ClassSize(void){ return sizeof(SIOInt16);} int16 mVal; bool Save(CFileWriter* pcFileWriter) { return pcFileWriter-> WriteInt16 (mVal); } bool Load(CFileReader* pcFileReader) { return pcFileReader-> ReadInt16 (&mVal); } };
struct SIOInt32 { public:const char* ClassName(void){ return "SIOInt32";}size ClassSize(void){ return sizeof(SIOInt32);} int32 mVal; bool Save(CFileWriter* pcFileWriter) { return pcFileWriter-> WriteInt32 (mVal); } bool Load(CFileReader* pcFileReader) { return pcFileReader-> ReadInt32 (&mVal); } };
struct SIOInt64 { public:const char* ClassName(void){ return "SIOInt64";}size ClassSize(void){ return sizeof(SIOInt64);} int64 mVal; bool Save(CFileWriter* pcFileWriter) { return pcFileWriter-> WriteInt64 (mVal); } bool Load(CFileReader* pcFileReader) { return pcFileReader-> ReadInt64 (&mVal); } };
struct SIOUInt8 { public:const char* ClassName(void){ return "SIOUInt8";}size ClassSize(void){ return sizeof(SIOUInt8);} uint8 mVal; bool Save(CFileWriter* pcFileWriter) { return pcFileWriter-> WriteInt8 (mVal); } bool Load(CFileReader* pcFileReader) { return pcFileReader-> ReadInt8 (&mVal); } };
struct SIOUInt16 { public:const char* ClassName(void){ return "SIOUInt16";}size ClassSize(void){ return sizeof(SIOUInt16);} uint16 mVal; bool Save(CFileWriter* pcFileWriter) { return pcFileWriter-> WriteInt16 (mVal); } bool Load(CFileReader* pcFileReader) { return pcFileReader-> ReadInt16 (&mVal); } };
struct SIOUInt32 { public:const char* ClassName(void){ return "SIOUInt32";}size ClassSize(void){ return sizeof(SIOUInt32);} uint32 mVal; bool Save(CFileWriter* pcFileWriter) { return pcFileWriter-> WriteInt32 (mVal); } bool Load(CFileReader* pcFileReader) { return pcFileReader-> ReadInt32 (&mVal); } };
struct SIOUInt64 { public:const char* ClassName(void){ return "SIOUInt64";}size ClassSize(void){ return sizeof(SIOUInt64);} uint64 mVal; bool Save(CFileWriter* pcFileWriter) { return pcFileWriter-> WriteInt64 (mVal); } bool Load(CFileReader* pcFileReader) { return pcFileReader-> ReadInt64 (&mVal); } };
struct SIOBool { public:const char* ClassName(void){ return "SIOBool";}size ClassSize(void){ return sizeof(SIOBool);} bool mVal; bool Save(CFileWriter* pcFileWriter) { return pcFileWriter-> WriteBool (mVal); } bool Load(CFileReader* pcFileReader) { return pcFileReader-> ReadBool (&mVal); } };
struct SIOChar8 { public:const char* ClassName(void){ return "SIOChar8";}size ClassSize(void){ return sizeof(SIOChar8);} char8 mVal; bool Save(CFileWriter* pcFileWriter) { return pcFileWriter-> WriteChar (mVal); } bool Load(CFileReader* pcFileReader) { return pcFileReader-> ReadChar (&mVal); } };
struct SIOChar16 { public:const char* ClassName(void){ return "SIOChar16";}size ClassSize(void){ return sizeof(SIOChar16);} char16 mVal; bool Save(CFileWriter* pcFileWriter) { return pcFileWriter-> WriteWChar (mVal); } bool Load(CFileReader* pcFileReader) { return pcFileReader-> ReadWChar (&mVal); } };
struct SIOFloat32 { public:const char* ClassName(void){ return "SIOFloat32";}size ClassSize(void){ return sizeof(SIOFloat32);} float32 mVal; bool Save(CFileWriter* pcFileWriter) { return pcFileWriter-> WriteFloat (mVal); } bool Load(CFileReader* pcFileReader) { return pcFileReader-> ReadFloat (&mVal); } };
struct SIOFloat64 { public:const char* ClassName(void){ return "SIOFloat64";}size ClassSize(void){ return sizeof(SIOFloat64);} float64 mVal; bool Save(CFileWriter* pcFileWriter) { return pcFileWriter-> WriteFloat (mVal); } bool Load(CFileReader* pcFileReader) { return pcFileReader-> ReadFloat (&mVal); } };
struct SIOVoid
{
public:const char* ClassName(void){ return "SIOVoid";}size ClassSize(void){ return sizeof(SIOVoid);};
bool Save(CFileWriter* pcFileWriter)
{
return true;
}
bool Load(CFileReader* pcFileReader)
{
return true;
}
};
struct SIOData
{
public:const char* ClassName(void){ return "SIOData";}size ClassSize(void){ return sizeof(SIOData);};
bool Save(CFileWriter* pcFileWriter)
{
return pcFileWriter->WriteData(this, 1);
}
bool Load(CFileReader* pcFileReader)
{
return pcFileReader->ReadData(this, 1);
}
};
