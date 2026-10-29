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
struct tm gsTime;
time_t time(time_t* ptTime)
{
if (ptTime)
{
*ptTime = 0;
}
return 0;
}
clock_t clock(void)
{
return (clock_t)-1;
}
static bool IsLeapYear(int iYear)
{
return ((iYear % 4) == 0) && (((iYear % 100) != 0) || ((iYear % 400) == 0));
}
static int DaysInMonth(int iYear, int iMonth)
{
static const int aiDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
return ((iMonth == 1) && IsLeapYear(iYear)) ? 29 : aiDays[iMonth];
}
struct tm* gmtime(const time_t* ptTime)
{
long lDays;
long lSeconds;
int iYear;
int iMonth;
int iYearDays;
lDays = *ptTime / 86400;
lSeconds = *ptTime % 86400;
if (lSeconds < 0)
{
lSeconds += 86400;
lDays--;
}
gsTime.tm_sec = (int)(lSeconds % 60);
gsTime.tm_min = (int)((lSeconds / 60) % 60);
gsTime.tm_hour = (int)(lSeconds / 3600);
gsTime.tm_wday = (int)((lDays + 4) % 7);
if (gsTime.tm_wday < 0)
{
gsTime.tm_wday += 7;
}
iYear = 1970;
for (;;)
{
iYearDays = IsLeapYear(iYear) ? 366 : 365;
if (lDays < 0)
{
iYear--;
lDays += IsLeapYear(iYear) ? 366 : 365;
}
else if (lDays >= iYearDays)
{
lDays -= iYearDays;
iYear++;
}
else
{
break;
}
}
gsTime.tm_year = iYear - 1900;
gsTime.tm_yday = (int)lDays;
for (iMonth = 0; lDays >= DaysInMonth(iYear, iMonth); iMonth++)
{
lDays -= DaysInMonth(iYear, iMonth);
}
gsTime.tm_mon = iMonth;
gsTime.tm_mday = (int)lDays + 1;
gsTime.tm_isdst = 0;
return &gsTime;
}
struct tm* localtime(const time_t* ptTime)
{
return gmtime(ptTime);
}
time_t mktime(struct tm* psTime)
{
long lDays;
int iYear;
int iMonth;
int iMonths;
time_t tTime;
iYear = psTime->tm_year + 1900 + psTime->tm_mon / 12;
iMonths = psTime->tm_mon % 12;
if (iMonths < 0)
{
iMonths += 12;
iYear--;
}
lDays = 0;
if (iYear >= 1970)
{
for (int i = 1970; i < iYear; i++)
{
lDays += IsLeapYear(i) ? 366 : 365;
}
}
else
{
for (int i = iYear; i < 1970; i++)
{
lDays -= IsLeapYear(i) ? 366 : 365;
}
}
for (iMonth = 0; iMonth < iMonths; iMonth++)
{
lDays += DaysInMonth(iYear, iMonth);
}
lDays += psTime->tm_mday - 1;
tTime = ((lDays * 24 + psTime->tm_hour) * 60 + psTime->tm_min) * 60 + psTime->tm_sec;
*psTime = *gmtime(&tTime);
return tTime;
}
