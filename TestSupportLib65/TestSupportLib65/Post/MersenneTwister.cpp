typedef unsigned long size_t;
typedef long ptrdiff_t;
typedef long long max_align_t;
typedef long time_t;
typedef long clock_t;
struct tm
{
int tm_sec;
int tm_min;
int tm_hour;
int tm_mday;
int tm_mon;
int tm_year;
int tm_wday;
int tm_yday;
int tm_isdst;
};
extern "C"
{
time_t time(time_t* ptTime);
clock_t clock(void);
struct tm* localtime(const time_t* ptTime);
struct tm* gmtime(const time_t* ptTime);
time_t mktime(struct tm* psTime);
double difftime(time_t tEnd, time_t tStart);
size_t strftime(char* szDest, size_t uiMax, const char* szFormat, const struct tm* psTime);
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
class CMersenneTwister
{
private:
uint32 mauiState[624];
uint32 muiIndex;
void Twist(void);
public:
void Init(void);
void Init(uint32 iSeed);
void Kill(void);
uint32 Next(void);
int32 Next(int32 iMin, int32 iMaxInclusive);
};
void CMersenneTwister::Init(void)
{
uint32 uiSeed;
uiSeed = (uint32)time(0L);
uiSeed ^= (uint32)clock() * 1812433253;
uiSeed ^= (uint32)(ptr)(&uiSeed);
Init(uiSeed);
}
void CMersenneTwister::Init(uint32 iSeed)
{
uint32 i;
uint32 uiPrevious;
mauiState[0] = iSeed;
for (i = 1; i < 624; i++)
{
uiPrevious = mauiState[i - 1];
mauiState[i] = 1812433253 * (uiPrevious ^ (uiPrevious >> 30)) + i;
}
muiIndex = 624;
}
void CMersenneTwister::Kill(void)
{
}
void CMersenneTwister::Twist(void)
{
uint32 i;
uint32 uiCombined;
uint32 uiTwisted;
for (i = 0; i < 624; i++)
{
uiCombined = (mauiState[i] & 0x80000000) | (mauiState[(i + 1) % 624] & 0x7fffffff);
uiTwisted = uiCombined >> 1;
if (uiCombined & 1)
{
uiTwisted ^= 0x9908b0df;
}
mauiState[i] = mauiState[(i + 397) % 624] ^ uiTwisted;
}
muiIndex = 0;
}
uint32 CMersenneTwister::Next(void)
{
uint32 y;
if (muiIndex >= 624)
{
Twist();
}
y = mauiState[muiIndex];
muiIndex++;
y ^= y >> 11;
y ^= (y << 7) & 0x9d2c5680;
y ^= (y << 15) & 0xefc60000;
y ^= y >> 18;
return y;
}
int32 CMersenneTwister::Next(int32 iMin, int32 iMaxInclusive)
{
uint32 uiRange;
uint32 uiThreshold;
uint32 uiValue;
if (iMaxInclusive <= iMin)
{
return iMin;
}
uiRange = (uint32)iMaxInclusive - (uint32)iMin + 1;
if (uiRange == 0)
{
return (int32)Next();
}
uiThreshold = (0 - uiRange) % uiRange;
do
{
uiValue = Next();
}
while (uiValue < uiThreshold);
return (int32)((uint32)iMin + (uiValue % uiRange));
}
