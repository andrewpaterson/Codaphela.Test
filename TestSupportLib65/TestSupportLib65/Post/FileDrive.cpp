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
class CFileDrive
{
protected:
uint64 muiMaxSector;
uint32 muiSectorSize;
public:
void Init(uint32 uiSectorSize);
virtual void Kill(void) =0;
virtual bool Read(uint64 uiSector, void* pvData) =0;
virtual bool Read(uint64 uiSector, uint32 uiNumSectors, void* pvData) =0;
virtual bool Write(uint64 uiSector, void* pvData) =0;
virtual bool Write(uint64 uiSector, uint32 uiNumSectors, void* pvData) =0;
virtual bool Erase(uint64 uiStartSector, uint64 uiStopSectorInclusive) =0;
uint64 GetTotalSectors(void);
uint32 GetSectorSize(void);
virtual uint32 GetPageSize(void);
uint64 SetMaxSectorForTesting(uint64 uiMaxSector);
};
void CFileDrive::Init(uint32 uiSectorSize)
{
muiMaxSector = 0;
muiSectorSize = uiSectorSize;
}
uint64 CFileDrive::GetTotalSectors(void)
{
return muiMaxSector - 1;
}
uint32 CFileDrive::GetSectorSize(void)
{
return muiSectorSize;
}
uint32 CFileDrive::GetPageSize(void)
{
return 1;
}
uint64 CFileDrive::SetMaxSectorForTesting(uint64 uiMaxSector)
{
uint64 uiOldMaxSector = muiMaxSector;
muiMaxSector = uiMaxSector;
return uiOldMaxSector;
}
