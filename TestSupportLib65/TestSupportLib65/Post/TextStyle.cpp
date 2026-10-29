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
typedef uint32 ARGB32;
uint8 Get8BitAlphaColour(ARGB32 uiColour);
uint8 Get8BitBlueColour(ARGB32 uiColour);
uint8 Get8BitGreenColour(ARGB32 uiColour);
uint8 Get8BitRedColour(ARGB32 uiColour);
uint8 Clamp8BitColour(uint32 uiColour);
ARGB32 Set8BitAlphaColour(uint32 iAlpha);
ARGB32 Set8BitBlueColour(uint32 iBlue);
ARGB32 Set8BitGreenColour(uint32 iGreen);
ARGB32 Set8BitRedColour(uint32 iRed);
ARGB32 Set8BitAlphaColour(uint8 iAlpha);
ARGB32 Set8BitBlueColour(uint8 iBlue);
ARGB32 Set8BitGreenColour(uint8 iGreen);
ARGB32 Set8BitRedColour(uint8 iRed);
float32 Convert8BitColourToFloat(ARGB32 uiColour);
uint8 ConvertFloatTo8BitColour(float32 fColour);
ARGB32 Set32BitColour(uint32 r, uint32 g, uint32 b, uint32 a);
ARGB32 Set32BitColour(uint8 r, uint8 g, uint8 b, uint8 a);
ARGB32 Set32BitColour(float32 r, float32 g, float32 b, float32 a);
ARGB32 Set32BitColour(uint32 r, uint32 g, uint32 b);
ARGB32 Set32BitColour(uint8 r, uint8 g, uint8 b);
ARGB32 Set32BitColour(float32 r, float32 g, float32 b);
void Get32BitColour(uint32* r, uint32* g, uint32* b, uint32* a, ARGB32 uiColour);
void Get32BitColour(float32* r, float32* g, float32* b, float32* a, ARGB32 uiColour);
void Get32BitColour(float32* r, float32* g, float32* b, ARGB32 uiColour);
ARGB32 Add32BitColours(ARGB32 uiColour1, ARGB32 uiColour2);
ARGB32 Subtract32BitColours(ARGB32 uiColour1, ARGB32 uiColour2);
ARGB32 Minimum32BitColour(ARGB32 uiColour1, ARGB32 uiColour2);
ARGB32 Maximum32BitColour(ARGB32 uiColour1, ARGB32 uiColour2);
ARGB32 Modulate32BitColours(ARGB32 uiColour1, ARGB32 uiColour2);
ARGB32 Weight32BitColours(ARGB32 uiColour1, ARGB32 uiColour2, float32 fWeight1);
ARGB32 BlendAlpha32BitColours(ARGB32 uiColour1, ARGB32 uiColour2);
uint8 GetM8BitAlphaColour(ARGB32 uiColour);
uint8 GetM8BitBlueColour(ARGB32 uiColour);
uint8 GetM8BitGreenColour(ARGB32 uiColour);
uint8 GetM8BitRedColour(ARGB32 uiColour);
ARGB32 SetM32BitColour(uint8 r, uint8 g, uint8 b, uint8 a);
ARGB32 SetM8BitAlphaColour(uint8 iAlpha);
ARGB32 SetM8BitBlueColour(uint8 iBlue);
ARGB32 SetM8BitGreenColour(uint8 iGreen);
ARGB32 SetM8BitRedColour(uint8 iRed);
uint32 ConvertToBGR(ARGB32 uiColour);
uint32 ConvertToBGRA(ARGB32 uiColour);
enum EFontStyle
{
FS_Regular = 0,
FS_Bold = 1,
FS_Italic = 2,
FS_BoldItalic = 3,
};
enum ETextPosition
{
TP_Normal,
TP_Superscript,
TP_Subscript,
};
struct STextStyle
{
bool bBold;
bool bItalic;
float32 fPixelSize;
ARGB32 sColour;
ETextPosition ePosition;
bool bUnderline;
bool bOverline;
bool bStrikethrough;
void Init(void);
void Init(bool bBold, bool bItalic, float32 fPixelSize, ARGB32 sColour);
EFontStyle GetFontStyle(void);
uint8 GetDecorations(void);
bool Equals(STextStyle* psOther);
bool EqualsFont(STextStyle* psOther);
};
struct STextStyleOverride
{
uint16 uiSet;
STextStyle sStyle;
void Init(void);
void SetColour(ARGB32 sColour);
void SetBold(bool bBold);
void SetItalic(bool bItalic);
void SetPixelSize(float32 fPixelSize);
void SetPosition(ETextPosition ePosition);
void SetUnderline(bool bUnderline);
void SetOverline(bool bOverline);
void SetStrikethrough(bool bStrikethrough);
void ApplyTo(STextStyle* psStyle);
bool ChangesFont(void);
};
void STextStyle::Init(void)
{
Init(false, false, 0.0f, 0xFFFFFFFF);
}
void STextStyle::Init(bool bBold, bool bItalic, float32 fPixelSize, ARGB32 sColour)
{
this->bBold = bBold;
this->bItalic = bItalic;
this->fPixelSize = fPixelSize;
this->sColour = sColour;
ePosition = TP_Normal;
bUnderline = false;
bOverline = false;
bStrikethrough = false;
}
EFontStyle STextStyle::GetFontStyle(void)
{
return (EFontStyle)((bBold ? FS_Bold : FS_Regular) | (bItalic ? FS_Italic : FS_Regular));
}
bool STextStyle::Equals(STextStyle* psOther)
{
return EqualsFont(psOther) && (sColour == psOther->sColour) && (bUnderline == psOther->bUnderline) && (bOverline == psOther->bOverline) && (bStrikethrough == psOther->bStrikethrough);
}
uint8 STextStyle::GetDecorations(void)
{
return (bUnderline ? 0x01 : 0) | (bOverline ? 0x02 : 0) | (bStrikethrough ? 0x04 : 0);
}
bool STextStyle::EqualsFont(STextStyle* psOther)
{
return (bBold == psOther->bBold) && (bItalic == psOther->bItalic) && (fPixelSize == psOther->fPixelSize) && (ePosition == psOther->ePosition);
}
void STextStyleOverride::Init(void)
{
uiSet = 0;
sStyle.Init();
}
void STextStyleOverride::SetColour(ARGB32 sColour)
{
sStyle.sColour = sColour;
uiSet |= 0x01;
}
void STextStyleOverride::SetBold(bool bBold)
{
sStyle.bBold = bBold;
uiSet |= 0x02;
}
void STextStyleOverride::SetItalic(bool bItalic)
{
sStyle.bItalic = bItalic;
uiSet |= 0x04;
}
void STextStyleOverride::SetPixelSize(float32 fPixelSize)
{
sStyle.fPixelSize = fPixelSize;
uiSet |= 0x08;
}
void STextStyleOverride::SetPosition(ETextPosition ePosition)
{
sStyle.ePosition = ePosition;
uiSet |= 0x10;
}
void STextStyleOverride::SetUnderline(bool bUnderline)
{
sStyle.bUnderline = bUnderline;
uiSet |= 0x20;
}
void STextStyleOverride::SetOverline(bool bOverline)
{
sStyle.bOverline = bOverline;
uiSet |= 0x40;
}
void STextStyleOverride::SetStrikethrough(bool bStrikethrough)
{
sStyle.bStrikethrough = bStrikethrough;
uiSet |= 0x80;
}
void STextStyleOverride::ApplyTo(STextStyle* psStyle)
{
if (uiSet & 0x01)
{
psStyle->sColour = sStyle.sColour;
}
if (uiSet & 0x02)
{
psStyle->bBold = sStyle.bBold;
}
if (uiSet & 0x04)
{
psStyle->bItalic = sStyle.bItalic;
}
if (uiSet & 0x08)
{
psStyle->fPixelSize = sStyle.fPixelSize;
}
if (uiSet & 0x10)
{
psStyle->ePosition = sStyle.ePosition;
}
if (uiSet & 0x20)
{
psStyle->bUnderline = sStyle.bUnderline;
}
if (uiSet & 0x40)
{
psStyle->bOverline = sStyle.bOverline;
}
if (uiSet & 0x80)
{
psStyle->bStrikethrough = sStyle.bStrikethrough;
}
}
bool STextStyleOverride::ChangesFont(void)
{
return (uiSet & (0x02 | 0x04 | 0x08 | 0x10)) != 0;
}
