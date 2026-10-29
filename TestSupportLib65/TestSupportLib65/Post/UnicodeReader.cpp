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
class CChars;
class CKillable
{
public:
virtual void Kill(void) =0;
virtual void Print(CChars* psz);
};
enum EUnicodeEncoding
{
UE_Unknown,
UE_UTF8,
UE_UTF8BOM,
UE_UTF16LE,
UE_UTF16BE,
};
class CUnicode : public CKillable
{
protected:
uint16 muiError;
uint16 muiTooSmall;
uint16 muiZWJ;
public:
void Init(void);
void Kill(void) override;
size GetUnicodeCodePointLength(uint16 uiChar);
size GetUnicodeCodePointLength(uint32 uiChar);
size AppendCodePoint(uint16 uiCodePoint, size uiCodePointLength, uint8* puiBuffer, size uiBufferPos, size uiBufferLength);
size AppendCodePoint(uint32 uiCodePoint, size uiCodePointLength, uint8* puiBuffer, size uiBufferPos, size uiBufferLength);
size GetUTF16Length(uint32 uiCodePoint);
uint16 GetUTF16ElementUint16(uint32 uiCodePoint);
uint32 GetUTF16ElementUint32(uint32 uiCodePoint);
size GetUTF8Length(uint32 uiCodePoint);
uint16 GetUTF8ElementUint16(uint32 uiCodePoint);
uint32 GetUTF8ElementUint32(uint32 uiCodePoint);
size GetError(void);
uint16 GetZWJCodePoint(void);
};
EUnicodeEncoding GetUnicodeEncoding(void* puiData, size uiDataLength);
class CUnicodeReader : public CUnicode
{
protected:
uint32 muiUTF8ZWJBytes;
uint32 muiUTF16LEZWJBytes;
uint32 muiUTF16BEZWJBytes;
uint32 muiUTF8BOMBytes;
uint32 muiUTF16LEBOMBytes;
uint32 muiUTF16BEBOMBytes;
public:
void Init(void);
void Kill(void) override;
virtual uint16 GetCodePointUint16(void) =0;
virtual uint32 GetCodePointUint32(void) =0;
virtual size GetCodePointMulti(uint8* puiBuffer, size uiBufferLength) =0;
virtual void* GetCurrentData(void) =0;
virtual bool GetByteOrderMark(void) =0;
virtual size PeekUTFBytes(void) =0;
virtual size GetPosition(void) =0;
size GetZWJLength(EUnicodeEncoding eEncoding);
uint8* GetZWJBytes(EUnicodeEncoding eEncoding);
size GetBOMLength(EUnicodeEncoding eEncoding);
uint8* GetBOMBytes(EUnicodeEncoding eEncoding);
bool IsTooSmallOrError(uint16 ui);
bool IsError(uint16 ui);
bool IsError(uint32 ui);
bool IsTooSmall(uint16 ui);
uint32 MakeCodePointUint32FromBuffer(uint8* puiCodePointBuffer, size uiBufferLength);
uint16 MakeCodePointUint16FromBuffer(uint8* puiCodePointBuffer, size uiBufferLength);
};
void CUnicodeReader::Init(void)
{
CUnicode::Init();
muiUTF8ZWJBytes = 0x8D80E2;
muiUTF16LEZWJBytes = 0x200D;
muiUTF16BEZWJBytes = 0x0D20;
muiUTF8BOMBytes = 0xBFBBEF;
muiUTF16LEBOMBytes = 0xFEFF;
muiUTF16BEBOMBytes = 0xFFFE;
}
void CUnicodeReader::Kill(void)
{
CUnicode::Kill();
}
bool CUnicodeReader::IsTooSmallOrError(uint16 ui)
{
return (ui == muiError) || (ui == muiTooSmall);
}
bool CUnicodeReader::IsError(uint16 ui)
{
return ui == muiError;
}
bool CUnicodeReader::IsError(uint32 ui)
{
return ui == muiError;
}
bool CUnicodeReader::IsTooSmall(uint16 ui)
{
return ui == muiTooSmall;
}
size CUnicodeReader::GetBOMLength(EUnicodeEncoding eEncoding)
{
switch (eEncoding)
{
case UE_UTF8:
return 0;
case UE_UTF8BOM:
return 3;
case UE_UTF16LE:
case UE_UTF16BE:
return 2;
default:
return 0;
}
}
uint8* CUnicodeReader::GetBOMBytes(EUnicodeEncoding eEncoding)
{
switch (eEncoding)
{
case UE_UTF8:
return 0L;
case UE_UTF8BOM:
return (uint8*)&muiUTF8BOMBytes;
case UE_UTF16LE:
return (uint8*)&muiUTF16LEBOMBytes;
case UE_UTF16BE:
return (uint8*)&muiUTF16BEBOMBytes;
default:
return 0L;
}
}
size CUnicodeReader::GetZWJLength(EUnicodeEncoding eEncoding)
{
switch (eEncoding)
{
case UE_UTF8:
case UE_UTF8BOM:
return 3;
case UE_UTF16LE:
case UE_UTF16BE:
return 2;
default:
return 0;
}
}
uint8* CUnicodeReader::GetZWJBytes(EUnicodeEncoding eEncoding)
{
switch (eEncoding)
{
case UE_UTF8:
case UE_UTF8BOM:
return (uint8*)&muiUTF8ZWJBytes;
case UE_UTF16LE:
return (uint8*)&muiUTF16LEZWJBytes;
case UE_UTF16BE:
return (uint8*)&muiUTF16BEZWJBytes;
default:
return 0L;
}
}
uint32 CUnicodeReader::MakeCodePointUint32FromBuffer(uint8* puiCodePointBuffer, size uiBufferLength)
{
uint32 uiCodePoint;
size uiShift;
size ui;
ui = 0;
uiShift = 0;
uiCodePoint = 0;
while (ui != uiBufferLength)
{
uiCodePoint |= (uint32)puiCodePointBuffer[ui] << uiShift;
ui++;
uiShift += 8;
}
return uiCodePoint;
}
uint16 CUnicodeReader::MakeCodePointUint16FromBuffer(uint8* puiCodePointBuffer, size uiBufferLength)
{
uint16 uiCodePoint;
uiCodePoint = puiCodePointBuffer[0];
if (uiBufferLength == 2)
{
uiCodePoint |= (uint32)puiCodePointBuffer[1] << 8;
}
return uiCodePoint;
}
